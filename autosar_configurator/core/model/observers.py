"""
Observer pattern implementation for data model changes
"""
from typing import Any, Protocol


class Observer(Protocol):
    """Observer base class"""

    def handle_update(self, event: str, data: Any):
        """Called when observed object changes

        Args:
            event: Event type (e.g., 'modified', 'added', 'removed')
            data: Event data
        """
        ...


class Subject:
    """Subject base class for observable objects"""

    def __init__(self):
        self._observers: list[Observer] = []

    def attach(self, observer: Observer):
        """Attach an observer"""
        if observer not in self._observers:
            self._observers.append(observer)

    def detach(self, observer: Observer):
        """Detach an observer"""
        if observer in self._observers:
            self._observers.remove(observer)

    def notify(self, event: str, data: Any = None):
        """Notify all observers"""
        for observer in self._observers:
            observer.handle_update(event, data)
