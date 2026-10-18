## 1. 数据层
- [x] 1.1 `ChipDefinition.resources`（`{类型: [GenericResourceDef]}`）；YAML `resources` 段的加载、导出、校验（类型与 `resource_id` 非空、同类型 `resource_id` 唯一、属性值复用 `normalize_value`）
- [x] 1.2 旧段迁移：`can_resources`、`adc_resources`、`spi_resources`、`intc_sources` 按 `convert_legacy_chip` 的类型名与属性名转入 `resources`；同类型已存在时以 `resources` 为准并警告；导出只写 `resources`
- [x] 1.3 `effective_resources()`：`resources` ∪ 旧字段转换结果；`convert_legacy_chip`、properties 兜底导出、新建项目向导芯片信息改读它；删除未被调用的旧映射器 `resource_mapper.py`
- [x] 1.4 测试：旧格式与新格式加载出相同的有效资源；导出→加载往返无损；非法类型、重复 `resource_id`、非法属性值被拒绝并指出位置；旧字段构造的芯片照常可用

## 2. 映射规则信息
- [x] 2.1 从规则读出 `{resource_type: (module, 读取的属性)}`（`source`、`condition`、`enabled_when` 中的 `resource.properties.<名>`）
- [x] 2.2 测试：13 条内置规则的类型与属性集合

## 3. 硬件映射向导
- [x] 3.1 有项目时芯片来自 `chip_for_project` / `available_chip_names`，默认选中项目芯片；无项目时芯片库优先，代码内置芯片只作兜底
- [x] 3.2 向导读有效资源与 `ports` 构造通用芯片
- [x] 3.3 测试：CAN、ADC、SPI、Port、Dio、Intc 的映射动作与改动前相同；只存在于项目 `chips/` 的芯片能被选中并映射；新类型（如 `gpt_channel`）的实例能被 Gpt 规则映射

## 4. 设计器外设页
- [x] 4.1 类型列表（实例数、对应模块）：新增 / 删除类型；可选类型来自规则，也可手输
- [x] 4.2 实例表：`resource_id`、`display_name` 与属性列；增删 / 复制实例；增删属性列；单元格按 `infer_scalar` 推断类型；列表属性逗号分隔
- [x] 4.3 按模式批量添加，`*_id` 属性自动编号
- [x] 4.4 新增实例预填规则属性；缺少规则属性时标出并提示
- [x] 4.5 移除旧的 CAN、ADC、SPI 固定组；载入、克隆、保存都经过 `resources`
- [x] 4.6 测试：任意类型可增删；每实例属性独立保存（不再被全局值覆盖）；批量添加与编号；缺属性提示；保存后加载一致

## 5. 内置芯片与文档
- [x] 5.1 内置芯片 YAML 迁移为 `resources` 格式（载入再保存），对比迁移前后的有效资源相同；`THA6206.yaml` 独有外设并入 `THA6206_LFBGA292.yaml` 后删除
- [x] 5.2 `doc/chip_ecu_resources.md`：外设实例的格式、与映射规则的关系、向导的芯片来源
- [x] 5.3 `python -m pytest tests -q`（排除已知卡死的 `tests/ui/test_davinci_integration.py`）
- [x] 5.4 `openspec validate generalize-chip-peripheral-resources --strict`
