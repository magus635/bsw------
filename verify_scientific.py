from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from lxml import etree

def test_scientific_parsing():
    xml = """
    <CONTAINER-VALUE>
        <SHORT-NAME>CanGeneral</SHORT-NAME>
        <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
                <DEFINITION-REF DEST="ECUC-FLOAT-PARAM-DEF">/THA6_AS440_FuSa/Can/CanGeneral/CanTimeoutDuration</DEFINITION-REF>
                <VALUE>1e-06</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
                <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/THA6_AS440_FuSa/Can/CanGeneral/CanCount</DEFINITION-REF>
                <VALUE>100</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
                <DEFINITION-REF DEST="ECUC-FLOAT-PARAM-DEF">/THA6_AS440_FuSa/Can/CanGeneral/CanInterval</DEFINITION-REF>
                <VALUE>0.005</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
        </PARAMETER-VALUES>
    </CONTAINER-VALUE>
    """
    
    parser = ArxmlParser()
    element = etree.fromstring(xml.strip())
    container = parser._parse_ecuc_container_value(element)
    
    print(f"Container: {container.short_name}")
    
    # 1. Test 1e-06 (Scientific Notation)
    val_1e06 = container.parameter_values.get("CanTimeoutDuration").value
    print(f"CanTimeoutDuration: {val_1e06} (Type: {type(val_1e06)})")
    assert isinstance(val_1e06, float), f"Expected float for 1e-06, got {type(val_1e06)}"
    assert val_1e06 == 1e-06
    
    # 2. Test 100 (Integer)
    val_100 = container.parameter_values.get("CanCount").value
    print(f"CanCount: {val_100} (Type: {type(val_100)})")
    assert isinstance(val_100, int), f"Expected int for 100, got {type(val_100)}"
    assert val_100 == 100
    
    # 3. Test 0.005 (Standard Float)
    val_005 = container.parameter_values.get("CanInterval").value
    print(f"CanInterval: {val_005} (Type: {type(val_005)})")
    assert isinstance(val_005, float), f"Expected float for 0.005, got {type(val_005)}"
    assert val_005 == 0.005
    
    print("\nSUCCESS: All scientific notation parsing tests passed!")

if __name__ == "__main__":
    test_scientific_parsing()
