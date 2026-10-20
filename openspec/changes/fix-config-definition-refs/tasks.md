## 1. 排查

- [x] 1.1 列出按 `definition_ref` 匹配定义的代码（`get_container_def`、overlay、ENABLE 条件、校验、界面），确认改写为绝对路径后仍能匹配；需要时改为按模块相对路径匹配（`same_definition`，见 design.md）
- [x] 1.2 记录基线：T1、T2 各配置文件中相对路径、错误前缀、通用 `DEST` 的条数；T1、T2 全模块生成结果

## 2. 定义路径与换算

- [x] 2.1 `EcucModuleDef.ar_path`；`ecuc_def_parser` 解析 XDM 与 ARXML 时记录实际路径
- [x] 2.2 新增 `core/model/definition_refs.py`：`absolute_ref`、`needs_repair`、`same_definition` 和各类 `DEST`
- [x] 2.3 单元测试：相对路径、`/AUTOSAR/EcucDefs` 前缀、已正确的路径、模块本身、空路径

## 3. 新建与加载

- [x] 3.1 `ConfigurationManager` 新建容器实例、参数时写绝对路径和具体 `DEST`；保存前统一补全，覆盖其他入口新建的值；模块配置用 `ar_path`
- [x] 3.2 加载模块配置后纠正已有值，INFO 日志报告条数
- [x] 3.3 测试：新建布尔、整数、枚举参数和子容器后保存，`DEFINITION-REF` 与 `DEST` 正确；加载含相对路径与通用 `DEST` 的文件后保存，全部纠正；正确的 EB 引用不变

## 4. 回归

- [x] 4.1 T1、T2 加载后保存到临时目录：相对路径、错误前缀、通用 `DEST` 为 0；其余变化只有枚举值改用 TEXTUAL 标签、空值参数不再写 `<VALUE></VALUE>`（已有行为）
- [x] 4.2 T1、T2 全模块生成结果前后一致（改动前的代码与改动后的代码；纠正后的文件重新加载后生成）
- [x] 4.3 全部测试通过
