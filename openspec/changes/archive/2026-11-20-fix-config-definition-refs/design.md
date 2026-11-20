## Context

AUTOSAR ECUC 值文件中，每个容器、参数和引用的 `DEFINITION-REF` 是定义元素的绝对路径（`/<包>/<模块>/<容器>/.../<参数>`），`DEST` 是定义元素的类型。EB tresos 按这两项把值对应到已加载的定义上。

本工具的现状：

| 来源 | `DEFINITION-REF` | `DEST` |
|---|---|---|
| 从 EB 文件导入的值 | 原文保留，正确 | 原文保留，正确 |
| 工具新建的顶层容器 | `/AUTOSAR/EcucDefs/<Module>/<Container>` | `ECUC-PARAM-CONF-CONTAINER-DEF` |
| 工具新建的子容器、参数、引用 | `<Container>/.../<Name>`（相对） | 参数为通用 `ECUC-PARAMETER-DEF` |
| 工具新建的模块配置 | `/AUTOSAR/EcucDefs/<Module>` | `ECUC-MODULE-DEF` |

T1 中 XDM 定义的实际路径：Can、Dem、EcuC、Intc、Mcu、Port、Resource 为 `/THA6_AS440_FuSa/<Module>`，Os 为 `/THA6_ASR21/Os`；Arti 定义（`Arti_ParamDef.arxml`）为 `/AUTOSAR/EcucDefs/Arti`。

## Goals / Non-Goals

- Goals：工具写出的每个 `DEFINITION-REF` 都是定义元素的实际绝对路径，`DEST` 是定义元素的具体类型；已写坏的配置在下次保存时被纠正。
- Non-Goals：改变定义解析器内部的定义路径（生成器、界面、ENABLE 条件按现有形式匹配）；改变代码生成。

## Decisions

### 模块定义的实际路径

解析定义时记录 `EcucModuleDef.ar_path`：

- XDM：`/<AR-PACKAGE 名>/<MODULE-DEF 名>`，取自 `d:ctr type="AR-PACKAGE"` 与 `d:chc type="AR-ELEMENT" value="MODULE-DEF"`。
- ARXML：ECUC-MODULE-DEF 所在的 AR-PACKAGE 层级加模块名。
- 无法确定时回落为 `/AUTOSAR/EcucDefs/<Module>`（现有行为）。

### 换算函数

`definition_refs.absolute_ref(module_def, def_ref)`：

1. 求出相对于模块的路径 `rel`：
   - 不以 `/` 开头：`rel = def_ref`。
   - 以 `/` 开头：去掉第一个等于模块名的路径段及其之前的部分（`/AUTOSAR/EcucDefs/Can/CanConfigSet` → `CanConfigSet`；`/THA6_AS440_FuSa/Can/CanConfigSet` → `CanConfigSet`）；只有模块本身时 `rel` 为空。
2. 返回 `ar_path` 或 `ar_path + "/" + rel`。

`definition_refs.dest_of(module_def, rel)` 按 `rel` 在定义树中查找元素，返回其类型：

- 参数：`param_type.value`（`ECUC-BOOLEAN-PARAM-DEF` 等）
- 引用：`ECUC-REFERENCE-DEF`；CHOICE 引用为 `ECUC-CHOICE-REFERENCE-DEF`；外部引用等沿用定义中记录的类型
- 容器：`ECUC-PARAM-CONF-CONTAINER-DEF`；CHOICE 容器为 `ECUC-CHOICE-CONTAINER-DEF`
- 查不到时返回 `None`，保留原值

### 写入时机

- 新建：`ConfigurationManager` 新建容器实例、设置参数、设置引用时，用换算函数生成 `definition_ref`，并设置 `dest_type` / `def_dest_type`。
- 加载：模块配置加载完成后遍历一次，对路径不是绝对路径、前缀不是 `ar_path`、或 `DEST` 为通用值的项纠正，记录修复条数（INFO 日志）。纠正只改内存，下次保存写回。
- 序列化器不变：它已经写出值上的 `definition_ref` 和 `dest_type`。

### 导入 EB 文件的配置

从 EB 导入的值，前缀本来就是定义的实际路径，换算后不变；`DEST` 也已具体，不改。

### 实现时补充的改动

- **按定义匹配不再依赖路径形式**：新增 `definition_refs.same_definition`，按模块内的相对路径比较。实例与定义的相等比较都改用它，包括多重性计数（`config_manager`、树视图、快速配置向导）、`get_all_instances_of_def` 和依赖规则。从 EB 导入的实例路径是 `/THA6_ASR21/...`，原来用相等比较本来就匹配不上。
- **ENABLE 条件的定义查找**：`enable_conditions._definitions_by_ref` 改为按模块内的相对路径查找。原来 T2 的 311 个容器、582 个参数（都从 EB 导入）在这个索引里都查不到。纠正后，T1 原来按相对路径能查到的 378 个参数改成绝对路径后，仍然能查到。T1、T2 的生成结果前后一致。
- **XDM 的 `*_LABEL` 类型**：`INTEGER_LABEL`、`FLOAT_LABEL`、`STRING_LABEL` 按去掉 `_LABEL` 的类型解析。原来都落到 STRING，例如 `CommonPublishedInformation/ArMajorVersion`，而它在 AUTOSAR 标准定义中是 `INTEGER-PARAM-DEF`。
- **值元素的标签**：序列化器原本就根据 DEST 选择 `ECUC-NUMERICAL-PARAM-VALUE` 或 `ECUC-TEXTUAL-PARAM-VALUE`。DEST 补全之后，可选值为数字的枚举参数（如 Os 的 `MemoryBlockAlign`）改为写 TEXTUAL，符合 AUTOSAR 对枚举值的规定。
- **空字符串 `definition_ref`**（没有路径的定义）保持为空，不换算成模块路径。

## Risks / Trade-offs

- 内部按 `definition_ref` 匹配的代码（`get_container_def`、overlay、ENABLE 条件）若用相等比较，改写后的绝对路径可能匹配不上。缓解：实现前排查这些匹配点（现有多数用 `endswith`），用 T1、T2 全模块生成前后逐文件比对验证，并跑全部测试。
- 配置文件出现成批差异：预期之内，提交说明中写明。
