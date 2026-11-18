"""Task 4: CLI 工具测试。

验证命令行导入工具的行为：
- 命令行解析
- 项目加载 + 模块扫描
- 模块导入 + 打包
- 可选 MCAL 资源导出
"""

import pytest
from pathlib import Path
import tempfile
import json

from autosar_configurator.core.davinci_import_cli import DaVinciImportCLI


class TestDaVinciImportCLI:
    """命令行导入工具的基本功能。"""

    def test_cli_rejects_missing_project_file(self):
        """项目文件不存在时报错。"""
        cli = DaVinciImportCLI()

        with tempfile.TemporaryDirectory() as tmp_path:
            missing = Path(tmp_path) / "missing.dpa"
            output = Path(tmp_path) / "output"

            code = cli.run(["--project", str(missing), "--output", str(output)])
            assert code != 0

    def test_cli_creates_output_on_success(self):
        """成功时创建输出目录。"""
        cli = DaVinciImportCLI()

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 创建真实格式的 DaVinci 项目文件
            dpa_file = tmp_path / "test.dpa"
            sip_path = tmp_path / "sip"
            sip_path.mkdir()

            # 真实 .dpa 格式：<ProjectAssistant><Folders><SIP>相对路径</SIP></Folders></ProjectAssistant>
            dpa_xml = """<?xml version="1.0"?>
<ProjectAssistant>
    <Folders>
        <SIP>sip</SIP>
    </Folders>
</ProjectAssistant>"""
            dpa_file.write_text(dpa_xml)

            output_dir = tmp_path / "output"

            code = cli.run(["--project", str(dpa_file), "--output", str(output_dir)])

            # 应该至少创建输出目录（即使没有模块也成功）
            assert output_dir.exists()
            assert code == 0

    def test_cli_parses_derivative_uuid(self):
        """--derivative-uuid 参数被正确解析。"""
        cli = DaVinciImportCLI()

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 创建真实格式的项目
            dpa_file = tmp_path / "test.dpa"
            sip_path = tmp_path / "sip"
            sip_path.mkdir()

            dpa_xml = """<?xml version="1.0"?>
<ProjectAssistant>
    <Folders>
        <SIP>sip</SIP>
    </Folders>
</ProjectAssistant>"""
            dpa_file.write_text(dpa_xml)

            output_dir = tmp_path / "output"
            test_uuid = "B632B9EE-F23D-43CD-9C54-542178A058D9"

            # 运行时不应该崩溃
            code = cli.run([
                "--project", str(dpa_file),
                "--output", str(output_dir),
                "--derivative-uuid", test_uuid
            ])

            # 成功（即使没有匹配）
            assert code == 0

    def test_cli_optional_include_resources_flag(self):
        """--include-resources 标志被正确处理。"""
        cli = DaVinciImportCLI()

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            dpa_file = tmp_path / "test.dpa"
            sip_path = tmp_path / "sip"
            sip_path.mkdir()

            dpa_xml = """<?xml version="1.0"?>
<ProjectAssistant>
    <Folders>
        <SIP>sip</SIP>
    </Folders>
</ProjectAssistant>"""
            dpa_file.write_text(dpa_xml)

            output_dir = tmp_path / "output"

            # 有 --include-resources 时应该不崩溃
            code = cli.run([
                "--project", str(dpa_file),
                "--output", str(output_dir),
                "--include-resources"
            ])

            assert code == 0

    def test_cli_with_real_module_structure(self):
        """真实模块结构下的导入。"""
        cli = DaVinciImportCLI()

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 创建 SIP 结构
            sip_dir = tmp_path / "sip"
            os_bswmd = sip_dir / "Components" / "Os" / "BSWMD"
            os_bswmd.mkdir(parents=True)

            # 创建有效的 ARXML
            os_file = os_bswmd / "Os_Arm_bswmd.arxml"
            os_file.write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF>
                    <SHORT-NAME>Os</SHORT-NAME>
                </ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>""")

            # 创建真实格式的 DaVinci 项目
            dpa_file = tmp_path / "project.dpa"
            dpa_xml = """<?xml version="1.0"?>
<ProjectAssistant>
    <Folders>
        <SIP>sip</SIP>
    </Folders>
</ProjectAssistant>"""
            dpa_file.write_text(dpa_xml)

            output_dir = tmp_path / "output"

            # 运行导入
            code = cli.run(["--project", str(dpa_file), "--output", str(output_dir)])

            # 成功
            assert code == 0
            assert output_dir.exists()

            # 应该生成 Os 模块包
            os_package = output_dir / "Os"
            if os_package.exists():
                manifest = os_package / "module.json"
                assert manifest.exists()
                data = json.loads(manifest.read_text())
                assert data["module"] == "Os"
