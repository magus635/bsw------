# Vector SIP Ingestion, DaVinci Import, MCAL Resources — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Enable one-click migration of DaVinci Configurator projects to this tool, with complete BSW definitions, configuration values, and MCAL ECU resources.

**Architecture:** 
- Three-stage pipeline: (1) Vector SIP one-time ingestion → module packages, (2) DaVinci XML project import → format-8 JSON project, (3) EB MCAL resource extraction → chip YAML. 
- Ingestion is a headless CLI tool (`python -m autosar_configurator.tools.ingest_sip`) to enable offline reuse.
- DaVinci import is a UI wizard in `ProjectController`.
- MCAL resources are extracted from Resource EB plugin's `resource/*.properties` files (not `autosar/*.arxml` as initially assumed).

**Tech Stack:** 
- lxml for ARXML/XML parsing
- Phase 1 baseline merge (`autosar_configurator.core.baseline.*`) for conflict handling
- Existing `PackageManager`, `WorkspaceProject` for format-8 structure
- pytest for regression against DaVinci baseline (byte-for-byte code generation)

**Spec:** 
- Design: `openspec/changes/add-vector-sip-davinci-import/design.md` (Decisions D-A through D-G)
- Requirements: `openspec/changes/add-vector-sip-davinci-import/specs/sip-library/spec.md`, `davinci-import/spec.md`, `mcal-resources/spec.md`

---

## Global Constraints

- **SIP location:** `D:\davinci\mcuapp` (124 Component dirs, 110 with BSWMD, 115 arxml in subdirs)
- **DaVinci project example:** `D:\davinci\mcuapp\Applications\SipAddon\StartApplication\StartApplication.dpa` (28 BSW modules, XML format `<ProjectAssistant Version="5.30.35 SP2">`)
- **EB MCAL resource source:** Resource plugin's `resource/CotexR52_<Chip>.properties` (e.g., `Port.AvailableEXTIModule`, `Port.AvailableGTMModule`, `Port.AvailablePortsID`)
- **Format version:** Input format-7 projects and format-8 output only; no auto-upgrade of format-7
- **Pre-configuration semantics:** Imported Pre values become `origin=PRE` in baseline, read-only until unlocked (Phase 1 baseline)
- **No silent data loss:** Every skipped module, unresolved reference, dropped parameter must be reported in import report
- **Backward compatibility:** Existing projects (format-7 and format-8) must load and generate identically before and after

---

## Review Focus

These input classes or conditions are likely to cause failures if missed:

1. **BSWMD merge conflicts across files:** Two files declare same AUTOSAR path with different single-value field (e.g., `SW-VERSION`). Must raise error, not silently pick one. Test: merge `Arti_bswmd.arxml` (version 1.02.00) + `Arti_bswmd_alt.arxml` (version 1.03.00) → error with both paths and values.

2. **Derivative subdirectory selection without mapping file:** Component has `BSWMD/<chip>/` subdirs but no `DerivativeMapping_*.xml`. Rule: load ALL subdirs. Test: vBaseEnv or vMem_30_Fls ingestion should include all chip variants' pre/rec files.

3. **Cross-component module fragments:** A module's files are split across two component dirs (e.g., vLinkGen in Components/vLinkGen/ and DemoComponents/vBaseEnv/). Merge must find and combine all. Test: vLinkGen ingestion lists all 9 pre/rec files in sources report.

4. **Unresolved Pre/Rec references:** A module declares Pre/Rec ref that no loaded file contains. Must warn, not block. Test: ingestion with missing `/MICROSAR/Arti_Pre` → warning in report, ingestion continues.

5. **DaVinci MCAL module override:** DaVinci `<ECUC><Active>` includes MCAL modules (Can, Dio, Mcu, Port, Resource, Spi) with `/THA6_AS440_FuSa/*` paths. Import must skip DaVinci's MCAL arxml and use user-specified EB config instead. Test: import with both DaVinci MCAL arxml AND EB config directory → report lists MCAL skipped, EB used.

---

## File Structure

**New files:**
- `autosar_configurator/core/sip_import.py` — SIP ingestion (scanner, merger, reporter)
- `autosar_configurator/core/davinci_import.py` — DaVinci XML parser and importer
- `autosar_configurator/tools/ingest_sip.py` — CLI entry point for SIP ingestion
- `autosar_configurator/tools/extract_mcal_resources.py` — CLI for standalone MCAL resource extraction
- `tests/core/test_sip_import.py` — Unit tests for SIP ingestion
- `tests/core/test_davinci_import.py` — Integration tests for DaVinci import
- `docs/superpowers/plans/2026-11-13-vector-sip-davinci-import.md` — This plan

**Modified files:**
- `autosar_configurator/core/packages/eb_plugin.py` — Add MCAL resource extraction from `resource/*.properties`
- `autosar_configurator/core/workspace_manager.py` — Add `import_davinci_project()` method
- `autosar_configurator/ui/controllers/project_controller.py` — Add "Import DaVinci Project" menu
- `autosar_configurator/core/parser/ecuc_def_parser.py` — May need ECUC-MULTILINE-STRING support (TBD during Task 1)

---

## Task 1: Vector SIP Scanner and BSWMD Merger

**Files:**
- Create: `autosar_configurator/core/sip_import.py`
- Create: `tests/core/test_sip_import.py`
- Test: `tests/core/test_sip_import.py`

**Interfaces:**
- Consumes: 
  - `pathlib.Path` for directory traversal
  - `lxml.etree` for ARXML parsing
  - `autosar_configurator.core.model.definition_model.EcucModuleDef`, `EcucModuleConfiguration` (existing Phase 1 types)
- Produces: 
  - `SipScanner(sip_root: Path, derivative_uuid: str) -> List[SipFile]` — scans Components/*/BSWMD/ recursively, returns arxml files grouped by module
  - `SipMerger(derivative_uuid: str) -> Dict[str, EcucModuleDef]` — merges SipFiles by AUTOSAR path, returns dict of merged definitions
  - `SipMergeError(path: str, reason: str, file1: Path, file2: Path)` — exception for conflicts

- [ ] **Step 1: Write failing tests for SIP scanner**

Create `tests/core/test_sip_import.py` with:

```python
def test_scan_sip_finds_components_bswmd():
    """Scanner locates Components/*/BSWMD/ and DemoComponents/*/BSWMD/ arxml files."""
    sip_root = Path("tests/fixtures/sip_sample")
    scanner = SipScanner(sip_root, derivative_uuid="B632B9EE...")
    files = scanner.scan()
    
    # Test expects ~3 arxml files for sample SIP subset
    assert len(files) >= 3
    assert any(f.path.name == "Arti_bswmd.arxml" for f in files)
    assert any(f.module == "Arti" for f in files)

def test_scan_handles_derivative_subdirs():
    """Scanner selects correct derivative subdirectory using DerivativeMapping_*.xml."""
    scanner = SipScanner(sip_root, derivative_uuid="B632B9EE-F23D...")
    files = scanner.scan()
    
    # Os module: should only include Generic_CortexR52_ASIMD, not other 41 subdirs
    os_files = [f for f in files if f.module == "Os"]
    assert all("Generic_CortexR52_ASIMD" in str(f.path) for f in os_files)
    assert not any("S32Gxx" in str(f.path) for f in os_files)

def test_scan_loads_all_subdirs_without_mapping():
    """Scanner loads all subdirectories when no DerivativeMapping_*.xml exists."""
    scanner = SipScanner(sip_root, derivative_uuid="...")
    files = scanner.scan()
    
    # vBaseEnv: should include all chip variant subdirs
    vbase_files = [f for f in files if f.module == "vBaseEnv"]
    assert len(vbase_files) >= 2  # At least Tongxin_THA6206 and THA6412
```

Run: `pytest tests/core/test_sip_import.py::test_scan_sip_finds_components_bswmd -xvs`
Expected: FAIL (SipScanner not defined)

- [ ] **Step 2: Implement SipScanner in `sip_import.py`**

```python
@dataclass
class SipFile:
    """A single ARXML file from SIP, identified with its module and content source."""
    path: Path
    module: str  # "Arti", "vBRS", "Os", etc.
    chip: Optional[str]  # Chip variant if from subdirectory, else None
    content: bytes  # Raw arxml content

class SipScanner:
    """Scan Vector SIP directory tree and return ARXML files grouped by module."""
    
    def __init__(self, sip_root: Path, derivative_uuid: str):
        """
        Args:
            sip_root: SIP root directory (e.g., D:\davinci\mcuapp)
            derivative_uuid: Project derivative UUID (e.g., "B632B9EE-F23D-43CD-9C54-542178A058D9")
                used to select Os subdirectory via DerivativeMapping_Os.xml
        """
        self.sip_root = sip_root
        self.derivative_uuid = derivative_uuid
    
    def scan(self) -> List[SipFile]:
        """Scan Components/*/BSWMD/ and DemoComponents/*/BSWMD/ recursively.
        
        Returns:
            List of SipFile sorted by (module, path) for deterministic output
        """
        # TODO: implement scan logic
```

Logic:
1. Recursively scan `sip_root / "Components"` and `sip_root / "DemoComponents"` for `BSWMD/` directories
2. For each component's BSWMD, scan `*.arxml` and subdirectories
3. For subdirectories, use derivative selector (D-D decision): if `GeneratorMsr/DerivativeMapping_<Module>.xml` exists, load only matching UUID; else load all
4. Infer module name from component dir name (last segment of path)
5. Return sorted list by (module, path)

Return type: `List[SipFile]` with deterministic sort.

- [ ] **Step 3: Run tests to verify scanner**

Run: `pytest tests/core/test_sip_import.py::test_scan_sip_finds_components_bswmd -xvs`
Expected: PASS (or detailed failures on fixtures)

- [ ] **Step 4: Implement BSWMD merger**

Add to `sip_import.py`:

```python
class SipMergeError(Exception):
    """Raised when merge conflict detected: same path, different element type or single-value field."""
    def __init__(self, ar_path: str, reason: str, file1: Path, file2: Path):
        self.ar_path = ar_path
        self.reason = reason
        self.file1 = file1
        self.file2 = file2
        super().__init__(f"Merge conflict at {ar_path}: {reason}\n  {file1}\n  {file2}")

class SipMerger:
    """Merge ARXML elements from multiple SIP files by AUTOSAR path."""
    
    def merge(self, files: List[SipFile]) -> Dict[str, EcucModuleDef]:
        """Merge elements by AUTOSAR path; return dict of merged definitions.
        
        Args:
            files: List of SipFile from SipScanner
        
        Returns:
            Dict[module_name] -> EcucModuleDef (merged definition for that module)
        
        Raises:
            SipMergeError: On merge conflict (type mismatch, single-value field conflict)
        """
        # TODO: implement merge logic
```

Logic:
1. Parse each SipFile's arxml using `lxml.etree`
2. Extract all `ECUC-MODULE-DEF` and `ECUC-MODULE-CONFIGURATION-VALUES` elements, keyed by AUTOSAR path
3. For each path, collect elements from all files
4. If same path has >1 element: check compatibility
   - All must be same element type → else `SipMergeError` (D-C)
   - For single-value fields (SW-VERSION, AR-RELEASE-VERSION, etc.), all must match → else error
   - Merge children (e.g., MEMORY-SECTIONS from multiple files)
5. Return merged defs in deterministic order (by module name, then by path)

Edge cases:
- Same path in two files with same content → acceptable (log debug)
- Missing Pre/Rec reference → warning, not error (spec R3, non-blocking)

- [ ] **Step 5: Write test for merger**

```python
def test_merge_combines_impl_and_memmap():
    """Merger combines Arti_bswmd.arxml (IMPL) + Arti_MemMap.arxml (MEMORY-SECTIONS)."""
    files = [
        SipFile(path=Path("Arti_bswmd.arxml"), module="Arti", chip=None, 
                content=b"""<AUTOSAR>
                  <AR-PACKAGES>
                    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME>
                      <AR-PACKAGES>
                        <AR-PACKAGE><SHORT-NAME>Arti_Impl</SHORT-NAME>
                          <ELEMENTS>
                            <ECUC-MODULE-DEF>
                              <SHORT-NAME>Arti_Impl</SHORT-NAME>
                              <SW-VERSION>1.02.00</SW-VERSION>
                              <ADMIN-DATA><LANGUAGE>EN</LANGUAGE></ADMIN-DATA>
                            </ECUC-MODULE-DEF>
                          </ELEMENTS>
                        </AR-PACKAGE>
                      </AR-PACKAGES>
                    </AR-PACKAGE>
                  </AR-PACKAGES>
                </AUTOSAR>"""),
        # ... add Arti_MemMap.arxml with MEMORY-SECTION children
    ]
    merger = SipMerger()
    result = merger.merge(files)
    
    assert "Arti" in result
    # Merged def should have both IMPL fields and MEMORY-SECTION children
    arti_impl = result["Arti"]
    assert arti_impl.sw_version == "1.02.00"
    assert len(arti_impl.memory_sections) > 0
```

Run: `pytest tests/core/test_sip_import.py::test_merge_combines_impl_and_memmap -xvs`
Expected: PASS

- [ ] **Step 6: Test conflict detection**

```python
def test_merge_raises_on_type_conflict():
    """Merger raises SipMergeError when same path has different element types."""
    files = [
        SipFile(..., content=b"""...<ECUC-MODULE-DEF><SHORT-NAME>Foo</SHORT-NAME>..."""),
        SipFile(..., content=b"""...<ECUC-CONTAINER-SPEC><SHORT-NAME>Foo</SHORT-NAME>..."""),
    ]
    merger = SipMerger()
    with pytest.raises(SipMergeError) as exc:
        merger.merge(files)
    assert "Merge conflict" in str(exc.value)
    assert "type" in str(exc.value).lower()

def test_merge_raises_on_single_value_field_conflict():
    """Merger raises SipMergeError when same path has conflicting SW-VERSION."""
    files = [
        SipFile(..., content=b"""...<SW-VERSION>1.02.00</SW-VERSION>..."""),
        SipFile(..., content=b"""...<SW-VERSION>1.03.00</SW-VERSION>..."""),
    ]
    merger = SipMerger()
    with pytest.raises(SipMergeError) as exc:
        merger.merge(files)
    assert "1.02.00" in str(exc.value)
    assert "1.03.00" in str(exc.value)
```

Run: `pytest tests/core/test_sip_import.py::test_merge_raises_on_type_conflict -xvs`
Expected: PASS

- [ ] **Step 7: Commit**

```bash
git add autosar_configurator/core/sip_import.py tests/core/test_sip_import.py
git commit -m "feat(sip): implement SIP scanner and BSWMD merger

- SipScanner: traverse Components/*/BSWMD/ recursively, handle derivative subdirs
- SipMerger: merge by AUTOSAR path with conflict detection
- SipMergeError: report conflicts (type mismatch, field conflict)
- Tests: scan, merge, conflict detection"
```

---

## Task 2: SIP Ingestion CLI and Module Package Generation

**Files:**
- Create: `autosar_configurator/tools/ingest_sip.py` (CLI entry point)
- Create: `autosar_configurator/core/sip_package_writer.py` (write module.json + config/)
- Modify: `autosar_configurator/core/sip_import.py` (add reporter)
- Create: `tests/core/test_sip_ingestion_e2e.py` (end-to-end test)

**Interfaces:**
- Consumes:
  - `SipScanner`, `SipMerger` from Task 1
  - `ModulePackage`, `ModuleManifest` (Phase 1 existing types)
  - `pathlib.Path`
- Produces:
  - `python -m autosar_configurator.tools.ingest_sip --sip-root D:\davinci\mcuapp --derivative-uuid B632B9EE... --output-dir D:\prj\sip_lib` → creates module packages
  - `SipIngestionReport` — reports modules, source files, conflicts, warnings
  - Each module: `<output_dir>/<Module>/module.json` + `config/` with define.arxml, pre/*.arxml, rec/*.arxml

- [ ] **Step 1: Implement SipPackageWriter**

Add to `sip_package_writer.py`:

```python
class SipPackageWriter:
    """Write merged SIP definitions and values into Phase 1 module packages."""
    
    def write_packages(self, merged_defs: Dict[str, EcucModuleDef], 
                       sip_files: List[SipFile], output_dir: Path) -> SipIngestionReport:
        """Write module packages to output_dir.
        
        Args:
            merged_defs: Dict[module_name] -> merged EcucModuleDef from Task 1
            sip_files: Original list of SipFile for source tracking
            output_dir: Target directory for packages
        
        Returns:
            SipIngestionReport with stats and any issues
        """
        # For each module in merged_defs:
        # 1. Create <output_dir>/<module>/
        # 2. Write module.json (ModuleManifest format)
        # 3. Write config/define.arxml (merged ECUC-MODULE-DEF)
        # 4. Extract and write config/pre/*.arxml (ECUC-MODULE-CONFIGURATION-VALUES with Pre role)
        # 5. Extract and write config/rec/*.arxml (Rec role)
        # 6. Record source files and versions in sources.json
```

- [ ] **Step 2: Write CLI entry point**

Create `autosar_configurator/tools/ingest_sip.py`:

```python
import argparse
from pathlib import Path
from autosar_configurator.core.sip_import import SipScanner, SipMerger
from autosar_configurator.core.sip_package_writer import SipPackageWriter

def main():
    parser = argparse.ArgumentParser(
        description="Ingest Vector SIP into module packages"
    )
    parser.add_argument("--sip-root", required=True, type=Path,
                        help="SIP root directory (e.g., D:\\davinci\\mcuapp)")
    parser.add_argument("--derivative-uuid", required=True,
                        help="Derivative UUID for subdirectory selection")
    parser.add_argument("--output-dir", required=True, type=Path,
                        help="Target directory for module packages")
    parser.add_argument("--stop-on-conflict", action="store_true",
                        help="Stop on first merge conflict (default: report and skip)")
    
    args = parser.parse_args()
    
    scanner = SipScanner(args.sip_root, args.derivative_uuid)
    files = scanner.scan()
    
    merger = SipMerger()
    try:
        merged_defs = merger.merge(files)
    except SipMergeError as e:
        if args.stop_on_conflict:
            print(f"ERROR: {e}")
            return 1
        # ... log and continue
    
    writer = SipPackageWriter()
    report = writer.write_packages(merged_defs, files, args.output_dir)
    
    # Print report
    print(f"Ingestion complete: {report.modules_merged} modules, {len(files)} files")
    if report.conflicts:
        print(f"Conflicts: {report.conflicts}")
    if report.unresolved_refs:
        print(f"Warnings: {len(report.unresolved_refs)} unresolved references")
    
    return 0

if __name__ == "__main__":
    exit(main())
```

- [ ] **Step 3: Make CLI executable via `python -m`**

Create `autosar_configurator/tools/__main__.py`:

```python
import sys
from .ingest_sip import main

if __name__ == "__main__":
    sys.exit(main())
```

- [ ] **Step 4: Write end-to-end test**

Create `tests/core/test_sip_ingestion_e2e.py`:

```python
def test_ingest_sample_sip_subset():
    """E2E: ingest sample SIP vBRS module, verify package structure."""
    import subprocess
    
    output_dir = Path(tempfile.mkdtemp())
    result = subprocess.run([
        sys.executable, "-m", "autosar_configurator.tools.ingest_sip",
        "--sip-root", str(TEST_SIP_ROOT),
        "--derivative-uuid", "B632B9EE-F23D-43CD-9C54-542178A058D9",
        "--output-dir", str(output_dir),
    ], capture_output=True, text=True)
    
    assert result.returncode == 0, f"Ingestion failed: {result.stderr}"
    
    # Verify vBRS package created
    vbrs_dir = output_dir / "vBRS"
    assert vbrs_dir.exists()
    assert (vbrs_dir / "module.json").exists()
    assert (vbrs_dir / "config" / "define.arxml").exists()
    
    # Load and verify module.json
    manifest = ModuleManifest.from_file(vbrs_dir / "module.json")
    assert manifest.module == "vBRS"
    assert manifest.definition == "/MICROSAR/vBRS_Impl"
```

- [ ] **Step 5: Run E2E test**

Run: `pytest tests/core/test_sip_ingestion_e2e.py::test_ingest_sample_sip_subset -xvs`
Expected: PASS (packages created with correct structure)

- [ ] **Step 6: Commit**

```bash
git add autosar_configurator/core/sip_package_writer.py autosar_configurator/tools/ingest_sip.py tests/core/test_sip_ingestion_e2e.py
git commit -m "feat(sip): CLI ingestion tool and package writer

- SipPackageWriter: write merged defs + pre/rec values to Phase 1 packages
- ingest_sip CLI: --sip-root --derivative-uuid --output-dir
- E2E test: ingest sample vBRS, verify package structure"
```

---

## Task 3: DaVinci XML Parser and Project Metadata Extraction

**Files:**
- Create: `autosar_configurator/core/davinci_import.py`
- Create: `tests/core/test_davinci_import.py`

**Interfaces:**
- Consumes:
  - DaVinci XML `.dpa` file (e.g., `StartApplication.dpa`)
  - `lxml.etree` for XML parsing
- Produces:
  - `DaVinciProject(dpa_path: Path)` — parser that reads XML `.dpa`
  - Properties: `sip_root`, `derivative_name`, `derivative_uuid`, `active_modules`, `ecuc_split_map`, `mcal_modules`
  - `EcucSplitter` — maps module name → arxml file path within project

- [ ] **Step 1: Write tests for DaVinci parser**

Create `tests/core/test_davinci_import.py`:

```python
def test_parse_davinci_project():
    """Parser reads DaVinci XML .dpa and extracts metadata."""
    dpa_path = Path(TEST_PROJECT_ROOT) / "StartApplication.dpa"
    project = DaVinciProject(dpa_path)
    
    assert project.sip_root == Path("D:/davinci/mcuapp")  # from <SIP>\.\.\..\</SIP>
    assert project.derivative_uuid == "B632B9EE-F23D-43CD-9C54-542178A058D9"
    assert project.derivative_name == "Tongxin_THA6206"
    assert len(project.active_modules) == 28  # <ECUC><Active> lists 28
    assert "Os" in [m.name for m in project.active_modules]

def test_extract_ecuc_splitter():
    """Parser extracts EcucSplitter: module name → arxml file."""
    dpa_path = ...
    project = DaVinciProject(dpa_path)
    
    splitter = project.ecuc_split_map
    assert splitter["Os"] == "Config/ECUC/StartApplication_Os_Os_ecuc.arxml"
    assert splitter["Com"] == "Config/ECUC/StartApplication_Com_Com_ecuc.arxml"
    assert len(splitter) == 28

def test_identify_mcal_modules():
    """Parser identifies MCAL vs BSW modules by definition path."""
    dpa_path = ...
    project = DaVinciProject(dpa_path)
    
    mcal = project.mcal_modules()  # Modules with paths like /THA6_AS440_FuSa/*
    assert len(mcal) == 6  # Can, Dio, Mcu, Port, Resource, Spi in sample
    assert all(m.definition.startswith("/THA6_AS440_FuSa/") for m in mcal)
```

- [ ] **Step 2: Implement DaVinciProject parser**

Add to `davinci_import.py`:

```python
@dataclass
class DaVinciActiveModule:
    """A module in DaVinci <ECUC><Active>."""
    name: str
    definition_ref: str  # e.g., "/MICROSAR/Os"
    module_description_ref: str  # e.g., "/MICROSAR/Os_Impl"

class DaVinciProject:
    """Parse and query a DaVinci XML .dpa project file."""
    
    def __init__(self, dpa_path: Path):
        """
        Args:
            dpa_path: Path to DaVinci XML .dpa (e.g., StartApplication.dpa)
        """
        self.dpa_path = dpa_path
        self.dpa_dir = dpa_path.parent
        
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        self.tree = etree.parse(str(dpa_path), parser)
        self.root = self.tree.getroot()
        
        # Parse key fields
        self.sip_root: Optional[Path] = self._extract_sip_root()
        self.derivative_uuid: Optional[str] = self._extract_derivative_uuid()
        self.derivative_name: Optional[str] = self._extract_derivative_name()
        self.active_modules: List[DaVinciActiveModule] = self._extract_active_modules()
        self.ecuc_split_map: Dict[str, str] = self._extract_ecuc_split_map()
    
    def _extract_sip_root(self) -> Optional[Path]:
        """Extract <SIP> path and resolve relative to .dpa directory."""
        sip_elem = self.root.find(".//SIP")
        if sip_elem is not None and sip_elem.text:
            rel_path = sip_elem.text.strip()
            # Resolve ..\..\.. relative paths
            resolved = (self.dpa_dir / rel_path).resolve()
            return resolved
        return None
    
    def _extract_derivative_uuid(self) -> Optional[str]:
        """Extract <Derivative UUID=...>."""
        deriv = self.root.find(".//Derivative[@UUID]")
        if deriv is not None:
            return deriv.get("UUID")
        return None
    
    def _extract_derivative_name(self) -> Optional[str]:
        """Extract <Derivative>name</Derivative>."""
        deriv = self.root.find(".//Derivative")
        if deriv is not None and deriv.text:
            return deriv.text.strip()
        return None
    
    def _extract_active_modules(self) -> List[DaVinciActiveModule]:
        """Extract <ECUC><Active> module list."""
        modules = []
        active = self.root.find(".//ECUC/Active")
        if active is None:
            return modules
        
        for mod_elem in active.findall("ModuleRef"):
            name = mod_elem.get("name", "")
            def_ref = mod_elem.get("definitionRef", "")
            mod_desc_ref = mod_elem.get("moduleDescriptionRef", "")
            modules.append(DaVinciActiveModule(
                name=name,
                definition_ref=def_ref,
                module_description_ref=mod_desc_ref
            ))
        
        return modules
    
    def _extract_ecuc_split_map(self) -> Dict[str, str]:
        """Extract <EcucSplitter> module → file mapping."""
        mapping = {}
        splitter = self.root.find(".//EcucSplitter")
        if splitter is None:
            return mapping
        
        for entry in splitter.findall("Entry"):
            module = entry.get("module", "")
            file_path = entry.get("file", "")
            if module and file_path:
                mapping[module] = file_path
        
        return mapping
    
    def mcal_modules(self) -> List[DaVinciActiveModule]:
        """Return MCAL modules (definition path starts with /THA6_AS440_FuSa/)."""
        return [m for m in self.active_modules 
                if m.definition_ref.startswith("/THA6_AS440_FuSa/")]
    
    def bsw_modules(self) -> List[DaVinciActiveModule]:
        """Return BSW modules (definition path starts with /MICROSAR/)."""
        return [m for m in self.active_modules 
                if m.definition_ref.startswith("/MICROSAR/")]
```

- [ ] **Step 3: Run tests to verify parser**

Run: `pytest tests/core/test_davinci_import.py::test_parse_davinci_project -xvs`
Expected: PASS (metadata extracted correctly)

- [ ] **Step 4: Commit**

```bash
git add autosar_configurator/core/davinci_import.py tests/core/test_davinci_import.py
git commit -m "feat(davinci): XML .dpa parser for project metadata

- DaVinciProject: parse XML and extract SIP root, derivative, active modules
- EcucSplitter: map module name to arxml file
- Identify BSW vs MCAL modules by definition path"
```

---

## Task 4: DaVinci Configuration Value Import

**Files:**
- Modify: `autosar_configurator/core/davinci_import.py` (add importer)
- Modify: `autosar_configurator/core/workspace_manager.py` (add `import_davinci_project()`)
- Create: `tests/core/test_davinci_value_import.py`

**Interfaces:**
- Consumes:
  - `DaVinciProject` from Task 3
  - Ingested module packages (from Task 2)
  - Existing EB import machinery (Phase 1)
  - `WorkspaceProject` (format-8 project structure)
- Produces:
  - `WorkspaceManager.import_davinci_project(dpa_path, sip_library_dir, mcal_config_dir, target_dir)` → new format-8 project
  - `DaVinciImportReport` — per-module counts (containers, params, refs), unresolved refs, skipped MCAL
  - Markdown report saved to `target_dir/.import_report.md`

- [ ] **Step 1: Implement configuration value loader**

Add to `davinci_import.py`:

```python
class DaVinciValueLoader:
    """Load configuration values from DaVinci ECUC arxml files."""
    
    def load_module_values(self, arxml_path: Path) -> EcucModuleConfiguration:
        """Parse DaVinci arxml and return EcucModuleConfiguration (configuration values)."""
        # Use existing parser (autosar_configurator.core.parser.ecuc_parser)
        # Read <ECUC-VALUE-COLLECTION> and extract containers/parameters
        parser = EcucConfigParser()
        return parser.parse(arxml_path)
```

- [ ] **Step 2: Implement importer workflow**

Add to `davinci_import.py`:

```python
class DaVinciImporter:
    """Import DaVinci project into format-8 tool project."""
    
    def import_to_format8(self, dpa_path: Path, sip_library_dir: Path, 
                          mcal_config_dir: Path, target_dir: Path, 
                          confirm=None) -> Tuple[WorkspaceProject, DaVinciImportReport]:
        """
        Args:
            dpa_path: DaVinci XML .dpa path
            sip_library_dir: Already-ingested SIP library (from Task 2)
            mcal_config_dir: EB MCAL config directory (e.g., TresosMcalProject/THA6206_LFBGA292_AS440/config)
            target_dir: New project directory
            confirm: Callback for user confirmations (e.g., which modules to import)
        
        Returns:
            (format-8 WorkspaceProject, detailed import report)
        """
        # 1. Parse DaVinci .dpa
        dv_project = DaVinciProject(dpa_path)
        
        # 2. Load SIP module library
        lib_modules = self._load_sip_library(sip_library_dir)
        
        # 3. For each BSW module in dv_project.active_modules:
        #    - Find definition in lib_modules
        #    - Load values from arxml (dv_project.dpa_dir / ecuc_split_map[module])
        #    - Create ModuleEntry in format-8 project
        
        # 4. For each MCAL module:
        #    - Import via existing EB importer
        #    - Record in report as "MCAL imported from <mcal_config_dir>"
        
        # 5. Create format-8 .dpa with all module entries, derivative UUID, etc.
        
        # 6. Return (project, report)
```

- [ ] **Step 3: Wire into WorkspaceManager**

Modify `workspace_manager.py`:

```python
class WorkspaceProject:
    # ... existing methods ...
    
    def import_davinci_project(self, dpa_path: Path, sip_library_dir: Path, 
                                mcal_config_dir: Optional[Path] = None,
                                target_project_dir: Optional[Path] = None,
                                confirm=None) -> Tuple["WorkspaceProject", "DaVinciImportReport"]:
        """Import a DaVinci XML project into format-8.
        
        Args:
            dpa_path: DaVinci XML .dpa
            sip_library_dir: Ingested SIP library directory
            mcal_config_dir: EB MCAL config directory (user prompted if None)
            target_project_dir: New format-8 project dir (user prompted if None)
            confirm: Callback for confirmations
        
        Returns:
            (new format-8 WorkspaceProject, DaVinciImportReport)
        """
        importer = DaVinciImporter()
        return importer.import_to_format8(dpa_path, sip_library_dir, mcal_config_dir, 
                                          target_project_dir, confirm)
```

- [ ] **Step 4: Write integration tests**

Create `tests/core/test_davinci_value_import.py`:

```python
def test_import_davinci_project():
    """E2E: import sample DaVinci StartApplication.dpa into format-8."""
    dva_path = TEST_PROJECT_ROOT / "StartApplication.dpa"
    sip_lib = TEST_SIP_LIBRARY  # from Task 2 test output
    mcal_dir = TEST_MCAL_CONFIG  # EB config dir
    target_dir = Path(tempfile.mkdtemp())
    
    project, report = WorkspaceProject.import_davinci_project(
        dva_path, sip_lib, mcal_dir, target_dir
    )
    
    # Verify project structure
    assert project.format_version == 8
    assert len(project.module_entries) == 28  # 22 BSW + 6 MCAL
    
    # Verify modules resolved
    os_entry = next(e for e in project.module_entries if e.name == "Os")
    assert os_entry.definition == "/MICROSAR/Os"
    
    # Verify import report
    assert report.total_modules == 28
    assert report.modules_imported == 28
    assert len(report.unresolved_refs) == 0
    assert report.mcal_modules_source == str(mcal_dir)
    
    # Verify no silent data loss
    assert not report.dropped_modules
```

Run: `pytest tests/core/test_davinci_value_import.py::test_import_davinci_project -xvs`
Expected: PASS (all 28 modules imported, 0 unresolved refs)

- [ ] **Step 5: Commit**

```bash
git add autosar_configurator/core/davinci_import.py autosar_configurator/core/workspace_manager.py tests/core/test_davinci_value_import.py
git commit -m "feat(davinci): import configuration values into format-8

- DaVinciImporter: load values from arxml and bind to SIP definitions
- WorkspaceProject.import_davinci_project(): E2E import workflow
- DaVinciImportReport: per-module stats, unresolved refs, dropped content
- Tests: 28-module import, all values preserved"
```

---

## Task 5: EB MCAL Resource Extraction from `.properties`

**Files:**
- Create: `autosar_configurator/core/mcal_resource_extractor.py`
- Modify: `autosar_configurator/core/packages/eb_plugin.py` (add resource extraction)
- Create: `autosar_configurator/tools/extract_mcal_resources.py` (CLI)
- Modify: `autosar_configurator/data/chips/*.yaml` (fill Port resources)
- Create: `tests/core/test_mcal_resource_extraction.py`

**Interfaces:**
- Consumes:
  - EB Resource plugin's `resource/CotexR52_<Chip>.properties` files
  - Chip YAML files (e.g., `THA6206_LFBGA292.yaml`)
- Produces:
  - `McalResourceExtractor.extract_from_properties(prop_path: Path) -> Dict[str, Any]` → Port resources
  - Updated chip YAML with `_source` field for traceability
  - CLI: `python -m autosar_configurator.tools.extract_mcal_resources --eb-plugins D:/path --chip THA6206_LFBGA292`

- [ ] **Step 1: Implement properties parser**

Create `mcal_resource_extractor.py`:

```python
class McalResourceExtractor:
    """Extract ECU resources from EB `.properties` files."""
    
    def extract_from_properties(self, prop_path: Path) -> Dict[str, Dict[str, Any]]:
        """Parse Resource plugin's .properties and extract Port/Spi/etc. resources.
        
        Args:
            prop_path: Path to CotexR52_<Chip>.properties
        
        Returns:
            Dict[module_name][resource_key] = value
            Example: {
              "Port": {
                "AvailableEXTIModule": ["_1_"],
                "AvailablePortsID": ["_0_", "_2_", "_10_", ...],
                "_source": "Def/plugins/Resource_THA6_AS440/resource/..."
              }
            }
        """
        result = {}
        
        # Parse .properties file (KEY:VALUE format)
        with open(prop_path, 'r') as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                
                # Port.AvailableEXTIModule: _1_
                if ":" in line:
                    key, value = line.split(":", 1)
                    key = key.strip()
                    value = value.strip()
                    
                    # Parse module.resource format
                    if "." in key:
                        module, resource = key.split(".", 1)
                        if module not in result:
                            result[module] = {}
                        
                        # Parse value (comma or space delimited)
                        if resource == "AvailablePortsID":
                            result[module][resource] = value.split()
                        else:
                            result[module][resource] = value.split()
        
        # Add source for traceability
        for module in result:
            result[module]["_source"] = str(prop_path)
        
        return result
```

- [ ] **Step 2: Integrate into EB plugin loader**

Modify `packages/eb_plugin.py`:

```python
def load_mcal_resources(plugin_dir: Path) -> Dict[str, Dict[str, Any]]:
    """Load MCAL ECU resources from Resource sibling plugin if available.
    
    The Resource plugin (Resource_THA6_AS440) contains resource/CotexR52_<Chip>.properties
    with Port.AvailableEXTIModule, AvailableGTMModule, AvailablePortsID, etc.
    """
    # Sibling plugin: replace "Port_THA6_AS440" with "Resource_THA6_AS440"
    parent = plugin_dir.parent
    resource_plugin = parent / "Resource_THA6_AS440"
    
    if not resource_plugin.exists():
        return {}
    
    # Look for resource/CotexR52_*.properties files
    resources = {}
    for prop_file in (resource_plugin / "resource").glob("CotexR52_*.properties"):
        extractor = McalResourceExtractor()
        chip_resources = extractor.extract_from_properties(prop_file)
        resources.update(chip_resources)
    
    return resources
```

- [ ] **Step 3: Write tests**

Create `tests/core/test_mcal_resource_extraction.py`:

```python
def test_extract_port_resources_from_properties():
    """Extractor parses .properties and returns Port resources."""
    prop_file = TEST_RESOURCE_DIR / "CotexR52_THA6206_LFBGA292.properties"
    extractor = McalResourceExtractor()
    resources = extractor.extract_from_properties(prop_file)
    
    assert "Port" in resources
    port = resources["Port"]
    assert port["AvailableEXTIModule"] == ["_1_"]
    assert port["AvailableGTMModule"] == ["_1_"]
    assert port["AvailablePortsID"] == ["_0_", "_2_", "_10_", "_11_", ...]
    assert "_source" in port

def test_extract_spi_resources():
    """Extractor also handles Spi resources."""
    prop_file = ...
    extractor = McalResourceExtractor()
    resources = extractor.extract_from_properties(prop_file)
    
    assert "Spi" in resources
    spi = resources["Spi"]
    assert "MaxHwUnit" in spi
    assert spi["_source"] is not None
```

- [ ] **Step 4: Update chip YAML files**

Script to fill Port resources from extracted data:

```python
def update_chip_yaml_from_resources(chip_yaml_path: Path, resources: Dict):
    """Update chip YAML with extracted Port resources."""
    import yaml
    
    with open(chip_yaml_path, 'r') as f:
        chip_data = yaml.safe_load(f)
    
    # Merge Port resources
    if "Port" in resources:
        if "Port" not in chip_data:
            chip_data["Port"] = {}
        chip_data["Port"].update(resources["Port"])
    
    with open(chip_yaml_path, 'w') as f:
        yaml.dump(chip_data, f, default_flow_style=False, sort_keys=False)
```

For THA6206_LFBGA292.yaml: replace `null` values with extracted values:

```yaml
Port:
  AvailableEXTIModule: [EXTI0, EXTI1]
  AvailableEXTIModuleNodeNumber: [1]
  AvailableGTMModule: [GTM0]
  AvailableGTMModuleNodeNumber: [8]
  AvailableIOMPINModule: null  # Not in Resource plugin
  AvailableIOMPINModuleNodeNumber: null
  AvailablePSI5Module: null
  AvailablePSI5ModuleNodeNumber: null
  AvailablePortsID: [P00, P02, P10, P11, P13, P14, P15, P20, P21, P22, P23, P32, P33, P34, P40, P41]
  _source: "test_import_project/Def/plugins/Resource_THA6_AS440/resource/CotexR52_THA6206_LFBGA292.properties"
```

- [ ] **Step 5: Commit**

```bash
git add autosar_configurator/core/mcal_resource_extractor.py autosar_configurator/core/packages/eb_plugin.py autosar_configurator/tools/extract_mcal_resources.py tests/core/test_mcal_resource_extraction.py autosar_configurator/data/chips/THA6206_LFBGA292.yaml
git commit -m "feat(mcal): extract Port ECU resources from EB Resource plugin

- McalResourceExtractor: parse .properties files
- Extract Port.AvailableEXTIModule, GTM, IOMPIN, PSI5, PortsID
- Record _source for traceability
- Update chip YAML with extracted values
- Resolve all 14 Port warnings on DaVinci import"
```

---

## Task 6: UI Integration — Import DaVinci Project Menu

**Files:**
- Modify: `autosar_configurator/ui/controllers/project_controller.py`
- Create: `autosar_configurator/ui/wizards/davinci_import_wizard.py`
- Create: `tests/ui/test_davinci_import_wizard.py`

**Interfaces:**
- Consumes:
  - `WorkspaceProject.import_davinci_project()` from Task 4
  - Qt dialogs (QFileDialog, QMessageBox, QProgressDialog)
- Produces:
  - "File → Import DaVinci Project..." menu entry
  - Import wizard: select .dpa → select/confirm SIP lib → select MCAL dir → target dir → run import
  - Progress dialog during import
  - Report dialog with link to markdown report file

- [ ] **Step 1: Add menu entry**

Modify `project_controller.py` (ProjectController.init_ui or similar):

```python
self.import_davinci_action = QAction("Import DaVinci Project...", self.win)
self.import_davinci_action.triggered.connect(self.on_import_davinci_project)
self.win.menu_file.addAction(self.import_davinci_action)
```

- [ ] **Step 2: Implement wizard**

Create `davinci_import_wizard.py`:

```python
class DaVinciImportWizard(QWizard):
    """Multi-step wizard for DaVinci project import."""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Import DaVinci Project")
        self.dpa_path = None
        self.sip_lib_path = None
        self.mcal_config_path = None
        self.target_dir = None
        
        # Page 1: Select DaVinci .dpa
        self.addPage(self._page_select_dpa())
        # Page 2: Select/confirm SIP library
        self.addPage(self._page_select_sip_lib())
        # Page 3: Select EB MCAL config dir
        self.addPage(self._page_select_mcal_dir())
        # Page 4: Select target project dir
        self.addPage(self._page_select_target_dir())
        # Page 5: Confirm and import
        self.addPage(self._page_confirm())
```

- [ ] **Step 3: Implement import handler**

Add to `project_controller.py`:

```python
def on_import_davinci_project(self):
    """Handle File → Import DaVinci Project menu action."""
    wizard = DaVinciImportWizard(self.win)
    if wizard.exec() == QWizard.Accepted:
        # Run import in background thread
        self._import_davinci_async(
            wizard.dpa_path,
            wizard.sip_lib_path,
            wizard.mcal_config_path,
            wizard.target_dir
        )

def _import_davinci_async(self, dpa_path, sip_lib, mcal_dir, target_dir):
    """Run DaVinci import in worker thread."""
    worker = DaVinciImportWorker(dpa_path, sip_lib, mcal_dir, target_dir)
    worker.finished.connect(self.on_import_davinci_finished)
    worker.error.connect(self.on_import_davinci_error)
    worker.start()

def on_import_davinci_finished(self, project, report):
    """Display import report dialog."""
    dialog = QMessageBox(self.win)
    dialog.setWindowTitle("Import Complete")
    dialog.setText(f"Imported {report.total_modules} modules\nSee report for details")
    dialog.setDetailedText(report.to_markdown())
    dialog.setStandardButtons(QMessageBox.Ok)
    dialog.exec()
    
    # Offer to open project
    reply = QMessageBox.question(self.win, "Open Project?", 
                                 "Open imported project now?",
                                 QMessageBox.Yes | QMessageBox.No)
    if reply == QMessageBox.Yes:
        self.on_open_project(str(project.project_file))
```

- [ ] **Step 4: Write UI tests**

Create `tests/ui/test_davinci_import_wizard.py`:

```python
def test_davinci_import_wizard_flow(qtbot):
    """Wizard flow: select files → confirm → import."""
    wizard = DaVinciImportWizard()
    qtbot.addWidget(wizard)
    
    # Page 1: Select .dpa
    dpa_input = wizard.findChild(QLineEdit, "dpa_path_input")
    dpa_input.setText(str(TEST_DPA_PATH))
    
    # ... fill other pages ...
    
    # Click Finish
    finish_btn = wizard.button(QWizard.FinishButton)
    qtbot.mouseClick(finish_btn, Qt.LeftButton)
    
    # Verify import completed
    # ...
```

- [ ] **Step 5: Commit**

```bash
git add autosar_configurator/ui/controllers/project_controller.py autosar_configurator/ui/wizards/davinci_import_wizard.py tests/ui/test_davinci_import_wizard.py
git commit -m "feat(ui): add Import DaVinci Project wizard

- File > Import DaVinci Project menu entry
- Multi-step wizard: select .dpa → SIP lib → MCAL dir → target
- Progress dialog during import
- Report display and project open on completion"
```

---

## Task 7: Regression and Acceptance Tests

**Files:**
- Create: `tests/core/test_davinci_regression.py`
- Modify: `tools/compare_generation.py` (existing from Phase 1)
- Create: `tests/integration/test_phase2_acceptance.py`

**Interfaces:**
- Consumes:
  - Ingested SIP library (from Task 2)
  - DaVinci sample project (StartApplication.dpa)
  - EB MCAL config directory
  - DaVinci baseline code (Config/GenData)
- Produces:
  - Regression proof: imported project generates byte-identical code
  - Acceptance: all 14 Port warnings gone, 28 modules load, 0 unresolved refs

- [ ] **Step 1: Generate code from imported project**

```python
def test_import_and_generate_matches_davinci():
    """E2E regression: import DaVinci → generate code → matches DaVinci baseline."""
    # Setup: prepare SIP lib, import project
    ...
    
    # Generate code with imported project
    gen_output_imported = Path(tempfile.mkdtemp())
    generator.generate(imported_project, gen_output_imported)
    
    # Compare to DaVinci baseline
    baseline_dir = TEST_PROJECT_ROOT / "Config" / "GenData"
    
    comparison = compare_generation_output(baseline_dir, gen_output_imported)
    
    # Expect 0 differences (modulo timestamps)
    assert comparison.total_files_compared > 0
    assert comparison.files_identical == comparison.total_files_compared
    assert comparison.files_different == 0
```

Run: `pytest tests/core/test_davinci_regression.py::test_import_and_generate_matches_davinci -xvs`
Expected: PASS (100% code match)

- [ ] **Step 2: Verify Port warnings gone**

```python
def test_import_davinci_resolves_port_warnings():
    """After import, Port.AvailableEXTIModule and friends are no longer null."""
    # Import project
    project, report = import_davinci_project(...)
    
    # Load Port module config
    port_module = next(e for e in project.module_entries if e.name == "Port")
    port_config = ConfigurationManager(project).load_module(port_module)
    
    # Verify ECU resources available
    ecu_resources = project.ecu_resource_resolver()
    
    port_resources = ecu_resources.get("Port", {})
    assert port_resources.get("AvailableEXTIModule") is not None
    assert port_resources.get("AvailableGTMModule") is not None
    assert port_resources.get("AvailablePortsID") is not None
```

- [ ] **Step 3: Run full test suite**

```bash
python -m pytest tests/ -q -p no:cacheprovider
```

Expected: All existing tests pass (no regressions), new tests pass (14 Port warnings gone, all 28 modules import).

- [ ] **Step 4: Commit**

```bash
git add tests/core/test_davinci_regression.py tests/integration/test_phase2_acceptance.py
git commit -m "test(phase2): regression and acceptance tests

- Generate code from imported DaVinci project
- Verify byte-identical output vs baseline
- Confirm all 14 Port ECU resource warnings resolved
- 28 BSW + 6 MCAL modules import with 0 unresolved refs"
```

---

## Summary

**After Task 7, you have:**

1. ✅ Vector SIP ingestion tool (CLI) — converts 110+ SIP modules to packages
2. ✅ DaVinci XML project parser — extracts all metadata
3. ✅ DaVinci import (E2E) — 28 BSW + 6 MCAL modules, format-8 project
4. ✅ MCAL ECU resources extracted — all 14 Port warnings gone
5. ✅ UI wizard — File → Import DaVinci Project
6. ✅ Regression proof — generated code matches DaVinci baseline byte-for-byte
7. ✅ Acceptance — import real DaVinci project, generate, compare, verify

**Remaining for Phase 3+:**
- MemMap header generation (subproject 2)
- System description import (subproject 10, critical for communications)
- RTE + OS reverse inference (subproject 9)
