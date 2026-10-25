/* Minimal compilertypes.h for the SC300 (Cortex-M3) build check; the target SDK has the real one. */
#ifndef COMPILERTYPES_H_
#define COMPILERTYPES_H_

#ifdef __ASSEMBLER__
#define SECTION_ASM(name, ctrIns, opt)  .section name, ctrIns
#define GLOBAL_ASM                      .global
#define TYPE_ASM(name, typeclass)       .type name, %function
#define SP_FORCE_ALIGN_ASM(cmd)         .eabi_attribute cmd, 1
#define END_FILE
#endif

#endif /* COMPILERTYPES_H_ */
