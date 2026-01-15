# verify_xpath_can_xdm.py
"""
Verification script for XPath and template syntax found in Can.xdm
Tests the XPath engine and built-in functions against real patterns.
"""
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.context import ContextStack

def setup_mock_can_config():
    """Create a mock CAN configuration matching Can.xdm structure"""
    renderer = Renderer(strict=False)
    
    # Can module root
    can = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    
    # CanGeneral container
    can_general = ConfigurationNode(short_name="CanGeneral", node_type="container", path="/Can/CanGeneral")
    can_general.add_child(ConfigurationNode(short_name="CanSetBaudrateApi", node_type="parameter", 
                                             path="/Can/CanGeneral/CanSetBaudrateApi", value=True))
    can.add_child(can_general)
    
    # CanConfigSet container
    config_set = ConfigurationNode(short_name="CanConfigSet", node_type="container", path="/Can/CanConfigSet")
    
    # CanController instances
    for i in range(2):
        ctrl = ConfigurationNode(short_name=f"CanController_{i}", node_type="container", 
                                 path=f"/Can/CanConfigSet/CanController_{i}")
        ctrl.add_child(ConfigurationNode(short_name="CanControllerId", node_type="parameter",
                                         path=f"/Can/CanConfigSet/CanController_{i}/CanControllerId", value=i))
        ctrl.add_child(ConfigurationNode(short_name="CanHardwareChannel", node_type="parameter",
                                         path=f"/Can/CanConfigSet/CanController_{i}/CanHardwareChannel", 
                                         value=f"CAN_CONTROLLER_0{i}"))
        ctrl.add_child(ConfigurationNode(short_name="CanControllerActivation", node_type="parameter",
                                         path=f"/Can/CanConfigSet/CanController_{i}/CanControllerActivation", value=True))
        ctrl.add_child(ConfigurationNode(short_name="CanWakeupSupport", node_type="parameter",
                                         path=f"/Can/CanConfigSet/CanController_{i}/CanWakeupSupport", value=False))
        ctrl.add_child(ConfigurationNode(short_name="CanFDSupport", node_type="parameter",
                                         path=f"/Can/CanConfigSet/CanController_{i}/CanFDSupport", value=True))
        
        # CanControllerBaudrateConfig
        baud = ConfigurationNode(short_name="CanControllerBaudrateConfig_0", node_type="container",
                                  path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0")
        baud.add_child(ConfigurationNode(short_name="CanControllerBaudRateConfigID", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerBaudRateConfigID", value=i))
        baud.add_child(ConfigurationNode(short_name="CanControllerBaudRate", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerBaudRate", value=500.0))
        baud.add_child(ConfigurationNode(short_name="CanControllerPRESDIV", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerPRESDIV", value=2))
        baud.add_child(ConfigurationNode(short_name="CanControllerPropSeg", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerPropSeg", value=7))
        baud.add_child(ConfigurationNode(short_name="CanControllerSeg1", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerSeg1", value=7))
        baud.add_child(ConfigurationNode(short_name="CanControllerSeg2", node_type="parameter",
                                          path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerSeg2", value=2))
        
        # FD config
        fd_baud = ConfigurationNode(short_name="CanControllerFdBaudrateConfig", node_type="container",
                                     path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerFdBaudrateConfig")
        fd_baud.add_child(ConfigurationNode(short_name="CanControllerTxBitRateSwitch", node_type="parameter",
                                            path=f"/Can/CanConfigSet/CanController_{i}/CanControllerBaudrateConfig_0/CanControllerFdBaudrateConfig/CanControllerTxBitRateSwitch", value=True))
        baud.add_child(fd_baud)
        
        ctrl.add_child(baud)
        config_set.add_child(ctrl)
    
    can.add_child(config_set)
    renderer.symbol_table.register_module("Can", can)
    return renderer

def test_xpath_patterns():
    """Test XPath patterns found in Can.xdm"""
    renderer = setup_mock_can_config()
    results = []
    
    # Pattern 1: node:exists() - Line 341, 396, 417
    print("\n--- Test 1: node:exists() ---")
    template1 = """[!LOOP "as:modconf('Can')/CanConfigSet/*"!]
Controller: [!node:name(.)!]
FD Exists: [!node:exists(CanControllerBaudrateConfig_0/CanControllerFdBaudrateConfig)!]
[!ENDLOOP!]"""
    out1 = renderer.render(template1)
    print(out1)
    results.append(("node:exists()", "FD Exists: True" in out1))
    
    # Pattern 2: node:fallback() - Line 125, 127, 128
    print("\n--- Test 2: node:fallback() ---")
    template2 = """[!LOOP "as:modconf('Can')/CanConfigSet/*"!]
[!VAR "id" = "node:fallback(CanControllerId, 999)"!]
Fallback ID: [!$id!]
[!ENDLOOP!]"""
    out2 = renderer.render(template2)
    print(out2)
    results.append(("node:fallback()", "Fallback ID: 0" in out2 or "Fallback ID: 1" in out2))
    
    # Pattern 3: count() - Line 127
    print("\n--- Test 3: count() ---")
    template3 = """Controllers: [!count(as:modconf('Can')/CanConfigSet/*)!]"""
    out3 = renderer.render(template3)
    print(out3)
    results.append(("count()", "Controllers: 2" in out3))
    
    # Pattern 4: text:uniq() - Line 111, 128, 344
    print("\n--- Test 4: text:uniq() (check uniqueness) ---")
    # Note: text:uniq is not implemented yet, but we can test text:split
    template4 = """[!VAR "list" = "'A,B,C,A'"!]
Split: [!count(text:split($list, ','))!]"""
    out4 = renderer.render(template4)
    print(out4)
    results.append(("text:split count", "Split: 4" in out4))
    
    # Pattern 5: node:value() with relative path - Line 358, 488
    print("\n--- Test 5: node:value() with path ---")
    template5 = """[!LOOP "as:modconf('Can')/CanConfigSet/*"!]
[!VAR "baud" = "node:value(CanControllerBaudrateConfig_0/CanControllerBaudRate)"!]
Baud: [!$baud!]
[!ENDLOOP!]"""
    out5 = renderer.render(template5)
    print(out5)
    results.append(("node:value(path)", "Baud: 500" in out5))
    
    # Pattern 6: Boolean comparison - Line 199, 216, 471
    print("\n--- Test 6: Boolean comparison ---")
    template6 = """[!LOOP "as:modconf('Can')/CanConfigSet/*"!]
[!IF "CanWakeupSupport = 'true'"!]Wakeup ON[!ELSE!]Wakeup OFF[!ENDIF!]
[!ENDLOOP!]"""
    out6 = renderer.render(template6)
    print(out6)
    results.append(("Boolean comparison", "Wakeup OFF" in out6))
    
    # Pattern 7: AND condition - Line 341, 471, 484
    print("\n--- Test 7: AND condition ---")
    template7 = """[!LOOP "as:modconf('Can')/CanConfigSet/*"!]
[!IF "(node:exists(CanFDSupport)) and (CanFDSupport = 'true')"!]FD Enabled[!ELSE!]FD Disabled[!ENDIF!]
[!ENDLOOP!]"""
    out7 = renderer.render(template7)
    print(out7)
    results.append(("AND condition", "FD Enabled" in out7))
    
    # Pattern 8: Numeric comparison - Line 127, 396
    print("\n--- Test 8: Numeric comparison ---")
    template8 = """[!VAR "val" = "15"!]
[!IF "$val > 10"!]Greater[!ELSE!]Lesser[!ENDIF!]"""
    out8 = renderer.render(template8)
    print(out8)
    results.append(("Numeric comparison", "Greater" in out8))
    
    # Pattern 9: num:i() conversion - Line 57, 125
    print("\n--- Test 9: num:i() ---")
    template9 = """[!VAR "v" = "'5'"!]
Num: [!num:i($v)!]U"""
    out9 = renderer.render(template9)
    print(out9)
    results.append(("num:i()", "Num: 5U" in out9))
    
    # Pattern 10: node:path() - Line 259
    print("\n--- Test 10: node:path() ---")
    template10 = """[!LOOP "as:modconf('Can')/CanConfigSet/*[1]"!]
Path: [!node:path(.)!]
[!ENDLOOP!]"""
    out10 = renderer.render(template10)
    print(out10)
    results.append(("node:path()", "/Can/CanConfigSet" in out10))
    
    # Summary
    print("\n" + "="*60)
    print("XPath Pattern Verification Results:")
    print("="*60)
    passed = 0
    failed = 0
    for name, result in results:
        status = "PASS" if result else "FAIL"
        if result: passed += 1
        else: failed += 1
        print(f"  {name}: {status}")
    print(f"\nTotal: {passed} passed, {failed} failed")
    return failed == 0

if __name__ == "__main__":
    success = test_xpath_patterns()
    exit(0 if success else 1)
