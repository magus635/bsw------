[!NOCODE!][!//
/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Intc_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Intc
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
*
****************************************************************************************************/

[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!][!//
[!IF "not(var:defined('INTC_CFG_COMMON_M'))"!][!//
[!VAR "INTC_CFG_COMMON_M"="'true'"!][!//


[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Get the total number of the SPI interrupts that are enabled */!][!//
[!MACRO "CG_GeneTotalIntSrcNumMacro"!][!//
    [!VAR "Var_IntSrcNum" = "num:i(0)"!][!//
    [!VAR "Var_IntSrcNumCore0" = "num:i(0)"!][!//
    [!VAR "Var_IntSrcNumCore1" = "num:i(0)"!][!//
    [!VAR "Var_IntSrcNumCore2" = "num:i(0)"!][!//
    [!VAR "Var_IntSrcNumCore3" = "num:i(0)"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!LOOP "IntcIntSrcSubClassContainer/*/IntcIntSrcContainer/*"!][!//
            [!IF "IntcIntSrcEnable = 'true'"!][!//
                [!IF "IntcIntSrcCategory = 'CAT1'"!][!//
                    [!IF "IntcIntSrcCoreMapping = 'CORE0'"!][!//
                        [!VAR "Var_IntSrcNumCore0" = "num:i($Var_IntSrcNumCore0 + 1)"!][!//
                    [!ELSEIF "IntcIntSrcCoreMapping = 'CORE1'"!][!//
                        [!VAR "Var_IntSrcNumCore1" = "num:i($Var_IntSrcNumCore1 + 1)"!][!//
                    [!ELSEIF "IntcIntSrcCoreMapping = 'CORE2'"!][!//
                        [!VAR "Var_IntSrcNumCore2" = "num:i($Var_IntSrcNumCore2 + 1)"!][!//
                    [!ELSEIF "IntcIntSrcCoreMapping = 'CORE3'"!][!//
                        [!VAR "Var_IntSrcNumCore3" = "num:i($Var_IntSrcNumCore3 + 1)"!][!//
                    [!ENDIF!][!//
                    [!VAR "Var_IntSrcNum" = "num:i($Var_IntSrcNum + 1)"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Get the Software Interrupt configured flag */!][!//
[!MACRO "CG_GetSgiIntConfigFlag"!][!//
    [!VAR "Var_SoftIntConfigFlag" = "num:i(0)"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!/* Only SPI interrupts is external interrupts */!][!//
        [!IF "./IntcIntSrcClass = 'GIC_SGI' or ./IntcIntSrcClass = 'INTC_SOFTINT'"!][!//
            [!LOOP "IntcIntSrcSubClassContainer/*/IntcIntSrcContainer/*"!][!//
                [!IF "IntcIntSrcEnable = 'true'"!][!//
                    [!VAR "Var_SoftIntConfigFlag" = "num:i(1)"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!IF "num:i($Var_SoftIntConfigFlag) = num:i(1)"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!/* call "CG_GeneTotalIntSrcNumMacro" */!][!//
[!CALL "CG_GeneTotalIntSrcNumMacro"!][!//

[!INDENT "8"!][!//
[!/* Generate Macro definition */!][!//
[!MACRO "CG_GenIntConfigurationPara", "Para_IntType" = ""!][!//
    /* Interrupt priority */
    [!IF "IntcIntSrcAssignedTo = 'FIQ'"!][!//
        [!SELECT "as:modconf('Intc')[1]/IntcGeneral"!][!//
            [!VAR "Var_GroupPriorityShiftLeftValue" = "num:i(./IntcFIQPriorityBinaryPoint - 2)"!][!//
        [!ENDSELECT!][!//
    [!ELSE!][!//
        [!SELECT "as:modconf('Intc')[1]/IntcGeneral"!][!//
            [!VAR "Var_GroupPriorityShiftLeftValue" = "num:i(./IntcIRQPriorityBinaryPoint - 3)"!][!//
        [!ENDSELECT!][!//
    [!ENDIF!][!//
    [!IF "(node:exists(IntcIntSrcSubPriority)) and (node:exists(IntcIntSrcGroupPriority))"!][!//
        [!"num:i(bit:or(bit:shl(IntcIntSrcGroupPriority, $Var_GroupPriorityShiftLeftValue), IntcIntSrcSubPriority))"!]U,
    [!ELSEIF "not(node:exists(IntcIntSrcSubPriority))"!][!//
        [!IF "node:exists(./IntcIntSrcGroupPriority)"!][!//
            [!"IntcIntSrcGroupPriority"!]U,
        [!ELSE!][!//
            0U,  /* Default to 0 */
        [!ENDIF!][!//
    [!ELSE!][!//
        [!"IntcIntSrcSubPriority"!]U,
    [!ENDIF!][!//
    [!IF "IntcIntSrcAssignedTo = 'FIQ'"!][!//
        /* Allocated to [!"IntcIntSrcAssignedTo"!](Group0) */
        INTC_INTERRUPTGROUP_FIQ,
    [!ELSE!][!//
        /* Allocated to [!"IntcIntSrcAssignedTo"!](Group1) */
        INTC_INTERRUPTGROUP_IRQ,
    [!ENDIF!][!//
    /* Interrupt trigger method */
    INTC_TRIGGERMETHOD_[!"IntcIntSrcTriggerMethod"!],
    [!IF "node:value(./IntcIntSrcEnableInstalling) = 'true'"!][!//
        /* Enable when installing */
        TRUE,
    [!ELSE!][!//
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
    [!ENDIF!][!//
    /* Unique interrupt ID */
    [!"IntcIntSrcId"!]U,
    /* Interrupt service handler */
    [!IF "$Para_IntType = 'ExternalInt'"!][!//
        Intc_Irq_IntSrc[!"IntcIntSrcId"!]Entry,
    [!ELSE!][!//
        Intc_Irq_Core[!"text:split(IntcIntSrcCoreMapping, 'CORE')[1]"!]IntSrc[!"IntcIntSrcId"!]Entry,
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Generate the macro for enabled interrupts */!][!//
[!MACRO "CG_GeneEnabledIntMacro"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!/* Only SGI or PPI interrupts is internal interrupts */!][!//
        [!IF "not(text:contains(ecu:list('Intc.CoreFixedIntClass'), ./IntcIntSrcClass))"!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
                    [!IF "IntcIntSrcEnable = 'true'"!][!//
/* Interrupt source [!"IntcIntSrcId"!] enabled: [!"IntcIntSrcName"!] */
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_EN                                   (STD_ON)
/* Interrupt source [!"IntcIntSrcId"!] category: [!"IntcIntSrcName"!] */
[!IF "node:exists(IntcIntSrcCategory)"!][!//
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_CAT                                  (INTC_SRC_TYPE_[!"IntcIntSrcCategory"!])
[!ELSE!][!//
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_CAT                                  (INTC_SRC_TYPE_CAT1)
[!ENDIF!][!//
/* Interrupt source [!"IntcIntSrcId"!] notification: [!"IntcIntSrcName"!] */
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_NOTIF_EN                             [!IF "(node:exists(IntcIntSrcNotification)) and (normalize-space(IntcIntSrcNotification) != 'NULL_PTR')"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]
[!IF "node:exists(IntcIntSrcNotification)"!][!//
/* Notification function for interrupt source [!"IntcIntSrcId"!]: [!"IntcIntSrcName"!] */
extern void [!"normalize-space(IntcIntSrcNotification)"!](void);
#define Intc_Irq_NotifIntSrc[!"IntcIntSrcId"!]()                               [!"normalize-space(IntcIntSrcNotification)"!]()

[!ENDIF!][!//

                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ELSE!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
                    [!IF "IntcIntSrcEnable = 'true'"!][!//
/* Interrupt source [!"IntcIntSrcId"!] enabled: [!"IntcIntSrcName"!] */
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_[!"IntcIntSrcCoreMapping"!]_EN                              (STD_ON)
/* Interrupt source [!"IntcIntSrcId"!] category: [!"IntcIntSrcName"!] */
[!IF "node:exists(IntcIntSrcCategory)"!][!//
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_[!"IntcIntSrcCoreMapping"!]_CAT                             (INTC_SRC_TYPE_[!"IntcIntSrcCategory"!])
[!ELSE!][!//
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_[!"IntcIntSrcCoreMapping"!]_CAT                             (INTC_SRC_TYPE_CAT1)
[!ENDIF!][!//
/* Interrupt source [!"IntcIntSrcId"!] notification: [!"IntcIntSrcName"!] */
#define INTC_CFG_INTSRC[!"IntcIntSrcId"!]_[!"IntcIntSrcCoreMapping"!]_NOTIF_EN                        [!IF "(node:exists(IntcIntSrcNotification)) and (normalize-space(IntcIntSrcNotification) != 'NULL_PTR')"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]
[!IF "node:exists(IntcIntSrcNotification)"!][!//
/* Notification function for interrupt source [!"IntcIntSrcId"!]: [!"IntcIntSrcName"!] */
extern void [!"normalize-space(IntcIntSrcNotification)"!](void);
#define Intc_Irq_NotifCore[!"text:split(IntcIntSrcCoreMapping, 'CORE')[1]"!]IntSrc[!"IntcIntSrcId"!]()                           [!"normalize-space(IntcIntSrcNotification)"!]()
[!ENDIF!][!//

                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Generate the macro for interrupt category enable status */!][!//
[!MACRO "CG_GeneIntCategoryEnStatusMacro"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!VAR "Var_IntCatName" = "./IntcIntSrcClass"!][!//
        [!VAR "Var_IntCatEn" = "'false'"!][!//
        [!/* Only SGI or PPI interrupts is internal interrupts */!][!//
        [!IF "not((./IntcIntSrcClass  = 'GIC_SGI') or (./IntcIntSrcClass  = 'GIC_PPI'))"!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
                    [!IF "IntcIntSrcEnable = 'true'"!][!//
                        [!VAR "Var_IntCatEn" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ELSE!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
                    [!IF "IntcIntSrcEnable = 'true'"!][!//
                        [!VAR "Var_IntCatEn" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
/* [!"$Var_IntCatName"!] interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_[!"text:toupper($Var_IntCatName)"!]_INTSRC_EN                                   [!IF "$Var_IntCatEn = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Generate the all interrupt source macro */!][!//
[!MACRO "CG_GeneIntIdMacro"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!/* Only SGI or PPI interrupts is internal interrupts */!][!//
        [!IF "not(text:contains(ecu:list('Intc.CoreFixedIntClass'), ./IntcIntSrcClass))"!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
/* External interrupt source(SPI): INTID [!"IntcIntSrcId"!] - [!"text:toupper(IntcIntSrcName)"!] */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_[!"text:toupper(IntcIntSrcName)"!]                                   ([!"IntcIntSrcId"!]U)
#ifndef INTC_INTSRC_NUM_[!"IntcIntSrcId"!]        
#define INTC_INTSRC_NUM_[!"IntcIntSrcId"!]                                     ([!"IntcIntSrcId"!]U)
#endif /* INTC_INTSRC_NUM_[!"IntcIntSrcId"!] */
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ELSE!][!//
            [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
                [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
/* Internal interrupt source(SGI or PPI): INTID [!"IntcIntSrcId"!] */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_[!"text:toupper(IntcIntSrcName)"!]                                   ([!"IntcIntSrcId"!]U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_[!"text:toupper(IntcIntSrcName)"!]_[!"IntcIntSrcCoreMapping"!]                               ([!"IntcIntSrcId"!]U)
#ifndef INTC_INTSRC_NUM_[!"IntcIntSrcId"!]
#define INTC_INTSRC_NUM_[!"IntcIntSrcId"!]                                     ([!"IntcIntSrcId"!]U)
#endif /* INTC_INTSRC_NUM_[!"IntcIntSrcId"!] */
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!NOCODE!][!//
[!/* Generate the macro for the core mask of internal interrupt source (SGI). */!][!//
[!MACRO "CG_GeneSgiInterruptCoreMacro"!][!//
    [!VAR "Var_CoreIdBit" = "num:i(1)"!][!//
    [!VAR "Var_CoreIdMask" = "num:i(0)"!][!//
    [!FOR "Var_CoreCnt" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "Var_CoreIdBit" = "bit:shl(num:i(1), $Var_CoreCnt)"!][!//
        [!VAR "Var_CoreIdMask" = "bit:or($Var_CoreIdMask, $Var_CoreIdBit)"!][!//
/* Represent core[!"num:i($Var_CoreCnt)"!] for generate the SGI interrupt */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE[!"num:i($Var_CoreCnt)"!]                                      ([!"num:inttohex($Var_CoreIdBit, 2)"!]U)
    [!ENDFOR!][!//
[!/* Line feed */!]
/* All cores mask for generate software interrupt(SGI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE_MASK                                  ([!"num:inttohex($Var_CoreIdMask, 2)"!]U)
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!][!//

[!ENDIF!][!// Avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
