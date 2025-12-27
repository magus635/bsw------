/**
 * @file Mcu_PBcfg.c
 * @brief Post-Build Configuration for Mcu module
 */

#include "Mcu_Cfg.h"
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA_POSTBUILD
#include "Mcu_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Mcu_ConfigType, MCU_CONST) Mcu_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Mcu_MemMap.h"
