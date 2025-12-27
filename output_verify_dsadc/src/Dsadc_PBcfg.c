/**
 * @file Dsadc_PBcfg.c
 * @brief Post-Build Configuration for Dsadc module
 */

#include "Dsadc_Cfg.h"
#include "Dsadc_MemMap.h"

#define DSADC_START_SEC_CONFIG_DATA_POSTBUILD
#include "Dsadc_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Dsadc_ConfigType, DSADC_CONST) Dsadc_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define DSADC_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Dsadc_MemMap.h"
