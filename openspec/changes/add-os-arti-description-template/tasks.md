## 0. 前置材料（实施前）
- [ ] 0.1 收到样例 Os 配置 ARXML、THA6 Os 定义文件、对应生成的 `Os_Cfg.h/.c`、`Os_AppCommon.m`，放入 `tests/fixtures/os_arti/`
- [ ] 0.2 根据材料关闭 design.md 的 Open Questions 1–5，并回写 design.md

## 1. 生成器支持非 C 模板
- [x] 1.1 `generator.py:_discover_template_types`：`<Module>_` 前缀文件增加 `.arxml`、`.orti` 后缀白名单，`t_type` 为完整后缀文件名
- [x] 1.2 测试：`Os_Arti.arxml` 被发现并输出为 `Os_Arti.arxml`；未在白名单内的后缀（如 `.txt`）仍被忽略；`.c`/`.h`/`.tpl` 行为不变
- [x] 1.3 指纹稳定性检查：仓库中没有 `verify_fingerprints.py`。指纹只对已发现的模板计算，模板目录中没有 `.arxml`/`.orti` 模板的模块，其指纹不变

## 2. Os_Arti.arxml 模板
- [ ] 2.1 文档骨架与 `OsUseArti` 开关（D5）
- [ ] 2.2 `ArtiValues`：States、TypeMap（TaskId / Isr2Id / TaskState / AppMode / LastError / ServiceId / Priority）、Expression、Constant、Object*Parameter
- [ ] 2.3 `ArtiOs`：Os / Task / Isr / Stack / Context / Alarm / Resource 的 Class 与 Instance
- [ ] 2.4 `ArtiHardware`：每核一个 CoreClass / CoreInstance（D4）
- [ ] 2.5 只使用 D2 列出的语法与函数

## 3. 验证
- [ ] 3.1 本工具渲染样例 Os 配置，无错误、无 unimplemented-function 告警
- [ ] 3.2 输出通过 `AUTOSAR_00047.xsd` 校验；用 `Arti_ParamDef.arxml` 加载无未知参数，多重性满足（Open Questions 3/4 的已知缺口除外）
- [ ] 3.3 `ArtiOsTaskInstanceId` / `ArtiOsIsrInstanceId` / TypeMap `Input` 与样例 `Os_Cfg.h` 的 `TaskType` / `ISRType` 一致，并与 ORTI 模板的 `RUNNINGTASK` / `RUNNINGISR2` ENUM 一致
- [ ] 3.4 把输出作为 Arti 模块值文件导入本工具（与 Os 同一工程），`resolve_all_references()` 无解析错误
- [ ] 3.5 `OsUseArti` 关闭时输出合法空文档
- [ ] 3.6 （用户执行）在 EB tresos 中用同一配置生成，结果与 3.1 一致；用 TRACE32 加载，确认多核当前任务与任务状态显示正确

## 4. ORTI 模板语法修复（bug fix，可独立提交）
- [ ] 4.1 `RESOURCE.LOCKED`、`SPINLOCK.LOCKED` 枚举项补逗号；`PRIORITY_TYPE` 补分号；单核派生型 `CoreIdType` 去掉多余逗号；`$MaxIsr` / `$MaxTask` 在集合为空时有默认值
- [ ] 4.2 文件改名为 `Os_Trace.orti`（与文件头一致）

## 5. 文档
- [ ] 5.1 更新 `doc/2026-10-06_自研OS原生支持ARTI开发说明.md` 第十节：说明标准做法是由 OS 生成器导出 Arti 配置，手工配置只作为过渡方案
