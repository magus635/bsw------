# 自研 OS 内核 ARTI 动态 trace 插桩点清单

本文整理 THA6 自研 OS 内核里所有 ARTI（AUTOSAR Run-Time Interface）hook trace 的插桩点，供核对、评审与后续维护使用。

约定、配置参数和上板验证见 `ARTI_hook_tracing.md`（第 3 节是本 OS 的约定），本文不重复，只在需要时引用。

## 0. 范围、资料与读法

- 已插桩内核：`D:/19_AutosarOS/02_THA6204/02_Software/01_Code/01_Trunk/00_CodeProject/tr002_THA6_OS_Project/Os`。下文文件路径一律相对这个目录，行号是它**当前**的行号（`文件:行号`）。
- 包装宏与事件表来自配置器插件模板：`.../Os_THA6_ASR21/generate_PB/Os_ArtiEvents.m`（唯一事件表）和 `.../generate_PB/Os/kernel/Os_ArtiHooks.h`（包装宏，生成到 `Os_ArtiHooks.h`）。开关和影子状态常量来自同目录的 `Os_ArtiCfg.h`。这三个文件由生成器输出，**不在内核目录里**，内核只 `#include "Os_ArtiHooks.h"` / `"Os_ArtiCfg.h"`。
- 比对基线：插桩前原内核 `scratchpad/kernel_base/Os`。`scratchpad/kernel_basefix/Os` 是"原内核 + 两处非 ARTI 修复"（只有 `hook/Os_hook.c`、`isr/Os_isr.c` 与 kernel_base 不同，已逐文件核对）。`scratchpad` 指 `C:/Users/00048/AppData/Local/Temp/claude/D--bsw-------main-bsw------/69d1e05f-401b-4157-8d4f-41952157af67/scratchpad`。
- 三份 diff 的含义（均用 `diff -ru --strip-trailing-cr`，CRLF/LF 差异已忽略）：
  - `kernel_base/Os` 对 当前内核：15 个文件有差异，是 ARTI 插桩加两处修复；
  - `kernel_basefix/Os` 对 当前内核：同样 15 个文件，**仅 ARTI 插桩**（本文第 1~4 节依据它）；
  - `kernel_base/Os` 对 `kernel_basefix/Os`：2 个文件（`Os_hook.c`、`Os_isr.c`），**仅非 ARTI 修复**（第 5 节依据它）。
  - 现成的 `kernel_arti.diff` 没有使用（可能不是最新）。
- 事件名按**增强模型**（`OsVendorArtiStateModel = ENHANCED`，也是默认值）写：任务类 `AR_CP_OSARTI_TASK`，Cat2 ISR 类 `AR_CP_OSARTI_CAT2ISR`。标准模型下的差异：任务的 `Resume`/`Continue` 都映射成 `OsTask_Start`；Cat2 ISR 只有 `Start`/`Stop`，类名为 `AR_CP_OS_TASK`/`AR_CP_OS_CAT2ISR`（映射在 `Os_ArtiHooks.h` 模板中，`OS_ARTI_TASK_RESUME`/`OS_ARTI_TASK_CONTINUE`/`OS_ARTI_ISR2_*`）。
- 所有 `OS_ARTI_*` 宏在对应开关关闭或事件不在事件表时展开为 `((void)0)`；`OS_ARTI_SC_DECL/BEGIN/END` 在 `OS_ARTI_TRACE_SERVICECALLS != STD_ON` 时展开为空。六个类开关（`OS_ARTI_TRACE_APPLICATION/TASK/CAT2ISR/SERVICECALLS/SPINLOCK/HOOK`）在内核里以 `#if` 包住大部分插桩代码（见 6.3 节）。
- 事件上下文（`_contextName`）：服务调用事件为 `SPRVSR`，其余为 `NOSUSP`。`NOSUSP` 事件要求发出时中断已屏蔽；凡是可能从未加锁路径进入的点，内核先本地 `OsIsr_SuspendISR`（见第 4 节）。

### 0.1 宏的层次

| 层 | 名称 | 作用 |
|---|---|---|
| 内核调用的包装宏 | `OS_ARTI_TASK_<EV>(core, task)`、`OS_ARTI_ISR2_<EV>(core, isr)`、`OS_ARTI_APPLICATION_<EV>(core, app)`、`OS_ARTI_SPINLOCK_LOCKED/RELEASED(core, id)`、`OS_ARTI_HOOK_<HOOK>_START/RETURN(core, param)`、`OS_ARTI_APPHOOK_<HOOK>_START/RETURN(core, app, param)` | 把语义事件映射到 `OS_ARTI_EV_<事件名>`，事件不在事件表时为 `((void)0)` |
| 服务调用辅助宏 | `OS_ARTI_SC_DECL`、`OS_ARTI_SC_BEGIN(Api, param)`、`OS_ARTI_SC_END(Api, param)` | `DECL` 在声明区取 `OsArtiScCore = Os_Inf_GetCoreId()`；`BEGIN/END` 分别展开为 `OS_ARTI_SC_<Api>_START/_RETURN` |
| 最终的 trace 调用 | `OS_ARTI_EV_<事件名>(core, param)` → `ARTI_TRACE(ctx, class, instName, core, event, param)` | 由生成器按事件表输出 |

内核代码只调用上面前两层，从不直接调用 `ARTI_TRACE`。

## 1. 按文件列出的插桩点

共 15 个文件（13 个 `.c`、2 个 `_types.h`）。`#include` 与类型字段的改动见第 4 节。

**服务调用（`AR_CP_OS_SERVICECALLS`）的通用位置**：`OS_ARTI_SC_DECL` 在声明区；`OS_ARTI_SC_BEGIN` 紧跟在 `OsOrti_ServiceStart(...)` 之后、任何参数/上下文检查之前，不在内核关中断区内；`OS_ARTI_SC_END` 紧接在 `OsOrti_ServiceEnd(...)` 之前、最后一次 `OsIsr_ResumeISR` 之后（已用脚本核对：BEGIN 与 END 之间的 `OsIsr_SuspendISR`/`ResumeISR` 成对，END 之前最后一个是 Resume；`ReleaseResource` 有两条退出分支各自 Resume；没有关中断区的服务无此项）。因此 SC 事件**都在内核关中断区之外**（`SPRVSR` 语境）。下表凡不符合这个位置规律的函数都在备注里写明。函数里没有位于 BEGIN 与 END 之间的 `return`（已核对，唯一的"命中"都是注释里的单词）。跨核服务在目标核执行的是 `OsXxx_*` 本地实现（`ServiceCallCfg.EntryAddress` 指向它们），其中没有 SC 宏，所以服务调用事件只在调用方一侧的 `OsXxx_Internal_*` 函数里发出。

"事件"列里服务调用的事件名为 `OsServiceCall_<Api>_Start` 与 `_Return`，`<Api>` 即宏的第一个参数。参数取值写在"宏"列（Start 参数 / Return 参数）。

### 1.1 `alarm/Os_alarm.c`（5 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `alarm/Os_alarm.c:184` ; `224` | `OsAlarm_Internal_GetAlarmBase` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetAlarmBase, AlarmID)`<br>`OS_ARTI_SC_END(GetAlarmBase, (E_OK == Status) ? (uint32)(Info) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetAlarmBase_Start ; _Return |  |
| `alarm/Os_alarm.c:241` ; `299` | `OsAlarm_Internal_GetAlarm` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetAlarm, AlarmID)`<br>`OS_ARTI_SC_END(GetAlarm, (E_OK == Status) ? (uint32)(*Tick) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetAlarm_Start ; _Return |  |
| `alarm/Os_alarm.c:318` ; `372` | `OsAlarm_Internal_SetRelAlarm` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SetRelAlarm, AlarmID)`<br>`OS_ARTI_SC_END(SetRelAlarm, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SetRelAlarm_Start ; _Return |  |
| `alarm/Os_alarm.c:391` ; `445` | `OsAlarm_Internal_SetAbsAlarm` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SetAbsAlarm, AlarmID)`<br>`OS_ARTI_SC_END(SetAbsAlarm, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SetAbsAlarm_Start ; _Return |  |
| `alarm/Os_alarm.c:463` ; `513` | `OsAlarm_Internal_CancelAlarm` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CancelAlarm, AlarmID)`<br>`OS_ARTI_SC_END(CancelAlarm, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CancelAlarm_Start ; _Return |  |

### 1.2 `application/Os_application.c`（7 个服务 + 应用事件）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `application/Os_application.c:219` | `OsApp_Internal_Arti` | switch 的 `OS_ARTI_APP_EV_START` 分支 | `OS_ARTI_APPLICATION_START(ArtiCore, ApplicationID)` | AR_CP_OS_APPLICATION / OsApplication_Start | 辅助函数（205-232），自带 `OsIsr_SuspendISR/ResumeISR`（214/231）；被 :1051 调用 |
| `application/Os_application.c:222` | `OsApp_Internal_Arti` | `OS_ARTI_APP_EV_RESTART` 分支 | `OS_ARTI_APPLICATION_RESTART(...)` | AR_CP_OS_APPLICATION / OsApplication_Restart | 被 :930 调用 |
| `application/Os_application.c:225` | `OsApp_Internal_Arti` | `OS_ARTI_APP_EV_ALLOWACCESS` 分支 | `OS_ARTI_APPLICATION_ALLOWACCESS(...)` | AR_CP_OS_APPLICATION / OsApplication_AllowAccess | 被 :464 调用 |
| `application/Os_application.c:228` | `OsApp_Internal_Arti` | `default` 分支（TERMINATE） | `OS_ARTI_APPLICATION_TERMINATE(...)` | AR_CP_OS_APPLICATION / OsApplication_Terminate | 被 :690、:938、:1106 调用 |
| `application/Os_application.c:464` | `OsApp_Internal_AllowAccess` | `*AppStatusRef = APPLICATION_ACCESSIBLE` 之后、`result = E_OK` 之前 | 调用 `OsApp_Internal_Arti(Current_AppID, OS_ARTI_APP_EV_ALLOWACCESS)` | OsApplication_AllowAccess | 仅当 AllowAccess 成功置位时 |
| `application/Os_application.c:690` | `OsApp_SetAppTerminateStatus` | 置 `APPLICATION_TERMINATED` 之前 | 调用 `OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_TERMINATE)` | OsApplication_Terminate | 仅当原状态不是 TERMINATED；调用者 `Os_PreInit`（`kernel/Os_kernel.c:918`） |
| `application/Os_application.c:930` | `OsApp_TerminateApplication` | 置 `APPLICATION_RESTARTING` 之后、`OsTask_ActivateRestartTask` 之前 | 调用 `OsApp_Internal_Arti(Application, OS_ARTI_APP_EV_RESTART)` | OsApplication_Restart | `RestartOption == OS_OSAPPLICATION_RESTART` 分支；该函数也被保护 hook 处置（`OsHook_Internal_HandleProtectionReaction`，`hook/Os_hook.c:403/407`）和 TerminateApplication 服务（:524 跨核入口、:535 本核）调用 |
| `application/Os_application.c:938` | `OsApp_TerminateApplication` | else 分支，置 `APPLICATION_TERMINATED` 之前 | 调用 `OsApp_Internal_Arti(Application, OS_ARTI_APP_EV_TERMINATE)` | OsApplication_Terminate | 不重启分支；**无"状态已是 TERMINATED"判断**，直接发 |
| `application/Os_application.c:1051` | `OsApp_ApplicationInit` | 函数末尾，置 `APPLICATION_ACCESSIBLE` 之后 | 调用 `OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_START)` | OsApplication_Start | 调用者 `StartOS`（`kernel/Os_kernel.c:1025`） |
| `application/Os_application.c:1106` | `OsApp_ApplicationDeInit` | 函数末尾，置 `APPLICATION_TERMINATED` 之前 | 调用 `OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_TERMINATE)` | OsApplication_Terminate | 仅当原状态不是 TERMINATED；调用者 `OsKernel_ShutdownOSProcessing`（`kernel/Os_kernel.c:302`） |
| `application/Os_application.c:246` ; `247` | `OsApp_Internal_GetApplicationID` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetApplicationID, 0U)`<br>`OS_ARTI_SC_END(GetApplicationID, ArtiApp)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetApplicationID_Start ; _Return | BEGIN/END 在同一语句块内相邻（块内只读取 Current_Config_ApplicationID），位于 OsOrti_ServiceStart 与 OsOrti_ServiceEnd 之间 |
| `application/Os_application.c:268` ; `299` | `OsApp_Internal_CheckObjectOwnership` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CheckObjectOwnership, ObjectType)`<br>`OS_ARTI_SC_END(CheckObjectOwnership, AppID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CheckObjectOwnership_Start ; _Return |  |
| `application/Os_application.c:317` ; `345` | `OsApp_Internal_CheckObjectAccess` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CheckObjectAccess, ApplID)`<br>`OS_ARTI_SC_END(CheckObjectAccess, result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CheckObjectAccess_Start ; _Return |  |
| `application/Os_application.c:365` ; `415` | `OsApp_Internal_GetApplicationState` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetApplicationState, Application)`<br>`OS_ARTI_SC_END(GetApplicationState, (E_OK == result) ? (uint32)(*Value) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetApplicationState_Start ; _Return |  |
| `application/Os_application.c:434` ; `470` | `OsApp_Internal_AllowAccess` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(AllowAccess, 0U)`<br>`OS_ARTI_SC_END(AllowAccess, result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_AllowAccess_Start ; _Return |  |
| `application/Os_application.c:491` ; `548` | `OsApp_Internal_TerminateApplication` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(TerminateApplication, Application)`<br>`OS_ARTI_SC_END(TerminateApplication, result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_TerminateApplication_Start ; _Return |  |
| `application/Os_application.c:1156/1168` ; `1158/1170` | `GetCurrentApplicationID` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetCurrentApplicationID, 0U)`<br>`OS_ARTI_SC_END(GetCurrentApplicationID, AppID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetCurrentApplicationID_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处；块内包住 `AppID = ...Current_ApplicationID` 一行 |

### 1.3 `counter/Os_counter.c`（3 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `counter/Os_counter.c:780` ; `826` | `OsCounter_Internal_IncrementCounter` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(IncrementCounter, CounterID)`<br>`OS_ARTI_SC_END(IncrementCounter, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_IncrementCounter_Start ; _Return |  |
| `counter/Os_counter.c:844` ; `885` | `OsCounter_Internal_GetCounterValue` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetCounterValue, CounterID)`<br>`OS_ARTI_SC_END(GetCounterValue, (E_OK == Status) ? (uint32)(*Value) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetCounterValue_Start ; _Return |  |
| `counter/Os_counter.c:904` ; `949` | `OsCounter_Internal_GetElapsedValue` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetElapsedValue, CounterID)`<br>`OS_ARTI_SC_END(GetElapsedValue, (E_OK == Status) ? (uint32)(*ElapsedValue) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetElapsedValue_Start ; _Return |  |

### 1.4 `event/Os_event.c`（5 个服务 + 任务 Wait / Release）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `event/Os_event.c:531-532` | `OsEvent_Internal_WaitEvent` | 在 `OsIsr_SuspendISR(&Level)`（:510）的关中断区内；`TaskDynPtr->State = WAITING` 之后、`OsTask_DoScheduling(SAVING_CONTEXT)` 之前 | `TaskDynPtr->ArtiState = OS_ARTI_TASK_WAITING;`（531）<br>`OS_ARTI_TASK_WAIT(ArtiCore, SchedulerPtr->CurrentTask)`（532） | AR_CP_OSARTI_TASK / OsTask_Wait | 仅在任务真正进入等待时（`TaskEnterWaitState == TRUE`）；所等事件已置位则不发。无本地屏蔽（已在服务的关中断区内） |
| `event/Os_event.c:722-726`（宏在 :725） | `OsEvent_SetEvent` | `TP 时间帧检查` 通过后、`OsTask_AddTaskToScheduler` 之前；**本地** `OsIsr_SuspendISR`(:722) … `OsIsr_ResumeISR`(:726) | `TaskDynPtr->ArtiState = OS_ARTI_TASK_RELEASED;`（:724）<br>`OS_ARTI_TASK_RELEASE(ArtiCore, TaskID)`（:725） | AR_CP_OSARTI_TASK / OsTask_Release | 条件：被置事件命中 `EventWait` 且任务处于 `WAITING`。跨核 SetEvent 由目标核的服务 ISR2 执行此函数，故本地屏蔽 |
| `event/Os_event.c:184` ; `248` | `OsEvent_Internal_SetEvent` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SetEvent, TaskID)`<br>`OS_ARTI_SC_END(SetEvent, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SetEvent_Start ; _Return |  |
| `event/Os_event.c:267` ; `317` | `OsEvent_Internal_SetEventAsyn` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SetEventAsyn, TaskID)`<br>`OS_ARTI_SC_END(SetEventAsyn, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SetEventAsyn_Start ; _Return | END 参数固定 `0U`（无返回值） |
| `event/Os_event.c:336` ; `372` | `OsEvent_Internal_ClearEvent` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ClearEvent, Mask)`<br>`OS_ARTI_SC_END(ClearEvent, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ClearEvent_Start ; _Return |  |
| `event/Os_event.c:390` ; `453` | `OsEvent_Internal_GetEvent` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetEvent, TaskID)`<br>`OS_ARTI_SC_END(GetEvent, (E_OK == Status) ? (uint32)(*Event) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetEvent_Start ; _Return |  |
| `event/Os_event.c:475` ; `551` | `OsEvent_Internal_WaitEvent` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(WaitEvent, Mask)`<br>`OS_ARTI_SC_END(WaitEvent, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_WaitEvent_Start ; _Return |  |

### 1.5 `hook/Os_hook.c`（hook 事件）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `hook/Os_hook.c:208-217` | `OsHook_Internal_Arti` | 应用 hook 分支（`OBJECT_APPHOOK == HookObjectInfo->ObjectType`）的 switch | `OS_ARTI_APPHOOK_ERRORHOOK_START/RETURN`（208/209）<br>`OS_ARTI_APPHOOK_STARTUPHOOK_START/RETURN`（212/213）<br>`OS_ARTI_APPHOOK_SHUTDOWNHOOK_START/RETURN`（216/217） | AR_CP_OS_HOOK / `OsHook_ErrorHook_<App>_Start/_Return`、`OsHook_StartupHook_<App>_*`、`OsHook_ShutdownHook_<App>_*` | `<App>` 由应用 ID 在运行时选字面量（`Os_ArtiHooks.h` 里按应用 ID 的 switch）；应用没有 ProtectionHook，故 switch 无该分支。辅助函数 187-251（块 181-252），自带 `OsIsr_SuspendISR/ResumeISR`（200/248） |
| `hook/Os_hook.c:229-242` | `OsHook_Internal_Arti` | 内核 hook 分支的 switch | `OS_ARTI_HOOK_ERRORHOOK_START/RETURN`（229/230）<br>`OS_ARTI_HOOK_STARTUPHOOK_START/RETURN`（233/234）<br>`OS_ARTI_HOOK_SHUTDOWNHOOK_START/RETURN`（237/238）<br>`OS_ARTI_HOOK_PROTECTIONHOOK_START/RETURN`（241/242） | AR_CP_OS_HOOK / `OsHook_ErrorHook_Start/_Return`、`OsHook_StartupHook_*`、`OsHook_ShutdownHook_*`、`OsHook_ProtectionHook_*` | 同上；`Start` 参数为 `Param`，`Return` 的参数见各调用点 |
| `hook/Os_hook.c:299` | `OsHook_Internal_CallHook` | 切到 hook 对象的上下文**之前**（`Os_Hal_ContextSetParam` 之后、`Os_Hal_ContextSwitch` 之前） | 调用 `OsHook_Internal_Arti(Os_HookConPtr->HookName, HookObjectInfo, (uint32)Error, TRUE)` | 各 hook 的 `_Start` | 所有经 `CallHook` 的 hook（Error/Startup/Shutdown/Protection，核级与应用级）。`Param` = `Error`（Startup 传 `E_OK`，Shutdown/Protection 传错误码） |
| `hook/Os_hook.c:477` | `OsHook_Hookreturn` | 读出 hook 返回值与当前对象之后、处理 `RunningHookMask` 之前 | 调用 `OsHook_Internal_Arti(HookType, CurrentObjectInfo, 0U, FALSE)`，**`PROTECTIONHOOK != HookType` 时** | 各 hook 的 `_Return` | hook 返回时的统一出口；ProtectionHook 不在这里发 Return（见下一行）。`Param` 固定 0 |
| `hook/Os_hook.c:558` | `OsHook_CallProtectionHook` | `VerifyProtectionReaction` 校验并写 `Os_HookDynPtr->ProtectionReaction` 之后、`HandleProtectionReaction` 之前 | 调用 `OsHook_Internal_Arti(PROTECTIONHOOK, OsApp_GetSpecific_ObjectInfo(Os_CoreHookConPtr->ObjectID), (uint32)Os_HookDynPtr->ProtectionReaction, FALSE)` | AR_CP_OS_HOOK / OsHook_ProtectionHook_Return | 仅当配置了 ProtectionHook（`Os_CoreHookConPtr != NULL_PTR`）；参数为 OS 实际采取的处置（SWS OS 7.17.6） |
| `hook/Os_hook.c:633` / `:637` | `OsHook_CallPreTaskHook` | `PreTaskHook()` 调用前后各一个块；各自**本地**屏蔽中断（:632-634、:636-638） | `OS_ARTI_HOOK_PRETASKHOOK_START(ArtiCore, 0U)`、`OS_ARTI_HOOK_PRETASKHOOK_RETURN(ArtiCore, 0U)` | AR_CP_OS_HOOK / OsHook_PreTaskHook_Start / _Return | 仅 `PRETASKHOOK == STD_ON`；`PreTaskHook()` 本身在中断放开状态下执行。`ArtiCore` 在 `SuspendISR` **之前**取得（:631） |
| `hook/Os_hook.c:663` / `:667` | `OsHook_CallPostTaskHook` | 同上 | `OS_ARTI_HOOK_POSTTASKHOOK_START/RETURN(ArtiCore, 0U)` | AR_CP_OS_HOOK / OsHook_PostTaskHook_Start / _Return | 仅 `POSTTASKHOOK == STD_ON`；同上 |

### 1.6 `isr/Os_isr.c`（10 个服务，各 2 个分支；Cat2 ISR 事件）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `isr/Os_isr.c:1087` | `OsIsr_Internal_ArtiStart` | 仅当被打断对象是 ISR（`OBJECT_ISR == InterruptedObject->ObjectType`） | `Os_IsrConfigSet[InterruptedIsr]->IsrRunningData->ArtiState = OS_ARTI_ISR_PREEMPTED;`（:1086）<br>`OS_ARTI_ISR2_PREEMPT(ArtiCore, InterruptedIsr)` | AR_CP_OSARTI_CAT2ISR / OsCat2Isr_Preempt | 嵌套 ISR2：被打断的 ISR2 报 Preempt（被打断的任务不在这里报，任务靠 `OsTask_Internal_ArtiLeave`）。辅助函数从 :1072 起，不自带屏蔽（调用者 `PreISR` 已 `OsIsr_SuspendISR`） |
| `isr/Os_isr.c:1090` | `OsIsr_Internal_ArtiStart` | 同上，接在 Preempt 之后 | `...->ArtiState = OS_ARTI_ISR_RUNNING;`（:1089）<br>`OS_ARTI_ISR2_ACTIVATE(ArtiCore, IsrID)` | AR_CP_OSARTI_CAT2ISR / OsCat2Isr_Activate | 内核不知道中断何时挂起：**Activate 与 Start 连续发出** |
| `isr/Os_isr.c:1091` | `OsIsr_Internal_ArtiStart` | 紧接 Activate | `OS_ARTI_ISR2_START(ArtiCore, IsrID)` | AR_CP_OSARTI_CAT2ISR / OsCat2Isr_Start | 标准模型下为类 `AR_CP_OS_CAT2ISR` 的 Start |
| `isr/Os_isr.c:1144` | `OsIsr_PreISR` | 在 `OsIsr_SuspendISR(&SuspendLevel)` 区内；TP 检查通过、`OsTask_LeaveTaskLevel()`（若被打断的是任务）与 `OsOrti_ChangeIsr` 之后、`OsApp_ChangeCurrent_AppInfo(NextIsr->ObjectID)` 之前 | 调用 `OsIsr_Internal_ArtiStart(CurrentObject, NextIsr->ISRID)` | 触发 Preempt(条件)/Activate/Start | 含跨核服务 ISR2（`isCrossCore`）——同一入口，没有区分 |
| `isr/Os_isr.c:1106` | `OsIsr_Internal_ArtiStop` | 先写状态再发 | `...->ArtiState = OS_ARTI_ISR_INACTIVE;`（:1105）<br>`OS_ARTI_ISR2_STOP(ArtiCore, IsrID)` | AR_CP_OSARTI_CAT2ISR / OsCat2Isr_Stop | 辅助函数从 :1095 起 |
| `isr/Os_isr.c:1111` | `OsIsr_Internal_ArtiStop` | 仅当被打断对象是 ISR | `...->ArtiState = OS_ARTI_ISR_RUNNING;`（:1110）<br>`OS_ARTI_ISR2_RESUME(ArtiCore, InterruptedIsr)` | AR_CP_OSARTI_CAT2ISR / OsCat2Isr_Resume | 嵌套 ISR2 返回：被打断的 ISR2 报 Resume |
| `isr/Os_isr.c:1244` | `OsIsr_PostISR` | 出口：已 `OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL)`（:1193）；`OsIsr_Hal_EndOfInterrupt`、`OsApp_GetPrevious_ObjectInfo()` 之后，**重调度/上下文切回之前** | 调用 `OsIsr_Internal_ArtiStop(CurrentISRID, PreviousObject)` | Stop(+Resume) | 代码注释：Stop 先于它引起的任务事件。在 PostISR 的 [SWS_Os_00368/00369] 错误处理（见第 5 节）之后 |
| `isr/Os_isr.c:1303` | `OsIsr_PostServiceCallISR` | 服务调用 ISR2 出口：`ServiceChannelCfg` 里**没有未处理的服务**分支（`WriteIndex == ReadIndex`），`EndOfInterrupt`、取得 `PreviousObject` 之后、重调度之前；入口已 `OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL)`（:1281） | 调用 `OsIsr_Internal_ArtiStop(CurrentISRID, PreviousObject)` | Stop(+Resume) | 队列里还有服务时（else 分支）不发 Stop，服务 ISR2 继续运行 |
| `isr/Os_isr.c:543/554` ; `545/556` | `EnableAllInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(EnableAllInterrupts, 0U)`<br>`OS_ARTI_SC_END(EnableAllInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_EnableAllInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:572/583` ; `574/585` | `DisableAllInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(DisableAllInterrupts, 0U)`<br>`OS_ARTI_SC_END(DisableAllInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_DisableAllInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:601/612` ; `603/614` | `ResumeAllInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(ResumeAllInterrupts, 0U)`<br>`OS_ARTI_SC_END(ResumeAllInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ResumeAllInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:630/641` ; `632/643` | `SuspendAllInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(SuspendAllInterrupts, 0U)`<br>`OS_ARTI_SC_END(SuspendAllInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SuspendAllInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:659/670` ; `661/672` | `ResumeOSInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(ResumeOSInterrupts, 0U)`<br>`OS_ARTI_SC_END(ResumeOSInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ResumeOSInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:688/699` ; `690/701` | `SuspendOSInterrupts` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(SuspendOSInterrupts, 0U)`<br>`OS_ARTI_SC_END(SuspendOSInterrupts, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SuspendOSInterrupts_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:719/730` ; `721/732` | `GetISRID` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(GetISRID, 0U)`<br>`OS_ARTI_SC_END(GetISRID, ISRID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetISRID_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:751/762` ; `753/764` | `DisableInterruptSource` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(DisableInterruptSource, ISRID)`<br>`OS_ARTI_SC_END(DisableInterruptSource, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_DisableInterruptSource_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:785/796` ; `787/798` | `EnableInterruptSource` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(EnableInterruptSource, ISRID)`<br>`OS_ARTI_SC_END(EnableInterruptSource, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_EnableInterruptSource_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |
| `isr/Os_isr.c:818/829` ; `820/831` | `ClearPendingInterrupt` | 入口/出口（包住实现调用） | `OS_ARTI_SC_BEGIN(ClearPendingInterrupt, ISRID)`<br>`OS_ARTI_SC_END(ClearPendingInterrupt, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ClearPendingInterrupt_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处（真分支在 `Os_Inf_TrapToSystemMode()` 之后），块内包住 `OsIsr_Internal_*`/`OsIsr_*` 实现调用；本函数没有 OsOrti_Service*。BEGIN/END 都在实现调用之外，不在其关中断区内 |

### 1.7 `isr/Os_isr_types.h`（仅类型）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `isr/Os_isr_types.h:46`、`:73-75` | — | 无宏调用 | `#include "Os_ArtiCfg.h"`（:46）；`Os_IsrDynamicType` 增加 `uint8 ArtiState`（受 `OS_ARTI_TRACE_CAT2ISR` 控制） | — | 见第 3、4 节 |

### 1.8 `kernel/Os_kernel.c`（8 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `kernel/Os_kernel.c:244` | `OsKernel_Internal_ShutdownAllCores` | 入口(BEGIN)：关中断区外 | `OS_ARTI_SC_BEGIN(ShutdownAllCores, Error)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ShutdownAllCores_Start（无 Return） | 仅 Start（服务不返回）；位于 OsOrti_ServiceStart 之后、扩展错误检查之前 |
| `kernel/Os_kernel.c:324` ; `341` | `OsKernel_Internal_GetNumberOfActivatedCores` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetNumberOfActivatedCores, 0U)`<br>`OS_ARTI_SC_END(GetNumberOfActivatedCores, ActivatedCoresNumber)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetNumberOfActivatedCores_Start ; _Return |  |
| `kernel/Os_kernel.c:386` ; `435` | `OsKernel_Internal_ControlIdle` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ControlIdle, CoreID)`<br>`OS_ARTI_SC_END(ControlIdle, result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ControlIdle_Start ; _Return |  |
| `kernel/Os_kernel.c:971` | `StartOS` | 入口(BEGIN)：关中断区外 | `OS_ARTI_SC_BEGIN(StartOS, Mode)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StartOS_Start（无 Return） | 仅 Start（服务不返回，Os_ArtiEvents.m 返回类型图为 x）；位于 `OsOrti_OrtiInit(Mode)` 之后、`OsIsr_SuspendISR2` 之前的独立语句块 |
| `kernel/Os_kernel.c:1047` ; `1080` | `StartCore` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(StartCore, CoreID)`<br>`OS_ARTI_SC_END(StartCore, *Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StartCore_Start ; _Return | END 参数取 `*Status` |
| `kernel/Os_kernel.c:1101/1114` ; `1103/1116` | `GetCoreID` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetCoreID, 0U)`<br>`OS_ARTI_SC_END(GetCoreID, CoreID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetCoreID_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处；块内包住 `Os_Inf_GetCoreId()` 一行 |
| `kernel/Os_kernel.c:1138/1148` | `ShutdownOS` | 入口(BEGIN)：关中断区外 | `OS_ARTI_SC_BEGIN(ShutdownOS, Error)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ShutdownOS_Start（无 Return） | 仅 Start（服务不返回）；`IsNeedSysTrap()` 真/假两个分支各一处，包在 `OsKernel_Internal_ShutdownOS(Error)` 之前 |
| `kernel/Os_kernel.c:1241/1253` ; `1243/1255` | `GetActiveApplicationMode` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetActiveApplicationMode, 0U)`<br>`OS_ARTI_SC_END(GetActiveApplicationMode, ActiveAppMode)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetActiveApplicationMode_Start ; _Return | `IsNeedSysTrap()` 真/假两个分支各一处；块内包住 `ActiveAppMode = OsKernel_StartOS_OsMode` 一行 |

### 1.9 `mpu/Os_mpu.c`（11 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `mpu/Os_mpu.c:492` ; `517` | `OsAccess_Internal_CheckObjectMemoryAccess` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CheckTaskMemoryAccess, TaskID)`<br>`OS_ARTI_SC_END(CheckTaskMemoryAccess, Result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CheckTaskMemoryAccess_Start ; _Return |  |
| `mpu/Os_mpu.c:539` ; `564` | `OsAccess_Internal_CheckISRMemoryAccess` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CheckISRMemoryAccess, ISRID)`<br>`OS_ARTI_SC_END(CheckISRMemoryAccess, Result)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CheckISRMemoryAccess_Start ; _Return |  |
| `mpu/Os_mpu.c:625` ; `665` | `OsPeripheral_Internal_Read8` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ReadPeripheral8, Address)`<br>`OS_ARTI_SC_END(ReadPeripheral8, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ReadPeripheral8_Start ; _Return |  |
| `mpu/Os_mpu.c:684` ; `725` | `OsPeripheral_Internal_Read16` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ReadPeripheral16, Address)`<br>`OS_ARTI_SC_END(ReadPeripheral16, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ReadPeripheral16_Start ; _Return |  |
| `mpu/Os_mpu.c:744` ; `784` | `OsPeripheral_Internal_Read32` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ReadPeripheral32, Address)`<br>`OS_ARTI_SC_END(ReadPeripheral32, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ReadPeripheral32_Start ; _Return |  |
| `mpu/Os_mpu.c:803` ; `844` | `OsPeripheral_Internal_Write8` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(WritePeripheral8, Address)`<br>`OS_ARTI_SC_END(WritePeripheral8, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_WritePeripheral8_Start ; _Return |  |
| `mpu/Os_mpu.c:863` ; `904` | `OsPeripheral_Internal_Write16` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(WritePeripheral16, Address)`<br>`OS_ARTI_SC_END(WritePeripheral16, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_WritePeripheral16_Start ; _Return |  |
| `mpu/Os_mpu.c:923` ; `964` | `OsPeripheral_Internal_Write32` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(WritePeripheral32, Address)`<br>`OS_ARTI_SC_END(WritePeripheral32, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_WritePeripheral32_Start ; _Return |  |
| `mpu/Os_mpu.c:984` ; `1027` | `OsPeripheral_Internal_Modify8` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ModifyPeripheral8, Address)`<br>`OS_ARTI_SC_END(ModifyPeripheral8, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ModifyPeripheral8_Start ; _Return |  |
| `mpu/Os_mpu.c:1047` ; `1089` | `OsPeripheral_Internal_Modify16` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ModifyPeripheral16, Address)`<br>`OS_ARTI_SC_END(ModifyPeripheral16, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ModifyPeripheral16_Start ; _Return |  |
| `mpu/Os_mpu.c:1112` ; `1151` | `OsPeripheral_Internal_Modify32` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ModifyPeripheral32, Address)`<br>`OS_ARTI_SC_END(ModifyPeripheral32, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ModifyPeripheral32_Start ; _Return |  |

> 备注：`CheckTaskMemoryAccess`、`CheckISRMemoryAccess` 的实现函数分别叫 `OsAccess_Internal_CheckObjectMemoryAccess`（task 版，:492）和 `OsAccess_Internal_CheckISRMemoryAccess`。表中"函数"列是代码里实际的函数名，"事件"列的 `<Api>` 来自宏参数。

### 1.10 `resource/Os_resource.c`（2 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `resource/Os_resource.c:163` ; `233` | `OsResource_Internal_GetResource` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetResource, ResID)`<br>`OS_ARTI_SC_END(GetResource, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetResource_Start ; _Return |  |
| `resource/Os_resource.c:252` ; `340` | `OsResource_Internal_ReleaseResource` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ReleaseResource, ResID)`<br>`OS_ARTI_SC_END(ReleaseResource, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ReleaseResource_Start ; _Return |  |

### 1.11 `scheduletable/Os_scheduletable.c`（8 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `scheduletable/Os_scheduletable.c:565` ; `610` | `OsSchT_Internal_StartRel` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(StartScheduleTableRel, SchTID)`<br>`OS_ARTI_SC_END(StartScheduleTableRel, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StartScheduleTableRel_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:703` ; `742` | `OsSchT_Internal_StartAbs` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(StartScheduleTableAbs, SchTID)`<br>`OS_ARTI_SC_END(StartScheduleTableAbs, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StartScheduleTableAbs_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:836` ; `875` | `OsSchT_Internal_Stop` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(StopScheduleTable, SchTID)`<br>`OS_ARTI_SC_END(StopScheduleTable, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StopScheduleTable_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:898` ; `981` | `OsSchT_Internal_Next` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(NextScheduleTable, SchT_To_ID)`<br>`OS_ARTI_SC_END(NextScheduleTable, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_NextScheduleTable_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:1011` ; `1065` | `OsSchT_Internal_StartSynchron` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(StartScheduleTableSynchron, SchTID)`<br>`OS_ARTI_SC_END(StartScheduleTableSynchron, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_StartScheduleTableSynchron_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:1285` ; `1381` | `OsSchT_Internal_Sync` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SyncScheduleTable, SchTID)`<br>`OS_ARTI_SC_END(SyncScheduleTable, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SyncScheduleTable_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:1398` ; `1464` | `OsSchT_Internal_SetAsync` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(SetScheduleTableAsync, SchTID)`<br>`OS_ARTI_SC_END(SetScheduleTableAsync, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_SetScheduleTableAsync_Start ; _Return |  |
| `scheduletable/Os_scheduletable.c:1554` ; `1594` | `OsSchT_Internal_GetStatus` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetScheduleTableStatus, SchTID)`<br>`OS_ARTI_SC_END(GetScheduleTableStatus, (E_OK == Status) ? (uint32)(*ScheduleStatus) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetScheduleTableStatus_Start ; _Return |  |

### 1.12 `services/Os_services.c`（1 个服务）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `services/Os_services.c:112` ; `217` | `OsService_Internal_CallTrustedFunction` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(CallTrustedFunction, FunctionIndex)`<br>`OS_ARTI_SC_END(CallTrustedFunction, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_CallTrustedFunction_Start ; _Return |  |

### 1.13 `spinlock/Os_spinlock.c`（3 个服务 + 自旋锁事件）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `spinlock/Os_spinlock.c:337` | `OsSpinlock_Internal_GetSpinlock` | 自旋循环里，`OsIsr_SuspendISR`（:307）与 `OsIsr_ResumeISR`（:342）之间；`Getlock` 返回 TRUE、入锁表、写 `OwnerObjectID` 之后 | `OS_ARTI_SPINLOCK_LOCKED(ArtiCore, SpinlockId)` | AR_CP_OS_SPINLOCK / OsSpinlock_Locked | 取得锁时才发，自旋等待期间不发 |
| `spinlock/Os_spinlock.c:466` | `OsSpinlock_Internal_TryToGetSpinlock` | `OsIsr_SuspendISR`（:434）区内，`Result == TRUE` 分支、写 `OwnerObjectID` 之后 | `OS_ARTI_SPINLOCK_LOCKED(ArtiCore, SpinlockId)` | AR_CP_OS_SPINLOCK / OsSpinlock_Locked | 只在 `TRYTOGETSPINLOCK_SUCCESS` 时 |
| `spinlock/Os_spinlock.c:537` | `OsSpinlock_Internal_ReleaseSpinlock` | `OsIsr_SuspendISR`（:532）之后、`OsSpinlock_Hal_Releaselock`（:541）**之前** | `OS_ARTI_SPINLOCK_RELEASED(ArtiCore, SpinlockId)` | AR_CP_OS_SPINLOCK / OsSpinlock_Released | 放在硬件释放之前：释放之后别的核可能已经发出 Locked（代码注释 :535） |
| `spinlock/Os_spinlock.c:854` | `OsSpinlock_SpinlockDeInit` | 函数开头、`OsSpinlock_Hal_Releaselock`（:859）之前；**本地** `OsIsr_SuspendISR`(:852) … `ResumeISR`(:856) | `OS_ARTI_SPINLOCK_RELEASED(ArtiCore, SpinlockId)` | AR_CP_OS_SPINLOCK / OsSpinlock_Released | 因终止对象代为释放（经 `OsLock_ClearLockList`(`resource/Os_lock.c:105`)、`OsTask_ErrorReturn`(`task/Os_task.c:1371`)、`OsTask_TaskDeinit`(`task/Os_task.c:1691`)）；条件 `OwnerObjectID != 0xFFFFFFFF`（锁确有持有者）；经 `OsTask_ErrorReturn` 进入时没有内核锁，所以要本地屏蔽 |
| `spinlock/Os_spinlock.c:244` ; `354` | `OsSpinlock_Internal_GetSpinlock` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetSpinlock, SpinlockId)`<br>`OS_ARTI_SC_END(GetSpinlock, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetSpinlock_Start ; _Return |  |
| `spinlock/Os_spinlock.c:375` ; `487` | `OsSpinlock_Internal_TryToGetSpinlock` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(TryToGetSpinlock, SpinlockId)`<br>`OS_ARTI_SC_END(TryToGetSpinlock, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_TryToGetSpinlock_Start ; _Return |  |
| `spinlock/Os_spinlock.c:506` ; `611` | `OsSpinlock_Internal_ReleaseSpinlock` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ReleaseSpinlock, SpinlockId)`<br>`OS_ARTI_SC_END(ReleaseSpinlock, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ReleaseSpinlock_Start ; _Return |  |

### 1.14 `task/Os_task.c`（7 个服务 + 任务事件）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `task/Os_task.c:232` | `OsTask_Internal_ArtiActivate` | 本地屏蔽 `OsIsr_SuspendISR`(:229) … `ResumeISR`(:233) 内；先写状态再发 | `OsTask_GetTaskDyn(TaskID)->ArtiState = OS_ARTI_TASK_ACTIVATED;`（:231）<br>`OS_ARTI_TASK_ACTIVATE(ArtiCore, TaskID)` | AR_CP_OSARTI_TASK / OsTask_Activate | 辅助函数 220-234（块 213-316）；调用点：`OsTask_TaskInit`:1250（自启动）、`OsTask_ActivateTask`:1469、`OsTask_Internal_ChainTask`:565（链到自己） |
| `task/Os_task.c:248` | `OsTask_Internal_ArtiTerminate` | 本地屏蔽(:245/:258) | `OS_ARTI_TASK_TERMINATE(ArtiCore, TaskID)`；随后写 `ArtiState`（:252 / :256） | AR_CP_OSARTI_TASK / OsTask_Terminate | 辅助函数 236-259；调用点：`OsTask_TerminateTaskBody`:468、`OsTask_Internal_ChainTask`:564（链到自己）与 :601（链到别的任务）、`OsTask_TaskDeinit`:1702（强制终止） |
| `task/Os_task.c:278` | `OsTask_Internal_ArtiLeave` | 仅当 `CurrentTaskID != NextTaskID` 且 `ArtiState == RUNNING` 时，本地屏蔽(:275/:279) | `...->ArtiState = OS_ARTI_TASK_PREEMPTED;`（:277）<br>`OS_ARTI_TASK_PREEMPT(ArtiCore, CurrentTaskID)` | AR_CP_OSARTI_TASK / OsTask_Preempt | 辅助函数 262-281；调用点 `OsTask_DoScheduling`:1123（在 `OsHook_CallPostTaskHook` 之后，`SchedulerPtr->CurrentTask = NextTaskID` 之前）。任务在 Terminate/Wait 后让出 CPU 时 `ArtiState` 已不是 RUNNING，不会发 Preempt |
| `task/Os_task.c:302` / `:305` / `:309` | `OsTask_Internal_ArtiEnter` | 仅当 `ArtiState != RUNNING`，本地屏蔽(:297/:313)，按 `ArtiState` 的 switch | `OS_ARTI_TASK_RESUME`（:302，`PREEMPTED`）<br>`OS_ARTI_TASK_CONTINUE`（:305，`RELEASED`）<br>`OS_ARTI_TASK_START`（:309，default 即 `ACTIVATED`）；最后 `ArtiState = RUNNING`（:312） | AR_CP_OSARTI_TASK / OsTask_Resume / OsTask_Continue / OsTask_Start | 辅助函数 285-315；调用点 `OsTask_DoScheduling`:1146（`OsApp_ChangeCurrent_AppInfo` 之后、`OsHook_CallPreTaskHook` 之前）。任务本来就在 RUNNING（从 ISR2 或 hook 回到同一任务）则不发。其它状态走 default 发 Start（注释称"事件流检查会报告不一致"） |
| `task/Os_task.c:1258` | `OsTask_TaskInit` | 非自启动分支，`State = SUSPENDED` 之后 | `TaskDynPtr->ArtiState = OS_ARTI_TASK_SUSPENDED;` | — | 只写影子状态，不发事件 |
| `task/Os_task.c:213-316` | — | 受 `OS_ARTI_TRACE_TASK` 控制的 4 个 static 辅助函数的整块定义 | — | — | 见第 4.2 节 |
| `task/Os_task.c:333` ; `388` | `OsTask_Internal_ActivateTask` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ActivateTask, TaskID)`<br>`OS_ARTI_SC_END(ActivateTask, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ActivateTask_Start ; _Return |  |
| `task/Os_task.c:412` ; `415` | `OsTask_Internal_TerminateTask` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(TerminateTask, ArtiTask)`<br>`OS_ARTI_SC_END(TerminateTask, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_TerminateTask_Start ; _Return | 包装函数 OsTask_Internal_TerminateTask：BEGIN 在 `OsTask_TerminateTaskBody()` 之前；正常终止不返回，END 只在出错返回时到达。仅在 `OS_ARTI_TRACE_SERVICECALLS==STD_ON` 时存在该包装（else 分支用 `#define OsTask_TerminateTaskBody OsTask_Internal_TerminateTask`，task.c:418-420） |
| `task/Os_task.c:508` ; `622` | `OsTask_Internal_ChainTask` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ChainTask, TaskID)`<br>`OS_ARTI_SC_END(ChainTask, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ChainTask_Start ; _Return |  |
| `task/Os_task.c:640` ; `682` | `OsTask_Internal_Schedule` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(Schedule, 0U)`<br>`OS_ARTI_SC_END(Schedule, Status)` | AR_CP_OS_SERVICECALLS / OsServiceCall_Schedule_Start ; _Return |  |
| `task/Os_task.c:700` ; `758` | `OsTask_Internal_GetTaskState` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetTaskState, TaskID)`<br>`OS_ARTI_SC_END(GetTaskState, (E_OK == Status) ? (uint32)(*State) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetTaskState_Start ; _Return |  |
| `task/Os_task.c:775` ; `807` | `OsTask_Internal_GetTaskID` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(GetTaskID, 0U)`<br>`OS_ARTI_SC_END(GetTaskID, (E_OK == Status) ? (uint32)(*TaskID) : OS_ARTI_SC_INVALID)` | AR_CP_OS_SERVICECALLS / OsServiceCall_GetTaskID_Start ; _Return |  |
| `task/Os_task.c:824` ; `867` | `OsTask_Internal_ActivateTaskAsyn` | 入口(BEGIN)：ServiceStart 之后、关中断区外；出口(END)：最后一次 ResumeISR 之后、关中断区外 | `OS_ARTI_SC_BEGIN(ActivateTaskAsyn, TaskID)`<br>`OS_ARTI_SC_END(ActivateTaskAsyn, 0U)` | AR_CP_OS_SERVICECALLS / OsServiceCall_ActivateTaskAsyn_Start ; _Return | END 参数固定 `0U`（无返回值） |

### 1.15 `task/Os_task_types.h`（仅类型）

| 文件:行号 | 函数 | 插桩位置 | 宏 | 事件（类 / 事件名） | 触发条件 / 备注 |
|---|---|---|---|---|---|
| `task/Os_task_types.h:49`、`:107-109` | — | 无宏调用 | `#include "Os_ArtiCfg.h"`（:49）；`Os_TaskDynamicType` 增加 `uint8 ArtiState`（受 `OS_ARTI_TRACE_TASK` 控制） | — | 见第 3、4 节 |

## 2. 按事件类的反向索引

"由谁发出"一栏指触发的内核场景。事件名按增强模型；标准模型的映射见第 0 节。

### 2.1 任务（`AR_CP_OSARTI_TASK`，实例参数 `TaskId`，上下文 NOSUSP）

| 事件 | 发出点（文件:行号） | 由什么场景走到这里 |
|---|---|---|
| OsTask_Activate | `task/Os_task.c:232`（`OsTask_Internal_ArtiActivate`） | 调用点 `task/Os_task.c:1250`（`OsTask_TaskInit`，自启动任务）、`:1469`（`OsTask_ActivateTask`，仅当任务原为 SUSPENDED；多重激活不发）、`:565`（ChainTask 到自己，Terminate 之后）。`OsTask_ActivateTask` 的调用者：`ActivateTask` 服务（`Os_task.c:359`）、`ChainTask` 到别的任务（:577）、`OsTask_ActivateRestartTask`（:1599）、报警动作 `OsAlarm_DoAlarm`（`alarm/Os_alarm.c:723`）、调度表到期动作 `OsSchT_Internal_EPAction`（`scheduletable/Os_scheduletable.c:1650`），以及它们的跨核入口 |
| OsTask_Start | `task/Os_task.c:309`（`OsTask_Internal_ArtiEnter` default） | `OsTask_DoScheduling`:1146，任务首次被调度，`ArtiState == ACTIVATED`；标准模型下 Resume、Continue 也映射到它 |
| OsTask_Preempt | `task/Os_task.c:278`（`OsTask_Internal_ArtiLeave`） | `OsTask_DoScheduling`:1123，当前任务被另一个任务取代且仍在 RUNNING；ISR2 进入本身不发任务事件；ISR2 退出时若调度到另一个任务，才在此发 Preempt（见第 3 节） |
| OsTask_Resume | `task/Os_task.c:302`（`OsTask_Internal_ArtiEnter`） | `OsTask_DoScheduling`:1146，`ArtiState == PREEMPTED` |
| OsTask_Continue | `task/Os_task.c:305`（`OsTask_Internal_ArtiEnter`） | `OsTask_DoScheduling`:1146，`ArtiState == RELEASED`（先前 WaitEvent，被 SetEvent 释放） |
| OsTask_Wait | `event/Os_event.c:532`（`OsEvent_Internal_WaitEvent`） | 服务 `WaitEvent`，所等事件未置位，任务进入等待 |
| OsTask_Release | `event/Os_event.c:725`（`OsEvent_SetEvent`） | 服务 `SetEvent`（含报警/调度表的 SetEvent 动作，`OsEvent_SetEvent` 调用点 `alarm/Os_alarm.c:740`、`scheduletable/Os_scheduletable.c:1682`、`event/Os_event.c:218`）命中等待中的任务 |
| OsTask_Terminate | `task/Os_task.c:248`（`OsTask_Internal_ArtiTerminate`） | 调用点 `:468`（TerminateTask 正常终止，经 `OsTask_TerminateTaskBody`，包括 `OsTask_ErrorReturn`:1375 的任务返回未调 TerminateTask）、`:564`（ChainTask 到自己）、`:601`（ChainTask 到别的任务，目标 Activate 成功之后）、`:1702`（`OsTask_TaskDeinit`，强制终止，任何状态）|

### 2.2 Cat2 ISR（`AR_CP_OSARTI_CAT2ISR`，实例参数 `Isr2Id`，上下文 NOSUSP）

| 事件 | 发出点 | 场景 |
|---|---|---|
| OsCat2Isr_Activate | `isr/Os_isr.c:1090` | `OsIsr_PreISR`:1144，与 Start 连续发 |
| OsCat2Isr_Start | `isr/Os_isr.c:1091` | 同上 |
| OsCat2Isr_Preempt | `isr/Os_isr.c:1087` | `OsIsr_PreISR`:1144，被打断对象是另一个 ISR2 |
| OsCat2Isr_Resume | `isr/Os_isr.c:1111` | `OsIsr_PostISR`:1244 或 `OsIsr_PostServiceCallISR`:1303 返回时，被打断对象是 ISR2 |
| OsCat2Isr_Stop | `isr/Os_isr.c:1106` | `OsIsr_PostISR`:1244（普通 ISR2 出口）；`OsIsr_PostServiceCallISR`:1303（跨核服务 ISR2，队列清空时） |

服务调用 ISR2（`isCrossCore`）与普通 ISR2 走同一入口，也会被当成 Cat2 ISR 上报；这是否符合预期见第 7 节。

### 2.3 应用（`AR_CP_OS_APPLICATION`，实例参数 `ApplicationId`，上下文 NOSUSP）

| 事件 | 发出点 | 场景 |
|---|---|---|
| OsApplication_Start | `application/Os_application.c:219`（调用点 :1051） | `OsApp_ApplicationInit`，由 `StartOS`（`kernel/Os_kernel.c:1025`）逐应用调用，置 ACCESSIBLE 之后 |
| OsApplication_Restart | `:222`（调用点 :930） | `OsApp_TerminateApplication` 的重启分支（服务 TerminateApplication、保护 hook 的 `PRO_TERMINATEAPPL_RESTART` 处置（`hook/Os_hook.c:407`）） |
| OsApplication_AllowAccess | `:225`（调用点 :464） | 服务 `AllowAccess` 成功 |
| OsApplication_Terminate | `:228`（调用点 :690、:938、:1106） | :690 `OsApp_SetAppTerminateStatus`（`Os_PreInit`:918）；:938 `OsApp_TerminateApplication` 的不重启分支；:1106 `OsApp_ApplicationDeInit`（`OsKernel_ShutdownOSProcessing`:302） |

### 2.4 自旋锁（`AR_CP_OS_SPINLOCK`，实例参数 `SpinlockId`，上下文 NOSUSP）

| 事件 | 发出点 | 场景 |
|---|---|---|
| OsSpinlock_Locked | `spinlock/Os_spinlock.c:337`、`:466` | 服务 `GetSpinlock`（取得锁时）、`TryToGetSpinlock`（成功时） |
| OsSpinlock_Released | `spinlock/Os_spinlock.c:537`、`:854` | 服务 `ReleaseSpinlock`；`OsSpinlock_SpinlockDeInit`（代已终止对象释放）。**未插桩**：`OsSpinlock_GetInternalSpinlock`/`ReleaseInternalSpinlock`（:818-835，内核内部锁），见第 7 节 |

### 2.5 Hook（`AR_CP_OS_HOOK`，上下文 NOSUSP）

| 事件 | 发出点 | 场景 |
|---|---|---|
| OsHook_ErrorHook_Start / OsHook_StartupHook_Start / OsHook_ShutdownHook_Start / OsHook_ProtectionHook_Start（`LastError`/`-`） | `hook/Os_hook.c:229/233/237/241`（宏），调用点 `:299` | `OsHook_Internal_CallHook` 在切换到 hook 上下文之前；入口函数 `OsHook_CallErrorHook`(:444)、`OsHook_CallProtectionHook`(:543)、`OsHook_CallCoreStartupHook`(:576)、`OsHook_CallCoreShutdownHook`(:602) |
| OsHook_ErrorHook_Return / OsHook_StartupHook_Return / OsHook_ShutdownHook_Return | `hook/Os_hook.c:230/234/238`，调用点 `:477` | `OsHook_Hookreturn`（hook 函数返回的统一出口） |
| OsHook_ProtectionHook_Return（参数 `ProtectionReaction`） | `hook/Os_hook.c:242`，调用点 `:558` | `OsHook_CallProtectionHook`，校验后的处置；只有这一处，`OsHook_Hookreturn` 对它跳过 |
| OsHook_ErrorHook_`<App>`_Start/_Return、OsHook_StartupHook_`<App>`_*、OsHook_ShutdownHook_`<App>`_* | `hook/Os_hook.c:208-217`，调用点同上 | 应用级 hook：`OsHook_CallErrorHook`(:446)、`OsHook_CallAppStartupHook`(:589)、`OsHook_CallAppShutdownHook`(:615) |
| OsHook_PreTaskHook_Start/_Return | `hook/Os_hook.c:633 / 637` | `OsHook_CallPreTaskHook`（`DoScheduling` 里任务切入时） |
| OsHook_PostTaskHook_Start/_Return | `hook/Os_hook.c:663 / 667` | `OsHook_CallPostTaskHook`（`DoScheduling` 里任务让出时） |

### 2.6 服务调用（`AR_CP_OS_SERVICECALLS`，上下文 SPRVSR）

70 个服务，每个有 `OsServiceCall_<Api>_Start`，其中 67 个另有 `_Return`；`StartOS`、`ShutdownOS`、`ShutdownAllCores` 没有 Return。服务与所在函数见第 1 节各表，服务清单与 `Os_ArtiEvents.m` 的 `ArtiServices` 一一对应（用脚本比对：集合相同，各 70 项）。按文件的服务数：alarm 5、application 7、counter 3、event 5、isr 10、kernel 8、mpu 11、resource 2、scheduletable 8、services 1、spinlock 3、task 7。

## 3. 影子状态 `ArtiState`

事件由 `ArtiState` 决定，**不是**内核的 `State`。原因（`task/Os_task.c:215-218` 的注释）：进入 ISR2 时 `OsTask_LeaveTaskLevel` 会把被打断的任务置为 READY，而 READY 并不能说明任务"为什么就绪"（刚激活、被抢占、还是被 SetEvent 释放）。

### 3.1 存放位置

| 结构体 | 字段 | 定义处 | 取值常量（`Os_ArtiCfg.h`） | 受控于 |
|---|---|---|---|---|
| `Os_TaskDynamicType` | `uint8 ArtiState` | `task/Os_task_types.h:109` | `OS_ARTI_TASK_SUSPENDED(0)`、`ACTIVATED(1)`、`RUNNING(2)`、`PREEMPTED(3)`、`WAITING(4)`、`RELEASED(5)` | `OS_ARTI_TRACE_TASK == STD_ON` |
| `Os_IsrDynamicType` | `uint8 ArtiState` | `isr/Os_isr_types.h:75` | `OS_ARTI_ISR_INACTIVE(0)`、`RUNNING(1)`、`PREEMPTED(2)` | `OS_ARTI_TRACE_CAT2ISR == STD_ON` |

其它结构体（hook、应用、自旋锁）没有影子状态。

### 3.2 任务 `ArtiState` 的读写

| 位置 | 操作 | 值 | 说明 |
|---|---|---|---|
| `task/Os_task.c:231` | 写 | ACTIVATED | `OsTask_Internal_ArtiActivate`，先写后发 Activate |
| `task/Os_task.c:252` | 写 | ACTIVATED | `OsTask_Internal_ArtiTerminate`，发 Terminate 之后；若 `ActivationCount != 0`（还有挂起的激活，下一个实例马上就绪，其 Activate 在激活时已报） |
| `task/Os_task.c:256` | 写 | SUSPENDED | 同上，`ActivationCount == 0` |
| `task/Os_task.c:277` | 写 | PREEMPTED | `OsTask_Internal_ArtiLeave`，发 Preempt 之前 |
| `task/Os_task.c:312` | 写 | RUNNING | `OsTask_Internal_ArtiEnter` 末尾（发完 Start/Resume/Continue 之后） |
| `task/Os_task.c:1258` | 写 | SUSPENDED | `OsTask_TaskInit` 非自启动分支（自启动分支通过 Activate 间接写 ACTIVATED） |
| `event/Os_event.c:531` | 写 | WAITING | `WaitEvent` 进入等待，发 Wait 之前 |
| `event/Os_event.c:724` | 写 | RELEASED | `SetEvent` 释放等待任务，发 Release 之前 |
| `task/Os_task.c:272` | 读 | — | `ArtiLeave`：`ArtiState == RUNNING` 才报 Preempt |
| `task/Os_task.c:294` | 读 | — | `ArtiEnter`：`ArtiState != RUNNING` 才报 Start/Resume/Continue |
| `task/Os_task.c:299` | 读 | — | `ArtiEnter` 的 switch：PREEMPTED→Resume，RELEASED→Continue，其它→Start |

### 3.3 Cat2 ISR `ArtiState` 的读写

| 位置 | 操作 | 值 | 说明 |
|---|---|---|---|
| `isr/Os_isr.c:1086` | 写 | PREEMPTED | `OsIsr_Internal_ArtiStart`，被打断的 ISR2 |
| `isr/Os_isr.c:1089` | 写 | RUNNING | 同上，新进入的 ISR2 |
| `isr/Os_isr.c:1105` | 写 | INACTIVE | `OsIsr_Internal_ArtiStop`，结束的 ISR2 |
| `isr/Os_isr.c:1110` | 写 | RUNNING | 同上，被恢复的 ISR2 |

ISR 的 `ArtiState` **没有读取点**（grep 全内核只有以上 4 处，均为赋值）；状态仅被写入，Preempt/Resume 的判定靠"被打断对象类型是 ISR"，并不读它。ISR 的 `ArtiState` 没有显式初始化（`OsIsr_IsrInit`（`isr/Os_isr.c:1335`）只清 `SpinlockOccupied` 等），依赖运行数据区零初始化（INACTIVE = 0）——是否确实零初始化，待确认。

### 3.4 与内核 `State` 的区别

- 内核 `State`（`SUSPENDED/READY/RUNNING/WAITING`）服务于调度，在 `OsTask_DoScheduling`（`task/Os_task.c:1137-1141`）里按"当前 RUNNING→READY、下一个→RUNNING"改写，ISR2 进入（`OsTask_LeaveTaskLevel`）时被打断的任务也会被置 READY。`ArtiState` 不参与调度，只在 ARTI 辅助函数、`OsTask_TaskInit` 和 `WaitEvent`/`SetEvent` 的两处写入。
- `ArtiState` 把 READY 拆成 `ACTIVATED`（刚激活）、`PREEMPTED`（被任务抢占）、`RELEASED`（被事件释放）三种，才能区分 Start/Resume/Continue。
- 被 ISR2 打断又回到同一任务时，`ArtiState` 仍为 RUNNING，因此 `ArtiEnter` 不发事件，`ArtiLeave` 也不发（`CurrentTaskID == NextTaskID`）；被打断的任务在 trace 里始终是 Running。

## 4. 额外插入的非宏改动

### 4.1 影子状态字段与头文件

| 位置 | 内容 |
|---|---|
| `task/Os_task_types.h:107-109` | `Os_TaskDynamicType` 增加 `uint8 ArtiState`（`#if OS_ARTI_TRACE_TASK == STD_ON`） |
| `isr/Os_isr_types.h:73-75` | `Os_IsrDynamicType` 增加 `uint8 ArtiState`（`#if OS_ARTI_TRACE_CAT2ISR == STD_ON`） |
| `task/Os_task_types.h:49`、`isr/Os_isr_types.h:46` | `#include "Os_ArtiCfg.h"`（开关与状态常量，不能包含 `Os_Arti.h`） |
| 13 个 `.c` 的 include 区 | `#include "Os_ArtiHooks.h"`：`alarm/Os_alarm.c:50`、`application/Os_application.c:54`、`counter/Os_counter.c:49`、`event/Os_event.c:50`、`hook/Os_hook.c:47`、`isr/Os_isr.c:56`、`kernel/Os_kernel.c:59`、`mpu/Os_mpu.c:51`、`resource/Os_resource.c:51`、`scheduletable/Os_scheduletable.c:51`、`services/Os_services.c:49`、`spinlock/Os_spinlock.c:52`、`task/Os_task.c:58` |

### 4.2 新增 static 辅助函数

| 函数 | 位置 | 作用 | 是否自带屏蔽中断 |
|---|---|---|---|
| `OsApp_Internal_Arti` | `application/Os_application.c:205-232`（宏常量 `OS_ARTI_APP_EV_START/RESTART/ALLOWACCESS/TERMINATE` 在 :201-204，块 :195-233） | 按事件号发应用事件 | 是（:214/:231） |
| `OsHook_Internal_Arti` | `hook/Os_hook.c:187-251`（块 181-252） | 按 hook 类型与对象类型（应用/内核）选宏 | 是（:200/:248） |
| `OsIsr_Internal_ArtiStart` | `isr/Os_isr.c:1072` 起（块 1067-1114） | Preempt、Activate、Start | 否（调用者 `OsIsr_PreISR` 已屏蔽） |
| `OsIsr_Internal_ArtiStop` | `isr/Os_isr.c:1095` 起 | Stop、Resume | 否（调用者已屏蔽） |
| `OsTask_Internal_ArtiActivate` | `task/Os_task.c:220-234`（块 213-316） | Activate | 是（:229/:233） |
| `OsTask_Internal_ArtiTerminate` | `task/Os_task.c:236-259` | Terminate | 是（:245/:258） |
| `OsTask_Internal_ArtiLeave` | `task/Os_task.c:262-281` | Preempt | 条件成立时才屏蔽（:275/:279） |
| `OsTask_Internal_ArtiEnter` | `task/Os_task.c:285-315` | Start/Resume/Continue | 条件成立时才屏蔽（:297/:313） |

### 4.3 本地屏蔽中断（插桩引入的 `OsIsr_SuspendISR`/`ResumeISR` 对）

这些屏蔽只在 ARTI 开关打开时存在，目的是满足 `NOSUSP` 语境（见 `ARTI_hook_tracing.md` 第 3 节）：

| 位置 | 所在函数 | 说明 |
|---|---|---|
| `application/Os_application.c:214/231` | `OsApp_Internal_Arti` | 应用事件无论调用者状态都屏蔽 |
| `event/Os_event.c:722/726` | `OsEvent_SetEvent` | 跨核 SetEvent 由目标核服务 ISR2 执行，不一定持有内核锁 |
| `hook/Os_hook.c:200/248` | `OsHook_Internal_Arti` | 经 `CallHook` 与 `OsHook_Hookreturn` 进入 |
| `hook/Os_hook.c:632/634/636/638`、`:662/664/666/668` | `OsHook_CallPreTaskHook`、`OsHook_CallPostTaskHook` | Start、Return 各一对，中间的 hook 函数体在中断放开状态下运行 |
| `spinlock/Os_spinlock.c:852/856` | `OsSpinlock_SpinlockDeInit` | `OsTask_ErrorReturn` 路径没有内核锁 |
| `task/Os_task.c:229/233`、`245/258`、`275/279`（条件）、`297/313`（条件） | 4 个任务辅助函数 | 跨核服务 ISR 路径等 |

### 4.4 其它结构性改动

- `task/Os_task.c:394-420`（受 `OS_ARTI_TRACE_SERVICECALLS` 控制）：把原来的 `OsTask_Internal_TerminateTask` 函数体改名为 `OsTask_TerminateTaskBody`（定义在 :422），原名变成带 `BEGIN/END` 的包装；`OsTask_ErrorReturn` 的调用同步改成 `OsTask_TerminateTaskBody()`（:1375，基线是 `OsTask_Internal_TerminateTask()`）。原因：`OsTask_ErrorReturn`（任务返回未调 TerminateTask）不是服务调用，不应发 `OsServiceCall_TerminateTask_*`。开关关闭时通过 `#define OsTask_TerminateTaskBody OsTask_Internal_TerminateTask`（:419）保持原貌。
- 对只有一行实现调用的服务（isr 的 10 个服务、`GetCoreID`、`GetActiveApplicationMode`、`ShutdownOS`、`GetCurrentApplicationID`），把原来的那一行调用包进花括号块，并在块内加 `OS_ARTI_SC_DECL`、BEGIN、END（逐个见 1.2、1.6、1.8 的备注）。这些包装块不受 `OS_ARTI_TRACE_*` 的 `#if` 控制，开关关闭时靠 `OS_ARTI_SC_*` 展开为空，结果只剩一个空的花括号块。
- `application/Os_application.c:246` 的 `GetApplicationID`：原来该处是空行，现在在 `OS_ARTI_TRACE_SERVICECALLS` 开关下放了一个块（:242-249），块内先把 `Current_Config_ApplicationID` 存到局部变量 `ArtiApp`（:245）再 BEGIN/END；函数末尾的返回语句不变。

## 5. 非 ARTI 的内核修复（出现在 diff 里，**不是**插桩）

依据 `diff -ru --strip-trailing-cr kernel_base/Os kernel_basefix/Os`，只涉及两个文件。这些改动让内核行为改变，**即使 ARTI 全部关闭也生效**。

### 5.1 `hook/Os_hook.c`：ProtectionHook 处置

| 位置 | 改动 | 说明 |
|---|---|---|
| `hook/Os_hook.c:330`（`OsHook_Internel_VerifyProtectionReaction`） | `ProtectionReaction` → `FatalError`：`((E_OS_PROTECTION_EXCEPTION == FatalError) \|\| (E_OS_PROTECTION_MEMORY == FatalError)) && OsApp_CheckTrustedFunctionIsCalled()` | 基线比较的是 `ProtectionReaction`，现改为比较错误码 `FatalError`（代码注释 [SWS_Os_00860]） |
| `hook/Os_hook.c:551-553`（`OsHook_CallProtectionHook`） | 基线：`OsHook_Internel_VerifyProtectionReaction(ProtectionReaction, FatalError);`（返回值被丢弃）并用 `Os_HookDynPtr->ProtectionReaction`（未校验的值）去 `HandleProtectionReaction`。现在：`ProtectionReaction = Verify...(...)`，写回 `Os_HookDynPtr->ProtectionReaction`，用校验后的值调用 `HandleProtectionReaction` | 代码注释："Act on the verified reaction; keep it in the hook data (read by ARTI and for diagnosis)"。ARTI 的 `OsHook_ProtectionHook_Return` 参数读的是这个字段（:558） |

### 5.2 `isr/Os_isr.c`：`OsIsr_PostISR` 的错误分支

`isr/Os_isr.c:1176-1260`。基线的行为问题与新行为（对照 diff）：

- 基线先 `OsLock_ClearLockList(...)` 再读 `LockList->LockType` 判定错误类型；改后的代码注释写明 `ClearLockList` 会清空列表，所以要先读类型。现在先读类型，记入 `ErrorStatus`（`E_OS_RESOURCE` / `E_OS_SPINLOCK`，:1206/:1210），再清空（:1212）。清空之后 `LockList` 的具体取值（是否为 NULL）待确认，因此基线的读取是否越界本次不下结论。
- 三种错误（资源/自旋锁、中断被挂起 `E_OS_DISABLEDINT`:1219）统一用 `ErrorStatus` 记录，`if (E_OK != ErrorStatus)`（:1226）才调用 `OsHook_SetErrorParameterZero` + `OsHook_CallErrorHook(ErrorStatus)`；hook 返回后 `OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL)`（:1232）再次屏蔽。
- 基线中，`EndOfInterrupt` 与上下文切回只写在最后一个 `else`（无错误）分支里，三个错误分支里没有；现在无论有无错误，都执行"结束 ISR"那个块（:1235 起）。

### 5.3 自旋锁 Released 的位置

"Released 移到硬件释放之前"在 `diff kernel_base kernel_basefix` 中**没有**对应改动（基线没有任何 ARTI 代码），在 `diff kernel_basefix 当前内核` 里是作为 ARTI 插桩出现的：`spinlock/Os_spinlock.c:537`（`OsSpinlock_Hal_Releaselock` 在 :541）和 :854（`Hal_Releaselock` 在 :859）。它是 ARTI 事件顺序的修正（保证 Released 先于其它核的 Locked），不改变内核功能，所以归在插桩里（第 1.13 节）。这一点不是从 diff 看出的，而是从当前源码的位置与注释确认的；较早版本的 Released 位置没有在本次读取的资料中，故不能给出"改前"的具体行。

## 6. 统计与复现

### 6.1 数字

| 项目 | 数量 |
|---|---|
| 被改动的文件 | 15（13 个 `.c` + 2 个 `_types.h`） |
| 含 `OS_ARTI_*` 宏调用的文件 | 13（全部 `.c`）；`Os_task_types.h`、`Os_isr_types.h` 只有字段与 include |
| 宏调用点总数（`OS_ARTI_(TASK\|ISR2\|APPLICATION\|SPINLOCK\|HOOK\|APPHOOK\|SC)_xxx(`，不含 `#define` 与 `OS_ARTI_SC_DECL`） | **203** |
| 其中服务调用 `OS_ARTI_SC_BEGIN` / `OS_ARTI_SC_END` | 84 / 80（合计 164）；`OS_ARTI_SC_DECL` 84 处；另 4 处 BEGIN 无对应 END：`StartOS`、`ShutdownOS`（2 个分支）、`ShutdownAllCores` |
| 任务（`OS_ARTI_TASK_*`） | 8（Activate、Terminate、Preempt、Resume、Continue、Start 在 `Os_task.c`；Wait、Release 在 `Os_event.c`） |
| Cat2 ISR（`OS_ARTI_ISR2_*`） | 5（Preempt、Activate、Start、Stop、Resume） |
| 应用（`OS_ARTI_APPLICATION_*`） | 4 |
| 自旋锁（`OS_ARTI_SPINLOCK_*`） | 4（Locked 2、Released 2） |
| Hook（`OS_ARTI_HOOK_*`） | 12（核级 hook 的 Start/Return 8 处在 `OsHook_Internal_Arti`，PreTask/PostTask 各 Start+Return 4 处） |
| 应用 hook（`OS_ARTI_APPHOOK_*`） | 6 |
| Hook 合计（HOOK + APPHOOK） | 18 |

校验：164 + 8 + 5 + 4 + 4 + 12 + 6 = 203。

"逻辑触发点"（辅助函数/内联块的调用位置）另计：任务 11（Activate 3、Terminate 4、Leave 1、Enter 1、WaitEvent 1、SetEvent 1）、Cat2 ISR 3（PreISR 1、Stop 2）、应用 6、自旋锁 4、Hook 5（`OsHook_Internal_Arti` 3 个调用点 + PreTask、PostTask 两个内联块）。

按函数/事件计的服务调用：70 个服务，Start 70 个事件、Return 67 个事件。

### 6.2 事件类对照

| 事件类 | 宏调用点 | 备注 |
|---|---|---|
| AR_CP_OS_SERVICECALLS | 164 | 70 个服务 |
| AR_CP_OSARTI_TASK / AR_CP_OS_TASK | 8 | 6 个事件在 `Os_task.c`，2 个在 `Os_event.c` |
| AR_CP_OSARTI_CAT2ISR / AR_CP_OS_CAT2ISR | 5 | |
| AR_CP_OS_APPLICATION | 4 | |
| AR_CP_OS_SPINLOCK | 4 | |
| AR_CP_OS_HOOK | 18 | 含应用 hook 6 |

### 6.3 复现命令

在内核 `Os` 目录下执行（Git Bash；`K` 为已插桩内核目录，`S` 为 scratchpad）：

```bash
K="D:/19_AutosarOS/02_THA6204/02_Software/01_Code/01_Trunk/00_CodeProject/tr002_THA6_OS_Project/Os"
S="C:/Users/00048/AppData/Local/Temp/claude/D--bsw-------main-bsw------/69d1e05f-401b-4157-8d4f-41952157af67/scratchpad"

# 1) 文件差异（15 个）与分类
diff -rq --strip-trailing-cr "$S/kernel_base/Os" "$K"            # 插桩 + 修复，15 个文件
diff -rq --strip-trailing-cr "$S/kernel_basefix/Os" "$K"         # 仅插桩，15 个文件
diff -rq --strip-trailing-cr "$S/kernel_base/Os" "$S/kernel_basefix/Os"   # 仅修复：Os_hook.c、Os_isr.c

# 2) 宏调用点总数（203）与按类计数
cd "$K"
grep -rEn 'OS_ARTI_(TASK|ISR2|APPLICATION|SPINLOCK|HOOK|APPHOOK|SC)_[A-Z0-9_]+\(' --include=*.c --include=*.h . | grep -v '#define' | wc -l
grep -rEo 'OS_ARTI_(TASK|ISR2|APPLICATION|SPINLOCK|HOOK|APPHOOK|SC)_[A-Z0-9_]+\(' --include=*.c --include=*.h . \
  | sed -E 's/.*OS_ARTI_([A-Z0-9]+)_.*/\1/' | sort | uniq -c
grep -rEo 'OS_ARTI_SC_(BEGIN|END|DECL)' --include=*.c . | sed 's/.*://' | sort | uniq -c   # 84 / 80 / 84

# 3) 其它插桩点
grep -rn 'Internal_Arti\|ArtiState' --include=*.c --include=*.h .            # 辅助函数调用点与影子状态读写
grep -rn 'Os_ArtiHooks.h\|Os_ArtiCfg.h' --include=*.c --include=*.h .       # include（15 个文件）
grep -rn 'OS_ARTI_TRACE_' --include=*.c --include=*.h .                       # #if 开关
```

行号与"所在函数"表由 `scratchpad/arti_sites.py`（扫描上面正则的匹配行，函数名取其前最近一个"行首标识符行、下一行是 `(`"的定义）生成，输出 `scratchpad/sites.tsv`；位置规律用 `scratchpad/pos_check.py`、`scratchpad/ret_check.py` 核对。这些是本次的临时脚本，不在仓库里。

## 7. 待确认项

1. **ISR `ArtiState` 的零初始化**：`OsIsr_IsrInit`（`isr/Os_isr.c:1335`）不显式初始化 `ArtiState`，依赖 `IsrRunningData` 所在内存零初始化。内存映射段是否清零，需看链接脚本/启动代码，本次未查。
2. **服务调用 ISR2 被当作 Cat2 ISR 上报**：`OsIsr_PreISR` 的入口对跨核服务 ISR2（`isCrossCore`）没有区分，会发 `OsCat2Isr_*`。这是预期还是需要过滤，待确认（本次未在配置里确认该 ISR 是否会出现在 `Isr2Id` 的映射表中）。
3. **内核内部自旋锁没有 Locked/Released**：`OsSpinlock_GetInternalSpinlock`/`ReleaseInternalSpinlock`（`spinlock/Os_spinlock.c:818-835`）直接 `Hal_Getlock/Releaselock`，未插桩。它们应是 OS 内部锁、不属于 `OsSpinlock` 配置对象，但本次没有从配置侧确认。
4. **应用事件的 `Terminate` 条件不一致**：:690、:1106 在原状态已是 TERMINATED 时跳过，:938 不判断直接发。:938 所在分支前面是否可能已是 TERMINATED，待确认（`OsApp_TerminateApplication` 前面的状态检查本次没有通读）。
5. **`OsTask_TaskDeinit` 的强制终止**：`task/Os_task.c:1702` 对任何状态的任务都发 `Terminate`（包括已经是 SUSPENDED 的），注释称这是设计 D10 的约定；是否会对已 SUSPENDED 的任务产生多余的 Terminate，待确认。
6. **`kernel_arti.diff` 未使用**：scratchpad 里原有的 `kernel_arti.diff` 可能是旧版，本文全部基于重新生成的 diff。

