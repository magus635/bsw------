"""
Cross-Module Dependency Validator

This module reads confirmed dependency rules from a markdown file
and validates project configurations against those rules.
"""
from typing import Dict, List, Optional, Tuple
from pathlib import Path
import re

from ..validation_engine import ValidationRule, ValidationResult, ValidationMessage


class CrossModuleDependencyRule:
    """Represents a single cross-module dependency rule"""
    
    def __init__(
        self,
        source_param: str,
        source_condition: str,
        source_value: str,
        target_param: str,
        target_condition: str,
        target_value: str,
        reason: str,
        status: str = 'pending'
    ):
        self.source_param = source_param
        self.source_condition = source_condition
        self.source_value = source_value
        self.target_param = target_param
        self.target_condition = target_condition
        self.target_value = target_value
        self.reason = reason
        self.status = status
    
    def __repr__(self):
        return f"Rule({self.source_param} {self.source_condition} {self.source_value} -> {self.target_param} {self.target_condition} {self.target_value})"


class CrossModuleValidator:
    """Validates cross-module dependencies based on confirmed rules"""
    
    def __init__(self):
        self.rules: List[CrossModuleDependencyRule] = []
    
    def load_rules_from_markdown(self, md_path: Path) -> int:
        """
        Load confirmed dependency rules from a markdown file.
        
        Args:
            md_path: Path to the dependencies.md file
            
        Returns:
            Number of confirmed rules loaded
        """
        self.rules = []
        
        if not md_path.exists():
            print(f"Warning: Dependency file not found: {md_path}")
            return 0
        
        content = md_path.read_text(encoding='utf-8')
        
        # First, count how many [x] marked rows exist
        confirmed_rows = re.findall(r'\|\s*\d+\s*\|\s*\[\s*x\s*\]\s*\|', content, re.IGNORECASE)
        print(f"[DEBUG] Found {len(confirmed_rows)} rows with [x] status in markdown")
        
        # Parse table rows - look for lines with confirmed status [x] (flexible whitespace)
        # New format: | # | [x] | 来源 | `source_param` | condition value | `target_param` | condition value | reason |
        # Old format: | # | [x] | `source_param` | condition value | `target_param` | condition value | reason |
        # Support [x], [ x], [x ], [ x ]
        table_pattern_new = re.compile(
            r'\|\s*\d+\s*\|\s*\[\s*x\s*\]\s*\|[^|]+\|\s*`([^`]+)`\s*\|\s*([^|]+)\|\s*`([^`]+)`\s*\|\s*([^|]+)\|\s*([^|]+)\|',
            re.IGNORECASE
        )
        table_pattern_old = re.compile(
            r'\|\s*\d+\s*\|\s*\[\s*x\s*\]\s*\|\s*`([^`]+)`\s*\|\s*([^|]+)\|\s*`([^`]+)`\s*\|\s*([^|]+)\|\s*([^|]+)\|',
            re.IGNORECASE
        )
        
        # Try new format first, then old format
        for pattern_name, pattern in [("new", table_pattern_new), ("old", table_pattern_old)]:
            matches = list(pattern.finditer(content))
            print(f"[DEBUG] Pattern '{pattern_name}' matched {len(matches)} rows")
            
            for match in matches:
                source_param = match.group(1).strip()
                source_cond_val = match.group(2).strip()
                target_param = match.group(3).strip()
                target_cond_val = match.group(4).strip()
                reason = match.group(5).strip()
                
                # Parse condition and value
                source_cond, source_val = self._parse_condition_value(source_cond_val)
                target_cond, target_val = self._parse_condition_value(target_cond_val)
                
                if source_cond and target_cond:
                    rule = CrossModuleDependencyRule(
                        source_param=source_param,
                        source_condition=source_cond,
                        source_value=source_val,
                        target_param=target_param,
                        target_condition=target_cond,
                        target_value=target_val,
                        reason=reason,
                        status='confirmed'
                    )
                    self.rules.append(rule)
                else:
                    print(f"[WARN] Skipped rule due to condition parsing failure: {source_param} -> {target_param}")
            
            # If found rules with current pattern, stop
            if self.rules:
                break
        
        print(f"Loaded {len(self.rules)} confirmed dependency rules")
        return len(self.rules)
    
    def _parse_condition_value(self, cond_val: str) -> Tuple[Optional[str], Optional[str]]:
        """Parse condition and value from a string like '= true', '>= 1024', 'exists true', or 'undefined N/A'"""
        cond_val = cond_val.strip()
        if not cond_val:
            return None, None
        
        # Support operators: =, ==, !=, <, <=, >, >=, exists
        match = re.match(r'([=<>!]+|exists)\s*(.+)', cond_val)
        if match:
            return match.group(1), match.group(2).strip()
        
        # Fallback: treat the whole string as value with '=' condition
        # This handles AI-generated formats like 'undefined N/A', '<reference_to_valid_clock> N/A'
        # We'll treat it as an existence/presence check
        return '=', cond_val
    
    def validate_project(self, project) -> ValidationResult:
        """
        Validate a project against loaded dependency rules.
        
        Args:
            project: ProjectWorkspace instance
            
        Returns:
            ValidationResult with any violations found
        """
        result = ValidationResult()
        
        if not project or not hasattr(project, 'module_managers'):
            return result
        
        if not self.rules:
            result.add_message(ValidationMessage(
                severity="warning",
                message="No dependency rules loaded. Run 'Analyze Dependencies' first.",
                suggested_fix="Execute 'Analyze Cross-Module Dependencies' from the menu"
            ))
            return result
        
        # Build a lookup of all parameter values across modules
        param_values = self._build_param_lookup(project)
        
        # Check each rule
        for rule in self.rules:
            violations = self._check_rule(rule, param_values)
            for violation in violations:
                result.add_message(violation)
        
        return result
    
    def _build_param_lookup(self, project) -> Dict[str, any]:
        """Build a lookup dictionary of all parameter values"""
        lookup = {}
        
        for module_name, manager in project.module_managers.items():
            if manager.configuration:
                self._add_config_to_lookup(
                    module_name, 
                    manager.configuration.containers, 
                    lookup
                )
        
        return lookup
    
    def _add_config_to_lookup(
        self, 
        module_name: str, 
        containers: List, 
        lookup: Dict,
        parent_path: str = ""
    ):
        """Recursively add container parameters to lookup"""
        for container in containers:
            container_path = f"{parent_path}/{container.short_name}" if parent_path else container.short_name
            
            # Add parameter values
            for param_name, param_value in container.parameter_values.items():
                full_path = f"{module_name}.{container_path}.{param_name}"
                lookup[full_path] = param_value.value
                # Also add short forms for easier matching
                lookup[f"{module_name}.{param_name}"] = param_value.value
            
            # Add reference values
            for ref_name, ref_value in container.reference_values.items():
                full_path = f"{module_name}.{container_path}.{ref_name}"
                lookup[full_path] = ref_value.value_ref
                lookup[f"{module_name}.{ref_name}"] = ref_value.value_ref
            
            # Recurse into sub-containers
            self._add_config_to_lookup(
                module_name, 
                container.sub_containers, 
                lookup, 
                container_path
            )
    
    def _check_rule(
        self, 
        rule: CrossModuleDependencyRule, 
        param_values: Dict[str, any]
    ) -> List[ValidationMessage]:
        """Check a single rule against parameter values"""
        violations = []
        
        # Find source parameter value
        source_value = self._find_param_value(rule.source_param, param_values)
        if source_value is None:
            # Source parameter not found, can't check
            return violations
        
        # Check if source condition is met
        if not self._check_condition(source_value, rule.source_condition, rule.source_value):
            # Source condition not met, rule doesn't apply
            return violations
        
        # Source condition is met, check target
        target_value = self._find_param_value(rule.target_param, param_values)
        
        # Handle 'exists' condition
        if rule.target_condition == 'exists':
            if target_value is None:
                violations.append(ValidationMessage(
                    severity="error",
                    message=f"跨模块依赖违规: {rule.source_param} = {source_value}，"
                            f"但目标 {rule.target_param} 不存在",
                    rule_name="CrossModuleDependency",
                    details=rule.reason,
                    suggested_fix=f"确保 {rule.target_param} 已配置"
                ))
            return violations
        
        # Target parameter must satisfy its condition
        if target_value is None:
            violations.append(ValidationMessage(
                severity="error",
                message=f"跨模块依赖违规: {rule.source_param} = {source_value}，"
                        f"但目标参数 {rule.target_param} 未配置",
                rule_name="CrossModuleDependency",
                details=rule.reason,
                suggested_fix=f"配置 {rule.target_param} {rule.target_condition} {rule.target_value}"
            ))
        elif not self._check_condition(target_value, rule.target_condition, rule.target_value):
            violations.append(ValidationMessage(
                severity="error",
                message=f"跨模块依赖违规: {rule.source_param} = {source_value}，"
                        f"要求 {rule.target_param} {rule.target_condition} {rule.target_value}，"
                        f"但实际值为 {target_value}",
                rule_name="CrossModuleDependency",
                details=rule.reason,
                suggested_fix=f"将 {rule.target_param} 设置为 {rule.target_condition} {rule.target_value}"
            ))
        
        return violations
    
    def _find_param_value(self, param_path: str, param_values: Dict[str, any]) -> Optional[any]:
        """Find a parameter value by path, trying various matching strategies"""
        # Direct match
        if param_path in param_values:
            return param_values[param_path]
        
        # Partial match - try to find params that end with the given path
        for key, value in param_values.items():
            if key.endswith(param_path) or param_path in key:
                return value
        
        return None
    
    def _check_condition(self, actual_value: any, condition: str, expected_value: str) -> bool:
        """Check if a value satisfies a condition"""
        # Convert expected value to appropriate type
        expected = self._convert_value(expected_value, type(actual_value))
        
        try:
            if condition == '=' or condition == '==':
                return actual_value == expected
            elif condition == '!=':
                return actual_value != expected
            elif condition == '>':
                return float(actual_value) > float(expected)
            elif condition == '>=':
                return float(actual_value) >= float(expected)
            elif condition == '<':
                return float(actual_value) < float(expected)
            elif condition == '<=':
                return float(actual_value) <= float(expected)
            elif condition == 'exists':
                return actual_value is not None
        except (TypeError, ValueError):
            pass
        
        return False
    
    def _convert_value(self, value_str: str, target_type: type) -> any:
        """Convert a string value to the target type"""
        value_str = value_str.strip()
        
        # Boolean
        if value_str.lower() in ('true', 'false'):
            return value_str.lower() == 'true'
        
        # Integer
        try:
            return int(value_str)
        except ValueError:
            pass
        
        # Float
        try:
            return float(value_str)
        except ValueError:
            pass
        
        # String
        return value_str
