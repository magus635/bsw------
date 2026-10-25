

/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Eth_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Geth
 *
 *   brief                 : This file contains Demo application for Eth Driver
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
#include "Eth_Demo.h"
#include "ComStack_Types.h"
#include "Demo_Common.h"
#include "Eth.h"
#include "EthIf.h"
#include "Mcall.h"

#define PHY_IF_MII (1U)

#ifdef PHY_IF_RGMII
#include "phy_dp83867.h"
#else
#include "phy_tja1101.h"
#endif
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define ETH_ARP_PROTOCOL               (0X0806U)

#define DELAY_30SEC                    (30000U)

#define ETH_FRAME_TYPE_1               (0xABCDU)

#define ETH_IPADDRESS_LENGTH           (4U)

#define ETH_ARPFRAME_DEST_IPADD_OFFSET (24U)

#define ETH_FRAMEHEADER_LENGTH         (14U)
#define ETH_FRAMECHKSUM_LENGTH         (4U)
#define ETH_SHIFT_8BIT                 (8U)
#define ETH_SHIFT_16BIT                (16U)
#define ETH_SHIFT_24BIT                (24U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

static uint8            Macaddress[6] = {0x12, 0x22, 0x33, 0x44, 0x55, 0x66};
static uint8            MacDestArpaddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /*Broadcast*/

static uint8            ArpData[28] = {0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x01, 0x01,
                                       0x01, 0x01, 0x01, 0x01, 0xa9, 0xfe, 0xfe, 0xab, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0xa9, 0xfe, 0xab, 0xa8};
static uint8            MacDestBrodaddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static Eth_BufIdxType   TmpBuffIdx;
static Eth_RxStatusType RxStatus;
static volatile Std_ReturnType    EthDemoRetVal;
static volatile BufReq_ReturnType Global_TempUSage1;
static int                        initFlag;

static uint8                     *TmpBuffPtr;
static uint8                      Temp_Macaddress[6];
uint32                            Src_IPaddress;

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
volatile uint32                   ArpReply;
volatile uint8                    PromiscuousCheck, StabilityTest;
uint8                             Ret_MacAddr[ETH_MAC_ADD_LEN];

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

static void                       StartResult(void)
{
    DEBUG_PRINTF("\n\nRESULT_START\n");
}

static void EndResult(void)
{
    DEBUG_PRINTF("\nRESULT_END\n\n");
}

/****************************************************************************************************
 *   Function Name           : TxBufferFill1
 *
 *   Service ID              : None.
 *
 *   Description             : This function fill buffer.
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
static void TxBufferFill1(uint8 *pTxBuff, uint16 DataLen, uint8 *Framedatax)
{
    uint8 i = 0;

    for (; i < DataLen; i++)
    {
        *(pTxBuff + i) = Framedatax[i];
    }

    return;
}

/****************************************************************************************************
 *   Function Name           : Ping_App
 *
 *   Service ID              : None.
 *
 *   Description             : This function is Ping Application .
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/

static void Ping_App(void)
{
    uint8           i;
    uint32          paramArray[6];
    volatile uint32 TimeoutCntr = 0U;

    paramArray[0] = 169;
    paramArray[1] = 254;
    paramArray[2] = 31;
    paramArray[3] = 177;

    for (i = 0U; i < ETH_IPADDRESS_LENGTH; i++)
    {
        ArpData[ETH_ARPFRAME_DEST_IPADD_OFFSET + i] = (uint8)paramArray[i];
    }
    for (i = 0U; i < 6U; i++)
    {
        ArpData[8U + i] = (uint8)Temp_Macaddress[i];
    }

    Src_IPaddress =
        (((paramArray[0] & 0xFFU) << ETH_SHIFT_24BIT) | ((paramArray[1] & 0xFFU) << ETH_SHIFT_16BIT) |
         ((paramArray[2] & 0xFFU) << ETH_SHIFT_8BIT) | (paramArray[3] & 0xFFU));
    TransmitArpFrame();

    do
    {
        Eth_TxConfirmation(0);
#if (ETH_ENA_RX_INT == STD_OFF)
        Eth_Receive(0,0, (Eth_RxStatusType *)&RxStatus);
#endif   

        TimeoutCntr++;
    } while ((ArpReply != 1) && (1000 > TimeoutCntr));


    if (ArpReply == 1U)
    {
        ArpReply = 0U;
        StartResult();
        DEBUG_PRINTF("Result = Pass;");
        EndResult();
    }
    else
    {
        DEBUG_PRINTF("\n Destination Host Unreachable\n  ");
        DEBUG_PRINTF("Reason 1: Ethernet Cross Wire is NOT connected between Board and Your PC\n");
        DEBUG_PRINTF("Reason 2: IP Address Entered is Wrong\n ");
        StartResult();
        DEBUG_PRINTF("Result = Fail;");
        EndResult();
    }
}

/****************************************************************************************************
 *   Function Name           : stabilityTest
 *
 *   Service ID              : None.
 *
 *   Description             : Promiscuous mode and stability Test .
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
static void Stability_Test(void)
{
    volatile uint32 TimeoutCntr = 0U;
    char            cmd;
    DEBUG_PRINTF("stability test\n");
    DEBUG_PRINTF(" 'x': exit\n");
    
    ArpReply = 0;
    /* Update filter for Open filter mode */
    (void)Eth_UpdatePhysAddrFilter(0, (uint8 *)&MacDestBrodaddress, ETH_ADD_TO_FILTER);
    StabilityTest = 1;
    do
    {
#if (ETH_ENA_RX_INT == STD_OFF)
        Eth_Receive(0, 0,(Eth_RxStatusType *)&RxStatus);
#endif    
       Uart_Read(0, (uint8*)&cmd);
       if (cmd == 'x')
        {
            DEBUG_PRINTF("stability test Count = %d\n",TimeoutCntr);
           break;
        }
        TimeoutCntr++;
    } while (1);
    /* Wait for 30 secs to receive frames */
    DEBUG_PRINTF("stability test over %lu \n", ArpReply);
}

/****************************************************************************************************
 *   Function Name           : Receive_Poll
 *
 *   Service ID              : None.
 *
 *   Description             : Promiscuous mode Receive all Frames .
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
static void Receive_Poll(void)
{
    volatile uint32 TimeoutCntr = 0;
    char            cmd = 0;
    Eth_GetPhysAddr(0, Ret_MacAddr);
    DEBUG_PRINTF("Recieve 30S or 'x': exit\n");
    Test_EthRxConfirmCount[0] = 0;
    /* Update filter for Open filter mode */
    (void)Eth_UpdatePhysAddrFilter(0, (uint8 *)&MacDestBrodaddress, ETH_ADD_TO_FILTER);

    do
    {
#if (ETH_ENA_RX_INT == STD_OFF)
        Eth_Receive(0,0, (Eth_RxStatusType *)&RxStatus);
#endif   

        Uart_Read(0, (uint8*)&cmd);

        if (cmd == 'x')
        {
            break;
        }

        Timer_DelayMs(1);
        TimeoutCntr++;
    } while (DELAY_30SEC != TimeoutCntr);
    /* Wait for 30 secs to receive frames */

    if ((Test_EthRxConfirmCount[0] > 0U) && (1U == PromiscuousCheck))
    {
        StartResult();
        DEBUG_PRINTF("Result = Pass;");
        EndResult();
    }
    else
    {
        StartResult();
        DEBUG_PRINTF("Result = Fail;");
        EndResult();
    }
}

/****************************************************************************************************
 *   Function Name           : Tx_EthFrame
 *
 *   Service ID              : None.
 *
 *   Description             : Transmit ETH Frame .
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
static void Tx_EthFrame(void)
{
    volatile uint32 TimeoutCntr;
    uint16          TmpTxlength, i;
    uint8          *TmpEthTxBuffPtr;

    Test_EthTxConfirmCount[0] = 0;

    TmpTxlength = 66U;
    Global_TempUSage1 = Eth_ProvideTxBuffer(0, 0,&TmpBuffIdx, &TmpEthTxBuffPtr, &TmpTxlength);
    if(BUFREQ_OK == Global_TempUSage1)
    {

        #if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)

            Eth_EnableEgressTimeStamp(0, TmpBuffIdx);
        #endif    

            for (i = 0U; i < TmpTxlength; i++)
            {
                *TmpEthTxBuffPtr = i + 1;
                TmpEthTxBuffPtr += 1;
            }

            EthDemoRetVal =
                Eth_Transmit(0, TmpBuffIdx, ETH_FRAME_TYPE_1, 1, TmpTxlength, &MacDestArpaddress[0]);

            TimeoutCntr = 0x7FFFFF;

            do
            {
                Eth_TxConfirmation(0);
            } while ((0U == Test_EthTxConfirmCount[0]) && ((TimeoutCntr--) > 0));

    }

    if (Test_EthTxConfirmCount[0] > 0U)
    {
        DEBUG_PRINTF("\n Transmitted ETH Frame of FrameType 0xABCD");
        DEBUG_PRINTF(
            "\n Payload Length %lu bytes and Total Frame Length %lu bytes\n",
            (uint32)TmpTxlength,
            ((uint32)TmpTxlength + ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH));
        Test_EthTxConfirmCount[0] = 0;

        StartResult();
        DEBUG_PRINTF("Result = Pass;");
        EndResult();
    }
    else
    {
        StartResult();
        DEBUG_PRINTF("Result = Fail;");
        EndResult();
    }
}

/****************************************************************************************************
 *   Function Name           : Read_PhyReg
 *
 *   Service ID              : None.
 *
 *   Description             : This function Read PHY Registers  .
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
 *   Preconditions           : .
 *
 ****************************************************************************************************/
static void Read_PhyReg(void)
{
    uint16         Ret_RegVal = 0, Ret_RegValOld;
    volatile uint8 EthTest_CtrlIdx = 0, ErrCnt = 0;
    Std_ReturnType Return_Type1;

#if (ETH_ENA_MII_API == STD_ON)

    Return_Type1 = Eth_ReadMii(EthTest_CtrlIdx, 0, 0x01, &Ret_RegVal);
    if (Return_Type1 == E_OK)
    {
        DEBUG_PRINTF(
            "\nReg Value Read from Ethernet PHY RegIdx 1 (Basic Mode Status REG): 0x%x \n ",
            Ret_RegVal);
    }
    else
    {
        ErrCnt++;
    }

    /*read PHY identifier register 1 (register 2)  */
    Return_Type1 = Eth_ReadMii(0, 0, 2U, &Ret_RegVal);
    if ((E_OK == Return_Type1) && (0x0180U == Ret_RegVal))
    {
        /*read PHY identifier register 2 (register 3)  */
        Return_Type1 = Eth_ReadMii(0, 0, 3U, &Ret_RegVal);
        if ((E_OK == Return_Type1) && (0xDD01U == Ret_RegVal))
        {}
        else
        {
            ErrCnt++;
        }
    }
    else
    {
        ErrCnt++;
    }

    Return_Type1 = Eth_ReadMii(0, 0, 22, &Ret_RegValOld);
    DEBUG_PRINTF("\nReg Value Read from 22: 0x%x \n ", Ret_RegValOld);
    if (E_OK == Return_Type1)
    {
        /* Write */
        Return_Type1 = Eth_WriteMii(0, 0, 22, 0xf000);
        DEBUG_PRINTF("\nReg Value write to 22: 0x%x \n ", 0xf000);
        if (E_OK != Return_Type1)
        {
            ErrCnt++;
        }
        else
        {
            Return_Type1 = Eth_ReadMii(0, 0, 22, &Ret_RegVal);
            if (0xf000 != Ret_RegVal)
            {
                ErrCnt++;
                DEBUG_PRINTF("\nReg Value Read from 22: 0x%x \n ", Ret_RegVal);
            }
        }
        Return_Type1 = Eth_WriteMii(0, 0, 22, Ret_RegValOld);
    }

    if (0U == ErrCnt)
    {
        StartResult();
        DEBUG_PRINTF("Result = Pass;");
        EndResult();
    }
    else
    {
        StartResult();
        DEBUG_PRINTF("Result = Fail;");
        EndResult();
    }
#endif
}

#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)

/****************************************************************************************************
 *   Function Name           : TimeStampDemo
 *
 *   Service ID              : None.
 *
 *   Description             : This function test Timestamp .
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
 *   Preconditions           : .
 *
 ****************************************************************************************************/

static void TimeStampDemo(void)
{
    Eth_TimeStampQualType TimeQual;
    Eth_TimeStampType     TimeStamp;
    Std_ReturnType        RetVal;
    uint8                 Result = 0;
    Eth_TimeStampType     DemotimeStamp;
    Eth_TimeStampType     EthTimeStamp;
    RetVal = Eth_GetCurrentTime(0, &TimeQual, &TimeStamp);
    if (TimeQual != ETH_INVALID)
    {
        DEBUG_PRINTF(
            "Eth_GetCurrentTime :secondsHi =%lu, %lu:%lu \n;",
            TimeStamp.secondsHi,
            TimeStamp.seconds,
            TimeStamp.nanoseconds);
    }
    else
    {
        RetVal = E_NOT_OK;
        Result = 1U;
    }

    volatile uint32 TimeoutCntr;
    uint16          TmpTxlength, i;
    uint8          *TmpEthTxBuffPtr;
    uint32 ns;
    Test_EthRxTimeConfirmCount[0] = 0;
    Test_EthTxTimeConfirmCount[0] = 0;
    Test_EthTxConfirmCount[0] = 0U;
    TmpTxlength = 16;
    Global_TempUSage1 = Eth_ProvideTxBuffer(0, 0, &TmpBuffIdx, &TmpEthTxBuffPtr, &TmpTxlength);

    Eth_EnableEgressTimeStamp(0, TmpBuffIdx);

    for (i = 0U; i < TmpTxlength; i++)
    {
        *TmpEthTxBuffPtr = i + 1U;
        TmpEthTxBuffPtr += 1U;
    }

    EthDemoRetVal =
        Eth_Transmit(0U, TmpBuffIdx, ETH_FRAME_TYPE_1, TRUE, TmpTxlength, &MacDestArpaddress[0]);

    TimeoutCntr = 30;

    do
    {
        Eth_TxConfirmation(0);
    } while ((0U == Test_EthTxTimeConfirmCount[0]) && ((TimeoutCntr--) > 0));




    if(Test_EthRxTimeConfirmCount[0] != 0)
    {
        DEBUG_PRINTF(
            "Get Vaild Rx timestamp \n;");
    }
    if(Test_EthTxTimeConfirmCount[0] != 0)
    {
        DEBUG_PRINTF(
            "Get Vaild Tx timestamp \n;");
    }
    TimeStamp.secondsHi = 2U;
    TimeStamp.seconds = 10U;
    TimeStamp.nanoseconds = 0U;


    RetVal = Eth_GetCurrentTime(0, &TimeQual, &DemotimeStamp);
    Timer_DelayMs(60);  
    RetVal = Eth_GetCurrentTime(0, &TimeQual, &EthTimeStamp);
    ns = EthTimeStamp.nanoseconds - DemotimeStamp.nanoseconds;
    if (TimeQual != ETH_INVALID)
    {
        DEBUG_PRINTF(
            "Eth_GetCurrentTime :secondsHi =%lu, %lu:%lu \n;",
            DemotimeStamp.secondsHi,
            DemotimeStamp.seconds,
            DemotimeStamp.nanoseconds);
    }
    else
    {
        RetVal = E_NOT_OK;
        Result = 1U;
    }
    DEBUG_PRINTF(
        "EthTimeStamp:secondsHi =%lu, %lu:%lu \n;",
        EthTimeStamp.secondsHi,
        EthTimeStamp.seconds,
        EthTimeStamp.nanoseconds);

    if ((EthTimeStamp.secondsHi != DemotimeStamp.secondsHi) ||
        (EthTimeStamp.seconds != DemotimeStamp.seconds) || (ns > 60100000) ||
        (ns < 59999999U))
    {
        Result = 1;
        RetVal = E_NOT_OK;
    }

    if (Result == 0U)
    {
        StartResult();
        DEBUG_PRINTF("Result = Pass;");
        EndResult();
    }
    else
    {
        StartResult();
        DEBUG_PRINTF("Result = Fail;");
        EndResult();
    }
    (void)RetVal;
}
#endif /* (ETH_GLOBAL_TIME_SUPPORT_API  \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : TransmitArpFrame
 *
 *   Service ID              : None.
 *
 *   Description             : This function Transmit Arp Frame .
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
void TransmitArpFrame(void)
{
    boolean Txstatus1 = 0U;
    uint16  Tmp_Txlenghth1 = 28U;

    Global_TempUSage1 = Eth_ProvideTxBuffer(0U, 0, &TmpBuffIdx, &TmpBuffPtr, &Tmp_Txlenghth1);

    if (Global_TempUSage1 == BUFREQ_OK)
    {
#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)

        Eth_EnableEgressTimeStamp(0, TmpBuffIdx);
#endif

        TxBufferFill1(TmpBuffPtr, Tmp_Txlenghth1, ArpData);

        EthDemoRetVal = Eth_Transmit(
            0, TmpBuffIdx, ETH_ARP_PROTOCOL, Txstatus1, Tmp_Txlenghth1, &MacDestBrodaddress[0]);
        Eth_TxConfirmation(0);
        if (EthDemoRetVal == E_OK)
        {}
        else
        {
            DEBUG_PRINTF("\nEth_Transmit FAILED");
        }
    }
    else if (Global_TempUSage1 == BUFREQ_E_NOT_OK)
    {
        DEBUG_PRINTF("\n BUFREQ_E_NOT_OK ");
    }
    else if (Global_TempUSage1 == BUFREQ_E_BUSY)
    {
        DEBUG_PRINTF("\n BUFREQ_E_BUSY ");
    }
    else if (Global_TempUSage1 == BUFREQ_E_OVFL)
    {
        DEBUG_PRINTF("\n BUFREQ_E_OVFL ");
    }
    else
    {}
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Eth_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for ETH driver.
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
 *   Preconditions           : ETH_Driver must be uninitialized.
 *
 ****************************************************************************************************/
void Eth_Demo(void)
{
    volatile uint8 loopvar = 0;
    char           cmd = 0;
    MultiCoreID    CoreId;

    CoreId = Mcal_GetCoreId();
    if (0 == initFlag)
    {
        initFlag = 1;
        /*Dio_WriteChannel(DioConf_DioPort_4_TJA1101_EN_CTRL,STD_HIGH);*/      
        Timer_DelayMs(100);
        Eth_Init(&Eth_ConfigSet[0]);
        /* Setup the PHY device */
        static Eth_NodeHandle g_EthNode;
        g_EthNode.pEthModule = Eth_ConfigSet[0]
                                   .EthCoreConfigPtr[CoreId]
                                   ->EthCtrlConfigPtr[0]
                                   .EthSdkCtrlConfigPtr->pEthModule;
        g_EthNode.ethMiiCrValue = Eth_ConfigSet[0]
                                   .EthCoreConfigPtr[CoreId]
                                   ->EthCtrlConfigPtr[0]
                                   .EthSdkCtrlConfigPtr->ethMiiCrValue;
#ifdef PHY_IF_RGMII
        retvalue = Eth_Phy_Dp83867_Init(
            &g_EthNode,
            Eth_ConfigSet[0]
                .EthCoreConfigPtr[CoreId]
                ->EthCtrlConfigPtr[0].EthSdkCtrlConfigPtr->phyInterfaceMode,
            Eth_ConfigSet[0]
                .EthCoreConfigPtr[CoreId]
                ->EthCtrlConfigPtr[0].EthSdkCtrlConfigPtr->mac.lineSpeed);

#else

        Eth_Phy_Tja1101_Init(
            &g_EthNode,
            Eth_ConfigSet[0]
                .EthCoreConfigPtr[CoreId]
                ->EthCtrlConfigPtr[0].EthSdkCtrlConfigPtr->phyInterfaceMode,
            Eth_ConfigSet[0]
                .EthCoreConfigPtr[CoreId]
                ->EthCtrlConfigPtr[0].EthSdkCtrlConfigPtr->mac.lineSpeed);
#endif
        Timer_DelayMs(100U);

        (void)Eth_SetControllerMode(0, ETH_MODE_ACTIVE);   
        Timer_DelayMs(100U);
        Eth_SetPhysAddr((uint8)0, &Macaddress[0]);   
        Eth_GetPhysAddr((uint8)0, &Temp_Macaddress[0]);
        DEBUG_PRINTF(
            "Eth_GetPhysAddr =%x:%x:%x:%x:%x:%x \n",
            Temp_Macaddress[0],
            Temp_Macaddress[1],
            Temp_Macaddress[2],
            Temp_Macaddress[3],
            Temp_Macaddress[4],
            Temp_Macaddress[5]);
    }

    while (loopvar == 0U)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF(
            "\n              ETH DRIVER DEMO MENU V%d.%d.%d  (demo do not support tha6104) ",
            ETH_SW_MAJOR_VERSION,
            ETH_SW_MINOR_VERSION,
            ETH_SW_PATCH_VERSION);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> :Promiscuous Mode: Receive All Frames ");
        DEBUG_PRINTF("\n  <2> :PING Application");
        DEBUG_PRINTF("\n  <3> :Transmit ETH Frame");
        DEBUG_PRINTF("\n  <4> :Read PHY Registers ");
#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
        DEBUG_PRINTF("\n  <5> :TimeStamp ");
#endif
        DEBUG_PRINTF("\n  <x> :Go back to Main Menu    \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();
        switch (cmd)
        {
        case '1':
            DEBUG_PRINTF("1\n");

            Receive_Poll();
            break;

        case '2':
            DEBUG_PRINTF("2\n");

            Ping_App();
            break;

        case '3':
            DEBUG_PRINTF("3\n");

            Tx_EthFrame();
            break;

        case '4':
            DEBUG_PRINTF("4\n");

            Read_PhyReg();
            break;
#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
        case '5':
            DEBUG_PRINTF("5\n");

            TimeStampDemo();
            break;
#endif /* (ETH_GLOBAL_TIME_SUPPORT_API  \== STD_ON) */

        case 'p':
            DEBUG_PRINTF("p\n");
            Stability_Test();
            break;

        case 'x':
        case 'X':
            loopvar = 1;
            StabilityTest = 0;
            break;

        default:

            DEBUG_PRINTF("\n\n  INVALID OPTION");
            break;
        } /* End of Case */
    }     /* End of While loop */
}

