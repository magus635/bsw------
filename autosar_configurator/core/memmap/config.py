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

AFTER, OFFSET, FIXED = "after", "offset", "fixed"
START_MODES = (AFTER, OFFSET, FIXED)
START_LABELS = {AFTER: "接在上一个区域之后", OFFSET: "窗口起点加偏移", FIXED: "固定地址"}
DEFAULT_LIMIT_ALIGN = 64

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
    start_mode: str = "after"       # after the previous region of the window, window base + offset, or fixed
    offset: int = 0                 # for start_mode "offset"
    address: Optional[int] = None   # for start_mode "fixed"
    size: Optional[int] = None      # upper bound, or the length of a stack/reserved region
    load_region: str = ""           # the load region it belongs to; '' is the first one
    limit_align: int = 64           # alignment of its <name>_LIMIT region


@dataclass
class LoadRegion:
    """A load region of the linker file: where a group of execution regions is loaded from."""
    name: str
    window: str                     # the chip window it starts at
    size: int                       # upper bound


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
    load_regions: List[LoadRegion] = field(default_factory=list)    # in order; empty: one ROM_CODE

    # --- where a region starts, how big, which load region -------------------------

    def set_start(self, name: str, mode: str, offset: int = 0, address: Optional[int] = None) -> None:
        """Choose how region ``name`` starts.

        Raises:
            ConfigError: unknown mode, a negative offset, or a fixed start without an address
        """
        region = self._existing(name)
        if mode not in START_MODES:
            raise ConfigError(f"起点方式不对：{mode}（应为 {', '.join(START_MODES)}）")
        if mode == OFFSET and offset < 0:
            raise ConfigError(f"区域 {name} 的偏移不能为负：{offset}")
        if mode == FIXED and (address is None or address < 0):
            raise ConfigError(f"区域 {name} 选了固定地址，但没有给出地址")
        region.start_mode = mode
        region.offset = offset if mode == OFFSET else 0
        region.address = address if mode == FIXED else None

    def set_size(self, name: str, size: Optional[int]) -> None:
        """Set the region's size, or clear it with None (then the default rule applies)."""
        region = self._existing(name)
        if size is not None and size <= 0:
            raise ConfigError(f"区域 {name} 的大小必须为正数")
        region.size = size

    def set_load_region(self, name: str, load_region: str) -> None:
        region = self._existing(name)
        if load_region and self.load_region(load_region) is None:
            raise ConfigError(f"没有加载区域 {load_region}")
        region.load_region = load_region

    # --- load regions ------------------------------------------------------------------

    def load_region(self, name: str) -> Optional[LoadRegion]:
        return next((l for l in self.load_regions if l.name == name), None)

    def add_load_region(self, load: LoadRegion) -> None:
        if not _IDENTIFIER.match(load.name or ""):
            raise ConfigError(f"加载区域名称不对：{load.name!r}（字母、数字、下划线，不以数字开头）")
        if self.load_region(load.name) is not None:
            raise ConfigError(f"加载区域 {load.name} 已存在")
        if load.size <= 0:
            raise ConfigError(f"加载区域 {load.name} 的大小必须为正数")
        self.load_regions.append(load)

    def rename_load_region(self, old: str, new: str) -> None:
        load = self.load_region(old)
        if load is None:
            raise ConfigError(f"没有加载区域 {old}")
        if not _IDENTIFIER.match(new or ""):
            raise ConfigError(f"加载区域名称不对：{new!r}")
        if new != old and self.load_region(new) is not None:
            raise ConfigError(f"加载区域 {new} 已存在")
        load.name = new
        for region in self.regions:
            if region.load_region == old:
                region.load_region = new

    def remove_load_region(self, name: str) -> None:
        """Remove a load region; its execution regions go back to the first one."""
        load = self.load_region(name)
        if load is None:
            raise ConfigError(f"没有加载区域 {name}")
        self.load_regions.remove(load)
        for region in self.regions:
            if region.load_region == name:
                region.load_region = ""

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


def region_doubts(config: MemoryMapConfig, chip_regions) -> List[str]:
    """What is questionable about where the regions start and how big they are; never stops
    anything (the user may mean it), only listed before generating.

    A fixed address outside the region's window, an offset past the window's end, a size
    larger than the window.
    """
    windows = {r.name: r for r in chip_regions}
    doubts = []
    for region in sorted(config.regions, key=lambda r: r.name):
        window = windows.get(region.window)
        if window is None:
            continue
        if region.start_mode == FIXED and region.address is not None and not window.contains(region.address):
            doubts.append(f"区域 {region.name} 的固定地址 {region.address:#x} 不在窗口 {window.name}"
                          f"（{window.start:#x}–{window.end:#x}）内")
        if region.start_mode == OFFSET and region.offset >= window.size:
            doubts.append(f"区域 {region.name} 的偏移 {region.offset:#x} 超出窗口 {window.name} 的大小 {window.size:#x}")
        if region.size is not None and region.size > window.size:
            doubts.append(f"区域 {region.name} 的大小 {region.size:#x} 超过窗口 {window.name} 的大小 {window.size:#x}")
    return doubts


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
    # the fields of the later change only when they differ from the old behaviour, so that an
    # older configuration is written exactly as before
    if r.start_mode != AFTER:
        data["start_mode"] = r.start_mode
    if r.start_mode == OFFSET:
        data["offset"] = hex(r.offset)
    if r.start_mode == FIXED and r.address is not None:
        data["address"] = hex(r.address)
    if r.size is not None:
        data["size"] = hex(r.size)
    if r.load_region:
        data["load_region"] = r.load_region
    if r.limit_align != DEFAULT_LIMIT_ALIGN:
        data["limit_align"] = r.limit_align
    return data


def _load_dict(l: LoadRegion) -> dict:
    return {"name": l.name, "window": l.window, "size": hex(l.size)}


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
    data = {
        "schema": SCHEMA,
        "chip": config.chip,
        "options": dict(sorted(config.options.items())),
        "regions": [_region_dict(r) for r in sorted(config.regions, key=lambda r: r.name)],
        "rules": [_rule_dict(r) for r in config.rules],
        "manual": dict(sorted(config.manual.items())),
        "trimmed": sorted(config.trimmed),
    }
    if config.load_regions:
        data["load_regions"] = [_load_dict(l) for l in config.load_regions]     # their order matters
    return data


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
        name = _need(entry, "name", where, str)
        start_mode = str(entry.get("start_mode", AFTER))
        if start_mode not in START_MODES:
            raise ConfigError(f"{where}的 start_mode 不对：{start_mode}")
        offset = _number(entry.get("offset", 0), where, "offset")
        if offset < 0:
            raise ConfigError(f"{where}的 offset 不能为负")
        address = _number(entry["address"], where, "address") if "address" in entry else None
        if start_mode == FIXED and address is None:
            raise ConfigError(f"{where}选了固定地址，但没有 address")
        size = _number(entry["size"], where, "size") if "size" in entry else None
        if size is not None and size <= 0:
            raise ConfigError(f"{where}的 size 必须为正数")
        limit_align = int(entry.get("limit_align", DEFAULT_LIMIT_ALIGN))
        if limit_align <= 0:
            raise ConfigError(f"{where}的 limit_align 必须为正数")
        regions.append(ExecRegion(
            name, str(entry.get("memory", "")), str(entry.get("window", "")), kind,
            int(entry.get("order", 0)), int(entry.get("align", 64)), bool(entry.get("required", False)),
            str(entry.get("origin", USER)), entry.get("size_actual"), start_mode, offset, address, size,
            str(entry.get("load_region", "")), limit_align))
    load_regions = []
    for index, entry in enumerate(data.get("load_regions", [])):
        where = f"load_regions[{index}]"
        if not isinstance(entry, dict):
            raise ConfigError(f"{where}必须是对象")
        load_regions.append(LoadRegion(_need(entry, "name", where, str), _need(entry, "window", where, str),
                                       _number(_need(entry, "size", where), where, "size")))
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
        options=dict(data.get("options", {})), load_regions=load_regions)


def _number(value: Any, where: str, key: str) -> int:
    """A number written as hex text (``"0x1000"``) or as an integer."""
    if isinstance(value, bool):
        raise ConfigError(f"{where}的 {key} 不是数字")
    if isinstance(value, int):
        return value
    try:
        return int(str(value).strip(), 0)
    except ValueError:
        raise ConfigError(f"{where}的 {key} 不是数字：{value!r}") from None
