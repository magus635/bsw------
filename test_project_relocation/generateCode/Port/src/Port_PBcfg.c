/**
 * @file Port_PBcfg.c
 * @brief Post-Build Configuration for Port module
 */

#include "Port_Cfg.h"
#include "Port_MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_POSTBUILD
#include "Port_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Port_ConfigType, PORT_CONST) Port_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define PORT_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Port_MemMap.h"
