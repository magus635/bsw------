[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_Com.h CSL Template */!]
#if !defined (PDUR_COM_H)
# define PDUR_COM_H

#include "PduR_Cfg.h"

#define PDUR_START_SEC_CODE
# include "PduR_MemMap.h"

FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);

#define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h"

#endif /* PDUR_COM_H */
