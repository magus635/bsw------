"""
Test Resource Module Integration with CAN Code Generation

Verifies:
1. Resource module can be loaded
2. CAN Controller to Core mapping works
3. MCAL_CORE generation is correct
"""
import sys
import os
import unittest
from pathlib import Path

# Add project root to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable


class TestResourceModuleLoading(unittest.TestCase):
    """Test Resource module configuration loading"""

    def setUp(self):
        """Set up paths"""
        project_root = Path(__file__).parent.parent.parent.parent
        self.test_data_dir = project_root / "tests" / "test_data"
        self.resource_def = self.test_data_dir / "Resource_Def.arxml"
        self.resource_config = self.test_data_dir / "Resource_Config.arxml"

    def test_resource_files_exist(self):
        """Verify Resource configuration files exist"""
        self.assertTrue(self.resource_def.exists(), f"Resource_Def.arxml not found at {self.resource_def}")
        self.assertTrue(self.resource_config.exists(), f"Resource_Config.arxml not found at {self.resource_config}")
        print(f"✅ Resource files exist:")
        print(f"   - {self.resource_def}")
        print(f"   - {self.resource_config}")


class TestResourceModuleRendering(unittest.TestCase):
    """Test Resource module integration with CAN code generation"""

    def setUp(self):
        """Set up renderer with Resource and CAN configuration"""
        project_root = Path(__file__).parent.parent.parent.parent
        self.template_dir = project_root / "autosar_configurator" / "generator" / "templates" / "can"

        self.renderer = Renderer(strict=False, template_dir=self.template_dir)

        # Build Resource module configuration
        resource_root = ConfigurationNode(
            short_name="Resource",
            node_type="module",
            path="/Resource"
        )

        # ResourceCoreConfigSet
        core_config_set = ConfigurationNode(
            short_name="ResourceCoreConfigSet",
            node_type="container",
            path="/Resource/ResourceCoreConfigSet"
        )
        resource_root.add_child(core_config_set)

        # CORE0 Configuration
        core0_config = ConfigurationNode(
            short_name="ResourceCoreConfig_0",
            node_type="container",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0"
        )
        core_config_set.add_child(core0_config)

        core0_id = ConfigurationNode(
            short_name="ResourceCoreId",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceCoreId",
            value="CORE0",
            param_type="STRING"
        )
        core0_config.add_child(core0_id)

        core0_enable = ConfigurationNode(
            short_name="ResourceCoreEnable",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceCoreEnable",
            value=True,
            param_type="BOOLEAN"
        )
        core0_config.add_child(core0_enable)

        # ResourceAllocation for CAN Controller 0
        allocation0 = ConfigurationNode(
            short_name="ResourceAllocation_CAN_0",
            node_type="container",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_CAN_0"
        )
        core0_config.add_child(allocation0)

        alloc0_module = ConfigurationNode(
            short_name="ResourceModule",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_CAN_0/ResourceModule",
            value="CAN",
            param_type="STRING"
        )
        allocation0.add_child(alloc0_module)

        alloc0_ref = ConfigurationNode(
            short_name="ResourceModuleRef",
            node_type="reference",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_CAN_0/ResourceModuleRef",
            value="/Can/CanConfigSet/CanController/CanController_0",
            param_type="REFERENCE"
        )
        allocation0.add_child(alloc0_ref)

        # CORE1 Configuration
        core1_config = ConfigurationNode(
            short_name="ResourceCoreConfig_1",
            node_type="container",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1"
        )
        core_config_set.add_child(core1_config)

        core1_id = ConfigurationNode(
            short_name="ResourceCoreId",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceCoreId",
            value="CORE1",
            param_type="STRING"
        )
        core1_config.add_child(core1_id)

        core1_enable = ConfigurationNode(
            short_name="ResourceCoreEnable",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceCoreEnable",
            value=True,
            param_type="BOOLEAN"
        )
        core1_config.add_child(core1_enable)

        # ResourceAllocation for CAN Controller 1
        allocation1 = ConfigurationNode(
            short_name="ResourceAllocation_CAN_1",
            node_type="container",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_CAN_1"
        )
        core1_config.add_child(allocation1)

        alloc1_module = ConfigurationNode(
            short_name="ResourceModule",
            node_type="parameter",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_CAN_1/ResourceModule",
            value="CAN",
            param_type="STRING"
        )
        allocation1.add_child(alloc1_module)

        alloc1_ref = ConfigurationNode(
            short_name="ResourceModuleRef",
            node_type="reference",
            path="/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_CAN_1/ResourceModuleRef",
            value="/Can/CanConfigSet/CanController/CanController_1",
            param_type="REFERENCE"
        )
        allocation1.add_child(alloc1_ref)

        # Register Resource module
        self.renderer.symbol_table.register_module("Resource", resource_root)

        # Build CAN module configuration
        can_root = ConfigurationNode(
            short_name="Can",
            node_type="module",
            path="/Can"
        )

        # CanConfigSet
        can_config_set = ConfigurationNode(
            short_name="CanConfigSet",
            node_type="container",
            path="/Can/CanConfigSet"
        )
        can_root.add_child(can_config_set)

        # CanController container
        can_controller = ConfigurationNode(
            short_name="CanController",
            node_type="container",
            path="/Can/CanConfigSet/CanController"
        )
        can_config_set.add_child(can_controller)

        # CanController_0
        can_ctrl_0 = ConfigurationNode(
            short_name="CanController_0",
            node_type="container",
            path="/Can/CanConfigSet/CanController/CanController_0"
        )
        can_controller.add_child(can_ctrl_0)

        ctrl0_id = ConfigurationNode(
            short_name="CanControllerId",
            node_type="parameter",
            path="/Can/CanConfigSet/CanController/CanController_0/CanControllerId",
            value=0,
            param_type="INTEGER"
        )
        can_ctrl_0.add_child(ctrl0_id)

        # CanController_1
        can_ctrl_1 = ConfigurationNode(
            short_name="CanController_1",
            node_type="container",
            path="/Can/CanConfigSet/CanController/CanController_1"
        )
        can_controller.add_child(can_ctrl_1)

        ctrl1_id = ConfigurationNode(
            short_name="CanControllerId",
            node_type="parameter",
            path="/Can/CanConfigSet/CanController/CanController_1/CanControllerId",
            value=1,
            param_type="INTEGER"
        )
        can_ctrl_1.add_child(ctrl1_id)

        # Register CAN module
        self.renderer.symbol_table.register_module("Can", can_root)

    def test_resource_module_exists(self):
        """Test Resource module can be queried"""
        template = '''[!IF "node:exists(as:modconf('Resource')[1])"!]
Resource module found!
[!ELSE!]
Resource module NOT found!
[!ENDIF!]'''

        try:
            result = self.renderer.render(template, "Can")
            print("✅ Resource module check result:")
            print(result)
            self.assertIn("Resource module found!", result)
        except Exception as e:
            self.fail(f"Resource module check failed: {e}")

    def test_resource_core_loop(self):
        """Test looping through Resource core configurations"""
        template = '''[!SELECT "as:modconf('Resource')[1]"!]
[!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!]
Core: [!"./ResourceCoreId"!] - Enabled: [!"./ResourceCoreEnable"!]
[!ENDLOOP!]
[!ENDSELECT!]'''

        try:
            result = self.renderer.render(template, "Can")
            print("✅ Resource core loop result:")
            print(result)
            self.assertIn("CORE0", result)
            self.assertIn("CORE1", result)
        except Exception as e:
            self.fail(f"Resource core loop failed: {e}")

    def test_resource_allocation_query(self):
        """Test querying resource allocation for CAN module"""
        template = '''[!SELECT "as:modconf('Resource')[1]"!]
[!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!]
[!IF "./ResourceCoreEnable = 'true'"!]
Core [!"./ResourceCoreId"!] allocations:
[!LOOP "ResourceAllocation/*"!]
  - Module: [!"./ResourceModule"!], Ref: [!"./ResourceModuleRef"!]
[!ENDLOOP!]
[!ENDIF!]
[!ENDLOOP!]
[!ENDSELECT!]'''

        try:
            result = self.renderer.render(template, "Can")
            print("✅ Resource allocation query result:")
            print(result)
            self.assertIn("CAN", result)
            self.assertIn("CanController_0", result)
            self.assertIn("CanController_1", result)
        except Exception as e:
            self.fail(f"Resource allocation query failed: {e}")


class TestMcalCoreGeneration(unittest.TestCase):
    """Test MCAL_CORE macro generation for CAN controllers"""

    def setUp(self):
        """Set up renderer with complete configuration"""
        project_root = Path(__file__).parent.parent.parent.parent
        self.template_dir = project_root / "autosar_configurator" / "generator" / "templates" / "can"

        self.renderer = Renderer(strict=False, template_dir=self.template_dir)

        # Build Resource module (same as above but with controlled allocation)
        resource_root = ConfigurationNode("Resource", "module", "/Resource")
        core_config_set = ConfigurationNode("ResourceCoreConfigSet", "container", "/Resource/ResourceCoreConfigSet")
        resource_root.add_child(core_config_set)

        # CORE0 with CanController_0
        core0 = ConfigurationNode("ResourceCoreConfig_0", "container", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0")
        core_config_set.add_child(core0)
        core0.add_child(ConfigurationNode("ResourceCoreId", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceCoreId", "CORE0", "STRING"))
        core0.add_child(ConfigurationNode("ResourceCoreEnable", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceCoreEnable", True, "BOOLEAN"))

        alloc0 = ConfigurationNode("ResourceAllocation_0", "container", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_0")
        core0.add_child(alloc0)
        alloc0.add_child(ConfigurationNode("ResourceModule", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_0/ResourceModule", "CAN", "STRING"))
        alloc0.add_child(ConfigurationNode("ResourceModuleRef", "reference", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_0/ResourceAllocation_0/ResourceModuleRef", "/Can/CanConfigSet/CanController/CanController_0", "REFERENCE"))

        # CORE1 with CanController_1
        core1 = ConfigurationNode("ResourceCoreConfig_1", "container", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1")
        core_config_set.add_child(core1)
        core1.add_child(ConfigurationNode("ResourceCoreId", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceCoreId", "CORE1", "STRING"))
        core1.add_child(ConfigurationNode("ResourceCoreEnable", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceCoreEnable", True, "BOOLEAN"))

        alloc1 = ConfigurationNode("ResourceAllocation_1", "container", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_1")
        core1.add_child(alloc1)
        alloc1.add_child(ConfigurationNode("ResourceModule", "parameter", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_1/ResourceModule", "CAN", "STRING"))
        alloc1.add_child(ConfigurationNode("ResourceModuleRef", "reference", "/Resource/ResourceCoreConfigSet/ResourceCoreConfig_1/ResourceAllocation_1/ResourceModuleRef", "/Can/CanConfigSet/CanController/CanController_1", "REFERENCE"))

        self.renderer.symbol_table.register_module("Resource", resource_root)

        # Build CAN module
        can_root = ConfigurationNode("Can", "module", "/Can")
        can_config_set = ConfigurationNode("CanConfigSet", "container", "/Can/CanConfigSet")
        can_root.add_child(can_config_set)

        can_controller = ConfigurationNode("CanController", "container", "/Can/CanConfigSet/CanController")
        can_config_set.add_child(can_controller)

        can_ctrl_0 = ConfigurationNode("CanController_0", "container", "/Can/CanConfigSet/CanController/CanController_0")
        can_controller.add_child(can_ctrl_0)
        can_ctrl_0.add_child(ConfigurationNode("CanControllerId", "parameter", "/Can/CanConfigSet/CanController/CanController_0/CanControllerId", 0, "INTEGER"))

        can_ctrl_1 = ConfigurationNode("CanController_1", "container", "/Can/CanConfigSet/CanController/CanController_1")
        can_controller.add_child(can_ctrl_1)
        can_ctrl_1.add_child(ConfigurationNode("CanControllerId", "parameter", "/Can/CanConfigSet/CanController/CanController_1/CanControllerId", 1, "INTEGER"))

        self.renderer.symbol_table.register_module("Can", can_root)

    def test_mcal_core_generation_concept(self):
        """Test the concept of MCAL_CORE generation"""
        # This tests the logic without using the full macro
        template = '''[!SELECT "as:modconf('Can')[1]"!]
/* Controller Core Mapping */
[!VAR "ModuleName" = "'CAN'"!]
[!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!]
[!VAR "ControllerName" = "node:name(.)"!]
[!VAR "MappedCoreId" = "num:i(0)"!]
[!SELECT "as:modconf('Resource')[1]"!]
[!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!]
[!IF "./ResourceCoreEnable = 'true'"!]
[!VAR "CoreId" = "./ResourceCoreId"!]
[!LOOP "ResourceAllocation/*"!]
[!IF "./ResourceModule = $ModuleName"!]
[!IF "text:split(./ResourceModuleRef, '/')[last()] = $ControllerName"!]
[!VAR "MappedCoreId" = "num:i(text:split($CoreId, 'CORE')[last()])"!]
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]
[!ENDLOOP!]
[!ENDSELECT!]
MCAL_CORE[!"$MappedCoreId"!],    /* [!"$ControllerName"!] -> Core[!"$MappedCoreId"!] */
[!ENDLOOP!]
[!ENDSELECT!]'''

        try:
            result = self.renderer.render(template, "Can")
            print("✅ MCAL_CORE generation result:")
            print(result)

            # Verify the mapping
            self.assertIn("MCAL_CORE0", result)
            self.assertIn("MCAL_CORE1", result)
            self.assertIn("CanController_0", result)
            self.assertIn("CanController_1", result)
        except Exception as e:
            self.fail(f"MCAL_CORE generation failed: {e}")


if __name__ == '__main__':
    unittest.main(verbosity=2)
