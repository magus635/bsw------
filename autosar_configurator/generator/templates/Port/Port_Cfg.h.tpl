/**
 * @file Port_Cfg.h
 * @brief Configuration header for Port module
 */

#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Port_Types.h"

/*===========================================================================
 *                   PORT PRE-COMPILE PARAMETERS
 *===========================================================================*/

{% for param in precompile_params %}
/* {{ param.path }} */
#define PORT_{{ param.name.upper() }}  ({{ param.value }})
{% endfor %}

/*===========================================================================
 *                   PORT PIN MACROS
 *===========================================================================*/

#define PORT_NUM_CONFIGURED_PINS  ({{ containers|length }})

#endif /* PORT_CFG_H */
