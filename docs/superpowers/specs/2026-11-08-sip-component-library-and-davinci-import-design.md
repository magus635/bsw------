# 组件库加载、工程目录管理与 DaVinci 工程导入：设计需求

日期：2026-11-08。这是"用本工具取代 DaVinci Configurator"总体工作的第一个子项目。

## 1. 要做什么，为什么

用户要彻底摆脱 DaVinci Configurator，用本工具完成 BSW 模块的配置、校验、代码生成和系统集成。BSW 源码以 Vector MICROSAR 的静态代码为基础（`D:\davinci\mcuapp\Components\<模块>\Implementation`），允许修改；配置代码由本工具的 EB 兼容模板生成，不用 Vector 的生成器 jar。

DaVinci 的做法是：按目录约定扫描 SIP 下所有 `Components/*/BSWMD/*.arxml`，在内存里按 AUTOSAR 路径合并同名元素，建成统一模型，生成器只通过模型取数据。本工具目前没有这一层：

- 模块定义在 `.dpa` 里逐个写出，每个模块只认一个定义文件；
- 不认识 `BSW-IMPLEMENTATION`、`MEMORY-SECTION`，也不会把 `Arti_bswmd.arxml` 和 `Arti_MemMap.arxml` 合并成一个 `/MICROSAR/Arti_Impl`；
- 除定义文件外，其他工程目录都写死在代码里。

本子项目补上这一层，并把现有 DaVinci 工程的配置接过来。后续子项目（MemMap 汇总、链接文件和 Makefile、各模块模板、SchM、RTE、系统描述导入）都建立在它之上。

## 2. 总体路线（供定位，本文只覆盖第 1 项）

不用 Vector 的 jar，意味着要补的不只是模板。2026-11-09 的调查（见 5.1 末尾）表明，组件 jar 中模板/输出类只占 4%～43%，其余是校验、修复动作（solving action，会直接改写 ECUC）、生成前的中间计算，以及向 Configurator 登记的集成信息；RTE 核心是外部程序；系统描述推导在 Configurator 本体里。路线据此扩充为：

| 顺序 | 子项目 | 取代 DaVinci 的哪部分 |
|---|---|---|
| **1** | **组件库加载 + 工程目录管理 + DaVinci 工程导入（本文）** | 本体的 SIP 扫描、BSWMD 合并、工程加载 |
| 2 | MemMap 汇总生成：收集所有模块的内存段，生成各 `<Msn>_MemMap.h`（含 MCAL 段的来源，见第 10 节） | `Common_MemMap.jar` |
| 3 | 链接文件、Makefile、文件清单 | `vLinkGen.jar`、`vBRS.jar` 的构建输出 |
| 4 | 各模块配置代码模板 + **生成前预计算**（句柄 ID、缓冲区大小、排序、哈希等；放在模板内还是公共函数库，由该子项目定） | 各组件 jar 的 generation 与中间模型部分 |
| 5 | **校验框架 + 规则**：先建框架，规则随模块逐步补；缺规则不应阻止生成，但必须让用户知道哪些模块没有规则覆盖 | 各组件 jar 的 validation 部分（Dem 一个 jar 就有 422 个规则类） |
| 6 | **跨模块自动补全**（修复动作的等价物）：如 Os 的空闲任务、栈、自旋锁、内存区，BswM/EcuM 的引用，EcuC 初始化函数列表；每次补全要可预览、可追溯、可撤销 | 各组件 jar 的 solving action；本体 `workflow.ecucupdater` |
| 7 | **BSW Internal Behavior + SchM**：各模块的独占区、MainFunction 周期与 TimingEvent，与 ECUC 保持同步；BSW 调度、MainFunction→Task 映射 | 各 jar 登记的 `addExclusiveArea`、`addTimingEventUpdater`；本体 `bswintbehavior` 服务 |
| 8 | **Service SWC 生成**（Dem、Dcm、BswM、EcuM 等的 `*_swc.arxml`） | 各 jar 的 `registerSwcTemplate` / `*SwcTemplateProducer` |
| 9 | **RTE 生成，以及由 RTE 反推的 OS 配置**（报警、调度表、任务映射、事件）。OS 是自研内核，接口要按该内核重新设计 | `MicrosarRteGen64.exe` + `Rte.jar` 的 `RteEcucUpdater` |
| 10 | 系统描述导入与推导（SystemExtract/DBC→Com/PduR/CanIf 等） | 本体 `workflow.baseecuc.mapping`（约 60 个模块的推导规则） |
| 11 | BSWMD 版本迁移（可选：固定 SIP 版本时可不做） | 各 jar 的 `registerBswmdMigrationRules` |

说明：
- 这个顺序是助手的建议，用户还没有明确确认。
- 导入的 DaVinci 工程里，上述 jar 和本体产出的结果（RTE 回写的 Os 报警、修复动作补全的容器、推导出的通信配置等）已经固化在 ECUC 中，所以第 1 项"导入后接着用"不依赖第 5～11 项。缺这些子项目的影响，出现在导入之后修改配置时：原来由 DaVinci 自动完成的联动，要由新工具或人来完成。
- 第 5～11 项的实际次序，应按"导入后最常做的修改"来定，例如经常改通信就提前第 10 项，经常加 Runnable 就提前第 7～9 项。

## 3. 用户已定的事项

- 目标是彻底摆脱 DaVinci，包括系统集成（RTE、SchM、MemMap 汇总、EcuM/BswM 模式联动、链接文件、Makefile 和文件清单），参考 DaVinci Configurator 的做法。
- BSW 静态代码参考 Vector 的，可能有改动。生成器用代码模板，**不用 Vector 的 jar**。
- 在现有工具 `D:\bsw-------main\bsw------` 上做，模板格式已定（EB 兼容的 `[!…!]` 格式）。
- **目录由 `.dpa` 管理**，原设计对工程目录没有硬性要求的思路要保持并贯彻。
- **MCAL 用 EB 插件布局，BSW 全部用 Vector 布局。**
- 对 Vector 静态代码的修改**直接在 `Components/<模块>/Implementation/` 里改**，不另外维护叠加副本。
- 自研模板放在 **`Components/<模块>/Templates/`**（与 `Implementation/` 同级）。
- **要能直接导入 DaVinci 工程，接着用已有配置。**
- **一次性迁移**：导入后只用本工具编辑，不需要再让 DaVinci 读回；DaVinci 工程只作为生成结果的对照基线。

## 4. 目标、非目标、反目标

**目标**

- **G1**：`.dpa` 管理工程用到的全部目录，代码里不再写死工程目录名。
- **G2**：`.dpa` 可声明多个组件库根目录，每个注明布局（`vector` 或 `eb`）；工具按约定扫描出全部可用模块。
- **G3**：Vector 布局下，一个模块 `BSWMD/` 里的全部 arxml 按 AUTOSAR 路径合并，得到模块定义、`BSW-IMPLEMENTATION`（版本、Vendor、AR 版本、内存段、依赖的头文件、Pre/Rec 配置引用）以及 Pre/Rec 配置值。
- **G4**：记录每个模块由哪些文件合并而来及其版本；再次打开工程时，发现变化要提示。
- **G5**：一次性导入 DaVinci 工程，得到一个本工具工程，已有配置值全部保留、定义全部解析。
- **G6**：旧格式工程照常打开。

**非目标**

- 任何代码生成，包括 MemMap 头文件。本子项目只保证生成所需的数据已在模型里。
- 模板清单文件的格式（输出文件名、生成顺序等）。只约定 `Templates/` 目录的位置，格式在模板子项目里定。
- 解析 SystemExtract、SWC、InternalBehavior、TimingExtensions。导入时只记录路径。
- 写回 DaVinci 格式，或让 DaVinci 再打开迁移后的工程。
- 修改 Vector 的 `BSWMD/` 文件。
- 把 Vector 的 BSWMD、静态代码或 jar 放进本工具仓库。

**反目标**（即使功能做出来，出现以下情况也算失败）

- 静默丢失配置：导入后某个参数、容器或引用没了，却没有报告。
- 静默合并冲突：两个文件对同一路径给出矛盾内容时，工具任选一个而不报错。
- 静默漏读：某个 `*_MemMap.arxml` 没被加载，只有到后续生成时才发现少了段。
- 用户看不出某个模块的定义来自哪些文件。
- 旧工程打不开，或打开后配置变了。

## 5. 已查明的事实

### 5.1 DaVinci 的机制（来自对 `D:\davinci\mcuapp` 的分析）

- **SIP 根目录**由 DaVinci `.dpa` 的 `<SIP>` 给出。样例 `Applications\SipAddon\StartApplication\StartApplication.dpa` 第 37 行为 `.\..\..`，即 `D:\davinci\mcuapp`。
- **扫描约定**来自 Configurator 插件 `com.vector.cfg.core.sip.msr_*.jar` 中的字符串：`Components`、`DemoComponents`、`BSWMD`、`GeneratorMsr`，方法 `getBswmdFolders`、`getRegularUsedBswmdFolders`、`getDemoUsedBswmdFolders`；扩展入口为 `DaVinciConfigurator\Core\AdditionalComponents.ini` 和 `com.vector.cfg.AdditionalBswmdPaths`（样例中不存在）。是否递归、是否按 license 过滤，未反编译确认。
- **工具自带定义**：`DaVinciConfigurator\Core\StandardDefinition\`（AUTOSAR 标准定义，如 `/AUTOSAR/EcucDefs/Arti`）、`DaVinciConfigurator\AddrTypes\MemMap_SwAddrMethods.arxml`、`DaVinciConfigurator\PlatformTypes\PlatformTypes_AR4.arxml`。
- **合并**：同一路径的元素分在多个文件里。例：`/MICROSAR/Arti_Impl` 在 `Arti_bswmd.arxml` 第 9220 行（版本、Pre/Rec 引用、模块定义引用）和 `Arti_MemMap.arxml` 第 26 行（内存段 `ARTI_CODE`、`ARTI_VAR_NO_INIT_32`、依赖 `Arti_MemMap.h`）各有一部分。前者带 UUID，后者不带。
- **合并结果只在内存里**，不落盘。生成器 jar 只调用模型 API（`com/vector/cfg/model/{mdf,query,access}`），不读文件。
- **引用的 Pre/Rec 不一定存在**：`Arti_Impl` 引用 `/MICROSAR/Arti_Pre` 和 `/MICROSAR/Arti_Rec`，但 `Components/Arti/BSWMD/` 里没有它们。
- **组件 jar 的职责远不止模板**（2026-11-09 调查，提取 jar 内类名与字符串，未反编译整个 jar）：
  - 抽样 9 个 jar 的顶层类，模板/输出类占比：CanIf、BswM、Dcm 4%，Com 9%，Dem 6%，EcuM 21%，Rte 25%，PduR、Os 43%。校验类在 Com、CanIf、Dem、Dcm 中占 45%～62%。
  - 修复动作直接写 ECUC：引用 `ISolvingAction` 的类 Dem 425、Dcm 176、Os 115、BswM 78；Os 有 `OsSaCreateTaskIdle`、`OsSaCreateStacks`、`OsSaCreateSpinlockIoc`、`OsSaCreateMemoryRegion` 等。
  - 各 jar 的 `GeneratorPackage` 向本体登记独占区（`addExclusiveArea`）、MainFunction 周期/TimingEvent（`addTimingEventUpdater`）、MemMap 段（`registerMemMapSections`）、Service SWC 模板（`registerSwcTemplate`）、BSWMD 迁移规则（`registerBswmdMigrationRules`）。
  - RTE 核心是外部程序 `Components/Rte/Generator/MicrosarRteGen64.exe`；`Rte.jar` 的 `RteEcucUpdater` 把结果回写 ECUC。样例 Os 配置中有 32 处 `DV:RTE` 标记，如报警 `Rte_Al_TE_CanTp_CanTp_MainFunction`。
  - 系统描述→ECUC 的推导在本体插件 `com.vector.cfg.workflow.baseecuc.mapping`（912 个类），组件 jar 不参与；EcuC 初始化函数列表（`DV:EcucBswInitFunction`）也由本体的 `workflow.ecucupdater` 处理。

### 5.2 样例 SIP 的规模和文件形态

- `Components/` 下 124 个目录，其中 110 个有 `BSWMD/`；`DemoComponents/` 下另有 vBRS、vLinkGen、vBaseEnv 等。
- 文件名形态统计：`*_bswmd.arxml` 96 个，`*_MemMap.arxml` 69 个，`*_bswmd_rec.arxml` 17 个，另有 `*_pre*.arxml`、芯片相关文件等。含 `ECUC-MODULE-CONFIGURATION-VALUES`（Pre/Rec）的文件 155 个。**文件名不可作为语义依据**，必须按内容中的元素类型和路径识别。
- 一个目录不一定只含一个模块：`Components/Mcal_Tha62x/BSWMD/` 有 81 个文件，涵盖全部 MCAL 模块；`Components/MemMap/BSWMD/` 有定义、SwAddrMethods、多份 Rec/Pre。
- 包路径不止 `/MICROSAR`：如 `/MICROSAR/CanTrcv_Tja1040/CanTrcv`、`/MICROSAR/VTT/VTTOs`、`/THA6_AS440_FuSa/Adc`。
- **`BSWMD/` 下有子目录**（2026-11-09 补查，第一层扫描时漏掉）：共 115 个 arxml 位于子目录中，涉及 3 个组件：
  - `Components/Os/BSWMD/Os/<衍生芯片目录>/`：42 个子目录（`Generic_CortexR52`、`Generic_CortexR52_ASIMD`、`S32Gxx`、`TMS570LC43x` 等），每个含 `Os_<名>_bswmd_pre.arxml`、`_rec.arxml`。**每个子目录都声明同一个 `/MICROSAR/Os_Pre`**，只是 `OsPublishedInformation` 下的容器不同。
  - `DemoComponents/vBaseEnv/BSWMD/vBaseEnv/Tongxin_THA6/`：`vBaseEnv_THA6_pre.arxml`、`vBRS_THA6_pre.arxml`、`vLinkGen_THA6_rec.arxml`。
  - `Components/vMem_30_Fls/BSWMD/vMem_30_Fls/vMem_30_Fls.arxml`。
- **DaVinci 只加载与工程衍生芯片对应的子目录**：样例工程的 Os 配置（`StartApplication_Os_Os_ecuc.arxml`）里只出现 `Generic_CortexR52_ASIMD`，其余 41 个子目录的内容都没有进入。对应关系来自 `Components/Os/GeneratorMsr/DerivativeMapping_Os.xml`：以衍生芯片 UUID `B632B9EE-F23D-43CD-9C54-542178A058D9`（与 DaVinci `.dpa` 中 `<Derivative UUID=…>Tongxin_THA6206` 相同）映射到 `SIP_Folder = Generic_CortexR52_ASIMD`。**子目录名与衍生芯片名不同**，不能按名字匹配。整个 SIP 中只有 Os 有这种映射文件；vBaseEnv、vMem_30_Fls 的子目录没有映射文件，样例中 vBaseEnv 子目录的内容进入了配置（推断：无映射文件的子目录总是加载，未反编译确认）。
- **组件目录不等于模块**：`DemoComponents/vBaseEnv/BSWMD/` 里有 vLinkGen 的 4 个 rec（`vLinkGen_BaseEnv_rec.arxml`、`vLinkGen_BaseEnv_Variants_rec.arxml`、`vLinkGen_BaseEnv_Compiler_KEEP_rec.arxml`、`Tongxin_THA6/vLinkGen_THA6_rec.arxml`），加上 vLinkGen 自己目录里的 5 个 pre/rec，vLinkGen 共 9 个 pre/rec 文件，分布在两个组件目录里。

### 5.3 样例 DaVinci 工程

- `StartApplication.dpa` 是 XML（`<ProjectAssistant Version="5.30.35 SP2">`）。相关字段：
  - `<SIP>`、`<Folders>`（ECUC、GenData、GenDataVtt、Source、ServiceComponents、Logs、ApplicationComponentFolders、TimingExtensionFolders、BswInternalBehaviour、McData、DefinitionRestriction、AUTOSAR）；
  - `<Derivative>`（Tongxin_THA6206）、`<Compiler>`（LlvmHighTec）、`<SipIds>`；
  - `<Input><ECUEX>`（SystemExtract）、`<References>`（FlatMap、FlatExtract、Communication、DVWorkspace）；
  - `<EcucSplitter>`：每个模块配置所在文件；
  - `<ECUC><Active>`：`Config\ECUC\StartApplication.ecuc.arxml`（`ECUC-VALUE-COLLECTION`，28 条模块引用：vSet、Os、Det、EcuC、BswM、EcuM、Rte、vBRS、vBaseEnv、Spi、Crc、Dio、vLinkGen、MemMap、VTTMemMap、Resource、Port、Mcu、Can、CanIf、ComM、CanSM、Com、PduR、CanTrcv、VX1000、Dcm、CanTp）；`<Derived>`：`StartApplication.ecuc.Initial.arxml`；
  - `<ModuleDefinitionMappings>`：模块名→定义路径；
  - `ToolSettings/Misc` 下的 `BswImplSwVersion`、`BswmdVersion`：DaVinci 记录的各模块实现版本。
- `Config/ECUC/` 下有约 30 个 `*_ecuc.arxml`，用 `DEFINITION-REF` 指向 `/MICROSAR/<模块>` 或 `/THA6_AS440_FuSa/<模块>`，用 `MODULE-DESCRIPTION-REF` 指向 `/MICROSAR/<模块>_Impl`。同目录还有 MCAL 的 `*.xdm` 和 `convert_ecuc_to_xdm.py`。
- `.workflow/DeletedModules/` 下有 DaVinci 删除模块时留下的历史配置。

### 5.4 本工具现状（`D:\bsw-------main\bsw------`）

- 工程文件 `.dpa` 是 JSON，`format_version` 7。与 DaVinci 同扩展名、不同格式。
- 模块在 `.dpa` 的 `modules` 里逐个列出 `def_path`、`config_path`；另有 `def_search_paths`。
- 写死在代码里的目录：
  - `ConfigValue/`：`workspace_manager.py:896`、`:907`；
  - `templates/`：`workspace_manager.py:951`、`:1537`，`generation_controller.py:107`、`:338`，`davinci_tree_view.py:133`，`project_properties_dialog.py:296`，`ecu_resource_diagnostics.py:94`，`ecu_resource_resolver.py:57`；
  - `generateCode/`：`generation_controller.py:162`，`memmap/check.py:92`；
  - `Def/`、`Def/plugins/`：`workspace_manager.py:139`、`:1121`、`:1306`、`:1360`，`generator.py:125`、`:149`，`chip_constraint_service.py:166`、`:191`、`:236`，`chip_database.py:667`，`ecu_resource_resolver.py:49`，`xdm_chip_extractor.py:338`。
- 已有 EB 工程导入（`import_eb_project`，copy/link 两种模式），能读 EB 插件的 `config/*.xdm` 和 `generate_PB/`。
- 已能加载单个 Vector BSWMD（vBRS 设计中验证过 `vBRS_bswmd.arxml`），但不支持 ECUC-MULTILINE-STRING。
- 仓库约定：新能力和架构调整要先写 OpenSpec 提案（`openspec/AGENTS.md`）。

## 6. 需求

### R1 `.dpa` 管理全部工程目录

- `.dpa` 新增目录字段，至少覆盖：配置值目录、模板搜索目录、生成输出目录、EB 插件目录、MCAL 配置值目录（EB 工程 `config/`）、组件库根目录列表、系统描述等外部输入文件的路径。
- 所有 5.4 中列出的写死路径改为从工程对象读取。
- 路径存为相对工程文件所在目录的相对路径；在工程目录之外的保持绝对路径（与现有 `eb_source_root` 的处理一致）。
- 旧工程缺这些字段时，取原来的目录名作为默认值，行为与现在完全一致。

### R2 组件库声明与扫描

- `.dpa` 可声明多个组件库，每项包含：根目录、布局类型（`vector` | `eb`）。另可声明单独补充的模块目录（相当于 DaVinci 的 AdditionalComponents），以及**要排除的组件目录**（如 `Components/Mcal_Tha62x`，见第 10 节）。被排除的目录不扫描、不参与合并，但在"来源"界面中可见其被排除。
- `vector` 布局：扫描 `<根>/Components/*/BSWMD/` 和 `<根>/DemoComponents/*/BSWMD/` 下的 `*.arxml`，**包括子目录**，子目录按下面的衍生芯片规则取舍。每个组件目录同时识别 `Implementation/`、`Templates/`、`Make/`（存在即记录，不存在不报错）。
- **衍生芯片子目录的选择**：
  - 工程记录衍生芯片的名字和 UUID（DaVinci 导入时取自 `<Derivative UUID=…>`）。
  - 组件提供 `GeneratorMsr/DerivativeMapping_<模块>.xml` 时，按衍生芯片 UUID 查出 `SIP_Folder`，只加载 `BSWMD/` 下对应子目录；该组件的其他衍生芯片子目录一律不加载。这是 GeneratorMsr 中唯一被读取的内容，作为数据文件解析，不执行 jar。
  - 有映射文件但查不到当前衍生芯片时报错，不得退回"全部加载"或"任选一个"。
  - 没有映射文件的子目录全部加载（与样例行为一致，见 5.2）。
  - `.dpa` 允许对单个组件显式指定子目录，覆盖上面的规则；覆盖要在来源界面中标出。
  - 选择结果写入 R4 的来源记录。
- `eb` 布局：沿用现有 EB 插件识别规则（`<插件>/config/*.xdm`、`generate_PB/`）。
- 工具自带的公共定义（AUTOSAR 标准定义、SwAddrMethods、PlatformTypes）也要能加载，因为 Vector BSWMD 引用它们（如 `REFINED-MODULE-DEF-REF /AUTOSAR/EcucDefs/Arti`、`SW-ADDRMETHOD-REF /MICROSAR_MemMap/SwAddrMethods/CODE`）。来源可以是 DaVinci 安装目录，也可以是本工具自带副本，由 `.dpa` 指定。
- 扫描结果是"可用模块"列表，即使工程还没配置这些模块，也能在"添加模块"时选到。

### R3 BSWMD 加载与合并

- 按文件内容识别元素，不按文件名，也不按所在组件目录（vLinkGen 的 rec 有一部分在 vBaseEnv 目录里，见 5.2）。至少识别：`ECUC-MODULE-DEF`、`BSW-IMPLEMENTATION`（含 `RESOURCE-CONSUMPTION/MEMORY-SECTIONS`、`REQUIRED-ARTIFACTS`、`PRECONFIGURED-CONFIGURATION-REFS`、`RECOMMENDED-CONFIGURATION-REFS`、`VENDOR-SPECIFIC-MODULE-DEF-REFS`、版本字段）、`ECUC-MODULE-CONFIGURATION-VALUES`（Pre/Rec）、`SW-ADDR-METHOD`。
- 同一 AUTOSAR 路径出现在多个文件时，合并为一个元素，以路径而非 UUID 为准。
- **冲突必须报错**，至少包括：同一路径元素类型不同；同一单值字段取值不同；同一路径的 `ECUC-MODULE-DEF` 在两个组件里各有一份（不允许合并模块定义）。报错要指出路径和涉及的文件。
- 引用目标不存在（如 `Arti_Pre`、`Arti_Rec`）记为警告，不阻止加载。
- 合并结果只在内存里，不写回 BSWMD 文件。
- 合并后的模型要能被后续生成器查询（至少：取某模块的 `BSW-IMPLEMENTATION`；遍历所有模块的内存段及其 SwAddrMethod）。
- 补上 ECUC-MULTILINE-STRING 等现有解析器缺的定义类型（凡样例 SIP 中实际出现的都要能读）。

### R4 来源与版本记录

- 对每个模块，工程保存时记录：参与合并的文件列表（相对组件库根目录）、`SW-VERSION`、`AR-RELEASE-VERSION`。
- 打开工程时与当前组件库比对；文件增减、版本变化要列出并提示，由用户确认后再更新记录。不得静默采用新内容而不提示。
- UI 中可查看任一模块的来源文件列表和版本。

### R5 添加模块

- 从"可用模块"添加模块时，若其 `BSW-IMPLEMENTATION` 引用了存在的 Pre/Rec 配置，用户可选择以 Rec 作为初始值；Pre 中的值视为预设、只读（与 DaVinci 行为一致，具体只读粒度见第 9 节）。
- 新建的模块配置记录它对应的 `BSW-IMPLEMENTATION` 路径（相当于 DaVinci 的 `MODULE-DESCRIPTION-REF`）。

### R6 DaVinci 工程导入（一次性）

- 输入：DaVinci 的 `.dpa`（XML）。工具按内容区分 DaVinci `.dpa` 与本工具 `.dpa`（JSON）。
- 输出：在用户指定的新目录生成一个本工具工程。**DaVinci 工程目录保持不动**，作为对照基线。
- 映射：
  - `<SIP>` → 一个 `vector` 布局组件库；
  - `<Folders>`、`<Input>`、`<References>` 中的路径 → 新 `.dpa` 的对应字段（本子项目不解析的文件只记录路径）；
  - `<Derivative>`（名字和 UUID 都要，UUID 用于 R2 的子目录选择）、`<Compiler>`、`<SipIds>` → 工程属性；
  - `<ECUC><Active>` 的 `ECUC-VALUE-COLLECTION` 和 `<EcucSplitter>` 列出的各模块文件 → 读出全部模块配置值，复制进新工程的配置值目录；
  - DaVinci 的 `BswImplSwVersion` → 与 R4 的版本记录比对，不一致时在导入报告中列出。
- MCAL 部分走 EB 插件布局；`Components/Mcal_Tha62x` 自动列入排除项（见第 10 节）。
- **MCAL 配置值的来源由目录设置指定**（用户 2026-11-08 决定）：MCAL 的 EB 插件目录（定义与模板）和 MCAL 配置值目录（EB 工程的 `config/*.xdm`）都是 `.dpa` 的目录字段（R1），导入时由用户指定，工具不自行猜测。导入界面可以把找到的候选（如样例中的 `TresosMcalProject/THA6206_LFBGA292_AS440/config`、`doc/THA6XXX_MC_AS440/Mcal/EbPlugins/eclipse/plugins`）作为默认值给出，但必须经用户确认。MCAL 配置值通过现有 EB 导入功能从该目录读取。
- DaVinci 生效集合中的 MCAL 模块（样例中 Can、Dio、Mcu、Port、Resource、Spi，定义路径 `/THA6_AS440_FuSa/...`）**不作为配置值来源**，以免同一模块有两份配置；导入报告列出这些被跳过的模块，并核对 BSW 对它们的引用在 EB 来源的配置里能否解析。
- 样例中 MCAL 配置存在三份且内容不一致（DaVinci arxml 6 个模块、`Config/ECUC/*.xdm` 17 个、`TresosMcalProject` 的 EB 工程），这正是不让工具自行选择的原因。
- 导入后：每个模块配置都能找到定义；跨模块引用（含 MCAL 与 BSW 之间）全部解析。
- **导入报告**：逐模块列出导入的容器、参数、引用数量；列出无法解析的定义、引用和被丢弃的内容。不得有未报告的丢失。
- `.workflow/DeletedModules/` 不导入。

### R7 旧工程兼容

- `format_version` ≤ 7 的工程照常打开，配置值、变体、芯片设置不变。
- 保存为新版本格式；新版本格式的工程被旧工具打开时，按现有的版本检查拒绝并提示。

## 7. 验收

用样例 `D:\davinci\mcuapp\Applications\SipAddon\StartApplication`：

1. 导入成功，生成新工程；原 DaVinci 工程目录内容不变（可用 git status 或文件哈希验证）。
2. 导入报告中：每个已配置模块都有定义；未解析引用为 0（或每一条都有明确原因并经用户认可）；无未报告的丢失。
3. 抽查：`/MICROSAR/Arti_Impl` 合并后同时含 SW-VERSION 1.02.00 和两个内存段；`/MICROSAR/MemMap` 定义能找到 `MemMap_SwAddrMethods.arxml` 中的 SwAddrMethod。
4. 导入的配置值与来源逐参数一致：BSW 模块对照 DaVinci 原 `*_ecuc.arxml`，MCAL 模块对照用户指定的 EB 配置值目录（比较方法由实现者定，但必须是自动比较）。
   另抽查衍生芯片子目录：`/MICROSAR/Os_Pre` 的 `OsPublishedInformation` 下只有 `Generic_CortexR52_ASIMD`，没有其他 41 个衍生芯片的容器；vLinkGen 的 9 个 pre/rec 文件都被加载，并在来源界面中列出（含位于 vBaseEnv 目录的 4 个）。
5. 保存、关闭、重新打开：配置不变，来源记录不变，不出现版本变化提示。
6. 在组件库里改一个 BSWMD 文件的 SW-VERSION 后重新打开：出现提示，指出模块和变化。
7. 构造一个冲突（两个文件对同一路径给出不同的单值字段）：加载报错，指出路径和两个文件。
8. 一个现有旧格式工程（含 EB 导入的 MCAL）照常打开，生成结果与改造前一致。

## 8. 助手替用户做的决定（请用户审阅）

- **组件库用"根目录 + 约定扫描"，不逐个列文件**。理由：一个模块的定义分在多个文件里，逐个列容易漏掉 `*_MemMap.arxml`；模块数量 100+；升级 SIP 只需改根目录；与 DaVinci、EB 一致。
- **多个组件库、分布局类型**，以容纳 Vector BSW 和 EB MCAL 两种来源。
- **合并冲突一律报错**，不做"后加载者覆盖"。
- **导入生成新工程到新目录**，不就地改写 DaVinci 工程。
- **按内容区分两种 `.dpa`**，不改本工具工程文件的扩展名。
- **生成输出目录平铺**（同 DaVinci GenData），不按模块分子目录。本子项目只把它设为新工程的默认输出目录；旧工程保持 `generateCode/<模块>/` 的现有行为。理由：Vector 的 `Make/` 和静态代码按平铺目录 include；便于与 DaVinci 输出逐文件对照。
- **用户拒绝更新来源记录时**（R4）：仍用组件库的新内容打开工程，保留旧记录，下次打开继续提示，直到用户接受。不缓存旧定义快照。配置值与新定义不兼容的地方按现有校验报出问题。
- **模块身份以定义路径为准**：不同组件库提供同名但定义路径不同的模块（如 `/MICROSAR/EcuC` 与 EB 的 EcuC）时，两者都出现在"可用模块"列表里，工程中每个模块配置通过 `DEFINITION-REF` 明确绑定其中一个。DaVinci 导入时按原配置的 `DEFINITION-REF` 绑定。同一定义路径出现在两个库里则按 R3 报错。
- **导入范围以 `<ECUC><Active>` 集合为准**（样例 28 个模块）。`<ModuleDefinitionMappings>` 只是名字到定义的映射，不代表已配置，不导入。
- **衍生芯片子目录规则**（R2）：有 `DerivativeMapping_*.xml` 的按 UUID 选一个子目录，查不到就报错；没有映射文件的子目录全部加载；`.dpa` 可逐组件覆盖。"无映射文件即全部加载"是根据样例推断的 DaVinci 行为，未反编译确认。
- **子项目顺序**（第 2 节）。

## 9. 留给实现者

- 新 `.dpa` 字段的具体命名与 JSON 结构、`format_version` 编号。
- 合并模型的内部数据结构，以及与现有 `EcucModuleDef` 模型的衔接方式。
- 扫描与解析的性能策略（例如先建索引、只完整解析工程用到的模块）。样例 SIP 有数百个 arxml，打开工程不应明显变慢。
- 导入后配置值文件在新工程里的拆分方式（每模块一个文件即可）。
- Pre 值只读的粒度（整个容器或单个参数）。
- 自动比较配置值的实现方式。
- 按仓库约定补写 OpenSpec 提案。

## 10. 已决问题与遗留影响

- **MCAL 以 EB 插件为准，排除 `Components/Mcal_Tha62x`**（用户 2026-11-08 决定）。
  - 背景：样例 SIP 的 `Components/Mcal_Tha62x/BSWMD/` 里有一套 Vector 包装过的 MCAL 定义（`Copy_<模块>_THA6206_LFBGA292.arxml`，包路径 `/THA6_AS440_FuSa`）、内存段（`<模块>_MemMap.arxml`，`/THA6_AS440_FuSa/<模块>_Impl`）和 Rec（`<模块>_bswmd_rec.arxml`，位于 `/THA6_AS440` 包）。EB 插件里的 MCAL 定义也用 `/THA6_AS440_FuSa` 包，两者都加载会冲突。
  - 落实：R2 的组件库声明要支持**排除指定组件目录**；DaVinci 导入时自动把 `Mcal_Tha62x` 列入排除项，并在导入报告中说明。排除是 `.dpa` 里的显式记录，不是代码里写死的名字。
  - **遗留影响（交给 MemMap 子项目）**：排除后，MCAL 各模块的内存段在模型里没有来源。已查：样例 EB 插件（`test_import_project/Def/plugins`、`TresosMcalProject`）里都没有 `BSW-IMPLEMENTATION` 或 `MEMORY-SECTION`。MCAL 的 MemMap 在 EB 体系下一般由 MCAL 自带的 MemMap 头文件处理（`Mcal_Tha62x/BSWMD/` 里也有一份 `MemMap.h`）。MemMap 子项目需决定 MCAL 段是否纳入汇总、从哪里取。本子项目不处理。
