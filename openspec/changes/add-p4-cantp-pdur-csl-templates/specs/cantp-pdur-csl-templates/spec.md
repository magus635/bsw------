## ADDED Requirements

### Requirement: CanTp Vector MICROSAR CSL Template Pack
The generator SHALL provide a Vector MICROSAR ComStackLib (`CSL`) EB Tresos template pack for `CanTp` under `template_packs/davinci/CanTp/` generating the complete 5-file configuration surface (`include/CanTp_Cfg.h`, `include/CanTp_Lcfg.h`, `include/CanTp_PBcfg.h`, `src/CanTp_Lcfg.c`, `src/CanTp_PBcfg.c`).

#### Scenario: CanTp symbolic names, CSL switches, and timing tables generated
- **WHEN** `CodeGenerator` renders `CanTp` for `StartApplication1.dpa` or a synthetic ECUC configuration containing physical and functional RxNSdus and TxNSdus
- **THEN** all 5 `CanTp` files render with zero unexpanded `[!` tags, compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and achieve `>=95%` `#define` parity and `100%` `CONST/VAR` symbol parity against reference GenData.

### Requirement: PduR Vector MICROSAR CSL Template Pack
The generator SHALL provide a Vector MICROSAR ComStackLib (`CSL`) EB Tresos template pack for `PduR` under `template_packs/davinci/PduR/` generating the complete 10-file configuration surface (`include/PduR_Types.h`, `include/PduR_Cfg.h`, `include/PduR_Lcfg.h`, `include/PduR_PBcfg.h`, `include/PduR_CanIf.h`, `include/PduR_CanTp.h`, `include/PduR_Com.h`, `include/PduR_Dcm.h`, `src/PduR_Lcfg.c`, `src/PduR_PBcfg.c`).

#### Scenario: PduR routing tables, module dispatch descriptors, and CSL accessor macros generated
- **WHEN** `CodeGenerator` renders `PduR` for `StartApplication1.dpa` or a synthetic multi-module ECUC configuration (`CanIf`, `CanTp`, `Com`, `Dcm`) with IF and TP routing paths
- **THEN** all 10 `PduR` files render with zero unexpanded `[!` tags, compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and achieve `>=95%` `#define` parity and `100%` `CONST/VAR` symbol parity against reference GenData.
