## Why

目标是让本工具具备系统级 Memory Map 能力：MCAL、SDK、OS、应用用到的内存段，都能映射到输出段、放进正确的物理区域，并且能适配不同编译器。整体路线见 `design.md`，本变更只做第一步：**只读的一致性检查**。

现状（都已在文件里核对）：

- **段的声明分散在静态源码和生成代码里。**
  - MCAL 驱动 `Mcal/Code/` 共 81 个文件、610 次 `#include "<Msn>_MemMap.h"`。
  - SDK 共 138 个文件。
  - 插件模板只出现在 `*_PBcfg.c/h` 中（36 个文件，只有 `CONFIG_DATA` 段，以及 Dma、Spi 的部分 `VAR` 段），段名里的核心号在生成时才填入，例如 `CORE[!"$CoreIndex"!]`。
- **段名映射是厂商的 48 个静态头文件**（`CommonFile/Memmap/<Msn>_MemMap.h`，标注 "sample code only"），用 `MEMMAP_START_TEXT/RODATA/DATA/BSS(".输出段名")` 写成。OS 的 `Os_memmap.h` 则由 OS 配置（`OsMemoryMap`、`MemorySection`、`MemoryBlock`）生成。
- **物理布局只有 OS 在生成**：OS 模板 `scatter.scat`（ADS），读取 OS 配置里的 `MemoryRegion`、`MemoryBlock` 和 `MemorySection`。但它只为 OS 自己的段生成选择器，**MCAL 的 `.mcal_*` 段一个都没有放**。T1 工程（THA6206）生成的 `scatter.scat` 里 `.mcal_` 出现 0 次。
- 后果：例如 Can 驱动的 `CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED`，经 `Can_MemMap.h` 映射为 `.mcal_bss_asil_d_unspecified_core0`，在 T1 的分散加载文件里只能被 `UNDEFINE_RAM_BSS` 的 `*(+BSS)` 通配吸收，落进 `GMU_NORMAL`（全局、可缓存内存），而不是 CPU0 的 TCM。`*_uncached` 段同理会落进可缓存区域。这类问题现在只能在板子上出现异常后才被发现。
- 段名映射和链接脚本对不上时，只有编译时 `#error "MemMap.h, no valid matching start-stop section defined."`，或者链接后的布局错误才会暴露；生成阶段完全不检查。

## What Changes

- **新增只读的"内存映射检查"**，不修改任何配置或文件：
  1. **收集段的使用**：扫描用户添加的源码目录（MCAL、SDK、OS 内核、应用）和工程的生成输出目录，找出 `#define <X>_START_SEC_<Y>` 和 `<X>_STOP_SEC_<Y>`，并检查写法：START/STOP 配对、嵌套层级一致、define 之后紧跟 `#include` MemMap 头。含 `[!...!]` 的模板文件不扫描，以生成结果为准。
  2. **读取段名映射**：解析用户指定目录下的 MemMap 头文件（厂商静态头、OS 生成的 `Os_memmap.h`），得到"段名 → 种类（TEXT/RODATA/DATA/BSS）+ 输出段名"。
  3. **读取物理布局**：解析一个 ADS 分散加载文件（`.scat`），得到每个执行区域的基址（解析 `#define`，以及 `AlignExpr(ImageLimit(X))` 这类相对基址）、显式选择器 `*(.name)`，以及通配选择器 `+RO-CODE`、`+RO-DATA`、`+RW-DATA`、`+BSS`、`+ZI`、`.ANY`。
  4. **报告**：
     - 用到但没有映射的段（编译会报 `#error`）；
     - 映射出的输出段没有被显式放置、只会落进某个通配区域的（报出落在哪个区域）；
     - 完全没有区域接收的段；
     - 属性冲突：`COREn` 的段落在不属于核心 n 的区域；`NO_CACHEABLE` / `_uncached` 的段落在可缓存区域。
     结果按类别、文件、行排序，可导出 Markdown 清单。
- **芯片数据新增 `memory_regions`**（名称、起始地址、长度、类型 flash/ram、所属核心、是否可缓存）。本变更只补 THA6206，数据从厂商链接脚本的 MEMORY 注释表提取，全部标记"待确认"，确认后才视为可信。属性冲突检查按执行区域基址落在哪个芯片区域来判断；芯片没有 `memory_regions` 时，跳过这一项并在结果里说明。
- **检查设置随工程保存**：源码目录、MemMap 头目录、链接文件路径，都以相对工程目录的 POSIX 路径保存。
- **界面**：新增"检查内存映射"对话框，做法参照现有的"芯片依赖扫描"对话框（后台执行、可取消、导出清单）。

## Impact

- Affected specs：`memory-map-check`（新增）；`chip-library`（芯片数据新增可选的 `memory_regions`）
- Affected code：
  - 新增 `core/memmap/`：段扫描、MemMap 头解析、ADS 分散加载文件解析、检查
  - `core/workspace_manager.py`：保存和读取检查设置
  - `core/hardware/`：芯片 YAML 读写 `memory_regions`（可选字段，旧文件不受影响）
  - `autosar_configurator/data/chips/THA6206_LFBGA292.yaml`：新增 `memory_regions`，标记待确认
  - 新增 `ui/dialogs/memory_map_check_dialog.py`，并在主窗口挂菜单项
- **兼容性**：只读，不改变生成结果；旧工程和旧芯片文件照常加载。
- **不在本变更范围内**（见 `design.md` 的路线）：生成 `<Msn>_MemMap.h`；集成者层面的系统内存布局配置及其生成的放置规则；ADS 以外编译器的链接文件解析；启动初始化表（拷贝和清零）检查；按 map 文件检查容量；芯片定义设计器编辑 `memory_regions`。
