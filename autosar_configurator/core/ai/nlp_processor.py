"""
Natural Language Processor for DaVinci Assistant
Parses text commands and executes application actions.
"""
import re
from typing import Optional
from PySide6.QtGui import QUndoStack

from ..config_manager import ConfigurationManager
from ..model.definition_model import EcucContainerDef
from ...ui.commands import CreateContainerCommand, SetParameterCommand
from .gemini_client import GeminiClient
from .prompt_manager import PromptManager
from .knowledge_base import KnowledgeBase
from .validator import IntelligentValidator
import os

from ..model.configuration_model import EcucContainerValue

class NaturalLanguageProcessor:
    """
    Core NLP engine for processing user intents.
    """
    
    def __init__(self, api_key: str = None, config_manager=None, undo_stack: Optional[QUndoStack] = None, action_handler: Optional[callable] = None):
        self.gemini_client = GeminiClient(api_key)
        self.knowledge_base = KnowledgeBase(api_key)
        self.validator = IntelligentValidator(self.knowledge_base, self.gemini_client)
        self.config_manager = config_manager # Reference to main config data
        self.project = None # Reference to active project (for multi-module validation)
        self.prompt_manager = PromptManager(self.config_manager)
        self.undo_stack = undo_stack # Keep undo_stack as it's used later
        
        # Callback for executing actions (e.g. create_container)
        self.action_handler = action_handler
        
        # Try to load cached knowledge base first
        if self.knowledge_base.is_ready:
            loaded = self.knowledge_base.load_from_disk()
            if loaded and self.knowledge_base.documents:
                print(f"DEBUG: Restored {len(self.knowledge_base.documents)} documents from cache")
            else:
                # Fallback: Auto-load sample data if exists and cache was empty
                sample_path = "datasheets/sample_chip_manual.txt"
                if os.path.exists(sample_path):
                    print(f"DEBUG: NLP loading knowledge from {sample_path}")
                    try:
                        self.knowledge_base.load_document(sample_path)
                        # Save to cache for next time
                        self.knowledge_base.save_to_disk()
                    except Exception as e:
                        print(f"DEBUG: Failed to load sample knowledge: {e}")
                
    def process_message(self, text: str, context_instance: Optional[EcucContainerValue] = None) -> str:
        """
        Process a user message and return a response string.
        Strategy: Check simple regex intents first, then fallback to LLM.
        """
        text = text.strip()
        print(f"DEBUG: NLP processing: '{text}' with context: {context_instance}")
        
        # 0a. Command: /model
        if text.startswith('/model'):
            return self._handle_model_command(text)
        
        # 0b. Greeting: Hi/Hello
        if re.search(r"^(hi|hello|hey|你好|您好)\b", text, re.IGNORECASE):
            return "您好！我是您的 AI 助手。请问有什么关于 AUTOSAR 配置的问题我可以帮您？"

        # 1. Intent: Create Container
        # Pattern: "Create <ContainerName>" or "Add <ContainerName>"
        create_match = re.search(r"(?:Create|Add)\s+(\w+)", text, re.IGNORECASE)
        if create_match:
            if not self.config_manager:
                return "⚠️ 请先加载项目或 DEF 文件以创建容器。"
            container_name = create_match.group(1)
            return self._handle_create_intent(container_name, context_instance)
            
        # 2. Intent: Set Parameter
        # Pattern: "Set <ParamName> to <Value>"
        set_match = re.search(r"Set\s+(\w+)\s+to\s+(.+)", text, re.IGNORECASE)
        if set_match:
            if not self.config_manager:
                return "⚠️ 请先加载项目以设置参数。"
            param_name = set_match.group(1)
            value = set_match.group(2)
            return self._handle_set_intent(param_name, value, context_instance)
            
        # 3. Intent: Explain (Hybrid)
        # Pattern: "Explain <ContainerName>"
        explain_match = re.search(r"Explain\s+(\w+)", text, re.IGNORECASE)
        if explain_match:
            container_name = explain_match.group(1)
            
            # 1. Try Local/Hybrid if Project is Loaded
            if self.config_manager:
                # If LLM is ready, use it for richer explanation
                if self.gemini_client.is_ready():
                     return self._handle_gemini_explain(container_name)
                else:
                     return self._handle_explain_intent(container_name)
            
            # 2. If No Project, but LLM Ready -> General Question
            elif self.gemini_client.is_ready():
                 return self._handle_gemini_general(f"Explain {container_name} in AUTOSAR context.")
                 
            # 3. No Project, No LLM -> Error
            else:
                 return "⚠️ 请先加载项目以获取解释，或配置 API Key 以使用云端知识库。"

        # 5. Intent: Save
        if re.search(r"^(save|保存)", text, re.IGNORECASE):
            if self.action_handler:
                self.action_handler("save")
                return "✅ 已触发保存。"
            return "⚠️无法执行保存。"

        # 6. Intent: Generate Code
        if re.search(r"^(generate|build|生成代码)", text, re.IGNORECASE):
            if self.action_handler:
                self.action_handler("generate")
                return "✅ 已触发代码生成。"
            return "⚠️无法执行代码生成。"

        # 7. Intent: Single Parameter Validation
        # Pattern: "check <ParamName>" or "检查<ParamName>" or "validate <ParamName>"
        # Allow optional space between keyword and parameter name for Chinese input
        single_check_match = re.search(r"^(?:check|检查|validate|验证)\s*([A-Za-z_][A-Za-z0-9_]*)$", text, re.IGNORECASE)
        if single_check_match:
            param_name = single_check_match.group(1)
            print(f"DEBUG: Single param validation triggered for: '{param_name}'")
            return self._handle_single_param_validation(param_name, context_instance)

        # 8. Intent: Full Configuration Validation
        # Allow optional '@' prefix so users can say "@验证配置"
        if re.search(r"^@?\s*(validate|check|audit|verify|检查配置|验证配置)", text, re.IGNORECASE):
            # Prioritize Project-Wide Validation if project is loaded
            if self.project:
                return self.validator.validate_project(self.project)
            elif self.config_manager:
                return self.validator.validate(self.config_manager)
            return "⚠️ 无法验证：未连接 Project 或 ConfigurationManager。"
        
        
        # 3. Fallback to Gemini for general questions / RAG
        # Check for explicit RAG trigger '@'
        use_rag = False
        if text.strip().startswith("@"):
            use_rag = True
            text = text.strip()[1:].strip() # Remove '@'
            
        if self.gemini_client.is_ready():
            return self._handle_gemini_chat(text, use_rag=use_rag)
            
        # Default response
        return (
            "⚠️ 我不太明白您的指令。\n"
            "这可能是因为 Gemini API 未配置或 `google-generativeai` 包未安装。\n\n"
            "您可以尝试使用本地指令，例如：\n"
            "• Create AdcHwUnit\n"
            "• Explain AdcHwUnit\n"
            "• Set AdcClock to 80000\n"
            "• @查找资料 (使用知识库)"
        )

    def _handle_gemini_chat(self, text: str, use_rag: bool = False) -> str:
        """Ask Gemini a question, optionally using RAG context"""
        
        context_str = ""
        if use_rag and self.knowledge_base.is_ready:
            print(f"DEBUG: RAG Search for: '{text}'")
            results = self.knowledge_base.search(text)
            if results:
                context_str = "\n[Retrieved Knowledge from Knowledge Base]:\n"
                for doc, score in results:
                    # Truncate doc content for prompt size management
                    context_str += f"- {doc.strip()[:300]}...\n"
                context_str += "\n[End of Knowledge Base]\n"
                context_str += "Note: Please prioritize the specific knowledge provided above if it is relevant to the user's question.\n"
            else:
                context_str = "\n[Knowledge Base]: No relevant documents found.\n"
        
        full_text = f"{context_str}\nUser Question: {text}"
        prompt = self.prompt_manager.build_general_prompt(full_text)
        return self.gemini_client.generate_response(prompt)

    def _handle_gemini_explain(self, container_name: str) -> str:
        """Use Gemini to explain a container, providing definition context"""
        # Find def first to get standard description
        target_def = self._find_container_def(container_name)
        if not target_def:
             return f"I don't see a container named '{container_name}' in this module."
             
        prompt = self.prompt_manager.build_explain_prompt(target_def)
        return self.gemini_client.generate_response(prompt)
        
    def _find_container_def(self, name: str) -> Optional[EcucContainerDef]:
        """Helper to find container definition"""
        for c_def in self.config_manager.module_def.containers.values():
            if c_def.short_name.lower() == name.lower():
                return c_def
            for sub_def in c_def.sub_containers.values():
                if sub_def.short_name.lower() == name.lower():
                    return sub_def
        return None

    def _handle_create_intent(self, container_short_name: str, context_instance: Optional[EcucContainerValue] = None) -> str:
        """
        Handle creation intent, optionally using context (selected instance) as parent.
        """
        target_def: Optional[EcucContainerDef] = None
        parent_instance: Optional[EcucContainerValue] = None
        
        # Strategy 1: Check if it's a valid sub-container of the current context
        if context_instance:
            context_def = context_instance.definition
            # Check sub-containers of context
            for sub_def in context_def.sub_containers.values():
                if sub_def.short_name.lower() == container_short_name.lower():
                    target_def = sub_def
                    parent_instance = context_instance
                    break
        
        # Strategy 2: If no context match, search top-level containers
        if not target_def:
            for c_def in self.config_manager.module_def.containers.values():
                if c_def.short_name.lower() == container_short_name.lower():
                    target_def = c_def
                    # Top-level, so no parent
                    parent_instance = None 
                    break
        
        # Strategy 3: Search all container definitions (Global Search)
        # Only if we haven't found it yet. If we find it here, it implies it's a sub-container
        # but we aren't in the right context multiple levels down or it's just somewhere else.
        if not target_def:
             # Very simple search for now - just 2 levels deep as per original code
             # TODO: improve global search map
             for c_def in self.config_manager.module_def.containers.values():
                for sub_def in c_def.sub_containers.values():
                    if sub_def.short_name.lower() == container_short_name.lower():
                        target_def = sub_def
                        break
                if target_def: break
        
        if not target_def:
            return f"❌ 找不到容器定义 '{container_short_name}'。"

        # Validation: If it's a sub-container but we don't have a parent
        # Check if it IS a top-level container (by checking existence in module containers)
        is_top_level = target_def.short_name in self.config_manager.module_def.containers
        
        if not is_top_level and not parent_instance:
             # We found the definition, but it's a sub-container and we don't have a valid parent context selected
             # Try to see if there is ONLY ONE instance of the parent? No, that's assuming too much.
             return f"⚠️ '{target_def.short_name}' 是一个子容器。请先选择一个有效的父容器 ('{target_def.parent.short_name}' 实例)。"

        # Execute
        instance_name = self.config_manager._generate_instance_name(target_def, parent_instance)
        command = CreateContainerCommand(self.config_manager, target_def, parent_instance, instance_name)
        self.undo_stack.push(command)
        
        location_str = f" 在 **{parent_instance.short_name}** 下" if parent_instance else " 在根节点"
        return f"✅ 已创建 **{instance_name}**{location_str}。"

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
             return f"❌ 找不到容器定义 '{container_name}'。"
             
        desc = target_def.description or "无描述信息。"
        return (
            f"**{target_def.short_name}**\n"
            f"📄 描述: {desc}\n"
            f"🔢 重复性: {target_def.multiplicity_str}"
        )

    def _handle_set_intent(self, param_name: str, value: str, instance: Optional[EcucContainerValue]) -> str:
        """Handle Set Parameter intent"""
        if not instance:
             return "⚠️ 请先在树状图中选择一个容器实例，然后再设置参数。"
             
        container_def = instance.definition
        param_def = container_def.parameters.get(param_name)
        
        # Try finding case-insensitive if exact match fails
        if not param_def:
            for p_name, p_def in container_def.parameters.items():
                if p_name.lower() == param_name.lower():
                    param_def = p_def
                    param_name = p_name # Correct the name
                    break
        
        if not param_def:
            return f"❌ 在 '{instance.short_name}' 中找不到参数 '{param_name}' (定义: {container_def.short_name})。"
            
        # Context-aware type conversion
        from ..model.definition_model import EcucParameterType
        
        typed_value = value
        
        try:
            if param_def.param_type == EcucParameterType.INTEGER:
                if value.startswith("0x"):
                    typed_value = int(value, 16)
                else:
                    typed_value = int(value)
                    
            elif param_def.param_type == EcucParameterType.FLOAT:
                typed_value = float(value)
                
            elif param_def.param_type == EcucParameterType.BOOLEAN:
                lower_val = value.lower()
                if lower_val in ["true", "1", "yes", "on"]:
                    typed_value = True
                elif lower_val in ["false", "0", "no", "off"]:
                    typed_value = False
                else:
                    raise ValueError(f"无效的布尔值: '{value}'")
                    
            elif param_def.param_type == EcucParameterType.ENUMERATION:
                # Basic validation (optional but good)
                if param_def.literals:
                    # Case-insensitive check
                    found_literal = None
                    for lit in param_def.literals:
                        if lit.lower() == value.lower():
                            found_literal = lit
                            break
                    
                    if found_literal:
                        typed_value = found_literal
                    else:
                        # Depending on strictness, we might warn or fail. 
                        # For now, let's just warn but set it (some tools allow lax enum setting)
                        # or better, fail if we want robustness.
                        # Let's start with strict for listed literals.
                         raise ValueError(f"Invalid enum value '{value}'. Allowed: {', '.join(param_def.literals)}")
                         
            # String and others kept as is
            
            command = SetParameterCommand(self.config_manager, instance, param_name, typed_value)
            self.undo_stack.push(command)
            return f"✅ 已设置 **{param_name}** 为 **{typed_value}**。"
            
        except ValueError as e:
            return f"❌ Invalid format for {param_def.param_type.name}: {str(e)}"
        except Exception as e:
            return f"❌ Failed to set parameter: {str(e)}"
    
    def _handle_model_command(self, text: str) -> str:
        """Handle /model command for viewing and switching models"""
        parts = text.split()
        
        # /model - show current and available models
        if len(parts) == 1:
            current = self.gemini_client.get_current_model()
            available = self.gemini_client.get_available_models()
            
            if not available:
                return "⚠️ 无法获取模型列表。请检查 API Key 是否正确配置。"
            
            # Format model list (show short names)
            model_list = []
            for m in available:
                short_name = m.replace('models/', '')
                marker = "✅" if m == current else "  "
                model_list.append(f"{marker} {short_name}")
            
            return f"**当前模型**: {current.replace('models/', '')}\n\n**可用模型**:\n" + "\n".join(model_list) + "\n\n使用 `/model <模型名>` 切换模型。"
        
        # /model <name> - switch to specified model
        else:
            target_name = parts[1]
            if self.gemini_client.set_model(target_name):
                new_model = self.gemini_client.get_current_model().replace('models/', '')
                return f"✅ 已切换到模型: **{new_model}**"
            else:
                available = [m.replace('models/', '') for m in self.gemini_client.get_available_models()]
                return f"❌ 模型 '{target_name}' 不可用。\n可用模型: {', '.join(available[:5])}"
    
    def _handle_single_param_validation(self, param_name: str, context_instance: Optional[EcucContainerValue]) -> str:
        """
        Handle validation of a single parameter.
        
        Args:
            param_name: Name of the parameter to validate
            context_instance: The currently selected container instance
            
        Returns:
            Validation result string
        """
        if not self.config_manager:
            return "⚠️ 请先加载项目或模块配置。"
        
        # Strategy 1: If context_instance is provided, search there first
        if context_instance:
            # Check if parameter exists in this instance
            param_value = None
            for pname, pval in context_instance.parameter_values.items():
                if pname.lower() == param_name.lower():
                    param_name = pname  # Use correct case
                    param_value = pval.value
                    break
            
            if param_value is not None:
                return self.validator.validate_parameter(
                    param_name,
                    param_value,
                    context_instance.short_name,
                    self.config_manager
                )
        
        # Strategy 2: Search all containers for the parameter
        found_params = []
        
        def search_container(container: EcucContainerValue):
            for pname, pval in container.parameter_values.items():
                if pname.lower() == param_name.lower():
                    found_params.append((container, pname, pval.value))
            for sub in container.sub_containers:
                search_container(sub)
        
        for container in self.config_manager.configuration.containers:
            search_container(container)
        if not found_params:
            return f"❌ 未找到参数 '{param_name}'。请确保参数名称正确。"
        
        print(f"DEBUG: Found {len(found_params)} instance(s) of '{param_name}'")
        
        if len(found_params) == 1:
            container, actual_name, value = found_params[0]
            print(f"DEBUG: Validating single instance: {container.short_name}.{actual_name} = {value}")
            return self.validator.validate_parameter(
                actual_name,
                value,
                container.short_name,
                self.config_manager
            )
        
        # Multiple instances found
        results = [f"找到 {len(found_params)} 个 '{param_name}' 实例，逐个检查：\n"]
        for container, actual_name, value in found_params:
            result = self.validator.validate_parameter(
                actual_name,
                value,
                container.short_name,
                self.config_manager
            )
            results.append(f"\n**{container.short_name}.{actual_name}** = {value}\n{result}\n")
        
        return "\n".join(results)
