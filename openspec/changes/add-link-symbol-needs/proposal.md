## Why

`add-memory-layout-view` 能看到段放在哪，但链接文件还要满足另一类要求：厂商 `startup.c` 和 OS 生成的代码，会按**固定的区域名**引用链接器符号。链接文件里少了某个名字，要到链接时才报"符号未定义"，甚至更糟——名字存在但区域不对，板上才暴露。

整体路线是"从代码收集 → 与芯片内存匹配 → 按编译器生成链接文件"（见 `add-memory-layout-view` 的 `design.md`）。生成链接文件时必须产出这些区域名，所以第一步是把它们从代码里读出来。本变更只做这一步：**读取链接符号需求，并在检查和视图里报告链接文件缺哪些**，不生成任何文件。

现状（读文件核实，未运行）：

- **厂商 `startup.c`** 用宏按区域名取符号，区域名是宏的第一个参数：
  - `STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, …)`：要区域的基址、界限、加载地址；
  - `STARTUP_GETBSSDATAINFO(UNDEFINE_RAM_BSS, …)`：要区域的基址和清零界限；
  - `STARTUP_GETIMAGEBASEADDR`、`STARTUP_GETIMAGELIMITADDR`、`STARTUP_GETIMAGEBSSLIMITADDR`、`STARTUP_GETLOADBASEADDR`；
  - `STARTUP_SETSTACK(MODE_SYS, CORE0_USER_STACK)`、`STARTUP_SETHYPMODESP(CORE0_HYP_STACK)`：要栈区域的界限。
- **宏如何变成链接器符号，随编译器而异**（`startup_ads.h` 与 `startup_ghs.h` 各一套）：

  | 用途 | ADS（armlink） | GHS |
  |---|---|---|
  | 区域基址 | `Image$$<名>$$Base` | `__<名>_ADDRESS_START` |
  | 复制类区域的界限 | `Image$$<名>_LIMIT$$Base` | `__<名>_ADDRESS_END` |
  | 清零类区域的界限 | `Image$$<名>_LIMIT$$ZI$$Base` | `__<名>_ADDRESS_END` |
  | 加载地址 | `Load$$<名>$$Base` | `__<名>_LOAD_ADDRESS_START` |
  | 栈顶 | `Image$$<名>$$ZI$$Limit` | `__<名>_ADDRESS_END` |

  这解释了为什么厂商脚本和 OS 模板里到处有 `<块名>_LIMIT` 这类空区域：它们是 ADS 下"界限"符号的来源。
- **OS 生成的代码**：`Os_link_Lcfg.c` 模板声明 `extern uint32 Image$$<块名>$$Base`、`Image$$<块名>_LIMIT$$Base`、`Load$$<块名>$$Base`，块名来自 OS 内存配置的 `MemoryBlock`，还有写死的 `CORE0_USER_STACK` 等 14 个栈区域。
- **现在没有任何检查**覆盖这一类：`add-memory-map-check` 只看段的放置，`add-memory-layout-view` 只展示放置。

## What Changes

- **新增"链接符号需求"的读取**，只读，来源有两类：
  1. **宏引用**：在用户添加的源码目录和生成输出目录里，找 `STARTUP_GETCOPYDATAINFO`、`STARTUP_GETBSSDATAINFO`、`STARTUP_GETIMAGEBASEADDR`、`STARTUP_GETIMAGELIMITADDR`、`STARTUP_GETIMAGEBSSLIMITADDR`、`STARTUP_GETLOADBASEADDR`、`STARTUP_SETSTACK`、`STARTUP_SETHYPMODESP` 的调用，取出区域名和用途（复制类、清零类、栈、基址、界限、加载地址），记录文件和行。
  2. **直接引用**：找 ADS 符号 `Image$$<名>$$Base`、`Image$$<名>_LIMIT$$Base`、`Image$$<名>$$ZI$$Limit`、`Load$$<名>$$Base`、`Load$$<名>$$Limit`（OS 生成的 `Os_link_Lcfg.c`、`Os_mpu_Lcfg.c` 等），和 GHS 符号 `__<名>_ADDRESS_START`、`__<名>_ADDRESS_END`、`__<名>_LOAD_ADDRESS_START`，取出区域名和用途。
  - 含 `[!...!]` 的模板文件不扫描，以生成结果为准（与段扫描一致）。
  - 不同写法得到同一种结构：区域名、用途集合、来源（文件、行）。
- **对照链接文件报告**：用已有的 ADS `.scat` 解析结果，检查每个被引用的区域名：
  - 链接文件里没有这个执行区域 → 报"链接文件缺少区域"，写明谁引用了它、用途；
  - 需要 `<名>_LIMIT` 的区域，链接文件里没有 `<名>_LIMIT` 空区域 → 报"缺少界限区域"（ADS 下界限符号来自它）；
  - 链接文件里有、但没有任何代码引用的区域 → 不报告，只在视图里标"无代码引用"，因为链接文件可以有自己需要的区域。
- **视图和导出**：
  - 检查新增类别"链接符号缺失"，沿用现有的分类、过滤和 Markdown 导出；
  - "内存布局"视图里，执行区域上标出"被谁引用、用途"，被引用但链接文件里没有的区域单列一组；
  - 非 ADS 链接文件仍按"目前只支持 ADS"处理，但**GHS 符号的引用仍然读取并显示**（读取不依赖链接文件格式），只是无法对照。
- **编译器符号约定放进一张表**（`core/memmap/symbols.py`），上表的映射写在代码里，供后续"按编译器生成"复用，不另维护。

## Impact

- Affected specs：`link-symbol-needs`（新增）
- Affected code：
  - 新增 `core/memmap/symbols.py`：宏与符号的识别、编译器符号约定表、区域需求的合并
  - `core/memmap/check.py`：扫描时收集需求；对照链接文件，新增类别"链接符号缺失"；`CheckResult` 新增 `needs`
  - `core/memmap/layout.py`、`ui/dialogs/memory_layout_dialog.py`：在执行区域上显示引用信息，单列缺失的区域
  - `ui/dialogs/memory_map_check_dialog.py`：新类别由现有的分类显示自动带出，不改
- **兼容性**：只读，不改变生成结果；`CheckResult` 只新增字段；没有任何引用的工程不受影响。
- **依赖**：`add-memory-map-check`（已实现）和 `add-memory-layout-view`（已实现，未提交）。
- **不在本变更范围内**：生成链接文件；GHS `.ld` 的解析和对照；`Os_link_Lcfg.c` 的初始化表与 OS 内存配置是否一致；判断区域放进哪块物理内存是否合适（那是 `add-memory-map-check` 的放置检查）；把需求变成布局配置的默认值。
