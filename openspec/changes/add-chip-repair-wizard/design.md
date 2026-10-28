## Context

核心层 `core/hardware/chip_repair.py`（`add-chip-repair-core`）提供：

- 读取来源：`ecu_resources_from_properties`、`diff_from_source`、`missing_key_changes`（键来自 `collect_referenced_keys(project)` 或 `collect_referenced_keys_in_dirs(dirs)`）；
- 合并与视图：`apply_changes`、`derive_views`；
- 待确认标记：`confirm_fields`、`mark_unconfirmed`；
- 保存：`save_repaired_chip`（包括 `RepairRecord`、`ChipFileChanged`、`next_version`、`git_author`、`history_path`）。

完整性检查 `check_chip(chip, project, entries)` 和 `plugin_entries(project)` 已经在项目属性里使用。

## Goals / Non-Goals

- Goals：
  - 不碰命令行也能完成一次完整修复；
  - 能从"资料不完整"直接进入修复；
  - 向导的逻辑可以不经过界面测试。
- Non-Goals：见 proposal 的"不在本变更范围内"。

## Decisions

- **`RepairSession` 放在核心层**，是一个普通类，不依赖 Qt。
  - 字段：`database`、`base`（深拷贝）、`project`（可为空）、`sources`（文件列表、是否扫描项目、插件目录列表）、`diff`、`selected`、`confirm_notes`、`new_marks`。
  - 方法：
    - `load_sources()`：合并 `.properties` 差异与缺失键差异，同一个键以 `.properties` 为准；
    - `default_selection()`：新增与变化；
    - `build()`：依次 `apply_changes` → `derive_views` → `confirm_fields` → `mark_unconfirmed`，返回 `(chip, views)`；
    - `completeness(chip)` / `completeness_change(chip)`：后者返回已解决、仍存在、新出现三组；
    - `save(record)`。
  - 命令行里合并来源的逻辑（目前写在 `tools/chip_repair.py` 的 `_difference`）改为调用 `RepairSession.load_sources()`，两边结果一致。
  - 备选方案是把状态放在向导的页面对象里，但这样逻辑只能通过界面测试，所以不采用。
- **向导基于 `QWizard`，不继承 `ConfigWizard`。** `ConfigWizard.accept()` 会收集各页的 `get_data()` 并发出 `wizard_completed`，而修复向导的结果是"保存成功的芯片名"。为了让保存失败时能停留在本页，保存放在最后一页的 `validatePage()` 里执行。
- **差异页用 `QTreeWidget`**：模块是父节点（三态勾选），键是子节点。
  - 列：键、类型、旧值、新值；值超过 80 个字符时截断，完整值放在提示里。
  - THA6412 的 Port 模块有一千多个键，一次性建树没有问题；不做懒加载。实施时实测，超过 1 秒再处理。
- **完整性对比**：用 `check_chip` 的 `CompletenessItem.field` 作为标识，比较修复前后，分为已解决、仍存在、新出现三组。打开了项目时连同项目一起检查，并传入 `plugin_entries(project)`。
- **入口与状态同步**：
  - 主窗口：`_launch_chip_repair_wizard(chip_name=None)`；成功后调用与设计器保存相同的 `_on_designer_chip_saved`（刷新约束、显示状态栏消息）。
  - 如果 `project.chip_store` 里有这颗芯片的副本，并且 `chip_update_differences()` 不为空，就提示用"项目属性 > 从芯片库更新"同步，不自动更新。
  - 设计器：载入或保存时记下 `_build_current_chip()` 的校验和；当前校验和与它不同，就说明有未保存的修改。不直接和 `_base_chip` 比较，因为表单会补上默认字段，未改动的芯片也可能与 `_base_chip` 不同。修复成功后调用 `_load_chip_by_name` 重新载入。
  - 项目属性："修复…"按钮在当前选中的芯片资料不完整时显示；修复成功后刷新芯片列表和完整性提示。
- **修改人**：预填 `git_author(芯片目录)`，用户可以修改。修改人为空时不允许完成。

## Risks / Trade-offs

- 向导打开后，芯片文件可能被设计器或其他人改动。保存时 `ChipFileChanged` 会拦住，提示用户重新打开向导，不提供强制覆盖。
- 项目副本不在修复范围内：项目要通过"从芯片库更新"才能拿到修复后的数据。这是有意的，芯片数据只在芯片库里修改。

## Implementation Notes

- **保存页的校验必须幂等**：`QWizard.accept()` 会再校验一次当前页。如果保存页已经校验并保存过，再调用 `accept()` 就会保存第二次，而第二次会把第一次的写入当成"文件已被改动"。现在 `SavePage.validatePage()` 在已有保存结果时直接返回成功。这个问题是在真实界面走查时发现的。
- **视图状态在界面上显示中文**（未变、已更新、未推导）；修改记录里仍写英文常量，保持与命令行一致。
- **`project_copy_notice()`** 由主窗口和项目属性共用：只比较项目副本与芯片库芯片的校验和，不比较 ECU 资源的差异，因为只处理待确认标记的修复不会改动 ECU 资源。
