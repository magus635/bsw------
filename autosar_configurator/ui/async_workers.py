"""Shared Qt worker primitives for non-blocking background calls.

Extracted from davinci_main_window.py so they can be reused by multiple
controllers (AI assistant, cross-module dependency analysis) without pulling
in the whole main window module.
"""
from PySide6.QtCore import QObject, Signal, QRunnable, Slot


class AIWorkerSignals(QObject):
    """Signals for a background worker thread."""
    result = Signal(object)  # Emits the response (str or complex object)
    error = Signal(str)      # Emits an error message


class AIWorker(QRunnable):
    """Worker thread for non-blocking AI API calls."""

    def __init__(self, processor, text: str, context_instance):
        super().__init__()
        self.signals = AIWorkerSignals()
        self.processor = processor
        self.text = text
        self.context_instance = context_instance

    @Slot()
    def run(self):
        """Execute the AI processing in a background thread."""
        try:
            response = self.processor.process_message(self.text, self.context_instance)
            self.signals.result.emit(response)
        except Exception as e:
            self.signals.error.emit(str(e))
