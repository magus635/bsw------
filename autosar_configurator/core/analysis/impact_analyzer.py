"""
Impact Analyzer for Configuration Changes

Analyzes the propagation of changes in the configuration based on:
1. Structural references (Ref parameters)
2. Logical dependencies (AI-inferred or Rule-based)
"""
from typing import Dict, List, Set, Optional, Tuple
from dataclasses import dataclass
import collections
import logging

logger = logging.getLogger(__name__)

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
        # All nodes in graph for fuzzy matching
        self.all_nodes: Set[str] = set()
        
    def clear(self):
        self.graph.clear()
        self.all_nodes.clear()
        
    def add_dependency(self, source: str, target: str, dep_type: str, reason: str):
        """Add a directed dependency: source affects target"""
        # Normalize paths to use consistent format (dots only)
        source_norm = self._to_dot_path(source)
        target_norm = self._to_dot_path(target)
        
        self.graph[source_norm].append((target_norm, dep_type, reason))
        self.all_nodes.add(source_norm)
        self.all_nodes.add(target_norm)
        
    def _to_dot_path(self, path: str) -> str:
        """Convert any path format to dot-separated format for consistency"""
        # Replace slashes with dots
        result = path.replace('/', '.')
        # Remove leading dots
        while result.startswith('.'):
            result = result[1:]
        # Collapse multiple dots
        while '..' in result:
            result = result.replace('..', '.')
        return result
        
    def build_from_configuration(self, configuration, module_name: str):
        """Build graph from structural references in configuration"""
        # Log first few container names for debugging
        if configuration.containers:
            container_names = [c.short_name for c in configuration.containers[:3]]
            logger.debug(f"Building graph for {module_name}, top containers: {container_names}")
        
        # Traverse containers
        for container in configuration.containers:
            self._process_container(container, module_name, "")
            
        logger.debug(f"Built dependency graph for {module_name}: {len(self.all_nodes)} nodes, {sum(len(v) for v in self.graph.values())} edges")
            
    def _process_container(self, container, module_name: str, parent_path: str, parent_enable_params: List[tuple] = None):
        """Process a container and its sub-containers to build the dependency graph
        
        Args:
            container: The container to process
            module_name: Module name (e.g., 'Can')
            parent_path: Path of parent container
            parent_enable_params: List of (full_path, base_name) tuples for enable params from parent
        """
        # Use dot-separated path format consistently
        container_path = f"{parent_path}.{container.short_name}" if parent_path else container.short_name
        full_container_path = f"{module_name}.{container_path}"
        
        if parent_enable_params is None:
            parent_enable_params = []
        
        # Add container as a node
        self.all_nodes.add(full_container_path)
        
        # Add parameters as nodes - collect from BOTH config values AND definition
        # This ensures we capture all parameters including newly added container instances
        param_names = set(container.parameter_values.keys())
        
        # Also add parameters from definition if available
        if hasattr(container, 'definition') and container.definition:
            for param_def in container.definition.parameters:
                param_names.add(param_def.short_name)
        
        param_names = list(param_names)
        for param_name in param_names:
            param_path = f"{full_container_path}.{param_name}"
            self.all_nodes.add(param_path)
        
        # 2. Detect intra-container parameter relationships (common AUTOSAR patterns)
        current_enable_params = self._detect_enable_config_patterns(full_container_path, param_names)
        self._detect_related_params(full_container_path, param_names)
        
        # 3. Apply parent enable params to current container's parameters
        for enable_path, base_name in parent_enable_params:
            for param_name in param_names:
                if base_name in param_name or param_name.startswith(base_name):
                    param_path = f"{full_container_path}.{param_name}"
                    self.add_dependency(
                        enable_path, param_path, 'inferred',
                        f"Parent Enable: {enable_path.split('.')[-1]} controls {param_name}"
                    )
        
        # 1. References: If Target changes, Source (referencer) is affected
        # Edge: Target -> Source (reference)
        for ref_name, ref_value in container.reference_values.items():
            target_path = ref_value.value_ref
            if target_path:
                # Convert target path to logical format
                norm_target = self._normalize_path(target_path)
                norm_source = f"{full_container_path}.{ref_name}"
                
                # Dependency: Target affects Source reference
                self.add_dependency(norm_target, norm_source, 'structural', f"Reference: {ref_name}")
                
                # Also add reverse edge: If reference changes, validation may fail
                self.add_dependency(norm_source, norm_target, 'structural', f"Referenced by: {container.short_name}.{ref_name}")

        # Recurse with combined enable params (parent + current)
        combined_enable_params = parent_enable_params + current_enable_params
        for sub in container.sub_containers:
            self._process_container(sub, module_name, container_path, combined_enable_params)
    
    def _detect_enable_config_patterns(self, container_path: str, param_names: List[str]) -> List[tuple]:
        """Detect Enable/Config parameter patterns commonly seen in AUTOSAR

        Common patterns:
        - XxxEnable -> affects all Xxx* parameters
        - XxxSupport -> affects all Xxx* parameters

        Note: DevErrorDetect is NOT included here because it doesn't control
        other functional parameters. Cross-module DevErrorDetect consistency
        should be handled by AI-generated logical dependencies.

        Returns:
            List of (enable_path, base_name) tuples for propagation to sub-containers
        """
        enable_suffixes = ['Enable', 'Support', 'Supported', 'Active', 'Used']
        found_enable_params = []

        for param in param_names:
            is_enable_param = any(param.endswith(suffix) for suffix in enable_suffixes)

            if is_enable_param:
                # Find the base name (e.g., "CanFD" from "CanFDSupport")
                base_name = param
                for suffix in enable_suffixes:
                    if param.endswith(suffix):
                        base_name = param[:-len(suffix)]
                        break

                enable_path = f"{container_path}.{param}"

                # Record this enable param for sub-container propagation
                if base_name and len(base_name) >= 2:
                    found_enable_params.append((enable_path, base_name))

                # Find related parameters that share the base name in current container
                if base_name and len(base_name) >= 2:
                    for other_param in param_names:
                        if other_param != param and (
                            other_param.startswith(base_name) or
                            base_name in other_param
                        ):
                            other_path = f"{container_path}.{other_param}"
                            self.add_dependency(
                                enable_path, other_path, 'inferred',
                                f"Enable/Config pattern: {param} controls {other_param}"
                            )

        return found_enable_params
    
    def _detect_related_params(self, container_path: str, param_names: List[str]):
        """Detect related parameters based on naming conventions
        
        Patterns:
        - Parameters with same prefix (e.g., CanBaudRate, CanPropSeg, CanSeg1)
        - Min/Max pairs
        - Id/Count pairs
        """
        # Group by common prefix (at least 4 chars)
        prefix_groups: Dict[str, List[str]] = {}
        for param in param_names:
            # Extract prefix (first word in CamelCase)
            prefix = ""
            for i, char in enumerate(param):
                if i > 3 and char.isupper():
                    prefix = param[:i]
                    break
            else:
                if len(param) > 6:
                    prefix = param[:6]
            
            if prefix and len(prefix) >= 4:
                if prefix not in prefix_groups:
                    prefix_groups[prefix] = []
                prefix_groups[prefix].append(param)
        
        # Create bidirectional dependencies within groups
        for prefix, group in prefix_groups.items():
            if len(group) >= 2 and len(group) <= 8:  # Reasonable group size
                for i, param1 in enumerate(group):
                    for param2 in group[i+1:]:
                        path1 = f"{container_path}.{param1}"
                        path2 = f"{container_path}.{param2}"
                        self.add_dependency(
                            path1, path2, 'inferred',
                            f"Related parameters (prefix: {prefix})"
                        )
                        self.add_dependency(
                            path2, path1, 'inferred', 
                            f"Related parameters (prefix: {prefix})"
                        )

    def load_dependencies(self, dependencies: List[Dict]):
        """Load logical dependencies (e.g. from AI analysis)
        
        Rules use short paths like 'Adc.AdcAnalogClockSource' but graph nodes
        use full paths like 'Adc.AdcConfigSet_0.AdcHwUnit_0.AdcAnalogClockSource'.
        We need to expand rules to match actual graph nodes.
        """
        loaded_count = 0
        skipped_count = 0
        
        for dep in dependencies:
            source = dep.get('source_param')  # e.g., 'Adc.AdcAnalogClockSource'
            target = dep.get('target_param')  # e.g., 'Mcu.McuClockReferencePoint'
            reason = dep.get('reason', 'Logical dependency')
            
            if not source or not target:
                skipped_count += 1
                continue
            
            # Find matching source nodes in graph
            source_matches = self._find_nodes_by_rule(source)
            target_matches = self._find_nodes_by_rule(target)
            
            if source_matches and target_matches:
                # Create edges between all matching source-target pairs
                for src in source_matches:
                    for tgt in target_matches:
                        self.add_dependency(src, tgt, 'logical', reason)
                loaded_count += 1
            elif source_matches or target_matches:
                # Partial match - still add the rule with short paths
                # This allows the rule to be matched during analyze_impact
                self.add_dependency(source, target, 'logical', reason)
                loaded_count += 1
            else:
                # No match at all - add anyway for reference
                self.add_dependency(source, target, 'logical', reason)
                loaded_count += 1
        
        logger.info(f"Loaded {loaded_count} dependency rules, skipped {skipped_count}")
    
    def _find_nodes_by_rule(self, rule_path: str) -> List[str]:
        """Find graph nodes matching a rule path
        
        Rule path may be short (e.g., 'Adc.AdcAnalogClockSource') and needs
        to match full paths (e.g., 'Adc.AdcConfigSet_0.AdcHwUnit_0.AdcAnalogClockSource')
        """
        matches = []
        parts = rule_path.split('.')
        
        if len(parts) < 2:
            return matches
        
        module_name = parts[0]
        param_name = parts[-1]
        
        # Find all nodes that: start with module name AND end with param name
        for node in self.all_nodes:
            if node.startswith(module_name + '.') and node.endswith('.' + param_name):
                matches.append(node)
        
        return matches

    def analyze_impact(self, node_path: str) -> List[ImpactPath]:
        """Find all nodes affected by a change in node_path (BFS)"""
        # Normalize input path
        query_path = self._to_dot_path(node_path)
        
        logger.debug(f"Analyzing impact for: {query_path}")
        logger.debug(f"Graph has {len(self.all_nodes)} nodes and {sum(len(v) for v in self.graph.values())} edges")
        
        # Show sample of Adc nodes for debugging
        adc_nodes = [n for n in self.all_nodes if n.startswith('Adc.')][:5]
        if adc_nodes:
            logger.debug(f"Sample Adc nodes in graph: {adc_nodes}")
        
        # Try to find matching nodes (exact or partial match)
        matching_nodes = self._find_matching_nodes(query_path)
        
        if not matching_nodes:
            logger.warning(f"Node not found in graph: {query_path}")
            # Try to find similar nodes
            similar = [n for n in self.all_nodes if query_path.split('.')[-1] in n][:3]
            if similar:
                logger.debug(f"Similar nodes containing param name: {similar}")
            return []
        
        logger.debug(f"Found {len(matching_nodes)} matching nodes: {matching_nodes}")
        
        # Check if matching nodes have any edges
        for mn in matching_nodes:
            if mn in self.graph:
                logger.debug(f"Node {mn} has {len(self.graph[mn])} outgoing edges")
            else:
                logger.debug(f"Node {mn} has NO outgoing edges in graph")
        
        impacts = []
        visited = set()
        
        # Start BFS from all matching nodes
        queue = collections.deque()
        for node in matching_nodes:
            queue.append((node, []))
        
        while queue:
            current, history = queue.popleft()
            
            if current in visited:
                continue
            visited.add(current)

            # Explore neighbors
            if current in self.graph:
                for target, dtype, reason in self.graph[current]:
                    if target not in visited:
                        new_history = history + [current]
                        
                        # Create impact record
                        impacts.append(ImpactPath(
                            source=query_path,
                            target=target,
                            path=new_history + [target],
                            reason=reason,
                            dependency_type=dtype
                        ))
                        
                        queue.append((target, new_history))
        
        logger.info(f"Found {len(impacts)} impacts for {query_path}")
        return impacts
    
    def _find_matching_nodes(self, query: str) -> List[str]:
        """Find nodes that match the query (exact or suffix match)"""
        matches = []
        
        # Exact match
        if query in self.all_nodes:
            matches.append(query)
            return matches
        
        # Try suffix match (query might be partial path)
        for node in self.all_nodes:
            if node.endswith(query) or node.endswith('.' + query):
                matches.append(node)
        
        # If no suffix match, try contains match
        if not matches:
            query_parts = query.split('.')
            for node in self.all_nodes:
                node_parts = node.split('.')
                # Check if all query parts appear in node parts (in order)
                idx = 0
                for part in node_parts:
                    if idx < len(query_parts) and part == query_parts[idx]:
                        idx += 1
                if idx == len(query_parts):
                    matches.append(node)
        
        return matches

    def _normalize_path(self, arxml_path: str) -> str:
        """Convert ARXML path to logical dot-separated path"""
        # /Config/Mcu/Container -> Mcu.Container
        parts = [p for p in arxml_path.split('/') if p and p != 'Config']
        if len(parts) >= 2:
            return '.'.join(parts)
        elif len(parts) == 1:
            return parts[0]
        return self._to_dot_path(arxml_path)
    
    def get_graph_stats(self) -> Dict:
        """Get statistics about the dependency graph"""
        return {
            'total_nodes': len(self.all_nodes),
            'total_edges': sum(len(v) for v in self.graph.values()),
            'structural_edges': sum(1 for edges in self.graph.values() for _, dtype, _ in edges if dtype == 'structural'),
            'logical_edges': sum(1 for edges in self.graph.values() for _, dtype, _ in edges if dtype == 'logical'),
            'inferred_edges': sum(1 for edges in self.graph.values() for _, dtype, _ in edges if dtype == 'inferred'),
        }
