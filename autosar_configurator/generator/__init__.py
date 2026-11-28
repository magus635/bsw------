"""
Code Generator Package
"""
from .template_engine import TemplateEngine, TemplateLoader
from .generator import CodeGenerator
from .platform_gen import (
    PlatformGenReport,
    generate_platform_artifacts,
    render_comstack_cfg_h,
    render_module_memmap_h,
    render_vbrs_files,
)
from .template_audit import (
    FileParityDetail,
    ModuleAuditResult,
    TemplateAuditReport,
    audit_project_templates,
)

__all__ = [
    'TemplateEngine',
    'TemplateLoader',
    'CodeGenerator',
    'PlatformGenReport',
    'FileParityDetail',
    'ModuleAuditResult',
    'TemplateAuditReport',
    'audit_project_templates',
    'generate_platform_artifacts',
    'render_comstack_cfg_h',
    'render_module_memmap_h',
    'render_vbrs_files',
]
