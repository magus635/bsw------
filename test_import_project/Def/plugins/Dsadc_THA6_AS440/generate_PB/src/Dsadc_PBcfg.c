/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Adc_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SARADC
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
* 
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Dsadc_PBcfg_c_REF_1:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the 
*   complexity.
*
*#Dsadc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain
*   parts of the driver must be placed.
*
*#Dsadc_PBcfg_c_REF_3:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
*   substitution.
*
*#Dsadc_PBcfg_c_REF_4:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
*   substitution.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Dsadc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!//
#include "Dsadc.h"
#include "Mcall.h"

[!NOCODE!][!//
    [!VAR "Var_DsadcDetEnFlg" = "DsadcGeneral/DsadcDevErrorDetect"!][!//
    [!VAR "Var_DsadcTimestampEnFlg" = "DsadcGeneral/DsadcTimestampEnable"!][!//
    [!VAR "Var_DsadcNotifFuncFlg" = "DsadcGeneral/DsadcNotifCapability"!][!//
    [!IF "DsadcGeneral/DsadcAuxiliaryFilterChainEnable = 'true'"!][!//
        [!VAR "Var_DsadcLimitCheckingFlg" = "DsadcGeneral/DsadcAuxLimitCheckingEnable"!][!//
    [!ELSE!][!//
        [!VAR "Var_DsadcLimitCheckingFlg" = "'false'"!][!//
    [!ENDIF!][!//
    [!VAR "Var_DsadcAuxFilterEnFlg" = "DsadcGeneral/DsadcAuxiliaryFilterChainEnable"!][!//
    [!VAR "Var_DsadcClockSyncEnFlg" = "DsadcGeneral/DsadcClockSyncEnable"!][!//
    [!VAR "Var_DsadcIntegratorEnFlg" = "DsadcGeneral/DsadcIntegratorEnable"!][!//
    [!CALL "CG_GeneDsadcCarrierEnableStatus"!][!//
    [!CALL "CG_GeneDsadcAuxFltrEnableBits"!][!//
    [!CALL "CG_GeneDsadc1InputPin"!][!//
    [!IF "num:i(variant:size()) != num:i(0)"!][!//
        [!VAR "Var_DsadcConfigShortName"="concat('_', variant:name())"!][!//
    [!ELSE!][!//
        [!VAR "Var_DsadcConfigShortName"="''"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
[!INDENT "0"!][!//
[!IF "$Var_DsadcNotifFuncFlg = 'true'"!][!//
    [!/* Notification Function declaration */!][!//
    [!LOOP "DsadcConfigSet/DsadcChannel/*"!][!//
        [!IF "node:exists(./DsadcNewResultNotification) and ./DsadcNewResultNotification != 'NULL_PTR'"!][!//
            /* New result notification declaration - [!"node:name(.)"!]: Channel[!"node:value(DsadcChannelId)"!] */
            extern void [!"./DsadcNewResultNotification"!](Dsadc_ConvChannelType ConvChannel);
        [!ENDIF!][!//
        [!IF "node:exists(./DsadcBufferFullNotification) and ./DsadcBufferFullNotification != 'NULL_PTR'"!][!//
            /* Buffer full notification declaration - [!"node:name(.)"!]: Channel[!"node:value(DsadcChannelId)"!] */
            extern void [!"./DsadcBufferFullNotification"!](void);
        [!ENDIF!][!//
        [!IF "node:exists(./DsadcLimitCheckingNotification) and ./DsadcLimitCheckingNotification != 'NULL_PTR'"!][!//
            /* Limit checking notification declaration - [!"node:name(.)"!]: Channel[!"node:value(DsadcChannelId)"!] */
            extern void [!"./DsadcLimitCheckingNotification"!](Dsadc_LimitCheckingEventType ChEvent, Dsadc_ResultType ChResult);
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!INDENT "0"!][!//
    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore3)"!][!//
    [!ENDIF!][!//
    [!IF "num:i($CoreUsedForDsadcChannelFlg) != num:i(0)"!][!//

        #define DSADC_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
        /* #Violation: Dsadc_PBcfg_c_REF_2 */
        #include "Dsadc_MemMap.h"

        [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, './DsadcChannelId')"!][!//
            [!CALL "CG_FindDsadcChannelMappedCoreId", "DsadcChannelName" = "node:name(.)"!][!//
            [!IF "num:i($DsadcChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                /* Modulator configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_ModulatorConfig Dsadc_ModulatorConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                    [!SELECT "./DsadcModulatorConfig/*[1]"!][!//
                        /* PINEN: enabled(TRUE) or disabled(FALSE) */
                        [!IF "./DsadcPositiveInputLine = 'DSADC_POS_DISABLE'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        /* NINEN: enabled(TRUE) or disabled(FALSE) */
                        [!IF "./DsadcNegativeInputLine = 'DSADC_NEG_DISABLE'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        /* PINSET: enabled(TRUE) or disabled(FALSE) */
                        [!IF "./DsadcPositiveInputLine = 'DSADC_POS_DISABLE'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        /* NINSET: enabled(TRUE) or disabled(FALSE) */
                        [!IF "./DsadcNegativeInputLine = 'DSADC_NEG_DISABLE'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        /* Initialize input pin of multiplexer */
                        [!IF "(./DsadcInputMuxInitPin = 'DSADC_INPUT_PIN_A') or (./DsadcInputMuxInitPin = 'DSADC_INPUT_PIN_C')"!]TRUE[!ELSE!]FALSE[!ENDIF!],
                        /* Not Change or change to another input pin by a trigger event */
                        [!IF "./DsadcInputMuxChangeMode = 'DSADC_INPUTMUX_CHANGE_PRESET'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        /* Auto power control disabled */
                        FALSE,
                        /* Input pin gain */
                        [!"./DsadcInputGain"!],
                        /* Control condition for a trigger event to control the input multiplexer */
                        [!IF "node:exists(./DsadcInputMuxControlMode)"!][!//
                            (Dsadc_InputMultiplexerTriggerMode)[!"./DsadcInputMuxControlMode"!]
                        [!ELSE!][!//
                            (Dsadc_InputMultiplexerTriggerMode)DSADC_INPUTMUX_CTRL_SW
                        [!ENDIF!][!//
                    [!ENDSELECT!][!//
                    [!ENDINDENT!][!//
                };

                /* Demodulator configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_DemodulatorConfig Dsadc_DemodulatorConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                    [!SELECT "./DsadcDemodulatorConfig/*[1]"!][!//
                        /* Result display mode: unsigned or signed */
                        [!IF "./DsadcResultDisplayMode = 'DSADC_RES_MODE_SIGNED'"!]FALSE[!ELSE!]TRUE[!ENDIF!],
                        [!IF "../../DsadcTriggerMode = 'DSADC_TRIGG_MODE_EXTERNAL'"!][!//
                            [!IF "node:exists(./DsadcTriggerSelect)"!][!//
                                [!VAR "Var_TrigSrcId" = "text:split(./DsadcTriggerSelect, '_')[2]"!][!//
                                [!VAR "Var_TrigSrcName" = "substring-after(./DsadcTriggerSelect, '_')"!][!//
                                /* Trigger source: [!"$Var_TrigSrcName"!] */
                                /* #Violation: Dsadc_PBcfg_c_REF_1 */
                                (Dsadc_TriggerSource)[!"$Var_TrigSrcId"!]U
                            [!ELSE!][!//
                                /* External trigger is not used */
                                /* #Violation: Dsadc_PBcfg_c_REF_1 */
                                (Dsadc_TriggerSource)0U
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            /* External trigger is not used, default is 0 */
                            /* #Violation: Dsadc_PBcfg_c_REF_1 */
                            (Dsadc_TriggerSource)0U
                        [!ENDIF!][!//
                    [!ENDSELECT!][!//
                    [!ENDINDENT!][!//
                };
                [!//
                [!/* Judge whether the timestamp is enabled or not. */!][!//
                [!IF "($Var_DsadcTimestampEnFlg = 'true') and (./DsadcChTimestampEnable = 'true')"!][!//
                [!/* line feed */!]
                /* Timestamp configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_TimeStampConfig Dsadc_TimestampConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                        /* Enable the timestamp counter */
                        TRUE,
                        [!IF "./DsadcDemodulatorConfig/*[1]/DsadcTimestampConfig/*[1]/DsadcInputMuxDispEnable = 'true'"!][!//
                            /* Multiplexer copy is enabled */
                            TRUE,
                        [!ELSE!][!//
                            /* Not copy multiplexer */
                            FALSE,
                        [!ENDIF!][!//
                        /* Timestamp clock frequency */
                        [!"./DsadcDemodulatorConfig/*[1]/DsadcTimestampConfig/*[1]/DsadcTimestampClockDivider"!]U,
                        /* Timestamp counter clock */
                        /* #Violation: Dsadc_PBcfg_c_REF_1 */
                        [!"./DsadcDemodulatorConfig/*[1]/DsadcTimestampConfig/*[1]/DsadcTimestampCounterClockSel"!],
                        /* Timestamp trigger mode is equal to trigger mode of external trigger source */
                        (Dsadc_TimeStampTriggerMode)[!"./DsadcDemodulatorConfig/*[1]/DsadcTimestampConfig/*[1]/DsadcTimestampTrigSignal"!]
                    [!ENDINDENT!][!//
                };
                [!ENDIF!][!//
                [!//
                [!VAR "Var_ChannelId" = "./DsadcChannelId"!][!//
                [!VAR "Var_AuxFilterEnableFlg" = "./DsadcChAuxiliaryFilterChainEnable"!][!//
                [!VAR "Var_LimitCheckingExistsFlag" = "'false'"!][!//
                [!SELECT "./DsadcFilterConfig/*[1]"!][!//
                    [!IF "($Var_AuxFilterEnableFlg = 'true') and node:exists(./DsadcLimitCheckingConfig)"!][!//
                        [!IF "(num:i(count(./DsadcLimitCheckingConfig/*)) > num:i(0)) and 
                              (./DsadcLimitCheckingConfig/*[1]/DsadcLimitCheckingEnable = 'true')"!][!//
                            /* Limit checking configuration parameters of channel[!"num:i($Var_ChannelId)"!] */
                            static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel[!"num:i($Var_ChannelId)"!] = 
                            {
                                [!INDENT "4"!][!//
                                /* Low boundary value of limit checking */
                                [!/* convert the signed value to unsigned value */!][!//
                                (uint16)[!"bit:and(num:i(./DsadcLimitCheckingConfig/*[1]/DsadcLowerBoundaryValue), num:hextoint('0xFFFF'))"!], 
                                /* high boundary value of limit checking */
                                (uint16)[!"bit:and(num:i(./DsadcLimitCheckingConfig/*[1]/DsadcUpperBoundaryValue), num:hextoint('0xFFFF'))"!]
                                [!ENDINDENT!][!//
                            };
                            [!VAR "Var_LimitCheckingExistsFlag" = "'true'"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDSELECT!][!//

                [!IF "$Var_LimitCheckingExistsFlag = 'false'"!][!//
                    /* Default Limit checking configuration parameters of channel[!"num:i($Var_ChannelId)"!],
                       Used for AVOID SAC ALARM */
                    static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel[!"num:i($Var_ChannelId)"!] = 
                    {
                        [!INDENT "4"!][!//
                        /* Low boundary value of limit checking: -32768, unsigned value is 32768 */
                        (uint16)32768, 
                        /* high boundary value of limit checking: 32767 */
                        (uint16)32767
                        [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//

                /* Main filter configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_MainFilterConfig Dsadc_MainFilterConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                    [!SELECT "./DsadcFilterConfig/*[1]"!][!//
                        [!IF "./DsadcFilterCICEnable = 'true'"!][!//
                            /* CIC filter is enabled */
                            TRUE,
                        [!ELSE!][!//
                            /* CIC filter is disbaled */
                            FALSE,
                        [!ENDIF!][!//
                        /* FIR0 decimation rate is [!"./DsadcFilterFIR0DecimationRate"!] */
                        [!IF "./DsadcFilterFIR0DecimationRate = '1'"!][!//
                            TRUE,
                        [!ELSE!][!//
                            FALSE,
                        [!ENDIF!][!//
                        /* FIR1 decimation rate is [!"./DsadcFilterFIR1DecimationRate"!] */
                        [!IF "./DsadcFilterFIR1DecimationRate = '1'"!][!//
                            TRUE,
                        [!ELSE!][!//
                            FALSE,
                        [!ENDIF!][!//
                        [!IF "./DsadcFilterFIR0Enable = 'true'"!][!//
                            /* FIR0 filter is enabled */
                            TRUE,
                        [!ELSE!][!//
                            /* FIR0 filter is disabled */
                            FALSE,
                        [!ENDIF!][!//
                        [!IF "./DsadcFilterFIR1Enable = 'true'"!][!//
                            /* FIR1 filter is enabled */
                            TRUE,
                        [!ELSE!][!//
                            /* FIR1 filter is disabled */
                            FALSE,
                        [!ENDIF!][!//
                        /* FIR0 offset */
                        (boolean)[!"./DsadcFilterFIR0OutputShift"!],
                        /* CIC filter sampling factor */
                        [!"num:i(./DsadcFilterCICSamplingFactor - 1)"!]U,
                        /* CIC filter type */
                        /* #Violation: Dsadc_PBcfg_c_REF_1 */
                        (Dsadc_CicParallelSelection)[!"num:i(text:split(./DsadcFilterCICSelect, 'CIC')[1] - 1)"!]U,
                        /* Service request */
                        [!IF "(../../DsadcResultHandlingImplementation != 'DSADC_POLLING_MODE')"!][!//
                            [!IF "(../../DsadcTriggerMode = 'DSADC_TRIGG_MODE_CONTINUOUS')"!][!//
                                (Dsadc_ServiceRequest)DSADC_DATA_FIFO_THRESHOLD,
                            [!ELSE!][!//
                                (Dsadc_ServiceRequest)[!"../../DsadcGateActiveLevel"!],
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            [!IF "(../../DsadcTriggerMode = 'DSADC_TRIGG_MODE_CONTINUOUS')"!][!//
                                (Dsadc_ServiceRequest)DSADC_GATE_NONE,
                            [!ELSE!][!//
                                (Dsadc_ServiceRequest)[!"../../DsadcGateActiveLevel"!],
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        /* Alarm generate config */
                        DSADC_ALARMCONDITION_NEWRESULT,
                        /* FIR1 offset */
                        /* #Violation: Dsadc_PBcfg_c_REF_1 */
                        (Dsadc_FirOffset)[!"./DsadcFilterFIR1OutputShift"!],
                        /* Offset compensation filter config. */
                        (Dsadc_FilterOffsetCompensation)[!"./DsadcFilterOffsetComp"!]
                    [!ENDSELECT!][!//
                    [!ENDINDENT!][!//
                };
                [!//
                [!IF "(./DsadcChAuxiliaryFilterChainEnable = 'true')"!][!//
                    [!/* line feed */!]
                    /* Auxiliary filter configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                    static const Dsadc_AuxiliaryFilterConfig Dsadc_AuxFilterConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                    {
                        [!SELECT "./DsadcFilterConfig/*[1]/DsadcAuxFilterConfig"!][!//
                        [!INDENT "4"!][!//
                        [!VAR "Var_AuxServiceReq" = "'false'"!][!//
                        [!IF "(../../../DsadcResultHandlingImplementation = 'DSADC_INTERRUPT_MODE') or (../../../DsadcResultHandlingImplementation = 'DSADC_POLLING_MODE')"!][!//
                            [!IF "node:exists(../../../DsadcChAuxFilterResultAcquisitionEnable) and (../../../DsadcChAuxFilterResultAcquisitionEnable = 'true')"!][!//
                                [!VAR "Var_AuxServiceReq" = "'true'"!][!//
                            [!ELSEIF "(node:exists(../DsadcLimitCheckingConfig)) and 
                                      (num:i(count(../DsadcLimitCheckingConfig/*)) > num:i(0)) and 
                                      (../DsadcLimitCheckingConfig/*[1]/DsadcLimitCheckingEnable = 'true')"!][!//
                                [!VAR "Var_AuxServiceReq" = "'true'"!][!//
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "$Var_AuxServiceReq = 'true'"!][!//
                            /* Enable the auxiliary filter service request */
                            TRUE,
                        [!ELSE!][!//
                            /* Disable the auxiliary filter service request */
                            FALSE,
                        [!ENDIF!][!//
                        [!IF "./DsadcAuxFilterCICEnable = 'true'"!][!//
                            /* Enable the auxiliary CIC filter */
                            TRUE,
                        [!ELSE!][!//
                            /* Disable the auxiliary CIC filter */
                            FALSE,
                        [!ENDIF!][!//
                        /* Auxiliary channel CIC filter sampling factor */
                        [!"num:i(./DsadcAuxFilterCICDecimationFactor - 1)"!]U,
                        /* Auxiliary filter type */
                        /* #Violation: Dsadc_PBcfg_c_REF_1 */
                        (Dsadc_CicParallelSelection)[!"num:i(text:split(./DsadcAuxFilterCICSelect, 'CIC')[1] - 1)"!]U
                        [!ENDINDENT!][!//
                        [!ENDSELECT!][!//
                    };
                [!ENDIF!][!//
                [!//
                [!IF "./DsadcFilterConfig/*[1]/DsadcChIntegratorEnable = 'true'"!][!//
                [!/* line feed */!]
                /* Integrator configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_MeanConfig Dsadc_IntegratorConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                    [!SELECT "./DsadcFilterConfig/*[1]"!][!//
                        [!IF "./DsadcChMeanMode = 'DSADC_SINGLE_CARRIER_MODE'"!][!//
                            /* Integrator for fixed single carrier */
                            FALSE,
                        [!ELSE!][!//
                            /* Integrator for Mean points configurable */
                            TRUE,
                        [!ENDIF!][!//
                        /* Integrator mean point */
                        [!"num:i(./DsadcChMeanPoints  - 1)"!]U,
                        /* Mean shift length */
                        DSADC_MEANSHIFTLENGTH_[!"text:split(./DsadcChMeanPointShiftLength, 'DSADC_MEAN_POINT_')[1]"!]
                    [!ENDSELECT!][!//
                    [!ENDINDENT!][!//
                };
                [!ENDIF!][!//
                [!//
                [!IF "(./DsadcTriggerMode = 'DSADC_TRIGG_MODE_CONTINUOUS') and (./DsadcResultHandlingImplementation != 'DSADC_POLLING_MODE')"!][!//
                    [!/* line feed */!]
                    /* FIFO configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                    static const Dsadc_FifoConfig Dsadc_FifoConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                    {
                        [!INDENT "4"!][!//
                            /* FIFO threshold */
                            /* #Violation: Dsadc_PBcfg_c_REF_1 */
                            (Dsadc_FifoThreshold)0U
                        [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//
                [!//
                [!IF "node:exists(./DsadcCalibCompConfig) and (num:i(count(./DsadcCalibCompConfig/*)) > 0)"!][!//
                    [!/* line feed */!]
                    /* Compensation configuration parameter of channel[!"num:i(./DsadcChannelId)"!] */
                    static const Dsadc_CompensationConfig Dsadc_CompensationConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                    {
                        [!INDENT "4"!][!//
                        /* DC compensation offset value. register COMP.DCOFFSET */
                        [!"./DsadcCalibCompConfig/*[1]/DsadcDcCompensationOffset"!]U,
                        /* Gain compensation offset value. register COMP.GCOFFSET */
                        [!"./DsadcCalibCompConfig/*[1]/DsadcGainCompensationOffset"!]U
                        [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//

                /* HW unit configuration parameters of channel[!"num:i(./DsadcChannelId)"!] */
                static const Dsadc_ModuleConfig Dsadc_HWUnitConfigChannel[!"num:i(./DsadcChannelId)"!] = 
                {
                    [!INDENT "4"!][!//
                    /* Point to the modulator parameters configuration */
                    &Dsadc_ModulatorConfigChannel[!"num:i(./DsadcChannelId)"!],
                    /* Point to the demodulator parameters configuration */
                    &Dsadc_DemodulatorConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!IF "($Var_DsadcTimestampEnFlg = 'true') and (./DsadcChTimestampEnable = 'true')"!][!//
                        /* Point to the timestamp parameters configuration */
                        &Dsadc_TimestampConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!ELSE!][!//
                        /* Timestamp is not enabled for this channel */
                        NULL_PTR,
                    [!ENDIF!][!//
                    /* Point to the limit checking parameters configuration */
                    &Dsadc_LimitCheckingConfigChannel[!"num:i(./DsadcChannelId)"!],
                    /* Point to the main filter parameter configuration */
                    &Dsadc_MainFilterConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!IF "(./DsadcChAuxiliaryFilterChainEnable = 'true')"!][!//
                        /* Point to the auxiliary filter parameter configuration */
                        &Dsadc_AuxFilterConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!ELSE!][!//
                        /* No auxiliary filter chain configuration */
                        NULL_PTR,
                    [!ENDIF!][!//
                    [!IF "./DsadcFilterConfig/*[1]/DsadcChIntegratorEnable = 'true'"!][!//
                        /* Point to the integrator parameters configuration */
                        &Dsadc_IntegratorConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!ELSE!][!//
                        /* Integrator is disabled */
                        NULL_PTR,
                    [!ENDIF!][!//
                    [!IF "(./DsadcTriggerMode = 'DSADC_TRIGG_MODE_CONTINUOUS') and (./DsadcResultHandlingImplementation != 'DSADC_POLLING_MODE')"!][!//
                        /* Point to the FIFO parameters configuration */
                        &Dsadc_FifoConfigChannel[!"num:i(./DsadcChannelId)"!]
                    [!ELSE!][!//
                        /* FIFO not used, external trigger */
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                };
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        /* Channel configuration parameters in [!"num:i($Var_CoreIdx)"!] */
        /* #Violation: Dsadc_PBcfg_c_REF_3 */
        /* #Violation: Dsadc_PBcfg_c_REF_4 */
        static const Dsadc_ChannelConfigType Dsadc_ChannelConfigCore[!"num:i($Var_CoreIdx)"!][[!"num:i($CoreUsedForDsadcChannelFlg)"!]] = 
        {
            [!INDENT "4"!][!//
            [!VAR "Var_ChannelCnt" = "num:i(0)"!][!//
            [!VAR "Var_SingleAccessChannelCnt" = "num:i(0)"!][!//
            [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, './DsadcChannelId')"!][!//
                [!CALL "CG_FindDsadcChannelMappedCoreId", "DsadcChannelName" = "node:name(.)"!][!//
                [!IF "num:i($DsadcChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                {
                    [!INDENT "8"!][!//
                    /* HW Unit ID */
                    [!"num:i(text:split(./DsadcHwUnitId, 'DSADC')[1])"!]U,
                    /* Logical channel ID */
                    [!"num:i(./DsadcChannelId)"!]U,
                    [!IF "./DsadcModulatorConfig/*[1]/DsadcDitheringEnable = 'true'"!][!//
                        /* Enable the modulator dithering */
                        TRUE,
                    [!ELSE!][!//
                        /* Disable the modulator dithering */
                        FALSE,
                    [!ENDIF!][!//
                    [!IF "(./DsadcModulatorConfig/*[1]/DsadcNegativeInputLine = 'DSADC_NEG_INPUT_COMM_MODE_VOLT') or 
                            (./DsadcModulatorConfig/*[1]/DsadcPositiveInputLine = 'DSADC_POS_INPUT_COMM_MODE_VOLT')"!][!//
                        [!VAR "Var_CommModeVoltValue" = "text:split(./DsadcModulatorConfig/*[1]/DsadcCommonModeVoltageSelect, 'DSADC_COMM_MODE_VOLT_')[1]"!][!//
                        /* Common mode voltage is used */
                        TRUE,
                        /* Common mode voltage connect to DSADC_BIASVOLTAGE_[!"$Var_CommModeVoltValue"!] */
                        DSADC_BIASVOLTAGE_[!"$Var_CommModeVoltValue"!],
                    [!ELSE!][!//
                        /* Common mode voltage is not used */
                        FALSE,
                        /* Default set to [!"ecu:list('Dsadc.CommModeVolt.type')[1]"!] */
                        DSADC_BIASVOLTAGE_0,
                    [!ENDIF!][!//
                    [!IF "$Var_DsadcAuxFilterEnFlg = 'true'"!][!//
                        [!IF "node:exists(./DsadcChAuxFilterResultAcquisitionEnable) and (./DsadcChAuxFilterResultAcquisitionEnable = 'true')"!][!//
                            /* Enable auxiliary conversion channel result acquisition functionality */
                            TRUE,
                        [!ELSE!][!//
                            /* Disable auxiliary conversion channel result acquisition functionality */
                            FALSE,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$Var_DsadcTimestampEnFlg = 'true'"!][!//
                        [!IF "./DsadcChTimestampEnable = 'true'"!][!//
                            /* Timestamp enabled */
                            TRUE,
                        [!ELSE!][!//
                            /* Timestamp disabled */
                            FALSE,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    /* Result handling mode */
                    [!"concat('DSADC_RESULT_HANDLING', text:split(./DsadcResultHandlingImplementation, 'DSADC')[1])"!],
                    /* Number of values to be acquired in streaming access mode */
                    [!"num:i(./DsadcStreamingNumSamples)"!]U,
                    /* Conversion result access mode */
                    [!"./DsadcAccessMode"!],
                    /* Buffer mode type */
                    [!"./DsadcStreamBufferMode"!],
                    [!IF "$Var_DsadcNotifFuncFlg = 'true'"!][!//
                        [!IF "node:exists(./DsadcNewResultNotification) and (./DsadcNewResultNotification != 'NULL_PTR')"!][!//
                            /* Pointer to the new conversion result generated notification function '[!"./DsadcNewResultNotification"!]' and 
                            this function shall be implemented by the user */
                            [!"./DsadcNewResultNotification"!],
                        [!ELSE!][!//
                            /* No new result conversion generated notification function */
                            NULL_PTR,
                        [!ENDIF!][!//
                        [!IF "node:exists(./DsadcBufferFullNotification) and (./DsadcBufferFullNotification != 'NULL_PTR')"!][!//
                            /* Pointer to the buffer full notification function '[!"./DsadcBufferFullNotification"!]' and 
                            this function shall be implemented by the user */
                            [!"./DsadcBufferFullNotification"!],
                        [!ELSE!][!//
                            /* No buffer full notification function */
                            NULL_PTR,
                        [!ENDIF!][!//
                        [!IF "node:exists(./DsadcLimitCheckingNotification) and (./DsadcLimitCheckingNotification != 'NULL_PTR')"!][!//
                            /* Pointer to the limit checking notification function '[!"./DsadcLimitCheckingNotification"!]' and 
                            this function shall be implemented by the user */
                            [!"./DsadcLimitCheckingNotification"!],
                        [!ELSE!][!//
                            /* No limit checking notification function */
                            NULL_PTR,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$Var_DsadcLimitCheckingFlg = 'true'"!][!//
                        /* Limit checking interrupt events */
                        [!IF "(node:exists(./DsadcFilterConfig/*[1]/DsadcLimitCheckingConfig)) and (num:i(count(./DsadcFilterConfig/*[1]/DsadcLimitCheckingConfig/*)) > num:i(0))"!][!//
                            [!SELECT "./DsadcFilterConfig/*[1]/DsadcLimitCheckingConfig/*[1]"!][!//
                                [!IF "./DsadcLimitCheckingEnable = 'true'"!][!//
                                    [!VAR "Var_Intlag" = "'false'"!][!//
                                    [!IF "./DsadcBelowLowerLimitEventEnable = 'true'"!][!//
                                        DSADC_LIMITCHECKING_BELOW_LOWER[!//
                                        [!VAR "Var_Intlag" = "'true'"!][!//
                                    [!ENDIF!][!//
                                    [!IF "./DsadcAboveUpperLimitEventEnable = 'true'"!][!//
                                        [!IF "$Var_Intlag = 'true'"!][!//
                                            [!WS "1"!]| [!//
                                        [!ENDIF!][!//
                                        DSADC_LIMITCHECKING_ABOVE_UPPER[!//
                                        [!VAR "Var_Intlag" = "'true'"!][!//
                                    [!ENDIF!][!//
                                    [!IF "$Var_Intlag = 'false'"!][!//
                                        0U
                                    [!ENDIF!][!//
                                    ,
                                [!ELSE!][!//
                                    0U,
                                [!ENDIF!][!//
                            [!ENDSELECT!][!//
                        [!ELSE!][!//
                            0U,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "node:exists(./DsadcCalibCompConfig) and (num:i(count(./DsadcCalibCompConfig/*)) > 0)"!][!//
                        /* Pointer to the compensation configuration parameter */
                        &Dsadc_CompensationConfigChannel[!"num:i(./DsadcChannelId)"!],
                    [!ELSE!][!//
                        /* No compensation configuration parameter */
                        NULL_PTR,
                    [!ENDIF!][!//
                    /* Point to the HW unit configuration of this channel([!"num:i(./DsadcChannelId)"!]) */
                    &Dsadc_HWUnitConfigChannel[!"num:i(./DsadcChannelId)"!]
                    [!ENDINDENT!][!//
                    [!VAR "Var_ChannelCnt" = "num:i($Var_ChannelCnt + 1)"!][!//
                }[!//
                    [!IF "num:i($Var_ChannelCnt) < num:i($CoreUsedForDsadcChannelFlg)"!][!//
                    ,
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        };

        /* Core[!"num:i($Var_CoreIdx)"!] configuration set */
        static const Dsadc_CoreConfigType Dsadc_ConfigSetCore[!"num:i($Var_CoreIdx)"!] = 
        {
            [!INDENT "4"!][!//
                /* Maximum number of the channels in core[!"num:i($Var_CoreIdx)"!] */
                [!"num:i($CoreUsedForDsadcChannelFlg)"!]U,
                /* Pointer to the channel configuration set */
                &Dsadc_ChannelConfigCore[!"num:i($Var_CoreIdx)"!][0]
            [!ENDINDENT!][!//
        };

        /* Configuration informations which mapped to Core[!"$Var_CoreIdx"!] */
        #define DSADC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
        /* #Violation: Dsadc_PBcfg_c_REF_2 */
        #include "Dsadc_MemMap.h"
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDFOR!][!//

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define DSADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"

[!INDENT "0"!][!//
[!SELECT "DsadcConfigSet"!][!//
[!//
[!IF "$Var_IsCarrierEnabled = 'true'"!][!//
[!/* line feed */!]
/* Carrier generater configuration parameters */
static const Dsadc_CarrierWaveConfig Dsadc_CarrierConfig = 
{
    [!INDENT "4"!][!//
    [!SELECT "as:modconf('Dsadc')/DsadcConfigSet/DsadcCarrierGenerator/*[1]"!][!//
        /* Default disabled */
        FALSE,
        [!IF "./DsadcPCMEnable = 'true'"!][!//
            /* Enable the PCM mode */
            TRUE,
        [!ELSE!][!//
            /* Disable the PCM mode */
            FALSE,
        [!ENDIF!][!//
        [!IF "./DsadcCarrierGenerationMode = 'DSADC_NORMAL_MODE'"!][!//
            /* Output wave normal */
            FALSE,
        [!ELSE!][!//
            /* Output wave bit reverse */
            TRUE,
        [!ENDIF!][!//
        /* Carrier wave */
        (Dsadc_WaveMode)[!"./DsadcCarrierSignalMode"!]
    [!ENDSELECT!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//

/* Configuration for logical channel ID mapping information.
    Sub channel index in core, HW unit ID, Core ID.
*/
[!VAR "Var_TotalChannelNum" = "num:i(count(./DsadcChannel/*))"!][!//
/* #Violation: Dsadc_PBcfg_c_REF_3 */
/* #Violation: Dsadc_PBcfg_c_REF_4 */
static const Dsadc_ChannelCoreMapType Dsadc_ChannelMapConfig[[!"num:i($Var_TotalChannelNum)"!]] = 
{
    [!INDENT "4"!][!//
    [!VAR "Var_DsadcChannel2Core0Num" = "0"!][!//
    [!VAR "Var_DsadcChannel2Core1Num" = "0"!][!//
    [!VAR "Var_DsadcChannel2Core2Num" = "0"!][!//
    [!VAR "Var_DsadcChannel2Core3Num" = "0"!][!//
    [!VAR "Var_ChannelCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(./DsadcChannel/*, './DsadcChannelId')"!][!//
    {[!//
        [!VAR "Var_ChannelCnt" = "num:i($Var_ChannelCnt + 1)"!][!//
        [!VAR "Var_SubChannelIdx" = "num:i(255)"!][!//
        [!CALL "CG_FindDsadcChannelMappedCoreId", "DsadcChannelName" = "node:name(.)"!][!//
        [!IF "num:i($DsadcChannelMappedCoreId) = num:i(0)"!][!//
            [!VAR "Var_SubChannelIdx" = "num:i($Var_DsadcChannel2Core0Num)"!][!//
            [!VAR "Var_DsadcChannel2Core0Num" = "num:i($Var_DsadcChannel2Core0Num + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(1)"!][!//
            [!VAR "Var_SubChannelIdx" = "num:i($Var_DsadcChannel2Core1Num)"!][!//
            [!VAR "Var_DsadcChannel2Core1Num" = "num:i($Var_DsadcChannel2Core1Num + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(2)"!][!//
            [!VAR "Var_SubChannelIdx" = "num:i($Var_DsadcChannel2Core2Num)"!][!//
            [!VAR "Var_DsadcChannel2Core2Num" = "num:i($Var_DsadcChannel2Core2Num + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(3)"!][!//
            [!VAR "Var_SubChannelIdx" = "num:i($Var_DsadcChannel2Core3Num)"!][!//
            [!VAR "Var_DsadcChannel2Core3Num" = "num:i($Var_DsadcChannel2Core3Num + 1)"!][!//
        [!ENDIF!][!//
        [!"num:i($Var_SubChannelIdx)"!]U, [!//
        [!"text:split(./DsadcHwUnitId, 'DSADC')[1]"!]U, [!//
        [!"num:i($DsadcChannelMappedCoreId)"!]U[!//
    }[!//
        [!IF "num:i($Var_ChannelCnt) < num:i($Var_TotalChannelNum)"!][!//
        ,
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
    [!/* Line feed */!]
};
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/* Configuration for HW unit to logical channel */
[!INDENT "0"!][!//
[!VAR "Var_TotalHWunitNum" = "num:i(count(ecu:list('Dsadc.HwUnitList')))"!][!//
/* #Violation: Dsadc_PBcfg_c_REF_3 */
/* #Violation: Dsadc_PBcfg_c_REF_4 */
static const Dsadc_ChannelType Dsadc_HWUnit2ChConfig[[!"num:i($Var_TotalHWunitNum)"!]] = 
{
    [!INDENT "4"!][!//
    [!FOR "Var_HWUnitIdx" = "num:i(0)" TO "num:i($Var_TotalHWunitNum - 1)"!][!//
        [!VAR "Var_HWUnitExistsFlg" = "num:i(255)"!][!//
        [!VAR "Var_ChannelID" = "num:i(255)"!][!//
        [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, './DsadcChannelId')"!][!//
            [!IF "num:i($Var_HWUnitIdx) = num:i(text:split(./DsadcHwUnitId, 'DSADC'))"!][!//
                [!VAR "Var_HWUnitExistsFlg" = "num:i(./DsadcChannelId)"!][!//
                [!VAR "Var_ChannelID" = "num:i(./DsadcChannelId)"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "num:i($Var_HWUnitExistsFlg) != num:i(255)"!][!//
        /* Logical channel[!"num:i($Var_ChannelID)"!] mapped to DSADC[!"num:i($Var_HWUnitIdx)"!] */
        [!ELSE!][!//
        /* DSADC[!"num:i($Var_HWUnitIdx)"!] not used */
        [!ENDIF!][!//
        [!"num:i($Var_HWUnitExistsFlg)"!]U[!//
        [!IF "num:i($Var_HWUnitIdx) < num:i($Var_TotalHWunitNum - 1)"!][!//
        ,
        [!ENDIF!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
    [!/* Line feed */!]
};
[!ENDINDENT!][!//

/* Global configuration parameters */
[!INDENT "0"!][!//
static const Dsadc_GlobalConfigType Dsadc_GlobalConfig = 
{
    [!INDENT "4"!][!//
    [!VAR "Var_HWUnitEnBits" = "num:i(0)"!][!//
    [!LOOP "DsadcConfigSet/DsadcChannel/*"!][!//
        [!VAR "Var_UsedHwUnitId" = "text:split(./DsadcHwUnitId, 'DSADC')[1]"!][!//
        [!IF "num:i($Var_UsedHwUnitId) >= num:i(8)"!][!//
            [!VAR "Var_HWUnitEnBits" = "bit:or($Var_HWUnitEnBits, bit:shl(1, num:i($Var_UsedHwUnitId + 8)))"!][!//
        [!ELSE!][!//
            [!VAR "Var_HWUnitEnBits" = "bit:or($Var_HWUnitEnBits, bit:shl(1, num:i($Var_UsedHwUnitId)))"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    /* HW unit enable status */
    [!"num:inttohex($Var_HWUnitEnBits, 8)"!]U,
    [!IF "$Var_DsadcAuxFilterEnFlg = 'true'"!][!//
        /* Auxiliary filter enable status */
        [!"num:inttohex($Var_AuxFltrEnBits, 8)"!]U,
    [!ENDIF!][!//
    [!IF "$Var_IsCarrierEnabled = 'true'"!][!//
        /* Point to the carrier signal configuration parameters */
        &Dsadc_CarrierConfig
    [!ELSE!][!//
        /* No carrier configuration parameters */
        NULL_PTR,
    [!ENDIF!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* Dsadc configuration set parameters */
const Dsadc_ConfigType Dsadc_ConfigSet[!"$Var_DsadcConfigShortName"!][DSADC_CONFIGSET_CNT] =
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!VAR "CoreUsedForDsadcChannelFlg" = "num:i(0)"!][!//
                [!IF "$Var_CoreIdx = num:i(0)"!][!//
                    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore0)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
                    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore1)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
                    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore2)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
                    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore3)"!][!//
                [!ENDIF!][!//
                [!IF "num:i($CoreUsedForDsadcChannelFlg) != num:i(0)"!][!//
                    /* Configuration set for core[!"num:i($Var_CoreIdx)"!] */
                    &Dsadc_ConfigSetCore[!"num:i($Var_CoreIdx)"!][!//
                [!ELSE!][!//
                    /* Not configuration set for core[!"num:i($Var_CoreIdx)"!] */
                    NULL_PTR[!//
                [!ENDIF!][!//
                [!IF "num:i($Var_CoreIdx) < num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                    ,
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        },
        /* Point to the global configuration parameters */
        &Dsadc_GlobalConfig,
        /* Point to the logical channel mapping buffer */
        &Dsadc_ChannelMapConfig[0],
        /* Point to the buffer that HW unit mapped to logical channel */
        &Dsadc_HWUnit2ChConfig[0][!//
        [!IF "num:i($Var_Dsadc1InputPin) != num:i(255)"!][!//
            ,
            /* Input pin for DSADC1 */
            [!"num:i($Var_Dsadc1InputPin)"!]U
        [!ELSE!][!//
            [!/* Line feed */!]
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
