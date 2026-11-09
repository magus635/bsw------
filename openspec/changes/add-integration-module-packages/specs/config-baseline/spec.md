# config-baseline — Delta

## ADDED Requirements

### Requirement: Layered Baseline Composition

对 format 8 工程中来自模块包的每个模块，工具 SHALL 按层合成基线 Base'，优先级从低到高为 DEFAULT（定义默认值）< REC < DERIVED < PRE。DERIVED 层在本阶段为空，但合成接口和三方合并 SHALL 支持插入该层，不需要改动接口。

#### Scenario: Pre 优先于 Rec

- **WHEN** 同一参数在 REC 中为 `A`、在 PRE 中为 `B`
- **THEN** Base' 中该参数为 `B`，来源为 PRE

#### Scenario: 空的 DERIVED 层不影响结果

- **WHEN** 合成时传入一个空的 DERIVED 层
- **THEN** Base' 与不传 DERIVED 层时完全相同

### Requirement: Baseline Snapshot

工具 SHALL 把用户接受的基线保存为 `config/base/<Module>.arxml`（与活配置同格式），并把快照哈希记在 `.dpa` 中。打开工程时，快照缺失或哈希不符 SHALL 按“旧工程迁移”处理：活配置中现有的值一律视为 USER，只有 PRE 会改动它们，且必须先预演。

#### Scenario: 快照被手工修改

- **WHEN** `config/base/Mcu.arxml` 的内容与 `.dpa` 中记录的哈希不一致
- **THEN** Mcu 的现有值全部视为 USER，Rec 或默认值的变化不会改动它们

### Requirement: Three-Way Merge On Load

加载 format 8 工程时，工具 SHALL 对每个路径比较 Base（快照）、Base'（新基线）和 Active（活配置）：Base = Base' 时不动；用户没改过的值（Active = Base）采用 Base'；用户改过的非 Pre 值保留并在报告中标为“基线变化但已被用户覆盖”；属于 PRE 且未解锁的值不等于 Base' 时改为 Base' 并标为“预设强制”；Base' 中新增的容器实例被创建。合并 SHALL NOT 自动删除任何容器或值；Base 中有而 Base' 中没有的容器只在报告中列出。

#### Scenario: 包中的 Rec 值和 Pre 值升级

- **WHEN** 在包中修改一个 Rec 值和一个 Pre 值后重新打开工程并确认合并
- **THEN** 用户没改过的 Rec 值跟随变化
- **AND** 用户改过的 Rec 值保留，并出现在报告中
- **AND** Pre 值被强制改变，并出现在报告中

#### Scenario: Pre 删除了容器

- **WHEN** Base 中有某个 Pre 容器而 Base' 中没有
- **THEN** 该容器保留在 Active 中，并在报告中列出，由用户决定是否删除

### Requirement: Preview And Confirm Before Change

当合并报告中有改动类条目（采用新基线、预设强制、创建）时，工具 SHALL 先预演并展示报告，用户确认后才写入 Active，并把 Base' 写回快照。用户拒绝时 Active 和 Base SHALL 都不变，下次打开工程时继续提示。

#### Scenario: 用户拒绝合并

- **WHEN** 打开工程时出现改动类合并条目，用户在预演中选择拒绝
- **THEN** 活配置和基线快照都不变
- **AND** 下次打开工程时再次出现同样的预演提示

### Requirement: Value Origin By Comparison

每个值的来源 SHALL 由比较得出，不写入配置文件：路径在 PRE 中出现为 `PRE`；Active 等于 Base 且 Base 的值来自 Rec 或定义默认值为 `REC` / `DEFAULT`；Active 不等于 Base 或 Base 中没有该路径为 `USER`；`DERIVED` 预留。活配置 arxml 的格式 SHALL 保持不变。

#### Scenario: 用户修改 Rec 初值

- **WHEN** 一个来自 REC 的参数被用户改为其他值
- **THEN** 该参数的来源显示为 `USER`
- **AND** 保存后的 `config/<Module>.arxml` 格式与改造前相同

### Requirement: Pre Read-Only Lock

来源为 PRE 的参数、引用和容器 SHALL 只读：拦截 SHALL 在命令层执行，覆盖配置面板、批量编辑、导入和 AI 助手等所有编辑入口；界面灰显并说明来源和 pre 文件。Pre 创建的容器不能删除或改名，但可以在其下添加 Pre 中没有的子容器和参数。用户 MAY 对单个参数解除锁定，解锁记录写入 `.dpa` 的 `pre_unlocked`，解锁的参数不再被“预设强制”改回。

#### Scenario: 编辑 Pre 参数被拒绝

- **WHEN** 用户试图修改 Mcu 复位原因表中来源为 PRE 的参数
- **THEN** 命令被拒绝，状态栏给出提示，撤销栈不变

#### Scenario: 解除锁定后可编辑

- **WHEN** 用户对该参数选择“解除锁定”并修改其值，然后保存并重新打开工程
- **THEN** 修改后的值保留，参数路径记录在 `pre_unlocked` 中

### Requirement: Add Module Initialized From Baseline

从模块包添加模块时，工具 SHALL 合成 Base'（默认包含 REC），以它作为活配置的初值，并写入基线快照。

#### Scenario: 添加带 Rec 的模块

- **WHEN** 从一个含 Rec 和 Pre 的模块包添加模块
- **THEN** 活配置中出现 Rec 和 Pre 的值，`config/base/<Module>.arxml` 被创建，所有值的来源不是 `USER`
