"""
Workspace Manager
Manages the overall project workspace, including multiple BSW module configurations.
"""
import json
import os
import shutil
from dataclasses import dataclass, field, asdict
from typing import Any, Dict, List, Optional, Tuple
from pathlib import Path

from .config_manager import ConfigurationManager
from .model.configuration_model import DEFAULT_VARIANT
from .model.definition_model import EcucModuleDef
from .parser.ecuc_def_parser import EcucDefParser
from . import project_paths
from .project_paths import ProjectDirectories
from .packages.errors import PackageError
from .packages.library import LibraryRef, find_package, scan_library
from .packages.package import ModulePackage
from .baseline.values import values_equal
from .baseline import session as baseline_session
from .baseline.merge import MergeResult
from .baseline.session import ModuleBaseline


@dataclass
class ModuleEntry:
    """Format 8 module entry: active module with definition and configuration paths.

    Attributes:
        name: Module short name (e.g., "Adc", "Mcu").
        definition: AUTOSAR path to the module definition (e.g., "/AUTOSAR/EcucDefs/Adc").
        library: Index into module_libraries; the library that provides this module.
        config_path: POSIX path to the module's configuration file (relative inside project,
                     absolute outside).
        pre_unlocked: List of parameter/container paths that were unlocked in the baseline.
        package_record: Dictionary of package metadata (e.g., version, checksum).
        base_hash: Optional SHA256 hash of the baseline values snapshot; None if not yet recorded.
    """
    name: str
    definition: str
    library: int
    config_path: str
    pre_unlocked: List[str] = field(default_factory=list)
    package_record: Dict[str, Any] = field(default_factory=dict)
    base_hash: Optional[str] = None

    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary for JSON serialization."""
        return asdict(self)

    @classmethod
    def from_dict(cls, d: Dict[str, Any]) -> "ModuleEntry":
        """Create from dictionary."""
        return cls(
            name=d.get("name", ""),
            definition=d.get("definition", ""),
            library=d.get("library", 0),
            config_path=d.get("config_path", ""),
            pre_unlocked=d.get("pre_unlocked", []),
            package_record=d.get("package_record", {}),
            base_hash=d.get("base_hash"),
        )

def _chip_selector_values(project):
    """Selector values declared by the chip library and the project's chips/ (never raises)."""
    try:
        from .hardware.ecu_resource_resolver import selector_values
        return selector_values(project)
    except Exception:  # noqa: BLE001 - parsing must not fail because of chip data
        return None


def _base_values(configuration) -> Dict[str, Any]:
    """Every parameter and reference value of ``configuration`` under the keys a variant override
    uses: ``<container path>.<name>``, ``<container path>.ref:<name>`` and the older
    ``<container short name>.<name>``."""
    values: Dict[str, Any] = {}

    def walk(container):
        for prefix in (container.get_path(), container.short_name):
            for name, param in container.parameter_values.items():
                values.setdefault(f"{prefix}.{name}", param.value)
            for name, ref in container.reference_values.items():
                values.setdefault(f"{prefix}.ref:{name}", ref.value_ref)
        for sub in container.sub_containers:
            walk(sub)

    for container in configuration.containers:
        walk(container)
    return values


_same_value = values_equal  # one value-equality rule, shared with the baseline layer


def _log_warning(message: str, *args) -> None:
    """Module-level logger (this file imports ``logging`` inside its methods by convention)."""
    import logging
    logging.getLogger(__name__).warning(message, *args)


def _snapshot_hash(path: Path) -> Optional[str]:
    """``"sha256:<hex>"`` of a baseline snapshot on disk, or None when there is none.

    Used when a module entry is re-created (re-add after a removal): the snapshot the user
    accepted is still the Base to merge against, and its hash is what records that.
    """
    try:
        if not Path(path).is_file():
            return None
        from .baseline.store import hash_file
        return hash_file(Path(path))
    except OSError:
        return None


def scan_libraries(project) -> List[Tuple[int, List[ModulePackage]]]:
    """(library index, packages) of every library in ``project.module_libraries``.

    Relative library paths resolve against the project root.  A library that cannot
    be scanned (e.g. unknown kind) contributes no packages and is logged.
    """
    import logging
    base = project_paths.project_root(project) if getattr(project, "path", None) else Path(".")
    result = []
    for index, ref in enumerate(getattr(project, "module_libraries", [])):
        try:
            packages = scan_library(ref, base)
        except PackageError as exc:
            logging.getLogger(__name__).warning("Cannot scan module library %s: %s", ref.path, exc)
            packages = []
        result.append((index, packages))
    return result


def package_for_path(project, file: Path) -> Optional[Tuple[int, ModulePackage]]:
    """The (library index, package) whose package directory contains ``file``, or None."""
    try:
        target = Path(file).resolve()
    except OSError:
        return None
    for index, packages in scan_libraries(project):
        for pkg in packages:
            root = pkg.root.resolve()
            if target == root or root in target.parents:
                return index, pkg
    return None


class WorkspaceProject:
    """Represents a DaVinci-style project containing multiple modules"""
    
    def __init__(self, name: str, path: Optional[Path] = None, format_version: int = 7):
        self.name = name
        self.path = path
        self.format_version = format_version
        # Map module name to its manager
        self.module_managers: Dict[str, ConfigurationManager] = {}
        # Map module name to its definition file path (for reloading)
        self.module_defs: Dict[str, Path] = {}

        # Project type (Vector or EB)
        from .config_manager import ProjectType
        self.project_type: ProjectType = ProjectType.VECTOR

        # Definition search paths (for EB projects with external plugins)
        self.def_search_paths: List[Path] = []

        # Variant Management
        self.variants: List[str] = ["Default"]  # Always have at least Default variant
        self.active_variant: Optional[str] = "Default"  # Currently selected variant
        # Default overrides dropped at load that differed from the base value: (module, path, override, base)
        self.default_override_conflicts: List[Tuple[str, str, Any, Any]] = []

        # Metadata
        from datetime import datetime
        self.created_date: str = datetime.now().isoformat()
        self.author: str = ""
        self.description: str = ""
        self.version: str = "1.0.0"

        # Cross-module dependency rules (cached results from analysis)
        self.dependency_rules: List[Dict] = []

        # Chip/Variant Selection (for projects with multiple chip .properties files)
        self.available_chips: List[str] = []  # Discovered chip variants from .properties
        self.selected_chip: Optional[str] = None  # User's selected chip

        # Chip dependency scan: added directories (POSIX, relative to the project
        # directory or absolute) and extra chip keywords
        self.chip_scan_dirs: List[str] = []
        self.chip_scan_keywords: List[str] = []

        # Memory map check: source and MemMap header directories and the linker
        # file (POSIX, relative to the project directory or absolute)
        self.memmap_source_dirs: List[str] = []
        self.memmap_header_dirs: List[str] = []
        self.memmap_linker_file: Optional[str] = None

        # EB project import: original source root (kept read-only, separate from save location)
        self.eb_source_root: Optional[Path] = None

        # EB import mode: 'copy' (self-contained, plugins copied into Def/plugins/)
        # or 'link' (Def/plugins and templates/{Module} are symlinks into the
        # original EB tree at eb_source_root)
        self.import_mode: str = "copy"

        # Per-module provenance: name -> {"origin": "native"|"eb-import",
        # "source_epc": str|None (relative to eb_source_root), "imported_at": str|None}
        self.module_provenance: Dict[str, Dict[str, Any]] = {}

        # ECU resources from .properties files and the chip YAML (for ecu:get/ecu:list
        # during UI and generation); see load_ecu_resources()
        self.ecu_resources: Dict[str, Any] = {}

        # Chip database used to look up selected_chip's ecu_resources; None means
        # the shared database over the packaged data/chips directory
        self.chip_database = None

        # Last EcuResourceReport from diagnose_ecu_resources() (None until run)
        self.ecu_resource_report = None

        # {name, resource_version, checksum} of the chip data the project uses,
        # saved in the project file; set when the chip is saved into or updated
        # in the project (see record_chip_data)
        self.chip_data_record = None

        # Directory table of a format 8 project (see project_paths); None means the
        # legacy directory names (ConfigValue/, templates/, generateCode/, Def/plugins/)
        self.directories: Optional[ProjectDirectories] = None

        # Format 8 module packages integration
        self.module_libraries: List[LibraryRef] = []  # List of available module libraries
        self.module_entries: Dict[str, ModuleEntry] = {}  # Active modules keyed by name
        self.packages: Dict[str, "ModulePackage"] = {}  # Module package of each module, by name
        # Format 8: raw variant_overrides of modules that failed to load, kept so a
        # save writes them back unchanged
        self.unloaded_variant_overrides: Dict[str, Any] = {}

        # Format 8 baseline layer: the accepted baseline of each module this session knows
        # (Base' after an accepted merge, the base of an add-module), by module name. This
        # is what the value origins and the Pre lock read; a module without an entry has no
        # baseline of its own (format ≤7, or an entry that never loaded).
        self.baselines: Dict[str, ModuleBaseline] = {}

    def add_module_from_package(self, pkg: "ModulePackage", lib_index: int,
                                persist: bool = True, confirm=None,
                                reconcile: bool = True) -> ConfigurationManager:
        """Add the module provided by ``pkg`` (from ``module_libraries[lib_index]``).

        Parses the package's definition file for ``selected_chip``, adds the module and
        registers it in ``module_entries`` and ``packages``.  An entry already present
        (a project being loaded, or a module re-added after a failed load) keeps its
        configuration path and baseline fields.

        Two cases, because the module may already have values:

        - **A new module** (no ``config/<M>.arxml``): Base' is composed from the package and
          becomes Active (D8: Rec included), and — with ``persist`` — the snapshot is
          written immediately.
        - **A configuration file exists** (re-add after ``remove_module``, a project being
          loaded): the file is Active, and Base' is reconciled into it exactly as on load —
          Base is the snapshot on disk when there still is one, the merge needs ``confirm``
          (``None`` rejects), and nothing is written until the next save. Writing Base'
          directly here would destroy the Base the user accepted and only force the Pre
          deviations on the next open.

        Args:
            pkg: The module package.
            lib_index: Index of the library that provided ``pkg``.
            persist: Write a new module's baseline snapshot at once (the add-module case).
                A load passes False so the saved Base survives until the merge has seen it.
            confirm: ``(preview_text, MergeResult) -> bool`` for the merge of an existing
                configuration; ``None`` rejects.
            reconcile: Whether an existing configuration is merged with Base' here. The
                project load passes False: it reconciles every module itself, once, in
                :meth:`reconcile_baseline` — so the add path must not do it a second time.

        Raises:
            PackageError / PackageConflictError: the package has no unique definition file
            ValueError: the existing configuration file cannot be loaded; the project is
                left as it was before the call. A baseline failure is reported separately:
                the module stays loaded, without a baseline, and the project continues.
        """
        def_file = pkg.definition_file(self.selected_chip)
        parser = EcucDefParser()
        parser.set_selector_values(_chip_selector_values(self))
        module_def = parser.parse_module_def_file(def_file)
        name = module_def.short_name
        stashed = self.unloaded_variant_overrides.get(name)
        manager = self.add_module(module_def, def_file)

        entry = self.module_entries.get(name)
        new_entry = entry is None
        if new_entry:
            config_rel = project_paths.config_file(self, name)
            try:
                config_rel = config_rel.relative_to(project_paths.project_root(self))
            except ValueError:
                pass
            entry = ModuleEntry(
                name=name,
                definition=pkg.manifest.definition,
                library=lib_index,
                config_path=config_rel.as_posix(),
            )

        config_loaded = False
        if entry.config_path and self.path:
            config_path = Path(entry.config_path)
            if not config_path.is_absolute():
                config_path = project_paths.project_root(self) / config_path
            if config_path.is_file():
                try:
                    manager.load_configuration(config_path)
                except Exception as exc:  # noqa: BLE001 - roll back, then report
                    self._rollback_added_module(name, stashed)
                    raise ValueError(
                        f"Failed to load configuration {entry.config_path}: {exc}") from exc
                config_loaded = True
                if stashed is not None:
                    # load_configuration replaces the configuration object
                    manager.configuration.variant_overrides = stashed

        if new_entry:
            self.module_entries[name] = entry
        else:
            entry.definition = pkg.manifest.definition
            entry.library = lib_index
        self.packages[name] = pkg

        if self.format_version < 8:
            return manager

        if config_loaded:
            if not reconcile:
                return manager          # the project load reconciles, once, after this call
            # An existing Active: merge Base' into it, never replace its Base
            if new_entry:
                # The entry was created by this call (re-add after a removal): the snapshot
                # on disk is still the Base the user accepted, if it is intact. Adoption is
                # limited to a genuinely new entry — an entry that merely lacks a hash in
                # .dpa must stay a migrated project (every value USER).
                entry.base_hash = _snapshot_hash(baseline_session.base_snapshot_path(self, name))
            try:
                self.reconcile_baseline(manager, entry, pkg, confirm)
            except Exception as exc:  # noqa: BLE001 - one module's baseline must not abort the project
                self.baselines.pop(name, None)
                manager.baseline_error = str(exc)
                _log_warning("基线合并失败，模块按无基线处理：%s（%s）", name, exc)
            return manager

        # A new module: Active = Base' (D8), snapshot written at once
        try:
            baseline = baseline_session.compute_new_base(
                pkg, self.selected_chip, manager.module_def, name)
            if baseline.has_layers:
                baseline_session.adopt_base(manager, baseline.base_config)
                if persist:
                    entry.base_hash = baseline_session.write_baseline(self, name, baseline)
                else:
                    baseline.dirty = True
                self.baselines[name] = baseline
        except Exception as exc:  # noqa: BLE001 - same rollback as a failed config load
            self._rollback_added_module(name, stashed)
            raise ValueError(
                f"Failed to initialise the baseline of {name}: {exc}") from exc
        return manager

    def _rollback_added_module(self, name: str, stashed: Any) -> None:
        """Undo the parts of ``add_module_from_package`` done before it failed."""
        self.module_managers.pop(name, None)
        self.module_defs.pop(name, None)
        self.baselines.pop(name, None)
        if stashed is not None:
            self.unloaded_variant_overrides[name] = stashed

    _MISSING = object()

    def reconcile_baseline(self, manager: ConfigurationManager, entry: "ModuleEntry",
                           pkg: "ModulePackage", confirm=None) -> Optional["MergeResult"]:
        """Recompute Base' of ``entry``'s module and merge it into Active (design §6.5 ④).

        The saved Base comes from the snapshot and its layers file; ``entry.base_hash``
        decides whether the snapshot is still the one the project recorded. The merge is
        applied only when ``confirm`` accepts it (``None`` rejects), and Base' then becomes
        the module's baseline for this session — ``dirty`` asks :meth:`save_project` to write
        it out. A rejected merge leaves Active, the snapshot and the remembered baseline as
        they were, so the next open prompts again.

        A package that contributes no Rec or Pre layer has no baseline to reconcile: the
        module keeps the one it was loaded with (if any) and nothing is prompted.

        Returns:
            The merge result, or ``None`` when the module has no baseline at all.
        """
        if self.format_version < 8:
            return None
        name = entry.name
        new = baseline_session.compute_new_base(pkg, self.selected_chip, manager.module_def, name)
        if not new.has_layers:
            return None

        old = baseline_session.load_baseline(self, name, entry.base_hash)
        unlocked = set(entry.pre_unlocked)
        result, applied = baseline_session.reconcile(
            manager, old.base_config, new, unlocked, confirm, module_name=name)
        if applied:
            new.dirty = True                       # written by the next save
            self.baselines[name] = new
        elif old.base_config is None and not result.has_changes:
            # A project with no snapshot whose active values already agree with Base' (a
            # migrated project, a first open): Base' becomes the snapshot on the next save,
            # so the values Active holds get a base to be compared with from then on. A
            # merge that had something to change and was rejected writes nothing.
            new.dirty = True
            self.baselines[name] = new
        elif old.layers_untrusted and not result.has_changes:
            # The snapshot verified but its layers could not be trusted (a half-written
            # update, a legacy file), so nothing is marked Pre and the lock is off. Healing
            # that is not a change the user has to confirm — Active is not touched — so the
            # freshly composed baseline replaces the pair on the next save. A merge that
            # did have changes and was rejected keeps waiting for an accepted one.
            new.dirty = True
            self.baselines[name] = new
        else:
            # Unchanged, rejected or no confirm: Base, its layers and the snapshot stay as
            # they are. ``old`` still carries Base's layers (and Base' when it has no
            # snapshot), which is what the origins and the Pre lock read.
            self.baselines[name] = old
        return result

    def snapshot_module(self, name: str) -> Dict[str, Any]:
        """Everything the project keeps for module ``name`` (any part may be absent),
        for restoring it with restore_module() after remove_module()."""
        return {
            "name": name,
            "manager": self.module_managers.get(name),
            "def_path": self.module_defs.get(name),
            "entry": self.module_entries.get(name),
            "package": self.packages.get(name),
            "overrides": self.unloaded_variant_overrides.get(name, self._MISSING),
            "baseline": self.baselines.get(name, self._MISSING),
        }

    def restore_module(self, snapshot: Dict[str, Any]) -> None:
        """Put back what snapshot_module() captured (parts that were absent stay absent)."""
        name = snapshot["name"]
        if snapshot["manager"] is not None:
            self.module_managers[name] = snapshot["manager"]
        if snapshot["def_path"] is not None:
            self.module_defs[name] = snapshot["def_path"]
        if snapshot["entry"] is not None:
            self.module_entries[name] = snapshot["entry"]
        if snapshot["package"] is not None:
            self.packages[name] = snapshot["package"]
        if snapshot["overrides"] is not self._MISSING:
            self.unloaded_variant_overrides[name] = snapshot["overrides"]
        if snapshot.get("baseline", self._MISSING) is not self._MISSING:
            self.baselines[name] = snapshot["baseline"]

    def discover_available_chips(self) -> List[str]:
        """Scan project for available chip .properties files.
        
        Looks in Def/plugins/*/resource/*.properties for chip definition files.
        Returns list of chip names (derived from filename).
        """
        if not self.path:
            return []
        
        chips = []
        def_dir = project_paths.resolve(self, "legacy_plugins")
        if def_dir.exists():
            # Look for resource/*.properties files
            for props_file in def_dir.rglob("resource/*.properties"):
                # Extract chip name from filename (e.g., CotexR52_THA6206_LFBGA292.properties -> THA6206_LFBGA292)
                name = props_file.stem
                # Try to extract chip identifier (THAxxxx pattern)
                parts = name.split('_')
                for i, part in enumerate(parts):
                    if part.startswith('THA') or part.startswith('tha'):
                        chip_name = '_'.join(parts[i:])
                        chips.append(chip_name)
                        break
                else:
                    # If no THA pattern, use the full stem
                    chips.append(name)
        
        self.available_chips = sorted(set(chips))
        return self.available_chips

    def load_ecu_resources(self) -> Dict[str, Any]:
        """Build ``self.ecu_resources`` for ecu:get() / ecu:list().

        Delegates to EcuResourceResolver: .properties files of the project and
        of the loaded module plugins (lower priority) merged with the selected
        chip's YAML ``ecu_resources`` (higher priority).  The whole dict is
        recomputed, so keys of a previously selected chip never linger.

        Returns:
            Flat dict mapping property keys (e.g. 'Adc.HwUnitId') to values.
        """
        from .hardware.ecu_resource_resolver import EcuResourceResolver
        from .parser.xdm_expression_resolver import apply_chip_expressions

        self.ecu_resources = EcuResourceResolver(self.chip_database).resolve(self)
        # Defaults, ranges and maximum counts written as chip expressions in the
        # loaded definitions follow the same resources as ecu:get()
        for manager in self.module_managers.values():
            module_def = getattr(manager, "module_def", None)
            if module_def is not None:
                apply_chip_expressions(module_def, self.ecu_resources)
        return self.ecu_resources

    # --- project-local chip definition (<project dir>/chips/<chip>.yaml) -------------

    @property
    def chip_store(self):
        """The project's chip directory, or None while the project has no location."""
        if not self.path:
            return None
        from .hardware.project_chip_store import ProjectChipStore

        path = Path(self.path)
        return ProjectChipStore(path.parent if path.suffix == ".dpa" else path)

    def _chip_library(self):
        from .hardware.chip_database import get_default_chip_database

        return self.chip_database or get_default_chip_database()

    def chip_source(self) -> str:
        """Where the selected chip's resources come from: 'project', 'library',
        'properties' (no chip YAML anywhere) or 'none' (no chip selected)."""
        from .hardware.ecu_resource_resolver import chip_for_project

        return chip_for_project(self, self.chip_database)[0]

    def adopt_selected_chip(self):
        """Save the selected chip as the project's own copy (chips/<chip>.yaml).

        The copy comes from the chip library; if the library does not have the
        chip, it is built from the project's resource .properties files.  Does
        nothing and returns the existing path when the project already has a copy.

        Raises:
            ValueError: no chip selected, project has no location, or no data to copy
        """
        import copy

        from .hardware.ecu_resource_resolver import chip_for_project, scan_properties
        from .hardware.project_chip_store import (
            SOURCE_LIBRARY, SOURCE_NONE, SOURCE_PROJECT, chip_from_properties,
        )

        store = self.chip_store
        if store is None:
            raise ValueError("The project has no location yet; save it first")
        source, chip = chip_for_project(self, self.chip_database)
        if source == SOURCE_NONE:
            raise ValueError("No chip is selected")
        if source == SOURCE_PROJECT:
            return store.path_for(self.selected_chip)
        if source == SOURCE_LIBRARY:
            new_chip = copy.deepcopy(chip)
        else:
            flat = scan_properties(self, resource_only=True)
            if not flat:
                raise ValueError(
                    f"No chip definition for {self.selected_chip} in the library and no "
                    f"resource .properties file in the project to build one from")
            new_chip = chip_from_properties(self.selected_chip, flat)
        path = store.save(new_chip)
        self.record_chip_data()
        self.load_ecu_resources()
        return path

    def record_chip_data(self):
        """Remember name, version and checksum of the chip data the project now uses."""
        from .hardware.chip_exporter import chip_checksum
        from .hardware.ecu_resource_resolver import chip_for_project

        chip = chip_for_project(self, self.chip_database)[1]
        self.chip_data_record = None if chip is None else {
            "name": chip.name,
            "resource_version": chip.resource_version,
            "checksum": chip_checksum(chip),
        }
        return self.chip_data_record

    def chip_data_findings(self):
        """Problems with the integrity of the chip data, as messages (empty when fine).

        Reports a project copy changed outside the designer or no longer matching
        the recorded checksum, a library chip that differs from the copy, and each
        entry the chip marks as still to fill in (待填写).
        """
        from .hardware.chip_exporter import chip_checksum
        from .hardware.chip_repair import to_fill_in_keys
        from .hardware.ecu_resource_resolver import chip_for_project
        from .hardware.project_chip_store import SOURCE_LIBRARY, SOURCE_PROJECT

        messages = []
        source, chip = chip_for_project(self, self.chip_database)
        if chip is None:
            return messages
        current = chip_checksum(chip)
        if source == SOURCE_PROJECT:
            record = self.chip_data_record or {}
            if record.get("name") not in (None, chip.name):
                record = {}     # describes another chip (saved before a chip switch was recorded)
            if chip.content_modified or (record.get("checksum") and record["checksum"] != current):
                messages.append(f"The project's chip data chips/{chip.name}.yaml was modified "
                                f"after it was saved into the project")
            library = self._chip_library().get_chip(chip.name)
            if library is not None and chip_checksum(library) != current:
                messages.append(f"The chip library has a different version of {chip.name} "
                                f"(Project Properties > Update from Library)")
        elif source == SOURCE_LIBRARY and chip.content_modified:
            messages.append(f"The chip library's {chip.name} was modified outside the chip designer")
        messages.extend(f"ECU resource '{key}' of chip {chip.name} is still to fill in (marked 待填写)"
                        for key in to_fill_in_keys(chip))
        return messages

    def chip_update_differences(self):
        """(lines, total) describing how the project's copy differs from the library's chip.

        Empty when the project has no copy or the library has no such chip.
        """
        from .hardware.project_chip_store import describe_differences

        store = self.chip_store
        if store is None or not self.selected_chip:
            return [], 0
        local = store.load(self.selected_chip)
        library = self._chip_library().get_chip(self.selected_chip)
        if local is None or library is None:
            return [], 0
        return describe_differences(local, library)

    def update_chip_from_library(self):
        """Replace the project's copy of the selected chip with the library's version.

        Raises:
            ValueError: no chip selected, no location, or the library lacks the chip
        """
        import copy

        store = self.chip_store
        if store is None:
            raise ValueError("The project has no location yet; save it first")
        if not self.selected_chip:
            raise ValueError("No chip is selected")
        library = self._chip_library().get_chip(self.selected_chip)
        if library is None:
            raise ValueError(f"The chip library has no chip {self.selected_chip}")
        path = store.save(copy.deepcopy(library))
        self.record_chip_data()
        self.load_ecu_resources()
        return path

    def chip_changed(self):
        """Call after ``selected_chip`` changed: keep the project's chips/ in step and recompute.

        A project that already keeps its chips in ``chips/`` gets the newly
        selected chip copied there from the library; a project without a
        ``chips/`` directory is left as it is (the user can adopt the chip
        explicitly).  The ECU resources are always recomputed from scratch.
        """
        import copy

        store = self.chip_store
        if (self.selected_chip and store is not None and store.exists()
                and not store.has(self.selected_chip)):
            library = self._chip_library().get_chip(self.selected_chip)
            if library is not None:
                store.save(copy.deepcopy(library))
                self.record_chip_data()
        # The record describes the chip in use: a switch to a chip whose copy is already
        # in chips/ records it too (re-opening the same chip keeps the saved record)
        record = self.chip_data_record or {}
        if self.selected_chip and record.get("name") != self.selected_chip:
            self.record_chip_data()
        return self.load_ecu_resources()

    def apply_chip_selectors(self, modules=None):
        """Write the selected chip's declared selector values into the loaded modules.

        Only for an explicit chip selection by the user; opening or importing a
        project leaves the configuration as it is (see check_selectors).

        Args:
            modules: limit to these module names; None = every loaded module

        Returns:
            SelectorResult listing the values changed and the selectors not written
        """
        from .hardware.chip_selectors import apply_selectors
        from .hardware.ecu_resource_resolver import chip_for_project

        return apply_selectors(self, chip_for_project(self, self.chip_database)[1], modules)

    def chip_from_configuration(self) -> Optional[str]:
        """The chip whose declared selectors match the configuration (for a project
        without ``selected_chip``), or None when no single chip matches."""
        from .hardware.chip_selectors import chip_from_selectors
        from .hardware.ecu_resource_resolver import _project_dir
        from .hardware.project_chip_store import ProjectChipStore

        chips = {}
        library = self._chip_library()
        for name in library.list_chips():
            chip = library.get_chip(name)
            if chip is not None:
                chips[name] = chip
        project_dir = _project_dir(self)
        if project_dir is not None:
            store = ProjectChipStore(project_dir)
            for name in store.list_names():
                chip = store.load(name)
                if chip is not None:
                    chips[name] = chip
        return chip_from_selectors(self, [chips[n] for n in sorted(chips)])

    def diagnose_ecu_resources(self):
        """Report ecu:get()/ecu:list() keys the loaded modules need but the project lacks.

        Stores the EcuResourceReport in ``self.ecu_resource_report`` and returns it.
        Scans module xdm files and templates, so call it when modules or the chip
        change rather than before every generation.  Never raises.
        """
        from .hardware.ecu_resource_diagnostics import diagnose
        from .hardware.ecu_resource_resolver import other_chip_keys

        try:
            from .hardware.ecu_resource_diagnostics import check_selectors, pin_table_differences
            from .hardware.ecu_resource_resolver import chip_for_project

            previous = self.ecu_resource_report
            report = diagnose(self, self.ecu_resources,
                              other_chip_keys=other_chip_keys(self, self.chip_database),
                              log=False)
            chip = chip_for_project(self, self.chip_database)[1]
            report.consistency.extend(check_selectors(self, chip))
            if chip is not None:
                report.consistency.extend(pin_table_differences(chip))
            report.consistency.extend(self.chip_data_findings())
            # The same finding is not logged again on every reload
            if previous is None or previous.warning_lines() != report.warning_lines():
                from .hardware.ecu_resource_diagnostics import log_report
                log_report(report)
            self.ecu_resource_report = report
        except Exception:  # noqa: BLE001 - diagnostics must never break project loading
            import logging
            logging.getLogger(__name__).exception("ECU resource diagnosis failed")
            self.ecu_resource_report = None
        return self.ecu_resource_report

    def ensure_default_variant(self):
        """Ensure Default variant exists for all modules

        Called when loading projects or adding modules to ensure
        the Default variant is properly initialized.
        """
        for name, manager in self.module_managers.items():
            config = manager.configuration
            if "Default" not in config.variant_overrides:
                config.variant_overrides["Default"] = {}
        
        # Ensure Default is in variants list
        if "Default" not in self.variants:
            self.variants.insert(0, "Default")
        
        # Set active variant to Default if not set
        if not self.active_variant:
            self.active_variant = "Default"

    def fold_default_overrides(self) -> List[Tuple[str, str, Any, Any]]:
        """Drop the "Default" variant's override layer: Default is the base configuration.

        Projects saved before this rule kept a copy of each edit made in the panel as a Default
        override, which the panel showed instead of the base value (the generator reads the base
        value).  The base value is kept.  Returns the overrides that differed from it, sorted, as
        (module, path, override, base); base is None where the base has no such value.
        """
        conflicts = []
        for module_name, manager in sorted(self.module_managers.items()):
            overrides = manager.configuration.variant_overrides.pop(DEFAULT_VARIANT, None)
            if not overrides:
                continue
            base = _base_values(manager.configuration)
            for path, value in sorted(overrides.items()):
                if path not in base or not _same_value(value, base[path]):
                    conflicts.append((module_name, path, value, base.get(path)))
        return conflicts
    
    def _copy_container_to_base(self, container, base_dict: dict):
        """Recursively copy container parameter values to Base dict"""
        for param_name, param_val in container.parameter_values.items():
            param_path = f"{container.get_path()}.{param_name}"
            base_dict[param_path] = param_val.value
        
        for sub in container.sub_containers:
            self._copy_container_to_base(sub, base_dict)
        
    def add_module(self, module_def: EcucModuleDef, def_path: Path, def_missing: bool = False) -> ConfigurationManager:
        """Add a new module to the project"""
        if module_def.short_name in self.module_managers:
            raise ValueError(f"Module {module_def.short_name} already exists in project")
            
        manager = ConfigurationManager(module_def, project_context=self, def_missing=def_missing)
        self.module_managers[module_def.short_name] = manager
        self.module_defs[module_def.short_name] = def_path
        # Overrides kept from an earlier failed load of this module come back with it
        stashed = self.unloaded_variant_overrides.pop(module_def.short_name, None)
        if stashed is not None:
            manager.configuration.variant_overrides = stashed
        return manager
        
    def remove_module(self, module_name: str):
        """Remove a module from the project.

        Before deleting, scan all other loaded modules for references that
        resolve into the module being removed.  Such references would become
        dangling pointers, so we warn about them and null-out the target so
        downstream code generation/validation does not silently consume a
        stale pointer.
        """
        if module_name in self.module_managers:
            manager = self.module_managers[module_name]
            removed_containers = set()

            def collect(container):
                removed_containers.add(id(container))
                for sub in container.sub_containers:
                    collect(sub)

            for container in manager.configuration.containers:
                collect(container)

            def scan(container, owner_name):
                def handle(ref_value):
                    if ref_value.is_resolved and ref_value.target is not None \
                            and id(ref_value.target) in removed_containers:
                        print(f"  - Warning: reference in module '{owner_name}' "
                              f"({container.get_path()}) targets removed module "
                              f"'{module_name}' — clearing dangling pointer "
                              f"('{ref_value.value_ref}')")
                        if ref_value in ref_value.target.referenced_by:
                            ref_value.target.referenced_by.remove(ref_value)
                        ref_value.target = None
                for ref_value in container.reference_values.values():
                    handle(ref_value)
                for ref_list in container.multi_reference_values.values():
                    for ref_value in ref_list:
                        handle(ref_value)
                for sub in container.sub_containers:
                    scan(sub, owner_name)

            for other_name, other_mgr in self.module_managers.items():
                if other_mgr is manager:
                    continue
                for container in other_mgr.configuration.containers:
                    scan(container, other_name)

            del self.module_managers[module_name]
            del self.module_defs[module_name]

        # Format 8 bookkeeping: a removed module must not come back on reload, and its
        # baseline must not be written back as an orphan snapshot on save
        self.module_entries.pop(module_name, None)
        self.packages.pop(module_name, None)
        self.baselines.pop(module_name, None)
        self.unloaded_variant_overrides.pop(module_name, None)
    def find_references_to_module(self, module_name: str) -> List[tuple]:
        """Find all references in other modules pointing to this module."""
        references = []
        target_manager = self.module_managers.get(module_name)
        if not target_manager:
            return references

        target_containers = set()
        def collect_containers(container):
            target_containers.add(id(container))
            for sub in container.sub_containers:
                collect_containers(sub)

        for container in target_manager.configuration.containers:
            collect_containers(container)

        def scan_container(container, src_module, path):
            for ref_name, ref_val in container.reference_values.items():
                is_match = False
                if ref_val.is_resolved and ref_val.target is not None and id(ref_val.target) in target_containers:
                    is_match = True
                elif ref_val.value_ref and (ref_val.value_ref.startswith(f"/{module_name}/") or ref_val.value_ref == f"/{module_name}"):
                    is_match = True
                if is_match:
                    references.append((src_module, path, ref_name))

            for ref_name, ref_list in container.multi_reference_values.items():
                for ref_val in ref_list:
                    is_match = False
                    if ref_val.is_resolved and ref_val.target is not None and id(ref_val.target) in target_containers:
                        is_match = True
                    elif ref_val.value_ref and (ref_val.value_ref.startswith(f"/{module_name}/") or ref_val.value_ref == f"/{module_name}"):
                        is_match = True
                    if is_match:
                        references.append((src_module, f"{path}/{ref_name}[{ref_val.index}]", ref_name))

            for sub in container.sub_containers:
                scan_container(sub, src_module, sub.get_path())

        for other_name, other_mgr in self.module_managers.items():
            if other_name == module_name:
                continue
            for container in other_mgr.configuration.containers:
                scan_container(container, other_name, container.get_path())

        return references

    def get_manager(self, module_name: str) -> Optional[ConfigurationManager]:
        return self.module_managers.get(module_name)
        
    def get_all_managers(self) -> List[ConfigurationManager]:
        return list(self.module_managers.values())
    
    def get_instance_by_path(self, path: str) -> Optional['EcucContainerValue']:
        """Get container instance by its full path from any module
        
        EMF-style global resolver: enables cross-module reference resolution.
        Supports multiple path formats:
        - Module-aware paths: /Adc/AdcConfigSet
        - Legacy /Config paths: /Config/AdcConfigSet
        - EB Tresos paths: /Adc_Config/Adc/AdcConfigSet (config file prefix)
        """
        from .model.configuration_model import EcucContainerValue
        
        # 1. Try exact match (best for module-aware paths)
        for manager in self.module_managers.values():
            config = manager.configuration
            instance = config.get_instance_by_path(path)
            if instance is not None:
                return instance
        
        # 2. Fallback for legacy /Config/ paths
        if path.startswith("/Config/"):
            suffix = path[8:]  # Remove "/Config/"
            for module_name, manager in self.module_managers.items():
                alt_path = f"/{module_name}/{suffix}"
                instance = manager.configuration.get_instance_by_path(alt_path)
                if instance is not None:
                    return instance
        
        # 3. Fallback for EB Tresos paths: /ModuleName_Config/ModuleName/Container...
        # Pattern: /{prefix}/{module_name}/... where prefix ends with _Config
        parts = path.split('/')
        if len(parts) >= 3 and parts[0] == '':
            prefix = parts[1]  # e.g., "I2c_Config"
            module_name = parts[2]  # e.g., "I2c"
            
            # Check if it matches the EB pattern (prefix_Config/prefix/...)
            if prefix.endswith('_Config') or prefix.endswith('_Values'):
                # Try stripping the config file prefix
                suffix = '/'.join(parts[2:])  # e.g., "I2c/I2cGlobalConfig/I2cChannel_0"
                for mgr_name, manager in self.module_managers.items():
                    alt_path = f"/{suffix}"
                    instance = manager.configuration.get_instance_by_path(alt_path)
                    if instance is not None:
                        return instance
            
            # Also try if module_name matches a loaded module, search with remaining path
            if module_name in self.module_managers:
                # Try with just module_name + rest of path
                rest_path = '/' + '/'.join(parts[2:])  # e.g., "/I2c/I2cGlobalConfig/I2cChannel_0"
                instance = self.module_managers[module_name].configuration.get_instance_by_path(rest_path)
                if instance is not None:
                    return instance
        
        # 4. Module configuration root references: /ModuleName/ModuleName
        # Some references (e.g., /Iom/Iom) point to ECUC-MODULE-CONFIGURATION-VALUES
        # rather than a container. Create a synthetic container proxy so the
        # reference resolver can treat the module root as a valid target.
        if len(parts) == 3 and parts[0] == '':
            module_key = parts[1]  # e.g., "Iom"
            config_name = parts[2]  # e.g., "Iom"
            if module_key in self.module_managers:
                config = self.module_managers[module_key].configuration
                if config.short_name == config_name:
                    proxy = EcucContainerValue(
                        short_name=config_name,
                        definition_ref=config.definition_ref,
                    )
                    proxy.module_name = module_key
                    proxy.module_config = config
                    return proxy
        
        return None

    
    def resolve_all_references(self) -> tuple:
        """Resolve all cross-module references in all loaded configurations
        
        EMF-style reference resolution: converts string paths to object pointers
        across all modules in the project.
        
        Returns:
            Tuple of (total_resolved, total_errors)
        """
        total_resolved = 0
        total_errors = 0
        
        for manager in self.module_managers.values():
            resolved, errors = manager.configuration.resolve_references(self.get_instance_by_path)
            total_resolved += resolved
            total_errors += errors
        
        return total_resolved, total_errors
    
    def get_all_resolution_errors(self) -> list:
        """Get all resolution errors across all modules
        
        Returns:
            List of ResolutionError objects for UI/AI display
        """
        all_errors = []
        for manager in self.module_managers.values():
            all_errors.extend(manager.configuration.get_resolution_errors())
        return all_errors
    
    def build_reverse_reference_index(self) -> int:
        """Build reverse reference index: populate 'referenced_by' on each container
        
        For each resolved reference, add the reference to the target's 'referenced_by' list.
        This enables queries like "who references this container?"
        
        Must be called AFTER resolve_all_references().
        
        Returns:
            Number of reverse references indexed
        """
        indexed_count = 0
        
        # First, clear all existing referenced_by lists to avoid stale entries
        def clear_referenced_by(container):
            container.referenced_by.clear()
            for sub in container.sub_containers:
                clear_referenced_by(sub)
        
        for manager in self.module_managers.values():
            for container in manager.configuration.containers:
                clear_referenced_by(container)
        
        # Now build fresh index
        def process_container(container):
            nonlocal indexed_count
            
            for ref_name, ref_value in container.reference_values.items():
                # Only process resolved references with valid target
                if ref_value.is_resolved and ref_value.target is not None:
                    # Add this reference to the target's referenced_by list
                    if ref_value not in ref_value.target.referenced_by:
                        ref_value.target.referenced_by.append(ref_value)
                        indexed_count += 1

            # Multi-valued references
            for ref_name, ref_list in container.multi_reference_values.items():
                for ref_value in ref_list:
                    if ref_value.is_resolved and ref_value.target is not None:
                        if ref_value not in ref_value.target.referenced_by:
                            ref_value.target.referenced_by.append(ref_value)
                            indexed_count += 1

            # Recurse into sub-containers
            for sub in container.sub_containers:
                process_container(sub)
        
        # Process all containers in all modules
        for manager in self.module_managers.values():
            for container in manager.configuration.containers:
                process_container(container)
        
        return indexed_count

    def find_global_references_to(self, target_container: 'EcucContainerValue') -> List[tuple]:
        """Find all references pointing to a specific container across ALL modules
        
        Args:
            target_container: Container to search references for
            
        Returns:
            List of tuples (source_container, reference_name)
        """
        target_path = target_container.get_path()
        references = []
        
        from .rules.reference_rules import ReferenceIntegrityRule
        for manager in self.module_managers.values():
            refs = ReferenceIntegrityRule.find_references_to(target_container, manager.configuration)
            references.extend(refs)
            
        return references



    def register_container_references(self, container: 'EcucContainerValue'):
        """Recursively register all references in a container tree to their targets' referenced_by list"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.is_resolved and ref_value.target is not None:
                if ref_value not in ref_value.target.referenced_by:
                    ref_value.target.referenced_by.append(ref_value)

        for ref_name, ref_list in container.multi_reference_values.items():
            for ref_value in ref_list:
                if ref_value.is_resolved and ref_value.target is not None:
                    if ref_value not in ref_value.target.referenced_by:
                        ref_value.target.referenced_by.append(ref_value)

        for sub in container.sub_containers:
            self.register_container_references(sub)

    def unregister_container_references(self, container: 'EcucContainerValue'):
        """Recursively remove all references in a container tree from their targets' referenced_by list"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.is_resolved and ref_value.target is not None:
                if ref_value in ref_value.target.referenced_by:
                    ref_value.target.referenced_by.remove(ref_value)

        for ref_name, ref_list in container.multi_reference_values.items():
            for ref_value in ref_list:
                if ref_value.is_resolved and ref_value.target is not None:
                    if ref_value in ref_value.target.referenced_by:
                        ref_value.target.referenced_by.remove(ref_value)

        for sub in container.sub_containers:
            self.unregister_container_references(sub)


class WorkspaceManager:
    """Manages the active project and workspace operations"""
    
    def __init__(self):
        self.current_project: Optional[WorkspaceProject] = None
        self.def_parser = EcucDefParser()
        
    def create_project(self, name: str, path: Path, format_version: int = 8) -> WorkspaceProject:
        """Create a new empty project (format 8 by default; legacy projects use format 7)"""
        self.current_project = WorkspaceProject(name, path, format_version=format_version)
        # Format 8 projects get default directories
        if format_version == 8:
            self.current_project.directories = ProjectDirectories.default_v8()
        return self.current_project
        
    def close_project(self):
        """Close current project"""
        self.current_project = None

    def export_epc(self, output_dir: Path, module_name: Optional[str] = None,
                   skip: Optional[set] = None) -> List[Path]:
        """Export module configuration(s) as EB Tresos-compatible .epc files.

        Args:
            output_dir: Directory to write {Module}.epc files into
            module_name: Export only this module; None exports all modules
            skip: id() of configuration objects to leave out (items whose
                definition ENABLE condition is false; computed by the caller)

        Returns:
            List of written file paths (sorted by module name)
        """
        from .serializer.ecuc_serializer import EcucValueSerializer

        if not self.current_project:
            raise ValueError("No project loaded")

        managers = self.current_project.module_managers
        if module_name is not None:
            if module_name not in managers:
                raise ValueError(f"Module '{module_name}' not found in project")
            selected = {module_name: managers[module_name]}
        else:
            selected = managers

        output_dir = Path(output_dir)
        output_dir.mkdir(parents=True, exist_ok=True)

        serializer = EcucValueSerializer()
        written = []
        for name in sorted(selected):
            epc_path = output_dir / f"{name}.epc"
            serializer.export_epc(selected[name].configuration, epc_path, skip=skip)
            written.append(epc_path)
        return written
        
    def save_project(self):
        """Save current project to file (format 7 for legacy projects, format 8 for new)"""
        if not self.current_project or not self.current_project.path:
            return

        from datetime import datetime

        # Determine format version: use existing format or default to 8 for new projects
        format_version = getattr(self.current_project, 'format_version', 8)

        # Store eb_source_root relative to the project root when it lies
        # inside it (portability); keep absolute otherwise (link mode with an
        # external EB tree).
        eb_source_root_str = None
        if self.current_project.eb_source_root:
            eb_root = Path(self.current_project.eb_source_root)
            try:
                eb_source_root_str = str(eb_root.relative_to(self.current_project.path.parent))
            except ValueError:
                eb_source_root_str = str(eb_root)

        project_dir = self.current_project.path.parent
        config_dir = project_paths.resolve(self.current_project, "config")
        config_dir.mkdir(parents=True, exist_ok=True)

        if format_version >= 8:
            # Format 8: new structure with directories, module_libraries, and module_entries
            data = self._save_project_v8(format_version, eb_source_root_str, project_dir, config_dir, datetime)
        else:
            # Format 7: legacy structure with def_path and provenance
            data = self._save_project_v7(eb_source_root_str, project_dir, config_dir, datetime)

        # Write project file
        with open(self.current_project.path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)

        # Copy EB templates (generate_PB) to project save directory.
        # Link mode never copies: templates/{Module} are symlinks into the
        # original EB tree, created at import time.
        if self.current_project.eb_source_root and self.current_project.import_mode == "copy":
            self._copy_eb_templates(project_dir)

    def _save_project_v7(self, eb_source_root_str, project_dir: Path, config_dir: Path, datetime_module) -> Dict[str, Any]:
        """Save project in format 7 (legacy, with def_path and per-module provenance)."""
        data = {
            "format_version": 7,  # v7: import_mode + per-module provenance
            "tool_version": "1.0.0",
            "project_type": self.current_project.project_type.value,
            "name": self.current_project.name,
            "created": self.current_project.created_date,
            "last_modified": datetime_module.now().isoformat(),
            "author": getattr(self.current_project, 'author', ''),
            "description": getattr(self.current_project, 'description', ''),
            "version": getattr(self.current_project, 'version', '1.0.0'),
            "def_search_paths": [str(p) for p in self.current_project.def_search_paths],
            "variants": self.current_project.variants,
            "active_variant": self.current_project.active_variant,
            "dependency_rules": self.current_project.dependency_rules,
            "available_chips": self.current_project.available_chips,
            "selected_chip": self.current_project.selected_chip,
            "chip_data": self.current_project.chip_data_record or self.current_project.record_chip_data(),
            "eb_source_root": eb_source_root_str,
            "import_mode": self.current_project.import_mode,
            "chip_scan_dirs": list(self.current_project.chip_scan_dirs),
            "chip_scan_keywords": list(self.current_project.chip_scan_keywords),
            "memmap_source_dirs": list(self.current_project.memmap_source_dirs),
            "memmap_header_dirs": list(self.current_project.memmap_header_dirs),
            "memmap_linker_file": self.current_project.memmap_linker_file,
            "modules": []
        }

        # Save each module (v7 format)
        for name, manager in self.current_project.module_managers.items():
            def_path = self.current_project.module_defs[name]
            config_path = project_paths.config_file(self.current_project, name)
            config_path.parent.mkdir(parents=True, exist_ok=True)
            relative_config_path = str(config_path.relative_to(project_dir))

            manager.save_configuration(config_path)

            try:
                save_def_path = str(def_path.relative_to(project_dir))
            except (ValueError, AttributeError):
                save_def_path = str(def_path)

            provenance = self.current_project.module_provenance.get(name, {})
            data["modules"].append({
                "name": name,
                "def_path": save_def_path,
                "config_path": relative_config_path,
                "variant_overrides": manager.configuration.variant_overrides,
                "origin": provenance.get("origin", "native"),
                "source_epc": provenance.get("source_epc"),
                "imported_at": provenance.get("imported_at"),
            })

        return data

    def _save_project_v8(self, format_version: int, eb_source_root_str, project_dir: Path, config_dir: Path, datetime_module) -> Dict[str, Any]:
        """Save project in format 8 (new structure with directories, libraries, and module_entries)."""
        # Ensure directories are set for format 8
        if self.current_project.directories is None:
            self.current_project.directories = ProjectDirectories.default_v8()

        data = {
            "format_version": format_version,
            "tool_version": "1.0.0",
            "project_type": self.current_project.project_type.value,
            "name": self.current_project.name,
            "created": self.current_project.created_date,
            "last_modified": datetime_module.now().isoformat(),
            "author": getattr(self.current_project, 'author', ''),
            "description": getattr(self.current_project, 'description', ''),
            "version": getattr(self.current_project, 'version', '1.0.0'),
            "def_search_paths": [str(p) for p in self.current_project.def_search_paths],
            "variants": self.current_project.variants,
            "active_variant": self.current_project.active_variant,
            "dependency_rules": self.current_project.dependency_rules,
            "available_chips": self.current_project.available_chips,
            "selected_chip": self.current_project.selected_chip,
            "chip_data": self.current_project.chip_data_record or self.current_project.record_chip_data(),
            "eb_source_root": eb_source_root_str,
            "import_mode": self.current_project.import_mode,
            "chip_scan_dirs": list(self.current_project.chip_scan_dirs),
            "chip_scan_keywords": list(self.current_project.chip_scan_keywords),
            "memmap_source_dirs": list(self.current_project.memmap_source_dirs),
            "memmap_header_dirs": list(self.current_project.memmap_header_dirs),
            "memmap_linker_file": self.current_project.memmap_linker_file,
            # Format 8 fields
            "directories": self.current_project.directories.to_dict(),
            "module_libraries": [lib.to_dict() for lib in self.current_project.module_libraries],
            "modules": []
        }

        # Save each module (v8 format: module_entries), sorted by name for a
        # deterministic file.  Modules with a manager write their configuration;
        # entries without one (failed to load) are written back unchanged and their
        # configuration files are left untouched.
        project = self.current_project
        modules_out: Dict[str, Dict[str, Any]] = {}
        for name, manager in sorted(project.module_managers.items()):
            config_path = project_paths.config_file(project, name)
            config_path.parent.mkdir(parents=True, exist_ok=True)
            relative_config_path = self._to_posix_path(config_path, project_dir, inside_only=False)

            manager.save_configuration(config_path)

            # Create or use existing module entry
            if name in project.module_entries:
                entry = project.module_entries[name]
                entry.config_path = relative_config_path
            else:
                entry = ModuleEntry(
                    name=name,
                    definition=f"/AUTOSAR/EcucDefs/{name}",  # Default; caller should override
                    library=0,  # Default; caller should set
                    config_path=relative_config_path,
                    pre_unlocked=[],
                    package_record={},
                    base_hash=None,
                )

            module_data = entry.to_dict()
            module_data["variant_overrides"] = manager.configuration.variant_overrides
            modules_out[name] = module_data

        for name, entry in project.module_entries.items():
            if name not in modules_out:
                module_data = entry.to_dict()
                if name in project.unloaded_variant_overrides:
                    module_data["variant_overrides"] = project.unloaded_variant_overrides[name]
                modules_out[name] = module_data

        data["modules"] = [modules_out[name] for name in sorted(modules_out)]

        # Baseline snapshots the session accepted (a merge applied on load, a module added)
        # are written after the configuration files, so both describe the same state. A
        # clean baseline is already on disk and is left untouched. A baseline whose module
        # has no entry in the project file is skipped: writing it would leave a snapshot
        # whose hash nobody records.
        for name in sorted(project.baselines):
            baseline = project.baselines[name]
            entry = project.module_entries.get(name)
            if not baseline.dirty or baseline.base_config is None:
                continue
            if entry is None or name not in modules_out:
                _log_warning("基线没有对应的模块条目，跳过快照写入：%s", name)
                continue
            try:
                digest = baseline_session.write_baseline(project, name, baseline)
            except OSError as exc:
                # One unwritable snapshot must not cost the project file: the module keeps
                # the hash it had, its baseline stays dirty for the next save.
                _log_warning("基线快照写入失败，保留原记录：%s（%s）", name, exc)
                continue
            entry.base_hash = digest
            modules_out[name]["base_hash"] = digest
        return data

    def _to_posix_path(self, path: Path, project_dir: Path, inside_only: bool = False) -> str:
        """Convert path to POSIX string, relative if inside project, absolute if outside.

        Args:
            path: The path to convert.
            project_dir: The project root directory.
            inside_only: If True, always try to make relative; if False, use absolute for outside paths.

        Returns:
            POSIX-style path string with only forward slashes.
        """
        try:
            rel = path.relative_to(project_dir)
            return str(rel).replace("\\", "/")
        except ValueError:
            # Path is outside project directory
            if inside_only:
                return str(path).replace("\\", "/")
            else:
                return str(path.resolve()).replace("\\", "/")

    def _copy_eb_templates(self, project_dir: Path):
        """Copy EB Tresos generate_PB templates to project save directory

        For each loaded module, find the generate_PB directory from the EB plugin
        (derived from the module's def_path) and copy its contents to:
            {project_dir}/templates/{ModuleName}/

        The generator searches project_template_dir/{ModuleName}/ for templates,
        so this makes the EB templates available for code generation.
        """
        templates_dir = project_dir / project_paths.dirs(self.current_project).templates
        copied_count = 0

        for name, def_path in self.current_project.module_defs.items():
            # Derive EB plugin directory from def_path
            # def_path = .../Adc_THA6_AS440/config/Adc.xdm → plugin_dir = .../Adc_THA6_AS440
            plugin_dir = def_path.parent.parent

            # Look for generate_PB directory
            generate_pb_dir = plugin_dir / "generate_PB"
            if not generate_pb_dir.exists():
                continue

            # Target: templates/{ModuleName}/
            target_dir = templates_dir / name

            # Copy entire generate_PB contents to target
            # Use shutil.copytree with dirs_exist_ok=True to overwrite
            try:
                shutil.copytree(generate_pb_dir, target_dir, dirs_exist_ok=True)
                copied_count += 1
            except Exception as e:
                import logging
                logging.getLogger(__name__).warning(
                    "Failed to copy template directory %s -> %s: %s",
                    generate_pb_dir, target_dir, e, exc_info=True,
                )

    def _resolve_path(self, path_str: str, project_dir: Path) -> Path:
        """Robustly resolve paths that might be relative or absolute from another platform.

        The Windows-anchor guessing below is a LEGACY fallback only: projects
        saved with format v7 store all paths relative to the project root (and
        eb_source_root relative when inside it), so this code only triggers for
        old project files carrying absolute paths from another machine.
        """
        import re
        
        # 1. Normalize separators
        norm_str = path_str.replace('\\', '/')
        
        # 2. Check for Windows absolute path (e.g., C:/...) ON NON-WINDOWS
        # If it's a Windows-style absolute path but we are on a system where it's not absolute
        if re.match(r'^[a-zA-Z]:/', norm_str):
            parts = norm_str.split('/')
            
            # Try to resolve relative to current project root
            # Look for common anchor points: project name or standard BSW folders
            project_name = project_dir.name
            anchors = [project_name, 'Def', 'plugins', 'ConfigValue', 'autosar']
            
            for anchor in anchors:
                if anchor in parts:
                    idx = parts.index(anchor)
                    # For project_name, use everything AFTER it
                    # For others, use everything FROM it (inclusive)
                    rel_parts = parts[idx+1:] if anchor == project_name else parts[idx:]
                    potential_path = project_dir.joinpath(*rel_parts)
                    if potential_path.exists():
                        return potential_path
            
            # If no anchor found or file doesn't exist, just return it as a Path object
            # It will likely fail exists() check later, allowing it to be handled gracefully
            return Path(norm_str)
            
        # 3. Handle normal paths (both absolute and relative)
        p = Path(norm_str)
        if p.is_absolute():
            return p
        return project_dir / p

    def load_project(self, project_path: Path, confirm=None) -> tuple[WorkspaceProject, list]:
        """Load project from file (format ≤8)

        A format 8 project reconciles every module's baseline while loading (design §6.5,
        step ④): Base' is composed from the module package and merged into the saved
        configuration, and the merge is applied only when ``confirm(markdown, result)``
        returns True. Format ≤7 projects never reconcile. With ``confirm=None`` every merge
        is treated as rejected — nothing is written, and the results are only computed.

        Args:
            project_path: The ``.dpa`` file.
            confirm: Optional ``(preview_text, MergeResult) -> bool`` shown before a merge
                that changes Active.

        Returns:
            tuple: (project, failed_modules list)
            failed_modules: List of tuples (module_name, error_message)
        """
        with open(project_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        # Check format version (Current max version is 8)
        format_version = data.get("format_version", 0)
        if format_version > 8:
            raise ValueError(
                f"Unsupported project format version {format_version}. "
                f"Please upgrade the tool."
            )

        project_name = data.get("name", "Untitled")
        project = WorkspaceProject(project_name, project_path, format_version=format_version)
        
        # Store metadata
        from datetime import datetime
        from .config_manager import ProjectType

        project.created_date = data.get("created", datetime.now().isoformat())
        project.author = data.get("author", "")
        project.description = data.get("description", "")
        project.version = data.get("version", "1.0.0")

        # Load project type (new in format v2)
        project_type_str = data.get("project_type", "Vector DaVinci")
        for pt in ProjectType:
            if pt.value == project_type_str:
                project.project_type = pt
                break

        # Load def search paths
        project.def_search_paths = [Path(p) for p in data.get("def_search_paths", [])]

        # Load format 8 fields (directories, module_libraries)
        if format_version >= 8:
            dirs_data = data.get("directories")
            if dirs_data:
                project.directories = ProjectDirectories.from_dict(dirs_data, ProjectDirectories.default_v8())
            else:
                project.directories = ProjectDirectories.default_v8()

            # Load module libraries
            for lib_data in data.get("module_libraries", []):
                project.module_libraries.append(LibraryRef.from_dict(lib_data))

        # Load variants with backward compatibility
        loaded_variants = data.get("variants", [])
        loaded_active = data.get("active_variant", None)

        # Migrate old projects: ensure Default variant exists
        if not loaded_variants:
            # Old project with no variants - create Default
            project.variants = ["Default"]
            project.active_variant = "Default"
        elif "Base" in loaded_variants and "Default" not in loaded_variants:
            # Old project with Base - rename Base to Default
            project.variants = ["Default" if v == "Base" else v for v in loaded_variants]
            project.active_variant = "Default" if loaded_active == "Base" else (loaded_active or "Default")
        else:
            project.variants = loaded_variants if "Default" in loaded_variants else ["Default"] + loaded_variants
            project.active_variant = loaded_active or "Default"

        # Ignore has_base from old projects (no longer used)
        # data.get("has_base", False) - deprecated

        # Load dependency rules (new in format v4)
        project.dependency_rules = data.get("dependency_rules", [])

        # Load chip selection (new in format v7)
        project.available_chips = data.get("available_chips", [])
        project.selected_chip = data.get("selected_chip", None)
        project.chip_data_record = data.get("chip_data") or None
        project.chip_scan_dirs = list(data.get("chip_scan_dirs") or [])
        project.chip_scan_keywords = list(data.get("chip_scan_keywords") or [])
        project.memmap_source_dirs = list(data.get("memmap_source_dirs") or [])
        project.memmap_header_dirs = list(data.get("memmap_header_dirs") or [])
        project.memmap_linker_file = data.get("memmap_linker_file") or None

        # Load EB source root (for imported EB projects).
        # Saved relative to the project root when inside it (v7); older
        # projects may have absolute paths.
        eb_root = data.get("eb_source_root")
        if eb_root:
            eb_root_path = Path(eb_root)
            if not eb_root_path.is_absolute():
                eb_root_path = project_path.parent / eb_root_path
            project.eb_source_root = eb_root_path

        # Load import mode (v7); older projects were always self-contained copies
        project.import_mode = data.get("import_mode", "copy")

        # Link mode: the project depends on the original EB tree — fail early
        # with a clear message instead of per-module load errors.
        if project.import_mode == "link" and project.eb_source_root \
                and not project.eb_source_root.exists():
            tresos_path = os.environ.get("TRESOS_PLUGINS_PATH", "")
            if not (tresos_path and Path(tresos_path).exists()):
                raise ValueError(
                    f"EB source tree not found: {project.eb_source_root}\n"
                    f"This project was imported in link mode and references the "
                    f"original EB Tresos tree. Restore it at that path, or set "
                    f"TRESOS_PLUGINS_PATH to the plugins directory."
                )
            # Repair the Def/plugins symlink to point at TRESOS_PLUGINS_PATH
            plugins_link = project_paths.legacy_plugins_dir(project_path.parent)
            if plugins_link.is_symlink() and not plugins_link.exists():
                plugins_link.unlink()
                os.symlink(Path(tresos_path), plugins_link, target_is_directory=True)
                import logging
                logging.getLogger(__name__).warning(
                    "Relinked Def/plugins to TRESOS_PLUGINS_PATH: %s", tresos_path)

        # If no available chips in file, try to discover them
        if not project.available_chips:
            project.path = project_path  # Ensure path is set before discovery
            project.discover_available_chips()


        project_dir = project_path.parent
        failed_modules = []

        # Load modules: format 8 uses module_entries, earlier formats use def_path
        if format_version >= 8:
            self._load_v8_modules(project, data, project_dir, failed_modules, confirm)
        else:
            # Format ≤7: Load with def_path (existing logic)
            for module_data in data.get("modules", []):
                name = module_data["name"]
                def_path_str = module_data["def_path"]
                config_path_str = module_data["config_path"]

                # Provenance (v7; older projects default to native).
                # Projects saved on Windows before the POSIX fix stored backslashes.
                source_epc = module_data.get("source_epc")
                if isinstance(source_epc, str):
                    source_epc = source_epc.replace("\\", "/")
                project.module_provenance[name] = {
                    "origin": module_data.get("origin", "native"),
                    "source_epc": source_epc,
                    "imported_at": module_data.get("imported_at"),
                }

                # Resolve paths robustly (handles cross-platform absolute paths)
                def_path = self._resolve_path(def_path_str, project_dir)
                config_path = self._resolve_path(config_path_str, project_dir)

                # Fallback for legacy projects (files in project root)
                # Check for both / and \ for cross-platform compatibility
                has_separator = "/" in config_path_str or "\\" in config_path_str
                if not config_path.exists() and not has_separator:
                    legacy_path = project_dir / Path(config_path_str).name
                    if legacy_path.exists():
                        config_path = legacy_path

                # Extended fallback: if ConfigValue is missing but file is in root
                # Check for both ConfigValue/ and ConfigValue\ for cross-platform compatibility
                elif not config_path.exists() and ("ConfigValue/" in config_path_str or "ConfigValue\\" in config_path_str):
                    legacy_path = project_dir / Path(config_path_str).name
                    if legacy_path.exists():
                        config_path = legacy_path


                if def_path.exists():
                    try:
                        # Load definition (selector enumerations include the project's own chips)
                        self.def_parser.set_selector_values(_chip_selector_values(project))
                        module_def = self.def_parser.parse_module_def_file(def_path)

                        # Create manager
                        manager = project.add_module(module_def, def_path)

                        # Load configuration if exists
                        if config_path.exists():
                            manager.load_configuration(config_path)

                        # Restore variant overrides if saved
                        if "variant_overrides" in module_data:
                            manager.configuration.variant_overrides = module_data["variant_overrides"]

                    except Exception as e:
                        error_msg = f"Failed to load: {str(e)}"
                        failed_modules.append((name, error_msg))

                else:
                    # Stub load: Create a surrogate module definition so we can still see the values
                    try:
                        from .model.definition_model import EcucModuleDef
                        # Try to infer correct definition_ref if possible, or use standard pattern
                        module_def = EcucModuleDef(
                            short_name=name,
                            definition_ref=f"/__STUB__/AUTOSAR/EcucDefs/{name}"
                        )

                        # Create manager with def_missing=True
                        manager = project.add_module(module_def, def_path, def_missing=True)

                        # Load configuration if exists (skip cleanup since def is a stub)
                        if config_path.exists():
                            manager.load_configuration(config_path, skip_cleanup=True)

                        # Restore variant overrides if saved
                        if "variant_overrides" in module_data:
                            manager.configuration.variant_overrides = module_data["variant_overrides"]



                    except Exception as e:
                        error_msg = f"Failed to load stub: {str(e)}"
                        failed_modules.append((name, error_msg))

        project.default_override_conflicts = project.fold_default_overrides()
        if project.default_override_conflicts:
            import logging
            log = logging.getLogger(__name__)
            for module_name, path, override, base in project.default_override_conflicts:
                log.warning("Default override dropped, base value kept: %s %s override=%r base=%r",
                            module_name, path, override, base)

        # EMF-style reference resolution: resolve cross-module references
        try:
            resolved_count, error_count = project.resolve_all_references()
            # Build reverse reference index for "who references me?" queries
            reverse_count = project.build_reverse_reference_index()
        except Exception as e:
            import logging
            logging.getLogger(__name__).warning(
                f"Reference resolution failed during project load: {e}", exc_info=True
            )
        # Load ECU resources from .properties files (if Def/plugins/ exists)
        ecu_res = project.load_ecu_resources()

        self.current_project = project
        return project, failed_modules

    def _load_v8_modules(self, project: WorkspaceProject, data: Dict[str, Any],
                         project_dir: Path, failed_modules: list,
                         confirm=None) -> None:
        """Load the ``modules`` of a format 8 project through its module libraries.

        Every entry is kept in ``module_entries`` (so saving does not drop it).  A module
        whose definition no library provides, or whose package is inconsistent, is
        reported in ``failed_modules`` as (name, reason) instead of raising.
        """
        modules_data = data.get("modules", [])
        entries = [ModuleEntry.from_dict(m) for m in modules_data]
        raw_overrides = {
            m.get("name", ""): m["variant_overrides"]
            for m in modules_data if "variant_overrides" in m
        }
        for entry in entries:
            project.module_entries[entry.name] = entry
            project.module_provenance[entry.name] = {
                "origin": "native",
                "source_epc": None,
                "imported_at": None,
            }
        if not entries:
            return

        def fail(name: str, reason: str) -> None:
            # Keep the entry and its raw overrides; drop any manager so a save leaves
            # the module's configuration file untouched
            failed_modules.append((name, reason))
            project.module_managers.pop(name, None)
            project.module_defs.pop(name, None)
            project.packages.pop(name, None)
            if name in raw_overrides:
                project.unloaded_variant_overrides[name] = raw_overrides[name]

        libraries = scan_libraries(project)
        for entry in entries:
            try:
                index, pkg = find_package(libraries, entry.definition)
                # Also loads the entry's configuration file when it exists. The snapshot is
                # not written here, and no merge happens here either: the entry-driven
                # reconcile below is the one that sees the saved Base and the confirm.
                manager = project.add_module_from_package(pkg, index, persist=False,
                                                          reconcile=False)
            except Exception as exc:  # noqa: BLE001 - package, definition and configuration errors: one module must not abort the project
                fail(entry.name, f"Failed to load: {exc}")
                continue

            if entry.name in raw_overrides:
                manager.configuration.variant_overrides = raw_overrides[entry.name]

            try:
                project.reconcile_baseline(manager, entry, pkg, confirm)
            except Exception as exc:  # noqa: BLE001 - a failed baseline must never abort the project
                # MergeApplyError means Active would be left half-merged; a package, parse
                # or serialiser error means the baseline cannot be computed at all. Either
                # way one module is reported and the rest of the project loads.
                fail(entry.name, f"Baseline merge failed: {exc}")

    def import_eb_project(self, project_root: Path, chip_name: Optional[str] = None,
                          target_dir: Optional[Path] = None,
                          progress_callback=None,
                          mode: str = "copy") -> tuple:
        """Batch import an EB Tresos project: auto-discover defines + EPC configs

        Import modes:
        - "copy" (default): the plugin directory tree (including
          ``resource/*.properties``) and ``generate_PB`` templates are copied
          into the project, making it fully self-contained.
        - "link": nothing is copied — ``Def/plugins`` and ``templates/{Module}``
          are created as symlinks into the original EB tree, so definitions,
          resources and templates always reflect the source. The project then
          depends on the EB tree remaining available.

        Args:
            project_root: Root directory of the source EB project
            chip_name: Optional chip name to select Config/{chip}/output/*.epc
            target_dir: Optional target directory for the new project.
                        If None, the project is created inside *project_root*.
            progress_callback: Optional callable(message: str) for progress updates
            mode: "copy" (self-contained) or "link" (reference original tree)

        Returns:
            tuple: (project, loaded_modules, failed_modules)
            loaded_modules: List of successfully loaded module names
            failed_modules: List of tuples (module_name, error_message)
        """
        from datetime import datetime
        from .config_manager import EpcFileScanner, ProjectType

        if mode not in ("copy", "link"):
            raise ValueError(f"Unknown import mode: {mode!r} (expected 'copy' or 'link')")

        def _progress(msg):
            if progress_callback:
                progress_callback(msg)


        # Determine where the project will live
        project_dir = target_dir if target_dir else project_root
        project_name = project_dir.name
        project = WorkspaceProject(project_name, project_dir / f"{project_name}.dpa")
        project.project_type = ProjectType.EB_TRESOS
        project.import_mode = mode

        loaded_modules = []
        failed_modules = []

        # If the user selected a chip (or passed a subfolder), we should append it to project_root
        if chip_name and (project_root / chip_name).exists():
            project_root = project_root / chip_name

        # Step 1: Scan for define files (.xdm and .arxml) in EB plugin structure
        _progress("Scanning for module definitions...")
        define_map = {}  # module_name -> def_path

        # Primary: Define/EbPlugins/eclipse/*/config/*.xdm (or Def/)
        eb_plugins_dir = project_root / "Define" / "EbPlugins" / "eclipse"
        if not eb_plugins_dir.is_dir():
            eb_plugins_dir = project_paths.legacy_plugins_dir(project_root)  # EB source tree

        if eb_plugins_dir.is_dir():
            for module_dir in sorted(eb_plugins_dir.iterdir()):
                if not module_dir.is_dir():
                    continue
                # Search config/ for .xdm files (primary define format)
                config_dir = module_dir / "config"
                if config_dir.exists():
                    for def_file in config_dir.glob("*.xdm"):
                        module_name = def_file.stem
                        # Skip supplementary config files (not real module definitions)
                        if module_name.endswith("PreConfiguration") or module_name.endswith("_Pre"):
                            continue
                        if module_name not in define_map:
                            define_map[module_name] = def_file
                # Also search autosar/ for .arxml define files (chip-specific defines)
                autosar_dir = module_dir / "autosar"
                if autosar_dir.exists():
                    for def_file in autosar_dir.glob("*.arxml"):
                        # arxml defines often have chip suffix, extract base module name
                        # e.g., Can_THA6206_LFBGA292.arxml → base "Can"
                        module_name = def_file.stem
                        base_name = module_name.split('_')[0] if '_' in module_name else module_name
                        # Only use arxml as fallback if no xdm for this module (case-insensitive)
                        existing_keys_lower = {k.lower() for k in define_map}
                        if base_name.lower() not in existing_keys_lower:
                            define_map[base_name] = def_file

        # Fallback: search more broadly in Define/ or Def/ for both .xdm and .arxml
        if not define_map:
            for define_dir_name in ["Define", "Def"]:
                define_dir = project_root / define_dir_name
                if define_dir.exists():
                    for ext in ("*.xdm", "*.arxml"):
                        for def_file in define_dir.rglob(ext):
                            module_name = def_file.stem
                            # Filter out config/rec files
                            if module_name.endswith("_Config") or module_name.endswith("_rec"):
                                continue
                            if module_name not in define_map:
                                define_map[module_name] = def_file
                    if define_map:
                        break

        _progress(f"Found {len(define_map)} module definition(s)")

        # ------------------------------------------------------------------
        # Step 1.5: Materialize plugins under project_dir/Def/plugins/
        #   copy mode: copy each plugin directory (self-contained project)
        #   link mode: one symlink Def/plugins -> source plugins dir; all
        #              downstream code (def loading, resource scan, template
        #              lookup) works unchanged through the link
        # ------------------------------------------------------------------
        plugins_target = project_paths.resolve(project, "legacy_plugins")

        # Common source root of all plugins (define_map paths sit at
        # {plugins_root}/{PluginName}/(config|autosar)/File)
        plugin_roots = {p.parent.parent.parent for p in define_map.values()}
        plugins_source = plugin_roots.pop() if len(plugin_roots) == 1 else None

        if not define_map:
            pass  # EPC-only import (stub modules): nothing to copy or link
        elif mode == "link":
            _progress("Linking plugin directory...")
            if plugins_source is None:
                raise ValueError(
                    "Link-mode import requires all plugins under one directory; "
                    f"found several roots for {sorted(define_map)}"
                )
            if plugins_target.resolve() != plugins_source.resolve():
                plugins_target.parent.mkdir(parents=True, exist_ok=True)
                if plugins_target.is_symlink() or plugins_target.exists():
                    raise ValueError(
                        f"Cannot link plugins: {plugins_target} already exists. "
                        f"Remove it or import in copy mode."
                    )
                os.symlink(plugins_source, plugins_target, target_is_directory=True)
                _progress(f"  Def/plugins -> {plugins_source}")
        else:
            plugins_target.mkdir(parents=True, exist_ok=True)
            copied_plugins: set[str] = set()

            _progress("Copying plugin directories...")

            for module_name, def_path in list(define_map.items()):
                # def_path is typically .../PluginName/config/Module.xdm
                # or .../PluginName/autosar/Module.arxml
                plugin_dir = def_path.parent.parent
                plugin_name = plugin_dir.name
                target_plugin = plugins_target / plugin_name

                # Copy entire plugin directory (config/, resource/, autosar/,
                # generate_PB/, etc.) if not already done and source != target
                if plugin_name not in copied_plugins and plugin_dir.is_dir():
                    if plugin_dir.resolve() != target_plugin.resolve():
                        try:
                            shutil.copytree(plugin_dir, target_plugin, dirs_exist_ok=True)
                            _progress(f"  Copied {plugin_name}")
                        except Exception as e:
                            _progress(f"  Warning: Failed to copy {plugin_name}: {e}")
                    copied_plugins.add(plugin_name)

            _progress(f"Copied {len(copied_plugins)} plugin directory(ies) to Def/plugins/")

        # Remap define_map entries into Def/plugins/ (works for both modes:
        # real copies or paths through the symlink)
        if plugins_source is not None or mode == "copy":
            for module_name, def_path in list(define_map.items()):
                plugin_dir = def_path.parent.parent
                try:
                    relative = def_path.relative_to(plugin_dir)
                    new_path = plugins_target / plugin_dir.name / relative
                    if new_path.exists():
                        define_map[module_name] = new_path
                except ValueError:
                    pass  # keep original path if remapping fails

        # Step 2: Scan for EPC configuration files
        _progress("Scanning for EPC configuration files...")
        epc_map = EpcFileScanner.find_epc_files(project_root, chip_name)
        _progress(f"Found {len(epc_map)} EPC configuration file(s)")

        # Step 2.5: A single value file may bundle several module
        # configurations — register every contained module, not just the
        # one matching the filename stem.
        for epc_path in sorted(set(epc_map.values())):
            for contained in EpcFileScanner.list_module_names(epc_path):
                if contained not in epc_map:
                    epc_map[contained] = epc_path
                    _progress(f"  Found bundled module '{contained}' in {epc_path.name}")

        # Step 3: Match defines with EPCs by module name
        all_modules = set(define_map.keys())
        epc_only = set(epc_map.keys()) - all_modules
        
        # Add epc_only modules to all_modules so we process them as stubs
        if epc_only:
            for name in sorted(epc_only):
                msg = f"EPC found but no matching define: {name}. Will load as stub module."
                _progress(f"Notice: {msg}")
                all_modules.add(name)

        # Step 4: Load each module
        total = len(all_modules)
        for idx, module_name in enumerate(sorted(all_modules), 1):
            def_path = define_map.get(module_name)
            epc_path = epc_map.get(module_name)

            status = f"({idx}/{total}) Loading {module_name}..."
            if epc_path:
                status += f" + EPC"
            _progress(status)

            try:
                actual_name = module_name
                if def_path:
                    # Parse definition (selector enumerations include the project's own chips)
                    self.def_parser.set_selector_values(_chip_selector_values(project))
                    module_def = self.def_parser.parse_module_def_file(def_path)
                    actual_name = module_def.short_name
    
                    # Check if module already loaded (e.g., EcuC.xdm and Ecuc.arxml both define "EcuC")
                    if actual_name in project.module_managers:
                        _progress(f"  Skipped {module_name}: module '{actual_name}' already loaded")
                        continue
    
                    # Add to project
                    manager = project.add_module(module_def, def_path)
                else:
                    # Stub load: Create a surrogate module definition
                    from .model.definition_model import EcucModuleDef
                    module_def = EcucModuleDef(
                        short_name=module_name, 
                        definition_ref=f"/__STUB__/AUTOSAR/EcucDefs/{module_name}"
                    )
                    
                    if actual_name in project.module_managers:
                        _progress(f"  Skipped {module_name}: module '{actual_name}' already loaded")
                        continue
                        
                    # Create manager with def_missing=True
                    manager = project.add_module(module_def, Path(f"stub_{module_name}.xdm"), def_missing=True)

                # Load EPC configuration if available
                # Also try matching by parsed short_name if filename didn't match
                actual_epc = epc_path
                if not actual_epc and actual_name != module_name:
                    actual_epc = epc_map.get(actual_name)
                if actual_epc:
                    manager.load_configuration(actual_epc, skip_cleanup=not bool(def_path))

                # Record provenance (source_epc relative to the EB source root)
                source_epc_str = None
                if actual_epc:
                    try:
                        source_epc_str = Path(actual_epc).relative_to(project_root).as_posix()
                    except ValueError:
                        source_epc_str = Path(actual_epc).as_posix()
                project.module_provenance[actual_name] = {
                    "origin": "eb-import",
                    "source_epc": source_epc_str,
                    "imported_at": datetime.now().isoformat(),
                }

                loaded_modules.append(actual_name)
            except Exception as e:
                error_str = str(e)
                # Non-module definition files (e.g., McuPreConfiguration) - just skip
                if "No ECUC-MODULE-DEF found" in error_str:
                    _progress(f"  Skipped {module_name}: not a module definition ({def_path.name})")
                    continue
                error_msg = f"Failed to load: {error_str}"
                failed_modules.append((module_name, error_msg))


        _progress(f"Import complete: {len(loaded_modules)} loaded, {len(failed_modules)} failed")

        # Step 5: Resolve cross-module references
        if loaded_modules:
            try:
                resolved_count, error_count = project.resolve_all_references()
                reverse_count = project.build_reverse_reference_index()
            except Exception as e:
                import logging
                logging.getLogger(__name__).warning(
                    f"Reference resolution failed during EB import: {e}", exc_info=True
                )
        # Link mode: templates/{Module} -> plugin generate_PB symlinks
        # (copy mode copies them at save time via _copy_eb_templates)
        if mode == "link":
            templates_dir = project_paths.resolve(project, "templates")
            templates_dir.mkdir(parents=True, exist_ok=True)
            linked = 0
            for name, def_path in project.module_defs.items():
                generate_pb = def_path.parent.parent / "generate_PB"
                link_path = templates_dir / name
                if generate_pb.is_dir() and not (link_path.is_symlink() or link_path.exists()):
                    os.symlink(generate_pb.resolve(), link_path, target_is_directory=True)
                    linked += 1
            _progress(f"Linked {linked} template directory(ies) into templates/")

        # Store chip info and EB source root
        chips = EpcFileScanner.detect_available_chips(project_root)
        project.available_chips = chips
        project.selected_chip = chip_name
        project.eb_source_root = project_root

        # Step 6: Load ECU resources from .properties files (now in Def/plugins/)
        ecu_res = project.load_ecu_resources()


        self.current_project = project
        return project, loaded_modules, failed_modules
