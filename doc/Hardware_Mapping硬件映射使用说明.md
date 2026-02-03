# Hardware Mapping 硬件映射功能使用说明

## 文档版本信息

- **版本**: 2.2
- **日期**: 2026年2月
- **适用模块**: 所有AUTOSAR BSW模块（通用机制）
- **更新历史**:
  - 2.2: 完善向导使用指南，添加动态 UI 生成说明
  - 2.1: 添加 EB Tresos Properties 文件加载说明
  - 2.0: 重构为通用数据驱动架构

---

## 目录

1. [功能概述](#1-功能概述)
2. [架构设计](#2-架构设计)
3. [芯片资源模型](#3-芯片资源模型)
4. [从EB Tresos Properties文件加载芯片](#4-从eb-tresos-properties文件加载芯片)
5. [映射规则配置](#5-映射规则配置)
6. [Hardware Mapping向导使用指南](#6-hardware-mapping向导使用指南)
7. [内置映射规则](#7-内置映射规则)
8. [自定义扩展](#8-自定义扩展)
9. [高级用法](#9-高级用法)
10. [最佳实践](#10-最佳实践)

---

## 1. 功能概述

### 1.1 什么是Hardware Mapping

**Hardware Mapping** (硬件映射) 是一种**通用的、数据驱动的**机制，用于将目标芯片的硬件资源自动映射到AUTOSAR BSW模块配置。

### 1.2 设计原则

| 原则 | 说明 |
|------|------|
| **通用性** | 不针对特定模块硬编码，支持任意BSW模块 |
| **数据驱动** | 映射规则通过配置文件定义，无需修改代码 |
| **可扩展** | 用户可自定义芯片资源和映射规则 |
| **动态UI** | 配置界面根据规则自动生成 |

### 1.3 核心价值

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│  芯片资源    │     │   映射规则   │     │ AUTOSAR配置  │
│  (通用模型)  │ ──▶ │  (YAML配置)  │ ──▶ │  (自动生成)  │
└──────────────┘     └──────────────┘     └──────────────┘
```

### 1.4 支持的模块

通过映射规则配置，可支持**任意**AUTOSAR BSW模块，包括但不限于：

| 类别 | 模块 |
|------|------|
| **MCAL** | Port, Dio, Adc, Pwm, Icu, Gpt, Spi, Can, Lin, Eth, Wdg, Mcu, Fls |
| **ECU抽象层** | CanIf, LinIf, EthIf, SpiIf |
| **服务层** | Com, PduR, CanSM, LinSM, EthSM |
| **系统服务** | EcuM, BswM, Dem, Det, Rte |

---

## 2. 架构设计

### 2.1 整体架构

```
┌─────────────────────────────────────────────────────────────────┐
│                        Hardware Mapping System                   │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  ┌─────────────────┐    ┌─────────────────┐    ┌─────────────┐ │
│  │  Chip Database  │    │  Mapping Rules  │    │  UI Generator│ │
│  │  (芯片数据库)   │    │   (映射规则)    │    │  (界面生成) │ │
│  └────────┬────────┘    └────────┬────────┘    └──────┬──────┘ │
│           │                      │                     │        │
│           ▼                      ▼                     ▼        │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │              Generic Resource Mapper (通用映射引擎)          ││
│  │  - 读取芯片资源                                              ││
│  │  - 加载映射规则                                              ││
│  │  - 生成映射动作 (MappingAction)                              ││
│  │  - 应用到配置管理器                                          ││
│  └─────────────────────────────────────────────────────────────┘│
│                              │                                   │
│                              ▼                                   │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │                Configuration Manager                         ││
│  │                (创建容器、设置参数)                           ││
│  └─────────────────────────────────────────────────────────────┘│
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

### 2.2 核心组件

| 组件 | 职责 |
|------|------|
| **ChipDatabase** | 管理芯片定义，提供资源查询 |
| **GenericResourceDef** | 通用资源模型，描述任意类型的硬件资源 |
| **MappingRule** | 映射规则模型，定义资源到配置的转换逻辑 |
| **GenericResourceMapper** | 通用映射引擎，执行映射逻辑 |
| **DynamicUIGenerator** | 根据规则配置生成配置界面 |

### 2.3 数据流

```
1. 用户选择芯片
   │
   ▼
2. ChipDatabase 返回 ChipDefinition (包含通用资源列表)
   │
   ▼
3. 根据芯片资源类型，加载对应的 MappingRule
   │
   ▼
4. DynamicUIGenerator 根据规则生成配置界面
   │
   ▼
5. 用户配置参数
   │
   ▼
6. GenericResourceMapper 根据规则和用户配置生成 MappingAction 列表
   │
   ▼
7. 应用 MappingAction 到 ConfigurationManager
```

---

## 3. 芯片资源模型

### 3.1 通用资源定义

采用通用的资源模型，而非为每种外设定义专门的类：

```python
@dataclass
class GenericResourceDef:
    """通用硬件资源定义"""
    resource_type: str          # 资源类型标识 (如 "can_controller", "gpio_port")
    resource_id: str            # 资源唯一标识 (如 "CAN0", "PORT_A")
    display_name: str           # 显示名称
    properties: Dict[str, Any]  # 资源属性 (灵活的键值对)

    # 示例属性:
    # CAN: {"controller_id": 0, "max_baudrate": 1000000, "supports_fd": True}
    # Port: {"pin_count": 16, "port_index": 0}
    # ADC: {"unit_id": 0, "channel_count": 16, "resolution_bits": 12}
```

### 3.2 芯片定义结构

```python
@dataclass
class ChipDefinition:
    """芯片定义"""
    name: str                                    # 芯片名称
    family: str                                  # 芯片系列
    package: str                                 # 封装类型
    description: str                             # 描述

    # 通用资源字典: {资源类型: [资源列表]}
    resources: Dict[str, List[GenericResourceDef]]

    # 元数据
    metadata: Dict[str, Any]
```

### 3.3 资源类型命名规范

| 资源类型 (resource_type) | 说明 | 典型属性 |
|--------------------------|------|----------|
| `can_controller` | CAN控制器 | controller_id, max_baudrate, supports_fd, mailbox_count |
| `lin_channel` | LIN通道 | channel_id, max_baudrate |
| `eth_controller` | 以太网控制器 | controller_id, max_speed, supports_rgmii |
| `spi_unit` | SPI单元 | unit_id, max_baudrate, supports_dma |
| `gpio_port` | GPIO端口 | port_index, pin_count |
| `gpio_pin` | GPIO引脚 | port, pin, alternate_functions |
| `adc_unit` | ADC单元 | unit_id, channel_count, resolution_bits |
| `adc_channel` | ADC通道 | unit_id, channel_id |
| `pwm_unit` | PWM单元 | unit_id, channel_count |
| `pwm_channel` | PWM通道 | unit_id, channel_id |
| `icu_channel` | ICU通道 | channel_id |
| `gpt_channel` | GPT通道 | channel_id |
| `wdg_unit` | 看门狗单元 | unit_id, timeout_range |
| `intc_source` | 中断源 | vector_number, priority_bits |
| `dma_channel` | DMA通道 | channel_id |
| `clock_source` | 时钟源 | frequency, type |

### 3.4 芯片定义示例 (YAML)

```yaml
# chips/THA6206.yaml
name: "THA6206_LFBGA292"
family: "THA6"
package: "LFBGA292"
description: "Automotive MCU with CAN/LIN/SPI"

resources:
  # CAN控制器
  can_controller:
    - resource_id: "CAN0"
      display_name: "CAN Controller 0"
      properties:
        controller_id: 0
        max_baudrate: 1000000
        supports_fd: true
        mailbox_count: 64
    - resource_id: "CAN1"
      display_name: "CAN Controller 1"
      properties:
        controller_id: 1
        max_baudrate: 1000000
        supports_fd: true
        mailbox_count: 64
    - resource_id: "CAN2"
      display_name: "CAN Controller 2"
      properties:
        controller_id: 2
        max_baudrate: 500000
        supports_fd: false
        mailbox_count: 32

  # GPIO端口
  gpio_port:
    - resource_id: "PORT_A"
      display_name: "Port A"
      properties:
        port_index: 0
        pin_count: 16
    - resource_id: "PORT_B"
      display_name: "Port B"
      properties:
        port_index: 1
        pin_count: 16
    # ... 更多端口

  # ADC单元
  adc_unit:
    - resource_id: "ADC0"
      display_name: "ADC Unit 0"
      properties:
        unit_id: 0
        channel_count: 16
        resolution_bits: 12
        channels: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
    - resource_id: "ADC1"
      display_name: "ADC Unit 1"
      properties:
        unit_id: 1
        channel_count: 16
        resolution_bits: 12
        channels: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

  # SPI单元
  spi_unit:
    - resource_id: "SPI0"
      display_name: "SPI Unit 0"
      properties:
        unit_id: 0
        max_baudrate: 20000000
        supports_dma: true
    - resource_id: "SPI1"
      display_name: "SPI Unit 1"
      properties:
        unit_id: 1
        max_baudrate: 20000000
        supports_dma: true

  # PWM单元
  pwm_channel:
    - resource_id: "PWM0_CH0"
      display_name: "PWM0 Channel 0"
      properties:
        unit_id: 0
        channel_id: 0
    - resource_id: "PWM0_CH1"
      display_name: "PWM0 Channel 1"
      properties:
        unit_id: 0
        channel_id: 1

  # 时钟源
  clock_source:
    - resource_id: "PLL0"
      display_name: "PLL 0"
      properties:
        type: "PLL"
        max_frequency: 200000000
    - resource_id: "XTAL"
      display_name: "Crystal Oscillator"
      properties:
        type: "XTAL"
        frequency: 40000000

metadata:
  cpu_frequency: 200000000
  flash_size: 4194304
  ram_size: 524288
```

---

## 4. 从EB Tresos Properties文件加载芯片

### 4.1 概述

EB Tresos 项目中包含 `.properties` 文件，定义了芯片的硬件资源信息。Hardware Mapping 系统支持自动解析这些文件，将其中的硬件资源定义转换为通用的 `ChipDefinition` 格式。

### 4.2 Properties 文件格式

EB Tresos 的 `.properties` 文件采用标准的 Java Properties 格式：

```properties
# 模块.参数名: 值
Can.MaxModules: 2
Can.MaxNodes: 8
Can.HwUnitNode: _CAN0_ _CAN1_ _CAN2_
Can.FDSupport: true

Port.AvailablePortsID: _0_ _1_ _2_ _3_ _4_ _5_
Port.PinsPerPort: _16_ _16_ _16_ _16_ _16_ _16_

Adc.HwUnitId: _SARADC0_ _SARADC1_
Adc.MaxResolution: 12
Adc.AdcChannels_Adc0: _0_ _1_ _2_ _3_ _4_ _5_ _6_ _7_

Spi.MaxHwUnits: 4
Spi.HwUnitId: _SPI0_ _SPI1_ _SPI2_ _SPI3_
Spi.DmaSupport: true
```

#### 值格式说明

| 格式 | 示例 | 解析结果 |
|------|------|----------|
| 单值 | `MaxModules: 2` | `int: 2` |
| 布尔值 | `FDSupport: true` | `bool: True` |
| 十六进制 | `BaseAddress: 0x40000000` | `int: 1073741824` |
| 下划线包裹列表 | `_CAN0_ _CAN1_ _CAN2_` | `list: ['CAN0', 'CAN1', 'CAN2']` |
| 逗号分隔列表 | `val1, val2, val3` | `list: ['val1', 'val2', 'val3']` |
| C风格后缀 | `(0U)`, `100UL` | 自动去除后缀 |

### 4.3 文件位置

Properties 文件通常位于 EB Tresos 项目的以下位置：

```
ProjectRoot/
├── Def/
│   └── plugins/
│       └── Resource_THA6206/
│           └── resource/
│               └── CortexR52_THA6206_LFBGA292.properties
└── config/
```

或者通过 `TRESOS_PLUGINS_PATH` 环境变量指定的插件目录：

```
$TRESOS_PLUGINS_PATH/
└── Resource_THA6206/
    └── resource/
        └── CortexR52_THA6206_LFBGA292.properties
```

### 4.4 自动提取的资源类型

从 Properties 文件可自动提取以下硬件资源：

| 资源类型 | Properties 模块 | 提取的属性 |
|----------|-----------------|------------|
| `can_resources` | Can | HwUnitNode, FDSupport, MaxNodes |
| `ports` | Port | AvailablePortsID, PinsPerPort |
| `adc_resources` | Adc | HwUnitId, MaxResolution, AdcChannels_AdcX |
| `spi_resources` | Spi | HwUnitId, MaxHwUnits, DmaSupport |
| `intc_sources` | Intc | Sources, MaxInterrupt |

### 4.5 使用方法

#### 方法1: 向导自动检测

Hardware Mapping 向导会自动搜索并加载 Properties 文件：

1. 打开向导后，点击 **"Detect from Project"** 按钮
2. 向导自动搜索项目目录及 `TRESOS_PLUGINS_PATH` 中的 Properties 文件
3. 找到后自动解析并填充芯片定义

#### 方法2: 编程式加载

```python
from pathlib import Path
from autosar_configurator.core.hardware import (
    ChipDatabase,
    TresosPropertiesParser,
    build_chip_from_properties,
    find_properties_files
)

# 方式A: 直接从 Properties 文件构建芯片定义
properties_path = Path("path/to/CortexR52_THA6206_LFBGA292.properties")
chip = build_chip_from_properties(properties_path)
print(f"Chip: {chip.name}")
print(f"CAN Controllers: {len(chip.can_resources)}")
print(f"Ports: {len(chip.ports)}")
print(f"ADC Units: {len(chip.adc_resources)}")

# 方式B: 通过 ChipDatabase 加载
db = ChipDatabase.create_default_database()
chip = db.load_from_properties_file(properties_path)

# 方式C: 自动扫描目录
db = ChipDatabase()
loaded_chips = db.scan_for_properties_files(Path("/path/to/tresos/plugins"))
print(f"Loaded chips: {loaded_chips}")

# 方式D: 从项目自动检测并加载
db = ChipDatabase()
chip = db.detect_and_load_from_project(Path("/path/to/project"))
if chip:
    print(f"Auto-detected chip: {chip.name}")
```

#### 方法3: 详细解析 Properties 内容

```python
from autosar_configurator.core.hardware import TresosPropertiesParser

parser = TresosPropertiesParser()
props = parser.parse_file(Path("path/to/chip.properties"))

# 访问原始属性
print(f"Chip name: {props.chip_name}")
print(f"All properties: {props.properties}")

# 按模块访问
can_props = props.resources.get('Can', {})
print(f"CAN HW Units: {can_props.get('HwUnitNode')}")
print(f"CAN FD Support: {can_props.get('FDSupport')}")

port_props = props.resources.get('Port', {})
print(f"Available Ports: {port_props.get('AvailablePortsID')}")
print(f"Pins Per Port: {port_props.get('PinsPerPort')}")

# 用于 ecu:get() 查询
ecu_resources = parser.get_ecu_resources_dict()
```

### 4.6 与通用资源模型的转换

从 Properties 文件加载的芯片使用传统的 `ChipDefinition` 格式（固定字段）。如需使用通用资源模型，可进行转换：

```python
from autosar_configurator.core.hardware import (
    build_chip_from_properties,
    convert_legacy_chip,
    GenericResourceMapper,
    get_default_rule_loader
)

# 从 Properties 加载传统格式
legacy_chip = build_chip_from_properties(Path("chip.properties"))

# 转换为通用格式
generic_chip = convert_legacy_chip(legacy_chip)
print(f"Resource types: {list(generic_chip.resources.keys())}")
# ['can_controller', 'gpio_port', 'gpio_pin', 'adc_unit', 'spi_unit']

# 使用通用映射器
mapper = GenericResourceMapper(chip=generic_chip, rule_loader=get_default_rule_loader())
available_modules = mapper.get_available_modules()
print(f"Available modules: {available_modules}")
```

### 4.7 Properties 文件示例

以下是一个完整的 Properties 文件示例：

```properties
# CortexR52_THA6206_LFBGA292.properties
# THA6206 Chip Resource Definition

# === CAN Module ===
Can.MaxModules: 1
Can.MaxNodes: 8
Can.HwUnitNode: _CAN0_ _CAN1_ _CAN2_
Can.FDSupport: true
Can.MaxMsgObjects: 64

# === Port Module ===
Port.AvailablePortsID: _0_ _1_ _2_ _3_ _4_ _5_ _6_ _7_
Port.PinsPerPort: _16_ _16_ _16_ _16_ _16_ _16_ _16_ _16_
Port.MaxPinModes: 8

# === ADC Module ===
Adc.HwUnitId: _SARADC0_ _SARADC1_
Adc.MaxResolution: 12
Adc.Resolution: _BITS_10_ _BITS_12_
Adc.AdcChannels_Adc0: _0_ _1_ _2_ _3_ _4_ _5_ _6_ _7_ _8_ _9_ _10_ _11_ _12_ _13_ _14_ _15_
Adc.AdcChannels_Adc1: _0_ _1_ _2_ _3_ _4_ _5_ _6_ _7_ _8_ _9_ _10_ _11_ _12_ _13_ _14_ _15_

# === SPI Module ===
Spi.MaxHwUnits: 4
Spi.HwUnitId: _SPI0_ _SPI1_ _SPI2_ _SPI3_
Spi.DmaSupport: true
Spi.MaxChannels: 128
Spi.MaxJobs: 128
Spi.MaxSequences: 128

# === INTC Module ===
Intc.MaxInterrupt: 256
Intc.MaxPriority: 15
```

### 4.8 类型系统说明

为保证向后兼容性，系统维护两套芯片定义类型：

| 类型 | 用途 | 数据结构 |
|------|------|----------|
| `ChipDefinition` (legacy) | Properties 文件加载、向导界面 | 固定字段: `ports`, `can_resources`, `adc_resources`, `spi_resources`, `intc_sources` |
| `GenericChipDefinition` | YAML 文件加载、通用映射引擎 | 通用字典: `resources: Dict[str, List[GenericResourceDef]]` |

导入方式：
```python
from autosar_configurator.core.hardware import (
    # 传统格式 (用于 Properties 文件)
    ChipDefinition,          # 固定字段版本
    CanResourceDef,
    PortPinDef,
    AdcResourceDef,
    SpiResourceDef,
    IntcSourceDef,

    # 通用格式 (用于 YAML 文件和通用映射)
    GenericChipDefinition,   # 通用资源字典版本
    GenericResourceDef,

    # 转换函数
    convert_legacy_chip,     # legacy -> generic
)
```

---

## 5. 映射规则配置

### 5.1 映射规则模型

```python
@dataclass
class MappingRule:
    """映射规则定义"""
    module: str                      # 目标AUTOSAR模块名
    resource_type: str               # 对应的芯片资源类型
    description: str                 # 规则描述

    # 容器生成规则
    containers: List[ContainerRule]

    # UI配置
    ui_config: UIConfig
```

```python
@dataclass
class ContainerRule:
    """容器生成规则"""
    path_template: str               # 容器路径模板，支持变量替换
    condition: Optional[str]         # 生成条件表达式

    # 参数映射
    parameters: List[ParameterMapping]

    # 子容器
    sub_containers: List['ContainerRule']
```

```python
@dataclass
class ParameterMapping:
    """参数映射规则"""
    name: str                        # AUTOSAR参数名
    source: Optional[str]            # 来源：资源属性路径 (如 "properties.controller_id")
    default: Any                     # 默认值
    transform: Optional[str]         # 值转换表达式
    condition: Optional[str]         # 条件表达式

    # UI配置
    ui_type: str                     # UI组件类型: checkbox, combo, spinbox, text
    ui_options: Dict[str, Any]       # UI选项
```

### 5.2 映射规则配置文件格式 (YAML)

```yaml
# mapping_rules/can.yaml
module: "Can"
resource_type: "can_controller"
description: "CAN Controller mapping rule"

containers:
  - path_template: "CanConfigSet/CanController_{resource.resource_id}"
    parameters:
      - name: "CanControllerId"
        source: "resource.properties.controller_id"
        ui_type: "readonly"

      - name: "CanControllerActivation"
        default: true
        ui_type: "checkbox"
        ui_options:
          label: "Enable Controller"

      - name: "CanControllerBaudRate"
        default: 500000
        ui_type: "combo"
        ui_options:
          label: "Baudrate"
          options: [125000, 250000, 500000, 1000000]
          constraint: "<= resource.properties.max_baudrate"

      - name: "CanControllerFdBaudrateConfig"
        default: false
        condition: "resource.properties.supports_fd == true"
        ui_type: "checkbox"
        ui_options:
          label: "Enable CAN FD"
          enabled_when: "resource.properties.supports_fd"

    sub_containers:
      - path_template: "CanControllerBaudrateConfig/CanControllerBaudrateConfig_Default"
        parameters:
          - name: "CanControllerBaudRateConfigID"
            default: 0
            ui_type: "spinbox"

ui_config:
  title: "CAN Controllers"
  layout: "table"
  columns:
    - field: "enable"
      header: "Enable"
      width: 60
    - field: "resource.resource_id"
      header: "Controller"
      width: 100
    - field: "CanControllerBaudRate"
      header: "Baudrate"
      width: 120
    - field: "CanControllerFdBaudrateConfig"
      header: "FD Support"
      width: 80
```

### 5.3 模板变量

映射规则中支持以下模板变量：

| 变量 | 说明 | 示例 |
|------|------|------|
| `{resource.resource_id}` | 资源ID | `CAN0`, `PORT_A` |
| `{resource.resource_type}` | 资源类型 | `can_controller` |
| `{resource.display_name}` | 显示名称 | `CAN Controller 0` |
| `{resource.properties.xxx}` | 资源属性 | `{resource.properties.controller_id}` |
| `{index}` | 循环索引 (0-based) | `0`, `1`, `2` |
| `{index1}` | 循环索引 (1-based) | `1`, `2`, `3` |
| `{chip.name}` | 芯片名称 | `THA6206_LFBGA292` |
| `{user.xxx}` | 用户配置值 | `{user.baudrate}` |

### 5.4 条件表达式

支持简单的条件表达式：

```yaml
# 布尔条件
condition: "resource.properties.supports_fd == true"
condition: "resource.properties.channel_count > 8"

# 存在性检查
condition: "resource.properties.dma_channel != null"

# 组合条件
condition: "resource.properties.supports_fd and user.enable_fd"
```

### 5.5 值转换表达式

```yaml
# 计算Pin ID: port_index * 16 + pin_number
transform: "resource.properties.port_index * 16 + resource.properties.pin"

# 字符串格式化
transform: "f'Controller_{resource.properties.controller_id}'"

# 条件转换
transform: "'BIG_ENDIAN' if resource.properties.byte_order == 0 else 'LITTLE_ENDIAN'"
```

---

## 6. Hardware Mapping向导使用指南

### 6.1 向导概述

Hardware Mapping 向导采用**数据驱动的动态 UI 生成**机制，界面根据 YAML 映射规则自动构建，无需为每个模块编写硬编码的 UI 代码。

#### 架构设计

```
┌─────────────────────────────────────────────────────────────────┐
│                    Hardware Mapping Wizard                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  ┌─────────────────┐    ┌─────────────────┐    ┌─────────────┐ │
│  │  ChipDatabase   │    │ MappingRuleLoader│    │  Dynamic UI │ │
│  │  (芯片数据库)   │    │   (规则加载器)   │    │  Generator  │ │
│  └────────┬────────┘    └────────┬────────┘    └──────┬──────┘ │
│           │                      │                     │        │
│           ▼                      ▼                     ▼        │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │              GenericResourceMapper (通用映射引擎)            ││
│  └─────────────────────────────────────────────────────────────┘│
│                                                                  │
│  向导页面:                                                       │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐          │
│  │ 芯片选择 │→│ 模块选择 │→│ 资源配置 │→│ 预览应用 │          │
│  │  Page 1  │ │  Page 2  │ │  Page 3  │ │  Page 4  │          │
│  └──────────┘ └──────────┘ └──────────┘ └──────────┘          │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

#### 支持的模块

向导动态加载所有已定义的映射规则，当前支持 **13 个模块**：

| 模块 | 资源类型 | 说明 |
|------|----------|------|
| Adc | adc_unit | ADC 模数转换器 |
| Can | can_controller | CAN 控制器 |
| Dio | gpio_pin | 数字 I/O |
| Eth | eth_controller | 以太网控制器 |
| Gpt | gpt_channel | 通用定时器 |
| Icu | icu_channel | 输入捕获单元 |
| Intc | intc_source | 中断控制器 |
| Lin | lin_channel | LIN 通道 |
| Mcu | clock_source | 微控制器/时钟配置 |
| Port | gpio_port | 端口配置 |
| Pwm | pwm_channel | PWM 通道 |
| Spi | spi_unit | SPI 单元 |
| Wdg | wdg_unit | 看门狗 |

### 6.2 启动向导

**菜单**: `工具 → Hardware Mapping向导`

### 6.3 步骤1: 选择芯片

```
┌─────────────────────────────────────────────────────────────────┐
│ Target Chip                                                      │
├─────────────────────────────────────────────────────────────────┤
│ Chip: [THA6206_LFBGA292 ▼]                                      │
│                                                                  │
│ [Detect from Project]  [Load from File...]                      │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ Chip Information                                                 │
├─────────────────────────────────────────────────────────────────┤
│ THA6206_LFBGA292                                                │
│                                                                  │
│ Family: THA6                                                    │
│ Package: LFBGA292                                               │
│                                                                  │
│ Resources:                                                       │
│ • adc_unit: 2 items                                             │
│ • can_controller: 3 items                                       │
│ • gpio_pin: 128 items                                           │
│ • gpio_port: 8 items                                            │
│ • spi_unit: 3 items                                             │
│                                                                  │
│ Metadata:                                                        │
│ • cpu_frequency: 200000000                                      │
│ • flash_size: 4194304                                           │
│ • ram_size: 524288                                              │
└─────────────────────────────────────────────────────────────────┘
```

#### 芯片加载方式

| 按钮 | 功能 |
|------|------|
| **Detect from Project** | 自动从项目的 Properties 文件或 XDM 文件检测芯片 |
| **Load from File...** | 手动加载 YAML 或 Properties 芯片定义文件 |

芯片来源优先级：
1. 内置芯片数据库 (ChipDatabase)
2. `data/chips/` 目录下的 YAML 文件
3. 项目 Properties 文件自动检测
4. 用户手动加载的文件

### 6.4 步骤2: 选择模块

模块列表**动态生成**，根据芯片拥有的资源类型决定哪些模块可用：

```
┌─────────────────────────────────────────────────────────────────┐
│ Select Modules                                                   │
├─────────────────────────────────────────────────────────────────┤
│ ☑ Adc          (2 adc_unit)                                     │
│ ☑ Can          (3 can_controller)                               │
│ ☑ Dio          (128 gpio_pin)                                   │
│ ☐ Eth          (no eth_controller available)              [灰]  │
│ ☐ Gpt          (no gpt_channel available)                 [灰]  │
│ ☐ Icu          (no icu_channel available)                 [灰]  │
│ ☐ Intc         (no intc_source available)                 [灰]  │
│ ☐ Lin          (no lin_channel available)                 [灰]  │
│ ☑ Mcu          (3 clock_source)                                 │
│ ☑ Port         (8 gpio_port)                                    │
│ ☐ Pwm          (no pwm_channel available)                 [灰]  │
│ ☑ Spi          (3 spi_unit)                                     │
│ ☐ Wdg          (no wdg_unit available)                    [灰]  │
├─────────────────────────────────────────────────────────────────┤
│ Select the modules you want to configure.                        │
│ Modules without matching chip resources are grayed out.          │
└─────────────────────────────────────────────────────────────────┘
```

- **有资源的模块**: 显示资源数量，可选择
- **无资源的模块**: 显示为灰色，不可选择
- **默认选中**: Can, Port, Mcu, Adc (如果有资源)

### 6.5 步骤3: 配置资源

界面根据映射规则的 `ui_config` **动态生成**，支持三种布局模式：

#### 布局模式1: Table (表格布局)

适用于大多数模块 (Can, Adc, Spi, Pwm, Gpt, Icu, Lin, Eth, Wdg, Intc)

```
┌─────────────────────────────────────────────────────────────────┐
│ CAN Controllers                                                  │
├────────┬─────────────────┬─────────────┬────────────────────────┤
│ Enable │ Controller      │ Baudrate    │ FD Support             │
├────────┼─────────────────┼─────────────┼────────────────────────┤
│   ☑   │ CAN Controller 0│ [500000 ▼]  │      ☑                 │
│   ☑   │ CAN Controller 1│ [500000 ▼]  │      ☑                 │
│   ☐   │ CAN Controller 2│ [500000 ▼]  │      ☐  [禁用-不支持FD]│
└────────┴─────────────────┴─────────────┴────────────────────────┘
```

表格列根据 `ui_config.columns` 配置动态生成：
- `readonly` 类型 → 只读文本
- `checkbox` 类型 → 复选框
- `combo` 类型 → 下拉选择框
- `spinbox` 类型 → 数值输入框

#### 布局模式2: List with Options (列表+选项布局)

适用于 Port 模块

```
┌─────────────────────────────────────────────────────────────────┐
│ GPIO Ports                                                       │
├─────────────────────────────────────────────────────────────────┤
│ Select resources to configure:                                   │
│ ┌─────────────────────────────────────────────────────────────┐ │
│ │ ☑ Port A (16 pins)                                          │ │
│ │ ☑ Port B (16 pins)                                          │ │
│ │ ☑ Port C (16 pins)                                          │ │
│ │ ☐ Port D (16 pins)                                          │ │
│ │ ☐ Port E (16 pins)                                          │ │
│ └─────────────────────────────────────────────────────────────┘ │
│                                                                  │
│ ┌─Options─────────────────────────────────────────────────────┐ │
│ │ Default Direction: [PORT_PIN_IN ▼]                          │ │
│ │ Default Mode:      [PORT_PIN_MODE_GPIO ▼]                   │ │
│ └─────────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
```

#### 布局模式3: Default Table (默认表格)

当规则没有定义 `ui_config` 时的回退方案

```
┌─────────────────────────────────────────────────────────────────┐
│ Module Resources                                                 │
├────────┬─────────────────┬──────────────────────────────────────┤
│ Enable │ Resource        │ Properties                           │
├────────┼─────────────────┼──────────────────────────────────────┤
│   ☑   │ RESOURCE_0      │ prop1=val1, prop2=val2, prop3=val3   │
│   ☑   │ RESOURCE_1      │ prop1=val1, prop2=val2, prop3=val3   │
└────────┴─────────────────┴──────────────────────────────────────┘
```

#### 条件控件

某些控件会根据资源属性自动启用/禁用：

```yaml
# 在映射规则中定义条件
- name: "CanControllerFdBaudrateConfig"
  condition: "resource.properties.supports_fd"  # 只有支持FD的控制器才启用
  ui_type: "checkbox"
```

### 6.6 步骤4: 预览与应用

```
Hardware Mapping Preview
============================================================

Chip: THA6206_LFBGA292
Family: THA6
Modules: Can, Port, Adc, Spi

------------------------------------------------------------

## Can (3 can_controller)

  [CREATE] CanConfigSet/CanController_CAN0
    [SET] CanControllerId = 0
    [SET] CanControllerActivation = true
    [SET] CanControllerBaudRate = 500000
    [SET] CanControllerFdBaudrateConfig = true

  [CREATE] CanConfigSet/CanController_CAN1
    [SET] CanControllerId = 1
    [SET] CanControllerActivation = true
    [SET] CanControllerBaudRate = 500000

  Subtotal: 20 actions

## Port (8 gpio_port)

  [CREATE] PortConfigSet/PortContainer_PORT_A
    [SET] PortNumberOfPortPins = 16
  [CREATE] PortConfigSet/PortContainer_PORT_A/PortPin_PORT_A0
    [SET] PortPinId = 0
    [SET] PortPinDirection = PORT_PIN_IN
  ... and 500 more actions

  Subtotal: 528 actions

------------------------------------------------------------
Total actions: 757
```

预览页面显示：
- 芯片信息和选中的模块
- 每个模块将要执行的操作
- 操作类型：`[CREATE]` 创建容器，`[SET]` 设置参数，`[REF]` 设置引用
- 每个模块的操作数量统计
- 总操作数量

### 6.7 UI 组件类型

动态 UI 支持以下组件类型：

| ui_type | 组件 | 用途 | 配置选项 |
|---------|------|------|----------|
| `readonly` | QTableWidgetItem | 只读显示 | - |
| `checkbox` | QCheckBox | 布尔值选择 | `condition` (启用条件) |
| `combo` | QComboBox | 下拉选择 | `options` (选项列表) |
| `spinbox` | QSpinBox | 整数输入 | `min`, `max`, `default` |
| `text` | QLineEdit | 文本输入 | `placeholder`, `default` |

### 6.8 动态 UI 生成流程

```
1. 加载映射规则
   │
   ▼
2. 获取规则的 ui_config
   │
   ├─ layout == "table"
   │   └─ 调用 _create_table_layout()
   │       └─ 根据 columns 生成表头
   │       └─ 为每个资源生成一行
   │       └─ 为每个参数创建对应的控件
   │
   ├─ layout == "list_with_options"
   │   └─ 调用 _create_list_with_options_layout()
   │       └─ 创建资源多选列表
   │       └─ 根据 options 创建额外配置控件
   │
   └─ 无 ui_config
       └─ 调用 _create_default_table()
           └─ 创建通用的 Enable/Resource/Properties 表格
```

### 6.9 用户配置收集

向导会自动收集所有用户配置，格式如下：

```python
user_configs = {
    "Can": {
        "CAN0": {"enable": True, "CanControllerBaudRate": "500000"},
        "CAN1": {"enable": True, "CanControllerBaudRate": "250000"},
        "CAN2": {"enable": False}
    },
    "Port": {
        "PORT_A": {"enable": True},
        "PORT_B": {"enable": True},
        "_option_default_direction": "PORT_PIN_IN",
        "_option_default_mode": "PORT_PIN_MODE_GPIO"
    }
}
```

这些配置会传递给 `GenericResourceMapper.generate_mapping()` 来生成最终的映射动作。

---

## 7. 内置映射规则

### 7.1 规则文件位置

```
autosar_configurator/
└── data/
    └── mapping_rules/
        ├── can.yaml
        ├── port.yaml
        ├── dio.yaml
        ├── adc.yaml
        ├── pwm.yaml
        ├── icu.yaml
        ├── gpt.yaml
        ├── spi.yaml
        ├── lin.yaml
        ├── eth.yaml
        ├── wdg.yaml
        ├── mcu.yaml
        └── intc.yaml
```

### 7.2 Can模块规则

```yaml
# mapping_rules/can.yaml
module: "Can"
resource_type: "can_controller"
description: "Map CAN controllers to Can module configuration"

containers:
  - path_template: "CanConfigSet/CanController_{resource.resource_id}"
    parameters:
      - name: "CanControllerId"
        source: "resource.properties.controller_id"
        ui_type: "readonly"

      - name: "CanControllerActivation"
        default: true
        ui_type: "checkbox"

      - name: "CanControllerBaudRate"
        default: 500000
        ui_type: "combo"
        ui_options:
          options: [125000, 250000, 500000, 1000000]

      - name: "CanControllerFdBaudrateConfig"
        condition: "resource.properties.supports_fd"
        default: false
        ui_type: "checkbox"

ui_config:
  title: "CAN Controllers"
  layout: "table"
  columns:
    - {field: "enable", header: "Enable", width: 60}
    - {field: "resource.resource_id", header: "Controller", width: 100}
    - {field: "CanControllerBaudRate", header: "Baudrate", width: 120}
    - {field: "CanControllerFdBaudrateConfig", header: "FD", width: 60}
```

### 7.3 Port模块规则

```yaml
# mapping_rules/port.yaml
module: "Port"
resource_type: "gpio_port"
description: "Map GPIO ports to Port module configuration"

containers:
  - path_template: "PortConfigSet/PortContainer_{resource.resource_id}"
    parameters:
      - name: "PortNumberOfPortPins"
        source: "resource.properties.pin_count"
        ui_type: "readonly"

    # 为每个引脚生成子容器
    sub_containers:
      - path_template: "PortPin_{resource.resource_id}{pin_index}"
        iterate: "range(resource.properties.pin_count)"
        iterate_var: "pin_index"
        parameters:
          - name: "PortPinId"
            transform: "resource.properties.port_index * 16 + pin_index"
            ui_type: "readonly"

          - name: "PortPinDirection"
            default: "PORT_PIN_IN"
            ui_type: "combo"
            ui_options:
              options: ["PORT_PIN_IN", "PORT_PIN_OUT", "PORT_PIN_INOUT"]

          - name: "PortPinMode"
            default: "PORT_PIN_MODE_GPIO"
            ui_type: "combo"
            ui_options:
              options: ["PORT_PIN_MODE_GPIO", "PORT_PIN_MODE_ALT1", "PORT_PIN_MODE_ALT2"]

ui_config:
  title: "GPIO Ports"
  layout: "list_with_options"
  list_field: "resource"
  options:
    - {name: "default_direction", label: "Default Direction", type: "combo",
       options: ["PORT_PIN_IN", "PORT_PIN_OUT"]}
    - {name: "default_mode", label: "Default Mode", type: "combo",
       options: ["PORT_PIN_MODE_GPIO"]}
```

### 7.4 Adc模块规则

```yaml
# mapping_rules/adc.yaml
module: "Adc"
resource_type: "adc_unit"
description: "Map ADC units to Adc module configuration"

containers:
  - path_template: "AdcConfigSet/AdcHwUnit_{resource.resource_id}"
    parameters:
      - name: "AdcHwUnitId"
        source: "resource.properties.unit_id"
        ui_type: "readonly"

      - name: "AdcPrescale"
        default: 1
        ui_type: "spinbox"
        ui_options:
          min: 1
          max: 256

      - name: "AdcResolution"
        source: "resource.properties.resolution_bits"
        ui_type: "readonly"

    sub_containers:
      - path_template: "AdcGroup_Default/AdcChannel_{channel}"
        iterate: "resource.properties.channels"
        iterate_var: "channel"
        parameters:
          - name: "AdcChannelId"
            source: "channel"
            ui_type: "readonly"

ui_config:
  title: "ADC Units"
  layout: "table"
  columns:
    - {field: "enable", header: "Enable", width: 60}
    - {field: "resource.resource_id", header: "Unit", width: 80}
    - {field: "resource.properties.channel_count", header: "Channels", width: 80}
    - {field: "resource.properties.resolution_bits", header: "Resolution", width: 80}
```

### 7.5 Pwm模块规则

```yaml
# mapping_rules/pwm.yaml
module: "Pwm"
resource_type: "pwm_channel"
description: "Map PWM channels to Pwm module configuration"

containers:
  - path_template: "PwmChannelConfigSet/PwmChannel_{resource.resource_id}"
    parameters:
      - name: "PwmChannelId"
        source: "resource.properties.channel_id"
        ui_type: "readonly"

      - name: "PwmDutycycleDefault"
        default: 0x4000
        ui_type: "spinbox"
        ui_options:
          min: 0
          max: 0x8000
          format: "hex"

      - name: "PwmPeriodDefault"
        default: 1000
        ui_type: "spinbox"
        ui_options:
          min: 1
          max: 65535

      - name: "PwmPolarity"
        default: "PWM_HIGH"
        ui_type: "combo"
        ui_options:
          options: ["PWM_HIGH", "PWM_LOW"]

ui_config:
  title: "PWM Channels"
  layout: "table"
```

### 7.6 Mcu模块规则

```yaml
# mapping_rules/mcu.yaml
module: "Mcu"
resource_type: "clock_source"
description: "Map clock sources to Mcu module configuration"

containers:
  - path_template: "McuModuleConfiguration/McuClockSettingConfig/McuClockReferencePoint_{resource.resource_id}"
    parameters:
      - name: "McuClockReferencePointFrequency"
        source: "resource.properties.frequency"
        default: "resource.properties.max_frequency"
        ui_type: "spinbox"
        ui_options:
          min: 1000000
          max: 400000000

ui_config:
  title: "Clock Configuration"
  layout: "form"
```

---

## 8. 自定义扩展

### 8.1 添加新芯片

1. 在 `data/chips/` 目录创建YAML文件
2. 使用通用资源格式定义硬件资源
3. 重启工具或手动加载

### 8.2 添加新模块映射规则

1. 在 `data/mapping_rules/` 目录创建YAML文件
2. 定义 `resource_type` 对应的芯片资源类型
3. 配置容器模板和参数映射
4. 配置UI生成规则

### 8.3 扩展现有规则

```yaml
# mapping_rules/can_extended.yaml
# 继承基础规则并扩展
extends: "can.yaml"

containers:
  - path_template: "CanConfigSet/CanController_{resource.resource_id}"
    # 追加更多参数
    parameters:
      - name: "CanControllerRxProcessing"
        default: "POLLING"
        ui_type: "combo"
        ui_options:
          options: ["POLLING", "INTERRUPT"]

      - name: "CanControllerTxProcessing"
        default: "POLLING"
        ui_type: "combo"
        ui_options:
          options: ["POLLING", "INTERRUPT"]
```

### 8.4 自定义UI组件

支持的UI组件类型：

| 类型 | 说明 | 配置选项 |
|------|------|----------|
| `readonly` | 只读文本 | - |
| `text` | 文本输入 | placeholder, max_length |
| `spinbox` | 数值输入 | min, max, step, format |
| `combo` | 下拉选择 | options, editable |
| `checkbox` | 复选框 | label |
| `radio` | 单选按钮组 | options |
| `reference` | 引用选择 | target_module, target_container |

---

## 9. 高级用法

### 9.1 编程式使用

```python
from autosar_configurator.core.hardware import (
    ChipDatabase, GenericResourceMapper, MappingRuleLoader
)

# 加载芯片
db = ChipDatabase()
db.load_from_directory(Path("data/chips"))
chip = db.get_chip("THA6206_LFBGA292")

# 加载映射规则
rule_loader = MappingRuleLoader()
rule_loader.load_from_directory(Path("data/mapping_rules"))

# 创建通用映射器
mapper = GenericResourceMapper(chip, rule_loader)

# 获取可用模块
available = mapper.get_available_modules()
# ['Can', 'Port', 'Adc', 'Spi', 'Pwm', 'Mcu']

# 生成映射动作
actions = mapper.generate_mapping(
    module="Can",
    user_config={
        "CAN0": {"enable": True, "CanControllerBaudRate": 500000},
        "CAN1": {"enable": True, "CanControllerBaudRate": 250000},
        "CAN2": {"enable": False},
    }
)

# 应用到配置
applied = mapper.apply_actions(actions, config_manager)
```

### 9.2 批量映射

```python
# 一次性配置多个模块
modules_config = {
    "Can": {
        "CAN0": {"enable": True},
        "CAN1": {"enable": True},
    },
    "Port": {
        "PORT_A": {"enable": True, "default_direction": "PORT_PIN_IN"},
        "PORT_B": {"enable": True, "default_direction": "PORT_PIN_OUT"},
    },
    "Adc": {
        "ADC0": {"enable": True},
    }
}

all_actions = []
for module, config in modules_config.items():
    actions = mapper.generate_mapping(module, config)
    all_actions.extend(actions)

mapper.apply_actions(all_actions, config_manager)
```

### 9.3 导出映射规则

```python
# 将当前配置导出为映射规则
rule = mapper.export_current_config_as_rule(module="Can")
rule.save(Path("my_custom_can_rule.yaml"))
```

---

## 10. 最佳实践

### 10.1 芯片定义

- 使用标准的 `resource_type` 命名
- 属性名使用 snake_case
- 包含足够的元数据 (频率、大小限制等)

### 10.2 映射规则

- 路径模板使用有意义的命名
- 为参数提供合理的默认值
- 使用条件表达式处理可选特性
- UI配置应直观易用

### 10.3 映射流程

1. 先配置基础模块 (Mcu)
2. 再配置底层驱动 (Port, Can, Spi, Adc)
3. 最后配置上层模块 (CanIf, Com)
4. 映射后执行验证

### 10.4 版本管理

- 芯片定义和映射规则应纳入版本控制
- 记录规则修改历史
- 团队共享统一的规则配置

---

## 附录A: 完整的资源类型列表

| 资源类型 | 对应模块 | 典型属性 |
|----------|----------|----------|
| `can_controller` | Can | controller_id, max_baudrate, supports_fd |
| `lin_channel` | Lin | channel_id, max_baudrate |
| `eth_controller` | Eth | controller_id, mac_address |
| `spi_unit` | Spi | unit_id, max_baudrate, supports_dma |
| `gpio_port` | Port | port_index, pin_count |
| `gpio_pin` | Port, Dio | port, pin, alternate_functions |
| `adc_unit` | Adc | unit_id, channel_count, resolution_bits |
| `adc_channel` | Adc | unit_id, channel_id |
| `pwm_channel` | Pwm | unit_id, channel_id, max_frequency |
| `icu_channel` | Icu | channel_id, edge_detection |
| `gpt_channel` | Gpt | channel_id, max_ticks |
| `wdg_unit` | Wdg | unit_id, timeout_ms |
| `fls_sector` | Fls | sector_id, base_address, size |
| `dma_channel` | Dma | channel_id, priority |
| `intc_source` | Intc | vector_number, priority_bits |
| `clock_source` | Mcu | type, frequency |

## 附录B: 表达式语法

### 变量访问
```
resource.resource_id          # 资源ID
resource.properties.xxx       # 资源属性
user.xxx                      # 用户配置值
chip.name                     # 芯片名称
index                         # 循环索引
```

### 运算符
```
+, -, *, /, %                 # 算术运算
==, !=, <, >, <=, >=          # 比较运算
and, or, not                  # 逻辑运算
```

### 内置函数
```
len(list)                     # 列表长度
range(n)                      # 生成序列
format(value, spec)           # 格式化
upper(str), lower(str)        # 大小写转换
```

---

*文档结束*
