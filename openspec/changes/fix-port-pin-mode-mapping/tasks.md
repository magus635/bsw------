## 1. 规则与选项

- [ ] 1.1 `port.yaml`：删掉 `PortPinMode` 参数；`ui_config.options` 里删掉"Default Mode"，保留"Default Direction"
- [ ] 1.2 测试：任意芯片的 Port 映射没有 `PortPinMode` 和 `PortPinInitialMode` 的动作；`P10_13` 仍是 `PortPinId = 173`
- [ ] 1.3 测试：向导 Port 页的选项列表里没有默认模式（读 `get_default_rule_loader().get_rule("Port").ui_config.options`）

## 2. 配置模板

- [ ] 2.1 先看清模板怎么被使用：读 `template_manager.py` 里加载 `data/templates` 的部分，以及是否有测试引用这两个文件
- [ ] 2.2 `port_gpio_input.yaml` 去掉 `fixed.PortPinMode`；`port_gpio_output.yaml` 去掉 `adjustable` 里的 `PortPinMode` 和 `fixed` 里对应项（若有）
- [ ] 2.3 测试：加载两个模板，参数里没有 `PortPinMode`

## 3. 对照厂商定义的测试

- [ ] 3.1 新增 `tests/core/test_port_rule_definition.py`：用 `EcucDefParser().parse_module_def_file` 读 `Port.xdm`，对 `port.yaml` 里每个参数检查：存在；定义列出了取值时，值（含 `ui_options` 里的全部选项和 `default`）都在其中
- [ ] 3.2 确认这个测试在修改前会因 `PortPinMode` 失败（先 `git stash` 规则文件的修改或临时还原一次，记录失败信息），修改后通过
- [ ] 3.3 在同一文件里加一条对 `PortPinInitialMode` 的说明性测试：规则不写它（解析出的取值列表为空，无法静态对照）

## 4. 文档与验证

- [ ] 4.1 `doc/Hardware_Mapping硬件映射使用说明.md` 里有四处要改：界面示意图里的"Default Mode"行（约 885 行）、`_option_default_mode` 示例（约 1016 行）、规则文件示例里的 `PortPinMode` 参数（约 1119–1123 行）和 `default_mode` 选项（约 1132 行）；`doc/THA6XXX_MC_AS440/` 下是厂商的资料，不改
- [ ] 4.2 全量测试通过（`QT_QPA_PLATFORM=offscreen python -m pytest tests -q`）

依赖与顺序：本变更依赖 `add-chip-ports-from-ecu-resources`（同改 `port.yaml`），在它实施并提交之后再开始；1、2、3 之间没有依赖，可以并行。
