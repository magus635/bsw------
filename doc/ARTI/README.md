# doc/ARTI

| 文件 | 作用 |
| :--- | :--- |
| `AUTOSAR_CP_EXP_ARTI.pdf`、`AUTOSAR_CP_SWS_ARTI.pdf`、`AUTOSAR_SWS_OS.pdf` | 规范 |
| `AUTOSAR_00047.xsd`、`xml.xsd` | ARTI ARXML 的 XSD 校验 |
| `Os_Trace.orti` | ORTI 模板，**测试使用的版本**：内容与插件的 `Os_Trace_Core0.ORTI` 相同，已修正 KOIL 语法缺陷，只含 `Os_OrtiRunningData[0]` |
| `Os_Trace_Core0.ORTI`、`Os_Trace_Core1.ORTI`、`Os_AppCommon.m` | 从 THA6 Os 插件（`Os_THA6_ASR21/generate_PB/`）复制来的**参考副本**，未修改 |

## `Os_Trace.orti` 与插件 ORTI 的差异

插件版是按核拆分的两个文件，两者只有 OS 段里的 `Os_OrtiRunningData[n]` 下标不同（Core0 为 `[0]`，Core1 为 `[1]`）。`Os_Trace.orti` 相对 `Os_Trace_Core0.ORTI` 的改动都是语法修复，不改变内容：

- ENUM 列表末项多余的逗号（`CORE_ID`、`SERVICETRACE`、`CURRENTAPPMODE`、`PRIORITY`、`STACK`、`CONTEXT` 等）
- `RESOURCE.LOCKED`、`SPINLOCK.LOCKED` 的枚举项缺逗号，`PRIORITY_TYPE` 缺分号
- `$MaxTask`、`$MaxIsr` 在没有 Task / CATEGORY_2 ISR 时补默认值（EB 对未定义变量会中止）

`tests/generator/test_orti_template.py` 检查这些语法问题。ARTI 与 ORTI 的覆盖对照由 `tests/generator/test_arti_orti_parity.py` 完成，参考 `openspec/changes/add-arti-orti-parity/`。
