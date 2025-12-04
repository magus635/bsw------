"""
Tests for Container and Parameter classes
"""
import pytest
from autosar_configurator.core.model.container import Container, Parameter
from autosar_configurator.core.model.observers import Observer


class TestObserver(Observer):
    """Mock observer for testing"""

    def __init__(self):
        self.events = []

    def update(self, event: str, data=None):
        self.events.append({'event': event, 'data': data})


class TestParameter:
    """Tests for Parameter class"""

    def test_create_parameter(self):
        """Test creating a basic parameter"""
        param = Parameter(short_name="TestParam", value=100, value_type="INTEGER")

        assert param.short_name == "TestParam"
        assert param.value == 100
        assert param.value_type == "INTEGER"

    def test_parameter_default_type(self):
        """Test parameter default value type"""
        param = Parameter(short_name="TestParam")

        assert param.value_type == "STRING"

    def test_validate_integer_valid(self):
        """Test validating valid integer"""
        param = Parameter(short_name="Test", value=42, value_type="INTEGER")

        errors = param.validate()
        assert len(errors) == 0

    def test_validate_integer_invalid(self):
        """Test validating invalid integer"""
        param = Parameter(short_name="Test", value="not_a_number", value_type="INTEGER")

        errors = param.validate()
        assert len(errors) == 1
        assert "Invalid integer value" in errors[0]

    def test_validate_float_valid(self):
        """Test validating valid float"""
        param = Parameter(short_name="Test", value=3.14, value_type="FLOAT")

        errors = param.validate()
        assert len(errors) == 0

    def test_validate_float_invalid(self):
        """Test validating invalid float"""
        param = Parameter(short_name="Test", value="abc", value_type="FLOAT")

        errors = param.validate()
        assert len(errors) == 1
        assert "Invalid float value" in errors[0]

    def test_validate_min_value(self):
        """Test minimum value validation"""
        param = Parameter(
            short_name="Test",
            value=5,
            value_type="INTEGER",
            min_value=10
        )

        errors = param.validate()
        assert len(errors) == 1
        assert "below minimum" in errors[0]

    def test_validate_max_value(self):
        """Test maximum value validation"""
        param = Parameter(
            short_name="Test",
            value=100,
            value_type="INTEGER",
            max_value=50
        )

        errors = param.validate()
        assert len(errors) == 1
        assert "above maximum" in errors[0]

    def test_validate_range_valid(self):
        """Test value within valid range"""
        param = Parameter(
            short_name="Test",
            value=25,
            value_type="INTEGER",
            min_value=0,
            max_value=100
        )

        errors = param.validate()
        assert len(errors) == 0

    def test_validate_enum_valid(self):
        """Test valid enum value"""
        param = Parameter(
            short_name="Test",
            value="OPTION_A",
            value_type="ENUM",
            enum_values=["OPTION_A", "OPTION_B", "OPTION_C"]
        )

        errors = param.validate()
        assert len(errors) == 0

    def test_validate_enum_invalid(self):
        """Test invalid enum value"""
        param = Parameter(
            short_name="Test",
            value="OPTION_D",
            value_type="ENUM",
            enum_values=["OPTION_A", "OPTION_B", "OPTION_C"]
        )

        errors = param.validate()
        assert len(errors) == 1
        assert "not in allowed values" in errors[0]

    def test_validate_none_value(self):
        """Test validation with None value"""
        param = Parameter(
            short_name="Test",
            value=None,
            value_type="INTEGER",
            min_value=0,
            max_value=100
        )

        errors = param.validate()
        assert len(errors) == 0  # None values should not trigger validation errors

    def test_parameter_to_arxml(self):
        """Test ARXML serialization"""
        param = Parameter(
            short_name="TestParam",
            value=100,
            value_type="INTEGER"
        )

        arxml = param.to_arxml()

        assert "<PARAMETER>" in arxml
        assert "<SHORT-NAME>TestParam</SHORT-NAME>" in arxml
        assert "<VALUE>100</VALUE>" in arxml
        assert "<TYPE>INTEGER</TYPE>" in arxml

    def test_parameter_with_unit(self):
        """Test parameter with unit"""
        param = Parameter(
            short_name="Speed",
            value=100,
            value_type="INTEGER",
            unit="km/h"
        )

        assert param.unit == "km/h"


class TestContainer:
    """Tests for Container class"""

    def test_create_container(self):
        """Test creating a basic container"""
        container = Container(short_name="TestContainer")

        assert container.short_name == "TestContainer"
        assert len(container.sub_containers) == 0
        assert len(container.parameters) == 0

    def test_add_parameter(self):
        """Test adding a parameter to container"""
        container = Container(short_name="TestContainer")
        param = Parameter(short_name="Param1", value=100)

        container.add_parameter(param)

        assert "Param1" in container.parameters
        assert container.parameters["Param1"] == param
        assert param.parent == container

    def test_add_duplicate_parameter(self):
        """Test adding duplicate parameter raises error"""
        container = Container(short_name="TestContainer")
        param1 = Parameter(short_name="Param1", value=100)
        param2 = Parameter(short_name="Param1", value=200)

        container.add_parameter(param1)

        with pytest.raises(ValueError, match="Parameter Param1 already exists"):
            container.add_parameter(param2)

    def test_get_parameter(self):
        """Test getting parameter by name"""
        container = Container(short_name="TestContainer")
        param = Parameter(short_name="Param1", value=100)

        container.add_parameter(param)

        retrieved = container.get_parameter("Param1")
        assert retrieved == param

    def test_get_nonexistent_parameter(self):
        """Test getting non-existent parameter returns None"""
        container = Container(short_name="TestContainer")

        retrieved = container.get_parameter("NonExistent")
        assert retrieved is None

    def test_add_sub_container(self):
        """Test adding a sub-container"""
        parent = Container(short_name="Parent")
        child = Container(short_name="Child")

        parent.add_sub_container(child)

        assert "Child" in parent.sub_containers
        assert parent.sub_containers["Child"] == child
        assert child.parent == parent

    def test_add_duplicate_sub_container(self):
        """Test adding duplicate sub-container raises error"""
        parent = Container(short_name="Parent")
        child1 = Container(short_name="Child")
        child2 = Container(short_name="Child")

        parent.add_sub_container(child1)

        with pytest.raises(ValueError, match="Container Child already exists"):
            parent.add_sub_container(child2)

    def test_get_sub_container(self):
        """Test getting sub-container by name"""
        parent = Container(short_name="Parent")
        child = Container(short_name="Child")

        parent.add_sub_container(child)

        retrieved = parent.get_sub_container("Child")
        assert retrieved == child

    def test_remove_sub_container(self):
        """Test removing a sub-container"""
        parent = Container(short_name="Parent")
        child = Container(short_name="Child")

        parent.add_sub_container(child)
        removed = parent.remove_sub_container("Child")

        assert removed == child
        assert "Child" not in parent.sub_containers

    def test_remove_nonexistent_sub_container(self):
        """Test removing non-existent sub-container returns None"""
        parent = Container(short_name="Parent")

        removed = parent.remove_sub_container("NonExistent")
        assert removed is None

    def test_container_dirty_on_parameter_add(self):
        """Test container is marked dirty when parameter added"""
        container = Container(short_name="TestContainer")
        param = Parameter(short_name="Param1", value=100)

        container.add_parameter(param)

        assert container.is_dirty

    def test_container_dirty_on_sub_container_add(self):
        """Test container is marked dirty when sub-container added"""
        parent = Container(short_name="Parent")
        child = Container(short_name="Child")

        parent.add_sub_container(child)

        assert parent.is_dirty

    def test_container_dirty_on_sub_container_remove(self):
        """Test container is marked dirty when sub-container removed"""
        parent = Container(short_name="Parent")
        child = Container(short_name="Child")

        parent.add_sub_container(child)
        parent.mark_clean()

        parent.remove_sub_container("Child")

        assert parent.is_dirty

    def test_observer_notification_on_parameter_add(self):
        """Test observers are notified when parameter is added"""
        container = Container(short_name="TestContainer")
        observer = TestObserver()
        param = Parameter(short_name="Param1", value=100)

        container.attach(observer)
        container.add_parameter(param)

        events = [e['event'] for e in observer.events]
        assert 'parameter_added' in events

    def test_observer_notification_on_container_add(self):
        """Test observers are notified when sub-container is added"""
        parent = Container(short_name="Parent")
        observer = TestObserver()
        child = Container(short_name="Child")

        parent.attach(observer)
        parent.add_sub_container(child)

        events = [e['event'] for e in observer.events]
        assert 'container_added' in events

    def test_observer_notification_on_container_remove(self):
        """Test observers are notified when sub-container is removed"""
        parent = Container(short_name="Parent")
        observer = TestObserver()
        child = Container(short_name="Child")

        parent.add_sub_container(child)
        parent.attach(observer)
        parent.remove_sub_container("Child")

        events = [e['event'] for e in observer.events]
        assert 'container_removed' in events

    def test_container_to_arxml(self):
        """Test ARXML serialization"""
        container = Container(short_name="TestContainer")
        param = Parameter(short_name="Param1", value=100)
        child = Container(short_name="ChildContainer")

        container.add_parameter(param)
        container.add_sub_container(child)

        arxml = container.to_arxml()

        assert "<CONTAINER>" in arxml
        assert "<SHORT-NAME>TestContainer</SHORT-NAME>" in arxml
        assert "<PARAMETERS>" in arxml
        assert "<SUB-CONTAINERS>" in arxml

    def test_multiplicity_constraints(self):
        """Test multiplicity constraint attributes"""
        container = Container(
            short_name="Test",
            min_multiplicity=1,
            max_multiplicity=5
        )

        assert container.min_multiplicity == 1
        assert container.max_multiplicity == 5

    def test_references(self):
        """Test reference dictionary"""
        container = Container(short_name="Test")

        container.references["ModuleRef"] = "/Path/To/Module"

        assert container.references["ModuleRef"] == "/Path/To/Module"

    def test_nested_structure(self):
        """Test complex nested structure"""
        root = Container(short_name="Root")
        level1 = Container(short_name="Level1")
        level2 = Container(short_name="Level2")
        param = Parameter(short_name="Param", value=42)

        root.add_sub_container(level1)
        level1.add_sub_container(level2)
        level2.add_parameter(param)

        assert root.get_sub_container("Level1") == level1
        assert level1.get_sub_container("Level2") == level2
        assert level2.get_parameter("Param") == param
        assert param.get_path() == "/Root/Level1/Level2/Param"

    def test_thread_safety_parameter_add(self):
        """Test thread-safe parameter addition"""
        import threading

        container = Container(short_name="Test")
        results = []

        def add_param(i):
            param = Parameter(short_name=f"Param{i}", value=i)
            try:
                container.add_parameter(param)
                results.append(True)
            except Exception:
                results.append(False)

        threads = [threading.Thread(target=add_param, args=(i,)) for i in range(10)]

        for t in threads:
            t.start()

        for t in threads:
            t.join()

        assert len(container.parameters) == 10
        assert all(results)
