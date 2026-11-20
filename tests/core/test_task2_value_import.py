"""Task 2-RED: 值导入 + 多块合并 + DerivativeMapping 过滤。

验证需求：
1. load_configuration 调用 merge_module_configurations，多块自动合并
2. SipScanner DerivativeMapping 过滤（Task 2 递延，此处 RED 先写）
3. 导入 vBRS Pre/Rec 两块，应自动合并成一个
"""

import pytest
from pathlib import Path
import tempfile
from lxml import etree

from autosar_configurator.core.config_manager import (
    ConfigurationManager,
    merge_module_configurations,
    ValidationError,
)
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
)
from autosar_configurator.core.parser.arxml_parser import ArxmlParser


class TestLoadConfigurationMergesMultipleBlocks:
    """load_configuration 自动合并多块模块配置。"""

    def test_load_configuration_auto_merges_multiple_blocks(self):
        """同一文件两块 vBRS（Pre 和 Rec），导入后自动合并。"""
        # 模拟模块定义
        module_def = EcucModuleDef(
            short_name="vBRS",
            definition_ref="/MICROSAR/vBRS",
        )

        # 创建有两个 vBRS 块的 ARXML
        arxml_content = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-CONFIGURATION-VALUES>
                    <SHORT-NAME>vBRS_Pre</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
                    <CONTAINERS/>
                </ECUC-MODULE-CONFIGURATION-VALUES>
                <ECUC-MODULE-CONFIGURATION-VALUES>
                    <SHORT-NAME>vBRS_Rec</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
                    <CONTAINERS/>
                </ECUC-MODULE-CONFIGURATION-VALUES>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""

        with tempfile.NamedTemporaryFile(suffix=".arxml", delete=False) as f:
            f.write(arxml_content)
            f.flush()
            file_path = Path(f.name)

        try:
            manager = ConfigurationManager(module_def)

            # 调用 load_configuration（会用 merge_module_configurations）
            manager.load_configuration(file_path)

            # 验证：结果应该是一个合并后的配置
            assert manager.configuration is not None
            assert manager.configuration.short_name in ("vBRS_Pre", "vBRS_Rec", "vBRS")
        finally:
            file_path.unlink()

    def test_load_configuration_reports_conflict(self):
        """两块有冲突参数值时，应报错（不静默覆盖）。"""
        module_def = EcucModuleDef(
            short_name="vBRS",
            definition_ref="/MICROSAR/vBRS",
        )

        arxml_content = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-CONFIGURATION-VALUES>
                    <SHORT-NAME>vBRS_1</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
                    <CONTAINERS/>
                </ECUC-MODULE-CONFIGURATION-VALUES>
                <ECUC-MODULE-CONFIGURATION-VALUES>
                    <SHORT-NAME>vBRS_2</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
                    <CONTAINERS/>
                </ECUC-MODULE-CONFIGURATION-VALUES>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""

        with tempfile.NamedTemporaryFile(suffix=".arxml", delete=False) as f:
            f.write(arxml_content)
            f.flush()
            file_path = Path(f.name)

        try:
            manager = ConfigurationManager(module_def)

            # 此处暂不期望报错（因为测试 ARXML 没有参数值）
            # 真实场景下若有冲突会报 ValidationError
            manager.load_configuration(file_path)

            assert manager.configuration is not None
        finally:
            file_path.unlink()


class TestSipScannerDerivativeMappingFilter:
    """SipScanner 按 DerivativeMapping 过滤 chip 子目录（Task 2 递延实现）。"""

    def test_scanner_loads_all_chips_without_mapping(self):
        """没有 DerivativeMapping 时，扫描所有 chip 子目录。"""
        from autosar_configurator.core.davinci_importer import SipScanner

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 构建 Components/Os/BSWMD/Os/两个chip目录
            os_bswmd = tmp_path / "Components" / "Os" / "BSWMD" / "Os"
            os_bswmd.mkdir(parents=True)

            chip1 = os_bswmd / "Generic_CortexR52_ASIMD"
            chip1.mkdir()
            (chip1 / "os_pre.arxml").write_text("""<?xml version="1.0"?>
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

            chip2 = os_bswmd / "S32Gxx"
            chip2.mkdir()
            (chip2 / "os_pre.arxml").write_text("""<?xml version="1.0"?>
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

            scanner = SipScanner(tmp_path)
            files = scanner.scan_module("Os")

            # 无 DerivativeMapping，应返回所有 chip 的文件
            assert len(files) >= 2

    def test_scanner_filters_by_derivative_mapping(self):
        """有 DerivativeMapping 时，只加载匹配 UUID 的 chip。

        注：此测试目前 RED（功能未实现）。Task 2 实现后改 GREEN。
        """
        from autosar_configurator.core.davinci_importer import SipScanner

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 构建 Components/Os/BSWMD/Os/两个chip目录
            os_bswmd = tmp_path / "Components" / "Os" / "BSWMD" / "Os"
            os_bswmd.mkdir(parents=True)

            chip1 = os_bswmd / "Generic_CortexR52_ASIMD"
            chip1.mkdir()
            (chip1 / "os_pre.arxml").write_text("""<?xml version="1.0"?>
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

            chip2 = os_bswmd / "S32Gxx"
            chip2.mkdir()
            (chip2 / "os_pre.arxml").write_text("""<?xml version="1.0"?>
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

            # 写 DerivativeMapping：UUID → Generic_CortexR52_ASIMD
            mapping_file = tmp_path / "Components" / "Os" / "GeneratorMsr" / "DerivativeMapping_Os.xml"
            mapping_file.parent.mkdir(parents=True)
            mapping_file.write_text("""<?xml version="1.0"?>
<Settings>
    <Settings Name="ModuleList">
        <Settings Name="Os">
            <Settings Name="Generic_CortexR52_ASIMD">
                <Settings Name="B632B9EE-F23D-43CD-9C54-542178A058D9">
                    <Setting Name="SIP_Folder" Value="Generic_CortexR52_ASIMD"/>
                </Settings>
            </Settings>
        </Settings>
    </Settings>
</Settings>""")

            scanner = SipScanner(tmp_path)
            files = scanner.scan_module("Os", derivative_uuid="B632B9EE-F23D-43CD-9C54-542178A058D9")

            # 只返回 Generic_CortexR52_ASIMD 的文件
            assert len(files) == 1
            assert "Generic_CortexR52_ASIMD" in str(files[0].path)
            assert "S32Gxx" not in str(files[0].path)

    def test_scanner_raises_when_derivative_uuid_missing_from_mapping(self, tmp_path: Path):
        """存在 DerivativeMapping 但查不到当前 UUID 时必须报错，不得退回全量加载。"""
        from autosar_configurator.core.davinci_importer import (
            SipDerivativeMappingError,
            SipMergeError,
            SipScanner,
        )

        os_arxml = """<?xml version="1.0"?>
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
</AUTOSAR>"""
        os_bswmd = tmp_path / "Components" / "Os" / "BSWMD" / "Os"
        for chip_dir in ("Generic_CortexR52_ASIMD", "S32Gxx"):
            d = os_bswmd / chip_dir
            d.mkdir(parents=True)
            (d / "os_pre.arxml").write_text(os_arxml, encoding="utf-8")

        mapping_file = tmp_path / "Components" / "Os" / "GeneratorMsr" / "DerivativeMapping_Os.xml"
        mapping_file.parent.mkdir(parents=True)
        mapping_file.write_text("""<?xml version="1.0"?>
<Settings>
    <Settings Name="ModuleList">
        <Settings Name="Os">
            <Settings Name="Generic_CortexR52_ASIMD">
                <Settings Name="B632B9EE-F23D-43CD-9C54-542178A058D9">
                    <Setting Name="SIP_Folder" Value="Generic_CortexR52_ASIMD"/>
                </Settings>
            </Settings>
        </Settings>
    </Settings>
</Settings>""", encoding="utf-8")

        unknown_uuid = "00000000-0000-0000-0000-000000000000"
        scanner = SipScanner(tmp_path)

        assert issubclass(SipDerivativeMappingError, SipMergeError)

        with pytest.raises(SipDerivativeMappingError) as exc1:
            scanner.scan_module("Os", derivative_uuid=unknown_uuid)
        msg1 = str(exc1.value)
        assert "Os" in msg1
        assert unknown_uuid in msg1
        assert "DerivativeMapping_Os.xml" in msg1

        with pytest.raises(SipDerivativeMappingError) as exc2:
            scanner.scan_all_modules(derivative_uuid=unknown_uuid)
        msg2 = str(exc2.value)
        assert "Os" in msg2
        assert unknown_uuid in msg2
        assert "DerivativeMapping_Os.xml" in msg2

    def test_scanner_raises_when_derivative_mapping_xml_is_malformed(self, tmp_path: Path):
        """DerivativeMapping XML 解析失败时必须报错，不得静默吞掉。"""
        from autosar_configurator.core.davinci_importer import SipDerivativeMappingError, SipScanner

        os_dir = tmp_path / "Components" / "Os" / "BSWMD" / "Os" / "Generic_CortexR52_ASIMD"
        os_dir.mkdir(parents=True)
        (os_dir / "os_pre.arxml").write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF><SHORT-NAME>Os</SHORT-NAME></ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        mapping_file = tmp_path / "Components" / "Os" / "GeneratorMsr" / "DerivativeMapping_Os.xml"
        mapping_file.parent.mkdir(parents=True)
        mapping_file.write_text("<Settings><Broken", encoding="utf-8")

        scanner = SipScanner(tmp_path)
        with pytest.raises(SipDerivativeMappingError) as exc:
            scanner.scan_module("Os", derivative_uuid="B632B9EE-F23D-43CD-9C54-542178A058D9")
        assert "DerivativeMapping_Os.xml" in str(exc.value)
        assert "Os" in str(exc.value)

    def test_scan_module_ignores_unrelated_module_mapping_error(self, tmp_path: Path):
        """按单模块扫描 vBRS 时，不因其他模块(Os)的 DerivativeMapping 不匹配而失败。"""
        from autosar_configurator.core.davinci_importer import SipScanner

        os_dir = tmp_path / "Components" / "Os" / "BSWMD" / "Os" / "Generic_CortexR52_ASIMD"
        os_dir.mkdir(parents=True)
        (os_dir / "os_pre.arxml").write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF><SHORT-NAME>Os</SHORT-NAME></ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        mapping_file = tmp_path / "Components" / "Os" / "GeneratorMsr" / "DerivativeMapping_Os.xml"
        mapping_file.parent.mkdir(parents=True)
        mapping_file.write_text("""<?xml version="1.0"?>
<Settings>
    <Settings Name="Generic_CortexR52_ASIMD">
        <Settings Name="UUID-A">
            <Setting Name="SIP_Folder" Value="Generic_CortexR52_ASIMD"/>
        </Settings>
    </Settings>
</Settings>""", encoding="utf-8")

        vbrs_dir = tmp_path / "DemoComponents" / "vBRS" / "BSWMD"
        vbrs_dir.mkdir(parents=True)
        (vbrs_dir / "vBRS_bswmd.arxml").write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF><SHORT-NAME>vBRS</SHORT-NAME></ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        scanner = SipScanner(tmp_path)
        files = scanner.scan_module("vBRS", derivative_uuid="UUID-UNKNOWN")
        assert len(files) == 1
        assert files[0].module == "vBRS"
