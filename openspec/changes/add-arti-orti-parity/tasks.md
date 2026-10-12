## 0. 前置与基线
- [x] 0.1 把插件的 `Os_Trace_Core0.ORTI`、`Os_Trace_Core1.ORTI`、`Os_AppCommon.m` 同步到 `doc/ARTI/`作为参考副本，并在 `doc/ARTI/README.md` 说明它们与 `Os_Trace.orti` 的差异。对照测试实际用语法已修正的 `Os_Trace.orti` 渲染（内容与插件 Core0 相同，插件版有 ENUM 末项多余逗号等 KOIL 语法缺陷，见 README），因此测试能解析
- [x] 0.2 扩展 `tests/generator/os_arti_fixture.py`：增加 OsEvent、OsScheduleTable、OsSpinlock、OsResource 的天花板配置、Task 的 `OsTaskSchedule` 和事件引用、Alarm 的 action 配置
- [x] 0.3 通用组件最小试验：为 Event 输出一个通用组件，通过 XSD 和 `Arti_ParamDef.arxml` 校验，本工具导入后引用全部解析
- [x] 0.4 `tests/generator/test_arti_orti_parity.py`：解析基准 ORTI 与渲染出的 ARTI，输出缺口清单，带显式例外清单；此时清单即当前缺口，测试以"缺口不增加"为准

## 1. 已有对象的属性补全
- [x] 1.1 Task：`OSTASKTYPE`、`OSTASKSCHEDULE`、`OSTASKMAXACTIVATION`、`REMAININGACTIVATIONS`、`EVENTMASK`、`EVENTSETFLAG`
- [x] 1.2 ISR：`PRIORITY`
- [x] 1.3 Alarm：`ACTION`（含 TypeMap）、`ALARMTIME`
- [x] 1.4 Resource：`PRIORITY_TYPE`、`PRIORITY`
- [x] 1.5 `LOCKED`（Task、ISR、Resource）：TypeMap 输入用 `&Os_LockConfig_<资源>` 地址表达式，空值输出 `-`

## 2. 新对象
- [x] 2.1 Event
- [x] 2.2 ScheduleTable（`STATE` 映射到 ARTI 标准状态，`SCHEDULETABLENEXT`）
- [x] 2.3 Spinlock（`STATE` 映射到标准状态，`LOCKED`、`LOCK_METHOD`）
- [x] 2.4 OS_CONFIG（三个常量）

## 3. 收尾
- [x] 3.1 对照测试缺口清单只剩例外清单中的项（`RESOURCE_OWNER`、`SPINLOCK_OWNER` 及 D6 所列）
- [x] 3.2 `Os_SC300` 条件：ARTI 不判断，差异已记录（Open Questions 4 / D6）；不需要代码改动
- [x] 3.3 更新 `doc/2026-10-06_自研OS原生支持ARTI开发说明.md`：ORTI 与 ARTI 覆盖对照表、差异清单、双轨交付说明
- [x] 3.4 更新第一阶段 design.md 的 Non-Goals（`ArtiGeneric` 扩展已完成）
- [x] 3.5 另起 change 处理 `RESOURCE_OWNER`、`SPINLOCK_OWNER`（ObjectID 编号）：已由 `add-arti-owner-object-ids` 完成

## 4. 真机验证（使用者执行，暂无 TRACE32 环境）
- [ ] 4.1 调试器加载 ARTI，确认通用组件（Task 扩展属性、Event、ScheduleTable、Spinlock、OS_CONFIG）是否显示
- [ ] 4.2 同一配置下对比 ORTI 与 ARTI 的显示内容，记录差异并回写 D6
