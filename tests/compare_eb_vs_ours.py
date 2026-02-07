#!/usr/bin/env python3
"""
比较 EB 原始 config 和本项目生成的 config 的差异
"""
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from pathlib import Path
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
import lxml.etree as etree

def collect_all_data(config):
    """收集配置中的所有数据"""
    containers = {}
    params = {}
    refs = {}
    
    def process_container(c, path=""):
        full_path = f"{path}/{c.short_name}"
        containers[full_path] = {
            'short_name': c.short_name,
            'definition_ref': c.definition_ref,
            'param_count': len(c.parameter_values),
            'ref_count': len(c.reference_values),
            'sub_count': len(c.sub_containers)
        }
        
        for pname, pval in c.parameter_values.items():
            params[f"{full_path}.{pname}"] = {
                'value': pval.value,
                'definition_ref': pval.definition_ref
            }
        
        for rname, rval in c.reference_values.items():
            refs[f"{full_path}.{rname}"] = {
                'value_ref': rval.value_ref,
                'definition_ref': rval.definition_ref
            }
        
        for sub in c.sub_containers:
            process_container(sub, full_path)
    
    for c in config.containers:
        process_container(c)
    
    return containers, params, refs

def load_config(file_path):
    """加载配置文件"""
    parser = ArxmlParser()
    tree = etree.parse(str(file_path))
    root = tree.getroot()
    
    namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
    config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
    if config_elem is None:
        config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')
    
    return parser.parse_ecuc_configuration_values(config_elem)

def main():
    # EB 原始文件
    eb_file = Path('/Users/qlwang/Desktop/t1/ConfigValue/Can_Config.arxml_副本2')
    # 本项目生成的文件
    our_file = Path('/Users/qlwang/Desktop/t1/ConfigValue/Can_Config.arxml')
    
    print(f"=== EB vs 本项目 Config 比较 ===\n")
    print(f"EB 原始文件: {eb_file}")
    print(f"EB 文件大小: {eb_file.stat().st_size} bytes")
    print(f"本项目文件: {our_file}")
    print(f"本项目大小: {our_file.stat().st_size} bytes\n")
    
    # 加载两个配置
    eb_config = load_config(eb_file)
    our_config = load_config(our_file)
    
    eb_containers, eb_params, eb_refs = collect_all_data(eb_config)
    our_containers, our_params, our_refs = collect_all_data(our_config)
    
    print(f"EB 配置: {len(eb_containers)} 容器, {len(eb_params)} 参数, {len(eb_refs)} 引用")
    print(f"本项目: {len(our_containers)} 容器, {len(our_params)} 参数, {len(our_refs)} 引用")
    
    # 比较
    print("\n=== 差异分析 ===")
    
    # 新增的容器（本项目有，EB 没有）
    extra_containers = set(our_containers.keys()) - set(eb_containers.keys())
    if extra_containers:
        print(f"\n🆕 本项目新增的容器 ({len(extra_containers)}):")
        for c in sorted(extra_containers)[:30]:
            print(f"   {c}")
        if len(extra_containers) > 30:
            print(f"   ... 还有 {len(extra_containers) - 30} 个")
    
    # 缺失的容器（EB 有，本项目没有）
    missing_containers = set(eb_containers.keys()) - set(our_containers.keys())
    if missing_containers:
        print(f"\n❌ 本项目缺失的容器 ({len(missing_containers)}):")
        for c in sorted(missing_containers)[:30]:
            print(f"   {c}")
    
    # 新增的参数
    extra_params = set(our_params.keys()) - set(eb_params.keys())
    if extra_params:
        print(f"\n🆕 本项目新增的参数 ({len(extra_params)}):")
        for p in sorted(extra_params)[:30]:
            print(f"   {p} = {our_params[p]['value']}")
        if len(extra_params) > 30:
            print(f"   ... 还有 {len(extra_params) - 30} 个")
    
    # 缺失的参数
    missing_params = set(eb_params.keys()) - set(our_params.keys())
    if missing_params:
        print(f"\n❌ 本项目缺失的参数 ({len(missing_params)}):")
        for p in sorted(missing_params)[:30]:
            print(f"   {p} = {eb_params[p]['value']}")
    
    # 值不同的参数
    print("\n=== 值不同的参数 ===")
    diff_count = 0
    for p in sorted(eb_params.keys()):
        if p in our_params:
            eb_val = eb_params[p]['value']
            our_val = our_params[p]['value']
            if str(eb_val) != str(our_val):
                diff_count += 1
                if diff_count <= 30:
                    print(f"   {p}:")
                    print(f"      EB: {eb_val}")
                    print(f"      本项目: {our_val}")
    
    if diff_count > 30:
        print(f"   ... 还有 {diff_count - 30} 个参数值不同")
    elif diff_count == 0:
        print("   ✅ 共有参数的值都相同")

if __name__ == "__main__":
    main()
