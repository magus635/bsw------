## 1. 扫描核心（`core/hardware/chip_dependency_scan.py`）
- [x] 1.1 关键字推导：完整名称、型号片段、族前缀、用户补充；单元测试覆盖 `THA610X`、`THA6XXX` 命中，`THA6_` 与 `LFBGA292` 不作为型号
- [x] 1.2 XPath 芯片名判断：从 xdm 的 XPath 属性和模板指令中识别 `=`、`!=`、`contains`、`starts-with`，记录文件、行号、原文、涉及芯片
- [x] 1.3 C 预处理判断：`#if/#ifdef/#ifndef/#elif`，跳过注释
- [x] 1.4 隐含默认分支：模板 IF 链与 C `#if` 链的栈跟踪
- [x] 1.5 疑似写死数值：模板中指令外的 ≥ `0x10000` 十六进制常量，每文件最多 50 行
- [x] 1.6 资源覆盖：选择器可选值 × (芯片库声明、`plugin.xml` 登记与文件存在、文件名匹配是否一致、`ecu:get/list` 键齐全)
- [x] 1.7 文件过滤、2 MB 上限、取消回调、确定性排序
- [x] 1.8 Markdown 检查清单导出

## 2. 项目保存
- [x] 2.1 `chip_scan_dirs`、`chip_scan_keywords` 读写（POSIX 相对路径），旧项目为空
- [x] 2.2 运行 `python -m pytest tests/core/test_parser_serializer.py tests/core/test_command.py -q`

## 3. 界面
- [x] 3.1 `ui/dialogs/chip_dependency_scan_dialog.py`：目录与关键字设置、后台扫描与进度/取消、按类别→文件→行的树、按芯片与类别筛选、导出
- [x] 3.2 菜单 “Tools → 芯片依赖扫描…”
- [x] 3.3 UI 测试

## 4. 验证
- [x] 4.1 合成样例测试（Os/Port 风格的 xdm、模板、C 文件、plugin.xml）
- [x] 4.2 在 T1 副本上运行（加上 Os 插件、内核、SDK 目录），核对：Port 的 `contains(…,'THA610X')` 被发现、`Os_isr_Lcfg.c` GIC 表的 ELSE 被报为隐含默认分支、`scatter.scat` 的整文件 6206 判断被报（其中地址只在注释里，实际区域来自 MemoryRegion 配置，不报）、GIC 表地址被报为疑似写死、`Os_isr_hal.c:215` 的 `#ifdef OS_THA6206` 被发现，并记录各类数量
- [x] 4.3 确认扫描后项目配置与被扫描文件均未改变；全量测试通过
