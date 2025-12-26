"""
Object Graph Context Builder for AI/RAG

Implements a smart trimming strategy:
- L0: Anchor object (always included)
- L1: Direct semantic relationships (required)
- L2: Limited causal expansion (optional)
- STOP: Depth/count limits

Key insight: 
把"工程依赖图"压缩成"回答当前问题所需的最小因果子图"。
"""
from typing import Optional, List, Dict, Any, Set
from dataclasses import dataclass, field


@dataclass
class TrimmingConfig:
    """Configuration for context graph trimming"""
    max_depth: int = 2
    max_nodes: int = 30
    max_reverse_refs: int = 3
    max_params_per_container: int = 5
    max_sub_containers: int = 3
    include_l2_expansion: bool = True


@dataclass
class ContextResult:
    """Result of context building with metadata for AI transparency"""
    context_text: str
    anchor_path: str
    node_count: int
    depth_reached: int
    truncated: bool = False
    truncation_reasons: List[str] = field(default_factory=list)
    
    def to_dict(self) -> Dict:
        """Convert to dict for structured AI consumption"""
        return {
            "anchor": self.anchor_path,
            "node_count": self.node_count,
            "depth": self.depth_reached,
            "truncated": self.truncated,
            "limits": {
                "max_depth": 2,
                "max_nodes": 30
            }
        }


class ObjectGraphContextBuilder:
    """Builds trimmed context subgraph from the object graph for AI
    
    Trimming Strategy:
    - L0: Anchor object (必选)
    - L1: Direct semantic relationships (必选)
    - L2: Causal expansion with limits (可选)
    - STOP: When depth/count limits reached
    
    Usage:
        builder = ObjectGraphContextBuilder(project)
        result = builder.build_context(selected_container)
        # result.context_text -> for AI prompt
        # result.truncated -> tell AI what was cut
    """
    
    def __init__(self, project=None, config: TrimmingConfig = None):
        self.project = project
        self.config = config or TrimmingConfig()
        
        # Tracking for STOP conditions
        self._visited: Set[str] = set()
        self._node_count: int = 0
        self._current_depth: int = 0
        self._truncation_reasons: List[str] = []
    
    def build_context(self, anchor, depth: int = None) -> ContextResult:
        """Build trimmed context from anchor object
        
        Args:
            anchor: EcucContainerValue (anchor object)
            depth: Override max depth (optional)
            
        Returns:
            ContextResult with context text and metadata
        """
        if anchor is None:
            return ContextResult("", "", 0, 0)
        
        # Reset tracking
        self._visited = set()
        self._node_count = 0
        self._current_depth = 0
        self._truncation_reasons = []
        
        max_depth = depth if depth is not None else self.config.max_depth
        
        lines = []
        lines.append("# Configuration Context")
        lines.append("")
        
        # L0: Anchor object (必选)
        lines.extend(self._build_l0_anchor(anchor))
        
        # L1: Direct semantic relationships (必选)
        lines.extend(self._build_l1_semantic(anchor))
        
        # Diagnostics: Resolution issues for AI (if any)
        lines.extend(self._build_resolution_issues(anchor))
        
        # L2: Causal expansion (可选, 有限)
        if self.config.include_l2_expansion and max_depth >= 2:
            lines.extend(self._build_l2_causal(anchor))
        
        # Truncation notice for AI
        if self._truncation_reasons:
            lines.append("")
            lines.append("---")
            lines.append(f"*Context truncated: {'; '.join(self._truncation_reasons[:3])}*")
        
        context_text = "\n".join(lines)
        
        return ContextResult(
            context_text=context_text,
            anchor_path=anchor.get_path(),
            node_count=self._node_count,
            depth_reached=self._current_depth,
            truncated=len(self._truncation_reasons) > 0,
            truncation_reasons=self._truncation_reasons
        )
    
    def _build_l0_anchor(self, anchor) -> List[str]:
        """L0: Anchor object - always included
        
        Contains:
        - Object type
        - shortName
        - value (if parameter)
        - definition (Def)
        - path
        """
        lines = []
        self._mark_visited(anchor.get_path())
        
        lines.append(f"## [L0] Anchor: `{anchor.short_name}`")
        lines.append(f"- **Path**: `{anchor.get_path()}`")
        lines.append(f"- **Definition**: `{anchor.definition_ref}`")
        
        # Key parameters (limited)
        if anchor.parameter_values:
            param_count = len(anchor.parameter_values)
            shown = list(anchor.parameter_values.items())[:self.config.max_params_per_container]
            
            lines.append("")
            lines.append("### Parameters")
            for name, param_val in shown:
                val_display = repr(param_val.value) if param_val.value is not None else "(not set)"
                lines.append(f"- `{name}` = {val_display}")
            
            if param_count > len(shown):
                lines.append(f"- *... and {param_count - len(shown)} more*")
                self._add_truncation(f"{param_count - len(shown)} params omitted")
        
        lines.append("")
        return lines
    
    def _build_l1_semantic(self, anchor) -> List[str]:
        """L1: Direct semantic relationships - required
        
        Includes:
        1. Ref → target (forward references with error details)
        2. Parameter → Definition
        3. Reverse Ref (who depends on me, limited)
        """
        lines = []
        
        # 1. Forward references (Ref → target) with error details
        if anchor.reference_values:
            lines.append("## [L1] Forward References")
            for ref_name, ref_val in anchor.reference_values.items():
                target_path = ref_val.value_ref
                
                if ref_val.is_resolved:
                    lines.append(f"- `{ref_name}` → `{target_path}` [✅ Resolved]")
                    # Show target's key params if resolved
                    if ref_val.target and not self._should_stop():
                        target = ref_val.target
                        self._mark_visited(target.get_path())
                        key_params = self._extract_key_params(target)
                        for p_name, p_val in key_params[:3]:
                            lines.append(f"  - `{p_name}` = {repr(p_val)}")
                elif ref_val.has_error:
                    error = ref_val.resolution_error
                    lines.append(f"- `{ref_name}` → `{target_path}` [❌ {error.error_type}]")
                    lines.append(f"  - **Error**: {error.message}")
                    lines.append(f"  - **Suggestion**: {error.suggestion}")
                else:
                    lines.append(f"- `{ref_name}` → `{target_path}` [⏳ Pending]")
            lines.append("")
        
        # 2. Reverse references (who depends on me)
        if hasattr(anchor, 'referenced_by') and anchor.referenced_by:
            ref_count = len(anchor.referenced_by)
            shown_refs = anchor.referenced_by[:self.config.max_reverse_refs]
            
            lines.append("## [L1] Referenced By (dependents)")
            for ref_val in shown_refs:
                source = self._find_reference_source(ref_val)
                if source:
                    ref_name = ref_val.definition_ref.split('/')[-1] if ref_val.definition_ref else "?"
                    lines.append(f"- `{source.get_path()}` via `{ref_name}`")
                    self._mark_visited(source.get_path())
            
            if ref_count > len(shown_refs):
                lines.append(f"- *... and {ref_count - len(shown_refs)} more dependents*")
                self._add_truncation(f"{ref_count - len(shown_refs)} reverse refs omitted")
            
            lines.append("")
        
        return lines
    
    def _build_resolution_issues(self, anchor) -> List[str]:
        """Build summary of all resolution errors for AI diagnostics
        
        Provides structured error information so AI can:
        1. Explain what's wrong
        2. Suggest specific fixes
        3. Reference error types and paths
        """
        lines = []
        errors_found = []
        
        # Collect errors from all references
        for ref_name, ref_val in anchor.reference_values.items():
            if ref_val.has_error:
                errors_found.append((ref_name, ref_val.resolution_error))
        
        if errors_found:
            lines.append("## [Diagnostics] Resolution Issues")
            lines.append(f"*Found {len(errors_found)} reference issue(s) requiring attention:*")
            lines.append("")
            
            for ref_name, error in errors_found:
                lines.append(f"### ❌ `{ref_name}`")
                lines.append(f"- **Type**: `{error.error_type}`")
                lines.append(f"- **Severity**: {error.severity}")
                lines.append(f"- **Problem**: {error.message}")
                lines.append(f"- **Fix**: {error.suggestion}")
                if error.candidates:
                    lines.append(f"- **Candidates**: {', '.join(str(c) for c in error.candidates[:3])}")
                lines.append("")
            
            lines.append("---")
            lines.append("*AI: Use this diagnostic info to explain problems and suggest fixes.*")
            lines.append("")
        
        return lines
    
    def _build_l2_causal(self, anchor) -> List[str]:
        """L2: Causal expansion - optional, strictly limited
        
        Rules:
        - Only follow impact paths (not structural siblings)
        - Max 1-2 representative instances for LOOP containers
        - Stop at depth limit
        """
        lines = []
        
        if self._should_stop():
            return lines
        
        self._current_depth = 2
        
        # Expand from reverse refs: who depends on the dependents?
        if hasattr(anchor, 'referenced_by') and anchor.referenced_by:
            l2_items = []
            
            for ref_val in anchor.referenced_by[:2]:  # Limit L2 expansion
                source = self._find_reference_source(ref_val)
                if source and not self._is_visited(source.get_path()):
                    # Check if source has further dependencies
                    if hasattr(source, 'referenced_by') and source.referenced_by:
                        for further_ref in source.referenced_by[:1]:  # Only 1 hop further
                            further_source = self._find_reference_source(further_ref)
                            if further_source and not self._is_visited(further_source.get_path()):
                                l2_items.append(f"- `{source.short_name}` → `{further_source.short_name}`")
                                self._mark_visited(further_source.get_path())
            
            if l2_items:
                lines.append("## [L2] Extended Impact Chain")
                lines.extend(l2_items[:5])  # Hard limit
                if len(l2_items) > 5:
                    self._add_truncation("L2 chain truncated at 5 items")
                lines.append("")
        
        # Hierarchy context (parent only, not siblings)
        if anchor.parent and not self._is_visited(anchor.parent.get_path()):
            lines.append("## [L2] Container Hierarchy")
            lines.append(f"- **Parent**: `{anchor.parent.short_name}`")
            
            sibling_count = len(anchor.parent.sub_containers) - 1
            if sibling_count > 0:
                lines.append(f"- *{sibling_count} sibling container(s) - not expanded*")
            
            self._mark_visited(anchor.parent.get_path())
            lines.append("")
        
        return lines
    
    def _extract_key_params(self, container) -> List[tuple]:
        """Extract key parameters (ID, Type, Index, etc.)"""
        key_keywords = ['id', 'type', 'index', 'name', 'enable', 'baudrate', 'address']
        result = []
        
        for name, param_val in container.parameter_values.items():
            name_lower = name.lower()
            for keyword in key_keywords:
                if keyword in name_lower:
                    result.append((name, param_val.value))
                    break
        
        # If no key params found, return first few
        if not result:
            result = [(n, p.value) for n, p in list(container.parameter_values.items())[:3]]
        
        return result
    
    def _should_stop(self) -> bool:
        """Check STOP conditions"""
        if self._node_count >= self.config.max_nodes:
            self._add_truncation(f"node limit ({self.config.max_nodes}) reached")
            return True
        if self._current_depth >= self.config.max_depth:
            return True
        return False
    
    def _mark_visited(self, path: str):
        """Mark a path as visited"""
        if path not in self._visited:
            self._visited.add(path)
            self._node_count += 1
    
    def _is_visited(self, path: str) -> bool:
        """Check if a path was already visited"""
        return path in self._visited
    
    def _add_truncation(self, reason: str):
        """Add truncation reason"""
        if reason not in self._truncation_reasons:
            self._truncation_reasons.append(reason)
    
    def _find_reference_source(self, ref_val) -> Optional[Any]:
        """Find the container that holds a given reference value"""
        if not self.project:
            return None
        
        for manager in self.project.module_managers.values():
            result = self._search_for_ref_in_container(ref_val, manager.configuration.containers)
            if result:
                return result
        return None
    
    def _search_for_ref_in_container(self, ref_val, containers) -> Optional[Any]:
        """Recursively search for the container holding a reference"""
        for container in containers:
            for ref_name, stored_ref in container.reference_values.items():
                if stored_ref is ref_val:
                    return container
            
            result = self._search_for_ref_in_container(ref_val, container.sub_containers)
            if result:
                return result
        return None
    
    # Convenience methods for specific anchor types
    
    def build_parameter_context(self, container, param_name: str) -> ContextResult:
        """Build focused context for a specific parameter"""
        # Build context from container, then add parameter focus
        result = self.build_context(container, depth=1)
        
        # Add parameter-specific header
        param_val = container.parameter_values.get(param_name)
        if param_val:
            param_info = f"\n**Focus**: Parameter `{param_name}` = {repr(param_val.value)}\n"
            result.context_text = param_info + result.context_text
        
        return result
    
    def build_reference_context(self, container, ref_name: str) -> ContextResult:
        """Build focused context for a specific reference"""
        result = self.build_context(container, depth=2)
        
        ref_val = container.reference_values.get(ref_name)
        if ref_val:
            ref_info = f"\n**Focus**: Reference `{ref_name}` → `{ref_val.value_ref}`\n"
            result.context_text = ref_info + result.context_text
        
        return result
