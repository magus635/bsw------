# vBRS 配置代码的 EB 模板和启动初始化表

## Why

用户要用本工具，为自己的工程（THA6206、EB 风格配置、自研 OS 内核）生成 vBRS 的配置代码。这些代码要与 Vector 静态 BrsMain/BrsHw 一起编译、链接，再与 MCAL、自研内核和 MICROSAR EcuM/Rte 组成完整的 AUTOSAR Classic ECU 工程。

DaVinci 只能处理 MICROSAR 工程。本工具目前既没有 vBRS 模板，也不生成 Vector 启动代码所需的初始化表。

用户已决定：

- 复位和内存初始化交给 Vector BrsHw 的启动代码，厂商 `startup.c` 退出；
- 编译器用 ADS；
- THA6206 的最高 CPU 频率为 400 MHz。

本变更取代 `add-vbrs-code-templates`（另一 AI 的方案，用户已叫停并授权推翻）。

## What Changes

- **vBRS 模板包**：新增 `template_packs/vBRS/`，用 EB 模板生成 `vBrsCfg.h`、`vBrs_Lcfg.h`、`vBrs_Lcfg.c`、`Makefile.config.generated`。
  - 输入：vBRS 配置（Vector BSWMD 从已安装的 SIP 加载）、芯片数据、用户 Os 的核映射、存储布局中的启动栈。
  - 输入不全时拒绝生成。
  - 输出文件名显式声明，文件头用本工具自己的。
  - 去掉文件头后，必须与 DaVinci MSR 生成器的输出逐字节一致。
- **启动初始化表**：链接文件生成器从同一份 Plan 生成 `vLinkGen_Cfg.h`、`vLinkGen_Lcfg.h`、`vLinkGen_Lcfg.c`，覆盖厂商 `startup.c` 原来做的全部内存工作：
  - 复制在 RAM/TCM 中执行的代码和数据；
  - 清零 bss；
  - 核本地别名窗口每个核各一条表项；
  - 用 Early 区域块对 ECC RAM 整块清零；
  - 保证静态代码引用的标签存在（每核启动栈顶、异常向量表、表中的起止和加载地址）。
- **存储布局**：每个区域新增可选的阶段、所属核、对齐字段；每个核新增 `STACK_C<n>` 启动栈区域。
- **芯片数据**：
  - THA6206 的 `cpu_frequency` 改为 400 MHz；
  - 新增 Vector 衍生芯片标识、核类型、窗口 ECC 粒度、窗口整块清零归属；
  - 未确认的值标记出来，不删除。
- **参数类型**：支持 ECUC-MULTILINE-STRING（vBRS 的 `vBRSMakefileUserCode` 需要），包括解析、保存和编辑。
- **ADS 编译链接检查工具**：把 Vector 静态代码复制出来，与生成文件一起编译、链接，再从映射文件核对标签和表项。
- **启动步骤对照**：逐项对照厂商 `startup.c` 和 BrsHw，列出 BrsHw 缺少的步骤以及补的位置（回调文件草稿）。
- **清理旧方案**：删除 `openspec/changes/add-vbrs-code-templates`、`docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md` 和 `docs/superpowers/plans/2026-11-06-vbrs-*`。

## Impact

- New capabilities: `vbrs-code-generation`, `startup-init-tables`.
- Modified capabilities: `chip-library`（芯片数据新字段、频率改正），`config-editor`（多行字符串参数）。
- Builds on the active changes `add-linker-file-generation`, `update-linker-generator-authority`, `add-memory-layout-config` and `add-link-symbol-needs` (linker plan, ADS generator, symbol table, required regions).
- Code:
  - `autosar_configurator/core/memmap/`（config、plan、symbols、generators）；
  - `autosar_configurator/generator/`（显式输出名、引擎函数）；
  - `autosar_configurator/core/parser/`、`core/model/`（多行字符串）；
  - `autosar_configurator/data/chips/THA6206_LFBGA292.yaml`；
  - `template_packs/vBRS/`；`tools/`；`tests/`。
- Not changed:
  - Vector 静态代码和用户内核；
  - `D:\davinci` 下的任何文件（对照输出在副本上生成）；
  - Vector BSWMD、JAR 和静态代码都不放进仓库。
- Risk: Vector 的 R52 BrsHw 只支持 HighTec。第一个任务是一个实验：在 ADS 下不改静态代码，能否编译并链接它。如果不行，停下来问用户（也可以改用 Vector 的 Arm6 版 BrsHw）。

## Design

`docs/superpowers/specs/2026-11-06-vbrs-eb-templates-design.md`，摘要见本目录 `design.md`。
