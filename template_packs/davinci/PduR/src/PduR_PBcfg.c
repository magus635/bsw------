[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_PBcfg.c CSL Template */!]
#define PDUR_PBCFGSOURCE

#include "PduR_PBcfg.h"
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!IF "@name = 'Com'"!]
#include "Com_Cbk.h"
[!ELSEIF "@name = 'Dcm'"!]
#include "Dcm_Cbk.h"
[!ELSE!]
#include "[!"@name"!].h"
[!ENDIF!]
[!ENDLOOP!]
