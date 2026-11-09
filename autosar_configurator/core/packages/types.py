"""Package data types."""

from dataclasses import dataclass, field
from typing import List, Optional


@dataclass
class PackageFile:
    """A file in a module package, optionally chip-conditional."""
    path: str
    chips: List[str] = field(default_factory=list)


@dataclass
class ModuleManifest:
    """Module package manifest data.

    Attributes:
        module: Module short name
        definition: AUTOSAR path to ECUC-MODULE-DEF
        implementation_path: Optional path to BSW-IMPLEMENTATION
        files: List of package files with optional chip conditions
        pre: AUTOSAR paths to pre-configuration value sets
        rec: AUTOSAR paths to recommendation value sets
        templates: Optional template directory path
        resources: Optional resources directory path
        implementation: Optional implementation directory path
        exchange_copies: List of exchange copy files (not loaded)
        origin: Origin metadata dict
        inferred: Whether manifest was inferred from plugin.xml
        chip_selector: Optional chip selector configuration
    """
    module: str
    definition: str
    implementation_path: Optional[str] = None
    files: List[PackageFile] = field(default_factory=list)
    pre: List[str] = field(default_factory=list)
    rec: List[str] = field(default_factory=list)
    templates: Optional[str] = None
    resources: Optional[str] = None
    implementation: Optional[str] = None
    exchange_copies: List[str] = field(default_factory=list)
    origin: dict = field(default_factory=dict)
    inferred: bool = False
    chip_selector: Optional[dict] = None
