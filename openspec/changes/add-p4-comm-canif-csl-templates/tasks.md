## 1. OpenSpec
- [ ] 1.1 Create and strictly validate `openspec/changes/add-p4-comm-canif-csl-templates/`

## 2. CanIf CSL EB Template Pack
- [ ] 2.1 Author `template_packs/davinci/CanIf/include/{CanIf_Can.h,CanIf_CanTrcv.h,CanIf_Cfg.h}`
- [ ] 2.2 Author `template_packs/davinci/CanIf/src/{CanIf_Lcfg.c,CanIf_PBcfg.c}`

## 3. ComM CSL EB Template Pack
- [ ] 3.1 Author `template_packs/davinci/ComM/include/{ComM_GenTypes.h,ComM_Lcfg.h,ComM_Cfg.h,ComM_Private_Cfg.h}`
- [ ] 3.2 Author `template_packs/davinci/ComM/src/ComM_Lcfg.c`

## 4. Verification
- [ ] 4.1 Create `tests/generator/test_p4_comm_canif_templates.py` covering synthetic configs, clang `--target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and read-only `StartApplication1.dpa` parity audit
- [ ] 4.2 Run pytest suite, `tools/audit_templates.py --template-pack template_packs/davinci`, and `openspec validate add-p4-comm-canif-csl-templates --strict`, then mark all tasks complete
