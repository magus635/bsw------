## Context

- 第一阶段（`add-os-arti-description-template`）的核对结果见该 change 的 design.md。本 change 在它之上补齐 ORTI 覆盖。
- ARTI 定义 `definitions/Arti/Arti_ParamDef.arxml` 的 `ArtiOs` 只有 Alarm / Context / Isr / Resource / Stack / Task / Os 的 Class 与 Instance，没有 Event、Spinlock、ScheduleTable 的容器。通用机制是 `ArtiGeneric`：`ArtiGenericComponentClass`（名字，加若干 `ClassParameter`，各带名字和 `TypeMapRef`）、`ArtiGenericComponentInstance`（名字，`ClassRef`，加若干 `InstanceParameter`，各引用一个 Constant / Expression / Hook）。`ArtiOsGenericComponentRef`、`ArtiOsTaskInstanceGenericComponentRef`、`ArtiOsIsrInstanceGenericComponentRef` 等引用可把通用组件挂到 Os 对象上。
- `ArtiParameterTypeMapPairOutputRef` 的目标含 `ArtiStatesScheduleTableState`、`ArtiStatesSpinlockState`、`ArtiStatesSpinlockOwnerType`，说明规范预期用通用组件描述这三类对象。
- 权威的 ORTI 是插件 `Os_THA6_ASR21/generate_PB/Os/Os_Trace_Core0.ORTI` 与 `Os_Trace_Core1.ORTI`（两者只有 `Os_OrtiRunningData[n]` 的下标不同）。仓库中的 `doc/ARTI/Os_Trace.orti` 与插件版有约 50 行差异，且只含 `[0]`。

## Goals / Non-Goals

- Goals
  - ORTI 的每个对象类型和属性在 ARTI 中都有对应，表达式一致，枚举映射一致。
  - 用自动对照测试给出覆盖缺口清单，并让缺口数逐步归零。
- Non-Goals
  - `RESOURCE_OWNER`、`SPINLOCK_OWNER`（见 D5）。
  - `ArtiHook`、运行时 trace、内核改动。
  - 调试器显示效果的验证（需要 TRACE32 环境，使用者后续执行）。

## Decisions

### D1 "兼容"的定义
三层，验收取最后一层：对象覆盖、属性覆盖、取值显示一致（表达式字符串相同，枚举数值到名字的映射相同）。做不到一致的项必须在 D6 的差异清单里逐条说明原因。

### D2 通用组件建模
每类需要补齐的内容用一个通用组件 Class，类参数名与 ORTI 属性名一致（`OSTASKTYPE`、`EVENTMASK` 等），这样调试器里显示的名字与 ORTI 相同。每个对象一个 Instance，参数是 Constant（静态值，如 `OsTaskSchedule`、`OsEventMask`、`OS_CONFIG` 的三项）或 Expression（运行时表达式）。需要把数值显示成名字的，给类参数挂 TypeMap。

### D3 ORTI 属性到 ARTI 的映射

| 对象 | ORTI 属性 | ARTI 载体 | 表达式 / 值（取自插件 ORTI） |
| :--- | :--- | :--- | :--- |
| Task | `OSTASKTYPE` | 通用组件，TypeMap（0=BASIC，1=EXTENDED） | `Task_<T>_ConfigRef.IsExtended` |
| Task | `OSTASKSCHEDULE` | 通用组件，Constant | `OsTaskSchedule` |
| Task | `OSTASKMAXACTIVATION` | 通用组件，Expression | `Task_<T>_ConfigRef.MaxActivationCount` |
| Task | `REMAININGACTIVATIONS` | 通用组件，Expression | `Task_<T>_ConfigRef.MaxActivationCount - <T>_RunningData.ActivationCount` |
| Task | `EVENTMASK` / `EVENTSETFLAG` | 通用组件，Expression | `<T>_RunningData.EventWait` / `.EventSet` |
| Task / ISR | `LOCKED` | 通用组件，Expression，加 TypeMap（输入为 `<T>_RunningData.LockList`，用 `&Os_LockConfig_<资源>` 的地址表达式做 `InputExpressionRef`，输出为资源名；空值输出 `-`） | `<T>_RunningData.LockList` |
| ISR | `PRIORITY` | 通用组件，Expression | `<I>.IsrHwConfig.priority`（逐字沿用 ORTI，见 Open Questions 3） |
| Alarm | `ACTION` | 通用组件，Expression，加 TypeMap（0..3：ACTIVATETASK / SETEVENT / CALLBACK / INCREMENTCOUNTER） | `Alarm_<A>_ConfigRef.ActionType` |
| Alarm | `ALARMTIME` | 通用组件，Constant `0` | ORTI 标注"Not Supported" |
| Resource | `LOCKED` | 通用组件，Expression，加 TypeMap | `Os_LockConfig_<R>.Previous` |
| Resource | `PRIORITY_TYPE` / `PRIORITY` | 通用组件，Expression | `Os_ResourceConfig_<R>.CeilingIsrLevel == 0xFFFFFFFF ? …`（完整式取自 ORTI） |
| Event | `EVENTMASK` | 通用组件，Constant | `OsEventMask` |
| ScheduleTable | `STATE` | 通用组件，TypeMap 的 `OutputRef` 指向 `ArtiStatesScheduleTableState`（0=STOPPED，1=NEXT，2=WAITING，3=RUNNING，4=RUNNING_AND_SYNCHRONOUS） | `Os_<S>_RunningData.State` |
| ScheduleTable | `SCHEDULETABLENEXT` | 通用组件，Expression，加 TypeMap（序号到名字，`0xFF` 输出 `-`） | `Os_<S>_RunningData.NextSchTID` |
| Spinlock | `STATE` | 通用组件，TypeMap 的 `OutputRef` 指向 `ArtiStatesSpinlockState`（0=UNLOCKED，1=LOCKED） | `Os_LockStatus_<S>.lockStatus` |
| Spinlock | `LOCKED` / `LOCK_METHOD` | 通用组件，Expression | `Os_LockConfig_<S>.Previous` / `Os_SpinlockConfig_<S>.OsSpinlockLockMethod` |
| OS | `ScalabilityClass` / `StatusLevel` / `OsStackMonitoring` | Os 级通用组件，三个 Constant | `OsScalabilityClass` / `OsStatus` / `OsStackMonitoring` |

### D4 对照测试
`tests/generator/test_arti_orti_parity.py` 渲染基准 ORTI 和 ARTI，解析 ORTI 的 `TASK` / `ISR` / `ALARM` 等对象及其属性赋值，对每个属性在 ARTI 输出里查找同名类参数与同一表达式字符串。测试输出缺口清单；允许一份显式的例外清单（D6），例外之外的缺口使测试失败。随阶段推进，缺口清单逐步归零。

### D5 推迟项
`RESOURCE_OWNER` 和 `SPINLOCK_OWNER` 的 ObjectID 编号由 `Os_AppCommon.m` 的宏累加得到，逻辑复杂，容易与内核漂移。另起 change 处理，本 change 把它们列入例外清单。

### D6 无法完全一致的差异
- ORTI 按核拆成 `Os_Trace_Core0.ORTI`、`Os_Trace_Core1.ORTI`，ARTI 一个文件含所有核。
- ORTI 的 `ALARMTIME` 本来是常量 `0`（不支持），ARTI 同样输出常量 `0`。
- 调试器对 ORTI 枚举的显示方式与对 ARTI TypeMap 的显示方式可能不同，需要真机确认。

## Risks / Trade-offs

- **调试器是否显示通用组件未知**。这是整个方案成立的前提，当前没有 TRACE32 环境，只能先做到规范和定义校验。使用者之后在真机上验证；若不显示，需要回到本 change 重新评估（例如改为在 ARTI 标准容器之外保留 ORTI）。
- ORTI 里有的表达式本身可能不对（例如 ISR `PRIORITY` 的 `<I>.IsrHwConfig.priority`）。本 change 先逐字沿用以保证一致，并在 Open Questions 记录，不在此处修正。
- ORTI 对 `OsResourceSubderivative = Os_SC300` 会跳过 Alarm / ScheduleTable / Spinlock，ARTI 模板目前没有此判断。

## Open Questions

1. 调试器（TRACE32 版本待定）是否显示 `ArtiGeneric` 通用组件，以及一个文件含多核是否可用。
2. **已定。** Alarm 的 `ACTION` 用通用组件加 TypeMap，因为 ORTI 是运行时读取 `Alarm_<A>_ConfigRef.ActionType`；标准的 `ArtiOsAlarmInstanceAction`（静态字符串）没有使用。
3. **已核对。** 插件 `isr/Os_isr_Lcfg.c:177` 生成 `static const Os_IsrConfigType <ISR 名> = {...}`，所以 `<I>.IsrHwConfig.priority` 是真实符号。同一文件 `:80-81` 显示 `<I>_RunningData` 只为 CATEGORY_2 ISR 生成，所以 ORTI 对 CATEGORY_1 ISR 输出的 `LOCKED`（以及 `STACK`、`CONTEXT`）引用了不存在的符号，ARTI 不输出（对照测试里对这三项做了 CATEGORY_1 豁免）。
4. `Os_SC300` 条件在 ARTI 里如何处理。
