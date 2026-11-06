# vBRS 配置代码 EB 模板设计

日期：2026-11-06。本文取代 `docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md` 和 `openspec/changes/add-vbrs-code-templates`。这两份是另一个 AI 的方案，用户已叫停该 AI，并授权全部推翻重做。

## 1. 要做什么，为什么

用户要用本工具为自己的工程生成 vBRS 的配置代码。这类工程以 THA6206 为代表：配置是 EB 风格，OS 是用户自己移植的内核。

生成的配置代码要和 Vector vBRS 的静态核心代码（BrsMain、BrsHw）一起编译、链接。之后再和 MCAL、自研 OS 内核、MICROSAR BSW（EcuM、Rte 等，位于 `D:\davinci\mcuapp\Components`）组成一个完整的 AUTOSAR Classic ECU 工程。

不直接用 DaVinci 的原因：工程配置在本工具里，OS 也不是 MICROSAR Os。DaVinci 只能处理 MICROSAR 工程。

做成的标准：

1. 给定同一份 vBRS 配置，本工具生成的 vBRS 文件与 DaVinci（MSR 生成器）生成的逐字节一致，文件头注释除外。
2. 生成的全部配置文件能和 Vector 静态代码一起，在目标编译器下编译、链接通过；链接后，每个标签都落在正确的区域上。

## 2. 用户已定的事项

- 模板格式用 EB 兼容格式（`[!…!]`），不用轻量 TemplateEngine。
- 生成结果给本工具自己的工程用，不替代 DaVinci 去处理 Vector 工程。
- 允许用 DaVinci 生成对照输出，允许反编译分析 vBRS 的 JAR。
- 只做 MSR 生成器（GeneratorMsr 14.09.01），DvC6 本次不需要。
- 配置代码和已有的核心代码（Vector 静态 BrsMain/BrsHw）一起编译链接。
- OS 是"我们自己移植的这套"。
- 编译器方面，用户原话："ads，gcc，tasking，hitec等等都可以"。
- 另一个 AI 的改动可以全部推翻。
- 2026-11-06 对设计审查问题的答复：
  - 复位和内存初始化交给 Vector 的启动代码（BrsHw → `Brs_ApplicationEntry`），厂商的 `startup.c` 退出。
  - 编译器用 ADS。
  - THA6206 最高 CPU 频率为 400 MHz，本工具芯片数据里的 120 MHz 是错的。

## 3. 目标、非目标、反目标

**目标**

- **G1**：用 EB 模板生成 vBRS 的 4 个常规输出：`vBrsCfg.h`、`vBrs_Lcfg.h`、`vBrs_Lcfg.c`、`Makefile.config.generated`。
- **G2**：从本工具的存储布局生成 `vLinkGen_Cfg.h`、`vLinkGen_Lcfg.h`、`vLinkGen_Lcfg.c`。由于 Vector 启动代码接管内存初始化，这些表必须覆盖厂商 `startup.c` 现在做的全部内存工作（见 §5.3）。
- **G3**：静态代码按名字引用的链接标签都由本工具的链接文件生成器保证存在。这些标签包括每核启动栈顶、每核异常向量表起点，以及初始化表里的起止地址和加载地址。
- **G4**：完成两类验证：与 DaVinci 输出对照；用 ADS 编译、链接。
- **G5**：逐项对照厂商 `startup.c` 和 Vector BrsHw 的启动步骤，列出 BrsHw 没有覆盖的非内存工作（例如 TCM 配置寄存器、从核启动），并给出每项的落点（见 §5.7）。

**非目标**

- EcuM/SchM 桩。样例里 `vBRSEnableEcuMStubGeneration` 和 `vBRSEnableSchmStubGeneration` 都是 false，而且真实的 EcuM/Rte 已在 Components 里。
- DvC6 生成器。
- vLinkGen 的链接脚本（`vLinkGen_Template.ld`）。本工具已有自己的链接文件生成器。
- 修改 Vector 静态代码或用户内核。BrsHw 缺的步骤放进 Vector 留给用户的回调文件（如 `BrsMain_Callout_Stubs.c`），不改 Vector 的其他文件。
- 第一个工具链（ADS）以外的链接文件生成器，如 GNU ld、Tasking LSL。
- 上板或仿真运行。
- 把 Vector 的 BSWMD、静态代码或 JAR 反编译结果放进本仓库。

**反目标**（即使功能上做出来了，出现以下情况也算失败）

- 模板里没有逻辑，所有内容先在 Python 里拼好字符串，再填进模板。
- 只对上了一份样例配置，换一个开关就不一致。
- 初始化表和链接文件各自计算，标签名或区域对不上，要到上板时才发现。
- 静默猜值。例如缺少 Os 核映射或启动栈区域时，仍生成一个"看起来能编译"的文件。

## 4. 已查明的事实

### 4.1 样例与对照输出

- **样例工程**：`D:\davinci\mcuapp\Applications\SipAddon\StartApplication`。THA6206，2 核，工程编译器设为 `LlvmHighTec`。
- **对照输出可以重新生成**：2026-11-06 已在样例副本上运行 DaVinci 命令行，生成 vBRS 和 vLinkGen。
  - 副本位置：`%LOCALAPPDATA%\Temp\vbrs-ref-20261106\StartApplication`，dpa 中 `<SIP>` 改为绝对路径 `D:\davinci\mcuapp`。
  - 命令（在 PowerShell 中运行；Git Bash 会把 `/MICROSAR/vBRS` 改写成 Windows 路径）：
    ```
    DVCfgCmd -p <dpa> -g -m "/MICROSAR/vBRS,/MICROSAR/vLinkGen" --extGenStepsToGenerate ""
    ```
  - 结果：耗时 91 秒，0 错误。8 个输出与工程里现存的输出逐行比较，除 `Generation Time` 外完全一致。
  - 结论：现存样例输出可以当作基线，也可以用命令行生成更多对照。
- **vBRS 配置内容**：vBRS 的 ECUC 值有 3 个容器。
  - `vBRSGeneral`：17 个开关。
  - `vBRSHwConfig`：时钟、FPU、指令集、对 Mcu 时钟参考点的引用、评估板信息。
  - `vBRSMemoryInit`：4 个初始化值、64 位开关、全局禁用开关。
- **衍生芯片信息不在 vBRS 配置里**：`BRS_DERIVATIVE_Tongxin_THA6206`、核类型、最高频率、核数来自 DaVinci 工程的 Derivative 设置和 SIP 里的衍生芯片数据。
- **核配置来自 Os**：`BrsMain_CoreConfig` 取自 MICROSAR Os 的核配置。生成文件里的注释原话是 "For MultiCore setups, the information is mainly based on the actual OS configuration"。

### 4.2 静态代码的约定

- **初始化表的版本与调用方式**：`BrsMainStartup.c` 包含 `vLinkGen_Lcfg.h`，并要求 `VLINKGEN_CFG_MAJOR_VERSION == 2`、`MINOR >= 10`（样例是 2.19）。它按阶段（Early、Zero、One、Two、Three、PowerOn、HardReset）和核号调用 `Brs_MemoryZeroInit` 和 `Brs_MemoryInit`，只有表的数量宏大于 1 时才调用，因为数量里包含结尾的空项。
- **`vLinkGen_Cfg.h` 也是必需的**：`vLinkGen_Lcfg.h` 包含 `vLinkGen_Cfg.h`，后者里有版本宏和数量宏，并包含 `vBrsCfg.h`。
- **`vBrs_Lcfg.c` 通过 BrsHw 的宏引用标签**（`ARMBrsHw_CortexR52.h:194–198`）：
  - `BRSHW_DEFINE_STARTUP_STACK(x)` 展开为 `_STACK_C<x>_LIMIT`。
  - `BRSHW_DEFINE_EXCVEC(x)` 和 `BRSHW_DEFINE_INTVEC(x)` 都展开为 `_OS_EXCVEC_CORE<x>_CODE_START`。
- **`brsMain_CoreType` 的成员顺序不能改**：启动汇编按偏移读取它的成员（`ARMStartup_CortexR52.c:550–605`，偏移 4 是 PhysicalCoreId，偏移 8 是 StartupStackEndLabel）。
- **R52 的 BrsHw 只支持 HighTec LLVM**：
  - 其他编译器会命中 `#error "Compiler not yet supported"`（`ARMBrsHw_CortexR52.h:281`）。
  - `BRS_COMP_LLVMHIGHTEC` 分支用的是 GNU 风格的内联汇编。
  - 本机没有安装 HighTec，但有 Arm Development Studio 2024.1（armclang/armlink）和 arm-none-eabi-gcc 13.2。
- **BrsMain 依赖的 Os/EcuM 接口**：`BrsMain.c` 调用 `Os_InitMemory`、`Os_Init`、`Os_InitialEnableInterruptSources`、`EcuM_Init`、`EcuM_StartupTwo`、`StartNonAutosarCore`。用户内核在 `Os.h:1435–1437` 声明了前三个，但 tr002 主干的源码里找不到它们的定义。

### 4.3 本工具现状

- **vBRS 配置已能读入**：能加载 vBRS BSWMD（`D:\davinci\mcuapp\DemoComponents\vBRS\BSWMD\vBRS_bswmd.arxml`）和 ECUC 值，EB 模板可以用 `as:modconf('vBRS')` 读取。但还不支持 ECUC-MULTILINE-STRING，所以 `vBRSMakefileUserCode` 读不进来。
- **链接文件生成器**：
  - 只能生成 ADS scatter（`core/memmap/generators/ads.py`）。
  - 区域种类有 code、const、data、bss、noinit、stack、reserved，没有"初始化策略、初始化阶段、所属核"这些属性。
  - 按编译器区分的标签表在 `core/memmap/symbols.py`：ADS 用 `Image$$…$$Base/Limit` 和 `Load$$…`，GHS 用 `__…_ADDRESS_START`。
- **代码生成器的输出文件名**：只支持 `{Module}_xxx` 形式或链接文件后缀。`vBrsCfg.h`、`Makefile.config.generated` 这类名字需要显式指定。
- **芯片数据**：THA6206 的数据有 `cores.count=2`、`available=[CORE0, CORE1]`、`master=CORE0` 和 `cpu_frequency`。
- **用户 Os 定义**（`doc/OS/OS define文件/Os.xdm`）里有：
  - `OsNumberOfCores`
  - `OsCoreIdMappingConfig`：由 `OsCoreId` 引用 EcucCoreDefinition，并给出 `OsPhysicalCoreId`
  - `OsApplicationCoreRef`

### 4.4 设计审查后补查的事实

- **两套启动代码**：本工具现有的 THA6206 工程用厂商的 `startup.c` 启动（`doc/THA6XXX_MC_AS440/…/Startup/startup.c`）。它负责以下工作，然后才调用 `_main()`：
  - 每个核设置各自的模式栈（`CORE<n>_*_STACK`）；
  - 经 ITMU 清 TCM；
  - 复制向量表和 clone 区域；
  - 按区域名复制或清零。

  Vector 的样例则从 `ARMStartup_CortexR52.c` 进入 `Brs_ApplicationEntry`，由 vLinkGen 表完成内存初始化。这两条路此前没有人做过选择（`vLinkGen_技术分析与借鉴.md` 第 737 行的问题一直未答）。2026-11-06 用户选定由 Vector 接管。
- **HighTec 的使用痕迹**：样例的 `Appl/TestSuit.elf` 和 `TestSuit.map` 于 2026-10-31 用 HighTec v8.1.0 构建（`Makefile.static:64` 设置 `COMPILER_MANUFACTURER = LLVMHIGHTEC`，`Makefile:84` 设置 `COMPILER_BASE_WIN = C:\HighTec\toolchains\arm\v8.1.0`）。本机没有这个目录，可见 HighTec 装在别的机器上。
- **Vector 可能有 Arm6 版 BrsHw**：`ARMBrsHw_CortexR52.h` 和 `Brs_MemMap.h` 的注释提到 Arm6；`Brs_MemMap.h` 用的 `#pragma clang section` 在 armclang 下也能用。
- **芯片数据与 Vector 数据冲突**：
  - Vector SIP 的 `vBaseEnv_THA6_pre.arxml` 记为 CORTEX_R52、400 MHz、2 核。
  - 本工具的 `THA6206_LFBGA292.yaml` 记为 `cpu_frequency: 120000000`，没有核类型字段，而且这一项不在 `unconfirmed` 列表里。
  - 后果：`BrsHw.c:5010` 在 `BRS_TIMEBASE_CLOCK > BRS_CPU_MAX_FREQUENCY` 时报 `#error`。样例的 TimebaseClock 是 400 MHz，按 120 MHz 生成就无法编译。
- **表项的 Alignment 有取值限制**：`BrsMainStartup.c:335–354` 规定 Alignment 为 0 或 4 时按 32 位写，为 8 时按 64 位写，其他值进入异常处理。样例中每核 OS 数据用 8，其余用 4。ECC 内存若用小于 ECC 粒度的写入来清零，可能触发 ECC 错误。
- **两份 BrsMain**：
  - 样例 `Appl/Source` 里的一份是 BRSMAIN_VERSION 0x0221，要求 vLinkGen minor ≥ 10。
  - SIP 的 `DemoComponents/vBRS/Implementation/_BrsMain*.c` 是新一版模板，要求 minor ≥ 16。
  - 生成 minor 19（与样例相同）时两份都满足。BrsHw 只有样例里有。

## 5. 设计

### 5.1 产物与数据来源

| 文件 | 生成方式 | 数据来源 |
| --- | --- | --- |
| `vBrsCfg.h` | EB 模板 | vBRS 配置；衍生芯片宏、核类型、最高频率、核数取自芯片数据 |
| `vBrs_Lcfg.h`、`vBrs_Lcfg.c` | EB 模板 | Os 核映射（逻辑核号、物理核号、是否为 AUTOSAR 核）；启动栈大小取自存储布局中该核的启动栈区域 |
| `Makefile.config.generated` | EB 模板 | 与 `vBrsCfg.h` 相同，另加每个核是否使用 |
| `vLinkGen_Cfg.h`、`vLinkGen_Lcfg.h`、`vLinkGen_Lcfg.c` | 链接文件生成器，与链接文件出自同一份 Plan | 存储布局 |

DaVinci 的数据来源在本工具里的对应：

- dpa 里的 Derivative（`Tongxin_THA6206`）对应芯片数据里的厂商和型号。
- SIP 衍生芯片数据（核类型、核数、最高频率）对应芯片数据。
- MICROSAR Os 的核配置对应用户 Os 的 `OsCoreIdMappingConfig` 和 `OsApplicationCoreRef`。
- vLinkGen 配置中段组的初始化策略、阶段和所属核，对应存储布局的区域（见 §5.3）。

### 5.2 模板

- 4 个 vBRS 文件各用一份 EB 模板，作为模板包放在仓库的 `template_packs/vBRS/` 下。用户在工程里把它设为模板目录后才会使用。这是因为本工具不提供运行时内置默认模板（`openspec/project.md`，remove-default-templates）。
- 逻辑写在模板里。Python 只补引擎缺少的函数，每个新函数都要有单元测试。
- 输出文件名显式声明：`vBrsCfg.h`、`vBrs_Lcfg.h`、`vBrs_Lcfg.c`、`Makefile.config.generated`。
- 文件头用本工具自己的，不复制 Vector 的版权和许可声明。对照时去掉文件头注释块后比较，正文（包括其中的说明性注释）要逐字节一致。
- 输入不全时报错，不生成。需要报错的情况包括：
  - 工程里没有 vBRS 模块；
  - 开了多核支持，但 Os 里没有核映射；
  - 某个核没有启动栈区域；
  - 芯片数据缺少核类型或频率。
- 模板的每个分支都以 JAR 中的逻辑为准。例如 `vBRSMcuClockReferencePointForBrsPeriphClock` 引用了 Mcu 时钟参考点；如果 JAR 用这个引用计算 `BRS_PERIPH_CLOCK`，模板也要通过同一引用读取。

### 5.3 初始化表与链接标签

- **由谁生成**：`vLinkGen_*` 三个文件由链接文件生成器生成，与链接文件用同一份 Plan、同一张按编译器区分的标签表（`symbols.py`）。理由：如果两边各算一遍，迟早会对不上（见反目标第 3 条）；同时，链接文件生成器是存储布局的权威，这是此前已定的原则。
- **区域如何变成表项**（覆盖厂商 `startup.c` 的内存工作）：
  - 执行地址与加载地址不同的区域（从 Flash 加载、在 RAM/TCM 执行）生成 Init 表项，不论种类是 data 还是 code/const。这样就覆盖了 INT_VECTOR_TABLE、CODE_CLONE、DATA_CLONE、PRIVATE_CODE_CORE<n>、PRIVATE_DATA_CORE<n>、RAM_CODE，以及各 LMU 的 DATA 区域。区域里如果还有 ZI 段，再加一条 ZeroInit 表项。
  - bss 区域生成 ZeroInit 表项。
  - noinit、stack，以及在 Flash 上执行的 code/const 不进表。
  - 生成时检查：每个 RW/ZI 区域、每个需要复制的区域都在表里，有遗漏就报错。
- **所属核与核本地别名窗口**：
  - 区域在某个核私有的窗口上（例如 CPU0 TCM 的全局地址），所属核就是该核。
  - 区域在核本地别名窗口上（CPUXATCM、CPUXCTCM 等，同一地址在每个核上指向各自的 TCM），每个核各生成一条表项：地址相同，所属核分别为 0…n−1。
  - 其他共享 RAM（LMU 等）的所属核为启动核。
  - 所属核可以在存储布局配置里按区域覆盖。
- **阶段**：默认为 ONE，可以在存储布局配置里按区域覆盖。新增的字段都是可选的，旧配置文件不受影响。本次不做 UI 编辑。
- **ECC 内存的整块初始化**（取代厂商 `startup.c` 用 ITMU 清 RAM 的做法）：
  - 用 vLinkGen 的 Early 区域块表。BrsHw 的启动汇编在设置栈之前按核遍历这张表；Alignment 为 8 时用 64 位写入（`ARMStartup_CortexR52.c:425–473`）。
  - 哪些窗口需要整块清零、由哪个核清，记在芯片数据里（新字段）。THA6206 按厂商 `startup.c` 现有的 ITMU 清除清单填写：每个核清自己的 ATCM、BTCM0、BTCM1、CTCM；核 0 另外清 LMU1、LMU2、LMU3。
  - 没有标记的窗口不清。One 和 HardReset 区域块表本次为空。
- **表项的 Alignment**（我的决定）：
  - 取自芯片数据中窗口的 ECC 粒度（新字段）。TCM 按 Cortex-R52 的 64 位 ECC 填 8；其他 RAM 先填 4，并标"待确认"。
  - 可以在存储布局配置里按区域覆盖。
  - 只允许 0、4、8 三个值，否则报错。不能用 scatter 的 `align`（例如 64）代替。
- **启动栈**（我的决定）：
  - 每个核新增一个 `STACK_C<n>` 区域，放在该核的 TCM 里，不复用内核的 `CORE<n>_USER_STACK`。内核的 `Os_link_Lcfg.c` 引用后者；如果复用，启动阶段会和内核共用同一块栈。
  - BrsHw 从启动栈顶依次切出 ABT、IRQ、FIQ、UND、SVC、SYS 六个模式栈，每个大小为 `MODE_STACK_SIZE`（`ARMStartup_CortexR52.c:607–622`），剩下的留给 main。区域大小在存储布局里配置；生成时检查它至少能容纳六个模式栈再加一个最小余量。
  - `vBrs_Lcfg.c` 里的 StartupStackSize 取这个区域的大小。
- **排序**：表项按区域名排序。这与样例一致，也符合本工具"按名字排序"的约定。
- **静态代码要求的区域**：存储布局里必须有每个核的启动栈区域和异常向量区域，名字以静态代码的宏为准，形如 `STACK_C<n>` 和 `OS_EXCVEC_CORE<n>_CODE`。缺失时要报出来。沿用现有机制，即"代码引用到的区域必须存在"；如有必要，把这些名字加进需求扫描。
- **ADS 下的特殊处理**：
  - armlink 不能在 scatter 里定义任意符号，所以表里直接写 `Image$$<R>$$Base`、`Image$$<R>$$Limit` 和 `Load$$<R>$$Base`。
  - 必须关闭 RW 数据压缩（`--datacompressor=off`），否则按表复制的结果是错的。
  - 启动过程不经过 `__main` 和 `__scatterload`，内存初始化完全依靠这些表。因此表必须覆盖每一个 RW/ZI 区域；生成时检查，有遗漏就报错。

### 5.4 编译器

- 生成的 C 代码与编译器无关。按工具链变化的只有 `vLinkGen_Lcfg.c` 里标签的写法和链接文件本身。
- 第一个验证的工具链是 ADS（armclang + armlink），用户已确认。
- Vector 的 R52 BrsHw 只认 HighTec。armclang 和 HighTec LLVM 同属 clang，所以计划在不改静态代码的前提下处理：
  - 编译时选中 BrsHw 的 HighTec 分支；
  - 链接时把 `_STACK_C<n>_LIMIT` 和 `_OS_EXCVEC_CORE<n>_CODE_START` 映射到 armlink 的 `Image$$` 符号，例如用 armlink steering 文件的 `RESOLVE … AS …`。
- 上面这条路先做成实施的第一个小实验。如果不改静态代码就走不通，停下来问用户。如果用户能从 Vector 拿到 Arm6 版 BrsHw，就改用它，这个实验也就不需要了。
- GCC、HighTec、Tasking 本次不做。以后支持它们时，需要各自的链接文件生成器和标签表，模板不用改。

### 5.5 vBRS 模块进入工程

- vBRS 的定义文件直接引用已安装 SIP 里的 BSWMD，不复制进仓库。
- 补上 ECUC-MULTILINE-STRING 参数类型，包括解析、保存，以及在界面上显示为多行文本。
- vBRS 的值可以在本工具里编辑，也可以导入已有的 ECUC 文件（例如样例里的 `StartApplication_vBRS_vBRS_ecuc.arxml`）。

### 5.6 验证

1. **与 DaVinci 对照**（vBRS 的 4 个文件）
   - **对照矩阵**：以样例配置为基础，模板读取的每个开关各改一次，覆盖以下几类：
     - 多核开/关，单核与双核；
     - 首个执行实例，FBL、HSM、Hypervisor、SafeContext、InterruptOnly；
     - LED 与引脚；
     - 时钟、指令集、FPU；
     - 初始化值、64 位开关、全局禁用。

     完整的开关清单在实施时从 JAR（javap 反汇编）里列全，每个分支至少一个用例。
   - **每个用例的做法**：
     1. 复制样例工程，修改 vBRS 的 ECUC（必要时也改 Os 核数），用 DVCfgCmd 只生成 vBRS。
     2. 本工具用同样的 vBRS 值，加上等价的芯片数据和 Os 核映射，渲染模板。
     3. 两边都去掉文件头，统一换行符后逐字节比较。
   - **夹具**：DaVinci 的输出去掉 Vector 文件头后存为测试夹具。生成夹具的脚本放在 `tools/` 下，用环境变量指向 DaVinci 安装目录；没设环境变量时，相关测试跳过。
2. **`vLinkGen_*` 三个文件**
   - 与样例逐行对照这些部分：类型定义、版本宏、表和集合的名字、数量宏、空表的写法、表项格式。
   - 表的内容用存储布局夹具做单元测试。
3. **ADS 编译链接**
   - 仿照 `tools/os_port_check` 做一个检查工具：把 Vector 静态 BrsMain/BrsHw 复制到临时目录（不动原文件），与生成的配置文件、Os/EcuM 桩一起用 armclang 编译，再按生成的 scatter 链接。
   - 从链接映射中检查：
     - 每个标签都已解析；
     - 每条初始化表项的起止地址和加载地址与对应区域一致；
     - 每个核的启动栈顶等于该核栈区域的上界。
   - 在 pytest 里，没有设置 ADS 相关环境变量时跳过。
4. **回归**：现有测试全部通过（已知与本次无关的 14 个失败除外），生成器指纹保持稳定。

### 5.7 启动步骤对照（G5）

厂商 `startup.c` 里有一些不属于内存初始化的工作，BrsHw 未必都做。实施时逐项对照，每项写明 BrsHw 是否已做、谁来补、补在哪里。目前已知的有：

| 厂商 `startup.c` 的步骤 | 需要确认的问题 |
| --- | --- |
| 每种模式的栈指向内核的 `CORE<n>_{USER,FIQ,IRQ,UNDEFINED,ABORT,KERNEL}_STACK`（第 932–1032 行） | BrsHw 从启动栈切出模式栈。内核启动后是否自己重设模式栈？如果不重设，IRQ/SVC 栈会小得多 |
| 写 BTCM/CTCM 配置寄存器（`Startup_SetTCMAddr`，ARM 勘误 CPU.H001） | BrsHw 只配置核内的 TCM 区域寄存器，这一步可能缺失 |
| Hyp 栈和临时 SVC 栈（第 818–858 行） | BrsHw 从 Hyp 模式进入时是否需要 |
| 从核启动（`Startup_StartSlaveCore`） | 与 Os 的 StartCore、BrsMain 的多核流程是否重复或冲突 |
| `UNCLEAR_RAM_BSS` 的特殊处理（第 266 行） | 对应到表里的哪一类，还是不进表 |

补的位置按以下顺序选：

1. 能用表表达的，放进生成的表；
2. 其次放进 Vector 留给用户的回调文件（如 `BrsMain_Callout_Stubs.c`）；
3. 需要改内核或 Vector 其他文件的，先停下来问用户。

本次交付对照表和回调代码草稿。上板验证属于整机集成，不在本次范围。

## 6. 集成缺口（本次不做，先记录）

- 用户内核声明了 `Os_InitMemory`、`Os_Init` 和 `Os_InitialEnableInterruptSources`，但没有定义，而 BrsMain 会调用它们。
- MICROSAR EcuM 同样期望 MICROSAR Os 风格的接口。
- 内核的向量表段需要放进 `OS_EXCVEC_CORE<n>_CODE` 区域，`BrsHw_ExceptionTable_Init` 才能拿到正确的地址。

以上都属于"整机工程能跑起来"的范围。本次的编译链接验证用桩函数代替。

## 7. 旧工作的处理

- 新的 OpenSpec 变更使用新 id，暂定为 `add-vbrs-eb-templates`。在同一次提交里删除以下内容（它们都已提交，可以从 git 历史找回）：
  - `openspec/changes/add-vbrs-code-templates`
  - `docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md`
  - `docs/superpowers/plans/2026-11-06-vbrs-*`（其中包括 944 KB 的清单 JSON）
- `stash@{0}` 里是另一个 AI 未提交的改动。它保留到新变更合入之后，再征得用户同意删除。其中关于 MULTILINE_STRING 的改动可以参考，但要按本设计重写并补上测试。

## 8. 约束

- 不修改 `D:\davinci` 下的任何文件，对照输出都在副本上生成。
- 仓库里只放本工具的模板，以及去掉 Vector 文件头的对照夹具。
- 反编译只用 JDK 自带的 javap；已有的部分结果在 `%LOCALAPPDATA%\Temp\vbrs-jar-analysis-20261105`。用户没有确认过下载第三方反编译器，所以不下载。
- 走 OpenSpec 流程：提案批准后再实施，实施时用 TDD。
- 遵守 CLAUDE.md：排序确定、路径用 POSIX 风格、生成器指纹稳定。

## 9. 留给实施者

- 引擎缺哪些函数、输出文件名怎样实现。
- 对照矩阵的具体用例，从 JAR 里把分支列全后确定。
- ADS 下标签映射的具体手段（steering 文件或其他办法），以第一个实验的结果为准。
- 存储布局新增字段的命名。

## 10. 用户已回答的问题（2026-11-06）

1. 复位和内存初始化由谁负责：交给 Vector BrsHw 的启动代码。
2. 编译器：ADS。
3. THA6206 最高 CPU 频率：400 MHz。本工具芯片数据里的 120 MHz 要改正。

## 11. 我做的决定（请阅读时核对）

- `vLinkGen_*` 三个文件由链接文件生成器生成，不用 EB 模板（§5.3）。
- 文件头用本工具自己的，对照时去掉文件头（§5.2）。
- 表项规则（§5.3）：
  - 执行地址与加载地址不同就生成复制表项；
  - 核本地别名窗口里的区域每个核各一条；
  - 阶段默认为 ONE；
  - 所属核按窗口推断，可以覆盖。
- ECC 内存整块清零用 Early 区域块表，清单照搬厂商 `startup.c` 的 ITMU 清单（§5.3）。
- 表项的 Alignment 取自芯片数据中窗口的 ECC 粒度：TCM 为 8，其余为 4 并标"待确认"（§5.3）。
- 每个核新增独立的 `STACK_C<n>` 启动栈区域，不复用内核的栈（§5.3）。
- 芯片数据新增 Vector 衍生芯片标识、核类型、最高频率、窗口 ECC 粒度、窗口整块清零五类字段。不从 SIP 的 vBaseEnv 读取，以保持"输入来自本工具自己的数据"（§5.1）。
- 本次只做 THA6206。它是唯一同时有 Vector BrsHw 和对照输出的芯片。
- 编译链接检查使用样例 `Appl/Source` 和 `Appl/Include` 里的静态代码（唯一和 BrsHw 配套的一份）。源码路径作为参数传入。
- BrsHw 缺少的步骤按"表 → 回调文件 → 问用户"的顺序补（§5.7）。
- 反编译只用 javap，不下载第三方反编译器。
- 新的 OpenSpec id 定为 `add-vbrs-eb-templates`；旧变更和旧文档在同一次提交中删除；stash 暂时保留（§7）。
