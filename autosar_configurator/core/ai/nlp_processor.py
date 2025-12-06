"""
Natural Language Processor for DaVinci Assistant
Parses text commands and executes application actions.
"""
import re
from typing import Optional
from PySide6.QtGui import QUndoStack

from ..config_manager import ConfigurationManager
from ..model.definition_model import EcucContainerDef
from ...ui.commands import CreateContainerCommand

class NaturalLanguageProcessor:
    """
    Translates natural language into application commands.
    Currently uses simple regex matching for prototype.
    """
    
    def __init__(self, config_manager: ConfigurationManager, undo_stack: QUndoStack):
        self.config_manager = config_manager
        self.undo_stack = undo_stack
        
    def process_message(self, text: str) -> str:
        """
        Process a user message and return a response string.
        Executes commands if intent is detected.
        """
        text = text.strip()
        
        # 1. Intent: Create Container
        # Pattern: "Create <ContainerName>" or "Add <ContainerName>"
        create_match = re.search(r"(?:Create|Add)\s+(\w+)", text, re.IGNORECASE)
        if create_match:
            container_name = create_match.group(1)
            return self._handle_create_intent(container_name)
            
        # 2. Intent: Explain
        # Pattern: "Explain <ContainerName>"
        explain_match = re.search(r"Explain\s+(\w+)", text, re.IGNORECASE)
        if explain_match:
            container_name = explain_match.group(1)
            return self._handle_explain_intent(container_name)
            
        # Default response
        return "I didn't understand that command. Try 'Create AdcHwUnit' or 'Explain AdcConfigSet'."

    def _handle_create_intent(self, container_short_name: str) -> str:
        """Handle creation intent"""
        # Find definition
        # We need to search all available container definitions in the module
        # Note: This finds the FIRST match.
        
        target_def: Optional[EcucContainerDef] = None
        
        # Search in top-level containers
        for c_def in self.config_manager.module_def.containers.values():
            if c_def.short_name.lower() == container_short_name.lower():
                target_def = c_def
                break
            # Search in sub-containers (recursive search ideally, but 1 level for now)
            for sub_def in c_def.sub_containers.values():
                if sub_def.short_name.lower() == container_short_name.lower():
                    target_def = sub_def
                    break
        
        if not target_def:
            return f"❌ Could not find container definition '{container_short_name}'."
            
        # Create it
        # Note: Parent handling is tricky. For now, if it's a sub-container, 
        # we need a selected parent. Since this processor is decoupled from UI selection for now,
        # we will only support Top-Level or assume Root.
        # TODO: Pass 'context' (selected instance) to process_message.
        
        # For prototype: Only allow top-level creation or warn
        if target_def.short_name in self.config_manager.module_def.containers:
            # It's a top level container
            instance_name = self.config_manager._generate_instance_name(target_def)
            command = CreateContainerCommand(self.config_manager, target_def, None, instance_name)
            self.undo_stack.push(command)
            return f"✅ Created **{instance_name}**."
        else:
            return f"⚠️ '{target_def.short_name}' is a sub-container. Please select a parent first (Context awarness pending)."

    def _handle_explain_intent(self, container_name: str) -> str:
        """Handle explain intent"""
        # Search definition same as above
        target_def: Optional[EcucContainerDef] = None
        for c_def in self.config_manager.module_def.containers.values():
            if c_def.short_name.lower() == container_name.lower():
                target_def = c_def
                break
            for sub_def in c_def.sub_containers.values():
                if sub_def.short_name.lower() == container_name.lower():
                    target_def = sub_def
                    break
                    
        if not target_def:
            return f"Unknown container '{container_name}'."
            
        desc = target_def.description or "No description available."
        mult = target_def.multiplicity_str
        return f"**{target_def.short_name}** [{mult}]\n\n{desc}"
