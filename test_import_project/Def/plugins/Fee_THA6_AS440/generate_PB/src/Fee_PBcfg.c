/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee_Cfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FEE module
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
*#Fee_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Fee_PBcfg_c_REF_2:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Fee_PBcfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Fee.m"!][!//
[!ENDNOCODE!][!//

#include "Fee.h"
#include "Fee_Cfg.h"

/****************************************************************************************************
*                         Function declaration                                                     **
****************************************************************************************************/
[!SELECT "as:modconf('Fee')[1]"!][!//
[!VAR "PostBuildType" = "'SELECTABLE'"!][!//
[!//

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
#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_PBcfg_c_REF_3 */
#include "Fee_MemMap.h"

[!//
[!VAR "Count" = "'0'"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
[!VAR "Count" = "$Count + '1'"!][!//
[!ENDLOOP!][!//
[!//
[!VAR "temp_count" = "'0'"!][!//

static const Fee_BlockConfigType Fee_BlockConfig[FEE_MAX_BLOCK_COUNT] =
{
[!LOOP "FeeBlockConfiguration/*"!][!//
    {
[!VAR "imm" = "FeeImmediateData"!][!//
[!VAR "blk_num" = "FeeBlockNumber"!][!//
[!VAR "blk_size" = "FeeBlockSize"!][!//
[!VAR "blk_cycle_count" = "FeeNumberOfWriteCycles"!][!//
        [!"$blk_cycle_count"!]U,     /* Block Cycle Count */
        [!"$blk_num"!]U,     /* Block number */
        [!"$blk_size"!]U,     /* Fee Block Size */
[!IF "$imm = 'true'"!][!//
        TRUE,    /* immediate */
[!ELSE!][!//
        FALSE,   /* normal */
[!ENDIF!][!//
[!VAR "temp_count" = "$temp_count + '1'"!][!//
[!IF "$temp_count = $Count"!][!//
    }
[!ELSE!][!//
    },
[!ENDIF!][!//
[!ENDLOOP!][!//
};

[!ENDSELECT!][!//
/* #Violation: Fee_PBcfg_c_REF_2 */
const Fee_ConfigType Fee_ConfigSet[FEE_CONFIG_COUNT] =
{
    {
        /* The number of configuration block */
        [!"num:i(count(FeeBlockConfiguration/*))"!]U,
        /* The block configuration */
        Fee_BlockConfig,
[!NOCODE!][!//
    [!SELECT "as:modconf('Fee')[1]"!][!//
    [!SELECT "FeeGeneral"!][!//
    [!/* FeeNvmJobEndNotification*/!][!//
    [!IF "node:exists(./FeeNvmJobEndNotification)"!][!//
      [!VAR "EndNotification" = "./FeeNvmJobEndNotification"!][!//
    [!ELSE!][!//
      [!VAR "EndNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($EndNotification) = 0 or $EndNotification = '"NULL"' or $EndNotification = 'NULL' or $EndNotification = 'NULL_PTR'"!][!//
      [!VAR "EndNotification" = "'(Fee_NotificationPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($EndNotification)= 'true'"!][!//
          21-00-05-ERROR: Under LOADABLE option FeeNvmJobEndNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "EndNotification" = "concat('(Fee_NotificationPtrType)',($EndNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($EndNotification)!= 'true'"!][!//
          21-00-06-ERROR: Under SELECTABLE option FeeNvmJobEndNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "EndNotification" = "$EndNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FeeNvmJobErrorNotification */!][!//
    [!IF "node:exists(./FeeNvmJobErrorNotification)"!][!//
      [!VAR "ErrorNotification" = "./FeeNvmJobErrorNotification"!][!//
    [!ELSE!][!//
      [!VAR "ErrorNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($ErrorNotification) = 0 or $ErrorNotification = '"NULL"' or $ErrorNotification = 'NULL' or $ErrorNotification = 'NULL_PTR'"!][!//
      [!VAR "ErrorNotification" = "'(Fee_NotificationPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($ErrorNotification)= 'true'"!][!//
          21-00-07-ERROR: Under LOADABLE option FeeNvmJobErrorNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "ErrorNotification" = "concat('(Fee_NotificationPtrType)',($ErrorNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($ErrorNotification)!= 'true'"!][!//
          21-00-08-ERROR: Under SELECTABLE option FeeNvmJobErrorNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "ErrorNotification" = "$ErrorNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FeeUnavailableFailureNotification */!][!//
    [!IF "node:exists(./FeeUnavailableFailureNotification)"!][!//
      [!VAR "UnavailableFailureNotification" = "./FeeUnavailableFailureNotification"!][!//
    [!ELSE!][!//
      [!VAR "UnavailableFailureNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($UnavailableFailureNotification) = 0 or $UnavailableFailureNotification = '"NULL"' or $UnavailableFailureNotification = 'NULL' or $UnavailableFailureNotification = 'NULL_PTR'"!][!//
      [!VAR "UnavailableFailureNotification" = "'(Fee_NotificationPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($UnavailableFailureNotification)= 'true'"!][!//
          21-00-09-ERROR: Under LOADABLE option FeeUnavailableFailureNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "UnavailableFailureNotification" = "concat('(Fee_NotificationPtrType)',($UnavailableFailureNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($UnavailableFailureNotification)!= 'true'"!][!//
          21-00-10-ERROR: Under SELECTABLE option FeeUnavailableFailureNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
      [!ENDASSERT!][!//
      [!VAR "UnavailableFailureNotification" = "$UnavailableFailureNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FeeDiscoverNonErasableAreasNotification */!][!//
    [!IF "node:exists(./FeeDiscoverNonErasableAreasNotification)"!][!//
      [!VAR "DiscoverNonErasableAreasNotification" = "./FeeDiscoverNonErasableAreasNotification"!][!//
    [!ELSE!][!//
      [!VAR "DiscoverNonErasableAreasNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($DiscoverNonErasableAreasNotification) = 0 or $DiscoverNonErasableAreasNotification = '"NULL"' or $DiscoverNonErasableAreasNotification = 'NULL' or $DiscoverNonErasableAreasNotification = 'NULL_PTR'"!][!//
      [!VAR "DiscoverNonErasableAreasNotification" = "'(Fee_NotificationPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($DiscoverNonErasableAreasNotification)= 'true'"!][!//
          21-00-11-ERROR: Under LOADABLE option FeeDiscoverNonErasableAreasNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "DiscoverNonErasableAreasNotification" = "concat('(Fee_NotificationPtrType)',($DiscoverNonErasableAreasNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($DiscoverNonErasableAreasNotification)!= 'true'"!][!//
          21-00-12-ERROR: Under SELECTABLE option FeeDiscoverNonErasableAreasNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "DiscoverNonErasableAreasNotification" = "$DiscoverNonErasableAreasNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* FeeNotFoundManagementInfoNotification */!][!//
    [!IF "node:exists(./FeeNotFoundManagementInfoNotification)"!][!//
      [!VAR "NotFoundManagementInfoNotification" = "./FeeNotFoundManagementInfoNotification"!][!//
    [!ELSE!][!//
      [!VAR "NotFoundManagementInfoNotification" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($NotFoundManagementInfoNotification) = 0 or $NotFoundManagementInfoNotification = '"NULL"' or $NotFoundManagementInfoNotification = 'NULL' or $NotFoundManagementInfoNotification = 'NULL_PTR'"!][!//
      [!VAR "NotFoundManagementInfoNotification" = "'(Fee_NotificationPtrType)0'"!][!//
    [!ELSE!][!//
      [!IF "$PostBuildType != 'SELECTABLE'"!][!//
        [!ASSERT "num:isnumber($NotFoundManagementInfoNotification)= 'true'"!][!//
          21-00-13-ERROR: Under LOADABLE option FeeNotFoundManagementInfoNotification should be entered as a Address. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "NotFoundManagementInfoNotification" = "concat('(Fee_NotificationPtrType)',($NotFoundManagementInfoNotification))"!][!//
      [!ELSE!][!//
        [!ASSERT "num:isnumber($NotFoundManagementInfoNotification)!= 'true'"!][!//
          21-00-14-ERROR: Under SELECTABLE option FeeNotFoundManagementInfoNotification should be entered as a function name. Change notification of [!"node:name(.)"!][!//
        [!ENDASSERT!][!//
        [!VAR "NotFoundManagementInfoNotification" = "$NotFoundManagementInfoNotification"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDSELECT!][!//
    [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!//
        /* Job End Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$EndNotification = '(Fee_NotificationPtrType)0'"!][!//
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
[!IF "$ErrorNotification = '(Fee_NotificationPtrType)0'"!][!//
        [!"$ErrorNotification"!],
[!ELSE!][!//
        [!"$ErrorNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($ErrorNotification)"!]U,
[!ENDIF!][!//
[!//
        /* Unavailable Failure Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$UnavailableFailureNotification = '(Fee_NotificationPtrType)0'"!][!//
        [!"$UnavailableFailureNotification"!],
[!ELSE!][!//
        [!"$UnavailableFailureNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($UnavailableFailureNotification)"!]U,
[!ENDIF!][!//
[!//
        /* Discover NonErasable Areas Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$DiscoverNonErasableAreasNotification = '(Fee_NotificationPtrType)0'"!][!//
        [!"$DiscoverNonErasableAreasNotification"!],
[!ELSE!][!//
        [!"$DiscoverNonErasableAreasNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($DiscoverNonErasableAreasNotification)"!]U,
[!ENDIF!][!//
[!//
        /* Not Found Management Info Notification */
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!IF "$NotFoundManagementInfoNotification = '(Fee_NotificationPtrType)0'"!][!//
        [!"$NotFoundManagementInfoNotification"!],
[!ELSE!][!//
        [!"$NotFoundManagementInfoNotification"!],
[!ENDIF!][!//
[!ELSE!][!//
        [!"($NotFoundManagementInfoNotification)"!]U,
[!ENDIF!][!//
    }
};

#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_PBcfg_c_REF_3 */
#include "Fee_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

