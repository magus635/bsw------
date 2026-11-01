## 1. 核心（`core/hardware/chip_repair.py`）

- [x] 1.1 `KeyChange.to_fill_in`；`missing_key_changes` 设为 `True`
- [x] 1.2 `TO_FILL_IN` 常量与 `mark_to_fill_in`、`drop_filled_marks`、`to_fill_in_keys`（返回新芯片，不改输入）
- [x] 1.3 `RepairSession.build` 按 design D3 的顺序调用；`default_selection` 排除 `to_fill_in` 项；`added_to_fill_in` 给出本次新增的待填写项
- [x] 1.4 历史 `confirmed`：自动去掉的 `待填写` 标记，说明为"已填写"（条目被删除时为"条目已删除"）
- [x] 1.5 `tests/core/test_chip_repair.py`：加标记/不覆盖已有标记；厂商空值不加标记；`.properties` 有值时不加标记；填值或删除后去掉标记；其他说明的标记保留；默认选择排除待填写；历史记录 marked/confirmed；命令行 `--all-added` 也会加标记

## 2. 工程告警（`core/workspace_manager.py`）

- [x] 2.1 `chip_data_findings` 对所用芯片的 `to_fill_in_keys` 逐个告警
- [x] 2.2 测试：工程副本和芯片库两种来源都会告警，告警进入 `diagnose_ecu_resources` 的报告；没有标记的厂商空值不告警

## 3. 修复向导（`ui/wizards/chip_repair_wizard.py`）

- [x] 3.1 第 3 步副标题说明"待填写需要手动勾选"
- [x] 3.2 保存页摘要显示本次新增的待填写数量；保存前询问，选"否"时不写入，停在保存页
- [x] 3.3 `tests/ui/test_chip_repair_wizard.py`：待填写项不默认勾选；勾选后第 5 步列为"新出现"；保存先询问（拒绝不写入/同意后保存）；保存后芯片带标记、`check_chip` 报告它（现有断言没有涉及扫描，无需改动）

## 4. 芯片定义设计器

- [x] 4.1 `EcuResourceEditor.add_placeholders` 记下加入的键，`set_resources` 时清空，`added_placeholders()` 读取
- [x] 4.2 `_build_current_chip` 调用 `mark_to_fill_in`（上述键）和 `drop_filled_marks`
- [x] 4.3 `tests/ui/test_chip_designer_history.py`：加入待填写后保存会加标记；填值再保存会去掉标记，历史记为已确认；载入的空值不加标记；载入后没有改动时保存仍然什么都不写（现有测试）

## 5. 验证

- [x] 5.1 `QT_QPA_PLATFORM=offscreen python3 -m pytest tests/ -q`：1150 passed，91 skipped
- [x] 5.2 在芯片库副本（SC300）上重跑探测：扫描键默认不勾选；手动勾选保存后出现 `ecu_resources.Os.ProbeMissingKey: 待填写`，`check_chip` 报告它；用 `.properties` 填值保存后标记消失，历史记为"已填写"
- [x] 5.3 芯片库 4 颗芯片没有待填写项，加标记/去标记不改变它们的标记，`check_chip` 结果不变
- [x] 5.4 `openspec validate mark-chip-entries-to-fill-in --strict`
