"""
Error Definitions for EB Template Engine
"""


class EBTemplateError(Exception):
    """Base exception for all EB template engine errors"""
    pass


class DanglingReferenceError(EBTemplateError):
    """Raised when a reference points to a non-existent node"""
    def __init__(self, ref_path: str, context: str = ""):
        self.ref_path = ref_path
        self.context = context
        super().__init__(f"Dangling reference: '{ref_path}'" + (f" in {context}" if context else ""))


class TypeMismatchError(EBTemplateError):
    """Raised when an operation receives incompatible types"""
    def __init__(self, expected: str, actual: str, operation: str = ""):
        self.expected = expected
        self.actual = actual
        self.operation = operation
        msg = f"Type mismatch: expected {expected}, got {actual}"
        if operation:
            msg += f" in {operation}"
        super().__init__(msg)


class MultiplicityViolationError(EBTemplateError):
    """Raised when container count violates XDM constraints"""
    def __init__(self, container_path: str, actual: int, min_val: int, max_val: int):
        self.container_path = container_path
        self.actual = actual
        self.min_val = min_val
        self.max_val = max_val
        max_str = "*" if max_val == -1 else str(max_val)
        super().__init__(
            f"Multiplicity violation at '{container_path}': "
            f"found {actual}, expected {min_val}..{max_str}"
        )


class TemplateParseError(EBTemplateError):
    """Raised when template parsing fails"""
    def __init__(self, message: str, line: int = 0, column: int = 0, 
                 template_file: str = "", context_path: str = ""):
        self.line = line
        self.column = column
        self.template_file = template_file
        self.context_path = context_path
        
        loc_parts = []
        if template_file:
            loc_parts.append(f"in '{template_file}'")
        if line > 0:
            loc_parts.append(f"at line {line}")
        if column > 0:
            loc_parts.append(f"column {column}")
        if context_path:
            loc_parts.append(f"context: {context_path}")
        
        loc = " ".join(loc_parts)
        super().__init__(f"Parse error {loc}: {message}" if loc else f"Parse error: {message}")


class UndefinedVariableError(EBTemplateError):
    """Raised when accessing an undefined variable"""
    def __init__(self, var_name: str):
        self.var_name = var_name
        super().__init__(f"Undefined variable: ${var_name}")


class XPathError(EBTemplateError):
    """Raised when XPath evaluation fails"""
    def __init__(self, xpath: str, reason: str):
        self.xpath = xpath
        self.reason = reason
        super().__init__(f"XPath error in '{xpath}': {reason}")
