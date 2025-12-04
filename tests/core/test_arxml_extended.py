"""
Tests for ARXML parsing and serialization of extended parameter types
"""
import pytest
from pathlib import Path
from autosar_configurator.core.model.container import Container, Parameter
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.serializer.arxml_serializer import ArxmlSerializer

class TestArxmlExtended:
    """Test ARXML extended types"""

    @pytest.fixture
    def serializer(self):
        return ArxmlSerializer(use_namespaces=False)

    @pytest.fixture
    def parser(self):
        return ArxmlParser()

    def test_array_roundtrip(self, serializer, parser, tmp_path):
        """Test round-trip serialization of ARRAY parameter"""
        container = Container(short_name="ArrayContainer")
        param = Parameter(
            short_name="IntArray",
            value=[1, 2, 3],
            value_type="ARRAY",
            content_type="INTEGER"
        )
        container.add_parameter(param)

        # Serialize
        xml_str = serializer.serialize_to_string(container)
        assert "<TYPE>ARRAY</TYPE>" in xml_str
        assert "<ARRAY-VALUES>" in xml_str
        assert "<VALUE>1</VALUE>" in xml_str

        # Parse back
        parsed_container = parser.parse_string(xml_str)
        parsed_param = parsed_container.get_parameter("IntArray")
        
        assert parsed_param is not None
        assert parsed_param.value_type == "ARRAY"
        assert parsed_param.content_type == "INTEGER"
        assert isinstance(parsed_param.value, list)
        assert len(parsed_param.value) == 3
        # Note: Parser returns strings by default, type conversion happens in validation or usage
        assert parsed_param.value == ["1", "2", "3"]

    def test_struct_roundtrip(self, serializer, parser):
        """Test round-trip serialization of STRUCT parameter"""
        container = Container(short_name="StructContainer")
        struct_val = {"id": 1, "name": "test"}
        param = Parameter(
            short_name="StructParam",
            value=struct_val,
            value_type="STRUCT"
        )
        container.add_parameter(param)

        # Serialize
        xml_str = serializer.serialize_to_string(container)
        assert "<TYPE>STRUCT</TYPE>" in xml_str
        assert "<STRUCT-VALUES>" in xml_str
        assert "<NAME>id</NAME>" in xml_str
        assert "<VALUE>1</VALUE>" in xml_str

        # Parse back
        parsed_container = parser.parse_string(xml_str)
        parsed_param = parsed_container.get_parameter("StructParam")
        
        assert parsed_param is not None
        assert parsed_param.value_type == "STRUCT"
        assert isinstance(parsed_param.value, dict)
        assert parsed_param.value["id"] == "1"
        assert parsed_param.value["name"] == "test"

    def test_mixed_types(self, serializer, parser):
        """Test container with mixed parameter types"""
        container = Container(short_name="MixedContainer")
        
        # Standard type
        p1 = Parameter(short_name="P1", value="val", value_type="STRING")
        container.add_parameter(p1)
        
        # Array
        p2 = Parameter(short_name="P2", value=["a", "b"], value_type="ARRAY")
        container.add_parameter(p2)
        
        # Struct
        p3 = Parameter(short_name="P3", value={"k": "v"}, value_type="STRUCT")
        container.add_parameter(p3)
        
        xml_str = serializer.serialize_to_string(container)
        parsed_container = parser.parse_string(xml_str)
        
        assert len(parsed_container.parameters) == 3
        assert parsed_container.get_parameter("P1").value == "val"
        assert parsed_container.get_parameter("P2").value == ["a", "b"]
        assert parsed_container.get_parameter("P3").value == {"k": "v"}
