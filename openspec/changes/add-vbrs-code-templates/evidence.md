# Local evidence (2026-11-05)

## Inputs

- Definition: D:/davinci/mcuapp/DemoComponents/vBRS/BSWMD/vBRS_bswmd.arxml
- Generators: D:/davinci/mcuapp/DemoComponents/vBRS/GeneratorMsr/vBRS.jar and GeneratorDvC6/vBRS.jar
- Values: D:/davinci/mcuapp/Applications/SipAddon/StartApplication/Config/ECUC/StartApplication_vBRS_vBRS_ecuc.arxml
- Outputs: D:/davinci/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData/{vBrsCfg.h,vBrs_Lcfg.c,vBrs_Lcfg.h}; application-root Makefile.config.generated
- Disassembly: C:/Users/00048/AppData/Local/Temp/vbrs-jar-analysis-20261105/. Temporary analysis artifacts are evidence aids, not runtime dependencies; implementation must make extraction reproducible from source JAR hashes.

## Observations

- vBrsCfg.h: 14,461 bytes; vBrs_Lcfg.c: 5,883 bytes; vBrs_Lcfg.h: 4,465 bytes; Makefile: 4,105 bytes.
- Linked C sample has two core entries, logical/physical IDs 0 and 1, startup stack size 1024u, ASR classification, exception and interrupt vector symbols. These are sample values, NOT defaults.
- Header/Makefile sample oscillator 25 MHz and timebase 400 MHz are NOT general defaults.
- Values explicitly disable vBRSEnableEcuMStubGeneration and vBRSEnableSchmStubGeneration.
- GenData/SchM_Mcu.h identifies MICROSAR RTE Generator 4.38.02; GenData/EcuM_Generated_Types.h identifies Module EcuM. Neither is a confirmed vBRS stub baseline.
- Static runtime inventory: _BrsMain.c, _BrsMain.h, _BrsMainStartup.c, _BrsMain_Appl.c, _BrsMain_Appl.h, _BrsMain_Callout_Stubs.c, _BrsMain_Cfg.h, _BrsMain_Types.h, _Brs_MemMap.h.

## Correction to previous analysis

The prior temporary ANALYSIS.md incorrectly said only DvC6 filters empty SchM behaviors. Re-reading MSR BrsGenerationProcessor.generate (javap lines approximately 7052-7063) shows getExclusiveAreas().size() > 0 OR getEntities().size() > 0 before registering SchM output. DvC6 has the corresponding isEmpty checks at approximately 6422-6428. This condition is NOT established as a semantic version difference. Subsequent rules must cite the actual branch, not repeat the prior report.

## Current integration constraints

- autosar_configurator/generator/template_engine.py: a lightweight custom renderer, not a full Jinja2 environment.
- generator.py:_discover_template_types: module-prefix discovery; no runtime default pack.
- generator.py:_generate_single_file: output_name override exists, otherwise prefixes module_name; current EB renderer has unrelated uncommitted changes.
- ecuc_def_parser multiline definition support remains to be implemented/tested, not assumed present.

## Tool availability

Codebase-memory project D-bsw-main-bsw is available. CodeGraph is uninitialized; no index initialization performed. openspec is not on PATH and strict validation has not run. Product tests have not run because this change currently contains only a proposal/design.

## 2026-11-06 全配置方案补充

- 已提取定义叶项 257 个（203 Boolean / 22 Integer / 9 String / 7 Enum / 1 Multiline / 15 Reference），容器定义 22 个；详见 docs/superpowers/plans/2026-11-06-vbrs-config-inventory.md 和 .json。
- 对 MSR 嵌套 jars/GenModel_vBRS.jar 以及 DvC6 模型的 VBRSDefRefs 做 javap 静态解析，两者均映射全部 257 项。不能只按参数名称搜索规则：veHaaS 验证器使用带下划线的 DefRefs 常量。
- 在已扫描 vBRS 规则类中 256 项有同名访问或精确 DefRefs 字段引用；PeriphClockDescription 目前仅见说明性定义。引用存在不证明分支已完整恢复；无引用也不直接证明完全无间接影响。
- 原 sources.json 的八份来源 SHA-256 本轮复核未变化；尚未补齐全部外部输入快照。
- 计划覆盖两个 JAR 的独立 profile，旧版 MSR-only 建议已替代。当前没有产品模板实现，不存在新模板生成等价验证结果。
- 已发现定义描述与生成规则可能冲突：LIN channel17 描述写 channel10；ExecutionInstance 描述的 FBL 宏与 JET 字符串不同。实施须以完整 JAR 条件及正确来源的原输出裁决，不能从描述直接生成宏。
- 配置叶项、容器和来源元数据已写入可复查附件；外部/动态读取和完整分支台账仍为实施任务，不用调查清单冒充全规则恢复完成。
