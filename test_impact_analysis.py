
import unittest
from autosar_configurator.core.analysis.impact_analyzer import ImpactAnalyzer

class MockReferenceValue:
    def __init__(self, value_ref):
        self.value_ref = value_ref

class MockContainer:
    def __init__(self, short_name, reference_values=None, sub_containers=None):
        self.short_name = short_name
        self.reference_values = reference_values or {}
        self.sub_containers = sub_containers or []

class MockConfig:
    def __init__(self, containers):
        self.containers = containers

class TestImpactAnalysis(unittest.TestCase):
    def setUp(self):
        self.analyzer = ImpactAnalyzer()
        
    def test_structural_impact(self):
        # Scenario: 
        # CanIf refers to CanController.
        # Reference: CanIf.CtrlRef -> Can.Controller
        # Impact: Changing Can.Controller should impact CanIf.CtrlRef
        
        # Note: My ImpactAnalyzer assumes Edge: Target -> Source (Dependency -> Dependent)
        # So build_from_configuration should generate: Can.Controller -> CanIf.CtrlRef
        
        # Setup Ref Value
        ref_val = MockReferenceValue(value_ref="/Config/Can/Controller1")
        
        # Source of reference
        canif_cont = MockContainer("IfConfig", reference_values={"CtrlRef": ref_val})
        canif_config = MockConfig([canif_cont])
        
        self.analyzer.build_from_configuration(canif_config, "CanIf")
        
        # Verify dependency
        # Target: Can.Controller1 (Normalized from /Config/Can/Controller1)
        # Source: CanIf.IfConfig.CtrlRef
        
        impacts = self.analyzer.analyze_impact("Can.Controller1")
        
        self.assertTrue(len(impacts) > 0)
        self.assertEqual(impacts[0].target, "CanIf.IfConfig.CtrlRef")
        self.assertEqual(impacts[0].dependency_type, "structural")

    def test_logical_impact(self):
        # Scenario: AI detects "Can.BaudRate" affects "CanIf.MaxBaudRate"
        
        rules = [
            {
                "source_param": "Can.Controller1.BaudRate",
                "target_param": "CanIf.IfConfig.MaxBaudRate",
                "reason": "Derived from controller baudrate"
            }
        ]
        
        self.analyzer.load_dependencies(rules)
        
        impacts = self.analyzer.analyze_impact("Can.Controller1.BaudRate")
        
        self.assertTrue(len(impacts) > 0)
        self.assertEqual(impacts[0].target, "CanIf.IfConfig.MaxBaudRate")
        self.assertEqual(impacts[0].dependency_type, "logical")

    def test_cascading_impact(self):
        # Chain: A -> B -> C
        
        # 1. Structural: B refers to A (So A -> B)
        # A: Mcu.Clock
        # B: Can.Controller (refers to Mcu.Clock)
        ref_val = MockReferenceValue(value_ref="/Config/Mcu/Clock")
        can_cont = MockContainer("Controller", reference_values={"ClockRef": ref_val})
        can_config = MockConfig([can_cont])
        self.analyzer.build_from_configuration(can_config, "Can")
        
        # 2. Logical: B affects C
        # B: Can.Controller.BaudRate (Assume part of Controller)
        # Note: B node name must match.
        # Structural builds: Mcu.Clock -> Can.Controller.ClockRef
        
        # Let's say Logical Rule: Can.Controller.ClockRef -> Can.Controller.BaudRate (Internal logic)
        self.analyzer.add_dependency("Can.Controller.ClockRef", "Can.Controller.BaudRate", "logical", "Clock determines Baud")
        
        # And another Logical: Can.Controller.BaudRate -> CanIf.MaxBaud
        self.analyzer.add_dependency("Can.Controller.BaudRate", "CanIf.MaxBaud", "logical", "Baud match")
        
        # Analyze impact of Mcu.Clock
        impacts = self.analyzer.analyze_impact("Mcu.Clock")
        
        # Expected:
        # Mcu.Clock -> Can.Controller.ClockRef
        # Can.Controller.ClockRef -> Can.Controller.BaudRate
        # Can.Controller.BaudRate -> CanIf.MaxBaud
        
        targets = [i.target for i in impacts]
        self.assertIn("Can.Controller.ClockRef", targets)
        self.assertIn("Can.Controller.BaudRate", targets)
        self.assertIn("CanIf.MaxBaud", targets)

if __name__ == '__main__':
    unittest.main()
