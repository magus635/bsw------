## MODIFIED Requirements

### Requirement: Template Lookup From Overlay And Package

对 format 8 工程中来自模块包的模块，生成器 SHALL 按“变体工程覆盖层 `templates/<pkg_dir_name>/`（当 `pkg_dir_name` 存在且不同于 `<Module>` 时）→ 通用工程覆盖层 `templates/<Module>/` → 包内模板目录”的顺序查找模板及其 `INCLUDE` 宏搜索目录：高优先级层中的同名文件优先，其余文件取自低优先级层。format 8 工程保存时 SHALL NOT 把包内模板复制到工程中。生成器指纹 SHALL 只按模板内容计算，模板来源路径的变化不得改变指纹。format ≤7 工程与非变体模块的模板查找保持不变。

#### Scenario: 工程覆盖层中的修改不被覆盖

- **WHEN** 用户修改 `templates/<Module>/` 中的一个模板后保存工程
- **THEN** 修改后的文件不被包内模板覆盖
- **AND** 生成时使用修改后的模板，其余模板取自包内模板目录

#### Scenario: 模板来源变化不改变指纹

- **WHEN** 同一份模板内容从工程内副本改为直接取自包内模板目录
- **THEN** 生成器指纹不变

#### Scenario: 变体级工程覆盖目录优先于通用模块覆盖目录

- **WHEN** format 8 工程中的 `CanTrcv` 绑定到包目录 `CanTrcv_Tle9255`，且工程同时存在 `templates/CanTrcv_Tle9255/CanTrcv_Cfg.h` 和 `templates/CanTrcv/CanTrcv_Cfg.h`
- **THEN** 生成器与 `INCLUDE` 宏解析优先使用 `templates/CanTrcv_Tle9255/CanTrcv_Cfg.h`，未在变体覆盖目录出现的模板再依次回退到 `templates/CanTrcv/` 与包内模板目录

