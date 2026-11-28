[!AUTOSPACING!]
[!/* Vector MICROSAR CanTp_Lcfg.h CSL Template */!]
#if !defined(CANTP_LCFG_H)
#define CANTP_LCFG_H

#include "CanTp_Types.h"
#include "Os.h"
#include "CanTp_PBcfg.h"

[!VAR "numRxSdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)])"!][!//
[!VAR "numTxSdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)])"!][!//
[!VAR "numRxNPdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)])"!][!//
[!IF "$numRxNPdus = 0"!][!VAR "numRxNPdus" = "$numRxSdus"!][!ENDIF!][!//

/* Typedefs - Sizes & Iterators */
typedef uint8 CanTp_SizeOfCalcBSType;
typedef uint8 CanTp_SizeOfPartitionIdentifiersType;
typedef uint8 CanTp_SizeOfRxPdu2RxSduIndType;
typedef uint8 CanTp_SizeOfRxPdu2TxSduIndType;
typedef uint8 CanTp_SizeOfRxPduMapType;
typedef uint8 CanTp_SizeOfRxSduCfgType;
typedef uint8 CanTp_SizeOfRxSduSnv2HdlType;
typedef uint8 CanTp_SizeOfRxStateType;
typedef uint8 CanTp_SizeOfTxPdu2RxSduIndType;
typedef uint8 CanTp_SizeOfTxPdu2TxSduIndType;
typedef uint8 CanTp_SizeOfTxPduMapType;
typedef uint8 CanTp_SizeOfTxSduCfgType;
typedef uint8 CanTp_SizeOfTxSduSnv2HdlType;
typedef uint8 CanTp_SizeOfTxSemaphoresType;
typedef uint8 CanTp_SizeOfTxStateType;

typedef uint8_least CanTp_CalcBSIterType;
typedef uint8_least CanTp_PartitionIdentifiersIterType;
typedef uint8_least CanTp_RxPdu2RxSduIndIterType;
typedef uint8_least CanTp_RxPdu2TxSduIndIterType;
typedef uint8_least CanTp_RxPduMapIterType;
typedef uint8_least CanTp_RxSduCfgIterType;
typedef uint8_least CanTp_RxSduSnv2HdlIterType;
typedef uint8_least CanTp_RxStateIterType;
typedef uint8_least CanTp_TxPdu2RxSduIndIterType;
typedef uint8_least CanTp_TxPdu2TxSduIndIterType;
typedef uint8_least CanTp_TxPduMapIterType;
typedef uint8_least CanTp_TxSduCfgIterType;
typedef uint8_least CanTp_TxSduSnv2HdlIterType;
typedef uint8_least CanTp_TxSemaphoresIterType;
typedef uint8_least CanTp_TxStateIterType;
typedef uint8_least CanTp_PCPartitionConfigIterType;

/* Field Typedefs */
typedef uint8 CanTp_CalcBSType;
typedef uint32 CanTp_CompatibilityVersionType;
typedef uint8 CanTp_PCPartitionConfigIdxOfPartitionIdentifiersType;
typedef uint8 CanTp_RxPdu2RxSduIndType;
typedef uint8 CanTp_RxPdu2TxSduIndType;
typedef uint8 CanTp_AddressingFormatOfRxPduMapType;
typedef boolean CanTp_GenericConnectionOfRxPduMapType;
typedef boolean CanTp_PduMetadataOfRxPduMapType;
typedef uint8 CanTp_RxPdu2RxSduEndIdxOfRxPduMapType;
typedef uint8 CanTp_RxPdu2RxSduPartitionIdxOfRxPduMapType;
typedef uint8 CanTp_RxPdu2RxSduStartIdxOfRxPduMapType;
typedef boolean CanTp_RxPdu2RxSduUsedOfRxPduMapType;
typedef uint8 CanTp_RxPdu2TxSduEndIdxOfRxPduMapType;
typedef uint8 CanTp_RxPdu2TxSduPartitionIdxOfRxPduMapType;
typedef uint8 CanTp_RxPdu2TxSduStartIdxOfRxPduMapType;
typedef boolean CanTp_RxPdu2TxSduUsedOfRxPduMapType;
typedef uint8 CanTp_BlockSizeOfRxSduCfgType;
typedef uint8 CanTp_CanTypeOfRxSduCfgType;
typedef uint8 CanTp_ChannelModeOfRxSduCfgType;
typedef boolean CanTp_GenericConnectionOfRxSduCfgType;
typedef PduIdType CanTp_LoLayerTxFcPduIdOfRxSduCfgType;
typedef uint8 CanTp_NArOfRxSduCfgType;
typedef uint8 CanTp_NBrOfRxSduCfgType;
typedef uint8 CanTp_NCrOfRxSduCfgType;
typedef PduIdType CanTp_PduRRxSduIdOfRxSduCfgType;
typedef uint8 CanTp_RxAddressOfRxSduCfgType;
typedef uint8 CanTp_RxAddressingFormatOfRxSduCfgType;
typedef uint8 CanTp_RxMaxPayloadLengthOfRxSduCfgType;
typedef boolean CanTp_RxPaddingActivationOfRxSduCfgType;
typedef PduIdType CanTp_RxPduIdOfRxSduCfgType;
typedef uint8 CanTp_RxPduMapIdxOfRxSduCfgType;
typedef boolean CanTp_RxPduMapUsedOfRxSduCfgType;
typedef uint8 CanTp_RxTaTypeOfRxSduCfgType;
typedef uint8 CanTp_RxWftMaxOfRxSduCfgType;
typedef uint8 CanTp_STminOfRxSduCfgType;
typedef uint8 CanTp_SduMetadataLengthOfRxSduCfgType;
typedef uint8 CanTp_TxFcAddressOfRxSduCfgType;
typedef PduIdType CanTp_TxFcPduConfirmationPduIdOfRxSduCfgType;
typedef uint8 CanTp_TxPduMapIdxOfRxSduCfgType;
typedef boolean CanTp_TxPduMapUsedOfRxSduCfgType;
typedef uint8 CanTp_TxSduCfgIdxOfRxSduCfgType;
typedef boolean CanTp_TxSduCfgUsedOfRxSduCfgType;
typedef uint8 CanTp_RxNSduHdlIdxOfRxSduSnv2HdlType;
typedef uint8 CanTp_RxNSduHdlPartitionIdxOfRxSduSnv2HdlType;
typedef boolean CanTp_RxNSduHdlUsedOfRxSduSnv2HdlType;
typedef uint8 CanTp_TxPdu2RxSduIndType;
typedef uint8 CanTp_TxPdu2TxSduIndType;
typedef uint32 CanTp_CanIdOfTxPduMapType;
typedef uint32 CanTp_MaskOfTxPduMapType;
typedef uint8 CanTp_TxPdu2RxSduEndIdxOfTxPduMapType;
typedef uint8 CanTp_TxPdu2RxSduPartitionIdxOfTxPduMapType;
typedef uint8 CanTp_TxPdu2RxSduStartIdxOfTxPduMapType;
typedef boolean CanTp_TxPdu2RxSduUsedOfTxPduMapType;
typedef uint8 CanTp_TxPdu2TxSduEndIdxOfTxPduMapType;
typedef uint8 CanTp_TxPdu2TxSduPartitionIdxOfTxPduMapType;
typedef uint8 CanTp_TxPdu2TxSduStartIdxOfTxPduMapType;
typedef boolean CanTp_TxPdu2TxSduUsedOfTxPduMapType;
typedef uint8 CanTp_CanTypeOfTxSduCfgType;
typedef uint8 CanTp_ChannelModeOfTxSduCfgType;
typedef PduIdType CanTp_LoLayerTxPduIdOfTxSduCfgType;
typedef uint8 CanTp_NAsOfTxSduCfgType;
typedef uint8 CanTp_NBsOfTxSduCfgType;
typedef uint8 CanTp_NCsOfTxSduCfgType;
typedef PduIdType CanTp_PduRTxSduIdOfTxSduCfgType;
typedef uint8 CanTp_RxFcAddressOfTxSduCfgType;
typedef PduIdType CanTp_RxFcPduIdOfTxSduCfgType;
typedef uint8 CanTp_RxPduMapIdxOfTxSduCfgType;
typedef boolean CanTp_RxPduMapUsedOfTxSduCfgType;
typedef uint8 CanTp_RxSduCfgIdxOfTxSduCfgType;
typedef boolean CanTp_RxSduCfgUsedOfTxSduCfgType;
typedef uint8 CanTp_SduMetadataLengthOfTxSduCfgType;
typedef boolean CanTp_TransmitCancellationOfTxSduCfgType;
typedef uint8 CanTp_TxAddressOfTxSduCfgType;
typedef uint8 CanTp_TxAddressingFormatOfTxSduCfgType;
typedef uint8 CanTp_TxMaxPayloadLengthOfTxSduCfgType;
typedef boolean CanTp_TxPaddingActivationOfTxSduCfgType;
typedef PduIdType CanTp_TxPduConfirmationPduIdOfTxSduCfgType;
typedef uint8 CanTp_TxPduMapIdxOfTxSduCfgType;
typedef boolean CanTp_TxPduMapUsedOfTxSduCfgType;
typedef uint8 CanTp_TxTaTypeOfTxSduCfgType;
typedef uint8 CanTp_TxNSduHdlIdxOfTxSduSnv2HdlType;
typedef uint8 CanTp_TxNSduHdlPartitionIdxOfTxSduSnv2HdlType;
typedef boolean CanTp_TxNSduHdlUsedOfTxSduSnv2HdlType;
#if (CANTP_SUPPORT_MULTI_PARTITION == STD_ON)
typedef ApplicationType CanTp_PartitionSNVOfPartitionIdentifiersType;
#else
typedef uint32 CanTp_PartitionSNVOfPartitionIdentifiersType;
#endif

/* Struct Typedefs */
typedef struct sCanTp_PartitionIdentifiersType
{
  CanTp_PartitionSNVOfPartitionIdentifiersType PartitionSNVOfPartitionIdentifiers;
  CanTp_PCPartitionConfigIdxOfPartitionIdentifiersType PCPartitionConfigIdxOfPartitionIdentifiers;
} CanTp_PartitionIdentifiersType;

typedef struct sCanTp_RxPduMapType
{
  CanTp_RxPdu2RxSduEndIdxOfRxPduMapType RxPdu2RxSduEndIdxOfRxPduMap;
  CanTp_RxPdu2RxSduStartIdxOfRxPduMapType RxPdu2RxSduStartIdxOfRxPduMap;
  CanTp_RxPdu2TxSduEndIdxOfRxPduMapType RxPdu2TxSduEndIdxOfRxPduMap;
  CanTp_RxPdu2TxSduPartitionIdxOfRxPduMapType RxPdu2TxSduPartitionIdxOfRxPduMap;
  CanTp_RxPdu2TxSduStartIdxOfRxPduMapType RxPdu2TxSduStartIdxOfRxPduMap;
} CanTp_RxPduMapType;

typedef struct sCanTp_RxSduCfgType
{
  CanTp_LoLayerTxFcPduIdOfRxSduCfgType LoLayerTxFcPduIdOfRxSduCfg;
  CanTp_PduRRxSduIdOfRxSduCfgType PduRRxSduIdOfRxSduCfg;
  CanTp_RxPduIdOfRxSduCfgType RxPduIdOfRxSduCfg;
  CanTp_TxFcPduConfirmationPduIdOfRxSduCfgType TxFcPduConfirmationPduIdOfRxSduCfg;
  CanTp_BlockSizeOfRxSduCfgType BlockSizeOfRxSduCfg;
  CanTp_RxPduMapIdxOfRxSduCfgType RxPduMapIdxOfRxSduCfg;
  CanTp_RxTaTypeOfRxSduCfgType RxTaTypeOfRxSduCfg;
  CanTp_RxWftMaxOfRxSduCfgType RxWftMaxOfRxSduCfg;
  CanTp_TxPduMapIdxOfRxSduCfgType TxPduMapIdxOfRxSduCfg;
  CanTp_TxSduCfgIdxOfRxSduCfgType TxSduCfgIdxOfRxSduCfg;
} CanTp_RxSduCfgType;

typedef struct sCanTp_RxSduSnv2HdlType
{
  CanTp_RxNSduHdlIdxOfRxSduSnv2HdlType RxNSduHdlIdxOfRxSduSnv2Hdl;
} CanTp_RxSduSnv2HdlType;

typedef struct sCanTp_TxPduMapType
{
  uint8 CanTp_TxPduMapNeverUsed;
} CanTp_TxPduMapType;

typedef struct sCanTp_TxSduCfgType
{
  uint8 CanTp_TxSduCfgNeverUsed;
} CanTp_TxSduCfgType;

typedef struct sCanTp_TxSduSnv2HdlType
{
  uint8 CanTp_TxSduSnv2HdlNeverUsed;
} CanTp_TxSduSnv2HdlType;

typedef P2VAR(CanTp_CalcBSType, TYPEDEF, CANTP_VAR_NO_INIT) CanTp_CalcBSPtrType;
typedef P2CONST(CanTp_PartitionIdentifiersType, TYPEDEF, CANTP_CONST) CanTp_PartitionIdentifiersPtrType;
typedef P2CONST(CanTp_RxPdu2RxSduIndType, TYPEDEF, CANTP_CONST) CanTp_RxPdu2RxSduIndPtrType;
typedef P2CONST(CanTp_RxPdu2TxSduIndType, TYPEDEF, CANTP_CONST) CanTp_RxPdu2TxSduIndPtrType;
typedef P2CONST(CanTp_RxPduMapType, TYPEDEF, CANTP_CONST) CanTp_RxPduMapPtrType;
typedef P2CONST(CanTp_RxSduCfgType, TYPEDEF, CANTP_CONST) CanTp_RxSduCfgPtrType;
typedef P2CONST(CanTp_RxSduSnv2HdlType, TYPEDEF, CANTP_CONST) CanTp_RxSduSnv2HdlPtrType;
typedef P2VAR(CanTp_RxStateType, TYPEDEF, CANTP_VAR_NO_INIT) CanTp_RxStatePtrType;
typedef P2CONST(CanTp_TxPdu2RxSduIndType, TYPEDEF, CANTP_CONST) CanTp_TxPdu2RxSduIndPtrType;
typedef P2CONST(CanTp_TxPdu2TxSduIndType, TYPEDEF, CANTP_CONST) CanTp_TxPdu2TxSduIndPtrType;
typedef P2CONST(CanTp_TxPduMapType, TYPEDEF, CANTP_CONST) CanTp_TxPduMapPtrType;
typedef P2CONST(CanTp_TxSduCfgType, TYPEDEF, CANTP_CONST) CanTp_TxSduCfgPtrType;
typedef P2CONST(CanTp_TxSduSnv2HdlType, TYPEDEF, CANTP_CONST) CanTp_TxSduSnv2HdlPtrType;
typedef P2VAR(CanTp_TxSemaphoreType, TYPEDEF, CANTP_VAR_NO_INIT) CanTp_TxSemaphoresPtrType;
typedef P2VAR(CanTp_TxStateType, TYPEDEF, CANTP_VAR_NO_INIT) CanTp_TxStatePtrType;

typedef struct sCanTp_PCPartitionConfigType
{
  uint8 CanTp_PCPartitionConfigNeverUsed;
} CanTp_PCPartitionConfigType;

typedef P2CONST(CanTp_PCPartitionConfigType, TYPEDEF, CANTP_CONST) CanTp_PCPartitionConfigPtrType;

typedef struct sCanTp_PCConfigType
{
  uint8 CanTp_PCConfigNeverUsed;
} CanTp_PCConfigType;

typedef CanTp_PCConfigType CanTp_PBConfigType;

#define CanTp_IsPreInitialized()        (CanTp_PreInitialized != FALSE)
#define CanTp_SetPreInitialized(Value)  (CanTp_PreInitialized = (Value))

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"
#if(CANTP_USE_INIT_POINTER == STD_ON)
extern P2CONST(CanTp_PBConfigType, CANTP_VAR_CLEARED, CANTP_PBCFG) CanTp_ConfigDataPtr;
#endif
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
extern VAR(boolean, CANTP_VAR_NO_INIT) CanTp_PreInitialized;
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CONST(CanTp_PartitionIdentifiersType, CANTP_CONST) CanTp_PartitionIdentifiers[1];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.h"
extern CONST(CanTp_RxPdu2RxSduIndType, CANTP_CONST) CanTp_RxPdu2RxSduInd[[!"num:i($numRxNPdus)"!]];
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CONST(CanTp_RxPduMapType, CANTP_CONST) CanTp_RxPduMap[[!"num:i($numRxNPdus)"!]];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CONST(CanTp_RxSduCfgType, CANTP_CONST) CanTp_RxSduCfg[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CONST(CanTp_RxSduSnv2HdlType, CANTP_CONST) CanTp_RxSduSnv2Hdl[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_8
#include "CanTp_MemMap.h"
extern VAR(CanTp_CalcBSType, CANTP_VAR_NO_INIT) CanTp_CalcBS[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
extern VAR(CanTp_RxStateType, CANTP_VAR_NO_INIT) CanTp_RxState[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

[!IF "$numTxSdus > 0"!][!//
#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
extern VAR(CanTp_TxSemaphoreType, CANTP_VAR_NO_INIT) CanTp_TxSemaphores[[!"num:i($numTxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
extern VAR(CanTp_TxStateType, CANTP_VAR_NO_INIT) CanTp_TxState[[!"num:i($numTxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

[!ENDIF!][!//
#endif /* CANTP_LCFG_H */
