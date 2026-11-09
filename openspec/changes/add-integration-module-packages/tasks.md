# Tasks

编号与实施计划 `docs/superpowers/plans/2026-11-09-integration-module-package-phase1-plan.md` 的 Task 1–14 一一对应。

## 1. 工程目录（W1）

- [ ] 1 工程目录解析 `ProjectDirectories`：新增 `core/project_paths.py`，把 `workspace_manager`、`generator`、`generation_controller`、`project_properties_dialog`、`davinci_tree_view`、`ecu_resource_*`、`chip_constraint_service` 中写死的目录名改为调用它；生成器新增 `project_root` 参数，删除往上找 `Def` 的推断（`tests/core/test_project_paths.py`）
- [ ] 2 `.dpa` format 8 的读写：`create_project`、`save_project`、`load_project`、`WorkspaceProject.__init__` 支持 `directories`、`module_libraries`、`modules`（按定义路径）；format ≤7 照旧并保存为 7（`tests/core/test_dpa_format8.py`）

## 2. 模块包（W2）

- [ ] 3 模块包清单与 EB 插件推断：新增 `core/packages/`（`manifest.py`、`eb_plugin.py`、`errors.py`）（`tests/core/packages/test_manifest.py`、`test_eb_plugin.py`）
- [ ] 4 值集合索引与包内按路径合并：新增 `core/packages/value_index.py`，`xdm_config_parser` 新增 `parse_all`（`tests/core/packages/test_value_index.py`）
- [ ] 5 `ModulePackage`、芯片条件与模块库：新增 `core/packages/package.py`，修改 `core/packages/library.py`（`tests/core/packages/test_package.py`、`test_library.py`）
- [ ] 6 format 8 工程按模块包加载和添加模块：`workspace_manager` 新增 `_load_v8_modules`、`add_module_from_package`；`ecu_resource_resolver` 扫描包资源目录；“Add Module” 对包内文件改走包接口（`tests/core/test_v8_load.py`）

## 3. 基线层（W4）

- [ ] 7 值展平与基线合成：新增 `core/baseline/`（`values.py`、`compose.py`），按 DEFAULT < REC < DERIVED < PRE 分层合成（`tests/core/baseline/test_values.py`、`test_compose.py`）
- [ ] 8 三方合并（纯函数）：新增 `core/baseline/merge.py`，表格驱动覆盖设计方案 §6.5 合并情形表（`tests/core/baseline/test_merge.py`）
- [ ] 9 基线快照存取与值来源判定：新增 `core/baseline/store.py`、`origin.py`（`tests/core/baseline/test_store_origin.py`）
- [ ] 10 加载、保存、添加模块时接入基线层：新增 `core/baseline/session.py`；`load_project(path, confirm=None)`、`save_project` 写快照和哈希、添加模块以 Base 为初值；界面传入预演确认回调（`tests/core/test_v8_baseline_flow.py`）
- [ ] 11 Pre 只读锁定与界面显示：`config_manager.check_editable` 与 `ui/commands.py` 命令层拦截；配置面板灰显、来源提示、解除/恢复锁定；批量编辑跳过锁定项（`tests/core/test_pre_lock.py`）

## 4. 模板查找（W6）

- [ ] 12 模板查找改为“覆盖层 → 包”：`project_paths.template_sources`，生成器新增 `package_template_dir`，format 8 不再调用 `_copy_eb_templates`（`tests/generator/test_template_sources.py`）

## 5. EB 工程导入（W9）

- [ ] 13 EB 工程导入生成 format 8 工程：插件目录登记为模块库，不复制模板、不创建符号链接，`PreConfiguration` 进入基线层（`tests/core/test_eb_import_v8.py`，更新 `tests/core/test_eb_import_modes.py`）

## 6. 回归与验收

- [ ] 14 回归与验收：新增 `tools/compare_generation.py`，旧工程改造前后生成结果 `0 differences`；全量 `pytest` 通过（已知无关失败除外）；Grep 确认写死目录名只在旧格式默认值表中；`openspec validate add-integration-module-packages --strict`
