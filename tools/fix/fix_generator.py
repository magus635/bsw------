"""
修复建议生成器 — 根据根因 trace JSON 生成针对渲染引擎的修复建议。

输入：eval_tracer 输出的根因 JSON (List[TraceEvent])
      可选：DiffReport JSON（关联 diff 上下文）
      可选：SourceMap JSON（模板行号 → 输出行号映射）

输出：修复建议 JSON，指明引擎中需要改动的组件 / 函数 / 逻辑

硬性约束：只修改渲染引擎代码，不修改任何模板文件。

Usage:
    from tools.fix.fix_generator import FixGenerator

    fixes = FixGenerator(
        trace_path="/tmp/os_trace.json",
        diff_path="/tmp/os_diff.json",       # optional
        source_map_path="/tmp/source_map.json",  # optional
    ).generate()

    fixes.dump("/tmp/fixes.json")
"""

from __future__ import annotations

import json
from dataclasses import dataclass, field, asdict
from enum import Enum
from pathlib import Path
from typing import Any, Dict, List, Optional


# ---------------------------------------------------------------------------
# 渲染引擎组件枚举
# ---------------------------------------------------------------------------

class EngineComponent(Enum):
    XPATH_ENGINE   = "xpath_engine"      # XPathEngine — XPath 求值 & loop index
    SYMBOL_TABLE   = "symbol_table"      # SymbolTable — 引用路径解析
    BUILTINS       = "builtins"          # BuiltinFunctions — node:ref / node:order
    RENDERER       = "renderer"          # Renderer — 模板渲染主循环
    CONTEXT        = "context"           # ExecutionContext / ContextStack
    OVERLAY_ENGINE = "overlay_engine"    # OverlayEngine — 多配置叠加


class FixCategory(Enum):
    LOOP_INDEX      = "loop_index"       # @index 解析错误
    REF_RESOLUTION  = "ref_resolution"   # 引用路径解析错误
    NODE_ORDER      = "node_order"       # 节点排序逻辑错误
    VALUE_EVAL      = "value_eval"       # 值求值 / 类型转换错误
    MISSING_OUTPUT  = "missing_output"   # 缺少输出行
    EXTRA_OUTPUT    = "extra_output"     # 多余输出行
    CAST_HANDLING   = "cast_handling"    # 类型强转处理
    CORE_DISPATCH   = "core_dispatch"    # 多核分发逻辑错误
    COUNTER_BINDING = "counter_binding"  # 计数器绑定错误


class Confidence(Enum):
    HIGH   = "high"       # 根因定位精确
    MEDIUM = "medium"     # 有强关联但未完全确认
    LOW    = "low"        # 推测性


# ---------------------------------------------------------------------------
# 数据模型
# ---------------------------------------------------------------------------

@dataclass
class FixSuggestion:
    fix_id: str                        # 唯一 ID, 如 "FIX-001"
    category: FixCategory
    component: EngineComponent         # 应修改的引擎组件
    target_function: str               # 建议修改的函数名
    confidence: Confidence

    description: str                   # 人类可读的问题描述
    root_cause: str                    # 根因分析
    suggested_fix: str                 # 建议的修改方案

    # 关联的 trace 事件序号
    related_trace_seqs: List[int] = field(default_factory=list)
    # 关联的 diff IDs
    related_diff_ids: List[str] = field(default_factory=list)

    # trace 事件中的关键上下文
    context_snapshot: Dict[str, Any] = field(default_factory=dict)

    def to_dict(self) -> dict:
        d = asdict(self)
        d["category"]  = self.category.value
        d["component"] = self.component.value
        d["confidence"] = self.confidence.value
        return d


@dataclass
class FixReport:
    trace_path: str
    diff_path: str = ""
    suggestions: List[FixSuggestion] = field(default_factory=list)

    # 统计
    total_trace_events: int = 0
    total_diff_items: int = 0

    @property
    def high_confidence(self) -> List[FixSuggestion]:
        return [s for s in self.suggestions if s.confidence == Confidence.HIGH]

    @property
    def by_component(self) -> Dict[str, List[FixSuggestion]]:
        groups: Dict[str, List[FixSuggestion]] = {}
        for s in self.suggestions:
            key = s.component.value
            groups.setdefault(key, []).append(s)
        return groups

    def summary(self) -> str:
        lines = [
            "=== FixReport ===",
            f"  Trace events : {self.total_trace_events}",
            f"  Diff items   : {self.total_diff_items}",
            f"  Suggestions  : {len(self.suggestions)}",
            f"    HIGH       : {len(self.high_confidence)}",
        ]
        for comp, fixes in self.by_component.items():
            lines.append(f"  [{comp}] {len(fixes)} fix(es)")
            for f in fixes[:3]:
                lines.append(f"    {f.fix_id} [{f.category.value}] {f.description[:60]}")
            if len(fixes) > 3:
                lines.append(f"    ... and {len(fixes) - 3} more")
        return "\n".join(lines)

    def to_json(self, indent: int = 2) -> str:
        data = {
            "trace_path":         self.trace_path,
            "diff_path":          self.diff_path,
            "total_trace_events": self.total_trace_events,
            "total_diff_items":   self.total_diff_items,
            "suggestions":        [s.to_dict() for s in self.suggestions],
        }
        return json.dumps(data, indent=indent, ensure_ascii=False)

    def dump(self, path: str) -> None:
        p = Path(path)
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(self.to_json(), encoding='utf-8')
        print(f"[FixGenerator] {len(self.suggestions)} suggestions → {path}")


# ---------------------------------------------------------------------------
# 引擎函数 → 组件 / 类别 映射
# ---------------------------------------------------------------------------

_FN_MAPPING: Dict[str, tuple[EngineComponent, FixCategory, str]] = {
    "_find_context_loop_index": (
        EngineComponent.XPATH_ENGINE,
        FixCategory.LOOP_INDEX,
        "XPathEngine._find_context_loop_index",
    ),
    "resolve_reference": (
        EngineComponent.SYMBOL_TABLE,
        FixCategory.REF_RESOLUTION,
        "SymbolTable.resolve_reference",
    ),
    "node_ref": (
        EngineComponent.BUILTINS,
        FixCategory.REF_RESOLUTION,
        "BuiltinFunctions.node_ref",
    ),
    "node_order": (
        EngineComponent.BUILTINS,
        FixCategory.NODE_ORDER,
        "BuiltinFunctions.node_order",
    ),
}

# DiffType → FixCategory 映射
_DIFF_TYPE_CATEGORY: Dict[str, FixCategory] = {
    "wrong_value":       FixCategory.VALUE_EVAL,
    "wrong_counter_ref": FixCategory.COUNTER_BINDING,
    "wrong_core_ref":    FixCategory.CORE_DISPATCH,
    "wrong_identifier":  FixCategory.REF_RESOLUTION,
    "missing_lines":     FixCategory.MISSING_OUTPUT,
    "extra_lines":       FixCategory.EXTRA_OUTPUT,
    "extra_cast":        FixCategory.CAST_HANDLING,
}


# ---------------------------------------------------------------------------
# FixGenerator
# ---------------------------------------------------------------------------

class FixGenerator:
    def __init__(
        self,
        trace_path: str,
        diff_path: str = "",
        source_map_path: str = "",
    ):
        self.trace_path = trace_path
        self.diff_path = diff_path
        self.source_map_path = source_map_path
        self._trace_events: List[dict] = []
        self._diff_items: List[dict] = []
        self._source_map: List[dict] = []   # source map entries
        self._fix_counter = 0

    # ---- Public API ----

    def generate(self) -> FixReport:
        """主入口：加载数据 → 分析 → 输出修复建议。"""
        self._load()

        report = FixReport(
            trace_path=self.trace_path,
            diff_path=self.diff_path,
            total_trace_events=len(self._trace_events),
            total_diff_items=len(self._diff_items),
        )

        # 1. 分析 trace 事件中的异常模式
        report.suggestions.extend(self._analyze_loop_index_anomalies())
        report.suggestions.extend(self._analyze_ref_resolution_failures())
        report.suggestions.extend(self._analyze_node_order_issues())

        # 2. 关联 diff items，补充修复建议
        if self._diff_items:
            report.suggestions.extend(self._analyze_diff_driven_fixes())

        # 3. 去重 & 按 confidence 排序
        report.suggestions = self._deduplicate(report.suggestions)
        report.suggestions.sort(
            key=lambda s: (
                {"high": 0, "medium": 1, "low": 2}[s.confidence.value],
                s.component.value,
            )
        )

        return report

    # ---- 数据加载 ----

    def _load(self) -> None:
        trace_p = Path(self.trace_path)
        if trace_p.exists():
            self._trace_events = json.loads(trace_p.read_text(encoding='utf-8'))
            print(f"[FixGenerator] Loaded {len(self._trace_events)} trace events")
        else:
            print(f"[FixGenerator] WARNING: trace file not found: {self.trace_path}")

        if self.diff_path:
            diff_p = Path(self.diff_path)
            if diff_p.exists():
                diff_data = json.loads(diff_p.read_text(encoding='utf-8'))
                # DiffReport JSON 中 files → items
                for fd in diff_data.get("files", []):
                    for item in fd.get("items", []):
                        item["_file_path"] = fd.get("file_path", "")
                        self._diff_items.append(item)
                print(f"[FixGenerator] Loaded {len(self._diff_items)} diff items")
            else:
                print(f"[FixGenerator] WARNING: diff file not found: {self.diff_path}")

        if self.source_map_path:
            smap_p = Path(self.source_map_path)
            if smap_p.exists():
                smap_data = json.loads(smap_p.read_text(encoding='utf-8'))
                self._source_map = smap_data.get("source_map", [])
                print(f"[FixGenerator] Loaded {len(self._source_map)} source map entries")
            else:
                print(f"[FixGenerator] WARNING: source map not found: {self.source_map_path}")

    # ---- 核心分析 ----

    def _next_id(self) -> str:
        self._fix_counter += 1
        return f"FIX-{self._fix_counter:03d}"

    def _analyze_loop_index_anomalies(self) -> List[FixSuggestion]:
        """
        检测 _find_context_loop_index 的异常：
        - match_reason = "no_match" 且 fallback 被使用
        - match_reason = "fallback" (scope 中找不到 node，退回 node.index)
        - 同一个 context_path 下 index 值跳变
        """
        fixes: List[FixSuggestion] = []
        loop_events = [
            e for e in self._trace_events
            if e.get("fn") == "_find_context_loop_index"
        ]

        if not loop_events:
            return fixes

        # 1. fallback / no_match 事件
        fallback_events = [
            e for e in loop_events
            if e.get("match_reason") in ("fallback", "no_match")
        ]
        if fallback_events:
            # 按 context_path 分组
            by_ctx: Dict[str, List[dict]] = {}
            for e in fallback_events:
                ctx = e.get("context_path", "<unknown>")
                by_ctx.setdefault(ctx, []).append(e)

            for ctx_path, events in by_ctx.items():
                reasons = {e.get("match_reason") for e in events}
                seqs = [e["seq"] for e in events]

                fixes.append(FixSuggestion(
                    fix_id=self._next_id(),
                    category=FixCategory.LOOP_INDEX,
                    component=EngineComponent.XPATH_ENGINE,
                    target_function="XPathEngine._find_context_loop_index",
                    confidence=Confidence.HIGH if "no_match" in reasons else Confidence.MEDIUM,
                    description=(
                        f"loop index 在 context '{ctx_path}' 下使用了 fallback 路径 "
                        f"({len(events)} 次)"
                    ),
                    root_cause=(
                        f"context_stack 中没有找到与目标 node 匹配的 loop scope。"
                        f"match_reasons: {reasons}。"
                        f"可能原因：(1) scope push 时未正确关联 context_node；"
                        f"(2) wrapper node 未被正确穿透；"
                        f"(3) parent chain 断裂。"
                    ),
                    suggested_fix=(
                        "检查 _find_context_loop_index 中 scope 遍历逻辑：\n"
                        "  1. 确认 context_stack._stack 中每个 scope 的 context_node "
                        "     与实际 loop 变量正确关联\n"
                        "  2. 检查 is_wrapper 属性的穿透逻辑是否覆盖所有 wrapper 类型\n"
                        "  3. 考虑添加 grandparent 匹配作为第三级 fallback"
                    ),
                    related_trace_seqs=seqs[:20],
                    context_snapshot={
                        "context_path": ctx_path,
                        "sample_event": events[0],
                    },
                ))

        # 2. 同一 context 下 index 跳变
        by_input: Dict[str, List[dict]] = {}
        for e in loop_events:
            key = e.get("input_repr", "")
            by_input.setdefault(key, []).append(e)

        for input_key, events in by_input.items():
            indices = [e.get("result_index", -1) for e in events]
            valid = [i for i in indices if i >= 0]
            if len(set(valid)) > 1 and len(valid) >= 2:
                # 同一个 input 返回了不同的 index — 正常情况（loop 迭代）
                # 但如果 result_index 不递增，说明可能有问题
                is_monotonic = all(
                    valid[i] <= valid[i + 1] for i in range(len(valid) - 1)
                )
                if not is_monotonic:
                    fixes.append(FixSuggestion(
                        fix_id=self._next_id(),
                        category=FixCategory.LOOP_INDEX,
                        component=EngineComponent.XPATH_ENGINE,
                        target_function="XPathEngine._find_context_loop_index",
                        confidence=Confidence.MEDIUM,
                        description=(
                            f"同一 input '{input_key[:50]}' 的 loop index 非单调递增：{valid[:10]}"
                        ),
                        root_cause=(
                            "同一节点在多次 _find_context_loop_index 调用中返回了非顺序的 index，"
                            "可能是 scope 被错误复用或 loop_count 未正确更新。"
                        ),
                        suggested_fix=(
                            "检查 context_stack 的 push/pop 是否对称，确保每次 loop 迭代"
                            "都正确更新 loop_index 和 loop_count。"
                        ),
                        related_trace_seqs=[e["seq"] for e in events[:10]],
                    ))

        return fixes

    def _analyze_ref_resolution_failures(self) -> List[FixSuggestion]:
        """
        检测引用解析异常：
        - resolve_reference 返回 None
        - node_ref 返回 None（路径不存在）
        """
        fixes: List[FixSuggestion] = []

        # resolve_reference failures
        ref_events = [
            e for e in self._trace_events
            if e.get("fn") == "resolve_reference"
        ]
        failed_refs = [
            e for e in ref_events
            if e.get("result_repr") == "None" or e.get("result_path") == ""
        ]
        if failed_refs:
            # 按 input_repr（引用路径）分组
            by_path: Dict[str, List[dict]] = {}
            for e in failed_refs:
                by_path.setdefault(e.get("input_repr", "?"), []).append(e)

            for ref_path, events in by_path.items():
                fixes.append(FixSuggestion(
                    fix_id=self._next_id(),
                    category=FixCategory.REF_RESOLUTION,
                    component=EngineComponent.SYMBOL_TABLE,
                    target_function="SymbolTable.resolve_reference",
                    confidence=Confidence.HIGH,
                    description=(
                        f"引用路径 '{ref_path}' 解析失败 ({len(events)} 次)"
                    ),
                    root_cause=(
                        f"SymbolTable.resolve_reference 无法找到路径 '{ref_path}'。"
                        f"可能原因：(1) symbol table 中未注册该路径；"
                        f"(2) 路径格式不匹配（斜杠 / 大小写 / 缩写）；"
                        f"(3) 节点未被正确加载到 symbol table。"
                    ),
                    suggested_fix=(
                        "在 SymbolTable.resolve_reference 中增加路径规范化逻辑，"
                        "或检查 symbol table 的注册时是否遗漏了相关节点。"
                    ),
                    related_trace_seqs=[e["seq"] for e in events[:10]],
                    context_snapshot={
                        "ref_path": ref_path,
                        "count": len(events),
                    },
                ))

        # node_ref failures
        noderef_events = [
            e for e in self._trace_events
            if e.get("fn") == "node_ref"
        ]
        failed_noderefs = [
            e for e in noderef_events
            if e.get("result_repr") == "None" or e.get("result_path") == ""
        ]
        if failed_noderefs:
            by_input: Dict[str, List[dict]] = {}
            for e in failed_noderefs:
                by_input.setdefault(e.get("input_repr", "?"), []).append(e)

            for inp, events in by_input.items():
                fixes.append(FixSuggestion(
                    fix_id=self._next_id(),
                    category=FixCategory.REF_RESOLUTION,
                    component=EngineComponent.BUILTINS,
                    target_function="BuiltinFunctions.node_ref",
                    confidence=Confidence.HIGH,
                    description=(
                        f"node:ref('{inp}') 返回 None ({len(events)} 次)"
                    ),
                    root_cause=(
                        f"node:ref() 无法解析输入 '{inp}'。"
                        f"如果 input 以 'str:' 开头，说明传入的是字符串路径；"
                        f"以 'node:' 开头说明传入的是节点对象。"
                        f"检查 builtins.py 中 node_ref 的路径查找链。"
                    ),
                    suggested_fix=(
                        "检查 BuiltinFunctions.node_ref 的实现：\n"
                        "  1. 字符串路径时是否正确委托给 symbol_table.resolve_reference\n"
                        "  2. 节点对象时是否正确返回节点本身\n"
                        "  3. 路径中是否包含模板变量未展开的部分"
                    ),
                    related_trace_seqs=[e["seq"] for e in events[:10]],
                    context_snapshot={
                        "input": inp,
                        "sample_loop_scopes": events[0].get("loop_scopes", []),
                    },
                ))

        return fixes

    def _analyze_node_order_issues(self) -> List[FixSuggestion]:
        """
        检测 node_order (排序) 异常：
        - 排序后顺序与预期不一致
        - sort_expr 为空但期望排序
        """
        fixes: List[FixSuggestion] = []
        order_events = [
            e for e in self._trace_events
            if e.get("fn") == "node_order"
        ]

        if not order_events:
            return fixes

        # 检测 input 和 result 的 index 序列是否一致
        for e in order_events:
            inp_repr = e.get("input_repr", "")
            res_repr = e.get("result_repr", "")
            sort_expr = e.get("input_extra", "")

            # 如果 input 和 result 不一致，说明排序改变了顺序
            if inp_repr != res_repr and inp_repr and res_repr:
                fixes.append(FixSuggestion(
                    fix_id=self._next_id(),
                    category=FixCategory.NODE_ORDER,
                    component=EngineComponent.BUILTINS,
                    target_function="BuiltinFunctions.node_order",
                    confidence=Confidence.LOW,
                    description=(
                        f"node_order 改变了节点顺序 (sort_expr={sort_expr!r})"
                    ),
                    root_cause=(
                        f"排序表达式 '{sort_expr}' 导致节点重排。"
                        f"Before: {inp_repr[:60]}; After: {res_repr[:60]}。"
                        f"若最终输出顺序错误，根因在排序逻辑。"
                    ),
                    suggested_fix=(
                        "检查 BuiltinFunctions.node_order 中 sort_expr 的求值逻辑，"
                        "确认排序比较器是否正确处理了数值 vs 字符串比较。"
                    ),
                    related_trace_seqs=[e["seq"]],
                    context_snapshot={
                        "sort_expr": sort_expr,
                        "input": inp_repr[:100],
                        "result": res_repr[:100],
                    },
                ))
                # 只报告前几个避免噪音
                if len(fixes) >= 5:
                    break

        return fixes

    def _analyze_diff_driven_fixes(self) -> List[FixSuggestion]:
        """
        从 diff items 出发，结合 trace 信息推断引擎修复点。
        """
        fixes: List[FixSuggestion] = []

        # 只关注 blocking severity 的 diff items
        blocking = [
            d for d in self._diff_items
            if d.get("severity") == "blocking"
        ]

        # 按 diff_type 分组
        by_type: Dict[str, List[dict]] = {}
        for d in blocking:
            by_type.setdefault(d.get("diff_type", "unknown"), []).append(d)

        for diff_type, items in by_type.items():
            category = _DIFF_TYPE_CATEGORY.get(diff_type)
            if not category:
                continue

            # 推断涉及的引擎组件
            component, target_fn = self._infer_component_for_diff(diff_type, items)

            sample = items[0]
            expected = sample.get("expected_content", "").strip()
            actual = sample.get("actual_content", "").strip()

            # 通过 source map 反查模板位置
            gen_line = sample.get("line_in_generated", 0)
            source_location = self._lookup_source_map(gen_line) if gen_line > 0 else {}

            ctx_snapshot: Dict[str, Any] = {
                "diff_type": diff_type,
                "count": len(items),
                "sample_file": sample.get("_file_path", ""),
                "sample_line_ref": sample.get("line_in_reference", 0),
                "sample_line_gen": gen_line,
            }
            if source_location:
                ctx_snapshot["source_location"] = source_location

            fixes.append(FixSuggestion(
                fix_id=self._next_id(),
                category=category,
                component=component,
                target_function=target_fn,
                confidence=Confidence.MEDIUM,
                description=(
                    f"{diff_type}: {len(items)} 处差异 "
                    f"(e.g. expected={expected!r}, actual={actual!r})"
                ),
                root_cause=self._infer_root_cause(diff_type, items),
                suggested_fix=self._infer_suggested_fix(diff_type, items),
                related_diff_ids=[d.get("diff_id", "") for d in items[:10]],
                context_snapshot=ctx_snapshot,
            ))

        return fixes

    # ---- Source Map 查询 ----

    def _lookup_source_map(self, output_line: int, tolerance: int = 2) -> Dict[str, Any]:
        """
        通过输出行号反查 source map，找到对应的模板文件位置和 config xpath。
        返回 {template_file, template_line, context_xpath, directive} 或空 dict。
        """
        if not self._source_map:
            return {}

        # 精确匹配
        for entry in self._source_map:
            if entry.get("output_line") == output_line:
                return {
                    "template_file": entry.get("template_file", ""),
                    "template_line": entry.get("template_line", 0),
                    "context_xpath": entry.get("context_xpath", ""),
                    "directive": entry.get("directive", ""),
                    "token_type": entry.get("token_type", ""),
                }

        # 容忍范围内最近匹配
        best = None
        best_dist = tolerance + 1
        for entry in self._source_map:
            dist = abs(entry.get("output_line", 0) - output_line)
            if dist <= tolerance and dist < best_dist:
                best = entry
                best_dist = dist

        if best:
            return {
                "template_file": best.get("template_file", ""),
                "template_line": best.get("template_line", 0),
                "context_xpath": best.get("context_xpath", ""),
                "directive": best.get("directive", ""),
                "token_type": best.get("token_type", ""),
                "_approx": True,
            }

        return {}

    # ---- 推断辅助 ----

    def _infer_component_for_diff(
        self, diff_type: str, items: List[dict]
    ) -> tuple[EngineComponent, str]:
        """根据 diff_type 推断最可能需要修改的引擎组件。"""
        mapping = {
            "wrong_value":       (EngineComponent.XPATH_ENGINE,   "XPathEngine — 值求值逻辑"),
            "wrong_counter_ref": (EngineComponent.SYMBOL_TABLE,   "SymbolTable — Counter 引用绑定"),
            "wrong_core_ref":    (EngineComponent.XPATH_ENGINE,   "XPathEngine — Core ID 分发"),
            "wrong_identifier":  (EngineComponent.SYMBOL_TABLE,   "SymbolTable — 标识符解析"),
            "missing_lines":     (EngineComponent.RENDERER,       "Renderer — 条件分支 / loop 控制"),
            "extra_lines":       (EngineComponent.RENDERER,       "Renderer — 条件分支 / loop 控制"),
            "extra_cast":        (EngineComponent.BUILTINS,       "BuiltinFunctions — 类型处理"),
        }
        return mapping.get(diff_type, (EngineComponent.RENDERER, "Renderer — 未分类"))

    def _infer_root_cause(self, diff_type: str, items: List[dict]) -> str:
        """根据 diff_type 和具体差异内容推断根因。"""
        causes = {
            "wrong_value": (
                "引擎在求值数值表达式时产生了错误的结果。"
                "可能是：(1) XPath 表达式中的 @index 解析错误；"
                "(2) 数值常量的 suffix (UL/U/L) 处理不一致；"
                "(3) 宏展开时取错了配置值。"
            ),
            "wrong_counter_ref": (
                "Counter 引用绑定到了错误的 ID。"
                "可能是 symbol_table 中 APPLICATION_COUNTER*_ID_MASK 的注册顺序"
                "与模板期望的 XPath 选择顺序不一致。"
            ),
            "wrong_core_ref": (
                "多核配置下取错了 Core ID。"
                "可能是 XPathEngine 在遍历多核配置时，"
                "loop scope 的 context_node 没有正确切换到目标 core。"
            ),
            "wrong_identifier": (
                "标名符解析不正确，可能是 symbol_table 的路径匹配"
                "在模糊查找时选错了候选项。"
            ),
            "missing_lines": (
                "参考代码中有但生成代码中没有的行。"
                "可能是：(1) 模板中的 [!IF] / [!LOOP] 条件不满足；"
                "(2) 配置节点未被正确加载；"
                "(3) renderer 跳过了某个分支。"
            ),
            "extra_lines": (
                "生成代码有多余行。"
                "可能是：(1) [!IF] 条件误判为 true；"
                "(2) [!LOOP] 迭代了不该迭代的节点；"
                "(3) overlay 叠加了不应该出现的配置。"
            ),
            "extra_cast": (
                "生成代码中多了 (uint32) 强制类型转换。"
                "这通常是 builtins 中的类型推断逻辑过于保守，"
                "对已经是 uint32 类型的值仍然添加了 cast。"
            ),
        }
        return causes.get(diff_type, f"diff_type={diff_type}: 未分类差异，需人工审查。")

    def _infer_suggested_fix(self, diff_type: str, items: List[dict]) -> str:
        """根据 diff_type 生成具体的修复建议。"""
        suggestions = {
            "wrong_value": (
                "1. 检查 XPathEngine 中数值表达式的求值逻辑\n"
                "2. 对比 trace 中 _find_context_loop_index 的 result_index 与预期值\n"
                "3. 确认配置节点的值是否正确加载"
            ),
            "wrong_counter_ref": (
                "1. 检查 SymbolTable 中 Counter 节点的注册顺序\n"
                "2. 确认 XPath 中对 Counter 子节点的选择是否使用了正确的路径\n"
                "3. 检查是否存在 INVALID Counter 与有效 Counter 的混淆"
            ),
            "wrong_core_ref": (
                "1. 检查多核 loop 的 context_node 切换逻辑\n"
                "2. 确认 CORE*_ID_MASK 的值与配置中的 core assignment 一致\n"
                "3. 检查 XPathEngine 是否在 core loop 中正确维护了 scope"
            ),
            "wrong_identifier": (
                "1. 检查 SymbolTable.resolve_reference 的路径匹配算法\n"
                "2. 确认是否存在同名但不同层级的节点导致歧义\n"
                "3. 增加路径长度优先的消歧策略"
            ),
            "missing_lines": (
                "1. 定位对应模板中的 [!IF] / [!LOOP] 指令\n"
                "2. 在 trace 中查找对应 XPath 条件的求值结果\n"
                "3. 检查 Renderer 的条件分支是否正确处理了该 XPath"
            ),
            "extra_lines": (
                "1. 定位对应模板中的 [!IF] / [!LOOP] 指令\n"
                "2. 检查条件判断逻辑是否将空节点误判为 truthy\n"
                "3. 检查 overlay_engine 是否引入了多余的配置叠加"
            ),
            "extra_cast": (
                "1. 在 BuiltinFunctions 中找到添加 (uint32) cast 的位置\n"
                "2. 增加类型检查，如果值已经是 uint32 类型则跳过 cast\n"
                "3. 或者在 Renderer 中做后处理，去除冗余 cast"
            ),
        }
        return suggestions.get(diff_type, "需要人工审查 trace 事件并定位引擎中的具体逻辑。")

    # ---- 去重 ----

    @staticmethod
    def _deduplicate(suggestions: List[FixSuggestion]) -> List[FixSuggestion]:
        """按 (component, category, target_function) 合并相似建议。"""
        seen: Dict[str, FixSuggestion] = {}
        result: List[FixSuggestion] = []

        for s in suggestions:
            key = f"{s.component.value}::{s.category.value}::{s.target_function}"
            if key in seen:
                # 合并 trace seqs 和 diff ids
                existing = seen[key]
                existing.related_trace_seqs.extend(s.related_trace_seqs)
                existing.related_diff_ids.extend(s.related_diff_ids)
                # 提升 confidence
                if s.confidence == Confidence.HIGH:
                    existing.confidence = Confidence.HIGH
            else:
                seen[key] = s
                result.append(s)

        return result
