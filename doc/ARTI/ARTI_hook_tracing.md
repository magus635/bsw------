# ARTI 运行时 trace：集成与验证说明

对应 openspec 变更 `add-arti-hook-tracing`。本文写给集成本 OS 的工程师，以及在目标板上做验证的人。设计细节见该变更的 `design.md`，规范依据是 SWS OS R21-11 §7.17（`doc/ARTI/AUTOSAR_SWS_OS.pdf`）。

## 1. 交付物

| 文件 | 来源 | 作用 |
| :--- | :--- | :--- |
| `Os_Arti.arxml` | Os 模板生成 | 停机描述，加上每个 trace 事件的 `ArtiHook` 描述 |
| `kernel/Os_ArtiCfg.h` | Os 模板生成 | 开关（`OS_ARTI_ON`、`OS_ARTI_ENHANCED`、`OS_ARTI_TRACE_<CLASS>`）和影子状态取值。内核类型头文件会包含它 |
| `kernel/Os_ArtiHooks.h` | Os 模板生成 | 内核调用的包装宏，只在内核源码里使用 |
| `kernel/Os_Arti_Mock.h`、`.c` | Os 模板生成 | 严格 Mock，只用于验证，不是产品代码 |
| `Os_Arti.h`、`Arti.h` | **trace 工具提供** | hook 的真实实现（SWS ARTI §7.2） |
| 内核源码 | `tr002_THA6_OS_Project/Os` | 插桩点，见 design D5 |

模板放在插件的 `generate_PB/` 下：`Os_ArtiEvents.m` 与 `Os_AppCommon.m` 同级，`Os/Os_Arti.arxml` 在 `Os/` 下，其余四个文件在 `Os/kernel/` 下；工程模板目录（如 t1 的 `templates/Os/`）布局相同。本仓库不保存模板：以插件为准，修改后同步到工程。仓库测试默认读插件目录，可用环境变量 `OS_TEMPLATE_DIR` 指向其它同布局目录，找不到时相关测试跳过（`tests/generator/os_templates.py`）。

## 2. 配置参数（`OsOS` 容器，本 OS 私有）

在 GUI 的 Os 模块里选中 `OsOS` 容器，在参数表中设置。七个 `OsVendorArti*` 参数只有在 `OsUseArti` 为 true 时才可编辑，也只在此时生效。它们都是 PreCompile 参数：改动后需要重新生成 Os 代码并重新编译内核。

### 2.1 总开关

| 参数 | 默认 | 作用 |
| :--- | :--- | :--- |
| `OsUseArti` | false | 标准参数，ARTI 总开关。关闭时不生成 `Os_Arti.arxml`，内核不含任何 ARTI 代码（目标文件与未插桩的内核逐字节相同）。打开时生成静态描述（对象、栈、上下文等，供停机调试读取）；是否再产生运行时 trace 事件由下面六个开关决定 |

### 2.2 状态模型

| 参数 | 取值 | 默认 | 作用 |
| :--- | :--- | :--- | :--- |
| `OsVendorArtiStateModel` | `ENHANCED` / `STANDARD` | ENHANCED | 决定任务和 Cat2 ISR 的状态机以及事件集合 |

- `ENHANCED`：使用 `AR_CP_OSARTI_TASK` 和 `AR_CP_OSARTI_CAT2ISR`（SWS OS R21-11 §7.17，推荐）。任务事件有 Activate、Start、Preempt、Resume、Wait、Release、Continue、Terminate；Cat2 ISR 事件有 Activate、Start、Preempt、Resume、Stop。能还原完整的调度时间线。
- `STANDARD`：使用 `AR_CP_OS_TASK` 和 `AR_CP_OS_CAT2ISR`。事件集合小（任务没有 Resume 和 Continue，Cat2 ISR 只有 Start 和 Stop），适用于 trace 工具只支持基础类的情况。
- 该选项同时写入 `Os_Arti.arxml` 的 `ArtiStatesTaskEnhanced`，让调试器知道任务状态用哪一套取值；内核里的影子状态取值（`Os_ArtiCfg.h`）也随它切换。
- 只影响任务和 Cat2 ISR。应用、自旋锁、Hook、服务调用的事件与此项无关。

### 2.3 事件类开关

| 参数 | 默认 | 控制的事件类 | 产生的事件 | 开销 |
| :--- | :--- | :--- | :--- | :--- |
| `OsVendorArtiTraceTask` | true | 任务（`AR_CP_OSARTI_TASK` 或 `AR_CP_OS_TASK`） | 激活、启动、抢占、恢复、等待、释放、继续、终止（STANDARD 模型没有恢复和继续） | 中：每次任务切换都有事件，调度路径上多几次调用 |
| `OsVendorArtiTraceCat2Isr` | true | Cat2 ISR（`AR_CP_OSARTI_CAT2ISR` 或 `AR_CP_OS_CAT2ISR`） | ISR 的激活、开始、被抢占、恢复、结束 | 中：每次 Cat2 中断进出各一次 |
| `OsVendorArtiTraceApplication` | true | OS-Application（`AR_CP_OS_APPLICATION`） | 应用的 Start、Restart、AllowAccess、Terminate | 低：只在应用状态变化时 |
| `OsVendorArtiTraceSpinlock` | true | 自旋锁（`AR_CP_OS_SPINLOCK`） | Locked、Released | 低到中：随 `GetSpinlock`、`ReleaseSpinlock` 的调用频率 |
| `OsVendorArtiTraceHook` | true | Hook（`AR_CP_OS_HOOK`） | 已配置的 `OsErrorHook`、`OsPreTaskHook`、`OsPostTaskHook`、`OsProtectionHook`、`OsStartupHook`、`OsShutdownHook` 以及各应用的 Error、Startup、Shutdown Hook；每个 Hook 一对 Start 和 Return 事件，没有配置的 Hook 不产生事件 | 低：Hook 本来就是少数路径 |
| `OsVendorArtiTraceServiceCalls` | false | 服务调用（`AR_CP_OS_SERVICECALLS`） | 每个 OS 服务（`ActivateTask`、`SetEvent`、`GetResource` 等）的进入（`_Start`）和退出（`_Return`），带参数和返回值 | **高**：每个服务调用多两个事件，且这类事件在管理态（`SPRVSR`）发出。默认关，只在需要看调用序列时打开 |

- 开关只影响运行时 trace 事件，不影响 `Os_Arti.arxml` 里的静态描述。
- 关闭一个类时，三处同时去掉：`Os_Arti.arxml` 不再有这类 `ArtiHook` 描述，`Os_ArtiHooks.h` 里对应的包装宏变为空，内核对应的插桩不编译进去。
- 事件、参数与描述始终来自同一份事件表（`Os_ArtiEvents.m`），所以不会出现"内核发了描述里没有的事件"。

### 2.4 常见配置

| 目的 | 设置 |
| :--- | :--- |
| 不用 ARTI | `OsUseArti` = false |
| 只做停机调试（不接 trace 工具） | `OsUseArti` = true，六个 `OsVendorArtiTrace*` 全关。不需要 `Os_Arti.h`，内核代码与没有 trace 时完全相同 |
| 看任务和中断的调度时间线 | `OsUseArti` = true，只开 `Task` 和 `Cat2Isr`，模型选 ENHANCED |
| trace 工具只支持基础状态机 | 模型选 STANDARD |
| 看 OS 服务调用序列 | 在上面基础上再开 `ServiceCalls` |
| 默认 | `OsUseArti` = true，ENHANCED，除 `ServiceCalls` 以外的五类开 |

- 打开任意一类事件后，编译就需要 `Os_Arti.h`：可以用 trace 工具提供的版本，也可以定义 `OS_ARTI_USE_MOCK` 改用 Mock。
- 打开 trace 后关中断的路径会变长，时间保护的预算需要在这个配置下重新标定。

## 3. 本 OS 的约定（写入集成手册）

- **宏参数顺序**按 SWS_Arti_00018：`ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter)`。
- **`_instanceName`** 取 `OsOS` 容器的短名（t1 中是 `OsOS`）。
- **`instanceParameter`** 是 OS 核索引，即 `Os_Inf_GetCoreId()` 的值，由 `TM_ArtiCoreIndex` 映射成 `Core<n>`。
- **`_contextName`**：服务调用事件是 `SPRVSR`，其余所有事件都是 `NOSUSP`。对 `NOSUSP` 事件，内核保证调用时中断已屏蔽到 `OS_ISR_TP_DISABLE_LEVEL`（凡是可能从未加锁路径进入的调用点，内核都会在本地先屏蔽再发事件）。优先级高于该级别的 Cat1 ISR 仍可能打断 hook，hook 的实现要对此可重入。
- **跨核调用**采用核间中断加 RPC：`ActivateTask`、`SetEvent`、`TerminateApplication` 的事件在目标核上发出。
- **状态模型**：任务和 Cat2 ISR 的事件由影子状态 `ArtiState` 决定，与内核的 `State` 无关。原因是 ISR2 进入时，内核会把被打断的任务改成 READY。
- **默认行为**（还需与 trace 工具方确认）：
  - 多重激活不发 `Activate`。
  - `WaitEvent` 时所等事件已置位，则不发 `Wait`。
  - 强制终止（保护处置、`TerminateApplication`）一个处于 Preempted、Waiting、Activated 或 Released 状态的任务，也发 `Terminate`。
  - Cat2 的 `Activate` 与 `Start` 同时发出，内核拿不到中断挂起的时刻。
  - `ChainTask` 时，目标任务的 `Activate` 可能先于调用者的 `Terminate`；两者是不同对象的状态机，互不影响。
  - TerminateTask 正常结束时不会返回，所以没有 `OsServiceCall_TerminateTask_Return`；`StartOS`、`ShutdownOS`、`ShutdownAllCores` 同样没有 Return。
- **时间保护**：打开 trace 后，关中断的路径会变长，时间保护的预算需要在这个配置下重新标定。
- **Cat1 ISR** 不经过 OS。需要的话由用户自己在 ISR1 里插桩，类名用 `AR_CP_ARTIEXT_CAT1ISR`，`_instanceName` 与上面保持一致。

## 4. 已在本机完成的验证

用 `arm-none-eabi-gcc` 13.2（`-D__HIGHTEC__`，`-O2`）编译内核，配置取 t1 工程的生成代码：

1. `OsUseArti` 关闭时，23 个目标文件的代码段、数据段、只读段和 bss 与改动前**逐字节相同**。
2. `OsUseArti` 打开、六类事件全关时，也与改动前逐字节相同。
3. 打开 trace 时，增强模型、标准模型、服务调用开关的各种组合都能用 Mock 编译通过，开 `-Wall -Wextra` 后与改动前相比没有新增警告。Mock 对四个字面 token 做拼接，所以内核代码里的事件与 `ArtiHook` 描述不一致时，编译会直接失败。
4. 参数组合编译：`tools/arti/build_kernel_matrix.py` 对 23 个组合各生成一次 t1 的 Os 代码，用 `-Wall -Wextra` 和 Mock 编译全部内核源码（23 个目标文件）加 `Os_Arti_Mock.c`。23 个组合全部通过：都能编译，相对"原内核、同样 `OsUseArti` 状态"没有新增警告；`OsUseArti` 关闭和六类全关两种配置的目标文件与原内核逐字节相同。组合是：`OsUseArti` 关、六类全关、默认、默认加 STANDARD、全开（两种模型）、默认下各关掉五个类之一、六个类各自单独打开（两种模型）。用法见脚本开头的说明。`OsUseArti` 打开时内核自带的 orti 运行时会被编入。原内核的 `Os_orti.c` 把 `0x1A2`、`ServiceId*2+3` 这类最大到 `0x1dc` 的值写进 `Os_ServiceType` 枚举字段；枚举按最小类型存放时（`arm-none-eabi-gcc` 默认）只有 1 字节，值被截断，ARTI 的 `ServiceTrace` 对不上类型映射表。现已把 `Os_OrtiType.ServiceId` 改成 `uint16`（`orti/Os_orti_types.h`），警告消失。
5. 仓库测试 `tests/generator/test_os_arti_hooks.py` 检查描述、头文件、Mock 三者一致，以及开关和模型的效果；`tests/generator/test_arti_event_stream.py` 测试事件流检查脚本。

## 5. 上板验证（需要在目标板上完成）

### 5.1 采集

1. 生成时打开 `OsUseArti`，定义 `OS_ARTI_USE_MOCK`，并把 `Os_Arti_Mock.c` 一起编译。
2. 如果需要跨核排序，定义 `OS_ARTI_MOCK_TIMESTAMP()`，例如读全局系统计数器。
3. 运行用例后，用调试器导出 `Os_ArtiMockLog`（cores × `OS_ARTI_MOCK_DEPTH` × 20 字节）和 `Os_ArtiMockCount`（cores × 4 字节）的原始内存，再检查：

```
python -m tools.arti.check_event_stream --mock <生成目录>/Os/kernel/Os_Arti_Mock.h \
    --log-bin log.bin --count-bin count.bin --depth 512 [--strict-start]
```

`Os_ArtiMockBadCore` 不为 0，说明有事件的核索引超出范围。从系统启动开始、且缓冲区没有回绕的采集，用 `--strict-start` 检查。

### 5.2 必备用例与期望序列（增强模型，同一个核）

| # | 场景 | 期望事件 |
| :--- | :--- | :--- |
| 1 | 基本链路 | `Activate(A)` `Start(A)` … `Activate(B)` `Preempt(A)` `Start(B)` `Terminate(B)` `Resume(A)` `Terminate(A)` |
| 2 | 扩展任务等待 | `Wait(A)` … `Release(A)` … `Continue(A)`，不允许出现 Waiting 直接到 Running |
| 3 | 先被抢占、后又等待 | 两次重新运行分别是 `Resume` 和 `Continue` |
| 4 | `WaitEvent` 时事件已置位 | 没有 `Wait` |
| 5 | ISR2 打断任务、不触发重调度 | `Activate(X)` `Start(X)` `Stop(X)`，没有任何任务事件 |
| 6 | ISR2 退出时重调度 | `Stop(X)` `Preempt(A)` `Start(B)`，`Stop` 必须在最前 |
| 7 | ISR2 嵌套 | `Start(X)` `Preempt(X)` `Activate(Y)` `Start(Y)` `Stop(Y)` `Resume(X)` `Stop(X)` |
| 8 | `ChainTask`；`Schedule()` 让给更高优先级 | `Terminate(A)` 与 `Activate(B)`；`Preempt(A)` … `Resume(A)` |
| 9 | BCC2/ECC2 多重激活 | 被抢占时再次激活，恢复时仍发 `Resume`；带挂起激活的 `Terminate` 之后发 `Start` |
| 10 | 强制终止（处于 Running、Preempted、Waiting） | `Terminate`；之后重新激活时发 `Start` |
| 11 | 跨核 `ActivateTask` / `SetEvent` | 事件出现在目标核的缓冲区里；`Activate` 的时间戳早于目标核随后的 `Start` |
| 12 | 自旋锁 | `Locked` 与 `Released` 成对出现，自旋等待期间没有事件 |
| 13 | hook | `OsHook_<名>_Start` / `_Return` 成对出现；ProtectionHook 的 Return 参数是实际采取的处置 |

以上用例检查脚本都能自动判定。第 4、9 两条要对照用例的具体代码看：脚本只能判断事件流本身合法，判断不了某个事件是否被漏发。

## 6. 发现的其它问题

- **内核 ProtectionHook（已修，2026-10-13）**：`OsHook_CallProtectionHook` 原先丢弃 `OsHook_Internel_VerifyProtectionReaction()` 的返回值，按校验前的值处置；没有配置 ProtectionHook 时，局部的 `PRO_SHUTDOWN`（SWS_Os_00107）也没有被用上。现在按校验后的处置执行，并写回 `Os_HookDynPtr->ProtectionReaction`。同一函数里"可信函数中发生内存/异常保护错误则关机"的判断，原先拿处置值（`PRO_*`）和错误码比较，这个分支永远不成立；现改为检查 `FatalError`。修复前编译器把校验调用整个优化掉了（`OsHook_CallProtectionHook` 从 368 字节变为 476 字节），说明这个 bug 确实生效过。
- **内核 `OsIsr_PostISR` 的错误分支（已修，2026-10-14）**：ISR 结束时若还持有资源、自旋锁或关着中断（SWS_Os_00368/00369），原代码只调用 ErrorHook 就结束，没有结束这个 ISR；ErrorHook 返回后走向取决于 `PostISR` 入口处的 `lr`，只有用户 ISR 是叶子函数时才会碰巧重入 `PostISR` 而正常结束，否则跳进用户 ISR 的中间。另外持有锁的分支在 `OsLock_ClearLockList` 清空链表之后又读 `LockList->LockType`，即读地址 0，ErrorHook 收到的错误码是随机的。现改为：先按链表头的类型确定错误码，再清理、调用 ErrorHook，之后重新关中断并走正常的 ISR 结束流程（EOI、`Stop`、调度或切回被打断的 ISR）。验证：把新旧两个版本编译成 ARM 代码，在 Unicorn 里配合桩函数运行 5 种场景、2 种 `lr` 状态；旧版本持有锁的场景读空指针出错、中断被关的场景在 `lr` 残留时跳到错误地址，新版本 10 个组合都正常结束，错误码分别为 6（资源）、19（自旋锁）、12（中断被关），EOI 时中断级别都是 20。
- **`Os_memmap.h` 不完整**：原因不在配置工具的渲染。t1 的 Os 配置里没有 `MemoryBlock`、`MemorySection`、`OsMemoryMap`（EB 工程里分别是 1 个块列表、118 个段、94 个映射），模板循环为空，却仍然输出末尾的 `#endif`，生成的 C 代码因此不合法。插件模板已改为只在有映射时才输出 `#endif`，没有映射时由 `MEMMAP_ERROR` 报出明确的错误。2026-10-13 已从 EB 集成测试工程（`03_test/.../tr002_THA6_OS_Project/Os_Configuration/config/Os.xdm`）向 t1 导入 8 个 MemoryRegion、118 个 MemorySection、25 个 MemoryBlock、94 个 OsMemoryMap，t1 原有的 89 个容器内容不变。导入后 t1 生成的 `Os_memmap.h` 与内核工程里 EB 生成的版本逐行一致，内核用 t1 自己的生成代码可以编译通过。

## 7. 把生成的 `Os_Arti.arxml` 导入 GUI 查看

模板生成的 `Os_Arti.arxml` 是 `/AUTOSAR/EcucDefs/Arti` 的 ECUC value 文件，可以导入配置工具查看。

- **方法一（只看，不动工程文件）**：打开工程，在左侧树选中 **Arti 模块**（工程里要已有 Arti 的定义 `definitions/Arti/Arti_ParamDef.arxml`），菜单 `File → Import → Import Value File...` 选 `Os_Arti.arxml`，确认"替换当前配置"。导入只改内存；不要保存工程，磁盘文件就不会变。
- **方法二**：把生成文件复制或改名为工程的 `ConfigValue\Arti_Config.arxml`，再打开工程。注意这会替换同名的手工配置。
- 同一个模块只有一份配置，导入是整体替换，不是合并。
- 实测（t1，无界面渲染）：1075 个容器、866 个参数、940 条引用全部载入，引用全部解析，树和面板无异常；已设引用在下拉框中的选中数见下。
- 2026-10-14 修复了两个显示和保存的问题：引用下拉框原先因为 `/Os/Os/...` 与 `/Os/...` 写法不同而全部显示"(Not set)"（现在 Arti 919 条引用中 917 条、Os 183 条中 175 条能选中）；STRING 参数的 `TRUE` 原先保存后变成 `true`（现保持原样）。
- 2026-10-14 起，t1 里全部已设引用的下拉框都能选中（Arti 919、Os 183、EcuC 2、Can 2）。之前 12 条没有候选项，有三个原因，已分别处理：解析器只读 `<a:da name="REF" value=…>` 单值写法，读不到 `<a:v>` 多值写法（Os 的 AppMode 引用）；解析器写死了属性命名空间版本 16，读不到 `EcuC.xdm` 用的版本 10；t1 手写的 `EcuC.xdm` 把核容器叫 `EcucCore`，而 `Os.xdm`、Arti 定义和 Os 模板里的路径都是标准的 `EcucCoreDefinition`，现已在 t1 里改成标准名（实例 `EcucCoreDefinition_0`、`_1`，与 EB 项目一致）。保存工程仍会丢掉文件头的注释（A1 到 A5 假设说明）。

## 8. 类型映射表里的名称字符串

trace 工具把数字 ID 显示成名称，用的是 `ArtiParameterTypeMapPair` 的 `ArtiParameterTypeMapPairOutput`（字符串）。2026-10-14 起，凡是带 `ArtiParameterTypeMapPairOutputRef`（指向实例的引用）的 Pair，模板都同时生成这个字符串，值是该对象的原名，写法与 EXP ARTI Listing 6.1 一致（字符串和引用并存）：

| 映射表 | 字符串 |
| :--- | :--- |
| `TM_TaskId`、`TM_Isr2Id` | 任务名、Cat2 ISR 名 |
| `TM_TaskState` | `RUNNING`、`READY`、`WAITING`、`SUSPENDED` |
| `TM_AppMode` | AppMode 名 |
| `TM_TaskStack`、`TM_TaskContext` | 所属任务名（不是 `<任务>_stack` 容器名） |
| 调度表状态、自旋锁状态 | 状态名 |

其余映射表原来就有字符串。测试：`test_os_arti_template.py` 里的三个 `name_string` 用例，以及 `test_arti_orti_parity.py::test_task_id_emits_task_name_string`。

## 9. 接入 trace 厂商提供的文件

厂商提供 `Arti.h`、`Os_Arti.h`、`Arti.c`（要求和示例见 `ARTI_vendor_requirements.md` 与 `vendor_example/`）。拿到后：

1. **放进工程**：三个文件放在应用或 BSW 目录，不放进内核目录。存放 `Arti.h` 和 `Os_Arti.h` 的目录加入头文件路径，`Arti.c` 加入编译。内核要能找到 `Std_Types.h`。
2. **去掉 Mock**：不要定义 `OS_ARTI_USE_MOCK`。`Os_Arti_Mock.h/.c` 可以留着，也可以从编译里剔除。
3. **配置并重新生成**：`OsUseArti` 打开，按厂商工具支持的类选 `OsVendorArtiStateModel`（只支持基础类选 `STANDARD`，否则 `ENHANCED`），打开需要的 `OsVendorArtiTrace*`；重新生成 Os 代码。把生成的 `Os_Arti.arxml` 交给厂商的工具或调试器；厂商的 `Os_Arti.h` 应由它生成，或与它核对。
4. **编译与缺宏**：厂商的 `Os_Arti.h` 缺某个事件的宏时，编译只给出"隐式声明"警告，链接时报 `undefined reference to ARTI_TRACE_<类>_<事件>`。对照 `Os_Arti.arxml` 的 `ArtiHook` 描述补齐。
5. **调用 `Arti_Init`**：内核不调用它，由集成者在 `StartOS` 之前调用，每个被 trace 的核都要初始化，具体按厂商的要求。
6. **先验证再上板**：先用 Mock 把内核编过、事件流检查通过，再换厂商文件。之后出问题，基本可以判断是厂商文件与描述不一致。`tools/arti/check_event_stream.py` 读 Mock 的日志格式，厂商工具输出的数据需要先转换成该格式；这一步没有验证过。上板用例见第 5 节。
7. **注意**：打开 trace 后关中断的路径变长，时间保护的预算要重新标定；`NOSUSP` 事件在关中断下发出，厂商的宏必须很短、不调用 OS 服务；厂商的实现必须可重入，高优先级的 Cat1 ISR 仍可能打断 hook。
