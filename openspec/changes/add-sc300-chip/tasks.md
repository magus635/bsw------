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
- [ ] 3.1 新增 `data/chips/SC300.yaml`：只有 Os 选择器，`ecu_resources.Os` 为 1 核、240/16 个中断，并带 `metadata.unconfirmed`
- [ ] 3.2 修正 Os 插件和 T1 中的 `Os_Resource_SC300.properties`
- [x] 3.3 `THA610X_LFBGA180.yaml` 只增加 `metadata.unconfirmed`，其他数据不改

## 4. 验证
- [ ] 4.1 T1 副本切换到 SC300：只写入 Os 选择器，MCAL 模块的值不变；`ecu:get('OsResource.NumOfCores')` 为 1；能生成代码，且生成的是 SC300 分支（NVIC、240 个中断）
- [ ] 4.2 6206 和 6412 的生成结果逐字节不变
- [ ] 4.3 芯片依赖扫描：`Os_SC300` 不再报“芯片库中没有声明此值的芯片”，改为显示待确认项
- [ ] 4.4 全量测试通过；在模型相关测试中运行 `tests/core/test_parser_serializer.py`、`tests/core/test_command.py`
