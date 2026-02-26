/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FLS module
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
*#Fls_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Fls_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*#Fls_PBcfg_c_REF_3:CertC-DL06-C;
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Fls_PBcfg_c_REF_4:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*/

[!NOCODE!][!//
[!INCLUDE "Fls.m"!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fls.h"
#include "Fls_Cfg.h"
[!AUTOSPACING!][!//

/***************************************************************************************************
*                         Function declaration
***************************************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
  [!SELECT "as:modconf('Fls')[1]/FlsConfigSet"!][!//
    [!IF "node:exists(./FlsJobEndNotification) = 'true'"!][!//
      [!VAR "Notification1" = "./FlsJobEndNotification"!][!//
    [!ELSE!][!//
      [!VAR "Notification1" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notification1) = 0"!][!//
      [!VAR "Notification1" = "'(Fls_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
    [!IF "$Notification1 = '"NULL"' or $Notification1 = 'NULL'or $Notification1 = 'NULL_PTR' or $Notification1 = ''"!][!//
      [!VAR "Notification1" = "'(Fls_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
    [!IF "$Notification1 != '(Fls_NotifFunctionPtrType)0'"!][!//
      [!IF "num:isnumber($Notification1) != 'true'"!][!//
        [!WS"0"!]/* Function declaration of Fls Job End Notification */
        [!WS"0"!]extern void [!"$Notification1"!](void);
      [!ENDIF!][!//
    [!ELSE!][!//
        [!WS"0"!]/* Fls Job End Notification Function is not configured */
    [!ENDIF!][!//

[!IF "node:exists(./FlsJobErrorNotification) = 'true'"!][!//
  [!VAR "Notification2" = "./FlsJobErrorNotification"!][!//
[!ELSE!][!//
  [!VAR "Notification2" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($Notification2) = 0"!][!//
  [!VAR "Notification2" = "'(Fls_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification2 = '"NULL"' or $Notification2 = 'NULL' or $Notification2 = 'NULL_PTR' or $Notification2 = ''"!][!//
  [!VAR "Notification2" = "'(Fls_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification2 != '(Fls_NotifFunctionPtrType)0'"!][!//
  [!IF "num:isnumber($Notification2) != 'true'"!][!//
    [!WS"0"!]/* Function declaration of Fls Job Error Notifications */
    [!WS"0"!]extern void [!"$Notification2"!](void);
  [!ENDIF!][!//
[!ELSE!][!//
    [!WS"0"!]/* Fls Job Error Notification Function is not configured */
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDSELECT!][!//

/***************************************************************************************************
*                               Local Constants
****************************************************************************************************/
[!CALL "CG_CalculateFlsSectorListNumber"!][!//

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/* #Violation: Fls_PBcfg_c_REF_3 */
/* #Violation: Fls_PBcfg_c_REF_4 */
static const Fls_SectorConfigType Fls_SectorList[[!"$FlsSectorListNumber"!]U] = 
{
[!CODE!][!//
[!VAR "FlsSectorListTmpNumber" =  "num:i(0)"!][!//
[!LOOP "node:order(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/*, 'FlsSectorStartaddress')"!][!//
    [!INDENT "4"!][!//
    /* configuration of ([!"node:name(.)"!]) */
    {
      [!INDENT "8"!][!//
      /* Start address of the this FlsSector */
      [!"node:value(./FlsSectorStartaddress)"!]U,
      /* Size of the sector */
      [!"node:value(./FlsSectorSize)"!]U,
      /* Size of flash page size */
      [!"node:value(./FlsPageSize)"!]U,
      /* End address of the this FlsSector */
      [!"num:i(num:i(./FlsSectorSize) * num:i(./FlsNumberOfSectors) + num:i(./FlsSectorStartaddress) - num:i('1'))"!]U
      [!ENDINDENT!][!//
      [!VAR "FlsSectorListTmpNumber" = "num:i($FlsSectorListTmpNumber + 1)"!][!//
    }[!IF "$FlsSectorListTmpNumber != $FlsSectorListNumber"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
};
[!ENDCODE!][!//

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/* Fls Configuration structure */
/* The job processing callback notifications shall be configurable as function pointers
   within the initialization data structure (Fls_ConfigType). [SWS_Fls_00109] */
[!IF "variant:name() != ''"!][!//
const Fls_ConfigType Fls_ConfigSet_[!"variant:name()"!][FLS_CONFIG_COUNT] =
[!ELSE!][!//
const Fls_ConfigType Fls_ConfigSet[FLS_CONFIG_COUNT] =
[!ENDIF!][!//
{
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!VAR "FlsAcLoadOnJobStart" =  "FlsGeneral/FlsAcLoadOnJobStart"!][!//
[!VAR "FlsTimeoutSupervisionEnabled" =  "FlsGeneral/FlsTimeoutSupervisionEnabled"!][!//
[!//
[!//
[!VAR "PostBuildType" = "'SELECTABLE'"!][!//
[!//
[!SELECT "FlsConfigSet"!][!//
[!CALL "FLS_CheckMaxOperateNumber"!][!//
[!VAR "FlsMaxReadFastMode" =  "./FlsMaxReadFastMode"!][!//
[!VAR "FlsMaxReadNormalMode" =  "./FlsMaxReadNormalMode"!][!//
[!VAR "FlsMaxWriteFastMode" =  "./FlsMaxWriteFastMode"!][!//
[!VAR "FlsMaxWriteNormalMode" =  "./FlsMaxWriteNormalMode"!][!//
    {
        /* Fast Mode : Maximum number of bytes to Read in one cycle */
        [!"$FlsMaxReadFastMode"!]U,
        /* Slow Mode : Maximum number of bytes to Read in one cycle */
        [!"$FlsMaxReadNormalMode"!]U,
        /* Fast Mode : Maximum number of bytes to Write in one cycle */
        [!"$FlsMaxWriteFastMode"!]U,
        /* Slow Mode : Maximum number of bytes to Write in one cycle */
        [!"$FlsMaxWriteNormalMode"!]U,
[!NOCODE!][!//
    [!/* Notification Check */!][!//
    [!IF "node:exists(as:modconf('Fee'))"!][!//
      [!IF "node:exists(./FlsJobEndNotification)"!][!//
        [!IF "node:exists(./FlsJobErrorNotification)"!][!//
          [!IF "'Fee_JobEndNotification' = ./FlsJobEndNotification"!][!//
            [!IF "'Fee_JobErrorNotification' = ./FlsJobErrorNotification"!][!//
              [!// Check OK
            [!ELSE!][!//
              [!ERROR!][!//
                ERROR: When using FEE, the Error notification function must be set to "Fee_JobErrorNotification".[!//
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!ERROR!][!//
              ERROR: When using FEE, the End notification function must be set to "Fee_JobEndNotification".[!//
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!ERROR!][!//
            ERROR: When using FEE, the Error notification function must be enabled.[!//
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!ERROR!][!//
          ERROR: When using FEE, the End notification function must be enabled.[!//
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FlsJobEndNotification */!][!//
    [!IF "node:exists(./FlsJobEndNotification)"!][!//
      [!VAR "EndNotification" = "./FlsJobEndNotification"!][!//
    [!ELSE!][!//
      [!VAR "EndNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($EndNotification) = 0 or $EndNotification = '"NULL"' or $EndNotification = 'NULL' or $EndNotification = 'NULL_PTR'"!][!//
      [!VAR "EndNotification" = "'(Fls_NotifFunctionPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($EndNotification)= 'true'"!][!//
          ERROR: Under LOADABLE option FlsJobEndNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "EndNotification" = "concat('(Fls_NotifFunctionPtrType)',($EndNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($EndNotification)!= 'true'"!][!//
          ERROR: Under SELECTABLE option FlsJobEndNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "EndNotification" = "$EndNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FlsJobErrorNotification */!][!//
    [!IF "node:exists(./FlsJobErrorNotification)"!][!//
      [!VAR "ErrorNotification" = "./FlsJobErrorNotification"!][!//
    [!ELSE!][!//
      [!VAR "ErrorNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($ErrorNotification) = 0 or $ErrorNotification = '"NULL"' or $ErrorNotification = 'NULL' or $ErrorNotification = 'NULL_PTR'"!][!//
      [!VAR "ErrorNotification" = "'(Fls_NotifFunctionPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($ErrorNotification)= 'true'"!][!//
          ERROR: Under LOADABLE option FlsJobErrorNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "ErrorNotification" = "concat('(Fls_NotifFunctionPtrType)',($ErrorNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($ErrorNotification)!= 'true'"!][!//
          ERROR: Under SELECTABLE option FlsJobErrorNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "ErrorNotification" = "$ErrorNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
[!//
        /* Job End Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$EndNotification = '(Fls_NotifFunctionPtrType)0'"!][!//
        [!"$EndNotification"!],
[!ELSE!][!//
        [!"$EndNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($EndNotification)"!]U,
[!ENDIF!][!//
[!//
        /* Job Error Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$ErrorNotification = '(Fls_NotifFunctionPtrType)0'"!][!//
        [!"$ErrorNotification"!],
[!ELSE!][!//
        [!"$ErrorNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($ErrorNotification)"!]U,
[!ENDIF!][!//
[!IF "$FlsTimeoutSupervisionEnabled = 'true'"!][!//
        /* FlsCallCycle for timeout monitoring, convert to us by multiplying by 1000 * 1000 */
[!VAR "CallCycle" = "FlsCallCycle"!][!//
[!VAR "CallCycle" = "$CallCycle * 1000 * 1000"!][!//
        [!"num:i($CallCycle)"!]U,[!//
[!ENDIF!][!// 
        /* Default mode of FLS driver */
        [!"FlsDefaultMode"!],
        /* Pointer of FlsSector configuration */
        &Fls_SectorList[0U],
        /* Number of FlsSector */
        [!"$FlsSectorListNumber"!]U
    }
[!ENDSELECT!][!//
[!//
[!ENDSELECT!][!//
};

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
