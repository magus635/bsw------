[!SELECT "as:modconf('ComM')[1]"!][!//
[!VAR "numChannels" = "num:i(count(ComMConfigSet/ComMChannel/*))"!][!//
[!IF "$numChannels < 1"!][!VAR "numChannels" = "num:i(1)"!][!ENDIF!][!//
#if !defined(COMM_GENTYPES_H)
#define COMM_GENTYPES_H

#if !defined (COMM_LOCAL)
# define COMM_LOCAL                                static
#endif

#if !defined (COMM_LOCAL_INLINE)
# define COMM_LOCAL_INLINE                         LOCAL_INLINE
#endif

#include "Rte_ComM_Type.h"

typedef struct ComM_InhibitionTypeTag
{
  ComM_InhibitionStatusType ComM_ECUGroupClassification;
  uint16 ComM_InhibitCnt;
  ComM_InhibitionStatusType ComM_InhibitionStatus[[!"$numChannels"!]u];
} ComM_InhibitionType;

#endif /* COMM_GENTYPES_H */
[!ENDSELECT!]
