// Linker snippet to include LMU memory

memory lmu
{
    mau = 8;
    size = 32k;
    type = reserved ram;
    map     cached (dest=bus:sri, dest_offset=0x90000000,           size=32k);
    map not_cached (dest=bus:sri, dest_offset=0xb0000000, reserved, size=32k);
}
