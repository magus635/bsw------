/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_hal.c
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer implementations of requirements of PORT module.
 **********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_hal_c_REF_1:MISRAC2012-Rule-2.1; 
* Justification:Hal layer API needs to be provided to the upper layer.
*
*#port_hal_c_REF_2:MISRAC2012-Rule-2.2;
* Justification:Platform-based design with configurable macros.
*
*#port_hal_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*#port_hal_c_REF_4:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*#port_hal_c_REF_5:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#port_hal_c_REF_6:MISRAC2012-Rule-19.2; 
* Justification:Using unions for bit-field access to registers
*
*#port_hal_c_REF_7:MISRAC2012-Rule-10.5; 
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8;
*
*#port_hal_c_REF_8:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#port_hal_c_REF_9:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#port_hal_c_REF_10:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#port_hal_c_REF_11:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 **********************************************************************************************************************/
#include "common_hal.h"
#include "port_hal.h"
#include "port_std.h"
#include "port_register.h"
#include "cpuwdt_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "tha6_cfg.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 **********************************************************************************************************************/
/* ^PORT_DIRECTION^ The PORT CTR and DSR register Control */
#define PORT_CTR_NUMBER 4U /* PORT CTR register number */
#define PORT_DSR_NUMBER 2U /* PORT DSR register number */

/* The PORT LVDS register Control */
/* #Violation: port_hal_c_REF_3 */
#define PORT_LVDS_DISABLE 0U         /* PORT LVDS function disable */
/* #Violation: port_hal_c_REF_3 */
#define PORT_LVDS_ENABLE  1U         /* PORT LVDS function enable */

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* RXMUX */
#define RXMUX_REG_OFFSET_RIGHT_SHIFT 8U /* RXMUX register offset right shift */
#define RXMUX_BIT_OFFSET_MASK 0xFFU     /* RXMUX bit fileld offset mask */
#endif

/* The PORT RXMUX module index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_CAN0ISEL_INDEX 0U        /* RXMUX CAN0ISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_CAN1ISEL_INDEX 1U        /* RXMUX CAN1ISEL index */
#define RXMUX_ETHISEL0_INDEX 3U        /* RXMUX ETHISEL0 index */
#define RXMUX_ETHISEL1_INDEX 4U        /* RXMUX ETHISEL1 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_I2C0ISEL_INDEX 5U        /* RXMUX I2C0ISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ASIISEL0_INDEX 6U        /* RXMUX ASIISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_SENTISEL0_INDEX 16U      /* RXMUX SENTISEL0 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_SENTISEL8_INDEX 17U      /* RXMUX SENTISEL8 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON0SEL0_INDEX 18U    /* RXMUX IOMMON0SEL0 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON0SEL8_INDEX 19U    /* RXMUX IOMMON0SEL8 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON2SEL0_INDEX 20U    /* RXMUX IOMMON2SEL0 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON2SEL8_INDEX 21U    /* RXMUX IOMMON2SEL8 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_DBGTRIGSEL_INDEX 22U     /* RXMUX DBGTRACE index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_CAN2ISEL_INDEX 23U       /* RXMUX CAN2ISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_CAN3ISEL_INDEX 24U       /* RXMUX CAN3ISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_I2C1ISEL_INDEX 26U       /* RXMUX I2C1ISEL index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ASIISEL1_INDEX 27U       /* RXMUX ASIISEL1 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ASIISEL2_INDEX 28U       /* RXMUX ASIISEL2 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_SENTISEL16_INDEX 29U     /* RXMUX SENTISEL16 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_SENTISEL24_INDEX 30U     /* RXMUX SENTISEL24 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON1SEL0_INDEX 31U    /* RXMUX IOMMON1SEL0 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMMON1SEL8_INDEX 32U    /* RXMUX IOMMON1SEL8 index */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_IOMPINSEL_INDEX 33U      /* RXMUX IOMPINSEL index */

/* #Violation: port_hal_c_REF_3 */
#define RXMUX_PSI5RXSEL_INDEX 33U      /* RXMUX PSI5RXSEL index */

/* The PORT RXMUX ETH1 offset */
#define RXMUX_ETHISEL1_RXD1_OFFSET 4U   /* RXMUX ETHISEL1 RXD1 offset */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ETHISEL1_RXD2_OFFSET 8U   /* RXMUX ETHISEL1 RXD2 offset */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ETHISEL1_RXD3_OFFSET 12U  /* RXMUX ETHISEL1 RXD3 offset */
#define RXMUX_ETHISEL1_TXCLK_OFFSET 16U /* RXMUX ETHISEL1 TXCLK offset */

/* The PORT RXMUX ETH0 offset */
#define RXMUX_ETHISEL0_RXCLK_OFFSET 4U /* RXMUX ETHISEL0 RXCK offset */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ETHISEL0_CRS_OFFSET 8U   /* RXMUX ETHISEL0 CRS offset */
/* #Violation: port_hal_c_REF_3 */
#define RXMUX_ETHISEL0_COL_OFFSET 12U  /* RXMUX ETHISEL0 COL offset */
#define RXMUX_ETHISEL0_DV_OFFSET 16U   /* RXMUX ETHISEL0 DV offset */
#define RXMUX_ETHISEL0_RXER_OFFSET 20U /* RXMUX ETHISEL0 RXER offset */

/* The PORT RXMUX I2C offset */
#define RXMUX_I2CISEL_SDA_OFFSET 4U /* RXMUX I2C0ISEL SDA offset */

/* The PORT RXMUX ESPI offset */
#define RXMUX_ESPIxISEL_MTSR_OFFSET 4U  /* RXMUX ESPIxISEL MTSR offset */
#define RXMUX_ESPIxISEL_SCLK_OFFSET 8U  /* RXMUX ESPIxISEL SCLK offset */
#define RXMUX_ESPIxISEL_SLSI_OFFSET 12U /* RXMUX ESPIxISEL SLSI offset */
#define RXMUX_ESPIxISEL_MRSTSEL_AH  0x00000U /* RXMUX ESPIxISEL MRSTH offset */
#define RXMUX_ESPIxISEL_MRSTSEL_IP  0x10000U /* RXMUX ESPIxISEL MRSTH offset */
#define RXMUX_ESPIxISEL_MRSTSEL_QV  0x20000U /* RXMUX ESPIxISEL MRSTH offset */

/**********************************************************************************************************************
 *                                             Global Function Definitions
 **********************************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: port_hal_c_REF_11 */
#include "Port_MemMap.h"

/* #Violation: port_hal_c_REF_4 */
boolean Port_Hal_SetPinInput(const Port_InputConfig *const pConfig)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif
    
    ret = TRUE;
    /* Set port pin input mode */
    ret &= Port_Std_SetPinInput(pConfig->modulePin.port, pConfig->modulePin.pin);

    /* Set pull mode */
    ret &= Port_Std_SetPinPullMode(pConfig->modulePin.port, pConfig->modulePin.pin, pConfig->pull);

    /* Set AL/TTL mode */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    ret &= Port_Std_SetPinLevel(pConfig->modulePin.port, pConfig->modulePin.pin, pConfig->level);
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPinGroupInput(const Port_InputConfig *const pConfig, uint16 pinMask)
{
    uint8 pinCounter;
    uint8 pinIndex;

    /* Value for configure CTRx */
    uint8 ctrIndex;
    uint8 ctrShift;
    uint32 ctr[PORT_CTR_NUMBER];

    /* Value for configure PSRx */
    uint32 psrValue;

    /* Value for configure DSRx */
    uint8 dsrIndex;
    uint8 dsrShift;
    uint32 dsr[PORT_DSR_NUMBER];
    
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    /* Get pin index */
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Initializing array ctr */
    ctr[0U] = pConfig->modulePin.port->CTR0.U;
    ctr[1U] = pConfig->modulePin.port->CTR4.U;
    ctr[2U] = pConfig->modulePin.port->CTR8.U;
    ctr[3U] = pConfig->modulePin.port->CTR12.U;

    /* Read PSR register */
    psrValue = pConfig->modulePin.port->PSR.U;

    /* Initializing array dsr */
    dsr[0U] = pConfig->modulePin.port->DSR0.U;
    dsr[1U] = pConfig->modulePin.port->DSR8.U;

    /* Write configure to buffer or value */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            /* Write configure to array ctr */
            ctrIndex = (pinCounter >> PORT_SHIFT_2);
            ctrShift = ((pinCounter & PORT_MASK_BIT_LOW_2) << PORT_SHIFT_3);
            ctr[ctrIndex] &= (~((uint32)PORT_MASK_BIT_LOW_8 << ctrShift));

            /* Write configure to value psrValue */
            psrValue &= (~((uint32)PORT_MASK_BIT_LOW_2 << (pinCounter << PORT_SHIFT_1))); /* Clear pull bit field */
            psrValue |= ((uint32)pConfig->pull << (pinCounter << PORT_SHIFT_1));          /* Set pull mode */

            /* Write configure to DSRx */
            dsrIndex = (pinCounter >> PORT_SHIFT_3); /* Calculate DSR register offset */
            /* Calculate level bit field offset */
            dsrShift = (((pinCounter & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_LEVEL_OFFSET);

            if(PORT_LEVEL_TTL == pConfig->level)
            {
                dsr[dsrIndex] |= ((uint32)1U << dsrShift); /* Set TTL level */
            }
            else
            {
                dsr[dsrIndex] &= (~((uint32)1U << dsrShift)); /* Set AL level */
            }
        }
    }

    /* Write to register */
    pConfig->modulePin.port->CTR0.U  = ctr[0U];
    ret = Port_Register_ReadBack_Check(ret, ctr[0U], pConfig->modulePin.port->CTR0.U);
    pConfig->modulePin.port->CTR4.U  = ctr[1U];
    ret = Port_Register_ReadBack_Check(ret, ctr[1U], pConfig->modulePin.port->CTR4.U);
    pConfig->modulePin.port->CTR8.U  = ctr[2U];
    ret = Port_Register_ReadBack_Check(ret, ctr[2U], pConfig->modulePin.port->CTR8.U);
    pConfig->modulePin.port->CTR12.U = ctr[3U];
    ret = Port_Register_ReadBack_Check(ret, ctr[3U], pConfig->modulePin.port->CTR12.U);

    pConfig->modulePin.port->PSR.U = psrValue; /* Write PSR register */
    ret = Port_Register_ReadBack_Check(ret, psrValue, pConfig->modulePin.port->PSR.U);

    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->modulePin.port->DSR0.U = dsr[0U];
    pConfig->modulePin.port->DSR8.U = dsr[1U];
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr[0U], pConfig->modulePin.port->DSR0.U);
    ret = Port_Register_ReadBack_Check(ret, dsr[1U], pConfig->modulePin.port->DSR8.U);

    return ret;
}

/* #Violation: port_hal_c_REF_4 */
boolean Port_Hal_SetPinGroupPull(const Port_PullConfig *const pConfig, uint16 pinMask)
{
    uint32 psrValue;
    uint8 pinCounter;
    uint8 pinIndex;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    psrValue = pConfig->modulePin.port->PSR.U; /* Read PSR register */
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Write to register */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            psrValue &= (~((uint32)PORT_MASK_BIT_LOW_2 << (pinCounter << PORT_SHIFT_1))); /* Clear pull bit field */
            psrValue |= ((uint32)pConfig->pull << (pinCounter << PORT_SHIFT_1));          /* Set pull mode */
        }
    }

    pConfig->modulePin.port->PSR.U = psrValue; /* Write PSR register */
    ret = Port_Register_ReadBack_Check(ret, psrValue, pConfig->modulePin.port->PSR.U);

    return ret;
}

/* #Violation: port_hal_c_REF_4 */
boolean Port_Hal_SetPinOutput(const Port_OutputConfig *const pConfig)
{
    Port_ControllerConfig controllerConfig;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    /* Set port pin no-pull mode */
    ret &= Port_Std_SetPinPullMode(pConfig->modulePin.port, pConfig->modulePin.pin, PORT_PULL_NONE);

    /* Set pin controller configuration module and pin */
    controllerConfig.modulePin.port = pConfig->modulePin.port;
    controllerConfig.modulePin.pin = pConfig->modulePin.pin;

    /* Set port pin multiplexer and push-pull/open-drain mode */
    ret &= Port_Std_SetPinOutput(pConfig->modulePin.port, pConfig->modulePin.pin, pConfig->outputSel, pConfig->outputMode);

    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    /* Set drive strength */
    ret &= Port_Std_SetPinDriveStrength(pConfig->modulePin.port, pConfig->modulePin.pin, pConfig->driveStrength);
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    if(PORT_CONTROLLER_PERIPHERAL == pConfig->controller)
    {
        /* Set pin controller peripheral */
        controllerConfig.controller = PORT_CONTROLLER_PERIPHERAL;
    }
    else
    {
        /* Set pin controller port */
        controllerConfig.controller = PORT_CONTROLLER_PORT;
    }

    ret &= Port_Hal_SetPinController(&controllerConfig);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPinGroupOutput(const Port_OutputConfig *const pConfig, uint16 pinMask)
{
    uint8 pinCounter;
    uint8 pinIndex;
    Port_PullConfig pullConfig;

    /* Value for configure CTRx */
    uint32 ctr[PORT_CTR_NUMBER];
    uint8 ctrIndex;
    uint8 ctrShift;

    /* Value for configure DSRx */
    uint32 dsr[PORT_DSR_NUMBER];
    uint8 dsrIndex;
    uint8 dsrShift;

    /* Value for configure HWCR */
    uint32 hwcr;
    uint8 hwcrShift;
    Port_Controller controller;

    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Set pin group no-pull mode */
    pullConfig.modulePin.pin = pConfig->modulePin.pin;
    pullConfig.modulePin.port = pConfig->modulePin.port;
    pullConfig.pull = PORT_PULL_NONE;
    ret &= Port_Hal_SetPinGroupPull(&pullConfig, pinMask);

    /* Initializing array ctr */
    ctr[0U] = pConfig->modulePin.port->CTR0.U;
    ctr[1U] = pConfig->modulePin.port->CTR4.U;
    ctr[2U] = pConfig->modulePin.port->CTR8.U;
    ctr[3U] = pConfig->modulePin.port->CTR12.U;

    /* Initializing array dsr */
    dsr[0U] = pConfig->modulePin.port->DSR0.U;
    dsr[1U] = pConfig->modulePin.port->DSR8.U;

    /* get initial value of HWCR */
    hwcr = pConfig->modulePin.port->HWCR.U;
    controller = pConfig->controller;
    
    /* Write to buffer */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            /* Calculate CTR register offset */
            ctrIndex = (pinCounter >> PORT_SHIFT_2);
            ctrShift = ((pinCounter & PORT_MASK_BIT_LOW_2) << PORT_SHIFT_3);
            ctr[ctrIndex] &= (~((uint32)PORT_MASK_BIT_LOW_8 << ctrShift)); /* Clear CTR bit field */
            ctr[ctrIndex] |= (((uint32)pConfig->outputSel | (uint32)pConfig->outputMode | PORT_PINMODE_OPEN_INOUT) << ctrShift);

            /* Calculate DSR register offset */
            dsrIndex = (pinCounter >> PORT_SHIFT_3); /* Calculate DSR register offset */
            /* Calculate level bit field offset */
            dsrShift = ((pinCounter & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2);
            dsr[dsrIndex] &= (~((uint32)1U << dsrShift)); /* Clear DSR bit field */
            dsr[dsrIndex] |= (uint32)(pConfig->driveStrength) << dsrShift;

            hwcrShift = (pinCounter << PORT_SHIFT_1);
            hwcr &= ~((uint32)PORT_MASK_BIT_LOW_2 << hwcrShift);
            hwcr |= ((uint32)controller << hwcrShift);
        }
    }

    /* Write to register */
    pConfig->modulePin.port->CTR0.U  = ctr[0U];
    ret = Port_Register_ReadBack_Check(ret, ctr[0U], pConfig->modulePin.port->CTR0.U);
    pConfig->modulePin.port->CTR4.U  = ctr[1U];
    ret = Port_Register_ReadBack_Check(ret, ctr[1U], pConfig->modulePin.port->CTR4.U);
    pConfig->modulePin.port->CTR8.U  = ctr[2U];
    ret = Port_Register_ReadBack_Check(ret, ctr[2U], pConfig->modulePin.port->CTR8.U);
    pConfig->modulePin.port->CTR12.U = ctr[3U];
    ret = Port_Register_ReadBack_Check(ret, ctr[3U], pConfig->modulePin.port->CTR12.U);
    pConfig->modulePin.port->HWCR.U = hwcr;
    ret = Port_Register_ReadBack_Check(ret, hwcr, pConfig->modulePin.port->HWCR.U);

    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->modulePin.port->DSR0.U = dsr[0U];
    pConfig->modulePin.port->DSR8.U = dsr[1U];
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr[0U], pConfig->modulePin.port->DSR0.U);
    ret = Port_Register_ReadBack_Check(ret, dsr[1U], pConfig->modulePin.port->DSR8.U);

    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPinGroupEmergency(const Port_EmergencyConfig *const pConfig, uint16 pinMask)
{
    uint32 es;
    uint8 pinCounter;
    uint8 pinIndex;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    es = pConfig->modulePin.port->ESR.U;
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Write to buffer */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            es &= (~((uint32)PORT_MASK_BIT_LOW_2 << (pinCounter << PORT_SHIFT_1))); /* Clear pull bit field */
            es |= ((uint32)pConfig->state << (pinCounter << PORT_SHIFT_1));         /* Set pull mode */
        }
    }

    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();             /* Unlock endinit protect */
    pConfig->modulePin.port->ESR.U = es; /* Write to ESR register */
    ret &= Cpuwdt_Hal_SetEndinit();               /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, es, pConfig->modulePin.port->ESR.U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPinGroupSlewRate(const Port_SlewRateConfig *const pConfig, uint16 pinMask)
{
    uint8 pinCounter;
    uint8 pinIndex;

    /* Value for configure DSRx */
    uint8 dsrIndex;
    uint8 dsrShift;
    uint32 dsr[PORT_DSR_NUMBER];

    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    /* Initializing array dsr */
    dsr[0U] = pConfig->modulePin.port->DSR0.U;
    dsr[1U] = pConfig->modulePin.port->DSR8.U;

    /* Get pin index */
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Write configure to buffer or value */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            /* Write configure to DSRx */
            dsrIndex = (pinCounter >> PORT_SHIFT_3); /* Calculate DSR register offset */
            /* Calculate level bit field offset */
            dsrShift = (((pinCounter & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_SLEWRATE_OFFSET);

            if(PORT_SLEWRATE_HIGH == pConfig->slewRate)
            {
                dsr[dsrIndex] |= ((uint32)1U << dsrShift); /* Set high slew rate */
            }
            else
            {
                dsr[dsrIndex] &= (~((uint32)1U << dsrShift)); /* Set low slew rate */
            }
        }
    }

    /* Write to register */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->modulePin.port->DSR0.U = dsr[0U];
    pConfig->modulePin.port->DSR8.U = dsr[1U];
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr[0U], pConfig->modulePin.port->DSR0.U);
    ret = Port_Register_ReadBack_Check(ret, dsr[1U], pConfig->modulePin.port->DSR8.U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPinGroupInputMode(const Port_InputModeConfig *const pConfig, uint16 pinMask)
{
    uint8 pinCounter;
    uint8 pinIndex;

    /* Value for configure DSRx */
    uint8 dsrIndex;
    uint8 dsrShift;
    uint32 dsr[PORT_DSR_NUMBER];

    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    /* Initializing array dsr */
    dsr[0U] = pConfig->modulePin.port->DSR0.U;
    dsr[1U] = pConfig->modulePin.port->DSR8.U;

    /* Get pin index */
    pinIndex = (uint8)pConfig->modulePin.pin;

    /* Write configure to buffer or value */
    for(pinCounter = pinIndex; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            /* Write configure to DSRx */
            dsrIndex = (pinCounter >> PORT_SHIFT_3); /* Calculate DSR register offset */

            /* Calculate level bit field offset */
            dsrShift = (((pinCounter & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_INPUTMODE_OFFSET);

            if(PORT_INPUTMODE_CMOS == pConfig->mode)
            {
                dsr[dsrIndex] |= ((uint32)1U << dsrShift); /* Set cmos mode */
            }
            else
            {
                dsr[dsrIndex] &= (~((uint32)1U << dsrShift)); /* Set schmidt mode */
            }
        }
    }
    /* Write to register */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->modulePin.port->DSR0.U = dsr[0U];
    pConfig->modulePin.port->DSR8.U = dsr[1U];
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr[0U], pConfig->modulePin.port->DSR0.U);
    ret = Port_Register_ReadBack_Check(ret, dsr[1U], pConfig->modulePin.port->DSR8.U);
    return ret;
}

/*************************************************** PORT pin lvds ***************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: port_hal_c_REF_4 */
boolean Port_Hal_SetPinLvds(const Port_LvdsConfig *const pConfig)
{
    uint32 lvdsIndex;
    Port_AnalogDigitalConfig config;
    /* #Violation: port_hal_c_REF_6 */
    PORT_LVDSR lvdsReg;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->port));
    /* #Violation: port_hal_c_REF_5 */
    /* #Violation: port_hal_c_REF_7 */
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_LVDS((pConfig->port), (uint32)(pConfig->pinN)));    
    /* #Violation: port_hal_c_REF_5 */
    /* #Violation: port_hal_c_REF_7 */
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_LVDS((pConfig->port), (uint32)(pConfig->pinP)));
#endif

    ret = TRUE;
    lvdsIndex = (uint32)pConfig->pinP >> PORT_SHIFT_1;

    /* Set LVDS pin analog mode */
    config.mode = PORT_FUNCTIONMODE_ANALOG;
    config.modulePin.port = pConfig->port;
    config.modulePin.pin = pConfig->pinP;
    ret &= Port_Hal_SetPinAnalogDigitalMode(&config); /* Set LVDS pinP analog mode */
    config.modulePin.pin = pConfig->pinN;
    ret &= Port_Hal_SetPinAnalogDigitalMode(&config); /* Set LVDS pinN analog mode */

    /* Set LVDS pin no pull */
    ret &= Port_Std_SetPinPullMode(pConfig->port, pConfig->pinP, PORT_PULL_NONE);
    ret &= Port_Std_SetPinPullMode(pConfig->port, pConfig->pinN, PORT_PULL_NONE);

    /* set pin push-pull output mode and output multiplexing */
    ret &= Port_Std_SetPinOutput(pConfig->port, pConfig->pinP, pConfig->outputSel, PORT_OUTPUTMODE_PUSHPULL);
    ret &= Port_Std_SetPinOutput(pConfig->port, pConfig->pinN, pConfig->outputSel, PORT_OUTPUTMODE_PUSHPULL);

    /* Configure LVDS mode */
    lvdsReg.U = 0U;
    lvdsReg.B.RTERMEN = pConfig->rTermEnable;
    lvdsReg.B.RTERMVAL = pConfig->rTermVal;
    lvdsReg.B.VOD = pConfig->vod;
    lvdsReg.B.IRATIO = pConfig->iRatio;
    lvdsReg.B.TXCM = pConfig->txCommonMode;
    lvdsReg.B.VBIASSEL = pConfig->biasVol;
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->port->LVDS[lvdsIndex].U = lvdsReg.U;
    
    /* Bias circuit enable */
    pConfig->port->LVDS[lvdsIndex].B.BIASEN = pConfig->biasEnable;
    /* LVDS transmit driver enable */
    pConfig->port->LVDS[lvdsIndex].B.TXEN = pConfig->txEnable;
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    lvdsReg.B.BIASEN = pConfig->biasEnable;
    lvdsReg.B.TXEN = pConfig->txEnable;
    ret = Port_Register_ReadBack_Check(ret, lvdsReg.U, pConfig->port->LVDS[lvdsIndex].U);
    return ret;
}
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_ResetPinLvds(const Port_LvdsModulePin *const pLvdsPins)
{
    uint32 lvdsIndex;
    Port_AnalogDigitalConfig config;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pLvdsPins));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pLvdsPins->port));  
    /* #Violation: port_hal_c_REF_5 */
    /* #Violation: port_hal_c_REF_7 */
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_LVDS((pLvdsPins->port), (uint32)(pLvdsPins->pinN)));    
    /* #Violation: port_hal_c_REF_5 */
    /* #Violation: port_hal_c_REF_7 */
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_LVDS((pLvdsPins->port), (uint32)(pLvdsPins->pinP)));
#endif

    ret = TRUE;
    lvdsIndex = (uint32)pLvdsPins->pinP >> PORT_SHIFT_1;

    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    /* Disable Bias circuit */
    pLvdsPins->port->LVDS[lvdsIndex].B.BIASEN = FALSE;
    /* Disable LVDS transmit driver */
    pLvdsPins->port->LVDS[lvdsIndex].B.TXEN = FALSE;
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, FALSE, pLvdsPins->port->LVDS[lvdsIndex].B.BIASEN);
    ret = Port_Register_ReadBack_Check(ret, FALSE, pLvdsPins->port->LVDS[lvdsIndex].B.TXEN);

    /* Set LVDS pin digital mode */
    config.mode = PORT_FUNCTIONMODE_DIGITAL;
    config.modulePin.port = pLvdsPins->port;
    config.modulePin.pin = pLvdsPins->pinP;
    ret &= Port_Hal_SetPinAnalogDigitalMode(&config); /* Set LVDS pinP digital mode */
    config.modulePin.pin = pLvdsPins->pinN;
    ret &= Port_Hal_SetPinAnalogDigitalMode(&config); /* Set LVDS pinN digital mode */
    
    return ret;
}
#endif

/****************************************** PORT Initializing Peripheral Pin *****************************************/
/******************************************************** ASI ********************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetAsiPins(const Port_AsiPinsConfig *const pConfig)
{
    uint32 rxmux;
    uint32 asiIndex;
    uint32 asiOffset;
    uint32 asiId;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTx));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRx));    
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_ASI((uint32)(pConfig->pRx->id)));    
#endif

    /* get ASI id */
    asiId = (uint32)pConfig->pRx->id;

    /* Init ASI TX pins */
    ret = Port_Hal_SetPinOutput(pConfig->pTx);

    /* Init ASI RX pins */
    ret &= Port_Hal_SetPinInput(&pConfig->pRx->inputConfig);
    /* #Violation: port_hal_c_REF_8 */
    asiIndex = (uint32)PORT_GET_ASI_INDEX(asiId);
    /* #Violation: port_hal_c_REF_8 */
    asiOffset = (uint32)PORT_GET_ASI_OFFSET(asiId);

    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[asiIndex].U;                 /* Read rxmux register */
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << asiOffset)); /* Clear rxmux bit field */
    rxmux |= ((uint32)pConfig->pRx->inputSel << asiOffset); /* Write input select to rxmux bit field */
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[asiIndex].U = rxmux;                 /* Write rxmux register */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[asiIndex].U);
    return ret;
}

/******************************************************** CAN ********************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetCanPins(const Port_CanPinsConfig *const pConfig)
{
    uint32 rxmux;
    uint32 canIndex;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTx));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRx));
    /* #Violation: port_hal_c_REF_8 */    
    Assert((boolean)PORT_CHECK_CAN((uint32)pConfig->pRx->id));
#endif

    /* Init CAN TX pins */
    ret = Port_Hal_SetPinOutput(pConfig->pTx);

    /* Init CAN RX pins */
    ret &= Port_Hal_SetPinInput(&pConfig->pRx->inputConfig);
    /* #Violation: port_hal_c_REF_8 */
    canIndex = (uint32)PORT_GET_CAN_INDEX((uint32)pConfig->pRx->id);

    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[canIndex].U;                                     /* Read rxmux register */
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << (uint32)pConfig->pRx->channel)); /* Clear rxmux bit field */
    rxmux |= ((uint32)pConfig->pRx->inputSel << (uint32)pConfig->pRx->channel); /* Write input select to rxmux bit field */
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[canIndex].U = rxmux;                                /* Write rxmux register */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[canIndex].U);

    /* Init CAN ECTT pins */
    if(NULL_PTR != pConfig->pEctt)
    {
        ret &= Port_Hal_SetPinInput(pConfig->pEctt);
    }

    return ret;
}

/******************************************************* DSADC *******************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetDsadcTriggerPins(const Port_DsadcTriggerInputConfig *const pConfig)
{
    uint32 rxmux;
    uint32 dsAdcIndex;
    uint32 dsAdcOffset;
    boolean ret;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    /* Init DSADC trigger input pin */
    ret = Port_Hal_SetPinInput(&pConfig->inputConfig);
    dsAdcIndex = (uint32)pConfig->triggerChannel >> (uint32)RXMUX_REG_OFFSET_RIGHT_SHIFT;
    dsAdcOffset = (uint32)pConfig->triggerChannel & (uint32)RXMUX_BIT_OFFSET_MASK;

    /* Set dsadc trigger input pin */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[dsAdcIndex].U;            /* Read rxmux register */

    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << dsAdcOffset));    /* Clear rxmux bit field */
    rxmux |= ((uint32)pConfig->inputSel << dsAdcOffset); /* Write input select to rxmux bit field */
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[dsAdcIndex].U = rxmux;            /* Write rxmux register */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[dsAdcIndex].U);
    return ret;
}
#endif

/******************************************************** ESPI *******************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEspiMasterFullDuplexPins(const Port_EspiMasterFullDuplexPinsConfig *const pConfig)
{
    uint8 espiId;
    uint32 espiSel;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMrst));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMtsr));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSclk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSlso));
#endif

    /* Initializing output pin */
    ret = Port_Hal_SetPinOutput(pConfig->pMtsr); /* Initializing output pin mtsr */
    ret &= Port_Hal_SetPinOutput(pConfig->pSclk); /* Initializing output pin sclk */
    ret &= Port_Hal_SetPinOutput(pConfig->pSlso); /* Initializing output pin slso */

    /* Initializing input pin and rxmux */
    ret &= Port_Hal_SetPinInput(&pConfig->pMrst->inputConfig);
    if(PORT_INPUTSEL_P < pConfig->pMrst->inputSel)
    {
       espiSel = (uint32)pConfig->pMrst->inputSel & PORT_MASK_BIT_LOW_3;
       espiSel |= RXMUX_ESPIxISEL_MRSTSEL_QV;
    }
    else if(PORT_INPUTSEL_H < pConfig->pMrst->inputSel)
    {
        espiSel = (uint32)pConfig->pMrst->inputSel & PORT_MASK_BIT_LOW_3;
        espiSel |= RXMUX_ESPIxISEL_MRSTSEL_IP;
    }
    else
    {
        espiSel = (uint32)pConfig->pMrst->inputSel & PORT_MASK_BIT_LOW_3;
        /* #Violation: port_hal_c_REF_2 */
        espiSel |= RXMUX_ESPIxISEL_MRSTSEL_AH;
    }

    espiId = (uint8)pConfig->pMrst->id;

#if defined(THA6_THA6412) 
    espiSel |= (uint32)(0x7U << 8U); /* Write 0x7 to the SCLKSEL bit field to prevent accidental activation of the slave mode clock input. */
#endif

    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[espiId].U = (uint32)espiSel; /* Write input select to rxmux */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, espiSel, PORT_PRXMUX->INSEL[espiId].U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEspiMasterHalfDuplexPins(const Port_EspiMasterHalfDuplexPinsConfig *const pConfig)
{
    uint8 espiId;
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSclk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSlso));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMtsr));
#endif

    /* Initializing output pin */
    ret = Port_Hal_SetPinOutput(pConfig->pSclk); /* Initializing output pin pSclk */
    ret &= Port_Hal_SetPinOutput(pConfig->pSlso); /* Initializing output pin pSlso */

    /* Initializing input/output pin */
    ret &= Port_Hal_SetPinOutput(&pConfig->pMtsr->outputConfig); /* Initializing input pin mtsr */

    rxmux = (uint32)pConfig->pMtsr->inputSel << RXMUX_ESPIxISEL_MTSR_OFFSET;
    espiId = (uint8)pConfig->pMtsr->id;

#if defined(THA6_THA6412) 
    rxmux |= (uint32)(0x7U << 8U); /* Write 0x7 to the SCLKSEL bit field to prevent accidental activation of the slave mode clock input. */
#endif

    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[espiId].U = rxmux; /* Write input select to rxmux */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[espiId].U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEspiSlaveFullDuplexPins(const Port_EspiSlaveFullDuplexPinsConfig *const pConfig)
{
    uint8 espiId;
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMrst));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMtsr));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSclk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSlsi));
#endif

    /* Initializing output pin */
    ret = Port_Hal_SetPinOutput(pConfig->pMrst); /* Initializing output pin pMrst */

    /* Initializing input pin and rxmux */
    ret &= Port_Hal_SetPinInput(&pConfig->pMtsr->inputConfig); /* Initializing input pin mtsr */
    ret &= Port_Hal_SetPinInput(&pConfig->pSclk->inputConfig); /* Initializing input pin sclk */
    ret &= Port_Hal_SetPinInput(&pConfig->pSlsi->inputConfig); /* Initializing input pin slsi */

    rxmux = ((uint32)pConfig->pMtsr->inputSel << RXMUX_ESPIxISEL_MTSR_OFFSET) |
            ((uint32)pConfig->pSclk->inputSel << RXMUX_ESPIxISEL_SCLK_OFFSET) |
            ((uint32)pConfig->pSlsi->inputSel << RXMUX_ESPIxISEL_SLSI_OFFSET);
    espiId = (uint8)pConfig->pMtsr->id;

    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[espiId].U = rxmux; /* Write input select to rxmux */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[espiId].U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEspiSlaveHalfDuplexPins(const Port_EspiSlaveHalfDuplexPinsConfig *const pConfig)
{
    uint8 espiId;
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSclk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSlsi));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMtsr));
#endif

    /* Initializing input pin */
    ret = Port_Hal_SetPinInput(&pConfig->pSclk->inputConfig); /* Initializing input pin sclk */
    ret &= Port_Hal_SetPinInput(&pConfig->pSlsi->inputConfig); /* Initializing input pin slsi */

    /* Initializing input/output pin */
    ret &= Port_Hal_SetPinOutput(&pConfig->pMtsr->outputConfig); /* Initializing input pin mtsr */

    rxmux = (uint32)pConfig->pMtsr->inputSel << RXMUX_ESPIxISEL_MTSR_OFFSET;
    espiId = (uint8)pConfig->pMtsr->id;
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[espiId].U = rxmux; /* Write input select to rxmux */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[espiId].U);
    return ret;
}

/******************************************************** ETH ********************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEthMiiPins(const Port_EthMiiPinsConfig *const pConfig)
{
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxDv));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxEr));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxEn));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxEr));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd2));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd3));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdc));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd2));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd3));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdio));
#endif

    /* Init ETH MII mode input pins */
    ret = Port_Hal_SetPinInput(&pConfig->pRxDv->inputConfig);  /* Initializing input pin rxDv */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxClk->inputConfig); /* Initializing input pin rxClk */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxEr->inputConfig);  /* Initializing input pin rxEr */
    ret &= Port_Hal_SetPinInput(&pConfig->pTxClk->inputConfig); /* Initializing input pin txClk */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd0->inputConfig);  /* Initializing input pin rxd0 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd1->inputConfig);  /* Initializing input pin rxd1 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd2->inputConfig);  /* Initializing input pin rxd2 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd3->inputConfig);  /* Initializing input pin rxd3 */

    /* Initializing input mode of CMOS for RxDv */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxDv->inputConfig.modulePin.port, pConfig->pRxDv->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for RxClk */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxClk->inputConfig.modulePin.port, pConfig->pRxClk->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for RxEr */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxEr->inputConfig.modulePin.port, pConfig->pRxEr->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for TxClk */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pTxClk->inputConfig.modulePin.port, pConfig->pTxClk->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd0 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd0->inputConfig.modulePin.port, pConfig->pRxd0->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd1 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd1->inputConfig.modulePin.port, pConfig->pRxd1->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd2 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd2->inputConfig.modulePin.port, pConfig->pRxd2->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd3 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd3->inputConfig.modulePin.port, pConfig->pRxd3->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Write ETH RXMUX0 */
    rxmux = (((uint32)pConfig->pRxEr->inputSel << RXMUX_ETHISEL0_RXER_OFFSET) |
             ((uint32)pConfig->pRxDv->inputSel << RXMUX_ETHISEL0_DV_OFFSET) |
             ((uint32)pConfig->pRxClk->inputSel << RXMUX_ETHISEL0_RXCLK_OFFSET) | 
             (uint32)pConfig->pMdio->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U);

    /* Write ETH RXMUX1 */
    rxmux = (((uint32)pConfig->pTxClk->inputSel << RXMUX_ETHISEL1_TXCLK_OFFSET) |
             ((uint32)pConfig->pRxd3->inputSel << RXMUX_ETHISEL1_RXD3_OFFSET) |
             ((uint32)pConfig->pRxd2->inputSel << RXMUX_ETHISEL1_RXD2_OFFSET) |
             ((uint32)pConfig->pRxd1->inputSel << RXMUX_ETHISEL1_RXD1_OFFSET) | (uint32)pConfig->pRxd0->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U);

    /* Init ETH MII mode output pins */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxEn);                /* Initializing input pin txEn */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxEr);                /* Initializing input pin txEr */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd0);                /* Initializing input pin txd0 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd1);                /* Initializing input pin txd1 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd2);                /* Initializing input pin txd2 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd3);                /* Initializing input pin txd3 */
    ret &= Port_Hal_SetPinOutput(pConfig->pMdc);                 /* Initializing input pin mdc */
    ret &= Port_Hal_SetPinOutput(&pConfig->pMdio->outputConfig); /* Initializing input/output pin mdio */

    return ret;
}

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEthRgmiiPins(const Port_EthRgmiiPinsConfig *const pConfig)
{
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pGrefClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxCtl));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxCtl));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd2));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd3));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdc));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd2));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd3));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdio));
#endif

    /* Init ETH RGMII mode input pins */
    ret = Port_Hal_SetPinInput(pConfig->pGrefClk);              /* Initializing input pin grefclk */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxCtl->inputConfig); /* Initializing input pin rxCtl */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxClk->inputConfig); /* Initializing input pin rxClk */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd0->inputConfig);  /* Initializing input pin rxd0 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd1->inputConfig);  /* Initializing input pin rxd1 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd2->inputConfig);  /* Initializing input pin rxd2 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd3->inputConfig);  /* Initializing input pin rxd3 */
    
    /* Initializing input mode of CMOS for grefClk */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pGrefClk->modulePin.port, pConfig->pGrefClk->modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for RxCtl */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxCtl->inputConfig.modulePin.port, pConfig->pRxCtl->inputConfig.modulePin.pin,
                             PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for RxClk */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxClk->inputConfig.modulePin.port, pConfig->pRxClk->inputConfig.modulePin.pin,
                             PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd0 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd0->inputConfig.modulePin.port, pConfig->pRxd0->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd1 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd1->inputConfig.modulePin.port, pConfig->pRxd1->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd2 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd2->inputConfig.modulePin.port, pConfig->pRxd2->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd3 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd3->inputConfig.modulePin.port, pConfig->pRxd3->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Write ETH RXMUX0 */
    rxmux = (((uint32)pConfig->pRxCtl->inputSel << RXMUX_ETHISEL0_DV_OFFSET) |
             ((uint32)pConfig->pRxClk->inputSel << RXMUX_ETHISEL0_RXCLK_OFFSET) | (uint32)pConfig->pMdio->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U);

    /* Write ETH RXMUX1 */
    rxmux = (((uint32)pConfig->pRxd3->inputSel << RXMUX_ETHISEL1_RXD3_OFFSET) |
             ((uint32)pConfig->pRxd2->inputSel << RXMUX_ETHISEL1_RXD2_OFFSET) |
             ((uint32)pConfig->pRxd1->inputSel << RXMUX_ETHISEL1_RXD1_OFFSET) | (uint32)pConfig->pRxd0->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U);

    /* Init ETH RGMII mode output pins */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxClk);               /* Initializing input pin txClk */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxCtl);               /* Initializing input pin txCtl */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd0);                /* Initializing input pin txd0 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd1);                /* Initializing input pin txd1 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd2);                /* Initializing input pin txd2 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd3);                /* Initializing input pin txd3 */
    ret &= Port_Hal_SetPinOutput(pConfig->pMdc);                 /* Initializing input pin mdc */
    ret &= Port_Hal_SetPinOutput(&pConfig->pMdio->outputConfig); /* Initializing input/output pin mdio */

    return ret;
}
#endif

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetEthRmiiPins(const Port_EthRmiiPinsConfig *const pConfig)
{
    uint32 rxmux;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRefClk));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pCrsDv));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxEr));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxEn));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdc));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd0));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRxd1));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pMdio));
#endif

    /* Init ETH RMII mode input pins */
    ret = Port_Hal_SetPinInput(&pConfig->pRefClk->inputConfig); /* Initializing input pin refClk */
    ret &= Port_Hal_SetPinInput(&pConfig->pCrsDv->inputConfig);  /* Initializing input pin crsDv */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxEr->inputConfig);   /* Initializing input pin rxEr */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd0->inputConfig);   /* Initializing input pin rxd0 */
    ret &= Port_Hal_SetPinInput(&pConfig->pRxd1->inputConfig);   /* Initializing input pin rxd1 */

    /* Initializing input mode of CMOS for refClk */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRefClk->inputConfig.modulePin.port, pConfig->pRefClk->inputConfig.modulePin.pin,
                             PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for CrsDv */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pCrsDv->inputConfig.modulePin.port, pConfig->pCrsDv->inputConfig.modulePin.pin,
                             PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for RxEr */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxEr->inputConfig.modulePin.port, pConfig->pRxEr->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd0 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd0->inputConfig.modulePin.port, pConfig->pRxd0->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Initializing input mode of CMOS for Rxd1 */
    /* #Violation: port_hal_c_REF_10 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    ret &= Port_Std_SetPinInputMode(pConfig->pRxd1->inputConfig.modulePin.port, pConfig->pRxd1->inputConfig.modulePin.pin, PORT_INPUTMODE_CMOS);
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_c_REF_10 */
    ENABLE_ALL_INTERRUPTS();

    /* Write ETH RXMUX0 */
    rxmux = (((uint32)pConfig->pRxEr->inputSel << RXMUX_ETHISEL0_RXER_OFFSET) |
             ((uint32)pConfig->pCrsDv->inputSel << RXMUX_ETHISEL0_DV_OFFSET) |
             ((uint32)pConfig->pRefClk->inputSel << RXMUX_ETHISEL0_RXCLK_OFFSET) | (uint32)pConfig->pMdio->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL0_INDEX].U);

    /* Write ETH RXMUX1 */
    rxmux = (((uint32)pConfig->pRxd1->inputSel << RXMUX_ETHISEL1_RXD1_OFFSET) | (uint32)pConfig->pRxd0->inputSel);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U);

    /* Init ETH RMII mode output pins */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxEn);                /* Initializing input pin txEn */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd0);                /* Initializing input pin txd0 */
    ret &= Port_Hal_SetPinOutput(pConfig->pTxd1);                /* Initializing input pin txd1 */
    ret &= Port_Hal_SetPinOutput(pConfig->pMdc);                 /* Initializing input pin mdc */
    ret &= Port_Hal_SetPinOutput(&pConfig->pMdio->outputConfig); /* Initializing input/output pin mdio */

#if defined(THA6_THA6104)
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U;
    rxmux &= ~(3UL << 16U);
    rxmux |= (1UL << 16U);

    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[RXMUX_ETHISEL1_INDEX].U);
#endif

    return ret;
}

/******************************************************** I2C ********************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetI2cMasterPins(const Port_I2cMasterPinsConfig *const pConfig)
{
    uint32 rxmux;
    uint32 i2cIndex;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSda));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pScl));
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_I2C((uint32)pConfig->pScl->id));    
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_I2C((uint32)pConfig->pSda->id));
#endif

    ret = Port_Hal_SetPinOutput(&pConfig->pScl->outputConfig); /* Initializing I2C output pin scl */
    ret &= Port_Hal_SetPinOutput(&pConfig->pSda->outputConfig); /* Initializing I2C input/output pin sda */

    rxmux = ((uint32)pConfig->pScl->inputSel | ((uint32)pConfig->pSda->inputSel << RXMUX_I2CISEL_SDA_OFFSET));
    /* #Violation: port_hal_c_REF_8 */
    i2cIndex = (uint32)PORT_GET_I2C_INDEX((uint32)pConfig->pScl->id);

    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[i2cIndex].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[i2cIndex].U);
    return ret;
}

/******************************************************** MSC ********************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetMscPins(const Port_MscPinsConfig *const pConfig)
{
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)((NULL_PTR != pConfig->pEn0) || (NULL_PTR != pConfig->pEn1) || (NULL_PTR != pConfig->pEn2)));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSdi));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pFclpn));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSopn));
#endif

    ret = Port_Hal_SetPinInput(pConfig->pSdi);  /* Initializing MSC input pin sdi */
    ret &= Port_Hal_SetPinLvds(pConfig->pFclpn); /* Initializing MSC lvds pins fclpn */
    ret &= Port_Hal_SetPinLvds(pConfig->pSopn);  /* Initializing MSC lvds pins sopn */

    if(NULL_PTR != pConfig->pEn0)
    {
        ret &= Port_Hal_SetPinOutput(pConfig->pEn0); /* Initializing MSC output pin en0 */
    }

    if(NULL_PTR != pConfig->pEn1)
    {
        ret &= Port_Hal_SetPinOutput(pConfig->pEn1); /* Initializing MSC output pin en1 */
    }

    if(NULL_PTR != pConfig->pEn2)
    {
        ret &= Port_Hal_SetPinOutput(pConfig->pEn2); /* Initializing MSC output pin en2, only THA6412 support */
    }

    return ret;
}
#endif

/******************************************************** SENT *******************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetSentNormalPins(const Port_SentNormalPinsConfig *const pConfig)
{
    uint32 rxmux;
    uint32 sentIndex;
    uint32 sentOffset;
    uint32 sentId;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSent));    
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_SENT((uint32)(pConfig->pSent->id)));
#endif

    /* get sent id */
    sentId = (uint32)pConfig->pSent->id;

    ret = Port_Hal_SetPinInput(&pConfig->pSent->inputConfig); /* Initializing input pin */
    /* #Violation: port_hal_c_REF_8 */
    sentIndex = (uint32)PORT_GET_SENT_INDEX(sentId);
    /* #Violation: port_hal_c_REF_8 */
    sentOffset = (uint32)PORT_GET_SENT_OFFSET(sentId);

    /* Configure spc input pin rxmux */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[sentIndex].U;
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << sentOffset));
    rxmux |= ((uint32)pConfig->pSent->inputSel << sentOffset);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[sentIndex].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[sentIndex].U);
    return ret;
}

/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetSentSpcPins(const Port_SentSpcPinsConfig *const pConfig)
{
    uint32 rxmux;
    uint32 sentIndex;
    uint32 sentOffset;
    uint32 sentId;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pSpc));    
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_SENT_SPC((uint32)(pConfig->pSpc->id)));
#endif

    /* get sent id */
    sentId = (uint32)pConfig->pSpc->id;

    ret = Port_Hal_SetPinOutput(&pConfig->pSpc->outputConfig); /* Initializing spc input/output pin */
    /* #Violation: port_hal_c_REF_8 */
    sentIndex = (uint32)PORT_GET_SENT_INDEX(sentId);
    /* #Violation: port_hal_c_REF_8 */
    sentOffset = (uint32)PORT_GET_SENT_SPC_OFFSET(sentId);

    /* Configure spc input pin rxmux */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[sentIndex].U;
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << sentOffset));
    rxmux |= ((uint32)pConfig->pSpc->inputSel << sentOffset);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[sentIndex].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[sentIndex].U);
    return ret;
}

/******************************************************** IOM *******************************************************/
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetIomPins(const Port_IomInputConfig *const pConfig)
{
    uint32 rxmux;
    uint8 regOffset;
    uint8 bitOffset;
    boolean ret;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = Port_Hal_SetPinInput(&pConfig->inputConfig); /* Initializing IOM input pin */
    /* Configure IOM input pin rxmux */
    regOffset = (uint8)((uint32)pConfig->id + ((uint32)pConfig->channel / 16U));

    /* Calculate IOM sel rxmux offset */
    if ((uint32)PORT_RXMUXIOMCHANNEL_7 < (uint32)pConfig->channel)
    {
        bitOffset = (uint8)((uint32)pConfig->channel - (uint32)PORT_RXMUXIOMCHANNEL_8)*2U;
    }
    else
    {
        bitOffset = ((uint8)pConfig->channel)*2U;
    }

    /* Configure IOM input pin rxmux */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[regOffset].U;
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << (uint32)bitOffset));
    rxmux |= ((uint32)pConfig->inputSel << (uint32)bitOffset);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[regOffset].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[regOffset].U);
    return ret;
}


#if defined(THA6_THA6104)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetIomPinsInput(Port_RxmuxIomPin iomPin, Port_RxmuxPinInputSel inputSel)
{
    uint32 rxmux;
    uint8 bitOffset;
    uint8 iomIndex;
    boolean ret;

    /* Calculate IOM sel rxmux offset */
    ret = TRUE;
    bitOffset = (uint8)iomPin;
    iomIndex = RXMUX_IOMPINSEL_INDEX;

    /* Configure IOM input pin rxmux */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[iomIndex].U;
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_1 << (uint32)bitOffset));
    rxmux |= ((uint32)inputSel << (uint32)bitOffset);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[iomIndex].U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[iomIndex].U);
    return ret;
}
#endif

/******************************************************** EXTI *******************************************************/
#if defined(THA6_THA6104)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetExtiPinsInput(Port_RxmuxExtiChannel extiChannel, Port_RxmuxPinInputSel inputSel)
{
    uint32 rxmux;
    uint8 bitOffset;
    boolean ret;

    /* Calculate EXTI sel rxmux offset */
    ret = TRUE;
    bitOffset = (uint8)extiChannel;

    /* Configure EXTI input pin rxmux */
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX_EXTI->U;
    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_2 << (uint32)bitOffset));
    rxmux |= ((uint32)inputSel << (uint32)bitOffset);
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX_EXTI->U = rxmux;
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX_EXTI->U);
    return ret;
}
#endif

/******************************************************** PSI5 *******************************************************/
#if defined(THA6_THA6412)
/* #Violation: port_hal_c_REF_1 */
boolean Port_Hal_SetPsi5Pins(const Port_Psi5PinsConfig *const pConfig)
{
    uint32 rxmux;
    uint8 psi5Index;
    uint8 psi5Offset;
    boolean ret;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pTx));
    /* #Violation: port_hal_c_REF_7 */
    Assert((boolean)(NULL_PTR != pConfig->pRx));
    /* #Violation: port_hal_c_REF_8 */
    Assert((boolean)PORT_CHECK_PSI5((uint32)(pConfig->pRx->channel)));
#endif

    /* Init PSI5 TX pins */
    ret = Port_Hal_SetPinOutput(pConfig->pTx);

    /* Init PSI5 RX pins */
    ret &= Port_Hal_SetPinInput(&pConfig->pRx->inputConfig);
    psi5Index = RXMUX_PSI5RXSEL_INDEX;
    psi5Offset = (uint8)pConfig->pRx->channel;
    /* #Violation: port_hal_c_REF_5 */
    rxmux = PORT_PRXMUX->INSEL[psi5Index].U;                             /* Read rxmux register */

    rxmux &= (~((uint32)PORT_MASK_BIT_LOW_4 << (uint32)psi5Offset));     /* Clear rxmux bit field */
    rxmux |= ((uint32)pConfig->pRx->inputSel << (uint32)psi5Offset);     /* Write input select to rxmux bit field */
    /* #Violation: port_hal_c_REF_5 */
    PORT_PRXMUX->INSEL[psi5Index].U = rxmux;                             /* Write rxmux register */
    /* #Violation: port_hal_c_REF_5 */
    ret = Port_Register_ReadBack_Check(ret, rxmux, PORT_PRXMUX->INSEL[psi5Index].U);
    return ret;
}
#endif
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: port_hal_c_REF_11 */
#include "Port_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
