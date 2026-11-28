[!SELECT "as:modconf('EcuM')[1]"!][!//
[!IF "not(node:exists(EcuMGeneral))"!][!ERROR "EcuMGeneral container is missing in EcuM configuration"!][!ENDIF!][!//
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
[!VAR "ecumProcessor" = "'ECUM_PROCESSOR_TONGXIN_THA6206'"!][!//
[!IF "ecu:has('EcuM.Processor')"!][!VAR "ecumProcessor" = "ecu:get('EcuM.Processor')"!][!ENDIF!][!//
[!VAR "ecumCompiler" = "'ECUM_COMP_LLVMHIGHTEC'"!][!//
[!IF "ecu:has('EcuM.Compiler')"!][!VAR "ecumCompiler" = "ecu:get('EcuM.Compiler')"!][!ENDIF!][!//
[!VAR "devErr" = "'STD_ON'"!][!//
[!IF "node:exists(EcuMGeneral/EcuMDevErrorDetect) and (node:value(EcuMGeneral/EcuMDevErrorDetect) != 'true')"!][!VAR "devErr" = "'STD_OFF'"!][!ENDIF!][!//
[!VAR "resetModeCount" = "num:i(count(EcuMConfiguration/EcuMFlexConfiguration/EcuMResetMode/*))"!][!//
[!IF "$resetModeCount = 0"!][!VAR "resetModeCount" = "num:i(4)"!][!ENDIF!][!//
[!VAR "shutdownCauseCount" = "num:i(count(EcuMConfiguration/EcuMFlexConfiguration/EcuMShutdownCause/*))"!][!//
[!IF "$shutdownCauseCount = 0"!][!VAR "shutdownCauseCount" = "num:i(4)"!][!ENDIF!][!//
[!VAR "partCount" = "num:i(count(EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*))"!][!//
[!IF "$partCount = 0"!][!VAR "partCount" = "num:i(1)"!][!ENDIF!][!//
[!VAR "osResName" = "'OsResource'"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMOSResource) and (node:refvalid(EcuMConfiguration/EcuMCommonConfiguration/EcuMOSResource) = 'true')"!][!//
[!VAR "osResName" = "node:name(node:ref(EcuMConfiguration/EcuMCommonConfiguration/EcuMOSResource))"!][!//
[!ENDIF!][!//
[!VAR "wkCount" = "num:i(count(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*))"!][!//
[!VAR "comMRefCount" = "num:i(0)"!][!//
[!VAR "firstComMChannelName" = "''"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource)"!][!//
[!LOOP "EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*"!][!//
[!IF "node:exists(EcuMComMChannelRef) and (node:refvalid(EcuMComMChannelRef) = 'true')"!][!//
[!VAR "comMRefCount" = "num:i($comMRefCount + 1)"!][!//
[!IF "$comMRefCount = 1"!][!//
[!VAR "firstComMChannelName" = "node:name(node:ref(EcuMComMChannelRef))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "sleepCount" = "num:i(count(EcuMConfiguration/EcuMCommonConfiguration/EcuMSleepMode/*))"!][!//
[!VAR "fixedBehav" = "'false'"!][!//
[!IF "node:exists(EcuMGeneral/EcuMEnableFixBehavior) and (node:value(EcuMGeneral/EcuMEnableFixBehavior) = 'true')"!][!VAR "fixedBehav" = "'true'"!][!ENDIF!][!//
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This file is part of the AUTOSAR BSW Configurator generated output.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EcuM_Cfg.h
 *            Module: EcuM
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#if !defined(ECUM_CFG_H)
#define ECUM_CFG_H

/**********************************************************************************************************************
 *  PRE-COMPILE Switches
 *********************************************************************************************************************/
/* pre-compile switches for development error detection and reporting */
#ifndef ECUM_DEV_ERROR_DETECT
#define ECUM_DEV_ERROR_DETECT [!"$devErr"!]
#endif
#ifndef ECUM_DEV_ERROR_REPORT
#define ECUM_DEV_ERROR_REPORT [!"$devErr"!]
#endif

/* pre-compile switches for EcuM configuration */
# define ECUM_SCHM_START_INITIALIZATION                               ([!IF "not(node:exists(EcuMGeneral/EcuMSchMStartInitialization)) or (node:value(EcuMGeneral/EcuMSchMStartInitialization) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_DEFERRED_BSWM_NOTIFICATION                              ([!IF "node:exists(EcuMGeneral/EcuMDeferredBswMNotification) and (node:value(EcuMGeneral/EcuMDeferredBswMNotification) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_NONCHANNEL_WAKEUP_RUN                                   ([!IF "node:exists(EcuMGeneral/EcuMNonChannelWakeupInRun) and (node:value(EcuMGeneral/EcuMNonChannelWakeupInRun) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SLAVE_CORE_HANDLING                                     ([!IF "not(node:exists(EcuMGeneral/EcuMSlaveCoreHandling)) or (node:value(EcuMGeneral/EcuMSlaveCoreHandling) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_BSW_ERROR_HOOK                                          ([!IF "not(node:exists(EcuMGeneral/EcuMBswErrorHook)) or (node:value(EcuMGeneral/EcuMBswErrorHook) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/* pre-compile switches for APIs */
# define ECUM_VERSION_INFO_API                                        ([!IF "node:exists(EcuMGeneral/EcuMVersionInfoApi) and (node:value(EcuMGeneral/EcuMVersionInfoApi) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

# define ECUM_ENABLE_DEF_BEHAVIOR                                     ([!IF "node:exists(EcuMFlexGeneral/EcuMEnableDefBehaviour) and (node:value(EcuMFlexGeneral/EcuMEnableDefBehaviour) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_RESET_LOOP_DETECTION                                    ([!IF "node:exists(EcuMFlexGeneral/EcuMResetLoopDetection) and (node:value(EcuMFlexGeneral/EcuMResetLoopDetection) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_ALARM_CLOCK_PRESENT                                     ([!IF "node:exists(EcuMFlexGeneral/EcuMAlarmClockPresent) and (node:value(EcuMFlexGeneral/EcuMAlarmClockPresent) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_MODE_HANDLING                                           ([!IF "node:exists(EcuMFlexGeneral/EcuMModeHandling) and (node:value(EcuMFlexGeneral/EcuMModeHandling) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

# define ECUM_FIXED_BEHAVIOR                                          ([!IF "$fixedBehav = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SUPPORT_RTE                                             ([!IF "($fixedBehav = 'true') and node:exists(EcuMFixedGeneral/EcuMIncludeRte) and (node:value(EcuMFixedGeneral/EcuMIncludeRte) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SUPPORT_RTE_MODE_SWITCH                                 ([!IF "($fixedBehav = 'true') and node:exists(EcuMFixedGeneral/EcuMGenModeSwitchPort) and (node:value(EcuMFixedGeneral/EcuMGenModeSwitchPort) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SUPPORT_RTE_MODE_SWITCH_ACK                             ([!IF "($fixedBehav = 'true') and node:exists(EcuMFixedGeneral/EcuMModeSwitchRteAck) and (node:value(EcuMFixedGeneral/EcuMModeSwitchRteAck) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_INCLUDE_NVRAM_MGR                                       ([!IF "($fixedBehav = 'true') and node:exists(EcuMFixedGeneral/EcuMIncludeNvramMgr) and (node:value(EcuMFixedGeneral/EcuMIncludeNvramMgr) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SUPPORT_DEM                                             ([!IF "node:exists(EcuMGeneral/EcuMIncludeDem) and (node:value(EcuMGeneral/EcuMIncludeDem) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
# define ECUM_SUPPORT_COMM                                            ([!IF "($fixedBehav = 'true') and node:exists(EcuMFixedGeneral/EcuMIncludeComM) and (node:value(EcuMFixedGeneral/EcuMIncludeComM) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!IF "$dummyKind = 'SelfAssignment'"!][!//
#ifndef ECUM_USE_DUMMY_STATEMENT
#define ECUM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ECUM_DUMMY_STATEMENT
#define ECUM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef ECUM_DUMMY_STATEMENT_CONST
#define ECUM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ELSEIF "$dummyKind = 'VoidCast'"!][!//
#ifndef ECUM_USE_DUMMY_STATEMENT
#define ECUM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ECUM_DUMMY_STATEMENT
#define ECUM_DUMMY_STATEMENT(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef ECUM_DUMMY_STATEMENT_CONST
#define ECUM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ELSE!][!//
#ifndef ECUM_USE_DUMMY_STATEMENT
#define ECUM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ECUM_DUMMY_STATEMENT
#define ECUM_DUMMY_STATEMENT(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef ECUM_DUMMY_STATEMENT_CONST
#define ECUM_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ENDIF!][!//
#ifndef ECUM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ECUM_ATOMIC_BIT_ACCESS_IN_BITFIELD [!"$atomicBitAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ECUM_ATOMIC_VARIABLE_ACCESS
#define ECUM_ATOMIC_VARIABLE_ACCESS [!"$atomicVarAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef [!"$ecumProcessor"!]
#define [!"$ecumProcessor"!]
#endif
#ifndef [!"$ecumCompiler"!]
#define [!"$ecumCompiler"!]
#endif
#ifndef ECUM_GEN_GENERATOR_MSR
#define ECUM_GEN_GENERATOR_MSR
#endif
[!IF "$bitOrder = 'MSB_to_LSB'"!][!//
#ifndef ECUM_CPUTYPE_BITORDER_MSB2LSB
#define ECUM_CPUTYPE_BITORDER_MSB2LSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ELSE!][!//
#ifndef ECUM_CPUTYPE_BITORDER_LSB2MSB
#define ECUM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ENDIF!][!//
#ifndef ECUM_CONFIGURATION_VARIANT_PRECOMPILE
#define ECUM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ECUM_CONFIGURATION_VARIANT_LINKTIME
#define ECUM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ECUM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ECUM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ECUM_CONFIGURATION_VARIANT
#define ECUM_CONFIGURATION_VARIANT ECUM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ECUM_POSTBUILD_VARIANT_SUPPORT
#define ECUM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/**********************************************************************************************************************
 *  PRE-COMPILE Counts and Switches
 *********************************************************************************************************************/
#define ECUM_RESETMODECOUNT                                           ([!"$resetModeCount"!]u)
#define ECUM_SHUTDOWNCAUSECOUNT                                       ([!"$shutdownCauseCount"!]u)
#define ECUM_NUMBER_OF_CORES                                          ([!"$partCount"!]u)
#define ECUM_NUMBER_OF_OS_APPLICATIONS                                ([!"$partCount"!]u)

#define ECUM_CORE_ID_STARTUP                                          OS_CORE_ID_MASTER
#define ECUM_CORE_ID_BSW                                              OS_CORE_ID_MASTER
#define ECUM_OS_RESOURCE                                              [!"$osResName"!]

#define ECUM_BSWM_CONFIG_POINTER                                      BswM_Config_Ptr
#define ECUM_SCHM_CONFIG_POINTER

typedef volatile uint32 EcuM_CoreStatusType;
typedef EcuM_CoreStatusType *EcuM_CoreStatusArrayType;

#define EcuM_SetCoreStatusValue(partitionIdx, value)                  (*EcuM_GetCoreStatus(partitionIdx) = value)
#define EcuM_GetCoreStatusValue(partitionIdx)                         (*EcuM_GetCoreStatus(partitionIdx))

# if (STD_ON == ECUM_DEV_ERROR_DETECT)
#  define EcuM_Det_ReportError(EcuM_FunctionId, EcuM_ErrorCode)       ((void)Det_ReportError((ECUM_MODULE_ID), (ECUM_INSTANCE_ID), (EcuM_FunctionId), (EcuM_ErrorCode)))
# else
#  define EcuM_Det_ReportError(EcuM_FunctionId, EcuM_ErrorCode)
# endif


/**********************************************************************************************************************
 *  ComStackLib Configuration Defines
 *********************************************************************************************************************/
#define ECUM_PBCONFIG                                                                               STD_OFF
#define ECUM_LTCONFIGIDXOFPBCONFIG                                                                  STD_OFF
#define ECUM_PCCONFIGIDXOFPBCONFIG                                                                  STD_OFF
#define ECUM_ALARMCLOCKTIMEOUT                                                                      STD_OFF
#define ECUM_COMMCHANNELREFS                                                                        [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_CHANNELOFCOMMCHANNELREFS                                                               [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_COMMPNCREFS                                                                            STD_OFF
#define ECUM_PNCOFCOMMPNCREFS                                                                       STD_OFF
#define ECUM_CORESTATUS                                                                             STD_ON
#define ECUM_DEFAULTAPPMODE                                                                         STD_ON
#define ECUM_DEFAULTSHUTDOWNMODE                                                                    STD_ON
#define ECUM_DEFAULTSHUTDOWNTARGET                                                                  STD_ON
#define ECUM_DRIVERINITONE                                                                          STD_ON
#define ECUM_FUNCTIONOFDRIVERINITONE                                                                STD_ON
#define ECUM_DRIVERRESTARTLIST                                                                      STD_OFF
#define ECUM_FUNCTIONOFDRIVERRESTARTLIST                                                            STD_OFF
#define ECUM_FINALMAGICNUMBER                                                                       STD_OFF
#define ECUM_FLEXUSER                                                                               STD_OFF
#define ECUM_ALARMCLOCKIDOFFLEXUSER                                                                 STD_OFF
#define ECUM_GODOWNALLOWEDOFFLEXUSER                                                                STD_OFF
#define ECUM_MODULEIDOFFLEXUSER                                                                     STD_OFF
#define ECUM_SETCLOCKALLOWEDOFFLEXUSER                                                              STD_OFF
#define ECUM_GENERATORCOMPATIBILITYVERSION                                                          STD_ON
#define ECUM_INITDATAHASHCODE                                                                       STD_OFF
#define ECUM_MAXWAKEUPSOURCECOUNT                                                                   STD_ON
#define ECUM_MODULESTATE                                                                            STD_ON
#define ECUM_NORMALMCUMODE                                                                          STD_ON
#define ECUM_PARTITIONDATA                                                                          STD_ON
#define ECUM_APPLICATIONOFPARTITIONDATA                                                             STD_ON
#define ECUM_BSWMPARTITIONOFPARTITIONDATA                                                           STD_OFF
#define ECUM_ECUMPARTITIONOFPARTITIONDATA                                                           STD_ON
#define ECUM_RESOURCEOFPARTITIONDATA                                                                STD_OFF
#define ECUM_SIZEOFCOMMCHANNELREFS                                                                  [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_SIZEOFCORESTATUS                                                                       STD_ON
#define ECUM_SIZEOFDRIVERINITONE                                                                    STD_ON
#define ECUM_SIZEOFPARTITIONDATA                                                                    STD_ON
#define ECUM_SIZEOFWAKEUPSOURCELIST                                                                 [!IF "$wkCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_SLEEPMODELIST                                                                          [!IF "$sleepCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_MCUMODEOFSLEEPMODELIST                                                                 [!IF "$sleepCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_POLLINGOFSLEEPMODELIST                                                                 [!IF "$sleepCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_VALIDOFSLEEPMODELIST                                                                   [!IF "$sleepCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_WAKEUPSOURCEOFSLEEPMODELIST                                                            [!IF "$sleepCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_VALIDATIONTIMEOUTTABLE                                                                 STD_OFF
#define ECUM_WAKEUPSOURCELIST                                                                       [!IF "$wkCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_CHECKWAKEUPTIMEOFWAKEUPSOURCELIST                                                      STD_OFF
#define ECUM_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST                                                [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST                                              [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_COMMCHANNELREFSUSEDOFWAKEUPSOURCELIST                                                  [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_COMMPNCREFSENDIDXOFWAKEUPSOURCELIST                                                    STD_OFF
#define ECUM_COMMPNCREFSSTARTIDXOFWAKEUPSOURCELIST                                                  STD_OFF
#define ECUM_COMMPNCREFSUSEDOFWAKEUPSOURCELIST                                                      STD_OFF
#define ECUM_POLLINGOFWAKEUPSOURCELIST                                                              STD_OFF
#define ECUM_REASONOFWAKEUPSOURCELIST                                                               STD_OFF
#define ECUM_VALIDOFWAKEUPSOURCELIST                                                                STD_OFF
#define ECUM_VALIDATIONTIMEOFWAKEUPSOURCELIST                                                       STD_OFF
#define ECUM_PCCONFIG                                                                               STD_ON
#define ECUM_COMMCHANNELREFSOFPCCONFIG                                                              [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_CORESTATUSOFPCCONFIG                                                                   STD_ON
#define ECUM_DEFAULTAPPMODEOFPCCONFIG                                                               STD_ON
#define ECUM_DEFAULTSHUTDOWNMODEOFPCCONFIG                                                          STD_ON
#define ECUM_DEFAULTSHUTDOWNTARGETOFPCCONFIG                                                        STD_ON
#define ECUM_DRIVERINITONEOFPCCONFIG                                                                STD_ON
#define ECUM_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF
#define ECUM_GENERATORCOMPATIBILITYVERSIONOFPCCONFIG                                                STD_ON
#define ECUM_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF
#define ECUM_MAXWAKEUPSOURCECOUNTOFPCCONFIG                                                         STD_ON
#define ECUM_MODULESTATEOFPCCONFIG                                                                  STD_ON
#define ECUM_NORMALMCUMODEOFPCCONFIG                                                                STD_ON
#define ECUM_PARTITIONDATAOFPCCONFIG                                                                STD_ON
#define ECUM_SIZEOFCOMMCHANNELREFSOFPCCONFIG                                                        [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_SIZEOFCORESTATUSOFPCCONFIG                                                             STD_ON
#define ECUM_SIZEOFDRIVERINITONEOFPCCONFIG                                                          STD_ON
#define ECUM_SIZEOFPARTITIONDATAOFPCCONFIG                                                          STD_ON
#define ECUM_SIZEOFWAKEUPSOURCELISTOFPCCONFIG                                                       [!IF "$wkCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_WAKEUPSOURCELISTOFPCCONFIG                                                             [!IF "$wkCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define ECUM_NO_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST                                             255u
#define ECUM_NO_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST                                           255u

#define ECUM_ISDEF_CHANNELOFCOMMCHANNELREFS                                                         [!IF "$comMRefCount = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_ISDEF_CORESTATUS                                                                       STD_OFF
#define ECUM_ISDEF_FUNCTIONOFDRIVERINITONE                                                          STD_OFF
#define ECUM_ISDEF_APPLICATIONOFPARTITIONDATA                                                       STD_OFF
#define ECUM_ISDEF_ECUMPARTITIONOFPARTITIONDATA                                                     STD_ON
#define ECUM_ISDEF_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST                                          STD_OFF
#define ECUM_ISDEF_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST                                        STD_OFF
#define ECUM_ISDEF_COMMCHANNELREFSUSEDOFWAKEUPSOURCELIST                                            STD_OFF
#define ECUM_ISDEF_COMMCHANNELREFSOFPCCONFIG                                                        [!IF "$comMRefCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define ECUM_ISDEF_CORESTATUSOFPCCONFIG                                                             STD_ON
#define ECUM_ISDEF_DRIVERINITONEOFPCCONFIG                                                          STD_ON
#define ECUM_ISDEF_MODULESTATEOFPCCONFIG                                                            STD_ON
#define ECUM_ISDEF_PARTITIONDATAOFPCCONFIG                                                          STD_ON
#define ECUM_ISDEF_WAKEUPSOURCELISTOFPCCONFIG                                                       [!IF "$wkCount > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "$comMRefCount = 1"!][!//
#define ECUM_EQ2_CHANNELOFCOMMCHANNELREFS                                                           ComMConf_ComMChannel_[!"$firstComMChannelName"!]
[!ELSE!][!//
#define ECUM_EQ2_CHANNELOFCOMMCHANNELREFS
[!ENDIF!][!//
#define ECUM_EQ2_CORESTATUS
#define ECUM_EQ2_FUNCTIONOFDRIVERINITONE
#define ECUM_EQ2_APPLICATIONOFPARTITIONDATA
#define ECUM_EQ2_ECUMPARTITIONOFPARTITIONDATA                                                       TRUE
#define ECUM_EQ2_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST
#define ECUM_EQ2_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST
#define ECUM_EQ2_COMMCHANNELREFSUSEDOFWAKEUPSOURCELIST
#define ECUM_EQ2_COMMCHANNELREFSOFPCCONFIG                                                          EcuM_ComMChannelRefs
#define ECUM_EQ2_CORESTATUSOFPCCONFIG                                                               EcuM_CoreStatus
#define ECUM_EQ2_DRIVERINITONEOFPCCONFIG                                                            EcuM_DriverInitOne
#define ECUM_EQ2_MODULESTATEOFPCCONFIG                                                              (&(EcuM_ModuleState))
#define ECUM_EQ2_PARTITIONDATAOFPCCONFIG                                                            EcuM_PartitionData
#define ECUM_EQ2_WAKEUPSOURCELISTOFPCCONFIG                                                         EcuM_WakeupSourceList

#define EcuM_Config_Ptr                                                                             NULL_PTR
#define EcuM_Config                                                                                 NULL_PTR

#define ECUM_CHECK_INIT_POINTER                                                                     STD_OFF
#define ECUM_FINAL_MAGIC_NUMBER                                                                     0x0A1Eu
#define ECUM_INDIVIDUAL_POSTBUILD                                                                   STD_OFF
#define ECUM_INIT_DATA                                                                              ECUM_CONST
#define ECUM_INIT_DATA_HASH_CODE                                                                    1797910197
#define ECUM_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF
#define ECUM_USE_INIT_POINTER                                                                       STD_OFF


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef P2FUNC ( void, ECUM_CODE, EcuM_DriverFuncType)( void );

typedef uint8 EcuM_SizeOfComMChannelRefsType;
typedef uint8 EcuM_SizeOfCoreStatusType;
typedef uint8 EcuM_SizeOfDriverInitOneType;
typedef uint8 EcuM_SizeOfPartitionDataType;
typedef uint8 EcuM_SizeOfWakeupSourceListType;

typedef uint8_least EcuM_ComMChannelRefsIterType;
typedef uint8_least EcuM_CoreStatusIterType;
typedef uint8_least EcuM_DriverInitOneIterType;
typedef uint8_least EcuM_PartitionDataIterType;
typedef uint8_least EcuM_WakeupSourceListIterType;

typedef uint8 EcuM_ChannelOfComMChannelRefsType;
typedef uint32 EcuM_DefaultAppModeType;
typedef uint8 EcuM_DefaultShutdownModeType;
typedef uint16 EcuM_GeneratorCompatibilityVersionType;
typedef uint8 EcuM_MaxWakeupSourceCountType;
typedef uint32 EcuM_NormalMcuModeType;
typedef uint8 EcuM_ApplicationOfPartitionDataType;
typedef boolean EcuM_EcuMPartitionOfPartitionDataType;
typedef uint8 EcuM_ComMChannelRefsEndIdxOfWakeupSourceListType;
typedef uint8 EcuM_ComMChannelRefsStartIdxOfWakeupSourceListType;
typedef boolean EcuM_ComMChannelRefsUsedOfWakeupSourceListType;

[!IF "$comMRefCount > 1"!][!//
typedef struct sEcuM_ComMChannelRefsType
{
  EcuM_ChannelOfComMChannelRefsType ChannelOfComMChannelRefs;
} EcuM_ComMChannelRefsType;
[!ELSE!][!//
typedef struct sEcuM_ComMChannelRefsType
{
  uint8 EcuM_ComMChannelRefsNeverUsed;
} EcuM_ComMChannelRefsType;
[!ENDIF!][!//

typedef struct sEcuM_DriverInitOneType
{
  EcuM_DriverFuncType FunctionOfDriverInitOne;
} EcuM_DriverInitOneType;

typedef struct sEcuM_PartitionDataType
{
  EcuM_ApplicationOfPartitionDataType ApplicationOfPartitionData;
} EcuM_PartitionDataType;

[!IF "$comMRefCount > 0"!][!//
typedef struct sEcuM_WakeupSourceListType
{
  EcuM_ComMChannelRefsEndIdxOfWakeupSourceListType ComMChannelRefsEndIdxOfWakeupSourceList;
  EcuM_ComMChannelRefsStartIdxOfWakeupSourceListType ComMChannelRefsStartIdxOfWakeupSourceList;
} EcuM_WakeupSourceListType;
[!ELSE!][!//
typedef struct sEcuM_WakeupSourceListType
{
  uint8 EcuM_WakeupSourceListNeverUsed;
} EcuM_WakeupSourceListType;
[!ENDIF!][!//

typedef P2CONST(EcuM_ComMChannelRefsType, TYPEDEF, ECUM_CONST) EcuM_ComMChannelRefsPtrType;
typedef P2CONST(EcuM_CoreStatusArrayType, TYPEDEF, ECUM_CONST) EcuM_CoreStatusPtrType;
typedef P2CONST(EcuM_DriverInitOneType, TYPEDEF, ECUM_CONST) EcuM_DriverInitOnePtrType;
typedef P2VAR(EcuM_StateType, TYPEDEF, ECUM_VAR_NO_INIT) EcuM_ModuleStatePtrType;
typedef P2CONST(EcuM_PartitionDataType, TYPEDEF, ECUM_CONST) EcuM_PartitionDataPtrType;
typedef P2CONST(EcuM_WakeupSourceListType, TYPEDEF, ECUM_CONST) EcuM_WakeupSourceListPtrType;
typedef P2CONST(EcuM_DefaultAppModeType, TYPEDEF, ECUM_CONST) EcuM_DefaultAppModeOfPCConfigPtrType;
typedef P2CONST(EcuM_StateType, TYPEDEF, ECUM_CONST) EcuM_DefaultShutdownTargetOfPCConfigPtrType;
typedef P2CONST(EcuM_NormalMcuModeType, TYPEDEF, ECUM_CONST) EcuM_NormalMcuModeOfPCConfigPtrType;

typedef struct sEcuM_PCConfigType
{
  uint8 EcuM_PCConfigNeverUsed;
} EcuM_PCConfigType;

typedef EcuM_PCConfigType EcuM_PbConfigType;

#endif /* ECUM_CFG_H */
[!ENDSELECT!]
