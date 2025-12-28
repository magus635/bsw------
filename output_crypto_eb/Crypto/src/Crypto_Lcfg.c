/* Crypto_Lcfg.c Template (Project Specific / Complex) */
#include "Crypto.h"

{% for driver_object in containers['CryptoDriverObjects'] %}
/* Driver Object:  */
const Crypto_DriverObjectType Crypto_DriverObject_ = {
    .Keys = {
        {% for key in driver_object.sub_containers['CryptoKey'] %}
        {
            .KeyId = ,
            .Elements = {
                {% for element in key.sub_containers['CryptoKeyElement'] %}
                {
                    .ElementId = ,
                    .Size = 
                }, 
                {% endfor %}
            }
        }, 
        {% endfor %}
    }
};
{% endfor %}
