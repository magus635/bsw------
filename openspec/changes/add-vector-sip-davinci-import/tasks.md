# Implementation Tasks

## 1. Vector SIP Library Ingestion Tool

- [ ] 1.1 Create `sip_import.py` module with SIP scanner
- [ ] 1.2 Implement BSWMD file discovery (Components/*/BSWMD/, recursive)
- [ ] 1.3 Implement AUTOSAR path-based element merging
- [ ] 1.4 Add conflict detection (type mismatch, single-value field conflicts)
- [ ] 1.5 Implement derivative subdirectory selection (DerivativeMapping_*.xml)
- [ ] 1.6 Extract BSW-IMPLEMENTATION (version, vendor, memory sections, Pre/Rec refs)
- [ ] 1.7 Generate module.json + config/ module packages
- [ ] 1.8 Add CLI entry point (e.g., `python -m autosar_configurator.tools.ingest_sip`)
- [ ] 1.9 Write unit tests for merging logic
- [ ] 1.10 Write integration test with sample SIP subset

## 2. DaVinci Project Import

- [ ] 2.1 Add DaVinci XML `.dpa` parser (extract SIP, Derivative, Folders, ECUC/Active)
- [ ] 2.2 Implement `WorkspaceManager.import_davinci_project()` method
- [ ] 2.3 Add UI menu "Import DaVinci Project" in project_controller.py
- [ ] 2.4 Add EB MCAL directory selection dialog (with auto-detection)
- [ ] 2.5 Import BSW module configurations from DaVinci ARXMLs
- [ ] 2.6 Import MCAL modules via existing EB import flow
- [ ] 2.7 Generate format-8 `.dpa` to new directory
- [ ] 2.8 Implement import report generation (container/param counts, unresolved items)
- [ ] 2.9 Add validation: every module has definition, all references resolve
- [ ] 2.10 Write integration test: import StartApplication.dpa, verify 28 modules
- [ ] 2.11 Add acceptance test: compare generated code to DaVinci baseline

## 3. EB MCAL Resource Extraction

- [ ] 3.1 Enhance eb_plugin.py to parse autosar/*.arxml files
- [ ] 3.2 Extract Port ECU resources (AvailableEXTIModule, GTM, IOMPIN, PSI5, PortsID)
- [ ] 3.3 Merge extracted resources into chips/<Chip>.yaml
- [ ] 3.4 Record ARXML source for each resource (traceability)
- [ ] 3.5 Add unit tests for resource extraction
- [ ] 3.6 Verify all 14 Port warnings disappear after import

## 4. Documentation and Polish

- [ ] 4.1 Update README: add "Import DaVinci Project" workflow
- [ ] 4.2 Document SIP ingestion CLI usage
- [ ] 4.3 Add troubleshooting guide for common import issues
- [ ] 4.4 Update CLAUDE.md with new import paths

## 5. Validation and Sign-off

- [ ] 5.1 Run full test suite (2381+ tests must pass)
- [ ] 5.2 Verify no regressions in existing EB import
- [ ] 5.3 Run `openspec validate add-vector-sip-davinci-import --strict`
- [ ] 5.4 User acceptance: import real DaVinci project, verify warnings gone
- [ ] 5.5 Code review

## Checkpoints

After Task 1: SIP ingestion tool working, can convert vBRS module from SIP to package
After Task 2: Can import StartApplication.dpa, all 28 modules load, definitions resolve
After Task 3: All 14 Port ECU resource warnings gone
After Task 5: Ready to merge
