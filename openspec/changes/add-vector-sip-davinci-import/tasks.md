# Implementation Tasks

## 1. Vector SIP Library Ingestion Tool

- [x] 1.1 Create `sip_import.py` module with SIP scanner (`SipScanner` in `davinci_importer.py`)
- [x] 1.2 Implement BSWMD file discovery (Components/*/BSWMD/, DemoComponents/*/BSWMD/, recursive)
- [x] 1.3 Implement AUTOSAR path-based element merging (`SipMerger`)
- [x] 1.4 Add conflict detection (type mismatch, single-value field conflicts, duplicate component defs -> `SipMergeError`)
- [x] 1.5 Implement derivative subdirectory selection (`DerivativeMapping_*.xml`)
- [x] 1.6 Extract BSW-IMPLEMENTATION (version, vendor, memory sections, required artifacts, Pre/Rec refs)
- [x] 1.7 Generate `module.json` + `sources.json` + `config/` module packages (`SipPackageWriter`)
- [x] 1.8 Add CLI entry point (`python -m autosar_configurator.core.davinci_import_cli`)
- [x] 1.9 Write unit tests for merging logic (`test_davinci_importer_real.py`, `test_import_merge_fixes.py`)
- [x] 1.10 Write integration test with sample SIP subset (`test_task5_end_to_end.py`)

## 2. DaVinci Project Import

- [x] 2.1 Add DaVinci XML `.dpa` parser (extract SIP, Derivative, Folders, ECUC/Active, EcucSplitter)
- [x] 2.2 Implement `WorkspaceManager.import_davinci_project()` method (`DaVinciProjectImporter`)
- [x] 2.3 Add UI menu "Import from DaVinci Project..." in `davinci_main_window.py` / `project_controller.py`
- [x] 2.4 Add EB MCAL directory selection dialog (with auto-detection)
- [x] 2.5 Import BSW module configurations from DaVinci ARXMLs
- [x] 2.6 Import MCAL modules via existing EB import flow
- [x] 2.7 Generate format-8 `.dpa` to new directory
- [x] 2.8 Implement import report generation (container/param counts, unresolved items)
- [x] 2.9 Add validation: every module has definition, all references resolve
- [x] 2.10 Write integration test: import StartApplication.dpa, verify 28 modules (`test_davinci_project_import_e2e.py` + real DPA verified)
- [ ] 2.11 Add acceptance test: compare generated code to DaVinci baseline（依赖后续各模块代码生成模板路线图项）

## 3. EB MCAL Resource Extraction

- [x] 3.1 Enhance `eb_plugin.py` / `McalResourceExtractor` to parse plugin resources & properties files
- [ ] 3.2 Extract Port ECU resources (AvailableEXTIModule, GTM, IOMPIN, PSI5, PortsID)（原厂 THA6206 .properties 与 DaVinci 配置中均不含该 8 项键，需按芯片手册人工确认）
- [ ] 3.3 Merge extracted resources into chips/<Chip>.yaml（同上：需按芯片手册确认后再写入以避免破坏校验和）
- [x] 3.4 Record source file path for each extracted resource (`_source` traceability)
- [x] 3.5 Add unit tests for resource extraction (`test_task3_mcal_resources.py`, `test_phase2_lifecycle.py`)
- [ ] 3.6 Verify all 14 Port warnings disappear after import（同 3.2/3.3：剩余 8 条为 THA6206 原厂缺失的 `待填写` 键）

## 4. Documentation and Polish

- [x] 4.1 Update README: add "Import DaVinci Project" workflow
- [x] 4.2 Document SIP ingestion CLI usage
- [x] 4.3 Add troubleshooting guide for common import issues
- [x] 4.4 Update CLAUDE.md with new import paths

## 5. Validation and Sign-off

- [x] 5.1 Run test suites (`246 passed` Phase 1/UI + `49 passed` Phase 2/3 + `259 passed` chip/DaVinci E2E suites)
- [x] 5.2 Verify no regressions in existing EB import
- [x] 5.3 Run `openspec validate add-vector-sip-davinci-import --strict`
- [x] 5.4 User acceptance: import real StartApplication.dpa (28/28 modules loaded in UI)
- [x] 5.5 Code review

## Checkpoints

After Task 1: SIP ingestion tool working, can convert vBRS module from SIP to package
After Task 2: Can import StartApplication.dpa, all 28 modules load, definitions resolve
After Task 3: All 14 Port ECU resource warnings gone
After Task 5: Ready to merge
