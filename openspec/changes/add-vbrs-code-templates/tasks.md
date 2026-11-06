## 0. Approval
- [ ] 用户确认逐文件范围、MSR 基准和接入设计；此前不得新增产品实现。

## 1. Evidence and rules
- [x] 定位四个已生成样例、项目 vBRS 值配置以及两个 JAR。
- [x] 区分九个静态实现文件；确认示例的 EcuM/SchM Stub 开关为 false。
- [ ] 核对输出类及十种模板的全部输出条件/路径，提取完整规则清单。
- [ ] 核对配置和样例是否一致，记录跨模块输入和全部来源哈希。

## 2. Tests first and context
- [ ] 为布尔、单位、缺省、多行、引用及多核规则先添加失败测试。
- [ ] 实现上下文构建和活动分支校验，补齐多行字符串通路。
- [ ] 为精确输出名、动态文件名、冲突、路径安全和依赖指纹先添加失败测试。
- [ ] 接入显式外部模板包/输出清单，保持原 EB 模板路径和无默认回退行为。

## 3. Per-file templates
- [ ] vBrsCfg.h.tpl
- [ ] vBrs_Lcfg.c.tpl
- [ ] vBrs_Lcfg.h.tpl
- [ ] Makefile.config.generated.tpl
- [ ] EcuM.c.tpl
- [ ] EcuM.h.tpl
- [ ] EcuM_Cbk.h.tpl
- [ ] EcuM_Error.h.tpl
- [ ] EcuM_Generated_Types.h.tpl
- [ ] SchM_Module.h.tpl（按模块 API 名实例化）

## 4. Verification and delivery
- [ ] 四个现有样例受控对照；逐项说明版本/配置不匹配。
- [ ] EcuM/SchM 分支测试及证据覆盖；无原生成基线时明确标注。
- [ ] focused 与 generator 回归通过；记录可用环境和未运行项。
- [ ] 使用说明、支持矩阵、未实现分支和外部模板选择步骤。
- [ ] OpenSpec strict 验证；保护原始 Vector 文件和已有未提交更改。
