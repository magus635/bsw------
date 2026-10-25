	.section ".sdk_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstm_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257B..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
__callee.Stm_Hal_Start.i.v::
	.size	__callee.Stm_Hal_Start.i.v,0
Stm_Hal_Start::
.LDW01:
	push	{r4,lr}
.LDW11:
.L113:

	bl	Cpuwdt_Hal_ClearEndinit
	ldr	r1,.L112
	and	r4,r0,1
	ldr	r0,[r1]
	orr	r0,r0,1
	str	r0,[r1]
.L115:

	bl	Cpuwdt_Hal_SetEndinit
	ldr	r3,.L112
	ldr	r1,[r3]
	and	r1,r1,1
	cmp	r1,1
	movne	r0,0
	andeq	r0,r4,r0
.LDW21:
.L117:

	pop	{r4,pc}
__ghs_eofn_Stm_Hal_Start::
	.endf	Stm_Hal_Start
;ret	r4	local
;ret	r0	local

	.section ".bss","awb"
.L76:
	.endo	.L76
	.section ".ghcalltbl",""
	.align	4
.L114:	.data.w	.L113
	.endo	.L114
.L116:	.data.w	.L115
	.endo	.L116
	.section ".ghrettbl",""
	.align	4
.L118:	.data.w	.L117
	.endo	.L118
	.data
	.global	__caller.Cpuwdt_Hal_SetEndinit.i.v

	.global	__caller.Cpuwdt_Hal_ClearEndinit.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
__callee.Stm_Hal_Stop.i.v::
	.size	__callee.Stm_Hal_Stop.i.v,0
Stm_Hal_Stop::
.LDW31:
	push	{r4,lr}
.LDW41:
.L208:

	bl	Cpuwdt_Hal_ClearEndinit
	ldr	r1,.L112
	and	r4,r0,1
	ldr	r0,[r1]
	bfc	r0,0,1
	str	r0,[r1]
.L210:

	bl	Cpuwdt_Hal_SetEndinit
	ldr	r3,.L112
	ldr	r1,[r3]
	tst	r1,1
	movne	r0,0
	andeq	r0,r4,r0
.LDW51:
.L212:

	pop	{r4,pc}
__ghs_eofn_Stm_Hal_Stop::
	.endf	Stm_Hal_Stop
;ret	r4	local
;ret	r0	local

	.section ".bss","awb"
.L172:
	.endo	.L172
	.section ".ghcalltbl",""
.L209:	.data.w	.L208
	.endo	.L209
.L211:	.data.w	.L210
	.endo	.L211
	.section ".ghrettbl",""
.L213:	.data.w	.L212
	.endo	.L213
	.data
	.global	__caller.Cpuwdt_Hal_SetEndinit.i.v

	.global	__caller.Cpuwdt_Hal_ClearEndinit.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
__callee.Stm_Hal_SetValue.i.l::
	.size	__callee.Stm_Hal_SetValue.i.l,0
Stm_Hal_SetValue::
.LDW61:
	push	{r4-r6,lr}
	mov	r4,r0
	mov	r5,r1
.LDW71:
.L276:

	bl	Cpuwdt_Hal_ClearEndinit
	ldr	r1,.L274
	str	r4,[r1]
	and	r6,r0,1
	str	r5,[r1,4]
.L278:

	bl	Cpuwdt_Hal_SetEndinit
	and	r0,r6,r0
	b	.L275

.L112:	.data.w	0xc0060800
	.endo	.L112

.L274:	.data.w	0xc0060808
	.endo	.L274

.L275:

;line126
..lin.78d5b950..a62b5a15.0_1::
.LDWlin1:
..gh.beginasm.3:
	.endo	..gh.beginasm.3
dsb

..gh.endasm.4:
	.endo	..gh.endasm.4

;line128
..lin.78d5b950..a62b5a15.0_2::
.LDWlin2:
..gh.beginasm.5:
	.endo	..gh.beginasm.5
isb

..gh.endasm.6:
	.endo	..gh.endasm.6

.LDW81:
.L280:

;line130
..lin.78d5b950..a62b5a15.0_3::
.LDWlin3:
	pop	{r4-r6,pc}
__ghs_eofn_Stm_Hal_SetValue::
	.endf	Stm_Hal_SetValue
;ret	r6	local

;value	r4	param

	.section ".bss","awb"
.L250:
	.endo	.L250
	.section ".ghcalltbl",""
.L277:	.data.w	.L276
	.endo	.L277
.L279:	.data.w	.L278
	.endo	.L279
	.section ".ghrettbl",""
.L281:	.data.w	.L280
	.endo	.L281
	.data
	.global	__caller.Cpuwdt_Hal_SetEndinit.i.v

	.global	__caller.Cpuwdt_Hal_ClearEndinit.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
__callee.Stm_Hal_InitPhyEL1Timer.v.p::
	.size	__callee.Stm_Hal_InitPhyEL1Timer.v.p,0
Stm_Hal_InitPhyEL1Timer::
.LDW91:
	push	{r4,lr}
	mov	r4,r0
.LDW02:
	ldrb	r0,[r0]
.L331:

	bl	Stm_Std_SetPhyEL1TimerInterrupt
	ldr	r0,[r4,4]
	pop	{r4,lr}
.L333:

	b	Stm_Std_SetPhyEL1TimerEvent
.LDW12:
__ghs_eofn_Stm_Hal_InitPhyEL1Timer::
	.endf	Stm_Hal_InitPhyEL1Timer

;pTimerConfig	r4	param

	.section ".bss","awb"
.L311:
	.endo	.L311
	.section ".ghcalltbl",""
.L332:	.data.w	.L331
	.endo	.L332
	.section ".ghtailcalltbl",""
	.align	4
.L334:	.data.w	.L333
	.endo	.L334
	.data
	.global	__caller.Stm_Std_SetPhyEL1TimerEvent.v.p

	.global	__caller.Stm_Std_SetPhyEL1TimerInterrupt.v.i

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
__callee.Stm_Hal_InitPhyEL2Timer.v.p::
	.size	__callee.Stm_Hal_InitPhyEL2Timer.v.p,0
Stm_Hal_InitPhyEL2Timer::
.LDW22:
	push	{r4,lr}
	mov	r4,r0
.LDW32:
	ldrb	r0,[r0]
.L379:

	bl	Stm_Std_SetPhyEL2TimerInterrupt
	ldr	r0,[r4,4]
	pop	{r4,lr}
.L381:

	b	Stm_Std_SetPhyEL2TimerEvent
.LDW42:
__ghs_eofn_Stm_Hal_InitPhyEL2Timer::
	.endf	Stm_Hal_InitPhyEL2Timer

;pTimerConfig	r4	param

	.section ".bss","awb"
.L359:
	.endo	.L359
	.section ".ghcalltbl",""
.L380:	.data.w	.L379
	.endo	.L380
	.section ".ghtailcalltbl",""
.L382:	.data.w	.L381
	.endo	.L382
	.data
	.global	__caller.Stm_Std_SetPhyEL2TimerEvent.v.p

	.global	__caller.Stm_Std_SetPhyEL2TimerInterrupt.v.i

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
__callee.Stm_Hal_InitVirtualTimer.v.p::
	.size	__callee.Stm_Hal_InitVirtualTimer.v.p,0
Stm_Hal_InitVirtualTimer::
.LDW52:
	push	{r4,lr}
	mov	r4,r0
.LDW62:
	ldrb	r0,[r0]
.L427:

	bl	Stm_Std_SetVirtualTimerInterrupt
	ldr	r0,[r4,4]
	pop	{r4,lr}
.L429:

	b	Stm_Std_SetVirtualTimerEvent
.LDW72:
__ghs_eofn_Stm_Hal_InitVirtualTimer::
	.endf	Stm_Hal_InitVirtualTimer

;pTimerConfig	r4	param

	.section ".bss","awb"
.L407:
	.endo	.L407
	.section ".ghcalltbl",""
.L428:	.data.w	.L427
	.endo	.L428
	.section ".ghtailcalltbl",""
.L430:	.data.w	.L429
	.endo	.L430
	.data
	.global	__caller.Stm_Std_SetVirtualTimerEvent.v.p

	.global	__caller.Stm_Std_SetVirtualTimerInterrupt.v.i

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
__callee.Stm_Hal_Get32BitPhyEL1TimerValue.i.v::
	.size	__callee.Stm_Hal_Get32BitPhyEL1TimerValue.i.v,0
Stm_Hal_Get32BitPhyEL1TimerValue::
.LDW82:
.LDW92:
..gh.beginasm.11:
	.endo	..gh.beginasm.11
MRC p15, 0, r0, c14, c2, 0

..gh.endasm.12:
	.endo	..gh.endasm.12

.LDW03:
.L473:

;line183
..lin.78d5b950..288e02a1.0_4::
.LDWlin4:
	ret	
__ghs_eofn_Stm_Hal_Get32BitPhyEL1TimerValue::
	.endf	Stm_Hal_Get32BitPhyEL1TimerValue

	.section ".bss","awb"
.L455:
	.endo	.L455
	.section ".ghrettbl",""
.L474:	.data.w	.L473
	.endo	.L474
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
__callee.Stm_Hal_Get32BitPhyEL2TimerValue.i.v::
	.size	__callee.Stm_Hal_Get32BitPhyEL2TimerValue.i.v,0
Stm_Hal_Get32BitPhyEL2TimerValue::
.LDW13:
.LDW23:
..gh.beginasm.14:
	.endo	..gh.beginasm.14
MRC p15, 4, r0, c14, c2, 0

..gh.endasm.15:
	.endo	..gh.endasm.15

.LDW33:
.L521:

;line197
..lin.78d5b950..adeab7e2.0_5::
.LDWlin5:
	ret	
__ghs_eofn_Stm_Hal_Get32BitPhyEL2TimerValue::
	.endf	Stm_Hal_Get32BitPhyEL2TimerValue

	.section ".bss","awb"
.L503:
	.endo	.L503
	.section ".ghrettbl",""
.L522:	.data.w	.L521
	.endo	.L522
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
__callee.Stm_Hal_Get32BitVirtualTimerValue.i.v::
	.size	__callee.Stm_Hal_Get32BitVirtualTimerValue.i.v,0
Stm_Hal_Get32BitVirtualTimerValue::
.LDW43:
.LDW53:
..gh.beginasm.17:
	.endo	..gh.beginasm.17
MRC p15, 0, r0, c14, c3, 0

..gh.endasm.18:
	.endo	..gh.endasm.18

.LDW63:
.L569:

;line210
..lin.78d5b950..190d8075.0_6::
.LDWlin6:
	ret	
__ghs_eofn_Stm_Hal_Get32BitVirtualTimerValue::
	.endf	Stm_Hal_Get32BitVirtualTimerValue

	.section ".bss","awb"
.L551:
	.endo	.L551
	.section ".ghrettbl",""
.L570:	.data.w	.L569
	.endo	.L570
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.19:
	.endo	..gh.f.a.1.e.19
__callee.Stm_Hal_Get64BitPhyEL1TimerCompareValue.l.v::
	.size	__callee.Stm_Hal_Get64BitPhyEL1TimerCompareValue.l.v,0
Stm_Hal_Get64BitPhyEL1TimerCompareValue::
.LDW73:
.LDW83:
.LDW93:

..gh.beginasm.20:
	.endo	..gh.beginasm.20
MRRC p15, 2, r0, r1, c14

..gh.endasm.21:
	.endo	..gh.endasm.21

.LDW04:

.LDW14:
.L617:

;line223
..lin.78d5b950..f38f308d.0_7::
.LDWlin7:
	ret	
__ghs_eofn_Stm_Hal_Get64BitPhyEL1TimerCompareValue::
	.endf	Stm_Hal_Get64BitPhyEL1TimerCompareValue

	.section ".bss","awb"
.L599:
	.endo	.L599
	.section ".ghrettbl",""
.L618:	.data.w	.L617
	.endo	.L618
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.22:
	.endo	..gh.f.a.1.e.22
__callee.Stm_Hal_Get64BitPhyEL2TimerCompareValue.l.v::
	.size	__callee.Stm_Hal_Get64BitPhyEL2TimerCompareValue.l.v,0
Stm_Hal_Get64BitPhyEL2TimerCompareValue::
.LDW24:
.LDW34:
.LDW44:

..gh.beginasm.23:
	.endo	..gh.beginasm.23
MRRC p15, 6, r0, r1, c14

..gh.endasm.24:
	.endo	..gh.endasm.24

.LDW54:

.LDW64:
.L665:

;line236
..lin.78d5b950..e1a552ae.0_8::
.LDWlin8:
	ret	
__ghs_eofn_Stm_Hal_Get64BitPhyEL2TimerCompareValue::
	.endf	Stm_Hal_Get64BitPhyEL2TimerCompareValue

	.section ".bss","awb"
.L647:
	.endo	.L647
	.section ".ghrettbl",""
.L666:	.data.w	.L665
	.endo	.L666
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.25:
	.endo	..gh.f.a.1.e.25
__callee.Stm_Hal_Get64BitVirtualTimerCompareValue.l.v::
	.size	__callee.Stm_Hal_Get64BitVirtualTimerCompareValue.l.v,0
Stm_Hal_Get64BitVirtualTimerCompareValue::
.LDW74:
.LDW84:
.LDW94:

..gh.beginasm.26:
	.endo	..gh.beginasm.26
MRRC p15, 3, r0, r1, c14

..gh.endasm.27:
	.endo	..gh.endasm.27

.LDW05:

.LDW15:
.L713:

;line249
..lin.78d5b950..2369ec81.0_9::
.LDWlin9:
	ret	
__ghs_eofn_Stm_Hal_Get64BitVirtualTimerCompareValue::
	.endf	Stm_Hal_Get64BitVirtualTimerCompareValue

	.section ".bss","awb"
.L695:
	.endo	.L695
	.section ".ghrettbl",""
.L714:	.data.w	.L713
	.endo	.L714
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.28:
	.endo	..gh.f.a.1.e.28
__callee.Stm_Hal_Set32BitPhyEL1TimerValue.v.i::
	.size	__callee.Stm_Hal_Set32BitPhyEL1TimerValue.v.i,0
Stm_Hal_Set32BitPhyEL1TimerValue::
.LDW25:
.LDW35:
..gh.beginasm.29:
	.endo	..gh.beginasm.29
MCR p15, 0, r0, c14, c2, 0

..gh.endasm.30:
	.endo	..gh.endasm.30

.LDW45:
.L761:

;line260
..lin.78d5b950..db7f952d.0_10::
.LDWlin10:
	ret	
__ghs_eofn_Stm_Hal_Set32BitPhyEL1TimerValue::
	.endf	Stm_Hal_Set32BitPhyEL1TimerValue

;value	r0	param

	.section ".bss","awb"
.L743:
	.endo	.L743
	.section ".ghrettbl",""
.L762:	.data.w	.L761
	.endo	.L762
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.31:
	.endo	..gh.f.a.1.e.31
__callee.Stm_Hal_Set32BitPhyEL2TimerValue.v.i::
	.size	__callee.Stm_Hal_Set32BitPhyEL2TimerValue.v.i,0
Stm_Hal_Set32BitPhyEL2TimerValue::
.LDW55:
.LDW65:
..gh.beginasm.32:
	.endo	..gh.beginasm.32
MCR p15, 4, r0, c14, c2, 0

..gh.endasm.33:
	.endo	..gh.endasm.33

.LDW75:
.L809:

;line270
..lin.78d5b950..60dc4a6e.0_11::
.LDWlin11:
	ret	
__ghs_eofn_Stm_Hal_Set32BitPhyEL2TimerValue::
	.endf	Stm_Hal_Set32BitPhyEL2TimerValue

;value	r0	param

	.section ".bss","awb"
.L791:
	.endo	.L791
	.section ".ghrettbl",""
.L810:	.data.w	.L809
	.endo	.L810
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.34:
	.endo	..gh.f.a.1.e.34
__callee.Stm_Hal_Set32BitVirtualTimerValue.v.i::
	.size	__callee.Stm_Hal_Set32BitVirtualTimerValue.v.i,0
Stm_Hal_Set32BitVirtualTimerValue::
.LDW85:
.LDW95:
..gh.beginasm.35:
	.endo	..gh.beginasm.35
MCR p15, 0, r0, c14, c3, 0

..gh.endasm.36:
	.endo	..gh.endasm.36

.LDW06:
.L857:

;line280
..lin.78d5b950..2a316481.0_12::
.LDWlin12:
	ret	
__ghs_eofn_Stm_Hal_Set32BitVirtualTimerValue::
	.endf	Stm_Hal_Set32BitVirtualTimerValue

;value	r0	param

	.section ".bss","awb"
.L839:
	.endo	.L839
	.section ".ghrettbl",""
.L858:	.data.w	.L857
	.endo	.L858
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.37:
	.endo	..gh.f.a.1.e.37
__callee.Stm_Hal_Set64BitPhyEL1TimerCompareValue.v.l::
	.size	__callee.Stm_Hal_Set64BitPhyEL1TimerCompareValue.v.l,0
Stm_Hal_Set64BitPhyEL1TimerCompareValue::
.LDW16:
.LDW26:
.LDW36:

..gh.beginasm.38:
	.endo	..gh.beginasm.38
MCRR p15, 2, r0, r1, c14

..gh.endasm.39:
	.endo	..gh.endasm.39

.LDW46:

.LDW56:
.L905:

;line293
..lin.78d5b950..8cc8ed99.0_13::
.LDWlin13:
	ret	
__ghs_eofn_Stm_Hal_Set64BitPhyEL1TimerCompareValue::
	.endf	Stm_Hal_Set64BitPhyEL1TimerCompareValue

;value	r0	param

	.section ".bss","awb"
.L887:
	.endo	.L887
	.section ".ghrettbl",""
.L906:	.data.w	.L905
	.endo	.L906
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.40:
	.endo	..gh.f.a.1.e.40
__callee.Stm_Hal_Set64BitPhyEL2TimerCompareValue.v.l::
	.size	__callee.Stm_Hal_Set64BitPhyEL2TimerCompareValue.v.l,0
Stm_Hal_Set64BitPhyEL2TimerCompareValue::
.LDW66:
.LDW76:
.LDW86:

..gh.beginasm.41:
	.endo	..gh.beginasm.41
MCRR p15, 6, r0, r1, c14

..gh.endasm.42:
	.endo	..gh.endasm.42

.LDW96:

.LDW07:
.L953:

;line305
..lin.78d5b950..7adf0fba.0_14::
.LDWlin14:
	ret	
__ghs_eofn_Stm_Hal_Set64BitPhyEL2TimerCompareValue::
	.endf	Stm_Hal_Set64BitPhyEL2TimerCompareValue

;value	r0	param

	.section ".bss","awb"
.L935:
	.endo	.L935
	.section ".ghrettbl",""
.L954:	.data.w	.L953
	.endo	.L954
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.43:
	.endo	..gh.f.a.1.e.43
__callee.Stm_Hal_Set64BitVirtualTimerCompareValue.v.l::
	.size	__callee.Stm_Hal_Set64BitVirtualTimerCompareValue.v.l,0
Stm_Hal_Set64BitVirtualTimerCompareValue::
.LDW17:
.LDW27:
.LDW37:

..gh.beginasm.44:
	.endo	..gh.beginasm.44
MCRR p15, 3, r0, r1, c14

..gh.endasm.45:
	.endo	..gh.endasm.45

.LDW47:

.LDW57:
.L1001:

;line318
..lin.78d5b950..e3db4b0d.0_15::
.LDWlin15:
	ret	
__ghs_eofn_Stm_Hal_Set64BitVirtualTimerCompareValue::
	.endf	Stm_Hal_Set64BitVirtualTimerCompareValue

;value	r0	param

	.section ".bss","awb"
.L983:
	.endo	.L983
	.section ".ghrettbl",""
.L1002:	.data.w	.L1001
	.endo	.L1002
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.46:
	.endo	..gh.f.a.1.e.46
__callee.Stm_Hal_EnablePhyEL1Timer.v.v::
	.size	__callee.Stm_Hal_EnablePhyEL1Timer.v.v,0
Stm_Hal_EnablePhyEL1Timer::
.LDW67:
.LDW77:
..gh.beginasm.47:
	.endo	..gh.beginasm.47
MRC p15, 0, r0, c14, c2, 1

..gh.endasm.48:
	.endo	..gh.endasm.48

;line330
..lin.78d5b950..c8917a27.0_16::
.LDWlin16:
	orr	r0,r0,1
..gh.beginasm.49:
	.endo	..gh.beginasm.49
MCR p15, 0, r0, c14, c2, 1

..gh.endasm.50:
	.endo	..gh.endasm.50

.LDW87:
.L1049:

;line334
..lin.78d5b950..c8917a27.0_17::
.LDWlin17:
	ret	
__ghs_eofn_Stm_Hal_EnablePhyEL1Timer::
	.endf	Stm_Hal_EnablePhyEL1Timer

	.section ".bss","awb"
.L1031:
	.endo	.L1031
	.section ".ghrettbl",""
.L1050:	.data.w	.L1049
	.endo	.L1050
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.51:
	.endo	..gh.f.a.1.e.51
__callee.Stm_Hal_EnablePhyEL2Timer.v.v::
	.size	__callee.Stm_Hal_EnablePhyEL2Timer.v.v,0
Stm_Hal_EnablePhyEL2Timer::
.LDW97:
.LDW08:
..gh.beginasm.52:
	.endo	..gh.beginasm.52
MRC p15, 4, r0, c14, c2, 1

..gh.endasm.53:
	.endo	..gh.endasm.53

;line346
..lin.78d5b950..cae6a2c8.0_18::
.LDWlin18:
	orr	r0,r0,1
..gh.beginasm.54:
	.endo	..gh.beginasm.54
MCR p15, 4, r0, c14, c2, 1

..gh.endasm.55:
	.endo	..gh.endasm.55

.LDW18:
.L1097:

;line350
..lin.78d5b950..cae6a2c8.0_19::
.LDWlin19:
	ret	
__ghs_eofn_Stm_Hal_EnablePhyEL2Timer::
	.endf	Stm_Hal_EnablePhyEL2Timer

	.section ".bss","awb"
.L1079:
	.endo	.L1079
	.section ".ghrettbl",""
.L1098:	.data.w	.L1097
	.endo	.L1098
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.56:
	.endo	..gh.f.a.1.e.56
__callee.Stm_Hal_EnableVirtualTimer.v.v::
	.size	__callee.Stm_Hal_EnableVirtualTimer.v.v,0
Stm_Hal_EnableVirtualTimer::
.LDW28:
.LDW38:
..gh.beginasm.57:
	.endo	..gh.beginasm.57
MRC p15, 0, r0, c14, c3, 1

..gh.endasm.58:
	.endo	..gh.endasm.58

;line362
..lin.78d5b950..4854a3db.0_20::
.LDWlin20:
	orr	r0,r0,1
..gh.beginasm.59:
	.endo	..gh.beginasm.59
MCR p15, 0, r0, c14, c3, 1

..gh.endasm.60:
	.endo	..gh.endasm.60

.LDW48:
.L1145:

;line366
..lin.78d5b950..4854a3db.0_21::
.LDWlin21:
	ret	
__ghs_eofn_Stm_Hal_EnableVirtualTimer::
	.endf	Stm_Hal_EnableVirtualTimer

	.section ".bss","awb"
.L1127:
	.endo	.L1127
	.section ".ghrettbl",""
.L1146:	.data.w	.L1145
	.endo	.L1146
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.61:
	.endo	..gh.f.a.1.e.61
__callee.Stm_Hal_DisablePhyEL1Timer.v.v::
	.size	__callee.Stm_Hal_DisablePhyEL1Timer.v.v,0
Stm_Hal_DisablePhyEL1Timer::
.LDW58:
.LDW68:
..gh.beginasm.62:
	.endo	..gh.beginasm.62
MRC p15, 0, r0, c14, c2, 1

..gh.endasm.63:
	.endo	..gh.endasm.63

;line378
..lin.78d5b950..5f4361f4.0_22::
.LDWlin22:
	bic	r0,r0,1
..gh.beginasm.64:
	.endo	..gh.beginasm.64
MCR p15, 0, r0, c14, c2, 1

..gh.endasm.65:
	.endo	..gh.endasm.65

.LDW78:
.L1193:

;line382
..lin.78d5b950..5f4361f4.0_23::
.LDWlin23:
	ret	
__ghs_eofn_Stm_Hal_DisablePhyEL1Timer::
	.endf	Stm_Hal_DisablePhyEL1Timer

	.section ".bss","awb"
.L1175:
	.endo	.L1175
	.section ".ghrettbl",""
.L1194:	.data.w	.L1193
	.endo	.L1194
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.66:
	.endo	..gh.f.a.1.e.66
__callee.Stm_Hal_DisablePhyEL2Timer.v.v::
	.size	__callee.Stm_Hal_DisablePhyEL2Timer.v.v,0
Stm_Hal_DisablePhyEL2Timer::
.LDW88:
.LDW98:
..gh.beginasm.67:
	.endo	..gh.beginasm.67
MRC p15, 4, r0, c14, c2, 1

..gh.endasm.68:
	.endo	..gh.endasm.68

;line394
..lin.78d5b950..61988a95.0_24::
.LDWlin24:
	bic	r0,r0,1
..gh.beginasm.69:
	.endo	..gh.beginasm.69
MCR p15, 4, r0, c14, c2, 1

..gh.endasm.70:
	.endo	..gh.endasm.70

.LDW09:
.L1241:

;line398
..lin.78d5b950..61988a95.0_25::
.LDWlin25:
	ret	
__ghs_eofn_Stm_Hal_DisablePhyEL2Timer::
	.endf	Stm_Hal_DisablePhyEL2Timer

	.section ".bss","awb"
.L1223:
	.endo	.L1223
	.section ".ghrettbl",""
.L1242:	.data.w	.L1241
	.endo	.L1242
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.71:
	.endo	..gh.f.a.1.e.71
__callee.Stm_Hal_DisableVirtualTimer.v.v::
	.size	__callee.Stm_Hal_DisableVirtualTimer.v.v,0
Stm_Hal_DisableVirtualTimer::
.LDW19:
.LDW29:
..gh.beginasm.72:
	.endo	..gh.beginasm.72
MRC p15, 0, r0, c14, c3, 1

..gh.endasm.73:
	.endo	..gh.endasm.73

;line410
..lin.78d5b950..b5438548.0_26::
.LDWlin26:
	bic	r0,r0,1
..gh.beginasm.74:
	.endo	..gh.beginasm.74
MCR p15, 0, r0, c14, c3, 1

..gh.endasm.75:
	.endo	..gh.endasm.75

.LDW39:
.L1289:

;line414
..lin.78d5b950..b5438548.0_27::
.LDWlin27:
	ret	
__ghs_eofn_Stm_Hal_DisableVirtualTimer::
	.endf	Stm_Hal_DisableVirtualTimer

	.section ".bss","awb"
.L1271:
	.endo	.L1271
	.section ".ghrettbl",""
.L1290:	.data.w	.L1289
	.endo	.L1290
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.76:
	.endo	..gh.f.a.1.e.76
__callee.Stm_Hal_GetPhyEL1TimerStatus.i.v::
	.size	__callee.Stm_Hal_GetPhyEL1TimerStatus.i.v,0
Stm_Hal_GetPhyEL1TimerStatus::
.LDW49:
.LDW59:
..gh.beginasm.77:
	.endo	..gh.beginasm.77
MRC p15, 0, r0, c14, c2, 1

..gh.endasm.78:
	.endo	..gh.endasm.78

;line429
..lin.78d5b950..955f0524.0_28::
.LDWlin28:
	ubfx	r0,r0,2,1
.LDW69:
.L1357:

	ret	
__ghs_eofn_Stm_Hal_GetPhyEL1TimerStatus::
	.endf	Stm_Hal_GetPhyEL1TimerStatus
;status	r0	local

	.section ".bss","awb"
.L1339:
	.endo	.L1339
	.section ".ghrettbl",""
.L1358:	.data.w	.L1357
	.endo	.L1358
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.79:
	.endo	..gh.f.a.1.e.79
__callee.Stm_Hal_GetPhyEL2TimerStatus.i.v::
	.size	__callee.Stm_Hal_GetPhyEL2TimerStatus.i.v,0
Stm_Hal_GetPhyEL2TimerStatus::
.LDW79:
.LDW89:
..gh.beginasm.80:
	.endo	..gh.beginasm.80
MRC p15, 4, r0, c14, c2, 1

..gh.endasm.81:
	.endo	..gh.endasm.81

;line454
..lin.78d5b950..c6526285.0_29::
.LDWlin29:
	ubfx	r0,r0,2,1
.LDW99:
.L1437:

	ret	
__ghs_eofn_Stm_Hal_GetPhyEL2TimerStatus::
	.endf	Stm_Hal_GetPhyEL2TimerStatus
;status	r0	local

	.section ".bss","awb"
.L1419:
	.endo	.L1419
	.section ".ghrettbl",""
.L1438:	.data.w	.L1437
	.endo	.L1438
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.82:
	.endo	..gh.f.a.1.e.82
__callee.Stm_Hal_GetVitualTimerStatus.i.v::
	.size	__callee.Stm_Hal_GetVitualTimerStatus.i.v,0
Stm_Hal_GetVitualTimerStatus::
.LDW001:
.LDW101:
..gh.beginasm.83:
	.endo	..gh.beginasm.83
MRC p15, 0, r0, c14, c3, 1

..gh.endasm.84:
	.endo	..gh.endasm.84

;line479
..lin.78d5b950..c9376d66.0_30::
.LDWlin30:
	ubfx	r0,r0,2,1
.LDW201:
.L1517:

	ret	
__ghs_eofn_Stm_Hal_GetVitualTimerStatus::
	.endf	Stm_Hal_GetVitualTimerStatus
;status	r0	local

	.section ".bss","awb"
.L1499:
	.endo	.L1499
	.section ".ghrettbl",""
.L1518:	.data.w	.L1517
	.endo	.L1518
	.section ".sdk_text_asil_d","ax"

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstm_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257B..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	57,13,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,115,114,99,47,115,116,109,95,104,97,108,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 30
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+30
	.section	.debug_str		;off: 174
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+174
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
	.data.b	193,5,0,0
	.data.b	2,0
	.data.b	110,2,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,115,114,99,47,115,116,109,95,104,97,108,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,112,117,119,100,116,92,105,110,99,92,99,112,117,119,100,116,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,112,117,119,100,116,92,105,110,99,92,99,112,117,119,100,116,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,67,112,117,119,100,116,95,77,101,109,77,97,112,46,104,0
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
	.section	.debug_str		;off: 196
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 36
	.data.w	.Ldw_str_begin+196
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
	.section	.debug_str		;off: 210
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+210
	.data.b	7
	.data.b	4

	.data.b	74
	.data.w	.Ldw_begin+385
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
	.data.w	.Ldw_begin+385
	.data.b	0

	.section	.debug_abbrev		;off: 39
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 61
	.data.b	23
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 224
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 75
	.data.w	.Ldw_str_begin+224
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+385
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+385
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+385
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+421
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1259

	.section	.debug_abbrev		;off: 48
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 113
	.data.b	53
	.data.w	.Ldw_begin+108

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 118
	.data.b	47
	.data.w	.Ldw_begin+113

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 62
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 125
	.data.b	23
	.data.w	.Ldw_begin+118
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+118
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+118
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+409
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+409
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+409
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+421
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+421
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+421
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+421
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+421
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+421
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

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1208
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1208
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1208
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 243
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 286
	.data.w	.Ldw_str_begin+243
	.data.b	7
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+1090

	.section	.debug_abbrev		;off: 69
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 297
	.data.b	53
	.data.w	.Ldw_begin+488

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+385
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+488

	.data.b	53
	.data.w	.Ldw_begin+311

	.data.b	47
	.data.w	.Ldw_begin+316

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+321
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+385
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+321
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+385
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+321
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+385
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+385
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 256
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 386
	.data.w	.Ldw_str_begin+256
	.data.b	51
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+35

	.section	.debug_abbrev		;off: 76
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 397
	.data.b	45
	.section	.debug_str		;off: 264
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 398
	.data.w	.Ldw_str_begin+264
	.data.b	56
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+35

	.data.b	45
	.section	.debug_str		;off: 270
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 410
	.data.w	.Ldw_str_begin+270
	.data.b	64
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 422
	.data.w	.Ldw_str_begin+277
	.data.b	68
	.data.b	29
	.data.b	7
	.data.w	.Ldw_begin+74

	.data.b	71
	.data.b	55
	.data.b	1
	.data.b	3
	.data.b	3
	.data.b	1

	.section	.debug_abbrev		;off: 91
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 439
	.data.b	40
	.section	.debug_str		;off: 284
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 440
	.data.w	.Ldw_str_begin+284
	.data.b	56
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+385
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 106
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

	.section	.debug_info		;off: 455
	.data.b	40
	.section	.debug_str		;off: 291
	.data.b	116,114,97,110,115,105,116,105,111,110,0
	.section	.debug_info		;off: 456
	.data.w	.Ldw_str_begin+291
	.data.b	57
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+385
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 302
	.data.b	103,101,110,101,114,97,116,101,95,98,105,116,0
	.section	.debug_info		;off: 472
	.data.w	.Ldw_str_begin+302
	.data.b	59
	.data.b	11
	.data.b	3
	.data.w	.Ldw_begin+397
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 315
	.data.b	83,116,109,95,69,118,101,110,116,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 489
	.data.w	.Ldw_str_begin+315
	.data.b	60
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+433

	.data.b	45
	.section	.debug_str		;off: 332
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 501
	.data.w	.Ldw_str_begin+332
	.data.b	24
	.data.b	22
	.data.b	10
	.data.w	.Ldw_begin+285

	.data.b	71
	.data.b	31
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 339
	.data.b	69,78,0
	.section	.debug_info		;off: 519
	.data.w	.Ldw_str_begin+339
	.data.b	32
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 125
	.data.b	41
	.data.b	13
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	11,15
	.data.b	12,15
	.data.b	13,11
	.data.b	56,10
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 537
	.data.b	41
	.section	.debug_str		;off: 342
	.data.b	72,68,66,71,0
	.section	.debug_info		;off: 538
	.data.w	.Ldw_str_begin+342
	.data.b	33
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 347
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 557
	.data.w	.Ldw_str_begin+347
	.data.b	34
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 358
	.data.b	83,84,77,95,67,78,84,67,82,95,66,105,116,115,0
	.section	.debug_info		;off: 577
	.data.w	.Ldw_str_begin+358
	.data.b	35
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+512

	.data.b	71
	.data.b	39
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 373
	.data.b	114,101,115,101,114,118,101,100,95,48,0
	.section	.debug_info		;off: 595
	.data.w	.Ldw_str_begin+373
	.data.b	40
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 384
	.data.b	68,66,71,72,0
	.section	.debug_info		;off: 614
	.data.w	.Ldw_str_begin+384
	.data.b	41
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 389
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 633
	.data.w	.Ldw_str_begin+389
	.data.b	42
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 400
	.data.b	83,84,77,95,67,78,84,83,82,95,66,105,116,115,0
	.section	.debug_info		;off: 653
	.data.w	.Ldw_str_begin+400
	.data.b	43
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+588

	.data.b	71
	.data.b	47
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 415
	.data.b	67,78,84,67,86,76,0
	.section	.debug_info		;off: 671
	.data.w	.Ldw_str_begin+415
	.data.b	48
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 422
	.data.b	83,84,77,95,67,78,84,67,86,76,95,66,105,116,115,0
	.section	.debug_info		;off: 691
	.data.w	.Ldw_str_begin+422
	.data.b	49
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+664

	.data.b	71
	.data.b	53
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 438
	.data.b	67,78,84,67,86,85,0
	.section	.debug_info		;off: 709
	.data.w	.Ldw_str_begin+438
	.data.b	54
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 445
	.data.b	83,84,77,95,67,78,84,67,86,85,95,66,105,116,115,0
	.section	.debug_info		;off: 729
	.data.w	.Ldw_str_begin+445
	.data.b	55
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+702

	.data.b	71
	.data.b	59
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 461
	.data.b	69,78,65,66,76,69,0
	.section	.debug_info		;off: 747
	.data.w	.Ldw_str_begin+461
	.data.b	60
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 468
	.data.b	73,77,65,83,75,0
	.section	.debug_info		;off: 766
	.data.w	.Ldw_str_begin+468
	.data.b	61
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 474
	.data.b	73,83,84,65,84,85,83,0
	.section	.debug_info		;off: 785
	.data.w	.Ldw_str_begin+474
	.data.b	62
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 482
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 804
	.data.w	.Ldw_str_begin+482
	.data.b	63
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+285
	.data.b	4
	.data.b	0
	.data.b	29
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 493
	.data.b	84,73,77,69,82,95,67,84,76,95,66,105,116,115,0
	.section	.debug_info		;off: 824
	.data.w	.Ldw_str_begin+493
	.data.b	64
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+740

	.data.b	73
	.data.b	87
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 150
	.data.b	73
	.data.b	23
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 841
	.data.b	40
	.section	.debug_str		;off: 508
	.data.b	85,0
	.section	.debug_info		;off: 842
	.data.w	.Ldw_str_begin+508
	.data.b	88
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 510
	.data.b	66,0
	.section	.debug_info		;off: 858
	.data.w	.Ldw_str_begin+510
	.data.b	89
	.data.b	20
	.data.b	9
	.data.w	.Ldw_begin+576
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 512
	.data.b	83,84,77,95,67,78,84,67,82,0
	.section	.debug_info		;off: 875
	.data.w	.Ldw_str_begin+512
	.data.b	90
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+835

	.data.b	73
	.data.b	95
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 522
	.data.b	85,0
	.section	.debug_info		;off: 893
	.data.w	.Ldw_str_begin+522
	.data.b	96
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 524
	.data.b	66,0
	.section	.debug_info		;off: 909
	.data.w	.Ldw_str_begin+524
	.data.b	97
	.data.b	20
	.data.b	9
	.data.w	.Ldw_begin+652
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 526
	.data.b	83,84,77,95,67,78,84,83,82,0
	.section	.debug_info		;off: 926
	.data.w	.Ldw_str_begin+526
	.data.b	98
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+886

	.data.b	73
	.data.b	103
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 536
	.data.b	85,0
	.section	.debug_info		;off: 944
	.data.w	.Ldw_str_begin+536
	.data.b	104
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 538
	.data.b	66,0
	.section	.debug_info		;off: 960
	.data.w	.Ldw_str_begin+538
	.data.b	105
	.data.b	21
	.data.b	9
	.data.w	.Ldw_begin+690
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 540
	.data.b	83,84,77,95,67,78,84,67,86,76,0
	.section	.debug_info		;off: 977
	.data.w	.Ldw_str_begin+540
	.data.b	106
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+937

	.data.b	73
	.data.b	111
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 551
	.data.b	85,0
	.section	.debug_info		;off: 995
	.data.w	.Ldw_str_begin+551
	.data.b	112
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 553
	.data.b	66,0
	.section	.debug_info		;off: 1011
	.data.w	.Ldw_str_begin+553
	.data.b	113
	.data.b	21
	.data.b	9
	.data.w	.Ldw_begin+728
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 555
	.data.b	83,84,77,95,67,78,84,67,86,85,0
	.section	.debug_info		;off: 1028
	.data.w	.Ldw_str_begin+555
	.data.b	114
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+988

	.data.b	73
	.data.b	119
	.data.b	1
	.data.b	9
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 566
	.data.b	85,0
	.section	.debug_info		;off: 1046
	.data.w	.Ldw_str_begin+566
	.data.b	120
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 568
	.data.b	66,0
	.section	.debug_info		;off: 1062
	.data.w	.Ldw_str_begin+568
	.data.b	121
	.data.b	20
	.data.b	9
	.data.w	.Ldw_begin+823
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 570
	.data.b	84,73,77,69,82,95,67,84,76,0
	.section	.debug_info		;off: 1079
	.data.w	.Ldw_str_begin+570
	.data.b	122
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+1039

	.data.b	71
	.data.b	137,1
	.data.b	1
	.data.b	9
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 580
	.data.b	67,78,84,67,82,0
	.section	.debug_info		;off: 1098
	.data.w	.Ldw_str_begin+580
	.data.b	138,1
	.data.b	15
	.data.b	9
	.data.w	.Ldw_begin+874
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 586
	.data.b	67,78,84,83,82,0
	.section	.debug_info		;off: 1115
	.data.w	.Ldw_str_begin+586
	.data.b	139,1
	.data.b	15
	.data.b	9
	.data.w	.Ldw_begin+925
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 592
	.data.b	67,78,84,67,86,76,0
	.section	.debug_info		;off: 1132
	.data.w	.Ldw_str_begin+592
	.data.b	140,1
	.data.b	16
	.data.b	9
	.data.w	.Ldw_begin+976
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 599
	.data.b	67,78,84,67,86,85,0
	.section	.debug_info		;off: 1149
	.data.w	.Ldw_str_begin+599
	.data.b	141,1
	.data.b	16
	.data.b	9
	.data.w	.Ldw_begin+1027
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 606
	.data.b	83,84,77,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 1167
	.data.w	.Ldw_str_begin+606
	.data.b	142,1
	.data.b	3
	.data.b	9
	.data.w	.Ldw_begin+292

	.data.b	52
	.section	.debug_str		;off: 617
	.data.b	0
	.section	.debug_info		;off: 1180
	.data.w	.Ldw_str_begin+617
	.data.b	51
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 165
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

	.section	.debug_info		;off: 1189
	.data.b	51
	.section	.debug_str		;off: 618
	.data.b	83,84,77,95,84,73,77,69,82,95,78,79,84,95,77,69,84,0
	.section	.debug_info		;off: 1190
	.data.w	.Ldw_str_begin+618
	.data.b	52
	.data.b	5
	.data.b	2
	.data.b	0

	.section	.debug_abbrev		;off: 182
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 1198
	.data.b	51
	.section	.debug_str		;off: 636
	.data.b	83,84,77,95,84,73,77,69,82,95,77,69,84,0
	.section	.debug_info		;off: 1199
	.data.w	.Ldw_str_begin+636
	.data.b	53
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 650
	.data.b	83,116,109,95,84,105,109,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 1209
	.data.w	.Ldw_str_begin+650
	.data.b	54
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+1179

	.data.b	71
	.data.b	64
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 666
	.data.b	105,110,116,114,0
	.section	.debug_info		;off: 1227
	.data.w	.Ldw_str_begin+666
	.data.b	65
	.data.b	13
	.data.b	2
	.data.w	.Ldw_begin+385
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 671
	.data.b	112,69,118,101,110,116,95,99,102,103,0
	.section	.debug_info		;off: 1243
	.data.w	.Ldw_str_begin+671
	.data.b	66
	.data.b	23
	.data.b	2
	.data.w	.Ldw_begin+297
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 682
	.data.b	83,116,109,95,84,105,109,101,114,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1260
	.data.w	.Ldw_str_begin+682
	.data.b	67
	.data.b	3
	.data.b	2
	.data.w	.Ldw_begin+1220

	.data.b	27
	.section	.debug_str		;off: 699
	.data.b	83,116,109,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 1272
	.data.w	.Ldw_str_begin+699
	.data.b	96
	.data.b	27
	.data.b	3
	.data.w	.Ldw_begin+385
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 197
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

	.section	.debug_info		;off: 1289
	.data.b	20
	.section	.debug_str		;off: 727
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 1290
	.data.w	.Ldw_str_begin+727
	.data.b	96
	.data.b	63
	.data.b	3
	.data.w	.Ldw_begin+385
	.data.b	0

	.section	.debug_abbrev		;off: 224
	.data.b	20
	.data.b	5
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 1302
	.data.b	20
	.section	.debug_str		;off: 733
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 1303
	.data.w	.Ldw_str_begin+733
	.data.b	96
	.data.b	77
	.data.b	3
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 740
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 1316
	.data.w	.Ldw_str_begin+740
	.data.b	96
	.data.b	92
	.data.b	3
	.data.w	.Ldw_begin+409
	.data.b	0

	.data.b	37

	.section	.debug_abbrev		;off: 241
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 1329
	.data.b	8
	.section	.debug_str		;off: 746
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1330
	.data.w	.Ldw_str_begin+746
	.data.b	98
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+385
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 246
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

	.section	.debug_info		;off: 1343
	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 750
	.data.b	83,116,109,95,83,116,100,95,83,101,116,80,104,121,69,76,49,84,105,109,101,114,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 1346
	.data.w	.Ldw_str_begin+750
	.data.b	136,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 265
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

	.section	.debug_info		;off: 1360
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 782
	.data.b	83,116,109,95,83,116,100,95,83,101,116,80,104,121,69,76,49,84,105,109,101,114,69,118,101,110,116,0
	.section	.debug_info		;off: 1362
	.data.w	.Ldw_str_begin+782
	.data.b	152,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 810
	.data.b	83,116,109,95,83,116,100,95,83,101,116,80,104,121,69,76,50,84,105,109,101,114,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 1378
	.data.w	.Ldw_str_begin+810
	.data.b	168,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 842
	.data.b	83,116,109,95,83,116,100,95,83,101,116,80,104,121,69,76,50,84,105,109,101,114,69,118,101,110,116,0
	.section	.debug_info		;off: 1394
	.data.w	.Ldw_str_begin+842
	.data.b	184,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 870
	.data.b	83,116,109,95,83,116,100,95,83,101,116,86,105,114,116,117,97,108,84,105,109,101,114,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 1410
	.data.w	.Ldw_str_begin+870
	.data.b	200,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 903
	.data.b	83,116,109,95,83,116,100,95,83,101,116,86,105,114,116,117,97,108,84,105,109,101,114,69,118,101,110,116,0
	.section	.debug_info		;off: 1426
	.data.w	.Ldw_str_begin+903
	.data.b	216,1
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 932
	.data.b	67,112,117,119,100,116,95,72,97,108,95,67,108,101,97,114,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 1442
	.data.w	.Ldw_str_begin+932
	.data.b	147,3
	.data.b	16
	.data.b	13
	.data.w	.Ldw_begin+385
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 956
	.data.b	67,112,117,119,100,116,95,72,97,108,95,83,101,116,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 1462
	.data.w	.Ldw_str_begin+956
	.data.b	165,3
	.data.b	16
	.data.b	13
	.data.w	.Ldw_begin+385
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 978
	.data.b	83,116,109,95,72,97,108,95,83,116,97,114,116,0
	.section	.debug_info		;off: 1482
	.data.w	.Ldw_str_begin+978
	.data.b	68
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.w	Stm_Hal_Start
	.data.w	__ghs_eofn_Stm_Hal_Start
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

	.section	.debug_abbrev		;off: 290
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
	.data.w	Stm_Hal_Start
	.data.w	__ghs_eofn_Stm_Hal_Start-Stm_Hal_Start
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 632
	.data.b	0,5,2
	.data.w	Stm_Hal_Start
	.data.b	6
	.data.b	3
	.data.b	196,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	108
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1516
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 338
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 1525
	.data.b	7
	.section	.debug_str		;off: 992
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1526
	.data.w	.Ldw_str_begin+992
	.data.b	70
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 347
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

	.section	.debug_info		;off: 1543
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 996
	.data.b	83,116,109,95,72,97,108,95,83,116,111,112,0
	.section	.debug_info		;off: 1546
	.data.w	.Ldw_str_begin+996
	.data.b	89
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.w	Stm_Hal_Stop
	.data.w	__ghs_eofn_Stm_Hal_Stop
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Stop
	.data.w	__ghs_eofn_Stm_Hal_Stop-Stm_Hal_Stop
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 668
	.data.b	0,5,2
	.data.w	Stm_Hal_Stop
	.data.b	6
	.data.b	3
	.data.b	217,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1580
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 1009
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1590
	.data.w	.Ldw_str_begin+1009
	.data.b	91
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1607
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1013
	.data.b	83,116,109,95,72,97,108,95,83,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 1610
	.data.w	.Ldw_str_begin+1013
	.data.b	110
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.w	Stm_Hal_SetValue
	.data.w	__ghs_eofn_Stm_Hal_SetValue
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	12
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
	.data.w	Stm_Hal_SetValue
	.data.w	__ghs_eofn_Stm_Hal_SetValue-Stm_Hal_SetValue
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 700
	.data.b	0,5,2
	.data.w	Stm_Hal_SetValue
	.data.b	6
	.data.b	3
	.data.b	238,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	28
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1644
	.data.b	22
	.section	.debug_str		;off: 1030
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 1645
	.data.w	.Ldw_str_begin+1030
	.data.b	110
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	80
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 368
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

	.section	.debug_info		;off: 1661
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 1036
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1671
	.data.w	.Ldw_str_begin+1036
	.data.b	112
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+385
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1688
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1040
	.data.b	83,116,109,95,72,97,108,95,73,110,105,116,80,104,121,69,76,49,84,105,109,101,114,0
	.section	.debug_info		;off: 1691
	.data.w	.Ldw_str_begin+1040
	.data.b	135,1
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_InitPhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_InitPhyEL1Timer
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

	.section	.debug_abbrev		;off: 387
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

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_InitPhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_InitPhyEL1Timer-Stm_Hal_InitPhyEL1Timer
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 757
	.data.b	0,5,2
	.data.w	Stm_Hal_InitPhyEL1Timer
	.data.b	6
	.data.b	3
	.data.b	135,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,1,1
	.section	.debug_info		;off: 1722
	.data.b	22
	.section	.debug_str		;off: 1064
	.data.b	112,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1723
	.data.w	.Ldw_str_begin+1064
	.data.b	135,1
	.data.b	60
	.data.b	1
	.data.w	.Ldw_begin+118
	.data.b	0
	.data.w	.Ldw_loc_begin+87
	.section	.debug_loc		;off: 87
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	80
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1740
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1077
	.data.b	83,116,109,95,72,97,108,95,73,110,105,116,80,104,121,69,76,50,84,105,109,101,114,0
	.section	.debug_info		;off: 1752
	.data.w	.Ldw_str_begin+1077
	.data.b	148,1
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_InitPhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_InitPhyEL2Timer
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_InitPhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_InitPhyEL2Timer-Stm_Hal_InitPhyEL2Timer
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 782
	.data.b	0,5,2
	.data.w	Stm_Hal_InitPhyEL2Timer
	.data.b	6
	.data.b	3
	.data.b	148,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,1,1
	.section	.debug_info		;off: 1783
	.data.b	22
	.section	.debug_str		;off: 1101
	.data.b	112,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1784
	.data.w	.Ldw_str_begin+1101
	.data.b	148,1
	.data.b	60
	.data.b	1
	.data.w	.Ldw_begin+118
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW22
	.data.w	.LDW32
	.data.b	1,0
	.data.b	80
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1801
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1114
	.data.b	83,116,109,95,72,97,108,95,73,110,105,116,86,105,114,116,117,97,108,84,105,109,101,114,0
	.section	.debug_info		;off: 1813
	.data.w	.Ldw_str_begin+1114
	.data.b	161,1
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_InitVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_InitVirtualTimer
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_InitVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_InitVirtualTimer-Stm_Hal_InitVirtualTimer
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 807
	.data.b	0,5,2
	.data.w	Stm_Hal_InitVirtualTimer
	.data.b	6
	.data.b	3
	.data.b	161,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,1,1
	.section	.debug_info		;off: 1844
	.data.b	22
	.section	.debug_str		;off: 1139
	.data.b	112,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1845
	.data.w	.Ldw_str_begin+1139
	.data.b	161,1
	.data.b	61
	.data.b	1
	.data.w	.Ldw_begin+118
	.data.b	0
	.data.w	.Ldw_loc_begin+147
	.section	.debug_loc		;off: 147
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	80
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1862
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1152
	.data.b	83,116,109,95,72,97,108,95,71,101,116,51,50,66,105,116,80,104,121,69,76,49,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 1874
	.data.w	.Ldw_str_begin+1152
	.data.b	175,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.w	Stm_Hal_Get32BitPhyEL1TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitPhyEL1TimerValue
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
	.data.w	Stm_Hal_Get32BitPhyEL1TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitPhyEL1TimerValue-Stm_Hal_Get32BitPhyEL1TimerValue
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 832
	.data.b	0,5,2
	.data.w	Stm_Hal_Get32BitPhyEL1TimerValue
	.data.b	6
	.data.b	3
	.data.b	181,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1907
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	8
	.section	.debug_str		;off: 1185
	.data.b	114,101,115,117,108,116,0
	.section	.debug_info		;off: 1917
	.data.w	.Ldw_str_begin+1185
	.data.b	177,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1192
	.data.b	83,116,109,95,72,97,108,95,71,101,116,51,50,66,105,116,80,104,121,69,76,50,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 1934
	.data.w	.Ldw_str_begin+1192
	.data.b	189,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.w	Stm_Hal_Get32BitPhyEL2TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitPhyEL2TimerValue
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
	.data.w	Stm_Hal_Get32BitPhyEL2TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitPhyEL2TimerValue-Stm_Hal_Get32BitPhyEL2TimerValue
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 859
	.data.b	0,5,2
	.data.w	Stm_Hal_Get32BitPhyEL2TimerValue
	.data.b	6
	.data.b	3
	.data.b	195,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1967
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	8
	.section	.debug_str		;off: 1225
	.data.b	114,101,115,117,108,116,0
	.section	.debug_info		;off: 1977
	.data.w	.Ldw_str_begin+1225
	.data.b	191,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1232
	.data.b	83,116,109,95,72,97,108,95,71,101,116,51,50,66,105,116,86,105,114,116,117,97,108,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 1994
	.data.w	.Ldw_str_begin+1232
	.data.b	202,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.w	Stm_Hal_Get32BitVirtualTimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitVirtualTimerValue
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
	.data.w	Stm_Hal_Get32BitVirtualTimerValue
	.data.w	__ghs_eofn_Stm_Hal_Get32BitVirtualTimerValue-Stm_Hal_Get32BitVirtualTimerValue
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 886
	.data.b	0,5,2
	.data.w	Stm_Hal_Get32BitVirtualTimerValue
	.data.b	6
	.data.b	3
	.data.b	208,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2027
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	8
	.section	.debug_str		;off: 1266
	.data.b	114,101,115,117,108,116,0
	.section	.debug_info		;off: 2037
	.data.w	.Ldw_str_begin+1266
	.data.b	204,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1273
	.data.b	83,116,109,95,72,97,108,95,71,101,116,54,52,66,105,116,80,104,121,69,76,49,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2054
	.data.w	.Ldw_str_begin+1273
	.data.b	215,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.w	Stm_Hal_Get64BitPhyEL1TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitPhyEL1TimerCompareValue
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
	.data.w	Stm_Hal_Get64BitPhyEL1TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitPhyEL1TimerCompareValue-Stm_Hal_Get64BitPhyEL1TimerCompareValue
	.data.b	1
	.data.w	.LDW14
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 913
	.data.b	0,5,2
	.data.w	Stm_Hal_Get64BitPhyEL1TimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	221,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2087
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW14

	.data.b	8
	.section	.debug_str		;off: 1313
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2097
	.data.w	.Ldw_str_begin+1313
	.data.b	217,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	0

	.data.b	34
	.data.w	.LDW93
	.data.w	.LDW04

	.data.b	8
	.section	.debug_str		;off: 1326
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2121
	.data.w	.Ldw_str_begin+1326
	.data.b	222,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1336
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2136
	.data.w	.Ldw_str_begin+1336
	.data.b	222,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1346
	.data.b	83,116,109,95,72,97,108,95,71,101,116,54,52,66,105,116,80,104,121,69,76,50,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2154
	.data.w	.Ldw_str_begin+1346
	.data.b	228,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.w	Stm_Hal_Get64BitPhyEL2TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitPhyEL2TimerCompareValue
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
	.data.w	Stm_Hal_Get64BitPhyEL2TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitPhyEL2TimerCompareValue-Stm_Hal_Get64BitPhyEL2TimerCompareValue
	.data.b	1
	.data.w	.LDW64
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 940
	.data.b	0,5,2
	.data.w	Stm_Hal_Get64BitPhyEL2TimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	234,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2187
	.data.b	34
	.data.w	.LDW34
	.data.w	.LDW64

	.data.b	8
	.section	.debug_str		;off: 1386
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2197
	.data.w	.Ldw_str_begin+1386
	.data.b	230,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	0

	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	8
	.section	.debug_str		;off: 1399
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2221
	.data.w	.Ldw_str_begin+1399
	.data.b	235,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1409
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2236
	.data.w	.Ldw_str_begin+1409
	.data.b	235,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 1419
	.data.b	83,116,109,95,72,97,108,95,71,101,116,54,52,66,105,116,86,105,114,116,117,97,108,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2254
	.data.w	.Ldw_str_begin+1419
	.data.b	241,1
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.w	Stm_Hal_Get64BitVirtualTimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitVirtualTimerCompareValue
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
	.data.w	Stm_Hal_Get64BitVirtualTimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Get64BitVirtualTimerCompareValue-Stm_Hal_Get64BitVirtualTimerCompareValue
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 967
	.data.b	0,5,2
	.data.w	Stm_Hal_Get64BitVirtualTimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	247,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2287
	.data.b	34
	.data.w	.LDW84
	.data.w	.LDW15

	.data.b	8
	.section	.debug_str		;off: 1460
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2297
	.data.w	.Ldw_str_begin+1460
	.data.b	243,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	0

	.data.b	34
	.data.w	.LDW94
	.data.w	.LDW05

	.data.b	8
	.section	.debug_str		;off: 1473
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2321
	.data.w	.Ldw_str_begin+1473
	.data.b	248,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1483
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2336
	.data.w	.Ldw_str_begin+1483
	.data.b	248,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1493
	.data.b	83,116,109,95,72,97,108,95,83,101,116,51,50,66,105,116,80,104,121,69,76,49,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 2354
	.data.w	.Ldw_str_begin+1493
	.data.b	254,1
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set32BitPhyEL1TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitPhyEL1TimerValue
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
	.data.w	Stm_Hal_Set32BitPhyEL1TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitPhyEL1TimerValue-Stm_Hal_Set32BitPhyEL1TimerValue
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 994
	.data.b	0,5,2
	.data.w	Stm_Hal_Set32BitPhyEL1TimerValue
	.data.b	6
	.data.b	3
	.data.b	130,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2383
	.data.b	19
	.section	.debug_str		;off: 1526
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2384
	.data.w	.Ldw_str_begin+1526
	.data.b	254,1
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	1
	.data.b	80

	.section	.debug_abbrev		;off: 433
	.data.b	19
	.data.b	5
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	75,12
	.data.b	2,10
	.data.b	0,0

	.section	.debug_info		;off: 2399
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1532
	.data.b	83,116,109,95,72,97,108,95,83,101,116,51,50,66,105,116,80,104,121,69,76,50,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 2411
	.data.w	.Ldw_str_begin+1532
	.data.b	136,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set32BitPhyEL2TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitPhyEL2TimerValue
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Set32BitPhyEL2TimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitPhyEL2TimerValue-Stm_Hal_Set32BitPhyEL2TimerValue
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1021
	.data.b	0,5,2
	.data.w	Stm_Hal_Set32BitPhyEL2TimerValue
	.data.b	6
	.data.b	3
	.data.b	140,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2440
	.data.b	19
	.section	.debug_str		;off: 1565
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2441
	.data.w	.Ldw_str_begin+1565
	.data.b	136,2
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	1
	.data.b	80

	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1571
	.data.b	83,116,109,95,72,97,108,95,83,101,116,51,50,66,105,116,86,105,114,116,117,97,108,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 2468
	.data.w	.Ldw_str_begin+1571
	.data.b	146,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set32BitVirtualTimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitVirtualTimerValue
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Set32BitVirtualTimerValue
	.data.w	__ghs_eofn_Stm_Hal_Set32BitVirtualTimerValue-Stm_Hal_Set32BitVirtualTimerValue
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1048
	.data.b	0,5,2
	.data.w	Stm_Hal_Set32BitVirtualTimerValue
	.data.b	6
	.data.b	3
	.data.b	150,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2497
	.data.b	19
	.section	.debug_str		;off: 1605
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2498
	.data.w	.Ldw_str_begin+1605
	.data.b	146,2
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	1
	.data.b	80

	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1611
	.data.b	83,116,109,95,72,97,108,95,83,101,116,54,52,66,105,116,80,104,121,69,76,49,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2525
	.data.w	.Ldw_str_begin+1611
	.data.b	157,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set64BitPhyEL1TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitPhyEL1TimerCompareValue
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Set64BitPhyEL1TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitPhyEL1TimerCompareValue-Stm_Hal_Set64BitPhyEL1TimerCompareValue
	.data.b	1
	.data.w	.LDW56
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1075
	.data.b	0,5,2
	.data.w	Stm_Hal_Set64BitPhyEL1TimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	163,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2554
	.data.b	19
	.section	.debug_str		;off: 1651
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2555
	.data.w	.Ldw_str_begin+1651
	.data.b	157,2
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	1
	.data.b	80

	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW56

	.data.b	34
	.data.w	.LDW36
	.data.w	.LDW46

	.data.b	8
	.section	.debug_str		;off: 1657
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2589
	.data.w	.Ldw_str_begin+1657
	.data.b	164,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1667
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2604
	.data.w	.Ldw_str_begin+1667
	.data.b	164,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1677
	.data.b	83,116,109,95,72,97,108,95,83,101,116,54,52,66,105,116,80,104,121,69,76,50,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2622
	.data.w	.Ldw_str_begin+1677
	.data.b	169,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set64BitPhyEL2TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitPhyEL2TimerCompareValue
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Set64BitPhyEL2TimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitPhyEL2TimerCompareValue-Stm_Hal_Set64BitPhyEL2TimerCompareValue
	.data.b	1
	.data.w	.LDW07
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1102
	.data.b	0,5,2
	.data.w	Stm_Hal_Set64BitPhyEL2TimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	175,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2651
	.data.b	19
	.section	.debug_str		;off: 1717
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2652
	.data.w	.Ldw_str_begin+1717
	.data.b	169,2
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	1
	.data.b	80

	.data.b	34
	.data.w	.LDW76
	.data.w	.LDW07

	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	8
	.section	.debug_str		;off: 1723
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2686
	.data.w	.Ldw_str_begin+1723
	.data.b	176,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1733
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2701
	.data.w	.Ldw_str_begin+1733
	.data.b	176,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1743
	.data.b	83,116,109,95,72,97,108,95,83,101,116,54,52,66,105,116,86,105,114,116,117,97,108,84,105,109,101,114,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2719
	.data.w	.Ldw_str_begin+1743
	.data.b	181,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_Set64BitVirtualTimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitVirtualTimerCompareValue
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_Set64BitVirtualTimerCompareValue
	.data.w	__ghs_eofn_Stm_Hal_Set64BitVirtualTimerCompareValue-Stm_Hal_Set64BitVirtualTimerCompareValue
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1129
	.data.b	0,5,2
	.data.w	Stm_Hal_Set64BitVirtualTimerCompareValue
	.data.b	6
	.data.b	3
	.data.b	187,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2748
	.data.b	19
	.section	.debug_str		;off: 1784
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 2749
	.data.w	.Ldw_str_begin+1784
	.data.b	181,2
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+421
	.data.b	0
	.data.b	1
	.data.b	80

	.data.b	34
	.data.w	.LDW27
	.data.w	.LDW57

	.data.b	34
	.data.w	.LDW37
	.data.w	.LDW47

	.data.b	8
	.section	.debug_str		;off: 1790
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 2783
	.data.w	.Ldw_str_begin+1790
	.data.b	188,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1800
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 2798
	.data.w	.Ldw_str_begin+1800
	.data.b	188,2
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+409
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1810
	.data.b	83,116,109,95,72,97,108,95,69,110,97,98,108,101,80,104,121,69,76,49,84,105,109,101,114,0
	.section	.debug_info		;off: 2816
	.data.w	.Ldw_str_begin+1810
	.data.b	194,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_EnablePhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_EnablePhyEL1Timer
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
	.data.w	Stm_Hal_EnablePhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_EnablePhyEL1Timer-Stm_Hal_EnablePhyEL1Timer
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1156
	.data.b	0,5,2
	.data.w	Stm_Hal_EnablePhyEL1Timer
	.data.b	6
	.data.b	3
	.data.b	200,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2845
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	8
	.section	.debug_str		;off: 1836
	.data.b	117,67,78,84,80,67,84,76,0
	.section	.debug_info		;off: 2855
	.data.w	.Ldw_str_begin+1836
	.data.b	197,2
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1845
	.data.b	83,116,109,95,72,97,108,95,69,110,97,98,108,101,80,104,121,69,76,50,84,105,109,101,114,0
	.section	.debug_info		;off: 2872
	.data.w	.Ldw_str_begin+1845
	.data.b	210,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_EnablePhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_EnablePhyEL2Timer
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_EnablePhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_EnablePhyEL2Timer-Stm_Hal_EnablePhyEL2Timer
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1192
	.data.b	0,5,2
	.data.w	Stm_Hal_EnablePhyEL2Timer
	.data.b	6
	.data.b	3
	.data.b	216,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2901
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	8
	.section	.debug_str		;off: 1871
	.data.b	117,67,78,84,72,80,67,84,76,0
	.section	.debug_info		;off: 2911
	.data.w	.Ldw_str_begin+1871
	.data.b	213,2
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1881
	.data.b	83,116,109,95,72,97,108,95,69,110,97,98,108,101,86,105,114,116,117,97,108,84,105,109,101,114,0
	.section	.debug_info		;off: 2928
	.data.w	.Ldw_str_begin+1881
	.data.b	226,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_EnableVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_EnableVirtualTimer
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_EnableVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_EnableVirtualTimer-Stm_Hal_EnableVirtualTimer
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1228
	.data.b	0,5,2
	.data.w	Stm_Hal_EnableVirtualTimer
	.data.b	6
	.data.b	3
	.data.b	232,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2957
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	8
	.section	.debug_str		;off: 1908
	.data.b	117,67,78,84,86,67,84,76,0
	.section	.debug_info		;off: 2967
	.data.w	.Ldw_str_begin+1908
	.data.b	229,2
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1917
	.data.b	83,116,109,95,72,97,108,95,68,105,115,97,98,108,101,80,104,121,69,76,49,84,105,109,101,114,0
	.section	.debug_info		;off: 2984
	.data.w	.Ldw_str_begin+1917
	.data.b	242,2
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_DisablePhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_DisablePhyEL1Timer
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_DisablePhyEL1Timer
	.data.w	__ghs_eofn_Stm_Hal_DisablePhyEL1Timer-Stm_Hal_DisablePhyEL1Timer
	.data.b	1
	.data.w	.LDW78
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1264
	.data.b	0,5,2
	.data.w	Stm_Hal_DisablePhyEL1Timer
	.data.b	6
	.data.b	3
	.data.b	248,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3013
	.data.b	34
	.data.w	.LDW68
	.data.w	.LDW78

	.data.b	8
	.section	.debug_str		;off: 1944
	.data.b	117,67,78,84,80,67,84,76,0
	.section	.debug_info		;off: 3023
	.data.w	.Ldw_str_begin+1944
	.data.b	245,2
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1953
	.data.b	83,116,109,95,72,97,108,95,68,105,115,97,98,108,101,80,104,121,69,76,50,84,105,109,101,114,0
	.section	.debug_info		;off: 3040
	.data.w	.Ldw_str_begin+1953
	.data.b	130,3
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_DisablePhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_DisablePhyEL2Timer
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_DisablePhyEL2Timer
	.data.w	__ghs_eofn_Stm_Hal_DisablePhyEL2Timer-Stm_Hal_DisablePhyEL2Timer
	.data.b	1
	.data.w	.LDW09
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1300
	.data.b	0,5,2
	.data.w	Stm_Hal_DisablePhyEL2Timer
	.data.b	6
	.data.b	3
	.data.b	136,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3069
	.data.b	34
	.data.w	.LDW98
	.data.w	.LDW09

	.data.b	8
	.section	.debug_str		;off: 1980
	.data.b	117,67,78,84,72,80,67,84,76,0
	.section	.debug_info		;off: 3079
	.data.w	.Ldw_str_begin+1980
	.data.b	133,3
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1990
	.data.b	83,116,109,95,72,97,108,95,68,105,115,97,98,108,101,86,105,114,116,117,97,108,84,105,109,101,114,0
	.section	.debug_info		;off: 3096
	.data.w	.Ldw_str_begin+1990
	.data.b	146,3
	.data.b	6
	.data.b	1
	.data.w	Stm_Hal_DisableVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_DisableVirtualTimer
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_DisableVirtualTimer
	.data.w	__ghs_eofn_Stm_Hal_DisableVirtualTimer-Stm_Hal_DisableVirtualTimer
	.data.b	1
	.data.w	.LDW39
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1336
	.data.b	0,5,2
	.data.w	Stm_Hal_DisableVirtualTimer
	.data.b	6
	.data.b	3
	.data.b	152,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3125
	.data.b	34
	.data.w	.LDW29
	.data.w	.LDW39

	.data.b	8
	.section	.debug_str		;off: 2018
	.data.b	117,67,78,84,86,67,84,76,0
	.section	.debug_info		;off: 3135
	.data.w	.Ldw_str_begin+2018
	.data.b	149,3
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2027
	.data.b	83,116,109,95,72,97,108,95,71,101,116,80,104,121,69,76,49,84,105,109,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3152
	.data.w	.Ldw_str_begin+2027
	.data.b	162,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.w	Stm_Hal_GetPhyEL1TimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetPhyEL1TimerStatus
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

	.section	.debug_frame		;off: 720
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_GetPhyEL1TimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetPhyEL1TimerStatus-Stm_Hal_GetPhyEL1TimerStatus
	.data.b	1
	.data.w	.LDW69
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1372
	.data.b	0,5,2
	.data.w	Stm_Hal_GetPhyEL1TimerStatus
	.data.b	6
	.data.b	3
	.data.b	169,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3185
	.data.b	34
	.data.w	.LDW59
	.data.w	.LDW69

	.data.b	8
	.section	.debug_str		;off: 2056
	.data.b	117,67,78,84,80,67,84,76,0
	.section	.debug_info		;off: 3195
	.data.w	.Ldw_str_begin+2056
	.data.b	165,3
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 2065
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 3210
	.data.w	.Ldw_str_begin+2065
	.data.b	166,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+177
	.section	.debug_loc		;off: 177
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3228
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2072
	.data.b	83,116,109,95,72,97,108,95,71,101,116,80,104,121,69,76,50,84,105,109,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3231
	.data.w	.Ldw_str_begin+2072
	.data.b	187,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.w	Stm_Hal_GetPhyEL2TimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetPhyEL2TimerStatus
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

	.section	.debug_frame		;off: 744
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_GetPhyEL2TimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetPhyEL2TimerStatus-Stm_Hal_GetPhyEL2TimerStatus
	.data.b	1
	.data.w	.LDW99
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1407
	.data.b	0,5,2
	.data.w	Stm_Hal_GetPhyEL2TimerStatus
	.data.b	6
	.data.b	3
	.data.b	194,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3264
	.data.b	34
	.data.w	.LDW89
	.data.w	.LDW99

	.data.b	8
	.section	.debug_str		;off: 2101
	.data.b	117,67,78,84,72,80,67,84,76,0
	.section	.debug_info		;off: 3274
	.data.w	.Ldw_str_begin+2101
	.data.b	190,3
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 2111
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 3289
	.data.w	.Ldw_str_begin+2111
	.data.b	191,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+196
	.section	.debug_loc		;off: 196
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3307
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 2118
	.data.b	83,116,109,95,72,97,108,95,71,101,116,86,105,116,117,97,108,84,105,109,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3310
	.data.w	.Ldw_str_begin+2118
	.data.b	212,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.w	Stm_Hal_GetVitualTimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetVitualTimerStatus
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

	.section	.debug_frame		;off: 768
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Stm_Hal_GetVitualTimerStatus
	.data.w	__ghs_eofn_Stm_Hal_GetVitualTimerStatus-Stm_Hal_GetVitualTimerStatus
	.data.b	1
	.data.w	.LDW201
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1442
	.data.b	0,5,2
	.data.w	Stm_Hal_GetVitualTimerStatus
	.data.b	6
	.data.b	3
	.data.b	219,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3343
	.data.b	34
	.data.w	.LDW101
	.data.w	.LDW201

	.data.b	8
	.section	.debug_str		;off: 2147
	.data.b	117,67,78,84,86,67,84,76,0
	.section	.debug_info		;off: 3353
	.data.w	.Ldw_str_begin+2147
	.data.b	215,3
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 2156
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 3368
	.data.w	.Ldw_str_begin+2156
	.data.b	216,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+1208
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+215
	.section	.debug_loc		;off: 215
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3386
	.data.b	0

	.data.b	0

	.data.b	0

	.section	.debug_macinfo		;off: 0
	.data.b	1
	.data.b	0
	.data.b	95,95,103,104,115,95,95,32,49,0
	.data.b	1
	.data.b	0
	.data.b	84,72,65,54,95,84,72,65,54,52,49,50,32,49,0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	43
	.data.b	2
	.data.b	3
	.data.b	34
	.data.b	3
	.data.b	3
	.data.b	31
	.data.b	4
	.data.b	3
	.data.b	24
	.data.b	5
	.data.b	3
	.data.b	13
	.data.b	6
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
	.data.b	51
	.data.b	76,79,67,65,76,95,70,79,82,67,69,73,78,76,73,78,69,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,97,108,119,97,121,115,95,105,110,108,105,110,101,41,41,32,115,116,97,116,105,99,32,95,95,105,110
	.data.b	108,105,110,101,0
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
	.data.b	70
	.data.b	71,69,84,95,67,80,54,52,40,99,112,44,111,112,49,44,82,116,44,67,82,109,41,32,123,117,105,110,116,51,50,32,118,97,108,49,95,116,101,109,112,32,61,32,48,85,44,32,118,97,108,50,95,116,101,109,112,32,61,32
	.data.b	48,85,59,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,82,82,67,32,112,34,32,35,99,112,32,34,44,32,34,32,35,111,112,49,32,34,44,32,37,48,44,32,37,49,44,32,99,34,32,35,67,82,109,32,58
	.data.b	32,34,61,114,34,40,118,97,108,49,95,116,101,109,112,41,44,32,34,61,114,34,40,118,97,108,50,95,116,101,109,112,41,58,32,58,32,34,109,101,109,111,114,121,34,41,59,32,82,116,32,61,32,40,40,40,117,105,110,116
	.data.b	54,52,41,118,97,108,50,95,116,101,109,112,41,32,60,60,32,51,50,41,32,43,32,118,97,108,49,95,116,101,109,112,59,125,0
	.data.b	1
	.data.b	74
	.data.b	83,69,84,95,67,80,54,52,40,99,112,44,111,112,49,44,82,116,44,67,82,109,41,32,123,117,105,110,116,51,50,32,118,97,108,49,95,116,101,109,112,44,32,118,97,108,50,95,116,101,109,112,59,32,118,97,108,49,95,116
	.data.b	101,109,112,32,61,32,40,117,105,110,116,51,50,41,32,82,116,59,32,118,97,108,50,95,116,101,109,112,32,61,32,40,117,105,110,116,51,50,41,40,82,116,32,62,62,32,51,50,41,59,32,65,83,77,95,86,79,76,65,84
	.data.b	73,76,69,40,34,77,67,82,82,32,112,34,32,35,99,112,32,34,44,32,34,32,35,111,112,49,32,34,44,32,37,48,44,32,37,49,44,32,99,34,32,35,67,82,109,32,58,58,32,34,114,34,40,118,97,108,49,95,116,101
	.data.b	109,112,41,44,32,34,114,34,40,118,97,108,50,95,116,101,109,112,41,58,32,34,109,101,109,111,114,121,34,41,59,125,0
	.data.b	1
	.data.b	80
	.data.b	68,83,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,100,115,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	1
	.data.b	81
	.data.b	73,83,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,105,115,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	1
	.data.b	107
	.data.b	68,73,83,65,66,76,69,95,65,76,76,95,73,78,84,69,82,82,85,80,84,83,40,41,32,0
	.data.b	1
	.data.b	108
	.data.b	69,78,65,66,76,69,95,65,76,76,95,73,78,84,69,82,82,85,80,84,83,40,41,32,0
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	7
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	1
	.data.b	66
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	8
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
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	9
	.data.b	3
	.data.b	21
	.data.b	10
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	11
	.data.b	3
	.data.b	56
	.data.b	12
	.data.b	1
	.data.b	187,1
	.data.b	83,84,77,95,66,65,83,69,95,65,68,68,82,69,83,83,32,40,48,120,67,48,48,54,48,56,48,48,85,41,0
	.data.b	1
	.data.b	188,1
	.data.b	83,84,77,48,32,40,40,83,84,77,95,77,79,68,85,76,69,32,42,41,32,83,84,77,95,66,65,83,69,95,65,68,68,82,69,83,83,41,0
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	8
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
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	13
	.data.b	3
	.data.b	28
	.data.b	14
	.data.b	4
	.data.b	1
	.data.b	152,1
	.data.b	67,80,85,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	154,1
	.data.b	15
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
	.data.b	15
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	63
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	65
	.data.b	8
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
	.data.b	236,3
	.data.b	83,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	238,3
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 452
	.data.b	0
