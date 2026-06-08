"""
Hardware Resource Mapper
Maps hardware resources to AUTOSAR configuration parameters
"""
from dataclasses import dataclass, field
from enum import Enum
from typing import List, Dict, Any, Optional

from .chip_database import ChipDefinition, CanResourceDef, PortPinDef


class MappingActionType(Enum):
    """Type of mapping action"""
    CREATE_CONTAINER = "create_container"
    SET_PARAMETER = "set_parameter"
    SET_REFERENCE = "set_reference"


@dataclass
class MappingAction:
    """A single hardware mapping action"""
    action_type: MappingActionType
    module: str
    container_path: str
    parameter_name: Optional[str] = None
    value: Any = None
    description: str = ""

    def __str__(self):
        if self.action_type == MappingActionType.CREATE_CONTAINER:
            return f"Create {self.container_path}"
        elif self.action_type == MappingActionType.SET_PARAMETER:
            return f"Set {self.container_path}/{self.parameter_name} = {self.value}"
        else:
            return f"Set reference {self.container_path}/{self.parameter_name} -> {self.value}"


@dataclass
class MappingResult:
    """Result of applying mapping actions"""
    applied: int = 0
    skipped: int = 0
    failed: int = 0

    def __str__(self):
        parts = [f"applied={self.applied}"]
        if self.skipped:
            parts.append(f"skipped={self.skipped} (not implemented)")
        if self.failed:
            parts.append(f"failed={self.failed}")
        return ", ".join(parts)

    @property
    def total(self):
        return self.applied + self.skipped + self.failed


class HardwareResourceMapper:
    """Maps hardware resources to AUTOSAR configuration"""

    def __init__(self, chip: ChipDefinition):
        """Initialize mapper with chip definition

        Args:
            chip: Chip definition to use for mapping
        """
        self.chip = chip

    def generate_can_mapping(self,
                             controllers: Optional[List[int]] = None,
                             baudrate: int = 500000) -> List[MappingAction]:
        """Generate CAN controller mapping actions

        Args:
            controllers: List of controller IDs to configure, or None for all
            baudrate: Default baudrate for controllers

        Returns:
            List of mapping actions
        """
        actions = []

        can_resources = self.chip.can_resources
        if controllers:
            can_resources = [c for c in can_resources if c.controller_id in controllers]

        for can in can_resources:
            # Create CanController container
            container_path = f"CanConfigSet/CanController_{can.controller_id}"

            actions.append(MappingAction(
                action_type=MappingActionType.CREATE_CONTAINER,
                module="Can",
                container_path=container_path,
                description=f"Create CAN Controller {can.name}"
            ))

            # Set controller ID
            actions.append(MappingAction(
                action_type=MappingActionType.SET_PARAMETER,
                module="Can",
                container_path=container_path,
                parameter_name="CanControllerId",
                value=can.controller_id,
                description=f"Set controller ID to {can.controller_id}"
            ))

            # Set baudrate (within limits)
            actual_baudrate = min(baudrate, can.max_baudrate)
            actions.append(MappingAction(
                action_type=MappingActionType.SET_PARAMETER,
                module="Can",
                container_path=container_path,
                parameter_name="CanControllerDefaultBaudrate",
                value=actual_baudrate,
                description=f"Set baudrate to {actual_baudrate}"
            ))

            # Enable controller
            actions.append(MappingAction(
                action_type=MappingActionType.SET_PARAMETER,
                module="Can",
                container_path=container_path,
                parameter_name="CanControllerActivation",
                value=True,
                description="Enable controller"
            ))

            # CAN FD support if available
            if can.supports_fd:
                actions.append(MappingAction(
                    action_type=MappingActionType.SET_PARAMETER,
                    module="Can",
                    container_path=container_path,
                    parameter_name="CanControllerFdBaudrateConfig",
                    value=True,
                    description="Enable CAN FD support"
                ))

        return actions

    def generate_port_mapping(self,
                              port_names: Optional[List[str]] = None,
                              default_direction: str = "INPUT") -> List[MappingAction]:
        """Generate Port pin mapping actions

        Args:
            port_names: List of port names to configure, or None for all
            default_direction: Default pin direction

        Returns:
            List of mapping actions
        """
        actions = []

        ports = self.chip.ports
        if port_names:
            ports = {k: v for k, v in ports.items() if k in port_names}

        for port_name, pins in ports.items():
            # Create PortContainer for each port
            port_container = f"PortConfigSet/PortContainer_{port_name}"

            actions.append(MappingAction(
                action_type=MappingActionType.CREATE_CONTAINER,
                module="Port",
                container_path=port_container,
                description=f"Create Port container for {port_name}"
            ))

            # Create PortPin for each pin
            for pin in pins:
                pin_container = f"{port_container}/PortPin_{pin.name}"

                actions.append(MappingAction(
                    action_type=MappingActionType.CREATE_CONTAINER,
                    module="Port",
                    container_path=pin_container,
                    description=f"Create pin {pin.name}"
                ))

                # Set pin ID (port * 16 + pin number is common convention)
                port_idx = ord(port_name[-1]) - ord('A') if port_name else 0
                pin_id = port_idx * 16 + pin.pin

                actions.append(MappingAction(
                    action_type=MappingActionType.SET_PARAMETER,
                    module="Port",
                    container_path=pin_container,
                    parameter_name="PortPinId",
                    value=pin_id,
                    description=f"Set pin ID to {pin_id}"
                ))

                # Set direction
                direction = pin.default_direction or default_direction
                actions.append(MappingAction(
                    action_type=MappingActionType.SET_PARAMETER,
                    module="Port",
                    container_path=pin_container,
                    parameter_name="PortPinDirection",
                    value=direction,
                    description=f"Set direction to {direction}"
                ))

        return actions

    def generate_adc_mapping(self,
                             units: Optional[List[int]] = None,
                             channels: Optional[List[int]] = None) -> List[MappingAction]:
        """Generate ADC unit mapping actions

        Args:
            units: List of ADC unit IDs to configure, or None for all
            channels: List of channel IDs to configure per unit, or None for all

        Returns:
            List of mapping actions
        """
        actions = []

        adc_resources = self.chip.adc_resources
        if units:
            adc_resources = [a for a in adc_resources if a.unit_id in units]

        for adc in adc_resources:
            # Create AdcHwUnit container
            unit_container = f"AdcConfigSet/AdcHwUnit_{adc.unit_id}"

            actions.append(MappingAction(
                action_type=MappingActionType.CREATE_CONTAINER,
                module="Adc",
                container_path=unit_container,
                description=f"Create ADC unit {adc.name}"
            ))

            actions.append(MappingAction(
                action_type=MappingActionType.SET_PARAMETER,
                module="Adc",
                container_path=unit_container,
                parameter_name="AdcHwUnitId",
                value=adc.unit_id,
                description=f"Set unit ID to {adc.unit_id}"
            ))

            # Configure channels
            channel_list = channels if channels else adc.channels
            for ch in channel_list:
                if ch not in adc.channels:
                    continue

                ch_container = f"{unit_container}/AdcChannel_{ch}"

                actions.append(MappingAction(
                    action_type=MappingActionType.CREATE_CONTAINER,
                    module="Adc",
                    container_path=ch_container,
                    description=f"Create ADC channel {ch}"
                ))

                actions.append(MappingAction(
                    action_type=MappingActionType.SET_PARAMETER,
                    module="Adc",
                    container_path=ch_container,
                    parameter_name="AdcChannelId",
                    value=ch,
                    description=f"Set channel ID to {ch}"
                ))

        return actions

    def generate_mcu_mapping(self) -> List[MappingAction]:
        """Generate MCU clock/peripheral mapping actions

        Returns:
            List of mapping actions
        """
        actions = []

        # Create basic MCU configuration
        actions.append(MappingAction(
            action_type=MappingActionType.CREATE_CONTAINER,
            module="Mcu",
            container_path="McuModuleConfiguration",
            description="Create MCU module configuration"
        ))

        # Add clock configuration
        actions.append(MappingAction(
            action_type=MappingActionType.CREATE_CONTAINER,
            module="Mcu",
            container_path="McuModuleConfiguration/McuClockSettingConfig",
            description="Create clock setting configuration"
        ))

        return actions

    def generate_intc_mapping(self,
                              sources: Optional[List[str]] = None) -> List[MappingAction]:
        """Generate interrupt controller mapping actions

        Args:
            sources: List of interrupt source names to configure, or None for all

        Returns:
            List of mapping actions
        """
        actions = []

        intc_sources = self.chip.intc_sources
        if sources:
            intc_sources = [i for i in intc_sources if i.name in sources]

        for intc in intc_sources:
            if not intc.is_configurable:
                continue

            container_path = f"IntcConfig/IntcSource_{intc.name}"

            actions.append(MappingAction(
                action_type=MappingActionType.CREATE_CONTAINER,
                module="Intc",
                container_path=container_path,
                description=f"Create interrupt source {intc.name}"
            ))

            actions.append(MappingAction(
                action_type=MappingActionType.SET_PARAMETER,
                module="Intc",
                container_path=container_path,
                parameter_name="IntcVectorNumber",
                value=intc.vector_number,
                description=f"Set vector number to {intc.vector_number}"
            ))

        return actions

    def apply_mappings(self, actions: List[MappingAction], config_manager) -> MappingResult:
        """Apply mapping actions to configuration — delegates to GenericResourceMapper logic."""
        from .generic_mapper import GenericResourceMapper
        delegate = GenericResourceMapper.__new__(GenericResourceMapper)
        return delegate.apply_actions(actions, config_manager)

    def get_available_modules(self) -> List[str]:
        """Get list of modules that can be configured for this chip"""
        modules = []

        if self.chip.ports:
            modules.append("Port")
        if self.chip.can_resources:
            modules.append("Can")
        if self.chip.adc_resources:
            modules.append("Adc")
        if self.chip.spi_resources:
            modules.append("Spi")
        if self.chip.intc_sources:
            modules.append("Intc")

        # MCU is always available
        modules.append("Mcu")

        return sorted(modules)
