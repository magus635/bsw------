"""
CSV Importer
Import configuration data from CSV files
"""
import csv
from pathlib import Path
from typing import List, Dict, Any, Tuple, Optional

from .base_importer import BaseImporter, ImportResult


class CsvImporter(BaseImporter):
    """Importer for CSV (Comma-Separated Values) files"""

    @property
    def supported_extensions(self) -> List[str]:
        return ['.csv', '.txt']

    @property
    def format_name(self) -> str:
        return "CSV (Comma-Separated Values)"

    def validate_file(self, path: Path) -> Tuple[bool, Optional[str]]:
        """Validate CSV file"""
        if not path.exists():
            return False, f"File not found: {path}"

        if path.suffix.lower() not in self.supported_extensions:
            return False, f"Unsupported file type: {path.suffix}"

        try:
            with open(path, 'r', encoding='utf-8') as f:
                # Try to read first line to check format
                reader = csv.reader(f)
                header = next(reader, None)
                if not header:
                    return False, "File is empty or has no header"
                if len(header) < 1:
                    return False, "File must have at least one column"
            return True, None
        except UnicodeDecodeError:
            # Try with latin-1 encoding
            try:
                with open(path, 'r', encoding='latin-1') as f:
                    reader = csv.reader(f)
                    header = next(reader, None)
                    if header:
                        return True, None
            except Exception as e:
                return False, f"Cannot read file: {e}"
            return False, "Cannot decode file encoding"
        except Exception as e:
            return False, f"Invalid CSV format: {e}"

    def _detect_encoding(self, path: Path) -> str:
        """Detect file encoding"""
        encodings = ['utf-8', 'utf-8-sig', 'latin-1', 'gbk', 'gb2312']
        for encoding in encodings:
            try:
                with open(path, 'r', encoding=encoding) as f:
                    f.read(1024)  # Read a sample
                return encoding
            except UnicodeDecodeError:
                continue
        return 'utf-8'  # Default fallback

    def _detect_delimiter(self, path: Path, encoding: str) -> str:
        """Detect CSV delimiter"""
        with open(path, 'r', encoding=encoding) as f:
            sample = f.read(4096)
            try:
                dialect = csv.Sniffer().sniff(sample, delimiters=',;\t|')
                return dialect.delimiter
            except csv.Error:
                return ','  # Default to comma

    def get_columns(self, path: Path) -> List[str]:
        """Get column names from CSV header"""
        encoding = self._detect_encoding(path)
        delimiter = self._detect_delimiter(path, encoding)

        with open(path, 'r', encoding=encoding) as f:
            reader = csv.reader(f, delimiter=delimiter)
            header = next(reader, [])
            return [col.strip() for col in header]

    def preview(self, path: Path, limit: int = 10) -> List[Dict[str, Any]]:
        """Preview first N records from CSV"""
        encoding = self._detect_encoding(path)
        delimiter = self._detect_delimiter(path, encoding)

        records = []
        with open(path, 'r', encoding=encoding) as f:
            reader = csv.DictReader(f, delimiter=delimiter)
            for i, row in enumerate(reader):
                if i >= limit:
                    break
                # Clean up keys and values
                cleaned = {k.strip(): v.strip() if v else '' for k, v in row.items()}
                records.append(cleaned)

        return records

    def import_data(self, path: Path, column_mapping: Dict[str, str]) -> ImportResult:
        """Import data from CSV with column mapping"""
        result = ImportResult(success=False)

        encoding = self._detect_encoding(path)
        delimiter = self._detect_delimiter(path, encoding)

        try:
            with open(path, 'r', encoding=encoding) as f:
                reader = csv.DictReader(f, delimiter=delimiter)

                for row_num, row in enumerate(reader, start=2):  # Start at 2 (header is 1)
                    try:
                        # Apply column mapping
                        mapped_record = {}
                        for src_col, target_param in column_mapping.items():
                            if src_col in row:
                                value = row[src_col].strip() if row[src_col] else ''
                                mapped_record[target_param] = value
                            else:
                                result.warnings.append(
                                    f"Row {row_num}: Source column '{src_col}' not found"
                                )

                        if mapped_record:
                            result.imported_data.append(mapped_record)
                            result.records_imported += 1
                        else:
                            result.records_skipped += 1

                    except Exception as e:
                        result.errors.append(f"Row {row_num}: {e}")
                        result.records_skipped += 1

            result.success = result.records_imported > 0

        except Exception as e:
            result.errors.append(f"Import failed: {e}")

        return result
