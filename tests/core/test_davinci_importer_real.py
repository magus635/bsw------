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

        # Must return merged bytes containing both elements from /MICROSAR
        assert result is not None
        assert b"Arti" in result
        assert b"ArtiRefinement" in result

    def test_merger_combines_bsw_impl_and_memory_sections(self):
        """Arti_bswmd + Arti_MemMap merge MEMORY-SECTIONS and REQUIRED-ARTIFACTS on same BSW-IMPLEMENTATION."""
        from autosar_configurator.core.davinci_importer import SipFile, SipMerger

        f1 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <ECUC-MODULE-DEF><SHORT-NAME>Arti</SHORT-NAME></ECUC-MODULE-DEF>
                <BSW-IMPLEMENTATION>
                    <SHORT-NAME>Arti_Impl</SHORT-NAME>
                    <SW-VERSION>1.02.00</SW-VERSION>
                    <PRECONFIGURED-CONFIGURATION-REFS>
                        <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/Arti_Pre</PRECONFIGURED-CONFIGURATION-REF>
                    </PRECONFIGURED-CONFIGURATION-REFS>
                </BSW-IMPLEMENTATION>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""
        f2 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES>
        <AR-PACKAGE>
            <SHORT-NAME>MICROSAR</SHORT-NAME>
            <ELEMENTS>
                <BSW-IMPLEMENTATION>
                    <SHORT-NAME>Arti_Impl</SHORT-NAME>
                    <SW-VERSION>1.02.00</SW-VERSION>
                    <RESOURCE-CONSUMPTION>
                        <MEMORY-SECTIONS>
                            <MEMORY-SECTION>
                                <SHORT-NAME>ARTI_CODE</SHORT-NAME>
                                <ALIGNMENT>UNSPECIFIED</ALIGNMENT>
                            </MEMORY-SECTION>
                        </MEMORY-SECTIONS>
                    </RESOURCE-CONSUMPTION>
                    <REQUIRED-ARTIFACTS>
                        <ARTIFACT-DESCRIPTORS>
                            <AUTOSAR-ENGINEERING-OBJECT>
                                <SHORT-LABEL>Arti_Cfg.h</SHORT-LABEL>
                                <CATEGORY>SWHDR</CATEGORY>
                            </AUTOSAR-ENGINEERING-OBJECT>
                        </ARTIFACT-DESCRIPTORS>
                    </REQUIRED-ARTIFACTS>
                </BSW-IMPLEMENTATION>
            </ELEMENTS>
        </AR-PACKAGE>
    </AR-PACKAGES>
</AUTOSAR>"""
        sip_files = [
            SipFile(path=Path("Components/Arti/BSWMD/Arti_bswmd.arxml"), module="Arti", content=f1),
            SipFile(path=Path("Components/Arti/BSWMD/Arti_MemMap.arxml"), module="Arti", content=f2),
        ]
        merged = SipMerger.merge_definition(sip_files, "Arti")
        assert merged is not None
        assert b"ARTI_CODE" in merged
        assert b"Arti_Cfg.h" in merged

        meta = SipMerger.extract_bsw_implementation_metadata(sip_files)
        assert meta["sw_version"] == "1.02.00"
        assert meta["preconfigured_refs"] == ["/MICROSAR/Arti_Pre"]
        assert meta["memory_sections"][0]["short_name"] == "ARTI_CODE"
        assert meta["required_artifacts"][0]["short_label"] == "Arti_Cfg.h"

    def test_merger_detects_type_scalar_and_duplicate_def_conflicts(self):
        """SipMergeError is raised on type mismatch, SW-VERSION conflict, or duplicate ECUC-MODULE-DEF."""
        from autosar_configurator.core.davinci_importer import SipFile, SipMergeError, SipMerger

        def_xml = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <ECUC-MODULE-DEF><SHORT-NAME>Arti</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        impl_same_name = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <BSW-IMPLEMENTATION><SHORT-NAME>Arti</SHORT-NAME></BSW-IMPLEMENTATION>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        with pytest.raises(SipMergeError, match="type mismatch"):
            SipMerger.merge_definition([
                SipFile(path=Path("a.arxml"), module="Arti", content=def_xml),
                SipFile(path=Path("b.arxml"), module="Arti", content=impl_same_name),
            ], "Arti")

        impl_v1 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <BSW-IMPLEMENTATION><SHORT-NAME>Arti_Impl</SHORT-NAME><SW-VERSION>1.02.00</SW-VERSION></BSW-IMPLEMENTATION>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        impl_v2 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <BSW-IMPLEMENTATION><SHORT-NAME>Arti_Impl</SHORT-NAME><SW-VERSION>1.03.00</SW-VERSION></BSW-IMPLEMENTATION>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        with pytest.raises(SipMergeError, match="SW-VERSION"):
            SipMerger.merge_definition([
                SipFile(path=Path("v1.arxml"), module="Arti", content=impl_v1),
                SipFile(path=Path("v2.arxml"), module="Arti", content=impl_v2),
            ], "Arti")

        with pytest.raises(SipMergeError, match="across components"):
            SipMerger.merge_definition([
                SipFile(path=Path("Components/CompA/BSWMD/a.arxml"), module="Arti", content=def_xml),
                SipFile(path=Path("Components/CompB/BSWMD/b.arxml"), module="Arti", content=def_xml),
            ], "Arti")

    def test_extract_value_collections_merges_fragments_and_loads_in_package(self, tmp_path):
        """Multi-file Pre fragments merge recursively and ModulePackage.load_pre/read_impl_metadata work."""
        from autosar_configurator.core.davinci_importer import SipFile, SipMerger, SipPackageWriter
        from autosar_configurator.core.packages.manifest import load_manifest
        from autosar_configurator.core.packages.package import ModulePackage

        def_file = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <ECUC-MODULE-DEF><SHORT-NAME>vBRS</SHORT-NAME></ECUC-MODULE-DEF>
        <BSW-IMPLEMENTATION>
            <SHORT-NAME>vBRS_Impl</SHORT-NAME>
            <SW-VERSION>2.00.00</SW-VERSION>
            <RESOURCE-CONSUMPTION><MEMORY-SECTIONS>
                <MEMORY-SECTION><SHORT-NAME>VBRS_VAR</SHORT-NAME></MEMORY-SECTION>
            </MEMORY-SECTIONS></RESOURCE-CONSUMPTION>
            <PRECONFIGURED-CONFIGURATION-REFS>
                <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/vBRS_Pre</PRECONFIGURED-CONFIGURATION-REF>
            </PRECONFIGURED-CONFIGURATION-REFS>
        </BSW-IMPLEMENTATION>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        pre_1 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
            <SHORT-NAME>vBRS_Pre</SHORT-NAME>
            <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
            <CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                    <SHORT-NAME>vBRSGeneral</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vBRS/vBRSGeneral</DEFINITION-REF>
                    <PARAMETER-VALUES>
                        <ECUC-TEXTUAL-PARAM-VALUE>
                            <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/vBRS/vBRSGeneral/P1</DEFINITION-REF>
                            <VALUE>one</VALUE>
                        </ECUC-TEXTUAL-PARAM-VALUE>
                    </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
            </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        pre_2 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
    <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
            <SHORT-NAME>vBRS_Pre</SHORT-NAME>
            <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vBRS</DEFINITION-REF>
            <CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                    <SHORT-NAME>vBRSGeneral</SHORT-NAME>
                    <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vBRS/vBRSGeneral</DEFINITION-REF>
                    <PARAMETER-VALUES>
                        <ECUC-TEXTUAL-PARAM-VALUE>
                            <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/vBRS/vBRSGeneral/P2</DEFINITION-REF>
                            <VALUE>two</VALUE>
                        </ECUC-TEXTUAL-PARAM-VALUE>
                    </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
            </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
    </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

        sip_files = [
            SipFile(path=Path("Components/vBRS/BSWMD/vBRS_bswmd.arxml"), module="vBRS", content=def_file),
            SipFile(path=Path("Components/vBRS/BSWMD/vBRS_General_pre.arxml"), module="vBRS", content=pre_1),
            SipFile(path=Path("DemoComponents/vBaseEnv/BSWMD/vBRS_THA6_pre.arxml"), module="vBRS", content=pre_2),
        ]
        merged_def = SipMerger.merge_definition(sip_files, "vBRS")
        vals = SipMerger.extract_value_collections(sip_files, "vBRS")
        impl = SipMerger.extract_bsw_implementation_metadata(sip_files)
        pkg_dir = SipPackageWriter.write_package(
            "vBRS",
            merged_def,
            pre_config=vals.get("pre"),
            rec_config=vals.get("rec"),
            output_dir=tmp_path,
            source_files=[str(f.path) for f in sip_files],
            impl_metadata=impl,
        )
        manifest = load_manifest(pkg_dir)
        assert manifest.pre == ["/MICROSAR/vBRS_Pre"]
        assert manifest.implementation_path == "/MICROSAR/vBRS_Impl"

        pkg = ModulePackage(pkg_dir, manifest)
        pre_cfgs = pkg.load_pre(None)
        assert len(pre_cfgs) == 1
        gen = pre_cfgs[0].containers[0]
        assert gen.parameter_values["P1"].value == "one"
        assert gen.parameter_values["P2"].value == "two"

        read_impl = pkg.read_impl_metadata()
        assert read_impl["memory_sections"][0]["short_name"] == "VBRS_VAR"

    def test_merge_deduplicates_unnamed_children_and_detects_value_conflict(self):
        """Identical unnamed children (e.g. PRECONFIGURED-CONFIGURATION-REF) are deduplicated;
        conflicting single-valued parameters across multi-file Pre fragments raise SipMergeError."""
        from lxml import etree
        from autosar_configurator.core.davinci_importer import SipFile, SipMergeError, SipMerger

        # 1. Identical PRECONFIGURED-CONFIGURATION-REF across two files should not duplicate
        impl_a = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <BSW-IMPLEMENTATION>
      <SHORT-NAME>ModA_Impl</SHORT-NAME>
      <PRECONFIGURED-CONFIGURATION-REFS>
        <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/ModA_Pre</PRECONFIGURED-CONFIGURATION-REF>
      </PRECONFIGURED-CONFIGURATION-REFS>
    </BSW-IMPLEMENTATION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        merged = SipMerger.merge_definition([
            SipFile(path=Path("a.arxml"), module="ModA", content=impl_a),
            SipFile(path=Path("b.arxml"), module="ModA", content=impl_a),
        ], "ModA")
        assert merged is not None
        root = etree.fromstring(merged)
        refs = [e for e in root.iter() if isinstance(e.tag, str) and e.tag.endswith("PRECONFIGURED-CONFIGURATION-REF")]
        assert len(refs) == 1

        # 2. Conflicting single-valued parameter in same-path Pre fragments raises SipMergeError
        pre_1 = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>ModA_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/ModA</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>General</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/ModA/General</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/ModA/General/P1</DEFINITION-REF>
          <VALUE>alpha</VALUE>
        </ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        pre_2 = pre_1.replace(b">alpha<", b">beta<")
        with pytest.raises(SipMergeError, match="Conflicting parameter"):
            SipMerger.extract_value_collections([
                SipFile(path=Path("pre1.arxml"), module="ModA", content=pre_1),
                SipFile(path=Path("pre2.arxml"), module="ModA", content=pre_2),
            ], "ModA")


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

    def test_package_writer_puts_def_pre_rec_in_config_without_sources_json(self, tmp_path):
        """Definition, Pre, and Rec files all live under config/; metadata is in module.json (no sources.json)."""
        from autosar_configurator.core.davinci_importer import SipPackageWriter
        from autosar_configurator.core.packages.manifest import load_manifest

        def_xml = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>Os</SHORT-NAME></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        pre_xml = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Os_Pre</SHORT-NAME></ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        rec_xml = b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Os_Rec</SHORT-NAME></ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

        pkg_path = SipPackageWriter.write_package(
            module_name="Os",
            definition_content=def_xml,
            pre_config=pre_xml,
            rec_config=rec_xml,
            output_dir=tmp_path,
            source_files=["ThirdParty/Os/Os_bswmd.arxml"],
            impl_metadata={
                "ar_path": "/MICROSAR/Os_Impl",
                "sw_version": "4.2.1",
                "memory_sections": [{"short_name": "OS_CODE"}],
            },
            implementation_dir="ThirdParty/Os/Implementation",
        )

        assert (pkg_path / "config" / "Os.arxml").is_file()
        assert (pkg_path / "config" / "Os_Pre.arxml").is_file()
        assert (pkg_path / "config" / "Os_Rec.arxml").is_file()
        assert not (pkg_path / "def").exists()
        assert not (pkg_path / "sources.json").exists()

        manifest = load_manifest(pkg_path)
        assert [f.path for f in manifest.files] == [
            "config/Os.arxml",
            "config/Os_Pre.arxml",
            "config/Os_Rec.arxml",
        ]
        assert manifest.definition == "/MICROSAR/Os"
        assert manifest.implementation == "ThirdParty/Os/Implementation"
        assert manifest.implementation_path == "/MICROSAR/Os_Impl"
        assert manifest.pre == ["/MICROSAR/Os_Pre"]
        assert manifest.rec == ["/MICROSAR/Os_Rec"]
        assert manifest.origin["source"] == "davinci"
        assert manifest.origin["sw_version"] == "4.2.1"
        assert manifest.origin["source_files"] == ["ThirdParty/Os/Os_bswmd.arxml"]
        assert manifest.origin["implementation"]["ar_path"] == "/MICROSAR/Os_Impl"

        impl = SipPackageWriter.read_impl_metadata(pkg_path)
        assert impl["sw_version"] == "4.2.1"
        assert impl["memory_sections"] == [{"short_name": "OS_CODE"}]

    def test_read_impl_metadata_legacy_sources_json_and_def_fallback(self, tmp_path):
        """Legacy packages using sources.json or def/*.arxml remain readable."""
        import json
        from autosar_configurator.core.davinci_importer import SipPackageWriter

        # 1. Legacy sources.json
        legacy_sources = tmp_path / "LegacySources"
        legacy_sources.mkdir()
        (legacy_sources / "sources.json").write_text(
            json.dumps({"implementation": {"ar_path": "/Old/Impl", "sw_version": "1.0.0"}}),
            encoding="utf-8",
        )
        assert SipPackageWriter.read_impl_metadata(legacy_sources)["sw_version"] == "1.0.0"

        # 2. Legacy def/*.arxml fallback (no module.json or sources.json)
        legacy_def = tmp_path / "LegacyDef"
        (legacy_def / "def").mkdir(parents=True)
        (legacy_def / "def" / "LegacyDef.arxml").write_bytes(b"""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <BSW-IMPLEMENTATION>
      <SHORT-NAME>LegacyDef_Impl</SHORT-NAME>
      <SW-VERSION>2.3.4</SW-VERSION>
    </BSW-IMPLEMENTATION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""")
        assert SipPackageWriter.read_impl_metadata(legacy_def)["sw_version"] == "2.3.4"


def test_ecuc_def_parser_supports_linker_symbol_multiline_and_add_info(tmp_path):
    """EcucDefParser recognizes ECUC-LINKER-SYMBOL-DEF, ECUC-MULTILINE-STRING-PARAM-DEF, and ECUC-ADD-INFO-PARAM-DEF."""
    from autosar_configurator.core.model.definition_model import EcucParameterType
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

    def_xml = tmp_path / "vLinkGen_bswmd.arxml"
    def_xml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>vLinkGen</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>vLinkGenSection</SHORT-NAME>
          <PARAMETERS>
            <ECUC-LINKER-SYMBOL-DEF><SHORT-NAME>SectionName</SHORT-NAME></ECUC-LINKER-SYMBOL-DEF>
            <ECUC-MULTILINE-STRING-PARAM-DEF><SHORT-NAME>AdditionalCode</SHORT-NAME></ECUC-MULTILINE-STRING-PARAM-DEF>
            <ECUC-ADD-INFO-PARAM-DEF><SHORT-NAME>ExtraDoc</SHORT-NAME></ECUC-ADD-INFO-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    mod_def = EcucDefParser().parse_module_def_file(def_xml)
    params = mod_def.containers["vLinkGenSection"].parameters
    assert params["SectionName"].param_type == EcucParameterType.LINKER_SYMBOL
    assert params["AdditionalCode"].param_type == EcucParameterType.MULTILINE_STRING
    assert params["ExtraDoc"].param_type == EcucParameterType.ADD_INFO
