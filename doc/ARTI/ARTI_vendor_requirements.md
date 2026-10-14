# ARTI trace 实现需求（致 trace 工具厂商）

自研 OS（THA6，多核）已在内核中插入 ARTI 事件，并生成描述文件。需要贵方提供 hook 的实现。本文只写需要贵方交付的内容和我们这一侧的约定。

## 1. 需要交付的文件

依据：AUTOSAR CP R24-11 SWS ARTI §7.2、§8.4、§8.7.1；OS 的类与事件依据 SWS OS R21-11 §7.17。

| 文件 | 内容 |
| :--- | :--- |
| `Arti.h` | 实现 `ARTI_TRACE`（以及 `ARTI_TRACE_N`），展开为模块相关的宏；声明 `Arti_Init`、`Arti_GetVersionInfo` |
| `Os_Arti.h` | 先包含 `Arti.h`，再定义本 OS 用到的所有 `ARTI_TRACE_<class>_<event>(instanceParameter, eventParameter)` 宏的实现 |
| `Arti.c` | `Arti_Init()`（SWS_Arti_91004）、`Arti_GetVersionInfo()`（SWS_Arti_91005）和 trace 所需的其它代码 |

规范要求：

- `ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter)`（SWS_Arti_00018）。前四个 token 参数中的 `_contextName`、`_className`、`_instanceName`、`_eventName` 是字面 token，不是变量；`instanceParameter`、`eventParameter` 是 uint32。
- 未启用的事件映射为空宏；宏内不要调用 BSW API，如需调用要注意嵌套和递归（SWS_Arti_00018 的说明）。
- `Arti_Init` 初始化失败报 `ARTI_E_INIT_FAILED`；`Arti_GetVersionInfo` 传空指针报 `ARTI_E_PARAM_POINTER`。
- 如何把事件编码进 trace 缓冲区由贵方工具决定，规范不规定。

## 2. 输入：ARTI 描述文件

我们的配置器生成 `Os_Arti.arxml`（`/AUTOSAR/EcucDefs/Arti`）。其中每个 `ArtiHook` 容器描述一个事件：上下文、类、实例、事件名，以及 `instanceParameter`、`eventParameter` 各自引用的类型映射表。请据此生成 `Os_Arti.h`。每个事件都有描述，没有描述的事件内核不会发出。

## 3. 内核侧的调用约定

- 内核只调用 `ARTI_TRACE(...)`（单事件参数形式），不使用 `ARTI_TRACE_N`。
- `_instanceName`：`OsOS`（OS 容器的短名）。
- `instanceParameter`：OS 核索引，即 `Os_Inf_GetCoreId()`，描述里由 `TM_ArtiCoreIndex` 映射为 `Core<n>`。
- `_contextName`：服务调用事件为 `SPRVSR`，其余为 `NOSUSP`。`NOSUSP` 事件调用时，中断已屏蔽到 `OS_ISR_TP_DISABLE_LEVEL`；优先级更高的 Cat1 ISR 仍可能打断 hook，所以 hook 实现必须可重入。
- 事件类（均可由配置开关）：

| 类 | 说明 | `eventParameter` |
| :--- | :--- | :--- |
| `AR_CP_OSARTI_TASK` / `AR_CP_OS_TASK` | 任务状态（增强 / 标准模型二选一） | 任务 ID |
| `AR_CP_OSARTI_CAT2ISR` / `AR_CP_OS_CAT2ISR` | Cat2 ISR 状态（增强 / 标准模型二选一） | ISR ID |
| `AR_CP_OS_APPLICATION` | OS-Application | 应用 ID |
| `AR_CP_OS_SPINLOCK` | 自旋锁 Locked、Released | 自旋锁 ID |
| `AR_CP_OS_HOOK` | 已配置的各 Hook 的 Start、Return | 错误码，或 ProtectionHook 的处置结果 |
| `AR_CP_OS_SERVICECALLS` | 每个 OS 服务的 Start、Return（默认关） | 该服务的对象 ID（任务、自旋锁、资源等，因服务而异）；Return 为返回的错误码 |

- 事件参数的取值范围均在 0..65535 内（ECUC_Arti_00024）。
- 跨核调用采用核间中断加 RPC，`ActivateTask`、`SetEvent`、`TerminateApplication` 的事件在目标核上发出。
- 任务、Cat2 ISR 的事件由内核里的"影子状态"决定，与内核自己的任务状态无关。

## 4. 请贵方确认的问题

1. `Arti_Init` 由谁、在什么时候调用？我们的内核目前不调用它，规范也没有规定调用方。请说明贵方的集成方式（例如由启动代码在 `StartOS` 之前调用）。
2. `NOSUSP` 上下文中 hook 的实现是否满足：不阻塞、不调用 OS 服务、可重入？
3. 多核时，事件的时间戳和核之间的先后顺序由工具如何处理？
4. 以下是我们的默认行为，请确认工具能接受：
   - 任务被多次激活时，不发 `Activate`。
   - `WaitEvent` 时所等待的事件已置位，不发 `Wait`。
   - 强制终止（保护处置、`TerminateApplication`）一个处于 Preempted、Waiting、Activated 或 Released 状态的任务时，也发 `Terminate`。
   - Cat2 ISR 的 `Activate` 与 `Start` 同时发出，内核取不到中断挂起的时刻。
   - `ChainTask` 时，目标任务的 `Activate` 可能先于调用者的 `Terminate`。
   - `TerminateTask`、`StartOS`、`ShutdownOS`、`ShutdownAllCores` 不会返回，所以没有对应的 Return 事件。
5. 工具对 `ARTI_TRACE_N`、`Arti_GetVersionInfo` 的支持范围。

## 5. 完整的实现示例

三个文件的完整内容在 `doc/ARTI/vendor_example/`（`Arti.h`、`Os_Arti.h`、`Arti.c`），文中标 `VENDOR` 的地方就是需要贵方修改的地方。示例能工作：我们用它们代替 Mock，在不定义 `OS_ARTI_USE_MOCK` 的情况下编译了内核（默认配置、两种状态模型下全开、只开 Hook、默认去掉任务事件，共 5 个配置，都能编译，没有新增警告）。

### 5.1 需要修改的地方

| 文件 | 位置 | 示例的做法 | 贵方需要做什么 |
| :--- | :--- | :--- | :--- |
| `Arti.h` | `ARTI_VENDOR_ID`、`ARTI_MODULE_ID`、版本号 | 占位值 `0xFFFF`、1.0.0 | 换成真实的厂商 ID、模块 ID 和版本 |
| `Arti.h` | `ARTI_TRACE` 的展开 | 只拼类名和事件名 | 如果工具要区分上下文（`NOSUSP`/`SPRVSR`）或多个 OS 实例，把它们也拼进宏名，并同步修改 `Os_Arti.h` |
| `Os_Arti.h` | `ARTI_OS_CORES` | 2 | 改成工程的核数；事件的核索引必须小于它 |
| `Os_Arti.h` | `arti_os_trace`、`ARTI_OS_EMIT` | 每核一个 32 位字，值为 `(事件ID<<16) \| (参数&0xFFFF)` | 换成工具需要的记录方式：写工具监视的变量、写软件 trace 缓冲区，或其它。必须可重入，不能调用 OS 服务 |
| `Os_Arti.h` | 每个事件的宏和事件 ID | 按我们的事件表生成，ID 从 1 顺序编号 | 事件 ID 换成工具的编号；不需要记录的事件可定义为 `((void)0)`；这个文件应由贵方工具根据 `Os_Arti.arxml` 生成 |
| `Arti.c` | `arti_os_trace` 的定义 | 放在默认的数据段 | 放到工具要求的内存段，保证调试器或 trace 硬件能访问 |
| `Arti.c` | `Arti_Init` | 清零 | 初始化工具自己的资源；失败时报 `ARTI_E_INIT_FAILED`；说明在哪里调用（内核不调用它） |
| `Arti.c` | `Arti_GetVersionInfo` | 空指针直接返回 | 空指针时报 `ARTI_E_PARAM_POINTER`（例如经 DET） |

### 5.2 `Arti.h`

```c
/**********************************************************************************************************
 * Arti.h - EXAMPLE of the ARTI trace macro (SWS ARTI 7.2, SWS_Arti_00018) and of the Arti API.
 * To be replaced by the file of the trace tool; places a vendor has to adapt are marked "VENDOR".
 **********************************************************************************************************/
#ifndef ARTI_H_
#define ARTI_H_

#include "Std_Types.h"                  /* uint32, Std_VersionInfoType */

/* VENDOR: identification of the module (SWS_Arti_91005); use the real vendor and module IDs and version */
#define ARTI_VENDOR_ID          (0xFFFFU)
#define ARTI_MODULE_ID          (0xFFFFU)
#define ARTI_SW_MAJOR_VERSION   (1U)
#define ARTI_SW_MINOR_VERSION   (0U)
#define ARTI_SW_PATCH_VERSION   (0U)

/* Arti.c */
extern void Arti_Init(void);                                            /* SWS_Arti_91004 */
extern void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);   /* SWS_Arti_91005 */

/* SWS_Arti_00018.  _contextName, _className, _instanceName and _eventName are literal tokens, they must not be
 * macro-expanded before they are pasted.  The kernel calls
 *     ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, <core>, OsTask_Activate, <task id>)
 * which expands to ARTI_TRACE_AR_CP_OSARTI_TASK_OsTask_Activate((<core>), (<task id>)), defined in Os_Arti.h.
 * This example does not need the context and the instance name.
 * VENDOR: if the tool needs them (e.g. to tell several OS instances apart, or to tell service calls from
 * the other contexts), paste them into the name as well: ARTI_TRACE_##_contextName##_##_className##... and
 * define Os_Arti.h accordingly. */
#define ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter) \
    ARTI_TRACE_##_className##_##_eventName((instanceParameter), (eventParameter))

#endif /* ARTI_H_ */
```

### 5.3 `Os_Arti.h`

完整文件有 164 个宏，下面是文件头和结尾部分，其余宏的写法相同，全部在 `vendor_example/Os_Arti.h` 里。该文件由 `tools/arti/gen_vendor_example.py` 根据 t1 工程全部事件类、两种状态模型的事件表生成；贵方的工程配置不同时（例如有自旋锁、使用了 PreTaskHook、应用级 Hook），事件集合不同，请用贵方工具根据 `Os_Arti.arxml` 生成，或者把配置给我们，我们重新生成。

```c
/**********************************************************************************************************
 * Os_Arti.h - EXAMPLE of the OS specific ARTI hook macros (SWS ARTI 7.2).
 *
 * Generated by tools/arti/gen_vendor_example.py from the Os_Arti_Mock.h of the t1 configuration with every trace
 * class on, for both state models (AR_CP_OSARTI_TASK, AR_CP_OSARTI_CAT2ISR, AR_CP_OS_TASK, AR_CP_OS_CAT2ISR).  It is meant to be replaced by the file the trace tool
 * generates from Os_Arti.arxml; places a vendor has to adapt are marked "VENDOR".
 *
 * The kernel includes this file through Os_ArtiHooks.h (when OS_ARTI_USE_MOCK is not defined) and calls
 *     ARTI_TRACE(<context>, <class>, OsOS, <core>, <event>, <parameter>)
 * Arti.h turns that into ARTI_TRACE_<class>_<event>(<core>, <parameter>), defined below.
 *
 * Parameters:  core       OS core index = Os_Inf_GetCoreId(), 0 .. ARTI_OS_CORES - 1
 *              parameter  AR_CP_OS(ARTI)_TASK / _CAT2ISR : task / ISR2 ID
 *                         AR_CP_OS_APPLICATION           : application ID
 *                         AR_CP_OS_SPINLOCK              : spinlock ID
 *                         AR_CP_OS_HOOK                  : error code; ProtectionHook: fatal error / reaction
 *                         AR_CP_OS_SERVICECALLS          : object ID of the service, Return: error code
 * Context:     NOSUSP events are emitted with interrupts masked up to OS_ISR_TP_DISABLE_LEVEL, SPRVSR events
 *              (service calls) are not; a higher priority Cat1 ISR can interrupt either, so the macros must be
 *              reentrant and must not call OS services.
 **********************************************************************************************************/
#ifndef OS_ARTI_H_
#define OS_ARTI_H_

#include "Arti.h"                       /* SWS ARTI 7.2: first, before any module specific macro */

/* VENDOR: number of OS cores of the project; the instance parameter of every event is below this */
#define ARTI_OS_CORES   (2U)

/* VENDOR: where the event goes.  Here: one 32 bit word per core that the trace tool observes (data trace of
 * the debug interface, or a software trace buffer that is filled by a write).  The word is
 *     (event ID << 16) | (event parameter & 0xFFFF)
 * The event IDs below are numbered by this example; use the numbering of the trace tool. */
extern volatile uint32 arti_os_trace[ARTI_OS_CORES];

#define ARTI_OS_EMIT(core, eventId, param) \
    (arti_os_trace[(core)] = ((uint32)(eventId) << 16) | ((uint32)(param) & 0xFFFFU))

/* VENDOR: one macro per ArtiHook of Os_Arti.arxml.  An event that the trace tool does not record can be
 * defined as ((void)0).  An event that is missing here makes the kernel fail to compile.  The set of events
 * depends on the configuration (state model, trace classes, configured hooks and applications). */

...
#define ARTI_TRACE_AR_CP_OSARTI_TASK_OsTask_Activate(core, param)                        ARTI_OS_EMIT((core), 5U, (param))   /* NOSUSP */
#define ARTI_TRACE_AR_CP_OSARTI_TASK_OsTask_Start(core, param)                           ARTI_OS_EMIT((core), 6U, (param))   /* NOSUSP */
#define ARTI_TRACE_AR_CP_OS_CAT2ISR_OsCat2Isr_Start(core, param)                         ARTI_OS_EMIT((core), 14U, (param))   /* NOSUSP */
#define ARTI_TRACE_AR_CP_OS_CAT2ISR_OsCat2Isr_Stop(core, param)                          ARTI_OS_EMIT((core), 17U, (param))   /* NOSUSP */
...

#endif /* OS_ARTI_H_ */
```

### 5.4 `Arti.c`

```c
/**********************************************************************************************************
 * Arti.c - EXAMPLE of the Arti API and of the storage of the trace variables.
 * To be replaced by the file of the trace tool; places a vendor has to adapt are marked "VENDOR".
 **********************************************************************************************************/
#include "Arti.h"
#include "Os_Arti.h"

/* VENDOR: the storage the trace tool observes.  Place it in the memory section the tool requires (for example
 * with the project's MemMap), and make sure the debugger or the trace hardware can reach it.
 * One 32 bit word per core: an aligned 32 bit write is atomic, so the macros are reentrant. */
volatile uint32 arti_os_trace[ARTI_OS_CORES];

/* SWS_Arti_91004.  The kernel does not call it: VENDOR / integrator, call it once before the OS starts
 * (for example from the start-up code before StartOS), on every core that is traced. */
void Arti_Init(void)
{
    uint32 core;

    for (core = 0U; core < ARTI_OS_CORES; core++)
    {
        arti_os_trace[core] = 0U;
    }
    /* VENDOR: initialise the tool's own resources here; on failure raise ARTI_E_INIT_FAILED (SWS_Arti_00009) */
}

/* SWS_Arti_91005 */
void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
    if (VersionInfoPtr == ((void *)0))
    {
        /* VENDOR: raise ARTI_E_PARAM_POINTER (SWS_Arti_00010), for example through the DET */
        return;
    }
    VersionInfoPtr->vendorID = ARTI_VENDOR_ID;
    VersionInfoPtr->moduleID = ARTI_MODULE_ID;
    VersionInfoPtr->sw_major_version = ARTI_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ARTI_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ARTI_SW_PATCH_VERSION;
}
```

## 6. 与我们提供的 Mock 的对应关系

| 贵方交付 | 对应的 Mock 文件 | 说明 |
| :--- | :--- | :--- |
| `Os_Arti.h` | `Os_Arti_Mock.h` | 都是每个事件一个宏。Mock 的宏名带上下文和实例名（`OS_ARTI_MOCK_<ctx>_<class>_OsOS_<event>`，用来做严格检查），贵方的只需 `ARTI_TRACE_<class>_<event>`；Mock 把事件写进环形缓冲区，贵方写进 trace 工具观察的位置 |
| `Arti.h` 里的 `ARTI_TRACE` | `Os_Arti_Mock.h` 里的 `ARTI_TRACE` | Mock 没有单独的 `Arti.h`，通用宏也定义在同一个头里；贵方按规范放在 `Arti.h`，由 `Os_Arti.h` 包含 |
| `Arti.c` | `Os_Arti_Mock.c` | Mock 的 .c 只定义缓冲区变量。**Mock 没有 `Arti_Init` 和 `Arti_GetVersionInfo`**，这两个函数没有对应的 Mock，由贵方实现 |

内核只包含 `Os_ArtiHooks.h`，它在没有定义 `OS_ARTI_USE_MOCK` 时包含 `Os_Arti.h`，所以换成贵方文件时内核代码不用改。

## 7. 我们提供的参考

- `Os_Arti.arxml` 和事件清单（由配置器按需生成）。
- 一个严格的 Mock（`Os_Arti_Mock.h/.c`），只用于验证：事件名、类名、参数顺序与描述不一致时直接编译失败；事件记录在每核一个的内存环形缓冲区里（`Os_ArtiMockLog`），不经过任何 trace 工具。可作为贵方 `Os_Arti.h` 的"宏清单"参照。
