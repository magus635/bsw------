## Why

`add-chip-repair-core` 已经提供了修复已有芯片的核心函数和命令行，但界面上仍然没有入口。芯片负责人修复芯片时，只能用命令行，或者走设计器"克隆再改名"的绕路。项目属性和芯片依赖扫描能显示"资料不完整"，却不能直接去修。

## What Changes

- **新增"芯片修复向导"**（`ui/wizards/chip_repair_wizard.py`），共六页，全部调用 `chip_repair` 的核心函数：
  1. **选择芯片**：芯片库中的芯片。
     - 显示 `resource_version`、完整性问题（打开了项目时连同项目的模块一起检查）、最近一次修改记录。
     - 文件在设计器之外被改过时给出提示。
  2. **修复来源**（可组合，也可以都不选，只处理待确认标记）：
     - 一个或多个 `.properties` 文件；
     - 扫描当前项目模块所需的键；
     - 扫描插件目录所需的键。
  3. **差异与选择**：
     - 按模块分组的树，每个键一行：类型、旧值、新值，"仅类型不同"单独标出；
     - 可以按模块或逐键勾选，默认勾选新增和变化，删除不勾选；
     - 可以按类型筛选，显示勾选计数。
  4. **待确认标记**：逐条"保留 / 确认（填写确认说明）"，也可以新增标记。
  5. **视图与检查**：显示视图同步结果，并对比修复前后的完整性：已解决、仍存在、新出现。
  6. **保存**：
     - 填写来源（按所选文件预填）、说明、版本（预填下一个版本）、修改人（预填 `git config user.name`）；
     - 显示改动汇总；
     - 点"完成"后保存。文件已被改动时提示并停留在本页，不会关闭。
- **入口**：
  - 主窗口菜单"修复芯片…"：预选当前项目的芯片；
  - 芯片定义设计器的"修复此芯片…"：编辑已有芯片时可用；设计器有未保存的修改时先询问是否放弃；修复完成后重新载入该芯片；
  - 项目属性里的"资料不完整"提示旁边加"修复…"按钮，打开向导并预选该芯片。
- **修复之后**：
  - 发出"芯片库已更新"信号，主窗口刷新芯片约束；
  - 如果当前项目使用的是这颗芯片的项目副本，提示可以用"从芯片库更新"同步。
- **`RepairSession`**（核心层，不依赖 Qt）：保存向导各页之间的状态（修复前的芯片、差异、勾选的键、确认与新增的标记、合并后的芯片、视图结果）。界面只负责显示和收集选择，逻辑可以不经过界面测试。

## Impact

- Affected specs：`chip-repair`（新增需求）
- Affected code：
  - 新增 `autosar_configurator/ui/wizards/chip_repair_wizard.py`
  - `autosar_configurator/core/hardware/chip_repair.py`：新增 `RepairSession`
  - `autosar_configurator/ui/davinci_main_window.py`：新增菜单项
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`：新增"修复此芯片…"按钮
  - `autosar_configurator/ui/dialogs/project_properties_dialog.py`：新增"修复…"按钮
  - 测试：`tests/core/test_chip_repair.py`、新增 `tests/ui/test_chip_repair_wizard.py`
  - 文档：`doc/chip_ecu_resources.md`、`doc/芯片定义设计器使用说明.html`
- 兼容性：芯片 YAML 与修改记录的格式不变；设计器原有的保存流程不变。
- 不在本变更范围内：
  - 修复项目里的芯片副本：只修芯片库，项目再用"从芯片库更新"同步；
  - 新建项目向导、硬件映射向导里的入口；
  - 引脚复用表合并、兄弟芯片对比、修复对项目配置的影响预览；
  - 设计器保存时写修改记录。
