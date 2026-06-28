"""
Smoke Test for EB Template Engine

Verifies:
1. Template parsing works
2. Overlay mechanism functions
3. C code generation produces valid output
4. AUTOSAR semantic mapping is correct
"""
import sys
import os
import unittest

# Add project root to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable


class TestSmokeTest(unittest.TestCase):
    """End-to-end smoke test for EB template engine"""
    
    def setUp(self):
        """Set up test data"""
        self.renderer = Renderer(strict=False)
        
        # Manually build a configuration tree for testing
        # This avoids complex model dependencies
        root = ConfigurationNode(
            short_name="Mcu",
            node_type="module",
            path="/Mcu"
        )
        
        general_config = ConfigurationNode(
            short_name="McuGeneralConfiguration",
            node_type="container",
            path="/Mcu/McuGeneralConfiguration"
        )
        root.add_child(general_config)
        
        # Add some parameters
        dev_error = ConfigurationNode(
            short_name="McuDevErrorDetect",
            node_type="parameter",
            path="/Mcu/McuGeneralConfiguration/McuDevErrorDetect",
            value=True,
            param_type="BOOLEAN"
        )
        general_config.add_child(dev_error)
        
        # Register in symbol table
        self.renderer.symbol_table.register_module("Mcu", root)
    
    def test_simple_template(self):
        """Test simple variable and output"""
        template = '[!VAR "x" = "42"!]Value: [!$x!]'
        result = self.renderer.render(template, "Mcu")
        self.assertIn("Value: 42", result)
    
    def test_if_condition(self):
        """Test IF/ELSE condition"""
        template = '[!VAR "flag" = "true"!][!IF $flag!]YES[!ELSE!]NO[!ENDIF!]'
        result = self.renderer.render(template, "Mcu")
        self.assertEqual(result, "YES")
    
    def test_variable_shadowing(self):
        """Test variable shadowing in nested scope"""
        template = '''[!VAR "x" = "outer"!]
[!IF true!]
[!VAR "x" = "inner"!]
Inner: [!$x!]
[!ENDIF!]'''
        result = self.renderer.render(template, "Mcu")
        self.assertIn("Inner: inner", result)
    
    def test_module_access(self):
        """Test as:modconf module access"""
        template = '[!SELECT as:modconf("Mcu")!]Module loaded[!ENDSELECT!]'
        result = self.renderer.render(template, "Mcu")
        self.assertIn("Module loaded", result)
    
    def test_node_exists(self):
        """Test node:exists function"""
        template = '[!IF node:exists(McuGeneralConfiguration)!]Config exists[!ENDIF!]'
        result = self.renderer.render(template, "Mcu")
        self.assertIn("Config exists", result)
    
    def test_header_guard_pattern(self):
        """Test typical header guard pattern"""
        template = '''[!VAR "Guard" = "MCU_CFG_H"!]
#ifndef [!"$Guard"!]
#define [!"$Guard"!]
/* Content */
#endif /* [!"$Guard"!] */'''
        result = self.renderer.render(template)
        self.assertIn("#ifndef MCU_CFG_H", result)
        self.assertIn("#define MCU_CFG_H", result)
        self.assertIn("#endif /* MCU_CFG_H */", result)
    
    def test_num_inttohex(self):
        """Test num:inttohex formatting"""
        template = '[!"num:inttohex(255, 4)"!]'
        result = self.renderer.render(template)
        # EB Tresos num:inttohex emits lowercase hex (matches standard output).
        self.assertEqual(result.strip(), "0x00ff")
    
    def test_string_functions(self):
        """Test string functions"""
        template = '[!"string:upper(\'hello\')"!]'
        result = self.renderer.render(template)
        self.assertEqual(result.strip(), "HELLO")


class TestAutoSarSemanticMapping(unittest.TestCase):
    """Test AUTOSAR semantic mapping for Boolean values"""
    
    def setUp(self):
        self.symbol_table = SymbolTable()
        from autosar_configurator.generator.eb.context import ContextStack
        from autosar_configurator.generator.eb.builtins import BuiltinFunctions
        
        self.context_stack = ContextStack()
        self.builtins = BuiltinFunctions(self.symbol_table, self.context_stack)
    
    # EB Tresos node:value() returns the canonical XPath boolean 'true'/'false'
    # (lowercase) for ALL boolean params, regardless of name. The C-level mapping
    # to STD_ON / TRUE is done by the templates via explicit [!IF!] blocks (the
    # standard reference output never contains a bare lowercase 'true'). A
    # name-based heuristic here would break every `node:value(X) = 'true'`
    # comparison (e.g. SpiEnableCs, SpiEnableDMA).
    def test_feature_boolean_true_lowercase(self):
        node = ConfigurationNode(
            short_name="McuDevErrorEnable",  # name must NOT change the result
            node_type="parameter",
            path="/Mcu/Config/McuDevErrorEnable",
            value=True,
            param_type="BOOLEAN"
        )
        self.assertEqual(self.builtins.node_value(node), "true")

    def test_feature_boolean_false_lowercase(self):
        node = ConfigurationNode(
            short_name="McuVersionInfoApiDisable",
            node_type="parameter",
            path="/Mcu/Config/McuVersionInfoApiDisable",
            value=False,
            param_type="BOOLEAN"
        )
        self.assertEqual(self.builtins.node_value(node), "false")

    def test_runtime_boolean_true(self):
        node = ConfigurationNode(
            short_name="McuIsReady",
            node_type="parameter",
            path="/Mcu/Config/McuIsReady",
            value=True,
            param_type="BOOLEAN"
        )
        self.assertEqual(self.builtins.node_value(node), "true")

    def test_runtime_boolean_false(self):
        node = ConfigurationNode(
            short_name="McuStatusFlag",
            node_type="parameter",
            path="/Mcu/Config/McuStatusFlag",
            value=False,
            param_type="BOOLEAN"
        )
        self.assertEqual(self.builtins.node_value(node), "false")


if __name__ == '__main__':
    unittest.main()
