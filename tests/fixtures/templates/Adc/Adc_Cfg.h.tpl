#ifndef {{ header_guard }}
#define {{ header_guard }}

/* Enumerations from Definition */
{% for enum in enums %}
/* {{ enum.name }} */
typedef enum {
    {% for literal in enum.literals %}
    {{ literal }}{% if not loop.last %},{% endif %}
    {% endfor %}
} {{ enum.name }}Type;

{% endfor %}

/* Pre-compile Parameters */
{% for param in precompile_params %}
#define {{ param.name | upper }}  ({{ param.value }})
{% endfor %}

#endif /* {{ header_guard }} */
