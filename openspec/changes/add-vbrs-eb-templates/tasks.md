# Tasks: add-vbrs-eb-templates

## 0. Housekeeping
- [ ] 0.1 Delete `openspec/changes/add-vbrs-code-templates`, `docs/superpowers/specs/2026-11-05-vbrs-code-templates-design.md` and `docs/superpowers/plans/2026-11-06-vbrs-*` in the same commit as this proposal. Keep `stash@{0}` until this change is merged.

## 1. Feasibility spike (blocks everything below)
- [ ] 1.1 Copy the sample's Vector static code (`Appl/Source`, `Appl/Include`) to a temp folder. Compile BrsHw/BrsMain with armclang and `-DBRS_COMP_LLVMHIGHTEC`, using the sample's generated `vBrsCfg.h`/`vBrs_Lcfg.*`/`vLinkGen_*`.
- [ ] 1.2 Link with a hand-written scatter. Map `_STACK_C<n>_LIMIT`, `_OS_EXCVEC_CORE<n>_CODE_START` and one `_X_START` label to `Image$$` symbols (steering-file `RESOLVE … AS …` or another way that needs no static-code change).
- [ ] 1.3 Write down the result. If it needs any change to Vector static code, stop and ask the user.

## 2. Startup step comparison
- [ ] 2.1 Compare vendor `startup.c` with BrsHw `ARMStartup_CortexR52.c`/`BrsHw.c` step by step. Cover mode stacks, TCM config registers, Hyp/temporary stacks, slave-core start and `UNCLEAR_RAM_BSS`.
- [ ] 2.2 For each gap, record who covers it: the tables, a callout in `BrsMain_Callout_Stubs.c`, or a question to the user. Draft the callout code.

## 3. Chip data
- [ ] 3.1 THA6206: set `cpu_frequency` to 400 MHz.
- [ ] 3.2 Add fields:
  - Vector derivative id (`Tongxin_THA6206`) and core type (`CORTEX_R52`);
  - per-window ECC granularity: TCM 8, other RAM 4, flagged unconfirmed;
  - per-window block-init owner, filled from vendor `startup.c`'s ITMU list.
- [ ] 3.3 Loader and chip-completeness tests for the new fields. Missing values are flagged, never invented.

## 4. Multiline string parameters
- [ ] 4.1 Parse ECUC-MULTILINE-STRING definitions and values. Save them back unchanged. Edit them as multiline text in the config panel.
- [ ] 4.2 Tests: round trip of `vBRSMakefileUserCode`; the panel shows and edits multiline text.

## 5. Reference outputs and branch inventory
- [ ] 5.1 List every branch of the JET classes `BrsCfgH`, `vBrs_LcfgC`, `vBrs_LcfgH`, `MakefileConfigGenerated` (javap) and the vBRS/Os/chip input each branch reads.
- [ ] 5.2 Write `tools/vbrs_reference`. It copies the sample project, sets the dpa SIP path, applies one vBRS/Os value change per case and runs `DVCfgCmd -g -m /MICROSAR/vBRS`. It stores outputs with the Vector header stripped as `tests/fixtures/vbrs/<case>/`. Paths come from env vars; nothing under `D:\davinci` is written.
- [ ] 5.3 Generate the matrix: sample plus at least one case per branch from 5.1.

## 6. vBRS templates
- [ ] 6.1 Explicit output names for template-pack files (`vBrsCfg.h`, `vBrs_Lcfg.h`, `vBrs_Lcfg.c`, `Makefile.config.generated`), with tests.
- [ ] 6.2 Add only the engine functions the templates need, each with unit tests.
- [ ] 6.3 Templates in `template_packs/vBRS/`, using the tool's own file header. Refuse with a reason when the vBRS module, the Os core mapping, a core's start-up stack region or the chip's core type/frequency is missing.
- [ ] 6.4 Parity test: every fixture case from 5.3 renders byte-identical after header strip.
- [ ] 6.5 Fingerprint stability check for the new outputs.

## 7. Memory layout
- [ ] 7.1 Optional per-region fields: init stage, owning core, alignment (0/4/8). Old config files load unchanged.
- [ ] 7.2 `STACK_C<n>` start-up stack regions in each core's TCM, and `OS_EXCVEC_CORE<n>_CODE` as required region names. Size check against six mode stacks plus a margin.
- [ ] 7.3 Tests for 7.1 and 7.2.

## 8. Init tables
- [ ] 8.1 Derive table entries from the plan:
  - copy for load ≠ exec;
  - zero for ZI;
  - one entry per core on core-local alias windows;
  - Early blocks from the chip's block-init windows;
  - sorted by region name.
- [ ] 8.2 Coverage check: generation is refused when an RW/ZI or copied region has no entry.
- [ ] 8.3 ADS label profile in `symbols.py` (`Image$$…`, `Load$$…`). Generate `vLinkGen_Cfg.h`, `vLinkGen_Lcfg.h`, `vLinkGen_Lcfg.c` next to the scatter file. The scatter file and the generation report state that `--datacompressor=off` is required.
- [ ] 8.4 Tests:
  - structure line-by-line against the sample (types, macros, table and set names, empty-table form, entry format);
  - table contents from layout fixtures.

## 9. ADS link check
- [ ] 9.1 `tools/brs_link_check`, modelled on `tools/os_port_check`. It copies the static code to temp, compiles it with the generated files and Os/EcuM stubs, and links with the generated scatter (plus the mapping from 1.2).
- [ ] 9.2 It checks from the map: every label resolved; each table entry equals its region's bounds and load address; each start-up stack end equals `STACK_C<n>` limit.
- [ ] 9.3 Pytest wrapper, skipped without the ADS env vars. Run it on the THA6206 sample layout.

## 10. Verification
- [ ] 10.1 Full test suite. Only the 14 known unrelated failures may remain.
- [ ] 10.2 `openspec validate add-vbrs-eb-templates --strict`.
