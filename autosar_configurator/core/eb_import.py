"""EB Tresos project import into a format 8 project (design §6.10, §6.6).

The pieces ``WorkspaceManager.import_eb_project`` puts together, kept here so that method
only orchestrates:

- :func:`import_project_dir` / :func:`import_target`: where the project goes — never inside
  the EB tree, never into a folder that already holds something;
- :func:`inspect_folder`: whether a folder is a project of this tool (a JSON ``.dpa``), an
  EB tree, or both — the one rule "Open Project Folder" and "Import EB Project" share;
- :func:`find_plugins_dir` / :func:`survey_plugins`: which plugin directories of the source
  tree are module packages, which are skipped and why, and which Vector-wrapped MCAL
  directories go into the library's ``exclude`` because an EB plugin provides the same
  definition (the ``Components/Mcal_Tha62x`` rule of the SIP spec, §6.3);
- :func:`module_configs_in`: the module configurations an EPC value file holds;
- :func:`package_record`: the package's files and their hashes for ``ModuleEntry``
  (SIP R4);
- :class:`ImportReport`: the per-module import report written to
  ``<history>/reports/<YYYYmmdd-HHMMSS>_import.md`` — nothing the import leaves out may go
  unreported.

No PySide6 here.
"""
import hashlib
import logging
from dataclasses import dataclass, field
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from lxml import etree

from . import project_paths
from .packages.errors import PackageError
from .packages.manifest import infer_package
from .packages.package import ModulePackage, module_def_paths

__all__ = [
    "EB_PLUGIN_MARKER", "IMPORTED_SUFFIX", "SkippedDir", "WrappedMcal", "PluginSurvey",
    "EpcValues", "ModuleImport", "ImportReport",
    "import_project_dir", "import_target", "free_sibling", "check_target_is_free",
    "is_tool_project_file", "FolderKind", "inspect_folder",
    "find_plugins_dir", "survey_plugins",
    "module_configs_in",
    "epc_names_definition", "count_values", "package_record", "report_path", "write_report",
]

_log = logging.getLogger(__name__)

EB_PLUGIN_MARKER = "plugin.xml"
_VECTOR_MANIFEST = "module.json"


def _secure_parser() -> etree.XMLParser:
    return etree.XMLParser(resolve_entities=False, no_network=True, huge_tree=True)


def _local(tag) -> str:
    return tag.rsplit("}", 1)[-1] if isinstance(tag, str) else ""


def _child_text(elem, name: str) -> Optional[str]:
    for child in elem:
        if _local(child.tag) == name:
            return (child.text or "").strip()
    return None


# --- where the project goes -------------------------------------------------------------

IMPORTED_SUFFIX = "_imported"


def _is_within(path: Path, root: Path) -> bool:
    path, root = Path(path).resolve(), Path(root).resolve()
    return path == root or root in path.parents


def _inside_message(target: Path, project_root: Path) -> str:
    return (f"不能把导入的工程放进 EB 工程目录本身：{Path(target).as_posix()} 在 "
            f"{Path(project_root).as_posix()} 之内。请选择 EB 工程目录之外的文件夹。")


def _is_free(directory: Path) -> bool:
    """Nothing there yet, or an empty directory: a project can be created in it."""
    if not directory.exists():
        return True
    try:
        return directory.is_dir() and not any(directory.iterdir())
    except OSError:
        return False


def free_sibling(project_root: Path) -> Path:
    """The first of ``<root>_imported``, ``<root>_imported_2``, … that is free
    (missing, or an empty directory) — an existing folder is never merged into."""
    project_root = Path(project_root)
    base = f"{project_root.name}{IMPORTED_SUFFIX}"
    candidate, counter = project_root.parent / base, 2
    while not _is_free(candidate):
        candidate = project_root.parent / f"{base}_{counter}"
        counter += 1
    return candidate


def import_project_dir(project_root: Path, target_dir: Optional[Path]) -> Path:
    """The directory :meth:`WorkspaceManager.import_eb_project` writes the project to.

    ``None``, or the EB tree itself, gives the first free sibling (:func:`free_sibling`);
    any other directory is used as it is — and must be free, see
    :func:`check_target_is_free`.

    Raises:
        ValueError: ``target_dir`` lies inside the EB tree — the import only reads it.
    """
    project_root = Path(project_root)
    if target_dir is None or Path(target_dir).resolve() == project_root.resolve():
        return free_sibling(project_root)
    if _is_within(target_dir, project_root):
        raise ValueError(_inside_message(target_dir, project_root))
    return Path(target_dir)


def check_target_is_free(project_dir: Path) -> None:
    """Refuse a project directory that already holds anything (a file, a folder).

    Raises:
        ValueError: the directory is a file, or a directory that is not empty; the message
            names what is there. The import never merges into, or overwrites, existing
            content.
    """
    project_dir = Path(project_dir)
    if _is_free(project_dir):
        return
    if not project_dir.is_dir():
        found = [project_dir]
    else:
        found = sorted(project_dir.iterdir(), key=lambda p: p.name)
    shown = "\n  ".join(p.as_posix() for p in found[:10])
    more = f"\n  …以及另外 {len(found) - 10} 项" if len(found) > 10 else ""
    raise ValueError(
        f"目标目录中已有内容，导入不会覆盖或合并进已有内容：\n  {shown}{more}\n"
        "请选择一个空目录。")


def import_target(project_root: Path, parent: Optional[Path]) -> Path:
    """The project directory for a destination folder the user chose (the UI dialogs).

    The project gets the subfolder ``<parent>/<EB tree name>``; ``None`` means "next to
    the EB tree". When that subfolder would be the EB tree itself (``parent`` holds it),
    the project goes to the first free sibling instead — ``<EB tree>_imported``,
    ``<EB tree>_imported_2``, … (:func:`free_sibling`), never an existing non-empty folder.
    A subfolder that already holds something is refused later by
    :func:`check_target_is_free`.

    Raises:
        ValueError: ``parent`` is the EB tree or inside it.
    """
    project_root = Path(project_root)
    if parent is None:
        return import_project_dir(project_root, None)
    if _is_within(parent, project_root):
        raise ValueError(_inside_message(parent, project_root))
    return import_project_dir(project_root, Path(parent) / project_root.name)


# --- what a folder is -------------------------------------------------------------------

def is_tool_project_file(path: Path) -> bool:
    """Whether ``path`` is a project file of this tool: a JSON object with ``format_version``.

    Anything else with the ``.dpa`` extension — a DaVinci XML project, a damaged or empty
    file, JSON that is not ours — is not a project of this tool, and must neither stop an
    EB import nor be opened as one.
    """
    import json

    try:
        data = json.loads(Path(path).read_text(encoding="utf-8"))
    except (OSError, ValueError, UnicodeDecodeError):
        return False
    return isinstance(data, dict) and "format_version" in data


@dataclass
class FolderKind:
    """What :func:`inspect_folder` found at the top level of a folder.

    Attributes:
        folder: The folder inspected.
        project_files: Project files of this tool (:func:`is_tool_project_file`) directly
            in the folder, sorted by name (case-insensitively, then exactly).
        is_eb_tree: The folder holds EB content an import would read: an EB plugins
            directory with at least one ``plugin.xml``, or EPC values under ``Config/``.
        has_eb_marker: The folder carries an EB workspace marker (``.tresos`` or
            ``.project``). Not EB content — it does not make a folder "both" — but it lets
            a folder without a project file be imported as EB, as it always could.
    """
    folder: Path
    project_files: List[Path] = field(default_factory=list)
    is_eb_tree: bool = False
    has_eb_marker: bool = False

    @property
    def is_project(self) -> bool:
        return bool(self.project_files)

    @property
    def is_both(self) -> bool:
        """A project file *and* EB content — e.g. ``<root>/<root>.dpa`` written into the EB
        tree by an earlier version of the import. Only the user can say which is meant."""
        return self.is_project and self.is_eb_tree


def _has_epc_values(folder: Path) -> bool:
    config = folder / "Config"
    try:
        return config.is_dir() and any(
            (chip / "output").is_dir() and any((chip / "output").glob("*.epc"))
            for chip in config.iterdir() if chip.is_dir())
    except OSError:
        return False


def inspect_folder(folder: Path) -> FolderKind:
    """Classify ``folder`` for "Open Project Folder" and "Import EB Project".

    Only the top level is looked at for project files, and a ``.dpa`` counts only when it
    is this tool's JSON project file. EB content is an EB plugins directory that holds
    plugins (:func:`find_plugins_dir`) or EPC values in ``Config/<chip>/output``. Nothing is
    written, and an unreadable folder is simply neither.
    """
    folder = Path(folder)
    kind = FolderKind(folder)
    if not folder.is_dir():
        return kind
    try:
        candidates = [p for p in folder.glob("*.dpa") if p.is_file()]
    except OSError:
        candidates = []
    kind.project_files = sorted((p for p in candidates if is_tool_project_file(p)),
                                key=lambda p: (p.name.lower(), p.name))
    plugins = find_plugins_dir(folder)
    kind.is_eb_tree = (plugins is not None and _holds_plugins(plugins)) or _has_epc_values(folder)
    kind.has_eb_marker = any((folder / name).exists() for name in (".tresos", ".project"))
    return kind


# --- the plugin directory ---------------------------------------------------------------

def _holds_plugins(directory: Path) -> bool:
    try:
        return any((sub / EB_PLUGIN_MARKER).is_file() for sub in directory.iterdir() if sub.is_dir())
    except OSError:
        return False


def find_plugins_dir(project_root: Path) -> Optional[Path]:
    """The EB plugins directory of a source tree, or ``None`` when it has none.

    Looked for in ``Define/EbPlugins/eclipse`` and the legacy plugins directory
    (``Def/plugins``), each also one level down in ``plugins/`` (an Eclipse installation
    keeps its plugins in ``eclipse/plugins/<Plugin>``). The first candidate whose
    subdirectories hold a ``plugin.xml`` wins; failing that, the first that exists.
    """
    roots = (Path(project_root) / "Define" / "EbPlugins" / "eclipse",
             project_paths.legacy_plugins_dir(project_root))
    existing = [c for root in roots for c in (root, root / "plugins") if c.is_dir()]
    for candidate in existing:
        if _holds_plugins(candidate):
            return candidate
    return existing[0] if existing else None


@dataclass
class SkippedDir:
    """A directory of the plugins directory that is not imported, and why."""
    name: str
    reason: str


@dataclass
class WrappedMcal:
    """A Vector-wrapped MCAL directory left out because EB plugins provide its modules.

    Attributes:
        name: Directory name (it goes into the library's ``exclude``).
        modules: ``(definition, EB plugin directory that provides it)`` for every definition
            the directory would have duplicated, sorted by definition.
    """
    name: str
    modules: List[Tuple[str, str]] = field(default_factory=list)


@dataclass
class PluginSurvey:
    """What :func:`survey_plugins` found in a plugins directory.

    Attributes:
        packages: Every directory with a ``plugin.xml`` that infers as a module package,
            sorted by directory name — the wrapped duplicates included (they are left out
            by ``exclude``, not by this list).
        skipped: Directories that are not module packages.
        wrapped: Vector-wrapped MCAL directories to exclude.
    """
    packages: List[ModulePackage] = field(default_factory=list)
    skipped: List[SkippedDir] = field(default_factory=list)
    wrapped: List[WrappedMcal] = field(default_factory=list)

    @property
    def exclude(self) -> List[str]:
        """Directory names for ``LibraryRef.exclude``, sorted."""
        return sorted(w.name for w in self.wrapped)


def _definitions_in(directory: Path) -> List[str]:
    """AR paths of every ECUC-MODULE-DEF in the ``.arxml`` files below ``directory``."""
    found = set()
    for path in sorted(directory.rglob("*.arxml"), key=lambda p: p.as_posix()):
        try:
            found.update(module_def_paths(path))
        except (etree.XMLSyntaxError, OSError) as exc:
            _log.warning("无法读取定义文件，跳过：%s（%s）", path, exc)
    return sorted(found)


def survey_plugins(plugins_dir: Path) -> PluginSurvey:
    """Classify every first-level directory of ``plugins_dir``.

    - A directory with ``plugin.xml`` whose manifest infers is a package; one whose
      manifest does not (a tresos plugin that configures no module) is skipped.
    - A Vector-wrapped MCAL directory duplicates a definition an EB plugin provides: a
      directory without ``plugin.xml`` whose ``.arxml`` files define it (a BSWMD), or a
      package carrying a ``module.json`` next to the EB plugin that provides the same
      definition. It is excluded, never loaded — two definitions of one module would
      conflict (design §6.3).
    - Any other directory without ``plugin.xml`` is skipped.

    Two EB plugins providing the same definition are left alone: the import cannot choose
    between them, so that module fails with the conflict and the report says so.
    """
    survey = PluginSurvey()
    plain: List[Path] = []
    for sub in sorted(Path(plugins_dir).iterdir(), key=lambda p: p.name):
        if not sub.is_dir() or sub.name.startswith("."):
            continue
        if not (sub / EB_PLUGIN_MARKER).is_file():
            plain.append(sub)
            continue
        try:
            manifest = infer_package(sub)
        except (PackageError, ValueError, KeyError, OSError) as exc:
            survey.skipped.append(SkippedDir(sub.name, f"不是模块插件（{exc}）"))
            continue
        survey.packages.append(ModulePackage(sub, manifest))

    # Definition -> the EB plugins (plugin.xml without module.json) that provide it
    eb_plugins: Dict[str, List[str]] = {}
    for pkg in survey.packages:
        if not (pkg.root / _VECTOR_MANIFEST).is_file():
            eb_plugins.setdefault(pkg.manifest.definition, []).append(pkg.root.name)

    wrapped: Dict[str, List[Tuple[str, str]]] = {}
    for pkg in survey.packages:
        providers = eb_plugins.get(pkg.manifest.definition, [])
        if (pkg.root / _VECTOR_MANIFEST).is_file() and len(providers) == 1:
            wrapped.setdefault(pkg.root.name, []).append((pkg.manifest.definition, providers[0]))
    for sub in plain:
        clashes = [(d, eb_plugins[d][0]) for d in _definitions_in(sub)
                   if len(eb_plugins.get(d, [])) == 1]
        if clashes:
            wrapped.setdefault(sub.name, []).extend(clashes)
        else:
            survey.skipped.append(SkippedDir(sub.name, "没有 plugin.xml，不是 EB 插件"))
    survey.wrapped = [WrappedMcal(name, sorted(mods)) for name, mods in sorted(wrapped.items())]
    return survey


# --- EPC values -----------------------------------------------------------------------

@dataclass
class EpcValues:
    """One module configuration in an EPC value file."""
    file: Path
    short_name: str
    definition_ref: Optional[str]


_STANDARD_DEFS = "/AUTOSAR/EcucDefs/"


def epc_names_definition(epc_ref: Optional[str], definition: str) -> bool:
    """Whether an EPC whose module DEFINITION-REF is ``epc_ref`` configures ``definition``.

    The module path must be the same, or the EPC names the standard AUTOSAR module
    (``/AUTOSAR/EcucDefs/<M>``) that every vendor definition of ``<M>`` refines. An EPC
    without a DEFINITION-REF is bound by its name alone, as before.

    ``definition_refs.same_definition`` cannot decide this: it compares module-relative
    paths, which are empty for any module path, so ``/A/Mcu`` and ``/B/Mcu`` compare equal.
    The check also has to happen before the values are loaded — ``load_configuration``
    repairs the module's DEFINITION-REF to the plugin's own path.
    """
    if not epc_ref:
        return True
    ref, own = epc_ref.rstrip("/"), definition.rstrip("/")
    if ref == own:
        return True
    module = own.rsplit("/", 1)[-1]
    return ref == f"{_STANDARD_DEFS}{module}"


def module_configs_in(value_file: Path) -> List[Tuple[str, Optional[str]]]:
    """``(SHORT-NAME, DEFINITION-REF)`` of every ECUC-MODULE-CONFIGURATION-VALUES in a file.

    Raises:
        etree.XMLSyntaxError / OSError: the file cannot be read (the caller reports it).
    """
    root = etree.parse(str(value_file), _secure_parser()).getroot()
    configs = []
    for elem in root.iter():
        if _local(elem.tag) != "ECUC-MODULE-CONFIGURATION-VALUES":
            continue
        name = _child_text(elem, "SHORT-NAME")
        if name:
            configs.append((name, _child_text(elem, "DEFINITION-REF") or None))
    return configs


def count_values(configuration) -> Dict[str, int]:
    """Containers, parameters, references and unrecognised parameters of a configuration."""
    counts = {"containers": 0, "parameters": len(configuration.parameter_values),
              "references": 0, "unknown": 0}

    def walk(container) -> None:
        counts["containers"] += 1
        counts["parameters"] += len(container.parameter_values)
        counts["parameters"] += sum(len(v) for v in container.multi_parameter_values.values())
        counts["references"] += len(container.reference_values)
        counts["references"] += sum(len(v) for v in container.multi_reference_values.values())
        counts["unknown"] += len(container.unknown_parameters)
        for sub in container.sub_containers:
            walk(sub)

    for container in configuration.containers:
        walk(container)
    return counts


# --- the package record (SIP R4) --------------------------------------------------------

def _sha256(path: Path) -> str:
    return "sha256:" + hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _plugin_sw_version(plugin_dir: Path) -> Optional[str]:
    """``"<major>.<minor>.<patch>"`` of the module a ``plugin.xml`` declares, if any."""
    plugin_xml = plugin_dir / EB_PLUGIN_MARKER
    if not plugin_xml.is_file():
        return None
    try:
        root = etree.parse(str(plugin_xml), _secure_parser()).getroot()
    except (etree.XMLSyntaxError, OSError):
        return None
    for module in root.iter("module"):
        parts = [module.get(f"swVersion{part}") for part in ("Major", "Minor", "Patch")]
        if all(parts):
            return ".".join(parts)
    return None


def package_record(pkg: ModulePackage) -> Dict[str, object]:
    """``{"sw_version": …, "files": {<path>: "sha256:<hex>"}}`` of a package's files.

    The files are the manifest's (definition and value files; not the exchange copies, which
    are never loaded), keyed by their POSIX path inside the package. A listed file that is
    missing is recorded as ``None`` rather than left out.
    """
    files: Dict[str, Optional[str]] = {}
    for pf in sorted(pkg.manifest.files, key=lambda f: f.path):
        path = pkg.root / pf.path
        files[pf.path] = _sha256(path) if path.is_file() else None
    record: Dict[str, object] = {"files": files}
    version = _plugin_sw_version(pkg.root)
    if version:
        record["sw_version"] = version
    return record


# --- the report -----------------------------------------------------------------------

@dataclass
class ModuleImport:
    """What the import did with one module."""
    name: str
    definition: str = ""
    plugin: str = ""
    source_epc: Optional[str] = None
    counts: Optional[Dict[str, int]] = None
    unresolved: List[str] = field(default_factory=list)
    pre: str = ""
    conflicts: List[str] = field(default_factory=list)
    exchange_copies: List[str] = field(default_factory=list)
    error: Optional[str] = None


@dataclass
class ImportReport:
    """The import report (design §6.6 ``.history/reports``, SIP R6 report rules)."""
    source: str = ""
    project_file: str = ""
    mode: str = ""
    chip: Optional[str] = None
    library: Optional[str] = None
    exclude: List[str] = field(default_factory=list)
    modules: List[ModuleImport] = field(default_factory=list)
    epc_only: List[ModuleImport] = field(default_factory=list)
    wrapped: List[WrappedMcal] = field(default_factory=list)
    skipped: List[SkippedDir] = field(default_factory=list)
    notices: List[str] = field(default_factory=list)

    def loaded(self) -> List[ModuleImport]:
        return [m for m in self.modules if m.error is None]

    def failed(self) -> List[ModuleImport]:
        return [m for m in self.modules if m.error is not None] + list(self.epc_only)

    def summary_lines(self) -> List[str]:
        """One line per module and per skipped item, for the progress callback and the log."""
        lines = [f"导入完成：{len(self.loaded())} 个模块已导入，{len(self.failed())} 个失败，"
                 f"{len(self.wrapped) + len(self.skipped)} 个目录跳过"]
        for m in self.modules:
            if m.error is not None:
                lines.append(f"  失败 {m.name}：{m.error}")
                continue
            parts = []
            if m.counts is not None:
                parts.append(f"容器 {m.counts['containers']}，参数 {m.counts['parameters']}，"
                             f"引用 {m.counts['references']}")
            else:
                parts.append("无 EPC 值")
            if m.unresolved:
                parts.append(f"未解析引用 {len(m.unresolved)}")
            if m.pre:
                parts.append(m.pre)
            lines.append(f"  {m.name}：" + "；".join(parts))
        for m in self.epc_only:
            lines.append(f"  失败 {m.name}：{m.error}")
        for w in self.wrapped:
            names = ", ".join(_module_of(d) for d, _ in w.modules)
            action = "已列入排除项" if w.name in self.exclude else "未复制进工程"
            lines.append(f"  跳过 MCAL 目录 {w.name}（{names}）：EB 插件已提供，{action}")
        for s in self.skipped:
            lines.append(f"  跳过目录 {s.name}：{s.reason}")
        for notice in self.notices:
            lines.append(f"  注意：{notice}")
        return lines

    def to_markdown(self) -> str:
        project_dir = Path(self.project_file).parent.as_posix() if self.project_file else ""
        lines = ["# EB 工程导入报告", "",
                 f"- 来源：`{self.source}`",
                 f"- 工程目录：`{project_dir}`",
                 f"- 工程文件：`{self.project_file}`",
                 f"- 模式：{self.mode}",
                 f"- 芯片：{self.chip or '未选择'}"]
        if self.library is not None:
            exclude = "、".join(f"`{e}`" for e in self.exclude) or "无"
            lines.append(f"- 插件库：`{self.library}`（eb-plugins），排除：{exclude}")
        else:
            lines.append("- 插件库：无（来源中没有 EB 插件目录）")
        lines += ["", "## 汇总", "", self.summary_lines()[0], ""]

        lines += ["## 模块", ""]
        if not self.modules:
            lines += ["没有插件提供模块。", ""]
        for m in self.modules:
            lines += _module_section(m)

        lines += ["## 跳过的 MCAL 模块", ""]
        if not self.wrapped:
            lines += ["无。", ""]
        for w in self.wrapped:
            action = ("已列入插件库的排除项" if w.name in self.exclude
                      else "未复制进工程")
            lines.append(f"- 目录 `{w.name}`：Vector 包装的 MCAL 定义，与 EB 插件冲突，"
                         f"{action}，不加载：")
            for definition, plugin in w.modules:
                lines.append(f"  - {_module_of(definition)}（`{definition}`），"
                             f"由 EB 插件 `{plugin}` 提供")
        if self.wrapped:
            lines.append("")

        lines += ["## 没有插件的 EPC 模块", ""]
        if not self.epc_only:
            lines += ["无。", ""]
        for m in self.epc_only:
            lines.append(f"- {m.name}：{m.error}")
        if self.epc_only:
            lines.append("")

        lines += ["## 跳过的目录", ""]
        if not self.skipped:
            lines += ["无。", ""]
        for s in self.skipped:
            lines.append(f"- `{s.name}`：{s.reason}")
        if self.skipped:
            lines.append("")

        if self.notices:
            lines += ["## 注意", ""]
            lines += [f"- {n}" for n in self.notices]
            lines.append("")
        return "\n".join(lines)


def _module_of(definition: str) -> str:
    return definition.rstrip("/").rsplit("/", 1)[-1]


def _module_section(m: ModuleImport) -> List[str]:
    lines = [f"### {m.name}", ""]
    if m.plugin:
        lines.append(f"- 插件：`{m.plugin}`（`{m.definition}`）")
    elif m.definition:
        lines.append(f"- 定义：`{m.definition}`")
    if m.error is not None:
        lines.append(f"- **失败**：{m.error}")
    lines.append(f"- EPC：`{m.source_epc}`" if m.source_epc else "- EPC：无（按新模块用基线初始化）")
    if m.counts is not None:
        line = (f"- 导入：容器 {m.counts['containers']}，参数 {m.counts['parameters']}，"
                f"引用 {m.counts['references']}")
        if m.counts.get("unknown"):
            line += f"；定义中没有的参数 {m.counts['unknown']} 个（已保留）"
        lines.append(line)
    if m.error is None:
        lines.append(f"- 未解析引用：{len(m.unresolved)}")
        lines += [f"  - {u}" for u in m.unresolved]
    if m.pre:
        lines.append(f"- 预设（Pre）：{m.pre}")
    if m.conflicts:
        lines.append("- EPC 值与预设不同：")
        lines += [f"  - {c}" for c in m.conflicts]
    if m.exchange_copies:
        lines.append("- 交换副本（未加载）：" + "、".join(f"`{c}`" for c in m.exchange_copies))
    lines.append("")
    return lines


def report_path(project, now: Optional[datetime] = None) -> Path:
    """``<history>/reports/<YYYYmmdd-HHMMSS>_import.md``; ``-2``, ``-3``… when taken."""
    stamp = (now or datetime.now()).strftime("%Y%m%d-%H%M%S")
    directory = project_paths.resolve(project, "history") / "reports"
    path = directory / f"{stamp}_import.md"
    counter = 2
    while path.exists():
        path = directory / f"{stamp}_import-{counter}.md"
        counter += 1
    return path


def write_report(project, report: ImportReport, now: Optional[datetime] = None) -> Path:
    """Write ``report`` under the project's history directory and return the path.

    Raises:
        OSError: the report cannot be written (the import reports it rather than losing it).
    """
    path = report_path(project, now)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(report.to_markdown(), encoding="utf-8")
    return path
