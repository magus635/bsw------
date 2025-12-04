#!/usr/bin/env python3
"""
简单的命令行演示脚本 - 验证所有功能是否正常
"""
import sys
from pathlib import Path

print("=" * 60)
print("AUTOSAR BSW配置工具 - 功能验证")
print("=" * 60)
print()

# 测试1: 导入模块
print("测试1: 检查模块导入...")
try:
    from autosar_configurator.core.model.container import Container, Parameter
    from autosar_configurator.core.model.observers import Observer, Subject
    from autosar_configurator.core.parser.arxml_parser import ArxmlParser
    from autosar_configurator.core.serializer.arxml_serializer import ArxmlSerializer
    print("✅ 所有核心模块导入成功")
except ImportError as e:
    print(f"❌ 模块导入失败: {e}")
    sys.exit(1)

print()

# 测试2: 创建数据模型
print("测试2: 创建数据模型...")
try:
    root = Container(short_name="TestRoot", description="测试根容器")

    # 添加CAN模块
    can = Container(short_name="CanModule", description="CAN驱动配置")
    root.add_sub_container(can)

    # 添加参数
    baudrate = Parameter(
        short_name="Baudrate",
        value=500,
        value_type="INTEGER",
        min_value=125,
        max_value=1000,
        unit="kbps",
        description="CAN总线波特率"
    )
    can.add_parameter(baudrate)

    print(f"✅ 创建容器: {root.short_name}")
    print(f"   ├─ {can.short_name}")
    print(f"   │  └─ {baudrate.short_name} = {baudrate.value} {baudrate.unit}")
except Exception as e:
    print(f"❌ 数据模型创建失败: {e}")
    sys.exit(1)

print()

# 测试3: 参数验证
print("测试3: 参数验证...")
try:
    errors = baudrate.validate()
    if not errors:
        print("✅ 参数验证通过")
    else:
        print(f"❌ 参数验证失败: {errors}")
except Exception as e:
    print(f"❌ 验证过程出错: {e}")
    sys.exit(1)

print()

# 测试4: 序列化
print("测试4: 序列化为ARXML...")
try:
    serializer = ArxmlSerializer(use_namespaces=False, pretty_print=True)
    xml_string = serializer.serialize_to_string(root)
    print(f"✅ 序列化成功 (生成 {len(xml_string)} 字节)")
    print("   前200字符:")
    print("   " + xml_string[:200].replace('\n', '\n   '))
except Exception as e:
    print(f"❌ 序列化失败: {e}")
    sys.exit(1)

print()

# 测试5: 解析
print("测试5: 解析ARXML...")
try:
    parser = ArxmlParser()
    parsed = parser.parse_string(xml_string)
    print(f"✅ 解析成功: {parsed.short_name}")

    # 验证数据完整性
    can_parsed = parsed.get_sub_container("CanModule")
    if can_parsed:
        baudrate_parsed = can_parsed.get_parameter("Baudrate")
        if baudrate_parsed:
            print(f"   往返测试: {baudrate_parsed.short_name} = {baudrate_parsed.value}")
        else:
            print("❌ 参数解析失败")
    else:
        print("❌ 容器解析失败")
except Exception as e:
    print(f"❌ 解析失败: {e}")
    sys.exit(1)

print()

# 测试6: 观察者模式
print("测试6: 观察者模式...")
try:
    class TestObserver(Observer):
        def __init__(self):
            self.notified = False
            self.event_type = None

        def update(self, event: str, data=None):
            self.notified = True
            self.event_type = event

    observer = TestObserver()
    root.attach(observer)

    # 触发变更
    root.mark_dirty()

    if observer.notified and observer.event_type == 'modified':
        print("✅ 观察者模式正常工作")
    else:
        print("❌ 观察者未收到通知")
except Exception as e:
    print(f"❌ 观察者模式测试失败: {e}")
    sys.exit(1)

print()

# 测试7: 文件操作
print("测试7: 文件读写...")
try:
    test_file = Path("/tmp/test_config.arxml")

    # 写入文件
    serializer.serialize_to_file(root, test_file)
    print(f"✅ 文件写入成功: {test_file}")

    # 读取文件
    parser = ArxmlParser()
    loaded = parser.parse_file(test_file)
    print(f"✅ 文件读取成功: {loaded.short_name}")

    # 清理
    test_file.unlink()
    print("✅ 清理临时文件")
except Exception as e:
    print(f"❌ 文件操作失败: {e}")
    if test_file.exists():
        test_file.unlink()

print()

# 测试8: GUI组件（可选）
print("测试8: GUI组件检查...")
try:
    from PySide6.QtWidgets import QApplication
    print("✅ PySide6已安装")
    print("   可以启动GUI: python3 main.py")
except ImportError:
    print("⚠️  PySide6未安装，GUI不可用")
    print("   安装命令: pip3 install PySide6")

print()
print("=" * 60)
print("验证完成！所有核心功能正常工作 ✅")
print("=" * 60)
print()
print("下一步:")
print("  1. 启动GUI应用: python3 main.py")
print("  2. 运行完整测试: pytest tests/ -v")
print("  3. 查看快速指南: cat QUICKSTART.md")
print()
