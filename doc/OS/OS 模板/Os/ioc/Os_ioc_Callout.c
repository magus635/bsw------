/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Callout.c
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : [!"$datetime"!]
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsIoc/*) != 0"!][!//
#include "Os_ioc.h"
#include "Os_ioc_types.h"
#include "Os_ioc_Cfg.h"
#include "Os_ioc_Lcfg.h"
#include "Os_task.h"
#include "Os_isr.h"
#include "Os_application.h"
#include "Os_application_types.h"
#include "Os_kernel.h"
#include "Os_ioc_Callout.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
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
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsIoc/*) != 0"!][!//
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"

[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "CurrentIocName" = "node:name(.)"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
FUNC(Std_ReturnType, OS_CODE) IocWrite[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                [!VAR "FindType" = "'false'"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                    [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                        [!VAR "FindType" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    uint32 CallbackCount;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].SenderApplication) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        /* Write data to buffer */
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                [!VAR "FindType" = "'false'"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                    [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                        [!VAR "FindType" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "count(../*) = 1"!][!//
        OsIoc_[!"$CurrentIocName"!]_Buffer = [!IF "$FindType = 'false'"!]*[!ENDIF!]Data_[!"@index"!];
                [!ELSE!][!//
        OsIoc_[!"$CurrentIocName"!]_Buffer_[!"@index"!] = [!IF "$FindType = 'false'"!]*[!ENDIF!]Data_[!"@index"!];
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        /* If this channel has callback */
        if(Os_IocConfig_[!"$CurrentIocName"!].CallbackCount > 0)
        {
            [!INDENT "12"!][!//
            /* Call callback function */
            for(CallbackCount = 0U; CallbackCount < Os_IocConfig_[!"$CurrentIocName"!].CallbackCount; CallbackCount++)
            {
                [!INDENT "16"!][!//
                Status = OsIoc_CallCallback(&Os_IocConfig_[!"$CurrentIocName"!].IocCallbacks[CallbackCount]);
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        }
        else
        {
            [!INDENT "12"!][!//
            /* Do nothing */
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
FUNC(Std_ReturnType, OS_CODE) IocRead[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
            [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].RecevierAppliaction) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        /* Read data from buffer */
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                [!IF "count(../*) = 1"!][!//
        *Data_[!"@index"!] = OsIoc_[!"$CurrentIocName"!]_Buffer;
                [!ELSE!][!//
        *Data_[!"@index"!] = OsIoc_[!"$CurrentIocName"!]_Buffer_[!"@index"!];
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        [!ENDINDENT!][!//
    }
    return Status;
    [!ENDINDENT!][!//
}

        [!ENDLOOP!][!//
    [!ELSE!][!//
        [!IF "(OsIocReceiverProperties/*/OsIocReceiveCallbackEnable = 'false') and (count(OsIocSenderProperties/*) > 1)"!][!//
            [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
FUNC(Std_ReturnType, OS_CODE) IocSend_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data
                    [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].SenderApplication) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        if((Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].WriteIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE == Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].ReadIndex)
        {
            [!INDENT "12"!][!//
            /* FIFO Full */
            Status = IOC_E_LIMIT;
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].DataLostCount++;
            [!ENDINDENT!][!//
        }
        else
        {
            [!INDENT "12"!][!//
            /* Write data to buffer */
                [!VAR "FindType" = "'false'"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                    [!IF "../../OsIocDataProperties/*/OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                        [!VAR "FindType" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            OsIoc_[!"$CurrentIocName"!]_Buffer[[!"@index"!]][Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].WriteIndex] = [!IF "$FindType = 'false'"!]*[!ENDIF!]Data;
            /* Increment of write index */
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].WriteIndex = (Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[[!"@index"!]].WriteIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE;
            Status = IOC_E_OK;
            [!ENDINDENT!][!//
        }
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

            [!ENDLOOP!][!//
FUNC(Std_ReturnType, OS_CODE) IocReceive_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    Std_ReturnType Status;
    uint32 ReceiveChannelCount;
    uint32 ReceiveChannel;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].RecevierAppliaction) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        ReceiveChannel = Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->NextReceiveChannel;
        for(ReceiveChannelCount = 0; ReceiveChannelCount < Os_IocConfig_[!"$CurrentIocName"!].ReceiveChannelNum; ReceiveChannelCount++)
        {
            [!INDENT "12"!][!//
            if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].WriteIndex == Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].ReadIndex)
            {
                [!INDENT "16"!][!//
                /* If data lost count has changed */
                if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCountRecord != Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCount)
                {
                    [!INDENT "20"!][!//
                    Status = IOC_E_NO_DATA_AND_LOST_DATA;
                    /* Update DataLostCountRecord */
                    Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCountRecord = Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCount;
                    [!ENDINDENT!][!//
                }
                else
                {
                    [!INDENT "20"!][!//
                    Status = IOC_E_NO_DATA;
                    [!ENDINDENT!][!//
                }
                [!ENDINDENT!][!//
            }
            else
            {
                [!INDENT "16"!][!//
                /* Read data from buffer */
                *Data = OsIoc_[!"$CurrentIocName"!]_Buffer[ReceiveChannel][Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].ReadIndex];
                /* Increment of read index */
                Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].ReadIndex = (Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].ReadIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE;
                /* If data lost count has changed */
                if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCountRecord != Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCount)
                {
                    [!INDENT "20"!][!//
                    Status = IOC_E_OK_AND_LOST_DATA;
                    /* Update DataLostCountRecord */
                    Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCountRecord = Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannel].DataLostCount;
                    [!ENDINDENT!][!//
                }
                else
                {
                    [!INDENT "20"!][!//
                    Status = IOC_E_OK;
                    [!ENDINDENT!][!//
                }
                [!ENDINDENT!][!//
            }
            ReceiveChannel++;
            if(ReceiveChannel >= Os_IocConfig_[!"$CurrentIocName"!].ReceiveChannelNum)
            {
                [!INDENT "16"!][!//
                ReceiveChannel = 0U;
                [!ENDINDENT!][!//
            }
            if(Status != IOC_E_NO_DATA)
            {
                [!INDENT "16"!][!//
                break;
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        }
        Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->NextReceiveChannel = ReceiveChannel;
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    uint32 ReceiveChannelCount;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if((OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].RecevierAppliaction) != E_OK) &&
       [!INDENT "7"!][!//
       (OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].SenderApplication) != E_OK))
       [!ENDINDENT!][!//
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        for(ReceiveChannelCount = 0; ReceiveChannelCount < Os_IocConfig_[!"$CurrentIocName"!].ReceiveChannelNum; ReceiveChannelCount++)
        {
            [!INDENT "12"!][!//
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannelCount].WriteIndex = 0U;
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData[ReceiveChannelCount].ReadIndex = 0U;
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

        [!ELSE!][!//
            [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
FUNC(Std_ReturnType, OS_CODE) IocSend[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                    [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].SenderApplication) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        if((Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE == Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex)
        {
            [!INDENT "12"!][!//
            /* FIFO Full */
            Status = IOC_E_LIMIT;
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCount++;
            [!ENDINDENT!][!//
        }
        else
        {
            [!INDENT "12"!][!//
            /* Write data to buffer */
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "count(../*) = 1"!][!//
            OsIoc_[!"$CurrentIocName"!]_Buffer[Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex] = [!IF "$FindType = 'false'"!]*[!ENDIF!]Data_[!"@index"!];
                    [!ELSE!][!//
            OsIoc_[!"$CurrentIocName"!]_Buffer_[!"@index"!][Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex] = [!IF "$FindType = 'false'"!]*[!ENDIF!]Data_[!"@index"!];
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            /* Increment of write index */
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex = (Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE;
            Status = IOC_E_OK;
            [!ENDINDENT!][!//
        }
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        /* If this channel has callback */
        if((Status == IOC_E_OK) && (Os_IocConfig_[!"$CurrentIocName"!].CallbackCount > 0))
        {
            [!INDENT "12"!][!//
            /* Call callback function */
            Status = OsIoc_CallCallback(Os_IocConfig_[!"$CurrentIocName"!].IocCallbacks);
            [!ENDINDENT!][!//
        }
        else
        {
            [!INDENT "12"!][!//
            /* Do nothing */
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
FUNC(Std_ReturnType, OS_CODE) IocReceive[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Os_IsrLevelType Level;
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if(OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].RecevierAppliaction) != E_OK)
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        /* Get interrupt lock/spinlock according to ioc config */
        OsIoc_GetLock(&Os_IocConfig_[!"$CurrentIocName"!], &Level);
        if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex == Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex)
        {
            [!INDENT "12"!][!//
            /* If data lost count has changed */
            if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCountRecord != Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCount)
            {
                [!INDENT "16"!][!//
                Status = IOC_E_NO_DATA_AND_LOST_DATA;
                /* Update DataLostCountRecord */
                Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCountRecord = Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCount;
                [!ENDINDENT!][!//
            }
            else
            {
                [!INDENT "16"!][!//
                Status = IOC_E_NO_DATA;
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        }
        else
        {
            [!INDENT "12"!][!//
            /* Read data from buffer */
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!IF "count(../*) = 1"!][!//
            *Data_[!"@index"!] = OsIoc_[!"$CurrentIocName"!]_Buffer[Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex];
                    [!ELSE!][!//
            *Data_[!"@index"!] = OsIoc_[!"$CurrentIocName"!]_Buffer_[!"@index"!][Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex];
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            /* Increment of read index */
            Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex = (Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex + 1) % OS_IOC_[!"text:toupper($CurrentIocName)"!]_BUFFER_SIZE;
            /* If data lost count has changed */
            if(Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCountRecord != Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCount)
            {
                [!INDENT "16"!][!//
                Status = IOC_E_OK_AND_LOST_DATA;
                /* Update DataLostCountRecord */
                Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCountRecord = Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->DataLostCount;
                [!ENDINDENT!][!//
            }
            else
            {
                [!INDENT "16"!][!//
                Status = IOC_E_OK;
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        }
        /* Release interrupt lock/spinlock according to ioc config */
        OsIoc_ReleaseLock(&Os_IocConfig_[!"$CurrentIocName"!], Level);
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

            [!ENDLOOP!][!//
FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    Std_ReturnType Status;

    if(IsNeedSysTrap())
    {
        [!INDENT "8"!][!//
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        [!ENDINDENT!][!//
    }
    /* App access check */
    if((OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].RecevierAppliaction) != E_OK) &&
       [!INDENT "7"!][!//
       (OsIoc_ApplicationAccessCheck(Os_IocConfig_[!"$CurrentIocName"!].SenderApplication) != E_OK))
       [!ENDINDENT!][!//
    {
        [!INDENT "8"!][!//
        Status = E_OS_ACCESS;
        [!ENDINDENT!][!//
    }
    else
    {
        [!INDENT "8"!][!//
        Status = IOC_E_OK;
        Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->WriteIndex = 0U;
        Os_IocConfig_[!"$CurrentIocName"!].IocRunningData->ReadIndex = 0U;
        [!ENDINDENT!][!//
    }

    return Status;
    [!ENDINDENT!][!//
}

        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//