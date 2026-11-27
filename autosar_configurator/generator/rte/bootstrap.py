"""Discovery and one-click initialization of the ``Rte`` module for projects lacking it."""

import shutil
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, List, Optional, Tuple

from .workbench_service import RteGenerationSettings, RteWorkbenchService


def builtin_rte_bswmd_path() -> Path:
    """Return the path to the built-in minimal AUTOSAR R4.2.2 ``Rte_bswmd.arxml``."""
    return Path(__file__).resolve().parents[2] / "data" / "builtin_defs" / "Rte_bswmd.arxml"


@dataclass
class RteBootstrapSources:
    """Discovered ways to activate, restore, or initialize ``Rte`` for a project."""

    library_packages: List[Tuple[int, Any]] = field(default_factory=list)
    deleted_archives: List[Path] = field(default_factory=list)
    has_failed_entry: bool = False


def discover_rte_sources(project: Any) -> RteBootstrapSources:
    """Inspect ``project`` safely for unactivated ``Rte`` packages, archives, or failed entries."""
    sources = RteBootstrapSources()
    if project is None:
        return sources

    if hasattr(project, "list_module_variant_packages"):
        try:
            sources.library_packages = list(project.list_module_variant_packages("Rte") or ())
        except Exception:
            sources.library_packages = []

    if getattr(project, "format_version", 0) >= 8 and hasattr(project, "list_deleted_archives"):
        try:
            sources.deleted_archives = list(project.list_deleted_archives("Rte") or ())
        except Exception:
            sources.deleted_archives = []

    managers = getattr(project, "module_managers", {}) or {}
    entries = getattr(project, "module_entries", {}) or {}
    sources.has_failed_entry = ("Rte" in entries) and ("Rte" not in managers)
    return sources


def bootstrap_rte_module(
    project: Any,
    *,
    library_package: Optional[Tuple[int, Any]] = None,
    restore_archive: Optional[Path] = None,
    confirm=None,
    seed_defaults: bool = True,
) -> Tuple[Any, str]:
    """Ensure ``Rte`` is loaded in ``project``, returning ``(manager, source_kind)``.

    ``source_kind`` is one of ``"existing"``, ``"restored"``, ``"library"``, or ``"builtin"``.
    """
    if project is None:
        raise ValueError("未提供工程对象，无法初始化 Rte 模块")

    managers = getattr(project, "module_managers", {}) or {}
    existing_mgr = managers.get("Rte")
    if existing_mgr is not None and getattr(existing_mgr, "configuration", None) is not None:
        return existing_mgr, "existing"

    if restore_archive is not None:
        mgr = project.restore_deleted_module(Path(restore_archive), confirm=confirm)
        source = "restored"
    elif library_package is not None:
        lib_index, pkg = library_package
        mgr = project.add_module_from_package(pkg, lib_index, confirm=confirm)
        source = "library"
    else:
        def_path = builtin_rte_bswmd_path()
        if not def_path.is_file():
            raise FileNotFoundError(f"内置 Rte BSWMD 定义文件不存在: {def_path}")

        proj_path = getattr(project, "path", None)
        if (
            getattr(project, "format_version", 7) >= 8
            and proj_path is not None
            and hasattr(project, "add_custom_module_from_file")
        ):
            mgr = project.add_custom_module_from_file(def_path, confirm=confirm)
        else:
            if proj_path is not None:
                def_dir = Path(proj_path).parent / "Def"
                def_dir.mkdir(parents=True, exist_ok=True)
                def_file = def_dir / def_path.name
                if not def_file.is_file():
                    shutil.copy2(def_path, def_file)
            else:
                def_file = def_path

            from ...core.parser.ecuc_def_parser import EcucDefParser

            parser = EcucDefParser()
            try:
                from ...core.hardware.ecu_resource_resolver import selector_values

                parser.set_selector_values(selector_values(project))
            except Exception:
                pass
            module_def = parser.parse_module_def_file(def_file)
            mgr = project.add_module(module_def, def_file)
        source = "builtin"

    if (
        seed_defaults
        and mgr is not None
        and getattr(mgr, "configuration", None) is not None
        and not getattr(mgr.configuration, "containers", None)
    ):
        RteWorkbenchService(project).update_rte_generation_settings(RteGenerationSettings())

    return mgr, source
