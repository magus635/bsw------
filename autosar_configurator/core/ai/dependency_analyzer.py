"""
AI-Powered Cross-Module Dependency Analyzer

This module uses AI to analyze AUTOSAR BSW module configurations and
extract potential cross-module parameter dependencies.

Workflow:
1. Extract all parameter information from project modules
2. Send to AI to infer potential dependencies
3. Generate dependencies.md for human review
"""
from typing import Dict, List, Optional, Any
from pathlib import Path
import re

from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


class DependencyAnalyzer:
    """AI-powered cross-module dependency analyzer"""
    
    def __init__(self, gemini_client=None):
        """
        Initialize the analyzer.
        
        Args:
            gemini_client: Optional GeminiClient for AI analysis
        """
        self.gemini_client = gemini_client
        self.extracted_params: Dict[str, List[Dict]] = {}  # module_name -> params
    
    def extract_project_parameters(self, project) -> Dict[str, List[Dict]]:
        """
        Extract all parameter information from a project.
        
        Args:
            project: ProjectWorkspace instance
            
        Returns:
            Dict mapping module name to list of parameter info dicts
        """
        self.extracted_params = {}
        self.cross_module_refs = []  # Store cross-module references from definitions
        
        if not project or not hasattr(project, 'module_managers'):
            return self.extracted_params
        
        for module_name, manager in project.module_managers.items():
            # Extract from configuration values
            if manager.configuration:
                params = self._extract_module_parameters(
                    module_name, 
                    manager.configuration
                )
                self.extracted_params[module_name] = params
            
            # Extract from module definitions (cross-module references)
            if manager.module_def:
                self._extract_definition_references(module_name, manager.module_def)
        
        return self.extracted_params
    
    def _extract_definition_references(self, module_name: str, module_def):
        """Extract cross-module references from module definition"""
        # Check containers for references
        for container_def in module_def.containers.values():
            self._extract_container_def_references(module_name, container_def, module_def.short_name)
    
    def _extract_container_def_references(self, module_name: str, container_def, parent_path: str):
        """Recursively extract references from container definition"""
        container_path = f"{parent_path}/{container_def.short_name}"
        
        # Check for references that point to other modules
        for ref_name, ref_def in container_def.references.items():
            dest_ref = ref_def.destination_ref or ""
            
            if not dest_ref:
                continue
                
            # Debug output
            print(f"[DEP] Checking ref: {ref_name} -> {dest_ref}")
            
            # Extract target module name from destination_ref
            # Format: /AUTOSAR/EcucDefs/ModuleName/...
            # or: /ModuleName_Def_Pkg/ModuleName/...
            target_module = self._extract_module_from_path(dest_ref)
            
            if target_module and target_module.lower() != module_name.lower():
                # This is a cross-module reference!
                print(f"[DEP] Found cross-module ref: {module_name}.{ref_name} -> {target_module}")
                self.cross_module_refs.append({
                    'source_module': module_name,
                    'source_container': container_path,
                    'reference_name': ref_name,
                    'target_path': dest_ref,
                    'target_module': target_module,
                    'description': ref_def.description or ""
                })
        
        # Recurse into sub-containers
        for sub_container in container_def.sub_containers.values():
            self._extract_container_def_references(module_name, sub_container, container_path)
    
    def _extract_module_from_path(self, path: str) -> str:
        """Extract module name from a definition reference path.
        
        Examples:
            /AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration -> Mcu
            /Mcu_Def_Pkg/Mcu/Container -> Mcu
            /AUTOSAR/EcucDefs/Adc/AdcConfigSet -> Adc
        """
        if not path:
            return ""
        
        parts = path.strip('/').split('/')
        
        # Pattern 1: /AUTOSAR/EcucDefs/ModuleName/...
        if len(parts) >= 3 and parts[0] == 'AUTOSAR' and parts[1] == 'EcucDefs':
            return parts[2]
        
        # Pattern 2: /ModuleName_Def_Pkg/ModuleName/...
        if len(parts) >= 2:
            if '_Def_Pkg' in parts[0] or 'Def_Pkg' in parts[0]:
                return parts[1]
            # Pattern 3: /ModuleName/Container/...
            return parts[0]
        
        return ""
    
    def _extract_module_parameters(
        self, 
        module_name: str, 
        configuration: EcucModuleConfiguration
    ) -> List[Dict]:
        """Extract parameters from a module configuration"""
        params = []
        
        print(f"[DEP] Extracting params from module: {module_name}")
        print(f"[DEP]   Containers count: {len(configuration.containers)}")
        
        for container in configuration.containers:
            params.extend(self._extract_container_parameters(
                module_name, container, ""
            ))
        
        print(f"[DEP]   Total params extracted: {len(params)}")
        for p in params:
            print(f"[DEP]     - {p['parameter']} = {p['value']}")
        
        return params
    
    def _extract_container_parameters(
        self, 
        module_name: str,
        container: EcucContainerValue, 
        parent_path: str
    ) -> List[Dict]:
        """Recursively extract parameters from a container"""
        params = []
        container_path = f"{parent_path}/{container.short_name}" if parent_path else container.short_name
        
        # Extract parameter values
        for param_name, param_value in container.parameter_values.items():
            params.append({
                'module': module_name,
                'container': container_path,
                'parameter': param_name,
                'value': param_value.value,
                'type': type(param_value.value).__name__,
                'full_path': f"{module_name}.{container_path}.{param_name}"
            })
        
        # Extract reference values
        for ref_name, ref_value in container.reference_values.items():
            params.append({
                'module': module_name,
                'container': container_path,
                'parameter': ref_name,
                'value': ref_value.value_ref,
                'type': 'reference',
                'full_path': f"{module_name}.{container_path}.{ref_name}"
            })
        
        # Recursively extract from sub-containers
        for sub_container in container.sub_containers:
            params.extend(self._extract_container_parameters(
                module_name, sub_container, container_path
            ))
        
        return params
    
    def analyze_with_ai(self, params_info: Dict[str, List[Dict]]) -> List[Dict]:
        """
        Use AI to analyze parameters and infer potential dependencies.
        
        Args:
            params_info: Dict of module parameters
            
        Returns:
            List of potential dependency rules
        """
        dependencies = []
        
        # 1. Always include cross-module references from module definitions
        # (These are factual, not AI-generated)
        for ref in getattr(self, 'cross_module_refs', []):
            dependencies.append({
                'source_param': f"{ref['source_module']}.{ref['reference_name']}",
                'source_condition': '!=',
                'source_value': 'null',
                'target_param': f"{ref['target_module']}.{ref['target_path'].split('/')[-1]}",
                'target_condition': 'exists',
                'target_value': 'true',
                'reason': f"模块定义引用：{ref['source_module']} 通过 {ref['reference_name']} 引用 {ref['target_module']}",
                'status': 'pending',
                'origin': '📋 定义'  # Source: Module Definition
            })
        
        # 2. Use AI to find additional parameter dependencies
        if self.gemini_client and self.gemini_client.is_ready():
            prompt = self._build_analysis_prompt(params_info)
            
            try:
                response = self.gemini_client.generate_response(prompt, timeout=60)
                print(f"[DEP] Raw AI Response:\n{response}\n[DEP] End of Raw Response")
                if response.startswith("🌍") or response.startswith("❌"):
                    print(f"[DEP] AI Analysis unavailable: {response}")
                else:
                    ai_dependencies = self._parse_ai_response(response)
                    dependencies.extend(ai_dependencies)
            except Exception as e:
                print(f"[DEP] AI analysis failed with exception: {e}")
        
        # 3. If no dependencies found, use heuristic fallback
        if not dependencies:
            return self._fallback_heuristic_analysis(params_info)
        
        return dependencies
    
    def _build_analysis_prompt(self, params_info: Dict[str, List[Dict]]) -> str:
        """Build the prompt for AI dependency analysis"""
        # Build a list of valid module.parameter combinations
        valid_params = []
        
        # Summarize parameters by module
        summary_lines = []
        for module_name, params in params_info.items():
            summary_lines.append(f"\n## 模块: {module_name}")
            # Group by container
            by_container = {}
            for p in params[:500]:  # Increased limit to 500
                container = p['container']
                if container not in by_container:
                    by_container[container] = []
                by_container[container].append(f"  - {p['parameter']} ({p['type']}): {p['value']}")
                # Track valid parameter paths
                valid_params.append(f"{module_name}.{p['parameter']}")
            
            for container, param_list in by_container.items():
                summary_lines.append(f"### {container}")
                summary_lines.extend(param_list[:50])  # Increased limit per container to 50
        
        params_summary = "\n".join(summary_lines)
        
        prompt = f"""你是一个顶级的 AUTOSAR 系统架构师和 BSW 配置专家。
请深度分析以下模块的参数配置（包括它们的值和物理引用关系），识别出它们之间**潜在**的逻辑耦合、一致性要求或安全限制。

【分析任务】
即便没有显式的错误，也请基于 AUTOSAR 最佳实践推断潜在的依赖规则。例如：
- **时钟频率约束**：如果 A 引用了 Mcu 的某个时钟，那么该时钟的频率是否应高于某个阈值？
- **硬件资源互斥**：检查是否有多个驱动可能在使用相同的底层硬件资源（虽然参数名不同）。
- **同步/延时要求**：主循环周期与采样周期是否匹配？
- **一致性检查**：如果 A 模块使能了某个功能，B 模块中对应的接口或参数是否也必须配置？

【输入参数列表】
{params_summary}

【输出要求】
1. **严格**遵循以下格式输出规则（每行一条）：
   `MODULE.PARAM 条件 值 -> MODULE.PARAM 条件 期望值 | 详细原因`
2. 即使关系比较微妙，也请作为“潜在规则”输出，供人工审核。
3. 原因部分请用中文详细说明：逻辑依据 + 潜在风险。
4. **禁止**输出任何 Markdown 标题、列表或解释性文字。
5. 如果确实没有任何发现，输出 "NO_DEPENDENCIES"。

示例：
Adc.AdcClockSource == Mcu.McuClockRef -> Mcu.McuClockFrequency >= 80000000 | ADC 使用该时钟源时，为了确保采样转换精度，MCU 主频不建议低于 80MHz"""

        return prompt
    
    def _parse_ai_response(self, response: str) -> List[Dict]:
        """Parse AI response into dependency rules"""
        dependencies = []
        
        if "NO_DEPENDENCIES" in response:
            return dependencies
        
        # Parse each line
        lines = response.strip().split('\n')
        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            
            # Try to parse: SOURCE COND VAL -> TARGET COND VAL | REASON
            # Improved regex to handle spaces and various characters more robustly
            match = re.match(
                r'([A-Za-z0-9_.]+)\s*([=<>!]+|exists)\s*(\S+)\s*->\s*([A-Za-z0-9_.]+)\s*([=<>!]+|exists)\s*(\S+)\s*\|\s*(.+)',
                line
            )
            if match:
                dependencies.append({
                    'source_param': match.group(1),
                    'source_condition': match.group(2),
                    'source_value': match.group(3),
                    'target_param': match.group(4),
                    'target_condition': match.group(5),
                    'target_value': match.group(6),
                    'reason': match.group(7).strip(),
                    'status': 'pending',
                    'origin': '🤖 AI'  # Source: AI Inference
                })
        
        return dependencies
    
    def _fallback_heuristic_analysis(self, params_info: Dict[str, List[Dict]]) -> List[Dict]:
        """
        Fallback heuristic analysis when AI is not available.
        Uses naming patterns and definition references to infer potential dependencies.
        """
        dependencies = []
        
        # 1. Include cross-module references from module definitions
        for ref in getattr(self, 'cross_module_refs', []):
            dependencies.append({
                'source_param': f"{ref['source_module']}.{ref['reference_name']}",
                'source_condition': '!=',
                'source_value': 'null',
                'target_param': f"{ref['target_module']} (模块)",
                'target_condition': 'exists',
                'target_value': 'true',
                'reason': f"模块 {ref['source_module']} 通过 {ref['reference_name']} 引用模块 {ref['target_module']}，目标模块必须存在",
                'status': 'pending'
            })
        
        # 2. Analyze configuration parameters
        all_params = []
        for module_name, params in params_info.items():
            for p in params:
                all_params.append({**p, 'module': module_name})
        
        # Look for common patterns
        # Enable/Disable flags that might affect other modules
        enable_params = [p for p in all_params if 'Enable' in p['parameter'] or 'Use' in p['parameter']]
        
        # Size/Count parameters that might have cross-module implications
        size_params = [p for p in all_params if 'Size' in p['parameter'] or 'Count' in p['parameter'] or 'Max' in p['parameter']]
        
        # Reference parameters pointing to other modules (from configuration values)
        ref_params = [p for p in all_params if p['type'] == 'reference']
        
        # Generate heuristic rules for reference values
        for ref_p in ref_params:
            if ref_p['value']:
                # Extract target module from reference path
                target_parts = ref_p['value'].split('/')
                if len(target_parts) > 1:
                    dependencies.append({
                        'source_param': ref_p['full_path'],
                        'source_condition': '!=',
                        'source_value': 'null',
                        'target_param': ref_p['value'],
                        'target_condition': 'exists',
                        'target_value': 'true',
                        'reason': f"引用参数 {ref_p['parameter']} 指向的目标必须存在",
                        'status': 'pending',
                        'origin': '📄 配置'  # Source: Config Reference
                    })
        
        return dependencies
    
    def generate_markdown(
        self, 
        dependencies: List[Dict], 
        output_path: Optional[Path] = None
    ) -> str:
        """
        Generate a markdown file with discovered dependencies.
        
        Args:
            dependencies: List of dependency rules
            output_path: Optional path to save the file
            
        Returns:
            Markdown content string
        """
        lines = [
            "# 跨模块依赖规则",
            "",
            "> 此文件由 AI 自动生成，请人工审核后确认。",
            "> 将 `[ ]` 改为 `[x]` 表示确认该规则，改为 `[-]` 表示拒绝。",
            "",
            "## 规则说明",
            "",
            "| 状态 | 含义 |",
            "|------|------|",
            "| `[ ]` | 待确认 |",
            "| `[x]` | 已确认 - 将用于验证 |",
            "| `[-]` | 已拒绝 - 不使用 |",
            "",
            "---",
            "",
            "## 发现的依赖关系",
            "",
        ]
        
        # Add debug info about extracted parameters
        if hasattr(self, 'extracted_params') and self.extracted_params:
            lines.extend([
                "",
                "<details>",
                "<summary>📊 分析数据 (点击展开)</summary>",
                "",
            ])
            for module_name, params in self.extracted_params.items():
                lines.append(f"**{module_name}** ({len(params)} 个参数)")
                for p in params[:10]:  # Limit to 10
                    lines.append(f"- `{p['parameter']}` = {p['value']}")
                if len(params) > 10:
                    lines.append(f"- ... 及其他 {len(params) - 10} 个参数")
                lines.append("")
            lines.extend([
                "</details>",
                "",
            ])
        
        if not dependencies:
            lines.append("*未发现潜在的跨模块依赖关系*")
        else:
            # Use wider columns for status and origin
            lines.append("| #  | 状态  | 来源     | 源参数 | 条件 | 目标参数 | 要求 | 原因 |")
            lines.append("|----|-------|----------|--------|------|----------|------|------|")
            
            for i, dep in enumerate(dependencies, 1):
                status = "[ ]" if dep.get('status') == 'pending' else (
                    "[x]" if dep.get('status') == 'confirmed' else "[-]"
                )
                origin = dep.get('origin', '❓ 未知')
                # Use emojis for clarity
                origin_map = {
                    '🤖 AI': '🤖 AI 智能推断',
                    '📋 定义': '📋 模块定义',
                    '📄 配置': '📄 配置引用'
                }
                display_origin = origin_map.get(origin, origin)
                # Ensure values are clean for the table
                source_val_display = f"{dep['source_condition']} {dep['source_value']}"
                target_req_display = f"{dep['target_condition']} {dep['target_value']}"
                
                lines.append(
                    f"| {i} | {status} | {display_origin} | `{dep['source_param']}` | "
                    f"{source_val_display} | "
                    f"`{dep['target_param']}` | "
                    f"{target_req_display} | "
                    f"{dep['reason']} |"
                )
        
        lines.extend([
            "",
            "---",
            "",
            "## 如何使用",
            "",
            "1. 审核上述规则，修改状态标记",
            "2. 保存文件",
            "3. 在工具中执行 **验证跨模块依赖**",
            "",
        ])
        
        content = "\n".join(lines)
        
        if output_path:
            output_path.parent.mkdir(parents=True, exist_ok=True)
            output_path.write_text(content, encoding='utf-8')
            print(f"Dependencies saved to: {output_path}")
        
        return content
