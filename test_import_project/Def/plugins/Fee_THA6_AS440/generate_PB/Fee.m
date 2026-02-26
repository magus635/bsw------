[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Fee.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Fee
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/************************************************************
    Macro:Fee_GetAllBlockSize
    Obtain the byte size occupied by all blocks
****************************************************************/!]
[!MACRO "Fee_GetAllBlockSize"!][!//
[!NOCODE!][!//
[!VAR "FeeVirtualPageSize" = "num:i(FeeGeneral/FeeVirtualPageSize)"!][!//
[!VAR "AllBlockSize" = "num:i(0)"!][!//
[!VAR "MaxBlockSize" = "num:i(0)"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
  [!VAR "BlockSize" = "num:i(0)"!][!//
  [!VAR "Pagecount" = "num:i(0)"!][!//
  [!VAR "Fee_BlockSize" = "./FeeBlockSize"!][!//
  [!IF "$Fee_BlockSize < ($FeeVirtualPageSize - num:i(8))"!][!//
    [!VAR "Pagecount" = "num:i(2)"!][!//
  [!ELSE!][!//
    [!VAR "Fee_BlockSize" = "$Fee_BlockSize - ($FeeVirtualPageSize - num:i(8))"!][!//
    [!VAR "Pagecount" = "$Fee_BlockSize div num:i($FeeVirtualPageSize - num:i(1))"!][!//
    [!IF "($Pagecount - num:i($Pagecount) != num:i(0))"!][!//
      [!VAR "Pagecount" = "num:i($Pagecount) + num:i(3)"!][!//
    [!ELSE!][!//
      [!VAR "Pagecount" = "num:i($Pagecount) + num:i(2)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "BlockSize" = "$Pagecount * $FeeVirtualPageSize"!][!//
  [!VAR "AllBlockSize" = "$AllBlockSize + $BlockSize"!][!//
  [!IF "$BlockSize > $MaxBlockSize"!][!//
    [!VAR "MaxBlockSize" = "$BlockSize"!][!//
  [!ENDIF!][!//  
[!ENDLOOP!][!//
[!CODE!][!//
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_ALL_BLOCK_SIZE                         ([!"num:i($AllBlockSize)"!]U)

/* The size of the max block. */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_MAX_BLOCK_SIZE                         ([!"num:i($MaxBlockSize)"!]U)

[!VAR "NumberofSector" = "node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsNumberOfSectors"!][!//
[!VAR "SectorEraseSize" = "node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsSectorSize"!][!//
[!VAR "FeeBankSize" = "num:i($NumberofSector * $SectorEraseSize div num:i(2))"!][!//
[!IF "$FeeBankSize < ($AllBlockSize + $MaxBlockSize + num:i(FeeGeneral/FeeThresholdValue)) + num:i(512)"!][!//
[!ERROR!][!//
21-00-02-ERROR: There are too many blocks configured for Fee module. The Dflash size assigned by Fls module to Fee module is divided by 2,
which is the size of the Fee module Bank. The Fee Bank size must be greater than the sum of all blocks size and FeeThresholdValue and the max block size and the stage page size(512), becase it must be ensure that a block can be written after GC is completed.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDCODE!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/************************************************************
    Macro:Fee_GetPageToByteShift
    The amount of shift between page and byte conversion
****************************************************************/!]
[!MACRO "Fee_GetPageToByteShift"!][!//
[!NOCODE!][!//
[!VAR "FeeVirtualPageSize" = "num:i(FeeGeneral/FeeVirtualPageSize)"!][!//
[!VAR "Counter" = "num:i(0)"!][!//
[!FOR "x" = "0" TO "10"!][!//
 [!VAR "FeeVirtualPageSize" = "$FeeVirtualPageSize div num:i(2)"!][!//
 [!VAR "Counter" = "$Counter + num:i(1)"!][!//
 [!"$FeeVirtualPageSize"!]
 [!IF "$FeeVirtualPageSize = 1.0"!][!//
 [!BREAK!]
 [!ENDIF!]
[!ENDFOR!][!//
[!CODE!][!//
#define FEE_PAGE_TO_BYTE_SHIFT                     ([!"num:i($Counter)"!]U)
[!ENDCODE!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!ENDNOCODE!][!//
