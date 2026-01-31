# XPath 语言参考

本文档详细描述了 EB Tresos 兼容模板引擎所支持的 XPath 语言子集及扩展函数库。

---

## 目录

1. [概述](#概述)
2. [XPath 基础语法](#xpath-基础语法)
3. [轴 (Axes)](#轴-axes)
4. [谓词 (Predicates)](#谓词-predicates)
5. [内置函数库](#内置函数库)
   - [节点函数 (node:*)](#节点函数-node)
   - [数值函数 (num:*)](#数值函数-num)
   - [字符串函数 (string:*)](#字符串函数-string)
   - [位操作函数 (bit:*)](#位操作函数-bit)
   - [ECU 资源函数 (ecu:*)](#ecu-资源函数-ecu)
   - [变体函数 (variant:*)](#变体函数-variant)
   - [变量函数 (var:*)](#变量函数-var)
   - [模型函数 (as:*)](#模型函数-as)
   - [EcuC 接口函数 (ecuC:*)](#ecuc-接口函数-ecuc)
   - [XPath 标准函数](#xpath-标准函数)
6. [运算符](#运算符)
7. [使用示例](#使用示例)

---

## 概述

本引擎实现了 XPath 2.0 的一个子集，专门针对 AUTOSAR 配置导航进行了优化。它支持：

- **节点导航**: 在 ConfigurationNode 树结构中进行路径导航
- **函数调用**: 丰富的内置函数库，覆盖节点操作、字符串处理、数值计算等
- **谓词过滤**: 支持条件筛选和索引访问
- **跨模块访问**: 通过 `as:modconf()` 实现跨模块配置查询

---

## XPath 支持程度总结

### 支持级别概览

| 特性类别 | 支持程度 | 说明 |
|----------|----------|------|
| 基本路径导航 | ✅ **完全支持** | 绝对/相对路径、父子导航 |
| 谓词表达式 | ✅ **完全支持** | 索引、比较、存在性检查、算术表达式、函数调用 |
| 函数调用 | ✅ **完全支持** | 60+ 内置函数，支持嵌套 |
| 多层嵌套 | ✅ **支持** | 函数嵌套、路径嵌套 |
| 复杂表达式 | ✅ **增强支持** | 支持谓词中的算术运算和函数调用 |
| XPath 2.0 高级特性 | ✅ **新增支持** | for/if/some/every 表达式、联合运算符、范围表达式 |
| 标准 XPath 函数 | ✅ **完全支持** | sum/avg/min/max/round/floor/ceiling/abs/translate/starts-with/ends-with |
| 轴 (Axes) | ✅ **完全支持** | 全部轴: child/parent/self/descendant/ancestor/following-sibling/preceding-sibling |

### ✅ 完全支持的功能

#### 1. 路径导航

```xpath
# 绝对路径
/Can/CanConfigSet/CanController

# 相对路径
./CanControllerId
../CanControllerDefaultBaudrate
CanController/CanControllerId

# 后代轴 (任意深度)
//CanHardwareObject

# 变量路径导航
$MyNode/ChildParameter
```

#### 2. 多层路径嵌套

```xpath
# 支持: 多级路径导航
as:modconf('Mcu')/McuModuleConfiguration/McuClockSettingConfig/McuClockSettingId

# 支持: 跨模块多级引用
node:value(node:ref(./CanCpuClockRef)/McuClockReferencePointFrequency)

# 支持: 路径 + 谓词组合
CanConfigSet/CanController[1]/CanControllerId
```

#### 3. 函数嵌套调用

```xpath
# 支持: 双层函数嵌套
num:inttohex(num:i($Value), 8)

# 支持: 三层函数嵌套
string:upper(node:name(node:ref(./MyReference)))

# 支持: 函数 + 路径组合
node:value(as:modconf('Mcu')/McuModuleConfiguration/McuClockSettingConfig[1]/McuClockSettingId)

# 支持: 函数参数中的路径
count(as:modconf('Can')/CanConfigSet/CanController/*)

# 支持: 位运算嵌套
bit:or(bit:shl(1, $Bit1), bit:shl(1, $Bit2))
```

#### 4. 谓词表达式

```xpath
# 支持: 数字索引 (1-indexed)
CanController[1]
CanController[last()]

# 支持: 简单比较
CanController[CanControllerId = '0']
CanController[Status != 'disabled']
CanController[Priority > 5]

# 支持: 布尔比较
CanController[CanWakeupSupport = 'true']

# 支持: 存在性检查
CanController[CanWakeupSupport]

# 支持: 属性过滤
Container[@name='Config_0']
```

#### 5. 算术和逻辑运算

```xpath
# 支持: 算术运算
$a + $b
$value * 2
$total div 8
$count mod 4

# 支持: 逻辑运算
$a > 0 and $b < 10
$flag or $backup
not($disabled)

# 支持: 复合条件 (在 IF 语句中)
[!IF "$ControllerCount > 0 and node:exists(./CanFDSupport)"!]
```

#### 6. 特殊路径语法

```xpath
# 支持: 通配符
CanController/*

# 支持: 当前节点
.
node:current()

# 支持: 变量引用
$VariableName
$Node/ChildPath
```

---

### ✅ 新增支持的功能 (已增强)

以下功能已在最新版本中增强支持：

#### 1. 谓词中的复杂表达式

```xpath
# ✅ 现已支持: 谓词中的算术表达式
CanController[CanControllerId > $Base + 1]
CanController[Priority >= $MinPrio * 2]

# ✅ 现已支持: 谓词中的函数调用
CanController[string:length(node:name(.)) > 5]
Container[num:i(Value) > 100]

# ✅ 支持: 函数调用索引
text:split($Path, '/')[num:i($Index)]

# ✅ 支持: 位置函数
Item[position() = 1]
Item[position() - 1 = 0]

# ✅ 支持: 谓词中的变量比较
CanController[CanControllerId = num:i($TargetId)]
CanController[CanControllerId = $TargetId]

# ✅ 支持: 复杂比较表达式
Container[./Priority > $BaseValue + 10]
Item[string:length(./Name) >= 3]
```

#### 2. 函数返回值后的路径

```xpath
# ✅ 支持: as:modconf 后续路径
as:modconf('Mcu')/McuModuleConfiguration

# ✅ 支持: node:ref 后续路径（通过变量）
[!VAR "RefNode" = "node:ref(./MyRef)"!]
[!VAR "Value" = "$RefNode/ChildParam"!]

# ✅ 支持: 函数结果直接续接路径 (新增)
text:split($Path, '/')[1]/ChildNode   字符串结果自动解析为路径
```

当函数返回字符串时（如 `text:split`），引擎会自动尝试将字符串解析为节点路径并继续导航。

---

### ✅ 新增支持的 XPath 轴

#### 完整 XPath 轴 (新增支持)

以下轴已在最新版本中实现：

```xpath
# ✅ 现已支持的轴
ancestor::CanController          祖先轴 - 查找所有祖先节点
ancestor-or-self::Container      祖先或自身轴 - 包含自身
following::Parameter             后续轴 - 文档顺序中的后续节点
following-sibling::Container     后续兄弟轴 - 同级别的后续节点
preceding::Parameter             前导轴 - 文档顺序中的前导节点
preceding-sibling::Container     前导兄弟轴 - 同级别的前导节点
self::*                          自身轴 - 当前节点
descendant-or-self::*            后代或自身轴

# ⚠️ 受限支持
attribute::name                  属性轴 (使用 @name 简写，映射到 short_name)

# ❌ 不支持
namespace::*                     命名空间轴 (AUTOSAR 无命名空间概念)
```

#### 使用示例

```template
[!// 查找当前节点的 CanConfigSet 祖先!]
[!VAR "ConfigSet" = "ancestor::CanConfigSet"!]

[!// 查找后续兄弟控制器!]
[!LOOP "following-sibling::CanController"!]
  /* Following: [!"node:name(.)"!] */
[!/LOOP!]

[!// 查找前导兄弟控制器!]
[!LOOP "preceding-sibling::CanController"!]
  /* Preceding: [!"node:name(.)"!] */
[!/LOOP!]

[!// 查找所有祖先容器!]
[!LOOP "ancestor::*"!]
  /* Ancestor: [!"node:name(.)"!] */
[!/LOOP!]
```

#### 2. ✅ XPath 2.0/3.0 高级特性 (新增支持)

以下高级特性已在最新版本中实现：

```xpath
# ✅ 现已支持: for 表达式
for $x in //Item return $x/Name

# ✅ 现已支持: if 表达式 (内联条件)
if ($a > 0) then 'yes' else 'no'

# ✅ 现已支持: some 量词 (存在性检查)
some $x in //Item satisfies $x/Value > 10

# ✅ 现已支持: every 量词 (全称检查)
every $x in //Item satisfies $x/Valid = 'true'

# ✅ 现已支持: 联合运算符
//CanController | //LinController

# ✅ 现已支持: 范围表达式
1 to 10

# ⚠️ 部分支持: 序列运算符
(1, 2, 3) | (4, 5, 6)                              ⚠️ 仅支持路径联合
```

#### 使用示例

```template
[!// for 表达式: 提取所有控制器名称!]
[!VAR "ControllerNames" = "for $c in //CanController return node:name($c)"!]

[!// if 表达式: 条件值选择!]
[!VAR "Status" = "if ($Count > 0) then 'ENABLED' else 'DISABLED'"!]

[!// some 量词: 检查是否存在任一满足条件的项!]
[!IF "some $c in //CanController satisfies $c/CanWakeupSupport = 'true'"!]
  #define CAN_WAKEUP_SUPPORTED
[!/IF!]

[!// every 量词: 检查所有项是否都满足条件!]
[!IF "every $c in //CanController satisfies node:exists($c/CanControllerId)"!]
  #define CAN_ALL_CONFIGURED
[!/IF!]

[!// 联合运算符: 遍历多种类型!]
[!LOOP "//CanController | //LinController"!]
  /* Controller: [!"node:name(.)"!] */
[!/LOOP!]

[!// 范围表达式: 生成索引序列!]
[!LOOP "1 to 10"!]
  #define INDEX_[!"."!]
[!/LOOP!]
```

#### 3. ✅ 标准 XPath 函数 (已实现)

以下函数已完全实现：

```xpath
# ✅ 聚合函数
sum(//Value)                     求和
avg(//Score)                     平均值 (XPath 2.0)
min(//Priority)                  最小值
max(//Priority)                  最大值

# ✅ 数学函数
round($x)                        四舍五入
floor($x)                        向下取整
ceiling($x)                      向上取整
abs($x)                          绝对值 (XPath 2.0)

# ✅ 字符串函数
translate($s, 'abc', 'xyz')      字符替换
starts-with($s, 'prefix')        前缀检查
ends-with($s, 'suffix')          后缀检查 (XPath 2.0)
format-number($n, '#.##')        数字格式化
```

#### 使用示例

```template
[!// 聚合函数!]
[!VAR "Total" = "sum(//CanController/CanControllerId)"!]
[!VAR "Average" = "avg(//Priority)"!]
[!VAR "LowestPriority" = "min(//Priority)"!]
[!VAR "HighestPriority" = "max(//Priority)"!]

[!// 数学函数!]
[!VAR "Rounded" = "round($FloatValue)"!]
[!VAR "FloorVal" = "floor($Value / 8)"!]
[!VAR "CeilVal" = "ceiling($Size / 4)"!]
[!VAR "AbsValue" = "abs($Offset)"!]

[!// 字符串函数!]
[!IF "starts-with($ModuleName, 'Can')"!]
[!IF "ends-with($FileName, '.h')"!]
[!VAR "Upper" = "translate($s, 'abc', 'ABC')"!]
[!VAR "Formatted" = "format-number($ByteSize, '#,##0.00')"!]
```

#### ⚠️ 受限实现的函数

```xpath
# ⚠️ document() - 外部文档加载 (返回 None，不支持外部文档)
document('external.xml')         ⚠️ 受限

# ⚠️ id() - ID 选择器 (回退到 short_name 匹配)
id('MyElementId')                ⚠️ 受限

# ❌ key() - 键选择器 (需要 XSLT key 定义，始终返回 None)
key('myKey', 'value')            ❌ 不支持
```

#### 4. ✅ 复杂嵌套 (新增支持)

以下复杂嵌套功能已在最新版本中实现：

```xpath
# ✅ 谓词中的谓词 (嵌套谓词)
//Container[Item[Value > 10]]                      现已支持

# ✅ 多重链式谓词
Item[@type='A'][@status='active']                  完全支持

# ✅ 动态路径构造
//{$nodeName}                                      使用变量构造路径
//Container[{$dynamicPredicate}]                   动态谓词
```

#### 使用示例

```template
[!// 嵌套谓词: 找到有高优先级参数的容器!]
[!LOOP "//Container[Parameter[Priority > 10]]"!]
  /* Found: [!"node:name(.)"!] */
[!/LOOP!]

[!// 多重谓词: 找到同时满足多个条件的元素!]
[!LOOP "Item[@enabled='true'][@type='RX']"!]
  /* Matched: [!"node:name(.)"!] */
[!/LOOP!]

[!// 动态路径: 使用变量构造节点名!]
[!VAR "targetName" = "'CanController'"!]
[!LOOP "//{$targetName}"!]
  /* Dynamic found: [!"node:name(.)"!] */
[!/LOOP!]
```

---

### 实际使用示例对比

#### ✅ 可行的复杂表达式

```template
[!// 示例1: 多层函数嵌套!]
[!VAR "HexAddr" = "num:inttohex(bit:or($Base, bit:shl(1, $Offset)), 8)"!]

[!// 示例2: 跨模块引用链!]
[!VAR "ClockRef" = "node:ref(./CanCpuClockRef)"!]
[!VAR "ClockFreq" = "node:value($ClockRef/McuClockReferencePointFrequency)"!]

[!// 示例3: 复杂条件判断!]
[!IF "node:exists(as:modconf('CanIf')) and count(CanController/*) > 0"!]

[!// 示例4: 路径拆分和索引!]
[!VAR "ModuleName" = "text:split(node:path(.), '/')[2]"!]

[!// 示例5: 排序后遍历!]
[!LOOP "node:order(CanController/*, 'CanControllerId')"!]

[!// 示例6: 嵌套引用解析!]
[!VAR "Target" = "node:ref(node:ref(./FirstRef)/SecondRef)"!]

[!// 示例7 (新增): 谓词中的算术表达式!]
[!LOOP "CanController/*[CanControllerId > $BaseId + 1]"!]

[!// 示例8 (新增): 谓词中的函数调用!]
[!LOOP "Container/*[string:length(node:name(.)) >= 5]"!]
```

#### ⚠️ 需要注意的表达式

由于引擎已增强，以下表达式现在可以工作，但某些情况可能需要改写：

```template
[!// ✅ 联合路径 - 现已支持!]
[!LOOP "//CanController | //LinController"!]...[!/LOOP!]

[!// ✅ ancestor 轴 - 现已支持!]
[!VAR "ConfigSet" = "ancestor::CanConfigSet"!]

[!// ✅ 嵌套谓词 - 现已支持!]
[!LOOP "//Container[Item[Value > 10]]"!]
  /* Found: [!"node:name(.)!"!] */
[!/LOOP!]
```

如果上述表达式不工作，可使用以下替代方案：

```template
[!// 替代: 分别遍历联合!]
[!LOOP "//CanController"!]...[!/LOOP!]
[!LOOP "//LinController"!]...[!/LOOP!]

[!// 替代: 使用多级 .. 代替 ancestor!]
[!VAR "ConfigSet" = "../../.."!]
```

---

### 性能注意事项

| 操作 | 性能 | 建议 |
|------|------|------|
| 直接子节点访问 | ⚡ 快速 | 优先使用 |
| 后代轴 `//` | 🐢 较慢 | 避免深度搜索 |
| 多重谓词过滤 | 🐢 较慢 | 减少嵌套层数 |
| 简单函数调用 | ⚡ 快速 | 推荐使用 |
| 深度嵌套函数 | ⚠️ 中等 | 适度使用 |

---

### 调试建议

当 XPath 表达式不工作时：

1. **使用 TRACE 调试**: `[!TRACE "$MyVariable"!]`
2. **分步验证**: 将复杂表达式拆成多个 VAR
3. **检查路径存在性**: 先用 `node:exists()` 验证
4. **查看日志**: 检查 `/tmp/bsw_gen.log` 中的详细信息

### 路径表达式

| 语法 | 描述 | 示例 |
|------|------|------|
| `/` | 根路径（绝对路径） | `/Can/CanConfigSet` |
| `./` | 当前节点（相对路径起始） | `./CanController` |
| `..` | 父节点 | `../CanControllerBaudrateConfig` |
| `//` | 后代轴（任意深度搜索） | `//CanHardwareObject` |
| `.` | 当前节点自身 | `node:value(.)` |
| `*` | 通配符（匹配所有子节点） | `CanController/*` |

### 变量引用

使用 `$` 前缀访问变量：

```xpath
$ControllerIndex
$ModuleName/CanConfigSet
node:value($MyNode)
```

---

## 轴 (Axes)

支持以下 XPath 轴：

| 轴 | 语法 | 描述 |
|----|------|------|
| child | `child::` 或直接写名称 | 子节点（默认轴） |
| parent | `..` | 父节点 |
| descendant | `//` | 所有后代节点 |
| self | `.` | 当前节点 |

### 示例

```xpath
# 子节点访问
CanController/CanControllerId

# 父节点访问
../CanControllerDefaultBaudrate

# 后代节点搜索
//CanHardwareObject[@name='CanRxHwObj_0']

# 当前节点
node:name(.)
```

---

## 谓词 (Predicates)

谓词用于过滤节点集，语法为 `[condition]`。

### 支持的谓词类型

| 类型 | 语法 | 示例 |
|------|------|------|
| 索引 | `[n]` | `CanController[1]` (1-indexed) |
| 最后一个 | `[last()]` | `CanController[last()]` |
| 存在性检查 | `[ParamName]` | `CanController[CanWakeupSupport]` |
| 相等比较 | `[Param = 'value']` | `CanController[CanControllerId = '0']` |
| 不等比较 | `[Param != 'value']` | `CanController[Status != 'disabled']` |
| 数值比较 | `[Param > n]` | `CanController[CanControllerId > 0]` |
| 布尔比较 | `[Param = 'true']` | `CanController[CanWakeupSupport = 'true']` |
| 属性过滤 | `[@attr='value']` | `Container[@name='Config_0']` |
| 位置函数 | `[position() = n]` | `Item[position() = 1]` |

### 谓词中的表达式

谓词支持函数调用：

```xpath
# 使用变量进行索引
text:split($Path, '/')[num:i($Index)]

# 使用函数比较
CanController[CanControllerId = num:i($TargetId)]
```

---

## 内置函数库

### 节点函数 (node:*)

用于操作和查询配置节点。

| 函数 | 签名 | 描述 |
|------|------|------|
| `node:value` | `node:value(node_or_path)` | 获取节点值，支持自动类型转换（Boolean → STD_ON/STD_OFF） |
| `node:name` | `node:name([node])` | 获取节点短名称 (short_name) |
| `node:path` | `node:path([node])` | 获取节点绝对路径 |
| `node:ref` | `node:ref(path_or_node)` | 解析引用，返回目标节点 |
| `node:exists` | `node:exists(path_or_node)` | 检查路径或节点是否存在，返回布尔值 |
| `node:refexists` | `node:refexists(path_or_node)` | 检查引用是否存在且目标有效 |
| `node:refvalid` | `node:refvalid(path_or_node)` | 验证引用有效性，返回 'true'/'false' 字符串 |
| `node:current` | `node:current()` | 获取当前上下文节点 |
| `node:order` | `node:order(nodes, [sort_expr])` | 对节点列表排序 |
| `node:fallback` | `node:fallback(value, default)` | 如果 value 为空则返回 default |

#### node:value 特殊行为

- **Boolean 参数**: 
  - 功能标志 (名称含 Enable/Disable/Dev/Support): 返回 `STD_ON` / `STD_OFF`
  - 运行时布尔: 返回 `TRUE` / `FALSE`
- **Reference 参数**: 返回目标路径字符串

#### 示例

```xpath
[!VAR "ControllerName" = "node:name(.)"!]
[!VAR "ClockFreq" = "node:value(node:ref(./McuClockReferenceRef)/McuClockReferencePointFrequency)"!]
[!IF "node:exists(./CanFDSupport)"!]
  [!IF "node:fallback(./CanControllerPRESDIV, 0) > 0"!]
```

---

### 数值函数 (num:*)

用于数值转换和计算。

| 函数 | 签名 | 描述 |
|------|------|------|
| `num:i` | `num:i(value)` | 转换为整数，支持十六进制 (0x...) |
| `num:inttohex` | `num:inttohex(value, [width])` | 整数转十六进制字符串 (如 0x1F) |
| `num:hextoint` | `num:hextoint(value)` | 十六进制字符串转整数 |
| `num:is_nan` | `num:is_nan(value)` | 检查是否为非数字 |
| `num:isnumber` | `num:isnumber(value)` | 检查是否为数字 |

#### 示例

```xpath
[!VAR "HexAddr" = "num:inttohex($BaseAddr + $Offset, 8)"!]
[!IF "num:isnumber($ConfigValue)"!]
[!VAR "IntValue" = "num:i($StringValue)"!]
```

---

### 字符串函数 (string:*)

用于字符串操作。

| 函数 | 签名 | 描述 |
|------|------|------|
| `string:concat` | `string:concat(s1, s2, ...)` | 连接多个字符串 |
| `string:split` | `string:split(s, delimiter)` | 按分隔符拆分字符串，返回列表 |
| `string:trim` | `string:trim(s)` | 去除首尾空白 |
| `string:upper` | `string:upper(s)` | 转为大写 |
| `string:lower` | `string:lower(s)` | 转为小写 |
| `string:match` | `string:match(s, pattern)` | 正则表达式匹配 |
| `string:length` | `string:length(s)` | 获取字符串长度 |
| `string:contains` | `string:contains(s, substring)` | 检查是否包含子串 |
| `string:substring` | `string:substring(s, start, [length])` | 提取子串 (1-indexed) |
| `string:substring-before` | `string:substring-before(s, delim)` | 获取分隔符前的部分 |
| `string:substring-after` | `string:substring-after(s, delim)` | 获取分隔符后的部分 |
| `string:replace` | `text:replace(s, old, new)` | 替换子串 |

#### text:* 别名

以下函数同时支持 `text:` 命名空间：

- `text:split` → `string:split`
- `text:join` → `string:concat`
- `text:tolower` → `string:lower`
- `text:toupper` → `string:upper`
- `text:replace` → `string:replace`

#### 示例

```xpath
[!VAR "ModuleName" = "text:split($FullPath, '/')[3]"!]
[!VAR "UpperName" = "string:upper($ModuleName)"!]
[!IF "string:contains($ControllerName, 'CAN')"!]
```

---

### 位操作函数 (bit:*)

用于位级操作。

| 函数 | 签名 | 描述 |
|------|------|------|
| `bit:shl` | `bit:shl(value, shift)` | 左移 (`value << shift`) |
| `bit:shr` | `bit:shr(value, shift)` | 右移 (`value >> shift`) |
| `bit:or` | `bit:or(v1, v2)` | 按位或 (`v1 \| v2`) |
| `bit:and` | `bit:and(v1, v2)` | 按位与 (`v1 & v2`) |
| `bit:xor` | `bit:xor(v1, v2)` | 按位异或 (`v1 ^ v2`) |
| `bit:not` | `bit:not(value, [width])` | 按位取反 (默认 32 位) |

#### 示例

```xpath
[!VAR "Mask" = "bit:shl(1, $BitPosition)"!]
[!VAR "Combined" = "bit:or($Flag1, $Flag2)"!]
[!VAR "Extracted" = "bit:and($Register, 0xFF)"!]
```

---

### ECU 资源函数 (ecu:*)

用于查询 ECU 硬件资源配置 (XDM-G)。

| 函数 | 签名 | 描述 |
|------|------|------|
| `ecu:get` | `ecu:get('Module.Param')` | 获取 ECU 资源参数值 |
| `ecu:list` | `ecu:list('Module.Param')` | 获取 ECU 资源参数列表 |

#### 路径格式

`Module.Container.Parameter` 或 `Module.Parameter`

#### 查找顺序

1. 用户提供的 `ecu_resources` 字典
2. 已加载模块配置
3. 模块定义默认值
4. Resource 模块 (回退)

#### 示例

```xpath
[!VAR "MaxControllers" = "ecu:get('Can.MaxControllers')"!]
[!IF "num:i(ecu:get('Can.MaxModules')) > 1"!]
[!LOOP "ecu:list('Adc.HwUnitId')"!]
```

---

### 变体函数 (variant:*)

用于多变体配置管理。

| 函数 | 签名 | 描述 |
|------|------|------|
| `variant:name` | `variant:name()` | 获取当前变体名称 |
| `variant:check` | `variant:check([condition])` | 检查变体条件 (无变体信息时返回 true) |
| `variant:exists` | `variant:exists([name])` | 检查变体是否存在 |
| `variant:size` | `variant:size()` | 获取变体数量 |
| `variant:all` | `variant:all()` | 获取所有变体名称列表 |

#### 兼容性说明

当项目无变体信息时，所有变体判断返回 `true`，确保向后兼容。

#### 示例

```xpath
[!IF "variant:exists('Debug')"!]
[!LOOP "variant:all()"!]
  [!VAR "CurrentVariant" = "variant:name()"!]
[!/LOOP!]
```

---

### 变量函数 (var:*)

用于变量定义检查。

| 函数 | 签名 | 描述 |
|------|------|------|
| `var:defined` | `var:defined('varname')` | 检查变量是否已定义 |
| `var:set` | `var:set('varname', value)` | 设置变量值 (返回空字符串) |

#### 示例

```xpath
[!IF "var:defined('CustomConfig')"!]
  [!VAR "Config" = "$CustomConfig"!]
[!ELSE!]
  [!VAR "Config" = "'default'"!]
[!/IF!]
```

---

### 模型函数 (as:*)

用于跨模块配置访问。

| 函数 | 签名 | 描述 |
|------|------|------|
| `as:modconf` | `as:modconf('ModuleName')` | 获取模块根配置节点 |
| `as:container` | `as:container(path)` | 从当前上下文获取容器 |

#### 示例

```xpath
[!VAR "McuModule" = "as:modconf('Mcu')"!]
[!VAR "ClockConfig" = "as:modconf('Mcu')/McuModuleConfiguration/McuClockSettingConfig"!]
[!LOOP "as:modconf('Can')/CanConfigSet/CanController/*"!]
```

---

### EcuC 接口函数 (ecuC:*)

符合 AUTOSAR EcuC 规范的接口函数。

| 函数 | 签名 | 描述 |
|------|------|------|
| `ecuC:getParamValue` | `ecuC:getParamValue(path)` | 获取参数值 (不存在时抛出错误) |
| `ecuC:getContainers` | `ecuC:getContainers(path)` | 获取容器列表 |
| `ecuC:hasParam` | `ecuC:hasParam(path)` | 检查参数是否存在 (node:exists 别名) |
| `ecuC:getReference` | `ecuC:getReference(path)` | 获取引用目标 |

#### 示例

```xpath
[!VAR "Baudrate" = "ecuC:getParamValue('CanControllerBaudRate')"!]
[!LOOP "ecuC:getContainers('CanHardwareObject')"!]
```

---

### XPath 标准函数

兼容标准 XPath 的函数。

| 函数 | 签名 | 描述 |
|------|------|------|
| `count` | `count(nodeset)` | 计算节点数量 |
| `not` | `not(boolean)` | 逻辑非 |
| `string` | `string(value)` | 转换为字符串 |
| `string-length` | `string-length(s)` | 字符串长度 |
| `concat` | `concat(s1, s2, ...)` | 连接字符串 |
| `contains` | `contains(s, sub)` | 包含检查 |
| `replace` | `replace(s, old, new)` | 替换 |
| `substring` | `substring(s, start, [len])` | 提取子串 |
| `substring-before` | `substring-before(s, delim)` | 分隔符前 |
| `substring-after` | `substring-after(s, delim)` | 分隔符后 |
| `normalize-space` | `normalize-space([s])` | 规范化空白字符 |

---

## 运算符

### 算术运算符

| 运算符 | 描述 | 示例 |
|--------|------|------|
| `+` | 加法 | `$a + $b` |
| `-` | 减法 | `$a - 1` |
| `*` | 乘法 | `$a * 2` |
| `div` | 除法 | `$a div $b` |
| `mod` | 取模 | `$a mod 8` |

### 比较运算符

| 运算符 | 描述 | 示例 |
|--------|------|------|
| `=` | 等于 | `$a = 'value'` |
| `!=` | 不等于 | `$a != 0` |
| `<` | 小于 | `$a < 10` |
| `>` | 大于 | `$a > 0` |
| `<=` | 小于等于 | `$a <= 100` |
| `>=` | 大于等于 | `$a >= 1` |

### 逻辑运算符

| 运算符 | 描述 | 示例 |
|--------|------|------|
| `and` | 逻辑与 | `$a > 0 and $b < 10` |
| `or` | 逻辑或 | `$a = 0 or $b = 0` |
| `not()` | 逻辑非 | `not($flag)` |

---

## 使用示例

### 示例 1: 遍历 CAN 控制器

```template
[!LOOP "as:modconf('Can')/CanConfigSet/CanController/*"!]
  /* Controller: [!"node:name(.)"!] (ID=[!"node:value(./CanControllerId)"!]) */
  [!IF "node:exists(./CanWakeupSupport) and ./CanWakeupSupport = 'true'"!]
    #define [!"string:upper(node:name(.))"!]_WAKEUP_ENABLED
  [!/IF!]
[!/LOOP!]
```

### 示例 2: 跨模块引用

```template
[!VAR "ClockRef" = "node:ref(./CanCpuClockRef)"!]
[!VAR "ClockFreq" = "node:value($ClockRef/McuClockReferencePointFrequency)"!]
#define CAN_CPU_CLOCK    ([!"num:i($ClockFreq)"!]U)
```

### 示例 3: 条件代码生成

```template
[!IF "node:exists(as:modconf('CanIf'))"!]
  #define CAN_CANIF_INTEGRATION   STD_ON
[!ELSE!]
  #define CAN_CANIF_INTEGRATION   STD_OFF
[!/IF!]
```

### 示例 4: 位操作

```template
[!VAR "InterruptMask" = "0"!]
[!LOOP "CanController/*"!]
  [!IF "./CanRxProcessing = 'INTERRUPT'"!]
    [!VAR "InterruptMask" = "bit:or($InterruptMask, bit:shl(1, num:i(./CanControllerId)))"!]
  [!/IF!]
[!/LOOP!]
#define CAN_RX_INTERRUPT_MASK    [!"num:inttohex($InterruptMask, 8)"!]U
```

### 示例 5: 使用 ECU 资源

```template
[!VAR "MaxHwObjects" = "ecu:get('Can.MaxHardwareObjects')"!]
[!IF "num:i(count(CanHardwareObject/*)) > num:i($MaxHwObjects)"!]
  [!ERROR!]Too many hardware objects configured![!/ERROR!]
[!/IF!]
```

---

## 注意事项

1. **索引从 1 开始**: XPath 谓词索引是 1-indexed (`[1]` 是第一个元素)
2. **路径大小写**: 路径匹配支持大小写不敏感的回退
3. **空值处理**: 使用 `node:fallback()` 处理可能为空的值
4. **跨模块访问**: 确保目标模块已加载后再使用 `as:modconf()`
5. **引用解析**: `node:ref()` 会自动解析引用类型节点
6. **布尔语义**: Boolean 参数根据上下文返回不同格式 (STD_ON/OFF 或 TRUE/FALSE)

---

## 相关文档

- [EB Tresos 模板语法](./模板语法.md)
- [AUTOSAR 配置原理](./bsw配置与代码生成原理.md)
- [XSD 与 ARXML 格式](./xsd和arxml.md)
