	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682568..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_CheckInitParam:
.LDW01:
	push	{r4,lr}
.LDW11:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.2:
	.endo	..gh.endasm.2

;line686
..lin.6655f927..ec71acc6.0_1::
.LDWlin1:
	mov	r4,1
	ldr	r3,.L430
	subs	r1,r2,0
	beq	.L163
	ldr	r2,.L431
	ldr	r2,[r2]
	cmp	r2,0
	bne	.L165
.L160:
	mov	r3,16
.L415:

.L416:

.L417:

	mov	r1,7
	mov	r0,255
.L432:

	bl	Det_ReportError
	b	.L162
.L165:
	ldr	r2,[r3,r1 lsl 2]
	cmp	r2,0
	moveq	r3,224
	beq	.L415
.L163:
	ldr	r1,[r3,r1 lsl 2]
	ldr	r1,[r1]
	cmp	r1,1
	moveq	r3,13
	moveq	r2,0
	beq	.L417
.L167:
	movs	r2,r0
	moveq	r3,14
	beq	.L416
.L170:
	mov	r4,0
.L162:
	mov	r0,r4
.LDW21:
.L434:

	pop	{r4,pc}
__ghs_eofn_Dsadc_CheckInitParam:
	.endf	Dsadc_CheckInitParam
	.endf	Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;RetErr	r4	local
;CoreId	r1	local

;ConfigPtr	r0	param

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Dsadc_InitFlgCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_InitFlgCore0:	.space	4
	.endo	Dsadc_InitFlgCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_InitFlgCore0
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Dsadc_CoreInitStatusSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_CoreInitStatusSetPtr:	.data.w	Dsadc_InitFlgCore0
	.space	12
	.endo	Dsadc_CoreInitStatusSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_CoreInitStatusSetPtr
	.section ".ghcalltbl",""
	.align	4
.L433:	.data.w	.L432
	.endo	.L433
	.section ".ghrettbl",""
	.align	4
.L435:	.data.w	.L434
	.endo	.L435
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_CheckInit:
.LDW31:
	push	{r4,lr}
.LDW41:
	mov	r4,1
	ldr	r3,.L430
	cmp	r1,0
	beq	.L438
	ldr	r2,[r3,r1 lsl 2]
	cmp	r2,0
	beq	.L446
.L438:
	ldr	r2,[r3,r1 lsl 2]
	ldr	r2,[r2]
	cmp	r2,1
	movne	r2,r0
	movne	r3,10
	bne	.L649
.L442:
	cmp	r0,1
	beq	.L445
	ldr	r3,.L660
	ldr	r2,[r3]
	ldr	r1,[r2,r1 lsl 2]
	cmp	r1,0
	bne	.L445
.L446:
	mov	r2,r0
	mov	r3,224
.L649:

	mov	r1,7
	mov	r0,255
.L661:

	bl	Det_ReportError
	b	.L441
.L445:
	mov	r4,0
.L441:
	mov	r0,r4
.LDW51:
.L663:

	pop	{r4,pc}
__ghs_eofn_Dsadc_CheckInit:
	.endf	Dsadc_CheckInit
	.endf	Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;RetErr	r4	local

;ServiceId	r0	param
;CoreId	r1	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Dsadc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_ConfigPtr:	.space	4
	.endo	Dsadc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_ConfigPtr
	.section ".ghcalltbl",""
.L662:	.data.w	.L661
	.endo	.L662
	.section ".ghrettbl",""
.L664:	.data.w	.L663
	.endo	.L664
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_CheckDeInit:
.LDW61:
	push	{r4,lr}
	mov	r4,r0
.LDW71:
	mov	r1,r0
	mov	r0,1
.L1068:

	bl	Dsadc_CheckInit
	cmp	r0,0
	cmpeq	r4,0
	moveq	r4,1<<24
	beq	.L674
.L1070:

	pop	{r4,pc}
.L673:
	ldr	r2,.L430
	ldr	r1,[r2,r4 lsr 22]
	cmp	r1,0
	beq	.L674
	ldr	r2,[r1]
	cmp	r2,1
	bne	.L674
	mov	r3,17
	mov	r1,7
	mov	r0,255
.L1072:

	bl	Det_ReportError
	mov	r0,1
.L674:
	add	r4,r4,1<<24
	lsr	r1,r4,24
	cmp	r1,4
.L1074:

	pophs	{r4,pc}
	cmp	r0,0
	beq	.L673
.LDW81:
.L1076:

	pop	{r4,pc}
__ghs_eofn_Dsadc_CheckDeInit:
	.endf	Dsadc_CheckDeInit
	.endf	Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;Err	r0	local

;CoreId	r4	param

	.section ".bss","awb"
.L981:
	.endo	.L981
	.section ".ghcalltbl",""
.L1069:	.data.w	.L1068
	.endo	.L1069
	.section ".ghrettbl",""
.L1071:	.data.w	.L1070
	.endo	.L1071
	.section ".ghcalltbl",""
.L1073:	.data.w	.L1072
	.endo	.L1073
	.section ".ghrettbl",""
.L1075:	.data.w	.L1074
	.endo	.L1075
.L1077:	.data.w	.L1076
	.endo	.L1077
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_CheckMulticoreAllocateError:
.LDW91:
	push	{r2,r4-r5,lr}
.LDW02:
	mov	r4,1
	cmp	r1,4
	movhs	r2,r0
	movhs	r3,21
	bhs	.L1269
.L1085:
	mov	r3,r1
	b	.L1278

.L430:	.data.w	Dsadc_CoreInitStatusSetPtr
	.endo	.L430

.L431:	.data.w	Dsadc_InitFlgCore0
	.endo	.L431

.L660:	.data.w	Dsadc_ConfigPtr
	.endo	.L660

.L1278:

;line880
..lin.6655f927..b09ea2c4.0_2::
.LDWlin2:
..gh.beginasm.6:
	.endo	..gh.beginasm.6
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.7:
	.endo	..gh.endasm.7

;line883
..lin.6655f927..b09ea2c4.0_3::
.LDWlin3:
	ldr	r1,.L1279
	ldr	r12,[r1]
	ldr	r5,[r12,20]
	ldr	r2,[r12,r2 lsl 2]
	add	r1,r3,r3 lsl 1
	ldrb	r1,[r1,r5]
	ldrb	r12,[r2]
	cmp	r1,r12
	bhs	.L1091
	ldr	r2,[r2,4]
	mov	r12,44
	smlabb	r1,r1,r12,r2
	ldrb	r1,[r1,1]
	cmp	r3,r1
	beq	.L1090
.L1091:
	mov	r2,r0
	mov	r3,225
.L1269:

	mov	r1,7
	mov	r0,255
.L1280:

	bl	Det_ReportError
	b	.L1082
.L1090:
	mov	r4,0
.L1082:
	mov	r0,r4
.LDW12:
.L1282:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Dsadc_CheckMulticoreAllocateError:
	.endf	Dsadc_CheckMulticoreAllocateError
	.endf	Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;RetErr	r4	local
;CoreChIdx	r1	local

;ServiceId	r0	param
;ChannelId	r3	param

	.section ".ghcalltbl",""
.L1281:	.data.w	.L1280
	.endo	.L1281
	.section ".ghrettbl",""
.L1283:	.data.w	.L1282
	.endo	.L1283
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_CheckAllChannelStatus:
.LDW22:
	push	{r2,r4-r7,lr}
	ldr	r7,.L1279
.LDW32:
	mov	r4,0
	b	.L2340

.L1279:	.data.w	Dsadc_ConfigPtr
	.endo	.L1279

.L2340:

;line951
..lin.6655f927..841c4b17.0_4::
.LDWlin4:
..gh.beginasm.9:
	.endo	..gh.beginasm.9
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.10:
	.endo	..gh.endasm.10

	ldr	r1,[r7]
;line954
..lin.6655f927..841c4b17.0_5::
.LDWlin5:
	mov	r5,r0
	ldr	r0,[r1,r0 lsl 2]
	cmp	r0,0
	movne	r6,r4
	bne	.L1297
	b	.L1299
.L1294:
	ldr	r2,.L2341
	rsb	r0,r6,r6 lsl 2
	ldr	r1,[r2,r5 lsl 2]
	add	r0,r1,r0 lsl 3
	ldr	r2,[r0,20]
	cmp	r2,1
	moveq	r4,r2
	moveq	r3,11
	moveq	r1,7
	moveq	r0,255
.L2343:

	bleq	Det_ReportError
	add	r6,r6,1
	cmp	r4,0
	uxtb	r6,r6
	bne	.L1298
.L1297:
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	ldrb	r0,[r0]
	cmp	r6,r0
	blo	.L1294
.L1299:
	ldr	r0,.L2342
	ldrb	r2,[r0]
	cmp	r2,1
	moveq	r4,r2
	moveq	r3,32
	moveq	r1,7
	moveq	r0,255
.L2345:

	bleq	Det_ReportError
.L1298:
	mov	r0,r4
.LDW42:
.L2347:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_CheckAllChannelStatus:
	.endf	Dsadc_CheckAllChannelStatus
	.endf	Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;RetErr	r4	local
;CoreChdx	r6	local
;CoreId	r5	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Dsadc_CarrierStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_CarrierStatus:	.space	1
	.endo	Dsadc_CarrierStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_CarrierStatus
	.section ".mcal_const_asil_d_unspecified","a"
Dsadc_CoreDataSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_CoreDataSetPtr:
	.data.w	Dsadc_DataCore0
	.space	12
	.endo	Dsadc_CoreDataSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_CoreDataSetPtr
	.section ".ghcalltbl",""
.L2344:	.data.w	.L2343
	.endo	.L2344
.L2346:	.data.w	.L2345
	.endo	.L2346
	.section ".ghrettbl",""
.L2348:	.data.w	.L2347
	.endo	.L2348
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Dsadc_DataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_DataCore0:	.space	96
	.endo	Dsadc_DataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_DataCore0
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
	.global	Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_DeInitChannel:
.LDW52:
	push	{r4,lr}
	mov	r4,r0
.LDW62:
.L2470:

	bl	SchM_Enter_Dsadc_DeInit
	mov	r0,4
.L2472:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2351
	ldr	r1,.L2469
	ldr	r0,[r1,r4 lsl 2]
.L2474:

	bl	Dsadc_Hal_DeInitModule
	and	r4,r0,1
	mov	r0,4
.L2476:

	bl	Mcal_ReleaseLock
	b	.L2353
.L2351:
	mov	r4,0
.L2353:
.L2478:

	bl	SchM_Exit_Dsadc_DeInit
	mov	r0,r4
.LDW72:
.L2480:

	pop	{r4,pc}
__ghs_eofn_Dsadc_DeInitChannel:
	.endf	Dsadc_DeInitChannel
	.endf	Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;SafetyErr	r4	local

;HwUnitId	r4	param

	.section ".mcal_const_asil_d_unspecified","a"
Dsadc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.::
Dsadc_BaseAddrs:	.data.b	0,32,0,176
	.data.b	0,36,0,176
	.data.b	0,32,1,176
	.data.b	0,36,1,176
	.data.b	0,40,0,176
	.data.b	0,44,0,176
	.data.b	0,40,1,176
	.data.b	0,44,1,176
	.data.b	0,16,48,176
	.data.b	0,20,48,176
	.endo	Dsadc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.endo	Dsadc_BaseAddrs
	.section ".bss","awb"
.L2418:
	.endo	.L2418
	.section ".ghcalltbl",""
.L2471:	.data.w	.L2470
	.endo	.L2471
.L2473:	.data.w	.L2472
	.endo	.L2473
.L2475:	.data.w	.L2474
	.endo	.L2475
.L2477:	.data.w	.L2476
	.endo	.L2477
.L2479:	.data.w	.L2478
	.endo	.L2479
	.section ".ghrettbl",""
.L2481:	.data.w	.L2480
	.endo	.L2481
	.data
	.global	__caller.SchM_Exit_Dsadc_DeInit.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Dsadc_Hal_DeInitModule.i.p

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Dsadc_DeInit.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.global	Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_SetInterruptEnStatus:
.LDW82:
.LDW92:
	ldr	r2,[r1,40]
	ldrb	r12,[r1,10]
	ldr	r3,[r2,16]
	cmp	r12,2
	bne	.L2484
	ldr	r1,[r3,12]
	cmp	r1,3
	moveq	r1,256
	movne	r1,1<<9
	strheq	r1,[r0,2]
	b	.L2774
.L2484:
	ldr	r3,[r3,12]
	cmp	r3,3
	bne	.L2490
	cmp	r12,0
	moveq	r3,2
	strheq	r3,[r0,2]
	b	.L2498
.L2490:
	cmp	r3,0
	bne	.L2497
.L2498:
	mov	r12,128
	ldrb	r3,[r1,8]
	b	.L2775
.L2497:
	mov	r3,1
	strh	r3,[r0,2]
	mov	r12,16
	ldrb	r3,[r1,9]
.L2775:

	cmp	r3,1
	ldrheq	r3,[r0,2]
	orreq	r3,r3,r12
	strheq	r3,[r0,2]
.L2496:
	ldr	r2,[r2,12]
	cmp	r2,0
	ldrhne	r2,[r0,2]
	ldrbne	r1,[r1,32]
	orrne	r1,r2,r1
.L2774:

	strhne	r1,[r0,2]
.LDW03:
.L2786:

	ret	
__ghs_eofn_Dsadc_SetInterruptEnStatus:
	.endf	Dsadc_SetInterruptEnStatus
	.endf	Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

;DataPtr	r0	param
;ChCfgPtr	r1	param

	.section ".bss","awb"
.L2664:
	.endo	.L2664
	.section ".ghrettbl",""
.L2787:	.data.w	.L2786
	.endo	.L2787
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
	.global	Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_AuxIsrEventEntry:
.LDW13:
	push	{r2,r4-r9,lr}
	mov	r3,r1
	mov	r7,r2
.LDW23:
	b	.L3051

.L2341:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L2341

.L2342:	.data.w	Dsadc_CarrierStatus
	.endo	.L2342

.L2469:	.data.w	Dsadc_BaseAddrs
	.endo	.L2469

.L3051:

;line1218
..lin.6655f927..d69aa6f3.0_6::
.LDWlin6:
..gh.beginasm.14:
	.endo	..gh.beginasm.14
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.15:
	.endo	..gh.endasm.15

;line1220
..lin.6655f927..d69aa6f3.0_7::
.LDWlin7:
	add	r1,r3,r3 lsl 1
	ldr	r3,.L3052
	ldr	r5,[r3]
	ldr	r5,[r5,20]
	ldrb	r5,[r1,r5]
	ldr	r1,.L3053
	ldr	r6,[r1,r0 lsl 2]
	mov	r0,r6
.L3055:

	bl	Dsadc_Hal_GetInterruptStatus
	mov	r8,r0
	tst	r0,128
	beq	.L2794
	mov	r0,r6
	mov	r1,128
.L3057:

	bl	Dsadc_Hal_ClearInterruptStatus
.L3059:

	bl	SchM_Enter_Dsadc_ResultHandling
	mov	r0,r6
	mov	r1,1
.L3061:

	bl	Dsadc_Hal_GetConversionResult
	ldr	r1,.L3054
	rsb	r2,r5,r5 lsl 2
	ldr	r1,[r1,r4 lsl 2]
	add	r9,r1,r2 lsl 3
	ldr	r1,[r9,8]
	strh	r0,[r1,2]
	mov	r0,3
	str	r0,[r9,16]
.L3063:

	bl	SchM_Exit_Dsadc_ResultHandling
	ldr	r2,[r7,20]
	cmp	r2,0
	beq	.L2794
	ldrb	r0,[r9]
	cmp	r0,1
.L3065:

	blxeq	r2
.L2794:
	tst	r8,32
	beq	.L2799
	mov	r0,r6
	mov	r1,32
.L3067:

	bl	Dsadc_Hal_ClearInterruptStatus
	ldr	r0,[r7,28]
	cmp	r0,0
.L3069:

	popeq	{r2,r4-r9,pc}
	ldr	r1,.L3054
	ldr	r0,[r1,r4 lsl 2]
	rsb	r3,r5,r5 lsl 2
	ldrb	r0,[r0,r3 lsl 3]
	cmp	r0,1
.L3071:

	popne	{r2,r4-r9,pc}
	mov	r0,r6
	mov	r1,1
.L3073:

	bl	Dsadc_Hal_GetConversionResult
	sxth	r1,r0
	ldr	r2,[r7,28]
	mov	r0,0
	b	.L3038
.L2799:
	tst	r8,64
.L3075:

	popeq	{r2,r4-r9,pc}
	mov	r0,r6
	mov	r1,64
.L3077:

	bl	Dsadc_Hal_ClearInterruptStatus
	ldr	r0,[r7,28]
	cmp	r0,0
.L3079:

	popeq	{r2,r4-r9,pc}
	ldr	r1,.L3054
	ldr	r1,[r1,r4 lsl 2]
	rsb	r0,r5,r5 lsl 2
	ldrb	r0,[r1,r0 lsl 3]
	cmp	r0,1
.L3081:

	popne	{r2,r4-r9,pc}
.L2808:
	mov	r0,r6
	mov	r1,1
.L3083:

	bl	Dsadc_Hal_GetConversionResult
	sxth	r1,r0
	ldr	r2,[r7,28]
	mov	r0,1
.L3038:

.L3085:

	blx	r2
.LDW33:
.L3087:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Dsadc_AuxIsrEventEntry:
	.endf	Dsadc_AuxIsrEventEntry
	.endf	Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;IntStatus	r8	local
;CoreChIdx	r5	local
;CoreId	r4	local

;HwUnitId	r0	param
;Channel	r3	param
;ChCfgPtr	r7	param

	.section ".ghcalltbl",""
.L3056:	.data.w	.L3055
	.endo	.L3056
.L3058:	.data.w	.L3057
	.endo	.L3058
.L3060:	.data.w	.L3059
	.endo	.L3060
.L3062:	.data.w	.L3061
	.endo	.L3062
.L3064:	.data.w	.L3063
	.endo	.L3064
.L3066:	.data.w	.L3065
	.endo	.L3066
.L3068:	.data.w	.L3067
	.endo	.L3068
	.section ".ghrettbl",""
.L3070:	.data.w	.L3069
	.endo	.L3070
.L3072:	.data.w	.L3071
	.endo	.L3072
	.section ".ghcalltbl",""
.L3074:	.data.w	.L3073
	.endo	.L3074
	.section ".ghrettbl",""
.L3076:	.data.w	.L3075
	.endo	.L3076
	.section ".ghcalltbl",""
.L3078:	.data.w	.L3077
	.endo	.L3078
	.section ".ghrettbl",""
.L3080:	.data.w	.L3079
	.endo	.L3080
.L3082:	.data.w	.L3081
	.endo	.L3082
	.section ".ghcalltbl",""
.L3084:	.data.w	.L3083
	.endo	.L3084
.L3086:	.data.w	.L3085
	.endo	.L3086
	.section ".ghrettbl",""
.L3088:	.data.w	.L3087
	.endo	.L3088
	.data
	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.SchM_Exit_Dsadc_ResultHandling.v.v

	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.SchM_Enter_Dsadc_ResultHandling.v.v

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetInterruptStatus.i.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
	.global	Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_IsrEventEntry:
.LDW43:
	push	{r4-r9,lr}
	sub	sp,sp,12
	mov	r7,r1
	ldr	r1,.L3053
	ldr	r5,[r1,r0 lsl 2]
	mov	r6,r0
	mov	r8,r2
.LDW53:
	mov	r0,r5
.L3257:

	bl	Dsadc_Hal_GetInterruptStatus
	mov	r9,r0
	tst	r0,1
	beq	.L3091
	mov	r0,r5
	mov	r1,0
.L3259:

	bl	Dsadc_Hal_GetConversionResult
	sxth	r4,r0
	mov	r0,r5
	mov	r1,1
.L3261:

	bl	Dsadc_Hal_ClearInterruptStatus
	str	r4,[sp]
	mov	r3,r8
	mov	r1,r7
	mov	r0,r6
	mov	r2,1
	b	.L3248
.L3091:
	mov	r4,1
	tst	r0,2
	beq	.L3093
.L3095:
	mov	r0,r5
	mov	r1,0
.L3263:

	bl	Dsadc_Hal_GetConversionResult
	sxth	r4,r0
	mov	r0,r5
	mov	r1,2
.L3265:

	bl	Dsadc_Hal_ClearInterruptStatus
	str	r4,[sp]
	mov	r3,r8
	mov	r1,r7
	mov	r0,r6
	mov	r2,0
.L3248:

.L3267:

	bl	Dsadc_FifoOrExternalTriggerIsr
	mov	r4,r0
.L3093:
	tst	r9,16
	beq	.L3097
	mov	r0,r5
	mov	r1,16
.L3269:

	bl	Dsadc_Hal_ClearInterruptStatus
	mov	r2,r8
	mov	r1,r7
	mov	r0,r6
.L3271:

	bl	Dsadc_TimestampIsr
.L3097:
	mov	r0,r4
.LDW63:
	add	sp,sp,12
.L3273:

	pop	{r4-r9,pc}
__ghs_eofn_Dsadc_IsrEventEntry:
	.endf	Dsadc_IsrEventEntry
	.endf	Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;SafetyErr	r4	local
;IntStatus	r9	local

;HwUnitId	r6	param
;Channel	r7	param
;ChCfgPtr	r8	param

	.section ".bss","awb"
.L3178:
	.endo	.L3178
	.section ".ghcalltbl",""
.L3258:	.data.w	.L3257
	.endo	.L3258
.L3260:	.data.w	.L3259
	.endo	.L3260
.L3262:	.data.w	.L3261
	.endo	.L3262
.L3264:	.data.w	.L3263
	.endo	.L3264
.L3266:	.data.w	.L3265
	.endo	.L3266
.L3268:	.data.w	.L3267
	.endo	.L3268
.L3270:	.data.w	.L3269
	.endo	.L3270
.L3272:	.data.w	.L3271
	.endo	.L3272
	.section ".ghrettbl",""
.L3274:	.data.w	.L3273
	.endo	.L3274
	.data
	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.Dsadc_Hal_GetInterruptStatus.i.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
	.global	Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_FifoOrExternalTriggerIsr:
.LDW73:
	push	{r4-fp,lr}
	sub	sp,sp,12
	mov	r8,r0
	mov	r12,r1
	strb	r2,[sp,3]
	mov	r6,r3
.LDW83:
	mov	r7,1
	b	.L4955

.L3052:	.data.w	Dsadc_ConfigPtr
	.endo	.L3052

.L3053:	.data.w	Dsadc_BaseAddrs
	.endo	.L3053

.L3054:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L3054

.L4955:

;line1457
..lin.6655f927..e4cf760d.0_8::
.LDWlin8:
..gh.beginasm.18:
	.endo	..gh.beginasm.18
 mrc p15, 0, r1, c0, c0, 5
 and r10, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r10, r10, r1         

..gh.endasm.19:
	.endo	..gh.endasm.19

;line1459
..lin.6655f927..e4cf760d.0_9::
.LDWlin9:
	ldr	r2,.L4956
	ldr	r9,[r2]
	ldr	r9,[r9,20]
	add	r0,r12,r12 lsl 1
	ldrb	r9,[r0,r9]
	ldr	r0,[r3,40]
	ldr	r0,[r0,28]
	ldr	fp,.L4957
	cmp	r0,0
	beq	.L3281
	ldr	r2,[fp,r8 lsl 2]
	ldr	r0,[r2,16]
	ubfx	r1,r0,20,1
	ldr	r0,[r2,16]
	ubfx	r0,r0,19,1
	add	r2,r0,r1 lsl 1
	str	r2,[sp,4]
	tst	r2,1
	beq	.L3289
	mov	r0,r7
	b	.L3320
.L3281:
	str	r0,[sp,4]
.L3289:
	ldr	r4,[r3,12]
.L4959:

	bl	SchM_Enter_Dsadc_ResultHandling
	cmp	r4,0
	bne	.L3303
	ldrb	r0,[r6,9]
	cmp	r0,1
	ldreq	r0,[r6,40]
	ldreq	r0,[r0,8]
	ldreq	r0,[r0,8]
	cmpeq	r0,0
	ldreq	r1,.L4958
	rsbeq	r0,r9,r9 lsl 2
	ldreq	r1,[r1,r10 lsl 2]
	addeq	r1,r1,r0 lsl 3
	ldreq	r0,[fp,r8 lsl 2]
	ldreq	r0,[r0,28]
	strheq	r0,[r1,4]
	ldr	r1,.L4958
	ldr	r1,[r1,r10 lsl 2]
	rsb	r0,r9,r9 lsl 2
	add	r5,r1,r0 lsl 3
	ldrb	r0,[r6,8]
	ldrsh	r1,[sp,48]
	ldr	r4,[r5,8]
	cmp	r0,1
	ldrbeq	r0,[sp,3]
	strh	r1,[r4]
	cmpeq	r0,1
	bne	.L3299
	ldr	r0,[fp,r8 lsl 2]
	mov	r1,r7
.L4961:

	bl	Dsadc_Hal_GetConversionResult
	strh	r0,[r4,2]
	mov	r0,3
	str	r0,[r5,16]
.L3299:
	mov	r0,3
	str	r0,[r5,20]
	b	.L3436
.L3303:
	ldr	r1,.L4958
	ldr	r1,[r1,r10 lsl 2]
	rsb	r0,r9,r9 lsl 2
	ldrb	r3,[r6,11]
	add	r5,r1,r0 lsl 3
	ldrb	r0,[r5,6]
	ldrsh	r2,[sp,48]
	cmp	r0,r3
	ldr	r12,[r5,8]
	moveq	r0,0
	lsl	r1,r0,1
	strh	r2,[r1,r12]
	add	r0,r0,1
	strb	r0,[r5,6]
	ldrb	r0,[r5,6]
	cmp	r0,r3
	bne	.L3305
	mov	r0,3
	str	r0,[r5,20]
.L4963:

	bl	SchM_Exit_Dsadc_ResultHandling
	ldr	r0,[r6,24]
	cmp	r0,0
	beq	.L3307
	ldrb	r1,[r5]
	cmp	r1,1
.L4965:

	blxeq	r0
.L3307:
	ldr	r0,[r6,16]
	cmp	r0,0
	bne	.L3302
.L4967:

	bl	SchM_Enter_Dsadc_ResultHandling
	ldr	r4,[fp,r8 lsl 2]
	ldrh	r1,[r5,2]
	mov	r0,r4
.L4969:

	bl	Dsadc_Hal_DisableInterrupt
	mov	r7,r0
	cmp	r0,1
	bne	.L3436
	ldrh	r1,[r5,2]
	mov	r0,r4
.L4971:

	bl	Dsadc_Hal_ClearInterruptStatus
	mov	r0,0
	strb	r0,[r5]
	b	.L3436
.L3305:
	ldr	r0,[r5,20]
	cmp	r0,3
	movne	r0,2
	strne	r0,[r5,20]
.L3436:
.L4973:

	bl	SchM_Exit_Dsadc_ResultHandling
.L3302:
	ldr	r3,[r6,20]
	cmp	r3,0
	beq	.L3317
	ldrb	r0,[r5]
	cmp	r0,1
	moveq	r0,0
.L4975:

	blxeq	r3
.L3317:
	mov	r0,0
.L3320:
	ldr	r1,.L4958
	rsb	r12,r9,r9 lsl 2
	ldr	r1,[r1,r10 lsl 2]
	add	r1,r1,r12 lsl 3
	str	r0,[r1,12]
	ldr	r0,[sp,4]
	cmp	r0,0
	beq	.L3321
	ldr	r0,[fp,r8 lsl 2]
.L4977:

	bl	Dsadc_Hal_ClearFifo
	and	r7,r7,r0
.L3321:
	mov	r0,r7
.LDW93:
	add	sp,sp,12
.L4979:

	pop	{r4-fp,pc}
__ghs_eofn_Dsadc_FifoOrExternalTriggerIsr:
	.endf	Dsadc_FifoOrExternalTriggerIsr
	.endf	Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;SafetyErr	r7	local
;CoreChIdx	r9	local
;CurrBufPos	r0	local
;FifoErr	[sp,4]	local
;CoreId	r10	local

;HwUnitId	r8	param
;Channel	r12	param
;TrigMthdFlg	[sp,3]	param
;ChCfgPtr	r6	param
;RecentRslt	[sp,48]	param

	.section ".ghcalltbl",""
.L4960:	.data.w	.L4959
	.endo	.L4960
.L4962:	.data.w	.L4961
	.endo	.L4962
.L4964:	.data.w	.L4963
	.endo	.L4964
.L4966:	.data.w	.L4965
	.endo	.L4966
.L4968:	.data.w	.L4967
	.endo	.L4968
.L4970:	.data.w	.L4969
	.endo	.L4970
.L4972:	.data.w	.L4971
	.endo	.L4972
.L4974:	.data.w	.L4973
	.endo	.L4974
.L4976:	.data.w	.L4975
	.endo	.L4976
.L4978:	.data.w	.L4977
	.endo	.L4978
	.section ".ghrettbl",""
.L4980:	.data.w	.L4979
	.endo	.L4980
	.data
	.global	__caller.Dsadc_Hal_ClearFifo.i.p

	.global	__caller.SchM_Exit_Dsadc_ResultHandling.v.v

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_DisableInterrupt.i.pi

	.global	__caller.SchM_Enter_Dsadc_ResultHandling.v.v

	.global	__caller.SchM_Exit_Dsadc_ResultHandling.v.v

	.global	__caller.Dsadc_Hal_GetConversionResult.i.pi

	.global	__caller.SchM_Enter_Dsadc_ResultHandling.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
	.global	Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_TimestampIsr:
.LDW04:
	push	{r4,lr}
	mov	r3,r1
.LDW14:
	ldr	r1,[r2,12]
	cmp	r1,0
	ldrbeq	r1,[r2,9]
	cmpeq	r1,1
.L5093:

	popne	{r4,pc}
	ldr	r1,[r2,40]
	ldr	r1,[r1,8]
	ldr	r1,[r1,8]
	cmp	r1,0
.L5095:

	popeq	{r4,pc}
	b	.L5089

.L4956:	.data.w	Dsadc_ConfigPtr
	.endo	.L4956

.L4957:	.data.w	Dsadc_BaseAddrs
	.endo	.L4957

.L4958:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L4958

.L5089:

;line1670
..lin.6655f927..b834fde5.0_10::
.LDWlin10:
..gh.beginasm.21:
	.endo	..gh.beginasm.21
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.22:
	.endo	..gh.endasm.22

;line1672
..lin.6655f927..b834fde5.0_11::
.LDWlin11:
	ldr	r12,.L5090
	add	r1,r3,r3 lsl 1
	ldr	r3,[r12]
	ldr	r3,[r3,20]
	ldrb	r3,[r1,r3]
	ldr	r1,.L5091
	ldr	r1,[r1,r2 lsl 2]
	rsb	r3,r3,r3 lsl 2
	add	r4,r1,r3 lsl 3
	ldr	r1,.L5092
	ldr	r0,[r1,r0 lsl 2]
.L5097:

	bl	Dsadc_Hal_GetTriggerTimeStamp
	strh	r0,[r4,4]
.LDW24:
.L5099:

	pop	{r4,pc}
__ghs_eofn_Dsadc_TimestampIsr:
	.endf	Dsadc_TimestampIsr
	.endf	Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;CoreChIdx	r3	local

;HwUnitId	r0	param
;Channel	r3	param
;ChCfgPtr	r2	param

	.section ".ghrettbl",""
.L5094:	.data.w	.L5093
	.endo	.L5094
.L5096:	.data.w	.L5095
	.endo	.L5096
	.section ".ghcalltbl",""
.L5098:	.data.w	.L5097
	.endo	.L5098
	.section ".ghrettbl",""
.L5100:	.data.w	.L5099
	.endo	.L5100
	.data
	.global	__caller.Dsadc_Hal_GetTriggerTimeStamp.i.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.23:
	.endo	..gh.f.a.1.e.23
	.global	Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_InitChannel:
.LDW34:
	push	{r2,r4-r9,lr}
	mov	r9,r0
	ldr	r0,[r9,r1 lsl 2]
	ldr	r0,[r0,4]
.LDW44:
	mov	r7,r1
	mov	r1,44
	smlabb	r5,r2,r1,r0
	ldrb	r0,[r5]
	ldr	r6,.L5092
	ldr	r1,[r5,40]
	mov	r8,r2
	ldr	r0,[r6,r0 lsl 2]
.L5337:

	bl	Dsadc_Hal_InitModule
	mov	r4,r0
	ldrb	r0,[r9,28]
.L5339:

	bl	Dsadc_Hal_ConfigDsadc1InPort
	and	r4,r4,r0
	ldrb	r0,[r5]
	ldrb	r1,[r5,2]
	ldr	r0,[r6,r0 lsl 2]
.L5341:

	bl	Dsadc_Hal_EnableDithering
	and	r4,r4,r0
	ldrb	r0,[r5]
	ldr	r0,[r6,r0 lsl 2]
	ldr	r1,[r0,96]
	bfc	r1,1,1
	str	r1,[r0,96]
	mov	r1,1
	ldr	r2,[r0,96]
	tst	r2,2
	movne	r1,0
	and	r4,r4,r1
	ldr	r1,[r0,96]
	bfc	r1,0,1
	str	r1,[r0,96]
	mvn	r1,0
	ldr	r2,[r0,96]
	tst	r2,1
	movne	r1,0
	and	r4,r4,r1
	ldr	r1,[r5,36]
	cmp	r1,0
	beq	.L5119
.L5343:

	bl	Dsadc_Hal_ConfigCompensation
	and	r4,r4,r0
.L5119:
	ldrb	r0,[r5,3]
	cmp	r0,1
	bne	.L5121
	ldrb	r0,[r5]
	ldr	r1,[r5,4]
	mov	r2,1
	ldr	r0,[r6,r0 lsl 2]
.L5345:

	bl	Dsadc_Hal_ConfigBiasVoltage
	and	r4,r4,r0
.L5121:
	ldrb	r0,[r5]
	ldr	r0,[r6,r0 lsl 2]
.L5347:

	bl	Dsadc_Hal_CloseLoop
	ldr	r1,.L5091
	ldr	r1,[r1,r7 lsl 2]
	rsb	r3,r8,r8 lsl 2
	and	r4,r4,r0
	add	r0,r1,r3 lsl 3
	mov	r1,0
	str	r1,[r0,8]
	mov	r3,r1
	mov	r2,r1
	add	r12,r0,8
	strb	r1,[r0,6]
	stmib	r12,{r1-r3}
	strb	r1,[r0]
	strh	r1,[r0,2]
	mov	r1,r5
.L5349:

	bl	Dsadc_SetInterruptEnStatus
.LDW54:
	mov	r0,r4
.L5351:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Dsadc_InitChannel:
	.endf	Dsadc_InitChannel
	.endf	Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;SafetyErr	r4	local
;ChCfgPtr	r5	local
;ret	r1	local
;ret	r1	local

;ConfigPtr	r9	param
;CoreId	r7	param
;ChIdx	r8	param

	.section ".bss","awb"
.L5247:
	.endo	.L5247
	.section ".ghcalltbl",""
.L5338:	.data.w	.L5337
	.endo	.L5338
.L5340:	.data.w	.L5339
	.endo	.L5340
.L5342:	.data.w	.L5341
	.endo	.L5342
.L5344:	.data.w	.L5343
	.endo	.L5344
.L5346:	.data.w	.L5345
	.endo	.L5346
.L5348:	.data.w	.L5347
	.endo	.L5348
.L5350:	.data.w	.L5349
	.endo	.L5350
	.section ".ghrettbl",""
.L5352:	.data.w	.L5351
	.endo	.L5352
	.data
	.global	__caller.Dsadc_Hal_CloseLoop.i.p

	.global	__caller.Dsadc_Hal_ConfigBiasVoltage.i.pii

	.global	__caller.Dsadc_Hal_ConfigCompensation.i.pp

	.global	__caller.Dsadc_Hal_EnableDithering.i.pi

	.global	__caller.Dsadc_Hal_ConfigDsadc1InPort.i.i

	.global	__caller.Dsadc_Hal_InitModule.i.pp

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.24:
	.endo	..gh.f.a.1.e.24
	.global	Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_InitMasterCore:
.LDW64:
	push	{r2,r4-r5,lr}
	ldr	r3,.L5563
.LDW74:
	mov	r5,r0
	ldr	r0,[r3]
	orr	r0,r0,1<<20
	str	r0,[r3]
	ldr	r0,[r3]
	mov	r4,1
	and	r0,r0,1<<20
	cmp	r0,1<<20
	movne	r4,0
	ldr	r0,[r3]
	orr	r0,r0,1<<21
	str	r0,[r3]
	mvn	r1,0
	ldr	r0,[r3]
	and	r0,r0,1<<21
	cmp	r0,1<<21
	movne	r1,0
	and	r4,r4,r1
	ldr	r1,[r5,16]
	ldr	r1,[r1]
	and	r0,r1,3<<16
	and	r1,r1,255
	orr	r0,r1,r0 lsr 8
.L5565:

	bl	Dsadc_Hal_EnableModuleSync
	and	r4,r4,r0
	ldr	r0,[r5,16]
	ldr	r0,[r0]
.L5567:

	bl	Dsadc_Hal_EnableMainChannelSync
	and	r4,r4,r0
	ldr	r0,[r5,16]
	ldr	r0,[r0,4]
.L5569:

	bl	Dsadc_Hal_EnableAuxChannelSync
	and	r4,r4,r0
	ldr	r0,[r5,16]
	ldr	r0,[r0,8]
	cmp	r0,0
	beq	.L5371
.L5571:

	bl	Dsadc_Hal_ConfigCarrierWave
	and	r4,r4,r0
.L5371:
	ldr	r1,.L5564
	ldr	r0,.L5090
	mov	r2,0
	cmp	r4,1
	strb	r2,[r1]
	streq	r5,[r0]
	mov	r0,r4
.LDW84:
.L5573:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Dsadc_InitMasterCore:
	.endf	Dsadc_InitMasterCore
	.endf	Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;SafetyErr	r4	local
;ret	r4	local
;ret	r1	local

;ConfigPtr	r5	param

	.section ".ghcalltbl",""
.L5566:	.data.w	.L5565
	.endo	.L5566
.L5568:	.data.w	.L5567
	.endo	.L5568
.L5570:	.data.w	.L5569
	.endo	.L5570
.L5572:	.data.w	.L5571
	.endo	.L5572
	.section ".ghrettbl",""
.L5574:	.data.w	.L5573
	.endo	.L5574
	.data
	.global	__caller.Dsadc_Hal_ConfigCarrierWave.i.p

	.global	__caller.Dsadc_Hal_EnableAuxChannelSync.i.i

	.global	__caller.Dsadc_Hal_EnableMainChannelSync.i.i

	.global	__caller.Dsadc_Hal_EnableModuleSync.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.25:
	.endo	..gh.f.a.1.e.25
	.global	Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.:
Dsadc_GetStreamLastPointerErrCheck:
.LDW94:
	ldr	r2,.L5090
	str	lr,[sp,-8]!
	ldr	r2,[r2]
	ldr	r2,[r2,r0 lsl 2]
	ldr	r2,[r2,4]
	mov	r3,44
	smlabb	r2,r1,r3,r2
	ldrb	r3,[r2,10]
.LDW05:
	cmp	r3,2
	moveq	r3,26
	beq	.L5764
.L5577:
	ldr	r2,[r2,12]
	cmp	r2,0
	moveq	r3,27
	beq	.L5765
.L5580:
	ldr	r2,.L5091
	rsb	r1,r1,r1 lsl 2
	ldr	r0,[r2,r0 lsl 2]
	add	r0,r0,r1 lsl 3
	ldr	r0,[r0,8]
	cmp	r0,0
	bne	.L5583
.L5584:
	mov	r3,24
.L5764:

.L5765:

	mov	r2,5
	mov	r1,7
	mov	r0,255
.L5774:

	bl	Det_ReportError
	mov	r0,1
.L5776:

	ldr	pc,[sp],8
.L5583:
	mov	r0,0
.LDW15:
.L5778:

	ldr	pc,[sp],8
__ghs_eofn_Dsadc_GetStreamLastPointerErrCheck:
	.endf	Dsadc_GetStreamLastPointerErrCheck
	.endf	Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
;ChCfgPtr	r2	local

;CoreId	r0	param
;CoreChIdx	r1	param

	.section ".ghcalltbl",""
.L5775:	.data.w	.L5774
	.endo	.L5775
	.section ".ghrettbl",""
.L5777:	.data.w	.L5776
	.endo	.L5777
.L5779:	.data.w	.L5778
	.endo	.L5779
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
__callee.Dsadc_Init.v.p::
	.size	__callee.Dsadc_Init.v.p,0
Dsadc_Init::
.LDW25:
	push	{r2,r4-r7,lr}
.LDW35:
	mov	r5,1
	mov	r7,r0
.L6392:

	bl	Dsadc_CheckInitParam
	cmp	r0,0
.L6394:

	popne	{r2,r4-r7,pc}
	b	.L6390

.L5090:	.data.w	Dsadc_ConfigPtr
	.endo	.L5090

.L5091:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L5091

.L5092:	.data.w	Dsadc_BaseAddrs
	.endo	.L5092

.L5563:	.data.w	0xb0002090
	.endo	.L5563

.L5564:	.data.w	Dsadc_CarrierStatus
	.endo	.L5564

.L6390:

;line1981
..lin.6655f927..20e44bd7.0_12::
.LDWlin12:
..gh.beginasm.27:
	.endo	..gh.beginasm.27
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.28:
	.endo	..gh.endasm.28

;line1984
..lin.6655f927..20e44bd7.0_13::
.LDWlin13:
	ldr	r0,[r7,r4 lsl 2]
	cmp	r0,0
	movne	r6,0
	bne	.L5793
	b	.L5788
.L5792:
	lsr	r2,r6,24
	mov	r1,r4
	mov	r0,r7
.L6396:

	bl	Dsadc_InitChannel
	and	r5,r0,1
	add	r6,r6,1<<24
.L5793:
	ldr	r0,[r7,r4 lsl 2]
	ldrb	r0,[r0]
	cmp	r0,r6 lsr 24
	bls	.L5788
	cmp	r5,1
	beq	.L5792
.L5788:
	cmp	r4,0
	bne	.L5795
	mov	r0,r7
.L6398:

	bl	Dsadc_InitMasterCore
	and	r5,r5,r0
.L5795:
	cmp	r5,1
	ldreq	r0,.L6391
	ldreq	r0,[r0,r4 lsl 2]
	streq	r5,[r0]
.L6400:

	popeq	{r2,r4-r7,pc}
	movs	r2,r5
	moveq	r3,226
	moveq	r1,7
	moveq	r0,255
.L6402:

	bleq	Det_ReportRuntimeError
.LDW45:
.L6404:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_Init::
	.endf	Dsadc_Init
;SafetyErr	r5	local
;CoreId	r4	local

;ConfigPtr	r7	param

	.section ".bss","awb"
.L6276:
	.endo	.L6276
	.section ".ghcalltbl",""
.L6393:	.data.w	.L6392
	.endo	.L6393
	.section ".ghrettbl",""
.L6395:	.data.w	.L6394
	.endo	.L6395
	.section ".ghcalltbl",""
.L6397:	.data.w	.L6396
	.endo	.L6397
.L6399:	.data.w	.L6398
	.endo	.L6399
	.section ".ghrettbl",""
.L6401:	.data.w	.L6400
	.endo	.L6401
	.section ".ghcalltbl",""
.L6403:	.data.w	.L6402
	.endo	.L6403
	.section ".ghrettbl",""
.L6405:	.data.w	.L6404
	.endo	.L6405
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
__callee.Dsadc_DeInit.v.v::
	.size	__callee.Dsadc_DeInit.v.v,0
Dsadc_DeInit::
.LDW55:
	push	{r4-r8,lr}
.LDW65:
	mov	r6,1
	b	.L7004

.L6391:	.data.w	Dsadc_CoreInitStatusSetPtr
	.endo	.L6391

.L7004:

;line2058
..lin.6655f927..dec85e40.0_14::
.LDWlin14:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.31:
	.endo	..gh.endasm.31

;line2061
..lin.6655f927..dec85e40.0_15::
.LDWlin15:
	mov	r0,r5
.L7008:

	bl	Dsadc_CheckDeInit
	cmp	r0,0
.L7010:

	popne	{r4-r8,pc}
.L7012:

	bl	Dsadc_CheckAllChannelStatus
	movs	r4,r0
.L7014:

	popne	{r4-r8,pc}
	ldr	r7,.L7005
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	cmp	r0,0
	movne	r8,r4
	bne	.L6421
	b	.L6416
.L6420:
	mov	r2,44
	ldr	r0,[r0,4]
	mul	r1,r2,r1
	ldrb	r0,[r1,r0]
	cmp	r0,0
	beq	.L6422
.L7016:

	bl	Dsadc_DeInitChannel
	and	r6,r0,1
.L6422:
	ldr	r2,.L7006
	lsr	r1,r8,24
	ldr	r0,[r2,r5 lsl 2]
	rsb	r1,r1,r1 lsl 2
	add	r0,r0,r1 lsl 3
	str	r4,[r0,16]
	add	r8,r8,1<<24
	str	r4,[r0,20]
.L6421:
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	lsr	r1,r8,24
	ldrb	r2,[r0]
	cmp	r1,r2
	bhs	.L6416
	cmp	r6,1
	beq	.L6420
.L6416:
	cmp	r5,0
	bne	.L6425
.L6426:
	mov	r0,r4
.L7018:

	bl	Dsadc_DeInitChannel
	and	r6,r6,r0
	cmp	r6,1
	streq	r4,[r7]
.L6989:

	bne	.L6412
	ldr	r0,.L7007
	ldr	r0,[r0,r5 lsl 2]
	str	r4,[r0]
.L7020:

	pop	{r4-r8,pc}
.L6425:
	cmp	r6,1
	b	.L6989
.L6412:
	cmp	r6,0
	moveq	r3,226
	moveq	r2,1
	moveq	r1,7
	moveq	r0,255
.L7022:

	bleq	Det_ReportRuntimeError
.LDW75:
.L7024:

	pop	{r4-r8,pc}
__ghs_eofn_Dsadc_DeInit::
	.endf	Dsadc_DeInit
;SafetyErr	r6	local
;Err	r0	local
;CoreId	r5	local

	.section ".ghcalltbl",""
.L7009:	.data.w	.L7008
	.endo	.L7009
	.section ".ghrettbl",""
.L7011:	.data.w	.L7010
	.endo	.L7011
	.section ".ghcalltbl",""
.L7013:	.data.w	.L7012
	.endo	.L7013
	.section ".ghrettbl",""
.L7015:	.data.w	.L7014
	.endo	.L7015
	.section ".ghcalltbl",""
.L7017:	.data.w	.L7016
	.endo	.L7017
.L7019:	.data.w	.L7018
	.endo	.L7019
	.section ".ghrettbl",""
.L7021:	.data.w	.L7020
	.endo	.L7021
	.section ".ghcalltbl",""
.L7023:	.data.w	.L7022
	.endo	.L7023
	.section ".ghrettbl",""
.L7025:	.data.w	.L7024
	.endo	.L7025
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.32:
	.endo	..gh.f.a.1.e.32
__callee.Dsadc_SetupResultBuffer.i.ip::
	.size	__callee.Dsadc_SetupResultBuffer.i.ip,0
Dsadc_SetupResultBuffer::
.LDW85:
	push	{r4-r8,lr}
	mov	r8,r0
	mov	r6,r1
.LDW95:
	b	.L7660

.L7005:	.data.w	Dsadc_ConfigPtr
	.endo	.L7005

.L7006:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L7006

.L7007:	.data.w	Dsadc_CoreInitStatusSetPtr
	.endo	.L7007

.L7660:

;line2179
..lin.6655f927..d7841d8d.0_16::
.LDWlin16:
..gh.beginasm.33:
	.endo	..gh.beginasm.33
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.34:
	.endo	..gh.endasm.34

;line2182
..lin.6655f927..d7841d8d.0_17::
.LDWlin17:
	mov	r1,r4
	mov	r0,2
.L7663:

	bl	Dsadc_CheckInit
	cmp	r0,0
.L7665:

	popne	{r4-r8,pc}
	ldr	r7,.L7661
	ldr	r5,[r7]
	ldr	r5,[r5,20]
	add	r0,r8,r8 lsl 1
	mov	r3,20
	cmp	r6,0
	ldrb	r5,[r0,r5]
	beq	.L7652
	mov	r1,r8
	mov	r0,2
.L7667:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
.L7669:

	popne	{r4-r8,pc}
	ldr	r0,[r7]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	mov	r1,44
	smlabb	r0,r5,r1,r0
	ldrb	r0,[r0,10]
	mov	r3,26
	cmp	r0,2
	beq	.L7652
	ldr	r0,.L7662
	rsb	r2,r5,r5 lsl 2
	ldr	r0,[r0,r4 lsl 2]
	add	r0,r0,r2 lsl 3
	ldr	r1,[r0,20]
	cmp	r1,0
	ldreq	r2,[r0,16]
	cmpeq	r2,0
	strbeq	r2,[r0,6]
	streq	r6,[r0,8]
	moveq	r0,r1
.L7671:

	popeq	{r4-r8,pc}
.L7043:
	mov	r3,11
.L7652:

	mov	r2,2
	mov	r1,7
	mov	r0,255
.L7673:

	bl	Det_ReportError
	mov	r0,1
.L7026:
.LDW06:
.L7675:

	pop	{r4-r8,pc}
__ghs_eofn_Dsadc_SetupResultBuffer::
	.endf	Dsadc_SetupResultBuffer
;RetErr	r0	local
;CoreChIdx	r5	local
;CoreId	r4	local

;Channel	r8	param
;DataBufferPtr	r6	param

	.section ".ghcalltbl",""
.L7664:	.data.w	.L7663
	.endo	.L7664
	.section ".ghrettbl",""
.L7666:	.data.w	.L7665
	.endo	.L7666
	.section ".ghcalltbl",""
.L7668:	.data.w	.L7667
	.endo	.L7668
	.section ".ghrettbl",""
.L7670:	.data.w	.L7669
	.endo	.L7670
.L7672:	.data.w	.L7671
	.endo	.L7672
	.section ".ghcalltbl",""
.L7674:	.data.w	.L7673
	.endo	.L7674
	.section ".ghrettbl",""
.L7676:	.data.w	.L7675
	.endo	.L7676
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.35:
	.endo	..gh.f.a.1.e.35
__callee.Dsadc_StartConversion.i.i::
	.size	__callee.Dsadc_StartConversion.i.i,0
Dsadc_StartConversion::
.LDW16:
	push	{r2,r4-r7,lr}
	mov	r7,r0
.LDW26:
	b	.L8666

.L7661:	.data.w	Dsadc_ConfigPtr
	.endo	.L7661

.L7662:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L7662

.L8666:

;line2288
..lin.6655f927..8cd4d817.0_18::
.LDWlin18:
..gh.beginasm.36:
	.endo	..gh.beginasm.36
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.37:
	.endo	..gh.endasm.37

;line2291
..lin.6655f927..8cd4d817.0_19::
.LDWlin19:
	mov	r1,r4
	mov	r0,3
.L8670:

	bl	Dsadc_CheckInit
	cmp	r0,0
.L8672:

	popne	{r2,r4-r7,pc}
	ldr	r0,.L8667
	ldr	r1,[r0]
	add	r0,r7,r7 lsl 1
	ldr	r5,[r1,20]
	ldrb	r5,[r0,r5]
	ldr	r0,[r1,r4 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r6,r5,r1,r0
	mov	r1,r7
	mov	r0,3
.L8674:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
.L8676:

	popne	{r2,r4-r7,pc}
	ldrb	r0,[r6,10]
	cmp	r0,2
	beq	.L7692
	ldr	r2,.L8668
	rsb	r0,r5,r5 lsl 2
	ldr	r1,[r2,r4 lsl 2]
	add	r0,r1,r0 lsl 3
	ldr	r0,[r0,8]
	cmp	r0,0
	moveq	r3,24
	beq	.L8650
.L7692:
.L8678:

	bl	SchM_Enter_Dsadc_StartConversion
	ldr	r0,.L8668
	rsb	r1,r5,r5 lsl 2
	ldr	r0,[r0,r4 lsl 2]
	add	r4,r0,r1 lsl 3
	ldr	r0,[r4,20]
	cmp	r0,0
	cmpne	r0,3
	bne	.L7693
	ldr	r0,[r4,16]
	cmp	r0,0
	cmpne	r0,3
	bne	.L7693
	mov	r0,0
	strb	r0,[r4,6]
	ldrb	r0,[r6,10]
	cmp	r0,2
	movne	r0,0
	strne	r0,[r4,12]
	ldrbne	r0,[r6]
	ldrne	r1,.L8669
	ldrne	r0,[r1,r0 lsl 2]
	ldrhne	r1,[r4,2]
.L8680:

	blne	Dsadc_Hal_ClearInterruptStatus
	ldrb	r0,[r6]
	ldr	r7,.L8669
	ldr	r0,[r7,r0 lsl 2]
.L8682:

	bl	Dsadc_Hal_ClearFifo
	mov	r5,r0
	ldrb	r0,[r6]
	ldrh	r1,[r4,2]
	ldr	r0,[r7,r0 lsl 2]
.L8684:

	bl	Dsadc_Hal_EnableInterrupt
	and	r5,r5,r0
	cmp	r5,1
	bne	.L7700
	str	r5,[r4,20]
	ldr	r0,[r6,12]
	cmp	r0,0
	streq	r5,[r4,16]
.L8686:

	bl	SchM_Exit_Dsadc_StartConversion
	mov	r0,0
.L8688:

	pop	{r2,r4-r7,pc}
.L7700:
.L8690:

	bl	SchM_Exit_Dsadc_StartConversion
	mov	r3,226
	mov	r2,3
	mov	r1,7
	mov	r0,255
.L8692:

	bl	Det_ReportRuntimeError
	b	.L8651
.L7693:
.L8694:

	bl	SchM_Exit_Dsadc_StartConversion
	mov	r3,11
.L8650:

	mov	r2,3
	mov	r1,7
	mov	r0,255
.L8696:

	bl	Det_ReportError
.L8651:

	mov	r0,1
.LDW36:
.L8698:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_StartConversion::
	.endf	Dsadc_StartConversion
;SafetyErr	r5	local
;RetErr	r0	local
;CoreChIdx	r5	local
;ChCfgPtr	r6	local
;CoreId	r4	local

;Channel	r7	param

	.section ".ghcalltbl",""
.L8671:	.data.w	.L8670
	.endo	.L8671
	.section ".ghrettbl",""
.L8673:	.data.w	.L8672
	.endo	.L8673
	.section ".ghcalltbl",""
.L8675:	.data.w	.L8674
	.endo	.L8675
	.section ".ghrettbl",""
.L8677:	.data.w	.L8676
	.endo	.L8677
	.section ".ghcalltbl",""
.L8679:	.data.w	.L8678
	.endo	.L8679
.L8681:	.data.w	.L8680
	.endo	.L8681
.L8683:	.data.w	.L8682
	.endo	.L8683
.L8685:	.data.w	.L8684
	.endo	.L8685
.L8687:	.data.w	.L8686
	.endo	.L8687
	.section ".ghrettbl",""
.L8689:	.data.w	.L8688
	.endo	.L8689
	.section ".ghcalltbl",""
.L8691:	.data.w	.L8690
	.endo	.L8691
.L8693:	.data.w	.L8692
	.endo	.L8693
.L8695:	.data.w	.L8694
	.endo	.L8695
.L8697:	.data.w	.L8696
	.endo	.L8697
	.section ".ghrettbl",""
.L8699:	.data.w	.L8698
	.endo	.L8699
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Dsadc_StartConversion.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Dsadc_StartConversion.v.v

	.global	__caller.SchM_Exit_Dsadc_StartConversion.v.v

	.global	__caller.Dsadc_Hal_EnableInterrupt.i.pi

	.global	__caller.Dsadc_Hal_ClearFifo.i.p

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.SchM_Enter_Dsadc_StartConversion.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.38:
	.endo	..gh.f.a.1.e.38
__callee.Dsadc_StopConversion.i.i::
	.size	__callee.Dsadc_StopConversion.i.i,0
Dsadc_StopConversion::
.LDW46:
	push	{r2,r4-r7,lr}
	mov	r7,r0
.LDW56:
	b	.L8947

.L8667:	.data.w	Dsadc_ConfigPtr
	.endo	.L8667

.L8668:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L8668

.L8669:	.data.w	Dsadc_BaseAddrs
	.endo	.L8669

.L8947:

;line2449
..lin.6655f927..791b5bcf.0_20::
.LDWlin20:
..gh.beginasm.39:
	.endo	..gh.beginasm.39
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.40:
	.endo	..gh.endasm.40

	mov	r5,r2
;line2452
..lin.6655f927..791b5bcf.0_21::
.LDWlin21:
	mov	r1,r2
	mov	r0,4
.L8951:

	bl	Dsadc_CheckInit
	subs	r4,r0,0
	bne	.L8708
	mov	r1,r7
	mov	r0,4
.L8953:

	bl	Dsadc_CheckMulticoreAllocateError
	subs	r4,r0,0
	bne	.L8708
	ldr	r6,.L8948
	add	r7,r7,r7 lsl 1
	ldr	r4,[r6]
	ldr	r4,[r4,20]
	ldrb	r4,[r4,r7]
.L8955:

	bl	SchM_Enter_Dsadc_StopConversion
	ldr	r0,.L8949
	rsb	r1,r4,r4 lsl 2
	ldr	r0,[r0,r5 lsl 2]
	add	r5,r0,r1 lsl 3
	ldr	r0,[r5,20]
	cmp	r0,0
	ldreq	r0,[r5,16]
	cmpeq	r0,0
	beq	.L8710
	ldr	r0,[r6]
	ldr	r0,[r0,20]
	add	r0,r7,r0
	ldrb	r0,[r0,1]
	ldr	r4,.L8950
	ldrh	r1,[r5,2]
	ldr	r0,[r4,r0 lsl 2]
.L8957:

	bl	Dsadc_Hal_DisableInterrupt
	cmp	r0,1
	bne	.L8713
	ldr	r0,[r6]
	ldr	r0,[r0,20]
	add	r0,r7,r0
	ldrb	r0,[r0,1]
	ldrh	r1,[r5,2]
	ldr	r0,[r4,r0 lsl 2]
.L8959:

	bl	Dsadc_Hal_ClearInterruptStatus
	mov	r4,0
	str	r4,[r5,20]
	str	r4,[r5,16]
	strb	r4,[r5]
.L8961:

	bl	SchM_Exit_Dsadc_StopConversion
	b	.L8708
.L8713:
.L8963:

	bl	SchM_Exit_Dsadc_StopConversion
	mov	r3,226
	mov	r2,4
	mov	r1,7
	mov	r0,255
.L8965:

	bl	Det_ReportRuntimeError
	b	.L8937
.L8710:
.L8967:

	bl	SchM_Exit_Dsadc_StopConversion
	mov	r3,12
	mov	r2,4
	mov	r1,7
	mov	r0,255
.L8969:

	bl	Det_ReportError
.L8937:

	mov	r4,1
.L8708:
	mov	r0,r4
.LDW66:
.L8971:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_StopConversion::
	.endf	Dsadc_StopConversion
;RetErr	r4	local
;CoreChIdx	r4	local
;CoreId	r5	local

;Channel	r7	param

	.section ".ghcalltbl",""
.L8952:	.data.w	.L8951
	.endo	.L8952
.L8954:	.data.w	.L8953
	.endo	.L8954
.L8956:	.data.w	.L8955
	.endo	.L8956
.L8958:	.data.w	.L8957
	.endo	.L8958
.L8960:	.data.w	.L8959
	.endo	.L8960
.L8962:	.data.w	.L8961
	.endo	.L8962
.L8964:	.data.w	.L8963
	.endo	.L8964
.L8966:	.data.w	.L8965
	.endo	.L8966
.L8968:	.data.w	.L8967
	.endo	.L8968
.L8970:	.data.w	.L8969
	.endo	.L8970
	.section ".ghrettbl",""
.L8972:	.data.w	.L8971
	.endo	.L8972
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Dsadc_StopConversion.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Dsadc_StopConversion.v.v

	.global	__caller.SchM_Exit_Dsadc_StopConversion.v.v

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_DisableInterrupt.i.pi

	.global	__caller.SchM_Enter_Dsadc_StopConversion.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.41:
	.endo	..gh.f.a.1.e.41
__callee.Dsadc_GetStreamLastPointer.i.ip::
	.size	__callee.Dsadc_GetStreamLastPointer.i.ip,0
Dsadc_GetStreamLastPointer::
.LDW76:
	push	{r2,r4-r9,lr}
	mov	r9,r0
	mov	r7,r1
.LDW86:
	mov	r4,0
	b	.L9801

.L8948:	.data.w	Dsadc_ConfigPtr
	.endo	.L8948

.L8949:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L8949

.L8950:	.data.w	Dsadc_BaseAddrs
	.endo	.L8950

.L9801:

;line2593
..lin.6655f927..32e09684.0_22::
.LDWlin22:
..gh.beginasm.42:
	.endo	..gh.beginasm.42
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.43:
	.endo	..gh.endasm.43

;line2596
..lin.6655f927..32e09684.0_23::
.LDWlin23:
	mov	r1,r5
	mov	r0,5
.L9804:

	bl	Dsadc_CheckInit
	cmp	r0,0
	bne	.L8986
	ldr	r8,.L9802
	ldr	r6,[r8]
	ldr	r6,[r6,20]
	add	r0,r9,r9 lsl 1
	mov	r3,20
	cmp	r7,0
	ldrb	r6,[r0,r6]
	beq	.L9468
	mov	r1,r9
	mov	r0,5
.L9806:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L8986
	mov	r1,r6
	mov	r0,r5
.L9808:

	bl	Dsadc_GetStreamLastPointerErrCheck
	cmp	r0,0
	bne	.L8986
	str	r0,[r7]
	ldr	r0,[r8]
	ldr	r0,[r0,r5 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r8,r6,r1,r0
.L9810:

	bl	SchM_Enter_Dsadc_GetStreamLastPointer
	ldr	r0,.L9803
	rsb	r2,r6,r6 lsl 2
	ldr	r0,[r0,r5 lsl 2]
	add	r0,r0,r2 lsl 3
	ldr	r5,[r0,20]
	sub	r1,r5,2
	cmp	r1,1
	ldrls	r1,[r0,12]
	cmpls	r1,0
	ldrbeq	r4,[r0,6]
	ldreq	r2,[r0,8]
	addeq	r1,r2,r4 lsl 1
	subeq	r1,r1,2
	streq	r1,[r7]
	moveq	r1,1
	streq	r1,[r0,20]
	cmpeq	r5,3
	ldrbeq	r4,[r8,11]
	ldreq	r1,[r8,16]
	cmpeq	r1,0
	streq	r1,[r0,20]
.L9812:

	bl	SchM_Exit_Dsadc_GetStreamLastPointer
	mov	r3,12
	cmp	r5,0
.L9468:
	moveq	r2,5
	moveq	r1,7
	moveq	r0,255
.L9814:

	bleq	Det_ReportError
.L8986:
	mov	r0,r4
.LDW96:
.L9816:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Dsadc_GetStreamLastPointer::
	.endf	Dsadc_GetStreamLastPointer
;RetErr	r0	local
;CoreChIdx	r6	local
;ChStatus	r5	local
;ValidNum	r4	local
;CoreId	r5	local
;ChCfgPtr	r8	local

;Channel	r9	param
;PtrToSamplePtr	r7	param

	.section ".ghcalltbl",""
.L9805:	.data.w	.L9804
	.endo	.L9805
.L9807:	.data.w	.L9806
	.endo	.L9807
.L9809:	.data.w	.L9808
	.endo	.L9809
.L9811:	.data.w	.L9810
	.endo	.L9811
.L9813:	.data.w	.L9812
	.endo	.L9813
.L9815:	.data.w	.L9814
	.endo	.L9815
	.section ".ghrettbl",""
.L9817:	.data.w	.L9816
	.endo	.L9817
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Dsadc_GetStreamLastPointer.v.v

	.global	__caller.SchM_Enter_Dsadc_GetStreamLastPointer.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.44:
	.endo	..gh.f.a.1.e.44
__callee.Dsadc_GetChannelStatus.i.ii::
	.size	__callee.Dsadc_GetChannelStatus.i.ii,0
Dsadc_GetChannelStatus::
.LDW07:
	push	{r2,r4-r9,lr}
	mov	r7,r0
	mov	r8,r1
.LDW17:
	b	.L10352

.L9802:	.data.w	Dsadc_ConfigPtr
	.endo	.L9802

.L9803:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L9803

.L10352:

;line2744
..lin.6655f927..4ab4e140.0_24::
.LDWlin24:
..gh.beginasm.45:
	.endo	..gh.beginasm.45
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.46:
	.endo	..gh.endasm.46

;line2746
..lin.6655f927..4ab4e140.0_25::
.LDWlin25:
	mov	r4,0
	mov	r1,r5
	mov	r0,6
.L10355:

	bl	Dsadc_CheckInit
	cmp	r0,0
	bne	.L9832
	ldr	r9,.L10353
	ldr	r6,[r9]
	ldr	r6,[r6,20]
	add	r0,r7,r7 lsl 1
	mov	r1,r7
	ldrb	r6,[r0,r6]
	mov	r0,6
.L10357:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L9832
	cmp	r8,1
	ldreq	r0,[r9]
	ldreq	r0,[r0,r5 lsl 2]
	moveq	r1,44
	ldreq	r0,[r0,4]
	smlabbeq	r1,r6,r1,r0
	ldreq	r0,[r1,40]
	ldreq	r0,[r0,20]
	cmpeq	r0,0
	bne	.L9833
	mov	r3,29
	mov	r2,6
	mov	r1,7
	mov	r0,255
.L10359:

	bl	Det_ReportError
	b	.L9832
.L9833:
	ldr	r0,[r9]
	ldr	r0,[r0,r5 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r7,r6,r1,r0
.L10361:

	bl	SchM_Enter_Dsadc_GetChannelStatus
	ldr	r0,.L10354
	ldr	r0,[r0,r5 lsl 2]
	rsb	r2,r6,r6 lsl 2
	cmp	r8,1
	add	r0,r0,r2 lsl 3
	ldreq	r4,[r0,16]
	ldrne	r4,[r0,20]
	ldr	r1,[r7,12]
	cmp	r1,0
	bne	.L9837
	sub	r1,r4,2
	cmp	r1,1
	bhi	.L9837
	cmp	r8,1
	moveq	r1,16
	movne	r1,20
	add	r0,r1,r0
	mov	r1,1
	str	r1,[r0]
.L9837:
.L10363:

	bl	SchM_Exit_Dsadc_GetChannelStatus
.L9832:
	mov	r0,r4
.LDW27:
.L10365:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Dsadc_GetChannelStatus::
	.endf	Dsadc_GetChannelStatus
;CoreChIdx	r6	local
;RetStatus	r4	local
;CoreId	r5	local
;ChCfgPtr	r7	local

;Channel	r7	param
;ConvChannel	r8	param

	.section ".ghcalltbl",""
.L10356:	.data.w	.L10355
	.endo	.L10356
.L10358:	.data.w	.L10357
	.endo	.L10358
.L10360:	.data.w	.L10359
	.endo	.L10360
.L10362:	.data.w	.L10361
	.endo	.L10362
.L10364:	.data.w	.L10363
	.endo	.L10364
	.section ".ghrettbl",""
.L10366:	.data.w	.L10365
	.endo	.L10366
	.data
	.global	__caller.SchM_Exit_Dsadc_GetChannelStatus.v.v

	.global	__caller.SchM_Enter_Dsadc_GetChannelStatus.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.47:
	.endo	..gh.f.a.1.e.47
__callee.Dsadc_StartCarrierSignal.i.v::
	.size	__callee.Dsadc_StartCarrierSignal.i.v,0
Dsadc_StartCarrierSignal::
.LDW37:
	push	{r4,lr}
.LDW47:
	ldr	r0,.L10555
	ldr	r0,[r0]
	mov	r4,1
	cmp	r0,1
	beq	.L10369
.L10370:
	mov	r3,10
.L10544:

.L10545:

	mov	r2,9
	mov	r1,7
	mov	r0,255
.L10558:

	bl	Det_ReportError
	b	.L10371
.L10369:
	ldr	r0,.L10353
	ldr	r1,[r0]
	ldr	r1,[r1,16]
	ldr	r1,[r1,8]
	cmp	r1,0
	moveq	r3,34
	beq	.L10545
.L10372:
	ldr	r1,.L10556
	ldrb	r2,[r1]
	cmp	r2,1
	moveq	r3,32
	beq	.L10544
.L10380:
	ldr	r0,.L10557
	ldr	r2,[r0]
	orr	r2,r2,1
	str	r2,[r0]
	strb	r4,[r1]
	mov	r4,0
.L10371:
	mov	r0,r4
.LDW57:
.L10560:

	pop	{r4,pc}
__ghs_eofn_Dsadc_StartCarrierSignal::
	.endf	Dsadc_StartCarrierSignal
;RetErr	r4	local

	.section ".ghcalltbl",""
.L10559:	.data.w	.L10558
	.endo	.L10559
	.section ".ghrettbl",""
.L10561:	.data.w	.L10560
	.endo	.L10561
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.48:
	.endo	..gh.f.a.1.e.48
__callee.Dsadc_StopCarrierSignal.i.v::
	.size	__callee.Dsadc_StopCarrierSignal.i.v,0
Dsadc_StopCarrierSignal::
.LDW67:
	push	{r4,lr}
.LDW77:
	ldr	r0,.L10555
	ldr	r0,[r0]
	mov	r4,1
	cmp	r0,1
	movne	r3,10
	movne	r2,r3
	bne	.L10704
.L10564:
	ldr	r2,.L10556
	ldrb	r1,[r2]
	cmp	r1,0
	bne	.L10572
.L10568:
	mov	r3,33
	mov	r2,10
.L10704:

	mov	r1,7
	mov	r0,255
.L10712:

	bl	Det_ReportError
	b	.L10566
.L10572:
	ldr	r0,.L10557
	ldr	r1,[r0]
	bfc	r1,0,1
	mov	r4,0
	str	r1,[r0]
	strb	r4,[r2]
.L10566:
	mov	r0,r4
.LDW87:
.L10714:

	pop	{r4,pc}
__ghs_eofn_Dsadc_StopCarrierSignal::
	.endf	Dsadc_StopCarrierSignal
;RetErr	r4	local

	.section ".ghcalltbl",""
.L10713:	.data.w	.L10712
	.endo	.L10713
	.section ".ghrettbl",""
.L10715:	.data.w	.L10714
	.endo	.L10715
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.49:
	.endo	..gh.f.a.1.e.49
__callee.Dsadc_GetTimestamp.i.i::
	.size	__callee.Dsadc_GetTimestamp.i.i,0
Dsadc_GetTimestamp::
.LDW97:
	push	{r4-r8,lr}
	mov	r8,r0
.LDW08:
	mov	r4,0
	b	.L11010

.L10353:	.data.w	Dsadc_ConfigPtr
	.endo	.L10353

.L10354:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L10354

.L10555:	.data.w	Dsadc_InitFlgCore0
	.endo	.L10555

.L10556:	.data.w	Dsadc_CarrierStatus
	.endo	.L10556

.L10557:	.data.w	0xb000206c
	.endo	.L10557

.L11010:

;line3209
..lin.6655f927..3ac6b417.0_26::
.LDWlin26:
..gh.beginasm.50:
	.endo	..gh.beginasm.50
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.51:
	.endo	..gh.endasm.51

;line3212
..lin.6655f927..3ac6b417.0_27::
.LDWlin27:
	mov	r1,r5
	mov	r0,11
.L11013:

	bl	Dsadc_CheckInit
	cmp	r0,0
	bne	.L10735
	ldr	r7,.L11011
	ldr	r6,[r7]
	ldr	r6,[r6,20]
	add	r0,r8,r8 lsl 1
	mov	r1,r8
	ldrb	r6,[r0,r6]
	mov	r0,11
.L11015:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L10735
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r0,r6,r1,r0
	ldrb	r1,[r0,10]
	cmp	r1,2
	moveq	r3,26
	beq	.L10778
	ldr	r1,[r0,12]
	cmp	r1,1
	ldrbne	r0,[r0,9]
	cmpne	r0,0
	bne	.L10736
	mov	r3,28
.L10778:
	mov	r2,11
	mov	r1,7
	mov	r0,255
.L11017:

	bl	Det_ReportError
	b	.L10735
.L10736:
	ldr	r0,.L11012
	rsb	r1,r6,r6 lsl 2
	ldr	r0,[r0,r5 lsl 2]
	add	r0,r0,r1 lsl 3
	ldrh	r4,[r0,4]
.L10735:
	mov	r0,r4
.LDW18:
.L11019:

	pop	{r4-r8,pc}
__ghs_eofn_Dsadc_GetTimestamp::
	.endf	Dsadc_GetTimestamp
;CoreChIdx	r6	local
;CurrTimestamp	r4	local
;ChCfgPtr	r0	local
;CoreId	r5	local

;Channel	r8	param

	.section ".ghcalltbl",""
.L11014:	.data.w	.L11013
	.endo	.L11014
.L11016:	.data.w	.L11015
	.endo	.L11016
.L11018:	.data.w	.L11017
	.endo	.L11018
	.section ".ghrettbl",""
.L11020:	.data.w	.L11019
	.endo	.L11020
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.52:
	.endo	..gh.f.a.1.e.52
__callee.Dsadc_EnableNotification.v.i::
	.size	__callee.Dsadc_EnableNotification.v.i,0
Dsadc_EnableNotification::
.LDW28:
	push	{r2,r4-r7,lr}
	mov	r7,r0
.LDW38:
	b	.L11257

.L11011:	.data.w	Dsadc_ConfigPtr
	.endo	.L11011

.L11012:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L11012

.L11257:

;line3308
..lin.6655f927..a4aea531.0_28::
.LDWlin28:
..gh.beginasm.53:
	.endo	..gh.beginasm.53
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.54:
	.endo	..gh.endasm.54

;line3311
..lin.6655f927..a4aea531.0_29::
.LDWlin29:
	mov	r1,r4
	mov	r0,12
.L11260:

	bl	Dsadc_CheckInit
	cmp	r0,0
.L11262:

	popne	{r2,r4-r7,pc}
	ldr	r6,.L11258
	ldr	r5,[r6]
	ldr	r5,[r5,20]
	add	r0,r7,r7 lsl 1
	mov	r1,r7
	ldrb	r5,[r0,r5]
	mov	r0,12
.L11264:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
.L11266:

	popne	{r2,r4-r7,pc}
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r1,r5,r1,r0
	ldr	r0,[r1,20]
	cmp	r0,0
	ldreq	r0,[r1,24]
	cmpeq	r0,0
	ldreq	r0,[r1,28]
	cmpeq	r0,0
	bne	.L11036
	mov	r3,23
	mov	r2,12
	mov	r1,7
	mov	r0,255
.L11268:

	bl	Det_ReportError
.L11270:

	pop	{r2,r4-r7,pc}
.L11036:
	ldr	r1,.L11259
	ldr	r1,[r1,r4 lsl 2]
	rsb	r0,r5,r5 lsl 2
	mov	r2,1
	strb	r2,[r1,r0 lsl 3]
.LDW48:
.L11272:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_EnableNotification::
	.endf	Dsadc_EnableNotification
;CoreChIdx	r5	local
;ChCfgPtr	r1	local
;CoreId	r4	local

;Channel	r7	param

	.section ".ghcalltbl",""
.L11261:	.data.w	.L11260
	.endo	.L11261
	.section ".ghrettbl",""
.L11263:	.data.w	.L11262
	.endo	.L11263
	.section ".ghcalltbl",""
.L11265:	.data.w	.L11264
	.endo	.L11265
	.section ".ghrettbl",""
.L11267:	.data.w	.L11266
	.endo	.L11267
	.section ".ghcalltbl",""
.L11269:	.data.w	.L11268
	.endo	.L11269
	.section ".ghrettbl",""
.L11271:	.data.w	.L11270
	.endo	.L11271
.L11273:	.data.w	.L11272
	.endo	.L11273
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.55:
	.endo	..gh.f.a.1.e.55
__callee.Dsadc_DisableNotification.v.i::
	.size	__callee.Dsadc_DisableNotification.v.i,0
Dsadc_DisableNotification::
.LDW58:
	push	{r2,r4-r7,lr}
	mov	r7,r0
.LDW68:
	b	.L11513

.L11258:	.data.w	Dsadc_ConfigPtr
	.endo	.L11258

.L11259:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L11259

.L11513:

;line3383
..lin.6655f927..3603757e.0_30::
.LDWlin30:
..gh.beginasm.56:
	.endo	..gh.beginasm.56
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.57:
	.endo	..gh.endasm.57

;line3386
..lin.6655f927..3603757e.0_31::
.LDWlin31:
	mov	r1,r4
	mov	r0,13
.L11516:

	bl	Dsadc_CheckInit
	cmp	r0,0
.L11518:

	popne	{r2,r4-r7,pc}
	ldr	r6,.L11514
	ldr	r5,[r6]
	ldr	r5,[r5,20]
	add	r0,r7,r7 lsl 1
	mov	r1,r7
	ldrb	r5,[r0,r5]
	mov	r0,13
.L11520:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
.L11522:

	popne	{r2,r4-r7,pc}
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	mov	r1,44
	ldr	r0,[r0,4]
	smlabb	r1,r5,r1,r0
	ldr	r0,[r1,20]
	cmp	r0,0
	ldreq	r0,[r1,24]
	cmpeq	r0,0
	ldreq	r0,[r1,28]
	cmpeq	r0,0
	bne	.L11289
	mov	r3,23
	mov	r2,13
	mov	r1,7
	mov	r0,255
.L11524:

	bl	Det_ReportError
.L11526:

	pop	{r2,r4-r7,pc}
.L11289:
	ldr	r1,.L11515
	ldr	r1,[r1,r4 lsl 2]
	rsb	r0,r5,r5 lsl 2
	mov	r2,0
	strb	r2,[r1,r0 lsl 3]
.LDW78:
.L11528:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_DisableNotification::
	.endf	Dsadc_DisableNotification
;CoreChIdx	r5	local
;CoreId	r4	local
;ChCfgPtr	r1	local

;Channel	r7	param

	.section ".ghcalltbl",""
.L11517:	.data.w	.L11516
	.endo	.L11517
	.section ".ghrettbl",""
.L11519:	.data.w	.L11518
	.endo	.L11519
	.section ".ghcalltbl",""
.L11521:	.data.w	.L11520
	.endo	.L11521
	.section ".ghrettbl",""
.L11523:	.data.w	.L11522
	.endo	.L11523
	.section ".ghcalltbl",""
.L11525:	.data.w	.L11524
	.endo	.L11525
	.section ".ghrettbl",""
.L11527:	.data.w	.L11526
	.endo	.L11527
.L11529:	.data.w	.L11528
	.endo	.L11529
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.58:
	.endo	..gh.f.a.1.e.58
__callee.Dsadc_GetVersionInfo.v.p::
	.size	__callee.Dsadc_GetVersionInfo.v.p,0
Dsadc_GetVersionInfo::
.LDW88:
.LDW98:
	cmp	r0,0
	moveq	r3,20
	moveq	r2,14
	moveq	r1,7
	moveq	r0,255
.L11611:

	beq	Det_ReportError
.L11532:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,255
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW09:
.L11613:

	ret	
__ghs_eofn_Dsadc_GetVersionInfo::
	.endf	Dsadc_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L11573:
	.endo	.L11573
	.section ".ghtailcalltbl",""
	.align	4
.L11612:	.data.w	.L11611
	.endo	.L11612
	.section ".ghrettbl",""
.L11614:	.data.w	.L11613
	.endo	.L11614
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.59:
	.endo	..gh.f.a.1.e.59
__callee.Dsadc_AuxiliaryChannel_ISRHandler.v.i::
	.size	__callee.Dsadc_AuxiliaryChannel_ISRHandler.v.i,0
Dsadc_AuxiliaryChannel_ISRHandler::
.LDW19:
	push	{r2,r4-r7,lr}
	mov	r5,r0
	ldr	r6,.L11514
.LDW29:
	b	.L11802

.L11514:	.data.w	Dsadc_ConfigPtr
	.endo	.L11514

.L11515:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L11515

.L11802:

;line3517
..lin.6655f927..961f801f.0_32::
.LDWlin32:
..gh.beginasm.60:
	.endo	..gh.beginasm.60
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.61:
	.endo	..gh.endasm.61

;line3520
..lin.6655f927..961f801f.0_33::
.LDWlin33:
	mov	r1,r4
	mov	r0,224
.L11805:

	bl	Dsadc_CheckInit
	cmp	r0,0
	bne	.L11621
	ldr	r7,[r6]
	ldr	r7,[r7,24]
	ldrb	r7,[r7,r5]
	mov	r0,224
	mov	r1,r7
.L11807:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L11621
	ldr	r1,[r6]
	ldr	r1,[r1,20]
	add	r0,r7,r7 lsl 1
	ldr	r3,.L11803
	ldrb	r0,[r0,r1]
	ldr	r2,[r3,r4 lsl 2]
	rsb	r1,r0,r0 lsl 2
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,16]
	cmp	r1,0
	bne	.L11627
	mov	r3,12
	mov	r2,224
	mov	r1,7
	mov	r0,255
.L11809:

	bl	Det_ReportError
	b	.L11628
.L11621:
	cmp	r0,1
	bne	.L11627
.L11628:
	ldr	r0,.L11804
	ldr	r4,[r0,r5 lsl 2]
	mov	r0,r4
.L11811:

	bl	Dsadc_Hal_GetInterruptStatus
	mov	r1,r0
	mov	r0,r4
.L11813:

	bl	Dsadc_Hal_ClearInterruptStatus
.L11815:

	pop	{r2,r4-r7,pc}
.L11627:
	ldr	r1,[r6]
	ldr	r1,[r1,r4 lsl 2]
	mov	r2,44
	ldr	r1,[r1,4]
	smlabb	r2,r0,r2,r1
	mov	r1,r7
	mov	r0,r5
.L11817:

	bl	Dsadc_AuxIsrEventEntry
.LDW39:
.L11819:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_AuxiliaryChannel_ISRHandler::
	.endf	Dsadc_AuxiliaryChannel_ISRHandler
;Err	r0	local
;Channel	r7	local
;CoreChIdx	r0	local
;CoreId	r4	local

;HwUnitId	r5	param

	.section ".ghcalltbl",""
.L11806:	.data.w	.L11805
	.endo	.L11806
.L11808:	.data.w	.L11807
	.endo	.L11808
.L11810:	.data.w	.L11809
	.endo	.L11810
.L11812:	.data.w	.L11811
	.endo	.L11812
.L11814:	.data.w	.L11813
	.endo	.L11814
	.section ".ghrettbl",""
.L11816:	.data.w	.L11815
	.endo	.L11816
	.section ".ghcalltbl",""
.L11818:	.data.w	.L11817
	.endo	.L11818
	.section ".ghrettbl",""
.L11820:	.data.w	.L11819
	.endo	.L11820
	.data
	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetInterruptStatus.i.p

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_ConfigPtr - Dsadc_ConfigPtr) +0 == 0
..gh.f.a.1.e.62:
	.endo	..gh.f.a.1.e.62
__callee.Dsadc_MainChannel_ISRHandler.v.i::
	.size	__callee.Dsadc_MainChannel_ISRHandler.v.i,0
Dsadc_MainChannel_ISRHandler::
.LDW49:
	push	{r2,r4-r7,lr}
	mov	r5,r0
	ldr	r6,.L12026
.LDW59:
	b	.L12027

.L11803:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L11803

.L11804:	.data.w	Dsadc_BaseAddrs
	.endo	.L11804

.L12026:	.data.w	Dsadc_ConfigPtr
	.endo	.L12026

.L12027:

;line3619
..lin.6655f927..11934cac.0_34::
.LDWlin34:
..gh.beginasm.63:
	.endo	..gh.beginasm.63
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.64:
	.endo	..gh.endasm.64

;line3622
..lin.6655f927..11934cac.0_35::
.LDWlin35:
	mov	r1,r4
	mov	r0,225
.L12030:

	bl	Dsadc_CheckInit
	cmp	r0,0
	bne	.L11827
	ldr	r7,[r6]
	ldr	r7,[r7,24]
	ldrb	r7,[r7,r5]
	mov	r0,225
	mov	r1,r7
.L12032:

	bl	Dsadc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L11827
	ldr	r1,[r6]
	ldr	r1,[r1,20]
	add	r0,r7,r7 lsl 1
	ldr	r3,.L12028
	ldrb	r0,[r0,r1]
	ldr	r2,[r3,r4 lsl 2]
	rsb	r1,r0,r0 lsl 2
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,20]
	cmp	r1,0
	bne	.L11833
	mov	r3,12
	mov	r2,225
	mov	r1,7
	mov	r0,255
.L12034:

	bl	Det_ReportError
	b	.L11834
.L11827:
	cmp	r0,1
	bne	.L11833
.L11834:
	ldr	r0,.L12029
	ldr	r4,[r0,r5 lsl 2]
	mov	r0,r4
.L12036:

	bl	Dsadc_Hal_GetInterruptStatus
	mov	r1,r0
	mov	r0,r4
.L12038:

	bl	Dsadc_Hal_ClearInterruptStatus
.L12040:

	pop	{r2,r4-r7,pc}
.L11833:
	ldr	r1,[r6]
	ldr	r1,[r1,r4 lsl 2]
	mov	r2,44
	ldr	r1,[r1,4]
	smlabb	r2,r0,r2,r1
	mov	r1,r7
	mov	r0,r5
.L12042:

	bl	Dsadc_IsrEventEntry
	cmp	r0,0
	moveq	r3,226
	moveq	r2,225
	moveq	r1,7
	moveq	r0,255
.L12044:

	bleq	Det_ReportRuntimeError
.LDW69:
.L12046:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Dsadc_MainChannel_ISRHandler::
	.endf	Dsadc_MainChannel_ISRHandler
;Err	r0	local
;Channel	r7	local
;CoreChIdx	r0	local
;CoreId	r4	local

;HwUnitId	r5	param

	.section ".ghcalltbl",""
.L12031:	.data.w	.L12030
	.endo	.L12031
.L12033:	.data.w	.L12032
	.endo	.L12033
.L12035:	.data.w	.L12034
	.endo	.L12035
.L12037:	.data.w	.L12036
	.endo	.L12037
.L12039:	.data.w	.L12038
	.endo	.L12039
	.section ".ghrettbl",""
.L12041:	.data.w	.L12040
	.endo	.L12041
	.section ".ghcalltbl",""
.L12043:	.data.w	.L12042
	.endo	.L12043
.L12045:	.data.w	.L12044
	.endo	.L12045
	.section ".ghrettbl",""
.L12047:	.data.w	.L12046
	.endo	.L12047
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Dsadc_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Dsadc_Hal_GetInterruptStatus.i.p

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"

.L12028:	.data.w	Dsadc_CoreDataSetPtr
	.endo	.L12028

.L12029:	.data.w	Dsadc_BaseAddrs
	.endo	.L12029

;Dsadc_InitFlgCore0	Dsadc_InitFlgCore0	static
;Dsadc_DataCore0	Dsadc_DataCore0	static
;Dsadc_CarrierStatus	Dsadc_CarrierStatus	static
;Dsadc_ConfigPtr	Dsadc_ConfigPtr	static
;Dsadc_CoreInitStatusSetPtr	Dsadc_CoreInitStatusSetPtr	static
;Dsadc_CoreDataSetPtr	Dsadc_CoreDataSetPtr	static
;Dsadc_BaseAddrs	Dsadc_BaseAddrs	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682568..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	121,75,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,115,114,99,47,68,115,97,100,99,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 36
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+36
	.section	.debug_str		;off: 180
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+180
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
	.data.b	22,17,0,0
	.data.b	2,0
	.data.b	173,6,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,115,114,99,47,68,115,97,100,99,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,77,99,97,108,108,92,105,110,99,108,117,100,101,92,77,99,97,108,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,77,99,97,108,108,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,77,99,97,108,108,92,105,110,99,108,117,100,101,92,77,99,97,108,108,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,105,110,99,108,117,100,101,92,68,115,97,100,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,100,115,97,100,99,92,105,110,99,92,100,115,97,100,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,100,115,97,100,99,92,105,110,99,92,100,115,97,100,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,100,115,97,100,99,92,105,110,99,92,100,115,97,100,99,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,68,115,97,100,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,100,101,118,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,68,115,97,100,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,68,101,116,92,105,110,99,108,117,100,101,92,68,101,116,46,104,0
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
	.data.w	.Ldw_begin+1716
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
	.section	.debug_str		;off: 202
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+202
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
	.section	.debug_str		;off: 216
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 50
	.data.w	.Ldw_str_begin+216
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 230
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 57
	.data.w	.Ldw_str_begin+230
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1477
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
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 249
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 115
	.data.w	.Ldw_str_begin+249
	.data.b	7
	.data.b	2

	.data.b	49
	.data.w	.Ldw_begin+10103

	.section	.debug_abbrev		;off: 48
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 126
	.data.b	47
	.data.w	.Ldw_begin+10638

	.section	.debug_abbrev		;off: 55
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 131
	.data.b	53
	.data.w	.Ldw_begin+126

	.section	.debug_abbrev		;off: 62
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 136
	.data.b	47
	.data.w	.Ldw_begin+131

	.data.b	74
	.data.w	.Ldw_begin+1513
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+12631
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+10638

	.data.b	47
	.data.w	.Ldw_begin+180

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+14160

	.data.b	53
	.data.w	.Ldw_begin+228

	.data.b	47
	.data.w	.Ldw_begin+233

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+238
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1728
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1728
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+13927

	.data.b	53
	.data.w	.Ldw_begin+307

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+13617

	.data.b	47
	.data.w	.Ldw_begin+337

	.data.b	47
	.data.w	.Ldw_begin+312

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 69
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 354
	.data.b	23
	.data.w	.Ldw_begin+342
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+347
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+347
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 264
	.data.b	115,104,111,114,116,0
	.section	.debug_info		;off: 389
	.data.w	.Ldw_str_begin+264
	.data.b	5
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+347
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+347
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13087
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+347
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+238
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1728
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+238
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1728
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+238
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+13087

	.data.b	47
	.data.w	.Ldw_begin+547

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+552
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+547

	.data.b	47
	.data.w	.Ldw_begin+602

	.data.b	74
	.data.w	.Ldw_begin+13111
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+607
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+13223
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13388
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+13099
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13075
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1648

	.data.b	47
	.data.w	.Ldw_begin+695

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+700
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13123
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 270
	.data.b	105,110,116,0
	.section	.debug_info		;off: 733
	.data.w	.Ldw_str_begin+270
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 274
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 740
	.data.w	.Ldw_str_begin+274
	.data.b	7
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+10651

	.data.b	47
	.data.w	.Ldw_begin+11887

	.data.b	53
	.data.w	.Ldw_begin+751

	.data.b	47
	.data.w	.Ldw_begin+11942

	.data.b	53
	.data.w	.Ldw_begin+761

	.data.b	47
	.data.w	.Ldw_begin+12048

	.data.b	53
	.data.w	.Ldw_begin+771

	.data.b	47
	.data.w	.Ldw_begin+12175

	.data.b	53
	.data.w	.Ldw_begin+781

	.data.b	47
	.data.w	.Ldw_begin+12400

	.data.b	53
	.data.w	.Ldw_begin+791

	.data.b	47
	.data.w	.Ldw_begin+12489

	.data.b	53
	.data.w	.Ldw_begin+801

	.data.b	47
	.data.w	.Ldw_begin+12120

	.data.b	53
	.data.w	.Ldw_begin+811

	.data.b	47
	.data.w	.Ldw_begin+12527

	.data.b	53
	.data.w	.Ldw_begin+821

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13388
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+831

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+845

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+13346
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+13087
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+853

	.data.b	47
	.data.w	.Ldw_begin+13062

	.data.b	53
	.data.w	.Ldw_begin+873

	.data.b	47
	.data.w	.Ldw_begin+12918

	.data.b	53
	.data.w	.Ldw_begin+883

	.data.b	47
	.data.w	.Ldw_begin+13007

	.data.b	53
	.data.w	.Ldw_begin+893

	.data.b	47
	.data.w	.Ldw_begin+13982

	.data.b	53
	.data.w	.Ldw_begin+903

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+908

	.section	.debug_abbrev		;off: 76
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 920
	.data.b	56
	.data.w	.Ldw_begin+732
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

	.section	.debug_info		;off: 928
	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+14054

	.data.b	53
	.data.w	.Ldw_begin+929

	.data.b	47
	.data.w	.Ldw_begin+13460

	.data.b	53
	.data.w	.Ldw_begin+939

	.data.b	47
	.data.w	.Ldw_begin+1489

	.data.b	53
	.data.w	.Ldw_begin+949

	.data.b	64
	.data.b	0
	.data.b	96
	.data.w	.Ldw_begin+13617

	.data.b	56
	.data.w	.Ldw_begin+732
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+13164

	.data.b	47
	.data.w	.Ldw_begin+975

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+980

	.data.b	56
	.data.w	.Ldw_begin+732
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+342

	.data.b	56
	.data.w	.Ldw_begin+732
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+185

	.data.b	56
	.data.w	.Ldw_begin+732
	.data.b	4
	.data.b	0
	.data.b	9

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1832
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1832
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+776

	.data.b	47
	.data.w	.Ldw_begin+786

	.data.b	47
	.data.w	.Ldw_begin+796

	.data.b	47
	.data.w	.Ldw_begin+806

	.data.b	47
	.data.w	.Ldw_begin+826

	.data.b	47
	.data.w	.Ldw_begin+888

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1080
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+898

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1104
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1525
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1513
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+12569
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1513
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1513
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+878

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1317
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+12696
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1477
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+12761
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

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1513
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1549
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1513
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1489
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 287
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1478
	.data.w	.Ldw_str_begin+287
	.data.b	51
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+42

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

	.section	.debug_info		;off: 1489
	.data.b	45
	.section	.debug_str		;off: 295
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1490
	.data.w	.Ldw_str_begin+295
	.data.b	56
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 301
	.data.b	115,105,110,116,49,54,0
	.section	.debug_info		;off: 1502
	.data.w	.Ldw_str_begin+301
	.data.b	58
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+388

	.data.b	45
	.section	.debug_str		;off: 308
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1514
	.data.w	.Ldw_str_begin+308
	.data.b	60
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+114

	.data.b	45
	.section	.debug_str		;off: 315
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1526
	.data.w	.Ldw_str_begin+315
	.data.b	64
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 322
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1538
	.data.w	.Ldw_str_begin+322
	.data.b	68
	.data.b	29
	.data.b	10
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 329
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1550
	.data.w	.Ldw_str_begin+329
	.data.b	39
	.data.b	15
	.data.b	5
	.data.w	.Ldw_begin+1489

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	5
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

	.section	.debug_info		;off: 1567
	.data.b	40
	.section	.debug_str		;off: 344
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1568
	.data.w	.Ldw_str_begin+344
	.data.b	63
	.data.b	13
	.data.b	5
	.data.w	.Ldw_begin+1513
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

	.section	.debug_info		;off: 1583
	.data.b	40
	.section	.debug_str		;off: 353
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1584
	.data.w	.Ldw_str_begin+353
	.data.b	64
	.data.b	13
	.data.b	5
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1600
	.data.w	.Ldw_str_begin+362
	.data.b	65
	.data.b	13
	.data.b	5
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1616
	.data.w	.Ldw_str_begin+379
	.data.b	66
	.data.b	13
	.data.b	5
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 396
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1632
	.data.w	.Ldw_str_begin+396
	.data.b	67
	.data.b	13
	.data.b	5
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 413
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1649
	.data.w	.Ldw_str_begin+413
	.data.b	68
	.data.b	2
	.data.b	5
	.data.w	.Ldw_begin+1561

	.data.b	52
	.section	.debug_str		;off: 433
	.data.b	0
	.section	.debug_info		;off: 1661
	.data.w	.Ldw_str_begin+433
	.data.b	36
	.data.b	1
	.data.b	11
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

	.section	.debug_info		;off: 1670
	.data.b	51
	.section	.debug_str		;off: 434
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 1671
	.data.w	.Ldw_str_begin+434
	.data.b	37
	.data.b	5
	.data.b	11
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

	.section	.debug_info		;off: 1679
	.data.b	51
	.section	.debug_str		;off: 451
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 1680
	.data.w	.Ldw_str_begin+451
	.data.b	38
	.data.b	5
	.data.b	11
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 468
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 1689
	.data.w	.Ldw_str_begin+468
	.data.b	39
	.data.b	5
	.data.b	11
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 485
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 1698
	.data.w	.Ldw_str_begin+485
	.data.b	40
	.data.b	5
	.data.b	11
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 502
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 1707
	.data.w	.Ldw_str_begin+502
	.data.b	41
	.data.b	5
	.data.b	11
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 519
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1717
	.data.w	.Ldw_str_begin+519
	.data.b	42
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1660

	.data.b	45
	.section	.debug_str		;off: 531
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 1729
	.data.w	.Ldw_str_begin+531
	.data.b	32
	.data.b	21
	.data.b	4
	.data.w	.Ldw_begin+1716

	.data.b	52
	.section	.debug_str		;off: 545
	.data.b	0
	.section	.debug_info		;off: 1741
	.data.w	.Ldw_str_begin+545
	.data.b	39
	.data.b	1
	.data.b	4
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 546
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 1751
	.data.w	.Ldw_str_begin+546
	.data.b	41
	.data.b	5
	.data.b	4
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 564
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 1760
	.data.w	.Ldw_str_begin+564
	.data.b	43
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 581
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 1769
	.data.w	.Ldw_str_begin+581
	.data.b	45
	.data.b	5
	.data.b	4
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 599
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 1778
	.data.w	.Ldw_str_begin+599
	.data.b	47
	.data.b	5
	.data.b	4
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 616
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 1787
	.data.w	.Ldw_str_begin+616
	.data.b	49
	.data.b	5
	.data.b	4
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 633
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 1796
	.data.w	.Ldw_str_begin+633
	.data.b	51
	.data.b	5
	.data.b	4
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 650
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 1805
	.data.w	.Ldw_str_begin+650
	.data.b	53
	.data.b	5
	.data.b	4
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 667
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 1814
	.data.w	.Ldw_str_begin+667
	.data.b	55
	.data.b	5
	.data.b	4
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 684
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 1823
	.data.w	.Ldw_str_begin+684
	.data.b	57
	.data.b	5
	.data.b	4
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 701
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 1833
	.data.w	.Ldw_str_begin+701
	.data.b	58
	.data.b	3
	.data.b	4
	.data.w	.Ldw_begin+1740

	.data.b	45
	.section	.debug_str		;off: 717
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 1845
	.data.w	.Ldw_str_begin+717
	.data.b	24
	.data.b	22
	.data.b	15
	.data.w	.Ldw_begin+739

	.data.b	71
	.data.b	36
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 724
	.data.b	80,73,78,83,69,84,0
	.section	.debug_info		;off: 1863
	.data.w	.Ldw_str_begin+724
	.data.b	37
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
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

	.section	.debug_info		;off: 1881
	.data.b	41
	.section	.debug_str		;off: 731
	.data.b	78,73,78,83,69,84,0
	.section	.debug_info		;off: 1882
	.data.w	.Ldw_str_begin+731
	.data.b	38
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 738
	.data.b	80,73,78,69,78,0
	.section	.debug_info		;off: 1901
	.data.w	.Ldw_str_begin+738
	.data.b	39
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 744
	.data.b	78,73,78,69,78,0
	.section	.debug_info		;off: 1920
	.data.w	.Ldw_str_begin+744
	.data.b	40
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 750
	.data.b	80,71,65,71,83,69,76,0
	.section	.debug_info		;off: 1939
	.data.w	.Ldw_str_begin+750
	.data.b	41
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 758
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 1958
	.data.w	.Ldw_str_begin+758
	.data.b	42
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 769
	.data.b	73,78,80,83,69,76,0
	.section	.debug_info		;off: 1977
	.data.w	.Ldw_str_begin+769
	.data.b	43
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 776
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 1996
	.data.w	.Ldw_str_begin+776
	.data.b	44
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 787
	.data.b	73,78,77,85,88,83,0
	.section	.debug_info		;off: 2015
	.data.w	.Ldw_str_begin+787
	.data.b	45
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 794
	.data.b	67,79,77,86,79,83,80,65,69,78,0
	.section	.debug_info		;off: 2034
	.data.w	.Ldw_str_begin+794
	.data.b	46
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 805
	.data.b	73,78,77,67,80,0
	.section	.debug_info		;off: 2053
	.data.w	.Ldw_str_begin+805
	.data.b	47
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	18
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 811
	.data.b	73,78,77,67,67,0
	.section	.debug_info		;off: 2072
	.data.w	.Ldw_str_begin+811
	.data.b	48
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 817
	.data.b	73,78,80,87,80,0
	.section	.debug_info		;off: 2091
	.data.w	.Ldw_str_begin+817
	.data.b	49
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 823
	.data.b	70,68,73,86,67,0
	.section	.debug_info		;off: 2110
	.data.w	.Ldw_str_begin+823
	.data.b	50
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 829
	.data.b	65,80,67,0
	.section	.debug_info		;off: 2129
	.data.w	.Ldw_str_begin+829
	.data.b	51
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 833
	.data.b	77,80,83,87,80,0
	.section	.debug_info		;off: 2148
	.data.w	.Ldw_str_begin+833
	.data.b	52
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 839
	.data.b	114,101,115,101,114,118,101,100,95,50,50,0
	.section	.debug_info		;off: 2167
	.data.w	.Ldw_str_begin+839
	.data.b	53
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	4
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 851
	.data.b	73,78,80,65,67,83,69,76,0
	.section	.debug_info		;off: 2186
	.data.w	.Ldw_str_begin+851
	.data.b	54
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 860
	.data.b	73,78,78,65,67,83,69,76,0
	.section	.debug_info		;off: 2205
	.data.w	.Ldw_str_begin+860
	.data.b	55
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 869
	.data.b	73,78,80,66,68,83,69,76,0
	.section	.debug_info		;off: 2224
	.data.w	.Ldw_str_begin+869
	.data.b	56
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 878
	.data.b	73,78,78,66,68,83,69,76,0
	.section	.debug_info		;off: 2243
	.data.w	.Ldw_str_begin+878
	.data.b	57
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 887
	.data.b	68,83,65,68,67,95,77,79,68,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 2263
	.data.w	.Ldw_str_begin+887
	.data.b	58
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+1856

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 905
	.data.b	84,82,71,83,69,76,0
	.section	.debug_info		;off: 2281
	.data.w	.Ldw_str_begin+905
	.data.b	63
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 912
	.data.b	84,83,84,82,80,0
	.section	.debug_info		;off: 2300
	.data.w	.Ldw_str_begin+912
	.data.b	64
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 918
	.data.b	84,83,80,0
	.section	.debug_info		;off: 2319
	.data.w	.Ldw_str_begin+918
	.data.b	65
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 922
	.data.b	82,68,80,0
	.section	.debug_info		;off: 2338
	.data.w	.Ldw_str_begin+922
	.data.b	66
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 926
	.data.b	77,83,87,80,0
	.section	.debug_info		;off: 2357
	.data.w	.Ldw_str_begin+926
	.data.b	67
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 931
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 2376
	.data.w	.Ldw_str_begin+931
	.data.b	68
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	21
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 942
	.data.b	82,83,84,65,68,67,0
	.section	.debug_info		;off: 2395
	.data.w	.Ldw_str_begin+942
	.data.b	69
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 949
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 2414
	.data.w	.Ldw_str_begin+949
	.data.b	70
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 961
	.data.b	70,73,70,79,66,89,80,65,83,83,0
	.section	.debug_info		;off: 2433
	.data.w	.Ldw_str_begin+961
	.data.b	71
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 972
	.data.b	114,101,115,101,114,118,101,100,95,49,52,0
	.section	.debug_info		;off: 2452
	.data.w	.Ldw_str_begin+972
	.data.b	72
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 984
	.data.b	68,83,65,68,67,95,68,69,77,73,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 2472
	.data.w	.Ldw_str_begin+984
	.data.b	73
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2274

	.data.b	71
	.data.b	77
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1003
	.data.b	114,101,115,101,114,118,101,100,95,48,0
	.section	.debug_info		;off: 2490
	.data.w	.Ldw_str_begin+1003
	.data.b	78
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1014
	.data.b	86,88,69,78,0
	.section	.debug_info		;off: 2509
	.data.w	.Ldw_str_begin+1014
	.data.b	79
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1019
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 2528
	.data.w	.Ldw_str_begin+1019
	.data.b	80
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1030
	.data.b	67,79,77,86,79,83,78,65,69,78,0
	.section	.debug_info		;off: 2547
	.data.w	.Ldw_str_begin+1030
	.data.b	81
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1041
	.data.b	67,79,77,86,79,83,78,66,69,78,0
	.section	.debug_info		;off: 2566
	.data.w	.Ldw_str_begin+1041
	.data.b	82
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1052
	.data.b	114,101,115,101,114,118,101,100,95,50,50,0
	.section	.debug_info		;off: 2585
	.data.w	.Ldw_str_begin+1052
	.data.b	83
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	10
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1064
	.data.b	68,83,65,68,67,95,67,80,86,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 2605
	.data.w	.Ldw_str_begin+1064
	.data.b	84
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2483

	.data.b	71
	.data.b	88
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1082
	.data.b	83,82,76,86,65,76,0
	.section	.debug_info		;off: 2623
	.data.w	.Ldw_str_begin+1082
	.data.b	89
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1089
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 2642
	.data.w	.Ldw_str_begin+1089
	.data.b	90
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1100
	.data.b	82,68,69,67,76,82,0
	.section	.debug_info		;off: 2661
	.data.w	.Ldw_str_begin+1100
	.data.b	91
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1107
	.data.b	87,82,69,67,76,82,0
	.section	.debug_info		;off: 2680
	.data.w	.Ldw_str_begin+1107
	.data.b	92
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1114
	.data.b	70,73,67,76,82,0
	.section	.debug_info		;off: 2699
	.data.w	.Ldw_str_begin+1114
	.data.b	93
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1120
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 2718
	.data.w	.Ldw_str_begin+1120
	.data.b	94
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	9
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1131
	.data.b	70,73,76,76,86,65,76,0
	.section	.debug_info		;off: 2737
	.data.w	.Ldw_str_begin+1131
	.data.b	95
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1139
	.data.b	82,68,69,70,0
	.section	.debug_info		;off: 2756
	.data.w	.Ldw_str_begin+1139
	.data.b	96
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1144
	.data.b	87,82,69,70,0
	.section	.debug_info		;off: 2775
	.data.w	.Ldw_str_begin+1144
	.data.b	97
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1149
	.data.b	114,101,115,101,114,118,101,100,95,50,49,0
	.section	.debug_info		;off: 2794
	.data.w	.Ldw_str_begin+1149
	.data.b	98
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	11
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1161
	.data.b	68,83,65,68,67,95,82,70,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 2814
	.data.w	.Ldw_str_begin+1161
	.data.b	99
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2616

	.data.b	71
	.data.b	103
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1178
	.data.b	77,67,82,69,83,0
	.section	.debug_info		;off: 2832
	.data.w	.Ldw_str_begin+1178
	.data.b	104
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1184
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 2851
	.data.w	.Ldw_str_begin+1184
	.data.b	105
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1196
	.data.b	68,83,65,68,67,95,77,67,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 2871
	.data.w	.Ldw_str_begin+1196
	.data.b	106
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2825

	.data.b	71
	.data.b	110
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1213
	.data.b	84,83,84,77,80,86,65,76,0
	.section	.debug_info		;off: 2889
	.data.w	.Ldw_str_begin+1213
	.data.b	111
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1222
	.data.b	65,77,83,69,84,0
	.section	.debug_info		;off: 2908
	.data.w	.Ldw_str_begin+1222
	.data.b	112
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1228
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 2927
	.data.w	.Ldw_str_begin+1228
	.data.b	113
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1240
	.data.b	84,83,86,70,0
	.section	.debug_info		;off: 2946
	.data.w	.Ldw_str_begin+1240
	.data.b	114
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1245
	.data.b	114,101,115,101,114,118,101,100,95,49,57,0
	.section	.debug_info		;off: 2965
	.data.w	.Ldw_str_begin+1245
	.data.b	115
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	13
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1257
	.data.b	68,83,65,68,67,95,84,83,84,77,80,95,66,105,116,115,0
	.section	.debug_info		;off: 2985
	.data.w	.Ldw_str_begin+1257
	.data.b	116
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2882

	.data.b	71
	.data.b	120
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1274
	.data.b	84,83,67,86,65,76,0
	.section	.debug_info		;off: 3003
	.data.w	.Ldw_str_begin+1274
	.data.b	121
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1281
	.data.b	84,83,67,67,83,0
	.section	.debug_info		;off: 3022
	.data.w	.Ldw_str_begin+1281
	.data.b	122
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1287
	.data.b	84,83,67,83,67,0
	.section	.debug_info		;off: 3041
	.data.w	.Ldw_str_begin+1287
	.data.b	123
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1293
	.data.b	65,77,83,67,69,78,0
	.section	.debug_info		;off: 3060
	.data.w	.Ldw_str_begin+1293
	.data.b	124
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1300
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 3079
	.data.w	.Ldw_str_begin+1300
	.data.b	125
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1312
	.data.b	68,83,65,68,67,95,84,83,67,78,84,95,66,105,116,115,0
	.section	.debug_info		;off: 3099
	.data.w	.Ldw_str_begin+1312
	.data.b	126
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+2996

	.data.b	71
	.data.b	130,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1329
	.data.b	77,67,70,69,78,0
	.section	.debug_info		;off: 3118
	.data.w	.Ldw_str_begin+1329
	.data.b	131,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1335
	.data.b	77,67,70,83,70,0
	.section	.debug_info		;off: 3138
	.data.w	.Ldw_str_begin+1335
	.data.b	132,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1341
	.data.b	77,67,80,83,0
	.section	.debug_info		;off: 3158
	.data.w	.Ldw_str_begin+1341
	.data.b	133,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1346
	.data.b	77,67,71,83,76,0
	.section	.debug_info		;off: 3178
	.data.w	.Ldw_str_begin+1346
	.data.b	134,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	17
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1352
	.data.b	73,78,84,69,82,66,89,80,65,83,83,0
	.section	.debug_info		;off: 3198
	.data.w	.Ldw_str_begin+1352
	.data.b	135,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1364
	.data.b	77,71,83,82,67,0
	.section	.debug_info		;off: 3218
	.data.w	.Ldw_str_begin+1364
	.data.b	136,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1370
	.data.b	77,65,71,67,83,0
	.section	.debug_info		;off: 3238
	.data.w	.Ldw_str_begin+1370
	.data.b	137,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1376
	.data.b	70,73,82,48,68,69,67,0
	.section	.debug_info		;off: 3258
	.data.w	.Ldw_str_begin+1376
	.data.b	138,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1384
	.data.b	70,73,82,49,68,69,67,0
	.section	.debug_info		;off: 3278
	.data.w	.Ldw_str_begin+1384
	.data.b	139,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1392
	.data.b	114,101,115,101,114,118,101,100,95,50,50,0
	.section	.debug_info		;off: 3298
	.data.w	.Ldw_str_begin+1392
	.data.b	140,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1404
	.data.b	67,79,77,86,79,83,80,66,66,89,80,65,83,83,0
	.section	.debug_info		;off: 3318
	.data.w	.Ldw_str_begin+1404
	.data.b	141,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1419
	.data.b	70,73,82,48,70,69,78,0
	.section	.debug_info		;off: 3338
	.data.w	.Ldw_str_begin+1419
	.data.b	142,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1427
	.data.b	70,73,82,49,70,69,78,0
	.section	.debug_info		;off: 3358
	.data.w	.Ldw_str_begin+1427
	.data.b	143,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1435
	.data.b	70,73,82,48,79,83,70,0
	.section	.debug_info		;off: 3378
	.data.w	.Ldw_str_begin+1435
	.data.b	144,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1443
	.data.b	70,73,82,49,79,83,70,0
	.section	.debug_info		;off: 3398
	.data.w	.Ldw_str_begin+1443
	.data.b	145,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	3
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1451
	.data.b	79,67,69,78,67,70,71,0
	.section	.debug_info		;off: 3418
	.data.w	.Ldw_str_begin+1451
	.data.b	146,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1459
	.data.b	68,83,65,68,67,95,77,70,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 3439
	.data.w	.Ldw_str_begin+1459
	.data.b	147,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3110

	.data.b	71
	.data.b	151,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1476
	.data.b	65,67,70,69,78,0
	.section	.debug_info		;off: 3459
	.data.w	.Ldw_str_begin+1476
	.data.b	152,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1482
	.data.b	65,67,70,68,70,0
	.section	.debug_info		;off: 3479
	.data.w	.Ldw_str_begin+1482
	.data.b	153,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1488
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 3499
	.data.w	.Ldw_str_begin+1488
	.data.b	154,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1499
	.data.b	65,67,80,83,0
	.section	.debug_info		;off: 3519
	.data.w	.Ldw_str_begin+1499
	.data.b	155,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1504
	.data.b	65,67,71,83,76,0
	.section	.debug_info		;off: 3539
	.data.w	.Ldw_str_begin+1504
	.data.b	156,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	17
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1510
	.data.b	114,101,115,101,114,118,101,100,95,49,53,0
	.section	.debug_info		;off: 3559
	.data.w	.Ldw_str_begin+1510
	.data.b	157,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1522
	.data.b	65,71,83,82,67,0
	.section	.debug_info		;off: 3579
	.data.w	.Ldw_str_begin+1522
	.data.b	158,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1528
	.data.b	65,65,71,67,83,0
	.section	.debug_info		;off: 3599
	.data.w	.Ldw_str_begin+1528
	.data.b	159,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1534
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 3619
	.data.w	.Ldw_str_begin+1534
	.data.b	160,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1546
	.data.b	68,83,65,68,67,95,65,70,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 3640
	.data.w	.Ldw_str_begin+1546
	.data.b	161,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3451

	.data.b	71
	.data.b	165,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1563
	.data.b	71,65,73,78,79,70,70,69,78,0
	.section	.debug_info		;off: 3660
	.data.w	.Ldw_str_begin+1563
	.data.b	166,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1573
	.data.b	71,65,73,78,79,70,70,0
	.section	.debug_info		;off: 3680
	.data.w	.Ldw_str_begin+1573
	.data.b	167,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1581
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 3700
	.data.w	.Ldw_str_begin+1581
	.data.b	168,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1592
	.data.b	79,70,70,83,69,84,86,65,76,0
	.section	.debug_info		;off: 3720
	.data.w	.Ldw_str_begin+1592
	.data.b	169,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1602
	.data.b	114,101,115,101,114,118,101,100,95,49,57,0
	.section	.debug_info		;off: 3740
	.data.w	.Ldw_str_begin+1602
	.data.b	170,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	13
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1614
	.data.b	68,83,65,68,67,95,71,65,73,78,67,84,82,95,66,105,116,115,0
	.section	.debug_info		;off: 3761
	.data.w	.Ldw_str_begin+1614
	.data.b	171,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3652

	.data.b	71
	.data.b	175,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1633
	.data.b	84,67,85,76,0
	.section	.debug_info		;off: 3781
	.data.w	.Ldw_str_begin+1633
	.data.b	176,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1638
	.data.b	84,67,76,76,0
	.section	.debug_info		;off: 3801
	.data.w	.Ldw_str_begin+1638
	.data.b	177,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1643
	.data.b	68,83,65,68,67,95,84,72,82,69,83,76,77,95,66,105,116,115,0
	.section	.debug_info		;off: 3822
	.data.w	.Ldw_str_begin+1643
	.data.b	178,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3773

	.data.b	71
	.data.b	182,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1662
	.data.b	65,67,82,69,83,0
	.section	.debug_info		;off: 3842
	.data.w	.Ldw_str_begin+1662
	.data.b	183,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1668
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 3862
	.data.w	.Ldw_str_begin+1668
	.data.b	184,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1680
	.data.b	68,83,65,68,67,95,65,67,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 3883
	.data.w	.Ldw_str_begin+1680
	.data.b	185,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3834

	.data.b	71
	.data.b	189,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1697
	.data.b	84,82,73,71,73,69,0
	.section	.debug_info		;off: 3903
	.data.w	.Ldw_str_begin+1697
	.data.b	190,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1704
	.data.b	70,73,70,79,70,73,76,76,73,69,0
	.section	.debug_info		;off: 3923
	.data.w	.Ldw_str_begin+1704
	.data.b	191,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1715
	.data.b	83,65,77,73,69,0
	.section	.debug_info		;off: 3943
	.data.w	.Ldw_str_begin+1715
	.data.b	192,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1721
	.data.b	83,66,77,73,69,0
	.section	.debug_info		;off: 3963
	.data.w	.Ldw_str_begin+1721
	.data.b	193,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1727
	.data.b	84,83,84,77,80,73,69,0
	.section	.debug_info		;off: 3983
	.data.w	.Ldw_str_begin+1727
	.data.b	194,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1735
	.data.b	83,65,65,73,69,0
	.section	.debug_info		;off: 4003
	.data.w	.Ldw_str_begin+1735
	.data.b	195,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1741
	.data.b	83,66,65,73,69,0
	.section	.debug_info		;off: 4023
	.data.w	.Ldw_str_begin+1741
	.data.b	196,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1747
	.data.b	82,69,65,73,69,0
	.section	.debug_info		;off: 4043
	.data.w	.Ldw_str_begin+1747
	.data.b	197,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1753
	.data.b	68,77,65,70,73,70,79,73,69,0
	.section	.debug_info		;off: 4063
	.data.w	.Ldw_str_begin+1753
	.data.b	198,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1763
	.data.b	68,77,65,84,82,73,71,73,69,0
	.section	.debug_info		;off: 4083
	.data.w	.Ldw_str_begin+1763
	.data.b	199,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1773
	.data.b	68,77,65,84,83,84,77,80,73,69,0
	.section	.debug_info		;off: 4103
	.data.w	.Ldw_str_begin+1773
	.data.b	200,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1784
	.data.b	68,77,65,82,69,65,73,69,0
	.section	.debug_info		;off: 4123
	.data.w	.Ldw_str_begin+1784
	.data.b	201,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1793
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 4143
	.data.w	.Ldw_str_begin+1793
	.data.b	202,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1805
	.data.b	68,83,65,68,67,95,73,78,84,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 4164
	.data.w	.Ldw_str_begin+1805
	.data.b	203,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3895

	.data.b	71
	.data.b	207,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1822
	.data.b	84,82,73,71,67,76,82,0
	.section	.debug_info		;off: 4184
	.data.w	.Ldw_str_begin+1822
	.data.b	208,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1830
	.data.b	70,73,70,79,70,73,76,76,67,76,82,0
	.section	.debug_info		;off: 4204
	.data.w	.Ldw_str_begin+1830
	.data.b	209,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1842
	.data.b	83,65,77,67,76,82,0
	.section	.debug_info		;off: 4224
	.data.w	.Ldw_str_begin+1842
	.data.b	210,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1849
	.data.b	83,66,77,67,76,82,0
	.section	.debug_info		;off: 4244
	.data.w	.Ldw_str_begin+1849
	.data.b	211,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1856
	.data.b	84,83,84,77,80,67,76,82,0
	.section	.debug_info		;off: 4264
	.data.w	.Ldw_str_begin+1856
	.data.b	212,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1865
	.data.b	83,65,65,67,76,82,0
	.section	.debug_info		;off: 4284
	.data.w	.Ldw_str_begin+1865
	.data.b	213,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1872
	.data.b	83,66,65,67,76,82,0
	.section	.debug_info		;off: 4304
	.data.w	.Ldw_str_begin+1872
	.data.b	214,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1879
	.data.b	82,69,65,67,76,82,0
	.section	.debug_info		;off: 4324
	.data.w	.Ldw_str_begin+1879
	.data.b	215,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1886
	.data.b	68,77,65,82,67,76,82,0
	.section	.debug_info		;off: 4344
	.data.w	.Ldw_str_begin+1886
	.data.b	216,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1894
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 4364
	.data.w	.Ldw_str_begin+1894
	.data.b	217,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	23
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1905
	.data.b	68,83,65,68,67,95,73,78,84,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 4385
	.data.w	.Ldw_str_begin+1905
	.data.b	218,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4176

	.data.b	71
	.data.b	222,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1923
	.data.b	84,82,73,71,83,84,0
	.section	.debug_info		;off: 4405
	.data.w	.Ldw_str_begin+1923
	.data.b	223,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1930
	.data.b	70,73,70,79,70,73,76,76,83,84,0
	.section	.debug_info		;off: 4425
	.data.w	.Ldw_str_begin+1930
	.data.b	224,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1941
	.data.b	83,65,77,83,84,0
	.section	.debug_info		;off: 4445
	.data.w	.Ldw_str_begin+1941
	.data.b	225,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1947
	.data.b	83,66,77,83,84,0
	.section	.debug_info		;off: 4465
	.data.w	.Ldw_str_begin+1947
	.data.b	226,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1953
	.data.b	84,83,84,77,80,83,84,0
	.section	.debug_info		;off: 4485
	.data.w	.Ldw_str_begin+1953
	.data.b	227,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1961
	.data.b	83,65,65,83,84,0
	.section	.debug_info		;off: 4505
	.data.w	.Ldw_str_begin+1961
	.data.b	228,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1967
	.data.b	83,66,65,83,84,0
	.section	.debug_info		;off: 4525
	.data.w	.Ldw_str_begin+1967
	.data.b	229,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1973
	.data.b	82,69,65,83,84,0
	.section	.debug_info		;off: 4545
	.data.w	.Ldw_str_begin+1973
	.data.b	230,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1979
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 4565
	.data.w	.Ldw_str_begin+1979
	.data.b	231,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	24
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1990
	.data.b	68,83,65,68,67,95,73,78,84,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 4586
	.data.w	.Ldw_str_begin+1990
	.data.b	232,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4397

	.data.b	71
	.data.b	236,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2008
	.data.b	84,69,83,84,83,69,76,0
	.section	.debug_info		;off: 4606
	.data.w	.Ldw_str_begin+2008
	.data.b	237,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2016
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 4626
	.data.w	.Ldw_str_begin+2016
	.data.b	238,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	29
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2027
	.data.b	68,83,65,68,67,95,84,69,83,84,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 4647
	.data.w	.Ldw_str_begin+2027
	.data.b	239,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4598

	.data.b	71
	.data.b	243,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2046
	.data.b	71,67,79,70,70,83,69,84,0
	.section	.debug_info		;off: 4667
	.data.w	.Ldw_str_begin+2046
	.data.b	244,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2055
	.data.b	68,67,79,70,70,83,69,84,0
	.section	.debug_info		;off: 4687
	.data.w	.Ldw_str_begin+2055
	.data.b	245,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2064
	.data.b	68,83,65,68,67,95,67,79,77,80,95,66,105,116,115,0
	.section	.debug_info		;off: 4708
	.data.w	.Ldw_str_begin+2064
	.data.b	246,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4659

	.data.b	71
	.data.b	250,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2080
	.data.b	82,69,71,83,77,69,78,0
	.section	.debug_info		;off: 4728
	.data.w	.Ldw_str_begin+2080
	.data.b	251,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2088
	.data.b	70,73,83,77,69,78,0
	.section	.debug_info		;off: 4748
	.data.w	.Ldw_str_begin+2088
	.data.b	252,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2095
	.data.b	68,65,83,77,69,78,0
	.section	.debug_info		;off: 4768
	.data.w	.Ldw_str_begin+2095
	.data.b	253,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2102
	.data.b	68,77,65,83,77,69,78,0
	.section	.debug_info		;off: 4788
	.data.w	.Ldw_str_begin+2102
	.data.b	254,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2110
	.data.b	84,82,73,71,83,77,69,78,0
	.section	.debug_info		;off: 4808
	.data.w	.Ldw_str_begin+2110
	.data.b	255,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2119
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 4828
	.data.w	.Ldw_str_begin+2119
	.data.b	128,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	22
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2131
	.data.b	68,83,65,68,67,95,83,77,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 4849
	.data.w	.Ldw_str_begin+2131
	.data.b	129,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4720

	.data.b	71
	.data.b	133,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2147
	.data.b	82,69,71,65,67,76,82,0
	.section	.debug_info		;off: 4869
	.data.w	.Ldw_str_begin+2147
	.data.b	134,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2155
	.data.b	70,73,65,67,76,82,0
	.section	.debug_info		;off: 4889
	.data.w	.Ldw_str_begin+2155
	.data.b	135,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2162
	.data.b	68,65,65,67,76,82,0
	.section	.debug_info		;off: 4909
	.data.w	.Ldw_str_begin+2162
	.data.b	136,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2169
	.data.b	68,77,65,65,67,76,82,0
	.section	.debug_info		;off: 4929
	.data.w	.Ldw_str_begin+2169
	.data.b	137,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2177
	.data.b	84,82,73,71,65,67,76,82,0
	.section	.debug_info		;off: 4949
	.data.w	.Ldw_str_begin+2177
	.data.b	138,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2186
	.data.b	83,69,65,67,76,82,0
	.section	.debug_info		;off: 4969
	.data.w	.Ldw_str_begin+2186
	.data.b	139,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2193
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 4989
	.data.w	.Ldw_str_begin+2193
	.data.b	140,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2205
	.data.b	68,83,65,68,67,95,65,76,65,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 5010
	.data.w	.Ldw_str_begin+2205
	.data.b	141,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+4861

	.data.b	71
	.data.b	145,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2223
	.data.b	83,77,82,69,65,83,84,0
	.section	.debug_info		;off: 5030
	.data.w	.Ldw_str_begin+2223
	.data.b	146,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2231
	.data.b	65,67,76,82,69,82,83,84,0
	.section	.debug_info		;off: 5050
	.data.w	.Ldw_str_begin+2231
	.data.b	147,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2240
	.data.b	70,73,82,69,71,65,83,84,0
	.section	.debug_info		;off: 5070
	.data.w	.Ldw_str_begin+2240
	.data.b	148,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2249
	.data.b	77,82,69,83,65,83,84,0
	.section	.debug_info		;off: 5090
	.data.w	.Ldw_str_begin+2249
	.data.b	149,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2257
	.data.b	70,73,65,83,84,0
	.section	.debug_info		;off: 5110
	.data.w	.Ldw_str_begin+2257
	.data.b	150,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2263
	.data.b	68,65,65,83,84,0
	.section	.debug_info		;off: 5130
	.data.w	.Ldw_str_begin+2263
	.data.b	151,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2269
	.data.b	68,77,65,65,83,84,0
	.section	.debug_info		;off: 5150
	.data.w	.Ldw_str_begin+2269
	.data.b	152,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2276
	.data.b	84,82,73,71,65,83,84,0
	.section	.debug_info		;off: 5170
	.data.w	.Ldw_str_begin+2276
	.data.b	153,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2284
	.data.b	83,69,65,83,84,0
	.section	.debug_info		;off: 5190
	.data.w	.Ldw_str_begin+2284
	.data.b	154,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2290
	.data.b	68,77,65,76,79,83,84,0
	.section	.debug_info		;off: 5210
	.data.w	.Ldw_str_begin+2290
	.data.b	155,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2298
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 5230
	.data.w	.Ldw_str_begin+2298
	.data.b	156,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	22
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2310
	.data.b	68,83,65,68,67,95,65,76,65,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 5251
	.data.w	.Ldw_str_begin+2310
	.data.b	157,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5022

	.data.b	71
	.data.b	161,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2328
	.data.b	68,77,65,70,65,73,78,0
	.section	.debug_info		;off: 5271
	.data.w	.Ldw_str_begin+2328
	.data.b	162,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2336
	.data.b	84,82,73,71,70,65,73,78,0
	.section	.debug_info		;off: 5291
	.data.w	.Ldw_str_begin+2336
	.data.b	163,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2345
	.data.b	114,101,115,101,114,118,101,100,95,52,0
	.section	.debug_info		;off: 5311
	.data.w	.Ldw_str_begin+2345
	.data.b	164,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	28
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2356
	.data.b	68,83,65,68,67,95,70,65,73,78,95,66,105,116,115,0
	.section	.debug_info		;off: 5332
	.data.w	.Ldw_str_begin+2356
	.data.b	165,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5263

	.data.b	71
	.data.b	169,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2372
	.data.b	68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 5352
	.data.w	.Ldw_str_begin+2372
	.data.b	170,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2381
	.data.b	68,83,65,68,67,95,68,77,65,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 5373
	.data.w	.Ldw_str_begin+2381
	.data.b	171,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5344

	.data.b	71
	.data.b	175,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2401
	.data.b	84,82,73,71,84,72,82,69,83,0
	.section	.debug_info		;off: 5393
	.data.w	.Ldw_str_begin+2401
	.data.b	176,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2411
	.data.b	68,83,65,68,67,95,84,82,73,71,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 5414
	.data.w	.Ldw_str_begin+2411
	.data.b	177,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5385

	.data.b	71
	.data.b	181,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2432
	.data.b	71,67,79,66,69,78,0
	.section	.debug_info		;off: 5434
	.data.w	.Ldw_str_begin+2432
	.data.b	182,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2439
	.data.b	68,67,79,66,69,78,0
	.section	.debug_info		;off: 5454
	.data.w	.Ldw_str_begin+2439
	.data.b	183,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2446
	.data.b	86,83,69,76,76,86,0
	.section	.debug_info		;off: 5474
	.data.w	.Ldw_str_begin+2446
	.data.b	184,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2453
	.data.b	67,65,76,83,69,76,76,86,0
	.section	.debug_info		;off: 5494
	.data.w	.Ldw_str_begin+2453
	.data.b	185,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2462
	.data.b	67,65,76,69,78,0
	.section	.debug_info		;off: 5514
	.data.w	.Ldw_str_begin+2462
	.data.b	186,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2468
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 5534
	.data.w	.Ldw_str_begin+2468
	.data.b	187,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	25
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2479
	.data.b	68,83,65,68,67,95,67,79,77,80,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 5555
	.data.w	.Ldw_str_begin+2479
	.data.b	188,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5426

	.data.b	71
	.data.b	192,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2498
	.data.b	84,69,83,84,77,79,68,69,0
	.section	.debug_info		;off: 5575
	.data.w	.Ldw_str_begin+2498
	.data.b	193,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2507
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 5595
	.data.w	.Ldw_str_begin+2507
	.data.b	194,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2518
	.data.b	68,83,65,68,67,95,84,69,83,84,77,79,68,69,95,66,105,116,115,0
	.section	.debug_info		;off: 5616
	.data.w	.Ldw_str_begin+2518
	.data.b	195,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5567

	.data.b	71
	.data.b	199,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2538
	.data.b	68,73,84,72,69,82,69,78,0
	.section	.debug_info		;off: 5636
	.data.w	.Ldw_str_begin+2538
	.data.b	200,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2547
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 5656
	.data.w	.Ldw_str_begin+2547
	.data.b	201,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2558
	.data.b	68,83,65,68,67,95,68,73,84,72,69,82,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 5677
	.data.w	.Ldw_str_begin+2558
	.data.b	202,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5628

	.data.b	71
	.data.b	206,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2578
	.data.b	69,78,0
	.section	.debug_info		;off: 5697
	.data.w	.Ldw_str_begin+2578
	.data.b	207,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2581
	.data.b	77,79,68,69,0
	.section	.debug_info		;off: 5717
	.data.w	.Ldw_str_begin+2581
	.data.b	208,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2586
	.data.b	80,67,77,69,78,0
	.section	.debug_info		;off: 5737
	.data.w	.Ldw_str_begin+2586
	.data.b	209,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2592
	.data.b	67,87,80,72,73,67,82,76,0
	.section	.debug_info		;off: 5757
	.data.w	.Ldw_str_begin+2592
	.data.b	210,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2601
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 5777
	.data.w	.Ldw_str_begin+2601
	.data.b	211,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2612
	.data.b	80,69,82,67,89,67,76,69,0
	.section	.debug_info		;off: 5797
	.data.w	.Ldw_str_begin+2612
	.data.b	212,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	19
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2621
	.data.b	80,69,82,73,78,68,69,88,0
	.section	.debug_info		;off: 5817
	.data.w	.Ldw_str_begin+2621
	.data.b	213,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2630
	.data.b	83,73,71,78,66,73,84,0
	.section	.debug_info		;off: 5837
	.data.w	.Ldw_str_begin+2630
	.data.b	214,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2638
	.data.b	83,89,78,83,73,71,78,66,73,84,0
	.section	.debug_info		;off: 5857
	.data.w	.Ldw_str_begin+2638
	.data.b	215,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2649
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 5877
	.data.w	.Ldw_str_begin+2649
	.data.b	216,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2661
	.data.b	68,83,65,68,67,95,67,87,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 5898
	.data.w	.Ldw_str_begin+2661
	.data.b	217,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5689

	.data.b	71
	.data.b	221,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2678
	.data.b	83,89,78,67,69,78,68,0
	.section	.debug_info		;off: 5918
	.data.w	.Ldw_str_begin+2678
	.data.b	222,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2686
	.data.b	83,89,78,67,83,84,65,82,84,0
	.section	.debug_info		;off: 5938
	.data.w	.Ldw_str_begin+2686
	.data.b	223,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2696
	.data.b	68,69,76,65,89,0
	.section	.debug_info		;off: 5958
	.data.w	.Ldw_str_begin+2696
	.data.b	224,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	8
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2702
	.data.b	67,78,84,0
	.section	.debug_info		;off: 5978
	.data.w	.Ldw_str_begin+2702
	.data.b	225,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2706
	.data.b	68,83,65,68,67,95,67,87,83,89,78,67,95,66,105,116,115,0
	.section	.debug_info		;off: 5999
	.data.w	.Ldw_str_begin+2706
	.data.b	226,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+5910

	.data.b	71
	.data.b	230,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2724
	.data.b	83,70,76,0
	.section	.debug_info		;off: 6019
	.data.w	.Ldw_str_begin+2724
	.data.b	231,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2728
	.data.b	77,79,68,69,0
	.section	.debug_info		;off: 6039
	.data.w	.Ldw_str_begin+2728
	.data.b	232,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2733
	.data.b	76,69,78,0
	.section	.debug_info		;off: 6059
	.data.w	.Ldw_str_begin+2733
	.data.b	233,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2737
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 6079
	.data.w	.Ldw_str_begin+2737
	.data.b	234,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	22
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2749
	.data.b	68,83,65,68,67,95,73,78,84,69,82,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 6100
	.data.w	.Ldw_str_begin+2749
	.data.b	235,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+6011

	.data.b	71
	.data.b	239,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2769
	.data.b	66,85,83,69,82,82,77,83,75,0
	.section	.debug_info		;off: 6120
	.data.w	.Ldw_str_begin+2769
	.data.b	240,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2779
	.data.b	68,77,65,76,79,83,83,77,65,83,75,0
	.section	.debug_info		;off: 6140
	.data.w	.Ldw_str_begin+2779
	.data.b	241,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2791
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 6160
	.data.w	.Ldw_str_begin+2791
	.data.b	242,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2802
	.data.b	68,83,65,68,67,95,66,85,83,69,82,82,77,83,75,95,66,105,116,115,0
	.section	.debug_info		;off: 6181
	.data.w	.Ldw_str_begin+2802
	.data.b	243,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+6112

	.data.b	71
	.data.b	247,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2823
	.data.b	83,85,83,67,84,82,76,0
	.section	.debug_info		;off: 6201
	.data.w	.Ldw_str_begin+2823
	.data.b	248,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2831
	.data.b	83,85,83,87,80,0
	.section	.debug_info		;off: 6221
	.data.w	.Ldw_str_begin+2831
	.data.b	249,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2837
	.data.b	83,85,83,70,76,65,71,0
	.section	.debug_info		;off: 6241
	.data.w	.Ldw_str_begin+2837
	.data.b	250,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2845
	.data.b	68,66,71,80,0
	.section	.debug_info		;off: 6261
	.data.w	.Ldw_str_begin+2845
	.data.b	251,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2850
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 6281
	.data.w	.Ldw_str_begin+2850
	.data.b	252,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	25
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2861
	.data.b	68,83,65,68,67,95,68,69,66,85,71,95,66,105,116,115,0
	.section	.debug_info		;off: 6302
	.data.w	.Ldw_str_begin+2861
	.data.b	253,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+6193

	.data.b	71
	.data.b	129,3
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2878
	.data.b	67,72,48,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6322
	.data.w	.Ldw_str_begin+2878
	.data.b	130,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2888
	.data.b	67,72,49,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6342
	.data.w	.Ldw_str_begin+2888
	.data.b	131,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2898
	.data.b	67,72,50,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6362
	.data.w	.Ldw_str_begin+2898
	.data.b	132,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2908
	.data.b	67,72,51,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6382
	.data.w	.Ldw_str_begin+2908
	.data.b	133,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2918
	.data.b	67,72,52,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6402
	.data.w	.Ldw_str_begin+2918
	.data.b	134,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2928
	.data.b	67,72,53,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6422
	.data.w	.Ldw_str_begin+2928
	.data.b	135,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2938
	.data.b	67,72,54,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6442
	.data.w	.Ldw_str_begin+2938
	.data.b	136,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2948
	.data.b	67,72,55,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6462
	.data.w	.Ldw_str_begin+2948
	.data.b	137,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2958
	.data.b	67,72,56,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6482
	.data.w	.Ldw_str_begin+2958
	.data.b	138,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2968
	.data.b	67,72,57,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6502
	.data.w	.Ldw_str_begin+2968
	.data.b	139,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2978
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 6522
	.data.w	.Ldw_str_begin+2978
	.data.b	140,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2990
	.data.b	77,48,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6542
	.data.w	.Ldw_str_begin+2990
	.data.b	141,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2999
	.data.b	77,49,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6562
	.data.w	.Ldw_str_begin+2999
	.data.b	142,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3008
	.data.b	77,50,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6582
	.data.w	.Ldw_str_begin+3008
	.data.b	143,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3017
	.data.b	77,51,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6602
	.data.w	.Ldw_str_begin+3017
	.data.b	144,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3026
	.data.b	77,52,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6622
	.data.w	.Ldw_str_begin+3026
	.data.b	145,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3035
	.data.b	77,53,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6642
	.data.w	.Ldw_str_begin+3035
	.data.b	146,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3044
	.data.b	77,54,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6662
	.data.w	.Ldw_str_begin+3044
	.data.b	147,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3053
	.data.b	77,55,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6682
	.data.w	.Ldw_str_begin+3053
	.data.b	148,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3062
	.data.b	77,56,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6702
	.data.w	.Ldw_str_begin+3062
	.data.b	149,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3071
	.data.b	77,57,82,85,78,67,84,76,0
	.section	.debug_info		;off: 6722
	.data.w	.Ldw_str_begin+3071
	.data.b	150,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3080
	.data.b	114,101,115,101,114,118,101,100,95,50,54,0
	.section	.debug_info		;off: 6742
	.data.w	.Ldw_str_begin+3080
	.data.b	151,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3092
	.data.b	68,83,65,68,67,95,71,76,79,66,67,82,67,95,66,105,116,115,0
	.section	.debug_info		;off: 6763
	.data.w	.Ldw_str_begin+3092
	.data.b	152,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+6314

	.data.b	71
	.data.b	156,3
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3111
	.data.b	82,69,83,69,86,70,48,0
	.section	.debug_info		;off: 6783
	.data.w	.Ldw_str_begin+3111
	.data.b	157,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3119
	.data.b	82,69,83,69,86,70,49,0
	.section	.debug_info		;off: 6803
	.data.w	.Ldw_str_begin+3119
	.data.b	158,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3127
	.data.b	82,69,83,69,86,70,50,0
	.section	.debug_info		;off: 6823
	.data.w	.Ldw_str_begin+3127
	.data.b	159,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3135
	.data.b	82,69,83,69,86,70,51,0
	.section	.debug_info		;off: 6843
	.data.w	.Ldw_str_begin+3135
	.data.b	160,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3143
	.data.b	82,69,83,69,86,70,52,0
	.section	.debug_info		;off: 6863
	.data.w	.Ldw_str_begin+3143
	.data.b	161,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3151
	.data.b	82,69,83,69,86,70,53,0
	.section	.debug_info		;off: 6883
	.data.w	.Ldw_str_begin+3151
	.data.b	162,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3159
	.data.b	82,69,83,69,86,70,54,0
	.section	.debug_info		;off: 6903
	.data.w	.Ldw_str_begin+3159
	.data.b	163,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3167
	.data.b	82,69,83,69,86,70,55,0
	.section	.debug_info		;off: 6923
	.data.w	.Ldw_str_begin+3167
	.data.b	164,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3175
	.data.b	82,69,83,69,86,70,56,0
	.section	.debug_info		;off: 6943
	.data.w	.Ldw_str_begin+3175
	.data.b	165,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3183
	.data.b	82,69,83,69,86,70,57,0
	.section	.debug_info		;off: 6963
	.data.w	.Ldw_str_begin+3183
	.data.b	166,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3191
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 6983
	.data.w	.Ldw_str_begin+3191
	.data.b	167,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3203
	.data.b	65,76,69,86,70,48,0
	.section	.debug_info		;off: 7003
	.data.w	.Ldw_str_begin+3203
	.data.b	168,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3210
	.data.b	65,76,69,86,70,49,0
	.section	.debug_info		;off: 7023
	.data.w	.Ldw_str_begin+3210
	.data.b	169,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3217
	.data.b	65,76,69,86,70,50,0
	.section	.debug_info		;off: 7043
	.data.w	.Ldw_str_begin+3217
	.data.b	170,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3224
	.data.b	65,76,69,86,70,51,0
	.section	.debug_info		;off: 7063
	.data.w	.Ldw_str_begin+3224
	.data.b	171,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3231
	.data.b	65,76,69,86,70,52,0
	.section	.debug_info		;off: 7083
	.data.w	.Ldw_str_begin+3231
	.data.b	172,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3238
	.data.b	65,76,69,86,70,53,0
	.section	.debug_info		;off: 7103
	.data.w	.Ldw_str_begin+3238
	.data.b	173,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3245
	.data.b	65,76,69,86,70,54,0
	.section	.debug_info		;off: 7123
	.data.w	.Ldw_str_begin+3245
	.data.b	174,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3252
	.data.b	65,76,69,86,70,55,0
	.section	.debug_info		;off: 7143
	.data.w	.Ldw_str_begin+3252
	.data.b	175,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3259
	.data.b	65,76,69,86,70,56,0
	.section	.debug_info		;off: 7163
	.data.w	.Ldw_str_begin+3259
	.data.b	176,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3266
	.data.b	65,76,69,86,70,57,0
	.section	.debug_info		;off: 7183
	.data.w	.Ldw_str_begin+3266
	.data.b	177,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3273
	.data.b	114,101,115,101,114,118,101,100,95,50,54,0
	.section	.debug_info		;off: 7203
	.data.w	.Ldw_str_begin+3273
	.data.b	178,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3285
	.data.b	68,83,65,68,67,95,71,76,79,66,69,86,83,70,95,66,105,116,115,0
	.section	.debug_info		;off: 7224
	.data.w	.Ldw_str_begin+3285
	.data.b	179,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+6775

	.data.b	71
	.data.b	183,3
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3305
	.data.b	82,69,83,69,67,76,82,48,0
	.section	.debug_info		;off: 7244
	.data.w	.Ldw_str_begin+3305
	.data.b	184,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3314
	.data.b	82,69,83,69,67,76,82,49,0
	.section	.debug_info		;off: 7264
	.data.w	.Ldw_str_begin+3314
	.data.b	185,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3323
	.data.b	82,69,83,69,67,76,82,50,0
	.section	.debug_info		;off: 7284
	.data.w	.Ldw_str_begin+3323
	.data.b	186,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3332
	.data.b	82,69,83,69,67,76,82,51,0
	.section	.debug_info		;off: 7304
	.data.w	.Ldw_str_begin+3332
	.data.b	187,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3341
	.data.b	82,69,83,69,67,76,82,52,0
	.section	.debug_info		;off: 7324
	.data.w	.Ldw_str_begin+3341
	.data.b	188,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3350
	.data.b	82,69,83,69,67,76,82,53,0
	.section	.debug_info		;off: 7344
	.data.w	.Ldw_str_begin+3350
	.data.b	189,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3359
	.data.b	82,69,83,69,67,76,82,54,0
	.section	.debug_info		;off: 7364
	.data.w	.Ldw_str_begin+3359
	.data.b	190,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3368
	.data.b	82,69,83,69,67,76,82,55,0
	.section	.debug_info		;off: 7384
	.data.w	.Ldw_str_begin+3368
	.data.b	191,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3377
	.data.b	82,69,83,69,67,76,82,56,0
	.section	.debug_info		;off: 7404
	.data.w	.Ldw_str_begin+3377
	.data.b	192,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3386
	.data.b	82,69,83,69,67,76,82,57,0
	.section	.debug_info		;off: 7424
	.data.w	.Ldw_str_begin+3386
	.data.b	193,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3395
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 7444
	.data.w	.Ldw_str_begin+3395
	.data.b	194,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3407
	.data.b	65,76,69,67,76,82,48,0
	.section	.debug_info		;off: 7464
	.data.w	.Ldw_str_begin+3407
	.data.b	195,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3415
	.data.b	65,76,69,67,76,82,49,0
	.section	.debug_info		;off: 7484
	.data.w	.Ldw_str_begin+3415
	.data.b	196,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3423
	.data.b	65,76,69,67,76,82,50,0
	.section	.debug_info		;off: 7504
	.data.w	.Ldw_str_begin+3423
	.data.b	197,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3431
	.data.b	65,76,69,67,76,82,51,0
	.section	.debug_info		;off: 7524
	.data.w	.Ldw_str_begin+3431
	.data.b	198,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3439
	.data.b	65,76,69,67,76,82,52,0
	.section	.debug_info		;off: 7544
	.data.w	.Ldw_str_begin+3439
	.data.b	199,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3447
	.data.b	65,76,69,67,76,82,53,0
	.section	.debug_info		;off: 7564
	.data.w	.Ldw_str_begin+3447
	.data.b	200,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3455
	.data.b	65,76,69,67,76,82,54,0
	.section	.debug_info		;off: 7584
	.data.w	.Ldw_str_begin+3455
	.data.b	201,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3463
	.data.b	65,76,69,67,76,82,55,0
	.section	.debug_info		;off: 7604
	.data.w	.Ldw_str_begin+3463
	.data.b	202,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3471
	.data.b	65,76,69,67,76,82,56,0
	.section	.debug_info		;off: 7624
	.data.w	.Ldw_str_begin+3471
	.data.b	203,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3479
	.data.b	65,76,69,67,76,82,57,0
	.section	.debug_info		;off: 7644
	.data.w	.Ldw_str_begin+3479
	.data.b	204,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3487
	.data.b	114,101,115,101,114,118,101,100,95,50,54,0
	.section	.debug_info		;off: 7664
	.data.w	.Ldw_str_begin+3487
	.data.b	205,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3499
	.data.b	68,83,65,68,67,95,71,76,79,66,69,86,83,70,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 7685
	.data.w	.Ldw_str_begin+3499
	.data.b	206,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+7236

	.data.b	71
	.data.b	210,3
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3522
	.data.b	77,67,72,48,69,78,0
	.section	.debug_info		;off: 7705
	.data.w	.Ldw_str_begin+3522
	.data.b	211,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3529
	.data.b	77,67,72,49,69,78,0
	.section	.debug_info		;off: 7725
	.data.w	.Ldw_str_begin+3529
	.data.b	212,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3536
	.data.b	77,67,72,50,69,78,0
	.section	.debug_info		;off: 7745
	.data.w	.Ldw_str_begin+3536
	.data.b	213,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3543
	.data.b	77,67,72,51,69,78,0
	.section	.debug_info		;off: 7765
	.data.w	.Ldw_str_begin+3543
	.data.b	214,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3550
	.data.b	77,67,72,52,69,78,0
	.section	.debug_info		;off: 7785
	.data.w	.Ldw_str_begin+3550
	.data.b	215,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3557
	.data.b	77,67,72,53,69,78,0
	.section	.debug_info		;off: 7805
	.data.w	.Ldw_str_begin+3557
	.data.b	216,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3564
	.data.b	77,67,72,54,69,78,0
	.section	.debug_info		;off: 7825
	.data.w	.Ldw_str_begin+3564
	.data.b	217,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3571
	.data.b	77,67,72,55,69,78,0
	.section	.debug_info		;off: 7845
	.data.w	.Ldw_str_begin+3571
	.data.b	218,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3578
	.data.b	65,67,72,48,69,78,0
	.section	.debug_info		;off: 7865
	.data.w	.Ldw_str_begin+3578
	.data.b	219,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3585
	.data.b	65,67,72,49,69,78,0
	.section	.debug_info		;off: 7885
	.data.w	.Ldw_str_begin+3585
	.data.b	220,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3592
	.data.b	65,67,72,50,69,78,0
	.section	.debug_info		;off: 7905
	.data.w	.Ldw_str_begin+3592
	.data.b	221,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3599
	.data.b	65,67,72,51,69,78,0
	.section	.debug_info		;off: 7925
	.data.w	.Ldw_str_begin+3599
	.data.b	222,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3606
	.data.b	65,67,72,52,69,78,0
	.section	.debug_info		;off: 7945
	.data.w	.Ldw_str_begin+3606
	.data.b	223,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3613
	.data.b	65,67,72,53,69,78,0
	.section	.debug_info		;off: 7965
	.data.w	.Ldw_str_begin+3613
	.data.b	224,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3620
	.data.b	65,67,72,54,69,78,0
	.section	.debug_info		;off: 7985
	.data.w	.Ldw_str_begin+3620
	.data.b	225,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3627
	.data.b	65,67,72,55,69,78,0
	.section	.debug_info		;off: 8005
	.data.w	.Ldw_str_begin+3627
	.data.b	226,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3634
	.data.b	77,67,72,56,69,78,0
	.section	.debug_info		;off: 8025
	.data.w	.Ldw_str_begin+3634
	.data.b	227,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3641
	.data.b	77,67,72,57,69,78,0
	.section	.debug_info		;off: 8045
	.data.w	.Ldw_str_begin+3641
	.data.b	228,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3648
	.data.b	65,67,72,56,69,78,0
	.section	.debug_info		;off: 8065
	.data.w	.Ldw_str_begin+3648
	.data.b	229,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3655
	.data.b	65,67,72,57,69,78,0
	.section	.debug_info		;off: 8085
	.data.w	.Ldw_str_begin+3655
	.data.b	230,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3662
	.data.b	83,89,78,67,83,87,73,84,67,72,0
	.section	.debug_info		;off: 8105
	.data.w	.Ldw_str_begin+3662
	.data.b	231,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3673
	.data.b	73,78,84,69,82,69,78,0
	.section	.debug_info		;off: 8125
	.data.w	.Ldw_str_begin+3673
	.data.b	232,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3681
	.data.b	114,101,115,101,114,118,101,100,95,50,50,0
	.section	.debug_info		;off: 8145
	.data.w	.Ldw_str_begin+3681
	.data.b	233,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+739
	.data.b	4
	.data.b	0
	.data.b	10
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3693
	.data.b	68,83,65,68,67,95,71,76,79,66,83,89,78,67,95,66,105,116,115,0
	.section	.debug_info		;off: 8166
	.data.w	.Ldw_str_begin+3693
	.data.b	234,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+7697

	.data.b	73
	.data.b	242,3
	.data.b	1
	.data.b	34
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

	.section	.debug_info		;off: 8185
	.data.b	40
	.section	.debug_str		;off: 3713
	.data.b	85,0
	.section	.debug_info		;off: 8186
	.data.w	.Ldw_str_begin+3713
	.data.b	243,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3715
	.data.b	66,0
	.section	.debug_info		;off: 8203
	.data.w	.Ldw_str_begin+3715
	.data.b	244,3
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+2262
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3717
	.data.b	68,83,65,68,67,95,77,79,68,67,70,71,0
	.section	.debug_info		;off: 8221
	.data.w	.Ldw_str_begin+3717
	.data.b	245,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8178

	.data.b	73
	.data.b	250,3
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3730
	.data.b	85,0
	.section	.debug_info		;off: 8241
	.data.w	.Ldw_str_begin+3730
	.data.b	251,3
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3732
	.data.b	66,0
	.section	.debug_info		;off: 8258
	.data.w	.Ldw_str_begin+3732
	.data.b	252,3
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+2471
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3734
	.data.b	68,83,65,68,67,95,68,69,77,73,67,70,71,0
	.section	.debug_info		;off: 8276
	.data.w	.Ldw_str_begin+3734
	.data.b	253,3
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8233

	.data.b	73
	.data.b	130,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3748
	.data.b	85,0
	.section	.debug_info		;off: 8296
	.data.w	.Ldw_str_begin+3748
	.data.b	131,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3750
	.data.b	66,0
	.section	.debug_info		;off: 8313
	.data.w	.Ldw_str_begin+3750
	.data.b	132,4
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+2604
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3752
	.data.b	68,83,65,68,67,95,67,80,86,67,70,71,0
	.section	.debug_info		;off: 8331
	.data.w	.Ldw_str_begin+3752
	.data.b	133,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8288

	.data.b	73
	.data.b	138,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3765
	.data.b	85,0
	.section	.debug_info		;off: 8351
	.data.w	.Ldw_str_begin+3765
	.data.b	139,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3767
	.data.b	66,0
	.section	.debug_info		;off: 8368
	.data.w	.Ldw_str_begin+3767
	.data.b	140,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+2813
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3769
	.data.b	68,83,65,68,67,95,82,70,67,79,78,0
	.section	.debug_info		;off: 8386
	.data.w	.Ldw_str_begin+3769
	.data.b	141,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8343

	.data.b	73
	.data.b	146,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3781
	.data.b	85,0
	.section	.debug_info		;off: 8406
	.data.w	.Ldw_str_begin+3781
	.data.b	147,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3783
	.data.b	66,0
	.section	.debug_info		;off: 8423
	.data.w	.Ldw_str_begin+3783
	.data.b	148,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+2870
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3785
	.data.b	68,83,65,68,67,95,77,67,82,69,83,0
	.section	.debug_info		;off: 8441
	.data.w	.Ldw_str_begin+3785
	.data.b	149,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8398

	.data.b	73
	.data.b	154,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3797
	.data.b	85,0
	.section	.debug_info		;off: 8461
	.data.w	.Ldw_str_begin+3797
	.data.b	155,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3799
	.data.b	66,0
	.section	.debug_info		;off: 8478
	.data.w	.Ldw_str_begin+3799
	.data.b	156,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+2984
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3801
	.data.b	68,83,65,68,67,95,84,83,84,77,80,0
	.section	.debug_info		;off: 8496
	.data.w	.Ldw_str_begin+3801
	.data.b	157,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8453

	.data.b	73
	.data.b	162,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3813
	.data.b	85,0
	.section	.debug_info		;off: 8516
	.data.w	.Ldw_str_begin+3813
	.data.b	163,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3815
	.data.b	66,0
	.section	.debug_info		;off: 8533
	.data.w	.Ldw_str_begin+3815
	.data.b	164,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+3098
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3817
	.data.b	68,83,65,68,67,95,84,83,67,78,84,0
	.section	.debug_info		;off: 8551
	.data.w	.Ldw_str_begin+3817
	.data.b	165,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8508

	.data.b	73
	.data.b	170,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3829
	.data.b	85,0
	.section	.debug_info		;off: 8571
	.data.w	.Ldw_str_begin+3829
	.data.b	171,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3831
	.data.b	66,0
	.section	.debug_info		;off: 8588
	.data.w	.Ldw_str_begin+3831
	.data.b	172,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+3438
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3833
	.data.b	68,83,65,68,67,95,77,70,67,70,71,0
	.section	.debug_info		;off: 8606
	.data.w	.Ldw_str_begin+3833
	.data.b	173,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8563

	.data.b	73
	.data.b	178,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3845
	.data.b	85,0
	.section	.debug_info		;off: 8626
	.data.w	.Ldw_str_begin+3845
	.data.b	179,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3847
	.data.b	66,0
	.section	.debug_info		;off: 8643
	.data.w	.Ldw_str_begin+3847
	.data.b	180,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+3639
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3849
	.data.b	68,83,65,68,67,95,65,70,67,70,71,0
	.section	.debug_info		;off: 8661
	.data.w	.Ldw_str_begin+3849
	.data.b	181,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8618

	.data.b	73
	.data.b	186,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3861
	.data.b	85,0
	.section	.debug_info		;off: 8681
	.data.w	.Ldw_str_begin+3861
	.data.b	187,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3863
	.data.b	66,0
	.section	.debug_info		;off: 8698
	.data.w	.Ldw_str_begin+3863
	.data.b	188,4
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+3760
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3865
	.data.b	68,83,65,68,67,95,71,65,73,78,67,84,82,0
	.section	.debug_info		;off: 8716
	.data.w	.Ldw_str_begin+3865
	.data.b	189,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8673

	.data.b	73
	.data.b	194,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3879
	.data.b	85,0
	.section	.debug_info		;off: 8736
	.data.w	.Ldw_str_begin+3879
	.data.b	195,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3881
	.data.b	66,0
	.section	.debug_info		;off: 8753
	.data.w	.Ldw_str_begin+3881
	.data.b	196,4
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+3821
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3883
	.data.b	68,83,65,68,67,95,84,72,82,69,83,76,77,0
	.section	.debug_info		;off: 8771
	.data.w	.Ldw_str_begin+3883
	.data.b	197,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8728

	.data.b	73
	.data.b	202,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3897
	.data.b	85,0
	.section	.debug_info		;off: 8791
	.data.w	.Ldw_str_begin+3897
	.data.b	203,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3899
	.data.b	66,0
	.section	.debug_info		;off: 8808
	.data.w	.Ldw_str_begin+3899
	.data.b	204,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+3882
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3901
	.data.b	68,83,65,68,67,95,65,67,82,69,83,0
	.section	.debug_info		;off: 8826
	.data.w	.Ldw_str_begin+3901
	.data.b	205,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8783

	.data.b	73
	.data.b	210,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3913
	.data.b	85,0
	.section	.debug_info		;off: 8846
	.data.w	.Ldw_str_begin+3913
	.data.b	211,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3915
	.data.b	66,0
	.section	.debug_info		;off: 8863
	.data.w	.Ldw_str_begin+3915
	.data.b	212,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+4163
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3917
	.data.b	68,83,65,68,67,95,73,78,84,69,78,0
	.section	.debug_info		;off: 8881
	.data.w	.Ldw_str_begin+3917
	.data.b	213,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8838

	.data.b	73
	.data.b	218,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3929
	.data.b	85,0
	.section	.debug_info		;off: 8901
	.data.w	.Ldw_str_begin+3929
	.data.b	219,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3931
	.data.b	66,0
	.section	.debug_info		;off: 8918
	.data.w	.Ldw_str_begin+3931
	.data.b	220,4
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+4384
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3933
	.data.b	68,83,65,68,67,95,73,78,84,67,76,82,0
	.section	.debug_info		;off: 8936
	.data.w	.Ldw_str_begin+3933
	.data.b	221,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8893

	.data.b	73
	.data.b	226,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3946
	.data.b	85,0
	.section	.debug_info		;off: 8956
	.data.w	.Ldw_str_begin+3946
	.data.b	227,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3948
	.data.b	66,0
	.section	.debug_info		;off: 8973
	.data.w	.Ldw_str_begin+3948
	.data.b	228,4
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+4585
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3950
	.data.b	68,83,65,68,67,95,73,78,84,83,84,83,0
	.section	.debug_info		;off: 8991
	.data.w	.Ldw_str_begin+3950
	.data.b	229,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+8948

	.data.b	73
	.data.b	234,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3963
	.data.b	85,0
	.section	.debug_info		;off: 9011
	.data.w	.Ldw_str_begin+3963
	.data.b	235,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3965
	.data.b	66,0
	.section	.debug_info		;off: 9028
	.data.w	.Ldw_str_begin+3965
	.data.b	236,4
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+4646
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3967
	.data.b	68,83,65,68,67,95,84,69,83,84,67,70,71,0
	.section	.debug_info		;off: 9046
	.data.w	.Ldw_str_begin+3967
	.data.b	237,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9003

	.data.b	73
	.data.b	242,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3981
	.data.b	85,0
	.section	.debug_info		;off: 9066
	.data.w	.Ldw_str_begin+3981
	.data.b	243,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3983
	.data.b	66,0
	.section	.debug_info		;off: 9083
	.data.w	.Ldw_str_begin+3983
	.data.b	244,4
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+4707
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3985
	.data.b	68,83,65,68,67,95,67,79,77,80,0
	.section	.debug_info		;off: 9101
	.data.w	.Ldw_str_begin+3985
	.data.b	245,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9058

	.data.b	73
	.data.b	250,4
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3996
	.data.b	85,0
	.section	.debug_info		;off: 9121
	.data.w	.Ldw_str_begin+3996
	.data.b	251,4
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3998
	.data.b	66,0
	.section	.debug_info		;off: 9138
	.data.w	.Ldw_str_begin+3998
	.data.b	252,4
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+4848
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4000
	.data.b	68,83,65,68,67,95,83,77,69,78,0
	.section	.debug_info		;off: 9156
	.data.w	.Ldw_str_begin+4000
	.data.b	253,4
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9113

	.data.b	73
	.data.b	130,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4011
	.data.b	85,0
	.section	.debug_info		;off: 9176
	.data.w	.Ldw_str_begin+4011
	.data.b	131,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4013
	.data.b	66,0
	.section	.debug_info		;off: 9193
	.data.w	.Ldw_str_begin+4013
	.data.b	132,5
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+5009
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4015
	.data.b	68,83,65,68,67,95,65,76,65,67,76,82,0
	.section	.debug_info		;off: 9211
	.data.w	.Ldw_str_begin+4015
	.data.b	133,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9168

	.data.b	73
	.data.b	138,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4028
	.data.b	85,0
	.section	.debug_info		;off: 9231
	.data.w	.Ldw_str_begin+4028
	.data.b	139,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4030
	.data.b	66,0
	.section	.debug_info		;off: 9248
	.data.w	.Ldw_str_begin+4030
	.data.b	140,5
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+5250
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4032
	.data.b	68,83,65,68,67,95,65,76,65,83,84,83,0
	.section	.debug_info		;off: 9266
	.data.w	.Ldw_str_begin+4032
	.data.b	141,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9223

	.data.b	73
	.data.b	146,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4045
	.data.b	85,0
	.section	.debug_info		;off: 9286
	.data.w	.Ldw_str_begin+4045
	.data.b	147,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4047
	.data.b	66,0
	.section	.debug_info		;off: 9303
	.data.w	.Ldw_str_begin+4047
	.data.b	148,5
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+5331
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4049
	.data.b	68,83,65,68,67,95,70,65,73,78,0
	.section	.debug_info		;off: 9321
	.data.w	.Ldw_str_begin+4049
	.data.b	149,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9278

	.data.b	73
	.data.b	154,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4060
	.data.b	85,0
	.section	.debug_info		;off: 9341
	.data.w	.Ldw_str_begin+4060
	.data.b	155,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4062
	.data.b	66,0
	.section	.debug_info		;off: 9358
	.data.w	.Ldw_str_begin+4062
	.data.b	156,5
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+5372
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4064
	.data.b	68,83,65,68,67,95,68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 9376
	.data.w	.Ldw_str_begin+4064
	.data.b	157,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9333

	.data.b	73
	.data.b	162,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4079
	.data.b	85,0
	.section	.debug_info		;off: 9396
	.data.w	.Ldw_str_begin+4079
	.data.b	163,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4081
	.data.b	66,0
	.section	.debug_info		;off: 9413
	.data.w	.Ldw_str_begin+4081
	.data.b	164,5
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+5413
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4083
	.data.b	68,83,65,68,67,95,84,82,73,71,84,72,82,69,83,0
	.section	.debug_info		;off: 9431
	.data.w	.Ldw_str_begin+4083
	.data.b	165,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9388

	.data.b	73
	.data.b	170,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4099
	.data.b	85,0
	.section	.debug_info		;off: 9451
	.data.w	.Ldw_str_begin+4099
	.data.b	171,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4101
	.data.b	66,0
	.section	.debug_info		;off: 9468
	.data.w	.Ldw_str_begin+4101
	.data.b	172,5
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+5554
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4103
	.data.b	68,83,65,68,67,95,67,79,77,80,67,79,78,0
	.section	.debug_info		;off: 9486
	.data.w	.Ldw_str_begin+4103
	.data.b	173,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9443

	.data.b	73
	.data.b	178,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4117
	.data.b	85,0
	.section	.debug_info		;off: 9506
	.data.w	.Ldw_str_begin+4117
	.data.b	179,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4119
	.data.b	66,0
	.section	.debug_info		;off: 9523
	.data.w	.Ldw_str_begin+4119
	.data.b	180,5
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+5615
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4121
	.data.b	68,83,65,68,67,95,84,69,83,84,77,79,68,69,0
	.section	.debug_info		;off: 9541
	.data.w	.Ldw_str_begin+4121
	.data.b	181,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9498

	.data.b	73
	.data.b	186,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4136
	.data.b	85,0
	.section	.debug_info		;off: 9561
	.data.w	.Ldw_str_begin+4136
	.data.b	187,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4138
	.data.b	66,0
	.section	.debug_info		;off: 9578
	.data.w	.Ldw_str_begin+4138
	.data.b	188,5
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+5676
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4140
	.data.b	68,83,65,68,67,95,68,73,84,72,69,82,69,78,0
	.section	.debug_info		;off: 9596
	.data.w	.Ldw_str_begin+4140
	.data.b	189,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9553

	.data.b	73
	.data.b	194,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4155
	.data.b	85,0
	.section	.debug_info		;off: 9616
	.data.w	.Ldw_str_begin+4155
	.data.b	195,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4157
	.data.b	66,0
	.section	.debug_info		;off: 9633
	.data.w	.Ldw_str_begin+4157
	.data.b	196,5
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+5897
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4159
	.data.b	68,83,65,68,67,95,67,87,67,70,71,0
	.section	.debug_info		;off: 9651
	.data.w	.Ldw_str_begin+4159
	.data.b	197,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9608

	.data.b	73
	.data.b	202,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4171
	.data.b	85,0
	.section	.debug_info		;off: 9671
	.data.w	.Ldw_str_begin+4171
	.data.b	203,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4173
	.data.b	66,0
	.section	.debug_info		;off: 9688
	.data.w	.Ldw_str_begin+4173
	.data.b	204,5
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+5998
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4175
	.data.b	68,83,65,68,67,95,67,87,83,89,78,67,0
	.section	.debug_info		;off: 9706
	.data.w	.Ldw_str_begin+4175
	.data.b	205,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9663

	.data.b	73
	.data.b	210,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4188
	.data.b	85,0
	.section	.debug_info		;off: 9726
	.data.w	.Ldw_str_begin+4188
	.data.b	211,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4190
	.data.b	66,0
	.section	.debug_info		;off: 9743
	.data.w	.Ldw_str_begin+4190
	.data.b	212,5
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+6099
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4192
	.data.b	68,83,65,68,67,95,73,78,84,69,82,67,79,78,0
	.section	.debug_info		;off: 9761
	.data.w	.Ldw_str_begin+4192
	.data.b	213,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9718

	.data.b	73
	.data.b	218,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4207
	.data.b	85,0
	.section	.debug_info		;off: 9781
	.data.w	.Ldw_str_begin+4207
	.data.b	219,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4209
	.data.b	66,0
	.section	.debug_info		;off: 9798
	.data.w	.Ldw_str_begin+4209
	.data.b	220,5
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+6180
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4211
	.data.b	68,83,65,68,67,95,66,85,83,69,82,82,77,83,75,0
	.section	.debug_info		;off: 9816
	.data.w	.Ldw_str_begin+4211
	.data.b	221,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9773

	.data.b	73
	.data.b	226,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4227
	.data.b	85,0
	.section	.debug_info		;off: 9836
	.data.w	.Ldw_str_begin+4227
	.data.b	227,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4229
	.data.b	66,0
	.section	.debug_info		;off: 9853
	.data.w	.Ldw_str_begin+4229
	.data.b	228,5
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+6301
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4231
	.data.b	68,83,65,68,67,95,68,69,66,85,71,0
	.section	.debug_info		;off: 9871
	.data.w	.Ldw_str_begin+4231
	.data.b	229,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9828

	.data.b	73
	.data.b	234,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4243
	.data.b	85,0
	.section	.debug_info		;off: 9891
	.data.w	.Ldw_str_begin+4243
	.data.b	235,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4245
	.data.b	66,0
	.section	.debug_info		;off: 9908
	.data.w	.Ldw_str_begin+4245
	.data.b	236,5
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+6762
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4247
	.data.b	68,83,65,68,67,95,71,76,79,66,67,82,67,0
	.section	.debug_info		;off: 9926
	.data.w	.Ldw_str_begin+4247
	.data.b	237,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9883

	.data.b	73
	.data.b	242,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4261
	.data.b	85,0
	.section	.debug_info		;off: 9946
	.data.w	.Ldw_str_begin+4261
	.data.b	243,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4263
	.data.b	66,0
	.section	.debug_info		;off: 9963
	.data.w	.Ldw_str_begin+4263
	.data.b	244,5
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+7223
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4265
	.data.b	68,83,65,68,67,95,71,76,79,66,69,86,83,70,0
	.section	.debug_info		;off: 9981
	.data.w	.Ldw_str_begin+4265
	.data.b	245,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9938

	.data.b	73
	.data.b	250,5
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4280
	.data.b	85,0
	.section	.debug_info		;off: 10001
	.data.w	.Ldw_str_begin+4280
	.data.b	251,5
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4282
	.data.b	66,0
	.section	.debug_info		;off: 10018
	.data.w	.Ldw_str_begin+4282
	.data.b	252,5
	.data.b	28
	.data.b	34
	.data.w	.Ldw_begin+7684
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4284
	.data.b	68,83,65,68,67,95,71,76,79,66,69,86,83,70,67,76,82,0
	.section	.debug_info		;off: 10036
	.data.w	.Ldw_str_begin+4284
	.data.b	253,5
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9993

	.data.b	73
	.data.b	130,6
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4302
	.data.b	85,0
	.section	.debug_info		;off: 10056
	.data.w	.Ldw_str_begin+4302
	.data.b	131,6
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4304
	.data.b	66,0
	.section	.debug_info		;off: 10073
	.data.w	.Ldw_str_begin+4304
	.data.b	132,6
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+8165
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4306
	.data.b	68,83,65,68,67,95,71,76,79,66,83,89,78,67,0
	.section	.debug_info		;off: 10091
	.data.w	.Ldw_str_begin+4306
	.data.b	133,6
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+10048

	.data.b	71
	.data.b	141,6
	.data.b	1
	.data.b	34
	.data.b	124
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4321
	.data.b	77,79,68,67,70,71,0
	.section	.debug_info		;off: 10111
	.data.w	.Ldw_str_begin+4321
	.data.b	142,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+8220
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4328
	.data.b	68,69,77,73,67,70,71,0
	.section	.debug_info		;off: 10128
	.data.w	.Ldw_str_begin+4328
	.data.b	143,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8275
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4336
	.data.b	67,80,86,67,70,71,0
	.section	.debug_info		;off: 10145
	.data.w	.Ldw_str_begin+4336
	.data.b	144,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+8330
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4343
	.data.b	114,101,115,101,114,118,101,100,95,48,67,0
	.section	.debug_info		;off: 10162
	.data.w	.Ldw_str_begin+4343
	.data.b	145,6
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1844
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4355
	.data.b	82,70,67,79,78,0
	.section	.debug_info		;off: 10179
	.data.w	.Ldw_str_begin+4355
	.data.b	146,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8385
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4361
	.data.b	77,67,82,69,83,0
	.section	.debug_info		;off: 10196
	.data.w	.Ldw_str_begin+4361
	.data.b	147,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8440
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4367
	.data.b	84,83,84,77,80,0
	.section	.debug_info		;off: 10213
	.data.w	.Ldw_str_begin+4367
	.data.b	148,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8495
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4373
	.data.b	84,83,67,78,84,0
	.section	.debug_info		;off: 10230
	.data.w	.Ldw_str_begin+4373
	.data.b	149,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8550
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4379
	.data.b	77,70,67,70,71,0
	.section	.debug_info		;off: 10247
	.data.w	.Ldw_str_begin+4379
	.data.b	150,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8605
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4385
	.data.b	65,70,67,70,71,0
	.section	.debug_info		;off: 10264
	.data.w	.Ldw_str_begin+4385
	.data.b	151,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8660
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4391
	.data.b	71,65,73,78,67,84,82,0
	.section	.debug_info		;off: 10281
	.data.w	.Ldw_str_begin+4391
	.data.b	152,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8715
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4399
	.data.b	84,72,82,69,83,76,77,0
	.section	.debug_info		;off: 10298
	.data.w	.Ldw_str_begin+4399
	.data.b	153,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8770
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4407
	.data.b	65,67,82,69,83,0
	.section	.debug_info		;off: 10315
	.data.w	.Ldw_str_begin+4407
	.data.b	154,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8825
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4413
	.data.b	73,78,84,69,78,0
	.section	.debug_info		;off: 10332
	.data.w	.Ldw_str_begin+4413
	.data.b	155,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+8880
	.data.b	2,35
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4419
	.data.b	73,78,84,67,76,82,0
	.section	.debug_info		;off: 10349
	.data.w	.Ldw_str_begin+4419
	.data.b	156,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+8935
	.data.b	2,35
	.data.b	56
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4426
	.data.b	73,78,84,83,84,83,0
	.section	.debug_info		;off: 10366
	.data.w	.Ldw_str_begin+4426
	.data.b	157,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+8990
	.data.b	2,35
	.data.b	60
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4433
	.data.b	84,69,83,84,67,70,71,0
	.section	.debug_info		;off: 10383
	.data.w	.Ldw_str_begin+4433
	.data.b	158,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+9045
	.data.b	2,35
	.data.b	64
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4441
	.data.b	67,79,77,80,0
	.section	.debug_info		;off: 10400
	.data.w	.Ldw_str_begin+4441
	.data.b	159,6
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+9100
	.data.b	2,35
	.data.b	68
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4446
	.data.b	83,77,69,78,0
	.section	.debug_info		;off: 10417
	.data.w	.Ldw_str_begin+4446
	.data.b	160,6
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+9155
	.data.b	2,35
	.data.b	72
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4451
	.data.b	65,76,65,67,76,82,0
	.section	.debug_info		;off: 10434
	.data.w	.Ldw_str_begin+4451
	.data.b	161,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+9210
	.data.b	2,35
	.data.b	76
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4458
	.data.b	65,76,65,83,84,83,0
	.section	.debug_info		;off: 10451
	.data.w	.Ldw_str_begin+4458
	.data.b	162,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+9265
	.data.b	2,35
	.data.b	80
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4465
	.data.b	70,65,73,78,0
	.section	.debug_info		;off: 10468
	.data.w	.Ldw_str_begin+4465
	.data.b	163,6
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+9320
	.data.b	2,35
	.data.b	84
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4470
	.data.b	68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 10485
	.data.w	.Ldw_str_begin+4470
	.data.b	164,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+9375
	.data.b	2,35
	.data.b	88
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4479
	.data.b	84,82,73,71,84,72,82,69,83,0
	.section	.debug_info		;off: 10502
	.data.w	.Ldw_str_begin+4479
	.data.b	165,6
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+9430
	.data.b	2,35
	.data.b	92
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4489
	.data.b	67,79,77,80,67,79,78,0
	.section	.debug_info		;off: 10519
	.data.w	.Ldw_str_begin+4489
	.data.b	166,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+9485
	.data.b	2,35
	.data.b	96
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4497
	.data.b	84,69,83,84,77,79,68,69,0
	.section	.debug_info		;off: 10536
	.data.w	.Ldw_str_begin+4497
	.data.b	167,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+9540
	.data.b	2,35
	.data.b	100
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4506
	.data.b	68,73,84,72,69,82,69,78,0
	.section	.debug_info		;off: 10553
	.data.w	.Ldw_str_begin+4506
	.data.b	168,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+9595
	.data.b	2,35
	.data.b	104
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4515
	.data.b	67,87,67,70,71,0
	.section	.debug_info		;off: 10570
	.data.w	.Ldw_str_begin+4515
	.data.b	169,6
	.data.b	17
	.data.b	34
	.data.w	.Ldw_begin+9650
	.data.b	2,35
	.data.b	108
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4521
	.data.b	67,87,83,89,78,67,0
	.section	.debug_info		;off: 10587
	.data.w	.Ldw_str_begin+4521
	.data.b	170,6
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+9705
	.data.b	2,35
	.data.b	112
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4528
	.data.b	73,78,84,69,82,67,79,78,0
	.section	.debug_info		;off: 10604
	.data.w	.Ldw_str_begin+4528
	.data.b	171,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+9760
	.data.b	2,35
	.data.b	116
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4537
	.data.b	66,85,83,69,82,82,77,83,75,0
	.section	.debug_info		;off: 10621
	.data.w	.Ldw_str_begin+4537
	.data.b	172,6
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+9815
	.data.b	2,35
	.data.b	120
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4547
	.data.b	68,83,65,68,67,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 10639
	.data.w	.Ldw_str_begin+4547
	.data.b	173,6
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+121

	.data.b	71
	.data.b	178,6
	.data.b	1
	.data.b	34
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4560
	.data.b	68,69,66,85,71,0
	.section	.debug_info		;off: 10659
	.data.w	.Ldw_str_begin+4560
	.data.b	179,6
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+9870
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4566
	.data.b	71,76,79,66,67,82,67,0
	.section	.debug_info		;off: 10676
	.data.w	.Ldw_str_begin+4566
	.data.b	180,6
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+9925
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4574
	.data.b	71,76,79,66,69,86,83,70,0
	.section	.debug_info		;off: 10693
	.data.w	.Ldw_str_begin+4574
	.data.b	181,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+9980
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4583
	.data.b	71,76,79,66,69,86,83,70,67,76,82,0
	.section	.debug_info		;off: 10710
	.data.w	.Ldw_str_begin+4583
	.data.b	182,6
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+10035
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4595
	.data.b	71,76,79,66,83,89,78,67,0
	.section	.debug_info		;off: 10727
	.data.w	.Ldw_str_begin+4595
	.data.b	183,6
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+10090
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4604
	.data.b	68,83,65,68,67,95,67,79,77,77,79,78,0
	.section	.debug_info		;off: 10745
	.data.w	.Ldw_str_begin+4604
	.data.b	184,6
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+746

	.data.b	52
	.section	.debug_str		;off: 4617
	.data.b	0
	.section	.debug_info		;off: 10758
	.data.w	.Ldw_str_begin+4617
	.data.b	70
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4618
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,83,79,70,84,87,65,82,69,0
	.section	.debug_info		;off: 10768
	.data.w	.Ldw_str_begin+4618
	.data.b	71
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4661
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,0
	.section	.debug_info		;off: 10777
	.data.w	.Ldw_str_begin+4661
	.data.b	72
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4702
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,0
	.section	.debug_info		;off: 10786
	.data.w	.Ldw_str_begin+4702
	.data.b	73
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 4744
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,66,79,84,72,0
	.section	.debug_info		;off: 10795
	.data.w	.Ldw_str_begin+4744
	.data.b	74
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4783
	.data.b	68,115,97,100,99,95,73,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 10805
	.data.w	.Ldw_str_begin+4783
	.data.b	75
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+10757

	.data.b	52
	.section	.debug_str		;off: 4817
	.data.b	0
	.section	.debug_info		;off: 10817
	.data.w	.Ldw_str_begin+4817
	.data.b	79
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4818
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,65,0
	.section	.debug_info		;off: 10827
	.data.w	.Ldw_str_begin+4818
	.data.b	80
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4840
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,66,0
	.section	.debug_info		;off: 10836
	.data.w	.Ldw_str_begin+4840
	.data.b	81
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4862
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,0
	.section	.debug_info		;off: 10845
	.data.w	.Ldw_str_begin+4862
	.data.b	82
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 4884
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,68,0
	.section	.debug_info		;off: 10854
	.data.w	.Ldw_str_begin+4884
	.data.b	83
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 4906
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,69,0
	.section	.debug_info		;off: 10863
	.data.w	.Ldw_str_begin+4906
	.data.b	84
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 4928
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,70,0
	.section	.debug_info		;off: 10872
	.data.w	.Ldw_str_begin+4928
	.data.b	85
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 4950
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,0
	.section	.debug_info		;off: 10881
	.data.w	.Ldw_str_begin+4950
	.data.b	86
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 4972
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,72,0
	.section	.debug_info		;off: 10890
	.data.w	.Ldw_str_begin+4972
	.data.b	87
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 4994
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,73,0
	.section	.debug_info		;off: 10899
	.data.w	.Ldw_str_begin+4994
	.data.b	88
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 5016
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,74,0
	.section	.debug_info		;off: 10908
	.data.w	.Ldw_str_begin+5016
	.data.b	89
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 5038
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,75,0
	.section	.debug_info		;off: 10917
	.data.w	.Ldw_str_begin+5038
	.data.b	90
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 5060
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,76,0
	.section	.debug_info		;off: 10926
	.data.w	.Ldw_str_begin+5060
	.data.b	91
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 5082
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,77,0
	.section	.debug_info		;off: 10935
	.data.w	.Ldw_str_begin+5082
	.data.b	92
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 5104
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,78,0
	.section	.debug_info		;off: 10944
	.data.w	.Ldw_str_begin+5104
	.data.b	93
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 5126
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,79,0
	.section	.debug_info		;off: 10953
	.data.w	.Ldw_str_begin+5126
	.data.b	94
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 5148
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,80,0
	.section	.debug_info		;off: 10962
	.data.w	.Ldw_str_begin+5148
	.data.b	95
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5170
	.data.b	68,115,97,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 10972
	.data.w	.Ldw_str_begin+5170
	.data.b	96
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+10816

	.data.b	52
	.section	.debug_str		;off: 5190
	.data.b	0
	.section	.debug_info		;off: 10984
	.data.w	.Ldw_str_begin+5190
	.data.b	100
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5191
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,78,79,78,69,0
	.section	.debug_info		;off: 10994
	.data.w	.Ldw_str_begin+5191
	.data.b	101
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5223
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,0
	.section	.debug_info		;off: 11003
	.data.w	.Ldw_str_begin+5223
	.data.b	102
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5257
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,0
	.section	.debug_info		;off: 11012
	.data.w	.Ldw_str_begin+5257
	.data.b	103
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5292
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,66,79,84,72,0
	.section	.debug_info		;off: 11021
	.data.w	.Ldw_str_begin+5292
	.data.b	104
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5324
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 11031
	.data.w	.Ldw_str_begin+5324
	.data.b	105
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+10983

	.data.b	52
	.section	.debug_str		;off: 5351
	.data.b	0
	.section	.debug_info		;off: 11043
	.data.w	.Ldw_str_begin+5351
	.data.b	109
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5352
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,49,0
	.section	.debug_info		;off: 11053
	.data.w	.Ldw_str_begin+5352
	.data.b	110
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5381
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,50,0
	.section	.debug_info		;off: 11062
	.data.w	.Ldw_str_begin+5381
	.data.b	111
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5410
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,51,0
	.section	.debug_info		;off: 11071
	.data.w	.Ldw_str_begin+5410
	.data.b	112
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5439
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,52,0
	.section	.debug_info		;off: 11080
	.data.w	.Ldw_str_begin+5439
	.data.b	113
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5468
	.data.b	68,115,97,100,99,95,67,105,99,80,97,114,97,108,108,101,108,83,101,108,101,99,116,105,111,110,0
	.section	.debug_info		;off: 11090
	.data.w	.Ldw_str_begin+5468
	.data.b	114
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11042

	.data.b	52
	.section	.debug_str		;off: 5495
	.data.b	0
	.section	.debug_info		;off: 11102
	.data.w	.Ldw_str_begin+5495
	.data.b	146,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5496
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,78,79,78,69,0
	.section	.debug_info		;off: 11113
	.data.w	.Ldw_str_begin+5496
	.data.b	147,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5522
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,72,73,71,72,0
	.section	.debug_info		;off: 11123
	.data.w	.Ldw_str_begin+5522
	.data.b	148,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5548
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,76,79,87,0
	.section	.debug_info		;off: 11133
	.data.w	.Ldw_str_begin+5548
	.data.b	149,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5573
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,70,73,70,79,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 11143
	.data.w	.Ldw_str_begin+5573
	.data.b	150,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5608
	.data.b	68,115,97,100,99,95,83,101,114,118,105,99,101,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 11154
	.data.w	.Ldw_str_begin+5608
	.data.b	151,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11101

	.data.b	52
	.section	.debug_str		;off: 5629
	.data.b	0
	.section	.debug_info		;off: 11167
	.data.w	.Ldw_str_begin+5629
	.data.b	155,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5630
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,78,69,87,82,69,83,85,76,84,0
	.section	.debug_info		;off: 11178
	.data.w	.Ldw_str_begin+5630
	.data.b	156,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5661
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,82,69,83,85,76,84,73,78,82,65,78,71,69,0
	.section	.debug_info		;off: 11188
	.data.w	.Ldw_str_begin+5661
	.data.b	157,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5696
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,82,69,83,85,76,84,79,85,84,82,65,78,71,69,0
	.section	.debug_info		;off: 11198
	.data.w	.Ldw_str_begin+5696
	.data.b	158,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5732
	.data.b	68,115,97,100,99,95,77,97,105,110,65,108,97,114,109,67,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 11209
	.data.w	.Ldw_str_begin+5732
	.data.b	159,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11166

	.data.b	52
	.section	.debug_str		;off: 5757
	.data.b	0
	.section	.debug_info		;off: 11222
	.data.w	.Ldw_str_begin+5757
	.data.b	163,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5758
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,48,0
	.section	.debug_info		;off: 11233
	.data.w	.Ldw_str_begin+5758
	.data.b	164,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5784
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,49,0
	.section	.debug_info		;off: 11243
	.data.w	.Ldw_str_begin+5784
	.data.b	165,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5810
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,50,0
	.section	.debug_info		;off: 11253
	.data.w	.Ldw_str_begin+5810
	.data.b	166,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5836
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,51,0
	.section	.debug_info		;off: 11263
	.data.w	.Ldw_str_begin+5836
	.data.b	167,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5862
	.data.b	68,115,97,100,99,95,70,105,114,79,102,102,115,101,116,0
	.section	.debug_info		;off: 11274
	.data.w	.Ldw_str_begin+5862
	.data.b	168,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11221

	.data.b	52
	.section	.debug_str		;off: 5878
	.data.b	0
	.section	.debug_info		;off: 11287
	.data.w	.Ldw_str_begin+5878
	.data.b	172,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5879
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,48,0
	.section	.debug_info		;off: 11298
	.data.w	.Ldw_str_begin+5879
	.data.b	173,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5912
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,49,0
	.section	.debug_info		;off: 11308
	.data.w	.Ldw_str_begin+5912
	.data.b	174,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5945
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,50,0
	.section	.debug_info		;off: 11318
	.data.w	.Ldw_str_begin+5945
	.data.b	175,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5978
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,51,0
	.section	.debug_info		;off: 11328
	.data.w	.Ldw_str_begin+5978
	.data.b	176,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6011
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,52,0
	.section	.debug_info		;off: 11338
	.data.w	.Ldw_str_begin+6011
	.data.b	177,1
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 6044
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,53,0
	.section	.debug_info		;off: 11348
	.data.w	.Ldw_str_begin+6044
	.data.b	178,1
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 6077
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,54,0
	.section	.debug_info		;off: 11358
	.data.w	.Ldw_str_begin+6077
	.data.b	179,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 6110
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,55,0
	.section	.debug_info		;off: 11368
	.data.w	.Ldw_str_begin+6110
	.data.b	180,1
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6143
	.data.b	68,115,97,100,99,95,70,105,108,116,101,114,79,102,102,115,101,116,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 11379
	.data.w	.Ldw_str_begin+6143
	.data.b	181,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11286

	.data.b	52
	.section	.debug_str		;off: 6174
	.data.b	0
	.section	.debug_info		;off: 11392
	.data.w	.Ldw_str_begin+6174
	.data.b	185,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6175
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,78,79,78,69,0
	.section	.debug_info		;off: 11403
	.data.w	.Ldw_str_begin+6175
	.data.b	186,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6197
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,83,73,78,69,0
	.section	.debug_info		;off: 11413
	.data.w	.Ldw_str_begin+6197
	.data.b	187,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6219
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,84,82,73,65,78,71,85,76,65,82,0
	.section	.debug_info		;off: 11423
	.data.w	.Ldw_str_begin+6219
	.data.b	188,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6247
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,83,81,85,65,82,69,0
	.section	.debug_info		;off: 11433
	.data.w	.Ldw_str_begin+6247
	.data.b	189,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6271
	.data.b	68,115,97,100,99,95,87,97,118,101,77,111,100,101,0
	.section	.debug_info		;off: 11444
	.data.w	.Ldw_str_begin+6271
	.data.b	190,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11391

	.data.b	52
	.section	.debug_str		;off: 6286
	.data.b	0
	.section	.debug_info		;off: 11457
	.data.w	.Ldw_str_begin+6286
	.data.b	194,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6287
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,49,0
	.section	.debug_info		;off: 11468
	.data.w	.Ldw_str_begin+6287
	.data.b	195,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6309
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,50,0
	.section	.debug_info		;off: 11478
	.data.w	.Ldw_str_begin+6309
	.data.b	196,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6331
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,51,0
	.section	.debug_info		;off: 11488
	.data.w	.Ldw_str_begin+6331
	.data.b	197,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6353
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,52,0
	.section	.debug_info		;off: 11498
	.data.w	.Ldw_str_begin+6353
	.data.b	198,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6375
	.data.b	68,115,97,100,99,95,70,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 11509
	.data.w	.Ldw_str_begin+6375
	.data.b	199,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11456

	.data.b	52
	.section	.debug_str		;off: 6395
	.data.b	0
	.section	.debug_info		;off: 11522
	.data.w	.Ldw_str_begin+6395
	.data.b	203,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6396
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,48,68,66,0
	.section	.debug_info		;off: 11533
	.data.w	.Ldw_str_begin+6396
	.data.b	204,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6414
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,54,68,66,0
	.section	.debug_info		;off: 11543
	.data.w	.Ldw_str_begin+6414
	.data.b	205,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6432
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,49,50,68,66,0
	.section	.debug_info		;off: 11553
	.data.w	.Ldw_str_begin+6432
	.data.b	206,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6451
	.data.b	68,115,97,100,99,95,80,103,97,71,97,105,110,0
	.section	.debug_info		;off: 11564
	.data.w	.Ldw_str_begin+6451
	.data.b	207,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11521

	.data.b	52
	.section	.debug_str		;off: 6465
	.data.b	0
	.section	.debug_info		;off: 11577
	.data.w	.Ldw_str_begin+6465
	.data.b	211,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6466
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,49,0
	.section	.debug_info		;off: 11588
	.data.w	.Ldw_str_begin+6466
	.data.b	212,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6496
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,50,0
	.section	.debug_info		;off: 11598
	.data.w	.Ldw_str_begin+6496
	.data.b	213,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6526
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,52,0
	.section	.debug_info		;off: 11608
	.data.w	.Ldw_str_begin+6526
	.data.b	214,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6556
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,56,0
	.section	.debug_info		;off: 11618
	.data.w	.Ldw_str_begin+6556
	.data.b	215,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6586
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,67,108,111,99,107,68,105,118,105,100,101,114,0
	.section	.debug_info		;off: 11629
	.data.w	.Ldw_str_begin+6586
	.data.b	216,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11576

	.data.b	52
	.section	.debug_str		;off: 6614
	.data.b	0
	.section	.debug_info		;off: 11642
	.data.w	.Ldw_str_begin+6614
	.data.b	220,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6615
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,50,0
	.section	.debug_info		;off: 11653
	.data.w	.Ldw_str_begin+6615
	.data.b	221,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6639
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,52,0
	.section	.debug_info		;off: 11663
	.data.w	.Ldw_str_begin+6639
	.data.b	222,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6663
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,56,0
	.section	.debug_info		;off: 11673
	.data.w	.Ldw_str_begin+6663
	.data.b	223,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6687
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,49,54,0
	.section	.debug_info		;off: 11683
	.data.w	.Ldw_str_begin+6687
	.data.b	224,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6712
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,51,50,0
	.section	.debug_info		;off: 11693
	.data.w	.Ldw_str_begin+6712
	.data.b	225,1
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 6737
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,54,52,0
	.section	.debug_info		;off: 11703
	.data.w	.Ldw_str_begin+6737
	.data.b	226,1
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6762
	.data.b	68,115,97,100,99,95,77,101,97,110,83,104,105,102,116,76,101,110,103,116,104,0
	.section	.debug_info		;off: 11714
	.data.w	.Ldw_str_begin+6762
	.data.b	227,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11641

	.data.b	71
	.data.b	235,1
	.data.b	1
	.data.b	35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6784
	.data.b	112,111,115,105,116,105,118,101,73,110,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 11734
	.data.w	.Ldw_str_begin+6784
	.data.b	236,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6804
	.data.b	110,101,103,97,116,105,118,101,73,110,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 11751
	.data.w	.Ldw_str_begin+6804
	.data.b	237,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6824
	.data.b	112,111,115,105,116,105,118,101,73,110,112,117,116,76,105,110,101,0
	.section	.debug_info		;off: 11768
	.data.w	.Ldw_str_begin+6824
	.data.b	238,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6842
	.data.b	110,101,103,97,116,105,118,101,73,110,112,117,116,76,105,110,101,0
	.section	.debug_info		;off: 11785
	.data.w	.Ldw_str_begin+6842
	.data.b	239,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6860
	.data.b	105,110,112,117,116,80,105,110,0
	.section	.debug_info		;off: 11802
	.data.w	.Ldw_str_begin+6860
	.data.b	240,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6869
	.data.b	105,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,77,111,100,101,0
	.section	.debug_info		;off: 11819
	.data.w	.Ldw_str_begin+6869
	.data.b	241,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6890
	.data.b	97,117,116,111,80,111,119,101,114,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 11836
	.data.w	.Ldw_str_begin+6890
	.data.b	242,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6907
	.data.b	112,103,97,71,97,105,110,0
	.section	.debug_info		;off: 11853
	.data.w	.Ldw_str_begin+6907
	.data.b	243,1
	.data.b	19
	.data.b	35
	.data.w	.Ldw_begin+11563
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6915
	.data.b	105,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 11870
	.data.w	.Ldw_str_begin+6915
	.data.b	244,1
	.data.b	39
	.data.b	35
	.data.w	.Ldw_begin+10804
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6943
	.data.b	68,115,97,100,99,95,77,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 11888
	.data.w	.Ldw_str_begin+6943
	.data.b	245,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11726

	.data.b	71
	.data.b	251,1
	.data.b	1
	.data.b	35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6965
	.data.b	114,101,115,117,108,116,68,105,115,112,108,97,121,77,111,100,101,0
	.section	.debug_info		;off: 11908
	.data.w	.Ldw_str_begin+6965
	.data.b	252,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6983
	.data.b	116,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 11925
	.data.w	.Ldw_str_begin+6983
	.data.b	253,1
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+10971
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6997
	.data.b	68,115,97,100,99,95,68,101,109,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 11943
	.data.w	.Ldw_str_begin+6997
	.data.b	254,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11900

	.data.b	71
	.data.b	132,2
	.data.b	1
	.data.b	35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7021
	.data.b	115,116,97,114,116,0
	.section	.debug_info		;off: 11963
	.data.w	.Ldw_str_begin+7021
	.data.b	133,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7027
	.data.b	109,117,108,116,105,112,108,101,120,101,114,67,111,112,121,69,110,97,98,108,101,0
	.section	.debug_info		;off: 11980
	.data.w	.Ldw_str_begin+7027
	.data.b	134,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7049
	.data.b	116,105,109,101,83,116,97,109,112,70,114,101,113,117,101,110,99,121,0
	.section	.debug_info		;off: 11997
	.data.w	.Ldw_str_begin+7049
	.data.b	135,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7068
	.data.b	100,105,118,105,100,101,114,0
	.section	.debug_info		;off: 12014
	.data.w	.Ldw_str_begin+7068
	.data.b	136,2
	.data.b	33
	.data.b	35
	.data.w	.Ldw_begin+11628
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7076
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 12031
	.data.w	.Ldw_str_begin+7076
	.data.b	137,2
	.data.b	32
	.data.b	35
	.data.w	.Ldw_begin+11030
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7081
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12049
	.data.w	.Ldw_str_begin+7081
	.data.b	138,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+11955

	.data.b	71
	.data.b	144,2
	.data.b	1
	.data.b	35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7103
	.data.b	109,101,97,110,77,111,100,101,0
	.section	.debug_info		;off: 12069
	.data.w	.Ldw_str_begin+7103
	.data.b	145,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7112
	.data.b	109,101,97,110,80,111,105,110,116,0
	.section	.debug_info		;off: 12086
	.data.w	.Ldw_str_begin+7112
	.data.b	146,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7122
	.data.b	115,104,105,102,116,76,101,110,103,116,104,0
	.section	.debug_info		;off: 12103
	.data.w	.Ldw_str_begin+7122
	.data.b	147,2
	.data.b	27
	.data.b	35
	.data.w	.Ldw_begin+11713
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7134
	.data.b	68,115,97,100,99,95,77,101,97,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12121
	.data.w	.Ldw_str_begin+7134
	.data.b	148,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+12061

	.data.b	71
	.data.b	154,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7151
	.data.b	116,104,114,101,115,104,111,108,100,76,111,119,101,114,0
	.section	.debug_info		;off: 12141
	.data.w	.Ldw_str_begin+7151
	.data.b	155,2
	.data.b	12
	.data.b	35
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7166
	.data.b	116,104,114,101,115,104,111,108,100,85,112,112,101,114,0
	.section	.debug_info		;off: 12158
	.data.w	.Ldw_str_begin+7166
	.data.b	156,2
	.data.b	12
	.data.b	35
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7181
	.data.b	68,115,97,100,99,95,84,104,114,101,115,104,111,108,100,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12176
	.data.w	.Ldw_str_begin+7181
	.data.b	157,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+12133

	.data.b	71
	.data.b	163,2
	.data.b	1
	.data.b	35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7203
	.data.b	99,105,99,70,105,108,116,101,114,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12196
	.data.w	.Ldw_str_begin+7203
	.data.b	164,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7219
	.data.b	100,101,99,105,109,97,116,105,111,110,82,97,116,101,48,0
	.section	.debug_info		;off: 12213
	.data.w	.Ldw_str_begin+7219
	.data.b	165,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7235
	.data.b	100,101,99,105,109,97,116,105,111,110,82,97,116,101,49,0
	.section	.debug_info		;off: 12230
	.data.w	.Ldw_str_begin+7235
	.data.b	166,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7251
	.data.b	102,105,114,48,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12247
	.data.w	.Ldw_str_begin+7251
	.data.b	167,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7262
	.data.b	102,105,114,49,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12264
	.data.w	.Ldw_str_begin+7262
	.data.b	168,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7273
	.data.b	102,105,114,79,102,102,115,101,116,48,0
	.section	.debug_info		;off: 12281
	.data.w	.Ldw_str_begin+7273
	.data.b	169,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7284
	.data.b	99,105,99,70,105,108,116,101,114,83,97,109,112,108,105,110,103,0
	.section	.debug_info		;off: 12298
	.data.w	.Ldw_str_begin+7284
	.data.b	170,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7302
	.data.b	112,97,114,97,108,108,101,108,0
	.section	.debug_info		;off: 12315
	.data.w	.Ldw_str_begin+7302
	.data.b	171,2
	.data.b	32
	.data.b	35
	.data.w	.Ldw_begin+11089
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7311
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 12332
	.data.w	.Ldw_str_begin+7311
	.data.b	172,2
	.data.b	26
	.data.b	35
	.data.w	.Ldw_begin+11153
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7319
	.data.b	99,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 12349
	.data.w	.Ldw_str_begin+7319
	.data.b	173,2
	.data.b	30
	.data.b	35
	.data.w	.Ldw_begin+11208
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7329
	.data.b	102,105,114,79,102,102,115,101,116,49,0
	.section	.debug_info		;off: 12366
	.data.w	.Ldw_str_begin+7329
	.data.b	174,2
	.data.b	21
	.data.b	35
	.data.w	.Ldw_begin+11273
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7340
	.data.b	111,102,102,115,101,116,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 12383
	.data.w	.Ldw_str_begin+7340
	.data.b	175,2
	.data.b	36
	.data.b	35
	.data.w	.Ldw_begin+11378
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7359
	.data.b	68,115,97,100,99,95,77,97,105,110,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12401
	.data.w	.Ldw_str_begin+7359
	.data.b	176,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+12188

	.data.b	71
	.data.b	182,2
	.data.b	1
	.data.b	35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7382
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 12421
	.data.w	.Ldw_str_begin+7382
	.data.b	183,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7390
	.data.b	99,105,99,70,105,108,116,101,114,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12438
	.data.w	.Ldw_str_begin+7390
	.data.b	184,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7406
	.data.b	97,117,120,105,108,105,97,114,121,67,105,99,70,105,108,116,101,114,83,97,109,112,108,105,110,103,0
	.section	.debug_info		;off: 12455
	.data.w	.Ldw_str_begin+7406
	.data.b	185,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7433
	.data.b	112,97,114,97,108,108,101,108,0
	.section	.debug_info		;off: 12472
	.data.w	.Ldw_str_begin+7433
	.data.b	186,2
	.data.b	32
	.data.b	35
	.data.w	.Ldw_begin+11089
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7442
	.data.b	68,115,97,100,99,95,65,117,120,105,108,105,97,114,121,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12490
	.data.w	.Ldw_str_begin+7442
	.data.b	187,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+12413

	.data.b	71
	.data.b	193,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7470
	.data.b	102,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 12510
	.data.w	.Ldw_str_begin+7470
	.data.b	194,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+11508
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7484
	.data.b	68,115,97,100,99,95,70,105,102,111,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12528
	.data.w	.Ldw_str_begin+7484
	.data.b	195,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+12502

	.data.b	52
	.section	.debug_str		;off: 7501
	.data.b	0
	.section	.debug_info		;off: 12541
	.data.w	.Ldw_str_begin+7501
	.data.b	112
	.data.b	1
	.data.b	33
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7502
	.data.b	68,83,65,68,67,95,77,65,73,78,67,72,65,78,78,69,76,0
	.section	.debug_info		;off: 12551
	.data.w	.Ldw_str_begin+7502
	.data.b	113
	.data.b	5
	.data.b	33
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7520
	.data.b	68,83,65,68,67,95,65,85,88,73,76,73,65,82,89,67,72,65,78,78,69,76,0
	.section	.debug_info		;off: 12560
	.data.w	.Ldw_str_begin+7520
	.data.b	114
	.data.b	5
	.data.b	33
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7543
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,83,101,108,101,99,116,0
	.section	.debug_info		;off: 12570
	.data.w	.Ldw_str_begin+7543
	.data.b	115
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12540

	.data.b	52
	.section	.debug_str		;off: 7563
	.data.b	0
	.section	.debug_info		;off: 12582
	.data.w	.Ldw_str_begin+7563
	.data.b	126
	.data.b	1
	.data.b	33
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7564
	.data.b	68,83,65,68,67,95,78,79,69,82,82,79,82,70,76,65,71,0
	.section	.debug_info		;off: 12592
	.data.w	.Ldw_str_begin+7564
	.data.b	127
	.data.b	5
	.data.b	33
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7582
	.data.b	68,83,65,68,67,95,82,69,65,68,69,82,82,79,82,0
	.section	.debug_info		;off: 12601
	.data.w	.Ldw_str_begin+7582
	.data.b	128,1
	.data.b	5
	.data.b	33
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7598
	.data.b	68,83,65,68,67,95,87,82,73,84,69,69,82,82,79,82,0
	.section	.debug_info		;off: 12611
	.data.w	.Ldw_str_begin+7598
	.data.b	129,1
	.data.b	5
	.data.b	33
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7615
	.data.b	68,83,65,68,67,95,82,69,65,68,65,78,68,87,82,73,84,69,69,82,82,79,82,0
	.section	.debug_info		;off: 12621
	.data.w	.Ldw_str_begin+7615
	.data.b	130,1
	.data.b	5
	.data.b	33
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7639
	.data.b	68,115,97,100,99,95,70,105,102,111,69,114,114,111,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 12632
	.data.w	.Ldw_str_begin+7639
	.data.b	131,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12581

	.data.b	52
	.section	.debug_str		;off: 7661
	.data.b	0
	.section	.debug_info		;off: 12645
	.data.w	.Ldw_str_begin+7661
	.data.b	152,1
	.data.b	1
	.data.b	33
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7662
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,48,0
	.section	.debug_info		;off: 12656
	.data.w	.Ldw_str_begin+7662
	.data.b	153,1
	.data.b	5
	.data.b	33
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7682
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,49,0
	.section	.debug_info		;off: 12666
	.data.w	.Ldw_str_begin+7682
	.data.b	154,1
	.data.b	5
	.data.b	33
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7702
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,50,0
	.section	.debug_info		;off: 12676
	.data.w	.Ldw_str_begin+7702
	.data.b	155,1
	.data.b	5
	.data.b	33
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7722
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,51,0
	.section	.debug_info		;off: 12686
	.data.w	.Ldw_str_begin+7722
	.data.b	156,1
	.data.b	5
	.data.b	33
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7742
	.data.b	68,115,97,100,99,95,66,105,97,115,86,111,108,116,97,103,101,83,101,108,101,99,116,0
	.section	.debug_info		;off: 12697
	.data.w	.Ldw_str_begin+7742
	.data.b	157,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12644

	.data.b	52
	.section	.debug_str		;off: 7766
	.data.b	0
	.section	.debug_info		;off: 12710
	.data.w	.Ldw_str_begin+7766
	.data.b	162,1
	.data.b	1
	.data.b	33
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7767
	.data.b	68,83,65,68,67,95,73,78,80,85,84,80,79,82,84,95,65,0
	.section	.debug_info		;off: 12721
	.data.w	.Ldw_str_begin+7767
	.data.b	163,1
	.data.b	5
	.data.b	33
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7785
	.data.b	68,83,65,68,67,95,73,78,80,85,84,80,79,82,84,95,66,0
	.section	.debug_info		;off: 12731
	.data.w	.Ldw_str_begin+7785
	.data.b	164,1
	.data.b	5
	.data.b	33
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7803
	.data.b	68,83,65,68,67,95,73,78,80,85,84,80,79,82,84,95,67,0
	.section	.debug_info		;off: 12741
	.data.w	.Ldw_str_begin+7803
	.data.b	165,1
	.data.b	5
	.data.b	33
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7821
	.data.b	68,83,65,68,67,95,73,78,80,85,84,80,79,82,84,95,68,0
	.section	.debug_info		;off: 12751
	.data.w	.Ldw_str_begin+7821
	.data.b	166,1
	.data.b	5
	.data.b	33
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7839
	.data.b	68,115,97,100,99,95,73,110,112,117,116,80,111,114,116,83,101,108,101,99,116,0
	.section	.debug_info		;off: 12762
	.data.w	.Ldw_str_begin+7839
	.data.b	167,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12709

	.data.b	71
	.data.b	180,1
	.data.b	1
	.data.b	33
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7861
	.data.b	112,77,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12782
	.data.w	.Ldw_str_begin+7861
	.data.b	181,1
	.data.b	34
	.data.b	33
	.data.w	.Ldw_begin+756
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7878
	.data.b	112,68,101,109,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12799
	.data.w	.Ldw_str_begin+7878
	.data.b	182,1
	.data.b	36
	.data.b	33
	.data.w	.Ldw_begin+766
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7897
	.data.b	112,84,105,109,101,83,116,97,109,112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12816
	.data.w	.Ldw_str_begin+7897
	.data.b	183,1
	.data.b	34
	.data.b	33
	.data.w	.Ldw_begin+776
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7914
	.data.b	112,84,104,114,101,115,104,111,108,100,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12833
	.data.w	.Ldw_str_begin+7914
	.data.b	184,1
	.data.b	34
	.data.b	33
	.data.w	.Ldw_begin+786
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7931
	.data.b	112,77,97,105,110,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12850
	.data.w	.Ldw_str_begin+7931
	.data.b	185,1
	.data.b	35
	.data.b	33
	.data.w	.Ldw_begin+796
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7949
	.data.b	112,65,117,120,105,108,105,97,114,121,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12867
	.data.w	.Ldw_str_begin+7949
	.data.b	186,1
	.data.b	40
	.data.b	33
	.data.w	.Ldw_begin+806
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7972
	.data.b	112,77,101,97,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12884
	.data.w	.Ldw_str_begin+7972
	.data.b	187,1
	.data.b	29
	.data.b	33
	.data.w	.Ldw_begin+816
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7984
	.data.b	112,70,105,102,111,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12901
	.data.w	.Ldw_str_begin+7984
	.data.b	188,1
	.data.b	29
	.data.b	33
	.data.w	.Ldw_begin+826
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7996
	.data.b	68,115,97,100,99,95,77,111,100,117,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 12919
	.data.w	.Ldw_str_begin+7996
	.data.b	189,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12774

	.data.b	71
	.data.b	195,1
	.data.b	1
	.data.b	33
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8015
	.data.b	101,120,99,105,116,97,116,105,111,110,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12939
	.data.w	.Ldw_str_begin+8015
	.data.b	196,1
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8032
	.data.b	112,99,109,69,110,97,98,108,101,0
	.section	.debug_info		;off: 12956
	.data.w	.Ldw_str_begin+8032
	.data.b	197,1
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8042
	.data.b	99,97,114,114,105,101,114,87,97,118,101,0
	.section	.debug_info		;off: 12973
	.data.w	.Ldw_str_begin+8042
	.data.b	198,1
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8054
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 12990
	.data.w	.Ldw_str_begin+8054
	.data.b	199,1
	.data.b	20
	.data.b	33
	.data.w	.Ldw_begin+11443
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8059
	.data.b	68,115,97,100,99,95,67,97,114,114,105,101,114,87,97,118,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 13008
	.data.w	.Ldw_str_begin+8059
	.data.b	200,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+12931

	.data.b	71
	.data.b	215,1
	.data.b	1
	.data.b	33
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8083
	.data.b	100,99,79,102,102,115,101,116,0
	.section	.debug_info		;off: 13028
	.data.w	.Ldw_str_begin+8083
	.data.b	216,1
	.data.b	12
	.data.b	33
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8092
	.data.b	103,99,79,102,102,115,101,116,0
	.section	.debug_info		;off: 13045
	.data.w	.Ldw_str_begin+8092
	.data.b	217,1
	.data.b	12
	.data.b	33
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8101
	.data.b	68,115,97,100,99,95,67,111,109,112,101,110,115,97,116,105,111,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 13063
	.data.w	.Ldw_str_begin+8101
	.data.b	218,1
	.data.b	3
	.data.b	33
	.data.w	.Ldw_begin+13020

	.data.b	45
	.section	.debug_str		;off: 8126
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 13076
	.data.w	.Ldw_str_begin+8126
	.data.b	49
	.data.b	15
	.data.b	31
	.data.w	.Ldw_begin+1489

	.data.b	45
	.section	.debug_str		;off: 8144
	.data.b	68,115,97,100,99,95,82,101,115,117,108,116,84,121,112,101,0
	.section	.debug_info		;off: 13088
	.data.w	.Ldw_str_begin+8144
	.data.b	51
	.data.b	16
	.data.b	31
	.data.w	.Ldw_begin+1501

	.data.b	45
	.section	.debug_str		;off: 8161
	.data.b	68,115,97,100,99,95,84,105,109,101,115,116,97,109,112,84,121,112,101,0
	.section	.debug_info		;off: 13100
	.data.w	.Ldw_str_begin+8161
	.data.b	53
	.data.b	16
	.data.b	31
	.data.w	.Ldw_begin+1513

	.data.b	45
	.section	.debug_str		;off: 8181
	.data.b	68,115,97,100,99,95,78,117,109,83,97,109,112,108,101,84,121,112,101,0
	.section	.debug_info		;off: 13112
	.data.w	.Ldw_str_begin+8181
	.data.b	55
	.data.b	15
	.data.b	31
	.data.w	.Ldw_begin+1489

	.data.b	45
	.section	.debug_str		;off: 8201
	.data.b	68,115,97,100,99,95,72,87,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 13124
	.data.w	.Ldw_str_begin+8201
	.data.b	57
	.data.b	27
	.data.b	31
	.data.w	.Ldw_begin+13075

	.data.b	52
	.section	.debug_str		;off: 8218
	.data.b	0
	.section	.debug_info		;off: 13136
	.data.w	.Ldw_str_begin+8218
	.data.b	69
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8219
	.data.b	68,83,65,68,67,95,85,78,73,78,73,84,73,65,76,73,90,69,0
	.section	.debug_info		;off: 13146
	.data.w	.Ldw_str_begin+8219
	.data.b	70
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8238
	.data.b	68,83,65,68,67,95,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 13155
	.data.w	.Ldw_str_begin+8238
	.data.b	71
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8256
	.data.b	68,115,97,100,99,95,73,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 13165
	.data.w	.Ldw_str_begin+8256
	.data.b	72
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13135

	.data.b	52
	.section	.debug_str		;off: 8271
	.data.b	0
	.section	.debug_info		;off: 13177
	.data.w	.Ldw_str_begin+8271
	.data.b	77
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8272
	.data.b	68,83,65,68,67,95,73,68,76,69,0
	.section	.debug_info		;off: 13187
	.data.w	.Ldw_str_begin+8272
	.data.b	80
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8283
	.data.b	68,83,65,68,67,95,66,85,83,89,0
	.section	.debug_info		;off: 13196
	.data.w	.Ldw_str_begin+8283
	.data.b	83
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8294
	.data.b	68,83,65,68,67,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 13205
	.data.w	.Ldw_str_begin+8294
	.data.b	86
	.data.b	5
	.data.b	31
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8310
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 13214
	.data.w	.Ldw_str_begin+8310
	.data.b	90
	.data.b	5
	.data.b	31
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8333
	.data.b	68,115,97,100,99,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 13224
	.data.w	.Ldw_str_begin+8333
	.data.b	91
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13176

	.data.b	52
	.section	.debug_str		;off: 8350
	.data.b	0
	.section	.debug_info		;off: 13236
	.data.w	.Ldw_str_begin+8350
	.data.b	95
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8351
	.data.b	68,83,65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,73,78,71,76,69,0
	.section	.debug_info		;off: 13246
	.data.w	.Ldw_str_begin+8351
	.data.b	97
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8376
	.data.b	68,83,65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,84,82,69,65,77,73,78,71,0
	.section	.debug_info		;off: 13255
	.data.w	.Ldw_str_begin+8376
	.data.b	99
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8404
	.data.b	68,115,97,100,99,95,65,99,99,101,115,115,84,121,112,101,0
	.section	.debug_info		;off: 13265
	.data.w	.Ldw_str_begin+8404
	.data.b	100
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13235

	.data.b	52
	.section	.debug_str		;off: 8421
	.data.b	0
	.section	.debug_info		;off: 13277
	.data.w	.Ldw_str_begin+8421
	.data.b	104
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8422
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,76,69,65,78,69,82,0
	.section	.debug_info		;off: 13287
	.data.w	.Ldw_str_begin+8422
	.data.b	107
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8449
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,67,73,82,67,85,76,65,82,0
	.section	.debug_info		;off: 13296
	.data.w	.Ldw_str_begin+8449
	.data.b	110
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8478
	.data.b	68,115,97,100,99,95,83,116,114,101,97,109,66,117,102,84,121,112,101,0
	.section	.debug_info		;off: 13306
	.data.w	.Ldw_str_begin+8478
	.data.b	111
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13276

	.data.b	52
	.section	.debug_str		;off: 8498
	.data.b	0
	.section	.debug_info		;off: 13318
	.data.w	.Ldw_str_begin+8498
	.data.b	115
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8499
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,65,66,79,86,69,95,85,80,80,69,82,95,76,73,77,73,84,0
	.section	.debug_info		;off: 13328
	.data.w	.Ldw_str_begin+8499
	.data.b	117
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8530
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,66,69,76,79,87,95,76,79,87,69,82,95,76,73,77,73,84,0
	.section	.debug_info		;off: 13337
	.data.w	.Ldw_str_begin+8530
	.data.b	119
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8561
	.data.b	68,115,97,100,99,95,76,105,109,105,116,67,104,101,99,107,105,110,103,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 13347
	.data.w	.Ldw_str_begin+8561
	.data.b	120
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13317

	.data.b	52
	.section	.debug_str		;off: 8590
	.data.b	0
	.section	.debug_info		;off: 13359
	.data.w	.Ldw_str_begin+8590
	.data.b	124
	.data.b	1
	.data.b	31
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8591
	.data.b	68,83,65,68,67,95,67,79,78,86,95,67,72,65,78,78,69,76,95,77,65,73,78,0
	.section	.debug_info		;off: 13369
	.data.w	.Ldw_str_begin+8591
	.data.b	126
	.data.b	5
	.data.b	31
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8615
	.data.b	68,83,65,68,67,95,67,79,78,86,95,67,72,65,78,78,69,76,95,65,85,88,0
	.section	.debug_info		;off: 13378
	.data.w	.Ldw_str_begin+8615
	.data.b	128,1
	.data.b	5
	.data.b	31
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8638
	.data.b	68,115,97,100,99,95,67,111,110,118,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 13389
	.data.w	.Ldw_str_begin+8638
	.data.b	129,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13358

	.data.b	71
	.data.b	139,1
	.data.b	1
	.data.b	31
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8660
	.data.b	67,111,114,101,67,104,97,110,110,101,108,73,100,120,0
	.section	.debug_info		;off: 13409
	.data.w	.Ldw_str_begin+8660
	.data.b	141,1
	.data.b	40
	.data.b	31
	.data.w	.Ldw_begin+13075
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8675
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 13426
	.data.w	.Ldw_str_begin+8675
	.data.b	143,1
	.data.b	40
	.data.b	31
	.data.w	.Ldw_begin+13123
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8684
	.data.b	67,104,97,110,110,101,108,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 13443
	.data.w	.Ldw_str_begin+8684
	.data.b	145,1
	.data.b	40
	.data.b	31
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8701
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,67,111,114,101,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 13461
	.data.w	.Ldw_str_begin+8701
	.data.b	146,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13401

	.data.b	71
	.data.b	150,1
	.data.b	1
	.data.b	31
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8726
	.data.b	67,104,78,111,116,105,102,83,116,97,116,117,115,0
	.section	.debug_info		;off: 13481
	.data.w	.Ldw_str_begin+8726
	.data.b	153,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8740
	.data.b	73,110,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 13498
	.data.w	.Ldw_str_begin+8740
	.data.b	156,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1513
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8750
	.data.b	84,105,109,101,115,116,97,109,112,0
	.section	.debug_info		;off: 13515
	.data.w	.Ldw_str_begin+8750
	.data.b	158,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13099
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8760
	.data.b	67,104,86,97,108,105,100,82,115,108,116,78,117,109,0
	.section	.debug_info		;off: 13532
	.data.w	.Ldw_str_begin+8760
	.data.b	160,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13111
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8775
	.data.b	67,104,82,115,108,116,66,117,102,80,116,114,0
	.section	.debug_info		;off: 13549
	.data.w	.Ldw_str_begin+8775
	.data.b	162,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+547
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8788
	.data.b	70,105,102,111,69,114,114,70,108,97,103,0
	.section	.debug_info		;off: 13566
	.data.w	.Ldw_str_begin+8788
	.data.b	164,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+12631
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8800
	.data.b	67,104,65,117,120,83,116,97,116,117,115,0
	.section	.debug_info		;off: 13583
	.data.w	.Ldw_str_begin+8800
	.data.b	167,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13223
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8812
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 13600
	.data.w	.Ldw_str_begin+8812
	.data.b	170,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13223
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8821
	.data.b	68,115,97,100,99,95,71,108,111,98,97,108,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 13618
	.data.w	.Ldw_str_begin+8821
	.data.b	171,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13473

	.data.b	71
	.data.b	177,1
	.data.b	1
	.data.b	31
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8842
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 13638
	.data.w	.Ldw_str_begin+8842
	.data.b	179,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13123
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8851
	.data.b	76,103,99,67,104,73,100,0
	.section	.debug_info		;off: 13655
	.data.w	.Ldw_str_begin+8851
	.data.b	181,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13075
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8859
	.data.b	73,115,77,100,108,68,105,116,104,101,114,105,110,103,69,110,0
	.section	.debug_info		;off: 13672
	.data.w	.Ldw_str_begin+8859
	.data.b	183,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8876
	.data.b	73,115,67,111,109,109,111,110,77,111,100,101,86,111,108,116,69,110,0
	.section	.debug_info		;off: 13689
	.data.w	.Ldw_str_begin+8876
	.data.b	185,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8895
	.data.b	67,111,109,109,111,110,77,111,100,101,86,111,108,116,76,101,118,101,108,0
	.section	.debug_info		;off: 13706
	.data.w	.Ldw_str_begin+8895
	.data.b	187,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+12696
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8915
	.data.b	73,115,65,117,120,67,104,82,115,108,116,65,99,113,69,110,0
	.section	.debug_info		;off: 13723
	.data.w	.Ldw_str_begin+8915
	.data.b	190,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8932
	.data.b	84,105,109,101,115,116,97,109,112,69,110,0
	.section	.debug_info		;off: 13740
	.data.w	.Ldw_str_begin+8932
	.data.b	194,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1477
	.data.b	2,35
	.data.b	9
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8944
	.data.b	82,115,108,116,72,108,100,77,116,104,100,0
	.section	.debug_info		;off: 13757
	.data.w	.Ldw_str_begin+8944
	.data.b	197,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	10
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8956
	.data.b	78,117,109,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 13774
	.data.w	.Ldw_str_begin+8956
	.data.b	199,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13111
	.data.b	2,35
	.data.b	11
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8967
	.data.b	82,115,108,116,65,99,99,101,115,115,77,111,100,0
	.section	.debug_info		;off: 13791
	.data.w	.Ldw_str_begin+8967
	.data.b	201,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13264
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8981
	.data.b	83,116,114,101,97,109,66,117,102,77,111,100,0
	.section	.debug_info		;off: 13808
	.data.w	.Ldw_str_begin+8981
	.data.b	203,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+13305
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8994
	.data.b	78,101,119,82,115,108,116,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 13825
	.data.w	.Ldw_str_begin+8994
	.data.b	206,1
	.data.b	12
	.data.b	31
	.data.w	.Ldw_begin+840
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9014
	.data.b	66,117,102,70,117,108,108,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 13842
	.data.w	.Ldw_str_begin+9014
	.data.b	208,1
	.data.b	12
	.data.b	31
	.data.w	.Ldw_begin+848
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9034
	.data.b	76,105,109,105,116,67,104,107,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 13859
	.data.w	.Ldw_str_begin+9034
	.data.b	210,1
	.data.b	12
	.data.b	31
	.data.w	.Ldw_begin+868
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9055
	.data.b	76,105,109,105,116,67,104,101,99,107,69,118,116,66,105,116,115,0
	.section	.debug_info		;off: 13876
	.data.w	.Ldw_str_begin+9055
	.data.b	214,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9073
	.data.b	67,97,108,105,98,67,111,109,112,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 13893
	.data.w	.Ldw_str_begin+9073
	.data.b	217,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+878
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9092
	.data.b	72,119,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13910
	.data.w	.Ldw_str_begin+9092
	.data.b	219,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+888
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9101
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 13928
	.data.w	.Ldw_str_begin+9101
	.data.b	220,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13630

	.data.b	71
	.data.b	226,1
	.data.b	1
	.data.b	31
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9125
	.data.b	77,97,120,67,111,114,101,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 13948
	.data.w	.Ldw_str_begin+9125
	.data.b	228,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9140
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 13965
	.data.w	.Ldw_str_begin+9140
	.data.b	230,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+312
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9157
	.data.b	68,115,97,100,99,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 13983
	.data.w	.Ldw_str_begin+9157
	.data.b	231,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13940

	.data.b	71
	.data.b	237,1
	.data.b	1
	.data.b	31
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9178
	.data.b	72,87,85,110,105,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 14003
	.data.w	.Ldw_str_begin+9178
	.data.b	239,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1525
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9191
	.data.b	65,117,120,70,108,116,114,72,119,85,110,105,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 14020
	.data.w	.Ldw_str_begin+9191
	.data.b	242,1
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1525
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9211
	.data.b	67,97,114,114,105,101,114,67,102,103,80,116,114,0
	.section	.debug_info		;off: 14037
	.data.w	.Ldw_str_begin+9211
	.data.b	245,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+898
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9225
	.data.b	68,115,97,100,99,95,71,108,111,98,97,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 14055
	.data.w	.Ldw_str_begin+9225
	.data.b	246,1
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+13995

	.data.b	71
	.data.b	251,1
	.data.b	1
	.data.b	31
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9248
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 14075
	.data.w	.Ldw_str_begin+9248
	.data.b	253,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+913
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9262
	.data.b	71,108,111,98,97,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 14092
	.data.w	.Ldw_str_begin+9262
	.data.b	255,1
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+934
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9275
	.data.b	67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 14109
	.data.w	.Ldw_str_begin+9275
	.data.b	129,2
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+944
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9289
	.data.b	72,119,85,110,105,116,84,111,67,104,97,110,110,101,108,73,100,80,116,114,0
	.section	.debug_info		;off: 14126
	.data.w	.Ldw_str_begin+9289
	.data.b	131,2
	.data.b	43
	.data.b	31
	.data.w	.Ldw_begin+954
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9310
	.data.b	68,115,97,100,99,49,73,110,112,117,116,80,105,110,0
	.section	.debug_info		;off: 14143
	.data.w	.Ldw_str_begin+9310
	.data.b	133,2
	.data.b	42
	.data.b	31
	.data.w	.Ldw_begin+1489
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9325
	.data.b	68,115,97,100,99,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 14161
	.data.w	.Ldw_str_begin+9325
	.data.b	135,2
	.data.b	3
	.data.b	31
	.data.w	.Ldw_begin+14067

	.data.b	6
	.section	.debug_str		;off: 9342
	.data.b	68,115,97,100,99,95,73,110,105,116,70,108,103,67,111,114,101,48,0
	.section	.debug_info		;off: 14174
	.data.w	.Ldw_str_begin+9342
	.data.b	233,1
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13164
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_InitFlgCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

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

	.section	.debug_info		;off: 14194
	.data.b	6
	.section	.debug_str		;off: 9361
	.data.b	68,115,97,100,99,95,68,97,116,97,67,111,114,101,48,0
	.section	.debug_info		;off: 14195
	.data.w	.Ldw_str_begin+9361
	.data.b	247,1
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+959
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	6
	.section	.debug_str		;off: 9377
	.data.b	68,115,97,100,99,95,67,97,114,114,105,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14216
	.data.w	.Ldw_str_begin+9377
	.data.b	202,2
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_CarrierStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	6
	.section	.debug_str		;off: 9397
	.data.b	68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 14237
	.data.w	.Ldw_str_begin+9397
	.data.b	206,2
	.data.b	64
	.data.b	1
	.data.w	.Ldw_begin+233
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	6
	.section	.debug_str		;off: 9413
	.data.b	68,115,97,100,99,95,67,111,114,101,73,110,105,116,83,116,97,116,117,115,83,101,116,80,116,114,0
	.section	.debug_info		;off: 14258
	.data.w	.Ldw_str_begin+9413
	.data.b	223,2
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+985
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_CoreInitStatusSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	6
	.section	.debug_str		;off: 9440
	.data.b	68,115,97,100,99,95,67,111,114,101,68,97,116,97,83,101,116,80,116,114,0
	.section	.debug_info		;off: 14279
	.data.w	.Ldw_str_begin+9440
	.data.b	128,3
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+1001
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_CoreDataSetPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	6
	.section	.debug_str		;off: 9461
	.data.b	68,115,97,100,99,95,66,97,115,101,65,100,100,114,115,0
	.section	.debug_info		;off: 14300
	.data.w	.Ldw_str_begin+9461
	.data.b	163,3
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+1017
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.

	.data.b	27
	.section	.debug_str		;off: 9477
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 14321
	.data.w	.Ldw_str_begin+9477
	.data.b	63
	.data.b	31
	.data.b	11
	.data.w	.Ldw_begin+1716
	.data.b	0
	.data.b	3
	.data.b	0
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

	.section	.debug_info		;off: 14338
	.data.b	37

	.section	.debug_abbrev		;off: 269
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 14339
	.data.b	8
	.section	.debug_str		;off: 9497
	.data.b	105,100,0
	.section	.debug_info		;off: 14340
	.data.w	.Ldw_str_begin+9497
	.data.b	65
	.data.b	17
	.data.b	11
	.data.w	.Ldw_begin+1716
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 274
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

	.section	.debug_info		;off: 14353
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9500
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 14356
	.data.w	.Ldw_str_begin+9500
	.data.b	131,2
	.data.b	48
	.data.b	2
	.data.w	.Ldw_begin+1549
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9513
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 14376
	.data.w	.Ldw_str_begin+9513
	.data.b	133,2
	.data.b	38
	.data.b	2
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 293
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

	.section	.debug_info		;off: 14390
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9530
	.data.b	68,115,97,100,99,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 14392
	.data.w	.Ldw_str_begin+9530
	.data.b	236,2
	.data.b	27
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 9560
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 14411
	.data.w	.Ldw_str_begin+9560
	.data.b	236,2
	.data.b	65
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	0

	.section	.debug_abbrev		;off: 318
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

	.section	.debug_info		;off: 14424
	.data.b	20
	.section	.debug_str		;off: 9566
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 14425
	.data.w	.Ldw_str_begin+9566
	.data.b	236,2
	.data.b	79
	.data.b	35
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 9573
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 14439
	.data.w	.Ldw_str_begin+9573
	.data.b	236,2
	.data.b	94
	.data.b	35
	.data.w	.Ldw_begin+1525
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 9579
	.data.b	114,101,116,0
	.section	.debug_info		;off: 14454
	.data.w	.Ldw_str_begin+9579
	.data.b	238,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9583
	.data.b	68,115,97,100,99,95,72,97,108,95,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 14471
	.data.w	.Ldw_str_begin+9583
	.data.b	252,1
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9604
	.data.b	68,115,97,100,99,95,72,97,108,95,67,111,110,102,105,103,67,97,114,114,105,101,114,87,97,118,101,0
	.section	.debug_info		;off: 14491
	.data.w	.Ldw_str_begin+9604
	.data.b	142,2
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9632
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 14511
	.data.w	.Ldw_str_begin+9632
	.data.b	195,2
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9658
	.data.b	68,115,97,100,99,95,72,97,108,95,68,105,115,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 14531
	.data.w	.Ldw_str_begin+9658
	.data.b	228,2
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9685
	.data.b	68,115,97,100,99,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14551
	.data.w	.Ldw_str_begin+9685
	.data.b	253,2
	.data.b	15
	.data.b	33
	.data.w	.Ldw_begin+1525
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9714
	.data.b	68,115,97,100,99,95,72,97,108,95,67,108,101,97,114,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14571
	.data.w	.Ldw_str_begin+9714
	.data.b	151,3
	.data.b	13
	.data.b	33
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9745
	.data.b	68,115,97,100,99,95,72,97,108,95,71,101,116,67,111,110,118,101,114,115,105,111,110,82,101,115,117,108,116,0
	.section	.debug_info		;off: 14587
	.data.w	.Ldw_str_begin+9745
	.data.b	168,3
	.data.b	15
	.data.b	33
	.data.w	.Ldw_begin+1513
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9775
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,77,111,100,117,108,101,83,121,110,99,0
	.section	.debug_info		;off: 14607
	.data.w	.Ldw_str_begin+9775
	.data.b	192,3
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9802
	.data.b	68,115,97,100,99,95,72,97,108,95,68,101,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 14627
	.data.w	.Ldw_str_begin+9802
	.data.b	245,3
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9825
	.data.b	68,115,97,100,99,95,72,97,108,95,67,108,101,97,114,70,105,102,111,0
	.section	.debug_info		;off: 14647
	.data.w	.Ldw_str_begin+9825
	.data.b	136,4
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9845
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,77,97,105,110,67,104,97,110,110,101,108,83,121,110,99,0
	.section	.debug_info		;off: 14667
	.data.w	.Ldw_str_begin+9845
	.data.b	174,4
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9877
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,65,117,120,67,104,97,110,110,101,108,83,121,110,99,0
	.section	.debug_info		;off: 14687
	.data.w	.Ldw_str_begin+9877
	.data.b	229,4
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9908
	.data.b	68,115,97,100,99,95,72,97,108,95,67,108,111,115,101,76,111,111,112,0
	.section	.debug_info		;off: 14707
	.data.w	.Ldw_str_begin+9908
	.data.b	137,5
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9928
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,68,105,116,104,101,114,105,110,103,0
	.section	.debug_info		;off: 14727
	.data.w	.Ldw_str_begin+9928
	.data.b	158,5
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9954
	.data.b	68,115,97,100,99,95,72,97,108,95,71,101,116,84,114,105,103,103,101,114,84,105,109,101,83,116,97,109,112,0
	.section	.debug_info		;off: 14747
	.data.w	.Ldw_str_begin+9954
	.data.b	175,5
	.data.b	15
	.data.b	33
	.data.w	.Ldw_begin+1513
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9984
	.data.b	68,115,97,100,99,95,72,97,108,95,67,111,110,102,105,103,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 14767
	.data.w	.Ldw_str_begin+9984
	.data.b	247,5
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10013
	.data.b	68,115,97,100,99,95,72,97,108,95,67,111,110,102,105,103,66,105,97,115,86,111,108,116,97,103,101,0
	.section	.debug_info		;off: 14787
	.data.w	.Ldw_str_begin+10013
	.data.b	140,6
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10041
	.data.b	68,115,97,100,99,95,72,97,108,95,67,111,110,102,105,103,68,115,97,100,99,49,73,110,80,111,114,116,0
	.section	.debug_info		;off: 14807
	.data.w	.Ldw_str_begin+10041
	.data.b	160,6
	.data.b	16
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10070
	.data.b	68,115,97,100,99,95,72,97,108,95,83,101,116,83,121,110,99,77,111,100,101,0
	.section	.debug_info		;off: 14827
	.data.w	.Ldw_str_begin+10070
	.data.b	219,7
	.data.b	27
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10092
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 14846
	.data.w	.Ldw_str_begin+10092
	.data.b	219,7
	.data.b	57
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 10097
	.data.b	114,101,116,0
	.section	.debug_info		;off: 14861
	.data.w	.Ldw_str_begin+10097
	.data.b	221,7
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10101
	.data.b	68,115,97,100,99,95,72,97,108,95,83,101,116,73,110,116,101,103,114,97,116,111,114,83,116,97,116,101,0
	.section	.debug_info		;off: 14878
	.data.w	.Ldw_str_begin+10101
	.data.b	231,7
	.data.b	27
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10130
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 14897
	.data.w	.Ldw_str_begin+10130
	.data.b	231,7
	.data.b	64
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 10136
	.data.b	114,101,116,0
	.section	.debug_info		;off: 14912
	.data.w	.Ldw_str_begin+10136
	.data.b	233,7
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10140
	.data.b	68,115,97,100,99,95,72,97,108,95,71,101,116,84,105,109,101,83,116,97,109,112,0
	.section	.debug_info		;off: 14929
	.data.w	.Ldw_str_begin+10140
	.data.b	243,7
	.data.b	26
	.data.b	33
	.data.w	.Ldw_begin+1513
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10163
	.data.b	112,68,115,97,100,99,0
	.section	.debug_info		;off: 14948
	.data.w	.Ldw_str_begin+10163
	.data.b	243,7
	.data.b	75
	.data.b	33
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10170
	.data.b	68,115,97,100,99,95,72,97,108,95,69,110,97,98,108,101,67,97,114,114,105,101,114,87,97,118,101,0
	.section	.debug_info		;off: 14965
	.data.w	.Ldw_str_begin+10170
	.data.b	128,8
	.data.b	27
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10198
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 14984
	.data.w	.Ldw_str_begin+10198
	.data.b	128,8
	.data.b	63
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10205
	.data.b	68,115,97,100,99,95,72,97,108,95,71,101,116,70,105,102,111,69,114,114,111,114,70,108,97,103,0
	.section	.debug_info		;off: 15001
	.data.w	.Ldw_str_begin+10205
	.data.b	137,8
	.data.b	41
	.data.b	33
	.data.w	.Ldw_begin+12631
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10232
	.data.b	112,68,115,97,100,99,0
	.section	.debug_info		;off: 15020
	.data.w	.Ldw_str_begin+10232
	.data.b	137,8
	.data.b	94
	.data.b	33
	.data.w	.Ldw_begin+136
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 10239
	.data.b	101,114,114,70,108,97,103,0
	.section	.debug_info		;off: 15035
	.data.w	.Ldw_str_begin+10239
	.data.b	139,8
	.data.b	11
	.data.b	33
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10247
	.data.b	116,101,109,112,49,0
	.section	.debug_info		;off: 15050
	.data.w	.Ldw_str_begin+10247
	.data.b	140,8
	.data.b	11
	.data.b	33
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10253
	.data.b	116,101,109,112,50,0
	.section	.debug_info		;off: 15065
	.data.w	.Ldw_str_begin+10253
	.data.b	141,8
	.data.b	11
	.data.b	33
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10259
	.data.b	68,115,97,100,99,95,72,97,108,95,66,121,112,97,115,115,68,99,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 15082
	.data.w	.Ldw_str_begin+10259
	.data.b	172,8
	.data.b	27
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10290
	.data.b	112,68,115,97,100,99,0
	.section	.debug_info		;off: 15101
	.data.w	.Ldw_str_begin+10290
	.data.b	172,8
	.data.b	78
	.data.b	33
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 10297
	.data.b	98,121,112,97,115,115,0
	.section	.debug_info		;off: 15115
	.data.w	.Ldw_str_begin+10297
	.data.b	172,8
	.data.b	95
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 10304
	.data.b	114,101,116,0
	.section	.debug_info		;off: 15130
	.data.w	.Ldw_str_begin+10304
	.data.b	174,8
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10308
	.data.b	68,115,97,100,99,95,72,97,108,95,66,121,112,97,115,115,71,97,105,110,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 15147
	.data.w	.Ldw_str_begin+10308
	.data.b	190,8
	.data.b	27
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 10341
	.data.b	112,68,115,97,100,99,0
	.section	.debug_info		;off: 15166
	.data.w	.Ldw_str_begin+10341
	.data.b	190,8
	.data.b	80
	.data.b	33
	.data.w	.Ldw_begin+185
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 10348
	.data.b	98,121,112,97,115,115,0
	.section	.debug_info		;off: 15180
	.data.w	.Ldw_str_begin+10348
	.data.b	190,8
	.data.b	97
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 10355
	.data.b	114,101,116,0
	.section	.debug_info		;off: 15195
	.data.w	.Ldw_str_begin+10355
	.data.b	192,8
	.data.b	13
	.data.b	33
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10359
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,83,116,97,114,116,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 15212
	.data.w	.Ldw_str_begin+10359
	.data.b	33
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10392
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,83,116,97,114,116,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 15227
	.data.w	.Ldw_str_begin+10392
	.data.b	34
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10424
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,83,116,111,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 15242
	.data.w	.Ldw_str_begin+10424
	.data.b	36
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10456
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,83,116,111,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 15257
	.data.w	.Ldw_str_begin+10456
	.data.b	37
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10487
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 15272
	.data.w	.Ldw_str_begin+10487
	.data.b	39
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10525
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 15287
	.data.w	.Ldw_str_begin+10525
	.data.b	40
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10562
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15302
	.data.w	.Ldw_str_begin+10562
	.data.b	42
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10596
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15317
	.data.w	.Ldw_str_begin+10596
	.data.b	43
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10629
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,82,101,115,117,108,116,72,97,110,100,108,105,110,103,0
	.section	.debug_info		;off: 15332
	.data.w	.Ldw_str_begin+10629
	.data.b	45
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10661
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,82,101,115,117,108,116,72,97,110,100,108,105,110,103,0
	.section	.debug_info		;off: 15347
	.data.w	.Ldw_str_begin+10661
	.data.b	46
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10692
	.data.b	83,99,104,77,95,69,110,116,101,114,95,68,115,97,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 15362
	.data.w	.Ldw_str_begin+10692
	.data.b	48
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10716
	.data.b	83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 15377
	.data.w	.Ldw_str_begin+10716
	.data.b	49
	.data.b	13
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10739
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 15392
	.data.w	.Ldw_str_begin+10739
	.data.b	105
	.data.b	39
	.data.b	41
	.data.w	.Ldw_begin+1549
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 10755
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 15411
	.data.w	.Ldw_str_begin+10755
	.data.b	113
	.data.b	39
	.data.b	41
	.data.w	.Ldw_begin+1549
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 10778
	.data.b	68,115,97,100,99,95,67,104,101,99,107,73,110,105,116,80,97,114,97,109,0
	.section	.debug_info		;off: 15430
	.data.w	.Ldw_str_begin+10778
	.data.b	163,5
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckInitParam
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

	.section	.debug_abbrev		;off: 335
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
	.data.w	Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckInitParam-Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1719
	.data.b	0,5,2
	.data.w	Dsadc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	166,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	12
	.data.b	27
	.data.b	59
	.data.b	75
	.data.b	12
	.data.b	91
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	13
	.data.b	43
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
	.section	.debug_info		;off: 15465
	.data.b	22
	.section	.debug_str		;off: 10799
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 15466
	.data.w	.Ldw_str_begin+10799
	.data.b	165,5
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+238
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

	.section	.debug_abbrev		;off: 383
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

	.section	.debug_info		;off: 15483
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 402
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 15492
	.data.b	7
	.section	.debug_str		;off: 10809
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 15493
	.data.w	.Ldw_str_begin+10809
	.data.b	168,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 411
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

	.section	.debug_info		;off: 15511
	.data.b	7
	.section	.debug_str		;off: 10816
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15512
	.data.w	.Ldw_str_begin+10816
	.data.b	169,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15530
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 10823
	.data.b	68,115,97,100,99,95,67,104,101,99,107,73,110,105,116,0
	.section	.debug_info		;off: 15533
	.data.w	.Ldw_str_begin+10823
	.data.b	230,5
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckInit
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
	.data.w	Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckInit-Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1777
	.data.b	0,5,2
	.data.w	Dsadc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	234,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	107
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
	.section	.debug_info		;off: 15568
	.data.b	22
	.section	.debug_str		;off: 10839
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15569
	.data.w	.Ldw_str_begin+10839
	.data.b	232,5
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15586
	.data.b	22
	.section	.debug_str		;off: 10849
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15587
	.data.w	.Ldw_str_begin+10849
	.data.b	233,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15604
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 10856
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 15614
	.data.w	.Ldw_str_begin+10856
	.data.b	236,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15632
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 10863
	.data.b	68,115,97,100,99,95,67,104,101,99,107,68,101,73,110,105,116,0
	.section	.debug_info		;off: 15635
	.data.w	.Ldw_str_begin+10863
	.data.b	160,6
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckDeInit
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
	.data.w	Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckDeInit-Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1831
	.data.b	0,5,2
	.data.w	Dsadc_CheckDeInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	163,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	59
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	75
	.data.b	59
	.data.b	12
	.data.b	75
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	24
	.data.b	1
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
	.section	.debug_info		;off: 15670
	.data.b	22
	.section	.debug_str		;off: 10881
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15671
	.data.w	.Ldw_str_begin+10881
	.data.b	162,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
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

	.section	.debug_info		;off: 15688
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 10888
	.data.b	69,114,114,0
	.section	.debug_info		;off: 15698
	.data.w	.Ldw_str_begin+10888
	.data.b	165,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+144
	.section	.debug_loc		;off: 144
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15716
	.data.b	8
	.section	.debug_str		;off: 10892
	.data.b	67,111,114,101,67,110,116,0
	.section	.debug_info		;off: 15717
	.data.w	.Ldw_str_begin+10892
	.data.b	166,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 10900
	.data.b	68,115,97,100,99,95,67,104,101,99,107,77,117,108,116,105,99,111,114,101,65,108,108,111,99,97,116,101,69,114,114,111,114,0
	.section	.debug_info		;off: 15734
	.data.w	.Ldw_str_begin+10900
	.data.b	218,6
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckMulticoreAllocateError
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
	.data.w	Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckMulticoreAllocateError-Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1889
	.data.b	0,5,2
	.data.w	Dsadc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	222,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	2
	.data.b	20
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	11
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	13
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	107
	.data.b	12
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
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 15769
	.data.b	22
	.section	.debug_str		;off: 10934
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15770
	.data.w	.Ldw_str_begin+10934
	.data.b	220,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.w	.Ldw_loc_begin+163
	.section	.debug_loc		;off: 163
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15787
	.data.b	22
	.section	.debug_str		;off: 10944
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 15788
	.data.w	.Ldw_str_begin+10944
	.data.b	221,6
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+182
	.section	.debug_loc		;off: 182
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	81
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15805
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 10954
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 15815
	.data.w	.Ldw_str_begin+10954
	.data.b	224,6
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+212
	.section	.debug_loc		;off: 212
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15833
	.data.b	8
	.section	.debug_str		;off: 10961
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15834
	.data.w	.Ldw_str_begin+10961
	.data.b	225,6
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10968
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 15849
	.data.w	.Ldw_str_begin+10968
	.data.b	226,6
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+231
	.section	.debug_loc		;off: 231
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15867
	.data.b	8
	.section	.debug_str		;off: 10978
	.data.b	67,102,103,80,116,114,0
	.section	.debug_info		;off: 15868
	.data.w	.Ldw_str_begin+10978
	.data.b	227,6
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 10985
	.data.b	68,115,97,100,99,95,67,104,101,99,107,65,108,108,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15885
	.data.w	.Ldw_str_begin+10985
	.data.b	169,7
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckAllChannelStatus
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_CheckAllChannelStatus-Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1973
	.data.b	0,5,2
	.data.w	Dsadc_CheckAllChannelStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	172,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	13
	.data.b	59
	.data.b	11
	.data.b	29
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	107
	.data.b	11
	.data.b	29
	.data.b	76
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 15920
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 11013
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 15930
	.data.w	.Ldw_str_begin+11013
	.data.b	174,7
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+250
	.section	.debug_loc		;off: 250
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15948
	.data.b	7
	.section	.debug_str		;off: 11020
	.data.b	67,111,114,101,67,104,100,120,0
	.section	.debug_info		;off: 15949
	.data.w	.Ldw_str_begin+11020
	.data.b	175,7
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1489
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+269
	.section	.debug_loc		;off: 269
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15967
	.data.b	8
	.section	.debug_str		;off: 11029
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15968
	.data.w	.Ldw_str_begin+11029
	.data.b	176,7
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11038
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15983
	.data.w	.Ldw_str_begin+11038
	.data.b	177,7
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+288
	.section	.debug_loc		;off: 288
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16001
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11045
	.data.b	68,115,97,100,99,95,68,101,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16004
	.data.w	.Ldw_str_begin+11045
	.data.b	251,7
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.w	Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_DeInitChannel
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_DeInitChannel-Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2064
	.data.b	0,5,2
	.data.w	Dsadc_DeInitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	254,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16039
	.data.b	22
	.section	.debug_str		;off: 11065
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 16040
	.data.w	.Ldw_str_begin+11065
	.data.b	253,7
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+307
	.section	.debug_loc		;off: 307
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

	.section	.debug_info		;off: 16057
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 11074
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 16067
	.data.w	.Ldw_str_begin+11074
	.data.b	128,8
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+337
	.section	.debug_loc		;off: 337
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16085
	.data.b	8
	.section	.debug_str		;off: 11084
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16086
	.data.w	.Ldw_str_begin+11084
	.data.b	129,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11095
	.data.b	68,115,97,100,99,95,83,101,116,73,110,116,101,114,114,117,112,116,69,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16103
	.data.w	.Ldw_str_begin+11095
	.data.b	184,8
	.data.b	39
	.data.b	1
	.data.w	Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_SetInterruptEnStatus
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

	.section	.debug_abbrev		;off: 432
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_SetInterruptEnStatus-Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2108
	.data.b	0,5,2
	.data.w	Dsadc_SetInterruptEnStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	192,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	91
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	6
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	13
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
	.section	.debug_info		;off: 16132
	.data.b	22
	.section	.debug_str		;off: 11122
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 16133
	.data.w	.Ldw_str_begin+11122
	.data.b	187,8
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+342
	.data.b	0
	.data.w	.Ldw_loc_begin+356
	.section	.debug_loc		;off: 356
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16150
	.data.b	22
	.section	.debug_str		;off: 11130
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16151
	.data.w	.Ldw_str_begin+11130
	.data.b	188,8
	.data.b	72
	.data.b	1
	.data.w	.Ldw_begin+347
	.data.b	0
	.data.w	.Ldw_loc_begin+375
	.section	.debug_loc		;off: 375
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16168
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11139
	.data.b	68,115,97,100,99,95,65,117,120,73,115,114,69,118,101,110,116,69,110,116,114,121,0
	.section	.debug_info		;off: 16180
	.data.w	.Ldw_str_begin+11139
	.data.b	173,9
	.data.b	39
	.data.b	1
	.data.w	Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_AuxIsrEventEntry
	.data.b	1
	.data.b	93
	.data.b	244,135,1
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_AuxIsrEventEntry-Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2228
	.data.b	0,5,2
	.data.w	Dsadc_AuxIsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	178,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	12
	.data.b	93
	.data.b	93
	.data.b	43
	.data.b	13
	.data.b	61
	.data.b	29
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	44
	.data.b	29
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	107
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	107
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16211
	.data.b	22
	.section	.debug_str		;off: 11162
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 16212
	.data.w	.Ldw_str_begin+11162
	.data.b	175,9
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+394
	.section	.debug_loc		;off: 394
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16229
	.data.b	22
	.section	.debug_str		;off: 11171
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16230
	.data.w	.Ldw_str_begin+11171
	.data.b	176,9
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+413
	.section	.debug_loc		;off: 413
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	81
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16247
	.data.b	22
	.section	.debug_str		;off: 11179
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16248
	.data.w	.Ldw_str_begin+11179
	.data.b	177,9
	.data.b	72
	.data.b	1
	.data.w	.Ldw_begin+347
	.data.b	0
	.data.w	.Ldw_loc_begin+443
	.section	.debug_loc		;off: 443
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	82
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16265
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 11188
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16275
	.data.w	.Ldw_str_begin+11188
	.data.b	180,9
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1525
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+473
	.section	.debug_loc		;off: 473
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16293
	.data.b	7
	.section	.debug_str		;off: 11198
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 16294
	.data.w	.Ldw_str_begin+11198
	.data.b	181,9
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+492
	.section	.debug_loc		;off: 492
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16312
	.data.b	7
	.section	.debug_str		;off: 11208
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16313
	.data.w	.Ldw_str_begin+11208
	.data.b	182,9
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+511
	.section	.debug_loc		;off: 511
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16331
	.data.b	8
	.section	.debug_str		;off: 11215
	.data.b	65,117,120,82,101,115,117,108,116,0
	.section	.debug_info		;off: 16332
	.data.w	.Ldw_str_begin+11215
	.data.b	185,9
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13087
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11225
	.data.b	68,115,97,100,99,95,73,115,114,69,118,101,110,116,69,110,116,114,121,0
	.section	.debug_info		;off: 16349
	.data.w	.Ldw_str_begin+11225
	.data.b	187,10
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.w	Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_IsrEventEntry
	.data.b	1
	.data.b	93
	.data.b	240,135,1
	.data.b	104
	.data.b	0
	.data.b	36
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
	.data.w	Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_IsrEventEntry-Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2342
	.data.b	0,5,2
	.data.w	Dsadc_IsrEventEntry..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	192,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	60
	.data.b	123
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	61
	.data.b	123
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	60
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 16384
	.data.b	22
	.section	.debug_str		;off: 11245
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 16385
	.data.w	.Ldw_str_begin+11245
	.data.b	189,10
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+530
	.section	.debug_loc		;off: 530
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	80
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16402
	.data.b	22
	.section	.debug_str		;off: 11254
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16403
	.data.w	.Ldw_str_begin+11254
	.data.b	190,10
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+560
	.section	.debug_loc		;off: 560
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	81
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16420
	.data.b	22
	.section	.debug_str		;off: 11262
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16421
	.data.w	.Ldw_str_begin+11262
	.data.b	191,10
	.data.b	72
	.data.b	1
	.data.w	.Ldw_begin+347
	.data.b	0
	.data.w	.Ldw_loc_begin+590
	.section	.debug_loc		;off: 590
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	82
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16438
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	7
	.section	.debug_str		;off: 11271
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 16448
	.data.w	.Ldw_str_begin+11271
	.data.b	194,10
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+620
	.section	.debug_loc		;off: 620
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16466
	.data.b	7
	.section	.debug_str		;off: 11281
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16467
	.data.w	.Ldw_str_begin+11281
	.data.b	195,10
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1525
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+639
	.section	.debug_loc		;off: 639
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16485
	.data.b	8
	.section	.debug_str		;off: 11291
	.data.b	82,101,99,101,110,116,82,115,108,116,0
	.section	.debug_info		;off: 16486
	.data.w	.Ldw_str_begin+11291
	.data.b	196,10
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+13087
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11302
	.data.b	68,115,97,100,99,95,70,105,102,111,79,114,69,120,116,101,114,110,97,108,84,114,105,103,103,101,114,73,115,114,0
	.section	.debug_info		;off: 16503
	.data.w	.Ldw_str_begin+11302
	.data.b	159,11
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.w	Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_FifoOrExternalTriggerIsr
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	44
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_FifoOrExternalTriggerIsr-Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2409
	.data.b	0,5,2
	.data.w	Dsadc_FifoOrExternalTriggerIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	166,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	12
	.data.b	92
	.data.b	91
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	136,1
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	239,126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	42
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	88
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	75
	.data.b	12
	.data.b	124
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	125
	.data.b	91
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	91
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	77
	.data.b	28
	.data.b	44
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	43
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	179,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	202,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
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
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	139
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 16538
	.data.b	22
	.section	.debug_str		;off: 11333
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 16539
	.data.w	.Ldw_str_begin+11333
	.data.b	161,11
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+658
	.section	.debug_loc		;off: 658
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	80
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16556
	.data.b	22
	.section	.debug_str		;off: 11342
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16557
	.data.w	.Ldw_str_begin+11342
	.data.b	162,11
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+688
	.section	.debug_loc		;off: 688
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	81
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16574
	.data.b	22
	.section	.debug_str		;off: 11350
	.data.b	84,114,105,103,77,116,104,100,70,108,103,0
	.section	.debug_info		;off: 16575
	.data.w	.Ldw_str_begin+11350
	.data.b	163,11
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.w	.Ldw_loc_begin+718
	.section	.debug_loc		;off: 718
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	82
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	3
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16592
	.data.b	22
	.section	.debug_str		;off: 11362
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16593
	.data.w	.Ldw_str_begin+11362
	.data.b	164,11
	.data.b	72
	.data.b	1
	.data.w	.Ldw_begin+347
	.data.b	0
	.data.w	.Ldw_loc_begin+749
	.section	.debug_loc		;off: 749
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	83
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16610
	.data.b	22
	.section	.debug_str		;off: 11371
	.data.b	82,101,99,101,110,116,82,115,108,116,0
	.section	.debug_info		;off: 16611
	.data.w	.Ldw_str_begin+11371
	.data.b	165,11
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13087
	.data.b	0
	.data.w	.Ldw_loc_begin+779
	.section	.debug_loc		;off: 779
	.data.w	.LDW73
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	48
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16628
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 11382
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 16638
	.data.w	.Ldw_str_begin+11382
	.data.b	168,11
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+799
	.section	.debug_loc		;off: 799
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16656
	.data.b	7
	.section	.debug_str		;off: 11392
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 16657
	.data.w	.Ldw_str_begin+11392
	.data.b	169,11
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+818
	.section	.debug_loc		;off: 818
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16675
	.data.b	7
	.section	.debug_str		;off: 11402
	.data.b	67,117,114,114,66,117,102,80,111,115,0
	.section	.debug_info		;off: 16676
	.data.w	.Ldw_str_begin+11402
	.data.b	170,11
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13111
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+837
	.section	.debug_loc		;off: 837
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16694
	.data.b	7
	.section	.debug_str		;off: 11413
	.data.b	70,105,102,111,69,114,114,0
	.section	.debug_info		;off: 16695
	.data.w	.Ldw_str_begin+11413
	.data.b	171,11
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+12631
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+856
	.section	.debug_loc		;off: 856
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16713
	.data.b	7
	.section	.debug_str		;off: 11421
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16714
	.data.w	.Ldw_str_begin+11421
	.data.b	172,11
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+876
	.section	.debug_loc		;off: 876
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16732
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11428
	.data.b	68,115,97,100,99,95,84,105,109,101,115,116,97,109,112,73,115,114,0
	.section	.debug_info		;off: 16735
	.data.w	.Ldw_str_begin+11428
	.data.b	246,12
	.data.b	39
	.data.b	1
	.data.w	Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_TimestampIsr
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
	.data.w	Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_TimestampIsr-Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2668
	.data.b	0,5,2
	.data.w	Dsadc_TimestampIsr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	251,12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	24
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	11
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	12
	.data.b	92
	.data.b	140
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16766
	.data.b	22
	.section	.debug_str		;off: 11447
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 16767
	.data.w	.Ldw_str_begin+11447
	.data.b	248,12
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+895
	.section	.debug_loc		;off: 895
	.data.w	.LDW04
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16784
	.data.b	22
	.section	.debug_str		;off: 11456
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16785
	.data.w	.Ldw_str_begin+11456
	.data.b	249,12
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+914
	.section	.debug_loc		;off: 914
	.data.w	.LDW04
	.data.w	.LDW14
	.data.b	1,0
	.data.b	81
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16802
	.data.b	22
	.section	.debug_str		;off: 11464
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16803
	.data.w	.Ldw_str_begin+11464
	.data.b	250,12
	.data.b	72
	.data.b	1
	.data.w	.Ldw_begin+347
	.data.b	0
	.data.w	.Ldw_loc_begin+944
	.section	.debug_loc		;off: 944
	.data.w	.LDW04
	.data.w	.LDW24
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16820
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	7
	.section	.debug_str		;off: 11473
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 16830
	.data.w	.Ldw_str_begin+11473
	.data.b	253,12
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+963
	.section	.debug_loc		;off: 963
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16848
	.data.b	8
	.section	.debug_str		;off: 11483
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16849
	.data.w	.Ldw_str_begin+11483
	.data.b	254,12
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11490
	.data.b	68,115,97,100,99,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 16866
	.data.w	.Ldw_str_begin+11490
	.data.b	170,13
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.w	Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_InitChannel
	.data.b	1
	.data.b	93
	.data.b	244,135,1
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
	.data.w	Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_InitChannel-Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2722
	.data.b	0,5,2
	.data.w	Dsadc_InitChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	175,13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	60
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	172
	.data.b	141
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	109
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	77
	.data.b	76
	.data.b	43
	.data.b	28
	.data.b	60
	.data.b	29
	.data.b	28
	.data.b	29
	.data.b	44
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 16901
	.data.b	22
	.section	.debug_str		;off: 11508
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 16902
	.data.w	.Ldw_str_begin+11508
	.data.b	172,13
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+238
	.data.b	0
	.data.w	.Ldw_loc_begin+982
	.section	.debug_loc		;off: 982
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	80
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16919
	.data.b	22
	.section	.debug_str		;off: 11518
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16920
	.data.w	.Ldw_str_begin+11518
	.data.b	173,13
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.w	.Ldw_loc_begin+1012
	.section	.debug_loc		;off: 1012
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	81
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16937
	.data.b	22
	.section	.debug_str		;off: 11525
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 16938
	.data.w	.Ldw_str_begin+11525
	.data.b	174,13
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1042
	.section	.debug_loc		;off: 1042
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	82
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16955
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 11531
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 16965
	.data.w	.Ldw_str_begin+11531
	.data.b	177,13
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1072
	.section	.debug_loc		;off: 1072
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16983
	.data.b	7
	.section	.debug_str		;off: 11541
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16984
	.data.w	.Ldw_str_begin+11541
	.data.b	178,13
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1091
	.section	.debug_loc		;off: 1091
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17002
	.data.b	8
	.section	.debug_str		;off: 11550
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 17003
	.data.w	.Ldw_str_begin+11550
	.data.b	179,13
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+337
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11558
	.data.b	68,115,97,100,99,95,73,110,105,116,77,97,115,116,101,114,67,111,114,101,0
	.section	.debug_info		;off: 17020
	.data.w	.Ldw_str_begin+11558
	.data.b	138,14
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.w	Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_InitMasterCore
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_InitMasterCore-Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2785
	.data.b	0,5,2
	.data.w	Dsadc_InitMasterCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	141,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	156
	.data.b	157
	.data.b	61
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	77
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17055
	.data.b	22
	.section	.debug_str		;off: 11579
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17056
	.data.w	.Ldw_str_begin+11579
	.data.b	140,14
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+238
	.data.b	0
	.data.w	.Ldw_loc_begin+1110
	.section	.debug_loc		;off: 1110
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	80
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17073
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 11589
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 17083
	.data.w	.Ldw_str_begin+11589
	.data.b	143,14
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1140
	.section	.debug_loc		;off: 1140
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17101
	.data.b	8
	.section	.debug_str		;off: 11599
	.data.b	72,119,85,110,105,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 17102
	.data.w	.Ldw_str_begin+11599
	.data.b	144,14
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1513
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11612
	.data.b	68,115,97,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,69,114,114,67,104,101,99,107,0
	.section	.debug_info		;off: 17119
	.data.w	.Ldw_str_begin+11612
	.data.b	218,14
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_GetStreamLastPointerErrCheck
	.data.b	1
	.data.b	93
	.data.b	128,128,1
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.w	__ghs_eofn_Dsadc_GetStreamLastPointerErrCheck-Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2856
	.data.b	0,5,2
	.data.w	Dsadc_GetStreamLastPointerErrCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc.
	.data.b	6
	.data.b	3
	.data.b	222,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	27
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	27
	.data.b	11
	.data.b	123
	.data.b	12
	.data.b	91
	.data.b	43
	.data.b	13
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17154
	.data.b	22
	.section	.debug_str		;off: 11647
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17155
	.data.w	.Ldw_str_begin+11647
	.data.b	220,14
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.w	.Ldw_loc_begin+1159
	.section	.debug_loc		;off: 1159
	.data.w	.LDW94
	.data.w	.LDW15
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17172
	.data.b	22
	.section	.debug_str		;off: 11654
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 17173
	.data.w	.Ldw_str_begin+11654
	.data.b	221,14
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1178
	.section	.debug_loc		;off: 1178
	.data.w	.LDW94
	.data.w	.LDW15
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17190
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	8
	.section	.debug_str		;off: 11664
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 17200
	.data.w	.Ldw_str_begin+11664
	.data.b	224,14
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11671
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17215
	.data.w	.Ldw_str_begin+11671
	.data.b	225,14
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1197
	.section	.debug_loc		;off: 1197
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17233
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11680
	.data.b	68,115,97,100,99,95,73,110,105,116,0
	.section	.debug_info		;off: 17236
	.data.w	.Ldw_str_begin+11680
	.data.b	168,15
	.data.b	31
	.data.b	1
	.data.w	Dsadc_Init
	.data.w	__ghs_eofn_Dsadc_Init
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_Init
	.data.w	__ghs_eofn_Dsadc_Init-Dsadc_Init
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2909
	.data.b	0,5,2
	.data.w	Dsadc_Init
	.data.b	6
	.data.b	3
	.data.b	171,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	61
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	91
	.data.b	45
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17267
	.data.b	22
	.section	.debug_str		;off: 11691
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17268
	.data.w	.Ldw_str_begin+11691
	.data.b	170,15
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+238
	.data.b	0
	.data.w	.Ldw_loc_begin+1216
	.section	.debug_loc		;off: 1216
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	80
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17285
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 11701
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 17295
	.data.w	.Ldw_str_begin+11701
	.data.b	173,15
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1246
	.section	.debug_loc		;off: 1246
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17313
	.data.b	8
	.section	.debug_str		;off: 11711
	.data.b	69,114,114,0
	.section	.debug_info		;off: 17314
	.data.w	.Ldw_str_begin+11711
	.data.b	175,15
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11715
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 17329
	.data.w	.Ldw_str_begin+11715
	.data.b	177,15
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11721
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17344
	.data.w	.Ldw_str_begin+11721
	.data.b	178,15
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1265
	.section	.debug_loc		;off: 1265
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17362
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11728
	.data.b	68,115,97,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 17365
	.data.w	.Ldw_str_begin+11728
	.data.b	252,15
	.data.b	31
	.data.b	1
	.data.w	Dsadc_DeInit
	.data.w	__ghs_eofn_Dsadc_DeInit
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
	.data.w	Dsadc_DeInit
	.data.w	__ghs_eofn_Dsadc_DeInit-Dsadc_DeInit
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2995
	.data.b	0,5,2
	.data.w	Dsadc_DeInit
	.data.b	6
	.data.b	3
	.data.b	255,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	13
	.data.b	43
	.data.b	44
	.data.b	12
	.data.b	27
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	125
	.data.b	3
	.data.b	111
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	61
	.data.b	28
	.data.b	12
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	16
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
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
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
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17396
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 11741
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 17406
	.data.w	.Ldw_str_begin+11741
	.data.b	129,16
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1284
	.section	.debug_loc		;off: 1284
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17424
	.data.b	7
	.section	.debug_str		;off: 11751
	.data.b	69,114,114,0
	.section	.debug_info		;off: 17425
	.data.w	.Ldw_str_begin+11751
	.data.b	130,16
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1303
	.section	.debug_loc		;off: 1303
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17443
	.data.b	8
	.section	.debug_str		;off: 11755
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 17444
	.data.w	.Ldw_str_begin+11755
	.data.b	131,16
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11761
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17459
	.data.w	.Ldw_str_begin+11761
	.data.b	132,16
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11770
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17474
	.data.w	.Ldw_str_begin+11770
	.data.b	133,16
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1322
	.section	.debug_loc		;off: 1322
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17492
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11777
	.data.b	68,115,97,100,99,95,83,101,116,117,112,82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 17495
	.data.w	.Ldw_str_begin+11777
	.data.b	242,16
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_SetupResultBuffer
	.data.w	__ghs_eofn_Dsadc_SetupResultBuffer
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_SetupResultBuffer
	.data.w	__ghs_eofn_Dsadc_SetupResultBuffer-Dsadc_SetupResultBuffer
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3121
	.data.b	0,5,2
	.data.w	Dsadc_SetupResultBuffer
	.data.b	6
	.data.b	3
	.data.b	247,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	107
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	155
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	0
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
	.data.b	12
	.data.b	12
	.data.b	109
	.data.b	45
	.data.b	12
	.data.b	28
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	92
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
	.section	.debug_info		;off: 17530
	.data.b	22
	.section	.debug_str		;off: 11801
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 17531
	.data.w	.Ldw_str_begin+11801
	.data.b	244,16
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1341
	.section	.debug_loc		;off: 1341
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	80
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17548
	.data.b	22
	.section	.debug_str		;off: 11809
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 17549
	.data.w	.Ldw_str_begin+11809
	.data.b	246,16
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.w	.Ldw_loc_begin+1371
	.section	.debug_loc		;off: 1371
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	81
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17566
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 11823
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 17576
	.data.w	.Ldw_str_begin+11823
	.data.b	249,16
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1401
	.section	.debug_loc		;off: 1401
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17594
	.data.b	7
	.section	.debug_str		;off: 11830
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 17595
	.data.w	.Ldw_str_begin+11830
	.data.b	250,16
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1420
	.section	.debug_loc		;off: 1420
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17613
	.data.b	8
	.section	.debug_str		;off: 11840
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17614
	.data.w	.Ldw_str_begin+11840
	.data.b	253,16
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11849
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17629
	.data.w	.Ldw_str_begin+11849
	.data.b	128,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1439
	.section	.debug_loc		;off: 1439
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17647
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11856
	.data.b	68,115,97,100,99,95,83,116,97,114,116,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 17650
	.data.w	.Ldw_str_begin+11856
	.data.b	228,17
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_StartConversion
	.data.w	__ghs_eofn_Dsadc_StartConversion
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_StartConversion
	.data.w	__ghs_eofn_Dsadc_StartConversion-Dsadc_StartConversion
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3235
	.data.b	0,5,2
	.data.w	Dsadc_StartConversion
	.data.b	6
	.data.b	3
	.data.b	231,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	93
	.data.b	77
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	60
	.data.b	12
	.data.b	107
	.data.b	12
	.data.b	27
	.data.b	27
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
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	29
	.data.b	108
	.data.b	45
	.data.b	44
	.data.b	45
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	11
	.data.b	44
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	29
	.data.b	43
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
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
	.section	.debug_info		;off: 17685
	.data.b	22
	.section	.debug_str		;off: 11878
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 17686
	.data.w	.Ldw_str_begin+11878
	.data.b	230,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1458
	.section	.debug_loc		;off: 1458
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	80
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17703
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 11886
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 17713
	.data.w	.Ldw_str_begin+11886
	.data.b	233,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1488
	.section	.debug_loc		;off: 1488
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17731
	.data.b	7
	.section	.debug_str		;off: 11896
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 17732
	.data.w	.Ldw_str_begin+11896
	.data.b	234,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1507
	.section	.debug_loc		;off: 1507
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17750
	.data.b	7
	.section	.debug_str		;off: 11903
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 17751
	.data.w	.Ldw_str_begin+11903
	.data.b	235,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1526
	.section	.debug_loc		;off: 1526
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17769
	.data.b	7
	.section	.debug_str		;off: 11913
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17770
	.data.w	.Ldw_str_begin+11913
	.data.b	236,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1545
	.section	.debug_loc		;off: 1545
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17788
	.data.b	7
	.section	.debug_str		;off: 11922
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17789
	.data.w	.Ldw_str_begin+11922
	.data.b	237,17
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1564
	.section	.debug_loc		;off: 1564
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17807
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11929
	.data.b	68,115,97,100,99,95,83,116,111,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 17810
	.data.w	.Ldw_str_begin+11929
	.data.b	134,19
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_StopConversion
	.data.w	__ghs_eofn_Dsadc_StopConversion
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_StopConversion
	.data.w	__ghs_eofn_Dsadc_StopConversion-Dsadc_StopConversion
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3380
	.data.b	0,5,2
	.data.w	Dsadc_StopConversion
	.data.b	6
	.data.b	3
	.data.b	137,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	60
	.data.b	12
	.data.b	77
	.data.b	29
	.data.b	109
	.data.b	61
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
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
	.section	.debug_info		;off: 17845
	.data.b	22
	.section	.debug_str		;off: 11950
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 17846
	.data.w	.Ldw_str_begin+11950
	.data.b	136,19
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1583
	.section	.debug_loc		;off: 1583
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	80
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17863
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	8
	.section	.debug_str		;off: 11958
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 17873
	.data.w	.Ldw_str_begin+11958
	.data.b	139,19
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11968
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 17888
	.data.w	.Ldw_str_begin+11968
	.data.b	140,19
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1613
	.section	.debug_loc		;off: 1613
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17906
	.data.b	7
	.section	.debug_str		;off: 11975
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 17907
	.data.w	.Ldw_str_begin+11975
	.data.b	141,19
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1632
	.section	.debug_loc		;off: 1632
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17925
	.data.b	7
	.section	.debug_str		;off: 11985
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17926
	.data.w	.Ldw_str_begin+11985
	.data.b	142,19
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1651
	.section	.debug_loc		;off: 1651
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17944
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11992
	.data.b	68,115,97,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 17947
	.data.w	.Ldw_str_begin+11992
	.data.b	138,20
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+13111
	.data.w	Dsadc_GetStreamLastPointer
	.data.w	__ghs_eofn_Dsadc_GetStreamLastPointer
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_GetStreamLastPointer
	.data.w	__ghs_eofn_Dsadc_GetStreamLastPointer-Dsadc_GetStreamLastPointer
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3500
	.data.b	0,5,2
	.data.w	Dsadc_GetStreamLastPointer
	.data.b	6
	.data.b	3
	.data.b	143,20
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	107
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	12
	.data.b	29
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	91
	.data.b	43
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	13
	.data.b	27
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
	.data.b	0
	.data.b	12
	.data.b	29
	.data.b	43
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17982
	.data.b	22
	.section	.debug_str		;off: 12019
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 17983
	.data.w	.Ldw_str_begin+12019
	.data.b	140,20
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1670
	.section	.debug_loc		;off: 1670
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	80
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18000
	.data.b	22
	.section	.debug_str		;off: 12027
	.data.b	80,116,114,84,111,83,97,109,112,108,101,80,116,114,0
	.section	.debug_info		;off: 18001
	.data.w	.Ldw_str_begin+12027
	.data.b	142,20
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.w	.Ldw_loc_begin+1700
	.section	.debug_loc		;off: 1700
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	81
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18018
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	7
	.section	.debug_str		;off: 12042
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 18028
	.data.w	.Ldw_str_begin+12042
	.data.b	146,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1730
	.section	.debug_loc		;off: 1730
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18046
	.data.b	7
	.section	.debug_str		;off: 12049
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 18047
	.data.w	.Ldw_str_begin+12049
	.data.b	148,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1749
	.section	.debug_loc		;off: 1749
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18065
	.data.b	7
	.section	.debug_str		;off: 12059
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18066
	.data.w	.Ldw_str_begin+12059
	.data.b	149,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1768
	.section	.debug_loc		;off: 1768
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18084
	.data.b	7
	.section	.debug_str		;off: 12068
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 18085
	.data.w	.Ldw_str_begin+12068
	.data.b	150,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13111
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1787
	.section	.debug_loc		;off: 1787
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18103
	.data.b	8
	.section	.debug_str		;off: 12077
	.data.b	70,105,102,111,69,114,114,0
	.section	.debug_info		;off: 18104
	.data.w	.Ldw_str_begin+12077
	.data.b	151,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+12631
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12085
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18119
	.data.w	.Ldw_str_begin+12085
	.data.b	152,20
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1806
	.section	.debug_loc		;off: 1806
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18137
	.data.b	7
	.section	.debug_str		;off: 12092
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18138
	.data.w	.Ldw_str_begin+12092
	.data.b	153,20
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1825
	.section	.debug_loc		;off: 1825
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18156
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12101
	.data.b	68,115,97,100,99,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18159
	.data.w	.Ldw_str_begin+12101
	.data.b	160,21
	.data.b	43
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.w	Dsadc_GetChannelStatus
	.data.w	__ghs_eofn_Dsadc_GetChannelStatus
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_GetChannelStatus
	.data.w	__ghs_eofn_Dsadc_GetChannelStatus-Dsadc_GetChannelStatus
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3631
	.data.b	0,5,2
	.data.w	Dsadc_GetChannelStatus
	.data.b	6
	.data.b	3
	.data.b	164,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	12
	.data.b	29
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	13
	.data.b	91
	.data.b	75
	.data.b	12
	.data.b	91
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	15
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
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	13
	.data.b	93
	.data.b	6
	.data.b	3
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	80
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	63
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	80
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	113
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	192,0
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	13
	.data.b	27
	.data.b	13
	.data.b	13
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18194
	.data.b	22
	.section	.debug_str		;off: 12124
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18195
	.data.w	.Ldw_str_begin+12124
	.data.b	162,21
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+1844
	.section	.debug_loc		;off: 1844
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	80
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18212
	.data.b	22
	.section	.debug_str		;off: 12132
	.data.b	67,111,110,118,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18213
	.data.w	.Ldw_str_begin+12132
	.data.b	163,21
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+13388
	.data.b	0
	.data.w	.Ldw_loc_begin+1874
	.section	.debug_loc		;off: 1874
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	81
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18230
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	8
	.section	.debug_str		;off: 12144
	.data.b	69,114,114,0
	.section	.debug_info		;off: 18240
	.data.w	.Ldw_str_begin+12144
	.data.b	172,21
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12148
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 18255
	.data.w	.Ldw_str_begin+12148
	.data.b	174,21
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1904
	.section	.debug_loc		;off: 1904
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18273
	.data.b	7
	.section	.debug_str		;off: 12158
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18274
	.data.w	.Ldw_str_begin+12158
	.data.b	175,21
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1923
	.section	.debug_loc		;off: 1923
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18292
	.data.b	7
	.section	.debug_str		;off: 12168
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18293
	.data.w	.Ldw_str_begin+12168
	.data.b	176,21
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1942
	.section	.debug_loc		;off: 1942
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18311
	.data.b	7
	.section	.debug_str		;off: 12175
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18312
	.data.w	.Ldw_str_begin+12175
	.data.b	177,21
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1961
	.section	.debug_loc		;off: 1961
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18330
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12184
	.data.b	68,115,97,100,99,95,83,116,97,114,116,67,97,114,114,105,101,114,83,105,103,110,97,108,0
	.section	.debug_info		;off: 18333
	.data.w	.Ldw_str_begin+12184
	.data.b	249,22
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_StartCarrierSignal
	.data.w	__ghs_eofn_Dsadc_StartCarrierSignal
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_StartCarrierSignal
	.data.w	__ghs_eofn_Dsadc_StartCarrierSignal-Dsadc_StartCarrierSignal
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3787
	.data.b	0,5,2
	.data.w	Dsadc_StartCarrierSignal
	.data.b	6
	.data.b	3
	.data.b	252,22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	29
	.data.b	75
	.data.b	12
	.data.b	123
	.data.b	13
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	44
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	13
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	29
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
	.section	.debug_info		;off: 18368
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 12209
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 18378
	.data.w	.Ldw_str_begin+12209
	.data.b	254,22
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1980
	.section	.debug_loc		;off: 1980
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18396
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12216
	.data.b	68,115,97,100,99,95,83,116,111,112,67,97,114,114,105,101,114,83,105,103,110,97,108,0
	.section	.debug_info		;off: 18399
	.data.w	.Ldw_str_begin+12216
	.data.b	195,23
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.w	Dsadc_StopCarrierSignal
	.data.w	__ghs_eofn_Dsadc_StopCarrierSignal
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_StopCarrierSignal
	.data.w	__ghs_eofn_Dsadc_StopCarrierSignal-Dsadc_StopCarrierSignal
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3838
	.data.b	0,5,2
	.data.w	Dsadc_StopCarrierSignal
	.data.b	6
	.data.b	3
	.data.b	198,23
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	29
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	13
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	108
	.data.b	13
	.data.b	12
	.data.b	77
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
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
	.section	.debug_info		;off: 18434
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	7
	.section	.debug_str		;off: 12240
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 18444
	.data.w	.Ldw_str_begin+12240
	.data.b	200,23
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1999
	.section	.debug_loc		;off: 1999
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18462
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12247
	.data.b	68,115,97,100,99,95,71,101,116,84,105,109,101,115,116,97,109,112,0
	.section	.debug_info		;off: 18465
	.data.w	.Ldw_str_begin+12247
	.data.b	250,24
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+13099
	.data.w	Dsadc_GetTimestamp
	.data.w	__ghs_eofn_Dsadc_GetTimestamp
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_GetTimestamp
	.data.w	__ghs_eofn_Dsadc_GetTimestamp-Dsadc_GetTimestamp
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3884
	.data.b	0,5,2
	.data.w	Dsadc_GetTimestamp
	.data.b	6
	.data.b	3
	.data.b	253,24
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
	.data.w	.LDWlin26
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	93
	.data.b	43
	.data.b	12
	.data.b	44
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	113
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	92
	.data.b	13
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
	.data.b	12
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18500
	.data.b	22
	.section	.debug_str		;off: 12266
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18501
	.data.w	.Ldw_str_begin+12266
	.data.b	252,24
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+2018
	.section	.debug_loc		;off: 2018
	.data.w	.LDW97
	.data.w	.LDW08
	.data.b	1,0
	.data.b	80
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18518
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	7
	.section	.debug_str		;off: 12274
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 18528
	.data.w	.Ldw_str_begin+12274
	.data.b	255,24
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2048
	.section	.debug_loc		;off: 2048
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18546
	.data.b	7
	.section	.debug_str		;off: 12284
	.data.b	67,117,114,114,84,105,109,101,115,116,97,109,112,0
	.section	.debug_info		;off: 18547
	.data.w	.Ldw_str_begin+12284
	.data.b	128,25
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13099
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2067
	.section	.debug_loc		;off: 2067
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18565
	.data.b	8
	.section	.debug_str		;off: 12298
	.data.b	69,114,114,0
	.section	.debug_info		;off: 18566
	.data.w	.Ldw_str_begin+12298
	.data.b	130,25
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12302
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18581
	.data.w	.Ldw_str_begin+12302
	.data.b	131,25
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2086
	.section	.debug_loc		;off: 2086
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18599
	.data.b	7
	.section	.debug_str		;off: 12311
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18600
	.data.w	.Ldw_str_begin+12311
	.data.b	133,25
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2105
	.section	.debug_loc		;off: 2105
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18618
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 12318
	.data.b	68,115,97,100,99,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 18621
	.data.w	.Ldw_str_begin+12318
	.data.b	223,25
	.data.b	31
	.data.b	1
	.data.w	Dsadc_EnableNotification
	.data.w	__ghs_eofn_Dsadc_EnableNotification
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

	.section	.debug_frame		;off: 720
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_EnableNotification
	.data.w	__ghs_eofn_Dsadc_EnableNotification-Dsadc_EnableNotification
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4004
	.data.b	0,5,2
	.data.w	Dsadc_EnableNotification
	.data.b	6
	.data.b	3
	.data.b	226,25
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
	.data.w	.LDWlin28
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	92
	.data.b	43
	.data.b	43
	.data.b	59
	.data.b	12
	.data.b	91
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
	.data.b	12
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18652
	.data.b	22
	.section	.debug_str		;off: 12343
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18653
	.data.w	.Ldw_str_begin+12343
	.data.b	225,25
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+2124
	.section	.debug_loc		;off: 2124
	.data.w	.LDW28
	.data.w	.LDW38
	.data.b	1,0
	.data.b	80
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18670
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	7
	.section	.debug_str		;off: 12351
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 18680
	.data.w	.Ldw_str_begin+12351
	.data.b	228,25
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2154
	.section	.debug_loc		;off: 2154
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18698
	.data.b	8
	.section	.debug_str		;off: 12361
	.data.b	69,114,114,0
	.section	.debug_info		;off: 18699
	.data.w	.Ldw_str_begin+12361
	.data.b	230,25
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12365
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18714
	.data.w	.Ldw_str_begin+12365
	.data.b	231,25
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2173
	.section	.debug_loc		;off: 2173
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18732
	.data.b	7
	.section	.debug_str		;off: 12374
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18733
	.data.w	.Ldw_str_begin+12374
	.data.b	233,25
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2192
	.section	.debug_loc		;off: 2192
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18751
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 12381
	.data.b	68,115,97,100,99,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 18754
	.data.w	.Ldw_str_begin+12381
	.data.b	170,26
	.data.b	31
	.data.b	1
	.data.w	Dsadc_DisableNotification
	.data.w	__ghs_eofn_Dsadc_DisableNotification
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

	.section	.debug_frame		;off: 744
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_DisableNotification
	.data.w	__ghs_eofn_Dsadc_DisableNotification-Dsadc_DisableNotification
	.data.b	1
	.data.w	.LDW78
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4080
	.data.b	0,5,2
	.data.w	Dsadc_DisableNotification
	.data.b	6
	.data.b	3
	.data.b	173,26
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
	.data.w	.LDWlin30
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	92
	.data.b	43
	.data.b	43
	.data.b	59
	.data.b	12
	.data.b	91
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
	.data.b	12
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18785
	.data.b	22
	.section	.debug_str		;off: 12407
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18786
	.data.w	.Ldw_str_begin+12407
	.data.b	172,26
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.w	.Ldw_loc_begin+2211
	.section	.debug_loc		;off: 2211
	.data.w	.LDW58
	.data.w	.LDW68
	.data.b	1,0
	.data.b	80
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18803
	.data.b	34
	.data.w	.LDW68
	.data.w	.LDW78

	.data.b	7
	.section	.debug_str		;off: 12415
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 18813
	.data.w	.Ldw_str_begin+12415
	.data.b	175,26
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2241
	.section	.debug_loc		;off: 2241
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18831
	.data.b	7
	.section	.debug_str		;off: 12425
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18832
	.data.w	.Ldw_str_begin+12425
	.data.b	176,26
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2260
	.section	.debug_loc		;off: 2260
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18850
	.data.b	8
	.section	.debug_str		;off: 12432
	.data.b	69,114,114,0
	.section	.debug_info		;off: 18851
	.data.w	.Ldw_str_begin+12432
	.data.b	178,26
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12436
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18866
	.data.w	.Ldw_str_begin+12436
	.data.b	179,26
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2279
	.section	.debug_loc		;off: 2279
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18884
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 12445
	.data.b	68,115,97,100,99,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 18887
	.data.w	.Ldw_str_begin+12445
	.data.b	249,26
	.data.b	33
	.data.b	1
	.data.w	Dsadc_GetVersionInfo
	.data.w	__ghs_eofn_Dsadc_GetVersionInfo
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
	.data.w	Dsadc_GetVersionInfo
	.data.w	__ghs_eofn_Dsadc_GetVersionInfo-Dsadc_GetVersionInfo
	.data.b	1
	.data.w	.LDW09
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4156
	.data.b	0,5,2
	.data.w	Dsadc_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	255,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	11
	.data.b	91
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
	.section	.debug_info		;off: 18916
	.data.b	22
	.section	.debug_str		;off: 12466
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 18917
	.data.w	.Ldw_str_begin+12466
	.data.b	252,26
	.data.b	65
	.data.b	1
	.data.w	.Ldw_begin+700
	.data.b	0
	.data.w	.Ldw_loc_begin+2298
	.section	.debug_loc		;off: 2298
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18934
	.data.b	34
	.data.w	.LDW98
	.data.w	.LDW09

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 12481
	.data.b	68,115,97,100,99,95,65,117,120,105,108,105,97,114,121,67,104,97,110,110,101,108,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 18946
	.data.w	.Ldw_str_begin+12481
	.data.b	173,27
	.data.b	31
	.data.b	1
	.data.w	Dsadc_AuxiliaryChannel_ISRHandler
	.data.w	__ghs_eofn_Dsadc_AuxiliaryChannel_ISRHandler
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

	.section	.debug_frame		;off: 792
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_AuxiliaryChannel_ISRHandler
	.data.w	__ghs_eofn_Dsadc_AuxiliaryChannel_ISRHandler-Dsadc_AuxiliaryChannel_ISRHandler
	.data.b	1
	.data.w	.LDW39
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4188
	.data.b	0,5,2
	.data.w	Dsadc_AuxiliaryChannel_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	176,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin33
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	61
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	123
	.data.b	12
	.data.b	91
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
	.data.b	43
	.data.b	12
	.data.b	77
	.data.b	75
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	139
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18977
	.data.b	22
	.section	.debug_str		;off: 12515
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 18978
	.data.w	.Ldw_str_begin+12515
	.data.b	175,27
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+2317
	.section	.debug_loc		;off: 2317
	.data.w	.LDW19
	.data.w	.LDW29
	.data.b	1,0
	.data.b	80
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18995
	.data.b	34
	.data.w	.LDW29
	.data.w	.LDW39

	.data.b	7
	.section	.debug_str		;off: 12524
	.data.b	69,114,114,0
	.section	.debug_info		;off: 19005
	.data.w	.Ldw_str_begin+12524
	.data.b	179,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2347
	.section	.debug_loc		;off: 2347
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19023
	.data.b	8
	.section	.debug_str		;off: 12528
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19024
	.data.w	.Ldw_str_begin+12528
	.data.b	180,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 12537
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19039
	.data.w	.Ldw_str_begin+12537
	.data.b	181,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1525
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12547
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 19054
	.data.w	.Ldw_str_begin+12547
	.data.b	183,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2366
	.section	.debug_loc		;off: 2366
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19072
	.data.b	7
	.section	.debug_str		;off: 12555
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 19073
	.data.w	.Ldw_str_begin+12555
	.data.b	184,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2385
	.section	.debug_loc		;off: 2385
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19091
	.data.b	7
	.section	.debug_str		;off: 12565
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19092
	.data.w	.Ldw_str_begin+12565
	.data.b	185,27
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2404
	.section	.debug_loc		;off: 2404
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19110
	.data.b	8
	.section	.debug_str		;off: 12572
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19111
	.data.w	.Ldw_str_begin+12572
	.data.b	186,27
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 12581
	.data.b	68,115,97,100,99,95,77,97,105,110,67,104,97,110,110,101,108,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 19128
	.data.w	.Ldw_str_begin+12581
	.data.b	146,28
	.data.b	31
	.data.b	1
	.data.w	Dsadc_MainChannel_ISRHandler
	.data.w	__ghs_eofn_Dsadc_MainChannel_ISRHandler
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

	.section	.debug_frame		;off: 816
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_MainChannel_ISRHandler
	.data.w	__ghs_eofn_Dsadc_MainChannel_ISRHandler-Dsadc_MainChannel_ISRHandler
	.data.b	1
	.data.w	.LDW69
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4278
	.data.b	0,5,2
	.data.w	Dsadc_MainChannel_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	149,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	61
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	123
	.data.b	12
	.data.b	91
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
	.data.b	43
	.data.b	12
	.data.b	77
	.data.b	75
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	141
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
	.section	.debug_info		;off: 19159
	.data.b	22
	.section	.debug_str		;off: 12610
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 19160
	.data.w	.Ldw_str_begin+12610
	.data.b	148,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+13123
	.data.b	0
	.data.w	.Ldw_loc_begin+2423
	.section	.debug_loc		;off: 2423
	.data.w	.LDW49
	.data.w	.LDW59
	.data.b	1,0
	.data.b	80
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19177
	.data.b	34
	.data.w	.LDW59
	.data.w	.LDW69

	.data.b	8
	.section	.debug_str		;off: 12619
	.data.b	83,97,102,101,116,121,69,114,114,0
	.section	.debug_info		;off: 19187
	.data.w	.Ldw_str_begin+12619
	.data.b	151,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1477
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12629
	.data.b	69,114,114,0
	.section	.debug_info		;off: 19202
	.data.w	.Ldw_str_begin+12629
	.data.b	153,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1549
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2453
	.section	.debug_loc		;off: 2453
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19220
	.data.b	8
	.section	.debug_str		;off: 12633
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19221
	.data.w	.Ldw_str_begin+12633
	.data.b	154,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13223
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 12642
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19236
	.data.w	.Ldw_str_begin+12642
	.data.b	155,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1525
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12652
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 19251
	.data.w	.Ldw_str_begin+12652
	.data.b	157,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2472
	.section	.debug_loc		;off: 2472
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19269
	.data.b	7
	.section	.debug_str		;off: 12660
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 19270
	.data.w	.Ldw_str_begin+12660
	.data.b	158,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+13075
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2491
	.section	.debug_loc		;off: 2491
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19288
	.data.b	7
	.section	.debug_str		;off: 12670
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19289
	.data.w	.Ldw_str_begin+12670
	.data.b	159,28
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+1728
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2510
	.section	.debug_loc		;off: 2510
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19307
	.data.b	8
	.section	.debug_str		;off: 12677
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19308
	.data.w	.Ldw_str_begin+12677
	.data.b	160,28
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+312
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
	.data.b	64
	.data.b	2
	.data.b	3
	.data.b	39
	.data.b	3
	.data.b	1
	.data.b	71
	.data.b	77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,84,72,65,54,52,49,50,95,66,71,65,53,49,54,32,40,49,85,41,0
	.data.b	1
	.data.b	75
	.data.b	77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,67,65,84,32,40,77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,84,72,65,54,52,49,50,95,66,71,65,53,49,54,41,0
	.data.b	1
	.data.b	78
	.data.b	77,67,65,76,95,77,65,83,84,69,82,95,67,79,82,69,32,40,77,67,65,76,95,67,79,82,69,48,41,0
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	4
	.data.b	3
	.data.b	25
	.data.b	5
	.data.b	3
	.data.b	25
	.data.b	6
	.data.b	3
	.data.b	31
	.data.b	7
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	8
	.data.b	3
	.data.b	13
	.data.b	9
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
	.data.b	177,2
	.data.b	80,50,67,79,78,83,84,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,99,111,110,115,116,32,112,116,114,116,121,112,101,32,42,0
	.data.b	1
	.data.b	190,2
	.data.b	67,79,78,83,84,80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116,0
	.data.b	1
	.data.b	203,2
	.data.b	67,79,78,83,84,80,50,67,79,78,83,84,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,99,111,110,115,116,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116
	.data.b	0
	.data.b	1
	.data.b	157,3
	.data.b	80,50,80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,42,0
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	10
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
	.data.b	26
	.data.b	11
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	12
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
	.data.b	12
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	28
	.data.b	14
	.data.b	3
	.data.b	22
	.data.b	15
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
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
	.data.b	145,2
	.data.b	68,83,65,68,67,95,67,79,77,77,79,78,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,48,56,48,85,0
	.data.b	1
	.data.b	147,2
	.data.b	68,83,65,68,67,48,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,48,48,48,85,0
	.data.b	1
	.data.b	149,2
	.data.b	68,83,65,68,67,49,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,52,48,48,85,0
	.data.b	1
	.data.b	151,2
	.data.b	68,83,65,68,67,50,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,49,50,48,48,48,85,0
	.data.b	1
	.data.b	153,2
	.data.b	68,83,65,68,67,51,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,49,50,52,48,48,85,0
	.data.b	1
	.data.b	155,2
	.data.b	68,83,65,68,67,52,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,56,48,48,85,0
	.data.b	1
	.data.b	157,2
	.data.b	68,83,65,68,67,53,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,67,48,48,85,0
	.data.b	1
	.data.b	159,2
	.data.b	68,83,65,68,67,54,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,49,50,56,48,48,85,0
	.data.b	1
	.data.b	161,2
	.data.b	68,83,65,68,67,55,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,49,50,67,48,48,85,0
	.data.b	1
	.data.b	163,2
	.data.b	68,83,65,68,67,56,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,51,48,49,48,48,48,85,0
	.data.b	1
	.data.b	166,2
	.data.b	68,83,65,68,67,57,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,51,48,49,52,48,48,85,0
	.data.b	1
	.data.b	169,2
	.data.b	68,83,65,68,67,48,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,48,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	171,2
	.data.b	68,83,65,68,67,49,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,49,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	173,2
	.data.b	68,83,65,68,67,50,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,50,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	175,2
	.data.b	68,83,65,68,67,51,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,51,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	177,2
	.data.b	68,83,65,68,67,52,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,52,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	179,2
	.data.b	68,83,65,68,67,53,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,53,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	181,2
	.data.b	68,83,65,68,67,54,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,54,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	183,2
	.data.b	68,83,65,68,67,55,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,55,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	185,2
	.data.b	68,83,65,68,67,56,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,56,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	187,2
	.data.b	68,83,65,68,67,57,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,57,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	189,2
	.data.b	68,83,65,68,67,95,67,79,77,77,79,78,95,77,79,68,85,76,69,32,40,40,68,83,65,68,67,95,67,79,77,77,79,78,32,42,41,40,68,83,65,68,67,95,67,79,77,77,79,78,95,66,65,83,69,95,65,68,68,82
	.data.b	69,83,83,41,41,0
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
	.data.b	18
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
	.data.b	18
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	19
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	20
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
	.data.b	34
	.data.b	22
	.data.b	3
	.data.b	31
	.data.b	23
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
	.data.b	1
	.data.b	66
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	24
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
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	25
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	24
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
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	26
	.data.b	3
	.data.b	38
	.data.b	27
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	28
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
	.data.b	28
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
	.data.b	148,1
	.data.b	77,67,65,76,95,67,79,82,69,49,32,40,77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,41,0
	.data.b	1
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	29
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
	.data.b	29
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	65
	.data.b	30
	.data.b	3
	.data.b	41
	.data.b	31
	.data.b	3
	.data.b	40
	.data.b	32
	.data.b	1
	.data.b	36
	.data.b	68,83,65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	37
	.data.b	68,83,65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	38
	.data.b	68,83,65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	40
	.data.b	68,83,65,68,67,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	41
	.data.b	68,83,65,68,67,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	42
	.data.b	68,83,65,68,67,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	44
	.data.b	68,83,65,68,67,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	45
	.data.b	68,83,65,68,67,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,50,53,53,85,41,0
	.data.b	1
	.data.b	49
	.data.b	68,83,65,68,67,95,67,79,78,70,73,71,83,69,84,95,67,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	56
	.data.b	68,83,65,68,67,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	63
	.data.b	68,83,65,68,67,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	70
	.data.b	68,83,65,68,67,95,67,70,71,95,68,69,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	77
	.data.b	68,83,65,68,67,95,68,69,77,95,69,82,82,79,82,95,82,69,80,79,82,84,95,83,84,65,84,85,83,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	84
	.data.b	68,83,65,68,67,95,67,70,71,95,71,69,84,83,84,82,69,65,77,76,65,83,84,80,79,73,78,84,69,82,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	91
	.data.b	68,83,65,68,67,95,67,70,71,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	98
	.data.b	68,83,65,68,67,95,67,70,71,95,78,79,84,73,70,95,67,65,80,65,66,73,76,73,84,89,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	105
	.data.b	68,83,65,68,67,95,67,70,71,95,84,73,77,69,83,84,65,77,80,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	112
	.data.b	68,83,65,68,67,95,67,70,71,95,67,76,79,67,75,83,89,78,67,95,69,78,65,66,76,69,32,40,68,83,65,68,67,95,69,78,65,66,76,69,41,0
	.data.b	1
	.data.b	119
	.data.b	68,83,65,68,67,95,67,70,71,95,73,78,84,69,71,82,65,84,79,82,95,69,78,65,66,76,69,32,40,68,83,65,68,67,95,69,78,65,66,76,69,41,0
	.data.b	1
	.data.b	126
	.data.b	68,83,65,68,67,95,67,70,71,95,76,73,77,73,84,95,67,72,69,67,75,73,78,71,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	133,1
	.data.b	68,83,65,68,67,95,67,70,71,95,65,85,88,95,70,73,76,84,69,82,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	140,1
	.data.b	68,83,65,68,67,95,67,70,71,95,83,69,84,95,67,65,82,82,73,69,82,95,83,89,78,67,95,80,65,82,65,77,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	148,1
	.data.b	68,83,65,68,67,95,67,70,71,95,71,69,84,95,67,65,82,82,73,69,82,95,83,89,78,67,95,68,69,76,65,89,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	154,1
	.data.b	68,83,65,68,67,95,67,70,71,95,73,78,73,84,95,83,89,78,67,95,69,78,65,66,76,69,95,72,87,85,78,73,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	157,1
	.data.b	68,83,65,68,67,95,84,79,84,65,76,95,72,87,85,78,73,84,32,40,49,48,85,41,0
	.data.b	1
	.data.b	162,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,48,32,40,48,85,41,0
	.data.b	1
	.data.b	163,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,49,32,40,49,85,41,0
	.data.b	1
	.data.b	164,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,50,32,40,50,85,41,0
	.data.b	1
	.data.b	165,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,51,32,40,51,85,41,0
	.data.b	1
	.data.b	166,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,52,32,40,52,85,41,0
	.data.b	1
	.data.b	167,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,53,32,40,53,85,41,0
	.data.b	1
	.data.b	168,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,54,32,40,54,85,41,0
	.data.b	1
	.data.b	169,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,55,32,40,55,85,41,0
	.data.b	1
	.data.b	170,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,56,32,40,56,85,41,0
	.data.b	1
	.data.b	171,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,68,83,65,68,67,57,32,40,57,85,41,0
	.data.b	1
	.data.b	197,1
	.data.b	68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,48,32,40,52,85,41,0
	.data.b	1
	.data.b	199,1
	.data.b	68,83,65,68,67,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,48,32,40,68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,48,41,0
	.data.b	1
	.data.b	201,1
	.data.b	68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,49,32,40,48,85,41,0
	.data.b	1
	.data.b	203,1
	.data.b	68,83,65,68,67,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,49,32,40,68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,49,41,0
	.data.b	1
	.data.b	205,1
	.data.b	68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	207,1
	.data.b	68,83,65,68,67,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,50,32,40,68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,50,41,0
	.data.b	1
	.data.b	209,1
	.data.b	68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	1
	.data.b	211,1
	.data.b	68,83,65,68,67,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,51,32,40,68,83,65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,51,41,0
	.data.b	1
	.data.b	213,1
	.data.b	68,83,65,68,67,95,67,70,71,95,84,79,84,65,76,95,67,72,65,78,78,69,76,83,32,40,52,85,41,0
	.data.b	1
	.data.b	217,1
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,72,65,78,68,76,73,78,71,95,73,78,84,69,82,82,85,80,84,95,77,79,68,69,32,40,48,85,41,0
	.data.b	1
	.data.b	221,1
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,72,65,78,68,76,73,78,71,95,68,77,65,95,77,79,68,69,32,40,50,85,41,0
	.data.b	1
	.data.b	224,1
	.data.b	68,83,65,68,67,95,67,70,71,95,68,77,65,95,77,79,68,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	226,1
	.data.b	68,83,65,68,67,95,67,70,71,95,73,78,84,69,82,82,85,80,84,95,77,79,68,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	228,1
	.data.b	68,83,65,68,67,95,67,70,71,95,80,79,76,76,73,78,71,95,77,79,68,69,32,40,83,84,68,95,79,70,70,41,0
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	33
	.data.b	3
	.data.b	45
	.data.b	34
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	35
	.data.b	1
	.data.b	207,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	209,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	234,2
	.data.b	68,83,65,68,67,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	158,4
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,4
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	47
	.data.b	37
	.data.b	4
	.data.b	1
	.data.b	62
	.data.b	68,83,65,68,67,95,69,88,84,69,82,78,65,76,95,84,82,73,71,71,69,82,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,48,85,41,0
	.data.b	1
	.data.b	65
	.data.b	68,83,65,68,67,95,70,73,70,79,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,49,85,41,0
	.data.b	1
	.data.b	74
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,52,85,41,0
	.data.b	1
	.data.b	77
	.data.b	68,83,65,68,67,95,65,85,88,73,76,73,65,82,89,95,83,65,85,76,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,53,85,41,0
	.data.b	1
	.data.b	80
	.data.b	68,83,65,68,67,95,65,85,88,73,76,73,65,82,89,95,83,66,85,76,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,54,85,41,0
	.data.b	1
	.data.b	83
	.data.b	68,83,65,68,67,95,65,85,88,73,76,73,65,82,89,95,67,79,77,80,76,69,84,69,68,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,55,85,41,0
	.data.b	1
	.data.b	86
	.data.b	68,83,65,68,67,95,68,77,65,95,70,73,70,79,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,56,85,41,0
	.data.b	1
	.data.b	89
	.data.b	68,83,65,68,67,95,68,77,65,95,69,88,84,69,82,78,65,76,95,84,82,73,71,71,69,82,95,73,78,84,69,82,82,85,80,84,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,57,85,41,0
	.data.b	1
	.data.b	231,1
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	220,8
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	222,8
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	38
	.data.b	1
	.data.b	47
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68
	.data.b	32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	53
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	55
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	52
	.data.b	68,83,65,68,67,95,69,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,65,85,41,0
	.data.b	1
	.data.b	54
	.data.b	68,83,65,68,67,95,69,95,66,85,83,89,32,40,40,117,105,110,116,56,41,48,120,48,66,85,41,0
	.data.b	1
	.data.b	56
	.data.b	68,83,65,68,67,95,69,95,73,68,76,69,32,40,40,117,105,110,116,56,41,48,120,48,67,85,41,0
	.data.b	1
	.data.b	58
	.data.b	68,83,65,68,67,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,48,120,48,68,85,41,0
	.data.b	1
	.data.b	60
	.data.b	68,83,65,68,67,95,69,95,80,65,82,65,77,95,67,79,78,70,73,71,32,40,40,117,105,110,116,56,41,48,120,48,69,85,41,0
	.data.b	1
	.data.b	62
	.data.b	68,83,65,68,67,95,69,95,77,65,83,84,69,82,95,67,79,82,69,95,85,78,73,78,73,84,73,65,76,73,90,69,32,40,40,117,105,110,116,56,41,48,120,49,48,85,41,0
	.data.b	1
	.data.b	64
	.data.b	68,83,65,68,67,95,69,95,83,76,65,86,69,95,67,79,82,69,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,48,120,49,49,85,41,0
	.data.b	1
	.data.b	66
	.data.b	68,83,65,68,67,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,49,52,85,41,0
	.data.b	1
	.data.b	68
	.data.b	68,83,65,68,67,95,69,95,80,65,82,65,77,95,67,72,65,78,78,69,76,32,40,40,117,105,110,116,56,41,48,120,49,53,85,41,0
	.data.b	1
	.data.b	74
	.data.b	68,83,65,68,67,95,69,95,78,79,84,73,70,95,67,65,80,65,66,73,76,73,84,89,32,40,40,117,105,110,116,56,41,48,120,49,55,85,41,0
	.data.b	1
	.data.b	76
	.data.b	68,83,65,68,67,95,69,95,66,85,70,70,69,82,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,49,56,85,41,0
	.data.b	1
	.data.b	79
	.data.b	68,83,65,68,67,95,69,95,68,77,65,95,69,78,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,49,65,85,41,0
	.data.b	1
	.data.b	81
	.data.b	68,83,65,68,67,95,69,95,83,73,78,71,76,69,95,69,78,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,49,66,85,41,0
	.data.b	1
	.data.b	84
	.data.b	68,83,65,68,67,95,69,95,84,73,77,69,83,84,65,77,80,95,78,79,84,95,83,85,80,80,79,82,84,69,68,32,40,40,117,105,110,116,56,41,48,120,49,67,85,41,0
	.data.b	1
	.data.b	87
	.data.b	68,83,65,68,67,95,69,95,65,85,88,95,70,73,76,84,69,82,95,68,73,83,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,49,68,85,41,0
	.data.b	1
	.data.b	94
	.data.b	68,83,65,68,67,95,69,95,67,65,82,82,73,69,82,95,65,76,82,69,65,68,89,95,79,80,69,78,68,69,68,32,40,40,117,105,110,116,56,41,48,120,50,48,85,41,0
	.data.b	1
	.data.b	97
	.data.b	68,83,65,68,67,95,69,95,67,65,82,82,73,69,82,95,65,76,82,69,65,68,89,95,67,76,79,83,69,68,32,40,40,117,105,110,116,56,41,48,120,50,49,85,41,0
	.data.b	1
	.data.b	100
	.data.b	68,83,65,68,67,95,69,95,67,65,82,82,73,69,82,95,68,73,83,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,50,50,85,41,0
	.data.b	1
	.data.b	103
	.data.b	68,83,65,68,67,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,40,117,105,110,116,56,41,48,120,69,48,85,41,0
	.data.b	1
	.data.b	105
	.data.b	68,83,65,68,67,95,69,95,67,79,82,69,95,72,87,85,78,73,84,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,69,49,85,41,0
	.data.b	1
	.data.b	112
	.data.b	68,83,65,68,67,95,69,95,83,65,70,69,84,89,95,67,72,69,67,75,95,70,65,73,76,69,68,32,40,40,117,105,110,116,56,41,48,120,69,50,85,41,0
	.data.b	1
	.data.b	118
	.data.b	68,83,65,68,67,95,83,73,68,95,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,48,85,41,0
	.data.b	1
	.data.b	120
	.data.b	68,83,65,68,67,95,83,73,68,95,68,69,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,49,85,41,0
	.data.b	1
	.data.b	122
	.data.b	68,83,65,68,67,95,83,73,68,95,83,69,84,85,80,82,69,83,85,76,84,66,85,70,70,69,82,32,40,40,117,105,110,116,56,41,48,120,48,50,85,41,0
	.data.b	1
	.data.b	124
	.data.b	68,83,65,68,67,95,83,73,68,95,83,84,65,82,84,67,79,78,86,69,82,83,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,51,85,41,0
	.data.b	1
	.data.b	126
	.data.b	68,83,65,68,67,95,83,73,68,95,83,84,79,80,67,79,78,86,69,82,83,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,52,85,41,0
	.data.b	1
	.data.b	128,1
	.data.b	68,83,65,68,67,95,83,73,68,95,71,69,84,83,84,82,69,65,77,76,65,83,84,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,48,53,85,41,0
	.data.b	1
	.data.b	130,1
	.data.b	68,83,65,68,67,95,83,73,68,95,71,69,84,83,84,65,84,85,83,32,40,40,117,105,110,116,56,41,48,120,48,54,85,41,0
	.data.b	1
	.data.b	133,1
	.data.b	68,83,65,68,67,95,83,73,68,95,83,84,65,82,84,67,65,82,82,73,69,82,83,73,71,78,65,76,32,40,40,117,105,110,116,56,41,48,120,48,57,85,41,0
	.data.b	1
	.data.b	136,1
	.data.b	68,83,65,68,67,95,83,73,68,95,83,84,79,80,67,65,82,82,73,69,82,83,73,71,78,65,76,32,40,40,117,105,110,116,56,41,48,120,48,65,85,41,0
	.data.b	1
	.data.b	138,1
	.data.b	68,83,65,68,67,95,83,73,68,95,71,69,84,84,73,77,69,83,84,65,77,80,32,40,40,117,105,110,116,56,41,48,120,48,66,85,41,0
	.data.b	1
	.data.b	140,1
	.data.b	68,83,65,68,67,95,83,73,68,95,69,78,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,67,85,41,0
	.data.b	1
	.data.b	142,1
	.data.b	68,83,65,68,67,95,83,73,68,95,68,73,83,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,68,85,41,0
	.data.b	1
	.data.b	144,1
	.data.b	68,83,65,68,67,95,83,73,68,95,71,69,84,86,69,82,83,73,79,78,73,78,70,79,32,40,40,117,105,110,116,56,41,48,120,48,69,85,41,0
	.data.b	1
	.data.b	153,1
	.data.b	68,83,65,68,67,95,83,73,68,95,65,85,88,67,72,65,78,78,69,76,95,73,83,82,32,40,40,117,105,110,116,56,41,48,120,69,48,85,41,0
	.data.b	1
	.data.b	155,1
	.data.b	68,83,65,68,67,95,83,73,68,95,77,65,73,78,67,72,65,78,78,69,76,95,73,83,82,32,40,40,117,105,110,116,56,41,48,120,69,49,85,41,0
	.data.b	1
	.data.b	242,1
	.data.b	68,83,65,68,67,95,69,78,65,66,76,69,32,40,49,85,41,0
	.data.b	1
	.data.b	132,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	133,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	249,2
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	250,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	66
	.data.b	39
	.data.b	1
	.data.b	27
	.data.b	68,83,65,68,67,95,86,69,78,68,79,82,95,73,68,32,40,48,120,65,70,85,41,0
	.data.b	1
	.data.b	28
	.data.b	68,83,65,68,67,95,77,79,68,85,76,69,95,73,68,32,40,50,53,53,85,41,0
	.data.b	1
	.data.b	30
	.data.b	68,83,65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	31
	.data.b	68,83,65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	32
	.data.b	68,83,65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	34
	.data.b	68,83,65,68,67,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	35
	.data.b	68,83,65,68,67,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	36
	.data.b	68,83,65,68,67,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	38
	.data.b	68,83,65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,32,40,40,117,105,110,116,56,41,55,85,41,0
	.data.b	4
	.data.b	3
	.data.b	67
	.data.b	40
	.data.b	4
	.data.b	3
	.data.b	70
	.data.b	41
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
	.data.b	1
	.data.b	127
	.data.b	68,83,65,68,67,95,71,69,84,95,67,72,67,70,71,40,67,111,114,101,44,67,104,97,110,110,101,108,73,100,120,41,32,40,38,68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102
	.data.b	105,103,80,116,114,91,67,111,114,101,93,45,62,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,97,110,110,101,108,73,100,120,93,41,0
	.data.b	1
	.data.b	134,1
	.data.b	68,83,65,68,67,95,71,69,84,95,67,79,82,69,67,72,73,68,88,40,67,104,97,110,110,101,108,41,32,40,68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,45,62,67,104,97,110,110,101,108,77,97,112,80,116,114
	.data.b	91,67,104,97,110,110,101,108,93,46,67,111,114,101,67,104,97,110,110,101,108,73,100,120,41,0
	.data.b	1
	.data.b	141,1
	.data.b	68,83,65,68,67,95,71,69,84,95,67,79,82,69,77,65,88,67,72,40,67,111,114,101,41,32,40,68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111
	.data.b	114,101,93,45,62,77,97,120,67,111,114,101,67,104,97,110,110,101,108,41,0
	.data.b	1
	.data.b	148,1
	.data.b	68,83,65,68,67,95,71,69,84,95,67,72,79,70,72,87,40,72,119,85,110,105,116,73,100,41,32,40,68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,45,62,72,119,85,110,105,116,84,111,67,104,97,110,110,101,108
	.data.b	73,100,80,116,114,91,72,119,85,110,105,116,73,100,93,41,0
	.data.b	1
	.data.b	155,1
	.data.b	68,83,65,68,67,95,71,69,84,95,72,87,79,70,67,72,40,67,104,97,110,110,101,108,41,32,40,68,115,97,100,99,95,67,111,110,102,105,103,80,116,114,45,62,67,104,97,110,110,101,108,77,97,112,80,116,114,91,67,104
	.data.b	97,110,110,101,108,93,46,72,119,85,110,105,116,73,100,41,0
	.data.b	1
	.data.b	163,1
	.data.b	68,83,65,68,67,95,67,72,83,84,65,40,67,111,114,101,44,67,104,97,110,110,101,108,73,100,120,41,32,40,68,115,97,100,99,95,67,111,114,101,68,97,116,97,83,101,116,80,116,114,91,67,111,114,101,93,91,67,104,97
	.data.b	110,110,101,108,73,100,120,93,46,67,104,83,116,97,116,117,115,41,0
	.data.b	1
	.data.b	169,1
	.data.b	68,83,65,68,67,95,67,72,65,85,88,83,84,65,40,67,111,114,101,44,67,104,97,110,110,101,108,73,100,120,41,32,40,68,115,97,100,99,95,67,111,114,101,68,97,116,97,83,101,116,80,116,114,91,67,111,114,101,93,91
	.data.b	67,104,97,110,110,101,108,73,100,120,93,46,67,104,65,117,120,83,116,97,116,117,115,41,0
	.data.b	1
	.data.b	175,1
	.data.b	68,83,65,68,67,95,67,72,73,78,84,66,73,84,83,40,67,111,114,101,44,67,104,97,110,110,101,108,73,100,120,41,32,40,68,115,97,100,99,95,67,111,114,101,68,97,116,97,83,101,116,80,116,114,91,67,111,114,101,93
	.data.b	91,67,104,97,110,110,101,108,73,100,120,93,46,73,110,116,69,110,66,105,116,115,41,0
	.data.b	1
	.data.b	181,1
	.data.b	68,115,97,100,99,95,82,101,112,111,114,116,69,114,114,111,114,40,83,101,114,118,105,99,101,73,100,44,69,114,114,67,111,100,101,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,40,68
	.data.b	83,65,68,67,95,77,79,68,85,76,69,95,73,68,44,32,68,83,65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,44,32,83,101,114,118,105,99,101,73,100,44,32,69,114,114,67,111,100,101,41,0
	.data.b	1
	.data.b	189,1
	.data.b	68,115,97,100,99,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,40,83,101,114,118,105,99,101,73,100,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69
	.data.b	114,114,111,114,40,68,83,65,68,67,95,77,79,68,85,76,69,95,73,68,44,32,68,83,65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,44,32,83,101,114,118,105,99,101,73,100,44,32,68,83,65,68,67,95,69,95
	.data.b	83,65,70,69,84,89,95,67,72,69,67,75,95,70,65,73,76,69,68,41,0
	.data.b	1
	.data.b	196,1
	.data.b	68,83,65,68,67,95,67,65,82,82,73,69,82,95,83,73,71,78,65,76,95,83,84,79,80,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	198,1
	.data.b	68,83,65,68,67,95,67,65,82,82,73,69,82,95,83,73,71,78,65,76,95,83,84,65,82,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	202,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,69,78,95,76,79,87,95,66,73,84,83,95,77,65,83,75,32,40,48,120,70,70,85,41,0
	.data.b	1
	.data.b	204,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,69,78,95,72,73,71,72,95,66,73,84,83,95,83,72,73,70,84,32,40,56,85,41,0
	.data.b	1
	.data.b	206,1
	.data.b	68,83,65,68,67,95,72,87,85,78,73,84,95,69,78,95,72,73,71,72,95,66,73,84,83,95,77,65,83,75,32,40,48,120,51,48,48,48,48,85,41,0
	.data.b	1
	.data.b	218,1
	.data.b	68,83,65,68,67,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,68,115,97,100
	.data.b	99,95,32,35,35,32,69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	221,1
	.data.b	68,83,65,68,67,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,68,115,97,100,99,95
	.data.b	32,35,35,32,69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	227,1
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	228,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32
	.data.b	0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	236,1
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	238,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	242,1
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	244,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32
	.data.b	0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	249,1
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	251,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	196,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67
	.data.b	72,69,65,66,76,69,32,0
	.data.b	3
	.data.b	198,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68
	.data.b	95,78,79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	208,2
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72
	.data.b	69,65,66,76,69,32,0
	.data.b	3
	.data.b	210,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	215,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	217,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	254,3
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	128,4
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	141,4
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	143,4
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	128,5
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	130,5
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,5
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	136,5
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,15
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	136,15
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	140,15
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	142,15
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	227,28
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	229,28
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 478
	.data.b	0
