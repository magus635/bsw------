## 1. OpenSpec Proposal
- [x] 1.1 Create proposal, design, tasks, and capability spec in `openspec/changes/add-p4-cantp-pdur-csl-templates/`
- [x] 1.2 Validate OpenSpec change strictly (`openspec validate add-p4-cantp-pdur-csl-templates --strict`)

## 2. CanTp CSL Template Pack
- [x] 2.1 Implement `template_packs/davinci/CanTp/include/CanTp_Cfg.h`
- [x] 2.2 Implement `template_packs/davinci/CanTp/include/CanTp_Lcfg.h` and `include/CanTp_PBcfg.h`
- [x] 2.3 Implement `template_packs/davinci/CanTp/src/CanTp_Lcfg.c` and `src/CanTp_PBcfg.c`

## 3. PduR CSL Template Pack
- [x] 3.1 Implement `template_packs/davinci/PduR/include/PduR_Types.h`, `PduR_Cfg.h`, `PduR_PBcfg.h`, `PduR_CanIf.h`, `PduR_CanTp.h`, `PduR_Com.h`, `PduR_Dcm.h`
- [x] 3.2 Implement `template_packs/davinci/PduR/include/PduR_Lcfg.h`
- [x] 3.3 Implement `template_packs/davinci/PduR/src/PduR_Lcfg.c` and `src/PduR_PBcfg.c`

## 4. Tests & Parity Verification
- [x] 4.1 Create `tests/generator/test_p4_cantp_pdur_templates.py` with synthetic generation, `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror` syntax checks, and `StartApplication1.dpa` parity assertions
- [x] 4.2 Run pytest across Batch 1-3 + platform/audit suites and run `tools/audit_templates.py --fail-on-error`
- [x] 4.3 Validate OpenSpec (`openspec validate add-p4-cantp-pdur-csl-templates --strict`) and mark all tasks complete
