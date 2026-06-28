import sys
import os
import unittest
from typing import Optional

# Add project root to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable

class TestUserTemplates(unittest.TestCase):
    """
    Verify the Parser and XPath Engine using user-provided EB C templates.
    """
    
    def setUp(self):
        self.renderer = Renderer(strict=False)
        self.symbol_table = self.renderer.symbol_table
        
        # ======================================================================
        # Build ECUC Model (Mocking ARXML content)
        # ======================================================================
        
        # Module: Can
        can_mod = ConfigurationNode("Can", "module", "/Can")
        
        # Container: CanGeneral
        can_general = ConfigurationNode("CanGeneral", "container", "/Can/CanGeneral")
        can_mod.add_child(can_general)
        
        # Param: CanDevErrorDetect (Feature)
        # Template checks: `node:value(...) = 'true'`
        can_general.add_child(ConfigurationNode(
            "CanDevErrorDetect", "parameter", "/Can/CanGeneral/CanDevErrorDetect",
            value="true" # Raw string
        ))
        
        # Param: CanVariant (for testing Variant Select)
        # Template checks: `CanImplementation/CanVariant` inside SELECT CanGeneral
        # So we place CanImplementation UNDER CanGeneral for this test structure
        can_impl = ConfigurationNode("CanImplementation", "container", "/Can/CanGeneral/CanImplementation")
        can_general.add_child(can_impl)
        can_impl.add_child(ConfigurationNode(
            "CanVariant", "parameter", "/Can/CanGeneral/CanImplementation/CanVariant",
            value="POST_BUILD"
        ))
        
        # Container: CanController (List)
        # Template uses LOOP "CanController/*" implying CanController is a parent container
        # or implies CanController is the definition ShortName and * means all instances. 
        # But standard XPath CanController/* means children of node named CanController.
        # So we create a parent node "CanController".
        can_ctrl_parent = ConfigurationNode("CanController", "container", "/Can/CanController")
        can_mod.add_child(can_ctrl_parent)
        
        for i in range(2):
            ctrl = ConfigurationNode(f"CanController_{i}", "container", f"/Can/CanController/CanController_{i}")
            
            # Param: CanControllerId
            ctrl.add_child(ConfigurationNode(
                "CanControllerId", "parameter", f"/Can/CanController/CanController_{i}/CanControllerId",
                value=i, param_type="INTEGER"
            ))
            
            # Param: CanControllerBaudrate
            ctrl.add_child(ConfigurationNode(
                "CanControllerBaudrate", "parameter", f"/Can/CanController/CanController_{i}/CanControllerBaudrate",
                value=500 * (i+1), param_type="INTEGER"
            ))
            
            # Param: CanWakeupSupport
            # Template checks: `='true'`
            val = "true" if i == 1 else "false"
            ctrl.add_child(ConfigurationNode(
                "CanWakeupSupport", "parameter", f"/Can/CanController/CanController_{i}/CanWakeupSupport",
                value=val
            ))
            
            # Add to parent container, not module directly
            can_ctrl_parent.add_child(ctrl)
            
        # Reference: CanMainFunctionTaskRef
        can_mod.add_child(ConfigurationNode(
            "CanMainFunctionTaskRef", "reference", "/Can/CanMainFunctionTaskRef",
            value="/Os/OsTask/OsTask_0"
        ))
        
        self.symbol_table.register_module("Can", can_mod)
        
        # Module: Os
        os_mod = ConfigurationNode("Os", "module", "/Os")
        os_task = ConfigurationNode("OsTask", "container", "/Os/OsTask")
        os_mod.add_child(os_task)
        task0 = ConfigurationNode("OsTask_0", "container", "/Os/OsTask/OsTask_0")
        os_task.add_child(task0)
        task0.add_child(ConfigurationNode(
            "OsTaskId", "parameter", "/Os/OsTask/OsTask_0/OsTaskId",
            value=10, param_type="INTEGER"
        ))
        
        self.symbol_table.register_module("Os", os_mod)

    # ======================================================================
    # Tests
    # ======================================================================

    def test_1_Can_Cfg_h(self):
        template = """
#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Std_Types.h"/* ==================== General ==================== */

/* 验证点：XPath读取布尔值，并用 IF 转换为宏 */
#define CAN_DEV_ERROR_DETECT   [!//!]
[!IF "node:value(CanGeneral/CanDevErrorDetect) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* 验证点：XPath count() 函数 */
#define CAN_CONTROLLER_COUNT  [!"num:i(count(CanController/*))"!]U

/* ==================== Controller IDs ==================== */

/* 验证点：LOOP 迭代与 Context 切换 */
[!LOOP "CanController/*"!]
/* ECUC: CanController/[!"node:name(.)"!]/CanControllerId */
/* 验证点：node:value(.) 读取当前上下文的子节点 */
#define CAN_CONTROLLER_ID_[!"node:name(.)"!]  [!"node:value(CanControllerId)"!]U
[!ENDLOOP!]

#endif /* CAN_CFG_H */
"""
        result = self.renderer.render(template, "Can").strip()
        self.assertIn("#define CAN_DEV_ERROR_DETECT   STD_ON", result)
        self.assertIn("#define CAN_CONTROLLER_COUNT  2U", result)
        self.assertIn("#define CAN_CONTROLLER_ID_CanController_0  0U", result)
        self.assertIn("#define CAN_CONTROLLER_ID_CanController_1  1U", result)

    def test_2_Can_PBcfg_h(self):
        template = """
#ifndef CAN_PBCFG_H
#define CAN_PBCFG_H

#include "Can_Types.h"/* 验证点：Variant 处理，假设 Variant 在预定义变量中 */
[!IF "$VARIANT = 'POST_BUILD'"!]
extern CONST(Can_ConfigType, CAN_CONST) Can_PBConfig;
[!ENDIF!]

#endif
"""
        # Set Variant Variable via initial_variables
        result = self.renderer.render(template, "Can", initial_variables={"VARIANT": "POST_BUILD"}).strip()
        self.assertIn("extern CONST(Can_ConfigType, CAN_CONST) Can_PBConfig;", result)

    def test_3_Can_PBcfg_c(self):
        template = """
#include "Can.h"#include "Can_PBcfg.h"/* ==================== Controller Config ==================== */

static CONST(Can_ControllerConfigType, CAN_CONST) CanControllerConfig[] =
{
[!LOOP "CanController/*"!]
  {
    /* Controller Index via node:order or sorting */
    .ControllerId = [!"node:value(CanControllerId)"!]U,
    .Baudrate     = [!"node:value(CanControllerBaudrate)"!]U,
    /* 验证点：布尔转 TRUE/FALSE */
    .WakeupSupport = [!//!]
[!IF "node:value(CanWakeupSupport) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
  },
[!ENDLOOP!]
};

/* ==================== Global Config ==================== */

CONST(Can_ConfigType, CAN_CONST) Can_PBConfig =
{
  .Controllers = CanControllerConfig,
  .ControllerCount = CAN_CONTROLLER_COUNT
};
"""
        result = self.renderer.render(template, "Can").strip()
        self.assertIn(".ControllerId = 0U,", result)
        self.assertIn(".WakeupSupport = FALSE", result)
        self.assertIn(".WakeupSupport = TRUE", result)

    def test_4_Can_h(self):
        """Synthesized Can.h.tt to verify VAR calculation and Hex formatting"""
        template = """
#ifndef CAN_H
#define CAN_H

/* 验证点：VAR 计算与 Hex 转换 */
[!VAR "Base" = "128"!]
[!VAR "Offset" = "127"!]
[!VAR "Mask" = "num:inttohex($Base + $Offset)"!]
#define CAN_MASK [!"$Mask"!]

/* 验证点：Context Loop */
[!LOOP "CanController/*"!]
extern void Can_Init_Controller_[!"node:value(CanControllerId)"!](void);
[!ENDLOOP!]

#endif
"""
        result = self.renderer.render(template, "Can").strip()
        # num:inttohex emits lowercase hex (EB Tresos / standard-output behaviour)
        self.assertIn("#define CAN_MASK 0xff", result)
        self.assertIn("extern void Can_Init_Controller_0(void);", result)
        self.assertIn("extern void Can_Init_Controller_1(void);", result)

    def test_5_Can_c(self):
        """Synthesized Can.c.tt to verify function generation"""
        template = """
#include "Can.h"

/* 验证点：函数生成 */
[!LOOP "CanController/*"!]
void Can_Init_[!"node:value(CanControllerId)"!](void)
{
    /* Baudrate: [!"node:value(CanControllerBaudrate)"!] */
}
[!ENDLOOP!]
"""
        result = self.renderer.render(template, "Can").strip()
        self.assertIn("void Can_Init_0(void)", result)
        self.assertIn("/* Baudrate: 500 */", result)
        self.assertIn("void Can_Init_1(void)", result)
        self.assertIn("/* Baudrate: 1000 */", result)

    def test_6_Ref_Handling(self):
        template = """
/* 原始需求：从 Can 模块跳到 OsTask 模块取 ID */
/* 你的引擎必须支持 node:ref() 函数将路径字符串转换为节点对象 */

[!VAR "MyTaskRef" = "node:ref(CanMainFunctionTaskRef)"!]

/* 验证点：变量解引用与跨模块 XPath */
#define CAN_MAIN_TASK_ID  [!"node:value($MyTaskRef/OsTaskId)"!]U
"""
        result = self.renderer.render(template, "Can").strip()
        self.assertIn("#define CAN_MAIN_TASK_ID  10U", result)

    def test_7_Variant_Logic(self):
        template = """
[!SELECT "CanGeneral"!]
  [!IF "CanImplementation/CanVariant = 'POST_BUILD'"!]
    #include "Can_PBcfg.h"
  [!ELSE!]
    #include "Can_Cfg.h"
  [!ENDIF!]
[!ENDSELECT!]
"""
        result = self.renderer.render(template, "Can").strip()
        self.assertIn('#include "Can_PBcfg.h"', result)

if __name__ == '__main__':
    unittest.main()
