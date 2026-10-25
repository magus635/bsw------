/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: pwrc_hal.c
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: PWRC hardware abstraction layer source file.
 *              This file contains implementations for PWRC hardware abstraction layer.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#pwrc_hal_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#pwrc_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#pwrc_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#pwrc_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#pwrc_hal_c_REF_5:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to register.
*
*#pwrc_hal_c_REF_6:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "pwrc_register.h"
#include "pwrc_hal.h"
#include "safewdt_hal.h"
#include "cpuwdt_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Voltage monitor mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_VLTALMCON_MASK                (0x3F3FU)
/* Current and voltage alarm real time status mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_CURVLTALMRTSTS_MASK           (0x1E3F3FU)
/* Current and voltage alarm status mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_CURVLTSTS_MASK                (0x0F3F3FU)

/* CPU status mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_CPUSTATUS_MASK                (0xFFU)

/* Enable write protection value to pwrc standby domain*/
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_STB_ENABLE_WRITE              (0x3355AACCU)
/* Disable write protection value to pwrc standby domain*/
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_STB_DISABLE_WRITE             (0x0u)
/* Permit main domain enter standby mode */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_ENABLE_STANDBY                (0x55U)
/* Forbid main domain enter standby mode */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_DISABLE_STANDBY               (0x0U)

/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_BITUPDATE_DISABLE             (0U)
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_BITUPDATE_ENABLE              (1U)

/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_BIT_DISABLE                   (0U)
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_BIT_ENABLE                    (1U)

/* Standby wakeup source mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_STBWAKEUPSOURCE_MASK          (0x2EFU)
/* Standby IO wakeup source mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_STBWAKEUPSOURCE_IO_MASK       (0x1DFFFFU)

/*Max counter wake-up source for stanby mode */
/* #Violation: pwrc_hal_c_REF_1 */
#define MAXCOUNTER_WAKEUP_SOURCE           (26U)
/*Max spread spectrum cycle */
/* #Violation: pwrc_hal_c_REF_1 */
#define MAX_SPREADSPECTRUM_CYCLE           (7U)

/* Wakeup source group0 */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_WAKEUPSOURCE_GROUP0         (0U)
/* Wakeup source group1 P33 */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_WAKEUPSOURCE_GROUP1_P33       (1U)
/* Wakeup source group2 P34 */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_WAKEUPSOURCE_GROUP2_P34       (2U)

/* Voltage detect threshold coarse mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_DETADJ_MASK                (0x777737U)

/* Voltage detect threshold fine mask */
/* #Violation: pwrc_hal_c_REF_1 */
#define PWRC_DETEADJ_MASK               (0x777737U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
#define PWRC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwrc_MemMap.h"

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetSecondaryVoltageMonitor(uint32 voltageMonitorEnable)
{
    /*********************************************************************************************************************************************************
     * Usage Restrictions
     * 1. In THA6104/THA6206/THA6412, before calling API Pwrc_Hal_SetSecondaryVoltageMonitor() to enable the secondary voltage monitor function, 
     * the configuration of coarse/fine adjustment gears by calling API Pwrc_Hal_SetSecondaryVoltageThreshold() should be completed firstly; then wait at least 1ms.
     *********************************************************************************************************************************************************/

    uint32 regValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if voltageMonitorEnable is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(0U == (voltageMonitorEnable & ~PWRC_VLTALMCON_MASK)));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    regValue = (~voltageMonitorEnable) & PWRC_VLTALMCON_MASK;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTCLR.U = (uint32)(voltageMonitorEnable & PWRC_VLTALMCON_MASK) ;    /* Clear alarm */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->VLTALMCON.B.UP_EN = (uint32)PWRC_BITUPDATE_ENABLE; /* Bit update enable */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->VLTALMCON.U = (uint32)regValue;    /* Set voltage monitor */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue, PWRC->VLTALMCON.U & PWRC_VLTALMCON_MASK);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetSecondaryVoltageThreshold(Pwrc_VoltageMonitor monitorVoltage, Pwrc_VoltageThreshold coarseGrade, Pwrc_VoltageThreshold fineGrade)
{
    /*********************************************************************************************************************************************************
     * Usage Restrictions
     * 1. In THA6104/THA6206/THA6412, when switching coarse adjustment gears (limited to VEXT/VEVRSB/VDDM_ADJ), 
     * direct switching from gear 0b000 to 0b111 is not allowed. 
     * The recommended procedure is: switch from gear 0b000 to 0b011 first, then to 0b111; 
     * alternatively, switch from gear 0b111 to 0b011 first, then to 0b000.
     * 2. In THA6104/THA6206/THA6412, after the configuration of coarse/fine adjustment gears by calling API Pwrc_Hal_SetSecondaryVoltageThreshold() is completed, 
     * wait at least 1ms before calling API Pwrc_Hal_SetSecondaryVoltageMonitor() to enable the secondary voltage monitor function.
     *********************************************************************************************************************************************************/

    uint32 regValue;
    uint32 shiftValue;
    boolean ret;

    shiftValue = (uint32)monitorVoltage << 2U;    /* Get the shift value */
    ret = TRUE;

    /* CoarseGrade modify */
    /* #Violation: pwrc_hal_c_REF_4 */
    regValue = (uint32)(PWRC->DETADJ.U);
    regValue &= ~((uint32)0x7U << shiftValue);    /* Clear the bits to modify */

    regValue |= ((uint32)coarseGrade << shiftValue);
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->DETADJ.B.UP_EN = PWRC_BITUPDATE_ENABLE; /* Bit update enable */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->DETADJ.U = regValue; /* Modify the threshold */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue & PWRC_DETADJ_MASK, PWRC->DETADJ.U & PWRC_DETADJ_MASK);
    
    /* FineGrade modify */
    /* #Violation: pwrc_hal_c_REF_4 */
    regValue = PWRC->DETEADJ.U;
    regValue &= ~((uint32)0x7U << shiftValue);    /* Clear the bits to modify */
    regValue |= ((uint32)fineGrade << shiftValue);
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->DETEADJ.B.UP_EN = (uint32)PWRC_BITUPDATE_ENABLE; /* Bit update enable */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->DETEADJ.U = (uint32)regValue; /* Modify the threshold */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue & PWRC_DETEADJ_MASK, PWRC->DETEADJ.U & PWRC_DETEADJ_MASK);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
uint32 Pwrc_Hal_GetCurVltAlmRealtimeStatus(void)
{
    /* #Violation: pwrc_hal_c_REF_4 */
    return (uint32)(PWRC->CURVLTALMRTSTS.U & PWRC_CURVLTALMRTSTS_MASK);
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetCurVltAlarm(uint32 curVltAlmEnable)
{
    uint32 regValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if curVltAlmEnable is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(0U == (curVltAlmEnable & ~PWRC_CURVLTSTS_MASK)));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    regValue = (~curVltAlmEnable) & PWRC_CURVLTSTS_MASK;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTALMMSK.U = (uint32)regValue;  /* Set current and voltage monitoring output alarm */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue, PWRC->CURVLTALMMSK.U & PWRC_CURVLTSTS_MASK);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetCurVltInterrupt(uint32 curVltIntEnable)
{
    uint32 regValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if curVltIntEnable is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(0U == (curVltIntEnable & ~PWRC_CURVLTSTS_MASK)));
#endif /* INPUT_ARG_DETECT */
    
    ret = TRUE;
    regValue = (~curVltIntEnable) & PWRC_CURVLTSTS_MASK;
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTINTMSK.U = (uint32)regValue;  /* Set current and voltage monitoring output interrupt */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue, PWRC->CURVLTINTMSK.U & PWRC_CURVLTSTS_MASK);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
uint32 Pwrc_Hal_GetCurVltAlarmStatus(void)
{
    /***********************************************************************************************************************************
     * Usage Restrictions
     * 1. In the THA6206 Version C chip, when the secondary voltage monitor function is enabled, a false alarm may occur within 8 us. 
     * The method to determine whether it is a false alarm is as follows: check the CURVLTSTS and CURVLTALMRTSTS registers. 
     * A genuine alarm is confirmed only when the corresponding bit fields of both registers are set simultaneously; 
     * if only the corresponding bit field of the CURVLTSTS register is set, it is a false alarm. 
     * Any alarm generated 8 us after the secondary voltage monitor function is enabled shall be deemed a genuine alarm.
    ************************************************************************************************************************************/

    /* #Violation: pwrc_hal_c_REF_4 */
    return (uint32)(PWRC->CURVLTSTS.U & PWRC_CURVLTSTS_MASK);
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_ClearCurVltAlarmStatus(uint32 alarmStatus)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if alarmStatus is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(0U==(alarmStatus & ~PWRC_CURVLTSTS_MASK)));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE; 
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* Clear alarm status */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTCLR.U = (uint32)(alarmStatus & PWRC_CURVLTSTS_MASK);
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetDsadcRefCurrent(Pwrc_FunctionEnable functionEnable)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->ADCREFC.B.IREF_EN = (uint32)functionEnable;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)functionEnable, PWRC->ADCREFC.B.IREF_EN);

    return ret;
}
#endif /* THA6_THA6412 */ /* THA6_THA6206 */ /* THA6_THA6206D */

/* #Violation: pwrc_hal_c_REF_2 */
uint32 Pwrc_Hal_GetCpuRealtimeStatus(void)
{
    /* #Violation: pwrc_hal_c_REF_4 */
    return (uint32)(PWRC->CPULPRTSTS.U & PWRC_CPUSTATUS_MASK);
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetLowPowerInterrupt(uint32 lowPowerInterrupt)
{
    uint32 regValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if lowPowerInterrupt is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(lowPowerInterrupt <= PWRC_CPUSTATUS_MASK));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    /* #Violation: pwrc_hal_c_REF_4 */
    regValue = PWRC->CPULPINTMSK.U;
    regValue &= (~lowPowerInterrupt);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CPULPINTCLR.U = lowPowerInterrupt;    /* Clear interrupt status */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CPULPINTMSK.U = regValue;    /* Set low power interrupt */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regValue, PWRC->CPULPINTMSK.U);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
uint32 Pwrc_Hal_GetLowPowerIntStatus(void)
{
    /* Return CPU low power mode interrupt status */
    /* #Violation: pwrc_hal_c_REF_4 */
    return (uint32)(PWRC->CPULPINTSTS.U & PWRC_CPUSTATUS_MASK);
}

/* #Violation: pwrc_hal_c_REF_2 */
void Pwrc_Hal_ClearLowPowerIntStatus(uint32 lowPowerStatus)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if lowPowerStatus is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(lowPowerStatus <= PWRC_CPUSTATUS_MASK));
#endif /* INPUT_ARG_DETECT */

    /* Clear low power interrupt status */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CPULPINTCLR.U = lowPowerStatus;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetLowpowerMode(Pwrc_LowpowerMode lowpowerMode)
{
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRC_LPCON regLPC;
    uint32 regSTDP;
    boolean ret;

    ret = TRUE;
    /* #Violation: pwrc_hal_c_REF_4 */
    regLPC.U = (uint32)(PWRC->LPCON.U);
    if(PWRC_LOWPOWERMODE_SLEEP == lowpowerMode)
    {
        regLPC.B.LPMSEL = PWRC_BIT_DISABLE;
        regSTDP = PWRC_DISABLE_STANDBY;        /* Forbid main domain enter to standby state */
    }
    else
    {
        regLPC.B.LPMSEL = PWRC_BIT_ENABLE;
        regSTDP = PWRC_ENABLE_STANDBY;        /* Permit main domain enter to standby state */
    }

    /* Write registers */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->LPCON.B.UP_EN = (uint32)PWRC_BITUPDATE_ENABLE;   /* Enable bit update */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->LPCON.B.LPMSEL = regLPC.B.LPMSEL;
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STDP.U = regSTDP;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regLPC.B.LPMSEL, PWRC->LPCON.B.LPMSEL);
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regSTDP, PWRCSTB->STDP.U);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);
    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_InitStandbyMode(const Pwrc_StandbySourceConfig standbySourceConfig[], uint8 wakeupSourceCount, uint8 standbyDelay)
{
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_WKUPC regWKUPC;
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRC_LPCON regLPC;
    uint32 regGroupIdx;
    uint32 setBit;
    uint8 count;
    boolean ret;

#if defined(THA6_THA6412)
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_STIOWKUPC0 regSTIOWKUPC0;
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_STIOWKUPC1 regSTIOWKUPC1;
#endif

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if lowPowerStatus is in the specific range */
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != standbySourceConfig));
    /* #Violation: pwrc_hal_c_REF_3 */
    Assert((boolean)(MAXCOUNTER_WAKEUP_SOURCE >= wakeupSourceCount));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    regLPC.U = 0U;
    regLPC.B.LPMSEL = 1U; /* standby mode */
    regLPC.B.STBYBLINK = standbyDelay;

    /* #Violation: pwrc_hal_c_REF_4 */
    regWKUPC.U = PWRCSTB->WKUPC.U;

#if defined(THA6_THA6412)
    /* #Violation: pwrc_hal_c_REF_4 */
    regSTIOWKUPC0.U = PWRCSTB->STIOWKUPC0.U;
    /* #Violation: pwrc_hal_c_REF_4 */
    regSTIOWKUPC1.U = PWRCSTB->STIOWKUPC1.U;
#endif

    for(count = 0; count < wakeupSourceCount; count++)
    {
        /* Divide wake-up source into corresponding group related with PWRC registers */
        regGroupIdx = (uint32)(uint32)standbySourceConfig[count].wakeupSource / 32U;
        /* Control bit value in one register */
        setBit = (uint32)standbySourceConfig[count].wakeupSource % 32U;

        if(regGroupIdx < PWRC_WAKEUPSOURCE_GROUP1_P33)
        {
            regWKUPC.U |= (1UL << setBit);
            /* IWDG and VEXT no filter and edge trigger */
            if ((uint32)standbySourceConfig[count].wakeupSource < (uint32)PWRC_STBWAKEUPSOURCE_VEXT)
            {
                /* set wake-up edge */
                regWKUPC.U &= ~(3UL << (16U + (2U*setBit)));
                regWKUPC.U |= (uint32)standbySourceConfig[count].pinWakeupEdge << (16U + (2U*setBit));
            }
        }
#if defined(THA6_THA6412)
        else if(regGroupIdx < PWRC_WAKEUPSOURCE_GROUP2_P34)
        {    /* Set P33 IO wakeup source */
            /* clear */
            regSTIOWKUPC0.U &= ~(3UL << (2U*setBit));
            /* set wake-up edge */
            regSTIOWKUPC0.U |= (uint32)standbySourceConfig[count].pinWakeupEdge << (2U*setBit);

        }
        else
        {    /* Set P34 IO wakeup source */
            /* clear */
            regSTIOWKUPC1.U &= ~(3UL << (2U*setBit));
            /* set wake-up edge */
            regSTIOWKUPC1.U |= (uint32)standbySourceConfig[count].pinWakeupEdge << (2U*setBit);
        }
#endif
    }

    /* Write registers */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->WKUPTIM.B.BLNKFIL_ALL = 1U;    /* Enable blanking filter */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, 1U, PWRCSTB->WKUPTIM.B.BLNKFIL_ALL);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->WKUPTIM.B.BLNKFIL = 1U;        /* Set blank filter control: Filtering time = (BLNKFIL * 14 * 1024) us */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, 1U, PWRCSTB->WKUPTIM.B.BLNKFIL);

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->WKUPSTS.U = (uint32)PWRC_STBWAKEUPSOURCE_MASK;/* Clear standby wakeup source */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->WKUPC.U = regWKUPC.U;    /* Set wakeup source */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regWKUPC.U, PWRCSTB->WKUPC.U);

#if defined(THA6_THA6412)
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STIOWKUSTS.U = (uint32)PWRC_STBWAKEUPSOURCE_IO_MASK;/* Clear standby IO wakeup source */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STIOWKUPC0.U = regSTIOWKUPC0.U;    /* Set wakeup source: P33 */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regSTIOWKUPC0.U, PWRCSTB->STIOWKUPC0.U);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STIOWKUPC1.U = regSTIOWKUPC1.U;    /* Set wakeup source: P34 */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, PWRCSTB->STIOWKUPC1.U, regSTIOWKUPC1.U);
#endif

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STDP.U = (uint32)PWRC_ENABLE_STANDBY; /* Permit main domain enter to standby state */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->LPCON.B.UP_EN = PWRC_BITUPDATE_ENABLE;   /* Enable bit update */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->LPCON.U = regLPC.U;
     ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_ENABLE_STANDBY, PWRCSTB->STDP.U);
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regLPC.U, PWRC->LPCON.U);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
uint32 Pwrc_Hal_GetStbWakeupSource(void)
{
    uint32 regWKUPSTS;

#if defined(THA6_THA6412)
    /* #Violation: pwrc_hal_c_REF_4 */
    regWKUPSTS = PWRCSTB->STIOWKUSTS.U << 11U;
    /*bit[7:0] for WKUPSTS[7:0], bit8 ~ bit10 reserved, bit[31:11] for STIOWKUSTS[20:0]*/
    /* #Violation: pwrc_hal_c_REF_4 */
    regWKUPSTS |= (uint32)(PWRCSTB->WKUPSTS.U & 0xFFU);
#endif

#if defined(THA6_THA6104) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* #Violation: pwrc_hal_c_REF_4 */
    regWKUPSTS = (uint32)(PWRCSTB->WKUPSTS.U & 0xFFU);
#endif

    return regWKUPSTS;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_ClearStbWakeupSource(uint32 wakeupSource)
{
    boolean ret;
    ret = TRUE;

    /* Write registers */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);
    /*wakeupSource: bit[7:0] for WKUPSTS[9:0], bit9 cleared, bit[31:11] for STIOWKUSTS[20:0]*/
    /* Clear standby wakeup source  */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->WKUPSTS.U = (wakeupSource & PWRC_STBWAKEUPSOURCE_MASK) | 0x200U;
    /* Clear IO standby wakeup source  */
#if defined(THA6_THA6412)
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->STIOWKUSTS.U = ((wakeupSource >> 11U) & PWRC_STBWAKEUPSOURCE_IO_MASK);
#endif
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
     /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetStbEvrcCurrentMonitor(Pwrc_CurrentMonitor monitorType, Pwrc_FunctionEnable functionEnable)
{
    uint32 maskValue;
    boolean ret;
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_EVRC regEVRC;

    ret = TRUE;
    maskValue = ((uint32)monitorType) << 2U;
    /* #Violation: pwrc_hal_c_REF_4 */
    regEVRC.U = PWRCSTB->EVRCC.U;
    if (PWRC_FUNCTION_ENABLE == functionEnable)
    {
        regEVRC.U |= maskValue;
    }
    else
    {
        regEVRC.U &= ~maskValue;
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTCLR.U |= (uint32)monitorType << 16U;    /* Clear alarm status*/
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->EVRCC.B.UP_EN = (uint32)PWRC_BITUPDATE_ENABLE;   /* Enable bit update */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->EVRCC.U = regEVRC.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);

    return ret;
}

/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetStbEvr33CurrentMonitor(Pwrc_CurrentMonitor monitorType, Pwrc_FunctionEnable functionEnable)
{
    uint32 maskValue;
    boolean ret;
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_EVR33C regEVR33C;

    ret = TRUE;
    maskValue = (uint32)monitorType << 2U;
    /* #Violation: pwrc_hal_c_REF_4 */
    regEVR33C.U = (uint32)PWRCSTB->EVR33C.U;
    if (PWRC_FUNCTION_ENABLE == functionEnable)
    {
        regEVR33C.U |= maskValue;
    }
    else
    {
        regEVR33C.U &= ~maskValue;
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRC->CURVLTCLR.U |= (uint32)monitorType << 18U;    /* Clear alarm status*/
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->EVR33C.B.UP_EN = (uint32)PWRC_BITUPDATE_ENABLE;   /* Enable bit update */
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->EVR33C.U = regEVR33C.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, regEVR33C.U, PWRCSTB->EVR33C.U);

    return ret;
}

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetStbEvrcSpreadSpectrum(uint8 spreadSpectrumCycle, Pwrc_FunctionEnable functionEnable)
{
    /* #Violation: pwrc_hal_c_REF_5 */
    PWRCSTB_EVRCCK regEVRCCK;
    boolean ret;

    ret = TRUE;

    /* #Violation: pwrc_hal_c_REF_4 */
    regEVRCCK.U = (uint32)PWRCSTB->EVRCCK.U;
    regEVRCCK.B.SPSP_STEP = spreadSpectrumCycle;
    if (PWRC_FUNCTION_ENABLE == functionEnable)
    {
        regEVRCCK.B.SPSP_EN = PWRC_BIT_ENABLE;
    }
    else
    {
        regEVRCCK.B.SPSP_EN = PWRC_BIT_DISABLE;
    }

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->EVRCCK.U = regEVRCCK.U;    /* Set EVRC spread spectrum */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)regEVRCCK.U, PWRCSTB->EVRCCK.U);
    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);

    return ret;
} /* THA6_THA6412 */ /* THA6_THA6206 */ /* THA6_THA6206D */
#endif

#if defined(THA6_THA6104)
/* #Violation: pwrc_hal_c_REF_2 */
boolean Pwrc_Hal_SetStandbyModeEntryIndication(Pwrc_FunctionEnable functionEnable)
{
    boolean ret;
    ret = TRUE; 

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = (uint32)PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_ENABLE_WRITE, PWRCSTB->SWP);

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->BEMSKS.B.STBYFLAG_IOEN = (uint32)functionEnable; /* Set standbymode entry indication */

    /* #Violation: pwrc_hal_c_REF_4 */
    PWRCSTB->SWP = PWRC_STB_DISABLE_WRITE;  /* Disable access standby domain */
    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)PWRC_STB_DISABLE_WRITE, PWRCSTB->SWP);

    /* #Violation: pwrc_hal_c_REF_4 */
    ret = Pwrc_Register_ReadBack_Check(ret, (uint32)functionEnable, (uint32)PWRCSTB->BEMSKS.B.STBYFLAG_IOEN);

    return ret;
}
#endif

#define PWRC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pwrc_hal_c_REF_6 */
#include "Pwrc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
