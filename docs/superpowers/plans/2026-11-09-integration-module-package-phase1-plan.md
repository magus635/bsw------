# 集成模块包 · 阶段 1 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal：** 交付设计方案的阶段 1（W1、W2、W4、W6、W9）。完成后：

- 一个模块的 define、pre、rec 放在同一个模块包目录里；
- 加载时由基线层自动导入 pre，并用三方合并保护用户修改；
- 工程目录由 `.dpa` format 8 管理，代码里不再写死目录名；
- EB 插件目录不做改造就能作为模块包使用；
- 旧工程（format ≤ 7）照常打开，生成结果不变。

**Architecture：** 新增两个纯 Python 子包，都不依赖 UI：

- `core/packages/`：模块包的清单、EB 插件推断、值集合索引与包内合并、模块库；
- `core/baseline/`：值展平、基线合成、三方合并、快照存取、值来源判定。

`core/project_paths.py` 统一解析工程目录。`WorkspaceManager` 只在 format 8 分支调用这些模块；format ≤ 7 的分支保持现状。只读锁定放在 `ConfigurationManager` 和 `ui/commands.py` 这两个修改入口。

**Tech Stack：** Python 3.11、lxml、PySide6、pytest。

**Spec：** `docs/superpowers/specs/2026-11-09-integration-module-package-design.md`（第 6 节为主，第 11 节为已定决策）

## Global Constraints

- 新工程 `format_version` = 8。format ≤ 7 的工程**按原逻辑加载和保存，并且保存后仍是 7**，本阶段不自动升级（升级命令属于阶段 2 的 W8）。
- format 8 的目录默认值：`config`=`config`，`base`=`config/base`，`templates`=`templates`，`gen`=`gen`，`gen_layout`=`flat`，`chips`=`chips`，`integration`=`integration`，`system`=`system`，`history`=`.history`，`modules`=`modules`。
- format ≤ 7 的目录：配置值 `ConfigValue/`、模板 `templates/`、输出 `generateCode/<Module>/`、EB 插件 `Def/plugins/`，都由 `ProjectDirectories.legacy()` 给出。
- `.dpa` 中的路径一律用 POSIX 风格：工程目录内存相对路径，工程目录外存绝对路径。
- 凡是遍历集合并影响输出的地方都用 `sorted()`；生成器指纹只按模板内容计算（`generator.py:675`），这个规则不变。
- 基线层的层次和优先级：DEFAULT < REC < DERIVED < PRE。本阶段 DERIVED 层为空，但接口必须接受它（设计 §8，用户 2026-11-09 说 Os、通信矩阵、Runnable 改得多）。
- DEFAULT 层只用定义里的静态默认值 `default_value`，不计算 `default_expr` 和 XPath 默认值，以保证基线可复现。
- 三方合并**从不自动删除**容器或值；凡有改动，先经过 `confirm` 回调，回调返回 False 时 Active 和 Base 都不变。
- 值来源 `origin` 不写进配置 arxml；配置 arxml 格式不变。
- Pre 角色和 Rec 角色**按 AUTOSAR 路径**判定，不按文件名判定；一个文件里可以同时有 Pre 和 Rec。
- EB 插件中的 `autosar/<模块>_<芯片>.arxml` 不加载，只记为 `exchange_copies`。
- 不修改 `D:\davinci` 下的任何文件；仓库里不放 Vector 的文件。
- 不提供运行时默认模板（`openspec/project.md`）。
- 每个任务完成后运行 `python -m pytest tests/core -q`，已知的无关失败除外；改动模型或序列化后，额外运行 `python -m pytest tests/core/test_parser_serializer.py tests/core/test_command.py -q`。

## Review Focus

1. **容器实例名对不上**：用户把 Rec 创建的容器改了名，或者 Pre 删掉了一个容器。期望：合并时不删除任何东西，报告中列出 `removed_in_base`。对应测试 `test_merge_never_deletes_renamed_or_removed`（Task 8）。
2. **多值参数和多值引用**出现在 Pre 中。期望：作为有序列表整体比较、整体强制，不按元素拆开合并。对应测试 `test_merge_multi_values_compared_as_list`（Task 8）。
3. **工程或模块库路径含中文或空格，或位于工程目录之外**（仓库本身就在 `D:\bsw-------main` 下）。期望：保存后再打开，路径一致，并以 POSIX 风格存储。对应测试 `test_v8_paths_non_ascii_and_external_roundtrip`（Task 2）。
4. **基线快照丢失，或哈希与 `.dpa` 记录不一致**。期望：按“旧工程迁移”处理，所有值视为 USER，只有 Pre 会改值，并且必须经过 `confirm`。对应测试 `test_base_missing_or_tampered_treated_as_migration`（Task 9）。
5. **通过非面板入口修改被 Pre 锁定的值**，包括批量向导、粘贴容器、改名、改引用、导入值文件。期望：
   - 前四种入口直接拒绝修改，并给出 `PreLockedError` 信息；
   - 导入值文件后，下次合并时 Pre 被强制恢复，并写入报告。

   对应测试 `test_lock_blocks_all_mutation_entries`（Task 11）。

---

### Task 0：OpenSpec 提案（获批后才能开始 Task 1）

**Files：**
- Create：`openspec/changes/add-integration-module-packages/proposal.md`、`tasks.md`、`design.md`
- Create：`openspec/changes/add-integration-module-packages/specs/module-packages/spec.md`、`specs/config-baseline/spec.md`、`specs/project-file/spec.md`（format 8 目录表，ADDED）、`specs/config-templates/spec.md`（MODIFIED：模板查找顺序“覆盖层 → 包”）

- [ ] **Step 1：** 阅读 `openspec/AGENTS.md`，按其中的格式编写上述文件。
  - `proposal.md` 的 Why 引用设计方案 §3 的 P1–P9；
  - `design.md` 链接设计方案，不复制正文；
  - 每条 Requirement 至少有一个 Scenario，场景取自设计方案 §12 的验收 1–8；
  - `tasks.md` 与本计划的 Task 1–14 一一对应。
- [ ] **Step 2：** 运行 `openspec validate add-integration-module-packages --strict`。期望输出：`is valid`。
- [ ] **Step 3：** 提交（`docs: propose add-integration-module-packages`），然后**停下，等用户批准**。

---

### Task 1：工程目录解析 `ProjectDirectories`（W1）

**Files：**
- Create：`autosar_configurator/core/project_paths.py`
- Modify（把写死的目录名改为调用 `project_paths`）：
  - `core/workspace_manager.py:139,896,906-907,951,1121,1537`
  - `generator/generator.py:51-62,118-150`（新增 `project_root` 参数）
  - `ui/controllers/generation_controller.py:107,162,338`
  - `ui/dialogs/project_properties_dialog.py:296`
  - `ui/widgets/davinci_tree_view.py:133`
  - `core/hardware/ecu_resource_diagnostics.py:94`
  - `core/hardware/ecu_resource_resolver.py:49-57`
  - `core/chip_constraint_service.py:166,191,236`
  - `core/hardware/chip_database.py:667`
  - `core/hardware/xdm_chip_extractor.py:338`
  - `core/memmap/check.py:92`
- Test：`tests/core/test_project_paths.py`

**Interfaces：**
- Produces：
  - `@dataclass(frozen=True) ProjectDirectories`，字段：`config, base, templates, gen, gen_layout, chips, integration, system, history, modules, legacy_plugins`（都是 `str`，POSIX 风格，相对于工程根）；
  - 类方法：`ProjectDirectories.default_v8()`、`ProjectDirectories.legacy()`、`ProjectDirectories.from_dict(d: dict, fallback: "ProjectDirectories")`；实例方法 `to_dict() -> dict`。
  - `project_root(project) -> Path`：取 `.dpa` 所在目录。
  - `dirs(project) -> ProjectDirectories`：读 `project.directories`，没有时用 `legacy()`。
  - `resolve(project, key: str) -> Path`。
  - `config_file(project, module: str) -> Path`：v8 为 `config/<M>.arxml`，legacy 为 `ConfigValue/<M>_Config.arxml`。
  - `gen_dir(project, module: str) -> Path`：`flat` 时为 `gen/`，legacy 为 `generateCode/<M>/`。
  - `WorkspaceProject.directories: Optional[ProjectDirectories] = None`。
  - `CodeGenerator.__init__(..., project_root: Optional[Path] = None)`：传入时直接使用，不再向上查找；只有为 None 时才走原来的查找逻辑，以兼容现有测试。

- [ ] **Step 1：** 写失败测试：
  - `test_legacy_dirs_match_old_names`：对 `directories=None` 的工程，`config_file(p,"Mcu")` 等于 `<root>/ConfigValue/Mcu_Config.arxml`，`gen_dir(p,"Mcu")` 等于 `<root>/generateCode/Mcu`，`resolve(p,"templates")` 等于 `<root>/templates`；
  - `test_v8_dirs_flat_gen`：`gen_dir` 等于 `<root>/gen`，`config_file` 等于 `<root>/config/Mcu.arxml`；
  - `test_generator_uses_given_project_root`：给出 `project_root` 时，即使模板目录的上级有 `Def/`，资源扫描也只在 `project_root` 下进行。
- [ ] **Step 2：** 运行 `python -m pytest tests/core/test_project_paths.py -v`。期望：FAIL（ImportError）。
- [ ] **Step 3：** 实现 `project_paths.py`，并替换上面列出的每一处写死路径；每个 UI 调用点都把 `project_root(project)` 传给 `CodeGenerator`。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_project_paths.py -v`，期望 PASS。再运行 `python -m pytest tests/core -q`，期望没有新增失败。
- [ ] **Step 5：** 用 Grep 搜索 `"ConfigValue"|"generateCode"|"Def" / "plugins"|/ "templates"`，命中只允许出现在 `project_paths.py` 中。
- [ ] **Step 6：** 提交：`refactor(project): resolve project directories via ProjectDirectories`。

### Task 2：`.dpa` format 8 的读写（W1）

**Files：**
- Modify：`core/workspace_manager.py`（`create_project`、`save_project`、`load_project`、`WorkspaceProject.__init__`）
- Test：`tests/core/test_dpa_format8.py`

**Interfaces：**
- Consumes：Task 1 的 `ProjectDirectories`。
- Produces：
  - `WorkspaceProject.format_version: int`：新建工程为 8，加载时取文件中的值；
  - `WorkspaceProject.module_libraries: List[LibraryRef]`，其中 `@dataclass LibraryRef(path: str, kind: Literal["package","eb-plugins"], exclude: List[str])`，定义在 `core/packages/library.py`，本任务先建一个只有 dataclass 的文件；
  - `WorkspaceProject.module_entries: Dict[str, ModuleEntry]`，其中 `@dataclass ModuleEntry(name, definition, library: int, config_path, pre_unlocked: List[str], package_record: dict, base_hash: Optional[str])`，定义在 `core/workspace_manager.py`；
  - `WorkspaceManager.create_project(name, path, format_version: int = 8)`。
- `load_project` 接受的最高版本从 7 改为 8；format 8 的模块加载留给 Task 6，本任务只读写字段。

- [ ] **Step 1：** 写失败测试：
  - `test_v8_roundtrip_fields`：`directories`、`module_libraries`、`modules[]` 的每个字段保存后再加载，结果相同；
  - `test_v7_stays_v7_on_save`：加载 `tests/test_data/test_project.dpa`（或一个临时的 v7 文件）后保存，`format_version` 仍为 7，`modules[].def_path` 原样保留；
  - `test_v8_paths_non_ascii_and_external_roundtrip`（Review Focus 3）：工程放在 `tmp_path/"中文 目录"`，一个库在工程内、一个库在 `tmp_path` 之外；保存后 JSON 中，内部库是相对路径、外部库是绝对路径，两者都只含 `/`；再次加载后 `resolve` 得到的路径与原路径相同。
- [ ] **Step 2：** 运行这些测试，期望 FAIL。
- [ ] **Step 3：** 实现：`save_project` 按 `format_version` 分支（7 走原路径，8 写新字段）；`load_project` 对 8 读入新字段。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_dpa_format8.py tests/core/test_eb_import_modes.py tests/core/test_workspace.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(project): .dpa format 8 directories, libraries and module entries`。

### Task 3：模块包清单与 EB 插件推断（W2）

**Files：**
- Create：`autosar_configurator/core/packages/__init__.py`、`manifest.py`、`eb_plugin.py`、`errors.py`
- Test：`tests/core/packages/test_manifest.py`、`tests/core/packages/test_eb_plugin.py`
- Fixture：直接使用仓库中的 `test_import_project/Def/plugins/Mcu_THA6_AS440`、`Can_THA6_AS440`（只读）

**Interfaces：**
- Produces：
  - `errors.py`：`class PackageError(Exception)`；`class PackageConflictError(PackageError)`，带属性 `path: str` 和 `files: List[str]`。
  - `@dataclass PackageFile(path: str, chips: List[str] = [])`。
  - `@dataclass ModuleManifest`，字段：`module, definition, implementation_path: Optional[str], files: List[PackageFile], pre: List[str], rec: List[str], templates: Optional[str], resources: Optional[str], implementation: Optional[str], exchange_copies: List[str], origin: dict, inferred: bool, chip_selector: Optional[dict]`。
  - `load_manifest(pkg_dir: Path) -> ModuleManifest`：读 `module.json`（`schema` 必须为 1，否则抛 `PackageError`）。
  - `write_manifest(pkg_dir: Path, m: ModuleManifest) -> None`：键按排序输出，路径用 POSIX 风格。
  - `infer_from_plugin_xml(plugin_dir: Path) -> ModuleManifest`，规则：
    - schema 下的 `<resource type="xdm">`，只要没有被任何 `<preconfig resourceId>` 引用，就进入 `files`；
    - preconfig 资源文件也进入 `files`；
    - `<preconfig path="ASPath:X">` 中的 X 进入 `pre`；
    - `<data><schemaNode path>` 中的路径是 `definition`；
    - `autosar/*.arxml` 进入 `exchange_copies`；
    - 有 `generate_PB/` 时 `templates` 为 `"generate_PB"`；
    - 有 `resource/` 时 `resources` 为 `"resource"`；
    - `module` 取 `definition` 的最后一段；`inferred=True`。
  - `infer_package(pkg_dir: Path) -> ModuleManifest`：有 `module.json` 就读清单，否则有 `plugin.xml` 就推断，两者都没有时抛 `PackageError`。

- [ ] **Step 1：** 写失败测试：
  - `test_mcu_plugin_inferred`：`definition=="/THA6_AS440_FuSa/Mcu"`，`pre==["/THA6_AS440_FuSa/McuPreConfiguration"]`，`files` 的路径集合为 `{"config/Mcu.xdm","config/McuPreConfiguration.xdm"}`，`exchange_copies` 含 3 个 `autosar/Mcu_*.arxml`，`templates=="generate_PB"`；
  - `test_can_plugin_has_no_pre`：`pre==[]`；
  - `test_manifest_roundtrip`：`write_manifest` 后再 `load_manifest`，结果相等；
  - `test_manifest_bad_schema_rejected`：`schema` 为 2 时抛 `PackageError`。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现 `manifest.py`、`eb_plugin.py`、`errors.py`。解析 `plugin.xml` 时用 `etree.XMLParser(resolve_entities=False, no_network=True)`。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/packages -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(packages): module manifest and EB plugin.xml inference`。

### Task 4：值集合索引与包内按路径合并（W2）

**Files：**
- Create：`autosar_configurator/core/packages/value_index.py`
- Modify：`core/parser/xdm_config_parser.py`，新增 `parse_all`
- Test：`tests/core/packages/test_value_index.py`

**Interfaces：**
- Produces：
  - `XdmConfigParser.parse_all(file_path: Path) -> List[Tuple[str, EcucModuleConfiguration]]`：返回文件中**每一个** `MODULE-CONFIGURATION` 的 `(AR 路径, 配置)`。AR 路径 = `/` + 外层各级 `AR-PACKAGE` 的名字 + `/` + `d:chc` 的 `name`。
  - `index_value_collections(file: Path) -> Dict[str, List[EcucModuleConfiguration]]`：键是 AR 完整路径（逐级拼接 `AR-PACKAGE` 的 SHORT-NAME，再拼元素自己的 SHORT-NAME）。`.arxml` 用 `ArxmlParser.parse_ecuc_configuration_values(elem)` 解析，`.xdm` 用 `parse_all`。
  - `load_value_collection(files: List[Path], ar_path: str) -> Optional[EcucModuleConfiguration]`：把这些文件中所有该路径的片段按容器名递归合并。同一参数取值不同时抛 `PackageConflictError(path=<容器路径.参数>, files=[...])`。一个片段都没有时返回 None。

- [ ] **Step 1：** 写失败测试，夹具在 `tmp_path` 中手写：
  - `test_one_file_holds_pre_and_rec`：一个 arxml 中包含 `/MICROSAR/X_Pre` 和 `/MICROSAR/X_Rec`，索引出两个键，各自的容器互不混入；
  - `test_same_path_two_files_merged`：两个文件都声明 `/MICROSAR/X_Pre`，各带一个不同的容器，合并后两个容器都在；
  - `test_same_param_conflict_raises`：两个文件中同一参数分别为 1 和 2，抛 `PackageConflictError`，`e.files` 含这两个文件名；
  - `test_xdm_preconfiguration_indexed`：`Mcu_THA6_AS440/config/McuPreConfiguration.xdm` 索引出键 `/THA6_AS440_FuSa/McuPreConfiguration`，其下有容器 `McuPublishedInformation`；
  - `test_nested_package_path`：`/MICROSAR/VTT/X_Pre` 的嵌套包路径正确。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/packages/test_value_index.py tests/core/test_xdm_value_import.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(packages): index value collections by AR path and merge within a package`。

### Task 5：`ModulePackage`、芯片条件与模块库（W2）

**Files：**
- Create：`autosar_configurator/core/packages/package.py`
- Modify：`autosar_configurator/core/packages/library.py`
- Test：`tests/core/packages/test_package.py`、`tests/core/packages/test_library.py`

**Interfaces：**
- Consumes：Task 3 的 `infer_package`、`ModuleManifest`；Task 4 的 `load_value_collection`。
- Produces：
  - `class ModulePackage(root: Path, manifest: ModuleManifest)`，方法：
    - `selected_files(chip: Optional[str]) -> List[Path]`：`chips` 为空的文件总是选中；`chips` 非空时，`chip` 在列表中才选中；结果排序。
    - `definition_file(chip) -> Path`：在选中的文件中找含 `ECUC-MODULE-DEF` 的文件。arxml 用 SHORT-NAME 路径匹配 `definition`；xdm 用 `MODULE-DEF` 的 ASPath 匹配。多于一个时抛 `PackageConflictError`，一个都没有时抛 `PackageError`。
    - `load_pre(chip) -> List[EcucModuleConfiguration]`、`load_rec(chip) -> List[EcucModuleConfiguration]`：对 `pre`/`rec` 中的每个路径调用 `load_value_collection`；某个路径找不到时记一条 warning（`self.warnings: List[str]`），不抛异常。
    - `template_dir() -> Optional[Path]`、`resource_dir() -> Optional[Path]`。
  - `scan_library(ref: LibraryRef, base: Path) -> List[ModulePackage]`：`package` 类型扫一级子目录中的 `module.json`；`eb-plugins` 类型扫一级子目录中的 `plugin.xml`；跳过 `exclude` 中的目录名；不解析定义；按目录名排序。
  - `find_package(libraries: List[Tuple[int, List[ModulePackage]]], definition: str) -> Tuple[int, ModulePackage]`：同一 `definition` 出现在多个包中时抛 `PackageConflictError`，找不到时抛 `PackageError`。

- [ ] **Step 1：** 写失败测试：
  - `test_chip_selects_pre_file`：两个 pre 文件，分别带 `chips=["A"]` 和 `["B"]`；`chip="B"` 时只选中后者；
  - `test_two_pre_same_chip_conflict`：两个文件都带 `chips=["A"]`，同一参数取值不同；`load_pre("A")` 抛 `PackageConflictError`，并指出这两个文件；
  - `test_missing_pre_path_warns`：`pre` 中的路径在任何文件里都不存在时，`warnings` 非空，不抛异常；
  - `test_eb_library_scan`：以 `test_import_project/Def/plugins` 作为 `eb-plugins` 库，扫描结果按名字排序，含 `Mcu`，不含 `exclude` 中的插件；
  - `test_duplicate_definition_across_libraries`：两个库都提供 `/THA6_AS440_FuSa/Mcu` 时，`find_package` 抛 `PackageConflictError`。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/packages -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(packages): ModulePackage chip selection and module libraries`。

### Task 6：format 8 工程按模块包加载和添加模块（W2 接入）

**Files：**
- Modify：
  - `core/workspace_manager.py`：新增 `_load_v8_modules`，以及 `WorkspaceProject.add_module_from_package`；
  - `core/hardware/ecu_resource_resolver.py`：把包的 `resource_dir` 纳入扫描；
  - `ui/controllers/project_controller.py:836-871`：在 “Add Module” 中，如果所选文件位于某个包内，就改走包接口。
- Test：`tests/core/test_v8_load.py`

**Interfaces：**
- Consumes：Task 2 的 `module_entries`、`module_libraries`；Task 5 的 `scan_library`、`find_package`、`ModulePackage`。
- Produces：
  - `WorkspaceProject.packages: Dict[str, ModulePackage]`，按模块名索引；
  - `WorkspaceProject.add_module_from_package(pkg: ModulePackage, lib_index: int) -> ConfigurationManager`：解析 `definition_file(selected_chip)`，调用现有的 `add_module`，登记 `module_entries` 和 `packages`。本任务**不应用** pre/rec（留给 Task 10）。
  - `package_for_path(project, file: Path) -> Optional[Tuple[int, ModulePackage]]`：判断文件是否位于已登记库的某个包中。

- [ ] **Step 1：** 写失败测试：
  - `test_v8_loads_definition_from_package`：一个 v8 工程以 `eb-plugins` 库引用 `test_import_project/Def/plugins`，模块为 Mcu；加载后 `module_managers["Mcu"].module_def.ar_path == "/THA6_AS440_FuSa/Mcu"`，配置从 `config/Mcu.arxml` 读入；
  - `test_v8_missing_package_reports_failure`：`definition` 在所有库中都找不到时，`load_project` 返回的 `failed_modules` 中含 Mcu 和找不到的原因，不抛异常；
  - `test_v8_resources_from_package`：包的 `resource/*.properties` 中的值出现在 `project.ecu_resources` 中。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_v8_load.py tests/core/test_ecu_resource_resolver.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(project): load and add modules from module packages`。

### Task 7：值展平与基线合成（W4）

**Files：**
- Create：`autosar_configurator/core/baseline/__init__.py`、`values.py`、`compose.py`
- Test：`tests/core/baseline/test_values.py`、`tests/core/baseline/test_compose.py`

**Interfaces：**
- Produces：
  - `values.py`：
    - `ValueKey = str`，三种形式：
      - `"C:<容器路径>"`：表示容器存在；
      - `"P:<容器路径>.<参数名>"`：参数值；
      - `"R:<容器路径>.<引用名>"`：引用值。

      容器路径用 `EcucContainerValue.get_path()`，路径前缀统一用模块名。多值参数和多值引用的值是 `tuple`（Review Focus 2）。
    - `flatten(config: EcucModuleConfiguration) -> Dict[ValueKey, Any]`：结果按键排序。
    - `values_equal(a, b) -> bool`：复用 `workspace_manager._same_value` 的比较语义。
  - `compose.py`：
    - `class Layer(Enum)`：`DEFAULT=0, REC=1, DERIVED=2, PRE=3`。
    - `compose_base(module_def, module_name: str, layers: Dict[Layer, List[EcucModuleConfiguration]]) -> Tuple[EcucModuleConfiguration, Dict[ValueKey, Layer]]`。规则：
      - 按层从低到高叠加；
      - 对出现在结果中的每个容器，用 `module_def` 中该容器定义参数的静态 `default_value` 补齐缺失的参数，这些参数标为 DEFAULT 层；
      - 第二个返回值记录每个键来自哪一层。
      - `layers` 中可以有 DERIVED，并按 DERIVED 处理。

- [ ] **Step 1：** 写失败测试：
  - `test_flatten_keys_sorted_and_multi_as_tuple`；
  - `test_pre_overrides_rec`：同一参数 Rec 为 1、Pre 为 2，结果为 2，层为 PRE；
  - `test_derived_between_rec_and_pre`：Rec 为 1、Derived 为 3，结果为 3（DERIVED）；再加 Pre 为 2，结果为 2（PRE）；
  - `test_defaults_fill_only_base_containers`：Rec 中的容器缺少带 `default_value` 的参数时，结果中补上默认值，层为 DEFAULT；`default_expr` 不计算。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/baseline -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(baseline): flatten values and compose layered base`。

### Task 8：三方合并（纯函数）（W4）

**Files：**
- Create：`autosar_configurator/core/baseline/merge.py`
- Test：`tests/core/baseline/test_merge.py`（表格驱动，覆盖设计方案 §6.5 的合并情形表）

**Interfaces：**
- Consumes：Task 7 的 `flatten`、`values_equal`、`Layer`。
- Produces：
  - `class MergeKind(Enum)`：`ADOPT, KEPT_USER, PRE_FORCED, CREATE, REMOVED_IN_BASE`。
  - `@dataclass MergeItem(key: ValueKey, kind: MergeKind, base_value, new_value, active_value)`。
  - `@dataclass MergeResult(items: List[MergeItem])`，属性 `has_changes`（是否有 ADOPT、PRE_FORCED 或 CREATE 条目），方法 `to_markdown(module: str) -> str`。
  - `three_way_merge(base: Optional[Dict], new_base: Dict, active: Dict, new_layers: Dict[ValueKey, Layer], unlocked: Set[ValueKey]) -> MergeResult`：
    - `base` 为 None 表示首次启用或迁移，此时所有非 Pre 的差异都算 KEPT_USER；
    - `unlocked` 中的 Pre 键按普通键处理。
  - `apply_merge(active_config: EcucModuleConfiguration, module_def, new_base_config: EcucModuleConfiguration, result: MergeResult) -> None`：只执行 ADOPT、PRE_FORCED、CREATE，CREATE 从 `new_base_config` 复制容器子树；**不执行任何删除**。

- [ ] **Step 1：** 写失败测试，每种情形一个测试：
  - `test_unchanged_base_no_items`；
  - `test_adopt_when_user_untouched`；
  - `test_keep_user_when_user_changed`；
  - `test_pre_forced_over_user`；
  - `test_unlocked_pre_kept_user`；
  - `test_create_new_pre_container`；
  - `test_merge_never_deletes_renamed_or_removed`（Review Focus 1）：Base 中有容器 X，Base' 中没有，Active 中把 X 改名为 Y；结果中有 `REMOVED_IN_BASE`，`apply_merge` 之后 Y 和它的值都还在；
  - `test_merge_multi_values_compared_as_list`（Review Focus 2）：Pre 中的多值参数为 (1,2)，Active 中为 (2,1)，结果是一条 PRE_FORCED，应用后为 (1,2)；
  - `test_first_enable_all_user_except_pre`：`base=None`，Rec 的值与 Active 不同，结果为 KEPT_USER，不改值。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/baseline/test_merge.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(baseline): three-way merge of base, new base and active values`。

### Task 9：基线快照存取与值来源判定（W4）

**Files：**
- Create：`autosar_configurator/core/baseline/store.py`、`origin.py`
- Test：`tests/core/baseline/test_store_origin.py`

**Interfaces：**
- Produces：
  - `write_base(path: Path, config: EcucModuleConfiguration) -> str`：用 `EcucValueSerializer` 写 arxml，返回文件的 sha256，格式为 `"sha256:<hex>"`。
  - `read_base(path: Path, expected_hash: Optional[str]) -> Optional[EcucModuleConfiguration]`：文件不存在、哈希不符或解析失败时返回 None，并记录 warning 日志。
  - `class Origin(Enum)`：`DEFAULT, REC, DERIVED, PRE, USER`。
  - `classify(key, active: Dict, base: Optional[Dict], base_layers: Dict[ValueKey, Layer], unlocked: Set) -> Origin`：
    - 键属于 Pre 且不在 `unlocked` 中：PRE；
    - Active 的值等于 Base 的值：取该键的层；
    - 其余情况：USER。
  - `origins_for(config, base_config, base_layers, unlocked) -> Dict[ValueKey, Origin]`。

- [ ] **Step 1：** 写失败测试：
  - `test_write_read_roundtrip_hash`；
  - `test_base_missing_or_tampered_treated_as_migration`（Review Focus 4）：快照被删除，或文件中改了一个字节，`read_base` 都返回 None；再把 None 交给 `three_way_merge`，非 Pre 的差异全部是 KEPT_USER；
  - `test_classify_rec_vs_user`：值等于 Base 中来自 Rec 的值时为 REC，修改后为 USER；
  - `test_classify_pre_unlocked_is_not_pre`。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/baseline -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(baseline): base snapshot store and value origin classification`。

### Task 10：加载、保存、添加模块时接入基线层（W4）

**Files：**
- Modify：
  - `core/workspace_manager.py`：
    - `load_project(path, confirm=None)`；
    - `_load_v8_modules` 在加载完 Active 之后执行合并；
    - `save_project` 写入快照和 `base_hash`；
    - `add_module_from_package` 中，Active 初值 = Base（D8：默认用 Rec）。
  - `ui/controllers/project_controller.py`：打开工程和添加模块时传入一个 `confirm` 回调。回调用对话框展示 `MergeResult.to_markdown`，有确认和拒绝两个按钮。
- Create：`autosar_configurator/core/baseline/session.py`
- Test：`tests/core/test_v8_baseline_flow.py`

**Interfaces：**
- Consumes：Task 5 的 `load_pre`、`load_rec`；Tasks 7–9 的全部接口。
- Produces：
  - `ModuleBaseline`（定义在 `session.py`），字段：`base_config, layers: Dict[ValueKey, Layer], pre_keys: Set[ValueKey]`。
  - `compute_new_base(pkg: ModulePackage, chip, module_def, module_name, derived: List[EcucModuleConfiguration] = []) -> ModuleBaseline`。
  - `reconcile(manager: ConfigurationManager, old_base: Optional[EcucModuleConfiguration], new: ModuleBaseline, unlocked: Set[str], confirm: Callable[[str, MergeResult], bool]) -> Tuple[MergeResult, bool]`：返回结果和是否已应用。`has_changes` 为 False 时不调用 `confirm`。
  - `WorkspaceProject.baselines: Dict[str, ModuleBaseline]`：本次会话中已接受的基线，供 Task 11 判定来源和锁定使用。
  - 报告写到 `<history>/reports/<YYYYmmdd-HHMMSS>_merge_<Module>.md`，`.dpa` 中的相对路径用 POSIX 风格。
  - `confirm` 为 None 时（命令行或测试场景），默认**拒绝**，不改值，并在返回值中保留结果。

- [ ] **Step 1：** 写失败测试，使用 `tmp_path` 中手写的模块包（`module.json` + 一个 xdm/arxml 定义 + 一个同时含 Pre 和 Rec 的值文件）：
  - `test_add_module_initialises_from_rec_and_pre`：添加模块后，Active 含 Rec 和 Pre 的值，并写出了快照；
  - `test_reopen_without_package_change_no_confirm`：重新打开时 `confirm` 没有被调用；
  - `test_rec_change_follows_untouched_keeps_user`（对应设计方案 §12 验收 4）：修改包中的两个 Rec 值和一个 Pre 值，其中一个 Rec 值事先被用户改过；`confirm` 返回 True 后，未改过的 Rec 值跟随变化，改过的保留，Pre 值被强制，报告文件已生成；
  - `test_reject_keeps_active_and_base`：`confirm` 返回 False 时，Active 和快照都不变；下次打开再次调用 `confirm`；
  - `test_v7_project_never_reconciles`：v7 工程打开时 `confirm` 不被调用，配置不变。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_v8_baseline_flow.py tests/core/test_workspace.py tests/core/test_persistence.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(baseline): reconcile package baselines on load, add and save`。

### Task 11：Pre 只读锁定与界面显示（W4）

**Files：**
- Modify：
  - `core/config_manager.py`：新增 `check_editable`；在 `set_parameter_value`、`delete_container_instance`、`apply_recommended_values` 中调用它；
  - `ui/commands.py`：在 `SetReferenceCommand`、`RenameContainerCommand`、`MoveContainerCommand`、`PasteContainerCommand` 的构造函数中调用它；
  - `ui/controllers/edit_controller.py`：捕获 `PreLockedError`，在状态栏提示，不压入撤销栈；
  - `ui/widgets/davinci_config_panel.py`：Pre 值灰显，提示文字写明来源和 pre 文件；右键菜单增加“解除锁定/恢复锁定”，改动写入 `module_entries[m].pre_unlocked`；
  - `ui/widgets/batch_edit_dialog.py`：跳过锁定的值，并列出被跳过的项。
- Test：`tests/core/test_pre_lock.py`

**Interfaces：**
- Consumes：Task 10 的 `WorkspaceProject.baselines`；Task 9 的 `origins_for`。
- Produces：
  - `class PreLockedError(ValueError)`，定义在 `core/config_manager.py`，带属性 `key: str`。
  - `ConfigurationManager.check_editable(instance: EcucContainerValue, name: Optional[str] = None) -> None`：
    - `name` 为 None 时检查的是容器本身（删除、改名、移动）；
    - 键属于 `pre_keys` 且不在 `pre_unlocked` 中时抛 `PreLockedError`；
    - 没有 `project_context`，或模块没有基线时，直接通过。
  - `ConfigurationManager.value_origin(instance, name) -> Optional[Origin]`：供面板显示来源。

- [ ] **Step 1：** 写失败测试：
  - `test_lock_blocks_all_mutation_entries`（Review Focus 5）：对一个 Pre 参数，`set_parameter_value` 抛 `PreLockedError`；对 Pre 创建的容器，`delete_container_instance` 抛错；`apply_recommended_values` 不改动 Pre 键；`ui.commands` 中改名、改引用、粘贴的构造函数都抛错（用 `pytest.importorskip("PySide6")`，没有显示环境时跳过）；
  - `test_unlock_allows_edit_and_persists`：解锁后可以修改，保存再打开后仍是解锁状态，合并时该值为 KEPT_USER；
  - `test_import_value_file_then_pre_restored`：用值文件覆盖 Pre 参数后保存，重新打开时出现 PRE_FORCED 条目。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_pre_lock.py tests/core/test_command.py -v`，期望 PASS。再运行 `python -m pytest tests/ui -q`，需要本地有显示环境。
- [ ] **Step 5：** 手工检查：
  - 打开 Task 14 Step 1 中做好的 EB 新工程，Mcu 下 `McuResetReasonConf` 中的参数显示为灰色，提示为“来源：PRE（McuPreConfiguration.xdm）”；
  - 解锁后可以编辑。
- [ ] **Step 6：** 提交：`feat(baseline): lock preconfigured values and show value origin`。

### Task 12：模板查找改为“覆盖层 → 包”（W6）

**Files：**
- Modify：
  - `generator/generator.py:51-62,300-434`：新增参数 `package_template_dir`；
  - `core/project_paths.py`：新增 `template_sources(project, module) -> Tuple[Optional[Path], Optional[Path]]`；
  - `ui/controllers/generation_controller.py`、`ui/widgets/davinci_tree_view.py:133`、`ui/dialogs/project_properties_dialog.py:296`、`core/hardware/ecu_resource_diagnostics.py:94`：改为调用 `template_sources`；
  - `core/workspace_manager.py:938-939`：format 8 不再调用 `_copy_eb_templates`。
- Test：`tests/generator/test_template_sources.py`

**Interfaces：**
- Consumes：Task 6 的 `WorkspaceProject.packages`。
- Produces：
  - `CodeGenerator.__init__(..., package_template_dir: Optional[Path] = None)`：这个目录本身就是模块模板目录，**不再**在它下面找 `<Module>/` 子目录。扫描顺序为 `project_template_dir/<Module>`（覆盖层）→ `package_template_dir` → `user_template_dir/<Module>`，同一相对路径和类型先找到的生效。
  - `template_sources(project, module)`：返回 `(覆盖层根目录, 包模板目录)`。legacy 工程返回 `(<root>/templates, None)`，与现在的行为相同。

- [ ] **Step 1：** 写失败测试：
  - `test_overlay_wins_over_package`：覆盖层和包中有同名模板时，生成结果用覆盖层的内容；
  - `test_package_used_when_no_overlay`；
  - `test_fingerprint_independent_of_template_location`：同一份模板内容，放在覆盖层和放在包里，`_calculate_fingerprint` 的结果相同；
  - `test_v8_save_does_not_copy_templates`（对应验收 6）：在覆盖层中修改模板后保存，文件内容不变，`templates/` 中也没有出现插件模板的副本。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述接口。
- [ ] **Step 4：** 运行 `python -m pytest tests/generator -q`，期望没有新增失败。如果仓库中有 `verify_fingerprints.py`，再运行它，期望没有指纹变化。
- [ ] **Step 5：** 提交：`feat(generator): template lookup overlay then package; stop copying templates`。

### Task 13：EB 工程导入生成 format 8 工程（W9）

**Files：**
- Modify：
  - `core/workspace_manager.py:1246-1560`（`import_eb_project`）；
  - `ui/controllers/project_controller.py`（导入对话框传入 `confirm`）；
  - `tests/core/test_eb_import_modes.py`（期望值改为 v8 布局）。
- Test：`tests/core/test_eb_import_v8.py`

**Interfaces：**
- Consumes：Task 2 的 `create_project(format_version=8)`；Tasks 5、6、10 的全部接口。
- Produces：`import_eb_project(project_root, chip_name=None, target_dir=None, progress_callback=None, mode="copy", confirm=None) -> tuple`，返回值不变。行为如下：
  - `link` 模式：插件目录作为 `eb-plugins` 库登记，存为绝对路径或相对路径，**不创建符号链接**；
  - `copy` 模式：把插件复制到 `modules/<插件目录名>/`，并登记一个 `eb-plugins` 类型的库，指向 `modules`；
  - EPC 值写到 `config/<M>.arxml`；
  - 不复制模板；
  - `McuPreConfiguration` 不再被跳过：模块按 Task 10 的流程建立基线，因为已有 EPC 值，按“迁移”处理（`base=None`）；
  - 原来跳过 `PreConfiguration`/`_Pre` 的文件名规则（`workspace_manager.py:1318`、`:1514`）删除，改由清单推断决定。

- [ ] **Step 1：** 写失败测试：
  - `test_import_link_no_symlink`：导入后工程目录中没有任何符号链接，`module_libraries[0].kind == "eb-plugins"`；
  - `test_import_copy_into_modules`：导入后存在 `modules/Mcu_THA6_AS440/plugin.xml`，`.dpa` 的 `format_version == 8`；
  - `test_import_mcu_preconfiguration_applied`（对应验收 1）：以 `test_import_project` 作为来源，`confirm` 返回 True；导入后 Mcu 中有 `McuPublishedInformation/McuResetReasonConf` 的 Pre 容器，`value_origin` 为 PRE；`autosar/` 中的 arxml 没有被加载；
  - `test_old_v7_imported_project_still_opens`：用旧代码导入的 v7 工程（夹具中直接写好 v7 的 `.dpa` 和 `Def/plugins` 目录）照常打开。
- [ ] **Step 2：** 运行测试，期望 FAIL。
- [ ] **Step 3：** 实现上述行为，并更新 `test_eb_import_modes.py` 中依赖 `Def/plugins` 和符号链接的断言。
- [ ] **Step 4：** 运行 `python -m pytest tests/core/test_eb_import_v8.py tests/core/test_eb_import_modes.py -v`，期望 PASS。
- [ ] **Step 5：** 提交：`feat(import): EB import creates format-8 projects with plugin libraries`。

### Task 14：回归与验收

**Files：**
- Create：`tools/compare_generation.py`。用法：`python tools/compare_generation.py <dpa> <输出目录A> <输出目录B>`，生成两次并逐文件比较，忽略文件头中的时间戳行。

- [ ] **Step 1：** 在改造前的提交（Task 1 之前的 `main`）上，用工具对 `test_project_relocation/test.davinci` 所在工程，以及用户的 T1/T2 工程（路径请用户提供）分别生成一次，保存为基准。
- [ ] **Step 2：** 在本分支上再生成一次，并逐文件比较。期望输出：`0 differences`（对应设计方案 §12 验收 5）。
- [ ] **Step 3：** 运行 `python -m pytest tests/ -q`。期望：除已知的无关失败外，全部通过；在 PR 说明中列出已知失败的数量和名字。
- [ ] **Step 4：** 用 Grep 检查设计方案 §12 验收 7：`"ConfigValue"`、`"generateCode"`、`"Def"` 只在 `project_paths.py` 的 `legacy()` 中出现。
- [ ] **Step 5：** 运行 `openspec validate add-integration-module-packages --strict`，然后勾选 `tasks.md` 中的各项。
- [ ] **Step 6：** 提交：`test: phase-1 regression and acceptance for module packages`。
