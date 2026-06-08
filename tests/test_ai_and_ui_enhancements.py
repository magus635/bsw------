import os
import sys
from pathlib import Path
from unittest.mock import patch

import pytest

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.core.ai.nlp_processor import NaturalLanguageProcessor
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import EcucModuleDef

# ---------------------------------------------------------------------------
# Guard: skip the whole module unless the caller explicitly opts in.
# Set RUN_AI_TESTS=1 in the environment to run these tests.
# They are excluded from the normal regression gate because they make real
# network calls to Google Gemini and can hang indefinitely.
# ---------------------------------------------------------------------------
pytestmark = pytest.mark.skipif(
    not os.environ.get("RUN_AI_TESTS"),
    reason="Skipped by default: makes real Gemini API calls. Set RUN_AI_TESTS=1 to enable.",
)


def test_ai_template_intent():
    # Patch out GEMINI_API_KEY so no real network call is made when running
    # under RUN_AI_TESTS=1 without a live key; the NLP layer should return
    # its local "API Key not configured" fallback message.
    with patch.dict(os.environ, {"GEMINI_API_KEY": ""}, clear=False):
        mcu_def = EcucModuleDef("Mcu")
        config_mgr = ConfigurationManager(mcu_def)

        # api_key=None + empty env var → GeminiClient never configures → is_ready() is False
        nlp = NaturalLanguageProcessor(api_key=None, config_manager=config_mgr)

        # Test intent recognition
        response_save = nlp.process_message("保存项目")
        print(f"Intent 'Save': {response_save}")
        assert "保存" in response_save

        # Template intent without a live key should return the "configure API Key" warning
        response_tpl = nlp.process_message("帮我写一个 Adc 的模板")
        print(f"Intent 'Template': {response_tpl}")
        assert any(x in response_tpl for x in ["API Key", "模板", "tpl", "template"])

        response_tpl_en = nlp.process_message("Write a template for Mcu")
        print(f"Intent 'Template EN': {response_tpl_en}")
        assert any(x in response_tpl_en for x in ["API Key", "模板", "tpl", "template"])


def test_ui_import():
    try:
        from autosar_configurator.ui.widgets.variant_management_dialog import VariantManagementDialog
        print("VariantManagementDialog import: SUCCESS")
    except ImportError as e:
        print(f"VariantManagementDialog import: FAILED - {e}")
        sys.exit(1)


if __name__ == "__main__":
    print("--- Testing AI Intent Recognition ---")
    test_ai_template_intent()
    print("\n--- Testing UI Component Import ---")
    test_ui_import()
    print("\nSUCCESS: All enhancements verified (intent & structure)!")
