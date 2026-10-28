## Context

芯片 YAML（`data/chips/<name>.yaml`）里与修复有关的数据：

| 数据段 | 角色 | 来源 |
|---|---|---|
| `ecu_resources` | 唯一权威，模板用 `ecu:get` 读取 | 厂商 `.properties`、插件所需键 |
| `resources` | 视图：外设实例 | `peripherals_from_ecu()` 推导 |
| `metadata.cores` | 视图：核数、可用核、主核 | `typed_fields_from_ecu()` 推导 |
| `ports` | 视图：引脚表 | `ports_from_ecu()`（`add-chip-ports-from-ecu-resources`，未实施） |
| `selectors`、`name/family/package/description`、`metadata` 其余字段 | 独立数据，本变更不推导 | 手册 |
| `metadata.unconfirmed` | 待确认标记 | 修复过程 |
| `resource_version`、`checksum` | 版本与完整性 | 保存时写入 |

已有能力：`flatten_ecu_resources` / `nest_flat_resources`（扁平键与嵌套结构互转）、`normalize_value`（加载时把区间写法展开为列表）、`ecu_resource_data._same`（值与类型都相同）、`collect_referenced_keys(_in_dirs)`（模块引用的键）、`check_chip`（完整性检查）、`ChipDefinitionExporter.save_yaml`（原子写入并写校验和）、`WorkspaceProject.chip_data_findings`（芯片库与项目副本不一致时提示）。

## Goals / Non-Goals

- Goals：
  - 不经过界面也能对已有芯片完成"取来源 → 看差异 → 选择性合并 → 同步视图 → 处理待确认 → 保存并留记录"；
  - 每一步都可以单独测试；
  - 后续的修复向导只需调用这些函数。
- Non-Goals：
  - 界面；
  - 引脚复用表合并、兄弟芯片对比、项目影响预览；
  - 用户级覆盖目录；
  - 设计器保存流程的改造。

## Decisions

- **一个模块 `chip_repair.py`，函数式接口，输入芯片不被修改。**
  - 每个变更函数返回新的 `ChipDefinition`（深拷贝），方便调用方保留"修复前"做对比和回退。
  - 主要接口：
    - `diff_ecu_resources(old, new) -> EcuDiff`
    - `ecu_resources_from_properties(paths) -> EcuResources`
    - `missing_key_changes(chip, referenced_keys) -> EcuDiff`
    - `apply_changes(chip, diff, selected_keys) -> ChipDefinition`
    - `derive_views(chip) -> (ChipDefinition, ViewReport)`
    - `confirm_fields(chip, fields_with_notes)` / `mark_unconfirmed(chip, field, note)`
    - `save_repaired_chip(database, chip, base, record) -> SaveResult`
  - 备选是一个有状态的 `ChipRepairSession` 类。界面层以后可以在这些函数外面包一层会话，核心层保持无状态更容易测试，所以不采用。
- **差异只看 `ecu_resources`，按扁平键比较。**
  - `EcuDiff.changes` 中的每一项是 `KeyChange(key, kind, old, new)`，`kind ∈ {added, removed, changed}`，按键排序。
  - 两边都先经 `normalize_value`，再用 `_same` 比较：区间写法和展开的列表算相同。
  - 类型不同算作变化（例如 `1` 与 `"1"`），并在 `KeyChange.type_only` 里标出，方便调用方识别"只是类型不同"。原因是 `ecu:get` 对两者的结果不同，不能静默视为相同。
- **合并只动选中的键。**
  - `selected_keys` 为空表示什么都不做。
  - 删除和其他改动一样必须显式选中，核心层没有"全部应用"的默认值，由调用方（命令行或向导）决定默认勾选什么。
  - 已有键原位更新；新增键追加到所在模块末尾，多个新增键按键名排序；新模块追加到末尾。这样保存后的 YAML 差异最小。
- **视图同步。**
  - `resources`：`peripherals_from_ecu` 能推导出的外设类型整体替换，推导不出的类型保留不动。手工维护的类型（如 `pwm_channel`）因此不丢。
  - `metadata.cores`：只覆盖 ECU 资源里有对应键的字段。
  - `ports`：用 `importlib` 探测 `ecu_resource_diagnostics.ports_from_ecu`；存在且有 Port 数据时替换，否则不改动，并在 `ViewReport` 里记为"未推导"。
  - `ViewReport` 列出每个视图的状态：未变、已更新（附实例数变化）或未推导（附原因）。
- **待确认标记。** `metadata.unconfirmed` 支持两种写法：映射（字段 → 说明）和列表。读的时候沿用 `chip_completeness.unconfirmed_fields` 的解析；写回统一为映射。确认操作只移除标记，确认说明写入修改记录，不写进芯片。
- **保存的安全检查。**
  1. **不允许改名**：`chip.name` 必须等于 `base.name`，否则抛 `ValueError`。
  2. **文件没有被别人改过**：目标文件当前内容的校验和（按 YAML 重新加载后计算，不比较原始文本）必须等于 `base` 的校验和。不相等时抛 `ChipFileChanged`。
  3. **在设计器外改过的芯片照常修复**：`base.content_modified` 为真时允许保存，修改记录里写 `base_modified_outside: true`。
  4. 写入顺序：复制旧文件为 `<name>.yaml.bak`（覆盖上一次的备份）→ 原子写入新 YAML → 追加修改记录 → `database.register_chip`。
- **`resource_version`。**
  - 调用方给出版本时使用给出的值。
  - 否则末位加一：`1.0.0` 变为 `1.0.1`；末段不是数字时追加 `.1`；原来为空时写 `1.0.0`。
  - 修改记录同时写旧版本和新版本。
- **修改记录文件 `data/chips/history/<name>.yaml`。**
  - 放子目录是因为芯片库只扫描 `data/chips/*.yaml`（不递归），历史文件不会被误当成芯片；放在同级的 `<name>.history.yaml` 会被扫描到，所以不采用。
  - 格式：

    ```yaml
    chip: THA610X_LFBGA180
    entries:
      - date: 2026-10-28
        author: <调用方给出，缺省为操作系统用户名>
        source: MCAL R440 Port_THA610X.properties
        note: 补 Port 只读端口
        resource_version: {old: 1.0.0, new: 1.0.1}
        base_modified_outside: false
        ecu_resources:
          added:   [{key: Port.AvailableReadOnlyPorts, new: "_40_"}]
          changed: [{key: Mcu.X, old: 1, new: 2}]
          removed: []
        views: {resources: updated, metadata.cores: unchanged, ports: not derived}
        confirmed: [{field: metadata.flash_size, note: 按 SDK 链接脚本核对}]
        marked: []
        checksum: <保存后的校验和>
    ```

  - 只追加，不改写已有条目。
  - 新旧值完整记录，列表也写全：文件独立存放，长一些可以接受，换来的是可审计。
- **命令行 `tools/chip_repair.py`。**
  - `diff <chip> <file.properties>...`：打印差异，不写文件。
  - `apply <chip> <file.properties>... --keys K1,K2 | --all-added --all-changed [--include-removed] --source TEXT --note TEXT [--version V] [--confirm FIELD=NOTE ...]`：依次合并、同步视图、处理待确认标记、保存。
  - 删除只有加 `--include-removed` 才会应用。
  - 退出码：0 表示成功；1 表示参数错误或文件已被改动；2 表示没有任何改动。

## Risks / Trade-offs

- **`.properties` 解析出的类型可能与 YAML 中的不同**（如数字被解析为字符串），导致大量"只是类型不同"的变化。
  - 缓解：任务 1.2 用内置芯片当初导入时所用的厂商文件重新比较，要求零差异；不为零时先修正解析，不在比较时放宽类型。
- **第一次对内置芯片同步视图时 `resources` 会变化**：目前 `resources.intc_source` 与按 `Intc` 推导的结果数量不同。
  - 缓解：`ViewReport` 给出实例数变化；任务 3.3 先记录每颗内置芯片的推导差异，确认没有问题再允许命令行默认同步视图。
- **单个 `.bak` 只保留最近一次。**
  - 内置芯片另有 git 历史，修改记录保存了全部新旧值，足以回溯。

## Migration Plan

不需要迁移：没有 `history/` 文件的芯片照常加载，第一次修复时创建该文件。

## Implementation Notes

- **`author`**：调用方给出时使用给出的值；否则取 `git config user.name`（在芯片目录下执行）；git 不可用或该项为空时取操作系统用户名。已与用户确认。
- **部分来源只比较其中的模块**：增加 `diff_from_source(current, source)`，只比较来源里出现的模块。原因是厂商 `.properties` 往往只覆盖部分模块，直接比较整个芯片会把其余模块的所有键都报成"删除"。命令行使用这个函数；`diff_ecu_resources` 保持完整比较。
- **任务 1.2 的结论**：4 颗内置芯片与当初导入所用的厂商文件（`tests/fixtures/ecu_resources/` 与 `test_import_project/Def/plugins/Resource_THA6_AS440/resource/`）按严格类型比较都是零差异，`.properties` 的解析不需要修改。
- **任务 3.3 的结论**：
  - 4 颗内置芯片的 `resources` 同步后都没有变化：此前担心的 `intc_source` 数量差异并不存在，`resources.intc_source` 本来就是按 `Intc` 推导的。
  - `ports` 都记为"未推导"。
  - 只有 THA610X 的核字段原本会变化：`OsResource.NumOfCores` 为 1，`Resource.NumOfCores` 为 2，`metadata.cores.count` 为 2；按 `TYPED_FIELD_MAP` 的顺序会取 1。改为"已有值与任一对应键相符就保留"，与 `chip-library` 的完整性规则（任一相符即可，MCAL 可能计入 Os 不用的锁步核）一致。改后 4 颗芯片的所有视图都不变，所以命令行 `apply` 默认同步视图。
