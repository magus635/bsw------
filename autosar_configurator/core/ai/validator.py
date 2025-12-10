"""
Intelligent Validation Module
Uses RAG to validate the current AUTOSAR configuration against chip manuals and constraints.
"""
from typing import List, Optional
import json

from ..config_manager import ConfigurationManager
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from .knowledge_base import KnowledgeBase
from .gemini_client import GeminiClient

class IntelligentValidator:
    """
    Validates AUTOSAR configuration using AI and RAG Knowledge Base.
    """
    
    def __init__(self, knowledge_base: KnowledgeBase, gemini_client: GeminiClient):
        self.knowledge_base = knowledge_base
        self.gemini_client = gemini_client
        
    def validate(self, config_manager: ConfigurationManager) -> str:
        """
        Perform intelligent validation on the current configuration module.
        """
        snapshot = self._create_snapshot(config_manager)
        return self._perform_validation(snapshot, config_manager.module_def.short_name)

    def validate_project(self, project) -> str:
        """
        Perform intelligent validation on the entire project (all modules).
        """
        if not self.knowledge_base.is_ready:
            return "❌ Knowledge Base is not ready. Please configure API Key and add documents."
            
        # 1. Create Combined Snapshot
        snapshots = []
        module_names = []
        
        for module_name, manager in project.module_managers.items():
            mod_snapshot = self._create_snapshot(manager)
            if mod_snapshot:
                snapshots.append(mod_snapshot)
                module_names.append(module_name)
        
        if not snapshots:
            return "⚠️ Project is empty. Nothing to validate."
            
        combined_snapshot = "\n\n".join(snapshots)
        context_name = f"Project Modules: {', '.join(module_names)}"
        
        return self._perform_validation(combined_snapshot, context_name)

    def _perform_validation(self, snapshot: str, context_name: str) -> str:
        """Helper to run the actual AI validation"""
        if not self.knowledge_base.is_ready:
            return "❌ Knowledge Base is not ready. Please configure API Key and add documents."
            
        if not snapshot:
            return "⚠️ Configuration is empty. Nothing to validate."
            
        print(f"DEBUG: Validating {context_name}...\nSnapshot size: {len(snapshot)} chars")
        
        # 2. Retrieve Relevant Constraints
        # Broad search for all modules involved
        search_query = f"limitations constraints dependencies for {context_name}"
        rag_context = self.knowledge_base.search(search_query, top_k=10) # Increase top_k for project
        
        context_str = ""
        if rag_context:
            context_str = "\nRelevant Documentation:\n"
            for doc, score in rag_context:
                context_str += f"- {doc.strip()[:600]}...\n" 
        
        # 3. Ask AI to Validate
        prompt = (
            f"You are a strict Compliance Auditor for AUTOSAR configurations.\n"
            f"Your goal is to cross-check the 'Current Configuration Snapshot' against the 'Reference Documentation'.\n\n"
            
            f"=== Reference Documentation (Ground Truth) ===\n"
            f"{context_str}\n\n"
            
            f"=== Current Configuration Snapshot (To Audit) ===\n"
            f"```yaml\n{snapshot}\n```\n\n"
            
            f"=== Audit Instructions ===\n"
            f"1. Compare parameters against limits in the Documentation.\n"
            f"2. Check for Cross-Module Consistency (e.g. if ADC uses a clock, is MCU clock configured?).\n"
            f"3. REPORT ONLY DETECTED VIOLATIONS. Group by Module.\n"
            f"4. Format: '❌ [Module] [Parameter] = [Value] violates ...'\n"
            f"5. If compliant, return '✅ Configuration is compliant.'\n"
        )
        
        print("DEBUG: Sending validation prompt to Gemini...")
        return self.gemini_client.generate_response(
            prompt, 
            generation_config={"temperature": 0.0}
        )

    def _create_snapshot(self, config_manager: ConfigurationManager) -> str:
        """
        Create a textual representation of the current configuration.
        """
        config = config_manager.configuration
        if not config.containers:
            return ""
            
        snapshot_lines = []
        snapshot_lines.append(f"Module: {config.short_name}")
        
        for container in config.containers:
            self._serialize_container(container, snapshot_lines, indent=2)
            
        return "\n".join(snapshot_lines)
        
    def _serialize_container(self, container: EcucContainerValue, lines: List[str], indent: int):
        """Recursively serialize container to lines"""
        prefix = " " * indent
        lines.append(f"{prefix}- Container: {container.short_name} ({container.definition_ref})")
        
        # Parameters
        for name, param_val in container.parameter_values.items():
            lines.append(f"{prefix}  - {name}: {param_val.value}")
            
        # References
        for name, ref_val in container.reference_values.items():
            lines.append(f"{prefix}  - {name} -> {ref_val.value_ref}")
            
        # Sub-containers
        for sub in container.sub_containers:
            self._serialize_container(sub, lines, indent + 2)
