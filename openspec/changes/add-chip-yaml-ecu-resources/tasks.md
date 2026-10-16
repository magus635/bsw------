## 1. 数据模型与 YAML
- [x] 1.1 `ChipDefinition` 增加 `ecu_resources: Dict[str, Dict[str, Any]]` 与 `resource_version: str`，默认值为空
- [x] 1.2 `ChipDatabase._load_chip_from_yaml` 读取 `ecu_resources` 与 `resource_version`；字段缺失时行为不变；值类型只接受标量或标量列表，其余报明确的错误
- [x] 1.3 `ChipDefinitionExporter.to_yaml_dict` 输出这两个字段，保持与加载器无损往返
- [x] 1.4 测试：缺省、标量、列表、含点号的键（如 `SyncGroup.Master.SARADC0`）的 YAML 往返；旧 YAML 加载结果不变
- [x] 1.5 区间写法：加载时把"下标区间 → 值"的映射展开为完整列表；缺口、重叠、超出范围、非法键都报错并指出键
- [x] 1.6 YAML 导出：列表至少 16 项且区间条目数更少时输出区间写法，否则输出普通列表
- [x] 1.7 测试：区间与普通列表加载结果相同；992 项触发方式往返相同；各类非法区间的错误信息

## 2. properties 导入
- [x] 2.1 `tresos_properties_parser.py` 增加全量取键的辅助函数：把解析结果按模块（键的第一个 `.` 之前）归入 `ecu_resources`，不做外设建模
- [x] 2.2 `ChipDatabase` 增加 `import_ecu_resources_from_properties(chip, paths)`；多个文件并入同一芯片；同键后者覆盖前者并记录日志
- [x] 2.3 测试：用 `Os_Resource_THA6412.properties` 与 `CotexR52_THA6412_BGA516.properties` 导入，键总数与逐项取值断言；续行、空行、注释打断续行的情形

## 3. properties 导出
- [x] 3.1 `to_properties_string` 在 `chip.ecu_resources` 非空时，按模块输出文件内容；键与值逐项取自该字段，不补默认值；版本与文件名取自芯片数据
- [x] 3.2 `chip.ecu_resources` 为空时保持旧输出，现有 `tests/core/test_chip_designer.py` 不改
- [x] 3.3 测试：导入 → 导出 → 再导入，扁平键值完全相同（两份样例文件）；导出内容确定（重复导出字节相同）

## 4. 统一解析入口
- [x] 4.1 新增 `core/hardware/ecu_resource_resolver.py`：`resolve(project, chip_database) -> dict`；properties 部分搬入现有 `load_ecu_resources` 的扫描与过滤逻辑，行为不变
- [x] 4.2 合并规则：properties 低、芯片 YAML 高；同键不同值时记录 INFO；更换芯片时整体重算
- [x] 4.3 `WorkspaceProject.load_ecu_resources` 委托给 Resolver
- [x] 4.4 接入五个时机：`ProjectController.new_project`、打开项目（`load_project` / `_load_project_at_path`）、`import_eb_project`、`add_module_to_project`、更换芯片（项目属性）
- [x] 4.5 测试：新建项目选芯片后 `ecu_resources` 非空；更换芯片后旧键不残留；导入 EB 项目的结果与改动前逐键一致

## 5. 生成器
- [x] 5.1 `generation_controller.py`（两处）、`project_properties_dialog.py`、`davinci_tree_view.py` 的 `CodeGenerator(...)` 传入 `ecu_resources=project.ecu_resources`
- [x] 5.2 `CodeGenerator` 在收到 `ecu_resources` 时不再扫描；未收到时保留现有扫描
- [x] 5.3 运行 `tests/generator/test_ecu_resources_merge.py` 与 `verify_fingerprints.py`（若存在），确认导入项目的生成结果与指纹无变化

## 6. 诊断
- [x] 6.1 键需求扫描：对已加载模块的 xdm 和 `templates/{Module}/` 收集 `ecu:get/ecu:list` 引用的键
- [x] 6.2 比对并生成报告：缺失键（警告）、未引用键（信息）；在 UI 状态栏或日志面板展示，不阻断生成
- [x] 6.3 一致性检查表：`NumOfCores` ↔ `AvailableCores` 个数；`MasterCore` 必须是 `CORE<n>` 写法且属于 `AvailableCores`（其他写法只报警，不转换）；`IocPrimitiveDataTypeNum` ↔ `IocPrimitiveDataType` 个数；规则以表声明
- [x] 6.4 测试：缺失键、多余键、个数不一致、主核不在核名内、主核写法为 `OS_CORE_ID_0` 各一例；动态拼接键不产生缺失误报

## 7. 设计器与文档
- [x] 7.1 `ChipDefinitionDesignerDialog` 增加"导入 properties"和"ECU 资源"只读预览（编辑留待后续）；保存时写入 `ecu_resources`
- [x] 7.2 `ChipDefinitionDesignerDialog` 导出 properties 使用 D5 的新路径
- [x] 7.3 文档：YAML `ecu_resources` 格式、与 properties 的关系、"properties 为生成物"的约定

## 8. 验证
- [ ] 8.1 `python -m pytest tests/core/test_parser_serializer.py tests/core/test_command.py -q`
- [ ] 8.2 `python -m pytest tests/generator -q`、`QT_QPA_PLATFORM=offscreen python -m pytest tests/ui -q`
- [ ] 8.3 `openspec validate add-chip-yaml-ecu-resources --strict`
- [ ] 8.4 用带有 Os 插件的真实项目运行诊断，据结果确认 `Os.*`、`OsResource.*` 各键哪些必须、哪些无用；并对照生成结果确认 `OsResource.MasterCore` 改成 `CORE0` 写法后输出是否变化，把结论写回文档
