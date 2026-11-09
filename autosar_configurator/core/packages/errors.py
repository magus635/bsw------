"""Package-related errors."""


class PackageError(Exception):
    """Base exception for module package errors."""
    pass


class PackageConflictError(PackageError):
    """Conflict in package definitions or values.

    Attributes:
        path: AUTOSAR path where conflict occurred
        files: List of files involved in the conflict
    """

    def __init__(self, message: str, path: str, files: list):
        super().__init__(message)
        self.path = path
        self.files = files
