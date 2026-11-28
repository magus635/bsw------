# ComM and CanIf MICROSAR CSL Templates Capability

## ADDED Requirements

### Requirement: CanIf MICROSAR CSL Header and Lcfg Generation
`template_packs/davinci/CanIf` SHALL generate all five Vector MICROSAR headers and sources (`CanIf_Can.h`, `CanIf_CanTrcv.h`, `CanIf_Cfg.h`, `CanIf_Lcfg.c`, and `CanIf_PBcfg.c`) with full ComStackLib (`CSL`) switches, symbolic controller/transceiver/PDU handles, mailbox and buffer tables, upper-layer callback dispatch lists, and union RAM structures.

#### Scenario: Rendering CanIf CSL outputs from CAN controller, buffer, and Tx/Rx PDU configs
- **WHEN** `CodeGenerator.generate_all()` renders `template_packs/davinci/CanIf` on a `CanIf` configuration with controllers, HTH/HRH, Tx buffers, transceivers, and Tx/Rx PDUs
- **THEN** all five files emit with zero unexpanded `[!` tags, compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and match >=95% of `StartApplication` `#define`s and 100% of `CONST/VAR` symbols

### Requirement: ComM MICROSAR CSL Header and Lcfg Generation
`template_packs/davinci/ComM` SHALL generate all five Vector MICROSAR headers and sources (`ComM_GenTypes.h`, `ComM_Lcfg.h`, `ComM_Cfg.h`, `ComM_Private_Cfg.h`, and `ComM_Lcfg.c`) with full CSL switches, user/channel symbolic constants, per-channel union structs, `ComM_Private_Cfg.h` accessors, and per-channel `ComM_MainFunction_<Ch>` dispatchers.

#### Scenario: Rendering ComM CSL outputs from channel and user configs
- **WHEN** `CodeGenerator.generate_all()` renders `template_packs/davinci/ComM` on single-channel or multi-channel `ComM` configurations
- **THEN** all five files emit with zero unexpanded `[!` tags, compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and match >=95% of `StartApplication` `#define`s and 100% of `CONST/VAR` symbols
