## 0. 前提
- [x] 0.1 已确认：改 EB 正式插件和 T1 两份副本；没有现成的 SC300 内核，由现成 Cortex-M3 移植，另立提案

## 1. 资料完整性（`core/hardware/chip_completeness.py`）
- [x] 1.1 读取 `metadata.unconfirmed`（字段 → 说明）
- [x] 1.2 自动检查：选择器值不在模块定义的取值范围内、声明了 Os 选择器但没有 Os 资源、核数不一致
- [x] 1.3 单元测试：每类检查都有用例；确认检查不修改芯片对象，也不修改芯片文件

## 2. 界面与扫描
- [x] 2.1 项目属性：芯片下拉框显示“（资料不完整）”，选中后状态文字列出缺少的内容；芯片仍可选择
- [x] 2.2 芯片依赖扫描的“资源覆盖”中列出完整性条目
- [x] 2.3 UI 测试

## 3. 芯片数据
- [x] 3.1 新增 `data/chips/SC300.yaml`：只有 Os 选择器，`ecu_resources.Os` 为 1 核、240/16 个中断，并带 `metadata.unconfirmed`
- [x] 3.2 修正 Os 插件和 T1 中的 `Os_Resource_SC300.properties`
- [x] 3.3 `THA610X_LFBGA180.yaml` 只增加 `metadata.unconfirmed`，其他数据不改

## 4. 验证
- [x] 4.1 T1 副本切换到 SC300：只写入 Os 选择器，MCAL 模块的值不变；`ecu:get('OsResource.NumOfCores')` 为 1；能生成代码，且生成的是 SC300 分支（NVIC、240 个中断）
- [x] 4.2 6206 和 6412 的生成结果逐字节不变
- [x] 4.3 芯片依赖扫描：`Os_SC300` 不再报“芯片库中没有声明此值的芯片”，改为显示待确认项
- [x] 4.4 全量测试通过；在模型相关测试中运行 `tests/core/test_parser_serializer.py`、`tests/core/test_command.py`

## 实施记录（2026-10-25）
- `SC300.yaml` 由修正后的 `Os_Resource_SC300.properties` 导入生成（与资源文件逐键一致）：只有 `Os.OsResourceSubderivative: Os_SC300`，`OsResource` 1 核 / `CORE0` / `SupportProcessor: SC300`，没有引脚和外设。
- `Os_Resource_SC300.properties`（插件主副本 `D:/19_AutosarOS/.../Os_THA6_ASR21` → T1 `Def/plugins/.../resource` 和仓库 `doc/OS`）：原文件与 THA6206 的逐字节相同，现改为 1 核、SC300；`IsrTriggerMethodList` 保留，写 256 项（16 个系统异常 + 240 个外部中断），全为 4（Undefine）：NVIC 没有边沿/电平配置，SC300 分支的模板固定输出 TriggerMethod 0。
- 待确认（`metadata.unconfirmed`）：外部中断数。模板按 Cortex-M3 上限 240，THA6206 HSM 启动文件 `startup_ARMSC300.s` 的向量表只有 73 个外部中断（0-72）。
- 验证：T1 切到 SC300 只写入 Os 选择器，Resource 仍为 `THA6206_LFBGA292`；Os 生成 `OS_SC300`、240/16、`OS_KERNEL_MAX_CORE_NUM 1`、没有 GIC 表。T1 的 Can 模块按 SC300 生成会失败（没有 MCAL 资源），符合“SC300 不运行 MCAL”，HSM 项目不应包含 MCAL 模块。6206/6412 生成结果除时间戳外不变。
- 生成的代码要编译运行还需要 Cortex-M3 内核移植，另立提案。
