/* Minimal datatypes.h for the SC300 (Cortex-M3) build check; the target SDK has the real one.
 * uint32 is unsigned long, as in the SDK, so the types match the real build. */
#ifndef DATATYPES_H_
#define DATATYPES_H_

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;
typedef signed long long    sint64;
typedef unsigned char       boolean;
typedef float               float32;
typedef double              float64;
typedef unsigned long       uintptr_t;

#endif /* DATATYPES_H_ */
