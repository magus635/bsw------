## Why

EB tresos 的模块定义可以给容器、列表、参数和引用写启用条件：`<a:da name="ENABLE" type="XPath" expr="..."/>`。条件为假时，EB 认为这一项不属于当前配置：生成代码时模板看不到它，导出 EPC 时也不写出。但它在 XDM 里的数据会保留，条件重新为真时恢复。

本工具解析定义时没有读取 `ENABLE`，这些项会照常参与生成和导出。用 T2 项目（`Os_THA6_ASR21` 定义、SC1 配置）对照 EB 自己的输出：

- 定义规定 `OsTaskTimingProtection` 只在 `OsScalabilityClass` 为 SC2 或 SC4 时启用。T2 是 SC1，EB 忽略了 Task0、Task1 的时间保护，本工具却生成了时间保护数据。受影响的文件有 `Os_timingprotection_Lcfg.c`、`Os_timingprotection_Cfg.h`、`Os_kernel_Cfg.h`、`Os_context_Lcfg.c`，例如 `TOTAL_TPUSED_NUM` EB 为 0，本工具为 2。
- 导出的 EPC 里多出 `OsTaskTimingProtection_0` 下的参数，EB 的 EPC 没有。
- `Os_THA6_ASR21` 定义里有 44 处这样的条件：内存保护、时间保护、访问检查随扩展等级变化；`OsResourceCoreRef` 与 `OsResourceLinkedResourceRef` 随资源属性互斥；`MemoryRegion`、`MemoryBlock` 等随 `OsResourceSubderivative` 变化。其他 EB 插件也普遍使用。

## What Changes

- **定义解析**：读取 `v:ctr`、`v:lst`、`v:chc`、`v:var`、`v:ref` 上的 XPath `ENABLE`，保存表达式，并按 `true`/`false` 属性映射结果（`true="false" false="true"` 表示表达式为真时关闭）。`v:lst` 上的条件作用于整个列表，`v:ctr` 等上的条件作用于该项本身。
  - 定义里固定的 `ENABLE` 值（如 `value="false"`）不是条件：它只是新建可选项时的初始状态，实际状态由值文件记录，XDM 导入时已经处理。
- **生成**：项目的所有模块都载入配置树以后、渲染模板之前，按文档顺序自上而下计算每个带条件的节点，上下文为该节点本身，与 EB 相同。条件为假的节点连同子树从配置树中移除，模板里 `node:exists`、`count`、`LOOP` 等都看不到它。已移除子树里的条件不再计算。
- **EPC 导出**：条件为假的项不写入导出的 EPC，与 EB 的导出一致。
- **数据保留**：项目保存的 `ConfigValue/*.arxml` 和导入的 XDM 数据不删除、不改动。条件重新为真时，这些值照常参与生成和导出。
- **无法计算的条件**：表达式报错或用到未实现的函数时，该项按"启用"处理，即保持当前行为，并在生成结果里给出警告，写明节点路径和表达式，每个表达式只报一次。
- **增量生成**：生成器指纹加入版本号，升级后第一次生成会重新生成所有模块，避免沿用按旧规则生成的结果。

## Impact

- Affected specs: `definition-enable-conditions`（新增能力）
- Affected code:
  - `autosar_configurator/core/model/definition_model.py`：容器、参数、引用定义增加 `enable_expr`，容器定义另加列表级的 `list_enable_expr`
  - `autosar_configurator/core/parser/ecuc_def_parser.py`：读取 `ENABLE`
  - `autosar_configurator/generator/eb/`：新增启用条件计算，在 `renderer` 载入模块后、渲染前执行；生成器指纹版本
  - `autosar_configurator/core/serializer/ecuc_serializer.py` 与导出 EPC 的 UI 控制器：导出时排除关闭的项
  - 测试 `tests/core/`、`tests/generator/`
- 兼容性：
  - 定义里没有 `ENABLE` 的模块，生成和导出结果不变。
  - 有条件的模块（如 Os），生成代码和导出的 EPC 会变化，向 EB 的输出靠拢。
- **不在本变更范围内**：
  - 界面上把关闭的项显示为灰色或隐藏（后续单独提案）。
  - `EDITABLE`、`INVALID`、`VISIBLE` 等其他 XPath 属性。
  - 多重性校验对关闭项的处理。
