## 0. 前提
- [x] 0.1 用户回答 design.md 的三个开放问题（范围、运行验证方式、HSM 公共代码差异）
- [x] 0.2 备份主干内核 `tr002_THA6_OS_Project/Os`、SDK `platform/startup`、插件 `Os.xdm`
- [x] 0.3 R52 基线：用 arm-none-eabi-gcc（`-D__HIGHTEC__`）编译主干内核和 T1 的 6206 生成代码，保存全部 `.o`

## 1. 硬件适配层（内核）
- [x] 1.1 `common/Os_compiler_cm3.h`：从 HSM 的 `Os_compiler_ads_cm3.h` 移入，补齐主干新增的 `Os_Inf_*` 接口和 `Os_AtomicBitClear`
- [x] 1.2 `Os_compiler_types.h`：先判断 `__OS_SUPPORT_CORTEX_M3__`
- [x] 1.3 `context/Os_context_exception_cm3.s`：从 HSM 移入；对照 `Os_Hal_ContextMpuSwitch_Asm` 和 `Os_Hal_ServiceContextSwitch_Asm` 在主干中的调用点，确定 M3 下的行为（MPU 关闭时不调用，单核没有跨核服务）
- [x] 1.4 `Os_context_types.h` 和 `Os_context.c`：按宏区分上下文帧、`ContextInit` 和 `ContextAbort`
- [x] 1.5 `isr/Os_isr_hal_cm3.c`：NVIC 实现；`Os_isr_hal.c` 和 `Os_isr_hal.h` 中的 GICv3 部分放到 `#ifndef` 里
- [x] 1.6 `timer/Os_timer_hal.c`：M3 下不编译 EL1 定时器；核对 counter 的硬件节拍来自模板生成的 SysTick 驱动
- [x] 1.7 检查其余 `Os_Inf_*` 和 FPU 的使用点，确认 M3 下都有定义或已排除

## 2. 插件与模板
- [x] 2.1 `Os.xdm`：增加 SC300 的 INVALID 校验，只报错不改值；同步到 T1 和 `doc/OS`（实际规则见实施记录）
- [x] 2.2 核对模板的 SC300 分支（`Os_context_Lcfg.c`、`Os_isr_Lcfg.c`、`Os_isr_Cfg.h`、`Os_timer_Callout.c`）与新的上下文帧和中断表一致；补 `Os_memmap.h` 的 SC300 分支
- [x] 2.3 准备一份 SC300 示例配置，用于生成和编译（由 T1 裁成单核，见实施记录）

## 3. 验证
- [x] 3.1 R52：改动后重新编译，全部 `.o` 与 0.3 的基线逐字节一致
- [x] 3.2 SC300：用示例配置生成代码，与主干内核一起用 `arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -D__OS_SUPPORT_CORTEX_M3__` 编译并链接成 ELF，没有错误和新增警告
- [x] 3.3 在 QEMU `mps2-an385` 上运行：任务激活和切换、`WaitEvent`/`SetEvent`、资源天花板、SysTick 驱动 alarm、Cat2 ISR 打断线程以及 ISR 嵌套
- [ ] 3.4 用户在 SC300 板上用 armclang 编译并运行
- [x] 3.5 本仓库：生成测试（找到插件模板时运行）；全量测试通过

## 实施记录（2026-10-25）
- 用户决定：范围 SC1；装 QEMU（11.1.0，`mps2-an385`）；公共代码以主干为准，只取 HSM 的硬件适配层。
- 内核（`tr002_THA6_OS_Project/Os`；改动前的备份在会话草稿区 `backup_m3/`）：
  - 新增 `common/Os_compiler_cm3.h`、`context/Os_context_exception_cm3.s`、`isr/Os_isr_hal_cm3.c`；
  - `Compiler.h`、`Os_compiler_types.h` 在 ADS 和 HighTec 分支里按 `__OS_SUPPORT_CORTEX_M3__` 选 M3 头文件；
  - `Os_context_types.h`（M3 上下文帧）和 `Os_context.c`（ContextInit、ContextAbort、ContextSetParam）按宏区分；
  - `Os_isr_hal.c/.h`、`Os_timer_hal.c`、`Os_mpu_hal.c`：R52 实现放进 `#if !defined(__OS_SUPPORT_CORTEX_M3__)`。M3 的 `OsTimer_Hal_TriggerInterrupt` 置 SysTick 或 NVIC 的挂起位。EL1 定时器和 MPU 在 M3 上不编译，配置错时链接失败。
- 相对 HSM 移植改正的问题（HSM 工程本身没改，这些问题它也有）：
  - `DisableInterruptSource`、`ClearPendingInterrupt` 对 NVIC 的写 1 寄存器用了 `|=`，会关掉或清掉同一组 32 个里所有已使能或已挂起的中断；改为直接写；
  - `IsEnable` 把掩码值强转成 8 位 `boolean`，第 8–31 位永远读成 FALSE；改为 `!= 0`；
  - 中断返回和提权共用 `svc #0`，非特权任务调 API 会被当成中断返回而破坏栈；改为 `svc #255` 用于中断返回、`svc #0` 只提权，降权直接写 CONTROL；
  - 伪造异常帧的返回地址用 `add r1, pc, #8` 算出，依赖指令对齐；改为 `adr` 标号；写 CONTROL 后补 `isb`。
- 插件与模板（主副本 `D:/19_AutosarOS/...`，同步到 T1 和 `doc/OS`）：
  - `Os.xdm`：`OsResourceSubderivative` 增加 4 条 INVALID：SC1；所有 ISR 的优先级在 1–7；硬件 counter 用 SysTick 且不是高分辨率；单核；
  - `memorymap/Os_memmap.h`：SC300 没有内存布局配置，加一个分支 `#undef MEMMAP_ERROR`，段留在默认段，由工程链接脚本放置。
- 验证：
  - R52：改动前后用 `arm-none-eabi-gcc -D__HIGHTEC__` 编译主干内核和 T1 的 6206 配置，23 个 `.o` 逐字节一致（新增的 `Os_isr_hal_cm3.o` 在 R52 下为空）；
  - 生成：T1 的 6206、6412 生成结果除时间戳外不变；
  - SC300：用 T1 裁成单核的示例配置生成代码，与主干内核一起用 `-mcpu=cortex-m3` 编译出 46 个目标文件，打开警告后没有隐式声明、指针或截断类警告；
  - QEMU `mps2-an385`：16 步检查全部通过，包括任务抢占、Cat2 ISR 打断任务、ISR 嵌套、资源天花板、SysTick 驱动 alarm 唤醒 `WaitEvent`、ISR 结束后切到更高优先级的任务；
  - `Os.xdm` 规则：用本工具的 XPath 引擎对示例配置和 4 种错误配置求值，每种只触发对应的一条，6206 不触发；仓库测试 `tests/generator/test_os_sc300_definition.py`；
  - 全量测试 1079 个通过，4 个跳过。
- 没覆盖到：Handler 模式下的中断嵌套（只有优先级 0 的中断才会走到，配置上已禁止）；非特权线程的提权路径（SC300 模板把所有上下文都设为特权）。
- 另外发现，未修：
  - 本工具的 XPath 引擎把谓词里的 `and`/`or` 当成顶层运算符，`count(X[a or b]) > 0` 会算错；规则因此改用 `count(X[a]) + count(X[b])` 和链式谓词 `[a][b]`。（已在 2026-10-25 修复：`_find_word_outside_context` 计入方括号，`_evaluate_predicate_condition` 自己处理 `and`/`or` 和括号；测试 `tests/generator/test_xpath_predicate_logic.py`）；
  - T1 的任务只把系统应用列为访问应用，所属的 `OsApplication_Trusted_Core0` 激活不了自己的任务（`E_OS_ACCESS`），R52 上也一样；
  - T1 的自启动任务挂在 `OS_APPMODE_ANY` 上，`StartOS(OSDEFAULTAPPMODE)` 不会启动它们；
  - 主干 `Os_compiler_hightec.h` 的 `Os_AtomicBitClear` 用了 `P2VAR`，而 `Compiler.h` 在定义 `P2VAR` 之前就包含了这个头文件，所以 HighTec/GCC 下编译不过（ADS 版本用 `uint32`，不受影响）。
