"""
Gemini API Client for DaVinci Assistant.
Wraps the google-generativeai library.
"""
import os
try:
    import google.generativeai as genai
    HAS_GEMINI = True
except ImportError:
    HAS_GEMINI = False
    
from typing import Optional, List

class GeminiClient:
    """
    Client for interacting with Google's Gemini API.
    """
    
    def __init__(self, api_key: Optional[str] = None):
        self.api_key = api_key or os.environ.get("GEMINI_API_KEY")
        self.model = None
        self._is_configured = False
        self._available_models: List[str] = []
        self._current_model_name: str = ""
        
        if self.api_key:
            self.configure(self.api_key)
            
    def configure(self, api_key: str):
        """Configure the client with an API key"""
        print(f"DEBUG: Configuring Gemini with key: {api_key[:4]}...***")
        if not HAS_GEMINI:
            print("DEBUG: google-generativeai package not installed.")
            self._is_configured = False
            return
            
        self.api_key = api_key
        try:
            genai.configure(api_key=self.api_key)
            
            # Dynamic Model Discovery
            print("DEBUG: Discovering available models...")
            self._available_models = []
            try:
                for m in genai.list_models():
                    if 'generateContent' in m.supported_generation_methods:
                        self._available_models.append(m.name)
                        print(f"DEBUG: Found model: {m.name}")
            except Exception as list_err:
                print(f"DEBUG: Failed to list models: {list_err}")
                
            # Selection Strategy
            preferred_order = [
                'models/gemini-1.5-flash',
                'models/gemini-1.5-pro',
                'models/gemini-2.0-flash-exp',
                'models/gemini-1.0-pro',
                'models/gemini-pro'
            ]
            
            selected_model_name = None
            for pref in preferred_order:
                if pref in self._available_models:
                    selected_model_name = pref
                    break
            
            # Fallback if discovery failed or no match
            if not selected_model_name:
                if self._available_models:
                     selected_model_name = self._available_models[0]
                else:
                     selected_model_name = 'gemini-1.5-flash' # More robust default than legacy gemini-pro
            
            print(f"DEBUG: Selected model: {selected_model_name}")
            self.model = genai.GenerativeModel(selected_model_name)
            self._current_model_name = selected_model_name
            self._is_configured = True
            print(f"DEBUG: Gemini configured successfully using model: '{selected_model_name}'")
        except Exception as e:
            print(f"DEBUG: Failed to configure Gemini: {e}")
            self._is_configured = False
    
    def get_available_models(self) -> List[str]:
        """Return list of available model names"""
        return self._available_models
    
    def get_current_model(self) -> str:
        """Return the current model name"""
        return self._current_model_name
    
    def set_model(self, model_name: str) -> bool:
        """Switch to a specific model. Returns True on success."""
        if not HAS_GEMINI or not self._is_configured:
            return False
        
        # Allow partial matching (e.g., 'gemini-1.5-pro' matches 'models/gemini-1.5-pro')
        target = None
        for m in self._available_models:
            if model_name in m or m.endswith(model_name):
                target = m
                break
        
        if target:
            try:
                self.model = genai.GenerativeModel(target)
                self._current_model_name = target
                print(f"DEBUG: Switched to model: {target}")
                return True
            except Exception as e:
                print(f"DEBUG: Failed to switch model: {e}")
                return False
        return False
            
    def generate_response(self, prompt: str, **kwargs) -> str:
        """
        Generate a response from Gemini.
        """
        if not self._is_configured or not self.model:
            print("DEBUG: Gemini not configured, skipping generation.")
            return "⚠️ Gemini API key not configured. Please set it in Settings."
            
        try:
            print("DEBUG: Sending request to Gemini...")
            response = self.model.generate_content(prompt, **kwargs)
            print("DEBUG: Gemini response received.")
            return response.text
        except Exception as e:
            print(f"DEBUG: Gemini API Error: {e}")
            return f"❌ Gemini API Error: {str(e)}"

    def is_ready(self) -> bool:
        return self._is_configured
