[!NOCODE!][!//

[!AUTOSPACING!]
[!CODE!][!//
/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Icu_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TIM
*
*   brief                 : This file contains all post-build parameters in ICU Driver
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
*#Icu_PBcfg_c_REF_1:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Icu_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
* 
*#Icu_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!ENDCODE!][!//
[!NOCODE!][!//
[!INCLUDE "Icu_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!CODE!][!//
/* \[SWS_Icu_00247]*/
/* \[SWS_Icu_00254]*/
#include "Icu.h"

/* \[SWS_Icu_00214] [SWS_Icu_00348] [SWS_Icu_00044] [SWS_Icu_00215][SWS_Icu_00349]
 * Declare the notification functions */
[!ENDCODE!][!//
[!LOOP "IcuConfigSet/IcuChannel/*"!][!//
[!IF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//
[!IF "(node:exists(./IcuSignalEdgeDetection/IcuSignalNotification))and((./IcuSignalEdgeDetection/IcuSignalNotification)!="NULL_PTR")"!][!//
[!CODE!][!//
extern void [!"./IcuSignalEdgeDetection/IcuSignalNotification"!](void);[!//
[!ENDCODE!][!//
[!CR!][!//
[!ENDIF!][!//
[!ELSEIF "IcuMeasurementMode= 'ICU_MODE_TIMESTAMP'"!][!//
[!IF "(node:exists(./IcuTimestampMeasurement/IcuTimestampNotification))and((./IcuTimestampMeasurement/IcuTimestampNotification)!="NULL_PTR")"!][!//
[!CODE!][!//
extern void [!"./IcuTimestampMeasurement/IcuTimestampNotification"!](void);[!//
[!ENDCODE!][!//
[!CR!][!//
[!ENDIF!][!//
[!ELSEIF "IcuMeasurementMode= 'ICU_MODE_EDGE_COUNTER'"!][!//
[!IF "(node:exists(./IcuEdgeCounterMeasurement/IcuTimerOverflowNotification))and((./IcuEdgeCounterMeasurement/IcuTimerOverflowNotification)!="NULL_PTR")"!][!//
[!CODE!][!//
extern void [!"./IcuEdgeCounterMeasurement/IcuTimerOverflowNotification"!](void);[!//
[!ENDCODE!][!//
[!CR!][!//
[!ENDIF!][!//
[!ELSE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//



[!VAR "ReportWakeupSource" = "IcuGeneral/IcuReportWakeupSource"!][!//
[!VAR "MaxChannels"= "num:i(count(IcuConfigSet/IcuChannel/*))"!][!//
[!VAR "TimeStampRam"="0"!][!//
[!VAR "SignalMeasurementRam"="0"!][!//
[!VAR "TioSignalMeasurementRam"="0"!][!//
[!VAR "EdgeCountRam"="0"!][!//
[!VAR "TimChMax"="0"!][!//
[!VAR "TioChMax"="0"!][!//

[!//

[!LOOP "IcuConfigSet/IcuChannel/*"!][!//
[!IF "$MaxChannels <= ./IcuChannelId"!][!//
    [!ERROR!][!//
        [122-00-02-ERROR]: IcuChannelId ([!"./IcuChannelId"!]) is larger than configured number of channels ([!"$MaxChannels"!]).
    [!ENDERROR!][!//
[!ENDIF!][!//

[!IF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//
[!ELSEIF "IcuMeasurementMode= 'ICU_MODE_TIMESTAMP'"!][!//
  [!VAR "TimeStampRam" = "$TimeStampRam+1"!][!//
[!ELSEIF "IcuMeasurementMode= 'ICU_MODE_EDGE_COUNTER'"!][!//
  [!VAR "EdgeCountRam" = "$EdgeCountRam+1"!][!//
[!ELSE!][!//
    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTimChannel)"!][!//
    [!VAR "SignalMeasurementRam" = "$SignalMeasurementRam+1"!][!//
    [!ENDIF!][!//
    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTioChannel)"!][!//
    [!VAR "TioSignalMeasurementRam" = "$TioSignalMeasurementRam+1"!][!//
    [!ENDIF!][!//

[!ENDIF!][!//

    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTimChannel)"!][!//
    [!VAR "TimChMax" = "$TimChMax+1"!][!//
    [!ENDIF!][!//
    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTioChannel)"!][!//
    [!VAR "TioChMax" = "$TioChMax+1"!][!//
    [!ENDIF!][!//

[!ENDLOOP!][!//

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!VAR "EdgecountIndex"="00"!][!//
[!VAR "TimeStampIndex"="00"!][!//
[!VAR "SignalMeasurementIndex"="00"!][!//
[!VAR "SignalMeasurementTioIndex"="00"!][!//

[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!INDENT "0"!][!//
[!IF "$CoreIndex = '0'"!][!//
[!VAR "CoreUsedForIcuChFlg" = "num:i($IcuChannelMappedCore0)"!][!//
[!ELSEIF "$CoreIndex = '1'"!][!//
[!VAR "CoreUsedForIcuChFlg" = "num:i($IcuChannelMappedCore1)"!][!//
[!ELSEIF "$CoreIndex = '2'"!][!//
[!VAR "CoreUsedForIcuChFlg" = "num:i($IcuChannelMappedCore2)"!][!//
[!ELSEIF "$CoreIndex = '3'"!][!//
[!VAR "CoreUsedForIcuChFlg" = "num:i($IcuChannelMappedCore3)"!][!//
[!ELSEIF "$CoreIndex = '4'"!][!//
[!VAR "CoreUsedForIcuChFlg" = "num:i($IcuChannelMappedCore4)"!][!//
[!ENDIF!][!//
[!IF "num:i($CoreUsedForIcuChFlg) != '0'"!][!//
[!CODE!][!//

/* Icu Channel(s) configuration informations which mapped to Core[!"$CoreIndex"!] */
/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"
[!ENDCODE!][!//


[!SELECT "as:modconf('Icu')[1]/IcuConfigSet/IcuChannel"!][!//
[!LOOP "node:order(./*, 'IcuChannelId')"!][!//


[!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
[!IF "num:i($IcuchannelMappedCoreId) = $CoreIndex"!][!//
[!VAR "TimChFilterTimeForFallingEdgeValue" ="node:value(./TimChannelFilterConfig/TimChFilterTimeForFallingEdge)"!][!//
[!VAR "TimChFilterTimeForRisingEdgeValue" ="node:value(./TimChannelFilterConfig/TimChFilterTimeForRisingEdge)"!][!//
[!VAR "TimChannelFilterEnableValue" ="node:value(./TimChannelFilterConfig/TimChannelFilterEnable)"!][!//
[!VAR "temp1" ="node:value(./TimChannelFilterConfig/TimChFilterCounterFreqSelect)"!][!//
[!VAR "TimChFilterCounterFreqSelectValue" = "concat('GTM_',$temp1)"!][!//
[!VAR "temp1" ="node:value(./TimChannelFilterConfig/TimChFilterModeForRisingEdge)"!][!//
[!VAR "TimChFilterModeForRisingEdgeValue" = "concat('GTM_',$temp1)"!][!//
[!VAR "temp1" ="node:value(./TimChannelFilterConfig/TimChFilterModeForFallingEdge)"!][!//
[!VAR "TimChFilterModeForFallingEdgeValue" = "concat('GTM_',$temp1)"!][!//
[!IF "$TimChannelFilterEnableValue = 'true'"!][!//

[!CODE!][!//
static const Gtm_Icu_ConfigFilter Icu_ConfigFilterCore[!"$CoreIndex"!]Ch[!"IcuChannelId"!] = 
{
    [!INDENT "4"!][!//
    /* FilterCounterFreqSelect */
    [!"$TimChFilterCounterFreqSelectValue"!],[!//

    /* FilterModeForRisingEdge */
    [!"$TimChFilterModeForRisingEdgeValue"!],[!//

    /* FilterModeForFallingEdge */
    [!"$TimChFilterModeForFallingEdgeValue"!],[!//

    /* FilterTimeForRisingEdge */
    [!"num:i($TimChFilterTimeForRisingEdgeValue)"!]U,[!//

    /* FilterTimeForFallingEdge */
    [!"num:i($TimChFilterTimeForFallingEdgeValue)"!]U[!//
    [!ENDINDENT!][!//

};
[!ENDCODE!][!//



[!ENDIF!][!//


[!ENDIF!][!//

[!ENDLOOP!][!//
[!ENDSELECT!][!//

[!IF "$TimChMax >0 "!][!//


[!CALL "AuxCheck"!][!//



[!CODE!][!//
static const Gtm_Icu_Config Icu_ConfigCore[!"$CoreIndex"!][]=
{
[!ENDCODE!][!//


[!SELECT "as:modconf('Icu')[1]/IcuConfigSet/IcuChannel"!][!//
[!LOOP "node:order(./*, 'IcuChannelId')"!][!//

[!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
[!IF "num:i($IcuchannelMappedCoreId) = $CoreIndex"!][!//

    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTimChannel)"!][!//


    [!IF "./IcuDefaultStartEdge= 'ICU_RISING_EDGE'"!][!//
        [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_RISE'"!][!//
    [!ELSEIF "./IcuDefaultStartEdge= 'ICU_BOTH_EDGES'"!][!//
        [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_BOTH'"!][!//
    [!ELSE!][!//
        [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_FALL'"!][!//
    [!ENDIF!][!//

    [!VAR "RefChannel" = "./IcuChannelInputSelection"!][!//
    [!VAR "Unit" = "node:ref($RefChannel)/ModuleId"!][!//
    [!VAR "TimerNumber" = "node:ref($RefChannel)/ChannelId"!][!//

    [!CALL "GetIntcInfo", "HwName"="'Gtm0Tim'","ClusterId" = "$Unit","ChId" = "$TimerNumber","Mode" = "'LEVEL'"!][!//

    [!INDENT "4"!][!//
    [!CODE!][!//
    /* [!"@name"!] */
    {
    [!ENDCODE!][!//
    [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        [!VAR "Interrupt" = "1"!][!//
        [!VAR "InterruptType" = "'NewValue'"!][!//
        [!IF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_MEASUREMENT'"!][!//
            [!VAR "Interrupt" = "4"!][!//
            [!VAR "InterruptType" = "'Cnt OverFlow'"!][!//
            [!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_HIGH_TIME'"!][!//
            [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_FALL'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_LOW_TIME'"!][!//
               [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_RISE'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_PERIOD_TIME'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_DUTY_CYCLE'"!][!//
            [!ELSE!][!//
            [!ENDIF!][!//

        [!ELSEIF "IcuMeasurementMode= 'ICU_MODE_EDGE_COUNTER'"!][!//
            [!VAR "Interrupt" = "4"!][!//
            [!VAR "InterruptType" = "'Cnt OverFlow'"!][!//
        [!ELSE!][!//
        [!ENDIF!][!//
        [!INDENT "8"!][!//
        [!CODE!][!//
            /* IcuMeasurementMode */
            (Gtm_Icu_Mode)[!"IcuMeasurementMode"!],[!//

            /* Clock */
            [!IF "./IcuGtmSmuClkSrc= 'CMU_CLK0'"!][!//
            GTM_CMU_CLK_0,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK1'"!][!//
            GTM_CMU_CLK_1,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK2'"!][!//
            GTM_CMU_CLK_2, 
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK3'"!][!//
            GTM_CMU_CLK_3, 
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK4'"!][!//
            GTM_CMU_CLK_4,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK5'"!][!//
            GTM_CMU_CLK_5,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK6'"!][!//
            GTM_CMU_CLK_6,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK7'"!][!//
            GTM_CMU_CLK_7,
            [!ENDIF!][!//
            /*input*/    
            [!IF "./TimChannelInputSelect= 'INPUT_OF_CURRENT_TIM_CHANNEL'"!][!//
            GTM_TIM_INPUT_CURRENTCHANNEL,
            [!ELSEIF "./TimChannelInputSelect= 'INPUT_OF_PREVIOUS_TIM_CHANNEL'"!][!//
            GTM_TIM_INPUT_ADJACENTCHANNEL,
            [!ELSE!][!//
            GTM_TIM_INPUT_AUX,
            [!ENDIF!][!//
            /*edge*/        
            [!"$EdgeValue"!],[!//
            
            [!VAR "TimChannelFilterEnableValue" ="node:value(./TimChannelFilterConfig/TimChannelFilterEnable)"!][!//
            /*Filter*/
            [!IF "$TimChannelFilterEnableValue = 'false'"!][!//
            NULL_PTR,
            [!ELSE!][!//
            &Icu_ConfigFilterCore[!"$CoreIndex"!]Ch[!"IcuChannelId"!],
            [!ENDIF!][!//
            /*ctrlMethodSetPtr*/
            NULL_PTR,
            /* Enables resetting of counter in certain modes */
            [!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_HIGH_TIME' or IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_LOW_TIME'"!][!//
            TRUE,
            [!ELSE!][!//
            FALSE,
            [!ENDIF!][!//
            /* Interrupt */
            {
                [!INDENT "12"!][!//
                [!"num:i($Interrupt)"!]U,/* [!"$InterruptType"!] */
                GTM_IRQMODE_[!"$Mode"!]
                [!ENDINDENT!][!//
            },
            FALSE,
            [!IF "./TimChannelInputSelect= 'INPUT_OF_CURRENT_TIM_CHANNEL'"!][!//
            /*AuxInConfig*/
            {
                [!INDENT "12"!][!//
                /* IsChIndexBiggerThan7 */
                [!"$ChState"!],
                FALSE,
                FALSE,
                [!ENDINDENT!][!//
            },
            [!ELSEIF "./TimChannelInputSelect= 'INPUT_OF_PREVIOUS_TIM_CHANNEL'"!][!//
            /* AuxInConfig */
            {
                [!INDENT "12"!][!//
                /*IsChIndexBiggerThan7*/
                [!"$ChState"!],
                FALSE,
                FALSE,
                [!ENDINDENT!][!//
            },
            [!ELSE!][!//
            /*AuxInConfig*/
            {
                [!INDENT "12"!][!//
                /*IsChIndexBiggerThan7*/
                [!"$ChState"!],
                /*IsTOM*/
                [!IF "contains(./AuxInSource, 'ATOM')"!][!//
                FALSE,
                [!ELSE!][!//
                TRUE,
                [!ENDIF!][!//
                /*IsNegtive*/
                [!IF "contains(./AuxInSource, 'N')"!][!//
                TRUE,
                [!ELSE!][!//
                FALSE,
                [!ENDIF!][!//
                [!ENDINDENT!][!//
            }
            [!ENDIF!][!//
        [!ENDCODE!][!//
            [!ENDINDENT!][!//


        [!ENDINDENT!][!//
    [!INDENT "4"!][!//
    [!CODE!][!//
    },

    [!ENDCODE!][!//
    [!ENDINDENT!][!//

    [!ENDIF!][!//

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!CODE!][!//
};

[!ENDCODE!][!//
[!ENDIF!][!// $TimChMax >0



[!IF "$TioChMax >0 "!][!//
[!CODE!][!//
static const Gtm_Icu_Tio_Config Icu_Tio_ConfigCore[!"$CoreIndex"!][]=
{
[!ENDCODE!][!//

[!SELECT "as:modconf('Icu')[1]/IcuConfigSet/IcuChannel"!][!//
[!LOOP "node:order(./*, 'IcuChannelId')"!][!//

[!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
[!IF "num:i($IcuchannelMappedCoreId) = $CoreIndex"!][!//
    [!VAR "SFE" = "'FALSE'"!][!//
    [!VAR "SRE" = "'TRUE'"!][!//
    [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTioChannel)"!][!//
    [!IF "./IcuDefaultStartEdge= 'ICU_RISING_EDGE'"!][!//
        [!VAR "EdgeValue" = "'GTM_ICU_TIO_EDGE_RISE'"!][!//
    [!ELSEIF "./IcuDefaultStartEdge= 'ICU_BOTH_EDGES'"!][!//
        [!VAR "EdgeValue" = "'GTM_ICU_TIO_EDGE_BOTH'"!][!//
    [!ELSE!][!//
        [!VAR "EdgeValue" = "'GTM_ICU_TIO_EDGE_FALL'"!][!//
        [!VAR "SFE" = "'TRUE'"!][!//
        [!VAR "SRE" = "'FALSE'"!][!//        
    [!ENDIF!][!//

    [!VAR "RefChannel" = "./IcuChannelInputSelection"!][!//
    [!VAR "Unit" = "node:ref($RefChannel)/TioId"!][!//
    [!VAR "TimerNumber" = "node:ref($RefChannel)/ChannelId"!][!//

    [!CALL "GetIntcInfo", "HwName"="'Gtm0Tio'","ClusterId" = "$Unit","ChId" = "$TimerNumber","Mode" = "'LEVEL'"!][!//

    [!INDENT "4"!][!//
    [!CODE!][!//
    /* Core[!"$CoreIndex"!]Ch[!"num:i(./IcuChannelId)"!] */
    {
    [!ENDCODE!][!//
    [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        [!IF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_MEASUREMENT'"!][!//
            [!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_HIGH_TIME'"!][!//
            [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_RISE'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_LOW_TIME'"!][!//
               [!VAR "EdgeValue" = "'GTM_TIM_EDGE_CAP_FALL'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_PERIOD_TIME'"!][!//
            [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_DUTY_CYCLE'"!][!//
            [!ELSE!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
        [!ENDIF!][!//
        [!INDENT "8"!][!//
        [!CODE!][!//
            /* IcuMeasurementMode */
            [!IF "contains(./IcuMeasurementMode, 'EDGE_COUNTER')"!][!//
            GTM_ICU_TIO_MODE_EDGE_COUNTER,
            [!ELSEIF "contains(./IcuMeasurementMode, 'EDGE_DETECT')"!][!//
            GTM_ICU_TIO_MODE_SIGNAL_EDGE_DETECT,
            [!ELSEIF "contains(./IcuMeasurementMode, 'TIMESTAMP')"!][!//
            GTM_ICU_TIO_MODE_TIMESTAMP,
            [!ELSE!][!//
            GTM_ICU_TIO_MODE_SIGNAL_MEASUREMENT,
            [!ENDIF!][!//

            /* Clock */
            [!IF "./IcuGtmSmuClkSrc= 'CMU_CLK0'"!][!//
            GTM_TIO_UPDATE_SRC_CLK0,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK1'"!][!//
            GTM_TIO_UPDATE_SRC_CLK1,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK2'"!][!//
            GTM_TIO_UPDATE_SRC_CLK2, 
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK3'"!][!//
            GTM_TIO_UPDATE_SRC_CLK3, 
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK4'"!][!//
            GTM_TIO_UPDATE_SRC_CLK4,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK5'"!][!//
            GTM_TIO_UPDATE_SRC_CLK5,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK6'"!][!//
            GTM_TIO_UPDATE_SRC_CLK6,
            [!ELSEIF "./IcuGtmSmuClkSrc= 'CMU_CLK7'"!][!//
            GTM_TIO_UPDATE_SRC_CLK7,
            [!ENDIF!][!//

            /*edge*/        
            [!"$EdgeValue"!],[!//
            
            [!VAR "TimChannelFilterEnableValue" ="node:value(./TimChannelFilterConfig/TimChannelFilterEnable)"!][!//
            /* Select Source Of Capture */
            GTM_TIO_COMPARE_SRC_RSTB0,
            /* Interrupt */
            {
                [!INDENT "12"!][!//
                GTM_IRQMODE_[!"$Mode"!],
                [!"$SRE"!],
                [!"$SFE"!],
                [!ENDINDENT!][!//
            },
            FALSE
        [!ENDCODE!][!//
            [!ENDINDENT!][!//


        [!ENDINDENT!][!//
    [!INDENT "4"!][!//
    [!CODE!][!//
    },

    [!ENDCODE!][!//
    [!ENDINDENT!][!//

    [!ENDIF!][!//

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!CODE!][!//
};

[!ENDCODE!][!//
[!ENDIF!][!// $TioChMax >0


[!CODE!][!//
static const Icu_ChnConfigType Icu_ChannelConfigCore[!"$CoreIndex"!][ICU_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]]=
{
[!ENDCODE!][!//
    [!VAR "nTim"="0"!][!//
    [!VAR "nTio"="0"!][!//
    [!VAR "Unit"="00"!][!//
    [!VAR "TimerNumber"="0000"!][!//
    [!VAR "ChannelType"="02"!][!//
    [!SELECT "as:modconf('Icu')[1]/IcuConfigSet/IcuChannel"!][!//
    [!LOOP "node:order(./*, 'IcuChannelId')"!][!//

    [!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
    [!IF "num:i($IcuchannelMappedCoreId) = $CoreIndex"!][!//

    [!INDENT "4"!][!//
    [!CODE!][!//
    /* ICU Channel [!"IcuChannelId"!] */
    {
    [!ENDCODE!][!//
    [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        [!CODE!][!//
        [!"IcuChannelId"!]U,
[!INDENT "0"!][!//
[!ENDINDENT!][!//
        [!ENDCODE!][!//
        [!ENDINDENT!][!//
        [!INDENT "8"!][!//
          [!CODE!][!//
        /* Notification function pointer */
        [!ENDCODE!][!//
        [!IF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//
        [!IF "(node:exists(./IcuSignalEdgeDetection/IcuSignalNotification))and((./IcuSignalEdgeDetection/IcuSignalNotification)!="NULL_PTR")"!][!//
        [!CODE!][!//
        &[!"./IcuSignalEdgeDetection/IcuSignalNotification"!],[!//
        [!ENDCODE!][!//
        [!CR!][!//
        [!ELSE!][!//
        [!CODE!][!//
        NULL_PTR,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!ELSEIF "IcuMeasurementMode= 'ICU_MODE_TIMESTAMP'"!][!//
        [!IF "(node:exists(./IcuTimestampMeasurement/IcuTimestampNotification))and((./IcuTimestampMeasurement/IcuTimestampNotification)!="NULL_PTR")"!][!//
        [!CODE!][!//
        &[!"./IcuTimestampMeasurement/IcuTimestampNotification"!],[!//
        [!ENDCODE!][!//
        [!CR!][!//
        [!ELSE!][!//
        [!CODE!][!//
        NULL_PTR,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!ELSEIF "IcuMeasurementMode= 'ICU_MODE_EDGE_COUNTER'"!][!//
        [!CODE!][!//
        NULL_PTR,
        [!ENDCODE!][!//
        [!ELSE!][!//
        [!CODE!][!//
        NULL_PTR,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!ENDINDENT!][!//
        [!INDENT "0"!][!//
[!CODE!][!//
[!ENDCODE!][!//
        [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        
        [!VAR "RefChannel" = "./IcuChannelInputSelection"!][!//
        [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTimChannel)"!][!//
        [!VAR "Unit" = "node:ref($RefChannel)/ModuleId"!][!//
        [!VAR "TimerNumber" = "node:ref($RefChannel)/ChannelId"!][!//
        [!ELSE!]    
        [!VAR "Unit" = "node:ref($RefChannel)/TioId"!][!//
        [!VAR "TimerNumber" = "node:ref($RefChannel)/ChannelId"!][!//
        [!ENDIF!]


        [!CODE!][!//
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_[!"num:i($Unit)"!],
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_[!"num:i($TimerNumber)"!],
        [!ENDCODE!][!//
        [!CODE!][!//
        /* ChannelProperties */        
        [!IF "IcuMeasurementMode= 'ICU_MODE_TIMESTAMP'"!][!//
        [!IF "./IcuTimestampMeasurement/IcuTimestampMeasurementProperty= 'ICU_CIRCULAR_BUFFER'"!][!//
        (uint8)ICU_CIRCULAR_BUFFER,
        [!ELSE!][!//
        (uint8)ICU_LINEAR_BUFFER, 
        [!ENDIF!][!//
        [!ELSEIF "IcuMeasurementMode= 'ICU_MODE_SIGNAL_MEASUREMENT'"!][!//
        [!IF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_HIGH_TIME'"!][!//
        ICU_MEASUREMENT_PRO_HIGH_TIME, 
        [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_LOW_TIME'"!][!//
        ICU_MEASUREMENT_PRO_LOW_TIME,
        [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_PERIOD_TIME'"!][!//
        ICU_MEASUREMENT_PRO_PERIOD,
        [!ELSEIF "IcuSignalMeasurement/IcuSignalMeasurementProperty= 'ICU_DUTY_CYCLE'"!][!//
        ICU_MEASUREMENT_PRO_DUTY_CYCLE,
        [!ELSE!][!//
        0x00,
        [!ENDIF!][!//
        [!ELSEIF "IcuMeasurementMode= 'ICU_MODE_EDGE_COUNTER'"!][!//
        0x00,
        [!ELSE!][!//
        0x00,
        [!ENDIF!][!//
        /* Tim_ConfigPtr */
        [!IF "node:exists(node:ref(./IcuChannelInputSelection)/GtmTimChannel)"!][!//
        &Icu_ConfigCore[!"$CoreIndex"!][[!"num:i($nTim)"!]],
        [!NOCODE!][!//
        [!VAR "nTim"="$nTim+1"!][!//
        [!ENDNOCODE!][!//
        [!ELSE!][!//
        NULL_PTR,
        [!ENDIF!][!//
        [!NOCODE!][!//
        [!VAR "WakeupValue" = "'FALSE'"!][!//
        [!VAR "WakeupComment" = "'Not applicable'"!][!//
        [!VAR "WakeupReason" = "num:i(0)"!][!//
        [!IF "IcuMeasurementMode = 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//  
        [!VAR "Wakeup" = "./IcuWakeupCapability"!][!//
        [!IF "$Wakeup = 'true'"!][!//
            [!VAR "WakeupValue" = "'TRUE'"!][!//
        [!ENDIF!][!//
        [!VAR "Wakeupreference" = "''"!][!//
        [!IF "$Wakeup = 'true'"!][!//
            [!IF "node:exists(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1]) = 'true' and $ReportWakeupSource = 'true'"!][!//         
            [!VAR "Wakeupreference" = "node:name(node:ref(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1]))"!][!//
            [!VAR "WakeupComment" = "concat('WakeupSourceId Value for Channel ',num:i(IcuChannelId))"!][!//
            [!ELSEIF "$ReportWakeupSource = 'true'"!][!//

            [!ENDIF!][!//        
        [!ENDIF!][!//
        [!IF "string-length($Wakeupreference) > 0 and $ReportWakeupSource = 'true'"!][!//
            [!VAR "WakeupReason" = "node:ref(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1])/EcuMWakeupSourceId"!][!//
        [!ENDIF!][!//   
        [!ENDIF!][!//
        [!ENDNOCODE!][!//        
        /* IsWakeupChannel */
        [!"$WakeupValue"!],
        /* WakeupSourceCfgInfo */
        [!"$WakeupReason"!]U,/*[!"$WakeupComment"!]*/
        [!ENDCODE!][!//
        [!ENDINDENT!][!//
        [!INDENT "4"!][!//
        [!CODE!][!//
    },
    [!ENDCODE!][!//
    [!ENDINDENT!][!//


    [!ENDIF!][!//

    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!//
[!CODE!][!//
};
[!ENDCODE!][!//


[!CODE!][!//

static const Icu_ChannelConfigType Icu_ChannelConfigSetCore[!"$CoreIndex"!][] =
{
[!ENDCODE!][!//
    [!INDENT "4"!][!//
    [!CODE!][!//
    {
    [!ENDCODE!][!//
    [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        [!CODE!][!//
        /* Icu_ChnConfigType */
        &Icu_ChannelConfigCore[!"$CoreIndex"!][0],
        [!ENDCODE!][!//
        [!ENDINDENT!][!//
    [!INDENT "4"!][!//
    [!CODE!][!//
    }
    [!ENDCODE!][!//
    [!ENDINDENT!][!//

[!CODE!][!//
};
[!ENDCODE!][!//
[!CODE!][!//

/* Icu channel number and configuration information in Core[!"$CoreIndex"!] */
static const Icu_CoreConfigType Icu_CoreConfigCore[!"$CoreIndex"!] =
{
    [!INDENT "4"!][!//
    /* Maximum number of the channels allocated to the core[!"$CoreIndex"!] */
    ICU_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!],
    /* Icu configuration information of core[!"$CoreIndex"!] */
    &Icu_ChannelConfigSetCore[!"$CoreIndex"!][0]
    [!ENDINDENT!][!//
};

/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"
[!ENDCODE!][!//

[!ENDIF!][!//
[!ENDINDENT!][!//


[!ENDFOR!][!//

[!INDENT "0"!][!//
[!CODE!][!//

/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"

/* 
This array is used for mapping Icu Channel to the Core. 
Array index is Icu channel -> array member is index of Icu_ChannelConfigSetCorex[x=0~4]
*/
static const Icu_MappingType Icu_ChannelToCoreMap[ICU_TOTAL_CHANNEL_NUMBER] =
{
    /* Index, executionCore */
[!ENDCODE!][!//
    [!INDENT "4"!][!//
    [!VAR "Channel2Core0Num" = "0"!][!//
    [!VAR "Channel2Core1Num" = "0"!][!//
    [!VAR "Channel2Core2Num" = "0"!][!//
    [!VAR "Channel2Core3Num" = "0"!][!//
    [!VAR "Channel2Core4Num" = "0"!][!//
    [!VAR "x" = "0"!][!//
    [!VAR "TotalChannelNum" = "num:i(count(IcuConfigSet/IcuChannel/*))"!][!//
    [!FOR "IcuChannelIndex" = "0" TO "num:i($TotalChannelNum - 1)"!][!//
    [!LOOP "IcuConfigSet/IcuChannel/*"!][!//
    [!IF "IcuChannelId = $IcuChannelIndex"!][!//
    [!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
    [!IF "$IcuchannelMappedCoreId = num:i(0)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core0Num)"!][!//
    [!VAR "Channel2Core0Num" = "$Channel2Core0Num + 1"!][!//
    [!ELSEIF "$IcuchannelMappedCoreId = num:i(1)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core1Num)"!][!//
    [!VAR "Channel2Core1Num" = "$Channel2Core1Num + 1"!][!//
    [!ELSEIF "$IcuchannelMappedCoreId = num:i(2)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core2Num)"!][!//
    [!VAR "Channel2Core2Num" = "$Channel2Core2Num + 1"!][!//
    [!ELSEIF "$IcuchannelMappedCoreId = num:i(3)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core3Num)"!][!//
    [!VAR "Channel2Core3Num" = "$Channel2Core3Num + 1"!][!//
    [!ELSEIF "$IcuchannelMappedCoreId = num:i(4)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core4Num)"!][!//
    [!VAR "Channel2Core4Num" = "$Channel2Core4Num + 1"!][!//
    [!ENDIF!][!//
[!CODE!][!//
    /* [!"@name"!] */
    {[!"num:i($Channel2CoreNumIndex)"!]U, MULTICOREID_CPU[!"$IcuchannelMappedCoreId"!]}[!IF "$x != num:i($TotalChannelNum - 1)"!],[!ENDIF!]

[!ENDCODE!][!//
    [!VAR "x" = "$x+1"!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
[!CODE!][!//
};
[!ENDCODE!][!//
[!ENDINDENT!][!//


[!INDENT "0"!][!//
[!CODE!][!//

/* Mapping the hardware channel(GTM-TIM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel id */
/* #Violation: Icu_PBcfg_c_REF_1 */
static const uint8 Icu_HwTimChannelMap[[!"num:i(ecu:get('Gtm.NumberOfTimChannels') * ecu:get('Gtm.NumberOfTimChannels'))"!]U] =
{
[!VAR "LastChannel" = "concat(num:i(ecu:get('Gtm.NumberOfTimChannels') - 1), num:i(ecu:get('Gtm.NumberOfTimChannels') - 1))"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
  [!FOR "ChIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
      [!VAR "CurrentHwChannel" = "concat($ModeleIndex, $ChIndex)"!][!//
      [!LOOP "node:order(IcuConfigSet/IcuChannel/*, 'IcuChannelId')"!][!//
        [!VAR "LogicChannelId" = "'0xFF'"!][!//
          [!VAR "RefChannel" = "./IcuChannelInputSelection"!][!//
          [!VAR "Unit" = "node:ref($RefChannel)/ModuleId"!][!//
          [!VAR "TimerNumber" = "node:ref($RefChannel)/ChannelId"!][!//
          [!VAR "LogicHwChannel" = "concat($Unit, $TimerNumber)"!][!//
          [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
            [!VAR "LogicChannelId" = "./IcuChannelId"!][!//
            [!BREAK!]
          [!ENDIF!][!//
      [!ENDLOOP!][!//
        [!INDENT "4"!][!//
      /* TIM[!"$ModeleIndex"!]_CH[!"$ChIndex"!] */
      [!IF "$CurrentHwChannel != $LastChannel"!][!//
      [!"$LogicChannelId"!]U,
      [!ELSE!]
      [!"$LogicChannelId"!]U
      [!ENDIF!][!//
      [!ENDINDENT!][!//
  [!ENDFOR!][!//
[!ENDFOR!][!//
};

/* Configuration parameters */
/* #Violation: Icu_PBcfg_c_REF_2*/
[!IF "variant:name() != ''"!][!//
const Icu_ConfigType Icu_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Icu_ConfigType Icu_ConfigSet[1U] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /* Pointer to Core Configuration structure */
    [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
      [!IF "$CoreId = num:i(0)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($IcuChannelMappedCore0)"!][!//
      [!ELSEIF "$CoreId = num:i(1)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($IcuChannelMappedCore1)"!][!//
      [!ELSEIF "$CoreId = num:i(2)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($IcuChannelMappedCore2)"!][!//
      [!ELSEIF "$CoreId = num:i(3)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($IcuChannelMappedCore3)"!][!//
      [!ENDIF!][!//
    [!IF "num:i($CoreUsedForEthHwUnitFlg) != num:i(0)"!][!//
            /* configuration information of core[!"num:i($CoreId)"!] */
            &Icu_CoreConfigCore[!"num:i($CoreId)"!][!//
    [!ELSE!][!//
            /* No configuration information for core[!"num:i($CoreId)"!] */
            NULL_PTR[!//
    [!ENDIF!][!//
    [!IF "num:i($CoreId) < num:i(ecu:get('Mcu.NoOfCoreAvailable') - 1)"!][!//
,
    [!ENDIF!][!//
    [!ENDFOR!][!//
            [!ENDINDENT!][!//
        
        },
        /* Table for relationship between channel ID in specified core and ICU channel ID */
        &Icu_ChannelToCoreMap[0U],
        /* Pointer to GTM-TIM channel mapping with logic channel */
        &Icu_HwTimChannelMap[0U]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDCODE!][!//
[!ENDINDENT!][!//
[!CODE!][!//
/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"
[!ENDCODE!][!//

[!ENDNOCODE!][!//

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
