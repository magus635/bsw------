## Context

主干内核的上下文模型（SDK `platform/startup/exception.s`）：

- 服务调用用 `svc #0` 进入，`EL1_SVCHandler` 把 `SPSR` 改成 System 模式后返回，所以 API 在调用者的栈上以特权模式运行；`Os_Inf_TrapToUserMode` 用 `cps #0x10` 回到 User 模式。
- 任务切换由 C 代码**同步**调用 `Os_Hal_ContextSwitch_Asm(next, cur)`：在 System 模式下直接 `bx lr` 到新上下文；在 IRQ 模式下（ISR 结束时）用 `eret` 直接返回新任务。
- 中断屏蔽和资源天花板用 GIC 的 `ICC_PMR`；`TPIDRURO` 存当前线程；核号来自 `MPIDR`。

Cortex-M3（ARMv7-M）没有这些处理器模式，也没有 `ICC_PMR`；异常返回必须经由 `EXC_RETURN`，Handler 模式下不能直接“跳”进一个线程。

## Goals / Non-Goals

- Goals：同一份内核源码支持 SC300；内核公共代码（任务、调度、事件、资源、alarm 等）不改；R52 目标文件逐字节不变。
- Non-Goals：MPU、时间保护、多核；重写 HSM 工程。

## Decisions

### D1. 沿用 HSM 移植的“中断在线程模式下处理”方案（推荐）

HSM 移植的 `SysIRQ_Handler`：

1. 所有外设中断和 SysTick 都进入它。它先把 `BASEPRI` 临时设为 `0x20`，再保存 `CONTROL`、`BASEPRI` 和 `xPSR`。
2. 如果被打断的是线程模式（`EXC_RETURN != 0xFFFFFFF1`），就在栈上伪造一个异常帧，异常返回到线程模式的下一条指令，在**线程模式**下调用 `OsIsr_InterruptHandler`。
3. 处理完后执行 `svc #0`，由 `SVC_Handler` 恢复硬件自动保存的现场。
4. 如果是嵌套中断（`EXC_RETURN == 0xFFFFFFF1`），就直接在 Handler 模式下处理。

这样 ISR 结束时的任务切换仍然是一次同步的 `Os_Hal_ContextSwitch_Asm`（保存 `sp, lr, r4–r12, primask, basepri, control, xpsr`，然后 `bx lr`），与 R52 的调用约定相同。`Os_isr.c`、`Os_task.c` 等公共代码不需要知道架构。

理由：已在 HSM 量产分支运行；对公共代码零侵入，主干后来的修复可以直接用在 SC300 上。

### 备选：PendSV 延迟切换（不推荐用于本变更）

这是 FreeRTOS 等通用做法：ISR 里只设置 `PENDSVSET`，切换在最低优先级的 PendSV 中进行。它更符合 ARMv7-M 的惯例，嵌套也简单。但内核在很多地方假定“调用切换函数后不再回到调用点”（例如 `OsIsr_PostISR`、`TerminateTask`、`ChainTask`），改成延迟切换要改公共代码，而且 R52 也要跟着改，风险和验证量都大得多。

### D2. 架构选择用 `__OS_SUPPORT_CORTEX_M3__`，与编译器无关

`Os_compiler_types.h` 先判断 `__OS_SUPPORT_CORTEX_M3__`，定义了就包含 `Os_compiler_cm3.h`；没有定义时保留现在的编译器分支。M3 头文件只用 GNU 内联汇编语法，armclang 和 arm-none-eabi-gcc 都能编译。HSM 的命名是 `Os_compiler_ads_cm3.h`；主干去掉 `ads`，因为它与编译器无关。

### D3. 优先级映射

SC300 有 3 位优先级（HSM 的 `priority << 5`；Arm 的 SC300 CMSIS 头文件 `__NVIC_PRIO_BITS = 3`）。`OsIsrPriority` 的取值 0–7 直接写成 `priority << 5`。`BASEPRI` 的天花板用同样的编码。`BASEPRI = 0` 表示不屏蔽，所以优先级 0 的中断不能被 OS 屏蔽（这是 ARMv7-M 的限制）。`Os.xdm` 的校验提示用户：Cat2 ISR 不应配置为 0。

### D4. 单核编译

`OS_KERNEL_MAX_CORE_NUM` 由模板按 `NumOfCores = 1` 生成。

- `Os_spinlock_hal.c` 的 `ldrex/strex` 在 ARMv7-M 上可用，保留；
- `OsIsr_Hal_TriggerSoftwareInterrupt`（跨核中断）在 M3 上为空操作，与 HSM 相同；
- `Os_Inf_GetCoreId` 返回 0。

### D5. R52 不变的证明

改动前后，用 `arm-none-eabi-gcc -D__HIGHTEC__ -mcpu=cortex-r52`、相同参数，编译主干内核和 T1 的 6206 配置，比较所有 `.o` 是否逐字节相同。做法与 ARTI 那次相同。

## Risks / Trade-offs

- **中断入口路径**：伪造异常帧依赖 `EXC_RETURN` 的值和栈布局，在 r1p1 之前的 M3 上还有 8 字节对齐（`STKALIGN`）的问题。SC300 r0p0 基于 Cortex-M3 r2p0，默认开启 `STKALIGN`。
  - 缓解：照搬 HSM 已验证的代码，不做改写；在 QEMU 或板上覆盖“线程被打断”和“中断嵌套”两条路径。
- **SC300 与 Cortex-M3 r2p0 的差异**：公开资料只有 Cortex-M3 TRM（DDI 0337）；SC300 TRM 是保密文档。
  - 缓解：只用 ARMv7-M 架构定义的寄存器（NVIC、SCB、SysTick），不用实现相关的特性。
- **HSM 与主干长期分叉**：本变更不合并它们，以后由用户决定是否让 HSM 改用主干。

## Open Questions（需要你决定）

1. 范围按 SC1 是否可以（不做 MPU 和时间保护）？
2. 运行验证：是否允许我安装 QEMU（`qemu-system-arm`，用 `mps2-an385` 板模型）？还是只做编译链接，再由你在板上验证？
3. HSM 移植里与主干不同的公共代码（例如 `Os_ServiceCallInputType` 改成指向常量的指针），是否有 SC300 特有的原因？如果没有，本变更只取它的硬件适配层，公共代码一律以主干为准。
