/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains Demo application for Can Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Can_Demo.h"
#include "Demo_Common.h"
#include "ComStack_Types.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "Can.h"
#include "Can_Irq.h"
#include "Intc.h"
#include "CanIf_Can.h"
#include "CanIf.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define CAN_LOOPTIME_COUNT      (100U)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define DEMO_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
#include "Demo_MemMap.h"

static uint8 Can_Demo_Init_Flag_Core0 = 0xf0;
static uint8 Can_Demo_Init_Flag_Core1 = 0xf1;

static uint8 Can_Demo_Start_Flag_Core0 = 0x0f;
static uint8 Can_Demo_Start_Flag_Core1 = 0x1f;

#define DEMO_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
#include "Demo_MemMap.h"

#define DEMO_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
#include "Demo_MemMap.h"

static uint8 Can_Demo_Current_Cmd = 0;

#define DEMO_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
#include "Demo_MemMap.h"

#define DEMO_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Demo_MemMap.h"
/* Data Bytes For CAN Frame */
static uint8 Tx_data_buffer[13][8] =
{
    { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
    { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 },
    { 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28 },
    { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 },
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58 },
    { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68 },
    { 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78 },
    { 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88 },
    { 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 },
    { 0xa1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    { 0xb1, 0x22, 0x33, 0x44, 0x44, 0x33, 0x22, 0x11 },
    { 0xc1, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 },
};

/* Data Bytes For CAN FD Frame payload is 64Bytes. */
static uint8 Tx_data_FD_64[3][64] =
{
    {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
    },
    {
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60
    },
    {
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80
    }
};

/* Can frame configuration array. */
static Can_PduType Can_Write_TestData[11u] =
{
    /* Controller0 Receive frame. */
    {
        (PduIdType)0u,
        (uint8)8u,
        (Can_IdType)0x100u,
        &Tx_data_buffer[0][0]
    },
    {
        (PduIdType)1u,
        (uint8)8u,
        (Can_IdType)0x9eeff004u,
        &Tx_data_buffer[1][0]
    },
    /* Controller1 Receive frame. */
    {
        (PduIdType)0u,
        (uint8)8u,
        (Can_IdType)0x101u,
        &Tx_data_buffer[2][0]
    },
    {
        (PduIdType)1u,
        (uint8)8u,
        (Can_IdType)0x9eeff000u,
        &Tx_data_buffer[3][0]
    },
    /* Controller2 Receive frame. */
    {
        (PduIdType)0u,
        (uint8)64u,
        (Can_IdType)0x40000102u,
        &Tx_data_FD_64[1][0]
    },
    {
        (PduIdType)1u,
        (uint8)64u,
        (Can_IdType)0xDeeff002u,
        &Tx_data_FD_64[2][0]
    },
    /* Controller3 Receive frame. */
    {
        (PduIdType)0u,
        (uint8)64u,
        (Can_IdType)0x40000103u,
        &Tx_data_FD_64[1][0]
    },
    {
        (PduIdType)1u,
        (uint8)64u,
        (Can_IdType)0xDeeff003u,
        &Tx_data_FD_64[2][0]
    },
    /* Controller5 Reveive frame. */
    {
        (PduIdType)0u,
        (uint8)8u,
        (Can_IdType)0x105u,
        &Tx_data_buffer[2][0]
    },
    /* Controller0 Receive frame. */
    {
        (PduIdType)0u,
        (uint8)8u,
        (Can_IdType)0x400u,
        &Tx_data_buffer[3][0]
    },
    /* Controller6 Transmit frame. */
    {
        (PduIdType)0u,
        (uint8)8u,
        (Can_IdType)0x401u,
        &Tx_data_buffer[0][0]
    },
};

#define DEMO_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Demo_MemMap.h"


/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define DEMO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"


/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Can_StandardID_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_StandardID_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;

    /* Enable Controller1 Receive dedicate buffer interrupt. */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_265);

    /* Start Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STARTED);
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 is ready to sent CAN Standard Frame to Controller1");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller0 sent 0x101 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0, &Can_Write_TestData[2]);

    looptimeCnt = CAN_LOOPTIME_COUNT;

    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CAN frame is end\n");
        DEBUG_PRINTF("\n\n/*********************************************************/\n");
        DEBUG_PRINTF("    The Controller0 sent CAN Standard Frame to Controller1 is end.");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    /* Disable Controller1 Receive interrupt. */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_265);
}
/****************************************************************************************************
*   Function Name           : Can_StandardID_Check2
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_StandardID_Check2(void)
{
    uint8 i;
    uint32 looptimeCnt;

    /* Enable Controller1 Receive dedicate buffer interrupt. */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_265);

    /* Start Controller1  */
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller1@core1 Receiving...");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    looptimeCnt = CAN_LOOPTIME_COUNT;

    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CAN frame is end\n");
        DEBUG_PRINTF("\n\n/*********************************************************/\n");
        DEBUG_PRINTF("    The Controller1@core0 Received CAN Standard Frame from Controller4@core1.");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller1  */
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    /* Disable Controller1 Receive interrupt. */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_265);
}
/****************************************************************************************************
*   Function Name           : Can_ExtendedID_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_ExtendedID_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;

    /* Enable Controller1 Receive interrupt. */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_265);

    /* Start Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STARTED);
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 is ready to sent CAN Extended Frame to Controller1");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller0 sent 0x9eeff000 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN0_Tx_Extended_Test1, &Can_Write_TestData[3]);

    looptimeCnt = CAN_LOOPTIME_COUNT;

    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CAN frame is end\n");
        DEBUG_PRINTF("\n\n/*********************************************************/\n");
        DEBUG_PRINTF("    The Controller0 sent CAN Extended Frame to Controller1 is end.");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    /* Disable Controller1 Receive interrupt. */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_265);
}
/****************************************************************************************************
*   Function Name           : CanFD_StandardID_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void CanFD_StandardID_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;
    /* Start Controller2 and Controller3  */
    (void)Can_SetControllerMode(2,CAN_CS_STARTED);
    (void)Can_SetControllerMode(3,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller4 is ready to sent CAN Standard Frame to Controller0\n");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller0 sent 0x101 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN2_Tx_FD_Standard_Test0, &Can_Write_TestData[6]);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Can_MainFunction_Mode();
        Can_MainFunction_Write();
        Can_MainFunction_Read();
        Can_MainFunction_BusOff();
#if(CAN_NOACK_ERR_SUPPORTED == STD_ON)
        Can_MainFunction_NoAck();
#endif
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CANFD frame is end\n");
        DEBUG_PRINTF("\n\n/*********************************************************/\n");
        DEBUG_PRINTF("    The Controller2 sent CANFD Standard Frame to Controller3 is end.");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller2 and Controller3  */
    (void)Can_SetControllerMode(2,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(3,CAN_CS_STOPPED);
}
/****************************************************************************************************
*   Function Name           : CanFD_ExtendedID_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void CanFD_ExtendedID_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;
    /* Start Controller2 and Controller3  */
    (void)Can_SetControllerMode(2,CAN_CS_STARTED);
    (void)Can_SetControllerMode(3,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller2 is ready to sent CANFD Extended Frame to Controller3");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller0 sent 0xDeeff003 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN2_Tx_FD_Extended_Test1, &Can_Write_TestData[7]);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Can_MainFunction_Mode();
        Can_MainFunction_Write();
        Can_MainFunction_Read();
        Can_MainFunction_BusOff();
#if(CAN_NOACK_ERR_SUPPORTED == STD_ON)
        Can_MainFunction_NoAck();
#endif
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CANFD frame is end\n");
        DEBUG_PRINTF("\n\n/*********************************************************/\n");
        DEBUG_PRINTF("    The Controller2 sent CANFD Extended Frame to Controller3 is end.");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller2 and Controller3  */
    (void)Can_SetControllerMode(2,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(3,CAN_CS_STOPPED);
}
/****************************************************************************************************
*   Function Name           : Can_StandardID_Send
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_StandardID_Send(void)
{
    uint32 looptimeCnt;
    /* Start Controller4  */
    (void)Can_SetControllerMode(4,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller4@core1 is ready to sent CAN Standard Frame to Controller0@core0\n");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller4 sent 0x101 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN4_Tx_Stand_Test0, &Can_Write_TestData[2]);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while(looptimeCnt > 0)
    {
        looptimeCnt--;
        Can_MainFunction_Mode();
        Can_MainFunction_Write();
        Can_MainFunction_Read();
        Can_MainFunction_BusOff();
#if(CAN_NOACK_ERR_SUPPORTED == STD_ON)
        Can_MainFunction_NoAck();
#endif
        Timer_DelayMs(1);
    }

    /* Stop Controller4  */
    (void)Can_SetControllerMode(4,CAN_CS_STOPPED);
}

/****************************************************************************************************
*   Function Name           : Can_SetBaudrate_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_SetBaudrate_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;
    /* Start Controller0 and Controller1  */
    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    This Demo Case need Controller0 and Controller1 only connect \nwith each other. Don't make them connect to Can bus. ");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Enable Controller1 Receive dedicate buffer interrupt. */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_265);

    /* Start Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STARTED);
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 and Controller1 current baudrate is 250KBit/s and \nready to communicate with each other.");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Controller0 sent 0x101 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0, &Can_Write_TestData[2]);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CAN frame is end\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    /* Stop Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    DEBUG_PRINTF("\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Set Controller0 baudrate to 125KBit/s.");
    DEBUG_PRINTF("\n/*********************************************************/\n");

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    /* Set Controller0 baudrate to 125Kbit/s */
    (void)Can_SetBaudrate(0u,1u);
    (void)Can_SetBaudrate(1u,1u);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 and Controller1 current baudrate is 125KBit/s and \n    ready to communicate with each other.");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    /* Start Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STARTED);
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    /* Controller0 sent 0x101 to Controller1 */
    (void)Can_Write(CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0, &Can_Write_TestData[2]);

    looptimeCnt = CAN_LOOPTIME_COUNT;
    while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
    {
        looptimeCnt--;
        Timer_DelayMs(1);
    }

    if(Can_Receive_MB_Flag == 1u)
    {
        Can_Receive_MB_Flag = 0u;

        DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
        DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
        DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
        DEBUG_PRINTF("The CAN Data is\n");

        for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
        {
            DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
        }

        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("The CAN frame is end\n");
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Stop Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    DEBUG_PRINTF("\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Set Controller0 baudrate back to 250KBit/s.");
    DEBUG_PRINTF("\n/*********************************************************/\n");

    /* Set Controller0 baudrate to 500Kbit/s */
    (void)Can_SetBaudrate(0u,0u);
    (void)Can_SetBaudrate(1u,0u);

    /* Disable Controller1 Receive interrupt. */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_265);
}
/****************************************************************************************************
*   Function Name           : Can_RxFIFOReceive_Check
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_RxFIFOReceive_Check(void)
{
    uint8 i;
    uint32 looptimeCnt;
    uint32 ReceiveCnt;
    uint8 RxFIFOCheckFlag;

    DEBUG_PRINTF("\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 ready to receive 0x200~0x207 by RxFIFO.");
    DEBUG_PRINTF("\n/*********************************************************/\n");

    /* Enable Controller1 Receive FiFO0 interrupt. */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_268);

    /* Start Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STARTED);
    (void)Can_SetControllerMode(1,CAN_CS_STARTED);

    DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    Controller0 is ready to sent CAN Standard Frame to Controller1");
    DEBUG_PRINTF("\n/*********************************************************/\n\n\n");

    RxFIFOCheckFlag = 0u;

    /* Controller0 sent 0x200~0x207 to Controller1 */
    for(ReceiveCnt = 0u; ReceiveCnt < 8u; ReceiveCnt++)
    {
        Can_Write_TestData[2].id = 0x200U + ReceiveCnt;
        (void)Can_Write(CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0, &Can_Write_TestData[2]);

        looptimeCnt = CAN_LOOPTIME_COUNT;
        while((looptimeCnt > 0U) && (Can_Receive_MB_Flag == 0U))
        {
            looptimeCnt--;
            Timer_DelayMs(1);
        }

        if(Can_Receive_MB_Flag == 1u)
        {
            Can_Receive_MB_Flag = 0u;

            DEBUG_PRINTF("The CANID is 0x%lx\n", Can_MessageBuf.CanId);
            DEBUG_PRINTF("The CAN Controller is %d\n", Can_MessageBuf.ControllerId);
            DEBUG_PRINTF("The CAN Pdu length is %ld\n", Can_Message_PduInfo.SduLength);
            DEBUG_PRINTF("The CAN Data is\n");

            for(i = 0u; i < Can_Message_PduInfo.SduLength; i++)
            {
                DEBUG_PRINTF("0x%x ",Can_Message_PduInfo.SduDataPtr[i]);
            }

            DEBUG_PRINTF("\n");
            DEBUG_PRINTF("The CAN frame is end\n");

            if(Can_MessageBuf.CanId == (0x200U + ReceiveCnt))
            {
                RxFIFOCheckFlag |= 1u<<ReceiveCnt;
            }
        }
    }

    DEBUG_PRINTF("\n\n/*********************************************************/\n");
    DEBUG_PRINTF("    The Controller0 sent CAN Standard Frame to Controller1 is end.");
    DEBUG_PRINTF("\n/*********************************************************/\n");

    if(RxFIFOCheckFlag == 0xffu)
    {
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }

    /* Resume the buffer ID setting. */
    Can_Write_TestData[2].id = 0x101u;

    /* Stop Controller0 and Controller1  */
    (void)Can_SetControllerMode(0,CAN_CS_STOPPED);
    (void)Can_SetControllerMode(1,CAN_CS_STOPPED);

    /* Disable Controller1 Receive interrupt. */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_268);
}
/****************************************************************************************************
*   Function Name           : Can_Demo_Core0_Task
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver working on Core0 task.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_Demo_Core0_Task(void)
{
    char cmd;
    uint8 Can_Exit;
    Std_VersionInfoType VersionInfo;
    uint32 Conuter;

    Can_GetVersionInfo(&VersionInfo);

    DEBUG_PRINTF("\n\n\n");
    DEBUG_PRINTF("\n/*********************************************************/");
    DEBUG_PRINTF("\n           CAN DRIVER CODE VERSION V%d.%d.%d                  ",
           VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
    DEBUG_PRINTF("\n/*********************************************************/");

    DEBUG_PRINTF("\n\n\n");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n                CAN DRIVER CONFIG INFORMATION             \n ");
    DEBUG_PRINTF("\n                                                          \n ");
    DEBUG_PRINTF("     1.  Controller 0 Map to CAN00 on P20.8(Tx) and P20.7(Rx)\n ");
    DEBUG_PRINTF("     2.  Controller 1 Map to CAN01 on P33.9(Tx) and P33.10(Rx)\n ");
    DEBUG_PRINTF("     3.  Controller 2 Map to CAN02 on P15.0(Tx) and P15.1(Rx)\n ");
#if defined(THA6_THA6104)
    DEBUG_PRINTF("     4.  Controller 3 Map to CAN10 on P00.0(Tx) and P00.1(Rx)\n ");
#else
    DEBUG_PRINTF("     4.  Controller 3 Map to CAN10 on P23.1(Tx) and P23.0(Rx)\n ");
#endif /* THA6_THA6104 */
    DEBUG_PRINTF("     5.  Controller 4 Map to CAN11 on P02.5(Tx) and P02.4(Rx)\n ");
    DEBUG_PRINTF("                                                            \n ");
    DEBUG_PRINTF("\n/*********************************************************/\n");

    DEBUG_PRINTF("\n\n\n");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n                CAN DRIVER DEMOAPP MENU                   \n ");
    DEBUG_PRINTF("\n                                                          \n ");
    DEBUG_PRINTF("     1.  Core0: Transfer of Standard Frame on Controller0, and receive at Controller1\n ");
    DEBUG_PRINTF("     2.  Core0: Transfer of Extended Frame on Controller0, and receive at Controller1\n ");
    DEBUG_PRINTF("     3.  Core0: Transfer of Standard CANFD Frame on Controller2, and receive at Controller3\n ");
    DEBUG_PRINTF("     4.  Core0: Transfer of Extended CANFD Frame on Controller2, and receive at Controller3\n ");
    DEBUG_PRINTF("     5.  Core0: Changing Controller0 Baudrate from 500KBit/s to 250Kbit/s by Can_SetBaudRate\n ");
    DEBUG_PRINTF("     6.  Core0: Controller1 RxFIFO function test\n ");
#ifndef THA6_THA6104
    DEBUG_PRINTF("     7.  Core0 To Core1:Transfer of Standard Frame on Controller0 of Core0, and receive at Controller4 of Core1\n ");
    DEBUG_PRINTF("     8.  Core1 To Core0:Transfer of Standard Frame on Controller4 of Core1, and receive at Controller1 of Core0\n ");
#endif /* THA6_THA6104 */
    DEBUG_PRINTF("     x.  Back To Main Menu                                  \n ");
    DEBUG_PRINTF("                                                            \n ");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("  Enter Your Option : ");

    Can_Exit = 0u;

    while (0U == Can_Exit)
    {
        cmd = DEBUG_GETC();

        switch (cmd)
        {
            case '1':
                /* Transfer of Standard Frame. Task for Core0. */
                Can_StandardID_Check();

            break;

            case '2':
                /* Transfer of Extended Frame. Task for Core0. */
                Can_ExtendedID_Check();

            break;

            case '3':
                /* Transfer of Standard CANFD Frame. Task for Core0. */
                CanFD_StandardID_Check();

            break;

            case '4':
                /* Transfer of Extended CANFD Frame. Task for Core0. */
                CanFD_ExtendedID_Check();

            break;

            case '5':
                /* Changing Controller baudrate and sent CAN frame. Task for Core0. */
                Can_SetBaudrate_Check();

            break;

            case '6':
                /* Controller0 RxFIFO function test receive. Task for Core0. */
                Can_RxFIFOReceive_Check();

            break;

            case '7':
                /* Core0 To Core1:Transfer of Standard Frame on Controller0 of Core0, and receive at Controller4 of Core1 */
                Can_Demo_Current_Cmd = 7u;
                Can_Demo_Start_Flag_Core0 = 0x0f;
                Can_Demo_Start_Flag_Core1 = 0xAA;
                Conuter = 0u;
                while((0x0Fu != Can_Demo_Start_Flag_Core0)||(0x1Fu != Can_Demo_Start_Flag_Core1))
                {
                    if(Conuter >= 10000000u)
                    {
                        DEBUG_PRINTF("\n\n Controller0@Core0 send frame to Controller4@Core1 failed");
                        DEBUG_PRINTF("\n\n The Can_Demo_Start_Flag_Core0 value is :0x%x",Can_Demo_Start_Flag_Core0);
                        DEBUG_PRINTF("\n\n The Can_Demo_Start_Flag_Core1 value is :0x%x",Can_Demo_Start_Flag_Core1);
                        break;
                    }
                    Conuter++;
                };

            break;

            case '8':
                /* Core1 To Core0:Transfer of Standard Frame on Controller4 of Core1, and receive at Controller1 of Core0 */
                Can_Demo_Current_Cmd = 8u;
                Can_Demo_Start_Flag_Core0 = 0x0f;
                Can_Demo_Start_Flag_Core1 = 0xAA;
                Conuter = 0u;
                while((0x0Fu != Can_Demo_Start_Flag_Core0)||(0x1Fu != Can_Demo_Start_Flag_Core1))
                {
                    if(Conuter >= 10000000u)
                    {
                        DEBUG_PRINTF("\n\n Controller4@Core1 send frame to Controller1@Core0 failed");
                        DEBUG_PRINTF("\n\n The Can_Demo_Start_Flag_Core2 value is :0x%x",Can_Demo_Start_Flag_Core0);
                        DEBUG_PRINTF("\n\n The Can_Demo_Start_Flag_Core4 value is :0x%x",Can_Demo_Start_Flag_Core1);
                        break;
                    }
                    Conuter++;
                };
                Can_StandardID_Check2();

            break;

            case 'X':

                Can_Exit = 1U;
                break;

            default:
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
        }

    }
}
/****************************************************************************************************
*   Function Name           : Can_Demo_Core1_Task
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver working on Core1 task.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be initialized.
*
****************************************************************************************************/
static void Can_Demo_Core1_Task(void)
{
    switch (Can_Demo_Current_Cmd)
    {
        case 7u:
            /* Transfer of Standard CAN Frame. Task for Core1. */
            Can_Demo_Start_Flag_Core1 = 0x1f;
            Can_StandardID_Check2();

        break;

        case 8u:
            /* Transfer of Extended CAN Frame. Task for Core1. */
            Can_Demo_Start_Flag_Core1 = 0x1f;
            Can_StandardID_Send();

        break;

        default:
            DEBUG_PRINTF("\n\n  INVALID OPTION");
            break;
    }
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Can_DemoEntry
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for CAN driver.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
****************************************************************************************************/
void Can_DemoEntry(void)
{

    Mcal_CoreType CoreId;
    /* Get core id which is executing currently */
    CoreId = Mcal_GetCoreId();

    switch(CoreId)
    {
        case MULTICOREID_CPU0:
            /* Core0 Can Demo Task. */
            if(Can_Demo_Init_Flag_Core0 == 0xf0u)
            {
                Can_Demo_Init_Flag_Core0 = 0x55u;
                Can_Init(&Can_ConfigSet[0]);
            }

            Can_Demo_Core0_Task();

        break;

        case MULTICOREID_CPU1:

            /* Core1 Can Demo Task. */
            if(0xAAu == Can_Demo_Start_Flag_Core1)
            {
                if(Can_Demo_Init_Flag_Core1 == 0xf1u)
                {
                    Can_Demo_Init_Flag_Core1 = 0x55u;
                    Can_Init(&Can_ConfigSet[0]);
                }

                Can_Demo_Core1_Task();
            }

            break;

        default:
            DEBUG_PRINTF("\n\n  INVALID Core");
            break;
    }


}

#define DEMO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"

