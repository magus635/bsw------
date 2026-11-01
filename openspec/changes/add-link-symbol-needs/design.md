## Context

`startup.c` 与 OS 生成的代码按区域名引用链接器符号。生成链接文件（后续阶段）必须产出这些名字，所以先把"需要哪些名字、为什么需要"从代码里读出来。

两个编译器的符号约定已读（`startup_ads.h`、`startup_ghs.h`），差异集中在宏里；`startup.c` 本身用宏、不关心符号的写法。OS 的生成代码则直接写 ADS 符号（`Image$$…`），所以对 OS 来说，GHS 目前没有对应的写法可读。

## Goals / Non-Goals

- Goals：读出每个被引用的区域名及其用途；在已有的 ADS 链接文件里报告缺少的区域和 `_LIMIT`；把编译器符号约定放进一处，后续生成复用。
- Non-Goals：生成任何文件；解析 GHS `.ld`；判断初始化表与 OS 内存配置是否一致；判断区域放进的物理内存是否合适。

## Decisions

### D1 用途由符号或宏的种类决定，不由名字猜

| 引用 | 用途 |
|---|---|
| `STARTUP_GETCOPYDATAINFO(R, …)` | 复制：基址、界限、加载地址 |
| `STARTUP_GETBSSDATAINFO(R, …)` | 清零：基址、清零界限 |
| `STARTUP_GETIMAGEBASEADDR(R, …)` | 基址 |
| `STARTUP_GETIMAGELIMITADDR(R, …)` | 界限（复制类） |
| `STARTUP_GETIMAGEBSSLIMITADDR(R, …)` | 界限（清零类） |
| `STARTUP_GETLOADBASEADDR(R, …)` | 加载地址 |
| `STARTUP_SETSTACK(模式, R)`、`STARTUP_SETHYPMODESP(R)` | 栈顶 |
| `Image$$R$$Base` / `__R_ADDRESS_START` | 基址 |
| `Image$$R_LIMIT$$Base` / `__R_ADDRESS_END` | 界限 |
| `Image$$R_LIMIT$$ZI$$Base` | 界限（清零类） |
| `Image$$R$$ZI$$Limit` | 栈顶 |
| `Load$$R$$Base` / `__R_LOAD_ADDRESS_START` | 加载地址 |
| `Load$$R$$Limit` | 加载界限 |

同一个区域可以有多个用途，合并成用途集合，来源各自保留。

### D2 编译器符号约定只写一处

`symbols.py` 里有两张表：

- 宏 → 用途（上表前半部分），与编译器无关；
- 用途 → 各编译器的符号模板（ADS、GHS），用于识别直接引用，也是后续生成链接文件时"必须产出这些符号"的依据。

GHS 的符号来自 `startup_ghs.h`，直接引用的识别按它写；GHS 的"清零类界限"与"复制类界限"是同一个符号 `__R_ADDRESS_END`，所以从 GHS 符号读不出界限是清零类还是复制类，记为"界限"。

### D3 对照链接文件的规则，只用已解析出的内容

对 ADS 链接文件（已有 `parse_scatter`）：

- 区域缺失：被引用的区域名不是任何执行区域名；
- 缺少界限区域：用途含"界限"，且链接文件里有该区域、没有名为 `<名>_LIMIT` 的执行区域。厂商脚本和 OS 模板都用 `AlignExpr(ImageLimit(X), n) EMPTY 0x0{}` 的空区域做界限，这是实际约定；
- 不检查区域里有什么选择器，也不检查地址。

栈区域是例外：厂商脚本用 `EMPTY 0x1000 {}` 声明栈区域，`<名>_LIMIT` 不适用，栈顶用 `Image$$R$$ZI$$Limit`，所以用途为"栈顶"的区域不要求 `_LIMIT`。

### D4 模板文件与生成结果

与段扫描一致：含 `[!` 的文件不扫描。OS 的 `Os_link_Lcfg.c` 模板里块名是模板变量，扫描生成结果才有真实块名。`output/` 里那份 `Os_link_Lcfg.c` 只有注释，扫描不到需求，视图里就显示为没有引用——这是那份输出的问题，不是本变更的问题。

### D5 非 ADS 的链接文件

读取不依赖链接文件格式。没有 ADS 链接文件时，需求照常读取和显示，对照部分跳过并在结果里说明。

## Risks / Trade-offs

- 宏的调用被条件编译包住时（按核数选择），一律当作引用，可能多报缺失。结果标为"可能"，沿用段扫描的做法。
- 区域名来自宏参数，如果参数本身是另一个宏，只能读到字面。遇到时按字面显示，不猜展开结果。
- 只检查"名字在不在"。名字在、但区域放在错误的内存里，由放置检查负责。
- GHS 的清零/复制界限不可区分（D2）。对 GHS 链接文件的对照是后续工作，此处不会产生误报。

## Open Questions

- 第 4 步生成时，OS 的初始化表（`Os_link_Lcfg.c` 的 `Image$$<块名>$$Base` 引用）要与生成的链接文件一致。块名来自 OS 内存配置，所以"替换 OS 自带 scatter 还是保留"这个决定，会决定这些块名由谁产出。本变更读出来的 OS 块名，正好为这个决定提供依据。
