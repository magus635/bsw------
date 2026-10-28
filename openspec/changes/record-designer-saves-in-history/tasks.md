## 1. 实现

- [x] 1.1 `_on_save_clicked`：已有芯片走 `save_repaired_chip`，来源"设计器手工编辑"
- [x] 1.2 `ChipFileChanged` 时询问是否覆盖；覆盖则直接保存，否则不写
- [x] 1.3 没有未保存改动时不写，状态栏提示
- [x] 1.4 保存后更新版本号、状态栏和提示信息

## 2. 测试

- [x] 2.1 `tests/ui/test_chip_designer_history.py`：备份、版本、历史；连续两次保存；无改动；新芯片；文件被外部改动（取消与覆盖）
- [x] 2.2 更新 `test_saving_an_edited_chip_keeps_its_ecu_resources` 的版本断言
- [x] 2.3 全量测试通过
