"""
DBC Importer
Import CAN configuration from DBC (Vector Database) files
"""
from pathlib import Path
from typing import List, Dict, Any, Tuple, Optional
from dataclasses import dataclass
import re

from .base_importer import BaseImporter, ImportResult


@dataclass
class DbcMessage:
    """Represents a CAN message from DBC"""
    id: int
    name: str
    dlc: int
    transmitter: str = ""
    signals: List['DbcSignal'] = None

    def __post_init__(self):
        if self.signals is None:
            self.signals = []


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

    def __post_init__(self):
        if self.receivers is None:
            self.receivers = []


class DbcParser:
    """Simple DBC file parser"""

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

    def parse(self, path: Path) -> List[DbcMessage]:
        """Parse DBC file and return messages"""
        messages = []
        current_message = None

        with open(path, 'r', encoding='utf-8', errors='replace') as f:
            for line in f:
                line = line.strip()

                # Parse message definition
                msg_match = self.MESSAGE_PATTERN.match(line)
                if msg_match:
                    if current_message:
                        messages.append(current_message)

                    current_message = DbcMessage(
                        id=int(msg_match.group(1)),
                        name=msg_match.group(2),
                        dlc=int(msg_match.group(3)),
                        transmitter=msg_match.group(4) or ""
                    )
                    continue

                # Parse signal definition
                if current_message and line.startswith('SG_'):
                    sig_match = self.SIGNAL_PATTERN.match(line)
                    if sig_match:
                        byte_order = 'big_endian' if sig_match.group(4) == '0' else 'little_endian'
                        value_type = 'signed' if sig_match.group(5) == '-' else 'unsigned'

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
                            receivers=[r.strip() for r in sig_match.group(11).split(',') if r.strip()]
                        )
                        current_message.signals.append(signal)

        if current_message:
            messages.append(current_message)

        return messages


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
            with open(path, 'r', encoding='utf-8', errors='replace') as f:
                content = f.read(4096)
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
            "SignalCount"
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
            records.append({
                "MessageId": f"0x{msg.id:03X}",
                "MessageName": msg.name,
                "DLC": msg.dlc,
                "Transmitter": msg.transmitter,
                "SignalCount": len(msg.signals)
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
                    field_values = {
                        "MessageId": msg.id,
                        "MessageIdHex": f"0x{msg.id:03X}",
                        "MessageName": msg.name,
                        "DLC": msg.dlc,
                        "Transmitter": msg.transmitter,
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
