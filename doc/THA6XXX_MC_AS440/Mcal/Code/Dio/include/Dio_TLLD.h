/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_TLLD.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains internal function declarations of Dio Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c)
*   All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Dio_TLLD_h_REF_1:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Dio_TLLD_h_REF_2:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#Dio_TLLD_h_REF_5:CWE-704;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified memory 
* address.
*
*/

#ifndef DIO_TLLD_H_
#define DIO_TLLD_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "port_register.h"
#include "Dio_Cfg.h"
#include "Dio_GeneralTypes.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define DIO_PIN_STATE_TOGGLED           (0x10001UL)  /* Pin is toggled, set-bit and reset-bit write 1 */
#define LEVEL_MASK                      (0x01UL)
/* #Violation: Dio_TLLD_h_REF_2 */
/* #Violation: Dio_TLLD_h_REF_5 */
#define DIO_REG_WRITE32(reg, value)         ((reg) = (value))
/* Define the PORT base address */
#define DIO_BASE_ADDRESS                (PORT_P00_BASE_ADDRESS)
/* Calculate PORTx base address */
/* #Violation: Dio_TLLD_h_REF_2 */
/* #Violation: Dio_TLLD_h_REF_5 */
#define DIO(Group)                      ((PORT_MODULE*)(DIO_BASE_ADDRESS + ((Group) * 0x100UL)))
#define DIO_SETBIT                      (0x01U)

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Dio_TLLD_GetPinState
*
*   Service ID              : None.
*
*   Description             : This function shall return the level of the channel.
*                     
*   Parameters in           : PortNumber: Port number of DIO channel.
*                             PinNumber: Pin number of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
*                             STD_LOW: The physical level of the corresponding Pin is STD_LOW.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(Dio_LevelType, DIO_PRIVATE_CODE) Dio_TLLD_GetPinLevel
(
    Dio_PortType    PortNumber,
    uint8           PinNumber
)
{
    Dio_LevelType PinState;

    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    PinState = (Dio_LevelType)(DIO(PortNumber)->IDR.U >> PinNumber) & DIO_SETBIT;

    return PinState;
}

/****************************************************************************************************
*   Function Name           : Dio_TLLD_SetPinLevel
*
*   Service ID              : None.
*
*   Description             : This function shall set pin output voltage to low state.
*                     
*   Parameters in           : PortNumber: Port number of DIO channel.
*                             PinNumber: Pin number of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(void, DIO_PRIVATE_CODE) Dio_TLLD_SetPinLevel
(
    uint8           PortNumber,
    uint8           PinNum,
    Dio_LevelType   Level
)
{
    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    DIO_REG_WRITE32(DIO(PortNumber)->BSRR.U, (LEVEL_MASK << ((PinNum) + ((Level) * (DIO_PIN_MAX_NUMBER)))));
}

/****************************************************************************************************
*   Function Name           : Dio_TLLD_TogglePin
*
*   Service ID              : None.
*
*   Description             : This function shall set pin output voltage to reverse state.
*                     
*   Parameters in           : PortNumber: Port number of DIO channel.
*                             PinNumber: Pin number of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(Dio_LevelType, DIO_PRIVATE_CODE) Dio_TLLD_TogglePin
(
    Dio_PortType    PortNumber,
    uint8           PinNum
)
{
    Dio_LevelType PinState;

    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    DIO_REG_WRITE32(DIO(PortNumber)->BSRR.U, (DIO_PIN_STATE_TOGGLED << PinNum));

    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    if (0U == ((DIO(PortNumber)->IDR.U >> PinNum) & LEVEL_MASK))
    {
        PinState = STD_LOW;
    }
    else
    {
        PinState = STD_HIGH;
    }

    return PinState;
}

/****************************************************************************************************
*   Function Name           : Dio_TLLD_GetGroupLevel
*
*   Service ID              : None.
*
*   Description             : This function shall set pin output voltage to reverse state.
*                     
*   Parameters in           : PortNumber: Port number of DIO group.
*                             PortOffset: Offset of DIO group.
*                             mask: Mask of DIO group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : The physical level of the corresponding Pin.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(Dio_PortLevelType, DIO_PRIVATE_CODE) Dio_TLLD_GetGroupLevel
(
    uint8       PortNumber,
    uint8       Offset,
    uint16      Mask
)
{
    Dio_PortLevelType GroupState;
    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    GroupState = ((uint16)DIO(PortNumber)->IDR.U & Mask) >> Offset;

    return GroupState;
}

/****************************************************************************************************
*   Function Name           : Dio_TLLD_SetGroupLevel
*
*   Service ID              : None.
*
*   Description             : This function shall set group pins output voltage state.
*                     
*   Parameters in           : PortNumber: Port number of DIO group.
*                             PortOffset: Offset of DIO group.
*                             mask: Mask of DIO group.
*                             Data: Value to be set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Dio_PortLevelType: The physical level of the corresponding Pin.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(void, DIO_PRIVATE_CODE) Dio_TLLD_SetGroupLevel
(
    Dio_PortType        PortNumber,
    uint8               Offset,
    uint16              Mask,
    Dio_PortLevelType   Level
)
{
    /* 
     * ((Level << Offset) & Mask) << 16: Set the high level bit according to Mask
     * ((~Level) << Offset) & Mask:      Set high and low levels according to Mask
    */
    /* #Violation: Dio_TLLD_h_REF_1 */
    /* #Violation: Dio_TLLD_h_REF_2 */
    DIO(PortNumber)->BSRR.U = ((((uint32)Level << Offset) & Mask) << 16U) | 
                              ((((~(uint32)Level) << Offset) & Mask));

}  
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* DIO_TLLD_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

