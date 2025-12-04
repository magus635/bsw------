/**
 * @file {{ module_name }}_PBcfg.c
 * @brief Post-Build configuration for {{ module_name }} module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}_Cfg.h"

/*===========================================================================
 *                     CONFIGURATION STRUCTURES
 *===========================================================================*/

{% for container in containers %}
/* Configuration for {{ container.name }} */
const {{ module_name }}_{{ container.name }}_ConfigType {{ module_name }}_{{ container.name }}_Config = {
{% for param in container.parameters %}
    .{{ param.name }} = {{ param.value }},
{% endfor %}
};

{% endfor %}
