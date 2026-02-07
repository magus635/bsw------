#!/usr/bin/env python3
"""
测试 INDEX 序列化是否正确工作
"""
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from pathlib import Path
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
import lxml.etree as etree

def main():
    eb_file = Path('/Users/qlwang/Desktop/t1/ConfigValue/Can_Config.arxml_副本2')
    temp_output = Path('/tmp/Can_Config_with_index.arxml')
    
    print(f"=== INDEX 序列化测试 ===\n")
    
    # 加载 EB 文件
    parser = ArxmlParser()
    tree = etree.parse(str(eb_file))
    root = tree.getroot()
    
    namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
    config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
    if config_elem is None:
        config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')
    
    config = parser.parse_ecuc_configuration_values(config_elem)
    
    # 统计有 INDEX 的容器
    index_count = 0
    def count_indexes(c):
        nonlocal index_count
        if getattr(c, '_has_explicit_index', False):
            index_count += 1
        for sub in c.sub_containers:
            count_indexes(sub)
    
    for c in config.containers:
        count_indexes(c)
    
    print(f"解析到 {index_count} 个带有显式 INDEX 的容器")
    
    # 保存
    serializer = EcucValueSerializer()
    serializer.serialize_to_file(config, temp_output)
    
    # 检查输出文件中的 INDEX 数量
    with open(temp_output, 'r') as f:
        content = f.read()
    
    output_index_count = content.count('<INDEX>')
    print(f"输出文件中有 {output_index_count} 个 <INDEX> 元素")
    
    # 比较原始文件
    with open(eb_file, 'r') as f:
        orig_content = f.read()
    
    orig_index_count = orig_content.count('<INDEX>')
    print(f"原始 EB 文件有 {orig_index_count} 个 <INDEX> 元素")
    
    if output_index_count == orig_index_count:
        print(f"\n✅ INDEX 数量一致!")
    else:
        print(f"\n⚠️ INDEX 数量不一致: {output_index_count} vs {orig_index_count}")

if __name__ == "__main__":
    main()
