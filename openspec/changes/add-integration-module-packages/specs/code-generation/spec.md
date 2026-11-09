# code-generation — Delta

## ADDED Requirements

### Requirement: Template Lookup From Overlay And Package

对 format 8 工程中来自模块包的模块，生成器 SHALL 按“工程覆盖层 `templates/<Module>/` → 包内模板目录”的顺序查找模板：覆盖层中的同名文件优先，其余文件取自包内模板目录。format 8 工程保存时 SHALL NOT 把包内模板复制到工程中。生成器指纹 SHALL 只按模板内容计算，模板来源路径的变化不得改变指纹。format ≤7 工程的模板查找保持不变。

#### Scenario: 工程覆盖层中的修改不被覆盖

- **WHEN** 用户修改 `templates/<Module>/` 中的一个模板后保存工程
- **THEN** 修改后的文件不被包内模板覆盖
- **AND** 生成时使用修改后的模板，其余模板取自包内模板目录

#### Scenario: 模板来源变化不改变指纹

- **WHEN** 同一份模板内容从工程内副本改为直接取自包内模板目录
- **THEN** 生成器指纹不变
