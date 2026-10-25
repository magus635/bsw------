/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port_TLLD.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains internal functions of Port Driver
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
*
*#Port_TLLD_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Port_TLLD_c_REF_2:MISRAC2012-Rule-2.2;
* Justification: Platform-based design with configurable macros.
*
*#Port_TLLD_c_REF_3:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Port_TLLD_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Port_TLLD_c_REF_5:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Port_TLLD_c_REF_6:CertC-DCL00-C; 
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "SchM_Port.h"
#include "Port_TLLD.h"
#include "Port_GeneralTypes.h"
#include "Port_Cfg.h"
#include "Mcall.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Mask: Mask value range 0~3 */
#define PORT_RANGE_0TO3_MASK                            (0x03U)

/* Macro definition of Port-Pin controler function register bit field mask */
#define PORT_REG_CTR_MASK                               (0xFFUL)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Port_TLLD_c_REF_3 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

#ifdef PORT_SAFETY_ENABLE
static FUNC(boolean, PORT_PRIVATE_CODE) Port_RegReadBackCheck
(
    uint32  RegValue,
    uint32  ExpectValue
);
#endif /* PORT_SAFETY_ENABLE */

static FUNC(boolean, PORT_PRIVATE_CODE) Port_SetRegisterValue
(
    volatile uint32     *RegAddressPtr,
    uint32              ExpectValue,
    uint32              Mask,
    uint32              Pin
);
/****************************************************************************************************
**                          Private Function Definitions                                            **
****************************************************************************************************/
#ifdef PORT_SAFETY_ENABLE
/****************************************************************************************************
*   Function Name           : Port_RegReadBackCheck
*
*   Service ID              : None.
*
*   Description             : This function is used to read back the register.
*
*   Parameters in           : RegValue   : Register actual value.
*                             ExpectValue: Expected setting value.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Register readback check results.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, PORT_PRIVATE_CODE) Port_RegReadBackCheck
(
    uint32  RegValue,
    uint32  ExpectValue
)
{
    boolean         RetStatus;

    /* Initialization function return value */
    RetStatus = TRUE;

    if (RegValue != ExpectValue)
    {
        RetStatus = FALSE;
    }

    return RetStatus;
}
#endif /* PORT_SAFETY_ENABLE */
/****************************************************************************************************
*   Function Name           : Port_SetRegisterValue
*
*   Service ID              : None.
*
*   Description             : This function is used to set register values.
*
*   Parameters in           : RegAddressPtr : Point to the register address to be processed.
*                             ExpectValue   : Expected setting value.
*                             Mask          : Mask of the bit fields to be set.
*                             Pin           : The Pin ID to be set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Whether the register is written successfully.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, PORT_PRIVATE_CODE) Port_SetRegisterValue
(
    /* #Violation: Port_TLLD_c_REF_6 */
    volatile uint32     *RegAddressPtr,
    uint32              ExpectValue,
    uint32              Mask,
    uint32              Pin
)
{
    boolean        RetStatus;
    uint8          Offset;
    uint32         RegValue;

    /* Initialization function return value */
    RetStatus = TRUE;
    /* Check the scope of the operation */
    if(PORT_NULL_MASK == Pin)
    {
        /* Calculate the expected value of the full bit field operation */
        RegValue = ExpectValue;
    }
    else
    {
        /* Get the current configuration value of the register */
        RegValue = *RegAddressPtr;
        /* Calculate the offset of the Pin to be operated */
        Offset = (uint8)((Pin & 0x03UL) << 0x03UL);
        /* Clear the register bit field to be operated */
        RegValue &= ~(Mask << Offset);
        /* Calculate the register bit field to be operated */
        RegValue |= ExpectValue << Offset;
    }
    
    /* Set the register bit field to be operated */
    *RegAddressPtr = RegValue;

#ifdef PORT_SAFETY_ENABLE
    /* Register readback to check write results */
    /* #Violation: Port_TLLD_c_REF_2 */
    RetStatus &= Port_RegReadBackCheck(*RegAddressPtr, RegValue);
#endif /* PORT_SAFETY_ENABLE */

    return RetStatus;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Port_TLLD_Init
*
*   Service ID              : None.
*
*   Description             : This function shall initialize Port registers.
*
*   Parameters in           : ConfigPtr: Pointer to PORT driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Hardware initialization results.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Port_00005
****************************************************************************************************/
FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_Init
(
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
    uint8       PortNumber;
    uint8       PortIndex;
    uint8       LoopCnt;
    boolean     RetStatus;

#if (PORT_LVDS_FUNCTION_ENABLE == STD_ON)
    const Port_LVDSPairType *LVDSPairCfgPtr;
#endif

    /* Initialization function return value */
    RetStatus = TRUE;
    /* Writing ODR, CTRx, DSRx, ESR, DFR HWCR, PSR registers 
       Loop Port to Maximum Port ID */
    for (PortNumber = 0U; ((TRUE == RetStatus) && (PortNumber < PORT_MAX_NUMBER)); PortNumber++)
    {
        /* Get the Port index of the real Port Number */
        PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];
        if ((uint8)PORT_NULL_MASK != PortIndex)
        {
            /*  SWS_Port_00055:
                The function Port_Init shall set the port pin output latch to a default level
                (defined during configuration) before setting the port pin direction to output.
                Ensures that the default level is immediately output on the port pin when it is set
                to an output port pin.
            */
            /* #Violation: Port_TLLD_c_REF_2 */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->ODR.U),
                            ConfigPtr->ODRCfgPtr[PortIndex].U, PORT_NULL_MASK, PORT_NULL_MASK);

            /* Configure Port-Pin Output Function Select */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U),
                           (ConfigPtr->CTRxCfgPtr[PortIndex].U[0] & PORT_SEL_MASK),
                           PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U),
                           (ConfigPtr->CTRxCfgPtr[PortIndex].U[1] & PORT_SEL_MASK),
                           PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U),
                           (ConfigPtr->CTRxCfgPtr[PortIndex].U[2] & PORT_SEL_MASK),
                           PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U),
                           (ConfigPtr->CTRxCfgPtr[PortIndex].U[3] & PORT_SEL_MASK),
                           PORT_NULL_MASK, PORT_NULL_MASK);

            /* Configure Port-Pin Direction, Push-pull&Open-drain */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U),
                           ConfigPtr->CTRxCfgPtr[PortIndex].U[0], PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U),
                           ConfigPtr->CTRxCfgPtr[PortIndex].U[1], PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U),
                           ConfigPtr->CTRxCfgPtr[PortIndex].U[2], PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U),
                           ConfigPtr->CTRxCfgPtr[PortIndex].U[3], PORT_NULL_MASK, PORT_NULL_MASK);
            
            if(NULL_PTR != ConfigPtr->STTLCfgPtr)
            {
                RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->STTL.U),
                           ConfigPtr->STTLCfgPtr[PortIndex].U, PORT_NULL_MASK, PORT_NULL_MASK);
            }

            /* Enter the critical section to avoid timeout caused during WDT Endinit. */
            PORT_ENTER_CRITICAL_SECTION(Init);
            /* Release the register write protection controlled by the CPU watchdog */
            /* #Violation: Port_TLLD_c_REF_1 */
            RetStatus &= Mcal_EndinitClr();

            /* Configure Port-Pin Pad level, slew-rate, Pad input mode, Pad driver Select */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->DSR0.U),
                           ConfigPtr->DSRxCfgPtr[PortIndex].DSR[0], PORT_NULL_MASK, PORT_NULL_MASK);

            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->DSR8.U),
                           ConfigPtr->DSRxCfgPtr[PortIndex].DSR[1], PORT_NULL_MASK, PORT_NULL_MASK);

            /* Configure Port emergency stop enable */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->ESR.U),
                           0x00UL, PORT_NULL_MASK, PORT_NULL_MASK);

            /* Configure Port-Pin digital function enable */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->DFR.U),
                           ConfigPtr->DFRCfgPtr[PortIndex].U, PORT_NULL_MASK, PORT_NULL_MASK);

            /* Set the register write protection controlled by the CPU watchdog */
            /* #Violation: Port_TLLD_c_REF_1 */
            RetStatus &= Mcal_EndinitSet();

            /* Exit the critical section to avoid timeout caused during WDT Endinit. */
            PORT_EXIT_CRITICAL_SECTION(Init);

            /* Configure Port-Pin hardware control select */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->HWCR.U),
                          ConfigPtr->HWCRCfgPtr[PortIndex].U, PORT_NULL_MASK, PORT_NULL_MASK);

            /* Configure Port-Pin Pull_Up/Pull_Down */
            RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->PSR.U),
                           ConfigPtr->PSRCfgPtr[PortIndex].U, PORT_NULL_MASK, PORT_NULL_MASK);
        }
    }

    /* Configure Port-Pin input multiplexing function selection */
    for (LoopCnt = 0U; ((TRUE == RetStatus) && (LoopCnt < PORT_RXMUX_MODU_CNT)); LoopCnt++)
    {
        /* #Violation: Port_TLLD_c_REF_2 */
        /* #Violation: Port_TLLD_c_REF_4 */
        RetStatus &= Port_SetRegisterValue(&(PORT_PRXMUX->INSEL[LoopCnt].U),
                                ConfigPtr->RXMUXSelPtr[LoopCnt].U, PORT_NULL_MASK, PORT_NULL_MASK);
    }

#ifdef THA6_THA6104
    /* #Violation: Port_TLLD_c_REF_3 */
    RetStatus &= Port_SetRegisterValue(&(PORT_PRXMUX_EXTI->U),
                            ConfigPtr->RXMUXSelPtr[LoopCnt].U, PORT_NULL_MASK, PORT_NULL_MASK);
#endif /* THA6_THA6104 */

/* Configure Port-Pin LVDS register */
#if (PORT_LVDS_FUNCTION_ENABLE == STD_ON)
    if(NULL_PTR != ConfigPtr->LVDSConfigPtr)
    {
        for(LoopCnt = 0U;
            ((TRUE == RetStatus) && (LoopCnt < (ConfigPtr->LVDSConfigPtr->LVDSPairNumber)));
            LoopCnt++)
        {
            /* Get the LVDS Pair configuration structure pointer */
            LVDSPairCfgPtr = &ConfigPtr->LVDSConfigPtr->LVDSPairConfigPtr[LoopCnt];
            /* Get the port group ID */
            PortNumber = LVDSPairCfgPtr->PortId;
            if(PORT_MAX_NUMBER > PortNumber)
            {
                /* Get the Port index of the real Port Number */
                PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];
                if((uint8)PORT_NULL_MASK != PortIndex)
                {
                    /* Enter the critical section to avoid timeout caused during WDT Endinit. */
                    PORT_ENTER_CRITICAL_SECTION(Init);
                    /* Release the register write protection controlled by the CPU watchdog */
                    /* #Violation: Port_TLLD_c_REF_1 */
                    RetStatus &= Mcal_EndinitClr();

                    /* Enable the LVDSR function and set the configuration information */
                    RetStatus &= Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->
                                    LVDS[LVDSPairCfgPtr->LVDSRNumber & PORT_RANGE_0TO3_MASK].U),
                                    LVDSPairCfgPtr->LVDSConfig, PORT_NULL_MASK, PORT_NULL_MASK);
                    
                    /* Turn on LVDS BIASEN */
                    ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->
                            LVDS[LVDSPairCfgPtr->LVDSRNumber & PORT_RANGE_0TO3_MASK].B.BIASEN = TRUE;
#ifdef PORT_SAFETY_ENABLE
                    RetStatus &= Port_RegReadBackCheck(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->
                            LVDS[LVDSPairCfgPtr->LVDSRNumber & PORT_RANGE_0TO3_MASK].B.BIASEN, TRUE);
#endif /* PORT_SAFETY_ENABLE */

                    /* Turn on LVDS TXEN */
                    ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->
                            LVDS[LVDSPairCfgPtr->LVDSRNumber & PORT_RANGE_0TO3_MASK].B.TXEN = TRUE;
#ifdef PORT_SAFETY_ENABLE
                    RetStatus &= Port_RegReadBackCheck(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->
                            LVDS[LVDSPairCfgPtr->LVDSRNumber & PORT_RANGE_0TO3_MASK].B.TXEN, TRUE);
#endif /* PORT_SAFETY_ENABLE */
                    /* Set the register write protection controlled by the CPU watchdog */
                    /* #Violation: Port_TLLD_c_REF_1 */
                    RetStatus &= Mcal_EndinitSet();

                    /* Exit the critical section to avoid timeout caused during WDT Endinit. */
                    PORT_EXIT_CRITICAL_SECTION(Init);
                }
            }
        }
    }
#endif

    return RetStatus;
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_TLLD_SetPinDirection
*
*   Service ID              : None.
*
*   Description             : This function is used to set the Port-Pin pin direction.
*
*   Parameters in           : PortNumber: ID of Port.
*                             PinNumber:  ID of Pin.
*                             Direction:  Input direction to be set.
*                             ConfigPtr:  Pointer to PORT driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Port-Pin Direction Setting Result.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_SetPinDirection
(
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinDirectionType Direction,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
    uint8           PortIndex;
    boolean         RetStatus;

    /* Get the index of Port ID */
    PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];

    /* Clear the output direction enable control register bit field in CTRx */
    switch(PinNumber >> 2U)
    {
        case 0x00U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U),
                                                    (uint32)Direction, PORT_REG_DIR_MASK, PinNumber);
            break;
        }
        case 0x01U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U),
                                                    (uint32)Direction, PORT_REG_DIR_MASK, PinNumber);
            break;
        }
        case 0x02U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U),
                                                    (uint32)Direction, PORT_REG_DIR_MASK, PinNumber);
            break;
        }
        case 0x03U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U),
                                                    (uint32)Direction, PORT_REG_DIR_MASK, PinNumber);
            break;
        }
        default:
        {
            /* All branches do not match and return an error */
            RetStatus = FALSE;
            break;
        }
    }
    
    return RetStatus;
}
#endif /* (PORT_SET_PIN_DIRECTION_API  \== STD_ON) */

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_TLLD_RefreshPortDirection
*
*   Service ID              : None.
*
*   Description             : Refresh Port-Pin properties to the initialization state.
*
*   Parameters in           : PortNumber: ID of Port.
*                             PinNumber:  ID of Pin.
*                             PinCfgData: Input Port-Pin configuration value.
*                             ConfigPtr:  Pointer to PORT driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Port-Pin pin attribute refresh result.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_RefreshPortDirection
(
    uint8 PortNumber,
    uint8 PinNumber,
    uint8 PinCfgData,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
    uint8           PortIndex;
    boolean         RetStatus;

    /* Get the index of Port ID */
    PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];
    /* Write CTRx to configure mode and Index*/
    switch(PinNumber >> 2U)
    {
        case 0x00U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U),
                                                           PinCfgData, PORT_REG_CTR_MASK, PinNumber);
            break;
        }
        case 0x01U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U),
                                                           PinCfgData, PORT_REG_CTR_MASK, PinNumber);
            break;
        }
        case 0x02U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U),
                                                           PinCfgData, PORT_REG_CTR_MASK, PinNumber);
            break;
        }
        case 0x03U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U),
                                                           PinCfgData, PORT_REG_CTR_MASK, PinNumber);
            break;
        }
        default:
        {
            /* All branches do not match and return an error */
            RetStatus = FALSE;
            break;
        }
    }
    
    return RetStatus;
}
#endif /* (PORT_SET_PIN_DIRECTION_API  \== STD_ON) */

#if (PORT_SET_PIN_MODE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_TLLD_SetPinMode
*
*   Service ID              : None.
*
*   Description             : This function shall set pin output alt mode.
*
*   Parameters in           : PortNumber: ID of Port.
*                             PinNumber:  ID of Pin.
*                             Mode:       Input Port-Pin multiplexing mode.
*                             ConfigPtr:  Pointer to PORT driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Port-Pin pin output multiplexing mode setting result.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_SetPinMode
(
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinModeType Mode,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
    uint8           PortIndex;
    boolean         RetStatus;

    /* Get the index of Port ID */
    PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];
    /* Write CTRx to configure mode and Index*/
    switch(PinNumber >> 2U)
    {
        case 0x00U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U),
                                                                Mode, PORT_REG_MODE_MASK, PinNumber);
            break;
        }
        case 0x01U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U),
                                                                Mode, PORT_REG_MODE_MASK, PinNumber);
            break;
        }
        case 0x02U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U),
                                                                Mode, PORT_REG_MODE_MASK, PinNumber);
            break;
        }
        case 0x03U:
        {
            RetStatus = Port_SetRegisterValue(&(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U),
                                                                Mode, PORT_REG_MODE_MASK, PinNumber);
            break;
        }
        default:
        {
            /* All branches do not match and return an error */
            RetStatus = FALSE;
            break;
        }
    }

    return RetStatus;
}
#endif /* (PORT_SET_PIN_MODE_API  \== STD_ON) */

#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Port_TLLD_GetPinCTRCfg
*
*   Service ID              : None.
*
*   Description             : This function shall get CTR register value from specified port.
*
*   Parameters in           : PortNumber: ID of Port.
*                             PinNumber:  ID of Pin.
*                             ConfigPtr:  Pointer to PORT driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Value of CTR register.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(uint8, PORT_PRIVATE_CODE) Port_TLLD_GetPinCTRCfg
(
    uint8 PortNumber,
    uint8 PinNumber,
    /* #Violation: Port_TLLD_c_REF_6 */
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
    uint8           PortIndex;
    uint8           PinCTRCfg;
    uint32          CTRxValue;
    
    /* Initialization function return value */
    CTRxValue = 0UL;
    /* Get the index of Port ID */
    PortIndex = ConfigPtr->AvailablePortIndexPtr[PortNumber];
    /* Write CTRx to configure mode and Index*/
    switch(PinNumber >> 2U)
    {
        case 0x00U:
        {
            CTRxValue = (uint32)(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR0.U);
            break;
        }
        case 0x01U:
        {
            CTRxValue = (uint32)(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR4.U);
            break;
        }
        case 0x02U:
        {
            CTRxValue = (uint32)(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR8.U);
            break;
        }
        case 0x03U:
        {
            CTRxValue = (uint32)(ConfigPtr->HwUnitBaseAddressPtr[PortIndex]->CTR12.U);
            break;
        }
        default:
        {
            /* All branches do not match and return */
            break;
        }
    }
    /* Get the register configuration value of the corresponding Pin */
    PinCTRCfg = (uint8)(CTRxValue >> ((PinNumber & PORT_RANGE_0TO3_MASK) <<PORT_RANGE_0TO3_MASK));

    return PinCTRCfg;
}
#endif /* ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API \== STD_ON)) */

/* #Violation: Port_TLLD_c_REF_3 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_TLLD_c_REF_5 */
#include "Port_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

