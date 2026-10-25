/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all type definitions of Sent Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Sent_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Sent_GeneralTypes_h_REF_2:CertC-DCL02-C; 
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Sent_GeneralTypes_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/

#ifndef SENT_GENERALTYPES_H_
#define SENT_GENERALTYPES_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
#include "sent_hal.h"
#include "rcc_hal.h"
#include "Mcall.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* Type definition for Channel Ids */
typedef uint8 Sent_ChannelIdxType;

/* Type definition for Channel enable/disable operations */
typedef enum
{
  SENT_DISABLE        = 0x00U,
  SENT_ENABLE
} Sent_ChanOpType;

/* Structure definition for Channel Status */
/* #Violation: Sent_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{    
    uint8 IsCRCErr;         /* Specifies the status of CRC error (r) */
    uint8 IsFrameErr;       /* Specifies the status of frame error (r) */
    uint8 IsSlowCRCErr;       /* Specifies the status of CRC error in the received slow channel data (r) */
    uint8 IsSlowFrameErr;     /* Specifies the status of frame error in the received slow channel data (r) */
    uint8 IsSlowDone;         /* When it is set, it indicates that the receiving of the slow channel serial message is done (r) */
    uint8 IsDone;             /* When it is set, it indicates that the receiving of the fast channel serial message is done (r) */
} Sent_ChanStatusType;

/* Type definition for SENT Event/s to be notified */
typedef Sent_ChanStatusType Sent_NotifType;

/* Type definition for SENT Application notification function pointer */
typedef void (*Sent_NotifFnPtrType) (Sent_ChannelIdxType ChannelId,
                                     Sent_NotifType *StatPtr);
/*
  Structure definition for a SENT channel configuration
*/
/* #Violation: Sent_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{
    Sent_Config Config;
/* SPC Related Typedefs */
#if (SENT_SPC_USED == STD_ON)
    const Sent_Spc_Config *SpcConfigPtr;
    uint8 SpcPlusWidth;
    /* SPC enable */
    uint8 EnableSpc;
#endif /* #if (SENT_SPC_USED  \== STD_ON) */
    /* Physical Channel Id  */
    Sent_ChannelIdxType  ChanId;
    /* Callback function */
    Sent_NotifFnPtrType CallbackFn;
    /* Callback error function */
    Sent_NotifFnPtrType CallbackErrFn;
} Sent_ChannelCfgType;

/* Structure definition for the core */
/* #Violation: Sent_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{
    /* No of channels */
    Sent_ChannelIdxType          MaxChannels;
    /* Sent Channel Configuration */
    const  Sent_ChannelCfgType *Sent_ChannelConfigPtr;
} Sent_CoreConfigType;

/* Structure definition to receive serial data */
/* #Violation: Sent_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{
    /* 16-bit serial data */
    /* #Violation: Sent_GeneralTypes_h_REF_2 */
    uint16    Data;
    /* 4/8-bit Message Id */
    /* #Violation: Sent_GeneralTypes_h_REF_2 */
    uint8     MsgId;
    /* CRC of the serial data */
    /* #Violation: Sent_GeneralTypes_h_REF_2 */
    uint8     Crc;
    /* Configuration bit */
    uint8     Configuration;
} Sent_RxSerialDataType;

/* #Violation: Sent_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{
    /* Mapping of the core and channels - Store the core number of each channel
    * here. Searching becomes easy with this. */
    MultiCoreID Sent_ChannelCore;
    /* Mapping of the channels and config index - Store the index of the
    * configuration where the channel information is kept. */
    Sent_ChannelIdxType Sent_ChannelIndex;
} Sent_ChannelMapType;

/*
  Structure definition for SENT configuration
*/
typedef struct
/* #Violation: Sent_GeneralTypes_h_REF_3 */
{
    /* Pointer to Core configuration */
    const Sent_CoreConfigType *SentCorePtr[MCAL_NUMBER_OF_CORES];
    /* Number of SENT channels configured */
    uint8                     NumChannelsConfigured;
    /* The Lookup table pointer
     The pointer to the structure gives the arrangement
     of channels as per the core 
     inferior is logic channel index*/
    const Sent_ChannelMapType   *Sent_ChannelLookUpTablePtr;
    /* Physical to Logical Id mapping */
    const Sent_ChannelIdxType   *Sent_LogicalChanIdPtr;
    /* Logical to Physical Id mapping 
     inferior is logical channel index */
    const Sent_ChannelIdxType   *Sent_PhysicalChanIdPtr;
} Sent_ConfigType;

#endif /* SENT_GENERALTYPES_H_ */
/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/

