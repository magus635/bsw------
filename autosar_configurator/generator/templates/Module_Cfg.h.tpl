/**
 * @file {{ module_name }}_Cfg.h
 * @brief Configuration header for {{ module_name }} module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

#ifndef {{ header_guard }}
#define {{ header_guard }}

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}.h"

/*===========================================================================
 *                       CONFIGURATION PARAMETERS
 *===========================================================================*/

{% for container in containers %}
/* {{ container.name }} */
{% for param in container.parameters %}
#define {{ module_name }}_{{ container.name }}_{{ param.name }}  {{ param.value }}
{% endfor %}

{% endfor %}

#endif /* {{ header_guard }} */
