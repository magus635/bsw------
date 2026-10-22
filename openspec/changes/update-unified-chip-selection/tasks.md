## 1. Core
- [x] 1.1 `WorkspaceProject.apply_chip_selectors()`：按 `selectors` 写入容器参数与模块级参数，返回 `(key, old, new)` 变化列表与未写入原因；值不在定义枚举中时不写（`core/hardware/chip_selectors.py`）
- [x] 1.2 由选择器值反查芯片（芯片库与项目 `chips/` 中 `selectors` 唯一匹配），用于没有 `selected_chip` 的旧项目（`WorkspaceProject.chip_from_configuration()`）
- [x] 1.3 添加模块时，若项目已有芯片，对该模块调用 `apply_chip_selectors()`；缺少的单实例容器链（如 `ResourceGeneral`）按定义创建
- [x] 1.4 单元测试 `tests/core/test_chip_selection.py`：容器参数、模块级参数（Os）、模块未加载、无 `selectors`、值不在枚举、创建容器、多实例容器不创建、反查唯一/歧义、打开项目不改值

## 2. UI
- [x] 2.1 统一入口 `ProjectController.apply_project_chip(chip, write_selectors)`：`selected_chip` → `chip_changed()` → 选择器 → 约束服务 → 刷新
- [x] 2.2 新建项目向导、Project Properties、导入 EB、打开项目改为调用统一入口（导入/打开 `write_selectors=False`；不一致时导入摘要和状态栏提示）
- [x] 2.3 Project Properties 新增 “Apply Chip Selectors” 按钮与不一致提示
- [x] 2.4 配置面板中芯片声明的选择器参数只读并显示提示；移除 `davinci_main_window._on_parameter_changed` 中的 `ResourceSubderivative` 反向切换和 `_get_resource_subderivative`
- [x] 2.5 UI 测试 `tests/ui/test_unified_chip_selection.py`：统一入口写入/不写入、同芯片仍刷新、Apply Chip Selectors、选择器参数不可编辑

## 3. Verification
- [x] 3.1 `python -m pytest tests/core/test_chip_selection.py tests/core/test_chip_single_source.py tests/core/test_ecu_resource_diagnostics.py -q`
- [x] 3.2 `python -m pytest tests/ -q`（1006 passed, 4 skipped）
- [x] 3.3 导入验证：`test_import_project` 无 EPC 值；改用 EB 示例工程 `DemoWorkspace/CodeProject/DemoMcal` 三颗芯片导入：配置值不变、无不一致警告、反查芯片均正确
- [x] 3.4 生成器未改动；仓库无 `verify_fingerprints.py`，指纹不受影响
