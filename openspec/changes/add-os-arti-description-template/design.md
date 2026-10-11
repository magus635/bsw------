## Context

- 现有 ORTI 模板 `doc/ARTI/Os_Arti.arxml`（文件头为 `Os_Trace.ORTI`，KOIL 2.2）是 OS 生成器对调试器描述内核的唯一来源，包含内核变量名、ID 规则和 Os 配置路径。
- ARTI 定义 `definitions/Arti/Arti_ParamDef.arxml` 已入库，并通过 XSD 校验。
- EB tresos 的 `TemplateBasedCodeGenerator` 会渲染模板目录（如 `generate_PB/`）下除 `.m` 以外的所有文件，输出名等于模板文件名（见 `test_import_project/Def/plugins/*/plugin.xml`）。
- 本工具 `generator.py:_discover_template_types` 只接受 `<Module>_*.c`、`<Module>_*.h`、`*.tpl`（`generator.py:368-373`），`.arxml` 模板会被静默跳过。

## Goals / Non-Goals

- Goals
  - 用一个模板生成 ARTI 停机调试描述，在 EB tresos 和本工具里渲染结果一致。
  - 支持多核：每个核一个 `ArtiHardwareCoreInstance`。
  - ID 与 ORTI 模板同规则，保证 ORTI、ARTI、`Os_Cfg.h` 三方一致。
- Non-Goals（第二阶段）
  - `ArtiHook`、`Os_ArtiHooks.h`、内核插桩、`ArtiStatesTaskEnhanced=true`。
  - `ArtiGeneric` 扩展：Spinlock、ScheduleTable、Event、OS_CONFIG 在 ArtiOs 里没有对应容器，第一阶段不输出，调试器仍可从 ORTI 获取这些信息。
  - 修改 ORTI 模板的输出内容（其语法缺陷按 bug fix 单独处理，见 tasks 4）。

## Decisions

### D1 模板命名与放置
- 文件名 `Os_Arti.arxml`，放在 THA6 Os 插件的模板目录（与 ORTI 模板同目录）。EB 下输出 `Os_Arti.arxml`。
- 本工具：`_discover_template_types` 对 `<Module>_` 前缀文件增加后缀白名单 `.arxml`、`.orti`，`t_type` 取前缀之后的完整文件名，输出 `<Module>_<t_type>`，即仍为 `Os_Arti.arxml`。
- 不采用"任意后缀都接受"：插件目录里可能有其他带模块前缀的非模板文件，白名单更安全。

### D2 模板语法约束
只使用 ORTI 模板已使用、且本工具 builtins 已实现的构造：`[!SELECT!]`、`[!LOOP!]`、`[!IF!]`、`[!VAR!]`、`[!FOR!]`、`[!INDENT!]`、`[!INCLUDE!]`、`node:order`、`node:ref`、`node:name`、`node:value`、`num:i`、`text:split`、`num:order`、`count`、`concat`、`contains`、`@index`。新增需求的函数时，先确认两边都支持。

### D3 ORTI → ARTI 映射（第一阶段）

| ORTI | ARTI | 内核表达式（沿用 ORTI） |
| :--- | :--- | :--- |
| `OS.RUNNINGTASK` | 每核 `ArtiHardwareCoreInstanceCurrentTaskRef`；TypeMap `TM_TaskId`：`Input=OsTask/@index` → `OutputRef` 指向 `ArtiOsTaskInstance`，`NO_TASK` → `Output` 字符串 | `Os_OrtiRunningData[n].RunningTaskType` |
| `OS.RUNNINGISR2` | 每核 `…CurrentIsrRef`；`TM_Isr2Id`（只含 CAT2） | `Os_OrtiRunningData[n].RunningISRType` |
| `OS.LASTERROR` | 每核 `…LastErrorRef`；`TM_LastError`（`Output` 为错误码字符串） | `Os_OrtiRunningData[n].LastError` |
| `OS.RUNNINGTASKPRIORITY` | 每核 `…RunningTaskPriorityRef`；TypeMap `Input=@index` → `Output=优先级` | `Os_OrtiRunningData[n].RunningTaskType` |
| `OS.CURRENTAPPMODE` | `ArtiOsInstanceAppModeRef` / `ArtiOsClassAppModeRef`；`TM_AppMode`：`Input=@index+1` → `OutputRef` 指向 `OsAppMode` | `Os_OrtiRunningData[0].CurrentAppMode` |
| `OS.SERVICETRACE` | `ArtiOsInstanceServiceTraceRef` / `ArtiOsClassServiceTraceRef`；`TM_ServiceId` | `Os_OrtiRunningData[n].ServiceId` |
| `TASK.STATE`（0..3） | `ArtiOsTaskInstanceCurrentTaskStateRef`；`TM_TaskState` → `ArtiStatesTaskState`（Running / Ready / Waiting / Suspended） | `<T>_RunningData.State` |
| `TASK.CURRENTACTIVATIONS` / `STACK` / `CONTEXT` | `ArtiOsTaskInstance` 的 `CurrentActivationsRef` / `StackRef` / `ContextRef` | 同 ORTI |
| `STACK` 对象 | `ArtiOsStackInstance`（`Direction="DOWN"`；Size / BaseAddress / FillPattern 用 Constant 或 Expression） | 同 ORTI |
| `ISR` 对象 | `ArtiOsIsrInstance`（`Id=OsIsr/@index`，`Category`，`EcucRef`） | — |
| `ALARM` 对象 | `ArtiOsAlarmInstance`（State / CycleTime / Action / Counter / EcuCRef） | 同 ORTI |
| `RESOURCE` 对象 | `ArtiOsResourceInstance`（State / Locker / Priority / EcuCRef） | 同 ORTI |

- `ArtiStatesTaskEnhanced=false`：内核状态变量只有 4 态，没有 hook，第一阶段按标准模型声明。
- `ArtiOsTaskInstanceId`：取 `OsTask/@index`（ORTI `RUNNINGTASK` 用同一规则），必须等于 `Os_Cfg.h` 的 `TaskType`，由 tasks 3.3 验证。
- `ArtiOsIsrInstanceId`：取 `OsIsr/@index`，同上。

### D4 多核
- 核数取 Os 配置中的核数参数，每个核输出一个 `ArtiHardwareCoreInstance`，`CoreId` 为逻辑核号，表达式下标为 `[n]`。
- 前提是 `Os_OrtiRunningData` 是按核索引的数组（ORTI 模板里只用了 `[0]`），需在 Open Questions 1 中确认。

### D5 开关
- `OsUseArti` 关闭时输出合法 AUTOSAR 文档，但不含 `ECUC-MODULE-CONFIGURATION-VALUES`，使导入该文件的流程不报错。
- `OsUseArti` 在 Os 定义中的位置待确认（Open Questions 2）。

### D6 引用路径
- 指向 Os 容器的 `VALUE-REF` 由模板顶部变量 `$OsValuePkg`（Os 值文件的 AR 包路径）拼接 `node:name()` 得到。不用 `node:path()`，因为两个引擎的返回格式不保证一致。
- 本工具 `WorkspaceProject.get_instance_by_path` 已支持 `/Module/Module/...` 与 `/X_Config/...` 形式，导入后可解析。

## Risks / Trade-offs

- 内核变量名、ID 规则直接复制自 ORTI 模板。ORTI 若本身与内核不一致，ARTI 会一起错 → 用样例 `Os_Cfg.h` 交叉核对（tasks 3.3）。
- 两套模板各自计算 ID，日后可能漂移 → 第二阶段把 ID 计算抽到 `.m` 宏文件中共用。
- `ArtiHardwareCoreInstance` 的两个必填引用（`CurrentApplicationRef`、`EcucCoreRef`）在 ORTI 里没有对应数据（Open Questions 3、4）。

## Open Questions

1. `Os_OrtiRunningData` 是否为按核索引的数组？数组长度等于哪个配置参数（`OsOS/OsNumberOfCores`？该参数名见本工具通用导出 `output/Os/Os_Cfg.h`，未在 THA6 定义中核实）？逻辑核号与 `OsCoreIdMappingConfig/OsPhysicalCoreId` 是什么关系？
2. `OsUseArti` 在 THA6 Os 定义中的路径与取值方式（文档记为 `OsOS/OsStatus = OsUseArti`，未核实）。
3. 当前 OS-Application 是否有内核变量可读？`ArtiHardwareCoreInstanceCurrentApplicationRef` 为 1..1；若没有，回退为指向一个 `ArtiConstant`（值 `"N/A"`）。
4. 工程里是否存在 `EcucCoreDefinition` 容器？`ArtiHardwareCoreInstanceEcucCoreRef` 为 1..1，目标路径本身也是假设的（`gen_arti_os.py` 注释）。若不存在，第一阶段省略该引用，并在校验中作为已知缺口放行。
5. Os 值文件的 AR 包路径（`$OsValuePkg` 的默认值），需从样例 Os 配置 ARXML 中确定。
