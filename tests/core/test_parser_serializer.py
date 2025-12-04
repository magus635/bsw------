"""
Tests for ARXML parser and serializer
"""
import pytest
from pathlib import Path
import tempfile
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.serializer.arxml_serializer import ArxmlSerializer
from autosar_configurator.core.model.container import Container, Parameter


class TestArxmlParser:
    """Tests for ArxmlParser"""

    def test_parse_simple_container(self):
        """Test parsing a simple container"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>TestContainer</SHORT-NAME>
    <DESC>Test description</DESC>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        assert container.short_name == "TestContainer"
        assert container.description == "Test description"

    def test_parse_container_with_parameters(self):
        """Test parsing container with parameters"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>ConfigContainer</SHORT-NAME>
    <PARAMETERS>
        <PARAMETER>
            <SHORT-NAME>Param1</SHORT-NAME>
            <VALUE>100</VALUE>
            <TYPE>INTEGER</TYPE>
        </PARAMETER>
        <PARAMETER>
            <SHORT-NAME>Param2</SHORT-NAME>
            <VALUE>Hello</VALUE>
            <TYPE>STRING</TYPE>
        </PARAMETER>
    </PARAMETERS>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        assert container.short_name == "ConfigContainer"
        assert len(container.parameters) == 2
        assert container.get_parameter("Param1").value == "100"
        assert container.get_parameter("Param2").value == "Hello"

    def test_parse_parameter_with_constraints(self):
        """Test parsing parameter with min/max constraints"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>Test</SHORT-NAME>
    <PARAMETERS>
        <PARAMETER>
            <SHORT-NAME>Speed</SHORT-NAME>
            <VALUE>50</VALUE>
            <TYPE>INTEGER</TYPE>
            <MIN-VALUE>0</MIN-VALUE>
            <MAX-VALUE>100</MAX-VALUE>
            <UNIT>km/h</UNIT>
        </PARAMETER>
    </PARAMETERS>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        param = container.get_parameter("Speed")
        assert param.value == "50"
        assert param.min_value == 0.0
        assert param.max_value == 100.0
        assert param.unit == "km/h"

    def test_parse_parameter_with_enum(self):
        """Test parsing parameter with enum values"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>Test</SHORT-NAME>
    <PARAMETERS>
        <PARAMETER>
            <SHORT-NAME>Mode</SHORT-NAME>
            <VALUE>OPTION_A</VALUE>
            <TYPE>ENUM</TYPE>
            <ENUM-VALUES>
                <ENUM-VALUE>OPTION_A</ENUM-VALUE>
                <ENUM-VALUE>OPTION_B</ENUM-VALUE>
                <ENUM-VALUE>OPTION_C</ENUM-VALUE>
            </ENUM-VALUES>
        </PARAMETER>
    </PARAMETERS>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        param = container.get_parameter("Mode")
        assert param.value == "OPTION_A"
        assert param.enum_values == ["OPTION_A", "OPTION_B", "OPTION_C"]

    def test_parse_nested_containers(self):
        """Test parsing nested containers"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>Parent</SHORT-NAME>
    <SUB-CONTAINERS>
        <CONTAINER>
            <SHORT-NAME>Child1</SHORT-NAME>
        </CONTAINER>
        <CONTAINER>
            <SHORT-NAME>Child2</SHORT-NAME>
            <SUB-CONTAINERS>
                <CONTAINER>
                    <SHORT-NAME>GrandChild</SHORT-NAME>
                </CONTAINER>
            </SUB-CONTAINERS>
        </CONTAINER>
    </SUB-CONTAINERS>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        assert container.short_name == "Parent"
        assert len(container.sub_containers) == 2
        assert container.get_sub_container("Child1") is not None
        assert container.get_sub_container("Child2") is not None

        child2 = container.get_sub_container("Child2")
        assert len(child2.sub_containers) == 1
        assert child2.get_sub_container("GrandChild") is not None

    def test_parse_file_not_found(self):
        """Test parsing non-existent file"""
        parser = ArxmlParser()

        with pytest.raises(FileNotFoundError):
            parser.parse_file(Path("/nonexistent/file.arxml"))

    def test_parse_invalid_xml(self):
        """Test parsing invalid XML"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER>
    <SHORT-NAME>Test
</CONTAINER>"""

        parser = ArxmlParser()

        with pytest.raises(ValueError, match="XML parsing error"):
            parser.parse_string(xml)

    def test_parse_with_namespaces(self):
        """Test parsing with AUTOSAR namespaces"""
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<CONTAINER xmlns="http://autosar.org/schema/r4.0">
    <SHORT-NAME>TestContainer</SHORT-NAME>
    <PARAMETERS>
        <PARAMETER>
            <SHORT-NAME>Param1</SHORT-NAME>
            <VALUE>42</VALUE>
            <TYPE>INTEGER</TYPE>
        </PARAMETER>
    </PARAMETERS>
</CONTAINER>"""

        parser = ArxmlParser()
        container = parser.parse_string(xml)

        assert container.short_name == "TestContainer"
        assert len(container.parameters) == 1


class TestArxmlSerializer:
    """Tests for ArxmlSerializer"""

    def test_serialize_simple_container(self):
        """Test serializing a simple container"""
        container = Container(short_name="TestContainer", description="Test description")

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<SHORT-NAME>TestContainer</SHORT-NAME>" in xml_string
        assert "<DESC>Test description</DESC>" in xml_string

    def test_serialize_container_with_parameters(self):
        """Test serializing container with parameters"""
        container = Container(short_name="ConfigContainer")
        param1 = Parameter(short_name="Param1", value=100, value_type="INTEGER")
        param2 = Parameter(short_name="Param2", value="Hello", value_type="STRING")

        container.add_parameter(param1)
        container.add_parameter(param2)

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<PARAMETERS>" in xml_string
        assert "<SHORT-NAME>Param1</SHORT-NAME>" in xml_string
        assert "<VALUE>100</VALUE>" in xml_string
        assert "<SHORT-NAME>Param2</SHORT-NAME>" in xml_string
        assert "<VALUE>Hello</VALUE>" in xml_string

    def test_serialize_parameter_with_constraints(self):
        """Test serializing parameter with constraints"""
        container = Container(short_name="Test")
        param = Parameter(
            short_name="Speed",
            value=50,
            value_type="INTEGER",
            min_value=0,
            max_value=100,
            unit="km/h"
        )

        container.add_parameter(param)

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<MIN-VALUE>0</MIN-VALUE>" in xml_string
        assert "<MAX-VALUE>100</MAX-VALUE>" in xml_string
        assert "<UNIT>km/h</UNIT>" in xml_string

    def test_serialize_parameter_with_enum(self):
        """Test serializing parameter with enum values"""
        container = Container(short_name="Test")
        param = Parameter(
            short_name="Mode",
            value="OPTION_A",
            value_type="ENUM",
            enum_values=["OPTION_A", "OPTION_B", "OPTION_C"]
        )

        container.add_parameter(param)

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<ENUM-VALUES>" in xml_string
        assert "<ENUM-VALUE>OPTION_A</ENUM-VALUE>" in xml_string
        assert "<ENUM-VALUE>OPTION_B</ENUM-VALUE>" in xml_string
        assert "<ENUM-VALUE>OPTION_C</ENUM-VALUE>" in xml_string

    def test_serialize_nested_containers(self):
        """Test serializing nested containers"""
        parent = Container(short_name="Parent")
        child1 = Container(short_name="Child1")
        child2 = Container(short_name="Child2")

        parent.add_sub_container(child1)
        parent.add_sub_container(child2)

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(parent)

        assert "<SUB-CONTAINERS>" in xml_string
        assert "<SHORT-NAME>Child1</SHORT-NAME>" in xml_string
        assert "<SHORT-NAME>Child2</SHORT-NAME>" in xml_string

    def test_serialize_to_file(self):
        """Test serializing to file"""
        container = Container(short_name="TestContainer")
        param = Parameter(short_name="TestParam", value=42)
        container.add_parameter(param)

        serializer = ArxmlSerializer(use_namespaces=False)

        with tempfile.NamedTemporaryFile(mode='w', suffix='.arxml', delete=False) as f:
            temp_path = Path(f.name)

        try:
            serializer.serialize_to_file(container, temp_path)

            # Verify file exists and contains expected content
            assert temp_path.exists()
            content = temp_path.read_text()
            assert "<SHORT-NAME>TestContainer</SHORT-NAME>" in content
            assert "<SHORT-NAME>TestParam</SHORT-NAME>" in content

        finally:
            if temp_path.exists():
                temp_path.unlink()

    def test_serialize_with_namespaces(self):
        """Test serializing with AUTOSAR namespaces"""
        container = Container(short_name="TestContainer")

        serializer = ArxmlSerializer(use_namespaces=True)
        xml_string = serializer.serialize_to_string(container)

        assert 'xmlns="http://autosar.org/schema/r4.0"' in xml_string
        assert 'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"' in xml_string

    def test_serialize_multiplicity(self):
        """Test serializing container with multiplicity"""
        container = Container(
            short_name="TestContainer",
            min_multiplicity=1,
            max_multiplicity=5
        )

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<MULTIPLICITY>" in xml_string
        assert "<MIN>1</MIN>" in xml_string
        assert "<MAX>5</MAX>" in xml_string

    def test_serialize_unbounded_multiplicity(self):
        """Test serializing container with unbounded multiplicity"""
        container = Container(
            short_name="TestContainer",
            min_multiplicity=0,
            max_multiplicity=-1
        )

        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(container)

        assert "<MULTIPLICITY>" in xml_string
        assert "<MAX>UNBOUNDED</MAX>" in xml_string


class TestParserSerializerRoundTrip:
    """Test roundtrip parsing and serialization"""

    def test_roundtrip_simple(self):
        """Test simple roundtrip"""
        # Create original container
        original = Container(short_name="Test")
        param = Parameter(short_name="Param1", value=42, value_type="INTEGER")
        original.add_parameter(param)

        # Serialize
        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(original)

        # Parse back
        parser = ArxmlParser()
        parsed = parser.parse_string(xml_string)

        # Verify
        assert parsed.short_name == original.short_name
        assert len(parsed.parameters) == 1
        param = parsed.get_parameter("Param1")
        assert param.value == "42"  # Note: parsed as string
        assert param.value_type == "INTEGER"

    def test_roundtrip_complex(self):
        """Test complex roundtrip with nested structure"""
        # Create complex structure
        root = Container(short_name="Root", description="Root container")

        child1 = Container(short_name="Child1")
        param1 = Parameter(
            short_name="Speed",
            value=50,
            value_type="INTEGER",
            min_value=0,
            max_value=100,
            unit="km/h"
        )
        child1.add_parameter(param1)

        child2 = Container(short_name="Child2")
        param2 = Parameter(
            short_name="Mode",
            value="OPTION_A",
            value_type="ENUM",
            enum_values=["OPTION_A", "OPTION_B"]
        )
        child2.add_parameter(param2)

        root.add_sub_container(child1)
        root.add_sub_container(child2)

        # Serialize
        serializer = ArxmlSerializer(use_namespaces=False)
        xml_string = serializer.serialize_to_string(root)

        # Parse back
        parser = ArxmlParser()
        parsed = parser.parse_string(xml_string)

        # Verify structure
        assert parsed.short_name == "Root"
        assert parsed.description == "Root container"
        assert len(parsed.sub_containers) == 2

        parsed_child1 = parsed.get_sub_container("Child1")
        assert parsed_child1 is not None
        assert len(parsed_child1.parameters) == 1

        speed_param = parsed_child1.get_parameter("Speed")
        assert speed_param.min_value == 0.0
        assert speed_param.max_value == 100.0
        assert speed_param.unit == "km/h"

        parsed_child2 = parsed.get_sub_container("Child2")
        assert parsed_child2 is not None

        mode_param = parsed_child2.get_parameter("Mode")
        assert mode_param.enum_values == ["OPTION_A", "OPTION_B"]
