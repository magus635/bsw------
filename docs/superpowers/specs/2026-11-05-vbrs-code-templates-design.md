# vBRS 逐文件模板设计（待确认）

初稿：2026-11-05；按用户两项硬要求修订：2026-11-06。用户目标：利用现有模板系统，将每个 vBRS 生成文件背后的规则表达为可运行模板，而非继续停留在可行性说明。

## 1. 事实、范围和建议

已找到 StartApplication 下三个 vBrs C/H 输出和 Makefile.config.generated，同时找到项目 vBRS ECUC 值文件。输出和配置是否来自同一次生成尚未核验，不能直接宣布它们是完全一致的黄金基线。

DemoComponents/vBRS/Implementation 下九个文件为运行时实现/用户优化文件，单独列入静态依赖清单，不伪造成 JAR 的生成输出。样例中 vBRSEnableEcuMStubGeneration 和 vBRSEnableSchmStubGeneration 均为 false；GenData/SchM_Mcu.h 标识 RTE Generator，EcuM_Generated_Types.h 标识 EcuM 模块，不能拿这两类文件当作 vBRS Stub 的基线。

覆盖当前两个 JAR：MSR 14.09.01 与 DvC6 14.09.02，分别提供明确版本的模板包和验证报告，不混用规则。先以 MSR 对照现有样例是实施顺序，不是把 DvC6 限定为仅作参考。旧稿“MSR 唯一目标”的建议由本修订替代。

## 2. 每文件模板清单

拟分别放置于 template_packs/vBRS-msr-14.09.01/vBRS/ 和 template_packs/vBRS-dvc6-14.09.02/vBRS/，由用户选为外部模板目录；不成为默认回退模板。

| 原生成输出 | 拟建模板 | 规则与数据 | 样例状态 |
| --- | --- | --- | --- |
| vBrsCfg.h | vBrsCfg.h.tpl | 特性宏、时钟单位、硬件和驱动标志、用户 include | 已找到 |
| vBrs_Lcfg.c | vBrs_Lcfg.c.tpl | 核顺序、逻辑/物理核、栈/异常向量/中断向量符号及大小 | 已找到 |
| vBrs_Lcfg.h | vBrs_Lcfg.h.tpl | 与 C 文件一致的类型、数组长度及 extern 声明 | 已找到 |
| Makefile.config.generated | Makefile.config.generated.tpl | 时钟、衍生芯片、核使用、编译特性、用户 Makefile 内容 | 已找到 |
| EcuM.c | EcuM.c.tpl | EcuM Stub 初始化、模式、变体、多核分支 | 无确认的 vBRS Stub 基线 |
| EcuM.h | EcuM.h.tpl | Stub 接口、类型和声明 | 同上 |
| EcuM_Cbk.h | EcuM_Cbk.h.tpl | Stub 回调声明 | 同上 |
| EcuM_Error.h | EcuM_Error.h.tpl | Stub 错误接口/常量，逐项由 JAR 确认 | 同上 |
| EcuM_Generated_Types.h | EcuM_Generated_Types.h.tpl | Stub 派生类型，不能使用 EcuM 模块同名文件代替 | 同上 |
| SchM_<module API name>.h | SchM_Module.h.tpl | exclusive areas、entities、模块 API infix/ID 命名 | 无确认的 vBRS Stub 基线 |

总计十种模板；SchM 是按配置实例化的一对多输出，不是为示例中每个模块复制一份固定模板。精确输出目录应从输出类构造器复核后写入清单；已确认 MSR SchM 指向 GenData 的兄弟 Include 目录。不得凭文件扩展名猜目录。

## 3. 架构与接入

采用：ECUC 定义/值及其他模块 → 引用解析 → 规则计算/校验 → brs、ecum、schm 上下文 → 显式输出集合 → 模板渲染。

复用现有 TemplateEngine 支持的变量、if、for 子集，不把它误当作完整 Jinja2。模板只做文本排版、条件和循环；频率计算、名字派生、跨模块解析、列表排序在上下文构建层完成。所有必需字段在渲染前验证，防止轻量引擎对缺失值的宽松处理掩盖错误。

既有 _discover_template_types 主要识别 <module>_ 前缀，而 _generate_single_file 默认构造 <module>_<type>；vBrsCfg.h（无下划线）、Makefile、EcuM、SchM 无法全部按此规则接入。建议为显式选择的模板包增加声明式输出清单：template、output_name、target（gendata/include/source/application）、condition、repeat。条件只引用上下文中已计算的布尔值，repeat 只引用已验证的记录列表，不执行任意脚本。没有清单的旧模板保持原发现机制。

UI/调用方为包提供明确的 application、gendata、include、source 目标根；现有只选单一输出目录的工作流使用该目录作为 application，并预览约定的子目录映射，不把 ..\Include 原样拼进路径。只有实际输出需要的目标才必需。所有目标文件在相应根内校验，禁止路径穿越和绝对路径注入。

模块启用并具有有效上下文后输出四个常规文件。EcuM 文件遵循 JAR 的 Stub 开关及 EcuC 识别条件；SchM 遵循 Stub 开关及行为集合。渲染前确定完整输出集合，发现同名 EcuM/RTE 文件冲突时停止并提示，不覆盖其他生成器的文件。关闭特性后的旧文件只允许通过明确归属记录识别，并告知用户，不批量删除非本工具文件。

指纹需覆盖模板、输出清单、规则版本以及实际依赖的外部模块配置，不能只看 vBRS 自身参数；否则修改 Os 核配置可能仍复用旧输出。

## 4. 规则恢复与完整性

逐条记录 ID、源 JAR 哈希/版本、类/方法/字节码偏移、输入定义引用、缺省/不存在语义、条件、计算、输出片段、依赖、测试和状态。状态区分 confirmed、implemented、tested、baseline-compared、unresolved，不把仅观察到 getter 当成完整规则。

已确认的起点：PLL 开关控制存在型宏（关闭不定义）；频率整除 1,000,000 时转换 MHz；用户 Makefile 多行文本注入；核心列表及 EcuM/SchM 文件注册条件。BrsCfgHJet、vBrs_LcfgCJet 等完整分支与剩余 EcuM 头模板继续逐项恢复。

默认值只使用已证明的定义/生成器语义，不将不存在当 false。所有活动输出所需的未解析引用、未知枚举、未实现规则必须产生定位错误并阻止这次生成，不返回一个只有占位注释的“成功”文件。禁止自动修复原配置来迁就模板。

多行参数必须从定义解析、实例值、序列化到上下文保持换行；若编辑器不能编辑，也应明确只读/不支持，不能丢弃原值。

## 5. 样例及验证

1. 记录四个样例、两 JAR、定义及配置文件的哈希和来源；核对样例宏/核数据与配置及跨模块输入的一致性，发现不一致时报告，不硬编码样例数字。
2. 纯规则测试覆盖 true/false/不存在、Hz/MHz、0/1/N 核、非连续物理核、引用缺失、多行用户内容、EcuM 启停、SchM 空/非空行为和命名。
3. 十种模板均做渲染测试；C/H 核数量保持一致；输出无残留模板语法；未支持配置不能产生成功结果。
4. 四个已找到样例在测试专用元数据重放模式下保持编码/BOM/换行/空白，逐字节零差异验收；正常生成使用真实身份，只允许逐字段登记的身份/时间差异并报告原始 diff，不删去注释或宽泛归一化。重放原元数据只用于测试，不冒充正常生成身份。
5. EcuM/SchM 没有原始基线时，以 JAR 分支证据和合成输入做测试，并标记未完成原工具基线比对；获得合法原工具输出后再提升兼容性声明。不以此把相应模板移出范围。
6. 运行 focused tests 与 tests/generator 回归；CI 不依赖 D:/davinci 路径，私有样例作为显式 opt-in 本地对照。最小合成 fixtures 不包含整套厂商 SDK。
7. 有可用头文件/编译器时补充语法或工程构建测试；文本相同并不证明硬件启动安全或量产可用。

## 6. 非目标与完成标准

不把静态 BrsMain 实现重写成可配置模板，不重建整个 Vector SDK，不混合两代生成器，不在没有原工具对照时声称 100% 替代。两个版本的全文件清单、可追溯规则、十种可渲染模板、全部配置与辅助行为接入、无未实现可达分支及测试报告才算实现交付；只有四个样例的静态复制不算完成。

用户已明确需要构造所有生成文件模板。待审批的是本修订双版本方案、外部模板包接入与等价验收方式；函数拆分、测试文件命名等细节留给实现者。当前仍在 OpenSpec 审批阶段。

## 7. 2026-11-06 全覆盖与等价验收修订

用户明确两条硬要求：当前 JAR 的可配项全部实现；配置生成结果与已有代码一致。覆盖 257 个定义叶项、22 个容器，以及 JAR 读取的外部/动态输入、验证器和辅助规则；不能以 257 数量代替完整规则封账。

完整方案见 ../plans/2026-11-06-vbrs-code-templates-implementation-plan.md，逐项清单见 ../plans/2026-11-06-vbrs-config-inventory.md 与同名 JSON。计划中的目标映射不是已实现证明；字段访问证据不是完整分支证据。

双版本必须分别覆盖十类输出及可达规则（含 EcuM 变体、多核、SchM 行为、配置辅助/veHaaS）。活动分支拒绝生成是安全措施，不是将未实现项计作完成。不能恢复规则时列明剩余项，不得自行缩小范围。

四个当前原文件须在匹配输入下完成逐字节重放。缺少 vBRS Stub 原工具基线时可阶段性交付规则测试，但整体原工具等价验收仍未完成；不能用 RTE/EcuM 模块同名输出替代。需要两版本各自适用的原工具参考输出才能关闭全部等价验收事项。
