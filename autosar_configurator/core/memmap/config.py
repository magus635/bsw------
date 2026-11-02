"""
Memory layout configuration

The configuration the integrator makes on top of what the scan finds: execution regions
(placed on a window of the chip's physical memory), the rules that put sections into them,
and the exceptions placed by hand.  It is a text file, ``memorymap.json``, in the
``linkedFile`` directory of the project's integration directory, ordered so that two
versions compare cleanly (rule order is the exception: it is the rules' priority).

Three layers::

    section            from the scan, read only
      │ placement      rules, or by hand
    execution region   in this configuration
      │ lies on
    physical memory    the chip's memory_regions, read only

Nothing here removes a placement behind the user's back: a placement whose region is gone
stays, and is shown as "to be placed again".
"""
import json
import os
import re
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional

INTEGRATION_DIR = "IntegrationProject"       # the integration project directory
LINKED_FILE_DIR = "linkedFile"               # where the linker files and this configuration live
CONFIG_FILE = "memorymap.json"
SCHEMA = 1

CODE, CONST, DATA, BSS, NOINIT, STACK, RESERVED = (
    "code", "const", "data", "bss", "noinit", "stack", "reserved")
KINDS = (CODE, CONST, DATA, BSS, NOINIT, STACK, RESERVED)
KIND_LABELS = {CODE: "代码", CONST: "常量", DATA: "已初始化数据", BSS: "清零数据", NOINIT: "未初始化数据",
               STACK: "栈", RESERVED: "保留"}
# which kind of section (TEXT, RODATA, DATA, BSS of the MemMap headers) each region kind takes
_ACCEPTS = {CODE: "TEXT", CONST: "RODATA", DATA: "DATA", BSS: "BSS", NOINIT: "BSS"}

FACTORY, USER = "factory", "user"
REQUIRED_ORIGIN, DEFAULT_ORIGIN = "required", "default"

LIMIT_SUFFIX = "_LIMIT"
_IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


class ConfigError(ValueError):
    """The configuration cannot be read, changed or written as asked; the message says why."""


@dataclass
class ExecRegion:
    """An execution region of the linker file."""
    name: str
    memory: str                     # the physical memory it lies on
    window: str                     # and the window of it, which decides the cache attribute
    kind: str
    order: int                      # position inside its window; decides the AlignExpr chain
    align: int = 64
    required: bool = False          # code refers to it by name: cannot be removed or renamed
    origin: str = USER              # required, default or user
    size_actual: Optional[int] = None       # reserved for a map file; never filled here


@dataclass
class Rule:
    """Sections matching ``match`` (all given conditions) go to ``target``."""
    name: str
    match: Dict[str, Any]
    target: str
    origin: str = USER              # factory or user
    note: str = ""                  # where the rule comes from
    original: Optional[Dict[str, Any]] = None   # a changed factory rule's first form, to compare

    @property
    def changed(self) -> bool:
        return self.original is not None


@dataclass
class MemoryMapConfig:
    chip: str = ""
    regions: List[ExecRegion] = field(default_factory=list)
    rules: List[Rule] = field(default_factory=list)
    manual: Dict[str, str] = field(default_factory=dict)        # section -> region, by hand
    trimmed: List[str] = field(default_factory=list)            # required regions of cores the chip lacks
    options: Dict[str, Any] = field(default_factory=dict)

    # --- regions -----------------------------------------------------------------

    def region(self, name: str) -> Optional[ExecRegion]:
        return next((r for r in self.regions if r.name == name), None)

    def add_region(self, region: ExecRegion) -> None:
        check_region_name(region.name)
        if region.kind not in KINDS:
            raise ConfigError(f"区域 {region.name} 的种类不对：{region.kind}（应为 {', '.join(KINDS)}）")
        if self.region(region.name) is not None:
            raise ConfigError(f"区域 {region.name} 已存在")
        self.regions.append(region)

    def remove_region(self, name: str) -> None:
        """Remove a user region.  The placements that pointed at it stay in the configuration."""
        region = self._existing(name)
        if region.required:
            raise ConfigError(f"区域 {name} 是必需区域（代码按名字引用它），不能删除")
        self.regions.remove(region)

    def rename_region(self, old: str, new: str) -> None:
        region = self._existing(old)
        if region.required:
            raise ConfigError(f"区域 {old} 是必需区域（代码按名字引用它），不能改名")
        check_region_name(new)
        if new != old and self.region(new) is not None:
            raise ConfigError(f"区域 {new} 已存在")
        region.name = new

    def _existing(self, name: str) -> ExecRegion:
        region = self.region(name)
        if region is None:
            raise ConfigError(f"没有区域 {name}")
        return region


def check_region_name(name: str) -> None:
    """A region name becomes a linker symbol, so it has to be an identifier.

    Raises:
        ConfigError: the name cannot be a region name
    """
    if not _IDENTIFIER.match(name or ""):
        raise ConfigError(f"区域名称不对：{name!r}（字母、数字、下划线，不以数字开头）")
    if name.endswith(LIMIT_SUFFIX):
        raise ConfigError(f"区域名称不能以 {LIMIT_SUFFIX} 结尾：{name}（界限区域由生成器自动产出）")


def accepts(kind: str, section_kind: str) -> bool:
    """Whether a region of ``kind`` takes a section of ``section_kind`` (TEXT, RODATA, DATA, BSS)."""
    return _ACCEPTS.get(kind) == section_kind


def refusal(kind: str, section_kind: str) -> str:
    """Why a region of ``kind`` does not take the section; empty when it does."""
    if accepts(kind, section_kind):
        return ""
    if kind == STACK:
        return "栈区域是空区域，不能放段"
    if kind == RESERVED:
        return "保留区域是空区域，不能放段"
    return f"{KIND_LABELS.get(kind, kind)}区域（{kind}）不接收 {section_kind} 段"


# --- the file ----------------------------------------------------------------------------

def config_path(project_dir: Path) -> Path:
    return Path(project_dir) / INTEGRATION_DIR / LINKED_FILE_DIR / CONFIG_FILE


def _region_dict(r: ExecRegion) -> dict:
    data = {"name": r.name, "memory": r.memory, "window": r.window, "kind": r.kind, "order": r.order,
            "align": r.align, "required": r.required, "origin": r.origin}
    if r.size_actual is not None:
        data["size_actual"] = r.size_actual
    return data


def _rule_dict(r: Rule) -> dict:
    data = {"name": r.name, "match": dict(sorted(r.match.items())), "target": r.target, "origin": r.origin}
    if r.note:
        data["note"] = r.note
    if r.original is not None:
        data["original"] = r.original
    return data


def config_dict(config: MemoryMapConfig) -> dict:
    """The configuration as written: regions, manual placements and the rest by name, the
    rules in their own order (it is their priority)."""
    return {
        "schema": SCHEMA,
        "chip": config.chip,
        "options": dict(sorted(config.options.items())),
        "regions": [_region_dict(r) for r in sorted(config.regions, key=lambda r: r.name)],
        "rules": [_rule_dict(r) for r in config.rules],
        "manual": dict(sorted(config.manual.items())),
        "trimmed": sorted(config.trimmed),
    }


def save_config(config: MemoryMapConfig, path: Path) -> None:
    """Write the configuration as text, through a temporary file so that a failure leaves
    the existing file as it was.

    Raises:
        ConfigError: the file could not be written
    """
    path = Path(path)
    text = json.dumps(config_dict(config), ensure_ascii=False, indent=2) + "\n"
    temp = None
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        fd, temp = tempfile.mkstemp(dir=path.parent, prefix=path.name + ".", suffix=".tmp")
        with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as handle:
            handle.write(text)
        os.replace(temp, path)
        temp = None
    except OSError as e:
        raise ConfigError(f"无法写入 {path}：{e}") from e
    finally:
        if temp is not None:
            try:
                os.unlink(temp)
            except OSError:
                pass


def _need(data: dict, key: str, where: str, kind=None):
    if key not in data:
        raise ConfigError(f"{where}缺少 {key}")
    value = data[key]
    if kind is not None and not isinstance(value, kind):
        raise ConfigError(f"{where}的 {key} 类型不对")
    return value


def load_config(path: Path) -> MemoryMapConfig:
    """The configuration in ``path``; an empty one when there is no file (nothing is written).

    Raises:
        ConfigError: the file exists but cannot be read; the message names it
    """
    path = Path(path)
    if not path.is_file():
        return MemoryMapConfig()
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as e:
        raise ConfigError(f"{path.name} 不是有效的 JSON：{e}") from e
    try:
        return _parse(data)
    except ConfigError as e:
        raise ConfigError(f"{path.name}：{e}") from e


def _parse(data: Any) -> MemoryMapConfig:
    if not isinstance(data, dict):
        raise ConfigError("顶层必须是对象")
    if data.get("schema") != SCHEMA:
        raise ConfigError(f"schema 版本不支持：{data.get('schema')!r}（本软件读 {SCHEMA}）")
    regions_data, rules_data, manual = data.get("regions", []), data.get("rules", []), data.get("manual", {})
    if not isinstance(regions_data, list):
        raise ConfigError("regions 必须是列表")
    if not isinstance(rules_data, list):
        raise ConfigError("rules 必须是列表")
    if not isinstance(manual, dict):
        raise ConfigError("manual 必须是对象")
    regions = []
    for index, entry in enumerate(regions_data):
        where = f"regions[{index}]"
        if not isinstance(entry, dict):
            raise ConfigError(f"{where}必须是对象")
        kind = _need(entry, "kind", where, str)
        if kind not in KINDS:
            raise ConfigError(f"{where}的 kind 不对：{kind}")
        regions.append(ExecRegion(
            _need(entry, "name", where, str), str(entry.get("memory", "")), str(entry.get("window", "")), kind,
            int(entry.get("order", 0)), int(entry.get("align", 64)), bool(entry.get("required", False)),
            str(entry.get("origin", USER)), entry.get("size_actual")))
    rules = []
    for index, entry in enumerate(rules_data):
        where = f"rules[{index}]"
        if not isinstance(entry, dict):
            raise ConfigError(f"{where}必须是对象")
        rule_name = _need(entry, "name", where, str)
        target = _need(entry, "target", where, str)          # what a rule is for comes first
        rules.append(Rule(
            rule_name, dict(_need(entry, "match", where, dict)), target, str(entry.get("origin", USER)),
            str(entry.get("note", "")), entry.get("original")))
    return MemoryMapConfig(
        chip=str(data.get("chip", "")), regions=regions, rules=rules,
        manual={str(k): str(v) for k, v in manual.items()}, trimmed=[str(t) for t in data.get("trimmed", [])],
        options=dict(data.get("options", {})))
