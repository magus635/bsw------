[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Mcu.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!AUTOSPACING!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('MCU_M'))"!]
[!VAR "MCU_M"="'true'"!]

[!VAR "TOUTSEL_Var" = "num:i(0)"!][!//
[!VAR "TIMSEL_Var" = "num:i(0)"!][!//
[!VAR "LOOP_Number" = "num:i(0)"!][!//
[!VAR "TOUT_Description" = "num:i(0)"!][!//
[!VAR "TOUT_Number" = "num:i(0)"!][!//
[!VAR "SELECT_PIN" = "num:i(0)"!][!//
[!VAR "SELECT_NUM" = "num:i(0)"!][!//


[!VAR "Tim_index" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index" = "num:i(0)"!][!//
[!VAR "Tim_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index_Check" = "num:i(0)"!][!//
[!VAR "TIM_SELECT_PIN" = "num:i(0)"!][!//

[!VAR "Channel_index" = "num:i(0)"!][!//
[!VAR "Atom_Channel_index" = "num:i(0)"!][!//
[!VAR "Tom_index" = "num:i(0)"!][!//
[!VAR "Atom_index" = "num:i(0)"!][!//
[!VAR "ToutFirstNumber" = "num:i(0)"!][!//
[!VAR "Tom_index_Check" = "num:i(0)"!][!//
[!VAR "Atom_index_Check" = "num:i(0)"!][!//
[!VAR "Channel_index_Check" = "num:i(0)"!][!//
[!VAR "Atom_Channel_index_Check" = "num:i(0)"!][!//

[!VAR "GTM_ADCTRG0OUT0_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG1OUT0_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG2OUT0_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG3OUT0_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG4OUT0_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG0OUT1_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG1OUT1_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG2OUT1_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG3OUT1_Register" = "num:i(0)"!][!//
[!VAR "GTM_ADCTRG4OUT1_Register" = "num:i(0)"!][!//

[!VAR "RegisterValueSET0CON0" = "num:i(0)"!][!//
[!VAR "RegisterValueSET0CON1" = "num:i(0)"!][!//
[!VAR "RegisterValueSET0CON2" = "num:i(0)"!][!//
[!VAR "RegisterValueSET0CON3" = "num:i(0)"!][!//

[!VAR "RegisterValueSET1CON0" = "num:i(0)"!][!//
[!VAR "RegisterValueSET1CON1" = "num:i(0)"!][!//
[!VAR "RegisterValueSET1CON2" = "num:i(0)"!][!//
[!VAR "RegisterValueSET1CON3" = "num:i(0)"!][!//

[!VAR "RegisterValueSET2CON0" = "num:i(0)"!][!//
[!VAR "RegisterValueSET2CON1" = "num:i(0)"!][!//
[!VAR "RegisterValueSET2CON2" = "num:i(0)"!][!//
[!VAR "RegisterValueSET2CON3" = "num:i(0)"!][!//

[!VAR "RegisterValueSET3CON0" = "num:i(0)"!][!//
[!VAR "RegisterValueSET3CON1" = "num:i(0)"!][!//
[!VAR "RegisterValueSET3CON2" = "num:i(0)"!][!//
[!VAR "RegisterValueSET3CON3" = "num:i(0)"!][!//



[!INDENT "0"!][!//
[!/*Judge the Tom Tout number is select repeat or not.*/!][!//
[!MACRO "GTM_TOUT_REPEAT_ERROR_CHECK"!][!//
[!VAR "Tom_id" = "num:i(0)"!][!//
[!VAR "Channel_id" = "num:i(0)"!][!//
[!VAR "TomCheck_id" = "num:i(0)"!][!//
[!VAR "ChannelCheck_id" = "num:i(0)"!][!//
[!VAR "AtomCheck_id" = "num:i(0)"!][!//
[!VAR "Atom_id" = "num:i(0)"!][!//
[!/*Select the Tom node.*/!][!//
[!SELECT "GtmConfiguration/*[1]/Tom"!][!//
    [!/*Loop check the Tom0 to Tom2.*/!][!//
    [!FOR "$Tom_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
        [!/*Print the current Tom index for debug.*/!][!//
        [!/*Tom[!"$Tom_index"!]*/!][!//
        [!/*Select the Tomchanel node of current Tom.*/!][!//
        [!SELECT "./*[num:i($Tom_index + 1)]/TomChannel"!][!//
        [!/*Print the current node path for debug.*/!][!//
        [!/*[!"node :path(.)"!]*/!][!//
        [!/*Everytime Tom index increase, the Channel index variable need to clear to 0.*/!][!//
        [!VAR "Channel_index" = "num:i(0)"!][!//
        [!/*Loop the channel of current Tom node by channel_index. The index range is 0~15.*/!][!//
        [!FOR "$Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
            [!VAR "Channel_id" = "./*[num:i($Channel_index + 1)]/TomChannelOutput/ChannelId"!][!//
            [!VAR "Tom_id" = "./*[num:i($Channel_index + 1)]/TomChannelOutput/TomId"!][!//
            [!/*Select the TomChannelPortPinSelect node of current TomChannel.In order to cut down the Tout number to compare with other node.*/!][!//
            [!SELECT "./*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelPortPinSelect"!][!//
                [!/*Judge the Tom_N function is supportted. If support, cut down the TomChannelNegativePortPinSelect Tout number.*/!][!//
                [!IF "../GTM_Tom_Negative_Support = 'true'"!][!//
                    [!/*Cut down the Tout number of the Tom_N to compare with other node.*/!][!//
                    [!VAR "ToutFirstNumber" = "substring(node:value(../TomChannelNegativePortPinSelect),11,7)"!][!//
                [!ELSE!][!//
                    [!/*Cut down the Tout number to compare with other node.*/!][!//
                    [!VAR "ToutFirstNumber" = "substring(node:value(.),11,7)"!][!//
                [!ENDIF!][!//
                [!/*Print the current Tom number and channel index for debug.*/!][!//
                [!/*Tom[!"$Tom_index"!]_Channel[!"$Channel_index"!] the TOUT is [!"$ToutFirstNumber"!].*/!][!//
                [!/*Set the index of checking variable with current index.It's can loop in order check Tout number, don't check previous Tom index.*/!][!//
                [!VAR "Tom_index_Check" = "num:i($Tom_index)"!][!//
                [!/*Loop the Tom node by index. The index range is 0~2.*/!][!//
                [!FOR "$Tom_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
                    [!/*If the index gt 2 ,then break out.*/!][!//
                    [!IF "$Tom_index_Check > num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
                        [!BREAK!][!//
                    [!ELSE!][!//
                        [!/*Print the current check Tom index for debug.*/!][!//
                        [!/*Check the Tom[!"$Tom_index_Check"!]*/!][!//
                        [!/*If the check index is equal to current tom index, it means the Tom index of node is itself located.*/!][!//
                        [!IF "$Tom_index_Check = $Tom_index"!][!//
                            [!/*Then set the check index to current chanel index for avoiding repeat check previous channel node.*/!][!//
                            [!VAR "Channel_index_Check" = "num:i($Channel_index)"!][!//
                        [!ELSE!][!//
                            [!/*If the Tom index is not current index. Then clear the channel index to zero.*/!][!//
                            [!VAR "Channel_index_Check" = "num:i(0)"!][!//
                        [!ENDIF!][!//
                        [!/*Loop the channel check index from current index to max number.*/!][!//
                        [!FOR "$Channel_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
                            [!/*If the channel check index is lt 15 and the Tom check index equal current index, 
                                then check the current node Tout number is different from the check node or not*/!][!//
                            [!IF "(num:i($Channel_index_Check + 1) < '16') and ($Tom_index_Check = $Tom_index)"!][!//
                                [!/*Judge the Tom_N function is supportted. If support, compare the TomChannelNegativePortPinSelect Tout number.*/!][!//
                                [!IF "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/GTM_Tom_Negative_Support = 'true'"!][!//
                                    [!/*Print the current check Tom channel index and node path for debug.*/!][!//
                                    [!/*Check the Tom[!"num:i($Tom_index_Check)"!]Channel[!"num:i($Channel_index_Check + 1)"!]*/!][!//
                                    [!/*[!"substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelPortPinSelect),11,7)"!]*/!][!//
                                    [!/*[!"node:path(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelPortPinSelect)"!]*/!][!//
                                    [!/*If the Tout number is equal, then report the error node index.*/!][!//
                                    [!IF "node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelNegativePortPinSelect) = 'TOMXXCHXX_NO_USED_TOM_CHANNEL'"!][!//
                                    [!/*Do nothing.*/!][!//
                                    [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelNegativePortPinSelect),11,7)"!][!//
                                        [!VAR "ChannelCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/ChannelId"!][!//
                                        [!VAR "TomCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomId"!][!//
                                        [!ERROR!][!//
                                            [101-00-01-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Tom[!"$TomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                        [!ENDERROR!][!//
                                    [!ENDIF!][!//
                                [!ELSE!][!//
                                    [!IF "node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelPortPinSelect) = 'TOMXXCHXX_NO_USED_TOM_CHANNEL'"!][!//
                                    [!/*Do nothing.*/!][!//
                                    [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomChannelPortPinSelect),11,7)"!][!//
                                        [!VAR "ChannelCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/ChannelId"!][!//
                                        [!VAR "TomCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 2]/TomChannelOutput/TomId"!][!//
                                        [!ERROR!][!//
                                            [101-00-02-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Tom[!"$TomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                        [!ENDERROR!][!//
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!/*If the current Tom index is not the check index, then check all the channel index.*/!][!//
                            [!ELSEIF "$Tom_index_Check > $Tom_index"!][!//
                                [!/*Judge the Tom_N function is supportted. If support, compare the TomChannelNegativePortPinSelect Tout number.*/!][!//
                                [!IF "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/GTM_Tom_Negative_Support = 'true'"!][!//
                                    [!/*Print the current check Tom channel index and node path for debug.*/!][!//
                                    [!/*Check the Tom[!"num:i($Tom_index_Check)"!]Channel[!"num:i($Channel_index_Check)"!]*/!][!//
                                    [!/*[!"substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelPortPinSelect),11,7)"!]*/!][!//
                                    [!/*[!"node:path(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelPortPinSelect)"!]*/!][!//
                                    [!/*If the Tout number is equal, then report the error node index.*/!][!//
                                    [!IF "node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelNegativePortPinSelect) = 'TOMXXCHXX_NO_USED_TOM_CHANNEL'"!][!//
                                    [!/*Do nothing.*/!][!//
                                    [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelNegativePortPinSelect),11,7)"!][!//
                                        [!VAR "ChannelCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/ChannelId"!][!//
                                        [!VAR "TomCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomId"!][!//
                                        [!ERROR!][!//
                                            [101-00-01-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!].. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Tom[!"$TomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                        [!ENDERROR!][!//
                                    [!ENDIF!][!//
                                [!ELSE!][!//
                                    [!IF "node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelPortPinSelect) = 'TOMXXCHXX_NO_USED_TOM_CHANNEL'"!][!//
                                    [!/*Do nothing.*/!][!//
                                    [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomChannelPortPinSelect),11,7)"!][!//
                                        [!VAR "ChannelCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/ChannelId"!][!//
                                        [!VAR "TomCheck_id" = "../../../../../*[$Tom_index_Check + 1]/TomChannel/*[$Channel_index_Check + 1]/TomChannelOutput/TomId"!][!//
                                        [!ERROR!][!//
                                            [101-00-02-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!].. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Tom[!"$TomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                        [!ENDERROR!][!//
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!/*If the current Tom index is out of range, then break current loop.*/!][!//
                            [!ELSE!][!//
                                [!BREAK!][!//
                            [!ENDIF!][!//
                            [!/*Increased the check channel index by one.*/!][!//
                            [!VAR "Channel_index_Check" = "num:i($Channel_index_Check + 1)"!][!//
                        [!ENDFOR!][!//
                        [!/*Increased the check Tom index by one.*/!][!//
                        [!VAR "Tom_index_Check" = "num:i($Tom_index_Check + 1)"!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!/*Loop the Atom node by index. The index range is 0~2. Clear the atom check index to 0 everytime the select channel index increased. 
                    It's need check the Atom node is repeat Tout number or not every Tom channel node.*/!][!//
                [!VAR "Atom_index_Check" = "num:i(0)"!][!//
                [!FOR "$Atom_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
                    [!/*If the index gt 5 ,then break out.*/!][!//
                    [!IF "$Atom_index_Check > num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
                        [!BREAK!][!//
                    [!ELSE!][!//
                        [!/*Print the current check Atom index for debug.*/!][!//
                        [!/*Check the Atom[!"$Atom_index_Check"!]*/!][!//
                        [!VAR "Atom_Channel_index_Check" = "num:i(0)"!][!//
                        [!/*Loop the channel index of current Atom node..*/!][!//
                        [!FOR "$Atom_Channel_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
                            [!/*Judge the Atom_N function is supportted. If support, compare the AtomChannelOutput Tout number.*/!][!//
                            [!IF "../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
                                [!/*Print the current check Atom channel index for debug.*/!][!//
                                [!/*Check the Atom[!"$Atom_index_Check"!]_Channel[!"$Atom_Channel_index_Check"!]*/!][!//
                                [!/*If the Tout number is equal the current atom channel Tout number, then report the error node index.*/!][!//
                                [!IF "node:value(../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelNegativePortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelNegativePortPinSelect),11,7)"!][!//
                                    [!VAR "ChannelCheck_id" = "../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/ChannelId"!][!//
                                    [!VAR "AtomCheck_id" = "../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-01-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                [!IF "node:value(../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelPortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelPortPinSelect),11,7)"!][!//
                                    [!VAR "ChannelCheck_id" = "../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/ChannelId"!][!//
                                    [!VAR "AtomCheck_id" = "../../../../../../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-02-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Tom[!"$Tom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                            [!/*Increased the check Atom channel index by one.*/!][!//
                            [!VAR "Atom_Channel_index_Check" = "num:i($Atom_Channel_index_Check + 1)"!][!//
                        [!ENDFOR!][!//
                    [!ENDIF!][!//
                    [!/*Increased the check Atom index by one.*/!][!//
                    [!VAR "Atom_index_Check" = "num:i($Atom_index_Check + 1)"!][!//
                [!ENDFOR!][!//



            [!ENDSELECT!][!//
            [!/*Increased the select channel index by one.*/!][!//
            [!VAR "Channel_index" = "num:i($Channel_index + 1)"!][!//
        [!ENDFOR!][!//
        [!ENDSELECT!][!//
        [!/*Increased the Tom channel index by one.*/!][!//
        [!VAR "Tom_index" = "num:i($Tom_index + 1)"!][!//
    [!ENDFOR!][!//
    [!/*Loop check the Atom0 to Atom5.*/!][!//
    [!FOR "$Atom_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
        [!/*Print the current Atom index for debug.*/!][!//
        [!/*Check the Atom[!"$Atom_index"!]*/!][!//
        [!/*Clear the Atom check channel index to 0 for loop in start.*/!][!//
        [!VAR "Atom_Channel_index" = "num:i(0)"!][!//
        [!/*Loop the channel of current Atom node by channel_index. The index range is 0~7.*/!][!//
        [!FOR "$Atom_Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
            [!VAR "Channel_id" = "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/ChannelId"!][!//
            [!VAR "Atom_id" = "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomId"!][!//
            [!/*Judge the Atom_N function is supportted. If support, cut down the TomChannelNegativePortPinSelect Tout number.*/!][!//
            [!IF "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
                [!/*Cut down the Tout number of the Atom_N to compare with other node.*/!][!//
                [!VAR "ToutFirstNumber" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelNegativePortPinSelect),11,7)"!][!//
            [!ELSE!][!//
                [!/*Cut down the Tout number to compare with other node.*/!][!//
                [!VAR "ToutFirstNumber" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelPortPinSelect),11,7)"!][!//
            [!ENDIF!][!//
            [!/*Print the current check Atom index for debug.*/!][!//
            [!/*Atom[!"$Atom_index"!]_Channel[!"$Atom_Channel_index"!]*/!][!//
            [!/*Clear the Atom check index to 0 for loop in start.*/!][!//
            [!VAR "Atom_index_Check" = "num:i(0)"!][!//
            [!/*Loop the Atom check index from 0~5.*/!][!//
            [!FOR "$Atom_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
                [!IF "$Atom_index_Check > num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
                    [!BREAK!][!//
                [!ELSE!][!//
                    [!/*Print the current check Atom index for debug.*/!][!//
                    [!/*Check the Atom[!"$Atom_index_Check"!]*/!][!//
                    [!/*If the check index is equal to current Atom index, it means the Atom index of node is itself located.*/!][!//
                    [!IF "$Atom_index_Check = $Atom_index"!][!//
                        [!/*Then set the check index to current chanel index for avoiding repeat check previous channel node.*/!][!//
                        [!VAR "Atom_Channel_index_Check" = "num:i($Atom_Channel_index)"!][!//
                    [!ELSE!][!//
                        [!/*If the Atom index is not current index. Then clear the channel index to zero.*/!][!//
                        [!VAR "Atom_Channel_index_Check" = "num:i(0)"!][!//
                    [!ENDIF!][!//
                    [!/*Loop the channel index of current Atom node..*/!][!//
                    [!FOR "$Atom_Channel_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
                        [!/*If the channel check index is lt 8 and the Atom check index equal current index, then check the current node Tout number 
                            is different from the check node or not*/!][!//
                        [!IF "(num:i($Atom_Channel_index_Check + 1) < '8') and ($Atom_index_Check = $Atom_index)"!][!//
                            [!/*Judge the Atom_N function is supportted. If support, compare the AtomChannelOutput Tout number.*/!][!//
                            [!IF "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
                                [!/*Print the current check Atom index and node path for debug.*/!][!//
                                [!/*Check the Atom[!"num:i($Atom_index_Check)"!]Channel[!"num:i($Atom_Channel_index_Check + 1)"!]*/!][!//
                                [!/*[!"node:path(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomChannelPortPinSelect)"!]*/!][!//
                                [!/*If the Tout number is equal the current atom channel Tout number, then report the error node index.*/!][!//
                                [!IF "node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomChannelNegativePortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomChannelNegativePortPinSelect),11,7)"!][!//
                                    [!VAR "ChannelCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/ChannelId"!][!//
                                    [!VAR "AtomCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-01-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Atom[!"$Atom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                [!IF "node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomChannelPortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomChannelPortPinSelect),11,7)"!][!//
                                    [!VAR "ChannelCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/ChannelId"!][!//
                                    [!VAR "AtomCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 2]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-02-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Atom[!"$Atom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!/*If the current Atom index is not the check index, then check all the channel index.*/!][!//
                        [!ELSEIF "$Atom_index_Check > $Atom_index"!][!//
                            [!/*Judge the Atom_N function is supportted. If support, compare the AtomChannelOutput Tout number.*/!][!//
                            [!IF "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
                                [!/*Print the current check Atom index and node path for debug.*/!][!//
                                [!/*Check the Atom[!"num:i($Atom_index_Check)"!]Channel[!"num:i($Atom_Channel_index_Check)"!]*/!][!//
                                [!/*[!"node:path(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelPortPinSelect)"!]*/!][!//
                                [!/*If the Tout number is equal, then report the error node index.*/!][!//
                                [!IF "node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelNegativePortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelNegativePortPinSelect),11,7)"!][!//
                                [!VAR "ChannelCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/ChannelId"!][!//
                                [!VAR "AtomCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-01-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Atom[!"$Atom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                [!IF "node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelPortPinSelect) = 'ATOMXCHXX_NO_USED_ATOM_CHANNEL'"!][!//
                                [!/*Do nothing.*/!][!//
                                [!ELSEIF "$ToutFirstNumber = substring(node:value(../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomChannelPortPinSelect),11,7)"!][!//
                                    [!VAR "ChannelCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/ChannelId"!][!//
                                    [!VAR "AtomCheck_id" = "../Atom/*[$Atom_index_Check + 1]/AtomChannel/*[$Atom_Channel_index_Check + 1]/AtomChannelOutput/AtomId"!][!//
                                    [!ERROR!][!//
                                        [101-00-02-ERROR]: "TOUT Number is Select Repeat Error in [!"node:path(.)"!]. The Error node is Atom[!"$Atom_id"!]_Channel[!"$Channel_id"!].The Error Tout number is [!"$ToutFirstNumber"!]. The repeat node is Atom[!"$AtomCheck_id"!]_Channel[!"$ChannelCheck_id"!]."
                                    [!ENDERROR!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                        [!/*Increased the check Atom channel index by one.*/!][!//
                        [!VAR "Atom_Channel_index_Check" = "num:i($Atom_Channel_index_Check + 1)"!][!//
                    [!ENDFOR!][!//
                [!ENDIF!][!//
                [!/*Increased the check Atom index by one.*/!][!//
                [!VAR "Atom_index_Check" = "num:i($Atom_index_Check + 1)"!][!//
            [!ENDFOR!][!//
            




            [!/*Increased the select channel index by one.*/!][!//
            [!VAR "Atom_Channel_index" = "num:i($Atom_Channel_index + 1)"!][!//
        [!ENDFOR!][!//
        [!/*Increased the Atom channel index by one.*/!][!//
        [!VAR "Atom_index" = "num:i($Atom_index + 1)"!][!//
    [!ENDFOR!][!//


[!ENDSELECT!][!//
[!ENDMACRO!][!//

[!/*Get Tom and Atom Tout number to TOUTSELX register.*/!][!//
[!MACRO "GTM_GET_TOUTSEL_NUMBER"!][!//
    [!/*Init the variables that the function are used.*/!][!//
    [!VAR "Tom_index" = "num:i(0)"!][!//
    [!VAR "Tom_id" = "num:i(0)"!][!//
    [!VAR "Channel_index" = "num:i(0)"!][!//
    [!VAR "Channel_id" = "num:i(0)"!][!//
    [!VAR "Atom_Channel_index" = "num:i(0)"!][!//
    [!VAR "Atom_index" = "num:i(0)"!][!//
    [!VAR "ValidTomChannel" = "num:i(0)"!][!//
    [!/*Select the Tom node.*/!][!//
    [!SELECT "GtmConfiguration/*[1]/Tom"!][!//
    [!/*Loop Tom0 to Tom2 of the Tom index.*/!][!//
    [!FOR "Tom_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
        [!/*Init the channel index to 0 for everytime loop new Tom index.*/!][!//
        [!VAR "Channel_index" = "num:i(0)"!][!//
        [!/*Loop Channel0 to Channel15 of the Channel index.*/!][!//
        [!FOR "Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
            [!NOCODE!][!//
            [!/*Judge the Tom_N function is supportted. If support, deal with the TomChannelNegativePortPinSelect Tout number.*/!][!//
            [!VAR "Channel_id" = "./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/ChannelId"!][!//
            [!VAR "Tom_id" = "./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomId"!][!//
            [!IF "./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/GTM_Tom_Negative_Support = 'true'"!][!//
                [!IF "$Channel_id > 9"!][!//
                    [!VAR "Par2"="concat('TOM',$Tom_id,'CH',$Channel_id,'N')"!][!//
                [!ELSE!][!//Channel_id > 9
                    [!VAR "Par2"="concat('TOM',$Tom_id,'CH0',$Channel_id,'N')"!][!//
                [!ENDIF!][!//Channel_id > 9
                [!VAR "Par1" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelNegativePortPinSelect),1,9)"!][!//
                [!IF "$Par1 != 'TOMXXCHXX'"!][!//
                    [!IF "$Par1 != $Par2"!][!//
                        [!ERROR!][!//
                        [101-00-04-ERROR]: "TOMXCHY and TomChannelNegativePortPinSelect([!"$Par1"!]) is mismatching  in  [!"node:path(.)"!]. The Error node is [!"$Par2"!]"
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!/*Cut down the Tout number description.For example TOUT001.*/!][!//
                [!VAR "TOUT_Description" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelNegativePortPinSelect),11,7)"!][!//
                [!/*Cut down the Tout number to find the select Atom or Tom channel.*/!][!//
                [!VAR "TOUT_Number" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelNegativePortPinSelect),15,3)"!][!//
                [!/*Cut down the select channel to combined the TOUTSELX register.*/!][!//
                [!VAR "SELECT_PIN" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelNegativePortPinSelect),22,1)"!][!//
                [!/*Check the Tom[!"num:i($Tom_index)"!]Channel[!"num:i($Channel_index)N"!]*/!][!//
            [!ELSE!][!//
                [!IF "$Channel_id > 9"!][!//
                    [!VAR "Par2"="concat('TOM0',$Tom_id,'CH',$Channel_id)"!][!//
                [!ELSE!][!//Channel_id > 9
                    [!VAR "Par2"="concat('TOM0',$Tom_id,'CH0',$Channel_id)"!][!//
                [!ENDIF!][!//Channel_id > 9
                [!VAR "Par1" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelPortPinSelect),1,9)"!][!//
                [!IF "$Par1 != 'TOMXXCHXX'"!][!//
                    [!IF "$Par1 != $Par2"!][!//
                        [!ERROR!][!//
                        [101-00-04-ERROR]: "TOMXCHY and TomChannelPortPinSelect([!"$Par1"!]) is mismatching  in [!"node:path(.)"!]. The Error node is [!"$Par2"!]"
                        [!ENDERROR!][!//
                    [!ENDIF!][!//$Par1 != $Par2
                [!ENDIF!][!//$Par1 != $TOMXXCHXX
                [!/*Cut down the Tout number description.For example TOUT001.*/!][!//
                [!VAR "TOUT_Description" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelPortPinSelect),11,7)"!][!//
                [!/*Cut down the Tout number to find the select Atom or Tom channel.*/!][!//
                [!VAR "TOUT_Number" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelPortPinSelect),15,3)"!][!//
                [!/*Cut down the select channel to combined the TOUTSELX register.*/!][!//
                [!VAR "SELECT_PIN" = "substring(node:value(./*[num:i($Tom_index + 1)]/TomChannel/*[num:i($Channel_index + 1)]/TomChannelOutput/TomChannelPortPinSelect),22,1)"!][!//
                [!/*Check the Tom[!"num:i($Tom_index)"!]Channel[!"num:i($Channel_index)"!]*/!][!//
            [!ENDIF!][!//
            [!ENDNOCODE!][!//
            [!IF "$TOUT_Description != 'NO_USED'"!][!//
                [!VAR "ValidTomChannel" = "num:i($ValidTomChannel + 1)"!][!//
                [!INDENT "4"!][!//
                {GTM_TOUTSEL_[!"num:hextoint($SELECT_PIN)"!],[!"num:inttohex($TOUT_Number)"!]U},
                [!ENDINDENT!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!/*Increased the Tom channel index by one.*/!][!//
        [!VAR "Tom_index" = "num:i($Tom_index + 1)"!][!//
    [!ENDFOR!][!//
    [!/*Loop Atom0 to Atom5 of the Atom index.*/!][!//
    [!FOR "Atom_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
        [!/*Init the channel index to 0 for everytime loop new Atom index.*/!][!//
        [!VAR "Atom_Channel_index" = "num:i(0)"!][!//
        [!/*Loop Channel0 to Channel7 of the Channel index.*/!][!//
        [!FOR "Atom_Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
                [!NOCODE!][!//

                [!VAR "Channel_id" = "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/ChannelId"!][!//
                [!VAR "Atom_id" = "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomId"!][!//
                [!/*Judge the Atom_N function is supportted. If support, deal with the AtomChannelNegativePortPinSelect Tout number.*/!][!//
                [!IF "../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
                    [!VAR "Par2"="concat('ATOM',$Atom_id,'CH',$Channel_id,'N')"!][!//
                    [!VAR "Par1" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelNegativePortPinSelect),1,9)"!][!//
                    [!IF "$Par1 != 'ATOMXCHXX'"!][!//
                        [!IF "$Par1 != $Par2"!][!//
                            [!ERROR!][!//
                            [101-00-04-ERROR]: "ATOMXCHY and AtomChannelNegativePortPinSelect([!"$Par1"!]) is mismatching  in [!"node:path(.)"!]. The Error node is [!"$Par2"!]"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//$Par1 != $Par2
                    [!ENDIF!][!//$Par1 != $TOMXXCHX
                    [!/*Cut down the Tout number to find the select tom or Atom channel.*/!][!//
                    [!VAR "TOUT_Number" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelNegativePortPinSelect),15,3)"!][!//
                    [!/*Cut down the Tout number description.For example TOUT001.*/!][!//
                    [!VAR "TOUT_Description" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelNegativePortPinSelect),11,7)"!][!//
                    [!/*Cut down the select channel to combined the TOUTSELX register.*/!][!//
                    [!VAR "SELECT_PIN" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelNegativePortPinSelect),22,1)"!][!//
                    [!/*Check the Atom[!"num:i($Atom_index)"!]Channel[!"num:i($Atom_Channel_index)"!]N*/!][!//
                [!ELSE!][!//
                    [!VAR "Par2"="concat('ATOM',$Atom_id,'CH0',$Channel_id)"!][!//
                    [!VAR "Par1" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelPortPinSelect),1,9)"!][!//
                    [!IF "$Par1 != 'ATOMXCHXX'"!][!//
                        [!IF "$Par1 != $Par2"!][!//
                            [!ERROR!][!//
                            [101-00-04-ERROR]: "ATOMXCHY and AtomChannelPortPinSelect([!"$Par1"!]) is mismatching  in [!"node:path(.)"!]. The Error node is [!"$Par2"!]"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//$Par1 != $Par2
                    [!ENDIF!][!//$Par1 != $TOMXXCHXX
                    [!/*Cut down the Tout number to find the select tom or Atom channel.*/!][!//
                    [!VAR "TOUT_Number" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelPortPinSelect),15,3)"!][!//
                    [!/*Cut down the Tout number description.For example TOUT001.*/!][!//
                    [!VAR "TOUT_Description" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelPortPinSelect),11,7)"!][!//
                    [!/*Cut down the select channel to combined the TOUTSELX register.*/!][!//
                    [!VAR "SELECT_PIN" = "substring(node:value(../Atom/*[num:i($Atom_index + 1)]/AtomChannel/*[num:i($Atom_Channel_index + 1)]/AtomChannelOutput/AtomChannelPortPinSelect),22,1)"!][!//
                    [!/*Check the Atom[!"num:i($Atom_index)"!]Channel[!"num:i($Atom_Channel_index)"!]*/!][!//
                [!ENDIF!][!//
                [!ENDNOCODE!][!//
            [!IF "$TOUT_Description != 'NO_USED'"!][!//
                    [!VAR "ValidTomChannel" = "num:i($ValidTomChannel + 1)"!][!//
                    [!INDENT "4"!][!//
                    {GTM_TOUTSEL_[!"num:hextoint($SELECT_PIN)"!],[!"num:inttohex($TOUT_Number)"!]U},
                    [!ENDINDENT!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!/*Increased the Atom channel index by one.*/!][!//
        [!VAR "Atom_index" = "num:i($Atom_index + 1)"!][!//
    [!ENDFOR!][!//
 
    [!ENDSELECT!][!//
[!ENDMACRO!][!//

[!/*Judge the Tim select number repeat or not.*/!][!//
[!MACRO "GTM_TIM_REPEAT_ERROR_CHECK"!][!//
[!SELECT "GtmConfiguration/*[1]/Tim"!][!//
[!/*Init the variables that the function are used.*/!][!//
[!VAR "Tim_index" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index" = "num:i(0)"!][!//
[!VAR "Tim_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index_Check" = "num:i(0)"!][!//
    [!/*Loop Tim0 to Tom5 of the Tom index.*/!][!//
    [!FOR "$Tim_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
        [!/*Init the channel index to 0 for everytime loop new Tim index.*/!][!//
        [!VAR "Tim_Channel_index" = "num:i(0)"!][!//
        [!/*Loop Channel0 to Channel7 of the Channel index.*/!][!//
        [!FOR "$Tim_Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
            [!/*Cut down the select PinSet number to combined the TIMXINSEL register.*/!][!//
            [!VAR "Tim_PinMap_index" = "substring(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect,10,12)"!][!//
                [!/*Print the Tout number information for debug.*/!][!//
                [!/*Tim[!"$Tim_index"!]_Channel[!"$Tim_Channel_index"!]*/!][!//
                [!/*[!"node:value(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect)"!]*/!][!//
                [!/*[!"$Tim_PinMap_index"!]*/!][!//
            [!/*Init the loop check index to 0 for everytime loop new Tim channel node.*/!][!//
            [!VAR "Tim_index_Check" = "num:i(0)"!][!//
            [!/*Loop the index from 0 to 5,correspond the TIM0INSEL to TIM5INSEL.*/!][!//
            [!FOR "$Tim_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
                [!IF "$Tim_index_Check > num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
                    [!BREAK!][!//
                [!ELSE!][!//
                 [!/*If the check index is equal to current Tim index, it means the Tom index of node is itself located.*/!][!//
                    [!IF "$Tim_index_Check = $Tim_index"!][!//
                        [!/*Then set the check index to current chanel index for avoiding repeat check previous channel node.*/!][!//
                        [!VAR "Tim_Channel_index_Check" = "num:i($Tim_Channel_index)"!][!//
                    [!ELSE!][!//
                        [!/*If the Tim index is not current index. Then clear the channel index to zero.*/!][!//
                        [!VAR "Tim_Channel_index_Check" = "num:i(0)"!][!//
                    [!ENDIF!][!//
                    [!/*Loop the channel index of current Tim node.*/!][!//
                    [!FOR "$Tim_Channel_index_Check" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
                         [!/*If the channel check index is lt 8 and the Tim check index equal current index, then check the current node Tim channel Pin set 
                            is different from the check node or not*/!][!//
                        [!IF "(num:i($Tim_Channel_index_Check + 1) < '8') and ($Tim_index_Check = $Tim_index)"!][!//
                            [!/*If the Tim channel Pin set is equal the current Tim channel Tim channel Pin set number, then report the error node index.*/!][!//
                            [!VAR "Tim_PinMap_index_Check" = "substring(./*[num:i($Tim_index_Check+1)]/TimChannel/*[num:i($Tim_Channel_index_Check+2)]/TimChannelGeneral/TimChannelPortPinSelect,10,12)"!][!//
                                [!/*Print the Tout number information for debug.*/!][!//
                                [!/*Check the Tim[!"$Tim_index_Check"!]_Channel[!"num:i($Tim_Channel_index_Check+1)"!]*/!][!//
                                [!/*[!"$Tim_PinMap_index_Check"!]*/!][!//
                            [!IF "$Tim_PinMap_index = $Tim_PinMap_index_Check"!][!//
                                [!IF "contains($Tim_PinMap_index, 'PORT')"!][!//
                                [!WARNING!][!//
                                    [101-00-03-WARNING]: "Tim select repeat , repeat Tim channel select to the same pin set. The  node is Tim[!"num:i($Tim_index)"!]_Channel[!"num:i($Tim_Channel_index_Check)"!].The  Port and pin is [!"$Tim_PinMap_index"!]. The repeat node is Tim[!"num:i($Tim_index_Check)"!]_Channel[!"num:i($Tim_Channel_index_Check)"!]."
                                [!ENDWARNING!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!/*If the current Tim index is not the check index, then check all the channel index.*/!][!//
                        [!ELSEIF "$Tim_index_Check > $Tim_index"!][!//
                            [!/*If the Tim channel Pin set is equal the current Tim channel Tim channel Pin set number, then report the error node index.*/!][!//
                            [!VAR "Tim_PinMap_index_Check" = "substring(./*[num:i($Tim_index_Check+1)]/TimChannel/*[num:i($Tim_Channel_index_Check+1)]/TimChannelGeneral/TimChannelPortPinSelect,10,12)"!][!//
                                [!/*Print the Tout number information for debug.*/!][!//
                                [!/*Check the Tim[!"$Tim_index_Check"!]_Channel[!"num:i($Tim_Channel_index_Check)"!]*/!][!//
                                [!/*[!"$Tim_PinMap_index_Check"!]*/!][!//
                            [!IF "$Tim_PinMap_index = $Tim_PinMap_index_Check"!][!//
                                [!IF "contains($Tim_PinMap_index, 'PORT')"!][!//
                                [!WARNING!][!//
                                     [101-00-03-WARNING]: "Tim select repeat , repeat Tim channel select to the same pin set. The  node is Tim[!"num:i($Tim_index)"!]_Channel[!"num:i($Tim_Channel_index_Check)"!].The  Port and pin is [!"$Tim_PinMap_index"!]. The repeat node is Tim[!"num:i($Tim_index_Check)"!]_Channel[!"num:i($Tim_Channel_index_Check)"!]."
                                [!ENDWARNING!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                        [!/*Increased the check Tim channel index by one.*/!][!//
                        [!VAR "Tim_Channel_index_Check" = "num:i($Tim_Channel_index_Check + 1)"!][!//
                    [!ENDFOR!][!//
                [!ENDIF!][!//
                [!/*Increased the check Tim index by one.*/!][!//
                [!VAR "Tim_index_Check" = "num:i($Tim_index_Check + 1)"!][!//
            [!ENDFOR!][!//
            [!/*Increased the check Tim channel index by one.*/!][!//
            [!VAR "Tim_Channel_index" = "num:i($Tim_Channel_index + 1)"!][!//
        [!ENDFOR!][!//
        [!/*Increased the check Tim index by one.*/!][!//
        [!VAR "Tim_index" = "num:i($Tim_index + 1)"!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//

[!/*Get Tim seclect channel to TIMXINSEL register.*/!][!//
[!MACRO "GTM_GET_TIM_NUMBER"!][!//
[!SELECT "GtmConfiguration/*[1]/Tim"!][!//
[!VAR "Tim_index" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index" = "num:i(0)"!][!//
[!VAR "Tim_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index_Check" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index" = "num:i(0)"!][!//
[!VAR "Tim_PinMap_index_Check" = "num:i(0)"!][!//
[!VAR "TIM_SELECT_PIN" = "num:i(0)"!][!//
[!VAR "ValidTimChannel" = "num:i(0)"!][!//
[!/*Loop Tim0 to Tim5 of the Tim index.*/!][!//
    [!FOR "Tim_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
        [!/*Init the channel index to 0 for everytime loop new Tim index.*/!][!//
        [!VAR "Tim_Channel_index" = "num:i(0)"!][!//
        [!/*Loop Channel0 to Channel7 of the Channel index.*/!][!//
        [!FOR "Tim_Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
            [!VAR "Channel_id" = "./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/ChannelId"!][!//
            [!VAR "Tim_id" = "./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimId"!][!//
            [!VAR "TIM_SELECT_PIN" = "text:split(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect,'_SEL')[last()]"!][!//
            [!VAR "Par2"="concat('TIM',$Tim_id,'_CH',$Channel_id)"!][!//
            [!VAR "Par1" = "substring(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect,1,8)"!][!//
            [!IF "$Par1 != 'TIM_CHAN'"!][!//
                [!IF "$Par1 != $Par2"!][!//
                    [!ERROR!][!//
                    [101-00-04-ERROR]: "TIMXCHY and TimChannelPortPinSelect([!"$Par1"!]) is mismatching  in [!"node:path(.)"!]. The Error node is [!"$Par2"!]"
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!/*Print the Tim number information for debug.*/!][!//
            [!/*[!"$TIM_SELECT_PIN"!]*/!][!//
            [!/*Select the number of the Tim from TIMXINSEL register.*/!][!//
            [!VAR "SELECT_NUM" = "num:i($Tim_id*8)"!][!//
            [!/*Loop the Tim number of the TIMXINSEL register.*/!][!//
            [!FOR "SELECT_NUM" = "num:i($Tim_id*8)" TO "num:i($Tim_id*8+7)"!][!//
                [!/*If the current TIm number is equal to the Tim number of the TIMXINSEL register,
                    then load the select channel to the array of the TIMSEL_register.*/!][!//
                [!IF "num:i($Channel_id + $Tim_id*8) = num:i($SELECT_NUM)"!][!//
                [!IF "num:i($TIM_SELECT_PIN) != num:i(0)"!][!//
                    [!VAR "ValidTimChannel" = "num:i($ValidTimChannel + 1)"!][!//
                    [!INDENT "4"!][!//
                    {GTM_TIM_INDEX_[!"num:i($Tim_id)"!],GTM_TIM_CH_INDEX_[!"num:i($Channel_id)"!],GTM_CHXSEL_[!"num:i($TIM_SELECT_PIN)"!] },
                    [!ENDINDENT!][!//
                [!ELSEIF "num:hextoint($TIM_SELECT_PIN) != num:i(0)"!][!//
                    [!VAR "ValidTimChannel" = "num:i($ValidTimChannel + 1)"!][!//
                    [!INDENT "4"!][!//
                    {GTM_TIM_INDEX_[!"num:i($Tim_id)"!],GTM_TIM_CH_INDEX_[!"num:i($Channel_id)"!],GTM_CHXSEL_[!"num:hextoint($TIM_SELECT_PIN)"!] },
                    [!ENDINDENT!][!//
                [!ENDIF!][!//
                [!ENDIF!][!//
                [!/*Increased the select channel by one.*/!][!//
                [!VAR "SELECT_NUM" = "num:i($SELECT_NUM + 1)"!][!//
            [!ENDFOR!][!//
        [!ENDFOR!][!//
        [!/*Increased the Tim channel index by one.*/!][!//
        [!VAR "Tim_index" = "num:i($Tim_index + 1)"!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//






[!/*Get DSADC seclect channel to MXINSEL register.*/!][!//
[!MACRO "GTM_GET_DSADC_NUMBER"!][!//
[!SELECT "GtmConfiguration/*[1]/Tim"!][!//
[!VAR "Tim_index" = "num:i(0)"!][!//
[!VAR "Tim_Channel_index" = "num:i(0)"!][!//
[!VAR "DSADC_SELECT" = "num:i(0)"!][!//
[!VAR "DSADC" = "num:i(0)"!][!//
[!VAR "ValidDsadcChannel" = "num:i(0)"!][!//
[!/*Loop Tim0 to Tim5 of the Tim index.*/!][!//
    [!FOR "Tim_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
        [!/*Init the channel index to 0 for everytime loop new Tim index.*/!][!//
        [!VAR "Tim_Channel_index" = "num:i(0)"!][!//
        [!/*Loop Channel0 to Channel7 of the Channel index.*/!][!//
        [!FOR "Tim_Channel_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
            [!VAR "Channel_id" = "./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/ChannelId"!][!//
            [!VAR "Tim_id" = "./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimId"!][!//
            [!VAR "DSADC_SELECT" = "text:split(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect, '_')[5]"!][!//
            [!VAR "DSADC" = "substring(./*[num:i($Tim_index+1)]/TimChannel/*[num:i($Tim_Channel_index+1)]/TimChannelGeneral/TimChannelPortPinSelect,10,5)"!][!//
            [!/*Print the Tim number information for debug.*/!][!//
            [!/*Select the number of the Tim from TIMXINSEL register.*/!][!//
            [!VAR "SELECT_NUM" = "num:i($Tim_id*8)"!][!//
            [!/*Loop the Tim number of the TIMXINSEL register.*/!][!//
            [!FOR "SELECT_NUM" = "num:i($Tim_id*8)" TO "num:i($Tim_id*8+7)"!][!//
                [!/*If the current TIm number is equal to the Tim number of the TIMXINSEL register,
                    then load the select channel to the array of the TIMSEL_register.*/!][!//
                [!IF "num:i($Channel_id + $Tim_id*8) = num:i($SELECT_NUM)"!][!//
                [!IF "$DSADC = 'DSADC'"!][!//
                    [!VAR "ValidDsadcChannel" = "num:i($ValidDsadcChannel + 1)"!][!//
                    [!INDENT "4"!][!//
                    {[!"num:i($Tim_id)"!]U, [!"num:i($Channel_id)"!]U, GTM_CHXSEL_[!"num:hextoint($DSADC_SELECT)"!] },
                    [!ENDINDENT!][!//
                [!ENDIF!][!//
                [!ENDIF!][!//
                [!/*Increased the select channel by one.*/!][!//
                [!VAR "SELECT_NUM" = "num:i($SELECT_NUM + 1)"!][!//
            [!ENDFOR!][!//
        [!ENDFOR!][!//
        [!/*Increased the Tim channel index by one.*/!][!//
        [!VAR "Tim_index" = "num:i($Tim_index + 1)"!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//






[!/*Get Gtm seclect channel to ADCTRGxOUTx register.*/!][!//
[!MACRO "GTM_GET_SARADC_TRIGGER_REGISTER"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmTrigger/*[1]/GtmTrigger"!][!//
    [!FOR "ADC_Index" = "0" TO "7"!][!//
        [!VAR "GTM_ADCTRG0OUT0_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger0Select),19,2)),num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger0Select),15,1))*4),num:i($GTM_ADCTRG0OUT0_Register))"!][!//
        [!VAR "GTM_ADCTRG1OUT0_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger1Select),19,2)),num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger1Select),15,1))*4),num:i($GTM_ADCTRG1OUT0_Register))"!][!//
        [!VAR "GTM_ADCTRG2OUT0_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger2Select),19,2)),num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger2Select),15,1))*4),num:i($GTM_ADCTRG2OUT0_Register))"!][!//
        [!VAR "GTM_ADCTRG3OUT0_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger3Select),19,2)),num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger3Select),15,1))*4),num:i($GTM_ADCTRG3OUT0_Register))"!][!//
        [!VAR "GTM_ADCTRG4OUT0_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger4Select),19,2)),num:i(substring(node:value(./*[num:i($ADC_Index + 1)]/GtmTrigger4Select),15,1))*4),num:i($GTM_ADCTRG4OUT0_Register))"!][!//
    [!ENDFOR!][!//
    [!VAR "GTM_ADCTRG0OUT1_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[9]/GtmTrigger0Select),19,2)),num:i(substring(node:value(./*[9]/GtmTrigger0Select),15,1))*4),num:i($GTM_ADCTRG0OUT1_Register))"!][!//
    [!VAR "GTM_ADCTRG1OUT1_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[9]/GtmTrigger1Select),19,2)),num:i(substring(node:value(./*[9]/GtmTrigger1Select),15,1))*4),num:i($GTM_ADCTRG1OUT1_Register))"!][!//
    [!VAR "GTM_ADCTRG2OUT1_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[9]/GtmTrigger2Select),19,2)),num:i(substring(node:value(./*[9]/GtmTrigger2Select),15,1))*4),num:i($GTM_ADCTRG2OUT1_Register))"!][!//
    [!VAR "GTM_ADCTRG3OUT1_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[9]/GtmTrigger3Select),19,2)),num:i(substring(node:value(./*[9]/GtmTrigger3Select),15,1))*4),num:i($GTM_ADCTRG3OUT1_Register))"!][!//
    [!VAR "GTM_ADCTRG4OUT1_Register" = "bit:xor(bit:shl(num:i(substring(node:value(./*[9]/GtmTrigger4Select),19,2)),num:i(substring(node:value(./*[9]/GtmTrigger4Select),15,1))*4),num:i($GTM_ADCTRG4OUT1_Register))"!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//










[!/*Get Gtm seclect channel to ADCTRGxOUTx register. TRI0CH00_TOM00_CH07_SEL0_CH02 */!][!//
[!MACRO "GTM_GET_SARADC_TRIGGER"!][!//
[!VAR "TrigerSelect" = "num:i(0)"!][!//
[!VAR "SelValue" = "num:i(0)"!][!//
[!VAR "ValidAdcChannel" = "num:i(0)"!][!//
[!INDENT "4"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/SaradcSent"!][!//
    [!FOR "SaradcCheckindex" = "0" TO "num:i(ecu:get('Gtm.NumberOfTriggerChannel')*4 - 1)"!][!//
        [!FOR "SaradcCheckindexIn" = "0" TO "$SaradcCheckindex"!][!//
        [!VAR "triggIn" = "substring((./*[num:i($SaradcCheckindexIn + 1)]/GtmTriggerSelect),4,1)"!][!//
        [!VAR "trigIn" = "(./*[num:i($SaradcCheckindexIn + 1)]/GtmTriggerSelect)"!][!//
        [!VAR "triggOut" = "substring((./*[num:i($SaradcCheckindex + 1)]/GtmTriggerSelect),4,1)"!][!//
        [!VAR "trigOut" = "(./*[num:i($SaradcCheckindex + 1)]/GtmTriggerSelect)"!][!//
        [!VAR "ChidIn" = "(./*[num:i($SaradcCheckindexIn + 1)]/ChannelId)"!][!//
        [!VAR "ChidOut" = "(./*[num:i($SaradcCheckindex + 1)]/ChannelId)"!][!//
        [!IF "$ChidIn = $ChidOut"!][!//
            [!IF "$triggIn = $triggOut"!][!//
                [!IF "$trigIn != $trigOut"!][!//
                [!ERROR!][!//
                101-10: GtmTriggerSelect choose the same Gtmtrigger GroupID [!"$triggIn"!], and use different source [!"$trigIn"!] and [!"$trigOut"!].
                [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDFOR!][!//


    [!FOR "AdcIndex" = "0" TO "num:i(ecu:get('Gtm.NumberOfTriggerChannel')*4 - 1)"!][!//
    [!VAR "TrigerSelect" = "substring(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect,10,10)"!][!//
    [!IF "$TrigerSelect != 'NO_TRIGGER'"!][!//
    [!NOCODE!][!//
    //ADD CHECK HERE
    [!VAR "VarTriggerSelect" = "./*[num:i($AdcIndex + 1)]/GtmTriggerSelect"!][!//
    [!VAR "SelectGtm" = "substring($VarTriggerSelect,10,10)"!][!//
    [!VAR "GtmTimerType" = "num:i(0)"!][!//
    [!VAR "GtmTimerModNo" = "num:i(0)"!][!//
    [!VAR "GtmTimerChNo" = "num:i(0)"!][!//


    [!VAR "Channel_Id" = "./*[num:i($AdcIndex + 1)]/ChannelId"!][!//
        [!VAR "ValidAdcChannel" = "num:i($ValidAdcChannel + 1)"!][!//
        [!VAR "ADC_Valid_Index" = "$Channel_Id"!][!//
        [!VAR "SelValue" = "num:i(substring(node:value(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect),28,2))"!][!//
        [!VAR "Group_Id" = "num:i(substring(node:value(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect),4,1))"!][!//
    [!ENDNOCODE!][!//
    {GTM_TRIG_ADCGROUP_[!"$ADC_Valid_Index"!],GTM_TRIG_ADCTRIG_[!"$Group_Id"!],GTM_CHXSEL_[!"$SelValue"!]},
    [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/*Get Gtm seclect channel to DSADCOUTMUX register.*/!][!//
[!MACRO "GTM_GET_DSADC_TRIGGER"!][!//
[!VAR "TrigerSelect" = "num:i(0)"!][!//
[!VAR "SelValue" = "num:i(0)"!][!//
[!VAR "ValidDsadcTrigChannel" = "num:i(0)"!][!//
[!INDENT "4"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/Dsadc"!][!//
    [!FOR "AdcIndex" = "0" TO "num:i(ecu:get('Gtm.DsadcNum') - 1)"!][!//
    [!VAR "TrigerSelect" = "substring(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect,10,10)"!][!//
    [!IF "$TrigerSelect != 'NO_TRIGGER'"!][!//
    [!NOCODE!][!//
    [!VAR "Channel_Id" = "./*[num:i($AdcIndex + 1)]/ChannelId"!][!//
    [!VAR "ValidDsadcTrigChannel" = "num:i($ValidDsadcTrigChannel + 1)"!][!//
    [!VAR "SelValue" = "num:i(substring(node:value(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect),28,2))"!][!//
    [!VAR "Group_Id" = "num:i(substring(node:value(./*[num:i($AdcIndex + 1)]/GtmTriggerSelect),4,1))"!][!//
    [!ENDNOCODE!][!//
    {[!"num:i($Group_Id)"!]U, [!"num:i($Channel_Id)"!]U, GTM_CHXSEL_[!"num:i($SelValue)"!] },
    [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

  




[!MACRO "GTM_GET_DMA"!][!//
[!INDENT "4"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/Dma"!][!//
[!VAR "DMA_ValidCh" = "num:i(0)"!][!//
[!FOR "Index" = "0" TO "num:i(ecu:get('Gtm.DmaRequestNum')) - 1"!][!//
        [!VAR "Select" = "substring(node:value(./*[num:i($Index + 1)]/TriggerSource),6,9)"!][!//
        [!IF "$Select != '63_NO_DMA'"!][!//
        [!VAR "DMA_ValidCh" = "num:i(1+$DMA_ValidCh)"!][!//
        [!VAR "SelValue" = "num:i(substring(node:value(./*[num:i($Index + 1)]/TriggerSource),6,2))"!][!//
        [!VAR "ClusterId" = "substring(node:value(./*[num:i($Index + 1)]/TriggerSource),4,1)"!][!//
        [!VAR "RegisterOffset" = "num:i(0)"!][!//
        [!FOR "CheckIndex" = "num:i(0)" TO "num:i($Index)-1"!][!//
            [!VAR "CheckClusterId" = "substring(node:value(./*[num:i($CheckIndex + 1)]/TriggerSource),4,1)"!][!//
            [!IF "$ClusterId = $CheckClusterId"!][!//
                [!VAR "RegisterOffset" = "num:i($RegisterOffset+num:i(1))"!][!//
                [!IF "node:value(./*[num:i($Index + 1)]/TriggerSource) = node:value(./*[num:i($CheckIndex + 1)]/TriggerSource)"!][!//
                    [!WARNING!][!//
                    [101-10] Warning: Sources of different DmaRequest are the same in [!"node:path(.)"!]. 
                    [!ENDWARNING!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        { GTM_TRIG_DMAL1_MUX_[!"num:i($ClusterId)"!][!"$RegisterOffset"!],[!"$SelValue"!]U},
        [!ENDIF!][!//
[!ENDFOR!]
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!MACRO "GTM_GET_DMA_LEVEL2"!][!//
[!INDENT "4"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/Dma"!][!//
[!VAR "DmaL2_ValidCh" = "num:i(0)"!][!//
[!FOR "Index" = "0" TO "num:i(ecu:get('Gtm.DmaRequestNum')) - 1"!][!//
        [!VAR "Select" = "substring(node:value(./*[num:i($Index + 1)]/TriggerSource),6,9)"!][!//
        [!IF "$Select != '63_NO_DMA'"!][!//
        [!VAR "DmaL2_ValidCh" = "num:i(1+$DmaL2_ValidCh)"!][!//
        [!VAR "SelValue" = "num:i(substring(node:value(./*[num:i($Index + 1)]/TriggerSource),6,2))"!][!//
        [!VAR "ClusterId" = "substring(node:value(./*[num:i($Index + 1)]/TriggerSource),4,1)"!][!//
        [!VAR "RegisterOffset" = "num:i(0)"!][!//
        [!FOR "CheckIndex" = "num:i(0)" TO "num:i($Index)-1"!][!//
            [!VAR "CheckClusterId" = "substring(node:value(./*[num:i($CheckIndex + 1)]/TriggerSource),4,1)"!][!//
            [!IF "$ClusterId = $CheckClusterId"!][!//
                [!VAR "RegisterOffset" = "num:i($RegisterOffset+num:i(1))"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        { GTM_TRIG_DMAL1_MUX_[!"num:i($ClusterId)"!][!"$RegisterOffset"!],GTM_TRIG_DMACHANNEL_[!"num:i(./*[num:i($Index + 1)]/DmaRequestId)"!]},
        [!ENDIF!][!//
[!ENDFOR!]
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//



//24~31 bit for set SetNum 0~15 for bit BitIndex.  16~23 :H,L.
[!MACRO "GTM_GET_MSC"!][!//
[!INDENT "4"!][!//
[!VAR "MSC_ValidCh" = "num:i(0)"!][!//
[!VAR "Set_Valid" = "num:i(0)"!][!//
[!VAR "Bit_Valid" = "num:i(0)"!][!//
[!VAR "Set_ValueH" = "'STD_OFF'"!][!//
[!VAR "Set_ValueL" = "'STD_OFF'"!][!//
[!VAR "SetNumL" = "num:i(0)"!][!//
[!VAR "SetNumH" = "num:i(0)"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*/Msc"!][!//
[!FOR "Mcs_index" = "0" TO "num:i(ecu:get('Gtm.NumberOfMsc') - 1)"!][!//
    [!FOR "BitIndex" = "0" TO "15"!][!//
            [!VAR "Select" = "substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration),1,7)"!][!//
            [!VAR "SelectH" = "substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration),1,7)"!][!//
            [!VAR "SetNumL" = "substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration),4,1)"!][!//
            [!VAR "SetNumH" = "substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration),4,1)"!][!//
            [!VAR "Set_ValueH" = "(./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration)"!][!//
            [!VAR "Set_ValueL" = "(./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration)"!][!//
            [!IF "$Select != 'SETX_NO'"!][!//
                [!VAR "SelValue" = "num:i(substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration),17,2))"!][!//
                [!IF "bit:and($Set_Valid,bit:or ( bit:or (bit:shl(16777216,$SetNumL) ,bit:shl(1,$BitIndex)), bit:shl(65536,1)))!= bit:or ( bit:or (bit:shl(16777216,$SetNumL) ,bit:shl(1,$BitIndex) ) , bit:shl(65536,1) ) "!][!//
                    [!VAR "Set_Valid" = "bit:or ( bit:or (bit:shl(16777216,$SetNumL) ,bit:shl(1,$BitIndex)), bit:shl(65536,1))"!][!//
                    [!VAR "MSC_ValidCh" = "$MSC_ValidCh+num:i(1)"!][!//
                    { GTM_TRIG_MSCTRIGSET_[!"$SetNumL"!], GTM_TRIG_MSCTRIGSIGNAL_[!"$BitIndex"!],[!"$SelValue"!]U},
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$SelectH != 'SETX_NO'"!][!//
                [!VAR "SelValueH" = "num:i(substring((./*[num:i($Mcs_index + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration),17,2))"!][!//
                [!IF "bit:and($Set_Valid,bit:or ( bit:or (bit:shl(16777216,$SetNumH) ,bit:shl(1,$BitIndex)), bit:shl(65536,2)))!= bit:or ( bit:or (bit:shl(16777216,$SetNumH) ,bit:shl(1,$BitIndex) ) , bit:shl(65536,2) ) "!][!//
                    [!VAR "Set_Valid" = "bit:or ( bit:or (bit:shl(16777216,$SetNumH) ,bit:shl(1,$BitIndex)), bit:shl(65536,2))"!][!//
                    [!VAR "MSC_ValidCh" = "$MSC_ValidCh+num:i(1)"!][!//
                    { GTM_TRIG_MSCTRIGSET_[!"$SetNumH"!], GTM_TRIG_MSCTRIGSIGNAL_[!"$BitIndex"!],[!"$SelValueH"!]U},
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$SetNumL = $SetNumH"!][!//
                [!IF "$Set_ValueL != $Set_ValueH"!][!//
                    [!ERROR!][!//
                    [101-00-09-ERROR]: "Only the same resource of the same Set or any resource of different SETs can be selected under the same bit. MscDataBit_[!"$BitIndex"!]  Select ([!"$Set_ValueL"!])  in Msc[!"$Mcs_index"!] is different with (([!"$Set_ValueH"!])).  path is: [!"node:path(.)"!],"
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!FOR "McsCheckindex" = "$Mcs_index+1" TO "num:i(ecu:get('Gtm.NumberOfMsc') - 1)"!][!//
                    [!VAR "SetNumCheckL" = "substring((./*[num:i($McsCheckindex + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration),4,1)"!][!//
                    [!VAR "SetNumCheckH" = "substring((./*[num:i($McsCheckindex + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration),4,1)"!][!//
                    [!VAR "Set_ValueCheckH" = "(./*[num:i($McsCheckindex + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitHighConfiguration)"!][!//
                    [!VAR "Set_ValueCheckL" = "(./*[num:i($McsCheckindex + 1)]/MscDataBit/*[num:i($BitIndex + 1)]/MscDataBitLowConfiguration)"!][!//
                    [!IF "$SetNumL = $SetNumCheckL"!][!//
                        [!IF "$Set_ValueL != $Set_ValueCheckL"!][!//
                            [!ERROR!][!//
                            [101-00-09-ERROR]: "Only the same resource of the same Set or any resource of different SETs can be selected under the same bit. MscDataBit_[!"$BitIndex"!]  Select ([!"$Set_ValueL"!])  in Msc[!"$Mcs_index"!] is different with that of Msc[!"$McsCheckindex"!] ([!"$Set_ValueCheckL"!]).  path is: [!"node:path(.)"!],"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$SetNumH = $SetNumCheckL"!][!//
                        [!IF "$Set_ValueH != $Set_ValueCheckL"!][!//
                            [!ERROR!][!//
                            [101-00-09-ERROR]: "Only the same resource of the same Set or any resource of different SETs can be selected under the same bit. MscDataBit_[!"$BitIndex"!]  Select ([!"$Set_ValueH"!])  in Msc[!"$Mcs_index"!] is different with that of Msc[!"$McsCheckindex"!] ([!"$Set_ValueCheckL"!]).  path is: [!"node:path(.)"!],"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$SetNumL = $SetNumCheckH"!][!//
                        [!IF "$Set_ValueL != $Set_ValueCheckH"!][!//
                            [!ERROR!][!//
                            [101-00-09-ERROR]: "Only the same resource of the same Set or any resource of different SETs can be selected under the same bit. MscDataBit_[!"$BitIndex"!]  Select ([!"$Set_ValueL"!])  in Msc[!"$Mcs_index"!] is different with that of Msc[!"$McsCheckindex"!] ([!"$Set_ValueCheckH"!]).  path is: [!"node:path(.)"!],"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$SetNumH = $SetNumCheckH"!][!//
                        [!IF "$Set_ValueH != $Set_ValueCheckH"!][!//
                            [!ERROR!][!//
                            [101-00-09-ERROR]: "Only the same resource of the same Set or any resource of different SETs can be selected under the same bit. MscDataBit_[!"$BitIndex"!]  Select ([!"$Set_ValueH"!])  in Msc[!"$Mcs_index"!] is different with that of Msc[!"$McsCheckindex"!] ([!"$Set_ValueCheckH"!]).  path is: [!"node:path(.)"!],"
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
            [!ENDFOR!][!//
    [!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//



[!MACRO "GTM_GET_MSC_LEVEL2"!][!//
[!INDENT "4"!][!//
[!VAR "MscL2_ValidCh" = "num:i(0)"!][!//
[!LOOP "GtmConfiguration/*[1]/GtmToPeripheral/*/Msc/*"!][!//
    [!FOR "SET_Index" = "0" TO "15"!][!//
        [!VAR "SET_Id" = "./MscDataBit/*[num:i($SET_Index + 1)]/BitId"!][!//
        [!VAR "Select" = "substring((./MscDataBit/*[num:i($SET_Index + 1)]/MscDataBitLowConfiguration),1,7)"!][!//
        [!IF "$Select != 'SETX_NO'"!][!//
            [!VAR "MscL2_ValidCh" = "num:i(1+$MscL2_ValidCh)"!][!//
            [!VAR "SelValue" = "num:i(substring((./MscDataBit/*[num:i($SET_Index + 1)]/MscDataBitLowConfiguration),4,1))"!][!//
            { GTM_TRIG_MSCTRIGSET_[!"$SelValue"!], GTM_TRIG_MSCTRIGINPUT_LOW,GTM_TRIG_MSCTRIGSIGNAL_[!"$SET_Id"!],GTM_TRIG_MSCNUM_[!"./HwId"!]},
        [!ENDIF!][!//
        [!VAR "Select" = "substring((./MscDataBit/*[num:i($SET_Index + 1)]/MscDataBitHighConfiguration),1,7)"!][!//
        [!IF "$Select != 'SETX_NO'"!][!//
            [!VAR "MscL2_ValidCh" = "num:i(1+$MscL2_ValidCh)"!][!//
            [!VAR "SelValue" = "num:i(substring((./MscDataBit/*[num:i($SET_Index + 1)]/MscDataBitHighConfiguration),4,1))"!][!//
            { GTM_TRIG_MSCTRIGSET_[!"$SelValue"!], GTM_TRIG_MSCTRIGINPUT_HIGH,GTM_TRIG_MSCTRIGSIGNAL_[!"$SET_Id"!],GTM_TRIG_MSCNUM_[!"./HwId"!]},
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//




[!ENDINDENT!][!//
[!ENDIF!][!//avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//



[!MACRO "GetGtmParams","ref1"= "","GtmTimerType"="","GtmTimerModNo"="",
"GtmTimerChNo"=""!][!//
    [!NOCODE!][!//
        [!IF "node:exists(node:ref($ref1)/GtmAtomChannel)"!][!//
            [!VAR "GtmTimerType" = "'ATOM'"!][!//
        [!ELSE!][!//
            [!VAR "GtmTimerType" = "'TOM'"!][!//
        [!ENDIF!][!//
        [!VAR "GtmTimerModNo" = "node:ref($ref1)/ModuleId"!][!//
        [!VAR "GtmTimerChNo" = "node:ref($ref1)/ChannelId"!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/*Get Gtm Trigger Num.*/!][!//
[!MACRO "GTM_GET_TRIGGER_NUM"!][!//
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/GtmOutput"!][!//
[!VAR "McuGtmSourceNum" = "num:i(count(./*))"!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//


