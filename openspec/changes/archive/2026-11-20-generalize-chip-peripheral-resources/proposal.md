## Why

芯片定义设计器的"外设规格"页写死了 CAN、ADC、SPI 三组，不能增减外设类型；而它的数据唯一的实质用途是**硬件映射向导**（按芯片的外设实例自动创建模块配置）。现状有四个问题：

1. **类型写死。** `data/mapping_rules/` 有 13 个模块的映射规则（adc、can、dio、eth、gpt、icu、intc、lin、mcu、port、pwm、spi、wdg），对应的外设类型有 `eth_controller`、`gpt_channel`、`icu_channel`、`lin_channel`、`clock_source`、`pwm_channel`、`wdg_unit` 等；芯片 YAML 却只能提供 CAN、ADC、SPI（和引脚、中断源）。其余规则拿不到芯片数据，向导对这些模块没用。
2. **粒度粗，会丢数据。** CAN-FD 是全局勾选、ADC 分辨率是全局值、SPI 只有一组时钟与 DMA 设置；载入再保存时，各实例自己的设置被全局值覆盖。`intc_sources` 在设计器里不能编辑。
3. **两套模型并存。** 芯片 YAML 用带类型的字段（`can_resources`、`adc_resources`、`spi_resources`、`intc_sources`），向导用通用资源模型（`generic_resource.ChipDefinition.resources`），中间靠 `convert_legacy_chip` 临时转换；通用模型自己的 YAML 格式（`resources:`）芯片库从没用过。
4. **向导不认项目里的芯片。** `HardwareMappingWizard` 的芯片来源是代码里的 `ChipDatabase.create_default_database()` 加芯片库目录，看不到项目 `chips/` 里的副本，也不会默认选中项目的芯片。

已确认：保留并交付硬件映射向导；外设改用通用资源模型（方案 B）。

## What Changes

- **芯片 YAML 的 `resources` 段**：外设实例统一写成通用资源格式 `{类型: [{resource_id, display_name, properties}]}`，与 `generic_resource` 现有的读写格式一致；任意外设类型、每个实例任意属性。
- **旧字段迁移**：加载时把 `can_resources`、`adc_resources`、`spi_resources`、`intc_sources` 按 `convert_legacy_chip` 现有的类型名与属性名转成 `resources`（`can_controller`、`adc_unit`、`spi_unit`、`intc_source`）；保存时只写 `resources`。引脚表仍在 `ports`（第 3 页），`gpio_port` / `gpio_pin` 照旧由引脚表推导。
- **兼容读取**：仍以 `can_resources=...` 构造芯片的代码（内置默认芯片、properties 构造、xdm 提取、测试）继续可用；读取外设统一走"有效资源"（`resources` 加旧字段的转换结果）。
- **设计器"外设"页改为通用编辑器**：
  - 左边是外设类型列表（带实例数），可新增、删除类型；可选类型来自映射规则，也可手输。
  - 右边是该类型的实例表：`resource_id`、`display_name`，每个属性一列；可增删、复制实例，"按模式批量添加"（如 `CAN0`…`CAN5`，编号属性自动递增）。
  - 新增实例时按映射规则预填该类型规则会读取的属性；实例缺少规则要读的属性时提示（向导会因此拿不到值）。
- **硬件映射向导的芯片来源**：与项目一致——项目 `chips/` 副本优先，其次芯片库；默认选中项目的芯片。直接读取 `resources`，不再经过旧字段转换。
- **新建项目向导的芯片信息**：按类型显示外设实例数，不再只列 CAN、ADC、SPI。

## Impact

- Affected specs: `chip-peripheral-resources`（新增能力）。
- Affected code:
  - `autosar_configurator/core/hardware/chip_database.py`（`resources` 字段、旧字段迁移、有效资源）
  - `autosar_configurator/core/hardware/chip_exporter.py`（导出 `resources`；旧的 properties 兜底推导改读有效资源）
  - `autosar_configurator/core/hardware/generic_resource.py`（`convert_legacy_chip` 改用有效资源与 `ports`）
  - `autosar_configurator/core/hardware/mapping_rules*`（读出每条规则的资源类型和它读取的属性）
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`（外设页）与新的外设编辑部件
  - `autosar_configurator/ui/wizards/hardware_mapping_wizard.py`、`ui/controllers/wizard_controller.py`（芯片来源）
  - `autosar_configurator/ui/wizards/new_project_wizard.py`（芯片信息）
  - 内置芯片 YAML（`data/chips/*.yaml`）迁移为 `resources` 格式
  - 测试：`tests/core/`、`tests/ui/`
- 兼容性：
  - 旧格式芯片 YAML 照常加载（迁移在内存中进行），设计器保存后变为新格式；两种格式加载出的有效资源相同。
  - 迁移改变了 YAML 内容，内置芯片迁移后重新计算校验和；已固化到项目的副本不受影响，项目里会提示"芯片库有不同版本"（预期）。
  - 硬件映射向导对 CAN、ADC、SPI、Port、Dio、Intc 的映射结果不变（同样的类型名与属性名）。
- **不在本变更范围内**：
  - 外设实例与 `ecu_resources` 之间的一致性（如 `can_controller` 个数与 `Can.MaxModules`）。
  - 为 eth、gpt、icu、lin、mcu、pwm、wdg 填写内置芯片的真实外设数据（需要厂商数据；本变更只让它们能被录入）。
  - 修改映射规则本身。
