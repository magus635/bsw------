/* Can_Lcfg.c Template (Project Specific / Complex) */
#include "Can.h"

{% for config_set in containers['CanConfigSet'] %}
/* Configuration: {{ config_set.short_name | upper }} */
const Can_ConfigType Can_Config_{{ config_set.short_name }} = {
    .Controllers = {
        {% for controller in config_set.sub_containers['CanController'] %}
        {
            .ControllerId = {{ controller.parameter_values['CanControllerId'].value }},
            .CanControllerBaudrateConfig = {
                {% for baudrate in controller.sub_containers['CanControllerBaudrateConfig'] %}
                {
                    .BaudRate = {{ baudrate.parameter_values['CanControllerBaudRate'].value }} /* Kbps */,
                    .PropSeg = {{ baudrate.parameter_values['CanControllerPropSeg'].value }},
                    .PhaseSeg1 = {{ baudrate.parameter_values['CanControllerPhaseSeg1'].value }},
                    .PhaseSeg2 = {{ baudrate.parameter_values['CanControllerPhaseSeg2'].value }}
                }{% if not loop.last %}, {% endif %}
                {% endfor %}
            }
        }{% if not loop.last %}, {% endif %}
        {% endfor %}
    }
};
{% endfor %}
