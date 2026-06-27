"""AI Assistant controller — extracted from DaVinciMainWindow (P2-6, phase 1).

Owns the AI assistant dock, the NaturalLanguageProcessor lifecycle, the async
chat workers, and the per-parameter "AI help" QProcess. Holds a back-reference
to the main window (``self.win``) for shared state (settings, config_manager,
undo_stack, tree_view, config_panel, thread_pool) and Qt parenting.
"""
import logging

from PySide6.QtCore import Qt, QProcess, QProcessEnvironment
from PySide6.QtWidgets import QDockWidget

from ..async_workers import AIWorker
from ..widgets.ai_assistant import AIAssistantWidget
from ...core.ai.nlp_processor import NaturalLanguageProcessor

logger = logging.getLogger(__name__)


class AiAssistantController:
    """Groups all AI-assistant behaviour previously living on the main window."""

    def __init__(self, win):
        self.win = win
        self.ai_processor = None
        self._ai_help_process = None

    # ----- setup -------------------------------------------------------------
    def setup_dock(self):
        """Create the AI Assistant dock widget and wire its signals."""
        win = self.win
        win.ai_assistant_dock = QDockWidget("AI Assistant", win)
        win.ai_assistant_dock.setObjectName("AIAssistantDock")  # Required for saveState()
        win.ai_assistant_dock.setAllowedAreas(Qt.RightDockWidgetArea | Qt.LeftDockWidgetArea)

        win.ai_assistant_widget = AIAssistantWidget()
        win.ai_assistant_dock.setWidget(win.ai_assistant_widget)

        win.addDockWidget(Qt.RightDockWidgetArea, win.ai_assistant_dock)

        # Connect signals
        win.ai_assistant_widget.message_sent.connect(self.handle_message)
        win.ai_assistant_widget.settings_clicked.connect(self.configure_settings)

        # Hide by default
        win.ai_assistant_dock.hide()

        # Backend initialised lazily when config_manager is available.
        self.ai_processor = None

    # ----- processor lifecycle ----------------------------------------------
    def _ensure_processor(self, api_key):
        """Create the NaturalLanguageProcessor on first use; return it."""
        if not self.ai_processor:
            self.ai_processor = NaturalLanguageProcessor(
                api_key=api_key,
                config_manager=self.win.config_manager,
                undo_stack=self.win.undo_stack,
                action_handler=self.handle_action,
            )
        return self.ai_processor

    def configure_settings(self):
        """Ensure the AI processor is initialised when Settings is clicked.

        Called BEFORE the KnowledgeBaseDialog opens.
        """
        api_key = self.win.settings.value("gemini_api_key")
        self._ensure_processor(api_key)

        # Always ensure the KB reference is set on the widget.
        if self.ai_processor and hasattr(self.ai_processor, 'knowledge_base'):
            self.win.ai_assistant_widget.knowledge_base = self.ai_processor.knowledge_base

    # ----- chat --------------------------------------------------------------
    def handle_message(self, text: str):
        """Handle a message from the AI Assistant widget."""
        win = self.win
        api_key = win.settings.value("gemini_api_key")

        if not self.ai_processor:
            self._ensure_processor(api_key)
            # Set knowledge base reference on the widget for the Settings dialog.
            win.ai_assistant_widget.knowledge_base = self.ai_processor.knowledge_base
        else:
            # Keep references current.
            self.ai_processor.config_manager = win.config_manager
            if self.ai_processor.gemini_client.api_key != api_key:
                self.ai_processor.gemini_client.configure(api_key)
            self.ai_processor.action_handler = self.handle_action

        logger.debug(f"Processing AI message (async): '{text}'")
        win.ai_assistant_widget.set_status("Thinking...", busy=True)

        # Get context from selection (safely).
        context_instance = None
        try:
            if hasattr(win.tree_view, 'get_selected_instance'):
                context_instance = win.tree_view.get_selected_instance()
            else:
                logger.debug("tree_view missing get_selected_instance")
        except Exception as e:
            logger.debug(f"Context error: {e}")

        worker = AIWorker(self.ai_processor, text, context_instance)
        worker.signals.result.connect(self.on_response)
        worker.signals.error.connect(self.on_error)
        win.thread_pool.start(worker)

    def on_response(self, response: str):
        """Handle an AI response from the worker thread."""
        logger.debug(f"AI Response received: '{response[:50]}...'")
        self.win.ai_assistant_widget.append_message("AI", response)
        self.win.ai_assistant_widget.set_status("Ready")

    def on_error(self, error_msg: str):
        """Handle an AI error from the worker thread."""
        logger.debug(f"AI Error: {error_msg}")
        self.win.ai_assistant_widget.append_message("System", f"❌ Error: {error_msg}")
        self.win.ai_assistant_widget.set_status("Error")

    def handle_action(self, action_name: str):
        """Execute an action requested by the AI."""
        if action_name == "validate":
            self.win.validation_controller.validate_configuration()
        elif action_name == "save":
            # Works for both single-module and project mode.
            self.win.save_project()
        elif action_name == "generate":
            self.win.generation_controller.generate_code()

    # ----- per-parameter contextual help ------------------------------------
    def on_help_requested(self, container_name: str, param_name: str):
        """Handle an AI help request for a parameter — provide contextual guidance."""
        win = self.win
        api_key = win.settings.value("gemini_api_key")
        if not api_key:
            win.config_panel.update_ai_help("⚠️ 请先在 AI Assistant 中配置 API Key")
            return

        self._ensure_processor(api_key)

        # Build prompt for AI — handle both parameters and references.
        if param_name.startswith("REF:"):
            # Reference request — format: "REF:ref_name:dest_type"
            parts = param_name.split(":", 2)
            ref_name = parts[1] if len(parts) > 1 else param_name
            dest_type = parts[2] if len(parts) > 2 else "unknown"

            prompt = f"""你是一个AUTOSAR BSW配置专家。请针对以下引用(Reference)提供简洁的配置指导：

容器: {container_name}
引用名: {ref_name}
目标类型: {dest_type}

请用2-3句话说明：
1. 这个引用的作用是什么？它连接什么模块或资源？
2. 配置时需要注意什么？如何选择正确的目标？

请直接给出指导，不要有多余的开场白。使用中文回答。"""
        else:
            # Parameter request
            prompt = f"""你是一个AUTOSAR BSW配置专家。请针对以下参数提供简洁的配置指导：

容器: {container_name}
参数: {param_name}

请用2-3句话说明：
1. 这个参数的作用是什么？它影响什么功能？
2. 配置时需要注意什么？有什么常见错误要避免？

请直接给出指导，不要有多余的开场白。使用中文回答。"""

        # Use subprocess via QProcess for truly killable AI requests.
        import sys

        process = QProcess(win)
        win.config_panel.current_ai_process = process  # Store for cancellation

        # Build Python script to run in the subprocess.
        script = '''
import os
import sys
import google.generativeai as genai

# Read the API key from the environment instead of argv so it is not
# visible to other users via `ps`/`/proc/<pid>/cmdline` for the
# subprocess lifetime.
api_key = os.environ.get("GEMINI_API_KEY", "")
prompt = sys.argv[1]
model_name = sys.argv[2] if len(sys.argv) > 2 else "gemini-2.0-flash"

try:
    genai.configure(api_key=api_key)
    model = genai.GenerativeModel(model_name)
    response = model.generate_content(prompt, request_options={"timeout": 15})
    print(response.text)
except Exception as e:
    print(f"ERROR: {str(e)}", file=sys.stderr)
'''

        def on_finished(exit_code, exit_status):
            if win.config_panel.ai_request_cancelled:
                self._ai_help_process = None
                return

            try:
                if self._ai_help_process:
                    output = self._ai_help_process.readAllStandardOutput().data().decode('utf-8').strip()
                    error = self._ai_help_process.readAllStandardError().data().decode('utf-8').strip()

                    if exit_code == 0 and output:
                        win.config_panel.update_ai_help(output)
                        win.config_panel.cache_ai_help(container_name, param_name, output)
                    elif error:
                        win.config_panel.update_ai_help(f"❌ {error}")
                    else:
                        win.config_panel.update_ai_help("❌ 请求失败，请重试")
            except RuntimeError:
                pass  # Process already deleted
            finally:
                win.config_panel.current_ai_process = None
                self._ai_help_process = None

        process.finished.connect(on_finished)

        # Store reference to prevent garbage collection.
        self._ai_help_process = process

        # Get current model name.
        model_name = "gemini-2.0-flash"
        if self.ai_processor and self.ai_processor.gemini_client:
            model_name = self.ai_processor.gemini_client.get_current_model()

        # Pass the API key via the process environment (not argv) so it is not
        # exposed in the process listing to other local users.
        env = QProcessEnvironment.systemEnvironment()
        env.insert("GEMINI_API_KEY", api_key)
        process.setProcessEnvironment(env)

        # Start subprocess (api_key intentionally NOT passed as an argument).
        process.start(sys.executable, ["-c", script, prompt, model_name])

    # ----- teardown ----------------------------------------------------------
    def cleanup(self):
        """Terminate any in-flight AI help subprocess (called on window close)."""
        if self._ai_help_process is not None:
            if self._ai_help_process.state() != QProcess.NotRunning:
                self._ai_help_process.terminate()
                self._ai_help_process.waitForFinished(1000)
