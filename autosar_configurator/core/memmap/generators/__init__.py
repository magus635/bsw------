"""
Linker file generators

One generator per compiler, each reading only a ``plan.Plan`` and returning the text of a
linker file and the file name it is meant to have (design.md D1, D2).  The registry lists
every compiler the tool knows of and says whether it has a generator; asking for one that has
none raises ``UnsupportedCompiler`` and produces no text.
"""
from dataclasses import dataclass
from typing import Callable, Dict, List, Optional, Tuple

from ..plan import Plan

ADS = "ads"
GHS = "ghs"
HIGHTEC = "hightec"
IAR = "iar"
TASKING = "tasking"

NOT_YET = "尚未支持"


class UnsupportedCompiler(ValueError):
    """No generator for the compiler; the message says why."""


@dataclass(frozen=True)
class GeneratedFile:
    compiler: str
    file_name: str          # e.g. scatter.scat
    directory: str          # under IntegrationProject/linkedFile, e.g. Ads
    text: str


@dataclass(frozen=True)
class CompilerEntry:
    key: str
    label: str
    directory: str                                  # under linkedFile
    file_name: str
    generate: Optional[Callable[[Plan], str]] = None
    reason: str = ""                                # why it cannot be chosen, when it cannot

    @property
    def supported(self) -> bool:
        return self.generate is not None


def _registry() -> Tuple[CompilerEntry, ...]:
    from . import ads
    why = "{label} 链接文件的格式还没有读过厂商样例，按 design.md D2 不凭想象生成；在后续变更中做"
    return (
        CompilerEntry(ADS, "ADS (armclang)", "Ads", ads.FILE_NAME, ads.generate),
        CompilerEntry(GHS, "GHS", "Ghs", "link.ld", None, f"{NOT_YET}：" + why.format(label="GHS")),
        CompilerEntry(HIGHTEC, "HighTec", "HighTec", "link.ld", None, f"{NOT_YET}：" + why.format(label="HighTec")),
        CompilerEntry(IAR, "IAR", "Iar", "link.icf", None, f"{NOT_YET}：" + why.format(label="IAR")),
        CompilerEntry(TASKING, "Tasking", "Tasking", "link.lsl", None, f"{NOT_YET}：" + why.format(label="Tasking")),
    )


def compilers() -> List[CompilerEntry]:
    """Every compiler the tool knows of, in the order the window offers them."""
    return list(_registry())


def compiler(key: str) -> CompilerEntry:
    """The registry entry of ``key``.

    Raises:
        UnsupportedCompiler: the tool does not know the compiler
    """
    found: Dict[str, CompilerEntry] = {e.key: e for e in _registry()}
    if key not in found:
        raise UnsupportedCompiler(f"不认识的编译器：{key}（可选 {', '.join(found)}）")
    return found[key]


def generate(key: str, plan: Plan) -> GeneratedFile:
    """The linker file of ``plan`` for compiler ``key``.

    Raises:
        UnsupportedCompiler: the compiler has no generator; no text is produced
    """
    entry = compiler(key)
    if not entry.supported:
        raise UnsupportedCompiler(f"{entry.label} {entry.reason}")
    return GeneratedFile(entry.key, entry.file_name, entry.directory, entry.generate(plan))
