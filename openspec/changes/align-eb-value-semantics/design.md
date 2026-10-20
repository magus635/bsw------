## Context

EB tresos 的代码模板命令建立在 JXPath 的定制版（`org.apache.commons.jxpath.studio`）之上。从 EB tresos 27.0.0 安装（`...\Mcal_Tha62x\Supply\tresos\plugins`）反编译和实测得到：

- `ExpressionCommand`（`[!"expr"!]`）：`XPathContext.getValue(expr)` 后直接 `toString()` 输出，不做格式化。
- `VarCommand`（`[!VAR!]`）：同样 `getValue(expr).toString()`，用 `DefaultGeneratorContext.setVariable(name, String)` 保存。开发手册 7.2.9 节："The variables are always stored and interpreted as string values."
- `ForCommand`（`[!FOR!]`）：循环变量用 `Integer.toString(int)` 保存。
- `XPathContext.getValue` 直接返回 JXPath 的结果，没有后处理。

JXPath（EB 版）实测结果：

| 表达式 | 类型 | 值 |
|---|---|---|
| `0`、`5`、`1+1`、`2 * 3`、`count(/x)`、`string-length('ab')`、`floor(2.5)` | Double | `0.0`、`5.0`、`2.0`、`6.0`、`0.0`、`2.0`、`2.0` |
| `100000000` | Double | `1.0E8` |
| `concat('a', 1+1)` | String | `a2`（XPath 的数字转字符串不带 `.0`） |
| `'0.0' = '0'`、`$a = '5'`（a 为 `"5.0"`） | Boolean | `false` |
| `'0.0' = 0`、`$a = 5`、`$a > 4` | Boolean | `true` |

EB 扩展函数（`dreisoft.tresos.datamodel2.jar`）的运行时返回类型：

| 函数 | 类型 | 例 |
|---|---|---|
| `num:i`、`num:hextoint` 等 `*toint`、`bit:and` 等 `bit:*` | Long | `num:i(5.0)` → `5` |
| `num:f` | String | `5.0` |
| `num:inttohex` 等 | String | `0xff` |
| `num:max`、`num:min` | Double | `3.0` |
| `num:add` 等列表运算 | Vector | `[3.0]` |

## Goals / Non-Goals

- Goals：表达式的值类型、转字符串、VAR/FOR 保存和比较与 EB 一致，消除 `PRIORITY0_CORE0_QUEUESIZE` 这类差异；所有现有对照工程的输出保持与 EB 一致或更接近。
- Non-Goals：变量保存节点时的行为；宏的变量作用域；其他模板命令。

## Decisions

### 值的表示

引擎内部用 Python 类型对应 EB 的 Java 类型：

- `float` ↔ Double：XPath 数字。字面量 `5` 解析为 `5.0`。
- `int` ↔ Long：`num:i` 等整数函数的结果。
- `bool` ↔ Boolean。
- `str` ↔ String：包括所有变量的值。
- 配置节点与节点集保持现有表示。

转字符串统一走 `builtins.to_string`：`float` 用 `_format_float_java`，`bool` 用 `true`/`false`，`int` 用 `str`。

XPath 自身的数字转字符串（`string()`、`concat()` 的参数等）按 XPath 1.0：整数值不带 `.0`（`concat('a', 2.0)` → `a2`）。这与 `toString()` 不同，需要分开处理。

### 比较

按 XPath 1.0 第 3.4 节实现一处公共函数，所有比较路径都调用它：

1. 有一边是节点集：逐个取节点的值比较，任一成立即为真。
2. 有一边是布尔：两边转布尔。
3. 有一边是数字（`float` 或 `int`）：两边转数字，转不了时为 NaN。
4. 否则两边按字符串比较。

`<`、`>`、`<=`、`>=` 两边都转数字。

### 节点值的类型

已核实（任务 1.1）：EB 的 `PathPointer.getValue()`（`dreisoft.tresos.datamodel2.data.node.PathPointer`）通过 `INode.getValue(int)` 或 `IPathTransparentNode.getContainedValue(int)` 取值，两者都返回 `String`。所以所有参数的节点值在 XPath 中都是字符串，与参数类型无关：

- 节点值与字符串或变量比较，按字符串比较（`OsTaskPriority = $x`，`$x` 为 `"1.0"` 时为假）。
- 节点值与数字比较，按数字比较（`OsTaskPriority = 1` 为真）。
- BOOLEAN 参数是 `'true'`/`'false'` 字符串，与现有对照数据一致。

本工具的配置节点可能保存了类型化的值（如 `int`）。进入比较时，节点值一律按它在配置里的文本作为字符串参与比较。

### VAR 保存节点的情况

EB 的 VAR 对节点结果也会 `toString()`。本工具的部分模板代码可能依赖变量里保存节点（之后用 `$x/Child` 继续导航）。为了不扩大影响面，结果是节点或节点集时保持现状，只对数字、布尔、字符串结果转字符串。

## Risks / Trade-offs

- 影响面大：所有比较和数值输出都经过新规则。缓解：用下面的对照集全面回归，任何新增差异都要逐一解释。
  - tr002 的 124 个 EB 测试工程（`CfgEBProject/*`，用 `xdm_cmp.py` 比较 QUEUESIZE 和 CeilingPriority，并扩展为比较全部输出）。
  - intTest 工程（T2）与 EB 输出逐文件比较。
  - t1 改动前后的输出比较（Can、Mcu、Port、Os）。
  - `verify_fingerprints.py` 和 `tests/generator`。
- 模板直接输出算术结果时会出现 `2.0`。这与 EB 一致；若有本工具专用的模板依赖旧行为，回归时会暴露，届时在模板里加 `num:i`。
