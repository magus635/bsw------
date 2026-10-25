/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Can_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "Can.h"
/***************************************************************************************************
*                               Local Macros
****************************************************************************************************/
/* Hardware object mapped to Core0 */
#define CAN_USED_HRH_MB_MAX_NUM_TO_CORE0             (5U)
#define CAN_USED_HTH_MB_MAX_NUM_TO_CORE0             (4U)
/* Hardware object mapped to Core1 */
#define CAN_USED_HRH_MB_MAX_NUM_TO_CORE1             (0U)
#define CAN_USED_HTH_MB_MAX_NUM_TO_CORE1             (1U)

/***************************************************************************************************
*                               Local Variables
****************************************************************************************************/
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/***************************************************************************************************
*                               Local Constants
****************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                        Hardware Filter Configurations
****************************************************************************************************/
static CONST(CanHwFilterType, CAN_CONST) Can_HwFilter_CfgSet[5U]=
{
    /* Controller Descriptor of CAN1_Rx_Standard*/
    {
        CAN_FILTER_ID_TYPE_STANDARD,  /* FilterType */
        (uint8)0U,                    /* StandardFilterIndex,invalid when extended frames */
        (uint8)0U,                    /* ExtendedFilterIndex,invalid when standard frames */
        (uint32)0x101U,               /* CanHwFilterCode */
        (uint32)0x101U,               /* CanHwFilterMask */
        (uint8)CAN_FILTERELECFG_STORE_RXBUFFER,
        (uint8)CAN_FILTERTYPE_CLASSIC,
        (uint8)CAN_RX_BUFFER0,
    },
    /* Controller Descriptor of CAN1_Rx_Standard_FIFO*/
    {
        CAN_FILTER_ID_TYPE_STANDARD,  /* FilterType */
        (uint8)1U,                    /* StandardFilterIndex,invalid when extended frames */
        (uint8)0U,                    /* ExtendedFilterIndex,invalid when standard frames */
        (uint32)0x200U,               /* CanHwFilterCode */
        (uint32)0x0U,               /* CanHwFilterMask */
        (uint8)CAN_FILTERELECFG_STORE_FIFO0,
        (uint8)CAN_FILTERTYPE_CLASSIC,
        (uint8)CAN_RX_FIFO0,
    },
    /* Controller Descriptor of CAN1_Rx_Extended*/
    {
        CAN_FILTER_ID_TYPE_EXTENDED,  /* FilterType */
        (uint8)2U,                    /* StandardFilterIndex,invalid when extended frames */
        (uint8)0U,                    /* ExtendedFilterIndex,invalid when standard frames */
        (uint32)0x1eeff000U,               /* CanHwFilterCode */
        (uint32)0xffffffffU,               /* CanHwFilterMask */
        (uint8)CAN_FILTERELECFG_STORE_RXBUFFER,
        (uint8)CAN_FILTERTYPE_CLASSIC,
        (uint8)CAN_RX_BUFFER1,
    },
    /* Controller Descriptor of CAN3_Rx_FD_Standard*/
    {
        CAN_FILTER_ID_TYPE_STANDARD,  /* FilterType */
        (uint8)0U,                    /* StandardFilterIndex,invalid when extended frames */
        (uint8)0U,                    /* ExtendedFilterIndex,invalid when standard frames */
        (uint32)0x103U,               /* CanHwFilterCode */
        (uint32)0xffffffffU,               /* CanHwFilterMask */
        (uint8)CAN_FILTERELECFG_STORE_RXBUFFER,
        (uint8)CAN_FILTERTYPE_CLASSIC,
        (uint8)CAN_RX_BUFFER0,
    },
    /* Controller Descriptor of CAN3_Rx_FD_Extended*/
    {
        CAN_FILTER_ID_TYPE_EXTENDED,  /* FilterType */
        (uint8)1U,                    /* StandardFilterIndex,invalid when extended frames */
        (uint8)0U,                    /* ExtendedFilterIndex,invalid when standard frames */
        (uint32)0x1eeff003U,               /* CanHwFilterCode */
        (uint32)0xffffffffU,               /* CanHwFilterMask */
        (uint8)CAN_FILTERELECFG_STORE_RXBUFFER,
        (uint8)CAN_FILTERTYPE_CLASSIC,
        (uint8)CAN_RX_BUFFER1,
    },
};
/***************************************************************************************************
*                       Hardware Object(s) Configurations
****************************************************************************************************/
/**
* +---------------------------------------+---------+-------+-----------+
* |                                       | POLLING | MIXED | INTERRUPT |
* +---------------------------------------+---------+-------+-----------+
* | CanHardwareObjectUsesPolling  = TRUE  |   O     |  O    |    X      |
* | CanHardwareObjectUsesPolling  = FALSE |   O     |  X    |    X      |
* +---------------------------------------+---------+-------+-----------+
*/
static CONST(Can_HardwareObjectType, CAN_CONST) Can_HardwareObj_MBCfgSet[CAN_USED_HOH_MB_MAX_NUM] =
{
    /*CAN4_Tx_Stand_Test0*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)0U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_TRANSMIT,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)4U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)1U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_1 */
        NULL_PTR,    /* HwFilterPtr */
        0U,                 /* Tx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN1_Rx_Standard*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)1U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_RECEIVE,/*Object_Type*/
        (boolean)FALSE,             /*Porcessing:INTERRUPT*/
        (uint8)1U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        &Can_HwFilter_CfgSet[0],    /* HwFilterPtr */
        0U,                         /* Rx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN2_Tx_FD_Extended_Test1*/
    {
        (Can_HandleType)FULL_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_EXTENDED,        /*CanFrameIdType*/
        (uint16)2U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_TRANSMIT,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)2U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        NULL_PTR,    /* HwFilterPtr */
        0U,                 /* Tx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN1_Rx_Standard_FIFO*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)8U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)3U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_RECEIVE,/*Object_Type*/
        (boolean)FALSE,             /*Porcessing:INTERRUPT*/
        (uint8)1U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle configured for INTERRUPT mode, reference not used */
        &Can_HwFilter_CfgSet[1],    /* HwFilterPtr */
        0U, /* RxFIFO0 Elements Index,The starting Elements Index of each Controller's RxFIFO must be 0 */
        (Can_MsgRamType)CAN_MSG_FIFO0, /* MsgRamType */
    },
    /*CAN1_Rx_Extended*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_EXTENDED,        /*CanFrameIdType*/
        (uint16)4U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_RECEIVE,/*Object_Type*/
        (boolean)FALSE,             /*Porcessing:INTERRUPT*/
        (uint8)1U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        &Can_HwFilter_CfgSet[2],    /* HwFilterPtr */
        1U,                         /* Rx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN3_Rx_FD_Standard*/
    {
        (Can_HandleType)FULL_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)5U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_RECEIVE,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)3U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        &Can_HwFilter_CfgSet[3],    /* HwFilterPtr */
        0U,                         /* Rx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN3_Rx_FD_Extended*/
    {
        (Can_HandleType)FULL_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_EXTENDED,        /*CanFrameIdType*/
        (uint16)6U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_RECEIVE,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)3U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        &Can_HwFilter_CfgSet[4],    /* HwFilterPtr */
        1U,                         /* Rx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN0_Tx_Standard_Test0*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)8U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)7U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_TRANSMIT,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)0U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        NULL_PTR,    /* HwFilterPtr */
        1U,                 /* Tx Queue Elements Index,In case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO
        or a Tx Queue, the Put and Get Indices indicate the number of the Tx Buffer starting with the first dedicated Tx Buffers. */
        (Can_MsgRamType)CAN_MSG_QUEUE, /* MsgRamType */
    },
    /*CAN0_Tx_Extended_Test1*/
    {
        (Can_HandleType)BASIC_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_EXTENDED,        /*CanFrameIdType*/
        (uint16)8U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_TRANSMIT,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)0U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)0U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_0 */
        NULL_PTR,    /* HwFilterPtr */
        0U,                 /* Tx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
    /*CAN2_Tx_FD_Standard_Test0*/
    {
        (Can_HandleType)FULL_CAN,   /*HandleType*/
        (uint16)1U,                 /*CanHwObjectCount*/
        (uint16)1U,                 /*CanHwFIFOThreshold*/
        CANID_TYPE_STANDARD,        /*CanFrameIdType*/
        (uint16)9U,                 /*Hardware Object ID*/
        (Can_ObjectType)CAN_TRANSMIT,/*Object_Type*/
        (boolean)TRUE,             /*Porcessing:POLLING*/
        (uint8)2U,                  /* ControllerId - based on the order from CanController list */
        (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
        (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
        (uint8)1U,                  /* CanMainFuncRWPeriodRef handle reference is from CanMainFunctionRWPeriods_1 */
        NULL_PTR,    /* HwFilterPtr */
        1U,                 /* Tx Buffer Elements Index */
        (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
    },
};
#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE0 CONFIGURATIONS START
****************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       HardwareObject Mapping List
****************************************************************************************************/
static const Can_HwHandleType Can_HohToCfgSetCore0[CAN_USED_HOH_MB_MAX_NUM_TO_CORE0] =
{
    1U,     /* The index of HardwareObject1(assigned to Core0) in HardwareObject list */
    2U,     /* The index of HardwareObject2(assigned to Core0) in HardwareObject list */
    3U,     /* The index of HardwareObject3(assigned to Core0) in HardwareObject list */
    4U,     /* The index of HardwareObject4(assigned to Core0) in HardwareObject list */
    5U,     /* The index of HardwareObject5(assigned to Core0) in HardwareObject list */
    6U,     /* The index of HardwareObject6(assigned to Core0) in HardwareObject list */
    7U,     /* The index of HardwareObject7(assigned to Core0) in HardwareObject list */
    8U,     /* The index of HardwareObject8(assigned to Core0) in HardwareObject list */
    9U,     /* The index of HardwareObject9(assigned to Core0) in HardwareObject list */
};

static const uint8 CanTxBufferAndFIFOIndexToHwObjectId0[2U]=
{
    7U,    /* The index of HardwareObject7 with buffer and FIFO (assigned to Core0 Controller0) in HardwareObject list */
    8U     /* The index of HardwareObject8 with buffer and FIFO (assigned to Core0 Controller0) in HardwareObject list */
};
static const uint8 Can_RxBufferIndexToHwObjectId1[2U]=
{
    1U,    /* The index of HardwareObject1 with dedicated buffer (assigned to Core0 Controller1) in HardwareObject list */
    4U     /* The index of HardwareObject4 with dedicated buffer (assigned to Core0 Controller1) in HardwareObject list */
};
static const uint8 Can_RxFifoIndexToHwObjectId1[1U]=
{
    3U     /* The index of HardwareObject3 with FIFO (assigned to Core0 Controller1) in HardwareObject list */
};
static const uint8 CanTxBufferAndFIFOIndexToHwObjectId2[2U]=
{
    2U,    /* The index of HardwareObject2 with buffer and FIFO (assigned to Core0 Controller2) in HardwareObject list */
    9U     /* The index of HardwareObject9 with buffer and FIFO (assigned to Core0 Controller2) in HardwareObject list */
};
static const uint8 Can_RxBufferIndexToHwObjectId3[2U]=
{
    5U,    /* The index of HardwareObject5 with dedicated buffer (assigned to Core0 Controller3) in HardwareObject list */
    6U     /* The index of HardwareObject6 with dedicated buffer (assigned to Core0 Controller3) in HardwareObject list */
};

/***************************************************************************************************
*                        CAN_CONTROLLER_02 CanFD Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerFdBaudrateType, CAN_CONST) Can_FDBaudrateCfgSet_Controller2[1U]=
{
    {
        (boolean)TRUE, /*CanControllerTxBitRateSwitch*/
        (uint16)400U, /*ControllerFdBaudRate in kbps*/
        {
            (uint32)1U, /*ControllerSyncJumpWidth*/
            (uint32)9U, /*ControllerFdBaudRatePRESDIV*/
            (uint32)5U, /*ControllerPropSeg+ControllerSeg1*/
            (uint32)2U, /*ControllerSeg2*/
            (uint8)0U, /*CanControllerSspOffset*/
            (uint8)0U, /*compFilterWindow*/
        },
        (boolean)FALSE, /*CanControllerSspOffset*/                        
    },
};
/***************************************************************************************************
*                        CAN_CONTROLLER_10 CanFD Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerFdBaudrateType, CAN_CONST) Can_FDBaudrateCfgSet_Controller3[1U]=
{
    {
        (boolean)TRUE, /*CanControllerTxBitRateSwitch*/
        (uint16)400U, /*ControllerFdBaudRate in kbps*/
        {
            (uint32)1U, /*ControllerSyncJumpWidth*/
            (uint32)9U, /*ControllerFdBaudRatePRESDIV*/
            (uint32)5U, /*ControllerPropSeg+ControllerSeg1*/
            (uint32)2U, /*ControllerSeg2*/
            (uint8)0U, /*CanControllerSspOffset*/
            (uint8)0U, /*compFilterWindow*/
        },
        (boolean)FALSE, /*CanControllerSspOffset*/                        
    },
};
/***************************************************************************************************
*                        CAN_CONTROLLER_00 Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller0[2U]=
{
    {
        (uint16)250U, /*ControllerBaudRate in kbps*/
        (uint16)0U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)9U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        NULL_PTR /*ControllerFdDefaultConfig*/
    },
    {
        (uint16)125U, /*ControllerBaudRate in kbps*/
        (uint16)1U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)19U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        NULL_PTR /*ControllerFdDefaultConfig*/
    },
};
/***************************************************************************************************
*                        CAN_CONTROLLER_01 Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller1[2U]=
{
    {
        (uint16)250U, /*ControllerBaudRate in kbps*/
        (uint16)0U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)9U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        NULL_PTR /*ControllerFdDefaultConfig*/
    },
    {
        (uint16)125U, /*ControllerBaudRate in kbps*/
        (uint16)1U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)19U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        NULL_PTR /*ControllerFdDefaultConfig*/
    },
};
/***************************************************************************************************
*                        CAN_CONTROLLER_02 Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller2[1U]=
{
    {
        (uint16)250U, /*ControllerBaudRate in kbps*/
        (uint16)0U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)9U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        &Can_FDBaudrateCfgSet_Controller2[0] /*ControllerFdDefaultConfig*/
    },
};
/***************************************************************************************************
*                        CAN_CONTROLLER_10 Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller3[1U]=
{
    {
        (uint16)250U, /*ControllerBaudRate in kbps*/
        (uint16)0U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)9U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        &Can_FDBaudrateCfgSet_Controller3[0] /*ControllerFdDefaultConfig*/
    },
};
/***************************************************************************************************
*                        Message RAM Configurations
****************************************************************************************************/
static CONST(Can_ControllerMsgRAMConfigType, CAN_CONST) Can_ControllerMsgRAMMapConfigCore0[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0]=
{
    {
        /* Start Address of each section within the Message RAM */
        {
            /* CAN_CONTROLLER_00 Message RAM Start Address :0xc0098000 */
            0x00000000U,     /* Standard Filter List Start Address #0 */
            0x00000000U,     /* Extended Filter List Start Address #0 */
            0x00000000U,     /* Rx FIFO 0 Start Address #0 */
            0x00000000U,     /* Rx FIFO 1 Start Address #0 */
            0x00000000U,     /* Rx Buffer Start Address #0 */
            0xc0098000U,     /* Tx Event FIFO Start Address #1 */
            0xc0098048U      /* Tx Buffers Start Address #1 */
            /* CAN_CONTROLLER_00 Message RAM End Address :0xc00980d8 */
        },
        {
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
            0x0U,                    /* RxFIFO0Threshold */
            0x0U,                    /* RxFIFO1Threshold */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 0 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 1 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Rx Buffer data field size */
            0x0U,                    /* Number of Dedicated Rx Buffer elements */
            0x0U,                    /* Number of Rx FIFO0 Elements */
            0x0U                     /* Number of Rx FIFO1 Elements */
        },
        {
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Tx buffer data field size */
            0x1U,                    /* Number of Dedicated Tx Buffers */
            0x8U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            0x9U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
        },
        {
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
            0x0U,                        /* Number of standard Message ID filters. */
            0x0U,                        /* Number of extended Message ID filters */
        },
        0U,                                   /* Total number of RX buffer used */
        0U,                                   /* Total number of RX FIFO used */
        2U,                                   /* Total number of Hth */
        NULL_PTR,
        NULL_PTR,
        &CanTxBufferAndFIFOIndexToHwObjectId0[0]   /* Hth index list */
    },
    {
        /* Start Address of each section within the Message RAM */
        {
            /* CAN_CONTROLLER_01 Message RAM Start Address :0xc00980d8 */
            0xc00980d8U,     /* Standard Filter List Start Address #2 */
            0xc00980e0U,     /* Extended Filter List Start Address #1 */
            0xc00980e8U,     /* Rx FIFO 0 Start Address #8 */
            0x00000000U,     /* Rx FIFO 1 Start Address #0 */
            0xc0098168U,     /* Rx Buffer Start Address #2 */
            0x00000000U,     /* Tx Event FIFO Start Address #0 */
            0x00000000U      /* Tx Buffers Start Address #0 */
            /* CAN_CONTROLLER_01 Message RAM End Address :0xc0098188 */
        },
        {
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
            0x1U,                    /* RxFIFO0Threshold */
            0x0U,                    /* RxFIFO1Threshold */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 0 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 1 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Rx Buffer data field size */
            0x2U,                    /* Number of Dedicated Rx Buffer elements */
            0x8U,                    /* Number of Rx FIFO0 Elements */
            0x0U                     /* Number of Rx FIFO1 Elements */
        },
        {
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Tx buffer data field size */
            0x0U,                    /* Number of Dedicated Tx Buffers */
            0x0U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            0x0U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
        },
        {
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
            0x2U,                        /* Number of standard Message ID filters. */
            0x1U,                        /* Number of extended Message ID filters */
        },
        2U,                                   /* Total number of RX buffer used */
        1U,                                   /* Total number of RX FIFO used */
        0U,                                   /* Total number of Hth */
        &Can_RxBufferIndexToHwObjectId1[0],   /* Rx dedicated buffer index list */
        &Can_RxFifoIndexToHwObjectId1[0],     /* Rx FIFO index list */
        NULL_PTR
    },
    {
        /* Start Address of each section within the Message RAM */
        {
            /* CAN_CONTROLLER_02 Message RAM Start Address :0xc0098188 */
            0x00000000U,     /* Standard Filter List Start Address #0 */
            0x00000000U,     /* Extended Filter List Start Address #0 */
            0x00000000U,     /* Rx FIFO 0 Start Address #0 */
            0x00000000U,     /* Rx FIFO 1 Start Address #0 */
            0x00000000U,     /* Rx Buffer Start Address #0 */
            0xc0098188U,     /* Tx Event FIFO Start Address #0 */
            0xc0098198U      /* Tx Buffers Start Address #2 */
            /* CAN_CONTROLLER_02 Message RAM End Address :0xc0098228 */
        },
        {
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
            0x0U,                    /* RxFIFO0Threshold */
            0x0U,                    /* RxFIFO1Threshold */
            (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 0 data field size */
            (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 1 data field size */
            (uint8)CAN_DATAFIELDSIZE_64,    /* Rx buffer data field size */
            0x0U,                    /* Number of Dedicated Rx Buffer elements */
            0x0U,                    /* Number of Rx FIFO0 Elements */
            0x0U                     /* Number of Rx FIFO1 Elements */
        },
        {
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
            (uint8)CAN_DATAFIELDSIZE_64,    /* Tx buffer data field size */
            0x2U,                    /* Number of Dedicated Tx Buffers */
            0x0U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            0x2U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
        },
        {
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
            0x0U,                        /* Number of standard Message ID filters. */
            0x0U,                        /* Number of extended Message ID filters */
        },
        0U,                                   /* Total number of RX buffer used */
        0U,                                   /* Total number of RX FIFO used */
        2U,                                   /* Total number of Hth */
        NULL_PTR,
        NULL_PTR,
        &CanTxBufferAndFIFOIndexToHwObjectId2[0]   /* Hth index list */
    },
    {
        /* Start Address of each section within the Message RAM */
        {
            /* CAN_CONTROLLER_10 Message RAM Start Address :0xd0008000 */
            0xd0008000U,     /* Standard Filter List Start Address #1 */
            0xd0008004U,     /* Extended Filter List Start Address #1 */
            0x00000000U,     /* Rx FIFO 0 Start Address #0 */
            0x00000000U,     /* Rx FIFO 1 Start Address #0 */
            0xd000800cU,     /* Rx Buffer Start Address #2 */
            0x00000000U,     /* Tx Event FIFO Start Address #0 */
            0x00000000U      /* Tx Buffers Start Address #0 */
            /* CAN_CONTROLLER_10 Message RAM End Address :0xd000809c */
        },
        {
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
            0x0U,                    /* RxFIFO0Threshold */
            0x0U,                    /* RxFIFO1Threshold */
            (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 0 data field size */
            (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 1 data field size */
            (uint8)CAN_DATAFIELDSIZE_64,    /* Rx buffer data field size */
            0x2U,                    /* Number of Dedicated Rx Buffer elements */
            0x0U,                    /* Number of Rx FIFO0 Elements */
            0x0U                     /* Number of Rx FIFO1 Elements */
        },
        {
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
            (uint8)CAN_DATAFIELDSIZE_64,    /* Tx buffer data field size */
            0x0U,                    /* Number of Dedicated Tx Buffers */
            0x0U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            0x0U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
        },
        {
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
            0x1U,                        /* Number of standard Message ID filters. */
            0x1U,                        /* Number of extended Message ID filters */
        },
        2U,                                   /* Total number of RX buffer used */
        0U,                                   /* Total number of RX FIFO used */
        0U,                                   /* Total number of Hth */
        &Can_RxBufferIndexToHwObjectId3[0],   /* Rx dedicated buffer index list */
        NULL_PTR,
        NULL_PTR
    }
};
/***************************************************************************************************
*                        Can Controller(s) General Configurations
****************************************************************************************************/
static CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerCfgSetCore0[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0] =
{
    /*Can Controller0 Configuration*/
    {
        (Can_ProcessingType)CAN_POLLING,      /*BusoffProcessing*/
        (boolean)TRUE,                    /*Activation*/
        (uint8)CAN_CONTROLLER_00,         /*PhysicalID*/
        (CAN_NODE*)CAN_CONTROLLER_00_BASE_ADDRESS,         /*Physical Address*/
        (uint8)0U,                        /*LogicalID*/
        (Can_ProcessingType)CAN_POLLING,      /*RxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*TxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*WakeupProcessing*/
        (boolean)TRUE,                    /*WakeupSupport*/
        (uint32)0xFFFFFFFFU,              /*Invalid WakeupSourceId*/
        (Can_InterruptStateType)CAN_INTERRUPT_DOWN,        /*InterruptState*/
        (boolean)FALSE,                       /*CanFDSupport*/
        (uint8)0U,                            /*DefaultBaudrate*/
        &Can_BaudrateCfgSet_Controller0[0],   /*BaudrateCfg*/
        (uint8)2U,                              /*NumberofBaudrate*/
        &Can_ControllerMsgRAMMapConfigCore0[0]  /*MsgRAM map to Controller list*/
    },
    /*Can Controller1 Configuration*/
    {
        (Can_ProcessingType)CAN_POLLING,      /*BusoffProcessing*/
        (boolean)TRUE,                    /*Activation*/
        (uint8)CAN_CONTROLLER_01,         /*PhysicalID*/
        (CAN_NODE*)CAN_CONTROLLER_01_BASE_ADDRESS,         /*Physical Address*/
        (uint8)1U,                        /*LogicalID*/
        (Can_ProcessingType)CAN_INTERRUPT,      /*RxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*TxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*WakeupProcessing*/
        (boolean)FALSE,                   /*WakeupSupport*/
        (uint32)0xFFFFFFFFU,              /*Invalid WakeupSourceId*/
        (Can_InterruptStateType)CAN_INTERRUPT_ACTIVE,        /*InterruptState*/
        (boolean)FALSE,                       /*CanFDSupport*/
        (uint8)0U,                            /*DefaultBaudrate*/
        &Can_BaudrateCfgSet_Controller1[0],   /*BaudrateCfg*/
        (uint8)2U,                              /*NumberofBaudrate*/
        &Can_ControllerMsgRAMMapConfigCore0[1]  /*MsgRAM map to Controller list*/
    },
    /*Can Controller2 Configuration*/
    {
        (Can_ProcessingType)CAN_POLLING,      /*BusoffProcessing*/
        (boolean)TRUE,                    /*Activation*/
        (uint8)CAN_CONTROLLER_02,         /*PhysicalID*/
        (CAN_NODE*)CAN_CONTROLLER_02_BASE_ADDRESS,         /*Physical Address*/
        (uint8)2U,                        /*LogicalID*/
        (Can_ProcessingType)CAN_POLLING,      /*RxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*TxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*WakeupProcessing*/
        (boolean)FALSE,                   /*WakeupSupport*/
        (uint32)0xFFFFFFFFU,              /*Invalid WakeupSourceId*/
        (Can_InterruptStateType)CAN_INTERRUPT_DOWN,        /*InterruptState*/
        (boolean)TRUE,                       /*CanFDSupport*/
        (uint8)0U,                            /*DefaultBaudrate*/
        &Can_BaudrateCfgSet_Controller2[0],   /*BaudrateCfg*/
        (uint8)1U,                              /*NumberofBaudrate*/
        &Can_ControllerMsgRAMMapConfigCore0[2]  /*MsgRAM map to Controller list*/
    },
    /*Can Controller3 Configuration*/
    {
        (Can_ProcessingType)CAN_POLLING,      /*BusoffProcessing*/
        (boolean)TRUE,                    /*Activation*/
        (uint8)CAN_CONTROLLER_10,         /*PhysicalID*/
        (CAN_NODE*)CAN_CONTROLLER_10_BASE_ADDRESS,         /*Physical Address*/
        (uint8)3U,                        /*LogicalID*/
        (Can_ProcessingType)CAN_POLLING,      /*RxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*TxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*WakeupProcessing*/
        (boolean)FALSE,                   /*WakeupSupport*/
        (uint32)0xFFFFFFFFU,              /*Invalid WakeupSourceId*/
        (Can_InterruptStateType)CAN_INTERRUPT_DOWN,        /*InterruptState*/
        (boolean)TRUE,                       /*CanFDSupport*/
        (uint8)0U,                            /*DefaultBaudrate*/
        &Can_BaudrateCfgSet_Controller3[0],   /*BaudrateCfg*/
        (uint8)1U,                              /*NumberofBaudrate*/
        &Can_ControllerMsgRAMMapConfigCore0[3]  /*MsgRAM map to Controller list*/
    },
};
/***************************************************************************************************
*                       Can Controller Usage Informations
****************************************************************************************************/
static const Can_CoreConfigType Can_CoreConfigCore0 =
{
    (Can_IdType)CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0,       /* Maximum number of the Controller(assigned to the core0) */
    &Can_ControllerCfgSetCore0[0],                          /* Can configuration information of core0 */
    (Can_HwHandleType)CAN_USED_HRH_MB_MAX_NUM_TO_CORE0,     /* Maximum number of the HRH(assigned to the core0) */
    (Can_HwHandleType)CAN_USED_HTH_MB_MAX_NUM_TO_CORE0,     /* Maximum number of the HTH(assigned to the core0) */
    (Can_HwHandleType)CAN_USED_HOH_MB_MAX_NUM_TO_CORE0,     /* Maximum number of the HOH(assigned to the core0) */
    &Can_HohToCfgSetCore0[0]                                /* Hardware object index at Hardware Object Config Sets list */
};

#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE0 CONFIGURATIONS STOP
****************************************************************************************************/

/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE1 CONFIGURATIONS START
****************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       HardwareObject Mapping List
****************************************************************************************************/
static const Can_HwHandleType Can_HohToCfgSetCore1[CAN_USED_HOH_MB_MAX_NUM_TO_CORE1] =
{
    0U,     /* The index of HardwareObject0(assigned to Core1) in HardwareObject list */
};

static const uint8 CanTxBufferAndFIFOIndexToHwObjectId4[1U]=
{
    0U     /* The index of HardwareObject0 with buffer and FIFO (assigned to Core1 Controller4) in HardwareObject list */
};

/***************************************************************************************************
*                        CAN_CONTROLLER_11 Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller4[1U]=
{
    {
        (uint16)250U, /*ControllerBaudRate in kbps*/
        (uint16)0U, /*ControllerBaudRateConfigID */
        {
            (uint16)1U, /*ControllerSyncJumpWidth*/
            (uint16)9U, /*ControllerPRESDIV*/
            (uint8)10U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)3U, /*ControllerSeg2*/
        },
        NULL_PTR /*ControllerFdDefaultConfig*/
    },
};
/***************************************************************************************************
*                        Message RAM Configurations
****************************************************************************************************/
static CONST(Can_ControllerMsgRAMConfigType, CAN_CONST) Can_ControllerMsgRAMMapConfigCore1[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1]=
{
    {
        /* Start Address of each section within the Message RAM */
        {
            /* CAN_CONTROLLER_11 Message RAM Start Address :0xd000809c */
            0x00000000U,     /* Standard Filter List Start Address #0 */
            0x00000000U,     /* Extended Filter List Start Address #0 */
            0x00000000U,     /* Rx FIFO 0 Start Address #0 */
            0x00000000U,     /* Rx FIFO 1 Start Address #0 */
            0x00000000U,     /* Rx Buffer Start Address #0 */
            0xd000809cU,     /* Tx Event FIFO Start Address #0 */
            0xd00080a4U      /* Tx Buffers Start Address #1 */
            /* CAN_CONTROLLER_11 Message RAM End Address :0xd00080b4 */
        },
        {
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
            (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
            0x0U,                    /* RxFIFO0Threshold */
            0x0U,                    /* RxFIFO1Threshold */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 0 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 1 data field size */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Rx Buffer data field size */
            0x0U,                    /* Number of Dedicated Rx Buffer elements */
            0x0U,                    /* Number of Rx FIFO0 Elements */
            0x0U                     /* Number of Rx FIFO1 Elements */
        },
        {
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
            (uint8)CAN_DATAFIELDSIZE_8,     /* Tx buffer data field size */
            0x1U,                    /* Number of Dedicated Tx Buffers */
            0x0U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            0x1U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
        },
        {
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
            (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
            (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
            0x0U,                        /* Number of standard Message ID filters. */
            0x0U,                        /* Number of extended Message ID filters */
        },
        0U,                                   /* Total number of RX buffer used */
        0U,                                   /* Total number of RX FIFO used */
        1U,                                   /* Total number of Hth */
        NULL_PTR,
        NULL_PTR,
        &CanTxBufferAndFIFOIndexToHwObjectId4[0]   /* Hth index list */
    }
};
/***************************************************************************************************
*                        Can Controller(s) General Configurations
****************************************************************************************************/
static CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerCfgSetCore1[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1] =
{
    /*Can Controller4 Configuration*/
    {
        (Can_ProcessingType)CAN_POLLING,      /*BusoffProcessing*/
        (boolean)TRUE,                    /*Activation*/
        (uint8)CAN_CONTROLLER_11,         /*PhysicalID*/
        (CAN_NODE*)CAN_CONTROLLER_11_BASE_ADDRESS,         /*Physical Address*/
        (uint8)4U,                        /*LogicalID*/
        (Can_ProcessingType)CAN_POLLING,      /*RxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*TxProcessing*/
        (Can_ProcessingType)CAN_POLLING,      /*WakeupProcessing*/
        (boolean)FALSE,                   /*WakeupSupport*/
        (uint32)0xFFFFFFFFU,              /*Invalid WakeupSourceId*/
        (Can_InterruptStateType)CAN_INTERRUPT_DOWN,        /*InterruptState*/
        (boolean)FALSE,                       /*CanFDSupport*/
        (uint8)0U,                            /*DefaultBaudrate*/
        &Can_BaudrateCfgSet_Controller4[0],   /*BaudrateCfg*/
        (uint8)1U,                              /*NumberofBaudrate*/
        &Can_ControllerMsgRAMMapConfigCore1[0]  /*MsgRAM map to Controller list*/
    },
};
/***************************************************************************************************
*                       Can Controller Usage Informations
****************************************************************************************************/
static const Can_CoreConfigType Can_CoreConfigCore1 =
{
    (Can_IdType)CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1,       /* Maximum number of the Controller(assigned to the core1) */
    &Can_ControllerCfgSetCore1[0],                          /* Can configuration information of core1 */
    (Can_HwHandleType)CAN_USED_HRH_MB_MAX_NUM_TO_CORE1,     /* Maximum number of the HRH(assigned to the core1) */
    (Can_HwHandleType)CAN_USED_HTH_MB_MAX_NUM_TO_CORE1,     /* Maximum number of the HTH(assigned to the core1) */
    (Can_HwHandleType)CAN_USED_HOH_MB_MAX_NUM_TO_CORE1,     /* Maximum number of the HOH(assigned to the core1) */
    &Can_HohToCfgSetCore1[0]                                /* Hardware object index at Hardware Object Config Sets list */
};

#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE1 CONFIGURATIONS STOP
****************************************************************************************************/


#define CAN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       Can Controller Allocation Mapping List
****************************************************************************************************/
static const Mcal_CoreType Can_ControllerMapList[CAN_USED_CONTROLLER_MAX_NUM] =
{
    MCAL_CORE0,    /* Controller<0>(assigned to Core<0>)*/
    MCAL_CORE0,    /* Controller<1>(assigned to Core<0>)*/
    MCAL_CORE0,    /* Controller<2>(assigned to Core<0>)*/
    MCAL_CORE0,    /* Controller<3>(assigned to Core<0>)*/
    MCAL_CORE1     /* Controller<4>(assigned to Core<1>)*/
};

/***************************************************************************************************
*                       Can Controller Index Mapping List
*   CanControllerId                              Can_ControllerGlobalStatus_Corei/
*                                                Can_ControllerCfgSetCorei
*   +-----------------------+                    +-------+
*   | CanController0(Core0) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
*   | CanController1(Core0) |   -------------->  |   1   |
*   +-----------------------+                    +-------+
*   | CanController2(Core1) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
*   | CanController3(Core2) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
****************************************************************************************************/
static const uint8 Can_ControllerToCoreMap[CAN_USED_CONTROLLER_MAX_NUM] =
{
    0U, /* Controller<0>(assigned to Core0) in Controller list index <0> */
    1U, /* Controller<1>(assigned to Core0) in Controller list index <1> */
    2U, /* Controller<2>(assigned to Core0) in Controller list index <2> */
    3U, /* Controller<3>(assigned to Core0) in Controller list index <3> */
    0U  /* Controller<4>(assigned to Core1) in Controller list index <0> */
};

/***************************************************************************************************
*                       Hardware Object Status Mapping List
*
*   CanObjectId(CanHwObjectCount)                  Can_MBGlobalStatus_Corei
*   +-------------------------+                    +-------+
*   | ID0(CanHwObjectCount=1) |   -------------->  |   0   |
*   +-------------------------+                    +-------+
*   | ID1(CanHwObjectCount=3) |   -------------->  |   1   |
*   +-------------------------+                    +-------+
*   | ID2(CanHwObjectCount=1) |   ---------        |   2   |
*   +-------------------------+            |       +-------+
*   | ID3(CanHwObjectCount=2) |   ------   |       |   3   |
*   +-------------------------+         |  |       +-------+
*                                       |   ---->  |   4   | 
*                                       |          +-------+
*                                        ------->  |   5   | 
*                                                  +-------+
*   
****************************************************************************************************/
static const uint16 Can_HwObjectToCoreIndexMap[CAN_USED_HOH_MB_MAX_NUM] =
{
    0U, /* CanObjectId<0> CanHwObjectCount=1 in (assigned to Core1) Can_MBGlobalStatus_Corei index */
    0U, /* CanObjectId<1> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    1U, /* CanObjectId<2> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    2U, /* CanObjectId<3> CanHwObjectCount=8 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    10U, /* CanObjectId<4> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    11U, /* CanObjectId<5> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    12U, /* CanObjectId<6> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    13U, /* CanObjectId<7> CanHwObjectCount=8 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    21U, /* CanObjectId<8> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
    22U  /* CanObjectId<9> CanHwObjectCount=1 in (assigned to Core0) Can_MBGlobalStatus_Corei index */
};
/***************************************************************************************************
*                       Can Driver Configuration Set
****************************************************************************************************/
const Can_ConfigType Can_ConfigSet[CAN_CONFIG_COUNT] =
{
    {
        /* CanController Config Sets of all cores */
        {
            &Can_CoreConfigCore0,         /* Can Controller configuration of Core0 */
            &Can_CoreConfigCore1          /* Can Controller configuration of Core1 */
        },
        &Can_HardwareObj_MBCfgSet[0],     /* Hardware Object Config Sets of all cores */
        &Can_ControllerToCoreMap[0],      /* Mapping can controller ID to global controller status of each core */
        &Can_HwObjectToCoreIndexMap[0],   /* Mapping hardware object ID to global mailbox status of each core */
        &Can_ControllerMapList[0]         /* Mapping can controller ID to CoreID */
    }
};
#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"

