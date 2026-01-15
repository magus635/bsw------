from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine
from autosar_configurator.generator.eb.renderer import Renderer
from dataclasses import dataclass

@dataclass
class MockContainerDef:
    short_name: str
    definition_ref: str
    is_required: bool = True
    sub_containers: dict = None
    parameters: dict = None
    references: dict = None
    lower_multiplicity: int = 1
    upper_multiplicity: int = -1

@dataclass
class MockModuleDef:
    short_name: str
    definition_ref: str
    containers: dict

@dataclass
class MockContainerValue:
    short_name: str
    definition_ref: str
    children: dict = None

@dataclass
class MockModuleConfig:
    short_name: str
    containers: list

# Setup
symbol_table = SymbolTable()
engine = OverlayEngine(symbol_table)

# Definition
can_def = MockModuleDef(
    short_name="Can",
    definition_ref="/AUTOSAR/EcucDefs/Can",
    containers={
        "CanConfigSet": MockContainerDef(
            short_name="CanConfigSet",
            definition_ref="/AUTOSAR/EcucDefs/Can/CanConfigSet",
            sub_containers={},
            parameters={},
            references={}
        )
    }
)

# Configuration with multiple instances
config = MockModuleConfig(
    short_name="Can",
    containers=[
        MockContainerValue(short_name="CanConfigSet", definition_ref="/AUTOSAR/EcucDefs/Can/CanConfigSet"),
        MockContainerValue(short_name="CanConfigSet_0", definition_ref="/AUTOSAR/EcucDefs/Can/CanConfigSet"),
        MockContainerValue(short_name="CanConfigSet_1", definition_ref="/AUTOSAR/EcucDefs/Can/CanConfigSet")
    ]
)

root = engine.build_configuration_tree(can_def, config)

print(f"Module children: {[c.short_name for c in root.get_children_list()]}")

renderer = Renderer()
renderer.symbol_table = symbol_table

# TEST 1: Direct access
print("--- TEST 1: Direct access ---")
tpl1 = "[!LOOP \"as:modconf('Can')/CanConfigSet/*\"!]Found: [!\"node:name(.)\"!][!ENDLOOP!]"
print(f"Template: {tpl1}")
print(f"Result: {renderer.render(tpl1, module_name='Can')}")

# TEST 2: Wildcard on sibling
print("--- TEST 2: Wildcard mapping ---")
tpl2 = "[!LOOP \"as:modconf('Can')/*\"!][!IF \"node:name(.) = 'CanConfigSet' or node:name(.) = 'CanConfigSet_0'\"!]Found: [!\"node:name(.)\"!][!ENDIF!][!ENDLOOP!]"
print(f"Template: {tpl2}")
print(f"Result: {renderer.render(tpl2, module_name='Can')}")

