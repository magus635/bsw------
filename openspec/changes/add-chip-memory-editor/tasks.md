## 1. 数据模型

- [x] 1.1 `MemoryRegionDef` 新增可选字段 `memory`、`window`、`source`；缺省时 `memory` 等于 `name`（`memory_name` 属性）；`parse_memory_regions` 读新字段，旧格式不变，新字段必须是文本
- [x] 1.2 `memory_region_dict` 只写有值的字段，`memory` 等于 `name` 时不写；旧芯片往返后与以前完全一致
- [x] 1.3 分组函数 `group_memories`：按 `memory` 归并窗口，保持文件顺序，组的位置在其第一个窗口处；`rename_memory`：改存储名，改所有窗口，重名被拒
- [x] 1.4 校验函数 `region_problems`：阻止保存的错误（名称重复）与只提示的问题（重叠、同存储大小不一致、同存储类型混用）分开返回；数字、大小、类型的错误本来就在读取时抛 `ValueError`
- [x] 1.5 测试：`test_memory_regions_grouping.py`（新字段往返、旧格式不变、分组、重命名、各条校验）；`test_chip_memory_yaml.py`（YAML 往返；库内全部芯片的 stored checksum 等于重新计算的值）

## 2. 导入

- [x] 2.1 新增 `core/hardware/memory_regions_import.py`：从 ADS `.scat` 头部注释表解析区域，识别 `起始 终止 - 长度` 与 `起始 起始 + 长度` 两种行，只读注释表里的行
- [x] 2.2 类型、可缓存、核心从名称和行尾说明读；说明里没有的字段不猜，记入 `unstated_cache`、`unstated_type`；全部带 `source`
- [x] 2.3 合并 `merge_import`：同名不覆盖，只报告；文件里重名只取第一行；不改入参
- [x] 2.4 用 `LinkerAdsPf.scat` 与 OS 模板 `scatter.scat` 的注释表各做一组测试（合成文本，不依赖 `doc/` 目录）：`test_memory_regions_import.py`

## 3. 设计器

- [ ] 3.1 新增 `ui/dialogs/memory_region_editor.py`：按存储分组的表格，增删改、按存储重命名；输入时校验并列出问题；十六进制输入
- [ ] 3.2 "导入…"按钮：选择 `.scat`、预览、确认后合并；已有同名项不覆盖
- [ ] 3.3 在 `chip_definition_designer_dialog.py` 加第六个页签；工作副本进 `_build_current_chip`；未保存状态与预览页同步
- [ ] 3.4 保存遵守"只标记不删除"：来源缺失的项标待确认；修改过的项不自动确认
- [ ] 3.5 UI 测试（offscreen）：编辑、校验提示、导入预览与合并、保存后重新加载一致；原有设计器测试全部保持通过

## 4. THA6206 数据

- [ ] 4.1 `THA6206_LFBGA292.yaml`：给 25 项补 `memory`、`window`、`source`，数值不变，仍全部待确认；按"修复"流程升 `resource_version`、备份、写历史
- [ ] 4.2 测试：数值与之前逐项相同；`test_library_chips_unchanged_and_tha6206_regions` 仍通过；其他库内芯片的 checksum 不变

## 5. 展示

- [ ] 5.1 `layout.py`：物理区域一级按存储分组显示窗口；没有 `memory` 字段的旧芯片显示与现在一致
- [ ] 5.2 工作台布局页签随之更新；原有布局测试保持通过

## 6. 验证

- [ ] 6.1 全量测试（SC300 的两个已知失败除外）；`openspec validate add-chip-memory-editor --strict`
- [ ] 6.2 用户在设计器里打开 THA6206，核对归组是否合理（特别是 CPU 本地别名与各核 AXI 区域是否同一块存储）
