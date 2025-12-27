/**
 * @file Adc_PBcfg.c
 * @brief Post-Build Configuration for Adc module
 */

#include "Adc_Cfg.h"
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD
#include "Adc_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Adc_ConfigType, ADC_CONST) Adc_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Adc_MemMap.h"
