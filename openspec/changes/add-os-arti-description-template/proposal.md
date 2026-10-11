## Why

自研 OS（THA6 Os 插件）目前只通过 ORTI 2.2 模板（`doc/ARTI/Os_Trace.orti`，原名 `Os_Arti.arxml`）向调试器描述内核，只覆盖 Core 0，且不是 ARTI 格式。按 EXP ARTI §2.4 Fig 2.1，ARTI EcuC 容器应由 OS 生成器导出，而不是用户手工填写。第一阶段先把 ORTI 已有的"停机调试"信息改为生成标准 ARTI ARXML，并补上多核。

## What Changes

- 新增 EB 模板 `Os_Arti.arxml`：从 Os 配置生成 `/AUTOSAR/EcucDefs/Arti` 的 ECUC 值文件，内容包括 `ArtiValues`（States / TypeMap / Expression / Constant / Object*Parameter）、`ArtiOs`（Os / Task / Isr / Stack / Context / Alarm / Resource 的 Class 与 Instance）、`ArtiHardware`（每核一个 CoreInstance）。
- 模板复用 ORTI 模板的内核变量名与 ID 规则（`OsTask/@index`、`OsIsr/@index`），只使用 ORTI 模板已用过的模板语法与函数，保证在 EB tresos 和本工具中都能渲染。
- 整个输出受 `OsUseArti` 控制；关闭时输出一个合法但不含 Arti 模块配置的空 ARXML。
- 本工具代码生成器的模板发现扩展为接受 `<Module>_*.arxml` 与 `<Module>_*.orti`（白名单），输出文件名与模板名一致；原有 `.c` / `.h` / `.tpl` 规则不变。
- 不包括（第二阶段）：`ArtiHook` 条目与 `Os_ArtiHooks.h`、内核插桩、`ArtiGeneric` 扩展（Spinlock / ScheduleTable / Event / OS_CONFIG 实例）。

## Impact

- Affected specs: `os-arti-description`（新增）、`code-generation`
- Affected code: `autosar_configurator/generator/generator.py`（`_discover_template_types` 后缀白名单）；新增模板文件（放置位置见 design.md D1）；新增测试 `tests/generator/test_os_arti_template.py`
- 依赖材料（实施前需要）：样例 Os 配置 ARXML、THA6 Os 定义文件、对应生成的 `Os_Cfg.h/.c`、`Os_AppCommon.m`（见 design.md Open Questions）
