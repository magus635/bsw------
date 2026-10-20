## Why

EB tresos 模板里的变量一律按字符串保存，数字转成字符串的方式取决于它从哪里来；比较时按 XPath 1.0 规则，两边都是字符串就按字符串比较。本工具的引擎把数字统一当成数值处理，比较时总是先尝试数值比较，在少数模板写法下结果与 EB 不同。

已经确认的实例：intTest 工程（`Os_THA6_ASR21` 插件）的 `Os_task_Cfg.h` 中 `PRIORITY0_CORE0_QUEUESIZE`，EB 输出 `(2U)`，本工具输出 `(3U)`。

- 模板 `Os_task_Cfg.h:112` 写 `[!VAR "CeilingPriority" = "0"!]`，宏 `Os_Calculate_Resource_CeilingPriority`（`Os_AppCommon.m:143`）也写 `"0"`。EB 把数字字面量求值为 Double，存成 `"0.0"`。
- 循环变量 `[!FOR "i" ...!]` 由 EB 用 `Integer.toString` 保存，是 `"0"`。
- `Os_task_Cfg.h:119` 的 `$CeilingPriority = $i` 在 EB 中是字符串比较，`"0.0" = "0"` 为假；本工具按数值比较为真，于是把链接到 RES_SCHEDULER 的 `OsResource_0` 多算进了优先级 0 的队列。
- 从内核看 2 才是正确值：天花板为 `0xFFFFFFFF` 的资源从不进入就绪队列（内核 `task/Os_task.c:1333-1355`）。

用 EB 自带的 JXPath 库（EB tresos 27.0.0 安装中的 `org.apache.commons.jxpath.studio.jar`）实测，并反编译 EB 的模板命令（`VarCommand`、`ForCommand`、`ExpressionCommand`），得到以下 EB 行为，本工具目前都不同：

| 写法 | EB | 本工具 |
|---|---|---|
| `[!"1+1"!]`、`[!"count(...)"!]` | `2.0`、`0.0` | `2`、`0` |
| `[!"1 < 2"!]` | `true` | `True` |
| `[!VAR "a" = "5"!]` 后 `$a` | `"5.0"` | `"5"` |
| `$a = '5'`（`$a` 为上行的值） | 假 | 真 |
| VAR `"0"` 与 FOR 变量 `0` 比较 | 假 | 真 |
| `[!"'0.0' = '0'"!]` | `false` | 解析错误，原样输出 |

## What Changes

- **数值类型**：表达式求值区分 EB 的两种数值。
  - XPath 数字（Java Double）：数字字面量、算术运算、`count`、`string-length`、`number`、`sum`、`floor`/`ceiling`/`round`、`num:max`/`num:min` 等。
  - 整数（Java Long）：`num:i`、`num:hextoint` 等进制转换、`bit:*`。
- **转成字符串**：输出 `[!"..."!]` 与保存 `[!VAR!]` 时，按 EB 的 `toString()` 规则把值转成字符串：Double 用 Java `Double.toString`（`2.0`、`1.0E8`），整数不带小数，布尔为 `true`/`false`。
- **VAR**：结果为数字、布尔或字符串时，按上一条转成字符串后保存，与 EB 相同。结果为配置节点或节点集时保持现状（见 design.md）。
- **FOR**：循环变量保存为整数字符串（`"0"`、`"1"`）。
- **比较**：`=`、`!=` 按 XPath 1.0 规则：
  - 有一边是布尔：都转成布尔比较。
  - 否则有一边是数字：都转成数字比较。
  - 否则（两边都是字符串，包括变量）：按字符串比较。
  - `<`、`>`、`<=`、`>=` 一律转成数字比较。
  - 引擎中现有的几处比较实现统一到这一套规则。
- **字面量解析**：修正 `[!"'0.0' = '0'"!]` 这类以引号开头、以引号结尾的表达式被误当作字符串字面量的问题。
- **增量生成**：生成器指纹版本号加一，升级后第一次生成会重新生成所有模块。

## Impact

- Affected specs: `eb-template-value-semantics`（新增能力）
- Affected code（`autosar_configurator/generator/eb/`）：
  - `xpath_engine.py`：数值类型、算术、比较（约 484-533 行、2188-2235 行等各处比较实现）
  - `builtins.py`：内置函数的返回类型、`to_string`（已有 `_format_float_java` 可复用）
  - `renderer.py`：`_handle_var`（710 行起）、`_handle_for`（2080 行起）、OUTPUT 处理（479 行起）、`_strip_tag_quotes`
  - `generator.py`：`GENERATOR_VERSION`
  - 测试 `tests/generator/`
- 兼容性：
  - 目标是和 EB 的输出一致，所以凡是与 EB 不一致的生成结果都可能变化。已知的有 intTest 的 `PRIORITY0_CORE0_QUEUESIZE` 从 3 变为 2。
  - 模板若直接输出算术结果而不用 `num:i`，输出会从 `2` 变成 `2.0`，与 EB 相同。EB 插件的模板通常都用 `num:i` 包住，回归时会全面核对。
  - 现有测试 `tests/generator/test_line_comment_whitespace.py` 里 `[!VAR "a" = "5"!]...[!"$a"!]UL` 期望 `5UL`，按 EB 语义应为 `5.0UL`，需要改用与真实模板一致的写法。
- **不在本变更范围内**：
  - 变量保存配置节点（如 `[!VAR "x" = "node:ref(.)"!]`）时的行为，保持现状。
  - 宏参数与变量作用域。EB 的变量实际上全局共享，本工具目前把宏的输出参数传回调用方，已知的模板都能正确处理，不在这里改动。
  - 内核 KillTask 的越界问题，单独跟踪。
