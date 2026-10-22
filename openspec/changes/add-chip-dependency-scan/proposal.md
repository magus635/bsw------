## Why

预计每年新增 2 颗芯片，EB tresos 仍是正式的生产工具，Os 插件、MCAL、内核和 SDK 都由我们维护。目前加一颗新芯片要改哪些地方，只能靠人工搜索。T1 的复盘表明，这种做法既漏又看不全：

- 芯片名判断有好几种写法。`Os.xdm` 和 Os 模板里有 30 处 `= 'Os_THA6206'` 这类比较；Port 模板里还有 `contains(…, 'THA610X')`、`!= 'THA6206_LFBGA292'`，按 `=` 搜索时漏掉了。
- 有些芯片相关的内容不带芯片名，按名字搜不到。`[!IF]` 的 `ELSE` 分支默认就是“另一颗芯片”（`Os_isr_Lcfg.c` 的 GIC 地址表就是这样，新芯片会悄悄沿用 6412 的地址）；GIC 地址表里写死了地址常量。（`scatter.scat` 中的 6206 内存地址只出现在注释里，实际区域来自 MemoryRegion 配置；整个文件被 `= 'Os_THA6206'` 判断包住。）
- 两套资源文件的查找方式可能对不上。EB 按 `plugin.xml` 中 `ecuresource` 的登记来找资源文件，我们的工具按文件名找。新芯片的 properties 文件只要命名不规范，两边就会加载不同的文件。
- 内核、SDK、MCAL 的 C 代码里还有大约 800 处 `#if defined(THA6_THA6412)` 这类芯片宏，都不在项目目录里。

阶段 0 先做一个**只读**的“芯片依赖扫描”，输出新增芯片时的检查清单。它不修改任何插件、模板或代码，也为后续的重构摸清实际范围。

## What Changes

- 新增 **芯片依赖扫描**（菜单“Tools → 芯片依赖扫描…”），按类别输出发现项，每条都带文件（POSIX 相对路径）、行号、原文和涉及的芯片：
  1. **芯片名判断**：xdm 和模板中 XPath 的 `=`、`!=`、`contains`、`starts-with` 对芯片名的比较；C、汇编和链接脚本中 `#if`、`#ifdef`、`#ifndef`、`#elif` 对芯片宏的判断。
  2. **隐含默认分支**：带有 `ELSE`（模板）或 `#else`（C）的芯片判断。新芯片会走进这个分支，需要人工确认是否适用。
  3. **疑似写死的芯片数值**：模板和链接脚本中像地址的十六进制常量（不小于 `0x10000`），标为“需人工确认”。
  4. **资源覆盖**：已加载模块中每个芯片选择器参数（如 `OsResourceSubderivative`），逐个检查它的每个可选值是否满足以下条件：
     - 有芯片库中的芯片声明了它；
     - 在 `plugin.xml` 中登记了资源文件，且该文件存在；
     - 和我们的工具按文件名匹配到的是同一个文件；
     - 模块引用的 `ecu:get`/`ecu:list` 键都有定义。
- 识别哪些写法算芯片名的规则见 `design.md`。规则会从芯片库自动推出，用户也可以补充关键字。
- 扫描范围：
  - 已加载模块的定义文件和模板；
  - 用户额外添加的目录（EB 插件、内核、SDK、MCAL）。这些目录以相对项目的 POSIX 路径保存在项目文件中，团队可以共用。
- 结果可以按芯片和类别筛选，也可以导出为 Markdown 检查清单（每条一个 `- [ ]`），方便逐项跟踪。
- 扫描在后台运行，可以取消，结果的排序是确定的。扫描时不会修改项目配置，也不会修改任何被扫描的文件。

## Impact

- Affected specs: 新增 `chip-dependency-scan`。
- Affected code:
  - 新增 `autosar_configurator/core/hardware/chip_dependency_scan.py`：扫描逻辑，与界面无关。它复用 `ecu_resource_diagnostics` 中的 `_module_sources`、`collect_referenced_keys`，以及 `resource_file_matches_chip`。
  - 新增 `autosar_configurator/ui/dialogs/chip_dependency_scan_dialog.py`，并在 `davinci_main_window.py` 中添加菜单项。
  - `autosar_configurator/core/workspace_manager.py`：项目中新增 `chip_scan_dirs` 和 `chip_scan_keywords` 两个字段的保存和读取。旧项目没有这两个字段时为空列表。
  - 测试：新增 `tests/core/test_chip_dependency_scan.py` 和 `tests/ui/test_chip_dependency_scan_dialog.py`。
- 兼容性：生成结果、指纹和 EPC 导出都不变。项目文件只多一个可选字段。
- 不在本变更内：修改任何插件、模板或 C 代码；新芯片向导；导出 EB 文件。这些属于后续阶段。
