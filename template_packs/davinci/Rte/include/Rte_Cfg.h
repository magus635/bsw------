[!SELECT "as:modconf('Rte')[1]"!][!//
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Rte_Cfg.h
 *            Module: Rte
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *       Description: RTE configuration header file
 *********************************************************************************************************************/

/* double include prevention */
#if !defined (RTE_CFG_H)
# define RTE_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define RTE_CFG_MAJOR_VERSION                                    (4u)
# define RTE_CFG_MINOR_VERSION                                    (38u)

/* RteBswGeneral */
# define RTE_SCHM_VERSION_INFO_API                                [!IF "node:exists(RteBswGeneral/RteSchMVersionInfoApi) and node:value(RteBswGeneral/RteSchMVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_USE_COM_SHADOW_SIGNAL_API                            [!IF "node:exists(RteBswGeneral/RteUseComShadowSignalApi) and node:value(RteBswGeneral/RteUseComShadowSignalApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* RteGeneration */
# define RTE_CALIBRATION_SUPPORT                                  [!IF "node:exists(RteGeneration/RteCalibrationSupport)"!][!"node:value(RteGeneration/RteCalibrationSupport)"!][!ELSE!]NONE[!ENDIF!]
# define RTE_CODE_VENDOR_ID                                       ([!IF "node:exists(RteGeneration/RteCodeVendorId)"!][!"num:i(node:value(RteGeneration/RteCodeVendorId))"!]u[!ELSE!]30u[!ENDIF!])
# define RTE_DEV_ERROR_DETECT                                     [!IF "node:exists(RteGeneration/RteDevErrorDetect) and node:value(RteGeneration/RteDevErrorDetect) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_DEV_ERROR_DETECT_UNINIT                              [!IF "node:exists(RteGeneration/RteDevErrorDetectUninit) and node:value(RteGeneration/RteDevErrorDetectUninit) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_GENERATION_MODE                                      [!IF "node:exists(RteGeneration/RteGenerationMode)"!][!"node:value(RteGeneration/RteGenerationMode)"!][!ELSE!]COMPATIBILITY_MODE[!ENDIF!]
# define RTE_IOC_INTERACTION_RETURN_VALUE                         [!IF "node:exists(RteGeneration/RteIocInteractionReturnValue)"!][!"node:value(RteGeneration/RteIocInteractionReturnValue)"!][!ELSE!]RTE_IOC[!ENDIF!]
# define RTE_MEASUREMENT_SUPPORT                                  [!IF "node:exists(RteGeneration/RteMeasurementSupport) and node:value(RteGeneration/RteMeasurementSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_OPTIMIZATION_MODE                                    [!IF "node:exists(RteGeneration/RteOptimizationMode)"!][!"node:value(RteGeneration/RteOptimizationMode)"!][!ELSE!]RUNTIME[!ENDIF!]
# define RTE_TOOL_CHAIN_SIGNIFICANT_CHARACTERS                    ([!IF "node:exists(RteGeneration/RteToolChainSignificantCharacters)"!][!"num:i(node:value(RteGeneration/RteToolChainSignificantCharacters))"!]u[!ELSE!]31u[!ENDIF!])
# define RTE_VALUE_RANGE_CHECK_ENABLED                            [!IF "node:exists(RteGeneration/RteValueRangeCheckEnabled) and node:value(RteGeneration/RteValueRangeCheckEnabled) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_VFB_TRACE_ENABLED                                    [!IF "node:exists(RteGeneration/RteVfbTraceEnabled) and node:value(RteGeneration/RteVfbTraceEnabled) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_A2L_VERSION                                          [!IF "node:exists(RteGeneration/RteA2LVersion)"!][!"node:value(RteGeneration/RteA2LVersion)"!][!ELSE!]V160[!ENDIF!]
# define RTE_XCP_EVENT_SUPPORT                                    [!IF "node:exists(RteGeneration/RteXcpEventSupport) and node:value(RteGeneration/RteXcpEventSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_CALIBRATION_BUFFER_SIZE                              ([!IF "node:exists(RteGeneration/RteCalibrationBufferSize)"!][!"num:i(node:value(RteGeneration/RteCalibrationBufferSize))"!]u[!ELSE!]0u[!ENDIF!])
# define RTE_ENFORCE_IOC                                          [!IF "node:exists(RteGeneration/RteEnforceIoc) and node:value(RteGeneration/RteEnforceIoc) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_INITIALIZE_IMPLICIT_BUFFERS                          [!IF "node:exists(RteGeneration/RteInitializeImplicitBuffers) and node:value(RteGeneration/RteInitializeImplicitBuffers) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_COM_TIMEOUT_SOURCE                                   [!IF "node:exists(RteGeneration/RteComTimeoutSource)"!][!"node:value(RteGeneration/RteComTimeoutSource)"!][!ELSE!]SWC[!ENDIF!]
# define RTE_ENFORCE_QUEUED_IOC                                   [!IF "node:exists(RteGeneration/RteEnforceQueuedIoc) and node:value(RteGeneration/RteEnforceQueuedIoc) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_USE_ABS_ALARM_INITIALIZATION                         [!IF "node:exists(RteGeneration/RteUseAbsAlarmInitialization) and node:value(RteGeneration/RteUseAbsAlarmInitialization) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_OPTIMIZE_LOCKS_IN_ASIL_PARTITIONS                    [!IF "node:exists(RteGeneration/RteOptimizeLocksInASILPartitions) and node:value(RteGeneration/RteOptimizeLocksInASILPartitions) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_USE_RTE_SEMANTICS_FOR_INTRA_LET_COMMUNICATION        [!IF "node:exists(RteGeneration/UseRteSemanticsForIntraLetCommunication)"!][!IF "node:value(RteGeneration/UseRteSemanticsForIntraLetCommunication) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ELSE!]STD_ON[!ENDIF!]
# define RTE_BASIC_RUNTIME_ENVIRONMENT_MODE                       [!IF "node:exists(RteGeneration/RteBasicRuntimeEnvironmentMode) and node:value(RteGeneration/RteBasicRuntimeEnvironmentMode) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_ENABLE_LET                                           [!IF "node:exists(RteGeneration/RteEnableLET) and node:value(RteGeneration/RteEnableLET) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_ENABLE_MEMORY_PROTECTION                             [!IF "node:exists(RteGeneration/RteEnableMemoryProtection) and node:value(RteGeneration/RteEnableMemoryProtection) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_ENABLE_MULTI_CORE                                    [!IF "node:exists(RteGeneration/RteEnableMultiCore) and node:value(RteGeneration/RteEnableMultiCore) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_DISABLE_INTER_ECU_INT_TO_INT_DATA_CONVERSION           [!IF "node:exists(RteGeneration/RteDisableInterEcuIntToIntDataConversion) and node:value(RteGeneration/RteDisableInterEcuIntToIntDataConversion) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_ALARM_GLOBAL_START_OFFSET                            ([!IF "node:exists(RteGeneration/RteAlarmGlobalStartOffset)"!][!"num:i(node:value(RteGeneration/RteAlarmGlobalStartOffset))"!]u[!ELSE!]1u[!ENDIF!])
# define RTE_DISABLE_RTE_INIT_MEMORY                              [!IF "node:exists(RteGeneration/RteDisableRteInitMemory) and node:value(RteGeneration/RteDisableRteInitMemory) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
# define RTE_DISABLE_OS_SCHEDULE_TABLE_AND_ALARM_GENERATION       [!IF "node:exists(RteGeneration/RteDisableOsScheduleTableAndAlarmGeneration) and node:value(RteGeneration/RteDisableOsScheduleTableAndAlarmGeneration) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* RteInitializationBehavior */
[!IF "node:exists(RteInitializationBehavior/*[1]/RteInitializationStrategy)"!][!//
# define RTE_INITIALIZATION_STRATEGY                              [!"node:value(RteInitializationBehavior/*[1]/RteInitializationStrategy)"!]
[!ENDIF!][!//

/* Configured instance summary counts */
# define RTE_NUM_OF_BSW_MODULE_INSTANCES                          ([!"num:i(count(RteBswModuleInstance/*))"!]u)
# define RTE_NUM_OF_EXCLUSIVE_ACCESS_OPTIMIZATIONS                ([!"num:i(count(RteExclusiveAccessOptimization/*))"!]u)
# define RTE_NUM_OF_VFB_TRACE_CLIENTS                             ([!IF "node:exists(RteGeneration)"!][!"num:i(count(RteGeneration/RteVfbTraceClient/*))"!]u[!ELSE!]0u[!ENDIF!])
# define RTE_NUM_OF_IMPLICIT_COMMUNICATIONS                      ([!"num:i(count(RteImplicitCommunication/*))"!]u)
# define RTE_NUM_OF_INITIALIZATION_BEHAVIORS                      ([!"num:i(count(RteInitializationBehavior/*))"!]u)
# define RTE_NUM_OF_OS_ACTIVATIONS                                ([!IF "node:exists(RteOsInteraction)"!][!"num:i(count(RteOsInteraction/RteUsedOsActivation/*))"!]u[!ELSE!]0u[!ENDIF!])
# define RTE_NUM_OF_SW_COMPONENT_INSTANCES                        ([!"num:i(count(RteSwComponentInstance/*))"!]u)
# define RTE_NUM_OF_SW_COMPONENT_TYPES                            ([!"num:i(count(RteSwComponentType/*))"!]u)
# define RTE_NUM_OF_INITIALIZATION_RUNNABLE_BATCHES               ([!"num:i(count(RteInitializationRunnableBatch/*))"!]u)

#endif /* RTE_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Rte_Cfg.h
 *********************************************************************************************************************/
[!ENDSELECT!][!//
