## Context

- 通用资源模型（`core/hardware/generic_resource.py`）：`GenericResourceDef(resource_type, resource_id, display_name, properties)`；`ChipDefinitionLoader` 读写 YAML 的 `resources:` 段；`convert_legacy_chip` 把旧芯片的 `can_resources`、`ports`、`adc_resources`、`spi_resources`、`intc_sources` 转成 `can_controller`、`gpio_port`/`gpio_pin`、`adc_unit`、`spi_unit`、`intc_source`。
- 映射规则（`data/mapping_rules/*.yaml`）：每条规则有 `module`、`resource_type`，参数用 `source: "resource.properties.<名>"` 读取实例属性，也可在 `condition` / `enabled_when` 里引用 `resource.properties.<名>`。
- 硬件映射向导：芯片来源是 `ChipDatabase.create_default_database()`（代码里的三颗示例芯片）加 `data/chips` 目录，再逐个 `convert_legacy_chip`。
- 旧字段的读取方：新建项目向导的芯片信息、properties 兜底导出、`resource_mapper.py`（旧映射器，仅被导出，未见调用；已删除）、xdm 提取（构造旧字段）。

## Goals / Non-Goals

- Goals：任意外设类型、每个实例任意属性；一套模型；设计器能录入映射规则需要的数据；向导与项目使用同一颗芯片。
- Non-Goals：外设与 `ecu_resources` 的一致性；补齐内置芯片的其他外设数据；改映射规则。

## Decisions

### D1 YAML 用通用资源格式

```yaml
resources:
  can_controller:
    - resource_id: CAN0
      display_name: CAN Controller 0
      properties: {controller_id: 0, max_baudrate: 1000000, supports_fd: true, mailbox_count: 64}
  gpt_channel:
    - resource_id: GPT0
      display_name: GPT Channel 0
      properties: {channel_id: 0}
```

- 与 `ChipDefinitionLoader` 现有格式相同，不另造格式。
- 类型名、`resource_id` 不能为空；同一类型下 `resource_id` 唯一；属性值为标量或标量列表（与 `ecu_resources` 同样的值限制，复用 `normalize_value`）。不合法时加载失败并指出文件、类型和实例。
- `display_name` 缺省时取 `resource_id`。

### D2 旧字段：加载时迁移，导出只写新格式

- 加载：旧的四个段按 `convert_legacy_chip` 的类型名与属性名转进 `resources`。若某类型在 `resources` 里已存在，以 `resources` 为准并写警告（不合并，避免重复实例）。
- 导出：只写 `resources`，不再写旧段。
- 构造兼容：`ChipDefinition` 保留旧字段，供仍以旧字段构造芯片的代码使用；新增 `effective_resources()` = `resources` ∪ 旧字段转换结果（同类型以 `resources` 为准）。所有读外设的地方改用它。
- `ports` 不动：引脚表有独立的编辑页和数据结构；`gpio_port` / `gpio_pin` 仍由 `ports` 推导，不写进 `resources`，避免两份引脚数据。

备选（不采用）：把旧字段改成只读属性。会破坏现有以关键字参数构造芯片的代码和测试，收益不大。

### D3 映射规则驱动设计器

从规则读出 `{resource_type: (module, 读取的属性集合)}`：属性集合由 `source` 与 `condition` / `enabled_when` 里出现的 `resource.properties.<名>` 收集。设计器用它：

- 可选外设类型 = 规则里的类型 ∪ 芯片已有的类型（显示对应模块名，例如 `gpt_channel (Gpt)`）；也可手输新类型。
- 新增实例时预填该类型规则读取的属性（值为空待填）。
- 实例缺少规则会读的属性时，在该行标出并在页底提示"硬件映射向导将拿不到 X"。
- 规则里没有的类型照样能录入，只是没有预填和提示。

### D4 编辑方式

- 实例表：固定列 `resource_id`、`display_name`，其后每个属性一列（该类型下所有实例属性的并集，按规则属性优先、其余按名称排序）；单元格值按 `infer_scalar` 推断类型，空单元格表示该实例没有这个属性。
- 增加属性列、删除属性列；增删、复制实例。
- 按模式批量添加：前缀、起始编号、个数，例如 `CAN` / 0 / 6 → `CAN0`…`CAN5`；若该类型规则读取某个以 `_id` 结尾的属性（`controller_id`、`unit_id`、`channel_id`），自动填入编号。
- 列表型属性（如 `adc_unit.channels`）在单元格里以逗号分隔编辑。

### D5 硬件映射向导的芯片来源

- 有项目时：芯片 = `chip_for_project(project)` 的结果（项目副本优先，其次芯片库）；芯片列表 = `available_chip_names(project)`；默认选中项目的 `selected_chip`。
- 没有项目时：芯片库。`create_default_database()` 的代码内置芯片只在芯片库中没有同名芯片时使用（保持现状的兜底）。
- 向导直接读芯片的有效资源与 `ports`，`convert_legacy_chip` 改为基于它们构造通用芯片。

## Risks / Trade-offs

- **内置芯片迁移会改变校验和。** 已固化的项目会提示芯片库有不同版本——这是预期提示，内容等价。
- **属性名约定靠规则。** 规则读 `controller_id`，厂商写成 `ctrl_id` 就会被提示缺失；提示是唯一的保护。
- **大芯片的实例数。** 中断源可能上百个；实例表用表格视图，按类型分页显示。

## Migration Plan

1. 先做数据层（D1、D2）和有效资源，所有读取方改用它；旧格式与新格式加载结果相同的测试先通过。
2. 再做向导芯片来源（D5），用现有映射测试确认 CAN、ADC、SPI、Port、Dio、Intc 结果不变。
3. 设计器页（D3、D4）。
4. 最后迁移内置芯片 YAML（设计器载入再保存即可，结果需对比）。
5. 回滚：数据层兼容旧格式，撤销即可。

## Resolved Decisions

1. `resource_mapper.py`（旧版硬件映射器，按代码写死的逻辑生成 Can/Port/Adc/Mcu/Intc 配置动作，与内存映射无关）没有调用方，随本变更删除，`core.hardware` 不再导出 `HardwareResourceMapper`、`MappingAction`、`MappingActionType`（向导使用的 `Generic*` 名称不变）。
2. `THA6206.yaml` 与 `THA6206_LFBGA292.yaml` 芯片名相同、被后者覆盖：把前者独有的外设（`clock_source`、`gpt_channel`、`lin_channel`、`pwm_channel`、`wdg_unit`）和 `metadata.vendor` 并入后者，冲突项保留后者的值，`gpio_port` 不并入（端口以引脚表为准），然后删除前者。
