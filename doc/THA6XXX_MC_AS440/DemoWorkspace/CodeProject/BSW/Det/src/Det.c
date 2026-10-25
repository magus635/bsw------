/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Det.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Det
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
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
#include "Std_Types.h"
#include "Det.h"
#include "Mcall.h"
#include "Compiler.h"
#include "Demo_Common.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

Det_Error GstDetErrBuffer[DET_ERROR_BUFFER_SIZE];
uint8 GstDetBuffIndex[MCAL_NUMBER_OF_CORES] = {0x00};
Runtime_Error GstRTErrBuffer[RUNTIME_ERROR_BUFFER_SIZE];
uint8 GstRTBuffIndex[MCAL_NUMBER_OF_CORES] = {0x00};
TransientFault_Error GstTFErrBuffer[TF_ERROR_BUFFER_SIZE];
uint8 GstTFBuffIndex[MCAL_NUMBER_OF_CORES] = {0x00};

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

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(Std_ReturnType, DET_CODE) Det_ReportError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
)
{
    Det_Error     *DetBufferPtr;
    Mcal_CoreType CoreId;
    
    CoreId = Mcal_GetCoreId();
    /* DET error is reported */
    if (GstDetBuffIndex[CoreId] < DET_ERROR_BUFFER_SIZE)
    {
        DetBufferPtr = &GstDetErrBuffer[GstDetBuffIndex[CoreId]];
        GstDetBuffIndex[CoreId]++;
        DetBufferPtr->ModuleId[CoreId] = ModuleId;
        DetBufferPtr->InstanceId[CoreId] = InstanceId;
        DetBufferPtr->ApiId[CoreId] = ApiId;
        DetBufferPtr->ErrorId[CoreId] = ErrorId;
    }

    DEBUG_PRINTF("Det error, ModuleId is %03d,  InstanceId is 0x%02x, ApiId is 0x%02x, ErrorId is 0x%02x, Core Id is %d\n",
                 ModuleId, InstanceId, ApiId, ErrorId, CoreId);
    return E_OK;
}

FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
)
{
    Runtime_Error *RTBufferPtr;
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    /* Runtime error is reported */
    if (GstRTBuffIndex[CoreId] < RUNTIME_ERROR_BUFFER_SIZE)
    {
        RTBufferPtr = &GstRTErrBuffer[GstRTBuffIndex[CoreId]++];
        RTBufferPtr->ModuleId[CoreId] = ModuleId;
        RTBufferPtr->InstanceId[CoreId] = InstanceId;
        RTBufferPtr->ApiId[CoreId] = ApiId;
        RTBufferPtr->ErrorId[CoreId] = ErrorId;
    }

    DEBUG_PRINTF("Runtime error, ModuleId is %03d,  InstanceId is 0x%02x, ApiId is 0x%02x, ErrorId is 0x%02x, CoreId is %d",
                 ModuleId, InstanceId, ApiId, ErrorId, CoreId);
    return E_OK;
}

FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
)
{
    TransientFault_Error *TFBufferPtr;
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    /* Transient Fault error is reported */
    if (GstTFBuffIndex[CoreId] < TF_ERROR_BUFFER_SIZE)
    {
        TFBufferPtr = &GstTFErrBuffer[GstTFBuffIndex[CoreId]++];
        TFBufferPtr->ModuleId[CoreId] = ModuleId;
        TFBufferPtr->InstanceId[CoreId] = InstanceId;
        TFBufferPtr->ApiId[CoreId] = ApiId;
        TFBufferPtr->ErrorId[CoreId] = ErrorId;
    }
    else
    {
        /* Do nothing */
    }

    DEBUG_PRINTF("Transient Fault, ModuleId is %03d,  InstanceId is 0x%02x, ApiId is 0x%02x, ErrorId is 0x%02x, CoreId is %d",
                 ModuleId, InstanceId, ApiId, ErrorId, CoreId);
    return E_OK;
}

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
