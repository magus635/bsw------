/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sac_hal.c
 * Author:      00977
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all interface implementations of SAC module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#sac_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#sac_hal_c_REF_2:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*
*#sac_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Casting a pointer to an integral type to obtain its address.
*
*#sac_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#sac_hal_c_REF_6:DCL15-C & DCL19-C;
* Justification: Reserved API for user access.
*
*#sac_hal_c_REF_7:MISRAC2012-Dir-1.1;
* Justification: Inline assembly for CPU-specific operations.
*
*#sac_hal_c_REF_8:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity
*
*#sac_hal_c_REF_9:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#sac_hal_c_REF_10:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
* #sac_hal_c_REF_11:MISRAC2012-Rule-8.7;
* Justification:The interface is called by the application layer.
*
* #sac_hal_c_REF_12:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #sac_hal_c_REF_13:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #sac_hal_c_REF_14:MISRAC2012-Rule-10.5
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "sac_register.h"
#include "sac_hal.h"
#include "safewdt_hal.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Sac standby alarm group 20 sequence */
#define SAC_STDBY_ALARM_GROUP20     (20U)
/* SAC standby enable control FIP response alarm */
#define SAC_CMDSTDBY_STBEN       (0x03U)
/* SAC standby active pull down FIP pin */
#define SAC_CMDSTDBY_FIPEN       (0x03U)
/* Software release FIP in SAC standby domain */
#define SAC_CMDSTDBY_FIPCTRL_RELEASE (0x2U)
/* Software can't control FIP in SAC standby domain */
#define SAC_CMDSTDBY_FIPCTRL_NONE (0x0U)
/* FIP release allows for the maximum tolerable time period */
#define SAC_CMDSTDBY_FIPCTRL_TIMEOUT   (0x100000U)
/* SAC standby alarm allows for the maximum tolerable time period */
#define SAC_ASR_CLEARTIMEOUT   (0x100000U)
/* Set AGFIPSTDBY bit 0 */
#define BIT_0_SET (0x01U)
/* Set AGFIPSTDBY bit 4 */
#define BIT_4_SET ((uint32)0x10U)
/* Set AGFIPSTDBY bit 9 */
#define BIT_9_SET ((uint32)0x200U)
/* Set AGFIPSTDBY bit 16 and 17 */
#define BIT_16_17_SET ((uint32)0x30000U)  /* used in THA6412, Ivalid in THA6206 */
/* Set AGFIPSTDBY bit 30 */
#define BIT_30_SET ((uint32)0x40000000U)
/* Set CMDSTDBY bit 4 */
#define BIT_4_CLEAR ((uint32)0xFFFFFFEFU)

/* Enable write protection value to pwrc standby domain */
#define PWRC_STB_ENABLE_WRITE (0x3355AACCU)
/* Disable write protection value to pwrc standby domain */
#define PWRC_STB_DISABLE_WRITE (0x0U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/

#define SAC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Sac_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: sac_hal_c_REF_1 */
boolean Sac_Hal_InitModule(const Sac_InitConfig  *const pConfig)
{
    /* #Violation: sac_hal_c_REF_2 */
    SAC_FIP fipVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_PCTL pctlVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_AGC agcVal;
    Sac_CmdExResult cmd_rst;
    boolean retSts;
    retSts = TRUE;

    /* Read FIP value */
    /* #Violation: sac_hal_c_REF_3 */
    fipVal.U = SAC->FIP.U;
    /* The pConfig is not NULL pointer and register protected by KEYS not permanent locked */
    /* #Violation: sac_hal_c_REF_4 */
    if((NULL_PTR != pConfig) && (SAC_KEYS_PROTECTION_PERMANENTLOCK != SAC->KEYS.B.PERLCK))
    {
        /* Set the FIP fault state duration prescaler */
        fipVal.B.PRE1 = (uint32)pConfig->fipConfig.fipFaultDurationPre;
        /* Set the FIP dynamic protocol prescaler */
        fipVal.B.PRE2 = (uint32)pConfig->fipConfig.fipDynProtoPre;
        /* Set the FIP fault state duration */
        fipVal.B.TFIP_HIGH = (uint32)pConfig->fipConfig.faultStateDurationHigh;
        /* Set the FIP mode */
        fipVal.B.MODE = (uint32)pConfig->fipConfig.fipMode;

        /* Read AGC value */
        /* #Violation: sac_hal_c_REF_3 */
        agcVal.U = SAC->AGC.U;
        /* Mapping between Interrupt Generation Configuration Set 0 and Interrupt Request */
        agcVal.B.IGCS0 = (uint32)pConfig->alarmConfig.igcs0;
        /* Mapping between Interrupt Generation Configuration Set 1 and Interrupt Request */
        agcVal.B.IGCS1 = (uint32)pConfig->alarmConfig.igcs1;
        /* Mapping between Interrupt Generation Configuration Set 2 and Interrupt Request */
        agcVal.B.IGCS2 = (uint32)pConfig->alarmConfig.igcs2;
        /* Mapping between Interrupt Generation Configuration Set 3 and Interrupt Request */
        agcVal.B.IGCS3 = (uint32)pConfig->alarmConfig.igcs3;
        /* Enabled or disabled Fault to Run transition */
        agcVal.B.EFRST = (uint32)pConfig->alarmConfig.faultToRun;
        /* Select which CPU to send the NMI to */
        agcVal.B.NMISEL = (uint32)pConfig->alarmConfig.nmiSendTo;

        /* Read PCTL value */
        /* #Violation: sac_hal_c_REF_3 */
        pctlVal.U = SAC->PCTL.U;
        /* Set port direction */
        pctlVal.B.HWDIR = (uint32)pConfig->portConfig.portDir;
    
        /* Release FIP */
        cmd_rst = Sac_Hal_ReleaseFip();
        if(SAC_CMDEXRESULT_FAILED == cmd_rst)
        {
            retSts &= FALSE;
        }
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();
 
        /* Set the value (0x00BC) of the KEYS to unlocks the SAC configuration registers for modification */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->KEYS.U = (uint32)(SAC_KEYS_PROTECTION_UNLOCK);
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->KEYS.U, (uint32)(SAC_KEYS_PROTECTION_UNLOCK));

        /* Write FIP value */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->FIP.U = fipVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->FIP.U, fipVal.U);

        /* Write AGC value */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->AGC.U = agcVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->AGC.U, agcVal.U);

        /* Write PCTL value */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->PCTL.U = pctlVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->PCTL.U, pctlVal.U);

        /* Set the value (0x0000) of the KEYS to temporarily locks the SAC configuration registers */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->KEYS.U = (uint32)(SAC_KEYS_PROTECTION_LOCK);
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->KEYS.U, (uint32)(SAC_KEYS_PROTECTION_LOCK));

        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();        
   }
   /* The pConfig is NULL pointer */
   else
   {
        retSts = FALSE;
   }
   return  retSts;
}

/* #Violation: sac_hal_c_REF_1 */
boolean Sac_Hal_SetAlarmAction(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex alarmIndex, Sac_AlarmInternalAction alarmAction,
                            Sac_FipAction fipAction)
{
    uint32 alarmGroupCF2;
    uint32 alarmGroupCF1;
    uint32 alarmGroupCF0;
    uint32 alarmGroupConfigMask;
    uint32 standbyGroup;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_ACAG ac0agVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_ACAG ac1agVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_ACAG ac2agVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_FIPAG fipagVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_AGFIPSTDBY agfipstdbyVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_CMDSTDBY cmdstdbyReg;
    uint32 regMaskBit;

    boolean retSts;
    retSts = TRUE;
    regMaskBit = 0x40000380U;
    /* Get the mask for configuration registers to set the particular bits */
    alarmGroupConfigMask = ~((uint32)1U << (uint32)alarmIndex);
    /* SAC alarm group is less than or equal to SAC_ALARMGROUP_12 */
    if(alarmGroup<=SAC_ALARMGROUP_12)
    {
        /* Extract alarm configuration for 3 ACxAG (x=0-2) registers from input parameter */
        alarmGroupCF0 = ((uint32)alarmAction & 1U) << (uint32)alarmIndex;
        alarmGroupCF1 = (((uint32)alarmAction >> 1U) & 1U) << (uint32)alarmIndex;
        alarmGroupCF2 = (((uint32)alarmAction >> 2U) & 1U) << (uint32)alarmIndex;

        /* #Violation: sac_hal_c_REF_3 */
        ac0agVal.U = (SAC->AC0AG[alarmGroup].U & alarmGroupConfigMask) | alarmGroupCF0;
        /* #Violation: sac_hal_c_REF_3 */
        ac1agVal.U = (SAC->AC1AG[alarmGroup].U & alarmGroupConfigMask) | alarmGroupCF1;
        /* #Violation: sac_hal_c_REF_3 */
        ac2agVal.U = (SAC->AC2AG[alarmGroup].U & alarmGroupConfigMask) | alarmGroupCF2;
        /* #Violation: sac_hal_c_REF_3 */
        fipagVal.U = (SAC->FIPAG[alarmGroup].U & alarmGroupConfigMask) | ((uint32)fipAction << (uint32)alarmIndex);
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();

        /* Set the KEYS to unlocks the SAC configuration registers for modification */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->KEYS.U = SAC_KEYS_PROTECTION_UNLOCK;

        /* Write alarm configuration into corresponding SAC alarm ACxAG (x=0-2) registers */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->AC0AG[alarmGroup].U = ac0agVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->AC0AG[alarmGroup].U, ac0agVal.U);
        /* #Violation: sac_hal_c_REF_3 */
        SAC->AC1AG[alarmGroup].U = ac1agVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->AC1AG[alarmGroup].U, ac1agVal.U);
        /* #Violation: sac_hal_c_REF_3 */
        SAC->AC2AG[alarmGroup].U = ac2agVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->AC2AG[alarmGroup].U, ac2agVal.U);

        /* Write alarm configuration into corresponding SAC FIPAG registers */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->FIPAG[alarmGroup].U = fipagVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->FIPAG[alarmGroup].U, fipagVal.U);

        /* Set KEYS to temporarily locks the SAC configuration registers */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->KEYS.U = SAC_KEYS_PROTECTION_LOCK;

        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
    }
    /* SAC alarm group is more than SAC_ALARMGROUP_12 */
    else
    {
        standbyGroup = (uint32)alarmGroup-SAC_STDBY_ALARM_GROUP20;
        /* #Violation: sac_hal_c_REF_3 */
        cmdstdbyReg.U = SAC_STDBY->CMDSTDBY.U;
        /* FIP is active */
        if(SAC_FIPACTION_ACTIVATE == fipAction)
        {
            cmdstdbyReg.B.STBEN = SAC_CMDSTDBY_STBEN;
            cmdstdbyReg.B.FIPEN = SAC_CMDSTDBY_FIPEN;
        }
        /* FIP is not active */
        else
        {
            cmdstdbyReg.B.STBEN = 0U;
            cmdstdbyReg.B.FIPEN = 0U;
        }
        /* #Violation: sac_hal_c_REF_3 */
        agfipstdbyVal.U = (SAC_STDBY->AGFIPSTDBY[(standbyGroup & 0x1U)].U & alarmGroupConfigMask)|
                       ((uint32)fipAction << (uint32)alarmIndex);
        /* SAC_STDBY configuration */
        /* #Violation: sac_hal_c_REF_3 */
        PWRCSTBY_SWP = PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();

        /* Write alarm configuration into corresponding SAC ASRFIPSTDBY registers */
        /* #Violation: sac_hal_c_REF_3 */
        SAC_STDBY->AGFIPSTDBY[(standbyGroup & 0x1U)].U = agfipstdbyVal.U|BIT_0_SET;
        /* Register read back check */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC_STDBY->AGFIPSTDBY[(standbyGroup & 0x1U)].U, agfipstdbyVal.U);
        /* #Violation: sac_hal_c_REF_3 */                        
        SAC_STDBY->CMDSTDBY.U = cmdstdbyReg.U|BIT_30_SET;
        /* Register read back check */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, (SAC_STDBY->CMDSTDBY.U & (~(regMaskBit))), ((cmdstdbyReg.U) & (~(regMaskBit))));
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        /* Disable access standby domain */
        /* #Violation: sac_hal_c_REF_3 */
        PWRCSTBY_SWP = PWRC_STB_DISABLE_WRITE; 
    }
    return retSts;
}


/* #Violation: sac_hal_c_REF_11 */
Sac_State Sac_Hal_GetSacState(void)
{
    uint32 curState;
    Sac_State state;

    /* Return sac state read from DBG register */
    /* #Violation: sac_hal_c_REF_3 */
    curState = (uint32)SAC->DBG.B.FSMSTS;
    /* Judge SAC current status */
    switch(curState)
    {   
        /* SAC is in start state */
        case 1U:
            state = SAC_STATE_START;
            break;
        /* SAC is in run state */
        case 2U:
            state = SAC_STATE_RUN;
            break;
        /* SAC is in run pre state */
        case 4U:
            state = SAC_STATE_RUNPRE;
            break;
        /* SAC is in fault state */
        case 8U:
            state = SAC_STATE_FAULT;
            break;
        /* SAC is in intermediate state */
        default:
            state = SAC_STATE_INTERMEDIATE;
            break;
    }
    return state;
}

/* #Violation: sac_hal_c_REF_11 */
Sac_CmdExResult Sac_Hal_ReleaseFip(void)
{
    Sac_CmdExResult result;
    Sac_State state;
    boolean retSts;
    retSts = TRUE;

    /* Get SAC state */
    state = Sac_Hal_GetSacState();

    /* SAC in START state or SAC in FAULT state and enable FAULT to RUN transition */
    if((SAC_STATE_START == state) || ((SAC_STATE_RUN == state)) ||
        /* #Violation: sac_hal_c_REF_3 */
       ((SAC_STATE_FAULT == state) && ((uint32)SAC_FAULTTORUN_ENABLED == SAC->AGC.B.EFRST)))
    {
        /* Release FIP to fault free state */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->CMD.U = (uint32)SAC_COMMAND_RELEASEFIP;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->CMD.U, SAC_COMMAND_RELEASEFIP);

        /* Command is successful */
        /* #Violation: sac_hal_c_REF_3 */
        if(0U == (uint32)SAC->STS.B.RES)
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }
        /* Command is failed */
        else
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
        /* state is FALSE */
        if(FALSE == retSts)
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    /* SAC in other status */
    else
    {
        result = SAC_CMDEXRESULT_FAILED;
    }
    return result;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_CmdExResult Sac_Hal_StandbyReleaseFip(void)
{
    Sac_CmdExResult result;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_CMDSTDBY cmdstdbyReg;
    uint32 timeOut;
    uint32 fipStatus;
    uint32 regMaskBit;
    boolean retSts;
    retSts = TRUE;
    regMaskBit = 0x40000380U;

    result = SAC_CMDEXRESULT_FAILED;
    /* #Violation: sac_hal_c_REF_3 */
    cmdstdbyReg.U = SAC_STDBY->CMDSTDBY.U;
    cmdstdbyReg.B.STBEN = SAC_CMDSTDBY_STBEN;
    cmdstdbyReg.B.FIPCTRL = SAC_CMDSTDBY_FIPCTRL_RELEASE;

    /* SAC_STDBY configuration */
    /* #Violation: sac_hal_c_REF_3 */
    PWRCSTBY_SWP = PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();

    /* Release standby FIP */
    /* #Violation: sac_hal_c_REF_3 */
    SAC_STDBY->CMDSTDBY.U = cmdstdbyReg.U|BIT_30_SET;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, (SAC_STDBY->CMDSTDBY.U & (~(regMaskBit))), ((cmdstdbyReg.U) & (~(regMaskBit))));
    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();

    /* read back to verify FIP have been released */
    timeOut = 0U;
    do
    {
        /* #Violation: sac_hal_c_REF_3 */
        fipStatus = SAC->STS.B.FIP;
        timeOut++;
    /* FIP0 is low state and timeing counting not overflow  */
    } while (((fipStatus&0x01U) == 0U) && (timeOut < SAC_CMDSTDBY_FIPCTRL_TIMEOUT));  /* Wait if FIP[0]==0 */

    cmdstdbyReg.B.FIPCTRL = SAC_CMDSTDBY_FIPCTRL_NONE;  /* Release software control */
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();

    /* #Violation: sac_hal_c_REF_3 */
    SAC_STDBY->CMDSTDBY.U = cmdstdbyReg.U|BIT_30_SET;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, (SAC_STDBY->CMDSTDBY.U & (~(regMaskBit))), ((cmdstdbyReg.U) & (~(regMaskBit))));
    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    /* Disable access standby domain */
    /* #Violation: sac_hal_c_REF_3 */
    PWRCSTBY_SWP = PWRC_STB_DISABLE_WRITE;  

    if(0U != fipStatus)
    {
        result = SAC_CMDEXRESULT_SUCCESSFUL;
    }

    if(FALSE == retSts)
    {
        result = SAC_CMDEXRESULT_FAILED;
    }
    return result;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_CmdExResult Sac_Hal_ActivateRunState(void)
{
    Sac_CmdExResult result;
    Sac_State state;
    boolean retSts;
    retSts = TRUE;

    /* Get SAC state */
    state = Sac_Hal_GetSacState();

    /* SAC in START or RUN state */
    if((SAC_STATE_START == state) || (SAC_STATE_RUN == state))
    {
        /* Switch START to RUN state */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->CMD.U = (uint32)SAC_COMMAND_START;
        /* Register read back check */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->CMD.U, (uint32)SAC_COMMAND_START);

        /* Check if command was successful */
        /* #Violation: sac_hal_c_REF_3 */
        if(0U == (uint32)SAC->STS.B.RES)
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }
        else
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    /* SAC in other state */
    else
    {
        result = SAC_CMDEXRESULT_FAILED;
    }

    if(FALSE == retSts)
    {
        result = SAC_CMDEXRESULT_FAILED;
    }
    return result;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_CmdExResult Sac_Hal_TriggerSoftwareAlarm(Sac_SoftwareAlarm swAlarmNum)
{
    Sac_CmdExResult result;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_CMD cmdVal;
    Sac_State state;
    boolean retSts;
    retSts = TRUE;

    result = SAC_CMDEXRESULT_FAILED;
    /* Get SAC state */
    state = Sac_Hal_GetSacState();
    /* SAC is in RUN or FAULT state */
    if((SAC_STATE_RUN == state) ||(SAC_STATE_FAULT == state))
    {
        cmdVal.U = 0U;
        /* Set software alarm command */
        cmdVal.B.CMD = (uint32)SAC_COMMAND_TRIGGERSOFTWAREALARM;
        /* Set software alarm number */
        cmdVal.B.ARG = (uint32)swAlarmNum;

        /* Write CMD value */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->CMD.U = cmdVal.U;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->CMD.U, cmdVal.U);
        /* Command is successful */
        /* #Violation: sac_hal_c_REF_3 */
        if(0U == (uint32)SAC->STS.B.RES)
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }

        if(FALSE == retSts)
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    return result;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_AlarmStatus Sac_Hal_GetAlarmStatus(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex alarmIndex)
{
    Sac_AlarmStatus alarmStatus;
    uint32 standbyAlarmGroup;

    /* Alarm is not triggered */
    alarmStatus = SAC_ALARMSTATUS_NOTTRIGGERED;
    /* SAC alarm group is Gorup20 or Group21 */
    if((alarmGroup == SAC_ALARMGROUP_20) || (alarmGroup == SAC_ALARMGROUP_21))
    {
        standbyAlarmGroup = (uint32)alarmGroup - SAC_STDBY_ALARM_GROUP20;
        /* Alarm state is set */
        /* #Violation: sac_hal_c_REF_3 */
        if(1U == (uint32)((SAC_STDBY->ASRSTDBY[standbyAlarmGroup].U >> (uint32)alarmIndex) & 1U))
        {
            /* Alarm is triggered */
            alarmStatus = SAC_ALARMSTATUS_TRIGGERED;
        }
    }
    /* SAC alarm group is Gorup0 ~ Group19 */
    else
    {
        /* Alarm state is set */
        /* #Violation: sac_hal_c_REF_3 */
        if(1U == (uint32)((SAC->ASR[alarmGroup].U >> (uint32)alarmIndex) & 1U))
        {
            /* Alarm is triggered */
            alarmStatus = SAC_ALARMSTATUS_TRIGGERED;
        }
    }
    return alarmStatus;
}

/* #Violation: sac_hal_c_REF_1 */
/* #Violation: sac_hal_c_REF_8 */
Sac_CmdExResult Sac_Hal_ClearAlarmStatus(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex Index)
{
    Sac_CmdExResult result;
    uint32 standbyAlarmGroup;
    uint32 regValue;
    uint32 alarmMask;
    uint32 alarmStatus;
    uint32 timeOut;
    uint32 regMaskBit;
    uint32 temptVal;
    boolean retSts;
    
    retSts = TRUE;
    regMaskBit = 0x40000380U;

    result = SAC_CMDEXRESULT_FAILED;
    alarmMask = (uint32)1U<<(uint32)Index;
    /* SAC alarm group is Gorup20 or Group21 */
    if((alarmGroup == SAC_ALARMGROUP_20) || (alarmGroup == SAC_ALARMGROUP_21))
    {
        standbyAlarmGroup = (uint32)alarmGroup-SAC_STDBY_ALARM_GROUP20;
        /* #Violation: sac_hal_c_REF_3 */
        regValue = SAC_STDBY->CMDSTDBY.U;
        /* #Violation: sac_hal_c_REF_3 */
        PWRCSTBY_SWP = PWRC_STB_ENABLE_WRITE;   /* Enable access standby domain */
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();
   
        /* BITPROT[30], ACEN[4] write 1,for compatible purpose, set BIT_9_SET and BIT_16_17_SET together */
        /* #Violation: sac_hal_c_REF_3 */
        SAC_STDBY->CMDSTDBY.U = (regValue | BIT_30_SET | BIT_4_SET | BIT_9_SET | BIT_16_17_SET);
        temptVal = (regValue | BIT_4_SET);
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, (SAC_STDBY->CMDSTDBY.U & (~(regMaskBit))), (temptVal & (~(regMaskBit))));
        /* Execute barrier instruction */
        /* #Violation: sac_hal_c_REF_7 */
        /* #Violation: sac_hal_c_REF_12 */
        /* #Violation: sac_hal_c_REF_13 */
        ASM_VOLATILE("ISB");
        /* Write 1 in ASRSTDBY bit to clear alarm */
        /* #Violation: sac_hal_c_REF_3 */
        SAC_STDBY->ASRSTDBY[standbyAlarmGroup].U = alarmMask;
        /* Execute barrier instruction */
        /* #Violation: sac_hal_c_REF_7 */
        /* #Violation: sac_hal_c_REF_12 */
        /* #Violation: sac_hal_c_REF_13 */
        ASM_VOLATILE("ISB");
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        /* Read back to verify the bits have been cleared */
        timeOut = 0U;
        do
        {
            /* #Violation: sac_hal_c_REF_3 */
            alarmStatus = SAC_STDBY->ASRSTDBY[standbyAlarmGroup].U & alarmMask;
            timeOut++;
        /* Alarm state flag not clear and timeing counting not overflow */
        } while ((alarmStatus != 0U) && (timeOut < SAC_ASR_CLEARTIMEOUT));

        /* ACEN write 0 to exit clear status */
        /* #Violation: sac_hal_c_REF_3 */
        regValue = SAC_STDBY->CMDSTDBY.U;
        regValue |= BIT_30_SET;
        regValue &= BIT_4_CLEAR;
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();

        /* #Violation: sac_hal_c_REF_3 */
        SAC_STDBY->CMDSTDBY.U = regValue;
        /* Check register readback check value meet expectation */
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, (SAC_STDBY->CMDSTDBY.U & (~(regMaskBit))), (regValue & (~(regMaskBit))));
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        /* Disable access standby domain */
        /* #Violation: sac_hal_c_REF_3 */
        PWRCSTBY_SWP = PWRC_STB_DISABLE_WRITE; 

        if(0U == alarmStatus)
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }
    }
    /* SAC alarm group is Gorup0 ~ Group19 */
    else
    {
        /* Clear alarm status */
        /* #Violation: sac_hal_c_REF_3 */
        SAC->CMD.U = (uint32)SAC_COMMAND_ALRAMSTATUSCLEAR;
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();

        /* #Violation: sac_hal_c_REF_3 */
        SAC->ASR[alarmGroup].U = alarmMask;
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        
        /* Command is successful */
        /* #Violation: sac_hal_c_REF_3 */
        if(0U == (uint32)SAC->STS.B.RES)
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }
    }
    if (FALSE == retSts)
    {
        result = SAC_CMDEXRESULT_FAILED;
    }

    return result;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_AlarmExStatus Sac_Hal_GetAlarmExecutionStatus(Sac_AlarmExecutionStatus alarmEx)
{
    Sac_AlarmExStatus alarmExStatus;
    /* Alarm execution is not set */
    /* #Violation: sac_hal_c_REF_3 */
    if(0U == (uint32)((SAC->AEX.U >> (uint32)alarmEx) & 1U))
    {
        /* No request was serviced or no alarm event missed */
        alarmExStatus = SAC_ALARMEXSTATUS_NOREQSERORNOEVENTMISSED;
    }
    /* Alarm execution is set */
    else
    {
        /* Request was serviced or at least one alarm event missed */
        alarmExStatus = SAC_ALARMEXSTATUS_REQSEROREVENTMISSED;
    }
    return alarmExStatus;
}

/* #Violation: sac_hal_c_REF_1 */
boolean Sac_Hal_ClearAlarmExecutionStatus(Sac_AlarmExecutionStatus alarmEx)
{
    boolean retSts;
    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();

    /* Clear alarm execution status */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->AEXCLR.U = (uint32)1 << (uint32)alarmEx;

    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();

    return retSts;
}

/* #Violation: sac_hal_c_REF_1 */
boolean Sac_Hal_LockConfigRegPermanently(void)
{
    boolean retSts;
    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();

    /* Lock config register permanently */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->KEYS.B.PERLCK = SAC_KEYS_PROTECTION_PERMANENTLOCK;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->KEYS.B.PERLCK, SAC_KEYS_PROTECTION_PERMANENTLOCK);
    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}

/* #Violation: sac_hal_c_REF_1 */
Sac_CmdExResult Sac_Hal_CommandExcute(Sac_Command command, uint8 argVal)
{
    Sac_CmdExResult result;
    Sac_State state;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_CMD cmdVla;
    boolean retSts;
    retSts = TRUE;
    /* #Violation: sac_hal_c_REF_3 */
    cmdVla.U = SAC->CMD.U;
    result = SAC_CMDEXRESULT_SUCCESSFUL;
    /* Get sac state */
    state = Sac_Hal_GetSacState();
    /* if command is release fip */
    if(SAC_EXECUTE_RELRASE_FIP == command)
    {
        /* Check if SAC in START state or if SAC in FAULT state and enable FAULT to RUN transition */
        /* #Violation: sac_hal_c_REF_3 */
        if(!((SAC_STATE_START == state) ||
        ((SAC_STATE_FAULT == state) && ((uint32)SAC_FAULTTORUN_ENABLED == SAC->AGC.B.EFRST))))
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    /* if command is trigger alarm */
    else if (SAC_EXECUTE_TRIG_ALARM == command)
    {
        if ((SAC_STATE_RUN != state) && (SAC_STATE_FAULT != state))
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    /* if command is alive test */
    else if ((SAC_EXECUTE_ALIVE_TEST == command))
    {
        if(SAC_STATE_START != state)
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }
    else
    {
        /* Do nothing */
    }
    /* if result is successful */
    if(result == SAC_CMDEXRESULT_SUCCESSFUL)
    {
        cmdVla.B.CMD = (uint8)command;
        cmdVla.B.ARG = argVal;
        /* #Violation: sac_hal_c_REF_3 */
        SAC->CMD.U = cmdVla.U;
        /* #Violation: sac_hal_c_REF_3 */
        retSts = Sac_Register_ReadBack_Check(retSts, SAC->CMD.U, cmdVla.U);
        /* Check if command was successful */
        /* #Violation: sac_hal_c_REF_3 */
        if((0U == (uint32)SAC->STS.B.RES) && (TRUE == retSts))
        {
            result = SAC_CMDEXRESULT_SUCCESSFUL;
        }
        else
        {
            result = SAC_CMDEXRESULT_FAILED;
        }
    }

    return result;
}

/* #Violation: sac_hal_c_REF_1 */
boolean Sac_Hal_SetPesAction(const Sac_PesConfig *const pPesConfig)
{
    boolean retSts;
    retSts = TRUE;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_FIP fipVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_PCTL pctlVal;
    /* #Violation: sac_hal_c_REF_2 */
    SAC_AGC agcVal;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the configure parameter pointer is null pointer */
    /* #Violation: sac_hal_c_REF_14 */
    Assert((boolean)(NULL_PTR != pPesConfig));
    /* #Violation: sac_hal_c_REF_14 */
    Assert((boolean)((0x40U) > pPesConfig->innerTrigCfg));
#endif
    /* Read FIP value */
    /* #Violation: sac_hal_c_REF_3 */
    fipVal.U = SAC->FIP.U;
    /* Read PCTL value */
    /* #Violation: sac_hal_c_REF_3 */
    pctlVal.U = SAC->PCTL.U;
    /* Read AGC value */
    /* #Violation: sac_hal_c_REF_3 */
    agcVal.U = SAC->AGC.U;
    /* En/Disable FIP0 trigger PES */
    fipVal.B.PES = pPesConfig->fip0TrigEn;
    /* En/Disabel FIP0 filter and then send to PES */
    pctlVal.B.GFPES_EN = pPesConfig->fip0Filter;
    /* Inner SAC post action trigger PES configuration */
    agcVal.B.PES = pPesConfig->innerTrigCfg;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();

    /* Set the value (0x00BC) of the KEYS to unlocks the SAC configuration registers for modification */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->KEYS.U = (uint32)(SAC_KEYS_PROTECTION_UNLOCK);
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->KEYS.U, (uint32)(SAC_KEYS_PROTECTION_UNLOCK));

    /* Write FIP value */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->FIP.U = fipVal.U;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->FIP.U, fipVal.U);

    /* Write AGC value */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->AGC.U = agcVal.U;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->AGC.U, agcVal.U);

    /* Write PCTL value */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->PCTL.U = pctlVal.U;
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->PCTL.U, pctlVal.U);

    /* Set the value (0x0000) of the KEYS to temporarily locks the SAC configuration registers */
    /* #Violation: sac_hal_c_REF_3 */
    SAC->KEYS.U = (uint32)(SAC_KEYS_PROTECTION_LOCK);
    /* Check register readback check value meet expectation */
    /* #Violation: sac_hal_c_REF_3 */
    retSts = Sac_Register_ReadBack_Check(retSts, SAC->KEYS.U, (uint32)(SAC_KEYS_PROTECTION_LOCK));

    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();        

    return  retSts;
}



#define SAC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: sac_hal_c_REF_10 */
#include "Sac_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
