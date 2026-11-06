# vBRS 逐文件代码模板

## Why

用户要求利用本项目已有模板机制、vBRS 已生成代码以及 JAR 中的生成规则，为每个 vBRS 生成输出构造可随配置变化的模板。仅把现有输出复制为 .tpl 无法支持其他配置；仅凭定义 ARXML 也无法解析多核、EcuM、SchM 等派生数据。

## What Changes

- 新增显式加载的 vBRS 模板包，不恢复运行时内置默认模板。
- 基准拟选 GeneratorMsr 14.09.01；DvC6 仅作对照，未经核对不混用规则。
- 覆盖四种常规输出、五种条件 EcuM Stub 输出，以及按内部行为实例化的 SchM 头文件模板。
- 增加受校验的配置上下文构建及显式输出名/目录/条件映射，复用现有 TemplateEngine，不引入另一种模板引擎。
- 补齐 vBRSMakefileUserCode 所需的多行参数数据通路；对缺失引用和未还原分支报错，不用默认零值制造看似正确的输出。
- 增加逐规则证据、分支测试和样例对照；静态实现文件不冒充生成输出。

## Impact

- New capability: vbrs-code-generation.
- Proposed locations: template_packs/vBRS-msr-14.09.01/vBRS/; autosar_configurator/generator/vbrs/; tests/generator/vbrs/.
- Integration boundaries: generator.py（显式模板包发现、输出映射、上下文和指纹）；definition_model.py / ecuc_def_parser.py（多行参数）；必要时配置序列化和参数编辑器。
- 不覆盖用户现有未提交改动，不修改 D:/davinci 下的原始文件，不运行原始生成器、不增加 Java SDK 运行时依赖。
- 与 remove-default-templates 保持一致；避免侵入当前有本地改动的 EB renderer/values/computed_defaults。

## Approval status

待用户确认。此次只提交调查记录和设计，尚未新增产品模板、规则处理代码或执行实现测试。

## Design

见 docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md 和本目录 evidence.md。
