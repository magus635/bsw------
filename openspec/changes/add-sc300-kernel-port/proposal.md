## Why

`add-sc300-chip` 完成后，可以为 SC300 配置项目并生成 Os 代码，但主干内核（`tr002_THA6_OS_Project/Os`）只支持 Cortex-R52 + GICv3：上下文切换、中断入口、异常处理在 SDK 的 `exception.s` 里，使用 R52 的处理器模式、`ICC_PMR`、`TPIDRURO`、EL1 通用定时器和 R52 MPU。生成的 SC300 代码因此无法编译运行。

此前我说“没有现成的 SC300 内核”，这个结论不对。THA6206 HSM 工程（`Desktop/02_Hsm/tr001_THA6206_HSM_Application/Code/os/Os`，SVN 原路径 `D:\14_Security\...\CATL_Br003_From_General_ReleaseV1_2_0`）里已经有本内核的 Cortex-M3 移植，用 `armclang -mcpu=sc300 -D__OS_SUPPORT_CORTEX_M3__` 编译，并在量产分支上运行。但它是从旧版本分出来的裁剪版：

- 只有任务、事件、资源、ISR、钩子和应用，没有 counter、alarm、调度表、定时器、IOC、自旋锁、MPU 和时间保护；
- 与主干差异很大：`Os_task.c` 约 1000 行、`Os_isr.c` 约 900 行、`Os_application.c` 约 800 行，主干后来的修复（例如 TaskDeinit、PostISR、ARTI）都不在里面。

## What Changes

把 HSM 移植里已在量产中验证过的 Cortex-M3 硬件适配层搬进主干内核，用编译宏选择架构，使同一份内核源码同时支持 R52 和 SC300。

- **架构选择**：沿用 HSM 的宏 `__OS_SUPPORT_CORTEX_M3__`。定义了这个宏时，选用 Cortex-M3 的编译器接口头文件、上下文帧和硬件适配层；没有定义时，R52 的代码逐字节不变。
- **新增文件**（来自 HSM 移植，按主干现状调整）：
  - `common/Os_compiler_cm3.h`：`Os_Inf_*` 接口的 M3 实现。`ICC_PMR` 改为 `BASEPRI`，用 `svc` 切换特权级，核号固定为 0，没有 FPU 和协处理器。armclang 和 GCC 都使用这一份。
  - `context/Os_context_exception_cm3.s`：任务切换、新线程启动，以及 `SysIRQ_Handler` 和 `SVC_Handler`。
  - `isr/Os_isr_hal_cm3.c`：NVIC 的使能、挂起和优先级设置（3 位优先级，`priority << 5`）。
- **按宏区分的现有文件**：
  - `Os_compiler_types.h`；
  - `Os_context_types.h`：M3 上下文帧为 `Sp, Lr, R4–R12, Primask, Basepri, Control, xPsr`；
  - `Os_context.c`：上下文初始化和中止；
  - `Os_isr_hal.c` 与 `Os_isr_hal.h`；
  - `Os_timer_hal.c`：M3 下不编译 EL1 通用定时器，系统节拍由模板生成的 SysTick 驱动提供。这部分模板已有。
- **范围是 SC1**：SC300 上提供任务、事件、资源、ISR、钩子、counter、alarm、调度表和 SysTick。单核，不需要 IOC 跨核通道和自旋锁，按单核配置编译。不做 MPU（SC3/SC4）和时间保护（SC2/SC4）。
- **插件 `Os.xdm`**（主副本在 `D:/19_AutosarOS`，同步到 T1 和 `doc/OS`）：选 `Os_SC300` 时增加 INVALID 校验：
  - 只允许 SC1；
  - 不能启用内存保护和时间保护；
  - `OsIsrPriority` 在 0–7 之间，内部异常号只允许 SysTick 和 PendSV 之类可配置的系统异常。

  校验只报错，不改用户的配置。
- **模板**：逐项核对 SC300 分支与新的上下文帧和中断表是否一致。这些分支原先是为 HSM 移植写的。

## 不在本变更内

- HSM 工程本身不改动，仍使用它自己的分支内核；以后是否迁到主干另行决定。
- SC300 的 MPU（是否实现、几个 region）资料不足，不做。
- PendSV 式的上下文切换重写（见 design.md 的备选方案）。

## Impact

- Affected specs：`os-kernel-cortex-m3`（新能力）。
- Affected code（都不在本仓库）：
  - 内核：`tr002_THA6_OS_Project/Os` 中 `common/`、`context/`、`isr/`、`timer/` 下的上述文件；由用户提交 SVN。
  - 插件：`Os_THA6_ASR21/config/Os.xdm`，以及 SC300 分支模板（如需修正）。
  - T1 和 `doc/OS` 中的对应副本。
- 仓库：如果模板或 xdm 有改动，同步 `doc/OS`；新增 SC300 示例配置的生成测试（只在找到插件模板时运行，与 ARTI 测试的方式相同）。
- **兼容性**：未定义 `__OS_SUPPORT_CORTEX_M3__` 时，R52 的目标文件必须逐字节不变。这是验收条件。
- **验证限制**：本机没有 armclang 和 SC300 板。
  - 编译和链接用 `arm-none-eabi-gcc 13.2`（`-mcpu=cortex-m3`）。
  - 运行验证有两条路，需要你选：一是装 QEMU，用 Cortex-M3 的 `mps2-an385` 板模型跑任务切换、SysTick 和 ISR；二是只在你的 SC300 板上验证。
