/* Adc_Lcfg.c Template (Project Specific / Complex) */
#include "Adc.h"

{% for config_set in containers['AdcConfigSet'] %}
const Adc_ConfigType Adc_Config_{{ config_set.short_name }} = {
    .AdcPrescale = {{ config_set.parameter_values['AdcPrescale'].value }},
    .AdcResolution = {{ config_set.parameter_values['AdcResolution'].value }},
    
    /* Hardware Units and Groups (Complex Recursive Loop) */
    .HwUnits = {
        {% for hw_unit in config_set.sub_containers['AdcHwUnit'] %}
        {
            .HwUnitId = {{ hw_unit.parameter_values['AdcHwUnitId'].value }},
            .Groups = {
                {% for group in hw_unit.sub_containers['AdcGroup'] %}
                {
                    .GroupId = {{ group.parameter_values['AdcGroupId'].value }},
                    .Channels = {
                        {% for channel in group.sub_containers['AdcChannel'] %}
                        {{ channel.parameter_values['AdcChannelId'].value }}{% if not loop.last %}, {% endif %}
                        {% endfor %}
                    }
                }{% if not loop.last %}, {% endif %}
                {% endfor %}
            }
        }{% if not loop.last %}, {% endif %}
        {% endfor %}
    }
};
{% endfor %}
