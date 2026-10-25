/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Det.h
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

#ifndef DET_H
#define DET_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Mcall.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/




#define DET_ERROR_BUFFER_SIZE 60U
#define RUNTIME_ERROR_BUFFER_SIZE 60U
#define TF_ERROR_BUFFER_SIZE 60U


/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Defining the structure to store the parameters of Det Report Error
   function */
typedef struct
{ /* It will store the ModuleId of the reporting module */
  uint16 ModuleId[MCAL_NUMBER_OF_CORES];
  /* It will store the index based InstanceId of the reporting module */
  uint8 InstanceId[MCAL_NUMBER_OF_CORES];
  /* It will store the ApiId of the reporting function */
  uint8 ApiId[MCAL_NUMBER_OF_CORES];
  /* It will store the ErrorId of the reporting error */
  uint8 ErrorId[MCAL_NUMBER_OF_CORES];
}Det_Error;

/* Defining the structure to store the parameters of Runtime error Report Error
   function */
typedef struct
{ /* It will store the ModuleId of the reporting module */
  uint16 ModuleId[MCAL_NUMBER_OF_CORES];
  /* It will store the index based InstanceId of the reporting module */
  uint8 InstanceId[MCAL_NUMBER_OF_CORES];
  /* It will store the ApiId of the reporting function */
  uint8 ApiId[MCAL_NUMBER_OF_CORES];
  /* It will store the ErrorId of the reporting error */
  uint8 ErrorId[MCAL_NUMBER_OF_CORES];
}Runtime_Error;

/* Defining the structure to store the parameters of Transient Fault Report Error
   function */
typedef struct
{ /* It will store the ModuleId of the reporting module */
  uint16 ModuleId[MCAL_NUMBER_OF_CORES];
  /* It will store the index based InstanceId of the reporting module */
  uint8 InstanceId[MCAL_NUMBER_OF_CORES];
  /* It will store the ApiId of the reporting function */
  uint8 ApiId[MCAL_NUMBER_OF_CORES];
  /* It will store the ErrorId of the reporting error */
  uint8 ErrorId[MCAL_NUMBER_OF_CORES];
}TransientFault_Error;

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern Det_Error GstDetErrBuffer[DET_ERROR_BUFFER_SIZE];
extern uint8 GstDetBuffIndex[MCAL_NUMBER_OF_CORES];
extern Runtime_Error GstRTErrBuffer[RUNTIME_ERROR_BUFFER_SIZE];
extern uint8 GstRTBuffIndex[MCAL_NUMBER_OF_CORES];
extern TransientFault_Error GstTFErrBuffer[TF_ERROR_BUFFER_SIZE];
extern uint8 GstTFBuffIndex[MCAL_NUMBER_OF_CORES];

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern FUNC(Std_ReturnType, DET_CODE) Det_ReportError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);

extern FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);

extern FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);

#endif /* DET_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
