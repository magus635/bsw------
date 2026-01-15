# verify_compatibility.py - EB Tresos Template Compatibility Tests
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode

def test_compatibility():
    renderer = Renderer(strict=False)
    
    # Mock data
    ctrl0 = ConfigurationNode(short_name="CanController_0", node_type="container", path="/Can/Can/CanController_0")
    ctrl0.add_child(ConfigurationNode(short_name="CanControllerId", node_type="parameter", path="/Can/Can/CanController_0/CanControllerId", value=10))
    
    can_mod = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    can_mod.add_child(ctrl0)
    renderer.symbol_table.register_module("Can", can_mod)
    
    print("--- Testing FOR loop with expressions ---")
    template = """
[!VAR "CanObjectIdList" = "'A,B,C,D'"!]
[!FOR "v" = "1" TO "count(text:split($CanObjectIdList, ','))"!]
[!VAR "CanObjectId" = "text:split($CanObjectIdList, ',')[num:i($v)]"!]
v=[!$v!]: id=[!$CanObjectId!]
[!ENDFOR!]
"""
    output = renderer.render(template)
    print(output)
    assert "v=1: id=A" in output, "FOR loop indexing failed"
    assert "v=4: id=D" in output, "FOR loop counting failed"
    print("PASS: FOR loop with expressions")
    
    print("\n--- Testing substring functions ---")
    template2 = """
[!VAR "path" = "'/Can/Can/CanController_0'"!]
After: [!substring-after($path, 'Can/')!]
Before: [!substring-before($path, '/CanController')!]
"""
    output2 = renderer.render(template2)
    print(output2)
    assert "After: Can/CanController_0" in output2, "substring-after failed"
    assert "Before: /Can/Can" in output2, "substring-before failed"
    print("PASS: substring functions")

    print("\n--- Testing num:hextoint and num:inttohex ---")
    template3 = """Result: [!num:inttohex(num:hextoint('0x10'))!]"""
    output3 = renderer.render(template3)
    print(output3)
    assert "0x10" in output3 or "0X10" in output3, "num:hextoint/num:inttohex failed"
    print("PASS: hex conversion")
    
    print("\n--- Testing text:split and text:tolower ---")
    template4 = """
[!VAR "list" = "'APPLE,BANANA,CHERRY'"!]
[!VAR "item1" = "text:split($list, ',')[1]"!]
Lower: [!text:tolower($item1)!]
"""
    output4 = renderer.render(template4)
    print(output4)
    assert "Lower: apple" in output4, "text:tolower failed"
    print("PASS: text functions")
    
    print("\n" + "="*50)
    print("All Compatibility Tests PASSED!")
    print("="*50)

if __name__ == "__main__":
    test_compatibility()
