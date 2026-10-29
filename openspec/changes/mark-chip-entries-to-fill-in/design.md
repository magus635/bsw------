## Context

芯片 `ecu_resources` 里的 `null`（`PLACEHOLDER`）有两种来源，存下来以后无法区分：

| 来源 | 例子 | 含义 |
|---|---|---|
| 厂商 `.properties` 的空值（`Key:` 后面没有值） | THA6206 `Gtm.TriggerXModule4`，库内共 49 个 | 合法数据，EB 里 `ecu:get` 同样得到空值 |
| 键扫描生成的占位（`missing_key_changes`、设计器"加入待填写"） | 向导扫描出的 `Os.Missing` | 模块需要，芯片还没有值 |

现有的诊断和检查都按"键在不在"判断，所以占位一旦写入就和真正有值的键一样，不再被报告。

## Goals / Non-Goals

- Goal：占位写入以后仍然能被发现（完整性、工程诊断），填写以后自动消除；向导不再顺手把占位写进芯片。
- Non-Goal：改变 `null` 的存储或解析方式；修正设计器保存时按全部 `null` 计数的提醒。

## Decisions

### D1 用 `metadata.unconfirmed` 标记识别占位，而不是看值是否为 `null`
- 检查所有 `null`：库内 49 个厂商空值会让 THA610X、THA6206、THA6412 全部变成"（资料不完整）"。
- 只检查"被引用且为 `null`"：`Port.DefaultHighStrengthCtrIPin`、`Port.AvailableLVDSPorts` 是被引用的厂商空值，会在每个用这些芯片的工程里误报；而且不打开工程就看不到。
- 把 `.properties` 空值改解析成 `""`：要改解析器、迁移数据、升级版本，用了芯片副本的工程都会看到差异。

标记复用现有机制：`check_chip` 已经报告标记，修复向导第 4 步可以处理标记，历史已经记录 `marked`/`confirmed`。

### D2 在产生占位的地方加标记
`.properties` 里的空值也会生成 `new=None` 的新增项，所以保存时只看"新出现的 `null`"分不出来源。
- `KeyChange` 增加 `to_fill_in: bool = False`，只有 `missing_key_changes` 把它设为 `True`。`RepairSession.build` 对选中的 `to_fill_in` 项、且结果仍是 `null` 的条目加标记。同一个键 `.properties` 有值时，用文件里的值（现有规则），不加标记。
- 设计器：`EcuResourceEditor.add_placeholders` 记下本次加入的键（`set_resources` 时清空）；设计器 `_build_current_chip` 对其中仍为 `null` 的条目加标记。

### D3 标记的说明固定为 `待填写`，自动去除只处理这个说明
- 规则按当前状态判断，不依赖"上一版"：带 `待填写` 说明的 `ecu_resources.<模块>.<键>` 标记，条目有值或不存在时去掉。这样在 YAML 外部填了值的情况，下一次保存也会收拾干净。
- 其他说明的标记（例如人工标的"数据从别的芯片拷来，需要核对"）即使条目有值也保留，只能在修复向导第 4 步确认。
- 历史的 `confirmed` 由前后标记的差异算出（现有逻辑）；自动去掉的标记，说明默认为"已填写"。

核心函数放在 `chip_repair.py`，与 `confirm_fields`、`mark_unconfirmed` 并列，都返回新芯片：
- `mark_to_fill_in(chip, keys)`：给仍为 `null` 的条目加 `待填写` 标记，已有标记不覆盖；
- `drop_filled_marks(chip)`：按 D3 去掉标记；
- `to_fill_in_keys(chip)`：带 `待填写` 标记且仍为 `null` 的平铺键，按键排序。

调用位置：`RepairSession.build`（顺序：合并 → 加标记 → 去标记 → 推导视图 → 确认/新增标记）和设计器 `_build_current_chip`。`save_repaired_chip` 不做隐式改写，保存的就是调用方生成的芯片。

### D4 工程告警放在 `chip_data_findings`，不改 `diagnose`
`diagnose` 只拿到平铺后的 `project.ecu_resources`，看不到芯片的标记。`WorkspaceProject.chip_data_findings` 已经拿到工程实际使用的芯片（工程副本或芯片库），并把结果并入 ECU 资源报告的 `consistency`。在这里对 `to_fill_in_keys(chip)` 的每个键加一条告警，这样告警会出现在日志和状态栏计数中，与其他芯片数据问题放在一起。

### D5 向导：不默认勾选，保存前询问
- `RepairSession.default_selection` 不包含 `to_fill_in` 的新增项。命令行不使用默认选择，不受影响。
- 保存页统计 `to_fill_in_keys(修复后) - to_fill_in_keys(修复前)`，即本次新增的待填写项，在摘要里显示数量，保存前询问。只算新增的项，避免已有标记每次都弹窗。

## Risks / Trade-offs

- 本变更之前写入的占位没有标记，无法识别。已核对：当前芯片库里的 49 个 `null` 都能在厂商 `.properties` 中找到对应的空值，没有遗留的占位。工程 `chips/` 副本里如果有遗留，可以在修复向导第 4 步手工加标记。
- 用户在第 4 步"确认"一个仍为空的 `待填写` 标记，会再次把问题隐藏。这是带说明的显式操作，写进历史，可以接受。
