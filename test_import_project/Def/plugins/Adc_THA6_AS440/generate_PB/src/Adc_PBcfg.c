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
*#Adc_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Adc_PBcfg_c_REF_2:MISRAC2012-Rule-10.5;
* Justification:Redundant cast is necessary to maintain the software structure and reduce the 
* complexity.
*
*#Adc_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Adc_PBcfg_c_REF_4:CertC-DLC06-C
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Adc_PBcfg_c_REF_5:CWE-547
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Adc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!//
#include "Adc.h"

[!//
[!SELECT "as:modconf('Adc')[1]"!][!//
[!NOCODE!][!//
    [!VAR "AdcPrioImp" = "AdcGeneral/AdcPriorityImplementation"!][!//
    [!VAR "AdcReqSrcCount"= "num:i(ecu:get('Adc.ReqSrcCount') - 1)"!][!//
    [!VAR "AdcHwTrigApiEnSta" = "AdcGeneral/AdcHwTriggerApi"!][!//
    [!VAR "AdcGrpNotifEnSta" = "AdcGeneral/AdcGrpNotifCapability"!][!//
    [!VAR "AdcLimitCheckingEnSta" = "AdcGeneral/AdcEnableLimitCheck"!][!//
    [!VAR "AdcSyncGroupEnSta" = "AdcGeneral/AdcSyncConvEnable"!][!//
    [!CALL "Adc_HwUnitResultHandlingMethodEnStatus"!][!//
    [!IF "num:i(variant:size()) != num:i(0)"!][!//
        [!VAR "Var_AdcConfigShortName"="concat('_', variant:name())"!][!//
    [!ELSE!][!//
        [!VAR "Var_AdcConfigShortName"="''"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
[!//

/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
[!INDENT "0"!][!//
[!IF "$AdcGrpNotifEnSta = 'true'"!][!//
    [!/* Notification Function declaration */!][!//
    [!LOOP "AdcConfigSet/AdcHwUnit/*/AdcGroup/*"!][!//
        [!IF "node:exists(./AdcNotification)"!][!//
            /* [!"node:name(../../.)"!]/[!"node:name(.)"!] notification function declaration */
            extern void [!"./AdcNotification"!](void);
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
[!/* Container: Adc HwUnit Configuration */!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!INDENT "0"!][!//
    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore3)"!][!//
    [!ENDIF!][!//
    [!IF "num:i($CoreUsedForAdcHwUnitFlg) != num:i(0)"!][!//

        /* Configuration informations which mapped to Core[!"$Var_CoreIdx"!] */
        /* #Violation: Adc_PBcfg_c_REF_3 */
        #define ADC_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$Var_CoreIdx"!]_UNSPECIFIED
        /* #Violation: Adc_PBcfg_c_REF_1 */
        #include "Adc_MemMap.h"

        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "HwUnitName" = "./AdcHwUnitId"!][!//
            [!VAR "UnitId" = "num:i(text:split($HwUnitName, 'SARADC')[1])"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                /* ADC[!"$UnitId"!] Group "[!"node:name(.)"!]" configuration */
                [!LOOP "node:order(AdcGroup/*, './AdcGroupId')"!][!//
                    [!VAR "SymbolicName" = "node:name(.)"!][!//
                    [!VAR "TotalAdcGroupDef"= "num:i(count(AdcGroupDefinition/*))"!][!//
                    /* #Violation: Adc_PBcfg_c_REF_5 */
                    /* #Violation: Adc_PBcfg_c_REF_4 */
                    static const Adc_GroupDefType Adc_ChsInHwUnit[!"$UnitId"!][!"$SymbolicName"!][[!"num:i($TotalAdcGroupDef + 1)"!]] =
                    {
                    [!INDENT "4"!][!//
                        /* Total number of channels assigned to the group '[!"$SymbolicName"!]' of HwUnit[!"$UnitId"!] */
                        [!"$TotalAdcGroupDef"!]U,

                        /* The channels assigned to the group '[!"$SymbolicName"!]' of HwUnit[!"$UnitId"!] */
                    [!FOR "GroupDef" = "num:i(0)" TO "num:i($TotalAdcGroupDef)-1"!][!//
                        [!VAR "GroupChannelName" = "node:name(node:ref(AdcGroupDefinition/*[@index=$GroupDef]))"!][!//
                        [!LOOP "../../AdcChannel/*"!][!//
                            [!IF "@name = $GroupChannelName"!][!//
                                [!VAR "GroupChannelIndex" = "AdcChannelId"!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                        [!"num:i($GroupChannelIndex)"!]U[!IF "num:i($GroupDef) != num:i(($TotalAdcGroupDef)-1)"!],[!ENDIF!]
                    [!ENDFOR!][!//
                    [!ENDINDENT!][!//
                    };
                    [!IF "(../../AdcResultHandlingImplementation = 'DMA_MODE') and (node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!][!//
                        
                        [!VAR "TotalAdcGroupResRegDef"= "num:i(count(AdcResultRegisterDefinition/*))"!][!//
                        /* Result register configuration of the channels assigned to the group '[!"$SymbolicName"!]' of HwUnit[!"$UnitId"!] */
                        /* #Violation: Adc_PBcfg_c_REF_5 */
                        /* #Violation: Adc_PBcfg_c_REF_4 */
                        static const uint8 Adc_ChResRegsInHwUnit[!"$UnitId"!][!"$SymbolicName"!][[!"num:i($TotalAdcGroupResRegDef + 1)"!]] =
                        {
                        [!INDENT "4"!][!//
                        [!FOR "GroupResRegDef" = "num:i(0)" TO "num:i($TotalAdcGroupResRegDef)-1"!][!//
                            [!"node:value(AdcResultRegisterDefinition/*[@index=$GroupResRegDef])"!]U[!//
                            [!IF "num:i($GroupResRegDef) != num:i(($TotalAdcGroupResRegDef)-1)"!],[!ENDIF!]
                        [!ENDFOR!][!//
                        [!ENDINDENT!][!//
                        };
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!/*
        Configuration: ADC Group configuration structure
                      ADC_GROUP_ID refered by Array Index
                      ADC_GROUP_PRIORITY if ADC_PRIORITY_HW_SW considered,
                      ADC_GROUP_REPLACEMENT if ADC_PRIORITY_HW_SW considered
                      ADC_GROUP_DEFINITION
                      ADC_GROUP_TRIGG_SRC
                      ADC_GROUP_CONV_MODE
                      ADC_STREAMING_NUM_SAMPLES
                      ADC_STREAMING_BUFFER_MODE
                      ADC_HW_TRIG_SIGNAL if EXT TR Source selected
                      ADC_HW_TRIG_TIMER if TIM TR source selected
        */!][!//
        /* ADC Groups are arranged in the order of their trigger type ( HW/SW ) and
           request sources (RS0 .. RS2) starting from SW trigger RS0 to SW trigger
           RS2 and then HW trigger RS0 to HW trigger RS2. */
        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "HwUnitName" = "./AdcHwUnitId"!][!//
            [!VAR "UnitId" = "num:i(text:split($HwUnitName, 'SARADC')[1])"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                [!VAR "TotalAdcGroups"= "num:i(count(AdcGroup/*))"!][!//
                [!LOOP "node:order(AdcGroup/*, './AdcGroupId')"!][!//
                    [!IF "$AdcHwTrigApiEnSta = 'true'"!][!//
                        [!IF "./AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW'"!][!//
                            /* HW trigger configuration parameters for [!"node:name(.)"!]: channel [!"./AdcGroupId"!] */
                            /* #Violation: Adc_PBcfg_c_REF_5 */
                            /* #Violation: Adc_PBcfg_c_REF_4 */
                            static const Saradc_GatingTriggerConfig Adc_HwUnit[!"$UnitId"!]Group[!"./AdcGroupId"!]HwTrigConfig =
                            {
                                [!INDENT "4"!][!//
                                [!VAR "Var_GtmTrigSrcNum" = "text:split(text:split(node:ref(./AdcHwExtTrigSelect)/GtmTriggerSelect, 'CH')[1], 'TRI')[1]"!][!//
                                /* Gating source */
                                SARADC_GATINGSOURCE_GTM_TRIGGER[!"$Var_GtmTrigSrcNum"!],
                                /* Trigger source */
                                SARADC_TRIGGERSOURCE_GTM_TRIGGER[!"$Var_GtmTrigSrcNum"!],
                                /* Start conversion after HW trigger request occurs */
                                SARADC_GATINGMODE_ALWAYS,
                                /* Trigger signal edge */
                                [!IF "node:exists(./AdcHwTrigSignal)"!][!//
                                    /* #Violation: Adc_PBcfg_c_REF_2 */
                                    (Saradc_TriggerMode)[!"./AdcHwTrigSignal"!],
                                [!ELSE!][!//
                                    /* #Violation: Adc_PBcfg_c_REF_2 */
                                    (Saradc_TriggerMode)ADC_HW_TRIG_RISING_EDGE,
                                [!ENDIF!][!//
                                /* Not used timer trigger */
                                {
                                    [!INDENT "8"!][!//
                                    FALSE,
                                    0U,
                                    SARADC_TIMERMODE_STOP
                                    [!ENDINDENT!][!//
                                }
                                [!ENDINDENT!][!//
                            };
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!VAR "GroupCnt" = "num:i(0)"!][!//
                /* ADC HwUnit[!"$UnitId"!] Group configuration */
                static const Adc_GroupCfgType Adc_HwUnit[!"$UnitId"!]GrpCfg[ADC_CFG_GROUPS_HWUNIT_ADC[!"num:i($UnitId)"!]] =
                {
                [!INDENT "4"!][!//
                [!LOOP "node:order(AdcGroup/*, './AdcGroupId')"!][!//
                    [!VAR "GroupCnt" = "num:i($GroupCnt + 1)"!][!//
                    [!VAR "SymbolicName" = "node:name(.)"!][!//
                    /* Group '[!"$SymbolicName"!]' */
                    {
                    [!INDENT "8"!][!//
                    [!IF "($AdcSyncGroupEnSta = 'true')"!][!//
                        [!IF "node:exists(../../AdcSyncConvMode)"!][!//
                            [!IF "(../../AdcSyncConvMode = 'ADC_SYNC_CONV_SLAVE') or (../../AdcSyncConvMode = 'ADC_STANDALONE')"!][!//
                                /* No sync channel enable under this group */
                                FALSE,
                            [!ELSE!][!//
                                [!VAR "Var_IsSyncChExistsFlg" = "'false'"!][!//
                                [!LOOP "./AdcGroupDefinition/*"!][!//
                                    [!IF "node:ref(.)/AdcChannelSyncConvEnable = 'true'"!][!//
                                        [!VAR "Var_IsSyncChExistsFlg" = "'true'"!][!//
                                        [!BREAK!][!//
                                    [!ENDIF!][!//
                                [!ENDLOOP!][!//
                                [!IF "$Var_IsSyncChExistsFlg = 'true'"!][!//
                                    /* Exists at least a sync channel under this group */
                                    TRUE,
                                [!ELSE!][!//
                                    /* No sync channel enable under this group */
                                    FALSE,
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            /* Sync conversion is not enabled */
                            FALSE,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    /* Number of ADC values to be acquired in streaming access mode */
                    [!"AdcStreamingNumSamples"!]U,
                    /* Internal channel mask from group definition - derived from the tool */
                    [!NOCODE!][!//
                        [!VAR "TotalAdcGroupDef"= "num:i(count(AdcGroupDefinition/*))"!][!//
                        [!VAR "GroupMask" = "num:i(0)"!][!//
                        [!VAR "ChIndex" = "num:i(1)"!][!//
                        [!VAR "ShiftMask" = "num:i(0)"!][!//
                        [!VAR "EcuListName" = "concat('Adc.AdcChannels_Adc', $UnitId)"!][!//
                        [!FOR "GroupDef" = "num:i(0)" TO "num:i($TotalAdcGroupDef - 1)"!][!//
                            [!VAR "AnalogInputChannelNumber" = "node:ref(AdcGroupDefinition/*[@index=$GroupDef])/AdcAnChannelNum"!][!//
                            [!CALL "CG_FindHwUnitChannelID", "ChannelListName" = "$EcuListName", "ChannelName" = "$AnalogInputChannelNumber"!][!//
                            [!VAR "ChannelNumber"= "$ChannelPosition"!][!//
                            [!VAR "ShiftMask" = "bit:shl(num:i($ChIndex), num:i($ChannelNumber))"!][!//
                            [!VAR "GroupMask" = "bit:or(num:i($GroupMask), num:i($ShiftMask))"!][!//
                        [!ENDFOR!][!//
                    [!ENDNOCODE!][!//
                    (uint16)[!"num:inttohex($GroupMask)"!],
                    [!IF "$AdcGrpNotifEnSta = 'true'"!][!//
                        /* Notification function pointer */
                        [!IF "node:exists(./AdcNotification)"!][!//
                            [!"./AdcNotification"!],
                        [!ELSE!][!//
                            NULL_PTR,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                        /* Assignment of channels to a channel group */
                        /* First element is the number of configured channels in the group */
                        /* From Second element will give the channel ID */
                        &Adc_ChsInHwUnit[!"$UnitId"!][!"$SymbolicName"!][0U],
                        [!IF "($Var_DmaModeEn = 'STD_ON')"!][!//
                            [!IF "(../../AdcResultHandlingImplementation = 'DMA_MODE')"!][!//
                                [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!][!//
                                    /* Result register configuration of the channels assigned to the group */
                                    &Adc_ChResRegsInHwUnit[!"$UnitId"!][!"$SymbolicName"!][0U],
                                [!ELSE!][!//
                                    /* Manual allocation of the result register is not supported for this channel.
                                    (AdcResultRegisterManual = false). */
                                    NULL_PTR,
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                /* ADC[!"$UnitId"!] not in DMA result handling mode, 
                                   and manual allocation of the result register is not supported. */
                                NULL_PTR,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                    [!IF "$AdcHwTrigApiEnSta = 'true'"!][!//
                        [!IF "./AdcGroupTriggSrc = 'ADC_TRIGG_SRC_SW'"!][!//
                            /* SW trigger */
                            NULL_PTR,
                        [!ELSE!][!//
                            /* Pointer to the HW trigger configuration parameters */
                            &Adc_HwUnit[!"$UnitId"!]Group[!"./AdcGroupId"!]HwTrigConfig,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "node:exists(./AdcResultAccumulation)"!][!//
                        /* Enable result accumulation mode */
                        [!"num:i(./AdcResultAccumulation - 1)"!]U,
                    [!ELSE!][!//
                        /* Disable result accumulation mode */
                        0U,
                    [!ENDIF!][!//
                    /* Group trigger source: SW or HW */
                    [!"AdcGroupTriggSrc"!],
                    /* Group request queue: RS0 - RS2 */
                    SARADC_[!"AdcGroupRequestSource"!],
                    /* Group access mode */
                    [!"AdcGroupAccessMode"!],
                    /* Group conversion mode */
                    [!"AdcGroupConversionMode"!],
                    /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
                    [!"AdcStreamingBufferMode"!][!//
                    [!IF "./AdcGroupTriggSrc = 'ADC_TRIGG_SRC_SW'"!][!//
                        [!IF "$AdcPrioImp = 'ADC_PRIORITY_HW_SW'"!],
                            /* Priority level of the group */
                            [!"AdcGroupPriority"!]U,
                        [!ENDIF!]
                    [!ELSE!][!//
                        [!/* Priority mechanism for hardware trigger */!][!//
                        [!IF "$AdcPrioImp = 'ADC_PRIORITY_HW_SW'"!],
                            /* Priority level of the group */
                            0U,
                        [!ENDIF!]
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                    }[!IF "num:i($GroupCnt) < num:i($TotalAdcGroups)"!],[!ENDIF!]
                [!ENDLOOP!][!//
                [!ENDINDENT!][!//
                };
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!IF "AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_HW_SW'"!][!//
            /*
              Constant for extracting the Groups configured for a particular trigger source
              Used in Scheduler function in Adc.c
            */
            [!VAR "TotalAdcUnit" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
            [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
                [!NOCODE!][!//
                    [!VAR "GroupRS0Mask" = "num:i(0)"!][!//
                    [!VAR "GroupRS1Mask" = "num:i(0)"!][!//
                    [!VAR "GroupRS2Mask" = "num:i(0)"!][!//
                    [!VAR "Grpindex" = "num:i(1)"!][!//
                [!ENDNOCODE!][!//
                [!VAR "HwUnitName" = "./AdcHwUnitId"!][!//
                [!VAR "UnitId" = "num:i(text:split($HwUnitName, 'SARADC')[1])"!][!//
                [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
                [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                    [!VAR "GrpID" = "num:i(0)"!][!//
                    /* ADC[!"$UnitId"!] group mask configuration */
                    static const uint32 Adc_HwUnit[!"$UnitId"!]GroupMask[3U] =
                    {
                    [!INDENT "4"!][!//
                    [!NOCODE!][!//
                        [!FOR "ReqSrcId" = "num:i(0)" TO "num:i($AdcReqSrcCount)"!][!//
                            [!VAR "ShiftRSMask" = "num:i(0)"!][!//
                            [!VAR "GroupRSMask" = "num:i(0)"!][!//
                            [!VAR "ReqSrcName" = "ecu:list('Adc.ReqSrcClass')[num:i($ReqSrcId + 1)]"!][!//
                            [!LOOP "node:order(AdcGroup/*, './AdcGroupId')"!][!//
                                [!IF "./AdcGroupRequestSource = $ReqSrcName"!][!//
                                    [!IF "./AdcGroupTriggSrc = 'ADC_TRIGG_SRC_SW'"!][!//
                                        [!VAR "ShiftRSMask" = "bit:shl(num:i($Grpindex), num:i($GrpID))"!][!//
                                        [!VAR "GroupRSMask" = "bit:or(num:i($GroupRSMask), num:i($ShiftRSMask))"!][!//
                                        [!VAR "GrpID" = "$GrpID + 1"!][!//
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!ENDLOOP!][!//
                            [!IF "$ReqSrcName = ecu:list('Adc.ReqSrcClass')[1]"!][!//
                                [!VAR "GroupRS0Mask" = "num:i($GroupRSMask)"!][!//
                            [!ELSEIF "$ReqSrcName = ecu:list('Adc.ReqSrcClass')[2]"!][!//
                                [!VAR "GroupRS1Mask" = "num:i($GroupRSMask)"!][!//
                            [!ELSEIF "$ReqSrcName = ecu:list('Adc.ReqSrcClass')[3]"!][!//
                                [!VAR "GroupRS2Mask" = "num:i($GroupRSMask)"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                    [!ENDNOCODE!][!//
                        [!"num:inttohex($GroupRS0Mask)"!]U, /* For Request source 0 */
                        [!"num:inttohex($GroupRS1Mask)"!]U, /* For Request source 1 */
                        [!"num:inttohex($GroupRS2Mask)"!]U  /* For Request source 2 */
                    [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
        [!//

        [!/* Container: AdcChannelConfiguration */!][!//
        [!/* Configuration: ADC Channel configuration structure */!][!//
        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "HwUnitName" = "./AdcHwUnitId"!][!//
            [!VAR "UnitId" = "num:i(text:split($HwUnitName, 'SARADC')[1])"!][!//
            [!VAR "HwunitResolution" = "text:split(./AdcResolution, 'BITS_')[1]"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                [!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!][!//
                    [!VAR "ChLimitCheck"= "node:exists(./AdcChannelLimitCheck) and (./AdcChannelLimitCheck = 'true')"!][!//
                    [!IF "$ChLimitCheck  = 'true'"!][!//
                        /* Limit checking configuration parameters for [!"node:name(.)"!]: channel [!"./AdcChannelId"!] */
                        static const Adc_ChannelLimitCheckType Adc_HwUnit[!"$UnitId"!]Channel[!"./AdcChannelId"!]LimitCheckingConfig =
                        {
                            [!IF "node:exists(./AdcChannelRangeSelect )"!][!//
                                [!VAR "ChannelRangeSelect" = "node:value(./AdcChannelRangeSelect )"!][!//
                            [!ENDIF!][!//
                            [!IF "node:exists(./AdcChannelLowLimit)"!][!//
                                [!VAR "AdcChLowLimit" = "node:value(./AdcChannelLowLimit)"!][!//
                            [!ENDIF!][!//
                            [!IF "node:exists(./AdcChannelHighLimit)"!][!//
                                [!VAR "AdcChHighLimit" = "node:value(./AdcChannelHighLimit)"!][!//
                            [!ENDIF!][!//
                            [!CALL "Adc_GeneConfigBoundVal", "ChannelRangeSelect"= "$ChannelRangeSelect",
                                                            "ChannelHighLimit" ="$AdcChHighLimit",
                                                            "ChannelLowLimit"= "$AdcChLowLimit",
                                                            "ConvResolution" = "$HwunitResolution"!][!//
                            [!IF "($ChannelRangeSelect = 'ADC_RANGE_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_NOT_OVER_HIGH') or ($ChannelRangeSelect = 'ADC_RANGE_NOT_UNDER_LOW')"!][!//
                                [!/* Conversion result in boundary */!][!//
                                [!VAR "Var_AdcChIntTrigMode" = "'SARADC_CHANNELINTERRUPT_INBOUNDARY'"!][!//
                            [!ELSEIF "($ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW') or ($ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH')"!][!//
                                [!/* Conversion result out of boundary */!][!//
                                [!VAR "Var_AdcChIntTrigMode" = "'SARADC_CHANNELINTERRUPT_OUTBOUNDARY'"!][!//
                            [!ELSE!][!//
                                [!/* Always conversion */!][!//
                                [!VAR "Var_AdcChIntTrigMode" = "'SARADC_CHANNELINTERRUPT_ENABLE'"!][!//
                            [!ENDIF!][!//
                            [!//
                            [!INDENT "4"!][!//
                            /* Limit checking configuration */
                            {
                                [!INDENT "8"!][!//
                                /* Low boundary */
                                [!"num:i($AdcBoundLowVal)"!]U,
                                /* high boundary */
                                [!"num:i($AdcBoundHighVal)"!]U
                                [!ENDINDENT!][!//
                            },
                            /* Channel interrupt type for limit checking */
                            [!"$Var_AdcChIntTrigMode"!]
                            [!ENDINDENT!][!//
                        };
                    [!ENDIF!][!//
                [!ENDLOOP!][!//

                /* ADC [!"$UnitId"!] Channel configuration */
                /* #Violation: Adc_PBcfg_c_REF_5 */
                /* #Violation: Adc_PBcfg_c_REF_4 */
                static const Adc_ChannelCfgType Adc_HwUnit[!"$UnitId"!]ChCfg[[!"num:i(count(./AdcChannel/*))"!]] =
                {
                [!INDENT "4"!][!//
                [!VAR "ChannelCount" = "num:i(0)"!][!//
                [!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!][!//
                    [!VAR "ChCtrVal" = "num:i(0)"!][!//
                    [!NOCODE!][!//
                    [!VAR "EcuListName" = "concat('Adc.AdcChannels_Adc', $UnitId)"!][!//
                    [!/* Find the channel ID through the channel name */!][!//
                    [!CALL "CG_FindHwUnitChannelID", "ChannelListName" = "$EcuListName", "ChannelName" = "./AdcAnChannelNum"!][!//
                    [!VAR "ChannelNumber" = "$ChannelPosition"!][!//
                    [!ENDNOCODE!][!//
                    /* Channel "[!"node:name(.)"!]": channel ID - [!"./AdcChannelId"!] */
                    {
                        [!INDENT "8"!][!//
                        [!VAR "ChLimitCheck"= "node:exists(./AdcChannelLimitCheck) and (./AdcChannelLimitCheck = 'true')"!][!//
                        [!IF "$AdcLimitCheckingEnSta = 'true'"!][!//
                            [!IF "$ChLimitCheck = 'true'"!][!//
                                /* Pointer to the limit checking configuration parameters */
                                &Adc_HwUnit[!"$UnitId"!]Channel[!"./AdcChannelId"!]LimitCheckingConfig,
                            [!ELSE!][!//
                                /* Limit checking is not enabled for this channel */
                                NULL_PTR,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        /* Channel[!"$ChannelNumber"!] configuration */
                        {
                            [!INDENT "12"!][!//
                            /* Channel ID */
                            SARADC_CHANNELRESULT[!"$ChannelNumber"!],
                            /* Over-write always */
                            SARADC_OVERWRITEMODE,
                            [!IF "../../AdcResultHandlingImplementation = 'DMA_MODE'"!][!//
                                /* Dma is used */
                                TRUE,
                            [!ELSE!][!//
                                /* Dma is unused */
                                FALSE,
                            [!ENDIF!][!//
                            /* Conversion result align method */
                            (boolean)ADC_RESULT_ALIGNMENT,
                            [!IF "node:exists(./AdcChannelSyncConvEnable) and (./AdcChannelSyncConvEnable = 'true')"!][!//
                                /* Synchronize conversion is enabled */
                                TRUE,
                            [!ELSE!][!//
                                /* Synchronize conversion is unused */
                                FALSE,
                            [!ENDIF!][!//
                            [!IF "$AdcLimitCheckingEnSta = 'true'"!][!//
                                [!IF "$ChLimitCheck = 'true'"!][!//
                                    [!VAR "ChannelRangeSelect" = "node:value(./AdcChannelRangeSelect )"!][!//
                                    /* Limit checking is used for this channel */
                                    [!IF "($ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW') or ($ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH')"!][!//
                                        /* Limit checking range: Greater than the upper limit, Less than the lower limit */
                                        TRUE,
                                    [!ELSE!][!//
                                        /* Limit checking range: Less than the upper limit, Greater than the lower limit */
                                        FALSE,
                                    [!ENDIF!][!//
                                    /* Discard result out of range */
                                    FALSE,
                                [!ELSE!][!//
                                    /* Limit checking is not used for this channel */
                                    /* Less than the upper boundary, greater than the lower boundary is
                                    the threshold range */
                                    FALSE,
                                    /* Retain result out of range */
                                    TRUE,
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                /* Limit checking is not used for this channel */
                                /* Less than the upper boundary, greater than the lower boundary is
                                the threshold range */
                                FALSE,
                                /* Retain result out of range */
                                TRUE,
                            [!ENDIF!][!//
                            /* HDI not used */
                            SARADC_HDI_OFF
                            [!ENDINDENT!][!//
                        },
                        /* Channel[!"$ChannelNumber"!] configuration for runtime */
                        {
                            [!INDENT "12"!][!//
                            /* Channel ID */
                            SARADC_CHANNELRESULT[!"$ChannelNumber"!],
                            [!IF "../../AdcResultHandlingImplementation = 'DMA_MODE'"!][!//
                                /* Dma is used */
                                TRUE,
                            [!ELSE!][!//
                                /* Dma is unused */
                                FALSE,
                            [!ENDIF!][!//
                            [!IF "node:exists(./AdcChannelSyncConvEnable) and (./AdcChannelSyncConvEnable = 'true')"!][!//
                                /* Synchronize conversion is enabled */
                                TRUE,
                            [!ELSE!][!//
                                /* Synchronize conversion is unused */
                                FALSE,
                            [!ENDIF!][!//
                            [!IF "$AdcLimitCheckingEnSta = 'true'"!][!//
                                [!IF "$ChLimitCheck = 'true'"!][!//
                                    [!VAR "ChannelRangeSelect" = "node:value(./AdcChannelRangeSelect )"!][!//
                                    /* Limit checking is used for this channel */
                                    [!IF "($ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW') or ($ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH')"!][!//
                                        /* Limit checking range: Greater than the upper limit, Less than the lower limit */
                                        TRUE,
                                    [!ELSE!][!//
                                        /* Limit checking range: Less than the upper limit, Greater than the lower limit */
                                        FALSE,
                                    [!ENDIF!][!//
                                    /* Discard result out of range */
                                    FALSE,
                                [!ELSE!][!//
                                    /* Limit checking is not used for this channel */
                                    /* Less than the upper boundary, greater than the lower boundary is
                                    the threshold range */
                                    FALSE,
                                    /* Retain result out of range */
                                    TRUE,
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                /* Limit checking is not used for this channel */
                                /* Less than the upper boundary, greater than the lower boundary is
                                the threshold range */
                                FALSE,
                                /* Retain result out of range */
                                TRUE,
                            [!ENDIF!][!//
                            /* HDI not used */
                            SARADC_HDI_OFF
                            [!ENDINDENT!][!//
                        }
                        [!ENDINDENT!][!//
                    }[!//
                [!IF "num:i($ChannelCount) < (num:i(count(../*) - 1))"!],[!ENDIF!][!//

                [!VAR "ChannelCount" = "num:i($ChannelCount + 1)"!][!//
            [!ENDLOOP!][!//
            [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!/* Container: AdcHWUnitConfiguration */!][!//
        [!/* Configuration: ADC HW unit configuration structure */!][!//
        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "HwUnitName" = "./AdcHwUnitId"!][!//
            [!VAR "UnitId" = "num:i(text:split($HwUnitName, 'SARADC')[1])"!][!//
            [!VAR "HwunitResolution" = "text:split(./AdcResolution, 'BITS_')[1]"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                /* ADC [!"$UnitId"!] hardware unit configuration */
                static const Saradc_ModuleConfig Adc_HwUnit[!"$UnitId"!]HwCfg =
                {
                [!INDENT "4"!][!//
                /* Clock prescale */
                [!IF "node:exists(./AdcPrescale)"!][!//
                    [!"num:i((./AdcPrescale - 2) div 2)"!]U,
                [!ELSE!][!//
                    /* Default set to 14 */
                    14U,
                [!ENDIF!][!//
                /* Sample time */
                [!"./AdcKernelChSampleTime"!]U,
                /* Conversion Resolution */
                SARADC_RESOLUTION_[!"$HwunitResolution"!]BIT,
                [!IF "node:exists(./AdcSyncConvMode)"!][!//
                    [!IF "(./AdcSyncConvMode = 'ADC_SYNC_CONV_MASTER') or (./AdcSyncConvMode = 'ADC_STANDALONE')"!][!//
                        /* Synchronous conversion source - master or standalone */
                        SARADC_CONVERTER_MASTER,
                    [!ELSE!][!//
                        [!VAR "Var_MasterHwUnitNumber" = "text:split(node:ref(./AdcSyncConvMasterObject)/AdcHwUnitId, 'SARADC')[1]"!][!//
                        [!VAR "Var_SlaveHwUnitNumber" = "text:split(./AdcHwUnitId, 'SARADC')[1]"!][!//
                        [!IF "num:i($Var_MasterHwUnitNumber) >= num:i(8)"!][!//
                            [!VAR "Var_MasterHwUnitNumber" = "$Var_MasterHwUnitNumber - 8"!][!//
                        [!ELSEIF "num:i($Var_MasterHwUnitNumber) >= num:i(4)"!]
                            [!VAR "Var_MasterHwUnitNumber" = "$Var_MasterHwUnitNumber - 4"!][!//
                        [!ENDIF!][!//
                        [!IF "num:i($Var_SlaveHwUnitNumber) >= num:i(8)"!][!//
                            [!VAR "Var_SlaveHwUnitNumber" = "$Var_SlaveHwUnitNumber - 8"!][!//
                        [!ELSEIF "num:i($Var_SlaveHwUnitNumber) >= num:i(4)"!]
                            [!VAR "Var_SlaveHwUnitNumber" = "$Var_SlaveHwUnitNumber - 4"!][!//
                        [!ENDIF!][!//
                        /* Synchronous conversion source - slave */
                        SARADC_CONVERTER_SLAVE[!"ecu:list(concat('Adc.SyncGroup.Master.SARADC', num:i($Var_MasterHwUnitNumber)))[num:i($Var_SlaveHwUnitNumber + 1)]"!],
                    [!ENDIF!][!//
                [!ELSE!][!//
                    /* Synchronous conversion source - unused */
                    SARADC_CONVERTER_MASTER,
                [!ENDIF!][!//
                /* Request queue configuration */
                {
                    [!INDENT "8"!][!//
                    /* Request queue 0 */
                    {
                        [!INDENT "12"!][!//
                            /* Priority */
                            SARADC_QUEUEPRIORITY_[!"AdcRequestSource0Prio"!],
                            /* Start mode */
                            SARADC_STARTMODE_CANCELINJECTREPEAT,
                            /* Arbitration queue is enable */
                            TRUE
                        [!ENDINDENT!][!//
                    },
                    /* Request queue 1 */
                    {
                        [!INDENT "12"!][!//
                            /* Priority */
                            SARADC_QUEUEPRIORITY_[!"AdcRequestSource1Prio"!],
                            /* Start mode */
                            SARADC_STARTMODE_CANCELINJECTREPEAT,
                            /* Arbitration queue is enable */
                            TRUE
                        [!ENDINDENT!][!//
                    },
                    /* Request queue 2 */
                    {
                        [!INDENT "12"!][!//
                            /* Priority */
                            SARADC_QUEUEPRIORITY_[!"AdcRequestSource2Prio"!],
                            /* Start mode */
                            SARADC_STARTMODE_CANCELINJECTREPEAT,
                            /* Arbitration queue is enable */
                            TRUE,
                        [!ENDINDENT!][!//
                    }
                    [!ENDINDENT!][!//
                }
                [!/* Module Clock control. Divider Factor for Analog Internal Clock (fADCI) */!][!//
                [!VAR "AdcSpbClock" = "node:value(node:ref(../../AdcAnalogClockSource)/McuClockReferencePointFrequency)"!][!//
                [!IF "node:exists(./AdcPrescale)"!][!//
                    [!VAR "AdcfadciClock" = "($AdcSpbClock) div 1000000 div num:i(./AdcPrescale)"!][!//
                [!ELSE!][!//
                    [!VAR "AdcfadciClock" = "($AdcSpbClock) div 1000000 div num:i(14)"!][!//
                [!ENDIF!][!//
                [!VAR "AdcfadciClock" = "num:i($AdcfadciClock * 100) div 100"!][!//
                [!ASSERT "$AdcfadciClock >= (ecu:get('Adc.AnalogClockMinMHz')) and $AdcfadciClock <= (ecu:get('Adc.AnalogClockMaxMHz'))"!][!//
                    123-000-01-ERROR: Invalid configuration. Analog clock (fADCI) for [!"node:name(.)"!] is ([!"$AdcfadciClock"!]MHz) out of range. Modify the AdcPrescale or AdcAnalogClockSource(in Mcu Module), such that Adc analog clock (fADCI) is within [!"ecu:get('Adc.AnalogClockMinMHz')"!]MHz to [!"ecu:get('Adc.AnalogClockMaxMHz')"!]MHz.
                [!ENDASSERT!][!//
                [!ENDINDENT!][!//
                };

            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!IF "$AdcSyncGroupEnSta = 'true'"!][!//
            [!/* Sync group mapping relationship */!][!//
            [!LOOP "node:order(as:modconf('Adc')/AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
                [!VAR "Var_MasterHwUnitID" = "./AdcHwUnitId"!][!//
                [!VAR "Var_MasterHwUnitName" = "node:name(.)"!][!//
                [!VAR "Var_MasterUnitId" = "num:i(text:split($Var_MasterHwUnitID, 'SARADC')[1])"!][!//
                [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
                [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                    [!IF "node:exists(./AdcSyncConvMode) and (./AdcSyncConvMode = 'ADC_SYNC_CONV_MASTER')"!][!//
                        [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
                        [!VAR "Var_MasterHwCoreID" = "num:i($AdcHwUnitMappedCoreId)"!][!//
                        [!VAR "Var_SyncGroupSlaveCnt" = "num:i(0)"!][!//
                        [!LOOP "node:order(as:modconf('Adc')/AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
                            [!VAR "UnitId" = "num:i(text:split($Var_MasterHwUnitID, 'SARADC')[1])"!][!//
                            [!IF "(./AdcHwUnitId != $Var_MasterHwUnitID)"!][!//
                                [!IF "(./AdcSyncConvMode = 'ADC_SYNC_CONV_SLAVE') and (node:ref(./AdcSyncConvMasterObject)/AdcHwUnitId = $Var_MasterHwUnitID)"!][!//
                                    [!VAR "Var_SyncGroupSlaveCnt" = "$Var_SyncGroupSlaveCnt + 1"!][!//
                                    [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
                                    [!VAR "Var_SlaveHwCoreID" = "num:i($AdcHwUnitMappedCoreId)"!][!//
                                    [!IF "num:i($Var_MasterHwCoreID) != num:i($Var_SlaveHwCoreID)"!][!//
                                        [!ERROR!][!//
                                            123-000-03-ERROR: All hardware units within a synchronous conversion group should be assigned to the same core(Master: [!"$Var_MasterHwUnitName"!]; Slave: [!"node:name(.)"!]).
                                        [!ENDERROR!][!//
                                        [!BREAK!][!//
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                        [!IF "num:i($Var_SyncGroupSlaveCnt) = num:i(0)"!][!//
                            [!ERROR!][!//
                                123-000-02-ERROR: No slaves assigned to master([!"$Var_MasterHwUnitName"!]).
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                        /* Slave HW unit ID configuration when sync group is used */
                        /* #Violation: Adc_PBcfg_c_REF_4 */
                        /* #Violation: Adc_PBcfg_c_REF_5 */
                        static const Adc_HwUnitType Adc_SyncGroupSlaveHwUnitMasterAdc[!"num:i($Var_MasterUnitId)"!]Core[!"$Var_CoreIdx"!][[!"num:i($Var_SyncGroupSlaveCnt + 1)"!]] =
                        {
                        [!INDENT "4"!][!//
                        /* Total number of all slaves */
                        [!"num:i($Var_SyncGroupSlaveCnt)"!],
                        [!/* Line feed */!]
                        /* Slave HW unit IDs */
                        [!VAR "Var_SlaveCnt" = "num:i(0)"!][!//
                        [!LOOP "node:order(as:modconf('Adc')/AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
                            [!IF "./AdcHwUnitId != $Var_MasterHwUnitID"!][!//
                                [!IF "(./AdcSyncConvMode = 'ADC_SYNC_CONV_SLAVE') and (node:ref(./AdcSyncConvMasterObject)/AdcHwUnitId = $Var_MasterHwUnitID)"!][!//
                                    [!"num:i(text:split(./AdcHwUnitId, 'SARADC')[1])"!]U[!//
                                    [!VAR "Var_SlaveCnt" = "num:i($Var_SlaveCnt + 1)"!][!//
                                    [!IF "num:i($Var_SlaveCnt) < num:i($Var_SyncGroupSlaveCnt)"!][!//
                                        ,
                                    [!ELSE!][!//
                                        [!/* Line feed */!]
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                        [!ENDINDENT!][!//
                        };
                        [!/* Line feed */!]
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//

        /* ADC HwUnit configuration parameters of Core[!"$Var_CoreIdx"!] */
        static const Adc_KernelConfigType Adc_HwUnitConfigSetCore[!"$Var_CoreIdx"!][ADC_MAX_HWUNIT_TO_CORE[!"$Var_CoreIdx"!]] =
        {
        [!VAR "Idx" = "num:i(0)"!][!//
        [!/* Generated in ascending of SARADC HwUnit */!][!//
        [!VAR "GroupIndex" = "num:i(0)"!][!//
        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "AdcHwUnitIdNum" = "text:split(./AdcHwUnitId, 'SARADC')[1]"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                [!VAR "Idx" = "$Idx + 1"!][!//
                [!INDENT "4"!][!//
                /* ADC [!"$AdcHwUnitIdNum"!] configuration */
                {
                    [!INDENT "8"!][!//
                        /* ADC HwUnit[!"$AdcHwUnitIdNum"!] */
                        ADC_HWUNIT_ADC[!"$AdcHwUnitIdNum"!],
                        [!IF "($Var_PollingModeEn = 'STD_ON') or ($Var_DmaModeEn = 'STD_ON')"!][!//
                            /* Result handling method of the HW unit */
                            ADC_RESULT_HANDLING_[!"./AdcResultHandlingImplementation"!],
                        [!ENDIF!][!//
                        /* Pointer to Adc Hw Unit configuration */
                        &Adc_HwUnit[!"$AdcHwUnitIdNum"!]HwCfg,
                        [!IF "$AdcSyncGroupEnSta = 'true'"!][!//
                            [!IF "node:exists(./AdcSyncConvMode) and (./AdcSyncConvMode = 'ADC_SYNC_CONV_MASTER')"!][!//
                                /* Pointer to the slave Hw units of sync group */
                                &Adc_SyncGroupSlaveHwUnitMasterAdc[!"num:i($AdcHwUnitIdNum)"!]Core[!"$Var_CoreIdx"!][0],
                            [!ELSE!][!//
                                /* Sync group slave or standalone */
                                NULL_PTR,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        /* [!"num:i(count(./AdcChannel/*))"!] channels */
                        [!"num:i(count(./AdcChannel/*))"!]U,
                        /* Pointer to the array of channel configuration */
                        &Adc_HwUnit[!"$AdcHwUnitIdNum"!]ChCfg[0U],
                        /* Pointer to the array of group configuration */
                        &Adc_HwUnit[!"$AdcHwUnitIdNum"!]GrpCfg[0U],
                        [!IF "$AdcPrioImp = 'ADC_PRIORITY_HW_SW'"!][!//
                            /* Pointer to the array of Group mask */
                            &Adc_HwUnit[!"$AdcHwUnitIdNum"!]GroupMask[0U],
                        [!ENDIF!][!//
                        /* Total number of configured groups */
                        ADC_CFG_GROUPS_HWUNIT_ADC[!"$AdcHwUnitIdNum"!],
                        /* Index of group start position in ADC HwUnit[!"$AdcHwUnitIdNum"!] in Core[!"$Var_CoreIdx"!] */
                        [!"$GroupIndex"!]U[!//
                        [!IF "($Var_DmaModeEn = 'STD_ON')"!][!//
                            ,
                            /* Interrupt enable status*/
                            [!IF "(./AdcResultHandlingImplementation = 'DMA_MODE')"!][!//
                                [!IF "(node:exists(./AdcDmaResultHandlingInterruptEnable) and (./AdcDmaResultHandlingInterruptEnable = 'true'))"!][!//
                                    /* Interrupt is enabled when in DMA mode */
                                    TRUE
                                [!ELSE!][!//
                                    /* Interrupt is disabled when in DMA mode */
                                    FALSE
                                [!ENDIF!][!//
                            [!ELSEIF "(./AdcResultHandlingImplementation = 'POLLING_MODE')"!][!//
                                /* Interrupt is always disabled when polling mode */
                                FALSE
                            [!ELSE!][!//
                                /* Interrupt is always enabled when interrupt */
                                TRUE
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            [!/* Line feed */!]
                        [!ENDIF!][!//
                    [!ENDINDENT!][!//
                    [!VAR "GroupIndex" = "num:i($GroupIndex + count(AdcGroup/*))"!][!//
                }[!IF "num:i($Idx) != num:i($CoreUsedForAdcHwUnitFlg)"!],[!ENDIF!]
                [!ENDINDENT!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        };

        /* Total ADC Hwunit number and configuration information in Core[!"$Var_CoreIdx"!] */
        static const Adc_CoreConfigType Adc_ConfigSetCore[!"$Var_CoreIdx"!] =
        {
            [!INDENT "4"!][!//
            /* Maximum number of the ADC HwUnit allocated to the core[!"$Var_CoreIdx"!] */
            ADC_MAX_HWUNIT_TO_CORE[!"$Var_CoreIdx"!],
            /* ADC HwUnit configuration information of core[!"$Var_CoreIdx"!] */
            &Adc_HwUnitConfigSetCore[!"$Var_CoreIdx"!][0]
            [!ENDINDENT!][!//
        };
        /* #Violation: Adc_PBcfg_c_REF_3 */
        #define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$Var_CoreIdx"!]_UNSPECIFIED
        /* #Violation: Adc_PBcfg_c_REF_1 */
        #include "Adc_MemMap.h"

    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDFOR!][!//
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
/*
This array is used for mapping Adc hardware unit to the Core.
Array index is Adc hardware unit ->
First member in the array is index of Adc_HwUnitConfigSetCorex[x=0~4];
Second member in the array is Core ID that the HW unit is mapped to.
*/
static const Adc_HWUnitCoreMapType Adc_HwUnitToCoreMap[ADC_MAX_KERNELS] =
{
    [!INDENT "4"!][!//
    [!VAR "AdcHwUnit2Core0Num" = "0"!][!//
    [!VAR "AdcHwUnit2Core1Num" = "0"!][!//
    [!VAR "AdcHwUnit2Core2Num" = "0"!][!//
    [!VAR "AdcHwUnit2Core3Num" = "0"!][!//
    [!VAR "TotalAdcHwUnitNum" = "num:i(ecu:get('Adc.MaxControllers'))"!][!//
    [!FOR "AdcHwUnitIndex" = "0" TO "num:i($TotalAdcHwUnitNum - 1)"!][!//
        [!VAR "AdcHwUnit2CoreNumIndex" = "num:i(255)"!][!//
        [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'num:i(text:split(./AdcHwUnitId, &apos;SARADC&apos;)[1])')"!][!//
            [!VAR "AdcHwUnitId" = "text:split(./AdcHwUnitId, 'SARADC')[1]"!][!//
            [!IF "num:i($AdcHwUnitId) = num:i($AdcHwUnitIndex)"!][!//
                [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
                [!IF "$AdcHwUnitMappedCoreId = num:i(0)"!][!//
                    [!VAR "AdcHwUnit2CoreNumIndex" = "num:i($AdcHwUnit2Core0Num)"!][!//
                    [!VAR "AdcHwUnit2Core0Num" = "$AdcHwUnit2Core0Num + 1"!][!//
                [!ELSEIF "$AdcHwUnitMappedCoreId = num:i(1)"!][!//
                    [!VAR "AdcHwUnit2CoreNumIndex" = "num:i($AdcHwUnit2Core1Num)"!][!//
                    [!VAR "AdcHwUnit2Core1Num" = "$AdcHwUnit2Core1Num + 1"!][!//
                [!ELSEIF "$AdcHwUnitMappedCoreId = num:i(2)"!][!//
                    [!VAR "AdcHwUnit2CoreNumIndex" = "num:i($AdcHwUnit2Core2Num)"!][!//
                    [!VAR "AdcHwUnit2Core2Num" = "$AdcHwUnit2Core2Num + 1"!][!//
                [!ELSEIF "$AdcHwUnitMappedCoreId = num:i(3)"!][!//
                    [!VAR "AdcHwUnit2CoreNumIndex" = "num:i($AdcHwUnit2Core3Num)"!][!//
                    [!VAR "AdcHwUnit2Core3Num" = "$AdcHwUnit2Core3Num + 1"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "num:i($AdcHwUnit2CoreNumIndex) = num:i(255)"!][!//
            /* ADC[!"$AdcHwUnitIndex"!] is not used */
            {255U, 255U}[!//
        [!ELSE!][!//
            /* ADC[!"$AdcHwUnitIndex"!] config info is assigned to Adc_HwUnitConfigSetCore[!"$AdcHwUnitMappedCoreId"!][[!"num:i($AdcHwUnit2CoreNumIndex)"!]], and mapped to CORE[!"num:i($AdcHwUnitMappedCoreId)"!] */
            {[!"num:i($AdcHwUnit2CoreNumIndex)"!]U, [!"$AdcHwUnitMappedCoreId"!]U}[!//
        [!ENDIF!][!//
        [!IF "num:i($AdcHwUnitIndex) != num:i(ecu:get('Adc.MaxControllers') - 1)"!],[!ENDIF!]
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//


[!/* Container: AdcConfiguration */!][!//
/*
ADC configuration data set
*/
[!INDENT "0"!][!//
const Adc_ConfigType Adc_ConfigSet[!"$Var_AdcConfigShortName"!][ADC_CONFIG_COUNT] =
{
    [!INDENT "4"!][!//
    [!SELECT "AdcConfigSet"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i(0)"!][!//
                [!IF "$Var_CoreIdx = num:i(0)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore0)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore1)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore2)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore3)"!][!//
                [!ENDIF!][!//
                [!IF "num:i($CoreUsedForAdcHwUnitFlg) != num:i(0)"!][!//
                    /* ADC configuration information of core[!"num:i($Var_CoreIdx)"!] */
                    &Adc_ConfigSetCore[!"num:i($Var_CoreIdx)"!][!//
                [!ELSE!][!//
                    /* No configuration information for core[!"num:i($Var_CoreIdx)"!] */
                    NULL_PTR[!//
                [!ENDIF!][!//
                [!IF "num:i($Var_CoreIdx) < num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                    ,
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        },
        /* Pointer to Adc HwUnit mapped to core configuration */
        &Adc_HwUnitToCoreMap[0]
        [!ENDINDENT!][!//
    }
    [!ENDSELECT!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!//
[!ENDSELECT!][!//
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
