[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_CanIf.h CSL Template */!]
#if !defined (PDUR_CANIF_H)
# define PDUR_CANIF_H

#include "PduR_Cfg.h"

#define PDUR_START_SEC_CODE
# include "PduR_MemMap.h"

FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(PduIdType TxPduId);

#define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h"

#endif /* PDUR_CANIF_H */
