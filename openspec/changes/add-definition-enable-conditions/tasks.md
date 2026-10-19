## 1. 定义解析

- [x] 1.1 定义模型：容器、参数、引用定义增加 `enable_expr`；容器定义增加 `list_enable_expr`（来自 `v:lst`）与 `in_list`
- [x] 1.2 `ecuc_def_parser`：读取 `v:ctr`、`v:lst`、`v:chc`、`v:var`、`v:ref` 上的 `<a:da name="ENABLE" type="XPath">`，保存 `expr`（没有 `expr` 时取第一个 `a:tst/@expr`），并按 `true`/`false` 属性映射结果；固定值不作为条件；参数、引用所在列表的条件归到参数、引用本身
- [x] 1.3 测试：`Os_THA6_ASR21` 定义解析后，44 个条件都挂在正确的定义上，列表级与项级分开（`test_real_os_definition_conditions`，需设置 `OS_THA6_DEFINITION_XDM`）

## 2. 生成

- [x] 2.1 新增启用条件计算 `generator/eb/enable_conditions.py`：
  - 输入为已载入所有模块的符号表，按文档顺序自上而下计算。
  - 条件为假时，移除节点与子树，清理别名，重建路径索引。
  - 算不出来时按启用处理，并记录警告，每个表达式只报一次。
  - 计算期间，单个子容器的父节点指向它所在的容器。
- [x] 2.2 接入生成流程：在 `EBTemplateEngine.render` 中，所有模块载入后、渲染前执行；警告进入 `CodeGenerator.warnings` 和日志
- [x] 2.3 生成器指纹加入版本号（`CodeGenerator.GENERATOR_VERSION`）
- [x] 2.4 测试 `tests/generator/test_enable_conditions.py`，覆盖：
  - 列表级条件（SC1、SC2）
  - 多值引用列表
  - 互斥引用
  - 单个子容器中的反向映射
  - 跨模块条件
  - 计算失败时按启用处理并给出警告
  - 固定值不作为条件
  - 无条件的模块不变
  - 指纹版本

## 3. EPC 导出

- [x] 3.1 序列化器 `export_epc(..., skip=)` 跳过集合中的容器、参数值和引用值；不传 `skip` 时输出逐字节不变
- [x] 3.2 导出控制器：`ProjectController._disabled_items` 为整个项目构建配置树、计算条件，再通过 `WorkspaceManager.export_epc(skip=)` 交给序列化器
- [x] 3.3 测试：
  - 关闭项不出现在导出的 EPC 里。
  - 项目保存的 ARXML 仍保留这些值。
  - 条件重新为真后，这些值重新导出。

## 4. 对照验证

- [x] 4.1 T2 项目试跑生成，与 EB 输出比较：
  - 60 个文件中 59 个一致，时间保护相关的 4 个文件已与 EB 一致。
  - 剩余 `Os_task_Cfg.h` 中 `PRIORITY0_CORE0_QUEUESIZE` 一行（见 design.md，与本变更无关）。
- [x] 4.2 T2 项目导出 EPC，与 EB 的 EPC 比较：
  - `OsTaskTimingProtection_0` 与 `OsApplicationHooks` 三个参数都不再导出，原因是反向映射，已写回 design.md。
  - 剩余差异只有选择容器子容器的命名（已知，不在本变更范围）。
- [x] 4.3 测试：
  - `tests/core/test_parser_serializer.py`、`tests/core/test_command.py`、`tests/generator` 与全部非 UI 测试通过：794 个通过，4 个跳过。
  - UI 测试（offscreen）通过：127 个。
  - t1 项目生成结果与改动前相同，只多出 `scatter.scat`。
