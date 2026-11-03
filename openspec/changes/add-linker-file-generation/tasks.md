## 1. 链接计划（编译器无关）

- [x] 1.1 新增 `core/memmap/plan.py`：`Plan`（加载区域、窗口、执行区域、保留区域、每段的放置状态）；`PlanRegion` 有名称、所在加载区域、窗口、种类、对齐、起始（`start_window` 窗口基址，或 `after` 前一个区域并对齐）、收纳的输出段、大小上限、是否需要界限区域、代码里的用途
- [x] 1.2 `build_plan(config, rows, chip_regions, needs, layout)`：段用 `place_all` 放置，只收"规则"和"手动"；窗口先 flash 后按地址，窗口内按 `order`、再按名称；区域内的输出段按名称排序；一个加载区域 `ROM_CODE`，基址为第一个 flash 窗口；大小上限取出厂布局的 `size`，没有就取窗口大小，栈默认 0x1000（design.md D1）
- [x] 1.3 选项 `options.reserve_missing_cores`（默认开，`reserve_missing_cores` / `set_reserve_missing_cores`，随 `memorymap.json` 保存）：开时 `config.trimmed` 的名字成为保留区域；需要界限的区域按 `RegionNeed.needs_limit_region()` 标记（只要栈顶的不需要），代码直接写 `<R>_LIMIT` 的也标记 R；没有扫描到任何需求时每个区域都标记并警告
- [x] 1.4 `check_plan(plan)` → (拒绝, 警告)：拒绝"待重新放置"的段（列出段名）、没有窗口的区域、窗口不在芯片里的区域、一个可用区域都没有；警告"未放置"的段、"必需区域未经代码核对"（以"没有扫描到需求"为准，配置不保存来源）、代码引用但配置里没有的区域
- [x] 1.5 测试 `tests/core/test_linker_plan.py`（18 例）：构造与起始、段排序、界限标记、大小、同样输入（含打乱顺序）同样计划、保留选项开/关/保存后仍关、各拒绝与警告条件

## 2. 生成器接口与登记表

- [x] 2.1 新增 `core/memmap/generators/__init__.py`：`CompilerEntry`（键、名称、`linkedFile` 下的目录、文件名、生成函数、不可用原因）、`compilers()`、`compiler(key)`、`generate(key, plan)` → `GeneratedFile`（文本、文件名、目录）；`UnsupportedCompiler` 错误
- [x] 2.2 登记 ADS（可用，`Ads/scatter.scat`）；GHS、HighTec、IAR、Tasking 登记为"尚未支持"并写明原因（没读过格式样例，见 D2）
- [x] 2.3 测试：登记表五项且只有 ADS 可用；GHS 等四种与未知编译器都抛 `UnsupportedCompiler`，不产生文本（`tests/core/test_ads_generator.py`）

## 3. ADS 生成器

- [x] 3.1 新增 `core/memmap/generators/ads.py`：首行与厂商一致、`#define <窗口>_ADDRESS`、`AlignExpr(ImageLimit(前一个), 对齐)`、`*(.name)` 选择器、每窗口一行 `;窗口名`、界限区域集中放在加载区域末尾、栈区域 `EMPTY`、保留区域 `EMPTY 0x0 {}` 并带注释、不写时间戳、`
` 行尾
- [x] 3.2 同样的计划得到逐字节相同的输出（测试比对 SHA-256 与写盘后的字节）
- [x] 3.3 保留区域选项关闭后文件里没有保留区域和那段注释；注释写明 `startup.c` 不引用时可关闭（选项本身见 1.3）
- [x] 3.4 测试：合成计划的输出逐行断言（含界限、栈、保留区域）；选项关闭；没有界限需求时不写界限区域；往返：`parse_scatter` 读回的区域名与顺序、选择器、窗口基址与跟随关系与计划一致；用出厂数据和芯片库 THA6206 存储做完整计划，所有出厂区域都在、能读回、不被拒绝

## 4. 自检

- [x] 4.1 `core/memmap/linkfile.py`：`self_check(path, …)` 与 `self_check_text(text, …)`（未写盘时检查临时副本）把生成物交给 `run_check`，返回 `SelfCheck`（`missing_symbols`、`unplaced`、`clean`、说明文字）
- [x] 4.2 验收测试（合成工程：Can 源码、MemMap 头、`startup.c`）：完整配置的生成物没有"链接符号缺失"和"没有区域接收的段"；关闭保留选项后自检报出 `PRIVATE_DATA_CORE2` 缺失；有未放置段时自检报出该段
- [x] 4.3 `SELF_CHECK_NOTE` 写明自检只证明生成器与检查器一致，不证明能链接；界面显示它（第 6 节）

## 5. 写文件

- [x] 5.1 `target_path(project_dir, "ads")` = `IntegrationProject/linkedFile/Ads/scatter.scat`；`write_linker_file`：同目录临时文件 → 旧文件复制为 `.bak` → 改名到位；失败抛 `LinkFileError`，旧文件不变，不留临时文件
- [x] 5.2 `preview(path, text)`：纯函数，给出路径、是否覆盖、备份路径、UTF-8 字节数、内容是否与现有文件相同；`prepare_generation` 只计划和生成文本、不写；取消即不调用写函数
- [x] 5.3 测试 `tests/core/test_linkfile_write.py`：新文件、备份、改名失败与临时文件创建失败时旧文件不变且无残留、取消后目录与之前完全相同、两次生成写出的字节相同

## 6. 界面

- [x] 6.1 "配置"页签新增"编译器"下拉、"为芯片没有的核写保留区域"勾选（默认开，随配置保存）与"生成链接文件…"按钮；不可用的编译器置灰，提示里写明原因
- [x] 6.2 生成前：有拒绝原因时逐条列出、不预览不写；否则 `GenerationPreviewDialog` 显示写入路径、新建/替换（备份名）/内容相同、字节数、区域统计、警告和文件全文，"写入"才写；生成后显示自检结果（`linkfile.self_check_result`：用扫描结果和检查器自己的读取器，不重新扫源码）与"不能证明能链接"的说明；"打开所在目录"
- [x] 6.3 UI 测试（offscreen）：`tests/ui/test_memory_map_generate_tab.py`：下拉状态、保留选项保存、拒绝显示原因、预览确认与取消、备份与内容相同、写入失败、生成后自检结果；快速自检与完整自检结论一致（`tests/core/test_linkfile_write.py`）；相关 217 个通过（2026-11-03，用户运行）

## 7. 对照与验证

- [x] 7.1 ~~与厂商 `LinkerAdsPf.scat` 对照~~：由 `update-linker-generator-authority` 撤销。用户定位生成器是权威，厂商脚本只是可选导入源，不作为验收条件（见 design.md D7）
- [ ] 7.2 全量测试（SC300 的两个已知失败除外）；`openspec validate add-linker-file-generation --strict`
- [ ] 7.3 用户在 THA6206 工程上生成，并在 ADS 编译器里实际链接一次，给出结果（工具外，需要用户）
