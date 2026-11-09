# project-file — Delta

## ADDED Requirements

### Requirement: Format 8 Directory Table

`.dpa` format 8 SHALL 含 `directories` 目录表（`config`、`base`、`templates`、`gen`、`gen_layout`、`chips`、`integration`、`system`、`history`），所有代码 SHALL 通过目录表解析工程目录，不得写死目录名；旧格式的默认值表（`ConfigValue`、`templates`、`generateCode`、`Def/plugins`）集中在一处。新工程的默认目录名为 `config/`、`config/base/`、`templates/`、`gen/`（平铺）、`chips/`、`integration/`、`system/`、`.history/`。

#### Scenario: 新建 format 8 工程

- **WHEN** 用户新建工程
- **THEN** `.dpa` 写入 `format_version: 8` 和完整的 `directories` 表，活配置保存在 `config/<Module>.arxml`

#### Scenario: 代码中没有写死的旧目录名

- **WHEN** 在仓库源码中搜索 `"ConfigValue"`、`"generateCode"`、`"Def/plugins"`
- **THEN** 只在旧格式默认值表中出现

### Requirement: Project Root Is The Dpa Directory

工程根目录 SHALL 一律取 `.dpa` 所在目录。生成器 SHALL NOT 再从模板目录往上查找 `Def`/`Define` 目录来推断工程根。

#### Scenario: 模板目录不在常规位置

- **WHEN** 工程的模板目录位于自定义路径，其上层没有 `Def` 目录
- **THEN** 生成器使用 `.dpa` 所在目录作为工程根，资源和芯片数据按目录表解析

### Requirement: Active Module List

format 8 的 `modules` SHALL 是已激活模块的权威清单，每项记录 `name`、`definition`（定义的 AUTOSAR 路径）、`library`、`config_path`、`pre_unlocked`、`package_record` 和基线快照哈希；模块通过 `definition` 在 `module_libraries` 中定位，不再保存定义文件路径。

#### Scenario: format 8 工程往返

- **WHEN** 一个 format 8 工程被保存后重新打开
- **THEN** `modules`、`module_libraries`、`directories` 和每个模块的 `pre_unlocked` 与保存前一致

### Requirement: Legacy Format Compatibility

format ≤7 的工程 SHALL 按原逻辑打开（`def_path`、`ConfigValue/`、`templates/`、`generateCode/`），SHALL NOT 应用 PRE 或基线合并，保存时 SHALL 仍写 format 7；目录表取旧目录名作为默认值。

#### Scenario: 旧工程生成结果不变

- **WHEN** 打开现有旧工程（含 EB copy/link 导入的工程，例如 `test_project_relocation`、用户的 T1/T2 工程）并生成代码
- **THEN** 生成结果与改造前逐字节一致，生成器指纹不变

#### Scenario: 旧工程保存后格式不变

- **WHEN** 一个 format 7 工程被打开后保存
- **THEN** `.dpa` 仍为 `format_version: 7`，不出现 format 8 字段

### Requirement: EB Import Produces Format 8 Project

EB 工程导入 SHALL 生成 format 8 工程：插件目录登记为 `module_libraries` 中的 `eb-plugins` 库（copy 模式先复制到工程内的库目录，link 模式直接写外部路径），`.epc`/`.xdm` 中的值导入 `config/`，SHALL NOT 复制模板，SHALL NOT 创建符号链接；插件的 `PreConfiguration` SHALL 按基线层处理，不再跳过。导入后的 Active 按“旧工程迁移”处理，PRE 带来的改动先预演再确认。

#### Scenario: link 模式导入

- **WHEN** 用户以 link 模式导入一个 EB 工程
- **THEN** 工程目录中没有符号链接，`module_libraries` 中记录 EB 插件目录的路径

#### Scenario: 导入时处理 McuPreConfiguration

- **WHEN** 导入的 EB 工程含 Mcu 插件及其 `McuPreConfiguration.xdm`
- **THEN** 预设值进入 Mcu 的基线，与导入值不同的条目出现在预演报告中
