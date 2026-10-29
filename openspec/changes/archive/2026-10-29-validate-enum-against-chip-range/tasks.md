## 1. 实现

- [x] 1.1 `EnumerationValidationRule.validate` 接收 `project_context`，取 `ecu_resources` 和 `selected_chip`（引擎已按签名传入 `project_context`）
- [x] 1.2 范围来源：`range_expr` 是单纯 `ecu:list('X.Y')` 且资源里有该键（先精确、再忽略大小写）且列表非空时，用芯片范围；否则沿用 `param_def.literals`
- [x] 1.3 芯片范围的错误消息写明键和芯片，`suggested_fix` 列出可选值；多值参数逐个检查

## 2. 测试

- [x] 2.1 `tests/core/test_enum_chip_range_validation.py`：值不在芯片范围报错误，消息含键名和芯片名
- [x] 2.2 值在芯片范围内不报；解析时留下的旧 `literals` 与当前芯片不同，以当前芯片为准
- [x] 2.3 不检查的情况：无工程上下文、复杂表达式、资源缺键、列表为空，结果与改动前一致
- [x] 2.4 键名大小写不同、值为逗号分隔字符串时仍能匹配
- [x] 2.5 厂商 THA6412 定义 + 示例配置：对 THA6412 无新增报告；对 THA610X 报出 `Adc.HwUnitId` 的 `SARADC8`

## 3. 验证

- [x] 3.1 全量测试通过（`QT_QPA_PLATFORM=offscreen python -m pytest tests -q`：1247 passed, 5 skipped）
- [x] 3.2 三套厂商示例配置对各自芯片均无新增错误（经 `ValidationEngine` 全部默认规则跑全部模块：芯片范围错误 0；THA6412 配置放到 THA610X 上报 93 条。每套另有 1 条已有的 Can `CanIcomConfig` 个数错误，与本变更无关）
