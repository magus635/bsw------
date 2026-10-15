# ARTI trace 实现基准（给 trace 工具厂商，以及集成人员）

自研 OS（THA6，多核）已在内核中插入 ARTI 事件，并生成描述文件 `Os_Arti.arxml`。ARTI 的 hook 实现由三个文件组成。我们提供一套**完整、可直接编译运行的基准**，任何 trace 工具厂商都以它为起点修改，集成时不必再从头写。

依据：AUTOSAR CP R24-11 SWS ARTI §7.2、§8.4、§8.7.1；OS 的类与事件依据 SWS OS R21-11 §7.17。

## 1. 三个基准文件

位置：`doc/ARTI/vendor_example/`。文件里标 `VENDOR` 的地方是厂商可以修改的地方，其余不需要改。

| 文件 | 内容 |
| :--- | :--- |
| `Arti.h` | `ARTI_TRACE` 宏（SWS_Arti_00018）、各事件类的开关、API 声明、版本信息、记录用的 `ARTI_EMIT` 钩子、traced word 的编码宏 |
| `Os_Arti.h` | 先包含 `Arti.h`；事件编号（任务、Cat2 ISR、Cat1 ISR、自旋锁、应用、OS 的 Hook、全部服务调用）；每个事件类的宏实现 |
| `Arti.c` | 两个 trace 变量的定义、`Arti_Init()`（SWS_Arti_91004）、`Arti_GetVersionInfo()`（SWS_Arti_91005） |

基准的做法：一个 ARTI 事件就是对一个全局 32 位变量写一次值，由 trace 工具捕获（调试接口的数据 trace，或任何由这次写触发的软件缓冲区）。

- 任务、ISR、自旋锁、应用、Hook 的事件写 `arti_os_trace`：`[0:7]` 核索引、`[8:14]` 事件编号、`[15]` 有效位（恒为 1）、`[16:31]` 对象 ID（Hook 为事件参数）。
- 服务调用事件写 `arti_sc_trace`：`[0:7]` 核索引、`[8:14]` 服务编号、`[15]` 返回标志；服务的参数不记录。
- 事件编号和上面的编码，与 Lauterbach 的 ARTI 实现相同（见第 5 节），所以 TRACE32 的解码适用。

## 2. 厂商需要修改的地方

| 文件 | 位置 | 基准的做法 | 厂商需要做什么 |
| :--- | :--- | :--- | :--- |
| `Arti.h` | `ARTI_VENDOR_ID`、`ARTI_MODULE_ID`、版本号 | 占位值 `0xFFFF`、1.0.0 | 换成真实的厂商 ID、模块 ID 和版本 |
| `Arti.h` | `ARTI_ENABLE_OS_*` | 全部打开 | 可关闭某类事件（该类的宏变空）；内核自己的开关决定发哪些事件，这里不会增加事件 |
| `Arti.h` | `ARTI_DEV_ERROR_DETECT` | `STD_OFF` | 需要上报 Det 时设为 `STD_ON`，并提供 `Det.h` |
| `Arti.h` | `ARTI_EMIT` | 空 | 软件 trace（缓冲区、传输到主机）在这里写代码；数据 trace 不需要 |
| `Arti.h` | `ARTI_TRACE` 的展开 | 只拼类名 | 工具需要区分上下文或多个 OS 实例时，把它们也拼进宏名，并同步修改 `Os_Arti.h` |
| `Os_Arti.h` | 事件编号 | 与 Lauterbach 相同 | 工具用别的编号时修改；必须与工具一致 |
| `Os_Arti.h` | 各类宏的函数体 | 写 `arti_os_trace` 加调用 `ARTI_EMIT` | 换成别的记录方式。必须可重入，不能调用 OS 服务 |
| `Arti.c` | 变量的存放 | 默认数据段 | 放到工具要求的内存段，保证调试器或 trace 硬件能访问 |
| `Arti.c` | `Arti_Init` | 清零 | 初始化工具自己的资源；失败时报 `ARTI_E_INIT_FAILED`；内核不调用它，请说明在哪里调用 |
| `Arti.c` | `Arti_GetVersionInfo` | 空指针直接返回 | 空指针时报 `ARTI_E_PARAM_POINTER` |

一个容易踩的坑：宏如果丢掉某个参数，必须仍然对它求值（`(void)(参数)`），因为内核传入的是只用于 trace 的局部变量，直接丢掉会让编译器报"未使用"警告。基准已经这样写。

## 3. 内核侧的调用约定

- 内核只调用 `ARTI_TRACE(...)`（单事件参数形式），不使用 `ARTI_TRACE_N`。
- `_instanceName`：`OsOS`（OS 容器的短名）。
- `instanceParameter`：OS 核索引，即 `Os_Inf_GetCoreId()`，描述里由 `TM_ArtiCoreIndex` 映射为 `Core<n>`。
- `_contextName`：服务调用事件为 `SPRVSR`，其余为 `NOSUSP`。`NOSUSP` 事件调用时，中断已屏蔽到 `OS_ISR_TP_DISABLE_LEVEL`；优先级更高的 Cat1 ISR 仍可能打断 hook，所以 hook 实现必须可重入。
- 事件类：

| 类 | 说明 | `eventParameter` |
| :--- | :--- | :--- |
| `AR_CP_OSARTI_TASK` / `AR_CP_OS_TASK` | 任务状态（增强 / 标准模型二选一） | 任务 ID |
| `AR_CP_OSARTI_CAT2ISR` / `AR_CP_OS_CAT2ISR` | Cat2 ISR 状态（增强 / 标准模型二选一） | ISR ID |
| `AR_CP_OS_APPLICATION` | OS-Application | 应用 ID |
| `AR_CP_OS_SPINLOCK` | 自旋锁 Locked、Released | 自旋锁 ID |
| `AR_CP_OS_HOOK` | 已配置的各 Hook 的 Start、Return | 错误码，或 ProtectionHook 的处置结果 |
| `AR_CP_OS_SERVICECALLS` | 每个 OS 服务的 Start、Return（默认关） | 服务的对象 ID，基准不记录 |

- 应用级 Hook（`OsHook_<Hook>_<应用名>_Start/_Return`）与配置有关，事件编号由生成的 `Os_ArtiHooks.h` 从 64 开始依次分配，上限 128；超过时生成会报 `#error`。
- 事件参数的取值范围均在 0..65535 内（ECUC_Arti_00024）。
- 跨核调用采用核间中断加 RPC，`ActivateTask`、`SetEvent`、`TerminateApplication` 的事件在目标核上发出。
- 任务、Cat2 ISR 的事件由内核里的"影子状态"决定，与内核自己的任务状态无关。

## 4. 请厂商确认的问题

1. `Arti_Init` 由谁、在什么时候调用？我们的内核目前不调用它，规范也没有规定调用方。请说明集成方式（例如由启动代码在 `StartOS` 之前调用）。
2. `NOSUSP` 上下文中 hook 的实现是否满足：不阻塞、不调用 OS 服务、可重入？
3. 多核时，事件的时间戳和核之间的先后顺序由工具如何处理？
4. 以下是我们的默认行为，请确认工具能接受：
   - 任务被多次激活时，不发 `Activate`。
   - `WaitEvent` 时所等待的事件已置位，不发 `Wait`。
   - 强制终止（保护处置、`TerminateApplication`）一个处于 Preempted、Waiting、Activated 或 Released 状态的任务时，也发 `Terminate`。
   - Cat2 ISR 的 `Activate` 与 `Start` 同时发出，内核取不到中断挂起的时刻。
   - `ChainTask` 时，目标任务的 `Activate` 可能先于调用者的 `Terminate`。
   - `TerminateTask`、`StartOS`、`ShutdownOS`、`ShutdownAllCores` 不会返回，所以没有对应的 Return 事件。
5. 任务 ID 和 ISR ID 怎样映射到对象：用 `Os_Arti.arxml`，还是用 ORTI 里的序号？

## 5. 与 Lauterbach TRACE32 的关系

- **Lauterbach 提供自己的实现**：TRACE32 安装目录 `~~/demo/kernel/arti/hooks_cp`，用法是复制 `common` 目录、把 `arti.c` 加进编译、在 `arti.h` 里选 trace 方法。版权声明为"仅供 TRACE32 使用"，我们的基准是独立编写的，没有拷贝它的代码，只采用了与它相同的事件编号和 traced word 的编码，以便 TRACE32 解码。
- **已验证**：把同样的 `ARTI_TRACE` 调用（44 个 OS 事件，以及 Lauterbach 已定义的 14 个服务调用事件）分别用 Lauterbach 的实现和我们的基准编译，在仿真器里运行，写入 `arti_os_trace`、`arti_sc_trace` 的值逐个相同。
- **没有验证**：没有在 TRACE32 上跑过；任务和 ISR 的 ID 在 TRACE32 里是否按 `Os_Arti.arxml` 解码，还是要按 ORTI 的序号，需要实测（Lauterbach 的应用笔记写的是后者）；目标芯片是否支持数据 trace，或者要改用 LOGGER 或 FDX。
- **两种用法**：
  1. **直接用我们的基准**。TRACE32 的 `arti_data_trace.cmm` 只依赖变量名 `arti_os_trace`、`arti_sc_trace`，可以直接使用。
  2. **用 Lauterbach 的包**。它的 `arti.h` 需要做这些事：打开自旋锁、应用、Hook、服务调用这几个类（默认被注释掉，对应的事件会静默变成空宏）；关闭 RTE 开关；关闭 Det 或提供 `Det.h`；它没有定义我们的大部分服务调用事件（只有 14 个），也没有应用级 Hook 事件，打开这些类时会编译失败，需要另写 `Os_Arti.h` 补齐。`Os_Arti.h` 只需包含 `arti.h` 再补缺的事件名。

## 6. 与 Mock 的对应关系

| 厂商文件 | 对应的 Mock 文件 | 说明 |
| :--- | :--- | :--- |
| `Os_Arti.h` | `Os_Arti_Mock.h` | 都是每个事件一个宏。Mock 的宏名带上下文和实例名（`OS_ARTI_MOCK_<ctx>_<class>_OsOS_<event>`，用来做严格检查），基准的宏名只含类，事件是枚举值；Mock 把事件写进内存环形缓冲区，基准写进 trace 变量 |
| `Arti.h` 里的 `ARTI_TRACE` | `Os_Arti_Mock.h` 里的 `ARTI_TRACE` | Mock 没有单独的 `Arti.h`，通用宏和事件宏在同一个头里 |
| `Arti.c` | `Os_Arti_Mock.c` | Mock 的 .c 只定义缓冲区，没有 `Arti_Init` 和 `Arti_GetVersionInfo`；这两个函数在基准的 `Arti.c` 里 |

内核只包含 `Os_ArtiHooks.h`，它在没有定义 `OS_ARTI_USE_MOCK` 时包含 `Os_Arti.h`，所以换成基准或厂商文件时内核代码不用改。

## 7. 验证基准的方法

- `tools/arti/build_kernel_matrix.py --vendor-dir doc/ARTI/vendor_example ...`：用基准代替 Mock，对 24 个配置（含应用级 Hook）逐个生成并编译全部内核源码，检查没有新增警告。厂商的文件也可以用同样的方法检查。
- `tests/generator/test_arti_baseline_files.py`：检查内核可能发出的每个事件在基准里都有编号、编号不冲突、应用级 Hook 的编号从 64 开始，以及内核包装宏能与基准一起编译。
