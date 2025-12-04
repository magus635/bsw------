"""
Container and Parameter classes for AUTOSAR configuration
"""
from dataclasses import dataclass, field
from typing import Dict, Any, Optional, List
from .base import ArxmlElement


@dataclass
class Parameter(ArxmlElement):
    """AUTOSAR Parameter"""

    value: Any = None
    value_type: str = "STRING"  # STRING, INTEGER, FLOAT, BOOLEAN, ENUM, REFERENCE, ARRAY, STRUCT
    min_value: Optional[float] = None
    max_value: Optional[float] = None
    enum_values: Optional[List[str]] = None
    unit: Optional[str] = None
    
    # For ARRAY type
    content_type: str = "STRING"  # Type of array elements
    
    # For STRUCT type
    struct_definition: Optional[Dict[str, str]] = None  # Field name -> Type mapping

    def validate(self) -> List[str]:
        """Validate parameter value"""
        errors = []
        
        if self.value is None:
            return errors

        if self.value_type == "INTEGER":
            try:
                int(self.value)
            except (ValueError, TypeError):
                errors.append(f"Invalid integer value: {self.value}")

        elif self.value_type == "FLOAT":
            try:
                float(self.value)
            except (ValueError, TypeError):
                errors.append(f"Invalid float value: {self.value}")
                
        elif self.value_type == "BOOLEAN":
            if not isinstance(self.value, bool) and str(self.value).lower() not in ('true', 'false', '0', '1'):
                errors.append(f"Invalid boolean value: {self.value}")

        elif self.value_type == "REFERENCE":
            if not isinstance(self.value, str) or not self.value.strip():
                errors.append(f"Invalid reference value: {self.value}")
                
        elif self.value_type == "ARRAY":
            if not isinstance(self.value, list):
                errors.append(f"Array value must be a list, got {type(self.value)}")
            else:
                # Validate each element based on content_type
                for i, item in enumerate(self.value):
                    if self.content_type == "INTEGER":
                        try:
                            int(item)
                        except (ValueError, TypeError):
                            errors.append(f"Invalid integer at index {i}: {item}")
                    elif self.content_type == "FLOAT":
                        try:
                            float(item)
                        except (ValueError, TypeError):
                            errors.append(f"Invalid float at index {i}: {item}")
                            
        elif self.value_type == "STRUCT":
            if not isinstance(self.value, dict):
                errors.append(f"Struct value must be a dictionary, got {type(self.value)}")
            elif self.struct_definition:
                # Validate fields against definition
                for field_name, field_type in self.struct_definition.items():
                    if field_name not in self.value:
                        errors.append(f"Missing required struct field: {field_name}")
                    else:
                        # Basic type check for fields (simplified)
                        field_val = self.value[field_name]
                        if field_type == "INTEGER":
                            try:
                                int(field_val)
                            except (ValueError, TypeError):
                                errors.append(f"Invalid integer for field {field_name}: {field_val}")

        # Numeric constraints (only for scalar numbers)
        if self.value_type in ["INTEGER", "FLOAT"] and self.value is not None:
            try:
                val = float(self.value)
                if self.min_value is not None and val < self.min_value:
                    errors.append(f"Value {self.value} below minimum {self.min_value}")
                if self.max_value is not None and val > self.max_value:
                    errors.append(f"Value {self.value} above maximum {self.max_value}")
            except (ValueError, TypeError):
                pass

        if self.enum_values and self.value not in self.enum_values:
            errors.append(f"Value {self.value} not in allowed values: {self.enum_values}")

        return errors

    def to_arxml(self) -> str:
        """Serialize to ARXML"""
        return f"""<PARAMETER>
    <SHORT-NAME>{self.short_name}</SHORT-NAME>
    <VALUE>{self.value}</VALUE>
    <TYPE>{self.value_type}</TYPE>
</PARAMETER>"""

    @classmethod
    def from_arxml(cls, element: Any) -> 'Parameter':
        """Parse from ARXML element"""
        # Simplified implementation
        return cls(short_name="placeholder")


@dataclass
class Container(ArxmlElement):
    """AUTOSAR Container"""

    sub_containers: Dict[str, 'Container'] = field(default_factory=dict)
    parameters: Dict[str, Parameter] = field(default_factory=dict)
    references: Dict[str, str] = field(default_factory=dict)

    # Multiplicity constraints
    min_multiplicity: int = 0
    max_multiplicity: int = 1  # -1 for unlimited

    def add_sub_container(self, container: 'Container'):
        """Add a sub-container"""
        with self._lock:
            if container.short_name in self.sub_containers:
                raise ValueError(f"Container {container.short_name} already exists")
            container.parent = self
            self.sub_containers[container.short_name] = container
            self.mark_dirty()
            self.notify('container_added', container)

    def remove_sub_container(self, short_name: str) -> Optional['Container']:
        """Remove a sub-container"""
        with self._lock:
            if short_name not in self.sub_containers:
                return None
            container = self.sub_containers.pop(short_name)
            self.mark_dirty()
            self.notify('container_removed', container)
            return container

    def add_parameter(self, param: Parameter):
        """Add a parameter"""
        with self._lock:
            if param.short_name in self.parameters:
                raise ValueError(f"Parameter {param.short_name} already exists")
            param.parent = self
            self.parameters[param.short_name] = param
            self.mark_dirty()
            self.notify('parameter_added', param)

    def remove_parameter(self, short_name: str) -> Optional[Parameter]:
        """Remove a parameter"""
        with self._lock:
            if short_name not in self.parameters:
                return None
            parameter = self.parameters.pop(short_name)
            self.mark_dirty()
            self.notify('parameter_removed', parameter)
            return parameter

    def get_parameter(self, name: str) -> Optional[Parameter]:
        """Get parameter by name"""
        return self.parameters.get(name)

    def get_sub_container(self, name: str) -> Optional['Container']:
        """Get sub-container by name"""
        return self.sub_containers.get(name)

    def to_arxml(self) -> str:
        """Serialize to ARXML"""
        params_xml = '\n'.join(p.to_arxml() for p in self.parameters.values())
        containers_xml = '\n'.join(c.to_arxml() for c in self.sub_containers.values())

        return f"""<CONTAINER>
    <SHORT-NAME>{self.short_name}</SHORT-NAME>
    <PARAMETERS>
{params_xml}
    </PARAMETERS>
    <SUB-CONTAINERS>
{containers_xml}
    </SUB-CONTAINERS>
</CONTAINER>"""

    @classmethod
    def from_arxml(cls, element: Any) -> 'Container':
        """Parse from ARXML element"""
        # Simplified implementation
        return cls(short_name="placeholder")
