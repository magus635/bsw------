
import os
import sys

# Mocking the generated code structure to import GeminiClient
sys.path.append(os.getcwd())

try:
    from autosar_configurator.core.ai.gemini_client import GeminiClient
except ImportError:
    print("Could not import GeminiClient. Run from project root.")
    sys.exit(1)

# Ensure Env Var is set
os.environ["GEMINI_API_KEY"] = "MOCK_KEY_FOR_TEST"

print("--- Test 1: Init with Env Var ---")
client = GeminiClient(api_key=None)
print(f"Client API Key: {client.api_key}")
print(f"Is Configured (local flag): {client._is_configured}")

# Simulate MainWindow behavior
settings_key = None # user hasn't set it in UI

print("\n--- Test 2: Reconfigure with None ---")
if client.api_key != settings_key:
    print(f"Keys differ ('{client.api_key}' != '{settings_key}'). Reconfiguring...")
    client.configure(settings_key)

print(f"Client API Key after reconfigure: {client.api_key}")
if not client.api_key:
    print("FAILURE: API Key was clobbered!")
else:
    print("SUCCESS: API Key preserved.")
