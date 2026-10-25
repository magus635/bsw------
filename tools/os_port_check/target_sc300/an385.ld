/* QEMU mps2-an385: SSRAM1 at 0x00000000 (code), SSRAM2/3 at 0x20000000 (data) */
MEMORY
{
    CODE (rx)  : ORIGIN = 0x00000000, LENGTH = 4M
    DATA (rwx) : ORIGIN = 0x20000000, LENGTH = 4M
}
ENTRY(Reset_Handler)
SECTIONS
{
    .text : {
        KEEP(*(.vectors))
        *(.text*) *(.exceptionHandler*) *(.rodata*)
        . = ALIGN(4);
    } > CODE
    __data_load = LOADADDR(.data);
    .data : { __data_start = .; *(.data*) . = ALIGN(4); __data_end = .; } > DATA AT > CODE
    .bss (NOLOAD) : { __bss_start = .; *(.bss*) *(COMMON) . = ALIGN(4); __bss_end = .; } > DATA
    . = ALIGN(8);
    . = . + 0x4000;
    __stack_top = .;
}
