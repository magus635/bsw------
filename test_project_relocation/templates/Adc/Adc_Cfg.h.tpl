/**
 * @file Adc_Cfg.h
 * @brief Pre-Compile Configuration for Adc module
 */

#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "Std_Types.h"

/* --- Adc General Configuration --- */
#define ADC_DEV_ERROR_DETECT            (STD_ON)
#define ADC_VERSION_INFO_API            (STD_OFF)
#define ADC_DEINIT_API                  (STD_ON)

/* --- Adc Pre-Compile Parameters --- */
{% for param in precompile_params %}
#define ADC_{{ param.name | upper }}    ({{ param.value }})
{% endfor %}

#endif /* ADC_CFG_H */
