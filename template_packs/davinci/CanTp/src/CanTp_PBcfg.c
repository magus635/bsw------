[!AUTOSPACING!]
[!/* Vector MICROSAR CanTp_PBcfg.c CSL Template */!]
#define CANTP_PBCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanTp_Lcfg.h"
#include "CanTp_PBcfg.h"
#if (CANTP_LOLAYER_CANIF == STD_ON)
# include "CanIf.h"
#endif
#include "PduR_CanTp.h"
