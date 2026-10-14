// Linker snippet to include OLDA memory

  OLDA_NonCached : ORIGIN = 0xAFE00000 , LENGTH = 0x00004000 /* 16 KiB */

  .arti ALIGN(16) :
  {
    arti.o(.bss)
  } > OLDA_NonCached
  _arti_START = ADDR(.arti);
  _arti_END = ENDADDR(.arti) - 1;
  _arti_LIMIT = ENDADDR(.arti);

  _arti_ALL_START = _arti_START;
  _arti_ALL_END = _arti_END;
  _arti_ALL_LIMIT = _arti_LIMIT;
