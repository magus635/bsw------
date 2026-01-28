"""
Configuration Model - ECUC Configuration (VALUE) layer
Represents user-created instances and their configured values
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Any, Set
from datetime import datetime

from .definition_model import VariantType


@dataclass
class EcucParameterValue:
    """ECUC Parameter Value (ECUC-TEXTUAL-PARAM-VALUE / ECUC-NUMERICAL-PARAM-VALUE)
    
    Stores the actual configured value for a parameter
    """
    definition_ref: str  # Path to EcucParameterDef, e.g., "/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcPrescale"
    value: Any  # Actual value: "SARADC0", 14, True, etc.
    
    # Metadata
    is_modified: bool = False
    last_modified: Optional[datetime] = None
    
    def mark_modified(self):
        """Mark this value as modified"""
        self.is_modified = True
        self.last_modified = datetime.now()


class ResolutionSeverity:
    """Severity levels for resolution errors"""
    INFO = "info"        # 等待加载
    WARNING = "warning"  # 可运行但需注意
    ERROR = "error"      # 必须修复


class ResolutionError:
    """Engineering-grade resolution error with explainable information for UI and AI
    
    工程级设计目标：失败也要"可诊断、可定位、可解释、可恢复"
    
    Provides structured error information that can be:
    1. Displayed in UI (warnings, tooltips, validation reports)
    2. Used by AI to explain problems and suggest fixes
    3. Used for impact analysis
    """
    
    # ===== Error Types (10 engineering-grade categories) =====
    
    # Basic resolution errors
    PATH_NOT_FOUND = "path_not_found"           # 路径不存在
    MODULE_NOT_LOADED = "module_not_loaded"     # 模块未加载
    INVALID_PATH = "invalid_path"               # 路径格式错误
    
    # Type/semantic errors
    TYPE_MISMATCH = "type_mismatch"             # 目标类型不匹配
    AMBIGUOUS_REFERENCE = "ambiguous_reference" # 多候选歧义
    DEF_VALUE_MISMATCH = "def_value_mismatch"   # 定义/值层级混淆
    
    # Lifecycle errors
    UNRESOLVED = "unresolved"                   # 尚未解析
    STALE_REFERENCE = "stale_reference"         # 陈旧引用（目标已删除）
    
    # Structural warnings
    CIRCULAR_REFERENCE = "circular_reference"   # 循环引用
    DEEP_CHAIN = "deep_chain"                   # 过深引用链
    
    # Optional reference
    OPTIONAL_NOT_SET = "optional_not_set"       # 可选引用未配置
    
    def __init__(
        self, 
        error_type: str, 
        path: str,
        message: str = None,
        suggestion: str = None,
        severity: str = None,
        # AI-ready fields
        expected_type: str = None,
        actual_type: str = None,
        candidates: list = None,
        impact_scope: list = None,
        recoverable: bool = True
    ):
        self.error_type = error_type
        self.path = path
        self.severity = severity or self._default_severity(error_type)
        self.message = message or self._default_message(error_type, path)
        self.suggestion = suggestion or self._default_suggestion(error_type)
        
        # AI-ready fields
        self.expected_type = expected_type
        self.actual_type = actual_type
        self.candidates = candidates or []
        self.impact_scope = impact_scope or []
        self.recoverable = recoverable
    
    def _default_severity(self, error_type: str) -> str:
        severity_map = {
            self.UNRESOLVED: ResolutionSeverity.INFO,
            self.OPTIONAL_NOT_SET: ResolutionSeverity.INFO,
            self.CIRCULAR_REFERENCE: ResolutionSeverity.WARNING,
            self.DEEP_CHAIN: ResolutionSeverity.WARNING,
            # All others are ERROR
        }
        return severity_map.get(error_type, ResolutionSeverity.ERROR)
    
    def _default_message(self, error_type: str, path: str) -> str:
        module_hint = path.split('/')[2] if path and '/' in path and len(path.split('/')) > 2 else "Unknown"
        
        messages = {
            self.PATH_NOT_FOUND: f"目标容器不存在: {path}",
            self.MODULE_NOT_LOADED: f"模块 '{module_hint}' 尚未加载到当前工程",
            self.INVALID_PATH: f"无效的引用路径格式: {path}",
            self.TYPE_MISMATCH: f"目标类型不匹配: {path}",
            self.AMBIGUOUS_REFERENCE: f"引用存在多个候选目标: {path}",
            self.DEF_VALUE_MISMATCH: f"引用错误地指向了定义而非实例: {path}",
            self.UNRESOLVED: f"该引用尚未解析: {path}",
            self.STALE_REFERENCE: f"目标对象已被删除/替换: {path}",
            self.CIRCULAR_REFERENCE: f"检测到循环引用: {path}",
            self.DEEP_CHAIN: f"引用链过深: {path}",
            self.OPTIONAL_NOT_SET: f"可选引用未配置: {path}",
        }
        return messages.get(error_type, f"解析错误: {path}")
    
    def _default_suggestion(self, error_type: str) -> str:
        suggestions = {
            self.PATH_NOT_FOUND: "检查目标容器是否存在或创建它",
            self.MODULE_NOT_LOADED: "将引用的模块添加到项目中",
            self.INVALID_PATH: "检查引用路径格式，使用完整路径",
            self.TYPE_MISMATCH: "确保引用指向正确类型的容器",
            self.AMBIGUOUS_REFERENCE: "使用完整路径消除歧义",
            self.DEF_VALUE_MISMATCH: "引用应指向 EcucContainerValue 而非 EcucContainerDef",
            self.UNRESOLVED: "请先完成配置加载",
            self.STALE_REFERENCE: "重新创建目标容器或更新此引用",
            self.CIRCULAR_REFERENCE: "检查配置逻辑，避免循环依赖",
            self.DEEP_CHAIN: "考虑简化配置结构",
            self.OPTIONAL_NOT_SET: "系统将采用默认行为，如需覆盖请配置此引用",
        }
        return suggestions.get(error_type, "检查引用配置")
    
    def to_dict(self) -> dict:
        """Convert to dict for AI/API consumption
        
        Provides all information AI needs to explain and diagnose the error.
        """
        result = {
            "reference_path": self.path,
            "state": "Error" if self.severity == ResolutionSeverity.ERROR else self.severity.capitalize(),
            "error_type": self.error_type,
            "severity": self.severity,
            "message": self.message,
            "suggestion": self.suggestion,
            "recoverable": self.recoverable,
        }
        
        # Add optional AI-ready fields if present
        if self.expected_type:
            result["expected_type"] = self.expected_type
        if self.actual_type:
            result["actual_type"] = self.actual_type
        if self.candidates:
            result["available_candidates"] = self.candidates
        if self.impact_scope:
            result["impact_scope"] = self.impact_scope
        
        return result
    
    def to_user_message(self) -> str:
        """Format for user display"""
        icon = {"error": "❌", "warning": "⚠️", "info": "ℹ️"}.get(self.severity, "❓")
        return f"{icon} {self.message}\n   💡 {self.suggestion}"
    
    def __str__(self) -> str:
        return f"[{self.severity.upper()}] {self.message}"


@dataclass
class EcucReferenceValue:
    """ECUC Reference Value (ECUC-REFERENCE-VALUE)
    
    Stores a reference to another container instance.
    
    EMF-Style Object Navigation:
    - `value_ref`: Original string path (for serialization)
    - `target`: Resolved EcucContainerValue object (for object navigation)
    - `resolution_error`: Structured error if resolution failed
    
    After resolution, you can navigate directly:
        ref.target.parameter_values['SomeParam'].value
    Instead of:
        lookup_by_path(ref.value_ref).parameter_values[...]
    """
    definition_ref: str  # Path to EcucReferenceDef
    value_ref: str  # Path to target container instance
    
    # EMF-style resolved target object (populated after resolve_references() is called)
    target: Optional['EcucContainerValue'] = None
    
    # Resolution error (if resolution failed)
    resolution_error: Optional[ResolutionError] = field(default=None, repr=False)
    
    # Metadata
    is_modified: bool = False
    
    @property
    def is_resolved(self) -> bool:
        """Check if this reference has been resolved to an object"""
        return self.target is not None
    
    @property
    def has_error(self) -> bool:
        """Check if resolution failed with an error"""
        return self.resolution_error is not None


@dataclass
class EcucContainerValue:
    """ECUC Container Value (ECUC-CONTAINER-VALUE)
    
    Represents a user-created instance of a container definition
    """
    short_name: str  # User-defined instance name, e.g., "AdcHwUnit_0", "AdcConfigSet"
    definition_ref: str  # Path to EcucContainerDef, e.g., "/AUTOSAR/EcucDefs/Adc/AdcHwUnit"
    
    # Configured parameter values
    parameter_values: Dict[str, EcucParameterValue] = field(default_factory=dict)
    
    # Configured reference values
    reference_values: Dict[str, EcucReferenceValue] = field(default_factory=dict)
    
    # Sub-container instances
    sub_containers: List['EcucContainerValue'] = field(default_factory=list)
    
    # Parent container (for path generation)
    parent: Optional['EcucContainerValue'] = field(default=None, repr=False)
    
    # Reverse references: who references this container?
    # Populated by WorkspaceProject.build_reverse_reference_index()
    referenced_by: List['EcucReferenceValue'] = field(default_factory=list, repr=False)
    
    # Module association (for path uniqueness and registration)
    module_name: str = ""
    module_config: Optional['EcucModuleConfiguration'] = field(default=None, repr=False)
    
    # Metadata
    index: int = 0  # Instance index (for sorting)
    is_modified: bool = False
    last_modified: Optional[datetime] = None
    
    # Validation state
    validation_errors: List[str] = field(default_factory=list)
    
    # Variant Selection: which variant this instance belongs to (None = All)
    variant: Optional[str] = None
    
    def get_path(self) -> str:

        """Get full path of this container instance"""
        if self.parent:
            return f"{self.parent.get_path()}/{self.short_name}"
        
        # Use module name if available to avoid cross-module clashing
        root = f"/{self.module_name}" if self.module_name else "/Config"
        return f"{root}/{self.short_name}"
    
    def set_parameter_value(self, param_name: str, value: Any, definition_ref: str):
        """Set or update a parameter value"""
        if param_name in self.parameter_values:
            param_value = self.parameter_values[param_name]
            param_value.value = value
            param_value.mark_modified()
        else:
            self.parameter_values[param_name] = EcucParameterValue(
                definition_ref=definition_ref,
                value=value,
                is_modified=True,
                last_modified=datetime.now()
            )
        self.mark_modified()

    def remove_parameter_value(self, param_name: str) -> bool:
        """Remove a parameter value (revert to unconfigured state)

        Used to clear optional parameters back to their default/unconfigured state.
        The parameter will not be saved to ARXML after removal.

        Args:
            param_name: Name of the parameter to remove

        Returns:
            True if parameter was removed, False if it didn't exist
        """
        if param_name in self.parameter_values:
            del self.parameter_values[param_name]
            self.mark_modified()
            return True
        return False

    def has_parameter_value(self, param_name: str) -> bool:
        """Check if a parameter has been explicitly configured

        Args:
            param_name: Name of the parameter to check

        Returns:
            True if parameter has a configured value, False if using default
        """
        return param_name in self.parameter_values

    def set_reference_value(self, ref_name: str, value_ref: str, definition_ref: str):
        """Set or update a reference value"""
        self.reference_values[ref_name] = EcucReferenceValue(
            definition_ref=definition_ref,
            value_ref=value_ref,
            is_modified=True
        )
        self.mark_modified()
    
    def add_sub_container(self, sub_container: 'EcucContainerValue'):
        """Add a sub-container instance"""
        sub_container.parent = self
        sub_container.module_name = self.module_name
        sub_container.module_config = self.module_config
        
        self.sub_containers.append(sub_container)
        
        # Register in module if possible
        if self.module_config:
            self.module_config._register_instance(sub_container)
            
        self.mark_modified()
    
    def remove_sub_container(self, sub_container: 'EcucContainerValue'):
        """Remove a sub-container instance"""
        self.sub_containers.remove(sub_container)
        self.mark_modified()
    
    def mark_modified(self):
        """Mark this container as modified"""
        self.is_modified = True
        self.last_modified = datetime.now()
    
    def has_validation_errors(self) -> bool:
        """Check if this container has validation errors"""
        return len(self.validation_errors) > 0

    def clone(self) -> 'EcucContainerValue':
        """Deep copy of the container instance"""
        new_instance = EcucContainerValue(
            short_name=self.short_name,
            definition_ref=self.definition_ref,
            variant=self.variant,
            is_modified=True,
            last_modified=datetime.now()
        )

        
        # Clone parameters
        for name, param in self.parameter_values.items():
            new_instance.parameter_values[name] = EcucParameterValue(
                definition_ref=param.definition_ref,
                value=param.value[:] if isinstance(param.value, list) else param.value, # Handle list cloning
                is_modified=True,
                last_modified=datetime.now()
            )
            
        # Clone references
        for name, ref in self.reference_values.items():
            new_instance.reference_values[name] = EcucReferenceValue(
                definition_ref=ref.definition_ref,
                value_ref=ref.value_ref,
                is_modified=True
            )
            
        # Clone sub-containers
        for sub in self.sub_containers:
            new_sub = sub.clone()
            new_instance.add_sub_container(new_sub)
            
        return new_instance


@dataclass
class EcucModuleConfiguration:
    """ECUC Module Configuration Values (ECUC-MODULE-CONFIGURATION-VALUES)
    
    Top-level configuration for a BSW module, containing all user-created instances
    """
    short_name: str  # e.g., "Adc"
    definition_ref: str  # Path to EcucModuleDef, e.g., "/AUTOSAR/EcucDefs/Adc"
    
    # Top-level container instances
    containers: List[EcucContainerValue] = field(default_factory=list)
    
    # Metadata
    implementation_config_variant: str = "VariantPostBuild"
    is_modified: bool = False
    last_saved: Optional[datetime] = None
    
    # All created instance paths (for quick lookup)
    _instance_registry: Dict[str, EcucContainerValue] = field(default_factory=dict)
    
    # Variant Management: stores parameter overrides per variant
    # Structure: {"VariantName": {"Container.ParamName": value, ...}}
    variant_overrides: Dict[str, Dict[str, Any]] = field(default_factory=dict)
    
    def get_value_for_variant(self, param_path: str, variant: Optional[str]) -> tuple:
        """Get parameter value considering variant override
        
        Args:
            param_path: Full parameter path (e.g., "AdcConfigSet.AdcPrescale")
            variant: Variant name, or None for base configuration
            
        Returns:
            Tuple of (value, is_override) where is_override indicates if value
            comes from variant override layer
        """
        if variant and variant in self.variant_overrides:
            overrides = self.variant_overrides[variant]
            if param_path in overrides:
                return (overrides[param_path], True)
        
        # Fall back to base value - search in containers
        return (None, False)  # Caller should use container's value
    
    def set_value_for_variant(self, param_path: str, value: Any, variant: Optional[str]):
        """Set parameter value for a specific variant
        
        Args:
            param_path: Full parameter path
            value: New value to set
            variant: Variant name (None means modify base configuration directly)
        """
        if variant:
            if variant not in self.variant_overrides:
                self.variant_overrides[variant] = {}
            self.variant_overrides[variant][param_path] = value
            self.is_modified = True
        # If variant is None, caller should modify container directly
    
    def clear_variant_override(self, param_path: str, variant: str):
        """Remove a variant-specific override (revert to base value)"""
        if variant in self.variant_overrides:
            if param_path in self.variant_overrides[variant]:
                del self.variant_overrides[variant][param_path]
                self.is_modified = True
    
    def get_variant_overrides_count(self, variant: str) -> int:
        """Get number of parameter overrides for a variant"""
        if variant in self.variant_overrides:
            return len(self.variant_overrides[variant])
        return 0

    
    def add_container(self, container: EcucContainerValue):
        """Add a top-level container instance"""
        container.module_name = self.short_name
        container.module_config = self
        
        # Recursively propagate module info to all sub-containers
        # (important for containers loaded from ARXML where sub-containers
        # were added before the top-level container was added to config)
        def propagate_module_info(c: EcucContainerValue):
            c.module_name = self.short_name
            c.module_config = self
            for sub in c.sub_containers:
                propagate_module_info(sub)
        
        propagate_module_info(container)
        
        self.containers.append(container)
        self._register_instance(container)
        self.is_modified = True
    
    def remove_container(self, container: EcucContainerValue):
        """Remove a container instance"""
        self.containers.remove(container)
        self._unregister_instance(container)
        self.is_modified = True
    
    def _register_instance(self, container: EcucContainerValue):
        """Register a container instance and all its sub-containers"""
        path = container.get_path()
        self._instance_registry[path] = container
        
        # Recursively register sub-containers
        for sub_container in container.sub_containers:
            self._register_instance(sub_container)
    
    def _unregister_instance(self, container: EcucContainerValue):
        """Unregister a container instance and all its sub-containers"""
        path = container.get_path()
        if path in self._instance_registry:
            del self._instance_registry[path]
        
        # Recursively unregister sub-containers
        for sub_container in container.sub_containers:
            self._unregister_instance(sub_container)
    
    def get_instance_by_path(self, path: str) -> Optional[EcucContainerValue]:
        """Get a container instance by its full path"""
        return self._instance_registry.get(path)
    
    def get_all_instances_of_def(self, definition_ref: str) -> List[EcucContainerValue]:
        """Get all instances of a specific container definition"""
        instances = []
        for container in self.containers:
            instances.extend(self._find_instances_by_def(container, definition_ref))
        return instances
    
    def _find_instances_by_def(self, container: EcucContainerValue, definition_ref: str) -> List[EcucContainerValue]:
        """Recursively find all instances matching a definition"""
        instances = []
        if container.definition_ref == definition_ref:
            instances.append(container)
        
        for sub_container in container.sub_containers:
            instances.extend(self._find_instances_by_def(sub_container, definition_ref))
        
        return instances
    
    def mark_saved(self):
        """Mark configuration as saved"""
        self.is_modified = False
        self.last_saved = datetime.now()
    
    def resolve_references(self, resolver: callable) -> tuple:
        """Resolve all references in this configuration to object pointers
        
        EMF-style reference resolution: converts string paths to object references.
        Also tracks resolution errors for UI/AI display.
        
        Args:
            resolver: A callable that takes a path string and returns the
                      EcucContainerValue object, or None if not found.
                      Signature: (path: str) -> Optional[EcucContainerValue]
        
        Returns:
            Tuple of (resolved_count, error_count)
        """
        resolved_count = 0
        error_count = 0
        
        def resolve_container(container: EcucContainerValue):
            nonlocal resolved_count, error_count
            
            for ref_name, ref_value in container.reference_values.items():
                if ref_value.value_ref and not ref_value.is_resolved:
                    target = resolver(ref_value.value_ref)
                    if target is not None:
                        ref_value.target = target
                        ref_value.resolution_error = None  # Clear any previous error
                        resolved_count += 1
                    else:
                        # Create explainable error with proper categorization
                        path = ref_value.value_ref
                        if not path or not path.startswith('/'):
                            error = ResolutionError(
                                ResolutionError.INVALID_PATH,
                                path
                            )
                        else:
                            # Extract module hint for better error messages
                            parts = path.split('/')
                            module_hint = parts[2] if len(parts) > 2 else ""
                            
                            # Determine if it's a module-not-loaded vs path-not-found
                            # For now, assume PATH_NOT_FOUND (workspace can upgrade to MODULE_NOT_LOADED)
                            error = ResolutionError(
                                ResolutionError.PATH_NOT_FOUND,
                                path,
                                suggestion=f"检查 '{module_hint}' 模块是否已加载，或目标容器是否存在"
                            )
                        ref_value.resolution_error = error
                        error_count += 1
            
            for sub in container.sub_containers:
                resolve_container(sub)
        
        for container in self.containers:
            resolve_container(container)
        
        return resolved_count, error_count
    
    def get_resolution_errors(self) -> List[ResolutionError]:
        """Get all resolution errors in this configuration
        
        Returns:
            List of ResolutionError objects for UI/AI display
        """
        errors = []
        
        def collect_errors(container: EcucContainerValue):
            for ref_name, ref_value in container.reference_values.items():
                if ref_value.has_error:
                    errors.append(ref_value.resolution_error)
            for sub in container.sub_containers:
                collect_errors(sub)
        
        for container in self.containers:
            collect_errors(container)
        
        return errors
