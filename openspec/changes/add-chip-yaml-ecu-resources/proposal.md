## Why

模板和 xdm 通过 `ecu:get()` / `ecu:list()` 读取"按芯片区分的资源常量"（核数、核名、主核、ISR 触发方式、各外设数量等）。目前这些常量只能来自厂商的 `*.properties` 文件，存在四个问题：

1. **新建项目拿不到。** `ProjectController.new_project()` 与 `add_module_to_project()` 都不调用 `WorkspaceProject.load_ecu_resources()`；只有"打开项目"和"导入 EB 项目"才读。新建的项目 `ecu_resources` 为空，且项目里没有 `Def/`，生成器也找不到文件。
2. **芯片与文件靠文件名匹配。** `resource_file_matches_chip` 按文件名的下划线片段判断；EB 里真正的映射（`plugin.xml` 的 `ecuresource/subderivative`）工具从不读取，两边可能选出不同的文件。
3. **缺键时静默出错。** `ecu:get()` 找不到键时生成器（`strict=False`）不报错，Os 等模块会静默生成缺少核数、主核的代码，与"不要生成看似合理的默认输出"的项目约束冲突。
4. **两套读取逻辑。** `WorkspaceProject.load_ecu_resources()` 与 `CodeGenerator._load_ecu_resources()` 各自扫描、各自过滤，搜索范围不同（前者含模块定义路径，后者含模板目录）；四个 `CodeGenerator(...)` 调用点都没有把前者的结果传给生成器。

作为芯片厂商，我们自己维护这些数据，客户不会在 EB Tresos 里使用导出的 properties。因此决定：**芯片 YAML 是权威来源，`.properties` 只作为迁移时的导入来源，以及用于往返校验的导出产物**。

## What Changes

- **芯片 YAML 新增 `ecu_resources` 段**：按模块分组的键值表，完整键为 `<Module>.<name>`（如 `OsResource.NumOfCores`），值为标量或列表；同时新增 `resource_version`。字段缺省时行为与现在完全一致。
- **长列表允许区间写法**：列表值可写成"下标区间 → 值"的映射（如 `0-15: 1`），加载时展开成完整列表，用于 `Os.IsrTriggerMethodList` 这类 992 项的数据。
- **`ChipDefinition` 增加 `ecu_resources`**：`ChipDatabase._load_chip_from_yaml` 与 `ChipDefinitionExporter.to_yaml_dict` 无损往返；没有建模的键原样保存，不丢弃。
- **properties → YAML 导入**：复用 `TresosPropertiesParser`，把一个或多个 properties 文件的全部键并入芯片的 `ecu_resources`，不按模块硬编码建模。
- **YAML → properties 导出**：按模块各写一个文件，内容只来自 `ecu_resources`，不再混入硬编码常量（如 `Can.MaxHwObjects: 512`）。旧的 `to_properties_string` 在芯片没有 `ecu_resources` 时保持原输出。
- **统一解析入口 `EcuResourceResolver`**：合并"插件 properties（低）→ 芯片 YAML（高）"，结果存入 `project.ecu_resources`。在新建项目、打开项目、导入 EB 项目、添加模块、更换芯片五个时机调用。
- **生成器使用项目已有的字典**：四个调用点传入 `ecu_resources=project.ecu_resources`；生成器自己的扫描仅保留给没有项目的场景。
- **缺键与一致性诊断**：加载模块时收集 xdm 和模板里引用的 `ecu:get/ecu:list` 键（复用 `extract_xdm_resources`），与 `ecu_resources` 比对，向用户报告缺失键与未使用键；并对已知键做一致性检查（核数与核名个数、主核在核名之内且使用 `CORE<n>` 写法、`*Num` 与列表长度）。诊断只提示，不阻断生成。

## Impact

- Affected specs: `chip-ecu-resources`（新增能力）；与待归档的 `chip-management`（`add-chip-definition-designer`）有关联：本变更扩展它的 YAML schema 与 properties 导出要求，不修改其已有要求。
- Affected code:
  - `autosar_configurator/core/hardware/chip_database.py`（`ChipDefinition`、YAML 加载）
  - `autosar_configurator/core/hardware/chip_exporter.py`（YAML 导出、properties 导出）
  - `autosar_configurator/core/hardware/ecu_resource_resolver.py`（新增）
  - `autosar_configurator/core/hardware/tresos_properties_parser.py`（只增加"全量取键"的辅助函数，不改现有解析行为）
  - `autosar_configurator/core/workspace_manager.py`（`load_ecu_resources` 委托给 Resolver）
  - `autosar_configurator/ui/controllers/project_controller.py`、`generation_controller.py`、`ui/dialogs/project_properties_dialog.py`、`ui/widgets/davinci_tree_view.py`（调用点）
  - `autosar_configurator/generator/generator.py`（优先使用传入的 `ecu_resources`）
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`（导入 / 预览 `ecu_resources`，见 tasks 第 7 组）
  - 测试：`tests/core/`、`tests/generator/test_ecu_resources_merge.py`
- 兼容性：
  - 已有芯片 YAML 不需要修改。
  - 已有 EB 导入项目：生成结果不得变化（需运行 `verify_fingerprints.py`，并保持排序与遍历顺序）。
  - **不在本变更范围内**：生成 EB 插件的 `plugin.xml`（`ecuresource` 段，客户不在 EB 中使用导出文件）；读取 `plugin.xml`；项目级用户覆盖值。
  - 首批导入与往返验证只覆盖两类文件：`Os_Resource_*.properties` 与 `CotexR52_*.properties`（Resource 插件）。
- 验证限制：Os 插件（`Os.xdm`、`templates/Os/`）不在本仓库，无法在本机核实 `Os.*`、`OsResource.*` 各键是否被实际读取，"必须 / 无用"的结论要等第 6 组诊断功能在带有 Os 插件的项目上运行后才能确定。
