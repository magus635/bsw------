"""Phase 1 model-driven RTE/SchM code generator facade."""

from pathlib import Path
import logging
from typing import Any, Dict, List, Optional, Tuple

from ...core import project_paths
from .extractor import RteModelExtractor
from .model import RteGenerationReport, RtePreviewFile, RteProjectModel
from .renderers import (
    render_rte_cbk_h,
    render_rte_cfg_h,
    render_rte_h,
    render_rte_main_h,
    render_rte_type_h_stub,
    render_rte_user_types_h,
    render_schm_h,
    render_schm_type_h,
)
from .renderers_phase23 import (
    _merge_swc_models,
    render_rte_c,
    render_rte_compiler_cfg_h,
    render_rte_data_handle_type_h,
    render_rte_hook_h,
    render_rte_osapp_c,
    render_rte_type_h_full,
    render_swc_h,
    render_swc_memmap_h,
    render_swc_type_h,
)

logger = logging.getLogger(__name__)


def has_project_overlay_templates(
    overlay_root: Optional[Path],
    module_name: str,
    package_dir_name: Optional[str] = None,
) -> bool:
    """Return True when ``overlay_root`` contains a non-empty module/variant overlay dir."""
    if overlay_root is None or not Path(overlay_root).is_dir():
        return False
    root = Path(overlay_root)
    candidates = [module_name]
    if package_dir_name and package_dir_name.lower() != module_name.lower():
        candidates.insert(0, package_dir_name)
    target_lowers = {c.lower() for c in candidates}
    try:
        for item in root.iterdir():
            if item.is_dir() and item.name.lower() in target_lowers:
                if any(p.is_file() for p in item.rglob("*")):
                    return True
    except OSError:
        return False
    return False


def run_rte_schm_pipeline(
    project: Any,
    output_dir: Path,
    *,
    flat: bool,
    generate_type_stub: bool = True,
    include_phase2_3: bool = True,
    force: bool = False,
    apply_overlay: bool = True,
    overlay_root: Optional[Path] = None,
    variant_name: Optional[str] = None,
    variant_overrides: Optional[Dict[str, Any]] = None,
    project_variants: Optional[Any] = None,
    all_configs: Optional[Dict[str, Any]] = None,
    selected_chip: Optional[str] = None,
    ecu_resources: Optional[Dict[str, Any]] = None,
    project_root: Optional[Path] = None,
    package_dir_name: Optional[str] = None,
    module_def: Any = None,
    configuration: Any = None,
    ib_index: Optional[Any] = None,
    swc_index: Optional[Any] = None,
) -> Tuple[bool, RteGenerationReport, str]:
    """Run Phase 1-3 model-driven RTE/SchM generation and optional ``templates/Rte/`` overlays."""
    from ..generator import CodeGenerator

    report = RteSchMGenerator(
        project,
        generate_type_stub=generate_type_stub,
        include_phase2_3=include_phase2_3,
    ).generate(
        Path(output_dir), flat=flat, force=force, ib_index=ib_index, swc_index=swc_index
    )
    for w in report.warnings:
        logger.warning("[RteSchMGen] %s", w)
    if not report.ok:
        err_msg = "; ".join(report.errors)
        logger.error("[RteSchMGen] Failed: %s", err_msg)
        return False, report, err_msg

    if (
        apply_overlay
        and overlay_root is not None
        and module_def is not None
        and configuration is not None
        and has_project_overlay_templates(overlay_root, "Rte", package_dir_name)
    ):
        overlay_gen = CodeGenerator(
            module_def,
            configuration,
            project_template_dir=overlay_root,
            package_template_dir=None,
            variant_overrides=variant_overrides,
            variant_name=variant_name,
            project_variants=project_variants,
            all_configurations=all_configs,
            selected_chip=selected_chip,
            ecu_resources=ecu_resources,
            project_root=project_root,
            package_dir_name=package_dir_name,
        )
        variant_to_use = variant_name if variant_name else "Default"
        ov_ok = overlay_gen.generate_all(
            Path(output_dir), force=force, variant=variant_to_use, flat=flat
        )
        if not ov_ok and overlay_gen.last_status != "skipped":
            msg = "Rte project overlay template generation failed"
            report.errors.append(msg)
            return False, report, msg

    detail = ""
    if report.skipped_modules:
        skipped_names = ", ".join(m for m, _ in report.skipped_modules)
        detail = f"skipped unloaded modules: {skipped_names}"
    return True, report, detail


class RteSchMGenerator:
    """Synthesizes Phase 1 RTE/SchM headers and Phase 2/3 SWC contracts + multi-core C sources."""

    def __init__(
        self,
        project: Any,
        *,
        generate_type_stub: bool = True,
        include_phase2_3: bool = True,
    ) -> None:
        self.project = project
        self.generate_type_stub = generate_type_stub
        self.include_phase2_3 = include_phase2_3

    def generate(
        self,
        output_dir: Path,
        *,
        flat: bool = False,
        force: bool = False,
        ib_index: Optional[Any] = None,
        swc_index: Optional[Any] = None,
    ) -> RteGenerationReport:
        """Extract models and emit Phase 1-3 files into ``output_dir``."""
        model, report = RteModelExtractor.extract(
            self.project, ib_index=ib_index, swc_index=swc_index
        )
        if model is None or not report.ok:
            return report

        base_out = Path(output_dir)
        include_dir = base_out / ("include" if flat else "Rte/include")
        src_dir = base_out / ("src" if flat else "Rte/src")
        include_dir.mkdir(parents=True, exist_ok=True)

        outputs = self._build_outputs(model, include_phase2_3=self.include_phase2_3)
        for rel_name, content in sorted(outputs.items()):
            dst = include_dir / rel_name
            dst.parent.mkdir(parents=True, exist_ok=True)
            self._write_if_changed(dst, content, report, force=force)

        stubs = self._build_stubs(model, include_phase2_3=self.include_phase2_3)
        for rel_name, (content, _src_kind) in sorted(stubs.items()):
            dst = include_dir / rel_name
            dst.parent.mkdir(parents=True, exist_ok=True)
            if dst.exists():
                report.preserved_files.append(dst)
            else:
                dst.write_text(content, encoding="utf-8")
                report.generated_files.append(dst)

        if self.include_phase2_3:
            c_sources = self._build_c_sources(model)
            if c_sources:
                src_dir.mkdir(parents=True, exist_ok=True)
                for rel_name, content in sorted(c_sources.items()):
                    dst = src_dir / rel_name
                    dst.parent.mkdir(parents=True, exist_ok=True)
                    self._write_if_changed(dst, content, report, force=force)

        return report

    def preview(
        self,
        output_dir: Path,
        *,
        flat: bool = False,
        overlay_root: Optional[Path] = None,
        package_dir_name: Optional[str] = None,
        ib_index: Optional[Any] = None,
        swc_index: Optional[Any] = None,
    ) -> Tuple[List[RtePreviewFile], RteGenerationReport]:
        """Compute non-mutating Phase 1-3 file previews and diagnostics against ``output_dir``."""
        model, report = RteModelExtractor.extract(
            self.project, ib_index=ib_index, swc_index=swc_index
        )
        if model is None:
            return [], report

        base_out = Path(output_dir)
        include_dir = base_out / ("include" if flat else "Rte/include")
        src_dir = base_out / ("src" if flat else "Rte/src")

        preview_map: Dict[str, RtePreviewFile] = {}
        for rel_name, content in sorted(
            self._build_outputs(model, include_phase2_3=self.include_phase2_3).items()
        ):
            dst = include_dir / rel_name
            status = "new"
            if dst.is_file():
                try:
                    status = "unchanged" if dst.read_text(encoding="utf-8") == content else "updated"
                except OSError:
                    status = "updated"
            preview_map[rel_name] = RtePreviewFile(
                filename=rel_name,
                target_path=dst,
                content=content,
                status=status,
                source="model",
            )

        for rel_name, (content, src_kind) in sorted(
            self._build_stubs(model, include_phase2_3=self.include_phase2_3).items()
        ):
            dst = include_dir / rel_name
            if dst.is_file():
                try:
                    existing_text = dst.read_text(encoding="utf-8", errors="replace")
                except OSError:
                    existing_text = content
                preview_map[rel_name] = RtePreviewFile(
                    filename=rel_name,
                    target_path=dst,
                    content=existing_text,
                    status="preserved",
                    source=src_kind,
                )
            else:
                preview_map[rel_name] = RtePreviewFile(
                    filename=rel_name,
                    target_path=dst,
                    content=content,
                    status="new",
                    source=src_kind,
                )

        if self.include_phase2_3:
            for rel_name, content in sorted(self._build_c_sources(model).items()):
                dst = src_dir / rel_name
                status = "new"
                if dst.is_file():
                    try:
                        status = "unchanged" if dst.read_text(encoding="utf-8") == content else "updated"
                    except OSError:
                        status = "updated"
                preview_map[rel_name] = RtePreviewFile(
                    filename=rel_name,
                    target_path=dst,
                    content=content,
                    status=status,
                    source="model",
                )

        if overlay_root is not None:
            for rel_name, dst_dir, content in self._collect_overlay_previews(
                Path(overlay_root), include_dir, src_dir, package_dir_name
            ):
                preview_map[rel_name] = RtePreviewFile(
                    filename=rel_name,
                    target_path=dst_dir / rel_name,
                    content=content,
                    status="overlay",
                    source="overlay",
                )

        files = [preview_map[k] for k in sorted(preview_map)]
        return files, report

    @staticmethod
    def _build_outputs(
        model: RteProjectModel,
        *,
        include_phase2_3: bool = True,
    ) -> Dict[str, str]:
        outputs: Dict[str, str] = {
            "Rte.h": render_rte_h(model),
            "Rte_Main.h": render_rte_main_h(model),
            "Rte_Cfg.h": render_rte_cfg_h(model),
            "Rte_Cbk.h": render_rte_cbk_h(model),
        }
        for bsw_mod in model.bsw_modules:
            outputs[f"SchM_{bsw_mod.api_name}.h"] = render_schm_h(bsw_mod)
            outputs[f"SchM_{bsw_mod.api_name}_Type.h"] = render_schm_type_h(bsw_mod)

        if include_phase2_3:
            outputs["Rte_Compiler_Cfg.h"] = render_rte_compiler_cfg_h(model)
            outputs["Rte_Hook.h"] = render_rte_hook_h(model)

        if include_phase2_3 and (model.swc_components or model.rte_type_defs):
            outputs["Rte_DataHandleType.h"] = render_rte_data_handle_type_h(model)
            by_type: Dict[str, List[Any]] = {}
            for swc in model.swc_components:
                by_type.setdefault(swc.swc_type_name, []).append(swc)
            for swc_type_name, group in sorted(by_type.items()):
                merged = _merge_swc_models(group)
                outputs[f"Components/Rte_{swc_type_name}_Type.h"] = render_swc_type_h(merged)
                outputs[f"Components/Rte_{swc_type_name}.h"] = render_swc_h(merged)
                outputs[f"Components/{swc_type_name}_MemMap.h"] = render_swc_memmap_h(merged)

        return outputs

    def _build_stubs(
        self,
        model: Optional[RteProjectModel] = None,
        *,
        include_phase2_3: bool = True,
    ) -> Dict[str, Tuple[str, str]]:
        stubs: Dict[str, Tuple[str, str]] = {"Rte_UserTypes.h": (render_rte_user_types_h(), "stub")}
        if self.generate_type_stub:
            if include_phase2_3 and model is not None and (model.rte_type_defs or model.swc_components):
                stubs["Rte_Type.h"] = (render_rte_type_h_full(model), "model")
            else:
                stubs["Rte_Type.h"] = (render_rte_type_h_stub(), "stub")
        return stubs

    @staticmethod
    def _build_c_sources(model: RteProjectModel) -> Dict[str, str]:
        if not model.swc_components and not model.task_schedules:
            return {}
        sources: Dict[str, str] = {"Rte.c": render_rte_c(model)}
        apps = sorted(
            {t.os_application for t in model.task_schedules if t.os_application}
            | {s.os_application for s in model.swc_components if s.os_application}
            | set(model.os_applications)
        )
        if not apps:
            apps = ["SystemApplication_OsCore0"]
        for app_name in apps:
            sources[f"Rte_{app_name}.c"] = render_rte_osapp_c(model, app_name)
        return sources

    @staticmethod
    def _collect_overlay_previews(
        overlay_root: Path,
        include_dir: Path,
        src_dir: Path,
        package_dir_name: Optional[str],
    ) -> List[Tuple[str, Path, str]]:
        if not overlay_root.is_dir():
            return []
        candidates = ["Rte"]
        if package_dir_name and package_dir_name.lower() != "rte":
            candidates.insert(0, package_dir_name)
        seen_names: set = set()
        results: List[Tuple[str, Path, str]] = []
        # Search lowest-precedence last, or match priority order keeping first
        for cname in candidates:
            matched_dir: Optional[Path] = None
            exact = overlay_root / cname
            if exact.is_dir():
                matched_dir = exact
            else:
                try:
                    for item in sorted(overlay_root.iterdir(), key=lambda p: p.name):
                        if item.is_dir() and item.name.lower() == cname.lower():
                            matched_dir = item
                            break
                except OSError:
                    matched_dir = None
            if matched_dir is None:
                continue
            for f in sorted(matched_dir.rglob("*"), key=lambda p: p.as_posix()):
                if not f.is_file():
                    continue
                low = f.name.lower()
                if not low.startswith(("rte_", "rte.", "schm_")):
                    continue
                if not low.endswith((".h", ".c", ".tpl")):
                    continue
                out_name = f.name[:-4] if low.endswith(".tpl") else f.name
                if not out_name.lower().endswith((".h", ".c")):
                    continue
                if out_name in seen_names:
                    continue
                seen_names.add(out_name)
                try:
                    text = f.read_text(encoding="utf-8", errors="replace")
                except OSError:
                    continue
                dst_dir = src_dir if out_name.lower().endswith(".c") else include_dir
                results.append((out_name, dst_dir, text))
        return results

    @staticmethod
    def _write_if_changed(
        dst: Path,
        content: str,
        report: RteGenerationReport,
        *,
        force: bool,
    ) -> None:
        if not force and dst.is_file():
            try:
                if dst.read_text(encoding="utf-8") == content:
                    report.unchanged_files.append(dst)
                    return
            except OSError:
                pass
        dst.write_text(content, encoding="utf-8")
        report.generated_files.append(dst)

    @classmethod
    def generate_from_project(
        cls,
        project: Any,
        output_dir: Optional[Path] = None,
        *,
        flat: Optional[bool] = None,
        force: bool = False,
        generate_type_stub: bool = True,
        include_phase2_3: bool = True,
    ) -> RteGenerationReport:
        """Convenience entry point resolving layout and default output root from ``project``."""
        if flat is None:
            flat = project_paths.dirs(project).gen_layout == project_paths.GEN_LAYOUT_FLAT
        target = Path(output_dir) if output_dir is not None else project_paths.resolve(project, "gen")
        return cls(
            project,
            generate_type_stub=generate_type_stub,
            include_phase2_3=include_phase2_3,
        ).generate(target, flat=flat, force=force)
