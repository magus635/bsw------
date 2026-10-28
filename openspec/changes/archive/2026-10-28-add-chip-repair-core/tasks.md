## 1. 修复来源与差异

- [x] 1.1 从 `ChipDatabase.import_ecu_resources_from_properties` 拆出 `ecu_resources_from_properties(paths)`（不修改芯片，后读的文件覆盖先读的同名键）；原方法改为调用它，现有测试不改仍通过
- [x] 1.2 用内置芯片当初导入时所用的厂商 `.properties` 与该芯片比较，要求零差异；有"只是类型不同"的差异时先修正解析
  - 结论：4 颗内置芯片与厂商文件严格比较均为零差异，解析不需修改
- [x] 1.3 `diff_ecu_resources(old, new)`：扁平键、归一化后比较、按键排序、`type_only` 标记
- [x] 1.4 `missing_key_changes(chip, referenced_keys)`：基于 `collect_referenced_keys(_in_dirs)`，生成值为空的新增项
- [x] 1.5 单元测试：新增、删除、变化；区间写法等于列表写法；只是类型不同；多文件覆盖；缺失键

## 2. 合并与待确认标记

- [x] 2.1 `apply_changes(chip, diff, selected_keys)`：返回副本；删除需显式选中；保持键序，新增键在模块末尾按键名排序
- [x] 2.2 `confirm_fields` / `mark_unconfirmed`：兼容映射与列表两种写法，写回统一为映射；不改动被标记的数据
- [x] 2.3 单元测试：只应用选中项、未选中的删除、空选择、输入芯片不被修改、确认后 `check_chip` 不再报告该字段

## 3. 视图同步

- [x] 3.1 `derive_views(chip)`：外设按类型替换（推导不出的类型保留）、核字段按键存在与否覆盖、`ports` 在 `ports_from_ecu` 存在时推导；返回 `ViewReport`
- [x] 3.2 单元测试：保留手工外设类型、无核键、无引脚推导、`ViewReport` 内容
- [x] 3.3 对 4 颗内置芯片运行 `derive_views` 并记录各视图的差异（不写文件），结论写进 design.md；差异不合理时先停下讨论
  - 结论：resources 均不变、ports 未推导；THA610X 核数改为"任一键相符即保留"后不变（见 design.md Implementation Notes）

## 4. 保存与修改记录

- [x] 4.1 `save_repaired_chip(database, chip, base, record)`：
  - 检查是否改名、文件是否在加载后被改过（`ChipFileChanged`）
  - 写 `.bak` → 原子写入 → 追加修改记录 → `register_chip`
- [x] 4.2 `resource_version` 规则：给定版本、末位递增、末段非数字、原来为空
- [x] 4.3 修改记录 `history/<name>.yaml`：首次创建、追加不改旧条目、不参与校验和
- [x] 4.4 单元测试（`tmp_path` 芯片目录）：
  - 正常保存与备份、改名被拒、文件被改被拒、`content_modified` 芯片可保存且记录
  - 芯片库忽略 `history/`
  - 项目副本与修复后的芯片库不一致时 `chip_data_findings` 报告

## 5. 命令行与文档

- [x] 5.1 `tools/chip_repair.py diff|apply`，参数与退出码按 design.md
- [x] 5.2 测试：`diff` 不写文件；`apply` 默认不删除；没有改动时退出码为 2；文件已被改动时退出码为 1
- [x] 5.3 用一颗内置芯片的副本走一遍端到端：`diff` → `apply`（含 `--confirm`）→ 重新加载 → `check_chip`，结果附在本任务下
  - 结果：THA610X 副本，改 1 个值、加 1 个键并确认 flash_size → 1.0.0→1.0.1、生成 .bak 与修改记录、重新加载校验和正确，check_chip 不再报告 flash_size；再次 apply 退出码 2
- [x] 5.4 `doc/chip_ecu_resources.md` 增加"修复已有芯片"一节（流程、命令行、修改记录格式）
- [x] 5.5 全量测试通过（`QT_QPA_PLATFORM=offscreen python -m pytest tests -q`）：1137 passed，5 skipped

依赖与并行：1 与 2 可以并行；3.1 中的 `ports` 推导依赖 `add-chip-ports-from-ecu-resources`，没有它也能完成（记为未推导）；4 依赖 1–3；5 依赖 4。
