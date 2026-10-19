## Context

EB 定义里 `ENABLE` 的写法：

```xml
<v:lst name="OsTaskTimingProtection" type="MAP">
  <a:da name="MAX" value="1"/>
  <a:da name="ENABLE" type="XPath"
        expr="(../../../OsOS/OsScalabilityClass = 'SC4') or (../../../OsOS/OsScalabilityClass = 'SC2')"
        true="true" false="false"/>
  <v:ctr name="OsTaskTimingProtection" type="IDENTIFIABLE"> ... </v:ctr>
</v:lst>

<v:ref name="OsResourceCoreRef" type="REFERENCE">
  <a:da name="ENABLE" type="XPath"
        expr="(../OsResourceProperty != 'LINKED') or (../OsResourceLinkedToResScheduler = 'true')"/>
</v:ref>
```

表达式以带条件的节点本身为上下文，`..` 是它在数据树里的父节点：

- 列表 `OsTaskTimingProtection` 的父节点是 Task0，再往上是列表 `OsTask`，然后是模块 Os。
- 参数的父节点是它所在的容器实例。

本工具的配置树（`OverlayEngine`）已经按这个结构建立：每个列表对应一个包装节点（`is_wrapper=True`），实例挂在它下面。所以 EB 的相对路径不用改写，就能用现有的 `XPathEngine` 和内置函数直接计算。

## Goals / Non-Goals

- Goals：生成和 EPC 导出时，条件为假的项与 EB 一样不出现；不丢失用户数据；算不出来的条件不改变现有行为。
- Non-Goals：界面显示；`EDITABLE`、`INVALID` 等其他 XPath 属性；导入时根据条件删除数据。

## Decisions

- **Decision：在配置树上计算，不在定义解析时计算。**
  - 条件取决于配置值（扩展等级、资源属性等），同一个定义在不同配置下结果不同，所以解析定义时只保存表达式。
  - 现有的 `MAX`、`DEFAULT` 等 XPath 属性在解析时用静态解析器计算；`ENABLE` 不能这样处理。
- **Decision：所有模块载入以后统一计算，按文档顺序自上而下。**
  - 条件可以跨模块，例如经 `node:ref` 读取 EcuC 的核心定义，所以要等项目的所有模块都在符号表里以后再计算。
  - 自上而下计算时，父节点被移除后，子树里的条件不再计算，这和 EB 的结果一致。
  - 同一层的兄弟节点按配置树的顺序依次计算，结果是确定的。前面的兄弟被移除后，后面的条件再引用它会得到空值；EB 里引用关闭项的结果同样是空。
- **Decision：移除节点，而不是加一个"关闭"标记。**
  - 模板里 `node:exists`、`count(*)`、`LOOP`、`node:value` 等几十处写法都应该"看不到"关闭项。
  - 逐个函数判断标记容易漏，从树里摘掉最直接。
  - 符号表的路径索引一并删除。
- **Decision：EPC 导出复用同一套计算。**
  - 导出前为项目构建配置树并计算条件，得到关闭项的配置对象集合，序列化时跳过这些对象。
  - 这一步放在 UI 导出控制器里组装，核心层的序列化器只接受一个可选的"跳过集合"，核心层不依赖生成器。
- **Decision：算不出来就按启用处理，并发出警告。**
  - 定义里可能有本工具还没实现的函数。此时如果按"关闭"处理，可能悄悄删掉用户需要的代码；按"启用"处理就是现在的行为。
  - 警告写入生成结果，满足项目"不静默回退"的约定。
- **Decision：指纹加版本号。**
  - 指纹现在只覆盖配置和模板，这次改动不改变指纹的输入，但会改变生成的输出。
  - 加入一个常量版本号，保证升级后第一次生成会全部重新生成。

- **Decision（实施中确定）：固定值不是条件。**
  - EcuC 定义里有 10 处 `<a:da name="ENABLE" value="false"/>`，例如 `EcucHardware`。它们是可选项新建时的初始状态。
  - 值文件里的 `<a:a name="ENABLE" value="false"/>` 才表示关闭，XDM 导入时已经跳过。
  - 如果把固定值当作条件，`EcucHardware` 会被关闭，Os 引用的核心定义会全部失效。
- **Decision（实施中确定）：按 `true`/`false` 属性映射结果。**
  - `OsAppErrorHook` 等三个钩子参数写的是 `true="false" false="true"`：表达式为真时关闭。SC1 下表达式为真，所以 EB 关闭了它们。
  - 这正是 design 原先列出的待核实差异的原因。
- **Decision（实施中确定）：单个子容器的父节点。**
  - 配置树给每个子容器实例都加了一层包装节点。在 EB 里，只有列表（`v:lst`）的项才有这一层；单个 `v:ctr` 直接挂在父容器下，条件里的 `..` 也是按这个结构写的。
  - 计算条件期间，单个子容器实例的父指针临时指向包装节点的父节点，算完立即恢复，不影响模板。
  - 定义模型新增 `in_list` 标记，用来区分单个容器和列表。

## Risks / Trade-offs

- **XPath 兼容性不足导致误判。** 一旦误判为"关闭"，会少生成代码。
  - 缓解：用 `Os_THA6_ASR21` 定义的 44 个条件做回归测试，在 SC1、SC2、SC3、SC4 等配置下与预期结果比较；对照 T2 项目和 EB 的输出。
- **性能。** 每次生成都要多走一遍配置树。条件只有几十处，每处按实例计算，开销可以忽略；实施时用 T2 实测。
- **已查清：** T2 里 EB 的 EPC 没有 `OsApplicationHooks` 的三个参数，原因是反向映射（见上文 Decisions）。按映射计算后，结果与 EB 一致。

- **待核实的差异 2。** T2 的 `Os_task_Cfg.h` 中 `PRIORITY0_CORE0_QUEUESIZE`，EB 为 2，本工具为 3。
  - 多出的 1 来自 `OsResource_0`：它是 `LINKED`、链接到 `RES_SCHEDULER`，属于核 0，宏算出的天花板优先级为 0，于是被计入优先级 0。
  - EB 的 EPC 里这个资源的数据与本工具相同，按模板逻辑 EB 也应该计入。原因还没查到。
  - 实施启用条件后先复核；如果仍有差异，单独排查，不在本变更里猜测修改。
  - 复核结果：启用条件实施后差异仍在，确认与本变更无关，留待单独排查。

## Migration Plan

- 不改项目文件格式，也不需要迁移数据。
- 升级后第一次生成会重新生成所有模块。
- 回滚：去掉条件计算这一步，结果恢复为当前行为。

## Open Questions

- 选择容器（`v:chc`）中未选中的分支本来就不生成，选择容器本身带条件的情况，按其他容器同样处理。实施时如果遇到有歧义的情况，再在这里补充。
