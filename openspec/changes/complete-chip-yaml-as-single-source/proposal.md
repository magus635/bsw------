## Why

目标是"每颗芯片一个 YAML 就够"：芯片厂商用芯片定义设计器维护每颗芯片的 YAML，随工具交付给用户；用户只选芯片，不需要 `.properties`，也不需要改模块定义文件。`add-chip-yaml-ecu-resources` 和 `add-chip-designer-ecu-resource-editor` 之后，代码生成已经做到这一点，但还有四处做不到：

1. **界面约束仍只读 `.properties`。** `ChipConstraintService` 只扫描 `Def/plugins/*/resource/*.properties`，把结果交给 xdm 表达式解析器（`XdmExpressionResolver.set_constraints`）。参数的取值范围、最大值、实例数等由 `ecu:get/ecu:list` 算出的限制都来自这里，完全不看芯片 YAML。只有 YAML 的项目，界面上这些限制是空的；芯片可选列表也只从 properties 文件名发现。
2. **芯片选择器写死在模块定义里。** `Resource.xdm` 的 `ResourceSubderivative` 取值范围写死为三颗芯片（`THA610X_LFBGA180`、`THA6206_LFBGA292`、`THA6412_BGA516`）；`Os.xdm` 的 `OsResourceSubderivative` 写死为 `Os_THA6206`、`Os_THA6412`、`Os_SC300`，而且 Os 的取值与芯片名命名不同，模板按它分支（如 `= 'Os_SC300'`）。新增芯片必须改定义文件。
3. **同一事实存两份。** 芯片 YAML 里设计器的带类型字段（`metadata.cores`、`can_resources`、`adc_resources`、`spi_resources`）与 `ecu_resources` 会描述同一件事（如核数同时出现在 `metadata.cores.count`、`OsResource.NumOfCores`、`Resource.NumOfCores`），可能不一致；而模板只读 `ecu_resources`。
4. **交付的完整性不可检查。** 只有 `resource_version`，没有校验和；项目里的 `chips/` 副本可以被改动而无人察觉；项目不记录所用芯片数据的版本。芯片数据对用户应当只读、可追溯（功能安全工具鉴定也会关心）。

已确认的决策：芯片数据以 YAML 交付；同一事实以 `ecu_resources` 为准。

## What Changes

- **界面约束改用同一份数据**：`ChipConstraintService` 的约束取自 `EcuResourceResolver` 算出的 `project.ecu_resources`（芯片 YAML 加项目 properties），与代码生成一致；芯片可选列表合并芯片库、项目内芯片和 properties 文件名三类来源。
- **芯片选择器由芯片 YAML 声明**：芯片 YAML 新增 `selectors` 段，声明本芯片在各模块选择器参数上的取值，例如 `Resource.ResourceSubderivative: THA6412_BGA516`、`Os.OsResourceSubderivative: Os_THA6412`。解析定义时，这些参数的可选值为"定义文件原有的值 ∪ 芯片库中所有芯片声明的值"，新芯片无需改定义文件。选中芯片后，若用户配置里的选择器取值与芯片声明不一致，给出诊断警告（不自动改用户配置）。
- **以 `ecu_resources` 为准的一致性规则**：声明一张"带类型字段 ↔ `ecu_resources` 键"的映射表（首批只含核数、可用核列表、主核这类含义明确的项）。设计器发现不一致时提示，并提供"用 ECU 资源覆盖表单"；导出与生成只读 `ecu_resources`。
- **版本与校验和**：芯片 YAML 带 `resource_version` 与按规范化内容计算的 `checksum`（设计器保存时写入）。项目记录所用芯片的版本和校验和；打开项目时，若项目副本被改动（校验和不符）或芯片库有不同版本，给出提示。设计器之外的手改会被发现。

## Impact

- Affected specs: `chip-single-source`（新增能力）；依赖 `chip-ecu-resources`、`chip-designer-ecu-editor`（均已实现，待归档）。
- Affected code:
  - `autosar_configurator/core/chip_constraint_service.py`（数据来源）
  - `autosar_configurator/core/parser/ecuc_def_parser.py`（选择器参数的可选值注入）
  - `autosar_configurator/core/hardware/chip_database.py`、`chip_exporter.py`（`selectors`、`checksum`）
  - `autosar_configurator/core/hardware/ecu_resource_diagnostics.py`（选择器与芯片声明不符的诊断、带类型字段一致性）
  - `autosar_configurator/core/workspace_manager.py`（项目记录芯片版本与校验和）
  - `autosar_configurator/ui/davinci_main_window.py`、`ui/controllers/project_controller.py`（约束更新时机、提示）
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`（选择器编辑、一致性提示、保存写校验和）
  - 测试：`tests/core/`、`tests/ui/`
- 兼容性：
  - 没有 `selectors`、`checksum` 的芯片 YAML 照常加载；定义文件原有的选择器取值保留，不会因芯片库缺少声明而丢失。
  - 已有项目（含 properties）界面约束：改动前的每个约束都保留且值不变（`test_import_project` 三颗芯片实测：0 缺失、0 不同）；新增的只有生成器本来就读取的 build 配置文件里的键（7 个）。
  - 生成结果与指纹不变。
- **不在本变更范围内**：
  - 芯片切换后已解析的定义需要重新解析才能刷新枚举值（现有行为，见 design 的 Risks）。
  - 带类型字段与 `ecu_resources` 之间超出首批映射表的对应关系（CAN/ADC/SPI 等）。
  - 对芯片数据做加密签名（只做校验和，用于发现改动，不防恶意篡改）。
