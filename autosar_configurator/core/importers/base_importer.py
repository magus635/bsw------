"""
Base Importer Interface
Defines the common interface for all configuration importers
"""
from abc import ABC, abstractmethod
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Dict, Any, Tuple, Optional


@dataclass
class ImportResult:
    """Result of an import operation"""
    success: bool
    records_imported: int = 0
    records_skipped: int = 0
    errors: List[str] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)
    imported_data: List[Dict[str, Any]] = field(default_factory=list)


class BaseImporter(ABC):
    """Abstract base class for configuration importers"""

    @property
    @abstractmethod
    def supported_extensions(self) -> List[str]:
        """Return list of supported file extensions (e.g., ['.csv', '.txt'])"""
        pass

    @property
    @abstractmethod
    def format_name(self) -> str:
        """Return human-readable format name"""
        pass

    @abstractmethod
    def validate_file(self, path: Path) -> Tuple[bool, Optional[str]]:
        """Validate that file can be imported

        Args:
            path: Path to the file

        Returns:
            Tuple of (is_valid, error_message)
        """
        pass

    @abstractmethod
    def get_columns(self, path: Path) -> List[str]:
        """Get available columns/fields from the file

        Args:
            path: Path to the file

        Returns:
            List of column names
        """
        pass

    @abstractmethod
    def preview(self, path: Path, limit: int = 10) -> List[Dict[str, Any]]:
        """Preview first N records from the file

        Args:
            path: Path to the file
            limit: Maximum number of records to preview

        Returns:
            List of dictionaries containing record data
        """
        pass

    @abstractmethod
    def import_data(self, path: Path, column_mapping: Dict[str, str]) -> ImportResult:
        """Import data from file with column mapping

        Args:
            path: Path to the file
            column_mapping: Dict mapping source columns to target parameter names

        Returns:
            ImportResult with success status and imported data
        """
        pass
