# EB 模板 Boolean 语义修改方案

日期：2026-06-06

> 文档状态：历史方案记录。当前模板引擎行为请以代码、测试和根目录 `PROJECT_SUMMARY.md` 为准；本文用于说明当时的设计动机和语义约束。

## 目标

为 EB 模板引擎建立清晰的 Boolean 语义分层，兼容现有 EB 风格模板里的条件比较，同时为 AUTOSAR Classic C 代码生成提供显式、无歧义的输出函数。

核心契约：

```text
node:value(x)
  EB 表达式取值语义：BOOLEAN -> 'true' / 'false'

autosar:std_on_off(x)
  AUTOSAR 开关宏输出：true -> STD_ON，false -> STD_OFF

autosar:true_false(x)
  C boolean 宏输出：true -> TRUE，false -> FALSE
```

## 背景问题

当前 `node:value()` 对 `BOOLEAN` 固定返回 `'true'/'false'`，这与 EB 条件表达式兼容：

```eb
[!IF "node:value(CanWakeupSupport) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
```

但项目测试中也存在直接输出 C 宏的期望，例如 `STD_ON/STD_OFF` 或 `TRUE/FALSE`。如果直接修改 `node:value()` 的返回值，会破坏大量 `= 'true'` 的模板语法。因此需要把“取值/比较”和“C 代码输出”拆成不同函数。

## 设计原则

1. 不改变 `node:value()` 的 EB 表达式语义。
2. 不根据参数名自动猜测输出格式，避免 `Enable/Support/Disable` 等命名误判。
3. 输出点必须显式选择目标格式。
4. 新函数使用通用 `autosar:` 命名空间，不使用 `mcal:`，避免 OS、EcuC、BSW 模块使用时产生歧义。
5. 迁移只处理“直接输出 Boolean”的模板，不全局替换 `node:value()`。

## 需要修改的代码点

### 1. 内置函数注册

文件：`autosar_configurator/generator/eb/builtins.py`

在 `BuiltinFunctions.__init__()` 的 `_functions` 字典中新增：

```python
'autosar:std_on_off': self.autosar_std_on_off,
'autosar:true_false': self.autosar_true_false,
```

建议同时在文件头部函数分类注释中增加：

```text
- AUTOSAR output functions: autosar:std_on_off, autosar:true_false
```

### 2. 新增 Boolean 输出函数

文件：`autosar_configurator/generator/eb/builtins.py`

新增三个函数：

```python
def autosar_std_on_off(self, node_or_path_or_value: Any) -> str:
    ...

def autosar_true_false(self, node_or_path_or_value: Any) -> str:
    ...

def _resolve_boolean_value(self, node_or_path_or_value: Any) -> bool:
    ...
```

实现要求：

- 支持参数是 `ConfigurationNode`。
- 支持参数是相对路径、绝对路径、当前节点子节点名。
- 支持参数已经是 `True/False`、`'true'/'false'`、`'1'/'0'`、`'STD_ON'/'STD_OFF'`、`'TRUE'/'FALSE'`。
- 复用 `execution_context.py` 中已有的 `parse_boolean()`、`format_boolean_feature()`、`format_boolean_runtime()`，不要再复制一套 Boolean 解析逻辑。
- 路径解析失败时遵循现有 `strict` 行为：非 strict 返回可诊断的空值或默认 false，strict 下抛出错误。具体策略应与 `node:value()` 的错误处理保持一致。

推荐实现语义：

```text
autosar:std_on_off(x)
  parse_boolean(x) ? 'STD_ON' : 'STD_OFF'

autosar:true_false(x)
  parse_boolean(x) ? 'TRUE' : 'FALSE'
```

### 3. 保留并澄清 `node:value()` 语义

文件：`autosar_configurator/generator/eb/builtins.py`

保留当前 `BOOLEAN -> 'true'/'false'` 行为，但更新注释，明确这是 EB 表达式取值语义：

```text
node:value() returns EB expression values. BOOLEAN parameters are normalized
to lowercase 'true'/'false' so templates can compare against EB boolean text.
C code output must use autosar:std_on_off() or autosar:true_false().
```

不要把 `node:value()` 改成 `STD_ON/STD_OFF` 或 `TRUE/FALSE`。

### 4. 函数参数解析

文件：`autosar_configurator/generator/eb/renderer.py`

当前 `_evaluate_function_call()` 只把 `node:` 和 `ecuC:` 函数按节点参数解析：

```python
is_node_func = func_name.startswith('node:') or func_name.startswith('ecuC:')
```

需要加入 `autosar:`：

```python
is_node_func = (
    func_name.startswith('node:')
    or func_name.startswith('ecuC:')
    or func_name.startswith('autosar:')
)
```

原因：`autosar:std_on_off(CanGeneral/CanDevErrorDetect)` 需要拿到参数节点或路径，不能过早被普通表达式求值成不可追踪的字符串。

### 5. XPath Boolean 展开语义

文件：`autosar_configurator/generator/eb/xpath_engine.py`

`XPathEngine._unwrap_result()` 当前对 `BOOLEAN` 返回 `'true'/'false'`。此行为应保留，因为 XPath/IF 条件表达式依赖这个语义。

需要修改的是注释，不应再暗示 `node:value()` 或 XPath 自动输出 C 宏。建议说明：

```text
BOOLEAN values are normalized to EB expression text ('true'/'false').
Use autosar:* functions for C macro output.
```

### 6. 执行上下文注释

文件：`autosar_configurator/generator/eb/execution_context.py`

当前 `BooleanOutputMode` 注释中有“NOT allowed: true / false (lowercase)”的表述，容易与 `node:value()` 的 EB 表达式语义冲突。

建议调整为：

```text
These helpers define AUTOSAR C output formats.
Lowercase true/false remains valid for EB expression values and comparisons.
```

函数 `format_boolean_feature()` 和 `format_boolean_runtime()` 可以保留，供 `autosar:*` 新函数复用。

## 需要修改的模板点

### 1. 直接输出开关宏的模板

文件：`tests/generator/eb/templates/Mcu_Cfg.h.tt`

当前：

```eb
#define MCU_DEV_ERROR_DETECT        [!node:value(McuDevErrorDetect)!]
#define MCU_VERSION_INFO_API        [!node:value(McuVersionInfoApi)!]
#define MCU_PERFORM_RESET_API       [!node:value(McuPerformResetApi)!]
```

修改为：

```eb
#define MCU_DEV_ERROR_DETECT        [!"autosar:std_on_off(McuDevErrorDetect)"!]
#define MCU_VERSION_INFO_API        [!"autosar:std_on_off(McuVersionInfoApi)"!]
#define MCU_PERFORM_RESET_API       [!"autosar:std_on_off(McuPerformResetApi)"!]
```

### 2. Golden Master 中的直接 Boolean 输出

文件：`tests/generator/eb/test_golden_master.py`

当前示例：

```eb
#define CAN_DEV_ERROR_DETECT   [!"node:value(CanGeneral/CanDevErrorDetect)"!]
```

修改为：

```eb
#define CAN_DEV_ERROR_DETECT   [!"autosar:std_on_off(CanGeneral/CanDevErrorDetect)"!]
```

当前示例：

```eb
.WakeupSupport = [!IF "node:value('CanWakeupSupport') == 'STD_ON'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
```

修改为二选一，推荐直接输出：

```eb
.WakeupSupport = [!"autosar:true_false('CanWakeupSupport')"!]
```

如需要保留 IF 风格，则应比较 `'true'`：

```eb
.WakeupSupport = [!IF "node:value('CanWakeupSupport') = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
```

### 3. 真实 Can 模板

文件：`autosar_configurator/generator/templates/can/Can_PBcfg.c`

当前多数 Boolean 输出已经是显式 IF：

```eb
(boolean)[!IF "CanHardwareObjectUsesPolling = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!]
```

这类写法不需要修改。可以在后续模板清理中选择性改成：

```eb
(boolean)[!"autosar:true_false(CanHardwareObjectUsesPolling)"!],
```

但不应作为本次兼容修复的强制范围。

### 4. 不应修改的模板写法

以下写法不应批量替换：

```eb
[!IF "node:value(X) = 'true'"!]... [!ENDIF!]
[!VAR "X" = "node:value(Y)"!]
[!LOOP "node:order(..., 'node:value(Id)')"!]
[!"node:value(NumericOrEnum)"!]
```

这些用途仍属于取值、比较、排序、数字/枚举输出，不是 Boolean C 宏输出。

## 需要修改的测试点

### 1. 调整错误契约测试

文件：`tests/generator/eb/test_smoke.py`

当前 `TestAutoSarSemanticMapping` 直接断言 `node_value()` 返回 `STD_ON/STD_OFF/TRUE/FALSE`。应改为：

```text
node_value(BOOLEAN True)  -> 'true'
node_value(BOOLEAN False) -> 'false'
```

并新增 formatter 测试：

```text
autosar:std_on_off(True)  -> STD_ON
autosar:std_on_off(False) -> STD_OFF
autosar:true_false(True)  -> TRUE
autosar:true_false(False) -> FALSE
```

### 2. 新增 renderer 集成测试

建议新增文件：`tests/generator/eb/test_autosar_boolean_output.py`

覆盖：

```eb
[!"autosar:std_on_off(CanGeneral/CanDevErrorDetect)"!]
[!"autosar:true_false(CanWakeupSupport)"!]
[!IF "node:value(CanWakeupSupport) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
```

必须验证：

- 新函数能接收相对路径。
- 新函数能接收带引号的子节点名。
- 新函数能接收直接 Boolean 值。
- `node:value()` 的 `'true'/'false'` 比较继续工作。

### 3. 更新 Golden Master 断言

文件：`tests/generator/eb/test_golden_master.py`

保留输出期望：

```text
#define CAN_DEV_ERROR_DETECT   STD_ON
.WakeupSupport = FALSE
.WakeupSupport = TRUE
```

但模板实现改用 `autosar:*` 或 `node:value() = 'true'`，不要再依赖 `node:value() == 'STD_ON'`。

### 4. 保留用户模板 IF 测试

文件：`tests/generator/eb/test_user_templates.py`

现有：

```eb
[!IF "node:value(CanGeneral/CanDevErrorDetect) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!IF "node:value(CanWakeupSupport) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
```

这组测试应保留，用来防止未来再次破坏 EB 条件比较语义。

## 需要修改的文档点

### 1. README

文件：`README.md`

内置函数列表增加：

```text
- AUTOSAR 输出: autosar:std_on_off(), autosar:true_false()
```

### 2. XPath 语言参考

文件：`doc/XPath语言参考.md`

当前 `node:value` 描述包含“Boolean -> STD_ON/STD_OFF”，需要改为：

```text
node:value(node_or_path)：获取 EB 表达式值。BOOLEAN 归一化为 'true'/'false'，用于 IF/XPath 比较。
```

新增函数说明：

```text
autosar:std_on_off(x)：BOOLEAN 输出为 STD_ON/STD_OFF
autosar:true_false(x)：BOOLEAN 输出为 TRUE/FALSE
```

### 3. EB Tresos XDM 说明

文件：`doc/EB_Tresos_XDM格式解析说明.md`

在内置函数表中加入 `autosar:*`，并说明 `node:value()` 与 C 输出函数的分工。

### 4. UI 用户手册

文件：`autosar_configurator/ui/dialogs/user_manual_dialog.py`

在内置函数提示中补充：

```text
autosar:std_on_off(), autosar:true_false()
```

### 5. 审查报告

文件：`doc/项目审查报告_2026-06-06.md`

如需要保持审查报告与最终决策一致，建议把 Boolean 问题描述改为：

```text
Boolean 输出语义未分层：node:value() 应保留 EB 比较语义，C 宏输出应使用显式 autosar:* formatter。
```

这不是必须的代码改动，但有助于后续追踪决策。

## 兼容与迁移策略

### 阶段 1：新增能力，不改变旧行为

- 新增 `autosar:std_on_off()` 和 `autosar:true_false()`。
- 保持 `node:value()` 返回 `'true'/'false'`。
- 保持现有 IF 模板继续通过。

### 阶段 2：迁移项目内直接 Boolean 输出

只迁移已确认是 Boolean C 宏输出的位置：

```text
tests/generator/eb/templates/Mcu_Cfg.h.tt
tests/generator/eb/test_golden_master.py
```

真实模板目录中暂未发现必须迁移的直接 Boolean `node:value()` 输出。`Can_PBcfg.c` 主要是 IF 显式输出，保留即可。

### 阶段 3：为用户旧模板提供检查

建议后续增加模板 lint，不作为本次核心修复阻塞项。lint 可提示类似风险：

```text
直接输出疑似 Boolean 参数：
[!"node:value(SomeEnable)"!]

建议：
[!"autosar:std_on_off(SomeEnable)"!]
或
[!"autosar:true_false(SomeFlag)"!]
```

不要在运行时强制自动转换，以免破坏用户已有模板。

## 验证计划

### 最小验证

```bash
QT_QPA_PLATFORM=offscreen python3 -m pytest \
  tests/generator/eb/test_smoke.py \
  tests/generator/eb/test_user_templates.py \
  tests/generator/eb/test_golden_master.py \
  -q
```

验证目标：

- `node:value()` Boolean 仍可与 `'true'/'false'` 比较。
- `autosar:std_on_off()` 输出 `STD_ON/STD_OFF`。
- `autosar:true_false()` 输出 `TRUE/FALSE`。
- Golden Master 中 C 宏输出保持不变。

### 模板搜索验证

```bash
rg -n "node:value\\([^\\n]*Enable|node:value\\([^\\n]*Disable|node:value\\([^\\n]*Support|node:value\\([^\\n]*Detect" \
  autosar_configurator/generator/templates tests/generator
```

逐条判断是否是直接 C 输出。只有直接输出 Boolean 的位置才迁移。

### 回归验证

```bash
QT_QPA_PLATFORM=offscreen python3 -m pytest tests/generator/eb -q
```

注意：当前模板引擎还有独立失败项，包括行注释、字面量输出和十六进制大小写。如果这些尚未修复，完整 `tests/generator/eb` 可能仍失败。Boolean 修复应先用最小验证确认，再与其他模板引擎修复合并跑全量。

## 关联但不纳入本方案的修复项

这些问题会影响模板引擎总体测试，但不属于 Boolean 语义拆分：

1. `lexer.py` 行注释正则贪婪匹配导致 `[!// comment !]After` 丢失 `After`。
2. `renderer.py` 字面量输出 `[!"Hello World"!]` 当前输出为空。
3. `builtins.py` 的 `num:inttohex()` 当前输出小写，测试期望大写。
4. `context.py` 变量 shadow 语义与测试/注释存在冲突，需要单独确认 EB 语义后处理。

这些应作为独立补丁修复，不要通过改变 Boolean 语义来掩盖。

## 验收标准

1. `node:value(BOOLEAN)` 在表达式中稳定返回 `'true'/'false'`。
2. 直接 C 开关宏输出使用 `autosar:std_on_off()`。
3. 直接 C boolean 输出使用 `autosar:true_false()`。
4. 现有 `= 'true'` 的 EB 条件模板不需要修改且继续通过。
5. 项目内直接 Boolean 输出模板已迁移。
6. README、XPath 参考、XDM 说明、UI 用户手册中的函数说明一致。
7. 最小验证测试通过。
