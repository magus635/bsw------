"""
Placement rules

A section is placed in an execution region either by hand (an exception) or by the first
rule that matches it.  Priority is simply *manual, then the rules in their list order*; the
rules of a project are its own copy of the factory rules, which the user may change, add to,
remove and reorder, so there is no second level of "default" rules to reason about.

Every section has exactly one status::

    by rule | manual | not placed | to be placed again

"To be placed again" is a placement (manual, or the rule's) whose region is gone or no longer
takes that kind of section, which is what happens after a chip change.  Such a placement is
never dropped: it stays in the configuration and is shown, so nothing the user decided is lost
without them seeing it.
"""
import copy
import fnmatch
from dataclasses import dataclass, field
from typing import Any, Dict, Iterable, List, Optional

from .check import SectionRow
from .config import FACTORY, USER, ConfigError, MemoryMapConfig, Rule, refusal

BY_RULE, MANUAL, NOT_PLACED, AGAIN = "rule", "manual", "not-placed", "again"
STATUS_LABELS = {BY_RULE: "规则", MANUAL: "手动", NOT_PLACED: "未放置", AGAIN: "待重新放置"}
FACTORY_VERSION_KEY = "factory_version"
AGAIN_KEY = "to_place_again"        # in config.options: regions whose window does not fit the chip


def set_window(config: MemoryMapConfig, region_name: str, memory: str, window: str) -> None:
    """Put an execution region on another window; this also clears its "to be placed again" mark.

    Raises:
        ConfigError: there is no such region
    """
    region = config.region(region_name)
    if region is None:
        raise ConfigError(f"没有区域 {region_name}")
    region.memory, region.window = memory, window
    again = [n for n in config.options.get(AGAIN_KEY, []) if n != region_name]
    if again:
        config.options[AGAIN_KEY] = again
    else:
        config.options.pop(AGAIN_KEY, None)


@dataclass(frozen=True)
class Placement:
    section: str
    status: str
    target: Optional[str] = None        # the execution region
    rule: Optional[str] = None          # the rule that placed it, for status "rule"


@dataclass
class RuleInfo:
    matched: int = 0                    # sections this rule places
    shadowed: bool = False              # matches sections, all of which an earlier rule takes
    invalid: str = ""                   # why it cannot place anything, '' when it can


@dataclass
class RestorePreview:
    changed: List[str] = field(default_factory=list)       # factory rules the user changed
    added: List[str] = field(default_factory=list)         # the user's own rules
    removed: List[str] = field(default_factory=list)       # factory rules the user removed

    @property
    def any(self) -> bool:
        return bool(self.changed or self.added or self.removed)


# --- matching ---------------------------------------------------------------------------

def matches(match: Dict[str, Any], row: SectionRow) -> bool:
    """Whether ``row`` meets every condition of ``match`` (an empty match meets any section).

    ``name`` is a pattern (case does not matter, as in the linker file), ``kind`` a list of
    TEXT, RODATA, DATA, BSS, ``core`` a core number or None for a section of no core,
    ``cacheable`` false for a non-cacheable section, ``module`` a module of the section.
    An unknown condition never matches: a typo must not turn a rule into "everything".
    """
    for key, wanted in match.items():
        if key == "name":
            if not fnmatch.fnmatchcase(row.output.lower(), str(wanted).lower()):
                return False
        elif key == "kind":
            kinds = wanted if isinstance(wanted, (list, tuple)) else [wanted]
            if row.kind not in kinds:
                return False
        elif key == "core":
            if row.core != wanted:
                return False
        elif key == "cacheable":
            if (not row.non_cacheable) is not bool(wanted):
                return False
        elif key == "module":
            if wanted not in row.modules:
                return False
        else:
            return False
    return True


def _target_problem(config: MemoryMapConfig, region_name: str, row: SectionRow) -> str:
    region = config.region(region_name)
    if region is None:
        return f"没有区域 {region_name}"
    if region_name in config.options.get(AGAIN_KEY, []):
        return f"区域 {region_name} 所在的窗口在当前芯片上对不上，需要重新选择窗口"
    return refusal(region.kind, row.kind)


# --- placing ------------------------------------------------------------------------------

def place(config: MemoryMapConfig, row: SectionRow) -> Placement:
    """Where ``row`` goes and why."""
    name = row.output
    if name in config.manual:
        target = config.manual[name]
        if _target_problem(config, target, row):
            return Placement(name, AGAIN, target)
        return Placement(name, MANUAL, target)
    for rule in config.rules:
        if not matches(rule.match, row):
            continue
        if rule.target in config.options.get(AGAIN_KEY, []):
            return Placement(name, AGAIN, rule.target, rule.name)     # the rule's region lost its window
        if not _target_problem(config, rule.target, row):
            return Placement(name, BY_RULE, rule.target, rule.name)
    return Placement(name, NOT_PLACED)


def place_all(config: MemoryMapConfig, rows: Iterable[SectionRow]) -> List[Placement]:
    return [place(config, row) for row in sorted(rows, key=lambda r: r.output)]


def check_manual(config: MemoryMapConfig, row: SectionRow, region_name: str) -> str:
    """Why ``row`` cannot be placed by hand in ``region_name``; empty when it can."""
    return _target_problem(config, region_name, row)


def set_manual(config: MemoryMapConfig, row: SectionRow, region_name: str) -> None:
    """Place ``row`` by hand.

    Raises:
        ConfigError: the region does not take it; nothing is stored
    """
    problem = check_manual(config, row, region_name)
    if problem:
        raise ConfigError(problem)
    config.manual[row.output] = region_name


def clear_manual(config: MemoryMapConfig, section: str) -> None:
    config.manual.pop(section, None)


def rule_info(config: MemoryMapConfig, rows: Iterable[SectionRow]) -> Dict[str, RuleInfo]:
    """For each rule: how many sections it places, whether it is shadowed, whether it is invalid.

    A rule is shadowed when it matches sections but an earlier rule takes every one of them.
    """
    rows = list(rows)
    info = {rule.name: RuleInfo() for rule in config.rules}
    taken = set()
    for rule in config.rules:
        entry = info[rule.name]
        region = config.region(rule.target)
        entry.invalid = f"没有区域 {rule.target}" if region is None else ""
        matching = [r for r in rows if matches(rule.match, r)]
        usable = [r for r in matching if not refusal(region.kind, r.kind)] if region is not None else []
        free = [r for r in usable if r.output not in taken]
        entry.matched = len(free)
        entry.shadowed = bool(usable) and not free
        taken.update(r.output for r in free)
    return info


# --- editing the rules -------------------------------------------------------------------------

def _rule(config: MemoryMapConfig, name: str) -> Rule:
    rule = next((r for r in config.rules if r.name == name), None)
    if rule is None:
        raise ConfigError(f"没有规则 {name}")
    return rule


def change_rule(config: MemoryMapConfig, name: str, match: Optional[dict] = None,
                target: Optional[str] = None, note: Optional[str] = None) -> None:
    """Change a rule.  A factory rule keeps its first form in ``original`` (and is marked as
    changed) until it is changed back to it."""
    rule = _rule(config, name)
    if rule.origin == FACTORY and rule.original is None:
        rule.original = {"match": copy.deepcopy(rule.match), "target": rule.target}
    if match is not None:
        rule.match = copy.deepcopy(match)
    if target is not None:
        rule.target = target
    if note is not None:
        rule.note = note
    if rule.original is not None and rule.original == {"match": rule.match, "target": rule.target}:
        rule.original = None


def add_rule(config: MemoryMapConfig, rule: Rule, position: Optional[int] = None) -> None:
    if any(r.name == rule.name for r in config.rules):
        raise ConfigError(f"规则 {rule.name} 已存在")
    rule.origin = USER
    config.rules.insert(len(config.rules) if position is None else max(position, 0), rule)


def remove_rule(config: MemoryMapConfig, name: str) -> None:
    config.rules.remove(_rule(config, name))


def move_rule(config: MemoryMapConfig, name: str, position: int) -> None:
    rule = _rule(config, name)
    config.rules.remove(rule)
    config.rules.insert(min(max(position, 0), len(config.rules)), rule)


# --- the factory rules -----------------------------------------------------------------------------

def install_factory(config: MemoryMapConfig, factory: List[Rule], version: int) -> bool:
    """Copy the factory rules into a project that has no rules and was never given them.

    The copy is the project's own from then on.  Returns whether anything was copied.
    """
    if config.rules or FACTORY_VERSION_KEY in config.options:
        return False
    config.rules = [copy.deepcopy(r) for r in factory]
    config.options[FACTORY_VERSION_KEY] = version
    return True


def factory_update_available(config: MemoryMapConfig, version: int) -> bool:
    """Whether the software ships newer factory rules than the project was given.  Nothing is
    applied: the user chooses whether to take them."""
    given = config.options.get(FACTORY_VERSION_KEY)
    return given is not None and version > given


def restore_preview(config: MemoryMapConfig, factory: List[Rule]) -> RestorePreview:
    """What restoring the factory rules would lose.  The configuration is not changed."""
    preview = RestorePreview()
    factory_names = {r.name for r in factory}
    mine = {r.name: r for r in config.rules}
    for rule in factory:
        have = mine.get(rule.name)
        if have is None:
            preview.removed.append(rule.name)
        elif have.changed or (have.match, have.target) != (rule.match, rule.target):
            preview.changed.append(rule.name)
    preview.added = [r.name for r in config.rules if r.name not in factory_names]
    return preview


def restore_factory(config: MemoryMapConfig, factory: List[Rule]) -> None:
    """Replace the rule list by the factory rules; the manual placements stay."""
    config.rules = [copy.deepcopy(r) for r in factory]
