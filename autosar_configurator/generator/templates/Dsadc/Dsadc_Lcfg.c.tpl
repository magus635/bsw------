#include "Dsadc.h"
#include "Dsadc_Cfg.h"

/*===========================================================================
 *                         Dsadc Channel Configuration
 *===========================================================================*/

const Dsadc_ConfigType Dsadc_Config = {
    .Channels = {
        {% for container in containers %}
        {% if 'DsadcChannel' in container.definition_ref %}
        {
            .Id = {{ container.parameter_values.DsadcChannelId.value }},
            .Modulator = {
                .ClockDivider = {{ container.parameter_values.DsadcModulatorClockDivider.value }},
                .InputSelect = {{ container.parameter_values.DsadcModulatorInputSelect.value }}
            },
            .Filter = {
                .OverSamplingRate = {{ container.parameter_values.DsadcFilterOverSamplingRate.value }},
                .CombFilterShift = {{ container.parameter_values.DsadcFilterCombFilterShift.value }}
            }
        }{% if not loop.last %},{% endif %}
        {% endif %}
        {% endfor %}
    }
};
