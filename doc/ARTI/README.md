# doc/ARTI

调试器只用 ARTI（`templates/Os/Os_Arti.arxml` 生成的 `Os_Arti.arxml`）。ORTI 已不再生成，插件 `generate_PB/Os/` 里的 `Os_Trace_Core0/1.ORTI` 模板已删除。下面的 ORTI 文件只作为**冻结的对照基线**保留，不参与交付。

| 文件 | 作用 |
| :--- | :--- |
| `AUTOSAR_CP_EXP_ARTI.pdf`、`AUTOSAR_CP_SWS_ARTI.pdf`、`AUTOSAR_SWS_OS.pdf` | 规范 |
| `AUTOSAR_00047.xsd`、`xml.xsd` | ARTI ARXML 的 XSD 校验 |
| `Os_AppCommon.m` | 从 THA6 Os 插件复制的宏文件，ARTI 模板也 include 它（对象编号规则） |
| `Os_Trace.orti` | ORTI 基线，**测试使用的版本**：内容与插件原来的 `Os_Trace_Core0.ORTI` 相同，已修正 KOIL 语法缺陷，只含 `Os_OrtiRunningData[0]` |
| `Os_Trace_Core0.ORTI`、`Os_Trace_Core1.ORTI` | 插件删除前的原始模板副本，未修改，仅供查阅 |

`tests/generator/test_arti_orti_parity.py` 用同一份 Os 配置渲染 `Os_Trace.orti` 和 ARTI 模板，检查每个 ORTI 属性在 ARTI 里都有对应，保证 ARTI 没有漏项。参考 `openspec/changes/add-arti-orti-parity/`。

注意：内核的 `Os/orti/`（`Os_orti.c` 等）**不能删**。ARTI 读取的 `Os_OrtiRunningData` 就是它在运行时维护的，名字带 orti 只是历史原因。

## `Os_Trace.orti` 与插件 ORTI 的差异

插件版是按核拆分的两个文件，两者只有 OS 段里的 `Os_OrtiRunningData[n]` 下标不同（Core0 为 `[0]`，Core1 为 `[1]`）。`Os_Trace.orti` 相对 `Os_Trace_Core0.ORTI` 的改动都是语法修复，不改变内容：

- ENUM 列表末项多余的逗号（`CORE_ID`、`SERVICETRACE`、`CURRENTAPPMODE`、`PRIORITY`、`STACK`、`CONTEXT` 等）
- `RESOURCE.LOCKED`、`SPINLOCK.LOCKED` 的枚举项缺逗号，`PRIORITY_TYPE` 缺分号
- `$MaxTask`、`$MaxIsr` 在没有 Task / CATEGORY_2 ISR 时补默认值（EB 对未定义变量会中止）
