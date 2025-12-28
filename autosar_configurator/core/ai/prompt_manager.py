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
            f"You are an expert in AUTOSAR BSW configuration and EB Tresos-compatible template generation. "
            f"You have deep knowledge across various modules like Adc, Mcu, Port, Can, Crypto, etc.\n"
            f"The user is CURRENTLY working on the '{module_name}' module, but you should assist with ANY BSW-related request.\n"
            "Your goal is to assist the user in configuring modules and writing C templates.\n"
            "The system uses an enhanced Template Engine with the following capabilities:\n"
            "- Recursive tags: Supports nested {% for %} and {% if %} up to any depth.\n"
            "- Logical Operators: Supports 'not', 'in', '==', '!=', 'is None', 'is not None'.\n"
            "- Loop Metadata: Inside for-loops, 'loop.last', 'loop.first', 'loop.index' are available.\n"
            "- Filters: Supports '| upper', '| lower', '| length'.\n"
            "Be concise and technical. Respond in Chinese (Simplified)."
        )

    def build_general_prompt(self, user_query: str) -> str:
        """Construct prompt for general queries"""
        system_context = self._get_system_context()
        return f"{system_context}\n\nUser Question: {user_query}"

    def build_template_generation_prompt(self, request: str, module_def: Optional[str] = None) -> str:
        """Construct prompt specifically for generating templates"""
        system_context = self._get_system_context()
        def_info = f"\nModule Structure Context: {module_def}" if module_def else ""
        
        return (
            f"{system_context}\n\n"
            f"Task: Generate a C template (.tpl) based on the following user request.\n"
            f"User Request: {request}\n"
            f"{def_info}\n\n"
            "Rules for template generation:\n"
            "1. Use standard C syntax for output.\n"
            "2. Use {% for container in containers %} to iterate through module containers.\n"
            "3. Use container.sub_containers to access nested child configurations.\n"
            "4. Use container.parameter_values[ParamName].value to get parameter values.\n"
            "5. Always use {% if not loop.last %},{% endif %} for array item separation.\n"
            "6. Wrap everything in a standard C boilerplate with includes and header guards if requested."
        )

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
