	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682575..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_CheckDetErrors:
.LDW01:
	push	{r2,r4-r5,lr}
.LDW11:
	mov	r4,1
	cmp	r0,11
	bls	.L64
.L65:
	mov	r2,r1
	mov	r3,18
.L284:

.L285:

.L286:

	mov	r1,0
	mov	r0,121
.L300:

	bl	Det_ReportError
	b	.L66
.L64:
	ldr	r12,.L298
	ldr	r3,[r12,r2 lsl 2]
	ldr	r3,[r3]
	cmp	r3,1
	movne	r2,r1
	movne	r3,17
	bne	.L284
.L67:
	ldr	r3,.L299
	ldr	r5,[r3]
	ldr	r12,[r5,16]
	ldr	r3,[r12,r0 lsl 3]
	cmp	r2,r3
	movne	r2,r1
	movne	r3,225
	bne	.L286
.L70:
	ldr	r2,[r5,r2 lsl 2]
	add	r0,r12,r0 lsl 3
	ldrb	r0,[r0,4]
	ldr	r2,[r2,4]
	add	r0,r0,r0 lsl 2
	add	r0,r2,r0 lsl 4
	ldrb	r0,[r0,28]
	cmp	r0,1
	movhi	r2,r1
	movhi	r3,243
	bhi	.L285
.L73:
	mov	r4,0
.L66:
	mov	r0,r4
.LDW21:
.L302:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Pwm_CheckDetErrors:
	.endf	Pwm_CheckDetErrors
	.endf	Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ErrValue	r4	local

;ChannelNumber	r0	param
;ApiSid	r1	param
;CoreId	r2	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Pwm_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_ConfigPtr:	.space	4
	.endo	Pwm_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Pwm_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_CoreDriverStatusPtr:
	.data.w	Pwm_DriverStatusCore0
	.data.w	Pwm_DriverStatusCore1
	.space	8
	.endo	Pwm_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_CoreDriverStatusPtr
	.section ".ghcalltbl",""
	.align	4
.L301:	.data.w	.L300
	.endo	.L301
	.section ".ghrettbl",""
	.align	4
.L303:	.data.w	.L302
	.endo	.L303
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Pwm_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_DriverStatusCore0:	.space	4
	.endo	Pwm_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_DriverStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Pwm_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_DriverStatusCore1:	.space	4
	.endo	Pwm_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_DriverStatusCore1
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_CalculateDuty:
.LDW31:
.LDW41:
	cmp	r0,0
	cmpne	r0,r1
	movls	r1,r0
	mov	r0,r1
.LDW51:
.L419:

	ret	
__ghs_eofn_Pwm_CalculateDuty:
	.endf	Pwm_CalculateDuty
	.endf	Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;AbsoluteDuty	r1	local

;AbsolutePeriod	r0	param
;RelativeDuty	r1	param

	.section ".bss","awb"
.L380:
	.endo	.L380
	.section ".ghrettbl",""
.L420:	.data.w	.L419
	.endo	.L420
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_ChannelInit:
.LDW61:
	push	{r4-r6,lr}
	mov	r6,r0
	mov	r5,r2
.LDW71:
	rsb	r4,r1,r1 lsl 2
	add	r1,r0,32
	add	r0,r0,28
.L544:

	bl	Gtm_Pwm_Hal_InitChannel
	ldr	r1,.L543
	ldr	r1,[r1,r5 lsl 2]
	add	r2,r1,r4 lsl 2
	ldr	r1,[r6,12]
	str	r1,[r2,8]
	ldr	r3,[r6,16]
	cmp	r3,0
	cmpne	r1,0
	cmpne	r3,r1
	moveq	r1,1
	strbeq	r1,[r2]
.LDW81:
.L546:

	pop	{r4-r6,pc}
__ghs_eofn_Pwm_ChannelInit:
	.endf	Pwm_ChannelInit
	.endf	Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ChannelStatusPtr	r2	local
;SafetyFlag	r0	local

;ChannelConfigPtr	r6	param
;CoreIndex	r1	param
;CoreId	r5	param

	.section ".mcal_const_asil_d_unspecified","a"
Pwm_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_CoreChannelStatusPtr:
	.data.w	Pwm_ChannelStatusCore0
	.data.w	Pwm_ChannelStatusCore1
	.space	8
	.endo	Pwm_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_CoreChannelStatusPtr
	.section ".bss","awb"
.L497:
	.endo	.L497
	.section ".ghcalltbl",""
.L545:	.data.w	.L544
	.endo	.L545
	.section ".ghrettbl",""
.L547:	.data.w	.L546
	.endo	.L547
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Pwm_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_ChannelStatusCore0:	.space	96
	.endo	Pwm_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_ChannelStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
Pwm_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.::
Pwm_ChannelStatusCore1:	.space	48
	.endo	Pwm_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.endo	Pwm_ChannelStatusCore1
	.data
	.global	__caller.Gtm_Pwm_Hal_InitChannel.i.pp

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_InitDetCheck:
.LDW91:
	push	{r4,lr}
.LDW02:
	mov	r4,1
	movs	r2,r0
	moveq	r3,16
	beq	.L1030
.L550:
	ldr	r0,[r0,r1 lsl 2]
	movs	r2,r0
	bne	.L553
.L554:
	mov	r3,224
.L1030:

	mov	r1,r0
	b	.L1031
.L553:
	ldr	r0,.L298
	ldr	r0,[r0,r1 lsl 2]
	ldr	r0,[r0]
	cmp	r0,0
	beq	.L556
.L557:
	mov	r2,0
	mov	r3,20
	mov	r1,r2
.L1031:

	mov	r0,121
.L1041:

	bl	Det_ReportError
	b	.L552
.L556:
	mov	r4,r0
.L552:
	mov	r0,r4
.LDW12:
.L1043:

	pop	{r4,pc}
__ghs_eofn_Pwm_InitDetCheck:
	.endf	Pwm_InitDetCheck
	.endf	Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ErrValue	r4	local

;ConfigPtr	r0	param
;CoreId	r1	param

	.section ".bss","awb"
.L952:
	.endo	.L952
	.section ".ghcalltbl",""
.L1042:	.data.w	.L1041
	.endo	.L1042
	.section ".ghrettbl",""
.L1044:	.data.w	.L1043
	.endo	.L1044
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_SetDutyCycleDetCheck:
.LDW22:
	push	{r4-r6,lr}
	mov	r6,r1
.LDW32:
	mov	r5,r2
	mov	r4,r0
	mov	r1,2
.L1237:

	bl	Pwm_CheckDetErrors
	cmp	r0,0
.L1239:

	popne	{r4-r6,pc}
	ldr	r2,.L299
	ldr	r1,[r2]
	ldr	r2,[r1,r5 lsl 2]
	ldr	r1,[r1,16]
	add	r1,r1,r4 lsl 3
	ldrb	r1,[r1,4]
	ldr	r2,[r2,4]
	add	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 4
	ldrb	r1,[r1,28]
	cmp	r1,1
	bne	.L1049
	cmp	r6,1<<24
	b	.L1229
.L1049:
	cmp	r1,0
.L1241:

	popne	{r4-r6,pc}
.L1055:
	cmp	r6,1<<16
.L1229:

.L1243:

	poplo	{r4-r6,pc}
	mov	r3,243
	mov	r2,2
	mov	r1,r0
	mov	r0,121
.L1245:

	bl	Det_ReportError
	mov	r0,1
.LDW42:
.L1247:

	pop	{r4-r6,pc}
__ghs_eofn_Pwm_SetDutyCycleDetCheck:
	.endf	Pwm_SetDutyCycleDetCheck
	.endf	Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ErrValue	r0	local

;ChannelNumber	r4	param
;DutyCycleValue	r6	param
;CoreId	r5	param

	.section ".ghcalltbl",""
.L1238:	.data.w	.L1237
	.endo	.L1238
	.section ".ghrettbl",""
.L1240:	.data.w	.L1239
	.endo	.L1240
.L1242:	.data.w	.L1241
	.endo	.L1242
.L1244:	.data.w	.L1243
	.endo	.L1244
	.section ".ghcalltbl",""
.L1246:	.data.w	.L1245
	.endo	.L1246
	.section ".ghrettbl",""
.L1248:	.data.w	.L1247
	.endo	.L1248
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_SetPeriodAndDutyDetCheck:
.LDW52:
	push	{r2,r4-r7,lr}
	mov	r6,r1
	mov	r7,r2
	mov	r4,r3
.LDW62:
	mov	r2,r3
	mov	r5,r0
	mov	r1,3
.L1540:

	bl	Pwm_CheckDetErrors
	cmp	r0,0
.L1542:

	popne	{r2,r4-r7,pc}
	ldr	r2,.L299
	ldr	r1,[r2]
	ldr	r2,[r1,r4 lsl 2]
	ldr	r1,[r1,16]
	add	r1,r1,r5 lsl 3
	ldrb	r1,[r1,4]
	ldr	r2,[r2,4]
	add	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 4
	ldr	r2,[r1,8]
	cmp	r2,0
	movne	r3,19
	bne	.L1330
	ldrb	r1,[r1,28]
	cmp	r1,0
	bne	.L1256
.L1257:
	cmp	r6,1<<16
	cmplo	r7,1<<16
.L1530:

	bhs	.L1271
.L1544:

	pop	{r2,r4-r7,pc}
.L1256:
	cmp	r1,1
.L1546:

	popne	{r2,r4-r7,pc}
	cmp	r6,1<<24
	cmplo	r7,1<<24
	b	.L1530
.L1271:
	mov	r3,243
.L1330:
	mov	r2,3
	mov	r1,r0
	mov	r0,121
.L1548:

	bl	Det_ReportError
	mov	r0,1
.LDW72:
.L1550:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Pwm_SetPeriodAndDutyDetCheck:
	.endf	Pwm_SetPeriodAndDutyDetCheck
	.endf	Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ErrValue	r0	local

;ChannelNumber	r5	param
;PeriodValue	r6	param
;DutyCycleValue	r7	param
;CoreId	r4	param

	.section ".ghcalltbl",""
.L1541:	.data.w	.L1540
	.endo	.L1541
	.section ".ghrettbl",""
.L1543:	.data.w	.L1542
	.endo	.L1543
.L1545:	.data.w	.L1544
	.endo	.L1545
.L1547:	.data.w	.L1546
	.endo	.L1547
	.section ".ghcalltbl",""
.L1549:	.data.w	.L1548
	.endo	.L1549
	.section ".ghrettbl",""
.L1551:	.data.w	.L1550
	.endo	.L1551
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_EnDisableNotificationDetCheck:
.LDW82:
	push	{r4-r6,lr}
.LDW92:
	mov	r5,r2
	mov	r6,r1
	mov	r4,r0
.L1690:

	bl	Pwm_CheckDetErrors
	ldr	r2,.L299
	ldr	r1,[r2]
	ldr	r2,[r1,16]
	cmp	r0,0
	add	r2,r2,r4 lsl 3
.L1692:

	popne	{r4-r6,pc}
	ldr	r0,[r1,r5 lsl 2]
	ldrb	r3,[r2,4]
	ldr	r0,[r0,4]
	add	r3,r3,r3 lsl 2
	add	r0,r0,r3 lsl 4
	ldr	r1,[r0,24]
	cmp	r1,0
	bne	.L1556
	mov	r2,r6
	mov	r3,244
	mov	r0,121
.L1694:

	bl	Det_ReportError
	mov	r0,1
.L1696:

	pop	{r4-r6,pc}
.L1556:
	mov	r0,0
.LDW03:
.L1698:

	pop	{r4-r6,pc}
__ghs_eofn_Pwm_EnDisableNotificationDetCheck:
	.endf	Pwm_EnDisableNotificationDetCheck
	.endf	Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;ErrValue	r0	local
;ChIndexInCore	r3	local

;ChannelNumber	r4	param
;ApiSid	r6	param
;CoreId	r5	param

	.section ".ghcalltbl",""
.L1691:	.data.w	.L1690
	.endo	.L1691
	.section ".ghrettbl",""
.L1693:	.data.w	.L1692
	.endo	.L1693
	.section ".ghcalltbl",""
.L1695:	.data.w	.L1694
	.endo	.L1695
	.section ".ghrettbl",""
.L1697:	.data.w	.L1696
	.endo	.L1697
.L1699:	.data.w	.L1698
	.endo	.L1699
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
	.global	Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.:
Pwm_Is0Or100IrqHandle:
.LDW13:
	ldr	r12,[r0,4]
.LDW23:
	mov	r3,r0
	mov	r0,0
	cmp	r12,0
.L1924:

	reteq	
	ldrb	r3,[r3]
	cmp	r3,0
	bne	.L1704
	cmp	r2,0
	cmpne	r2,r1
	cmpne	r1,0
	moveq	r0,1
.L1926:

	ret	
.L1704:
	cmp	r2,0
	cmpne	r1,0
	cmpne	r2,r1
	movne	r0,2
.L1700:
.LDW33:
.L1928:

	ret	
__ghs_eofn_Pwm_Is0Or100IrqHandle:
	.endf	Pwm_Is0Or100IrqHandle
	.endf	Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
;HandleFlag	r0	local

;ChannelStatusPtr	r3	param
;CurrentPeriod	r1	param
;AbsDutyCycle	r2	param

	.section ".bss","awb"
.L1834:
	.endo	.L1834
	.section ".ghrettbl",""
.L1925:	.data.w	.L1924
	.endo	.L1925
.L1927:	.data.w	.L1926
	.endo	.L1927
.L1929:	.data.w	.L1928
	.endo	.L1929
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
__callee.Pwm_GetVersionInfo.v.p::
	.size	__callee.Pwm_GetVersionInfo.v.p,0
Pwm_GetVersionInfo::
.LDW43:
.LDW53:
	movs	r1,r0
	moveq	r3,21
	moveq	r2,8
	moveq	r0,121
.L2011:

	beq	Det_ReportError
.L1932:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,121
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW63:
.L2013:

	ret	
__ghs_eofn_Pwm_GetVersionInfo::
	.endf	Pwm_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L1973:
	.endo	.L1973
	.section ".ghtailcalltbl",""
	.align	4
.L2012:	.data.w	.L2011
	.endo	.L2012
	.section ".ghrettbl",""
.L2014:	.data.w	.L2013
	.endo	.L2014
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
__callee.Pwm_Init.v.p::
	.size	__callee.Pwm_Init.v.p,0
Pwm_Init::
.LDW73:
	push	{r4-r8,lr}
.LDW83:
	mov	r6,1
	b	.L2298

.L298:	.data.w	Pwm_CoreDriverStatusPtr
	.endo	.L298

.L299:	.data.w	Pwm_ConfigPtr
	.endo	.L299

.L543:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L543

.L2298:

;line1238
..lin.3629a77c..1dbb5c0c.0_1::
.LDWlin1:
..gh.beginasm.10:
	.endo	..gh.beginasm.10
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.11:
	.endo	..gh.endasm.11

;line1242
..lin.3629a77c..1dbb5c0c.0_2::
.LDWlin2:
	mov	r1,r4
	mov	r5,r0
.L2301:

	bl	Pwm_InitDetCheck
	cmp	r0,0
	ldreq	r0,.L2299
	streq	r5,[r0]
	ldreq	r8,[r5,r4 lsl 2]
	moveq	r5,0
	ldreq	r8,[r8,4]
	beq	.L2026
.L2303:

	pop	{r4-r8,pc}
.L2025:
	mov	r0,5
.L2305:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2034
	add	r3,r5,r5 lsl 2
	mov	r2,r4
	mov	r1,r5
	add	r0,r8,r3 lsl 4
.L2307:

	bl	Pwm_ChannelInit
	and	r6,r6,r0
	mov	r0,5
.L2309:

	bl	Mcal_ReleaseLock
	cmp	r6,1
	bne	.L2034
	add	r5,r5,r6
	uxtb	r5,r5
.L2026:
	ldr	r0,.L2299
	ldr	r0,[r0]
	ldr	r0,[r0,r4 lsl 2]
	ldrb	r0,[r0]
	cmp	r5,r0
	blo	.L2025
	ldr	r0,.L2300
	ldr	r0,[r0,r4 lsl 2]
	str	r6,[r0]
.L2311:

	pop	{r4-r8,pc}
.L2034:
	mov	r2,0
	mov	r3,226
	mov	r0,121
	mov	r1,r2
.L2313:

	bl	Det_ReportRuntimeError
.LDW93:
.L2315:

	pop	{r4-r8,pc}
__ghs_eofn_Pwm_Init::
	.endf	Pwm_Init
;CoreId	r4	local
;ChannelConfigPtr	r8	local
;ChIndexInCore	r5	local
;SafetyFlag	r6	local

;ConfigPtr	r5	param

	.section ".ghcalltbl",""
.L2302:	.data.w	.L2301
	.endo	.L2302
	.section ".ghrettbl",""
.L2304:	.data.w	.L2303
	.endo	.L2304
	.section ".ghcalltbl",""
.L2306:	.data.w	.L2305
	.endo	.L2306
.L2308:	.data.w	.L2307
	.endo	.L2308
.L2310:	.data.w	.L2309
	.endo	.L2310
	.section ".ghrettbl",""
.L2312:	.data.w	.L2311
	.endo	.L2312
	.section ".ghcalltbl",""
.L2314:	.data.w	.L2313
	.endo	.L2314
	.section ".ghrettbl",""
.L2316:	.data.w	.L2315
	.endo	.L2316
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Mcal_GetLock.i.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
__callee.Pwm_DeInit.v.v::
	.size	__callee.Pwm_DeInit.v.v,0
Pwm_DeInit::
.LDW04:
	push	{r4-fp,lr}
	sub	sp,sp,12
.LDW14:
	mov	r4,1
	b	.L2623

.L2299:	.data.w	Pwm_ConfigPtr
	.endo	.L2299

.L2300:	.data.w	Pwm_CoreDriverStatusPtr
	.endo	.L2300

.L2623:

;line1362
..lin.3629a77c..6da44fb5.0_3::
.LDWlin3:
..gh.beginasm.13:
	.endo	..gh.beginasm.13
 mrc p15, 0, r1, c0, c0, 5
 and r7, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r7, r7, r1         

..gh.endasm.14:
	.endo	..gh.endasm.14

;line1365
..lin.3629a77c..6da44fb5.0_4::
.LDWlin4:
	ldr	r1,.L2624
	ldr	r10,[r1,r7 lsl 2]
	ldr	r0,[r10]
	cmp	r0,1
	beq	.L2323
	mov	r3,17
	mov	r2,r4
	mov	r1,0
	mov	r0,121
.L2627:

	bl	Det_ReportError
	b	.L2317
.L2323:
	ldr	r9,.L2625
	ldr	r1,[r9]
	ldr	r1,[r1,r7 lsl 2]
	ldr	r1,[r1,4]
	mov	r8,0
	str	r1,[sp]
.L2329:
	ldr	r0,[r9]
	ldr	r0,[r0,r7 lsl 2]
	ldrb	r0,[r0]
	mov	fp,0
	cmp	r8,r0
	strhs	fp,[r10]
	bhs	.L2317
	ldr	r2,.L2626
	ldr	r1,[r2,r7 lsl 2]
	rsb	r0,r8,r8 lsl 2
	add	r5,r1,r0 lsl 2
	add	r0,r8,r8 lsl 2
	ldr	r1,[sp]
	lsl	r6,r0,4
	add	r0,r6,r1
	ldr	r2,[r0,4]
	str	r2,[sp,4]
.L2629:

	bl	SchM_Enter_Pwm_DeInit
	mov	r0,5
.L2631:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2330
	ldr	r0,[r9]
	ldr	r0,[r0,r7 lsl 2]
	ldr	r0,[r0,4]
	ldr	r1,[sp,4]
	add	r0,r6,r0
	add	r0,r0,28
.L2633:

	bl	Gtm_Pwm_Hal_DeinitChannel
	and	r4,r4,r0
	mov	r0,5
.L2635:

	bl	Mcal_ReleaseLock
	b	.L2332
.L2330:
	mov	r4,fp
.L2332:
	mov	r0,fp
	stmib	r5,{r0,fp}
	strb	fp,[r5]
.L2637:

	bl	SchM_Exit_Pwm_DeInit
	cmp	r4,1
	addeq	r8,r8,r4
	uxtbeq	r8,r8
	beq	.L2329
	mov	r3,226
	mov	r2,1
	mov	r1,fp
	mov	r0,121
.L2639:

	bl	Det_ReportRuntimeError
.L2317:
.LDW24:
	add	sp,sp,12
.L2641:

	pop	{r4-fp,pc}
__ghs_eofn_Pwm_DeInit::
	.endf	Pwm_DeInit
;CoreId	r7	local
;ChIndexInCore	r8	local
;ChannelConfigPtr	[sp]	local
;IdleSignalLevel	[sp,4]	local
;ChannelStatusPtr	r5	local
;SafetyFlag	r4	local

	.section ".ghcalltbl",""
.L2628:	.data.w	.L2627
	.endo	.L2628
.L2630:	.data.w	.L2629
	.endo	.L2630
.L2632:	.data.w	.L2631
	.endo	.L2632
.L2634:	.data.w	.L2633
	.endo	.L2634
.L2636:	.data.w	.L2635
	.endo	.L2636
.L2638:	.data.w	.L2637
	.endo	.L2638
.L2640:	.data.w	.L2639
	.endo	.L2640
	.section ".ghrettbl",""
.L2642:	.data.w	.L2641
	.endo	.L2642
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_DeInit.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Gtm_Pwm_Hal_DeinitChannel.i.pi

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Pwm_DeInit.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
__callee.Pwm_SetDutyCycle.v.ii::
	.size	__callee.Pwm_SetDutyCycle.v.ii,0
Pwm_SetDutyCycle::
.LDW34:
	push	{r4-fp,lr}
	sub	sp,sp,20
	mov	r8,r1
.LDW44:
	mov	r5,1
	b	.L3171

.L2624:	.data.w	Pwm_CoreDriverStatusPtr
	.endo	.L2624

.L2625:	.data.w	Pwm_ConfigPtr
	.endo	.L2625

.L2626:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L2626

.L3171:

;line1490
..lin.3629a77c..6045783a.0_5::
.LDWlin5:
..gh.beginasm.16:
	.endo	..gh.beginasm.16
 mrc p15, 0, r1, c0, c0, 5
 and r6, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r6, r6, r1         

..gh.endasm.17:
	.endo	..gh.endasm.17

;line1493
..lin.3629a77c..6045783a.0_6::
.LDWlin6:
	mov	r2,r6
	mov	r1,r8
	mov	r4,r0
.L3174:

	bl	Pwm_SetDutyCycleDetCheck
	cmp	r0,0
	bne	.L2643
	ldr	r9,.L3172
	ldr	r2,[r9]
	ldr	r1,[r2,16]
	ldr	r12,.L3173
	add	r0,r1,r4 lsl 3
	ldrb	r1,[r0,4]
	ldr	r3,[r12,r6 lsl 2]
	rsb	r0,r1,r1 lsl 2
	add	fp,r3,r0 lsl 2
	ldr	r0,[r2,r6 lsl 2]
	add	r1,r1,r1 lsl 2
	lsl	r4,r1,4
	ldr	r0,[r0,4]
	str	r4,[sp,8]
	add	r4,r4,r0
	ldr	r0,[r4,8]
	str	r4,[sp,4]
	str	r0,[sp,12]
	cmp	r0,0
	ldreq	r7,[fp,8]
	ldrne	r7,[r4,12]
	mov	r1,r8
	mov	r0,r7
.L3176:

	bl	Pwm_CalculateDuty
	mov	r10,r0
	ldr	r0,[r4,52]
	cmp	r0,0
	moveq	r4,r7
	moveq	r8,r10
	beq	.L2656
	ldr	r0,[sp,4]
	ldrb	r0,[r0,28]
	cmp	r0,0
	movweq	r8,0xffff
	mvnne	r8,255<<24
	cmp	r10,0
	moveq	r4,r8
	moveq	r8,r10
	beq	.L2671
	cmp	r10,r7
	moveq	r4,0
	beq	.L2656
	ldr	r0,[sp,12]
	cmp	r0,2
	subne	r0,r7,r10
	lsrne	r4,r0,1
	subne	r8,r7,r4
	bne	.L2657
	ldr	r4,[r4,20]
	mov	r0,r7
	add	r1,r10,r4
.L3178:

	bl	__umoddiv32_hard
	mov	r8,r0
.L2657:
	cmp	r8,2
	cmplo	r8,r4
	bhs	.L2656
.L2671:
	mov	r3,243
	mov	r2,2
	mov	r1,0
	mov	r0,121
.L3180:

	bl	Det_ReportRuntimeError
.L2656:
.L3182:

	bl	SchM_Enter_Pwm_SetDutyCycle
	mov	r2,r10
	mov	r1,r7
	mov	r0,fp
.L3184:

	bl	Pwm_Is0Or100IrqHandle
	mov	r7,r0
	cmp	r0,1
	bne	.L2673
	ldr	r0,[r9]
	ldr	r0,[r0,r6 lsl 2]
	ldr	r1,[sp,8]
	ldr	r0,[r0,4]
	mov	r2,0
	add	r0,r1,r0
	mov	r1,3
	add	r0,r0,28
.L3186:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r5,r5,r0
	mov	r0,1
	strb	r0,[fp]
.L2673:
	ldr	r0,[r9]
	ldr	r0,[r0,r6 lsl 2]
	ldr	r10,[sp,8]
	ldr	r0,[r0,4]
	mov	r2,r8
	add	r1,r10,r0
	ldrb	r3,[r1,76]
	add	r0,r1,28
	mov	r1,r4
.L3188:

	bl	Gtm_Pwm_Hal_SetPeriodDutyCycle
	and	r5,r5,r0
	cmp	r7,2
	bne	.L2675
	ldr	r0,[r9]
	ldr	r0,[r0,r6 lsl 2]
	ldr	r0,[r0,4]
	mov	r2,1
	ldr	r1,[fp,4]
	add	r0,r10,r0
	add	r0,r0,28
.L3190:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r5,r5,r0
	mov	r0,0
	strb	r0,[fp]
.L2675:
.L3192:

	bl	SchM_Exit_Pwm_SetDutyCycle
	cmp	r5,1
	movne	r3,226
	movne	r2,2
	movne	r1,0
	movne	r0,121
.L3194:

	blne	Det_ReportRuntimeError
.L2643:
.LDW54:
	add	sp,sp,20
.L3196:

	pop	{r4-fp,pc}
__ghs_eofn_Pwm_SetDutyCycle::
	.endf	Pwm_SetDutyCycle
;CurrentPeriod	r7	local
;AbsDutyCycle	r10	local
;ChIndexInCore	r1	local
;ChannelStatusPtr	fp	local
;CoreId	r6	local
;ChannelConfigPtr	r4	local
;HwCompareZero	r4	local
;HwCompareOne	r8	local
;HandleInfo	r7	local
;SafetyFlag	r5	local
;MaxCounter	r8	local

;ChannelNumber	r4	param
;DutyCycle	r8	param

	.section ".ghcalltbl",""
.L3175:	.data.w	.L3174
	.endo	.L3175
.L3177:	.data.w	.L3176
	.endo	.L3177
.L3179:	.data.w	.L3178
	.endo	.L3179
.L3181:	.data.w	.L3180
	.endo	.L3181
.L3183:	.data.w	.L3182
	.endo	.L3183
.L3185:	.data.w	.L3184
	.endo	.L3185
.L3187:	.data.w	.L3186
	.endo	.L3187
.L3189:	.data.w	.L3188
	.endo	.L3189
.L3191:	.data.w	.L3190
	.endo	.L3191
.L3193:	.data.w	.L3192
	.endo	.L3193
.L3195:	.data.w	.L3194
	.endo	.L3195
	.section ".ghrettbl",""
.L3197:	.data.w	.L3196
	.endo	.L3197
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_SetDutyCycle.v.v

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Pwm_Hal_SetPeriodDutyCycle.i.piii

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.SchM_Enter_Pwm_SetDutyCycle.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
__callee.Pwm_SetPeriodAndDuty.v.iii::
	.size	__callee.Pwm_SetPeriodAndDuty.v.iii,0
Pwm_SetPeriodAndDuty::
.LDW64:
	push	{r2,r4-fp,lr}
	mov	r8,r1
.LDW74:
	mov	r4,1
	b	.L3366

.L3172:	.data.w	Pwm_ConfigPtr
	.endo	.L3172

.L3173:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L3173

.L3366:

;line1667
..lin.3629a77c..47b78c60.0_7::
.LDWlin7:
..gh.beginasm.19:
	.endo	..gh.beginasm.19
 mrc p15, 0, r1, c0, c0, 5
 and r6, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r6, r6, r1         

..gh.endasm.20:
	.endo	..gh.endasm.20

;line1671
..lin.3629a77c..47b78c60.0_8::
.LDWlin8:
	mov	r3,r6
	mov	r10,r2
	mov	r1,r8
	mov	r7,r0
.L3369:

	bl	Pwm_SetPeriodAndDutyDetCheck
	cmp	r0,0
.L3371:

	popne	{r2,r4-fp,pc}
	ldr	r5,.L3367
	ldr	r1,[r5]
	ldr	r1,[r1,16]
	ldr	r2,.L3368
	add	r0,r1,r7 lsl 3
	ldrb	r9,[r0,4]
	ldr	r1,[r2,r6 lsl 2]
	rsb	r0,r9,r9 lsl 2
	add	r7,r1,r0 lsl 2
.L3373:

	bl	SchM_Enter_Pwm_SetPeriodAndDuty
	str	r8,[r7,8]
	mov	r1,r10
	mov	r0,r8
.L3375:

	bl	Pwm_CalculateDuty
	mov	fp,r0
	mov	r2,r0
	mov	r1,r8
	mov	r0,r7
.L3377:

	bl	Pwm_Is0Or100IrqHandle
	mov	r10,r0
	cmp	r0,1
	bne	.L3206
	ldr	r1,[r5]
	ldr	r1,[r1,r6 lsl 2]
	ldr	r1,[r1,4]
	add	r0,r9,r9 lsl 2
	mov	r2,0
	add	r0,r1,r0 lsl 4
	mov	r1,3
	add	r0,r0,28
.L3379:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r4,r4,r0
	mov	r0,1
	strb	r0,[r7]
.L3206:
	ldr	r0,[r5]
	ldr	r0,[r0,r6 lsl 2]
	add	r9,r9,r9 lsl 2
	ldr	r0,[r0,4]
	lsl	r9,r9,4
	mov	r2,fp
	add	r0,r9,r0
	mov	r1,r8
	ldrb	r3,[r0,76]
	add	r0,r0,28
.L3381:

	bl	Gtm_Pwm_Hal_SetPeriodDutyCycle
	and	r4,r4,r0
	cmp	r10,2
	bne	.L3208
	ldr	r0,[r5]
	ldr	r0,[r0,r6 lsl 2]
	ldr	r0,[r0,4]
	mov	r2,1
	ldr	r1,[r7,4]
	add	r0,r9,r0
	add	r0,r0,28
.L3383:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r4,r4,r0
	mov	r0,0
	strb	r0,[r7]
.L3208:
.L3385:

	bl	SchM_Exit_Pwm_SetPeriodAndDuty
	cmp	r4,1
	movne	r3,226
	movne	r2,3
	movne	r1,0
	movne	r0,121
.L3387:

	blne	Det_ReportRuntimeError
.LDW84:
.L3389:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Pwm_SetPeriodAndDuty::
	.endf	Pwm_SetPeriodAndDuty
;CoreId	r6	local
;AbsDutyCycle	fp	local
;ChIndexInCore	r9	local
;ChannelStatusPtr	r7	local
;HandleInfo	r10	local
;SafetyFlag	r4	local

;ChannelNumber	r7	param
;Period	r8	param
;DutyCycle	r10	param

	.section ".ghcalltbl",""
.L3370:	.data.w	.L3369
	.endo	.L3370
	.section ".ghrettbl",""
.L3372:	.data.w	.L3371
	.endo	.L3372
	.section ".ghcalltbl",""
.L3374:	.data.w	.L3373
	.endo	.L3374
.L3376:	.data.w	.L3375
	.endo	.L3376
.L3378:	.data.w	.L3377
	.endo	.L3378
.L3380:	.data.w	.L3379
	.endo	.L3380
.L3382:	.data.w	.L3381
	.endo	.L3382
.L3384:	.data.w	.L3383
	.endo	.L3384
.L3386:	.data.w	.L3385
	.endo	.L3386
.L3388:	.data.w	.L3387
	.endo	.L3388
	.section ".ghrettbl",""
.L3390:	.data.w	.L3389
	.endo	.L3390
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_SetPeriodAndDuty.v.v

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Pwm_Hal_SetPeriodDutyCycle.i.piii

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.SchM_Enter_Pwm_SetPeriodAndDuty.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
__callee.Pwm_SetOutputToIdle.v.i::
	.size	__callee.Pwm_SetOutputToIdle.v.i,0
Pwm_SetOutputToIdle::
.LDW94:
	push	{r2,r4-r9,lr}
.LDW05:
	mov	r6,1
	b	.L3524

.L3367:	.data.w	Pwm_ConfigPtr
	.endo	.L3367

.L3368:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L3368

.L3524:

;line1792
..lin.3629a77c..fb4af976.0_9::
.LDWlin9:
..gh.beginasm.22:
	.endo	..gh.beginasm.22
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.23:
	.endo	..gh.endasm.23

;line1795
..lin.3629a77c..fb4af976.0_10::
.LDWlin10:
	mov	r2,r4
	mov	r5,r0
	mov	r1,4
.L3527:

	bl	Pwm_CheckDetErrors
	cmp	r0,0
.L3529:

	popne	{r2,r4-r9,pc}
	ldr	r7,.L3525
	ldr	r1,[r7]
	ldr	r1,[r1,16]
	add	r0,r1,r5 lsl 3
	ldrb	r5,[r0,4]
.L3531:

	bl	SchM_Enter_Pwm_SetOutputToIdle
	ldr	r2,.L3526
	lsl	r3,r5,2
	ldr	r1,[r2,r4 lsl 2]
	sub	r0,r3,r5
	add	r9,r1,r0 lsl 2
	ldr	r0,[r9,4]
	cmp	r0,0
	beq	.L3399
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	add	r8,r5,r3
	mov	r2,0
	mov	r1,3
	add	r0,r0,r8 lsl 4
	add	r0,r0,28
.L3533:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r6,r6,r0
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	mov	r1,3
	add	r0,r0,r8 lsl 4
	add	r0,r0,28
.L3535:

	bl	Gtm_Pwm_Hal_ClearInterruptStatus
	mov	r0,1
	strb	r0,[r9]
.L3399:
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	add	r1,r5,r5 lsl 2
	add	r0,r0,r1 lsl 4
	ldr	r1,[r0,4]
	add	r0,r0,28
.L3537:

	bl	Gtm_Pwm_Hal_SetIdleLevel
	and	r6,r6,r0
.L3539:

	bl	SchM_Exit_Pwm_SetOutputToIdle
	cmp	r6,1
	movne	r3,226
	movne	r2,4
	movne	r1,0
	movne	r0,121
.L3541:

	blne	Det_ReportRuntimeError
.LDW15:
.L3543:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Pwm_SetOutputToIdle::
	.endf	Pwm_SetOutputToIdle
;CoreId	r4	local
;ChIndexInCore	r5	local
;ChannelStatusPtr	r9	local
;SafetyFlag	r6	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L3528:	.data.w	.L3527
	.endo	.L3528
	.section ".ghrettbl",""
.L3530:	.data.w	.L3529
	.endo	.L3530
	.section ".ghcalltbl",""
.L3532:	.data.w	.L3531
	.endo	.L3532
.L3534:	.data.w	.L3533
	.endo	.L3534
.L3536:	.data.w	.L3535
	.endo	.L3536
.L3538:	.data.w	.L3537
	.endo	.L3538
.L3540:	.data.w	.L3539
	.endo	.L3540
.L3542:	.data.w	.L3541
	.endo	.L3542
	.section ".ghrettbl",""
.L3544:	.data.w	.L3543
	.endo	.L3544
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_SetOutputToIdle.v.v

	.global	__caller.Gtm_Pwm_Hal_SetIdleLevel.i.pi

	.global	__caller.Gtm_Pwm_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.SchM_Enter_Pwm_SetOutputToIdle.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.24:
	.endo	..gh.f.a.1.e.24
__callee.Pwm_GetOutputState.i.i::
	.size	__callee.Pwm_GetOutputState.i.i,0
Pwm_GetOutputState::
.LDW25:
	push	{r4-r6,lr}
.LDW35:
	mov	r4,0
	b	.L3637

.L3525:	.data.w	Pwm_ConfigPtr
	.endo	.L3525

.L3526:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L3526

.L3637:

;line1888
..lin.3629a77c..2945f4ea.0_11::
.LDWlin11:
..gh.beginasm.25:
	.endo	..gh.beginasm.25
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.26:
	.endo	..gh.endasm.26

	mov	r5,r2
;line1891
..lin.3629a77c..2945f4ea.0_12::
.LDWlin12:
	mov	r6,r0
	mov	r1,5
.L3639:

	bl	Pwm_CheckDetErrors
	cmp	r0,0
	bne	.L3551
	ldr	r0,.L3638
	ldr	r1,[r0]
	ldr	r2,[r1,16]
	add	r0,r2,r6 lsl 3
	ldrb	r0,[r0,4]
	add	r2,r0,r0 lsl 2
	ldr	r0,[r1,r5 lsl 2]
	ldr	r0,[r0,4]
	add	r0,r0,r2 lsl 4
	add	r0,r0,28
.L3641:

	bl	Gtm_Pwm_Hal_GetOutputLevel
	mov	r4,r0
.L3551:
	mov	r0,r4
.LDW45:
.L3643:

	pop	{r4-r6,pc}
__ghs_eofn_Pwm_GetOutputState::
	.endf	Pwm_GetOutputState
;OutputLevel	r4	local
;CoreId	r5	local

;ChannelNumber	r6	param

	.section ".ghcalltbl",""
.L3640:	.data.w	.L3639
	.endo	.L3640
.L3642:	.data.w	.L3641
	.endo	.L3642
	.section ".ghrettbl",""
.L3644:	.data.w	.L3643
	.endo	.L3644
	.data
	.global	__caller.Gtm_Pwm_Hal_GetOutputLevel.i.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.27:
	.endo	..gh.f.a.1.e.27
__callee.Pwm_DisableNotification.v.i::
	.size	__callee.Pwm_DisableNotification.v.i,0
Pwm_DisableNotification::
.LDW55:
	push	{r4-r8,lr}
.LDW65:
	b	.L3746

.L3638:	.data.w	Pwm_ConfigPtr
	.endo	.L3638

.L3746:

;line1949
..lin.3629a77c..5b595d13.0_13::
.LDWlin13:
..gh.beginasm.28:
	.endo	..gh.beginasm.28
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.29:
	.endo	..gh.endasm.29

;line1953
..lin.3629a77c..5b595d13.0_14::
.LDWlin14:
	mov	r2,r4
	mov	r5,r0
	mov	r1,6
.L3749:

	bl	Pwm_EnDisableNotificationDetCheck
	cmp	r0,0
.L3751:

	popne	{r4-r8,pc}
	ldr	r6,.L3747
	ldr	r1,[r6]
	ldr	r1,[r1,16]
	add	r0,r1,r5 lsl 3
	ldrb	r5,[r0,4]
.L3753:

	bl	SchM_Enter_Pwm_DisableNotification
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	add	r7,r5,r5 lsl 2
	mov	r2,0
	mov	r1,3
	add	r0,r0,r7 lsl 4
	add	r0,r0,28
.L3755:

	bl	Gtm_Pwm_Hal_SetInterrupt
	mov	r8,r0
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	mov	r1,3
	add	r0,r0,r7 lsl 4
	add	r0,r0,28
.L3757:

	bl	Gtm_Pwm_Hal_ClearInterruptStatus
	ldr	r0,.L3748
	rsb	r1,r5,r5 lsl 2
	ldr	r0,[r0,r4 lsl 2]
	add	r0,r0,r1 lsl 2
	mov	r1,0
	str	r1,[r0,4]
.L3759:

	bl	SchM_Exit_Pwm_DisableNotification
	cmp	r8,1
	movne	r3,226
	movne	r2,6
	movne	r1,0
	movne	r0,121
.L3761:

	blne	Det_ReportRuntimeError
.LDW75:
.L3763:

	pop	{r4-r8,pc}
__ghs_eofn_Pwm_DisableNotification::
	.endf	Pwm_DisableNotification
;ChIndexInCore	r5	local
;CoreId	r4	local
;SafetyFlag	r8	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L3750:	.data.w	.L3749
	.endo	.L3750
	.section ".ghrettbl",""
.L3752:	.data.w	.L3751
	.endo	.L3752
	.section ".ghcalltbl",""
.L3754:	.data.w	.L3753
	.endo	.L3754
.L3756:	.data.w	.L3755
	.endo	.L3756
.L3758:	.data.w	.L3757
	.endo	.L3758
.L3760:	.data.w	.L3759
	.endo	.L3760
.L3762:	.data.w	.L3761
	.endo	.L3762
	.section ".ghrettbl",""
.L3764:	.data.w	.L3763
	.endo	.L3764
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_DisableNotification.v.v

	.global	__caller.Gtm_Pwm_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.SchM_Enter_Pwm_DisableNotification.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.30:
	.endo	..gh.f.a.1.e.30
__callee.Pwm_EnableNotification.v.ii::
	.size	__callee.Pwm_EnableNotification.v.ii,0
Pwm_EnableNotification::
.LDW85:
	push	{r2,r4-r9,lr}
	mov	r9,r1
.LDW95:
	mov	r6,1
	b	.L3892

.L3747:	.data.w	Pwm_ConfigPtr
	.endo	.L3747

.L3748:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L3748

.L3892:

;line2037
..lin.3629a77c..126b6e26.0_15::
.LDWlin15:
..gh.beginasm.31:
	.endo	..gh.beginasm.31
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.32:
	.endo	..gh.endasm.32

;line2041
..lin.3629a77c..126b6e26.0_16::
.LDWlin16:
	mov	r2,r4
	mov	r5,r0
	mov	r1,7
.L3895:

	bl	Pwm_EnDisableNotificationDetCheck
	cmp	r0,0
.L3897:

	popne	{r2,r4-r9,pc}
	ldr	r7,.L3893
	ldr	r1,[r7]
	ldr	r1,[r1,16]
	ldr	r2,.L3894
	add	r0,r1,r5 lsl 3
	ldrb	r5,[r0,4]
	ldr	r1,[r2,r4 lsl 2]
	rsb	r0,r5,r5 lsl 2
	add	r8,r1,r0 lsl 2
.L3899:

	bl	SchM_Enter_Pwm_EnableNotification
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	add	r2,r5,r5 lsl 2
	ldr	r0,[r0,4]
	lsl	r5,r2,4
	mov	r1,3
	add	r0,r5,r0
	add	r0,r0,28
.L3901:

	bl	Gtm_Pwm_Hal_ClearInterruptStatus
	ldrb	r0,[r8]
	cmp	r0,0
	bne	.L3773
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	mov	r1,r9
	mov	r2,r6
	add	r0,r5,r0
	add	r0,r0,28
.L3903:

	bl	Gtm_Pwm_Hal_SetInterrupt
	and	r6,r6,r0
.L3773:
	str	r9,[r8,4]
.L3905:

	bl	SchM_Exit_Pwm_EnableNotification
	cmp	r6,1
	movne	r3,226
	movne	r2,7
	movne	r1,0
	movne	r0,121
.L3907:

	blne	Det_ReportRuntimeError
.LDW06:
.L3909:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Pwm_EnableNotification::
	.endf	Pwm_EnableNotification
;CoreId	r4	local
;ChIndexInCore	r5	local
;ChannelStatusPtr	r8	local
;SafetyFlag	r6	local

;ChannelNumber	r5	param
;Notification	r9	param

	.section ".ghcalltbl",""
.L3896:	.data.w	.L3895
	.endo	.L3896
	.section ".ghrettbl",""
.L3898:	.data.w	.L3897
	.endo	.L3898
	.section ".ghcalltbl",""
.L3900:	.data.w	.L3899
	.endo	.L3900
.L3902:	.data.w	.L3901
	.endo	.L3902
.L3904:	.data.w	.L3903
	.endo	.L3904
.L3906:	.data.w	.L3905
	.endo	.L3906
.L3908:	.data.w	.L3907
	.endo	.L3908
	.section ".ghrettbl",""
.L3910:	.data.w	.L3909
	.endo	.L3910
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Pwm_EnableNotification.v.v

	.global	__caller.Gtm_Pwm_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Pwm_Hal_ClearInterruptStatus.v.pi

	.global	__caller.SchM_Enter_Pwm_EnableNotification.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Pwm_ConfigPtr - Pwm_ConfigPtr) +0 == 0
..gh.f.a.1.e.33:
	.endo	..gh.f.a.1.e.33
__callee.Pwm_DutyPeriod_ISRHandler.v.iii::
	.size	__callee.Pwm_DutyPeriod_ISRHandler.v.iii,0
Pwm_DutyPeriod_ISRHandler::
.LDW16:
	push	{r4-r7,lr}
	sub	sp,sp,12
	mov	r5,r1
	ldr	r6,.L3893
.LDW26:
	b	.L4211

.L3893:	.data.w	Pwm_ConfigPtr
	.endo	.L3893

.L3894:	.data.w	Pwm_CoreChannelStatusPtr
	.endo	.L3894

.L4211:

;line2131
..lin.3629a77c..f003bd6c.0_17::
.LDWlin17:
..gh.beginasm.34:
	.endo	..gh.beginasm.34
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.35:
	.endo	..gh.endasm.35

;line2133
..lin.3629a77c..f003bd6c.0_18::
.LDWlin18:
	ldr	r12,[r6]
	cmp	r12,0
	ldrne	r3,.L4212
	ldrne	r1,[r3,r4 lsl 2]
	cmpne	r1,0
	beq	.L3911
	ldr	r1,[r1]
	cmp	r1,1
	bne	.L3911
	cmp	r0,0
	moveq	r1,16
	movne	r1,8
	add	r3,r12,r0 lsl 2
	ldr	r7,[r3,20]
	mla	r3,r5,r1,r2
	uxtb	r1,r3
	ldrb	r1,[r7,r1]
	cmp	r1,255
	beq	.L3911
	ldr	r3,[r12,16]
	lsl	r1,r1,3
	ldr	r12,[r3,r1]
	cmp	r4,r12
	bne	.L3927
	strb	r0,[sp,4]
	strb	r5,[sp,5]
	add	r0,r3,r1
	strb	r2,[sp,7]
	mov	r1,1
	ldrb	r5,[r0,4]
	add	r0,sp,4
.L4213:

	bl	Gtm_Pwm_Hal_GetInterruptEnableStatus
	mov	r7,r0
	add	r0,sp,4
	mov	r1,1
.L4215:

	bl	Gtm_Pwm_Hal_GetInterruptStatus
	and	r1,r0,r7
	add	r0,sp,4
	cmp	r1,1
	bne	.L3929
.L4217:

	bl	Gtm_Pwm_Hal_ClearInterruptStatus
	ldr	r1,[r6]
	ldr	r1,[r1,r4 lsl 2]
	add	r0,r5,r5 lsl 2
	ldr	r1,[r1,4]
	add	r0,r1,r0 lsl 4
	b	.L4199
.L3929:
	mov	r1,2
.L4219:

	bl	Gtm_Pwm_Hal_GetInterruptEnableStatus
	mov	r7,r0
	add	r0,sp,4
	mov	r1,2
.L4221:

	bl	Gtm_Pwm_Hal_GetInterruptStatus
	and	r0,r0,r7
	cmp	r0,1
	bne	.L3911
.L3933:
	add	r0,sp,4
	mov	r1,2
.L4223:

	bl	Gtm_Pwm_Hal_ClearInterruptStatus
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	add	r2,r5,r5 lsl 2
	ldr	r0,[r0,4]
	add	r0,r0,r2 lsl 4
.L4199:

	ldr	r0,[r0,24]
.L4225:

	blx	r0
	b	.L3911
.L3927:
	mov	r3,225
	mov	r2,15
	mov	r1,0
	mov	r0,121
.L4227:

	bl	Det_ReportError
.L3911:
.LDW36:
	add	sp,sp,12
.L4229:

	pop	{r4-r7,pc}
__ghs_eofn_Pwm_DutyPeriod_ISRHandler::
	.endf	Pwm_DutyPeriod_ISRHandler
;CoreId	r4	local
;ChIndexInCore	r5	local
;IntEnStatus	r7	local
;HWChannelObject	[sp,4]	local
;LogicChannelIndex	r1	local

;Module	r0	param
;ModuleIndex	r5	param
;Channel	r2	param

	.section ".ghcalltbl",""
.L4214:	.data.w	.L4213
	.endo	.L4214
.L4216:	.data.w	.L4215
	.endo	.L4216
.L4218:	.data.w	.L4217
	.endo	.L4218
.L4220:	.data.w	.L4219
	.endo	.L4220
.L4222:	.data.w	.L4221
	.endo	.L4222
.L4224:	.data.w	.L4223
	.endo	.L4224
.L4226:	.data.w	.L4225
	.endo	.L4226
.L4228:	.data.w	.L4227
	.endo	.L4228
	.section ".ghrettbl",""
.L4230:	.data.w	.L4229
	.endo	.L4230
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Gtm_Pwm_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Gtm_Pwm_Hal_GetInterruptStatus.i.pi

	.global	__caller.Gtm_Pwm_Hal_GetInterruptEnableStatus.i.pi

	.global	__caller.Gtm_Pwm_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Gtm_Pwm_Hal_GetInterruptStatus.i.pi

	.global	__caller.Gtm_Pwm_Hal_GetInterruptEnableStatus.i.pi

	.section ".mcal_text_asil_d","ax"

.L4212:	.data.w	Pwm_CoreDriverStatusPtr
	.endo	.L4212

;Pwm_ChannelStatusCore0	Pwm_ChannelStatusCore0	static
;Pwm_DriverStatusCore0	Pwm_DriverStatusCore0	static
;Pwm_ChannelStatusCore1	Pwm_ChannelStatusCore1	static
;Pwm_DriverStatusCore1	Pwm_DriverStatusCore1	static
;Pwm_CoreChannelStatusPtr	Pwm_CoreChannelStatusPtr	static
;Pwm_CoreDriverStatusPtr	Pwm_CoreDriverStatusPtr	static
;Pwm_ConfigPtr	Pwm_ConfigPtr	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682575..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	215,25,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,115,114,99,47,80,119,109,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 32
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+32
	.section	.debug_str		;off: 176
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+176
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
	.data.b	88,12,0,0
	.data.b	2,0
	.data.b	226,6,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,115,114,99,47,80,119,109,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,80,119,109,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,112,119,109,92,103,116,109,95,112,119,109,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,116,111,109,92,103,116,109,95,116,111,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,71,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,97,116,111,109,92,103,116,109,95,97,116,111,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,80,119,109,95,77,101,109,77,97,112,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,80,119,109,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,68,101,116,92,105,110,99,108,117,100,101,92,68,101,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,80,119,109,46,104,0
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
	.section	.debug_str		;off: 198
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 36
	.data.w	.Ldw_str_begin+198
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
	.section	.debug_str		;off: 212
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+212
	.data.b	7
	.data.b	4

	.data.b	74
	.data.w	.Ldw_begin+2311
	.data.b	1

	.section	.debug_abbrev		;off: 30
	.data.b	74
	.data.b	21
	.data.b	1
	.data.b	73,16
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 55
	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 226
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 57
	.data.w	.Ldw_str_begin+226
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.section	.debug_abbrev		;off: 39
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 75
	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1021
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2928

	.section	.debug_abbrev		;off: 48
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 112
	.data.b	53
	.data.w	.Ldw_begin+107

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 117
	.data.b	47
	.data.w	.Ldw_begin+112

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+117
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2721

	.data.b	47
	.data.w	.Ldw_begin+3110

	.data.b	53
	.data.w	.Ldw_begin+152

	.data.b	47
	.data.w	.Ldw_begin+157

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+162
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2463
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2463
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2721

	.data.b	53
	.data.w	.Ldw_begin+267

	.data.b	47
	.data.w	.Ldw_begin+272

	.data.b	74
	.data.w	.Ldw_begin+997
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+277
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1021

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 62
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 314
	.data.b	23
	.data.w	.Ldw_begin+2323
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+112
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+307
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+307
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1144

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+357
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+157
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2463
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2463
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2504
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2439
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2554
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 487
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 494
	.data.w	.Ldw_str_begin+260
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 273
	.data.b	105,110,116,0
	.section	.debug_info		;off: 501
	.data.w	.Ldw_str_begin+273
	.data.b	5
	.data.b	4

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+507

	.data.b	47
	.data.w	.Ldw_begin+3038

	.data.b	53
	.data.w	.Ldw_begin+515

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+520

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 532
	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	3

	.section	.debug_abbrev		;off: 80
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 540
	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2983

	.data.b	53
	.data.w	.Ldw_begin+541

	.data.b	47
	.data.w	.Ldw_begin+997

	.data.b	53
	.data.w	.Ldw_begin+551

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+556

	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	96
	.data.w	.Ldw_begin+2721

	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	48
	.data.w	.Ldw_begin+2721

	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+147

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+609

	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2595

	.data.b	47
	.data.w	.Ldw_begin+630

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+635

	.data.b	56
	.data.w	.Ldw_begin+500
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1462

	.data.b	53
	.data.w	.Ldw_begin+656

	.data.b	47
	.data.w	.Ldw_begin+661

	.data.b	47
	.data.w	.Ldw_begin+2242

	.data.b	53
	.data.w	.Ldw_begin+671

	.data.b	47
	.data.w	.Ldw_begin+676

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+681
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1253
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1253
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1253
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1774
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+985
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1774
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1021
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1774
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+985
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1021
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1021
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+985
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1021
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+666
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1774
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2427
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2427
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1009
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1045
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1009
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+997
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

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 986
	.data.w	.Ldw_str_begin+277
	.data.b	51
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+35

	.section	.debug_abbrev		;off: 93
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 997
	.data.b	45
	.section	.debug_str		;off: 285
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 998
	.data.w	.Ldw_str_begin+285
	.data.b	56
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+35

	.data.b	45
	.section	.debug_str		;off: 291
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1010
	.data.w	.Ldw_str_begin+291
	.data.b	60
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+486

	.data.b	45
	.section	.debug_str		;off: 298
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1022
	.data.w	.Ldw_str_begin+298
	.data.b	64
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 305
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1034
	.data.w	.Ldw_str_begin+305
	.data.b	68
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1046
	.data.w	.Ldw_str_begin+312
	.data.b	39
	.data.b	15
	.data.b	3
	.data.w	.Ldw_begin+997

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 108
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 1063
	.data.b	40
	.section	.debug_str		;off: 327
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1064
	.data.w	.Ldw_str_begin+327
	.data.b	63
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1009
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 123
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

	.section	.debug_info		;off: 1079
	.data.b	40
	.section	.debug_str		;off: 336
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1080
	.data.w	.Ldw_str_begin+336
	.data.b	64
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1009
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 345
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1096
	.data.w	.Ldw_str_begin+345
	.data.b	65
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1112
	.data.w	.Ldw_str_begin+362
	.data.b	66
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1128
	.data.w	.Ldw_str_begin+379
	.data.b	67
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 396
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1145
	.data.w	.Ldw_str_begin+396
	.data.b	68
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+1057

	.data.b	52
	.section	.debug_str		;off: 416
	.data.b	0
	.section	.debug_info		;off: 1157
	.data.w	.Ldw_str_begin+416
	.data.b	150,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 142
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

	.section	.debug_info		;off: 1167
	.data.b	51
	.section	.debug_str		;off: 417
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,76,69,86,69,76,0
	.section	.debug_info		;off: 1168
	.data.w	.Ldw_str_begin+417
	.data.b	151,1
	.data.b	5
	.data.b	13
	.data.b	0

	.section	.debug_abbrev		;off: 159
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 1177
	.data.b	51
	.section	.debug_str		;off: 435
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,0
	.section	.debug_info		;off: 1178
	.data.w	.Ldw_str_begin+435
	.data.b	152,1
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 453
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,78,79,84,73,70,89,0
	.section	.debug_info		;off: 1188
	.data.w	.Ldw_str_begin+453
	.data.b	153,1
	.data.b	5
	.data.b	13
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 477
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,83,73,78,71,76,69,80,85,76,83,69,0
	.section	.debug_info		;off: 1198
	.data.w	.Ldw_str_begin+477
	.data.b	154,1
	.data.b	5
	.data.b	13
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 501
	.data.b	71,116,109,95,73,114,113,77,111,100,101,0
	.section	.debug_info		;off: 1209
	.data.w	.Ldw_str_begin+501
	.data.b	155,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+1156

	.data.b	52
	.section	.debug_str		;off: 513
	.data.b	0
	.section	.debug_info		;off: 1222
	.data.w	.Ldw_str_begin+513
	.data.b	159,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 514
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,76,79,87,0
	.section	.debug_info		;off: 1233
	.data.w	.Ldw_str_begin+514
	.data.b	160,1
	.data.b	5
	.data.b	13
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 534
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,72,73,71,72,0
	.section	.debug_info		;off: 1243
	.data.w	.Ldw_str_begin+534
	.data.b	161,1
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 555
	.data.b	71,116,109,95,83,105,103,110,97,108,83,116,97,116,101,0
	.section	.debug_info		;off: 1254
	.data.w	.Ldw_str_begin+555
	.data.b	162,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+1221

	.data.b	52
	.section	.debug_str		;off: 571
	.data.b	0
	.section	.debug_info		;off: 1267
	.data.w	.Ldw_str_begin+571
	.data.b	166,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 572
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1278
	.data.w	.Ldw_str_begin+572
	.data.b	167,1
	.data.b	5
	.data.b	13
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 592
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,48,0
	.section	.debug_info		;off: 1288
	.data.w	.Ldw_str_begin+592
	.data.b	168,1
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 612
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,49,0
	.section	.debug_info		;off: 1298
	.data.w	.Ldw_str_begin+612
	.data.b	169,1
	.data.b	5
	.data.b	13
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 632
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,65,76,76,0
	.section	.debug_info		;off: 1308
	.data.w	.Ldw_str_begin+632
	.data.b	170,1
	.data.b	5
	.data.b	13
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 651
	.data.b	71,116,109,95,79,109,95,73,114,113,84,121,112,101,0
	.section	.debug_info		;off: 1319
	.data.w	.Ldw_str_begin+651
	.data.b	171,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+1266

	.data.b	52
	.section	.debug_str		;off: 666
	.data.b	0
	.section	.debug_info		;off: 1332
	.data.w	.Ldw_str_begin+666
	.data.b	175,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 667
	.data.b	71,84,77,95,79,85,84,80,85,84,95,77,79,68,85,76,69,95,84,79,77,0
	.section	.debug_info		;off: 1343
	.data.w	.Ldw_str_begin+667
	.data.b	176,1
	.data.b	5
	.data.b	13
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 689
	.data.b	71,84,77,95,79,85,84,80,85,84,95,77,79,68,85,76,69,95,65,84,79,77,0
	.section	.debug_info		;off: 1353
	.data.w	.Ldw_str_begin+689
	.data.b	177,1
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 712
	.data.b	71,84,77,95,79,85,84,80,85,84,95,77,79,68,85,76,69,95,84,73,79,0
	.section	.debug_info		;off: 1363
	.data.w	.Ldw_str_begin+712
	.data.b	178,1
	.data.b	5
	.data.b	13
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 734
	.data.b	71,116,109,95,79,117,116,112,117,116,95,77,111,100,117,108,101,0
	.section	.debug_info		;off: 1374
	.data.w	.Ldw_str_begin+734
	.data.b	180,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+1331

	.data.b	71
	.data.b	185,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 752
	.data.b	109,111,100,117,108,101,0
	.section	.debug_info		;off: 1394
	.data.w	.Ldw_str_begin+752
	.data.b	186,1
	.data.b	14
	.data.b	13
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 759
	.data.b	109,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 1411
	.data.w	.Ldw_str_begin+759
	.data.b	187,1
	.data.b	14
	.data.b	13
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 771
	.data.b	103,114,111,117,112,0
	.section	.debug_info		;off: 1428
	.data.w	.Ldw_str_begin+771
	.data.b	188,1
	.data.b	14
	.data.b	13
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 777
	.data.b	99,104,97,110,110,101,108,0
	.section	.debug_info		;off: 1445
	.data.w	.Ldw_str_begin+777
	.data.b	189,1
	.data.b	14
	.data.b	13
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 785
	.data.b	71,116,109,95,79,117,116,112,117,116,95,68,114,105,118,101,114,0
	.section	.debug_info		;off: 1463
	.data.w	.Ldw_str_begin+785
	.data.b	190,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+1386

	.data.b	52
	.section	.debug_str		;off: 803
	.data.b	0
	.section	.debug_info		;off: 1476
	.data.w	.Ldw_str_begin+803
	.data.b	89
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 804
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,48,0
	.section	.debug_info		;off: 1486
	.data.w	.Ldw_str_begin+804
	.data.b	90
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 828
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,49,0
	.section	.debug_info		;off: 1495
	.data.w	.Ldw_str_begin+828
	.data.b	91
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 852
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,50,0
	.section	.debug_info		;off: 1504
	.data.w	.Ldw_str_begin+852
	.data.b	92
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 876
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,51,0
	.section	.debug_info		;off: 1513
	.data.w	.Ldw_str_begin+876
	.data.b	93
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 900
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,52,0
	.section	.debug_info		;off: 1522
	.data.w	.Ldw_str_begin+900
	.data.b	94
	.data.b	5
	.data.b	10
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 924
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,48,0
	.section	.debug_info		;off: 1531
	.data.w	.Ldw_str_begin+924
	.data.b	95
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 946
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,49,0
	.section	.debug_info		;off: 1540
	.data.w	.Ldw_str_begin+946
	.data.b	96
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 968
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,50,0
	.section	.debug_info		;off: 1549
	.data.w	.Ldw_str_begin+968
	.data.b	97
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 990
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,51,0
	.section	.debug_info		;off: 1558
	.data.w	.Ldw_str_begin+990
	.data.b	98
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1012
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,52,0
	.section	.debug_info		;off: 1567
	.data.w	.Ldw_str_begin+1012
	.data.b	99
	.data.b	5
	.data.b	10
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1034
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,53,0
	.section	.debug_info		;off: 1576
	.data.w	.Ldw_str_begin+1034
	.data.b	100
	.data.b	5
	.data.b	10
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 1056
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,54,0
	.section	.debug_info		;off: 1585
	.data.w	.Ldw_str_begin+1056
	.data.b	101
	.data.b	5
	.data.b	10
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 1078
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,55,0
	.section	.debug_info		;off: 1594
	.data.w	.Ldw_str_begin+1078
	.data.b	102
	.data.b	5
	.data.b	10
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 1100
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,83,84,79,80,0
	.section	.debug_info		;off: 1603
	.data.w	.Ldw_str_begin+1100
	.data.b	105
	.data.b	5
	.data.b	10
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1119
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,84,82,73,71,79,85,84,0
	.section	.debug_info		;off: 1612
	.data.w	.Ldw_str_begin+1119
	.data.b	106
	.data.b	5
	.data.b	10
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 1141
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,69,88,84,84,82,73,71,73,78,0
	.section	.debug_info		;off: 1621
	.data.w	.Ldw_str_begin+1141
	.data.b	107
	.data.b	5
	.data.b	10
	.data.b	14

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1165
	.data.b	71,116,109,95,80,119,109,95,67,108,111,99,107,0
	.section	.debug_info		;off: 1631
	.data.w	.Ldw_str_begin+1165
	.data.b	108
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1475

	.data.b	52
	.section	.debug_str		;off: 1179
	.data.b	0
	.section	.debug_info		;off: 1643
	.data.w	.Ldw_str_begin+1179
	.data.b	112
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1180
	.data.b	71,84,77,95,80,87,77,95,82,69,83,69,84,69,86,69,78,84,95,79,78,67,77,48,0
	.section	.debug_info		;off: 1653
	.data.w	.Ldw_str_begin+1180
	.data.b	113
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1205
	.data.b	71,84,77,95,80,87,77,95,82,69,83,69,84,69,86,69,78,84,95,79,78,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 1662
	.data.w	.Ldw_str_begin+1205
	.data.b	114
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1234
	.data.b	71,116,109,95,80,119,109,95,82,101,115,101,116,69,118,101,110,116,0
	.section	.debug_info		;off: 1672
	.data.w	.Ldw_str_begin+1234
	.data.b	115
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1642

	.data.b	52
	.section	.debug_str		;off: 1253
	.data.b	0
	.section	.debug_info		;off: 1684
	.data.w	.Ldw_str_begin+1253
	.data.b	119
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1254
	.data.b	71,84,77,95,80,87,77,95,84,82,73,71,79,85,84,95,70,79,82,87,65,82,68,0
	.section	.debug_info		;off: 1694
	.data.w	.Ldw_str_begin+1254
	.data.b	120
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1278
	.data.b	71,84,77,95,80,87,77,95,84,82,73,71,79,85,84,95,71,69,78,69,82,65,84,69,0
	.section	.debug_info		;off: 1703
	.data.w	.Ldw_str_begin+1278
	.data.b	121
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1303
	.data.b	71,116,109,95,80,119,109,95,84,114,105,103,79,117,116,0
	.section	.debug_info		;off: 1713
	.data.w	.Ldw_str_begin+1303
	.data.b	122
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1683

	.data.b	52
	.section	.debug_str		;off: 1319
	.data.b	0
	.section	.debug_info		;off: 1725
	.data.w	.Ldw_str_begin+1319
	.data.b	126
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1320
	.data.b	71,84,77,95,80,87,77,95,73,82,81,69,68,71,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1735
	.data.w	.Ldw_str_begin+1320
	.data.b	127
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1341
	.data.b	71,84,77,95,80,87,77,95,73,82,81,69,68,71,69,95,82,73,83,69,0
	.section	.debug_info		;off: 1744
	.data.w	.Ldw_str_begin+1341
	.data.b	128,1
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1362
	.data.b	71,84,77,95,80,87,77,95,73,82,81,69,68,71,69,95,70,65,76,76,0
	.section	.debug_info		;off: 1754
	.data.w	.Ldw_str_begin+1362
	.data.b	129,1
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1383
	.data.b	71,84,77,95,80,87,77,95,73,82,81,69,68,71,69,95,65,76,76,0
	.section	.debug_info		;off: 1764
	.data.w	.Ldw_str_begin+1383
	.data.b	130,1
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1403
	.data.b	71,116,109,95,80,119,109,95,73,114,113,69,100,103,101,0
	.section	.debug_info		;off: 1775
	.data.w	.Ldw_str_begin+1403
	.data.b	131,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1724

	.data.b	52
	.section	.debug_str		;off: 1419
	.data.b	0
	.section	.debug_info		;off: 1788
	.data.w	.Ldw_str_begin+1419
	.data.b	135,1
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1420
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,0
	.section	.debug_info		;off: 1799
	.data.w	.Ldw_str_begin+1420
	.data.b	136,1
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1441
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,49,0
	.section	.debug_info		;off: 1809
	.data.w	.Ldw_str_begin+1441
	.data.b	137,1
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1468
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,50,0
	.section	.debug_info		;off: 1819
	.data.w	.Ldw_str_begin+1468
	.data.b	138,1
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1495
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,51,0
	.section	.debug_info		;off: 1829
	.data.w	.Ldw_str_begin+1495
	.data.b	139,1
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1522
	.data.b	71,116,109,95,80,119,109,95,67,111,117,110,116,77,111,100,101,0
	.section	.debug_info		;off: 1840
	.data.w	.Ldw_str_begin+1522
	.data.b	140,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1787

	.data.b	71
	.data.b	149,1
	.data.b	1
	.data.b	10
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1540
	.data.b	105,115,82,105,115,101,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 1860
	.data.w	.Ldw_str_begin+1540
	.data.b	150,1
	.data.b	20
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1554
	.data.b	105,115,70,97,108,108,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 1877
	.data.w	.Ldw_str_begin+1554
	.data.b	151,1
	.data.b	20
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1568
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 1894
	.data.w	.Ldw_str_begin+1568
	.data.b	152,1
	.data.b	20
	.data.b	10
	.data.w	.Ldw_begin+1208
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1573
	.data.b	71,116,109,95,80,119,109,95,67,111,110,102,105,103,73,114,113,0
	.section	.debug_info		;off: 1912
	.data.w	.Ldw_str_begin+1573
	.data.b	153,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1852

	.data.b	71
	.data.b	157,1
	.data.b	1
	.data.b	10
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1591
	.data.b	105,115,72,114,101,115,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 1932
	.data.w	.Ldw_str_begin+1591
	.data.b	158,1
	.data.b	17
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1605
	.data.b	104,114,101,115,80,101,114,105,111,100,0
	.section	.debug_info		;off: 1949
	.data.w	.Ldw_str_begin+1605
	.data.b	159,1
	.data.b	17
	.data.b	10
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1616
	.data.b	104,114,101,115,80,117,108,115,101,87,105,100,116,104,0
	.section	.debug_info		;off: 1966
	.data.w	.Ldw_str_begin+1616
	.data.b	160,1
	.data.b	17
	.data.b	10
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1631
	.data.b	71,116,109,95,80,119,109,95,72,114,101,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1984
	.data.w	.Ldw_str_begin+1631
	.data.b	161,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1924

	.data.b	71
	.data.b	166,1
	.data.b	1
	.data.b	10
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1650
	.data.b	99,108,107,0
	.section	.debug_info		;off: 2004
	.data.w	.Ldw_str_begin+1650
	.data.b	167,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1630
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1654
	.data.b	112,101,114,105,111,100,0
	.section	.debug_info		;off: 2021
	.data.w	.Ldw_str_begin+1654
	.data.b	168,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1661
	.data.b	100,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 2038
	.data.w	.Ldw_str_begin+1661
	.data.b	169,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1671
	.data.b	112,104,97,115,101,0
	.section	.debug_info		;off: 2055
	.data.w	.Ldw_str_begin+1671
	.data.b	170,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1677
	.data.b	104,114,101,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2072
	.data.w	.Ldw_str_begin+1677
	.data.b	171,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1983
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1688
	.data.b	114,101,115,101,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2089
	.data.w	.Ldw_str_begin+1688
	.data.b	172,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1671
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1700
	.data.b	115,105,103,110,97,108,76,101,118,101,108,0
	.section	.debug_info		;off: 2106
	.data.w	.Ldw_str_begin+1700
	.data.b	173,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1253
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1712
	.data.b	105,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 2123
	.data.w	.Ldw_str_begin+1712
	.data.b	174,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1911
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1722
	.data.b	116,114,105,103,79,117,116,0
	.section	.debug_info		;off: 2140
	.data.w	.Ldw_str_begin+1722
	.data.b	175,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1712
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1730
	.data.b	99,111,117,110,116,77,111,100,101,0
	.section	.debug_info		;off: 2157
	.data.w	.Ldw_str_begin+1730
	.data.b	176,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+1839
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1740
	.data.b	105,115,83,121,110,99,85,112,100,97,116,101,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 2174
	.data.w	.Ldw_str_begin+1740
	.data.b	177,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1760
	.data.b	105,115,67,104,97,110,110,101,108,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2191
	.data.w	.Ldw_str_begin+1760
	.data.b	178,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	45
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1776
	.data.b	105,115,79,117,116,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2208
	.data.w	.Ldw_str_begin+1776
	.data.b	179,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	46
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1791
	.data.b	105,115,73,109,109,101,100,105,97,116,101,0
	.section	.debug_info		;off: 2225
	.data.w	.Ldw_str_begin+1791
	.data.b	180,1
	.data.b	30
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	47
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1803
	.data.b	71,116,109,95,80,119,109,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2243
	.data.w	.Ldw_str_begin+1803
	.data.b	181,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+1996

	.data.b	52
	.section	.debug_str		;off: 1818
	.data.b	0
	.section	.debug_info		;off: 2256
	.data.w	.Ldw_str_begin+1818
	.data.b	36
	.data.b	1
	.data.b	24
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1819
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 2266
	.data.w	.Ldw_str_begin+1819
	.data.b	37
	.data.b	5
	.data.b	24
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1836
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 2275
	.data.w	.Ldw_str_begin+1836
	.data.b	38
	.data.b	5
	.data.b	24
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1853
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 2284
	.data.w	.Ldw_str_begin+1853
	.data.b	39
	.data.b	5
	.data.b	24
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1870
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 2293
	.data.w	.Ldw_str_begin+1870
	.data.b	40
	.data.b	5
	.data.b	24
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1887
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 2302
	.data.w	.Ldw_str_begin+1887
	.data.b	41
	.data.b	5
	.data.b	24
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1904
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 2312
	.data.w	.Ldw_str_begin+1904
	.data.b	42
	.data.b	3
	.data.b	24
	.data.w	.Ldw_begin+2255

	.data.b	45
	.section	.debug_str		;off: 1916
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 2324
	.data.w	.Ldw_str_begin+1916
	.data.b	32
	.data.b	21
	.data.b	23
	.data.w	.Ldw_begin+2311

	.data.b	52
	.section	.debug_str		;off: 1930
	.data.b	0
	.section	.debug_info		;off: 2336
	.data.w	.Ldw_str_begin+1930
	.data.b	39
	.data.b	1
	.data.b	23
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1931
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 2346
	.data.w	.Ldw_str_begin+1931
	.data.b	41
	.data.b	5
	.data.b	23
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1949
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 2355
	.data.w	.Ldw_str_begin+1949
	.data.b	43
	.data.b	5
	.data.b	23
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1966
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 2364
	.data.w	.Ldw_str_begin+1966
	.data.b	45
	.data.b	5
	.data.b	23
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1984
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 2373
	.data.w	.Ldw_str_begin+1984
	.data.b	47
	.data.b	5
	.data.b	23
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2001
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 2382
	.data.w	.Ldw_str_begin+2001
	.data.b	49
	.data.b	5
	.data.b	23
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2018
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 2391
	.data.w	.Ldw_str_begin+2018
	.data.b	51
	.data.b	5
	.data.b	23
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 2035
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 2400
	.data.w	.Ldw_str_begin+2035
	.data.b	53
	.data.b	5
	.data.b	23
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2052
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 2409
	.data.w	.Ldw_str_begin+2052
	.data.b	55
	.data.b	5
	.data.b	23
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 2069
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 2418
	.data.w	.Ldw_str_begin+2069
	.data.b	57
	.data.b	5
	.data.b	23
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2086
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 2428
	.data.w	.Ldw_str_begin+2086
	.data.b	58
	.data.b	3
	.data.b	23
	.data.w	.Ldw_begin+2335

	.data.b	45
	.section	.debug_str		;off: 2102
	.data.b	80,119,109,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 2440
	.data.w	.Ldw_str_begin+2102
	.data.b	51
	.data.b	16
	.data.b	2
	.data.w	.Ldw_begin+997

	.data.b	45
	.section	.debug_str		;off: 2118
	.data.b	80,119,109,95,80,101,114,105,111,100,84,121,112,101,0
	.section	.debug_info		;off: 2452
	.data.w	.Ldw_str_begin+2118
	.data.b	53
	.data.b	16
	.data.b	2
	.data.w	.Ldw_begin+1021

	.data.b	45
	.section	.debug_str		;off: 2133
	.data.b	80,119,109,95,68,117,116,121,67,121,99,108,101,84,121,112,101,0
	.section	.debug_info		;off: 2464
	.data.w	.Ldw_str_begin+2133
	.data.b	59
	.data.b	16
	.data.b	2
	.data.w	.Ldw_begin+1021

	.data.b	52
	.section	.debug_str		;off: 2151
	.data.b	0
	.section	.debug_info		;off: 2476
	.data.w	.Ldw_str_begin+2151
	.data.b	68
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2152
	.data.b	80,87,77,95,76,79,87,0
	.section	.debug_info		;off: 2486
	.data.w	.Ldw_str_begin+2152
	.data.b	69
	.data.b	5
	.data.b	2
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2160
	.data.b	80,87,77,95,72,73,71,72,0
	.section	.debug_info		;off: 2495
	.data.w	.Ldw_str_begin+2160
	.data.b	70
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2169
	.data.b	80,119,109,95,79,117,116,112,117,116,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 2505
	.data.w	.Ldw_str_begin+2169
	.data.b	71
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2475

	.data.b	52
	.section	.debug_str		;off: 2189
	.data.b	0
	.section	.debug_info		;off: 2517
	.data.w	.Ldw_str_begin+2189
	.data.b	75
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2190
	.data.b	80,87,77,95,82,73,83,73,78,71,95,69,68,71,69,0
	.section	.debug_info		;off: 2527
	.data.w	.Ldw_str_begin+2190
	.data.b	76
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2206
	.data.b	80,87,77,95,70,65,76,76,73,78,71,95,69,68,71,69,0
	.section	.debug_info		;off: 2536
	.data.w	.Ldw_str_begin+2206
	.data.b	77
	.data.b	5
	.data.b	2
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2223
	.data.b	80,87,77,95,66,79,84,72,95,69,68,71,69,83,0
	.section	.debug_info		;off: 2545
	.data.w	.Ldw_str_begin+2223
	.data.b	78
	.data.b	5
	.data.b	2
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2238
	.data.b	80,119,109,95,69,100,103,101,78,111,116,105,102,105,99,97,116,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 2555
	.data.w	.Ldw_str_begin+2238
	.data.b	79
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2516

	.data.b	52
	.section	.debug_str		;off: 2263
	.data.b	0
	.section	.debug_info		;off: 2567
	.data.w	.Ldw_str_begin+2263
	.data.b	82
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2264
	.data.b	80,87,77,95,85,78,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 2577
	.data.w	.Ldw_str_begin+2264
	.data.b	83
	.data.b	5
	.data.b	2
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2282
	.data.b	80,87,77,95,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 2586
	.data.w	.Ldw_str_begin+2282
	.data.b	84
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2298
	.data.b	80,119,109,95,73,110,105,116,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 2596
	.data.w	.Ldw_str_begin+2298
	.data.b	85
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2566

	.data.b	52
	.section	.debug_str		;off: 2316
	.data.b	0
	.section	.debug_info		;off: 2608
	.data.w	.Ldw_str_begin+2316
	.data.b	89
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2317
	.data.b	80,87,77,95,86,65,82,73,65,66,76,69,95,80,69,82,73,79,68,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+2317
	.data.b	90
	.data.b	5
	.data.b	2
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2337
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,0
	.section	.debug_info		;off: 2627
	.data.w	.Ldw_str_begin+2337
	.data.b	91
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2354
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,95,83,72,73,70,84,69,68,0
	.section	.debug_info		;off: 2636
	.data.w	.Ldw_str_begin+2354
	.data.b	92
	.data.b	5
	.data.b	2
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2379
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,95,67,69,78,84,69,82,95,65,76,73,71,78,69,68,0
	.section	.debug_info		;off: 2645
	.data.w	.Ldw_str_begin+2379
	.data.b	93
	.data.b	5
	.data.b	2
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2411
	.data.b	80,119,109,95,67,104,110,80,101,114,105,111,100,84,121,112,101,0
	.section	.debug_info		;off: 2655
	.data.w	.Ldw_str_begin+2411
	.data.b	94
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2607

	.data.b	71
	.data.b	99
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2429
	.data.b	68,117,116,121,73,115,48,79,114,49,48,48,0
	.section	.debug_info		;off: 2673
	.data.w	.Ldw_str_begin+2429
	.data.b	102
	.data.b	28
	.data.b	2
	.data.w	.Ldw_begin+985
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2442
	.data.b	73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2689
	.data.w	.Ldw_str_begin+2442
	.data.b	105
	.data.b	28
	.data.b	2
	.data.w	.Ldw_begin+1774
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2458
	.data.b	67,117,114,114,101,110,116,80,101,114,105,111,100,86,97,108,0
	.section	.debug_info		;off: 2705
	.data.w	.Ldw_str_begin+2458
	.data.b	107
	.data.b	28
	.data.b	2
	.data.w	.Ldw_begin+2451
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2475
	.data.b	80,119,109,95,67,104,97,110,110,101,108,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 2722
	.data.w	.Ldw_str_begin+2475
	.data.b	108
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2666

	.data.b	71
	.data.b	111
	.data.b	1
	.data.b	2
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2497
	.data.b	72,87,67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 2740
	.data.w	.Ldw_str_begin+2497
	.data.b	113
	.data.b	34
	.data.b	2
	.data.w	.Ldw_begin+1462
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2512
	.data.b	72,87,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2756
	.data.w	.Ldw_str_begin+2512
	.data.b	115
	.data.b	34
	.data.b	2
	.data.w	.Ldw_begin+2242
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2528
	.data.b	80,119,109,95,72,87,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 2773
	.data.w	.Ldw_str_begin+2528
	.data.b	116
	.data.b	3
	.data.b	2
	.data.w	.Ldw_begin+2733

	.data.b	71
	.data.b	140,1
	.data.b	1
	.data.b	2
	.data.b	80
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2545
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 2792
	.data.w	.Ldw_str_begin+2545
	.data.b	142,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2555
	.data.b	73,100,108,101,76,101,118,101,108,0
	.section	.debug_info		;off: 2809
	.data.w	.Ldw_str_begin+2555
	.data.b	144,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+1253
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2565
	.data.b	67,104,110,80,101,114,105,111,100,67,108,97,115,115,0
	.section	.debug_info		;off: 2826
	.data.w	.Ldw_str_begin+2565
	.data.b	146,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+2654
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2580
	.data.b	80,101,114,105,111,100,0
	.section	.debug_info		;off: 2843
	.data.w	.Ldw_str_begin+2580
	.data.b	148,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2587
	.data.b	68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 2860
	.data.w	.Ldw_str_begin+2587
	.data.b	150,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2597
	.data.b	83,104,105,102,116,86,97,108,117,101,0
	.section	.debug_info		;off: 2877
	.data.w	.Ldw_str_begin+2597
	.data.b	152,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2608
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 2894
	.data.w	.Ldw_str_begin+2608
	.data.b	154,1
	.data.b	27
	.data.b	2
	.data.w	.Ldw_begin+510
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2628
	.data.b	80,119,109,72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2911
	.data.w	.Ldw_str_begin+2628
	.data.b	156,1
	.data.b	25
	.data.b	2
	.data.w	.Ldw_begin+2772
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2647
	.data.b	80,119,109,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 2929
	.data.w	.Ldw_str_begin+2647
	.data.b	157,1
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2784

	.data.b	71
	.data.b	161,1
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2664
	.data.b	67,111,114,101,0
	.section	.debug_info		;off: 2949
	.data.w	.Ldw_str_begin+2664
	.data.b	163,1
	.data.b	26
	.data.b	2
	.data.w	.Ldw_begin+2323
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2669
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 2966
	.data.w	.Ldw_str_begin+2669
	.data.b	165,1
	.data.b	26
	.data.b	2
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2675
	.data.b	80,119,109,95,77,97,112,112,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 2984
	.data.w	.Ldw_str_begin+2675
	.data.b	166,1
	.data.b	3
	.data.b	2
	.data.w	.Ldw_begin+2941

	.data.b	71
	.data.b	170,1
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2691
	.data.b	77,97,120,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 3004
	.data.w	.Ldw_str_begin+2691
	.data.b	172,1
	.data.b	33
	.data.b	2
	.data.w	.Ldw_begin+997
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2703
	.data.b	80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3021
	.data.w	.Ldw_str_begin+2703
	.data.b	174,1
	.data.b	33
	.data.b	2
	.data.w	.Ldw_begin+112
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2724
	.data.b	80,119,109,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3039
	.data.w	.Ldw_str_begin+2724
	.data.b	179,1
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+2996

	.data.b	71
	.data.b	184,1
	.data.b	1
	.data.b	2
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2743
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3059
	.data.w	.Ldw_str_begin+2743
	.data.b	186,1
	.data.b	32
	.data.b	2
	.data.w	.Ldw_begin+525
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2757
	.data.b	80,119,109,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,0
	.section	.debug_info		;off: 3076
	.data.w	.Ldw_str_begin+2757
	.data.b	188,1
	.data.b	32
	.data.b	2
	.data.w	.Ldw_begin+546
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2777
	.data.b	80,119,109,72,119,67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 3093
	.data.w	.Ldw_str_begin+2777
	.data.b	190,1
	.data.b	32
	.data.b	2
	.data.w	.Ldw_begin+561
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2796
	.data.b	80,119,109,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3111
	.data.w	.Ldw_str_begin+2796
	.data.b	191,1
	.data.b	2
	.data.b	2
	.data.w	.Ldw_begin+3051

	.data.b	6
	.section	.debug_str		;off: 2811
	.data.b	80,119,109,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3124
	.data.w	.Ldw_str_begin+2811
	.data.b	120
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+577
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.section	.debug_abbrev		;off: 174
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

	.section	.debug_info		;off: 3143
	.data.b	6
	.section	.debug_str		;off: 2834
	.data.b	80,119,109,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3144
	.data.w	.Ldw_str_begin+2834
	.data.b	122
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2595
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	6
	.section	.debug_str		;off: 2856
	.data.b	80,119,109,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3164
	.data.w	.Ldw_str_begin+2856
	.data.b	140,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+593
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	6
	.section	.debug_str		;off: 2879
	.data.b	80,119,109,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3185
	.data.w	.Ldw_str_begin+2879
	.data.b	142,1
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2595
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	6
	.section	.debug_str		;off: 2901
	.data.b	80,119,109,95,67,111,114,101,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3206
	.data.w	.Ldw_str_begin+2901
	.data.b	199,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+614
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	6
	.section	.debug_str		;off: 2926
	.data.b	80,119,109,95,67,111,114,101,68,114,105,118,101,114,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3227
	.data.w	.Ldw_str_begin+2926
	.data.b	236,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+640
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	6
	.section	.debug_str		;off: 2950
	.data.b	80,119,109,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3248
	.data.w	.Ldw_str_begin+2950
	.data.b	149,2
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+157
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Pwm_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.

	.data.b	27
	.section	.debug_str		;off: 2964
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3269
	.data.w	.Ldw_str_begin+2964
	.data.b	220,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 195
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

	.section	.debug_info		;off: 3287
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 2988
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,68,101,105,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3289
	.data.w	.Ldw_str_begin+2988
	.data.b	239,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3014
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,83,101,116,73,100,108,101,76,101,118,101,108,0
	.section	.debug_info		;off: 3309
	.data.w	.Ldw_str_begin+3014
	.data.b	168,2
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3039
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,71,101,116,79,117,116,112,117,116,76,101,118,101,108,0
	.section	.debug_info		;off: 3329
	.data.w	.Ldw_str_begin+3039
	.data.b	184,2
	.data.b	24
	.data.b	10
	.data.w	.Ldw_begin+1253
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3066
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,83,101,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 3349
	.data.w	.Ldw_str_begin+3066
	.data.b	204,2
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3091
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,67,108,101,97,114,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3369
	.data.w	.Ldw_str_begin+3091
	.data.b	222,2
	.data.b	13
	.data.b	10
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 222
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

	.section	.debug_info		;off: 3383
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3124
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3385
	.data.w	.Ldw_str_begin+3124
	.data.b	170,3
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+1021
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3155
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,83,101,116,80,101,114,105,111,100,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 3405
	.data.w	.Ldw_str_begin+3155
	.data.b	191,3
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+985
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3186
	.data.b	71,116,109,95,80,119,109,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,69,110,97,98,108,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3425
	.data.w	.Ldw_str_begin+3186
	.data.b	209,3
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+1021
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3223
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 3445
	.data.w	.Ldw_str_begin+3223
	.data.b	63
	.data.b	31
	.data.b	24
	.data.w	.Ldw_begin+2311
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.section	.debug_abbrev		;off: 247
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 3463
	.data.b	8
	.section	.debug_str		;off: 3243
	.data.b	105,100,0
	.section	.debug_info		;off: 3464
	.data.w	.Ldw_str_begin+3243
	.data.b	65
	.data.b	17
	.data.b	24
	.data.w	.Ldw_begin+2311
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 252
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

	.section	.debug_info		;off: 3477
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3246
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 3480
	.data.w	.Ldw_str_begin+3246
	.data.b	131,2
	.data.b	48
	.data.b	21
	.data.w	.Ldw_begin+1045
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3259
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 3500
	.data.w	.Ldw_str_begin+3259
	.data.b	133,2
	.data.b	38
	.data.b	21
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3276
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 3516
	.data.w	.Ldw_str_begin+3276
	.data.b	105
	.data.b	39
	.data.b	42
	.data.w	.Ldw_begin+1045
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3292
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 3535
	.data.w	.Ldw_str_begin+3292
	.data.b	113
	.data.b	39
	.data.b	42
	.data.w	.Ldw_begin+1045
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3315
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 3554
	.data.w	.Ldw_str_begin+3315
	.data.b	41
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3337
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 3569
	.data.w	.Ldw_str_begin+3337
	.data.b	46
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3358
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,83,101,116,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 3584
	.data.w	.Ldw_str_begin+3358
	.data.b	51
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3386
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,83,101,116,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 3599
	.data.w	.Ldw_str_begin+3386
	.data.b	56
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3413
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,83,101,116,80,101,114,105,111,100,65,110,100,68,117,116,121,0
	.section	.debug_info		;off: 3614
	.data.w	.Ldw_str_begin+3413
	.data.b	61
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3445
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,83,101,116,80,101,114,105,111,100,65,110,100,68,117,116,121,0
	.section	.debug_info		;off: 3629
	.data.w	.Ldw_str_begin+3445
	.data.b	66
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3476
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,83,101,116,79,117,116,112,117,116,84,111,73,100,108,101,0
	.section	.debug_info		;off: 3644
	.data.w	.Ldw_str_begin+3476
	.data.b	71
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3507
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,83,101,116,79,117,116,112,117,116,84,111,73,100,108,101,0
	.section	.debug_info		;off: 3659
	.data.w	.Ldw_str_begin+3507
	.data.b	76
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3537
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3674
	.data.w	.Ldw_str_begin+3537
	.data.b	81
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3572
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3689
	.data.w	.Ldw_str_begin+3572
	.data.b	86
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3606
	.data.b	83,99,104,77,95,69,110,116,101,114,95,80,119,109,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3704
	.data.w	.Ldw_str_begin+3606
	.data.b	91
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3640
	.data.b	83,99,104,77,95,69,120,105,116,95,80,119,109,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3719
	.data.w	.Ldw_str_begin+3640
	.data.b	96
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3673
	.data.b	80,119,109,95,67,104,101,99,107,68,101,116,69,114,114,111,114,115,0
	.section	.debug_info		;off: 3734
	.data.w	.Ldw_str_begin+3673
	.data.b	198,3
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.w	Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_CheckDetErrors
	.data.b	1
	.data.b	93
	.data.b	180,128,1
	.data.b	116
	.data.b	0
	.data.b	12
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 271
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
	.data.w	Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_CheckDetErrors-Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1772
	.data.b	0,5,2
	.data.w	Pwm_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	203,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	12
	.data.b	108
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	60
	.data.b	11
	.data.b	92
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	13
	.data.b	139
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3769
	.data.b	22
	.section	.debug_str		;off: 3692
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 3770
	.data.w	.Ldw_str_begin+3692
	.data.b	200,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 319
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

	.section	.debug_info		;off: 3787
	.data.b	22
	.section	.debug_str		;off: 3706
	.data.b	65,112,105,83,105,100,0
	.section	.debug_info		;off: 3788
	.data.w	.Ldw_str_begin+3706
	.data.b	201,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3805
	.data.b	22
	.section	.debug_str		;off: 3713
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3806
	.data.w	.Ldw_str_begin+3713
	.data.b	202,3
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3823
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

	.section	.debug_info		;off: 3832
	.data.b	7
	.section	.debug_str		;off: 3720
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 3833
	.data.w	.Ldw_str_begin+3720
	.data.b	205,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
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

	.section	.debug_info		;off: 3851
	.data.b	8
	.section	.debug_str		;off: 3729
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 3852
	.data.w	.Ldw_str_begin+3729
	.data.b	206,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3743
	.data.b	80,119,109,95,67,97,108,99,117,108,97,116,101,68,117,116,121,0
	.section	.debug_info		;off: 3869
	.data.w	.Ldw_str_begin+3743
	.data.b	149,4
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.w	Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_CalculateDuty
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_CalculateDuty-Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1825
	.data.b	0,5,2
	.data.w	Pwm_CalculateDuty..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	155,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	12
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3902
	.data.b	22
	.section	.debug_str		;off: 3761
	.data.b	65,98,115,111,108,117,116,101,80,101,114,105,111,100,0
	.section	.debug_info		;off: 3903
	.data.w	.Ldw_str_begin+3761
	.data.b	151,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3920
	.data.b	22
	.section	.debug_str		;off: 3776
	.data.b	82,101,108,97,116,105,118,101,68,117,116,121,0
	.section	.debug_info		;off: 3921
	.data.w	.Ldw_str_begin+3776
	.data.b	152,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3938
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 3789
	.data.b	65,98,115,111,108,117,116,101,68,117,116,121,0
	.section	.debug_info		;off: 3948
	.data.w	.Ldw_str_begin+3789
	.data.b	155,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3966
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3802
	.data.b	80,119,109,95,67,104,97,110,110,101,108,73,110,105,116,0
	.section	.debug_info		;off: 3969
	.data.w	.Ldw_str_begin+3802
	.data.b	207,4
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.w	Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_ChannelInit
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	12
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_ChannelInit-Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1874
	.data.b	0,5,2
	.data.w	Pwm_ChannelInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	212,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	77
	.data.b	61
	.data.b	44
	.data.b	43
	.data.b	27
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4004
	.data.b	22
	.section	.debug_str		;off: 3818
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4005
	.data.w	.Ldw_str_begin+3818
	.data.b	209,4
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+117
	.data.b	0
	.data.w	.Ldw_loc_begin+133
	.section	.debug_loc		;off: 133
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	80
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4022
	.data.b	22
	.section	.debug_str		;off: 3835
	.data.b	67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4023
	.data.w	.Ldw_str_begin+3835
	.data.b	210,4
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+163
	.section	.debug_loc		;off: 163
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4040
	.data.b	22
	.section	.debug_str		;off: 3845
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4041
	.data.w	.Ldw_str_begin+3845
	.data.b	211,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+182
	.section	.debug_loc		;off: 182
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	82
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4058
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 3852
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 4068
	.data.w	.Ldw_str_begin+3852
	.data.b	214,4
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+212
	.section	.debug_loc		;off: 212
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4086
	.data.b	7
	.section	.debug_str		;off: 3869
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 4087
	.data.w	.Ldw_str_begin+3869
	.data.b	215,4
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+231
	.section	.debug_loc		;off: 231
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4105
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3880
	.data.b	80,119,109,95,73,110,105,116,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4108
	.data.w	.Ldw_str_begin+3880
	.data.b	135,5
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.w	Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_InitDetCheck
	.data.b	1
	.data.b	93
	.data.b	144,128,1
	.data.b	124
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_InitDetCheck-Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1909
	.data.b	0,5,2
	.data.w	Pwm_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	139,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	11
	.data.b	91
	.data.b	12
	.data.b	108
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4143
	.data.b	22
	.section	.debug_str		;off: 3897
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4144
	.data.w	.Ldw_str_begin+3897
	.data.b	137,5
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+162
	.data.b	0
	.data.w	.Ldw_loc_begin+250
	.section	.debug_loc		;off: 250
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4161
	.data.b	22
	.section	.debug_str		;off: 3907
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4162
	.data.w	.Ldw_str_begin+3907
	.data.b	138,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+269
	.section	.debug_loc		;off: 269
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4179
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 3914
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4189
	.data.w	.Ldw_str_begin+3914
	.data.b	141,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+288
	.section	.debug_loc		;off: 288
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4207
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3923
	.data.b	80,119,109,95,83,101,116,68,117,116,121,67,121,99,108,101,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4210
	.data.w	.Ldw_str_begin+3923
	.data.b	199,5
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.w	Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_SetDutyCycleDetCheck
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	12
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_SetDutyCycleDetCheck-Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1950
	.data.b	0,5,2
	.data.w	Pwm_SetDutyCycleDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	204,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	43
	.data.b	13
	.data.b	45
	.data.b	171
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	6
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4245
	.data.b	22
	.section	.debug_str		;off: 3948
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4246
	.data.w	.Ldw_str_begin+3948
	.data.b	201,5
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+307
	.section	.debug_loc		;off: 307
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

	.section	.debug_info		;off: 4263
	.data.b	22
	.section	.debug_str		;off: 3962
	.data.b	68,117,116,121,67,121,99,108,101,86,97,108,117,101,0
	.section	.debug_info		;off: 4264
	.data.w	.Ldw_str_begin+3962
	.data.b	202,5
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2463
	.data.b	0
	.data.w	.Ldw_loc_begin+337
	.section	.debug_loc		;off: 337
	.data.w	.LDW22
	.data.w	.LDW32
	.data.b	1,0
	.data.b	81
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4281
	.data.b	22
	.section	.debug_str		;off: 3977
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4282
	.data.w	.Ldw_str_begin+3977
	.data.b	203,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+367
	.section	.debug_loc		;off: 367
	.data.w	.LDW22
	.data.w	.LDW32
	.data.b	1,0
	.data.b	82
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4299
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 3984
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4309
	.data.w	.Ldw_str_begin+3984
	.data.b	206,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+397
	.section	.debug_loc		;off: 397
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4327
	.data.b	8
	.section	.debug_str		;off: 3993
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 4328
	.data.w	.Ldw_str_begin+3993
	.data.b	208,5
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4007
	.data.b	80,119,109,95,83,101,116,80,101,114,105,111,100,65,110,100,68,117,116,121,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4345
	.data.w	.Ldw_str_begin+4007
	.data.b	163,6
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.w	Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_SetPeriodAndDutyDetCheck
	.data.b	1
	.data.b	93
	.data.b	244,129,1
	.data.b	108
	.data.b	0
	.data.b	20
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_SetPeriodAndDutyDetCheck-Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2024
	.data.b	0,5,2
	.data.w	Pwm_SetPeriodAndDutyDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	169,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	76
	.data.b	43
	.data.b	11
	.data.b	45
	.data.b	155
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	34
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	35
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	73
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	52
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4380
	.data.b	22
	.section	.debug_str		;off: 4036
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4381
	.data.w	.Ldw_str_begin+4036
	.data.b	165,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+416
	.section	.debug_loc		;off: 416
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	80
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4398
	.data.b	22
	.section	.debug_str		;off: 4050
	.data.b	80,101,114,105,111,100,86,97,108,117,101,0
	.section	.debug_info		;off: 4399
	.data.w	.Ldw_str_begin+4050
	.data.b	166,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+446
	.section	.debug_loc		;off: 446
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	81
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4416
	.data.b	22
	.section	.debug_str		;off: 4062
	.data.b	68,117,116,121,67,121,99,108,101,86,97,108,117,101,0
	.section	.debug_info		;off: 4417
	.data.w	.Ldw_str_begin+4062
	.data.b	167,6
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2463
	.data.b	0
	.data.w	.Ldw_loc_begin+476
	.section	.debug_loc		;off: 476
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	82
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4434
	.data.b	22
	.section	.debug_str		;off: 4077
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4435
	.data.w	.Ldw_str_begin+4077
	.data.b	168,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+506
	.section	.debug_loc		;off: 506
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	83
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4452
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 4084
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4462
	.data.w	.Ldw_str_begin+4084
	.data.b	171,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+536
	.section	.debug_loc		;off: 536
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4480
	.data.b	8
	.section	.debug_str		;off: 4093
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 4481
	.data.w	.Ldw_str_begin+4093
	.data.b	172,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4107
	.data.b	80,119,109,95,69,110,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4498
	.data.w	.Ldw_str_begin+4107
	.data.b	170,7
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.w	Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_EnDisableNotificationDetCheck
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	12
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_EnDisableNotificationDetCheck-Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2168
	.data.b	0,5,2
	.data.w	Pwm_EnDisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	175,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	76
	.data.b	76
	.data.b	59
	.data.b	12
	.data.b	123
	.data.b	11
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4533
	.data.b	22
	.section	.debug_str		;off: 4141
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4534
	.data.w	.Ldw_str_begin+4141
	.data.b	172,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+555
	.section	.debug_loc		;off: 555
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	80
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4551
	.data.b	22
	.section	.debug_str		;off: 4155
	.data.b	65,112,105,83,105,100,0
	.section	.debug_info		;off: 4552
	.data.w	.Ldw_str_begin+4155
	.data.b	173,7
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+585
	.section	.debug_loc		;off: 585
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	81
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4569
	.data.b	22
	.section	.debug_str		;off: 4162
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4570
	.data.w	.Ldw_str_begin+4162
	.data.b	174,7
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.w	.Ldw_loc_begin+615
	.section	.debug_loc		;off: 615
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	82
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4587
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 4169
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4597
	.data.w	.Ldw_str_begin+4169
	.data.b	177,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+645
	.section	.debug_loc		;off: 645
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4615
	.data.b	7
	.section	.debug_str		;off: 4178
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 4616
	.data.w	.Ldw_str_begin+4178
	.data.b	178,7
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+664
	.section	.debug_loc		;off: 664
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4634
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4192
	.data.b	80,119,109,95,73,115,48,79,114,49,48,48,73,114,113,72,97,110,100,108,101,0
	.section	.debug_info		;off: 4637
	.data.w	.Ldw_str_begin+4192
	.data.b	236,7
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.w	Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_Is0Or100IrqHandle
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.w	__ghs_eofn_Pwm_Is0Or100IrqHandle-Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2209
	.data.b	0,5,2
	.data.w	Pwm_Is0Or100IrqHandle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CPwm.
	.data.b	6
	.data.b	3
	.data.b	241,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4670
	.data.b	22
	.section	.debug_str		;off: 4214
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 4671
	.data.w	.Ldw_str_begin+4214
	.data.b	238,7
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+277
	.data.b	0
	.data.w	.Ldw_loc_begin+683
	.section	.debug_loc		;off: 683
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	80
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4688
	.data.b	22
	.section	.debug_str		;off: 4231
	.data.b	67,117,114,114,101,110,116,80,101,114,105,111,100,0
	.section	.debug_info		;off: 4689
	.data.w	.Ldw_str_begin+4231
	.data.b	239,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+713
	.section	.debug_loc		;off: 713
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4706
	.data.b	22
	.section	.debug_str		;off: 4245
	.data.b	65,98,115,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 4707
	.data.w	.Ldw_str_begin+4245
	.data.b	240,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+732
	.section	.debug_loc		;off: 732
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4724
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 4258
	.data.b	72,97,110,100,108,101,70,108,97,103,0
	.section	.debug_info		;off: 4734
	.data.w	.Ldw_str_begin+4258
	.data.b	243,7
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+751
	.section	.debug_loc		;off: 751
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4752
	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 4269
	.data.b	80,87,77,95,67,97,108,99,117,108,97,116,101,67,111,109,112,97,114,101,86,97,108,117,101,115,0
	.section	.debug_info		;off: 4755
	.data.w	.Ldw_str_begin+4269
	.data.b	176,8
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 4296
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4770
	.data.w	.Ldw_str_begin+4296
	.data.b	178,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0

	.section	.debug_abbrev		;off: 368
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

	.section	.debug_info		;off: 4783
	.data.b	20
	.section	.debug_str		;off: 4303
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 4784
	.data.w	.Ldw_str_begin+4303
	.data.b	179,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4317
	.data.b	67,117,114,114,101,110,116,80,101,114,105,111,100,0
	.section	.debug_info		;off: 4798
	.data.w	.Ldw_str_begin+4317
	.data.b	180,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4331
	.data.b	65,98,115,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 4812
	.data.w	.Ldw_str_begin+4331
	.data.b	181,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4344
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4826
	.data.w	.Ldw_str_begin+4344
	.data.b	182,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4361
	.data.b	72,119,67,111,109,112,97,114,101,90,101,114,111,0
	.section	.debug_info		;off: 4840
	.data.w	.Ldw_str_begin+4361
	.data.b	183,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+307
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4375
	.data.b	72,119,67,111,109,112,97,114,101,79,110,101,0
	.section	.debug_info		;off: 4854
	.data.w	.Ldw_str_begin+4375
	.data.b	184,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+307
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 4388
	.data.b	77,97,120,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 4869
	.data.w	.Ldw_str_begin+4388
	.data.b	187,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4399
	.data.b	80,119,109,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 4886
	.data.w	.Ldw_str_begin+4399
	.data.b	144,9
	.data.b	29
	.data.b	1
	.data.w	Pwm_GetVersionInfo
	.data.w	__ghs_eofn_Pwm_GetVersionInfo
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

	.section	.debug_abbrev		;off: 385
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_GetVersionInfo
	.data.w	__ghs_eofn_Pwm_GetVersionInfo-Pwm_GetVersionInfo
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2257
	.data.b	0,5,2
	.data.w	Pwm_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	151,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	76
	.data.b	13
	.data.b	11
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4915
	.data.b	22
	.section	.debug_str		;off: 4418
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 4916
	.data.w	.Ldw_str_begin+4418
	.data.b	147,9
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+357
	.data.b	0
	.data.w	.Ldw_loc_begin+770
	.section	.debug_loc		;off: 770
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4933
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4433
	.data.b	80,119,109,95,73,110,105,116,0
	.section	.debug_info		;off: 4945
	.data.w	.Ldw_str_begin+4433
	.data.b	193,9
	.data.b	29
	.data.b	1
	.data.w	Pwm_Init
	.data.w	__ghs_eofn_Pwm_Init
	.data.b	1
	.data.b	93
	.data.b	240,131,1
	.data.b	108
	.data.b	0
	.data.b	20
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
	.data.w	Pwm_Init
	.data.w	__ghs_eofn_Pwm_Init-Pwm_Init
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2289
	.data.b	0,5,2
	.data.w	Pwm_Init
	.data.b	6
	.data.b	3
	.data.b	196,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	28
	.data.b	11
	.data.b	44
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	107
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	109
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	20
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	3
	.data.b	34
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4976
	.data.b	22
	.section	.debug_str		;off: 4442
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4977
	.data.w	.Ldw_str_begin+4442
	.data.b	195,9
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+157
	.data.b	0
	.data.w	.Ldw_loc_begin+789
	.section	.debug_loc		;off: 789
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	80
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4994
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 4452
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5004
	.data.w	.Ldw_str_begin+4452
	.data.b	198,9
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+819
	.section	.debug_loc		;off: 819
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5022
	.data.b	7
	.section	.debug_str		;off: 4459
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5023
	.data.w	.Ldw_str_begin+4459
	.data.b	199,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+838
	.section	.debug_loc		;off: 838
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5041
	.data.b	7
	.section	.debug_str		;off: 4476
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5042
	.data.w	.Ldw_str_begin+4476
	.data.b	200,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+857
	.section	.debug_loc		;off: 857
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5060
	.data.b	8
	.section	.debug_str		;off: 4490
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 5061
	.data.w	.Ldw_str_begin+4490
	.data.b	201,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4501
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5076
	.data.w	.Ldw_str_begin+4501
	.data.b	207,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4510
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5091
	.data.w	.Ldw_str_begin+4510
	.data.b	209,9
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+876
	.section	.debug_loc		;off: 876
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5109
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4521
	.data.b	80,119,109,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 5112
	.data.w	.Ldw_str_begin+4521
	.data.b	195,10
	.data.b	29
	.data.b	1
	.data.w	Pwm_DeInit
	.data.w	__ghs_eofn_Pwm_DeInit
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	44
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
	.data.w	Pwm_DeInit
	.data.w	__ghs_eofn_Pwm_DeInit-Pwm_DeInit
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2392
	.data.b	0,5,2
	.data.w	Pwm_DeInit
	.data.b	6
	.data.b	3
	.data.b	198,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	13
	.data.b	91
	.data.b	12
	.data.b	123
	.data.b	13
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	3
	.data.b	87
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	108
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	141
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	88
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	46
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5143
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	7
	.section	.debug_str		;off: 4532
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5153
	.data.w	.Ldw_str_begin+4532
	.data.b	200,10
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+895
	.section	.debug_loc		;off: 895
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5171
	.data.b	7
	.section	.debug_str		;off: 4539
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5172
	.data.w	.Ldw_str_begin+4539
	.data.b	201,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+914
	.section	.debug_loc		;off: 914
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5190
	.data.b	7
	.section	.debug_str		;off: 4553
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5191
	.data.w	.Ldw_str_begin+4553
	.data.b	202,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+933
	.section	.debug_loc		;off: 933
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5209
	.data.b	7
	.section	.debug_str		;off: 4570
	.data.b	73,100,108,101,83,105,103,110,97,108,76,101,118,101,108,0
	.section	.debug_info		;off: 5210
	.data.w	.Ldw_str_begin+4570
	.data.b	203,10
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+1253
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+953
	.section	.debug_loc		;off: 953
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5228
	.data.b	7
	.section	.debug_str		;off: 4586
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5229
	.data.w	.Ldw_str_begin+4586
	.data.b	204,10
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+973
	.section	.debug_loc		;off: 973
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5247
	.data.b	7
	.section	.debug_str		;off: 4603
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5248
	.data.w	.Ldw_str_begin+4603
	.data.b	205,10
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+992
	.section	.debug_loc		;off: 992
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5266
	.data.b	8
	.section	.debug_str		;off: 4614
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 5267
	.data.w	.Ldw_str_begin+4614
	.data.b	206,10
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4625
	.data.b	80,119,109,95,83,101,116,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5284
	.data.w	.Ldw_str_begin+4625
	.data.b	184,11
	.data.b	29
	.data.b	1
	.data.w	Pwm_SetDutyCycle
	.data.w	__ghs_eofn_Pwm_SetDutyCycle
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	52
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
	.data.w	Pwm_SetDutyCycle
	.data.w	__ghs_eofn_Pwm_SetDutyCycle-Pwm_SetDutyCycle
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2507
	.data.b	0,5,2
	.data.w	Pwm_SetDutyCycle
	.data.b	6
	.data.b	3
	.data.b	189,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	13
	.data.b	76
	.data.b	60
	.data.b	11
	.data.b	76
	.data.b	92
	.data.b	109
	.data.b	59
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	92
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	29
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	173
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	157
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5315
	.data.b	22
	.section	.debug_str		;off: 4642
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5316
	.data.w	.Ldw_str_begin+4642
	.data.b	186,11
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1011
	.section	.debug_loc		;off: 1011
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	80
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5333
	.data.b	22
	.section	.debug_str		;off: 4656
	.data.b	68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5334
	.data.w	.Ldw_str_begin+4656
	.data.b	188,11
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2463
	.data.b	0
	.data.w	.Ldw_loc_begin+1041
	.section	.debug_loc		;off: 1041
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	81
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5351
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 4666
	.data.b	67,117,114,114,101,110,116,80,101,114,105,111,100,0
	.section	.debug_info		;off: 5361
	.data.w	.Ldw_str_begin+4666
	.data.b	191,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1071
	.section	.debug_loc		;off: 1071
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5379
	.data.b	7
	.section	.debug_str		;off: 4680
	.data.b	65,98,115,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5380
	.data.w	.Ldw_str_begin+4680
	.data.b	192,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1090
	.section	.debug_loc		;off: 1090
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5398
	.data.b	7
	.section	.debug_str		;off: 4693
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5399
	.data.w	.Ldw_str_begin+4693
	.data.b	193,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1109
	.section	.debug_loc		;off: 1109
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5417
	.data.b	7
	.section	.debug_str		;off: 4707
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5418
	.data.w	.Ldw_str_begin+4707
	.data.b	194,11
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1128
	.section	.debug_loc		;off: 1128
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5436
	.data.b	7
	.section	.debug_str		;off: 4724
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5437
	.data.w	.Ldw_str_begin+4724
	.data.b	195,11
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1147
	.section	.debug_loc		;off: 1147
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5455
	.data.b	7
	.section	.debug_str		;off: 4731
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5456
	.data.w	.Ldw_str_begin+4731
	.data.b	196,11
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1166
	.section	.debug_loc		;off: 1166
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5474
	.data.b	7
	.section	.debug_str		;off: 4748
	.data.b	72,119,67,111,109,112,97,114,101,90,101,114,111,0
	.section	.debug_info		;off: 5475
	.data.w	.Ldw_str_begin+4748
	.data.b	197,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1185
	.section	.debug_loc		;off: 1185
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5493
	.data.b	7
	.section	.debug_str		;off: 4762
	.data.b	72,119,67,111,109,112,97,114,101,79,110,101,0
	.section	.debug_info		;off: 5494
	.data.w	.Ldw_str_begin+4762
	.data.b	198,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1204
	.section	.debug_loc		;off: 1204
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5512
	.data.b	7
	.section	.debug_str		;off: 4775
	.data.b	72,97,110,100,108,101,73,110,102,111,0
	.section	.debug_info		;off: 5513
	.data.w	.Ldw_str_begin+4775
	.data.b	200,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1223
	.section	.debug_loc		;off: 1223
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5531
	.data.b	8
	.section	.debug_str		;off: 4786
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5532
	.data.w	.Ldw_str_begin+4786
	.data.b	203,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4795
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5547
	.data.w	.Ldw_str_begin+4795
	.data.b	205,11
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1242
	.section	.debug_loc		;off: 1242
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5565
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4806
	.data.b	80,119,109,95,83,101,116,80,101,114,105,111,100,65,110,100,68,117,116,121,0
	.section	.debug_info		;off: 5568
	.data.w	.Ldw_str_begin+4806
	.data.b	235,12
	.data.b	29
	.data.b	1
	.data.w	Pwm_SetPeriodAndDuty
	.data.w	__ghs_eofn_Pwm_SetPeriodAndDuty
	.data.b	1
	.data.b	93
	.data.b	244,159,1
	.data.b	92
	.data.b	0
	.data.b	36
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
	.data.w	Pwm_SetPeriodAndDuty
	.data.w	__ghs_eofn_Pwm_SetPeriodAndDuty-Pwm_SetPeriodAndDuty
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2640
	.data.b	0,5,2
	.data.w	Pwm_SetPeriodAndDuty
	.data.b	6
	.data.b	3
	.data.b	242,12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	92
	.data.b	60
	.data.b	12
	.data.b	76
	.data.b	76
	.data.b	29
	.data.b	28
	.data.b	93
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	173
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	48
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
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
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5599
	.data.b	22
	.section	.debug_str		;off: 4827
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5600
	.data.w	.Ldw_str_begin+4827
	.data.b	238,12
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1261
	.section	.debug_loc		;off: 1261
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	80
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5617
	.data.b	22
	.section	.debug_str		;off: 4841
	.data.b	80,101,114,105,111,100,0
	.section	.debug_info		;off: 5618
	.data.w	.Ldw_str_begin+4841
	.data.b	239,12
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2451
	.data.b	0
	.data.w	.Ldw_loc_begin+1291
	.section	.debug_loc		;off: 1291
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	81
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5635
	.data.b	22
	.section	.debug_str		;off: 4848
	.data.b	68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5636
	.data.w	.Ldw_str_begin+4848
	.data.b	241,12
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2463
	.data.b	0
	.data.w	.Ldw_loc_begin+1321
	.section	.debug_loc		;off: 1321
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	82
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5653
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 4858
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5663
	.data.w	.Ldw_str_begin+4858
	.data.b	244,12
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1351
	.section	.debug_loc		;off: 1351
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5681
	.data.b	7
	.section	.debug_str		;off: 4865
	.data.b	65,98,115,68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5682
	.data.w	.Ldw_str_begin+4865
	.data.b	245,12
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1370
	.section	.debug_loc		;off: 1370
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5700
	.data.b	7
	.section	.debug_str		;off: 4878
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5701
	.data.w	.Ldw_str_begin+4878
	.data.b	246,12
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1389
	.section	.debug_loc		;off: 1389
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5719
	.data.b	7
	.section	.debug_str		;off: 4892
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5720
	.data.w	.Ldw_str_begin+4892
	.data.b	247,12
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1408
	.section	.debug_loc		;off: 1408
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5738
	.data.b	8
	.section	.debug_str		;off: 4909
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5739
	.data.w	.Ldw_str_begin+4909
	.data.b	250,12
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4918
	.data.b	72,97,110,100,108,101,73,110,102,111,0
	.section	.debug_info		;off: 5754
	.data.w	.Ldw_str_begin+4918
	.data.b	253,12
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1427
	.section	.debug_loc		;off: 1427
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5772
	.data.b	7
	.section	.debug_str		;off: 4929
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5773
	.data.w	.Ldw_str_begin+4929
	.data.b	255,12
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1446
	.section	.debug_loc		;off: 1446
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5791
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4940
	.data.b	80,119,109,95,83,101,116,79,117,116,112,117,116,84,111,73,100,108,101,0
	.section	.debug_info		;off: 5794
	.data.w	.Ldw_str_begin+4940
	.data.b	237,13
	.data.b	29
	.data.b	1
	.data.w	Pwm_SetOutputToIdle
	.data.w	__ghs_eofn_Pwm_SetOutputToIdle
	.data.b	1
	.data.b	93
	.data.b	244,135,1
	.data.b	100
	.data.b	0
	.data.b	28
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
	.data.w	Pwm_SetOutputToIdle
	.data.w	__ghs_eofn_Pwm_SetOutputToIdle-Pwm_SetOutputToIdle
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2744
	.data.b	0,5,2
	.data.w	Pwm_SetOutputToIdle
	.data.b	6
	.data.b	3
	.data.b	240,13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	13
	.data.b	76
	.data.b	60
	.data.b	11
	.data.b	76
	.data.b	29
	.data.b	92
	.data.b	59
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	125
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	157
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
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
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5825
	.data.b	22
	.section	.debug_str		;off: 4960
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5826
	.data.w	.Ldw_str_begin+4960
	.data.b	239,13
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1465
	.section	.debug_loc		;off: 1465
	.data.w	.LDW94
	.data.w	.LDW05
	.data.b	1,0
	.data.b	80
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5843
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 4974
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5853
	.data.w	.Ldw_str_begin+4974
	.data.b	242,13
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1495
	.section	.debug_loc		;off: 1495
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5871
	.data.b	7
	.section	.debug_str		;off: 4981
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5872
	.data.w	.Ldw_str_begin+4981
	.data.b	243,13
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1514
	.section	.debug_loc		;off: 1514
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5890
	.data.b	7
	.section	.debug_str		;off: 4995
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5891
	.data.w	.Ldw_str_begin+4995
	.data.b	245,13
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1533
	.section	.debug_loc		;off: 1533
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5909
	.data.b	8
	.section	.debug_str		;off: 5012
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5910
	.data.w	.Ldw_str_begin+5012
	.data.b	250,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5021
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5925
	.data.w	.Ldw_str_begin+5021
	.data.b	252,13
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1552
	.section	.debug_loc		;off: 1552
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5943
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5032
	.data.b	80,119,109,95,71,101,116,79,117,116,112,117,116,83,116,97,116,101,0
	.section	.debug_info		;off: 5946
	.data.w	.Ldw_str_begin+5032
	.data.b	209,14
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+2504
	.data.w	Pwm_GetOutputState
	.data.w	__ghs_eofn_Pwm_GetOutputState
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Pwm_GetOutputState
	.data.w	__ghs_eofn_Pwm_GetOutputState-Pwm_GetOutputState
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2827
	.data.b	0,5,2
	.data.w	Pwm_GetOutputState
	.data.b	6
	.data.b	3
	.data.b	212,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	13
	.data.b	60
	.data.b	44
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	173
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5981
	.data.b	22
	.section	.debug_str		;off: 5051
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5982
	.data.w	.Ldw_str_begin+5051
	.data.b	211,14
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1571
	.section	.debug_loc		;off: 1571
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	80
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5999
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 5065
	.data.b	79,117,116,112,117,116,76,101,118,101,108,0
	.section	.debug_info		;off: 6009
	.data.w	.Ldw_str_begin+5065
	.data.b	214,14
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2504
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1601
	.section	.debug_loc		;off: 1601
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6027
	.data.b	8
	.section	.debug_str		;off: 5077
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 6028
	.data.w	.Ldw_str_begin+5077
	.data.b	215,14
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5091
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6043
	.data.w	.Ldw_str_begin+5091
	.data.b	216,14
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1620
	.section	.debug_loc		;off: 1620
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6061
	.data.b	8
	.section	.debug_str		;off: 5098
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6062
	.data.w	.Ldw_str_begin+5098
	.data.b	219,14
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5107
	.data.b	80,119,109,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 6079
	.data.w	.Ldw_str_begin+5107
	.data.b	142,15
	.data.b	29
	.data.b	1
	.data.w	Pwm_DisableNotification
	.data.w	__ghs_eofn_Pwm_DisableNotification
	.data.b	1
	.data.b	93
	.data.b	240,131,1
	.data.b	108
	.data.b	0
	.data.b	20
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
	.data.w	Pwm_DisableNotification
	.data.w	__ghs_eofn_Pwm_DisableNotification-Pwm_DisableNotification
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2884
	.data.b	0,5,2
	.data.w	Pwm_DisableNotification
	.data.b	6
	.data.b	3
	.data.b	145,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	60
	.data.b	12
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	125
	.data.b	107
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
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
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6110
	.data.b	22
	.section	.debug_str		;off: 5131
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6111
	.data.w	.Ldw_str_begin+5131
	.data.b	144,15
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1639
	.section	.debug_loc		;off: 1639
	.data.w	.LDW55
	.data.w	.LDW65
	.data.b	1,0
	.data.b	80
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6128
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 5145
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 6138
	.data.w	.Ldw_str_begin+5145
	.data.b	147,15
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1669
	.section	.debug_loc		;off: 1669
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6156
	.data.b	7
	.section	.debug_str		;off: 5159
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6157
	.data.w	.Ldw_str_begin+5159
	.data.b	148,15
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1688
	.section	.debug_loc		;off: 1688
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6175
	.data.b	8
	.section	.debug_str		;off: 5166
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6176
	.data.w	.Ldw_str_begin+5166
	.data.b	149,15
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5183
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6191
	.data.w	.Ldw_str_begin+5183
	.data.b	152,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5192
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 6206
	.data.w	.Ldw_str_begin+5192
	.data.b	154,15
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1707
	.section	.debug_loc		;off: 1707
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6224
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5203
	.data.b	80,119,109,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 6227
	.data.w	.Ldw_str_begin+5203
	.data.b	228,15
	.data.b	29
	.data.b	1
	.data.w	Pwm_EnableNotification
	.data.w	__ghs_eofn_Pwm_EnableNotification
	.data.b	1
	.data.b	93
	.data.b	244,135,1
	.data.b	100
	.data.b	0
	.data.b	28
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
	.data.w	Pwm_EnableNotification
	.data.w	__ghs_eofn_Pwm_EnableNotification-Pwm_EnableNotification
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2965
	.data.b	0,5,2
	.data.w	Pwm_EnableNotification
	.data.b	6
	.data.b	3
	.data.b	232,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	60
	.data.b	11
	.data.b	76
	.data.b	76
	.data.b	29
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	60
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6258
	.data.b	22
	.section	.debug_str		;off: 5226
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6259
	.data.w	.Ldw_str_begin+5226
	.data.b	230,15
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2439
	.data.b	0
	.data.w	.Ldw_loc_begin+1726
	.section	.debug_loc		;off: 1726
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	80
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6276
	.data.b	22
	.section	.debug_str		;off: 5240
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 6277
	.data.w	.Ldw_str_begin+5240
	.data.b	231,15
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2554
	.data.b	0
	.data.w	.Ldw_loc_begin+1756
	.section	.debug_loc		;off: 1756
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	81
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6294
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 5253
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6304
	.data.w	.Ldw_str_begin+5253
	.data.b	234,15
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1786
	.section	.debug_loc		;off: 1786
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6322
	.data.b	7
	.section	.debug_str		;off: 5260
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 6323
	.data.w	.Ldw_str_begin+5260
	.data.b	235,15
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1805
	.section	.debug_loc		;off: 1805
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6341
	.data.b	7
	.section	.debug_str		;off: 5274
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6342
	.data.w	.Ldw_str_begin+5274
	.data.b	236,15
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+147
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1824
	.section	.debug_loc		;off: 1824
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6360
	.data.b	8
	.section	.debug_str		;off: 5291
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6361
	.data.w	.Ldw_str_begin+5291
	.data.b	239,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1045
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5300
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 6376
	.data.w	.Ldw_str_begin+5300
	.data.b	241,15
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1843
	.section	.debug_loc		;off: 1843
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6394
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5311
	.data.b	80,119,109,95,68,117,116,121,80,101,114,105,111,100,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 6397
	.data.w	.Ldw_str_begin+5311
	.data.b	195,16
	.data.b	30
	.data.b	1
	.data.w	Pwm_DutyPeriod_ISRHandler
	.data.w	__ghs_eofn_Pwm_DutyPeriod_ISRHandler
	.data.b	1
	.data.b	93
	.data.b	240,129,1
	.data.b	112
	.data.b	0
	.data.b	28
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
	.data.w	Pwm_DutyPeriod_ISRHandler
	.data.w	__ghs_eofn_Pwm_DutyPeriod_ISRHandler-Pwm_DutyPeriod_ISRHandler
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3055
	.data.b	0,5,2
	.data.w	Pwm_DutyPeriod_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	200,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	92
	.data.b	43
	.data.b	11
	.data.b	91
	.data.b	11
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	61
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	29
	.data.b	108
	.data.b	13
	.data.b	12
	.data.b	61
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	61
	.data.b	140
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	11
	.data.b	92
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 6428
	.data.b	22
	.section	.debug_str		;off: 5337
	.data.b	77,111,100,117,108,101,0
	.section	.debug_info		;off: 6429
	.data.w	.Ldw_str_begin+5337
	.data.b	197,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+1862
	.section	.debug_loc		;off: 1862
	.data.w	.LDW16
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6446
	.data.b	22
	.section	.debug_str		;off: 5344
	.data.b	77,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6447
	.data.w	.Ldw_str_begin+5344
	.data.b	198,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+1881
	.section	.debug_loc		;off: 1881
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	81
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6464
	.data.b	22
	.section	.debug_str		;off: 5356
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6465
	.data.w	.Ldw_str_begin+5356
	.data.b	199,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.w	.Ldw_loc_begin+1911
	.section	.debug_loc		;off: 1911
	.data.w	.LDW16
	.data.w	.LDW36
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6482
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 5364
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6492
	.data.w	.Ldw_str_begin+5364
	.data.b	202,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1930
	.section	.debug_loc		;off: 1930
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6510
	.data.b	7
	.section	.debug_str		;off: 5371
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 6511
	.data.w	.Ldw_str_begin+5371
	.data.b	203,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1949
	.section	.debug_loc		;off: 1949
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6529
	.data.b	7
	.section	.debug_str		;off: 5385
	.data.b	73,110,116,69,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6530
	.data.w	.Ldw_str_begin+5385
	.data.b	204,16
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1968
	.section	.debug_loc		;off: 1968
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6548
	.data.b	8
	.section	.debug_str		;off: 5397
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6549
	.data.w	.Ldw_str_begin+5397
	.data.b	205,16
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5407
	.data.b	72,87,67,104,97,110,110,101,108,79,98,106,101,99,116,0
	.section	.debug_info		;off: 6564
	.data.w	.Ldw_str_begin+5407
	.data.b	206,16
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1462
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1987
	.section	.debug_loc		;off: 1987
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6582
	.data.b	7
	.section	.debug_str		;off: 5423
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 6583
	.data.w	.Ldw_str_begin+5423
	.data.b	207,16
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1021
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2007
	.section	.debug_loc		;off: 2007
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6601
	.data.b	8
	.section	.debug_str		;off: 5441
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 6602
	.data.w	.Ldw_str_begin+5441
	.data.b	208,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+997
	.data.b	0
	.data.b	0

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
	.data.b	1
	.data.b	0
	.data.b	65,85,84,79,83,65,82,95,79,83,95,78,79,84,95,85,83,69,68,32,49,0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	57
	.data.b	2
	.data.b	3
	.data.b	34
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
	.data.b	177,2
	.data.b	80,50,67,79,78,83,84,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,99,111,110,115,116,32,112,116,114,116,121,112,101,32,42,0
	.data.b	1
	.data.b	190,2
	.data.b	67,79,78,83,84,80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116,0
	.data.b	1
	.data.b	240,2
	.data.b	86,65,82,40,118,97,114,116,121,112,101,44,109,101,109,99,108,97,115,115,41,32,118,97,114,116,121,112,101,0
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
	.data.b	1
	.data.b	55
	.data.b	69,95,78,79,84,95,79,75,32,40,83,116,100,95,82,101,116,117,114,110,84,121,112,101,41,40,48,120,48,49,117,41,0
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	9
	.data.b	1
	.data.b	31
	.data.b	80,87,77,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	32
	.data.b	80,87,77,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	33
	.data.b	80,87,77,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	36
	.data.b	80,87,77,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	37
	.data.b	80,87,77,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	38
	.data.b	80,87,77,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	40
	.data.b	80,87,77,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	41
	.data.b	80,87,77,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,49,50,49,85,41,0
	.data.b	1
	.data.b	54
	.data.b	80,87,77,95,68,69,95,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	63
	.data.b	80,87,77,95,83,69,84,95,68,85,84,89,95,67,89,67,76,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	72
	.data.b	80,87,77,95,83,69,84,95,80,69,82,73,79,68,95,65,78,68,95,68,85,84,89,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	81
	.data.b	80,87,77,95,83,69,84,95,79,85,84,80,85,84,95,84,79,95,73,68,76,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	89
	.data.b	80,87,77,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	98
	.data.b	80,87,77,95,71,69,84,95,79,85,84,80,85,84,95,83,84,65,84,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	170,1
	.data.b	80,87,77,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	172,1
	.data.b	80,87,77,95,68,85,84,89,95,83,72,73,70,84,95,73,78,95,84,73,67,75,83,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	174,1
	.data.b	80,87,77,95,72,65,78,68,76,69,95,83,72,73,70,84,95,66,89,95,79,70,70,83,69,84,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	176,1
	.data.b	80,87,77,95,78,79,84,73,70,73,67,65,84,73,79,78,95,83,85,80,80,79,82,84,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	178,1
	.data.b	80,87,77,95,48,95,49,48,48,95,73,78,84,69,82,82,85,80,84,95,72,65,78,68,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	181,1
	.data.b	80,87,77,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,48,32,40,56,85,41,0
	.data.b	1
	.data.b	183,1
	.data.b	80,87,77,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,49,32,40,52,85,41,0
	.data.b	1
	.data.b	185,1
	.data.b	80,87,77,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	187,1
	.data.b	80,87,77,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	1
	.data.b	191,1
	.data.b	80,87,77,95,77,65,88,95,67,72,65,78,78,69,76,95,73,68,95,67,79,78,70,73,71,85,82,69,68,32,40,49,49,85,41,0
	.data.b	1
	.data.b	193,1
	.data.b	80,87,77,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	10
	.data.b	3
	.data.b	33
	.data.b	11
	.data.b	3
	.data.b	43
	.data.b	12
	.data.b	1
	.data.b	45
	.data.b	73,78,80,85,84,95,65,82,71,95,68,69,84,69,67,84,32,83,84,68,95,79,70,70,0
	.data.b	1
	.data.b	70
	.data.b	71,69,84,95,67,80,54,52,40,99,112,44,111,112,49,44,82,116,44,67,82,109,41,32,123,117,105,110,116,51,50,32,118,97,108,49,95,116,101,109,112,32,61,32,48,85,44,32,118,97,108,50,95,116,101,109,112,32,61,32
	.data.b	48,85,59,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,77,82,82,67,32,112,34,32,35,99,112,32,34,44,32,34,32,35,111,112,49,32,34,44,32,37,48,44,32,37,49,44,32,99,34,32,35,67,82,109,32,58
	.data.b	32,34,61,114,34,40,118,97,108,49,95,116,101,109,112,41,44,32,34,61,114,34,40,118,97,108,50,95,116,101,109,112,41,58,32,58,32,34,109,101,109,111,114,121,34,41,59,32,82,116,32,61,32,40,40,40,117,105,110,116
	.data.b	54,52,41,118,97,108,50,95,116,101,109,112,41,32,60,60,32,51,50,41,32,43,32,118,97,108,49,95,116,101,109,112,59,125,0
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	13
	.data.b	3
	.data.b	33
	.data.b	14
	.data.b	3
	.data.b	31
	.data.b	15
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	16
	.data.b	3
	.data.b	56
	.data.b	17
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
	.data.b	204,3
	.data.b	71,84,77,95,66,65,83,69,95,65,68,68,82,32,40,48,120,57,52,56,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	207,3
	.data.b	71,84,77,95,72,65,76,32,40,40,71,84,77,95,77,79,68,85,76,69,32,42,41,71,84,77,95,66,65,83,69,95,65,68,68,82,41,0
	.data.b	1
	.data.b	212,3
	.data.b	71,84,77,95,67,76,85,83,84,69,82,95,78,85,77,32,40,56,85,41,0
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	39
	.data.b	71,84,77,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	213,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	215,1
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	132,2
	.data.b	71,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	134,2
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	112
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	114
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	144,8
	.data.b	71,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	146,8
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	34
	.data.b	19
	.data.b	1
	.data.b	158,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,1
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	181,9
	.data.b	71,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	183,9
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	193,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	195,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	232,3
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	234,3
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	21
	.data.b	3
	.data.b	39
	.data.b	22
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	23
	.data.b	3
	.data.b	26
	.data.b	24
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	25
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
	.data.b	25
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	26
	.data.b	3
	.data.b	28
	.data.b	27
	.data.b	4
	.data.b	1
	.data.b	152,1
	.data.b	67,80,85,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	154,1
	.data.b	28
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
	.data.b	28
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	29
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	30
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
	.data.b	30
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	31
	.data.b	3
	.data.b	34
	.data.b	32
	.data.b	1
	.data.b	66
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	33
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
	.data.b	33
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	34
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	33
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
	.data.b	33
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	35
	.data.b	3
	.data.b	38
	.data.b	36
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	110
	.data.b	77,99,97,108,95,71,101,116,67,111,114,101,73,100,40,41,32,77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,40,41,0
	.data.b	1
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	38
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
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	62
	.data.b	39
	.data.b	3
	.data.b	41
	.data.b	40
	.data.b	1
	.data.b	28
	.data.b	80,87,77,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	29
	.data.b	80,87,77,95,77,79,68,85,76,69,95,73,68,32,40,49,50,49,85,41,0
	.data.b	1
	.data.b	30
	.data.b	80,87,77,95,73,78,83,84,65,78,67,69,95,73,68,32,40,48,85,41,0
	.data.b	1
	.data.b	33
	.data.b	80,87,77,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	34
	.data.b	80,87,77,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	35
	.data.b	80,87,77,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	38
	.data.b	80,87,77,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	39
	.data.b	80,87,77,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	40
	.data.b	80,87,77,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	41
	.data.b	1
	.data.b	39
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	40
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	52
	.data.b	80,87,77,95,77,65,88,95,68,85,84,89,67,89,67,76,69,95,84,73,67,75,83,95,84,79,77,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	54
	.data.b	80,87,77,95,77,65,88,95,68,85,84,89,67,89,67,76,69,95,84,73,67,75,83,95,65,84,79,77,32,40,48,120,70,70,70,70,70,70,85,41,0
	.data.b	1
	.data.b	56
	.data.b	80,87,77,95,77,65,88,95,80,69,82,73,79,68,95,84,73,67,75,83,95,84,79,77,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	58
	.data.b	80,87,77,95,77,65,88,95,80,69,82,73,79,68,95,84,73,67,75,83,95,65,84,79,77,32,40,48,120,70,70,70,70,70,70,85,41,0
	.data.b	1
	.data.b	61
	.data.b	80,87,77,95,73,78,73,84,95,83,73,68,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	63
	.data.b	80,87,77,95,68,69,73,78,73,84,95,83,73,68,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	65
	.data.b	80,87,77,95,83,69,84,95,68,85,84,89,67,89,67,76,69,95,83,73,68,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	67
	.data.b	80,87,77,95,83,69,84,95,80,69,82,73,79,68,65,78,68,68,85,84,89,95,83,73,68,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	69
	.data.b	80,87,77,95,83,69,84,95,79,85,84,80,85,84,84,79,73,68,76,69,95,83,73,68,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	71
	.data.b	80,87,77,95,71,69,84,95,79,85,84,80,85,84,83,84,65,84,69,95,83,73,68,32,40,48,120,48,53,85,41,0
	.data.b	1
	.data.b	73
	.data.b	80,87,77,95,68,73,83,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,95,83,73,68,32,40,48,120,48,54,85,41,0
	.data.b	1
	.data.b	75
	.data.b	80,87,77,95,69,78,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,95,83,73,68,32,40,48,120,48,55,85,41,0
	.data.b	1
	.data.b	77
	.data.b	80,87,77,95,71,69,84,95,86,69,82,83,73,79,78,95,73,78,70,79,95,83,73,68,32,40,48,120,48,56,85,41,0
	.data.b	1
	.data.b	80
	.data.b	80,87,77,95,73,83,82,95,83,73,68,32,40,48,120,48,70,85,41,0
	.data.b	1
	.data.b	84
	.data.b	80,87,77,95,69,95,73,78,73,84,95,70,65,73,76,69,68,32,40,48,120,49,48,85,41,0
	.data.b	1
	.data.b	86
	.data.b	80,87,77,95,69,95,85,78,73,78,73,84,32,40,48,120,49,49,85,41,0
	.data.b	1
	.data.b	88
	.data.b	80,87,77,95,69,95,80,65,82,65,77,95,67,72,65,78,78,69,76,32,40,48,120,49,50,85,41,0
	.data.b	1
	.data.b	90
	.data.b	80,87,77,95,69,95,80,69,82,73,79,68,95,85,78,67,72,65,78,71,69,65,66,76,69,32,40,48,120,49,51,85,41,0
	.data.b	1
	.data.b	92
	.data.b	80,87,77,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,48,120,49,52,85,41,0
	.data.b	1
	.data.b	94
	.data.b	80,87,77,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,48,120,49,53,85,41,0
	.data.b	1
	.data.b	99
	.data.b	80,87,77,95,69,95,80,65,82,65,77,95,86,65,76,85,69,32,40,48,120,70,51,85,41,0
	.data.b	1
	.data.b	104
	.data.b	80,87,77,95,69,95,78,79,84,73,70,89,95,78,79,84,67,79,78,70,73,71,32,40,48,120,70,52,85,41,0
	.data.b	1
	.data.b	106
	.data.b	80,87,77,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,48,120,69,48,85,41,0
	.data.b	1
	.data.b	108
	.data.b	80,87,77,95,69,95,67,79,82,69,95,67,72,65,78,78,69,76,95,77,73,83,77,65,84,67,72,32,40,48,120,69,49,85,41,0
	.data.b	1
	.data.b	109
	.data.b	80,87,77,95,69,95,83,65,70,69,84,89,95,67,72,69,67,75,95,70,65,73,76,69,68,32,40,48,120,69,50,41,0
	.data.b	1
	.data.b	121
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	122
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	200,1
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	201,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	68
	.data.b	42
	.data.b	1
	.data.b	37
	.data.b	68,69,84,95,69,82,82,79,82,95,66,85,70,70,69,82,95,83,73,90,69,32,54,48,85,0
	.data.b	1
	.data.b	38
	.data.b	82,85,78,84,73,77,69,95,69,82,82,79,82,95,66,85,70,70,69,82,95,83,73,90,69,32,54,48,85,0
	.data.b	1
	.data.b	39
	.data.b	84,70,95,69,82,82,79,82,95,66,85,70,70,69,82,95,83,73,90,69,32,54,48,85,0
	.data.b	4
	.data.b	3
	.data.b	72
	.data.b	43
	.data.b	4
	.data.b	1
	.data.b	114
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	115
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	127
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	129,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	136,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	147,1
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	149,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	154,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	156,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	160,49
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	163,49
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	167,1
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	169,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	174,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	176,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	211,57
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	214,57
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	187,1
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	189,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	193,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	195,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	139,2
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	141,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	144,2
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	146,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	152,2
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	154,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	161,2
	.data.b	80,87,77,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,32,35,35,32,69,120
	.data.b	99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	165,2
	.data.b	80,87,77,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,32,35,35,32,69,120,99,108
	.data.b	117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	169,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,82,65,77,95,80,84,82,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,38,40,40,80,119,109,95,67,111,114,101,67,104,97
	.data.b	110,110,101,108,83,116,97,116,117,115,80,116,114,91,67,111,114,101,73,100,93,41,91,67,104,73,110,100,101,120,73,110,67,111,114,101,93,41,0
	.data.b	1
	.data.b	174,2
	.data.b	80,87,77,95,71,69,84,95,72,87,95,67,76,65,83,83,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,80,119,109,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67
	.data.b	111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100,101,120,73,110,67,111,114,101,93,46,32,80,119,109,72,119
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,46,72,87,67,104,97,110,110,101,108,73,110,100,101,120,46,109,111,100,117,108,101,41,0
	.data.b	1
	.data.b	180,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,79,66,74,69,67,84,95,80,84,82,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,38,80,119,109,95,67,111,110,102,105
	.data.b	103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100,101,120,73,110,67
	.data.b	111,114,101,93,46,32,80,119,109,72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,46,72,87,67,104,97,110,110,101,108,73,110,100,101,120,41,0
	.data.b	1
	.data.b	185,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,73,78,68,69,88,95,73,78,95,67,79,82,69,40,76,111,103,105,99,67,104,97,110,110,101,108,73,100,41,32,80,119,109,95,67,111,110,102,105,103,80,116,114,45
	.data.b	62,80,119,109,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,91,76,111,103,105,99,67,104,97,110,110,101,108,73,100,93,46,73,110,100,101,120,0
	.data.b	1
	.data.b	190,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,85,80,68,65,84,69,95,77,69,67,72,65,78,73,83,77,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,80,119,109,95
	.data.b	67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100
	.data.b	101,120,73,110,67,111,114,101,93,46,32,80,119,109,72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,46,72,87,67,104,97,110,110,101,108,67,111,110,102,105,103,46,105,115,83,121,110,99,85,112,100,97,116,101,69,110
	.data.b	97,98,108,101,100,41,0
	.data.b	1
	.data.b	196,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,77,79,68,69,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,80,119,109,95,67,111,110,102,105,103,80,116,114,45,62,67
	.data.b	111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100,101,120,73,110,67,111,114,101,93,46,32,67
	.data.b	104,110,80,101,114,105,111,100,67,108,97,115,115,41,0
	.data.b	1
	.data.b	202,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,73,68,76,69,76,69,86,69,76,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,80,119,109,95,67,111,110,102,105,103,80
	.data.b	116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100,101,120,73,110,67,111,114
	.data.b	101,93,46,32,73,100,108,101,76,101,118,101,108,41,0
	.data.b	1
	.data.b	208,2
	.data.b	80,87,77,95,71,69,84,95,67,72,65,78,78,69,76,95,78,79,84,73,70,89,95,80,84,82,40,67,111,114,101,73,100,44,67,104,73,110,100,101,120,73,110,67,111,114,101,41,32,40,80,119,109,95,67,111,110,102,105,103
	.data.b	80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,100,101,120,73,110,67,111
	.data.b	114,101,93,46,32,78,111,116,105,102,105,99,97,116,105,111,110,70,117,110,99,80,116,114,41,0
	.data.b	1
	.data.b	163,3
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	165,3
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	164,17
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	166,17
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 431
	.data.b	0
