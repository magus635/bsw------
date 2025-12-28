/**
 * @file Adc_PBcfg.c
 * @brief Post-Build Configuration for Adc module
 */

#include "Adc_Cfg.h"
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD
#include "Adc_MemMap.h"

/* --- Adc Post-Build Configuration --- */
const Adc_ConfigType Adc_Config_0 = {
{% for param in postbuild_params %}
    .{{ param.name }} = {{ param.value }},
{% endfor %}
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Adc_MemMap.h"
