## Why

`add-arti-orti-parity` 让 ARTI 覆盖了 ORTI 的全部属性，只剩 `RESOURCE_OWNER` 和 `SPINLOCK_OWNER` 两项没有对应（在对照测试的例外清单里）。这两项显示"谁持有这个资源或自旋锁"：内核把持有者的全局对象编号 `ObjectIDIndex` 写进 `OwnerObjectID`，ORTI 用一个枚举把编号翻译成 `Task <名>` / `ISR <名>`。缺了这两项，调试器看资源和自旋锁时只能看到一个数字，ARTI 还不能替代 ORTI。

## What Changes

- 在 `Os_Arti.arxml` 里为 `OsResource` 和 `OsSpinlock` 的通用组件增加 `RESOURCE_OWNER` / `SPINLOCK_OWNER` 参数：表达式取 `Os_<名>_RunningData.OwnerObjectID`，TypeMap 把对象编号映射成 `Task <名>` / `ISR <名>`，无持有者（`0xFFFFFFFF`）映射成 `-`，与 ORTI 的枚举一致。
- 对象编号的计算与 ORTI 使用同一套规则：按 `OsApplication/@index` 顺序，每个应用内先 Task、再 ISR（所有 ISR 都占编号，只有 CATEGORY_2 有名字），再累加该应用的其他对象（计数器、Alarm、调度表、Hook、IOC 回调）得到下一个应用的起点。
- 实现方式见 design.md D1，首选在 ARTI 模板里 `INCLUDE` 同一个 `Os_AppCommon.m`，避免两处各算一遍。
- 对照测试的例外清单去掉这两项。

## Impact

- Affected specs: `os-arti-description`（新增要求）
- Affected code: `templates/Os/Os_Arti.arxml`、`tests/generator/test_arti_orti_parity.py`、`tests/generator/test_os_arti_template.py`、测试夹具（需要 Hook、IOC 回调、计数器、调度表等对象才能验证起点累加）
- 依赖：`add-arti-orti-parity` 先合入；插件 `Os_AppCommon.m`（已在 `doc/ARTI/` 有参考副本）
- 不修改内核
