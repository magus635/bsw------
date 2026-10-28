## Why

芯片的修复历史（`data/chips/history/<名>.yaml`）只有修复向导和命令行会写。在芯片定义设计器里直接改一个已有芯片并保存，走的是 `ChipDefinitionExporter.save_yaml`：不备份、不升版本、不留记录，也不检查文件在加载之后有没有被别人改过（直接覆盖）。同一个芯片因此有两条保存路径，行为不一致，历史里缺了手工编辑。

## What Changes

- 设计器保存一个**已在芯片库里的芯片**（改的是它自己的文件）时，改走 `save_repaired_chip`：旧文件备份为 `.yaml.bak`，版本号加一，历史里追加一条（来源写"设计器手工编辑"），并检查文件自加载后是否被改动。
- 文件在加载后被别人改过时，设计器询问是否覆盖；选覆盖则退回原来的直接保存（没有备份和历史），选否则不写。
- 没有未保存的改动时，保存什么都不写，状态栏提示"没有改动"。
- 新芯片、另存为别的名字，不是修复，保持原样。
- 保存成功后更新界面里的版本号和提示信息。

## Impact

- Affected specs：`chip-repair`（修改 `Repair History`，新增设计器保存的场景）
- Affected code：`ui/dialogs/chip_definition_designer_dialog.py` 的 `_on_save_clicked`
- 兼容性：设计器每次保存已有芯片会把 `resource_version` 加一，并产生 `.yaml.bak` 和一条历史。此前保存不改版本，已有测试 `test_saving_an_edited_chip_keeps_its_ecu_resources` 中的版本断言相应更新。
- **不在本变更范围内**：设计器里编辑版本号；历史里记录设计器改了哪些字段（只有版本、校验和和待确认标记的变化，ECU 资源差异会如实写入）。
