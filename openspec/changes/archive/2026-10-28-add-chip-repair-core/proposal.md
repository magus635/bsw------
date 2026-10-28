## Why

芯片定义设计器只能新建芯片或克隆出新芯片，修复已有芯片缺少可靠的手段：

- 修复最常见的来源是新版 MCAL 的 `.properties`，现在只能整体导入，看不到哪些键新增、删除或改了值，也不能只取一部分。
- `ports`、`resources`、`metadata.cores` 与 `ecu_resources` 各存一份，修了 ECU 资源还要手工同步其余几份，容易漏。
- `metadata.unconfirmed`（待确认标记）在设计器里看不到也清不掉，数据核实后标记仍在。
- 保存直接整体重写 YAML：不留备份，不检查文件是否已在别处被改，不记录改了什么、依据是什么。
- 修复逻辑全在对话框里，脚本和测试都用不上。

已确定的原则：`ecu_resources` 是芯片数据的唯一权威，其余数据段由它推导；缺失或待确认的数据只标记、不删除；修复不改芯片名。

## What Changes

本变更只做核心层（`core/hardware/chip_repair.py`）和一个命令行工具，不改界面；修复向导放到后续变更。

- **ECU 资源差异**：按扁平键（`模块.键`）比较修复前后的 `ecu_resources`，分为新增、删除、值变化三类，按键排序，值相同（包括区间写法与列表写法相同）不算变化。
- **修复来源**：
  - 一个或多个 `.properties` 文件，解析结果只用于比较，不直接写入芯片；
  - 项目或插件目录里模块引用、芯片却没有的键，作为值为空的新增项。
- **选择性合并**：只应用调用方选中的改动；删除必须显式选中；未选中的键与芯片的其他数据不变；已有键保持原顺序，新增键追加在所在模块末尾。
- **从 ECU 资源同步视图**：`resources` 中能推导的外设类型、`metadata.cores` 中有对应键的字段，用 ECU 资源的推导结果覆盖；`ports` 在 `add-chip-ports-from-ecu-resources` 提供 `ports_from_ecu` 之后一并推导；返回每个视图是否改变。
- **待确认标记**：可确认（从 `metadata.unconfirmed` 移除，说明写入修改记录）或新增标记；两者都不改动数据本身。
- **保存修复结果**：
  - 不允许改名；
  - 磁盘文件在加载后被改过时拒绝保存；
  - 覆盖前备份为 `<name>.yaml.bak`；
  - `resource_version` 默认递增末位，也可以由调用方指定；
  - 重新计算校验和，并刷新芯片库里的芯片。
- **修改记录**：每次保存在 `data/chips/history/<name>.yaml` 追加一条，记录日期、修改人、来源、说明、版本变化、各类改动的键及新旧值、同步的视图、确认的待确认项、保存后的校验和。修改记录不参与芯片校验和，也不会被当作芯片加载。
- **命令行工具** `tools/chip_repair.py`：`diff` 只显示差异；`apply` 合并选中的改动、同步视图并保存。

已使用该芯片的项目不需要新增机制：现有的"芯片库版本与项目副本不同 → 从芯片库更新"提示会自动生效。

## Impact

- Affected specs：`chip-repair`（新增能力）
- Affected code：
  - 新增 `autosar_configurator/core/hardware/chip_repair.py`
  - `autosar_configurator/core/hardware/chip_database.py`：把 `.properties` 的解析从 `import_ecu_resources_from_properties` 中拆出一个不修改芯片的函数，原方法改为调用它，行为不变
  - 新增 `tools/chip_repair.py`
  - 测试 `tests/core/test_chip_repair.py`；文档 `doc/chip_ecu_resources.md`
- 依赖：`ports` 的推导来自 `add-chip-ports-from-ecu-resources`（未实施）。该变更实施之前，同步视图不改动 `ports`，并在结果里注明。
- 兼容性：
  - 芯片 YAML 格式不变；
  - 新增 `history/` 子目录，芯片库只读取 `data/chips/*.yaml`，不受影响；
  - 设计器的保存流程不变，暂不写修改记录（后续修复向导变更时统一）。
- 不在本变更范围内：
  - 修复向导及设计器、项目属性、向导里的入口；
  - 引脚复用表合并、兄弟芯片对比；
  - 修复对项目的影响预览；
  - 用户级芯片覆盖目录。
