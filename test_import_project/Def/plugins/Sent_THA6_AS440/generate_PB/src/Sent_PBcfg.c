/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Sent_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SENT
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/
/*
*#Violation Summary
*#Sent_PBCfg_c_REF_1:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Sent_PBCfg_c_REF_2:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Sent_PBCfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/
/****************************************************************************************************
 
****************************************************************************************************/
/*
  
 *
 ****************************************************************************************************/
/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/

 [!NOCODE!][!//
    [!INCLUDE "Sent.m"!][!//
    [!ENDNOCODE!][!//
[!AUTOSPACING!]
#include "Sent.h"

/****************************************************************************************************
 **                          Global Function Declarations                                           *
 ***************************************************************************************************/
[!NOCODE!][!//
[!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
[!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
    [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
        [!VAR "MaxSentChannels" = "num:i(0)"!][!//
        [!VAR "MaxSentChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//

    /* ConfigSet [!"num:i($SentId - 1)"!] */
    [!FOR "Channel" = "0" TO "num:i($MaxSentChannels)"!][!//
        [!SELECT "SentChannelConfigSet/*[num:i($Channel)]"!][!//
        [!VAR "SentCallOutFn" = "./SentChanCalloutFn"!][!//
        [!IF "string-length($SentCallOutFn) = 0"!][!//
            [!VAR "SentCallOutFn" = "'NULL_PTR'"!][!//
        [!ENDIF!][!//
        [!IF "num:isnumber($SentCallOutFn) = 'true'"!][!//
        [!ELSEIF "$SentCallOutFn != 'NULL_PTR' "!][!//
[!CODE!][!//
/* Application Callback function for SENT Channel[!"SentChLogiIndex"!] */
extern void [!"$SentCallOutFn"!] (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
[!ENDCODE!][!//
        [!ENDIF!]
        [!VAR "SentErrCallOutFn" = "./SentChanErrCalloutFn"!][!//
        [!IF "string-length($SentErrCallOutFn) = 0"!][!//
            [!VAR "SentErrCallOutFn" = "'NULL_PTR'"!][!//
        [!ENDIF!][!//
        [!IF "num:isnumber($SentErrCallOutFn) = 'true'"!][!//
        [!ELSEIF "$SentErrCallOutFn != 'NULL_PTR' "!][!//
[!CODE!][!//
/* Application Callback function for SENT Channel error[!"SentChLogiIndex"!] */
extern void [!"$SentErrCallOutFn"!] (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
[!ENDCODE!][!//
        [!ENDIF!]
        [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!ENDSELECT!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Sent')[1]"!][!//
    [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
    [!NOCODE!]
        [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
        [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
            [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//

            /*Channel Structure for selected Core*/
            [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!] 
            [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
                [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
                [!CALL "Sent_GetMasterCoreID"!][!//
                [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
[!CODE!][!//

#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
[!ENDCODE!][!// 

                    [!VAR "TotalChannels" = "num:i(0)"!][!//
                    [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
                    [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
                    [!FOR "ChannelNo" = "num:i(0)" TO "num:i($TotalChannels)"!][!//
                        [!SELECT "node:SentChannelConfigSet/*[num:i($ChannelNo)]"!][!//
                            [!VAR "NodeName" = "node:name(.)"!][!//
                            [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//

                            [!IF "$CGAllocationResult = 'TRUE'"!][!//  
                                [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
                                [!VAR "gtmChannel" = "'SENT_GTM_CHANNEL_0'"!][!//
                                [!IF "SPCConfig/SentChanUsedSpc = 'true'"!][!//
                                    [!IF "SPCConfig/SentTriggerMode = 'SENT_TRIGGER_MODE_GTM'"!][!//                                        
                                        [!VAR "gtmTrigerRefPoin" = "SPCConfig/SentGtmChannel"!][!//
                                        [!IF "text:contains(node:value(node:ref(./SPCConfig/SentGtmChannel)/GtmTriggerSelect),'TRI0')"!][!//                                      
                                            [!IF "text:contains(string(./SPCConfig/SentGtmChannel),'Saradc')"!][!//
                                                [!VAR "GtmTimerModuleChIndex" = "node:value(node:ref(./SPCConfig/SentGtmChannel)/ChannelId)"!][!//
                                                [!VAR "gtmChannel" = "concat('SENT_GTM_CHANNEL_', $GtmTimerModuleChIndex)"!][!//
                                            [!ELSE!]
                                                [!VAR "GtmTimerModuleChIndex" = "num:i(num:i(node:value(node:ref(./SPCConfig/SentGtmChannel)/ChannelId)) + 12)"!][!//
                                                [!IF "$GtmTimerModuleChIndex < 15"!][!//
                                                    [!"$GtmTimerModuleChIndex"!]
                                                    [!VAR "gtmChannel" = "concat('SENT_GTM_CHANNEL_', $GtmTimerModuleChIndex)"!][!//
                                                [!ELSE!][!//
                                                    [!ERROR!]
                                                        255-00-02-ERROR: You can only select GTM channel in GtmTriggerGroup_0 or Channel ID of Dsadc is 0, 1, 2.
                                                    [!ENDERROR!]
                                                [!ENDIF!][!//
                                            [!ENDIF!][!//
                                        [!ELSE!][!//
                                            [!ERROR!]
                                                255-00-02-ERROR: You can only select GTM channel in GtmTriggerGroup_0 or Channel ID of Dsadc is 0, 1, 2.
                                            [!ENDERROR!]
                                        [!ENDIF!][!//
                                [!ENDIF!][!//
[!CODE!][!//
/* Sent_Spc_Config for [!"$NodeName"!] */
static const Sent_Spc_Config SpcConfig[!"$ChannelNo"!] =
{
    [!"SPCConfig/SentTriggerMode"!], /* The trigger mode (SPC or GTM)  */
    [!"num:i(SentClocksPerTick)"!], /* per tick time in clock of SPC  */
    [!"$gtmChannel"!], /* Gtm channel for triggering SPC */
    0x02FAF07FUL /* Time out time for Gtm trigger */
};

[!ENDCODE!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDSELECT!][!//                        
                    [!ENDFOR!][!//


[!CODE!][!// 

[!IF "$MaxChannelsCore = num:i(0)"!][!//
[!ELSE!][!//
/*Channel Structure for selected Core*/
static const Sent_ChannelCfgType Sent_ChanConfig_Core[!"$CoreId"!][SENT_CHANNEL_COUNT_CORE[!"$CoreId"!]] =
{
[!ENDIF!][!//
[!ENDCODE!]      
     
                    [!VAR "TotalChannelPerCore"="num:i(0)"!][!//
                    [!FOR "ChannelNo" = "num:i(0)" TO "num:i($TotalChannels)"!][!//
                        [!SELECT "node:SentChannelConfigSet/*[num:i($ChannelNo)]"!][!//
                            [!VAR "NodeName" = "node:name(.)"!][!//
                            [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                            [!IF "$CGAllocationResult = 'TRUE'"!][!//
                                [!VAR "TotalChannelPerCore"="$TotalChannelPerCore + num:i(1)"!][!//
                            [!ENDIF!]
                        [!ENDSELECT!]
                    [!ENDFOR!]

                    [!VAR "curChannelInCore" = "num:i(0)"!][!//
                    [!FOR "ChannelNo" = "num:i(0)" TO "num:i($TotalChannels)"!][!//
                        [!SELECT "node:SentChannelConfigSet/*[num:i($ChannelNo)]"!][!//
                            [!VAR "NodeName" = "node:name(.)"!][!//
                            [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                            [!IF "$CGAllocationResult = 'TRUE'"!][!//
                                [!VAR "curChannelInCore"="$curChannelInCore + num:i(1)"!][!//
                                [!IF "SentChanFrameCrcDisable = 'true'"!][!//
                                    [!VAR "crcEnable" = "'SENT_CRC_ENABLE_OFF'"!][!//
                                [!ELSE!]
                                    [!VAR "crcEnable" = "'SENT_CRC_ENABLE_ON'"!][!//
                                [!ENDIF!][!//

                                [!IF "SentChanStatusNibbleCRCInc = 'true'"!][!//
                                    [!VAR "crcWith" = "'SENT_CRC_WITH_STATUS'"!][!//
                                [!ELSE!]
                                    [!VAR "crcWith" = "'SENT_CRC_WITH_OUT_STATUS'"!][!//
                                [!ENDIF!][!//

                                [!IF "SentChanIgnoreEndPulse = 'true'"!][!//
                                    [!VAR "pause" = "'SENT_PAUSE_DISABLE'"!][!//
                                [!ELSE!]
                                    [!VAR "pause" = "'SENT_PAUSE_ENABLE'"!][!//
                                [!ENDIF!][!//     

                                [!VAR "spcConfig" = "'NULL_PTR'"!][!//
                                [!VAR "EnableSpc" = "num:i(0)"!][!//
                                [!VAR "spcPlusWidth" = "num:i(0)"!][!//
                                [!IF "SPCConfig/SentChanUsedSpc = 'true'"!][!//                          
                                    [!VAR "spcConfig" = "concat('&SpcConfig', $ChannelNo)"!][!//                                 
                                    [!VAR "EnableSpc" = "num:i(1)"!][!//
                                    [!VAR "spcPlusWidth" = "num:i(SPCConfig/SentSpcPlusWidth)"!][!// 
                                [!ENDIF!][!//
          
                                [!VAR "Sentchannel"="node:name(.)"!][!//
[!CODE!][!//
[!IF "$MaxChannelsCore = num:i(0)"!][!//
[!ELSE!][!//
    /* Channel:[!"$Sentchannel"!] */
    {
        {
            {[!"SentChanCRCType"!], [!"$crcWith"!], [!"$crcEnable"!]}, /* CRC configuration */
            [!"concat('SENT_NIBBLES_NUM_', SentChanFrameDataLen)"!], /* SentChanFrameDataLen */
            [!"$pause"!],
            [!"SentChanInPulse"!], /* polarity */            
            [!"num:i(SentClocksPerTick * num:f(1.2))"!], /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            [!"num:i(SentClocksPerTick * num:f(0.8))"!],  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        [!"$spcConfig"!], 
        [!"$spcPlusWidth"!],
        [!"num:inttohex($EnableSpc)"!]U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        ([!"substring-after(SentChPhyIndex,"SENT")"!]U),
        /*Callback function ptr */
        [!"SentChanCalloutFn "!],
        [!"SentChanErrCalloutFn "!]        
                                    [!IF "num:i($curChannelInCore) != num:i($TotalChannelPerCore)"!]
    },
                                    [!ELSE!]
    }
                                    [!ENDIF!]
[!ENDIF!][!//
                                [!ENDCODE!][!//
                            [!ENDIF!][!//
                        [!ENDSELECT!][!//
                    [!ENDFOR!][!//
                    [!CODE!][!//
[!IF "$MaxChannelsCore = num:i(0)"!][!//
[!ELSE!][!//
};
[!ENDIF!][!//

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                        [!ENDCODE!]
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            [!ENDSELECT!][!//
        [!ENDFOR!][!//
  
    [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
    [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
        [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
            [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
            [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
                [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
                [!CALL "Sent_GetMasterCoreID"!][!//
                [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
                    [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
                    [!CALL "Sent_GetMasterCoreID"!][!//
                    [!VAR "TotalChannels" = "num:i(0)"!][!//
                    [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
                    [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
                    [!FOR "Channel" = "num:i(0)" TO "num:i($TotalChannels)"!]
                        [!SELECT "node:SentChannelConfigSet/*[num:i($Channel)]"!][!//
                            [!VAR "NodeName" = "node:name(.)"!][!//
                            [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                            [!IF "$CGAllocationResult = 'TRUE'"!][!//
                                [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
                            [!ENDIF!][!//
                        [!ENDSELECT!]
                    [!ENDFOR!]          
          
[!CODE!][!//

#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
static const Sent_CoreConfigType Sent_CoreConfigCore[!"$CoreId"!] =
{
    (Sent_ChannelIdxType)[!"num:i($MaxChannelsCore)"!]U,
                        [!IF "$MaxChannelsCore = num:i(0)"!][!//
    NULL_PTR
                        [!ELSE!][!//
    Sent_ChanConfig_Core[!"$CoreId"!]
                        [!ENDIF!][!//
};

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                    [!ENDCODE!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
        [!ENDSELECT!][!//
    [!ENDFOR!][!//
[!ENDNOCODE!]

#define SENT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
/* Data structure to hold core channel index map */
/* Allocation of the channels to different cores */
[!SELECT "SentConfigSet/*[num:i(1)]"!][!//
    [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
    [!NOCODE!]
        [!VAR "Module" = "'SENT'"!][!//
        [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
        [!VAR "CurrentIdx" = "num:i(0)"!][!//
        [!VAR "SentCore0Idx" = "num:i(0)"!][!//
        [!VAR "SentCore1Idx" = "num:i(0)"!][!//
        [!VAR "SentCore2Idx" = "num:i(0)"!][!//
        [!VAR "SentCore3Idx" = "num:i(0)"!][!//
        [!VAR "SentCore4Idx" = "num:i(0)"!][!//
        [!VAR "SentCore5Idx" = "num:i(0)"!][!//
        [!//
[!CODE!]
static const Sent_ChannelMapType Sent_ChannelLookUp[[!"num:i($TotalChannels)"!]] =      
{
[!ENDCODE!][!//

        [!CODE!]        
    /*CoreID, ChannelIndex*/           
        [!ENDCODE!]
        
        [!FOR "ChannelId" = "num:i(0)" TO "num:i($TotalChannels) - num:i(1)"!][!//
            [!SELECT "SentChannelConfigSet/*[SentChLogiIndex = num:i($ChannelId)]"!][!//
                [!VAR "NodeName" = "node:name(.)"!][!//
                [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
                    [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                    [!IF "$CGAllocationResult = 'TRUE'"!][!//
                        [!IF "$CoreId = num:i(0)"!][!//
                            [!VAR "CurrentIdx" = "$SentCore0Idx"!][!//
                            [!VAR "SentCore0Idx" = "$SentCore0Idx+num:i(1)"!][!//
                        [!ELSEIF "$CoreId = num:i(1)"!][!//
                            [!VAR "CurrentIdx" = "$SentCore1Idx"!][!//
                            [!VAR "SentCore1Idx" = "$SentCore1Idx+num:i(1)"!][!//
                        [!ELSE!][!//
                        [!ENDIF!][!//
                        
                        [!CODE!][!//
    {MULTICOREID_CPU[!"(num:i($CoreId))"!],[!"num:inttohex(number($CurrentIdx))"!]U}[!//
                            [!IF "num:i($ChannelId) != num:i($TotalChannels - 1)"!][!//
,
                            [!ENDIF!][!//
                            [!VAR "CurrentIdx" = "num:i(0)"!]
                        [!ENDCODE!]
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            [!ENDSELECT!][!//        
        [!ENDFOR!][!//    
    [!ENDNOCODE!]
    [!CR!][!//
};

[!ENDSELECT!][!//
[!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
[!CALL "Sent_GetMasterCoreID"!][!//
[!//
/* Physical to Logical channel mapping */
/* physical channel id is the index value of Sent_ChannelId and corresponding
   logical channel id in the channel configuration is stored */
[!VAR "SentMaxChannel" = "num:i(ecu:get('Sent.MaxChannelsSupported'))"!][!//
static const Sent_ChannelIdxType Sent_LogicalChannelId[SENT_HW_MAX_CHANNELS] =
{
    [!FOR "SentCounter" = "0" TO "num:i($SentMaxChannel - 1)"!][!//
        [!SELECT "SentConfigSet/*[num:i(1)]"!][!//
            [!IF "num:i(count(SentChannelConfigSet/*[SentChPhyIndex = concat('SENT',$SentCounter)])) = num:i(0)"!][!//
    0xFFU[!//
            [!ELSE!][!//
                [!LOOP "SentChannelConfigSet/*[SentChPhyIndex = concat('SENT',$SentCounter)]"!][!//
    [!"node:value(./SentChLogiIndex)"!]U[!//
                [!ENDLOOP!]
            [!ENDIF!][!//
            [!IF "num:i($SentCounter) != num:i($SentMaxChannel - 1)"!][!//
,
            [!ELSE!]
            [!ENDIF!][!//
        [!ENDSELECT!][!//
    [!ENDFOR!][!//
[!CR!][!//
};

/* Logical to physical channel mapping */
/* Logical id is the index value hardware channel id and
   physical id is the mapping to the configured channel in sequence */
[!VAR "SentMaxChannel" = "num:i(count(SentConfigSet/*[1]/SentChannelConfigSet/*))"!][!//
static const Sent_ChannelIdxType Sent_PhyChannelId[SENT_MAX_CHANNELS_CONFIGURED] =
{
[!VAR "SentCounter" = "num:i(0)"!]
[!LOOP "SentConfigSet/*[1]/SentChannelConfigSet/*"!][!//
    [!VAR "SentCounter" = "num:i($SentCounter + 1)"!]
    [!"substring-after(node:value(./SentChPhyIndex),"SENT")"!]U[!//
    [!IF "num:i($SentCounter) != num:i($SentMaxChannel)"!][!//
,
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!CR!][!//
};
[!ENDSELECT!][!//

/* SENT Module Configuration */[!//
[!/*const Sent_ConfigType Sent_Config = */!][!//
[!IF "variant:name() != ''"!][!//
const Sent_ConfigType Sent_ConfigSet_[!"variant:name()"!] =
[!ELSE!]
const Sent_ConfigType Sent_ConfigSet =
[!ENDIF!]
{
[!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
    [!CALL "Sent_GenerateModuleMap", "Module"="'SENT'"!][!//
    {
        [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
            [!INDENT "8"!][!//
            [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
            [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
                &Sent_CoreConfigCore[!"$CoreId"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!]
            [!ELSE!][!//
                NULL_PTR[!//
                [!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
,      
                [!ENDIF!]
            [!ENDIF!][!//

            [!ENDINDENT!][!//
        [!ENDFOR!][!//
        [!CR!][!//
    },
    /* SENT channels configured */
    [!NOCODE!][!//
    //[!VAR "MaxSentChannels" = "num:i(0)"!][!//
    [!VAR "MaxSentChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
    [!ENDNOCODE!][!//
    ([!"$MaxSentChannels"!]U),
    /* Channel Id to the core sequence mapping */
    Sent_ChannelLookUp,
    /* Physical to Logical Id mapping */
    Sent_LogicalChannelId,
    /* Logical to Physical ID mapping */
    Sent_PhyChannelId
[!ENDSELECT!][!//
};

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/
