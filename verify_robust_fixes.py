import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__))))

from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
import lxml.etree as etree

def test_arxml_numerical_fuzzy():
    print("Testing ArxmlParser numerical fuzzy conversion...")
    parser = ArxmlParser()
    xml_content = """
    <PARAMETER-VALUES>
        <ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF>/AUTOSAR/EcucDefs/Can/CanHardwareObject/CanHwObjectCount</DEFINITION-REF>
            <VALUE>true</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE>
    </PARAMETER-VALUES>
    """
    element = etree.fromstring(xml_content)
    from autosar_configurator.core.model.configuration_model import EcucContainerValue
    container = EcucContainerValue("CanHardwareObject", "/Test/CanHardwareObject")
    
    param_elem = element.xpath(".//*[local-name()='ECUC-NUMERICAL-PARAM-VALUE']")[0]
    parser._parse_ecuc_parameter_value(param_elem, container)
    
    v = container.parameter_values["CanHwObjectCount"].value
    print(f"CanHwObjectCount: {v} (type: {type(v)})")
    
    if v == 1:
        print("✅ SUCCESS: 'true' -> 1 during parsing")
    else:
        print("❌ FAILURE: Conversion failed")

def test_robust_indent_skipping():
    print("\nTesting Robust Indentation Skipping (Cross-token)...")
    renderer = Renderer()
    renderer.symbol_table._modules["testmodule"] = ConfigurationNode("TestModule", "module", "/TestModule")
    
    # Template with indentation split by directives
    # 8 spaces total: 4 + IF + 4
    template = '[!INDENT "8"!]\n    [!IF "node:exists(/TestModule)"!]    [!ENDIF!]Content\n[!ENDINDENT!]'
    
    result = renderer.render(template, module_name="testmodule")
    print("Rendered Output:")
    print("-" * 20)
    print(repr(result))
    print("-" * 20)
    
    # Correct output should have EXACTLY 8 spaces before "Content"
    # Previously, it would have 8 (prepended) + 4 (second chunk) = 12 spaces
    if "        Content" in result and "         Content" not in result:
        print("✅ SUCCESS: Cross-token skipping works (8 spaces total)")
    else:
        print(f"❌ FAILURE: Unexpected indentation. Spaces count: {result.find('Content')}")

def test_drift_with_multiple_directives():
    print("\nTesting Drift with Multiple Directives...")
    renderer = Renderer()
    renderer.symbol_table._modules["testmodule"] = ConfigurationNode("TestModule", "module", "/TestModule")
    
    # Template: 12 spaces split into 3 chunks
    template = '[!INDENT "8"!]\n    [!IF "1"!]    [!ENDIF!]    Content\n[!ENDINDENT!]'
    result = renderer.render(template, module_name="testmodule")
    
    # Expect 12 spaces? 
    # Template has 12. Indent is 8.
    # 1. Chunk 1 ("    "): Prepend 8, skip 4. spaces_to_skip becomes 4.
    # 2. IF directive.
    # 3. Chunk 2 ("    "): skip 4. spaces_to_skip becomes 0.
    # 4. ENDIF directive.
    # 5. Chunk 3 ("    Content"): skip 0.
    # Result: 8 (prepended) + 0 + 0 + 4 = 12 spaces.
    # THIS PRESERVES RELATIVE INDENT correctly!
    
    print(f"Result spaces: {result.find('Content')}")
    if result.find('Content') == 12:
         print("✅ SUCCESS: Relative offset (12 total for indent 8) preserved without drift")
    else:
         print("❌ FAILURE: Drift detected")

if __name__ == "__main__":
    test_arxml_numerical_fuzzy()
    test_robust_indent_skipping()
    test_drift_with_multiple_directives()
