# 跨模块依赖规则

> 此文件由 AI 自动生成，请人工审核后确认。
> 将 `[ ]` 改为 `[x]` 表示确认该规则，改为 `[-]` 表示拒绝。

## 规则说明

| 状态 | 含义 |
|------|------|
| `[ ]` | 待确认 |
| `[x]` | 已确认 - 将用于验证 |
| `[-]` | 已拒绝 - 不使用 |

---

## 发现的依赖关系


<details>
<summary>📊 分析数据 (点击展开)</summary>

**Adc** (6 个参数)
- `AdcPrescale` = 128
- `AdcDevErrorDetect` = True
- `AdcSamplingTime` = 56
- `AdcDmaEnable` = True
- `AdcResolution` = ADC_RESOLUTION_12BIT
- `AdcClockSourceRef` = /McuConfig/Mcu/McuClockConfig/McuClockSource_PLL

**Mcu** (6 个参数)
- `McuDevErrorDetect` = True
- `McuDmaEnable` = True
- `McuClockFrequency` = 80000000
- `McuClockSourceType` = MCU_CLOCK_PLL
- `McuClockFrequency` = 80000000
- `McuClockSourceType` = MCU_CLOCK_PLL

</details>

| # | 状态 | 来源 | 源参数 | 条件 | 目标参数 | 要求 | 原因 |
|---|------|------|--------|------|----------|------|------|
| 1 | [ ] | 📋 定义 | `Adc.AdcClockSourceRef` | != null | `Mcu.McuClockSource` | exists true | 模块定义引用：Adc 通过 AdcClockSourceRef 引用 Mcu |
| 2 | [ ] | 🤖 AI | `Adc.AdcClockSourceRef` | == /McuConfig/Mcu/McuClockConfig/McuClockSource_PLL | `McuClockConfig/McuClockSource_PLL.McuClockFrequency` | > 0 | ADC时钟源依赖于MCU时钟，频率必须有效，否则ADC无法正常工作。 |
| 3 | [ ] | 🤖 AI | `Adc.AdcResolution` | == ADC_RESOLUTION_12BIT | `Adc.AdcSamplingTime` | >= X | 较高分辨率需要更长的采样时间，确保转换精度，避免采样不足。X的具体值取决于硬件特性。 |
| 4 | [ ] | 🤖 AI | `Adc.AdcDmaEnable` | == True | `Mcu.McuDmaEnable` | == True | ADC使用DMA传输数据，需要MCU使能DMA功能，否则数据传输会失败。 |
| 5 | [ ] | 🤖 AI | `Adc.AdcDevErrorDetect` | == True | `Mcu.McuDevErrorDetect` | == True | ADC开启错误检测，建议MCU也开启，便于统一处理错误，提高系统可靠性。 |
| 6 | [ ] | 🤖 AI | `Adc.AdcPrescale` | > 1 | `McuClockConfig/McuClockSource_PLL.McuClockFrequency` | >= Y | ADC分频系数影响时钟频率，MCU主频需满足ADC最小时钟要求，Y的具体值取决于硬件特性。 |

---

## 如何使用

1. 审核上述规则，修改状态标记
2. 保存文件
3. 在工具中执行 **验证跨模块依赖**
