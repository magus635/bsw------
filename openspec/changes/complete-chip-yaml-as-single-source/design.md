## Context

- 三类数据：① 模块定义（xdm/ARXML，随插件版本）；② 芯片事实（每颗芯片一份，厂商维护，对用户只读）；③ 用户配置（项目）。`ecu:get('Module.Key')` 把 ① 与 ② 解耦。本变更的目标是让 ② 完全由芯片 YAML 承载。
- 界面约束：`ChipConstraintService._load_chip_constraints` 只读 `Def/plugins/*/resource/*.properties`；`DaVinciMainWindow._on_chip_constraints_changed` 与 `ProjectController.add_module_to_project` 把结果交给 `XdmExpressionResolver.set_constraints`。`EcucDefParser._parse_xdm_range` 在**解析定义时**求值 `RANGE` 表达式并写入 `param_def.literals`，静态 `RANGE`（`<a:v>…</a:v>`）直接作为枚举值。
- 选择器：`Resource.xdm` 的 `ResourceSubderivative`（容器内参数，取值即芯片名）；`Os.xdm` 的 `OsResourceSubderivative`（模块级 `v:var`，取值为 `Os_THA6206` / `Os_THA6412` / `Os_SC300`，与芯片名不同）。模板按选择器取值分支。

## Goals / Non-Goals

- Goals：只有芯片 YAML 的项目，界面约束与生成都完整；新增芯片不改定义文件；同一事实不出现两份不一致的数据；芯片数据的改动可被发现。
- Non-Goals：不自动改用户配置里的选择器取值；不做加密签名；不扩展带类型字段到 CAN/ADC/SPI 的完整映射。

## Decisions

### D1 界面约束取自 `project.ecu_resources`

`ChipConstraintService` 不再自行扫描 properties，改为：有项目时取 `project.ecu_resources`（已由 Resolver 合并 properties 与芯片 YAML，并在新建、打开、导入、加模块、换芯片时重算）；没有项目时退回现有的 properties 扫描。约束更新的时机与 `load_ecu_resources` 一致。

- 芯片可选列表：芯片库 ∪ 项目 `chips/` ∪ properties 文件名（与项目属性下拉框同一来源，抽成一个函数共用）。
- 验证：`test_import_project` 上，改动前的每个约束都在新路径中且值相同；新路径额外包含非 resource 目录下 `.properties`（build 配置，如 `bin.includes`）的键，这些键代码生成本来就读取。

备选（不采用）：让 `ChipConstraintService` 自己再读一遍芯片 YAML。会出现第三套合并逻辑，正是要消除的问题。

### D2 芯片 YAML 的 `selectors` 段

```yaml
name: THA6412_BGA516
selectors:
  Resource.ResourceSubderivative: THA6412_BGA516
  Os.OsResourceSubderivative: Os_THA6412
```

- 键是 `<模块>.<参数名>`（参数名在该模块定义里唯一时即可定位；容器内与模块级参数都支持）；值是标量字符串。
- 解析定义时，若参数名出现在芯片库任一芯片的 `selectors` 里，其枚举值 = 定义原有值 ∪ 芯片库全部芯片声明的值（保持定义原有顺序，新增值按芯片名排序追加）。原有值保留，避免旧项目里已选的值变成非法。
- 不修改 `DEFAULT`：默认值仍由定义决定，避免改变已有项目的生成结果。
- 选中芯片后，诊断检查用户配置里各选择器的取值：与芯片声明不同则警告（"Resource.ResourceSubderivative 配置为 X，所选芯片声明为 Y"）。不自动改用户配置——那是第 ③ 类数据，由用户决定。
- 为什么要显式声明而不是由芯片名推导：Os 的取值（`Os_THA6412`）与芯片名（`THA6412_BGA516`）命名规则不同，且 `Os_SC300` 这类取值无法从芯片名得出，推导就是猜。

### D3 以 `ecu_resources` 为准的一致性映射

一张映射表，首批只含含义明确的项：

| 带类型字段 | `ecu_resources` 键 |
|---|---|
| `metadata.cores.count` | `OsResource.NumOfCores`、`Resource.NumOfCores` |
| `metadata.cores.available` | `OsResource.AvailableCores`、`Resource.AvailableCores` |
| `metadata.cores.master` | `Resource.MasterCore` 的第一个元素（`OsResource.MasterCore` 是 `OS_CORE_ID_<n>` 写法，按编号比较） |

- 设计器在预览页与 ECU 资源页提示不一致；"用 ECU 资源覆盖表单"把表单字段改成 `ecu_resources` 的值。
- 只有当 `ecu_resources` 里存在对应键时才比较；没有该键时不提示（老芯片仍用表单字段）。
- 映射表声明在一处，后续扩展不改流程。

### D4 版本与校验和

- `checksum`：对芯片的规范化内容（去掉 `checksum` 字段后，按导出器的确定性输出）计算 SHA-256，写为 `sha256:<hex>`。设计器保存时计算并写入。
- 加载时若 YAML 带 `checksum` 而与内容不符，标记该芯片"内容已被修改"（只提示，仍加载）。
- 项目文件记录 `chip_data: {name, resource_version, checksum}`（相对信息，无路径）。打开项目时：
  - 项目副本校验和与记录不符 → 提示"项目内芯片数据已被修改"；
  - 芯片库同名芯片的校验和与项目副本不同 → 提示"芯片库有不同版本，可在项目属性里 Update from Library"。
- 只为发现改动，不防恶意篡改；不做签名。

## Risks / Trade-offs

- **已解析定义不随芯片切换刷新。** `RANGE` 在解析时求值；切换芯片后，已加载模块的枚举值不变，直到重新加载模块或项目。这是现有行为，本变更只保证"重新解析时用的是新数据"，并在状态栏提示需要重新加载。是否做自动重新解析留作后续。
- **选择器取值的并集会变大。** 芯片多了以后，选择器可选值会包含所有芯片；用户可能选到与所选芯片不符的值。由 D2 的诊断警告兜底。
- **校验和对格式敏感。** 规范化依赖导出器的确定性输出；导出器格式变化会让旧校验和失效。缓解：校验和计算基于解析后的数据（规范化 JSON），而不是 YAML 文本。
- **约束来源变化可能改变已有项目的界面行为。** 用 `test_import_project` 的逐键对比兜底；芯片 YAML 有 `ecu_resources` 时，约束会多出或改变——这是预期效果。

## Migration Plan

1. 先做 D1（约束同源），对比测试通过后再做其他项。
2. D2 先只做"可选值并集 + 诊断"，内置芯片 YAML 补上 `selectors`（三颗芯片的 Resource 选择器取值与定义一致；Os 取值按 T1 的 `Os.xdm` 填写，需厂商确认）。
3. D3、D4 相互独立。
4. 回滚：各项都只是新增字段或替换数据来源，移除即可恢复。

## Open Questions

1. 已确认：`THA610X_LFBGA180 → Os_THA610X`，`Os_SC300` 对应芯片 SC300；`THA6206_LFBGA292 → Os_THA6206`、`THA6412_BGA516 → Os_THA6412` 按命名规则填写。SC300 尚无芯片 YAML，是否加入芯片库待定。
2. 切换芯片后是否自动重新解析已加载模块的定义（目前不做）。
