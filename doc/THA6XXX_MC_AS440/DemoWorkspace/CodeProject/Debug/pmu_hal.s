	.section ".sdk_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682577..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.:
PMU_Hal_IsRightEvent:
.LDW01:
	mov	r1,r0
.LDW11:
	tst	r0,8
	mov	r0,0
	tsteq	r1,4
	tsteq	r1,2
	tsteq	r1,1
	movne	r0,1
.LDW21:
.L136:

	ret	
__ghs_eofn_PMU_Hal_IsRightEvent:
	.endf	PMU_Hal_IsRightEvent
	.endf	PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
;bRet	r0	local

;uCntIndex	r1	param

	.section ".bss","awb"
.L82:
	.endo	.L82
	.section ".ghrettbl",""
	.align	4
.L137:	.data.w	.L136
	.endo	.L137
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
__callee.PMU_Hal_Initialize.v.i::
	.size	__callee.PMU_Hal_Initialize.v.i,0
PMU_Hal_Initialize::
.LDW31:
.LDW41:
..gh.beginasm.2:
	.endo	..gh.beginasm.2
MRC p15, 0, r1, c9, c12, 0

..gh.endasm.3:
	.endo	..gh.endasm.3

;line100
..lin.8223aaae..704d819c.0_1::
.LDWlin1:
	cmp	r0,1
	orreq	r1,r1,73
	orrne	r1,r1,65
..gh.beginasm.4:
	.endo	..gh.beginasm.4
MCR p15, 0, r1, c9, c12, 0

..gh.endasm.5:
	.endo	..gh.endasm.5

.LDW51:
.L227:

;line112
..lin.8223aaae..704d819c.0_2::
.LDWlin2:
	ret	
__ghs_eofn_PMU_Hal_Initialize::
	.endf	PMU_Hal_Initialize
;uPMCR	r1	local

;bClockDiv	r0	param

	.section ".bss","awb"
.L188:
	.endo	.L188
	.section ".ghrettbl",""
.L228:	.data.w	.L227
	.endo	.L228
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
__callee.PMU_Hal_Deinitialize.v.v::
	.size	__callee.PMU_Hal_Deinitialize.v.v,0
PMU_Hal_Deinitialize::
.LDW61:
.LDW71:
..gh.beginasm.7:
	.endo	..gh.beginasm.7
MRC p15, 0, r0, c9, c12, 0

..gh.endasm.8:
	.endo	..gh.endasm.8

;line126
..lin.8223aaae..8c138a5.0_3::
.LDWlin3:
	bic	r0,r0,1
..gh.beginasm.9:
	.endo	..gh.beginasm.9
MCR p15, 0, r0, c9, c12, 0

..gh.endasm.10:
	.endo	..gh.endasm.10

.LDW81:
.L287:

;line127
..lin.8223aaae..8c138a5.0_4::
.LDWlin4:
	ret	
__ghs_eofn_PMU_Hal_Deinitialize::
	.endf	PMU_Hal_Deinitialize

	.section ".bss","awb"
.L269:
	.endo	.L269
	.section ".ghrettbl",""
.L288:	.data.w	.L287
	.endo	.L288
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
__callee.PMU_Hal_ResetCycCnt.v.v::
	.size	__callee.PMU_Hal_ResetCycCnt.v.v,0
PMU_Hal_ResetCycCnt::
.LDW91:
.LDW02:
..gh.beginasm.12:
	.endo	..gh.beginasm.12
MRC p15, 0, r0, c9, c12, 0

..gh.endasm.13:
	.endo	..gh.endasm.13

;line141
..lin.8223aaae..c48ed071.0_5::
.LDWlin5:
	orr	r0,r0,4
..gh.beginasm.14:
	.endo	..gh.beginasm.14
MCR p15, 0, r0, c9, c12, 0

..gh.endasm.15:
	.endo	..gh.endasm.15

.LDW12:
.L351:

;line142
..lin.8223aaae..c48ed071.0_6::
.LDWlin6:
	ret	
__ghs_eofn_PMU_Hal_ResetCycCnt::
	.endf	PMU_Hal_ResetCycCnt

	.section ".bss","awb"
.L333:
	.endo	.L333
	.section ".ghrettbl",""
.L352:	.data.w	.L351
	.endo	.L352
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
__callee.PMU_Hal_EnCycCnt.v.v::
	.size	__callee.PMU_Hal_EnCycCnt.v.v,0
PMU_Hal_EnCycCnt::
.LDW22:
.LDW32:
..gh.beginasm.17:
	.endo	..gh.beginasm.17
MRC p15, 0, r0, c9, c12, 1

..gh.endasm.18:
	.endo	..gh.endasm.18

;line156
..lin.8223aaae..6d0443c1.0_7::
.LDWlin7:
	orr	r0,r0,1<<31
..gh.beginasm.19:
	.endo	..gh.beginasm.19
MCR p15, 0, r0, c9, c12, 1

..gh.endasm.20:
	.endo	..gh.endasm.20

.LDW42:
.L415:

;line157
..lin.8223aaae..6d0443c1.0_8::
.LDWlin8:
	ret	
__ghs_eofn_PMU_Hal_EnCycCnt::
	.endf	PMU_Hal_EnCycCnt

	.section ".bss","awb"
.L397:
	.endo	.L397
	.section ".ghrettbl",""
.L416:	.data.w	.L415
	.endo	.L416
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
__callee.PMU_Hal_DisCycCnt.v.v::
	.size	__callee.PMU_Hal_DisCycCnt.v.v,0
PMU_Hal_DisCycCnt::
.LDW52:
.LDW62:
..gh.beginasm.22:
	.endo	..gh.beginasm.22
MRC p15, 0, r0, c9, c12, 2

..gh.endasm.23:
	.endo	..gh.endasm.23

;line171
..lin.8223aaae..ee5ae4ae.0_9::
.LDWlin9:
	orr	r0,r0,1<<31
..gh.beginasm.24:
	.endo	..gh.beginasm.24
MCR p15, 0, r0, c9, c12, 2

..gh.endasm.25:
	.endo	..gh.endasm.25

.LDW72:
.L479:

;line172
..lin.8223aaae..ee5ae4ae.0_10::
.LDWlin10:
	ret	
__ghs_eofn_PMU_Hal_DisCycCnt::
	.endf	PMU_Hal_DisCycCnt

	.section ".bss","awb"
.L461:
	.endo	.L461
	.section ".ghrettbl",""
.L480:	.data.w	.L479
	.endo	.L480
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
__callee.PMU_Hal_GetCycCntVal.l.v::
	.size	__callee.PMU_Hal_GetCycCntVal.l.v,0
PMU_Hal_GetCycCntVal::
.LDW82:
.LDW92:
.LDW03:

..gh.beginasm.27:
	.endo	..gh.beginasm.27
MRRC p15, 0, r0, r1, c9

..gh.endasm.28:
	.endo	..gh.endasm.28

.LDW13:

.LDW23:
.L537:

;line182
..lin.8223aaae..86f31cf1.0_11::
.LDWlin11:
	ret	
__ghs_eofn_PMU_Hal_GetCycCntVal::
	.endf	PMU_Hal_GetCycCntVal

	.section ".bss","awb"
.L519:
	.endo	.L519
	.section ".ghrettbl",""
.L538:	.data.w	.L537
	.endo	.L538
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
__callee.PMU_Hal_ResetAllEvtCnt.v.v::
	.size	__callee.PMU_Hal_ResetAllEvtCnt.v.v,0
PMU_Hal_ResetAllEvtCnt::
.LDW33:
.LDW43:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
MRC p15, 0, r0, c9, c12, 0

..gh.endasm.31:
	.endo	..gh.endasm.31

;line197
..lin.8223aaae..65d2791a.0_12::
.LDWlin12:
	orr	r0,r0,2
..gh.beginasm.32:
	.endo	..gh.beginasm.32
MCR p15, 0, r0, c9, c12, 0

..gh.endasm.33:
	.endo	..gh.endasm.33

.LDW53:
.L591:

;line198
..lin.8223aaae..65d2791a.0_13::
.LDWlin13:
	ret	
__ghs_eofn_PMU_Hal_ResetAllEvtCnt::
	.endf	PMU_Hal_ResetAllEvtCnt

	.section ".bss","awb"
.L573:
	.endo	.L573
	.section ".ghrettbl",""
.L592:	.data.w	.L591
	.endo	.L592
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.34:
	.endo	..gh.f.a.1.e.34
__callee.PMU_Hal_EnEvtCnt.v.i::
	.size	__callee.PMU_Hal_EnEvtCnt.v.i,0
PMU_Hal_EnEvtCnt::
.LDW63:
	push	{r4,lr}
.LDW73:
	mov	r4,r0
.L679:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L681:

	popne	{r4,pc}
..gh.beginasm.35:
	.endo	..gh.beginasm.35
MRC p15, 0, r1, c9, c12, 1

..gh.endasm.36:
	.endo	..gh.endasm.36

;line213
..lin.8223aaae..71819df1.0_14::
.LDWlin14:
	orr	r1,r1,r4
..gh.beginasm.37:
	.endo	..gh.beginasm.37
MCR p15, 0, r1, c9, c12, 1

..gh.endasm.38:
	.endo	..gh.endasm.38

.LDW83:
.L683:

;line215
..lin.8223aaae..71819df1.0_15::
.LDWlin15:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_EnEvtCnt::
	.endf	PMU_Hal_EnEvtCnt

;uMask	r4	param

	.section ".bss","awb"
.L646:
	.endo	.L646
	.section ".ghcalltbl",""
	.align	4
.L680:	.data.w	.L679
	.endo	.L680
	.section ".ghrettbl",""
.L682:	.data.w	.L681
	.endo	.L682
.L684:	.data.w	.L683
	.endo	.L684
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.39:
	.endo	..gh.f.a.1.e.39
__callee.PMU_Hal_DisEvtCnt.v.i::
	.size	__callee.PMU_Hal_DisEvtCnt.v.i,0
PMU_Hal_DisEvtCnt::
.LDW93:
	push	{r4,lr}
.LDW04:
	mov	r4,r0
.L759:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L761:

	popne	{r4,pc}
..gh.beginasm.40:
	.endo	..gh.beginasm.40
MRC p15, 0, r1, c9, c12, 2

..gh.endasm.41:
	.endo	..gh.endasm.41

;line230
..lin.8223aaae..f2d83ede.0_16::
.LDWlin16:
	orr	r1,r1,r4
..gh.beginasm.42:
	.endo	..gh.beginasm.42
MCR p15, 0, r1, c9, c12, 2

..gh.endasm.43:
	.endo	..gh.endasm.43

.LDW14:
.L763:

;line232
..lin.8223aaae..f2d83ede.0_17::
.LDWlin17:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_DisEvtCnt::
	.endf	PMU_Hal_DisEvtCnt

;uMask	r4	param

	.section ".bss","awb"
.L726:
	.endo	.L726
	.section ".ghcalltbl",""
.L760:	.data.w	.L759
	.endo	.L760
	.section ".ghrettbl",""
.L762:	.data.w	.L761
	.endo	.L762
.L764:	.data.w	.L763
	.endo	.L764
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.44:
	.endo	..gh.f.a.1.e.44
__callee.PMU_Hal_GetEvtCntVal.i.i::
	.size	__callee.PMU_Hal_GetEvtCntVal.i.i,0
PMU_Hal_GetEvtCntVal::
.LDW24:
.LDW34:
	subs	r0,r0,1
	beq	.L768
	subs	r0,r0,1
	beq	.L769
	subs	r0,r0,2
	beq	.L770
	cmp	r0,4
	beq	.L771
..gh.beginasm.45:
	.endo	..gh.beginasm.45
MRC p15, 0, r0, c14, c8, 0

..gh.endasm.46:
	.endo	..gh.endasm.46

.L955:

;line270
..lin.8223aaae..c7c48921.0_18::
.LDWlin18:
	ret	
.L768:
..gh.beginasm.47:
	.endo	..gh.beginasm.47
MRC p15, 0, r0, c14, c8, 0

..gh.endasm.48:
	.endo	..gh.endasm.48

.L957:

;line245
..lin.8223aaae..c7c48921.0_19::
.LDWlin19:
	ret	
.L769:
..gh.beginasm.49:
	.endo	..gh.beginasm.49
MRC p15, 0, r0, c14, c8, 1

..gh.endasm.50:
	.endo	..gh.endasm.50

.L959:

;line251
..lin.8223aaae..c7c48921.0_20::
.LDWlin20:
	ret	
.L770:
..gh.beginasm.51:
	.endo	..gh.beginasm.51
MRC p15, 0, r0, c14, c8, 2

..gh.endasm.52:
	.endo	..gh.endasm.52

.L961:

;line257
..lin.8223aaae..c7c48921.0_21::
.LDWlin21:
	ret	
.L771:
..gh.beginasm.53:
	.endo	..gh.beginasm.53
MRC p15, 0, r0, c14, c8, 3

..gh.endasm.54:
	.endo	..gh.endasm.54

.LDW44:
.L963:

;line274
..lin.8223aaae..c7c48921.0_22::
.LDWlin22:
	ret	
__ghs_eofn_PMU_Hal_GetEvtCntVal::
	.endf	PMU_Hal_GetEvtCntVal

;uCntIndex	r0	param

	.section ".bss","awb"
.L849:
	.endo	.L849
	.section ".ghrettbl",""
.L956:	.data.w	.L955
	.endo	.L956
.L958:	.data.w	.L957
	.endo	.L958
.L960:	.data.w	.L959
	.endo	.L960
.L962:	.data.w	.L961
	.endo	.L962
.L964:	.data.w	.L963
	.endo	.L964
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.55:
	.endo	..gh.f.a.1.e.55
__callee.PMU_Hal_SetEvtCntVal.v.ii::
	.size	__callee.PMU_Hal_SetEvtCntVal.v.ii,0
PMU_Hal_SetEvtCntVal::
.LDW54:
.LDW64:
	subs	r0,r0,1
	beq	.L968
	subs	r0,r0,1
	beq	.L969
	subs	r0,r0,2
	beq	.L970
	cmp	r0,4
	beq	.L971
..gh.beginasm.56:
	.endo	..gh.beginasm.56
MCR p15, 0, r1, c14, c8, 0

..gh.endasm.57:
	.endo	..gh.endasm.57

.L1153:

;line317
..lin.8223aaae..132ce9ad.0_23::
.LDWlin23:
	ret	
.L968:
..gh.beginasm.58:
	.endo	..gh.beginasm.58
MCR p15, 0, r1, c14, c8, 0

..gh.endasm.59:
	.endo	..gh.endasm.59

.L1155:

;line292
..lin.8223aaae..132ce9ad.0_24::
.LDWlin24:
	ret	
.L969:
..gh.beginasm.60:
	.endo	..gh.beginasm.60
MCR p15, 0, r1, c14, c8, 1

..gh.endasm.61:
	.endo	..gh.endasm.61

.L1157:

;line298
..lin.8223aaae..132ce9ad.0_25::
.LDWlin25:
	ret	
.L970:
..gh.beginasm.62:
	.endo	..gh.beginasm.62
MCR p15, 0, r1, c14, c8, 2

..gh.endasm.63:
	.endo	..gh.endasm.63

.L1159:

;line304
..lin.8223aaae..132ce9ad.0_26::
.LDWlin26:
	ret	
.L971:
..gh.beginasm.64:
	.endo	..gh.beginasm.64
MCR p15, 0, r1, c14, c8, 3

..gh.endasm.65:
	.endo	..gh.endasm.65

.LDW74:
.L1161:

;line320
..lin.8223aaae..132ce9ad.0_27::
.LDWlin27:
	ret	
__ghs_eofn_PMU_Hal_SetEvtCntVal::
	.endf	PMU_Hal_SetEvtCntVal
;uPMEVCNTR	r1	local

;uCntIndex	r0	param
;uVal	r1	param

	.section ".bss","awb"
.L1050:
	.endo	.L1050
	.section ".ghrettbl",""
.L1154:	.data.w	.L1153
	.endo	.L1154
.L1156:	.data.w	.L1155
	.endo	.L1156
.L1158:	.data.w	.L1157
	.endo	.L1158
.L1160:	.data.w	.L1159
	.endo	.L1160
.L1162:	.data.w	.L1161
	.endo	.L1162
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.66:
	.endo	..gh.f.a.1.e.66
__callee.PMU_Hal_SetEvtCntType.v.ii::
	.size	__callee.PMU_Hal_SetEvtCntType.v.ii,0
PMU_Hal_SetEvtCntType::
.LDW84:
.LDW94:
	ldr	r2,.L1345
	subs	r0,r0,1
	beq	.L1166
	subs	r0,r0,1
	beq	.L1167
	subs	r0,r0,2
	beq	.L1168
	cmp	r0,4
	beq	.L1169
	b	.L1346

.L1345:	.data.w	0xfa20ffff
	.endo	.L1345

.L1346:

;line374
..lin.8223aaae..78c96d8c.0_28::
.LDWlin28:
..gh.beginasm.67:
	.endo	..gh.beginasm.67
MRC p15, 0, r0, c14, c12, 0

..gh.endasm.68:
	.endo	..gh.endasm.68

;line376
..lin.8223aaae..78c96d8c.0_29::
.LDWlin29:
	and	r0,r1,r2
..gh.beginasm.69:
	.endo	..gh.beginasm.69
MCR p15, 0, r0, c14, c12, 0

..gh.endasm.70:
	.endo	..gh.endasm.70

.L1347:

;line379
..lin.8223aaae..78c96d8c.0_30::
.LDWlin30:
	ret	
.L1166:
..gh.beginasm.71:
	.endo	..gh.beginasm.71
MRC p15, 0, r0, c14, c12, 0

..gh.endasm.72:
	.endo	..gh.endasm.72

;line335
..lin.8223aaae..78c96d8c.0_31::
.LDWlin31:
	and	r0,r1,r2
..gh.beginasm.73:
	.endo	..gh.beginasm.73
MCR p15, 0, r0, c14, c12, 0

..gh.endasm.74:
	.endo	..gh.endasm.74

.L1349:

;line338
..lin.8223aaae..78c96d8c.0_32::
.LDWlin32:
	ret	
.L1167:
..gh.beginasm.75:
	.endo	..gh.beginasm.75
MRC p15, 0, r0, c14, c12, 1

..gh.endasm.76:
	.endo	..gh.endasm.76

;line345
..lin.8223aaae..78c96d8c.0_33::
.LDWlin33:
	and	r0,r1,r2
..gh.beginasm.77:
	.endo	..gh.beginasm.77
MCR p15, 0, r0, c14, c12, 1

..gh.endasm.78:
	.endo	..gh.endasm.78

.L1351:

;line348
..lin.8223aaae..78c96d8c.0_34::
.LDWlin34:
	ret	
.L1168:
..gh.beginasm.79:
	.endo	..gh.beginasm.79
MRC p15, 0, r0, c14, c12, 2

..gh.endasm.80:
	.endo	..gh.endasm.80

;line355
..lin.8223aaae..78c96d8c.0_35::
.LDWlin35:
	and	r0,r1,r2
..gh.beginasm.81:
	.endo	..gh.beginasm.81
MCR p15, 0, r0, c14, c12, 2

..gh.endasm.82:
	.endo	..gh.endasm.82

.L1353:

;line358
..lin.8223aaae..78c96d8c.0_36::
.LDWlin36:
	ret	
.L1169:
..gh.beginasm.83:
	.endo	..gh.beginasm.83
MRC p15, 0, r0, c14, c12, 3

..gh.endasm.84:
	.endo	..gh.endasm.84

;line365
..lin.8223aaae..78c96d8c.0_37::
.LDWlin37:
	and	r0,r1,r2
..gh.beginasm.85:
	.endo	..gh.beginasm.85
MCR p15, 0, r0, c14, c12, 3

..gh.endasm.86:
	.endo	..gh.endasm.86

.LDW05:
.L1355:

;line382
..lin.8223aaae..78c96d8c.0_38::
.LDWlin38:
	ret	
__ghs_eofn_PMU_Hal_SetEvtCntType::
	.endf	PMU_Hal_SetEvtCntType

;uCntIndex	r0	param
;uCntType	r1	param

	.section ".bss","awb"
.L1242:
	.endo	.L1242
	.section ".ghrettbl",""
.L1348:	.data.w	.L1347
	.endo	.L1348
.L1350:	.data.w	.L1349
	.endo	.L1350
.L1352:	.data.w	.L1351
	.endo	.L1352
.L1354:	.data.w	.L1353
	.endo	.L1354
.L1356:	.data.w	.L1355
	.endo	.L1356
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.87:
	.endo	..gh.f.a.1.e.87
__callee.PMU_Hal_GetEvtCntOvsStatus.i.i::
	.size	__callee.PMU_Hal_GetEvtCntOvsStatus.i.i,0
PMU_Hal_GetEvtCntOvsStatus::
.LDW15:
	push	{r4,lr}
.LDW25:
	mov	r4,r0
.L1484:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
	bne	.L1359
..gh.beginasm.88:
	.endo	..gh.beginasm.88
MRC p15, 0, r1, c9, c14, 3

..gh.endasm.89:
	.endo	..gh.endasm.89

;line395
..lin.8223aaae..78669afa.0_39::
.LDWlin39:
	cmp	r4,0
	andne	r0,r1,r4
.L1486:

	popne	{r4,pc}
	b	.L1363
.L1359:
	mov	r0,0
.L1488:

	pop	{r4,pc}
.L1363:
	mov	r0,r1
.LDW35:
.L1490:

	pop	{r4,pc}
__ghs_eofn_PMU_Hal_GetEvtCntOvsStatus::
	.endf	PMU_Hal_GetEvtCntOvsStatus
;uPMOVSSET	r0	local

;uCntIndex	r4	param

	.section ".bss","awb"
.L1427:
	.endo	.L1427
	.section ".ghcalltbl",""
.L1485:	.data.w	.L1484
	.endo	.L1485
	.section ".ghrettbl",""
.L1487:	.data.w	.L1486
	.endo	.L1487
.L1489:	.data.w	.L1488
	.endo	.L1489
.L1491:	.data.w	.L1490
	.endo	.L1491
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.90:
	.endo	..gh.f.a.1.e.90
__callee.PMU_Hal_ClearEvCnOvs.v.i::
	.size	__callee.PMU_Hal_ClearEvCnOvs.v.i,0
PMU_Hal_ClearEvCnOvs::
.LDW45:
	push	{r4,lr}
.LDW55:
	mov	r4,r0
.L1567:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L1569:

	popne	{r4,pc}
..gh.beginasm.91:
	.endo	..gh.beginasm.91
MRC p15, 0, r0, c9, c12, 3

..gh.endasm.92:
	.endo	..gh.endasm.92

;line421
..lin.8223aaae..cb6efdb5.0_40::
.LDWlin40:
..gh.beginasm.93:
	.endo	..gh.beginasm.93
MCR p15, 0, r4, c9, c12, 3

..gh.endasm.94:
	.endo	..gh.endasm.94

.LDW65:
.L1571:

;line423
..lin.8223aaae..cb6efdb5.0_41::
.LDWlin41:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_ClearEvCnOvs::
	.endf	PMU_Hal_ClearEvCnOvs

;uMask	r4	param

	.section ".bss","awb"
.L1534:
	.endo	.L1534
	.section ".ghcalltbl",""
.L1568:	.data.w	.L1567
	.endo	.L1568
	.section ".ghrettbl",""
.L1570:	.data.w	.L1569
	.endo	.L1570
.L1572:	.data.w	.L1571
	.endo	.L1572
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.95:
	.endo	..gh.f.a.1.e.95
__callee.PMU_Hal_EnEvtOvsIrq.v.i::
	.size	__callee.PMU_Hal_EnEvtOvsIrq.v.i,0
PMU_Hal_EnEvtOvsIrq::
.LDW75:
	push	{r4,lr}
.LDW85:
	mov	r4,r0
.L1655:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L1657:

	popne	{r4,pc}
..gh.beginasm.96:
	.endo	..gh.beginasm.96
MRC p15, 0, r1, c9, c14, 1

..gh.endasm.97:
	.endo	..gh.endasm.97

;line441
..lin.8223aaae..10c0930.0_42::
.LDWlin42:
	orr	r1,r1,r4
..gh.beginasm.98:
	.endo	..gh.beginasm.98
MCR p15, 0, r1, c9, c14, 1

..gh.endasm.99:
	.endo	..gh.endasm.99

.LDW95:
.L1659:

;line443
..lin.8223aaae..10c0930.0_43::
.LDWlin43:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_EnEvtOvsIrq::
	.endf	PMU_Hal_EnEvtOvsIrq

;uMask	r4	param

	.section ".bss","awb"
.L1622:
	.endo	.L1622
	.section ".ghcalltbl",""
.L1656:	.data.w	.L1655
	.endo	.L1656
	.section ".ghrettbl",""
.L1658:	.data.w	.L1657
	.endo	.L1658
.L1660:	.data.w	.L1659
	.endo	.L1660
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.100:
	.endo	..gh.f.a.1.e.100
__callee.PMU_Hal_DisEvtOvsIrq.v.i::
	.size	__callee.PMU_Hal_DisEvtOvsIrq.v.i,0
PMU_Hal_DisEvtOvsIrq::
.LDW06:
	push	{r4,lr}
.LDW16:
	mov	r4,r0
.L1735:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L1737:

	popne	{r4,pc}
..gh.beginasm.101:
	.endo	..gh.beginasm.101
MRC p15, 0, r1, c9, c14, 2

..gh.endasm.102:
	.endo	..gh.endasm.102

;line459
..lin.8223aaae..62e09efd.0_44::
.LDWlin44:
	orr	r1,r1,r4
..gh.beginasm.103:
	.endo	..gh.beginasm.103
MCR p15, 0, r1, c9, c14, 2

..gh.endasm.104:
	.endo	..gh.endasm.104

.LDW26:
.L1739:

;line461
..lin.8223aaae..62e09efd.0_45::
.LDWlin45:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_DisEvtOvsIrq::
	.endf	PMU_Hal_DisEvtOvsIrq

;uMask	r4	param

	.section ".bss","awb"
.L1702:
	.endo	.L1702
	.section ".ghcalltbl",""
.L1736:	.data.w	.L1735
	.endo	.L1736
	.section ".ghrettbl",""
.L1738:	.data.w	.L1737
	.endo	.L1738
.L1740:	.data.w	.L1739
	.endo	.L1740
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.105:
	.endo	..gh.f.a.1.e.105
__callee.PMU_Hal_EvtIncrement.v.i::
	.size	__callee.PMU_Hal_EvtIncrement.v.i,0
PMU_Hal_EvtIncrement::
.LDW36:
	push	{r4,lr}
.LDW46:
	mov	r4,r0
.L1807:

	bl	PMU_Hal_IsRightEvent
	cmp	r0,1
.L1809:

	popne	{r4,pc}
..gh.beginasm.106:
	.endo	..gh.beginasm.106
MCR p15, 0, r4, c9, c12, 4

..gh.endasm.107:
	.endo	..gh.endasm.107

.LDW56:
.L1811:

;line477
..lin.8223aaae..146efbe.0_46::
.LDWlin46:
	pop	{r4,pc}
__ghs_eofn_PMU_Hal_EvtIncrement::
	.endf	PMU_Hal_EvtIncrement

;uCntIndex	r4	param

	.section ".bss","awb"
.L1774:
	.endo	.L1774
	.section ".ghcalltbl",""
.L1808:	.data.w	.L1807
	.endo	.L1808
	.section ".ghrettbl",""
.L1810:	.data.w	.L1809
	.endo	.L1810
.L1812:	.data.w	.L1811
	.endo	.L1812
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.108:
	.endo	..gh.f.a.1.e.108
__callee.PMU_Hal_EnableUserMode.v.i::
	.size	__callee.PMU_Hal_EnableUserMode.v.i,0
PMU_Hal_EnableUserMode::
.LDW66:
.LDW76:
	and	r0,r0,15
..gh.beginasm.109:
	.endo	..gh.beginasm.109
MCR p15, 0, r0, c9, c14, 0

..gh.endasm.110:
	.endo	..gh.endasm.110

.LDW86:
.L1868:

;line490
..lin.8223aaae..99151e35.0_47::
.LDWlin47:
	ret	
__ghs_eofn_PMU_Hal_EnableUserMode::
	.endf	PMU_Hal_EnableUserMode

;uMode	r0	param

	.section ".bss","awb"
.L1850:
	.endo	.L1850
	.section ".ghrettbl",""
.L1869:	.data.w	.L1868
	.endo	.L1869
	.section ".sdk_text_asil_d","ax"

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682577..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	145,10,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,115,114,99,47,112,109,117,95,104,97,108,46,99,0
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
	.data.b	21,5,0,0
	.data.b	2,0
	.data.b	86,1,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,115,114,99,47,112,109,117,95,104,97,108,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,112,109,117,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,112,109,117,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,67,111,114,101,95,77,101,109,77,97,112,46,104,0
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
	.data.b	42
	.section	.debug_str		;off: 197
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 36
	.data.w	.Ldw_str_begin+197
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 19
	.data.b	42
	.data.b	36
	.data.b	0
	.data.b	3,14
	.data.b	62,11
	.data.b	11,11
	.data.b	0,0

	.section	.debug_info		;off: 42
	.data.b	42
	.section	.debug_str		;off: 211
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+211
	.data.b	7
	.data.b	4

	.data.b	74
	.data.w	.Ldw_begin+219
	.data.b	1

	.section	.debug_abbrev		;off: 30
	.data.b	74
	.data.b	21
	.data.b	1
	.data.b	73,16
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 55
	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.section	.debug_abbrev		;off: 39
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 61
	.data.b	0

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 48
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 64
	.data.b	23
	.data.w	.Ldw_begin+231
	.data.b	0

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

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 225
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 84
	.data.w	.Ldw_str_begin+225
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+255
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+243
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+243
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+243
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 244
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 220
	.data.w	.Ldw_str_begin+244
	.data.b	51
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+35

	.section	.debug_abbrev		;off: 55
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 231
	.data.b	45
	.section	.debug_str		;off: 252
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 232
	.data.w	.Ldw_str_begin+252
	.data.b	56
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+35

	.data.b	45
	.section	.debug_str		;off: 258
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 244
	.data.w	.Ldw_str_begin+258
	.data.b	64
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 265
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 256
	.data.w	.Ldw_str_begin+265
	.data.b	68
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+83

	.data.b	52
	.section	.debug_str		;off: 272
	.data.b	0
	.section	.debug_info		;off: 268
	.data.w	.Ldw_str_begin+272
	.data.b	82
	.data.b	1
	.data.b	6
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 70
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

	.section	.debug_info		;off: 277
	.data.b	51
	.section	.debug_str		;off: 273
	.data.b	83,87,95,73,78,67,82,0
	.section	.debug_info		;off: 278
	.data.w	.Ldw_str_begin+273
	.data.b	83
	.data.b	5
	.data.b	6
	.data.b	0

	.section	.debug_abbrev		;off: 87
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 286
	.data.b	51
	.section	.debug_str		;off: 281
	.data.b	76,49,73,95,67,65,67,72,69,95,82,69,70,73,76,76,0
	.section	.debug_info		;off: 287
	.data.w	.Ldw_str_begin+281
	.data.b	84
	.data.b	5
	.data.b	6
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 298
	.data.b	76,49,68,95,67,65,67,72,69,95,82,69,70,73,76,76,0
	.section	.debug_info		;off: 296
	.data.w	.Ldw_str_begin+298
	.data.b	85
	.data.b	5
	.data.b	6
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 315
	.data.b	76,49,68,95,67,65,67,72,69,0
	.section	.debug_info		;off: 305
	.data.w	.Ldw_str_begin+315
	.data.b	86
	.data.b	5
	.data.b	6
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 325
	.data.b	76,68,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 314
	.data.w	.Ldw_str_begin+325
	.data.b	87
	.data.b	5
	.data.b	6
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 336
	.data.b	83,84,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 323
	.data.w	.Ldw_str_begin+336
	.data.b	88
	.data.b	5
	.data.b	6
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 347
	.data.b	73,78,83,84,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 332
	.data.w	.Ldw_str_begin+347
	.data.b	89
	.data.b	5
	.data.b	6
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 360
	.data.b	69,88,67,95,84,65,75,69,78,0
	.section	.debug_info		;off: 341
	.data.w	.Ldw_str_begin+360
	.data.b	90
	.data.b	5
	.data.b	6
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 370
	.data.b	69,88,67,95,82,69,84,85,82,78,0
	.section	.debug_info		;off: 350
	.data.w	.Ldw_str_begin+370
	.data.b	91
	.data.b	5
	.data.b	6
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 381
	.data.b	67,73,68,95,87,82,73,84,69,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 359
	.data.w	.Ldw_str_begin+381
	.data.b	92
	.data.b	5
	.data.b	6
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 399
	.data.b	80,67,95,87,82,73,84,69,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 368
	.data.w	.Ldw_str_begin+399
	.data.b	93
	.data.b	5
	.data.b	6
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 416
	.data.b	66,82,95,73,77,77,69,68,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 377
	.data.w	.Ldw_str_begin+416
	.data.b	94
	.data.b	5
	.data.b	6
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 433
	.data.b	66,82,95,82,69,84,85,82,78,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 386
	.data.w	.Ldw_str_begin+433
	.data.b	95
	.data.b	5
	.data.b	6
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 451
	.data.b	85,78,65,76,73,71,78,69,68,95,76,68,83,84,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 395
	.data.w	.Ldw_str_begin+451
	.data.b	96
	.data.b	5
	.data.b	6
	.data.b	15

	.data.b	51
	.section	.debug_str		;off: 474
	.data.b	66,82,95,77,73,83,95,80,82,69,68,0
	.section	.debug_info		;off: 404
	.data.w	.Ldw_str_begin+474
	.data.b	97
	.data.b	5
	.data.b	6
	.data.b	16

	.data.b	51
	.section	.debug_str		;off: 486
	.data.b	67,80,85,95,67,89,67,76,69,83,0
	.section	.debug_info		;off: 413
	.data.w	.Ldw_str_begin+486
	.data.b	98
	.data.b	5
	.data.b	6
	.data.b	17

	.data.b	51
	.section	.debug_str		;off: 497
	.data.b	66,82,95,80,82,69,68,0
	.section	.debug_info		;off: 422
	.data.w	.Ldw_str_begin+497
	.data.b	99
	.data.b	5
	.data.b	6
	.data.b	18

	.data.b	51
	.section	.debug_str		;off: 505
	.data.b	77,69,77,95,65,67,67,69,83,83,0
	.section	.debug_info		;off: 431
	.data.w	.Ldw_str_begin+505
	.data.b	100
	.data.b	5
	.data.b	6
	.data.b	19

	.data.b	51
	.section	.debug_str		;off: 516
	.data.b	76,49,73,95,67,65,67,72,69,0
	.section	.debug_info		;off: 440
	.data.w	.Ldw_str_begin+516
	.data.b	101
	.data.b	5
	.data.b	6
	.data.b	20

	.data.b	51
	.section	.debug_str		;off: 526
	.data.b	66,85,83,95,65,67,67,69,83,83,0
	.section	.debug_info		;off: 449
	.data.w	.Ldw_str_begin+526
	.data.b	102
	.data.b	5
	.data.b	6
	.data.b	25

	.data.b	51
	.section	.debug_str		;off: 537
	.data.b	77,69,77,79,82,89,95,69,82,82,79,82,0
	.section	.debug_info		;off: 458
	.data.w	.Ldw_str_begin+537
	.data.b	103
	.data.b	5
	.data.b	6
	.data.b	26

	.data.b	51
	.section	.debug_str		;off: 550
	.data.b	73,78,83,84,95,83,80,69,67,0
	.section	.debug_info		;off: 467
	.data.w	.Ldw_str_begin+550
	.data.b	104
	.data.b	5
	.data.b	6
	.data.b	27

	.data.b	51
	.section	.debug_str		;off: 560
	.data.b	66,85,83,95,67,89,67,76,69,83,0
	.section	.debug_info		;off: 476
	.data.w	.Ldw_str_begin+560
	.data.b	105
	.data.b	5
	.data.b	6
	.data.b	29

	.data.b	51
	.section	.debug_str		;off: 571
	.data.b	67,72,65,73,78,0
	.section	.debug_info		;off: 485
	.data.w	.Ldw_str_begin+571
	.data.b	106
	.data.b	5
	.data.b	6
	.data.b	30

	.data.b	51
	.section	.debug_str		;off: 577
	.data.b	66,82,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 494
	.data.w	.Ldw_str_begin+577
	.data.b	107
	.data.b	5
	.data.b	6
	.data.b	33

	.data.b	51
	.section	.debug_str		;off: 588
	.data.b	66,82,95,77,73,83,95,80,82,69,68,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 503
	.data.w	.Ldw_str_begin+588
	.data.b	108
	.data.b	5
	.data.b	6
	.data.b	34

	.data.b	51
	.section	.debug_str		;off: 608
	.data.b	83,84,65,76,76,95,70,82,79,78,84,69,78,68,0
	.section	.debug_info		;off: 512
	.data.w	.Ldw_str_begin+608
	.data.b	109
	.data.b	5
	.data.b	6
	.data.b	35

	.data.b	51
	.section	.debug_str		;off: 623
	.data.b	83,84,65,76,76,95,66,65,67,75,69,78,68,0
	.section	.debug_info		;off: 521
	.data.w	.Ldw_str_begin+623
	.data.b	110
	.data.b	5
	.data.b	6
	.data.b	36

	.data.b	51
	.section	.debug_str		;off: 637
	.data.b	66,85,83,95,65,67,67,69,83,83,95,82,68,0
	.section	.debug_info		;off: 530
	.data.w	.Ldw_str_begin+637
	.data.b	111
	.data.b	5
	.data.b	6
	.data.b	224,0

	.data.b	51
	.section	.debug_str		;off: 651
	.data.b	66,85,83,95,65,67,67,69,83,83,95,87,82,0
	.section	.debug_info		;off: 540
	.data.w	.Ldw_str_begin+651
	.data.b	112
	.data.b	5
	.data.b	6
	.data.b	225,0

	.data.b	51
	.section	.debug_str		;off: 665
	.data.b	69,88,67,95,83,86,67,0
	.section	.debug_info		;off: 550
	.data.w	.Ldw_str_begin+665
	.data.b	113
	.data.b	5
	.data.b	6
	.data.b	130,1

	.data.b	51
	.section	.debug_str		;off: 673
	.data.b	69,88,67,95,73,82,81,0
	.section	.debug_info		;off: 560
	.data.w	.Ldw_str_begin+673
	.data.b	114
	.data.b	5
	.data.b	6
	.data.b	134,1

	.data.b	51
	.section	.debug_str		;off: 681
	.data.b	69,88,67,95,70,73,81,0
	.section	.debug_info		;off: 570
	.data.w	.Ldw_str_begin+681
	.data.b	115
	.data.b	5
	.data.b	6
	.data.b	135,1

	.data.b	51
	.section	.debug_str		;off: 689
	.data.b	69,88,67,95,72,86,67,0
	.section	.debug_info		;off: 580
	.data.w	.Ldw_str_begin+689
	.data.b	116
	.data.b	5
	.data.b	6
	.data.b	138,1

	.data.b	51
	.section	.debug_str		;off: 697
	.data.b	69,88,67,95,84,82,65,80,95,73,82,81,0
	.section	.debug_info		;off: 590
	.data.w	.Ldw_str_begin+697
	.data.b	117
	.data.b	5
	.data.b	6
	.data.b	142,1

	.data.b	51
	.section	.debug_str		;off: 710
	.data.b	69,88,67,95,84,82,65,80,95,70,73,81,0
	.section	.debug_info		;off: 600
	.data.w	.Ldw_str_begin+710
	.data.b	118
	.data.b	5
	.data.b	6
	.data.b	143,1

	.data.b	51
	.section	.debug_str		;off: 723
	.data.b	72,73,82,90,69,82,95,65,88,73,95,82,69,65,68,0
	.section	.debug_info		;off: 610
	.data.w	.Ldw_str_begin+723
	.data.b	119
	.data.b	5
	.data.b	6
	.data.b	192,1

	.data.b	51
	.section	.debug_str		;off: 739
	.data.b	72,73,82,90,69,82,95,65,88,73,95,87,82,73,84,69,0
	.section	.debug_info		;off: 620
	.data.w	.Ldw_str_begin+739
	.data.b	120
	.data.b	5
	.data.b	6
	.data.b	193,1

	.data.b	51
	.section	.debug_str		;off: 756
	.data.b	72,73,82,90,69,82,95,70,76,65,83,72,95,82,69,65,68,0
	.section	.debug_info		;off: 630
	.data.w	.Ldw_str_begin+756
	.data.b	121
	.data.b	5
	.data.b	6
	.data.b	194,1

	.data.b	51
	.section	.debug_str		;off: 774
	.data.b	72,73,82,90,69,82,95,76,76,80,80,95,82,69,65,68,0
	.section	.debug_info		;off: 640
	.data.w	.Ldw_str_begin+774
	.data.b	122
	.data.b	5
	.data.b	6
	.data.b	195,1

	.data.b	51
	.section	.debug_str		;off: 791
	.data.b	72,73,82,90,69,82,95,76,76,80,80,95,87,82,73,84,69,0
	.section	.debug_info		;off: 650
	.data.w	.Ldw_str_begin+791
	.data.b	123
	.data.b	5
	.data.b	6
	.data.b	196,1

	.data.b	51
	.section	.debug_str		;off: 809
	.data.b	72,73,82,90,69,82,95,78,67,95,65,88,73,95,82,69,65,68,0
	.section	.debug_info		;off: 660
	.data.w	.Ldw_str_begin+809
	.data.b	124
	.data.b	5
	.data.b	6
	.data.b	197,1

	.data.b	51
	.section	.debug_str		;off: 828
	.data.b	72,73,82,90,69,82,95,78,67,95,65,88,73,95,87,82,73,84,69,0
	.section	.debug_info		;off: 670
	.data.w	.Ldw_str_begin+828
	.data.b	125
	.data.b	5
	.data.b	6
	.data.b	198,1

	.data.b	51
	.section	.debug_str		;off: 848
	.data.b	72,73,82,90,69,82,95,78,67,95,70,76,65,83,72,95,82,69,65,68,0
	.section	.debug_info		;off: 680
	.data.w	.Ldw_str_begin+848
	.data.b	126
	.data.b	5
	.data.b	6
	.data.b	199,1

	.data.b	51
	.section	.debug_str		;off: 869
	.data.b	72,73,82,90,69,82,95,82,69,70,73,76,76,95,80,70,95,65,88,73,0
	.section	.debug_info		;off: 690
	.data.w	.Ldw_str_begin+869
	.data.b	127
	.data.b	5
	.data.b	6
	.data.b	200,1

	.data.b	51
	.section	.debug_str		;off: 890
	.data.b	72,73,82,90,69,82,95,82,69,70,73,76,76,95,76,83,95,65,88,73,0
	.section	.debug_info		;off: 700
	.data.w	.Ldw_str_begin+890
	.data.b	128,1
	.data.b	5
	.data.b	6
	.data.b	201,1

	.data.b	51
	.section	.debug_str		;off: 911
	.data.b	72,73,82,90,69,82,95,82,69,70,73,76,76,95,76,83,95,70,76,65,83,72,0
	.section	.debug_info		;off: 711
	.data.w	.Ldw_str_begin+911
	.data.b	129,1
	.data.b	5
	.data.b	6
	.data.b	202,1

	.data.b	51
	.section	.debug_str		;off: 934
	.data.b	72,73,82,90,69,82,95,68,67,95,65,67,67,69,83,83,95,65,88,73,0
	.section	.debug_info		;off: 722
	.data.w	.Ldw_str_begin+934
	.data.b	130,1
	.data.b	5
	.data.b	6
	.data.b	203,1

	.data.b	51
	.section	.debug_str		;off: 955
	.data.b	72,73,82,90,69,82,95,68,67,95,65,67,67,69,83,83,95,70,76,65,83,72,0
	.section	.debug_info		;off: 733
	.data.w	.Ldw_str_begin+955
	.data.b	131,1
	.data.b	5
	.data.b	6
	.data.b	204,1

	.data.b	51
	.section	.debug_str		;off: 978
	.data.b	72,73,82,90,69,82,95,73,67,95,65,67,67,69,83,83,95,65,88,73,0
	.section	.debug_info		;off: 744
	.data.w	.Ldw_str_begin+978
	.data.b	132,1
	.data.b	5
	.data.b	6
	.data.b	205,1

	.data.b	51
	.section	.debug_str		;off: 999
	.data.b	72,73,82,90,69,82,95,73,67,95,65,67,67,69,83,83,95,70,76,65,83,72,0
	.section	.debug_info		;off: 755
	.data.w	.Ldw_str_begin+999
	.data.b	133,1
	.data.b	5
	.data.b	6
	.data.b	206,1

	.data.b	51
	.section	.debug_str		;off: 1022
	.data.b	72,73,82,90,69,82,95,78,67,95,76,83,95,72,73,78,84,69,68,95,65,88,73,0
	.section	.debug_info		;off: 766
	.data.w	.Ldw_str_begin+1022
	.data.b	134,1
	.data.b	5
	.data.b	6
	.data.b	207,1

	.data.b	51
	.section	.debug_str		;off: 1046
	.data.b	72,73,82,90,69,82,95,78,67,95,76,83,95,72,73,78,84,69,68,95,70,76,65,83,72,95,82,69,65,68,0
	.section	.debug_info		;off: 777
	.data.w	.Ldw_str_begin+1046
	.data.b	135,1
	.data.b	5
	.data.b	6
	.data.b	208,1

	.data.b	51
	.section	.debug_str		;off: 1077
	.data.b	72,73,82,90,69,82,95,82,69,70,73,76,76,95,73,67,95,65,88,73,0
	.section	.debug_info		;off: 788
	.data.w	.Ldw_str_begin+1077
	.data.b	136,1
	.data.b	5
	.data.b	6
	.data.b	209,1

	.data.b	51
	.section	.debug_str		;off: 1098
	.data.b	72,73,82,90,69,82,95,82,69,70,73,76,76,95,73,67,95,70,76,65,83,72,0
	.section	.debug_info		;off: 799
	.data.w	.Ldw_str_begin+1098
	.data.b	137,1
	.data.b	5
	.data.b	6
	.data.b	210,1

	.data.b	51
	.section	.debug_str		;off: 1121
	.data.b	72,73,82,90,69,82,95,78,67,95,76,83,95,65,88,73,95,82,69,65,68,0
	.section	.debug_info		;off: 810
	.data.w	.Ldw_str_begin+1121
	.data.b	138,1
	.data.b	5
	.data.b	6
	.data.b	211,1

	.data.b	51
	.section	.debug_str		;off: 1143
	.data.b	72,73,82,90,69,82,95,78,67,95,76,83,95,70,76,65,83,72,95,82,69,65,68,0
	.section	.debug_info		;off: 821
	.data.w	.Ldw_str_begin+1143
	.data.b	139,1
	.data.b	5
	.data.b	6
	.data.b	212,1

	.data.b	51
	.section	.debug_str		;off: 1167
	.data.b	72,73,82,90,69,82,95,67,79,78,68,95,66,82,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 832
	.data.w	.Ldw_str_begin+1167
	.data.b	140,1
	.data.b	5
	.data.b	6
	.data.b	213,1

	.data.b	51
	.section	.debug_str		;off: 1190
	.data.b	72,73,82,90,69,82,95,77,73,83,95,80,82,69,68,95,67,79,78,68,95,66,82,0
	.section	.debug_info		;off: 843
	.data.w	.Ldw_str_begin+1190
	.data.b	141,1
	.data.b	5
	.data.b	6
	.data.b	214,1

	.data.b	51
	.section	.debug_str		;off: 1214
	.data.b	72,73,82,90,69,82,95,66,84,65,67,95,66,82,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 854
	.data.w	.Ldw_str_begin+1214
	.data.b	142,1
	.data.b	5
	.data.b	6
	.data.b	215,1

	.data.b	51
	.section	.debug_str		;off: 1237
	.data.b	72,73,82,90,69,82,95,77,73,83,95,80,82,69,68,95,66,84,65,67,95,66,82,0
	.section	.debug_info		;off: 865
	.data.w	.Ldw_str_begin+1237
	.data.b	143,1
	.data.b	5
	.data.b	6
	.data.b	216,1

	.data.b	51
	.section	.debug_str		;off: 1261
	.data.b	72,73,82,90,69,82,95,86,83,67,84,76,82,95,67,72,65,78,71,69,68,0
	.section	.debug_info		;off: 876
	.data.w	.Ldw_str_begin+1261
	.data.b	144,1
	.data.b	5
	.data.b	6
	.data.b	217,1

	.data.b	51
	.section	.debug_str		;off: 1283
	.data.b	72,73,82,90,69,82,95,68,83,66,95,65,76,76,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 887
	.data.w	.Ldw_str_begin+1283
	.data.b	145,1
	.data.b	5
	.data.b	6
	.data.b	218,1

	.data.b	51
	.section	.debug_str		;off: 1306
	.data.b	72,73,82,90,69,82,95,83,73,77,85,76,84,95,65,67,67,69,83,83,95,65,88,73,0
	.section	.debug_info		;off: 898
	.data.w	.Ldw_str_begin+1306
	.data.b	146,1
	.data.b	5
	.data.b	6
	.data.b	219,1

	.data.b	51
	.section	.debug_str		;off: 1331
	.data.b	72,73,82,90,69,82,95,83,73,77,85,76,84,95,65,67,67,69,83,83,95,70,76,65,83,72,0
	.section	.debug_info		;off: 909
	.data.w	.Ldw_str_begin+1331
	.data.b	147,1
	.data.b	5
	.data.b	6
	.data.b	220,1

	.data.b	51
	.section	.debug_str		;off: 1358
	.data.b	72,73,82,90,69,82,95,69,76,50,95,69,78,84,69,82,69,68,0
	.section	.debug_info		;off: 920
	.data.w	.Ldw_str_begin+1358
	.data.b	148,1
	.data.b	5
	.data.b	6
	.data.b	221,1

	.data.b	51
	.section	.debug_str		;off: 1377
	.data.b	72,73,82,90,69,82,95,67,82,83,95,66,82,95,82,69,84,73,82,69,68,0
	.section	.debug_info		;off: 931
	.data.w	.Ldw_str_begin+1377
	.data.b	149,1
	.data.b	5
	.data.b	6
	.data.b	222,1

	.data.b	51
	.section	.debug_str		;off: 1399
	.data.b	72,73,82,90,69,82,95,77,73,83,95,80,82,69,68,95,67,82,83,95,66,82,0
	.section	.debug_info		;off: 942
	.data.w	.Ldw_str_begin+1399
	.data.b	150,1
	.data.b	5
	.data.b	6
	.data.b	223,1

	.data.b	51
	.section	.debug_str		;off: 1422
	.data.b	72,73,82,90,69,82,95,67,79,82,95,69,82,82,95,77,69,77,0
	.section	.debug_info		;off: 953
	.data.w	.Ldw_str_begin+1422
	.data.b	151,1
	.data.b	5
	.data.b	6
	.data.b	240,1

	.data.b	51
	.section	.debug_str		;off: 1441
	.data.b	72,73,82,90,69,82,95,70,65,84,95,69,82,82,95,77,69,77,0
	.section	.debug_info		;off: 964
	.data.w	.Ldw_str_begin+1441
	.data.b	152,1
	.data.b	5
	.data.b	6
	.data.b	241,1

	.data.b	51
	.section	.debug_str		;off: 1460
	.data.b	72,73,82,90,69,82,95,66,85,83,95,67,79,82,95,68,65,84,65,0
	.section	.debug_info		;off: 975
	.data.w	.Ldw_str_begin+1460
	.data.b	153,1
	.data.b	5
	.data.b	6
	.data.b	242,1

	.data.b	51
	.section	.debug_str		;off: 1480
	.data.b	72,73,82,90,69,82,95,66,85,83,95,70,65,84,95,79,84,72,69,82,0
	.section	.debug_info		;off: 986
	.data.w	.Ldw_str_begin+1480
	.data.b	154,1
	.data.b	5
	.data.b	6
	.data.b	243,1

	.data.b	51
	.section	.debug_str		;off: 1501
	.data.b	72,73,82,90,69,82,95,66,85,83,95,80,82,79,84,79,67,79,76,95,65,78,89,0
	.section	.debug_info		;off: 997
	.data.w	.Ldw_str_begin+1501
	.data.b	155,1
	.data.b	5
	.data.b	6
	.data.b	244,1

	.data.b	51
	.section	.debug_str		;off: 1525
	.data.b	72,73,82,90,69,82,95,73,81,95,69,77,80,84,89,95,78,79,95,77,73,83,83,0
	.section	.debug_info		;off: 1008
	.data.w	.Ldw_str_begin+1525
	.data.b	156,1
	.data.b	5
	.data.b	6
	.data.b	128,2

	.data.b	51
	.section	.debug_str		;off: 1549
	.data.b	72,73,82,90,69,82,95,73,81,95,69,77,80,84,89,95,65,88,73,95,77,73,83,83,0
	.section	.debug_info		;off: 1019
	.data.w	.Ldw_str_begin+1549
	.data.b	157,1
	.data.b	5
	.data.b	6
	.data.b	129,2

	.data.b	51
	.section	.debug_str		;off: 1574
	.data.b	72,73,82,90,69,82,95,73,81,95,69,77,80,84,89,95,70,76,65,83,72,95,77,73,83,83,0
	.section	.debug_info		;off: 1030
	.data.w	.Ldw_str_begin+1574
	.data.b	158,1
	.data.b	5
	.data.b	6
	.data.b	130,2

	.data.b	51
	.section	.debug_str		;off: 1601
	.data.b	72,73,82,90,69,82,95,73,78,84,69,82,76,79,67,75,95,79,84,72,69,82,0
	.section	.debug_info		;off: 1041
	.data.w	.Ldw_str_begin+1601
	.data.b	159,1
	.data.b	5
	.data.b	6
	.data.b	131,2

	.data.b	51
	.section	.debug_str		;off: 1624
	.data.b	72,73,82,90,69,82,95,73,78,84,69,82,76,79,67,75,95,65,71,85,0
	.section	.debug_info		;off: 1052
	.data.w	.Ldw_str_begin+1624
	.data.b	160,1
	.data.b	5
	.data.b	6
	.data.b	132,2

	.data.b	51
	.section	.debug_str		;off: 1645
	.data.b	72,73,82,90,69,82,95,73,78,84,69,82,76,79,67,75,95,70,80,65,83,73,77,68,0
	.section	.debug_info		;off: 1063
	.data.w	.Ldw_str_begin+1645
	.data.b	161,1
	.data.b	5
	.data.b	6
	.data.b	133,2

	.data.b	51
	.section	.debug_str		;off: 1670
	.data.b	72,73,82,90,69,82,95,76,79,65,68,95,83,84,65,76,76,95,65,88,73,0
	.section	.debug_info		;off: 1074
	.data.w	.Ldw_str_begin+1670
	.data.b	162,1
	.data.b	5
	.data.b	6
	.data.b	134,2

	.data.b	51
	.section	.debug_str		;off: 1692
	.data.b	72,73,82,90,69,82,95,76,79,65,68,95,83,84,65,76,76,95,70,76,65,83,72,0
	.section	.debug_info		;off: 1085
	.data.w	.Ldw_str_begin+1692
	.data.b	163,1
	.data.b	5
	.data.b	6
	.data.b	135,2

	.data.b	51
	.section	.debug_str		;off: 1716
	.data.b	72,73,82,90,69,82,95,87,82,95,83,84,65,76,76,95,83,84,79,82,69,0
	.section	.debug_info		;off: 1096
	.data.w	.Ldw_str_begin+1716
	.data.b	164,1
	.data.b	5
	.data.b	6
	.data.b	136,2

	.data.b	51
	.section	.debug_str		;off: 1738
	.data.b	72,73,82,90,69,82,95,87,82,95,83,84,65,76,76,95,65,88,73,95,83,84,66,95,70,85,76,76,0
	.section	.debug_info		;off: 1107
	.data.w	.Ldw_str_begin+1738
	.data.b	165,1
	.data.b	5
	.data.b	6
	.data.b	137,2

	.data.b	51
	.section	.debug_str		;off: 1767
	.data.b	72,73,82,90,69,82,95,87,82,95,83,84,65,76,76,95,84,67,77,95,83,84,66,95,70,85,76,76,0
	.section	.debug_info		;off: 1118
	.data.w	.Ldw_str_begin+1767
	.data.b	166,1
	.data.b	5
	.data.b	6
	.data.b	138,2

	.data.b	51
	.section	.debug_str		;off: 1796
	.data.b	72,73,82,90,69,82,95,87,82,95,83,84,65,76,76,95,76,76,80,80,95,83,84,66,95,70,85,76,76,0
	.section	.debug_info		;off: 1129
	.data.w	.Ldw_str_begin+1796
	.data.b	167,1
	.data.b	5
	.data.b	6
	.data.b	139,2

	.data.b	51
	.section	.debug_str		;off: 1826
	.data.b	72,73,82,90,69,82,95,66,65,82,82,73,69,82,95,83,84,65,76,76,95,66,65,82,82,73,69,82,0
	.section	.debug_info		;off: 1140
	.data.w	.Ldw_str_begin+1826
	.data.b	168,1
	.data.b	5
	.data.b	6
	.data.b	140,2

	.data.b	51
	.section	.debug_str		;off: 1855
	.data.b	72,73,82,90,69,82,95,66,65,82,82,73,69,82,95,83,84,79,82,69,95,65,88,73,87,82,73,84,69,0
	.section	.debug_info		;off: 1151
	.data.w	.Ldw_str_begin+1855
	.data.b	169,1
	.data.b	5
	.data.b	6
	.data.b	141,2

	.data.b	51
	.section	.debug_str		;off: 1885
	.data.b	72,73,82,90,69,82,95,73,67,95,87,84,95,72,73,84,0
	.section	.debug_info		;off: 1162
	.data.w	.Ldw_str_begin+1885
	.data.b	170,1
	.data.b	5
	.data.b	6
	.data.b	128,4

	.data.b	51
	.section	.debug_str		;off: 1902
	.data.b	72,73,82,90,69,82,95,68,67,95,87,84,95,72,73,84,0
	.section	.debug_info		;off: 1173
	.data.w	.Ldw_str_begin+1902
	.data.b	171,1
	.data.b	5
	.data.b	6
	.data.b	129,4

	.data.b	51
	.section	.debug_str		;off: 1919
	.data.b	72,73,82,90,69,82,95,73,95,85,77,80,85,95,72,73,84,0
	.section	.debug_info		;off: 1184
	.data.w	.Ldw_str_begin+1919
	.data.b	172,1
	.data.b	5
	.data.b	6
	.data.b	130,4

	.data.b	51
	.section	.debug_str		;off: 1937
	.data.b	72,73,82,90,69,82,95,68,95,85,77,80,85,95,72,73,84,0
	.section	.debug_info		;off: 1195
	.data.w	.Ldw_str_begin+1937
	.data.b	173,1
	.data.b	5
	.data.b	6
	.data.b	131,4

	.data.b	51
	.section	.debug_str		;off: 1955
	.data.b	72,73,82,90,69,82,95,73,67,95,67,65,67,72,69,95,72,73,84,0
	.section	.debug_info		;off: 1206
	.data.w	.Ldw_str_begin+1955
	.data.b	174,1
	.data.b	5
	.data.b	6
	.data.b	132,4

	.data.b	51
	.section	.debug_str		;off: 1975
	.data.b	72,73,82,90,69,82,95,73,67,95,76,70,66,95,72,73,84,0
	.section	.debug_info		;off: 1217
	.data.w	.Ldw_str_begin+1975
	.data.b	175,1
	.data.b	5
	.data.b	6
	.data.b	133,4

	.data.b	51
	.section	.debug_str		;off: 1993
	.data.b	72,73,82,90,69,82,95,73,67,95,66,73,85,95,72,73,84,0
	.section	.debug_info		;off: 1228
	.data.w	.Ldw_str_begin+1993
	.data.b	176,1
	.data.b	5
	.data.b	6
	.data.b	134,4

	.data.b	51
	.section	.debug_str		;off: 2011
	.data.b	72,73,82,90,69,82,95,73,67,95,72,73,78,84,95,82,69,81,0
	.section	.debug_info		;off: 1239
	.data.w	.Ldw_str_begin+2011
	.data.b	177,1
	.data.b	5
	.data.b	6
	.data.b	135,4

	.data.b	51
	.section	.debug_str		;off: 2030
	.data.b	72,73,82,90,69,82,95,68,67,95,84,65,71,95,65,67,67,69,83,83,0
	.section	.debug_info		;off: 1250
	.data.w	.Ldw_str_begin+2030
	.data.b	178,1
	.data.b	5
	.data.b	6
	.data.b	136,4

	.data.b	51
	.section	.debug_str		;off: 2051
	.data.b	72,73,82,90,69,82,95,68,67,95,68,65,84,65,95,65,67,67,69,83,83,0
	.section	.debug_info		;off: 1261
	.data.w	.Ldw_str_begin+2051
	.data.b	179,1
	.data.b	5
	.data.b	6
	.data.b	137,4

	.data.b	51
	.section	.debug_str		;off: 2073
	.data.b	72,73,82,90,69,82,95,84,67,77,95,65,67,67,69,83,83,0
	.section	.debug_info		;off: 1272
	.data.w	.Ldw_str_begin+2073
	.data.b	180,1
	.data.b	5
	.data.b	6
	.data.b	138,4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2091
	.data.b	80,77,85,95,69,118,101,110,116,67,111,117,110,116,101,114,73,68,0
	.section	.debug_info		;off: 1284
	.data.w	.Ldw_str_begin+2091
	.data.b	181,1
	.data.b	3
	.data.b	6
	.data.w	.Ldw_begin+267

	.data.b	25
	.section	.debug_str		;off: 2110
	.data.b	80,77,85,95,72,97,108,95,73,115,82,105,103,104,116,69,118,101,110,116,0
	.section	.debug_info		;off: 1297
	.data.w	.Ldw_str_begin+2110
	.data.b	72
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+219
	.data.w	PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
	.data.w	__ghs_eofn_PMU_Hal_IsRightEvent
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 102
	.data.b	25
	.data.b	46
	.data.b	1
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
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
	.data.w	PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
	.data.w	__ghs_eofn_PMU_Hal_IsRightEvent-PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 352
	.data.b	0,5,2
	.data.w	PMU_Hal_IsRightEvent..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cpmu_hal.
	.data.b	6
	.data.b	3
	.data.b	200,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	44
	.data.b	27
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1329
	.data.b	22
	.section	.debug_str		;off: 2131
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 1330
	.data.w	.Ldw_str_begin+2131
	.data.b	72
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW01
	.data.w	.LDW11
	.data.b	1,0
	.data.b	80
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 150
	.data.b	22
	.data.b	5
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	75,12
	.data.b	2,6
	.data.b	0,0

	.section	.debug_info		;off: 1346
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 169
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 1355
	.data.b	7
	.section	.debug_str		;off: 2141
	.data.b	98,82,101,116,0
	.section	.debug_info		;off: 1356
	.data.w	.Ldw_str_begin+2141
	.data.b	74
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+219
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+30
	.section	.debug_loc		;off: 30
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 178
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

	.section	.debug_info		;off: 1373
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2146
	.data.b	80,77,85,95,72,97,108,95,73,110,105,116,105,97,108,105,122,101,0
	.section	.debug_info		;off: 1376
	.data.w	.Ldw_str_begin+2146
	.data.b	93
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_Initialize
	.data.w	__ghs_eofn_PMU_Hal_Initialize
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 199
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_Initialize
	.data.w	__ghs_eofn_PMU_Hal_Initialize-PMU_Hal_Initialize
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 385
	.data.b	0,5,2
	.data.w	PMU_Hal_Initialize
	.data.b	6
	.data.b	3
	.data.b	225,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1404
	.data.b	22
	.section	.debug_str		;off: 2165
	.data.b	98,67,108,111,99,107,68,105,118,0
	.section	.debug_info		;off: 1405
	.data.w	.Ldw_str_begin+2165
	.data.b	93
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+231
	.data.b	0
	.data.w	.Ldw_loc_begin+49
	.section	.debug_loc		;off: 49
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1421
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 2175
	.data.b	117,80,77,67,82,0
	.section	.debug_info		;off: 1431
	.data.w	.Ldw_str_begin+2175
	.data.b	95
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1448
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2181
	.data.b	80,77,85,95,72,97,108,95,68,101,105,110,105,116,105,97,108,105,122,101,0
	.section	.debug_info		;off: 1451
	.data.w	.Ldw_str_begin+2181
	.data.b	116
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_Deinitialize
	.data.w	__ghs_eofn_PMU_Hal_Deinitialize
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
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
	.data.w	PMU_Hal_Deinitialize
	.data.w	__ghs_eofn_PMU_Hal_Deinitialize-PMU_Hal_Deinitialize
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 429
	.data.b	0,5,2
	.data.w	PMU_Hal_Deinitialize
	.data.b	6
	.data.b	3
	.data.b	249,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1479
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	8
	.section	.debug_str		;off: 2202
	.data.b	117,80,77,67,82,0
	.section	.debug_info		;off: 1489
	.data.w	.Ldw_str_begin+2202
	.data.b	118
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 245
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

	.section	.debug_info		;off: 1502
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2208
	.data.b	80,77,85,95,72,97,108,95,82,101,115,101,116,67,121,99,67,110,116,0
	.section	.debug_info		;off: 1505
	.data.w	.Ldw_str_begin+2208
	.data.b	131,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_ResetCycCnt
	.data.w	__ghs_eofn_PMU_Hal_ResetCycCnt
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
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
	.data.w	PMU_Hal_ResetCycCnt
	.data.w	__ghs_eofn_PMU_Hal_ResetCycCnt-PMU_Hal_ResetCycCnt
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 468
	.data.b	0,5,2
	.data.w	PMU_Hal_ResetCycCnt
	.data.b	6
	.data.b	3
	.data.b	136,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1534
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	8
	.section	.debug_str		;off: 2228
	.data.b	117,80,77,67,82,0
	.section	.debug_info		;off: 1544
	.data.w	.Ldw_str_begin+2228
	.data.b	133,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2234
	.data.b	80,77,85,95,72,97,108,95,69,110,67,121,99,67,110,116,0
	.section	.debug_info		;off: 1561
	.data.w	.Ldw_str_begin+2234
	.data.b	146,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_EnCycCnt
	.data.w	__ghs_eofn_PMU_Hal_EnCycCnt
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_EnCycCnt
	.data.w	__ghs_eofn_PMU_Hal_EnCycCnt-PMU_Hal_EnCycCnt
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 507
	.data.b	0,5,2
	.data.w	PMU_Hal_EnCycCnt
	.data.b	6
	.data.b	3
	.data.b	151,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1590
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	8
	.section	.debug_str		;off: 2251
	.data.b	117,80,77,67,78,84,69,78,83,69,84,0
	.section	.debug_info		;off: 1600
	.data.w	.Ldw_str_begin+2251
	.data.b	148,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2263
	.data.b	80,77,85,95,72,97,108,95,68,105,115,67,121,99,67,110,116,0
	.section	.debug_info		;off: 1617
	.data.w	.Ldw_str_begin+2263
	.data.b	161,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_DisCycCnt
	.data.w	__ghs_eofn_PMU_Hal_DisCycCnt
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_DisCycCnt
	.data.w	__ghs_eofn_PMU_Hal_DisCycCnt-PMU_Hal_DisCycCnt
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 546
	.data.b	0,5,2
	.data.w	PMU_Hal_DisCycCnt
	.data.b	6
	.data.b	3
	.data.b	166,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1646
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	8
	.section	.debug_str		;off: 2281
	.data.b	117,80,77,67,78,84,69,78,67,76,82,0
	.section	.debug_info		;off: 1656
	.data.w	.Ldw_str_begin+2281
	.data.b	163,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2293
	.data.b	80,77,85,95,72,97,108,95,71,101,116,67,121,99,67,110,116,86,97,108,0
	.section	.debug_info		;off: 1673
	.data.w	.Ldw_str_begin+2293
	.data.b	176,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+255
	.data.w	PMU_Hal_GetCycCntVal
	.data.w	__ghs_eofn_PMU_Hal_GetCycCntVal
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_GetCycCntVal
	.data.w	__ghs_eofn_PMU_Hal_GetCycCntVal-PMU_Hal_GetCycCntVal
	.data.b	1
	.data.w	.LDW23
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 585
	.data.b	0,5,2
	.data.w	PMU_Hal_GetCycCntVal
	.data.b	6
	.data.b	3
	.data.b	180,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1706
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW23

	.data.b	8
	.section	.debug_str		;off: 2314
	.data.b	117,80,77,67,67,78,84,82,0
	.section	.debug_info		;off: 1716
	.data.w	.Ldw_str_begin+2314
	.data.b	178,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+255
	.data.b	0
	.data.b	0

	.data.b	34
	.data.w	.LDW03
	.data.w	.LDW13

	.data.b	8
	.section	.debug_str		;off: 2323
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 1740
	.data.w	.Ldw_str_begin+2323
	.data.b	181,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 2333
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 1755
	.data.w	.Ldw_str_begin+2333
	.data.b	181,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2343
	.data.b	80,77,85,95,72,97,108,95,82,101,115,101,116,65,108,108,69,118,116,67,110,116,0
	.section	.debug_info		;off: 1773
	.data.w	.Ldw_str_begin+2343
	.data.b	187,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_ResetAllEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_ResetAllEvtCnt
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_ResetAllEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_ResetAllEvtCnt-PMU_Hal_ResetAllEvtCnt
	.data.b	1
	.data.w	.LDW53
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 612
	.data.b	0,5,2
	.data.w	PMU_Hal_ResetAllEvtCnt
	.data.b	6
	.data.b	3
	.data.b	192,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1802
	.data.b	34
	.data.w	.LDW43
	.data.w	.LDW53

	.data.b	8
	.section	.debug_str		;off: 2366
	.data.b	117,80,77,67,82,0
	.section	.debug_info		;off: 1812
	.data.w	.Ldw_str_begin+2366
	.data.b	189,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2372
	.data.b	80,77,85,95,72,97,108,95,69,110,69,118,116,67,110,116,0
	.section	.debug_info		;off: 1829
	.data.w	.Ldw_str_begin+2372
	.data.b	202,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_EnEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_EnEvtCnt
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_EnEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_EnEvtCnt-PMU_Hal_EnEvtCnt
	.data.b	1
	.data.w	.LDW83
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 651
	.data.b	0,5,2
	.data.w	PMU_Hal_EnEvtCnt
	.data.b	6
	.data.b	3
	.data.b	202,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1860
	.data.b	22
	.section	.debug_str		;off: 2389
	.data.b	117,77,97,115,107,0
	.section	.debug_info		;off: 1861
	.data.w	.Ldw_str_begin+2389
	.data.b	202,1
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+87
	.section	.debug_loc		;off: 87
	.data.w	.LDW63
	.data.w	.LDW73
	.data.b	1,0
	.data.b	80
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1878
	.data.b	34
	.data.w	.LDW73
	.data.w	.LDW83

	.data.b	8
	.section	.debug_str		;off: 2395
	.data.b	117,80,77,67,78,84,69,78,83,69,84,0
	.section	.debug_info		;off: 1888
	.data.w	.Ldw_str_begin+2395
	.data.b	204,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2407
	.data.b	80,77,85,95,72,97,108,95,68,105,115,69,118,116,67,110,116,0
	.section	.debug_info		;off: 1905
	.data.w	.Ldw_str_begin+2407
	.data.b	219,1
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_DisEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_DisEvtCnt
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_DisEvtCnt
	.data.w	__ghs_eofn_PMU_Hal_DisEvtCnt-PMU_Hal_DisEvtCnt
	.data.b	1
	.data.w	.LDW14
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 696
	.data.b	0,5,2
	.data.w	PMU_Hal_DisEvtCnt
	.data.b	6
	.data.b	3
	.data.b	219,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1936
	.data.b	22
	.section	.debug_str		;off: 2425
	.data.b	117,77,97,115,107,0
	.section	.debug_info		;off: 1937
	.data.w	.Ldw_str_begin+2425
	.data.b	219,1
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW93
	.data.w	.LDW04
	.data.b	1,0
	.data.b	80
	.data.w	.LDW04
	.data.w	.LDW14
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1954
	.data.b	34
	.data.w	.LDW04
	.data.w	.LDW14

	.data.b	8
	.section	.debug_str		;off: 2431
	.data.b	117,80,77,67,78,84,69,78,67,76,82,0
	.section	.debug_info		;off: 1964
	.data.w	.Ldw_str_begin+2431
	.data.b	221,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2443
	.data.b	80,77,85,95,72,97,108,95,71,101,116,69,118,116,67,110,116,86,97,108,0
	.section	.debug_info		;off: 1981
	.data.w	.Ldw_str_begin+2443
	.data.b	236,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.w	PMU_Hal_GetEvtCntVal
	.data.w	__ghs_eofn_PMU_Hal_GetEvtCntVal
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 384
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_GetEvtCntVal
	.data.w	__ghs_eofn_PMU_Hal_GetEvtCntVal-PMU_Hal_GetEvtCntVal
	.data.b	1
	.data.w	.LDW44
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 741
	.data.b	0,5,2
	.data.w	PMU_Hal_GetEvtCntVal
	.data.b	6
	.data.b	3
	.data.b	238,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	27
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	11
	.data.b	3
	.data.b	100
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2014
	.data.b	22
	.section	.debug_str		;off: 2464
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 2015
	.data.w	.Ldw_str_begin+2464
	.data.b	236,1
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+147
	.section	.debug_loc		;off: 147
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2032
	.data.b	34
	.data.w	.LDW34
	.data.w	.LDW44

	.data.b	8
	.section	.debug_str		;off: 2474
	.data.b	117,80,77,69,86,67,78,84,82,0
	.section	.debug_info		;off: 2042
	.data.w	.Ldw_str_begin+2474
	.data.b	238,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2484
	.data.b	80,77,85,95,72,97,108,95,83,101,116,69,118,116,67,110,116,86,97,108,0
	.section	.debug_info		;off: 2059
	.data.w	.Ldw_str_begin+2484
	.data.b	151,2
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_SetEvtCntVal
	.data.w	__ghs_eofn_PMU_Hal_SetEvtCntVal
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_SetEvtCntVal
	.data.w	__ghs_eofn_PMU_Hal_SetEvtCntVal-PMU_Hal_SetEvtCntVal
	.data.b	1
	.data.w	.LDW74
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 830
	.data.b	0,5,2
	.data.w	PMU_Hal_SetEvtCntVal
	.data.b	6
	.data.b	3
	.data.b	157,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	27
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	11
	.data.b	3
	.data.b	100
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2088
	.data.b	22
	.section	.debug_str		;off: 2505
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 2089
	.data.w	.Ldw_str_begin+2505
	.data.b	151,2
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+166
	.section	.debug_loc		;off: 166
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2106
	.data.b	22
	.section	.debug_str		;off: 2515
	.data.b	117,86,97,108,0
	.section	.debug_info		;off: 2107
	.data.w	.Ldw_str_begin+2515
	.data.b	151,2
	.data.b	52
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+185
	.section	.debug_loc		;off: 185
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2124
	.data.b	34
	.data.w	.LDW64
	.data.w	.LDW74

	.data.b	7
	.section	.debug_str		;off: 2520
	.data.b	117,80,77,69,86,67,78,84,82,0
	.section	.debug_info		;off: 2134
	.data.w	.Ldw_str_begin+2520
	.data.b	153,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+204
	.section	.debug_loc		;off: 204
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2152
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2530
	.data.b	80,77,85,95,72,97,108,95,83,101,116,69,118,116,67,110,116,84,121,112,101,0
	.section	.debug_info		;off: 2155
	.data.w	.Ldw_str_begin+2530
	.data.b	196,2
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_SetEvtCntType
	.data.w	__ghs_eofn_PMU_Hal_SetEvtCntType
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_SetEvtCntType
	.data.w	__ghs_eofn_PMU_Hal_SetEvtCntType-PMU_Hal_SetEvtCntType
	.data.b	1
	.data.w	.LDW05
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 919
	.data.b	0,5,2
	.data.w	PMU_Hal_SetEvtCntType
	.data.b	6
	.data.b	3
	.data.b	199,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	40
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	11
	.data.b	3
	.data.b	80
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin33
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin36
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin37
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin38
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2184
	.data.b	22
	.section	.debug_str		;off: 2552
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 2185
	.data.w	.Ldw_str_begin+2552
	.data.b	196,2
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+223
	.section	.debug_loc		;off: 223
	.data.w	.LDW94
	.data.w	.LDW05
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2202
	.data.b	22
	.section	.debug_str		;off: 2562
	.data.b	117,67,110,116,84,121,112,101,0
	.section	.debug_info		;off: 2203
	.data.w	.Ldw_str_begin+2562
	.data.b	196,2
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+242
	.section	.debug_loc		;off: 242
	.data.w	.LDW94
	.data.w	.LDW05
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2220
	.data.b	34
	.data.w	.LDW94
	.data.w	.LDW05

	.data.b	8
	.section	.debug_str		;off: 2571
	.data.b	117,80,77,69,86,84,89,80,69,82,0
	.section	.debug_info		;off: 2230
	.data.w	.Ldw_str_begin+2571
	.data.b	198,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2582
	.data.b	80,77,85,95,72,97,108,95,71,101,116,69,118,116,67,110,116,79,118,115,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2247
	.data.w	.Ldw_str_begin+2582
	.data.b	130,3
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.w	PMU_Hal_GetEvtCntOvsStatus
	.data.w	__ghs_eofn_PMU_Hal_GetEvtCntOvsStatus
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_GetEvtCntOvsStatus
	.data.w	__ghs_eofn_PMU_Hal_GetEvtCntOvsStatus-PMU_Hal_GetEvtCntOvsStatus
	.data.b	1
	.data.w	.LDW35
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1064
	.data.b	0,5,2
	.data.w	PMU_Hal_GetEvtCntOvsStatus
	.data.b	6
	.data.b	3
	.data.b	130,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	75
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin39
	.data.b	11
	.data.b	27
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2282
	.data.b	22
	.section	.debug_str		;off: 2609
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 2283
	.data.w	.Ldw_str_begin+2609
	.data.b	130,3
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+261
	.section	.debug_loc		;off: 261
	.data.w	.LDW15
	.data.w	.LDW25
	.data.b	1,0
	.data.b	80
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2300
	.data.b	34
	.data.w	.LDW25
	.data.w	.LDW35

	.data.b	7
	.section	.debug_str		;off: 2619
	.data.b	117,80,77,79,86,83,83,69,84,0
	.section	.debug_info		;off: 2310
	.data.w	.Ldw_str_begin+2619
	.data.b	132,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+291
	.section	.debug_loc		;off: 291
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2328
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2629
	.data.b	80,77,85,95,72,97,108,95,67,108,101,97,114,69,118,67,110,79,118,115,0
	.section	.debug_info		;off: 2331
	.data.w	.Ldw_str_begin+2629
	.data.b	153,3
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_ClearEvCnOvs
	.data.w	__ghs_eofn_PMU_Hal_ClearEvCnOvs
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_ClearEvCnOvs
	.data.w	__ghs_eofn_PMU_Hal_ClearEvCnOvs-PMU_Hal_ClearEvCnOvs
	.data.b	1
	.data.w	.LDW65
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1106
	.data.b	0,5,2
	.data.w	PMU_Hal_ClearEvCnOvs
	.data.b	6
	.data.b	3
	.data.b	153,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	75
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin40
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin41
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2362
	.data.b	22
	.section	.debug_str		;off: 2650
	.data.b	117,77,97,115,107,0
	.section	.debug_info		;off: 2363
	.data.w	.Ldw_str_begin+2650
	.data.b	153,3
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+310
	.section	.debug_loc		;off: 310
	.data.w	.LDW45
	.data.w	.LDW55
	.data.b	1,0
	.data.b	80
	.data.w	.LDW55
	.data.w	.LDW65
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2380
	.data.b	34
	.data.w	.LDW55
	.data.w	.LDW65

	.data.b	8
	.section	.debug_str		;off: 2656
	.data.b	117,80,77,79,86,83,82,0
	.section	.debug_info		;off: 2390
	.data.w	.Ldw_str_begin+2656
	.data.b	155,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2664
	.data.b	80,77,85,95,72,97,108,95,69,110,69,118,116,79,118,115,73,114,113,0
	.section	.debug_info		;off: 2407
	.data.w	.Ldw_str_begin+2664
	.data.b	171,3
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_EnEvtOvsIrq
	.data.w	__ghs_eofn_PMU_Hal_EnEvtOvsIrq
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_EnEvtOvsIrq
	.data.w	__ghs_eofn_PMU_Hal_EnEvtOvsIrq-PMU_Hal_EnEvtOvsIrq
	.data.b	1
	.data.w	.LDW95
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1151
	.data.b	0,5,2
	.data.w	PMU_Hal_EnEvtOvsIrq
	.data.b	6
	.data.b	3
	.data.b	171,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	75
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin42
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin43
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2438
	.data.b	22
	.section	.debug_str		;off: 2684
	.data.b	117,77,97,115,107,0
	.section	.debug_info		;off: 2439
	.data.w	.Ldw_str_begin+2684
	.data.b	171,3
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+340
	.section	.debug_loc		;off: 340
	.data.w	.LDW75
	.data.w	.LDW85
	.data.b	1,0
	.data.b	80
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2456
	.data.b	34
	.data.w	.LDW85
	.data.w	.LDW95

	.data.b	8
	.section	.debug_str		;off: 2690
	.data.b	117,80,77,73,78,84,69,78,83,69,84,0
	.section	.debug_info		;off: 2466
	.data.w	.Ldw_str_begin+2690
	.data.b	173,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2702
	.data.b	80,77,85,95,72,97,108,95,68,105,115,69,118,116,79,118,115,73,114,113,0
	.section	.debug_info		;off: 2483
	.data.w	.Ldw_str_begin+2702
	.data.b	191,3
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_DisEvtOvsIrq
	.data.w	__ghs_eofn_PMU_Hal_DisEvtOvsIrq
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_DisEvtOvsIrq
	.data.w	__ghs_eofn_PMU_Hal_DisEvtOvsIrq-PMU_Hal_DisEvtOvsIrq
	.data.b	1
	.data.w	.LDW26
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1196
	.data.b	0,5,2
	.data.w	PMU_Hal_DisEvtOvsIrq
	.data.b	6
	.data.b	3
	.data.b	191,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	75
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin44
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin45
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2514
	.data.b	22
	.section	.debug_str		;off: 2723
	.data.b	117,77,97,115,107,0
	.section	.debug_info		;off: 2515
	.data.w	.Ldw_str_begin+2723
	.data.b	191,3
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+370
	.section	.debug_loc		;off: 370
	.data.w	.LDW06
	.data.w	.LDW16
	.data.b	1,0
	.data.b	80
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2532
	.data.b	34
	.data.w	.LDW16
	.data.w	.LDW26

	.data.b	8
	.section	.debug_str		;off: 2729
	.data.b	117,80,77,73,78,84,69,78,67,76,82,0
	.section	.debug_info		;off: 2542
	.data.w	.Ldw_str_begin+2729
	.data.b	193,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2741
	.data.b	80,77,85,95,72,97,108,95,69,118,116,73,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 2559
	.data.w	.Ldw_str_begin+2741
	.data.b	209,3
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_EvtIncrement
	.data.w	__ghs_eofn_PMU_Hal_EvtIncrement
	.data.b	1
	.data.b	93
	.data.b	144,128,1
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_EvtIncrement
	.data.w	__ghs_eofn_PMU_Hal_EvtIncrement-PMU_Hal_EvtIncrement
	.data.b	1
	.data.w	.LDW56
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1241
	.data.b	0,5,2
	.data.w	PMU_Hal_EvtIncrement
	.data.b	6
	.data.b	3
	.data.b	209,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	75
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin46
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2590
	.data.b	22
	.section	.debug_str		;off: 2762
	.data.b	117,67,110,116,73,110,100,101,120,0
	.section	.debug_info		;off: 2591
	.data.w	.Ldw_str_begin+2762
	.data.b	209,3
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+400
	.section	.debug_loc		;off: 400
	.data.w	.LDW36
	.data.w	.LDW46
	.data.b	1,0
	.data.b	80
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2608
	.data.b	34
	.data.w	.LDW46
	.data.w	.LDW56

	.data.b	8
	.section	.debug_str		;off: 2772
	.data.b	117,80,77,83,87,73,78,67,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+2772
	.data.b	211,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 2781
	.data.b	80,77,85,95,72,97,108,95,69,110,97,98,108,101,85,115,101,114,77,111,100,101,0
	.section	.debug_info		;off: 2635
	.data.w	.Ldw_str_begin+2781
	.data.b	225,3
	.data.b	6
	.data.b	1
	.data.w	PMU_Hal_EnableUserMode
	.data.w	__ghs_eofn_PMU_Hal_EnableUserMode
	.data.b	1
	.data.b	93
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	124
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	PMU_Hal_EnableUserMode
	.data.w	__ghs_eofn_PMU_Hal_EnableUserMode-PMU_Hal_EnableUserMode
	.data.b	1
	.data.w	.LDW86
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1278
	.data.b	0,5,2
	.data.w	PMU_Hal_EnableUserMode
	.data.b	6
	.data.b	3
	.data.b	232,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin47
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2664
	.data.b	22
	.section	.debug_str		;off: 2804
	.data.b	117,77,111,100,101,0
	.section	.debug_info		;off: 2665
	.data.w	.Ldw_str_begin+2804
	.data.b	225,3
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.w	.Ldw_loc_begin+430
	.section	.debug_loc		;off: 430
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2682
	.data.b	34
	.data.w	.LDW76
	.data.w	.LDW86

	.data.b	8
	.section	.debug_str		;off: 2810
	.data.b	117,80,77,85,83,69,82,69,78,82,0
	.section	.debug_info		;off: 2692
	.data.w	.Ldw_str_begin+2810
	.data.b	227,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+243
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.section	.debug_macinfo		;off: 0
	.data.b	1
	.data.b	0
	.data.b	95,95,103,104,115,95,95,32,49,0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	38
	.data.b	2
	.data.b	3
	.data.b	24
	.data.b	3
	.data.b	3
	.data.b	13
	.data.b	4
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
	.data.b	64
	.data.b	71,69,84,95,67,80,40,99,112,44,111,112,49,44,82,116,44,67,82,110,44,67,82,109,44,111,112,50,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,82,67,32,112,34,32,35,99,112,32,34,44,32,34,32
	.data.b	35,111,112,49,32,34,44,32,37,48,44,32,99,34,32,35,67,82,110,32,34,44,32,99,34,32,35,67,82,109,32,34,44,32,34,32,35,111,112,50,32,58,32,34,61,114,34,40,82,116,41,32,58,32,58,32,34,109,101,109
	.data.b	111,114,121,34,41,0
	.data.b	1
	.data.b	67
	.data.b	83,69,84,95,67,80,40,99,112,44,111,112,49,44,82,116,44,67,82,110,44,67,82,109,44,111,112,50,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,67,82,32,112,34,32,35,99,112,32,34,44,32,34,32
	.data.b	35,111,112,49,32,34,44,32,37,48,44,32,99,34,32,35,67,82,110,32,34,44,32,99,34,32,35,67,82,109,32,34,44,32,34,32,35,111,112,50,32,58,32,58,32,34,114,34,40,82,116,41,32,58,32,34,109,101,109,111
	.data.b	114,121,34,41,0
	.data.b	1
	.data.b	70
	.data.b	71,69,84,95,67,80,54,52,40,99,112,44,111,112,49,44,82,116,44,67,82,109,41,32,123,117,105,110,116,51,50,32,118,97,108,49,95,116,101,109,112,32,61,32,48,85,44,32,118,97,108,50,95,116,101,109,112,32,61,32
	.data.b	48,85,59,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,82,82,67,32,112,34,32,35,99,112,32,34,44,32,34,32,35,111,112,49,32,34,44,32,37,48,44,32,37,49,44,32,99,34,32,35,67,82,109,32,58
	.data.b	32,34,61,114,34,40,118,97,108,49,95,116,101,109,112,41,44,32,34,61,114,34,40,118,97,108,50,95,116,101,109,112,41,58,32,58,32,34,109,101,109,111,114,121,34,41,59,32,82,116,32,61,32,40,40,40,117,105,110,116
	.data.b	54,52,41,118,97,108,50,95,116,101,109,112,41,32,60,60,32,51,50,41,32,43,32,118,97,108,49,95,116,101,109,112,59,125,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	5
	.data.b	1
	.data.b	26
	.data.b	80,77,67,82,95,69,78,65,66,76,69,95,80,79,83,32,48,85,0
	.data.b	1
	.data.b	27
	.data.b	80,77,67,82,95,69,78,65,66,76,69,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,82,95,69,78,65,66,76,69,95,80,79,83,41,0
	.data.b	1
	.data.b	29
	.data.b	80,77,67,82,95,69,86,84,95,67,79,85,78,95,82,83,84,95,80,79,83,32,49,85,0
	.data.b	1
	.data.b	30
	.data.b	80,77,67,82,95,69,86,84,95,67,79,85,78,95,82,83,84,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,82,95,69,86,84,95,67,79,85,78,95,82,83,84,95,80,79,83,41,0
	.data.b	1
	.data.b	32
	.data.b	80,77,67,82,95,67,76,75,95,67,79,85,78,95,82,83,84,95,80,79,83,32,50,85,0
	.data.b	1
	.data.b	33
	.data.b	80,77,67,82,95,67,76,75,95,67,79,85,78,95,82,83,84,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,82,95,67,76,75,95,67,79,85,78,95,82,83,84,95,80,79,83,41,0
	.data.b	1
	.data.b	35
	.data.b	80,77,67,82,95,67,76,75,95,68,73,86,95,80,79,83,32,51,85,0
	.data.b	1
	.data.b	36
	.data.b	80,77,67,82,95,67,76,75,95,68,73,86,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,82,95,67,76,75,95,68,73,86,95,80,79,83,41,0
	.data.b	1
	.data.b	38
	.data.b	80,77,67,82,95,76,79,78,71,95,67,79,85,78,84,69,82,95,69,78,95,80,79,83,32,54,85,0
	.data.b	1
	.data.b	39
	.data.b	80,77,67,82,95,76,79,78,71,95,67,79,85,78,84,69,82,95,69,78,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,82,95,76,79,78,71,95,67,79,85,78,84,69,82,95,69,78,95,80,79,83,41,0
	.data.b	1
	.data.b	76
	.data.b	80,77,85,83,69,82,69,78,82,95,65,76,76,95,77,65,83,75,32,48,120,48,48,48,48,48,48,48,70,85,76,0
	.data.b	1
	.data.b	79
	.data.b	80,77,67,78,84,69,78,83,69,84,95,67,95,80,79,83,32,51,49,85,0
	.data.b	1
	.data.b	80
	.data.b	80,77,67,78,84,69,78,83,69,84,95,67,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,78,84,69,78,83,69,84,95,67,95,80,79,83,41,0
	.data.b	1
	.data.b	83
	.data.b	80,77,67,78,84,69,78,67,76,82,95,67,95,80,79,83,32,51,49,85,0
	.data.b	1
	.data.b	84
	.data.b	80,77,67,78,84,69,78,67,76,82,95,67,95,77,65,83,75,32,40,49,85,76,32,60,60,32,80,77,67,78,84,69,78,67,76,82,95,67,95,80,79,83,41,0
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	6
	.data.b	3
	.data.b	26
	.data.b	7
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	1
	.data.b	33
	.data.b	80,77,85,95,67,79,85,78,84,95,68,73,86,73,68,69,82,95,54,52,32,49,85,0
	.data.b	1
	.data.b	36
	.data.b	80,77,85,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,78,79,78,69,32,48,85,0
	.data.b	1
	.data.b	37
	.data.b	80,77,85,95,70,73,82,83,84,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,80,79,83,32,48,120,48,85,0
	.data.b	1
	.data.b	38
	.data.b	80,77,85,95,83,69,67,79,78,68,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,80,79,83,32,48,120,49,85,0
	.data.b	1
	.data.b	39
	.data.b	80,77,85,95,84,72,73,82,68,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,80,79,83,32,48,120,50,85,0
	.data.b	1
	.data.b	40
	.data.b	80,77,85,95,70,79,85,82,84,72,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,80,79,83,32,48,120,51,85,0
	.data.b	1
	.data.b	44
	.data.b	80,77,85,95,70,73,82,83,84,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,77,65,83,75,32,40,49,85,32,60,60,32,80,77,85,95,70,73,82,83,84,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95
	.data.b	80,79,83,41,0
	.data.b	1
	.data.b	45
	.data.b	80,77,85,95,83,69,67,79,78,68,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,77,65,83,75,32,40,49,85,32,60,60,32,80,77,85,95,83,69,67,79,78,68,95,69,86,69,78,84,95,67,79,85,78,84,69
	.data.b	82,95,80,79,83,41,0
	.data.b	1
	.data.b	46
	.data.b	80,77,85,95,84,72,73,82,68,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,77,65,83,75,32,40,49,85,32,60,60,32,80,77,85,95,84,72,73,82,68,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95
	.data.b	80,79,83,41,0
	.data.b	1
	.data.b	47
	.data.b	80,77,85,95,70,79,85,82,84,72,95,69,86,69,78,84,95,67,79,85,78,84,69,82,95,77,65,83,75,32,40,49,85,32,60,60,32,80,77,85,95,70,79,85,82,84,72,95,69,86,69,78,84,95,67,79,85,78,84,69
	.data.b	82,95,80,79,83,41,0
	.data.b	1
	.data.b	70
	.data.b	80,77,69,86,84,89,80,69,82,95,77,65,83,75,32,40,48,120,70,65,50,48,70,70,70,70,85,41,0
	.data.b	1
	.data.b	194,1
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	195,1
	.data.b	8
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
	.data.b	215,3
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	216,3
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	45
	.data.b	8
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
	.data.b	235,3
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	237,3
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 264
	.data.b	0
