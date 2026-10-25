	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682572..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_CheckDetErrors:
.LDW01:
	push	{r2,r4-r5,lr}
	mov	r2,r1
.LDW11:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.2:
	.endo	..gh.endasm.2

;line513
..lin.36298053..cb15ea07.0_1::
.LDWlin1:
	ldr	r12,.L230
	ldr	r1,[r12,r3 lsl 2]
	ldr	r1,[r1]
	mov	r4,1
	cmp	r1,1
	beq	.L27
.L28:
	mov	r3,10
.L219:

.L220:

	mov	r1,0
	mov	r0,100
.L232:

	bl	Det_ReportError
	b	.L29
.L27:
	cmp	r0,10
	movhs	r3,20
	bhs	.L220
.L30:
	ldr	r1,.L231
	ldr	r12,[r1]
	ldr	r5,[r12,16]
	ldr	r3,[r12,r3 lsl 2]
	add	r1,r5,r0 lsl 3
	ldrb	r1,[r1,1]
	ldr	r3,[r3,4]
	add	r1,r1,r1 lsl 2
	ldrb	r1,[r3,r1 lsl 2]
	cmp	r1,r0
	movne	r3,225
	bne	.L219
.L33:
	mov	r4,0
.L29:
	mov	r0,r4
.LDW21:
.L234:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_CheckDetErrors:
	.endf	Gpt_CheckDetErrors
	.endf	Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r4	local
;CoreId	r3	local

;LogicChannel	r0	param
;ApiSid	r2	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Gpt_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_ConfigPtr:	.space	4
	.endo	Gpt_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Gpt_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_CoreDriverStatusPtr:
	.data.w	Gpt_DriverStatusCore0
	.data.w	Gpt_DriverStatusCore1
	.space	8
	.endo	Gpt_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_CoreDriverStatusPtr
	.section ".ghcalltbl",""
	.align	4
.L233:	.data.w	.L232
	.endo	.L233
	.section ".ghrettbl",""
	.align	4
.L235:	.data.w	.L234
	.endo	.L235
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Gpt_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_DriverStatusCore0:	.space	12
	.endo	Gpt_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_DriverStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Gpt_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_DriverStatusCore1:	.space	12
	.endo	Gpt_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_DriverStatusCore1
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_PredefTimerDetCheck:
.LDW31:
	push	{r4,lr}
	mov	r2,r0
	mov	r4,r1
.LDW41:
	mov	r0,0
	b	.L407

.L230:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L230

.L231:	.data.w	Gpt_ConfigPtr
	.endo	.L231

.L407:

;line583
..lin.36298053..f867d381.0_2::
.LDWlin2:
..gh.beginasm.4:
	.endo	..gh.beginasm.4
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.5:
	.endo	..gh.endasm.5

;line585
..lin.36298053..f867d381.0_3::
.LDWlin3:
	ldr	r1,.L408
	ldr	r1,[r1,r3 lsl 2]
	ldr	r1,[r1]
	mov	r12,10
	cmp	r1,0
	movne	r12,22
	cmpne	r4,0
	beq	.L243
	cmp	r2,3
	movne	r12,23
	cmpne	r2,2
.L409:

	popls	{r4,pc}
.L243:
	mov	r3,r12
	mov	r2,13
	mov	r1,r0
	mov	r0,100
.L411:

	bl	Det_ReportError
	mov	r0,1
.LDW51:
.L413:

	pop	{r4,pc}
__ghs_eofn_Gpt_PredefTimerDetCheck:
	.endf	Gpt_PredefTimerDetCheck
	.endf	Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r0	local

;PredefTimer	r2	param
;TimeValuePtr	r4	param

	.section ".bss","awb"
.L344:
	.endo	.L344
	.section ".ghrettbl",""
.L410:	.data.w	.L409
	.endo	.L410
	.section ".ghcalltbl",""
.L412:	.data.w	.L411
	.endo	.L412
	.section ".ghrettbl",""
.L414:	.data.w	.L413
	.endo	.L414
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_InitDetCheck:
.LDW61:
	push	{r4,lr}
.LDW71:
	mov	r4,1
	cmp	r0,0
	moveq	r3,22
	beq	.L990
.L417:
	ldr	r2,[r0,r1 lsl 2]
	cmp	r2,0
	ldreq	r2,[r0,36]
	cmpeq	r2,0
	ldreq	r0,[r0,40]
	cmpeq	r0,0
	bne	.L420
.L421:
	mov	r3,224
.L990:

	mov	r2,r4
	mov	r1,r0
	b	.L991
.L420:
	ldr	r0,.L408
	ldr	r0,[r0,r1 lsl 2]
	ldr	r0,[r0]
	cmp	r0,0
	beq	.L425
.L426:
	mov	r3,13
	mov	r2,r4
	mov	r1,0
.L991:

	mov	r0,100
.L1001:

	bl	Det_ReportError
	b	.L419
.L425:
	mov	r4,r0
.L419:
	mov	r0,r4
.LDW81:
.L1003:

	pop	{r4,pc}
__ghs_eofn_Gpt_InitDetCheck:
	.endf	Gpt_InitDetCheck
	.endf	Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r4	local

;ConfigPtr	r0	param
;CoreId	r1	param

	.section ".bss","awb"
.L902:
	.endo	.L902
	.section ".ghcalltbl",""
.L1002:	.data.w	.L1001
	.endo	.L1002
	.section ".ghrettbl",""
.L1004:	.data.w	.L1003
	.endo	.L1004
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
	.global	Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_DeInitCheck:
.LDW91:
	push	{r2,r4-r5,lr}
	ldr	r2,.L408
.LDW02:
	mov	r5,r0
	ldr	r1,[r2,r5 lsl 2]
	ldr	r1,[r1]
	mov	r0,0
	cmp	r1,1
	beq	.L1007
	mov	r3,10
	mov	r2,2
	mov	r1,r0
	mov	r0,100
.L1236:

	bl	Det_ReportError
	mov	r0,1
.L1238:

	pop	{r2,r4-r5,pc}
.L1007:
	mov	r4,r0
	b	.L1013
.L1012:
	ldr	r2,.L1234
	ldr	r2,[r2,r5 lsl 2]
	lsr	r1,r4,24
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,4]
	cmp	r1,1
	bne	.L1011
	mov	r3,11
	mov	r2,2
	mov	r1,r0
	mov	r0,100
.L1240:

	bl	Det_ReportRuntimeError
	mov	r0,1
.L1011:
	add	r4,r4,1<<24
.L1013:
	ldr	r1,.L1235
	ldr	r1,[r1]
	ldr	r1,[r1,r5 lsl 2]
	ldrb	r1,[r1]
	cmp	r1,r4 lsr 24
.L1242:

	popls	{r2,r4-r5,pc}
	cmp	r0,0
	beq	.L1012
.LDW12:
.L1244:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_DeInitCheck:
	.endf	Gpt_DeInitCheck
	.endf	Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r0	local

;CoreId	r5	param

	.section ".mcal_const_asil_d_unspecified","a"
Gpt_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_CoreChannelStatusPtr:
	.data.w	Gpt_ChannelStatusCore0
	.data.w	Gpt_ChannelStatusCore1
	.space	8
	.endo	Gpt_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_CoreChannelStatusPtr
	.section ".ghcalltbl",""
.L1237:	.data.w	.L1236
	.endo	.L1237
	.section ".ghrettbl",""
.L1239:	.data.w	.L1238
	.endo	.L1239
	.section ".ghcalltbl",""
.L1241:	.data.w	.L1240
	.endo	.L1241
	.section ".ghrettbl",""
.L1243:	.data.w	.L1242
	.endo	.L1243
.L1245:	.data.w	.L1244
	.endo	.L1245
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Gpt_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_ChannelStatusCore0:	.space	48
	.endo	Gpt_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_ChannelStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
Gpt_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_ChannelStatusCore1:	.space	32
	.endo	Gpt_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_ChannelStatusCore1
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_StartTimerCheck:
.LDW22:
	push	{r4-r6,lr}
	mov	r6,r1
	mov	r4,r2
.LDW32:
	mov	r5,r0
	mov	r1,5
.L1489:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
.L1491:

	popne	{r4-r6,pc}
	ldr	r1,.L1235
	ldr	r3,[r1]
	ldr	r1,[r3,16]
	cmp	r6,0
	add	r1,r1,r5 lsl 3
	ldrb	r2,[r1,1]
	beq	.L1258
	cmp	r6,1
	ldreq	r12,[r3,r4 lsl 2]
	addeq	r1,r2,r2 lsl 2
	ldreq	r12,[r12,4]
	addeq	r1,r12,r1 lsl 2
	ldreq	r1,[r1,16]
	cmpeq	r1,0
	beq	.L1258
	ldr	r3,[r3,r4 lsl 2]
	add	r1,r2,r2 lsl 2
	ldr	r3,[r3,4]
	add	r1,r3,r1 lsl 2
	ldr	r1,[r1,4]
	cmp	r1,r6
	bhs	.L1257
.L1258:
	mov	r3,21
	mov	r2,5
	mov	r1,r0
	mov	r0,100
.L1493:

	bl	Det_ReportError
	b	.L1305
.L1257:
	ldr	r1,.L1234
	ldr	r1,[r1,r4 lsl 2]
	add	r1,r1,r2 lsl 3
	ldr	r1,[r1,4]
	cmp	r1,1
.L1495:

	popne	{r4-r6,pc}
	mov	r3,11
	mov	r2,5
	mov	r1,r0
	mov	r0,100
.L1497:

	bl	Det_ReportRuntimeError
.L1305:
	mov	r0,1
.LDW42:
.L1499:

	pop	{r4-r6,pc}
__ghs_eofn_Gpt_StartTimerCheck:
	.endf	Gpt_StartTimerCheck
	.endf	Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r0	local
;ChInCoreIndex	r2	local

;LogicChannel	r5	param
;TimerValue	r6	param
;CoreId	r4	param

	.section ".ghcalltbl",""
.L1490:	.data.w	.L1489
	.endo	.L1490
	.section ".ghrettbl",""
.L1492:	.data.w	.L1491
	.endo	.L1492
	.section ".ghcalltbl",""
.L1494:	.data.w	.L1493
	.endo	.L1494
	.section ".ghrettbl",""
.L1496:	.data.w	.L1495
	.endo	.L1496
	.section ".ghcalltbl",""
.L1498:	.data.w	.L1497
	.endo	.L1498
	.section ".ghrettbl",""
.L1500:	.data.w	.L1499
	.endo	.L1500
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.global	Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_EnableNotificationCheck:
.LDW52:
	push	{r2,r4-r5,lr}
	mov	r4,r1
.LDW62:
	mov	r5,r0
	mov	r1,7
.L1660:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
.L1662:

	popne	{r2,r4-r5,pc}
	ldr	r1,.L1235
	ldr	r12,[r1]
	ldr	r2,[r12,16]
	ldr	r12,[r12,r4 lsl 2]
	add	r1,r2,r5 lsl 3
	ldrb	r2,[r1,1]
	ldr	r12,[r12,4]
	add	r1,r2,r2 lsl 2
	add	r1,r12,r1 lsl 2
	ldr	r1,[r1,8]
	cmp	r1,0
	ldrne	r12,.L1234
	ldrne	r1,[r12,r4 lsl 2]
	mov	r3,20
	ldrbne	r1,[r1,r2 lsl 3]
	movne	r3,242
	cmpne	r1,1
.L1664:

	popne	{r2,r4-r5,pc}
	mov	r2,7
	mov	r1,r0
	mov	r0,100
.L1666:

	bl	Det_ReportError
	mov	r0,1
.LDW72:
.L1668:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_EnableNotificationCheck:
	.endf	Gpt_EnableNotificationCheck
	.endf	Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r0	local
;ChInCoreIndex	r2	local

;LogicChannel	r5	param
;CoreId	r4	param

	.section ".ghcalltbl",""
.L1661:	.data.w	.L1660
	.endo	.L1661
	.section ".ghrettbl",""
.L1663:	.data.w	.L1662
	.endo	.L1663
.L1665:	.data.w	.L1664
	.endo	.L1665
	.section ".ghcalltbl",""
.L1667:	.data.w	.L1666
	.endo	.L1667
	.section ".ghrettbl",""
.L1669:	.data.w	.L1668
	.endo	.L1669
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
	.global	Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_DisableNotificationCheck:
.LDW82:
	push	{r2,r4-r5,lr}
	mov	r4,r1
.LDW92:
	mov	r5,r0
	mov	r1,8
.L1820:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
.L1822:

	popne	{r2,r4-r5,pc}
	ldr	r1,.L1235
	ldr	r12,[r1]
	ldr	r2,[r12,16]
	ldr	r12,[r12,r4 lsl 2]
	add	r1,r2,r5 lsl 3
	ldrb	r2,[r1,1]
	ldr	r12,[r12,4]
	add	r1,r2,r2 lsl 2
	add	r1,r12,r1 lsl 2
	ldr	r1,[r1,8]
	cmp	r1,0
	ldrne	r12,.L1234
	ldrne	r1,[r12,r4 lsl 2]
	mov	r3,20
	ldrbne	r1,[r1,r2 lsl 3]
	movne	r3,241
	cmpne	r1,0
.L1824:

	popne	{r2,r4-r5,pc}
	mov	r2,8
	mov	r0,100
.L1826:

	bl	Det_ReportError
	mov	r0,1
.LDW03:
.L1828:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_DisableNotificationCheck:
	.endf	Gpt_DisableNotificationCheck
	.endf	Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;ErrValue	r0	local
;ChInCoreIndex	r2	local

;LogicChannel	r5	param
;CoreId	r4	param

	.section ".ghcalltbl",""
.L1821:	.data.w	.L1820
	.endo	.L1821
	.section ".ghrettbl",""
.L1823:	.data.w	.L1822
	.endo	.L1823
.L1825:	.data.w	.L1824
	.endo	.L1825
	.section ".ghcalltbl",""
.L1827:	.data.w	.L1826
	.endo	.L1827
	.section ".ghrettbl",""
.L1829:	.data.w	.L1828
	.endo	.L1829
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
	.global	Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_HWStopTimer:
.LDW13:
	push	{r4,lr}
	ldr	r12,.L1235
.LDW23:
	cmp	r1,0
	ldr	r2,[r12]
	bne	.L1832
	ldr	r1,[r2,20]
	add	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 2
.L1942:

	bl	Gtm_Timer_Hal_StopChannel
.L1944:

	pop	{r4,pc}
.L1832:
	ldr	r1,[r2,24]
	ldr	r0,[r1,r0 lsl 4]
.L1946:

	bl	Basetimer_Hal_StopTimer
	mov	r0,1
.LDW33:
.L1948:

	pop	{r4,pc}
__ghs_eofn_Gpt_HWStopTimer:
	.endf	Gpt_HWStopTimer
	.endf	Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;SafetyFlag	r4	local

;HwCfgMapIndex	r0	param
;HwClass	r1	param

	.section ".ghcalltbl",""
.L1943:	.data.w	.L1942
	.endo	.L1943
	.section ".ghrettbl",""
.L1945:	.data.w	.L1944
	.endo	.L1945
	.section ".ghcalltbl",""
.L1947:	.data.w	.L1946
	.endo	.L1947
	.section ".ghrettbl",""
.L1949:	.data.w	.L1948
	.endo	.L1949
	.data
	.global	__caller.Basetimer_Hal_StopTimer.v.p

	.global	__caller.Gtm_Timer_Hal_StopChannel.i.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.global	Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_HWSetTimerInterrupt:
.LDW43:
	push	{r4,lr}
	ldr	r12,.L1235
	cmp	r1,0
.LDW53:
	mov	r1,r2
	ldr	r2,[r12]
	bne	.L1952
	ldr	r2,[r2,20]
	add	r0,r0,r0 lsl 2
	add	r0,r2,r0 lsl 2
.L2070:

	bl	Gtm_Timer_Hal_SetInterrupt
.L2072:

	pop	{r4,pc}
.L1952:
	ldr	r2,[r2,24]
	ldr	r0,[r2,r0 lsl 4]
.L2074:

	bl	Basetimer_Hal_SetInterrupt
	mov	r0,1
.LDW63:
.L2076:

	pop	{r4,pc}
__ghs_eofn_Gpt_HWSetTimerInterrupt:
	.endf	Gpt_HWSetTimerInterrupt
	.endf	Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

.L408:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L408

.L1234:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L1234

.L1235:	.data.w	Gpt_ConfigPtr
	.endo	.L1235

;SafetyFlag	r4	local

;HwCfgMapIndex	r0	param
;HwClass	r3	param
;EnableState	r2	param

	.section ".ghcalltbl",""
.L2071:	.data.w	.L2070
	.endo	.L2071
	.section ".ghrettbl",""
.L2073:	.data.w	.L2072
	.endo	.L2073
	.section ".ghcalltbl",""
.L2075:	.data.w	.L2074
	.endo	.L2075
	.section ".ghrettbl",""
.L2077:	.data.w	.L2076
	.endo	.L2077
	.data
	.global	__caller.Basetimer_Hal_SetInterrupt.v.pi

	.global	__caller.Gtm_Timer_Hal_SetInterrupt.i.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
	.global	Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_PreDefTimerInit:
.LDW73:
	push	{r4,lr}
	sub	sp,sp,16
	ldr	r4,.L1235
.LDW83:
	mov	r0,1
	mvn	r2,0
	mov	r3,0
	stmib	sp,{r0,r2-r3}
	ldr	r0,[r4]
	add	r1,sp,4
	ldr	r0,[r0,36]
.L2129:

	bl	Basetimer_Hal_InitModule
	ldr	r0,[r4]
	ldr	r0,[r0,36]
.L2131:

	bl	Basetimer_Hal_StartTimer
	ldr	r0,[r4]
	add	r1,sp,4
	ldr	r0,[r0,40]
.L2133:

	bl	Basetimer_Hal_InitModule
	ldr	r0,[r4]
	ldr	r0,[r0,40]
.L2135:

	bl	Basetimer_Hal_StartTimer
.LDW93:
	add	sp,sp,16
.L2137:

	pop	{r4,pc}
__ghs_eofn_Gpt_PreDefTimerInit:
	.endf	Gpt_PreDefTimerInit
	.endf	Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;BaseTimerConfig	[sp,4]	local

	.section ".ghcalltbl",""
.L2130:	.data.w	.L2129
	.endo	.L2130
.L2132:	.data.w	.L2131
	.endo	.L2132
.L2134:	.data.w	.L2133
	.endo	.L2134
.L2136:	.data.w	.L2135
	.endo	.L2136
	.section ".ghrettbl",""
.L2138:	.data.w	.L2137
	.endo	.L2138
	.data
	.global	__caller.Basetimer_Hal_StartTimer.v.p

	.global	__caller.Basetimer_Hal_InitModule.v.pp

	.global	__caller.Basetimer_Hal_StartTimer.v.p

	.global	__caller.Basetimer_Hal_InitModule.v.pp

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
	.global	Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_PreDefTimerDeInit:
.LDW04:
	push	{r4,lr}
	ldr	r4,.L1235
.LDW14:
	ldr	r0,[r4]
	ldr	r0,[r0,36]
.L2189:

	bl	Basetimer_Hal_StopTimer
	ldr	r0,[r4]
	ldr	r0,[r0,40]
	pop	{r4,lr}
.L2191:

	b	Basetimer_Hal_StopTimer
.LDW24:
__ghs_eofn_Gpt_PreDefTimerDeInit:
	.endf	Gpt_PreDefTimerDeInit
	.endf	Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.section ".ghcalltbl",""
.L2190:	.data.w	.L2189
	.endo	.L2190
	.section ".ghtailcalltbl",""
	.align	4
.L2192:	.data.w	.L2191
	.endo	.L2192
	.data
	.global	__caller.Basetimer_Hal_StopTimer.v.p

	.global	__caller.Basetimer_Hal_StopTimer.v.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_NormalTimerInit:
.LDW34:
	push	{r4-r10,lr}
	ldr	r7,.L1235
.LDW44:
	mov	r4,1
..gh.beginasm.16:
	.endo	..gh.beginasm.16
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.17:
	.endo	..gh.endasm.17

	mov	r5,r0
;line1456
..lin.36298053..339d0e8d.0_4::
.LDWlin4:
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	ldrb	r8,[r0]
	mov	r6,0
	ldr	r9,[r0,4]
	b	.L2202
.L2201:
	add	r1,r0,r0 lsl 2
	ldr	r0,[r7]
	ldrb	r2,[r9,r1 lsl 2]
	ldr	r3,[r0,16]
	add	r2,r3,r2 lsl 3
	ldr	r3,[r0,r5 lsl 2]
	ldr	r3,[r3,4]
	add	r1,r3,r1 lsl 2
	ldr	r1,[r1,16]
	ldr	r2,[r2,4]
	cmp	r1,0
	bne	.L2203
	ldr	r0,[r0,20]
	add	r1,r2,r2 lsl 2
	add	r0,r0,r1 lsl 2
	add	r1,r0,4
.L2408:

	bl	Gtm_Timer_Hal_InitChannel
	and	r4,r4,r0
	cmp	r4,1
	beq	.L2206
	b	.L2208
.L2203:
	ldr	r0,[r0,24]
	add	r10,r0,r2 lsl 4
	add	r1,r10,4
	ldr	r0,[r10]
.L2410:

	bl	Basetimer_Hal_InitModule
	ldr	r0,[r10]
	mov	r1,0
.L2412:

	bl	Basetimer_Hal_SetInterrupt
.L2206:
	ldr	r1,.L2407
	ldr	r1,[r1,r5 lsl 2]
	lsr	r0,r6,24
	add	r0,r1,r0 lsl 3
	mov	r1,0
	str	r1,[r0,4]
	strb	r1,[r0]
	add	r6,r6,1<<24
	strb	r1,[r0,1]
.L2202:
	lsr	r0,r6,24
	cmp	r0,r8
	blo	.L2201
.L2208:
	mov	r0,r4
.LDW54:
.L2414:

	pop	{r4-r10,pc}
__ghs_eofn_Gpt_NormalTimerInit:
	.endf	Gpt_NormalTimerInit
	.endf	Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;MaxChannel	r8	local
;CoreId	r5	local
;ChannelConfigPtr	r9	local
;ChannelStatusPtr	r0	local
;BaseTimerConfigPtr	r10	local
;HwCfgIndex	r2	local
;SafetyFlag	r4	local

	.section ".ghcalltbl",""
.L2409:	.data.w	.L2408
	.endo	.L2409
.L2411:	.data.w	.L2410
	.endo	.L2411
.L2413:	.data.w	.L2412
	.endo	.L2413
	.section ".ghrettbl",""
.L2415:	.data.w	.L2414
	.endo	.L2415
	.data
	.global	__caller.Basetimer_Hal_SetInterrupt.v.pi

	.global	__caller.Basetimer_Hal_InitModule.v.pp

	.global	__caller.Gtm_Timer_Hal_InitChannel.i.pp

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
	.global	Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.:
Gpt_NormalTimerDeInit:
.LDW64:
	push	{r2,r4-r7,lr}
	ldr	r5,.L2547
.LDW74:
	b	.L2548

.L2407:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L2407

.L2547:	.data.w	Gpt_ConfigPtr
	.endo	.L2547

.L2548:

;line1542
..lin.36298053..82bca676.0_5::
.LDWlin5:
..gh.beginasm.19:
	.endo	..gh.beginasm.19
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.20:
	.endo	..gh.endasm.20

	ldr	r7,[r5]
;line1544
..lin.36298053..82bca676.0_6::
.LDWlin6:
	ldr	r7,[r7,r0 lsl 2]
	mov	r4,r0
	mov	r6,0
	ldrb	r7,[r7]
	b	.L2425
.L2424:
	ldr	r1,[r5]
	ldr	r3,[r1,r4 lsl 2]
	add	r0,r0,r0 lsl 2
	ldr	r3,[r3,4]
	ldr	r12,[r1,16]
	ldrb	r2,[r3,r0 lsl 2]
	add	r0,r3,r0 lsl 2
	ldr	r0,[r0,16]
	add	r2,r12,r2 lsl 3
	ldr	r2,[r2,4]
	cmp	r0,0
	ldreq	r1,[r1,20]
	addeq	r0,r2,r2 lsl 2
	addeq	r0,r1,r0 lsl 2
.L2550:

	bleq	Gtm_Timer_Hal_DeinitChannel
	ldr	r1,.L2549
	ldr	r1,[r1,r4 lsl 2]
	lsr	r0,r6,24
	add	r0,r1,r0 lsl 3
	mov	r1,0
	str	r1,[r0,4]
	strb	r1,[r0]
	add	r6,r6,1<<24
	strb	r1,[r0,1]
.L2425:
	lsr	r0,r6,24
	cmp	r0,r7
	blo	.L2424
.LDW84:
.L2552:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Gpt_NormalTimerDeInit:
	.endf	Gpt_NormalTimerDeInit
	.endf	Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
;MaxChannel	r7	local
;HwCfgMapIndex	r2	local
;CoreId	r4	local
;ChannelStatusPtr	r0	local

	.section ".ghcalltbl",""
.L2551:	.data.w	.L2550
	.endo	.L2551
	.section ".ghrettbl",""
.L2553:	.data.w	.L2552
	.endo	.L2553
	.data
	.global	__caller.Gtm_Timer_Hal_DeinitChannel.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
__callee.Gpt_GetVersionInfo.v.p::
	.size	__callee.Gpt_GetVersionInfo.v.p,0
Gpt_GetVersionInfo::
.LDW94:
.LDW05:
	movs	r2,r0
	moveq	r3,22
	moveq	r1,r0
	moveq	r0,100
.L2635:

	beq	Det_ReportError
.L2556:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,100
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW15:
.L2637:

	ret	
__ghs_eofn_Gpt_GetVersionInfo::
	.endf	Gpt_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L2597:
	.endo	.L2597
	.section ".ghtailcalltbl",""
.L2636:	.data.w	.L2635
	.endo	.L2636
	.section ".ghrettbl",""
.L2638:	.data.w	.L2637
	.endo	.L2638
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.22:
	.endo	..gh.f.a.1.e.22
__callee.Gpt_Init.v.p::
	.size	__callee.Gpt_Init.v.p,0
Gpt_Init::
.LDW25:
	push	{r4-r5,r7-r9,lr}
.LDW35:
	mov	r5,1
	b	.L2900

.L2549:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L2549

.L2900:

;line1964
..lin.36298053..c4e75343.0_7::
.LDWlin7:
..gh.beginasm.23:
	.endo	..gh.beginasm.23
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.24:
	.endo	..gh.endasm.24

;line1967
..lin.36298053..c4e75343.0_8::
.LDWlin8:
	mov	r1,r4
	mov	r9,r0
.L2904:

	bl	Gpt_InitDetCheck
	subs	r8,r0,0
.L2906:

	popne	{r4-r5,r7-r9,pc}
	ldr	r0,.L2901
	str	r9,[r0]
	mov	r0,r5
.L2908:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2647
	ldr	r7,.L2902
	ldr	r0,[r7]
	tst	r0,1
	orreq	r0,r0,1
	streq	r0,[r7]
.L2910:

	bleq	Gpt_PreDefTimerInit
	ldr	r1,[r7]
	add	r2,r4,1
	orr	r1,r1,r5 lsl r2
	mov	r0,r5
	str	r1,[r7]
.L2912:

	bl	Mcal_ReleaseLock
	b	.L2651
.L2647:
	mov	r3,160
	mov	r2,r5
	mov	r1,0
	mov	r0,100
.L2914:

	bl	Det_ReportRuntimeError
	mov	r8,r5
.L2651:
	ldr	r0,[r9,r4 lsl 2]
	cmp	r0,0
	beq	.L2645
	cmp	r8,0
	bne	.L2645
.L2916:

	bl	Gpt_NormalTimerInit
	and	r5,r5,r0
	ldr	r0,.L2903
	mov	r1,1
	ldr	r0,[r0,r4 lsl 2]
	stm	r0,{r1,r8}
.L2645:
	movs	r1,r5
	moveq	r3,226
	moveq	r2,1
	moveq	r0,100
.L2918:

	bleq	Det_ReportRuntimeError
.LDW45:
.L2920:

	pop	{r4-r5,r7-r9,pc}
__ghs_eofn_Gpt_Init::
	.endf	Gpt_Init
;CoreId	r4	local
;ErrValue	r8	local
;SafetyFlag	r5	local

;ConfigPtr	r9	param

	.section ".mcal_bss_asil_d_32","awb"
	.align	4
Gpt_PredefTimerStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.::
Gpt_PredefTimerStatus:	.space	4
	.endo	Gpt_PredefTimerStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.endo	Gpt_PredefTimerStatus
	.section ".ghcalltbl",""
.L2905:	.data.w	.L2904
	.endo	.L2905
	.section ".ghrettbl",""
.L2907:	.data.w	.L2906
	.endo	.L2907
	.section ".ghcalltbl",""
.L2909:	.data.w	.L2908
	.endo	.L2909
.L2911:	.data.w	.L2910
	.endo	.L2911
.L2913:	.data.w	.L2912
	.endo	.L2913
.L2915:	.data.w	.L2914
	.endo	.L2915
.L2917:	.data.w	.L2916
	.endo	.L2917
.L2919:	.data.w	.L2918
	.endo	.L2919
	.section ".ghrettbl",""
.L2921:	.data.w	.L2920
	.endo	.L2921
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Mcal_GetLock.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.25:
	.endo	..gh.f.a.1.e.25
__callee.Gpt_DeInit.v.v::
	.size	__callee.Gpt_DeInit.v.v,0
Gpt_DeInit::
.LDW55:
	push	{r4,r6-r7,lr}
.LDW65:
	b	.L3101

.L2901:	.data.w	Gpt_ConfigPtr
	.endo	.L2901

.L2902:	.data.w	Gpt_PredefTimerStatus
	.endo	.L2902

.L2903:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L2903

.L3101:

;line2083
..lin.36298053..8faaf0ac.0_9::
.LDWlin9:
..gh.beginasm.26:
	.endo	..gh.beginasm.26
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.27:
	.endo	..gh.endasm.27

;line2085
..lin.36298053..8faaf0ac.0_10::
.LDWlin10:
	mov	r0,r4
.L3104:

	bl	Gpt_DeInitCheck
	cmp	r0,0
.L3106:

	popne	{r4,r6-r7,pc}
.L3108:

	bl	Gpt_NormalTimerDeInit
	mov	r0,1
.L3110:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2930
	ldr	r6,.L3102
	add	r1,r4,1
	mov	r0,1
	lsl	r2,r0,r1
	ldr	r1,[r6]
	bic	r1,r1,r2
	str	r1,[r6]
.L3112:

	bl	Mcal_ReleaseLock
	ldr	r0,[r6]
	mov	r7,0
	tst	r0,30
	bne	.L2936
.L3114:

	bl	Gpt_PreDefTimerDeInit
	str	r7,[r6]
.L2936:
	ldr	r0,.L3103
	mov	r1,r7
	ldr	r0,[r0,r4 lsl 2]
	stm	r0,{r1,r7}
.L3116:

	pop	{r4,r6-r7,pc}
.L2930:
	mov	r3,160
	mov	r2,2
	mov	r1,0
	mov	r0,100
.L3118:

	bl	Det_ReportRuntimeError
.LDW75:
.L3120:

	pop	{r4,r6-r7,pc}
__ghs_eofn_Gpt_DeInit::
	.endf	Gpt_DeInit
;CoreId	r4	local

	.section ".ghcalltbl",""
.L3105:	.data.w	.L3104
	.endo	.L3105
	.section ".ghrettbl",""
.L3107:	.data.w	.L3106
	.endo	.L3107
	.section ".ghcalltbl",""
.L3109:	.data.w	.L3108
	.endo	.L3109
.L3111:	.data.w	.L3110
	.endo	.L3111
.L3113:	.data.w	.L3112
	.endo	.L3113
.L3115:	.data.w	.L3114
	.endo	.L3115
	.section ".ghrettbl",""
.L3117:	.data.w	.L3116
	.endo	.L3117
	.section ".ghcalltbl",""
.L3119:	.data.w	.L3118
	.endo	.L3119
	.section ".ghrettbl",""
.L3121:	.data.w	.L3120
	.endo	.L3121
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Mcal_GetLock.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.28:
	.endo	..gh.f.a.1.e.28
__callee.Gpt_GetTimeElapsed.i.i::
	.size	__callee.Gpt_GetTimeElapsed.i.i,0
Gpt_GetTimeElapsed::
.LDW85:
	push	{r2,r4-r5,lr}
.LDW95:
	mov	r4,0
	mov	r5,r0
	mov	r1,3
.L3365:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
	bne	.L3124
	b	.L3363

.L3102:	.data.w	Gpt_PredefTimerStatus
	.endo	.L3102

.L3103:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L3103

.L3363:

;line2193
..lin.36298053..af79e3dc.0_11::
.LDWlin11:
..gh.beginasm.29:
	.endo	..gh.beginasm.29
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.30:
	.endo	..gh.endasm.30

;line2195
..lin.36298053..af79e3dc.0_12::
.LDWlin12:
	ldr	r0,.L3364
	ldr	r3,[r0]
	ldr	r1,[r3,16]
	ldr	r2,[r3,r2 lsl 2]
	add	r0,r1,r5 lsl 3
	ldrb	r1,[r0,1]
	ldr	r2,[r2,4]
	add	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 2
	ldr	r1,[r1,16]
	ldr	r0,[r0,4]
	cmp	r1,1
	blo	.L3131
	bne	.L3124
	ldr	r1,[r3,24]
	ldr	r0,[r1,r0 lsl 4]
.L3367:

	bl	Basetimer_Hal_GetElapsedCount
	b	.L3356
.L3131:
	ldr	r1,[r3,20]
	add	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 2
	mov	r1,r4
.L3369:

	bl	Gtm_Timer_Hal_GetChannelInfo
.L3356:

	mov	r4,r0
.L3124:
	mov	r0,r4
.LDW06:
.L3371:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_GetTimeElapsed::
	.endf	Gpt_GetTimeElapsed
;HwCfgMapIndex	r0	local
;TimeElapsed	r4	local
;ChInCoreIndex	r1	local

;Channel	r5	param

	.section ".ghcalltbl",""
.L3366:	.data.w	.L3365
	.endo	.L3366
.L3368:	.data.w	.L3367
	.endo	.L3368
.L3370:	.data.w	.L3369
	.endo	.L3370
	.section ".ghrettbl",""
.L3372:	.data.w	.L3371
	.endo	.L3372
	.data
	.global	__caller.Basetimer_Hal_GetElapsedCount.i.p

	.global	__caller.Gtm_Timer_Hal_GetChannelInfo.i.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.31:
	.endo	..gh.f.a.1.e.31
__callee.Gpt_GetTimeRemaining.i.i::
	.size	__callee.Gpt_GetTimeRemaining.i.i,0
Gpt_GetTimeRemaining::
.LDW16:
	push	{r2,r4-r5,lr}
.LDW26:
	mov	r4,0
	mov	r5,r0
	mov	r1,4
.L3605:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
	bne	.L3375
	b	.L3603

.L3364:	.data.w	Gpt_ConfigPtr
	.endo	.L3364

.L3603:

;line2293
..lin.36298053..6214cb98.0_13::
.LDWlin13:
..gh.beginasm.32:
	.endo	..gh.beginasm.32
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.33:
	.endo	..gh.endasm.33

;line2296
..lin.36298053..6214cb98.0_14::
.LDWlin14:
	ldr	r0,.L3604
	ldr	r3,[r0]
	ldr	r1,[r3,16]
	ldr	r2,[r3,r2 lsl 2]
	add	r0,r1,r5 lsl 3
	ldrb	r1,[r0,1]
	ldr	r2,[r2,4]
	add	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 2
	ldr	r1,[r1,16]
	ldr	r0,[r0,4]
	cmp	r1,1
	blo	.L3382
	bne	.L3375
	ldr	r1,[r3,24]
	ldr	r0,[r1,r0 lsl 4]
.L3607:

	bl	Basetimer_Hal_GetRemainingCount
	b	.L3596
.L3382:
	ldr	r1,[r3,20]
	add	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 2
	mov	r1,1
.L3609:

	bl	Gtm_Timer_Hal_GetChannelInfo
.L3596:

	mov	r4,r0
.L3375:
	mov	r0,r4
.LDW36:
.L3611:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Gpt_GetTimeRemaining::
	.endf	Gpt_GetTimeRemaining
;HwCfgMapIndex	r0	local
;TimeRemaining	r4	local
;ChInCoreIndex	r1	local

;Channel	r5	param

	.section ".ghcalltbl",""
.L3606:	.data.w	.L3605
	.endo	.L3606
.L3608:	.data.w	.L3607
	.endo	.L3608
.L3610:	.data.w	.L3609
	.endo	.L3610
	.section ".ghrettbl",""
.L3612:	.data.w	.L3611
	.endo	.L3612
	.data
	.global	__caller.Basetimer_Hal_GetRemainingCount.i.p

	.global	__caller.Gtm_Timer_Hal_GetChannelInfo.i.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.34:
	.endo	..gh.f.a.1.e.34
__callee.Gpt_StartTimer.v.ii::
	.size	__callee.Gpt_StartTimer.v.ii,0
Gpt_StartTimer::
.LDW46:
	push	{r2,r4-fp,lr}
	mov	fp,r1
.LDW56:
	mov	r9,1
	mov	r7,0
	b	.L3838

.L3604:	.data.w	Gpt_ConfigPtr
	.endo	.L3604

.L3838:

;line2377
..lin.36298053..d96a8e7e.0_15::
.LDWlin15:
..gh.beginasm.35:
	.endo	..gh.beginasm.35
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.36:
	.endo	..gh.endasm.36

;line2380
..lin.36298053..d96a8e7e.0_16::
.LDWlin16:
	mov	r2,r4
	mov	r1,fp
	mov	r6,r0
.L3841:

	bl	Gpt_StartTimerCheck
	cmp	r0,0
.L3843:

	popne	{r2,r4-fp,pc}
	ldr	r5,.L3839
	ldr	r1,[r5]
	ldr	r1,[r1,16]
	add	r0,r1,r6 lsl 3
	ldr	r1,.L3840
	ldrb	r8,[r0,1]
	ldr	r1,[r1,r4 lsl 2]
	ldr	r6,[r0,4]
	add	r10,r1,r8 lsl 3
.L3845:

	bl	SchM_Enter_Gpt_StartTimer
	ldr	r0,[r5]
	ldr	r1,[r0,r4 lsl 2]
	ldr	r1,[r1,4]
	add	r8,r8,r8 lsl 2
	str	r9,[r10,4]
	add	r1,r1,r8 lsl 2
	ldr	r1,[r1,16]
	cmp	r1,1
	blo	.L3622
	bne	.L3628
	ldr	r0,[r0,24]
	mov	r1,fp
	ldr	r0,[r0,r6 lsl 4]
.L3847:

	bl	Basetimer_Hal_SetLoad
	ldr	r0,[r5]
	ldr	r0,[r0,24]
	ldr	r0,[r0,r6 lsl 4]
.L3849:

	bl	Basetimer_Hal_ClearFlag
	ldr	r0,[r5]
	ldr	r0,[r0,24]
	ldr	r0,[r0,r6 lsl 4]
.L3851:

	bl	Basetimer_Hal_StartTimer
	b	.L3628
.L3622:
	ldr	r0,[r0,20]
	add	r1,r6,r6 lsl 2
	lsl	r4,r1,2
	mov	r1,r7
	add	r0,r4,r0
.L3853:

	bl	Gtm_Timer_Hal_SetCounterValue
	mov	r0,r9
.L3855:

	bl	Mcal_GetLock
	subs	r7,r0,0
	bne	.L3628
	ldr	r0,[r5]
	ldr	r0,[r0,20]
	mov	r1,fp
	add	r0,r4,r0
.L3857:

	bl	Gtm_Timer_Hal_StartChannel
	mov	r9,r0
	mov	r0,1
.L3859:

	bl	Mcal_ReleaseLock
.L3628:
.L3861:

	bl	SchM_Exit_Gpt_StartTimer
	cmp	r9,1
	movne	r3,226
	movne	r2,5
	movne	r1,0
	movne	r0,100
.L3863:

	blne	Det_ReportRuntimeError
	cmp	r7,0
	movne	r3,160
	movne	r2,5
	movne	r1,0
	movne	r0,100
.L3865:

	blne	Det_ReportRuntimeError
.LDW66:
.L3867:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Gpt_StartTimer::
	.endf	Gpt_StartTimer
;CoreId	r4	local
;HwCfgMapIndex	r6	local
;ChannelStatusPtr	r10	local
;ChInCoreIndex	r8	local
;SafetyFlag	r9	local
;LockStatus	r7	local

;Channel	r6	param
;Value	fp	param

	.section ".ghcalltbl",""
.L3842:	.data.w	.L3841
	.endo	.L3842
	.section ".ghrettbl",""
.L3844:	.data.w	.L3843
	.endo	.L3844
	.section ".ghcalltbl",""
.L3846:	.data.w	.L3845
	.endo	.L3846
.L3848:	.data.w	.L3847
	.endo	.L3848
.L3850:	.data.w	.L3849
	.endo	.L3850
.L3852:	.data.w	.L3851
	.endo	.L3852
.L3854:	.data.w	.L3853
	.endo	.L3854
.L3856:	.data.w	.L3855
	.endo	.L3856
.L3858:	.data.w	.L3857
	.endo	.L3858
.L3860:	.data.w	.L3859
	.endo	.L3860
.L3862:	.data.w	.L3861
	.endo	.L3862
.L3864:	.data.w	.L3863
	.endo	.L3864
.L3866:	.data.w	.L3865
	.endo	.L3866
	.section ".ghrettbl",""
.L3868:	.data.w	.L3867
	.endo	.L3868
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Gpt_StartTimer.v.v

	.global	__caller.Basetimer_Hal_StartTimer.v.p

	.global	__caller.Basetimer_Hal_ClearFlag.v.p

	.global	__caller.Basetimer_Hal_SetLoad.v.pi

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Gtm_Timer_Hal_StartChannel.i.pi

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.Gtm_Timer_Hal_SetCounterValue.v.pi

	.global	__caller.SchM_Enter_Gpt_StartTimer.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.37:
	.endo	..gh.f.a.1.e.37
__callee.Gpt_StopTimer.v.i::
	.size	__callee.Gpt_StopTimer.v.i,0
Gpt_StopTimer::
.LDW76:
	push	{r4-r10,lr}
.LDW86:
	mov	r6,1
	b	.L4049

.L3839:	.data.w	Gpt_ConfigPtr
	.endo	.L3839

.L3840:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L3840

.L4049:

;line2500
..lin.36298053..6d881b6.0_17::
.LDWlin17:
..gh.beginasm.38:
	.endo	..gh.beginasm.38
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.39:
	.endo	..gh.endasm.39

	mov	r4,r2
;line2503
..lin.36298053..6d881b6.0_18::
.LDWlin18:
	mov	r5,r0
	mov	r1,6
.L4052:

	bl	Gpt_CheckDetErrors
	cmp	r0,0
	ldreq	r10,.L4050
	ldreq	r1,[r10]
	ldreq	r2,.L4051
	ldreq	r1,[r1,16]
	ldreq	r2,[r2,r4 lsl 2]
	addeq	r1,r1,r5 lsl 3
	ldrbeq	r5,[r1,1]
	ldreq	r9,[r1,4]
	addeq	r7,r2,r5 lsl 3
	ldreq	r0,[r7,4]
	cmpeq	r0,1
.L4054:

	popne	{r4-r10,pc}
.L4056:

	bl	SchM_Enter_Gpt_StopTimer
	mov	r0,r6
.L4058:

	bl	Mcal_GetLock
	subs	r8,r0,0
	bne	.L3879
	ldr	r0,[r10]
	ldr	r0,[r0,r4 lsl 2]
	add	r1,r5,r5 lsl 2
	ldr	r0,[r0,4]
	add	r0,r0,r1 lsl 2
	ldr	r1,[r0,16]
	mov	r0,r9
.L4060:

	bl	Gpt_HWStopTimer
	mov	r6,r0
	mov	r0,2
	str	r0,[r7,4]
	mov	r0,1
.L4062:

	bl	Mcal_ReleaseLock
.L3879:
.L4064:

	bl	SchM_Exit_Gpt_StopTimer
	cmp	r6,1
	movne	r3,226
	movne	r2,6
	movne	r1,0
	movne	r0,100
.L4066:

	blne	Det_ReportRuntimeError
	cmp	r8,0
	movne	r3,160
	movne	r2,6
	movne	r1,0
	movne	r0,100
.L4068:

	blne	Det_ReportRuntimeError
.LDW96:
.L4070:

	pop	{r4-r10,pc}
__ghs_eofn_Gpt_StopTimer::
	.endf	Gpt_StopTimer
;HwCfgMapIndex	r9	local
;ChannelStatusPtr	r7	local
;CoreId	r4	local
;ChInCoreIndex	r5	local
;SafetyFlag	r6	local
;LockStatus	r8	local

;Channel	r5	param

	.section ".ghcalltbl",""
.L4053:	.data.w	.L4052
	.endo	.L4053
	.section ".ghrettbl",""
.L4055:	.data.w	.L4054
	.endo	.L4055
	.section ".ghcalltbl",""
.L4057:	.data.w	.L4056
	.endo	.L4057
.L4059:	.data.w	.L4058
	.endo	.L4059
.L4061:	.data.w	.L4060
	.endo	.L4061
.L4063:	.data.w	.L4062
	.endo	.L4063
.L4065:	.data.w	.L4064
	.endo	.L4065
.L4067:	.data.w	.L4066
	.endo	.L4067
.L4069:	.data.w	.L4068
	.endo	.L4069
	.section ".ghrettbl",""
.L4071:	.data.w	.L4070
	.endo	.L4071
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Gpt_StopTimer.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Gpt_StopTimer.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.40:
	.endo	..gh.f.a.1.e.40
__callee.Gpt_GetPredefTimerValue.i.ip::
	.size	__callee.Gpt_GetPredefTimerValue.i.ip,0
Gpt_GetPredefTimerValue::
.LDW07:
	push	{r2,r4-r7,lr}
.LDW17:
	mov	r6,r1
	mov	r5,r0
.L4545:

	bl	Gpt_PredefTimerDetCheck
	subs	r4,r0,0
	bne	.L4074
	b	.L4542

.L4050:	.data.w	Gpt_ConfigPtr
	.endo	.L4050

.L4051:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L4051

.L4542:

;line2605
..lin.36298053..62539483.0_19::
.LDWlin19:
..gh.beginasm.41:
	.endo	..gh.beginasm.41
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.42:
	.endo	..gh.endasm.42

;line2610
..lin.36298053..62539483.0_20::
.LDWlin20:
	ldr	r0,.L4543
	ldr	r0,[r0,r2 lsl 2]
	ldr	r0,[r0]
	cmp	r0,1
	bne	.L4080
	ldr	r7,.L4544
	cmp	r5,3
	beq	.L4091
	ldr	r0,[r7]
	ldr	r0,[r0,36]
.L4547:

	bl	Basetimer_Hal_GetElapsedCount
	cmp	r5,0
	ubfxeq	r0,r0,0,16
	beq	.L4082
	cmp	r5,1
	biceq	r0,r0,255<<24
.L4082:
	str	r0,[r6]
	cmp	r5,3
	bne	.L4074
.L4091:
	ldr	r0,[r7]
	ldr	r0,[r0,40]
.L4549:

	bl	Basetimer_Hal_GetElapsedCount
	str	r0,[r6]
	b	.L4074
.L4080:
	mov	r4,1
.L4074:
	mov	r0,r4
.LDW27:
.L4551:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Gpt_GetPredefTimerValue::
	.endf	Gpt_GetPredefTimerValue
;ErrValue	r4	local
;CounterValue	r0	local

;PredefTimer	r5	param
;TimeValuePtr	r6	param

	.section ".ghcalltbl",""
.L4546:	.data.w	.L4545
	.endo	.L4546
.L4548:	.data.w	.L4547
	.endo	.L4548
.L4550:	.data.w	.L4549
	.endo	.L4550
	.section ".ghrettbl",""
.L4552:	.data.w	.L4551
	.endo	.L4552
	.data
	.global	__caller.Basetimer_Hal_GetElapsedCount.i.p

	.global	__caller.Basetimer_Hal_GetElapsedCount.i.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.43:
	.endo	..gh.f.a.1.e.43
__callee.Gpt_EnableNotification.v.i::
	.size	__callee.Gpt_EnableNotification.v.i,0
Gpt_EnableNotification::
.LDW37:
	push	{r4-r8,lr}
.LDW47:
	b	.L4658

.L4543:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L4543

.L4544:	.data.w	Gpt_ConfigPtr
	.endo	.L4544

.L4658:

;line2699
..lin.36298053..6814399d.0_21::
.LDWlin21:
..gh.beginasm.44:
	.endo	..gh.beginasm.44
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.45:
	.endo	..gh.endasm.45

;line2701
..lin.36298053..6814399d.0_22::
.LDWlin22:
	mov	r1,r4
	mov	r5,r0
.L4661:

	bl	Gpt_EnableNotificationCheck
	cmp	r0,0
.L4663:

	popne	{r4-r8,pc}
	ldr	r6,.L4659
	ldr	r1,[r6]
	ldr	r2,.L4660
	ldr	r1,[r1,16]
	ldr	r2,[r2,r4 lsl 2]
	add	r1,r1,r5 lsl 3
	ldrb	r5,[r1,1]
	ldr	r7,[r1,4]
	add	r8,r2,r5 lsl 3
.L4665:

	bl	SchM_Enter_Gpt_EnableNotification
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	mov	r2,1
	ldr	r0,[r0,4]
	add	r1,r5,r5 lsl 2
	strb	r2,[r8]
	add	r0,r0,r1 lsl 2
	ldr	r1,[r0,16]
	mov	r0,r7
.L4667:

	bl	Gpt_HWSetTimerInterrupt
	mov	r4,r0
.L4669:

	bl	SchM_Exit_Gpt_EnableNotification
	cmp	r4,1
	movne	r3,226
	movne	r2,7
	movne	r1,0
	movne	r0,100
.L4671:

	blne	Det_ReportRuntimeError
.LDW57:
.L4673:

	pop	{r4-r8,pc}
__ghs_eofn_Gpt_EnableNotification::
	.endf	Gpt_EnableNotification
;HwCfgMapIndex	r7	local
;CoreId	r4	local
;ChannelStatusPtr	r8	local
;ChInCoreIndex	r5	local
;SafetyFlag	r4	local

;Channel	r5	param

	.section ".ghcalltbl",""
.L4662:	.data.w	.L4661
	.endo	.L4662
	.section ".ghrettbl",""
.L4664:	.data.w	.L4663
	.endo	.L4664
	.section ".ghcalltbl",""
.L4666:	.data.w	.L4665
	.endo	.L4666
.L4668:	.data.w	.L4667
	.endo	.L4668
.L4670:	.data.w	.L4669
	.endo	.L4670
.L4672:	.data.w	.L4671
	.endo	.L4672
	.section ".ghrettbl",""
.L4674:	.data.w	.L4673
	.endo	.L4674
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Gpt_EnableNotification.v.v

	.global	__caller.SchM_Enter_Gpt_EnableNotification.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.46:
	.endo	..gh.f.a.1.e.46
__callee.Gpt_DisableNotification.v.i::
	.size	__callee.Gpt_DisableNotification.v.i,0
Gpt_DisableNotification::
.LDW67:
	push	{r4-r8,lr}
.LDW77:
	b	.L4770

.L4659:	.data.w	Gpt_ConfigPtr
	.endo	.L4659

.L4660:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L4660

.L4770:

;line2780
..lin.36298053..661b976a.0_23::
.LDWlin23:
..gh.beginasm.47:
	.endo	..gh.beginasm.47
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.48:
	.endo	..gh.endasm.48

;line2783
..lin.36298053..661b976a.0_24::
.LDWlin24:
	mov	r1,r4
	mov	r5,r0
.L4773:

	bl	Gpt_DisableNotificationCheck
	cmp	r0,0
.L4775:

	popne	{r4-r8,pc}
	ldr	r6,.L4771
	ldr	r1,[r6]
	ldr	r2,.L4772
	ldr	r1,[r1,16]
	ldr	r2,[r2,r4 lsl 2]
	add	r1,r1,r5 lsl 3
	ldrb	r5,[r1,1]
	ldr	r8,[r1,4]
	add	r7,r2,r5 lsl 3
.L4777:

	bl	SchM_Enter_Gpt_DisableNotification
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	add	r1,r5,r5 lsl 2
	mov	r2,0
	add	r0,r0,r1 lsl 2
	ldr	r1,[r0,16]
	mov	r0,r8
.L4779:

	bl	Gpt_HWSetTimerInterrupt
	mov	r4,r0
	mov	r0,0
	strb	r0,[r7]
.L4781:

	bl	SchM_Exit_Gpt_DisableNotification
	cmp	r4,1
	movne	r3,226
	movne	r2,8
	movne	r1,0
	movne	r0,100
.L4783:

	blne	Det_ReportRuntimeError
.LDW87:
.L4785:

	pop	{r4-r8,pc}
__ghs_eofn_Gpt_DisableNotification::
	.endf	Gpt_DisableNotification
;CoreId	r4	local
;ChannelStatusPtr	r7	local
;HwCfgMapIndex	r8	local
;ChInCoreIndex	r5	local
;SafetyFlag	r4	local

;Channel	r5	param

	.section ".ghcalltbl",""
.L4774:	.data.w	.L4773
	.endo	.L4774
	.section ".ghrettbl",""
.L4776:	.data.w	.L4775
	.endo	.L4776
	.section ".ghcalltbl",""
.L4778:	.data.w	.L4777
	.endo	.L4778
.L4780:	.data.w	.L4779
	.endo	.L4780
.L4782:	.data.w	.L4781
	.endo	.L4782
.L4784:	.data.w	.L4783
	.endo	.L4784
	.section ".ghrettbl",""
.L4786:	.data.w	.L4785
	.endo	.L4786
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Gpt_DisableNotification.v.v

	.global	__caller.SchM_Enter_Gpt_DisableNotification.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.49:
	.endo	..gh.f.a.1.e.49
__callee.Gpt_Gtm_ISRHandler.v.ii::
	.size	__callee.Gpt_Gtm_ISRHandler.v.ii,0
Gpt_Gtm_ISRHandler::
.LDW97:
	push	{r4-fp,lr}
	sub	sp,sp,12
	mov	r3,r1
	ldr	r7,.L4771
.LDW08:
	mov	r6,1
	b	.L5157

.L4771:	.data.w	Gpt_ConfigPtr
	.endo	.L4771

.L4772:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L4772

.L5157:

;line3151
..lin.36298053..a9b1c742.0_25::
.LDWlin25:
..gh.beginasm.50:
	.endo	..gh.beginasm.50
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.51:
	.endo	..gh.endasm.51

;line3153
..lin.36298053..a9b1c742.0_26::
.LDWlin26:
	ldr	r1,[r7]
	cmp	r1,0
	beq	.L4787
	ldr	r12,.L5158
	ldr	fp,[r12,r4 lsl 2]
	ldr	r2,[fp]
	cmp	r2,1
	bne	.L4787
	ldr	r12,[r1,28]
	add	r2,r3,r0 lsl 4
	uxtb	r2,r2
	ldrb	r2,[r12,r2]
	cmp	r2,255
	beq	.L4787
	ldr	r1,[r1,16]
	ldrb	r2,[r1,r2 lsl 3]!
	cmp	r4,r2
	bne	.L4799
	strb	r0,[sp,5]
	strb	r3,[sp,7]
	mov	r2,0
	strb	r2,[sp,4]
	ldr	r2,.L5159
	ldrb	r5,[r1,1]
	ldr	r2,[r2,r4 lsl 2]
	add	r0,sp,4
	ldr	r8,[r1,4]
	add	r9,r2,r5 lsl 3
.L5160:

	bl	Gtm_Timer_Hal_GetInterruptEnableStatus
	mov	r10,r0
	add	r0,sp,4
.L5162:

	bl	Gtm_Timer_Hal_GetInterruptStatus
	cmp	r10,1
	bne	.L4787
	cmp	r0,1
	bne	.L4793
	add	r0,sp,4
.L5164:

	bl	Gtm_Timer_Hal_ClearInterruptStatus
	ldr	r1,[r7]
	add	r0,r8,r8 lsl 2
	ldr	r1,[r1,20]
	add	r0,r1,r0 lsl 2
	ldrb	r0,[r0,16]
	cmp	r0,1
	bne	.L4804
	mov	r0,3
	str	r0,[r9,4]
	add	r0,sp,4
.L5166:

	bl	Gtm_Timer_Hal_StopChannel
	and	r6,r6,r0
	add	r0,sp,4
.L5168:

	bl	Gtm_Timer_Hal_GetCompareZero
	mov	r1,r0
	add	r0,sp,4
.L5170:

	bl	Gtm_Timer_Hal_SetCounterValue
.L4804:
	ldr	r0,[fp,4]
	cmp	r0,0
	ldrbeq	r0,[r9]
	cmpeq	r0,1
	ldreq	r0,[r7]
	ldreq	r0,[r0,r4 lsl 2]
	addeq	r2,r5,r5 lsl 2
	ldreq	r0,[r0,4]
	addeq	r0,r0,r2 lsl 2
	ldreq	r0,[r0,8]
.L5172:

	blxeq	r0
.L4793:
	cmp	r6,1
	movne	r3,226
	movne	r2,15
	movne	r1,0
	movne	r0,100
.L5174:

	blne	Det_ReportRuntimeError
	b	.L4787
.L4799:
	mov	r3,225
	mov	r2,15
	mov	r1,0
	mov	r0,100
.L5176:

	bl	Det_ReportError
.L4787:
.LDW18:
	add	sp,sp,12
.L5178:

	pop	{r4-fp,pc}
__ghs_eofn_Gpt_Gtm_ISRHandler::
	.endf	Gpt_Gtm_ISRHandler
;HwCfgMapIndex	r8	local
;ChannelStatusPtr	r9	local
;CoreId	r4	local
;ChInCoreIndex	r5	local
;IntStatus	r0	local
;IntEnStatus	r10	local
;HwChannelObject	[sp,4]	local
;LogicChannel	r2	local
;SafetyFlag	r6	local

;ModuleIndex	r0	param
;Channel	r3	param

	.section ".ghcalltbl",""
.L5161:	.data.w	.L5160
	.endo	.L5161
.L5163:	.data.w	.L5162
	.endo	.L5163
.L5165:	.data.w	.L5164
	.endo	.L5165
.L5167:	.data.w	.L5166
	.endo	.L5167
.L5169:	.data.w	.L5168
	.endo	.L5169
.L5171:	.data.w	.L5170
	.endo	.L5171
.L5173:	.data.w	.L5172
	.endo	.L5173
.L5175:	.data.w	.L5174
	.endo	.L5175
.L5177:	.data.w	.L5176
	.endo	.L5177
	.section ".ghrettbl",""
.L5179:	.data.w	.L5178
	.endo	.L5179
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Gtm_Timer_Hal_SetCounterValue.v.pi

	.global	__caller.Gtm_Timer_Hal_GetCompareZero.i.p

	.global	__caller.Gtm_Timer_Hal_StopChannel.i.p

	.global	__caller.Gtm_Timer_Hal_ClearInterruptStatus.v.p

	.global	__caller.Gtm_Timer_Hal_GetInterruptStatus.i.p

	.global	__caller.Gtm_Timer_Hal_GetInterruptEnableStatus.i.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Gpt_ConfigPtr - Gpt_ConfigPtr) +0 == 0
..gh.f.a.1.e.52:
	.endo	..gh.f.a.1.e.52
__callee.Gpt_Basetimer_ISRHandler.v.i::
	.size	__callee.Gpt_Basetimer_ISRHandler.v.i,0
Gpt_Basetimer_ISRHandler::
.LDW28:
	push	{r4-r8,lr}
	ldr	r6,.L5419
.LDW38:
	b	.L5420

.L5158:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L5158

.L5159:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L5159

.L5419:	.data.w	Gpt_ConfigPtr
	.endo	.L5419

.L5420:

;line3285
..lin.36298053..663951b6.0_27::
.LDWlin27:
..gh.beginasm.53:
	.endo	..gh.beginasm.53
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.54:
	.endo	..gh.endasm.54

;line3287
..lin.36298053..663951b6.0_28::
.LDWlin28:
	ldr	r1,[r6]
	cmp	r1,0
	ldrne	r3,.L5421
	ldrne	r7,[r3,r4 lsl 2]
	cmpne	r7,0
.L5423:

	popeq	{r4-r8,pc}
	ldr	r2,[r7]
	cmp	r2,1
.L5425:

	popne	{r4-r8,pc}
	ldr	r2,[r1,32]
	ldrb	r0,[r2,r0]
	cmp	r0,255
.L5427:

	popeq	{r4-r8,pc}
	ldr	r2,[r1,16]
	lsl	r0,r0,3
	ldrb	r2,[r0,r2]!
	cmp	r4,r2
	bne	.L5193
	ldrb	r5,[r0,1]
	ldr	r8,[r0,4]
	ldr	r0,[r1,24]
	ldr	r0,[r0,r8 lsl 4]
.L5429:

	bl	Basetimer_Hal_ClearFlag
	ldr	r1,.L5422
	ldr	r1,[r1,r4 lsl 2]
	add	r0,r1,r5 lsl 3
	ldr	r1,[r6]
	ldr	r2,[r1,24]
	add	r2,r2,r8 lsl 4
	ldr	r2,[r2,12]
	cmp	r2,2
	moveq	r2,3
	streq	r2,[r0,4]
	ldr	r2,[r7,4]
	cmp	r2,0
	ldrbeq	r0,[r0]
	cmpeq	r0,1
	ldreq	r1,[r1,r4 lsl 2]
	addeq	r0,r5,r5 lsl 2
	ldreq	r1,[r1,4]
	addeq	r0,r1,r0 lsl 2
	ldreq	r0,[r0,8]
.L5431:

	blxeq	r0
.L5433:

	pop	{r4-r8,pc}
.L5193:
	mov	r3,225
	mov	r2,160
	mov	r1,0
	mov	r0,100
.L5435:

	bl	Det_ReportError
.LDW48:
.L5437:

	pop	{r4-r8,pc}
__ghs_eofn_Gpt_Basetimer_ISRHandler::
	.endf	Gpt_Basetimer_ISRHandler
;CoreId	r4	local
;HwCfgMapIndex	r0	local
;ChannelStatusPtr	r0	local
;ChInCoreIndex	r5	local
;LogicChannel	r0	local

;HwChannel	r0	param

	.section ".ghrettbl",""
.L5424:	.data.w	.L5423
	.endo	.L5424
.L5426:	.data.w	.L5425
	.endo	.L5426
.L5428:	.data.w	.L5427
	.endo	.L5428
	.section ".ghcalltbl",""
.L5430:	.data.w	.L5429
	.endo	.L5430
.L5432:	.data.w	.L5431
	.endo	.L5432
	.section ".ghrettbl",""
.L5434:	.data.w	.L5433
	.endo	.L5434
	.section ".ghcalltbl",""
.L5436:	.data.w	.L5435
	.endo	.L5436
	.section ".ghrettbl",""
.L5438:	.data.w	.L5437
	.endo	.L5438
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Basetimer_Hal_ClearFlag.v.p

	.section ".mcal_text_asil_d","ax"

.L5421:	.data.w	Gpt_CoreDriverStatusPtr
	.endo	.L5421

.L5422:	.data.w	Gpt_CoreChannelStatusPtr
	.endo	.L5422

;Gpt_ChannelStatusCore0	Gpt_ChannelStatusCore0	static
;Gpt_DriverStatusCore0	Gpt_DriverStatusCore0	static
;Gpt_ChannelStatusCore1	Gpt_ChannelStatusCore1	static
;Gpt_DriverStatusCore1	Gpt_DriverStatusCore1	static
;Gpt_CoreChannelStatusPtr	Gpt_CoreChannelStatusPtr	static
;Gpt_CoreDriverStatusPtr	Gpt_CoreDriverStatusPtr	static
;Gpt_PredefTimerStatus	Gpt_PredefTimerStatus	static
;Gpt_ConfigPtr	Gpt_ConfigPtr	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682572..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	221,31,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,71,112,116,92,115,114,99,47,71,112,116,46,99,0
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
	.data.b	47,15,0,0
	.data.b	2,0
	.data.b	200,7,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,71,112,116,92,115,114,99,47,71,112,116,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,71,112,116,92,105,110,99,108,117,100,101,92,71,112,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,71,112,116,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,71,112,116,92,105,110,99,108,117,100,101,92,71,112,116,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,116,105,109,101,114,92,103,116,109,95,116,105,109,101,114,95,104,97,108,46,104,0
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
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,71,112,116,95,77,101,109,77,97,112,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,98,97,115,101,116,105,109,101,114,92,105,110,99,92,98,97,115,101,116,105,109,101,114,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,98,97,115,101,116,105,109,101,114,92,105,110,99,92,98,97,115,101,116,105,109,101,114,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,66,97,115,101,116,105,109,101,114,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,69,99,117,77,92,69,99,117,77,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,83,116,97,99,107,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,67,111,109,83,116,97,99,107,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,69,99,117,77,92,69,99,117,77,95,69,120,116,101,114,110,97,108,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,71,112,116,92,105,110,99,108,117,100,101,92,71,112,116,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,71,112,116,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,68,101,116,92,105,110,99,108,117,100,101,92,68,101,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,71,112,116,46,104,0
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
	.data.w	.Ldw_begin+1891
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
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
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
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3620

	.section	.debug_abbrev		;off: 48
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 87
	.data.b	53
	.data.w	.Ldw_begin+82

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 92
	.data.b	47
	.data.w	.Ldw_begin+3209

	.data.b	47
	.data.w	.Ldw_begin+1142

	.data.b	53
	.data.w	.Ldw_begin+97

	.data.b	47
	.data.w	.Ldw_begin+102

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+92
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+107
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3870

	.data.b	53
	.data.w	.Ldw_begin+131

	.data.b	47
	.data.w	.Ldw_begin+136

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+141
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1903
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1903
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3387

	.data.b	53
	.data.w	.Ldw_begin+178

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3009
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1903
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1903
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1903
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1142
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3250
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1142
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3250
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1106
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 62
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 297
	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+3387

	.data.b	47
	.data.w	.Ldw_begin+3442

	.data.b	53
	.data.w	.Ldw_begin+313

	.data.b	47
	.data.w	.Ldw_begin+3497

	.data.b	53
	.data.w	.Ldw_begin+323

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1265

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+336
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3009
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3009
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3009
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1142

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3209
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+412
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2997
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 479
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 486
	.data.w	.Ldw_str_begin+260
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 273
	.data.b	105,110,116,0
	.section	.debug_info		;off: 493
	.data.w	.Ldw_str_begin+273
	.data.b	5
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+2673

	.section	.debug_abbrev		;off: 69
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 504
	.data.b	53
	.data.w	.Ldw_begin+2814

	.data.b	47
	.data.w	.Ldw_begin+504

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+514

	.data.b	47
	.data.w	.Ldw_begin+3747

	.data.b	53
	.data.w	.Ldw_begin+522

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+527

	.section	.debug_abbrev		;off: 76
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 539
	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	3

	.section	.debug_abbrev		;off: 87
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 547
	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3692

	.data.b	53
	.data.w	.Ldw_begin+548

	.data.b	47
	.data.w	.Ldw_begin+1118

	.data.b	53
	.data.w	.Ldw_begin+558

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+563

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+509

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	48
	.data.w	.Ldw_begin+3387

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	5

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+3387

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+308

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+632

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+3317

	.data.b	47
	.data.w	.Ldw_begin+653

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+658

	.data.b	56
	.data.w	.Ldw_begin+492
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1528

	.data.b	53
	.data.w	.Ldw_begin+679

	.data.b	47
	.data.w	.Ldw_begin+684

	.data.b	47
	.data.w	.Ldw_begin+1823

	.data.b	53
	.data.w	.Ldw_begin+694

	.data.b	47
	.data.w	.Ldw_begin+699

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+704
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1142
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1724
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1142
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1142
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1142
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1106
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1106
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+689
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2007
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2007
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2973

	.data.b	53
	.data.w	.Ldw_begin+892

	.data.b	47
	.data.w	.Ldw_begin+897

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+902
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1106
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2814

	.data.b	53
	.data.w	.Ldw_begin+937

	.data.b	47
	.data.w	.Ldw_begin+942

	.data.b	74
	.data.w	.Ldw_begin+1142
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+947
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1142
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+947
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+509
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1142
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1130
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1166
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1130
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1118
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

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1107
	.data.w	.Ldw_str_begin+277
	.data.b	51
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+35

	.section	.debug_abbrev		;off: 100
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 1118
	.data.b	45
	.section	.debug_str		;off: 285
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1119
	.data.w	.Ldw_str_begin+285
	.data.b	56
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+35

	.data.b	45
	.section	.debug_str		;off: 291
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1131
	.data.w	.Ldw_str_begin+291
	.data.b	60
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+478

	.data.b	45
	.section	.debug_str		;off: 298
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1143
	.data.w	.Ldw_str_begin+298
	.data.b	64
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 305
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1155
	.data.w	.Ldw_str_begin+305
	.data.b	68
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1167
	.data.w	.Ldw_str_begin+312
	.data.b	39
	.data.b	15
	.data.b	6
	.data.w	.Ldw_begin+1118

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	6
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 115
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 1184
	.data.b	40
	.section	.debug_str		;off: 327
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1185
	.data.w	.Ldw_str_begin+327
	.data.b	63
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1130
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 130
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

	.section	.debug_info		;off: 1200
	.data.b	40
	.section	.debug_str		;off: 336
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1201
	.data.w	.Ldw_str_begin+336
	.data.b	64
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1130
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 345
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1217
	.data.w	.Ldw_str_begin+345
	.data.b	65
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1233
	.data.w	.Ldw_str_begin+362
	.data.b	66
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1249
	.data.w	.Ldw_str_begin+379
	.data.b	67
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 396
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1266
	.data.w	.Ldw_str_begin+396
	.data.b	68
	.data.b	2
	.data.b	6
	.data.w	.Ldw_begin+1178

	.data.b	52
	.section	.debug_str		;off: 416
	.data.b	0
	.section	.debug_info		;off: 1278
	.data.w	.Ldw_str_begin+416
	.data.b	150,1
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 149
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

	.section	.debug_info		;off: 1288
	.data.b	51
	.section	.debug_str		;off: 417
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,76,69,86,69,76,0
	.section	.debug_info		;off: 1289
	.data.w	.Ldw_str_begin+417
	.data.b	151,1
	.data.b	5
	.data.b	14
	.data.b	0

	.section	.debug_abbrev		;off: 166
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 1298
	.data.b	51
	.section	.debug_str		;off: 435
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,0
	.section	.debug_info		;off: 1299
	.data.w	.Ldw_str_begin+435
	.data.b	152,1
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 453
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,78,79,84,73,70,89,0
	.section	.debug_info		;off: 1309
	.data.w	.Ldw_str_begin+453
	.data.b	153,1
	.data.b	5
	.data.b	14
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 477
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,83,73,78,71,76,69,80,85,76,83,69,0
	.section	.debug_info		;off: 1319
	.data.w	.Ldw_str_begin+477
	.data.b	154,1
	.data.b	5
	.data.b	14
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 501
	.data.b	71,116,109,95,73,114,113,77,111,100,101,0
	.section	.debug_info		;off: 1330
	.data.w	.Ldw_str_begin+501
	.data.b	155,1
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+1277

	.data.b	52
	.section	.debug_str		;off: 513
	.data.b	0
	.section	.debug_info		;off: 1343
	.data.w	.Ldw_str_begin+513
	.data.b	159,1
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 514
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,76,79,87,0
	.section	.debug_info		;off: 1354
	.data.w	.Ldw_str_begin+514
	.data.b	160,1
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 534
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,72,73,71,72,0
	.section	.debug_info		;off: 1364
	.data.w	.Ldw_str_begin+534
	.data.b	161,1
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 555
	.data.b	71,116,109,95,83,105,103,110,97,108,83,116,97,116,101,0
	.section	.debug_info		;off: 1375
	.data.w	.Ldw_str_begin+555
	.data.b	162,1
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+1342

	.data.b	52
	.section	.debug_str		;off: 571
	.data.b	0
	.section	.debug_info		;off: 1388
	.data.w	.Ldw_str_begin+571
	.data.b	166,1
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 572
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1399
	.data.w	.Ldw_str_begin+572
	.data.b	167,1
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 592
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,48,0
	.section	.debug_info		;off: 1409
	.data.w	.Ldw_str_begin+592
	.data.b	168,1
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 612
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,49,0
	.section	.debug_info		;off: 1419
	.data.w	.Ldw_str_begin+612
	.data.b	169,1
	.data.b	5
	.data.b	14
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 632
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,65,76,76,0
	.section	.debug_info		;off: 1429
	.data.w	.Ldw_str_begin+632
	.data.b	170,1
	.data.b	5
	.data.b	14
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 651
	.data.b	71,116,109,95,79,109,95,73,114,113,84,121,112,101,0
	.section	.debug_info		;off: 1440
	.data.w	.Ldw_str_begin+651
	.data.b	171,1
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+1387

	.data.b	71
	.data.b	185,1
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 666
	.data.b	109,111,100,117,108,101,0
	.section	.debug_info		;off: 1460
	.data.w	.Ldw_str_begin+666
	.data.b	186,1
	.data.b	14
	.data.b	14
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 673
	.data.b	109,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 1477
	.data.w	.Ldw_str_begin+673
	.data.b	187,1
	.data.b	14
	.data.b	14
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 685
	.data.b	103,114,111,117,112,0
	.section	.debug_info		;off: 1494
	.data.w	.Ldw_str_begin+685
	.data.b	188,1
	.data.b	14
	.data.b	14
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 691
	.data.b	99,104,97,110,110,101,108,0
	.section	.debug_info		;off: 1511
	.data.w	.Ldw_str_begin+691
	.data.b	189,1
	.data.b	14
	.data.b	14
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 699
	.data.b	71,116,109,95,79,117,116,112,117,116,95,68,114,105,118,101,114,0
	.section	.debug_info		;off: 1529
	.data.w	.Ldw_str_begin+699
	.data.b	190,1
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+1452

	.data.b	52
	.section	.debug_str		;off: 717
	.data.b	0
	.section	.debug_info		;off: 1542
	.data.w	.Ldw_str_begin+717
	.data.b	66
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 718
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,70,88,67,76,75,48,0
	.section	.debug_info		;off: 1552
	.data.w	.Ldw_str_begin+718
	.data.b	67
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 746
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,70,88,67,76,75,49,0
	.section	.debug_info		;off: 1561
	.data.w	.Ldw_str_begin+746
	.data.b	68
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 774
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,70,88,67,76,75,50,0
	.section	.debug_info		;off: 1570
	.data.w	.Ldw_str_begin+774
	.data.b	69
	.data.b	5
	.data.b	12
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 802
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,70,88,67,76,75,51,0
	.section	.debug_info		;off: 1579
	.data.w	.Ldw_str_begin+802
	.data.b	70
	.data.b	5
	.data.b	12
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 830
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,70,88,67,76,75,52,0
	.section	.debug_info		;off: 1588
	.data.w	.Ldw_str_begin+830
	.data.b	71
	.data.b	5
	.data.b	12
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 858
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,78,79,67,76,79,67,75,0
	.section	.debug_info		;off: 1597
	.data.w	.Ldw_str_begin+858
	.data.b	72
	.data.b	5
	.data.b	12
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 884
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,83,84,79,80,0
	.section	.debug_info		;off: 1606
	.data.w	.Ldw_str_begin+884
	.data.b	73
	.data.b	5
	.data.b	12
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 907
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,84,82,73,71,79,85,84,0
	.section	.debug_info		;off: 1615
	.data.w	.Ldw_str_begin+907
	.data.b	74
	.data.b	5
	.data.b	12
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 933
	.data.b	71,84,77,95,84,79,77,95,67,72,95,67,76,75,83,82,67,95,69,88,84,84,82,73,71,73,78,0
	.section	.debug_info		;off: 1624
	.data.w	.Ldw_str_begin+933
	.data.b	75
	.data.b	5
	.data.b	12
	.data.b	14

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 961
	.data.b	71,116,109,95,84,111,109,95,67,104,95,67,108,107,83,114,99,0
	.section	.debug_info		;off: 1634
	.data.w	.Ldw_str_begin+961
	.data.b	76
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+1541

	.data.b	52
	.section	.debug_str		;off: 979
	.data.b	0
	.section	.debug_info		;off: 1646
	.data.w	.Ldw_str_begin+979
	.data.b	80
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 980
	.data.b	71,84,77,95,84,79,77,95,67,72,95,84,82,73,71,79,85,84,95,70,79,82,87,65,82,68,0
	.section	.debug_info		;off: 1656
	.data.w	.Ldw_str_begin+980
	.data.b	81
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1007
	.data.b	71,84,77,95,84,79,77,95,67,72,95,84,82,73,71,79,85,84,95,71,69,78,69,82,65,84,69,0
	.section	.debug_info		;off: 1665
	.data.w	.Ldw_str_begin+1007
	.data.b	82
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1035
	.data.b	71,116,109,95,84,111,109,95,67,104,95,84,114,105,103,79,117,116,0
	.section	.debug_info		;off: 1675
	.data.w	.Ldw_str_begin+1035
	.data.b	83
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+1645

	.data.b	52
	.section	.debug_str		;off: 1054
	.data.b	0
	.section	.debug_info		;off: 1687
	.data.w	.Ldw_str_begin+1054
	.data.b	49
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1055
	.data.b	71,84,77,95,84,73,77,69,82,95,67,79,85,78,84,95,85,83,69,68,0
	.section	.debug_info		;off: 1697
	.data.w	.Ldw_str_begin+1055
	.data.b	50
	.data.b	5
	.data.b	11
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1076
	.data.b	71,84,77,95,84,73,77,69,82,95,67,79,85,78,84,95,82,69,77,65,73,78,0
	.section	.debug_info		;off: 1706
	.data.w	.Ldw_str_begin+1076
	.data.b	51
	.data.b	5
	.data.b	11
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1099
	.data.b	71,84,77,95,84,73,77,69,82,95,67,79,85,78,84,95,80,69,82,73,79,68,0
	.section	.debug_info		;off: 1715
	.data.w	.Ldw_str_begin+1099
	.data.b	52
	.data.b	5
	.data.b	11
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1122
	.data.b	71,116,109,95,84,105,109,101,114,95,67,111,117,110,116,0
	.section	.debug_info		;off: 1725
	.data.w	.Ldw_str_begin+1122
	.data.b	53
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1686

	.data.b	71
	.data.b	63
	.data.b	1
	.data.b	11
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1138
	.data.b	99,108,107,0
	.section	.debug_info		;off: 1743
	.data.w	.Ldw_str_begin+1138
	.data.b	64
	.data.b	30
	.data.b	11
	.data.w	.Ldw_begin+1633
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1142
	.data.b	105,114,113,77,111,100,101,0
	.section	.debug_info		;off: 1759
	.data.w	.Ldw_str_begin+1142
	.data.b	65
	.data.b	30
	.data.b	11
	.data.w	.Ldw_begin+1329
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1150
	.data.b	116,114,105,103,79,117,116,0
	.section	.debug_info		;off: 1775
	.data.w	.Ldw_str_begin+1150
	.data.b	66
	.data.b	30
	.data.b	11
	.data.w	.Ldw_begin+1674
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1158
	.data.b	105,115,79,110,101,83,104,111,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 1791
	.data.w	.Ldw_str_begin+1158
	.data.b	67
	.data.b	30
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1174
	.data.b	105,115,73,114,113,69,110,97,98,108,101,0
	.section	.debug_info		;off: 1807
	.data.w	.Ldw_str_begin+1174
	.data.b	68
	.data.b	30
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	2,35
	.data.b	13
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1186
	.data.b	71,116,109,95,84,105,109,101,114,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1824
	.data.w	.Ldw_str_begin+1186
	.data.b	69
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1736

	.data.b	52
	.section	.debug_str		;off: 1203
	.data.b	0
	.section	.debug_info		;off: 1836
	.data.w	.Ldw_str_begin+1203
	.data.b	36
	.data.b	1
	.data.b	24
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1204
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 1846
	.data.w	.Ldw_str_begin+1204
	.data.b	37
	.data.b	5
	.data.b	24
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1221
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 1855
	.data.w	.Ldw_str_begin+1221
	.data.b	38
	.data.b	5
	.data.b	24
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1238
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 1864
	.data.w	.Ldw_str_begin+1238
	.data.b	39
	.data.b	5
	.data.b	24
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1255
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 1873
	.data.w	.Ldw_str_begin+1255
	.data.b	40
	.data.b	5
	.data.b	24
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1272
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 1882
	.data.w	.Ldw_str_begin+1272
	.data.b	41
	.data.b	5
	.data.b	24
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1289
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1892
	.data.w	.Ldw_str_begin+1289
	.data.b	42
	.data.b	3
	.data.b	24
	.data.w	.Ldw_begin+1835

	.data.b	45
	.section	.debug_str		;off: 1301
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 1904
	.data.w	.Ldw_str_begin+1301
	.data.b	32
	.data.b	21
	.data.b	23
	.data.w	.Ldw_begin+1891

	.data.b	52
	.section	.debug_str		;off: 1315
	.data.b	0
	.section	.debug_info		;off: 1916
	.data.w	.Ldw_str_begin+1315
	.data.b	39
	.data.b	1
	.data.b	23
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1316
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 1926
	.data.w	.Ldw_str_begin+1316
	.data.b	41
	.data.b	5
	.data.b	23
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1334
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 1935
	.data.w	.Ldw_str_begin+1334
	.data.b	43
	.data.b	5
	.data.b	23
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1351
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 1944
	.data.w	.Ldw_str_begin+1351
	.data.b	45
	.data.b	5
	.data.b	23
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1369
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 1953
	.data.w	.Ldw_str_begin+1369
	.data.b	47
	.data.b	5
	.data.b	23
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1386
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 1962
	.data.w	.Ldw_str_begin+1386
	.data.b	49
	.data.b	5
	.data.b	23
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1403
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 1971
	.data.w	.Ldw_str_begin+1403
	.data.b	51
	.data.b	5
	.data.b	23
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 1420
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 1980
	.data.w	.Ldw_str_begin+1420
	.data.b	53
	.data.b	5
	.data.b	23
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 1437
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 1989
	.data.w	.Ldw_str_begin+1437
	.data.b	55
	.data.b	5
	.data.b	23
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 1454
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 1998
	.data.w	.Ldw_str_begin+1454
	.data.b	57
	.data.b	5
	.data.b	23
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1471
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 2008
	.data.w	.Ldw_str_begin+1471
	.data.b	58
	.data.b	3
	.data.b	23
	.data.w	.Ldw_begin+1915

	.data.b	71
	.data.b	37
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1487
	.data.b	79,78,69,83,72,79,84,0
	.section	.debug_info		;off: 2026
	.data.w	.Ldw_str_begin+1487
	.data.b	38
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 181
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

	.section	.debug_info		;off: 2044
	.data.b	41
	.section	.debug_str		;off: 1495
	.data.b	83,73,90,69,0
	.section	.debug_info		;off: 2045
	.data.w	.Ldw_str_begin+1495
	.data.b	39
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1500
	.data.b	114,101,115,101,114,118,101,100,95,52,0
	.section	.debug_info		;off: 2064
	.data.w	.Ldw_str_begin+1500
	.data.b	40
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	27
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1511
	.data.b	73,78,84,69,78,0
	.section	.debug_info		;off: 2083
	.data.w	.Ldw_str_begin+1511
	.data.b	41
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1517
	.data.b	77,79,68,69,0
	.section	.debug_info		;off: 2102
	.data.w	.Ldw_str_begin+1517
	.data.b	42
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1522
	.data.b	69,78,0
	.section	.debug_info		;off: 2121
	.data.w	.Ldw_str_begin+1522
	.data.b	43
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1525
	.data.b	80,85,76,83,69,78,0
	.section	.debug_info		;off: 2140
	.data.w	.Ldw_str_begin+1525
	.data.b	44
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1532
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 2159
	.data.w	.Ldw_str_begin+1532
	.data.b	45
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	0
	.data.b	22
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1543
	.data.b	66,65,83,69,84,73,77,69,82,95,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 2179
	.data.w	.Ldw_str_begin+1543
	.data.b	46
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2019

	.data.b	71
	.data.b	50
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1563
	.data.b	67,76,82,0
	.section	.debug_info		;off: 2197
	.data.w	.Ldw_str_begin+1563
	.data.b	51
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1567
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2216
	.data.w	.Ldw_str_begin+1567
	.data.b	52
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1578
	.data.b	66,65,83,69,84,73,77,69,82,95,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 2236
	.data.w	.Ldw_str_begin+1578
	.data.b	53
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2190

	.data.b	71
	.data.b	57
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1597
	.data.b	73,78,84,83,84,83,0
	.section	.debug_info		;off: 2254
	.data.w	.Ldw_str_begin+1597
	.data.b	58
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1604
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2273
	.data.w	.Ldw_str_begin+1604
	.data.b	59
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1615
	.data.b	66,65,83,69,84,73,77,69,82,95,73,83,82,95,66,105,116,115,0
	.section	.debug_info		;off: 2293
	.data.w	.Ldw_str_begin+1615
	.data.b	60
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2247

	.data.b	71
	.data.b	64
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1634
	.data.b	82,73,83,0
	.section	.debug_info		;off: 2311
	.data.w	.Ldw_str_begin+1634
	.data.b	65
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1638
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2330
	.data.w	.Ldw_str_begin+1638
	.data.b	66
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1649
	.data.b	66,65,83,69,84,73,77,69,82,95,82,73,83,95,66,105,116,115,0
	.section	.debug_info		;off: 2350
	.data.w	.Ldw_str_begin+1649
	.data.b	67
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2304

	.data.b	71
	.data.b	71
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1668
	.data.b	72,65,76,84,69,78,0
	.section	.debug_info		;off: 2368
	.data.w	.Ldw_str_begin+1668
	.data.b	72
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1675
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2387
	.data.w	.Ldw_str_begin+1675
	.data.b	73
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+485
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1686
	.data.b	66,65,83,69,84,73,77,69,82,95,72,65,76,84,84,73,77,69,82,95,66,105,116,115,0
	.section	.debug_info		;off: 2407
	.data.w	.Ldw_str_begin+1686
	.data.b	74
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2361

	.data.b	73
	.data.b	81
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 206
	.data.b	73
	.data.b	23
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 2424
	.data.b	40
	.section	.debug_str		;off: 1711
	.data.b	85,0
	.section	.debug_info		;off: 2425
	.data.w	.Ldw_str_begin+1711
	.data.b	82
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1713
	.data.b	66,0
	.section	.debug_info		;off: 2441
	.data.w	.Ldw_str_begin+1713
	.data.b	83
	.data.b	24
	.data.b	40
	.data.w	.Ldw_begin+2235
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1715
	.data.b	66,65,83,69,84,73,77,69,82,95,67,76,82,0
	.section	.debug_info		;off: 2458
	.data.w	.Ldw_str_begin+1715
	.data.b	84
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2418

	.data.b	73
	.data.b	89
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1729
	.data.b	85,0
	.section	.debug_info		;off: 2476
	.data.w	.Ldw_str_begin+1729
	.data.b	90
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1731
	.data.b	66,0
	.section	.debug_info		;off: 2492
	.data.w	.Ldw_str_begin+1731
	.data.b	91
	.data.b	25
	.data.b	40
	.data.w	.Ldw_begin+2178
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1733
	.data.b	66,65,83,69,84,73,77,69,82,95,67,84,82,76,0
	.section	.debug_info		;off: 2509
	.data.w	.Ldw_str_begin+1733
	.data.b	92
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2469

	.data.b	73
	.data.b	97
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1748
	.data.b	85,0
	.section	.debug_info		;off: 2527
	.data.w	.Ldw_str_begin+1748
	.data.b	98
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1750
	.data.b	66,0
	.section	.debug_info		;off: 2543
	.data.w	.Ldw_str_begin+1750
	.data.b	99
	.data.b	24
	.data.b	40
	.data.w	.Ldw_begin+2349
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1752
	.data.b	66,65,83,69,84,73,77,69,82,95,82,73,83,0
	.section	.debug_info		;off: 2560
	.data.w	.Ldw_str_begin+1752
	.data.b	100
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2520

	.data.b	73
	.data.b	105
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1766
	.data.b	85,0
	.section	.debug_info		;off: 2578
	.data.w	.Ldw_str_begin+1766
	.data.b	106
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1768
	.data.b	66,0
	.section	.debug_info		;off: 2594
	.data.w	.Ldw_str_begin+1768
	.data.b	107
	.data.b	24
	.data.b	40
	.data.w	.Ldw_begin+2292
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1770
	.data.b	66,65,83,69,84,73,77,69,82,95,73,83,82,0
	.section	.debug_info		;off: 2611
	.data.w	.Ldw_str_begin+1770
	.data.b	108
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2571

	.data.b	73
	.data.b	113
	.data.b	1
	.data.b	40
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1784
	.data.b	85,0
	.section	.debug_info		;off: 2629
	.data.w	.Ldw_str_begin+1784
	.data.b	114
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1786
	.data.b	66,0
	.section	.debug_info		;off: 2645
	.data.w	.Ldw_str_begin+1786
	.data.b	115
	.data.b	30
	.data.b	40
	.data.w	.Ldw_begin+2406
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1788
	.data.b	66,65,83,69,84,73,77,69,82,95,72,65,76,84,84,73,77,69,82,0
	.section	.debug_info		;off: 2662
	.data.w	.Ldw_str_begin+1788
	.data.b	116
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+2622

	.data.b	71
	.data.b	125
	.data.b	1
	.data.b	40
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1808
	.data.b	76,79,65,68,0
	.section	.debug_info		;off: 2680
	.data.w	.Ldw_str_begin+1808
	.data.b	126
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1813
	.data.b	86,65,76,85,69,0
	.section	.debug_info		;off: 2696
	.data.w	.Ldw_str_begin+1813
	.data.b	127
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1819
	.data.b	67,84,82,76,0
	.section	.debug_info		;off: 2712
	.data.w	.Ldw_str_begin+1819
	.data.b	128,1
	.data.b	20
	.data.b	40
	.data.w	.Ldw_begin+2508
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1824
	.data.b	67,76,82,0
	.section	.debug_info		;off: 2729
	.data.w	.Ldw_str_begin+1824
	.data.b	129,1
	.data.b	19
	.data.b	40
	.data.w	.Ldw_begin+2457
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1828
	.data.b	82,73,83,0
	.section	.debug_info		;off: 2746
	.data.w	.Ldw_str_begin+1828
	.data.b	130,1
	.data.b	19
	.data.b	40
	.data.w	.Ldw_begin+2559
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1832
	.data.b	66,84,73,83,82,0
	.section	.debug_info		;off: 2763
	.data.w	.Ldw_str_begin+1832
	.data.b	131,1
	.data.b	19
	.data.b	40
	.data.w	.Ldw_begin+2610
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1838
	.data.b	66,71,76,79,65,68,0
	.section	.debug_info		;off: 2780
	.data.w	.Ldw_str_begin+1838
	.data.b	132,1
	.data.b	12
	.data.b	40
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1845
	.data.b	72,65,76,84,84,73,77,69,82,0
	.section	.debug_info		;off: 2797
	.data.w	.Ldw_str_begin+1845
	.data.b	133,1
	.data.b	25
	.data.b	40
	.data.w	.Ldw_begin+2661
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1855
	.data.b	66,65,83,69,84,73,77,69,82,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 2815
	.data.w	.Ldw_str_begin+1855
	.data.b	134,1
	.data.b	3
	.data.b	40
	.data.w	.Ldw_begin+499

	.data.b	52
	.section	.debug_str		;off: 1872
	.data.b	0
	.section	.debug_info		;off: 2828
	.data.w	.Ldw_str_begin+1872
	.data.b	44
	.data.b	1
	.data.b	39
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1873
	.data.b	66,65,83,69,84,73,77,69,82,95,77,79,68,69,95,70,82,69,69,82,85,78,78,73,78,71,0
	.section	.debug_info		;off: 2838
	.data.w	.Ldw_str_begin+1873
	.data.b	45
	.data.b	5
	.data.b	39
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1900
	.data.b	66,65,83,69,84,73,77,69,82,95,77,79,68,69,95,80,69,82,73,79,68,73,67,0
	.section	.debug_info		;off: 2847
	.data.w	.Ldw_str_begin+1900
	.data.b	46
	.data.b	5
	.data.b	39
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1924
	.data.b	66,65,83,69,84,73,77,69,82,95,77,79,68,69,95,79,78,69,83,72,79,84,0
	.section	.debug_info		;off: 2856
	.data.w	.Ldw_str_begin+1924
	.data.b	47
	.data.b	5
	.data.b	39
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1947
	.data.b	66,97,115,101,116,105,109,101,114,95,77,111,100,101,0
	.section	.debug_info		;off: 2866
	.data.w	.Ldw_str_begin+1947
	.data.b	48
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+2827

	.data.b	52
	.section	.debug_str		;off: 1962
	.data.b	0
	.section	.debug_info		;off: 2878
	.data.w	.Ldw_str_begin+1962
	.data.b	52
	.data.b	1
	.data.b	39
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1963
	.data.b	66,65,83,69,84,73,77,69,82,95,83,73,90,69,95,49,54,66,73,84,83,0
	.section	.debug_info		;off: 2888
	.data.w	.Ldw_str_begin+1963
	.data.b	53
	.data.b	5
	.data.b	39
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1985
	.data.b	66,65,83,69,84,73,77,69,82,95,83,73,90,69,95,51,50,66,73,84,83,0
	.section	.debug_info		;off: 2897
	.data.w	.Ldw_str_begin+1985
	.data.b	54
	.data.b	5
	.data.b	39
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2007
	.data.b	66,97,115,101,116,105,109,101,114,95,83,105,122,101,0
	.section	.debug_info		;off: 2907
	.data.w	.Ldw_str_begin+2007
	.data.b	55
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+2877

	.data.b	71
	.data.b	65
	.data.b	1
	.data.b	39
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2022
	.data.b	115,105,122,101,0
	.section	.debug_info		;off: 2925
	.data.w	.Ldw_str_begin+2022
	.data.b	66
	.data.b	20
	.data.b	39
	.data.w	.Ldw_begin+2906
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2027
	.data.b	108,111,97,100,0
	.section	.debug_info		;off: 2941
	.data.w	.Ldw_str_begin+2027
	.data.b	67
	.data.b	12
	.data.b	39
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2032
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 2957
	.data.w	.Ldw_str_begin+2032
	.data.b	68
	.data.b	20
	.data.b	39
	.data.w	.Ldw_begin+2865
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2037
	.data.b	66,97,115,101,116,105,109,101,114,95,73,110,105,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2974
	.data.w	.Ldw_str_begin+2037
	.data.b	69
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+2918

	.data.b	45
	.section	.debug_str		;off: 2058
	.data.b	69,99,117,77,95,87,97,107,101,117,112,83,111,117,114,99,101,84,121,112,101,0
	.section	.debug_info		;off: 2986
	.data.w	.Ldw_str_begin+2058
	.data.b	55
	.data.b	16
	.data.b	42
	.data.w	.Ldw_begin+1142

	.data.b	45
	.section	.debug_str		;off: 2080
	.data.b	71,112,116,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 2998
	.data.w	.Ldw_str_begin+2080
	.data.b	62
	.data.b	15
	.data.b	4
	.data.w	.Ldw_begin+1118

	.data.b	45
	.section	.debug_str		;off: 2096
	.data.b	71,112,116,95,86,97,108,117,101,84,121,112,101,0
	.section	.debug_info		;off: 3010
	.data.w	.Ldw_str_begin+2096
	.data.b	65
	.data.b	16
	.data.b	4
	.data.w	.Ldw_begin+1142

	.data.b	52
	.section	.debug_str		;off: 2110
	.data.b	0
	.section	.debug_info		;off: 3022
	.data.w	.Ldw_str_begin+2110
	.data.b	71
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2111
	.data.b	71,80,84,95,85,78,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 3032
	.data.w	.Ldw_str_begin+2111
	.data.b	72
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2129
	.data.b	71,80,84,95,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 3041
	.data.w	.Ldw_str_begin+2129
	.data.b	73
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2145
	.data.b	71,112,116,95,73,110,105,116,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 3051
	.data.w	.Ldw_str_begin+2145
	.data.b	74
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3021

	.data.b	52
	.section	.debug_str		;off: 2163
	.data.b	0
	.section	.debug_info		;off: 3063
	.data.w	.Ldw_str_begin+2163
	.data.b	78
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2164
	.data.b	71,80,84,95,77,79,68,69,95,78,79,82,77,65,76,0
	.section	.debug_info		;off: 3073
	.data.w	.Ldw_str_begin+2164
	.data.b	80
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2180
	.data.b	71,80,84,95,77,79,68,69,95,83,76,69,69,80,0
	.section	.debug_info		;off: 3082
	.data.w	.Ldw_str_begin+2180
	.data.b	83
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2195
	.data.b	71,112,116,95,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 3092
	.data.w	.Ldw_str_begin+2195
	.data.b	84
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+3062

	.data.b	52
	.section	.debug_str		;off: 2208
	.data.b	0
	.section	.debug_info		;off: 3104
	.data.w	.Ldw_str_begin+2208
	.data.b	88
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2209
	.data.b	71,80,84,95,67,72,95,78,79,84,83,84,65,82,84,69,68,0
	.section	.debug_info		;off: 3114
	.data.w	.Ldw_str_begin+2209
	.data.b	89
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2227
	.data.b	71,80,84,95,67,72,95,82,85,78,78,73,78,71,0
	.section	.debug_info		;off: 3123
	.data.w	.Ldw_str_begin+2227
	.data.b	90
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2242
	.data.b	71,80,84,95,67,72,95,83,84,79,80,80,69,68,0
	.section	.debug_info		;off: 3132
	.data.w	.Ldw_str_begin+2242
	.data.b	91
	.data.b	5
	.data.b	4
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2257
	.data.b	71,80,84,95,67,72,95,69,88,80,73,82,69,68,0
	.section	.debug_info		;off: 3141
	.data.w	.Ldw_str_begin+2257
	.data.b	92
	.data.b	5
	.data.b	4
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2272
	.data.b	71,112,116,95,67,104,97,110,110,101,108,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 3151
	.data.w	.Ldw_str_begin+2272
	.data.b	93
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+3103

	.data.b	52
	.section	.debug_str		;off: 2293
	.data.b	0
	.section	.debug_info		;off: 3163
	.data.w	.Ldw_str_begin+2293
	.data.b	97
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2294
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,49,54,66,73,84,0
	.section	.debug_info		;off: 3173
	.data.w	.Ldw_str_begin+2294
	.data.b	98
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2321
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,50,52,66,73,84,0
	.section	.debug_info		;off: 3182
	.data.w	.Ldw_str_begin+2321
	.data.b	99
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2348
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,51,50,66,73,84,0
	.section	.debug_info		;off: 3191
	.data.w	.Ldw_str_begin+2348
	.data.b	100
	.data.b	5
	.data.b	4
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2375
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,48,48,85,83,95,51,50,66,73,84,0
	.section	.debug_info		;off: 3200
	.data.w	.Ldw_str_begin+2375
	.data.b	101
	.data.b	5
	.data.b	4
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2404
	.data.b	71,112,116,95,80,114,101,100,101,102,84,105,109,101,114,84,121,112,101,0
	.section	.debug_info		;off: 3210
	.data.w	.Ldw_str_begin+2404
	.data.b	102
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+3162

	.data.b	52
	.section	.debug_str		;off: 2424
	.data.b	0
	.section	.debug_info		;off: 3222
	.data.w	.Ldw_str_begin+2424
	.data.b	106
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2425
	.data.b	71,80,84,95,72,87,95,71,84,77,0
	.section	.debug_info		;off: 3232
	.data.w	.Ldw_str_begin+2425
	.data.b	107
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2436
	.data.b	71,80,84,95,72,87,95,66,65,83,69,84,73,77,69,82,0
	.section	.debug_info		;off: 3241
	.data.w	.Ldw_str_begin+2436
	.data.b	108
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2453
	.data.b	71,112,116,95,72,87,84,121,112,101,0
	.section	.debug_info		;off: 3251
	.data.w	.Ldw_str_begin+2453
	.data.b	109
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+3221

	.data.b	71
	.data.b	115
	.data.b	1
	.data.b	4
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2464
	.data.b	71,112,116,95,73,110,105,116,83,116,97,116,101,0
	.section	.debug_info		;off: 3269
	.data.w	.Ldw_str_begin+2464
	.data.b	117
	.data.b	26
	.data.b	4
	.data.w	.Ldw_begin+3050
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2478
	.data.b	71,112,116,95,77,111,100,101,83,116,97,116,101,0
	.section	.debug_info		;off: 3285
	.data.w	.Ldw_str_begin+2478
	.data.b	119
	.data.b	26
	.data.b	4
	.data.w	.Ldw_begin+3091
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2492
	.data.b	71,112,116,95,87,97,107,101,117,112,67,104,97,110,110,101,108,73,110,102,111,0
	.section	.debug_info		;off: 3301
	.data.w	.Ldw_str_begin+2492
	.data.b	121
	.data.b	26
	.data.b	4
	.data.w	.Ldw_begin+2985
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2514
	.data.b	71,112,116,95,68,114,105,118,101,114,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 3318
	.data.w	.Ldw_str_begin+2514
	.data.b	122
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3262

	.data.b	71
	.data.b	126
	.data.b	1
	.data.b	4
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2534
	.data.b	78,111,116,105,102,121,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3336
	.data.w	.Ldw_str_begin+2534
	.data.b	128,1
	.data.b	34
	.data.b	4
	.data.w	.Ldw_begin+1106
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2547
	.data.b	87,97,107,101,85,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3353
	.data.w	.Ldw_str_begin+2547
	.data.b	130,1
	.data.b	34
	.data.b	4
	.data.w	.Ldw_begin+1106
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2560
	.data.b	83,116,97,116,117,115,0
	.section	.debug_info		;off: 3370
	.data.w	.Ldw_str_begin+2560
	.data.b	132,1
	.data.b	34
	.data.b	4
	.data.w	.Ldw_begin+3150
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2567
	.data.b	71,112,116,95,67,104,97,110,110,101,108,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 3388
	.data.w	.Ldw_str_begin+2567
	.data.b	133,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3329

	.data.b	71
	.data.b	139,1
	.data.b	1
	.data.b	4
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2589
	.data.b	72,119,67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 3408
	.data.w	.Ldw_str_begin+2589
	.data.b	141,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1528
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2604
	.data.b	72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3425
	.data.w	.Ldw_str_begin+2604
	.data.b	143,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1823
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2620
	.data.b	71,112,116,95,71,116,109,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3443
	.data.w	.Ldw_str_begin+2620
	.data.b	144,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3400

	.data.b	71
	.data.b	150,1
	.data.b	1
	.data.b	4
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2638
	.data.b	72,119,67,104,97,110,110,101,108,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 3463
	.data.w	.Ldw_str_begin+2638
	.data.b	152,1
	.data.b	35
	.data.b	4
	.data.w	.Ldw_begin+509
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2656
	.data.b	72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3480
	.data.w	.Ldw_str_begin+2656
	.data.b	154,1
	.data.b	35
	.data.b	4
	.data.w	.Ldw_begin+2973
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2672
	.data.b	71,112,116,95,66,97,115,101,116,105,109,101,114,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3498
	.data.w	.Ldw_str_begin+2672
	.data.b	155,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3455

	.data.b	71
	.data.b	160,1
	.data.b	1
	.data.b	4
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2696
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 3518
	.data.w	.Ldw_str_begin+2696
	.data.b	162,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2706
	.data.b	87,97,107,101,117,112,69,110,97,98,108,101,0
	.section	.debug_info		;off: 3535
	.data.w	.Ldw_str_begin+2706
	.data.b	164,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2719
	.data.b	77,97,120,84,105,99,107,86,97,108,117,101,0
	.section	.debug_info		;off: 3552
	.data.w	.Ldw_str_begin+2719
	.data.b	166,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2732
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 3569
	.data.w	.Ldw_str_begin+2732
	.data.b	168,1
	.data.b	35
	.data.b	4
	.data.w	.Ldw_begin+517
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2752
	.data.b	71,112,116,67,104,97,110,110,101,108,87,97,107,101,117,112,73,110,102,111,0
	.section	.debug_info		;off: 3586
	.data.w	.Ldw_str_begin+2752
	.data.b	170,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+2985
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2773
	.data.b	72,119,67,108,97,115,115,0
	.section	.debug_info		;off: 3603
	.data.w	.Ldw_str_begin+2773
	.data.b	172,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+3250
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2781
	.data.b	71,112,116,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3621
	.data.w	.Ldw_str_begin+2781
	.data.b	173,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3510

	.data.b	71
	.data.b	179,1
	.data.b	1
	.data.b	4
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2798
	.data.b	67,111,114,101,0
	.section	.debug_info		;off: 3641
	.data.w	.Ldw_str_begin+2798
	.data.b	181,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2803
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 3658
	.data.w	.Ldw_str_begin+2803
	.data.b	183,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1118
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2809
	.data.b	72,119,67,102,103,73,110,100,101,120,0
	.section	.debug_info		;off: 3675
	.data.w	.Ldw_str_begin+2809
	.data.b	185,1
	.data.b	33
	.data.b	4
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2820
	.data.b	71,112,116,95,77,97,112,112,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 3693
	.data.w	.Ldw_str_begin+2820
	.data.b	186,1
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+3633

	.data.b	71
	.data.b	191,1
	.data.b	1
	.data.b	4
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2836
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3713
	.data.w	.Ldw_str_begin+2836
	.data.b	193,1
	.data.b	36
	.data.b	4
	.data.w	.Ldw_begin+2997
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2847
	.data.b	71,112,116,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3730
	.data.w	.Ldw_str_begin+2847
	.data.b	195,1
	.data.b	36
	.data.b	4
	.data.w	.Ldw_begin+87
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2868
	.data.b	71,112,116,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3748
	.data.w	.Ldw_str_begin+2868
	.data.b	196,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3705

	.data.b	71
	.data.b	201,1
	.data.b	1
	.data.b	4
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2887
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3768
	.data.w	.Ldw_str_begin+2887
	.data.b	203,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+532
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2901
	.data.b	71,112,116,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,0
	.section	.debug_info		;off: 3785
	.data.w	.Ldw_str_begin+2901
	.data.b	205,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+553
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2921
	.data.b	71,112,116,72,119,71,116,109,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3802
	.data.w	.Ldw_str_begin+2921
	.data.b	207,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+318
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2939
	.data.b	71,112,116,72,119,66,97,115,101,84,105,109,101,114,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3819
	.data.w	.Ldw_str_begin+2939
	.data.b	209,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+328
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2963
	.data.b	71,112,116,72,119,67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 3836
	.data.w	.Ldw_str_begin+2963
	.data.b	212,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+568
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2982
	.data.b	71,112,116,80,114,101,100,101,102,84,105,109,101,114,80,116,114,0
	.section	.debug_info		;off: 3853
	.data.w	.Ldw_str_begin+2982
	.data.b	215,1
	.data.b	50
	.data.b	4
	.data.w	.Ldw_begin+584
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3000
	.data.b	71,112,116,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3871
	.data.w	.Ldw_str_begin+3000
	.data.b	216,1
	.data.b	2
	.data.b	4
	.data.w	.Ldw_begin+3760

	.data.b	6
	.section	.debug_str		;off: 3015
	.data.b	71,112,116,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3884
	.data.w	.Ldw_str_begin+3015
	.data.b	170,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+600
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.section	.debug_abbrev		;off: 221
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

	.section	.debug_info		;off: 3904
	.data.b	6
	.section	.debug_str		;off: 3038
	.data.b	71,112,116,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3905
	.data.w	.Ldw_str_begin+3038
	.data.b	172,1
	.data.b	55
	.data.b	1
	.data.w	.Ldw_begin+3317
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3060
	.data.b	71,112,116,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3926
	.data.w	.Ldw_str_begin+3060
	.data.b	189,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+616
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3083
	.data.b	71,112,116,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3947
	.data.w	.Ldw_str_begin+3083
	.data.b	191,1
	.data.b	55
	.data.b	1
	.data.w	.Ldw_begin+3317
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3105
	.data.b	71,112,116,95,67,111,114,101,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3968
	.data.w	.Ldw_str_begin+3105
	.data.b	248,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+637
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3130
	.data.b	71,112,116,95,67,111,114,101,68,114,105,118,101,114,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3989
	.data.w	.Ldw_str_begin+3130
	.data.b	156,2
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+663
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3154
	.data.b	71,112,116,95,80,114,101,100,101,102,84,105,109,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 4010
	.data.w	.Ldw_str_begin+3154
	.data.b	199,2
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_PredefTimerStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	6
	.section	.debug_str		;off: 3176
	.data.b	71,112,116,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4031
	.data.w	.Ldw_str_begin+3176
	.data.b	213,2
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+136
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Gpt_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.

	.data.b	27
	.section	.debug_str		;off: 3190
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4052
	.data.w	.Ldw_str_begin+3190
	.data.b	108
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 242
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

	.section	.debug_info		;off: 4069
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3216
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,68,101,105,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4071
	.data.w	.Ldw_str_begin+3216
	.data.b	124
	.data.b	13
	.data.b	11
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 269
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

	.section	.debug_info		;off: 4084
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3244
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,71,101,116,67,104,97,110,110,101,108,73,110,102,111,0
	.section	.debug_info		;off: 4086
	.data.w	.Ldw_str_begin+3244
	.data.b	141,1
	.data.b	15
	.data.b	11
	.data.w	.Ldw_begin+1142
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3273
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,83,116,97,114,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4106
	.data.w	.Ldw_str_begin+3273
	.data.b	159,1
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3300
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,83,116,111,112,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4126
	.data.w	.Ldw_str_begin+3300
	.data.b	176,1
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3326
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,83,101,116,67,111,117,110,116,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4146
	.data.w	.Ldw_str_begin+3326
	.data.b	193,1
	.data.b	13
	.data.b	11
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3356
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,71,101,116,67,111,109,112,97,114,101,90,101,114,111,0
	.section	.debug_info		;off: 4162
	.data.w	.Ldw_str_begin+3356
	.data.b	225,1
	.data.b	15
	.data.b	11
	.data.w	.Ldw_begin+1142
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3385
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,83,101,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 4182
	.data.w	.Ldw_str_begin+3385
	.data.b	243,1
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3412
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 4202
	.data.w	.Ldw_str_begin+3412
	.data.b	131,2
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3445
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,69,110,97,98,108,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 4222
	.data.w	.Ldw_str_begin+3445
	.data.b	147,2
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+1106
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3484
	.data.b	71,116,109,95,84,105,109,101,114,95,72,97,108,95,67,108,101,97,114,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 4242
	.data.w	.Ldw_str_begin+3484
	.data.b	163,2
	.data.b	13
	.data.b	11
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3519
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 4258
	.data.w	.Ldw_str_begin+3519
	.data.b	63
	.data.b	31
	.data.b	24
	.data.w	.Ldw_begin+1891
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.section	.debug_abbrev		;off: 294
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 4276
	.data.b	8
	.section	.debug_str		;off: 3539
	.data.b	105,100,0
	.section	.debug_info		;off: 4277
	.data.w	.Ldw_str_begin+3539
	.data.b	65
	.data.b	17
	.data.b	24
	.data.w	.Ldw_begin+1891
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 299
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

	.section	.debug_info		;off: 4290
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3542
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 4293
	.data.w	.Ldw_str_begin+3542
	.data.b	131,2
	.data.b	48
	.data.b	21
	.data.w	.Ldw_begin+1166
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3555
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 4313
	.data.w	.Ldw_str_begin+3555
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

	.data.b	26
	.section	.debug_str		;off: 3572
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 4329
	.data.w	.Ldw_str_begin+3572
	.data.b	95
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3597
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,83,101,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 4344
	.data.w	.Ldw_str_begin+3597
	.data.b	112
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3624
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,71,101,116,82,101,109,97,105,110,105,110,103,67,111,117,110,116,0
	.section	.debug_info		;off: 4359
	.data.w	.Ldw_str_begin+3624
	.data.b	127
	.data.b	15
	.data.b	39
	.data.w	.Ldw_begin+1142
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3656
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,71,101,116,69,108,97,112,115,101,100,67,111,117,110,116,0
	.section	.debug_info		;off: 4378
	.data.w	.Ldw_str_begin+3656
	.data.b	142,1
	.data.b	15
	.data.b	39
	.data.w	.Ldw_begin+1142
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3686
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,83,116,111,112,84,105,109,101,114,0
	.section	.debug_info		;off: 4398
	.data.w	.Ldw_str_begin+3686
	.data.b	175,1
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3710
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,83,116,97,114,116,84,105,109,101,114,0
	.section	.debug_info		;off: 4414
	.data.w	.Ldw_str_begin+3710
	.data.b	191,1
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3735
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,67,108,101,97,114,70,108,97,103,0
	.section	.debug_info		;off: 4430
	.data.w	.Ldw_str_begin+3735
	.data.b	206,1
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3759
	.data.b	66,97,115,101,116,105,109,101,114,95,72,97,108,95,83,101,116,76,111,97,100,0
	.section	.debug_info		;off: 4446
	.data.w	.Ldw_str_begin+3759
	.data.b	223,1
	.data.b	13
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3781
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 4462
	.data.w	.Ldw_str_begin+3781
	.data.b	105
	.data.b	39
	.data.b	48
	.data.w	.Ldw_begin+1166
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3797
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 4481
	.data.w	.Ldw_str_begin+3797
	.data.b	113
	.data.b	39
	.data.b	48
	.data.w	.Ldw_begin+1166
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3820
	.data.b	83,99,104,77,95,69,110,116,101,114,95,71,112,116,95,83,116,97,114,116,84,105,109,101,114,0
	.section	.debug_info		;off: 4500
	.data.w	.Ldw_str_begin+3820
	.data.b	29
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3846
	.data.b	83,99,104,77,95,69,120,105,116,95,71,112,116,95,83,116,97,114,116,84,105,109,101,114,0
	.section	.debug_info		;off: 4515
	.data.w	.Ldw_str_begin+3846
	.data.b	34
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3871
	.data.b	83,99,104,77,95,69,110,116,101,114,95,71,112,116,95,83,116,111,112,84,105,109,101,114,0
	.section	.debug_info		;off: 4530
	.data.w	.Ldw_str_begin+3871
	.data.b	39
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3896
	.data.b	83,99,104,77,95,69,120,105,116,95,71,112,116,95,83,116,111,112,84,105,109,101,114,0
	.section	.debug_info		;off: 4545
	.data.w	.Ldw_str_begin+3896
	.data.b	44
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3920
	.data.b	83,99,104,77,95,69,110,116,101,114,95,71,112,116,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 4560
	.data.w	.Ldw_str_begin+3920
	.data.b	49
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3954
	.data.b	83,99,104,77,95,69,120,105,116,95,71,112,116,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 4575
	.data.w	.Ldw_str_begin+3954
	.data.b	54
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3987
	.data.b	83,99,104,77,95,69,110,116,101,114,95,71,112,116,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 4590
	.data.w	.Ldw_str_begin+3987
	.data.b	59
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 4022
	.data.b	83,99,104,77,95,69,120,105,116,95,71,112,116,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 4605
	.data.w	.Ldw_str_begin+4022
	.data.b	64
	.data.b	13
	.data.b	49
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4056
	.data.b	71,112,116,95,67,104,101,99,107,68,101,116,69,114,114,111,114,115,0
	.section	.debug_info		;off: 4620
	.data.w	.Ldw_str_begin+4056
	.data.b	241,3
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_CheckDetErrors
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

	.section	.debug_abbrev		;off: 318
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
	.data.w	Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_CheckDetErrors-Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2002
	.data.b	0,5,2
	.data.w	Gpt_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	245,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	13
	.data.b	29
	.data.b	91
	.data.b	12
	.data.b	91
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	139
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	11
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
	.section	.debug_info		;off: 4655
	.data.b	22
	.section	.debug_str		;off: 4075
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4656
	.data.w	.Ldw_str_begin+4075
	.data.b	243,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
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

	.section	.debug_abbrev		;off: 366
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

	.section	.debug_info		;off: 4673
	.data.b	22
	.section	.debug_str		;off: 4088
	.data.b	65,112,105,83,105,100,0
	.section	.debug_info		;off: 4674
	.data.w	.Ldw_str_begin+4088
	.data.b	244,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW01
	.data.w	.LDW11
	.data.b	1,0
	.data.b	81
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4691
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 385
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 4700
	.data.b	7
	.section	.debug_str		;off: 4095
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4701
	.data.w	.Ldw_str_begin+4095
	.data.b	248,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+49
	.section	.debug_loc		;off: 49
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 394
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

	.section	.debug_info		;off: 4719
	.data.b	7
	.section	.debug_str		;off: 4104
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4720
	.data.w	.Ldw_str_begin+4104
	.data.b	249,3
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4738
	.data.b	8
	.section	.debug_str		;off: 4111
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4739
	.data.w	.Ldw_str_begin+4111
	.data.b	250,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4125
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4754
	.data.w	.Ldw_str_begin+4125
	.data.b	251,3
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+87
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4142
	.data.b	71,112,116,95,80,114,101,100,101,102,84,105,109,101,114,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4771
	.data.w	.Ldw_str_begin+4142
	.data.b	186,4
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PredefTimerDetCheck
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PredefTimerDetCheck-Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2064
	.data.b	0,5,2
	.data.w	Gpt_PredefTimerDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	190,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	96
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	31
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	111
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	32
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4806
	.data.b	22
	.section	.debug_str		;off: 4166
	.data.b	80,114,101,100,101,102,84,105,109,101,114,0
	.section	.debug_info		;off: 4807
	.data.w	.Ldw_str_begin+4166
	.data.b	188,4
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+92
	.data.b	0
	.data.w	.Ldw_loc_begin+87
	.section	.debug_loc		;off: 87
	.data.w	.LDW31
	.data.w	.LDW41
	.data.b	1,0
	.data.b	80
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4824
	.data.b	22
	.section	.debug_str		;off: 4178
	.data.b	84,105,109,101,86,97,108,117,101,80,116,114,0
	.section	.debug_info		;off: 4825
	.data.w	.Ldw_str_begin+4178
	.data.b	189,4
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+107
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW31
	.data.w	.LDW41
	.data.b	1,0
	.data.b	81
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4842
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 4191
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4852
	.data.w	.Ldw_str_begin+4191
	.data.b	193,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+147
	.section	.debug_loc		;off: 147
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4870
	.data.b	8
	.section	.debug_str		;off: 4200
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4871
	.data.w	.Ldw_str_begin+4200
	.data.b	194,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4207
	.data.b	71,112,116,95,73,110,105,116,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4888
	.data.w	.Ldw_str_begin+4207
	.data.b	148,5
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_InitDetCheck
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_InitDetCheck-Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2167
	.data.b	0,5,2
	.data.w	Gpt_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	152,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	29
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	43
	.data.b	59
	.data.b	12
	.data.b	75
	.data.b	11
	.data.b	91
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4923
	.data.b	22
	.section	.debug_str		;off: 4224
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4924
	.data.w	.Ldw_str_begin+4224
	.data.b	150,5
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+141
	.data.b	0
	.data.w	.Ldw_loc_begin+166
	.section	.debug_loc		;off: 166
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4941
	.data.b	22
	.section	.debug_str		;off: 4234
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4942
	.data.w	.Ldw_str_begin+4234
	.data.b	151,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.w	.Ldw_loc_begin+185
	.section	.debug_loc		;off: 185
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4959
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 4241
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4969
	.data.w	.Ldw_str_begin+4241
	.data.b	154,5
	.data.b	18
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+204
	.section	.debug_loc		;off: 204
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4987
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4250
	.data.b	71,112,116,95,68,101,73,110,105,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4990
	.data.w	.Ldw_str_begin+4250
	.data.b	211,5
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_DeInitCheck
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

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_DeInitCheck-Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2214
	.data.b	0,5,2
	.data.w	Gpt_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	214,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	91
	.data.b	43
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	123
	.data.b	13
	.data.b	91
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	107
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5025
	.data.b	22
	.section	.debug_str		;off: 4266
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5026
	.data.w	.Ldw_str_begin+4266
	.data.b	213,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.w	.Ldw_loc_begin+223
	.section	.debug_loc		;off: 223
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	80
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5043
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 4273
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5053
	.data.w	.Ldw_str_begin+4273
	.data.b	216,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+253
	.section	.debug_loc		;off: 253
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5071
	.data.b	8
	.section	.debug_str		;off: 4282
	.data.b	67,104,97,110,110,101,108,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5072
	.data.w	.Ldw_str_begin+4282
	.data.b	217,5
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4301
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5087
	.data.w	.Ldw_str_begin+4301
	.data.b	218,5
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+183
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4318
	.data.b	71,112,116,95,83,116,97,114,116,84,105,109,101,114,67,104,101,99,107,0
	.section	.debug_info		;off: 5104
	.data.w	.Ldw_str_begin+4318
	.data.b	151,6
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_StartTimerCheck
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
	.data.w	Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_StartTimerCheck-Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2271
	.data.b	0,5,2
	.data.w	Gpt_StartTimerCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	156,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	11
	.data.b	92
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	109
	.data.b	12
	.data.b	12
	.data.b	107
	.data.b	13
	.data.b	6
	.data.b	91
	.data.b	3
	.data.b	100
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	28
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
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5139
	.data.b	22
	.section	.debug_str		;off: 4338
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5140
	.data.w	.Ldw_str_begin+4338
	.data.b	153,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+272
	.section	.debug_loc		;off: 272
	.data.w	.LDW22
	.data.w	.LDW32
	.data.b	1,0
	.data.b	80
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5157
	.data.b	22
	.section	.debug_str		;off: 4351
	.data.b	84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5158
	.data.w	.Ldw_str_begin+4351
	.data.b	154,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.b	0
	.data.w	.Ldw_loc_begin+302
	.section	.debug_loc		;off: 302
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

	.section	.debug_info		;off: 5175
	.data.b	22
	.section	.debug_str		;off: 4362
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5176
	.data.w	.Ldw_str_begin+4362
	.data.b	155,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.w	.Ldw_loc_begin+332
	.section	.debug_loc		;off: 332
	.data.w	.LDW22
	.data.w	.LDW32
	.data.b	1,0
	.data.b	82
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5193
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 4369
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5203
	.data.w	.Ldw_str_begin+4369
	.data.b	158,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+362
	.section	.debug_loc		;off: 362
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5221
	.data.b	8
	.section	.debug_str		;off: 4378
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5222
	.data.w	.Ldw_str_begin+4378
	.data.b	159,6
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+183
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4395
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5237
	.data.w	.Ldw_str_begin+4395
	.data.b	160,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+381
	.section	.debug_loc		;off: 381
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5255
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4409
	.data.b	71,112,116,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,67,104,101,99,107,0
	.section	.debug_info		;off: 5258
	.data.w	.Ldw_str_begin+4409
	.data.b	241,6
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_EnableNotificationCheck
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_EnableNotificationCheck-Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2367
	.data.b	0,5,2
	.data.w	Gpt_EnableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	245,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	11
	.data.b	92
	.data.b	124
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	13
	.data.b	107
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	93
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
	.section	.debug_info		;off: 5293
	.data.b	22
	.section	.debug_str		;off: 4437
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5294
	.data.w	.Ldw_str_begin+4437
	.data.b	243,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+400
	.section	.debug_loc		;off: 400
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

	.section	.debug_info		;off: 5311
	.data.b	22
	.section	.debug_str		;off: 4450
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5312
	.data.w	.Ldw_str_begin+4450
	.data.b	244,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.w	.Ldw_loc_begin+430
	.section	.debug_loc		;off: 430
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	81
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5329
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 4457
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5339
	.data.w	.Ldw_str_begin+4457
	.data.b	247,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+460
	.section	.debug_loc		;off: 460
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5357
	.data.b	7
	.section	.debug_str		;off: 4466
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5358
	.data.w	.Ldw_str_begin+4466
	.data.b	248,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+479
	.section	.debug_loc		;off: 479
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5376
	.data.b	8
	.section	.debug_str		;off: 4480
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5377
	.data.w	.Ldw_str_begin+4480
	.data.b	249,6
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+183
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4497
	.data.b	71,112,116,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,67,104,101,99,107,0
	.section	.debug_info		;off: 5394
	.data.w	.Ldw_str_begin+4497
	.data.b	189,7
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_DisableNotificationCheck
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_DisableNotificationCheck-Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2431
	.data.b	0,5,2
	.data.w	Gpt_DisableNotificationCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	193,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	11
	.data.b	92
	.data.b	124
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	13
	.data.b	107
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	77
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
	.section	.debug_info		;off: 5429
	.data.b	22
	.section	.debug_str		;off: 4526
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5430
	.data.w	.Ldw_str_begin+4526
	.data.b	191,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+498
	.section	.debug_loc		;off: 498
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	80
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5447
	.data.b	22
	.section	.debug_str		;off: 4539
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5448
	.data.w	.Ldw_str_begin+4539
	.data.b	192,7
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.w	.Ldw_loc_begin+528
	.section	.debug_loc		;off: 528
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	81
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5465
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 4546
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5475
	.data.w	.Ldw_str_begin+4546
	.data.b	195,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+558
	.section	.debug_loc		;off: 558
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5493
	.data.b	7
	.section	.debug_str		;off: 4555
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5494
	.data.w	.Ldw_str_begin+4555
	.data.b	196,7
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+577
	.section	.debug_loc		;off: 577
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5512
	.data.b	8
	.section	.debug_str		;off: 4569
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5513
	.data.w	.Ldw_str_begin+4569
	.data.b	197,7
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+183
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4586
	.data.b	71,112,116,95,72,87,83,116,111,112,84,105,109,101,114,0
	.section	.debug_info		;off: 5530
	.data.w	.Ldw_str_begin+4586
	.data.b	208,9
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.w	Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_HWStopTimer
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_HWStopTimer-Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2495
	.data.b	0,5,2
	.data.w	Gpt_HWStopTimer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	212,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	91
	.data.b	12
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5565
	.data.b	22
	.section	.debug_str		;off: 4602
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 5566
	.data.w	.Ldw_str_begin+4602
	.data.b	210,9
	.data.b	10
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.w	.Ldw_loc_begin+596
	.section	.debug_loc		;off: 596
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5583
	.data.b	22
	.section	.debug_str		;off: 4616
	.data.b	72,119,67,108,97,115,115,0
	.section	.debug_info		;off: 5584
	.data.w	.Ldw_str_begin+4616
	.data.b	211,9
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+3250
	.data.b	0
	.data.w	.Ldw_loc_begin+615
	.section	.debug_loc		;off: 615
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5601
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 4624
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5611
	.data.w	.Ldw_str_begin+4624
	.data.b	214,9
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+634
	.section	.debug_loc		;off: 634
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5629
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4635
	.data.b	71,112,116,95,72,87,83,101,116,84,105,109,101,114,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 5632
	.data.w	.Ldw_str_begin+4635
	.data.b	130,10
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.w	Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_HWSetTimerInterrupt
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_HWSetTimerInterrupt-Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2528
	.data.b	0,5,2
	.data.w	Gpt_HWSetTimerInterrupt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	135,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	92
	.data.b	12
	.data.b	12
	.data.b	76
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5667
	.data.b	22
	.section	.debug_str		;off: 4659
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 5668
	.data.w	.Ldw_str_begin+4659
	.data.b	132,10
	.data.b	10
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.w	.Ldw_loc_begin+653
	.section	.debug_loc		;off: 653
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5685
	.data.b	22
	.section	.debug_str		;off: 4673
	.data.b	72,119,67,108,97,115,115,0
	.section	.debug_info		;off: 5686
	.data.w	.Ldw_str_begin+4673
	.data.b	133,10
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+3250
	.data.b	0
	.data.w	.Ldw_loc_begin+672
	.section	.debug_loc		;off: 672
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	81
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5703
	.data.b	22
	.section	.debug_str		;off: 4681
	.data.b	69,110,97,98,108,101,83,116,97,116,101,0
	.section	.debug_info		;off: 5704
	.data.w	.Ldw_str_begin+4681
	.data.b	134,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.w	.Ldw_loc_begin+702
	.section	.debug_loc		;off: 702
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5721
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	7
	.section	.debug_str		;off: 4693
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 5731
	.data.w	.Ldw_str_begin+4693
	.data.b	137,10
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+721
	.section	.debug_loc		;off: 721
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5749
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4704
	.data.b	71,112,116,95,80,114,101,68,101,102,84,105,109,101,114,73,110,105,116,0
	.section	.debug_info		;off: 5752
	.data.w	.Ldw_str_begin+4704
	.data.b	181,10
	.data.b	37
	.data.b	1
	.data.w	Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PreDefTimerInit
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

	.section	.debug_abbrev		;off: 415
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PreDefTimerInit-Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2561
	.data.b	0,5,2
	.data.w	Gpt_PreDefTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	184,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	77
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	77
	.data.b	61
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5783
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 4724
	.data.b	66,97,115,101,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5793
	.data.w	.Ldw_str_begin+4724
	.data.b	186,10
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2973
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+740
	.section	.debug_loc		;off: 740
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5811
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4740
	.data.b	71,112,116,95,80,114,101,68,101,102,84,105,109,101,114,68,101,73,110,105,116,0
	.section	.debug_info		;off: 5814
	.data.w	.Ldw_str_begin+4740
	.data.b	242,10
	.data.b	36
	.data.b	1
	.data.w	Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PreDefTimerDeInit
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

	.section	.debug_frame		;off: 384
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_PreDefTimerDeInit-Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2600
	.data.b	0,5,2
	.data.w	Gpt_PreDefTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	245,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	0,1,1
	.section	.debug_info		;off: 5845
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4762
	.data.b	71,112,116,95,78,111,114,109,97,108,84,105,109,101,114,73,110,105,116,0
	.section	.debug_info		;off: 5857
	.data.w	.Ldw_str_begin+4762
	.data.b	156,11
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.w	Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_NormalTimerInit
	.data.b	1
	.data.b	93
	.data.b	240,143,1
	.data.b	100
	.data.b	0
	.data.b	28
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_NormalTimerInit-Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2625
	.data.b	0,5,2
	.data.w	Gpt_NormalTimerInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	159,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	12
	.data.b	60
	.data.b	28
	.data.b	45
	.data.b	28
	.data.b	93
	.data.b	107
	.data.b	12
	.data.b	60
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	44
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	94
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	39
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5892
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 4782
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5902
	.data.w	.Ldw_str_begin+4782
	.data.b	161,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+760
	.section	.debug_loc		;off: 760
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5920
	.data.b	7
	.section	.debug_str		;off: 4793
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5921
	.data.w	.Ldw_str_begin+4793
	.data.b	162,11
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+779
	.section	.debug_loc		;off: 779
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5939
	.data.b	8
	.section	.debug_str		;off: 4800
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 5940
	.data.w	.Ldw_str_begin+4800
	.data.b	163,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4813
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5955
	.data.w	.Ldw_str_begin+4813
	.data.b	164,11
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+87
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+798
	.section	.debug_loc		;off: 798
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5973
	.data.b	7
	.section	.debug_str		;off: 4830
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5974
	.data.w	.Ldw_str_begin+4830
	.data.b	165,11
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+817
	.section	.debug_loc		;off: 817
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5992
	.data.b	8
	.section	.debug_str		;off: 4847
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 5993
	.data.w	.Ldw_str_begin+4847
	.data.b	166,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4857
	.data.b	71,116,109,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 6008
	.data.w	.Ldw_str_begin+4857
	.data.b	167,11
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+318
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4870
	.data.b	66,97,115,101,84,105,109,101,114,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 6023
	.data.w	.Ldw_str_begin+4870
	.data.b	168,11
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+328
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+836
	.section	.debug_loc		;off: 836
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6041
	.data.b	7
	.section	.debug_str		;off: 4889
	.data.b	72,119,67,102,103,73,110,100,101,120,0
	.section	.debug_info		;off: 6042
	.data.w	.Ldw_str_begin+4889
	.data.b	169,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+855
	.section	.debug_loc		;off: 855
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6060
	.data.b	7
	.section	.debug_str		;off: 4900
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 6061
	.data.w	.Ldw_str_begin+4900
	.data.b	170,11
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+874
	.section	.debug_loc		;off: 874
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6079
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4911
	.data.b	71,112,116,95,78,111,114,109,97,108,84,105,109,101,114,68,101,73,110,105,116,0
	.section	.debug_info		;off: 6082
	.data.w	.Ldw_str_begin+4911
	.data.b	248,11
	.data.b	37
	.data.b	1
	.data.w	Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_NormalTimerDeInit
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.w	__ghs_eofn_Gpt_NormalTimerDeInit-Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2717
	.data.b	0,5,2
	.data.w	Gpt_NormalTimerDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CGpt.
	.data.b	6
	.data.b	3
	.data.b	251,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	12
	.data.b	60
	.data.b	44
	.data.b	75
	.data.b	77
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	105
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	28
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6113
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	8
	.section	.debug_str		;off: 4933
	.data.b	67,104,73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 6123
	.data.w	.Ldw_str_begin+4933
	.data.b	253,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4947
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6138
	.data.w	.Ldw_str_begin+4947
	.data.b	254,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+893
	.section	.debug_loc		;off: 893
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6156
	.data.b	8
	.section	.debug_str		;off: 4958
	.data.b	76,111,103,105,99,73,100,0
	.section	.debug_info		;off: 6157
	.data.w	.Ldw_str_begin+4958
	.data.b	255,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4966
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 6172
	.data.w	.Ldw_str_begin+4966
	.data.b	128,12
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+912
	.section	.debug_loc		;off: 912
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6190
	.data.b	7
	.section	.debug_str		;off: 4980
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6191
	.data.w	.Ldw_str_begin+4980
	.data.b	129,12
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+931
	.section	.debug_loc		;off: 931
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6209
	.data.b	7
	.section	.debug_str		;off: 4987
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6210
	.data.w	.Ldw_str_begin+4987
	.data.b	130,12
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+950
	.section	.debug_loc		;off: 950
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6228
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5004
	.data.b	71,112,116,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 6231
	.data.w	.Ldw_str_begin+5004
	.data.b	231,14
	.data.b	29
	.data.b	1
	.data.w	Gpt_GetVersionInfo
	.data.w	__ghs_eofn_Gpt_GetVersionInfo
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
	.data.w	Gpt_GetVersionInfo
	.data.w	__ghs_eofn_Gpt_GetVersionInfo-Gpt_GetVersionInfo
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2802
	.data.b	0,5,2
	.data.w	Gpt_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	239,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	75
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
	.section	.debug_info		;off: 6260
	.data.b	22
	.section	.debug_str		;off: 5023
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6261
	.data.w	.Ldw_str_begin+5023
	.data.b	234,14
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+336
	.data.b	0
	.data.w	.Ldw_loc_begin+969
	.section	.debug_loc		;off: 969
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6278
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5038
	.data.b	71,112,116,95,73,110,105,116,0
	.section	.debug_info		;off: 6290
	.data.w	.Ldw_str_begin+5038
	.data.b	156,15
	.data.b	29
	.data.b	1
	.data.w	Gpt_Init
	.data.w	__ghs_eofn_Gpt_Init
	.data.b	1
	.data.b	93
	.data.b	176,135,1
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_Init
	.data.w	__ghs_eofn_Gpt_Init-Gpt_Init
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2834
	.data.b	0,5,2
	.data.w	Gpt_Init
	.data.b	6
	.data.b	3
	.data.b	159,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	13
	.data.b	60
	.data.b	44
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	60
	.data.b	12
	.data.b	45
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	93
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	91
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6321
	.data.b	22
	.section	.debug_str		;off: 5047
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 6322
	.data.w	.Ldw_str_begin+5047
	.data.b	158,15
	.data.b	55
	.data.b	1
	.data.w	.Ldw_begin+136
	.data.b	0
	.data.w	.Ldw_loc_begin+988
	.section	.debug_loc		;off: 988
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	80
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6339
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 5057
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6349
	.data.w	.Ldw_str_begin+5057
	.data.b	161,15
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1018
	.section	.debug_loc		;off: 1018
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6367
	.data.b	8
	.section	.debug_str		;off: 5064
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6368
	.data.w	.Ldw_str_begin+5064
	.data.b	163,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5075
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6383
	.data.w	.Ldw_str_begin+5075
	.data.b	166,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1037
	.section	.debug_loc		;off: 1037
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6401
	.data.b	7
	.section	.debug_str		;off: 5084
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 6402
	.data.w	.Ldw_str_begin+5084
	.data.b	168,15
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1056
	.section	.debug_loc		;off: 1056
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6420
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5095
	.data.b	71,112,116,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 6423
	.data.w	.Ldw_str_begin+5095
	.data.b	150,16
	.data.b	29
	.data.b	1
	.data.w	Gpt_DeInit
	.data.w	__ghs_eofn_Gpt_DeInit
	.data.b	1
	.data.b	93
	.data.b	208,129,1
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_DeInit
	.data.w	__ghs_eofn_Gpt_DeInit-Gpt_DeInit
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2944
	.data.b	0,5,2
	.data.w	Gpt_DeInit
	.data.b	6
	.data.b	3
	.data.b	153,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	12
	.data.b	44
	.data.b	45
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	13
	.data.b	28
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	76
	.data.b	3
	.data.b	110
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	14
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
	.section	.debug_info		;off: 6454
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 5106
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6464
	.data.w	.Ldw_str_begin+5106
	.data.b	155,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1075
	.section	.debug_loc		;off: 1075
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6482
	.data.b	8
	.section	.debug_str		;off: 5113
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6483
	.data.w	.Ldw_str_begin+5113
	.data.b	158,16
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5124
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6498
	.data.w	.Ldw_str_begin+5124
	.data.b	160,16
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5133
	.data.b	71,112,116,95,71,101,116,84,105,109,101,69,108,97,112,115,101,100,0
	.section	.debug_info		;off: 6515
	.data.w	.Ldw_str_begin+5133
	.data.b	248,16
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.w	Gpt_GetTimeElapsed
	.data.w	__ghs_eofn_Gpt_GetTimeElapsed
	.data.b	1
	.data.b	93
	.data.b	180,128,1
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_GetTimeElapsed
	.data.w	__ghs_eofn_Gpt_GetTimeElapsed-Gpt_GetTimeElapsed
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3043
	.data.b	0,5,2
	.data.w	Gpt_GetTimeElapsed
	.data.b	6
	.data.b	3
	.data.b	252,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	12
	.data.b	93
	.data.b	29
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	61
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	24
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
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6550
	.data.b	22
	.section	.debug_str		;off: 5152
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6551
	.data.w	.Ldw_str_begin+5152
	.data.b	251,16
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1094
	.section	.debug_loc		;off: 1094
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

	.section	.debug_info		;off: 6568
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 5160
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 6578
	.data.w	.Ldw_str_begin+5160
	.data.b	254,16
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1124
	.section	.debug_loc		;off: 1124
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6596
	.data.b	7
	.section	.debug_str		;off: 5174
	.data.b	84,105,109,101,69,108,97,112,115,101,100,0
	.section	.debug_info		;off: 6597
	.data.w	.Ldw_str_begin+5174
	.data.b	255,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1143
	.section	.debug_loc		;off: 1143
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6615
	.data.b	8
	.section	.debug_str		;off: 5186
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6616
	.data.w	.Ldw_str_begin+5186
	.data.b	128,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5193
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6631
	.data.w	.Ldw_str_begin+5193
	.data.b	129,17
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1162
	.section	.debug_loc		;off: 1162
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6649
	.data.b	8
	.section	.debug_str		;off: 5207
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6650
	.data.w	.Ldw_str_begin+5207
	.data.b	131,17
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5216
	.data.b	71,112,116,95,71,101,116,84,105,109,101,82,101,109,97,105,110,105,110,103,0
	.section	.debug_info		;off: 6667
	.data.w	.Ldw_str_begin+5216
	.data.b	221,17
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.w	Gpt_GetTimeRemaining
	.data.w	__ghs_eofn_Gpt_GetTimeRemaining
	.data.b	1
	.data.b	93
	.data.b	180,128,1
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_GetTimeRemaining
	.data.w	__ghs_eofn_Gpt_GetTimeRemaining-Gpt_GetTimeRemaining
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3135
	.data.b	0,5,2
	.data.w	Gpt_GetTimeRemaining
	.data.b	6
	.data.b	3
	.data.b	224,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	13
	.data.b	93
	.data.b	29
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	61
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	24
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
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6702
	.data.b	22
	.section	.debug_str		;off: 5237
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6703
	.data.w	.Ldw_str_begin+5237
	.data.b	223,17
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1181
	.section	.debug_loc		;off: 1181
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	80
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6720
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 5245
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 6730
	.data.w	.Ldw_str_begin+5245
	.data.b	226,17
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1211
	.section	.debug_loc		;off: 1211
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6748
	.data.b	7
	.section	.debug_str		;off: 5259
	.data.b	84,105,109,101,82,101,109,97,105,110,105,110,103,0
	.section	.debug_info		;off: 6749
	.data.w	.Ldw_str_begin+5259
	.data.b	227,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1230
	.section	.debug_loc		;off: 1230
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6767
	.data.b	8
	.section	.debug_str		;off: 5273
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6768
	.data.w	.Ldw_str_begin+5273
	.data.b	228,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5280
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6783
	.data.w	.Ldw_str_begin+5280
	.data.b	229,17
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1249
	.section	.debug_loc		;off: 1249
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6801
	.data.b	8
	.section	.debug_str		;off: 5294
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6802
	.data.w	.Ldw_str_begin+5294
	.data.b	231,17
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5303
	.data.b	71,112,116,95,83,116,97,114,116,84,105,109,101,114,0
	.section	.debug_info		;off: 6819
	.data.w	.Ldw_str_begin+5303
	.data.b	182,18
	.data.b	29
	.data.b	1
	.data.w	Gpt_StartTimer
	.data.w	__ghs_eofn_Gpt_StartTimer
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_StartTimer
	.data.w	__ghs_eofn_Gpt_StartTimer-Gpt_StartTimer
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3227
	.data.b	0,5,2
	.data.w	Gpt_StartTimer
	.data.b	6
	.data.b	3
	.data.b	188,18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	13
	.data.b	76
	.data.b	59
	.data.b	13
	.data.b	76
	.data.b	28
	.data.b	61
	.data.b	28
	.data.b	29
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	13
	.data.b	77
	.data.b	77
	.data.b	75
	.data.b	3
	.data.b	101
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	108
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	107
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	8
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
	.data.b	12
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	91
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
	.section	.debug_info		;off: 6850
	.data.b	22
	.section	.debug_str		;off: 5318
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6851
	.data.w	.Ldw_str_begin+5318
	.data.b	185,18
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1268
	.section	.debug_loc		;off: 1268
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	80
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6868
	.data.b	22
	.section	.debug_str		;off: 5326
	.data.b	86,97,108,117,101,0
	.section	.debug_info		;off: 6869
	.data.w	.Ldw_str_begin+5326
	.data.b	187,18
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3009
	.data.b	0
	.data.w	.Ldw_loc_begin+1298
	.section	.debug_loc		;off: 1298
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	81
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6886
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	7
	.section	.debug_str		;off: 5332
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6896
	.data.w	.Ldw_str_begin+5332
	.data.b	190,18
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1328
	.section	.debug_loc		;off: 1328
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6914
	.data.b	7
	.section	.debug_str		;off: 5339
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 6915
	.data.w	.Ldw_str_begin+5339
	.data.b	191,18
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1347
	.section	.debug_loc		;off: 1347
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6933
	.data.b	7
	.section	.debug_str		;off: 5353
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6934
	.data.w	.Ldw_str_begin+5353
	.data.b	192,18
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1366
	.section	.debug_loc		;off: 1366
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6952
	.data.b	7
	.section	.debug_str		;off: 5370
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6953
	.data.w	.Ldw_str_begin+5370
	.data.b	193,18
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1385
	.section	.debug_loc		;off: 1385
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6971
	.data.b	8
	.section	.debug_str		;off: 5384
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6972
	.data.w	.Ldw_str_begin+5384
	.data.b	194,18
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5393
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 6987
	.data.w	.Ldw_str_begin+5393
	.data.b	195,18
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1404
	.section	.debug_loc		;off: 1404
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7005
	.data.b	7
	.section	.debug_str		;off: 5404
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7006
	.data.w	.Ldw_str_begin+5404
	.data.b	196,18
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1423
	.section	.debug_loc		;off: 1423
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7024
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5415
	.data.b	71,112,116,95,83,116,111,112,84,105,109,101,114,0
	.section	.debug_info		;off: 7027
	.data.w	.Ldw_str_begin+5415
	.data.b	177,19
	.data.b	29
	.data.b	1
	.data.w	Gpt_StopTimer
	.data.w	__ghs_eofn_Gpt_StopTimer
	.data.b	1
	.data.b	93
	.data.b	240,143,1
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_StopTimer
	.data.w	__ghs_eofn_Gpt_StopTimer-Gpt_StopTimer
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3341
	.data.b	0,5,2
	.data.w	Gpt_StopTimer
	.data.b	6
	.data.b	3
	.data.b	181,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	13
	.data.b	60
	.data.b	44
	.data.b	12
	.data.b	76
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	156
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	91
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
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7058
	.data.b	22
	.section	.debug_str		;off: 5429
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7059
	.data.w	.Ldw_str_begin+5429
	.data.b	180,19
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1442
	.section	.debug_loc		;off: 1442
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	80
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7076
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	7
	.section	.debug_str		;off: 5437
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 7086
	.data.w	.Ldw_str_begin+5437
	.data.b	183,19
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1472
	.section	.debug_loc		;off: 1472
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7104
	.data.b	7
	.section	.debug_str		;off: 5451
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7105
	.data.w	.Ldw_str_begin+5451
	.data.b	184,19
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1491
	.section	.debug_loc		;off: 1491
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7123
	.data.b	7
	.section	.debug_str		;off: 5468
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7124
	.data.w	.Ldw_str_begin+5468
	.data.b	185,19
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1510
	.section	.debug_loc		;off: 1510
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7142
	.data.b	7
	.section	.debug_str		;off: 5475
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7143
	.data.w	.Ldw_str_begin+5475
	.data.b	186,19
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1529
	.section	.debug_loc		;off: 1529
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7161
	.data.b	8
	.section	.debug_str		;off: 5489
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7162
	.data.w	.Ldw_str_begin+5489
	.data.b	189,19
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5498
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 7177
	.data.w	.Ldw_str_begin+5498
	.data.b	191,19
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1548
	.section	.debug_loc		;off: 1548
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7195
	.data.b	7
	.section	.debug_str		;off: 5509
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7196
	.data.w	.Ldw_str_begin+5509
	.data.b	192,19
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1567
	.section	.debug_loc		;off: 1567
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7214
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5520
	.data.b	71,112,116,95,71,101,116,80,114,101,100,101,102,84,105,109,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7217
	.data.w	.Ldw_str_begin+5520
	.data.b	150,20
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.w	Gpt_GetPredefTimerValue
	.data.w	__ghs_eofn_Gpt_GetPredefTimerValue
	.data.b	1
	.data.b	93
	.data.b	244,129,1
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_GetPredefTimerValue
	.data.w	__ghs_eofn_Gpt_GetPredefTimerValue-Gpt_GetPredefTimerValue
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3432
	.data.b	0,5,2
	.data.w	Gpt_GetPredefTimerValue
	.data.b	6
	.data.b	3
	.data.b	155,20
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	107
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	61
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
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
	.section	.debug_info		;off: 7252
	.data.b	22
	.section	.debug_str		;off: 5544
	.data.b	80,114,101,100,101,102,84,105,109,101,114,0
	.section	.debug_info		;off: 7253
	.data.w	.Ldw_str_begin+5544
	.data.b	152,20
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3209
	.data.b	0
	.data.w	.Ldw_loc_begin+1586
	.section	.debug_loc		;off: 1586
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	80
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7270
	.data.b	22
	.section	.debug_str		;off: 5556
	.data.b	84,105,109,101,86,97,108,117,101,80,116,114,0
	.section	.debug_info		;off: 7271
	.data.w	.Ldw_str_begin+5556
	.data.b	154,20
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+412
	.data.b	0
	.data.w	.Ldw_loc_begin+1616
	.section	.debug_loc		;off: 1616
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	81
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7288
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	7
	.section	.debug_str		;off: 5569
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7298
	.data.w	.Ldw_str_begin+5569
	.data.b	157,20
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1646
	.section	.debug_loc		;off: 1646
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7316
	.data.b	8
	.section	.debug_str		;off: 5578
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7317
	.data.w	.Ldw_str_begin+5578
	.data.b	158,20
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5585
	.data.b	67,111,117,110,116,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7332
	.data.w	.Ldw_str_begin+5585
	.data.b	159,20
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1665
	.section	.debug_loc		;off: 1665
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7350
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5598
	.data.b	71,112,116,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 7353
	.data.w	.Ldw_str_begin+5598
	.data.b	253,20
	.data.b	29
	.data.b	1
	.data.w	Gpt_EnableNotification
	.data.w	__ghs_eofn_Gpt_EnableNotification
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_EnableNotification
	.data.w	__ghs_eofn_Gpt_EnableNotification-Gpt_EnableNotification
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3524
	.data.b	0,5,2
	.data.w	Gpt_EnableNotification
	.data.b	6
	.data.b	3
	.data.b	129,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	12
	.data.b	61
	.data.b	59
	.data.b	12
	.data.b	76
	.data.b	61
	.data.b	28
	.data.b	28
	.data.b	92
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	91
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
	.section	.debug_info		;off: 7384
	.data.b	22
	.section	.debug_str		;off: 5621
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7385
	.data.w	.Ldw_str_begin+5621
	.data.b	128,21
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1684
	.section	.debug_loc		;off: 1684
	.data.w	.LDW37
	.data.w	.LDW47
	.data.b	1,0
	.data.b	80
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7402
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 5629
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 7412
	.data.w	.Ldw_str_begin+5629
	.data.b	131,21
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1714
	.section	.debug_loc		;off: 1714
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7430
	.data.b	7
	.section	.debug_str		;off: 5643
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7431
	.data.w	.Ldw_str_begin+5643
	.data.b	132,21
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1733
	.section	.debug_loc		;off: 1733
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7449
	.data.b	7
	.section	.debug_str		;off: 5650
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7450
	.data.w	.Ldw_str_begin+5650
	.data.b	133,21
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1752
	.section	.debug_loc		;off: 1752
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7468
	.data.b	7
	.section	.debug_str		;off: 5667
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7469
	.data.w	.Ldw_str_begin+5667
	.data.b	134,21
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1771
	.section	.debug_loc		;off: 1771
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7487
	.data.b	8
	.section	.debug_str		;off: 5681
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7488
	.data.w	.Ldw_str_begin+5681
	.data.b	135,21
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5690
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 7503
	.data.w	.Ldw_str_begin+5690
	.data.b	136,21
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1790
	.section	.debug_loc		;off: 1790
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7521
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5701
	.data.b	71,112,116,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 7524
	.data.w	.Ldw_str_begin+5701
	.data.b	206,21
	.data.b	29
	.data.b	1
	.data.w	Gpt_DisableNotification
	.data.w	__ghs_eofn_Gpt_DisableNotification
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_DisableNotification
	.data.w	__ghs_eofn_Gpt_DisableNotification-Gpt_DisableNotification
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3594
	.data.b	0,5,2
	.data.w	Gpt_DisableNotification
	.data.b	6
	.data.b	3
	.data.b	210,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	13
	.data.b	60
	.data.b	59
	.data.b	12
	.data.b	76
	.data.b	61
	.data.b	29
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	44
	.data.b	29
	.data.b	27
	.data.b	11
	.data.b	91
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
	.section	.debug_info		;off: 7555
	.data.b	22
	.section	.debug_str		;off: 5725
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7556
	.data.w	.Ldw_str_begin+5725
	.data.b	209,21
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+2997
	.data.b	0
	.data.w	.Ldw_loc_begin+1809
	.section	.debug_loc		;off: 1809
	.data.w	.LDW67
	.data.w	.LDW77
	.data.b	1,0
	.data.b	80
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7573
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	7
	.section	.debug_str		;off: 5733
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7583
	.data.w	.Ldw_str_begin+5733
	.data.b	212,21
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1839
	.section	.debug_loc		;off: 1839
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7601
	.data.b	7
	.section	.debug_str		;off: 5740
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7602
	.data.w	.Ldw_str_begin+5740
	.data.b	213,21
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1858
	.section	.debug_loc		;off: 1858
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7620
	.data.b	7
	.section	.debug_str		;off: 5757
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 7621
	.data.w	.Ldw_str_begin+5757
	.data.b	214,21
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1877
	.section	.debug_loc		;off: 1877
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7639
	.data.b	8
	.section	.debug_str		;off: 5771
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7640
	.data.w	.Ldw_str_begin+5771
	.data.b	215,21
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5780
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7655
	.data.w	.Ldw_str_begin+5780
	.data.b	216,21
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1896
	.section	.debug_loc		;off: 1896
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7673
	.data.b	7
	.section	.debug_str		;off: 5794
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 7674
	.data.w	.Ldw_str_begin+5794
	.data.b	217,21
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1915
	.section	.debug_loc		;off: 1915
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7692
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5805
	.data.b	71,112,116,95,71,116,109,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 7695
	.data.w	.Ldw_str_begin+5805
	.data.b	186,24
	.data.b	28
	.data.b	1
	.data.w	Gpt_Gtm_ISRHandler
	.data.w	__ghs_eofn_Gpt_Gtm_ISRHandler
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_Gtm_ISRHandler
	.data.w	__ghs_eofn_Gpt_Gtm_ISRHandler-Gpt_Gtm_ISRHandler
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3664
	.data.b	0,5,2
	.data.w	Gpt_Gtm_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	190,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	91
	.data.b	13
	.data.b	77
	.data.b	43
	.data.b	12
	.data.b	75
	.data.b	11
	.data.b	28
	.data.b	27
	.data.b	28
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	61
	.data.b	45
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	123
	.data.b	12
	.data.b	44
	.data.b	60
	.data.b	45
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	26
	.data.b	2
	.data.b	28
	.data.b	1
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
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	3
	.data.b	95
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 7726
	.data.b	22
	.section	.debug_str		;off: 5824
	.data.b	77,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7727
	.data.w	.Ldw_str_begin+5824
	.data.b	188,24
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.w	.Ldw_loc_begin+1934
	.section	.debug_loc		;off: 1934
	.data.w	.LDW97
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7744
	.data.b	22
	.section	.debug_str		;off: 5836
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7745
	.data.w	.Ldw_str_begin+5836
	.data.b	189,24
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.w	.Ldw_loc_begin+1953
	.section	.debug_loc		;off: 1953
	.data.w	.LDW97
	.data.w	.LDW08
	.data.b	1,0
	.data.b	81
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7762
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	8
	.section	.debug_str		;off: 5844
	.data.b	84,105,109,101,114,80,101,114,105,111,100,0
	.section	.debug_info		;off: 7772
	.data.w	.Ldw_str_begin+5844
	.data.b	192,24
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5856
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 7787
	.data.w	.Ldw_str_begin+5856
	.data.b	193,24
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1983
	.section	.debug_loc		;off: 1983
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7805
	.data.b	7
	.section	.debug_str		;off: 5870
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7806
	.data.w	.Ldw_str_begin+5870
	.data.b	194,24
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2002
	.section	.debug_loc		;off: 2002
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7824
	.data.b	7
	.section	.debug_str		;off: 5887
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7825
	.data.w	.Ldw_str_begin+5887
	.data.b	195,24
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2021
	.section	.debug_loc		;off: 2021
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7843
	.data.b	7
	.section	.debug_str		;off: 5894
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7844
	.data.w	.Ldw_str_begin+5894
	.data.b	196,24
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2040
	.section	.debug_loc		;off: 2040
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7862
	.data.b	7
	.section	.debug_str		;off: 5908
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7863
	.data.w	.Ldw_str_begin+5908
	.data.b	197,24
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2059
	.section	.debug_loc		;off: 2059
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7881
	.data.b	7
	.section	.debug_str		;off: 5918
	.data.b	73,110,116,69,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7882
	.data.w	.Ldw_str_begin+5918
	.data.b	198,24
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2078
	.section	.debug_loc		;off: 2078
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7900
	.data.b	8
	.section	.debug_str		;off: 5930
	.data.b	79,110,101,83,104,111,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 7901
	.data.w	.Ldw_str_begin+5930
	.data.b	199,24
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5944
	.data.b	72,119,67,104,97,110,110,101,108,79,98,106,101,99,116,0
	.section	.debug_info		;off: 7916
	.data.w	.Ldw_str_begin+5944
	.data.b	200,24
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1528
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2097
	.section	.debug_loc		;off: 2097
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7934
	.data.b	8
	.section	.debug_str		;off: 5960
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 7935
	.data.w	.Ldw_str_begin+5960
	.data.b	201,24
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5967
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7950
	.data.w	.Ldw_str_begin+5967
	.data.b	202,24
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2117
	.section	.debug_loc		;off: 2117
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7968
	.data.b	7
	.section	.debug_str		;off: 5980
	.data.b	83,97,102,101,116,121,70,108,97,103,0
	.section	.debug_info		;off: 7969
	.data.w	.Ldw_str_begin+5980
	.data.b	203,24
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1106
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2136
	.section	.debug_loc		;off: 2136
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7987
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5991
	.data.b	71,112,116,95,66,97,115,101,116,105,109,101,114,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 7990
	.data.w	.Ldw_str_begin+5991
	.data.b	200,25
	.data.b	28
	.data.b	1
	.data.w	Gpt_Basetimer_ISRHandler
	.data.w	__ghs_eofn_Gpt_Basetimer_ISRHandler
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

	.section	.debug_frame		;off: 720
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Gpt_Basetimer_ISRHandler
	.data.w	__ghs_eofn_Gpt_Basetimer_ISRHandler-Gpt_Basetimer_ISRHandler
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3794
	.data.b	0,5,2
	.data.w	Gpt_Basetimer_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	203,25
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	43
	.data.b	12
	.data.b	91
	.data.b	12
	.data.b	29
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	60
	.data.b	91
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	124
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	0
	.data.b	1
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
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 8021
	.data.b	22
	.section	.debug_str		;off: 6016
	.data.b	72,119,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 8022
	.data.w	.Ldw_str_begin+6016
	.data.b	202,25
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.w	.Ldw_loc_begin+2155
	.section	.debug_loc		;off: 2155
	.data.w	.LDW28
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8039
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	7
	.section	.debug_str		;off: 6026
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 8049
	.data.w	.Ldw_str_begin+6026
	.data.b	205,25
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1903
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2174
	.section	.debug_loc		;off: 2174
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8067
	.data.b	7
	.section	.debug_str		;off: 6033
	.data.b	72,119,67,102,103,77,97,112,73,110,100,101,120,0
	.section	.debug_info		;off: 8068
	.data.w	.Ldw_str_begin+6033
	.data.b	206,25
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2193
	.section	.debug_loc		;off: 2193
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8086
	.data.b	7
	.section	.debug_str		;off: 6047
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 8087
	.data.w	.Ldw_str_begin+6047
	.data.b	207,25
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+308
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2212
	.section	.debug_loc		;off: 2212
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8105
	.data.b	8
	.section	.debug_str		;off: 6064
	.data.b	79,110,101,83,104,111,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 8106
	.data.w	.Ldw_str_begin+6064
	.data.b	208,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2865
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 6078
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 8121
	.data.w	.Ldw_str_begin+6078
	.data.b	209,25
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2231
	.section	.debug_loc		;off: 2231
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8139
	.data.b	7
	.section	.debug_str		;off: 6092
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 8140
	.data.w	.Ldw_str_begin+6092
	.data.b	210,25
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1118
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2250
	.section	.debug_loc		;off: 2250
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8158
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
	.data.b	63
	.data.b	2
	.data.b	3
	.data.b	36
	.data.b	3
	.data.b	1
	.data.b	36
	.data.b	71,80,84,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	37
	.data.b	71,80,84,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	38
	.data.b	71,80,84,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	40
	.data.b	71,80,84,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	41
	.data.b	71,80,84,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	42
	.data.b	71,80,84,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	44
	.data.b	71,80,84,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	45
	.data.b	71,80,84,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,49,48,48,85,41,0
	.data.b	1
	.data.b	56
	.data.b	71,80,84,95,71,69,84,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	63
	.data.b	71,80,84,95,68,69,95,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	70
	.data.b	71,80,84,95,84,73,77,69,95,69,76,65,80,83,69,68,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	77
	.data.b	71,80,84,95,84,73,77,69,95,82,69,77,65,73,78,73,78,71,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	86
	.data.b	71,80,84,95,69,78,65,66,76,69,95,68,73,83,65,66,76,69,95,78,79,84,73,70,73,67,65,84,73,79,78,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	96
	.data.b	71,80,84,95,87,65,75,69,85,80,95,70,85,78,67,84,73,79,78,65,76,73,84,89,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	173,1
	.data.b	71,80,84,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	189,1
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,48,48,85,83,95,51,50,66,73,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	190,1
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,49,54,66,73,84,95,69,78,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	191,1
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,50,52,66,73,84,95,69,78,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	192,1
	.data.b	71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,51,50,66,73,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	195,1
	.data.b	71,80,84,95,80,82,69,68,69,70,84,73,77,69,82,95,49,85,83,95,84,89,80,69,32,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,51,50,66,73,84,41,0
	.data.b	1
	.data.b	198,1
	.data.b	71,80,84,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,48,32,40,54,85,41,0
	.data.b	1
	.data.b	200,1
	.data.b	71,80,84,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,49,32,40,52,85,41,0
	.data.b	1
	.data.b	202,1
	.data.b	71,80,84,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	204,1
	.data.b	71,80,84,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	1
	.data.b	206,1
	.data.b	71,80,84,95,77,65,88,95,67,72,65,78,78,69,76,83,32,40,49,48,85,41,0
	.data.b	1
	.data.b	208,1
	.data.b	71,80,84,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	5
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	6
	.data.b	3
	.data.b	25
	.data.b	7
	.data.b	3
	.data.b	31
	.data.b	8
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	9
	.data.b	3
	.data.b	13
	.data.b	10
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
	.data.b	44
	.data.b	11
	.data.b	3
	.data.b	30
	.data.b	12
	.data.b	3
	.data.b	43
	.data.b	13
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
	.data.b	14
	.data.b	3
	.data.b	33
	.data.b	15
	.data.b	3
	.data.b	31
	.data.b	16
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	17
	.data.b	3
	.data.b	56
	.data.b	18
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
	.data.b	19
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
	.data.b	19
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
	.data.b	19
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
	.data.b	19
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	81
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	83
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	167,2
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	169,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
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
	.data.b	197,1
	.data.b	77,67,65,76,95,90,69,82,79,32,40,48,85,41,0
	.data.b	1
	.data.b	198,1
	.data.b	77,67,65,76,95,79,78,69,32,40,49,85,41,0
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
	.data.b	3
	.data.b	46
	.data.b	39
	.data.b	3
	.data.b	27
	.data.b	40
	.data.b	4
	.data.b	1
	.data.b	77
	.data.b	66,65,83,69,84,73,77,69,82,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	79
	.data.b	41
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,66,65,83,69,84,73,77,69,82,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	228,1
	.data.b	66,65,83,69,84,73,77,69,82,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	230,1
	.data.b	41
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	49
	.data.b	42
	.data.b	3
	.data.b	28
	.data.b	43
	.data.b	3
	.data.b	24
	.data.b	44
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	52
	.data.b	45
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	46
	.data.b	1
	.data.b	27
	.data.b	71,80,84,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	28
	.data.b	71,80,84,95,77,79,68,85,76,69,95,73,68,32,40,49,48,48,85,41,0
	.data.b	1
	.data.b	29
	.data.b	71,80,84,95,73,78,83,84,65,78,67,69,95,73,68,32,40,48,85,41,0
	.data.b	1
	.data.b	32
	.data.b	71,80,84,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	33
	.data.b	71,80,84,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	34
	.data.b	71,80,84,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	37
	.data.b	71,80,84,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	38
	.data.b	71,80,84,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	39
	.data.b	71,80,84,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	47
	.data.b	1
	.data.b	43
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	44
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	51
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	52
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	48
	.data.b	71,80,84,95,71,69,84,95,86,69,82,83,73,79,78,95,73,78,70,79,95,83,73,68,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	50
	.data.b	71,80,84,95,73,78,73,84,95,83,73,68,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	52
	.data.b	71,80,84,95,68,69,73,78,73,84,95,83,73,68,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	54
	.data.b	71,80,84,95,71,69,84,95,84,73,77,69,95,69,76,65,80,83,69,68,95,83,73,68,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	56
	.data.b	71,80,84,95,71,69,84,95,84,73,77,69,95,82,69,77,65,73,78,73,78,71,95,83,73,68,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	58
	.data.b	71,80,84,95,83,84,65,82,84,95,84,73,77,69,82,95,83,73,68,32,40,48,120,48,53,85,41,0
	.data.b	1
	.data.b	60
	.data.b	71,80,84,95,83,84,79,80,95,84,73,77,69,82,95,83,73,68,32,40,48,120,48,54,85,41,0
	.data.b	1
	.data.b	62
	.data.b	71,80,84,95,69,78,65,66,76,69,95,78,79,84,73,70,89,95,83,73,68,32,40,48,120,48,55,85,41,0
	.data.b	1
	.data.b	64
	.data.b	71,80,84,95,68,73,83,65,66,76,69,95,78,79,84,73,70,89,95,83,73,68,32,40,48,120,48,56,85,41,0
	.data.b	1
	.data.b	78
	.data.b	71,80,84,95,83,73,68,95,71,69,84,95,80,82,69,68,69,70,84,73,77,69,82,86,65,76,85,69,95,83,73,68,32,40,48,120,48,68,85,41,0
	.data.b	1
	.data.b	80
	.data.b	71,80,84,95,83,73,68,95,71,84,77,95,73,83,82,72,65,78,68,76,69,82,95,83,73,68,32,40,48,120,48,70,85,41,0
	.data.b	1
	.data.b	82
	.data.b	71,80,84,95,83,73,68,95,66,65,83,69,84,73,77,69,82,95,73,83,82,72,65,78,68,76,69,82,95,83,73,68,32,40,48,120,65,48,85,41,0
	.data.b	1
	.data.b	88
	.data.b	71,80,84,95,69,95,85,78,73,78,73,84,32,40,48,120,48,65,85,41,0
	.data.b	1
	.data.b	90
	.data.b	71,80,84,95,69,95,66,85,83,89,32,40,48,120,48,66,85,41,0
	.data.b	1
	.data.b	98
	.data.b	71,80,84,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,48,120,48,68,85,41,0
	.data.b	1
	.data.b	100
	.data.b	71,80,84,95,69,95,80,65,82,65,77,95,67,72,65,78,78,69,76,32,40,48,120,49,52,85,41,0
	.data.b	1
	.data.b	102
	.data.b	71,80,84,95,69,95,80,65,82,65,77,95,86,65,76,85,69,32,40,48,120,49,53,85,41,0
	.data.b	1
	.data.b	104
	.data.b	71,80,84,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,48,120,49,54,85,41,0
	.data.b	1
	.data.b	106
	.data.b	71,80,84,95,69,95,80,65,82,65,77,95,80,82,69,68,69,70,95,84,73,77,69,82,32,40,48,120,49,55,85,41,0
	.data.b	1
	.data.b	116
	.data.b	71,80,84,95,69,95,76,79,67,75,95,84,73,77,69,79,85,84,32,40,48,120,65,48,85,41,0
	.data.b	1
	.data.b	118
	.data.b	71,80,84,95,69,95,65,76,82,69,65,68,89,95,68,73,83,65,66,76,69,68,32,40,48,120,70,49,85,41,0
	.data.b	1
	.data.b	120
	.data.b	71,80,84,95,69,95,65,76,82,69,65,68,89,95,69,78,65,66,76,69,68,32,40,48,120,70,50,85,41,0
	.data.b	1
	.data.b	122
	.data.b	71,80,84,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,48,120,69,48,85,41,0
	.data.b	1
	.data.b	124
	.data.b	71,80,84,95,69,95,67,79,82,69,95,67,72,65,78,78,69,76,95,77,73,83,77,65,84,67,72,32,40,48,120,69,49,85,41,0
	.data.b	1
	.data.b	126
	.data.b	71,80,84,95,69,95,83,65,70,69,84,89,95,67,72,69,67,75,95,70,65,73,76,69,68,32,40,48,120,69,50,41,0
	.data.b	1
	.data.b	133,1
	.data.b	71,80,84,95,80,82,69,68,69,70,84,73,77,69,82,95,83,84,65,84,85,83,95,77,65,83,75,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	135,1
	.data.b	71,80,84,95,70,76,65,71,95,83,69,84,32,40,40,117,105,110,116,51,50,41,48,120,48,49,85,41,0
	.data.b	1
	.data.b	137,1
	.data.b	71,80,84,95,67,79,82,69,95,83,84,65,84,85,83,95,77,65,83,75,32,40,40,117,105,110,116,51,50,41,48,88,49,69,85,41,0
	.data.b	1
	.data.b	139,1
	.data.b	71,80,84,95,80,82,69,68,69,70,84,73,77,69,82,95,85,78,73,78,73,84,73,65,76,73,90,69,68,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	142,1
	.data.b	71,80,84,95,67,79,82,69,83,84,65,84,85,83,95,80,79,83,32,40,40,117,105,110,116,51,50,41,48,120,48,49,85,41,0
	.data.b	1
	.data.b	144,1
	.data.b	71,80,84,95,65,76,76,67,79,82,69,95,85,78,73,84,73,65,76,73,90,69,68,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	154,1
	.data.b	71,80,84,95,80,82,69,68,69,70,84,73,77,69,82,95,69,78,32,40,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,49,54,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78
	.data.b	41,32,124,124,32,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,50,52,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78,41,32,124,124,32,40,71,80,84,95,80,82,69,68,69
	.data.b	70,95,84,73,77,69,82,95,49,85,83,95,51,50,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78,41,32,124,124,32,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,48,48,85,83,95,51
	.data.b	50,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78,41,41,0
	.data.b	1
	.data.b	159,1
	.data.b	71,80,84,95,80,82,69,68,69,70,84,73,77,69,82,95,49,85,83,95,69,78,32,40,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,49,54,66,73,84,95,69,78,32,61,61,32,83,84
	.data.b	68,95,79,78,41,32,124,124,32,40,71,80,84,95,80,82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,50,52,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78,41,32,124,124,32,40,71,80,84,95,80
	.data.b	82,69,68,69,70,95,84,73,77,69,82,95,49,85,83,95,51,50,66,73,84,95,69,78,32,61,61,32,83,84,68,95,79,78,41,41,0
	.data.b	1
	.data.b	166,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	167,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	141,2
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	142,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	68
	.data.b	48
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
	.data.b	70
	.data.b	49
	.data.b	4
	.data.b	1
	.data.b	113
	.data.b	71,80,84,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,32,35,35,32,69,120
	.data.b	99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	116
	.data.b	71,80,84,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,32,35,35,32,69,120,99,108
	.data.b	117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	119
	.data.b	71,80,84,95,71,69,84,95,67,72,65,78,78,69,76,95,82,65,77,95,80,84,82,40,67,111,114,101,73,100,44,67,104,73,110,67,111,114,101,73,110,100,101,120,41,32,38,40,40,71,112,116,95,67,111,114,101,67,104,97
	.data.b	110,110,101,108,83,116,97,116,117,115,80,116,114,91,67,111,114,101,73,100,93,41,91,67,104,73,110,67,111,114,101,73,110,100,101,120,93,41,0
	.data.b	1
	.data.b	123
	.data.b	71,80,84,95,71,69,84,95,67,72,65,78,78,69,76,95,77,65,88,95,86,65,76,85,69,40,67,111,114,101,73,100,44,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,41,32,40,71,112,116,95,67,111,110,102,105
	.data.b	103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,71,112,116,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,97,110,73,110,67,111,114,101
	.data.b	73,110,100,101,120,93,46,77,97,120,84,105,99,107,86,97,108,117,101,41,0
	.data.b	1
	.data.b	127
	.data.b	71,80,84,95,71,69,84,95,72,87,67,79,78,70,73,71,95,77,65,80,73,78,68,69,88,40,76,111,103,105,99,67,104,97,110,110,101,108,73,100,41,32,40,71,112,116,95,67,111,110,102,105,103,80,116,114,45,62,71,112
	.data.b	116,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,91,76,111,103,105,99,67,104,97,110,110,101,108,73,100,93,46,72,119,67,102,103,73,110,100,101,120,41,0
	.data.b	1
	.data.b	131,1
	.data.b	71,80,84,95,71,69,84,95,71,84,77,95,67,72,65,78,78,69,76,95,79,66,74,69,67,84,95,80,84,82,40,72,119,67,102,103,77,97,112,73,110,100,101,120,41,32,40,38,40,71,112,116,95,67,111,110,102,105,103,80
	.data.b	116,114,45,62,71,112,116,72,119,71,116,109,67,111,110,102,105,103,80,116,114,91,72,119,67,102,103,77,97,112,73,110,100,101,120,93,46,72,119,67,104,97,110,110,101,108,73,110,100,101,120,41,41,0
	.data.b	1
	.data.b	135,1
	.data.b	71,80,84,95,71,69,84,95,66,65,83,69,84,73,77,69,82,95,67,72,65,78,78,69,76,95,79,66,74,69,67,84,95,80,84,82,40,72,119,67,102,103,77,97,112,73,110,100,101,120,41,32,40,71,112,116,95,67,111,110
	.data.b	102,105,103,80,116,114,45,62,71,112,116,72,119,66,97,115,101,84,105,109,101,114,67,111,110,102,105,103,80,116,114,91,72,119,67,102,103,77,97,112,73,110,100,101,120,93,46,72,119,67,104,97,110,110,101,108,73,110,100,101
	.data.b	120,80,116,114,41,0
	.data.b	1
	.data.b	139,1
	.data.b	71,80,84,95,71,69,84,95,72,87,95,67,76,65,83,83,40,67,111,114,101,73,100,44,67,104,73,110,67,111,114,101,73,110,100,101,120,41,32,40,71,112,116,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67
	.data.b	111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,71,112,116,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,73,110,67,111,114,101,73,110,100,101,120,93,46,72,119,67,108,97,115
	.data.b	115,41,0
	.data.b	1
	.data.b	143,1
	.data.b	71,80,84,95,71,69,84,95,67,72,65,78,78,69,76,95,73,78,68,69,88,95,73,78,95,67,79,82,69,40,76,111,103,105,99,67,104,97,110,110,101,108,73,100,41,32,71,112,116,95,67,111,110,102,105,103,80,116,114,45
	.data.b	62,71,112,116,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,91,76,111,103,105,99,67,104,97,110,110,101,108,73,100,93,46,73,110,100,101,120,0
	.data.b	1
	.data.b	152,1
	.data.b	71,80,84,95,68,69,84,95,82,85,78,84,73,77,69,95,69,82,82,79,82,95,82,69,80,79,82,84,40,65,112,105,83,105,100,44,69,114,114,67,111,100,101,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114
	.data.b	116,82,117,110,116,105,109,101,69,114,114,111,114,40,71,80,84,95,77,79,68,85,76,69,95,73,68,44,32,71,80,84,95,73,78,83,84,65,78,67,69,95,73,68,44,32,65,112,105,83,105,100,44,32,69,114,114,67,111,100
	.data.b	101,41,0
	.data.b	1
	.data.b	156,1
	.data.b	71,80,84,95,68,69,84,95,69,82,82,79,82,95,82,69,80,79,82,84,40,65,112,105,83,105,100,44,69,114,114,67,111,100,101,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,40,71
	.data.b	80,84,95,77,79,68,85,76,69,95,73,68,44,32,71,80,84,95,73,78,83,84,65,78,67,69,95,73,68,44,32,65,112,105,83,105,100,44,32,69,114,114,67,111,100,101,41,0
	.data.b	1
	.data.b	163,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	165,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	176,1
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	178,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	182,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	184,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	195,1
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	197,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	202,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	204,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	160,49
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	163,49
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	215,1
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	217,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	222,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	224,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	211,57
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	214,57
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	235,1
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	237,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	241,1
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	243,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	187,2
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	189,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	194,2
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,51,50,32,0
	.data.b	3
	.data.b	196,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	140,6
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,51,50,32,0
	.data.b	1
	.data.b	143,6
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	202,2
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,51,50,32,0
	.data.b	3
	.data.b	204,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	208,2
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	210,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	216,2
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	218,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	224,2
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	226,2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	205,3
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	207,3
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	212,3
	.data.b	71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	214,3
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,80,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	160,26
	.data.b	71,80,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	162,26
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 461
	.data.b	0
