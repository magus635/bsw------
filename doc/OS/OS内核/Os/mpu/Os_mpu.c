/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu.c
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
#include "Std_Types.h"
#include "Os_kernel.h"
#include "Os_application.h"
#include "Os_mpu_types.h"
#include "Os_mpu_hal.h"
#include "Os_mpu.h"
#include "Os_mpu_Lcfg.h"
#include "Os_isr_types.h"
#include "Os_hook.h"
#include "Os_isr.h"
#include "Os_isr_Lcfg.h"
#include "Os.h"
#include "Os_services.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
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
*   Function Name           : OsAccess_Internal_CheckAccess
*   Service ID              : None.
*   Description             : This function check the start address and end address in the range of region.
*   Parameters in           : PtrAccessRegions: The pointer to Access regions strcuture
*                             StartAddress: The start address of the region
*                             EndAddress: The end address of the region
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : OsAccess_RightType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckAccess
(
    P2VAR(Os_AccessConfigRefType, TYPEDEF, OS_VAR) PtrAccessRegions,
    uint32 StartAddress,
    uint32 EndAddress
);

/****************************************************************************************************
*   Function Name           : OsAccess_Internal_CheckObjectMemoryAccess
*   Service ID              : None.
*   Description             : The internal function to check access permission.
*   Parameters in           : ObjectID: The ID of Object
*                             Address: The pointer to start address to be checked
*                             Size: The size of the checked address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : OsAccess_RightType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckObjectMemoryAccess
(
    AccessObjectType ObjectID,
    MemoryStartAddressType Address,
    MemorySizeType Size
);

/****************************************************************************************************
*   Function Name           : OsAccess_Internal_CheckISRMemoryAccess
*   Service ID              : None.
*   Description             : The internal function of  CheckISRMemoryAccess.
*   Parameters in           : ISRID :The ID of ISR
*                             Address: The pointer to start address to be checked
*                             Size: The size of the checked address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : OsAccess_RightType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckISRMemoryAccess
(
    ISRType ISRID,
    MemoryStartAddressType Address,
    MemorySizeType Size
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_CheckAccess
*   Service ID              : None.
*   Description             : To check whether the peripheral address in the area or not.
*   Parameters in           : AreaID :The ID of hardware peripheral area reference
*                             Address: The pointer to start address to be checked
*                             Size: The size of the checked address, the value is 1(uint8),2(uint16),4(uint32)
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_CheckAccess
(
    AreaIdType AreaID,
    const void *Address,
    uint8 Size
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Read8
*   Service ID              : None.
*   Description             : To check whether the peripheral address in the area or not.
*   Parameters in           : Area : hardware peripheral area reference
*                             Address: The pointer to start address to be checked
*   Parameters inout        : None.
*   Parameters out          : ReadValue : content of the given memory location (<Address>).
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Read8
(
    AreaIdType Area,
    const uint8* Address,
    uint8* ReadValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Read16
*   Service ID              : None.
*   Description             : This function returns the content of a given memory location (<Address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address: memory address
*   Parameters inout        : None.
*   Parameters out          : ReadValue :content of the given memory location (<Address>) .
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Read16
(
    AreaIdType Area,
    const uint16* Address,
    uint16* ReadValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Read32
*   Service ID              : None.
*   Description             : This function returns the content of a given memory location (<Address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address: memory address
*   Parameters inout        : None.
*   Parameters out          : ReadValue :content of the given memory location (<Address>) .
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Read32
(
    AreaIdType Area,
    const uint32* Address,
    uint32* ReadValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Write8
*   Service ID              : None.
*   Description             : Writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Write8
(
    AreaIdType Area,
    uint8* Address,
    uint8 WriteValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Write16
*   Service ID              : None.
*   Description             : Writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
StatusType OsPeripheral_Internal_Write16
(
    AreaIdType Area,
    uint16* Address,
    uint16 WriteValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Write32
*   Service ID              : None.
*   Description             : Writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Write32
(
    AreaIdType Area,
    uint32* Address,
    uint32 WriteValue
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Modify8
*   Service ID              : None.
*   Description             : This function modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
StatusType OsPeripheral_Internal_Modify8
(
    AreaIdType Area,
    uint8* Address,
    uint8 Clearmask,
    uint8 Setmask
);

/****************************************************************************************************
*   Function Name           : StatusType OsPeripheral_Internal_Modify16 (AreaIdType Area,uint16* Address,uint16 Clearmask,uint16 Setmask);

*   Service ID              : None.
*   Description             : This function modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
StatusType OsPeripheral_Internal_Modify16
(
    AreaIdType Area,
    uint16* Address,
    uint16 Clearmask,
    uint16 Setmask
);

/****************************************************************************************************
*   Function Name           : OsPeripheral_Internal_Modify32
*   Service ID              : None.
*   Description             : This function modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
StatusType OsPeripheral_Internal_Modify32
(
    AreaIdType Area,
    uint32* Address,
    uint32 Clearmask,
    uint32 Setmask
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_AlignStackStartAddress
*   Service ID              : None.
*   Description             : The function align the start address.
*   Parameters in           : Address :memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The alignment address.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
FUNC(uint32, OS_CODE) OsMpu_Internal_AlignStackStartAddress
(
    uint32 Address
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_AlignStackEndAddress
*   Service ID              : None.
*   Description             : The function align the end address.
*   Parameters in           : Address :memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The alignment address.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
FUNC(uint32, OS_CODE) OsMpu_Internal_AlignStackEndAddress
(
    uint32 Address
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_StackRegion
*   Service ID              : None.
*   Description             : The function align the end address.
*   Parameters in           : CoreStackCfg : the pointer to the core stack configuration
*                             StackRegion : the pointer to the stack region configuration
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The alignment address.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None .
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsMpu_Internal_StackRegion
(
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)CoreStackCfg,
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)StackRegion
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckAccess
(
    P2VAR(Os_AccessConfigRefType, TYPEDEF, OS_VAR) PtrAccessRegions,
    uint32 StartAddress,
    uint32 EndAddress
)
{
    OsAccess_RightType Result;
    P2CONST(Os_AccessConfigType, TYPEDEF, OS_CONST) PtrAccess;
    P2CONST(Os_AccessRegionConfig, TYPEDEF, OS_CONST) PtrRegion;
    uint32 RegionIndex;

    if(NULL_PTR == PtrAccessRegions)
    {
        Result = OS_MEM_ACCESS_NON;
    }
    else
    {
        PtrAccess = *PtrAccessRegions;
        if(NULL_PTR == PtrAccess || PtrAccess->RegionCount < 1)
        {
            Result = OS_MEM_ACCESS_NON;
        }
        else
        {
            Result = OS_MEM_ACCESS_NON;
            RegionIndex = 0;

            /*Loop the region of Object to check the start address and end address in the range of region config */
            while(RegionIndex < PtrAccess->RegionCount)
            {
                PtrRegion = &(PtrAccess->RegionInfo[RegionIndex]);
                if((StartAddress >= PtrRegion->StartAddress) && (EndAddress < PtrRegion->EndAddress))
                {
                    /*return the access right*/
                    Result = PtrRegion->AccessRights;
                    break;
                }
                RegionIndex++;
            }

        }
    }
    return Result;
}

FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckObjectMemoryAccess
(
    TaskType TaskID,
    MemoryStartAddressType Address,
    MemorySizeType Size
)
{
    OsAccess_RightType Result;
    uint32 StartAddress;
    uint32 EndAddress;

    P2VAR(Os_AccessConfigRefType, TYPEDEF, OS_VAR) PtrAccessRegions;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  AccessObjectPtr;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CHECKTASKMEMORYACCESS);
    OS_ARTI_SC_BEGIN(CheckTaskMemoryAccess, TaskID);

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        Result =  OS_MEM_ACCESS_NON;
    }
    else if (OsService_ExtendedErrorCheck(Size < 1U))
    {
        Result =  OS_MEM_ACCESS_NON;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Result = OS_MEM_ACCESS_NON;
    }
    else
    {
        TaskPtr =  OsTask_GetTaskConst(TaskID);
        AccessObjectPtr = OsApp_GetSpecific_ObjectInfo(TaskPtr->ObjectID);
        PtrAccessRegions = (*AccessObjectPtr->ObjectDataInfo.ObjectContextInfoPtr)->AccessCheckInfoPtr;

        StartAddress = (uint32)(Address);
        EndAddress = (StartAddress + Size);
        Result = OsAccess_Internal_CheckAccess(PtrAccessRegions,StartAddress,EndAddress);
    }

    OS_ARTI_SC_END(CheckTaskMemoryAccess, Result);
    OsOrti_ServiceEnd(OS_SERVICEID_CHECKTASKMEMORYACCESS);

    return Result;
}

FUNC(OsAccess_RightType, OS_CODE) OsAccess_Internal_CheckISRMemoryAccess
(
    ISRType ISRID,
    MemoryStartAddressType Address,
    MemorySizeType Size
)
{
    OsAccess_RightType Result;
    uint32 StartAddress;
    uint32 EndAddress;
    P2VAR(Os_AccessConfigRefType, TYPEDEF, OS_VAR) PtrAccessRegions;
    P2CONST(Os_IsrConfigType, TYPEDEF, OS_CONST) ISRPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  AccessObjectPtr;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CHECKISRMEMORYACCESS);
    OS_ARTI_SC_BEGIN(CheckISRMemoryAccess, ISRID);

    if(OsService_ExtendedErrorCheck(ISRID >= OS_ISR_TOTAL_NUM))
    {
        Result =  OS_MEM_ACCESS_NON;
    }
    else if (OsService_ExtendedErrorCheck(Size < 1U))
    {
        Result =  OS_MEM_ACCESS_NON;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Result = OS_MEM_ACCESS_NON;
    }
    else
    {
        ISRPtr =  Os_IsrConfigSet[ISRID];
        AccessObjectPtr = OsApp_GetSpecific_ObjectInfo(ISRPtr->ObjectID);
        PtrAccessRegions = (*AccessObjectPtr->ObjectDataInfo.ObjectContextInfoPtr)->AccessCheckInfoPtr;

        StartAddress = (uint32)Address;
        EndAddress = (StartAddress + Size);
        Result = OsAccess_Internal_CheckAccess(PtrAccessRegions,StartAddress,EndAddress);
    }

    OS_ARTI_SC_END(CheckISRMemoryAccess, Result);
    OsOrti_ServiceEnd(OS_SERVICEID_CHECKISRMEMORYACCESS);

    return Result;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_CheckAccess
(
    AreaIdType AreaID,
    const void *Address,
    uint8 Size
)
{
    StatusType Status;
    uint32 StartAddress;
    uint32 EndAddress;
    uint32 AppID;
    uint32 AppMask;
    P2CONST(Os_PeripheralConfigType, TYPEDEF, OS_CONST) pPeripheralRight;

    AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
    AppMask = (uint32)(1UL << AppID);
    pPeripheralRight = OsMpu_PeripheralRefs[AreaID];
    StartAddress = pPeripheralRight->StartAddress;
    EndAddress = pPeripheralRight->EndAddress;

    /*Check the address whether in the range of peripheral or not */
    if(OsService_ExtendedErrorCheck(((uint32)Address <  StartAddress)
        || ((uint32)Address > (EndAddress - (uint32)(Size - 1) ))))
    {
        Status = E_OS_VALUE;
    }
    else
    {
        /*Check whether permit the application access or not */
        if((AppMask & pPeripheralRight->ApplicationMask) == AppMask)
        {
            Status = E_OK;
        }
        else
        {
            Status = E_OS_STATUS_ACCESSRIGHTS;
        }
    }

    return Status ;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Read8
(
    AreaIdType Area,
    const uint8* Address,
    uint8* ReadValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_READPERIPHERAL8);
    OS_ARTI_SC_BEGIN(ReadPeripheral8, Address);

    Size = 1U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address || NULL_PTR == ReadValue))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_READPERIPHERAL8)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *ReadValue = *Address;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_READPERIPHERAL8,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)ReadValue);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ReadPeripheral8, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_READPERIPHERAL8);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Read16
(
    AreaIdType Area,
    const uint16* Address,
    uint16* ReadValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_READPERIPHERAL16);
    OS_ARTI_SC_BEGIN(ReadPeripheral16, Address);

    /*size of uint16 */
    Size = 2U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address || NULL_PTR == ReadValue))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(!(OsKernel_GetCurrentRunningContext() & OS_CALL_READPERIPHERAL16))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area, (const void *)Address, Size);
        if(E_OK == Status )
        {
            *ReadValue = *Address;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_READPERIPHERAL16,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)ReadValue);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ReadPeripheral16, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_READPERIPHERAL16);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Read32
(
    AreaIdType Area,
    const uint32* Address,
    uint32* ReadValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_READPERIPHERAL32);
    OS_ARTI_SC_BEGIN(ReadPeripheral32, Address);

    /*size of uint32 */
    Size = 4U;
    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address || NULL_PTR == ReadValue))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_READPERIPHERAL32)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *ReadValue = *Address;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_READPERIPHERAL32,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)ReadValue);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ReadPeripheral32, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_READPERIPHERAL32);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Write8
(
    AreaIdType Area,
    uint8* Address,
    uint8 WriteValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_WRITEPERIPHERAL8);
    OS_ARTI_SC_BEGIN(WritePeripheral8, Address);

    /*size of uint8*/
    Size = 1U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_WRITEPERIPHERAL8)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = WriteValue ;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_WRITEPERIPHERAL8,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)((uint32)WriteValue));
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(WritePeripheral8, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_WRITEPERIPHERAL8);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Write16
(
    AreaIdType Area,
    uint16* Address,
    uint16 WriteValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_WRITEPERIPHERAL16);
    OS_ARTI_SC_BEGIN(WritePeripheral16, Address);

    /*size of uint16*/
    Size = 2U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_WRITEPERIPHERAL16)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = WriteValue ;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_WRITEPERIPHERAL16,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)((uint32)WriteValue));
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(WritePeripheral16, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_WRITEPERIPHERAL16);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Write32
(
    AreaIdType Area,
    uint32* Address,
    uint32 WriteValue
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_WRITEPERIPHERAL32);
    OS_ARTI_SC_BEGIN(WritePeripheral32, Address);

    /*size of uint32*/
    Size = 4U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_WRITEPERIPHERAL32)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = WriteValue ;
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_WRITEPERIPHERAL32,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)WriteValue);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(WritePeripheral32, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_WRITEPERIPHERAL32);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Modify8
(
    AreaIdType Area,
    uint8* Address,
    uint8 Clearmask,
    uint8 Setmask
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_MODIFYPERIPHERAL8);
    OS_ARTI_SC_BEGIN(ModifyPeripheral8, Address);

    Status = E_NOT_OK;
    /*size of uint8*/
    Size = 1U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_MODIFYPERIPHERAL8)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = (*Address & Clearmask) | Setmask;   
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterFour(OS_SERVICEID_MODIFYPERIPHERAL8,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)((uint32)Clearmask),
                (InputParaType)((uint32)Setmask));
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ModifyPeripheral8, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_MODIFYPERIPHERAL8);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Modify16
(
    AreaIdType Area,
    uint16* Address,
    uint16 Clearmask,
    uint16 Setmask
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_MODIFYPERIPHERAL16);
    OS_ARTI_SC_BEGIN(ModifyPeripheral16, Address);

    /*size of uint16*/
    Size = 2U;

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_MODIFYPERIPHERAL16)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = (*Address & Clearmask) | Setmask;   
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterFour(OS_SERVICEID_MODIFYPERIPHERAL16,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)((uint32)Clearmask),
                (InputParaType)((uint32)Setmask));
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ModifyPeripheral16, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_MODIFYPERIPHERAL16);

    return Status;
}

FUNC(StatusType, OS_CODE) OsPeripheral_Internal_Modify32
(
    AreaIdType Area,
    uint32* Address,
    uint32 Clearmask,
    uint32 Setmask
)
{
    StatusType Status;
    uint8 Size;
    Os_IsrLevelType Level;

    /*size of uint32*/
    Size = 4U;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_MODIFYPERIPHERAL32);
    OS_ARTI_SC_BEGIN(ModifyPeripheral32, Address);

    if(OsService_ExtendedErrorCheck(Area >= OS_PERIPHERALID_COUNT))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == Address))
    {
         Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_MODIFYPERIPHERAL32)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        Status = OsPeripheral_Internal_CheckAccess(Area,(const void *)Address,Size);
        if(E_OK == Status )
        {
            *Address = (*Address & Clearmask) | Setmask;   
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterFour(OS_SERVICEID_MODIFYPERIPHERAL32,
                (InputParaType)((uint32)Area),
                (InputParaType)Address,
                (InputParaType)Clearmask,
                (InputParaType)Setmask);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ModifyPeripheral32, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_MODIFYPERIPHERAL32);

    return Status;
}

FUNC(uint32, OS_CODE) OsMpu_Internal_AlignStackStartAddress
(
    uint32 Address
)
{
    /*if the address , directly return the addess, otherwise , sub the alignment size and then align the address */
    return ((Address & MPU_REGION_ALIGNMENT_MASK) != 0U)?((Address + MPU_REGION_ALIGNMENT)&MPU_REGION_ALIGNMENT):Address;
}

FUNC(uint32, OS_CODE) OsMpu_Internal_AlignStackEndAddress
(
    uint32 Address
)
{
    /*if the address , directly return the addess, otherwise , align the address and then sub the alignment size.Any question ,please refer to R52 TRM */
    return ((Address & MPU_REGION_ALIGNMENT_MASK) != 0U)?((Address&MPU_REGION_ALIGNMENT_MASK)-MPU_REGION_ALIGNMENT):(Address);
}

FUNC(StatusType, OS_CODE) OsMpu_Internal_StackRegion
(
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)CoreStackCfg,
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)StackRegion
)
{
    StatusType Status;
    Os_MpuConfigType StackMpuCfg;
    Os_HalMpuRegionType MpuRegions[3U];
    uint32 RegionIndex ;

    for(RegionIndex = 0U; RegionIndex<STACK_REGION_COUNT;RegionIndex++)
    {
        MpuRegions[RegionIndex].AccessControl = 0U;
        MpuRegions[RegionIndex].EnableFlags = 0U;
    }

    RegionIndex = 0U;
    Status = E_OK;
    /*The object stack start addrss or end address is out of the whole stack */
    if((StackRegion->StartAddress < CoreStackCfg->StartAddress)||
    (StackRegion->EndAddress > CoreStackCfg->EndAddress))
    {
        Status = E_NOT_OK;
    }
    else
    {
        /*the object start addess not equal the whole stack start address, then seperate two segment */
        if(StackRegion->StartAddress > CoreStackCfg->StartAddress)
        {
            MpuRegions[RegionIndex].RegionBaseAddr = OsMpu_Internal_AlignStackStartAddress(CoreStackCfg->StartAddress)|MPU_NON_SHAREABLE|MPU_EL1_R_EL0_R|MPU_EXECUTE_NEVER;
            MpuRegions[RegionIndex].RegionEndAddr = OsMpu_Internal_AlignStackEndAddress(StackRegion->StartAddress - MPU_REGION_ALIGNMENT)|MPU_REGION_ENABLE;
            MpuRegions[RegionIndex].RegionNum = RegionIndex + OS_MPU_STACK_REGION_PROTECT_ONE;

            RegionIndex++;

            MpuRegions[RegionIndex].RegionBaseAddr = OsMpu_Internal_AlignStackStartAddress(StackRegion->StartAddress)|MPU_NON_SHAREABLE|MPU_EL1_RW_EL0_RW|MPU_EXECUTE_NEVER;
            MpuRegions[RegionIndex].RegionEndAddr = OsMpu_Internal_AlignStackEndAddress(StackRegion->EndAddress - MPU_REGION_ALIGNMENT )|MPU_REGION_ENABLE;
            MpuRegions[RegionIndex].RegionNum = RegionIndex + OS_MPU_STACK_REGION_PROTECT_ONE;
            RegionIndex++;
            StackMpuCfg.RegionCounts = RegionIndex;
        }
        else
        {
            /*the object start addess  equal the whole stack start address, then just set one segment  */
            MpuRegions[RegionIndex].RegionBaseAddr = OsMpu_Internal_AlignStackStartAddress(StackRegion->StartAddress)|MPU_NON_SHAREABLE|MPU_EL1_RW_EL0_RW|MPU_EXECUTE_NEVER;
            MpuRegions[RegionIndex].RegionEndAddr = OsMpu_Internal_AlignStackEndAddress(StackRegion->EndAddress - MPU_REGION_ALIGNMENT)|MPU_REGION_ENABLE;
            MpuRegions[RegionIndex].RegionNum = RegionIndex + OS_MPU_STACK_REGION_PROTECT_ONE;
            RegionIndex++;
            StackMpuCfg.RegionCounts = RegionIndex;
        }

        if(StackRegion->EndAddress < CoreStackCfg->EndAddress)
        {
            MpuRegions[RegionIndex].RegionBaseAddr = OsMpu_Internal_AlignStackStartAddress(StackRegion->EndAddress + MPU_REGION_ALIGNMENT )|MPU_NON_SHAREABLE|MPU_EL1_R_EL0_R|MPU_EXECUTE_NEVER;
            MpuRegions[RegionIndex].RegionEndAddr = OsMpu_Internal_AlignStackEndAddress(CoreStackCfg->EndAddress - MPU_REGION_ALIGNMENT)|MPU_REGION_ENABLE;
            MpuRegions[RegionIndex].RegionNum = RegionIndex + OS_MPU_STACK_REGION_PROTECT_ONE;
            RegionIndex++;
            StackMpuCfg.RegionCounts += 1U;
        }

        StackMpuCfg.MpuRegions = &MpuRegions[0];
        OsMpu_Hal_SetStack(&StackMpuCfg);
    }
    return Status;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(void, OS_CODE) OsMpu_InitCore
(
    P2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) CoreMpuCfg
)
{
#ifdef OS_KERNEL_SUPPORT_SC3
    {
        OsMpu_Hal_CoreInit(CoreMpuCfg);
    }
#endif

}

FUNC(void, OS_CODE) OsMpu_DisableObjectRegion(void)
{
#ifdef OS_KERNEL_SUPPORT_SC3
    {
        uint32 RegionIndex ;
        uint32 AppMaxRegCount;
        uint32 CoreMaxRegCount;
        uint32 ObjectMaxRegCount;
        CoreMaxRegCount = OsKernel_GetCurrentCoreMaxCoreMpRegionNum();
        AppMaxRegCount = OsKernel_GetCurrentCoreMaxAppMpRegionNum();
        ObjectMaxRegCount = OsKernel_GetCurrentCoreMaxObjectMpRegionNum();
        for(RegionIndex = CoreMaxRegCount; RegionIndex < (CoreMaxRegCount + AppMaxRegCount + ObjectMaxRegCount); RegionIndex++)
        {
            OsMpu_Hal_DisableRegions(RegionIndex);
        }                                               
    }
#endif
}

FUNC(void, OS_CODE) OsMpu_AppSwitchTo
(
    ApplicationType AppID
)
{
#ifdef OS_KERNEL_SUPPORT_SC3
    {
        P2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) NextAppMpuCfg  ;
        uint32 RegionIndex ;
        uint32 AppMaxRegCount;
        uint32 CoreMaxRegCount;
        CoreMaxRegCount = OsKernel_GetCurrentCoreMaxCoreMpRegionNum();
        AppMaxRegCount = OsKernel_GetCurrentCoreMaxAppMpRegionNum();
        for(RegionIndex = CoreMaxRegCount; RegionIndex < (CoreMaxRegCount + AppMaxRegCount); RegionIndex++)
        {
            OsMpu_Hal_DisableRegions(RegionIndex);
        }

        NextAppMpuCfg = OsMpu_ConfigSet_ApplicationsRefs[AppID] ;
        if(NULL_PTR != NextAppMpuCfg)
        {
            OsMpu_Hal_MpuSwitch(NextAppMpuCfg);
        }
    }
#endif
}

FUNC(void, OS_CODE) OsMpu_ObjectSwitchTo
(
    P2VAR(Os_MpuConfigContextRefType, TYPEDEF, OS_VAR) NextObjectMpuCfg
)
{
#ifdef OS_KERNEL_SUPPORT_SC3

    {
        uint32 RegionIndex ;
        uint32 AppMaxRegCount;
        uint32 CoreMaxRegCount;
        uint32 ObjectMaxRegCount;
        CoreMaxRegCount = OsKernel_GetCurrentCoreMaxCoreMpRegionNum();
        AppMaxRegCount = OsKernel_GetCurrentCoreMaxAppMpRegionNum();
        ObjectMaxRegCount = OsKernel_GetCurrentCoreMaxObjectMpRegionNum();
        for(RegionIndex = (CoreMaxRegCount + AppMaxRegCount); RegionIndex < (CoreMaxRegCount + AppMaxRegCount + ObjectMaxRegCount); RegionIndex++)
        {
            OsMpu_Hal_DisableRegions(RegionIndex);
        }

        if(NULL_PTR != NextObjectMpuCfg)
        {
            OsMpu_Hal_MpuSwitch(*NextObjectMpuCfg);
        }

    }

#endif
}

FUNC(boolean, OS_CODE) OsMpu_IsMpuStackEnable
(
    void
)
{
#ifdef OS_KERNEL_SUPPORT_SC3
    uint32 CoreID;
    boolean MPUEnable;
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)CoreStackCfg;

    MPUEnable = FALSE;
    CoreID = Os_Inf_GetCoreId();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];
    if(NULL_PTR != CoreCfgPtr && (NULL_PTR != CoreCfgPtr->MpuConfigSetRef))
    {
        CoreStackCfg = CoreCfgPtr->MpuConfigSetRef->CoreStackCfg;
        if(NULL_PTR != CoreStackCfg)
        {
            MPUEnable = TRUE;
        }
    }
    return MPUEnable;
#endif
    return FALSE;
}

FUNC(void, OS_CODE) OsMpu_SwitchStack
(
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST)Os_ContextInfo
)
{
#ifdef OS_KERNEL_SUPPORT_SC3
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)CoreStackCfg;
    Os_HalStackConfigAddressType SwitchStackRegion;
    uint32 CoreID; 
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;

    CoreID = Os_Inf_GetCoreId();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];

    if(NULL_PTR != CoreCfgPtr && (NULL_PTR != CoreCfgPtr->MpuConfigSetRef))
    {
        CoreStackCfg = CoreCfgPtr->MpuConfigSetRef->CoreStackCfg;
        if(NULL_PTR != CoreStackCfg)
        {
            SwitchStackRegion.StartAddress = Os_ContextInfo->StackTopAddr;
            SwitchStackRegion.EndAddress = Os_ContextInfo->StackBottomAddr;
            OsMpu_Internal_StackRegion(CoreStackCfg,&SwitchStackRegion);
        }
    }

#endif
}

FUNC(OsAccess_RightType, OS_CODE)CheckTaskMemoryAccess
(
    TaskType TaskID,
    MemoryStartAddressType Address,
    MemorySizeType Size
)
{
    OsAccess_RightType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsAccess_Internal_CheckObjectMemoryAccess(TaskID,Address,Size);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.
    } 
    else
    {
        Status = OsAccess_Internal_CheckObjectMemoryAccess(TaskID,Address,Size);
    }

    return Status;
}

FUNC(OsAccess_RightType, OS_CODE)CheckISRMemoryAccess
(
    ISRType ISRID,
    MemoryStartAddressType Address,
    MemorySizeType Size
)
{
    OsAccess_RightType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsAccess_Internal_CheckISRMemoryAccess(ISRID,Address,Size);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsAccess_Internal_CheckISRMemoryAccess(ISRID,Address,Size);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)  ReadPeripheral8
(
    AreaIdType Area,
    const uint8* Address,
    uint8* ReadValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Read8(Area,Address,ReadValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Read8(Area,Address,ReadValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)ReadPeripheral16
(
    AreaIdType Area,
    const uint16* Address,
    uint16* ReadValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Read16(Area,Address,ReadValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Read16(Area,Address,ReadValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)ReadPeripheral32
(
    AreaIdType Area,
    const uint32* Address,
    uint32* ReadValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Read32(Area,Address,ReadValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Read32(Area,Address,ReadValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)WritePeripheral8
(
    AreaIdType Area,
    uint8* Address,
    uint8 WriteValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Write8(Area,Address,WriteValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Write8(Area,Address,WriteValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)WritePeripheral16
(
    AreaIdType Area,
    uint16* Address,
    uint16 WriteValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Write16(Area,Address,WriteValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Write16(Area,Address,WriteValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)WritePeripheral32
(
    AreaIdType Area,
    uint32* Address,
    uint32 WriteValue
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Write32(Area,Address,WriteValue);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Write32(Area,Address,WriteValue);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)ModifyPeripheral8
(
    AreaIdType Area,
    uint8* Address,
    uint8 Clearmask,
    uint8 Setmask
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Modify8(Area,Address,Clearmask,Setmask);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Modify8(Area,Address,Clearmask,Setmask);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)ModifyPeripheral16
(
    AreaIdType Area,
    uint16* Address,
    uint16 Clearmask,
    uint16 Setmask
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Modify16(Area,Address,Clearmask,Setmask);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Modify16(Area,Address,Clearmask,Setmask);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)ModifyPeripheral32
(
    AreaIdType Area,
    uint32* Address,
    uint32 Clearmask,
    uint32 Setmask
)
{
    StatusType Status;

    if (IsNeedSysTrap()) 
    {
        Os_Inf_TrapToSystemMode();   //switch to system mode.
        Status = OsPeripheral_Internal_Modify32(Area,Address,Clearmask,Setmask);
        Os_Inf_TrapToUserMode() ;     //switch to user mode.  
    } 
    else
    {
        Status = OsPeripheral_Internal_Modify32(Area,Address,Clearmask,Setmask);
    }

    return Status;
}
