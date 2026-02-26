/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Sent_Cfg.h
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
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Sent_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*/

#ifndef SENT_CFG_H_
#define SENT_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!//
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
  [!SELECT "as:modconf('Sent')[1]"!][!//
    [!//
    [!NOCODE!][!//
      [!INCLUDE "..\Sent.m"!][!//
    [!ENDNOCODE!][!//
    [!//
    [!NOCODE!][!//
      [!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
      [!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
      [!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!][!//
      /* AUTOSAR specification version numbers */
      #define SENT_CFG_AR_RELEASE_MAJOR_VERSION  ([!"substring-after($AsMajorVersion, ' ')"!]U)
      #define SENT_CFG_AR_RELEASE_MINOR_VERSION  ([!"$AsMinorVersion"!]U)
      #define SENT_CFG_AR_RELEASE_PATCH_VERSION  ([!"$AsRevisionVersion"!]U)
    [!NOCODE!][!//
      [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
      [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
      [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!]

    /* Vendor specific implementation version information */
    #define SENT_CFG_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
    #define SENT_CFG_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
    #define SENT_CFG_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)

    #define SENT_CFG_VENDOR_ID                 ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
    #define SENT_CFG_MODULE_ID                 ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

    /*
    Container : SentGeneralConfiguration
    */
    /*
      The following macros will enable or disable a particular feature
      in SENT module.
      Set the macro to ON to enable the feature and OFF to disable the same.
    */
    /*
    Configuration: SENT_SAFETY_ENABLE
    Preprocessor switch for enabling the safety development error detection and
    reporting.
    - if STD_ON, DET is Enabled
    - if STD_OFF,DET is Disabled
    */
    #define SENT_SAFETY_ENABLE  [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentSafetyErrorDetect"!][!//
    /*
    Configuration: SENT_DEV_ERROR_DETECT
    Preprocessor switch for enabling the development error detection and
    reporting.
    - if STD_ON, DET is Enabled
    - if STD_OFF,DET is Disabled
    */
   #define SENT_DEV_ERROR_DETECT  [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentDevErrorDetect"!][!//
    /* Configuration: SENT_DEINIT_API
    Sent_DeInit API configuration
    - if STD_ON, DeInit API is Enabled
    - if STD_OFF, DeInit API is Disabled
    */
    #define SENT_DEINIT_API        [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentDeInitApi"!][!//

    /* Configuration: SENT_VERSION_INFO_API
    Version Information API configuration
    - if STD_ON, VersionInfo API is Enabled
    - if STD_OFF, VersionInfo API is Disabled
    */
    #define SENT_VERSION_INFO_API  [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentVersionInfoApi"!][!//

    /* Configuration: SENT_SPC_USED
    SENT SPC Feature configuration
    - if STD_ON, SPC feature is Enabled
    - if STD_OFF, SPC feature is Disabled
    */
    #define SENT_SPC_USED         [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentSpcFeatureSupport"!][!//

    /* Configuration: SENT_HW_MAX_CHANNELS
    Maximum number of SENT physical channels supported
    */
    #define SENT_HW_MAX_CHANNELS   ([!"ecu:get('Sent.MaxChannelsSupported')"!]U)

    /* Configuration: SENT MODULE INSTANCE ID */
    /* #Violation: Sent_Cfg_h_REF_1 */
    #define SENT_INSTANCE_ID       ((uint8)[!"SentGeneral/SentIndex"!])

    /* Total no. of config sets */
    /* #Violation: Sent_Cfg_h_REF_1 */
    #define SENT_CONFIG_COUNT    ([!"num:i(count(SentConfigSet/*))"!]U)
    [!NOCODE!][!//
      [!/* Collect core-channel mappings from Resource Manager. */!]
      [!CALL "Sent_GenerateModuleMap", "Module"="'SENT'"!][!//
      [!CALL "Sent_GetMasterCoreID"!][!//
      [!SELECT "as:modconf('Sent')[1]/SentConfigSet/SentChannelConfigSet/*"!]
        [!/* Append the missing resources to master core */!]
        [!CALL "Sent_ValidateChAllocation", "Item" = "node:name(node:current())"!][!//
        [!IF "$CGResult = 'FALSE'"!]
          [!VAR "CGModuleMap" = "concat($CGModuleMap, 'CORE', $CGMasterCoreId, '_', node:name(node:current()), '#,')"!][!//
          [!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
          [!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
            [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
          [!ENDIF!]
        [!ENDIF!]
      [!ENDSELECT!]
      [!/* If no resource is allocated to master core, add master core to CGCoreUsed as dummy core */!]
      [!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
      [!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
        [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
      [!ENDIF!]
      [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
    [!ENDNOCODE!][!//
    [!CR!]
    /* Configuration: Resource
    The configuration contains allocation of Sent channels across cores.
    - if STD_ON, atleast one sent channel is configured in the core.
    - if STD_OFF, no sent channels are configured in the core. */
    [!NOCODE!][!//
      [!FOR "CoreIndex" = "num:i(1)" TO "num:i(2)"!][!//
        [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!]
        [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
        [!IF "text:match($CGCoreUsed, $matchCore)"!] [!// Fetch all strings matching the core.
          [!CODE!]
            /* #Violation: Sent_Cfg_h_REF_1 */
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_ON)
          [!ENDCODE!]
        [!ELSE!]
          [!CODE!]
            /* #Violation: Sent_Cfg_h_REF_1 */
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_OFF)
          [!ENDCODE!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDNOCODE!]
    [!CR!]
    /*
       Configuration:Max channels configured for Sent, max channels are same across
       variants.
    */
    [!NOCODE!][!//
      [!ASSERT "count(SentConfigSet/*)!=num:i(0)"!][!//
          255-00-01-ERROR: You should configure at least one SENT instance. Please add instance in /Sent/SentConfigSet."!][!//
      [!ENDASSERT!][!//
      [!SELECT "SentConfigSet/*"!][!//
        [!VAR "MaxChannels"= "num:i(count(SentChannelConfigSet/*))"!][!//
      [!ENDSELECT!][!//
    [!ENDNOCODE!][!//

    /* Sent Max Channels macro */
    #define SENT_MAX_CHANNELS_CONFIGURED         ((Sent_ChannelIdxType)[!"$MaxChannels"!])
    /* Number of Cores confgiured for Sent */
    [!VAR "MaxChannelsCore" = "num:i(255)"!][!//
    [!FOR "CoreId" = "num:i(0)" TO "$MaxCoreConfigured - num:i(1)"!][!//
      [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
      [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId) or ($CoreId < ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
        [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
        [!VAR "Module" = "'SENT'"!][!//
        [!SELECT "SentChannelConfigSet/*[SentChLogiIndex= num:i($ChannelId)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
          [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
          [!ENDIF!]
        [!ENDSELECT!]
      [!ENDIF!]
    [!ENDFOR!]
    [!CALL "Sent_PrintMasterCoreID"!][!//
    [!CALL "Sent_CGCalculateTotalChannelPerCore"!][!//
    [!CALL "Sent_CGCalculateChannelMasterCore"!][!//
/* The physical sent channels used. */
[!NOCODE!][!//
    [!VAR "SentMaxChannel" = "num:i(ecu:get('Sent.MaxChannelsSupported'))"!][!//
    [!FOR "SentCounter" = "0" TO "num:i($SentMaxChannel - 1)"!][!//
        [!SELECT "SentConfigSet/*[num:i(1)]"!][!//
             [!IF "num:i(count(SentChannelConfigSet/*[SentChPhyIndex = concat('SENT',$SentCounter)])) = num:i(0)"!][!//
[!CODE!][!//
#define SENT_INST0_CHAN[!"num:i($SentCounter)"!]                  (STD_OFF)
[!ENDCODE!][!//
             [!ELSE!][!//
[!CODE!][!//
#define SENT_INST0_CHAN[!"num:i($SentCounter)"!]                  (STD_ON)
[!ENDCODE!][!//
             [!ENDIF!][!//
        [!ENDSELECT!][!//
    [!ENDFOR!][!//
[!ENDNOCODE!]
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
**                          Global Function Declarations                                           **
****************************************************************************************************/
  [!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif  /* SENT_CFG_H */
/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/

