/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ecrc_hal.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #ecrc_hal_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #ecrc_hal_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 #ifndef ECRC_HAL_H_
#define ECRC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Maxium Channel number */
/* #Violation: ecrc_hal_c_REF_2 */
#define CHANNEL_MAX_NUM (8U)

#define ECRC_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Define the ECRC return status */
typedef enum
{
    ECRC_OK = 0U,    /* CRC Execute success */
    ECRC_NOT_OK      /* CRC Execute fail */
} Ecrc_ErrorFlag;

/* Kernel CRC algorithm type */
typedef enum
{
    ECRC_KERNALTYPE_CRC32_0 = 0U,    /* CRC value 0x04C11DB7 */
    ECRC_KERNALTYPE_CRC32_1,         /* CRC value 0xF4ACFB13 */
    ECRC_KERNALTYPE_CRC16,           /* CRC value 0x1021 */
    ECRC_KERNALTYPE_CRC8,            /* CRC value 0x1D */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    ECRC_KERNALTYPE_CRC32_2          /* CRC value 0xEDB88320 */
#endif
} Ecrc_KernalType;

/* The enable of input register ByteSwap */
typedef enum
{
    ECRC_BYTESWAP_DISABLE = 0U,    /* Disable Input register byteswap */
    ECRC_BYTESWAP_ENABLE           /* Enable Input register byteswap */
} Ecrc_ByteSwap;

/* The Xor value with the final CRC */
typedef enum
{
    ECRC_XOUT_ALLZERO = 0U,    /* XOR out value 0x00000000 */
    ECRC_XOUT_ALLONE           /* XOR out value 0xFFFFFFFF */
} Ecrc_Xout;

/* The enable of Bit Reflection for Result register */
typedef enum
{
    ECRC_BIT_REFLECTION_DISABLE = 0U,    /* Disable CRC bit wise reflection */
    ECRC_BIT_REFLECTION_ENABLE           /* Enable CRC bit wise reflection */
} Ecrc_Bit_Reflection;

/* The enable of Byte Reflection for Input register */
typedef enum
{
    ECRC_BYTE_REFLECTION_DISABLE = 0U,    /* Disable CRC byte reflection at the input */
    ECRC_BYTE_REFLECTION_ENABLE           /* Enable CRC byte reflection at the input */
} Ecrc_Byte_Reflection;

/* The enable of auto reload for CHLEN register  */
typedef enum
{
    ECRC_RELOAD_DISABLE = 0U,    /* Disable auto reload for CHLEN register */
    ECRC_RELOAD_ENABLE           /* Enable auto reload for CHLEN register */
} Ecrc_Reload;

/* Ecrc alarm status */
typedef enum
{
    ECRC_ALARMSTATUS_RESET = 0U,    /* Ecrc status reset */
    ECRC_ALARMSTATUS_SET            /* Ecrc status set */
}Ecrc_AlarmStatus;

/* Ecrc alarm status */
typedef enum
{
    ECRC_ALARMSTATUSFLAG_ESTCFG = 0U,     /* channel CHCFG register E alarm */
    ECRC_ALARMSTATUSFLAG_ESTRST,          /* public reset register E alarm */
    ECRC_ALARMSTATUSFLAG_SEST,            /* regbank register SE alarm */
    ECRC_ALARMSTATUSFLAG_ECRE,            /* ALMCLR register E alarm clear, bit redundant alarm */
    ECRC_ALARMSTATUSFLAG_SECRE,           /* ALMCLR register SE alarm clear, bit redundant alarm */
    ECRC_ALARMSTATUSFLAG_SENRE,           /* SAFEEN bit redundant alarm */
    ECRC_ALARMSTATUSFLAG_SENCRE           /* ALMCLRi bit redundant alarm */
}Ecrc_AlarmStatusFlag;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* ECRC configuration initial structure */
typedef struct
{
    Ecrc_ByteSwap        byteswap;         /* Byteswap enable */
    Ecrc_Xout            xout;             /* Xout value  */
    Ecrc_Bit_Reflection  bitReflection;    /* Bit reflection enable */
    Ecrc_Byte_Reflection byteReflection;   /* Byte reflection enable */
    Ecrc_Reload          reload;           /* Length reload enable */
    uint32               channelID;        /* Channel ID */
} Ecrc_Cfg;

/* ECRC calculation structure */
typedef struct
{
    Ecrc_KernalType kernel;         /* CRC algorithm */
    uint32          *pData;         /* CRC input data */
    uint16          crcDataLength;  /* CRC input data length */
    uint32          crcStartValue;  /* CRC start value */
    boolean         crcIsFirstCall; /* Is function first call */
    uint32          pResult;        /* The CRC result */
}Ecrc_Cal;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: ecrc_hal_c_REF_2 */
#define ECRC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ecrc_hal_c_REF_1 */
#include "Ecrc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Ecrc_Register_ReadBack_Check
 * Description:  Check register read back value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Indicates whether the register is configured correctly
 *               expect: Expect value
 *               actual: Actual value
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the register is configured correctly
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Ecrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(ECRC_REG_CHECK)
LOCAL_FORCEINLINE boolean Ecrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    boolean ret;
    ret = state;
    if (expect != actual)
    {
        ret &= FALSE;
    }
    return ret;
}
#else
LOCAL_FORCEINLINE boolean Ecrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    (void)state;
    (void)expect;
    (void)actual;
    return state;
}
#endif
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     void Ecrc_Hal_Init
 * Description:  Init ECRC configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEcrcConfig: ECRC configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern boolean Ecrc_Hal_Init(const Ecrc_Cfg *const pEcrcConfig);

/**********************************************************************************************************************
 * Function:     Ecrc_Hal_SetInterrupt
 * Description:  Set ECRC interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channelID: Channel ID (0~7)
 *               interruptEnable: Interrupt enable, if the corresponding bit == 1, enable the interrupt.(bit[3:0])
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/09/05    00930      Create
 *********************************************************************************************************************/
extern boolean Ecrc_Hal_SetInterrupt(uint32 channelID, const uint32 interruptEnable);

/**********************************************************************************************************************
 * Function:     Ecrc_InterruptInfo Ecrc_Hal_GetInterrupt
 * Description:  Get the flag error type of a channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        channelID: Channel ID (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint32: indicate all the interrupt flag at this channel. (bit[3:0])
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern uint32 Ecrc_Hal_GetInterrupt(uint32 channelID);

/**********************************************************************************************************************
 * Function:     void Ecrc_Hal_ClearInterrupt
 * Description:  Clear a specific Interrupt of a specific channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        channelID: Channel ID (0~7)
 *               clearMask: Interrupt clear mask, if the corresponding bit == 1, clear the interrupt. (bit[3:0])
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern boolean Ecrc_Hal_ClearInterrupt(uint32 channelID,uint32 clearMask);

/**********************************************************************************************************************
 * Function:     Ecrc_Reset_Status Ecrc_Hal_Reset
 * Description:  Reset Ecrc Module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Ecrc_ErrorFlag: Reset status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern Ecrc_ErrorFlag Ecrc_Hal_Reset(void);

/**********************************************************************************************************************
 * Function:     uint32 Ecrc_Hal_CalculateCrcWithoutCheck
 * Description:  Calculate the Crc result of a given data
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channelID: Indicate the channel number (0~7)
 * Inout:        Ecrc_Cal: ECRC calculation configuration pointer
 * Output:       None
 * Return:       Ecrc_ErrorFlag: return check Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern Ecrc_ErrorFlag Ecrc_Hal_CalculateCrcWithoutCheck(Ecrc_Cal *const pEcrcCal, uint32 channelID);

/**********************************************************************************************************************
 * Function:     uint32 Ecrc_Hal_CalculateCrcWithCheck
 * Description:  Check the Crc result of a given data
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channelID: Indicate the channel number (0~7)
 *               expectedCrc: the expected crc value for checking
 * Inout:        Ecrc_Cal: ECRC calculation configuration pointer
 * Output:       None
 * Return:       Ecrc_ErrorFlag: return check Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern Ecrc_ErrorFlag Ecrc_Hal_CalculateCrcWithCheck(Ecrc_Cal *const pEcrcCal, uint32 channelID, uint32 expectedCrc);

/**********************************************************************************************************************
 * Function:     Ecrc_AlarmStatus Ecrc_Hal_GetAlarmStatus
 * Description:  Check and return Ecrc Alarm Status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flagStatus: indicate which flag is set
 *               channelID: channel number (0~7)
 * Inout:        None
 * Output:       None
 * Return:       Ecrc_AlarmStatus: indicate if the flag is set
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern Ecrc_AlarmStatus Ecrc_Hal_GetAlarmStatus(Ecrc_AlarmStatusFlag flagStatus, uint32 channelID);

/**********************************************************************************************************************
 * Function:     void Ecrc_Hal_ClearAlarmStatus
 * Description:  Clear alarm flag status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        flagStatus: indicate which flag is set
 *               channelID: channel number (0~7)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/14    01321     Create
 *********************************************************************************************************************/
extern boolean Ecrc_Hal_ClearAlarmStatus(Ecrc_AlarmStatusFlag flagStatus, uint32 channelID);

/* #Violation: ecrc_hal_c_REF_2 */
#define ECRC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ecrc_hal_c_REF_1 */
#include "Ecrc_MemMap.h"
#endif /* ECRC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/    
