[!SELECT "as:modconf('ComM')[1]"!][!//
[!VAR "numChannels" = "num:i(count(ComMConfigSet/ComMChannel/*))"!][!//
[!IF "$numChannels < 1"!][!VAR "numChannels" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numUsers" = "num:i(count(ComMConfigSet/ComMUser/*))"!][!//
[!VAR "effUsers" = "$numUsers"!][!//
[!IF "$effUsers < 1"!][!VAR "effUsers" = "num:i(1)"!][!ENDIF!][!//
#if !defined(COMM_PRIVATE_CFG_H)
#define COMM_PRIVATE_CFG_H

# include "ComM_Lcfg.h"

#define ComM_GetFinalMagicNumberOfPCConfig()                                                        0x0C1Eu
#define ComM_GetInitDataHashCodeOfPCConfig()                                                        -1519769143
#define ComM_GetPartitionIdentifiersOfPCConfig()                                                    ComM_PartitionIdentifiers
#define ComM_GetSizeOfPartitionIdentifiersOfPCConfig()                                              1u

#define ComM_GetActiveComModeOfPCPartitionConfig(partitionIndex)                                    ComM_ActiveComMode.raw
#define ComM_GetActivePncComModeOfPCPartitionConfig(partitionIndex)                                 ComM_ActivePncComMode
#define ComM_GetBusComModeReqFrShutdownOfPCPartitionConfig(partitionIndex)                          ComM_BusComModeReqFrShutdown.raw
#define ComM_GetBusComModeReqOfPCPartitionConfig(partitionIndex)                                    ComM_BusComModeReq.raw
#define ComM_GetBusPncComModeReqOfPCPartitionConfig(partitionIndex)                                 ComM_BusPncComModeReq
#define ComM_GetBusSleepModeIndicatedOfPCPartitionConfig(partitionIndex)                            ComM_BusSleepModeIndicated.raw
#define ComM_GetBusSmStateOfPCPartitionConfig(partitionIndex)                                       ComM_BusSmState.raw
#define ComM_GetBusTypeFrOfPCPartitionConfig()                                                      ComM_BusTypeFr
#define ComM_GetChannelOfPCPartitionConfig()                                                        ComM_Channel
#define ComM_GetChannelPbOfPCPartitionConfig()                                                      ComM_ChannelPb
#define ComM_GetComAllowedOfPCPartitionConfig(partitionIndex)                                       ComM_ComAllowed.raw
#define ComM_GetCoordPncWithGwPassiveAndManagedChannelsOfPCPartitionConfig()                        ComM_CoordPncWithGwPassiveAndManagedChannels
#define ComM_GetDcmIndicationOfPCPartitionConfig()                                                  ComM_DcmIndication
#define ComM_GetDcmRequestActiveOfPCPartitionConfig(partitionIndex)                                 ComM_DcmRequestActive.raw
#define ComM_GetEcuMWakeUpIndicatedOfPCPartitionConfig(partitionIndex)                              ComM_EcuMWakeUpIndicated
#define ComM_GetEiraTxSignalIndirectionOfPCPartitionConfig()                                        ComM_EiraTxSignalIndirection
#define ComM_GetExtendedRamCheckOfPCPartitionConfig()                                               ComM_ExtendedRamCheck
#define ComM_GetForwardNmGatewayOfPCPartitionConfig(partitionIndex)                                 ComM_ForwardNmGateway.raw
#define ComM_GetForwardSynchronizedPncShutdownIndicatedOfPCPartitionConfig(partitionIndex)          ComM_ForwardSynchronizedPncShutdownIndicated
#define ComM_GetFrShutdownOfPCPartitionConfig(partitionIndex)                                       ComM_FrShutdown.raw
#define ComM_GetFullComRequestersOfPCPartitionConfig(partitionIndex)                                ComM_FullComRequesters
#define ComM_GetFullCommRequestNotifOfPCPartitionConfig()                                           ComM_FullCommRequestNotif
#define ComM_GetFullNmTypeOfChannelOfPCPartitionConfig()                                            ComM_FullNmTypeOfChannel
#define ComM_GetInhibitionOfPCPartitionConfig(partitionIndex)                                       (&(ComM_Inhibition))
#define ComM_GetInitStatusOfPCPartitionConfig(partitionIndex)                                       (&(ComM_InitStatus))
#define ComM_GetKeepAwakeChannelsOfPCPartitionConfig()                                              ComM_KeepAwakeChannels
#define ComM_GetLastStateChangeOfPCPartitionConfig()                                                ComM_LastStateChange
#define ComM_GetLightNmTypeOfChannelOfPCPartitionConfig()                                           ComM_LightNmTypeOfChannel
#define ComM_GetLinslaveNmTypeOfChannelOfPCPartitionConfig()                                        ComM_LinslaveNmTypeOfChannel
#define ComM_GetMinFullComModeTimerOfPCPartitionConfig(partitionIndex)                              ComM_MinFullComModeTimer.raw
#define ComM_GetModeLimitationOfPCPartitionConfig()                                                 ComM_ModeLimitation
#define ComM_GetNmGwExtOfPCPartitionConfig()                                                        ComM_NmGwExt
#define ComM_GetNmLightTimerOfPCPartitionConfig(partitionIndex)                                     ComM_NmLightTimer.raw
#define ComM_GetNmStartUpIndicatedOfPCPartitionConfig(partitionIndex)                               ComM_NmStartUpIndicated
#define ComM_GetNoneNmTypeOfChannelOfPCPartitionConfig()                                            ComM_NoneNmTypeOfChannel
#define ComM_GetNotifyPncStateChangeOfPCPartitionConfig(partitionIndex)                             (&(ComM_NotifyPncStateChange))
#define ComM_GetNvMStoreReqOfPCPartitionConfig(partitionIndex)                                      (&(ComM_NvMStoreReq))
#define ComM_GetOnlyNoneNmTypeOfChannelOfPCPartitionConfig()                                        ComM_OnlyNoneNmTypeOfChannel
#define ComM_GetPnc0VectorAvoidanceOfPCPartitionConfig()                                            ComM_Pnc0VectorAvoidance
#define ComM_GetPncChannelMappingOfPCPartitionConfig()                                              ComM_PncChannelMapping
#define ComM_GetPncCheckEnabledAtRuntimeOfPCPartitionConfig()                                       ComM_PncCheckEnabledAtRuntime
#define ComM_GetPncEiraRxCountOfPCPartitionConfig()                                                 0u
#define ComM_GetPncEiraRxOfPCPartitionConfig()                                                      ComM_PncEiraRx
#define ComM_GetPncExtendedFunctionalityOfPCPartitionConfig()                                       ComM_PncExtendedFunctionality
#define ComM_GetPncGwTypeActiveOfPCPartitionConfig()                                                ComM_PncGwTypeActive
#define ComM_GetPncGwTypeNoneOfPCPartitionConfig()                                                  ComM_PncGwTypeNone
#define ComM_GetPncGwTypePassiveOfPCPartitionConfig()                                               ComM_PncGwTypePassive
#define ComM_GetPncLimitationOfPCPartitionConfig(partitionIndex)                                    ComM_PncLimitation
#define ComM_GetPncOfPCPartitionConfig()                                                            ComM_Pnc
#define ComM_GetPncPSleepTimerOfPCPartitionConfig(partitionIndex)                                   ComM_PncPSleepTimer
#define ComM_GetPncPbIndOfPCPartitionConfig()                                                       ComM_PncPbInd
#define ComM_GetPncPbOfPCPartitionConfig()                                                          ComM_PncPb
#define ComM_GetPncSignalIndOfPCPartitionConfig()                                                   ComM_PncSignalInd
#define ComM_GetPncSignalOfPCPartitionConfig()                                                      ComM_PncSignal
#define ComM_GetPncSignalValuesOfPCPartitionConfig(partitionIndex)                                  ComM_PncSignalValues
#define ComM_GetPncToChannelRoutingStateOfPCPartitionConfig(partitionIndex)                         ComM_PncToChannelRoutingState.raw
#define ComM_GetPncWithoutChannelsOfPCPartitionConfig()                                             ComM_PncWithoutChannels
#define ComM_GetPostInitializedOfPCPartitionConfig(partitionIndex)                                  ComM_PostInitialized
#define ComM_GetResetRequiredOfPCPartitionConfig(partitionIndex)                                    ComM_ResetRequired.raw
#define ComM_GetSimulatedSmModeOfPCPartitionConfig(partitionIndex)                                  ComM_SimulatedSmMode.raw
#define ComM_GetSizeOfActivePncComModeOfPCPartitionConfig(partitionIndex)                           0u
#define ComM_GetSizeOfBusComModeReqFrShutdownOfPCPartitionConfig(partitionIndex)                    0u
#define ComM_GetSizeOfBusPncComModeReqOfPCPartitionConfig(partitionIndex)                           0u
#define ComM_GetSizeOfBusSleepModeIndicatedOfPCPartitionConfig(partitionIndex)                      0u
#define ComM_GetSizeOfBusTypeFrOfPCPartitionConfig()                                                0u
#define ComM_GetSizeOfChannelOfPCPartitionConfig()                                                  [!"$numChannels"!]u
#define ComM_GetSizeOfChannelPbOfPCPartitionConfig()                                                [!"$numChannels"!]u
#define ComM_GetSizeOfCoordPncWithGwPassiveAndManagedChannelsOfPCPartitionConfig()                  0u
#define ComM_GetSizeOfDcmIndicationOfPCPartitionConfig()                                            [!"$numChannels"!]u
#define ComM_GetSizeOfEcuMWakeUpIndicatedOfPCPartitionConfig(partitionIndex)                        [!"$numChannels"!]u
#define ComM_GetSizeOfEiraTxSignalIndirectionOfPCPartitionConfig()                                  0u
#define ComM_GetSizeOfExtendedRamCheckOfPCPartitionConfig()                                         0u
#define ComM_GetSizeOfForwardNmGatewayOfPCPartitionConfig(partitionIndex)                           0u
#define ComM_GetSizeOfForwardSynchronizedPncShutdownIndicatedOfPCPartitionConfig(partitionIndex)    0u
#define ComM_GetSizeOfFrShutdownOfPCPartitionConfig(partitionIndex)                                 0u
#define ComM_GetSizeOfFullComRequestersOfPCPartitionConfig(partitionIndex)                          0u
#define ComM_GetSizeOfFullCommRequestNotifOfPCPartitionConfig()                                     0u
#define ComM_GetSizeOfFullNmTypeOfChannelOfPCPartitionConfig()                                      0u
#define ComM_GetSizeOfKeepAwakeChannelsOfPCPartitionConfig()                                        [!"$numChannels"!]u
#define ComM_GetSizeOfLastStateChangeOfPCPartitionConfig()                                          0u
#define ComM_GetSizeOfLightNmTypeOfChannelOfPCPartitionConfig()                                     0u
#define ComM_GetSizeOfLinslaveNmTypeOfChannelOfPCPartitionConfig()                                  0u
#define ComM_GetSizeOfMinFullComModeTimerOfPCPartitionConfig(partitionIndex)                        0u
#define ComM_GetSizeOfModeLimitationOfPCPartitionConfig()                                           [!"$numChannels"!]u
#define ComM_GetSizeOfNmGwExtOfPCPartitionConfig()                                                  0u
#define ComM_GetSizeOfNmLightTimerOfPCPartitionConfig(partitionIndex)                               0u
#define ComM_GetSizeOfNmStartUpIndicatedOfPCPartitionConfig(partitionIndex)                         [!"$numChannels"!]u
#define ComM_GetSizeOfNoneNmTypeOfChannelOfPCPartitionConfig()                                      [!"$numChannels"!]u
#define ComM_GetSizeOfOnlyNoneNmTypeOfChannelOfPCPartitionConfig()                                  [!"$numChannels"!]u
#define ComM_GetSizeOfPnc0VectorAvoidanceOfPCPartitionConfig()                                      0u
#define ComM_GetSizeOfPncChannelMappingOfPCPartitionConfig()                                        0u
#define ComM_GetSizeOfPncCheckEnabledAtRuntimeOfPCPartitionConfig()                                 0u
#define ComM_GetSizeOfPncEiraRxOfPCPartitionConfig()                                                0u
#define ComM_GetSizeOfPncExtendedFunctionalityOfPCPartitionConfig()                                 0u
#define ComM_GetSizeOfPncGwTypeActiveOfPCPartitionConfig()                                          0u
#define ComM_GetSizeOfPncGwTypeNoneOfPCPartitionConfig()                                            0u
#define ComM_GetSizeOfPncGwTypePassiveOfPCPartitionConfig()                                         0u
#define ComM_GetSizeOfPncLimitationOfPCPartitionConfig(partitionIndex)                              0u
#define ComM_GetSizeOfPncOfPCPartitionConfig()                                                      0u
#define ComM_GetSizeOfPncPSleepTimerOfPCPartitionConfig(partitionIndex)                             0u
#define ComM_GetSizeOfPncPbIndOfPCPartitionConfig()                                                 0u
#define ComM_GetSizeOfPncPbOfPCPartitionConfig()                                                    0u
#define ComM_GetSizeOfPncSignalIndOfPCPartitionConfig()                                             0u
#define ComM_GetSizeOfPncSignalOfPCPartitionConfig()                                                0u
#define ComM_GetSizeOfPncSignalValuesOfPCPartitionConfig(partitionIndex)                            0u
#define ComM_GetSizeOfPncToChannelRoutingStateOfPCPartitionConfig(partitionIndex)                   0u
#define ComM_GetSizeOfPncWithoutChannelsOfPCPartitionConfig()                                       0u
#define ComM_GetSizeOfPostInitializedOfPCPartitionConfig(partitionIndex)                            1u
#define ComM_GetSizeOfResetRequiredOfPCPartitionConfig(partitionIndex)                              0u
#define ComM_GetSizeOfSimulatedSmModeOfPCPartitionConfig(partitionIndex)                            0u
#define ComM_GetSizeOfStateChangeOfPCPartitionConfig(partitionIndex)                                0u
#define ComM_GetSizeOfSynchronousWakeUpOfPCPartitionConfig()                                        0u
#define ComM_GetSizeOfUserByteMaskOfPCPartitionConfig()                                             [!"$effUsers"!]u
#define ComM_GetSizeOfUserModeNotiFuncOfPCPartitionConfig()                                         0u
#define ComM_GetSizeOfUserModeNotificationOnlyForPncUsersOfPCPartitionConfig()                      [!"$effUsers"!]u
#define ComM_GetSizeOfUserOfPCPartitionConfig()                                                     [!"$effUsers"!]u
#define ComM_GetSizeOfUserPncByteMaskOfPCPartitionConfig()                                          0u
#define ComM_GetSizeOfUserReqFullComOfPCPartitionConfig(partitionIndex)                             [!"$effUsers"!]u
#define ComM_GetSizeOfUserReqPncFullComOfPCPartitionConfig(partitionIndex)                          0u
#define ComM_GetSizeOfUserWithSinglePncOfPCPartitionConfig()                                        0u
#define ComM_GetSizeOfWakeupInhibitionOfPCPartitionConfig()                                         0u
#define ComM_GetStateChangeOfPCPartitionConfig(partitionIndex)                                      ComM_StateChange.raw
#define ComM_GetSynchronousWakeUpOfPCPartitionConfig()                                              ComM_SynchronousWakeUp
#define ComM_GetUserByteMaskOfPCPartitionConfig()                                                   ComM_UserByteMask
#define ComM_GetUserModeNotiFuncOfPCPartitionConfig()                                               ComM_UserModeNotiFunc
#define ComM_GetUserModeNotificationOnlyForPncUsersOfPCPartitionConfig()                            ComM_UserModeNotificationOnlyForPncUsers
#define ComM_GetUserOfPCPartitionConfig()                                                           ComM_User
#define ComM_GetUserPncByteMaskOfPCPartitionConfig()                                                ComM_UserPncByteMask
#define ComM_GetUserReqFullComOfPCPartitionConfig(partitionIndex)                                   ComM_UserReqFullCom
#define ComM_GetUserReqPncFullComOfPCPartitionConfig(partitionIndex)                                ComM_UserReqPncFullCom
#define ComM_GetUserWithSinglePncOfPCPartitionConfig()                                              ComM_UserWithSinglePnc
#define ComM_GetWakeupInhibitionOfPCPartitionConfig()                                               ComM_WakeupInhibition
#define ComM_GetSizeOfActiveComModeOfPCPartitionConfig(partitionIndex)                              ComM_GetSizeOfChannelOfPCPartitionConfig()
#define ComM_GetSizeOfBusComModeReqOfPCPartitionConfig(partitionIndex)                              ComM_GetSizeOfChannelOfPCPartitionConfig()
#define ComM_GetSizeOfBusSmStateOfPCPartitionConfig(partitionIndex)                                 ComM_GetSizeOfChannelOfPCPartitionConfig()
#define ComM_GetSizeOfComAllowedOfPCPartitionConfig(partitionIndex)                                 ComM_GetSizeOfChannelOfPCPartitionConfig()
#define ComM_GetSizeOfDcmRequestActiveOfPCPartitionConfig(partitionIndex)                           ComM_GetSizeOfChannelOfPCPartitionConfig()

#define ComM_GetLTConfigIdxOfPBConfig()                                                             0u
#define ComM_GetPBPartitionConfigOfPBConfig()                                                       NULL_PTR
#define ComM_GetPCConfigIdxOfPBConfig()                                                             0u


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(ComM_ChannelType, COMM_CONST) ComM_Channel[[!"$numChannels"!]];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(ComM_PartitionIdentifiersType, COMM_CONST) ComM_PartitionIdentifiers[1];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(ComM_UserType, COMM_CONST) ComM_User[[!"$effUsers"!]];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_ActiveComModeUType, COMM_VAR_NO_INIT) ComM_ActiveComMode;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_BusComModeReqUType, COMM_VAR_NO_INIT) ComM_BusComModeReq;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_BusSmStateUType, COMM_VAR_NO_INIT) ComM_BusSmState;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_ComAllowedUType, COMM_VAR_NO_INIT) ComM_ComAllowed;
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_DcmRequestActiveUType, COMM_VAR_NO_INIT) ComM_DcmRequestActive;
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern volatile VAR(ComM_EcuMWakeUpIndicatedType, COMM_VAR_NO_INIT) ComM_EcuMWakeUpIndicated[[!"$numChannels"!]];
#define COMM_STOP_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_InhibitionType, COMM_NVM_DATA_NO_INIT) ComM_Inhibition;
#define COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_InitStatusType, COMM_VAR_NO_INIT) ComM_InitStatus;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern volatile VAR(ComM_NmStartUpIndicatedType, COMM_VAR_NO_INIT) ComM_NmStartUpIndicated[[!"$numChannels"!]];
#define COMM_STOP_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_PostInitializedType, COMM_VAR_NO_INIT) ComM_PostInitialized[1];
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(ComM_UserReqFullComType, COMM_VAR_NO_INIT) ComM_UserReqFullCom[[!"$effUsers"!]];
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* COMM_PRIVATE_CFG_H */
[!ENDSELECT!]
