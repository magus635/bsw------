"""
Source Map — 模板行号 → 输出行号 映射

以 monkey-patch 方式挂载到 Renderer，记录 (模板文件, 模板行号) → (输出文件, 输出行号)
的映射关系，用于 diff 差异溯源。

使用方式：
    from tools.trace.source_map import SourceMapTracer

    # 安装（对 Renderer 类打 patch）
    SourceMapTracer.install()

    # 启用（在实际 render 前调用）
    SourceMapTracer.enable(template_file="Os_application_Lcfg.c")

    # 触发代码生成
    output = renderer.render(template, ...)

    # 输出
    SourceMapTracer.dump_json("/tmp/source_map.json")

    # 关闭
    SourceMapTracer.disable()
"""

from __future__ import annotations

import json
import functools
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import Any, Dict, List, Optional


@dataclass
class SourceMapEntry:
    template_file: str          # 模板文件路径
    template_line: int          # 模板行号 (1-based)
    output_line: int            # 输出行号 (1-based)
    token_type: str             # TEXT / OUTPUT / VAR / LOOP / IF / SELECT / ...
    directive: str = ""         # 指令内容摘要 (e.g. "[!VAR \"CoreMask\"...]")
    context_xpath: str = ""     # 当前 context node 的 xpath

    def to_dict(self) -> dict:
        return asdict(self)


class SourceMapTracer:
    _enabled: bool = False
    _installed: bool = False
    _entries: List[SourceMapEntry] = []
    _template_file: str = ""

    # 运行时跟踪
    _output_line: int = 1       # 当前输出行号

    # ---- 控制接口 ----

    @classmethod
    def enable(cls, template_file: str = "") -> None:
        cls._entries = []
        cls._template_file = template_file
        cls._output_line = 1
        cls._enabled = True

    @classmethod
    def disable(cls) -> None:
        cls._enabled = False

    @classmethod
    def is_enabled(cls) -> bool:
        return cls._enabled

    @classmethod
    def entries(cls) -> List[SourceMapEntry]:
        return list(cls._entries)

    @classmethod
    def set_template_file(cls, path: str) -> None:
        """切换当前模板文件（INCLUDE 时使用）"""
        cls._template_file = path

    @classmethod
    def dump_json(cls, path: str) -> None:
        p = Path(path)
        p.parent.mkdir(parents=True, exist_ok=True)
        data = {
            "total_entries": len(cls._entries),
            "source_map": [e.to_dict() for e in cls._entries],
        }
        p.write_text(json.dumps(data, indent=2, ensure_ascii=False), encoding='utf-8')
        print(f"[SourceMap] {len(cls._entries)} entries → {path}")

    @classmethod
    def summary(cls) -> str:
        lines = [
            f"[SourceMap] {len(cls._entries)} entries",
        ]
        by_type: Dict[str, int] = {}
        for e in cls._entries:
            by_type[e.token_type] = by_type.get(e.token_type, 0) + 1
        for tt, count in sorted(by_type.items(), key=lambda kv: -kv[1]):
            lines.append(f"  {tt:<20} {count:>6}")
        return "\n".join(lines)

    # ---- 记录 ----

    @classmethod
    def _record(cls, template_line: int, token_type: str,
                directive: str = "", context_xpath: str = "") -> None:
        if not cls._enabled:
            return
        cls._entries.append(SourceMapEntry(
            template_file=cls._template_file,
            template_line=template_line,
            output_line=cls._output_line,
            token_type=token_type,
            directive=directive[:120],
            context_xpath=context_xpath,
        ))

    @classmethod
    def _count_newlines(cls, text: str) -> None:
        """更新输出行号计数"""
        if not cls._enabled:
            return
        cls._output_line += text.count('\n')

    # ---- 安装 ----

    @classmethod
    def install(cls) -> None:
        """对 Renderer 类打 monkey-patch，拦截 _execute_tokens 和 render。"""
        if cls._installed:
            return

        from autosar_configurator.generator.eb.renderer import Renderer

        cls._patch_execute_tokens(Renderer)
        cls._patch_render(Renderer)

        cls._installed = True
        print("[SourceMap] Patches installed on Renderer")

    @classmethod
    def _patch_render(cls, RendererClass) -> None:
        """拦截 render() 来自动设置 template_file"""
        original = RendererClass.render

        @functools.wraps(original)
        def traced_render(self, template, module_name=None, context_path=None,
                          initial_variables=None, ecu_resources=None,
                          template_file=None):
            if SourceMapTracer._enabled and template_file:
                SourceMapTracer.set_template_file(template_file)
                SourceMapTracer._output_line = 1
            return original(self, template, module_name=module_name,
                            context_path=context_path,
                            initial_variables=initial_variables,
                            ecu_resources=ecu_resources,
                            template_file=template_file)

        RendererClass.render = traced_render

    @classmethod
    def _patch_execute_tokens(cls, RendererClass) -> None:
        """
        拦截 _execute_tokens，在每个 token 执行前记录 source map。
        通过监测 _output_buffer 的增长来追踪输出行号。
        """
        original = RendererClass._execute_tokens

        @functools.wraps(original)
        def traced_execute(self, tokens, start, end):
            if not SourceMapTracer._enabled:
                return original(self, tokens, start, end)

            # 逐 token 执行，在每个 token 前后记录
            i = start
            while i < end:
                tok = tokens[i]

                # 记录 BREAK
                if self._break_requested:
                    break

                # 获取当前 context xpath
                ctx_xpath = ""
                try:
                    if self._context_stack and self._context_stack._stack:
                        node = self._context_stack._stack[-1].context_node
                        if node:
                            ctx_xpath = getattr(node, 'path', '') or ''
                except Exception:
                    pass

                # 记录 buffer 长度来追踪输出变化
                buf_len_before = len(self._output_buffer)

                # 记录 source map entry（只记有实际输出的 token 类型）
                token_type = tok.type.name
                if tok.type.name in ('TEXT', 'OUTPUT', 'VAR', 'IF', 'LOOP',
                                     'SELECT', 'FOR', 'INCLUDE', 'CALL',
                                     'CR', 'WS', 'MACRO', 'TRACE',
                                     'AUTOGENERATE_WARNING', 'NOCODE', 'CODE'):
                    SourceMapTracer._record(
                        template_line=tok.line,
                        token_type=token_type,
                        directive=tok.content[:80] if tok.content else "",
                        context_xpath=ctx_xpath,
                    )

                # 执行单个 token：调用原始 _execute_tokens 但只执行一步
                # 为避免递归失控，对结构性 token 直接调用原始方法
                result = original(self, tokens, i, min(i + 1, end) if tok.type.name in (
                    'TEXT', 'OUTPUT', 'COMMENT', 'VAR', 'BREAK',
                    'INDENT', 'ENDINDENT', 'WS', 'AUTOSPACING', 'CR',
                    'AUTOGENERATE_WARNING', 'INCLUDE', 'CALL', 'TRACE',
                ) else end)

                # 统计新增的输出中的换行符
                for buf_idx in range(buf_len_before, len(self._output_buffer)):
                    SourceMapTracer._count_newlines(self._output_buffer[buf_idx])

                # 对于单步 token，直接 i+1；对于结构性 token(IF/LOOP/...)，
                # original 已处理到 END* 后，result 即为下一个 index
                if tok.type.name in (
                    'TEXT', 'OUTPUT', 'COMMENT', 'VAR', 'BREAK',
                    'INDENT', 'ENDINDENT', 'WS', 'AUTOSPACING', 'CR',
                    'AUTOGENERATE_WARNING', 'INCLUDE', 'CALL', 'TRACE',
                ):
                    i += 1
                else:
                    # 结构性 token (IF, LOOP, SELECT, FOR, NOCODE, CODE, MACRO, ASSERT, ERROR)
                    # original 处理了整个块，返回值是块结束后的 index
                    i = result

            return i

        RendererClass._execute_tokens = traced_execute

    # ---- 查询辅助 ----

    @classmethod
    def find_by_output_line(cls, output_line: int, tolerance: int = 0) -> List[SourceMapEntry]:
        """查找产生指定输出行的 source map entries"""
        return [
            e for e in cls._entries
            if abs(e.output_line - output_line) <= tolerance
        ]

    @classmethod
    def find_by_template_line(cls, template_line: int, template_file: str = "") -> List[SourceMapEntry]:
        """查找指定模板行对应的所有输出"""
        results = [e for e in cls._entries if e.template_line == template_line]
        if template_file:
            results = [e for e in results if e.template_file == template_file]
        return results
