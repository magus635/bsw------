/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Can_GeneralTypes.h
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

/****************************************************************************************************
**                         Coding Rule Violations                                                  **
****************************************************************************************************/
/*
*#Violation Summary
*
*#Can_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Can_GeneralTypes_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Can_GeneralTypes_h_REF_3:CertC-DCL12-C; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Can_GeneralTypes_h_REF_4:MISRAC2012-Rule-2.3;
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*/
#ifndef CAN_GENERAL_TYPES_H_
#define CAN_GENERAL_TYPES_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Can_Cfg.h"
#include "ComStack_Types.h"
#include "can_hal.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* SWS_Can_00039:
    transmit request could not be processed because no transmit object was available. 
    Overlayed return value of Std_ReturnType for CAN driver API Can_Write(). */
/* #Violation: Can_GeneralTypes_h_REF_2 */
#define CAN_BUSY            (Std_ReturnType)(0x02U)
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* SWS_Can_00416:
    Represents the Identifier of an L-PDU. 
    The two most significant bits specify the frame type:
    00 CAN message with Standard CAN ID.
    01 CAN FD frame with Standard CAN IDSpecifies the CAN ID type.
    10 CAN message with Extended CAN ID.
    11 CAN FD frame with Extended CAN ID. */
typedef uint32 Can_IdType;

/* SWS_Can_00429:
    Represents the hardware object handles of a CAN hardware unit. For CAN
    hardware units with more than 255 HW objects use extended range. */
typedef uint16 Can_HwHandleType;
/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
/* SWS_Can_91003:
    Error states of a CAN controller. */
typedef enum
{
    CAN_ERRORSTATE_ACTIVE = 0U,  /* The CAN controller takes fully part in communication. */
    CAN_ERRORSTATE_PASSIVE, /* The CAN controller takes part in communication,
                               but does not send active error frames. */
    CAN_ERRORSTATE_BUSOFF   /* The CAN controller does not take part in communication. */
} Can_ErrorStateType;

/* SWS_Can_91013:
    States that are used by the several ControllerMode functions. */
typedef enum
{
    CAN_CS_UNINIT  = 0U,     /* The CAN controller transition value to request state UNINT */
    CAN_CS_STARTED = 1U,     /* The CAN controller transition value to request state STARTED */
    CAN_CS_STOPPED = 2U,     /* The CAN controller transition value to request state STOPPED */
    CAN_CS_SLEEP   = 3U      /* The CAN controller transition value to request state SLEEP */
} Can_ControllerStateType;

/* SWS_Can_00103 SWS_Can_00246
    7.2 Driver State Machine */
typedef enum
{
    CAN_UNINIT = 0U,        /* The CAN controller Not initialized */
    CAN_READY               /* The CAN controller Initialized */
} Can_InitType;

/* ECUC_Can_00314 ECUC_Can_00317 ECUC_Can_00318 ECUC_Can_00319:
    Enables / disables API MainFunction for handling events in polling/interrupt mode. */
typedef enum
{
    CAN_INTERRUPT = 0U,     /* Interrupt Mode of operation. */
    CAN_MIXED,              /* Mixed Mode of operation. */
    CAN_POLLING             /* Polling Mode of operation. */
} Can_ProcessingType;

/* SWS_Can_00231 SWS_Can_00232
    Enables / disables Controller interrupt */
typedef enum
{
    CAN_INTERRUPT_DOWN = 0U, /* Interrupts disabled */
    CAN_INTERRUPT_ACTIVE     /* Interrupts enabled */
} Can_InterruptStateType;

/* SWS_Can_00227: 
    Busoff status for controller */
typedef enum
{
    CAN_BUS_OK = 0U,         /* Not in busoff status */
    CAN_BUS_OFF              /* Busoff status */
/* #Violation: Can_GeneralTypes_h_REF_4 */
} Can_BusOffStateType;

/* SWS_Can_00228:
    Wakeup status for controller */
typedef enum
{
    CAN_NOT_WAKEUP = 0U,     /* Not in wakeup state. */
    CAN_WAKEUP               /* wakeup state. */
} Can_WakeupStateType;

/* Wakeup types for controller */
typedef enum
{
    DEFAULT_STATE = 0U,      /* Default state in initialization. */
    SOFTWARE_WAKEUP,         /* Wakeup by software. */
    HARDWARE_WAKEUP          /* Wakeup by hardware. */
} Can_WakeupType;

/* ECUC_Can_00323:
    Specifies the type (Full-CAN or Basic-CAN) of a hardware object.*/
typedef enum
{
    BASIC_CAN = 0U,          /* Basic:For several L-PDUs are hadled by the hardware object */
    FULL_CAN                 /* Full :For only one L-PDU is handled by the hardware object */          
} Can_HandleType;

/* ECUC_Can_00065:
    Specifies whether the IdValue is of type
    - standard identifier
    - extended identifier
    - mixed mode */
/* Can_FilterIDType, enumeration for CAN filter id type */
typedef enum
{
    CANID_TYPE_STANDARD = 0U, /* Standard identifier */
    CANID_TYPE_EXTENDED,      /* Extended identifier */
    CANID_TYPE_MIXED,         /* Standard identifier + Extended identifier */
} Can_IdValueType;

/* ECUC_Can_00327:
    Specifies if the HardwareObject is used as Transmit or as Receive object. */
typedef enum
{
    CAN_RECEIVE = 0U,          /* Receive hardware object. */
    CAN_TRANSMIT               /* Transmit hardware object. */
} Can_ObjectType;

/* Non-AUTOSAR: 
    Data type used for Rx/Tx Msg Ram Type */
typedef enum
{
    CAN_MSG_DED_BUFFER = 0U,
    CAN_MSG_QUEUE,
    CAN_MSG_FIFO0,
    CAN_MSG_FIFO1
} Can_MsgRamType;

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* SWS_Can_00415: 
   CAN protocol data unit type. Used to provide ID, DLC and SDU from
   CAN Interface to CAN driver */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* SW Handle that will identify the request in the confirmation callback function. */
    PduIdType     swPduHandle;

    /* DLC */
    uint8         length;

    /* Identifier of L-PDU */   
    Can_IdType    id;

    /* Pointer to L-SDU */
    uint8         *sdu;
} Can_PduType;

/* SWS_CAN_00496:
    This type defines a data structure which clearly provides an Hardware Object
    Handle including its corresponding CAN Controller and therefore CanDrv as well
    as the specific CanId. */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Standard/Extended CAN ID of CAN L-PDU */
    Can_IdType        CanId;

    /* ID of the corresponding Hardware Object */   
    Can_HwHandleType  Hoh;

    /* ControllerId provided by CanIf */
    uint8             ControllerId;
} Can_HwType;

/* This type defines all the states and necessary information of Can Controller at
   runtime */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* Current status of the CAN controller. */
    Can_ControllerStateType             CurrentStatus;
    
    /* WakeupState status of the CAN controller */
    Can_WakeupStateType                 WakeupState;

    /* WakeupType status of the CAN controller */
    Can_WakeupType                      WakeupType;

    /* Current BaudrateIndex of the CAN controller. */
    uint8                               BaudrateIndexCfg;

    /* Disable Interupted Count of the CAN controller. */
    sint32                              DisableIntrpCount;
} Can_ControllerRuntimeType;

/* This type defines all the states and necessary information of the Can Controller
   mail box at runtime */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* Store the PduId of message transmited. */
    PduIdType                           Can_TxPduIdBuff;
    /* Store the counts from TxEvent FIFO. */
    uint8                               Can_TxEventCnt;
    /* Set when message transmited,Clear after PDUID report to CanIF. */
    boolean                             Can_TxPduIdBuffBusy;
} Can_MBStatusType;

/* This type is used to flag the Can Controller information */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
{
    /* CAN Controller initialize status */
    Can_InitType                *CanInitStatusPtr;

    /* CAN MB Status to Core */
    Can_MBStatusType            *CanMBStatusPtr;

    /* CAN Controller Status to Core */
    Can_ControllerRuntimeType   *ControllerStatusPtr;
} Can_CoreStatusType;

/****************************************************************************************************
**                          Global Configuration Structure Definitions                             **
****************************************************************************************************/
/* ECUC_Can_00468:
   This container is only valid for HRHs and contains the configuration 
   (parameters) of one hardware filter. */
typedef Can_Filter              CanHwFilterType;

/* ECUC_Can_00324:
   This container contains the configuration (parameters) of CAN Hardware Objects. */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct 
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* ECUC_Can_00323:
        Specifies the type (Full-CAN or Basic-CAN) of a hardware object. */
    Can_HandleType                      HandleType;
    /* ECUC_Can_00467:
        Number of hardware objects used to implement one HOH. */
    uint16                              HwObjectCount;
    uint16                              HwObjectFIFOThreshold;

    /* ECUC_Can_00065:
     Specifies whether the IdValue is of type(standard/extended/mixed) */
    Can_IdValueType                     CanFrameIdType;
    uint16                              ObjectId;

    /* ECUC_Can_00327:
     Specifies if the HardwareObject is used as Transmit or as Receive object. */
    Can_ObjectType                      ObjectType;

#if (CAN_TRIGGER_TRANSMIT_SUPPORT == STD_ON)
    /* ECUC_Can_00486:
       This parameter defines if or if not Can supports the trigger-transmit API for this handle.*/
    boolean                             TriggerTxEN;
#endif /* (CAN_TRIGGER_TRANSMIT_SUPPORT  \== STD_ON) */

    /* ECUC_Can_00490:
       Enables polling of this hardware object.*/
    boolean                             UsesPolling;

    /* ECUC_Can_00322:
        Reference to CAN Controller to which the HOH is associated to. */
    uint8                               ControllerId;

#if (CANFD_MODE_SUPPORT == STD_ON)
    /* ECUC_Can_00485:
        Specifies the value used to pad unspecified data in CAN FD frames > 8 bytes for transmission.
        This is necessary due to the discrete possible values of the DLC if > 8 bytes. */
    boolean                             FdPaddingEnable;
    uint8                               FdPaddingValue;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

    /* ECUC_Can_00438,ECUC_Can_00484:
       This parameter describes the period for cyclic call to Can_MainFunction_Read or
       Can_MainFunction_Write depending on the referring item.  */
    uint8                               CanMainFuncRWPeriodRef;

    /* ECUC_Can_00468:
        This is only valid for HRHs and contains the configuration of one hardware filter. */
    const CanHwFilterType               *HwFilterPtr;

    /* Non-AUTOSAR:
        Mark the mailbox at the (Rx/Tx)buffer index.
        Always zero if MsgRamType is not CAN_MSG_DED_BUFFER*/
    uint8                               ElementsIndex;

    /* Non-AUTOSAR:
        Mark the mailbox(Message RAM) type */
    Can_MsgRamType                      MsgRamType;
} Can_HardwareObjectType;

/* FD Baudrate Configurations data type */
#if (CANFD_MODE_SUPPORT == STD_ON)
/* ECUC_Can_00473:
    This optional container contains bit timing related configuration parameters 
    of the CAN controller(s) for payload and CRC of a CAN FD frame. If this 
    container exists the controller supports CAN FD frames. */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* ECUC_Can_00475:
        Specifies if the bit rate switching shall be used for transmissions. */
    boolean                             TBRS;

    /* ECUC_Can_00481:
        Specifies the data segment baud rate of the controller in kbps. */
    uint16                              FdBaudrateValue;

    /* ECUC_Can_00479,ECUC_Can_00476,ECUC_Can_00477,ECUC_Can_00478,ECUC_Can_00480:
        Contains bit timing related configuration parameters of the CAN controller */
    Can_FastBaudRate                    DataBaudRate;

    /* Enable the the Transmitter Delay Compensation Offset. */
    boolean                             TrcvDelayCompensationSupport;
} Can_ControllerFdBaudrateType;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

/* ECUC_Can_00387:
    This container contains bit timing related configuration parameters of the 
    CAN controller(s). */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* ECUC_Can_00005:
        Specifies the baudrate of the controller in kbps. */
    uint16                              BaudrateValue;
#if (CAN_SET_BAUDRATE_API == STD_ON)
    /* ECUC_Can_00471:
        Uniquely identifies a specific baudrate configuration. This ID is used by SetBaudrate API. */
    uint16                              BaudRateCfgID;
#endif /* (CAN_SET_BAUDRATE_API  \== STD_ON) */
    /* ECUC_Can_00073,ECUC_Can_00074,ECUC_Can_00075,ECUC_Can_00383:
        Contains bit timing related configuration parameters of the CAN controller. */
    Can_BaudRate                        BaudrateParam;
#if (CANFD_MODE_SUPPORT == STD_ON)
    /* ECUC_Can_00473:
        Contains bit timing related configuration parameters for CANFD frame.*/
    const Can_ControllerFdBaudrateType  *FdDefaultCfgPtr;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
} Can_ControllerBaudrateType;

/****************************************************************************************************
                Message RAM partition configuration data type
****************************************************************************************************/
/* Non-AUTOSAR:
    Contains Message RAM related configuration parameters of the CAN controller.  */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* Start Address of Each Section with in the Message RAM */
    Can_MessageRAM MsgRAMMap;

    /* Rx handle configuration */
    Can_RxConfig RxHandleConfig;

    /* Tx handle configuration */
    Can_TxConfig TxHandleConfig;

    /* Filter configuration */
    Can_FilterConfig FilterHandleConfig;

    /* Total number of Rx dedicate buffer */
    uint8 RxBufferNum;

    /* Total number of Rx FIFOs */
    uint8 RxFIFONum;

    /* Total number of Tx dedicate buffer */
    uint8 HthNum;

    /* Mapping table between dedicate buffer index and receiving mailbox */
    const uint8 *RxBufferIndexMap;

    /* Mapping table between FIFO index and receiving mailbox */
    const uint8 *RxFIFOIndexMap;

    /* Mapping table between dedicate buffer index and transmit mailbox */
    const uint8 *HthIndexMap;
} Can_ControllerMsgRAMConfigType;

/* ECUC_Can_00354: 
   This container contains the configuration parameters of the CAN controller(s). */
/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* ECUC_Can_00314:
        Enables / disables API Can_MainFunction_BusOff for handling busoff events
        in polling mode.*/
    Can_ProcessingType                  BusoffProcessing;

    /* ECUC_Can_00315:
       Defines if a CAN controller is used in the configuration. */
    boolean                             Activation;

    /* ECUC_Can_00382:
        Specifies the CAN controller base address. */
    uint8                               PhysicalID;
    CAN_NODE                           *PhysicalAddress;

    /* ECUC_Can_00316:
         the controller ID which is unique in a given CAN Driver. 
         The value for this parameter starts with 0 and continue without any gaps. */
    uint8                               LogicalID;

    /* ECUC_Can_00317:
        Enables / disables API Can_MainFunction_Read() for handling PDU reception events
        in polling mode. */
    Can_ProcessingType                  RxProcessing;

    /* ECUC_Can_00318:
        Enables / disables API Can_MainFunction_Write() for handling PDU transmission events
        in polling mode. */
    Can_ProcessingType                  TxProcessing;

#if (CAN_WAKEUP_SUPPORT == STD_ON)
    /* ECUC_Can_00319:
        Enables / disables API Can_MainFunction_Wakeup() for handling wakeup events
        in polling mode. */
    Can_ProcessingType                  WakeupProcessing;

    /* Non-AUTOSAR:
        Enables/disables handling for wakeup events */
    boolean                             WakeupSupport;

    /* ECUC_Can_00359:
        This parameter contains a reference to the Wakeup Source for this
        controller as defined in the ECU State Manager. */
    uint32                              WakeupSourceId;

#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */
    /* SWS_Can_00231 SWS_Can_00232
        Enables / disables Controller interrupt */
    Can_InterruptStateType              InterruptState;

#if (CANFD_MODE_SUPPORT == STD_ON)
    boolean                             CanFDSupport;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

    /* ECUC_Can_00435:
       Reference to baudrate configuration container configured for the Can Controller. */
    uint8                               DefaultBaudrate;
    const Can_ControllerBaudrateType    *BaudrateCfgPtr;
    uint8                               NumberofBaudrate;

    /* Non-AUTOSAR:
        Pointer to CAN controller corresponding Message RAM Mapping configuration */
    const Can_ControllerMsgRAMConfigType *MsgRAMMapConfigPtr;

} Can_ControllerConfigType;

/* #Violation: Can_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* Maximum number of controllers allocated to the core */
    Can_IdType                      MaxCoreController;

    /* The index of the configuration allocated to the core */
    const Can_ControllerConfigType  *CanControllerCfgPtr;

    /* Maximum number of the Hrh channels allocated to the core */
    Can_HwHandleType                MaxCoreHrhChannels;

    /* Maximum number of the Hth channels allocated to the core */
    Can_HwHandleType                MaxCoreHthChannels;

    /* Maximum number of the Hoh channels allocated to the core */
    Can_HwHandleType                MaxCoreHohChannels;

    /* The index of the Hoh channels allocated to the core */
    const Can_HwHandleType          *CanHohToCoreCfgPtr;
}Can_CoreConfigType;

/* SWS_Can_00413,ECUC_Can_00343:
   This is the type of the external data structure containing the overall initialization 
   data for the CAN driver and SFR settings affecting all controllers. 
   Furthermore it contains pointers to controller configuration structures. 
   The contents of the initialization data structure are CAN hardware specific. */
typedef struct
/* #Violation: Can_GeneralTypes_h_REF_3 */
{
    /* Pointer to the Core specific CAN configuration set */
    const Can_CoreConfigType        *CoreConfigPtr[MCAL_NUMBER_OF_CORES];

    /* Pointer to the Hardwareobject configuration set */
    const Can_HardwareObjectType    *HardwareObjectCfgPtr;

    /* Pointer to the mapping of controllers allocation cores */
    const uint8                     *ControllerToCorePtr;

    /* Pointer to the mapping of HwObjects allocation controllers */
    const uint16                    *HwObjToCoreMapPtr;

    /* The Controller Map to CoreID index to check the relationship between controllers and cores */
    const Mcal_CoreType             *ControllerMapListPtr;
} Can_ConfigType;


#endif /* _CAN_GENERAL_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

