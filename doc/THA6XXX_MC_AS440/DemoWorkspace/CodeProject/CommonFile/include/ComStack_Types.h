/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : ComStack_Types.h
*
*   Platform             : AUTOSAR
*
*   brief                : 
*
*   Autosar Version      : 4.4.0
*
*   SW Version           : 1.0.0
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Std_Types.h"
#include "ComStack_Cfg.h"
/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/*Action has been successfully finished*/
#define NTFRSLT_OK           0x00

/*Message not successfully received or sent out*/
#define NTFRSLT_E_NOT_OK     0x01

/*Timer N_Ar/N_As has passed its time-out value N_Asmax/N_Armax*/
#define NTFRSLT_E_TIMEOUT_A  0x02

/*Timer N_Bs has passed its time-out value N_Bsmax*/
#define NTFRSLT_E_TIMEOUT_BS 0x03

/*Timer N_Cr has passed its time-out value N_Crmax*/
#define NTFRSLT_E_TIMEOUT_CR 0x04

/*Unexpected sequence number (PCI.SN) value received*/
#define NTFRSLT_E_WRONG_SN   0x05

/*Invalid or unknown FlowStatus value has been received*/
#define NTFRSLT_E_INVALID_FS 0x06

/*Unexpected protocol data unit received*/
#define NTFRSLT_E_UNEXP_PDU  0x07

/*Flow control WAIT frame that exceeds the maximum counter N_WFTmax received*/
#define NTFRSLT_E_WFT_OVRN   0x08

/*Flow control (FC) N_PDU with FlowStatus = OVFLW received*/
#define NTFRSLT_E_ABORT  0x09

/*Indicates an abort of a transmission*/
#define NTFRSLT_E_NO_BUFFER  0x0A

/*Requested cancellation has been executed*/
#define NTFRSLT_E_CANCELATION_OK 0x0B

/*Request cancellation has not been executed*/
#define NTFRSLT_E_CANCELATION_NOT_OK 0x0C

/*The parameter change request has been successfully executed*/
#define NTFRSLT_PARAMETER_OK  0x0D

/*The request for the change of the parameter did not complete successfully*/
#define NTFRSLT_E_PARAMETER_NOT_OK  0x0E

/*The parameter change request not executed successfully due to an ongoing reception*/
#define NTFRSLT_E_RX_ON 0x0F

/*The parameter change request not executed successfully due to a wrong value*/
#define NTFRSLT_E_VALUE_NOT_OK 0x10

/*SWS_COMTYPE_00021*/
#define BUSTRCV_OK           0x00
#define BUSTRCV_E_ERROR      0x01
/***************************************************************************************************
*                               Typedef Enum
***************************************************************************************************/
/*SWS_COMTYPE_00012*/
typedef enum
{
    BUFREQ_OK = 0,              /*Buffer request accomplished successful*/
    BUFREQ_E_NOT_OK = 1,        /*Buffer request not successful. Buffer cannot be accessed*/
    BUFREQ_E_BUSY = 2,          /*Temporarily no buffer available. It's up the requestor to retry request for a certain time.*/
    BUFREQ_E_OVFL = 3           /*No Buffer of the required length can be provided*/
} BufReq_ReturnType;            /*Variables of this type are used to store the result of a buffer request.*/

/*SWS_COMTYPE_00031*/
typedef enum
{
    TP_STMIN = 0,               /*Separation Time*/
    TP_BS = 1,                  /*Block Size */
    TP_BC = 2                   /*Band width control parameter used in FlexRay transport protocol module*/
} TPParameterType;              /*Specify the parameter to which the value has to be changed (BS or STmin)*/

/*SWS_COMTYPE_00027*/
typedef enum
{
    TP_DATACONF = 0,            /*Indicates that all data, that have been copied so far, are confirmed
                                * confirmed and can be removed from the TP buffer*/
    TP_DATARETRY = 1,           /*Indicates that this API call shall copy already copied data in 
                                * order to recover from an error */
    TP_CONFPENDING = 2          /*Indicates that the previously copied data must remain in the TP*/
} TpDataStateType;

/*SWS_COMTYPE_00040*/
typedef enum
{
    ICOM_SWITCH_E_OK = 0,       /*The activation of Pretended Networking was successful*/
    ICOM_SWITCH_E_FAILED = 1    /*The activation of Pretended Networking was not successful*/
} IcomSwitch_ErrorType;
/***************************************************************************************************
*                               Type Definitions
***************************************************************************************************/
/*SWS_COMTYPE_00011*/
/* Basic information about a PDU of any type */
typedef struct
{
  uint8          *SduDataPtr;
  uint8          *MetaDataPtr;
  PduLengthType   SduLength;
} PduInfoType;

/*SWS_COMTYPE_00037*/
typedef struct
{
    TpDataStateType TpDataState;        /*The enum type to be used to store the state of Tp buffer*/
    PduLengthType  TxTpDataCnt;         /*length of the SDU in bytes*/
} RetryInfoType;

/*SWS_COMTYPE_00038*/
typedef uint8       NetworkHandleType;  /*Variables of the type NetworkHandleType shall be used to
                                        *       store the identifier of a communication channel.*/
/*SWS_COMTYPE_000368*/
typedef uint8       PNCHandleType;      /*Used to store the identifier of a partial network cluster.*/

/*SWS_COMTYPE_00039*/
typedef uint8       IcomConfigIdType;   /*IcomConfigIdType defines the configuration ID.*/


/*SWS_COMTYPE_00020*/
typedef uint8       BusTrcvErrorType;   /*Variables of this type shall be used to return the bus status
                                        *       evaluated by a transceiver.*/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/

#endif /* COMSTACK_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
