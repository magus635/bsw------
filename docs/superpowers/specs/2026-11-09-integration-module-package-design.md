# 集成环境设计方案：模块包（Define + Pre 同目录）与工程目录重整

日期：2026-11-09。状态：**用户已审阅，D1–D8 全部确定（见第 11 节）**。下一步写 OpenSpec 提案和实施计划。

**修订 1（2026-11-09 下午）**：参考修订后的《DaVinci 集成配置机制总结》和 SIP spec（新增 jar 职责调查和 11 项路线），并对本方案的各项说法逐条核实（§1.6）。主要改动如下：

- **新增“基线层”**（§6.5）：参照 DaVinci 的 InitialEcuC → BaseEcuC → ActiveEcuC，用基线快照和三方合并处理升级，取代原来“只记 pre 文件哈希”的做法。
- **更正 pre/rec 的识别方式**（§6.2）：pre/rec 的角色按 AUTOSAR 路径判定，不再按文件判定。经核实，同一个文件可以同时含 Pre 和 Rec，例如 `vBRS_General_pre.arxml` 里既有 `vBRS_Pre`，也有 `vBRS_Rec`。
- **更正 EB 插件的推断规则**（§6.2）：`autosar/<模块>_<芯片>.arxml` 也是模块定义，需要说明它们不加载的理由。
- **补充“超集 pre + 配置级选择”模式**（§6.2）：vBaseEnv 是这种做法。
- 路线图按 SIP spec 的 11 项对齐（§8），工作量和决策项也相应更新。

本文回答三件事：

1. 审查 `doc/集成环境设计方案/` 下的 3 份文档和 `docs/superpowers/` 下的相关 spec，指出可借鉴之处和问题（第 1 节）；
2. 从需求出发，列出当前工具在“集成”方面的痛点（第 2、3 节）；
3. 给出解决方案、实现难度和分阶段路线（第 4–11 节）。

---

## 1. 对现有设计文档的审查

### 1.1 `合并功能方案与可行性审查.html`（2026-10-24）

| 项 | 意见 |
| --- | --- |
| 定位 | 讨论的是“意图层 + 跨层推导”（Runnable→Task→Partition→MemMap），属于集成**之上**的一层。它默认模块定义、预配置值怎样进入工程已经解决，但这正是当前缺的部分。 |
| 证据 | 结论依据 README、PROJECT_SUMMARY 和代码目录，没有引用具体代码行；工程路径是 macOS 路径（`/Users/qlwang/...`），与当前仓库不一致。 |
| 可借鉴 | “值分为意图输入、规则推导、默认值、人工确认、人工覆盖五类，并记录来源”这一思想是对的。本方案的**值来源分层**（§6.5）就是它的最小落地版本。 |
| 建议 | 作为长期路线保留，**本轮不实施**。等模块包和值来源分层落地以后，推导结果才有地方存放、才能追溯。 |

### 1.2 `DaVinci Configurator 集成配置机制总结（源码与官方文档核对版）.html`

**修订版评价**：原审查指出的三个问题已经修正：步骤编号已统一；推断已逐处标为“观察”或“推断（未核实）”；衍生芯片子目录和跨目录 pre/rec 已经补上。修订版可以作为设计依据，但引用时要区分 PDF 写明的内容和工程观察。

**可借鉴的机制**（标出依据强度）：

| 机制 | 依据 | 本方案如何采用 |
| --- | --- | --- |
| 定义与值分离：`_bswmd` 是定义，`_pre` 在加载时应用并只读，`_rec` 只在新建时赋一次初值 | PDF 3.1.1、3.1.3 | §6.5 的 PRE、REC 规则 |
| 优先级：Pre > Derived，Pre > Rec | PDF 3.1.2、3.1.3 | §6.5。PDF **没有**规定 Derived 与 Rec 谁优先，本方案暂不规定，等推导能力落地时再定 |
| **分层产出基线**：推导规则先产出 InitialEcuC，叠加 pre/rec 后得到 BaseEcuC，再与 ActiveEcuC 做模型合并，保留用户修改和 User-Defined 参数 | PDF 第 3 章、3.2、4.5 | **新增 §6.5 基线层**。这次不做推导，只用“默认值 + Rec + Pre”构成基线，用三方合并处理定义或 pre 升级。以后加入推导，就在基线里加一层 |
| pre 容器会随保存写进活配置 | **观察**，PDF 未写明。本次已核实：`StartApplication_vBaseEnv_vBaseEnv_ecuc.arxml` 中有来自 pre 的 `Tongxin_THA6206` 和 `Tongxin_THA6412` 两个容器 | §6.5：活配置是包含 Pre 值的完整配置，保存时 Pre 值随之写入。这是本方案自己的决定，不依赖 DaVinci 是否这样做 |
| **超集 pre + 配置级选择**：vBaseEnv 的 pre 同时含 THA6206 和 THA6412，由 `vBaseEnvTestedDerivativeRef` 选当前芯片 | 本次已核实（pre 文件和活配置里各有两个容器） | §6.2：一个 pre 不带芯片条件也是合法用法 |
| **按芯片选 pre 文件**：Os 的 42 个子目录各自声明同一个 `/MICROSAR/Os_Pre`，由 `DerivativeMapping_Os.xml` 按 UUID 选一个 | SIP 文件证实 | §6.2 的文件级芯片条件；§6.10 入库时用映射表选择 |
| 已激活模块的权威清单（`ECUC-VALUE-COLLECTION`） | 工程文件 | §6.7 `modules` |
| 删除模块时归档（`.workflow/DeletedModules/`） | 工程文件 | §6.8 |

**仍需注意的地方**：

- 没有映射文件的子目录“总是加载”，仍然是推断。本方案只在入库时用到这条规则，入库结果要与 DaVinci 的活配置逐值比较来验证（§9 W11）。
- “文件所在的组件目录不等于它所属的模块”（vLinkGen 共 9 个 pre/rec，其中 4 个在 vBaseEnv 目录）：这正是“define 与 pre 放在同一目录”的价值所在。DaVinci 只能靠全局扫描和按路径合并把它们拼起来。
- **不照搬的部分**：DBC/系统描述推导和 `EcucSplitter`。本工具本来就是每个模块一个配置文件。

### 1.3 `vBaseEnv_vBRS_vLinkGen_架构分析.html`

- 文中注明“整理自 AI 会话记录”。第 7.5 节“Vector 制作 pre.arxml 的流程”属于推测（“右键 Duplicate”、“导出时重定向包名”），**不能作为设计依据**。
- 第 7.4 节对“逻辑命名空间合并”的解释是对的。它说明文件名不能作为语义依据，本方案在 §6.2 采纳这一点。
- 与本工具已有决定存在张力：该文把芯片硬件数据（核数、主频、内存块）放在 vBaseEnv 的 pre 里；而 vBRS 设计（`2026-11-06-vbrs-eb-templates-design.md` §11）已经决定**芯片数据只来自本工具的 `chips/*.yaml`**，不从 vBaseEnv 读取。本方案维持这个决定：pre 只承载“模块的预设值”，**不作为第二个芯片数据库**。

### 1.4 `docs/superpowers/specs/2026-11-08-sip-component-library-and-davinci-import-design.md`

- 优点：对 SIP 的事实调查很扎实，包括衍生芯片子目录、跨目录 rec、`Mcal_Tha62x` 与 EB 定义冲突、`Arti_Impl` 分散在两个文件。反目标（静默丢失、静默合并、静默漏读）写得好，本方案全部继承。
- 主要问题：它让工具在**运行时**直接理解 Vector SIP 布局，每次打开工程都要扫描数百个 arxml、跨组件按 AUTOSAR 路径合并、按 UUID 选衍生芯片子目录。代价是：
  - 工具要同时理解三种布局：本工具自己的、EB 插件、Vector SIP；
  - 加载流程、性能、冲突处理都变复杂，对现有加载代码属于颠覆性改动；
  - 和这次“define 与 pre 放在同一目录、方便处理”的要求方向相反。
- 本方案的处理：保留它的 R1（`.dpa` 管目录）、R4（来源与版本记录）、R5（添加模块时用 Pre/Rec）、R6（DaVinci 工程导入）和全部反目标；把 R2/R3 的“运行时扫描与合并”改为**一次性入库**，把 SIP 整理成模块包，运行时只认模块包（§6.10）。R2 新增的衍生芯片子目录规则（按 UUID 查映射、查不到报错、可逐组件覆盖）**原样搬到入库步骤**。
- **修订版新增内容及其对本方案的影响**：
  - **jar 职责调查（5.1）**：模板和输出只占组件 jar 的 4%～43%，其余是校验、修复动作（直接改写 ECUC）、预计算，以及向本体登记独占区、TimingEvent、MemMap 段、SWC 模板。影响有两点：
    - 修复动作和推导产生的值必须有地方存放，并且能追溯、能撤销。本方案用值来源中的 `DERIVED` 和基线层承载它们（§6.5），这是后续“跨模块自动补全”（§8 第 6 项）的前提。
    - 原本由 jar 在运行时向本体“登记”的集成信息（独占区、MemMap 段、TimingEvent），在本工具里需要固定的存放位置。本方案把它们作为模块包中 `impl` 的内容（§6.2），由后续子项目读取。
  - **11 项路线（第 2 节）**：本方案第 8 节已与它对齐，原来的 6 项拆成了 11 项。
  - **“导入后接着用不依赖第 5～11 项”**：这个判断对本方案同样成立，所以阶段划分不变（§9）。
- **与它的一处冲突**：SIP spec 第 8 节规定“用户拒绝更新来源记录时……不缓存旧定义快照”。本方案新增的基线快照（§6.5）缓存的是**值**（默认值、Rec、Pre 合成的结果），不缓存**定义**，两者不矛盾。但基线快照会在工程里多存一份文件，请在 D7 中确认。
- 第 2 节的子项目顺序仍标注为“用户还没有明确确认”，请在 D6 中一并确认。

### 1.5 `docs/superpowers/specs/2026-11-06-vbrs-eb-templates-design.md`

与本方案不冲突。vBRS 适合作为第一个“Vector 组件入库”的试点（§9 阶段 3），原因有两个：

- 它的 pre 分散在 vBaseEnv 目录；
- `/MICROSAR/vBRS_Pre` 由两个文件拼成（`vBRS_General_pre.arxml` 和 `Tongxin_THA6/vBRS_THA6_pre.arxml`），而且每个文件里同时有 `vBRS_Pre` 和 `vBRS_Rec`。

它的 §11 已决定在芯片数据里新增“Vector 衍生芯片标识”字段。入库时就用这个字段把本工具的芯片名对应到 `DerivativeMapping` 的 UUID（§6.10）。

### 1.6 本方案各项说法的核实结果

| 说法 | 结果 | 依据 |
| --- | --- | --- |
| EB 导入时跳过 `McuPreConfiguration.xdm` | 已核实 | `workspace_manager.py:1318`；`Mcu_THA6_AS440/plugin.xml` 第 46–52 行有 `<preconfig default="true">` |
| 26 个 EB 插件中只有 Mcu 声明了 preconfig | 已核实 | 搜索 `test_import_project/Def/plugins/*/plugin.xml` |
| EB 插件的 `config/` 下同时有定义和 pre | 已核实（Mcu） | `config/Mcu.xdm`、`config/McuPreConfiguration.xdm` |
| EB 插件的 `autosar/<模块>_<芯片>.arxml` 也是 `ECUC-MODULE-DEF`，路径与 xdm 相同 | 已核实（Mcu、Can） | 每个插件有 3 个芯片版本；`plugin.xml` 只把 `config/*.xdm` 登记为 schema。原稿 §6.2 漏掉了这一点，**已更正** |
| 一个值文件可以同时含 Pre 和 Rec | 已核实 | `vBRS_General_pre.arxml`、`vBRS_THA6_pre.arxml` 中都有 `vBRS_Pre` 和 `vBRS_Rec` |
| pre/rec 由 `BSW-IMPLEMENTATION` 的 `PRECONFIGURED-`/`RECOMMENDED-CONFIGURATION-REF` 按路径指定 | 已核实 | `vBRS_bswmd.arxml` 指向 `/MICROSAR/vBRS_Pre`、`/MICROSAR/vBRS_Rec`。原稿说“值文件里的引用决定角色”，**有误，已更正**：引用在 IMPL 里，不在值文件里 |
| 超集 pre（vBaseEnv 含两个芯片） | 已核实 | 见 §1.2 |
| 保存时 pre 写进活配置，与 DaVinci 相同 | 观察，PDF 未写明 | 见 §1.2 |
| 现有 Rec 加载会混入 Pre，并按 `_Pre` 后缀排序 | 已核实 | `config_manager.py:1495-1552` |
| 每次保存都会覆盖 `templates/<模块>/` | 已核实（按代码阅读） | `workspace_manager.py:938-970` 用 `copytree(dirs_exist_ok=True)`；未用实际工程复现 |
| 写死的目录名有 20 多处 | 已核实 | 对 `"templates"`、`"generateCode"`、`"ConfigValue"`、`"Def"` 的搜索结果 |
| EB `preconfig default="true"` 在 tresos 中的确切语义 | **未核实** | 需要用户确认（D1） |
| 没有映射文件的子目录总是加载 | **推断** | 沿用 SIP spec；入库后逐值比较验证 |

---

## 2. 需求

### 2.1 用户要做的事（场景）

| # | 场景 | 现在怎么做 |
| --- | --- | --- |
| S1 | 新建工程，选芯片，从“可用模块”里勾选要用的模块 | 只能通过文件对话框一个个选定义文件（`project_controller.py:841`） |
| S2 | 添加一个模块时，厂商预设的值（如 Mcu 复位原因表、Os 衍生芯片信息）自动进入配置 | 不会自动进入。EB 的 `McuPreConfiguration.xdm` 在导入时被跳过（`workspace_manager.py:1318`） |
| S3 | 添加模块或容器时，用推荐值作为初值 | 只能手动执行菜单 “Load Recommended Values...”，再选文件 |
| S4 | 一眼看出某个值是预设的、推荐的、默认的还是自己改的 | 看不出来。值上只有 `is_modified` 标志（`configuration_model.py:29`） |
| S5 | 厂商升级了定义或预设值，打开工程时知道哪些值受影响 | 不提示 |
| S6 | 把 EB 工程、Vector 组件、DaVinci 工程接进来 | 能导入 EB 工程，但不能接 Vector 组件和 DaVinci 工程 |
| S7 | 删除模块后还能找回原配置 | 直接删除，无法找回 |
| S8 | 看工程目录就知道每个目录放什么，拷到别的机器能直接打开 | 目录名写死在 20 多处代码里；link 模式依赖符号链接 |

### 2.2 需求清单

- **N1** 模块的图形结构仍然**由 define 文件构造**，现有的定义解析和配置树不变。
- **N2** 通过加载 **pre arxml/xdm** 导入预设的配置值。
- **N3** **define 与 pre 放在同一个目录里**。一个模块的全部“出厂资料”（定义、预设、推荐值、模板、资源）都在一个目录下。
- **N4** 参考 DaVinci 的集成方式，但**不颠覆**现有方案：
  - 已有工程照常打开，生成结果不变；
  - EB 插件不需要改造就能使用；
  - 加载、生成主流程保持不变。
- **N5** 重整工程目录结构，使其清晰、可移植。
- **N6** 为后续集成能力（MemMap 汇总、链接文件、Makefile、模式联动等）准备好数据和目录位置。

---

## 3. 当前设计的痛点

按“与需求的关系”排序，每一条都给出代码证据。

### P1 模块没有“包”的概念，define 只是一个孤立文件

- 工程里每个模块只记录一个 `def_path`（`workspace_manager.py:921-929`），添加模块就是选一个文件（`project_controller.py:841-859`）。
- 同一模块的 pre、rec、模板、`.properties` 资源与定义之间没有登记关系，只能靠目录约定或文件名去猜：
  - rec 用 `rglob("*_rec.arxml")` 按文件名找（`config_manager.py:130`）；
  - 模板目录按 `def_path.parent.parent / "generate_PB"` 推（`workspace_manager.py:957`）；
  - 芯片名按文件名里的 `THA` 前缀猜（`workspace_manager.py:146-150`）。
- 后果：没有“可用模块”清单；文件一换位置或换名字，关系就断了，而且不报错。

### P2 Pre 值没有进入工程的通道

- EB 插件在 `plugin.xml` 里明确登记了预配置。例如 Mcu 插件的 `<preconfig default="true" path="ASPath:/THA6_AS440_FuSa/McuPreConfiguration" .../>` 指向 `config/McuPreConfiguration.xdm`。本工具导入时却按文件名把它跳过了（`workspace_manager.py:1318`、`:1514`）。
- Vector 的 `_pre.arxml` 只能通过 “Load Recommended Values” 手动加载。加载时把 Pre 和 Rec 混成一份，规则是“Pre 先放、后者只补空缺”（`config_manager.py:1531-1552`）：
  - Pre 值可以被随意修改；
  - 下次打开工程时不会重新应用；
  - 厂商更新 pre 文件后，工程不会知道。
- **Pre 和 Rec 的语义被混为一谈。** DaVinci 中 Pre 是只读、每次加载都应用；Rec 只在新建时赋一次初值。

### P3 值没有来源信息

- `EcucParameterValue` 和 `EcucContainerValue` 只有 `is_modified`（`configuration_model.py:29`、`:278`）。无法区分默认值、预设值、推荐值和用户值。
- 因此做不到：只读锁定预设值、升级时只更新没被用户改过的值、在界面上标出来源。这也是第 1.1 节“意图层”将来落地的前提。

### P4 工程目录写死在代码里，工程根目录靠猜

- `ConfigValue/`、`templates/`、`generateCode/`、`Def/plugins/` 共在 20 多处写死（SIP spec 5.4 已逐行列出，例如 `workspace_manager.py:896`、`generation_controller.py:107`、`:162`、`ecu_resource_resolver.py:49-57`）。
- 生成器从模板目录**往上最多找 5 层**，找到含 `Def` 或 `Define` 的目录就当作工程根（`generator.py:118-140`），找不到时再按 `templates` 这个名字回退。目录一调整，这里就会悄悄找错。

### P5 模板被复制两份，而且每次保存都覆盖

- copy 模式下，**每次保存工程**都把 `Def/plugins/<插件>/generate_PB/` 用 `copytree(..., dirs_exist_ok=True)` 复制到 `templates/<模块>/`（`workspace_manager.py:938-970`）。
- 后果：
  - 同一份模板在工程里存在两份；
  - 用户在 `templates/<模块>/` 里修改过的同名模板文件，**下次保存时会被插件原件静默覆盖**。这违背了“静默丢失”反目标。

### P6 link 模式依赖符号链接，在 Windows 上不可靠

- link 模式用 `os.symlink` 创建 `Def/plugins` 和 `templates/<模块>`（`workspace_manager.py:1383`、`:1544`）。
- Windows 默认需要开发者模式或管理员权限才能创建符号链接；git 和压缩工具对符号链接的处理也不一致。用户主力环境是 Windows。

### P7 Vector 组件的定义与 pre 分散，无法按“一个模块一个目录”使用

- 例 1：vBRS 的 pre 在 vBaseEnv 目录里（见 §1.2 第 3 条）。
- 例 2：Os 的 pre 按衍生芯片分 42 个子目录。
- 例 3：`Arti_Impl` 分散在 `Arti_bswmd.arxml` 和 `Arti_MemMap.arxml` 两个文件中。
- 现有加载代码“一个模块一个定义文件”，处理不了这些情况。

### P8 删除模块无法找回，也没有“已激活模块”的权威清单

- `remove_module` 直接删除（`workspace_manager.py:483-529`）。
- `.dpa` 的 `modules` 数组兼任“激活清单”和“文件位置表”。

### P9 工程目录结构不清晰（目录审查结果）

当前一个导入 EB 后的工程：

```
<工程>/
├── <工程>.dpa            JSON，format 7
├── ConfigValue/          <模块>_Config.arxml（活配置）
├── Def/plugins/          EB 插件副本或符号链接（定义 + pre + 模板 + 资源）
├── templates/<模块>/     generate_PB 的第二份副本 + 自研模板（混在一起）
├── generateCode/<模块>/  生成产物，按模块分子目录
└── chips/                工程私有芯片数据
```

问题汇总：

- “出厂资料”（`Def/plugins`）和“工程自己的东西”（`templates` 里的自研模板）混放；
- 模板有两份；
- 目录名风格不统一，大小写和单复数混用；
- 内存映射检查的源码目录、链接文件等外部输入以零散字段挂在 `.dpa` 上，没有统一位置；
- 没有存放导入报告和删除归档的地方。

---

## 4. 目标、非目标、反目标

**目标**

- **G1 模块包**：一个模块的定义、预设（pre）、推荐值（rec）、模板、资源放在**同一个目录**，由清单文件说明每个文件的角色。
- **G2 Pre 进入工程**：加载模块时应用 pre，应用规则明确（§6.5），冲突必须报告。
- **G3 值来源与基线**：每个值知道自己来自 Default、Pre、Rec 还是用户，界面能显示，只读规则能执行；定义或预设升级时，用户改过的值不丢（三方合并）。
- **G4 可用模块清单**：从模块库扫描出可用模块，添加模块时从清单里选，按芯片自动挑选对应的 pre。
- **G5 工程目录清晰**：目录由 `.dpa` 管理，代码里不写死；新工程用新的目录结构，旧工程照常打开。
- **G6 兼容**：EB 插件目录不改造就能作为模块包使用；旧工程打开后配置和生成结果不变。

**非目标（本轮）**

- 意图层、跨层推导（§1.1）。
- 系统描述和 DBC 推导，以及 DaVinci 式的修复动作（Solving Actions）。基线层预留了 `DERIVED` 这一层（§6.5），但本轮不往里填内容。
- MemMap 汇总、链接文件、Makefile、SchM、RTE 的生成。本方案只保证它们需要的数据有地方存放（§8 路线图）。
- 让 DaVinci 读回本工具的工程。

**反目标**（出现以下任何一条都算失败）

- 静默丢失：配置值、容器、引用、用户修改过的模板消失却没有报告。
- 静默覆盖：pre 改掉了用户的值却没有报告。
- 静默选错：同一模块有多个候选 define 或 pre（例如多个芯片的版本）时，工具任选一个。
- 旧工程打不开，或打开后生成结果变了。

**约束**

- 定义解析器（`EcucDefParser`）、配置模型、生成器的主流程**不重写**，只在入口和出口加东西。
- 遵守 CLAUDE.md：排序确定、路径用 POSIX 风格、生成器指纹稳定。

---

## 5. 方案总览

```
            ┌──────────────────────── 模块库（一个或多个根目录，.dpa 声明） ────────────────────────┐
            │  <库>/Mcu/            <库>/Os/                 <EB plugins>/Can_THA6_AS440/          │
            │   module.json          module.json              plugin.xml   ← 无 module.json 时由它推出  │
            │   config/              config/                  config/Can.xdm                        │
            │    Mcu.xdm      (DEF)   Os.xdm          (DEF)    generate_PB/  (模板)                  │
            │    McuPre*.xdm  (PRE)   Os_THA6206_pre  (PRE,芯片条件)                                  │
            │    Mcu_rec.arxml(REC)   Os_rec.arxml    (REC)                                          │
            │   templates/ resource/  templates/                                                    │
            └───────────────────────────────────┬──────────────────────────────────────────────────┘
                                                │ ① 解析清单 → 按芯片选文件 → 包内按 AUTOSAR 路径合并
                                                ▼
   define ──② 构造图形框架（现有解析器，不变）──▶ 配置树
                                                │
   工程 config/<模块>.arxml ──③ 加载活配置（现有，不变）──▶ Active
                                                │
   ④ 计算新基线 Base' = DEFAULT ⊕ REC ⊕ (DERIVED 预留) ⊕ PRE
      与上次保存的基线 Base（config/base/<模块>.arxml）比较
      → 三方合并进 Active：用户没改过的值跟随基线；用户改过的值保留；
        PRE 强制生效并只读；有冲突或变化时先预演、再确认、并写报告
                                                ▼
                         引用解析 / 校验 / 生成（现有，不变）
```

关键点：

1. **只新增一个概念：模块包。** 它是一个目录加一个清单文件；EB 插件天然就是模块包，清单可以从 `plugin.xml` 推出。
2. **Vector SIP 不作为运行时布局。** 用“入库”工具一次性把需要的组件整理成模块包，同时完成跨目录收集和衍生芯片选择（§6.10）。运行时只认一种布局。
3. **加载流程中新增一步（④）**：计算基线并合并。它的前后步骤都不变。这一步对应 DaVinci 的“BaseEcuC 生成 + EcuC Update”，但只在本模块内进行，也没有推导。

---

## 6. 详细设计

### 6.1 模块包的目录结构

```
<Module>/                     目录名 = 模块名（Mcu、Os、vBRS …）
├── module.json               清单（权威）：模块名、定义路径、版本、文件角色、芯片条件、来源
├── config/                   ★ define、pre、rec 放在同一个目录
│   ├── <Module>.xdm | <Module>_bswmd.arxml       定义（ECUC-MODULE-DEF），可带 IMPL
│   ├── <Module>_MemMap.arxml                     IMPL 片段（内存段等，可选）
│   ├── *_pre.arxml | *PreConfiguration.xdm       值集合（ECUC-MODULE-CONFIGURATION-VALUES），可多份
│   └── *_rec.arxml                               值集合，可多份；一个文件里可以同时有 Pre 和 Rec
├── templates/                代码模板（EB 插件用 generate_PB/，清单里指明）
├── resource/                 *.properties 等芯片资源（EB 现有约定）
└── doc/                      可选：说明、变更记录
```

- 选择 `config/` 这个名字，是因为它和 EB 插件完全一致：EB 的 `Mcu.xdm` 和 `McuPreConfiguration.xdm` 本来就同在 `config/` 下。这样 EB 插件**零改造**即为模块包。EB 插件里的 `autosar/<模块>_<芯片>.arxml` 是同一定义的芯片版本（§1.6），按 §6.2 的规则处理。
- 静态源码（Vector 的 `Implementation/`）不放进包里。清单里只记录它的路径（`implementation` 字段），沿用 SIP spec “直接在 `Components/<模块>/Implementation/` 修改”的决定。

### 6.2 清单 `module.json`

```json
{
  "schema": 1,
  "module": "vBRS",
  "definition": "/MICROSAR/vBRS",
  "implementation_path": "/MICROSAR/vBRS_Impl",
  "vendor": "Vector", "sw_version": "...", "ar_version": "4.x",
  "files": [
    {"path": "config/vBRS_bswmd.arxml"},
    {"path": "config/vBRS_General_pre.arxml"},
    {"path": "config/vBRS_THA6_pre.arxml", "chips": ["THA6206_LFBGA292", "THA6412_BGA516"]}
  ],
  "pre": ["/MICROSAR/vBRS_Pre"],
  "rec": ["/MICROSAR/vBRS_Rec"],
  "templates": "templates",
  "resources": "resource",
  "implementation": "D:/davinci/mcuapp/DemoComponents/vBRS/Implementation",
  "origin": {"kind": "vector-sip", "source": "D:/davinci/mcuapp", "imported_at": "...",
             "derivative": {"chip": "THA6206_LFBGA292", "uuid": "B632B9EE-..."},
             "sources": {"config/vBRS_General_pre.arxml": "DemoComponents/vBaseEnv/BSWMD/vBRS_General_pre.arxml"},
             "hashes": {"config/vBRS_bswmd.arxml": "sha256:..."}}
}
```

规则：

- **文件只是来源，角色按 AUTOSAR 路径判定。** 一个文件可能同时含 Pre 和 Rec，一个 Pre 也可能由几个文件拼成（§1.6），所以 `files` 不标角色：
  - **定义**：`definition` 指向的 `ECUC-MODULE-DEF`；
  - **IMPL**：`implementation_path` 指向的 `BSW-IMPLEMENTATION`；
  - **PRE、REC**：`pre`、`rec` 列出的值集合路径。
- **路径从哪里来**：
  - Vector 组件：入库时从 IMPL 的 `PRECONFIGURED-CONFIGURATION-REF` / `RECOMMENDED-CONFIGURATION-REF` 抄写；
  - EB 插件：从 `plugin.xml` 的 `<preconfig path="ASPath:...">` 抄写。
  - 两边都是“按路径”，规则统一。
- **包内合并**：选中的文件里，路径相同的元素按 AUTOSAR 路径合并（例如 `vBRS_Pre` 来自两个文件，`Arti_Impl` 来自两个文件）。同一单值字段取值不同时**报错**，并指出路径和涉及的文件。合并只在**包内**进行，不跨包。
- **芯片条件**：`chips` 加在文件上。为空表示对所有芯片生效；不为空时，只在工程的 `selected_chip` 在列表中时才读这个文件。芯片名用本工具芯片库的名字。衍生芯片 UUID 只在入库时使用，记录在 `origin.derivative` 中，运行时不使用。
- **两种芯片相关的 pre 写法都支持**：
  - **文件级选择**（Os 式）：每个芯片一个文件，各自声明同一个 `Os_Pre`，靠 `chips` 选一个；
  - **超集 pre + 配置级选择**（vBaseEnv 式）：一个文件里有所有芯片的容器，不带 `chips`，全部应用；当前芯片由配置中的引用参数选择。“这个引用应当指向与 `selected_chip` 一致的容器”属于跨模块一致性规则，留给 §8 第 5 项。本轮只在模块包中记录这种对应关系（可选字段 `chip_selector`），不强制检查。
- **候选冲突**：在当前芯片下，同一路径的定义出现两份且内容不同，或者某个 `pre`/`rec` 路径一个元素都找不到，都**报错**，不任选。引用的 Pre/Rec 路径在任何文件里都不存在时（例如 `Arti_Pre`），只给**警告**，与 SIP spec R3 一致。
- **没有清单时的推断**（只用于兼容，结果在界面上标为“推断”）：
  - EB 插件：读 `plugin.xml`。
    - `schema/resource` 是定义来源（例如 `config/Mcu.xdm`）；
    - `preconfig` 的 `path` 是 PRE；
    - `generate_PB/` 是模板；`resource/` 是资源。
    - **`autosar/<模块>_<芯片>.arxml` 不加载**：它们没有在 `plugin.xml` 中登记为 schema，应视为定义的 AUTOSAR 交换副本，在来源界面中列出即可。这与现有导入逻辑一致：现有逻辑只在没有 xdm 时才用 arxml。
    - 如果某个插件只有 arxml、没有 xdm，就按文件名中的芯片名生成 `chips` 条件，并标为“推断”。
  - 普通目录：按文件**内容**识别。
    - 含 `ECUC-MODULE-DEF` 的元素是定义；
    - IMPL 中有 Pre/Rec 引用的，按引用确定角色；
    - 没有 IMPL 时，值集合 SHORT-NAME 以 `_Pre` 或 `_Rec` 结尾的按后缀判断，标为“推断”；无法判定的报警告，不加载。
  - 用户可以一键把推断结果写成 `module.json`，之后以清单为准。

### 6.3 模块库与“可用模块”

- `.dpa` 用 `module_libraries` 声明一个或多个库根目录，每项有类型：
  - `package`：每个子目录是一个模块包；
  - `eb-plugins`：EB 的 plugins 目录，每个插件是一个模块包。
- 扫描只读每个包的清单（或 `plugin.xml`），**不解析定义**，所以很快。扫描结果就是“可用模块”列表：名称、定义路径、版本、来源库、有没有当前芯片的 pre。
- 模块身份以**定义路径**为准（沿用 SIP spec 第 8 节）。同一定义路径出现在两个库中时报错，除非 `.dpa` 明确排除其中一个。`Mcal_Tha62x` 与 EB 插件冲突的情况，就用这条规则处理。

### 6.4 加载流程（每个模块）

| 步 | 动作 | 与现有代码的关系 |
| --- | --- | --- |
| ① | 定位模块包，读取清单，按 `selected_chip` 选文件 | 新增 `ModulePackage` 解析器 |
| ② | 解析定义；包内 IMPL 和值集合按 AUTOSAR 路径合并，冲突报错 | 定义解析**不变**；合并为新增功能，只在包内进行 |
| ③ | 加载 `config/<模块>.arxml` 中保存的活配置 | **不变** |
| ④ | 计算新基线并做三方合并（§6.5） | 新增 |
| ⑤ | 引用解析、默认值折叠、芯片表达式 | **不变** |

旧工程（`modules[].def_path` 形式）跳过 ① 和 ④，行为与现在完全一致（§6.9）。

### 6.5 值来源、基线层与三方合并

**为什么要有基线层**：原稿只给值加了一个会话内的 `origin` 标记，并记录 pre 文件哈希。这样有两个问题：

- 重新打开工程后，分不出某个值是 Rec 给的初值还是用户改的；
- 定义默认值或 Rec 升级时，不知道哪些值可以跟着变。

DaVinci 的解法是保存一份派生基线（InitialEcuC），叠加 pre/rec 得到 BaseEcuC，再与活配置合并并保留用户修改（PDF 第 3 章、3.2、4.5）。本方案采用同样的结构，但只在模块内做，不做推导。

**三层值**：

| 层 | 内容 | 存放 |
| --- | --- | --- |
| 活配置 Active | 用户最终使用的完整配置（包含 Pre 值），生成器和 EPC 导出都读它 | `config/<Module>.arxml`（格式不变） |
| 基线 Base | 上次接受时“默认值 ⊕ Rec ⊕ Pre”合成的结果（以后再加 Derived） | `config/base/<Module>.arxml`，由工具维护，与活配置同格式 |
| 新基线 Base' | 本次加载时，用当前模块包重新算出的基线 | 只在内存中 |

**值来源不写进配置文件，而是比较得出**：

| origin | 判定 | 可编辑 |
| --- | --- | --- |
| `PRE` | 该路径在 Pre 中出现 | **否**（D1） |
| `REC` / `DEFAULT` | Active 的值等于 Base 的值，且 Base 的值来自 Rec 或定义默认值 | 是 |
| `USER` | Active 的值不等于 Base 的值，或 Base 中没有这个路径 | 是 |
| `DERIVED` | 预留给后续推导或修复动作 | 视规则而定 |

这样做，配置 arxml 的格式完全不变，EB 往返兼容也不受影响。界面上的来源标记和只读状态，都由比较结果得出。

**合成基线的优先级**：Pre > Rec > 定义默认值。依据是 PDF 写明 Pre > Rec。Derived 与 Rec 谁优先，PDF 没有写明，等推导能力落地时再定。

**三方合并（步骤 ④）**：对 Base' 中的每个路径，比较 Base、Base' 和 Active：

| 情形 | 处理 |
| --- | --- |
| Base = Base'（基线没变） | 不动。这是绝大多数情况，打开工程没有额外开销 |
| Base ≠ Base'，Active = Base（用户没改过） | 采用 Base'，写入报告 |
| Base ≠ Base'，Active ≠ Base（用户改过），该值不属于 Pre | **保留用户值**，在报告中标为“基线变化但已被用户覆盖” |
| 该值属于 Pre，且 Active ≠ Base' | 改为 Base'，在报告中标为“预设强制”。这是唯一会改动用户值的情形 |
| Base' 中有新容器（Pre 新增的容器实例） | 创建 |
| Base 中有、Base' 中没有的容器（pre 删除了容器） | 不自动删除，在报告中列出，由用户决定 |

- 当报告中有“改动”类条目（采用新基线、预设强制、创建）时，先**预演**，用户确认后才写入；拒绝时 Active 和 Base 都不变，下次打开继续提示。这一点替代了原稿的 `pre_accepted` 哈希。
- 确认后，Base' 写回 `config/base/<Module>.arxml`。
- Pre 创建的容器不能删除或改名，但可以在它下面添加 Pre 中没有的子容器和参数。
- **只读锁定只在命令层（`command.py`）执行**。配置面板、批量向导、导入、AI 助手都经过命令层，UI 只负责灰显。

**首次启用（新模块，或旧工程迁移）**：

- 新建模块：Active = Base' 并初始化（D8 决定是否默认用 Rec），Base = Base'。
- 旧工程迁移：没有 Base，所以 Active 中现有的值一律视为 `USER`，只有 Pre 会改动它们，而且必须先预演、再逐模块确认（§6.9）。

**REC 规则**：

- 添加模块时，Rec 进入基线，因此也进入活配置的初值。
- 在界面上新建容器时，如果 Rec 中有同一定义的容器，就用它的参数值作为初值。
- 现有菜单 “Load Recommended Values” 保留，用于事后对比和应用，但**只读 Rec，不再混入 Pre**（修正 `config_manager.py:1531` 按 `_Pre` 后缀排序的做法）。

### 6.6 工程目录结构（新）

```
<工程>/
├── <工程>.dpa                 工程总控（JSON，format 8）：目录表、模块库、激活模块、芯片、变体
├── modules/                   工程私有模块包（copy 模式时放这里；也可以只引用外部库）
│   └── <Module>/ module.json, config/, templates/, resource/
├── config/                    活配置：<Module>.arxml（原 ConfigValue/<Module>_Config.arxml）
│   └── base/                  基线快照：<Module>.arxml（工具维护，§6.5）
├── templates/                 工程级模板覆盖层：templates/<Module>/ 中的同名文件优先于包内模板
├── chips/                     工程私有芯片数据（不变）
├── integration/               集成输入：存储布局、链接设置、外部源码与头文件目录
├── system/                    预留：系统描述/DBC、Service SWC、BSW Internal Behavior（§8 第 7–10 项，对应 DaVinci 的 Config/System、ServiceComponents、InternalBehavior）
├── gen/                       生成产物（原 generateCode/）
└── .history/                  工具自己维护：删除归档、导入报告、预设应用报告
    ├── deleted/<Module>_<时间戳>.arxml
    └── reports/<时间戳>_<类型>.md
```

各目录按“谁拥有、谁修改”划分：

| 目录 | 拥有者 | 是否手改 | 是否进版本库 |
| --- | --- | --- | --- |
| `modules/` | 供应商（入库时复制） | 否（升级时整体替换） | 是 |
| `config/` | 工程 | 通过工具修改 | 是 |
| `config/base/` | 工具 | 否 | **是**（三方合并需要它；丢失后按“旧工程迁移”处理） |
| `templates/` | 工程 | 是 | 是 |
| `chips/`、`integration/`、`system/` | 工程 | 是 | 是 |
| `gen/` | 工具 | 否 | 视团队习惯而定 |
| `.history/` | 工具 | 否 | 建议是 |

- **模板查找顺序**：`templates/<Module>/`（工程覆盖层）→ 包内模板目录。**不再在保存时复制模板**，痛点 P5 消失。
- **link 模式不再用符号链接**：`module_libraries` 直接写外部库的路径（相对或绝对），痛点 P6 消失。
- **工程根目录**一律取 `.dpa` 所在目录，删除生成器“往上找 `Def`”的推断（P4）。
- `gen/` 的布局由 `.dpa` 字段决定：平铺（与 DaVinci GenData 一致，SIP spec 已定为新工程默认）或按模块分子目录（旧工程保持）。

### 6.7 `.dpa` format 8 新增内容

```json
{
  "format_version": 8,
  "directories": {
    "config": "config", "base": "config/base", "templates": "templates", "gen": "gen", "gen_layout": "flat",
    "chips": "chips", "integration": "integration", "system": "system", "history": ".history"
  },
  "module_libraries": [
    {"path": "modules", "kind": "package"},
    {"path": "../shared/EbPlugins/eclipse/plugins", "kind": "eb-plugins", "exclude": []}
  ],
  "modules": [
    {"name": "Mcu", "definition": "/THA6_AS440_FuSa/Mcu", "library": 1,
     "config_path": "config/Mcu.arxml",
     "pre_unlocked": [],
     "package_record": {"sw_version": "1.2.0", "files": {"config/Mcu.xdm": "sha256:..."}}}
  ]
}
```

- `modules` 就是“已激活模块”的权威清单。模块通过 `definition` 在库中定位，不再保存定义文件路径。
- `package_record` 实现 SIP spec R4：打开工程时与库比对，变化需要提示并经用户确认，不静默采用。值层面的变化由 §6.5 的三方合并处理，两者配合使用：前者告诉用户“包变了”，后者告诉用户“哪些值因此变了”。
- `pre_unlocked`：用户解锁的 Pre 参数路径（D1 选 C 时使用）。
- 其他现有字段（变体、芯片、memmap_* 等）保留。`memmap_*` 的相对路径基准不变，只是推荐放在 `integration/` 下。

### 6.8 添加、删除模块

- **添加**：在“可用模块”对话框中勾选 → 计算基线（默认值 ⊕ Rec ⊕ Pre，D8）→ 以基线作为活配置初值，并写入基线快照 → 登记到 `modules`。旧的“选文件添加”保留为“从文件添加…”，所选目录会被当作一个临时包（推断清单）。
- **删除**：先把该模块的配置写到 `.history/deleted/<Module>_<时间戳>.arxml`，再执行现有的 `remove_module`（它已经会清理悬空引用）。可以从历史中恢复。

### 6.9 旧工程兼容与迁移

- format ≤ 7 的工程：按原逻辑打开（`def_path`、`ConfigValue/`、`templates/`、`generateCode/`），**不应用 PRE**。目录表取旧目录名作为默认值，生成结果不变。
- 提供“升级工程结构”命令（显式操作，不自动执行）：
  1. 识别每个模块的 `def_path` 所在包（EB 插件目录、普通目录）；
  2. 生成 `directories` 和 `module_libraries`，**不移动用户文件**，旧目录名直接写进目录表；
  3. 比较 `templates/<Module>/` 与插件的 `generate_PB/`，内容相同的文件标为“可删除的副本”，不同的文件保留为工程覆盖层，并列入报告；
  4. 对有 Pre 的模块走预演，用户逐个模块确认是否启用。启用后才生成 `config/base/<Module>.arxml`；没有基线时，现有值一律视为用户值（§6.5）；
  5. 用改造前后的生成结果做逐文件比较，报告差异。
- “重命名为新目录名”是可选的第二步，由用户决定。

### 6.10 外部来源接入

| 来源 | 方式 |
| --- | --- |
| EB 插件目录 | 作为 `eb-plugins` 库直接引用（link），或复制到 `modules/`（copy）。无需改造。 |
| EB 工程 | 现有 `import_eb_project` 保留。改为：插件目录登记为库，`.epc`/`.xdm` 值导入 `config/`，**不再复制模板**，`PreConfiguration` 按 §6.5 处理而不是跳过 |
| Vector SIP 组件 | **入库**（一次性）：<br>1. 选择组件。<br>2. 从 IMPL 的 Pre/Rec 引用得到路径，**按内容**收集 SIP 中所有含这些路径的文件，包括其他组件目录里的，例如 vBaseEnv 目录下的 vBRS pre。<br>3. 选衍生芯片子目录：用芯片数据中的 Vector 衍生芯片标识（vBRS spec §11 新增的字段）查 `DerivativeMapping_*.xml`，规则照搬 SIP spec R2：查不到就报错；没有映射文件的子目录全部收进来并标为“推断”；可以逐组件覆盖。<br>4. 复制进 `modules/<Module>/config/`，写清单，记录每个文件在 SIP 中的原始位置和哈希。SIP 本身不改动。 |
| DaVinci 工程 | 在入库的基础上：按 `<ECUC><Active>` 把用到的组件入库，导入各模块的 `*_ecuc.arxml` 值，MCAL 走 EB 插件（沿用 SIP spec R6 的决定和导入报告要求）。导入的值作为 Active。**Base 由本工具按入库后的包重新计算**，不使用 DaVinci 的 InitialEcuC：InitialEcuC 只覆盖 10 个通信模块，而且含有推导值，本工具目前不做推导。所以导入后各模块按“旧工程迁移”处理，只有 Pre 会改值，而且必须先预演。导入报告还要列出 Active 与 Pre 不一致的地方：这在 DaVinci 中本不应出现，出现就说明入库规则有偏差 |

入库把 SIP 的复杂性（跨目录、衍生芯片子目录、命名空间合并）**限制在一次性工具中**：

- 出错时有完整报告，可以重做；
- 运行时加载逻辑保持简单；
- 升级 SIP 时重新入库即可，§6.7 的 `package_record` 会提示哪些模块发生了变化。

---

## 7. 与已有 spec 的关系

| 文档 | 处理 |
| --- | --- |
| SIP spec（2026-11-08，含修订） | R1、R4、R5、R6 和反目标并入本方案；R2/R3 的“运行时扫描 Vector 布局与跨组件合并”由入库代替，其中衍生芯片子目录规则原样用于入库；“组件内 `Templates/` 目录”改为包内 `templates/`；`Mcal_Tha62x` 的排除规则保留（§6.3）；第 2 节的 11 项路线采纳为本方案第 8 节；第 8 节“不缓存旧定义快照”与本方案的基线值快照不冲突，见 §1.4 |
| DaVinci 集成机制总结（修订版） | 基线层（§6.5）参照其中的 InitialEcuC → BaseEcuC → ActiveEcuC；Pre/Rec 规则与优先级以 PDF 写明的为准 |
| vBRS EB 模板 spec（2026-11-06） | 不变。vBRS 作为第一个 Vector 入库试点 |
| 合并功能方案（2026-10-24） | 作为长期路线；本方案的 `DERIVED` 来源为它预留位置 |
| `openspec/project.md` “不提供运行时默认模板” | 不变。包内模板属于用户加载的资料，不是内置模板 |

---

## 8. 集成能力路线图

本方案是集成能力的底座。下表采用 SIP spec 修订版第 2 节的 11 项，并补上每一项依赖本方案的什么：

| 顺序 | 能力（取代 DaVinci 的哪部分） | 依赖本方案的什么 | 难度 |
| --- | --- | --- | --- |
| 1 | **模块包 + Pre/Rec + 基线层 + 目录重整（本方案）**；取代本体的 SIP 扫描、BSWMD 合并、工程加载 | — | 见第 9 节 |
| 2 | MemMap 汇总（`Common_MemMap.jar`） | 包内 IMPL 中的内存段（§6.2） | 中 |
| 3 | 链接文件、Makefile、文件清单（`vLinkGen.jar`、`vBRS.jar` 的构建输出） | 包清单中的 `implementation`、`integration/` | 中（链接文件生成器已有） |
| 4 | 各模块配置模板 + 生成前预计算 | 包内 `templates/` 和工程覆盖层（§6.6） | 中高（逐模块） |
| 5 | 校验框架 + 规则；包括 vBaseEnv 式“配置级芯片选择要与 `selected_chip` 一致” | 值来源（§6.5），用于区分“预设错”和“用户改错” | 高（规则量大） |
| 6 | 跨模块自动补全（修复动作的等价物），要可预览、可追溯、可撤销 | 基线层中的 `DERIVED` 层；预演/确认/报告机制直接复用（§6.5） | 高 |
| 7 | BSW Internal Behavior + SchM | 包内 IMPL 承载 jar 原来登记的独占区和 TimingEvent；结果放在 `system/` | 高 |
| 8 | Service SWC 生成 | `system/` | 中高 |
| 9 | RTE，以及由 RTE 反推的 OS 配置（自研内核） | `DERIVED` 层，回写 Os 时不覆盖用户值 | 很高 |
| 10 | 系统描述导入与推导 | `DERIVED` 层，相当于 InitialEcuC，直接放进基线（§6.5 的结构就是为它预留的） | 很高 |
| 11 | BSWMD 版本迁移（可选） | `package_record` 和三方合并已覆盖“值跟随新默认值”；结构性迁移（参数改名、移动）另做 | 中 |

第 5～11 项的次序，按 SIP spec 的建议，由“导入后最常做的修改”决定。**用户 2026-11-09 答复：导入后改得最多的是 Os、通信矩阵和 Runnable。**

这三类修改分别落在：

- Os：第 5、6、7 项；
- 通信矩阵：第 10 项；
- Runnable：第 8、9 项，第 9 项还会反推 Os。

它们都要求推导结果写入基线的 `DERIVED` 层，并在下次推导时**保留用户修改**，也就是 DaVinci InitialEcuC 解决的问题。因此：

- **本方案的基线层，从第一版起就按“可插入多层”实现**：默认值、Rec、Derived、Pre 各为一层。本轮 Derived 层为空，但接口和三方合并都要支持它。实施计划中把这一点列为阶段 1 的验收项，避免日后为推导返工。
- **建议的次序**（仍需用户确认）：
  1. 第 5、6 项的 Os 部分：校验框架，加上 Os 自动补全；Derived 层第一次真正使用。
  2. 第 7 项：SchM，MainFunction→Task。
  3. 第 10 项：通信矩阵（DBC/SystemExtract→Com/PduR/CanIf/CanSM…）。现有 `core/importers/dbc_importer.py` 只是按列映射导入表格，没有推导，这一项要从头建。
  4. 第 8、9 项：Service SWC 和 RTE（Runnable→Task→Os）。本工具目前没有 SWC/Runnable 模型，这一项要从头建，难度最高。
  5. 第 11 项。
- 通信矩阵和 Runnable 谁先做，取决于哪一个更痛。如果 Runnable 更急，就把第 4 步提到第 3 步之前。

原来按“只改 Os”给出的安排如下，Os 部分仍然适用：

- **第 5、6 项先做 Os 相关部分**：
  - 校验：Os 修改后，与 vBRS 核配置、存储布局（栈、内存区）、ARTI、芯片资源保持一致；
  - 自动补全：Os 的空闲任务、栈、自旋锁、内存区，以及 Os 核映射变化后对 vBRS、链接文件的联动。
  - 其他模块的规则随后补上。
- **第 7 项（SchM：MainFunction→Task、独占区）提前到第 6 项之后紧接着做**：它直接决定 Os 的任务和事件。
- **第 9 项中的“RTE 反推 Os”**：依赖第 8 项（Service SWC），顺序不变。但是 Os 侧的“推导层写入、不覆盖用户值”机制，在第 6 项中就先建好。
- 第 10、11 项排在最后。

已有基础：本工具的 Os 是自研内核，Os 模板、ARTI、存储布局和链接文件生成器都已经有了，所以第 5、6 项的 Os 部分可以直接复用这些数据。

---

## 9. 实现难度与工作量

估算按一名熟悉本仓库的开发者计，含单元测试，不含上板。“难度”指技术不确定性和对现有代码的牵连范围。

| # | 工作项 | 难度 | 估算（人日） | 主要难点 |
| --- | --- | --- | --- | --- |
| W1 | `.dpa` format 8 目录表，替换 20 多处写死路径，删除工程根推断 | 中低 | 3–4 | 路径分散，UI 和生成器都有；要保证旧工程的默认值完全等价 |
| W2 | 模块包解析：`module.json`、`plugin.xml` 推断（含 `autosar/` 副本的处理）、按路径判定角色、芯片条件选文件、包内按路径合并 | 中 | 5–6 | `plugin.xml` 变体多；一个文件同时含 Pre 和 Rec；推断出错必须报出来，不能吞掉 |
| W3 | 模块库扫描与“可用模块”对话框 | 中低 | 3 | 扫描性能（只读清单） |
| W4 | 基线层：合成 Base'、基线快照读写、三方合并、预演/确认/报告、由比较得出值来源、只读锁定 | **高** | 9–12 | 容器实例按名字对齐（含 Pre 新增和删除的容器）；多值参数和引用的比较；只读在命令层统一拦截；EB xdm 与 arxml 两种 pre 格式 |
| W5 | REC：添加模块和新建容器时作为初值；拆开现有 Pre/Rec 混合逻辑 | 中 | 2–3 | 容器级 REC 匹配规则（基线层已承担一部分） |
| W6 | 模板查找改为“覆盖层 → 包”，取消保存时复制 | 中 | 2–3 | 生成器指纹：模板来源路径变化不能导致指纹变化 |
| W7 | 删除归档与恢复 | 低 | 1–2 | — |
| W8 | 旧工程“升级工程结构”命令和生成结果比较 | 中 | 3–4 | 模板副本与覆盖的区分；必须做到零差异 |
| W9 | EB 工程导入适配（登记库、不复制模板、处理 PreConfiguration、去掉符号链接） | 中 | 3 | 兼容现有 copy/link 两种模式的工程 |
| W10 | 包外 IMPL 内容（内存段、依赖头文件）的模型查询接口、ECUC-MULTILINE-STRING | 中 | 2–3 | 供 MemMap 子项目使用的查询接口设计 |
| W11 | Vector SIP 入库工具（按 IMPL 引用路径收集、跨目录、DerivativeMapping、报告） | **高** | 6–8 | SIP 规模（数百文件）；规则依据部分是推断（SIP spec 5.2 “未反编译确认”） |
| W12 | DaVinci 工程导入（基于 W11；Active 与 Pre 的一致性报告） | 中高 | 4–6 | MCAL 三份配置不一致，需要用户指定来源；导入后逐参数自动比较 |

合计约 **43–57 人日**，测试与回归另加约 20%。

**分阶段交付**（每阶段都能单独使用）：

| 阶段 | 内容 | 交付给用户的价值 | 估算 |
| --- | --- | --- | --- |
| 阶段 1 | W1、W2、W4、W6、W9 | **满足本次核心诉求**：define 与 pre 同目录，pre 自动导入并受基线保护，目录清晰；EB 插件立即可用（含 `McuPreConfiguration`） | 22–28 人日 |
| 阶段 2 | W3、W5、W7、W8 | 可用模块清单、推荐值、删除归档、旧工程一键升级 | 9–12 人日 |
| 阶段 3 | W10、W11、W12 | Vector 组件和 DaVinci 工程接入；vBRS 作为试点 | 12–17 人日 |

难度最高的两处：

1. **W4 三方合并的正确性**：值的比较要覆盖单值、多值、引用和容器实例。做法是把合并做成与 UI 无关的纯函数，用表格驱动测试覆盖 §6.5 表格中的每一种情形；只读锁定只在命令层拦截，避免漏掉入口。
2. **W11 入库规则的不确定性**：“没有映射文件的子目录总是加载”等规则来自样例推断。做法是入库后与 DaVinci 的 `*_ecuc.arxml` 逐值比较，作为入库规则的验收标准。W12 的“Active 与 Pre 一致性报告”就是这项比较的自动化。

---

## 10. 风险与缓解

| 风险 | 影响 | 缓解 |
| --- | --- | --- |
| PRE 覆盖了旧工程中用户改过的值 | 生成结果变化 | 首次启用必须预演和确认；旧工程默认不启用；生成结果逐文件比较（W8） |
| 基线快照丢失或被手改 | 用户改过的值被误判为“未改”，从而跟随新基线 | 快照丢失时按“旧工程迁移”处理（全部视为用户值）；快照内容带哈希，打开时校验，不一致时同样按迁移处理 |
| 三方合并的容器对齐错误（例如重命名的容器被当成删除加新增） | 值丢失 | 删除一律不自动执行，只报告；合并结果先预演 |
| 推断的清单不准确 | 加载了错误的 pre，或漏掉了 pre | 推断结果在界面上标“推断”，并可写成清单；同角色出现多个候选时报错 |
| 模板来源变化导致生成器指纹变化 | 不必要的重新生成，或误判“未变化” | 指纹只按模板内容计算；对现有工程做指纹前后比较的回归测试 |
| 目录结构改变，影响用户脚本和习惯 | 用户困惑 | 旧工程不强制迁移；重命名是独立的可选步骤 |
| 入库复制了 Vector 文件 | 许可、仓库体积 | 包放在工程或用户指定的库中，**不进本工具仓库**（沿用 SIP spec 非目标） |

---

## 11. 需要你决定的问题

| # | 问题 | 选项 | 我的建议 |
| --- | --- | --- | --- |
| **D1** | Pre 值的语义 | A. 与 DaVinci 相同（PDF 3.1.1 写明）：每次加载都应用，只读；差异进报告<br>B. 只在添加模块时应用一次，之后可编辑<br>C. 默认按 A；允许对单个参数“解除锁定”，解锁记录写入 `.dpa` 的 `pre_unlocked` | **已定（用户 2026-11-09）：C**。EB 的 `preconfig default="true"` 也按 C 处理；它在 tresos 中的确切语义仍未核实，实施时如果能用 tresos 验证，就记录结果，结果与 C 不一致时再提出 |
| **D2** | 模块包放在哪里 | A. 复制进工程 `modules/`（自包含）<br>B. 引用外部共享库<br>C. 两者都支持，新建工程时选择 | **已定（用户 2026-11-09）：C**，默认 A |
| **D3** | Vector SIP 的接入方式 | A. 一次性入库为模块包（本方案）<br>B. 运行时扫描 SIP（SIP spec R2/R3） | **已定（用户 2026-11-09）：A** |
| **D4** | 新工程目录名 | A. 采用 §6.6 的新名字（`config/`、`gen/`、`modules/`…）<br>B. 沿用旧名（`ConfigValue/`、`generateCode/`、`Def/plugins/`） | **已定（用户 2026-11-09）：A**；旧工程不受影响 |
| **D5** | 新工程生成目录的布局 | A. 平铺<br>B. 按模块分子目录 | **已定（用户 2026-11-09）：A**。现有 THA6206 工程的 Makefile 是否兼容，在实施中验证；不兼容时，按模块分目录仍可作为工程级选项 |
| **D6** | 路线图（第 8 节，即 SIP spec 的 11 项）的顺序，尤其是第 5～11 项 | **用户 2026-11-09 答复：导入后改得最多的是 Os、通信矩阵和 Runnable**。第 8 节已给出建议次序；“通信矩阵和 Runnable 谁先做”待确认。这一项不影响阶段 1 |
| **D7** | 是否引入基线快照 `config/base/<Module>.arxml` | A. 引入（§6.5，三方合并，升级时用户改过的值不丢）<br>B. 不引入，只记 pre 文件哈希（原稿做法：Rec 或默认值升级时无法判断哪些值可以跟随） | **已定（用户 2026-11-09）：A，引入** |
| **D8** | 添加模块时是否默认用 Rec 初始化 | A. 默认用（与 DaVinci 相同）<br>B. 默认不用，可以勾选 | **已定（用户 2026-11-09）：A，默认用** |

---

## 12. 验收标准（阶段 1）

1. 一个 EB 插件目录不做任何修改，作为 `eb-plugins` 库加入新工程。添加 Mcu 后：
   - `McuPreConfiguration` 中的复位原因表出现在配置树中，灰显只读，来源显示为 PRE；
   - `autosar/Mcu_<芯片>.arxml` 没有被加载，并在来源界面中列为“交换副本”。
2. 手工构造一个包：define 与两个芯片的 pre 放在同一个 `config/` 目录中。
   - 切换芯片后，加载的 pre 随之切换；
   - 两个 pre 都匹配当前芯片且同一参数取值不同时，报错并指出路径和两个文件。
3. 构造一个同时含 `X_Pre` 和 `X_Rec` 的值文件：两者分别按 Pre 和 Rec 处理，不会因文件名带 `_pre` 而把 Rec 也当作 Pre。
4. 三方合并：在包中修改一个 Rec 值、一个 Pre 值后重新打开工程。
   - 用户没改过的 Rec 值跟随变化；
   - 用户改过的 Rec 值保留，并出现在报告中；
   - Pre 值被强制改变，并出现在报告中；
   - 所有变化先预演，拒绝后 Active 和 Base 都不变，下次打开继续提示。
5. 现有旧工程（含 EB copy/link 导入的工程，例如 `test_project_relocation`、用户的 T1/T2 工程）照常打开；不启用 PRE 时，生成结果与改造前逐字节一致，指纹不变。
6. 在 `templates/<Module>/` 中修改一个模板后保存工程：修改不被覆盖，生成时使用修改后的模板。
7. 全仓库搜索不到写死的 `ConfigValue`、`generateCode`、`Def/plugins`（旧格式默认值表除外）。
8. 现有测试全部通过（已知的无关失败除外）。
