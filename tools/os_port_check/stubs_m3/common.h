/* Minimal common.h for the SC300 (Cortex-M3) build check; the target SDK has the real one. */
#ifndef COMMON_H_
#define COMMON_H_

#include "Platform_Types.h"
#include "compilertypes.h"

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif
#ifndef TRUE
#define TRUE ((boolean)(1U))
#endif
#ifndef FALSE
#define FALSE ((boolean)(0U))
#endif
#ifndef STD_ON
#define STD_ON (1U)
#endif
#ifndef STD_OFF
#define STD_OFF (0U)
#endif
#ifndef PARAM_UNUSED
#define PARAM_UNUSED(param) ((void)(param))
#endif

#endif /* COMMON_H_ */
