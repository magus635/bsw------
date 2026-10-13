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

模板放在插件的 `generate_PB/` 下：`Os_ArtiEvents.m` 与 `Os_AppCommon.m` 同级，`Os/Os_Arti.arxml` 在 `Os/` 下，其余四个文件在 `Os/kernel/` 下。仓库 `templates/Os/` 下的是源版本。

## 2. 配置参数（`OsOS` 容器，本 OS 私有）

| 参数 | 默认值 | 说明 |
| :--- | :--- | :--- |
| `OsUseArti` | false | 标准参数，ARTI 总开关 |
| `OsVendorArtiStateModel` | ENHANCED | 选 ENHANCED 时用 `AR_CP_OSARTI_TASK` / `AR_CP_OSARTI_CAT2ISR`，选 STANDARD 时用 `AR_CP_OS_TASK` / `AR_CP_OS_CAT2ISR`。同时决定 `ArtiStatesTaskEnhanced` |
| `OsVendorArtiTraceApplication` / `Task` / `Cat2Isr` / `Spinlock` / `Hook` | true | 各类事件的开关 |
| `OsVendorArtiTraceServiceCalls` | false | 每个 OS 服务的进入和退出都会产生事件，开销最大 |

- **只做停机调试**（不接 trace 工具）：打开 `OsUseArti`，把六个 `OsVendorArtiTrace*` 全部关掉。这时不需要 `Os_Arti.h`，内核代码与没有 trace 时完全相同。
- 打开任意一类事件后，编译就需要 `Os_Arti.h`：可以用 trace 工具提供的版本，也可以定义 `OS_ARTI_USE_MOCK` 改用 Mock。

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
4. 仓库测试 `tests/generator/test_os_arti_hooks.py` 检查描述、头文件、Mock 三者一致，以及开关和模型的效果；`tests/generator/test_arti_event_stream.py` 测试事件流检查脚本。

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
- **`Os_memmap.h` 不完整**：原因不在配置工具的渲染。t1 的 Os 配置里没有 `MemoryBlock`、`MemorySection`、`OsMemoryMap`（EB 工程里分别是 1 个块列表、118 个段、94 个映射），模板循环为空，却仍然输出末尾的 `#endif`，生成的 C 代码因此不合法。插件模板已改为只在有映射时才输出 `#endif`，没有映射时由 `MEMMAP_ERROR` 报出明确的错误。2026-10-13 已从 EB 集成测试工程（`03_test/.../tr002_THA6_OS_Project/Os_Configuration/config/Os.xdm`）向 t1 导入 8 个 MemoryRegion、118 个 MemorySection、25 个 MemoryBlock、94 个 OsMemoryMap，t1 原有的 89 个容器内容不变。导入后 t1 生成的 `Os_memmap.h` 与内核工程里 EB 生成的版本逐行一致，内核用 t1 自己的生成代码可以编译通过。
