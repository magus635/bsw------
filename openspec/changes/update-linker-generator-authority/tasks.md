## 1. 模型

- [x] 1.1 `ExecRegion` 新增 `start_mode`（`after`/`offset`/`fixed`，缺省 `after`）、`offset`、`address`、`size`、`load_region`、`limit_align`（缺省 64），全部可选；常量 `AFTER`、`OFFSET`、`FIXED`、`START_MODES`、`START_LABELS`、`DEFAULT_LIMIT_ALIGN`
- [x] 1.2 `LoadRegion`（名称、窗口、大小上限）与 `MemoryMapConfig.load_regions`（有序）；读写只在与旧行为不同时才写新字段，旧 `memorymap.json` 读进来与写出去都与以前相同；数值写成十六进制文本
- [x] 1.3 校验：`set_start`（偏移不为负、固定地址必须给出）、`set_size`（为正）、`set_load_region`（必须存在）；加载区域的增、改名（执行区域跟着改）、删（执行区域回到第一个）；`region_doubts`：固定地址在窗口外、偏移超出窗口、大小超过窗口，只提示
- [x] 1.4 测试：`tests/core/test_memmap_config_start.py`（26 个）；原有核心测试保持通过（相关 215 个）

## 2. 生成器

- [x] 2.1 `plan.py`：起点按 `start_mode`；大小按 `size`（缺省规则不变）；多加载区域（列表为空时一个 `ROM_CODE`，与现在相同）；界限对齐按 `limit_align`
  - `PlanRegion` 新增 `start_mode`、`offset`、`address`、`limit_align`；窗口内的先后仍按 `order`、名称，与加载区域和起点方式无关，`after` 区域接在窗口里前一个区域之后（不论它的起点方式）
  - 配置了加载区域时按列表顺序，每个用自己的窗口基址与大小；区域的 `load_region` 为空归第一个；配置的加载区域所在窗口也写 `#define`；没有执行区域的加载区域不写（警告），第一个加载区域放保留区域时保留
  - 保留区域放在第一个加载区域，接在它的最后一个执行区域之后
- [x] 2.2 `generators/ads.py`：`offset` 写成 `<窗口>_ADDRESS+0x...`；`address` 写 `#define <区域>_ADDRESS` 再引用；每个加载区域一个块
  - 区域的 `#define` 写在窗口的 `#define` 之后；每个加载区域块的末尾是它自己的界限区域；界限区域对齐用 `limit_align`
- [x] 2.3 生成前检查：`address` 落在窗口外列为警告
  - 警告取 `config.region_doubts`（另含偏移超出窗口、大小超过窗口）；拒绝：区域的加载区域不存在、加载区域的窗口不在芯片里、固定地址名与窗口地址名相同；警告：空加载区域、`after` 引用了后面加载区域里的区域
- [x] 2.4 测试：三种起点各一例；大小；两个加载区域；界限对齐；没有新字段的旧配置除界限对齐外逐字节不变（单独测试界限对齐这一处有意的变化）；往返经 `parse_scatter`
  - 新增 `tests/core/test_linker_plan_start.py`（24 个）；`test_ads_generator.py` 的往返检查按加载区域与起点方式，整套 THA6206 出厂测试改为带上出厂加载区域、期望值取自出厂布局条目（任务 4 正在改出厂数据）；相关 6 个测试文件共 122 个通过

## 3. 导入

- [x] 3.1 新增 `core/memmap/import_scatter.py`：用 `parse_scatter` 读 `.scat`，转出加载区域、执行区域（窗口、起点方式、对齐、大小、种类）与手动放置
- [x] 3.2 种类推断（design.md D5）；推不出的标待确认
- [x] 3.3 不能导入的：通配、`.ANY`、按文件选择器、`+First`、落不进窗口的区域，逐条列出原因
- [x] 3.4 同名区域、已有手动放置都不覆盖，报告
- [x] 3.5 预览与合并分开；预览不改配置
- [x] 3.6 测试（合成文本，不在运行时读 `doc/`）：各转换规则；不能导入的报告；不覆盖；预览不改；导入后再生成，区域、起点、放置与导入的文件一致；`tests/core/test_import_scatter.py`（48 个）
  - 往返测试 `test_linker_plan_start.py::test_import_then_generate_gives_the_same_file`：生成 → 导入到同芯片的空配置 → 再生成，逐字节相同。补这个测试时发现：为芯片缺少的核写的保留区域（`config.trimmed` 里的名字）会被当成普通区域导入，再生成时多出一份；已改为不导入并说明"由生成器按保留选项自己产出"
- [x] 3.7 导入时猜出的种类在配置里保留"待确认"标记（`options.kind_unconfirmed`），直到用户设种类（`MemoryMapConfig.set_kind`，原样应用也算确认）；区域改名、删除时标记跟着走

## 4. 出厂数据

- [x] 4.1 `THA6206_LFBGA292_default.json`（版本 2）：`INT_VECTOR_TABLE` 改到 `CPUXATCM`（0x0，大小 0x2080）；补 `CODE_CLONE`、`DATA_CLONE`、`BSS_CLONE`、`RAM_CODE`、`EX_CODE_CORE1`、`EX_CONST_DATA_CORE1`、`DFLASH_DATA`；两个核的用户栈用固定起点（0x30129000、0x30529000），所有栈带大小 0x1000；`UNDEFINE_RAM_DATA` 偏移 0x20000；加载区域 `ROM_CODE` 与 `DFLASH_CODE`。读取侧：`factory.layout_region` 读新字段，`regions._region` 改用它，工程第一次准备时带上出厂加载区域（之后是工程自己的）
- [x] 4.2 测试（`test_memmap_factory.py`，44 个）：上述每处改正与新增；固定地址、偏移都落在各自窗口里（`region_doubts` 为空）；新增区域的窗口都在芯片里；出厂规则仍全部有效

## 5. 界面

- [x] 5.1 配置页签的区域编辑：右侧树下的"执行区域属性"表单（种类、起点方式、偏移/地址（十六进制）、大小、所属加载区域、界限对齐），"应用"一次全部生效或全部不生效；必需区域的种类不可改；树上加"起点""大小""加载区域"三列；固定地址落在窗口外等疑点应用后列出，不阻止
  - 模型补充：`set_limit_align`（必须是 2 的幂，`AlignExpr` 的要求）、`set_kind`、`change_load_region`、`move_load_region`
- [x] 5.2 加载区域的增删改：`LoadRegionDialog`（"加载区域…"），按顺序列出名称、窗口、起始、大小上限、执行区域数；新增（大小留空取窗口大小）、改名（执行区域跟着改）、改窗口与大小、上移下移、删除（执行区域回到第一个）
- [x] 5.3 "从链接文件导入…"：选 `.scat`、`ImportPreviewDialog` 列出新增/跳过/不能导入/近似导入各项、确认才合并；没有扫描结果（不知道芯片窗口）时不导入并说明；猜出的种类在树和顶部说明里标"种类待确认"
- [x] 5.4 UI 测试（offscreen）：`tests/ui/test_memory_map_region_properties.py`；与核心、配置页签、工作台测试一起 217 个通过（2026-11-03，用户运行）

## 6. 文档

- [x] 6.1 `add-linker-file-generation/design.md`（D6、D7、风险、迁移）、`tasks.md` 7.1；`add-memory-layout-config/design.md`（D3、风险）、`tasks.md` 4.3、`proposal.md`：去掉"厂商脚本是标准答案"，改为"生成器是权威，厂商脚本只是可选导入源"；界面上显示的出厂说明（`factory.FACTORY_NOTE`）同样改掉
- [x] 6.2 记忆：`linker-generator-authority.md`

## 7. 验证

- [ ] 7.1 全量测试（SC300 的两个已知失败除外）；`openspec validate update-linker-generator-authority --strict`
- [ ] 7.2 用户在 THA6206 工程上配置并生成，在 ADS 里实际链接（工具外，需要用户）
