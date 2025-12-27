#include "Mcu.h"
#include "Mcu_Cfg.h"

/*===========================================================================
 *                          MCU Clock Configuration
 *===========================================================================*/

{% for container in containers %}
{% if 'McuClockConfig' in container.definition_ref %}
/* {{ container.short_name }} */
const Mcu_ClockSettingConfigType {{ container.short_name }}_Settings = {
    .ClockSources = {
        {% for sub in container.sub_containers %}
        {% if 'McuClockSource' in sub.definition_ref %}
        {
            {% if sub.parameter_values.McuClockFrequency %}
            .Frequency = {{ sub.parameter_values.McuClockFrequency.value }}U,
            {% endif %}
            {% if sub.parameter_values.McuClockSourceType %}
            .Source = {{ sub.parameter_values.McuClockSourceType.value }}
            {% endif %}
        }{% if not loop.last %},{% endif %}
        {% endif %}
        {% endfor %}
    }
};
{% endif %}
{% endfor %}

const Mcu_ConfigType Mcu_Config = {
    .ClockSettings = {
        {% for container in containers %}
        {% if 'McuClockConfig' in container.definition_ref %}
        &{{ container.short_name }}_Settings{% if not loop.last %},{% endif %}
        {% endif %}
        {% endfor %}
    }
};
