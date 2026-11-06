# Design: add-vbrs-eb-templates

完整设计见 `docs/superpowers/specs/2026-11-06-vbrs-eb-templates-design.md`。这里只记录关键取舍。

## 数据来源

| 产物 | 生成方式 | 输入 |
| --- | --- | --- |
| `vBrsCfg.h`、`Makefile.config.generated` | EB 模板 | vBRS 配置；衍生芯片宏、核类型、最高频率、核数取自芯片数据 |
| `vBrs_Lcfg.h/.c` | EB 模板 | 用户 Os 的 `OsCoreIdMappingConfig`、`OsApplicationCoreRef`；`STACK_C<n>` 的大小 |
| `vLinkGen_Cfg.h`、`vLinkGen_Lcfg.h/.c` | 链接文件生成器 | 与链接文件相同的 Plan |

DaVinci 从 dpa 的 Derivative、SIP 衍生芯片数据和 MICROSAR Os 取的值，在本工具里分别取自芯片数据和用户 Os。

## 为什么初始化表不用 EB 模板

表项的起止标签必须和链接文件里的区域一一对应。两者用同一份 Plan、同一张按编译器区分的标签表，才能保证不会对不上；链接文件生成器也是存储布局的权威。vBRS 自己的 4 个文件用 EB 模板，这是用户的要求。

## 表项规则

- **复制表项（Init）**：执行地址与加载地址不同的区域，不论是代码还是数据。
- **清零表项（ZeroInit）**：bss 区域，以及 data 区域里的 ZI 部分。
- **不进表**：noinit、stack，以及在 Flash 上执行的 code/const。
- **所属核**：
  - 核私有窗口上的区域属于该核；
  - 核本地别名窗口上的区域每核各一条；
  - 其他区域属于启动核。
- **阶段**：默认为 ONE。所属核和阶段都可以按区域覆盖。
- **Alignment**：取窗口的 ECC 粒度（TCM 为 8，其余为 4 并标"待确认"），只允许 0、4、8。
- **Early 区域块**：芯片数据里标了需要整块清零的窗口，用 64 位写入清零。这一项取代厂商 `startup.c` 的 ITMU 清除。
- **排序**：表项按区域名排序；生成时检查有没有遗漏的 RW/ZI 区域或需要复制的区域。

## ADS

- armlink 不能在 scatter 里定义任意符号，所以表里写 `Image$$<R>$$Base/Limit` 和 `Load$$<R>$$Base`。
- 启动过程不经过 `__main`/`__scatterload`；RW 数据压缩必须关闭（`--datacompressor=off`）。生成器在文件和生成报告里写明这一点。
- 静态 BrsHw 只认 `BRS_COMP_LLVMHIGHTEC`。编译时选中该分支（armclang 同属 clang），并把 `_STACK_C<n>_LIMIT`、`_OS_EXCVEC_CORE<n>_CODE_START` 在链接时映射到 `Image$$` 符号。这条路先做实验，不行就停下来问用户。

## 对照

- **vBRS 的 4 个文件**：
  - 对照矩阵覆盖 JAR（javap）中每个分支；
  - 对照输出由 DVCfgCmd 在样例副本上生成，样例为 `-m /MICROSAR/vBRS`；
  - 去掉文件头、统一换行后逐字节比较。
- **`vLinkGen_*` 三个文件**：类型、宏、表名、空表写法和表项格式与样例逐行对照，表内容做单元测试。
- **ADS 编译链接**：用映射文件核对每个标签和每条表项。

## 不做的事

- EcuM/SchM 桩、DvC6；
- GNU ld/Tasking 链接文件生成器；
- 改 Vector 静态代码或用户内核；
- 上板；
- UI 编辑新增的区域字段。
