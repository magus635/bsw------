# vLinkGen / vBaseEnv 技术分析与对本工具内存映射的借鉴

| 项目 | 内容 |
|---|---|
| 分析对象 | Vector MICROSAR Classic vLinkGen Technical Reference 2.11.0（2025-05-13）；Vector vBaseEnv User Manual 2.30.0（2025-03-26） |
| 来源文件 | `doc/vector工具说明/TechnicalReference_vLinkGen.pdf`（35 页）；`doc/vector工具说明/UserManual_vBaseEnv.pdf`（92 页） |
| 对照对象 | 本工具 `autosar_configurator/core/memmap/`（内存映射工作台与链接文件生成器）、`core/hardware/memory_regions.py`（芯片存储数据） |
| 编写日期 | 2026-11-04 |
| 性质 | 参考分析。Vector 工具只作为机制参考，不是本工具要对齐的答案；本工具的生成器仍然是链接文件的唯一权威。 |

下文引用时，"TR §x" 指 vLinkGen Technical Reference 的章节，"UM §x" 指 vBaseEnv User Manual 的章节。

---

## 1. 摘要

vLinkGen 是 Vector 的链接脚本生成器。它先用一份**与编译器无关**的模型描述链接布局，再按所选编译器生成链接脚本，同时生成**初始化表**（`vLinkGen_Lcfg.c`）。

vBaseEnv 是让一颗芯片"能编译、能链接、能启动"的基础环境包。它和 vLinkGen 的分工如下：

- **vBaseEnv 提供硬件存储区**：每个芯片型号一份，带 ECC 对齐、类型、是否核本地寻址等属性。
- **vBaseEnv 提供一套超集默认布局**：包含专门放启动代码、向量表、启动栈的区域块。
- **vBRS 的启动代码读 vLinkGen 生成的表**：按阶段、按核完成清零和 ROM→RAM 复制，启动栈也从生成的表里取。

整条链路是这样的：

> 芯片型号的硬件存储区（vBaseEnv）→ Memory Region → Memory Region Block → Logical Group → Section Group → Linker Section → 链接脚本 + 初始化表 → 启动代码（vBRS）读表初始化

本工具已有与之同构的主干：芯片存储窗口 → 执行区域 → 段（经规则放置），并且已经采用"编译器无关的 plan + 按编译器的生成器"的结构。对照两份文档后得出以下结论：

1. **生成文件缺少"默认段 / 特殊段 / 固定用途区域"的表达**。vBaseEnv 为启动代码和向量表各设一个专门的区域块，并说明在部分平台上向量表的位置决定能否正确启动；本工具生成的 scatter 只写扫描到的 MemMap 段。这一点影响能否链接成功，优先级最高。
2. **ARM 跨加载区域时的顺序**：vLinkGen 明确规定了顺序如何调整，并用空区域作标记接续；本工具目前会写出向后引用，只给一条警告。
3. **"内容类型 + 核号"元数据，加上"超集布局 + 可用性"**，可以在换芯片或多核时自动选窗口。vBaseEnv 正是用这个机制给每个 OS 核自动生成启动栈并放好位置。
4. **初始化表与启动代码的配合方式**是 vBaseEnv 里最有参考价值的部分：启动代码不按名字引用区域，而是遍历生成的表，启动栈也从生成的表取。本工具的 `startup.c` 目前按区域名硬引用，是否改造需要先做决定。
5. **芯片存储数据还缺两项属性**：ECC 对齐，以及核本地寻址的重叠规则（核本地区域之间可以地址重叠，其余区域不能重叠）。

---

## 2. vLinkGen 概述

### 2.1 定位

- vLinkGen 是一个 BSW 模块（Vendor ID 30，Module ID 255），只支持 pre-compile 配置（TR §1）。
- 目标是用抽象方式描述链接脚本，让代码、常量和变量落到预期的存储位置。配置时不需要懂具体编译器的链接脚本语法。
- 模块本身不提供 C 初始化函数、状态、主函数或错误上报（TR §2.2–2.5）。初始化由 vBRS 的启动代码读取生成的表来完成（见 §5.6）。
- 两份文档都声明：生成的链接脚本和代码是**示例代码**，未经质量控制，不能直接用于量产（TR §1，UM §1）。

### 2.2 支持的编译器

ARM（5.x、6.x 及以上）、Wind River Diab、GCC、Green Hills、HighTec（GCC/LLVM）、IAR（7.x 及以上）、Linaro、Microchip MPLAB XC32、NXP（GCC）、Renesas、Tasking、Texas Instruments（含 LLVM）、Synopsys ARC Ccac（TR §1.1）。

### 2.3 生成的文件（TR §3.1）

| 文件 | 内容 | 集成方式 |
|---|---|---|
| `vLinkGen_Lcfg.c` | 初始化表 | 编进工程 |
| `vLinkGen_Lcfg.h` | 类型定义、初始化表的 extern 声明 | 编进工程 |
| `vLinkGen_Cfg.h` | pre-compile 宏 | 编进工程 |
| `vLinkGen_Template.<ext>` | 完整的链接脚本 | 可能需要先预处理，再交给链接器 |
| `vLinkGen_Template_<Variant>.<ext>` | 某个变体专用的完整链接脚本 | 直接交给链接器 |
| `vLinkGen_Inc_<Name>.<ext>` | 脚本片段（按模块、变体或 Logical Group 划分） | 只能被其他脚本 include，不能单独使用 |

- 脚本生成在 DaVinci 工程的 "Template Files" 目录，配置一变就会被覆盖。需要手改的话，应先复制到别处。
- vBaseEnv 的构建环境（MakeSupport）默认链接 `Source/vLinkGen_Template.lsl`（UM §5.4）。

---

## 3. 层级模型

### 3.1 六层定义（TR §1.2）

| 层 | 配置容器 | 含义 | 关键属性 |
|---|---|---|---|
| 硬件存储区（Hardware Memory Area） | `vBaseEnvMemLayoutHwRegion` | 芯片上真实的存储布局，由 vBaseEnv 按芯片型号提供，不可修改（详见 §5.2） | 起始地址、大小、类型、ECC 对齐、核本地寻址 |
| 存储区域（Memory Region） | `vLinkGenMemoryRegion` | 映射到硬件存储区的逻辑抽象层，使配置与硬件解耦 | 偏移（Offset）、大小、计算出的可用性与起点 |
| 区域块（Memory Region Block） | `vLinkGenMemoryRegionBlock` | 对 Memory Region 的再划分，也就是脚本里真正写出的存储定义 | 边界（LOWER/UPPER）、位置（Position）、大小、可接收的内容类型、初始化阶段、执行初始化的核 |
| 逻辑组（Logical Group） | `vLinkGenLogical{Const,Var,User,Symbol}Group` | 把若干 Section Group 或链接符号归成一组，映射到一个区域块 | 位置、内容类型、核号、所属变体、默认区域块、复制区域块、执行初始化的核 |
| 段组（Section Group） | `vLinkGen{Const,Var,User}SectionGroup` | 同类输入段的集合，即编译器手册里的"输出段" | 位置、初始化策略、初始化阶段、结尾对齐 |
| 链接段（Linker Section） | `vLinkGenLinker{Code,Const,Var,Stack,Spec}Section` | 最小单位，即编译器手册里的"输入段" | 段名、对齐、快速寻址、**目标文件 / 库过滤**、编译器专用标志 |

Section Group 的大小由它实际包含的段决定。它的起点由配置的位置和同一区域块内前面各组的大小共同决定。

### 3.2 示意（取自 TR 图 1-1，已简化）

```text
vBaseEnv            vLinkGen
硬件存储区     Memory Region     Region Block           Logical Group     Section Group     Linker Section
FLASH ──────► Code_Flash ──┬─► Code_Flash_0 (LOWER) ─► Code_Default ───► Code_Default ───► .text .BSW_CODE .MCAL_CODE
                           └─► Code_Flash_1 (UPPER) ─► Appl_1_Data_RO ─► Appl_1_Data_RO ─► .Appl_1_VAR_INIT_RO
              Data_Flash ────► Data_Flash_0 (LOWER) ─► Const_Default ──► Const_Default ──► .const .BSW_CONST
RAM ────────► Stack_Region ──► Stack_Region_0 ───────► Stacks ─────────► Stacks ─────────► .StackA_VAR_NOINIT ...
              Data_Region ─┬─► Data_Block_0 (LOWER) ─► Appl_1_Data ────┬► Appl_1_INIT ───► .Appl_1_VAR_INIT
                           │                                           ├► Appl_1_NOINIT ─► .Appl_1_VAR_NOINIT
                           │                                           └► Appl_1_ZEROINIT ► .Appl_1_VAR_ZERO_INIT
                           └─► Data_Block_1 (UPPER) ─► Appl_2_Data ────► Appl_2_Data ────► .Appl_2_VAR_*
```

要点有三：

- 区域块可以贴着 Memory Region 的**上边界**往下排。vBaseEnv 的启动栈正是这样放的（见 §5.4）。
- 一个 Logical Group 可以包含多个 Section Group，各自用不同的初始化策略。
- 代码和变量都不直接指定物理地址。更换芯片时只需改硬件存储区的映射。

---

## 4. vLinkGen 关键机制

### 4.1 文件生成方式（`vLinkGenFileGeneration`，TR §2.1.1）

| 方式 | 说明 |
|---|---|
| `STANDARD` | 完整脚本，忽略变体参数 |
| `STANDARD_WITH_VARIANTS` | 完整脚本，属于某个变体的逻辑组用 `#if defined(Variant)` 包起来，可能需要预处理 |
| `ONE_FILE_PER_VARIANT` | 每个变体一个完整脚本，不需要预处理 |
| `MODULE_SNIPPETS` | 每个模块一个片段（包含引用该模块的逻辑组） |
| `MODULE_SNIPPETS_GROUPWISE` | 同上，并按逻辑组 / 段组名加 `#ifdef` |
| `VARIANT_SNIPPETS` | 每个变体一个片段 |
| `LOGICAL_GROUP_SNIPPETS` | 每个逻辑组一个片段 |

片段的使用约束：

- 不是所有编译器都支持片段。
- 片段只包含逻辑组，不含存储定义，也不含全局用户代码组（PRE/POST）。
- 片段必须被主脚本 include。主脚本里的存储定义名称必须与 vLinkGen 配置里的区域块名称一致。

### 4.2 变体（TR §2.1.2，UM §8.4）

- 变体在全局定义（`vLinkGenVariantHandling/vLinkGenVariant`），由逻辑组引用。一个逻辑组可以属于多个变体；不属于任何变体的逻辑组在所有变体里都有效。
- 每次构建必须恰好定义一个变体（例如 `-DVariantName`）。
- **变体专属映射**：逻辑组可以在某个变体里覆盖默认的区域块引用。覆盖项是可选的，例如可以只把 ROM 复制的位置放到别处。这样不必为了换位置而复制逻辑组。
- UM 提到一个技巧：只需要一个变体时，再建一个不被任何逻辑组引用的空变体，用于"不包含该变体逻辑组"的那次构建。

### 4.3 用户代码组（TR §2.1.3）

用 `vLinkGenLogicalUserGroup` 加 `vLinkGenUserSectionGroup` 把编译器专用文本原样写进脚本。插入位置有三种：

| Placement | 位置 |
|---|---|
| `PRE` | 脚本开头 |
| `GROUP_LIST` | 逻辑组列表中的指定位置（不是所有编译器都支持） |
| `POST` | 脚本末尾 |

### 4.4 初始化表（TR §2.1.4）

由 `vLinkGen_Lcfg.c` 生成，启动代码（vBRS）读表执行，执行流程见 §5.6。

| 表 | 类型 | 内容 |
|---|---|---|
| `vLinkGen_ZeroInit_<Stage>_BlocksSet` | `vLinkGen_MemAreaSet` | 在某个阶段整块清零的区域块（ECC 初始化） |
| `vLinkGen_ZeroInit_<Stage>_GroupsSet` | `vLinkGen_MemAreaSet` | 在某个阶段清零的 VAR 段组 |
| `vLinkGen_Init_<Stage>_GroupsSet` | `vLinkGen_RamMemAreaSet` | 在某个阶段从 ROM 复制到 RAM 的段组：VAR 的初值，或在 RAM 中执行的 CONST 代码 |

**初始化阶段（Init Stage，TR 表 2-4，UM §8.2）**：

| 阶段 | 时机 |
|---|---|
| `EARLY` | 复位后立即执行，在启动代码**设置栈指针之前**完成（UM §5.1）。此时 PLL 可能还没初始化，大块区域会很慢，只在必要时使用 |
| `ZERO` | 默认启动流程中第一个执行 |
| `HARD_RESET_ONLY` | 与 ONE 同时机，但只在硬件复位时执行（软件复位时跳过） |
| `ONE` | 默认启动流程中第二个执行；需要初始化时的默认选择 |
| `TWO`、`THREE` | 在 HARD_RESET_ONLY 之后执行，例如需要在两次初始化之间喂狗时使用 |
| `POWER_ON` | 只在冷启动 / 上电复位（UM 另加欠压复位）时执行，热启动不执行。注意 UM §6.1.3 的说明：默认实现没有通用的判断条件，**总会执行**，需要项目自己补条件 |

**初始化策略（Init Policy，UM §8.2.2、§8.2.3）**：

| 对象 | 可选值 |
|---|---|
| VAR Section Group | `INIT`（初值放在 ROM，启动时复制到 RAM）、`ZERO_INIT`（清零）、`NONE` |
| CONST Section Group | `COPY_TO_RAM`（例如在 RAM 中执行的代码）、`NONE` |
| Memory Region Block | 设置初始化阶段和执行初始化的核，即整块清零 |

规则如下：

- 初始化策略按 Section Group 配置，对组内所有输入段生效，所以一个组里只能放初始化方式相同的段。
- **ROM 副本位置、RAM 副本位置、执行初始化的核这三项设置在 Logical Group 上，对组内所有 Section Group 生效。** 需要不同的值时，只能拆成不同的逻辑组（UM §8.2.2、§8.2.3 注）。
- 区域块和 CONST 段组不能使用所有阶段。
- **链接器自带的"复制表"不能与 vLinkGen 同时使用，可能需要通过选项关闭。**

**类型定义（TR §4.1）**：

```c
typedef struct { uint32 Start; uint32 End; uint32 Core; uint32 Alignment; } vLinkGen_MemArea;
typedef struct { uint32 Num; const vLinkGen_MemArea *Areas; } vLinkGen_MemAreaSet;

typedef struct { uint32 Start; uint32 End; uint32 Romstart; uint32 Romend;
                 uint32 Core; uint32 Alignment; } vLinkGen_RamMemArea;
typedef struct { uint32 Num; const vLinkGen_RamMemArea *Areas; } vLinkGen_RamMemAreaSet;
```

- `End` 等于 Start + Size。
- `Core` 是执行这项初始化的核。
- `Alignment` 是硬件存储区的 ECC 对齐，未设置时为 0。

（结构体成员名称取自 TR 表 4-1 至 4-4；`Areas` 写成指针是本文的示意写法，原文只写了类型名。关于 `Core` 是物理核号还是逻辑核号，两份文档说法不一致，见 §8。）

### 4.5 元数据配置（Metadata Based Configuration，TR §2.1.5）

作用是自动把逻辑组分配到正确的区域块。它在以下两种场合特别有用：

- 配置时自动生成新的逻辑组，例如按 OS 核生成的组（实例见 §5.5）；
- 更换被测芯片型号（`vBaseEnvTestedDerivativeRef`）。

| 元数据 | 参数 | 说明 |
|---|---|---|
| 内容类型 | `vLinkGen*GroupContentType` | 逻辑组链接后的内容种类，预定义有 `GLOBAL_CODE`、`LOCAL_DATA`、`STARTUP_STACK` 等，也可以自定义 |
| 核号 | `vLinkGen*GroupCore` | 只对核本地内容有意义 |
| 区域块可接收的内容类型 | `vLinkGenMemoryRegionBlockContentType` | 通常由推荐配置预先填好 |
| 区域是否可用 | `vLinkGenMemoryRegionAvailable` | 当前芯片型号上是否有该硬件存储区，自动设置（见 §5.3） |

工作方式：

- 工具根据逻辑组的内容类型和核号选择区域块（`vLinkGen*GroupRegion`）。需要复制的组，还会一并选好复制目标区域块（`vLinkGenConstGroupRamRegion` / `vLinkGenVarGroupRomRegion`）。
- 选择时会跳过当前芯片上不可用的区域。
- **设置了内容类型，区域块就由工具决定、不能手改；想手动指定，就把内容类型删掉。**

### 4.6 输出顺序（确定性，TR §3.3）

| 输出 | 排序 |
|---|---|
| 区域块 | 在 Memory Region 内先按边界（LOWER、UPPER），再按位置 |
| 逻辑组 | 所有类型放在一起，先按位置，再按容器名 |
| 段组 | 在逻辑组内先按位置，再按容器名 |
| 链接段 | 在段组内按容器名 |
| 链接符号 | 在符号组内按配置的名字 |

### 4.7 标签生成（TR §3.4）

| 编译器 | 标签 | 值 |
|---|---|---|
| ARM | `Image$$<Name>$$Base` / `Image$$<Name>$$Limit` | 起点 / 起点 + 大小（由链接器自己生成，vLinkGen 不额外生成） |
| Ccac、Diab、GHS、GCC、Linaro、HighTec、Tasking、TI | `[_]_<Name>_START` / `_END` / `_LIMIT` | 起点 / 起点 + 大小 − 1 / 起点 + 大小 |
| IAR | `_START`（`$$Base`）/ `_LIMIT`（`$$Limit`） | 起点 / 起点 + 大小 |
| Renesas | `__S_<Name>` / `__E_<Name>` | 起点 / 起点 + 大小 |

各标签的用途：

- `_LIMIT` 供初始化表使用。
- `_END` 是最后一个可写地址，供 MPU 区域的结束地址使用。
- vLinkGen 还会生成逻辑组级别的 `[_]_<LogicalGroup>_ALL_{START,END,LIMIT}`。原文提醒：链接器**不保证**组内各段连续，用于 MPU 时要谨慎。
- 另外可以用 `vLinkGenLogicalSymbolGroup` 定义与编译器无关的自定义链接符号，即名字加数值表达式（UM §8.3）。部分编译器不支持或只部分支持，vLinkGen 会给出警告。

### 4.8 特殊段（`vLinkGenLinkerSpecSection`，TR §3.5，UM §8.1.3）

用来写原样的输入段选择器，值必须符合目标编译器的语法。与其他段不同，特殊段既可以挂在 CONST 段组下，也可以挂在 VAR 段组下。

| 编译器 | 语法 |
|---|---|
| ARM | `*(<Value>[, OVERALIGN <Alignment>])` |
| Ccac、Diab | `.<Short-Name>[ KEEP][ (NOLOAD)][ ALIGN(<Alignment>)] : { <Value> }` |
| GCC | `[. = ALIGN(<Alignment>);] [KEEP(]*(<Value>)[)]` |
| GHS、HighTec、TI | `[. = ALIGN(<Alignment>);] *(<Value>)` |
| IAR | `Block <Short-Name>_BLOCK { section <Value> },` |
| Renesas | `<Value>[, &]` |
| Tasking | `select "<Value>";` |

普通链接段也可以按**目标文件 / 库**过滤（`vLinkGenLinker*SectionFiles`），写法例如 `filea.o;lib1.a(file*.o,file_b.o);file_?.o`，表示只链接这些文件中的该段（UM §8.1.1）。

### 4.9 编译器特殊处理（TR §3.2）

**ARM（与本工具的 ADS 生成器直接相关）**

- 不生成段组的结尾对齐。
- 不生成自定义标签，依靠链接器自动生成的 `Image$$...`。
- 要用 `--bss_threshold=0` 调用，否则未初始化变量可能被当作 rwdata（只在 ARM v5 上确认过）。
- 同一区域块内的逻辑组排序固定为：先按类型（CONST、VAR、USER、SYMBOL），再按位置，最后按名字。
- **跨加载区域时顺序无法保证（TR §3.2.1.1）**：同一块 RAM 由多个加载区域装载时，scatter 语法无法保证配置的位置顺序。vLinkGen 在每个加载区域里放一对空的标记区域，后一个加载区域从 `ImageLimit(<前一个>_END)` 开始：

```text
CodeFlash_B 0x20000000 0x00400000
{
    GlobalRam_A_AD 0xFEEF8000 EMPTY 0 { }
    pos_one_data +0 { ... }
    pos_two_data +0 { ... }
    GlobalRam_A_AD_END +0 EMPTY 0 { }
}
CodeFlash_A 0x10000000 0x00400000
{
    GlobalRam_A_1_AD ImageLimit(GlobalRam_A_AD_END) EMPTY 0 { }
    pos_zero_data +0 { ... }
    pos_five_data +0 { ... }
    GlobalRam_A_1_AD_END +0 EMPTY 0 { }
}
```

  逻辑组之间的顺序会被调整，但段组在逻辑组内的顺序是保证的。

**其他编译器（摘要）**

- **Tasking**：
  - 需要 `-Wl--user-provided-initialization-code` 选项。
  - 链接器可能为了减少空隙而重排逻辑组。有两种办法保证顺序：合并逻辑组，或者拆分区域块（缺点是要预先估计各块大小）。
  - `FORCE_ZERO_OFFSET` 标志可以强制首组放在块起点。
  - 已知缺陷 TCVX-39968：使用 GROUP 时，初值的 ROM 副本顺序可能与 RAM 顺序不一致。规避办法是把受影响的变量逐个写成特殊段。
- **TI**：链接后段组顺序可能与配置不同。
- **Renesas**：只给链接段生成对齐，且最大 16 字节。
- **Green Hills**：不支持 `DEFAULTS` 区。

---

## 5. vBaseEnv 中与内存映射相关的内容

vBaseEnv User Manual 的大部分篇幅讲 vBRS（启动环境、桩模块、驱动时钟引脚等）。本章只摘取与存储布局、链接和内存初始化相关的部分。

### 5.1 vBaseEnv 的组成（UM §2、§3）

vBaseEnv 是让一颗芯片"能编译、能链接、能启动、能初始化"的模块包，固定包含：EcuC、MemMap、OS（FBL 和 HSM Updater 除外）、vBaseEnv、vBRS、vLinkGen、vSet。其中：

- **vBaseEnv 模块**：保存所有与芯片型号相关的信息，其他基础模块从这里读取。
- **vBRS**：运行时基础系统，包括启动代码、内存初始化、`main()`、EcuM/SchM 桩。
- **MemMap 模块**：从 MEMORY-SECTION 生成 MemMap 头文件，并向 vLinkGen 加入若干逻辑组（如 `MSR_VAR`、`MSR_CODE`），但这些逻辑组**默认不使用**（UM §3.7）。

### 5.2 芯片型号信息与硬件存储区（UM §3.4）

- **平台与型号**：一个"平台"是一组兼容的芯片型号（OS、编译器、启动环境相同，核架构相同），它们在核数、存储区数量和大小、外设通道数上可以不同。这些差异全部记录在 `vBaseEnvDerivativeInformation` 里。
- **被测型号（Tested Derivative）**：项目实际选用的型号，可以与订购的型号不同（例如开发时用存储更大的型号）。
- **克隆型号**：预置的型号参数是只读的。需要修改时，可以对最接近的型号右键选 "Duplicate"，复制出一份可编辑的型号，再把被测型号指向它。

每个型号下的 `vBaseEnvMemLayoutHwRegions` 列出该型号的全部存储区，每个存储区的参数如下：

| 参数 | 说明 | 必填 |
|---|---|---|
| Start Address | 起始地址 | 是 |
| Size | 大小 | 是 |
| Type | RAM / ROM / NVRAM。部分链接器（如 Tasking）需要它区分存储种类 | 否 |
| ECC Alignment | ECC 要求的对齐。清零初始化要用到，例如 8 字节对齐的 ECC RAM 需要原生 64 位写入 | 否 |
| Core Local Addressing | 该存储区只能通过核本地地址访问（例如每个核在同一地址都有自己的本地 RAM）。vLinkGen 据此在链接文件里生成 `OVERLAY` 之类的关键字，让链接器允许同一地址范围被多次使用（UM §8.5） | 否 |

核本地寻址的规则（UM §8.5）：

- **没有**开启核本地寻址的存储区之间，地址范围不能有任何重叠，部分重叠也不行。
- TI、TI LLVM、GccNxp、IAR 不支持这一功能。在这些编译器下开启时，vLinkGen 会给出警告，链接文件仍能生成，但大概率链接失败。

### 5.3 超集默认布局与可用性（UM §3.4.2、§3.6.1）

- `vBaseEnvMemLayoutHwRegions` 是整个平台的**超集列表**：只要平台里有一个型号有某个存储区，它就出现在列表里。各型号的具体地址和大小另行记录。
- vLinkGen 的默认布局也是超集，例如按平台内最多的核数配置每核的存储区域。
- 选定被测型号后，vLinkGen 自动计算每个 Memory Region 的"可用性"（Calculated Availability）和起点。**逻辑组只会被自动映射到可用的区域。**
- 配置不一致时，工具给出校验消息并附带"一键修复"（solving action），例如：
  - VLINKGEN01300：段组的初始化策略为 INIT 或 ZERO_INIT 时，必须设置执行初始化的核，修复为设置默认核 0。
  - VLINKGEN02000：区域大小必须大于 0，修复为"设为到硬件存储区末尾的剩余大小"。

### 5.4 默认区域块（UM §3.6.2）

为了在多个执行实例（典型是 Bootloader 项目）之间划分存储，vBaseEnv 预置了以下区域块：

| 区域块 | 所在区域 | 放什么 | 要点 |
|---|---|---|---|
| `StartupCode_FirstExecInst` | FLASH | 逻辑组 `Brs_Startup_Code`（`BrsHwStartup.c` 与 `Brs_PreMainStartup()`） | 只需放进第一个执行实例。在启动代码位置决定能否正确启动 / 复位的平台上（如 Infineon Aurix），由这个块保证位置正确 |
| `CoreExceptions_FirstExecInst` | FLASH | 逻辑组 `Brs_ExcVect`（核异常向量表） | 只需放进第一个执行实例。在向量表位置决定能否正确启动的平台上（如 Arm Cortex-M），由这个块保证位置正确 |
| `ApplicationEntry` | FLASH | 逻辑组 `Brs_ApplicationEntry`（函数 `Brs_ApplicationEntry()`） | 固定地址，让一个执行实例（如 Boot Manager）能跳到另一个执行实例 |
| `StartupStack_Shared` | RAM | 引导核的启动栈（逻辑组 `STACK_C0`） | 边界为 **UPPER**，总在 RAM 区域末尾；大小由平台决定，示例为 0x400；多个执行实例共用。**若是 ECC RAM，初始化阶段必须设为 EARLY**，在设置栈指针之前完成初始化 |
| `Variables_Shared` | RAM | 多个执行实例共享的全局变量，主要是 `brsMain_ResetReason` | 边界为 UPPER，紧挨在启动栈下方，默认 16 字节。若是 ECC RAM，初始化阶段同样必须设为 EARLY |

### 5.5 按 OS 核自动生成启动栈（UM §3.4.4、§4.1.3）

- 开启 "Enable core specific vLinkGen config validation" 后，vBRS 为 OS 里配置的**每一个核**（包括非 AUTOSAR 核）在 vLinkGen 中生成一个逻辑组 `STACK_Cx` 和其下的段组。后缀 `x` 取该核的物理核号。
- 这些 `STACK_Cx` 的内容类型为 `STARTUP_STACK`，**依靠内容类型自动映射**到合适的区域块。手册示例中，`STACK_C0` 的默认区域块是 `DSPR_Core0/StartupStack_Shared`。
- 启动栈参数可以按平台覆盖，默认值为：栈对齐 4、栈尾对齐 4、栈大小 1024 字节。

这是 §4.5 元数据机制的一个完整实例：**由 OS 核配置决定"有几个栈"，由内容类型决定"每个栈放在哪"**，两者都不需要手工配置。

### 5.6 启动流程与内存初始化（UM §5.1、§6.1）

```text
brsStartupEntry                         BrsHwStartup.c（通常为汇编）
 ├ coreRegisterInit / coreRegisterInit2
 ├ brsStartupZeroInitLoop               读当前核号；清零 vLinkGen_ZeroInit_Early_Blocks /
 │                                      _Early_Groups 中属于本核的项（此时还没有栈）
 ├ brsStartupStackSearch                从 vBrs_Lcfg.c 生成的 BrsMain_CoreConfig 中取本核启动栈的末端标签
 ├ stackPointerInit
 └ coreRegisterInit3 → Brs_PreMainStartup()          段 .brsMainStartup
      ├ BrsHwEarlyInitPowerOn()（可选）
      ├ BrsHwGetResetReasonStartup() → brsMain_ResetReason（段 .brsSharedVar）
      └ Brs_ApplicationEntry()                        段 .brsApplicationEntry，固定地址
           ├ BrsHwApplicationInit()（可选）、BrsHw_GetCore()
           ├ 按阶段依次执行，每个阶段：钩子 → 清零（ZeroInit）→ 复制（Init）
           │     Zero → HardReset（软件复位时跳过）→ One → Two → Three → PowerOn
           ├ BrsMain_PreMainHook()；多核时 BrsHw_UnlockCores()
           └ main() → BrsMainInit()（看门狗 / PLL / 引脚）→ Os_Init() → EcuM_Init() → StartOS()
```

要点：

- **启动代码不按名字引用任何区域**。清零和复制都遍历 vLinkGen 生成的表，启动栈从 vBRS 生成的 `BrsMain_CoreConfig` 取，并且都按当前核号过滤。
- 每个阶段前都调用 `BrsMain_Callout_Stubs.c` 里的钩子（如 `BrsMain_MemoryInit_StageHardReset_Hook()`），项目可以在其中插入操作，例如在两个阶段之间喂狗，或先初始化 PLL。
- 清零默认按 4 字节对齐写入，也支持 8 字节。所用对齐取自硬件存储区的 ECC 对齐（§5.2），由 vLinkGen 写进 `vLinkGen_MemArea.Alignment`。
- 硬件复位与软件复位的区分靠 `brsMain_ResetReason`。典型用途：应用通过软件复位跳进 Bootloader 时，用于传递信息的 RAM 区域不能被清零。

### 5.7 vBRSMemoryInit（UM §4.13）

| 设置 | 作用 |
|---|---|
| Disable Memory Init Globally | 全局关闭 `Brs_MemoryInit()`，即 ROM→RAM 复制（清零 `Brs_MemoryZeroInit()` 仍执行）。用于无 Flash 的芯片：镜像由引导程序直接拷进 RAM，此时链接器要把初值直接放在变量地址上 |
| Enable 64-Bit size of Init Pattern | 初始化填充值用 64 位 |
| Init pattern（4 项） | 硬复位清零区域、硬复位清零块、清零区域、清零块各自的填充值，默认 0。若硬件存储区 ECC 对齐为 8 字节而未开 64 位填充，4 字节填充值会自动重复成 8 字节 |

### 5.8 vLinkGen 配置要点（UM §8）

UM 第 8 章是从 TR 移过来的配置说明，对 §4 补充以下几点：

- **配置链接段的步骤**：建链接段 → 设置名字、对齐、快速寻址、文件过滤、编译器标志 → 挂到某个段组 → 段组所在的逻辑组决定区域块（UM §8.1.1、§8.1.2）。
- **整块清零**：在区域块上设置初始化阶段（`vLinkGenMemoryRegionBlockInitStage`）和执行初始化的核（`vLinkGenMemoryRegionBlockInitCore`，UM 写明是**逻辑核号**）。
- **变量初始化**：在段组上设置策略和阶段，在逻辑组上设置 ROM 副本区域块（`vLinkGenVarGroupRomRegion`）和执行初始化的核（`vLinkGenVarGroupInitCore`）。
- **RAM 代码**：在 CONST 段组上把策略设为 `COPY_TO_RAM`，在逻辑组上设置 RAM 副本区域块（`vLinkGenConstGroupRamRegion`）。
- **自定义链接符号**：`vLinkGenLogicalSymbolGroup` 下的 `vLinkGenLinkerSymbol`（名字 + 值），可以按变体启用。

### 5.9 多执行实例与默认变体（UM §3.6.3、§4.3）

- 执行实例的种类有：Application、FBL、FBL_Updater、BM、BM_FBL、HSM、HSM_Updater、FlashDriver、Hypervisor。
- vBaseEnv 预置两个变体：`vLinkGenVariant_FirstExecInst`（第一个执行实例，如 Boot Manager）和 `vLinkGenVariant_DemoAppl`（其后的普通应用）。启动代码只放在前者，共享变量和启动栈放在两者。
- 配合 `ONE_FILE_PER_VARIANT`，每个实例得到自己的链接文件和内存初始化代码，vBRS 通过 `BRS_LINKER_COMMAND_FILE_POSTFIX` 让构建自动选用对应的文件。
- FBL 需要把第二份向量表（段 `.brsExcVectRam`）复制到 RAM，在擦写 Flash 期间使用。对应段组的策略为 `COPY_TO_RAM`。

---

## 6. 与本工具的对照

| Vector（vLinkGen / vBaseEnv） | 本工具 | 对应程度 |
|---|---|---|
| 硬件存储区：地址、大小、类型 | 芯片 YAML 的 `memory_regions`（`core/hardware/memory_regions.py`），只读 | 对应。本工具另外支持"一块存储多个地址窗口"，用来区分 cache 属性 |
| 硬件存储区：ECC 对齐 | 无 | 缺 |
| 硬件存储区：核本地寻址 | `core: local` 标记核本地别名（`memory_regions.py:29`）；但重叠检查对所有重叠都提出疑点，不区分是否核本地（`memory_regions.py:209`） | 部分对应 |
| 平台超集 + 型号 + 计算可用性 | 每颗芯片一份出厂布局；芯片缺少的核对应的必需区域进 `trimmed`，可选生成占位区域（`reserve_missing_cores`） | 近似 |
| 克隆型号再编辑 | 芯片设计器与芯片修复向导 | 近似 |
| Memory Region / Region Block | 合并在执行区域的"窗口 + 起点方式（接续 / 窗口基址加偏移 / 固定地址）+ 大小"里（`config.py:60` `ExecRegion`） | 部分对应。没有"贴上边界"的起点方式 |
| Logical Group | 执行区域 `ExecRegion` | 对应 |
| Section Group | 执行区域本身（一个 ADS 执行区域就是一个输出段） | 简化。区域内不再分组，段只按名字排序 |
| Linker Section | MemMap 头文件里扫描到的输出段，由规则放置（`rules.py:77` `matches`） | 部分对应。**只能放扫描到的段，不能写属性选择器、原样选择器或文件过滤** |
| 默认区域块：启动代码 / 向量表 / 应用入口 | 无专门位置 | 缺 |
| 初始化策略 | 区域种类 code/const/data/bss/noinit/stack/reserved（`config.py:34`） | 部分对应。没有初始化阶段和执行核 |
| 初始化表 + 启动代码读表 | 无。`startup.c` 通过 `STARTUP_*` 宏按区域名引用链接符号（`symbols.py`） | 缺 |
| 启动栈：按 OS 核自动生成，按内容类型放置 | 必需区域来自扫描 `startup.c` 和 OS MPU 代码得到的"链接符号需求"，位置由出厂布局或用户决定 | 思路不同（见 §7 P2-1） |
| 内容类型 + 核号元数据 | 规则按 kind/core/cacheable/module 匹配段；**窗口靠手选**；换芯片后标为"待重新放置"（`rules.py:29`） | 缺（窗口一侧） |
| 编译器无关模型 + 按编译器生成 | `plan.py`（Plan）+ `generators/ads.py` | 对应 |
| 确定性输出顺序 | plan 按固定键排序，同样输入生成同样字节 | 对应 |
| 标签 START / END / LIMIT | ADS 依靠 `Image$$`，另生成 `<R>_LIMIT` 空区域 | 部分对应。没有 END |
| ARM 跨加载区域顺序 | `plan.py:272` 检测到向后引用只给警告，文件里仍写 `ImageLimit(<后面的区域>)` | 处理方式不同 |
| 校验 + 一键修复 | 生成前的拒绝 / 警告清单（`plan.check_plan`）；芯片修复向导 | 部分对应。内存映射侧没有一键修复 |
| 片段输出 / 用户代码组 / 变体 / 多执行实例 | 无 | 缺（优先级低） |

---

## 7. 差距与借鉴建议

优先级：**P1** 影响生成文件能否链接或启动；**P2** 模型能力，收益大；**P3** 完善项；**P4** 暂不需要。

### P1-1 编译器默认段、特殊段与固定用途区域

- **Vector 的做法**：
  - 默认段组（如 `Code_Default` 收 `.text`）接住不走 MemMap 的内容。
  - 特殊段可以写原样选择器，带 `OVERALIGN`、`KEEP`。
  - 链接段可以按目标文件或库过滤。
  - vBaseEnv 为启动代码、向量表、应用入口各预置一个区域块，并说明在部分平台上它们的位置决定能否正确启动（§5.4）。
- **本工具现状**：
  - `generators/ads.py:53` 只为扫描到的段写 `*(.name)`。不走 MemMap 的代码、C 库、`InRoot$$Sections`、向量表、启动代码，在生成的文件里都没有位置。
  - 导入时已能识别 `*(+BSS)` 这类属性选择器（`scatter.py:30`），但生成器写不出来。
- **建议**：
  - 执行区域增加三类额外选择器：属性选择器（`+RO`、`+RW`、`+ZI` 等，作为兜底）、原样选择器（如 `*(InRoot$$Sections)`、`*(RESET, +FIRST)`、`.ANY`）、文件过滤（如 `startup.o(+RO)`），并纳入 plan 和自检。
  - 出厂布局为向量表和启动代码预置固定用途区域，作为必需区域。
- **注意**：本工具尚未做过真实链接，armlink 对没有归宿的段是报错还是放到意外的位置还没有验证，需要用一次真实链接确认。

### P1-2 ARM 跨加载区域的顺序

- **Vector 的做法**：明确接受"跨加载区域时顺序会被调整"，用空的标记区域加 `ImageLimit(<前一个>_END)` 接续，不写向后引用。
- **本工具现状**：同一窗口内的区域按 `order` 串成一条链，不管属于哪个加载区域。如果前一个区域在后面的加载区域里，就会写出向后引用，只给一条警告。
- **建议**：plan 在每个窗口内**先按加载区域顺序、再按 `order`** 排序，保证只引用前面已出现的区域。配置顺序被调整时，在生成前的清单里明确列出。

### P2-1 "内容类型 + 核号"自动选窗口，配合"超集布局 + 可用性"

- **Vector 的做法**：
  - 逻辑组标注内容类型和核号；区域块声明可接收的内容类型；工具结合芯片型号上的可用性自动选块。标注了就自动，删掉标注就手动。
  - 默认布局按平台超集准备，按被测型号计算可用性。
  - `STACK_Cx` 按 OS 核数自动生成、按 `STARTUP_STACK` 类型自动放置（§5.5）。
- **本工具现状**：窗口由用户手选；换芯片后窗口对不上，标记为"待重新放置"（`AGAIN_KEY`），需要逐个处理；缺核用 `trimmed` 加占位区域处理。
- **建议**：
  - 芯片 YAML 的 `memory_regions` 增加"可接收的内容类型"，作为出厂数据。信息不全时按约定标"待确认"，不删除。
  - 执行区域可选标注内容类型和核号。有标注的自动解析窗口；没有标注的保持现在的手选。
  - "每核一份"的区域（栈、核本地数据）按芯片核数展开，取代此前设想的"按核模板区域"。
  - 本工具的必需区域来自扫描到的链接符号需求，比 vBRS 按 OS 核生成更贴近实际代码，这一点保持不变；新机制只负责"放在哪"，不改变"需要哪些"。

### P2-2 初始化表，以及启动代码与区域名解耦

- **Vector 的做法**：
  - 从配置生成复制表、清零表和 ECC 整块清零表，每项带执行核和初始化阶段。
  - 启动代码只遍历这些表，按当前核过滤；启动栈也从生成的表取（§5.6）。
  - EARLY 阶段在设置栈指针之前完成，供 ECC RAM 上的启动栈使用。
  - 每个阶段前提供钩子；可以全局关闭复制（用于无 Flash 芯片）；填充值可配置。
- **本工具现状**：`startup.c` 是手写的，用 `STARTUP_GETCOPYDATAINFO(<区域名>, …)` 等宏按名字引用区域。所以才需要"必需区域不能改名"的限制和"链接符号缺失"检查。
- **建议**：
  - 作为**可选**输出，从 plan 生成一份初始化表 C 文件，字段参照 §4.4。
  - 初始化阶段至少支持一个默认阶段、`EARLY` 和 `POWER_ON`；每项带执行核。
  - 如果同时提供"每核启动栈表"，启动代码就可以完全不按名字引用区域。
- **前提**：要决定 `startup.c` 是否改为读表；对 ARM 来说还意味着不再使用 `__scatterload` 复制表（TR：链接器自带复制表不能与 vLinkGen 同时使用）。这是架构决策，需要先确认。

### P3-1 芯片存储数据：ECC 对齐与核本地寻址

- **Vector 的做法**：
  - 硬件存储区带可选的 ECC 对齐，供清零时选择写入宽度。
  - 核本地寻址标记让链接文件生成 `OVERLAY` 一类关键字；没有该标记的存储区之间不得重叠（§5.2）。
- **本工具现状**：`memory_regions` 没有 ECC 对齐；`core: local` 已有，但重叠检查对所有重叠一视同仁。
- **建议**：
  - 增加可选字段 `ecc_align`，数据来源不明时标"待确认"。只有做 P2-2 时才真正用到它。
  - 细化重叠检查：核本地窗口之间允许重叠；非核本地窗口重叠才提出疑点。这正好可以用来解决 THA6206 的 CPUX 本地 TCM 别名与各核 AXI 窗口的归属问题（芯片存储编辑器任务 6.2）。
  - 核本地区域在 armlink 中如何表达（`OVERLAY` 属性或其他方式）尚未验证，等需要生成时再定。

### P3-2 END 标签与自定义链接符号

- **Vector 的做法**：`_END` 等于起点 + 大小 − 1，用于 MPU 的结束地址；另可配置与编译器无关的自定义链接符号。
- **建议**：将来做 GHS/GCC 生成器时，在 `symbols.py` 的按编译器符号表里统一提供 START、END、LIMIT。ARM 侧继续使用 `Image$$...$$Limit` 和 `<R>_LIMIT` 空区域，需要 END 的地方由使用方减 1。

### P3-3 片段输出与用户代码组

- **片段输出**：给已有手写主脚本的集成方使用（例如只生成 MCAL/SDK 部分，让主脚本 include）。这正好回答了此前"替换 OS 自带的 scatter，还是只生成一部分"的问题。
- **用户代码组（PRE / GROUP_LIST / POST）**：作为模型表达不了时的逃生口。代价是它的内容对自检不透明，自检只能原样核对文本。

### P3-4 贴上边界的起点方式

- **Vector 的做法**：Region Block 可以贴 Memory Region 的上边界。vBaseEnv 的启动栈和共享变量都这样放（§5.4）。
- **建议**：起点方式增加"从窗口末尾往下"，适合栈等从顶部放置的区域。

### P3-5 校验附带一键修复

- **Vector 的做法**：校验消息附带可执行的修复，例如"大小设为到存储区末尾的剩余大小"（§5.3）。
- **建议**：内存映射工作台的部分警告（如区域没有大小、执行核未设）可以附带建议修复，由用户确认后执行，不自动修改。

### P4 变体与多执行实例

一份配置生成多份不同布局的脚本（Boot Manager + 应用、FBL 等），并支持按变体覆盖窗口。目前只有 THA6206 一种布局、一个执行实例，暂不需要。

### 附：非 Vector 来源的设想（仅作记录）

以下两点在两份文档中都**没有出处**，是本工具自己的想法：

- 对给 OS MPU 用的区域，按芯片 MPU 粒度（R52 的 base/limit 按 64 字节对齐）检查起点和大小；
- 规则增加 `asil` 匹配条件（段名中已含 `asil_d` 等信息）。

---

## 8. 待确认问题

1. `startup.c` 是否愿意改为读取生成的初始化表和每核启动栈表？这决定 P2-2 是否实施，以及是否放弃 `__scatterload`。
2. R52 的 TCM 等带 ECC 的存储，现在的启动代码是否在首次访问前整块写零？启动栈所在的 RAM 是否需要在设置栈指针之前初始化（对应 Vector 的 EARLY 阶段）？这一点尚未核实。
3. 当前生成的 `scatter.scat` 是否做过一次真实链接？P1-1 中"没有归宿的段"的实际后果需要以真实链接为准。
4. 向量表和启动代码在 THA6206 上是否必须放在固定地址？这决定 P1-1 中固定用途区域的出厂默认值。
5. 文档之间的不一致，实施时需要自行决定：
   - TR §4.1 说初始化表里的 `Core` 是**物理**核号，UM §8.2 说配置的执行核是**逻辑**核号。
   - TR 表 2-4 说 `POWER_ON` 在热启动时不执行，UM §6.1.3 说默认实现总会执行，需要项目自己补条件。

---

## 9. 对网上流传说法的勘误

此前参考过一段介绍 vLinkGen 的文字，与两份 Vector 文档对照后：

| 说法 | 文档中的情况 |
|---|---|
| 映射分四层（物理区域 → 逻辑组 → 段组 → 软件段） | 实际为六层：硬件存储区 → Memory Region → Region Block → Logical Group → Section Group → Linker Section |
| 硬件区域定义在 `MemLayoutHwRegions` 容器 | 基本属实：容器为 vBaseEnv 的 `vBaseEnvMemLayoutHwRegions`，每项为 `vBaseEnvMemLayoutHwRegion`，按芯片型号分别记录 |
| MemMap 通过 `MemMapLinkerLogicalGroupRef` 指向逻辑组 | 两份文档都未提及该参数。UM §3.7 只说 MemMap 模块会向 vLinkGen 加入 `MSR_VAR`、`MSR_CODE` 等逻辑组，且默认不使用 |
| 支持 `Core Local` / `OVERLAY` 映射 | 部分属实：这是**硬件存储区**的属性 `vBaseEnvHwRegionCoreLocalAddressing`，开启后 vLinkGen 生成 `OVERLAY` 一类关键字（UM §8.5），不是逻辑组上的映射方式；与核有关的另有逻辑组核号元数据和初始化表的执行核 |
| 按 OS-Application 生成满足 MPU 粒度的段组 | 两份文档都未提及；只提供 `_END` 标签供 MPU 使用，并提醒逻辑组标签不保证连续 |
| 自动生成 ROM→RAM 复制表 | 属实，见 §4.4；另有 ECC 整块清零和初始化阶段，由 vBRS 启动代码读表执行（§5.6） |

---

## 10. 参考

- Vector Informatik GmbH，*MICROSAR Classic vLinkGen Technical Reference*，Version 2.11.0，2025。
- Vector Informatik GmbH，*vBaseEnv User Manual*，Version 2.30.0，2025。
- 本工具源码：`autosar_configurator/core/memmap/config.py`、`rules.py`、`plan.py`、`symbols.py`、`scatter.py`、`generators/ads.py`，以及 `autosar_configurator/core/hardware/memory_regions.py`。
