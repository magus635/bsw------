[!SELECT "as:modconf('CanIf')[1]"!][!//
[!VAR "trcvInfix" = "'CanTrcv_30_Tle9255'"!][!//
[!IF "node:exists(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorApiInfix)"!][!//
[!VAR "vId" = "num:i(30)"!][!//
[!IF "node:exists(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorId)"!][!//
[!VAR "vId" = "num:i(node:value(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorId))"!][!//
[!ENDIF!][!//
[!VAR "vInf" = "string:trim(node:value(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorApiInfix))"!][!//
[!IF "string-length($vInf) > 0"!][!//
[!VAR "trcvInfix" = "concat('CanTrcv_', $vId, '_', $vInf)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
#if !defined(CANIF_CANTRCV_H)
#define CANIF_CANTRCV_H

#include "[!"$trcvInfix"!].h"

#endif /* CANIF_CANTRCV_H */
[!ENDSELECT!]
