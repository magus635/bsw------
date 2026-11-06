# vBRS 可配置项逐项清单（方案附件）

日期：2026-11-06。状态：已盘点，不代表规则已实现/完整验证。

共 **257 个定义叶项**：203 Boolean、22 Integer、9 String、7 Enum、1 Multiline String、15 Reference。另有 **22 个容器定义**；实例数量、容器缺失和顺序也是配置输入，不能仅测试叶值。

两个 JAR 的 `VBRSDefRefs` 均可映射全部 257 项。在 vBRS 规则类反汇编中，256 项发现同名访问或精确定义引用字段；`vBRSPeriphClockDescription` 目前仅有定义/说明证据。**字段出现不证明分支已恢复，257 也不是全部跨模块输入的总数。**

配套 JSON 保存完整路径、定义说明、上下界、枚举、目标、测试 ID、两个 JAR 的类/方法引用位置。行号定位的是本次 javap 输出；复核应以来源哈希与类/方法为准，实施时补字节码偏移及完整条件。

## 图例和验收口径

- Cfg=`vBrsCfg.h.tpl`；Lc/Lh=`vBrs_Lcfg.c/h.tpl`；Make=`Makefile.config.generated.tpl`。
- Ec/Eh/Ecb/Eerr/Et 分别为 EcuM.c、EcuM.h、EcuM_Cbk.h、EcuM_Error.h、EcuM_Generated_Types.h 的模板；Sch=`SchM_Module.h.tpl`。
- “前置配置建议/校验”也是模板包必须交付的功能：不伪造宏，不静默修改用户配置。仅显示为“支持”而未实现相应效果不算覆盖。
- 表中策略是实施映射；具体字符串、优先级、条件和版本差异仍须逐规则核定。所有行初始状态均为 `planned_not_branch_verified / not_implemented / not_compared`。
- 定义描述中的宏名仅为线索，不能代替 JAR：例如 LIN channel17 的描述误写 channel10；ExecutionInstance 的描述与模板 FBL 宏拼写存在差别。
- 默认“—”表示定义没有默认值，不等于 false/0；容器不存在时不能自动补成存在。

## 容器及多重性

| 定义路径（省略 /MICROSAR/vBRS/） | 最少 | 最多 |
|---|---:|---:|
| `vBRSGeneral` | 1 | 1 |
| `vBRSGeneral/vBRSOverrideInitPhase` | 0 | 无限 |
| `vBRSHwConfig` | 0 | 1 |
| `vBRSHwConfig/vBRSDriverHandlingCAN` | 0 | 2 |
| `vBRSHwConfig/vBRSDriverHandlingLIN` | 0 | 1 |
| `vBRSHwConfig/vBRSDriverHandlingFlexray` | 0 | 1 |
| `vBRSHwConfig/vBRSDriverHandlingEthernet` | 0 | 2 |
| `vBRSHwConfig/vBRSEvalBoardInfo` | 1 | 无限 |
| `vBRSHwConfig/vBRSDriverHandlingHyperbus` | 0 | 1 |
| `vBRSHwConfig/vBRSDriverHandlingI2C` | 0 | 1 |
| `vBRSHwConfig/vBRSDriverHandlingSpi` | 0 | 1 |
| `vBRSTestsuiteSupport` | 0 | 1 |
| `vBRSMemoryInit` | 1 | 1 |
| `vBRSVeHaasSupport` | 0 | 1 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo` | 0 | 无限 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingCAN` | 0 | 2 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingLIN` | 0 | 1 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingFlexray` | 0 | 1 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingEthernet` | 0 | 2 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingHyperbus` | 0 | 1 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingI2C` | 0 | 1 |
| `vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingSpi` | 0 | 1 |

## vBRSGeneral（22 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSGeneral/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-001 | `vBRSEnableSupportLEDs` | BOOLEAN / false | Cfg | 条件输出 LED 支持宏；Dio 引用另行解析 |
| VBRS-002 | `vBRSEnableSafeContextSupport` | BOOLEAN / false | Cfg | 条件输出 SafeContext 支持宏 |
| VBRS-003 | `vBRSEnableMultiCoreSupport` | BOOLEAN / false | Cfg,Lc,Lh,Make,Ec | 生成多核标志；按实际 coreData 输出表/声明和初始化分支 |
| VBRS-004 | `vBRSUserConfigFile` | STRING / — | Cfg | 非空时按原规则输出 include；校验文件名的引号/换行 |
| VBRS-005 | `vBRSEnableSupportToggleWdPin` | BOOLEAN / false | Cfg | 条件输出外部看门狗引脚支持宏 |
| VBRS-006 | `vBRSEnableSupportToggleCustomPin` | BOOLEAN / false | Cfg | 条件输出自定义引脚支持宏 |
| VBRS-007 | `vBRSEnableEcuMStubGeneration` | BOOLEAN / false | Ec,Eh,Ecb,Eerr,Et | 结合 EcuC 识别条件选择五个 EcuM 输出；不是无条件占位文件 |
| VBRS-008 | `vBRSDisableSetupSupport` | BOOLEAN / false | 前置校验/配置修复建议 | 控制 setup/solving-action；不伪造 C 宏，落实到模板包配套校验 |
| VBRS-009 | `vBRSEnableSchmStubGeneration` | BOOLEAN / false | Sch | 按有 exclusive areas 或 entities 的内部行为展开文件 |
| VBRS-010 | `vBRSEnableSchmStubSupportDrvCanAN` | BOOLEAN / false | Sch | 按模块和区域编号过滤 AN 指定的 exclusive areas；具体编号以 JAR 为准 |
| VBRS-011 | `vBRSEnableSchmStubEmptyExclusiveAreaHandling` | BOOLEAN / false | Sch | 选择空 Enter/Exit 宏或中断保护实现 |
| VBRS-012 | `vBRSExecutionInstance` | ENUMERATION / Application | Cfg,Make,Ec,Lc | 九种枚举分别建映射和组合条件；禁止只实现 Application/FBL |
| VBRS-013 | `vBRSFirstInstance` | BOOLEAN / true | Cfg,Make | 首实例标志及关联构建信息；不由文件名猜测 |
| VBRS-014 | `vBRSEnableCoreSpecificVLinkGenConfig` | BOOLEAN / false | 前置校验 → Lc,Lh | 核对 Os/EcuC/vLinkGen 核、栈、段组；不虚构直接宏 |
| VBRS-015 | `vBRSFblSupportEcuMInit` | BOOLEAN / false | Cfg,Ec | 只在 FBL 家族条件满足时选择 EcuM_Init/FblMain 对应分支 |
| VBRS-016 | `vBRSFblSupportExceptionTableInRam` | BOOLEAN / false | Cfg,Lc | 条件生成 RAM 异常表支持及表项；验证链接段组 |
| VBRS-017 | `vBRSEnableSmallDevicesOptimization` | BOOLEAN / false | 前置校验/配置修复建议 | 单核 SC1 条件下栈/Hook 设置建议；明确确认后应用，不在模板内擅改 Os |
| VBRS-018 | `vBRSHypervisorGuest` | BOOLEAN / false | Cfg,Make | 条件输出虚拟化 guest 属性并保留执行实例组合约束 |
| VBRS-019 | `vBRSToggleLEDDioChannel` | REFERENCE / — | Cfg | 解析 Dio 通道符号/前缀后输出 LED 通道绑定 |
| VBRS-020 | `vBRSToggleWdPinDioChannel` | REFERENCE / — | Cfg | 解析 Dio 通道符号/前缀后输出看门狗通道绑定 |
| VBRS-021 | `vBRSToggleCustomPinDioChannel` | REFERENCE / — | Cfg | 解析 Dio 通道符号/前缀后输出自定义通道绑定 |
| VBRS-022 | `vBRSVariantUsageOfvLinkGen` | REFERENCE / — | Cfg,Make | 解析所选 variant 名，输出链接变体与命令文件后缀，验证按变体输出条件 |

- `vBRSExecutionInstance` 全部枚举：`Application`、`FBL`、`FBL_Updater`、`BM`、`BM_FBL`、`HSM`、`HSM_Updater`、`FlashDriver`、`Hypervisor`。

## vBRSGeneral/vBRSOverrideInitPhase（2 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSGeneral/vBRSOverrideInitPhase/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-023 | `vBRSInitPhase` | ENUMERATION / — | Ec | 覆盖目标 init function 阶段；17 个枚举分别处理，NO_INIT 不能当缺失 |
| VBRS-024 | `vBRSInitFunction` | REFERENCE / — | Ec | 解析初始化函数引用，与 InitPhase 成对参与排序/排除规则 |

- `vBRSInitPhase` 全部枚举：`NO_INIT`、`INIT_MEMORY`、`INIT_ZERO`、`INIT_ONE_EARLY`、`INIT_ONE`、`INIT_ONE_LATE`、`INIT_TWO_MCAL`、`INIT_TWO_TRCV`、`INIT_TWO_DRV`、`INIT_TWO_IF`、`INIT_TWO_COM`、`INIT_TWO_SM`、`INIT_TWO_NM`、`INIT_TWO_TP`、`INIT_TWO_SYS`、`INIT_TWO_POST_NVMREADALL`、`INIT_THREE`。

## vBRSHwConfig（15 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-025 | `vBRSOscClock` | INTEGER / 0 | Cfg,Make | 非负 Hz 整除 1000000 时转 MHz，否则保留 Hz；宏、Make 数值及单位一起测试 |
| VBRS-026 | `vBRSTimebaseClock` | INTEGER / 0 | Cfg,Make | 非负 Hz 整除 1000000 时转 MHz，否则保留 Hz；宏、Make 数值及单位一起测试 |
| VBRS-027 | `vBRSPeriphClock` | INTEGER / 0 | Cfg,Make | 非负 Hz 整除 1000000 时转 MHz，否则保留 Hz；宏、Make 数值及单位一起测试 |
| VBRS-028 | `vBRSEnablePortHandling` | BOOLEAN / false | Cfg | 条件生成存在型宏；关闭时不定义为 0，保留原分支条件 |
| VBRS-029 | `vBRSEnableWatchdogHandling` | BOOLEAN / false | Cfg | 条件生成存在型宏；关闭时不定义为 0，保留原分支条件 |
| VBRS-030 | `vBRSEnablePLLClocksHandling` | BOOLEAN / false | Cfg | 条件生成存在型宏；关闭时不定义为 0，保留原分支条件 |
| VBRS-031 | `vBRSCompilerInstructionSet` | ENUMERATION / — | Cfg,Make | 五种指令集逐项输出宏和构建变量 |
| VBRS-032 | `vBRSCompilerEnableFPU` | BOOLEAN / — | Cfg,Make | FPU 布尔值映射宏及构建变量；区分缺失和 false |
| VBRS-033 | `vBRSPeriphClockDescription` | STRING / — | 无代码输出 | 保留定义/值及展示信息；尚未发现规则读取，完成审计后证明 no-output |
| VBRS-034 | `vBRSMakefileUserCode` | MULTILINE-STRING / — | Make | 保留多行文本和原插入位置，不吞换行，不解释为模板语法 |
| VBRS-035 | `vBRSPreferPLLWatchdogInit` | BOOLEAN / false | Cfg | 条件生成存在型宏；关闭时不定义为 0，保留原分支条件 |
| VBRS-036 | `vBRSCompilerPath` | STRING / — | Make | 输出 BRS_COMPILER_PATH；按原规则保留路径转义 |
| VBRS-037 | `vBRSProjectName` | STRING / — | Make | 输出 BRS_PROJECT_NAME |
| VBRS-038 | `vBRSMcuClockReferencePointForBrsPeriphClock` | REFERENCE / — | 前置配置建议 → Cfg,Make | Mcu 频率复制 solving-action；读值优先级须追踪，不能自动用引用值覆盖显式值 |
| VBRS-039 | `vBRSEvaluationBoard` | REFERENCE / — | Cfg,Make | 解析明确选中的 EvalBoardInfo，输出板卡标志/构建名；未选不取第一项 |

- `vBRSCompilerInstructionSet` 全部枚举：`THUMB`、`ARM`、`VLE`、`BOOKE`、`RV32I`。

## vBRSHwConfig/vBRSDriverHandlingCAN（25 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingCAN/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-040 | `vBRSEnableDriverHandlingCAN` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-041 | `vBRSDriverHandlingCAN_channel0` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-042 | `vBRSDriverHandlingCAN_channel1` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-043 | `vBRSDriverHandlingCAN_channel2` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-044 | `vBRSDriverHandlingCAN_channel3` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-045 | `vBRSDriverHandlingCAN_channel4` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-046 | `vBRSDriverHandlingCAN_channel5` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-047 | `vBRSDriverHandlingCAN_channel6` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-048 | `vBRSDriverHandlingCAN_channel7` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-049 | `vBRSDriverHandlingCAN_channel8` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-050 | `vBRSDriverHandlingCAN_channel9` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-051 | `vBRSDriverHandlingCAN_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-052 | `vBRSDriverHandlingCAN_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-053 | `vBRSDriverHandlingCAN_channel10` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-054 | `vBRSDriverHandlingCAN_channel11` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-055 | `vBRSDriverHandlingCAN_channel12` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-056 | `vBRSDriverHandlingCAN_channel13` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-057 | `vBRSDriverHandlingCAN_channel14` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-058 | `vBRSDriverHandlingCAN_channel15` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-059 | `vBRSDriverHandlingCAN_channel16` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-060 | `vBRSDriverHandlingCAN_channel17` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-061 | `vBRSDriverHandlingCAN_channel18` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-062 | `vBRSDriverHandlingCAN_channel19` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-063 | `vBRSDriverHandlingCAN_Instance` | ENUMERATION / — | Cfg | 按枚举/实例命名展开；CAN/Ethernet 双实例不得合并 |
| VBRS-064 | `vBRSDriverHandlingCAN_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

- `vBRSDriverHandlingCAN_Instance` 全部枚举：`MCAN`、`XCAN`、`RCAN`、`FlexCAN`、`RSCAN`。

## vBRSHwConfig/vBRSDriverHandlingLIN（27 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingLIN/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-065 | `vBRSEnableDriverHandlingLIN` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-066 | `vBRSDriverHandlingLIN_channel0` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-067 | `vBRSDriverHandlingLIN_channel1` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-068 | `vBRSDriverHandlingLIN_channel2` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-069 | `vBRSDriverHandlingLIN_channel3` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-070 | `vBRSDriverHandlingLIN_channel4` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-071 | `vBRSDriverHandlingLIN_channel5` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-072 | `vBRSDriverHandlingLIN_channel6` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-073 | `vBRSDriverHandlingLIN_channel7` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-074 | `vBRSDriverHandlingLIN_channel8` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-075 | `vBRSDriverHandlingLIN_channel9` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-076 | `vBRSDriverHandlingLIN_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-077 | `vBRSDriverHandlingLIN_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-078 | `vBRSDriverHandlingLIN_channel10` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-079 | `vBRSDriverHandlingLIN_channel11` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-080 | `vBRSDriverHandlingLIN_channel12` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-081 | `vBRSDriverHandlingLIN_channel13` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-082 | `vBRSDriverHandlingLIN_channel14` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-083 | `vBRSDriverHandlingLIN_channel15` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-084 | `vBRSDriverHandlingLIN_channel16` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-085 | `vBRSDriverHandlingLIN_channel17` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-086 | `vBRSDriverHandlingLIN_channel18` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-087 | `vBRSDriverHandlingLIN_channel19` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-088 | `vBRSDriverHandlingLIN_channel20` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-089 | `vBRSDriverHandlingLIN_channel21` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-090 | `vBRSDriverHandlingLIN_channel22` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-091 | `vBRSDriverHandlingLIN_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

## vBRSHwConfig/vBRSDriverHandlingFlexray（8 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingFlexray/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-092 | `vBRSEnableDriverHandlingFlexray` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-093 | `vBRSDriverHandlingFlexray_channel0A` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-094 | `vBRSDriverHandlingFlexray_channel0B` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-095 | `vBRSDriverHandlingFlexray_channel1A` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-096 | `vBRSDriverHandlingFlexray_channel1B` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-097 | `vBRSDriverHandlingFlexray_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-098 | `vBRSDriverHandlingFlexray_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-099 | `vBRSDriverHandlingFlexray_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

## vBRSHwConfig/vBRSDriverHandlingEthernet（22 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingEthernet/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-100 | `vBRSEnableDriverHandlingEthernet` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-101 | `vBRSDriverHandlingEthernet_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-102 | `vBRSDriverHandlingEthernet_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-103 | `vBRSDriverHandlingEthernet_Instance` | ENUMERATION / — | Cfg | 按枚举/实例命名展开；CAN/Ethernet 双实例不得合并 |
| VBRS-104 | `vBRSDriverHandlingEthernet_Port0` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-105 | `vBRSDriverHandlingEthernet_SwitchSupport` | BOOLEAN / false | Cfg | 条件输出交换机支持宏并与实例、端口组合验证 |
| VBRS-106 | `vBRSDriverHandlingEthernet_Port1` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-107 | `vBRSDriverHandlingEthernet_Port2` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-108 | `vBRSDriverHandlingEthernet_Port3` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-109 | `vBRSDriverHandlingEthernet_Port4` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-110 | `vBRSDriverHandlingEthernet_Port5` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-111 | `vBRSDriverHandlingEthernet_Port6` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-112 | `vBRSDriverHandlingEthernet_Port7` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-113 | `vBRSDriverHandlingEthernet_Port8` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-114 | `vBRSDriverHandlingEthernet_Port9` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-115 | `vBRSDriverHandlingEthernet_Port10` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-116 | `vBRSDriverHandlingEthernet_Port11` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-117 | `vBRSDriverHandlingEthernet_Port12` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-118 | `vBRSDriverHandlingEthernet_Port13` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-119 | `vBRSDriverHandlingEthernet_Port14` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-120 | `vBRSDriverHandlingEthernet_Port15` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-121 | `vBRSDriverHandlingEthernet_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

- `vBRSDriverHandlingEthernet_Instance` 全部枚举：`ETNA`、`ETNB`、`ETNF`、`GETH`、`GMAC`、`LETH`、`RSWITCH2`。

## vBRSHwConfig/vBRSEvalBoardInfo（3 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSEvalBoardInfo/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-122 | `vBRSEvalBoardDescription` | STRING / — | 前置校验/说明 → Make | 保留所选板卡说明，核对 JAR 是否输出注释；不生成独立功能宏 |
| VBRS-123 | `vBRSEvalBoard` | STRING / — | Cfg,Make | 所选记录的板名用于板卡宏/Make 变量；未选记录不参与输出 |
| VBRS-124 | `vBRSEvalBoardOscClock` | INTEGER / 0 | 前置配置建议 → Cfg,Make | 所选记录提供振荡频率的配置建议；确认复制/优先级后用统一频率规则 |

## vBRSHwConfig/vBRSDriverHandlingHyperbus（6 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingHyperbus/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-125 | `vBRSEnableDriverHandlingHyperbus` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-126 | `vBRSDriverHandlingHyperbus_channel0` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-127 | `vBRSDriverHandlingHyperbus_channel1` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-128 | `vBRSDriverHandlingHyperbus_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-129 | `vBRSDriverHandlingHyperbus_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-130 | `vBRSDriverHandlingHyperbus_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

## vBRSHwConfig/vBRSDriverHandlingI2C（15 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingI2C/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-131 | `vBRSEnableDriverHandlingI2C` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-132 | `vBRSDriverHandlingI2C_channel0` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-133 | `vBRSDriverHandlingI2C_channel1` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-134 | `vBRSDriverHandlingI2C_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-135 | `vBRSDriverHandlingI2C_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-136 | `vBRSDriverHandlingI2C_channel2` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-137 | `vBRSDriverHandlingI2C_channel3` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-138 | `vBRSDriverHandlingI2C_channel4` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-139 | `vBRSDriverHandlingI2C_channel5` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-140 | `vBRSDriverHandlingI2C_channel6` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-141 | `vBRSDriverHandlingI2C_channel7` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-142 | `vBRSDriverHandlingI2C_channel8` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-143 | `vBRSDriverHandlingI2C_channel9` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-144 | `vBRSDriverHandlingI2C_channel10` | BOOLEAN / false | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-145 | `vBRSDriverHandlingI2C_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

## vBRSHwConfig/vBRSDriverHandlingSpi（5 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSHwConfig/vBRSDriverHandlingSpi/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-146 | `vBRSEnableDriverHandlingSpi` | BOOLEAN / true | Cfg | 决定驱动支持宏及下属设置的输出条件；覆盖启用/禁用/容器缺失 |
| VBRS-147 | `vBRSDriverHandlingSpi_channel0` | BOOLEAN / — | Cfg | 在所属实例内逐项判断，条件输出对应编号宏；容器/父开关条件依 JAR，不能从说明文字直接猜编号 |
| VBRS-148 | `vBRSDriverHandlingSpi_PeripheralClock` | BOOLEAN / true | Cfg | 选择公共外设时钟或本驱动时钟，缺失不默认零 |
| VBRS-149 | `vBRSDriverHandlingSpi_Clock` | INTEGER / 0 | Cfg | 按有效时钟分支输出 Hz/MHz 数值及单位 |
| VBRS-150 | `vBRSDriverHandlingSpi_ClockRef` | REFERENCE / — | 前置配置建议 → Cfg | 解析 McuClockReferencePoint；按 solving-action 复制语义实现，优先级/触发条件逐版本核定 |

## vBRSTestsuiteSupport（1 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSTestsuiteSupport/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-151 | `vBRSEnableTestsuiteSupport` | BOOLEAN / true | Cfg,Ec | 依 testsuite 容器存在性和开关选择宏/初始化代码 |

## vBRSMemoryInit（6 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSMemoryInit/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-152 | `vBRSInitPatternBlocks` | INTEGER / 0 | Cfg | 无损读取 0..18446744073709551615，按 32/64 位分支输出十六进制及 C 后缀；越界处理与原规则核对 |
| VBRS-153 | `vBRSInitPatternHardResetBlocks` | INTEGER / 0 | Cfg | 无损读取 0..18446744073709551615，按 32/64 位分支输出十六进制及 C 后缀；越界处理与原规则核对 |
| VBRS-154 | `vBRSInitPatternAreas` | INTEGER / 0 | Cfg | 无损读取 0..18446744073709551615，按 32/64 位分支输出十六进制及 C 后缀；越界处理与原规则核对 |
| VBRS-155 | `vBRSInitPatternHardResetAreas` | INTEGER / 0 | Cfg | 无损读取 0..18446744073709551615，按 32/64 位分支输出十六进制及 C 后缀；越界处理与原规则核对 |
| VBRS-156 | `vBRSInitEnable64BitInitPattern` | BOOLEAN / false | Cfg | 切换 32/64 位模式及格式，验证 vLinkGen64BitMemoryMode |
| VBRS-157 | `vBRSDisableMemoryInitGlobally` | BOOLEAN / false | Cfg | 条件生成跳过内存初始化宏；不删除静态运行时代码 |

## vBRSVeHaasSupport（1 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-158 | `vBRSVeHaasAssembly` | REFERENCE / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo（5 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-159 | `vBRSVeHaasAssemblyName` | STRING / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-160 | `vBRSVeHaasAssemblyEvaluationBoard` | STRING / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-161 | `vBRSVeHaasAssemblyTestedDerivative` | STRING / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-162 | `vBRSVeHaasAssemblyToggleCustomPin` | BOOLEAN / true | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-163 | `vBRSVeHaasAssemblyToggleLEDPin` | BOOLEAN / true | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingCAN（23 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingCAN/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-164 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-165 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel1` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-166 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel2` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-167 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel3` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-168 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel4` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-169 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel5` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-170 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel6` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-171 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel7` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-172 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel8` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-173 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel9` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-174 | `vBRSVeHaasAssemblyDriverHandlingCAN_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-175 | `vBRSVeHaasAssemblyDriverHandlingCAN_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-176 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel10` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-177 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel11` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-178 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel12` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-179 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel13` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-180 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel14` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-181 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel15` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-182 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel16` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-183 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel17` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-184 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel18` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-185 | `vBRSVeHaasAssemblyDriverHandlingCAN_channel19` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-186 | `vBRSVeHaasAssemblyDriverHandlingCAN_Instance` | ENUMERATION / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

- `vBRSVeHaasAssemblyDriverHandlingCAN_Instance` 全部枚举：`MCAN`、`XCAN`、`RCAN`、`FlexCAN`、`RSCAN`。

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingLIN（25 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingLIN/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-187 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-188 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel1` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-189 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel2` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-190 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel3` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-191 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel4` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-192 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel5` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-193 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel6` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-194 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel7` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-195 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel8` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-196 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel9` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-197 | `vBRSVeHaasAssemblyDriverHandlingLIN_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-198 | `vBRSVeHaasAssemblyDriverHandlingLIN_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-199 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel10` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-200 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel11` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-201 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel12` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-202 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel13` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-203 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel14` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-204 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel15` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-205 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel16` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-206 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel17` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-207 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel18` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-208 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel19` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-209 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel20` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-210 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel21` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-211 | `vBRSVeHaasAssemblyDriverHandlingLIN_channel22` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingFlexray（6 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingFlexray/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-212 | `vBRSVeHaasAssemblyDriverHandlingFlexray_channel0A` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-213 | `vBRSVeHaasAssemblyDriverHandlingFlexray_channel0B` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-214 | `vBRSVeHaasAssemblyDriverHandlingFlexray_channel1A` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-215 | `vBRSVeHaasAssemblyDriverHandlingFlexray_channel1B` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-216 | `vBRSVeHaasAssemblyDriverHandlingFlexray_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-217 | `vBRSVeHaasAssemblyDriverHandlingFlexray_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingEthernet（20 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingEthernet/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-218 | `vBRSVeHaasAssemblyDriverHandlingEthernet_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-219 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-220 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Instance` | ENUMERATION / — | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-221 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-222 | `vBRSVeHaasAssemblyDriverHandlingEthernet_SwitchSupport` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-223 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port1` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-224 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port2` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-225 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port3` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-226 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port4` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-227 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port5` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-228 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port6` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-229 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port7` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-230 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port8` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-231 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port9` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-232 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port10` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-233 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port11` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-234 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port12` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-235 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port13` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-236 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port14` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-237 | `vBRSVeHaasAssemblyDriverHandlingEthernet_Port15` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

- `vBRSVeHaasAssemblyDriverHandlingEthernet_Instance` 全部枚举：`ETNA`、`ETNB`、`ETNF`、`GETH`、`GMAC`、`LETH`、`RSWITCH2`。

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingHyperbus（4 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingHyperbus/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-238 | `vBRSVeHaasAssemblyDriverHandlingHyperbus_channel0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-239 | `vBRSVeHaasAssemblyDriverHandlingHyperbus_channel1` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-240 | `vBRSVeHaasAssemblyDriverHandlingHyperbus_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-241 | `vBRSVeHaasAssemblyDriverHandlingHyperbus_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingI2C（13 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingI2C/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-242 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-243 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel1` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-244 | `vBRSVeHaasAssemblyDriverHandlingI2C_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-245 | `vBRSVeHaasAssemblyDriverHandlingI2C_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-246 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel2` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-247 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel3` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-248 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel4` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-249 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel5` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-250 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel6` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-251 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel7` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-252 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel8` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-253 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel9` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-254 | `vBRSVeHaasAssemblyDriverHandlingI2C_channel10` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingSpi（3 项）

本组完整路径前缀：`/MICROSAR/vBRS/vBRSVeHaasSupport/vBRSVeHaasAssemblyInfo/vBRSVeHaasAssemblyDriverHandlingSpi/`。

| ID | 配置项 | 类型 / 默认 | 目标 | 如何支持配置 |
|---|---|---|---|---|
| VBRS-255 | `vBRSVeHaasAssemblyDriverHandlingSpi_channel0` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-256 | `vBRSVeHaasAssemblyDriverHandlingSpi_PeripheralClock` | BOOLEAN / false | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |
| VBRS-257 | `vBRSVeHaasAssemblyDriverHandlingSpi_Clock` | INTEGER / 0 | 前置配置解析 → Cfg,Make/Lc（依目标） | 按选中的 Assembly 解析本字段，映射板卡/derivative/LED/驱动实际配置；保留多实例，输出差异建议并显式应用或报告冲突；目标模板复用正常配置分支，不制造 veHaaS 专用宏 |

## 实施时必须补齐的非叶项规则

1. 所有直接/间接外部模块输入，见主方案 E01–E10，不能用上述 257 项代替。
2. 输出选择/路径/名称、内部行为集合、模块存在性、动态 getParameter/字符串路径、默认/缺失、枚举组合、数据辅助类中的 C 文本拼接。
3. 每项完成标准：完整规则证据 + 模板/配套解析位置 + 正反/边界测试；无输出项需给出理由和不变性测试。
4. 双 JAR 分别封账：不得因为模型字段一样，就推断生成条件、校验或文本完全一致。
