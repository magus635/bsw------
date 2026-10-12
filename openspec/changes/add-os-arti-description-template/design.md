## Context

- 现有 ORTI 模板 `doc/ARTI/Os_Trace.orti`（原名 `Os_Arti.arxml`，KOIL 2.2）是 OS 生成器对调试器描述内核的唯一来源，包含内核变量名、ID 规则和 Os 配置路径。
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
实现中发现两处两个引擎行为不同，模板已规避：
- `[!SELECT "$变量"!]`：本工具引擎不解析变量形式的路径。SELECT 一律写路径字面量（ORTI 模板也是这么写的）。
- 表达式字符串里的 `&amp;`：本工具引擎会解码成 `&`，EB 原样保留。需要 `&` 的地方由宏在模板正文里写 `&amp;`（宏参数 `AddressOf`），不经过表达式。

模板中还用了 `[!MACRO!]`（定义在模板内）和 `text:replace`，用于去掉 EB 引用值的 `ASPath:` 前缀。

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

- 实现与上表的出入（第一阶段有意省略，等材料或第二阶段再补）：
  - `ArtiOsAlarmInstanceAction`、`AlarmTimeRef` 未输出：ORTI 的 Action 是运行时表达式，ARTI 要的是静态字符串，需要 OsAlarmAction 配置；AlarmTime 在 ORTI 中本来就标注"不支持"。
  - `ArtiOsResourceInstanceLockerRef`、`Priority` 未输出：Owner ObjectID 的编号依赖 `Os_AppCommon.m`。
  - `ArtiOsIsrInstance` 对 CATEGORY_1 ISR 也输出（带 `Category`）；`TM_Isr2Id` 只含 CATEGORY_2。**栈和上下文只对 CATEGORY_2 ISR 输出**：内核只为 Task 和 CATEGORY_2 ISR 生成 `<名>_stack`、`<名>_ContextInfo`（插件 `context/Os_context_Lcfg.c:89-93`、`:157-162`），对 CATEGORY_1 输出会让调试器求值时找不到符号（Open Questions 7）。
  - `LastError` 的表达式照常输出，但内核目前只在初始化时写 `E_OK`，之后不更新，调试器将一直显示 `E_OK`（Open Questions 6）。
  - `ArtiOsTaskInstanceFunction` 未输出：任务入口函数名的命名规则未知。
- `ArtiStatesTaskEnhanced=false`：内核状态变量只有 4 态，没有 hook，第一阶段按标准模型声明。
- `ArtiOsTaskInstanceId`：取 `OsTask/@index`（ORTI `RUNNINGTASK` 用同一规则），必须等于 `Os_Cfg.h` 的 `TaskType`，由 tasks 3.3 验证。
- `ArtiOsIsrInstanceId`：取 `OsIsr/@index`，同上。
- `NO_TASK`、`NO_ISR`：内核的无效值分别是 `INVALID_TASK = TOTAL_TASK_NUM = count(OsTask/*)` 和 `INVALID_ISR = OS_ISR_TOTAL_NUM = count(OsIsr/*)`（插件 `task/Os_task_Cfg.h`、`isr/Os_isr_Cfg.h:79-80`）。`NO_ISR` 统计**所有** ISR，含 CATEGORY_1，不是"最后一个 CATEGORY_2 的序号+1"。

### D4 多核
- 核数取 Os 配置中的核数参数，每个核输出一个 `ArtiHardwareCoreInstance`。
- `Os_OrtiRunningData[]` 的下标是 `Os_Inf_GetCoreId()`，即 `Os_ConfigSet.CoreIDListPtr[物理核号]`（内核 `kernel/Os_kernel.h:206`），是**逻辑核号**。插件模板里按核命名的变量（`Os_SchedulerProperty_Core<N>` 等）也用 `OsCoreId` 所引用核定义的 `EcucCoreId` 作 `<N>`。所以表达式下标和 `CoreId` 取 `EcucCoreId`，取不到时回退到 `OsPhysicalCoreId`（Open Questions 1）。

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

状态说明：**已有证据**指本工具对一份 THA6 Os 配置的通用导出 `output/Os/Os_PBcfg.c`（按容器列出参数和引用），可信度较高，但还没有对照 THA6 Os 定义文件和真实 `Os_Cfg.h` 核实。模板顶部注释里的 A1–A5 与下面各条对应。

**第二轮核对（来源）**：目标内核源码 `D:/19_AutosarOS/02_THA6204/02_Software/01_Code/01_Trunk/00_CodeProject/tr002_THA6_OS_Project/Os/`，插件模板 `D:/19_AutosarOS/02_THA6204/02_Software/02_ConfiguratorPlugins/01_Trunk/eclipse/plugins/Os_THA6_ASR21/generate_PB/Os/`。下面标"已核对"的条目以它们为依据；`output/Os/` 里 `OS_STATUS_USEARTI` 为关闭，其产物不含 ORTI 数据，不能作为这部分的证据。

1. **已核对（内核存在该数组），下标取值为强推断。** 核配置是 `OsCoreIdMappingConfig`（含 `OsPhysicalCoreId`、`OsCoreId`）。内核有 `Os_OrtiRunningData[OS_KERNEL_MAX_CORE_NUM]`（`orti/Os_orti.c`），下标是 `Os_Inf_GetCoreId()`，即 `CoreIDListPtr[物理核号]`，是逻辑核号；插件内核模板的 `<N>` 取 `EcucCoreId`。**仍未核实**：`CoreIDListPtr` 的内容由哪个模板生成，是否等于 `EcucCoreId`（A1，已改为取 `EcucCoreId`，回退 `OsPhysicalCoreId`）。
2. **已有证据。** `OsUseArti` 是 `OsOS` 下的布尔参数，与 `OsStatus`（`STANDARD`/`EXTENDED`）是两个参数。开发说明里"`OsStatus = OsUseArti`"的说法有误，已更正。
3. **已核对，已修正模板。** 内核有每核的 `Os_AppRunningTimeData_Core<N>`（`Os_ApplicationRunningTimeDataType`，`kernel/Os_kernel_Lcfg.c:69`），其中 `Current_ApplicationID` 是当前 OS-Application（`application/Os_application_types.h:154`；`OsApp_GetCurrentApplicationID()` 读它）。`ApplicationType = OsApplication/@index`，无效值 `INVALID_OSAPPLICATION = count(OsApplication/*)`（插件 `application/Os_application_Cfg.h:76-77`、`:127`）。模板新增表达式 `E_Core<N>_CurrentApplication` 和 `TM_ApplicationId`，取代原来的常量 `"N/A"`。`ArtiParameterTypeMapPairOutputRef` 的目标里没有 `OsApplication`（见定义文件），所以该 TypeMap 的输出用应用名字符串，不用引用。
4. **已有证据，并已修正定义文件。** 工程里有核定义容器，`OsCoreIdMappingConfig/OsCoreId` 引用 `/EcuC/EcuC/EcucHardware/EcucCoreDefinition_N`；模板直接沿用这个引用。同时发现 `Arti_ParamDef.arxml` 中 `ArtiHardwareCoreInstanceEcucCoreRef` 的目标路径少了 `EcuC` 一级（`/AUTOSAR/EcucDefs/EcucHardware/...`），已在 `tools/arti/gen_arti_os.py` 中改为标准路径 `/AUTOSAR/EcucDefs/EcuC/EcucHardware/EcucCoreDefinition` 并重新生成。
5. **已有证据。** 导出中的引用形如 `&Os_Os_OsCoreIdMappingConfig_0_Config`，即 Os 值路径为 `/Os/Os/<容器>`；模板中 `$OsValuePkg = '/Os/Os'`（A4）。
6. **内核已确认是遗漏，修复已 review 通过，待提交 SVN；模板无需修改。** 原状：`LastError` 在内核里只有一处赋值，`OsOrti_OrtiInit` 把它置为 `E_OK`（`orti/Os_orti.c:90`，trunk 与 tag t006 一致）；`OsHook_CallErrorHook(Error)` 只把错误码传给 ErrorHook，没有写入 `Os_OrtiRunningData`，所以 ARTI（和现有 ORTI）的 LastError 一直显示 `E_OK`。内核团队确认是遗漏，会补。
   - 方案：在 `OsHook_CallErrorHook` 开头、调用任何 Hook 之前，调用新增的 `OsOrti_SetLastError(Error)`（受 `OS_STATUS_USEARTI` 控制，下标 `Os_Inf_GetCoreId()`）。理由：(a) 内核里 60 处出错路径都经过该函数；(b) 该函数无条件执行，未配置 ErrorHook 时也会记录；(c) 进入前已 `OsIsr_SuspendISR`，更新是原子的；(d) `OsHook_SetErrorParameterXxx` 已先写 `ServiceID`，两者一致。成功时不清零，含义为"最近一次出错"。
   - 已知限制：不经过 `OsHook_CallErrorHook` 的错误（如保护钩子的保护错误）不会被记录。
   - 状态：改动在 `tr002_THA6_OS_Project/Os/` 的 `orti/Os_orti.c`、`orti/Os_orti.h`、`hook/Os_hook.c`，已 review 通过，尚未提交 SVN；已用 `arm-none-eabi-gcc -fsyntax-only` 在 `OS_STATUS_USEARTI` 开和关两种情况下检查语法，未用工程的 armclang 编译，也未运行。
   - 对模板的影响：无。`TM_LastError` 和 `Os_OrtiRunningData[n].LastError` 的表达式不变；内核提交 SVN 前，调试器看到的 LastError 仍恒为 `E_OK`。
7. **已核对，已修正模板。** (a) `NO_ISR` 应为 `count(OsIsr/*)`（D3）。(b) 内核只为 Task 和 CATEGORY_2 ISR 生成 `_stack`、`_ContextInfo`，模板对 CATEGORY_1 ISR 输出这些表达式会引用不存在的符号，已改为只对 CATEGORY_2 输出。
8. **已核对。** `TaskType = OsTask/@index`、`ISRType = OsIsr/@index`（插件 `task/Os_task_Cfg.h:64`、`isr/Os_isr_Cfg.h:75`），A2 成立。ServiceId 的写入编码为开始 `ServiceId*2+3`、结束 `&= ServiceId*2+2`、初值 `0x1A2`，与模板的 `TM_ServiceId`（值×2+2）一致。Task 状态枚举 `RUNNING/READY/WAITING/SUSPENDED = 0..3`（`task/Os_task_types.h:54-57`），A5 成立。栈：基址 `&<名>_stack[0]`、`StackBottomAddr = &<名>_stack[大小/4]`，内核在 `stack[0]`（`StackTopAddr`）放溢出监测字 `0xAA55AA55`（`context/Os_context_Lcfg.c:236`、`Os_context.c:203`），其余为清零的静态存储，所以栈方向 `DOWN`、填充模式 `0x00000000` 与内核一致。**仍未核对**：`CoreIDListPtr` 的内容（Open Questions 1）；各核 Hook 栈、`StartOsInitFunction` 栈等没有输出，属第一阶段范围之外。
