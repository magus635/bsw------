/**
 * @file {{ module_name }}_Lcfg.c
 * @brief Link-Time configuration for {{ module_name }} module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}_Cfg.h"
#include "{{ module_name }}_MemMap.h"

/*===========================================================================
 *                     LINK-TIME CONFIGURATION
 *===========================================================================*/

#define {{ module_name }}_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "{{ module_name }}_MemMap.h"

{% for container in containers %}
/* Link-Time configuration for {{ container.name }} */
CONST({{ module_name }}_{{ container.name }}_ConfigType, {{ module_name }}_CONST) {{ module_name }}_{{ container.name }}_LcfgData = {
{% for param in container.parameters %}
    .{{ param.name }} = {{ param.value }},
{% endfor %}
};

{% endfor %}

#define {{ module_name }}_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "{{ module_name }}_MemMap.h"
