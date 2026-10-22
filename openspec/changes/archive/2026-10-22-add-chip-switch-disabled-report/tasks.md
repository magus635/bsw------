## 1. Core
- [x] 1.1 `chip_selectors.preview_chip_change(project, chip_name)`：按芯片名取定义；沙盒项目（浅拷贝项目和管理器、深拷贝配置、共享定义）；在沙盒上 `apply_selectors()`；`EcuResourceResolver.resolve(沙盒)`；返回 `ChipChangePreview(chip, selector_result, modules, ecu_resources)`
- [x] 1.2 `enable_conditions.disabled_containers(modules, ecu_resources)`：返回被 ENABLE 条件禁用的最上层容器 `DisabledContainer(module, path, definition)`，复用 `disabled_configuration_objects()` 的求值；按模块、路径排序
- [x] 1.3 单元测试（`tests/core/test_chip_change_preview.py`）：预览后项目不变（配置值、新建容器、`selected_chip`、ECU 资源、`chips/`）；预览的选择器变化与确认后实际写入一致
- [x] 1.4 单元测试（同一文件）：列表级 ENABLE 读选择器参数、读 ECU 资源、只报最上层、切回恢复、两颗芯片下都禁用的不报

## 2. UI
- [x] 2.1 `ProjectController.preview_chip_change(chip)`：组合 core 预览与两次 `disabled_containers()`，得到选择器变化、将失效、将恢复；求值失败记日志并标记“无法检查”
- [x] 2.2 `ChipChangePreviewDialog`：选择器变化表；将失效、将恢复按模块和定义分组计数，可展开查看路径；注明模板中按芯片分支的输出不在此列；“切换” / “取消”
- [x] 2.3 Project Properties 改芯片：先预览，确认后 `apply_project_chip(chip, True)`；取消则不改芯片，其他字段照常保存；求值期间显示等待光标；完整列表写 INFO 日志
- [x] 2.4 “Apply Chip Selectors”：先预览，确认后 `apply_chip_selectors()`
- [x] 2.5 UI 测试（`tests/ui/test_unified_chip_selection.py`）：确认后生效、取消后不变、切回时列出恢复、切换前已禁用的不列出、无变化仍需确认、求值异常仍可确认

## 3. Verification
- [x] 3.1 `python -m pytest tests/core/test_chip_change_preview.py tests/ui/test_unified_chip_selection.py tests/core/test_parser_serializer.py tests/core/test_command.py -q`
- [x] 3.2 `python -m pytest tests/ -q`（1017 passed, 4 skipped）
- [x] 3.3 T1 副本（`Desktop/prj/t1`）：THA6206 → THA6412 预览列出 MemorySection 118、OsMemoryMap 94、MemoryBlock 25、MemoryRegion 10、SystemModeStack 1；预览后项目内存状态（配置、芯片、ECU 资源）不变；确认切换后切回时预览列出全部恢复；预览与实际切换的选择器变化、失效容器一致；预览约 0.5 秒。生成器未改动，未重新对比生成结果

## 4. Follow-up (review of the T1 preview)
- [x] 4.1 Warn when a kind of container has no enabled instance left (`enable_conditions.container_paths` / `is_disabled`, `ProjectController._unavailable_kinds`); mark such groups “全部失效”
- [x] 4.2 Tooltip with the container definition's DESC (`clean_description`, `ProjectController._container_descriptions`)
- [x] 4.3 Tests: `tests/core/test_chip_change_preview.py` (unavailable vs partly disabled, descriptions), `tests/ui/test_unified_chip_selection.py` (warning, marker, tooltip); full suite 1021 passed, 4 skipped
- [x] 4.4 Reasons: `EnableResult.removed_conditions` / `DisabledContainer.condition` keep the false ENABLE condition; `ProjectController._changed_inputs` / `_reasons` match it with changed selectors and `ecu:*` keys; dialog shows a reason summary per condition and a reason line in each group
- [x] 4.5 Tests for reasons (selector, chip resource, not identified); full suite 1023 passed, 4 skipped
