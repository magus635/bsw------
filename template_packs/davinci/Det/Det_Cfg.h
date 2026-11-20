[!SELECT "as:modconf('Det')[1]"!][!//
[!IF "not(node:exists(DetGeneral))"!][!ERROR "DetGeneral container is missing in Det configuration"!][!ENDIF!][!//
[!VAR "errorHookCount" = "num:i(0)"!][!//
[!VAR "runtimeCalloutCount" = "num:i(0)"!][!//
[!VAR "transientCalloutCount" = "num:i(0)"!][!//
[!IF "node:exists(DetNotification)"!][!//
[!VAR "errorHookCount" = "num:i(count(DetNotification/DetErrorHook/*))"!][!//
[!VAR "runtimeCalloutCount" = "num:i(count(DetNotification/DetReportRuntimeErrorCallout/*))"!][!//
[!VAR "transientCalloutCount" = "num:i(count(DetNotification/DetReportTransientFaultCallout/*))"!][!//
[!ENDIF!][!//
[!VAR "dummyKind" = "'SelfAssignment'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral)"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) and node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) = 'false'"!][!//
[!VAR "dummyKind" = "'None'"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "atomicBitAccess" = "'STD_OFF'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) and node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) = 'true'"!][!//
[!VAR "atomicBitAccess" = "'STD_ON'"!][!//
[!ENDIF!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!VAR "avaVal" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!IF "$avaVal = 'Atomic8BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'8u'"!][!//
[!ELSEIF "$avaVal = 'Atomic16BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'16u'"!][!//
[!ELSEIF "$avaVal = 'Atomic32BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!ELSEIF "$avaVal = 'Atomic64BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'64u'"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "bitOrder" = "'LSB_to_MSB'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!VAR "bitOrder" = "node:value(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!//
[!VAR "bitOrder" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!//
[!ENDIF!][!//
[!VAR "detProcessor" = "'DET_PROCESSOR_TONGXIN_THA6206'"!][!//
[!IF "ecu:has('Det.Processor')"!][!//
[!VAR "detProcessor" = "ecu:get('Det.Processor')"!][!//
[!ENDIF!][!//
[!VAR "detCompiler" = "'DET_COMP_LLVMHIGHTEC'"!][!//
[!IF "ecu:has('Det.Compiler')"!][!//
[!VAR "detCompiler" = "ecu:get('Det.Compiler')"!][!//
[!ENDIF!][!//
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Det_Cfg.h
 *            Module: Det
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#if !defined(DET_CFG_H)
#define DET_CFG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


#define DET_GENERATOR_CFG5
#define DET_AUTOSARVERSION                       4U
#define DET_ENABLED                              [!IF "node:value(DetGeneral/DetEnableDet) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define DET_VERSION_INFO_API                     [!IF "node:value(DetGeneral/DetVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define DET_DEBUG_ENABLED                        [!IF "node:value(DetGeneral/DetExtDebugSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define DET_DLTFILTERSIZE                        [!"num:i(node:value(DetGeneral/DetDltFilterSize))"!]u
#define DET_GLOBALFILTERSIZE                     [!"num:i(node:value(DetGeneral/DetGlobalFilterSize))"!]u
#define DET_BREAKFILTERSIZE                      [!"num:i(node:value(DetGeneral/DetBreakFilterSize))"!]u
#define DET_LOGBUFFERSIZE                        [!"num:i(node:value(DetGeneral/DetLogBufferSize))"!]u
#define DET_FORWARD_TO_DLT                       [!IF "node:exists(DetGeneral/DetForwardToDlt) and node:value(DetGeneral/DetForwardToDlt) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define DET_REPORT_ERROR_RECURSIONLIMIT          [!"num:i(node:value(DetGeneral/DetReportErrorRecursionLimit))"!]u
#define DET_REPORT_RUNTIMEERROR_RECURSIONLIMIT   [!"num:i(node:value(DetGeneral/DetReportRuntimeErrorRecursionLimit))"!]u
#define DET_REPORT_TRANSIENTFAULT_RECURSIONLIMIT [!"num:i(node:value(DetGeneral/DetReportTransientFaultRecursionLimit))"!]u

/*! DetModuleId symbolic name defines */
[!IF "node:exists(DetConfigSet)"!][!//
[!LOOP "DetConfigSet/DetModule/*"!][!//
#define DetConf_DetModule_[!"node:name(.)"!] ([!"num:i(node:value(DetModuleId))"!]u) 
[!ENDLOOP!][!//
[!ENDIF!][!//


/*! Service port defines */
[!IF "node:exists(DetConfigSet)"!][!//
[!LOOP "DetConfigSet/DetModule/*"!][!//
#define DetConf_[!"node:name(.)"!] [!"num:i(node:value(DetModuleId))"!]u 
[!LOOP "DetModuleInstance/*"!][!//
#define DetConf_DetModuleInstance_[!"node:name(.)"!] ([!"num:i(node:value(DetInstanceId))"!]u)
[!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DetPCDataSwitches  Det Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
[!IF "$errorHookCount > 0"!][!//
#define DET_ERRORHOOKTABLE                                                                          STD_ON
[!ELSE!][!//
#define DET_ERRORHOOKTABLE                                                                          STD_OFF  /**< Deactivateable: 'Det_ErrorHookTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
[!ENDIF!][!//
#define DET_FINALMAGICNUMBER                                                                        STD_OFF  /**< Deactivateable: 'Det_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DET_INITDATAHASHCODE                                                                        STD_OFF  /**< Deactivateable: 'Det_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
[!IF "$runtimeCalloutCount > 0"!][!//
#define DET_RUNTIMEERRORCALLOUTTABLE                                                                STD_ON
[!ELSE!][!//
#define DET_RUNTIMEERRORCALLOUTTABLE                                                                STD_OFF  /**< Deactivateable: 'Det_RuntimeErrorCalloutTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
[!ENDIF!][!//
[!IF "$errorHookCount > 0"!][!//
#define DET_SIZEOFERRORHOOKTABLE                                                                    STD_ON
[!ENDIF!][!//
[!IF "$runtimeCalloutCount > 0"!][!//
#define DET_SIZEOFRUNTIMEERRORCALLOUTTABLE                                                          STD_ON
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
#define DET_SIZEOFTRANSIENTFAULTCALLOUTTABLE                                                        STD_ON
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
#define DET_TRANSIENTFAULTCALLOUTTABLE                                                              STD_ON
[!ELSE!][!//
#define DET_TRANSIENTFAULTCALLOUTTABLE                                                              STD_OFF  /**< Deactivateable: 'Det_TransientFaultCalloutTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
[!ENDIF!][!//
#define DET_PCCONFIG                                                                                STD_ON
#define DET_FINALMAGICNUMBEROFPCCONFIG                                                              STD_OFF  /**< Deactivateable: 'Det_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DET_INITDATAHASHCODEOFPCCONFIG                                                              STD_OFF  /**< Deactivateable: 'Det_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
/** 
  \}
*/ 

/** 
  \defgroup  DetPCSymbolicInitializationPointers  Det Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Det_Config_Ptr                                                                              NULL_PTR  /**< symbolic identifier which shall be used to initialize 'Det' */
/** 
  \}
*/ 

/** 
  \defgroup  DetPCInitializationSymbols  Det Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Det_Config                                                                                  NULL_PTR  /**< symbolic identifier which could be used to initialize 'Det */
/** 
  \}
*/ 

/** 
  \defgroup  DetPCGeneral  Det General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define DET_CHECK_INIT_POINTER                                                                      STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define DET_FINAL_MAGIC_NUMBER                                                                      0x0F1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Det */
#define DET_INDIVIDUAL_POSTBUILD                                                                    STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Det' is not configured to be postbuild capable. */
#define DET_INIT_DATA                                                                               DET_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define DET_INIT_DATA_HASH_CODE                                                                     1840703899  /**< the precompile constant to validate the initialization structure at initialization time of Det with a hashcode. The seed value is '0x0F1Eu' */
#define DET_USE_ECUM_BSW_ERROR_HOOK                                                                 STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define DET_USE_INIT_POINTER                                                                        STD_OFF  /**< STD_ON if the init pointer Det shall be used. */
/** 
  \}
*/ 



[!IF "$dummyKind = 'SelfAssignment'"!][!//
#ifndef DET_USE_DUMMY_STATEMENT
#define DET_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT
#define DET_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT_CONST
#define DET_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
[!ELSEIF "$dummyKind = 'VoidCast'"!][!//
#ifndef DET_USE_DUMMY_STATEMENT
#define DET_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT
#define DET_DUMMY_STATEMENT(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT_CONST
#define DET_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
[!ELSE!][!//
#ifndef DET_USE_DUMMY_STATEMENT
#define DET_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT
#define DET_DUMMY_STATEMENT(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DET_DUMMY_STATEMENT_CONST
#define DET_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
[!ENDIF!][!//
#ifndef DET_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define DET_ATOMIC_BIT_ACCESS_IN_BITFIELD [!"$atomicBitAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef DET_ATOMIC_VARIABLE_ACCESS
#define DET_ATOMIC_VARIABLE_ACCESS [!"$atomicVarAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef [!"$detProcessor"!]
#define [!"$detProcessor"!]
#endif
#ifndef [!"$detCompiler"!]
#define [!"$detCompiler"!]
#endif
#ifndef DET_GEN_GENERATOR_MSR
#define DET_GEN_GENERATOR_MSR
#endif
[!IF "$bitOrder = 'MSB_to_LSB'"!][!//
#ifndef DET_CPUTYPE_BITORDER_MSB2LSB
#define DET_CPUTYPE_BITORDER_MSB2LSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ELSE!][!//
#ifndef DET_CPUTYPE_BITORDER_LSB2MSB
#define DET_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ENDIF!][!//
#ifndef DET_CONFIGURATION_VARIANT_PRECOMPILE
#define DET_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef DET_CONFIGURATION_VARIANT_LINKTIME
#define DET_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef DET_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define DET_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef DET_CONFIGURATION_VARIANT
#define DET_CONFIGURATION_VARIANT DET_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef DET_POSTBUILD_VARIANT_SUPPORT
#define DET_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/*! Compatibility defines */
#define DET_RUNTIME_ERROR_CALLOUT_ENABLED        DET_RUNTIMEERRORCALLOUTTABLE
#define DET_TRANSIENT_FAULT_CALLOUT_ENABLED      DET_TRANSIENTFAULTCALLOUTTABLE
#define DET_ERROR_HOOK_ENABLED                   DET_ERRORHOOKTABLE

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DetPCHasMacros  Det Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
[!IF "$errorHookCount > 0"!][!//
#define Det_HasErrorHookTable()                                                                     (TRUE != FALSE)
#define Det_HasSizeOfErrorHookTable()                                                               (TRUE != FALSE)
[!ENDIF!][!//
[!IF "$runtimeCalloutCount > 0"!][!//
#define Det_HasRuntimeErrorCalloutTable()                                                           (TRUE != FALSE)
#define Det_HasSizeOfRuntimeErrorCalloutTable()                                                     (TRUE != FALSE)
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
#define Det_HasTransientFaultCalloutTable()                                                         (TRUE != FALSE)
#define Det_HasSizeOfTransientFaultCalloutTable()                                                   (TRUE != FALSE)
[!ENDIF!][!//
#define Det_HasPCConfig()                                                                           (TRUE != FALSE)
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/
[!IF "$errorHookCount > 0"!][!//
#define Det_GetErrorHookTable(Index) (Det_ErrorHookTable[(Index)])
#define Det_GetSizeOfErrorHookTable() [!"$errorHookCount"!]u
[!ENDIF!][!//
[!IF "$runtimeCalloutCount > 0"!][!//
#define Det_GetRuntimeErrorCalloutTable(Index) (Det_RuntimeErrorCalloutTable[(Index)])
#define Det_GetSizeOfRuntimeErrorCalloutTable() [!"$runtimeCalloutCount"!]u
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
#define Det_GetTransientFaultCalloutTable(Index) (Det_TransientFaultCalloutTable[(Index)])
#define Det_GetSizeOfTransientFaultCalloutTable() [!"$transientCalloutCount"!]u
[!ENDIF!][!//



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Function pointer type for callouts */
typedef P2FUNC(Std_ReturnType, DET_CODE, Det_CalloutTableType)(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  DetPCRootValueTypes  Det Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Det_PCConfig */
typedef struct sDet_PCConfigType
{
  uint8 Det_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Det_PCConfigType;

typedef Det_PCConfigType Det_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 

 


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
 
[!IF "($errorHookCount > 0) or ($runtimeCalloutCount > 0) or ($transientCalloutCount > 0)"!][!//
#define DET_START_SEC_CONST_UNSPECIFIED
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "$errorHookCount > 0"!][!//
extern CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[[!"$errorHookCount"!]];
[!ENDIF!][!//
[!IF "$runtimeCalloutCount > 0"!][!//
extern CONST(Det_CalloutTableType, DET_CONST) Det_RuntimeErrorCalloutTable[[!"$runtimeCalloutCount"!]];
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
extern CONST(Det_CalloutTableType, DET_CONST) Det_TransientFaultCalloutTable[[!"$transientCalloutCount"!]];
[!ENDIF!][!//
#define DET_STOP_SEC_CONST_UNSPECIFIED
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDIF!][!//

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

 
#define DET_START_SEC_CODE
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "node:exists(DetNotification)"!][!//
[!VAR "seenCallouts" = "'|'"!][!//
[!LOOP "DetNotification/DetErrorHook/*"!][!//
[!VAR "fnName" = "string:trim(node:value(.))"!][!//
[!IF "string-length($fnName) > 0 and not(contains($seenCallouts, concat('|', $fnName, '|')))"!][!//
[!VAR "seenCallouts" = "concat($seenCallouts, $fnName, '|')"!][!//
FUNC(Std_ReturnType, DET_CODE) [!"$fnName"!](uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
[!ENDIF!][!//
[!ENDLOOP!][!//
[!LOOP "DetNotification/DetReportRuntimeErrorCallout/*"!][!//
[!VAR "fnName" = "string:trim(node:value(.))"!][!//
[!IF "string-length($fnName) > 0 and not(contains($seenCallouts, concat('|', $fnName, '|')))"!][!//
[!VAR "seenCallouts" = "concat($seenCallouts, $fnName, '|')"!][!//
FUNC(Std_ReturnType, DET_CODE) [!"$fnName"!](uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
[!ENDIF!][!//
[!ENDLOOP!][!//
[!LOOP "DetNotification/DetReportTransientFaultCallout/*"!][!//
[!VAR "fnName" = "string:trim(node:value(.))"!][!//
[!IF "string-length($fnName) > 0 and not(contains($seenCallouts, concat('|', $fnName, '|')))"!][!//
[!VAR "seenCallouts" = "concat($seenCallouts, $fnName, '|')"!][!//
FUNC(Std_ReturnType, DET_CODE) [!"$fnName"!](uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//



#define DET_STOP_SEC_CODE
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



[!IF "node:exists(DetGeneral/DetUserConfigFile) and string-length(string:trim(node:value(DetGeneral/DetUserConfigFile))) > 0"!][!//
#include "[!"string:trim(node:value(DetGeneral/DetUserConfigFile))"!]"
[!ENDIF!][!//
#endif /* DET_CFG_H */[!ENDSELECT!]
