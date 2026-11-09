# Design: add-integration-module-packages

完整设计见 [`docs/superpowers/specs/2026-11-09-integration-module-package-design.md`](../../../docs/superpowers/specs/2026-11-09-integration-module-package-design.md)（§6 详细设计，§11 决策 D1–D8 已全部确定，§12 验收标准）。实施计划见 [`docs/superpowers/plans/2026-11-09-integration-module-package-phase1-plan.md`](../../../docs/superpowers/plans/2026-11-09-integration-module-package-phase1-plan.md)。本文只列关键技术决策。

## 关键决策

1. **模块包 = `module.json` 清单 + `config/` 目录**。define、pre、rec 同在 `config/`，与 EB 插件布局一致；模板和资源目录由清单指明（§6.1、§6.2）。
2. **角色按 AUTOSAR 路径判定，不按文件判定**。定义取 `definition`，IMPL 取 `implementation_path`，PRE/REC 取 `pre`/`rec` 列出的值集合路径；一个文件可同时含 Pre 和 Rec，一个 Pre 可由多个文件拼成。包内按路径合并，同一单值字段取值不同时报错，不跨包合并（§6.2）。
3. **分层基线 DEFAULT < REC < DERIVED < PRE**。阶段 1 DERIVED 层为空，但合成接口和三方合并按“可插入多层”实现（§6.5、§8）。
4. **三方合并（Base / Base' / Active）从不删除**。Pre 删除的容器只报告；有改动类条目时先预演，用户确认后才写入 Active 和 Base，拒绝时两者都不变（§6.5）。
5. **基线快照放在 `config/base/<Module>.arxml`**，与活配置同格式，哈希记在 `.dpa`；快照缺失或哈希不符时按“旧工程迁移”处理，现有值一律视为 USER（§6.5、§10）。
6. **值来源由比较得出，不写进配置文件**，配置 arxml 格式和 EB 往返不受影响。Pre 只读锁定只在命令层执行，`pre_unlocked` 记录用户解锁的参数（D1 = C）。
7. **`.dpa` format 8**：新增 `directories`、`module_libraries`，`modules` 按定义路径定位包；工程根 = `.dpa` 所在目录。format ≤7 按原逻辑打开、不应用 PRE，保存时仍写 7（§6.7、§6.9）。
8. **EB 插件不改造即可使用**：没有 `module.json` 时从 `plugin.xml` 推断（schema → 定义，`preconfig` → PRE，`generate_PB/` → 模板）；`autosar/*.arxml` 视为交换副本，不加载，只在来源界面列出（§6.2）。
9. **模板查找顺序：覆盖层 `templates/<Module>/` → 包内模板目录**。format 8 保存时不再复制模板；指纹只按模板内容计算（§6.6、W6）。
10. **不使用符号链接**。link 模式改为在 `module_libraries` 中直接写外部库路径（§6.6、W9）。
