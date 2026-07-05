/**
 * @file Dsadc_Cfg.h
 * @brief Configuration header for Dsadc module
 */

#ifndef DSADC_CFG_H
#define DSADC_CFG_H

#include "Dsadc_Types.h"

/*===========================================================================
 *                   DSADC PRE-COMPILE PARAMETERS
 *===========================================================================*/

{% for param in precompile_params %}
/* {{ param.path }} */
#define DSADC_{{ param.name.upper() }}  ({{ param.value }})
{% endfor %}

#endif /* DSADC_CFG_H */
