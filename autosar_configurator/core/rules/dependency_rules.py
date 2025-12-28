"""
Dependency Validation Rules - Dependency and circular dependency detection

These rules detect circular dependencies in reference chains and
validate parameter/container dependencies.
"""
from typing import Set, Dict, List, Optional

from ..validation_engine import ValidationRule, ValidationResult
from ..model.definition_model import EcucModuleDef
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


class CircularDependencyRule(ValidationRule):
    """Detect circular dependencies in reference chains
    
    Uses graph traversal (DFS) to detect cycles in container reference relationships.
    """
    
    def __init__(self):
        super().__init__(
            name="CircularDependency",
            description="Detects circular dependencies in container reference relationships"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        # Build reference graph
        ref_graph = self._build_reference_graph(configuration)
        
        # Detect cycles using DFS
        visited = set()
        rec_stack = set()
        
        for node in ref_graph.keys():
            if node not in visited:
                cycle = self._detect_cycle_dfs(node, ref_graph, visited, rec_stack, [])
                if cycle:
                    result.add_message(self._create_error(
                        f"Circular dependency detected: {' → '.join(cycle)} → {cycle[0]}",
                        details="Reference cycle creates circular dependency",
                        suggested_fix="Break the cycle by removing one of the references"
                    ))
        
        return result
    
    def _build_reference_graph(self, configuration: EcucModuleConfiguration) -> Dict[str, List[str]]:
        """Build a directed graph of container references
        
        Returns:
            Dict mapping container path to list of referenced container paths
        """
        graph = {}
        
        def add_to_graph(container: EcucContainerValue):
            path = container.get_path()
            graph[path] = []
            
            for ref_value in container.reference_values.values():
                if ref_value.value_ref:
                    graph[path].append(ref_value.value_ref)
            
            for sub_container in container.sub_containers:
                add_to_graph(sub_container)
        
        for container in configuration.containers:
            add_to_graph(container)
        
        return graph
    
    def _detect_cycle_dfs(self, node: str, graph: Dict[str, List[str]],
                         visited: Set[str], rec_stack: Set[str],
                         path: List[str]) -> Optional[List[str]]:
        """Detect cycle using depth-first search
        
        Args:
            node: Current node
            graph: Reference graph
            visited: Set of visited nodes
            rec_stack: Recursion stack for cycle detection
            path: Current path being explored
            
        Returns:
            Cycle path if found, None otherwise
        """
        visited.add(node)
        rec_stack.add(node)
        path.append(node)
        
        if node in graph:
            for neighbor in graph[node]:
                if neighbor not in visited:
                    cycle = self._detect_cycle_dfs(neighbor, graph, visited, rec_stack, path[:])
                    if cycle:
                        return cycle
                elif neighbor in rec_stack:
                    # Found a cycle
                    cycle_start = path.index(neighbor)
                    return path[cycle_start:]
        
        rec_stack.remove(node)
        return None


class DependencyRule(ValidationRule):
    """Validate parameter and container dependencies
    
    This rule can be extended to support complex dependency rules like:
    - If parameter A has value X, then parameter B must be set
    - If container A exists, then container B must also exist
    """
    
    def __init__(self):
        super().__init__(
            name="Dependency",
            description="Validates parameter and container dependency rules"
        )
        # Dependency rules can be registered here
        self.param_dependencies: List[Dict] = []
        self.container_dependencies: List[Dict] = []
    
    def add_parameter_dependency(self, source_param: str, source_value: any,
                                target_param: str, container_def_ref: str):
        """Register a parameter dependency rule
        
        Args:
            source_param: Source parameter name
            source_value: Value that triggers the dependency
            target_param: Target parameter that must be set
            container_def_ref: Container definition reference
        """
        self.param_dependencies.append({
            'source_param': source_param,
            'source_value': source_value,
            'target_param': target_param,
            'container_def': container_def_ref
        })
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        # Validate parameter dependencies
        for container in configuration.containers:
            self._validate_container_dependencies(container, result)
        
        return result
    
    def _validate_container_dependencies(self, container: EcucContainerValue, result: ValidationResult):
        """Validate dependencies in a container"""
        # Check parameter dependencies
        for dep in self.param_dependencies:
            if container.definition_ref == dep['container_def']:
                source_param = dep['source_param']
                if source_param in container.parameter_values:
                    param_value = container.parameter_values[source_param].value
                    if param_value == dep['source_value']:
                        # Dependency triggered, check target
                        target_param = dep['target_param']
                        if target_param not in container.parameter_values:
                            result.add_message(self._create_error(
                                f"Parameter dependency violated: When '{source_param}'={dep['source_value']}, "
                                f"parameter '{target_param}' must be set",
                                container_path=container.get_path(),
                                suggested_fix=f"Set parameter '{target_param}'"
                            ))
        
        # Recursively check sub-containers
        for sub_container in container.sub_containers:
            self._validate_container_dependencies(sub_container, result)
