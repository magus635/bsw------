# 工程经验教训 (Lessons Learned)

## 多变体与模板查找审查改进记录 (2026-11-23)

1. **保持公共构造函数既有优先级语义，不悄悄反转默认参数优先级**
   - `EBTemplateEngine.__init__(..., template_dir=..., include_search_paths=...)` 原先约定 `template_dir` 优先于补充目录 `include_search_paths`；直接把 `include_search_paths` 放到 `template_dir` 前面会破坏既有直接调用方的预期。
   - 正确做法：通过新增显式参数 `priority_include_paths` 表达“高优先级覆盖层 > `template_dir` > `include_search_paths` 回退目录”，并在下层 `Renderer.__init__` 中基于 `.resolve()` 路径去重且避免在 `template_dir=None` 时把 `Path(".")` 抢插到 `include_search_paths` 首位。

2. **不要无条件把 `template_source_dir.parent` 加入 `INCLUDE` 搜索路径**
   - 当 `template_source_dir` 恰好是模块包模板根目录（如 `package_template_dir`）时，添加 `.parent` 会暴露整个包根目录；当它是工程覆盖层目录（如 `templates/<Variant>/`）时，添加 `.parent` 会让 `templates/` 在 `package_template_dir` 之前被搜索，并与其他回退路径产生重复。
   - 应由 `CodeGenerator._split_include_search_paths()` 显式划分优先级列表，包内相对子目录宏查找通过包目录与显式子目录列表覆盖。

3. **跨模块与多变体边界条件务必按目标模块作用域严格隔离，保持多入口策略一致**
   - `ConfigurationManager.load_configuration()` 检查互斥厂商定义时，只应统计匹配当前 `module_name` 的配置块（不能被同文件中其他无关模块的 `DEFINITION-REF` 干扰）。
   - 当模块本身已绑定到特定厂商定义（`is_specific_def=True`）时，无论文件中出现 1 个还是多个其他厂商变体块，均应与 `DaVinciProjectImporter._extract_module_config()` / `eb_import.epc_names_definition()` 保持一致：仅允许精确匹配或 `/AUTOSAR/EcucDefs/<Module>`/空引用回退，不静默降级加载错误厂商变体。

4. **修改定义路径匹配契约时全库检索所有调用点**
   - 修改 `same_definition()` / `module_relative()` 行为后，需同步检索全部生产代码调用方（包括 `DependencyRule`、`QuickConfigWizard` 等校验规则与辅助向导），确保混合对比厂商多段路径与标准路径时显式传递 `module_name`。

5. **核对多入口一致性时必须逐条核验完整契约（含无匹配返回值/异常行为、标准路径边界与调用方处理）**
   - 仅看到 `DaVinciProjectImporter._extract_module_config()` 跳过了错厂商块就误判其与 `ConfigurationManager.load_configuration()` 一致，会遗漏“无匹配时静默返回 `None` 导致 `import_project()` 默默退回空白 `sip_baseline`”、“未排除 `expected_def_ref == std_ref`”、以及“无 `<ModuleDefinitionMapping>` 时未回退到 `pkg.manifest.definition`”的差异。今后对照多入口一致性时，必须按完整输入/输出与异常状态表逐项核对，包括外层调用方的错误处理。

