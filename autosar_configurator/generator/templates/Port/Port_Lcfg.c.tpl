#include "Port.h"
#include "Port_Cfg.h"

/*===========================================================================
 *                          Port Pin Configuration
 *===========================================================================*/

const Port_ConfigType Port_Config = {
    .PinConfig = {
        {% for container in containers %}
        {% if 'PortPin' in container.definition_ref %}
        {
            .PinId = {{ container.parameter_values.PortPinId.value }},
            .PinMode = {{ container.parameter_values.PortPinMode.value }},
            .Direction = {{ container.parameter_values.PortPinDirection.value }},
            .InitialMode = {{ container.parameter_values.PortPinInitialMode.value }}
        }{% if not loop.last %},{% endif %}
        {% endif %}
        {% endfor %}
    }
};
