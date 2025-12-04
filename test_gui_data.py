"""
Simple test script to verify GUI functionality
"""
import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.model.container import Container, Parameter

# Create test data
root = Container(short_name="TestRoot", description="Test configuration")

# Add some child containers
can_module = Container(short_name="Can", description="CAN Driver configuration")
lin_module = Container(short_name="Lin", description="LIN Driver configuration")

root.add_sub_container(can_module)
root.add_sub_container(lin_module)

# Add parameters to CAN module
can_param1 = Parameter(
    short_name="CanBaudRate",
    value=500,
    value_type="INTEGER",
    min_value=125,
    max_value=1000,
    unit="kbps",
    description="CAN bus baud rate"
)

can_param2 = Parameter(
    short_name="CanMode",
    value="NORMAL",
    value_type="ENUM",
    enum_values=["NORMAL", "LOOPBACK", "SILENT"],
    description="CAN operating mode"
)

can_module.add_parameter(can_param1)
can_module.add_parameter(can_param2)

# Add parameters to LIN module
lin_param = Parameter(
    short_name="LinBaudRate",
    value=19200,
    value_type="INTEGER",
    min_value=9600,
    max_value=20000,
    unit="bps",
    description="LIN bus baud rate"
)

lin_module.add_parameter(lin_param)

print("Test data structure created successfully!")
print(f"Root: {root.short_name}")
print(f"  - {can_module.short_name} ({len(can_module.parameters)} parameters)")
print(f"  - {lin_module.short_name} ({len(lin_module.parameters)} parameters)")
