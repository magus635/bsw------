## 1. 模型

- [ ] 1.1 `ExecRegion` 新增 `start_mode`（`after`/`offset`/`address`，缺省 `after`）、`offset`、`address`、`size`、`load_region`、`limit_align`（缺省 64），全部可选
- [ ] 1.2 `MemoryMapConfig.load_regions`（名称、窗口、大小上限）；读写保持旧 `memorymap.json` 可读，旧文件读进来行为不变
- [ ] 1.3 校验：`offset` 不为负；`address` 不在所选窗口时给提示；`load_region` 必须存在；`size` 为正
- [ ] 1.4 测试：新字段往返；旧文件读取不变；各条校验

## 2. 生成器

- [ ] 2.1 `plan.py`：起点按 `start_mode`；大小按 `size`（缺省规则不变）；多加载区域（列表为空时一个 `ROM_CODE`，与现在相同）；界限对齐按 `limit_align`
- [ ] 2.2 `generators/ads.py`：`offset` 写成 `<窗口>_ADDRESS+0x...`；`address` 写 `#define <区域>_ADDRESS` 再引用；每个加载区域一个块
- [ ] 2.3 生成前检查：`address` 落在窗口外列为警告
- [ ] 2.4 测试：三种起点各一例；大小；两个加载区域；界限对齐；没有新字段的旧配置除界限对齐外逐字节不变（单独测试界限对齐这一处有意的变化）；往返经 `parse_scatter`

## 3. 导入

- [ ] 3.1 新增 `core/memmap/import_scatter.py`：用 `parse_scatter` 读 `.scat`，转出加载区域、执行区域（窗口、起点方式、对齐、大小、种类）与手动放置
- [ ] 3.2 种类推断（design.md D5）；推不出的标待确认
- [ ] 3.3 不能导入的：通配、`.ANY`、按文件选择器、`+First`、落不进窗口的区域，逐条列出原因
- [ ] 3.4 同名区域、已有手动放置都不覆盖，报告
- [ ] 3.5 预览与合并分开；预览不改配置
- [ ] 3.6 测试（合成文本，不在运行时读 `doc/`）：各转换规则；不能导入的报告；不覆盖；预览不改；导入后再生成，区域、起点、放置与导入的文件一致

## 4. 出厂数据

- [ ] 4.1 `THA6206_LFBGA292_default.json`：`INT_VECTOR_TABLE` 改到 `CPUXATCM`；补 `CODE_CLONE`、`DATA_CLONE`、`BSS_CLONE`、`RAM_CODE`、`EX_CODE_CORE1`、`EX_CONST_DATA_CORE1`、`DFLASH_DATA`；栈的固定起点与大小；`UNDEFINE_RAM_DATA` 偏移；DFLASH 加载区域
- [ ] 4.2 测试：新增区域的窗口都在芯片里；出厂规则仍全部有效；`test_memmap_factory.py` 保持通过

## 5. 界面

- [ ] 5.1 配置页签的区域编辑：起点方式、偏移/地址（十六进制）、大小、所属加载区域、界限对齐
- [ ] 5.2 加载区域的增删改
- [ ] 5.3 "从链接文件导入…"：选 `.scat`、预览、确认合并
- [ ] 5.4 UI 测试（offscreen）

## 6. 文档

- [ ] 6.1 `add-linker-file-generation/design.md`、`add-memory-layout-config/design.md`：按 design.md D7 改掉"厂商脚本是标准答案"
- [ ] 6.2 记忆：生成器是权威，厂商脚本只是可选导入源

## 7. 验证

- [ ] 7.1 全量测试（SC300 的两个已知失败除外）；`openspec validate update-linker-generator-authority --strict`
- [ ] 7.2 用户在 THA6206 工程上配置并生成，在 ADS 里实际链接（工具外，需要用户）
