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
    
    def push(self, context_node: Optional[ConfigurationNode] = None):
        """Push a new scope onto the stack.
        
        Args:
            context_node: New context node for this scope (or inherit from parent)
        """
        new_scope = Scope(
            context_node=context_node or self.current_node()
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
    
    # Variable management
    
    def set_variable(self, name: str, value: Any):
        """Set a variable. If it exists in a parent scope, update it there.
        Otherwise, set it in the current scope.
        
        Args:
            name: Variable name
            value: Variable value
        """
        # Search from top to bottom for existing variable to update
        for scope in reversed(self._stack):
            if name in scope.variables:
                scope.variables[name] = value
                return
        
        # If not found anywhere, create in current scope
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
