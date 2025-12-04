"""
Tests for ArxmlElement base class
"""
import pytest
from autosar_configurator.core.model.base import ArxmlElement
from autosar_configurator.core.model.observers import Observer
from typing import Any


class ConcreteElement(ArxmlElement):
    """Concrete implementation for testing"""

    def to_arxml(self) -> str:
        return f"<ELEMENT>{self.short_name}</ELEMENT>"

    @classmethod
    def from_arxml(cls, element: Any) -> 'ConcreteElement':
        return cls(short_name="test")


class TestObserver(Observer):
    """Mock observer for testing"""

    def __init__(self):
        self.events = []

    def update(self, event: str, data=None):
        self.events.append({'event': event, 'data': data})


class TestArxmlElement:
    """Tests for ArxmlElement class"""

    def test_create_element(self):
        """Test creating a basic element"""
        element = ConcreteElement(short_name="TestElement")

        assert element.short_name == "TestElement"
        assert element.uuid is not None
        assert element.parent is None
        assert element.description is None

    def test_short_name_validation_empty(self):
        """Test that empty short_name raises error"""
        with pytest.raises(ValueError, match="shortName cannot be empty"):
            ConcreteElement(short_name="")

    def test_short_name_validation_starts_with_number(self):
        """Test that short_name starting with number raises error"""
        with pytest.raises(ValueError, match="shortName must start with letter"):
            ConcreteElement(short_name="123Test")

    def test_short_name_validation_invalid_chars(self):
        """Test that invalid characters in short_name raise error"""
        with pytest.raises(ValueError, match="shortName contains invalid characters"):
            ConcreteElement(short_name="Test-Element")

        with pytest.raises(ValueError, match="shortName contains invalid characters"):
            ConcreteElement(short_name="Test Element")

    def test_short_name_validation_valid(self):
        """Test valid short_name formats"""
        # Should not raise
        ConcreteElement(short_name="TestElement")
        ConcreteElement(short_name="Test_Element")
        ConcreteElement(short_name="TestElement123")
        ConcreteElement(short_name="T")

    def test_uuid_generation(self):
        """Test that each element gets unique UUID"""
        elem1 = ConcreteElement(short_name="Elem1")
        elem2 = ConcreteElement(short_name="Elem2")

        assert elem1.uuid != elem2.uuid

    def test_dirty_tracking(self):
        """Test dirty flag tracking"""
        element = ConcreteElement(short_name="Test")

        assert not element.is_dirty

        element.mark_dirty()
        assert element.is_dirty

        element.mark_clean()
        assert not element.is_dirty

    def test_dirty_propagation_to_parent(self):
        """Test that marking dirty propagates to parent"""
        parent = ConcreteElement(short_name="Parent")
        child = ConcreteElement(short_name="Child")
        child.parent = parent

        assert not parent.is_dirty
        assert not child.is_dirty

        child.mark_dirty()

        assert child.is_dirty
        assert parent.is_dirty

    def test_get_path_root(self):
        """Test path generation for root element"""
        element = ConcreteElement(short_name="Root")

        assert element.get_path() == "/Root"

    def test_get_path_nested(self):
        """Test path generation for nested elements"""
        root = ConcreteElement(short_name="Root")
        child1 = ConcreteElement(short_name="Child1")
        child2 = ConcreteElement(short_name="Child2")

        child1.parent = root
        child2.parent = child1

        assert root.get_path() == "/Root"
        assert child1.get_path() == "/Root/Child1"
        assert child2.get_path() == "/Root/Child1/Child2"

    def test_observer_notification_on_dirty(self):
        """Test that observers are notified when element becomes dirty"""
        element = ConcreteElement(short_name="Test")
        observer = TestObserver()

        element.attach(observer)
        element.mark_dirty()

        assert len(observer.events) == 1
        assert observer.events[0]['event'] == 'modified'
        assert observer.events[0]['data'] == element

    def test_metadata_fields(self):
        """Test metadata fields"""
        element = ConcreteElement(
            short_name="Test",
            description="Test element",
            category="TEST_CATEGORY"
        )

        assert element.description == "Test element"
        assert element.category == "TEST_CATEGORY"

    def test_admin_data(self):
        """Test admin_data dictionary"""
        element = ConcreteElement(short_name="Test")

        element.admin_data['author'] = 'John Doe'
        element.admin_data['version'] = '1.0.0'

        assert element.admin_data['author'] == 'John Doe'
        assert element.admin_data['version'] == '1.0.0'

    def test_extensions(self):
        """Test extensions dictionary for OEM-specific data"""
        element = ConcreteElement(short_name="Test")

        element.extensions['oem_field'] = 'custom_value'

        assert element.extensions['oem_field'] == 'custom_value'

    def test_to_arxml(self):
        """Test ARXML serialization"""
        element = ConcreteElement(short_name="TestElement")

        arxml = element.to_arxml()

        assert "<ELEMENT>TestElement</ELEMENT>" in arxml

    def test_thread_safety(self):
        """Test thread-safe operations"""
        import threading

        element = ConcreteElement(short_name="Test")
        results = []

        def mark_dirty():
            element.mark_dirty()
            results.append(element.is_dirty)

        threads = [threading.Thread(target=mark_dirty) for _ in range(10)]

        for t in threads:
            t.start()

        for t in threads:
            t.join()

        assert element.is_dirty
        assert all(results)
