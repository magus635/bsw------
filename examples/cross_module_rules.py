"""
Cross-Module Validation Rules Example

This file demonstrates how to create custom Python-based validation rules
that check dependencies and consistency across multiple BSW modules.

Usage:
1. Load this file via "Tools > Load Custom Rules" in the AUTOSAR Configurator
2. Run validation to see cross-module checks

Requirements:
- The project must have multiple modules loaded (e.g., Can, CanIf, CanSM)
"""

from autosar_configurator.core.validation_engine import ValidationRule, ValidationResult


class CanIfBaudRateMatchRule(ValidationRule):
    """
    Validates that CanIf controller references match the baud rate
    configured in the referenced CanController.
    
    Cross-module dependency:
    - CanIf.CanIfCtrlCfg.CanIfCtrlBaudRate should match
    - Can.CanController.CanControllerBaudRate
    """
    
    def __init__(self):
        super().__init__(
            name="CanIfBaudRateMatch",
            description="CanIf controller baud rate must match referenced CanController baud rate"
        )
    
    def validate(self, module_def, configuration, project_context=None):
        result = ValidationResult()
        
        if not project_context:
            # Can't validate cross-module without project context
            return result
        
        # Get CanIf and Can module managers
        canif_mgr = project_context.module_managers.get('CanIf')
        can_mgr = project_context.module_managers.get('Can')
        
        if not canif_mgr or not can_mgr:
            # Modules not loaded, skip validation
            return result
        
        canif_config = canif_mgr.configuration
        can_config = can_mgr.configuration
        
        if not canif_config or not can_config:
            return result
        
        # Build a map of CanController names to their baud rates
        can_baudrates = {}
        for container in can_config.containers:
            if 'Controller' in container.short_name:
                baudrate = container.parameter_values.get('CanControllerBaudRate')
                if baudrate:
                    can_baudrates[container.short_name] = baudrate.value
        
        # Check CanIf controller configurations
        for container in canif_config.containers:
            if 'CtrlCfg' in container.short_name or 'Controller' in container.short_name:
                # Get referenced controller
                ctrl_ref = container.reference_values.get('CanIfCtrlDrvRef')
                if ctrl_ref:
                    ref_path = ctrl_ref.value_ref
                    # Extract controller name from path
                    ref_name = ref_path.split('/')[-1] if ref_path else None
                    
                    # Get CanIf baud rate
                    canif_baud = container.parameter_values.get('CanIfCtrlBaudRate')
                    
                    if ref_name and canif_baud and ref_name in can_baudrates:
                        can_baud = can_baudrates[ref_name]
                        if canif_baud.value != can_baud:
                            result.add_message(self._create_error(
                                f"CanIf controller '{container.short_name}' baud rate ({canif_baud.value}) "
                                f"does not match referenced CanController '{ref_name}' ({can_baud})",
                                container.get_path()
                            ))
        
        return result


class ComMChannelConsistencyRule(ValidationRule):
    """
    Validates that ComM channels are consistent with underlying
    CanSM network configurations.
    
    Cross-module dependency:
    - ComM.ComMChannel should have corresponding CanSM.CanSMNetwork
    """
    
    def __init__(self):
        super().__init__(
            name="ComMChannelConsistency",
            description="ComM channels must have matching CanSM network configurations"
        )
    
    def validate(self, module_def, configuration, project_context=None):
        result = ValidationResult()
        
        if not project_context:
            return result
        
        comm_mgr = project_context.module_managers.get('ComM')
        cansm_mgr = project_context.module_managers.get('CanSM')
        
        if not comm_mgr or not cansm_mgr:
            return result
        
        comm_config = comm_mgr.configuration
        cansm_config = cansm_mgr.configuration
        
        if not comm_config or not cansm_config:
            return result
        
        # Get CanSM network names
        cansm_networks = set()
        for container in cansm_config.containers:
            if 'Network' in container.short_name:
                cansm_networks.add(container.short_name)
        
        # Check ComM channels
        for container in comm_config.containers:
            if 'Channel' in container.short_name:
                # Get bus type
                bus_type = container.parameter_values.get('ComMBusType')
                if bus_type and bus_type.value == 'COMM_BUS_TYPE_CAN':
                    # Should have corresponding CanSM network
                    network_ref = container.reference_values.get('ComMNetworkRef')
                    if network_ref:
                        ref_name = network_ref.value_ref.split('/')[-1]
                        if ref_name not in cansm_networks:
                            result.add_message(self._create_warning(
                                f"ComM channel '{container.short_name}' references CanSM network "
                                f"'{ref_name}' which does not exist in CanSM configuration",
                                container.get_path()
                            ))
        
        return result


class McuClockReferenceRule(ValidationRule):
    """
    Validates that modules referencing MCU clock sources use valid clock IDs.
    
    Cross-module dependency:
    - Can.CanController.CanClockRef -> Mcu.McuClockSettingConfig
    - Gpt.GptChannelConfiguration.GptClockRef -> Mcu.McuClockSettingConfig
    """
    
    def __init__(self):
        super().__init__(
            name="McuClockReference",
            description="Clock references must point to valid MCU clock configurations"
        )
    
    def validate(self, module_def, configuration, project_context=None):
        result = ValidationResult()
        
        if not project_context:
            return result
        
        mcu_mgr = project_context.module_managers.get('Mcu')
        if not mcu_mgr or not mcu_mgr.configuration:
            return result
        
        # Build set of valid clock source paths
        valid_clocks = set()
        for container in mcu_mgr.configuration.containers:
            if 'Clock' in container.short_name:
                valid_clocks.add(container.get_path())
                # Also add sub-containers
                for sub in container.sub_containers:
                    valid_clocks.add(sub.get_path())
        
        # Check all modules for clock references
        for mod_name, mgr in project_context.module_managers.items():
            if mod_name == 'Mcu' or not mgr.configuration:
                continue
            
            self._check_clock_refs(mgr.configuration.containers, valid_clocks, result)
        
        return result
    
    def _check_clock_refs(self, containers, valid_clocks, result):
        """Recursively check containers for clock references"""
        for container in containers:
            for ref_name, ref_val in container.reference_values.items():
                if 'Clock' in ref_name and ref_val.value_ref:
                    if ref_val.value_ref not in valid_clocks:
                        result.add_message(self._create_error(
                            f"Invalid clock reference: '{ref_val.value_ref}' not found in MCU clock configuration",
                            container.get_path()
                        ))
            
            # Recurse into sub-containers
            self._check_clock_refs(container.sub_containers, valid_clocks, result)


class UniqueSymbolicNameRule(ValidationRule):
    """
    Validates that symbolic names are unique across the project.
    
    This is a project-wide rule that checks if any two containers
    share the same symbolic name when they shouldn't.
    """
    
    def __init__(self):
        super().__init__(
            name="UniqueSymbolicName",
            description="Symbolic names must be unique across the project"
        )
    
    def validate(self, module_def, configuration, project_context=None):
        result = ValidationResult()
        
        if not project_context:
            return result
        
        # Collect all symbolic names and their locations
        symbolic_names = {}  # name -> [(module, path), ...]
        
        for mod_name, mgr in project_context.module_managers.items():
            if not mgr.configuration:
                continue
            
            self._collect_symbolic_names(
                mgr.configuration.containers,
                mod_name,
                symbolic_names
            )
        
        # Report duplicates
        for name, locations in symbolic_names.items():
            if len(locations) > 1:
                loc_str = ", ".join([f"{m}:{p}" for m, p in locations])
                result.add_message(self._create_warning(
                    f"Symbolic name '{name}' is used in multiple locations: {loc_str}",
                    locations[0][1]  # Use first location as context
                ))
        
        return result
    
    def _collect_symbolic_names(self, containers, module_name, names_dict):
        """Recursively collect symbolic names from containers"""
        for container in containers:
            # Check for SymbolicNameValue parameter
            sym_param = container.parameter_values.get('SymbolicNameValue')
            if sym_param and sym_param.value:
                name = str(sym_param.value)
                if name not in names_dict:
                    names_dict[name] = []
                names_dict[name].append((module_name, container.get_path()))
            
            # Recurse
            self._collect_symbolic_names(container.sub_containers, module_name, names_dict)
