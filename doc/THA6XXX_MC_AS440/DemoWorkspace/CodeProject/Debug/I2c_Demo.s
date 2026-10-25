	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.:
I2c_WriteReadEeprom:
.LDW01:
	push	{r4-r6,lr}
	sub	sp,sp,24
.LDW11:
	mov	r0,64
	mov	r4,1
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.2:
	.endo	..gh.endasm.2

	strb	r0,[sp,7]
;line173
..lin.e0d50a4a..2d5f4691.0_1::
.LDWlin1:
	mov	r1,0
	ldr	r6,.L697
	strb	r1,[sp,6]
	strb	r0,[r6,1]
	mov	r5,r2
	ldr	r0,.L698
	strb	r1,[r6]
.L705:

	bl	I2c_Init
	mov	r1,2
.L30:
	strb	r1,[r6,r1]
	add	r1,r1,1
	cmp	r1,66
	blo	.L30
	ldr	r0,.L699
	ldrb	r5,[r0,r5]
	ldr	r1,.L700
	mov	r0,r5
.L707:

	bl	I2c_SyncTransmit
	cmp	r0,0
	bne	.L43
	str	r4,[sp,20]
	add	r0,sp,6
	str	r0,[sp,8]
	mov	r0,2
	strh	r0,[sp,14]
	mov	r0,80
	strh	r0,[sp,16]
	mov	r0,5
.L709:

	bl	Timer_DelayMs
	add	r1,sp,8
	mov	r0,r5
.L711:

	bl	I2c_SyncTransmit
	cmp	r0,0
	bne	.L43
	ldr	r1,.L701
	mov	r0,r5
.L713:

	bl	I2c_SyncTransmit
	subs	r1,r0,0
	bne	.L43
.L40:
	add	r0,r1,r6
	ldr	r2,.L702
	ldrb	r0,[r0,2]
	ldrb	r2,[r2,r1]
	cmp	r0,r2
	movne	r4,0
	add	r1,r1,1
	cmp	r4,1
	bne	.L43
	cmp	r1,64
	blo	.L40
	ldr	r1,.L703
	b	.L46
.L43:
	ldr	r1,.L704
.L46:
	mov	r0,0
.L715:

	bl	TmcPrintf
.L717:

	bl	I2c_DeInit
.LDW21:
	add	sp,sp,24
.L719:

	pop	{r4-r6,pc}
__ghs_eofn_I2c_WriteReadEeprom:
	.endf	I2c_WriteReadEeprom
	.endf	I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
;RegAddr	r0	local
;AddrBuf	[sp,6]	local
;loopCount	r1	local
;RetStatus	r1	local
;CoreId	r5	local
;compareResult	r4	local
;SendRegisterAddress	[sp,8]	local

	.section ".bss","awb"
I2c_ReceiveData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_ReceiveData:	.space	64
	.endo	I2c_ReceiveData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_ReceiveData
I2c_TransmitData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_TransmitData:	.space	66
	.endo	I2c_TransmitData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_TransmitData
	.section ".mcal_const_asil_d_unspecified","a"
I2c_CorexChanneMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_CorexChanneMap:	.space	4
	.endo	I2c_CorexChanneMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_CorexChanneMap
	.section ".mcal_data_asil_d_unspecified_uncached","aw"
	.align	4
I2c_UserTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_UserTransmit:	.data.w	I2c_TransmitData
	.data.b	0,0,66,0
	.data.b	80,0,0,0
	.data.b	1,0,0,0
	.endo	I2c_UserTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_UserTransmit
I2c_UserReceive..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_UserReceive:	.data.w	I2c_ReceiveData
	.data.b	0,0,64,0
	.data.b	80,0,0,0
	.data.b	2,0,0,0
	.endo	I2c_UserReceive..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_UserReceive
	.section ".rodata","a"
.L587:;	"\nI2c write and read eeprom FAILED!"
	.data.b	10,73,50,99
	.data.b	32,119,114,105
	.data.b	116,101,32,97
	.data.b	110,100,32,114
	.data.b	101,97,100,32
	.data.b	101,101,112,114
	.data.b	111,109,32,70
	.data.b	65,73,76,69
	.data.b	68,33
	.data.b	0
	.endo	.L587
.L588:;	"\nI2c write and read eeprom SUCCESS!"
	.data.b	10,73,50,99
	.data.b	32,119,114,105
	.data.b	116,101,32,97
	.data.b	110,100,32,114
	.data.b	101,97,100,32
	.data.b	101,101,112,114
	.data.b	111,109,32,83
	.data.b	85,67,67,69
	.data.b	83,83,33,0
	.endo	.L588
	.section ".ghcalltbl",""
	.align	4
.L706:	.data.w	.L705
	.endo	.L706
.L708:	.data.w	.L707
	.endo	.L708
.L710:	.data.w	.L709
	.endo	.L710
.L712:	.data.w	.L711
	.endo	.L712
.L714:	.data.w	.L713
	.endo	.L714
.L716:	.data.w	.L715
	.endo	.L716
.L718:	.data.w	.L717
	.endo	.L718
	.section ".ghrettbl",""
	.align	4
.L720:	.data.w	.L719
	.endo	.L720
	.data
	.global	__caller.I2c_DeInit.v.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.I2c_SyncTransmit.i.ip

	.global	__caller.I2c_SyncTransmit.i.ip

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.I2c_SyncTransmit.i.ip

	.global	__caller.I2c_Init.v.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (I2cCoreExeFlag - I2cCoreExeFlag) +0 == 0
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.:
I2c_DemoSelect:
.LDW31:
	push	{r4,lr}
	sub	sp,sp,16
.LDW41:
.L725:
	add	r0,sp,8
.L1781:

	bl	I2c_GetVersionInfo
	ldr	r1,.L1770
	mov	r0,0
.L1783:

	bl	TmcPrintf
	ldr	r1,.L1771
	mov	r0,0
.L1785:

	bl	TmcPrintf
	ldrb	r0,[sp,14]
	str	r0,[sp]
	ldr	r1,.L1772
	ldrb	r2,[sp,12]
	mov	r0,0
	ldrb	r3,[sp,13]
.L1787:

	bl	TmcPrintf
	ldr	r1,.L1773
	mov	r0,0
.L1789:

	bl	TmcPrintf
	ldr	r0,.L1774
	ldrb	r0,[r0]
	cmp	r0,0
	ldreq	r1,.L1775
	ldrne	r1,.L1776
	ldr	r4,.L1777
	mov	r0,0
.L1791:

	bl	TmcPrintf
	ldr	r1,.L1778
	mov	r0,0
.L1793:

	bl	TmcPrintf
	ldr	r1,.L1779
	mov	r0,0
.L1795:

	bl	TmcPrintf
.L1797:

	bl	getChar
	cmp	r0,49
	bne	.L729
	add	r0,r0,208
	strb	r0,[r4,1]
	mov	r0,1
	strb	r0,[r4]
.L1799:

	bl	I2c_Demo
.L732:
	ldrb	r0,[r4,1]
	cmp	r0,255
	bne	.L732
	b	.L725
.L729:
	cmp	r0,120
	cmpne	r0,88
	mvneq	r0,0
	strbeq	r0,[r4,1]
	beq	.L721
	ldr	r1,.L1780
	mov	r0,0
.L1801:

	bl	TmcPrintf
	b	.L725
.L721:
.LDW51:
	add	sp,sp,16
.L1803:

	pop	{r4,pc}
__ghs_eofn_I2c_DemoSelect:
	.endf	I2c_DemoSelect
	.endf	I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
;Cmd	r0	local
;VersionInfo	[sp,8]	local

	.data
I2c_DemoCoreSelFlg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_DemoCoreSelFlg:	.data.b	0
	.endo	I2c_DemoCoreSelFlg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_DemoCoreSelFlg
	.section ".mcal_data_asil_d_unspecified_uncached","aw"
I2cCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2cCoreExeFlag:	.data.b	0,255
	.endo	I2cCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2cCoreExeFlag
	.section ".rodata","a"
.L1654:;	"\n\n\n"
	.data.b	10,10,10,0
	.endo	.L1654
.L1655:;	"\n\n  INVALID OPTION"
	.data.b	10,10,32,32
	.data.b	73,78,86,65
	.data.b	76,73,68,32
	.data.b	79,80,84,73
	.data.b	79,78
	.data.b	0
	.endo	.L1655
.L1656:;	"\n  ENTER YOUR OPTION   : "
	.data.b	10,32,32,69
	.data.b	78,84,69,82
	.data.b	32,89,79,85
	.data.b	82,32,79,80
	.data.b	84,73,79,78
	.data.b	32,32,32,58
	.data.b	32,0
	.endo	.L1656
.L1657:;	"\n  <x> : Go back to Main Menu. \n"
	.data.b	10,32,32,60
	.data.b	120,62,32,58
	.data.b	32,71,111,32
	.data.b	98,97,99,107
	.data.b	32,116,111,32
	.data.b	77,97,105,110
	.data.b	32,77,101,110
	.data.b	117,46,32,10
	.data.b	0
	.endo	.L1657
.L1658:;	"\n                                                         "
	.data.b	10,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32
	.data.b	0
	.endo	.L1658
.L1659:;	"\n           I2C DRIVER DEMO MENU V%02d.%02d.%02d            "
	.data.b	10,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	73,50,67,32
	.data.b	68,82,73,86
	.data.b	69,82,32,68
	.data.b	69,77,79,32
	.data.b	77,69,78,85
	.data.b	32,86,37,48
	.data.b	50,100,46,37
	.data.b	48,50,100,46
	.data.b	37,48,50,100
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	0
	.endo	.L1659
.L1660:;	"\n/*********************************************************/"
	.data.b	10,47,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,42
	.data.b	42,42,42,47
	.data.b	0
	.endo	.L1660
.L1661:;	"\n  <1> : Write and read eeprom demo: Send data to eeprom in Core0. "
	.data.b	10,32,32,60
	.data.b	49,62,32,58
	.data.b	32,87,114,105
	.data.b	116,101,32,97
	.data.b	110,100,32,114
	.data.b	101,97,100,32
	.data.b	101,101,112,114
	.data.b	111,109,32,100
	.data.b	101,109,111,58
	.data.b	32,83,101,110
	.data.b	100,32,100,97
	.data.b	116,97,32,116
	.data.b	111,32,101,101
	.data.b	112,114,111,109
	.data.b	32,105,110,32
	.data.b	67,111,114,101
	.data.b	48,46,32,0
	.endo	.L1661
.L1662:;	"\n  <1> : Write and read eeprom demo: Send data to eeprom in Core1. "
	.data.b	10,32,32,60
	.data.b	49,62,32,58
	.data.b	32,87,114,105
	.data.b	116,101,32,97
	.data.b	110,100,32,114
	.data.b	101,97,100,32
	.data.b	101,101,112,114
	.data.b	111,109,32,100
	.data.b	101,109,111,58
	.data.b	32,83,101,110
	.data.b	100,32,100,97
	.data.b	116,97,32,116
	.data.b	111,32,101,101
	.data.b	112,114,111,109
	.data.b	32,105,110,32
	.data.b	67,111,114,101
	.data.b	49,46,32,0
	.endo	.L1662
	.section ".ghcalltbl",""
.L1782:	.data.w	.L1781
	.endo	.L1782
.L1784:	.data.w	.L1783
	.endo	.L1784
.L1786:	.data.w	.L1785
	.endo	.L1786
.L1788:	.data.w	.L1787
	.endo	.L1788
.L1790:	.data.w	.L1789
	.endo	.L1790
.L1792:	.data.w	.L1791
	.endo	.L1792
.L1794:	.data.w	.L1793
	.endo	.L1794
.L1796:	.data.w	.L1795
	.endo	.L1796
.L1798:	.data.w	.L1797
	.endo	.L1798
.L1800:	.data.w	.L1799
	.endo	.L1800
.L1802:	.data.w	.L1801
	.endo	.L1802
	.section ".ghrettbl",""
.L1804:	.data.w	.L1803
	.endo	.L1804
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.I2c_Demo.v.v

	.global	__caller.getChar.i.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.I2c_GetVersionInfo.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
__callee.I2c_DemoEntry.v.v::
	.size	__callee.I2c_DemoEntry.v.v,0
I2c_DemoEntry::
.LDW61:
	str	lr,[sp,-4]!
	sub	sp,sp,20
.LDW71:
.L1809:
	add	r0,sp,8
.L1972:

	bl	I2c_GetVersionInfo
	ldr	r1,.L1770
	mov	r0,0
.L1974:

	bl	TmcPrintf
	ldr	r1,.L1771
	mov	r0,0
.L1976:

	bl	TmcPrintf
	ldrb	r0,[sp,14]
	str	r0,[sp]
	ldr	r1,.L1772
	ldrb	r2,[sp,12]
	mov	r0,0
	ldrb	r3,[sp,13]
.L1978:

	bl	TmcPrintf
	ldr	r1,.L1773
	mov	r0,0
.L1980:

	bl	TmcPrintf
	ldr	r1,.L1970
	mov	r0,0
.L1982:

	bl	TmcPrintf
	ldr	r1,.L1778
	mov	r0,0
.L1984:

	bl	TmcPrintf
	ldr	r1,.L1779
	mov	r0,0
.L1986:

	bl	TmcPrintf
.L1988:

	bl	getChar
	subs	r0,r0,49
	beq	.L1811
	subs	r0,r0,39
	cmpne	r0,32
	beq	.L1805
	ldr	r1,.L1780
	mov	r0,0
.L1990:

	bl	TmcPrintf
	b	.L1809
.L1811:
	ldr	r1,.L1774
	mov	r0,0
	strb	r0,[r1]
	ldr	r1,.L1971
.L1992:

	bl	TmcPrintf
.L1994:

	bl	I2c_DemoSelect
	b	.L1809
.L1805:
.LDW81:
	add	sp,sp,20
.L1996:

	ldr	pc,[sp],4
__ghs_eofn_I2c_DemoEntry::
	.endf	I2c_DemoEntry
;VersionInfo	[sp,8]	local

	.section ".rodata","a"
.L1896:;	"\n  <1> : I2c Channel0 Demo in Core0. "
	.data.b	10,32,32,60
	.data.b	49,62,32,58
	.data.b	32,73,50,99
	.data.b	32,67,104,97
	.data.b	110,110,101,108
	.data.b	48,32,68,101
	.data.b	109,111,32,105
	.data.b	110,32,67,111
	.data.b	114,101,48,46
	.data.b	32,0
	.endo	.L1896
.L1897:;	"\n  Choose the Core0 to running demo. \n"
	.data.b	10,32,32,67
	.data.b	104,111,111,115
	.data.b	101,32,116,104
	.data.b	101,32,67,111
	.data.b	114,101,48,32
	.data.b	116,111,32,114
	.data.b	117,110,110,105
	.data.b	110,103,32,100
	.data.b	101,109,111,46
	.data.b	32,10
	.data.b	0
	.endo	.L1897
	.section ".bss","awb"
.L1898:
	.endo	.L1898
	.section ".ghcalltbl",""
.L1973:	.data.w	.L1972
	.endo	.L1973
.L1975:	.data.w	.L1974
	.endo	.L1975
.L1977:	.data.w	.L1976
	.endo	.L1977
.L1979:	.data.w	.L1978
	.endo	.L1979
.L1981:	.data.w	.L1980
	.endo	.L1981
.L1983:	.data.w	.L1982
	.endo	.L1983
.L1985:	.data.w	.L1984
	.endo	.L1985
.L1987:	.data.w	.L1986
	.endo	.L1987
.L1989:	.data.w	.L1988
	.endo	.L1989
.L1991:	.data.w	.L1990
	.endo	.L1991
.L1993:	.data.w	.L1992
	.endo	.L1993
.L1995:	.data.w	.L1994
	.endo	.L1995
	.section ".ghrettbl",""
.L1997:	.data.w	.L1996
	.endo	.L1997
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.getChar.i.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.I2c_GetVersionInfo.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
__callee.I2c_Demo.v.v::
	.size	__callee.I2c_Demo.v.v,0
I2c_Demo::
.LDW91:
	push	{r5,lr}
.LDW02:
	b	.L2178

.L697:	.data.w	I2c_TransmitData
	.endo	.L697

.L698:	.data.w	I2c_ConfigSet
	.endo	.L698

.L699:	.data.w	I2c_CorexChanneMap
	.endo	.L699

.L700:	.data.w	I2c_UserTransmit
	.endo	.L700

.L701:	.data.w	I2c_UserReceive
	.endo	.L701

.L702:	.data.w	I2c_ReceiveData
	.endo	.L702

.L703:	.data.w	.L588
	.endo	.L703

.L704:	.data.w	.L587
	.endo	.L704

.L1770:	.data.w	.L1654
	.endo	.L1770

.L1771:	.data.w	.L1660
	.endo	.L1771

.L1772:	.data.w	.L1659
	.endo	.L1772

.L1773:	.data.w	.L1658
	.endo	.L1773

.L1774:	.data.w	I2c_DemoCoreSelFlg
	.endo	.L1774

.L1775:	.data.w	.L1661
	.endo	.L1775

.L1776:	.data.w	.L1662
	.endo	.L1776

.L1777:	.data.w	I2cCoreExeFlag
	.endo	.L1777

.L1778:	.data.w	.L1657
	.endo	.L1778

.L1779:	.data.w	.L1656
	.endo	.L1779

.L1780:	.data.w	.L1655
	.endo	.L1780

.L1970:	.data.w	.L1896
	.endo	.L1970

.L1971:	.data.w	.L1897
	.endo	.L1971

.L2178:

;line407
..lin.e0d50a4a..d125afe7.0_2::
.LDWlin2:
..gh.beginasm.6:
	.endo	..gh.beginasm.6
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.7:
	.endo	..gh.endasm.7

;line409
..lin.e0d50a4a..d125afe7.0_3::
.LDWlin3:
	ldr	r1,.L2179
	ldrb	r1,[r1]
	cmp	r1,r0
	ldreq	r5,.L2180
	ldrbeq	r1,[r5]
	cmpeq	r1,1
.L2182:

	popne	{r5,pc}
	ldr	r1,.L2181
	ldr	r0,[r1,r0 lsl 2]
	ldrb	r1,[r0]
	cmp	r1,0
	moveq	r1,1
	strbeq	r1,[r0]
	ldrb	r0,[r5,1]
	cmp	r0,1
.L2184:

	bleq	I2c_WriteReadEeprom
	ldrb	r0,[r5,1]
	cmp	r0,255
	mvnne	r0,0
	strbne	r0,[r5,1]
	movne	r0,0
	strbne	r0,[r5]
.LDW12:
.L2186:

	pop	{r5,pc}
__ghs_eofn_I2c_Demo::
	.endf	I2c_Demo
;CoreId	r0	local

	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
I2c_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_DemoCoreInitStatus:
	.data.w	I2c_DemoInitStatusCore0
	.data.w	I2c_DemoInitStatusCore1
	.space	8
	.endo	I2c_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_DemoCoreInitStatus
	.section ".ghrettbl",""
.L2183:	.data.w	.L2182
	.endo	.L2183
	.section ".ghcalltbl",""
.L2185:	.data.w	.L2184
	.endo	.L2185
	.section ".ghrettbl",""
.L2187:	.data.w	.L2186
	.endo	.L2187
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
I2c_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_DemoInitStatusCore0:	.space	1
	.endo	I2c_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_DemoInitStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
I2c_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.::
I2c_DemoInitStatusCore1:	.space	1
	.endo	I2c_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.endo	I2c_DemoInitStatusCore1
	.section ".mcal_text_asil_d","ax"

.L2179:	.data.w	I2c_DemoCoreSelFlg
	.endo	.L2179

.L2180:	.data.w	I2cCoreExeFlag
	.endo	.L2180

.L2181:	.data.w	I2c_DemoCoreInitStatus
	.endo	.L2181

	.text
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
	.global	__global.use.I2c_ConfigSet.a1_C11.struct.192

;I2c_ConfigSet	I2c_ConfigSet	import
;I2c_DemoInitStatusCore0	I2c_DemoInitStatusCore0	static
;I2c_DemoInitStatusCore1	I2c_DemoInitStatusCore1	static
;I2c_DemoCoreSelFlg	I2c_DemoCoreSelFlg	static
;I2cCoreExeFlag	I2cCoreExeFlag	static
;I2c_TransmitData	I2c_TransmitData	static
;I2c_ReceiveData	I2c_ReceiveData	static
;I2c_UserTransmit	I2c_UserTransmit	static
;I2c_UserReceive	I2c_UserReceive	static
;I2c_CorexChanneMap	I2c_CorexChanneMap	static
;I2c_DemoCoreInitStatus	I2c_DemoCoreInitStatus	static

	.global	I2c_ConfigSet

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
	.section ".mcal_text_asil_d","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
	.text
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	133,8,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,73,50,99,47,73,50,99,95,68,101,109,111,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 31
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+31
	.section	.debug_str		;off: 175
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+175
	.data.b	1,0
	.data.w	.Ldw_line_begin
	.data.w	.Ldw_macinfo_begin
	.data.b	0

	.section	.debug_abbrev		;off: 0
	.data.b	2
	.data.b	17
	.data.b	1
	.data.b	3,14
	.data.b	27,14
	.data.b	37,14
	.data.b	19,5
	.data.b	16,6
	.data.b	67,6
	.data.b	66,11
	.data.b	0,0

	.section	.debug_line		;off: 0
.Ldw_line_begin:
	.data.b	140,10,0,0
	.data.b	2,0
	.data.b	64,9,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,73,50,99,47,73,50,99,95,68,101,109,111,46,99,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,73,50,99,47,73,50,99,95,68,101,109,111,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,83,116,100,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,112,105,108,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,112,105,108,101,114,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,50,99,92,105,110,99,108,117,100,101,92,73,50,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,50,99,92,105,110,99,108,117,100,101,92,73,50,99,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,83,116,97,99,107,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,83,116,97,99,107,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,73,50,99,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,77,99,97,108,108,92,105,110,99,108,117,100,101,92,77,99,97,108,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,77,99,97,108,108,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,77,99,97,108,108,92,105,110,99,108,117,100,101,92,77,99,97,108,108,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,109,117,108,116,105,99,111,114,101,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,67,111,114,101,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,112,117,119,100,116,92,105,110,99,92,99,112,117,119,100,116,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,112,117,119,100,116,92,105,110,99,92,99,112,117,119,100,116,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,67,112,117,119,100,116,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,105,110,99,92,115,97,102,101,119,100,116,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,97,102,101,119,100,116,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,114,99,99,92,105,110,99,92,114,99,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,114,99,99,92,105,110,99,92,114,99,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,82,99,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,77,99,97,108,108,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,50,99,92,105,110,99,92,105,50,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,50,99,92,105,110,99,92,105,50,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,73,50,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,50,99,92,105,110,99,108,117,100,101,92,73,50,99,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,73,50,99,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,67,111,109,109,111,110,92,68,101,109,111,95,67,111,109,109,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,67,111,109,109,111,110,92,68,101,109,111,95,84,101,115,116,84,105,109,101,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,67,111,109,109,111,110,92,68,101,109,111,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,85,97,114,116,92,85,97,114,116,95,68,101,109,111,46,104,0
	.data.b	0,0,0
	.data.b	67,58,92,103,104,115,92,99,111,109,112,95,50,48,50,51,49,52,92,97,110,115,105,92,115,116,100,97,114,103,46,104,0
	.data.b	0,0,0
	.data.b	67,58,92,103,104,115,92,99,111,109,112,95,50,48,50,51,49,52,92,97,110,115,105,92,103,104,115,95,118,97,108,105,115,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,85,97,114,116,92,105,110,99,108,117,100,101,92,85,97,114,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,85,97,114,116,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,85,97,114,116,92,105,110,99,108,117,100,101,92,85,97,114,116,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,97,115,105,92,105,110,99,92,97,115,105,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,97,115,105,92,105,110,99,92,97,115,105,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,65,115,105,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,85,97,114,116,92,105,110,99,108,117,100,101,92,85,97,114,116,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,85,97,114,116,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,85,97,114,116,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	67,58,92,103,104,115,92,99,111,109,112,95,50,48,50,51,49,52,92,97,110,115,105,92,115,116,100,105,110,116,46,104,0
	.data.b	0,0,0
	.data.b	67,58,92,103,104,115,92,99,111,109,112,95,50,48,50,51,49,52,92,97,110,115,105,92,103,104,115,95,97,110,110,101,120,95,107,46,104,0
	.data.b	0,0,0
	.data.b	0
	.section	.debug_macinfo		;off: 0
.Ldw_macinfo_begin:
	.section	.debug_frame		;off: 0
.Ldw_frame_begin:
	.data.b	140,0,0,0
	.data.b	255,255,255,255
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	12
	.data.b	13
	.data.b	0
	.data.b	7
	.data.b	0
	.data.b	7
	.data.b	1
	.data.b	7
	.data.b	2
	.data.b	7
	.data.b	3
	.data.b	7
	.data.b	4
	.data.b	7
	.data.b	5
	.data.b	7
	.data.b	6
	.data.b	7
	.data.b	7
	.data.b	7
	.data.b	8
	.data.b	7
	.data.b	9
	.data.b	7
	.data.b	10
	.data.b	7
	.data.b	11
	.data.b	7
	.data.b	12
	.data.b	7
	.data.b	13
	.data.b	7
	.data.b	14
	.data.b	7
	.data.b	15
	.data.b	7
	.data.b	16
	.data.b	7
	.data.b	17
	.data.b	7
	.data.b	18
	.data.b	7
	.data.b	19
	.data.b	7
	.data.b	20
	.data.b	7
	.data.b	21
	.data.b	7
	.data.b	22
	.data.b	7
	.data.b	23
	.data.b	7
	.data.b	24
	.data.b	7
	.data.b	25
	.data.b	7
	.data.b	26
	.data.b	7
	.data.b	27
	.data.b	7
	.data.b	28
	.data.b	7
	.data.b	29
	.data.b	7
	.data.b	30
	.data.b	7
	.data.b	31
	.data.b	7
	.data.b	32
	.data.b	7
	.data.b	33
	.data.b	7
	.data.b	34
	.data.b	7
	.data.b	35
	.data.b	7
	.data.b	36
	.data.b	7
	.data.b	37
	.data.b	7
	.data.b	38
	.data.b	7
	.data.b	39
	.data.b	7
	.data.b	40
	.data.b	7
	.data.b	41
	.data.b	7
	.data.b	42
	.data.b	7
	.data.b	43
	.data.b	7
	.data.b	44
	.data.b	7
	.data.b	45
	.data.b	7
	.data.b	46
	.data.b	7
	.data.b	47
	.data.b	7
	.data.b	48
	.data.b	7
	.data.b	49
	.data.b	7
	.data.b	50
	.data.b	7
	.data.b	51
	.data.b	7
	.data.b	52
	.data.b	7
	.data.b	53
	.data.b	7
	.data.b	54
	.data.b	7
	.data.b	55
	.data.b	7
	.data.b	56
	.data.b	7
	.data.b	57
	.data.b	7
	.data.b	58
	.data.b	7
	.data.b	59
	.data.b	7
	.data.b	60
	.data.b	7
	.data.b	61
	.data.b	7
	.data.b	62
	.data.b	7
	.data.b	63
	.section	.debug_info		;off: 35
	.data.b	74
	.data.w	.Ldw_begin+643
	.data.b	1

	.section	.debug_abbrev		;off: 19
	.data.b	74
	.data.b	21
	.data.b	1
	.data.b	73,16
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 41
	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 197
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+197
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 28
	.data.b	42
	.data.b	36
	.data.b	0
	.data.b	3,14
	.data.b	62,11
	.data.b	11,11
	.data.b	0,0

	.section	.debug_info		;off: 49
	.data.b	42
	.section	.debug_str		;off: 211
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 50
	.data.w	.Ldw_str_begin+211
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 225
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 57
	.data.w	.Ldw_str_begin+225
	.data.b	7
	.data.b	8

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 39
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 65
	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 244
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 67
	.data.w	.Ldw_str_begin+244
	.data.b	7
	.data.b	2

	.data.b	42
	.section	.debug_str		;off: 259
	.data.b	105,110,116,0
	.section	.debug_info		;off: 74
	.data.w	.Ldw_str_begin+259
	.data.b	5
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	2
	.data.w	.Ldw_begin+428

	.section	.debug_abbrev		;off: 46
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 87
	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 57
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 95
	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+428

	.section	.debug_abbrev		;off: 70
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 110
	.data.b	42
	.section	.debug_str		;off: 263
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 111
	.data.w	.Ldw_str_begin+263
	.data.b	7
	.data.b	4

	.data.b	53
	.data.w	.Ldw_begin+831

	.data.b	47
	.data.w	.Ldw_begin+867

	.section	.debug_abbrev		;off: 77
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 127
	.data.b	53
	.data.w	.Ldw_begin+122

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+953
	.data.b	0

	.section	.debug_abbrev		;off: 84
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 140
	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+132

	.data.b	47
	.data.w	.Ldw_begin+1196

	.data.b	53
	.data.w	.Ldw_begin+146

	.data.b	47
	.data.w	.Ldw_begin+428

	.data.b	47
	.data.w	.Ldw_begin+1251

	.data.b	53
	.data.w	.Ldw_begin+161

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+166

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+156

	.data.b	42
	.section	.debug_str		;off: 276
	.data.b	99,104,97,114,0
	.section	.debug_info		;off: 193
	.data.w	.Ldw_str_begin+276
	.data.b	8
	.data.b	1

	.data.b	53
	.data.w	.Ldw_begin+192

	.data.b	49
	.data.w	.Ldw_begin+1336

	.section	.debug_abbrev		;off: 93
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 209
	.data.b	47
	.data.w	.Ldw_begin+1323

	.data.b	64
	.data.b	0
	.data.b	24
	.data.w	.Ldw_begin+209

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	66
	.data.w	.Ldw_begin+428

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	193,0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+428

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	63

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+156

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+105

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+279

	.data.b	56
	.data.w	.Ldw_begin+73
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+575

	.data.b	47
	.data.w	.Ldw_begin+300

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+305
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+209

	.data.b	47
	.data.w	.Ldw_begin+319

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+324
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+807

	.data.b	47
	.data.w	.Ldw_begin+1107

	.data.b	53
	.data.w	.Ldw_begin+346

	.data.b	47
	.data.w	.Ldw_begin+351

	.data.b	74
	.data.w	.Ldw_begin+476
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+341
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+356
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+452
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+428
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+199
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	76

	.section	.debug_abbrev		;off: 100
	.data.b	76
	.data.b	24
	.data.b	0
	.data.b	0,0

	.section	.debug_info		;off: 408
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+192
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 281
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 417
	.data.w	.Ldw_str_begin+281
	.data.b	51
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+42

	.section	.debug_abbrev		;off: 105
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 428
	.data.b	45
	.section	.debug_str		;off: 289
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 429
	.data.w	.Ldw_str_begin+289
	.data.b	56
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 295
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 441
	.data.w	.Ldw_str_begin+295
	.data.b	60
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+66

	.data.b	45
	.section	.debug_str		;off: 302
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 453
	.data.w	.Ldw_str_begin+302
	.data.b	64
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 309
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 465
	.data.w	.Ldw_str_begin+309
	.data.b	68
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 316
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 477
	.data.w	.Ldw_str_begin+316
	.data.b	39
	.data.b	15
	.data.b	3
	.data.w	.Ldw_begin+428

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 120
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 494
	.data.b	40
	.section	.debug_str		;off: 331
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 495
	.data.w	.Ldw_str_begin+331
	.data.b	63
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+440
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 135
	.data.b	40
	.data.b	13
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	56,10
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 510
	.data.b	40
	.section	.debug_str		;off: 340
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 511
	.data.w	.Ldw_str_begin+340
	.data.b	64
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+440
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 349
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 527
	.data.w	.Ldw_str_begin+349
	.data.b	65
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 366
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 543
	.data.w	.Ldw_str_begin+366
	.data.b	66
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 383
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 559
	.data.w	.Ldw_str_begin+383
	.data.b	67
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 400
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 576
	.data.w	.Ldw_str_begin+400
	.data.b	68
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+488

	.data.b	52
	.section	.debug_str		;off: 420
	.data.b	0
	.section	.debug_info		;off: 588
	.data.w	.Ldw_str_begin+420
	.data.b	36
	.data.b	1
	.data.b	17
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 154
	.data.b	52
	.data.b	4
	.data.b	1
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 597
	.data.b	51
	.section	.debug_str		;off: 421
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 598
	.data.w	.Ldw_str_begin+421
	.data.b	37
	.data.b	5
	.data.b	17
	.data.b	0

	.section	.debug_abbrev		;off: 171
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 606
	.data.b	51
	.section	.debug_str		;off: 438
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 607
	.data.w	.Ldw_str_begin+438
	.data.b	38
	.data.b	5
	.data.b	17
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 455
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 616
	.data.w	.Ldw_str_begin+455
	.data.b	39
	.data.b	5
	.data.b	17
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 472
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 625
	.data.w	.Ldw_str_begin+472
	.data.b	40
	.data.b	5
	.data.b	17
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 489
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 634
	.data.w	.Ldw_str_begin+489
	.data.b	41
	.data.b	5
	.data.b	17
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 506
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 644
	.data.w	.Ldw_str_begin+506
	.data.b	42
	.data.b	3
	.data.b	17
	.data.w	.Ldw_begin+587

	.data.b	45
	.section	.debug_str		;off: 518
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 656
	.data.w	.Ldw_str_begin+518
	.data.b	32
	.data.b	21
	.data.b	16
	.data.w	.Ldw_begin+643

	.data.b	71
	.data.b	183,1
	.data.b	1
	.data.b	36
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 532
	.data.b	101,110,70,105,102,111,0
	.section	.debug_info		;off: 675
	.data.w	.Ldw_str_begin+532
	.data.b	184,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+416
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 539
	.data.b	102,105,102,111,82,120,87,97,116,101,114,77,97,114,107,0
	.section	.debug_info		;off: 692
	.data.w	.Ldw_str_begin+539
	.data.b	185,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 555
	.data.b	102,105,102,111,84,120,87,97,116,101,114,77,97,114,107,0
	.section	.debug_info		;off: 709
	.data.w	.Ldw_str_begin+555
	.data.b	186,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 571
	.data.b	102,105,102,111,65,108,105,103,110,77,111,100,101,0
	.section	.debug_info		;off: 726
	.data.w	.Ldw_str_begin+571
	.data.b	187,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 585
	.data.b	98,117,115,83,112,101,101,100,0
	.section	.debug_info		;off: 743
	.data.w	.Ldw_str_begin+585
	.data.b	188,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 594
	.data.b	100,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 760
	.data.w	.Ldw_str_begin+594
	.data.b	189,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 604
	.data.b	98,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 777
	.data.w	.Ldw_str_begin+604
	.data.b	190,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+452
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 614
	.data.b	73,50,67,95,73,110,105,116,80,97,114,97,109,101,116,101,114,0
	.section	.debug_info		;off: 795
	.data.w	.Ldw_str_begin+614
	.data.b	191,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+667

	.data.b	45
	.section	.debug_str		;off: 632
	.data.b	73,50,99,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 808
	.data.w	.Ldw_str_begin+632
	.data.b	48
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+428

	.data.b	45
	.section	.debug_str		;off: 648
	.data.b	73,50,99,95,72,119,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 820
	.data.w	.Ldw_str_begin+648
	.data.b	51
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+428

	.data.b	45
	.section	.debug_str		;off: 663
	.data.b	73,50,99,95,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 832
	.data.w	.Ldw_str_begin+663
	.data.b	54
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+428

	.data.b	45
	.section	.debug_str		;off: 676
	.data.b	73,50,99,95,83,105,122,101,84,121,112,101,0
	.section	.debug_info		;off: 844
	.data.w	.Ldw_str_begin+676
	.data.b	57
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+440

	.data.b	45
	.section	.debug_str		;off: 689
	.data.b	73,50,99,95,83,108,97,118,101,65,100,100,114,84,121,112,101,0
	.section	.debug_info		;off: 856
	.data.w	.Ldw_str_begin+689
	.data.b	60
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+440

	.data.b	45
	.section	.debug_str		;off: 707
	.data.b	73,50,99,95,73,110,105,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 868
	.data.w	.Ldw_str_begin+707
	.data.b	63
	.data.b	33
	.data.b	10
	.data.w	.Ldw_begin+794

	.data.b	52
	.section	.debug_str		;off: 726
	.data.b	0
	.section	.debug_info		;off: 880
	.data.w	.Ldw_str_begin+726
	.data.b	90
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 727
	.data.b	73,50,67,95,66,85,83,95,69,82,82,0
	.section	.debug_info		;off: 890
	.data.w	.Ldw_str_begin+727
	.data.b	92
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 739
	.data.b	73,50,67,95,79,86,69,82,82,85,78,0
	.section	.debug_info		;off: 899
	.data.w	.Ldw_str_begin+739
	.data.b	94
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 751
	.data.b	73,50,67,95,84,88,95,79,86,69,82,70,76,79,87,0
	.section	.debug_info		;off: 908
	.data.w	.Ldw_str_begin+751
	.data.b	96
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 767
	.data.b	73,50,67,95,82,88,95,85,78,68,69,82,70,76,79,87,0
	.section	.debug_info		;off: 917
	.data.w	.Ldw_str_begin+767
	.data.b	98
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 784
	.data.b	73,50,67,95,78,79,95,65,67,75,0
	.section	.debug_info		;off: 926
	.data.w	.Ldw_str_begin+784
	.data.b	100
	.data.b	5
	.data.b	10
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 795
	.data.b	73,50,67,95,65,82,66,73,84,82,65,84,73,79,78,95,76,79,83,84,0
	.section	.debug_info		;off: 935
	.data.w	.Ldw_str_begin+795
	.data.b	102
	.data.b	5
	.data.b	10
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 816
	.data.b	73,50,67,95,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 944
	.data.w	.Ldw_str_begin+816
	.data.b	104
	.data.b	5
	.data.b	10
	.data.b	6

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 828
	.data.b	73,50,99,95,67,104,97,110,110,101,108,69,114,114,111,114,84,121,112,101,0
	.section	.debug_info		;off: 954
	.data.w	.Ldw_str_begin+828
	.data.b	105
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+879

	.data.b	52
	.section	.debug_str		;off: 849
	.data.b	0
	.section	.debug_info		;off: 966
	.data.w	.Ldw_str_begin+849
	.data.b	109
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 850
	.data.b	73,50,67,95,78,79,95,79,80,69,82,65,84,73,79,78,0
	.section	.debug_info		;off: 976
	.data.w	.Ldw_str_begin+850
	.data.b	110
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 867
	.data.b	73,50,67,95,87,82,73,84,69,0
	.section	.debug_info		;off: 985
	.data.w	.Ldw_str_begin+867
	.data.b	112
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 877
	.data.b	73,50,67,95,82,69,65,68,0
	.section	.debug_info		;off: 994
	.data.w	.Ldw_str_begin+877
	.data.b	114
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 886
	.data.b	73,50,99,95,79,112,101,114,97,116,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 1004
	.data.w	.Ldw_str_begin+886
	.data.b	115
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+965

	.data.b	71
	.data.b	126
	.data.b	1
	.data.b	10
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 904
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 1022
	.data.w	.Ldw_str_begin+904
	.data.b	128,1
	.data.b	26
	.data.b	10
	.data.w	.Ldw_begin+117
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 912
	.data.b	65,100,100,114,101,115,115,77,111,100,101,0
	.section	.debug_info		;off: 1039
	.data.w	.Ldw_str_begin+912
	.data.b	130,1
	.data.b	25
	.data.b	10
	.data.w	.Ldw_begin+416
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 924
	.data.b	83,105,122,101,0
	.section	.debug_info		;off: 1056
	.data.w	.Ldw_str_begin+924
	.data.b	132,1
	.data.b	25
	.data.b	10
	.data.w	.Ldw_begin+843
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 929
	.data.b	83,108,97,118,101,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 1073
	.data.w	.Ldw_str_begin+929
	.data.b	134,1
	.data.b	25
	.data.b	10
	.data.w	.Ldw_begin+855
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 942
	.data.b	68,105,114,97,99,116,105,111,110,0
	.section	.debug_info		;off: 1090
	.data.w	.Ldw_str_begin+942
	.data.b	136,1
	.data.b	25
	.data.b	10
	.data.w	.Ldw_begin+1003
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 952
	.data.b	73,50,99,95,84,114,97,110,115,68,97,116,97,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1108
	.data.w	.Ldw_str_begin+952
	.data.b	137,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1015

	.data.b	71
	.data.b	163,1
	.data.b	1
	.data.b	10
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 974
	.data.b	72,119,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 1128
	.data.w	.Ldw_str_begin+974
	.data.b	165,1
	.data.b	38
	.data.b	10
	.data.w	.Ldw_begin+127
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 986
	.data.b	73,50,99,95,78,111,116,105,102,70,117,110,99,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 1145
	.data.w	.Ldw_str_begin+986
	.data.b	167,1
	.data.b	12
	.data.b	10
	.data.w	.Ldw_begin+141
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1007
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 1162
	.data.w	.Ldw_str_begin+1007
	.data.b	169,1
	.data.b	37
	.data.b	10
	.data.w	.Ldw_begin+819
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1016
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 1179
	.data.w	.Ldw_str_begin+1016
	.data.b	171,1
	.data.b	37
	.data.b	10
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	9
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1026
	.data.b	73,50,99,95,67,104,97,110,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1197
	.data.w	.Ldw_str_begin+1026
	.data.b	172,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1120

	.data.b	71
	.data.b	176,1
	.data.b	1
	.data.b	10
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1048
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 1217
	.data.w	.Ldw_str_begin+1048
	.data.b	178,1
	.data.b	44
	.data.b	10
	.data.w	.Ldw_begin+151
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1065
	.data.b	67,111,114,101,77,97,120,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 1234
	.data.w	.Ldw_str_begin+1065
	.data.b	180,1
	.data.b	37
	.data.b	10
	.data.w	.Ldw_begin+156
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1081
	.data.b	73,50,99,95,73,110,105,116,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1252
	.data.w	.Ldw_str_begin+1081
	.data.b	181,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1209

	.data.b	71
	.data.b	185,1
	.data.b	1
	.data.b	10
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1104
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 1272
	.data.w	.Ldw_str_begin+1104
	.data.b	187,1
	.data.b	38
	.data.b	10
	.data.w	.Ldw_begin+171
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1118
	.data.b	67,104,97,110,110,101,108,73,100,84,111,67,111,114,101,67,104,73,100,80,116,114,0
	.section	.debug_info		;off: 1289
	.data.w	.Ldw_str_begin+1118
	.data.b	189,1
	.data.b	38
	.data.b	10
	.data.w	.Ldw_begin+187
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1141
	.data.b	72,119,85,110,105,116,84,111,67,104,97,110,110,101,108,73,100,80,116,114,0
	.section	.debug_info		;off: 1306
	.data.w	.Ldw_str_begin+1141
	.data.b	191,1
	.data.b	38
	.data.b	10
	.data.w	.Ldw_begin+187
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1162
	.data.b	73,50,99,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1324
	.data.w	.Ldw_str_begin+1162
	.data.b	192,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1264

	.data.b	71
	.data.b	36
	.data.b	1
	.data.b	1
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1177
	.data.b	67,111,114,101,67,109,100,69,120,105,115,116,0
	.section	.debug_info		;off: 1343
	.data.w	.Ldw_str_begin+1177
	.data.b	37
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1190
	.data.b	67,111,114,101,69,120,101,67,109,100,0
	.section	.debug_info		;off: 1359
	.data.w	.Ldw_str_begin+1190
	.data.b	38
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1201
	.data.b	73,50,99,95,67,104,97,110,110,101,108,67,111,114,101,69,120,101,84,121,112,101,0
	.section	.debug_info		;off: 1376
	.data.w	.Ldw_str_begin+1201
	.data.b	39
	.data.b	3
	.data.b	1
	.data.w	.Ldw_begin+204

	.data.b	8
	.section	.debug_str		;off: 1224
	.data.b	73,50,99,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 1388
	.data.w	.Ldw_str_begin+1224
	.data.b	33
	.data.b	29
	.data.b	40
	.data.w	.Ldw_begin+214
	.data.b	1
	.data.b	1

	.section	.debug_abbrev		;off: 186
	.data.b	8
	.data.b	52
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	63,12
	.data.b	60,12
	.data.b	0,0

	.section	.debug_info		;off: 1401
	.data.b	6
	.section	.debug_str		;off: 1238
	.data.b	73,50,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 1402
	.data.w	.Ldw_str_begin+1238
	.data.b	46
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.section	.debug_abbrev		;off: 205
	.data.b	6
	.data.b	52
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	63,12
	.data.b	60,12
	.data.b	2,10
	.data.b	0,0

	.section	.debug_info		;off: 1421
	.data.b	6
	.section	.debug_str		;off: 1262
	.data.b	73,50,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 1422
	.data.w	.Ldw_str_begin+1262
	.data.b	52
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1286
	.data.b	73,50,99,95,68,101,109,111,67,111,114,101,83,101,108,70,108,103,0
	.section	.debug_info		;off: 1442
	.data.w	.Ldw_str_begin+1286
	.data.b	59
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_DemoCoreSelFlg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1305
	.data.b	73,50,99,67,111,114,101,69,120,101,70,108,97,103,0
	.section	.debug_info		;off: 1462
	.data.w	.Ldw_str_begin+1305
	.data.b	67
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1375
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2cCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1320
	.data.b	73,50,99,95,84,114,97,110,115,109,105,116,68,97,116,97,0
	.section	.debug_info		;off: 1482
	.data.w	.Ldw_str_begin+1320
	.data.b	69
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+230
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_TransmitData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1337
	.data.b	73,50,99,95,82,101,99,101,105,118,101,68,97,116,97,0
	.section	.debug_info		;off: 1502
	.data.w	.Ldw_str_begin+1337
	.data.b	70
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+247
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_ReceiveData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1353
	.data.b	73,50,99,95,85,115,101,114,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 1522
	.data.w	.Ldw_str_begin+1353
	.data.b	72
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1107
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_UserTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1370
	.data.b	73,50,99,95,85,115,101,114,82,101,99,101,105,118,101,0
	.section	.debug_info		;off: 1542
	.data.w	.Ldw_str_begin+1370
	.data.b	80
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1107
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_UserReceive..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1386
	.data.b	73,50,99,95,67,111,114,101,120,67,104,97,110,110,101,77,97,112,0
	.section	.debug_info		;off: 1562
	.data.w	.Ldw_str_begin+1386
	.data.b	96
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+263
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_CorexChanneMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	6
	.section	.debug_str		;off: 1405
	.data.b	73,50,99,95,68,101,109,111,67,111,114,101,73,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 1582
	.data.w	.Ldw_str_begin+1405
	.data.b	102
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+284
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	I2c_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.

	.data.b	27
	.section	.debug_str		;off: 1428
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1602
	.data.w	.Ldw_str_begin+1428
	.data.b	63
	.data.b	31
	.data.b	17
	.data.w	.Ldw_begin+643
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 226
	.data.b	27
	.data.b	46
	.data.b	1
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	60,12
	.data.b	32,11
	.data.b	63,12
	.data.b	50,11
	.data.b	76,11
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 1619
	.data.b	37

	.section	.debug_abbrev		;off: 253
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 1620
	.data.b	8
	.section	.debug_str		;off: 1448
	.data.b	105,100,0
	.section	.debug_info		;off: 1621
	.data.w	.Ldw_str_begin+1448
	.data.b	65
	.data.b	17
	.data.b	17
	.data.w	.Ldw_begin+643
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1451
	.data.b	73,50,99,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 1637
	.data.w	.Ldw_str_begin+1451
	.data.b	122
	.data.b	36
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 258
	.data.b	26
	.data.b	46
	.data.b	1
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	60,12
	.data.b	32,11
	.data.b	63,12
	.data.b	50,11
	.data.b	76,11
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 1650
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1470
	.data.b	73,50,99,95,73,110,105,116,0
	.section	.debug_info		;off: 1652
	.data.w	.Ldw_str_begin+1470
	.data.b	129,1
	.data.b	36
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1479
	.data.b	73,50,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 1668
	.data.w	.Ldw_str_begin+1479
	.data.b	135,1
	.data.b	36
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1490
	.data.b	73,50,99,95,83,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 1684
	.data.w	.Ldw_str_begin+1490
	.data.b	141,1
	.data.b	46
	.data.b	9
	.data.w	.Ldw_begin+476
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1507
	.data.b	84,105,109,101,114,95,68,101,108,97,121,77,115,0
	.section	.debug_info		;off: 1704
	.data.w	.Ldw_str_begin+1507
	.data.b	51
	.data.b	13
	.data.b	42
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1521
	.data.b	84,109,99,80,114,105,110,116,102,0
	.section	.debug_info		;off: 1719
	.data.w	.Ldw_str_begin+1521
	.data.b	176,1
	.data.b	14
	.data.b	44
	.data.w	.Ldw_begin+428
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1531
	.data.b	103,101,116,67,104,97,114,0
	.section	.debug_info		;off: 1739
	.data.w	.Ldw_str_begin+1531
	.data.b	177,1
	.data.b	13
	.data.b	44
	.data.w	.Ldw_begin+192
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1539
	.data.b	73,50,99,95,87,114,105,116,101,82,101,97,100,69,101,112,114,111,109,0
	.section	.debug_info		;off: 1759
	.data.w	.Ldw_str_begin+1539
	.data.b	156,1
	.data.b	13
	.data.b	1
	.data.w	I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.w	__ghs_eofn_I2c_WriteReadEeprom
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	36
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 283
	.data.b	24
	.data.b	46
	.data.b	1
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	17,1
	.data.b	18,1
	.data.b	64,10
	.data.b	131,65
	.data.b	15
	.data.b	135,65
	.data.b	13
	.data.b	133,65
	.data.b	15
	.data.b	134,65
	.data.b	13
	.data.b	146,65
	.data.b	15
	.data.b	60,12
	.data.b	32,11
	.data.b	63,12
	.data.b	50,11
	.data.b	76,11
	.data.b	39,12
	.data.b	0,0

	.section	.debug_frame		;off: 144
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.w	__ghs_eofn_I2c_WriteReadEeprom-I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2378
	.data.b	0,5,2
	.data.w	I2c_WriteReadEeprom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.b	6
	.data.b	3
	.data.b	156,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	13
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	92
	.data.b	43
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	27
	.data.b	44
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	75
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 1790
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 329
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 1799
	.data.b	7
	.section	.debug_str		;off: 1559
	.data.b	82,101,103,65,100,100,114,0
	.section	.debug_info		;off: 1800
	.data.w	.Ldw_str_begin+1559
	.data.b	158,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+440
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 338
	.data.b	7
	.data.b	52
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	63,12
	.data.b	60,12
	.data.b	2,6
	.data.b	0,0

	.section	.debug_info		;off: 1818
	.data.b	7
	.section	.debug_str		;off: 1567
	.data.b	65,100,100,114,66,117,102,0
	.section	.debug_info		;off: 1819
	.data.w	.Ldw_str_begin+1567
	.data.b	159,1
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+80
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1837
	.data.b	7
	.section	.debug_str		;off: 1575
	.data.b	108,111,111,112,67,111,117,110,116,0
	.section	.debug_info		;off: 1838
	.data.w	.Ldw_str_begin+1575
	.data.b	160,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+452
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+39
	.section	.debug_loc		;off: 39
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1856
	.data.b	7
	.section	.debug_str		;off: 1585
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 1857
	.data.w	.Ldw_str_begin+1585
	.data.b	161,1
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+476
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+58
	.section	.debug_loc		;off: 58
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1875
	.data.b	7
	.section	.debug_str		;off: 1595
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 1876
	.data.w	.Ldw_str_begin+1595
	.data.b	162,1
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+655
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+77
	.section	.debug_loc		;off: 77
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1894
	.data.b	7
	.section	.debug_str		;off: 1602
	.data.b	99,111,109,112,97,114,101,82,101,115,117,108,116,0
	.section	.debug_info		;off: 1895
	.data.w	.Ldw_str_begin+1602
	.data.b	163,1
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+416
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+96
	.section	.debug_loc		;off: 96
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1913
	.data.b	7
	.section	.debug_str		;off: 1616
	.data.b	83,101,110,100,82,101,103,105,115,116,101,114,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 1914
	.data.w	.Ldw_str_begin+1616
	.data.b	164,1
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1107
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+115
	.section	.debug_loc		;off: 115
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1932
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1636
	.data.b	73,50,99,95,68,101,109,111,83,101,108,101,99,116,0
	.section	.debug_info		;off: 1935
	.data.w	.Ldw_str_begin+1636
	.data.b	252,1
	.data.b	13
	.data.b	1
	.data.w	I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.w	__ghs_eofn_I2c_DemoSelect
	.data.b	1
	.data.b	93
	.data.b	144,128,1
	.data.b	124
	.data.b	0
	.data.b	20
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.w	__ghs_eofn_I2c_DemoSelect-I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2505
	.data.b	0,5,2
	.data.w	I2c_DemoSelect..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CI2c_Demo.
	.data.b	6
	.data.b	3
	.data.b	252,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	59
	.data.b	124
	.data.b	59
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	91
	.data.b	60
	.data.b	29
	.data.b	43
	.data.b	12
	.data.b	45
	.data.b	44
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	77
	.data.b	11
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 1966
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 1651
	.data.b	67,109,100,0
	.section	.debug_info		;off: 1976
	.data.w	.Ldw_str_begin+1651
	.data.b	254,1
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+135
	.section	.debug_loc		;off: 135
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1994
	.data.b	8
	.section	.debug_str		;off: 1655
	.data.b	69,120,105,116,0
	.section	.debug_info		;off: 1995
	.data.w	.Ldw_str_begin+1655
	.data.b	255,1
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1660
	.data.b	86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 2010
	.data.w	.Ldw_str_begin+1660
	.data.b	128,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+575
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+154
	.section	.debug_loc		;off: 154
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2028
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1672
	.data.b	73,50,99,95,68,101,109,111,69,110,116,114,121,0
	.section	.debug_info		;off: 2031
	.data.w	.Ldw_str_begin+1672
	.data.b	206,2
	.data.b	6
	.data.b	1
	.data.w	I2c_DemoEntry
	.data.w	__ghs_eofn_I2c_DemoEntry
	.data.b	1
	.data.b	93
	.data.b	128,128,1
	.data.b	0
	.data.b	0
	.data.b	20
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	I2c_DemoEntry
	.data.w	__ghs_eofn_I2c_DemoEntry-I2c_DemoEntry
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2567
	.data.b	0,5,2
	.data.w	I2c_DemoEntry
	.data.b	6
	.data.b	3
	.data.b	206,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	59
	.data.b	124
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	61
	.data.b	28
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 2062
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	8
	.section	.debug_str		;off: 1686
	.data.b	67,109,100,0
	.section	.debug_info		;off: 2072
	.data.w	.Ldw_str_begin+1686
	.data.b	208,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1690
	.data.b	69,120,105,116,0
	.section	.debug_info		;off: 2087
	.data.w	.Ldw_str_begin+1690
	.data.b	209,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+428
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1695
	.data.b	86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 2102
	.data.w	.Ldw_str_begin+1695
	.data.b	210,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+575
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+174
	.section	.debug_loc		;off: 174
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2120
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1707
	.data.b	73,50,99,95,68,101,109,111,0
	.section	.debug_info		;off: 2123
	.data.w	.Ldw_str_begin+1707
	.data.b	147,3
	.data.b	6
	.data.b	1
	.data.w	I2c_Demo
	.data.w	__ghs_eofn_I2c_Demo
	.data.b	1
	.data.b	93
	.data.b	160,128,1
	.data.b	124
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	I2c_Demo
	.data.w	__ghs_eofn_I2c_Demo-I2c_Demo
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2634
	.data.b	0,5,2
	.data.w	I2c_Demo
	.data.b	6
	.data.b	3
	.data.b	147,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	123
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	45
	.data.b	11
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	44
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2154
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 1716
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 2164
	.data.w	.Ldw_str_begin+1716
	.data.b	149,3
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+655
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+194
	.section	.debug_loc		;off: 194
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2182
	.data.b	0

	.data.b	0

	.data.b	0

	.section	.debug_macinfo		;off: 0
	.data.b	1
	.data.b	0
	.data.b	95,95,103,104,115,95,95,32,49,0
	.data.b	1
	.data.b	0
	.data.b	95,95,65,82,77,32,49,0
	.data.b	1
	.data.b	0
	.data.b	95,95,103,104,115,95,97,108,105,103,110,109,101,110,116,32,56,0
	.data.b	1
	.data.b	0
	.data.b	95,95,103,104,115,95,109,97,120,95,112,97,99,107,95,118,97,108,117,101,32,56,0
	.data.b	1
	.data.b	0
	.data.b	95,95,67,72,65,82,95,66,73,84,32,56,0
	.data.b	1
	.data.b	0
	.data.b	95,95,83,72,82,84,95,66,73,84,32,49,54,0
	.data.b	1
	.data.b	0
	.data.b	95,95,73,78,84,95,66,73,84,32,51,50,0
	.data.b	1
	.data.b	0
	.data.b	95,95,76,79,78,71,95,66,73,84,32,51,50,0
	.data.b	1
	.data.b	0
	.data.b	95,95,87,67,72,65,82,95,66,73,84,32,49,54,0
	.data.b	1
	.data.b	0
	.data.b	95,95,80,84,82,95,66,73,84,32,51,50,0
	.data.b	1
	.data.b	0
	.data.b	95,95,76,76,79,78,71,95,66,73,84,32,54,52,0
	.data.b	1
	.data.b	0
	.data.b	95,95,82,69,71,95,66,73,84,32,51,50,0
	.data.b	1
	.data.b	0
	.data.b	95,95,87,67,104,97,114,95,73,115,95,85,110,115,105,103,110,101,100,95,95,32,49,0
	.data.b	1
	.data.b	0
	.data.b	84,72,65,54,95,84,72,65,54,52,49,50,32,49,0
	.data.b	1
	.data.b	0
	.data.b	65,85,84,79,83,65,82,95,79,83,95,78,79,84,95,85,83,69,68,32,49,0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	26
	.data.b	2
	.data.b	3
	.data.b	27
	.data.b	3
	.data.b	3
	.data.b	25
	.data.b	4
	.data.b	3
	.data.b	31
	.data.b	5
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	7
	.data.b	1
	.data.b	26
	.data.b	83,84,82,73,78,71,73,70,89,40,120,41,32,35,120,0
	.data.b	1
	.data.b	30
	.data.b	69,88,80,65,78,68,95,80,82,65,71,77,65,40,120,41,32,95,80,114,97,103,109,97,40,83,84,82,73,78,71,73,70,89,40,120,41,41,0
	.data.b	1
	.data.b	38
	.data.b	65,83,77,95,86,79,76,65,84,73,76,69,32,95,95,97,115,109,32,118,111,108,97,116,105,108,101,0
	.data.b	1
	.data.b	43
	.data.b	73,78,76,73,78,69,32,95,95,105,110,108,105,110,101,0
	.data.b	1
	.data.b	47
	.data.b	76,79,67,65,76,95,73,78,76,73,78,69,32,115,116,97,116,105,99,32,95,95,105,110,108,105,110,101,0
	.data.b	1
	.data.b	51
	.data.b	76,79,67,65,76,95,70,79,82,67,69,73,78,76,73,78,69,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,97,108,119,97,121,115,95,105,110,108,105,110,101,41,41,32,115,116,97,116,105,99,32,95,95,105,110
	.data.b	108,105,110,101,0
	.data.b	1
	.data.b	88
	.data.b	77,69,77,77,65,80,95,83,84,65,82,84,95,66,83,83,40,83,101,99,116,105,111,110,78,97,109,101,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,98,115,115,32
	.data.b	61,32,83,101,99,116,105,111,110,78,97,109,101,41,0
	.data.b	1
	.data.b	91
	.data.b	77,69,77,77,65,80,95,83,84,79,80,95,66,83,83,40,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,98,115,115,32,61,32,100,101,102,97,117,108,116,41,0
	.data.b	1
	.data.b	95
	.data.b	77,69,77,77,65,80,95,83,84,65,82,84,95,82,79,68,65,84,65,40,83,101,99,116,105,111,110,78,97,109,101,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,114
	.data.b	111,100,97,116,97,32,61,32,83,101,99,116,105,111,110,78,97,109,101,41,0
	.data.b	1
	.data.b	98
	.data.b	77,69,77,77,65,80,95,83,84,79,80,95,82,79,68,65,84,65,40,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,114,111,100,97,116,97,32,61,32,100,101,102,97
	.data.b	117,108,116,41,0
	.data.b	1
	.data.b	102
	.data.b	77,69,77,77,65,80,95,83,84,65,82,84,95,68,65,84,65,40,83,101,99,116,105,111,110,78,97,109,101,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,100,97,116
	.data.b	97,32,61,32,83,101,99,116,105,111,110,78,97,109,101,41,0
	.data.b	1
	.data.b	105
	.data.b	77,69,77,77,65,80,95,83,84,79,80,95,68,65,84,65,40,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,100,97,116,97,32,61,32,100,101,102,97,117,108,116,41
	.data.b	0
	.data.b	1
	.data.b	109
	.data.b	77,69,77,77,65,80,95,83,84,65,82,84,95,84,69,88,84,40,83,101,99,116,105,111,110,78,97,109,101,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,116,101,120
	.data.b	116,32,61,32,83,101,99,116,105,111,110,78,97,109,101,41,0
	.data.b	1
	.data.b	112
	.data.b	77,69,77,77,65,80,95,83,84,79,80,95,84,69,88,84,40,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,116,101,120,116,32,61,32,100,101,102,97,117,108,116,41
	.data.b	0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	95,71,72,83,95,67,95,84,72,65,54,95,32,0
	.data.b	1
	.data.b	135,2
	.data.b	78,85,76,76,95,80,84,82,32,40,40,118,111,105,100,32,42,41,48,41,0
	.data.b	1
	.data.b	151,2
	.data.b	70,85,78,67,40,114,101,116,116,121,112,101,44,109,101,109,99,108,97,115,115,41,32,114,101,116,116,121,112,101,0
	.data.b	1
	.data.b	164,2
	.data.b	80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,0
	.data.b	1
	.data.b	190,2
	.data.b	67,79,78,83,84,80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116,0
	.data.b	1
	.data.b	203,2
	.data.b	67,79,78,83,84,80,50,67,79,78,83,84,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,99,111,110,115,116,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116
	.data.b	0
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	8
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	83,84,68,95,79,78,32,48,120,48,49,117,0
	.data.b	1
	.data.b	47
	.data.b	83,84,68,95,79,70,70,32,48,120,48,48,117,0
	.data.b	1
	.data.b	52
	.data.b	69,95,79,75,32,40,83,116,100,95,82,101,116,117,114,110,84,121,112,101,41,40,48,120,48,48,117,41,0
	.data.b	4
	.data.b	3
	.data.b	28
	.data.b	9
	.data.b	3
	.data.b	40
	.data.b	10
	.data.b	3
	.data.b	37
	.data.b	11
	.data.b	3
	.data.b	24
	.data.b	12
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	13
	.data.b	1
	.data.b	54
	.data.b	73,50,67,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	61
	.data.b	73,50,67,95,67,70,71,95,68,69,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	68
	.data.b	73,50,67,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	87
	.data.b	73,50,67,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	116
	.data.b	73,50,99,67,111,110,102,95,73,50,99,67,104,97,110,110,101,108,95,73,50,99,67,104,97,110,110,101,108,95,48,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	14
	.data.b	3
	.data.b	39
	.data.b	15
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	16
	.data.b	3
	.data.b	26
	.data.b	17
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	80
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	82
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	19
	.data.b	3
	.data.b	28
	.data.b	20
	.data.b	3
	.data.b	22
	.data.b	21
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	22
	.data.b	3
	.data.b	56
	.data.b	23
	.data.b	1
	.data.b	85
	.data.b	82,67,67,95,66,65,83,69,95,65,68,68,82,32,48,120,67,48,48,48,48,48,48,48,85,0
	.data.b	1
	.data.b	89
	.data.b	82,67,67,95,82,69,83,69,84,95,79,70,70,83,69,84,95,65,68,68,82,32,48,120,48,56,48,48,85,0
	.data.b	1
	.data.b	99
	.data.b	82,67,67,95,82,69,83,69,84,32,40,40,82,67,67,95,82,69,83,69,84,95,77,79,68,85,76,69,32,42,41,40,82,67,67,95,66,65,83,69,95,65,68,68,82,32,43,32,82,67,67,95,82,69,83,69,84,95,79,70
	.data.b	70,83,69,84,95,65,68,68,82,41,41,0
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	152,1
	.data.b	67,80,85,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	154,1
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,67,80,85,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	168,3
	.data.b	67,80,85,87,68,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	170,3
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	25
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	26
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	169,3
	.data.b	83,65,70,69,87,68,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	171,3
	.data.b	26
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	27
	.data.b	3
	.data.b	34
	.data.b	28
	.data.b	3
	.data.b	31
	.data.b	29
	.data.b	1
	.data.b	70
	.data.b	71,69,84,95,67,80,54,52,40,99,112,44,111,112,49,44,82,116,44,67,82,109,41,32,123,117,105,110,116,51,50,32,118,97,108,49,95,116,101,109,112,32,61,32,48,85,44,32,118,97,108,50,95,116,101,109,112,32,61,32
	.data.b	48,85,59,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,82,82,67,32,112,34,32,35,99,112,32,34,44,32,34,32,35,111,112,49,32,34,44,32,37,48,44,32,37,49,44,32,99,34,32,35,67,82,109,32,58
	.data.b	32,34,61,114,34,40,118,97,108,49,95,116,101,109,112,41,44,32,34,61,114,34,40,118,97,108,50,95,116,101,109,112,41,58,32,58,32,34,109,101,109,111,114,121,34,41,59,32,82,116,32,61,32,40,40,40,117,105,110,116
	.data.b	54,52,41,118,97,108,50,95,116,101,109,112,41,32,60,60,32,51,50,41,32,43,32,118,97,108,49,95,116,101,109,112,59,125,0
	.data.b	4
	.data.b	1
	.data.b	66
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	30
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	94
	.data.b	83,84,77,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	219,1
	.data.b	83,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	221,1
	.data.b	30
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	31
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	30
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	178,4
	.data.b	83,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	180,4
	.data.b	30
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	32
	.data.b	3
	.data.b	38
	.data.b	33
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	34
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	144,13
	.data.b	82,67,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	146,13
	.data.b	34
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	110
	.data.b	77,99,97,108,95,71,101,116,67,111,114,101,73,100,40,41,32,77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,40,41,0
	.data.b	1
	.data.b	145,1
	.data.b	77,67,65,76,95,67,79,82,69,48,32,40,77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,41,0
	.data.b	1
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	35
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	136,2
	.data.b	77,67,65,76,76,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	137,2
	.data.b	35
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	36
	.data.b	3
	.data.b	27
	.data.b	37
	.data.b	4
	.data.b	1
	.data.b	214,1
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	215,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	137,3
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	138,3
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	39
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	40
	.data.b	4
	.data.b	1
	.data.b	118
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	119
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	153,1
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	154,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	48
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	49
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	54
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	55
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	28
	.data.b	41
	.data.b	1
	.data.b	22
	.data.b	68,69,77,79,95,67,79,77,77,79,78,95,72,95,32,0
	.data.b	3
	.data.b	29
	.data.b	42
	.data.b	4
	.data.b	3
	.data.b	30
	.data.b	43
	.data.b	4
	.data.b	1
	.data.b	38
	.data.b	68,69,77,79,95,80,82,73,78,84,95,85,65,82,84,32,40,48,85,41,0
	.data.b	1
	.data.b	39
	.data.b	68,69,77,79,95,80,82,73,78,84,95,84,79,79,76,67,72,65,73,78,32,40,49,85,41,0
	.data.b	1
	.data.b	40
	.data.b	68,69,77,79,95,78,79,95,80,82,73,78,84,32,40,50,53,53,85,41,0
	.data.b	1
	.data.b	41
	.data.b	68,69,77,79,95,80,82,73,78,84,95,77,69,84,72,79,68,32,40,68,69,77,79,95,80,82,73,78,84,95,85,65,82,84,41,0
	.data.b	1
	.data.b	44
	.data.b	68,69,77,79,95,80,82,73,78,84,81,85,69,85,69,77,79,68,69,32,83,84,68,95,79,78,0
	.data.b	3
	.data.b	66
	.data.b	44
	.data.b	3
	.data.b	35
	.data.b	45
	.data.b	1
	.data.b	20
	.data.b	95,83,84,68,65,82,71,95,72,32,0
	.data.b	3
	.data.b	38
	.data.b	46
	.data.b	1
	.data.b	31
	.data.b	95,95,95,103,104,115,95,100,105,100,95,112,97,99,107,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	47
	.data.b	3
	.data.b	36
	.data.b	48
	.data.b	1
	.data.b	54
	.data.b	85,65,82,84,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	60
	.data.b	85,65,82,84,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	74
	.data.b	85,65,82,84,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	103
	.data.b	85,65,82,84,95,67,70,71,95,82,88,95,73,78,84,69,82,82,85,80,84,95,69,78,65,66,76,69,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	111
	.data.b	85,65,82,84,95,67,70,71,95,84,88,95,73,78,84,69,82,82,85,80,84,95,69,78,65,66,76,69,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	119
	.data.b	85,65,82,84,95,67,70,71,95,69,82,82,79,82,95,73,78,84,69,82,82,85,80,84,95,69,78,65,66,76,69,32,40,83,84,68,95,79,70,70,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	49
	.data.b	3
	.data.b	41
	.data.b	50
	.data.b	3
	.data.b	26
	.data.b	51
	.data.b	4
	.data.b	1
	.data.b	239,2
	.data.b	65,83,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	241,2
	.data.b	52
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,83,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	135,6
	.data.b	65,83,73,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	137,6
	.data.b	52
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	53
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	54
	.data.b	4
	.data.b	1
	.data.b	140,1
	.data.b	85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	142,1
	.data.b	55
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	211,1
	.data.b	85,65,82,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	213,1
	.data.b	55
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	41
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	56
	.data.b	1
	.data.b	20
	.data.b	95,95,71,72,83,95,83,84,68,73,78,84,95,72,32,0
	.data.b	1
	.data.b	156,1
	.data.b	95,95,95,70,65,83,84,51,50,32,105,110,116,0
	.data.b	1
	.data.b	157,1
	.data.b	95,95,95,70,65,83,84,51,50,95,66,73,84,32,95,95,82,69,71,95,66,73,84,0
	.data.b	1
	.data.b	136,2
	.data.b	95,95,95,73,76,52,56,66,73,84,32,95,95,76,76,79,78,71,95,66,73,84,0
	.data.b	1
	.data.b	168,2
	.data.b	95,95,95,73,76,54,52,66,73,84,32,95,95,76,76,79,78,71,95,66,73,84,0
	.data.b	1
	.data.b	143,3
	.data.b	95,95,95,73,77,66,73,84,32,95,95,76,76,79,78,71,95,66,73,84,0
	.data.b	3
	.data.b	187,4
	.data.b	57
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	68
	.data.b	80,82,73,78,84,70,95,69,65,67,72,95,66,85,70,70,69,82,95,76,69,78,32,40,50,53,54,85,41,0
	.data.b	1
	.data.b	138,1
	.data.b	85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	139,1
	.data.b	55
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	180,1
	.data.b	85,65,82,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	181,1
	.data.b	55
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	67
	.data.b	68,69,66,85,71,95,80,82,73,78,84,70,40,102,109,116,44,95,95,86,65,95,65,82,71,83,95,95,46,46,46,41,32,40,118,111,105,100,41,84,109,99,80,114,105,110,116,102,40,78,85,76,76,95,80,84,82,44,32,40
	.data.b	99,111,110,115,116,32,117,105,110,116,56,32,42,41,102,109,116,44,32,35,35,32,95,95,86,65,95,65,82,71,83,95,95,41,0
	.data.b	1
	.data.b	69
	.data.b	68,69,66,85,71,95,71,69,84,67,40,41,32,103,101,116,67,104,97,114,40,41,0
	.data.b	4
	.data.b	1
	.data.b	33
	.data.b	69,69,80,82,79,77,95,80,65,71,69,95,83,90,32,40,54,52,85,41,0
	.data.b	1
	.data.b	44
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	45
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	50
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	51
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	53
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	54
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	56
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	57
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	61
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	62
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	64
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65,66,76
	.data.b	69,32,0
	.data.b	3
	.data.b	65
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,8
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67
	.data.b	65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	240,8
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	89
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65,66,76,69
	.data.b	32,0
	.data.b	3
	.data.b	90
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	93
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	108
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	109
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	125
	.data.b	73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	126
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,50,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	182,3
	.data.b	73,50,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	183,3
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 359
	.data.b	0
