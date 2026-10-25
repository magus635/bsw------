/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Eth_Types.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Ethernet
 *
 *   brief                 : This file contains all type definitions of Ethernet Driver
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
*#Eth_Types_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity.
*
*#Eth_Types_h_REF_2:MISRAC2012-Rule-2.3; 
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*/
#ifndef Eth_Types_H
#define Eth_Types_H
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Eth_GeneralTypes.h"
/* \[SWS_Eth_00005]*/
#include "Eth_Cfg.h"
#include "Mcall.h"
/* \[SWS_Eth_00158] [SWS_Eth_00163][SWS_Eth_00178][SWS_Eth_00179][SWS_Eth_00180]*/
#include "eth_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
#define ETH_DISABLE_DEM_REPORT                (FALSE)    

#include "Dem.h"

typedef Eth_Config   EthSdkCtrlConfigType;

/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/

typedef enum
{
    ETH_CNTRL_NOT_INITIALIZED = 0x0U,/* controller is not initialized */
    ETH_CNTRL_INITIALIZED = 0x1U,/* controller is initialized */
    ETH_CNTRL_INITIALIZED_DOWN = 0x2U,/* controller is initialized and set to Down */
    ETH_CNTRL_INITIALIZED_ACTIVE = 0x3U/* controller is initialized and set to Active */
} Eth_ControllerInitStateType;


typedef enum
{
    ETH_TX_DESC_NOUSE = 0U,               /*  not_used; */
    ETH_TX_DESC_ASSIGNED,                 /*  assigned by provideTxBuf; */
    ETH_TX_DESC_TRANSMIT_WITH_CONFIRM     /* transmit with confirmation */
} Eth_TxdescTxConfirmType;


/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/


typedef struct
{
    /*DEM Id for ETH_E_ACCESS Failure.*/
    Dem_EventIdType EthDemAccess;
    /*DEM Id for ETH_E_RX_FRAMES_LOST Failure.*/
    Dem_EventIdType EthDemFramesLost;
    /*DEM Id for ETH_E_ALIGNMENT Failure.*/
    Dem_EventIdType EthDemAlignment;
    /*DEM Id for ETH_E_CRC Failure.*/
    Dem_EventIdType EthDemCRC;
    /*DEM Id for ETH_E_UNDERSIZEFRAME Failure.*/
    Dem_EventIdType EthDemUndersize;
    /*DEM Id for ETH_E_OVERSIZEFRAME Failure.*/
    Dem_EventIdType EthDemOversize;
    /*DEM Id for ETH_E_SINGLE_COLLISION Failure.*/
    Dem_EventIdType EthDemSingleCollision;
    /*DEM Id for ETH_E_MULTIPLE_COLLISION Failure.*/
    Dem_EventIdType EthDemMultipleCollision;
    /*DEM Id for ETH_E_LATE_COLLISION Failure.*/
    Dem_EventIdType EthDemLateCollision;
} Eth_DemType;


typedef struct
{
    /*num of frame for ETH_E_ACCESS .*/
    uint32 EthDemAccessCnt;
    /*num of frame for ETH_E_RX_FRAMES_LOST Failure.*/
    uint32 EthDemFramesLostCnt;
    /*num of frame for ETH_E_ALIGNMENT Failure.*/
    uint32 EthDemAlignmentCnt;
    /*num of frame for ETH_E_CRC Failure.*/
    uint32 EthDemCRCCnt;
    /*num of frame for ETH_E_UNDERSIZEFRAME Failure.*/
    uint32 EthDemUndersizeCnt;
    /*num of frame for ETH_E_OVERSIZEFRAME Failure.*/
    uint32 EthDemOversizeCnt;
    /*num of frame for ETH_E_SINGLE_COLLISION Failure.*/
    uint32 EthDemSingleCollisionCnt;
    /*num of frame for ETH_E_MULTIPLE_COLLISION Failure.*/
    uint32 EthDemMultipleCollisionCnt;
    /*num of frame for ETH_E_LATE_COLLISION Failure.*/
    uint32 EthDemLateCollisionCnt;
} Eth_DemErrorCnt;

/* #Violation: Eth_Types_h_REF_1*/
typedef struct
{
    const EthSdkCtrlConfigType *EthSdkCtrlConfigPtr;

    /* Pointer to the mapping of Tx FIFO to Channels */
    const uint8       *EthTxFifoChnlMapPtr;
    /* Pointer to the mapping of configured Priority to FifoIdx */
    const uint8       *EthTxPrioFifoMapPtr;
    /* Pointer to the mapping of Rx FIFO to Channels */
    const uint8       *EthRxFifoChnlMapPtr;
    /* Ethernet Controller Index */
    uint8              EthCtrlIdx;
    const Eth_DemType *EthDemPtr;/* pointer to Eth Dem */

} EthCtrlConfigType;

/* #Violation: Eth_Types_h_REF_1*/
typedef struct
{
    const EthCtrlConfigType *EthCtrlConfigPtr;

    /* maximum controllers allocated to current core */
    uint8               EthMaxControllers;
} Eth_CoreConfigType;
/* #Violation: Eth_Types_h_REF_1*/
typedef struct
{
    /* index of Execution core */
    uint8         CoreChIdx;
    /* Execution core */
    Mcal_CoreType ExecutionCore;
} Eth_MappingType;
/* \[SWS_Eth_00156] */
/* Structure for PB configuration(for initialization) */
/* #Violation: Eth_Types_h_REF_1*/
typedef struct
{
    /* Pointer to Core Configuration structure */
    const Eth_CoreConfigType *EthCoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /*The routing relationship between channels and cores*/
    const Eth_MappingType              *EthIdMapPtr;
} Eth_ConfigType;



/* Structure for controller's state */
/* #Violation: Eth_Types_h_REF_1*/
typedef struct
{
    Eth_NodeHandle              Node;
    Eth_StateType               DriverState;
    Eth_ControllerInitStateType CntrlState; /* controller states */
    Eth_DemErrorCnt             DemErrorCnt;
    /* Array of pointers to store the current DataPtr values for Ingress
     * timestamping */
    Eth_DataType* RxTmStmpDataPtr[4];

} Eth_ControllerStateType;

typedef struct
{
    Eth_ControllerStateType *ControllerStatePtr; /* controller states */
/* #Violation: Eth_Types_h_REF_2*/
} Eth_StatusType;

#endif /* Eth_Types_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

