/**
 * @file Mcu_Cfg.h
 * @brief Configuration header for MCU module
 */

#ifndef MCU_CFG_H
#define MCU_CFG_H

#include "Mcu_Types.h"

/*===========================================================================
 *                   MCU PRE-COMPILE PARAMETERS
 *===========================================================================*/

{% for param in precompile_params %}
/* {{ param.path }} */
#define MCU_{{ param.name.upper() }}  ({{ param.value }})
{% endfor %}

/*===========================================================================
 *                   MCU CLOCK CONFIGURATION
 *===========================================================================*/

{% for container in containers %}
{% if 'McuClockConfig' in container.definition_ref %}
/* Clock Configuration: {{ container.short_name }} */
#define MCU_{{ container.short_name.upper() }}_EN  (STD_ON)
{% endif %}
{% endfor %}

#endif /* MCU_CFG_H */
