"""
Factory rules and layout per chip

The factory data of a chip is a JSON file in ``autosar_configurator/data/memmap/<chip>_default.json``
with the chip's default layout (the execution regions the vendor's linker script has, with their
window and order) and the initial rules.  A chip without such a file has none: its sections show
as not placed and the user writes rules or places by hand.

Opening the configuration page of a project the first time copies the factory rules into the
project's own configuration (``rules.install_factory``); the files here are never changed by the
user, and a newer file never overwrites a project's copy.
"""
import json
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional

from .config import (
    AFTER,
    DEFAULT_LIMIT_ALIGN,
    FACTORY,
    REQUIRED_ORIGIN,
    ConfigError,
    ExecRegion,
    LoadRegion,
    MemoryMapConfig,
    Rule,
)
from .regions import FROM_CODE, RequiredRegions, merge_required, required_regions
from .rules import install_factory

DATA_DIR = Path(__file__).resolve().parent.parent.parent / "data" / "memmap"
FILE_SUFFIX = "_default.json"
FACTORY_NOTE = "出厂初始规则与布局只是起点：生成的链接文件以这里的配置为准，可以直接修改"


@dataclass
class FactoryData:
    chip: str
    version: int = 1
    note: str = ""
    layout: List[dict] = field(default_factory=list)
    rules: List[Rule] = field(default_factory=list)
    load_regions: List[dict] = field(default_factory=list)


def factory_path(chip: str, directory: Optional[Path] = None) -> Path:
    return Path(directory or DATA_DIR) / f"{chip}{FILE_SUFFIX}"


def load_factory(chip: str, directory: Optional[Path] = None) -> Optional[FactoryData]:
    """The factory data of ``chip``, or None when the chip has none.

    Raises:
        ConfigError: the file exists but is damaged (the software's own data: report, do not hide)
    """
    path = factory_path(chip, directory)
    if not chip or not path.is_file():
        return None
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as e:
        raise ConfigError(f"出厂数据 {path.name} 无法读取：{e}") from e
    if not isinstance(data, dict) or data.get("chip") != chip:
        raise ConfigError(f"出厂数据 {path.name} 的芯片不是 {chip}")
    rules = []
    for index, entry in enumerate(data.get("rules", [])):
        for key in ("name", "match", "target"):
            if key not in entry:
                raise ConfigError(f"出厂数据 {path.name} 的 rules[{index}] 缺少 {key}")
        rules.append(Rule(entry["name"], dict(entry["match"]), entry["target"], origin=FACTORY,
                          note=entry.get("note", "")))
    return FactoryData(chip, int(data.get("version", 1)), str(data.get("note", "")),
                       list(data.get("layout", [])), rules, list(data.get("load_regions", [])))


def layout_region(entry: dict, origin: str = REQUIRED_ORIGIN, required: bool = True) -> ExecRegion:
    """One entry of a factory layout as an execution region.

    Besides the window, order and kind the entry may say how the region starts (``start_mode``
    with ``offset`` or ``address``), how big it is (``size``), which load region it is in
    (``load_region``) and the alignment of its limit region (``limit_align``); numbers may be
    hex text.  A missing field means the default.
    """
    def number(key, default=None):
        value = entry.get(key, default)
        return int(str(value), 0) if value is not None and not isinstance(value, int) else value

    kind = entry["kind"]
    return ExecRegion(
        entry["name"], entry.get("memory", ""), entry.get("window", ""), kind, int(entry.get("order", 0)),
        int(entry.get("align", 8 if kind == "stack" else 64)), required=required, origin=origin,
        start_mode=entry.get("start_mode", AFTER), offset=number("offset", 0) or 0,
        address=number("address"), size=number("size"), load_region=entry.get("load_region", ""),
        limit_align=int(entry.get("limit_align", DEFAULT_LIMIT_ALIGN)))


def factory_regions(factory: FactoryData) -> List[ExecRegion]:
    """The factory layout as execution regions (all of them required: the vendor's names)."""
    return [layout_region(e) for e in factory.layout]


def factory_load_regions(factory: FactoryData) -> List[LoadRegion]:
    return [LoadRegion(e["name"], e["window"], int(str(e["size"]), 0)) for e in factory.load_regions]


def prepare(config: MemoryMapConfig, chip: str, needs, cores: Optional[int],
            directory: Optional[Path] = None) -> "Prepared":
    """Bring ``config`` up for ``chip``: the required regions from the code (or the factory
    layout), the factory rules if the project never had any.  Changes ``config`` in place.
    """
    factory = load_factory(chip, directory)
    layout = factory.layout if factory else None
    result = required_regions(needs, cores, layout)
    gone = merge_required(config, result)
    config.chip = chip
    installed = False
    if factory:
        installed = install_factory(config, factory.rules, factory.version)
        if not config.load_regions:
            # the factory load regions come with the project's first copy, like the rules;
            # afterwards they are the project's own
            for load in factory_load_regions(factory):
                config.load_regions.append(load)
    return Prepared(factory, result, gone, installed)


@dataclass
class Prepared:
    factory: Optional[FactoryData]
    required: RequiredRegions
    no_longer_needed: List[str]
    rules_installed: bool

    def notes(self) -> List[str]:
        """What the window should tell the user about where the data came from."""
        notes = [self.required.source_note()]
        if self.factory is None:
            notes.append("这个芯片没有出厂规则：所有段显示为未放置，请自己写规则或手动放置")
        else:
            notes.append(FACTORY_NOTE)
        if self.required.trimmed:
            notes.append("芯片没有这些核，区域不在配置里显示，生成时可按选项写成保留区域："
                         + "、".join(self.required.trimmed))
        return notes
