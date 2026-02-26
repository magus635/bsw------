import sys
from pathlib import Path
from lxml import etree

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')

try:
    tree = etree.parse(str(os_config_path))
    root = tree.getroot()
    parser = ArxmlParser()
    
    # Check if there's any ECUC-MODULE-CONFIGURATION-VALUES or if we need to parse it as XDM
    config_elem = parser._find_descendant(root, 'ECUC-MODULE-CONFIGURATION-VALUES')
    if config_elem is not None:
        print("Found ECUC-MODULE-CONFIGURATION-VALUES, parsing as standard ARXML.")
        config = parser.parse_ecuc_configuration_values(config_elem)
        print(f"Parsed config: {config.short_name}")
    else:
        print("No ECUC-MODULE-CONFIGURATION-VALUES found. This file is not standard ARXML.")
        chc_elem = root.xpath(".//d:chc[@value='MODULE-CONFIGURATION']", namespaces={'d': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd'})
        if chc_elem:
           print("Found Tresos DataModel MODULE-CONFIGURATION via d:chc tag.")
        else:
           print("No Tresos DataModel MODULE-CONFIGURATION found.")

except Exception as e:
    print(f"Error parsing: {e}")
    import traceback
    traceback.print_exc()

