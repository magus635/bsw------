[!SELECT "as:modconf('EcuM')[1]"!][!//
[!IF "not(node:exists(EcuMConfiguration))"!][!ERROR "EcuMConfiguration container is missing in EcuM configuration"!][!ENDIF!][!//
[!VAR "defaultAppMode" = "'OSDEFAULTAPPMODE'"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultAppMode) and (node:refvalid(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultAppMode) = 'true')"!][!//
[!VAR "defaultAppMode" = "node:name(node:ref(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultAppMode))"!][!//
[!ENDIF!][!//
[!VAR "defaultShutdownState" = "'ECUM_STATE_OFF'"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget/EcuMDefaultState)"!][!//
[!VAR "dsVal" = "node:value(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget/EcuMDefaultState)"!][!//
[!IF "$dsVal = 'EcuMStateSleep'"!][!VAR "defaultShutdownState" = "'ECUM_STATE_SLEEP'"!][!//
[!ELSEIF "$dsVal = 'EcuMStateReset'"!][!VAR "defaultShutdownState" = "'ECUM_STATE_RESET'"!][!//
[!ELSE!][!VAR "defaultShutdownState" = "'ECUM_STATE_OFF'"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "defaultShutdownMode" = "num:i(0)"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget/EcuMDefaultShutdownMode)"!][!//
[!VAR "defaultShutdownMode" = "num:i(node:value(EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget/EcuMDefaultShutdownMode))"!][!//
[!ENDIF!][!//
[!VAR "normalMcuMode" = "'McuConf_McuModeSettingConf_McuModeSettingConf_0'"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMFlexConfiguration/EcuMNormalMcuModeRef)"!][!//
[!IF "node:refvalid(EcuMConfiguration/EcuMFlexConfiguration/EcuMNormalMcuModeRef) = 'true'"!][!//
[!VAR "mcuModeLeaf" = "node:name(node:ref(EcuMConfiguration/EcuMFlexConfiguration/EcuMNormalMcuModeRef))"!][!//
[!VAR "normalMcuMode" = "concat('McuConf_McuModeSettingConf_', $mcuModeLeaf)"!][!//
[!ELSE!][!//
[!VAR "mcuRefParts" = "text:split(node:value(EcuMConfiguration/EcuMFlexConfiguration/EcuMNormalMcuModeRef), '/')"!][!//
[!VAR "mcuLeafCount" = "num:i(count($mcuRefParts))"!][!//
[!IF "$mcuLeafCount > 0"!][!//
[!VAR "normalMcuMode" = "concat('McuConf_McuModeSettingConf_', $mcuRefParts[position() = $mcuLeafCount])"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "partCount" = "num:i(count(EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*))"!][!//
[!IF "$partCount = 0"!][!VAR "partCount" = "num:i(1)"!][!ENDIF!][!//
[!VAR "wkCount" = "num:i(count(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*))"!][!//
[!VAR "effWkCount" = "$wkCount"!][!//
[!IF "$effWkCount = 0"!][!VAR "effWkCount" = "num:i(1)"!][!ENDIF!][!//
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
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This file is part of the AUTOSAR BSW Configurator generated output.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EcuM_PrivateCfg.h
 *            Module: EcuM
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#if !defined(ECUM_PRIVATECFG_H)
# define ECUM_PRIVATECFG_H

# if ( (defined ECUM_PRIVATE_CFG_INCLUDE) || (defined ECUM_PRIVATE_CFG_PARTLY_INCLUDE))
# else
#  error "EcuM_PrivateCfg.h must not be included outside of EcuM scope"
# endif

# if (defined ECUM_PRIVATE_CFG_INCLUDE)
#  include "EcuM_Init_PBcfg.h"
# endif

# include "Os.h"
# include "Mcu.h"
# include "Det.h"

# define EcuM_GlobalSuspend()                                         SuspendAllInterrupts()
# define EcuM_GlobalRestore()                                         ResumeAllInterrupts()


/**********************************************************************************************************************
 *  ComStackLib PCConfig Access Macros
 *********************************************************************************************************************/
#define EcuM_GetComMChannelRefsOfPCConfig()                                                         EcuM_ComMChannelRefs
#define EcuM_GetCoreStatusOfPCConfig()                                                              EcuM_CoreStatus
#define EcuM_GetDefaultAppModeOfPCConfig()                                                          [!"$defaultAppMode"!]
#define EcuM_GetDefaultShutdownModeOfPCConfig()                                                     [!"$defaultShutdownMode"!]u
#define EcuM_GetDefaultShutdownTargetOfPCConfig()                                                   [!"$defaultShutdownState"!]
#define EcuM_GetDriverInitOneOfPCConfig()                                                           EcuM_DriverInitOne
#define EcuM_GetGeneratorCompatibilityVersionOfPCConfig()                                           3584u
#define EcuM_GetMaxWakeupSourceCountOfPCConfig()                                                    [!"$wkCount"!]u
#define EcuM_GetModuleStateOfPCConfig()                                                             (&(EcuM_ModuleState))
#define EcuM_GetNormalMcuModeOfPCConfig()                                                           [!"$normalMcuMode"!]
#define EcuM_GetPartitionDataOfPCConfig()                                                           EcuM_PartitionData
#define EcuM_GetSizeOfComMChannelRefsOfPCConfig()                                                   [!"$comMRefCount"!]u
#define EcuM_GetSizeOfCoreStatusOfPCConfig()                                                        [!"$partCount"!]u
#define EcuM_GetSizeOfDriverInitOneOfPCConfig()                                                     1u
#define EcuM_GetSizeOfPartitionDataOfPCConfig()                                                     [!"$partCount"!]u
#define EcuM_GetSizeOfWakeupSourceListOfPCConfig()                                                  [!"$wkCount"!]u
#define EcuM_GetWakeupSourceListOfPCConfig()                                                        EcuM_WakeupSourceList

#define EcuM_GetCoreStatus(Index)                                                                   (EcuM_GetCoreStatusOfPCConfig()[(Index)])
#define EcuM_GetFunctionOfDriverInitOne(Index)                                                      (EcuM_GetDriverInitOneOfPCConfig()[(Index)].FunctionOfDriverInitOne)
#define EcuM_GetModuleState()                                                                       ((*(EcuM_GetModuleStateOfPCConfig())))
#define EcuM_GetApplicationOfPartitionData(Index)                                                   (EcuM_GetPartitionDataOfPCConfig()[(Index)].ApplicationOfPartitionData)
[!IF "$comMRefCount > 0"!][!//
#define EcuM_GetComMChannelRefsEndIdxOfWakeupSourceList(Index)                                      (EcuM_GetWakeupSourceListOfPCConfig()[(Index)].ComMChannelRefsEndIdxOfWakeupSourceList)
#define EcuM_GetComMChannelRefsStartIdxOfWakeupSourceList(Index)                                    (EcuM_GetWakeupSourceListOfPCConfig()[(Index)].ComMChannelRefsStartIdxOfWakeupSourceList)
[!ELSE!][!//
#define EcuM_GetComMChannelRefsEndIdxOfWakeupSourceList(Index)                                      ECUM_NO_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST
#define EcuM_GetComMChannelRefsStartIdxOfWakeupSourceList(Index)                                    ECUM_NO_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST
[!ENDIF!][!//
[!IF "$comMRefCount = 1"!][!//
#define EcuM_GetChannelOfComMChannelRefs(Index)                                                     ComMConf_ComMChannel_[!"$firstComMChannelName"!]
[!ELSEIF "$comMRefCount > 1"!][!//
#define EcuM_GetChannelOfComMChannelRefs(Index)                                                     (EcuM_GetComMChannelRefsOfPCConfig()[(Index)].ChannelOfComMChannelRefs)
[!ELSE!][!//
#define EcuM_GetChannelOfComMChannelRefs(Index)
[!ENDIF!][!//
#define EcuM_GetDefaultAppMode()                                                                    EcuM_GetDefaultAppModeOfPCConfig()
#define EcuM_GetDefaultShutdownMode()                                                               EcuM_GetDefaultShutdownModeOfPCConfig()
#define EcuM_GetDefaultShutdownTarget()                                                             EcuM_GetDefaultShutdownTargetOfPCConfig()
#define EcuM_GetGeneratorCompatibilityVersion()                                                     EcuM_GetGeneratorCompatibilityVersionOfPCConfig()
#define EcuM_GetMaxWakeupSourceCount()                                                              EcuM_GetMaxWakeupSourceCountOfPCConfig()
#define EcuM_GetNormalMcuMode()                                                                     EcuM_GetNormalMcuModeOfPCConfig()
#define EcuM_IsEcuMPartitionOfPartitionData(Index)                                                  (((TRUE)) != FALSE)
#define EcuM_GetSizeOfComMChannelRefs()                                                             EcuM_GetSizeOfComMChannelRefsOfPCConfig()
#define EcuM_GetSizeOfCoreStatus()                                                                  EcuM_GetSizeOfCoreStatusOfPCConfig()
#define EcuM_GetSizeOfDriverInitOne()                                                               EcuM_GetSizeOfDriverInitOneOfPCConfig()
#define EcuM_GetSizeOfPartitionData()                                                               EcuM_GetSizeOfPartitionDataOfPCConfig()
#define EcuM_GetSizeOfWakeupSourceList()                                                            EcuM_GetSizeOfWakeupSourceListOfPCConfig()
#define EcuM_IsComMChannelRefsUsedOfWakeupSourceList(Index)                                         (((boolean)(EcuM_GetComMChannelRefsStartIdxOfWakeupSourceList(Index) != ECUM_NO_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST)) != FALSE)

#define EcuM_SetModuleState(Value)                                                                  (*(EcuM_GetModuleStateOfPCConfig())) = (Value)

#define EcuM_HasComMChannelRefs()                                                                   [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasChannelOfComMChannelRefs()                                                          [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasCoreStatus()                                                                        (TRUE != FALSE)
#define EcuM_HasDefaultAppMode()                                                                    (TRUE != FALSE)
#define EcuM_HasDefaultShutdownMode()                                                               (TRUE != FALSE)
#define EcuM_HasDefaultShutdownTarget()                                                             (TRUE != FALSE)
#define EcuM_HasDriverInitOne()                                                                     (TRUE != FALSE)
#define EcuM_HasFunctionOfDriverInitOne()                                                           (TRUE != FALSE)
#define EcuM_HasGeneratorCompatibilityVersion()                                                     (TRUE != FALSE)
#define EcuM_HasMaxWakeupSourceCount()                                                              (TRUE != FALSE)
#define EcuM_HasModuleState()                                                                       (TRUE != FALSE)
#define EcuM_HasNormalMcuMode()                                                                     (TRUE != FALSE)
#define EcuM_HasPartitionData()                                                                     (TRUE != FALSE)
#define EcuM_HasApplicationOfPartitionData()                                                        (TRUE != FALSE)
#define EcuM_HasEcuMPartitionOfPartitionData()                                                      (TRUE != FALSE)
#define EcuM_HasSizeOfComMChannelRefs()                                                             [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasSizeOfCoreStatus()                                                                  (TRUE != FALSE)
#define EcuM_HasSizeOfDriverInitOne()                                                               (TRUE != FALSE)
#define EcuM_HasSizeOfPartitionData()                                                               (TRUE != FALSE)
#define EcuM_HasSizeOfWakeupSourceList()                                                            (TRUE != FALSE)
#define EcuM_HasWakeupSourceList()                                                                  (TRUE != FALSE)
#define EcuM_HasComMChannelRefsEndIdxOfWakeupSourceList()                                           [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasComMChannelRefsStartIdxOfWakeupSourceList()                                         [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasComMChannelRefsUsedOfWakeupSourceList()                                             [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasPCConfig()                                                                          (TRUE != FALSE)
#define EcuM_HasComMChannelRefsOfPCConfig()                                                         [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasCoreStatusOfPCConfig()                                                              (TRUE != FALSE)
#define EcuM_HasDefaultAppModeOfPCConfig()                                                          (TRUE != FALSE)
#define EcuM_HasDefaultShutdownModeOfPCConfig()                                                     (TRUE != FALSE)
#define EcuM_HasDefaultShutdownTargetOfPCConfig()                                                   (TRUE != FALSE)
#define EcuM_HasDriverInitOneOfPCConfig()                                                           (TRUE != FALSE)
#define EcuM_HasGeneratorCompatibilityVersionOfPCConfig()                                           (TRUE != FALSE)
#define EcuM_HasMaxWakeupSourceCountOfPCConfig()                                                    (TRUE != FALSE)
#define EcuM_HasModuleStateOfPCConfig()                                                             (TRUE != FALSE)
#define EcuM_HasNormalMcuModeOfPCConfig()                                                           (TRUE != FALSE)
#define EcuM_HasPartitionDataOfPCConfig()                                                           (TRUE != FALSE)
#define EcuM_HasSizeOfComMChannelRefsOfPCConfig()                                                   [!IF "$comMRefCount > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define EcuM_HasSizeOfCoreStatusOfPCConfig()                                                        (TRUE != FALSE)
#define EcuM_HasSizeOfDriverInitOneOfPCConfig()                                                     (TRUE != FALSE)
#define EcuM_HasSizeOfPartitionDataOfPCConfig()                                                     (TRUE != FALSE)
#define EcuM_HasSizeOfWakeupSourceListOfPCConfig()                                                  (TRUE != FALSE)
#define EcuM_HasWakeupSourceListOfPCConfig()                                                        (TRUE != FALSE)

#define EcuM_IncModuleState()                                                                       EcuM_GetModuleState()++
#define EcuM_DecModuleState()                                                                       EcuM_GetModuleState()--
#define EcuM_AddModuleState(Value)                                                                  EcuM_SetModuleState((EcuM_GetModuleState() + Value))
#define EcuM_SubModuleState(Value)                                                                  EcuM_SetModuleState((EcuM_GetModuleState() - Value))

# if (defined ECUM_PRIVATE_CFG_INCLUDE)
#  if((ECUM_CONFIGURATION_VARIANT == ECUM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) || (ECUM_POSTBUILD_VARIANT_SUPPORT == STD_ON))
typedef EcuM_GlobalConfigType EcuM_ConfigType;
#  else
typedef uint8 EcuM_ConfigType;
#  endif
# endif

[!IF "$comMRefCount > 1"!][!//
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(EcuM_ComMChannelRefsType, ECUM_CONST) EcuM_ComMChannelRefs[[!"$comMRefCount"!]];
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(EcuM_CoreStatusArrayType, ECUM_CONST) EcuM_CoreStatus[[!"$partCount"!]];
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(EcuM_DriverInitOneType, ECUM_CONST) EcuM_DriverInitOne[1];
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(EcuM_PartitionDataType, ECUM_CONST) EcuM_PartitionData[[!"$partCount"!]];
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(EcuM_WakeupSourceListType, ECUM_CONST) EcuM_WakeupSourceList[[!"$effWkCount"!]];
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(EcuM_StateType, ECUM_VAR_NO_INIT) EcuM_ModuleState;
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define ECUM_START_SEC_CODE
# include "EcuM_MemMap.h"

# if (defined ECUM_PRIVATE_CFG_INCLUDE)
FUNC(void, ECUM_CODE) EcuM_AL_SetProgrammableInterrupts(void);
FUNC(void, ECUM_CODE) EcuM_StartOS(AppModeType appMode);
#if(ECUM_SLAVE_CORE_HANDLING == STD_ON)
FUNC(void, ECUM_CODE) EcuM_WaitForSlaveCores(void);
#endif
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
FUNC(void, ECUM_CODE) EcuM_GptStartClock(Gpt_ChannelType GptChannel, Gpt_ModeType Mode, Gpt_ValueType Value);
FUNC(void, ECUM_CODE) EcuM_GptSetNormal(Gpt_ChannelType GptChannel, Gpt_ModeType Mode);
FUNC(void, ECUM_CODE) EcuM_GptSetSleep(Gpt_ChannelType GptChannel, Gpt_ModeType Mode);
#endif
#if(ECUM_SLEEPMODELIST == STD_ON)
FUNC(uint8, ECUM_CODE) EcuM_CheckRamHash(void);
FUNC(void, ECUM_CODE) EcuM_McuSetMode(Mcu_ModeType McuMode);
FUNC(void, ECUM_CODE) EcuM_SleepActivity(void);
FUNC(void, ECUM_CODE) EcuM_GenerateRamHash(void);
#endif
FUNC(void, ECUM_CODE) EcuM_ShutdownOS(Std_ReturnType ErrCode);
FUNC(void, ECUM_CODE) EcuM_AL_SwitchOff(void);
FUNC(void, ECUM_CODE) EcuM_AL_Reset(EcuM_ResetType Reset);
#  if((ECUM_CONFIGURATION_VARIANT == ECUM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) || (ECUM_POSTBUILD_VARIANT_SUPPORT == STD_ON))
FUNC(EcuM_GlobalConfigRefType, ECUM_CODE) EcuM_DeterminePbConfiguration(void);
#  endif
FUNC(void, ECUM_CODE) EcuM_ErrorHook(Std_ReturnType reason);
#if(ECUM_SLEEPMODELIST == STD_ON)
FUNC(void, ECUM_CODE) EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource);
FUNC(void, ECUM_CODE) EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource);
#endif
FUNC(void, ECUM_CODE) EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource);
FUNC(void, ECUM_CODE) EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource);
FUNC(void, ECUM_CODE) EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource);
FUNC(void, ECUM_CODE) EcuM_OnGoOffOne(void);
FUNC(void, ECUM_CODE) EcuM_OnGoOffTwo(void);
#  if(ECUM_FIXED_BEHAVIOR == STD_ON)
FUNC(void, ECUM_CODE) EcuM_OnEnterRun(void);
FUNC(void, ECUM_CODE) EcuM_OnExitRun(void);
FUNC(void, ECUM_CODE) EcuM_OnGoSleep(void);
FUNC(void, ECUM_CODE) EcuM_OnPrepShutdown(void);
FUNC(void, ECUM_CODE) EcuM_OnExitPostRun(void);
FUNC(void, ECUM_CODE) EcuM_OnFailedNvmWriteAllJobReaction(void);
FUNC(void, ECUM_CODE) EcuM_OnWakeupReaction(void);
FUNC(void, ECUM_CODE) EcuM_OnRTEStartup(void);
#  endif
# endif

extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitZero(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitOne(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverRestartList(void);

# define ECUM_STOP_SEC_CODE
# include "EcuM_MemMap.h"

#endif /* ECUM_PRIVATECFG_H */
[!ENDSELECT!]
