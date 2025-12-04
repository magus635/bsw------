"""
Base classes for AUTOSAR ARXML elements
"""
from dataclasses import dataclass, field
from typing import Optional, Dict, Any
from threading import RLock
from abc import ABC, abstractmethod
import uuid
from .observers import Subject


@dataclass
class ArxmlElement(ABC, Subject):
    """AUTOSAR element base class"""

    # Core attributes
    short_name: str
    uuid: str = field(default_factory=lambda: str(uuid.uuid4()))
    parent: Optional['ArxmlElement'] = None

    # Metadata
    description: Optional[str] = None
    category: Optional[str] = None
    admin_data: Dict[str, Any] = field(default_factory=dict)

    # OEM extensions
    extensions: Dict[str, Any] = field(default_factory=dict)

    # Internal state
    _dirty: bool = field(default=False, init=False, repr=False)
    _lock: RLock = field(default_factory=RLock, init=False, repr=False)

    def __post_init__(self):
        """Post-initialization validation"""
        Subject.__init__(self)
        self._validate_short_name()

    def _validate_short_name(self):
        """Validate shortName follows AUTOSAR naming rules"""
        if not self.short_name:
            raise ValueError("shortName cannot be empty")
        if not self.short_name[0].isalpha():
            raise ValueError("shortName must start with letter")
        if not all(c.isalnum() or c == '_' for c in self.short_name):
            raise ValueError("shortName contains invalid characters")

    @property
    def is_dirty(self) -> bool:
        """Check if element has been modified"""
        return self._dirty

    def mark_dirty(self):
        """Mark element as modified"""
        with self._lock:
            self._dirty = True
            self.notify('modified', self)
            if self.parent:
                self.parent.mark_dirty()

    def mark_clean(self):
        """Mark element as not modified"""
        with self._lock:
            self._dirty = False

    def get_path(self) -> str:
        """Get full path of element"""
        if self.parent is None:
            return f"/{self.short_name}"
        return f"{self.parent.get_path()}/{self.short_name}"

    @property
    def path(self) -> str:
        """Get full path of element (property)"""
        return self.get_path()

    @abstractmethod
    def to_arxml(self) -> str:
        """Serialize to ARXML string"""
        pass

    @classmethod
    @abstractmethod
    def from_arxml(cls, element: Any) -> 'ArxmlElement':
        """Parse from ARXML element"""
        pass
