"""
Research script to verify .xdm compatibility.
Hypothesis: .xdm files are just .arxml files with a different extension, 
or at least contain the same root elements.
"""
import sys
import os
from pathlib import Path
import lxml.etree as etree

# Add parent to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

def create_mock_xdm(filename: str):
    """Create a mock .xdm file with standard ARXML content"""
    content = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_4-2-2.xsd">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>TestPackage</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF UUID="123">
          <SHORT-NAME>TestModule</SHORT-NAME>
          <DESC>
            <L-2 L="EN">Test Module Definition in XDM</L-2>
          </DESC>
          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
          <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <POST-BUILD-VARIANT-SUPPORT>false</POST-BUILD-VARIANT-SUPPORT>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF UUID="456">
                <SHORT-NAME>TestContainer</SHORT-NAME>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""
    with open(filename, 'w') as f:
        f.write(content)
    print(f"Created {filename}")

def test_def_parsing(filename: str):
    print(f"Testing DEF parsing for {filename}...")
    parser = EcucDefParser()
    try:
        # Note: parser might check extension, so we want to see if it allows .xdm
        # If it doesn't check extension, it should work.
        module_def = parser.parse_module_def_file(Path(filename))
        print(f"✅ Success! Parsed module: {module_def.short_name}")
        return True
    except Exception as e:
        print(f"❌ Failed: {e}")
        return False

def main():
    xdm_file = "test_module.xdm"
    create_mock_xdm(xdm_file)
    
    success = test_def_parsing(xdm_file)
    
    # Clean up
    if os.path.exists(xdm_file):
        os.remove(xdm_file)
        
    if success:
        print("\nConclusion: .xdm files CAN be parsed by existing logic (content-wise).")
        print("Requirement: We just need to update file filters and search logic to include .xdm.")
    else:
        print("\nConclusion: Existing logic fails on .xdm, update needed.")

if __name__ == "__main__":
    main()
