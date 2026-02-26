import sys
from pathlib import Path
from lxml import etree

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration, EcucContainerValue, EcucParameterValue, EcucReferenceValue
)

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')

NAMESPACES = {
    'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
    'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd'
}

tree = etree.parse(str(os_config_path))
root = tree.getroot()

# The config is under d:lst type="TOP-LEVEL-PACKAGES" / d:ctr type="AR-PACKAGE" / d:lst type="ELEMENTS" / d:chc type="AR-ELEMENT" value="MODULE-CONFIGURATION" / d:ctr type="MODULE-CONFIGURATION"
module_config_elem = root.xpath(".//d:chc[@value='MODULE-CONFIGURATION']/d:ctr[@type='MODULE-CONFIGURATION']", namespaces=NAMESPACES)

if module_config_elem:
    module_config_elem = module_config_elem[0]
    # The parent chc has the short name
    short_name = module_config_elem.getparent().get('name')
    print(f"Found Module Configuration: {short_name}")
    
    # Let's inspect its direct children
    for child in module_config_elem:
        tag_local = etree.QName(child).localname
        name = child.get('name')
        itype = child.get('type')
        val = child.get('value')
        print(f"  Child: {tag_local}, name: {name}, type: {itype}, value: {val}")
        
    # Example: d:lst name="OsAppTaskRef"
    app_tasks = module_config_elem.xpath(".//d:lst[@name='OsAppTaskRef']/d:ref", namespaces=NAMESPACES)
    print(f"\nExample List OsAppTaskRef count: {len(app_tasks)}")
    if app_tasks:
        print(f" First ref value: {app_tasks[0].get('value')}")
