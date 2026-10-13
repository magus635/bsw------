# Design: ARTI hook tracing

依据：SWS OS R21-11 §7.17（`doc/ARTI/AUTOSAR_SWS_OS.pdf`，下文简称 SWS OS），SWS / EXP ARTI R24-11（`doc/ARTI/`），开发说明 `doc/2026-10-06_自研OS原生支持ARTI开发说明.md`（下文简称"说明"），内核 `tr002_THA6_OS_Project/Os`（下文简称"内核"）。

## D1 事件清单：以 SWS OS R21-11 原文为准

说明第九节第 1 条的"事件拼写待确认"，SWS OS 原文已给出答案（说明里"仓库里没有 SWS OS 原文"不对，原文就在 `doc/ARTI/`）：

| Class | 事件（`_eventName`） | eventParameter |
| :--- | :--- | :--- |
| `AR_CP_OS_APPLICATION` | `OsApplication_Start`、`OsApplication_Restart`、`OsApplication_AllowAccess`、`OsApplication_Terminate` | ApplicationType |
| `AR_CP_OS_TASK` | `OsTask_Activate`、`OsTask_Start`、`OsTask_Preempt`、`OsTask_Wait`、`OsTask_Release`、`OsTask_Terminate` | TaskType |
| `AR_CP_OSARTI_TASK` | 上一行加 `OsTask_Resume`、`OsTask_Continue` | TaskType |
| `AR_CP_OS_CAT2ISR` | `OsCat2Isr_Start`、`OsCat2Isr_Stop` | ISRType |
| `AR_CP_OSARTI_CAT2ISR` | `OsCat2Isr_Activate`、`OsCat2Isr_Start`、`OsCat2Isr_Preempt`、`OsCat2Isr_Resume`、`OsCat2Isr_Stop` | ISRType |
| `AR_CP_OS_SERVICECALLS` | `OsServiceCall_<API名>_Start` / `_Return` | 按 SWS OS 表：Start 为参数，Return 为返回值或输出值 |
| `AR_CP_OS_SPINLOCK` | `OsSpinlock_Locked`、`OsSpinlock_Released` | SpinlockIdType |
| `AR_CP_OS_HOOK` | `OsHook_<hook名>_Start` / `_Return` | 按 SWS OS 表 |

与说明不一致之处（本变更同时修正说明）：
- SWS OS R21-11 **定义了** `AR_CP_OSARTI_CAT2ISR`（说明第五节第 1 条写的是"规范里没有"，那是只查了 R24-11 ARTI 文档的结论）。本 OS 按 SWS OS 使用独立的增强类。
- `AR_CP_OS_HOOK` 是 SWS OS 正式定义的类。抓包里出现的 `AR_CP_OS_ERROR`、`AR_CP_OS_EVENT` 不在 SWS OS 里，本变更不实现。
- SWS OS 7.17 开头示例里写的是 `OsTask_Activation`，但规范性的转换表写的是 `OsTask_Activate`，以表为准。

## D2 宏参数

- `_contextName`：每个调用点按调用时的中断状态写（SWS ARTI §8.7.1.1）。预期：任务、ISR、自旋锁、应用、PreTask/PostTask/Error/Protection hook 的调用点都在 `OsIsr_SuspendISR` 或 `OS_ISR_TP_DISABLE_LEVEL` 之内，用 `NOSUSP`；服务调用的入口 / 出口处中断是开着的，处在系统模式，用 `SPRVSR`。实现时逐点核对，核对结果写进事件表，不允许默认写 `NOSUSP`。
- `_instanceName`：OS 的短名，取 Os 配置里 `OsOS` 容器的 SHORT-NAME（SWS_Arti_00008 的 `<OS Short Name>`）。代码和 `ArtiHookInstance` 都从同一个模板变量取值（D7）。
- `instanceParameter`：OS 内的核索引，从 0 起连续编号。内核里就是 `Os_Inf_GetCoreId()` 的返回值，也就是停机描述里 `Os_OrtiRunningData[]` 的下标（`Os_Arti.arxml` 文件头的 A1）。新增 TypeMap `TM_ArtiCoreIndex` 把它映射成 `Core<物理核号>`。按说明第三节第 4 条，不能用 `PairOutputRef` 指向 `ArtiHardwareCoreInstance`。
- `eventParameter`：见 D1。任务、ISR、应用沿用已有的 `TM_TaskId`、`TM_Isr2Id`、`TM_ApplicationId`；新增 `TM_SpinlockId`。Error/Protection/Shutdown hook 的参数用已有的 LastError 错误码表。服务调用的 Start 参数类型因 API 而异，只对 ID 类参数挂 TypeMap，其余显示数值。
- 跨核调用：内核用核间中断加 RPC（`OsIoc_CrossCoreServiceCall` 把 `OsTask_ActivateTask` 等转到目标核执行），所以事件在目标核上发出，`instanceParameter` 就是执行核。说明第九节第 2 条到此定稿。

## D3 两种状态模型：私有参数 `OsVendorArtiStateModel`

- 取值 `STANDARD` / `ENHANCED`，默认 `ENHANCED`（SWS OS："If possible, the second state machine is to be preferred"；ETA 用标准类时执行时间偏小）。
- 同一参数同时决定任务类（`AR_CP_OS_TASK` 或 `AR_CP_OSARTI_TASK`）和 Cat2 类（`AR_CP_OS_CAT2ISR` 或 `AR_CP_OSARTI_CAT2ISR`），并写入 `ArtiStatesTaskEnhanced`。不给任务和 ISR 分别配置，避免组合出与 `ArtiStatesTaskEnhanced` 不一致的状态。
- 说明里的参数名 `OsVendorArtiTaskModel` 改为 `OsVendorArtiStateModel`，说明同步修改。

## D4 ARTI 影子状态：两种模型都需要

说明第四节第 3 条的骨架假设内核的 `State` 能直接用，但本内核有两处不满足：
1. ISR2 进入时，`OsTask_LeaveTaskLevel` 把被打断的任务改成 `READY`；ISR 退出后，`OsTask_DoScheduling` 又把它改回 `RUNNING`。ARTI 要求 ISR 打断任务时任务状态不变、不发 `Preempt`；而且在调度器里看到的情形（"当前任务 READY，下一个还是它"）和真正的抢占无法区分。
2. 内核的 `READY` 不区分刚激活、被抢占、被释放。

所以在 `Os_TaskDynamicType` 里加一个字段 `ArtiState`，只在 `OsUseArti` 打开且任务类启用时存在（`#if`），取值为 ARTI 的状态：Suspended / Activated / Running / Preempted / Waiting / Released。标准模型下只用到其中的 Suspended / Ready / Running / Waiting。分派时发什么事件、是否发事件，都根据 `ArtiState` 判断，不看内核的 `State`。代价是每个任务多 1 字节，ARTI 关闭时为 0。

Cat2 ISR 在增强模型下也加 `ArtiState`（Inactive / Activated / Running / Preempted），用于嵌套时发 `Preempt` / `Resume`。

## D5 插桩点（对应内核函数）

| 位置 | 条件 | 事件（增强 / 标准） | 说明 |
| :--- | :--- | :--- | :--- |
| `OsTask_ActivateTask` | `State` 由 `SUSPENDED` 变为 `READY` | `OsTask_Activate` | 在 `OsTask_AddTaskToScheduler` 之前（先写状态和事件，再入队）。多重激活不发事件 |
| `OsTask_DoScheduling`：换下的任务 | `ArtiState == Running` 且下一个任务不是它，并且内核 `State` 不是 `WAITING` / `SUSPENDED` | `OsTask_Preempt` | 由 ISR 退出触发的调度也走这里；下一个任务仍是它时什么都不发 |
| `OsTask_DoScheduling`：换上的任务 | 按 `ArtiState` | Activated→`Start`，Preempted→`Resume`，Released→`Continue` / 标准一律 `Start` | `ArtiState == Running`（ISR 返回原任务）时不发 |
| `OsEvent` 的 `WaitEvent` | 进入等待（`State = WAITING` 处） | `OsTask_Wait` | 事件已置位、不进入等待时不发（D10） |
| `OsEvent` 的 `SetEvent`（第 684 行附近） | `WAITING` 且命中所等事件 | `OsTask_Release` | 在 `OsTask_AddTaskToScheduler` 之前 |
| `OsTask_Internal_TerminateTask` | 正常终止 | `OsTask_Terminate` | `ActivationCount` 仍大于 0 时 `ArtiState` 置为 Activated，不再发 `Activate` |
| `OsTask_Internal_ChainTask` | — | `OsTask_Terminate`，然后对目标发 `OsTask_Activate` | 顺序固定 |
| `OsTask_TaskDeinit`（`TerminateApplication`、保护处置） | 任务不在 Suspended | `OsTask_Terminate` | 被终止的任务可能处于 Preempted / Waiting（D10） |
| `OsIsr_PreISR` | 通过时间保护检查后 | 被打断的是 ISR2 时先对它发 `OsCat2Isr_Preempt`（仅增强）；新 ISR 发 `Activate` + `Start` / 标准只发 `Start` | 被打断的是任务时，任务不发事件 |
| `OsIsr_PostISR`、`OsIsr_PostServiceCallISR` | 结束当前 ISR2 | `OsCat2Isr_Stop`；回到被打断的 ISR2 时对它发 `OsCat2Isr_Resume`（仅增强） | `Stop` 必须在 `OsTask_DoScheduling` 之前发出（说明第五节第 1 条的时序不变式）；`PostServiceCallISR` 只在 FIFO 处理完、真正退出时发 `Stop` |
| `OsSpinlock_Internal_GetSpinlock` / `TryToGetSpinlock` | 写入 `OwnerObjectID` 处（真正拿到锁） | `OsSpinlock_Locked` | 自旋等待期间不发 |
| `OsSpinlock_Internal_ReleaseSpinlock`、`OsSpinlock_SpinlockDeInit` | 清除 `OwnerObjectID` 处 | `OsSpinlock_Released` | 内核内部使用的自旋锁（`OsSpinlock_GetInternalSpinlock`）不发 |
| `Os_application.c` | `AppStatusRef` 赋值处：StartOS 置 ACCESSIBLE、RESTARTING、TERMINATED、`AllowAccess` | `OsApplication_Start` / `_Restart` / `_Terminate` / `_AllowAccess` | 第 403、622、856、863、971、1023 行附近 |
| `Os_hook.c` | 每个 hook 函数调用前后 | `OsHook_<名>_Start` / `_Return` | ProtectionHook 的 `_Return` 在 OS 处理完返回值之后发，参数为实际采取的动作（SWS OS 7.17.6） |
| 服务调用 | 各 `Os*_Internal_<API>` 里现有 `OsOrti_ServiceStart` / `OsOrti_ServiceEnd` 的位置 | `OsServiceCall_<API>_Start` / `_Return` | 只在应用上下文调用时发；OS 内部调用（如 `OsTask_ErrorReturn` 调 `OsTask_Internal_TerminateTask`）不发 |

Cat1 ISR 不经过 OS，不插桩（说明第五节第 2 条）。跨核服务 ISR（`XSIGNALISR_OSCORE<n>`）是配置里的普通 ISR 对象，按 Cat2 正常发事件。

## D6 零开销与编译开关

- 所有插桩点只调用生成的私有包装宏（`OS_ARTI_TASK(...)` 等），从不直接写 `ARTI_TRACE`（说明第三节第 2 条）。
- 生成的 `Os_ArtiHooks.h` 在 `OS_STATUS_USEARTI == STD_ON` 时 `#include "Os_Arti.h"`；类开关关闭或 `OsUseArti` 关闭时，宏展开为 `((void)0)`，只为 hook 准备的局部变量用 `OS_ARTI_DECL_*` 宏声明，同样消失。
- 影子状态字段和所有维护它的语句都放在 `#if` 里。
- 验收：`OsUseArti` 关闭时，用同一个工具链编译改动前后的内核，各目标文件的 `.text`、`.data`、`.bss` 大小和内容相同（D9）。

## D7 一份事件表，三处使用

- 新增 `templates/Os/Os_ArtiEvents.m`，用 EB 模板宏计算出启用的 (context, class, event, instance TypeMap, event TypeMap) 列表，包含 D3 的模型选择和类开关。
- `Os_Arti.arxml` 用它生成 `ArtiHook` 容器；`Os_ArtiHooks.h` 用它生成包装宏；`Os_Arti_Mock.h` 用它生成 Mock 展开宏。三者不会各写一份。
- 应用专属 hook（`ErrorHook_<App>`、`StartupHook_<App>`、`ShutdownHook_<App>`）的事件名里带应用名，而内核通过函数指针表调用它们，写不出字面 token。处理方法：`Os_ArtiHooks.h` 为每个应用生成一个 `switch (AppID)` 分发宏，每个分支用该应用的字面 token。
- 服务调用的事件名只为内核实际实现的 API 生成（依据内核里的 `OS_SERVICEID_*`）。SWS OS 表里本 OS 不支持的 API（如外设访问）不生成。

## D8 头文件结构

按 R22-11 及以后的结构（说明第三节第 1 条）：OS 只 `#include "Os_Arti.h"`，由它再包含 `Arti.h`。两者由 trace 工具提供。没有工具时，集成方把生成的 `Os_Arti_Mock.h` 改名或通过 include 路径当作 `Os_Arti.h` 使用；Mock 不作为产品代码。

## D9 验证（没有 TRACE32 的前提下）

1. **仓库测试（pytest）**：用夹具配置渲染 `Os_Arti.arxml` 与 `Os_ArtiHooks.h`，检查以下几点：
   - `ArtiHook` 的四个字面值与头文件里的 token 逐字一致；
   - 被 hook 引用的 TypeMap 输入值都在 0..65535 之内；
   - 结构符合 `Arti_ParamDef.arxml`，并通过 XSD 校验；
   - 关闭某个类后，该类在 ARXML 和头文件里都不出现；
   - 两种模型各自产出正确的类名，并且与 `ArtiStatesTaskEnhanced` 一致。
2. **编译检查（本机 `arm-none-eabi-gcc` 13.2）**：用 t1 的生成代码和 Mock 编译内核（`-fsyntax-only` 或只编译不链接）。Mock 对四个字面 token 做 `##` 拼接，并且只定义 `ArtiHook` 里列出的组合，所以参数顺序错误、token 拼错、类开关与描述不一致，都会导致编译失败。再比较开关关闭时改动前后的目标文件（D6）。
3. **事件流检查脚本** `tools/arti/check_event_stream.py`：输入 Mock 记录的按核环形缓冲区（由用户在目标板上用调试器导出内存），按说明第七节的合法迁移表逐条检查，并检查 ISR 的 `Stop` 先于后续任务事件、同一核上不会同时有两个 Running。脚本本身用合成的事件流做单元测试。
4. **上板运行**：说明第七节第 3 条的必备用例需要在目标板上运行，由用户完成。本变更提供用例清单和期望的事件序列。

## D10 默认约定（说明第九节第 3 条，待与工具方确认，写入手册）

- 多重激活：不发 `Activate`（状态没有迁移）。
- `WaitEvent` 时所等事件已置位：不发 `Wait` / `Release` / `Continue`。
- 强制终止处于 Preempted / Waiting 的任务：发 `Terminate`（规范状态图里没有这条边），检查脚本的迁移表把它列为本 OS 的扩展。
- ISR2 嵌套：增强模型发 `Preempt` / `Resume`；标准模型只有 `Start` / `Stop`，嵌套关系由工具推断。
- Cat2 的 `Activate`：内核拿不到中断挂起的时刻，`Activate` 与 `Start` 在同一处先后发出，时间差只有几条指令。手册中写明"挂起时间不可测"。

## D11 部署

~~以仓库 `templates/Os/` 为准~~（2026-10-13 按用户决定改为：模板只放在插件 `generate_PB/` 和工程的 `templates/Os/` 两处，以插件为准；仓库 `templates/` 已删除，测试经 `tests/generator/os_templates.py` 读插件目录或 `OS_TEMPLATE_DIR`）。`Os_Arti.arxml`、`Os_ArtiHooks.h`、`Os_ArtiEvents.m`、`Os_Arti_Mock.h` 部署到插件 `generate_PB/Os/` 和 t1 的 `templates/Os/Os/`。`Os_Arti.arxml` 目前只在 t1 里，插件中还没有，这次一并部署。插件的 SVN 提交由用户处理。

## 风险

- **调度路径的正确性**：插桩改的是调度器和 ISR 进出这些最敏感的路径。所有新增语句都在 `#if` 内，关闭时代码不变；打开时的正确性只能靠事件流检查和上板用例保证。
- **时间保护**：开启后关中断路径变长，可能误触发时间保护（说明第六节第 2 条）。手册要求在开启 ARTI 的配置下重新标定预算。
- **MPU**：服务调用事件在切到系统模式之后发出，hook 实现写 trace 缓冲区不受用户态 MPU 限制。若 trace 工具的实现需要特定内存区，由工具方说明。
- **规范与工具不一致**：TRACE32 抓包里的类名（如 `AR_CP_OS_CAT1ISR`、`AR_CP_OS_ERROR`）与 SWS OS 有出入。本 OS 按 SWS OS 实现，工具侧的映射由工具负责。

## 实现中的调整（相对上面的设计）

- **新增 `Os_ArtiCfg.h`（D6）**：影子状态字段的 `#if` 在每个编译单元里都必须看到同样的开关，否则结构体布局会不一致。开关因此单独生成到 `Os_ArtiCfg.h`，由 `Os_task_types.h`、`Os_isr_types.h` 包含。`Os_ArtiHooks.h` 包含它，同时也包含 trace 工具的 `Os_Arti.h`，所以不能被类型头文件包含。
- **Cat2 ISR 的影子状态两种模型都保留（D4）**：标准模型下只用到 Running / Inactive，嵌套时的 `Preempt` / `Resume` 只在增强模型下发出。强制终止 ISR 时，内核把它的上下文改到返回路径，之后照常经过 `OsIsr_PostISR` 发出 `Stop`，所以 `OsIsr_IsrDeInit` 不需要插桩。
- **NOSUSP 处处成立（任务 4.9）**：`ActivateTask` / `SetEvent` 的跨核路径在目标核的服务 ISR2 里执行；`OsHook_Hookreturn`、`OsTask_ErrorReturn` 的中断状态也不确定。因此任务、hook、应用、自旋锁释放（DeInit）的事件辅助函数都在本地调用 `OsIsr_SuspendISR` / `OsIsr_ResumeISR`，这对嵌套是安全的。Pre/PostTaskHook 的 Start 和 Return 各自单独加锁，用户 hook 本身不在关中断状态下运行。
- **服务调用**：在 `Os_ArtiHooks.h` 里增加 `OS_ARTI_SC_DECL` / `OS_ARTI_SC_BEGIN(Api, p)` / `OS_ARTI_SC_END(Api, p)`，用 `##` 拼出对应 API 的包装宏名，ARTI token 本身仍是字面值。事件都在系统模式下发出：普通服务放在 `Os*_Internal_*` 里原有 ORTI 服务点的位置；没有 ORTI 服务点的公开接口（中断类 API、`GetISRID`、中断源 API、`ShutdownOS`），以及两个分支各自调用 ORTI 的接口（`GetCoreID`、`GetCurrentApplicationID`、`GetActiveApplicationMode`），在每个系统模式分支里用内部块包住，因为在用户模式下读核号可能不被允许。`OsTask_ErrorReturn` 调用 `OsTask_TerminateTaskBody`；该类关闭时，这个名字由宏映射回原来的函数，目标代码不变。
- **`ChainTask` 的顺序**：内核先激活目标任务、再终止调用者，所以目标的 `Activate` 先于调用者的 `Terminate`。两者是不同对象的状态机，不按 D5 表里写的顺序调整内核。
- **只做停机调试的配置**：`OsUseArti` 打开、六类事件全关时，`Os_ArtiHooks.h` 不包含 `Os_Arti.h`，不需要 trace 工具。
- **检查脚本**放在 `tools/arti/check_event_stream.py`（仓库已有的 ARTI 工具包），测试在 `tests/generator/test_arti_event_stream.py`。

## 验证结果

见 `doc/ARTI/ARTI_hook_tracing.md` 第 4 节。要点：
- `OsUseArti` 关闭时，以及打开但六类全关时，内核 23 个目标文件与改动前逐字节相同（`arm-none-eabi-gcc` 13.2，`-O2`，t1 配置）。
- 开启时，两种模型以及服务调用开关的各种组合都能用严格 Mock 编译，没有新增警告。
- 上板用例还没有运行。
