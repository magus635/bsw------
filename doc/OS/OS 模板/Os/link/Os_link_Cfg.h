/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_Link_Cfg.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : [!"$datetime"!]
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_LINK_CFG_H_
#define OS_LINK_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative) = 'Os_THA6206'"!][!//
[!VAR "ZeroInitStageOneNum" = "0"!][!//
[!VAR "ZeroInitStageTwoNum" = "0"!][!//
[!VAR "ZeroInitStageThreeNum" = "0"!][!//
[!VAR "ZeroInitStageUnclearNum" = "0"!][!//
[!VAR "DataStageOneNum" = "0"!][!//
[!VAR "DataStageTwoNum" = "0"!][!//
[!VAR "DataStageThreeNum" = "0"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEONE'"!][!//
            [!VAR "ZeroInitStageOneNum" = "$ZeroInitStageOneNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETWO'"!][!//
            [!VAR "ZeroInitStageTwoNum" = "$ZeroInitStageTwoNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETHREE'"!][!//
            [!VAR "ZeroInitStageThreeNum" = "$ZeroInitStageThreeNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEUNCLEAR'"!][!//
            [!VAR "ZeroInitStageUnclearNum" = "$ZeroInitStageUnclearNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEONE'"!][!//
            [!VAR "DataStageOneNum" = "$DataStageOneNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETWO'"!][!//
            [!VAR "DataStageTwoNum" = "$DataStageTwoNum + 1"!][!//
        [!ENDIF!][!//
        [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETHREE'"!][!//
            [!VAR "DataStageThreeNum" = "$DataStageThreeNum + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
#define  MEM_ZEROINIT_STAGEONE_NUM       ([!"num:i($ZeroInitStageOneNum)"!]u)
#define  MEM_ZEROINIT_STAGETWO_NUM       ([!"num:i($ZeroInitStageTwoNum)"!]u)
#define  MEM_ZEROINIT_STAGETHREE_NUM     ([!"num:i($ZeroInitStageThreeNum)"!]u)
#define  MEM_ZEROINIT_STAGEUNCLEAR_NUM   ([!"num:i($ZeroInitStageUnclearNum)"!]u)

#define  MEM_DATAINIT_STAGEONE_NUM       ([!"num:i($DataStageOneNum)"!]u)
#define  MEM_DATAINIT_STAGETWO_NUM       ([!"num:i($DataStageTwoNum)"!]u)
#define  MEM_DATAINIT_STAGETHREE_NUM     ([!"num:i($DataStageThreeNum)"!]u)
#define  MEM_FILL_PATTERN                (0u)
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
[!ENDIF!][!//

#endif /* OS_LINK_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_link_Cfg.h                                                                 **
****************************************************************************************************/


