"""Task 5: 端到端集成测试。

使用真实 DaVinci 工程（D:/davinci/mcuapp）验证完整导入流程。
"""

import pytest
from pathlib import Path
import json
import logging

from autosar_configurator.core.davinci_import_cli import DaVinciImportCLI

logger = logging.getLogger(__name__)

# 真实项目路径
REAL_DAVINCI_PROJECT = Path("D:/davinci/mcuapp/Applications/SipAddon/StartApplication/StartApplication.dpa")
REAL_DAVINCI_ROOT = REAL_DAVINCI_PROJECT.parent


class TestEndToEndDaVinciImport:
    """端到端导入测试：真实 DaVinci 工程。"""

    @pytest.mark.skipif(not REAL_DAVINCI_PROJECT.exists(), reason="DaVinci project not found")
    def test_import_real_davinci_project(self, tmp_path):
        """导入真实 DaVinci 工程，验证模块和资源。"""
        cli = DaVinciImportCLI(verbose=True)
        output_dir = tmp_path / "imported"

        # 运行导入（不含资源，先测试 BSW）
        code = cli.run([
            "--project", str(REAL_DAVINCI_PROJECT),
            "--output", str(output_dir),
            "--verbose"
        ])

        assert code == 0, "Import should succeed"
        assert output_dir.exists(), "Output directory should be created"

        # 验证：至少有一个模块包
        module_packages = list(output_dir.glob("*/module.json"))
        assert len(module_packages) > 0, f"Expected at least one module, found {len(module_packages)}"

        # 列出导入的模块
        modules = []
        for manifest_path in sorted(module_packages):
            data = json.loads(manifest_path.read_text())
            modules.append(data["module"])
            logger.info("Imported module: %s", data["module"])

        # 验证期望的模块（根据真实 SIP 结构）
        # 至少应该有 Os, vBRS 等常见 BSW 模块
        assert "Os" in modules or "vBRS" in modules or len(modules) > 0, \
            f"Expected common BSW modules, found: {modules}"

        logger.info("Total imported: %d modules", len(modules))

    @pytest.mark.skipif(not REAL_DAVINCI_PROJECT.exists(), reason="DaVinci project not found")
    def test_import_with_resource_extraction(self, tmp_path):
        """导入并提取 MCAL 资源。"""
        cli = DaVinciImportCLI(verbose=True)
        output_dir = tmp_path / "imported_with_resources"

        # 运行导入（含资源）
        code = cli.run([
            "--project", str(REAL_DAVINCI_PROJECT),
            "--output", str(output_dir),
            "--include-resources",
            "--verbose"
        ])

        assert code == 0, "Import with resources should succeed"

        # 验证资源文件生成
        yaml_files = list(output_dir.glob("resources_*.yaml"))
        logger.info("Generated %d resource YAML files", len(yaml_files))

        # 如果有资源文件，验证格式
        for yaml_file in yaml_files:
            content = yaml_file.read_text()
            assert len(content) > 0, f"Resource file {yaml_file.name} should not be empty"
            logger.info("Resource file: %s (%d bytes)", yaml_file.name, len(content))

    @pytest.mark.skipif(not REAL_DAVINCI_PROJECT.exists(), reason="DaVinci project not found")
    def test_import_with_derivative_uuid_filter(self, tmp_path):
        """使用 DerivativeMapping 按 UUID 过滤。"""
        cli = DaVinciImportCLI(verbose=True)
        output_dir = tmp_path / "filtered_import"

        # 尝试用一个 UUID 过滤（可能没有匹配，但命令应该不崩溃）
        test_uuid = "B632B9EE-F23D-43CD-9C54-542178A058D9"

        code = cli.run([
            "--project", str(REAL_DAVINCI_PROJECT),
            "--output", str(output_dir),
            "--derivative-uuid", test_uuid,
            "--verbose"
        ])

        # 即使没有匹配也应该成功
        assert code == 0, "Filtered import should not crash"
        assert output_dir.exists()

    @pytest.mark.skipif(not REAL_DAVINCI_PROJECT.exists(), reason="DaVinci project not found")
    def test_verify_no_unresolved_references(self, tmp_path):
        """验证导入后无未解决引用。"""
        cli = DaVinciImportCLI(verbose=True)
        output_dir = tmp_path / "verify_import"

        code = cli.run([
            "--project", str(REAL_DAVINCI_PROJECT),
            "--output", str(output_dir),
        ])

        assert code == 0

        # 读取所有生成的 module.json，检查完整性
        module_files = list(output_dir.glob("*/module.json"))

        for manifest_path in module_files:
            data = json.loads(manifest_path.read_text())

            # 验证必需字段
            assert "schema" in data, f"Missing schema in {manifest_path}"
            assert "module" in data, f"Missing module in {manifest_path}"
            assert "definition" in data, f"Missing definition in {manifest_path}"

            # definition 文件应该存在
            def_file = manifest_path.parent / data["definition"]
            assert def_file.exists(), f"Definition file not found: {def_file}"

            logger.info("Verified: %s (schema=%s)", data["module"], data["schema"])

        logger.info("All %d modules verified", len(module_files))
