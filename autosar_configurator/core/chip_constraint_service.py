"""
Chip Constraint Service

Manages chip-specific ECU resource constraints for the UI.
When ResourceSubderivative changes, this service reloads constraints
for the selected chip and notifies UI components to refresh.
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Any, Optional, Callable
from PySide6.QtCore import QObject, Signal
import logging

from .hardware.tresos_properties_parser import TresosPropertiesParser, find_properties_files

logger = logging.getLogger(__name__)


@dataclass
class ChipConstraints:
    """Constraints for a specific chip variant"""
    chip_name: str
    constraints: Dict[str, Any] = field(default_factory=dict)
    
    def get(self, path: str, default: Any = None) -> Any:
        """Get constraint value by path (e.g., 'I2c.MaxChannels') (Case-insensitive)"""
        if path in self.constraints:
            return self.constraints[path]
        
        # Try case-insensitive lookup
        path_lower = path.lower().strip()
        for k, v in self.constraints.items():
            if k.lower().strip() == path_lower:
                return v
                
        return default
    
    def get_enum_values(self, path: str) -> List[str]:
        """Get list of allowed enum values for a path"""
        value = self.get(path)
        
        if isinstance(value, list):
            return value
        if isinstance(value, str) and value:
            return [value]
        return []
    
    def get_max_instances(self, path: str) -> Optional[int]:
        """Get max instances for a container type"""
        value = self.constraints.get(path)
        if isinstance(value, int):
            return value
        return None


class ChipConstraintService(QObject):
    """Service for managing chip-specific ECU constraints
    
    Signals:
        constraints_changed: Emitted when chip selection changes and constraints are reloaded
    """
    
    constraints_changed = Signal(str)  # chip_name
    
    def __init__(self, project_path: Optional[Path] = None, parent=None):
        super().__init__(parent)
        self._project_path: Optional[Path] = project_path
        self._current_chip: Optional[str] = None
        self._constraints_cache: Dict[str, ChipConstraints] = {}
        self._all_chips: List[str] = []
        self._parser = TresosPropertiesParser()
    
    @property
    def current_chip(self) -> Optional[str]:
        return self._current_chip
    
    @property
    def available_chips(self) -> List[str]:
        return self._all_chips
    
    @property
    def current_constraints(self) -> ChipConstraints:
        """Get constraints for the currently selected chip"""
        if self._current_chip and self._current_chip in self._constraints_cache:
            return self._constraints_cache[self._current_chip]
        return ChipConstraints(chip_name="")
    
    def set_project_path(self, project_path: Path):
        """Set project path and discover available chips"""
        self._project_path = project_path
        self._discover_chips()
    
    def set_chip(self, chip_name: Optional[str]):
        """Set the active chip and reload constraints
        
        Args:
            chip_name: Chip variant name (e.g., 'THA6206_LFBGA292'), or None for auto-detect
        """
        if chip_name == self._current_chip:
            return
        
        old_chip = self._current_chip
        self._current_chip = chip_name
        
        if chip_name:
            self._load_chip_constraints(chip_name)
        
        logger.info(f"Chip changed: {old_chip} -> {chip_name}")
        self.constraints_changed.emit(chip_name or "")
    
    def get_constraint(self, path: str, default: Any = None) -> Any:
        """Get constraint value for current chip
        
        Args:
            path: Constraint path (e.g., 'I2c.MaxChannels')
            default: Default value if not found
        """
        return self.current_constraints.get(path, default)
    
    def get_enum_constraint(self, path: str) -> List[str]:
        """Get enum constraint values for current chip"""
        return self.current_constraints.get_enum_values(path)
    
    def get_all_constraints(self) -> Dict[str, Any]:
        """Get all constraints for current chip as a dictionary"""
        return self.current_constraints.constraints
    
    def _discover_chips(self):
        """Discover available chip variants from .properties files"""
        if not self._project_path:
            return
        
        self._all_chips = []
        self._constraints_cache = {}
        
        # Find .properties files in Def/plugins/*/resource/
        def_path = self._project_path / "Def" / "plugins"
        if not def_path.exists():
            return
        
        props_files = list(def_path.rglob("resource/*.properties"))
        
        seen_chips = set()
        for props_file in props_files:
            # Extract chip name from filename
            name = props_file.stem
            chip_name = self._extract_chip_name(name)
            if chip_name and chip_name not in seen_chips:
                seen_chips.add(chip_name)
                self._all_chips.append(chip_name)
                
                # Pre-load constraints
                self._load_chip_constraints(chip_name, props_file)
        
        self._all_chips.sort()
        logger.info(f"Discovered {len(self._all_chips)} chip variants: {self._all_chips}")
    
    def _extract_chip_name(self, filename: str) -> Optional[str]:
        """Extract chip name from properties filename"""
        if '_' not in filename:
            return None
        
        parts = filename.split('_')
        for i, part in enumerate(parts):
            if part.upper().startswith('THA'):
                return '_'.join(parts[i:])
        return None
    
    def _load_chip_constraints(self, chip_name: str, props_file: Optional[Path] = None):
        """Load constraints for a specific chip"""
        if chip_name in self._constraints_cache:
            return
        
        constraints = ChipConstraints(chip_name=chip_name)
        
        if not self._project_path:
            self._constraints_cache[chip_name] = constraints
            return
        
        # Find matching .properties files for this chip
        def_path = self._project_path / "Def" / "plugins"
        if not def_path.exists():
            self._constraints_cache[chip_name] = constraints
            return
        
        # Pattern: look for files containing chip_name
        chip_lower = chip_name.lower()
        props_files = list(def_path.rglob("resource/*.properties"))
        
        for props_file in props_files:
            if chip_lower in props_file.stem.lower():
                try:
                    result = self._parser.parse_file(props_file)
                    constraints.constraints.update(result.properties)
                except Exception as e:
                    logger.warning(f"Failed to parse {props_file}: {e}")
        
        self._constraints_cache[chip_name] = constraints
        logger.info(f"Loaded {len(constraints.constraints)} constraints for chip {chip_name}")
    
    def refresh(self):
        """Force refresh of current chip constraints"""
        if self._current_chip:
            # Clear cache and reload
            if self._current_chip in self._constraints_cache:
                del self._constraints_cache[self._current_chip]
            self._load_chip_constraints(self._current_chip)
            self.constraints_changed.emit(self._current_chip)
