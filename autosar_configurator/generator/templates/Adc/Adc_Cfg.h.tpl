/**
 * @file {{ module_name }}_Cfg.h
 * @brief Configuration header for {{ module_name }} module
 * 
 * ==========================================
 * >>> ADC MODULE-SPECIFIC TEMPLATE <<<
 * This file was generated using Adc-specific template!
 * ==========================================
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

#ifndef {{ header_guard }}
#define {{ header_guard }}

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}.h"
#include "Adc_Types.h"  /* Adc-specific include */

/*===========================================================================
 *                   ADC PRE-COMPILE PARAMETERS
 *===========================================================================*/

{% for param in precompile_params %}
/* {{ param.path }} */
#define {{ module_name }}_{{ param.name }}  ({{ param.value }})
{% endfor %}

/*===========================================================================
 *                   ADC CHANNEL CONFIGURATION
 *===========================================================================*/
/* ADC-specific configuration would go here */

#endif /* {{ header_guard }} */
