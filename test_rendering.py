
from autosar_configurator.generator.template_engine import TemplateEngine

def test_rendering():
    module_name = "Mcu"
    # Content as it would be after f-string expansion in generator.py
    template_content = """
{% for path_name_value in postbuild_params %}
    ./* {{ path_name_value.0 }} */{{ path_name_value.1 }} = {{ path_name_value.2 }},
{% endfor %}
"""
    context = {
        'module_name': 'Mcu',
        'postbuild_params': [
            ('McuModuleConfiguration/McuClockSettingConfig/McuClockSettingConfig_0/McuClockReferencePoint', 'McuClockReferencePoint', 'McuClockReferencePoint_0'),
        ]
    }
    
    engine = TemplateEngine()
    rendered = engine.render(template_content, context)
    print("--- Rendered Output ---")
    print(rendered)
    print("-----------------------")

if __name__ == "__main__":
    test_rendering()
