"""
Context Stack for Template Execution

Manages the current context node during template processing.
Implements:
- Stack-based context management (push/pop for LOOP, SELECT)
- node:current() always returns stack top
- Variable scoping with shadowing
"""
from typing import Dict, Any, Optional, List
from dataclasses import dataclass, field
from .symbol_table import ConfigurationNode


@dataclass
class Scope:
    """A single scope level in the execution context"""
    # Current context node (what '.' refers to)
    context_node: Optional[ConfigurationNode] = None
    
    # Variables defined in this scope
    variables: Dict[str, Any] = field(default_factory=dict)
    
    # Loop index (if inside a LOOP)
    loop_index: int = -1
    loop_count: int = 0


class ContextStack:
    """Manages execution context during template rendering.
    
    Key behaviors:
    - LOOP and SELECT push new scope with new context node
    - ENDLOOP and ENDSELECT pop scope
    - Variable lookup chains through parent scopes
    - node:current() returns current scope's context_node
    """
    
    def __init__(self, root_node: Optional[ConfigurationNode] = None):
        """Initialize context stack.
        
        Args:
            root_node: Initial context node (usually module root)
        """
        self._stack: List[Scope] = []
        # Create root scope
        self._stack.append(Scope(context_node=root_node))
    
    def push(self, context_node: Optional[ConfigurationNode] = Ellipsis):
        """Push a new scope onto the stack.
        
        Args:
            context_node: New context node for this scope (provided as None to clear context)
        """
        if context_node is Ellipsis:
            context_node = self.current_node()
            
        new_scope = Scope(
            context_node=context_node
        )
        self._stack.append(new_scope)
    
    def pop(self) -> Scope:
        """Pop the current scope from the stack.
        
        Returns:
            The popped Scope
            
        Raises:
            RuntimeError: If attempting to pop the root scope
        """
        if len(self._stack) <= 1:
            raise RuntimeError("Cannot pop root scope from context stack")
        return self._stack.pop()
    
    def current_scope(self) -> Scope:
        """Get the current (top) scope"""
        return self._stack[-1]
    
    def current_node(self) -> Optional[ConfigurationNode]:
        """Get the current context node (for node:current())"""
        return self._stack[-1].context_node
    
    def set_context_node(self, node: ConfigurationNode):
        """Set the context node for the current scope"""
        self._stack[-1].context_node = node
    
    def set_loop_info(self, index: int, count: int):
        """Set loop iteration info for current scope"""
        self._stack[-1].loop_index = index
        self._stack[-1].loop_count = count
    
    def get_loop_index(self) -> int:
        """Get current loop index (0-based), or -1 if not in a loop"""
        return self._stack[-1].loop_index
    
    def get_loop_count(self) -> int:
        """Get total loop count, or 0 if not in a loop"""
        return self._stack[-1].loop_count
    
    def get_loop_info(self) -> tuple:
        """Get current loop info (index, count). Provided for backward compatibility."""
        return self.get_loop_index(), self.get_loop_count()
    
    # Variable management
    
    def set_variable(self, name: str, value: Any):
        """Set a variable, following EB Tresos [!VAR!] assignment semantics.

        If the variable already exists in an enclosing scope, update it there
        (so re-assignments inside nested LOOP/SELECT blocks propagate back to the
        scope that declared it — the accumulator idiom). Only when the variable
        is not defined in any accessible scope is it created in the current scope.
        """
        for scope in reversed(self._stack):
            if name in scope.variables:
                scope.variables[name] = value
                return
        self._stack[-1].variables[name] = value
    
    def declare_variable(self, name: str, value: Any):
        """Declare a variable in the current (top) scope unconditionally.

        Unlike set_variable, this always creates a binding in the innermost
        scope even if an outer scope already defines the same name. Used for
        scope-local bindings such as MACRO parameters, which must shadow outer
        variables so recursion and nested calls stay isolated.
        """
        self._stack[-1].variables[name] = value

    def get_variable(self, name: str) -> Any:
        """Get a variable, searching from current scope up to root.
        
        Args:
            name: Variable name
            
        Returns:
            Variable value
            
        Raises:
            KeyError: If variable not found in any scope
        """
        # Special loop variables
        if name == '@index':
            idx = self.get_loop_index()
            if idx != -1:
                return idx  # 0-based index to match test expectation (and C array indexing)
        if name == '@count':
            count = self.get_loop_count()
            if count > 0:
                return count
        
        # Search from top to bottom
        for scope in reversed(self._stack):
            if name in scope.variables:
                return scope.variables[name]
        raise KeyError(f"Undefined variable: {name}")
    
    def has_variable(self, name: str) -> bool:
        """Check if a variable is defined in any accessible scope"""
        if name == '@index' and self.get_loop_index() != -1:
            return True
        if name == '@count' and self.get_loop_count() > 0:
            return True
            
        for scope in reversed(self._stack):
            if name in scope.variables:
                return True
        return False
    
    def get_all_variables(self) -> Dict[str, Any]:
        """Get all variables visible from current scope (merged)"""
        result = {}
        for scope in self._stack:
            result.update(scope.variables)
        return result
    
    @property
    def depth(self) -> int:
        """Get current stack depth (1 = root only)"""
        return len(self._stack)
    
    def current_scope_variables(self) -> Dict[str, Any]:
        """Get variables defined only in the current (top) scope.
        
        Returns:
            Dictionary of variable names to values in current scope only
        """
        return self._stack[-1].variables.copy()
    
    def set_variable_in_parent(self, name: str, value: Any):
        """Set a variable in the parent scope (one level up from current).
        
        This is used for macro variable propagation - variables set in a macro
        should be accessible after the macro returns.
        
        Args:
            name: Variable name
            value: Variable value
        """
        if len(self._stack) >= 2:
            self._stack[-2].variables[name] = value
        else:
            # Only root scope, set there
            self._stack[-1].variables[name] = value
