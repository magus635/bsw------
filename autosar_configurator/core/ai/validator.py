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
    
    def validate_parameter(self, param_name: str, param_value, container_name: str, config_manager: ConfigurationManager) -> str:
        """
        Validate a single parameter against the knowledge base.
        
        Args:
            param_name: Name of the parameter to validate
            param_value: Current value of the parameter
            container_name: Name of the container containing the parameter
            config_manager: The configuration manager
            
        Returns:
            Validation result string
        """
        if not self.knowledge_base.is_ready:
            return "❌ Knowledge Base 未就绪。请配置 API Key 并添加文档。"
        
        module_name = config_manager.module_def.short_name if config_manager.module_def else "Unknown"
        
        # Search for constraints related to this specific parameter
        search_queries = [
            f"{param_name} constraints limits range",
            f"{container_name} {param_name} configuration",
            f"{module_name} {param_name} valid values"
        ]
        
        # Combine results from multiple queries
        all_context = []
        for query in search_queries:
            results = self.knowledge_base.search(query, top_k=3)
            if results:
                for doc, score in results:
                    if doc not in [c[0] for c in all_context]:
                        all_context.append((doc, score))
        
        context_str = ""
        if all_context:
            context_str = "\n相关文档约束:\n"
            for doc, score in all_context[:5]:  # Limit to top 5
                context_str += f"- {doc.strip()[:400]}...\n"
        else:
            context_str = "\n[未找到相关文档约束]\n"
        
        # Build validation prompt
        prompt = (
            f"你是一个 AUTOSAR 配置审计专家。\n"
            f"请检查以下参数值是否符合文档中的约束：\n\n"
            
            f"=== 待检查参数 ===\n"
            f"模块: {module_name}\n"
            f"容器: {container_name}\n"
            f"参数: {param_name}\n"
            f"当前值: {param_value}\n\n"
            
            f"=== 参考文档 ===\n"
            f"{context_str}\n\n"
            
            f"=== 检查要求 ===\n"
            f"1. 检查参数值是否在允许的范围内\n"
            f"2. 检查是否有任何特殊限制或依赖条件\n"
            f"3. 如果发现问题，明确指出违规点和建议值\n"
            f"4. 如果没有问题，说明原因\n\n"
            
            f"请用中文回答，格式简洁明了。"
        )
        
        print(f"DEBUG: Validating parameter {param_name}={param_value}")
        return self.gemini_client.generate_response(
            prompt,
            generation_config={"temperature": 0.0}
        )
