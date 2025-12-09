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
    
from typing import Optional

class GeminiClient:
    """
    Client for interacting with Google's Gemini API.
    """
    
    def __init__(self, api_key: Optional[str] = None):
        self.api_key = api_key or os.environ.get("GEMINI_API_KEY")
        self.model = None
        self._is_configured = False
        
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
            available_models = []
            try:
                for m in genai.list_models():
                    if 'generateContent' in m.supported_generation_methods:
                        available_models.append(m.name)
                        print(f"DEBUG: Found model: {m.name}")
            except Exception as list_err:
                print(f"DEBUG: Failed to list models: {list_err}")
                
            # Selection Strategy
            preferred_order = [
                'models/gemini-1.5-flash',
                'models/gemini-1.5-pro',
                'models/gemini-1.0-pro',
                'models/gemini-pro'
            ]
            
            selected_model_name = None
            for pref in preferred_order:
                if pref in available_models:
                    selected_model_name = pref
                    break
            
            # Fallback if discovery failed or no match
            if not selected_model_name:
                if available_models:
                     selected_model_name = available_models[0]
                else:
                     selected_model_name = 'gemini-pro' # Hope for best
            
            print(f"DEBUG: Selected model: {selected_model_name}")
            self.model = genai.GenerativeModel(selected_model_name)
            self._is_configured = True
            print(f"DEBUG: Gemini configured successfully using model: '{selected_model_name}'")
        except Exception as e:
            print(f"DEBUG: Failed to configure Gemini: {e}")
            self._is_configured = False
            
    def generate_response(self, prompt: str) -> str:
        """
        Generate a response from Gemini.
        """
        if not self._is_configured or not self.model:
            print("DEBUG: Gemini not configured, skipping generation.")
            return "⚠️ Gemini API key not configured. Please set it in Settings."
            
        try:
            print("DEBUG: Sending request to Gemini...")
            response = self.model.generate_content(prompt)
            print("DEBUG: Gemini response received.")
            return response.text
        except Exception as e:
            print(f"DEBUG: Gemini API Error: {e}")
            return f"❌ Gemini API Error: {str(e)}"

    def is_ready(self) -> bool:
        return self._is_configured
