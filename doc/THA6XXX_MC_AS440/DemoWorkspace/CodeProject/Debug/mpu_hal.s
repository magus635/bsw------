	.section ".sdk_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cmpu_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682577..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
__callee.MPU_Hal_EnableEL1.v.v::
	.size	__callee.MPU_Hal_EnableEL1.v.v,0
MPU_Hal_EnableEL1::
.LDW01:
.LDW11:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
MRC p15, 0, r0, c1, c0, 0

..gh.endasm.2:
	.endo	..gh.endasm.2

;line86
..lin.a2346e4e..49ffcdb3.0_1::
.LDWlin1:
	orr	r0,r0,1
..gh.beginasm.3:
	.endo	..gh.beginasm.3
MCR p15, 0, r0, c1, c0, 0

..gh.endasm.4:
	.endo	..gh.endasm.4

;line91
..lin.a2346e4e..49ffcdb3.0_2::
.LDWlin2:
..gh.beginasm.5:
	.endo	..gh.beginasm.5
dsb

..gh.endasm.6:
	.endo	..gh.endasm.6

;line95
..lin.a2346e4e..49ffcdb3.0_3::
.LDWlin3:
..gh.beginasm.7:
	.endo	..gh.beginasm.7
isb

..gh.endasm.8:
	.endo	..gh.endasm.8

.LDW21:
.L63:

;line96
..lin.a2346e4e..49ffcdb3.0_4::
.LDWlin4:
	ret	
__ghs_eofn_MPU_Hal_EnableEL1::
	.endf	MPU_Hal_EnableEL1

	.section ".bss","awb"
.L45:
	.endo	.L45
	.section ".ghrettbl",""
	.align	4
.L64:	.data.w	.L63
	.endo	.L64
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
__callee.MPU_Hal_DisableEL1.v.v::
	.size	__callee.MPU_Hal_DisableEL1.v.v,0
MPU_Hal_DisableEL1::
.LDW31:
.LDW41:
..gh.beginasm.10:
	.endo	..gh.beginasm.10
dmb

..gh.endasm.11:
	.endo	..gh.endasm.11

;line114
..lin.a2346e4e..78640040.0_5::
.LDWlin5:
..gh.beginasm.12:
	.endo	..gh.beginasm.12
MRC p15, 0, r0, c1, c0, 0

..gh.endasm.13:
	.endo	..gh.endasm.13

;line120
..lin.a2346e4e..78640040.0_6::
.LDWlin6:
	bic	r0,r0,1
..gh.beginasm.14:
	.endo	..gh.beginasm.14
MCR p15, 0, r0, c1, c0, 0

..gh.endasm.15:
	.endo	..gh.endasm.15

;line125
..lin.a2346e4e..78640040.0_7::
.LDWlin7:
..gh.beginasm.16:
	.endo	..gh.beginasm.16
dsb

..gh.endasm.17:
	.endo	..gh.endasm.17

;line129
..lin.a2346e4e..78640040.0_8::
.LDWlin8:
..gh.beginasm.18:
	.endo	..gh.beginasm.18
isb

..gh.endasm.19:
	.endo	..gh.endasm.19

.LDW51:
.L127:

;line130
..lin.a2346e4e..78640040.0_9::
.LDWlin9:
	ret	
__ghs_eofn_MPU_Hal_DisableEL1::
	.endf	MPU_Hal_DisableEL1

	.section ".bss","awb"
.L109:
	.endo	.L109
	.section ".ghrettbl",""
.L128:	.data.w	.L127
	.endo	.L128
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
__callee.MPU_Hal_EnableEL2.v.v::
	.size	__callee.MPU_Hal_EnableEL2.v.v,0
MPU_Hal_EnableEL2::
.LDW61:
.LDW71:
..gh.beginasm.21:
	.endo	..gh.beginasm.21
MRC p15, 4, r0, c1, c0, 0

..gh.endasm.22:
	.endo	..gh.endasm.22

;line149
..lin.a2346e4e..49ffcdb4.0_10::
.LDWlin10:
	orr	r0,r0,1
..gh.beginasm.23:
	.endo	..gh.beginasm.23
MCR p15, 4, r0, c1, c0, 0

..gh.endasm.24:
	.endo	..gh.endasm.24

;line154
..lin.a2346e4e..49ffcdb4.0_11::
.LDWlin11:
..gh.beginasm.25:
	.endo	..gh.beginasm.25
dsb

..gh.endasm.26:
	.endo	..gh.endasm.26

;line158
..lin.a2346e4e..49ffcdb4.0_12::
.LDWlin12:
..gh.beginasm.27:
	.endo	..gh.beginasm.27
isb

..gh.endasm.28:
	.endo	..gh.endasm.28

.LDW81:
.L191:

;line159
..lin.a2346e4e..49ffcdb4.0_13::
.LDWlin13:
	ret	
__ghs_eofn_MPU_Hal_EnableEL2::
	.endf	MPU_Hal_EnableEL2

	.section ".bss","awb"
.L173:
	.endo	.L173
	.section ".ghrettbl",""
.L192:	.data.w	.L191
	.endo	.L192
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
__callee.MPU_Hal_DisableEL2.v.v::
	.size	__callee.MPU_Hal_DisableEL2.v.v,0
MPU_Hal_DisableEL2::
.LDW91:
.LDW02:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
dmb

..gh.endasm.31:
	.endo	..gh.endasm.31

;line178
..lin.a2346e4e..78640041.0_14::
.LDWlin14:
..gh.beginasm.32:
	.endo	..gh.beginasm.32
MRC p15, 4, r0, c1, c0, 0

..gh.endasm.33:
	.endo	..gh.endasm.33

;line184
..lin.a2346e4e..78640041.0_15::
.LDWlin15:
	bic	r0,r0,1
..gh.beginasm.34:
	.endo	..gh.beginasm.34
MCR p15, 4, r0, c1, c0, 0

..gh.endasm.35:
	.endo	..gh.endasm.35

;line189
..lin.a2346e4e..78640041.0_16::
.LDWlin16:
..gh.beginasm.36:
	.endo	..gh.beginasm.36
dsb

..gh.endasm.37:
	.endo	..gh.endasm.37

;line193
..lin.a2346e4e..78640041.0_17::
.LDWlin17:
..gh.beginasm.38:
	.endo	..gh.beginasm.38
isb

..gh.endasm.39:
	.endo	..gh.endasm.39

.LDW12:
.L255:

;line194
..lin.a2346e4e..78640041.0_18::
.LDWlin18:
	ret	
__ghs_eofn_MPU_Hal_DisableEL2::
	.endf	MPU_Hal_DisableEL2

	.section ".bss","awb"
.L237:
	.endo	.L237
	.section ".ghrettbl",""
.L256:	.data.w	.L255
	.endo	.L256
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.40:
	.endo	..gh.f.a.1.e.40
__callee.MPU_Hal_EnableEL2Re.v.i::
	.size	__callee.MPU_Hal_EnableEL2Re.v.i,0
MPU_Hal_EnableEL2Re::
.LDW22:
.LDW32:
..gh.beginasm.41:
	.endo	..gh.beginasm.41
MRC p15, 4, r1, c0, c0, 4

..gh.endasm.42:
	.endo	..gh.endasm.42

;line223
..lin.a2346e4e..c92a15ab.0_19::
.LDWlin19:
..gh.beginasm.43:
	.endo	..gh.beginasm.43
MRC p15, 4, r1, c6, c1, 1

..gh.endasm.44:
	.endo	..gh.endasm.44

;line229
..lin.a2346e4e..c92a15ab.0_20::
.LDWlin20:
	mov	r2,1
	orr	r0,r1,r2 lsl r0
..gh.beginasm.45:
	.endo	..gh.beginasm.45
MCR p15, 4, r0, c6, c1, 1

..gh.endasm.46:
	.endo	..gh.endasm.46

;line234
..lin.a2346e4e..c92a15ab.0_21::
.LDWlin21:
..gh.beginasm.47:
	.endo	..gh.beginasm.47
dsb

..gh.endasm.48:
	.endo	..gh.endasm.48

;line238
..lin.a2346e4e..c92a15ab.0_22::
.LDWlin22:
..gh.beginasm.49:
	.endo	..gh.beginasm.49
isb

..gh.endasm.50:
	.endo	..gh.endasm.50

.LDW42:
.L319:

;line239
..lin.a2346e4e..c92a15ab.0_23::
.LDWlin23:
	ret	
__ghs_eofn_MPU_Hal_EnableEL2Re::
	.endf	MPU_Hal_EnableEL2Re

;uRgNum	r0	param

	.section ".bss","awb"
.L301:
	.endo	.L301
	.section ".ghrettbl",""
.L320:	.data.w	.L319
	.endo	.L320
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.51:
	.endo	..gh.f.a.1.e.51
__callee.MPU_Hal_DisableEL2Re.v.i::
	.size	__callee.MPU_Hal_DisableEL2Re.v.i,0
MPU_Hal_DisableEL2Re::
.LDW52:
.LDW62:
..gh.beginasm.52:
	.endo	..gh.beginasm.52
dmb

..gh.endasm.53:
	.endo	..gh.endasm.53

;line257
..lin.a2346e4e..21651f78.0_24::
.LDWlin24:
..gh.beginasm.54:
	.endo	..gh.beginasm.54
MRC p15, 4, r1, c0, c0, 4

..gh.endasm.55:
	.endo	..gh.endasm.55

;line271
..lin.a2346e4e..21651f78.0_25::
.LDWlin25:
..gh.beginasm.56:
	.endo	..gh.beginasm.56
MRC p15, 4, r1, c6, c1, 1

..gh.endasm.57:
	.endo	..gh.endasm.57

;line277
..lin.a2346e4e..21651f78.0_26::
.LDWlin26:
	mov	r2,1
	lsl	r0,r2,r0
	bic	r0,r1,r0
..gh.beginasm.58:
	.endo	..gh.beginasm.58
MCR p15, 4, r0, c6, c1, 1

..gh.endasm.59:
	.endo	..gh.endasm.59

;line281
..lin.a2346e4e..21651f78.0_27::
.LDWlin27:
..gh.beginasm.60:
	.endo	..gh.beginasm.60
dsb

..gh.endasm.61:
	.endo	..gh.endasm.61

;line285
..lin.a2346e4e..21651f78.0_28::
.LDWlin28:
..gh.beginasm.62:
	.endo	..gh.beginasm.62
isb

..gh.endasm.63:
	.endo	..gh.endasm.63

.LDW72:
.L383:

;line286
..lin.a2346e4e..21651f78.0_29::
.LDWlin29:
	ret	
__ghs_eofn_MPU_Hal_DisableEL2Re::
	.endf	MPU_Hal_DisableEL2Re

;uRgNum	r0	param

	.section ".bss","awb"
.L365:
	.endo	.L365
	.section ".ghrettbl",""
.L384:	.data.w	.L383
	.endo	.L384
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.64:
	.endo	..gh.f.a.1.e.64
__callee.MPU_Hal_EnableEL1Bg.v.v::
	.size	__callee.MPU_Hal_EnableEL1Bg.v.v,0
MPU_Hal_EnableEL1Bg::
.LDW82:
.LDW92:
..gh.beginasm.65:
	.endo	..gh.beginasm.65
MRC p15, 0, r0, c1, c0, 0

..gh.endasm.66:
	.endo	..gh.endasm.66

;line305
..lin.a2346e4e..c92a0f5c.0_30::
.LDWlin30:
	orr	r0,r0,1<<17
..gh.beginasm.67:
	.endo	..gh.beginasm.67
MCR p15, 0, r0, c1, c0, 0

..gh.endasm.68:
	.endo	..gh.endasm.68

;line309
..lin.a2346e4e..c92a0f5c.0_31::
.LDWlin31:
..gh.beginasm.69:
	.endo	..gh.beginasm.69
dsb

..gh.endasm.70:
	.endo	..gh.endasm.70

;line313
..lin.a2346e4e..c92a0f5c.0_32::
.LDWlin32:
..gh.beginasm.71:
	.endo	..gh.beginasm.71
isb

..gh.endasm.72:
	.endo	..gh.endasm.72

.LDW03:
.L447:

;line314
..lin.a2346e4e..c92a0f5c.0_33::
.LDWlin33:
	ret	
__ghs_eofn_MPU_Hal_EnableEL1Bg::
	.endf	MPU_Hal_EnableEL1Bg

	.section ".bss","awb"
.L429:
	.endo	.L429
	.section ".ghrettbl",""
.L448:	.data.w	.L447
	.endo	.L448
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.73:
	.endo	..gh.f.a.1.e.73
__callee.MPU_Hal_DisableEL1Bg.v.v::
	.size	__callee.MPU_Hal_DisableEL1Bg.v.v,0
MPU_Hal_DisableEL1Bg::
.LDW13:
.LDW23:
..gh.beginasm.74:
	.endo	..gh.beginasm.74
dmb

..gh.endasm.75:
	.endo	..gh.endasm.75

;line331
..lin.a2346e4e..21651929.0_34::
.LDWlin34:
..gh.beginasm.76:
	.endo	..gh.beginasm.76
MRC p15, 0, r0, c1, c0, 0

..gh.endasm.77:
	.endo	..gh.endasm.77

;line337
..lin.a2346e4e..21651929.0_35::
.LDWlin35:
	bic	r0,r0,1<<17
..gh.beginasm.78:
	.endo	..gh.beginasm.78
MCR p15, 0, r0, c1, c0, 0

..gh.endasm.79:
	.endo	..gh.endasm.79

;line341
..lin.a2346e4e..21651929.0_36::
.LDWlin36:
..gh.beginasm.80:
	.endo	..gh.beginasm.80
dsb

..gh.endasm.81:
	.endo	..gh.endasm.81

;line345
..lin.a2346e4e..21651929.0_37::
.LDWlin37:
..gh.beginasm.82:
	.endo	..gh.beginasm.82
isb

..gh.endasm.83:
	.endo	..gh.endasm.83

.LDW33:
.L511:

;line346
..lin.a2346e4e..21651929.0_38::
.LDWlin38:
	ret	
__ghs_eofn_MPU_Hal_DisableEL1Bg::
	.endf	MPU_Hal_DisableEL1Bg

	.section ".bss","awb"
.L493:
	.endo	.L493
	.section ".ghrettbl",""
.L512:	.data.w	.L511
	.endo	.L512
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.84:
	.endo	..gh.f.a.1.e.84
__callee.MPU_Hal_EnableEL2Bg.v.v::
	.size	__callee.MPU_Hal_EnableEL2Bg.v.v,0
MPU_Hal_EnableEL2Bg::
.LDW43:
.LDW53:
..gh.beginasm.85:
	.endo	..gh.beginasm.85
MRC p15, 4, r0, c1, c0, 0

..gh.endasm.86:
	.endo	..gh.endasm.86

;line365
..lin.a2346e4e..c92a139d.0_39::
.LDWlin39:
	orr	r0,r0,1<<17
..gh.beginasm.87:
	.endo	..gh.beginasm.87
MCR p15, 4, r0, c1, c0, 0

..gh.endasm.88:
	.endo	..gh.endasm.88

;line369
..lin.a2346e4e..c92a139d.0_40::
.LDWlin40:
..gh.beginasm.89:
	.endo	..gh.beginasm.89
dsb

..gh.endasm.90:
	.endo	..gh.endasm.90

;line373
..lin.a2346e4e..c92a139d.0_41::
.LDWlin41:
..gh.beginasm.91:
	.endo	..gh.beginasm.91
isb

..gh.endasm.92:
	.endo	..gh.endasm.92

.LDW63:
.L575:

;line374
..lin.a2346e4e..c92a139d.0_42::
.LDWlin42:
	ret	
__ghs_eofn_MPU_Hal_EnableEL2Bg::
	.endf	MPU_Hal_EnableEL2Bg

	.section ".bss","awb"
.L557:
	.endo	.L557
	.section ".ghrettbl",""
.L576:	.data.w	.L575
	.endo	.L576
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.93:
	.endo	..gh.f.a.1.e.93
__callee.MPU_Hal_DisableEL2Bg.v.v::
	.size	__callee.MPU_Hal_DisableEL2Bg.v.v,0
MPU_Hal_DisableEL2Bg::
.LDW73:
.LDW83:
..gh.beginasm.94:
	.endo	..gh.beginasm.94
dmb

..gh.endasm.95:
	.endo	..gh.endasm.95

;line390
..lin.a2346e4e..21651d6a.0_43::
.LDWlin43:
..gh.beginasm.96:
	.endo	..gh.beginasm.96
MRC p15, 4, r0, c1, c0, 0

..gh.endasm.97:
	.endo	..gh.endasm.97

;line396
..lin.a2346e4e..21651d6a.0_44::
.LDWlin44:
	bic	r0,r0,1<<17
..gh.beginasm.98:
	.endo	..gh.beginasm.98
MCR p15, 4, r0, c1, c0, 0

..gh.endasm.99:
	.endo	..gh.endasm.99

;line400
..lin.a2346e4e..21651d6a.0_45::
.LDWlin45:
..gh.beginasm.100:
	.endo	..gh.beginasm.100
dsb

..gh.endasm.101:
	.endo	..gh.endasm.101

;line404
..lin.a2346e4e..21651d6a.0_46::
.LDWlin46:
..gh.beginasm.102:
	.endo	..gh.beginasm.102
isb

..gh.endasm.103:
	.endo	..gh.endasm.103

.LDW93:
.L639:

;line405
..lin.a2346e4e..21651d6a.0_47::
.LDWlin47:
	ret	
__ghs_eofn_MPU_Hal_DisableEL2Bg::
	.endf	MPU_Hal_DisableEL2Bg

	.section ".bss","awb"
.L621:
	.endo	.L621
	.section ".ghrettbl",""
.L640:	.data.w	.L639
	.endo	.L640
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.104:
	.endo	..gh.f.a.1.e.104
__callee.MPU_Hal_SetEL1Re.v.ip::
	.size	__callee.MPU_Hal_SetEL1Re.v.ip,0
MPU_Hal_SetEL1Re::
.LDW04:
.LDW14:
..gh.beginasm.105:
	.endo	..gh.beginasm.105
MRC p15, 0, r2, c0, c0, 4

..gh.endasm.106:
	.endo	..gh.endasm.106

;line447
..lin.a2346e4e..d79b7c8f.0_48::
.LDWlin48:
..gh.beginasm.107:
	.endo	..gh.beginasm.107
MCR p15, 0, r0, c6, c2, 1

..gh.endasm.108:
	.endo	..gh.endasm.108

;line452
..lin.a2346e4e..d79b7c8f.0_49::
.LDWlin49:
..gh.beginasm.109:
	.endo	..gh.beginasm.109
dsb

..gh.endasm.110:
	.endo	..gh.endasm.110

;line458
..lin.a2346e4e..d79b7c8f.0_50::
.LDWlin50:
	mov	r0,0
..gh.beginasm.111:
	.endo	..gh.beginasm.111
MCR p15, 0, r0, c6, c3, 1

..gh.endasm.112:
	.endo	..gh.endasm.112

;line462
..lin.a2346e4e..d79b7c8f.0_51::
.LDWlin51:
..gh.beginasm.113:
	.endo	..gh.beginasm.113
isb

..gh.endasm.114:
	.endo	..gh.endasm.114

;line465
..lin.a2346e4e..d79b7c8f.0_52::
.LDWlin52:
	ldr	r0,[r1,16]!
	ldmdb	r1!,{r3,r12}
	orr	r0,r0,r12 lsl 1
	orr	r0,r0,r3 lsl 3
	ldmdb	r1,{r2-r3}
	orr	r0,r0,r2
..gh.beginasm.115:
	.endo	..gh.beginasm.115
MCR p15, 0, r0, c6, c3, 0

..gh.endasm.116:
	.endo	..gh.endasm.116

;line476
..lin.a2346e4e..d79b7c8f.0_53::
.LDWlin53:
	ldrh	r0,[r1,12]
	ldrh	r2,[r1,14]
	ldr	r1,[r1,-8]
	orr	r0,r0,r2 lsl 1
	sub	r2,r3,64
	add	r1,r2,r1
	orr	r0,r0,r1
..gh.beginasm.117:
	.endo	..gh.beginasm.117
MCR p15, 0, r0, c6, c3, 1

..gh.endasm.118:
	.endo	..gh.endasm.118

;line489
..lin.a2346e4e..d79b7c8f.0_54::
.LDWlin54:
..gh.beginasm.119:
	.endo	..gh.beginasm.119
dsb

..gh.endasm.120:
	.endo	..gh.endasm.120

;line493
..lin.a2346e4e..d79b7c8f.0_55::
.LDWlin55:
..gh.beginasm.121:
	.endo	..gh.beginasm.121
isb

..gh.endasm.122:
	.endo	..gh.endasm.122

.LDW24:
.L697:

;line494
..lin.a2346e4e..d79b7c8f.0_56::
.LDWlin56:
	ret	
__ghs_eofn_MPU_Hal_SetEL1Re::
	.endf	MPU_Hal_SetEL1Re
;uPRBAR	r0	local
;uPRLAR	r0	local

;bRgNum	r0	param
;pRegionAtt	r1	param

	.section ".bss","awb"
.L679:
	.endo	.L679
	.section ".ghrettbl",""
.L698:	.data.w	.L697
	.endo	.L698
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.123:
	.endo	..gh.f.a.1.e.123
__callee.MPU_Hal_SetEL2Re.v.ip::
	.size	__callee.MPU_Hal_SetEL2Re.v.ip,0
MPU_Hal_SetEL2Re::
.LDW34:
.LDW44:
..gh.beginasm.124:
	.endo	..gh.beginasm.124
MRC p15, 4, r2, c0, c0, 4

..gh.endasm.125:
	.endo	..gh.endasm.125

;line537
..lin.a2346e4e..d79b80d0.0_57::
.LDWlin57:
..gh.beginasm.126:
	.endo	..gh.beginasm.126
MCR p15, 4, r0, c6, c2, 1

..gh.endasm.127:
	.endo	..gh.endasm.127

;line541
..lin.a2346e4e..d79b80d0.0_58::
.LDWlin58:
..gh.beginasm.128:
	.endo	..gh.beginasm.128
dsb

..gh.endasm.129:
	.endo	..gh.endasm.129

;line547
..lin.a2346e4e..d79b80d0.0_59::
.LDWlin59:
	mov	r0,0
..gh.beginasm.130:
	.endo	..gh.beginasm.130
MCR p15, 4, r0, c6, c3, 1

..gh.endasm.131:
	.endo	..gh.endasm.131

;line551
..lin.a2346e4e..d79b80d0.0_60::
.LDWlin60:
..gh.beginasm.132:
	.endo	..gh.beginasm.132
isb

..gh.endasm.133:
	.endo	..gh.endasm.133

;line554
..lin.a2346e4e..d79b80d0.0_61::
.LDWlin61:
	ldr	r0,[r1,16]!
	ldmdb	r1!,{r3,r12}
	orr	r0,r0,r12 lsl 1
	orr	r0,r0,r3 lsl 3
	ldmdb	r1,{r2-r3}
	orr	r0,r0,r2
..gh.beginasm.134:
	.endo	..gh.beginasm.134
MCR p15, 4, r0, c6, c3, 0

..gh.endasm.135:
	.endo	..gh.endasm.135

;line565
..lin.a2346e4e..d79b80d0.0_62::
.LDWlin62:
	ldrh	r0,[r1,12]
	ldrh	r2,[r1,14]
	ldr	r1,[r1,-8]
	orr	r0,r0,r2 lsl 1
	sub	r2,r3,64
	add	r1,r2,r1
	orr	r0,r0,r1
..gh.beginasm.136:
	.endo	..gh.beginasm.136
MCR p15, 4, r0, c6, c3, 1

..gh.endasm.137:
	.endo	..gh.endasm.137

;line578
..lin.a2346e4e..d79b80d0.0_63::
.LDWlin63:
..gh.beginasm.138:
	.endo	..gh.beginasm.138
dsb

..gh.endasm.139:
	.endo	..gh.endasm.139

;line582
..lin.a2346e4e..d79b80d0.0_64::
.LDWlin64:
..gh.beginasm.140:
	.endo	..gh.beginasm.140
isb

..gh.endasm.141:
	.endo	..gh.endasm.141

.LDW54:
.L748:

;line583
..lin.a2346e4e..d79b80d0.0_65::
.LDWlin65:
	ret	
__ghs_eofn_MPU_Hal_SetEL2Re::
	.endf	MPU_Hal_SetEL2Re
;uHPRBAR	r0	local
;uHPRLAR	r0	local

;bRgNum	r0	param
;pRegionAtt	r1	param

	.section ".bss","awb"
.L730:
	.endo	.L730
	.section ".ghrettbl",""
.L749:	.data.w	.L748
	.endo	.L749
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.142:
	.endo	..gh.f.a.1.e.142
__callee.MPU_Hal_SetMemAttri.v.ii::
	.size	__callee.MPU_Hal_SetMemAttri.v.ii,0
MPU_Hal_SetMemAttri::
.LDW64:
.LDW74:
	cmp	r0,4
	lsl	r0,r0,3
	mov	r3,255
	bhs	.L752
	uxtb	r0,r0
..gh.beginasm.143:
	.endo	..gh.beginasm.143
MRC p15, 0, r2, c10, c2, 0

..gh.endasm.144:
	.endo	..gh.endasm.144

;line610
..lin.a2346e4e..2b531779.0_66::
.LDWlin66:
	lsl	r3,r3,r0
	bic	r2,r2,r3
	and	r0,r3,r1 lsl r0
	orr	r0,r2,r0
..gh.beginasm.145:
	.endo	..gh.beginasm.145
MCR p15, 0, r0, c10, c2, 0

..gh.endasm.146:
	.endo	..gh.endasm.146

.L847:

	ret	
.L752:
;line621
..lin.a2346e4e..2b531779.0_67::
.LDWlin67:
	add	r0,r0,224
	uxtb	r0,r0
..gh.beginasm.147:
	.endo	..gh.beginasm.147
MRC p15, 0, r2, c10, c2, 1

..gh.endasm.148:
	.endo	..gh.endasm.148

;line627
..lin.a2346e4e..2b531779.0_68::
.LDWlin68:
	lsl	r3,r3,r0
	bic	r2,r2,r3
	and	r0,r3,r1 lsl r0
	orr	r0,r2,r0
..gh.beginasm.149:
	.endo	..gh.beginasm.149
MCR p15, 0, r0, c10, c2, 1

..gh.endasm.150:
	.endo	..gh.endasm.150

.LDW84:
.L849:

;line637
..lin.a2346e4e..2b531779.0_69::
.LDWlin69:
	ret	
__ghs_eofn_MPU_Hal_SetMemAttri::
	.endf	MPU_Hal_SetMemAttri
;uMAIR	r2	local
;uMemAtt	r3	local
;memAttShift	r0	local

;bAttIndex	r0	param
;bMemAtt	r1	param

	.section ".bss","awb"
.L805:
	.endo	.L805
	.section ".ghrettbl",""
.L848:	.data.w	.L847
	.endo	.L848
.L850:	.data.w	.L849
	.endo	.L850
	.section ".sdk_text_asil_d","ax"

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cmpu_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682577..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	21,6,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,115,114,99,47,109,112,117,95,104,97,108,46,99,0
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
	.data.b	132,5,0,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,115,114,99,47,109,112,117,95,104,97,108,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,109,112,117,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,67,111,114,101,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,109,112,117,95,114,101,103,105,115,116,101,114,46,104,0
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
	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 19
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 37
	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 197
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 39
	.data.w	.Ldw_str_begin+197
	.data.b	7
	.data.b	4

	.section	.debug_abbrev		;off: 26
	.data.b	42
	.data.b	36
	.data.b	0
	.data.b	3,14
	.data.b	62,11
	.data.b	11,11
	.data.b	0,0

	.section	.debug_info		;off: 45
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

	.data.b	23
	.data.w	.Ldw_begin+182
	.data.b	0

	.section	.debug_abbrev		;off: 37
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 62
	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+182
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
	.section	.debug_str		;off: 211
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 85
	.data.w	.Ldw_str_begin+211
	.data.b	8
	.data.b	1

	.data.b	47
	.data.w	.Ldw_begin+472

	.section	.debug_abbrev		;off: 46
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 96
	.data.b	53
	.data.w	.Ldw_begin+91

	.section	.debug_abbrev		;off: 53
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 101
	.data.b	47
	.data.w	.Ldw_begin+96

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+158
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+101
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+158
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+101
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+158
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+158
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 225
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 152
	.data.w	.Ldw_str_begin+225
	.data.b	7
	.data.b	2

	.data.b	45
	.section	.debug_str		;off: 240
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 159
	.data.w	.Ldw_str_begin+240
	.data.b	56
	.data.b	29
	.data.b	6
	.data.w	.Ldw_begin+84

	.section	.debug_abbrev		;off: 60
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 170
	.data.b	45
	.section	.debug_str		;off: 246
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 171
	.data.w	.Ldw_str_begin+246
	.data.b	60
	.data.b	29
	.data.b	6
	.data.w	.Ldw_begin+151

	.data.b	45
	.section	.debug_str		;off: 253
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 183
	.data.w	.Ldw_str_begin+253
	.data.b	64
	.data.b	29
	.data.b	6
	.data.w	.Ldw_begin+38

	.data.b	52
	.section	.debug_str		;off: 260
	.data.b	0
	.section	.debug_info		;off: 195
	.data.w	.Ldw_str_begin+260
	.data.b	43
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 75
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

	.section	.debug_info		;off: 204
	.data.b	51
	.section	.debug_str		;off: 261
	.data.b	77,80,85,95,78,79,78,69,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 205
	.data.w	.Ldw_str_begin+261
	.data.b	44
	.data.b	5
	.data.b	5
	.data.b	0

	.section	.debug_abbrev		;off: 92
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 213
	.data.b	51
	.section	.debug_str		;off: 280
	.data.b	77,80,85,95,85,78,80,82,69,68,73,67,84,65,66,76,69,0
	.section	.debug_info		;off: 214
	.data.w	.Ldw_str_begin+280
	.data.b	45
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 298
	.data.b	77,80,85,95,79,85,84,69,82,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 223
	.data.w	.Ldw_str_begin+298
	.data.b	46
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 318
	.data.b	77,80,85,95,73,78,78,69,82,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 232
	.data.w	.Ldw_str_begin+318
	.data.b	47
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 338
	.data.b	77,80,85,95,83,104,97,114,101,97,98,105,108,105,116,121,70,105,101,108,100,0
	.section	.debug_info		;off: 242
	.data.w	.Ldw_str_begin+338
	.data.b	48
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+194

	.data.b	52
	.section	.debug_str		;off: 360
	.data.b	0
	.section	.debug_info		;off: 254
	.data.w	.Ldw_str_begin+360
	.data.b	52
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 361
	.data.b	77,80,85,95,69,76,49,82,87,95,69,76,48,78,79,78,69,0
	.section	.debug_info		;off: 264
	.data.w	.Ldw_str_begin+361
	.data.b	53
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 379
	.data.b	77,80,85,95,69,76,49,82,87,95,69,76,48,82,87,0
	.section	.debug_info		;off: 273
	.data.w	.Ldw_str_begin+379
	.data.b	57
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 395
	.data.b	77,80,85,95,69,76,49,82,79,95,69,76,48,78,79,78,69,0
	.section	.debug_info		;off: 282
	.data.w	.Ldw_str_begin+395
	.data.b	61
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 413
	.data.b	77,80,85,95,69,76,49,82,79,95,69,76,48,82,79,0
	.section	.debug_info		;off: 291
	.data.w	.Ldw_str_begin+413
	.data.b	65
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 429
	.data.b	77,80,85,95,69,76,65,99,99,101,115,115,80,101,114,109,105,115,115,105,111,110,0
	.section	.debug_info		;off: 301
	.data.w	.Ldw_str_begin+429
	.data.b	67
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+253

	.data.b	52
	.section	.debug_str		;off: 452
	.data.b	0
	.section	.debug_info		;off: 313
	.data.w	.Ldw_str_begin+452
	.data.b	71
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 453
	.data.b	77,80,85,95,69,88,69,67,85,84,69,95,80,69,82,77,73,84,84,69,68,0
	.section	.debug_info		;off: 323
	.data.w	.Ldw_str_begin+453
	.data.b	72
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 475
	.data.b	77,80,85,95,69,88,69,67,85,84,69,95,78,69,86,69,82,0
	.section	.debug_info		;off: 332
	.data.w	.Ldw_str_begin+475
	.data.b	73
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 493
	.data.b	77,80,85,95,69,78,0
	.section	.debug_info		;off: 342
	.data.w	.Ldw_str_begin+493
	.data.b	74
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+312

	.data.b	71
	.data.b	84
	.data.b	1
	.data.b	5
	.data.b	24
	.data.b	1

	.section	.debug_abbrev		;off: 107
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 359
	.data.b	40
	.section	.debug_str		;off: 500
	.data.b	77,80,85,95,83,116,97,114,116,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 360
	.data.w	.Ldw_str_begin+500
	.data.b	85
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+182
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 122
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

	.section	.debug_info		;off: 375
	.data.b	40
	.section	.debug_str		;off: 517
	.data.b	77,80,85,95,82,101,103,105,111,110,83,105,122,101,0
	.section	.debug_info		;off: 376
	.data.w	.Ldw_str_begin+517
	.data.b	86
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+182
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 532
	.data.b	77,80,85,95,83,104,97,114,101,70,105,101,108,100,0
	.section	.debug_info		;off: 392
	.data.w	.Ldw_str_begin+532
	.data.b	87
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+241
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 547
	.data.b	77,80,85,95,65,99,99,80,101,114,109,0
	.section	.debug_info		;off: 408
	.data.w	.Ldw_str_begin+547
	.data.b	88
	.data.b	28
	.data.b	5
	.data.w	.Ldw_begin+300
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 559
	.data.b	77,80,85,95,88,78,0
	.section	.debug_info		;off: 424
	.data.w	.Ldw_str_begin+559
	.data.b	89
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+341
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 566
	.data.b	77,80,85,95,82,101,103,105,111,110,69,110,97,98,108,101,0
	.section	.debug_info		;off: 440
	.data.w	.Ldw_str_begin+566
	.data.b	90
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+170
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 583
	.data.b	77,80,85,95,65,116,116,73,110,100,101,120,0
	.section	.debug_info		;off: 456
	.data.w	.Ldw_str_begin+583
	.data.b	91
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+170
	.data.b	2,35
	.data.b	22
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 596
	.data.b	77,80,85,95,82,101,103,105,111,110,65,116,116,0
	.section	.debug_info		;off: 473
	.data.w	.Ldw_str_begin+596
	.data.b	92
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+353

	.data.b	24
	.section	.debug_str		;off: 610
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,49,0
	.section	.debug_info		;off: 485
	.data.w	.Ldw_str_begin+610
	.data.b	72
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_EnableEL1
	.data.w	__ghs_eofn_MPU_Hal_EnableEL1
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

	.section	.debug_abbrev		;off: 141
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
	.data.w	MPU_Hal_EnableEL1
	.data.w	__ghs_eofn_MPU_Hal_EnableEL1-MPU_Hal_EnableEL1
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 352
	.data.b	0,5,2
	.data.w	MPU_Hal_EnableEL1
	.data.b	6
	.data.b	3
	.data.b	207,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	3
	.data.b	5
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
	.section	.debug_info		;off: 513
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 187
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 522
	.data.b	8
	.section	.debug_str		;off: 628
	.data.b	117,83,67,84,76,82,0
	.section	.debug_info		;off: 523
	.data.w	.Ldw_str_begin+628
	.data.b	74
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 196
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

	.section	.debug_info		;off: 536
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 635
	.data.b	77,80,85,95,72,97,108,95,68,105,115,97,98,108,101,69,76,49,0
	.section	.debug_info		;off: 539
	.data.w	.Ldw_str_begin+635
	.data.b	101
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_DisableEL1
	.data.w	__ghs_eofn_MPU_Hal_DisableEL1
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	MPU_Hal_DisableEL1
	.data.w	__ghs_eofn_MPU_Hal_DisableEL1-MPU_Hal_DisableEL1
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 415
	.data.b	0,5,2
	.data.w	MPU_Hal_DisableEL1
	.data.b	6
	.data.b	3
	.data.b	236,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 567
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	8
	.section	.debug_str		;off: 654
	.data.b	117,83,67,84,76,82,0
	.section	.debug_info		;off: 577
	.data.w	.Ldw_str_begin+654
	.data.b	103
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 661
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,50,0
	.section	.debug_info		;off: 593
	.data.w	.Ldw_str_begin+661
	.data.b	135,1
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_EnableEL2
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2
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
	.data.w	MPU_Hal_EnableEL2
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2-MPU_Hal_EnableEL2
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 490
	.data.b	0,5,2
	.data.w	MPU_Hal_EnableEL2
	.data.b	6
	.data.b	3
	.data.b	142,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	3
	.data.b	5
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
	.section	.debug_info		;off: 622
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	8
	.section	.debug_str		;off: 679
	.data.b	117,72,83,67,84,76,82,0
	.section	.debug_info		;off: 632
	.data.w	.Ldw_str_begin+679
	.data.b	137,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 687
	.data.b	77,80,85,95,72,97,108,95,68,105,115,97,98,108,101,69,76,50,0
	.section	.debug_info		;off: 649
	.data.w	.Ldw_str_begin+687
	.data.b	164,1
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_DisableEL2
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2
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
	.data.w	MPU_Hal_DisableEL2
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2-MPU_Hal_DisableEL2
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 553
	.data.b	0,5,2
	.data.w	MPU_Hal_DisableEL2
	.data.b	6
	.data.b	3
	.data.b	171,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 678
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	8
	.section	.debug_str		;off: 706
	.data.b	117,72,83,67,84,76,82,0
	.section	.debug_info		;off: 688
	.data.w	.Ldw_str_begin+706
	.data.b	166,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 714
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,50,82,101,0
	.section	.debug_info		;off: 705
	.data.w	.Ldw_str_begin+714
	.data.b	199,1
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_EnableEL2Re
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2Re
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
	.data.w	MPU_Hal_EnableEL2Re
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2Re-MPU_Hal_EnableEL2Re
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 628
	.data.b	0,5,2
	.data.w	MPU_Hal_EnableEL2Re
	.data.b	6
	.data.b	3
	.data.b	208,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 734
	.data.b	22
	.section	.debug_str		;off: 734
	.data.b	117,82,103,78,117,109,0
	.section	.debug_info		;off: 735
	.data.w	.Ldw_str_begin+734
	.data.b	199,1
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 215
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

	.section	.debug_info		;off: 752
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	8
	.section	.debug_str		;off: 741
	.data.b	117,72,80,82,69,78,82,0
	.section	.debug_info		;off: 762
	.data.w	.Ldw_str_begin+741
	.data.b	201,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 749
	.data.b	117,72,77,80,85,73,82,0
	.section	.debug_info		;off: 777
	.data.w	.Ldw_str_begin+749
	.data.b	202,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 757
	.data.b	77,80,85,95,72,97,108,95,68,105,115,97,98,108,101,69,76,50,82,101,0
	.section	.debug_info		;off: 794
	.data.w	.Ldw_str_begin+757
	.data.b	244,1
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_DisableEL2Re
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2Re
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
	.data.w	MPU_Hal_DisableEL2Re
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2Re-MPU_Hal_DisableEL2Re
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 703
	.data.b	0,5,2
	.data.w	MPU_Hal_DisableEL2Re
	.data.b	6
	.data.b	3
	.data.b	251,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 823
	.data.b	22
	.section	.debug_str		;off: 778
	.data.b	117,82,103,78,117,109,0
	.section	.debug_info		;off: 824
	.data.w	.Ldw_str_begin+778
	.data.b	244,1
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 841
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	8
	.section	.debug_str		;off: 785
	.data.b	117,72,80,82,69,78,82,0
	.section	.debug_info		;off: 851
	.data.w	.Ldw_str_begin+785
	.data.b	246,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 793
	.data.b	117,72,77,80,85,73,82,0
	.section	.debug_info		;off: 866
	.data.w	.Ldw_str_begin+793
	.data.b	247,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 801
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,49,66,103,0
	.section	.debug_info		;off: 883
	.data.w	.Ldw_str_begin+801
	.data.b	163,2
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_EnableEL1Bg
	.data.w	__ghs_eofn_MPU_Hal_EnableEL1Bg
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
	.data.w	MPU_Hal_EnableEL1Bg
	.data.w	__ghs_eofn_MPU_Hal_EnableEL1Bg-MPU_Hal_EnableEL1Bg
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 790
	.data.b	0,5,2
	.data.w	MPU_Hal_EnableEL1Bg
	.data.b	6
	.data.b	3
	.data.b	170,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin33
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 912
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	8
	.section	.debug_str		;off: 821
	.data.b	117,83,67,84,76,82,0
	.section	.debug_info		;off: 922
	.data.w	.Ldw_str_begin+821
	.data.b	165,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 828
	.data.b	77,80,85,95,72,97,108,95,68,105,115,97,98,108,101,69,76,49,66,103,0
	.section	.debug_info		;off: 939
	.data.w	.Ldw_str_begin+828
	.data.b	191,2
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_DisableEL1Bg
	.data.w	__ghs_eofn_MPU_Hal_DisableEL1Bg
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
	.data.w	MPU_Hal_DisableEL1Bg
	.data.w	__ghs_eofn_MPU_Hal_DisableEL1Bg-MPU_Hal_DisableEL1Bg
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 853
	.data.b	0,5,2
	.data.w	MPU_Hal_DisableEL1Bg
	.data.b	6
	.data.b	3
	.data.b	197,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin36
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin37
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin38
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 968
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	8
	.section	.debug_str		;off: 849
	.data.b	117,83,67,84,76,82,0
	.section	.debug_info		;off: 978
	.data.w	.Ldw_str_begin+849
	.data.b	193,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 856
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,50,66,103,0
	.section	.debug_info		;off: 995
	.data.w	.Ldw_str_begin+856
	.data.b	223,2
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_EnableEL2Bg
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2Bg
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	MPU_Hal_EnableEL2Bg
	.data.w	__ghs_eofn_MPU_Hal_EnableEL2Bg-MPU_Hal_EnableEL2Bg
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 928
	.data.b	0,5,2
	.data.w	MPU_Hal_EnableEL2Bg
	.data.b	6
	.data.b	3
	.data.b	230,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin39
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin40
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin41
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin42
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1024
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	8
	.section	.debug_str		;off: 876
	.data.b	117,72,83,67,84,76,82,0
	.section	.debug_info		;off: 1034
	.data.w	.Ldw_str_begin+876
	.data.b	225,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 884
	.data.b	77,80,85,95,72,97,108,95,68,105,115,97,98,108,101,69,76,50,66,103,0
	.section	.debug_info		;off: 1051
	.data.w	.Ldw_str_begin+884
	.data.b	251,2
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_DisableEL2Bg
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2Bg
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	MPU_Hal_DisableEL2Bg
	.data.w	__ghs_eofn_MPU_Hal_DisableEL2Bg-MPU_Hal_DisableEL2Bg
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 991
	.data.b	0,5,2
	.data.w	MPU_Hal_DisableEL2Bg
	.data.b	6
	.data.b	3
	.data.b	128,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin44
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin45
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin46
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin47
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1080
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	8
	.section	.debug_str		;off: 905
	.data.b	117,72,83,67,84,76,82,0
	.section	.debug_info		;off: 1090
	.data.w	.Ldw_str_begin+905
	.data.b	253,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 913
	.data.b	77,80,85,95,72,97,108,95,83,101,116,69,76,49,82,101,0
	.section	.debug_info		;off: 1107
	.data.w	.Ldw_str_begin+913
	.data.b	153,3
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_SetEL1Re
	.data.w	__ghs_eofn_MPU_Hal_SetEL1Re
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
	.data.w	MPU_Hal_SetEL1Re
	.data.w	__ghs_eofn_MPU_Hal_SetEL1Re-MPU_Hal_SetEL1Re
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1066
	.data.b	0,5,2
	.data.w	MPU_Hal_SetEL1Re
	.data.b	6
	.data.b	3
	.data.b	174,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin48
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin49
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin50
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin51
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin52
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin53
	.data.b	13
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin54
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin55
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin56
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1136
	.data.b	22
	.section	.debug_str		;off: 930
	.data.b	98,82,103,78,117,109,0
	.section	.debug_info		;off: 1137
	.data.w	.Ldw_str_begin+930
	.data.b	153,3
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+158
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1154
	.data.b	22
	.section	.debug_str		;off: 937
	.data.b	112,82,101,103,105,111,110,65,116,116,0
	.section	.debug_info		;off: 1155
	.data.w	.Ldw_str_begin+937
	.data.b	153,3
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+101
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1172
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	8
	.section	.debug_str		;off: 948
	.data.b	117,77,80,85,73,82,0
	.section	.debug_info		;off: 1182
	.data.w	.Ldw_str_begin+948
	.data.b	155,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 955
	.data.b	117,80,82,83,69,76,82,0
	.section	.debug_info		;off: 1197
	.data.w	.Ldw_str_begin+955
	.data.b	156,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 963
	.data.b	117,80,82,66,65,82,0
	.section	.debug_info		;off: 1212
	.data.w	.Ldw_str_begin+963
	.data.b	157,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 234
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

	.section	.debug_info		;off: 1230
	.data.b	7
	.section	.debug_str		;off: 970
	.data.b	117,80,82,76,65,82,0
	.section	.debug_info		;off: 1231
	.data.w	.Ldw_str_begin+970
	.data.b	158,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1249
	.data.b	8
	.section	.debug_str		;off: 977
	.data.b	117,82,101,103,83,105,122,101,0
	.section	.debug_info		;off: 1250
	.data.w	.Ldw_str_begin+977
	.data.b	159,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 986
	.data.b	77,80,85,95,72,97,108,95,83,101,116,69,76,50,82,101,0
	.section	.debug_info		;off: 1267
	.data.w	.Ldw_str_begin+986
	.data.b	243,3
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_SetEL2Re
	.data.w	__ghs_eofn_MPU_Hal_SetEL2Re
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
	.data.w	MPU_Hal_SetEL2Re
	.data.w	__ghs_eofn_MPU_Hal_SetEL2Re-MPU_Hal_SetEL2Re
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1200
	.data.b	0,5,2
	.data.w	MPU_Hal_SetEL2Re
	.data.b	6
	.data.b	3
	.data.b	136,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin57
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin58
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin59
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin61
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin62
	.data.b	13
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin63
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin64
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin65
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1296
	.data.b	22
	.section	.debug_str		;off: 1003
	.data.b	98,82,103,78,117,109,0
	.section	.debug_info		;off: 1297
	.data.w	.Ldw_str_begin+1003
	.data.b	243,3
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+158
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1314
	.data.b	22
	.section	.debug_str		;off: 1010
	.data.b	112,82,101,103,105,111,110,65,116,116,0
	.section	.debug_info		;off: 1315
	.data.w	.Ldw_str_begin+1010
	.data.b	243,3
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+101
	.data.b	0
	.data.w	.Ldw_loc_begin+133
	.section	.debug_loc		;off: 133
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1332
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	8
	.section	.debug_str		;off: 1021
	.data.b	117,72,77,80,85,73,82,0
	.section	.debug_info		;off: 1342
	.data.w	.Ldw_str_begin+1021
	.data.b	245,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1029
	.data.b	117,72,80,82,83,69,76,82,0
	.section	.debug_info		;off: 1357
	.data.w	.Ldw_str_begin+1029
	.data.b	246,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1038
	.data.b	117,72,80,82,66,65,82,0
	.section	.debug_info		;off: 1372
	.data.w	.Ldw_str_begin+1038
	.data.b	247,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+152
	.section	.debug_loc		;off: 152
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1390
	.data.b	7
	.section	.debug_str		;off: 1046
	.data.b	117,72,80,82,76,65,82,0
	.section	.debug_info		;off: 1391
	.data.w	.Ldw_str_begin+1046
	.data.b	248,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+171
	.section	.debug_loc		;off: 171
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1409
	.data.b	8
	.section	.debug_str		;off: 1054
	.data.b	117,82,101,103,83,105,122,101,0
	.section	.debug_info		;off: 1410
	.data.w	.Ldw_str_begin+1054
	.data.b	249,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1063
	.data.b	77,80,85,95,72,97,108,95,83,101,116,77,101,109,65,116,116,114,105,0
	.section	.debug_info		;off: 1427
	.data.w	.Ldw_str_begin+1063
	.data.b	204,4
	.data.b	6
	.data.b	1
	.data.w	MPU_Hal_SetMemAttri
	.data.w	__ghs_eofn_MPU_Hal_SetMemAttri
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
	.data.w	MPU_Hal_SetMemAttri
	.data.w	__ghs_eofn_MPU_Hal_SetMemAttri-MPU_Hal_SetMemAttri
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1334
	.data.b	0,5,2
	.data.w	MPU_Hal_SetMemAttri
	.data.b	6
	.data.b	3
	.data.b	217,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin66
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin67
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin68
	.data.b	11
	.data.b	27
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin69
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1456
	.data.b	22
	.section	.debug_str		;off: 1083
	.data.b	98,65,116,116,73,110,100,101,120,0
	.section	.debug_info		;off: 1457
	.data.w	.Ldw_str_begin+1083
	.data.b	204,4
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+158
	.data.b	0
	.data.w	.Ldw_loc_begin+190
	.section	.debug_loc		;off: 190
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1474
	.data.b	22
	.section	.debug_str		;off: 1093
	.data.b	98,77,101,109,65,116,116,0
	.section	.debug_info		;off: 1475
	.data.w	.Ldw_str_begin+1093
	.data.b	204,4
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+158
	.data.b	0
	.data.w	.Ldw_loc_begin+209
	.section	.debug_loc		;off: 209
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1492
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 1101
	.data.b	117,77,65,73,82,0
	.section	.debug_info		;off: 1502
	.data.w	.Ldw_str_begin+1101
	.data.b	206,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+228
	.section	.debug_loc		;off: 228
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1520
	.data.b	7
	.section	.debug_str		;off: 1107
	.data.b	117,77,101,109,65,116,116,0
	.section	.debug_info		;off: 1521
	.data.w	.Ldw_str_begin+1107
	.data.b	207,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+247
	.section	.debug_loc		;off: 247
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1539
	.data.b	7
	.section	.debug_str		;off: 1115
	.data.b	109,101,109,65,116,116,83,104,105,102,116,0
	.section	.debug_info		;off: 1540
	.data.w	.Ldw_str_begin+1115
	.data.b	208,4
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+158
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+266
	.section	.debug_loc		;off: 266
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1558
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
	.data.b	45
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
	.data.b	32
	.data.b	83,84,68,95,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	36
	.data.b	83,84,68,95,79,70,70,32,40,48,85,41,0
	.data.b	1
	.data.b	45
	.data.b	73,78,80,85,84,95,65,82,71,95,68,69,84,69,67,84,32,83,84,68,95,79,70,70,0
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
	.data.b	79
	.data.b	68,77,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,100,109,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	1
	.data.b	80
	.data.b	68,83,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,100,115,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	1
	.data.b	81
	.data.b	73,83,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,105,115,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	4
	.data.b	3
	.data.b	50
	.data.b	5
	.data.b	3
	.data.b	23
	.data.b	6
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	77,65,88,95,71,82,79,85,80,95,77,69,77,95,65,84,84,95,73,78,68,69,88,32,52,85,0
	.data.b	1
	.data.b	31
	.data.b	76,73,77,73,84,95,65,68,68,82,69,83,83,95,65,76,73,71,78,95,83,73,90,69,32,54,52,85,0
	.data.b	1
	.data.b	101
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	102
	.data.b	7
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
	.data.b	176,2
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,2
	.data.b	7
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	51
	.data.b	8
	.data.b	1
	.data.b	21
	.data.b	83,67,84,76,82,95,77,95,77,80,85,95,80,79,83,32,48,85,0
	.data.b	1
	.data.b	22
	.data.b	83,67,84,76,82,95,77,95,77,80,85,95,77,65,83,75,32,40,49,85,76,32,60,60,32,83,67,84,76,82,95,77,95,77,80,85,95,80,79,83,41,0
	.data.b	1
	.data.b	24
	.data.b	83,67,84,76,82,95,66,82,95,77,80,85,95,80,79,83,32,49,55,85,0
	.data.b	1
	.data.b	25
	.data.b	83,67,84,76,82,95,66,82,95,77,80,85,95,77,65,83,75,32,40,49,85,76,32,60,60,32,83,67,84,76,82,95,66,82,95,77,80,85,95,80,79,83,41,0
	.data.b	1
	.data.b	28
	.data.b	72,83,67,84,76,82,95,77,95,77,80,85,95,80,79,83,32,48,85,0
	.data.b	1
	.data.b	29
	.data.b	72,83,67,84,76,82,95,77,95,77,80,85,95,77,65,83,75,32,40,49,85,76,32,60,60,32,72,83,67,84,76,82,95,77,95,77,80,85,95,80,79,83,41,0
	.data.b	1
	.data.b	31
	.data.b	72,83,67,84,76,82,95,66,82,95,77,80,85,95,80,79,83,32,49,55,85,0
	.data.b	1
	.data.b	32
	.data.b	72,83,67,84,76,82,95,66,82,95,77,80,85,95,77,65,83,75,32,40,49,85,76,32,60,60,32,72,83,67,84,76,82,95,66,82,95,77,80,85,95,80,79,83,41,0
	.data.b	4
	.data.b	1
	.data.b	65
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	67
	.data.b	7
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
	.data.b	255,4
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	129,5
	.data.b	7
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 255
	.data.b	0
