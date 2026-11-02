## Why

`add-memory-map-workbench` 之后，工具能读、能查、能看，但不能**配**。用户看到"`.mcal_bss_asil_d_unspecified_core0` 落进了 GMU_NORMAL，应该在 CPU0 的 BTCM"之后，只能去改链接文件。目标是在工具里把代码里的所有段，配置到芯片的物理存储里，配好后交给生成器（下一个变更）出链接文件。

你确认的界面构想：左边是扫描得到的段，右边是按工程芯片列出的物理存储（跟随工程设置），用拖拽或 `+`/`−` 把段配到右边。按规则自动归入，允许手动修改。

我在审查时指出了原构想缺的一层，你同意了：**段不是直接放进物理存储的，中间还有执行区域**。厂商脚本里 CPU0 的 BTCM 被切成 `PRIVATE_CODE_CORE0`、`PRIVATE_DATA_CORE0`、`PRIVATE_BSS_CORE0`、`PRIVATE_NO_INIT_CORE0` 和七个栈区域，它们有顺序、对齐，而且名字是 `startup.c` 写死的：

```
STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE0, …)      startup.c:413
STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE0, …)        startup.c:416
STARTUP_GETIMAGEBASEADDR(CORE0_USER_STACK, …)       startup.c:759
```

没有这一层，生成链接文件时就没有地方决定"必须产出哪些区域名、DATA 和 BSS 怎么分开、顺序怎么排"。

本变更做**布局配置**：数据模型、默认规则、手动修改、切芯片的处理，以及配置界面。**不生成链接文件**（下一个变更）。

**范围按你的决定限定为 THA6206**：默认规则和必需区域的清单只来自 THA6206 的厂商脚本。其他芯片先没有默认规则，界面能打开，但所有段显示"未放置"，用户手动配或自己写规则。

## What Changes

- **三层数据模型**（见 `design.md`）：
  - 段：扫描结果，只读；
  - 执行区域：属于布局配置；名称、所在物理存储及窗口、顺序、种类（代码、常量、数据、BSS、未初始化、栈）、对齐；
  - 物理存储：来自芯片 `memory_regions`（`add-chip-memory-editor` 提供分组），只读。
- **必需执行区域**：从"链接符号需求"（`add-link-symbol-needs` 已实现）里读出，加上 THA6206 默认布局里出现的区域。必需区域不能删除和改名，用户可以决定它放在哪个物理存储、里面放哪些段；它们的 `<名>_LIMIT` 界限区域不在界面上出现，生成时自动产出。必需区域按芯片核数裁剪（`startup.c` 里有 CORE2、CORE3 的区域，THA6206 只有 2 个核）：**裁剪只针对配置界面**，让用户看不到不存在的核的区域；这些区域仍然被代码引用，所以生成链接文件时由生成器自动补成空的"保留区域"（见 `add-linker-file-generation` 的设计），它们不进配置、用户不能往里放段。
- **放置规则**，按优先级，第一条匹配的生效：
  1. 手动放置（例外）；
  2. 用户规则（按段名通配、核心、种类、可缓存性匹配，指向一个执行区域）；
  3. 默认规则（THA6206，来自厂商 `LinkerAdsPf.scat`）：
     - `_core<n>` 的 DATA/BSS → 核 n 的私有数据/BSS 区域；
     - `_uncached` → 全局不可缓存区域；`_lmu<n>` → LMU n 的区域；
     - TEXT/RODATA → PFLASH 里的代码/常量区域；
     - 其余 DATA/BSS → `UNDEFINE_RAM_DATA`/`UNDEFINE_RAM_BSS`。
- **配置界面**（并入"内存映射"工作台，新增"配置"页签，在"诊断""布局"之后）：
  - 左：段列表，每个段带状态——规则放置、手动放置、未放置、待重新放置，可按模块、核心、种类、状态过滤；
  - 右：物理存储 → 窗口 → 执行区域的树，必需区域带标记；
  - 拖拽、"+""−"按钮、多选批量，都是同一个操作；手动操作产生例外，规则放置的段被手动移走后变成"手动"；
  - "规则…"打开规则编辑器（列表、顺序、增删）；
  - 每次改动后立即重跑检查，诊断页签里的结果同步更新。
- **配置的保存**：存在工程目录下集成工程的 `memorymap.json`（见 `design.md` 的目录决定），文本格式，便于版本管理；路径随工程保存，旧工程没有它时为空配置。
- **切芯片**：沿用现有的芯片变更预览，预览里增加"内存布局"一节；切换后保留在新芯片里仍然存在且属性兼容的放置，对不上的标"待重新放置"，不删除、不静默改；必需区域按新芯片的链接符号需求重新读，新增的补上，消失的标"不再需要"但保留。
- **检查沿用**：配置不改变检查器本身。生成链接文件之后（下一个变更），用现有检查器验证结果。

## Impact

- Affected specs：`memory-layout-config`（新增）；`project-chip-selection`（修改：芯片变更预览增加内存布局一节）
- Affected code：
  - 新增 `core/memmap/config.py`：布局配置的数据模型与读写
  - 新增 `core/memmap/rules.py`：默认规则、用户规则、匹配与冲突处理
  - 新增 `core/memmap/regions.py`：必需执行区域的来源与按核数裁剪
  - 新增 `ui/dialogs/memory_map_config_tab.py`，并接入 `memory_map_workbench.py`
  - `core/workspace_manager.py`：保存和读取布局配置的路径；切芯片预览接入
  - 新增默认规则的数据文件 `autosar_configurator/data/memmap/THA6206_default.json`
- **兼容性**：只读检查和布局视图不变；旧工程没有布局配置，行为与现在一致；配置只在用户保存时才写文件。
- **依赖**：`add-chip-memory-editor`（物理存储分组，THA6206 的数据补充）、`add-link-symbol-needs`（必需区域）。
- **不在本变更范围内**：生成链接文件（下一个变更 `add-linker-file-generation`）；容量检查（没有 `.map` 文件，段的大小不可知；数据模型里给执行区域预留可选的"实际大小"字段，不填）；THA610X 和 THA6412 的默认规则；OS 自带 `scatter.scat` 的处理（保留，不管它）。
