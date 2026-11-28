[!SELECT "as:modconf('ComM')[1]"!][!//
[!IF "not(node:exists(ComMGeneral))"!][!ERROR "ComMGeneral container missing in ComM configuration"!][!ENDIF!][!//
[!VAR "dummyKind" = "'SelfAssignment'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral)"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) and node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) = 'false'"!][!//
[!VAR "dummyKind" = "'None'"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!VAR "dummyKind" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "atomicBitAccess" = "'STD_OFF'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) and node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) = 'true'"!][!VAR "atomicBitAccess" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!VAR "avaVal" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!IF "$avaVal = 'Atomic8BitAccess'"!][!VAR "atomicVarAccess" = "'8u'"!][!//
[!ELSEIF "$avaVal = 'Atomic16BitAccess'"!][!VAR "atomicVarAccess" = "'16u'"!][!//
[!ELSEIF "$avaVal = 'Atomic32BitAccess'"!][!VAR "atomicVarAccess" = "'32u'"!][!//
[!ELSEIF "$avaVal = 'Atomic64BitAccess'"!][!VAR "atomicVarAccess" = "'64u'"!][!ENDIF!][!//
[!ENDIF!][!//
[!VAR "bitOrder" = "'LSB_to_MSB'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!VAR "bitOrder" = "node:value(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!VAR "bitOrder" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!ENDIF!][!//
[!VAR "commProcessor" = "'COMM_PROCESSOR_TONGXIN_THA6206'"!][!//
[!IF "ecu:has('ComM.Processor')"!][!VAR "commProcessor" = "ecu:get('ComM.Processor')"!][!ENDIF!][!//
[!VAR "commCompiler" = "'COMM_COMP_LLVMHIGHTEC'"!][!//
[!IF "ecu:has('ComM.Compiler')"!][!VAR "commCompiler" = "ecu:get('ComM.Compiler')"!][!ENDIF!][!//
[!VAR "devErr" = "'STD_ON'"!][!//
[!IF "node:exists(ComMGeneral/ComMDevErrorDetect) and node:value(ComMGeneral/ComMDevErrorDetect) != 'true'"!][!VAR "devErr" = "'STD_OFF'"!][!ENDIF!][!//
[!VAR "modeLim" = "'STD_ON'"!][!//
[!IF "node:exists(ComMGeneral/ComMModeLimitationEnabled) and node:value(ComMGeneral/ComMModeLimitationEnabled) != 'true'"!][!VAR "modeLim" = "'STD_OFF'"!][!ENDIF!][!//
[!VAR "wuInhib" = "'STD_OFF'"!][!//
[!IF "node:exists(ComMGeneral/ComMWakeupInhibitionEnabled) and node:value(ComMGeneral/ComMWakeupInhibitionEnabled) = 'true'"!][!VAR "wuInhib" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "pncSup" = "'STD_OFF'"!][!//
[!IF "node:exists(ComMGeneral/ComMPncSupport) and node:value(ComMGeneral/ComMPncSupport) = 'true'"!][!VAR "pncSup" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "syncWu" = "'STD_OFF'"!][!//
[!IF "node:exists(ComMGeneral/ComMSynchronousWakeUp) and node:value(ComMGeneral/ComMSynchronousWakeUp) = 'true'"!][!VAR "syncWu" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "numChannels" = "num:i(count(ComMConfigSet/ComMChannel/*))"!][!//
[!IF "$numChannels < 1"!][!VAR "numChannels" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numUsers" = "num:i(count(ComMConfigSet/ComMUser/*))"!][!//
[!VAR "effUsers" = "$numUsers"!][!//
[!IF "$effUsers < 1"!][!VAR "effUsers" = "num:i(1)"!][!ENDIF!][!//
#if !defined(COMM_CFG_H)
#define COMM_CFG_H

#include "ComM_Types.h"
#include "Com_Types.h"
#include "Os.h"

[!IF "$dummyKind = 'SelfAssignment'"!][!//
#ifndef COMM_USE_DUMMY_STATEMENT
#define COMM_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef COMM_DUMMY_STATEMENT
#define COMM_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef COMM_DUMMY_STATEMENT_CONST
#define COMM_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
[!ELSEIF "$dummyKind = 'VoidCast'"!][!//
#ifndef COMM_USE_DUMMY_STATEMENT
#define COMM_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef COMM_DUMMY_STATEMENT
#define COMM_DUMMY_STATEMENT(v) (void)(v)
#endif
#ifndef COMM_DUMMY_STATEMENT_CONST
#define COMM_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
[!ELSE!][!//
#ifndef COMM_USE_DUMMY_STATEMENT
#define COMM_USE_DUMMY_STATEMENT STD_OFF
#endif
#ifndef COMM_DUMMY_STATEMENT
#define COMM_DUMMY_STATEMENT(v)
#endif
#ifndef COMM_DUMMY_STATEMENT_CONST
#define COMM_DUMMY_STATEMENT_CONST(v)
#endif
[!ENDIF!][!//
#ifndef COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD [!"$atomicBitAccess"!]
#endif
#ifndef COMM_ATOMIC_VARIABLE_ACCESS
#define COMM_ATOMIC_VARIABLE_ACCESS [!"$atomicVarAccess"!]
#endif
#ifndef [!"$commProcessor"!]
#define [!"$commProcessor"!]
#endif
#ifndef [!"$commCompiler"!]
#define [!"$commCompiler"!]
#endif
#ifndef COMM_GEN_GENERATOR_MSR
#define COMM_GEN_GENERATOR_MSR
#endif
[!IF "$bitOrder = 'MSB_to_LSB'"!][!//
#ifndef COMM_CPUTYPE_BITORDER_MSB2LSB
#define COMM_CPUTYPE_BITORDER_MSB2LSB
#endif
[!ELSE!][!//
#ifndef COMM_CPUTYPE_BITORDER_LSB2MSB
#define COMM_CPUTYPE_BITORDER_LSB2MSB
#endif
[!ENDIF!][!//
#ifndef COMM_CONFIGURATION_VARIANT_PRECOMPILE
#define COMM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef COMM_CONFIGURATION_VARIANT_LINKTIME
#define COMM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef COMM_CONFIGURATION_VARIANT
#define COMM_CONFIGURATION_VARIANT COMM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef COMM_POSTBUILD_VARIANT_SUPPORT
#define COMM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#ifndef COMM_DEV_ERROR_DETECT
#define COMM_DEV_ERROR_DETECT [!"$devErr"!]
#endif
#ifndef COMM_DEV_ERROR_REPORT
#define COMM_DEV_ERROR_REPORT [!"$devErr"!]
#endif

#define COMM_VERSION_INFO_API                                             [!IF "node:exists(ComMGeneral/ComMVersionInfoApi) and node:value(ComMGeneral/ComMVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_MODE_LIMITATION                                              [!"$modeLim"!]
#define COMM_WAKEUP_INHIBITION                                            [!"$wuInhib"!]
#define COMM_PNC_SUPPORT                                                  [!"$pncSup"!]
#define COMM_PNC_ACTIVE_COORD                                             STD_OFF
#define COMM_PNC_PS_TIMER                                                 0u
#define COMM_ACTIVE_PNC                                                   0u
#define COMM_PNC_EXTENDED_FUNCTIONALITY_ENABLED                           STD_OFF
#define COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED                            STD_OFF
#define COMM_PNC_TO_CHANNEL_ROUTING_LIMITATION_ENABLED                    STD_OFF
#define COMM_PNC_PASSIVE_GW_SUPPORT                                       STD_OFF
#define COMM_PNC_EXISTS_COORD_PNC_WITH_GW_PASSIVE_AND_MANAGED_CHANNELS    STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_ACTIVE                               STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_NONE                                 STD_OFF
#define COMM_PNC_SIGNAL_LENGTH                                            0u
#define COMM_PNC_MAX_NUMBER_OF_EIRA_RX                                    0u
#define COMM_PNC_CHECK_ENABLED_AT_RUNTIME                                 STD_OFF
#define COMM_PNC_0_VECTOR_AVOIDANCE                                       STD_OFF
#define COMM_NM_GW_EXT_ENABLED                                            STD_OFF
#define COMM_KEEP_AWAKE_CHANNELS_SUPPORT                                  STD_ON
#define COMM_BUS_TYPE_INTERNAL_PRESENT                                    STD_OFF
#define COMM_BUS_TYPE_FR_PRESENT                                          STD_OFF
#define COMM_BUS_TYPE_LIN_PRESENT                                         STD_OFF
#define COMM_EXISTS_ONLY_NONE_NMTYPEOFCHANNEL                             STD_ON
#define COMM_FULL_COMM_REQUEST_NOTIF                                      STD_OFF
#define COMM_MAX_NUMBER_OF_USERS                                          [!"$effUsers"!]u
#define COMM_DCM_INDICATION                                               STD_ON
#define COMM_USERMODENOTIFUNC_PNC_USER_ONLY                               STD_ON
#define COMM_EXISTS_USER_WITH_SINGLE_PNC                                  STD_OFF
#define COMM_SYNCHRONOUS_WAKE_UP                                          [!"$syncWu"!]
#define COMM_EXTENDED_RAM_CHECK                                           STD_OFF
#define COMM_NM_VARIANT_FULL_PRESENT                                     STD_OFF
#define COMM_NVM_SUPPORT                                                  STD_OFF
#define COMM_MULTIPARTITION                                               STD_OFF
#define COMM_EXISTS_CHANNEL_ON_MASTER_PARTITION                           STD_ON
#define COMM_EXISTS_USER_ON_SATELLITE_PARTITION                           STD_OFF
#define COMM_EXISTS_USER_ON_MASTER_PARTITION                              STD_ON
#define COMM_ALL_CHANNEL_USER_REQUESTERS_SIZE                             0u
#define COMM_MASTER_PARTITION_IDX                       0u
#define COMM_SINGLEPARTITION                            0u
#define COMM_NO_SYMBOLICNAMEVALUE                       65535u

/* Symbolic Name Values: Users & Channels */
[!IF "node:exists(ComMConfigSet/ComMUser)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMUser/*, 'ComMUserIdentifier')"!][!//
#define ComMConf_ComMUser_[!"node:name(.)"!] [!"num:i(node:value(ComMUserIdentifier))"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
#define ComMConf_ComMChannel_[!"node:name(.)"!] [!"num:i(node:value(ComMChannelId))"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#define COMM_ACTIVECOMMODE                                                                          STD_ON
#define COMM_ACTIVEPNCCOMMODE                                                                       STD_OFF
#define COMM_BUSCOMMODEREQ                                                                          STD_ON
#define COMM_BUSCOMMODEREQFRSHUTDOWN                                                                STD_OFF
#define COMM_BUSPNCCOMMODEREQ                                                                       STD_OFF
#define COMM_BUSSLEEPMODEINDICATED                                                                  STD_OFF
#define COMM_BUSSMSTATE                                                                             STD_ON
#define COMM_BUSTYPEFR                                                                              STD_OFF
#define COMM_CHANNEL                                                                                STD_ON
#define COMM_BUSTYPEOFCHANNEL                                                                       STD_ON
#define COMM_GETCURRENTBUSSMMODEAPIOFCHANNEL                                                        STD_ON
#define COMM_GWTYPEOFCHANNEL                                                                        STD_ON
#define COMM_INHIBITIONINITVALUEOFCHANNEL                                                           STD_ON
#define COMM_INVALIDHNDOFCHANNEL                                                                    STD_OFF
#define COMM_J1939SUPPORTOFCHANNEL                                                                  STD_OFF
#define COMM_MAINFUNCTIONNEEDSSYNCOFCHANNEL                                                         STD_OFF
#define COMM_MANAGINGCHANNELIDOFCHANNEL                                                             STD_ON
#define COMM_MANAGINGCHANNELOFCHANNEL                                                               STD_OFF
#define COMM_MANAGINGUSEROFCHANNEL                                                                  STD_OFF
#define COMM_MINFULLCOMTIMEOFCHANNEL                                                                STD_OFF
#define COMM_NMLIGHTDURATIONOFCHANNEL                                                               STD_OFF
#define COMM_NMLIGHTSILENTDURATIONOFCHANNEL                                                         STD_OFF
#define COMM_NMSUPPORTOFCHANNEL                                                                     STD_OFF
#define COMM_NMTYPEOFCHANNEL                                                                        STD_ON
#define COMM_PARTITIONCONFIGIDXOFCHANNEL                                                            STD_ON
#define COMM_PASSIVEORLINSLAVEOFCHANNEL                                                             STD_OFF
#define COMM_PNCNMREQUESTOFCHANNEL                                                                  STD_OFF
#define COMM_REQUESTBUSSMMODEAPIOFCHANNEL                                                           STD_ON
#define COMM_RESETAFTERFORCINGNOCOMMOFCHANNEL                                                       STD_OFF
#define COMM_SILENTSUPPORTOFCHANNEL                                                                 STD_OFF
#define COMM_WAKEUPSTATEOFCHANNEL                                                                   STD_ON
#define COMM_CHANNELPB                                                                              STD_ON
#define COMM_INVALIDHNDOFCHANNELPB                                                                  STD_OFF
#define COMM_PNCLIMITATIONENDIDXOFCHANNELPB                                                         STD_OFF
#define COMM_PNCLIMITATIONSTARTIDXOFCHANNELPB                                                       STD_OFF
#define COMM_PNCLIMITATIONUSEDOFCHANNELPB                                                           STD_OFF
#define COMM_PNCPBINDENDIDXOFCHANNELPB                                                              STD_OFF
#define COMM_PNCPBINDSTARTIDXOFCHANNELPB                                                            STD_OFF
#define COMM_PNCPBINDUSEDOFCHANNELPB                                                                STD_OFF
#define COMM_USERREQFULLCOMENDIDXOFCHANNELPB                                                        STD_ON
#define COMM_USERREQFULLCOMSTARTIDXOFCHANNELPB                                                      STD_ON
#define COMM_USERREQFULLCOMUSEDOFCHANNELPB                                                          STD_ON
#define COMM_COMALLOWED                                                                             STD_ON
#define COMM_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELS                                                STD_OFF
#define COMM_DCMINDICATION                                                                          STD_ON
#define COMM_DCMREQUESTACTIVE                                                                       STD_ON
#define COMM_ECUMWAKEUPINDICATED                                                                    STD_ON
#define COMM_EIRATXSIGNALINDIRECTION                                                                STD_OFF
#define COMM_EXTENDEDRAMCHECK                                                                       STD_OFF
#define COMM_FINALMAGICNUMBER                                                                       STD_OFF
#define COMM_FORWARDNMGATEWAY                                                                       STD_OFF
#define COMM_FORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATED                                                STD_OFF
#define COMM_FRSHUTDOWN                                                                             STD_OFF
#define COMM_FULLCOMREQUESTERS                                                                      STD_OFF
#define COMM_FULLCOMMREQUESTNOTIF                                                                   STD_OFF
#define COMM_FULLNMTYPEOFCHANNEL                                                                    STD_OFF
#define COMM_INHIBITION                                                                             STD_ON
#define COMM_INITDATAHASHCODE                                                                       STD_OFF
#define COMM_INITSTATUS                                                                             STD_ON
#define COMM_KEEPAWAKECHANNELS                                                                      STD_ON
#define COMM_LASTSTATECHANGE                                                                        STD_OFF
#define COMM_LIGHTNMTYPEOFCHANNEL                                                                   STD_OFF
#define COMM_LINSLAVENMTYPEOFCHANNEL                                                                STD_OFF
#define COMM_MINFULLCOMMODETIMER                                                                    STD_OFF
#define COMM_MODELIMITATION                                                                         [!"$modeLim"!]
#define COMM_NMGWEXT                                                                                STD_OFF
#define COMM_NMLIGHTTIMER                                                                           STD_OFF
#define COMM_NMSTARTUPINDICATED                                                                     STD_ON
#define COMM_NONENMTYPEOFCHANNEL                                                                    STD_ON
#define COMM_NOTIFYPNCSTATECHANGE                                                                   STD_OFF
#define COMM_NVMSTOREREQ                                                                            STD_OFF
#define COMM_ONLYNONENMTYPEOFCHANNEL                                                                STD_ON
#define COMM_PARTITIONIDENTIFIERS                                                                   STD_ON
#define COMM_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                             STD_ON
#define COMM_PARTITIONSNVOFPARTITIONIDENTIFIERS                                                     STD_ON
#define COMM_PNC                                                                                    STD_OFF
#define COMM_CLEARMASKOFPNC                                                                         STD_OFF
#define COMM_COORDINATEDOFPNC                                                                       STD_OFF
#define COMM_INTERMEDIATEPNCCOORDINATOROFPNC                                                        STD_OFF
#define COMM_PNCIDOFPNC                                                                             STD_OFF
#define COMM_SETMASKOFPNC                                                                           STD_OFF
#define COMM_SYSTEMUSEROFPNC                                                                        STD_OFF
#define COMM_TOPLEVELPNCCOORDINATOROFPNC                                                            STD_OFF
#define COMM_WAKEUPENABLEDOFPNC                                                                     STD_OFF
#define COMM_PNC0VECTORAVOIDANCE                                                                    STD_OFF
#define COMM_PNCCHANNELMAPPING                                                                      STD_OFF
#define COMM_PNCCHECKENABLEDATRUNTIME                                                               STD_OFF
#define COMM_PNCEIRARX                                                                              STD_OFF
#define COMM_PNCEIRARXCOUNT                                                                         STD_OFF
#define COMM_PNCEXTENDEDFUNCTIONALITY                                                               STD_OFF
#define COMM_PNCGWTYPEACTIVE                                                                        STD_OFF
#define COMM_PNCGWTYPENONE                                                                          STD_OFF
#define COMM_PNCGWTYPEPASSIVE                                                                       STD_OFF
#define COMM_PNCLIMITATION                                                                          STD_OFF
#define COMM_PNCPSLEEPTIMER                                                                         STD_OFF
#define COMM_PNCPB                                                                                  STD_OFF
#define COMM_PNCCHANNELMAPPINGENDIDXOFPNCPB                                                         STD_OFF
#define COMM_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                                                       STD_OFF
#define COMM_PNCCHANNELMAPPINGUSEDOFPNCPB                                                           STD_OFF
#define COMM_PNCSIGNALINDENDIDXOFPNCPB                                                              STD_OFF
#define COMM_PNCSIGNALINDSTARTIDXOFPNCPB                                                            STD_OFF
#define COMM_PNCSIGNALINDUSEDOFPNCPB                                                                STD_OFF
#define COMM_SIGNALBYTEINDEXOFPNCPB                                                                 STD_OFF
#define COMM_USERREQPNCFULLCOMENDIDXOFPNCPB                                                         STD_OFF
#define COMM_USERREQPNCFULLCOMSTARTIDXOFPNCPB                                                       STD_OFF
#define COMM_PNCPBIND                                                                               STD_OFF
#define COMM_PNCSIGNAL                                                                              STD_OFF
#define COMM_BUSTYPEIDOFPNCSIGNAL                                                                   STD_OFF
#define COMM_CHANNELIDXOFPNCSIGNAL                                                                  STD_OFF
#define COMM_CHANNELUSEDOFPNCSIGNAL                                                                 STD_OFF
#define COMM_TYPEOFPNCSIGNAL                                                                        STD_OFF
#define COMM_PNCSIGNALIND                                                                           STD_OFF
#define COMM_PNCSIGNALVALUES                                                                        STD_OFF
#define COMM_PNCTOCHANNELROUTINGSTATE                                                               STD_OFF
#define COMM_PNCWITHOUTCHANNELS                                                                     STD_OFF
#define COMM_POSTINITIALIZED                                                                        STD_ON
#define COMM_RESETREQUIRED                                                                          STD_OFF
#define COMM_SIMULATEDSMMODE                                                                        STD_OFF
#define COMM_SIZEOFACTIVECOMMODE                                                                    STD_ON
#define COMM_SIZEOFACTIVEPNCCOMMODE                                                                 STD_ON
#define COMM_SIZEOFBUSCOMMODEREQ                                                                    STD_ON
#define COMM_SIZEOFBUSCOMMODEREQFRSHUTDOWN                                                          STD_ON
#define COMM_SIZEOFBUSPNCCOMMODEREQ                                                                 STD_ON
#define COMM_SIZEOFBUSSLEEPMODEINDICATED                                                            STD_ON
#define COMM_SIZEOFBUSSMSTATE                                                                       STD_ON
#define COMM_SIZEOFBUSTYPEFR                                                                        STD_ON
#define COMM_SIZEOFCHANNEL                                                                          STD_ON
#define COMM_SIZEOFCHANNELPB                                                                        STD_ON
#define COMM_SIZEOFCOMALLOWED                                                                       STD_ON
#define COMM_SIZEOFCOORDPNCWITHGWPASSIVEANDMANAGEDCHANNELS                                          STD_ON
#define COMM_SIZEOFDCMINDICATION                                                                    STD_ON
#define COMM_SIZEOFDCMREQUESTACTIVE                                                                 STD_ON
#define COMM_SIZEOFECUMWAKEUPINDICATED                                                              STD_ON
#define COMM_SIZEOFEIRATXSIGNALINDIRECTION                                                          STD_ON
#define COMM_SIZEOFEXTENDEDRAMCHECK                                                                 STD_ON
#define COMM_SIZEOFFORWARDNMGATEWAY                                                                 STD_ON
#define COMM_SIZEOFFORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATED                                          STD_ON
#define COMM_SIZEOFFRSHUTDOWN                                                                       STD_ON
#define COMM_SIZEOFFULLCOMREQUESTERS                                                                STD_ON
#define COMM_SIZEOFFULLCOMMREQUESTNOTIF                                                             STD_ON
#define COMM_SIZEOFFULLNMTYPEOFCHANNEL                                                              STD_ON
#define COMM_SIZEOFKEEPAWAKECHANNELS                                                                STD_ON
#define COMM_SIZEOFLASTSTATECHANGE                                                                  STD_ON
#define COMM_SIZEOFLIGHTNMTYPEOFCHANNEL                                                             STD_ON
#define COMM_SIZEOFLINSLAVENMTYPEOFCHANNEL                                                          STD_ON
#define COMM_SIZEOFMINFULLCOMMODETIMER                                                              STD_ON
#define COMM_SIZEOFMODELIMITATION                                                                   STD_ON
#define COMM_SIZEOFNMGWEXT                                                                          STD_ON
#define COMM_SIZEOFNMLIGHTTIMER                                                                     STD_ON
#define COMM_SIZEOFNMSTARTUPINDICATED                                                               STD_ON
#define COMM_SIZEOFNONENMTYPEOFCHANNEL                                                              STD_ON
#define COMM_SIZEOFONLYNONENMTYPEOFCHANNEL                                                          STD_ON
#define COMM_SIZEOFPARTITIONIDENTIFIERS                                                             STD_ON
#define COMM_SIZEOFPNC                                                                              STD_ON
#define COMM_SIZEOFPNC0VECTORAVOIDANCE                                                              STD_ON
#define COMM_SIZEOFPNCCHANNELMAPPING                                                                STD_ON
#define COMM_SIZEOFPNCCHECKENABLEDATRUNTIME                                                         STD_ON
#define COMM_SIZEOFPNCEIRARX                                                                        STD_ON
#define COMM_SIZEOFPNCEXTENDEDFUNCTIONALITY                                                         STD_ON
#define COMM_SIZEOFPNCGWTYPEACTIVE                                                                  STD_ON
#define COMM_SIZEOFPNCGWTYPENONE                                                                    STD_ON
#define COMM_SIZEOFPNCGWTYPEPASSIVE                                                                 STD_ON
#define COMM_SIZEOFPNCLIMITATION                                                                    STD_ON
#define COMM_SIZEOFPNCPSLEEPTIMER                                                                   STD_ON
#define COMM_SIZEOFPNCPB                                                                            STD_ON
#define COMM_SIZEOFPNCPBIND                                                                         STD_ON
#define COMM_SIZEOFPNCSIGNAL                                                                        STD_ON
#define COMM_SIZEOFPNCSIGNALIND                                                                     STD_ON
#define COMM_SIZEOFPNCSIGNALVALUES                                                                  STD_ON
#define COMM_SIZEOFPNCTOCHANNELROUTINGSTATE                                                         STD_ON
#define COMM_SIZEOFPNCWITHOUTCHANNELS                                                               STD_ON
#define COMM_SIZEOFPOSTINITIALIZED                                                                  STD_ON
#define COMM_SIZEOFRESETREQUIRED                                                                    STD_ON
#define COMM_SIZEOFSIMULATEDSMMODEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFSIMULATEDSMMODE                                                                  STD_ON
#define COMM_SIZEOFSTATECHANGE                                                                      STD_ON
#define COMM_SIZEOFSYNCHRONOUSWAKEUP                                                                STD_ON
#define COMM_SIZEOFUSER                                                                             STD_ON
#define COMM_SIZEOFUSERBYTEMASK                                                                     STD_ON
#define COMM_SIZEOFUSERMODENOTIFUNC                                                                 STD_ON
#define COMM_SIZEOFUSERMODENOTIFICATIONONLYFORPNCUSERS                                              STD_ON
#define COMM_SIZEOFUSERPNCBYTEMASK                                                                  STD_ON
#define COMM_SIZEOFUSERREQFULLCOM                                                                   STD_ON
#define COMM_SIZEOFUSERREQPNCFULLCOM                                                                STD_ON
#define COMM_SIZEOFUSERWITHSINGLEPNC                                                                STD_ON
#define COMM_SIZEOFWAKEUPINHIBITION                                                                 STD_ON
#define COMM_STATECHANGE                                                                            STD_OFF
#define COMM_SYNCHRONOUSWAKEUP                                                                      [!"$syncWu"!]
#define COMM_USER                                                                                   STD_ON
#define COMM_PARTITIONCONFIGIDXOFUSER                                                               STD_ON
#define COMM_PNCUSEROFUSER                                                                          STD_ON
#define COMM_USERBYTEMASKENDIDXOFUSER                                                               STD_ON
#define COMM_USERBYTEMASKSTARTIDXOFUSER                                                             STD_ON
#define COMM_USERBYTEMASKUSEDOFUSER                                                                 STD_ON
#define COMM_USERPNCBYTEMASKENDIDXOFUSER                                                            STD_OFF
#define COMM_USERPNCBYTEMASKLENGTHOFUSER                                                            STD_OFF
#define COMM_USERPNCBYTEMASKSTARTIDXOFUSER                                                          STD_OFF
#define COMM_USERPNCBYTEMASKUSEDOFUSER                                                              STD_OFF
#define COMM_USERBYTEMASK                                                                           STD_ON
#define COMM_CHANNELOFUSERBYTEMASK                                                                  STD_ON
#define COMM_CLEARMASKOFUSERBYTEMASK                                                                STD_ON
#define COMM_SETMASKOFUSERBYTEMASK                                                                  STD_ON
#define COMM_USERREQFULLCOMIDXOFUSERBYTEMASK                                                        STD_ON
#define COMM_USERMODENOTIFUNC                                                                       STD_OFF
#define COMM_USERMODENOTIFICATIONONLYFORPNCUSERS                                                    STD_ON
#define COMM_USERPNCBYTEMASK                                                                        STD_OFF
#define COMM_CLEARMASKOFUSERPNCBYTEMASK                                                             STD_OFF
#define COMM_PNCIDOFUSERPNCBYTEMASK                                                                 STD_OFF
#define COMM_PNCIDXOFUSERPNCBYTEMASK                                                                STD_OFF
#define COMM_SETMASKOFUSERPNCBYTEMASK                                                               STD_OFF
#define COMM_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK                                                  STD_OFF
#define COMM_USERREQFULLCOM                                                                         STD_ON
#define COMM_USERREQPNCFULLCOM                                                                      STD_OFF
#define COMM_USERWITHSINGLEPNC                                                                      STD_OFF
#define COMM_WAKEUPINHIBITION                                                                       STD_OFF
#define COMM_PCCONFIG                                                                               STD_ON
#define COMM_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF
#define COMM_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF
#define COMM_PCPARTITIONCONFIGOFPCCONFIG                                                            STD_ON
#define COMM_PARTITIONIDENTIFIERSOFPCCONFIG                                                         STD_ON
#define COMM_SIZEOFPARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define COMM_PCPARTITIONCONFIG                                                                      STD_ON
#define COMM_ACTIVECOMMODEOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_ACTIVEPNCCOMMODEOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_BUSCOMMODEREQFRSHUTDOWNOFPCPARTITIONCONFIG                                             STD_OFF
#define COMM_BUSCOMMODEREQOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_BUSPNCCOMMODEREQOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_BUSSLEEPMODEINDICATEDOFPCPARTITIONCONFIG                                               STD_OFF
#define COMM_BUSSMSTATEOFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_BUSTYPEFROFPCPARTITIONCONFIG                                                           STD_OFF
#define COMM_CHANNELOFPCPARTITIONCONFIG                                                             STD_ON
#define COMM_CHANNELPBOFPCPARTITIONCONFIG                                                           STD_ON
#define COMM_COMALLOWEDOFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELSOFPCPARTITIONCONFIG                             STD_OFF
#define COMM_DCMINDICATIONOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_DCMREQUESTACTIVEOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ECUMWAKEUPINDICATEDOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_EIRATXSIGNALINDIRECTIONOFPCPARTITIONCONFIG                                             STD_OFF
#define COMM_EXTENDEDRAMCHECKOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_FORWARDNMGATEWAYOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_FORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATEDOFPCPARTITIONCONFIG                             STD_OFF
#define COMM_FRSHUTDOWNOFPCPARTITIONCONFIG                                                          STD_OFF
#define COMM_FULLCOMREQUESTERSOFPCPARTITIONCONFIG                                                   STD_OFF
#define COMM_FULLCOMMREQUESTNOTIFOFPCPARTITIONCONFIG                                                STD_OFF
#define COMM_FULLNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                                 STD_OFF
#define COMM_INHIBITIONOFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_INITSTATUSOFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_KEEPAWAKECHANNELSOFPCPARTITIONCONFIG                                                   STD_ON
#define COMM_LASTSTATECHANGEOFPCPARTITIONCONFIG                                                     STD_OFF
#define COMM_LIGHTNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                                STD_OFF
#define COMM_LINSLAVENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                             STD_OFF
#define COMM_MINFULLCOMMODETIMEROFPCPARTITIONCONFIG                                                 STD_OFF
#define COMM_MODELIMITATIONOFPCPARTITIONCONFIG                                                      STD_ON
#define COMM_NMGWEXTOFPCPARTITIONCONFIG                                                             STD_OFF
#define COMM_NMLIGHTTIMEROFPCPARTITIONCONFIG                                                        STD_OFF
#define COMM_NMSTARTUPINDICATEDOFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_NONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_NOTIFYPNCSTATECHANGEOFPCPARTITIONCONFIG                                                STD_OFF
#define COMM_NVMSTOREREQOFPCPARTITIONCONFIG                                                         STD_OFF
#define COMM_ONLYNONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_PNC0VECTORAVOIDANCEOFPCPARTITIONCONFIG                                                 STD_OFF
#define COMM_PNCCHANNELMAPPINGOFPCPARTITIONCONFIG                                                   STD_OFF
#define COMM_PNCCHECKENABLEDATRUNTIMEOFPCPARTITIONCONFIG                                            STD_OFF
#define COMM_PNCEIRARXCOUNTOFPCPARTITIONCONFIG                                                      STD_OFF
#define COMM_PNCEIRARXOFPCPARTITIONCONFIG                                                           STD_OFF
#define COMM_PNCEXTENDEDFUNCTIONALITYOFPCPARTITIONCONFIG                                            STD_OFF
#define COMM_PNCGWTYPEACTIVEOFPCPARTITIONCONFIG                                                     STD_OFF
#define COMM_PNCGWTYPENONEOFPCPARTITIONCONFIG                                                       STD_OFF
#define COMM_PNCGWTYPEPASSIVEOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_PNCLIMITATIONOFPCPARTITIONCONFIG                                                       STD_OFF
#define COMM_PNCOFPCPARTITIONCONFIG                                                                 STD_OFF
#define COMM_PNCPSLEEPTIMEROFPCPARTITIONCONFIG                                                      STD_OFF
#define COMM_PNCPBINDOFPCPARTITIONCONFIG                                                            STD_OFF
#define COMM_PNCPBOFPCPARTITIONCONFIG                                                               STD_OFF
#define COMM_PNCSIGNALINDOFPCPARTITIONCONFIG                                                        STD_OFF
#define COMM_PNCSIGNALOFPCPARTITIONCONFIG                                                           STD_OFF
#define COMM_PNCSIGNALVALUESOFPCPARTITIONCONFIG                                                     STD_OFF
#define COMM_PNCTOCHANNELROUTINGSTATEOFPCPARTITIONCONFIG                                            STD_OFF
#define COMM_PNCWITHOUTCHANNELSOFPCPARTITIONCONFIG                                                  STD_OFF
#define COMM_POSTINITIALIZEDOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_RESETREQUIREDOFPCPARTITIONCONFIG                                                       STD_OFF
#define COMM_SIMULATEDSMMODEOFPCPARTITIONCONFIG                                                     STD_OFF
#define COMM_SIZEOFACTIVECOMMODEOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFACTIVEPNCCOMMODEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFBUSCOMMODEREQFRSHUTDOWNOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_SIZEOFBUSCOMMODEREQOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFBUSPNCCOMMODEREQOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFBUSSLEEPMODEINDICATEDOFPCPARTITIONCONFIG                                         STD_ON
#define COMM_SIZEOFBUSSMSTATEOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_SIZEOFBUSTYPEFROFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_SIZEOFCHANNELOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_SIZEOFCHANNELPBOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_SIZEOFCOMALLOWEDOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_SIZEOFCOORDPNCWITHGWPASSIVEANDMANAGEDCHANNELSOFPCPARTITIONCONFIG                       STD_ON
#define COMM_SIZEOFDCMINDICATIONOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFDCMREQUESTACTIVEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFECUMWAKEUPINDICATEDOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_SIZEOFEIRATXSIGNALINDIRECTIONOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_SIZEOFEXTENDEDRAMCHECKOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFFORWARDNMGATEWAYOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFFORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATEDOFPCPARTITIONCONFIG                       STD_ON
#define COMM_SIZEOFFRSHUTDOWNOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_SIZEOFFULLCOMREQUESTERSOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFFULLCOMMREQUESTNOTIFOFPCPARTITIONCONFIG                                          STD_ON
#define COMM_SIZEOFFULLNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_SIZEOFKEEPAWAKECHANNELSOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFLASTSTATECHANGEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFLIGHTNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                          STD_ON
#define COMM_SIZEOFLINSLAVENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_SIZEOFMINFULLCOMMODETIMEROFPCPARTITIONCONFIG                                           STD_ON
#define COMM_SIZEOFMODELIMITATIONOFPCPARTITIONCONFIG                                                STD_ON
#define COMM_SIZEOFNMGWEXTOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_SIZEOFNMLIGHTTIMEROFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_SIZEOFNMSTARTUPINDICATEDOFPCPARTITIONCONFIG                                            STD_ON
#define COMM_SIZEOFNONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_SIZEOFONLYNONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_SIZEOFPNC0VECTORAVOIDANCEOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_SIZEOFPNCCHANNELMAPPINGOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFPNCCHECKENABLEDATRUNTIMEOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_SIZEOFPNCEIRARXOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_SIZEOFPNCEXTENDEDFUNCTIONALITYOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_SIZEOFPNCGWTYPEACTIVEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFPNCGWTYPENONEOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFPNCGWTYPEPASSIVEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFPNCLIMITATIONOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFPNCOFPCPARTITIONCONFIG                                                           STD_ON
#define COMM_SIZEOFPNCPSLEEPTIMEROFPCPARTITIONCONFIG                                                STD_ON
#define COMM_SIZEOFPNCPBINDOFPCPARTITIONCONFIG                                                      STD_ON
#define COMM_SIZEOFPNCPBOFPCPARTITIONCONFIG                                                         STD_ON
#define COMM_SIZEOFPNCSIGNALINDOFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_SIZEOFPNCSIGNALOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_SIZEOFPNCSIGNALVALUESOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFPNCTOCHANNELROUTINGSTATEOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_SIZEOFPNCWITHOUTCHANNELSOFPCPARTITIONCONFIG                                            STD_ON
#define COMM_SIZEOFPOSTINITIALIZEDOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFRESETREQUIREDOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_SIZEOFSTATECHANGEOFPCPARTITIONCONFIG                                                   STD_ON
#define COMM_SIZEOFSYNCHRONOUSWAKEUPOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFUSERBYTEMASKOFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_SIZEOFUSERMODENOTIFUNCOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_SIZEOFUSERMODENOTIFICATIONONLYFORPNCUSERSOFPCPARTITIONCONFIG                           STD_ON
#define COMM_SIZEOFUSEROFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_SIZEOFUSERPNCBYTEMASKOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_SIZEOFUSERREQFULLCOMOFPCPARTITIONCONFIG                                                STD_ON
#define COMM_SIZEOFUSERREQPNCFULLCOMOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFUSERWITHSINGLEPNCOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_SIZEOFWAKEUPINHIBITIONOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_STATECHANGEOFPCPARTITIONCONFIG                                                         STD_OFF
#define COMM_SYNCHRONOUSWAKEUPOFPCPARTITIONCONFIG                                                   STD_OFF
#define COMM_USERBYTEMASKOFPCPARTITIONCONFIG                                                        STD_ON
#define COMM_USERMODENOTIFUNCOFPCPARTITIONCONFIG                                                    STD_OFF
#define COMM_USERMODENOTIFICATIONONLYFORPNCUSERSOFPCPARTITIONCONFIG                                 STD_ON
#define COMM_USEROFPCPARTITIONCONFIG                                                                STD_ON
#define COMM_USERPNCBYTEMASKOFPCPARTITIONCONFIG                                                     STD_OFF
#define COMM_USERREQFULLCOMOFPCPARTITIONCONFIG                                                      STD_ON
#define COMM_USERREQPNCFULLCOMOFPCPARTITIONCONFIG                                                   STD_OFF
#define COMM_USERWITHSINGLEPNCOFPCPARTITIONCONFIG                                                   STD_OFF
#define COMM_WAKEUPINHIBITIONOFPCPARTITIONCONFIG                                                    STD_OFF

#define COMM_MIN_FULLCOMREQUESTERS                                                                  0u
#define COMM_MIN_MINFULLCOMMODETIMER                                                                0u
#define COMM_MIN_NMLIGHTTIMER                                                                       0u
#define COMM_MIN_PNCLIMITATION                                                                      0u
#define COMM_MIN_PNCPSLEEPTIMER                                                                     0u
#define COMM_MIN_PNCSIGNALVALUES                                                                    0u
#define COMM_MIN_PNCTOCHANNELROUTINGSTATE                                                           0u
#define COMM_MIN_SIMULATEDSMMODE                                                                    0u
#define COMM_MIN_STATECHANGE                                                                        0u
#define COMM_MIN_USERREQFULLCOM                                                                     0u
#define COMM_MIN_USERREQPNCFULLCOM                                                                  0u
#define COMM_MAX_FULLCOMREQUESTERS                                                                  65535u
#define COMM_MAX_MINFULLCOMMODETIMER                                                                65535u
#define COMM_MAX_NMLIGHTTIMER                                                                       65535u
#define COMM_MAX_PNCLIMITATION                                                                      255u
#define COMM_MAX_PNCPSLEEPTIMER                                                                     65535u
#define COMM_MAX_PNCSIGNALVALUES                                                                    255u
#define COMM_MAX_PNCTOCHANNELROUTINGSTATE                                                           255u
#define COMM_MAX_SIMULATEDSMMODE                                                                    255u
#define COMM_MAX_STATECHANGE                                                                        255u
#define COMM_MAX_USERREQFULLCOM                                                                     255u
#define COMM_MAX_USERREQPNCFULLCOM                                                                  255u

#define COMM_NO_MANAGINGCHANNELIDOFCHANNEL                                                          255u
#define COMM_NO_MANAGINGUSEROFCHANNEL                                                               255u
#define COMM_NO_PNCLIMITATIONENDIDXOFCHANNELPB                                                      255u
#define COMM_NO_PNCLIMITATIONSTARTIDXOFCHANNELPB                                                    255u
#define COMM_NO_PNCPBINDENDIDXOFCHANNELPB                                                           255u
#define COMM_NO_PNCPBINDSTARTIDXOFCHANNELPB                                                         255u
#define COMM_NO_USERREQFULLCOMENDIDXOFCHANNELPB                                                     255u
#define COMM_NO_USERREQFULLCOMSTARTIDXOFCHANNELPB                                                   255u
#define COMM_NO_PNCCHANNELMAPPINGENDIDXOFPNCPB                                                      255u
#define COMM_NO_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                                                    255u
#define COMM_NO_PNCSIGNALINDENDIDXOFPNCPB                                                           255u
#define COMM_NO_PNCSIGNALINDSTARTIDXOFPNCPB                                                         255u
#define COMM_NO_CHANNELIDXOFPNCSIGNAL                                                               255u
#define COMM_NO_USERBYTEMASKENDIDXOFUSER                                                            255u
#define COMM_NO_USERBYTEMASKSTARTIDXOFUSER                                                          255u
#define COMM_NO_USERPNCBYTEMASKENDIDXOFUSER                                                         255u
#define COMM_NO_USERPNCBYTEMASKSTARTIDXOFUSER                                                       255u

#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_NMTYPEOFCHANNEL                                        STD_OFF
#define COMM_EXISTS_FULL_NMTYPEOFCHANNEL                                                            STD_OFF
#define COMM_EXISTS_PASSIVE_NMTYPEOFCHANNEL                                                         STD_OFF
#define COMM_EXISTS_LIGHT_NMTYPEOFCHANNEL                                                           STD_OFF
#define COMM_EXISTS_NONE_NMTYPEOFCHANNEL                                                            STD_ON
#define COMM_EXISTS_LINSLAVE_NMTYPEOFCHANNEL                                                        STD_OFF
#define COMM_EXISTS_EIRA_RX_TYPEOFPNCSIGNAL                                                         STD_OFF
#define COMM_EXISTS_EIRA_TX_TYPEOFPNCSIGNAL                                                         STD_OFF
#define COMM_EXISTS_ERA_RX_TYPEOFPNCSIGNAL                                                          STD_OFF
#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_TYPEOFPNCSIGNAL                                        STD_OFF

#define COMM_NOT_USED_IN_THIS_VARIANT_NMTYPEOFCHANNEL                                               0x00u
#define COMM_FULL_NMTYPEOFCHANNEL                                                                   0x01u
#define COMM_PASSIVE_NMTYPEOFCHANNEL                                                                0x02u
#define COMM_LIGHT_NMTYPEOFCHANNEL                                                                  0x03u
#define COMM_NONE_NMTYPEOFCHANNEL                                                                   0x04u
#define COMM_LINSLAVE_NMTYPEOFCHANNEL                                                               0x05u
#define COMM_EIRA_RX_TYPEOFPNCSIGNAL                                                                0x00u
#define COMM_EIRA_TX_TYPEOFPNCSIGNAL                                                                0x01u
#define COMM_ERA_RX_TYPEOFPNCSIGNAL                                                                 0x02u
#define COMM_NOT_USED_IN_THIS_VARIANT_TYPEOFPNCSIGNAL                                               0x03u

#define COMM_ISDEF_BUSTYPEFR                                                                        STD_OFF
#define COMM_ISDEF_BUSTYPEOFCHANNEL                                                                 STD_ON
#define COMM_ISDEF_GETCURRENTBUSSMMODEAPIOFCHANNEL                                                  STD_OFF
#define COMM_ISDEF_GWTYPEOFCHANNEL                                                                  STD_ON
#define COMM_ISDEF_INHIBITIONINITVALUEOFCHANNEL                                                     STD_ON
#define COMM_ISDEF_INVALIDHNDOFCHANNEL                                                              STD_OFF
#define COMM_ISDEF_J1939SUPPORTOFCHANNEL                                                            STD_OFF
#define COMM_ISDEF_MAINFUNCTIONNEEDSSYNCOFCHANNEL                                                   STD_OFF
#define COMM_ISDEF_MANAGINGCHANNELIDOFCHANNEL                                                       STD_ON
#define COMM_ISDEF_MANAGINGCHANNELOFCHANNEL                                                         STD_OFF
#define COMM_ISDEF_MANAGINGUSEROFCHANNEL                                                            STD_OFF
#define COMM_ISDEF_MINFULLCOMTIMEOFCHANNEL                                                          STD_OFF
#define COMM_ISDEF_NMLIGHTDURATIONOFCHANNEL                                                         STD_OFF
#define COMM_ISDEF_NMLIGHTSILENTDURATIONOFCHANNEL                                                   STD_OFF
#define COMM_ISDEF_NMSUPPORTOFCHANNEL                                                               STD_OFF
#define COMM_ISDEF_NMTYPEOFCHANNEL                                                                  STD_ON
#define COMM_ISDEF_PARTITIONCONFIGIDXOFCHANNEL                                                      STD_ON
#define COMM_ISDEF_PASSIVEORLINSLAVEOFCHANNEL                                                       STD_OFF
#define COMM_ISDEF_PNCNMREQUESTOFCHANNEL                                                            STD_OFF
#define COMM_ISDEF_REQUESTBUSSMMODEAPIOFCHANNEL                                                     STD_OFF
#define COMM_ISDEF_RESETAFTERFORCINGNOCOMMOFCHANNEL                                                 STD_OFF
#define COMM_ISDEF_SILENTSUPPORTOFCHANNEL                                                           STD_OFF
#define COMM_ISDEF_WAKEUPSTATEOFCHANNEL                                                             STD_ON
#define COMM_ISDEF_INVALIDHNDOFCHANNELPB                                                            STD_OFF
#define COMM_ISDEF_PNCLIMITATIONENDIDXOFCHANNELPB                                                   STD_OFF
#define COMM_ISDEF_PNCLIMITATIONSTARTIDXOFCHANNELPB                                                 STD_OFF
#define COMM_ISDEF_PNCLIMITATIONUSEDOFCHANNELPB                                                     STD_OFF
#define COMM_ISDEF_PNCPBINDENDIDXOFCHANNELPB                                                        STD_OFF
#define COMM_ISDEF_PNCPBINDSTARTIDXOFCHANNELPB                                                      STD_OFF
#define COMM_ISDEF_PNCPBINDUSEDOFCHANNELPB                                                          STD_OFF
#define COMM_ISDEF_USERREQFULLCOMENDIDXOFCHANNELPB                                                  [!IF "$numChannels = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_USERREQFULLCOMSTARTIDXOFCHANNELPB                                                [!IF "$numChannels = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_USERREQFULLCOMUSEDOFCHANNELPB                                                    STD_ON
#define COMM_ISDEF_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELS                                          STD_OFF
#define COMM_ISDEF_DCMINDICATION                                                                    STD_ON
#define COMM_ISDEF_EXTENDEDRAMCHECK                                                                 STD_OFF
#define COMM_ISDEF_FULLCOMMREQUESTNOTIF                                                             STD_OFF
#define COMM_ISDEF_FULLNMTYPEOFCHANNEL                                                              STD_OFF
#define COMM_ISDEF_KEEPAWAKECHANNELS                                                                STD_ON
#define COMM_ISDEF_LIGHTNMTYPEOFCHANNEL                                                             STD_OFF
#define COMM_ISDEF_LINSLAVENMTYPEOFCHANNEL                                                          STD_OFF
#define COMM_ISDEF_MODELIMITATION                                                                   STD_ON
#define COMM_ISDEF_NMGWEXT                                                                          STD_OFF
#define COMM_ISDEF_NONENMTYPEOFCHANNEL                                                              STD_ON
#define COMM_ISDEF_ONLYNONENMTYPEOFCHANNEL                                                          STD_ON
#define COMM_ISDEF_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                       STD_OFF
#define COMM_ISDEF_PARTITIONSNVOFPARTITIONIDENTIFIERS                                               STD_OFF
#define COMM_ISDEF_CLEARMASKOFPNC                                                                   STD_OFF
#define COMM_ISDEF_COORDINATEDOFPNC                                                                 STD_OFF
#define COMM_ISDEF_INTERMEDIATEPNCCOORDINATOROFPNC                                                  STD_OFF
#define COMM_ISDEF_PNCIDOFPNC                                                                       STD_OFF
#define COMM_ISDEF_SETMASKOFPNC                                                                     STD_OFF
#define COMM_ISDEF_SYSTEMUSEROFPNC                                                                  STD_OFF
#define COMM_ISDEF_TOPLEVELPNCCOORDINATOROFPNC                                                      STD_OFF
#define COMM_ISDEF_WAKEUPENABLEDOFPNC                                                               STD_OFF
#define COMM_ISDEF_PNC0VECTORAVOIDANCE                                                              STD_OFF
#define COMM_ISDEF_PNCCHANNELMAPPING                                                                STD_OFF
#define COMM_ISDEF_PNCCHECKENABLEDATRUNTIME                                                         STD_OFF
#define COMM_ISDEF_PNCEIRARX                                                                        STD_OFF
#define COMM_ISDEF_PNCEXTENDEDFUNCTIONALITY                                                         STD_OFF
#define COMM_ISDEF_PNCGWTYPEACTIVE                                                                  STD_OFF
#define COMM_ISDEF_PNCGWTYPENONE                                                                    STD_OFF
#define COMM_ISDEF_PNCGWTYPEPASSIVE                                                                 STD_OFF
#define COMM_ISDEF_PNCCHANNELMAPPINGENDIDXOFPNCPB                                                   STD_OFF
#define COMM_ISDEF_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                                                 STD_OFF
#define COMM_ISDEF_PNCCHANNELMAPPINGUSEDOFPNCPB                                                     STD_OFF
#define COMM_ISDEF_PNCSIGNALINDENDIDXOFPNCPB                                                        STD_OFF
#define COMM_ISDEF_PNCSIGNALINDSTARTIDXOFPNCPB                                                      STD_OFF
#define COMM_ISDEF_PNCSIGNALINDUSEDOFPNCPB                                                          STD_OFF
#define COMM_ISDEF_SIGNALBYTEINDEXOFPNCPB                                                           STD_OFF
#define COMM_ISDEF_USERREQPNCFULLCOMENDIDXOFPNCPB                                                   STD_OFF
#define COMM_ISDEF_USERREQPNCFULLCOMSTARTIDXOFPNCPB                                                 STD_OFF
#define COMM_ISDEF_PNCPBIND                                                                         STD_OFF
#define COMM_ISDEF_BUSTYPEIDOFPNCSIGNAL                                                             STD_OFF
#define COMM_ISDEF_CHANNELIDXOFPNCSIGNAL                                                            STD_OFF
#define COMM_ISDEF_CHANNELUSEDOFPNCSIGNAL                                                           STD_OFF
#define COMM_ISDEF_TYPEOFPNCSIGNAL                                                                  STD_OFF
#define COMM_ISDEF_PNCSIGNALIND                                                                     STD_OFF
#define COMM_ISDEF_PNCWITHOUTCHANNELS                                                               STD_OFF
#define COMM_ISDEF_SYNCHRONOUSWAKEUP                                                                STD_OFF
#define COMM_ISDEF_PARTITIONCONFIGIDXOFUSER                                                         STD_ON
#define COMM_ISDEF_PNCUSEROFUSER                                                                    STD_OFF
#define COMM_ISDEF_USERBYTEMASKENDIDXOFUSER                                                         [!IF "$effUsers = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_USERBYTEMASKSTARTIDXOFUSER                                                       [!IF "$effUsers = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_USERBYTEMASKUSEDOFUSER                                                           STD_ON
#define COMM_ISDEF_USERPNCBYTEMASKENDIDXOFUSER                                                      STD_OFF
#define COMM_ISDEF_USERPNCBYTEMASKLENGTHOFUSER                                                      STD_OFF
#define COMM_ISDEF_USERPNCBYTEMASKSTARTIDXOFUSER                                                    STD_OFF
#define COMM_ISDEF_USERPNCBYTEMASKUSEDOFUSER                                                        STD_OFF
#define COMM_ISDEF_CHANNELOFUSERBYTEMASK                                                            [!IF "$numChannels = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_CLEARMASKOFUSERBYTEMASK                                                          STD_ON
#define COMM_ISDEF_SETMASKOFUSERBYTEMASK                                                            STD_ON
#define COMM_ISDEF_USERREQFULLCOMIDXOFUSERBYTEMASK                                                  [!IF "$effUsers = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define COMM_ISDEF_USERMODENOTIFUNC                                                                 STD_OFF
#define COMM_ISDEF_USERMODENOTIFICATIONONLYFORPNCUSERS                                              STD_ON
#define COMM_ISDEF_CLEARMASKOFUSERPNCBYTEMASK                                                       STD_OFF
#define COMM_ISDEF_PNCIDOFUSERPNCBYTEMASK                                                           STD_OFF
#define COMM_ISDEF_PNCIDXOFUSERPNCBYTEMASK                                                          STD_OFF
#define COMM_ISDEF_SETMASKOFUSERPNCBYTEMASK                                                         STD_OFF
#define COMM_ISDEF_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK                                            STD_OFF
#define COMM_ISDEF_USERWITHSINGLEPNC                                                                STD_OFF
#define COMM_ISDEF_WAKEUPINHIBITION                                                                 STD_OFF
#define COMM_ISDEF_PCPARTITIONCONFIGOFPCCONFIG                                                      STD_ON
#define COMM_ISDEF_PARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define COMM_ISDEF_ACTIVECOMMODEOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_ACTIVEPNCCOMMODEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_BUSCOMMODEREQFRSHUTDOWNOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_ISDEF_BUSCOMMODEREQOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_BUSPNCCOMMODEREQOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_BUSSLEEPMODEINDICATEDOFPCPARTITIONCONFIG                                         STD_ON
#define COMM_ISDEF_BUSSMSTATEOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ISDEF_BUSTYPEFROFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_ISDEF_CHANNELOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_ISDEF_CHANNELPBOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_ISDEF_COMALLOWEDOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ISDEF_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELSOFPCPARTITIONCONFIG                       STD_ON
#define COMM_ISDEF_DCMINDICATIONOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_DCMREQUESTACTIVEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_ECUMWAKEUPINDICATEDOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_ISDEF_EIRATXSIGNALINDIRECTIONOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_ISDEF_EXTENDEDRAMCHECKOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_FORWARDNMGATEWAYOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_FORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATEDOFPCPARTITIONCONFIG                       STD_ON
#define COMM_ISDEF_FRSHUTDOWNOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ISDEF_FULLCOMREQUESTERSOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_FULLCOMMREQUESTNOTIFOFPCPARTITIONCONFIG                                          STD_ON
#define COMM_ISDEF_FULLNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_ISDEF_INHIBITIONOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ISDEF_INITSTATUSOFPCPARTITIONCONFIG                                                    STD_ON
#define COMM_ISDEF_KEEPAWAKECHANNELSOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_LASTSTATECHANGEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_LIGHTNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                          STD_ON
#define COMM_ISDEF_LINSLAVENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_ISDEF_MINFULLCOMMODETIMEROFPCPARTITIONCONFIG                                           STD_ON
#define COMM_ISDEF_MODELIMITATIONOFPCPARTITIONCONFIG                                                STD_ON
#define COMM_ISDEF_NMGWEXTOFPCPARTITIONCONFIG                                                       STD_ON
#define COMM_ISDEF_NMLIGHTTIMEROFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_ISDEF_NMSTARTUPINDICATEDOFPCPARTITIONCONFIG                                            STD_ON
#define COMM_ISDEF_NONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_ISDEF_NOTIFYPNCSTATECHANGEOFPCPARTITIONCONFIG                                          STD_ON
#define COMM_ISDEF_NVMSTOREREQOFPCPARTITIONCONFIG                                                   STD_ON
#define COMM_ISDEF_ONLYNONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                       STD_ON
#define COMM_ISDEF_PNC0VECTORAVOIDANCEOFPCPARTITIONCONFIG                                           STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPINGOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_PNCCHECKENABLEDATRUNTIMEOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_ISDEF_PNCEIRARXOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_ISDEF_PNCEXTENDEDFUNCTIONALITYOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_ISDEF_PNCGWTYPEACTIVEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_PNCGWTYPENONEOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_PNCGWTYPEPASSIVEOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_PNCLIMITATIONOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_PNCOFPCPARTITIONCONFIG                                                           STD_ON
#define COMM_ISDEF_PNCPSLEEPTIMEROFPCPARTITIONCONFIG                                                STD_ON
#define COMM_ISDEF_PNCPBINDOFPCPARTITIONCONFIG                                                      STD_ON
#define COMM_ISDEF_PNCPBOFPCPARTITIONCONFIG                                                         STD_ON
#define COMM_ISDEF_PNCSIGNALINDOFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_ISDEF_PNCSIGNALOFPCPARTITIONCONFIG                                                     STD_ON
#define COMM_ISDEF_PNCSIGNALVALUESOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_PNCTOCHANNELROUTINGSTATEOFPCPARTITIONCONFIG                                      STD_ON
#define COMM_ISDEF_PNCWITHOUTCHANNELSOFPCPARTITIONCONFIG                                            STD_ON
#define COMM_ISDEF_POSTINITIALIZEDOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_RESETREQUIREDOFPCPARTITIONCONFIG                                                 STD_ON
#define COMM_ISDEF_SIMULATEDSMMODEOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_STATECHANGEOFPCPARTITIONCONFIG                                                   STD_ON
#define COMM_ISDEF_SYNCHRONOUSWAKEUPOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_USERBYTEMASKOFPCPARTITIONCONFIG                                                  STD_ON
#define COMM_ISDEF_USERMODENOTIFUNCOFPCPARTITIONCONFIG                                              STD_ON
#define COMM_ISDEF_USERMODENOTIFICATIONONLYFORPNCUSERSOFPCPARTITIONCONFIG                           STD_ON
#define COMM_ISDEF_USEROFPCPARTITIONCONFIG                                                          STD_ON
#define COMM_ISDEF_USERPNCBYTEMASKOFPCPARTITIONCONFIG                                               STD_ON
#define COMM_ISDEF_USERREQFULLCOMOFPCPARTITIONCONFIG                                                STD_ON
#define COMM_ISDEF_USERREQPNCFULLCOMOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_USERWITHSINGLEPNCOFPCPARTITIONCONFIG                                             STD_ON
#define COMM_ISDEF_WAKEUPINHIBITIONOFPCPARTITIONCONFIG                                              STD_ON

#define COMM_EQ2_BUSTYPEFR
#define COMM_EQ2_BUSTYPEOFCHANNEL                                                                   COMM_BUS_TYPE_CAN
#define COMM_EQ2_GETCURRENTBUSSMMODEAPIOFCHANNEL
#define COMM_EQ2_GWTYPEOFCHANNEL                                                                    COMM_GATEWAY_TYPE_NONE
#define COMM_EQ2_INHIBITIONINITVALUEOFCHANNEL                                                       0x00u
#define COMM_EQ2_INVALIDHNDOFCHANNEL
#define COMM_EQ2_J1939SUPPORTOFCHANNEL
#define COMM_EQ2_MAINFUNCTIONNEEDSSYNCOFCHANNEL
#define COMM_EQ2_MANAGINGCHANNELIDOFCHANNEL                                                         255u
#define COMM_EQ2_MANAGINGCHANNELOFCHANNEL
#define COMM_EQ2_MANAGINGUSEROFCHANNEL
#define COMM_EQ2_MINFULLCOMTIMEOFCHANNEL
#define COMM_EQ2_NMLIGHTDURATIONOFCHANNEL
#define COMM_EQ2_NMLIGHTSILENTDURATIONOFCHANNEL
#define COMM_EQ2_NMSUPPORTOFCHANNEL
#define COMM_EQ2_NMTYPEOFCHANNEL                                                                    COMM_NONE_NMTYPEOFCHANNEL
#define COMM_EQ2_PARTITIONCONFIGIDXOFCHANNEL                                                        0u
#define COMM_EQ2_PASSIVEORLINSLAVEOFCHANNEL
#define COMM_EQ2_PNCNMREQUESTOFCHANNEL
#define COMM_EQ2_REQUESTBUSSMMODEAPIOFCHANNEL
#define COMM_EQ2_RESETAFTERFORCINGNOCOMMOFCHANNEL
#define COMM_EQ2_SILENTSUPPORTOFCHANNEL
#define COMM_EQ2_WAKEUPSTATEOFCHANNEL                                                               COMM_FULL_COM_NETWORK_REQUESTED
#define COMM_EQ2_INVALIDHNDOFCHANNELPB
#define COMM_EQ2_PNCLIMITATIONENDIDXOFCHANNELPB
#define COMM_EQ2_PNCLIMITATIONSTARTIDXOFCHANNELPB
#define COMM_EQ2_PNCLIMITATIONUSEDOFCHANNELPB
#define COMM_EQ2_PNCPBINDENDIDXOFCHANNELPB
#define COMM_EQ2_PNCPBINDSTARTIDXOFCHANNELPB
#define COMM_EQ2_PNCPBINDUSEDOFCHANNELPB
#define COMM_EQ2_USERREQFULLCOMENDIDXOFCHANNELPB                                                    1u
#define COMM_EQ2_USERREQFULLCOMSTARTIDXOFCHANNELPB                                                  0u
#define COMM_EQ2_USERREQFULLCOMUSEDOFCHANNELPB                                                      TRUE
#define COMM_EQ2_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELS
#define COMM_EQ2_DCMINDICATION                                                                      TRUE
#define COMM_EQ2_EXTENDEDRAMCHECK
#define COMM_EQ2_FULLCOMMREQUESTNOTIF
#define COMM_EQ2_FULLNMTYPEOFCHANNEL
#define COMM_EQ2_KEEPAWAKECHANNELS                                                                  TRUE
#define COMM_EQ2_LIGHTNMTYPEOFCHANNEL
#define COMM_EQ2_LINSLAVENMTYPEOFCHANNEL
#define COMM_EQ2_MODELIMITATION                                                                     TRUE
#define COMM_EQ2_NMGWEXT
#define COMM_EQ2_NONENMTYPEOFCHANNEL                                                                TRUE
#define COMM_EQ2_ONLYNONENMTYPEOFCHANNEL                                                            TRUE
#define COMM_EQ2_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS
#define COMM_EQ2_PARTITIONSNVOFPARTITIONIDENTIFIERS
#define COMM_EQ2_CLEARMASKOFPNC
#define COMM_EQ2_COORDINATEDOFPNC
#define COMM_EQ2_INTERMEDIATEPNCCOORDINATOROFPNC
#define COMM_EQ2_PNCIDOFPNC
#define COMM_EQ2_SETMASKOFPNC
#define COMM_EQ2_SYSTEMUSEROFPNC
#define COMM_EQ2_TOPLEVELPNCCOORDINATOROFPNC
#define COMM_EQ2_WAKEUPENABLEDOFPNC
#define COMM_EQ2_PNC0VECTORAVOIDANCE
#define COMM_EQ2_PNCCHANNELMAPPING
#define COMM_EQ2_PNCCHECKENABLEDATRUNTIME
#define COMM_EQ2_PNCEIRARX
#define COMM_EQ2_PNCEXTENDEDFUNCTIONALITY
#define COMM_EQ2_PNCGWTYPEACTIVE
#define COMM_EQ2_PNCGWTYPENONE
#define COMM_EQ2_PNCGWTYPEPASSIVE
#define COMM_EQ2_PNCCHANNELMAPPINGENDIDXOFPNCPB
#define COMM_EQ2_PNCCHANNELMAPPINGSTARTIDXOFPNCPB
#define COMM_EQ2_PNCCHANNELMAPPINGUSEDOFPNCPB
#define COMM_EQ2_PNCSIGNALINDENDIDXOFPNCPB
#define COMM_EQ2_PNCSIGNALINDSTARTIDXOFPNCPB
#define COMM_EQ2_PNCSIGNALINDUSEDOFPNCPB
#define COMM_EQ2_SIGNALBYTEINDEXOFPNCPB
#define COMM_EQ2_USERREQPNCFULLCOMENDIDXOFPNCPB
#define COMM_EQ2_USERREQPNCFULLCOMSTARTIDXOFPNCPB
#define COMM_EQ2_PNCPBIND
#define COMM_EQ2_BUSTYPEIDOFPNCSIGNAL
#define COMM_EQ2_CHANNELIDXOFPNCSIGNAL
#define COMM_EQ2_CHANNELUSEDOFPNCSIGNAL
#define COMM_EQ2_TYPEOFPNCSIGNAL
#define COMM_EQ2_PNCSIGNALIND
#define COMM_EQ2_PNCWITHOUTCHANNELS
#define COMM_EQ2_SYNCHRONOUSWAKEUP
#define COMM_EQ2_PARTITIONCONFIGIDXOFUSER                                                           0u
#define COMM_EQ2_PNCUSEROFUSER
#define COMM_EQ2_USERBYTEMASKENDIDXOFUSER                                                           1u
#define COMM_EQ2_USERBYTEMASKSTARTIDXOFUSER                                                         0u
#define COMM_EQ2_USERBYTEMASKUSEDOFUSER                                                             TRUE
#define COMM_EQ2_USERPNCBYTEMASKENDIDXOFUSER
#define COMM_EQ2_USERPNCBYTEMASKLENGTHOFUSER
#define COMM_EQ2_USERPNCBYTEMASKSTARTIDXOFUSER
#define COMM_EQ2_USERPNCBYTEMASKUSEDOFUSER
#define COMM_EQ2_CHANNELOFUSERBYTEMASK                                                              0u
#define COMM_EQ2_CLEARMASKOFUSERBYTEMASK                                                            0xFEu
#define COMM_EQ2_SETMASKOFUSERBYTEMASK                                                              0x01u
#define COMM_EQ2_USERREQFULLCOMIDXOFUSERBYTEMASK                                                    0u
#define COMM_EQ2_USERMODENOTIFUNC
#define COMM_EQ2_USERMODENOTIFICATIONONLYFORPNCUSERS                                                TRUE
#define COMM_EQ2_CLEARMASKOFUSERPNCBYTEMASK
#define COMM_EQ2_PNCIDOFUSERPNCBYTEMASK
#define COMM_EQ2_PNCIDXOFUSERPNCBYTEMASK
#define COMM_EQ2_SETMASKOFUSERPNCBYTEMASK
#define COMM_EQ2_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK
#define COMM_EQ2_USERWITHSINGLEPNC
#define COMM_EQ2_WAKEUPINHIBITION
#define COMM_EQ2_PCPARTITIONCONFIGOFPCCONFIG                                                        ComM_PCPartitionConfig
#define COMM_EQ2_PARTITIONIDENTIFIERSOFPCCONFIG                                                     ComM_PartitionIdentifiers
#define COMM_EQ2_ACTIVECOMMODEOFPCPARTITIONCONFIG                                                   ComM_ActiveComMode.raw
#define COMM_EQ2_ACTIVEPNCCOMMODEOFPCPARTITIONCONFIG                                                ComM_ActivePncComMode
#define COMM_EQ2_BUSCOMMODEREQFRSHUTDOWNOFPCPARTITIONCONFIG                                         ComM_BusComModeReqFrShutdown.raw
#define COMM_EQ2_BUSCOMMODEREQOFPCPARTITIONCONFIG                                                   ComM_BusComModeReq.raw
#define COMM_EQ2_BUSPNCCOMMODEREQOFPCPARTITIONCONFIG                                                ComM_BusPncComModeReq
#define COMM_EQ2_BUSSLEEPMODEINDICATEDOFPCPARTITIONCONFIG                                           ComM_BusSleepModeIndicated.raw
#define COMM_EQ2_BUSSMSTATEOFPCPARTITIONCONFIG                                                      ComM_BusSmState.raw
#define COMM_EQ2_BUSTYPEFROFPCPARTITIONCONFIG                                                       ComM_BusTypeFr
#define COMM_EQ2_CHANNELOFPCPARTITIONCONFIG                                                         ComM_Channel
#define COMM_EQ2_CHANNELPBOFPCPARTITIONCONFIG                                                       ComM_ChannelPb
#define COMM_EQ2_COMALLOWEDOFPCPARTITIONCONFIG                                                      ComM_ComAllowed.raw
#define COMM_EQ2_COORDPNCWITHGWPASSIVEANDMANAGEDCHANNELSOFPCPARTITIONCONFIG                         ComM_CoordPncWithGwPassiveAndManagedChannels
#define COMM_EQ2_DCMINDICATIONOFPCPARTITIONCONFIG                                                   ComM_DcmIndication
#define COMM_EQ2_DCMREQUESTACTIVEOFPCPARTITIONCONFIG                                                ComM_DcmRequestActive.raw
#define COMM_EQ2_ECUMWAKEUPINDICATEDOFPCPARTITIONCONFIG                                             ComM_EcuMWakeUpIndicated
#define COMM_EQ2_EIRATXSIGNALINDIRECTIONOFPCPARTITIONCONFIG                                         ComM_EiraTxSignalIndirection
#define COMM_EQ2_EXTENDEDRAMCHECKOFPCPARTITIONCONFIG                                                ComM_ExtendedRamCheck
#define COMM_EQ2_FORWARDNMGATEWAYOFPCPARTITIONCONFIG                                                ComM_ForwardNmGateway.raw
#define COMM_EQ2_FORWARDSYNCHRONIZEDPNCSHUTDOWNINDICATEDOFPCPARTITIONCONFIG                         ComM_ForwardSynchronizedPncShutdownIndicated
#define COMM_EQ2_FRSHUTDOWNOFPCPARTITIONCONFIG                                                      ComM_FrShutdown.raw
#define COMM_EQ2_FULLCOMREQUESTERSOFPCPARTITIONCONFIG                                               ComM_FullComRequesters
#define COMM_EQ2_FULLCOMMREQUESTNOTIFOFPCPARTITIONCONFIG                                            ComM_FullCommRequestNotif
#define COMM_EQ2_FULLNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                             ComM_FullNmTypeOfChannel
#define COMM_EQ2_INHIBITIONOFPCPARTITIONCONFIG                                                      (&(ComM_Inhibition))
#define COMM_EQ2_INITSTATUSOFPCPARTITIONCONFIG                                                      (&(ComM_InitStatus))
#define COMM_EQ2_KEEPAWAKECHANNELSOFPCPARTITIONCONFIG                                               ComM_KeepAwakeChannels
#define COMM_EQ2_LASTSTATECHANGEOFPCPARTITIONCONFIG                                                 ComM_LastStateChange
#define COMM_EQ2_LIGHTNMTYPEOFCHANNELOFPCPARTITIONCONFIG                                            ComM_LightNmTypeOfChannel
#define COMM_EQ2_LINSLAVENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                         ComM_LinslaveNmTypeOfChannel
#define COMM_EQ2_MINFULLCOMMODETIMEROFPCPARTITIONCONFIG                                             ComM_MinFullComModeTimer.raw
#define COMM_EQ2_MODELIMITATIONOFPCPARTITIONCONFIG                                                  ComM_ModeLimitation
#define COMM_EQ2_NMGWEXTOFPCPARTITIONCONFIG                                                         ComM_NmGwExt
#define COMM_EQ2_NMLIGHTTIMEROFPCPARTITIONCONFIG                                                    ComM_NmLightTimer.raw
#define COMM_EQ2_NMSTARTUPINDICATEDOFPCPARTITIONCONFIG                                              ComM_NmStartUpIndicated
#define COMM_EQ2_NONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                             ComM_NoneNmTypeOfChannel
#define COMM_EQ2_NOTIFYPNCSTATECHANGEOFPCPARTITIONCONFIG                                            (&(ComM_NotifyPncStateChange))
#define COMM_EQ2_NVMSTOREREQOFPCPARTITIONCONFIG                                                     (&(ComM_NvMStoreReq))
#define COMM_EQ2_ONLYNONENMTYPEOFCHANNELOFPCPARTITIONCONFIG                                         ComM_OnlyNoneNmTypeOfChannel
#define COMM_EQ2_PNC0VECTORAVOIDANCEOFPCPARTITIONCONFIG                                             ComM_Pnc0VectorAvoidance
#define COMM_EQ2_PNCCHANNELMAPPINGOFPCPARTITIONCONFIG                                               ComM_PncChannelMapping
#define COMM_EQ2_PNCCHECKENABLEDATRUNTIMEOFPCPARTITIONCONFIG                                        ComM_PncCheckEnabledAtRuntime
#define COMM_EQ2_PNCEIRARXOFPCPARTITIONCONFIG                                                       ComM_PncEiraRx
#define COMM_EQ2_PNCEXTENDEDFUNCTIONALITYOFPCPARTITIONCONFIG                                        ComM_PncExtendedFunctionality
#define COMM_EQ2_PNCGWTYPEACTIVEOFPCPARTITIONCONFIG                                                 ComM_PncGwTypeActive
#define COMM_EQ2_PNCGWTYPENONEOFPCPARTITIONCONFIG                                                   ComM_PncGwTypeNone
#define COMM_EQ2_PNCGWTYPEPASSIVEOFPCPARTITIONCONFIG                                                ComM_PncGwTypePassive
#define COMM_EQ2_PNCLIMITATIONOFPCPARTITIONCONFIG                                                   ComM_PncLimitation
#define COMM_EQ2_PNCOFPCPARTITIONCONFIG                                                             ComM_Pnc
#define COMM_EQ2_PNCPSLEEPTIMEROFPCPARTITIONCONFIG                                                  ComM_PncPSleepTimer
#define COMM_EQ2_PNCPBINDOFPCPARTITIONCONFIG                                                        ComM_PncPbInd
#define COMM_EQ2_PNCPBOFPCPARTITIONCONFIG                                                           ComM_PncPb
#define COMM_EQ2_PNCSIGNALINDOFPCPARTITIONCONFIG                                                    ComM_PncSignalInd
#define COMM_EQ2_PNCSIGNALOFPCPARTITIONCONFIG                                                       ComM_PncSignal
#define COMM_EQ2_PNCSIGNALVALUESOFPCPARTITIONCONFIG                                                 ComM_PncSignalValues
#define COMM_EQ2_PNCTOCHANNELROUTINGSTATEOFPCPARTITIONCONFIG                                        ComM_PncToChannelRoutingState.raw
#define COMM_EQ2_PNCWITHOUTCHANNELSOFPCPARTITIONCONFIG                                              ComM_PncWithoutChannels
#define COMM_EQ2_POSTINITIALIZEDOFPCPARTITIONCONFIG                                                 ComM_PostInitialized
#define COMM_EQ2_RESETREQUIREDOFPCPARTITIONCONFIG                                                   ComM_ResetRequired.raw
#define COMM_EQ2_SIMULATEDSMMODEOFPCPARTITIONCONFIG                                                 ComM_SimulatedSmMode.raw
#define COMM_EQ2_STATECHANGEOFPCPARTITIONCONFIG                                                     ComM_StateChange.raw
#define COMM_EQ2_SYNCHRONOUSWAKEUPOFPCPARTITIONCONFIG                                               ComM_SynchronousWakeUp
#define COMM_EQ2_USERBYTEMASKOFPCPARTITIONCONFIG                                                    ComM_UserByteMask
#define COMM_EQ2_USERMODENOTIFUNCOFPCPARTITIONCONFIG                                                ComM_UserModeNotiFunc
#define COMM_EQ2_USERMODENOTIFICATIONONLYFORPNCUSERSOFPCPARTITIONCONFIG                             ComM_UserModeNotificationOnlyForPncUsers
#define COMM_EQ2_USEROFPCPARTITIONCONFIG                                                            ComM_User
#define COMM_EQ2_USERPNCBYTEMASKOFPCPARTITIONCONFIG                                                 ComM_UserPncByteMask
#define COMM_EQ2_USERREQFULLCOMOFPCPARTITIONCONFIG                                                  ComM_UserReqFullCom
#define COMM_EQ2_USERREQPNCFULLCOMOFPCPARTITIONCONFIG                                               ComM_UserReqPncFullCom
#define COMM_EQ2_USERWITHSINGLEPNCOFPCPARTITIONCONFIG                                               ComM_UserWithSinglePnc
#define COMM_EQ2_WAKEUPINHIBITIONOFPCPARTITIONCONFIG                                                ComM_WakeupInhibition

#define ComM_ActivePncComMode                                                                       ((ComM_ActivePncComModePtrType)(NULL_PTR))
#define ComM_BusComModeReqFrShutdown                                                                ((ComM_BusComModeReqFrShutdownPtrType)(NULL_PTR))
#define ComM_BusPncComModeReq                                                                       ((ComM_BusPncComModeReqPtrType)(NULL_PTR))
#define ComM_BusSleepModeIndicated                                                                  ((ComM_BusSleepModeIndicatedPtrType)(NULL_PTR))
#define ComM_BusTypeFr                                                                              ((ComM_BusTypeFrPtrType)(NULL_PTR))
#define ComM_ChannelPb                                                                              ((ComM_ChannelPbPtrType)(NULL_PTR))
#define ComM_CoordPncWithGwPassiveAndManagedChannels                                                ((ComM_CoordPncWithGwPassiveAndManagedChannelsPtrType)(NULL_PTR))
#define ComM_EiraTxSignalIndirection                                                                ((ComM_EiraTxSignalIndirectionPtrType)(NULL_PTR))
#define ComM_ExtendedRamCheck                                                                       ((ComM_ExtendedRamCheckPtrType)(NULL_PTR))
#define ComM_ForwardNmGateway                                                                       ((ComM_ForwardNmGatewayPtrType)(NULL_PTR))
#define ComM_ForwardSynchronizedPncShutdownIndicated                                                ((ComM_ForwardSynchronizedPncShutdownIndicatedPtrType)(NULL_PTR))
#define ComM_FrShutdown                                                                             ((ComM_FrShutdownPtrType)(NULL_PTR))
#define ComM_FullComRequesters                                                                      ((ComM_FullComRequestersPtrType)(NULL_PTR))
#define ComM_FullCommRequestNotif                                                                   ((ComM_FullCommRequestNotifPtrType)(NULL_PTR))
#define ComM_FullNmTypeOfChannel                                                                    ((ComM_FullNmTypeOfChannelPtrType)(NULL_PTR))
#define ComM_LastStateChange                                                                        ((ComM_LastStateChangePtrType)(NULL_PTR))
#define ComM_LightNmTypeOfChannel                                                                   ((ComM_LightNmTypeOfChannelPtrType)(NULL_PTR))
#define ComM_LinslaveNmTypeOfChannel                                                                ((ComM_LinslaveNmTypeOfChannelPtrType)(NULL_PTR))
#define ComM_MinFullComModeTimer                                                                    ((ComM_MinFullComModeTimerPtrType)(NULL_PTR))
#define ComM_NmGwExt                                                                                ((ComM_NmGwExtPtrType)(NULL_PTR))
#define ComM_NmLightTimer                                                                           ((ComM_NmLightTimerPtrType)(NULL_PTR))
#define ComM_NotifyPncStateChange                                                                   ((ComM_NotifyPncStateChangePtrType)(NULL_PTR))
#define ComM_NvMStoreReq                                                                            ((ComM_NvMStoreReqPtrType)(NULL_PTR))
#define ComM_Pnc                                                                                    ((ComM_PncPtrType)(NULL_PTR))
#define ComM_Pnc0VectorAvoidance                                                                    ((ComM_Pnc0VectorAvoidancePtrType)(NULL_PTR))
#define ComM_PncChannelMapping                                                                      ((ComM_PncChannelMappingPtrType)(NULL_PTR))
#define ComM_PncCheckEnabledAtRuntime                                                               ((ComM_PncCheckEnabledAtRuntimePtrType)(NULL_PTR))
#define ComM_PncEiraRx                                                                              ((ComM_PncEiraRxPtrType)(NULL_PTR))
#define ComM_PncExtendedFunctionality                                                               ((ComM_PncExtendedFunctionalityPtrType)(NULL_PTR))
#define ComM_PncGwTypeActive                                                                        ((ComM_PncGwTypeActivePtrType)(NULL_PTR))
#define ComM_PncGwTypeNone                                                                          ((ComM_PncGwTypeNonePtrType)(NULL_PTR))
#define ComM_PncGwTypePassive                                                                       ((ComM_PncGwTypePassivePtrType)(NULL_PTR))
#define ComM_PncLimitation                                                                          ((ComM_PncLimitationPtrType)(NULL_PTR))
#define ComM_PncPSleepTimer                                                                         ((ComM_PncPSleepTimerPtrType)(NULL_PTR))
#define ComM_PncPb                                                                                  ((ComM_PncPbPtrType)(NULL_PTR))
#define ComM_PncPbInd                                                                               ((ComM_PncPbIndPtrType)(NULL_PTR))
#define ComM_PncSignal                                                                              ((ComM_PncSignalPtrType)(NULL_PTR))
#define ComM_PncSignalInd                                                                           ((ComM_PncSignalIndPtrType)(NULL_PTR))
#define ComM_PncSignalValues                                                                        ((ComM_PncSignalValuesPtrType)(NULL_PTR))
#define ComM_PncToChannelRoutingState                                                               ((ComM_PncToChannelRoutingStatePtrType)(NULL_PTR))
#define ComM_PncWithoutChannels                                                                     ((ComM_PncWithoutChannelsPtrType)(NULL_PTR))
#define ComM_ResetRequired                                                                          ((ComM_ResetRequiredPtrType)(NULL_PTR))
#define ComM_SimulatedSmMode                                                                        ((ComM_SimulatedSmModePtrType)(NULL_PTR))
#define ComM_StateChange                                                                            ((ComM_StateChangePtrType)(NULL_PTR))
#define ComM_SynchronousWakeUp                                                                      ((ComM_SynchronousWakeUpPtrType)(NULL_PTR))
#define ComM_UserByteMask                                                                           ((ComM_UserByteMaskPtrType)(NULL_PTR))
#define ComM_UserModeNotiFunc                                                                       ((ComM_UserModeNotiFuncPtrType)(NULL_PTR))
#define ComM_UserPncByteMask                                                                        ((ComM_UserPncByteMaskPtrType)(NULL_PTR))
#define ComM_UserReqPncFullCom                                                                      ((ComM_UserReqPncFullComPtrType)(NULL_PTR))
#define ComM_UserWithSinglePnc                                                                      ((ComM_UserWithSinglePncPtrType)(NULL_PTR))
#define ComM_WakeupInhibition                                                                       ((ComM_WakeupInhibitionPtrType)(NULL_PTR))

#define ComM_Config_Ptr                                                                             NULL_PTR
#define ComM_Config                                                                                 NULL_PTR

#define COMM_CHECK_INIT_POINTER                                                                     STD_OFF
#define COMM_FINAL_MAGIC_NUMBER                                                                     0x0C1Eu
#define COMM_INDIVIDUAL_POSTBUILD                                                                   STD_OFF
#define COMM_INIT_DATA                                                                              COMM_CONST
#define COMM_INIT_DATA_HASH_CODE                                                                    -215872543
#define COMM_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF
#define COMM_USE_INIT_POINTER                                                                       STD_OFF

#define COMM_PBCONFIG                                                                               STD_OFF
#define COMM_LTCONFIGIDXOFPBCONFIG                                                                  STD_OFF
#define COMM_PBPARTITIONCONFIGOFPBCONFIG                                                            STD_OFF
#define COMM_PCCONFIGIDXOFPBCONFIG                                                                  STD_OFF
#define COMM_PBPARTITIONCONFIG                                                                      STD_OFF
#define COMM_ISDEF_LTCONFIGIDXOFPBCONFIG                                                            STD_OFF
#define COMM_ISDEF_PBPARTITIONCONFIGOFPBCONFIG                                                      STD_OFF
#define COMM_ISDEF_PCCONFIGIDXOFPBCONFIG                                                            STD_OFF
#define COMM_EQ2_LTCONFIGIDXOFPBCONFIG
#define COMM_EQ2_PBPARTITIONCONFIGOFPBCONFIG
#define COMM_EQ2_PCCONFIGIDXOFPBCONFIG


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef P2FUNC(Std_ReturnType, COMM_CODE, ComM_StateNotiFuncPtrType) (Rte_ModeType_ComMMode  nextMode);
typedef P2FUNC(Std_ReturnType, COMM_CODE, RequestBusSMModeApiType) (NetworkHandleType Channel, ComM_ModeType ComMode);
typedef P2FUNC(Std_ReturnType, COMM_CODE, GetCurrentBusSMModeApiType) (NetworkHandleType Channel, P2VAR(ComM_ModeType, AUTOMATIC, AUTOMATIC) ComMode);

typedef uint8 ComM_SizeOfActiveComModeType;
typedef uint8 ComM_SizeOfActivePncComModeType;
typedef uint8 ComM_SizeOfBusComModeReqType;
typedef uint8 ComM_SizeOfBusComModeReqFrShutdownType;
typedef uint8 ComM_SizeOfBusPncComModeReqType;
typedef uint8 ComM_SizeOfBusSleepModeIndicatedType;
typedef uint8 ComM_SizeOfBusSmStateType;
typedef uint8 ComM_SizeOfBusTypeFrType;
typedef uint8 ComM_SizeOfChannelType;
typedef uint8 ComM_SizeOfChannelPbType;
typedef uint8 ComM_SizeOfComAllowedType;
typedef uint8 ComM_SizeOfCoordPncWithGwPassiveAndManagedChannelsType;
typedef uint8 ComM_SizeOfDcmIndicationType;
typedef uint8 ComM_SizeOfDcmRequestActiveType;
typedef uint8 ComM_SizeOfEcuMWakeUpIndicatedType;
typedef uint8 ComM_SizeOfEiraTxSignalIndirectionType;
typedef uint8 ComM_SizeOfExtendedRamCheckType;
typedef uint8 ComM_SizeOfForwardNmGatewayType;
typedef uint8 ComM_SizeOfForwardSynchronizedPncShutdownIndicatedType;
typedef uint8 ComM_SizeOfFrShutdownType;
typedef uint8 ComM_SizeOfFullComRequestersType;
typedef uint8 ComM_SizeOfFullCommRequestNotifType;
typedef uint8 ComM_SizeOfFullNmTypeOfChannelType;
typedef uint8 ComM_SizeOfKeepAwakeChannelsType;
typedef uint8 ComM_SizeOfLastStateChangeType;
typedef uint8 ComM_SizeOfLightNmTypeOfChannelType;
typedef uint8 ComM_SizeOfLinslaveNmTypeOfChannelType;
typedef uint8 ComM_SizeOfMinFullComModeTimerType;
typedef uint8 ComM_SizeOfModeLimitationType;
typedef uint8 ComM_SizeOfNmGwExtType;
typedef uint8 ComM_SizeOfNmLightTimerType;
typedef uint8 ComM_SizeOfNmStartUpIndicatedType;
typedef uint8 ComM_SizeOfNoneNmTypeOfChannelType;
typedef uint8 ComM_SizeOfOnlyNoneNmTypeOfChannelType;
typedef uint8 ComM_SizeOfPartitionIdentifiersType;
typedef uint8 ComM_SizeOfPncType;
typedef uint8 ComM_SizeOfPnc0VectorAvoidanceType;
typedef uint8 ComM_SizeOfPncChannelMappingType;
typedef uint8 ComM_SizeOfPncCheckEnabledAtRuntimeType;
typedef uint8 ComM_SizeOfPncEiraRxType;
typedef uint8 ComM_SizeOfPncExtendedFunctionalityType;
typedef uint8 ComM_SizeOfPncGwTypeActiveType;
typedef uint8 ComM_SizeOfPncGwTypeNoneType;
typedef uint8 ComM_SizeOfPncGwTypePassiveType;
typedef uint8 ComM_SizeOfPncLimitationType;
typedef uint8 ComM_SizeOfPncPSleepTimerType;
typedef uint8 ComM_SizeOfPncPbType;
typedef uint8 ComM_SizeOfPncPbIndType;
typedef uint8 ComM_SizeOfPncSignalType;
typedef uint8 ComM_SizeOfPncSignalIndType;
typedef uint8 ComM_SizeOfPncSignalValuesType;
typedef uint8 ComM_SizeOfPncToChannelRoutingStateType;
typedef uint8 ComM_SizeOfPncWithoutChannelsType;
typedef uint8 ComM_SizeOfPostInitializedType;
typedef uint8 ComM_SizeOfResetRequiredType;
typedef uint8 ComM_SizeOfSimulatedSmModeType;
typedef uint8 ComM_SizeOfStateChangeType;
typedef uint8 ComM_SizeOfSynchronousWakeUpType;
typedef uint8 ComM_SizeOfUserType;
typedef uint8 ComM_SizeOfUserByteMaskType;
typedef uint8 ComM_SizeOfUserModeNotiFuncType;
typedef uint8 ComM_SizeOfUserModeNotificationOnlyForPncUsersType;
typedef uint8 ComM_SizeOfUserPncByteMaskType;
typedef uint8 ComM_SizeOfUserReqFullComType;
typedef uint8 ComM_SizeOfUserReqPncFullComType;
typedef uint8 ComM_SizeOfUserWithSinglePncType;
typedef uint8 ComM_SizeOfWakeupInhibitionType;

typedef uint8_least ComM_BusTypeFrIterType;
typedef uint8_least ComM_ChannelIterType;
typedef uint8_least ComM_ChannelPbIterType;
typedef uint8_least ComM_CoordPncWithGwPassiveAndManagedChannelsIterType;
typedef uint8_least ComM_DcmIndicationIterType;
typedef uint8_least ComM_EcuMWakeUpIndicatedIterType;
typedef uint8_least ComM_EiraTxSignalIndirectionIterType;
typedef uint8_least ComM_ExtendedRamCheckIterType;
typedef uint8_least ComM_FullComRequestersIterType;
typedef uint8_least ComM_FullCommRequestNotifIterType;
typedef uint8_least ComM_FullNmTypeOfChannelIterType;
typedef uint8_least ComM_KeepAwakeChannelsIterType;
typedef uint8_least ComM_LightNmTypeOfChannelIterType;
typedef uint8_least ComM_LinslaveNmTypeOfChannelIterType;
typedef uint8_least ComM_ModeLimitationIterType;
typedef uint8_least ComM_NmGwExtIterType;
typedef uint8_least ComM_NmStartUpIndicatedIterType;
typedef uint8_least ComM_NoneNmTypeOfChannelIterType;
typedef uint8_least ComM_OnlyNoneNmTypeOfChannelIterType;
typedef uint8_least ComM_PartitionIdentifiersIterType;
typedef uint8_least ComM_PncIterType;
typedef uint8_least ComM_Pnc0VectorAvoidanceIterType;
typedef uint8_least ComM_PncChannelMappingIterType;
typedef uint8_least ComM_PncCheckEnabledAtRuntimeIterType;
typedef uint8_least ComM_PncEiraRxIterType;
typedef uint8_least ComM_PncExtendedFunctionalityIterType;
typedef uint8_least ComM_PncGwTypeActiveIterType;
typedef uint8_least ComM_PncGwTypeNoneIterType;
typedef uint8_least ComM_PncGwTypePassiveIterType;
typedef uint8_least ComM_PncLimitationIterType;
typedef uint8_least ComM_PncPbIterType;
typedef uint8_least ComM_PncPbIndIterType;
typedef uint8_least ComM_PncSignalIterType;
typedef uint8_least ComM_PncSignalIndIterType;
typedef uint8_least ComM_PncSignalValuesIterType;
typedef uint8_least ComM_PncWithoutChannelsIterType;
typedef uint8_least ComM_PostInitializedIterType;
typedef uint8_least ComM_SynchronousWakeUpIterType;
typedef uint8_least ComM_UserIterType;
typedef uint8_least ComM_UserByteMaskIterType;
typedef uint8_least ComM_UserModeNotiFuncIterType;
typedef uint8_least ComM_UserModeNotificationOnlyForPncUsersIterType;
typedef uint8_least ComM_UserPncByteMaskIterType;
typedef uint8_least ComM_UserReqFullComIterType;
typedef uint8_least ComM_UserReqPncFullComIterType;
typedef uint8_least ComM_UserWithSinglePncIterType;
typedef uint8_least ComM_WakeupInhibitionIterType;
typedef uint8_least ComM_PCPartitionConfigIterType;
typedef ComM_ChannelIterType ComM_ActiveComModeIterType;
typedef ComM_PncIterType ComM_ActivePncComModeIterType;
typedef ComM_ChannelIterType ComM_BusComModeReqIterType;
typedef ComM_ChannelIterType ComM_BusComModeReqFrShutdownIterType;
typedef ComM_PncIterType ComM_BusPncComModeReqIterType;
typedef ComM_ChannelIterType ComM_BusSleepModeIndicatedIterType;
typedef ComM_ChannelIterType ComM_BusSmStateIterType;
typedef ComM_ChannelIterType ComM_ComAllowedIterType;
typedef ComM_ChannelIterType ComM_DcmRequestActiveIterType;
typedef ComM_ChannelIterType ComM_ForwardNmGatewayIterType;
typedef ComM_PncIterType ComM_ForwardSynchronizedPncShutdownIndicatedIterType;
typedef ComM_ChannelIterType ComM_FrShutdownIterType;
typedef ComM_UserIterType ComM_LastStateChangeIterType;
typedef ComM_ChannelIterType ComM_MinFullComModeTimerIterType;
typedef ComM_ChannelIterType ComM_NmLightTimerIterType;
typedef ComM_PncIterType ComM_PncPSleepTimerIterType;
typedef ComM_ChannelIterType ComM_PncToChannelRoutingStateIterType;
typedef ComM_ChannelIterType ComM_ResetRequiredIterType;
typedef ComM_ChannelIterType ComM_SimulatedSmModeIterType;
typedef ComM_ChannelIterType ComM_StateChangeIterType;

typedef boolean ComM_BusSleepModeIndicatedType;
typedef boolean ComM_BusTypeFrType;
typedef uint8 ComM_GwTypeOfChannelType;
typedef uint8 ComM_InhibitionInitValueOfChannelType;
typedef boolean ComM_InvalidHndOfChannelType;
typedef boolean ComM_J1939SupportOfChannelType;
typedef boolean ComM_MainFunctionNeedsSyncOfChannelType;
typedef uint8 ComM_ManagingChannelIdOfChannelType;
typedef boolean ComM_ManagingChannelOfChannelType;
typedef uint8 ComM_ManagingUserOfChannelType;
typedef uint8 ComM_MinFullComTimeOfChannelType;
typedef uint8 ComM_NmLightDurationOfChannelType;
typedef uint8 ComM_NmLightSilentDurationOfChannelType;
typedef boolean ComM_NmSupportOfChannelType;
typedef uint8 ComM_NmTypeOfChannelType;
typedef uint8 ComM_PartitionConfigIdxOfChannelType;
typedef boolean ComM_PassiveOrLinSlaveOfChannelType;
typedef boolean ComM_PncNmRequestOfChannelType;
typedef boolean ComM_ResetAfterForcingNoCommOfChannelType;
typedef boolean ComM_SilentSupportOfChannelType;
typedef uint8 ComM_WakeupStateOfChannelType;
typedef boolean ComM_InvalidHndOfChannelPbType;
typedef uint8 ComM_PncLimitationEndIdxOfChannelPbType;
typedef uint8 ComM_PncLimitationStartIdxOfChannelPbType;
typedef boolean ComM_PncLimitationUsedOfChannelPbType;
typedef uint8 ComM_PncPbIndEndIdxOfChannelPbType;
typedef uint8 ComM_PncPbIndStartIdxOfChannelPbType;
typedef boolean ComM_PncPbIndUsedOfChannelPbType;
typedef uint8 ComM_UserReqFullComEndIdxOfChannelPbType;
typedef uint8 ComM_UserReqFullComStartIdxOfChannelPbType;
typedef boolean ComM_UserReqFullComUsedOfChannelPbType;
typedef boolean ComM_ComAllowedType;
typedef boolean ComM_CoordPncWithGwPassiveAndManagedChannelsType;
typedef boolean ComM_DcmIndicationType;
typedef boolean ComM_DcmRequestActiveType;
typedef boolean ComM_EcuMWakeUpIndicatedType;
typedef boolean ComM_ExtendedRamCheckType;
typedef uint16 ComM_FinalMagicNumberType;
typedef boolean ComM_ForwardNmGatewayType;
typedef boolean ComM_ForwardSynchronizedPncShutdownIndicatedType;
typedef boolean ComM_FrShutdownType;
typedef uint16 ComM_FullComRequestersType;
typedef boolean ComM_FullCommRequestNotifType;
typedef boolean ComM_FullNmTypeOfChannelType;
typedef sint32 ComM_InitDataHashCodeType;
typedef boolean ComM_KeepAwakeChannelsType;
typedef boolean ComM_LightNmTypeOfChannelType;
typedef boolean ComM_LinslaveNmTypeOfChannelType;
typedef uint16 ComM_MinFullComModeTimerType;
typedef boolean ComM_ModeLimitationType;
typedef boolean ComM_NmGwExtType;
typedef uint16 ComM_NmLightTimerType;
typedef boolean ComM_NmStartUpIndicatedType;
typedef boolean ComM_NoneNmTypeOfChannelType;
typedef boolean ComM_NotifyPncStateChangeType;
typedef boolean ComM_NvMStoreReqType;
typedef boolean ComM_OnlyNoneNmTypeOfChannelType;
typedef uint32 ComM_PartitionSNVOfPartitionIdentifiersType;
typedef uint8 ComM_ClearMaskOfPncType;
typedef boolean ComM_CoordinatedOfPncType;
typedef boolean ComM_IntermediatePncCoordinatorOfPncType;
typedef uint8 ComM_PncIdOfPncType;
typedef uint8 ComM_SetMaskOfPncType;
typedef uint8 ComM_SystemUserOfPncType;
typedef boolean ComM_TopLevelPncCoordinatorOfPncType;
typedef boolean ComM_WakeupEnabledOfPncType;
typedef boolean ComM_Pnc0VectorAvoidanceType;
typedef uint8 ComM_PncChannelMappingType;
typedef boolean ComM_PncCheckEnabledAtRuntimeType;
typedef boolean ComM_PncEiraRxType;
typedef uint8 ComM_PncEiraRxCountType;
typedef boolean ComM_PncExtendedFunctionalityType;
typedef boolean ComM_PncGwTypeActiveType;
typedef boolean ComM_PncGwTypeNoneType;
typedef boolean ComM_PncGwTypePassiveType;
typedef uint8 ComM_PncLimitationType;
typedef uint16 ComM_PncPSleepTimerType;
typedef uint8 ComM_PncChannelMappingEndIdxOfPncPbType;
typedef uint8 ComM_PncChannelMappingStartIdxOfPncPbType;
typedef boolean ComM_PncChannelMappingUsedOfPncPbType;
typedef uint8 ComM_PncSignalIndEndIdxOfPncPbType;
typedef uint8 ComM_PncSignalIndStartIdxOfPncPbType;
typedef boolean ComM_PncSignalIndUsedOfPncPbType;
typedef uint8 ComM_SignalByteIndexOfPncPbType;
typedef uint8 ComM_UserReqPncFullComEndIdxOfPncPbType;
typedef uint8 ComM_UserReqPncFullComStartIdxOfPncPbType;
typedef uint8 ComM_PncPbIndType;
typedef uint8 ComM_BusTypeIdOfPncSignalType;
typedef uint8 ComM_ChannelIdxOfPncSignalType;
typedef boolean ComM_ChannelUsedOfPncSignalType;
typedef uint8 ComM_TypeOfPncSignalType;
typedef uint8 ComM_PncSignalIndType;
typedef uint8 ComM_PncSignalValuesType;
typedef uint8 ComM_PncToChannelRoutingStateType;
typedef boolean ComM_PncWithoutChannelsType;
typedef boolean ComM_PostInitializedType;
typedef boolean ComM_ResetRequiredType;
typedef uint8 ComM_SimulatedSmModeType;
typedef uint8 ComM_StateChangeType;
typedef boolean ComM_SynchronousWakeUpType;
typedef uint8 ComM_PartitionConfigIdxOfUserType;
typedef boolean ComM_PncUserOfUserType;
typedef uint8 ComM_UserByteMaskEndIdxOfUserType;
typedef uint8 ComM_UserByteMaskStartIdxOfUserType;
typedef boolean ComM_UserByteMaskUsedOfUserType;
typedef uint8 ComM_UserPncByteMaskEndIdxOfUserType;
typedef uint8 ComM_UserPncByteMaskLengthOfUserType;
typedef uint8 ComM_UserPncByteMaskStartIdxOfUserType;
typedef boolean ComM_UserPncByteMaskUsedOfUserType;
typedef uint8 ComM_ChannelOfUserByteMaskType;
typedef uint8 ComM_ClearMaskOfUserByteMaskType;
typedef uint8 ComM_SetMaskOfUserByteMaskType;
typedef uint8 ComM_UserReqFullComIdxOfUserByteMaskType;
typedef boolean ComM_UserModeNotificationOnlyForPncUsersType;
typedef uint8 ComM_ClearMaskOfUserPncByteMaskType;
typedef uint8 ComM_PncIDOfUserPncByteMaskType;
typedef uint8 ComM_PncIdxOfUserPncByteMaskType;
typedef uint8 ComM_SetMaskOfUserPncByteMaskType;
typedef uint8 ComM_UserReqPncFullComIdxOfUserPncByteMaskType;
typedef uint8 ComM_UserReqFullComType;
typedef uint8 ComM_UserReqPncFullComType;
typedef boolean ComM_UserWithSinglePncType;
typedef boolean ComM_WakeupInhibitionType;
typedef uint16_least ComM_PBPartitionConfigIterType;
typedef uint8 ComM_PCPartitionConfigIdxOfPartitionIdentifiersType;
typedef uint8 ComM_LTConfigIdxOfPBConfigType;
typedef uint8 ComM_PCConfigIdxOfPBConfigType;

typedef struct sComM_ChannelType
{
  GetCurrentBusSMModeApiType GetCurrentBusSMModeApiOfChannel;
  RequestBusSMModeApiType RequestBusSMModeApiOfChannel;
} ComM_ChannelType;

typedef struct sComM_ChannelPbType
{
  uint8 ComM_ChannelPbNeverUsed;
} ComM_ChannelPbType;

typedef struct sComM_EiraTxSignalIndirectionType
{
  uint8 ComM_EiraTxSignalIndirectionNeverUsed;
} ComM_EiraTxSignalIndirectionType;

typedef struct sComM_PartitionIdentifiersType
{
  ComM_PartitionSNVOfPartitionIdentifiersType PartitionSNVOfPartitionIdentifiers;
  ComM_PCPartitionConfigIdxOfPartitionIdentifiersType PCPartitionConfigIdxOfPartitionIdentifiers;
} ComM_PartitionIdentifiersType;

typedef struct sComM_PncType
{
  uint8 ComM_PncNeverUsed;
} ComM_PncType;

typedef struct sComM_PncPbType
{
  uint8 ComM_PncPbNeverUsed;
} ComM_PncPbType;

typedef struct sComM_PncSignalType
{
  uint8 ComM_PncSignalNeverUsed;
} ComM_PncSignalType;

typedef struct sComM_UserType
{
  ComM_PncUserOfUserType PncUserOfUser;
} ComM_UserType;

typedef struct sComM_UserByteMaskType
{
  uint8 ComM_UserByteMaskNeverUsed;
} ComM_UserByteMaskType;

typedef struct sComM_UserPncByteMaskType
{
  uint8 ComM_UserPncByteMaskNeverUsed;
} ComM_UserPncByteMaskType;

typedef struct ComM_ActiveComModeStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_StateType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_StateType ComMChannel_0;
[!ENDIF!][!//
} ComM_ActiveComModeStructSType;

typedef struct ComM_BusComModeReqStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_StateType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_StateType ComMChannel_0;
[!ENDIF!][!//
} ComM_BusComModeReqStructSType;

typedef struct ComM_BusComModeReqFrShutdownStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_StateType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_StateType ComMChannel_0;
[!ENDIF!][!//
} ComM_BusComModeReqFrShutdownStructSType;

typedef struct ComM_BusSleepModeIndicatedStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_BusSleepModeIndicatedType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_BusSleepModeIndicatedType ComMChannel_0;
[!ENDIF!][!//
} ComM_BusSleepModeIndicatedStructSType;

typedef struct ComM_BusSmStateStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_ModeType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_ModeType ComMChannel_0;
[!ENDIF!][!//
} ComM_BusSmStateStructSType;

typedef struct ComM_ComAllowedStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_ComAllowedType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_ComAllowedType ComMChannel_0;
[!ENDIF!][!//
} ComM_ComAllowedStructSType;

typedef struct ComM_DcmRequestActiveStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_DcmRequestActiveType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_DcmRequestActiveType ComMChannel_0;
[!ENDIF!][!//
} ComM_DcmRequestActiveStructSType;

typedef struct ComM_ForwardNmGatewayStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_ForwardNmGatewayType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_ForwardNmGatewayType ComMChannel_0;
[!ENDIF!][!//
} ComM_ForwardNmGatewayStructSType;

typedef struct ComM_FrShutdownStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_FrShutdownType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_FrShutdownType ComMChannel_0;
[!ENDIF!][!//
} ComM_FrShutdownStructSType;

typedef struct ComM_MinFullComModeTimerStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_MinFullComModeTimerType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_MinFullComModeTimerType ComMChannel_0;
[!ENDIF!][!//
} ComM_MinFullComModeTimerStructSType;

typedef struct ComM_NmLightTimerStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_NmLightTimerType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_NmLightTimerType ComMChannel_0;
[!ENDIF!][!//
} ComM_NmLightTimerStructSType;

typedef struct ComM_PncToChannelRoutingStateStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_PncToChannelRoutingStateType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_PncToChannelRoutingStateType ComMChannel_0;
[!ENDIF!][!//
} ComM_PncToChannelRoutingStateStructSType;

typedef struct ComM_ResetRequiredStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_ResetRequiredType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_ResetRequiredType ComMChannel_0;
[!ENDIF!][!//
} ComM_ResetRequiredStructSType;

typedef struct ComM_SimulatedSmModeStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_SimulatedSmModeType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_SimulatedSmModeType ComMChannel_0;
[!ENDIF!][!//
} ComM_SimulatedSmModeStructSType;

typedef struct ComM_StateChangeStructSTag
{
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  ComM_StateChangeType ComMChannel_[!"num:i(node:value(ComMChannelId))"!];
[!ENDLOOP!][!ELSE!][!//
  ComM_StateChangeType ComMChannel_0;
[!ENDIF!][!//
} ComM_StateChangeStructSType;

typedef union ComM_ActiveComModeUTag
{
  ComM_StateType raw[[!"$numChannels"!]];
  ComM_ActiveComModeStructSType str;
} ComM_ActiveComModeUType;

typedef union ComM_BusComModeReqUTag
{
  ComM_StateType raw[[!"$numChannels"!]];
  ComM_BusComModeReqStructSType str;
} ComM_BusComModeReqUType;

typedef union ComM_BusComModeReqFrShutdownUTag
{
  ComM_StateType raw[[!"$numChannels"!]];
  ComM_BusComModeReqFrShutdownStructSType str;
} ComM_BusComModeReqFrShutdownUType;

typedef union ComM_BusSleepModeIndicatedUTag
{
  ComM_BusSleepModeIndicatedType raw[[!"$numChannels"!]];
  ComM_BusSleepModeIndicatedStructSType str;
} ComM_BusSleepModeIndicatedUType;

typedef union ComM_BusSmStateUTag
{
  ComM_ModeType raw[[!"$numChannels"!]];
  ComM_BusSmStateStructSType str;
} ComM_BusSmStateUType;

typedef union ComM_ComAllowedUTag
{
  ComM_ComAllowedType raw[[!"$numChannels"!]];
  ComM_ComAllowedStructSType str;
} ComM_ComAllowedUType;

typedef union ComM_DcmRequestActiveUTag
{
  ComM_DcmRequestActiveType raw[[!"$numChannels"!]];
  ComM_DcmRequestActiveStructSType str;
} ComM_DcmRequestActiveUType;

typedef union ComM_ForwardNmGatewayUTag
{
  ComM_ForwardNmGatewayType raw[[!"$numChannels"!]];
  ComM_ForwardNmGatewayStructSType str;
} ComM_ForwardNmGatewayUType;

typedef union ComM_FrShutdownUTag
{
  ComM_FrShutdownType raw[[!"$numChannels"!]];
  ComM_FrShutdownStructSType str;
} ComM_FrShutdownUType;

typedef union ComM_MinFullComModeTimerUTag
{
  ComM_MinFullComModeTimerType raw[[!"$numChannels"!]];
  ComM_MinFullComModeTimerStructSType str;
} ComM_MinFullComModeTimerUType;

typedef union ComM_NmLightTimerUTag
{
  ComM_NmLightTimerType raw[[!"$numChannels"!]];
  ComM_NmLightTimerStructSType str;
} ComM_NmLightTimerUType;

typedef union ComM_PncToChannelRoutingStateUTag
{
  ComM_PncToChannelRoutingStateType raw[[!"$numChannels"!]];
  ComM_PncToChannelRoutingStateStructSType str;
} ComM_PncToChannelRoutingStateUType;

typedef union ComM_ResetRequiredUTag
{
  ComM_ResetRequiredType raw[[!"$numChannels"!]];
  ComM_ResetRequiredStructSType str;
} ComM_ResetRequiredUType;

typedef union ComM_SimulatedSmModeUTag
{
  ComM_SimulatedSmModeType raw[[!"$numChannels"!]];
  ComM_SimulatedSmModeStructSType str;
} ComM_SimulatedSmModeUType;

typedef union ComM_StateChangeUTag
{
  ComM_StateChangeType raw[[!"$numChannels"!]];
  ComM_StateChangeStructSType str;
} ComM_StateChangeUType;

typedef P2VAR(ComM_StateType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ActiveComModePtrType;
typedef P2VAR(ComM_PncModeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ActivePncComModePtrType;
typedef P2VAR(ComM_StateType, TYPEDEF, COMM_VAR_NO_INIT) ComM_BusComModeReqPtrType;
typedef P2VAR(ComM_StateType, TYPEDEF, COMM_VAR_NO_INIT) ComM_BusComModeReqFrShutdownPtrType;
typedef P2VAR(ComM_PncModeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_BusPncComModeReqPtrType;
typedef P2VAR(ComM_BusSleepModeIndicatedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_BusSleepModeIndicatedPtrType;
typedef P2VAR(ComM_ModeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_BusSmStatePtrType;
typedef P2CONST(ComM_BusTypeFrType, TYPEDEF, COMM_CONST) ComM_BusTypeFrPtrType;
typedef P2CONST(ComM_ChannelType, TYPEDEF, COMM_CONST) ComM_ChannelPtrType;
typedef P2CONST(ComM_ChannelPbType, TYPEDEF, COMM_CONST) ComM_ChannelPbPtrType;
typedef P2VAR(ComM_ComAllowedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ComAllowedPtrType;
typedef P2CONST(ComM_CoordPncWithGwPassiveAndManagedChannelsType, TYPEDEF, COMM_CONST) ComM_CoordPncWithGwPassiveAndManagedChannelsPtrType;
typedef P2CONST(ComM_DcmIndicationType, TYPEDEF, COMM_CONST) ComM_DcmIndicationPtrType;
typedef P2VAR(ComM_DcmRequestActiveType, TYPEDEF, COMM_VAR_NO_INIT) ComM_DcmRequestActivePtrType;
typedef P2VAR(volatile ComM_EcuMWakeUpIndicatedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_EcuMWakeUpIndicatedPtrType;
typedef P2CONST(ComM_EiraTxSignalIndirectionType, TYPEDEF, COMM_CONST) ComM_EiraTxSignalIndirectionPtrType;
typedef P2CONST(ComM_ExtendedRamCheckType, TYPEDEF, COMM_CONST) ComM_ExtendedRamCheckPtrType;
typedef P2VAR(ComM_ForwardNmGatewayType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ForwardNmGatewayPtrType;
typedef P2VAR(ComM_ForwardSynchronizedPncShutdownIndicatedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ForwardSynchronizedPncShutdownIndicatedPtrType;
typedef P2VAR(ComM_FrShutdownType, TYPEDEF, COMM_VAR_NO_INIT) ComM_FrShutdownPtrType;
typedef P2VAR(ComM_FullComRequestersType, TYPEDEF, COMM_VAR_NO_INIT) ComM_FullComRequestersPtrType;
typedef P2CONST(ComM_FullCommRequestNotifType, TYPEDEF, COMM_CONST) ComM_FullCommRequestNotifPtrType;
typedef P2CONST(ComM_FullNmTypeOfChannelType, TYPEDEF, COMM_CONST) ComM_FullNmTypeOfChannelPtrType;
typedef P2VAR(ComM_InhibitionType, TYPEDEF, COMM_NVM_DATA_NO_INIT) ComM_InhibitionPtrType;
typedef P2VAR(ComM_InitStatusType, TYPEDEF, COMM_VAR_NO_INIT) ComM_InitStatusPtrType;
typedef P2CONST(ComM_KeepAwakeChannelsType, TYPEDEF, COMM_CONST) ComM_KeepAwakeChannelsPtrType;
typedef P2VAR(ComM_ModeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_LastStateChangePtrType;
typedef P2CONST(ComM_LightNmTypeOfChannelType, TYPEDEF, COMM_CONST) ComM_LightNmTypeOfChannelPtrType;
typedef P2CONST(ComM_LinslaveNmTypeOfChannelType, TYPEDEF, COMM_CONST) ComM_LinslaveNmTypeOfChannelPtrType;
typedef P2VAR(ComM_MinFullComModeTimerType, TYPEDEF, COMM_VAR_NO_INIT) ComM_MinFullComModeTimerPtrType;
typedef P2CONST(ComM_ModeLimitationType, TYPEDEF, COMM_CONST) ComM_ModeLimitationPtrType;
typedef P2CONST(ComM_NmGwExtType, TYPEDEF, COMM_CONST) ComM_NmGwExtPtrType;
typedef P2VAR(ComM_NmLightTimerType, TYPEDEF, COMM_VAR_NO_INIT) ComM_NmLightTimerPtrType;
typedef P2VAR(volatile ComM_NmStartUpIndicatedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_NmStartUpIndicatedPtrType;
typedef P2CONST(ComM_NoneNmTypeOfChannelType, TYPEDEF, COMM_CONST) ComM_NoneNmTypeOfChannelPtrType;
typedef P2VAR(ComM_NotifyPncStateChangeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_NotifyPncStateChangePtrType;
typedef P2VAR(ComM_NvMStoreReqType, TYPEDEF, COMM_VAR_NO_INIT) ComM_NvMStoreReqPtrType;
typedef P2CONST(ComM_OnlyNoneNmTypeOfChannelType, TYPEDEF, COMM_CONST) ComM_OnlyNoneNmTypeOfChannelPtrType;
typedef P2CONST(ComM_PartitionIdentifiersType, TYPEDEF, COMM_CONST) ComM_PartitionIdentifiersPtrType;
typedef P2CONST(ComM_PncType, TYPEDEF, COMM_CONST) ComM_PncPtrType;
typedef P2CONST(ComM_Pnc0VectorAvoidanceType, TYPEDEF, COMM_CONST) ComM_Pnc0VectorAvoidancePtrType;
typedef P2CONST(ComM_PncChannelMappingType, TYPEDEF, COMM_CONST) ComM_PncChannelMappingPtrType;
typedef P2CONST(ComM_PncCheckEnabledAtRuntimeType, TYPEDEF, COMM_CONST) ComM_PncCheckEnabledAtRuntimePtrType;
typedef P2CONST(ComM_PncEiraRxType, TYPEDEF, COMM_CONST) ComM_PncEiraRxPtrType;
typedef P2CONST(ComM_PncExtendedFunctionalityType, TYPEDEF, COMM_CONST) ComM_PncExtendedFunctionalityPtrType;
typedef P2CONST(ComM_PncGwTypeActiveType, TYPEDEF, COMM_CONST) ComM_PncGwTypeActivePtrType;
typedef P2CONST(ComM_PncGwTypeNoneType, TYPEDEF, COMM_CONST) ComM_PncGwTypeNonePtrType;
typedef P2CONST(ComM_PncGwTypePassiveType, TYPEDEF, COMM_CONST) ComM_PncGwTypePassivePtrType;
typedef P2VAR(ComM_PncLimitationType, TYPEDEF, COMM_VAR_NO_INIT) ComM_PncLimitationPtrType;
typedef P2VAR(ComM_PncPSleepTimerType, TYPEDEF, COMM_VAR_NO_INIT) ComM_PncPSleepTimerPtrType;
typedef P2CONST(ComM_PncPbType, TYPEDEF, COMM_CONST) ComM_PncPbPtrType;
typedef P2CONST(ComM_PncPbIndType, TYPEDEF, COMM_CONST) ComM_PncPbIndPtrType;
typedef P2CONST(ComM_PncSignalType, TYPEDEF, COMM_CONST) ComM_PncSignalPtrType;
typedef P2CONST(ComM_PncSignalIndType, TYPEDEF, COMM_CONST) ComM_PncSignalIndPtrType;
typedef P2VAR(ComM_PncSignalValuesType, TYPEDEF, COMM_VAR_NO_INIT) ComM_PncSignalValuesPtrType;
typedef P2VAR(ComM_PncToChannelRoutingStateType, TYPEDEF, COMM_VAR_NO_INIT) ComM_PncToChannelRoutingStatePtrType;
typedef P2CONST(ComM_PncWithoutChannelsType, TYPEDEF, COMM_CONST) ComM_PncWithoutChannelsPtrType;
typedef P2VAR(ComM_PostInitializedType, TYPEDEF, COMM_VAR_NO_INIT) ComM_PostInitializedPtrType;
typedef P2VAR(ComM_ResetRequiredType, TYPEDEF, COMM_VAR_NO_INIT) ComM_ResetRequiredPtrType;
typedef P2VAR(ComM_SimulatedSmModeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_SimulatedSmModePtrType;
typedef P2VAR(ComM_StateChangeType, TYPEDEF, COMM_VAR_NO_INIT) ComM_StateChangePtrType;
typedef P2CONST(ComM_SynchronousWakeUpType, TYPEDEF, COMM_CONST) ComM_SynchronousWakeUpPtrType;
typedef P2CONST(ComM_UserType, TYPEDEF, COMM_CONST) ComM_UserPtrType;
typedef P2CONST(ComM_UserByteMaskType, TYPEDEF, COMM_CONST) ComM_UserByteMaskPtrType;
typedef P2CONST(ComM_StateNotiFuncPtrType, TYPEDEF, COMM_CONST) ComM_UserModeNotiFuncPtrType;
typedef P2CONST(ComM_UserModeNotificationOnlyForPncUsersType, TYPEDEF, COMM_CONST) ComM_UserModeNotificationOnlyForPncUsersPtrType;
typedef P2CONST(ComM_UserPncByteMaskType, TYPEDEF, COMM_CONST) ComM_UserPncByteMaskPtrType;
typedef P2VAR(ComM_UserReqFullComType, TYPEDEF, COMM_VAR_NO_INIT) ComM_UserReqFullComPtrType;
typedef P2VAR(ComM_UserReqPncFullComType, TYPEDEF, COMM_VAR_NO_INIT) ComM_UserReqPncFullComPtrType;
typedef P2CONST(ComM_UserWithSinglePncType, TYPEDEF, COMM_CONST) ComM_UserWithSinglePncPtrType;
typedef P2CONST(ComM_WakeupInhibitionType, TYPEDEF, COMM_CONST) ComM_WakeupInhibitionPtrType;

typedef struct sComM_PCPartitionConfigType
{
  uint8 ComM_PCPartitionConfigNeverUsed;
} ComM_PCPartitionConfigType;

typedef P2CONST(ComM_PCPartitionConfigType, TYPEDEF, COMM_CONST) ComM_PCPartitionConfigPtrType;

typedef struct sComM_PCConfigType
{
  uint8 ComM_PCConfigNeverUsed;
} ComM_PCConfigType;

typedef ComM_PCConfigType ComM_ConfigType;

typedef struct sComM_PBPartitionConfigType
{
  uint8 ComM_PBPartitionConfigNeverUsed;
} ComM_PBPartitionConfigType;

typedef P2CONST(ComM_PBPartitionConfigType, TYPEDEF, COMM_PBCFG) ComM_PBPartitionConfigPtrType;

typedef struct sComM_PBConfigType
{
  uint8 ComM_PBConfigNeverUsed;
} ComM_PBConfigType;


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

#endif /* COMM_CFG_H */
[!ENDSELECT!]
