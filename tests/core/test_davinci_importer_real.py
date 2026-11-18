"""Task 1-RED: DaVinciProject parser + SIP scanner with real SIP layout.

Tests use verified real layouts from 2026-11-18:
- Components/Os/BSWMD/Os/Generic_CortexR52_ASIMD/*.arxml
- DemoComponents/vBaseEnv/BSWMD/*: vBRS files, vLinkGen files mixed
- module ≠ component dir (must group by DEFINITION-REF in ARXML, not path)

Before implementation: verify that scanner groups files by content, not by path.
"""

import pytest
from pathlib import Path
import tempfile
from lxml import etree
import zipfile
import io


class TestDaVinciProjectParser:
    """Parse real DaVinci .dpa format and extract metadata."""

    def test_parse_davinci_dpa_extracts_all_fields(self):
        """Parser reads .dpa and extracts SIP root, derivative UUID/name, module definitions, split map."""
        # Sample from verified D:\davinci\mcuapp\Applications\SipAddon\StartApplication\StartApplication.dpa
        dpa_content = """<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<ProjectAssistant Version="5.30.35 SP2">
    <Folders>
        <SIP>.\\..\\..\\..</SIP>
        <ECUC>.\\Config\\ECUC</ECUC>
    </Folders>
    <Environment>
        <Derivative UUID="B632B9EE-F23D-43CD-9C54-542178A058D9">Tongxin_THA6206</Derivative>
    </Environment>
    <Display>
        <ModuleDefinitionMappings>
            <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
            <ModuleDefinitionMapping ModuleConfigName="Port" ModuleDefinitionRef="/THA6_AS440_FuSa/Port"/>
            <ModuleDefinitionMapping ModuleConfigName="vBRS" ModuleDefinitionRef="/MICROSAR/vBRS"/>
        </ModuleDefinitionMappings>
    </Display>
    <EcucSplitter>
        <Configuration>Config\\ECUC\\StartApplication.ecuc.arxml</Configuration>
        <Splitter File=".\\Config\\ECUC\\StartApplication_Os_Os_ecuc.arxml">
            <Module Name="Os"/>
        </Splitter>
        <Splitter File=".\\Config\\ECUC\\StartApplication_Port_Port_ecuc.arxml">
            <Module Name="Port"/>
        </Splitter>
    </EcucSplitter>
    <ECUC>
        <Active RootPackageName="/ActiveEcuC/ActiveEcuC">Config\\ECUC\\StartApplication.ecuc.arxml</Active>
    </ECUC>
</ProjectAssistant>"""

        with tempfile.NamedTemporaryFile(mode='w', suffix='.dpa', delete=False) as f:
            f.write(dpa_content)
            f.flush()
            dpa_path = Path(f.name)

            from autosar_configurator.core.davinci_importer import DaVinciProject
            project = DaVinciProject.from_file(dpa_path)

            # Verify all fields
            assert project.derivative_uuid == "B632B9EE-F23D-43CD-9C54-542178A058D9"
            assert project.derivative_name == "Tongxin_THA6206"
            assert project.sip_root is not None
            assert len(project.module_definitions) == 3
            assert project.module_definitions["Os"] == "/MICROSAR/Os"
            assert project.module_definitions["Port"] == "/THA6_AS440_FuSa/Port"
            assert project.module_definitions["vBRS"] == "/MICROSAR/vBRS"
            assert len(project.ecuc_split_map) == 2
            assert "Os" in project.ecuc_split_map
            assert "Port" in project.ecuc_split_map
            assert project.main_ecuc_file is not None

    def test_parser_identifies_bsw_vs_mcal_modules(self):
        """Parser correctly classifies modules by definition path prefix."""
        dpa_content = """<?xml version="1.0"?>
<ProjectAssistant>
    <Folders><SIP>.</SIP></Folders>
    <Environment><Derivative UUID="uuid1">Der</Derivative></Environment>
    <Display>
        <ModuleDefinitionMappings>
            <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
            <ModuleDefinitionMapping ModuleConfigName="Com" ModuleDefinitionRef="/MICROSAR/Com"/>
            <ModuleDefinitionMapping ModuleConfigName="Port" ModuleDefinitionRef="/THA6_AS440_FuSa/Port"/>
            <ModuleDefinitionMapping ModuleConfigName="Mcu" ModuleDefinitionRef="/THA6_AS440_FuSa/Mcu"/>
        </ModuleDefinitionMappings>
    </Display>
    <EcucSplitter>
        <Configuration>Main.ecuc.arxml</Configuration>
    </EcucSplitter>
    <ECUC><Active RootPackageName="/">Main.ecuc.arxml</Active></ECUC>
</ProjectAssistant>"""

        with tempfile.NamedTemporaryFile(mode='w', suffix='.dpa', delete=False) as f:
            f.write(dpa_content)
            f.flush()

            from autosar_configurator.core.davinci_importer import DaVinciProject
            project = DaVinciProject.from_file(Path(f.name))

            bsw = project.bsw_modules()
            mcal = project.mcal_modules()

            assert set(bsw) == {"Os", "Com"}
            assert set(mcal) == {"Port", "Mcu"}


class TestSipScannerContentDriven:
    """SIP scanner groups files by ARXML content (DEFINITION-REF), not by path.

    Real layout: vBRS files in DemoComponents/vBaseEnv/BSWMD/, not DemoComponents/vBRS/.
    Scanner must return vBRS files even though component dir is vBaseEnv.
    """

    def test_scanner_finds_modules_by_definition_ref_not_path(self, tmp_path):
        """Scanner walks all component BSWMD dirs and groups by DEFINITION-REF in ARXML."""
        # Setup: simulated SIP
        # Components/Os/BSWMD/Os/Generic_CortexR52_ASIMD/
        components = tmp_path / "Components"
        os_bswmd = components / "Os" / "BSWMD" / "Os" / "Generic_CortexR52_ASIMD"
        os_bswmd.mkdir(parents=True)

        # Write Os arxml
        os_arxml = os_bswmd / "Os_Generic_CortexR52_ASIMD_bswmd_pre.arxml"
        os_arxml.write_text("""<?xml version="1.0"?>
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

        # Setup: DemoComponents/vBaseEnv/BSWMD/ with vBRS file inside (mimics real layout)
        demo = tmp_path / "DemoComponents"
        vbaseenv_bswmd = demo / "vBaseEnv" / "BSWMD"
        vbaseenv_bswmd.mkdir(parents=True)

        # vBRS file inside vBaseEnv's BSWMD (real layout: vBRS has no separate BSWMD)
        vbrs_arxml = vbaseenv_bswmd / "vBRS_General_pre.arxml"
        vbrs_arxml.write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF>
                    <SHORT-NAME>vBRS</SHORT-NAME>
                </ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>""")

        # Scanner: walk all BSWMD, extract DEFINITION-REF from each file, group by module
        from autosar_configurator.core.davinci_importer import SipScanner
        scanner = SipScanner(tmp_path)

        # Request Os files
        os_files = scanner.scan_module("Os", "B632B9EE-F23D-43CD-9C54-542178A058D9")
        assert len(os_files) == 1
        assert os_files[0].module == "Os"

        # Request vBRS files — must find them even though they're in vBaseEnv dir
        vbrs_files = scanner.scan_module("vBRS", "B632B9EE-F23D-43CD-9C54-542178A058D9")
        assert len(vbrs_files) == 1, "Scanner should find vBRS_General_pre.arxml in DemoComponents/vBaseEnv/BSWMD/"
        assert vbrs_files[0].module == "vBRS"

    def test_scanner_respects_derivative_mapping(self, tmp_path):
        """If DerivativeMapping_<Module>.xml exists, load only matching UUID folder."""
        # Setup: Components/Os/BSWMD/Os/ with two chip folders
        os_bswmd = tmp_path / "Components" / "Os" / "BSWMD" / "Os"
        os_bswmd.mkdir(parents=True)

        # Valid ARXML with Os module definition
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

        # Folder 1: Generic_CortexR52_ASIMD (matches UUID)
        folder1 = os_bswmd / "Generic_CortexR52_ASIMD"
        folder1.mkdir()
        (folder1 / "os_pre.arxml").write_text(os_arxml)

        # Folder 2: S32Gxx (doesn't match)
        folder2 = os_bswmd / "S32Gxx"
        folder2.mkdir()
        (folder2 / "os_pre.arxml").write_text(os_arxml)

        # DerivativeMapping: UUID → Generic_CortexR52_ASIMD
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

        from autosar_configurator.core.davinci_importer import SipScanner
        scanner = SipScanner(tmp_path)

        # Should load only from matching folder
        files = scanner.scan_module("Os", "B632B9EE-F23D-43CD-9C54-542178A058D9")
        assert len(files) == 1
        assert "Generic_CortexR52_ASIMD" in str(files[0].path)


class TestSipMergerByDefinition:
    """Merger combines files by AUTOSAR path, uses same_definition to match containers.

    Prerequisite test for the "前置修复 Step 1" that fixes痛点 1.
    """

    def test_merger_handles_multiple_files_for_one_module(self):
        """Multiple ARXML files (bswmd + MemMap) merge by AUTOSAR path, not file name."""
        from autosar_configurator.core.davinci_importer import SipMerger

        bswmd = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF>
                    <SHORT-NAME>Arti</SHORT-NAME>
                </ECUC-MODULE-DEF>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""

        memmap = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <MEMORY-SECTION-REFINEMENT>
                    <SHORT-NAME>ArtiRefinement</SHORT-NAME>
                </MEMORY-SECTION-REFINEMENT>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""

        merger = SipMerger()
        # merge_module expects List[SipFile], not dict
        from autosar_configurator.core.davinci_importer import SipFile
        result = merger.merge_module([
            SipFile(path=Path("Arti_bswmd.arxml"), module="Arti", content=bswmd),
            SipFile(path=Path("Arti_MemMap.arxml"), module="Arti", content=memmap),
        ], "Arti")

        # Must return merged bytes without error
        assert result is not None


class TestSipPackageWriter:
    """Write module packages with correct module.json schema."""

    def test_package_writer_creates_valid_module_json(self, tmp_path):
        """Generated module.json passes load_manifest validation."""
        from autosar_configurator.core.davinci_importer import SipPackageWriter
        from autosar_configurator.core.packages.manifest import load_manifest

        writer = SipPackageWriter()

        arxml = b"<arxml/>"
        pkg_path = writer.write_package("Os", arxml, output_dir=tmp_path)

        # Verify load_manifest accepts it
        manifest = load_manifest(pkg_path)
        assert manifest.module == "Os"
        assert manifest.definition is not None
