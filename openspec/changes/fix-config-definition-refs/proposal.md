## Why

工具保存的模块配置（`ConfigValue/*_Config.arxml`）中，凡是在工具里新建的参数值、引用值和容器，`DEFINITION-REF` 都写得不对，EB tresos 等按定义路径解析的工具无法识别：

- 路径是相对路径。例如 T1 在界面勾选 `OsVendorArtiTraceTask` 后保存，写出的是 `OsOS/OsVendorArtiTraceTask`，而同一容器里从 EB 导入的值是 `/THA6_ASR21/Os/OsOS/OsUseArti`。
- 前缀写死为 `/AUTOSAR/EcucDefs/<Module>`。EB 的 XDM 定义实际所在的包是 `/<AR-PACKAGE>/<Module>`，例如 T1 的 Can、Mcu、Port 是 `/THA6_AS440_FuSa/...`，Os 是 `/THA6_ASR21/Os`。工具新建的模块配置连模块本身的 `DEFINITION-REF` 都是 `/AUTOSAR/EcucDefs/Can`。
- `DEST` 一律写通用的 `ECUC-PARAMETER-DEF`，不是 `ECUC-BOOLEAN-PARAM-DEF` 这类具体类型。

已写坏的文件：T1 有 8 个配置文件含相对路径，共约 1370 条（Os 614、Intc 523、Can 76、Dem 63、Adc 56，Resource、Port、Mcu 也有）；T2 的 Os_Config 有 584 条通用 `DEST`。工具自身按名字匹配，代码生成不受影响。

原因：

- 定义解析器（`core/parser/ecuc_def_parser.py`）只把顶层容器的定义路径改写为 `/AUTOSAR/EcucDefs/<Module>/<Container>`，容器内的参数、引用和子容器保留相对于模块的路径（`OsOS/OsUseArti`）。新建值时直接取这个路径。
- 新建值不记录定义类型，保存时 `DEST` 回落到通用值。

## What Changes

- **定义的实际路径**：解析定义时记录模块在定义文件中的实际路径（XDM：`/<AR-PACKAGE>/<Module>`；ARXML：AR-PACKAGE 层级），作为 `EcucModuleDef.ar_path`。
- **统一换算**：新增一个函数，把定义路径换算为配置文件中应写的绝对路径。前缀用模块定义的实际路径；相对路径接在前缀后；`/<其他包>/<Module>/...` 改为该前缀。
- **新建值写对**：`ConfigurationManager` 新建参数、引用、容器实例时，用上述函数生成 `DEFINITION-REF`，并按定义记录具体的 `DEST` 类型（参数类型、引用或 CHOICE 引用、容器或 CHOICE 容器）。新建模块配置的 `DEFINITION-REF` 用模块定义的实际路径。
- **修复已有文件**：加载配置时在内存中纠正相对路径、错误前缀和通用 `DEST`，日志报告修复条数；下次保存时写回。不主动写磁盘。
- 定义解析器内部的定义路径形式保持不变（生成器与界面的匹配依赖它），只在写入配置的值上做换算。

## Impact

- Affected specs: `config-definition-refs`（新增能力）
- Affected code:
  - `core/parser/ecuc_def_parser.py`：记录 `ar_path`
  - `core/model/definition_model.py`：`EcucModuleDef.ar_path`
  - `core/config_manager.py`：新建值的定义路径和 `DEST`
  - 配置加载处（`workspace_manager` / 模块管理器）：加载时纠正
  - 新增换算函数（`core/model/definition_refs.py`）
  - 按定义匹配的比较（`config_manager`、`configuration_model`、`rules/dependency_rules.py`、树视图、快速配置向导）与 ENABLE 条件的定义查找（`generator/eb/enable_conditions.py`）：改为不依赖路径形式
  - XDM `*_LABEL` 类型按对应的值类型解析
  - 测试 `tests/core/`
- 兼容性：
  - 保存的配置文件中，原先相对或前缀错误的 `DEFINITION-REF` 和通用 `DEST` 会被改写，文件会出现成批差异，这是预期的修复。其余内容不变。
  - 工具按名字匹配定义，加载、界面显示和代码生成不受影响；用 T1、T2 验证生成结果前后一致。
- 不在本变更范围内：定义解析器内部定义路径的规范化；`.epc` 导出（已按 EB 布局单独处理）。
