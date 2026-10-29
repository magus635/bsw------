## Context

系统级 Memory Map 要打通四件事，任何一处改了，其他几处都要跟着变：

| 环节 | 内容 | 现在 |
|---|---|---|
| ① 段的使用 | 各模块代码里 `<X>_START_SEC_<Y>` 声明的段 | MCAL/SDK 写死在静态源码里；生成代码里只有配置数据段 |
| ② 段名映射 | 段名 → 输出段名，即 `<Msn>_MemMap.h` | 厂商 48 个静态头；OS 由配置生成 `Os_memmap.h` |
| ③ 物理布局 | 输出段 → 执行区域 → 物理地址，即链接文件 | 只有 OS 模板生成 ADS `scatter.scat`，只放 OS 的段 |
| ④ 启动初始化 | 哪些区域从 Flash 拷贝、哪些清零 | 厂商 `startup.c` 按固定区域名处理；OS 的 `Os_link_Lcfg.c` 由配置生成分阶段的拷贝和清零表 |

已有可用的部件：

- **OS 的内存模型**（`Os.xdm`）已经是一个小型的布局配置：
  - `MemoryRegion`：起止地址、RAM/FLASH、拷贝方式；
  - `MemoryBlock`：大小、对齐、类型 `BSS/NON_INIT/VARIABLE/RO_DATA/RO_CODE`、所在区域、拷贝阶段；
  - `MemorySection`：对齐、是否排在最前；
  - `OsMemoryMap`：OS 段名 → `MemorySection`；
  - 以及各核心的栈。

  由这一份配置生成 `Os_memmap.h`、`scatter.scat`、`Os_link_Lcfg.c`（初始化表）和 `Os_mpu_Lcfg.c`。
- 局限：
  - `scatter.scat` 模板只支持 `Os_THA6206` 和 `Os_THA610X`；
  - 只支持 ADS；
  - 核心相关的字段写死为 Core0/Core1（`MemoryRegionCopy`、各栈的 `Core0/Core1...`）；
  - 不支持 THA6412 的 4 个核心。
- **编译器差异已有一半被厂商抽象**：
  - `CommonFile/include/Compiler.h` 把 `MEMMAP_START_*(".name")` 按 ARMCC/ADS、GHS、IAR、HighTec、Tasking 展开成各自的 pragma；
  - `startup_<编译器>.h` 用 `STARTUP_GETCOPYDATAINFO` 和 `STARTUP_GETBSSDATAINFO` 隐藏了不同链接器的符号命名。

## Goals / Non-Goals（本变更）

- Goals：在不改任何交付物的前提下，把 ①②③ 的不一致和放错区域的问题，在生成阶段就报出来，第一个目标是 T1（THA6206 + ADS）。
- Non-Goals：生成任何文件；修改 OS 配置；支持 ADS 以外的链接文件；检查启动初始化和容量。

## Decisions

### D1 放置归集成者，OS 只是参与方之一（后续阶段）

物理布局由集成者决定。OS 和 MCAL、SDK、应用一样，是提供段的一方，它的内存配置集成者也可以调整，不由 OS 配置者单独锁定。所以 OS 的 `MemoryRegion`/`MemoryBlock`/`MemorySection` 不作为放置的唯一来源；它的模型（区域、块、拷贝阶段）可以作为集成者布局配置的参考。

集成者布局配置的具体形式，以及它与 OS 内存配置如何保持一致（谁生成链接文件、OS 配置是否从中派生），留给第 2 阶段的提案决定。

本变更的检查不依赖这一点：它读取的是最终的链接文件，对 OS 的段和 MCAL 的段一视同仁。所以无论链接文件由谁生成，检查都适用。

### D2 沿用厂商的输出段名

例如 `.mcal_bss_asil_d_unspecified_core0`。这样厂商的 48 个头文件和 `startup.c` 都不用改。只有将来用户要偏离默认映射时，才需要生成 `<Msn>_MemMap.h`。

### D3 段的属性从名称中解析，规则保持简单

- 种类以 MemMap 头里的宏为准：`MEMMAP_START_TEXT/RODATA/DATA/BSS`。
- 核心号取段名里的 `_CORE<n>_`，或输出段名里的 `_core<n>`。
- 不可缓存取段名里的 `NO_CACHEABLE`，或输出段名里的 `_uncached`。
- 不解析 ASIL 和宽度，它们不影响这次的检查。

### D4 区域属性来自芯片数据，按地址判断

执行区域的基址落在芯片 `memory_regions` 的哪一段，就认为它在哪个区域，由此得到所属核心和是否可缓存。不按区域名称猜测，因为 OS 配置里的名称由用户自定。

- 相对基址的处理：`AlignExpr(ImageLimit(X), n)` 和直接写成 `X` 的，都视为与执行区域 X 在同一芯片区域。
- 数据可信度：芯片数据标记为"待确认"时，结果里注明这一点。

### D5 通配选择器的归属

- 规则：一个输出段没有被任何 `*(.name)` 显式选中时，按种类找能接收它的通配选择器：
  - TEXT → `+RO-CODE` 或 `+RO`
  - RODATA → `+RO-DATA` 或 `+RO`
  - DATA → `+RW-DATA` 或 `+RW`
  - BSS → `+BSS` 或 `+ZI`
  - 都找不到时 → `.ANY`
- 报告方式：报告为"未显式放置"，并给出它会落在哪个执行区域。
- 局限：链接器实际的选择优先级比这复杂，所以这只是检查提示，不保证与链接结果完全一致。

### D6 编译器适配的位置

| 差异点 | 适配方式 |
|---|---|
| 段的 pragma | 由 `Compiler.h` 的 `MEMMAP_START_*` 负责，工具不感知 |
| 链接文件语法 | 每种编译器一个解析器（本变更只做 ADS `.scat`）；生成时每种编译器一套模板（后续阶段） |
| 链接器符号 | 用于初始化表，后续阶段按编译器配置 |

解析结果统一转成同一种结构（执行区域：名称、基址、选择器列表）。所以检查逻辑与编译器无关，新增一种编译器只需要再加一个解析器。

## 路线（后续各自提案）

1. **本变更**：只读一致性检查（ADS + THA6206）。
2. **集成者的系统内存布局配置**：
   - 覆盖 OS、MCAL、SDK、应用的全部输出段，集成者可以调整其中任何一方（包括 OS）的放置。
   - 默认规则：`COREn` 进 CPUn BTCM；`uncached` 进 device 区域；CODE、CONST 进 PFLASH。
   - 需要决定与 OS 内存配置的关系，避免两处各说各话。
   - 以厂商链接脚本 `LinkFiles/Ads/LinkerAdsPf*.scat` 作为标准答案，对照验证。
   - 生成后，本变更的检查应当没有"未显式放置"一类的问题。
3. **OS 内存模型扩展**到 4 核和 THA6412，需要先改插件 `Os.xdm` 和模板。
4. **启动初始化检查**：区域的拷贝和清零与 `Os_link_Lcfg`、`startup.c` 是否一致。
5. **其他编译器**（GHS、HighTec、IAR、Tasking）的链接文件解析和生成模板；需要偏离默认映射时，生成 `<Msn>_MemMap.h`。
6. **按 map 文件检查容量**。

## Risks / Trade-offs

- 只扫描用户添加的目录：漏加目录就会漏报"用到但没映射"。所以结果里列出扫描了哪些目录、多少个文件。
- 条件编译：`#if` 分支里的段（例如按编译器或核心数选择的）一律当作用到，可能多报。这类报告标为"可能"，不当作错误。
- 芯片区域数据从注释表提取，可能有误，所以标记"待确认"。这符合"芯片数据缺失时只提示，不删除"的约定。
