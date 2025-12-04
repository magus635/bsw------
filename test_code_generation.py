#!/usr/bin/env python3
"""
自动化代码生成测试脚本
测试多个场景并生成分析报告
"""

import sys
from pathlib import Path
import json
from datetime import datetime

# 添加项目路径
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.generator.generator import CodeGenerator


class TestScenario:
    """测试场景基类"""
    
    def __init__(self, name: str, description: str):
        self.name = name
        self.description = description
        self.output_dir = Path.home() / "Desktop" / "test_scenarios" / name
        self.output_dir.mkdir(parents=True, exist_ok=True)
        
    def setup(self, module_def, config_manager):
        """设置场景配置 - 子类实现"""
        raise NotImplementedError
        
    def run(self, def_file: Path):
        """运行测试场景"""
        print(f"\n{'='*60}")
        print(f"🧪 测试场景: {self.name}")
        print(f"📝 描述: {self.description}")
        print(f"📁 输出: {self.output_dir}")
        print(f"{'='*60}")
        
        try:
            # 1. 解析 DEF 文件
            parser = EcucDefParser()
            module_def = parser.parse_module_def_file(def_file)
            
            # 2. 创建配置管理器
            config_manager = ConfigurationManager(module_def)
            
            # 3. 设置场景特定配置
            self.setup(module_def, config_manager)
            
            # 4. 生成代码
            generator = CodeGenerator(module_def, config_manager.configuration)
            generator.generate_all(self.output_dir)
            
            # 5. 分析结果
            result = self.analyze_output()
            
            print(f"✅ 场景完成!")
            return result
            
        except Exception as e:
            print(f"❌ 场景失败: {str(e)}")
            import traceback
            traceback.print_exc()
            return None
    
    def analyze_output(self):
        """分析生成的输出"""
        result = {
            'scenario': self.name,
            'timestamp': datetime.now().isoformat(),
            'files': []
        }
        
        for file in self.output_dir.glob('*'):
            if file.is_file():
                with open(file, 'r') as f:
                    content = f.read()
                    result['files'].append({
                        'name': file.name,
                        'size': file.stat().st_size,
                        'lines': len(content.splitlines()),
                        'macros': content.count('#define'),
                        'structs': content.count('const')
                    })
        
        return result


class Scenario1_Empty(TestScenario):
    """场景1: 空配置"""
    
    def __init__(self):
        super().__init__(
            "scenario1_empty",
            "测试没有任何容器实例时的代码生成"
        )
    
    def setup(self, module_def, config_manager):
        # 不添加任何容器
        print("  → 创建空配置（无容器实例）")
        pass


class Scenario3_Multiple(TestScenario):
    """场景3: 多个容器实例"""
    
    def __init__(self):
        super().__init__(
            "scenario3_multiple",
            "测试同一容器定义的多个实例"
        )
    
    def setup(self, module_def, config_manager):
        print("  → 创建多个 AdcConfigSet 实例")
        
        if 'AdcConfigSet' not in module_def.containers:
            print("  ⚠️  AdcConfigSet 容器不存在，跳过")
            return
        
        container_def = module_def.containers['AdcConfigSet']
        
        # 创建 3 个实例，参数值不同
        for i, prescale in enumerate([10, 15, 20], 1):
            instance = config_manager.create_container_instance(
                container_def,
                instance_name=f"AdcConfig_{chr(64+i)}"  # A, B, C
            )
            
            # 设置不同的参数值
            if 'AdcPrescale' in container_def.parameters:
                config_manager.set_parameter_value(
                    instance, 
                    'AdcPrescale', 
                    prescale
                )
            
            print(f"    ✓ 创建实例: AdcConfig_{chr(64+i)} (AdcPrescale={prescale})")


class Scenario5_Types(TestScenario):
    """场景5: 不同参数类型"""
    
    def __init__(self):
        super().__init__(
            "scenario5_types",
            "测试各种参数类型的代码生成"
        )
    
    def setup(self, module_def, config_manager):
        print("  → 创建包含不同参数类型的配置")
        
        # 创建 AdcConfigSet 实例
        if 'AdcConfigSet' in module_def.containers:
            container_def = module_def.containers['AdcConfigSet']
            instance = config_manager.create_container_instance(
                container_def,
                instance_name="TypeTestConfig"
            )
            
            # 设置不同类型的参数
            params_to_set = {
                'AdcPrescale': 25,  # INTEGER
                'AdcResolution': 'BITS_10',  # ENUMERATION
                'AdcKernelChSampleTime': 5,  # INTEGER
            }
            
            for param_name, value in params_to_set.items():
                if param_name in container_def.parameters:
                    config_manager.set_parameter_value(instance, param_name, value)
                    print(f"    ✓ 设置 {param_name} = {value}")
        
        # 创建 AdcGeneral 实例
        if 'AdcGeneral' in module_def.containers:
            container_def = module_def.containers['AdcGeneral']
            instance = config_manager.create_container_instance(
                container_def,
                instance_name="GeneralConfig"
            )
            
            # 设置布尔参数
            bool_params = {
                'AdcDevErrorDetect': True,  # BOOLEAN
                'AdcDeInitApi': False,  # BOOLEAN
            }
            
            for param_name, value in bool_params.items():
                if param_name in container_def.parameters:
                    config_manager.set_parameter_value(instance, param_name, value)
                    print(f"    ✓ 设置 {param_name} = {value}")


class Scenario9_Boundary(TestScenario):
    """场景9: 边界值测试"""
    
    def __init__(self):
        super().__init__(
            "scenario9_boundary",
            "测试极端参数值的处理"
        )
    
    def setup(self, module_def, config_manager):
        print("  → 创建边界值配置")
        
        if 'AdcConfigSet' in module_def.containers:
            container_def = module_def.containers['AdcConfigSet']
            instance = config_manager.create_container_instance(
                container_def,
                instance_name="BoundaryConfig"
            )
            
            # 设置边界值
            boundary_params = {
                'AdcKernelChSampleTime': 2,  # 最小值
                'AdcPrescale': 320,  # 最大值
            }
            
            for param_name, value in boundary_params.items():
                if param_name in container_def.parameters:
                    param_def = container_def.parameters[param_name]
                    config_manager.set_parameter_value(instance, param_name, value)
                    print(f"    ✓ 设置 {param_name} = {value} (范围: {param_def.min_value}-{param_def.max_value})")


def generate_comparison_report(results):
    """生成对比分析报告"""
    report_file = Path.home() / "Desktop" / "test_scenarios" / "comparison_report.md"
    
    with open(report_file, 'w') as f:
        f.write("# 代码生成测试对比报告\n\n")
        f.write(f"**生成时间**: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
        f.write("---\n\n")
        
        # 总览表格
        f.write("## 测试场景总览\n\n")
        f.write("| 场景 | 文件数 | 总行数 | 宏定义数 | 结构数 |\n")
        f.write("|------|--------|--------|----------|--------|\n")
        
        for result in results:
            if result:
                total_lines = sum(f['lines'] for f in result['files'])
                total_macros = sum(f['macros'] for f in result['files'])
                total_structs = sum(f['structs'] for f in result['files'])
                
                f.write(f"| {result['scenario']} | {len(result['files'])} | "
                       f"{total_lines} | {total_macros} | {total_structs} |\n")
        
        f.write("\n---\n\n")
        
        # 详细分析
        f.write("## 详细分析\n\n")
        for result in results:
            if result:
                f.write(f"### {result['scenario']}\n\n")
                for file_info in result['files']:
                    f.write(f"**{file_info['name']}**:\n")
                    f.write(f"- 大小: {file_info['size']} bytes\n")
                    f.write(f"- 行数: {file_info['lines']}\n")
                    f.write(f"- 宏定义: {file_info['macros']}\n")
                    f.write(f"- 配置结构: {file_info['structs']}\n\n")
    
    print(f"\n📊 对比报告已生成: {report_file}")
    return report_file


def main():
    """主函数"""
    print("🚀 AUTOSAR 代码生成自动化测试")
    print("="*60)
    
    # DEF 文件路径
    def_file = Path("Adc_THA6206_LFBGA292.arxml")
    
    if not def_file.exists():
        print(f"❌ DEF 文件不存在: {def_file}")
        return
    
    # 定义测试场景
    scenarios = [
        Scenario1_Empty(),
        Scenario3_Multiple(),
        Scenario5_Types(),
        Scenario9_Boundary(),
    ]
    
    # 运行所有场景
    results = []
    for scenario in scenarios:
        result = scenario.run(def_file)
        if result:
            results.append(result)
    
    # 生成对比报告
    if results:
        report_file = generate_comparison_report(results)
        
        print("\n" + "="*60)
        print("✅ 所有测试场景完成!")
        print(f"📁 输出目录: ~/Desktop/test_scenarios/")
        print(f"📊 对比报告: {report_file}")
        print("="*60)
    else:
        print("\n❌ 没有成功的测试结果")


if __name__ == "__main__":
    main()
