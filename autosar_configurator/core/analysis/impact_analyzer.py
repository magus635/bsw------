"""
Impact Analyzer for Configuration Changes

Analyzes the propagation of changes in the configuration based on:
1. Structural references (Ref parameters)
2. Logical dependencies (AI-inferred or Rule-based)
"""
from typing import Dict, List, Set, Optional, Tuple
from dataclasses import dataclass
import collections

@dataclass
class ImpactPath:
    """Represents a path of impact propagation"""
    source: str
    target: str
    path: List[str]
    reason: str
    dependency_type: str  # 'structural', 'logical'

class ImpactAnalyzer:
    def __init__(self):
        # Adjacency list: node -> list of (target, type, reason)
        self.graph: Dict[str, List[Tuple[str, str, str]]] = collections.defaultdict(list)
        
    def clear(self):
        self.graph.clear()
        
    def add_dependency(self, source: str, target: str, dep_type: str, reason: str):
        """Add a directed dependency: source affects target"""
        self.graph[source].append((target, dep_type, reason))
        
    def build_from_configuration(self, configuration, module_name: str):
        """Build graph from structural references in configuration"""
        # Traverse containers
        for container in configuration.containers:
            self._process_container(container, module_name, "")
            
    def _process_container(self, container, module_name: str, parent_path: str):
        container_path = f"{parent_path}/{container.short_name}" if parent_path else container.short_name
        full_container_path = f"{module_name}.{container_path}" # Logical path format
        
        # 1. References: Source (RefParam) -> Target (Container)
        # If RefParam changes, it points to a different Target.
        # But impact analysis usually means: "If Target changes, does Source logic break?"
        # OR "If Source (Ref) changes, does it affect validation?"
        # Usually: "Dependent depends on Dependency".
        # Ref Value = "Dependency". The Container holding Ref is "Dependent".
        # So Edge: Target -> Source.
        # Example: CanIf refers to CanController. If CanController Clock changes, CanIf might break.
        # So: CanController (Target) -> CanIf (Source).
        
        for ref_name, ref_value in container.reference_values.items():
            target_path = ref_value.value_ref
            if target_path:
                # Convert target path to logical format (approximate)
                # /Config/Mcu/McuConfig/Clock -> Mcu.McuConfig/Clock
                # This needs normalization logic.
                norm_target = self._normalize_path(target_path)
                norm_source = f"{full_container_path}.{ref_name}"
                
                # Dependency: Target affects Source
                self.add_dependency(norm_target, norm_source, 'structural', f"Reference: {ref_name}")

        # Recurse
        for sub in container.sub_containers:
            self._process_container(sub, module_name, container_path)

    def load_dependencies(self, dependencies: List[Dict]):
        """Load logical dependencies (e.g. from AI analysis)"""
        # Format: {source_param, target_param, reason, ...}
        # AI/Rule format: Source Condition -> Target Requirement.
        # This usually implies: Source implies constraint on Target.
        # If Source changes, Target might need to change to satisfy constraint.
        # So Source affects Target.
        # Edge: Source -> Target.
        
        for dep in dependencies:
            source = dep.get('source_param')
            target = dep.get('target_param')
            reason = dep.get('reason', 'Logical dependency')
            
            if source and target:
                self.add_dependency(source, target, 'logical', reason)

    def analyze_impact(self, node_path: str) -> List[ImpactPath]:
        """Find all nodes affected by a change in node_path (BFS)"""
        impacts = []
        visited = set()
        queue = collections.deque([(node_path, [])]) # (current_node, path_history)
        
        while queue:
            current, history = queue.popleft()
            
            if current in visited:
                continue
            visited.add(current)
            
            # Record impact (exclude self)
            if current != node_path:
                # Find the edge that led here for reason
                # Simplified: just full history
                pass

            # Explore neighbors
            if current in self.graph:
                for target, dtype, reason in self.graph[current]:
                    new_history = history + [current]
                    
                    # Create impact record
                    impacts.append(ImpactPath(
                        source=node_path,
                        target=target,
                        path=new_history + [target],
                        reason=reason,
                        dependency_type=dtype
                    ))
                    
                    queue.append((target, new_history))
                    
        return impacts

    def _normalize_path(self, arxml_path: str) -> str:
        """Convert ARXML path to logical path (Module.Container/Param)"""
        # /Config/Mcu/Container -> Mcu.Container
        parts = [p for p in arxml_path.split('/') if p and p != 'Config']
        if len(parts) >= 2:
            return f"{parts[0]}.{'/'.join(parts[1:])}"
        return arxml_path
