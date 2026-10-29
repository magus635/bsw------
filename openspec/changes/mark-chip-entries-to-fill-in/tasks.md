## 1. 核心（`core/hardware/chip_repair.py`）

- [ ] 1.1 `KeyChange.to_fill_in`；`missing_key_changes` 设为 `True`
- [ ] 1.2 `TO_FILL_IN` 常量与 `mark_to_fill_in`、`drop_filled_marks`、`to_fill_in_keys`（返回新芯片，不改输入）
- [ ] 1.3 `RepairSession.build` 按 design D3 的顺序调用；`default_selection` 排除 `to_fill_in` 项
- [ ] 1.4 历史 `confirmed`：自动去掉的 `待填写` 标记，说明默认为"已填写"
- [ ] 1.5 `tests/core/test_chip_repair.py`：加标记/不覆盖已有标记；厂商空值不加标记；`.properties` 有值时不加标记；填值或删除后去掉标记；其他说明的标记保留；默认选择排除待填写；历史记录 marked/confirmed

## 2. 工程告警（`core/workspace_manager.py`）

- [ ] 2.1 `chip_data_findings` 对所用芯片的 `to_fill_in_keys` 逐个告警
- [ ] 2.2 测试：工程副本和芯片库两种来源都会告警；没有标记的厂商空值不告警

## 3. 修复向导（`ui/wizards/chip_repair_wizard.py`）

- [ ] 3.1 第 3 步副标题说明"待填写需要手动勾选"
- [ ] 3.2 保存页摘要显示本次新增的待填写数量；保存前询问，选"否"时不写入，停在保存页
- [ ] 3.3 `tests/ui/test_chip_repair_wizard.py`：更新默认勾选断言；待填写项不默认勾选；勾选后保存先询问（取消/确认）；保存后芯片显示"（资料不完整）"

## 4. 芯片定义设计器

- [ ] 4.1 `EcuResourceEditor.add_placeholders` 记下加入的键，`set_resources` 时清空，并提供读取接口
- [ ] 4.2 `_build_current_chip` 调用 `mark_to_fill_in`（上述键）和 `drop_filled_marks`
- [ ] 4.3 `tests/ui/test_chip_designer_history.py`（或 `test_chip_designer_ecu_resources.py`）：加入待填写后保存会加标记；填值再保存会去掉标记，历史记为已确认；载入后没有改动时保存仍然什么都不写

## 5. 验证

- [ ] 5.1 `QT_QPA_PLATFORM=offscreen python3 -m pytest tests/ -q` 全部通过
- [ ] 5.2 在芯片库副本上重跑之前的探测脚本：扫描键默认不勾选；手动勾选保存后出现 `ecu_resources.Os.ProbeMissingKey: 待填写`，`check_chip` 报告它；填值保存后标记消失
- [ ] 5.3 芯片库 4 颗芯片的 `check_chip` 结果与变更前一致（厂商空值不受影响）
- [ ] 5.4 `openspec validate mark-chip-entries-to-fill-in --strict`
