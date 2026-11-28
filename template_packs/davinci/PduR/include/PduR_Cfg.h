[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_Cfg.h CSL Template */!]
#if !defined (PDUR_CFG_H)
# define PDUR_CFG_H

#include "PduR_Types.h"

#ifndef PDUR_USE_DUMMY_STATEMENT
#define PDUR_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef PDUR_DUMMY_STATEMENT
#define PDUR_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef PDUR_DUMMY_STATEMENT_CONST
#define PDUR_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef PDUR_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define PDUR_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF
#endif
#ifndef PDUR_ATOMIC_VARIABLE_ACCESS
#define PDUR_ATOMIC_VARIABLE_ACCESS 32u
#endif
#ifndef PDUR_PROCESSOR_TONGXIN_THA6206
#define PDUR_PROCESSOR_TONGXIN_THA6206
#endif
#ifndef PDUR_COMP_LLVMHIGHTEC
#define PDUR_COMP_LLVMHIGHTEC
#endif
#ifndef PDUR_GEN_GENERATOR_MSR
#define PDUR_GEN_GENERATOR_MSR
#endif
#ifndef PDUR_CPUTYPE_BITORDER_LSB2MSB
#define PDUR_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_PRECOMPILE
#define PDUR_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_LINKTIME
#define PDUR_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define PDUR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef PDUR_CONFIGURATION_VARIANT
#define PDUR_CONFIGURATION_VARIANT PDUR_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef PDUR_POSTBUILD_VARIANT_SUPPORT
#define PDUR_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

[!VAR "devErr" = "as:modconf('PduR')[1]/PduRGeneral/PduRDevErrorDetect"!][!//
[!VAR "extErr" = "as:modconf('PduR')[1]/PduRGeneral/PduRExtendedErrorChecks"!][!//
[!VAR "verInfo" = "as:modconf('PduR')[1]/PduRGeneral/PduRVersionInfoApi"!][!//
[!VAR "multicore" = "as:modconf('PduR')[1]/PduRGeneral/PduRSupportMulticore"!][!//
[!VAR "bswmCbk" = "'false'"!][!//
[!IF "node:exists(as:modconf('PduR')[1]/PduRGeneral/PduRBswMCallbacks)"!][!//
[!VAR "bswmCbk" = "as:modconf('PduR')[1]/PduRGeneral/PduRBswMCallbacks"!][!//
[!ENDIF!][!//

#define PDUR_DEV_ERROR_DETECT [!IF "$devErr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_DEV_ERROR_REPORT [!IF "$devErr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXTENDED_ERROR_CHECKS [!IF "$extErr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_VERSION_INFO_API [!IF "$verInfo = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_ERROR_NOTIFICATION STD_OFF
#define PDUR_MULTICORE [!IF "$multicore = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWM_CALLBACKS [!IF "$bswmCbk = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PduR_PBConfigIdType uint32

[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!IF "@name = 'Com'"!][!//
#define PDUR_FCT_COMTX 0x89u
[!ELSEIF "@name = 'CanIf'"!][!//
#define PDUR_FCT_CANIFRXIND 0x01u
#define PDUR_FCT_CANIFTX 0x09u
#define PDUR_FCT_CANIFTXCFM 0x02u
[!ELSEIF "@name = 'CanTp'"!][!//
#define PDUR_FCT_CANTPRXIND 0x05u
#define PDUR_FCT_CANTPTX 0x09u
#define PDUR_FCT_CANTPTXCFM 0x08u
#define PDUR_FCT_CANTPSOR 0x06u
#define PDUR_FCT_CANTPCPYRX 0x04u
#define PDUR_FCT_CANTPCPYTX 0x07u
[!ELSEIF "@name = 'Dcm'"!][!//
#define PDUR_FCT_DCMTX 0x99u
#define PDUR_FCT_DCMCTX 0x9Au
[!ENDIF!][!//
[!ENDLOOP!][!//

/* Symbolic Name Handles */
[!VAR "hasDeepDest" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[node:exists(PduRDestPduDirection) and node:exists(PduRDestPduHandleId)])"!][!//
[!IF "$hasDeepDest > 0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[node:exists(PduRDestPduDirection) and node:exists(PduRDestPduHandleId)], '@name')"!][!//
#define PduRConf_PduRDestPdu_[!"@name"!] [!"num:i(PduRDestPduHandleId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[node:exists(PduRSrcPduDirection) and node:exists(PduRSourcePduHandleId)], '@name')"!][!//
#define PduRConf_PduRSrcPdu_[!"@name"!] [!"num:i(PduRSourcePduHandleId)"!]u
[!ENDLOOP!][!//
[!ELSE!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[node:exists(PduRDestPduDirection) and node:exists(PduRDestPduHandleId)], '@name')"!][!//
#define PduRConf_PduRDestPdu_[!"@name"!] [!"num:i(PduRDestPduHandleId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[node:exists(PduRSrcPduDirection) and node:exists(PduRSourcePduHandleId)], '@name')"!][!//
#define PduRConf_PduRSrcPdu_[!"@name"!] [!"num:i(PduRSourcePduHandleId)"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//

#endif /* PDUR_CFG_H */
