// Linker snippet to include OLDA memory

memory olda
{
    mau = 8;
    size = 16k;
    type = reserved ram;
    map (dest=bus:sri, dest_offset=0xafe00000, size=16k);
}
