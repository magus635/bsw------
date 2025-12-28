/* Adc_Lcfg.c Template (Project Specific / Complex) */
#include "Adc.h"

{% for config_set in containers['AdcConfigSet'] %}
const Adc_ConfigType Adc_Config_ = {
    .AdcPrescale = ,
    .AdcResolution = ,
    
    /* Hardware Units and Groups (Complex Recursive Loop) */
    .HwUnits = {
        {% for hw_unit in config_set.sub_containers['AdcHwUnit'] %}
        {
            .HwUnitId = ,
            .Groups = {
                {% for group in hw_unit.sub_containers['AdcGroup'] %}
                {
                    .GroupId = ,
                    .Channels = {
                        {% for channel in group.sub_containers['AdcChannel'] %}
                        , 
                        {% endfor %}
                    }
                }, 
                {% endfor %}
            }
        }, 
        {% endfor %}
    }
};
{% endfor %}
