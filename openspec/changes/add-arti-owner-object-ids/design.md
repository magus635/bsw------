## Context

- 内核写入：`Os_resource.c:219`、`Os_spinlock.c:329/448` 把 `CurrentObject->ObjectIDIndex` 写进 `OwnerObjectID`；释放时写 `0xFFFFFFFF`。
- ORTI 的 `RESOURCE_OWNER` / `SPINLOCK_OWNER` 是一个枚举：每个应用内依次给 Task（`Task <名>`）和 ISR（`ISR <名>`，只有 CATEGORY_2 输出名字，但所有 ISR 都占一个编号）编号，之后 `ObjectID` 被重置为"到该应用结束为止的累计对象数"（`CurrentAppObjectCnt`），累计内容是 Task + ISR + 计数器 + Alarm + 调度表 + Hook 个数 + IOC 回调个数。
- Hook 个数和 IOC 回调个数由 `Os_AppCommon.m` 的宏 `Os_Calculate_Hook_ObjectCount`、`Os_Calculate_IocCallBack_ObjectCount` 计算。Hook 个数的规则：非内核应用按各 Hook 开关累加；内核应用按 `OsOS/OsHooks` 的开关累加，另加 1。
- 现有测试用空桩替代这两个宏（返回 0），因此累加起点从未被真实验证。

## Goals / Non-Goals

- Goals
  - ARTI 的 `RESOURCE_OWNER`、`SPINLOCK_OWNER` 与 ORTI 的枚举逐项一致。
  - 编号规则只有一份实现。
- Non-Goals
  - 修改内核或 ORTI 模板。
  - 其他对象（Alarm、调度表）的持有者显示。

## Decisions

### D1 编号计算怎么共用
- 方案 A（首选）：ARTI 模板 `[!INCLUDE "Os_AppCommon.m"!]`，直接调用同样的宏，再按 ORTI 的方式累加。两个模板用同一份宏，不会漂移。
- 方案 B：在 ARTI 模板里重写计算。独立可测，但会和 `Os_AppCommon.m` 各算一遍，日后可能漂移。
- 取舍：方案 A 取决于本工具的模板引擎能不能执行 `.m` 里的构造（`[!NOCODE!]`、`node:exists`、`/…/OsApplication/*[num:i($AppID + 1)]` 这种带位置谓词的路径、`bit:` 函数）。**先做可行性试验（tasks 1）**，不行再退到 B，并在 design 里记录差异。

### D2 TypeMap 形式
输入是 `ObjectIDIndex`，输出是字符串 `Task <名>` / `ISR <名>`（不用 `OutputRef`，因为 `ArtiParameterTypeMapPairOutputRef` 不能指向 Os 的 Task 或 ISR 值）。无持有者：输入 4294967295，输出 `-`。ORTI 里 `RESOURCE_OWNER` 和 `SPINLOCK_OWNER` 的枚举内容相同，ARTI 用一张共用的 `TM_ObjectOwner`，两个类参数都挂它。

### D4 缺少 `Os_AppCommon.m` 时的保护（实施中发现）
本工具的 `INCLUDE` 找不到文件时不报错，宏调用也静默失败，结果是对象编号漏掉 Hook、IOC 回调的个数（例如 `Task_C` 变成 7 而不是 10），没有任何提示。EB tresos 里找不到文件会直接报错，所以问题只出在本工具。做法：模板在 `INCLUDE` 之前把 `ObjectID` 置为哨兵值，宏文件会把它置为 0；`INCLUDE` 之后若仍是哨兵，就不输出 `TM_ObjectOwner`，持有者类参数不挂 TypeMap（调试器显示数字），宁可少显示，也不显示错误的名字。

### D3 测试
- 夹具补充：每个应用的 Hook 开关、IOC 回调、计数器，使累加起点不为 0。
- 对照测试：ORTI 渲染时使用真实的 `Os_AppCommon.m`（若引擎可执行），ARTI 的 TypeMap 编号必须与 ORTI 枚举的编号逐项相同。

## Risks / Trade-offs

- 引擎不能执行 `Os_AppCommon.m` 时，方案 A 不可用，退到方案 B 会引入第二份编号逻辑。
- ORTI 对 CATEGORY_1 ISR 也占编号但不输出名字；ARTI 要保持同样的占位，否则后面所有对象的编号错位。

## Open Questions

1. **已解决。** 本工具的引擎能执行真实的 `Os_AppCommon.m`（非内核应用与内核应用两条分支都试过，无告警），ARTI 与 ORTI 渲染出的编号一致，也与手算一致（App_Core0 含 2 个 Task、2 个 ISR、1 个计数器、1 个 Alarm、1 个调度表、3 个 Hook 对象 = 10，所以 App_Core1 从 10 开始）。
2. **已核对。** 内核侧的编号规则与 ORTI 一致：插件 `application/Os_application_Cfg.h:80-112` 里 `APPLICATION<n>_OBJECT_START_NUMBER` 是各应用对象数的累加，每个应用的对象数 = Task + ISR + Alarm + 计数器 + 调度表 + IOC 回调 + Hook，Hook 的计数规则（非内核应用按各开关累加，内核应用按 `OsOS/OsHooks` 的开关累加再加 1）与 `Os_AppCommon.m` 逐条相同，也就是 ORTI 的 `CurrentAppObjectCnt`。`application/Os_application_Lcfg.c:287-350` 的对象表给每个对象顺序编号 `ObjectIDIndex`，一个应用内依次是 Task、ISR、计数器、Alarm、调度表、Hook；ISR 的 `ObjectID + 1` 在 `CATEGORY_2` 判断之外，所有 ISR 都占编号，与 ORTI 一致。**未逐项读**：IOC 回调对象的编号条目。
