from lxml import etree

NAMESPACES = {
    'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
    'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd',
    'v': 'http://www.tresos.de/_projects/DataModel2/06/schema.xsd'
}

file_path = '/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml'
tree = etree.parse(file_path)
root = tree.getroot()

module_config_elem = root.xpath(".//d:chc[@value='MODULE-CONFIGURATION']/d:ctr[@type='MODULE-CONFIGURATION']", namespaces=NAMESPACES)
print("module_config_elem:", module_config_elem)

