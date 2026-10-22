## Why

切换芯片的预览已经能说明容器为什么失效（哪条 ENABLE 条件不成立、读到的哪个输入变了），但没有说明条件写在哪里。用户要核对或修改插件定义时，还得自己在 `Os.xdm`（T1 有 5000 多行）里搜索；而且同一条条件文字在 T1 的 `Os.xdm` 中出现了 5 次（第 3885、3989、4118、4168、5179 行），搜索也分不清是哪一处。

## What Changes

- 解析定义时记录每个 ENABLE 条件所在的行号：容器自身的条件、外层 `v:lst` 的条件、参数和引用的条件分别记录。
- 判断失效时，除了失败的条件，也记下它的行号；文件取模块的定义文件，显示为相对项目根目录的 POSIX 路径。
- 预览中每个分组的原因行加上“位置：<文件> 第 N 行”；顶部的原因汇总按条件列出所有位置。位置文字可以选中复制。
- 不加“打开文件”按钮（系统默认程序无法跳到指定行）。

## Impact

- Affected specs: `project-chip-selection`（修改 “Chip Change Preview Explains Why”）。
- Affected code:
  - `autosar_configurator/core/model/definition_model.py`：`enable_line` / `list_enable_line`
  - `autosar_configurator/core/parser/ecuc_def_parser.py`：记录行号
  - `autosar_configurator/generator/eb/enable_conditions.py`：`removed_condition_lines`、`DisabledContainer.condition_line`
  - `autosar_configurator/ui/controllers/project_controller.py`、`ui/dialogs/chip_change_preview_dialog.py`：显示位置
  - 测试：`tests/core/test_chip_change_preview.py`、`tests/ui/test_unified_chip_selection.py`
- 兼容性：只增加字段，生成结果、指纹与 EPC 导出不变。ARXML 定义（没有行号的来源）不显示位置。
