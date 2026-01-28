
import os
import sys

# Add project path to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
from autosar_configurator.generator.eb.builtins import BuiltinFunctions

# Mock objects
class MockNode:
    def __init__(self, name, value=None, children=None, path=""):
        self.name = name
        self.value = value
        self._children = children or {}
        self.path = path
    
    def get_child(self, name):
        return self._children.get(name)
    
    def get_value(self):
        return self.value
    
    def node_name(self):
        return self.name

class MockConfig:
    def __init__(self, nodes):
        self.nodes = nodes
    
    def get_instance_by_path(self, path):
        return self.nodes.get(path)

# Set up mock nodes
mcu_ref_point = MockNode("McuClockReferencePoint_0", value=100000000.0)
adc_config_set = MockNode("AdcConfigSet_0")
adc_hw_unit = MockNode("AdcHwUnit_0", children={
    "AdcPrescale": MockNode("AdcPrescale", value=50)
})

# References
adc_analog_clock_source_ref = MockNode("AdcAnalogClockSource", value=mcu_ref_point)

# Structure
# AdcConfigSet_0
#   AdcAnalogClockSource -> mcu_ref_point
#   AdcHwUnit -> [adc_hw_unit]

nodes = {
    "/Mcu/McuModuleConfiguration_0/McuClockSettingConfig_0/McuClockReferencePoint_0": mcu_ref_point,
    "/Adc/AdcConfigSet_0": adc_config_set,
    "/Adc/AdcConfigSet_0/AdcHwUnit_0": adc_hw_unit
}

# Mock Renderer and ContextStack
renderer = Renderer()
stack = ContextStack(adc_hw_unit)
renderer.context_stack = stack

# Mock XPath Engine to handle refs
class MockXPathEngine:
    def evaluate(self, expr, node=None):
        if expr == "../../AdcAnalogClockSource":
            return adc_analog_clock_source_ref
        if expr == "./AdcPrescale":
            return adc_hw_unit.get_child("AdcPrescale")
        return None

renderer._xpath_engine = MockXPathEngine()

# Test variables
AdcSpbClock = 100000000.0
AdcPrescale = 50

# Calculation from template
AdcfadciClock = (AdcSpbClock) / 1000000 / AdcPrescale
print(f"Calculated AdcfadciClock (initial): {AdcfadciClock}")

AdcfadciClock = int(AdcfadciClock * 100) / 100
print(f"Calculated AdcfadciClock (after rounding): {AdcfadciClock}")

# Assertion check
MinMHz = 1
MaxMHz = 40
assertion = AdcfadciClock >= MinMHz and AdcfadciClock <= MaxMHz
print(f"Assertion ({AdcfadciClock} >= {MinMHz} and {AdcfadciClock} <= {MaxMHz}): {assertion}")

# Test with renderer's _evaluate_condition
expr = f"{AdcfadciClock} >= 1 and {AdcfadciClock} <= 40"
res = renderer._evaluate_condition(expr)
print(f"Renderer evaluation of '{expr}': {res}")

# Test with original expression as in template
renderer.context_stack.set_variable("AdcSpbClock", 100000000.0)
renderer.context_stack.set_variable("AdcPrescale", 50)
renderer.context_stack.set_variable("AdcfadciClock", 2.0)

template_expr = "$AdcfadciClock >= (ecu:get('Adc.AnalogClockMinMHz')) and $AdcfadciClock <= (ecu:get('Adc.AnalogClockMaxMHz'))"
# We need to mock ecu:get
class MockBuiltins:
    def __init__(self, context_stack):
        self.context_stack = context_stack
    def call(self, name, args):
        if name == "ecu:get":
            if args[0] == "Adc.AnalogClockMinMHz": return 1
            if args[0] == "Adc.AnalogClockMaxMHz": return 40
        return None

renderer._builtins = MockBuiltins(stack)

# We need to implement _evaluate_condition to handle ecu:get correctly or mock it
# Actually _evaluate_condition calls _evaluate_expression which calls _evaluate_function_call

def mock_evaluate_expression(expr):
    if "ecu:get('Adc.AnalogClockMinMHz')" in expr:
        return 1
    if "ecu:get('Adc.AnalogClockMaxMHz')" in expr:
        return 40
    if "$AdcfadciClock" in expr:
        return 2.0
    return None

# Override renderer methods for testing
original_eval_expr = renderer._evaluate_expression
renderer._evaluate_expression = lambda e: (
    2.0 if e.strip() == "$AdcfadciClock" else 
    1 if "MinMHz" in e else 
    40 if "MaxMHz" in e else 
    original_eval_expr(e)
)

final_res = renderer._evaluate_condition(template_expr)
print(f"Final Renderer evaluation of template expression: {final_res}")
