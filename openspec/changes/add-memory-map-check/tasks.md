## 1. 段的使用

- [ ] 1.1 扫描源码目录和生成输出目录中的 `.c/.h`，跳过含 `[!` 的文件；找出 `#define <X>_START_SEC_<Y>` 和 `<X>_STOP_SEC_<Y>`，记录文件和行号
- [ ] 1.2 写法检查：START/STOP 配对（同一文件内按顺序）、`#if` 嵌套层级一致、define 之后的下一条预处理指令是 `#include` MemMap 头；`#if` 分支中的段标为"可能"
- [ ] 1.3 用 `Mcal/Code/Can` 和 T1 生成的 `Can_PBcfg.c` 做测试数据

## 2. 段名映射

- [ ] 2.1 解析 MemMap 头：`#if/#elif defined <X>_START_SEC_<Y>` 后跟 `MEMMAP_START_(TEXT|RODATA|DATA|BSS)("<输出段>")`，得到段名 → 种类 + 输出段；重复定义的段要报告
- [ ] 2.2 用厂商 `Can_MemMap.h` 和 T1 生成的 `Os_memmap.h` 做测试

## 3. ADS 分散加载文件

- [ ] 3.1 解析 `#define 名 值`、加载区域、执行区域（名称、基址表达式、属性），以及选择器 `*(.name[,…])`、`*(+RO-CODE)` 这类通配和 `.ANY`；忽略 `;` 注释和 `#!` 首行
- [ ] 3.2 基址：数值、`#define` 名、`AlignExpr(ImageLimit(X), n)`、`ImageLimit(X)`、直接写成 `X` 的，都要解析出地址，或者解析出它跟随哪个区域
- [ ] 3.3 用 T1 生成的 `scatter.scat` 和厂商 `LinkFiles/Ads/LinkerAdsPf.scat` 做测试

## 4. 芯片区域数据

- [ ] 4.1 芯片 YAML 新增可选字段 `memory_regions`（name、start、size、type、core、cacheable），读写都保持原样；旧文件不受影响
- [ ] 4.2 按厂商 MEMORY 注释表补 THA6206 的区域，每项标记"待确认"

## 5. 检查与报告

- [ ] 5.1 合并 ①②③，报告：用到但没映射；未显式放置（给出会落到的区域和通配选择器）；无区域接收；COREn 落在别的核心的区域；不可缓存的段落在可缓存区域
- [ ] 5.2 结果按类别、文件、行排序，导出 Markdown 清单；结果头部列出扫描的目录、文件数、链接文件，以及芯片区域是否待确认
- [ ] 5.3 检查过程不修改任何配置或文件

## 6. 工程设置与界面

- [ ] 6.1 工程保存和读取检查设置（源码目录、MemMap 头目录、链接文件），用相对工程目录的 POSIX 路径；旧工程读取时为空
- [ ] 6.2 "检查内存映射"对话框：后台执行、可取消、显示结果、导出；在主窗口挂菜单项
- [ ] 6.3 UI 测试（offscreen）：设置保存、执行、取消、导出

## 7. 验证

- [ ] 7.1 在 T1（THA6206，Can、Mcu、Port、Intc 和 OS）上执行，列出结果给用户确认；预期能报出 `.mcal_bss_asil_d_unspecified_core0` 落进 `UNDEFINE_RAM_BSS`（GMU_NORMAL）
- [ ] 7.2 全量测试；`openspec validate add-memory-map-check --strict`
