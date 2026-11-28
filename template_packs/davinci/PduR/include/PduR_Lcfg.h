[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_Lcfg.h CSL Template */!]
#if !defined (PDUR_LCFG_H)
# define PDUR_LCFG_H

# include "PduR_Types.h"
# include "PduR_Cfg.h"
# include "Os.h"
# include "PduR_PBcfg.h"
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!IF "@name = 'Com'"!][!//
#include "Com_Cbk.h"
[!ELSEIF "@name = 'Dcm'"!][!//
#include "Dcm_Cbk.h"
[!ELSE!][!//
#include "[!"@name"!].h"
[!ENDIF!][!//
[!ENDLOOP!][!//

[!VAR "numMods" = "0"!][!//
[!VAR "comModIdx" = "-1"!][!//
[!VAR "mSearch" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
  [!IF "@name = 'Com'"!][!VAR "comModIdx" = "$mSearch"!][!ENDIF!][!//
  [!VAR "mSearch" = "$mSearch + 1"!][!//
  [!VAR "numMods" = "$numMods + 1"!][!//
[!ENDLOOP!][!//
[!VAR "hasDeepPaths" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[node:exists(PduRRoutingPathCommunicationType) and (*/PduRSrcPduDirection = 'RECEIVE' or */PduRSrcPduDirection = 'TRANSMIT')])"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!VAR "numIfRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numTpRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numIfTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!VAR "numTpTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!ELSE!][!//
[!VAR "numIfRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numTpRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numIfTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!VAR "numTpTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!ENDIF!][!//
[!VAR "numPaths" = "num:i($numIfRx + $numTpRx + $numIfTx + $numTpTx)"!][!//
[!VAR "numTxAll" = "num:i($numIfTx + $numTpTx)"!][!//
[!VAR "spinLock" = "'4294967295'"!][!//
[!IF "node:exists(as:modconf('PduR')[1]/PduRGeneral/PduRSpinlockRetryCounter)"!][!//
[!VAR "spinLock" = "num:i(as:modconf('PduR')[1]/PduRGeneral/PduRSpinlockRetryCounter)"!][!//
[!ENDIF!][!//
[!VAR "cfgId" = "'0'"!][!//
[!IF "node:exists(as:modconf('PduR')[1]/PduRRoutingTables/PduRConfigurationId)"!][!//
[!VAR "cfgId" = "num:i(as:modconf('PduR')[1]/PduRRoutingTables/PduRConfigurationId)"!][!//
[!ENDIF!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!VAR "hasIgnoreLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[PduRPduLengthHandlingStrategy = 'IGNORE'])"!][!//
[!VAR "hasShortenLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[PduRPduLengthHandlingStrategy = 'SHORTEN'])"!][!//
[!VAR "hasDiscardLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*/*[PduRPduLengthHandlingStrategy = 'DISCARD'])"!][!//
[!ELSE!][!//
[!VAR "hasIgnoreLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRPduLengthHandlingStrategy = 'IGNORE'])"!][!//
[!VAR "hasShortenLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRPduLengthHandlingStrategy = 'SHORTEN'])"!][!//
[!VAR "hasDiscardLen" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRPduLengthHandlingStrategy = 'DISCARD'])"!][!//
[!ENDIF!][!//
[!VAR "hasUnusedLen" = "num:i($numTpRx + $numTpTx)"!][!//

/* CSL Precompile Data Switches */
#define PDUR_APPLICATIONID2DESTAPPLICATIONMANAGERROM                                                STD_OFF
#define PDUR_DESTAPPLICATIONMANAGERROMIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                  STD_OFF
#define PDUR_DESTAPPLICATIONMANAGERROMUSEDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                 STD_OFF
#define PDUR_INVALIDHNDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                                    STD_OFF
#define PDUR_PARTITIONCONFIGIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                            STD_OFF
#define PDUR_BMTXBUFFERARRAYRAM                                                                     STD_OFF
#define PDUR_BMTXBUFFERINDROM                                                                       STD_OFF
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINDROM                                                     STD_OFF
#define PDUR_BMTXBUFFERINSTANCERAM                                                                  STD_OFF
#define PDUR_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM                                       STD_OFF
#define PDUR_BMTXBUFFERINSTANCEROM                                                                  STD_OFF
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINSTANCEROM                                                STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAM                                                             STD_OFF
#define PDUR_BMTXBUFFERRAM                                                                          STD_OFF
#define PDUR_ALLOCATEDOFBMTXBUFFERRAM                                                               STD_OFF
#define PDUR_BMTXBUFFERARRAYRAMWRITEIDXOFBMTXBUFFERRAM                                              STD_OFF
#define PDUR_RXLENGTHOFBMTXBUFFERRAM                                                                STD_OFF
#define PDUR_BMTXBUFFERROM                                                                          STD_OFF
#define PDUR_BMTXBUFFERARRAYRAMENDIDXOFBMTXBUFFERROM                                                STD_OFF
#define PDUR_BMTXBUFFERARRAYRAMLENGTHOFBMTXBUFFERROM                                                STD_OFF
#define PDUR_BMTXBUFFERARRAYRAMSTARTIDXOFBMTXBUFFERROM                                              STD_OFF
#define PDUR_BMTXBUFFERINSTANCEROMENDIDXOFBMTXBUFFERROM                                             STD_OFF
#define PDUR_BMTXBUFFERINSTANCEROMSTARTIDXOFBMTXBUFFERROM                                           STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAMENDIDXOFBMTXBUFFERROM                                        STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAMLENGTHOFBMTXBUFFERROM                                        STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAMSTARTIDXOFBMTXBUFFERROM                                      STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAMUSEDOFBMTXBUFFERROM                                          STD_OFF
#define PDUR_CONFIGID                                                                               STD_ON
#define PDUR_DEFERREDEVENTCACHEARRAYRAM                                                             STD_OFF
#define PDUR_RMGDESTROMIDXOFDEFERREDEVENTCACHEARRAYRAM                                              STD_OFF
#define PDUR_DEFERREDEVENTCACHERAM                                                                  STD_OFF
#define PDUR_DEFERREDEVENTCACHEARRAYRAMREADIDXOFDEFERREDEVENTCACHERAM                               STD_OFF
#define PDUR_DEFERREDEVENTCACHEARRAYRAMWRITEIDXOFDEFERREDEVENTCACHERAM                              STD_OFF
#define PDUR_DEFERREDEVENTCACHEROM                                                                  STD_OFF
#define PDUR_DEFERREDEVENTCACHEARRAYRAMENDIDXOFDEFERREDEVENTCACHEROM                                STD_OFF
#define PDUR_DEFERREDEVENTCACHEARRAYRAMLENGTHOFDEFERREDEVENTCACHEROM                                STD_OFF
#define PDUR_DEFERREDEVENTCACHEARRAYRAMSTARTIDXOFDEFERREDEVENTCACHEROM                              STD_OFF
#define PDUR_DESTAPPLICATIONMANAGERROM                                                              STD_ON
#define PDUR_INITIALIZEDIDXOFDESTAPPLICATIONMANAGERROM                                              STD_ON
#define PDUR_INITIALIZEDPARTITIONIDXOFDESTAPPLICATIONMANAGERROM                                     STD_ON
#define PDUR_RMGDESTROMENDIDXOFDESTAPPLICATIONMANAGERROM                                            STD_ON
#define PDUR_RMGDESTROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                          STD_ON
#define PDUR_RMGDESTROMUSEDOFDESTAPPLICATIONMANAGERROM                                              STD_ON
#define PDUR_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                                     STD_ON
#define PDUR_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                   STD_ON
#define PDUR_EXCLUSIVEAREAROM                                                                       STD_ON
#define PDUR_LOCKOFEXCLUSIVEAREAROM                                                                 STD_ON
#define PDUR_UNLOCKOFEXCLUSIVEAREAROM                                                               STD_ON
#define PDUR_FINALMAGICNUMBER                                                                       STD_OFF
#define PDUR_FMFIFOELEMENTRAM                                                                       STD_OFF
#define PDUR_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM                                                     STD_OFF
#define PDUR_RMDESTROMIDXOFFMFIFOELEMENTRAM                                                         STD_OFF
#define PDUR_FMFIFORAM                                                                              STD_OFF
#define PDUR_FILLLEVELOFFMFIFORAM                                                                   STD_OFF
#define PDUR_FMFIFOELEMENTRAMREADIDXOFFMFIFORAM                                                     STD_OFF
#define PDUR_FMFIFOELEMENTRAMWRITEIDXOFFMFIFORAM                                                    STD_OFF
#define PDUR_FMFIFOROM                                                                              STD_OFF
#define PDUR_BMTXBUFFERINDROMENDIDXOFFMFIFOROM                                                      STD_OFF
#define PDUR_BMTXBUFFERINDROMLENGTHOFFMFIFOROM                                                      STD_OFF
#define PDUR_BMTXBUFFERINDROMSTARTIDXOFFMFIFOROM                                                    STD_OFF
#define PDUR_FMFIFOELEMENTRAMENDIDXOFFMFIFOROM                                                      STD_OFF
#define PDUR_FMFIFOELEMENTRAMLENGTHOFFMFIFOROM                                                      STD_OFF
#define PDUR_FMFIFOELEMENTRAMSTARTIDXOFFMFIFOROM                                                    STD_OFF
#define PDUR_LOCKROMIDXOFFMFIFOROM                                                                  STD_OFF
#define PDUR_LOCKROMUSEDOFFMFIFOROM                                                                 STD_OFF
#define PDUR_GENERALPROPERTIESROM                                                                   STD_ON
#define PDUR_SPINLOCKRETRYCOUNTEROFGENERALPROPERTIESROM                                             STD_ON
#define PDUR_INITDATAHASHCODE                                                                       STD_OFF
#define PDUR_INITIALIZEDRAM                                                                         STD_ON
#define PDUR_INTERFACEFIFOQUEUEARRAYRAM                                                             STD_OFF
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAM                                                           STD_OFF
#define PDUR_ACTUALLENGTHOFINTERFACEFIFOQUEUEELEMENTRAM                                             STD_OFF
#define PDUR_INTERFACEFIFOQUEUEMETADATAARRAYRAM                                                     STD_OFF
#define PDUR_INTERFACEFIFOQUEUERAM                                                                  STD_OFF
#define PDUR_FIFOFULLOFINTERFACEFIFOQUEUERAM                                                        STD_OFF
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMREADIDXOFINTERFACEFIFOQUEUERAM                             STD_OFF
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMWRITEIDXOFINTERFACEFIFOQUEUERAM                            STD_OFF
#define PDUR_INTERFACEFIFOQUEUEROM                                                                  STD_OFF
#define PDUR_INTERFACEFIFOQUEUEARRAYRAMENDIDXOFINTERFACEFIFOQUEUEROM                                STD_OFF
#define PDUR_INTERFACEFIFOQUEUEARRAYRAMSTARTIDXOFINTERFACEFIFOQUEUEROM                              STD_OFF
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMENDIDXOFINTERFACEFIFOQUEUEROM                              STD_OFF
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMSTARTIDXOFINTERFACEFIFOQUEUEROM                            STD_OFF
#define PDUR_INTERFACEFIFOQUEUEMETADATAARRAYRAMENDIDXOFINTERFACEFIFOQUEUEROM                        STD_OFF
#define PDUR_INTERFACEFIFOQUEUEMETADATAARRAYRAMSTARTIDXOFINTERFACEFIFOQUEUEROM                      STD_OFF
#define PDUR_INTERFACEFIFOQUEUEMETADATAARRAYRAMUSEDOFINTERFACEFIFOQUEUEROM                          STD_OFF
#define PDUR_MAXMETADATALENGTHOFINTERFACEFIFOQUEUEROM                                               STD_OFF
#define PDUR_MAXPDULENGTHOFINTERFACEFIFOQUEUEROM                                                    STD_OFF
#define PDUR_RMDESTROMIDXOFINTERFACEFIFOQUEUEROM                                                    STD_OFF
#define PDUR_LOCKROM                                                                                STD_ON
#define PDUR_EXCLUSIVEAREAROMIDXOFLOCKROM                                                           STD_ON
#define PDUR_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                          STD_ON
#define PDUR_SPINLOCKRAMIDXOFLOCKROM                                                                STD_OFF
#define PDUR_SPINLOCKRAMPARTITIONIDXOFLOCKROM                                                       STD_OFF
#define PDUR_SPINLOCKRAMUSEDOFLOCKROM                                                               STD_OFF
#define PDUR_MCQBUFFERARRAYRAM                                                                      STD_OFF
#define PDUR_MCQBUFFERRAM                                                                           STD_OFF
#define PDUR_MCQBUFFERARRAYRAMPENDINGREADIDXOFMCQBUFFERRAM                                          STD_OFF
#define PDUR_MCQBUFFERARRAYRAMPENDINGWRITEIDXOFMCQBUFFERRAM                                         STD_OFF
#define PDUR_MCQBUFFERARRAYRAMREADIDXOFMCQBUFFERRAM                                                 STD_OFF
#define PDUR_MCQBUFFERARRAYRAMWRITEIDXOFMCQBUFFERRAM                                                STD_OFF
#define PDUR_MCQBUFFERROM                                                                           STD_OFF
#define PDUR_MCQBUFFERARRAYRAMENDIDXOFMCQBUFFERROM                                                  STD_OFF
#define PDUR_MCQBUFFERARRAYRAMLENGTHOFMCQBUFFERROM                                                  STD_OFF
#define PDUR_MCQBUFFERARRAYRAMSTARTIDXOFMCQBUFFERROM                                                STD_OFF
#define PDUR_MMROM                                                                                  STD_ON
#define PDUR_CANCELRECEIVESUPPORTEDOFMMROM                                                          STD_ON
#define PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM                                                        STD_ON
#define PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM                                                       STD_ON
#define PDUR_LOIFCANCELTRANSMITFCTPTROFMMROM                                                        STD_ON
#define PDUR_LOIFOFMMROM                                                                            STD_ON
#define PDUR_LOIFTRANSMITFCTPTROFMMROM                                                              STD_ON
#define PDUR_LOTPCANCELRECEIVEFCTPTROFMMROM                                                         STD_ON
#define PDUR_LOTPCANCELTRANSMITFCTPTROFMMROM                                                        STD_ON
#define PDUR_LOTPCHANGEPARAMETERFCTPTROFMMROM                                                       STD_ON
#define PDUR_LOTPOFMMROM                                                                            STD_ON
#define PDUR_LOTPTRANSMITFCTPTROFMMROM                                                              STD_ON
#define PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM                                                       STD_ON
#define PDUR_UPIFOFMMROM                                                                            STD_ON
#define PDUR_UPIFRXINDICATIONFCTPTROFMMROM                                                          STD_ON
#define PDUR_UPIFTRIGGERTRANSMITFCTPTROFMMROM                                                       STD_ON
#define PDUR_UPIFTXCONFIRMATIONFCTPTROFMMROM                                                        STD_ON
#define PDUR_UPTPCOPYRXDATAFCTPTROFMMROM                                                            STD_ON
#define PDUR_UPTPCOPYTXDATAFCTPTROFMMROM                                                            STD_ON
#define PDUR_UPTPOFMMROM                                                                            STD_ON
#define PDUR_UPTPSTARTOFRECEPTIONFCTPTROFMMROM                                                      STD_ON
#define PDUR_UPTPTPRXINDICATIONFCTPTROFMMROM                                                        STD_ON
#define PDUR_UPTPTPTXCONFIRMATIONFCTPTROFMMROM                                                      STD_ON
#define PDUR_PARTITIONIDENTIFIERS                                                                   STD_ON
#define PDUR_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                             STD_ON
#define PDUR_PARTITIONSNVOFPARTITIONIDENTIFIERS                                                     STD_ON
#define PDUR_RMBUFFEREDIFPROPERTIESRAM                                                              STD_OFF
#define PDUR_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM                                                   STD_OFF
#define PDUR_RMBUFFEREDIFPROPERTIESROM                                                              STD_OFF
#define PDUR_FMFIFOROMIDXOFRMBUFFEREDIFPROPERTIESROM                                                STD_OFF
#define PDUR_FMFIFOROMUSEDOFRMBUFFEREDIFPROPERTIESROM                                               STD_OFF
#define PDUR_INTERFACEFIFOQUEUEROMIDXOFRMBUFFEREDIFPROPERTIESROM                                    STD_OFF
#define PDUR_INTERFACEFIFOQUEUEROMUSEDOFRMBUFFEREDIFPROPERTIESROM                                   STD_OFF
#define PDUR_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                                   STD_OFF
#define PDUR_SINGLEBUFFERROMIDXOFRMBUFFEREDIFPROPERTIESROM                                          STD_OFF
#define PDUR_SINGLEBUFFERROMUSEDOFRMBUFFEREDIFPROPERTIESROM                                         STD_OFF
#define PDUR_RMBUFFEREDTPPROPERTIESRAM                                                              STD_OFF
#define PDUR_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM                                         STD_OFF
#define PDUR_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM                                                 STD_OFF
#define PDUR_RMBUFFEREDTPPROPERTIESROM                                                              STD_OFF
#define PDUR_FMFIFOROMIDXOFRMBUFFEREDTPPROPERTIESROM                                                STD_OFF
#define PDUR_QUEUEDDESTCNTOFRMBUFFEREDTPPROPERTIESROM                                               STD_OFF
#define PDUR_TPTHRESHOLDOFRMBUFFEREDTPPROPERTIESROM                                                 STD_OFF
#define PDUR_RMDESTROM                                                                              STD_ON
#define PDUR_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM                                                 STD_ON
#define PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                                   STD_ON
#define PDUR_QUEUEDOFRMDESTROM                                                                      STD_ON
#define PDUR_RMDESTRPGROMIDXOFRMDESTROM                                                             STD_OFF
#define PDUR_RMDESTRPGROMPARTITIONIDXOFRMDESTROM                                                    STD_OFF
#define PDUR_RMDESTRPGROMUSEDOFRMDESTROM                                                            STD_OFF
#define PDUR_RMGDESTROMIDXOFRMDESTROM                                                               STD_ON
#define PDUR_RMSRCROMIDXOFRMDESTROM                                                                 STD_ON
#define PDUR_ROUTINGTYPEOFRMDESTROM                                                                 STD_ON
#define PDUR_RMDESTRPGRAM                                                                           STD_OFF
#define PDUR_ENABLEDCNTOFRMDESTRPGRAM                                                               STD_OFF
#define PDUR_RMDESTRPGROM                                                                           STD_OFF
#define PDUR_INITIALENABLEDCNTOFRMDESTRPGROM                                                        STD_OFF
#define PDUR_RMDESTROMIDXOFRMDESTRPGROM                                                             STD_OFF
#define PDUR_RMDESTROMUSEDOFRMDESTRPGROM                                                            STD_OFF
#define PDUR_RMDESTRPGROMIND                                                                        STD_OFF
#define PDUR_RMGDESTNTO1INFORAM                                                                     STD_OFF
#define PDUR_RMDESTROMIDXOFRMGDESTNTO1INFORAM                                                       STD_OFF
#define PDUR_TRANSMISSIONACTIVEOFRMGDESTNTO1INFORAM                                                 STD_OFF
#define PDUR_RMGDESTNTO1INFOROM                                                                     STD_OFF
#define PDUR_EXPECTTXCONFIRMATIONOFRMGDESTNTO1INFOROM                                               STD_OFF
#define PDUR_RMGDESTQUEUEDTPRAM                                                                     STD_OFF
#define PDUR_BMTXBUFFERINSTANCEROMIDXOFRMGDESTQUEUEDTPRAM                                           STD_OFF
#define PDUR_INTRANSMISSIONCONTEXTOFRMGDESTQUEUEDTPRAM                                              STD_OFF
#define PDUR_TPTXINSTSMSTATEOFRMGDESTQUEUEDTPRAM                                                    STD_OFF
#define PDUR_RMGDESTQUEUEDTPROM                                                                     STD_OFF
#define PDUR_FMFIFOROMIDXOFRMGDESTQUEUEDTPROM                                                       STD_OFF
#define PDUR_RMGDESTROM                                                                             STD_ON
#define PDUR_DESTAPPLICATIONMANAGERROMIDXOFRMGDESTROM                                               STD_ON
#define PDUR_DESTHNDOFRMGDESTROM                                                                    STD_ON
#define PDUR_DIRECTIONOFRMGDESTROM                                                                  STD_ON
#define PDUR_LOCKROMIDXOFRMGDESTROM                                                                 STD_ON
#define PDUR_METADATALENGTHOFRMGDESTROM                                                             STD_ON
#define PDUR_MMROMIDXOFRMGDESTROM                                                                   STD_ON
#define PDUR_PDULENGTHOFRMGDESTROM                                                                  STD_ON
#define PDUR_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                      STD_ON
#define PDUR_RMBUFFEREDIFPROPERTIESROMIDXOFRMGDESTROM                                               STD_OFF
#define PDUR_RMBUFFEREDIFPROPERTIESROMPARTITIONIDXOFRMGDESTROM                                      STD_OFF
#define PDUR_RMBUFFEREDIFPROPERTIESROMUSEDOFRMGDESTROM                                              STD_OFF
#define PDUR_RMDESTROMIDXOFRMGDESTROM                                                               STD_ON
#define PDUR_RMGDESTNTO1INFOROMIDXOFRMGDESTROM                                                      STD_OFF
#define PDUR_RMGDESTNTO1INFOROMPARTITIONIDXOFRMGDESTROM                                             STD_OFF
#define PDUR_RMGDESTNTO1INFOROMUSEDOFRMGDESTROM                                                     STD_OFF
#define PDUR_RMGDESTQUEUEDTPROMIDXOFRMGDESTROM                                                      STD_OFF
#define PDUR_RMGDESTQUEUEDTPROMPARTITIONIDXOFRMGDESTROM                                             STD_OFF
#define PDUR_RMGDESTQUEUEDTPROMUSEDOFRMGDESTROM                                                     STD_OFF
#define PDUR_TXIF2UPIDXOFRMGDESTROM                                                                 STD_ON
#define PDUR_RMSRCROM                                                                               STD_ON
#define PDUR_DESTAPPLICATIONMANAGERROMIDXOFRMSRCROM                                                 STD_ON
#define PDUR_DIRECTIONOFRMSRCROM                                                                    STD_ON
#define PDUR_IFOFRMSRCROM                                                                           STD_ON
#define PDUR_LOCKROMIDXOFRMSRCROM                                                                   STD_ON
#define PDUR_MMROMIDXOFRMSRCROM                                                                     STD_ON
#define PDUR_RMBUFFEREDTPPROPERTIESROMIDXOFRMSRCROM                                                 STD_OFF
#define PDUR_RMBUFFEREDTPPROPERTIESROMPARTITIONIDXOFRMSRCROM                                        STD_OFF
#define PDUR_RMBUFFEREDTPPROPERTIESROMUSEDOFRMSRCROM                                                STD_OFF
#define PDUR_RMDESTROMENDIDXOFRMSRCROM                                                              STD_ON
#define PDUR_RMDESTROMLENGTHOFRMSRCROM                                                              STD_ON
#define PDUR_RMDESTROMSTARTIDXOFRMSRCROM                                                            STD_ON
#define PDUR_SRCHNDOFRMSRCROM                                                                       STD_ON
#define PDUR_TPOFRMSRCROM                                                                           STD_ON
#define PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                                     STD_ON
#define PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM                                                      STD_ON
#define PDUR_RPGEXTIDROM                                                                            STD_OFF
#define PDUR_INVALIDHNDOFRPGEXTIDROM                                                                STD_OFF
#define PDUR_RPGROMIDXOFRPGEXTIDROM                                                                 STD_OFF
#define PDUR_RPGROMPARTITIONIDXOFRPGEXTIDROM                                                        STD_OFF
#define PDUR_RPGROMUSEDOFRPGEXTIDROM                                                                STD_OFF
#define PDUR_RPGRAM                                                                                 STD_OFF
#define PDUR_ENABLEDOFRPGRAM                                                                        STD_OFF
#define PDUR_RPGROM                                                                                 STD_OFF
#define PDUR_ENABLEDATINITOFRPGROM                                                                  STD_OFF
#define PDUR_RMDESTRPGROMINDENDIDXOFRPGROM                                                          STD_OFF
#define PDUR_RMDESTRPGROMINDSTARTIDXOFRPGROM                                                        STD_OFF
#define PDUR_RMDESTRPGROMINDUSEDOFRPGROM                                                            STD_OFF
#define PDUR_RXIF2DEST                                                                              [!IF "$numIfRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST                                                STD_ON
#define PDUR_INVALIDHNDOFRXIF2DEST                                                                  STD_OFF
#define PDUR_RMSRCROMIDXOFRXIF2DEST                                                                 STD_ON
#define PDUR_RXTP2DEST                                                                              [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST                                              STD_ON
#define PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST                                          STD_ON
#define PDUR_INVALIDHNDOFRXTP2DEST                                                                  STD_OFF
#define PDUR_RMSRCROMIDXOFRXTP2DEST                                                                 STD_ON
#define PDUR_RXTP2SRC                                                                               [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_INVALIDHNDOFRXTP2SRC                                                                   STD_OFF
#define PDUR_RMDESTROMIDXOFRXTP2SRC                                                                 STD_ON
#define PDUR_SINGLEBUFFERARRAYRAM                                                                   STD_OFF
#define PDUR_SINGLEBUFFERINITVALUESROM                                                              STD_OFF
#define PDUR_SINGLEBUFFERMETADATAARRAYRAM                                                           STD_OFF
#define PDUR_SINGLEBUFFERRAM                                                                        STD_OFF
#define PDUR_ACTUALLENGTHOFSINGLEBUFFERRAM                                                          STD_OFF
#define PDUR_SINGLEBUFFERROM                                                                        STD_OFF
#define PDUR_RMDESTROMIDXOFSINGLEBUFFERROM                                                          STD_OFF
#define PDUR_SINGLEBUFFERARRAYRAMENDIDXOFSINGLEBUFFERROM                                            STD_OFF
#define PDUR_SINGLEBUFFERARRAYRAMLENGTHOFSINGLEBUFFERROM                                            STD_OFF
#define PDUR_SINGLEBUFFERARRAYRAMSTARTIDXOFSINGLEBUFFERROM                                          STD_OFF
#define PDUR_SINGLEBUFFERINITVALUESROMENDIDXOFSINGLEBUFFERROM                                       STD_OFF
#define PDUR_SINGLEBUFFERINITVALUESROMLENGTHOFSINGLEBUFFERROM                                       STD_OFF
#define PDUR_SINGLEBUFFERINITVALUESROMSTARTIDXOFSINGLEBUFFERROM                                     STD_OFF
#define PDUR_SINGLEBUFFERMETADATAARRAYRAMENDIDXOFSINGLEBUFFERROM                                    STD_OFF
#define PDUR_SINGLEBUFFERMETADATAARRAYRAMLENGTHOFSINGLEBUFFERROM                                    STD_OFF
#define PDUR_SINGLEBUFFERMETADATAARRAYRAMSTARTIDXOFSINGLEBUFFERROM                                  STD_OFF
#define PDUR_SINGLEBUFFERMETADATAARRAYRAMUSEDOFSINGLEBUFFERROM                                      STD_OFF
#define PDUR_SIZEOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                                          STD_ON
#define PDUR_SIZEOFBMTXBUFFERARRAYRAM                                                               STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINDROM                                                                 STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINSTANCERAM                                                            STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINSTANCEROM                                                            STD_OFF
#define PDUR_SIZEOFBMTXBUFFERMETADATAARRAYRAM                                                       STD_ON
#define PDUR_SIZEOFBMTXBUFFERRAM                                                                    STD_OFF
#define PDUR_SIZEOFBMTXBUFFERROM                                                                    STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHEARRAYRAM                                                       STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHERAM                                                            STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHEROM                                                            STD_OFF
#define PDUR_SIZEOFDESTAPPLICATIONMANAGERROM                                                        STD_ON
#define PDUR_SIZEOFEXCLUSIVEAREAROM                                                                 STD_ON
#define PDUR_SIZEOFFMFIFOELEMENTRAM                                                                 STD_OFF
#define PDUR_SIZEOFFMFIFORAM                                                                        STD_OFF
#define PDUR_SIZEOFFMFIFOROM                                                                        STD_OFF
#define PDUR_SIZEOFGENERALPROPERTIESROM                                                             STD_ON
#define PDUR_SIZEOFINITIALIZEDRAM                                                                   STD_ON
#define PDUR_SIZEOFINTERFACEFIFOQUEUEARRAYRAM                                                       STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEELEMENTRAM                                                     STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEMETADATAARRAYRAM                                               STD_ON
#define PDUR_SIZEOFINTERFACEFIFOQUEUERAM                                                            STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEROM                                                            STD_OFF
#define PDUR_SIZEOFLOCKROM                                                                          STD_ON
#define PDUR_SIZEOFMCQBUFFERARRAYRAM                                                                STD_OFF
#define PDUR_SIZEOFMCQBUFFERRAM                                                                     STD_OFF
#define PDUR_SIZEOFMCQBUFFERROM                                                                     STD_OFF
#define PDUR_SIZEOFMMROM                                                                            STD_ON
#define PDUR_SIZEOFPARTITIONIDENTIFIERS                                                             STD_ON
#define PDUR_SIZEOFRMBUFFEREDIFPROPERTIESRAM                                                        STD_OFF
#define PDUR_SIZEOFRMBUFFEREDIFPROPERTIESROM                                                        STD_OFF
#define PDUR_SIZEOFRMBUFFEREDTPPROPERTIESRAM                                                        STD_OFF
#define PDUR_SIZEOFRMBUFFEREDTPPROPERTIESROM                                                        STD_OFF
#define PDUR_SIZEOFRMDESTROM                                                                        STD_ON
#define PDUR_SIZEOFRMDESTRPGRAM                                                                     STD_ON
#define PDUR_SIZEOFRMDESTRPGROM                                                                     STD_ON
#define PDUR_SIZEOFRMDESTRPGROMIND                                                                  STD_ON
#define PDUR_SIZEOFRMGDESTNTO1INFORAM                                                               STD_ON
#define PDUR_SIZEOFRMGDESTNTO1INFOROM                                                               STD_ON
#define PDUR_SIZEOFRMGDESTQUEUEDTPRAM                                                               STD_OFF
#define PDUR_SIZEOFRMGDESTQUEUEDTPROM                                                               STD_OFF
#define PDUR_SIZEOFRMGDESTROM                                                                       STD_ON
#define PDUR_SIZEOFRMSRCROM                                                                         STD_ON
#define PDUR_SIZEOFRPGEXTIDROM                                                                      STD_ON
#define PDUR_SIZEOFRPGRAM                                                                           STD_ON
#define PDUR_SIZEOFRPGROM                                                                           STD_ON
#define PDUR_SIZEOFRXIF2DEST                                                                        [!IF "$numIfRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFRXTP2DEST                                                                        [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFRXTP2SRC                                                                         [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFSINGLEBUFFERARRAYRAM                                                             STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERINITVALUESROM                                                        STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERMETADATAARRAYRAM                                                     STD_ON
#define PDUR_SIZEOFSINGLEBUFFERRAM                                                                  STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERROM                                                                  STD_OFF
#define PDUR_SIZEOFSPINLOCKCOUNTERRAM                                                               STD_OFF
#define PDUR_SIZEOFSPINLOCKRAM                                                                      STD_OFF
#define PDUR_SIZEOFSPINLOCKROM                                                                      STD_OFF
#define PDUR_SIZEOFSRCAPPLICATIONROM                                                                STD_ON
#define PDUR_SIZEOFTX2LO                                                                            [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFTXIF2UP                                                                          [!IF "$numIfTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFTXTP2SRC                                                                         [!IF "$numTpTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SPINLOCKCOUNTERRAM                                                                     STD_OFF
#define PDUR_SPINLOCKRAM                                                                            STD_OFF
#define PDUR_LOCKVARIABLEOFSPINLOCKRAM                                                              STD_OFF
#define PDUR_SPINLOCKROM                                                                            STD_OFF
#define PDUR_SPINLOCKCOUNTERRAMENDIDXOFSPINLOCKROM                                                  STD_OFF
#define PDUR_SPINLOCKCOUNTERRAMLENGTHOFSPINLOCKROM                                                  STD_OFF
#define PDUR_SPINLOCKCOUNTERRAMSTARTIDXOFSPINLOCKROM                                                STD_OFF
#define PDUR_SRCAPPLICATIONROM                                                                      STD_ON
#define PDUR_DEFERREDEVENTCACHEROMIDXOFSRCAPPLICATIONROM                                            STD_OFF
#define PDUR_DEFERREDEVENTCACHEROMPARTITIONIDXOFSRCAPPLICATIONROM                                   STD_OFF
#define PDUR_DEFERREDEVENTCACHEROMUSEDOFSRCAPPLICATIONROM                                           STD_OFF
#define PDUR_DESTAPPLICATIONMANAGERROMDESTINATIONIDXOFSRCAPPLICATIONROM                             STD_ON
#define PDUR_DESTAPPLICATIONMANAGERROMSOURCEIDXOFSRCAPPLICATIONROM                                  STD_ON
#define PDUR_MCQBUFFERROMIDXOFSRCAPPLICATIONROM                                                     STD_OFF
#define PDUR_MCQBUFFERROMPARTITIONIDXOFSRCAPPLICATIONROM                                            STD_OFF
#define PDUR_MCQBUFFERROMUSEDOFSRCAPPLICATIONROM                                                    STD_OFF
#define PDUR_TX2LO                                                                                  [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO                                                        STD_ON
#define PDUR_CANCELTRANSMITUSEDOFTX2LO                                                              STD_ON
#define PDUR_INVALIDHNDOFTX2LO                                                                      STD_OFF
#define PDUR_RMSRCROMIDXOFTX2LO                                                                     STD_ON
#define PDUR_TXIF2UP                                                                                [!IF "$numIfTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP                                                STD_ON
#define PDUR_INVALIDHNDOFTXIF2UP                                                                    STD_OFF
#define PDUR_RMGDESTROMIDXOFTXIF2UP                                                                 STD_ON
#define PDUR_TXCONFIRMATIONUSEDOFTXIF2UP                                                            STD_ON
#define PDUR_TXTP2SRC                                                                               [!IF "$numTpTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC                                             STD_ON
#define PDUR_INVALIDHNDOFTXTP2SRC                                                                   STD_OFF
#define PDUR_RMGDESTROMIDXOFTXTP2SRC                                                                STD_ON
#define PDUR_PCCONFIG                                                                               STD_ON
#define PDUR_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF
#define PDUR_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF
#define PDUR_PCPARTITIONCONFIGOFPCCONFIG                                                            STD_ON
#define PDUR_PARTITIONIDENTIFIERSOFPCCONFIG                                                         STD_ON
#define PDUR_SIZEOFPARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define PDUR_PCPARTITIONCONFIG                                                                      STD_ON
#define PDUR_APPLICATIONID2DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                             STD_OFF
#define PDUR_BMTXBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                          STD_OFF
#define PDUR_CONFIGIDOFPCPARTITIONCONFIG                                                            STD_ON
#define PDUR_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                           STD_ON
#define PDUR_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                                STD_ON
#define PDUR_INITIALIZEDRAMOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_INTERFACEFIFOQUEUEMETADATAARRAYRAMOFPCPARTITIONCONFIG                                  STD_OFF
#define PDUR_LOCKROMOFPCPARTITIONCONFIG                                                             STD_ON
#define PDUR_MMROMOFPCPARTITIONCONFIG                                                               STD_ON
#define PDUR_RMDESTROMOFPCPARTITIONCONFIG                                                           STD_ON
#define PDUR_RMDESTRPGRAMOFPCPARTITIONCONFIG                                                        STD_OFF
#define PDUR_RMDESTRPGROMINDOFPCPARTITIONCONFIG                                                     STD_OFF
#define PDUR_RMDESTRPGROMOFPCPARTITIONCONFIG                                                        STD_OFF
#define PDUR_RMGDESTNTO1INFORAMOFPCPARTITIONCONFIG                                                  STD_OFF
#define PDUR_RMGDESTNTO1INFOROMOFPCPARTITIONCONFIG                                                  STD_OFF
#define PDUR_RMGDESTROMOFPCPARTITIONCONFIG                                                          STD_ON
#define PDUR_RMSRCROMOFPCPARTITIONCONFIG                                                            STD_ON
#define PDUR_RPGEXTIDROMOFPCPARTITIONCONFIG                                                         STD_OFF
#define PDUR_RPGRAMOFPCPARTITIONCONFIG                                                              STD_OFF
#define PDUR_RPGROMOFPCPARTITIONCONFIG                                                              STD_OFF
#define PDUR_RXIF2DESTOFPCPARTITIONCONFIG                                                           [!IF "$numIfRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_RXTP2DESTOFPCPARTITIONCONFIG                                                           [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_RXTP2SRCOFPCPARTITIONCONFIG                                                            [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SINGLEBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                        STD_OFF
#define PDUR_SIZEOFAPPLICATIONID2DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                       STD_ON
#define PDUR_SIZEOFBMTXBUFFERARRAYRAMOFPCPARTITIONCONFIG                                            STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINDROMOFPCPARTITIONCONFIG                                              STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINSTANCERAMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFBMTXBUFFERINSTANCEROMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFBMTXBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                    STD_ON
#define PDUR_SIZEOFBMTXBUFFERRAMOFPCPARTITIONCONFIG                                                 STD_OFF
#define PDUR_SIZEOFBMTXBUFFERROMOFPCPARTITIONCONFIG                                                 STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHEARRAYRAMOFPCPARTITIONCONFIG                                    STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHERAMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFDEFERREDEVENTCACHEROMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFDESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                     STD_ON
#define PDUR_SIZEOFEXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_SIZEOFFMFIFOELEMENTRAMOFPCPARTITIONCONFIG                                              STD_OFF
#define PDUR_SIZEOFFMFIFORAMOFPCPARTITIONCONFIG                                                     STD_OFF
#define PDUR_SIZEOFFMFIFOROMOFPCPARTITIONCONFIG                                                     STD_OFF
#define PDUR_SIZEOFGENERALPROPERTIESROMOFPCPARTITIONCONFIG                                          STD_ON
#define PDUR_SIZEOFINITIALIZEDRAMOFPCPARTITIONCONFIG                                                STD_ON
#define PDUR_SIZEOFINTERFACEFIFOQUEUEARRAYRAMOFPCPARTITIONCONFIG                                    STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEELEMENTRAMOFPCPARTITIONCONFIG                                  STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEMETADATAARRAYRAMOFPCPARTITIONCONFIG                            STD_ON
#define PDUR_SIZEOFINTERFACEFIFOQUEUERAMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFINTERFACEFIFOQUEUEROMOFPCPARTITIONCONFIG                                         STD_OFF
#define PDUR_SIZEOFLOCKROMOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_SIZEOFMCQBUFFERARRAYRAMOFPCPARTITIONCONFIG                                             STD_OFF
#define PDUR_SIZEOFMCQBUFFERRAMOFPCPARTITIONCONFIG                                                  STD_OFF
#define PDUR_SIZEOFMCQBUFFERROMOFPCPARTITIONCONFIG                                                  STD_OFF
#define PDUR_SIZEOFMMROMOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_SIZEOFRMBUFFEREDIFPROPERTIESRAMOFPCPARTITIONCONFIG                                     STD_OFF
#define PDUR_SIZEOFRMBUFFEREDIFPROPERTIESROMOFPCPARTITIONCONFIG                                     STD_OFF
#define PDUR_SIZEOFRMBUFFEREDTPPROPERTIESRAMOFPCPARTITIONCONFIG                                     STD_OFF
#define PDUR_SIZEOFRMBUFFEREDTPPROPERTIESROMOFPCPARTITIONCONFIG                                     STD_OFF
#define PDUR_SIZEOFRMDESTROMOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_SIZEOFRMDESTRPGRAMOFPCPARTITIONCONFIG                                                  STD_ON
#define PDUR_SIZEOFRMDESTRPGROMINDOFPCPARTITIONCONFIG                                               STD_ON
#define PDUR_SIZEOFRMDESTRPGROMOFPCPARTITIONCONFIG                                                  STD_ON
#define PDUR_SIZEOFRMGDESTNTO1INFORAMOFPCPARTITIONCONFIG                                            STD_ON
#define PDUR_SIZEOFRMGDESTNTO1INFOROMOFPCPARTITIONCONFIG                                            STD_ON
#define PDUR_SIZEOFRMGDESTQUEUEDTPRAMOFPCPARTITIONCONFIG                                            STD_OFF
#define PDUR_SIZEOFRMGDESTQUEUEDTPROMOFPCPARTITIONCONFIG                                            STD_OFF
#define PDUR_SIZEOFRMGDESTROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_SIZEOFRMSRCROMOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_SIZEOFRPGEXTIDROMOFPCPARTITIONCONFIG                                                   STD_ON
#define PDUR_SIZEOFRPGRAMOFPCPARTITIONCONFIG                                                        STD_ON
#define PDUR_SIZEOFRPGROMOFPCPARTITIONCONFIG                                                        STD_ON
#define PDUR_SIZEOFRXIF2DESTOFPCPARTITIONCONFIG                                                     [!IF "$numIfRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFRXTP2DESTOFPCPARTITIONCONFIG                                                     [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFRXTP2SRCOFPCPARTITIONCONFIG                                                      [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFSINGLEBUFFERARRAYRAMOFPCPARTITIONCONFIG                                          STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERINITVALUESROMOFPCPARTITIONCONFIG                                     STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                  STD_ON
#define PDUR_SIZEOFSINGLEBUFFERRAMOFPCPARTITIONCONFIG                                               STD_OFF
#define PDUR_SIZEOFSINGLEBUFFERROMOFPCPARTITIONCONFIG                                               STD_OFF
#define PDUR_SIZEOFSPINLOCKCOUNTERRAMOFPCPARTITIONCONFIG                                            STD_OFF
#define PDUR_SIZEOFSPINLOCKRAMOFPCPARTITIONCONFIG                                                   STD_OFF
#define PDUR_SIZEOFSPINLOCKROMOFPCPARTITIONCONFIG                                                   STD_OFF
#define PDUR_SIZEOFSRCAPPLICATIONROMOFPCPARTITIONCONFIG                                             STD_ON
#define PDUR_SIZEOFTX2LOOFPCPARTITIONCONFIG                                                         [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFTXIF2UPOFPCPARTITIONCONFIG                                                       [!IF "$numIfTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SIZEOFTXTP2SRCOFPCPARTITIONCONFIG                                                      [!IF "$numTpTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                                   STD_ON
#define PDUR_TX2LOOFPCPARTITIONCONFIG                                                               [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_TXIF2UPOFPCPARTITIONCONFIG                                                             [!IF "$numIfTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_TXTP2SRCOFPCPARTITIONCONFIG                                                            [!IF "$numTpTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* Min / Max / NoValue Defines */
#define PDUR_MIN_BMTXBUFFERMETADATAARRAYRAM                                                         0u
#define PDUR_MIN_INTERFACEFIFOQUEUEMETADATAARRAYRAM                                                 0u
#define PDUR_MIN_ENABLEDCNTOFRMDESTRPGRAM                                                           0u
#define PDUR_MIN_RMDESTROMIDXOFRMGDESTNTO1INFORAM                                                   0u
#define PDUR_MIN_SINGLEBUFFERMETADATAARRAYRAM                                                       0u
#define PDUR_MAX_BMTXBUFFERMETADATAARRAYRAM                                                         255u
#define PDUR_MAX_INTERFACEFIFOQUEUEMETADATAARRAYRAM                                                 255u
#define PDUR_MAX_ENABLEDCNTOFRMDESTRPGRAM                                                           65535u
#define PDUR_MAX_RMDESTROMIDXOFRMGDESTNTO1INFORAM                                                   255u
#define PDUR_MAX_SINGLEBUFFERMETADATAARRAYRAM                                                       255u
#define PDUR_NO_DESTAPPLICATIONMANAGERROMIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM               255u
#define PDUR_NO_INITIALIZEDPARTITIONIDXOFDESTAPPLICATIONMANAGERROM                                  255u
#define PDUR_NO_RMGDESTROMENDIDXOFDESTAPPLICATIONMANAGERROM                                         255u
#define PDUR_NO_RMGDESTROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                       255u
#define PDUR_NO_EXCLUSIVEAREAROMIDXOFLOCKROM                                                        255u
#define PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM                                                          255u
#define PDUR_NO_RMDESTRPGROMPARTITIONIDXOFRMDESTROM                                                 255u
#define PDUR_NO_INITIALENABLEDCNTOFRMDESTRPGROM                                                     255u
#define PDUR_NO_RMDESTROMIDXOFRMDESTRPGROM                                                          255u
#define PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM                                                    255u
#define PDUR_NO_DESTHNDOFRMGDESTROM                                                                 255u
#define PDUR_NO_RMGDESTNTO1INFOROMIDXOFRMGDESTROM                                                   255u
#define PDUR_NO_RMGDESTNTO1INFOROMPARTITIONIDXOFRMGDESTROM                                          255u
#define PDUR_NO_RPGROMIDXOFRPGEXTIDROM                                                              255u
#define PDUR_NO_RPGROMPARTITIONIDXOFRPGEXTIDROM                                                     255u
#define PDUR_NO_RMDESTRPGROMINDENDIDXOFRPGROM                                                       255u
#define PDUR_NO_RMDESTRPGROMINDSTARTIDXOFRPGROM                                                     255u

/* Exists Defines */
#define PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                              STD_OFF
#define PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                       STD_OFF
#define PDUR_EXISTS_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                    [!IF "$hasShortenLen > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_DISCARD_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                    [!IF "$hasDiscardLen > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                     [!IF "$hasIgnoreLen > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                     [!IF "$hasUnusedLen > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 [!IF "$numIfRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 [!IF "$numIfTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_IF_UNBUFFERED_UL_API_FWD_ROUTINGTYPEOFRMDESTROM                                 STD_OFF
#define PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM                                      STD_OFF
#define PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM                                              STD_OFF
#define PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 [!IF "$numTpRx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 [!IF "$numTpTx > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM                                              STD_OFF
#define PDUR_EXISTS_RX_DIRECTIONOFRMGDESTROM                                                        [!IF "($numIfRx + $numTpRx) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_TX_DIRECTIONOFRMGDESTROM                                                        [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM                                      STD_OFF
#define PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM                                     STD_ON
#define PDUR_EXISTS_RX_DIRECTIONOFRMSRCROM                                                          [!IF "($numIfRx + $numTpRx) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define PDUR_EXISTS_TX_DIRECTIONOFRMSRCROM                                                          [!IF "$numTxAll > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* Constant Enumeration Values */
#define PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                     0x00u
#define PDUR_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                              0x01u
#define PDUR_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                           0x00u
#define PDUR_DISCARD_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                           0x01u
#define PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                            0x02u
#define PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                            0x03u
#define PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x00u
#define PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x01u
#define PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x05u
#define PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x06u
#define PDUR_RX_DIRECTIONOFRMGDESTROM                                                               0x00u
#define PDUR_TX_DIRECTIONOFRMGDESTROM                                                               0x01u
#define PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM                                             0x00u
#define PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM                                            0x01u
#define PDUR_RX_DIRECTIONOFRMSRCROM                                                                 0x00u
#define PDUR_TX_DIRECTIONOFRMSRCROM                                                                 0x01u

/* ISDEF Defines */
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM            STD_OFF
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMUSEDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM           STD_OFF
#define PDUR_ISDEF_INVALIDHNDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                              STD_OFF
#define PDUR_ISDEF_PARTITIONCONFIGIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                      STD_OFF
#define PDUR_ISDEF_INITIALIZEDIDXOFDESTAPPLICATIONMANAGERROM                                        STD_ON
#define PDUR_ISDEF_INITIALIZEDPARTITIONIDXOFDESTAPPLICATIONMANAGERROM                               STD_ON
#define PDUR_ISDEF_RMGDESTROMENDIDXOFDESTAPPLICATIONMANAGERROM                                      STD_ON
#define PDUR_ISDEF_RMGDESTROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                    STD_ON
#define PDUR_ISDEF_RMGDESTROMUSEDOFDESTAPPLICATIONMANAGERROM                                        STD_ON
#define PDUR_ISDEF_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                               STD_ON
#define PDUR_ISDEF_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                             STD_ON
#define PDUR_ISDEF_LOCKOFEXCLUSIVEAREAROM                                                           STD_OFF
#define PDUR_ISDEF_UNLOCKOFEXCLUSIVEAREAROM                                                         STD_OFF
#define PDUR_ISDEF_SPINLOCKRETRYCOUNTEROFGENERALPROPERTIESROM                                       STD_ON
#define PDUR_ISDEF_EXCLUSIVEAREAROMIDXOFLOCKROM                                                     STD_ON
#define PDUR_ISDEF_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                    STD_ON
#define PDUR_ISDEF_CANCELRECEIVESUPPORTEDOFMMROM                                                    STD_ON
#define PDUR_ISDEF_CHANGEPARAMETERSUPPORTEDOFMMROM                                                  STD_ON
#define PDUR_ISDEF_IFCANCELTRANSMITSUPPORTEDOFMMROM                                                 STD_ON
#define PDUR_ISDEF_LOIFCANCELTRANSMITFCTPTROFMMROM                                                  STD_OFF
#define PDUR_ISDEF_LOIFOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_LOIFTRANSMITFCTPTROFMMROM                                                        STD_OFF
#define PDUR_ISDEF_LOTPCANCELRECEIVEFCTPTROFMMROM                                                   STD_OFF
#define PDUR_ISDEF_LOTPCANCELTRANSMITFCTPTROFMMROM                                                  STD_OFF
#define PDUR_ISDEF_LOTPCHANGEPARAMETERFCTPTROFMMROM                                                 STD_OFF
#define PDUR_ISDEF_LOTPOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_LOTPTRANSMITFCTPTROFMMROM                                                        STD_OFF
#define PDUR_ISDEF_TPCANCELTRANSMITSUPPORTEDOFMMROM                                                 STD_ON
#define PDUR_ISDEF_UPIFOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_UPIFRXINDICATIONFCTPTROFMMROM                                                    STD_OFF
#define PDUR_ISDEF_UPIFTRIGGERTRANSMITFCTPTROFMMROM                                                 STD_OFF
#define PDUR_ISDEF_UPIFTXCONFIRMATIONFCTPTROFMMROM                                                  STD_OFF
#define PDUR_ISDEF_UPTPCOPYRXDATAFCTPTROFMMROM                                                      STD_OFF
#define PDUR_ISDEF_UPTPCOPYTXDATAFCTPTROFMMROM                                                      STD_OFF
#define PDUR_ISDEF_UPTPOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_UPTPSTARTOFRECEPTIONFCTPTROFMMROM                                                STD_OFF
#define PDUR_ISDEF_UPTPTPRXINDICATIONFCTPTROFMMROM                                                  STD_OFF
#define PDUR_ISDEF_UPTPTPTXCONFIRMATIONFCTPTROFMMROM                                                STD_OFF
#define PDUR_ISDEF_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                       STD_OFF
#define PDUR_ISDEF_PARTITIONSNVOFPARTITIONIDENTIFIERS                                               STD_OFF
#define PDUR_ISDEF_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM                                           STD_ON
#define PDUR_ISDEF_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                             STD_OFF
#define PDUR_ISDEF_QUEUEDOFRMDESTROM                                                                STD_ON
#define PDUR_ISDEF_RMDESTRPGROMIDXOFRMDESTROM                                                       STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMPARTITIONIDXOFRMDESTROM                                              STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMUSEDOFRMDESTROM                                                      STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFRMDESTROM                                                         STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRMDESTROM                                                           STD_OFF
#define PDUR_ISDEF_ROUTINGTYPEOFRMDESTROM                                                           STD_OFF
#define PDUR_ISDEF_INITIALENABLEDCNTOFRMDESTRPGROM                                                  STD_OFF
#define PDUR_ISDEF_RMDESTROMIDXOFRMDESTRPGROM                                                       STD_OFF
#define PDUR_ISDEF_RMDESTROMUSEDOFRMDESTRPGROM                                                      STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMIND                                                                  STD_OFF
#define PDUR_ISDEF_EXPECTTXCONFIRMATIONOFRMGDESTNTO1INFOROM                                         STD_OFF
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMIDXOFRMGDESTROM                                         STD_ON
#define PDUR_ISDEF_DESTHNDOFRMGDESTROM                                                              STD_OFF
#define PDUR_ISDEF_DIRECTIONOFRMGDESTROM                                                            STD_OFF
#define PDUR_ISDEF_LOCKROMIDXOFRMGDESTROM                                                           STD_ON
#define PDUR_ISDEF_METADATALENGTHOFRMGDESTROM                                                       STD_ON
#define PDUR_ISDEF_MMROMIDXOFRMGDESTROM                                                             STD_OFF
#define PDUR_ISDEF_PDULENGTHOFRMGDESTROM                                                            STD_OFF
#define PDUR_ISDEF_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                STD_ON
#define PDUR_ISDEF_RMDESTROMIDXOFRMGDESTROM                                                         STD_OFF
#define PDUR_ISDEF_RMGDESTNTO1INFOROMIDXOFRMGDESTROM                                                STD_OFF
#define PDUR_ISDEF_RMGDESTNTO1INFOROMPARTITIONIDXOFRMGDESTROM                                       STD_OFF
#define PDUR_ISDEF_RMGDESTNTO1INFOROMUSEDOFRMGDESTROM                                               STD_OFF
#define PDUR_ISDEF_TXIF2UPIDXOFRMGDESTROM                                                           STD_OFF
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMIDXOFRMSRCROM                                           STD_ON
#define PDUR_ISDEF_DIRECTIONOFRMSRCROM                                                              STD_OFF
#define PDUR_ISDEF_IFOFRMSRCROM                                                                     STD_OFF
#define PDUR_ISDEF_LOCKROMIDXOFRMSRCROM                                                             STD_ON
#define PDUR_ISDEF_MMROMIDXOFRMSRCROM                                                               STD_OFF
#define PDUR_ISDEF_RMDESTROMENDIDXOFRMSRCROM                                                        STD_OFF
#define PDUR_ISDEF_RMDESTROMLENGTHOFRMSRCROM                                                        STD_ON
#define PDUR_ISDEF_RMDESTROMSTARTIDXOFRMSRCROM                                                      STD_OFF
#define PDUR_ISDEF_SRCHNDOFRMSRCROM                                                                 STD_OFF
#define PDUR_ISDEF_TPOFRMSRCROM                                                                     STD_OFF
#define PDUR_ISDEF_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                               STD_ON
#define PDUR_ISDEF_TXCONFIRMATIONSUPPORTEDOFRMSRCROM                                                STD_OFF
#define PDUR_ISDEF_INVALIDHNDOFRPGEXTIDROM                                                          STD_OFF
#define PDUR_ISDEF_RPGROMIDXOFRPGEXTIDROM                                                           STD_OFF
#define PDUR_ISDEF_RPGROMPARTITIONIDXOFRPGEXTIDROM                                                  STD_OFF
#define PDUR_ISDEF_RPGROMUSEDOFRPGEXTIDROM                                                          STD_OFF
#define PDUR_ISDEF_ENABLEDATINITOFRPGROM                                                            STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMINDENDIDXOFRPGROM                                                    STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMINDSTARTIDXOFRPGROM                                                  STD_OFF
#define PDUR_ISDEF_RMDESTRPGROMINDUSEDOFRPGROM                                                      STD_OFF
#define PDUR_ISDEF_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST                                          STD_ON
#define PDUR_ISDEF_INVALIDHNDOFRXIF2DEST                                                            STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRXIF2DEST                                                           STD_OFF
#define PDUR_ISDEF_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST                                        STD_ON
#define PDUR_ISDEF_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST                                    STD_ON
#define PDUR_ISDEF_INVALIDHNDOFRXTP2DEST                                                            STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRXTP2DEST                                                           STD_OFF
#define PDUR_ISDEF_INVALIDHNDOFRXTP2SRC                                                             STD_OFF
#define PDUR_ISDEF_RMDESTROMIDXOFRXTP2SRC                                                           STD_OFF
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMDESTINATIONIDXOFSRCAPPLICATIONROM                       STD_ON
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMSOURCEIDXOFSRCAPPLICATIONROM                            STD_ON
#define PDUR_ISDEF_BSWMPDURTRANSMITCALLBACKOFTX2LO                                                  STD_ON
#define PDUR_ISDEF_CANCELTRANSMITUSEDOFTX2LO                                                        STD_ON
#define PDUR_ISDEF_INVALIDHNDOFTX2LO                                                                STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFTX2LO                                                               STD_OFF
#define PDUR_ISDEF_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP                                          STD_ON
#define PDUR_ISDEF_INVALIDHNDOFTXIF2UP                                                              STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFTXIF2UP                                                           STD_OFF
#define PDUR_ISDEF_TXCONFIRMATIONUSEDOFTXIF2UP                                                      STD_ON
#define PDUR_ISDEF_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC                                       STD_ON
#define PDUR_ISDEF_INVALIDHNDOFTXTP2SRC                                                             STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFTXTP2SRC                                                          STD_ON
#define PDUR_ISDEF_PCPARTITIONCONFIGOFPCCONFIG                                                      STD_ON
#define PDUR_ISDEF_PARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define PDUR_ISDEF_APPLICATIONID2DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                       STD_ON
#define PDUR_ISDEF_BMTXBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                    STD_ON
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                     STD_ON
#define PDUR_ISDEF_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_ISDEF_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                          STD_ON
#define PDUR_ISDEF_INITIALIZEDRAMOFPCPARTITIONCONFIG                                                STD_ON
#define PDUR_ISDEF_INTERFACEFIFOQUEUEMETADATAARRAYRAMOFPCPARTITIONCONFIG                            STD_ON
#define PDUR_ISDEF_LOCKROMOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_ISDEF_MMROMOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_ISDEF_RMDESTROMOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_ISDEF_RMDESTRPGRAMOFPCPARTITIONCONFIG                                                  STD_ON
#define PDUR_ISDEF_RMDESTRPGROMINDOFPCPARTITIONCONFIG                                               STD_ON
#define PDUR_ISDEF_RMDESTRPGROMOFPCPARTITIONCONFIG                                                  STD_ON
#define PDUR_ISDEF_RMGDESTNTO1INFORAMOFPCPARTITIONCONFIG                                            STD_ON
#define PDUR_ISDEF_RMGDESTNTO1INFOROMOFPCPARTITIONCONFIG                                            STD_ON
#define PDUR_ISDEF_RMGDESTROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_ISDEF_RMSRCROMOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_ISDEF_RPGEXTIDROMOFPCPARTITIONCONFIG                                                   STD_ON
#define PDUR_ISDEF_RPGRAMOFPCPARTITIONCONFIG                                                        STD_ON
#define PDUR_ISDEF_RPGROMOFPCPARTITIONCONFIG                                                        STD_ON
#define PDUR_ISDEF_RXIF2DESTOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_ISDEF_RXTP2DESTOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_ISDEF_RXTP2SRCOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_ISDEF_SINGLEBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                  STD_ON
#define PDUR_ISDEF_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                             STD_ON
#define PDUR_ISDEF_TX2LOOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_ISDEF_TXIF2UPOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_ISDEF_TXTP2SRCOFPCPARTITIONCONFIG                                                      STD_ON

/* EQ2 Defines */
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMUSEDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM
#define PDUR_EQ2_INVALIDHNDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM
#define PDUR_EQ2_PARTITIONCONFIGIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM
#define PDUR_EQ2_INITIALIZEDIDXOFDESTAPPLICATIONMANAGERROM                                          0u
#define PDUR_EQ2_INITIALIZEDPARTITIONIDXOFDESTAPPLICATIONMANAGERROM                                 0u
#define PDUR_EQ2_RMGDESTROMENDIDXOFDESTAPPLICATIONMANAGERROM                                        [!"num:i($numPaths)"!]u
#define PDUR_EQ2_RMGDESTROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                      0u
#define PDUR_EQ2_RMGDESTROMUSEDOFDESTAPPLICATIONMANAGERROM                                          TRUE
#define PDUR_EQ2_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                                 1u
#define PDUR_EQ2_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                               0u
#define PDUR_EQ2_LOCKOFEXCLUSIVEAREAROM
#define PDUR_EQ2_UNLOCKOFEXCLUSIVEAREAROM
#define PDUR_EQ2_SPINLOCKRETRYCOUNTEROFGENERALPROPERTIESROM                                         [!"num:i($spinLock)"!]u
#define PDUR_EQ2_EXCLUSIVEAREAROMIDXOFLOCKROM                                                       0u
#define PDUR_EQ2_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                      TRUE
#define PDUR_EQ2_CANCELRECEIVESUPPORTEDOFMMROM                                                      FALSE
#define PDUR_EQ2_CHANGEPARAMETERSUPPORTEDOFMMROM                                                    FALSE
#define PDUR_EQ2_IFCANCELTRANSMITSUPPORTEDOFMMROM                                                   FALSE
#define PDUR_EQ2_LOIFCANCELTRANSMITFCTPTROFMMROM
#define PDUR_EQ2_LOIFOFMMROM
#define PDUR_EQ2_LOIFTRANSMITFCTPTROFMMROM
#define PDUR_EQ2_LOTPCANCELRECEIVEFCTPTROFMMROM
#define PDUR_EQ2_LOTPCANCELTRANSMITFCTPTROFMMROM
#define PDUR_EQ2_LOTPCHANGEPARAMETERFCTPTROFMMROM
#define PDUR_EQ2_LOTPOFMMROM
#define PDUR_EQ2_LOTPTRANSMITFCTPTROFMMROM
#define PDUR_EQ2_TPCANCELTRANSMITSUPPORTEDOFMMROM                                                   FALSE
#define PDUR_EQ2_UPIFOFMMROM
#define PDUR_EQ2_UPIFRXINDICATIONFCTPTROFMMROM
#define PDUR_EQ2_UPIFTRIGGERTRANSMITFCTPTROFMMROM
#define PDUR_EQ2_UPIFTXCONFIRMATIONFCTPTROFMMROM
#define PDUR_EQ2_UPTPCOPYRXDATAFCTPTROFMMROM
#define PDUR_EQ2_UPTPCOPYTXDATAFCTPTROFMMROM
#define PDUR_EQ2_UPTPOFMMROM
#define PDUR_EQ2_UPTPSTARTOFRECEPTIONFCTPTROFMMROM
#define PDUR_EQ2_UPTPTPRXINDICATIONFCTPTROFMMROM
#define PDUR_EQ2_UPTPTPTXCONFIRMATIONFCTPTROFMMROM
#define PDUR_EQ2_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS
#define PDUR_EQ2_PARTITIONSNVOFPARTITIONIDENTIFIERS
#define PDUR_EQ2_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM                                             FALSE
#define PDUR_EQ2_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM
#define PDUR_EQ2_QUEUEDOFRMDESTROM                                                                  FALSE
#define PDUR_EQ2_RMDESTRPGROMIDXOFRMDESTROM
#define PDUR_EQ2_RMDESTRPGROMPARTITIONIDXOFRMDESTROM
#define PDUR_EQ2_RMDESTRPGROMUSEDOFRMDESTROM
#define PDUR_EQ2_RMGDESTROMIDXOFRMDESTROM
#define PDUR_EQ2_RMSRCROMIDXOFRMDESTROM
#define PDUR_EQ2_ROUTINGTYPEOFRMDESTROM
#define PDUR_EQ2_INITIALENABLEDCNTOFRMDESTRPGROM
#define PDUR_EQ2_RMDESTROMIDXOFRMDESTRPGROM
#define PDUR_EQ2_RMDESTROMUSEDOFRMDESTRPGROM
#define PDUR_EQ2_RMDESTRPGROMIND
#define PDUR_EQ2_EXPECTTXCONFIRMATIONOFRMGDESTNTO1INFOROM
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMIDXOFRMGDESTROM                                           0u
#define PDUR_EQ2_DESTHNDOFRMGDESTROM
#define PDUR_EQ2_DIRECTIONOFRMGDESTROM
#define PDUR_EQ2_LOCKROMIDXOFRMGDESTROM                                                             0u
#define PDUR_EQ2_METADATALENGTHOFRMGDESTROM                                                         0u
#define PDUR_EQ2_MMROMIDXOFRMGDESTROM
#define PDUR_EQ2_PDULENGTHOFRMGDESTROM
#define PDUR_EQ2_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                  PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM
#define PDUR_EQ2_RMDESTROMIDXOFRMGDESTROM
#define PDUR_EQ2_RMGDESTNTO1INFOROMIDXOFRMGDESTROM
#define PDUR_EQ2_RMGDESTNTO1INFOROMPARTITIONIDXOFRMGDESTROM
#define PDUR_EQ2_RMGDESTNTO1INFOROMUSEDOFRMGDESTROM
#define PDUR_EQ2_TXIF2UPIDXOFRMGDESTROM
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMIDXOFRMSRCROM                                             0u
#define PDUR_EQ2_DIRECTIONOFRMSRCROM
#define PDUR_EQ2_IFOFRMSRCROM
#define PDUR_EQ2_LOCKROMIDXOFRMSRCROM                                                               0u
#define PDUR_EQ2_MMROMIDXOFRMSRCROM
#define PDUR_EQ2_RMDESTROMENDIDXOFRMSRCROM
#define PDUR_EQ2_RMDESTROMLENGTHOFRMSRCROM                                                          1u
#define PDUR_EQ2_RMDESTROMSTARTIDXOFRMSRCROM
#define PDUR_EQ2_SRCHNDOFRMSRCROM
#define PDUR_EQ2_TPOFRMSRCROM
#define PDUR_EQ2_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                                 FALSE
#define PDUR_EQ2_TXCONFIRMATIONSUPPORTEDOFRMSRCROM
#define PDUR_EQ2_INVALIDHNDOFRPGEXTIDROM
#define PDUR_EQ2_RPGROMIDXOFRPGEXTIDROM
#define PDUR_EQ2_RPGROMPARTITIONIDXOFRPGEXTIDROM
#define PDUR_EQ2_RPGROMUSEDOFRPGEXTIDROM
#define PDUR_EQ2_ENABLEDATINITOFRPGROM
#define PDUR_EQ2_RMDESTRPGROMINDENDIDXOFRPGROM
#define PDUR_EQ2_RMDESTRPGROMINDSTARTIDXOFRPGROM
#define PDUR_EQ2_RMDESTRPGROMINDUSEDOFRPGROM
#define PDUR_EQ2_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST                                            FALSE
#define PDUR_EQ2_INVALIDHNDOFRXIF2DEST
#define PDUR_EQ2_RMSRCROMIDXOFRXIF2DEST
#define PDUR_EQ2_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST                                          FALSE
#define PDUR_EQ2_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST                                      FALSE
#define PDUR_EQ2_INVALIDHNDOFRXTP2DEST
#define PDUR_EQ2_RMSRCROMIDXOFRXTP2DEST
#define PDUR_EQ2_INVALIDHNDOFRXTP2SRC
#define PDUR_EQ2_RMDESTROMIDXOFRXTP2SRC
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMDESTINATIONIDXOFSRCAPPLICATIONROM                         0u
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMSOURCEIDXOFSRCAPPLICATIONROM                              0u
#define PDUR_EQ2_BSWMPDURTRANSMITCALLBACKOFTX2LO                                                    FALSE
#define PDUR_EQ2_CANCELTRANSMITUSEDOFTX2LO                                                          FALSE
#define PDUR_EQ2_INVALIDHNDOFTX2LO
#define PDUR_EQ2_RMSRCROMIDXOFTX2LO
#define PDUR_EQ2_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP                                            FALSE
#define PDUR_EQ2_INVALIDHNDOFTXIF2UP
#define PDUR_EQ2_RMGDESTROMIDXOFTXIF2UP
#define PDUR_EQ2_TXCONFIRMATIONUSEDOFTXIF2UP                                                        TRUE
#define PDUR_EQ2_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC                                         FALSE
#define PDUR_EQ2_INVALIDHNDOFTXTP2SRC
#define PDUR_EQ2_RMGDESTROMIDXOFTXTP2SRC                                                            0u
#define PDUR_EQ2_PCPARTITIONCONFIGOFPCCONFIG                                                        PduR_PCPartitionConfig
#define PDUR_EQ2_PARTITIONIDENTIFIERSOFPCCONFIG                                                     PduR_PartitionIdentifiers
#define PDUR_EQ2_APPLICATIONID2DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                         PduR_ApplicationId2DestApplicationManagerRom
#define PDUR_EQ2_BMTXBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                      PduR_BmTxBufferMetaDataArrayRam
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                       PduR_DestApplicationManagerRom
#define PDUR_EQ2_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                                PduR_ExclusiveAreaRom
#define PDUR_EQ2_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                            PduR_GeneralPropertiesRom
#define PDUR_EQ2_INITIALIZEDRAMOFPCPARTITIONCONFIG                                                  PduR_InitializedRam
#define PDUR_EQ2_INTERFACEFIFOQUEUEMETADATAARRAYRAMOFPCPARTITIONCONFIG                              PduR_InterfaceFifoQueueMetaDataArrayRam
#define PDUR_EQ2_LOCKROMOFPCPARTITIONCONFIG                                                         PduR_LockRom
#define PDUR_EQ2_MMROMOFPCPARTITIONCONFIG                                                           PduR_MmRom
#define PDUR_EQ2_RMDESTROMOFPCPARTITIONCONFIG                                                       PduR_RmDestRom
#define PDUR_EQ2_RMDESTRPGRAMOFPCPARTITIONCONFIG                                                    PduR_RmDestRpgRam
#define PDUR_EQ2_RMDESTRPGROMINDOFPCPARTITIONCONFIG                                                 PduR_RmDestRpgRomInd
#define PDUR_EQ2_RMDESTRPGROMOFPCPARTITIONCONFIG                                                    PduR_RmDestRpgRom
#define PDUR_EQ2_RMGDESTNTO1INFORAMOFPCPARTITIONCONFIG                                              PduR_RmGDestNto1InfoRam
#define PDUR_EQ2_RMGDESTNTO1INFOROMOFPCPARTITIONCONFIG                                              PduR_RmGDestNto1InfoRom
#define PDUR_EQ2_RMGDESTROMOFPCPARTITIONCONFIG                                                      PduR_RmGDestRom
#define PDUR_EQ2_RMSRCROMOFPCPARTITIONCONFIG                                                        PduR_RmSrcRom
#define PDUR_EQ2_RPGEXTIDROMOFPCPARTITIONCONFIG                                                     PduR_RpgExtIdRom
#define PDUR_EQ2_RPGRAMOFPCPARTITIONCONFIG                                                          PduR_RpgRam
#define PDUR_EQ2_RPGROMOFPCPARTITIONCONFIG                                                          PduR_RpgRom
#define PDUR_EQ2_RXIF2DESTOFPCPARTITIONCONFIG                                                       PduR_RxIf2Dest
#define PDUR_EQ2_RXTP2DESTOFPCPARTITIONCONFIG                                                       PduR_RxTp2Dest
#define PDUR_EQ2_RXTP2SRCOFPCPARTITIONCONFIG                                                        PduR_RxTp2Src
#define PDUR_EQ2_SINGLEBUFFERMETADATAARRAYRAMOFPCPARTITIONCONFIG                                    PduR_SingleBufferMetaDataArrayRam
#define PDUR_EQ2_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                               PduR_SrcApplicationRom
#define PDUR_EQ2_TX2LOOFPCPARTITIONCONFIG                                                           PduR_Tx2Lo
#define PDUR_EQ2_TXIF2UPOFPCPARTITIONCONFIG                                                         PduR_TxIf2Up
#define PDUR_EQ2_TXTP2SRCOFPCPARTITIONCONFIG                                                        PduR_TxTp2Src

#define PduR_ApplicationId2DestApplicationManagerRom                                                ((PduR_ApplicationId2DestApplicationManagerRomPtrType)(NULL_PTR))
#define PduR_BmTxBufferMetaDataArrayRam                                                             ((PduR_BmTxBufferMetaDataArrayRamPtrType)(NULL_PTR))
#define PduR_DestApplicationManagerRom                                                              ((PduR_DestApplicationManagerRomPtrType)(NULL_PTR))
#define PduR_GeneralPropertiesRom                                                                   ((PduR_GeneralPropertiesRomPtrType)(NULL_PTR))
#define PduR_InterfaceFifoQueueMetaDataArrayRam                                                     ((PduR_InterfaceFifoQueueMetaDataArrayRamPtrType)(NULL_PTR))
#define PduR_LockRom                                                                                ((PduR_LockRomPtrType)(NULL_PTR))
#define PduR_RmDestRpgRam                                                                           ((PduR_RmDestRpgRamPtrType)(NULL_PTR))
#define PduR_RmDestRpgRom                                                                           ((PduR_RmDestRpgRomPtrType)(NULL_PTR))
#define PduR_RmDestRpgRomInd                                                                        ((PduR_RmDestRpgRomIndPtrType)(NULL_PTR))
#define PduR_RmGDestNto1InfoRam                                                                     ((PduR_RmGDestNto1InfoRamPtrType)(NULL_PTR))
#define PduR_RmGDestNto1InfoRom                                                                     ((PduR_RmGDestNto1InfoRomPtrType)(NULL_PTR))
#define PduR_RpgExtIdRom                                                                            ((PduR_RpgExtIdRomPtrType)(NULL_PTR))
#define PduR_RpgRam                                                                                 ((PduR_RpgRamPtrType)(NULL_PTR))
#define PduR_RpgRom                                                                                 ((PduR_RpgRomPtrType)(NULL_PTR))
#define PduR_RxIf2Dest                                                                              ((PduR_RxIf2DestPtrType)(NULL_PTR))
#define PduR_RxTp2Dest                                                                              ((PduR_RxTp2DestPtrType)(NULL_PTR))
[!IF "$numTpRx = 0"!][!//
#define PduR_RxTp2Src                                                                               ((PduR_RxTp2SrcPtrType)(NULL_PTR))
[!ENDIF!][!//
#define PduR_SingleBufferMetaDataArrayRam                                                           ((PduR_SingleBufferMetaDataArrayRamPtrType)(NULL_PTR))
#define PduR_SrcApplicationRom                                                                      ((PduR_SrcApplicationRomPtrType)(NULL_PTR))
#define PduR_Tx2Lo                                                                                  ((PduR_Tx2LoPtrType)(NULL_PTR))
#define PduR_TxIf2Up                                                                                ((PduR_TxIf2UpPtrType)(NULL_PTR))
#define PduR_TxTp2Src                                                                               ((PduR_TxTp2SrcPtrType)(NULL_PTR))

#define PduR_Config_Ptr                                                                             NULL_PTR
#define PduR_Config                                                                                 NULL_PTR
#define PDUR_CHECK_INIT_POINTER                                                                     STD_OFF
#define PDUR_FINAL_MAGIC_NUMBER                                                                     0x331Eu
#define PDUR_INDIVIDUAL_POSTBUILD                                                                   STD_OFF
#define PDUR_INIT_DATA                                                                              PDUR_CONST
#define PDUR_INIT_DATA_HASH_CODE                                                                    -863935689
#define PDUR_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF
#define PDUR_USE_INIT_POINTER                                                                       STD_OFF
#define PduR_PartitionIndexOfCSLForCommonSharedMemory                                               0u
#define PDUR_LTCONFIG                                                                               STD_OFF
#define PDUR_LTPARTITIONCONFIGOFLTCONFIG                                                            STD_OFF
#define PDUR_LTPARTITIONCONFIG                                                                      STD_OFF
#define PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE 1
#define PDUR_MAX_META_DATA_SIZE 1

#define PduR_GetPartitionIdentifiersOfPCConfig()                                                    PduR_PartitionIdentifiers
#define PduR_GetSizeOfPartitionIdentifiersOfPCConfig()                                              1u
#define PduR_GetApplicationId2DestApplicationManagerRomOfPCPartitionConfig()                        PduR_ApplicationId2DestApplicationManagerRom
#define PduR_GetBmTxBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex)                       PduR_BmTxBufferMetaDataArrayRam
#define PduR_GetConfigIdOfPCPartitionConfig(partitionIndex)                                         [!"num:i($cfgId)"!]u
#define PduR_GetDestApplicationManagerRomOfPCPartitionConfig()                                      PduR_DestApplicationManagerRom
#define PduR_GetExclusiveAreaRomOfPCPartitionConfig()                                               PduR_ExclusiveAreaRom
#define PduR_GetGeneralPropertiesRomOfPCPartitionConfig()                                           PduR_GeneralPropertiesRom
#define PduR_GetInitializedRamOfPCPartitionConfig(partitionIndex)                                   PduR_InitializedRam
#define PduR_GetInterfaceFifoQueueMetaDataArrayRamOfPCPartitionConfig(partitionIndex)               PduR_InterfaceFifoQueueMetaDataArrayRam
#define PduR_GetLockRomOfPCPartitionConfig()                                                        PduR_LockRom
#define PduR_GetMmRomOfPCPartitionConfig()                                                          PduR_MmRom
#define PduR_GetRmDestRomOfPCPartitionConfig()                                                      PduR_RmDestRom
#define PduR_GetRmDestRpgRamOfPCPartitionConfig(partitionIndex)                                     PduR_RmDestRpgRam
#define PduR_GetRmDestRpgRomIndOfPCPartitionConfig(partitionIndex)                                  PduR_RmDestRpgRomInd
#define PduR_GetRmDestRpgRomOfPCPartitionConfig(partitionIndex)                                     PduR_RmDestRpgRom
#define PduR_GetRmGDestNto1InfoRamOfPCPartitionConfig(partitionIndex)                               PduR_RmGDestNto1InfoRam
#define PduR_GetRmGDestNto1InfoRomOfPCPartitionConfig(partitionIndex)                               PduR_RmGDestNto1InfoRom
#define PduR_GetRmGDestRomOfPCPartitionConfig()                                                     PduR_RmGDestRom
#define PduR_GetRmSrcRomOfPCPartitionConfig()                                                       PduR_RmSrcRom
#define PduR_GetRpgExtIdRomOfPCPartitionConfig()                                                    PduR_RpgExtIdRom
#define PduR_GetRpgRamOfPCPartitionConfig(partitionIndex)                                           PduR_RpgRam
#define PduR_GetRpgRomOfPCPartitionConfig(partitionIndex)                                           PduR_RpgRom
#define PduR_GetRxIf2DestOfPCPartitionConfig()                                                      PduR_RxIf2Dest
#define PduR_GetRxTp2DestOfPCPartitionConfig()                                                      PduR_RxTp2Dest
#define PduR_GetRxTp2SrcOfPCPartitionConfig()                                                       PduR_RxTp2Src
#define PduR_GetSingleBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex)                     PduR_SingleBufferMetaDataArrayRam
#define PduR_GetSizeOfApplicationId2DestApplicationManagerRomOfPCPartitionConfig()                  0u
#define PduR_GetSizeOfBmTxBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex)                 0u
#define PduR_GetSizeOfDestApplicationManagerRomOfPCPartitionConfig()                                1u
#define PduR_GetSizeOfExclusiveAreaRomOfPCPartitionConfig()                                         1u
#define PduR_GetSizeOfGeneralPropertiesRomOfPCPartitionConfig()                                     1u
#define PduR_GetSizeOfInitializedRamOfPCPartitionConfig(partitionIndex)                             1u
#define PduR_GetSizeOfInterfaceFifoQueueMetaDataArrayRamOfPCPartitionConfig(partitionIndex)         0u
#define PduR_GetSizeOfLockRomOfPCPartitionConfig()                                                  1u
#define PduR_GetSizeOfMmRomOfPCPartitionConfig()                                                    [!"num:i($numMods)"!]u
#define PduR_GetSizeOfRmDestRomOfPCPartitionConfig()                                                [!"num:i($numPaths)"!]u
#define PduR_GetSizeOfRmDestRpgRamOfPCPartitionConfig(partitionIndex)                               0u
#define PduR_GetSizeOfRmDestRpgRomIndOfPCPartitionConfig(partitionIndex)                            0u
#define PduR_GetSizeOfRmDestRpgRomOfPCPartitionConfig(partitionIndex)                               0u
#define PduR_GetSizeOfRmGDestNto1InfoRamOfPCPartitionConfig(partitionIndex)                         0u
#define PduR_GetSizeOfRmGDestNto1InfoRomOfPCPartitionConfig(partitionIndex)                         0u
#define PduR_GetSizeOfRmGDestRomOfPCPartitionConfig()                                               [!"num:i($numPaths)"!]u
#define PduR_GetSizeOfRmSrcRomOfPCPartitionConfig()                                                 [!"num:i($numPaths)"!]u
#define PduR_GetSizeOfRpgExtIdRomOfPCPartitionConfig()                                              0u
#define PduR_GetSizeOfRpgRamOfPCPartitionConfig(partitionIndex)                                     0u
#define PduR_GetSizeOfRpgRomOfPCPartitionConfig(partitionIndex)                                     0u
#define PduR_GetSizeOfRxIf2DestOfPCPartitionConfig()                                                [!"num:i($numIfRx)"!]u
#define PduR_GetSizeOfRxTp2DestOfPCPartitionConfig()                                                [!"num:i($numTpRx)"!]u
#define PduR_GetSizeOfRxTp2SrcOfPCPartitionConfig()                                                 [!"num:i($numTpRx)"!]u
#define PduR_GetSizeOfSingleBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex)               0u
#define PduR_GetSizeOfSrcApplicationRomOfPCPartitionConfig()                                        1u
#define PduR_GetSizeOfTx2LoOfPCPartitionConfig()                                                    [!"num:i($numTxAll)"!]u
#define PduR_GetSizeOfTxIf2UpOfPCPartitionConfig()                                                  [!"num:i($numIfTx)"!]u
#define PduR_GetSizeOfTxTp2SrcOfPCPartitionConfig()                                                 [!"num:i($numTpTx)"!]u
#define PduR_GetSrcApplicationRomOfPCPartitionConfig()                                              PduR_SrcApplicationRom
#define PduR_GetTx2LoOfPCPartitionConfig()                                                          PduR_Tx2Lo
#define PduR_GetTxIf2UpOfPCPartitionConfig()                                                        PduR_TxIf2Up
#define PduR_GetTxTp2SrcOfPCPartitionConfig()                                                       PduR_TxTp2Src

#define PduR_IsPreInitialized()                     (PduR_PreInitialized != FALSE)
#define PduR_SetPreInitialized(Value)               (PduR_PreInitialized = (Value))

/* Function Pointer Typedefs */
typedef P2FUNC(void, PDUR_CODE, PduR_LockFunctionType) (void);
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TransmitFctPtrType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TriggerTransmitFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfRxIndicationType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfTxConfirmationFctPtrType) (PduIdType);
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_StartOfReceptionFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduLengthType, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyRxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyTxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpRxIndicationFctPtrType) (PduIdType, Std_ReturnType);
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpTxConfirmationFctPtrType) (PduIdType, Std_ReturnType);
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelTransmitFctPtrType)(PduIdType);
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelReceiveFctPtrType) (PduIdType);
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_ChangeParameterFctPtrType) (PduIdType, TPParameterType, uint16);

/* Size & Iterator Typedefs */
typedef uint8 PduR_SizeOfApplicationId2DestApplicationManagerRomType;
typedef uint8 PduR_SizeOfBmTxBufferMetaDataArrayRamType;
typedef uint8 PduR_SizeOfDestApplicationManagerRomType;
typedef uint8 PduR_SizeOfExclusiveAreaRomType;
typedef uint8 PduR_SizeOfGeneralPropertiesRomType;
typedef uint8 PduR_SizeOfInitializedRamType;
typedef uint8 PduR_SizeOfInterfaceFifoQueueMetaDataArrayRamType;
typedef uint8 PduR_SizeOfLockRomType;
typedef uint8 PduR_SizeOfMmRomType;
typedef uint8 PduR_SizeOfPartitionIdentifiersType;
typedef uint8 PduR_SizeOfRmDestRomType;
typedef uint8 PduR_SizeOfRmDestRpgRamType;
typedef uint8 PduR_SizeOfRmDestRpgRomType;
typedef uint8 PduR_SizeOfRmDestRpgRomIndType;
typedef uint8 PduR_SizeOfRmGDestNto1InfoRamType;
typedef uint8 PduR_SizeOfRmGDestNto1InfoRomType;
typedef uint8 PduR_SizeOfRmGDestRomType;
typedef uint8 PduR_SizeOfRmSrcRomType;
typedef uint8 PduR_SizeOfRpgExtIdRomType;
typedef uint8 PduR_SizeOfRpgRamType;
typedef uint8 PduR_SizeOfRpgRomType;
typedef uint8 PduR_SizeOfRxIf2DestType;
typedef uint8 PduR_SizeOfRxTp2DestType;
typedef uint8 PduR_SizeOfRxTp2SrcType;
typedef uint8 PduR_SizeOfSingleBufferMetaDataArrayRamType;
typedef uint8 PduR_SizeOfSrcApplicationRomType;
typedef uint8 PduR_SizeOfTx2LoType;
typedef uint8 PduR_SizeOfTxIf2UpType;
typedef uint8 PduR_SizeOfTxTp2SrcType;

typedef uint8_least PduR_ApplicationId2DestApplicationManagerRomIterType;
typedef uint8_least PduR_BmTxBufferMetaDataArrayRamIterType;
typedef uint8_least PduR_DestApplicationManagerRomIterType;
typedef uint8_least PduR_ExclusiveAreaRomIterType;
typedef uint8_least PduR_GeneralPropertiesRomIterType;
typedef uint8_least PduR_InitializedRamIterType;
typedef uint8_least PduR_InterfaceFifoQueueMetaDataArrayRamIterType;
typedef uint8_least PduR_LockRomIterType;
typedef uint8_least PduR_MmRomIterType;
typedef uint8_least PduR_PartitionIdentifiersIterType;
typedef uint8_least PduR_RmDestRomIterType;
typedef uint8_least PduR_RmDestRpgRomIterType;
typedef uint8_least PduR_RmDestRpgRomIndIterType;
typedef uint8_least PduR_RmGDestNto1InfoRomIterType;
typedef uint8_least PduR_RmGDestRomIterType;
typedef uint8_least PduR_RmSrcRomIterType;
typedef uint8_least PduR_RpgExtIdRomIterType;
typedef uint8_least PduR_RpgRomIterType;
typedef uint8_least PduR_RxIf2DestIterType;
typedef uint8_least PduR_RxTp2DestIterType;
typedef uint8_least PduR_RxTp2SrcIterType;
typedef uint8_least PduR_SingleBufferMetaDataArrayRamIterType;
typedef uint8_least PduR_SrcApplicationRomIterType;
typedef uint8_least PduR_Tx2LoIterType;
typedef uint8_least PduR_TxIf2UpIterType;
typedef uint8_least PduR_TxTp2SrcIterType;
typedef uint8_least PduR_PCPartitionConfigIterType;
typedef PduR_RmDestRpgRomIterType PduR_RmDestRpgRamIterType;
typedef PduR_RmGDestNto1InfoRomIterType PduR_RmGDestNto1InfoRamIterType;
typedef PduR_RpgRomIterType PduR_RpgRamIterType;

/* Field Typedefs */
typedef uint8 PduR_DestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRomType;
typedef boolean PduR_DestApplicationManagerRomUsedOfApplicationId2DestApplicationManagerRomType;
typedef boolean PduR_InvalidHndOfApplicationId2DestApplicationManagerRomType;
typedef uint8 PduR_PartitionConfigIdxOfApplicationId2DestApplicationManagerRomType;
typedef uint8 PduR_BmTxBufferMetaDataArrayRamType;
typedef uint8 PduR_ConfigIdType;
typedef uint8 PduR_InitializedIdxOfDestApplicationManagerRomType;
typedef uint8 PduR_InitializedPartitionIdxOfDestApplicationManagerRomType;
typedef uint8 PduR_RmGDestRomEndIdxOfDestApplicationManagerRomType;
typedef uint8 PduR_RmGDestRomStartIdxOfDestApplicationManagerRomType;
typedef boolean PduR_RmGDestRomUsedOfDestApplicationManagerRomType;
typedef uint8 PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType;
typedef uint8 PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRomType;
typedef uint32 PduR_SpinlockRetryCounterOfGeneralPropertiesRomType;
typedef boolean PduR_InitializedRamType;
typedef uint8 PduR_InterfaceFifoQueueMetaDataArrayRamType;
typedef uint8 PduR_ExclusiveAreaRomIdxOfLockRomType;
typedef boolean PduR_ExclusiveAreaRomUsedOfLockRomType;
typedef unsigned int PduR_CancelReceiveSupportedOfMmRomType;
typedef unsigned int PduR_ChangeParameterSupportedOfMmRomType;
typedef unsigned int PduR_IfCancelTransmitSupportedOfMmRomType;
typedef unsigned int PduR_LoIfOfMmRomType;
typedef unsigned int PduR_LoTpOfMmRomType;
typedef unsigned int PduR_TpCancelTransmitSupportedOfMmRomType;
typedef unsigned int PduR_UpIfOfMmRomType;
typedef unsigned int PduR_UpTpOfMmRomType;
typedef uint8 PduR_PCPartitionConfigIdxOfPartitionIdentifiersType;
typedef boolean PduR_BswMPduRPreTransmitCallbackOfRmDestRomType;
typedef uint8 PduR_PduLengthHandlingStrategyOfRmDestRomType;
typedef boolean PduR_QueuedOfRmDestRomType;
typedef uint8 PduR_RmDestRpgRomIdxOfRmDestRomType;
typedef uint8 PduR_RmDestRpgRomPartitionIdxOfRmDestRomType;
typedef boolean PduR_RmDestRpgRomUsedOfRmDestRomType;
typedef uint8 PduR_RmGDestRomIdxOfRmDestRomType;
typedef uint8 PduR_RmSrcRomIdxOfRmDestRomType;
typedef uint8 PduR_RoutingTypeOfRmDestRomType;
typedef uint16 PduR_EnabledCntOfRmDestRpgRamType;
typedef uint8 PduR_InitialEnabledCntOfRmDestRpgRomType;
typedef uint8 PduR_RmDestRomIdxOfRmDestRpgRomType;
typedef boolean PduR_RmDestRomUsedOfRmDestRpgRomType;
typedef uint8 PduR_RmDestRpgRomIndType;
typedef uint8 PduR_RmDestRomIdxOfRmGDestNto1InfoRamType;
typedef boolean PduR_TransmissionActiveOfRmGDestNto1InfoRamType;
typedef boolean PduR_ExpectTxConfirmationOfRmGDestNto1InfoRomType;
typedef uint8 PduR_DestApplicationManagerRomIdxOfRmGDestRomType;
typedef uint8 PduR_DestHndOfRmGDestRomType;
typedef uint8 PduR_DirectionOfRmGDestRomType;
typedef uint8 PduR_LockRomIdxOfRmGDestRomType;
typedef uint8 PduR_MetaDataLengthOfRmGDestRomType;
typedef uint8 PduR_MmRomIdxOfRmGDestRomType;
typedef uint8 PduR_PduLengthOfRmGDestRomType;
typedef uint8 PduR_PduRDestPduProcessingOfRmGDestRomType;
typedef uint8 PduR_RmDestRomIdxOfRmGDestRomType;
typedef uint8 PduR_RmGDestNto1InfoRomIdxOfRmGDestRomType;
typedef uint8 PduR_RmGDestNto1InfoRomPartitionIdxOfRmGDestRomType;
typedef boolean PduR_RmGDestNto1InfoRomUsedOfRmGDestRomType;
typedef uint8 PduR_TxIf2UpIdxOfRmGDestRomType;
typedef uint8 PduR_DestApplicationManagerRomIdxOfRmSrcRomType;
typedef uint8 PduR_DirectionOfRmSrcRomType;
typedef boolean PduR_IfOfRmSrcRomType;
typedef uint8 PduR_LockRomIdxOfRmSrcRomType;
typedef uint8 PduR_MmRomIdxOfRmSrcRomType;
typedef uint8 PduR_RmDestRomEndIdxOfRmSrcRomType;
typedef uint8 PduR_RmDestRomLengthOfRmSrcRomType;
typedef uint8 PduR_RmDestRomStartIdxOfRmSrcRomType;
typedef uint8 PduR_SrcHndOfRmSrcRomType;
typedef boolean PduR_TpOfRmSrcRomType;
typedef boolean PduR_TriggerTransmitSupportedOfRmSrcRomType;
typedef boolean PduR_TxConfirmationSupportedOfRmSrcRomType;
typedef boolean PduR_InvalidHndOfRpgExtIdRomType;
typedef uint8 PduR_RpgRomIdxOfRpgExtIdRomType;
typedef uint8 PduR_RpgRomPartitionIdxOfRpgExtIdRomType;
typedef boolean PduR_RpgRomUsedOfRpgExtIdRomType;
typedef boolean PduR_EnabledOfRpgRamType;
typedef boolean PduR_EnabledAtInitOfRpgRomType;
typedef uint8 PduR_RmDestRpgRomIndEndIdxOfRpgRomType;
typedef uint8 PduR_RmDestRpgRomIndStartIdxOfRpgRomType;
typedef boolean PduR_RmDestRpgRomIndUsedOfRpgRomType;
typedef boolean PduR_BswMPduRRxIndicationCallbackOfRxIf2DestType;
typedef boolean PduR_InvalidHndOfRxIf2DestType;
typedef uint8 PduR_RmSrcRomIdxOfRxIf2DestType;
typedef boolean PduR_BswMPduRTpRxIndicationCallbackOfRxTp2DestType;
typedef boolean PduR_BswMPduRTpStartOfReceptionCallbackOfRxTp2DestType;
typedef boolean PduR_InvalidHndOfRxTp2DestType;
typedef uint8 PduR_RmSrcRomIdxOfRxTp2DestType;
typedef boolean PduR_InvalidHndOfRxTp2SrcType;
typedef uint8 PduR_RmDestRomIdxOfRxTp2SrcType;
typedef uint8 PduR_SingleBufferMetaDataArrayRamType;
typedef uint8 PduR_DestApplicationManagerRomDestinationIdxOfSrcApplicationRomType;
typedef uint8 PduR_DestApplicationManagerRomSourceIdxOfSrcApplicationRomType;
typedef boolean PduR_BswMPduRTransmitCallbackOfTx2LoType;
typedef boolean PduR_CancelTransmitUsedOfTx2LoType;
typedef boolean PduR_InvalidHndOfTx2LoType;
typedef uint8 PduR_RmSrcRomIdxOfTx2LoType;
typedef boolean PduR_BswMPduRTxConfirmationCallbackOfTxIf2UpType;
typedef boolean PduR_InvalidHndOfTxIf2UpType;
typedef uint8 PduR_RmGDestRomIdxOfTxIf2UpType;
typedef boolean PduR_TxConfirmationUsedOfTxIf2UpType;
typedef boolean PduR_BswMPduRTpTxConfirmationCallbackOfTxTp2SrcType;
typedef boolean PduR_InvalidHndOfTxTp2SrcType;
typedef uint8 PduR_RmGDestRomIdxOfTxTp2SrcType;
typedef uint8 PduR_MemIdxType;
#if(PDUR_MULTICORE == STD_ON)
typedef ApplicationType PduR_PartitionSNVOfPartitionIdentifiersType;
#else
typedef uint32 PduR_PartitionSNVOfPartitionIdentifiersType;
#endif

typedef struct
{
  uint8*        dataPtr;
  PduLengthType dataLength;
} PduType;

typedef struct sPduR_ApplicationId2DestApplicationManagerRomType
{
  uint8 PduR_ApplicationId2DestApplicationManagerRomNeverUsed;
} PduR_ApplicationId2DestApplicationManagerRomType;

typedef struct sPduR_DestApplicationManagerRomType
{
  uint8 PduR_DestApplicationManagerRomNeverUsed;
} PduR_DestApplicationManagerRomType;

typedef struct sPduR_ExclusiveAreaRomType
{
  PduR_LockFunctionType LockOfExclusiveAreaRom;
  PduR_LockFunctionType UnlockOfExclusiveAreaRom;
} PduR_ExclusiveAreaRomType;

typedef struct sPduR_GeneralPropertiesRomType
{
  uint8 PduR_GeneralPropertiesRomNeverUsed;
} PduR_GeneralPropertiesRomType;

typedef struct sPduR_LockRomType
{
  uint8 PduR_LockRomNeverUsed;
} PduR_LockRomType;

typedef struct sPduR_MmRomType
{
  PduR_LoIfOfMmRomType LoIfOfMmRom :1;
  PduR_LoTpOfMmRomType LoTpOfMmRom :1;
  PduR_UpIfOfMmRomType UpIfOfMmRom :1;
  PduR_UpTpOfMmRomType UpTpOfMmRom :1;
  PduR_CancelReceiveFctPtrType LoTpCancelReceiveFctPtrOfMmRom;
  PduR_CancelTransmitFctPtrType LoIfCancelTransmitFctPtrOfMmRom;
  PduR_CancelTransmitFctPtrType LoTpCancelTransmitFctPtrOfMmRom;
  PduR_ChangeParameterFctPtrType LoTpChangeParameterFctPtrOfMmRom;
  PduR_CopyRxDataFctPtrType UpTpCopyRxDataFctPtrOfMmRom;
  PduR_CopyTxDataFctPtrType UpTpCopyTxDataFctPtrOfMmRom;
  PduR_IfRxIndicationType UpIfRxIndicationFctPtrOfMmRom;
  PduR_IfTxConfirmationFctPtrType UpIfTxConfirmationFctPtrOfMmRom;
  PduR_StartOfReceptionFctPtrType UpTpStartOfReceptionFctPtrOfMmRom;
  PduR_TpRxIndicationFctPtrType UpTpTpRxIndicationFctPtrOfMmRom;
  PduR_TpTxConfirmationFctPtrType UpTpTpTxConfirmationFctPtrOfMmRom;
  PduR_TransmitFctPtrType LoIfTransmitFctPtrOfMmRom;
  PduR_TransmitFctPtrType LoTpTransmitFctPtrOfMmRom;
  PduR_TriggerTransmitFctPtrType UpIfTriggerTransmitFctPtrOfMmRom;
} PduR_MmRomType;

typedef struct sPduR_PartitionIdentifiersType
{
  PduR_PartitionSNVOfPartitionIdentifiersType PartitionSNVOfPartitionIdentifiers;
} PduR_PartitionIdentifiersType;

typedef struct sPduR_RmDestRomType
{
  PduR_PduLengthHandlingStrategyOfRmDestRomType PduLengthHandlingStrategyOfRmDestRom;
  PduR_RmGDestRomIdxOfRmDestRomType RmGDestRomIdxOfRmDestRom;
  PduR_RmSrcRomIdxOfRmDestRomType RmSrcRomIdxOfRmDestRom;
  PduR_RoutingTypeOfRmDestRomType RoutingTypeOfRmDestRom;
} PduR_RmDestRomType;

typedef struct sPduR_RmDestRpgRamType
{
  uint8 PduR_RmDestRpgRamNeverUsed;
} PduR_RmDestRpgRamType;

typedef struct sPduR_RmDestRpgRomType
{
  uint8 PduR_RmDestRpgRomNeverUsed;
} PduR_RmDestRpgRomType;

typedef struct sPduR_RmGDestNto1InfoRamType
{
  uint8 PduR_RmGDestNto1InfoRamNeverUsed;
} PduR_RmGDestNto1InfoRamType;

typedef struct sPduR_RmGDestNto1InfoRomType
{
  uint8 PduR_RmGDestNto1InfoRomNeverUsed;
} PduR_RmGDestNto1InfoRomType;

typedef struct sPduR_RmGDestRomType
{
  PduR_DestHndOfRmGDestRomType DestHndOfRmGDestRom;
  PduR_DirectionOfRmGDestRomType DirectionOfRmGDestRom;
  PduR_MmRomIdxOfRmGDestRomType MmRomIdxOfRmGDestRom;
  PduR_PduLengthOfRmGDestRomType PduLengthOfRmGDestRom;
  PduR_RmDestRomIdxOfRmGDestRomType RmDestRomIdxOfRmGDestRom;
  PduR_TxIf2UpIdxOfRmGDestRomType TxIf2UpIdxOfRmGDestRom;
} PduR_RmGDestRomType;

typedef struct sPduR_RmSrcRomType
{
  PduR_TpOfRmSrcRomType TpOfRmSrcRom;
  PduR_DirectionOfRmSrcRomType DirectionOfRmSrcRom;
  PduR_MmRomIdxOfRmSrcRomType MmRomIdxOfRmSrcRom;
  PduR_RmDestRomStartIdxOfRmSrcRomType RmDestRomStartIdxOfRmSrcRom;
  PduR_SrcHndOfRmSrcRomType SrcHndOfRmSrcRom;
} PduR_RmSrcRomType;

typedef struct sPduR_RpgExtIdRomType
{
  uint8 PduR_RpgExtIdRomNeverUsed;
} PduR_RpgExtIdRomType;

typedef struct sPduR_RpgRamType
{
  uint8 PduR_RpgRamNeverUsed;
} PduR_RpgRamType;

typedef struct sPduR_RpgRomType
{
  uint8 PduR_RpgRomNeverUsed;
} PduR_RpgRomType;

typedef struct sPduR_RxIf2DestType
{
  uint8 PduR_RxIf2DestNeverUsed;
} PduR_RxIf2DestType;

typedef struct sPduR_RxTp2DestType
{
  uint8 PduR_RxTp2DestNeverUsed;
} PduR_RxTp2DestType;

typedef struct sPduR_RxTp2SrcType
{
  PduR_RmDestRomIdxOfRxTp2SrcType RmDestRomIdxOfRxTp2Src;
} PduR_RxTp2SrcType;

typedef struct sPduR_SrcApplicationRomType
{
  uint8 PduR_SrcApplicationRomNeverUsed;
} PduR_SrcApplicationRomType;

typedef struct sPduR_Tx2LoType
{
  uint8 PduR_Tx2LoNeverUsed;
} PduR_Tx2LoType;

typedef struct sPduR_TxIf2UpType
{
  uint8 PduR_TxIf2UpNeverUsed;
} PduR_TxIf2UpType;

typedef struct sPduR_TxTp2SrcType
{
  uint8 PduR_TxTp2SrcNeverUsed;
} PduR_TxTp2SrcType;

typedef P2CONST(PduR_ApplicationId2DestApplicationManagerRomType, TYPEDEF, PDUR_CONST) PduR_ApplicationId2DestApplicationManagerRomPtrType;
typedef P2VAR(PduR_BmTxBufferMetaDataArrayRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_BmTxBufferMetaDataArrayRamPtrType;
typedef P2CONST(PduR_DestApplicationManagerRomType, TYPEDEF, PDUR_CONST) PduR_DestApplicationManagerRomPtrType;
typedef P2CONST(PduR_ExclusiveAreaRomType, TYPEDEF, PDUR_CONST) PduR_ExclusiveAreaRomPtrType;
typedef P2CONST(PduR_GeneralPropertiesRomType, TYPEDEF, PDUR_CONST) PduR_GeneralPropertiesRomPtrType;
typedef P2VAR(PduR_InitializedRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_InitializedRamPtrType;
typedef P2VAR(PduR_InterfaceFifoQueueMetaDataArrayRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_InterfaceFifoQueueMetaDataArrayRamPtrType;
typedef P2CONST(PduR_LockRomType, TYPEDEF, PDUR_CONST) PduR_LockRomPtrType;
typedef P2CONST(PduR_MmRomType, TYPEDEF, PDUR_CONST) PduR_MmRomPtrType;
typedef P2CONST(PduR_PartitionIdentifiersType, TYPEDEF, PDUR_CONST) PduR_PartitionIdentifiersPtrType;
typedef P2CONST(PduR_RmDestRomType, TYPEDEF, PDUR_CONST) PduR_RmDestRomPtrType;
typedef P2VAR(PduR_RmDestRpgRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_RmDestRpgRamPtrType;
typedef P2CONST(PduR_RmDestRpgRomType, TYPEDEF, PDUR_CONST) PduR_RmDestRpgRomPtrType;
typedef P2CONST(PduR_RmDestRpgRomIndType, TYPEDEF, PDUR_CONST) PduR_RmDestRpgRomIndPtrType;
typedef P2VAR(PduR_RmGDestNto1InfoRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_RmGDestNto1InfoRamPtrType;
typedef P2CONST(PduR_RmGDestNto1InfoRomType, TYPEDEF, PDUR_CONST) PduR_RmGDestNto1InfoRomPtrType;
typedef P2CONST(PduR_RmGDestRomType, TYPEDEF, PDUR_CONST) PduR_RmGDestRomPtrType;
typedef P2CONST(PduR_RmSrcRomType, TYPEDEF, PDUR_CONST) PduR_RmSrcRomPtrType;
typedef P2CONST(PduR_RpgExtIdRomType, TYPEDEF, PDUR_CONST) PduR_RpgExtIdRomPtrType;
typedef P2VAR(PduR_RpgRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_RpgRamPtrType;
typedef P2CONST(PduR_RpgRomType, TYPEDEF, PDUR_CONST) PduR_RpgRomPtrType;
typedef P2CONST(PduR_RxIf2DestType, TYPEDEF, PDUR_CONST) PduR_RxIf2DestPtrType;
typedef P2CONST(PduR_RxTp2DestType, TYPEDEF, PDUR_CONST) PduR_RxTp2DestPtrType;
typedef P2CONST(PduR_RxTp2SrcType, TYPEDEF, PDUR_CONST) PduR_RxTp2SrcPtrType;
typedef P2VAR(PduR_SingleBufferMetaDataArrayRamType, TYPEDEF, PDUR_VAR_NO_INIT) PduR_SingleBufferMetaDataArrayRamPtrType;
typedef P2CONST(PduR_SrcApplicationRomType, TYPEDEF, PDUR_CONST) PduR_SrcApplicationRomPtrType;
typedef P2CONST(PduR_Tx2LoType, TYPEDEF, PDUR_CONST) PduR_Tx2LoPtrType;
typedef P2CONST(PduR_TxIf2UpType, TYPEDEF, PDUR_CONST) PduR_TxIf2UpPtrType;
typedef P2CONST(PduR_TxTp2SrcType, TYPEDEF, PDUR_CONST) PduR_TxTp2SrcPtrType;

typedef struct sPduR_PCPartitionConfigType
{
  uint8 PduR_PCPartitionConfigNeverUsed;
} PduR_PCPartitionConfigType;

typedef P2CONST(PduR_PCPartitionConfigType, TYPEDEF, PDUR_CONST) PduR_PCPartitionConfigPtrType;

typedef struct sPduR_PCConfigType
{
  uint8 PduR_PCConfigNeverUsed;
} PduR_PCConfigType;

typedef PduR_PCConfigType PduR_PBConfigType;

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[[!"num:i($numMods)"!]];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_PartitionIdentifiersType, PDUR_CONST) PduR_PartitionIdentifiers[1];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[[!"num:i($numPaths)"!]];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[[!"num:i($numPaths)"!]];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[[!"num:i($numPaths)"!]];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

[!IF "$numTpRx > 0"!][!//
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
extern CONST(PduR_RxTp2SrcType, PDUR_CONST) PduR_RxTp2Src[[!"num:i($numTpRx)"!]];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
[!ENDIF!][!//

#define PDUR_START_SEC_VAR_NO_INIT_8
#include "PduR_MemMap.h"
extern VAR(PduR_InitializedRamType, PDUR_VAR_NO_INIT) PduR_InitializedRam[1];
#define PDUR_STOP_SEC_VAR_NO_INIT_8
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
#if(PDUR_USE_INIT_POINTER == STD_ON)
extern P2CONST(PduR_PBConfigType, PDUR_VAR_CLEARED, PDUR_PBCFG) PduR_ConfigDataPtr;
#endif
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"
extern VAR(boolean, PDUR_VAR_NO_INIT) PduR_PreInitialized;
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"

/* CSL Inline Accessor Prototypes & Definitions */
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfApplicationId2DestApplicationManagerRomType, PDUR_CODE) PduR_GetSizeOfApplicationId2DestApplicationManagerRom(void)
{
  return (PduR_SizeOfApplicationId2DestApplicationManagerRomType) PduR_GetSizeOfApplicationId2DestApplicationManagerRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfBmTxBufferMetaDataArrayRamType, PDUR_CODE) PduR_GetSizeOfBmTxBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfBmTxBufferMetaDataArrayRamType) PduR_GetSizeOfBmTxBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetSizeOfDestApplicationManagerRom(void)
{
  return (PduR_SizeOfDestApplicationManagerRomType) PduR_GetSizeOfDestApplicationManagerRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfExclusiveAreaRomType, PDUR_CODE) PduR_GetSizeOfExclusiveAreaRom(void)
{
  return (PduR_SizeOfExclusiveAreaRomType) PduR_GetSizeOfExclusiveAreaRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfGeneralPropertiesRomType, PDUR_CODE) PduR_GetSizeOfGeneralPropertiesRom(void)
{
  return (PduR_SizeOfGeneralPropertiesRomType) PduR_GetSizeOfGeneralPropertiesRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfInitializedRamType, PDUR_CODE) PduR_GetSizeOfInitializedRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfInitializedRamType) PduR_GetSizeOfInitializedRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfInterfaceFifoQueueMetaDataArrayRamType, PDUR_CODE) PduR_GetSizeOfInterfaceFifoQueueMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfInterfaceFifoQueueMetaDataArrayRamType) PduR_GetSizeOfInterfaceFifoQueueMetaDataArrayRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfLockRomType, PDUR_CODE) PduR_GetSizeOfLockRom(void)
{
  return (PduR_SizeOfLockRomType) PduR_GetSizeOfLockRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfMmRomType, PDUR_CODE) PduR_GetSizeOfMmRom(void)
{
  return (PduR_SizeOfMmRomType) PduR_GetSizeOfMmRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfPartitionIdentifiersType, PDUR_CODE) PduR_GetSizeOfPartitionIdentifiers(void)
{
  return (PduR_SizeOfPartitionIdentifiersType) PduR_GetSizeOfPartitionIdentifiersOfPCConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmDestRomType, PDUR_CODE) PduR_GetSizeOfRmDestRom(void)
{
  return (PduR_SizeOfRmDestRomType) PduR_GetSizeOfRmDestRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmDestRpgRamType, PDUR_CODE) PduR_GetSizeOfRmDestRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRmDestRpgRamType) PduR_GetSizeOfRmDestRpgRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmDestRpgRomType, PDUR_CODE) PduR_GetSizeOfRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRmDestRpgRomType) PduR_GetSizeOfRmDestRpgRomOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmDestRpgRomIndType, PDUR_CODE) PduR_GetSizeOfRmDestRpgRomInd(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRmDestRpgRomIndType) PduR_GetSizeOfRmDestRpgRomIndOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmGDestNto1InfoRamType, PDUR_CODE) PduR_GetSizeOfRmGDestNto1InfoRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRmGDestNto1InfoRamType) PduR_GetSizeOfRmGDestNto1InfoRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmGDestNto1InfoRomType, PDUR_CODE) PduR_GetSizeOfRmGDestNto1InfoRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRmGDestNto1InfoRomType) PduR_GetSizeOfRmGDestNto1InfoRomOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmGDestRomType, PDUR_CODE) PduR_GetSizeOfRmGDestRom(void)
{
  return (PduR_SizeOfRmGDestRomType) PduR_GetSizeOfRmGDestRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRmSrcRomType, PDUR_CODE) PduR_GetSizeOfRmSrcRom(void)
{
  return (PduR_SizeOfRmSrcRomType) PduR_GetSizeOfRmSrcRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRpgExtIdRomType, PDUR_CODE) PduR_GetSizeOfRpgExtIdRom(void)
{
  return (PduR_SizeOfRpgExtIdRomType) PduR_GetSizeOfRpgExtIdRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRpgRamType, PDUR_CODE) PduR_GetSizeOfRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRpgRamType) PduR_GetSizeOfRpgRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRpgRomType, PDUR_CODE) PduR_GetSizeOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfRpgRomType) PduR_GetSizeOfRpgRomOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRxIf2DestType, PDUR_CODE) PduR_GetSizeOfRxIf2Dest(void)
{
  return (PduR_SizeOfRxIf2DestType) PduR_GetSizeOfRxIf2DestOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRxTp2DestType, PDUR_CODE) PduR_GetSizeOfRxTp2Dest(void)
{
  return (PduR_SizeOfRxTp2DestType) PduR_GetSizeOfRxTp2DestOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfRxTp2SrcType, PDUR_CODE) PduR_GetSizeOfRxTp2Src(void)
{
  return (PduR_SizeOfRxTp2SrcType) PduR_GetSizeOfRxTp2SrcOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfSingleBufferMetaDataArrayRamType, PDUR_CODE) PduR_GetSizeOfSingleBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SizeOfSingleBufferMetaDataArrayRamType) PduR_GetSizeOfSingleBufferMetaDataArrayRamOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfSrcApplicationRomType, PDUR_CODE) PduR_GetSizeOfSrcApplicationRom(void)
{
  return (PduR_SizeOfSrcApplicationRomType) PduR_GetSizeOfSrcApplicationRomOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfTx2LoType, PDUR_CODE) PduR_GetSizeOfTx2Lo(void)
{
  return (PduR_SizeOfTx2LoType) PduR_GetSizeOfTx2LoOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfTxIf2UpType, PDUR_CODE) PduR_GetSizeOfTxIf2Up(void)
{
  return (PduR_SizeOfTxIf2UpType) PduR_GetSizeOfTxIf2UpOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_SizeOfTxTp2SrcType, PDUR_CODE) PduR_GetSizeOfTxTp2Src(void)
{
  return (PduR_SizeOfTxTp2SrcType) PduR_GetSizeOfTxTp2SrcOfPCPartitionConfig();
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRomType, PDUR_CODE) PduR_GetDestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRom(PduR_ApplicationId2DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomUsedOfApplicationId2DestApplicationManagerRomType, PDUR_CODE) PduR_IsDestApplicationManagerRomUsedOfApplicationId2DestApplicationManagerRom(PduR_ApplicationId2DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomUsedOfApplicationId2DestApplicationManagerRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfApplicationId2DestApplicationManagerRomType, PDUR_CODE) PduR_IsInvalidHndOfApplicationId2DestApplicationManagerRom(PduR_ApplicationId2DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfApplicationId2DestApplicationManagerRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_PartitionConfigIdxOfApplicationId2DestApplicationManagerRomType, PDUR_CODE) PduR_GetPartitionConfigIdxOfApplicationId2DestApplicationManagerRom(PduR_ApplicationId2DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PartitionConfigIdxOfApplicationId2DestApplicationManagerRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferMetaDataArrayRamType, PDUR_CODE) PduR_GetBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_BmTxBufferMetaDataArrayRamType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_LockFunctionType, PDUR_CODE) PduR_GetLockOfExclusiveAreaRom(PduR_ExclusiveAreaRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LockFunctionType) (PduR_GetExclusiveAreaRomOfPCPartitionConfig()[(Index)].LockOfExclusiveAreaRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_LockFunctionType, PDUR_CODE) PduR_GetUnlockOfExclusiveAreaRom(PduR_ExclusiveAreaRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LockFunctionType) (PduR_GetExclusiveAreaRomOfPCPartitionConfig()[(Index)].UnlockOfExclusiveAreaRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_InitializedRamType, PDUR_CODE) PduR_IsInitializedRam(PduR_InitializedRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_InitializedRamType) ((PduR_GetInitializedRamOfPCPartitionConfig(partitionIndex)[(Index)]) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueMetaDataArrayRamType, PDUR_CODE) PduR_GetInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_InterfaceFifoQueueMetaDataArrayRamType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_CancelTransmitFctPtrType, PDUR_CODE) PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CancelTransmitFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoIfCancelTransmitFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_LoIfOfMmRomType, PDUR_CODE) PduR_IsLoIfOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LoIfOfMmRomType) ((PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoIfOfMmRom) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_TransmitFctPtrType, PDUR_CODE) PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TransmitFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoIfTransmitFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_CancelReceiveFctPtrType, PDUR_CODE) PduR_GetLoTpCancelReceiveFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CancelReceiveFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoTpCancelReceiveFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_CancelTransmitFctPtrType, PDUR_CODE) PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CancelTransmitFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoTpCancelTransmitFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_ChangeParameterFctPtrType, PDUR_CODE) PduR_GetLoTpChangeParameterFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_ChangeParameterFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoTpChangeParameterFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_LoTpOfMmRomType, PDUR_CODE) PduR_IsLoTpOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LoTpOfMmRomType) ((PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoTpOfMmRom) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_TransmitFctPtrType, PDUR_CODE) PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TransmitFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoTpTransmitFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_UpIfOfMmRomType, PDUR_CODE) PduR_IsUpIfOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_UpIfOfMmRomType) ((PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfOfMmRom) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_IfRxIndicationType, PDUR_CODE) PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_IfRxIndicationType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfRxIndicationFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_TriggerTransmitFctPtrType, PDUR_CODE) PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TriggerTransmitFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfTriggerTransmitFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_IfTxConfirmationFctPtrType, PDUR_CODE) PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_IfTxConfirmationFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfTxConfirmationFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_CopyRxDataFctPtrType, PDUR_CODE) PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CopyRxDataFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpCopyRxDataFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_CopyTxDataFctPtrType, PDUR_CODE) PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CopyTxDataFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpCopyTxDataFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_UpTpOfMmRomType, PDUR_CODE) PduR_IsUpTpOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_UpTpOfMmRomType) ((PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpOfMmRom) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_StartOfReceptionFctPtrType, PDUR_CODE) PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_StartOfReceptionFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpStartOfReceptionFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_TpRxIndicationFctPtrType, PDUR_CODE) PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TpRxIndicationFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpTpRxIndicationFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_TpTxConfirmationFctPtrType, PDUR_CODE) PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TpTxConfirmationFctPtrType) (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpTpTpTxConfirmationFctPtrOfMmRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_PartitionSNVOfPartitionIdentifiersType, PDUR_CODE) PduR_GetPartitionSNVOfPartitionIdentifiers(PduR_PartitionIdentifiersIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PartitionSNVOfPartitionIdentifiersType) (PduR_GetPartitionIdentifiersOfPCConfig()[(Index)].PartitionSNVOfPartitionIdentifiers);
}
PDUR_LOCAL_INLINE FUNC(PduR_PduLengthHandlingStrategyOfRmDestRomType, PDUR_CODE) PduR_GetPduLengthHandlingStrategyOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PduLengthHandlingStrategyOfRmDestRomType) (PduR_GetRmDestRomOfPCPartitionConfig()[(Index)].PduLengthHandlingStrategyOfRmDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomIdxOfRmDestRomType, PDUR_CODE) PduR_GetRmDestRpgRomIdxOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRpgRomIdxOfRmDestRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomPartitionIdxOfRmDestRomType, PDUR_CODE) PduR_GetRmDestRpgRomPartitionIdxOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRpgRomPartitionIdxOfRmDestRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomUsedOfRmDestRomType, PDUR_CODE) PduR_IsRmDestRpgRomUsedOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRpgRomUsedOfRmDestRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomIdxOfRmDestRomType, PDUR_CODE) PduR_GetRmGDestRomIdxOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomIdxOfRmDestRomType) (PduR_GetRmDestRomOfPCPartitionConfig()[(Index)].RmGDestRomIdxOfRmDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfRmDestRomType, PDUR_CODE) PduR_GetRmSrcRomIdxOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmSrcRomIdxOfRmDestRomType) (PduR_GetRmDestRomOfPCPartitionConfig()[(Index)].RmSrcRomIdxOfRmDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RoutingTypeOfRmDestRomType, PDUR_CODE) PduR_GetRoutingTypeOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RoutingTypeOfRmDestRomType) (PduR_GetRmDestRomOfPCPartitionConfig()[(Index)].RoutingTypeOfRmDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_EnabledCntOfRmDestRpgRamType, PDUR_CODE) PduR_GetEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_EnabledCntOfRmDestRpgRamType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_InitialEnabledCntOfRmDestRpgRomType, PDUR_CODE) PduR_GetInitialEnabledCntOfRmDestRpgRom(PduR_RmDestRpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_InitialEnabledCntOfRmDestRpgRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomIdxOfRmDestRpgRomType, PDUR_CODE) PduR_GetRmDestRomIdxOfRmDestRpgRom(PduR_RmDestRpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRomIdxOfRmDestRpgRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomUsedOfRmDestRpgRomType, PDUR_CODE) PduR_IsRmDestRomUsedOfRmDestRpgRom(PduR_RmDestRpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRomUsedOfRmDestRpgRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomIndType, PDUR_CODE) PduR_GetRmDestRpgRomInd(PduR_RmDestRpgRomIndIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRpgRomIndType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomIdxOfRmGDestNto1InfoRamType, PDUR_CODE) PduR_GetRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_TransmissionActiveOfRmGDestNto1InfoRamType, PDUR_CODE) PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_TransmissionActiveOfRmGDestNto1InfoRamType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_ExpectTxConfirmationOfRmGDestNto1InfoRomType, PDUR_CODE) PduR_IsExpectTxConfirmationOfRmGDestNto1InfoRom(PduR_RmGDestNto1InfoRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_ExpectTxConfirmationOfRmGDestNto1InfoRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_DestHndOfRmGDestRomType, PDUR_CODE) PduR_GetDestHndOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestHndOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].DestHndOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_DirectionOfRmGDestRomType, PDUR_CODE) PduR_GetDirectionOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DirectionOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].DirectionOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_MmRomIdxOfRmGDestRomType, PDUR_CODE) PduR_GetMmRomIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_MmRomIdxOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].MmRomIdxOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_PduLengthOfRmGDestRomType, PDUR_CODE) PduR_GetPduLengthOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PduLengthOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].PduLengthOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomIdxOfRmGDestRomType, PDUR_CODE) PduR_GetRmDestRomIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomIdxOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].RmDestRomIdxOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestNto1InfoRomIdxOfRmGDestRomType, PDUR_CODE) PduR_GetRmGDestNto1InfoRomIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestNto1InfoRomIdxOfRmGDestRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestNto1InfoRomPartitionIdxOfRmGDestRomType, PDUR_CODE) PduR_GetRmGDestNto1InfoRomPartitionIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestNto1InfoRomPartitionIdxOfRmGDestRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestNto1InfoRomUsedOfRmGDestRomType, PDUR_CODE) PduR_IsRmGDestNto1InfoRomUsedOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestNto1InfoRomUsedOfRmGDestRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_TxIf2UpIdxOfRmGDestRomType, PDUR_CODE) PduR_GetTxIf2UpIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TxIf2UpIdxOfRmGDestRomType) (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].TxIf2UpIdxOfRmGDestRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_DirectionOfRmSrcRomType, PDUR_CODE) PduR_GetDirectionOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DirectionOfRmSrcRomType) (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].DirectionOfRmSrcRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_MmRomIdxOfRmSrcRomType, PDUR_CODE) PduR_GetMmRomIdxOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_MmRomIdxOfRmSrcRomType) (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].MmRomIdxOfRmSrcRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomStartIdxOfRmSrcRomType, PDUR_CODE) PduR_GetRmDestRomStartIdxOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomStartIdxOfRmSrcRomType) (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].RmDestRomStartIdxOfRmSrcRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_SrcHndOfRmSrcRomType, PDUR_CODE) PduR_GetSrcHndOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_SrcHndOfRmSrcRomType) (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].SrcHndOfRmSrcRom);
}
PDUR_LOCAL_INLINE FUNC(PduR_TpOfRmSrcRomType, PDUR_CODE) PduR_IsTpOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TpOfRmSrcRomType) ((PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].TpOfRmSrcRom) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfRpgExtIdRomType, PDUR_CODE) PduR_IsInvalidHndOfRpgExtIdRom(PduR_RpgExtIdRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfRpgExtIdRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RpgRomIdxOfRpgExtIdRomType, PDUR_CODE) PduR_GetRpgRomIdxOfRpgExtIdRom(PduR_RpgExtIdRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RpgRomIdxOfRpgExtIdRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RpgRomPartitionIdxOfRpgExtIdRomType, PDUR_CODE) PduR_GetRpgRomPartitionIdxOfRpgExtIdRom(PduR_RpgExtIdRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RpgRomPartitionIdxOfRpgExtIdRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RpgRomUsedOfRpgExtIdRomType, PDUR_CODE) PduR_IsRpgRomUsedOfRpgExtIdRom(PduR_RpgExtIdRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RpgRomUsedOfRpgExtIdRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_EnabledOfRpgRamType, PDUR_CODE) PduR_IsEnabledOfRpgRam(PduR_RpgRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_EnabledOfRpgRamType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_EnabledAtInitOfRpgRomType, PDUR_CODE) PduR_IsEnabledAtInitOfRpgRom(PduR_RpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_EnabledAtInitOfRpgRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomIndEndIdxOfRpgRomType, PDUR_CODE) PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(PduR_RpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRpgRomIndEndIdxOfRpgRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomIndStartIdxOfRpgRomType, PDUR_CODE) PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(PduR_RpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRpgRomIndStartIdxOfRpgRomType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRpgRomIndUsedOfRpgRomType, PDUR_CODE) PduR_IsRmDestRpgRomIndUsedOfRpgRom(PduR_RpgRomIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_RmDestRpgRomIndUsedOfRpgRomType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfRxIf2DestType, PDUR_CODE) PduR_IsInvalidHndOfRxIf2Dest(PduR_RxIf2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfRxIf2DestType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfRxTp2DestType, PDUR_CODE) PduR_IsInvalidHndOfRxTp2Dest(PduR_RxTp2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfRxTp2DestType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfRxTp2SrcType, PDUR_CODE) PduR_IsInvalidHndOfRxTp2Src(PduR_RxTp2SrcIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfRxTp2SrcType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomIdxOfRxTp2SrcType, PDUR_CODE) PduR_GetRmDestRomIdxOfRxTp2Src(PduR_RxTp2SrcIterType Index)
{
[!IF "$numTpRx > 0"!][!//
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomIdxOfRxTp2SrcType) (PduR_GetRxTp2SrcOfPCPartitionConfig()[(Index)].RmDestRomIdxOfRxTp2Src);
[!ELSE!][!//
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomIdxOfRxTp2SrcType) (0u);
[!ENDIF!][!//
}
PDUR_LOCAL_INLINE FUNC(PduR_SingleBufferMetaDataArrayRamType, PDUR_CODE) PduR_GetSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SingleBufferMetaDataArrayRamType) (0u);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfTx2LoType, PDUR_CODE) PduR_IsInvalidHndOfTx2Lo(PduR_Tx2LoIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfTx2LoType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfTxIf2UpType, PDUR_CODE) PduR_IsInvalidHndOfTxIf2Up(PduR_TxIf2UpIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfTxIf2UpType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_InvalidHndOfTxTp2SrcType, PDUR_CODE) PduR_IsInvalidHndOfTxTp2Src(PduR_TxTp2SrcIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InvalidHndOfTxTp2SrcType) ((FALSE) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_ConfigIdType, PDUR_CODE) PduR_GetConfigId(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_ConfigIdType) PduR_GetConfigIdOfPCPartitionConfig(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(PduR_InitializedIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetInitializedIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InitializedIdxOfDestApplicationManagerRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_InitializedPartitionIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetInitializedPartitionIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_InitializedPartitionIdxOfDestApplicationManagerRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomEndIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetRmGDestRomEndIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomEndIdxOfDestApplicationManagerRomType) [!"num:i($numPaths)"!]u;
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomStartIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetRmGDestRomStartIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomStartIdxOfDestApplicationManagerRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomUsedOfDestApplicationManagerRomType, PDUR_CODE) PduR_IsRmGDestRomUsedOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomUsedOfDestApplicationManagerRomType) (((TRUE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetSrcApplicationRomEndIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType) 1u;
}
PDUR_LOCAL_INLINE FUNC(PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRomType, PDUR_CODE) PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(PduR_DestApplicationManagerRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_SpinlockRetryCounterOfGeneralPropertiesRomType, PDUR_CODE) PduR_GetSpinlockRetryCounterOfGeneralPropertiesRom(PduR_GeneralPropertiesRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_SpinlockRetryCounterOfGeneralPropertiesRomType) [!"num:i($spinLock)"!]u;
}
PDUR_LOCAL_INLINE FUNC(PduR_ExclusiveAreaRomIdxOfLockRomType, PDUR_CODE) PduR_GetExclusiveAreaRomIdxOfLockRom(PduR_LockRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_ExclusiveAreaRomIdxOfLockRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_ExclusiveAreaRomUsedOfLockRomType, PDUR_CODE) PduR_IsExclusiveAreaRomUsedOfLockRom(PduR_LockRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_ExclusiveAreaRomUsedOfLockRomType) (((TRUE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_CancelReceiveSupportedOfMmRomType, PDUR_CODE) PduR_IsCancelReceiveSupportedOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CancelReceiveSupportedOfMmRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_ChangeParameterSupportedOfMmRomType, PDUR_CODE) PduR_IsChangeParameterSupportedOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_ChangeParameterSupportedOfMmRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_IfCancelTransmitSupportedOfMmRomType, PDUR_CODE) PduR_IsIfCancelTransmitSupportedOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_IfCancelTransmitSupportedOfMmRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_TpCancelTransmitSupportedOfMmRomType, PDUR_CODE) PduR_IsTpCancelTransmitSupportedOfMmRom(PduR_MmRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TpCancelTransmitSupportedOfMmRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType, PDUR_CODE) PduR_GetPCPartitionConfigIdxOfPartitionIdentifiers(PduR_PartitionIdentifiersIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PCPartitionConfigIdxOfPartitionIdentifiersType) ((PduR_PCPartitionConfigIdxOfPartitionIdentifiersType)((Index)));
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRPreTransmitCallbackOfRmDestRomType, PDUR_CODE) PduR_IsBswMPduRPreTransmitCallbackOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRPreTransmitCallbackOfRmDestRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_QueuedOfRmDestRomType, PDUR_CODE) PduR_IsQueuedOfRmDestRom(PduR_RmDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_QueuedOfRmDestRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomIdxOfRmGDestRomType, PDUR_CODE) PduR_GetDestApplicationManagerRomIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomIdxOfRmGDestRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_LockRomIdxOfRmGDestRomType, PDUR_CODE) PduR_GetLockRomIdxOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LockRomIdxOfRmGDestRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_MetaDataLengthOfRmGDestRomType, PDUR_CODE) PduR_GetMetaDataLengthOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_MetaDataLengthOfRmGDestRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_PduRDestPduProcessingOfRmGDestRomType, PDUR_CODE) PduR_GetPduRDestPduProcessingOfRmGDestRom(PduR_RmGDestRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_PduRDestPduProcessingOfRmGDestRomType) PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM;
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomIdxOfRmSrcRomType, PDUR_CODE) PduR_GetDestApplicationManagerRomIdxOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomIdxOfRmSrcRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_IfOfRmSrcRomType, PDUR_CODE) PduR_IsIfOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_IfOfRmSrcRomType) (((!(PduR_IsTpOfRmSrcRom(Index)))) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_LockRomIdxOfRmSrcRomType, PDUR_CODE) PduR_GetLockRomIdxOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_LockRomIdxOfRmSrcRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomEndIdxOfRmSrcRomType, PDUR_CODE) PduR_GetRmDestRomEndIdxOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomEndIdxOfRmSrcRomType) ((PduR_RmDestRomEndIdxOfRmSrcRomType)((PduR_GetRmDestRomStartIdxOfRmSrcRom(Index) + 1u)));
}
PDUR_LOCAL_INLINE FUNC(PduR_RmDestRomLengthOfRmSrcRomType, PDUR_CODE) PduR_GetRmDestRomLengthOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmDestRomLengthOfRmSrcRomType) 1u;
}
PDUR_LOCAL_INLINE FUNC(PduR_TriggerTransmitSupportedOfRmSrcRomType, PDUR_CODE) PduR_IsTriggerTransmitSupportedOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TriggerTransmitSupportedOfRmSrcRomType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_TxConfirmationSupportedOfRmSrcRomType, PDUR_CODE) PduR_IsTxConfirmationSupportedOfRmSrcRom(PduR_RmSrcRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
[!IF "$comModIdx >= 0"!][!//
  return (PduR_TxConfirmationSupportedOfRmSrcRomType) (((boolean)(PduR_GetMmRomIdxOfRmSrcRom(Index) == [!"num:i($comModIdx)"!]u)) != FALSE);
[!ELSE!][!//
  return (PduR_TxConfirmationSupportedOfRmSrcRomType) (((FALSE)) != FALSE);
[!ENDIF!][!//
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRRxIndicationCallbackOfRxIf2DestType, PDUR_CODE) PduR_IsBswMPduRRxIndicationCallbackOfRxIf2Dest(PduR_RxIf2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRRxIndicationCallbackOfRxIf2DestType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfRxIf2DestType, PDUR_CODE) PduR_GetRmSrcRomIdxOfRxIf2Dest(PduR_RxIf2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmSrcRomIdxOfRxIf2DestType) ((PduR_RmSrcRomIdxOfRxIf2DestType)((Index)));
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRTpRxIndicationCallbackOfRxTp2DestType, PDUR_CODE) PduR_IsBswMPduRTpRxIndicationCallbackOfRxTp2Dest(PduR_RxTp2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRTpRxIndicationCallbackOfRxTp2DestType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRTpStartOfReceptionCallbackOfRxTp2DestType, PDUR_CODE) PduR_IsBswMPduRTpStartOfReceptionCallbackOfRxTp2Dest(PduR_RxTp2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRTpStartOfReceptionCallbackOfRxTp2DestType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfRxTp2DestType, PDUR_CODE) PduR_GetRmSrcRomIdxOfRxTp2Dest(PduR_RxTp2DestIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmSrcRomIdxOfRxTp2DestType) ((PduR_RmSrcRomIdxOfRxTp2DestType)((((PduR_RmSrcRomIdxOfRxTp2DestType)(Index)) + [!"num:i($numIfRx)"!]u)));
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomDestinationIdxOfSrcApplicationRomType, PDUR_CODE) PduR_GetDestApplicationManagerRomDestinationIdxOfSrcApplicationRom(PduR_SrcApplicationRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomDestinationIdxOfSrcApplicationRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_DestApplicationManagerRomSourceIdxOfSrcApplicationRomType, PDUR_CODE) PduR_GetDestApplicationManagerRomSourceIdxOfSrcApplicationRom(PduR_SrcApplicationRomIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_DestApplicationManagerRomSourceIdxOfSrcApplicationRomType) 0u;
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRTransmitCallbackOfTx2LoType, PDUR_CODE) PduR_IsBswMPduRTransmitCallbackOfTx2Lo(PduR_Tx2LoIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRTransmitCallbackOfTx2LoType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_CancelTransmitUsedOfTx2LoType, PDUR_CODE) PduR_IsCancelTransmitUsedOfTx2Lo(PduR_Tx2LoIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_CancelTransmitUsedOfTx2LoType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfTx2LoType, PDUR_CODE) PduR_GetRmSrcRomIdxOfTx2Lo(PduR_Tx2LoIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmSrcRomIdxOfTx2LoType) ((PduR_RmSrcRomIdxOfTx2LoType)((((PduR_RmSrcRomIdxOfTx2LoType)(Index)) + [!"num:i($numIfRx + $numTpRx)"!]u)));
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRTxConfirmationCallbackOfTxIf2UpType, PDUR_CODE) PduR_IsBswMPduRTxConfirmationCallbackOfTxIf2Up(PduR_TxIf2UpIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRTxConfirmationCallbackOfTxIf2UpType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomIdxOfTxIf2UpType, PDUR_CODE) PduR_GetRmGDestRomIdxOfTxIf2Up(PduR_TxIf2UpIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomIdxOfTxIf2UpType) ((PduR_RmGDestRomIdxOfTxIf2UpType)((((PduR_RmGDestRomIdxOfTxIf2UpType)(Index)) + [!"num:i($numTpTx)"!]u)));
}
PDUR_LOCAL_INLINE FUNC(PduR_TxConfirmationUsedOfTxIf2UpType, PDUR_CODE) PduR_IsTxConfirmationUsedOfTxIf2Up(PduR_TxIf2UpIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_TxConfirmationUsedOfTxIf2UpType) (((TRUE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_BswMPduRTpTxConfirmationCallbackOfTxTp2SrcType, PDUR_CODE) PduR_IsBswMPduRTpTxConfirmationCallbackOfTxTp2Src(PduR_TxTp2SrcIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_BswMPduRTpTxConfirmationCallbackOfTxTp2SrcType) (((FALSE)) != FALSE);
}
PDUR_LOCAL_INLINE FUNC(PduR_RmGDestRomIdxOfTxTp2SrcType, PDUR_CODE) PduR_GetRmGDestRomIdxOfTxTp2Src(PduR_TxTp2SrcIterType Index)
{
  PDUR_DUMMY_STATEMENT(Index);
  return (PduR_RmGDestRomIdxOfTxTp2SrcType) ((PduR_RmGDestRomIdxOfTxTp2SrcType)(Index));
}

PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_BmTxBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetInitializedRam(PduR_InitializedRamIterType Index, PduR_InitializedRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  PduR_GetInitializedRamOfPCPartitionConfig(partitionIndex)[(Index)] = (Value);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_InterfaceFifoQueueMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_EnabledCntOfRmDestRpgRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_RmDestRomIdxOfRmGDestNto1InfoRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_TransmissionActiveOfRmGDestNto1InfoRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetEnabledOfRpgRam(PduR_RpgRamIterType Index, PduR_EnabledOfRpgRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_SingleBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(Value);
  PDUR_DUMMY_STATEMENT(partitionIndex);
}

PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferMetaDataArrayRamPtrType, PDUR_CODE) PduR_GetAddrBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_BmTxBufferMetaDataArrayRamPtrType) (NULL_PTR);
}
PDUR_LOCAL_INLINE FUNC(PduR_InitializedRamPtrType, PDUR_CODE) PduR_GetAddrInitializedRam(PduR_InitializedRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_InitializedRamPtrType) (&(PduR_GetInitializedRamOfPCPartitionConfig(partitionIndex)[(Index)]));
}
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueMetaDataArrayRamPtrType, PDUR_CODE) PduR_GetAddrInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_InterfaceFifoQueueMetaDataArrayRamPtrType) (NULL_PTR);
}
PDUR_LOCAL_INLINE FUNC(PduR_SingleBufferMetaDataArrayRamPtrType, PDUR_CODE) PduR_GetAddrSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex)
{
  PDUR_DUMMY_STATEMENT(Index);
  PDUR_DUMMY_STATEMENT(partitionIndex);
  return (PduR_SingleBufferMetaDataArrayRamPtrType) (NULL_PTR);
}

PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasApplicationId2DestApplicationManagerRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomUsedOfApplicationId2DestApplicationManagerRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfApplicationId2DestApplicationManagerRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPartitionConfigIdxOfApplicationId2DestApplicationManagerRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBmTxBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasConfigId(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInitializedIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInitializedPartitionIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomEndIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomStartIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomUsedOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSrcApplicationRomEndIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSrcApplicationRomStartIdxOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasExclusiveAreaRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLockOfExclusiveAreaRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUnlockOfExclusiveAreaRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasGeneralPropertiesRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSpinlockRetryCounterOfGeneralPropertiesRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInitializedRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInterfaceFifoQueueMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLockRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasExclusiveAreaRomIdxOfLockRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasExclusiveAreaRomUsedOfLockRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasCancelReceiveSupportedOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasChangeParameterSupportedOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasIfCancelTransmitSupportedOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoIfCancelTransmitFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoIfOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoIfTransmitFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoTpCancelReceiveFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoTpCancelTransmitFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoTpChangeParameterFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoTpOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLoTpTransmitFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTpCancelTransmitSupportedOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpIfOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpIfRxIndicationFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpIfTriggerTransmitFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpIfTxConfirmationFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpCopyRxDataFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpCopyTxDataFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpStartOfReceptionFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpTpRxIndicationFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasUpTpTpTxConfirmationFctPtrOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPartitionIdentifiers(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPCPartitionConfigIdxOfPartitionIdentifiers(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPartitionSNVOfPartitionIdentifiers(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRPreTransmitCallbackOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPduLengthHandlingStrategyOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasQueuedOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomIdxOfRmDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomPartitionIdxOfRmDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomUsedOfRmDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomIdxOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRomIdxOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRoutingTypeOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasEnabledCntOfRmDestRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInitialEnabledCntOfRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomIdxOfRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomUsedOfRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomInd(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomIdxOfRmGDestNto1InfoRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTransmissionActiveOfRmGDestNto1InfoRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasExpectTxConfirmationOfRmGDestNto1InfoRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomIdxOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestHndOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDirectionOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLockRomIdxOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasMetaDataLengthOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasMmRomIdxOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPduLengthOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPduRDestPduProcessingOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomIdxOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRomIdxOfRmGDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRomPartitionIdxOfRmGDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRomUsedOfRmGDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxIf2UpIdxOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomIdxOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDirectionOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasIfOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLockRomIdxOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasMmRomIdxOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomEndIdxOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomLengthOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomStartIdxOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSrcHndOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTpOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTriggerTransmitSupportedOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxConfirmationSupportedOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgExtIdRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfRpgExtIdRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRomIdxOfRpgExtIdRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRomPartitionIdxOfRpgExtIdRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRomUsedOfRpgExtIdRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasEnabledOfRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasEnabledAtInitOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomIndEndIdxOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomIndStartIdxOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomIndUsedOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxIf2Dest(void) { return (boolean)([!IF "$numIfRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRRxIndicationCallbackOfRxIf2Dest(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfRxIf2Dest(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRomIdxOfRxIf2Dest(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxTp2Dest(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRTpRxIndicationCallbackOfRxTp2Dest(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRTpStartOfReceptionCallbackOfRxTp2Dest(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfRxTp2Dest(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRomIdxOfRxTp2Dest(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxTp2Src(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfRxTp2Src(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomIdxOfRxTp2Src(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSingleBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfApplicationId2DestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfBmTxBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfDestApplicationManagerRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfExclusiveAreaRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfGeneralPropertiesRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfInitializedRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfInterfaceFifoQueueMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfLockRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfMmRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfPartitionIdentifiers(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRomInd(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestNto1InfoRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestNto1InfoRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgExtIdRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxIf2Dest(void) { return (boolean)([!IF "$numIfRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxTp2Dest(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxTp2Src(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfSingleBufferMetaDataArrayRam(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfSrcApplicationRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTx2Lo(void) { return (boolean)([!IF "$numTxAll > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTxIf2Up(void) { return (boolean)([!IF "$numIfTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTxTp2Src(void) { return (boolean)([!IF "$numTpTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSrcApplicationRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomDestinationIdxOfSrcApplicationRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomSourceIdxOfSrcApplicationRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTx2Lo(void) { return (boolean)([!IF "$numTxAll > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRTransmitCallbackOfTx2Lo(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasCancelTransmitUsedOfTx2Lo(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfTx2Lo(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRomIdxOfTx2Lo(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxIf2Up(void) { return (boolean)([!IF "$numIfTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRTxConfirmationCallbackOfTxIf2Up(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfTxIf2Up(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomIdxOfTxIf2Up(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxConfirmationUsedOfTxIf2Up(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxTp2Src(void) { return (boolean)([!IF "$numTpTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBswMPduRTpTxConfirmationCallbackOfTxTp2Src(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInvalidHndOfTxTp2Src(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomIdxOfTxTp2Src(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPCConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPCPartitionConfigOfPCConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPartitionIdentifiersOfPCConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfPartitionIdentifiersOfPCConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasApplicationId2DestApplicationManagerRomOfPCPartitionConfig(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasBmTxBufferMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasConfigIdOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasDestApplicationManagerRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasExclusiveAreaRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasGeneralPropertiesRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInitializedRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasInterfaceFifoQueueMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasLockRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasMmRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomIndOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmDestRpgRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestNto1InfoRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmGDestRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRmSrcRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgExtIdRomOfPCPartitionConfig(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRpgRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxIf2DestOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxTp2DestOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasRxTp2SrcOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSingleBufferMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfApplicationId2DestApplicationManagerRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfBmTxBufferMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfDestApplicationManagerRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfExclusiveAreaRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfGeneralPropertiesRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfInitializedRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfInterfaceFifoQueueMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfLockRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfMmRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRomIndOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmDestRpgRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestNto1InfoRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestNto1InfoRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmGDestRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRmSrcRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgExtIdRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRpgRomOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxIf2DestOfPCPartitionConfig(void) { return (boolean)([!IF "$numIfRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxTp2DestOfPCPartitionConfig(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfRxTp2SrcOfPCPartitionConfig(void) { return (boolean)([!IF "$numTpRx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfSingleBufferMetaDataArrayRamOfPCPartitionConfig(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfSrcApplicationRomOfPCPartitionConfig(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTx2LoOfPCPartitionConfig(void) { return (boolean)([!IF "$numTxAll > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTxIf2UpOfPCPartitionConfig(void) { return (boolean)([!IF "$numIfTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSizeOfTxTp2SrcOfPCPartitionConfig(void) { return (boolean)([!IF "$numTpTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasSrcApplicationRomOfPCPartitionConfig(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTx2LoOfPCPartitionConfig(void) { return (boolean)([!IF "$numTxAll > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxIf2UpOfPCPartitionConfig(void) { return (boolean)([!IF "$numIfTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_HasTxTp2SrcOfPCPartitionConfig(void) { return (boolean)([!IF "$numTpTx > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }

PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsSINGLE_BUFFERQueueTypeOfRmBufferedIfPropertiesRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsFIFOQueueTypeOfRmBufferedIfPropertiesRom(PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(partitionIndex); return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsSHORTENPduLengthHandlingStrategyOfRmDestRom(void) { return (boolean)([!IF "$hasShortenLen > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsDISCARDPduLengthHandlingStrategyOfRmDestRom(void) { return (boolean)([!IF "$hasDiscardLen > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsIGNOREPduLengthHandlingStrategyOfRmDestRom(void) { return (boolean)([!IF "$hasIgnoreLen > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsUNUSEDPduLengthHandlingStrategyOfRmDestRom(void) { return (boolean)([!IF "$hasUnusedLen > 0"!]TRUE[!ELSE!]FALSE[!ENDIF!] != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsRXDirectionOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsTXDirectionOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsDEFERREDPduRDestPduProcessingOfRmGDestRom(void) { return (boolean)(FALSE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsIMMEDIATEPduRDestPduProcessingOfRmGDestRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsRXDirectionOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_ExistsTXDirectionOfRmSrcRom(void) { return (boolean)(TRUE != FALSE); }

PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IncBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IncInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IncEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IncRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IncSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }

PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DecBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DecInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DecEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DecRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DecSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(partitionIndex); }

PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_AddBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_BmTxBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_AddInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_InterfaceFifoQueueMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_AddEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_EnabledCntOfRmDestRpgRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_AddRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_RmDestRomIdxOfRmGDestNto1InfoRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_AddSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_SingleBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }

PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SubBmTxBufferMetaDataArrayRam(PduR_BmTxBufferMetaDataArrayRamIterType Index, PduR_BmTxBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SubInterfaceFifoQueueMetaDataArrayRam(PduR_InterfaceFifoQueueMetaDataArrayRamIterType Index, PduR_InterfaceFifoQueueMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SubEnabledCntOfRmDestRpgRam(PduR_RmDestRpgRamIterType Index, PduR_EnabledCntOfRmDestRpgRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SubRmDestRomIdxOfRmGDestNto1InfoRam(PduR_RmGDestNto1InfoRamIterType Index, PduR_RmDestRomIdxOfRmGDestNto1InfoRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SubSingleBufferMetaDataArrayRam(PduR_SingleBufferMetaDataArrayRamIterType Index, PduR_SingleBufferMetaDataArrayRamType Value, PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIndex) { PDUR_DUMMY_STATEMENT(Index); PDUR_DUMMY_STATEMENT(Value); PDUR_DUMMY_STATEMENT(partitionIndex); }
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_LCFG_H */
