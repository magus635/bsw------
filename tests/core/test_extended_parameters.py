"""
Unit tests for extended parameter types (REFERENCE, ARRAY, STRUCT)
"""
import pytest
from autosar_configurator.core.model.container import Parameter

class TestExtendedParameters:
    """Test extended parameter types"""

    def test_reference_validation(self):
        """Test REFERENCE type validation"""
        # Valid reference
        param = Parameter(short_name="RefParam", value="/Path/To/Element", value_type="REFERENCE")
        assert len(param.validate()) == 0

        # Invalid reference (empty)
        param.value = ""
        assert len(param.validate()) > 0
        
        # Invalid reference (not a string)
        param.value = 123
        assert len(param.validate()) > 0

    def test_array_validation(self):
        """Test ARRAY type validation"""
        # Valid integer array
        param = Parameter(
            short_name="IntArray", 
            value=[1, 2, 3], 
            value_type="ARRAY",
            content_type="INTEGER"
        )
        assert len(param.validate()) == 0

        # Valid float array
        param = Parameter(
            short_name="FloatArray", 
            value=[1.1, 2.2, 3.3], 
            value_type="ARRAY",
            content_type="FLOAT"
        )
        assert len(param.validate()) == 0

        # Invalid array (not a list)
        param.value = "not a list"
        assert len(param.validate()) > 0

        # Invalid array content (wrong type)
        param.value = [1, "two", 3]
        param.content_type = "INTEGER"
        assert len(param.validate()) > 0

    def test_struct_validation(self):
        """Test STRUCT type validation"""
        struct_def = {
            "id": "INTEGER",
            "name": "STRING",
            "enabled": "BOOLEAN"
        }
        
        # Valid struct
        valid_value = {
            "id": 1,
            "name": "Test",
            "enabled": True
        }
        param = Parameter(
            short_name="StructParam",
            value=valid_value,
            value_type="STRUCT",
            struct_definition=struct_def
        )
        assert len(param.validate()) == 0

        # Invalid struct (not a dict)
        param.value = [1, "Test", True]
        assert len(param.validate()) > 0

        # Missing field
        invalid_value = {
            "id": 1,
            "name": "Test"
            # Missing enabled
        }
        param.value = invalid_value
        assert len(param.validate()) > 0

        # Invalid field type
        invalid_type_value = {
            "id": "not an int",
            "name": "Test",
            "enabled": True
        }
        param.value = invalid_type_value
        assert len(param.validate()) > 0
