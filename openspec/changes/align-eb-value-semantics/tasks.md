## 1. 核实

- [x] 1.1 用 EB 数据模型 jar 核实 INTEGER、FLOAT、BOOLEAN、ENUMERATION、STRING 参数的节点值在 XPath 中的 Java 类型，记入 design.md
- [x] 1.2 记录现状基线：124 个 EB 测试工程、intTest（T2）、t1 的当前输出与 EB 输出的差异清单

## 2. 值类型与转字符串

- [x] 2.1 `xpath_engine`：数字字面量解析为 `float`，算术结果为 `float`
- [x] 2.2 `builtins`：按 design.md 的表调整返回类型（`num:i`、`*toint`、`bit:*` 返回 `int`；`count`、`string-length`、`num:max`/`num:min` 等返回 `float`；`num:f` 返回字符串）
- [x] 2.3 `builtins.to_string`：`bool` 输出 `true`/`false`；XPath 内部的数字转字符串（`string()`、`concat()`）整数值不带 `.0`
- [x] 2.4 测试：表达式输出与 VAR 保存的值与 design.md 中 EB 实测结果逐条一致

## 3. VAR、FOR 与比较

- [x] 3.1 `renderer._handle_var`：数字、布尔、字符串结果转成 EB 字符串保存；节点结果保持现状（整数保留 `int`，见 design.md）
- [x] 3.2 `renderer._handle_for`：循环变量保存为整数字符串
- [x] 3.3 `xpath_engine`：实现 XPath 1.0 比较的公共函数，替换现有各处比较实现
- [x] 3.4 修正以引号开头和结尾的表达式（如 `'0.0' = '0'`）被当作字符串字面量的问题
- [x] 3.5 测试：
  - `$a = $i`（VAR `"0"` 与 FOR `0`）为假；`$a = 0` 为真；`$a = '5'`（VAR `"5"`）为假
  - intTest 的 `PRIORITY0_CORE0_QUEUESIZE` 为 `(2U)`
  - 修正 `test_line_comment_whitespace.py` 中依赖旧行为的用例

## 4. 对照回归

- [ ] 4.1 124 个 EB 测试工程：输出与 EB 一致，不少于基线
- [x] 4.2 intTest（T2）与 EB 逐文件比较：`Os_task_Cfg.h` 一致，其他文件不新增差异
- [x] 4.3 t1 前后输出比较，每处变化都有解释
- [x] 4.4 生成器指纹版本号加一；`verify_fingerprints.py`、`tests/generator`、全部测试通过
