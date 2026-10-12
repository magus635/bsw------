## Why

第一阶段的 `Os_Arti.arxml` 只覆盖了 ORTI 中的 OS、Task（部分）、ISR（部分）、Stack、Alarm（部分）、Resource（部分）。Event、ScheduleTable、Spinlock、OS_CONFIG 和一批 Task / ISR / Resource 属性在 ARTI 里没有输出，调试器仍然只能从 ORTI 得到这些信息，所以 ORTI 不能下线。目标是让 ARTI 模板覆盖 ORTI 的全部内容，使两者可以互相替代。

## What Changes

- 用 ARTI 定义里的 `ArtiGeneric` 通用组件（Class / Instance / Parameter，经各 `…GenericComponentRef` 挂到 Os、Task、Isr、Resource 等容器）补齐 ARTI 专用容器没有的对象和属性：
  - Task：`OSTASKTYPE`、`OSTASKSCHEDULE`、`OSTASKMAXACTIVATION`、`REMAININGACTIVATIONS`、`EVENTMASK`、`EVENTSETFLAG`、`LOCKED`
  - ISR：`PRIORITY`、`LOCKED`
  - Alarm：`ACTION`、`ALARMTIME`
  - Resource：`LOCKED`、`PRIORITY_TYPE`、`PRIORITY`
  - 新对象：Event、ScheduleTable、Spinlock（`STATE`、`LOCKED`、`LOCK_METHOD`）、OS_CONFIG
- 表达式字符串与 ORTI 逐字相同，枚举取值映射与 ORTI 相同。
- 以插件里的 `Os_Trace_Core0/1.ORTI` 为权威基准，同步进仓库，新增"ORTI 对照测试"：解析 ORTI 与 ARTI 的渲染结果，报告每个 ORTI 对象、属性在 ARTI 中是否存在、表达式是否相同。
- 在文档里列出无法做到完全一致的差异（ORTI 按核拆成两个文件而 ARTI 是一个文件；`ALARMTIME` 在 ORTI 中本来就是"不支持"等）。
- **不包括**：`RESOURCE_OWNER`、`SPINLOCK_OWNER`（依赖 `Os_AppCommon.m` 的 ObjectID 累加，另起 change）；`ArtiHook` 和运行时 trace；调试器真机验证（暂无 TRACE32 环境，由使用者之后执行）。

## Impact

- Affected specs: `os-arti-description`（新增要求；依赖 `add-os-arti-description-template` 先归档）
- Affected code: `templates/Os/Os_Arti.arxml`；`tests/generator/os_arti_fixture.py`（增加 Event、ScheduleTable、Spinlock、锁相关配置）；新增 `tests/generator/test_arti_orti_parity.py`；新增对照基准 `doc/ARTI/` 下的插件 ORTI 副本
- 不修改内核、不修改 ORTI 模板
