"""
Pinout Table Importer

Imports pinout and alternate function definitions from Excel (.xlsx, .xls)
and CSV (.csv) files into AUTOSAR chip definitions.
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Dict, Optional, Any, Tuple
import csv
import re
import logging

from .chip_database import PortPinDef

logger = logging.getLogger(__name__)


@dataclass
class PinoutImportResult:
    """Result of pinout table import operation"""
    ports: Dict[str, List[PortPinDef]] = field(default_factory=dict)
    total_pins: int = 0
    detected_headers: Dict[str, str] = field(default_factory=dict)
    warnings: List[str] = field(default_factory=list)
    errors: List[str] = field(default_factory=list)

    @property
    def success(self) -> bool:
        return len(self.errors) == 0 and self.total_pins > 0


class PinoutTableImporter:
    """Importer for pinout and multiplexing tables from Excel and CSV files"""

    # Common aliases for column header matching (lowercased)
    PORT_ALIASES = {'port', 'port_name', 'gpio_port', 'port name', 'gpio port', '端口', '端口名'}
    PIN_ALIASES = {'pin', 'pin_number', 'pin_index', 'pin number', 'pin id', '引脚号', '管脚号', '引脚序号', 'pin_no', 'pin no'}
    NAME_ALIASES = {'name', 'pin_name', 'pin name', 'signal', 'signal_name', 'signal name', 'net_name', '引脚名称', '信号名称', '管脚名称'}
    DIR_ALIASES = {'direction', 'dir', 'default_direction', 'default direction', '方向', '默认方向', 'i/o', 'io'}
    AF_ALIASES = {'alternate_functions', 'alternate functions', 'af', 'mux', 'functions', '复用功能', '多路复用', 'alternate function'}

    def __init__(self):
        pass

    def import_file(self, file_path: Path, sheet_name: Optional[str] = None) -> PinoutImportResult:
        """Import pinout from an Excel (.xlsx, .xls) or CSV (.csv) file"""
        path = Path(file_path)
        if not path.exists():
            return PinoutImportResult(errors=[f"File not found: {file_path}"])

        suffix = path.suffix.lower()
        if suffix == '.csv':
            return self._import_csv(path)
        elif suffix in ('.xlsx', '.xlsm', '.xltx', '.xltm'):
            return self._import_excel(path, sheet_name)
        else:
            return PinoutImportResult(errors=[
                f"Unsupported file format '{suffix}'. Supported: .csv, .xlsx, .xlsm (save legacy .xls as .xlsx)"
            ])

    def _import_csv(self, path: Path) -> PinoutImportResult:
        """Parse CSV pinout file"""
        encodings = ['utf-8', 'utf-8-sig', 'gbk', 'gb2312', 'latin1']
        content = None
        for enc in encodings:
            try:
                with open(path, 'r', encoding=enc) as f:
                    lines = f.readlines()
                content = lines
                break
            except Exception:
                continue

        if content is None:
            return PinoutImportResult(errors=[f"Failed to decode CSV file: {path}"])

        reader = csv.reader(content)
        rows = [row for row in reader if any(cell.strip() for cell in row)]
        if not rows:
            return PinoutImportResult(errors=["CSV file is empty"])

        return self._process_raw_table(rows)

    def _import_excel(self, path: Path, sheet_name: Optional[str] = None) -> PinoutImportResult:
        """Parse Excel pinout file using openpyxl"""
        try:
            import openpyxl
        except ImportError:
            return PinoutImportResult(errors=["openpyxl library is required for Excel files. Please install it."])

        try:
            wb = openpyxl.load_workbook(path, data_only=True, read_only=True)
            sheet_warning = None
            if sheet_name and sheet_name in wb.sheetnames:
                sheet = wb[sheet_name]
            else:
                sheet = wb.active
                if sheet_name:
                    sheet_warning = f"Sheet '{sheet_name}' not found, using active sheet '{sheet.title}'"

            rows = []
            for row in sheet.iter_rows(values_only=True):
                str_row = [str(cell).strip() if cell is not None else "" for cell in row]
                if any(str_row):
                    rows.append(str_row)

            wb.close()
            if not rows:
                return PinoutImportResult(errors=["Excel sheet is empty"])

            result = self._process_raw_table(rows)
            if sheet_warning:
                result.warnings.insert(0, sheet_warning)
            return result
        except Exception as e:
            logger.exception("Failed to read Excel file")
            return PinoutImportResult(errors=[f"Failed to read Excel file: {str(e)}"])

    def _process_raw_table(self, rows: List[List[str]]) -> PinoutImportResult:
        """Find headers and process rows into PortPinDef objects"""
        result = PinoutImportResult()

        # Find header row (search in first 10 rows)
        header_row_idx = -1
        col_mapping = {}  # semantic key -> col index
        af_col_indices = []  # indices for multiple AF columns (e.g. AF0, AF1...)
        header_row: List[str] = []

        for r_idx, row in enumerate(rows[:10]):
            mapping, af_indices = self._detect_header_mapping(row)
            # Require at least name or (port and pin)
            if 'name' in mapping or ('port' in mapping and 'pin' in mapping):
                header_row_idx = r_idx
                col_mapping = mapping
                af_col_indices = af_indices
                header_row = row
                result.detected_headers = {k: row[v] for k, v in mapping.items()}
                break

        if header_row_idx == -1:
            # Fallback: Assume first row is header
            header_row_idx = 0
            col_mapping, af_col_indices = self._detect_header_mapping(rows[0])
            header_row = rows[0]
            result.detected_headers = {k: rows[0][v] for k, v in col_mapping.items() if v < len(rows[0])}

        af_mode_numbers = self._af_mode_numbers(header_row, af_col_indices)
        ports_dict: Dict[str, Dict[int, PortPinDef]] = {}

        for r_idx in range(header_row_idx + 1, len(rows)):
            row = rows[r_idx]
            if not any(cell.strip() for cell in row):
                continue

            pin_def, err = self._parse_pin_row(row, col_mapping, af_col_indices, af_mode_numbers)
            if err:
                result.warnings.append(f"Row {r_idx + 1}: {err}")
                continue

            if not pin_def:
                continue

            port_name = pin_def.port
            if port_name not in ports_dict:
                ports_dict[port_name] = {}

            # Save pin (overwrite or warn on duplicate)
            if pin_def.pin in ports_dict[port_name]:
                result.warnings.append(
                    f"Row {r_idx + 1}: Duplicate pin {pin_def.name} in {port_name}, overwriting previous definition."
                )

            ports_dict[port_name][pin_def.pin] = pin_def

        # Sort pins by pin index inside each port
        final_ports: Dict[str, List[PortPinDef]] = {}
        for port_name in sorted(ports_dict.keys()):
            pins_map = ports_dict[port_name]
            sorted_pins = [pins_map[p_idx] for p_idx in sorted(pins_map.keys())]
            final_ports[port_name] = sorted_pins

        result.ports = final_ports
        total_pins = sum(len(pins) for pins in final_ports.values())
        result.total_pins = total_pins

        if total_pins == 0 and not result.errors:
            result.errors.append("No valid pins could be extracted from the table.")

        return result

    def _detect_header_mapping(self, header_row: List[str]) -> Tuple[Dict[str, int], List[int]]:
        """Identify which columns correspond to port, pin, name, dir, alternate functions"""
        mapping = {}
        af_indices = []

        for c_idx, cell in enumerate(header_row):
            val = cell.strip().lower()
            val_clean = re.sub(r'[\s_\-]+', ' ', val)

            # Check AF columns (e.g. AF0, AF1, MUX0, Function 1, MUX_1)
            if re.match(r'^(af|mux|func|function)[\s_\-]?\d+$', val) or val in self.AF_ALIASES:
                af_indices.append(c_idx)
                if 'af' not in mapping:
                    mapping['af'] = c_idx
                continue

            if 'port' not in mapping and (val in self.PORT_ALIASES or val_clean in self.PORT_ALIASES):
                mapping['port'] = c_idx
            elif 'pin' not in mapping and (val in self.PIN_ALIASES or val_clean in self.PIN_ALIASES):
                mapping['pin'] = c_idx
            elif 'name' not in mapping and (val in self.NAME_ALIASES or val_clean in self.NAME_ALIASES):
                mapping['name'] = c_idx
            elif 'dir' not in mapping and (val in self.DIR_ALIASES or val_clean in self.DIR_ALIASES):
                mapping['dir'] = c_idx

        return mapping, af_indices

    @staticmethod
    def _af_mode_numbers(header_row: List[str], af_col_indices: List[int]) -> Dict[int, int]:
        """Map AF column index -> hardware mode number.

        Uses the number in the header (AF3 -> 3) when every AF column has one,
        otherwise falls back to column order. A single generic
        'alternate functions' column carries no mode numbering.
        """
        numbers: Dict[int, int] = {}
        for c_idx in af_col_indices:
            cell = header_row[c_idx] if c_idx < len(header_row) else ""
            m = re.search(r'(\d+)\s*$', cell.strip())
            if not m:
                break
            numbers[c_idx] = int(m.group(1))
        if len(numbers) == len(af_col_indices) and len(set(numbers.values())) == len(numbers):
            return numbers
        if len(af_col_indices) > 1:
            return {c_idx: pos for pos, c_idx in enumerate(af_col_indices)}
        return {}

    @staticmethod
    def _normalize_direction(raw_dir: str) -> str:
        """Normalize direction text to INPUT / OUTPUT / INOUT"""
        d = re.sub(r'[\s_\-]+', '', raw_dir.upper())
        if d in ('INOUT', 'IO', 'I/O', 'BI', 'BIDIR', 'BIDIRECTIONAL') or ('IN' in d and 'OUT' in d):
            return "INOUT"
        if d in ('O', 'OUT', 'OUTPUT') or d.startswith('OUT'):
            return "OUTPUT"
        return "INPUT"

    def _parse_pin_row(
        self,
        row: List[str],
        col_mapping: Dict[str, int],
        af_col_indices: List[int],
        af_mode_numbers: Optional[Dict[int, int]] = None,
    ) -> Tuple[Optional[PortPinDef], Optional[str]]:
        """Extract a single PortPinDef from a row"""
        get_val = lambda k: row[col_mapping[k]].strip() if k in col_mapping and col_mapping[k] < len(row) else ""

        raw_port = get_val('port')
        raw_pin = get_val('pin')
        raw_name = get_val('name')
        raw_dir = get_val('dir')

        # Fallback extraction if port/pin not separated
        # Examples: raw_name = "PA0", "PB15", "P00_1", "PORTA_0", "P1.2"
        extracted_port = None
        extracted_pin = None

        if raw_port and raw_pin:
            extracted_port = self._normalize_port_name(raw_port)
            try:
                extracted_pin = int(re.search(r'\d+', raw_pin).group())
            except Exception:
                pass

        # Try parsing from raw_name or raw_port if still missing
        if extracted_port is None or extracted_pin is None:
            candidate = raw_name or raw_port
            match = re.match(r'^P([A-Za-z]|\d{1,2})[._\-]?(\d{1,2})$', candidate, re.IGNORECASE)
            if match:
                p_group = match.group(1).upper()
                extracted_port = f"PORT_{p_group}"
                extracted_pin = int(match.group(2))
            else:
                match_port = re.match(r'^PORT_?([A-Za-z]|\d{1,2})[._\-]?(\d{1,2})$', candidate, re.IGNORECASE)
                if match_port:
                    extracted_port = f"PORT_{match_port.group(1).upper()}"
                    extracted_pin = int(match_port.group(2))

        if extracted_port is None or extracted_pin is None:
            return None, f"Could not determine Port and Pin from row: {row[:5]}"

        # Name fallback
        pin_name = raw_name or f"P{extracted_port.replace('PORT_', '')}{extracted_pin}"

        # Direction normalization
        direction = self._normalize_direction(raw_dir) if raw_dir else "INPUT"

        # Collect alternate functions
        af_list = []
        alt_modes: Dict[int, str] = {}
        af_mode_numbers = af_mode_numbers or {}

        # If dedicated AF columns exist (e.g. AF0, AF1...)
        for idx in af_col_indices:
            if idx < len(row):
                val = row[idx].strip()
                if val and val.upper() not in ('-', 'NA', 'N/A', 'NONE', 'RESERVED'):
                    # May contain sub-splits (e.g. "GPIO / TIM0_CH0")
                    sub_items = [i.strip() for i in re.split(r'[,/;|\n\r]+', val) if i.strip()]
                    for cleaned in sub_items:
                        if cleaned not in af_list:
                            af_list.append(cleaned)
                    # Empty columns are skipped above but keep their number,
                    # so the mode index always matches the hardware mode.
                    if idx in af_mode_numbers and sub_items:
                        alt_modes[af_mode_numbers[idx]] = "/".join(sub_items)

        # Also check single AF column if not in af_col_indices
        if 'af' in col_mapping and col_mapping['af'] not in af_col_indices:
            raw_af = get_val('af')
            if raw_af:
                sub_items = re.split(r'[,/;|\n\r]+', raw_af)
                for item in sub_items:
                    cleaned = item.strip()
                    if cleaned and cleaned not in af_list:
                        af_list.append(cleaned)

        # Flat list keeps GPIO first for existing mapper consumers;
        # alt_modes is never padded, it reflects the table exactly.
        if not af_list:
            af_list = ["GPIO"]
        elif "GPIO" not in af_list:
            af_list.insert(0, "GPIO")

        pin_def = PortPinDef(
            name=pin_name,
            port=extracted_port,
            pin=extracted_pin,
            alternate_functions=af_list,
            default_direction=direction,
            alt_modes=alt_modes,
        )
        return pin_def, None

    def _normalize_port_name(self, raw_port: str) -> str:
        """Normalize port string to standard 'PORT_X' format"""
        p = raw_port.strip().upper()
        if p.startswith('PORT_'):
            return p
        if p.startswith('PORT'):
            return f"PORT_{p[4:].strip('_')}"
        if p.startswith('P') and len(p) > 1 and (p[1:].isalnum()):
            return f"PORT_{p[1:]}"
        return f"PORT_{p}"
