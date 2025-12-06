"""
自动化测试套件 - 今日实现功能
运行: python test_today_features.py
"""

import sys
from pathlib import Path

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.config_manager import ConfigurationManager, ValidationError
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
)


def create_test_module_def():
    """创建测试用的模块定义"""
    module_def = EcucModuleDef("TestModule")
    module_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule"  # Set module definition ref
    
    container_def = EcucContainerDef(
        short_name="TestContainer",
        lower_multiplicity=1,
        upper_multiplicity=1
    )
    
    # Set definition_ref BEFORE adding parameters
    container_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule/TestContainer"
    
    container_def.parameters = {
        "IntParam": EcucParameterDef(
            short_name="IntParam",
            param_type=EcucParameterType.INTEGER,
            min_value=0,
            max_value=100,
            lower_multiplicity=1,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/IntParam"
        ),
        "EnumParam": EcucParameterDef(
            short_name="EnumParam",
            param_type=EcucParameterType.ENUMERATION,
            literals=["option1", "option2", "option3"],
            lower_multiplicity=1,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/EnumParam"
        ),
        "BoolParam": EcucParameterDef(
            short_name="BoolParam",
            param_type=EcucParameterType.BOOLEAN,
            lower_multiplicity=0,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/BoolParam"
        ),
        "FloatParam": EcucParameterDef(
            short_name="FloatParam",
            param_type=EcucParameterType.FLOAT,
            min_value=0.0,
            max_value=1.0,
            lower_multiplicity=0,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/FloatParam"
        ),
        "StringParam": EcucParameterDef(
            short_name="StringParam",
            param_type=EcucParameterType.STRING,
            lower_multiplicity=0,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/StringParam"
        )
    }
    
    module_def.containers = {"TestContainer": container_def}
    
    return module_def


def test_parameter_default_values():
    """Test 1: 测试参数默认值初始化"""
    print("\n" + "="*60)
    print("Test 1: Parameter Default Values")
    print("="*60)
    
    module_def = create_test_module_def()
    manager = ConfigurationManager(module_def)
    
    # Create container instance at root level
    container_def = module_def.containers["TestContainer"]
    instance = manager.create_container_instance(
        container_def,  # Pass the container_def object, not string
        None,  # parent
        "TestInstance"  # instance_name
    )
    
    # 验证默认值
    tests = [
        ("IntParam", 0, "Integer should default to min or 0"),
        ("EnumParam", "option1", "Enum should default to first literal"),
        ("BoolParam", False, "Boolean should default to False"),
        ("FloatParam", 0.0, "Float should default to min or 0.0"),
        ("StringParam", "", "String should default to empty")
    ]
    
    passed = 0
    failed = 0
    
    for param_name, expected, description in tests:
        actual = instance.parameter_values[param_name].value
        if actual == expected:
            print(f"  ✅ {param_name}: {actual} == {expected}")
            passed += 1
        else:
            print(f"  ❌ {param_name}: {actual} != {expected} - {description}")
            failed += 1
    
    print(f"\nResult: {passed} passed, {failed} failed")
    return failed == 0


def test_type_conversion_and_validation():
    """Test 2: 测试类型转换和验证"""
    print("\n" + "="*60)
    print("Test 2: Type Conversion and Validation")
    print("="*60)
    
    module_def = create_test_module_def()
    manager = ConfigurationManager(module_def)
    container_def = module_def.containers["TestContainer"]
    instance = manager.create_container_instance(
        container_def,
        None,
        "TestInstance"
    )
    
    passed = 0
    failed = 0
    
    # Test Integer conversion
    try:
        manager.set_parameter_value(instance, "IntParam", "42")
        if instance.parameter_values["IntParam"].value == 42:
            print("  ✅ Integer string conversion: '42' -> 42")
            passed += 1
        else:
            print(f"  ❌ Integer conversion failed")
            failed += 1
    except Exception as e:
        print(f"  ❌ Integer conversion error: {e}")
        failed += 1
    
    # Test Integer range validation
    try:
        manager.set_parameter_value(instance, "IntParam", "200")
        print("  ❌ Should reject out of range value")
        failed += 1
    except (ValueError, ValidationError):
        print("  ✅ Correctly rejected out of range value (200 > 100)")
        passed += 1
    
    # Test Float conversion
    try:
        manager.set_parameter_value(instance, "FloatParam", "0.5")
        if instance.parameter_values["FloatParam"].value == 0.5:
            print("  ✅ Float string conversion: '0.5' -> 0.5")
            passed += 1
        else:
            print(f"  ❌ Float conversion failed")
            failed += 1
    except Exception as e:
        print(f"  ❌ Float conversion error: {e}")
        failed += 1
    
    # Test Boolean conversion
    try:
        manager.set_parameter_value(instance, "BoolParam", "true")
        if instance.parameter_values["BoolParam"].value == True:
            print("  ✅ Boolean string conversion: 'true' -> True")
            passed += 1
        else:
            print(f"  ❌ Boolean conversion failed")
            failed += 1
    except Exception as e:
        print(f"  ❌ Boolean conversion error: {e}")
        failed += 1
    
    # Test Enum validation
    try:
        manager.set_parameter_value(instance, "EnumParam", "option2")
        if instance.parameter_values["EnumParam"].value == "option2":
            print("  ✅ Enum value accepted: 'option2'")
            passed += 1
        else:
            print(f"  ❌ Enum value not set correctly")
            failed += 1
    except Exception as e:
        print(f"  ❌ Enum validation error: {e}")
        failed += 1
    
    try:
        manager.set_parameter_value(instance, "EnumParam", "invalid")
        print("  ❌ Should reject invalid enum value")
        failed += 1
    except (ValueError, ValidationError):
        print("  ✅ Correctly rejected invalid enum value")
        passed += 1
    
    print(f"\nResult: {passed} passed, {failed} failed")
    return failed == 0


def test_project_version_management():
    """Test 3: 测试Project版本管理"""
    print("\n" + "="*60)
    print("Test 3: Project Version Management")
    print("="*60)
    
    import json
    import tempfile
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    
    manager = WorkspaceManager()
    passed = 0
    failed = 0
    
    # Test 1: 拒绝未来版本
    with tempfile.NamedTemporaryFile(mode='w', suffix='.dpa', delete=False) as f:
        future_data = {
            "format_version": 999,
            "tool_version": "99.0.0",
            "name": "FutureProject",
            "modules": []
        }
        json.dump(future_data, f)
        future_file = f.name
    
    try:
        project, failed_modules = manager.load_project(Path(future_file))
        print("  ❌ Should reject future version")
        failed += 1
    except ValueError as e:
        if "unsupported" in str(e).lower():
            print("  ✅ Correctly rejected unsupported version (999)")
            passed += 1
        else:
            print(f"  ❌ Wrong error message: {e}")
            failed += 1
    finally:
        Path(future_file).unlink()
    
    # Test 2: 接受当前版本
    with tempfile.NamedTemporaryFile(mode='w', suffix='.dpa', delete=False) as f:
        current_data = {
            "format_version": 1,
            "tool_version": "1.0.0",
            "name": "CurrentProject",
            "created": "2025-12-05T20:00:00",
            "modules": []
        }
        json.dump(current_data, f)
        current_file = f.name
    
    try:
        project, failed_modules = manager.load_project(Path(current_file))
        if project and project.name == "CurrentProject":
            print("  ✅ Successfully loaded current version (1)")
            passed += 1
        else:
            print("  ❌ Failed to load current version")
            failed += 1
    except Exception as e:
        print(f"  ❌ Error loading current version: {e}")
        failed += 1
    finally:
        Path(current_file).unlink()
    
    print(f"\nResult: {passed} passed, {failed} failed")
    return failed == 0


def test_project_metadata():
    """Test 4: 测试Project元数据"""
    print("\n" + "="*60)
    print("Test 4: Project Metadata")
    print("="*60)
    
    import json
    import tempfile
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    
    manager = WorkspaceManager()
    passed = 0
    failed = 0
    
    with tempfile.TemporaryDirectory() as tmpdir:
        project_path = Path(tmpdir) / "test.dpa"
        
        # 创建Project
        project = manager.create_project("MetadataTest", project_path)
        project.author = "Test Author"
        project.description = "Test Description"
        project.version = "2.0.0"
        
        # 保存
        manager.save_project()
        
        # 验证文件内容
        with open(project_path) as f:
            data = json.load(f)
        
        tests = [
            ("format_version", 1),
            ("name", "MetadataTest"),
            ("author", "Test Author"),
            ("description", "Test Description"),
            ("version", "2.0.0")
        ]
        
        for key, expected in tests:
            if key in data and data[key] == expected:
                print(f"  ✅ {key}: {data[key]}")
                passed += 1
            else:
                print(f"  ❌ {key}: expected {expected}, got {data.get(key)}")
                failed += 1
        
        # 验证时间戳
        if "created" in data:
            print(f"  ✅ created timestamp: {data['created']}")
            passed += 1
        else:
            print(f"  ❌ created timestamp missing")
            failed += 1
        
        if "last_modified" in data:
            print(f"  ✅ last_modified timestamp: {data['last_modified']}")
            passed += 1
        else:
            print(f"  ❌ last_modified timestamp missing")
            failed += 1
    
    print(f"\nResult: {passed} passed, {failed} failed")
    return failed == 0


def run_all_tests():
    """运行所有测试"""
    print("\n" + "="*60)
    print("🧪 Running All Automated Tests")
    print("="*60)
    
    tests = [
        ("Parameter Default Values", test_parameter_default_values),
        ("Type Conversion and Validation", test_type_conversion_and_validation),
        ("Project Version Management", test_project_version_management),
        ("Project Metadata", test_project_metadata)
    ]
    
    results = []
    for name, test_func in tests:
        try:
            result = test_func()
            results.append((name, result))
        except Exception as e:
            print(f"\n❌ Test '{name}' crashed: {e}")
            import traceback
            traceback.print_exc()
            results.append((name, False))
    
    # Summary
    print("\n" + "="*60)
    print("📊 Test Summary")
    print("="*60)
    
    passed_count = sum(1 for _, result in results if result)
    total_count = len(results)
    
    for name, result in results:
        status = "✅ PASSED" if result else "❌ FAILED"
        print(f"{status}: {name}")
    
    print(f"\nTotal: {passed_count}/{total_count} tests passed")
    
    if passed_count == total_count:
        print("\n🎉 All tests passed!")
        return 0
    else:
        print(f"\n⚠️ {total_count - passed_count} test(s) failed")
        return 1


if __name__ == "__main__":
    sys.exit(run_all_tests())
