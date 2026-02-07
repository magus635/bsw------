import xml.etree.ElementTree as ET

def analyze():
    tree = ET.parse('/Users/qlwang/Desktop/t1/ConfigValue/Can_Config.arxml')
    root = tree.getroot()
    ns = {'ns': 'http://autosar.org/schema/r4.0'}
    
    # 1. Map controllers to IDs
    ctrl_map = {}
    for ctrl in root.findall(".//ns:ECUC-CONTAINER-VALUE", ns):
        def_ref_node = ctrl.find("ns:DEFINITION-REF", ns)
        if def_ref_node is not None and def_ref_node.text.endswith("/Can/CanConfigSet/CanController"):
            name = ctrl.find("ns:SHORT-NAME", ns).text
            id_val = None
            for val in ctrl.findall(".//ns:ECUC-NUMERICAL-PARAM-VALUE", ns):
                sub_def_ref = val.find("ns:DEFINITION-REF", ns).text
                if "CanControllerId" in sub_def_ref:
                    id_val = int(val.find("ns:VALUE", ns).text)
                    break
            ctrl_map[name] = id_val
    print(f"Controllers: {ctrl_map}")

    # 2. Count HRH/HTH per controller
    stats = {}
    for hoh in root.findall(".//ns:ECUC-CONTAINER-VALUE", ns):
        def_ref_node = hoh.find("ns:DEFINITION-REF", ns)
        if def_ref_node is not None and def_ref_node.text.endswith("/Can/CanConfigSet/CanHardwareObject"):
            hoh_name = hoh.find("ns:SHORT-NAME", ns).text
            obj_type = None
            for val in hoh.findall(".//ns:ECUC-TEXTUAL-PARAM-VALUE", ns):
                sub_def_ref = val.find("ns:DEFINITION-REF", ns).text
                if "CanObjectType" in sub_def_ref:
                    obj_type = val.find("ns:VALUE", ns).text
                    break
            
            ctrl_ref = None
            for ref in hoh.findall(".//ns:ECUC-REFERENCE-VALUE", ns):
                sub_def_ref = ref.find("ns:DEFINITION-REF", ns).text
                if "CanControllerRef" in sub_def_ref:
                    raw_ref = ref.find("ns:VALUE-REF", ns).text
                    ctrl_ref = raw_ref.split('/')[-1]
                    break
            
            if ctrl_ref not in stats:
                stats[ctrl_ref] = {'HRH': 0, 'HTH': 0}
            
            if obj_type == 'RECEIVE':
                stats[ctrl_ref]['HRH'] += 1
            else:
                stats[ctrl_ref]['HTH'] += 1
    
    for ctrl, data in sorted(stats.items()):
        print(f"Ctrl {ctrl} (ID {ctrl_map.get(ctrl)}): HRH={data['HRH']}, HTH={data['HTH']}")

analyze()
