#include "Crypto.h"
#include "Crypto_Cfg.h"

/*===========================================================================
 *                          Crypto Key Configuration
 *===========================================================================*/

{% for container in containers %}
{% if 'CryptoKey' in container.definition_ref %}
/* {{ container.short_name }} */
const Crypto_KeyType {{ container.short_name }}_Config = {
    .KeyId = {{ container.parameter_values.CryptoKeyId.value }},
    {% if container.parameter_values.CryptoKeyType %}
    .KeyType = {{ container.parameter_values.CryptoKeyType.value }},
    {% endif %}
    
    /* Key Elements */
    .ElementsCount = {{ container.sub_containers|length }},
    .Elements = {
        {% for sub in container.sub_containers %}
        {
            .Id = {{ sub.parameter_values.CryptoKeyElementId.value }},
            .Size = {{ sub.parameter_values.CryptoKeyElementSize.value }}
        }{% if not loop.last %},{% endif %}
        {% endfor %}
    }
};
{% endif %}
{% endfor %}

/* Array of all keys */
const Crypto_KeyType* const Crypto_KeysConfig[] = {
{% for container in containers %}
{% if 'CryptoKey' in container.definition_ref %}
    &{{ container.short_name }}_Config{% if not loop.last %},{% endif %}
{% endif %}
{% endfor %}
};
