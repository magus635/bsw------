## 1. 实现

- [x] 1.1 先确认调用方：读 `_create_single_value_editor` 的所有调用点（`davinci_config_panel.py` 的参数编辑和 `ListEditorWidget`），确认只调用返回的取值函数
- [x] 1.2 枚举分支：当前值非空且不在最终选项里时，加一项 `"<值>（不在可选范围）"`，item data 为原值，选中它，并设置 toolTip
- [x] 1.3 取值函数：当前项有 data 返回 data，否则返回 `currentText`

## 2. 测试

- [x] 2.1 `tests/ui/test_config_panel_enum_value.py`：厂商 `Port.xdm` 的 `PortPinMode`，存 `PORT_PIN_MODE_GPIO` 时显示带标记的原值、取值函数返回原值、toolTip 列出 `PORT_PIN_MODE_ALL`
- [x] 2.2 值合法或为空时，选项与改动前一致，没有带标记的项
- [x] 2.3 选项被芯片约束全部过滤掉时，当前值如实显示（无标记，因为没有可对照的选项）

## 3. 验证

- [x] 3.1 全量测试通过（`QT_QPA_PLATFORM=offscreen python -m pytest tests -q`）
- [x] 3.2 核对显示与校验一致：同一个值 `PORT_PIN_MODE_GPIO`，校验报"不在 allowed literals"，编辑器显示"PORT_PIN_MODE_GPIO（不在可选范围）"（离屏运行 `DaVinciConfigPanel`，未在真实显示的完整程序里点开）
