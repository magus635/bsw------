#include "Adc.h"
#include "Adc_Cfg.h"

{% for container in containers %}
{% if 'AdcConfigSet' in container.definition_ref %}
/* Configuration: {{ container.short_name }} */
const Adc_ConfigType {{ container.short_name }} = {
    /* HW Units */
    .HwUnits = {
        {% for hw_unit in container.sub_containers %}
        {% if 'AdcHwUnit' in hw_unit.definition_ref %}
        {
            {% if hw_unit.parameter_values.AdcHwUnitId %}
            .Id = {{ hw_unit.parameter_values.AdcHwUnitId.value }},
            {% endif %}
            
            /* Channels in this HW Unit */
            .Channels = {
                {% for ch in hw_unit.sub_containers %}
                {% if 'AdcChannel' in ch.definition_ref %}
                {
                    .Name = "{{ ch.short_name }}",
                    .Id = {{ ch.parameter_values.AdcChannelId.value }}
                }{% if not loop.last %},{% endif %}
                {% endif %}
                {% endfor %}
            }
        }{% if not loop.last %},{% endif %}
        {% endif %}
        {% endfor %}
    }
};
{% endif %}
{% endfor %}
