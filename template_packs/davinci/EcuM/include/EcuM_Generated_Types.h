[!SELECT "as:modconf('EcuM')[1]"!][!//
[!IF "not(node:exists(EcuMConfiguration))"!][!ERROR "EcuMConfiguration container is missing in EcuM configuration"!][!ENDIF!][!//
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This file is part of the AUTOSAR BSW Configurator generated output.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EcuM_Generated_Types.h
 *            Module: EcuM
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#if !defined(ECUM_GENERATEDTYPES_H)
#define ECUM_GENERATEDTYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "Rte_EcuM_Type.h"
# include "Std_Types.h"

/**********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! This type is a bit mask of wakeup sources. */
 typedef uint32 EcuM_WakeupSourceType;

/* Wakeup Source Symbolic Name Values */
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource)"!][!//
[!LOOP "node:order(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*, 'EcuMWakeupSourceId')"!][!//
[!IF "node:exists(EcuMWakeupSourceId)"!][!//
#define EcuMConf_EcuMWakeupSource_[!"node:name(.)"!] ([!"num:i(node:value(EcuMWakeupSourceId))"!]u)
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//

/* Wakeup Source Bitmasks */
#define ECUM_WKSOURCE_NONE                    (EcuM_WakeupSourceType)(0x00000000u)
#define ECUM_WKSOURCE_ALL_SOURCES             (EcuM_WakeupSourceType)(~((EcuM_WakeupSourceType)0x00UL))
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource)"!][!//
[!LOOP "node:order(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*, 'EcuMWakeupSourceId')"!][!//
[!IF "node:exists(EcuMWakeupSourceId)"!][!//
[!VAR "wkName" = "node:name(.)"!][!//
[!VAR "wkId" = "num:i(node:value(EcuMWakeupSourceId))"!][!//
[!VAR "wkMacro" = "$wkName"!][!//
[!IF "not(starts-with($wkName, 'ECUM_WKSOURCE_'))"!][!//
[!VAR "wkMacro" = "concat('ECUM_WKSOURCE_', $wkName)"!][!//
[!ENDIF!][!//
#define [!"$wkMacro"!] (EcuM_WakeupSourceType)([!"num:i(bit:shl(1, $wkId))"!]u)
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//

/* ------------------------------------- Range of EcuM_StateType ------------------------------------------------- */
#define ECUM_SUBSTATE_MASK                                  (0x0Fu)
#define ECUM_STATE_STARTUP                                  (0x10u)
#define ECUM_STATE_STARTUP_ONE                              (0x11u)
#define ECUM_STATE_STARTUP_TWO                              (0x12u)
#define ECUM_STATE_WAKEUP                                   (0x20u)
#define ECUM_STATE_WAKEUP_ONE                               (0x21u)
#define ECUM_STATE_WAKEUP_VALIDATION                        (0x22u)
#define ECUM_STATE_WAKEUP_REACTION                          (0x23u)
#define ECUM_STATE_WAKEUP_TWO                               (0x24u)
#define ECUM_STATE_WAKEUP_WAKESLEEP                         (0x25u)
#define ECUM_STATE_WAKEUP_TTII                              (0x26u)
#define ECUM_STATE_RUN                                      (0x30u)
#define ECUM_STATE_APP_RUN                                  (0x32u)
#define ECUM_STATE_APP_POST_RUN                             (0x33u)
#define ECUM_STATE_SHUTDOWN                                 (0x40u)
#define ECUM_STATE_PREP_SHUTDOWN                            (0x44u)
#define ECUM_STATE_GO_SLEEP                                 (0x49u)
#define ECUM_STATE_GO_OFF_ONE                               (0x4Du)
#define ECUM_STATE_GO_OFF_TWO                               (0x4Eu)
#define ECUM_STATE_ERROR                                    (0xFFu)

typedef uint8 EcuM_WakeupStateType;

/* Wakeup States */
#define ECUM_WKSTATUS_NONE                                  (0u)
#define ECUM_WKSTATUS_PENDING                               (1u)
#define ECUM_WKSTATUS_VALIDATED                             (2u)
#define ECUM_WKSTATUS_EXPIRED                               (3u)
#define ECUM_WKSTATUS_CHECKWAKEUP                           (5u)
#define ECUM_WKSTATUS_ENABLED                               (6u)

/* Run Status */
#define ECUM_RUNSTATUS_UNKNOWN                              (0u)
#define ECUM_RUNSTATUS_REQUESTED                            (1u)
#define ECUM_RUNSTATUS_RELEASED                             (2u)

typedef uint8 EcuM_RunStatusType;
typedef EcuM_ModeType EcuM_ResetType;

#endif /* ECUM_GENERATEDTYPES_H */
[!ENDSELECT!]
