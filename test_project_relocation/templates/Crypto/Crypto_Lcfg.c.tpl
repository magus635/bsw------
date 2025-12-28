/* Crypto_Lcfg.c Template (Project Specific / Complex) */
#include "Crypto.h"

{% for driver_object in containers['CryptoDriverObjects'] %}
/* Driver Object: {{ driver_object.short_name }} */
const Crypto_DriverObjectType Crypto_DriverObject_{{ driver_object.short_name }} = {
    .Keys = {
        {% for key in driver_object.sub_containers['CryptoKey'] %}
        {
            .KeyId = {{ key.parameter_values['CryptoKeyId'].value }},
            .Elements = {
                {% for element in key.sub_containers['CryptoKeyElement'] %}
                {
                    .ElementId = {{ element.parameter_values['CryptoKeyElementId'].value }},
                    .Size = {{ element.parameter_values['CryptoKeyElementSize'].value }}{% if element.parameter_values['CryptoKeyElementFormat'] is not None %},
                    .Format = {{ element.parameter_values['CryptoKeyElementFormat'].value }}{% endif %}
                }{% if not loop.last %}, {% endif %}
                {% endfor %}
            }
        }{% if not loop.last %}, {% endif %}
        {% endfor %}
    }
};
{% endfor %}
