## 1. 解析器

- [x] 1.1 顶层 `v:lst` 的 `MAX` 为 XPath 时保存 `upper_multiplicity_expr`；子容器 `v:lst` 有两段循环，先执行的那段也补上保存（否则 `AdcHwUnit` 等拿不到表达式）
- [x] 1.2 参数保存静态默认值（`static_default`），表达式算不出时退回它
- [x] 1.3 `XdmExpressionResolver.resolve_expression` 去掉包住整个表达式的多余括号；键名与 `ecu:get` 一样先精确、再忽略大小写匹配

## 2. 按芯片重算

- [x] 2.1 新函数 `apply_chip_expressions(module_def, resources)`：重算默认值（按类型转换）、枚举范围、最大个数；返回改动数
- [x] 2.2 `WorkspaceProject.load_ecu_resources` 末尾对所有已加载模块调用；添加模块后也调用
- [x] 2.3 换芯片后配置面板、树的显示随之刷新（已有 `chip_changed` → `_refresh_config_views` 路径，核对即可）

## 3. 测试

- [x] 3.1 单元测试：默认值、范围、最大个数按资源算出；换资源后重算；算不出时退回静态默认值或不限；类型转换
- [x] 3.2 厂商 xdm + THA6412 资源：打开工程后 `Adc` 硬件单元上限为 12、`Dma` 通道上限为 128（THA610X 为 4 和 48）；超出时添加被拒、校验报错
- [x] 3.3 已有配置值在重算前后不变

## 4. 验证

- [x] 4.1 全量测试通过（1291 passed, 5 skipped）
- [x] 4.2 厂商示例工程（THA6412、THA6206、THA610X）改动前后生成结果对比：198 个生成文件逐字节相同（改动前跑两次也相同，结果稳定）。导入后按芯片算出的默认值 54/39 个、最大个数 28/24 个；示例配置里有 52/49 个未配置、默认值来自芯片的参数，但这些参数没有体现到生成结果里
