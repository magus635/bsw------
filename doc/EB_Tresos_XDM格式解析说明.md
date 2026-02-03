# EB Tresos XDM 格式解析说明

## 文档版本信息

- **版本**: 1.0
- **日期**: 2025年10月
- **适用对象**: EB Tresos Studio XDM格式模块定义文件

---

## 目录

1. [XDM格式概述](#1-xdm格式概述)
2. [XDM与ARXML格式对比](#2-xdm与arxml格式对比)
3. [XDM元素结构详解](#3-xdm元素结构详解)
4. [命名空间定义](#4-命名空间定义)
5. [当前项目支持状态](#5-当前项目支持状态)
6. [全面支持XDM所需的扩展](#6-全面支持xdm所需的扩展)
7. [实现建议与优先级](#7-实现建议与优先级)

---

## 1. XDM格式概述

### 1.1 什么是XDM

XDM (XML Data Model) 是 **EB (Elektrobit) Tresos Studio** 使用的专有模块定义格式。它与AUTOSAR标准ARXML格式具有相同的语义目的，但采用不同的XML结构表示。

### 1.2 XDM的主要用途

- **模块定义 (Module Definition)**: 定义BSW模块的容器结构、参数类型、约束条件
- **ECU资源定义**: 通过 `ecu:get()` 和 `ecu:list()` 表达式引用芯片硬件资源
- **验证规则**: 嵌入XPath表达式实现参数值的动态验证
- **默认值计算**: 支持基于XPath的动态默认值计算

### 1.3 典型文件结构

```
project/
├── Def/                    # 定义文件目录
│   ├── Can.xdm            # CAN模块定义
│   ├── Spi.xdm            # SPI模块定义
│   └── ...
├── config/                 # 配置文件目录
│   ├── Can.arxml          # CAN模块配置
│   └── ...
└── generate/               # 生成代码输出目录
```

---

## 2. XDM与ARXML格式对比

### 2.1 核心差异对照表

| 特性 | ARXML (AUTOSAR标准) | XDM (EB Tresos) |
|------|---------------------|-----------------|
| **命名空间** | `http://autosar.org/schema/r4.0` | `http://www.tresos.de/_projects/DataModel2/*` |
| **模块定义** | `<ECUC-MODULE-DEF>` | `<d:chc type="AR-ELEMENT" value="MODULE-DEF">` |
| **容器定义** | `<ECUC-PARAM-CONF-CONTAINER-DEF>` | `<v:ctr type="IDENTIFIABLE">` |
| **参数定义** | `<ECUC-INTEGER-PARAM-DEF>` | `<v:var type="INTEGER">` |
| **引用定义** | `<ECUC-REFERENCE-DEF>` | `<v:ref type="REFERENCE">` |
| **属性表示** | 子元素 (如 `<SHORT-NAME>`) | 属性元素 (如 `<a:a name="...">`) |
| **默认值** | `<DEFAULT-VALUE>` 子元素 | `<a:da name="DEFAULT">` 属性 |
| **约束条件** | `<MIN>`, `<MAX>` 子元素 | `<a:da name="INVALID">` 内的 `<a:tst>` |
| **ECU资源** | 不支持 | `ecu:get()`, `ecu:list()` 表达式 |

### 2.2 结构映射示例

#### ARXML 格式 (INTEGER参数)
```xml
<ECUC-INTEGER-PARAM-DEF>
    <SHORT-NAME>CanControllerId</SHORT-NAME>
    <DESC>
        <L-2 L="EN">Controller ID which is unique in CAN Driver</L-2>
    </DESC>
    <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
    <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SCOPE>ECU</SCOPE>
    <ORIGIN>AUTOSAR_ECUC</ORIGIN>
    <DEFAULT-VALUE>0</DEFAULT-VALUE>
    <MIN>0</MIN>
    <MAX>255</MAX>
</ECUC-INTEGER-PARAM-DEF>
```

#### XDM 格式 (同一INTEGER参数)
```xml
<v:var name="CanControllerId" type="INTEGER">
    <a:a name="DESC" value="EN: Controller ID which is unique in CAN Driver" />
    <a:a name="SCOPE" value="ECU" />
    <a:a name="ORIGIN" value="AUTOSAR_ECUC" />
    <a:a name="SYMBOLICNAMEVALUE" value="true" />
    <a:a name="UUID" value="badb922c-fc6c-4da1-bcd6-3c423d586ebe" />
    <a:da name="DEFAULT" value="0" />
    <a:da name="INVALID" type="Range">
        <a:tst expr="&lt;=255" />
        <a:tst expr="&gt;=0" />
    </a:da>
</v:var>
```

---

## 3. XDM元素结构详解

### 3.1 根结构

```xml
<?xml version="1.0"?>
<datamodel version="7.0"
    xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
    xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
    xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
    xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">

    <d:ctr type="AUTOSAR" factory="autosar">
        <d:lst type="TOP-LEVEL-PACKAGES">
            <d:ctr name="PackageName" type="AR-PACKAGE">
                <d:lst type="ELEMENTS">
                    <d:chc name="ModuleName" type="AR-ELEMENT" value="MODULE-DEF">
                        <!-- 模块定义内容 -->
                    </d:chc>
                </d:lst>
            </d:ctr>
        </d:lst>
    </d:ctr>
</datamodel>
```

### 3.2 核心元素类型

#### 3.2.1 容器元素 (`<v:ctr>`)

```xml
<v:ctr name="ContainerName" type="IDENTIFIABLE">
    <a:a name="DESC" value="EN: Container description" />
    <a:a name="UUID" value="uuid-string" />
    <!-- 子参数和子容器 -->
</v:ctr>
```

**type 属性值**:
- `IDENTIFIABLE`: 可命名容器 (对应 ECUC-PARAM-CONF-CONTAINER-DEF)
- `MODULE-DEF`: 模块定义根容器

#### 3.2.2 列表容器 (`<v:lst>`)

```xml
<v:lst name="CanController" type="MAP">
    <a:da name="MIN" value="1" />
    <a:da name="MAX" type="XPath" expr="num:i(ecu:get('Can.MaxModules')*ecu:get('Can.MaxNodes'))" />
    <v:ctr name="CanController" type="IDENTIFIABLE">
        <!-- 容器模板定义 -->
    </v:ctr>
</v:lst>
```

**type 属性值**:
- `MAP`: 多实例容器列表 (upper-multiplicity > 1)

#### 3.2.3 参数元素 (`<v:var>`)

```xml
<v:var name="ParameterName" type="TYPE">
    <a:a name="DESC" value="..." />
    <a:a name="SCOPE" value="LOCAL|ECU" />
    <a:a name="ORIGIN" value="AUTOSAR_ECUC|VendorName" />
    <a:a name="SYMBOLICNAMEVALUE" value="true|false" />
    <a:a name="OPTIONAL" value="true|false" />
    <a:a name="POSTBUILDVARIANTVALUE" value="true|false" />
    <a:a name="IMPLEMENTATIONCONFIGCLASS" type="IMPLEMENTATIONCONFIGCLASS">
        <icc:v vclass="PreCompile|PostBuild">VariantPostBuild</icc:v>
    </a:a>
    <a:da name="DEFAULT" value="..." />
    <a:da name="RANGE">
        <a:v>VALUE1</a:v>
        <a:v>VALUE2</a:v>
    </a:da>
    <a:da name="INVALID" type="Range">
        <a:tst expr="&lt;=MAX" />
        <a:tst expr="&gt;=MIN" />
    </a:da>
</v:var>
```

**type 属性值对应参数类型**:
| XDM type | ARXML 对应 | Python类型 |
|----------|------------|------------|
| `INTEGER` | ECUC-INTEGER-PARAM-DEF | int |
| `FLOAT` | ECUC-FLOAT-PARAM-DEF | float |
| `BOOLEAN` | ECUC-BOOLEAN-PARAM-DEF | bool |
| `ENUMERATION` | ECUC-ENUMERATION-PARAM-DEF | str (枚举) |
| `STRING` | ECUC-STRING-PARAM-DEF | str |
| `FUNCTION-NAME` | ECUC-FUNCTION-NAME-DEF | str |

#### 3.2.4 引用元素 (`<v:ref>`)

```xml
<v:ref name="CanCpuClockRef" type="REFERENCE">
    <a:a name="DESC" value="EN: Reference to the CPU clock configuration" />
    <a:a name="SCOPE" value="LOCAL" />
    <a:da name="REF" value="ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration/McuClockSettingConfig/McuClockReferencePoint" />
</v:ref>
```

**type 属性值**:
- `REFERENCE`: 普通引用
- `SYMBOLIC-NAME-REFERENCE`: 符号名引用
- `CHOICE-REFERENCE`: 多目标引用

### 3.3 属性元素详解

#### 3.3.1 静态属性 (`<a:a>`)

用于定义固定的元数据属性:

| name值 | 含义 | 示例值 |
|--------|------|--------|
| `DESC` | 描述文本 | `"EN: ..."` |
| `UUID` | 唯一标识符 | UUID字符串 |
| `SCOPE` | 作用域 | `LOCAL`, `ECU` |
| `ORIGIN` | 来源 | `AUTOSAR_ECUC`, `VendorName` |
| `SYMBOLICNAMEVALUE` | 是否符号名 | `true`, `false` |
| `OPTIONAL` | 是否可选 | `true`, `false` |
| `POSTBUILDVARIANTVALUE` | PostBuild变体值 | `true`, `false` |
| `POSTBUILDVARIANTMULTIPLICITY` | PostBuild变体多重性 | `true`, `false` |
| `EDITABLE` | 是否可编辑 | `true`, `false` 或 XPath |
| `LOWER-MULTIPLICITY` | 最小多重性 | `0`, `1` |
| `UPPER-MULTIPLICITY` | 最大多重性 | `1`, `*` |
| `REQUIRES-INDEX` | 需要索引 | `true` |

#### 3.3.2 动态属性 (`<a:da>`)

用于定义可计算或可选择的属性:

| name值 | 含义 | 类型 |
|--------|------|------|
| `DEFAULT` | 默认值 | 静态值或XPath表达式 |
| `MIN` | 列表最小数量 | 整数 |
| `MAX` | 列表最大数量 | 整数或XPath |
| `RANGE` | 枚举值范围 | `<a:v>` 列表或XPath |
| `INVALID` | 验证规则 | `<a:tst>` 列表 |
| `REF` | 引用目标路径 | ASPath字符串 |
| `EDITABLE` | 编辑条件 | XPath表达式 |

#### 3.3.3 验证表达式 (`<a:tst>`)

```xml
<a:da name="INVALID" type="Range">
    <a:tst expr="&lt;=255" />
    <a:tst expr="&gt;=0" />
</a:da>

<a:da name="INVALID" type="XPath">
    <a:tst expr="text:uniq(../../*/CanControllerId, .)"
           false="Duplicated value, CanControllerId must be unique" />
</a:da>
```

### 3.4 ECU资源表达式

XDM特有的硬件资源引用机制:

#### 3.4.1 ecu:get() - 获取单值
```xml
<a:da name="MAX" type="XPath" expr="num:i(ecu:get('Can.MaxModules')*ecu:get('Can.MaxNodes'))" />
```

#### 3.4.2 ecu:list() - 获取列表
```xml
<a:da name="RANGE" type="XPath" expr="ecu:list('Can.HwUnitNode')" />
```

#### 3.4.3 常见ECU资源路径
| 路径 | 含义 | 典型值 |
|------|------|--------|
| `Can.MaxModules` | CAN模块数量 | 2 |
| `Can.MaxNodes` | 每模块节点数 | 8 |
| `Can.HwUnitNode` | 硬件单元列表 | `["CAN_CONTROLLER_00", ...]` |
| `Adc.MaxHwUnits` | ADC单元数量 | 4 |
| `Spi.MaxHwUnits` | SPI单元数量 | 4 |

---

## 4. 命名空间定义

### 4.1 XDM命名空间前缀

```xml
xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
xmlns:ad="http://www.tresos.de/_projects/DataModel2/08/admindata.xsd"
xmlns:cd="http://www.tresos.de/_projects/DataModel2/08/customdata.xsd"
xmlns:f="http://www.tresos.de/_projects/DataModel2/14/formulaexpr.xsd"
xmlns:icc="http://www.tresos.de/_projects/DataModel2/08/implconfigclass.xsd"
xmlns:mt="http://www.tresos.de/_projects/DataModel2/11/multitest.xsd"
xmlns:variant="http://www.tresos.de/_projects/DataModel2/11/variant.xsd"
```

### 4.2 前缀用途说明

| 前缀 | 用途 |
|------|------|
| `d:` | 数据结构元素 (ctr, lst, chc) |
| `v:` | 模式/值元素 (ctr, var, ref, lst) |
| `a:` | 属性元素 (a, da, v, tst) |
| `ad:` | 管理数据 (ADMIN-DATA) |
| `cd:` | 自定义数据 |
| `f:` | 公式表达式 |
| `icc:` | 实现配置类 |
| `mt:` | 多测试 |
| `variant:` | 变体信息 |

---

## 5. 当前项目支持状态

### 5.1 已支持功能

| 功能 | 支持程度 | 相关文件 |
|------|----------|----------|
| XDM文件扫描 | ✅ 完整 | `config_manager.py:DefFileScanner` |
| UI文件选择 | ✅ 完整 | `davinci_main_window.py` |
| ECU资源提取 | ✅ 完整 | `xdm_chip_extractor.py`, `ecu_resource_parser.py` |
| ecu:get/list支持 | ✅ 完整 | `builtins.py` |
| 硬件资源构建 | ✅ 完整 | `xdm_chip_extractor.py` |
| Overlay机制 | ✅ 完整 | `overlay_engine.py` |

### 5.2 部分支持功能

| 功能 | 支持程度 | 说明 |
|------|----------|------|
| 模块定义解析 | ⚠️ 有限 | `EcucDefParser`使用命名空间无关查找，但主要针对ARXML结构 |
| 容器定义解析 | ⚠️ 有限 | 无法识别XDM的 `<v:ctr>` 结构 |
| 参数定义解析 | ⚠️ 有限 | 无法识别XDM的 `<v:var>` 结构 |

### 5.3 未支持功能

| 功能 | 状态 | 说明 |
|------|------|------|
| XDM原生模块定义解析 | ❌ | 需要专门的XDM解析器 |
| XDM验证规则解析 | ❌ | `<a:da name="INVALID">` 中的 `<a:tst>` |
| XDM动态默认值 | ❌ | XPath类型的DEFAULT表达式 |
| XDM编辑条件 | ❌ | `<a:a name="EDITABLE" type="XPath">` |
| XDM列表约束 | ❌ | MIN/MAX的XPath表达式 |
| Implementation Config Class | ❌ | `<icc:v>` 元素解析 |

---

## 6. 全面支持XDM所需的扩展

### 6.1 核心解析器扩展

#### 6.1.1 新增XDM专用解析器

**文件**: `autosar_configurator/core/parser/xdm_def_parser.py`

```python
class XdmDefParser:
    """Parser for EB Tresos XDM Definition files"""

    XDM_NAMESPACES = {
        'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
        'v': 'http://www.tresos.de/_projects/DataModel2/06/schema.xsd',
        'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd',
        'icc': 'http://www.tresos.de/_projects/DataModel2/08/implconfigclass.xsd',
    }

    def parse_module_def_file(self, file_path: Path) -> EcucModuleDef:
        """解析XDM模块定义文件"""
        pass

    def _parse_container_def(self, v_ctr: Element) -> EcucContainerDef:
        """解析 <v:ctr> 元素为容器定义"""
        pass

    def _parse_parameter_def(self, v_var: Element) -> EcucParameterDef:
        """解析 <v:var> 元素为参数定义"""
        pass

    def _parse_reference_def(self, v_ref: Element) -> EcucReferenceDef:
        """解析 <v:ref> 元素为引用定义"""
        pass

    def _parse_list_def(self, v_lst: Element) -> EcucContainerDef:
        """解析 <v:lst> 元素为多实例容器定义"""
        pass
```

#### 6.1.2 需要解析的关键映射

| XDM元素 | 属性/子元素 | 映射到模型字段 |
|---------|-------------|----------------|
| `<v:ctr>` | `name` | `short_name` |
| `<v:ctr>` | `<a:a name="DESC">` | `description` |
| `<v:var>` | `type` | `param_type` (需映射) |
| `<v:var>` | `<a:da name="DEFAULT">` | `default_value` |
| `<v:var>` | `<a:da name="RANGE">` | `literals` (枚举) |
| `<v:var>` | `<a:da name="INVALID">` | `min_value`, `max_value` |
| `<v:lst>` | `<a:da name="MIN">` | `lower_multiplicity` |
| `<v:lst>` | `<a:da name="MAX">` | `upper_multiplicity` |
| `<v:ref>` | `<a:da name="REF">` | `destination_ref` |
| `<a:a name="SCOPE">` | value | `scope` |
| `<a:a name="ORIGIN">` | value | `origin` |
| `<icc:v>` | vclass/mclass | `config_class` |

### 6.2 验证规则解析

#### 6.2.1 验证表达式模型

**文件**: `autosar_configurator/core/model/validation_model.py`

```python
@dataclass
class XdmValidationRule:
    """XDM验证规则模型"""
    rule_type: str  # "Range", "XPath"
    expression: str  # XPath或比较表达式
    error_message: str  # false属性值

@dataclass
class XdmDynamicAttribute:
    """XDM动态属性模型"""
    name: str  # DEFAULT, RANGE, INVALID, EDITABLE, MIN, MAX
    attr_type: str  # "static", "XPath", "Range"
    static_value: Any  # 静态值
    xpath_expr: str  # XPath表达式
    tests: List[XdmValidationRule]  # 验证测试列表
```

#### 6.2.2 验证表达式解析器

```python
class XdmValidationParser:
    """解析XDM验证表达式"""

    def parse_invalid_attribute(self, da_elem: Element) -> List[XdmValidationRule]:
        """解析 <a:da name="INVALID"> 内的验证规则"""
        pass

    def parse_range_tests(self, tests: List[Element]) -> Tuple[Optional[int], Optional[int]]:
        """从 <a:tst expr="<=X"> 提取min/max值"""
        pass
```

### 6.3 动态表达式求值

#### 6.3.1 XPath表达式扩展

需要在现有 `xpath_engine.py` 中添加对XDM特有XPath函数的支持:

| 函数 | 用途 | 示例 |
|------|------|------|
| `node:exists(path)` | 检查节点存在 | `node:exists(../CanFDSupport)` |
| `node:value(path)` | 获取节点值 | `node:value(../CanControllerId)` |
| `node:ref(path)` | 解引用 | `node:ref(../CanCpuClockRef)` |
| `node:path(node)` | 获取路径 | `node:path(.)` |
| `node:fallback(expr, default)` | 回退值 | `node:fallback(., 0)` |
| `node:current()` | 当前节点 | `node:current()/../@index` |
| `text:uniq(list, value)` | 唯一性检查 | `text:uniq(../../*/Id, .)` |
| `text:split(str)` | 字符串分割 | `text:split('1 2 3')` |

### 6.4 Implementation Config Class支持

#### 6.4.1 配置类模型扩展

```python
@dataclass
class ImplementationConfigClass:
    """实现配置类"""
    variant_class: str  # "PreCompile", "Link", "PostBuild"
    config_variant: str  # "VariantPreCompile", "VariantPostBuild"
    multiplicity_class: Optional[str] = None  # mclass属性
```

#### 6.4.2 解析ICC元素

```xml
<a:a name="IMPLEMENTATIONCONFIGCLASS" type="IMPLEMENTATIONCONFIGCLASS">
    <icc:v vclass="PreCompile">VariantPostBuild</icc:v>
    <icc:v mclass="PostBuild">VariantPostBuild</icc:v>
</a:a>
```

### 6.5 参考路径 (ASPath) 解析

XDM使用特殊的ASPath格式表示引用目标:

```
ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration/McuClockSettingConfig/McuClockReferencePoint
```

需要解析器将此转换为标准AUTOSAR定义引用路径。

### 6.6 统一解析器工厂

#### 6.6.1 自动格式检测

**文件**: `autosar_configurator/core/parser/def_parser_factory.py`

```python
class DefParserFactory:
    """定义文件解析器工厂"""

    @staticmethod
    def get_parser(file_path: Path) -> Union[EcucDefParser, XdmDefParser]:
        """根据文件内容自动选择解析器"""
        content = file_path.read_text(encoding='utf-8')

        if 'tresos.de/_projects/DataModel2' in content:
            return XdmDefParser()
        elif 'autosar.org/schema' in content:
            return EcucDefParser()
        else:
            # 根据扩展名回退
            if file_path.suffix.lower() == '.xdm':
                return XdmDefParser()
            return EcucDefParser()
```

---

## 7. 实现建议与优先级

### 7.1 实现优先级

| 优先级 | 功能 | 工作量 | 依赖 |
|--------|------|--------|------|
| **P0** | XdmDefParser基础框架 | 3天 | 无 |
| **P0** | v:ctr/v:var/v:ref解析 | 2天 | P0 |
| **P0** | DefParserFactory集成 | 1天 | P0 |
| **P1** | a:da属性解析 (DEFAULT/RANGE) | 2天 | P0 |
| **P1** | v:lst列表容器解析 | 1天 | P0 |
| **P2** | INVALID验证规则解析 | 2天 | P1 |
| **P2** | ICC配置类解析 | 1天 | P0 |
| **P3** | 动态XPath DEFAULT求值 | 3天 | XPath引擎 |
| **P3** | EDITABLE条件求值 | 2天 | XPath引擎 |
| **P4** | 完整验证规则执行 | 3天 | P2, XPath引擎 |

### 7.2 测试用例建议

```python
# tests/core/test_xdm_parser.py

def test_parse_xdm_module_def():
    """测试XDM模块定义解析"""
    parser = XdmDefParser()
    module_def = parser.parse_module_def_file(Path("eb_test_templates/Can.xdm"))

    assert module_def.short_name == "Can"
    assert "CanConfigSet" in [c.short_name for c in module_def.containers]

def test_parse_xdm_parameter_types():
    """测试XDM参数类型映射"""
    # INTEGER, BOOLEAN, ENUMERATION, FLOAT, STRING, FUNCTION-NAME
    pass

def test_parse_xdm_validation_rules():
    """测试XDM验证规则解析"""
    pass

def test_parse_xdm_ecu_resources():
    """测试ECU资源表达式提取"""
    pass

def test_xdm_arxml_unified_model():
    """测试XDM和ARXML解析结果的模型一致性"""
    pass
```

### 7.3 集成检查清单

- [ ] XdmDefParser实现并通过单元测试
- [ ] DefParserFactory自动格式检测
- [ ] workspace_manager.py使用工厂模式
- [ ] davinci_main_window.py透明支持XDM加载
- [ ] 现有ARXML功能回归测试通过
- [ ] 文档更新 (CLAUDE.md, 用户手册)

---

## 附录A: XDM示例片段

### A.1 完整的INTEGER参数定义

```xml
<v:var name="CanControllerId" type="INTEGER">
    <a:a name="DESC" value="EN: This parameter provides the controller ID which is unique in a given CAN Driver." />
    <a:a name="POSTBUILDVARIANTVALUE" value="false"/>
    <a:a name="IMPLEMENTATIONCONFIGCLASS" type="IMPLEMENTATIONCONFIGCLASS">
        <icc:v vclass="PreCompile">VariantPostBuild</icc:v>
    </a:a>
    <a:a name="ORIGIN" value="AUTOSAR_ECUC" />
    <a:a name="SCOPE" value="ECU" />
    <a:a name="SYMBOLICNAMEVALUE" value="true" />
    <a:a name="UUID" value="badb922c-fc6c-4da1-bcd6-3c423d586ebe" />
    <a:da name="DEFAULT" type="XPath" expr="node:fallback(node:current()/../@index, num:i(1))" />
    <a:da name="RANGE" type="XPath">
        <a:tst expr="(node:fallback(.,1) &gt;= 0) and (node:fallback(.,1) &lt; num:i(count(node:fallback(node:current()/../../*, 1 ))))"
               false="Value out of range: must be in range 0 to N-1" />
        <a:tst expr="text:uniq(node:fallback(../../*/CanControllerId, text:split('1 2 3')), node:fallback(.,1))"
               false="Duplicated value, CanControllerId must be unique" />
    </a:da>
    <a:da name="INVALID" type="Range">
        <a:tst expr="&lt;=255" />
        <a:tst expr="&gt;=0" />
    </a:da>
</v:var>
```

### A.2 带ECU资源的列表容器

```xml
<v:lst name="CanController" type="MAP">
    <a:da name="MIN" value="1" />
    <a:da name="MAX" type="XPath" expr="num:i(ecu:get('Can.MaxModules')*ecu:get('Can.MaxNodes'))" />
    <v:ctr name="CanController" type="IDENTIFIABLE">
        <a:a name="REQUIRES-INDEX" value="true"/>
        <!-- 子参数... -->
    </v:ctr>
</v:lst>
```

### A.3 带条件编辑的引用

```xml
<v:ref name="CanControllerDefaultBaudrate" type="REFERENCE">
    <a:a name="DESC" value="EN: Reference to baudrate configuration" />
    <a:a name="POSTBUILDVARIANTVALUE" value="true" />
    <a:da name="REF" value="ASPathDataOfSchema:/AUTOSAR/EcucDefs/Can/CanConfigSet/CanController/CanControllerBaudrateConfig" />
    <a:da name="INVALID" type="XPath"
          expr="(contains(node:path(node:ref(.)),node:path(../CanControllerBaudrateConfig))) and (node:refvalid(.))"
          false="The configured node does not exist or may not be referenced." />
</v:ref>
```

---

*文档结束*
