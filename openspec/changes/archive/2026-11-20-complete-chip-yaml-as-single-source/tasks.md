## 1. 界面约束同源（D1）
- [x] 1.1 抽出"芯片可选列表"函数（芯片库 ∪ 项目 `chips/` ∪ properties 文件名），项目属性下拉框与 `ChipConstraintService` 共用
- [x] 1.2 `ChipConstraintService`：有项目时约束取自 `project.ecu_resources`，没有项目时保留现有 properties 扫描
- [x] 1.3 约束更新时机与 `load_ecu_resources` 对齐（新建、打开、导入、加模块、换芯片）
- [x] 1.4 测试：`test_import_project` 上每颗芯片改动前的约束全部保留且值不变（新增只来自 build 配置文件）；只有芯片 YAML 的项目，`ecu:get` 的 `MAX`、`ecu:list` 的 `RANGE` 能从 YAML 取到

## 2. 芯片选择器（D2）
- [x] 2.1 芯片 YAML 的 `selectors` 段：加载、导出、校验（键为 `<模块>.<参数名>`，值为字符串）
- [x] 2.2 `EcucDefParser`：选择器参数的枚举值 = 定义原有值 ∪ 芯片库声明的值；不改 `DEFAULT`
- [x] 2.3 诊断：用户配置的选择器取值与所选芯片声明不符时警告，不改配置
- [x] 2.4 设计器：在 ECU 资源页旁提供选择器编辑（模块.参数 → 值）
- [x] 2.5 内置芯片 YAML 补 `selectors`：Resource 取值按定义；Os 取值 `Os_THA610X` / `Os_THA6206` / `Os_THA6412`（SC300 尚无芯片 YAML）
- [x] 2.6 测试：新芯片只在 YAML 声明选择器即可出现在枚举里；原有值保留；不符时有警告；`DEFAULT` 不变

## 3. 以 `ecu_resources` 为准（D3）
- [x] 3.1 映射表（核数、可用核、主核）与比较函数，`ecu_resources` 缺对应键时不比较
- [x] 3.2 设计器预览页与 ECU 资源页显示不一致；"用 ECU 资源覆盖表单"
- [x] 3.3 测试：不一致被提示；覆盖后表单与 `ecu_resources` 一致；缺键时不提示；`OsResource.MasterCore` 按编号比较

## 4. 版本与校验和（D4）
- [x] 4.1 规范化内容的 SHA-256（基于解析后的数据，去掉 `checksum` 字段）；设计器保存时写入
- [x] 4.2 加载时校验和不符：标记"已被修改"并提示，仍加载
- [x] 4.3 项目文件记录 `chip_data: {name, resource_version, checksum}`；打开时比较项目副本与记录、项目副本与芯片库
- [x] 4.4 测试：手改 YAML 后加载被发现；项目副本被改被发现；芯片库新版本被提示；无 `checksum` 的旧 YAML 照常加载

## 5. 文档与验证
- [x] 5.1 `doc/chip_ecu_resources.md`：`selectors`、一致性规则、校验和与项目记录、交付给用户的流程
- [x] 5.2 `python -m pytest tests -q`（排除已知卡死的 `tests/ui/test_davinci_integration.py`）；生成结果与指纹不变
- [x] 5.3 `openspec validate complete-chip-yaml-as-single-source --strict`
