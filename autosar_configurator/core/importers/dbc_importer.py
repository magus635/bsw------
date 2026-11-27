"""
DBC Importer
Import CAN configuration from DBC (Vector Database) files
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
import re

from .base_importer import BaseImporter, ImportResult


def _read_dbc_text(path: Path) -> str:
    """Decode DBC bytes across UTF-8, GB18030, and CP1252 without crashing on OEM symbols."""
    raw = Path(path).read_bytes()
    for enc in ("utf-8-sig", "utf-8", "gb18030", "cp1252"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


def _unquote(raw: str) -> str:
    s = raw.strip()
    if len(s) >= 2 and s[0] == '"' and s[-1] == '"':
        s = s[1:-1]
    return s.replace('\\"', '"')


def _resolve_attr_value(raw: str, enum_values: Optional[List[str]] = None) -> Any:
    s = raw.strip()
    if s.startswith('"') and s.endswith('"'):
        return _unquote(s)
    if enum_values:
        try:
            idx = int(s, 0)
            if 0 <= idx < len(enum_values):
                return enum_values[idx]
        except ValueError:
            pass
    try:
        return int(s, 0)
    except ValueError:
        pass
    try:
        return float(s)
    except ValueError:
        return s


def _is_truthy_diag(val: Any) -> bool:
    if isinstance(val, str):
        return val.strip().lower() in ("yes", "true", "1")
    if isinstance(val, (int, float)):
        return val != 0
    return False


@dataclass
class DbcMessage:
    """Represents a CAN message from DBC"""
    id: int
    name: str
    dlc: int
    transmitter: str = ""
    is_extended: bool = False
    signals: List['DbcSignal'] = None
    cycle_time_ms: Optional[float] = None
    send_type: str = ""
    is_fd: bool = False
    is_diag: bool = False
    diag_role: str = ""
    comment: str = ""

    def __post_init__(self):
        if self.signals is None:
            self.signals = []
        if self.dlc and self.dlc > 8:
            self.is_fd = True


@dataclass
class DbcSignal:
    """Represents a CAN signal from DBC"""
    name: str
    start_bit: int
    length: int
    byte_order: str  # 'little_endian' or 'big_endian'
    value_type: str  # 'unsigned' or 'signed'
    factor: float = 1.0
    offset: float = 0.0
    min_value: float = 0.0
    max_value: float = 0.0
    unit: str = ""
    receivers: List[str] = None
    init_value: Optional[float] = None
    send_type: str = ""
    comment: str = ""

    def __post_init__(self):
        if self.receivers is None:
            self.receivers = []


@dataclass
class DbcDatabase:
    """Complete parsed DBC database including ECU nodes, messages, attributes, and comments."""

    path: Path
    db_name: str = ""
    bus_type: str = "CAN"
    ecu_nodes: List[str] = field(default_factory=list)
    messages: List[DbcMessage] = field(default_factory=list)


class DbcParser:
    """DBC parser supporting legacy message listing and rich attribute/comment extraction."""

    # Regex patterns for DBC parsing
    MESSAGE_PATTERN = re.compile(
        r'BO_\s+(\d+)\s+(\w+)\s*:\s*(\d+)\s*(\w*)'
    )
    SIGNAL_PATTERN = re.compile(
        r'SG_\s+(\w+)\s*:\s*(\d+)\|(\d+)@(\d)([+-])\s*'
        r'\(\s*([^,]+)\s*,\s*([^)]+)\s*\)\s*'
        r'\[\s*([^|]+)\s*\|\s*([^\]]+)\s*\]\s*'
        r'"([^"]*)"\s*(.*)$'
    )
    BU_PATTERN = re.compile(r'^BU_\s*:\s*(.*)$')
    BA_DEF_ENUM_PATTERN = re.compile(
        r'\bBA_DEF_\s+(?:(?:BO_|SG_|BU_|EV_|REL_)\s+)?"([^"]+)"\s+ENUM\s+([^;]+);'
    )
    BA_DEF_DEF_PATTERN = re.compile(
        r'\bBA_DEF_DEF_\s+"([^"]+)"\s+("(?:[^"\\]|\\.)*"|[^;\s]+)\s*;'
    )
    BA_GLOBAL_PATTERN = re.compile(
        r'\bBA_\s+"([^"]+)"\s+("(?:[^"\\]|\\.)*"|[^;\s]+)\s*;'
    )
    BA_MSG_PATTERN = re.compile(
        r'\bBA_\s+"([^"]+)"\s+BO_\s+(\d+)\s+("(?:[^"\\]|\\.)*"|[^;\s]+)\s*;'
    )
    BA_SIG_PATTERN = re.compile(
        r'\bBA_\s+"([^"]+)"\s+SG_\s+(\d+)\s+(\w+)\s+("(?:[^"\\]|\\.)*"|[^;\s]+)\s*;'
    )
    CM_MSG_PATTERN = re.compile(
        r'\bCM_\s+BO_\s+(\d+)\s+"((?:[^"\\]|\\.)*)"\s*;'
    )
    CM_SIG_PATTERN = re.compile(
        r'\bCM_\s+SG_\s+(\d+)\s+(\w+)\s+"((?:[^"\\]|\\.)*)"\s*;'
    )

    def parse_database(self, path: Path) -> DbcDatabase:
        """Parse DBC file into a :class:`DbcDatabase` with nodes, comments, and ``BA_`` metadata."""
        path = Path(path)
        content = _read_dbc_text(path)

        ecu_nodes: List[str] = []
        seen_nodes = set()
        messages: List[DbcMessage] = []
        msg_by_raw_id: Dict[int, DbcMessage] = {}
        sig_by_key: Dict[Tuple[int, str], DbcSignal] = {}
        current_message: Optional[DbcMessage] = None
        current_raw_id: Optional[int] = None

        for raw_line in content.splitlines():
            line = raw_line.strip()
            if not line:
                continue

            bu_match = self.BU_PATTERN.match(line)
            if bu_match:
                for tok in re.split(r'[\s,]+', bu_match.group(1).strip()):
                    if tok and tok != "Vector__XXX" and tok not in seen_nodes:
                        seen_nodes.add(tok)
                        ecu_nodes.append(tok)
                continue

            msg_match = self.MESSAGE_PATTERN.match(line)
            if msg_match:
                if current_message is not None:
                    messages.append(current_message)

                raw_id = int(msg_match.group(1))
                # DBC encodes 29-bit extended frame IDs with bit 31 set
                is_extended = bool(raw_id & 0x80000000)
                can_id = raw_id & 0x1FFFFFFF if is_extended else raw_id
                dlc = int(msg_match.group(3))
                transmitter = msg_match.group(4) or ""

                current_message = DbcMessage(
                    id=can_id,
                    name=msg_match.group(2),
                    dlc=dlc,
                    transmitter=transmitter,
                    is_extended=is_extended,
                    is_fd=dlc > 8,
                )
                current_raw_id = raw_id
                msg_by_raw_id[raw_id] = current_message
                if transmitter and transmitter != "Vector__XXX" and transmitter not in seen_nodes:
                    seen_nodes.add(transmitter)
                    ecu_nodes.append(transmitter)
                continue

            if current_message is not None and current_raw_id is not None and line.startswith('SG_'):
                sig_match = self.SIGNAL_PATTERN.match(line)
                if sig_match:
                    byte_order = 'big_endian' if sig_match.group(4) == '0' else 'little_endian'
                    value_type = 'signed' if sig_match.group(5) == '-' else 'unsigned'
                    receivers = [r.strip() for r in sig_match.group(11).split(',') if r.strip()]
                    signal = DbcSignal(
                        name=sig_match.group(1),
                        start_bit=int(sig_match.group(2)),
                        length=int(sig_match.group(3)),
                        byte_order=byte_order,
                        value_type=value_type,
                        factor=float(sig_match.group(6)),
                        offset=float(sig_match.group(7)),
                        min_value=float(sig_match.group(8)),
                        max_value=float(sig_match.group(9)),
                        unit=sig_match.group(10),
                        receivers=receivers,
                    )
                    current_message.signals.append(signal)
                    sig_by_key[(current_raw_id, signal.name)] = signal
                    for recv in receivers:
                        if recv != "Vector__XXX" and recv not in seen_nodes:
                            seen_nodes.add(recv)
                            ecu_nodes.append(recv)

        if current_message is not None:
            messages.append(current_message)

        # Parse BA_DEF_ enum lists and BA_DEF_DEF_ defaults
        enum_defs: Dict[str, List[str]] = {}
        for m in self.BA_DEF_ENUM_PATTERN.finditer(content):
            attr_name = m.group(1).strip()
            literals = re.findall(r'"([^"]*)"', m.group(2))
            if literals:
                enum_defs[attr_name] = literals

        attr_defaults: Dict[str, Any] = {}
        for m in self.BA_DEF_DEF_PATTERN.finditer(content):
            attr_name = m.group(1).strip()
            attr_defaults[attr_name] = _resolve_attr_value(
                m.group(2), enum_defs.get(attr_name)
            )

        db_name = str(attr_defaults.get("DBName") or "")
        bus_type = str(attr_defaults.get("BusType") or "CAN") or "CAN"

        default_msg_send = attr_defaults.get("GenMsgSendType")
        default_sig_send = attr_defaults.get("GenSigSendType")
        default_vframe = attr_defaults.get("VFrameFormat")
        default_cycle = attr_defaults.get("GenMsgCycleTime")
        for msg in messages:
            if isinstance(default_msg_send, str) and default_msg_send:
                msg.send_type = default_msg_send
            if isinstance(default_cycle, (int, float)) and float(default_cycle) > 0:
                msg.cycle_time_ms = float(default_cycle)
            if isinstance(default_vframe, str) and "fd" in default_vframe.lower():
                msg.is_fd = True
            if isinstance(default_sig_send, str) and default_sig_send:
                for sig in msg.signals:
                    sig.send_type = default_sig_send

        # Global BA_ attributes
        for m in self.BA_GLOBAL_PATTERN.finditer(content):
            attr_name = m.group(1).strip()
            resolved = _resolve_attr_value(m.group(2), enum_defs.get(attr_name))
            if attr_name == "DBName" and isinstance(resolved, str) and resolved:
                db_name = resolved
            elif attr_name == "BusType" and isinstance(resolved, str) and resolved:
                bus_type = resolved

        # Message comments (CM_ BO_) and attributes (BA_ ... BO_)
        for m in self.CM_MSG_PATTERN.finditer(content):
            target = msg_by_raw_id.get(int(m.group(1)))
            if target is not None:
                target.comment = m.group(2).replace('\\"', '"').strip()

        for m in self.CM_SIG_PATTERN.finditer(content):
            target = sig_by_key.get((int(m.group(1)), m.group(2).strip()))
            if target is not None:
                target.comment = m.group(3).replace('\\"', '"').strip()

        for m in self.BA_MSG_PATTERN.finditer(content):
            attr_name = m.group(1).strip()
            raw_id = int(m.group(2))
            target = msg_by_raw_id.get(raw_id)
            if target is None:
                continue
            resolved = _resolve_attr_value(m.group(3), enum_defs.get(attr_name))
            if attr_name == "GenMsgCycleTime":
                try:
                    c_val = float(resolved)
                    if c_val >= 0:
                        target.cycle_time_ms = c_val
                except (TypeError, ValueError):
                    pass
            elif attr_name == "GenMsgSendType":
                target.send_type = str(resolved).strip()
            elif attr_name == "VFrameFormat":
                if "fd" in str(resolved).lower():
                    target.is_fd = True
            elif attr_name in ("DiagRequest", "DiagResponse", "DiagState"):
                if _is_truthy_diag(resolved):
                    target.is_diag = True
                    if attr_name == "DiagRequest":
                        target.diag_role = "request"
                    elif attr_name == "DiagResponse":
                        target.diag_role = "response"
                    elif not target.diag_role:
                        target.diag_role = "functional"

        sig_has_start_val = set()
        for m in self.BA_SIG_PATTERN.finditer(content):
            attr_name = m.group(1).strip()
            key = (int(m.group(2)), m.group(3).strip())
            target = sig_by_key.get(key)
            if target is None:
                continue
            resolved = _resolve_attr_value(m.group(4), enum_defs.get(attr_name))
            if attr_name == "GenSigStartValue":
                try:
                    target.init_value = float(resolved)
                    sig_has_start_val.add(key)
                except (TypeError, ValueError):
                    pass
            elif attr_name == "GenSigInactiveValue" and key not in sig_has_start_val:
                try:
                    target.init_value = float(resolved)
                except (TypeError, ValueError):
                    pass
            elif attr_name == "GenSigSendType":
                target.send_type = str(resolved).strip()

        return DbcDatabase(
            path=path,
            db_name=db_name or path.stem,
            bus_type=bus_type,
            ecu_nodes=ecu_nodes,
            messages=messages,
        )

    def parse(self, path: Path) -> List[DbcMessage]:
        """Parse DBC file and return messages"""
        return self.parse_database(path).messages


class DbcImporter(BaseImporter):
    """Importer for DBC (CAN Database) files"""

    def __init__(self):
        self._parser = DbcParser()

    @property
    def supported_extensions(self) -> List[str]:
        return ['.dbc']

    @property
    def format_name(self) -> str:
        return "DBC (Vector CAN Database)"

    def validate_file(self, path: Path) -> Tuple[bool, Optional[str]]:
        """Validate DBC file"""
        if not path.exists():
            return False, f"File not found: {path}"

        if path.suffix.lower() not in self.supported_extensions:
            return False, f"Unsupported file type: {path.suffix}"

        try:
            content = _read_dbc_text(path)[:4096]
            # Check for DBC markers
            if 'VERSION' not in content and 'BO_' not in content:
                return False, "File does not appear to be a valid DBC file"
            return True, None
        except Exception as e:
            return False, f"Cannot read file: {e}"

    def get_columns(self, path: Path) -> List[str]:
        """Get available fields from DBC (message-level)"""
        return [
            "MessageId",
            "MessageName",
            "DLC",
            "Transmitter",
            "SignalCount",
            "IdType"
        ]

    def get_signal_columns(self) -> List[str]:
        """Get available signal-level fields"""
        return [
            "SignalName",
            "StartBit",
            "Length",
            "ByteOrder",
            "ValueType",
            "Factor",
            "Offset",
            "MinValue",
            "MaxValue",
            "Unit",
            "Receivers"
        ]

    def preview(self, path: Path, limit: int = 10) -> List[Dict[str, Any]]:
        """Preview messages from DBC"""
        messages = self._parser.parse(path)

        records = []
        for msg in messages[:limit]:
            id_str = f"0x{msg.id:08X}" if msg.is_extended else f"0x{msg.id:03X}"
            records.append({
                "MessageId": id_str,
                "MessageName": msg.name,
                "DLC": msg.dlc,
                "Transmitter": msg.transmitter,
                "SignalCount": len(msg.signals),
                "IdType": "EXTENDED" if msg.is_extended else "STANDARD"
            })

        return records

    def preview_signals(self, path: Path, message_name: str = None, limit: int = 50) -> List[Dict[str, Any]]:
        """Preview signals from DBC"""
        messages = self._parser.parse(path)

        records = []
        for msg in messages:
            if message_name and msg.name != message_name:
                continue

            for sig in msg.signals:
                records.append({
                    "MessageId": f"0x{msg.id:03X}",
                    "MessageName": msg.name,
                    "SignalName": sig.name,
                    "StartBit": sig.start_bit,
                    "Length": sig.length,
                    "ByteOrder": sig.byte_order,
                    "ValueType": sig.value_type,
                    "Factor": sig.factor,
                    "Offset": sig.offset,
                    "MinValue": sig.min_value,
                    "MaxValue": sig.max_value,
                    "Unit": sig.unit,
                    "Receivers": ", ".join(sig.receivers)
                })

                if len(records) >= limit:
                    return records

        return records

    def import_data(self, path: Path, column_mapping: Dict[str, str]) -> ImportResult:
        """Import data from DBC with column mapping

        For DBC files, the column_mapping maps DBC fields to AUTOSAR parameters.
        """
        result = ImportResult(success=False)

        try:
            messages = self._parser.parse(path)

            for msg in messages:
                try:
                    mapped_record = {}

                    # Map message-level fields
                    id_hex = f"0x{msg.id:08X}" if msg.is_extended else f"0x{msg.id:03X}"
                    field_values = {
                        "MessageId": msg.id,
                        "MessageIdHex": id_hex,
                        "MessageName": msg.name,
                        "DLC": msg.dlc,
                        "Transmitter": msg.transmitter,
                        "IdType": "EXTENDED" if msg.is_extended else "STANDARD",
                    }

                    for src_field, target_param in column_mapping.items():
                        if src_field in field_values:
                            mapped_record[target_param] = field_values[src_field]

                    # Include signals as nested data
                    mapped_record['_signals'] = []
                    for sig in msg.signals:
                        mapped_record['_signals'].append({
                            'name': sig.name,
                            'start_bit': sig.start_bit,
                            'length': sig.length,
                            'byte_order': sig.byte_order,
                            'value_type': sig.value_type,
                            'factor': sig.factor,
                            'offset': sig.offset,
                        })

                    if mapped_record:
                        result.imported_data.append(mapped_record)
                        result.records_imported += 1

                except Exception as e:
                    result.errors.append(f"Message {msg.name}: {e}")
                    result.records_skipped += 1

            result.success = result.records_imported > 0

        except Exception as e:
            result.errors.append(f"Import failed: {e}")

        return result

    def get_messages(self, path: Path) -> List[DbcMessage]:
        """Get parsed messages for advanced usage"""
        return self._parser.parse(path)
