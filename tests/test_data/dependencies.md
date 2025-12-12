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
| 1 | [ x ] | 📋 定义 | `Adc.AdcClockSourceRef` | != null | `Mcu.McuClockSource` | exists true | 模块定义引用：Adc 通过 AdcClockSourceRef 引用 Mcu |
| 2 | [x] | 🤖 AI | `Adc.AdcClockSourceRef` | == /McuConfig/Mcu/McuClockConfig/McuClockSource_PLL | `McuClockConfig/McuClockSource_PLL.McuClockSourceType` | == MCU_CLOCK_PLL | ADC时钟源必须与MCU配置的时钟源类型一致，否则ADC无法正常工作。 |
| 3 | [] | 🤖 AI | `Adc.AdcResolution` | == ADC_RESOLUTION_12BIT | `Adc.AdcSamplingTime` | >= 12 | 较高分辨率需要更长的采样时间，确保ADC转换精度，避免采样时间不足导致转换错误。 |
| 4 | [ x] | 🤖 AI | `Adc.AdcDmaEnable` | == True | `Mcu.McuDmaEnable` | == True | ADC使用DMA传输时，MCU必须启用DMA功能，否则DMA传输无法进行，数据无法正确传输。 |
| 5 | [ ] | 🤖 AI | `Adc.AdcDevErrorDetect` | == True | `Mcu.McuDevErrorDetect` | == True | ADC开启错误检测时，MCU也应开启，确保错误能够被正确检测和处理，提高系统安全性。 |
| 6 | [x ] | 🤖 AI | `McuClockConfig/McuClockSource_PLL.McuClockFrequency` | > 0 | `Adc.AdcPrescale` | > 0 | ADC分频系数必须大于0，否则ADC时钟频率为0，无法正常工作，导致系统崩溃。 |

---

## 如何使用

1. 审核上述规则，修改状态标记
2. 保存文件
3. 在工具中执行 **验证跨模块依赖**
