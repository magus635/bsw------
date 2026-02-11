import os
from pathlib import Path
from autosar_configurator.generator.eb_template_engine import Renderer
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
import lxml.etree as etree 

# 1. 你的模板代码
DIO_TEMPLATE = """
[!MACRO "CG_GetDioChannelCfgData"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Port.MaxAvailablePortID')"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'), concat('_', $PortNumber, '_'))"!][!//
            {/* Port[!"$PortNumber"!] */ [!//
                [!VAR "PortConfigured" = "num:i(0)"!][!//
                [!/* Loop for all DioPort containers to generate configured Port, Channels under this port  */!][!//
                [!IF "node:exists(DioConfig/DioPort/*[DioPortId = num:i($PortNumber)])"!][!//
                    [!SELECT "DioConfig/DioPort/*[DioPortId = num:i($PortNumber)]"!][!//
                        DIO_PORT_CONFIGURED,[!WS "5"!][!//
                        [!FOR "PinNumber" = "0" TO "15"!][!//
                            [!IF "node:exists(DioChannel/*[DioChannelId = num:i($PinNumber)])"!][!// <-- 还原 XPath 表达式
                                [!VAR "PortConfigured" = "bit:or($PortConfigured,(bit:shl(1,num:i($PinNumber))))"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                        ([!"num:inttohex($PortConfigured, 4)"!]U)[!//
                    [!ENDSELECT!][!//
                [!ELSE!][!//
                    DIO_PORT_NOT_CONFIGURED, (0x0000U)[!//
                [!ENDIF!][!//
            }[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ENDIF!]
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

/* --- Now, let's call the macro to see the output --- */
[!CALL "CG_GetDioChannelCfgData"!]
"""

def run_test():
    # 2. 指定你的配置文件和定义文件路径
    arxml_config_path = Path('Dio_Config_Test.arxml')
    arxml_def_path = Path('Dio_Definition_Test.arxml') 

    # 3. 初始化解析器
    def_parser = EcucDefParser()
    arxml_parser = ArxmlParser()
    
    # 加载 ARXML 定义
    module_def = def_parser.parse_module_def_file(arxml_def_path)

    if not module_def or module_def.short_name != "Dio":
        print(f"错误: 无法从 {arxml_def_path} 中加载 'Dio' 模块定义。")
        return
    
    print(f"已加载模块定义: {module_def.short_name}")

    # 加载 ARXML 配置 - 直接从 XML 元素解析 EcucModuleConfiguration
    try:
        tree = etree.parse(str(arxml_config_path))
        root = tree.getroot()

        namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
        # 查找 ECUC-MODULE-CONFIGURATION-VALUES 元素
        config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
        if config_elem is None:
            # 尝试不带命名空间查找
            config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')

        if config_elem is None:
            print(f"错误: 在 {arxml_config_path} 中找不到 ECUC-MODULE-CONFIGURATION-VALUES 元素。")
            return
        
        module_config = arxml_parser.parse_ecuc_configuration_values(config_elem)

    except Exception as e:
        print(f"加载配置时发生错误: {e}")
        import traceback
        traceback.print_exc()
        return

    if not isinstance(module_config, EcucModuleConfiguration) or module_config.short_name != "Dio":
        print(f"错误: 从 {arxml_config_path} 中加载的不是 'Dio' 模块配置，或名称不匹配。")
        print(f"实际类型: {type(module_config)}, 实际名称: {module_config.short_name if module_config else 'None'}")
        return
    
    print(f"已加载模块配置: {module_config.short_name}")
    
    # 模拟 ECU 资源，特别是 Port 模块的数据
    configured_port_ids = []
    
    # 修正：module_config.containers 是一个列表，直接迭代
    for top_level_container in module_config.containers:
        if top_level_container.short_name == 'DioConfig':
            dio_config_container = top_level_container
            
            for sub_container in dio_config_container.sub_containers:
                if sub_container.short_name.startswith('DioPort_'):
                    if 'DioPortId' in sub_container.parameter_values:
                        port_id = sub_container.parameter_values['DioPortId'].value
                        configured_port_ids.append(port_id)
    
    # ECU 资源的模拟值
    ecu_resources = {
        'Port.MaxAvailablePortID': 15, # 假设最大端口ID为15，可以根据实际情况调整
        'Port.AvailablePortsID': '_' + '_'.join(map(str, sorted(configured_port_ids))) + '_' # 格式如 _0_1_14_
    }
    
    print(f"模拟 ECU 资源: {ecu_resources}")
    
    # 4. 初始化渲染器
    renderer = Renderer()
    
    # 5. 将模块定义和模块配置加载到渲染器 (不传入 ecu_resources)
    renderer.load_module(module_def, module_config)

    # 6. 渲染模板
    print("--- 模板渲染结果 ---")
    try:
        # 将 ecu_resources 传递给 render 方法
        output = renderer.render(DIO_TEMPLATE, module_name="Dio", ecu_resources=ecu_resources)
        print(output)
    except Exception as e:
        print(f"渲染出错: {e}")
        import traceback
        traceback.print_exc()
    print("--- 渲染结束 ---")

if __name__ == "__main__":
    # 添加项目根目录到 sys.path，以便导入 autosar_configurator
    import sys
    sys.path.insert(0, os.getcwd())
    run_test()
