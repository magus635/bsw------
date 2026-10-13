## Why

ARTI 的停机调试描述已经完成（`add-os-arti-description-template`、`add-arti-orti-parity`、`add-arti-owner-object-ids`），但调试器和时序工具只能看到停机那一刻的状态，看不到运行过程：任务和 ISR 的时间线、执行时间、响应时间、等待原因、锁的持有时间都无从得到。SWS OS R21-11 §7.17（`doc/ARTI/AUTOSAR_SWS_OS.pdf`）要求 OS 在状态迁移处调用 `ARTI_TRACE` 宏，并在 ARTI 描述里用 `ArtiHook` 容器说明每个 hook。本内核目前只在"当前任务 / 当前 ISR 改变"时更新 `Os_OrtiRunningData`，没有任何 `ARTI_TRACE` 调用，`Os_Arti.arxml` 里也没有 `ArtiHook`。

## What Changes

- **事件范围**：实现 SWS OS §7.17 的全部六个 OS 类：`AR_CP_OS_APPLICATION`、`AR_CP_OS_TASK` / `AR_CP_OSARTI_TASK`、`AR_CP_OS_CAT2ISR` / `AR_CP_OSARTI_CAT2ISR`、`AR_CP_OS_SERVICECALLS`、`AR_CP_OS_SPINLOCK`、`AR_CP_OS_HOOK`。事件名一律取 SWS OS R21-11 原文的转换表。
- **两种状态模型都支持**：私有参数 `OsVendorArtiStateModel`（`STANDARD` / `ENHANCED`，默认 `ENHANCED`）同时决定任务和 Cat2 ISR 用标准类还是增强类，并同步写入 `ArtiStatesTaskEnhanced`。
- **按类开关**：私有参数 `OsVendorArtiTrace<Class>`（六个布尔，`SERVICECALLS` 默认关闭）。关闭的类在代码里展开为空，在 `ArtiHook` 里也不出现。
- **ARTI 描述**：`templates/Os/Os_Arti.arxml` 新增 `ArtiHook` 容器（每个启用的 class × event 一条）、核索引 / 任务 / ISR / 应用 / 自旋锁 / 服务调用参数的 TypeMap，并由 `ArtiOsInstanceHookRef` 关联到 OS 实例。
- **生成的包装宏头文件**：新增模板 `templates/Os/Os_ArtiHooks.h`，与 `Os_Arti.arxml` 共用一份事件表（新增宏文件 `Os_ArtiEvents.m`），保证代码里的字面 token 与 `ArtiHook` 描述逐字一致。开关关闭时所有宏展开为 `((void)0)`，取参数的局部变量也随之消失。
- **Mock 与检查**：新增模板生成的 `Os_Arti_Mock.h`（对四个字面 token 做 `##` 拼接，只为 `ArtiHook` 里列出的组合定义展开宏，并把事件写入按核分开的环形缓冲区），以及仓库里的事件流状态机检查脚本。
- **内核插桩**（`tr002_THA6_OS_Project/Os`，SVN 提交由用户处理）：调度器、`ActivateTask` / `TerminateTask` / `ChainTask` / `Schedule`、`WaitEvent` / `SetEvent`、ISR2 进入 / 退出 / 嵌套、自旋锁、应用状态变化、各 hook 函数、服务调用入口 / 出口。任务和 ISR 各增加一个只在增强模型下存在的 ARTI 影子状态字段。
- **插件**（`Os_THA6_ASR21`）：`Os.xdm` 增加上述私有参数；`Os_Arti.arxml`、`Os_ArtiHooks.h`、`Os_ArtiEvents.m` 部署到 `generate_PB/Os/`。
- **文档**：修正开发说明里与 SWS OS 原文不符之处（SWS OS 原文在仓库里；R21-11 定义了 `AR_CP_OSARTI_CAT2ISR`），补集成手册所需的约定。

## Impact

- Affected specs: `os-arti-description`（新增 hook 描述要求）、`os-arti-hooks`（新能力：包装宏、内核插桩、零开销、验证）
- Affected code:
  - 仓库：`templates/Os/Os_Arti.arxml`、新增 `templates/Os/Os_ArtiEvents.m`、`Os_ArtiCfg.h`、`Os_ArtiHooks.h`、`Os_Arti_Mock.h`、`Os_Arti_Mock.c`、`tools/arti/check_event_stream.py`（新增）、`tests/generator/` 下的新测试与夹具、`doc/ARTI/ARTI_hook_tracing.md`（新增）、`doc/2026-10-06_自研OS原生支持ARTI开发说明.md`
  - 插件：`config/Os.xdm`、`generate_PB/Os/`（不在本仓库）
  - 内核：`task/`、`event/`、`isr/`、`spinlock/`、`application/`、`hook/`、`kernel/` 及各服务 API 所在模块（不在本仓库）
- 依赖：`Os_AppCommon.m`（对象编号，已在用）；hook 的真实实现 `Arti.h` / `Os_Arti.h` 由 trace 工具提供，不在本变更内
- 验证限制：暂无 TRACE32。编译层面的一致性检查用本机 `arm-none-eabi-gcc` 做；运行时事件流需要在目标板上用 Mock 记录后导出，再用检查脚本验证，这一步由用户在板子上完成
- 兼容性：`OsUseArti` 关闭时内核代码与现在完全相同（零开销是验收条件）；开启时增加关中断路径的执行时间，时间保护预算需要重新标定（写入手册）
