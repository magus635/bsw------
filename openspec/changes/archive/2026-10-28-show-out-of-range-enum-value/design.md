## Context

`_create_single_value_editor` 的枚举分支：建 `QComboBox`，可选参数在最前面加"(未配置)"，再加选项，最后 `setCurrentText(str(current_value))`。取值函数是 `combo.currentText`，改动信号是 `currentTextChanged`。值不在列表里时 `setCurrentText` 对不可编辑的下拉框没有效果。

## Decisions

- **用 item data 保存真实值**：新增的那一项文字是 `"<值>（不在可选范围）"`，item data 是原值。取值函数改为"当前项有 data 就返回 data，否则返回 `currentText`"。这样选中这一项（包括重新选回它）写回的是原值，不会把带标记的文字存进配置。其他项没有 data，行为不变。
- **只在有当前值、且不在选项里时才加**：值为空或在选项里时不动，现有测试和界面不受影响。比较用字符串（`str(current_value)`），与现有 `setCurrentText` 一致。
- **提示文字**：给下拉框设 toolTip，写"当前值不在可选范围内；可选：A, B"，让用户知道为什么。
- **不用红色样式**：深浅主题下要另外处理颜色，文字标记已经足够，保持简单。
- **不做自动迁移**：静默改用户数据，且无法判断旧值该对应哪个新值。

## Risks / Trade-offs

- 该函数被所有枚举参数使用。风险是现有取值函数被替换后，某处依赖 `combo.currentText` 作为函数对象。需确认调用方只调用返回的 getter，不直接比较它。
- 用户把不合法值改成合法值后，带标记的项仍留在列表里，可以再选回去。这是有意的：不删除，避免界面在编辑中途改变选项。

## Open Questions

无。
