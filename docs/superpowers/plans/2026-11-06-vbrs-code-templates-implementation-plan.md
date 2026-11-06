# vBRS 全配置覆盖与逐文件等价生成 Implementation Plan

> **For agentic workers:** 实施时使用 superpowers:executing-plans 按任务执行；若用户选择并行方式，再使用 superpowers:subagent-driven-development。当前仅提交方案，未获批准前不写产品实现。

**Goal:** 覆盖当前两个 vBRS JAR 涉及的全部可配置行为，为每一种实际生成文件提供模板，并以配置驱动的原文件对照证明输出一致。

**Architecture:** ECUC 定义/值及跨模块元数据 → 显式配置辅助与校验 → 版本化规则上下文 → 输出清单 → 逐文件模板。模板处理条件、循环、文本；引用解析、数值运算和初始化排序由随模板包交付的规则层负责，不把现有生成文件作为运行时输入。

**Tech Stack:** 项目现有 Python、ECUC ARXML、轻量 TemplateEngine、pytest；JAR/javap 仅用于离线规则恢复，不新增生产运行时 Java 依赖。

**Spec:** openspec/changes/add-vbrs-code-templates/specs/vbrs-code-generation/spec.md；设计 docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md（2026-11-06 修订）。

## Global Constraints

- 用户两条硬要求：所有 JAR 可配行为全部覆盖；配置生成结果与已有代码一致。只复制当前样例、只实现已启用分支都不合格。
- 覆盖 GeneratorMsr 14.09.01 与 GeneratorDvC6 14.09.02，使用明确分离的 profile；MSR 先完成现有样例回归，不以此把 DvC6 降为范围外。
- 只从用户显式选择的外部模板目录加载，不恢复默认回退模板；不把九个静态 BrsMain 实现文件算作生成输出。
- 不修改 D:/davinci 原始文件；不覆盖现有 EB 相关未提交修改；不擅自运行原生成器或分发整套厂商 SDK。
- 未解析的活动规则必须报错；但“拒绝未实现分支”只是安全措施，不能算全量交付完成。
- 新工具不冒充 Vector 生成器；回归重放元数据与实际生产生成身份分离。

## Review Focus

1. 容器缺失 vs 值 false vs 无默认值：不能自动补出驱动/板卡/Stub（任务 2、4）。
2. CAN/Ethernet 两实例及非连续核号：不能按数组位置代替硬件 ID，不能合并实例（任务 3、4）。
3. 64 位整数与多行 Makefile：不能经浮点丢精度或被再次当作模板执行（任务 2、4）。
4. 同名 EcuM/RTE 文件与多目标目录：不得覆盖别的生成器输出或越界写入（任务 6）。
5. 预设、Mcu 引用及外部模块变化：不得静默覆盖用户值，缓存不得复用旧上下文（任务 3、6）。

---

## 一、交付物与“全覆盖”定义

交付的是 **两份版本化模板包 + 配套规则/校验能力 + 覆盖台账 + 原工具对照报告**，而不是只交十个带占位符的文件。

本轮盘点结果：

| 配置域 | 定义叶项数 | 具体范围 | 实现去向 |
|---|---:|---|---|
| vBRSGeneral | 24 | 特性开关、执行实例、FBL、Dio、vLinkGen 变体、初始化阶段覆盖 | Cfg/Make/EcuM/SchM、配置辅助校验 |
| vBRSHwConfig | 126 | 时钟、指令集、FPU、硬件初始化、七类驱动、板卡、项目/编译器/用户 Makefile | Cfg/Make、时钟和板卡解析 |
| vBRSTestsuiteSupport | 1 | 测试支持开关及容器存在性 | Cfg/EcuM |
| vBRSMemoryInit | 6 | 四个填充值、64 位模式、全局禁用 | Cfg、vLinkGen 约束校验 |
| vBRSVeHaasSupport | 100 | Assembly 选择、板卡、derivative、LED/自定义脚、驱动预设 | 预设解析/配置建议 → 常规模板 |
| **合计** | **257** | 203 Boolean、22 Integer、9 String、7 Enum、1 多行文本、15 Reference | 逐项附件，不合并计数 |

另有 **22 个容器定义**，包括 CAN/Ethernet 最多两个实例、初始化阶段覆盖和板卡/Assembly 的多记录结构。短名、实例数量、存在性也属于输入。

附件：
- [257 项逐项清单](2026-11-06-vbrs-config-inventory.md)：逐项名称、类型/默认、输出目标、实现策略、全部枚举、容器数量限制。
- [机器可检查清单](2026-11-06-vbrs-config-inventory.json)：完整定义路径、上下界、引用类型、描述、两个 JAR 的字段/类/方法证据、测试 ID 与状态。

**重要边界：257 是本份 vBRS 定义的叶项数，不是 JAR 全部输入数。** 两个 JAR 的定义常量均映射这 257 项；256 项在规则反汇编中找到名称/字段访问，剩余 PeriphClockDescription 暂只见说明性定义。访问出现不等于规则分支已完整恢复。全覆盖最终还必须封账下面的跨模块、动态读取、验证器、辅助方法和文件选择规则。

## 二、这些配置如何改变生成结果

### 2.1 通用配置（24 项）

- LED、SafeContext、多核、看门狗脚、自定义脚、首执行实例、Hypervisor guest：模板按有效配置输出存在型宏，Dio 引用先解析真实通道符号/供应商前缀。
- ExecutionInstance 九值全覆盖：Application、FBL、FBL_Updater、BM、BM_FBL、HSM、HSM_Updater、FlashDriver、Hypervisor。对每值验证宏、构建变量和初始化路径；不能靠字符串包含 FBL 粗略判断。
- FblSupportEcuMInit、FblSupportExceptionTableInRam：在原 JAR 的 FBL 条件内选择初始化入口和 RAM 异常表支持，不能对所有实例生效。
- EcuM/SchM Stub 开关控制整个输出文件集合；SchM 另有 CAN Application Note 排除规则和空 exclusive-area 模式。
- UserConfigFile 输出 include；VariantUsageOfvLinkGen 解析所选变体，影响头文件和链接命令后缀。
- OverrideInitPhase 的 InitFunction 引用与 InitPhase 成对解析。17 阶段全部支持：NO_INIT、INIT_MEMORY、INIT_ZERO、INIT_ONE_EARLY、INIT_ONE、INIT_ONE_LATE、INIT_TWO_MCAL、INIT_TWO_TRCV、INIT_TWO_DRV、INIT_TWO_IF、INIT_TWO_COM、INIT_TWO_SM、INIT_TWO_NM、INIT_TWO_TP、INIT_TWO_SYS、INIT_TWO_POST_NVMREADALL、INIT_THREE。排序、覆盖冲突和 NO_INIT 省略语义按 JAR 恢复。
- DisableSetupSupport、EnableCoreSpecificVLinkGenConfig、EnableSmallDevicesOptimization 是配置辅助/校验行为，不伪造成不存在的 C 宏。配套层负责 setup 开关、核与链接配置一致性、单核 SC1 栈/Hook 优化建议，并给出作用记录。

### 2.2 硬件配置（126 项）

**公共项：** Osc/Timebase/Periph 三种时钟；Port/Watchdog/PLL/PreferPLLWatchdogInit 四开关；THUMB/ARM/VLE/BOOKE/RV32I 指令集；FPU；Mcu 频率引用；板卡引用和板卡名/说明/振荡频率；CompilerPath、ProjectName、MakefileUserCode；PeriphClockDescription 说明。

**驱动项：**

| 驱动 | 项数 | 通道/端口 | 附加配置 |
|---|---:|---|---|
| CAN | 25 | channel0–19，逐项布尔 | 开关、公共/独立时钟、时钟值/引用、MCAN/XCAN/RCAN/FlexCAN/RSCAN；0–2 实例 |
| LIN | 27 | channel0–22 | 开关、公共/独立时钟、时钟值/引用 |
| Flexray | 8 | 0A/0B/1A/1B | 开关、公共/独立时钟、时钟值/引用 |
| Ethernet | 22 | Port0–15 | 开关、公共/独立时钟、时钟值/引用、SwitchSupport；ETNA/ETNB/ETNF/GETH/GMAC/LETH/RSWITCH2；0–2 实例 |
| Hyperbus | 6 | channel0–1 | 开关、公共/独立时钟、时钟值/引用 |
| I2C | 15 | channel0–10 | 开关、公共/独立时钟、时钟值/引用 |
| Spi | 5 | channel0 | 开关、公共/独立时钟、时钟值/引用 |

模板循环经过验证的实例/通道列表，但保留每个原配置项独立控制能力。实例前缀、宏名和父子条件取 JAR，不直接从参数名/定义描述拼猜。已发现 LIN channel17 的描述误写 channel10，因此说明文档不能作为唯一生成规则。

**已确认的规则例子：**
- PLL true 输出 #define BRS_ENABLE_PLLCLOCKS；false 不输出该宏，不能输出为 0。
- 非负时钟 Hz 能整除 1,000,000 时输出 MHz 数值，否则保留 Hz；数值与单位一起匹配。25,000,000 → 25 MHz；25,000,001 → 25,000,001 Hz。
- Mcu clock reference 的定义涉及 solving-action 复制，不等于每次生成都自动覆盖显式时钟。恢复触发条件/优先级后实现显式配置建议，未确认前不得任选一个值。
- 板卡记录列表不等于已选择板卡；当前样例有 THA6206/THA6412 两条记录但没有板卡引用，不能取第一条。

### 2.3 内存与 veHaaS

四个初始化 pattern 均为整数，定义上限 18446744073709551615。使用无损整数，按 32/64 位模式恢复十六进制格式、后缀和越界语义；64 位模式须核对 vLinkGen。全局禁用仅生成相应控制，不改写 BrsMain 静态实现。

veHaaS 100 项包括 Assembly 选择 1、基本信息 5、CAN 23、LIN 25、Flexray 6、Ethernet 20、Hyperbus 4、I2C 13、Spi 3。不是 100 个独立输出宏：选中预设后将其字段映射到实际 vBRS/vBaseEnv 配置，再走普通模板。须覆盖板卡/derivative 查找失败、同名歧义、显式值冲突、双实例及预设切换。先展示需要改变的值，再明确应用或报冲突；不在渲染时悄悄修改源配置。

### 2.4 JAR 还会读取的外部输入

以下是已发现的输入族，实施任务 1 必须展开到具体路径/元数据字段及测试；本表不是宣称外部项已枚举完毕。

| ID | 输入来源 | 需恢复的可配置内容 | 影响输出 |
|---|---|---|---|
| E01 | vBaseEnv | derivative/说明、CPU 类型/核数/启动核/频率、启动栈、derivative 与 clock/pll/port/protection/reset/watchdog/opmode/usermodeaccess/powerdown 分组 | Cfg、Lc/Lh、Make |
| E02 | Os、EcuC、VHyp | 物理/逻辑核映射、ASR 核属性、核引用/排序；OS 中断支持与相关元数据 | Lc/Lh、Cfg、Make、EcuM、SchM |
| E03 | vLinkGen | 变体、逻辑组/段组/栈名和大小、异常向量/中断向量符号、64 位模式 | Lc/Lh、Cfg、Make |
| E04 | Dio | 通道实例名、API 前缀及绑定引用 | Cfg |
| E05 | Mcu | McuClockReferencePointFrequency 及引用目标、复制校验 | 时钟配置 → Cfg/Make |
| E06 | vSet | InitFunction/Header/ModuleRef/ConfigType/Instance/ConfigPtrName/InitPhase/AdditionalInitCode | EcuM.c |
| E07 | EcuC 初始化模型 | 无 vSet 时的初始化输入、PDU collection 及配置结构/变体相关信息 | EcuM.c/h |
| E08 | EcuM | WakeupSource/Id、真实模块存在性与 Stub 关系 | EcuM_Generated_Types.h 及文件选择 |
| E09 | 模块 BSWMD、Rte/Os | API infix、vendor/module ID、MemMap、internal behavior、exclusive areas/entities、Rte 启动/存在性 | SchM、EcuM、Cfg |
| E10 | 模块存在性/仿真特性 | Adc/Dio/Eep/Fee/Fls/Gpt/I2c/Icu/Mcu/Port/Pwm/Spi/Wdg 的 EmulationFeature，Det/EcuM/EcuC/vSet/Rte 等存在条件 | Stub/初始化/头文件相关分支 |

不能只看编译后的 JET/Groovy 模板。BrsGenerationProcessor、BrsDataRep、BrsEcuMStubDataRep、工具类、验证器/solving-actions 中的派生条件、初始化函数调用和 C 文本拼接都在覆盖范围内。未影响任何输出的辅助配置也必须给出独立作用及测试，不能直接忽略。

## 三、每个文件的模板职责

两个 profile 各提供以下十种模板；共用规则只能在双版本证据证明一致后抽取。输出内容属于模板，不把整个文件预先拼成一个字符串再放入空壳模板。

| 生成文件 | 模板 | 配置实现 |
|---|---|---|
| vBrsCfg.h | vBrsCfg.h.tpl | 条件宏、执行实例、所有硬件/驱动通道、时钟单位、Dio、CPU/derivative、内存模式和用户 include |
| vBrs_Lcfg.c | vBrs_Lcfg.c.tpl | 循环有序 coreData；实际物理/逻辑 ID、ASR 属性、栈/向量符号及大小、FBL RAM 表分支 |
| vBrs_Lcfg.h | vBrs_Lcfg.h.tpl | 与 C 使用同一 coreData 和数量，输出类型及 extern 声明 |
| Makefile.config.generated | Makefile.config.generated.tpl | 时钟/CPU/核使用、板卡和分组、指令集/FPU、Stub/实例、链接变体、编译器路径/项目名、多行用户内容 |
| EcuM.c | EcuM.c.tpl | init 列表/头文件、阶段覆盖、参数/配置指针、去重、post-build 变体、StartupTwo、Rte、FBL、多核和 testsuite |
| EcuM.h | EcuM.h.tpl | PDU collection、类型/接口及多核分支 |
| EcuM_Cbk.h | EcuM_Cbk.h.tpl | 已检查 MSR JET 未见数据模型读取，按固定正文 + 条件文件选择处理；DvC6 单独核定 |
| EcuM_Error.h | EcuM_Error.h.tpl | 同上，不为了“可配置”虚构可变常量 |
| EcuM_Generated_Types.h | EcuM_Generated_Types.h.tpl | wakeup source/ID 和派生类型规则 |
| SchM_<module API name>.h | SchM_Module.h.tpl | 按行为实例展开；模块命名、exclusive areas/entities、AN 排除、空宏/中断策略、MemMap |

EcuM 输出选择包括 Stub 开关和 EcuC 可识别条件。两个版本均有 SchM 行为非空判定（exclusive areas 或 entities 非空），不能误说仅 DvC6 有。精确目录逐版本由输出类构造器核定；已确认 MSR SchM 指向 GenData 的兄弟 Include，通过目标根映射实现，不原样拼接 .. 路径。

## 四、如何验收“与已有代码一致”

### 4.1 当前四文件黄金回归

输入来自 StartApplication/Config/ECUC，包括 vBRS 和被引用模块；预期输出来自 Appl/GenData/vBrsCfg.h、vBrs_Lcfg.c、vBrs_Lcfg.h 与 Appl/Makefile.config.generated。附件已保存它们和两个 JAR/定义的 SHA-256。本轮复核八个既有来源哈希未变化；跨模块输入快照还需补齐。

当前可用的对照点（不是硬编码规则）：
- 25 MHz Osc、400 MHz Timebase、25 MHz Periph；ARM、FPU。
- Tongxin_THA6206、CORTEX_R52、2 核；core 0/1 两条 ASR 记录，样例栈大小 1024u。
- FirstInstance=true、MultiCore=true、Application，四个 pattern 为 0，PLL/Port/Watchdog 与两类 Stub 为 false。
- Lcfg C/H 数量一致；Make 中 0/1 核启用，样例 2–7 未启用。

必须先核对配置与原输出是否同批生成；若不一致，应取得匹配输入或明确报告来源问题，不能写死旧输出以通过比较。

### 4.2 精确一致与正常生成身份

1. **黄金回归重放模式：** 冻结明确列出的时间/工具元数据，并保持原编码、BOM、换行、空白和最终换行；四个文件逐字节比对，零差异才通过。原工具身份只作为测试 fixture 重放，不作为本工具正常产物的身份。
2. **正常生成模式：** 使用本工具真实身份；正文、宏存在性、注释中的单位、符号/顺序、声明、数值、函数调用、Make 内容均须一致。只允许逐字段登记的生成身份/时间差异，报告原始 diff 和允许差异；不删光注释、不排序行、不做宽泛归一化。
3. 如无法冻结某字段，报告不满足“逐字节一致”，不能把语义相近称为完全相同。

### 4.3 未启用分支与双版本

- 当前没有经确认的 vBRS EcuM/SchM Stub 原始输出。现有 SchM_Mcu.h 来自 RTE，同名 EcuM 类型头来自 EcuM，不能冒用。
- 对这些输出先做字节码规则/模板测试；**全量原工具等价验收还需合法原工具产生的对应配置快照与输出**。没有样本时状态必须是“实现/规则测试完成，原工具等价未验证”，不宣布总目标完成。
- 所有 Boolean 测 true/false/缺失，枚举测全部值，通道逐个启停并测多实例，数值测边界；初始化 17 阶段、post-build、Rte、CAN AN、OS 中断模式、veHaaS 等组合按条件分支覆盖并增加关键交互测试。不能仅拿当前四文件覆盖率代替规则覆盖率。
- 两版本独立生成、独立报告；同配置不要求两个原 JAR 互相输出一致，而要求各模板与自己的 JAR 语义/基线一致。

最终通过条件：257 定义项及全部外部/动态规则已分类封账；无未实现可达分支；十类模板有测试；四份当前基线精确重放通过；Stub/版本差异的必要原工具基线对照通过；现有生成器回归通过。有限测试不是所有配置数学等价的证明，报告须列明覆盖的分支和输入域。

## 五、实现分解（审批后执行）

### 任务 1：规则台账封账与双版本差异

**Files:** 新建 autosar_configurator/generator/vbrs/rules/schema.json、rules/msr-14.09.01.json、rules/dvc6-14.09.02.json；tests/generator/vbrs/test_rule_inventory.py。方案附件是调查输入，不是自动判定通过的证据。

**Interfaces:** 每条 RuleRecord 含 id、profile、definition_paths/external_inputs、source_hash/class/method/offset、conditions、transform、targets、test_ids、status；规则与配置项多对多关联。

- [ ] 先写失败测试 test_all_definition_items_classified：257 条唯一完整路径全部关联规则或有证据的 no-output，不接受 unresolved 当完成。
- [ ] 写 test_all_dynamic_reads_classified：枚举两个 JAR 的 getter/DefRef/getParameter/动态路径、输出注册及文本拼接来源；任何未分类访问或分支导致审计失败。
- [ ] 从完整 javap 及数据辅助类逐分支恢复规则和两版本差异，补 E01–E10 具体路径；定义注释冲突由实际 JAR/原输出裁决并留记录。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_rule_inventory.py -q；审计通过才允许称“全量规则已恢复”。

### 任务 2：无损输入与多行配置通路

**Files:** 修改 autosar_configurator/core/parser/ecuc_def_parser.py；根据既有模型实际类型最小修改 definition_model.py/值序列化；新建 generator/vbrs/model.py、input_adapter.py；tests/generator/vbrs/test_inputs.py（上述 generator 相对 autosar_configurator）。

**Interfaces:** load_vbrs_inputs(all_configurations, definitions, metadata) -> VbrsInputs；保留 missing、原路径/短名、容器实例、无损整数、多行字符串和引用，禁止先转 float。

- [ ] 先写 test_missing_false_and_absent_container、test_uint64_exact（0、2^32−1、2^32、2^53+1、2^64−1/越界）、test_multiline_roundtrip；验证换行、引号、模板标记原样保留。
- [ ] 补齐多行定义解析/值读取保存，不更换现有模板引擎；对未知枚举、错误多重性、必需值缺失报定位错误。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_inputs.py -q，保存往返前后配置结构对比。

### 任务 3：预设/跨模块解析与规则上下文

**Files:** 新建 generator/vbrs/resolver.py、setup_rules.py、context.py、core_rules.py、ecum_rules.py、schm_rules.py；tests/generator/vbrs/test_context.py、test_setup.py、test_external_inputs.py。

**Interfaces:** propose_setup(inputs, profile) -> SetupResult（值变更建议及诊断，不修改输入）；build_context(inputs, profile) -> VbrsContext（brs/cores/ecum/schm/build 记录与依赖指纹）。建议明确应用后重新构建上下文。

- [ ] 先写 test_vehaas_conflict_no_mutation、test_board_not_selected、test_clock_reference_copy_not_silent_override；要求输入不被修改，冲突/缺失定位到完整路径。
- [ ] 写 test_noncontiguous_physical_cores、test_stack_reference_and_fallback、test_init_phase_override_all_17、test_config_pointer_dedup、test_all_execution_instances，按已封账规则断言顺序、符号和去重。
- [ ] 实现任务 1 确认的规则；时钟整除运算/大整数在规则层完成，模板不访问原始 ARXML、不运行任意表达式。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_context.py tests/generator/vbrs/test_setup.py tests/generator/vbrs/test_external_inputs.py -q。

### 任务 4：四个常规模板，全配置分支

**Files:** 两包 template_packs/vBRS-msr-14.09.01/vBRS/ 与 template_packs/vBRS-dvc6-14.09.02/vBRS/ 下的 vBrsCfg.h.tpl、vBrs_Lcfg.c.tpl、vBrs_Lcfg.h.tpl、Makefile.config.generated.tpl；tests/generator/vbrs/test_regular_templates.py。

**Interfaces:** 仅消费 VbrsContext 的验证后字段，所有模板分支关联 RuleRecord；使用现有轻量 TemplateEngine 支持的语法。

- [ ] 先写 test_pll_omitted_when_false、test_clock_units（25000000→25 MHz，25000001 保留 Hz）、test_all_driver_channels、test_two_can_eth_instances、test_memory_widths、test_core_c_h_agree、test_user_code_not_reinterpreted。
- [ ] 逐文件转写正文/条件/循环；禁止读取旧生成文件、把 25/400/2/1024 等样例值写成常量，禁止规则层吞并整个输出正文。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_regular_templates.py -q；每项清单关联实际模板分支及通过测试。

### 任务 5：五类 EcuM 与一类 SchM 模板

**Files:** 两包中的 EcuM.c.tpl、EcuM.h.tpl、EcuM_Cbk.h.tpl、EcuM_Error.h.tpl、EcuM_Generated_Types.h.tpl、SchM_Module.h.tpl；tests/generator/vbrs/test_stub_templates.py。

**Interfaces:** 消费 context.ecum 和 context.schm；输出族是否启用、SchM 重复记录由完整条件决定。

- [ ] 先写 test_ecum_requires_recognized_ecuc、test_vset_and_ecuc_init_sources、test_postbuild_variants、test_rte_start_once、test_wakeup_ids、test_schm_entities_only、test_empty_behavior_excluded、test_can_an_masks、test_empty_exclusive_area_mode。
- [ ] 固定正文模板保持固定；可变初始化调用/声明/宏在模板中显式循环，不为固定头虚构参数。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_stub_templates.py -q；未得到原工具样例不能标 baseline-compared。

### 任务 6：显式模板包接入、目录与输出所有权

**Files:** 新建 generator/vbrs/pack.py、output_plan.py；修改 autosar_configurator/generator/generator.py；两包 manifest.json；tests/generator/vbrs/test_pack_integration.py。

**Interfaces:** plan_outputs(context, manifest, roots) -> list[OutputSpec]，OutputSpec 指定 template、exact output_name、target root、单次/重复上下文；无任意脚本条件。先校验完整输出集合，再暂存渲染，失败不留下“成功”的半套新产物。

- [ ] 先写 test_exact_filename_without_module_prefix、test_dynamic_schm_name、test_path_escape_rejected、test_foreign_output_not_overwritten、test_render_failure_no_partial_outputs、test_external_change_invalidates_cache。
- [ ] 接入显式清单，旧模板仍走原发现机制；提供 application/gendata/include/source 根映射和输出预览；只有本包拥有的旧文件才可建议清理，不自动删除他人文件。
- [ ] 指纹包含模板/规则/profile、配置及实际引用模块/元数据；不只哈希 vBRS。
- [ ] 运行 python -m pytest tests/generator/vbrs/test_pack_integration.py tests/generator -q。

### 任务 7：原文件等价验收与交付报告

**Files:** tests/generator/vbrs/test_baseline_parity.py、fixtures/vbrs/manifest.json、docs/vbrs-template-coverage.md、docs/vbrs-template-usage.md；本地私有基线不随公共测试提交。

**Interfaces:** 基线 manifest 记录输入/输出哈希、生成器/profile、元数据冻结字段；compare_outputs 输出逐字节/允许身份差异两份报告，缺基线显示 NOT_VERIFIED，不返回 PASS。

- [ ] 先写 test_existing_four_outputs_byte_equal、test_identity_only_diff_allowlist、test_wrong_generator_baseline_rejected；CI 使用最小合成 fixtures，本地显式提供真实基线路径。
- [ ] 收齐跨模块输入及配置一致性证据，获得缺少的原 vBRS Stub 与双版本差异基线，逐模板比较；失败反查规则，不修改预期来“适配”错误输出。
- [ ] 运行 python -m pytest tests/generator/vbrs -q、python -m pytest tests/generator -q；额外报告真实基线测试通过数/未验证数。原工具数据不可用时这项保持未完成。
- [ ] 有匹配编译环境时补编译/语法检查；不将文本一致宣传为硬件启动安全或量产验证。
- [ ] 执行 openspec validate add-vbrs-code-templates --strict；交付逐项覆盖/差异/测试报告和使用方式，经审阅后再整合提交。

## 六、当前状态与批准边界

本轮完成的是实现方案、257 项定义清单、容器清单和规则引用证据索引。**尚未实现任何产品模板，尚未证明任一文件由新模板生成后与旧文件等价。**

方案采用双版本分离、完整输入覆盖、四文件先回归再补 Stub/差异基线的顺序。函数拆分等实现细节可在保持接口/验收要求下调整；不得自行删减配置项或把缺少基线解释为“已经完全一致”。批准本方案仅启动实现，不等于批准降低用户两项验收要求。
