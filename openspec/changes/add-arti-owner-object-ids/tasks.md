## 1. 可行性
- [x] 1.1 （已通过：引擎执行真实 `.m` 无告警，且数值与手算一致）在测试里用真实的 `doc/ARTI/Os_AppCommon.m` 渲染 ORTI（替换空桩），确认引擎能执行其中的宏；记录哪些构造不支持
- [x] 1.2 （已核对，见 design.md Open Questions 2）对照内核：用真实 `Os_application_Cfg.h` 的 `APPLICATION<n>_OBJECT_START_NUMBER` 验证 ORTI 的累计规则，回写 design.md Open Questions 2

## 2. 实现
- [x] 2.1 夹具补充 Hook 开关、IOC 回调、计数器，使应用起点不为 0
- [x] 2.2 `Os_Arti.arxml`：`INCLUDE "Os_AppCommon.m"`（或按 D1 退到方案 B），计算每个 Task 与 CATEGORY_2 ISR 的 `ObjectIDIndex`
- [x] 2.3 TypeMap `ResourceOwner`、`SpinlockOwner`（含 `-` = 0xFFFFFFFF），类参数 `RESOURCE_OWNER`、`SPINLOCK_OWNER`，表达式 `Os_<名>_RunningData.OwnerObjectID`
- [x] 2.4 对照测试：去掉例外清单中的两项；新增编号与 ORTI 枚举逐项一致的测试

## 3. 收尾
- [x] 3.1 更新 `doc/2026-10-06_自研OS原生支持ARTI开发说明.md` 第十节 4 的"未覆盖"列表
- [x] 3.2 更新 `add-arti-orti-parity` 的 tasks 3.5 和 design D5

## 4. 真机验证（使用者执行）
- [ ] 4.1 资源被任务或 ISR 持有时，调试器显示持有者名字
