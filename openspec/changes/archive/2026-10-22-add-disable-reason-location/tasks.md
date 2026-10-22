## 1. Implementation
- [x] 1.1 定义模型增加 `enable_line`（参数、引用、容器）与 `list_enable_line`（容器）；解析 XDM 时记录 `a:da name="ENABLE"` 的行号
- [x] 1.2 `apply_enable_conditions` 记录失败条件的行号；`DisabledContainer.condition_line`（不参与比较）
- [x] 1.3 控制器把行号与模块定义文件（相对项目根目录、POSIX）组合成位置；对话框在分组原因行与原因汇总中显示
- [x] 1.4 测试：解析行号、预览中的位置、汇总列出多个位置

## 2. Verification
- [x] 2.1 `python -m pytest tests/ -q`（1026 passed, 4 skipped）
- [x] 2.2 T1 副本：五类容器分别显示 `Os.xdm` 第 3885、3989、4118、4168、5179 行，即各 ENABLE 条件 `expr=` 所在行（T1 的标签跨三行，libxml2 报告的是标签结束行，解析时回溯到 `expr=` 行）
