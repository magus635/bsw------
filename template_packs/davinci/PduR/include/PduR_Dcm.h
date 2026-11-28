[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_Dcm.h CSL Template */!]
#if !defined (PDUR_DCM_H)
# define PDUR_DCM_H

#include "PduR_Cfg.h"

#define PDUR_START_SEC_CODE
# include "PduR_MemMap.h"

FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
[!IF "node:exists(as:modconf('PduR')[1]/Dcm/PduRCancelTransmit) and as:modconf('PduR')[1]/Dcm/PduRCancelTransmit = 'true'"!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelTransmit(PduIdType id);
[!ELSE!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelTransmit(PduIdType id);
[!ENDIF!][!//

#define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h"

#endif /* PDUR_DCM_H */
