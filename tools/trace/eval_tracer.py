"""
引擎执行轨迹收集器（类级 monkey-patch，跨 render() 调用持久有效）

使用方式：
    from tools.trace.eval_tracer import Tracer

    # 安装（全局类级 patch，只需调用一次）
    Tracer.install()

    # 启用 + 清空历史
    Tracer.enable()

    # 触发代码生成
    gen.generate_all(out_dir)

    # 查看结果
    print(Tracer.summary())
    Tracer.dump_json("/tmp/trace.json")

    # 关闭（保留 patch，停止记录）
    Tracer.disable()

捕获的函数：
    XPathEngine._find_context_loop_index  → loop index 解析（@index 的核心）
    SymbolTable.resolve_reference         → 引用路径解析
    BuiltinFunctions.node_ref             → node:ref() 调用
    BuiltinFunctions.node_order           → node:order() 调用
"""

from __future__ import annotations

import json
import time
import functools
from dataclasses import dataclass, field, asdict
from typing import Any, List, Optional

# ---------------------------------------------------------------------------
# Trace event
# ---------------------------------------------------------------------------

@dataclass
class TraceEvent:
    seq: int                            # 全局序列号（单调递增）
    fn: str                             # 被 trace 的函数名

    # 调用时的 context stack 快照
    context_path: str = ""              # 当前 context node 的 path
    context_name: str = ""              # 当前 context node 的 short_name
    loop_scopes: List[dict] = field(default_factory=list)
    # 每个 loop scope: {"depth": i, "node": path, "name": name, "index": N, "count": M}

    # 输入
    input_repr: str = ""
    input_extra: str = ""               # 第二个关键参数（如 sort_expr）

    # 输出
    result_repr: str = ""
    result_path: str = ""               # 返回节点的 path
    result_index: int = -1             # 返回节点的 .index

    # _find_context_loop_index 专属
    matched_scope_depth: int = -1      # 哪层 scope 匹配（-1 = 无匹配）
    fallback_index: int = -1           # node.index 属性值（fallback 时参考）
    match_reason: str = ""             # "direct_match" | "parent_match" | "fallback" | "no_match"

    def to_dict(self) -> dict:
        d = asdict(self)
        return d


# ---------------------------------------------------------------------------
# Tracer — 类级 patch，跨 render() 调用持久有效
# ---------------------------------------------------------------------------

class Tracer:
    _enabled: bool = False
    _events: List[TraceEvent] = []
    _seq: int = 0
    _installed: bool = False            # 类级 patch 只做一次

    # ---- 控制接口 ----

    @classmethod
    def enable(cls) -> None:
        """启用 trace 并清空历史事件。"""
        cls._events = []
        cls._seq = 0
        cls._enabled = True

    @classmethod
    def disable(cls) -> None:
        cls._enabled = False

    @classmethod
    def is_enabled(cls) -> bool:
        return cls._enabled

    @classmethod
    def events(cls) -> List[TraceEvent]:
        return list(cls._events)

    @classmethod
    def events_for_fn(cls, fn: str) -> List[TraceEvent]:
        return [e for e in cls._events if e.fn == fn]

    @classmethod
    def summary(cls) -> str:
        counts: dict[str, int] = {}
        for e in cls._events:
            counts[e.fn] = counts.get(e.fn, 0) + 1
        lines = [f"[Tracer] {len(cls._events)} events total:"]
        for fn, n in sorted(counts.items(), key=lambda kv: -kv[1]):
            lines.append(f"  {fn:<45} {n:>6}")
        return "\n".join(lines)

    @classmethod
    def dump_json(cls, path: str) -> None:
        with open(path, 'w', encoding='utf-8') as f:
            json.dump([e.to_dict() for e in cls._events], f, indent=2, ensure_ascii=False)
        print(f"[Tracer] {len(cls._events)} events → {path}")

    # ---- 安装（类级 patch）----

    @classmethod
    def install(cls) -> None:
        """
        对引擎类本身（非实例）打 patch。只需调用一次。
        此后所有新建的引擎实例都会自动带 trace。
        """
        if cls._installed:
            return

        from autosar_configurator.generator.eb.xpath_engine import XPathEngine
        from autosar_configurator.generator.eb.symbol_table import SymbolTable
        from autosar_configurator.generator.eb.builtins import BuiltinFunctions

        cls._patch_find_context_loop_index(XPathEngine)
        cls._patch_resolve_reference(SymbolTable)
        cls._patch_node_ref(BuiltinFunctions)
        cls._patch_node_order(BuiltinFunctions)

        cls._installed = True
        print("[Tracer] Class-level patches installed on XPathEngine, SymbolTable, BuiltinFunctions")

    # ---- 内部工具 ----

    @classmethod
    def _next_seq(cls) -> int:
        cls._seq += 1
        return cls._seq

    @classmethod
    def _record(cls, event: TraceEvent) -> None:
        cls._events.append(event)

    @classmethod
    def _snapshot_context(cls, context_stack) -> tuple:
        """提取 context_stack 的当前状态快照。"""
        ctx_path, ctx_name, scopes = "", "", []
        if context_stack is None:
            return ctx_path, ctx_name, scopes
        try:
            stack = context_stack._stack
            if stack:
                n = stack[-1].context_node
                if n:
                    ctx_path = getattr(n, 'path', '') or ''
                    ctx_name = getattr(n, 'short_name', '') or ''
            for depth, scope in enumerate(stack):
                if scope.loop_index >= 0:
                    node = scope.context_node
                    scopes.append({
                        "depth": depth,
                        "node":  getattr(node, 'path', '') if node else "",
                        "name":  getattr(node, 'short_name', '') if node else "",
                        "index": scope.loop_index,
                        "count": scope.loop_count,
                    })
        except Exception:
            pass
        return ctx_path, ctx_name, scopes

    # ---- Patch 实现 ----

    @classmethod
    def _patch_find_context_loop_index(cls, XPathEngine) -> None:
        original = XPathEngine._find_context_loop_index

        @functools.wraps(original)
        def traced(self, node):
            result = original(self, node)

            if Tracer._enabled:
                ctx_path, ctx_name, loop_scopes = Tracer._snapshot_context(
                    getattr(self, 'context_stack', None)
                )
                node_path   = getattr(node, 'path',       '') if node else ""
                node_name   = getattr(node, 'short_name', '') if node else ""
                fallback_i  = getattr(node, 'index',      -1) if node else -1

                # 确定匹配原因
                match_reason   = "no_match"
                matched_depth  = -1
                if result is not None:
                    try:
                        stack = self.context_stack._stack
                        for i in range(len(stack) - 2, -1, -1):
                            scope = stack[i]
                            if scope.loop_index < 0:
                                continue
                            ctx_node = scope.context_node
                            if ctx_node is node:
                                matched_depth = i
                                match_reason  = "direct_match"
                                break
                            if hasattr(ctx_node, 'parent') and ctx_node.parent:
                                p = ctx_node.parent
                                while p and getattr(p, 'is_wrapper', False):
                                    p = p.parent
                                if p is node:
                                    matched_depth = i
                                    match_reason  = "parent_match"
                                    break
                    except Exception:
                        pass
                else:
                    match_reason = "fallback" if fallback_i >= 0 else "no_match"

                Tracer._record(TraceEvent(
                    seq=Tracer._next_seq(),
                    fn="_find_context_loop_index",
                    context_path=ctx_path,
                    context_name=ctx_name,
                    loop_scopes=loop_scopes,
                    input_repr=f"{node_name}  path={node_path}",
                    result_repr=str(result),
                    result_index=result if result is not None else -1,
                    matched_scope_depth=matched_depth,
                    fallback_index=fallback_i,
                    match_reason=match_reason,
                ))

            return result

        XPathEngine._find_context_loop_index = traced

    @classmethod
    def _patch_resolve_reference(cls, SymbolTable) -> None:
        original = SymbolTable.resolve_reference

        @functools.wraps(original)
        def traced(self, ref_path: str):
            result = original(self, ref_path)

            if Tracer._enabled:
                res_path = getattr(result, 'path',       '') if result else ""
                res_name = getattr(result, 'short_name', '') if result else ""
                res_idx  = getattr(result, 'index',      -1) if result else -1

                Tracer._record(TraceEvent(
                    seq=Tracer._next_seq(),
                    fn="resolve_reference",
                    input_repr=ref_path,
                    result_repr=f"{res_name} idx={res_idx}" if result else "None",
                    result_path=res_path,
                    result_index=res_idx,
                ))

            return result

        SymbolTable.resolve_reference = traced

    @classmethod
    def _patch_node_ref(cls, BuiltinFunctions) -> None:
        original = BuiltinFunctions.node_ref

        @functools.wraps(original)
        def traced(self, path_or_node):
            result = original(self, path_or_node)

            if Tracer._enabled:
                if isinstance(path_or_node, str):
                    inp = f"str:{path_or_node}"
                elif hasattr(path_or_node, 'path'):
                    inp = f"node:{getattr(path_or_node,'path','?')}"
                else:
                    inp = repr(path_or_node)[:80]

                ctx_path, ctx_name, loop_scopes = Tracer._snapshot_context(
                    getattr(self, 'context_stack', None)
                )
                res_path = getattr(result, 'path',       '') if result else ""
                res_name = getattr(result, 'short_name', '') if result else ""
                res_idx  = getattr(result, 'index',      -1) if result else -1

                Tracer._record(TraceEvent(
                    seq=Tracer._next_seq(),
                    fn="node_ref",
                    context_path=ctx_path,
                    context_name=ctx_name,
                    loop_scopes=loop_scopes,
                    input_repr=inp,
                    result_repr=f"{res_name} idx={res_idx}" if result else "None",
                    result_path=res_path,
                    result_index=res_idx,
                ))

            return result

        BuiltinFunctions.node_ref = traced

    @classmethod
    def _patch_node_order(cls, BuiltinFunctions) -> None:
        original = BuiltinFunctions.node_order

        @functools.wraps(original)
        def traced(self, nodes, sort_expr=None):
            result = original(self, nodes, sort_expr)

            if Tracer._enabled:
                def _names(lst):
                    if not isinstance(lst, list):
                        return repr(lst)[:60]
                    parts = [
                        f"{getattr(n,'short_name','?')}(idx={getattr(n,'index',-1)})"
                        for n in lst[:5]
                    ]
                    suffix = f" +{len(lst)-5} more" if len(lst) > 5 else ""
                    return "[" + ", ".join(parts) + "]" + suffix

                Tracer._record(TraceEvent(
                    seq=Tracer._next_seq(),
                    fn="node_order",
                    input_repr=_names(nodes if isinstance(nodes, list) else []),
                    input_extra=str(sort_expr),
                    result_repr=_names(result),
                ))

            return result

        BuiltinFunctions.node_order = traced
