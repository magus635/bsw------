## Why

芯片修复向导现在有三个入口：主窗口菜单、设计器、工程属性。用户最常碰到芯片资料不全的地方是**选芯片**的时候：新建工程向导的芯片页、硬件映射向导的芯片页。在那里发现芯片有问题，只能退出向导，另找入口修复，再回来重选。

## What Changes

- 新建工程向导的芯片页加"修复所选…"按钮：选中芯片库里的芯片时可用，修复后刷新列表并保持选中。
- 硬件映射向导的芯片页加"Repair..."按钮：当前芯片在芯片库里时可用；修复后刷新芯片下拉框并保持选中；工程里有这颗芯片的副本且与库不同时，提示用"Update from Library"。
- 向导内的入口和其他入口一样，打开同一个修复向导。

## Impact

- Affected specs：`chip-repair`（修改 `Repair Entry Points`）
- Affected code：`ui/wizards/new_project_wizard.py`、`ui/wizards/hardware_mapping_wizard.py`；测试加在 `tests/ui/test_chip_repair_wizard.py`
- 兼容性：只多两个按钮，不改变原有流程。
- **不在本变更范围内**：按钮的显隐按"资料是否完整"控制（工程属性里是这样做的）；这里始终可用，因为修复也用于补充资料。
