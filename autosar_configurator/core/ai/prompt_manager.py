"""
Prompt Manager for DaVinci Assistant.
Responsible for constructing context-aware prompts for the AI.
"""
from typing import Optional, List
from ..config_manager import ConfigurationManager
from ..model.definition_model import EcucContainerDef
from ..model.configuration_model import EcucContainerValue

class PromptManager:
    """
    Constructs prompts with context from the application state.
    """
    
    def __init__(self, config_manager: Optional[ConfigurationManager]):
        self.config_manager = config_manager
        
    def _get_system_context(self) -> str:
        """Return general system context"""
        module_name = "General"
        if self.config_manager and self.config_manager.module_def:
            module_name = self.config_manager.module_def.short_name
            
        return (
            f"You are an expert in AUTOSAR BSW configuration, specifically for the '{module_name}' module.\n"
            "Your goal is to assist the user in configuring the module correctly according to the ARXML definition.\n"
            "Be concise and technical.\n"
            "IMPORTANT: Please respond to all questions and instructions in Chinese (Simplified)."
        )

    def build_general_prompt(self, user_query: str) -> str:
        """Construct prompt for general queries"""
        system_context = self._get_system_context()
        return f"{system_context}\n\nUser Question: {user_query}"

    def build_explain_prompt(self, container_def: EcucContainerDef) -> str:
        """Construct prompt to explain a container"""
        system_context = self._get_system_context()
        
        desc = container_def.description or "No description available in ARXML."
        multiplicity = container_def.multiplicity_str
        
        # Collect sub-container names for context
        sub_containers = ", ".join([sc.short_name for sc in container_def.sub_containers.values()])
        
        # Collect parameters for context
        parameters = ", ".join([p.short_name for p in container_def.parameters.values()])
        
        return (
            f"{system_context}\n\n"
            f"Task: Explain the container '{container_def.short_name}'.\n\n"
            f"Context from ARXML:\n"
            f"- Description: {desc}\n"
            f"- Multiplicity: {multiplicity}\n"
            f"- Contains Sub-containers: {sub_containers}\n"
            f"- Contains Parameters: {parameters}\n\n"
            "Please explain what this container is used for and typical configuration values."
        )

    def build_fix_error_prompt(self, error_msg: str, context_element_name: str) -> str:
        """Construct prompt to help fix a validation error"""
        system_context = self._get_system_context()
        return (
            f"{system_context}\n\n"
            f"Task: Suggest a fix for the following validation error.\n\n"
            f"Error Message: {error_msg}\n"
            f"Element: {context_element_name}\n\n"
            "Explain why this error occurred and how to resolve it."
        )
