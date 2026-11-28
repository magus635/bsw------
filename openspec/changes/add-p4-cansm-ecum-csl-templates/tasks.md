## 1. OpenSpec
- [x] 1.1 Create and strictly validate `openspec/changes/add-p4-cansm-ecum-csl-templates/`

## 2. Template Audit Pack Override
- [x] 2.1 Add `template_pack_dir: Optional[Path] = None` support to `audit_project_templates()` (`autosar_configurator/generator/template_audit.py`)
- [x] 2.2 Add `--template-pack` CLI option to `tools/audit_templates.py`

## 3. CanSM CSL EB Template Pack
- [x] 3.1 Author `template_packs/davinci/CanSM/include/CanSM_Cfg.h` with full MICROSAR CSL macros, feature switches, timing conversions, typedefs, and MemMap declarations
- [x] 3.2 Author `template_packs/davinci/CanSM/src/CanSM_Lcfg.c` with `CanSM_ChannelVarRecord[]` and multi-channel `CanSM_ChannelConfig[]` definitions

## 4. EcuM CSL EB Template Pack
- [x] 4.1 Author `template_packs/davinci/EcuM/include/EcuM_Generated_Types.h`, `EcuM_Cfg.h`, `EcuM_PrivateCfg.h`, `EcuM_Init_Cfg.h`, and `EcuM_Init_PBcfg.h`
- [x] 4.2 Author `template_packs/davinci/EcuM/src/EcuM_Cfg.c`, `EcuM_Init_Cfg.c`, `EcuM_Init_PBcfg.c`, and `EcuM_PBcfg.c`

## 5. Verification
- [x] 5.1 Create `tests/generator/test_p4_cansm_ecum_templates.py` covering synthetic configs, clang `--target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and read-only `StartApplication1.dpa` parity audit
- [x] 5.2 Run pytest suite, `tools/audit_templates.py --template-pack template_packs/davinci`, and `openspec validate add-p4-cansm-ecum-csl-templates --strict`, then mark all tasks complete
