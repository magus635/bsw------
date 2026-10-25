	.section ".sdk_text_asil_d","ax"

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	2
Adc_DmaTransferSwTrigResult::	.space	40
	.endo	Adc_DmaTransferSwTrigResult
	.section ".sdk_text_asil_d","ax"
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_GtmTriggerCnt_0 - Adc_GtmTriggerCnt_0) +0 == 0
	.assert 0x0 + (Adc_HwTrigSingleResult - Adc_GtmTriggerCnt_0) +0 == 2
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_HwTrigSingleWithGtmDemo:
.LDW01:
	push	{r4-r6,lr}
	ldr	r4,.L242
.LDW11:
	movw	r0,0x0179
.L247:

	bl	Intc_EnableInterrupt
	mov	r5,0
	mov	r0,r5
	strb	r5,[r4]
.L249:

	bl	Adc_EnableGroupNotification
	add	r1,r4,2
	mov	r0,r5
.L251:

	bl	Adc_SetupResultBuffer
	movs	r1,r0
	mov	r0,r5
	bne	.L23
	strb	r1,[r4]
.L253:

	bl	Adc_EnableHardwareTrigger
	b	.L28
.L23:
	ldr	r1,.L243
.L255:

	bl	TmcPrintf
.L28:
	add	r5,r5,1
	mov	r0,1
.L257:

	bl	Timer_DelayMs
	cmp	r5,0x03e8
	ldrblo	r0,[r4]
	cmplo	r0,5
	blo	.L28
	ldrb	r0,[r4]
	cmp	r0,5
	ldreq	r1,.L244
	ldrne	r1,.L245
	mov	r0,0
.L259:

	bl	TmcPrintf
	movw	r0,0x0179
.L261:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
	pop	{r4-r6,lr}
.L263:

	b	TmcPrintf
.LDW21:
__ghs_eofn_Adc_HwTrigSingleWithGtmDemo:
	.endf	Adc_HwTrigSingleWithGtmDemo
	.endf	Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ret	r1	local
;LoopCnt	r5	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_GtmTriggerCnt_0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_GtmTriggerCnt_0:	.space	1
	.endo	Adc_GtmTriggerCnt_0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_GtmTriggerCnt_0
	.section ".rodata","a"
.L154:;	"\n"
	.data.b	10,0
	.endo	.L154
	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.space	1
Adc_HwTrigSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_HwTrigSingleResult:	.space	14
	.endo	Adc_HwTrigSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_HwTrigSingleResult
	.section ".rodata","a"
.L155:;	"\nTest Result = PASS"
	.data.b	10,84,101,115
	.data.b	116,32,82,101
	.data.b	115,117,108,116
	.data.b	32,61,32,80
	.data.b	65,83,83,0
	.endo	.L155
.L156:;	"\nTest Result = FAIL"
	.data.b	10,84,101,115
	.data.b	116,32,82,101
	.data.b	115,117,108,116
	.data.b	32,61,32,70
	.data.b	65,73,76,0
	.endo	.L156
.L157:;	"\nSetup result buffer FAILED!!!"
	.data.b	10,83,101,116
	.data.b	117,112,32,114
	.data.b	101,115,117,108
	.data.b	116,32,98,117
	.data.b	102,102,101,114
	.data.b	32,70,65,73
	.data.b	76,69,68,33
	.data.b	33,33
	.data.b	0
	.endo	.L157
	.section ".ghcalltbl",""
	.align	4
.L248:	.data.w	.L247
	.endo	.L248
.L250:	.data.w	.L249
	.endo	.L250
.L252:	.data.w	.L251
	.endo	.L252
.L254:	.data.w	.L253
	.endo	.L254
.L256:	.data.w	.L255
	.endo	.L256
.L258:	.data.w	.L257
	.endo	.L258
.L260:	.data.w	.L259
	.endo	.L260
.L262:	.data.w	.L261
	.endo	.L262
	.section ".ghtailcalltbl",""
	.align	4
.L264:	.data.w	.L263
	.endo	.L264
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Adc_EnableGroupNotification.v.i

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_HwTrigStreamingResult - Adc_HwTrigStreamingResult) +0 == 0
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_HwTrigStreamingWithGtmDemo:
.LDW31:
	push	{r4-r6,lr}
	sub	sp,sp,8
	ldr	r6,.L591
.LDW41:
	movw	r0,0x017a
.L596:

	bl	Intc_EnableInterrupt
	mov	r1,r6
	mov	r0,1
.L598:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L267
	mov	r0,1
.L600:

	bl	Adc_EnableHardwareTrigger
	b	.L269
.L267:
	ldr	r1,.L243
	mov	r0,0
.L602:

	bl	TmcPrintf
.L269:
	mov	r4,0
.L272:
	mov	r0,1
.L604:

	bl	Timer_DelayMs
	add	r1,sp,4
	mov	r0,1
.L606:

	bl	Adc_GetStreamLastPointer
	add	r4,r4,1
	cmp	r4,0x03e8
	bhs	.L270
	cmp	r0,5
	bne	.L272
.L270:
	mov	r0,1
.L608:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	bne	.L274
	ldr	r1,.L592
.L610:

	bl	TmcPrintf
	mov	r4,0
.L278:
	ldr	r1,.L593
	mov	r2,r4
	mov	r0,0
.L612:

	bl	TmcPrintf
	mov	r5,0
.L283:
	add	r0,r5,r5 lsl 2
	add	r0,r0,r4
	lsl	r0,r0,1
	ldr	r1,.L594
	ldrh	r2,[r0,r6]
	mov	r0,0
.L614:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,3
	blo	.L283
	ldr	r1,.L595
	mov	r0,0
.L616:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,5
	blo	.L278
	ldr	r1,.L244
	b	.L284
.L274:
	ldr	r1,.L245
.L284:
	mov	r0,0
.L618:

	bl	TmcPrintf
	movw	r0,0x017a
.L620:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
.L622:

	bl	TmcPrintf
.LDW51:
	add	sp,sp,8
.L624:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_HwTrigStreamingWithGtmDemo:
	.endf	Adc_HwTrigStreamingWithGtmDemo
	.endf	Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;LoopCnt	r4	local
;ResultPtr	[sp,4]	local
;ValidNum	r0	local

	.section ".rodata","a"
.L450:;	"\r\n"
	.data.b	13,10
	.data.b	0
	.endo	.L450
.L451:;	"%4u "
	.data.b	37,52,117,32
	.data.b	0
	.endo	.L451
.L452:;	"No. %d: "
	.data.b	78,111,46,32
	.data.b	37,100,58,32
	.data.b	0
	.endo	.L452
	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_HwTrigStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_HwTrigStreamingResult:	.space	30
	.endo	Adc_HwTrigStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_HwTrigStreamingResult
	.section ".rodata","a"
.L453:;	"\nSARADC0 HW trigger Linear Streaming Result: \r\n"
	.data.b	10,83,65,82
	.data.b	65,68,67,48
	.data.b	32,72,87,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	76,105,110,101
	.data.b	97,114,32,83
	.data.b	116,114,101,97
	.data.b	109,105,110,103
	.data.b	32,82,101,115
	.data.b	117,108,116,58
	.data.b	32,13,10,0
	.endo	.L453
	.section ".ghcalltbl",""
.L597:	.data.w	.L596
	.endo	.L597
.L599:	.data.w	.L598
	.endo	.L599
.L601:	.data.w	.L600
	.endo	.L601
.L603:	.data.w	.L602
	.endo	.L603
.L605:	.data.w	.L604
	.endo	.L605
.L607:	.data.w	.L606
	.endo	.L607
.L609:	.data.w	.L608
	.endo	.L609
.L611:	.data.w	.L610
	.endo	.L611
.L613:	.data.w	.L612
	.endo	.L613
.L615:	.data.w	.L614
	.endo	.L615
.L617:	.data.w	.L616
	.endo	.L617
.L619:	.data.w	.L618
	.endo	.L619
.L621:	.data.w	.L620
	.endo	.L621
.L623:	.data.w	.L622
	.endo	.L623
	.section ".ghrettbl",""
	.align	4
.L625:	.data.w	.L624
	.endo	.L625
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetStreamLastPointer.i.ip

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_GtmTriggerCnt_0 - Adc_GtmTriggerCnt_0) +0 == 0
	.assert 0x0 + (Adc_HwTrigSingleResult - Adc_GtmTriggerCnt_0) +0 == 2
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_HwTrigSingleWithResultAccumuDemo:
.LDW61:
	push	{r4-r6,lr}
	ldr	r4,.L242
.LDW71:
	movw	r0,0x0179
.L852:

	bl	Intc_EnableInterrupt
	mov	r0,0
	strb	r0,[r4]
	mov	r0,2
.L854:

	bl	Adc_EnableGroupNotification
	add	r1,r4,2
	mov	r0,2
.L856:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L628
	strb	r0,[r4]
	mov	r0,2
.L858:

	bl	Adc_EnableHardwareTrigger
	b	.L630
.L628:
	ldr	r1,.L243
	mov	r0,0
.L860:

	bl	TmcPrintf
.L630:
	mov	r5,0
.L633:
	add	r5,r5,1
	mov	r0,1
.L862:

	bl	Timer_DelayMs
	movw	r0,0x1388
	cmp	r5,r0
	ldrblo	r0,[r4]
	cmplo	r0,5
	blo	.L633
	ldrb	r0,[r4]
	cmp	r0,5
	ldreq	r1,.L244
	ldrne	r1,.L245
	mov	r0,0
.L864:

	bl	TmcPrintf
	movw	r0,0x0179
.L866:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
	pop	{r4-r6,lr}
.L868:

	b	TmcPrintf
.LDW81:
__ghs_eofn_Adc_HwTrigSingleWithResultAccumuDemo:
	.endf	Adc_HwTrigSingleWithResultAccumuDemo
	.endf	Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ret	r0	local
;LoopCnt	r5	local

	.section ".ghcalltbl",""
.L853:	.data.w	.L852
	.endo	.L853
.L855:	.data.w	.L854
	.endo	.L855
.L857:	.data.w	.L856
	.endo	.L857
.L859:	.data.w	.L858
	.endo	.L859
.L861:	.data.w	.L860
	.endo	.L861
.L863:	.data.w	.L862
	.endo	.L863
.L865:	.data.w	.L864
	.endo	.L865
.L867:	.data.w	.L866
	.endo	.L867
	.section ".ghtailcalltbl",""
.L869:	.data.w	.L868
	.endo	.L869
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Adc_EnableGroupNotification.v.i

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SyncGroupHwTrigDemo:
.LDW91:
	push	{r4-r5,lr}
	sub	sp,sp,12
.LDW02:
	mov	r0,0
	strb	r0,[sp,2]
	mov	r0,2
	strb	r0,[sp,3]
	movw	r0,0x0179
.L1284:

	bl	Intc_EnableInterrupt
	ldr	r1,.L1280
	mov	r0,3
.L1286:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L872
	mov	r0,3
.L1288:

	bl	Adc_EnableHardwareTrigger
	b	.L874
.L872:
	ldr	r1,.L243
	mov	r0,0
.L1290:

	bl	TmcPrintf
.L874:
	mov	r4,0
.L877:
	mov	r0,1
.L1292:

	bl	Timer_DelayMs
	add	r1,sp,4
	mov	r0,3
.L1294:

	bl	Adc_GetStreamLastPointer
	add	r4,r4,1
	cmp	r4,0x03e8
	bhs	.L875
	cmp	r0,5
	bne	.L877
.L875:
	mov	r0,3
.L1296:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	bne	.L879
	ldr	r1,.L1281
.L1298:

	bl	TmcPrintf
	mov	r5,0
.L883:
	add	r0,sp,2
	ldr	r1,.L1282
	ldrb	r2,[r0,r5]
	mov	r0,0
.L1300:

	bl	TmcPrintf
	mov	r4,1
.L888:
	ldr	r1,.L1283
	mov	r2,r4
	mov	r0,0
.L1302:

	bl	TmcPrintf
	ldr	r2,[sp,4]
	lsl	r0,r4,1
	ldr	r1,.L594
	ldrh	r2,[r0,r2]
	mov	r0,0
.L1304:

	bl	TmcPrintf
	ldr	r1,.L595
	mov	r0,0
.L1306:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,5
	bls	.L888
	add	r5,r5,1
	cmp	r5,2
	blo	.L883
	ldr	r1,.L244
	b	.L893
.L879:
	ldr	r1,.L245
.L893:
	mov	r0,0
.L1308:

	bl	TmcPrintf
	movw	r0,0x0179
.L1310:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
.L1312:

	bl	TmcPrintf
.LDW12:
	add	sp,sp,12
.L1314:

	pop	{r4-r5,pc}
__ghs_eofn_Adc_SyncGroupHwTrigDemo:
	.endf	Adc_SyncGroupHwTrigDemo
	.endf	Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

.L242:	.data.w	Adc_GtmTriggerCnt_0
	.endo	.L242

.L243:	.data.w	.L157
	.endo	.L243

.L244:	.data.w	.L155
	.endo	.L244

.L245:	.data.w	.L156
	.endo	.L245

.L246:	.data.w	.L154
	.endo	.L246

.L591:	.data.w	Adc_HwTrigStreamingResult
	.endo	.L591

.L592:	.data.w	.L453
	.endo	.L592

.L593:	.data.w	.L452
	.endo	.L593

.L594:	.data.w	.L451
	.endo	.L594

.L595:	.data.w	.L450
	.endo	.L595

.L1280:	.data.w	Adc_SyncGrpResult
	.endo	.L1280

.L1281:	.data.w	.L1141
	.endo	.L1281

.L1282:	.data.w	.L1140
	.endo	.L1282

.L1283:	.data.w	.L1139
	.endo	.L1283

;SyncGrpHwId	[sp,2]	local
;LoopCnt	r4	local
;Result	[sp,4]	local
;ValidNum	r0	local

	.section ".rodata","a"
.L1139:;	"\t - No. %d: "
	.data.b	9,32,45,32
	.data.b	78,111,46,32
	.data.b	37,100,58,32
	.data.b	0
	.endo	.L1139
	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SyncGrpResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SyncGrpResult:	.space	20
	.endo	Adc_SyncGrpResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SyncGrpResult
	.section ".rodata","a"
.L1140:;	"  - Sync group SARADC%d conversion results: \n"
	.data.b	32,32,45,32
	.data.b	83,121,110,99
	.data.b	32,103,114,111
	.data.b	117,112,32,83
	.data.b	65,82,65,68
	.data.b	67,37,100,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,32,114
	.data.b	101,115,117,108
	.data.b	116,115,58,32
	.data.b	10,0
	.endo	.L1140
.L1141:;	"\nSync group HW trigger with Linear Streaming conversion Result: \r\n"
	.data.b	10,83,121,110
	.data.b	99,32,103,114
	.data.b	111,117,112,32
	.data.b	72,87,32,116
	.data.b	114,105,103,103
	.data.b	101,114,32,119
	.data.b	105,116,104,32
	.data.b	76,105,110,101
	.data.b	97,114,32,83
	.data.b	116,114,101,97
	.data.b	109,105,110,103
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,32
	.data.b	82,101,115,117
	.data.b	108,116,58,32
	.data.b	13,10
	.data.b	0
	.endo	.L1141
	.section ".ghcalltbl",""
.L1285:	.data.w	.L1284
	.endo	.L1285
.L1287:	.data.w	.L1286
	.endo	.L1287
.L1289:	.data.w	.L1288
	.endo	.L1289
.L1291:	.data.w	.L1290
	.endo	.L1291
.L1293:	.data.w	.L1292
	.endo	.L1293
.L1295:	.data.w	.L1294
	.endo	.L1295
.L1297:	.data.w	.L1296
	.endo	.L1297
.L1299:	.data.w	.L1298
	.endo	.L1299
.L1301:	.data.w	.L1300
	.endo	.L1301
.L1303:	.data.w	.L1302
	.endo	.L1303
.L1305:	.data.w	.L1304
	.endo	.L1305
.L1307:	.data.w	.L1306
	.endo	.L1307
.L1309:	.data.w	.L1308
	.endo	.L1309
.L1311:	.data.w	.L1310
	.endo	.L1311
.L1313:	.data.w	.L1312
	.endo	.L1313
	.section ".ghrettbl",""
.L1315:	.data.w	.L1314
	.endo	.L1315
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetStreamLastPointer.i.ip

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_SwContinuousConversionCnt - Adc_SwContinuousConversionCnt) +0 == 0
	.assert 0x0 + (Adc_SwContinusBuffer - Adc_SwContinuousConversionCnt) +0 == 4
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigContinuousConversionDemo:
.LDW22:
	push	{r4-r6,lr}
	ldr	r4,.L1564
.LDW32:
	movw	r0,0x0185
.L1566:

	bl	Intc_EnableInterrupt
	mov	r0,0
	add	r1,r4,4
	str	r0,[r4]
	mov	r0,64
.L1568:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L1318
	mov	r0,64
.L1570:

	bl	Adc_EnableGroupNotification
	mov	r0,64
.L1572:

	bl	Adc_StartGroupConversion
	b	.L1320
.L1318:
	ldr	r1,.L243
	mov	r0,0
.L1574:

	bl	TmcPrintf
.L1320:
	mov	r5,0
.L1323:
	add	r5,r5,1
	mov	r0,1
.L1576:

	bl	Timer_DelayMs
	cmp	r5,0x03e8
	ldrlo	r0,[r4]
	cmplo	r0,5
	blo	.L1323
	ldr	r0,[r4]
	cmp	r0,5
	ldreq	r1,.L244
	ldrne	r1,.L1565
	mov	r0,0
.L1578:

	bl	TmcPrintf
	mov	r0,64
.L1580:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	movne	r0,64
.L1582:

	blne	Adc_StopGroupConversion
	movw	r0,0x0185
.L1584:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
	pop	{r4-r6,lr}
.L1586:

	b	TmcPrintf
.LDW42:
__ghs_eofn_Adc_SwTrigContinuousConversionDemo:
	.endf	Adc_SwTrigContinuousConversionDemo
	.endf	Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;LoopCnt	r5	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.space	2
	.align	4
Adc_SwContinuousConversionCnt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwContinuousConversionCnt:	.space	4
	.endo	Adc_SwContinuousConversionCnt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwContinuousConversionCnt
Adc_SwContinusBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwContinusBuffer:	.space	14
	.endo	Adc_SwContinusBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwContinusBuffer
	.section ".rodata","a"
.L1458:;	"\nTest Result = FAILED"
	.data.b	10,84,101,115
	.data.b	116,32,82,101
	.data.b	115,117,108,116
	.data.b	32,61,32,70
	.data.b	65,73,76,69
	.data.b	68,0
	.endo	.L1458
	.section ".ghcalltbl",""
.L1567:	.data.w	.L1566
	.endo	.L1567
.L1569:	.data.w	.L1568
	.endo	.L1569
.L1571:	.data.w	.L1570
	.endo	.L1571
.L1573:	.data.w	.L1572
	.endo	.L1573
.L1575:	.data.w	.L1574
	.endo	.L1575
.L1577:	.data.w	.L1576
	.endo	.L1577
.L1579:	.data.w	.L1578
	.endo	.L1579
.L1581:	.data.w	.L1580
	.endo	.L1581
.L1583:	.data.w	.L1582
	.endo	.L1583
.L1585:	.data.w	.L1584
	.endo	.L1585
	.section ".ghtailcalltbl",""
.L1587:	.data.w	.L1586
	.endo	.L1587
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_EnableGroupNotification.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigWithLimitCheckingDemo:
.LDW52:
	push	{r4,lr}
	sub	sp,sp,8
.LDW62:
	movw	r0,0x0185
.L1907:

	bl	Intc_EnableInterrupt
	ldr	r1,.L1903
	mov	r0,65
.L1909:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L1590
	mov	r0,65
.L1911:

	bl	Adc_StartGroupConversion
	b	.L1592
.L1590:
	ldr	r1,.L243
	mov	r0,0
.L1913:

	bl	TmcPrintf
.L1592:
	mov	r4,0
	b	.L1593
.L1595:
	mov	r0,65
.L1915:

	bl	Adc_StopGroupConversion
	mov	r0,65
.L1917:

	bl	Adc_StartGroupConversion
	add	r4,r4,1
.L1593:
	mov	r0,1
.L1919:

	bl	Timer_DelayMs
	mov	r0,65
.L1921:

	bl	Adc_GetGroupStatus
	cmp	r4,0x03e8
	bhs	.L1594
	cmp	r0,1
	beq	.L1595
.L1594:
	mov	r0,65
.L1923:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L1597
	add	r1,sp,6
	mov	r0,65
.L1925:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L1599
	ldr	r1,.L1904
.L1927:

	bl	TmcPrintf
	ldr	r1,.L594
	ldrh	r2,[sp,6]
	mov	r0,0
.L1929:

	bl	TmcPrintf
.L1599:
	ldr	r1,.L1905
	b	.L1601
.L1597:
	ldr	r1,.L1906
	mov	r0,0
.L1931:

	bl	TmcPrintf
	ldr	r1,.L245
.L1601:
	mov	r0,0
.L1933:

	bl	TmcPrintf
	mov	r0,65
.L1935:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	movne	r0,65
.L1937:

	blne	Adc_StopGroupConversion
	movw	r0,0x0185
.L1939:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
.L1941:

	bl	TmcPrintf
.LDW72:
	add	sp,sp,8
.L1943:

	pop	{r4,pc}
__ghs_eofn_Adc_SwTrigWithLimitCheckingDemo:
	.endf	Adc_SwTrigWithLimitCheckingDemo
	.endf	Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ConvResult	[sp,6]	local
;LoopCnt	r4	local
;ResultStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SwOneShotLimitChecking..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwOneShotLimitChecking:	.space	2
	.endo	Adc_SwOneShotLimitChecking..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwOneShotLimitChecking
	.section ".rodata","a"
.L1754:;	"\n\nTest Result = PASS"
	.data.b	10,10,84,101
	.data.b	115,116,32,82
	.data.b	101,115,117,108
	.data.b	116,32,61,32
	.data.b	80,65,83,83
	.data.b	0
	.endo	.L1754
.L1755:;	"\nSARADC2 LimitCheckGroup_0 conversion Results: "
	.data.b	10,83,65,82
	.data.b	65,68,67,50
	.data.b	32,76,105,109
	.data.b	105,116,67,104
	.data.b	101,99,107,71
	.data.b	114,111,117,112
	.data.b	95,48,32,99
	.data.b	111,110,118,101
	.data.b	114,115,105,111
	.data.b	110,32,82,101
	.data.b	115,117,108,116
	.data.b	115,58,32,0
	.endo	.L1755
.L1756:;	"\nNo conversion result in the range from 1500 to 3000."
	.data.b	10,78,111,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,32,114
	.data.b	101,115,117,108
	.data.b	116,32,105,110
	.data.b	32,116,104,101
	.data.b	32,114,97,110
	.data.b	103,101,32,102
	.data.b	114,111,109,32
	.data.b	49,53,48,48
	.data.b	32,116,111,32
	.data.b	51,48,48,48
	.data.b	46,0
	.endo	.L1756
	.section ".ghcalltbl",""
.L1908:	.data.w	.L1907
	.endo	.L1908
.L1910:	.data.w	.L1909
	.endo	.L1910
.L1912:	.data.w	.L1911
	.endo	.L1912
.L1914:	.data.w	.L1913
	.endo	.L1914
.L1916:	.data.w	.L1915
	.endo	.L1916
.L1918:	.data.w	.L1917
	.endo	.L1918
.L1920:	.data.w	.L1919
	.endo	.L1920
.L1922:	.data.w	.L1921
	.endo	.L1922
.L1924:	.data.w	.L1923
	.endo	.L1924
.L1926:	.data.w	.L1925
	.endo	.L1926
.L1928:	.data.w	.L1927
	.endo	.L1928
.L1930:	.data.w	.L1929
	.endo	.L1930
.L1932:	.data.w	.L1931
	.endo	.L1932
.L1934:	.data.w	.L1933
	.endo	.L1934
.L1936:	.data.w	.L1935
	.endo	.L1936
.L1938:	.data.w	.L1937
	.endo	.L1938
.L1940:	.data.w	.L1939
	.endo	.L1940
.L1942:	.data.w	.L1941
	.endo	.L1942
	.section ".ghrettbl",""
.L1944:	.data.w	.L1943
	.endo	.L1944
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigOneShotConversionDemo:
.LDW82:
	push	{r4,lr}
	sub	sp,sp,16
.LDW92:
	movw	r0,0x0186
.L2269:

	bl	Intc_EnableInterrupt
	ldr	r1,.L2267
	mov	r0,66
.L2271:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L1947
	mov	r0,66
.L2273:

	bl	Adc_StartGroupConversion
	b	.L1949
.L1947:
	ldr	r1,.L243
	mov	r0,0
.L2275:

	bl	TmcPrintf
.L1949:
	mov	r4,0
.L1952:
	add	r4,r4,1
	mov	r0,1
.L2277:

	bl	Timer_DelayMs
	mov	r0,66
.L2279:

	bl	Adc_GetGroupStatus
	cmp	r4,0x03e8
	cmpls	r0,1
	beq	.L1952
	mov	r0,66
.L2281:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L1954
	mov	r1,sp
	mov	r0,66
.L2283:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L1956
	ldr	r1,.L2268
.L2285:

	bl	TmcPrintf
	mov	r4,0
	b	.L1961
.L1960:
	lsl	r0,r4,1
	ldr	r1,.L594
	ldrh	r2,[r0,sp]
	mov	r0,0
.L2287:

	bl	TmcPrintf
	add	r4,r4,1
	uxtb	r4,r4
.L1961:
	cmp	r4,7
	blo	.L1960
.L1956:
	ldr	r1,.L1905
	b	.L1962
.L1954:
	ldr	r1,.L245
.L1962:
	mov	r0,0
.L2289:

	bl	TmcPrintf
	mov	r0,66
.L2291:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	movne	r0,66
.L2293:

	blne	Adc_StopGroupConversion
	movw	r0,0x0186
.L2295:

	bl	Intc_DisableInterrupt
	ldr	r1,.L246
	mov	r0,0
.L2297:

	bl	TmcPrintf
.LDW03:
	add	sp,sp,16
.L2299:

	pop	{r4,pc}
__ghs_eofn_Adc_SwTrigOneShotConversionDemo:
	.endf	Adc_SwTrigOneShotConversionDemo
	.endf	Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ChannelLoop	r4	local
;LoopCnt	r4	local
;Result	[sp]	local
;ResultStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SwOneShotBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwOneShotBuffer:	.space	14
	.endo	Adc_SwOneShotBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwOneShotBuffer
	.section ".rodata","a"
.L2114:;	"\nSARADC3 AdcGroupOneShot conversion Results: "
	.data.b	10,83,65,82
	.data.b	65,68,67,51
	.data.b	32,65,100,99
	.data.b	71,114,111,117
	.data.b	112,79,110,101
	.data.b	83,104,111,116
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,32
	.data.b	82,101,115,117
	.data.b	108,116,115,58
	.data.b	32,0
	.endo	.L2114
	.section ".ghcalltbl",""
.L2270:	.data.w	.L2269
	.endo	.L2270
.L2272:	.data.w	.L2271
	.endo	.L2272
.L2274:	.data.w	.L2273
	.endo	.L2274
.L2276:	.data.w	.L2275
	.endo	.L2276
.L2278:	.data.w	.L2277
	.endo	.L2278
.L2280:	.data.w	.L2279
	.endo	.L2280
.L2282:	.data.w	.L2281
	.endo	.L2282
.L2284:	.data.w	.L2283
	.endo	.L2284
.L2286:	.data.w	.L2285
	.endo	.L2286
.L2288:	.data.w	.L2287
	.endo	.L2288
.L2290:	.data.w	.L2289
	.endo	.L2290
.L2292:	.data.w	.L2291
	.endo	.L2292
.L2294:	.data.w	.L2293
	.endo	.L2294
.L2296:	.data.w	.L2295
	.endo	.L2296
.L2298:	.data.w	.L2297
	.endo	.L2298
	.section ".ghrettbl",""
.L2300:	.data.w	.L2299
	.endo	.L2300
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_SwStreamingBuffer - Adc_SwStreamingBuffer) +2 == 2
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
	.global	Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigContinuousStreamingDemo:
.LDW13:
	push	{r4-r6,lr}
	sub	sp,sp,8
	ldr	r5,.L2669
.LDW23:
	movw	r0,0x0187
.L2675:

	bl	Intc_EnableInterrupt
	add	r4,r5,2
	mov	r0,67
	mov	r1,r4
.L2677:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L2303
	mov	r0,67
.L2679:

	bl	Adc_StartGroupConversion
	b	.L2305
.L2303:
	ldr	r1,.L243
	mov	r0,0
.L2681:

	bl	TmcPrintf
.L2305:
	mov	r5,0
.L2308:
	mov	r0,1
.L2683:

	bl	Timer_DelayMs
	add	r1,sp,4
	mov	r0,67
.L2685:

	bl	Adc_GetStreamLastPointer
	add	r5,r5,1
	cmp	r5,0x03e8
	bhs	.L2306
	cmp	r0,5
	bne	.L2308
.L2306:
	mov	r0,67
.L2687:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	bne	.L2310
	ldr	r1,.L2670
.L2689:

	bl	TmcPrintf
	mov	r5,0
.L2314:
	ldr	r1,.L593
	mov	r2,r5
	mov	r0,0
.L2691:

	bl	TmcPrintf
	mov	r6,0
.L2319:
	add	r0,r6,r6 lsl 2
	add	r0,r0,r5
	lsl	r0,r0,1
	ldr	r1,.L594
	ldrh	r2,[r0,r4]
	mov	r0,0
.L2693:

	bl	TmcPrintf
	add	r6,r6,1
	cmp	r6,4
	blo	.L2319
	ldr	r1,.L2671
	mov	r0,0
.L2695:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,5
	blo	.L2314
	ldr	r1,.L2672
	b	.L2320

.L1564:	.data.w	Adc_SwContinuousConversionCnt
	.endo	.L1564

.L1565:	.data.w	.L1458
	.endo	.L1565

.L1903:	.data.w	Adc_SwOneShotLimitChecking
	.endo	.L1903

.L1904:	.data.w	.L1755
	.endo	.L1904

.L1905:	.data.w	.L1754
	.endo	.L1905

.L1906:	.data.w	.L1756
	.endo	.L1906

.L2267:	.data.w	Adc_SwOneShotBuffer
	.endo	.L2267

.L2268:	.data.w	.L2114
	.endo	.L2268

.L2669:	.data.w	Adc_SwStreamingBuffer-2
	.endo	.L2669

.L2670:	.data.w	.L2516
	.endo	.L2670

.L2671:	.data.w	.L450
	.endo	.L2671

.L2672:	.data.w	.L155
	.endo	.L2672

.L2673:	.data.w	.L156
	.endo	.L2673

.L2310:
;line830
..lin.87a640f4..bc0e9432.1_1::
.LDWlin1:
	ldr	r1,.L2673
.L2320:
	mov	r0,0
.L2697:

	bl	TmcPrintf
	mov	r0,67
.L2699:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	movne	r0,67
.L2701:

	blne	Adc_StopGroupConversion
	movw	r0,0x0187
.L2703:

	bl	Intc_DisableInterrupt
	ldr	r1,.L2674
	mov	r0,0
.L2705:

	bl	TmcPrintf
.LDW33:
	add	sp,sp,8
.L2707:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_SwTrigContinuousStreamingDemo:
	.endf	Adc_SwTrigContinuousStreamingDemo
	.endf	Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ResultPtr	[sp,4]	local
;LoopCnt	r5	local
;ValidNum	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SwStreamingBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwStreamingBuffer:	.space	40
	.endo	Adc_SwStreamingBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwStreamingBuffer
	.section ".rodata","a"
.L2516:;	"\nSARADC2 SW trigger Linear Streaming Result: \r\n"
	.data.b	10,83,65,82
	.data.b	65,68,67,50
	.data.b	32,83,87,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	76,105,110,101
	.data.b	97,114,32,83
	.data.b	116,114,101,97
	.data.b	109,105,110,103
	.data.b	32,82,101,115
	.data.b	117,108,116,58
	.data.b	32,13,10,0
	.endo	.L2516
	.section ".ghcalltbl",""
.L2676:	.data.w	.L2675
	.endo	.L2676
.L2678:	.data.w	.L2677
	.endo	.L2678
.L2680:	.data.w	.L2679
	.endo	.L2680
.L2682:	.data.w	.L2681
	.endo	.L2682
.L2684:	.data.w	.L2683
	.endo	.L2684
.L2686:	.data.w	.L2685
	.endo	.L2686
.L2688:	.data.w	.L2687
	.endo	.L2688
.L2690:	.data.w	.L2689
	.endo	.L2690
.L2692:	.data.w	.L2691
	.endo	.L2692
.L2694:	.data.w	.L2693
	.endo	.L2694
.L2696:	.data.w	.L2695
	.endo	.L2696
.L2698:	.data.w	.L2697
	.endo	.L2698
.L2700:	.data.w	.L2699
	.endo	.L2700
.L2702:	.data.w	.L2701
	.endo	.L2702
.L2704:	.data.w	.L2703
	.endo	.L2704
.L2706:	.data.w	.L2705
	.endo	.L2706
	.section ".ghrettbl",""
.L2708:	.data.w	.L2707
	.endo	.L2708
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetStreamLastPointer.i.ip

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigOneShotConversionResultAccumuDemo:
.LDW43:
	push	{r4,lr}
	sub	sp,sp,16
.LDW53:
	movw	r0,0x0185
.L3036:

	bl	Intc_EnableInterrupt
	ldr	r1,.L2267
	mov	r0,68
.L3038:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L2711
	mov	r0,68
.L3040:

	bl	Adc_StartGroupConversion
	b	.L2713
.L2711:
	ldr	r1,.L3034
	mov	r0,0
.L3042:

	bl	TmcPrintf
.L2713:
	mov	r4,0
.L2716:
	add	r4,r4,1
	mov	r0,1
.L3044:

	bl	Timer_DelayMs
	mov	r0,68
.L3046:

	bl	Adc_GetGroupStatus
	movw	r1,0x1388
	cmp	r4,r1
	cmpls	r0,1
	beq	.L2716
	mov	r0,68
.L3048:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L2718
	mov	r1,sp
	mov	r0,68
.L3050:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L2720
	ldr	r1,.L2268
.L3052:

	bl	TmcPrintf
	mov	r4,0
	b	.L2725
.L2724:
	lsl	r0,r4,1
	ldr	r1,.L3035
	ldrh	r2,[r0,sp]
	mov	r0,0
.L3054:

	bl	TmcPrintf
	add	r4,r4,1
	uxtb	r4,r4
.L2725:
	cmp	r4,7
	blo	.L2724
.L2720:
	ldr	r1,.L1905
	b	.L2726
.L2718:
	ldr	r1,.L2673
.L2726:
	mov	r0,0
.L3056:

	bl	TmcPrintf
	mov	r0,68
.L3058:

	bl	Adc_GetGroupStatus
	cmp	r0,0
	movne	r0,68
.L3060:

	blne	Adc_StopGroupConversion
	movw	r0,0x0185
.L3062:

	bl	Intc_DisableInterrupt
	ldr	r1,.L2674
	mov	r0,0
.L3064:

	bl	TmcPrintf
.LDW63:
	add	sp,sp,16
.L3066:

	pop	{r4,pc}
__ghs_eofn_Adc_SwTrigOneShotConversionResultAccumuDemo:
	.endf	Adc_SwTrigOneShotConversionResultAccumuDemo
	.endf	Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ChannelLoop	r4	local
;LoopCnt	r4	local
;Result	[sp]	local
;ResultStatus	r0	local

	.section ".ghcalltbl",""
.L3037:	.data.w	.L3036
	.endo	.L3037
.L3039:	.data.w	.L3038
	.endo	.L3039
.L3041:	.data.w	.L3040
	.endo	.L3041
.L3043:	.data.w	.L3042
	.endo	.L3043
.L3045:	.data.w	.L3044
	.endo	.L3045
.L3047:	.data.w	.L3046
	.endo	.L3047
.L3049:	.data.w	.L3048
	.endo	.L3049
.L3051:	.data.w	.L3050
	.endo	.L3051
.L3053:	.data.w	.L3052
	.endo	.L3053
.L3055:	.data.w	.L3054
	.endo	.L3055
.L3057:	.data.w	.L3056
	.endo	.L3057
.L3059:	.data.w	.L3058
	.endo	.L3059
.L3061:	.data.w	.L3060
	.endo	.L3061
.L3063:	.data.w	.L3062
	.endo	.L3063
.L3065:	.data.w	.L3064
	.endo	.L3065
	.section ".ghrettbl",""
.L3067:	.data.w	.L3066
	.endo	.L3067
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.global	Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigPollingSingleDemo:
.LDW73:
	push	{r4-r5,lr}
	sub	sp,sp,20
.LDW83:
	mov	r4,0
	b	.L3073
.L3072:
	lsl	r0,r4,1
	add	r4,r4,1
	mvn	r2,0
	uxtb	r4,r4
	strh	r2,[r0,sp]
.L3073:
	cmp	r4,7
	blo	.L3072
	ldr	r1,.L3425
	movw	r0,0x0102
.L3428:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L3074
	movw	r0,0x0102
.L3430:

	bl	Adc_StartGroupConversion
	b	.L3076
.L3074:
	ldr	r1,.L3426
	mov	r0,0
.L3432:

	bl	TmcPrintf
.L3076:
	mov	r4,0
.L3079:
	add	r4,r4,1
	movw	r0,0x0102
.L3434:

	bl	Adc_GetGroupStatus
	cmp	r4,0x03e8
	cmpls	r0,1
	beq	.L3079
	movw	r0,0x0102
.L3436:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L3081
	mov	r5,sp
	movw	r0,0x0102
	mov	r1,r5
.L3438:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L3083
	ldr	r1,.L3427
.L3440:

	bl	TmcPrintf
	mov	r4,0
	b	.L3088
.L3087:
	lsl	r0,r4,1
	ldr	r1,.L3035
	ldrh	r2,[r0,r5]
	mov	r0,0
.L3442:

	bl	TmcPrintf
	add	r4,r4,1
	uxtb	r4,r4
.L3088:
	cmp	r4,7
	blo	.L3087
.L3083:
	ldr	r1,.L1905
	b	.L3089
.L3081:
	ldr	r1,.L2673
.L3089:
	mov	r0,0
.L3444:

	bl	TmcPrintf
	ldr	r1,.L2674
	mov	r0,0
.L3446:

	bl	TmcPrintf
.LDW93:
	add	sp,sp,20
.L3448:

	pop	{r4-r5,pc}
__ghs_eofn_Adc_SwTrigPollingSingleDemo:
	.endf	Adc_SwTrigPollingSingleDemo
	.endf	Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ChannelLoop	r4	local
;Result	[sp]	local
;LoopCnt	r4	local
;ResultStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwPollingSingleResult:	.space	14
	.endo	Adc_SwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwPollingSingleResult
	.section ".rodata","a"
.L3258:;	"\nSetup result buffer fail"
	.data.b	10,83,101,116
	.data.b	117,112,32,114
	.data.b	101,115,117,108
	.data.b	116,32,98,117
	.data.b	102,102,101,114
	.data.b	32,102,97,105
	.data.b	108,0
	.endo	.L3258
.L3259:;	"\nSARADC8 polling mode; SW trigger conversion Results: "
	.data.b	10,83,65,82
	.data.b	65,68,67,56
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,59,32,83
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,82,101,115
	.data.b	117,108,116,115
	.data.b	58,32
	.data.b	0
	.endo	.L3259
	.section ".ghcalltbl",""
.L3429:	.data.w	.L3428
	.endo	.L3429
.L3431:	.data.w	.L3430
	.endo	.L3431
.L3433:	.data.w	.L3432
	.endo	.L3433
.L3435:	.data.w	.L3434
	.endo	.L3435
.L3437:	.data.w	.L3436
	.endo	.L3437
.L3439:	.data.w	.L3438
	.endo	.L3439
.L3441:	.data.w	.L3440
	.endo	.L3441
.L3443:	.data.w	.L3442
	.endo	.L3443
.L3445:	.data.w	.L3444
	.endo	.L3445
.L3447:	.data.w	.L3446
	.endo	.L3447
	.section ".ghrettbl",""
.L3449:	.data.w	.L3448
	.endo	.L3449
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
	.global	Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_HwTrigPollingSingleDemo:
.LDW04:
	push	{r4-r5,lr}
	sub	sp,sp,20
.LDW14:
	mov	r4,0
	b	.L3455
.L3454:
	lsl	r0,r4,1
	add	r4,r4,1
	mvn	r2,0
	uxtb	r4,r4
	strh	r2,[r0,sp]
.L3455:
	cmp	r4,7
	blo	.L3454
	ldr	r1,.L3793
	mov	r0,256
.L3796:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L3456
	mov	r0,256
.L3798:

	bl	Adc_EnableHardwareTrigger
	b	.L3458
.L3456:
	ldr	r1,.L3794
	mov	r0,0
.L3800:

	bl	TmcPrintf
.L3458:
	mov	r4,0
.L3461:
	add	r4,r4,1
	mov	r0,1
.L3802:

	bl	Timer_DelayMs
	mov	r0,256
.L3804:

	bl	Adc_GetGroupStatus
	cmp	r4,0x03e8
	cmpls	r0,1
	beq	.L3461
	mov	r0,256
.L3806:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L3463
	mov	r5,sp
	mov	r0,256
	mov	r1,r5
.L3808:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L3465
	ldr	r1,.L3795
.L3810:

	bl	TmcPrintf
	mov	r4,0
	b	.L3470
.L3469:
	lsl	r0,r4,1
	ldr	r1,.L3035
	ldrh	r2,[r0,r5]
	mov	r0,0
.L3812:

	bl	TmcPrintf
	add	r4,r4,1
	uxtb	r4,r4
.L3470:
	cmp	r4,8
	blo	.L3469
.L3465:
	ldr	r1,.L1905
	b	.L3471
.L3463:
	ldr	r1,.L2673
.L3471:
	mov	r0,0
.L3814:

	bl	TmcPrintf
	mov	r0,256
.L3816:

	bl	Adc_DisableHardwareTrigger
	ldr	r1,.L2674
	mov	r0,0
.L3818:

	bl	TmcPrintf
.LDW24:
	add	sp,sp,20
.L3820:

	pop	{r4-r5,pc}
__ghs_eofn_Adc_HwTrigPollingSingleDemo:
	.endf	Adc_HwTrigPollingSingleDemo
	.endf	Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ChannelLoop	r4	local
;Result	[sp]	local
;LoopCnt	r4	local
;ResultStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_HwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_HwPollingSingleResult:	.space	16
	.endo	Adc_HwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_HwPollingSingleResult
	.section ".rodata","a"
.L3626:;	"\nSARADC8 Setup result buffer fail"
	.data.b	10,83,65,82
	.data.b	65,68,67,56
	.data.b	32,83,101,116
	.data.b	117,112,32,114
	.data.b	101,115,117,108
	.data.b	116,32,98,117
	.data.b	102,102,101,114
	.data.b	32,102,97,105
	.data.b	108,0
	.endo	.L3626
.L3627:;	"\nSARADC8 polling mode; HW trigger conversion Results: "
	.data.b	10,83,65,82
	.data.b	65,68,67,56
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,59,32,72
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,82,101,115
	.data.b	117,108,116,115
	.data.b	58,32
	.data.b	0
	.endo	.L3627
	.section ".ghcalltbl",""
.L3797:	.data.w	.L3796
	.endo	.L3797
.L3799:	.data.w	.L3798
	.endo	.L3799
.L3801:	.data.w	.L3800
	.endo	.L3801
.L3803:	.data.w	.L3802
	.endo	.L3803
.L3805:	.data.w	.L3804
	.endo	.L3805
.L3807:	.data.w	.L3806
	.endo	.L3807
.L3809:	.data.w	.L3808
	.endo	.L3809
.L3811:	.data.w	.L3810
	.endo	.L3811
.L3813:	.data.w	.L3812
	.endo	.L3813
.L3815:	.data.w	.L3814
	.endo	.L3815
.L3817:	.data.w	.L3816
	.endo	.L3817
.L3819:	.data.w	.L3818
	.endo	.L3819
	.section ".ghrettbl",""
.L3821:	.data.w	.L3820
	.endo	.L3821
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_DisableHardwareTrigger.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_SwPollingStreamingResult - Adc_SwPollingStreamingResult) +0 == 0
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
	.global	Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigPollingStreamingDemo:
.LDW34:
	push	{r4-r6,lr}
	sub	sp,sp,8
	ldr	r6,.L4171
.LDW44:
	mov	r4,0
	movw	r0,0x0103
	mov	r1,r6
.L4178:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L3824
	movw	r0,0x0103
.L4180:

	bl	Adc_StartGroupConversion
	b	.L3829
.L3824:
	ldr	r1,.L3426
	mov	r0,r4
.L4182:

	bl	TmcPrintf
.L3829:
	add	r4,r4,1
	movw	r0,0x0103
.L4184:

	bl	Adc_GetGroupStatus
	cmp	r4,0x03e8
	bhi	.L3827
	cmp	r0,3
	bne	.L3829
.L3827:
	movw	r0,0x0103
.L4186:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L3831
	add	r1,sp,4
	movw	r0,0x0103
.L4188:

	bl	Adc_GetStreamLastPointer
	cmp	r0,5
	bne	.L3831
	ldr	r1,.L4172
	mov	r0,0
.L4190:

	bl	TmcPrintf
	mov	r4,0
.L3837:
	ldr	r1,.L4173
	mov	r2,r4
	mov	r0,0
.L4192:

	bl	TmcPrintf
	mov	r5,0
.L3842:
	add	r0,r5,r5 lsl 2
	add	r0,r0,r4
	lsl	r0,r0,1
	b	.L4174

.L2674:	.data.w	.L154
	.endo	.L2674

.L3034:	.data.w	.L157
	.endo	.L3034

.L3035:	.data.w	.L451
	.endo	.L3035

.L3425:	.data.w	Adc_SwPollingSingleResult
	.endo	.L3425

.L3426:	.data.w	.L3258
	.endo	.L3426

.L3427:	.data.w	.L3259
	.endo	.L3427

.L3793:	.data.w	Adc_HwPollingSingleResult
	.endo	.L3793

.L3794:	.data.w	.L3626
	.endo	.L3794

.L3795:	.data.w	.L3627
	.endo	.L3795

.L4171:	.data.w	Adc_SwPollingStreamingResult
	.endo	.L4171

.L4172:	.data.w	.L4030
	.endo	.L4172

.L4173:	.data.w	.L452
	.endo	.L4173

.L4174:

;line1157
..lin.87a640f4..99d5d670.1_2::
.LDWlin2:
	ldr	r1,.L3035
	ldrh	r2,[r0,r6]
	mov	r0,0
.L4194:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,3
	blo	.L3842
	ldr	r1,.L4175
	mov	r0,0
.L4196:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,5
	blo	.L3837
	ldr	r1,.L4176
	b	.L3844
.L3831:
	ldr	r1,.L4177
.L3844:
	mov	r0,0
.L4198:

	bl	TmcPrintf
	ldr	r1,.L2674
	mov	r0,0
.L4200:

	bl	TmcPrintf
.LDW54:
	add	sp,sp,8
.L4202:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_SwTrigPollingStreamingDemo:
	.endf	Adc_SwTrigPollingStreamingDemo
	.endf	Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ResultPtr	[sp,4]	local
;LoopCnt	r4	local
;ReturnStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_SwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_SwPollingStreamingResult:	.space	30
	.endo	Adc_SwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_SwPollingStreamingResult
	.section ".rodata","a"
.L4030:;	"\nSARADC8 polling mode; SW trigger Linear Streaming Result: \r\n"
	.data.b	10,83,65,82
	.data.b	65,68,67,56
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,59,32,83
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,76,105
	.data.b	110,101,97,114
	.data.b	32,83,116,114
	.data.b	101,97,109,105
	.data.b	110,103,32,82
	.data.b	101,115,117,108
	.data.b	116,58,32,13
	.data.b	10,0
	.endo	.L4030
	.section ".ghcalltbl",""
.L4179:	.data.w	.L4178
	.endo	.L4179
.L4181:	.data.w	.L4180
	.endo	.L4181
.L4183:	.data.w	.L4182
	.endo	.L4183
.L4185:	.data.w	.L4184
	.endo	.L4185
.L4187:	.data.w	.L4186
	.endo	.L4187
.L4189:	.data.w	.L4188
	.endo	.L4189
.L4191:	.data.w	.L4190
	.endo	.L4191
.L4193:	.data.w	.L4192
	.endo	.L4193
.L4195:	.data.w	.L4194
	.endo	.L4195
.L4197:	.data.w	.L4196
	.endo	.L4197
.L4199:	.data.w	.L4198
	.endo	.L4199
.L4201:	.data.w	.L4200
	.endo	.L4201
	.section ".ghrettbl",""
.L4203:	.data.w	.L4202
	.endo	.L4203
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetStreamLastPointer.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_HwPollingStreamingResult - Adc_HwPollingStreamingResult) +2 == 2
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.global	Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_HwTrigPollingStreamingDemo:
.LDW64:
	push	{r4-r6,lr}
	sub	sp,sp,8
	ldr	r12,.L4561
.LDW74:
	add	r4,r12,2
	movw	r0,0x0101
	mov	r1,r4
.L4563:

	bl	Adc_SetupResultBuffer
	cmp	r0,0
	bne	.L4206
	movw	r0,0x0101
.L4565:

	bl	Adc_EnableHardwareTrigger
	b	.L4208
.L4206:
	ldr	r1,.L3426
	mov	r0,0
.L4567:

	bl	TmcPrintf
.L4208:
	mov	r5,0
.L4211:
	add	r5,r5,1
	mov	r0,1
.L4569:

	bl	Timer_DelayMs
	movw	r0,0x0101
.L4571:

	bl	Adc_GetGroupStatus
	cmp	r5,0x03e8
	bhi	.L4209
	cmp	r0,3
	bne	.L4211
.L4209:
	movw	r0,0x0101
.L4573:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	bne	.L4213
	add	r1,sp,4
	movw	r0,0x0101
.L4575:

	bl	Adc_GetStreamLastPointer
	cmp	r0,5
	bne	.L4213
	ldr	r1,.L4562
	mov	r0,0
.L4577:

	bl	TmcPrintf
	mov	r5,0
.L4219:
	ldr	r1,.L4173
	mov	r2,r5
	mov	r0,0
.L4579:

	bl	TmcPrintf
	mov	r6,0
.L4224:
	add	r0,r6,r6 lsl 2
	add	r0,r0,r5
	lsl	r0,r0,1
	ldr	r1,.L3035
	ldrh	r2,[r0,r4]
	mov	r0,0
.L4581:

	bl	TmcPrintf
	add	r6,r6,1
	cmp	r6,5
	blo	.L4224
	ldr	r1,.L4175
	mov	r0,0
.L4583:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,5
	blo	.L4219
	ldr	r1,.L4176
	b	.L4226
.L4213:
	ldr	r1,.L4177
.L4226:
	mov	r0,0
.L4585:

	bl	TmcPrintf
	ldr	r1,.L2674
	mov	r0,0
.L4587:

	bl	TmcPrintf
.LDW84:
	add	sp,sp,8
.L4589:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_HwTrigPollingStreamingDemo:
	.endf	Adc_HwTrigPollingStreamingDemo
	.endf	Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;ResultPtr	[sp,4]	local
;LoopCnt	r5	local
;ReturnStatus	r0	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Adc_HwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_HwPollingStreamingResult:	.space	50
	.endo	Adc_HwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_HwPollingStreamingResult
	.section ".rodata","a"
.L4414:;	"\nSARADC8 polling mode; HW trigger Linear Streaming Result: \r\n"
	.data.b	10,83,65,82
	.data.b	65,68,67,56
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,59,32,72
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,76,105
	.data.b	110,101,97,114
	.data.b	32,83,116,114
	.data.b	101,97,109,105
	.data.b	110,103,32,82
	.data.b	101,115,117,108
	.data.b	116,58,32,13
	.data.b	10,0
	.endo	.L4414
	.section ".ghcalltbl",""
.L4564:	.data.w	.L4563
	.endo	.L4564
.L4566:	.data.w	.L4565
	.endo	.L4566
.L4568:	.data.w	.L4567
	.endo	.L4568
.L4570:	.data.w	.L4569
	.endo	.L4570
.L4572:	.data.w	.L4571
	.endo	.L4572
.L4574:	.data.w	.L4573
	.endo	.L4574
.L4576:	.data.w	.L4575
	.endo	.L4576
.L4578:	.data.w	.L4577
	.endo	.L4578
.L4580:	.data.w	.L4579
	.endo	.L4580
.L4582:	.data.w	.L4581
	.endo	.L4582
.L4584:	.data.w	.L4583
	.endo	.L4584
.L4586:	.data.w	.L4585
	.endo	.L4586
.L4588:	.data.w	.L4587
	.endo	.L4588
	.section ".ghrettbl",""
.L4590:	.data.w	.L4589
	.endo	.L4590
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetStreamLastPointer.i.ip

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_EnableHardwareTrigger.v.i

	.global	__caller.Adc_SetupResultBuffer.i.ip

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
	.global	Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigDmaTransferDemo:
.LDW94:
	push	{r4-r6,lr}
.LDW05:
	ldr	r0,.L4998
.L5002:

	bl	Dma_Init
	mov	r0,9
.L5004:

	bl	Dma_ChannelStart
	mov	r0,10
.L5006:

	bl	Dma_ChannelStart
	mov	r0,11
.L5008:

	bl	Dma_ChannelStart
	mov	r0,12
.L5010:

	bl	Dma_ChannelStart
	mov	r4,0
	mov	r6,5
.L4783:
	mov	r0,32
.L5012:

	bl	Adc_StartGroupConversion
	mov	r5,0
.L4784:
	add	r5,r5,1
	mov	r0,1
.L5014:

	bl	Timer_DelayMs
	mov	r0,32
.L5016:

	bl	Adc_GetGroupStatus
	cmp	r5,0x03e8
	bhi	.L4786
	cmp	r0,3
	bne	.L4784
.L4786:
	mov	r0,32
.L5018:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	beq	.L4788
	ldr	r1,.L4177
	mov	r0,0
.L5020:

	bl	TmcPrintf
	b	.L4604
.L4788:
	add	r4,r4,1
	subs	r6,r6,1
	bne	.L4783
.L4604:
	uxtb	r0,r4
	cmp	r0,5
	bne	.L4606
	ldr	r1,.L4999
	mov	r0,0
.L5022:

	bl	TmcPrintf
	mov	r4,0
.L4610:
	ldr	r1,.L5000
	mov	r2,r4
	mov	r0,0
.L5024:

	bl	TmcPrintf
	mov	r5,0
.L4615:
	add	r0,r4,r4 lsl 2
	add	r0,r5,r0
	ldr	r2,.L5001
	lsl	r0,r0,1
	ldr	r1,.L3035
	ldrh	r2,[r0,r2]
	mov	r0,0
.L5026:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,5
	blo	.L4615
	ldr	r1,.L2674
	mov	r0,0
.L5028:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,4
	blo	.L4610
	ldr	r1,.L4176
	mov	r0,0
.L5030:

	bl	TmcPrintf
.L4606:
	ldr	r1,.L2674
	mov	r0,0
.L5032:

	bl	TmcPrintf
	mov	r1,0
	mov	r0,9
.L5034:

	bl	Dma_ChannelCancel
	mov	r1,0
	mov	r0,10
.L5036:

	bl	Dma_ChannelCancel
	mov	r1,0
	mov	r0,11
.L5038:

	bl	Dma_ChannelCancel
	mov	r1,0
	mov	r0,12
.L5040:

	bl	Dma_ChannelCancel
	pop	{r4-r6,lr}
.L5042:

	b	Dma_DeInit
.LDW15:
__ghs_eofn_Adc_SwTrigDmaTransferDemo:
	.endf	Adc_SwTrigDmaTransferDemo
	.endf	Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;LoopCnt	r5	local
;ReturnStatus	r0	local

	.section ".rodata","a"
.L4859:;	"ADC1 Channel%d:"
	.data.b	65,68,67,49
	.data.b	32,67,104,97
	.data.b	110,110,101,108
	.data.b	37,100,58,0
	.endo	.L4859
.L4860:;	"\nSARADC1 DMA mode; SW trigger one-shot Result: \r\n"
	.data.b	10,83,65,82
	.data.b	65,68,67,49
	.data.b	32,68,77,65
	.data.b	32,109,111,100
	.data.b	101,59,32,83
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,111,110
	.data.b	101,45,115,104
	.data.b	111,116,32,82
	.data.b	101,115,117,108
	.data.b	116,58,32,13
	.data.b	10,0
	.endo	.L4860
	.section ".ghcalltbl",""
.L5003:	.data.w	.L5002
	.endo	.L5003
.L5005:	.data.w	.L5004
	.endo	.L5005
.L5007:	.data.w	.L5006
	.endo	.L5007
.L5009:	.data.w	.L5008
	.endo	.L5009
.L5011:	.data.w	.L5010
	.endo	.L5011
.L5013:	.data.w	.L5012
	.endo	.L5013
.L5015:	.data.w	.L5014
	.endo	.L5015
.L5017:	.data.w	.L5016
	.endo	.L5017
.L5019:	.data.w	.L5018
	.endo	.L5019
.L5021:	.data.w	.L5020
	.endo	.L5021
.L5023:	.data.w	.L5022
	.endo	.L5023
.L5025:	.data.w	.L5024
	.endo	.L5025
.L5027:	.data.w	.L5026
	.endo	.L5027
.L5029:	.data.w	.L5028
	.endo	.L5029
.L5031:	.data.w	.L5030
	.endo	.L5031
.L5033:	.data.w	.L5032
	.endo	.L5033
.L5035:	.data.w	.L5034
	.endo	.L5035
.L5037:	.data.w	.L5036
	.endo	.L5037
.L5039:	.data.w	.L5038
	.endo	.L5039
.L5041:	.data.w	.L5040
	.endo	.L5041
	.section ".ghtailcalltbl",""
.L5043:	.data.w	.L5042
	.endo	.L5043
	.data
	.global	__caller.Dma_DeInit.v.v

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_Init.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
	.global	Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigDmaTransferWithDaisyChainDemo:
.LDW25:
	push	{r4-r6,lr}
.LDW35:
	ldr	r0,.L4998
.L5340:

	bl	Dma_Init
	mov	r0,13
.L5342:

	bl	Dma_ChannelStart
	ldr	r1,.L5338
	mov	r0,0
.L5344:

	bl	TmcPrintf
	mov	r4,0
.L5048:
	mov	r0,33
.L5346:

	bl	Adc_StartGroupConversion
	mov	r5,0
.L5052:
	add	r5,r5,1
	mov	r0,1
.L5348:

	bl	Timer_DelayMs
	mov	r0,33
.L5350:

	bl	Adc_GetGroupStatus
	cmp	r5,0x03e8
	bhi	.L5050
	cmp	r0,3
	bne	.L5052
.L5050:
	mov	r0,33
.L5352:

	bl	Adc_GetGroupStatus
	cmp	r0,3
	mov	r0,0
	bne	.L5054
	ldr	r1,.L5339
	mov	r2,r4
.L5354:

	bl	TmcPrintf
	mov	r5,0
.L5059:
	ldr	r2,.L5001
	lsl	r0,r5,1
	ldr	r1,.L3035
	ldrh	r2,[r0,r2]
	mov	r0,0
.L5356:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,4
	blo	.L5059
	ldr	r1,.L2674
	mov	r0,0
.L5358:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,5
	blo	.L5048
	b	.L5061
.L5054:
	ldr	r1,.L4177
.L5360:

	bl	TmcPrintf
.L5061:
	uxtb	r0,r4
	cmp	r0,5
	ldreq	r1,.L4176
	moveq	r0,0
.L5362:

	bleq	TmcPrintf
	ldr	r1,.L2674
	mov	r0,0
.L5364:

	bl	TmcPrintf
	mov	r1,0
	mov	r0,13
.L5366:

	bl	Dma_ChannelCancel
	pop	{r4-r6,lr}
.L5368:

	b	Dma_DeInit
.LDW45:
__ghs_eofn_Adc_SwTrigDmaTransferWithDaisyChainDemo:
	.endf	Adc_SwTrigDmaTransferWithDaisyChainDemo
	.endf	Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

.L4175:	.data.w	.L450
	.endo	.L4175

.L4176:	.data.w	.L155
	.endo	.L4176

.L4177:	.data.w	.L156
	.endo	.L4177

.L4561:	.data.w	Adc_HwPollingStreamingResult-2
	.endo	.L4561

.L4562:	.data.w	.L4414
	.endo	.L4562

.L4998:	.data.w	Dma_ConfigSet
	.endo	.L4998

.L4999:	.data.w	.L4860
	.endo	.L4999

.L5000:	.data.w	.L4859
	.endo	.L5000

.L5001:	.data.w	Adc_DmaTransferSwTrigResult
	.endo	.L5001

.L5338:	.data.w	.L5218
	.endo	.L5338

.L5339:	.data.w	.L5217
	.endo	.L5339

;LoopCnt	r5	local
;ReturnStatus	r0	local

	.section ".rodata","a"
.L5217:;	"%d Sampled:"
	.data.b	37,100,32,83
	.data.b	97,109,112,108
	.data.b	101,100,58,0
	.endo	.L5217
.L5218:;	"\nSARADC1 DMA mode with daisy chain and linked list; SW trigger one-sh..."
	.data.b	10,83,65,82
	.data.b	65,68,67,49
	.data.b	32,68,77,65
	.data.b	32,109,111,100
	.data.b	101,32,119,105
	.data.b	116,104,32,100
	.data.b	97,105,115,121
	.data.b	32,99,104,97
	.data.b	105,110,32,97
	.data.b	110,100,32,108
	.data.b	105,110,107,101
	.data.b	100,32,108,105
	.data.b	115,116,59,32
	.data.b	83,87,32,116
	.data.b	114,105,103,103
	.data.b	101,114,32,111
	.data.b	110,101,45,115
	.data.b	104,111,116,32
	.data.b	82,101,115,117
	.data.b	108,116,58,32
	.data.b	13,10
	.data.b	0
	.endo	.L5218
	.section ".ghcalltbl",""
.L5341:	.data.w	.L5340
	.endo	.L5341
.L5343:	.data.w	.L5342
	.endo	.L5343
.L5345:	.data.w	.L5344
	.endo	.L5345
.L5347:	.data.w	.L5346
	.endo	.L5347
.L5349:	.data.w	.L5348
	.endo	.L5349
.L5351:	.data.w	.L5350
	.endo	.L5351
.L5353:	.data.w	.L5352
	.endo	.L5353
.L5355:	.data.w	.L5354
	.endo	.L5355
.L5357:	.data.w	.L5356
	.endo	.L5357
.L5359:	.data.w	.L5358
	.endo	.L5359
.L5361:	.data.w	.L5360
	.endo	.L5361
.L5363:	.data.w	.L5362
	.endo	.L5363
.L5365:	.data.w	.L5364
	.endo	.L5365
.L5367:	.data.w	.L5366
	.endo	.L5367
	.section ".ghtailcalltbl",""
.L5369:	.data.w	.L5368
	.endo	.L5369
	.data
	.global	__caller.Dma_DeInit.v.v

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Adc_GetGroupStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_Init.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.:
Adc_SwTrigDmaTransferAllChToOneResRegDemo:
.LDW55:
	push	{r4,lr}
.LDW65:
	ldr	r0,.L4998
.L5594:

	bl	Dma_Init
	mov	r0,18
.L5596:

	bl	Dma_ChannelStart
	mov	r0,34
.L5598:

	bl	Adc_StartGroupConversion
	mov	r4,0
.L5374:
	add	r4,r4,1
	mov	r0,1
.L5600:

	bl	Timer_DelayMs
	mov	r0,18
.L5602:

	bl	Dma_GetChannelStatus
	cmp	r4,0x03e8
	bhs	.L5372
	tst	r0,1
	beq	.L5374
.L5372:
	cmp	r4,0x03e8
	beq	.L5376
	ldr	r1,.L5591
	mov	r0,0
.L5604:

	bl	TmcPrintf
	mov	r4,0
.L5381:
	ldr	r2,.L5001
	lsl	r0,r4,1
	ldr	r1,.L5592
	ldrh	r2,[r0,r2]
	mov	r0,0
.L5606:

	bl	TmcPrintf
	add	r4,r4,1
	cmp	r4,6
	blo	.L5381
	ldr	r1,.L4176
	b	.L5382
.L5376:
	ldr	r1,.L4177
.L5382:
	mov	r0,0
.L5608:

	bl	TmcPrintf
	ldr	r1,.L5593
	mov	r0,0
.L5610:

	bl	TmcPrintf
	mov	r0,34
.L5612:

	bl	Adc_StopGroupConversion
	mov	r1,0
	mov	r0,18
.L5614:

	bl	Dma_ChannelCancel
	pop	{r4,lr}
.L5616:

	b	Dma_DeInit
.LDW75:
__ghs_eofn_Adc_SwTrigDmaTransferAllChToOneResRegDemo:
	.endf	Adc_SwTrigDmaTransferAllChToOneResRegDemo
	.endf	Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
;LoopCnt	r4	local
;DmaChStatus	r0	local

	.section ".rodata","a"
.L5501:;	"\nSARADC1 DMA mode; SW trigger one-shot(All conversion results stored ..."
	.data.b	10,83,65,82
	.data.b	65,68,67,49
	.data.b	32,68,77,65
	.data.b	32,109,111,100
	.data.b	101,59,32,83
	.data.b	87,32,116,114
	.data.b	105,103,103,101
	.data.b	114,32,111,110
	.data.b	101,45,115,104
	.data.b	111,116,40,65
	.data.b	108,108,32,99
	.data.b	111,110,118,101
	.data.b	114,115,105,111
	.data.b	110,32,114,101
	.data.b	115,117,108,116
	.data.b	115,32,115,116
	.data.b	111,114,101,100
	.data.b	32,105,110,32
	.data.b	111,110,101,32
	.data.b	114,101,115,105
	.data.b	103,116,101,114
	.data.b	41,32,82,101
	.data.b	115,117,108,116
	.data.b	58,32,13,10
	.data.b	0
	.endo	.L5501
	.section ".ghcalltbl",""
.L5595:	.data.w	.L5594
	.endo	.L5595
.L5597:	.data.w	.L5596
	.endo	.L5597
.L5599:	.data.w	.L5598
	.endo	.L5599
.L5601:	.data.w	.L5600
	.endo	.L5601
.L5603:	.data.w	.L5602
	.endo	.L5603
.L5605:	.data.w	.L5604
	.endo	.L5605
.L5607:	.data.w	.L5606
	.endo	.L5607
.L5609:	.data.w	.L5608
	.endo	.L5609
.L5611:	.data.w	.L5610
	.endo	.L5611
.L5613:	.data.w	.L5612
	.endo	.L5613
.L5615:	.data.w	.L5614
	.endo	.L5615
	.section ".ghtailcalltbl",""
.L5617:	.data.w	.L5616
	.endo	.L5617
	.data
	.global	__caller.Dma_DeInit.v.v

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Dma_GetChannelStatus.i.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Adc_StartGroupConversion.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_Init.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
__callee.Adc_DemoEntry.v.v::
	.size	__callee.Adc_DemoEntry.v.v,0
Adc_DemoEntry::
.LDW85:
	push	{r4-r5,lr}
	sub	sp,sp,20
.LDW95:
	mov	r5,0
.L5622:
	add	r0,sp,8
.L6103:

	bl	Adc_GetVersionInfo
	ldr	r1,.L6079
	mov	r0,r5
.L6105:

	bl	TmcPrintf
	ldr	r1,.L6080
	mov	r0,r5
.L6107:

	bl	TmcPrintf
	ldrb	r0,[sp,14]
	str	r0,[sp]
	ldr	r1,.L6081
	ldrb	r2,[sp,12]
	mov	r0,r5
	ldrb	r3,[sp,13]
.L6109:

	bl	TmcPrintf
	ldr	r1,.L6082
	mov	r0,r5
.L6111:

	bl	TmcPrintf
	ldr	r1,.L6083
	mov	r0,r5
.L6113:

	bl	TmcPrintf
	ldr	r1,.L6084
	mov	r0,r5
.L6115:

	bl	TmcPrintf
	ldr	r1,.L6085
	mov	r0,r5
.L6117:

	bl	TmcPrintf
	ldr	r1,.L6086
	mov	r0,r5
.L6119:

	bl	TmcPrintf
	ldr	r1,.L6087
	mov	r0,r5
.L6121:

	bl	TmcPrintf
	ldr	r1,.L6088
	mov	r0,r5
.L6123:

	bl	TmcPrintf
	ldr	r1,.L6089
	mov	r0,r5
.L6125:

	bl	TmcPrintf
	ldr	r1,.L6090
	mov	r0,r5
.L6127:

	bl	TmcPrintf
	ldr	r1,.L6091
	mov	r0,r5
.L6129:

	bl	TmcPrintf
	ldr	r1,.L6092
	mov	r0,r5
.L6131:

	bl	TmcPrintf
	ldr	r1,.L6093
	mov	r0,r5
.L6133:

	bl	TmcPrintf
	ldr	r1,.L6094
	mov	r0,r5
.L6135:

	bl	TmcPrintf
	ldr	r1,.L6095
	mov	r0,r5
.L6137:

	bl	TmcPrintf
	ldr	r1,.L6096
	mov	r0,r5
.L6139:

	bl	TmcPrintf
	ldr	r1,.L6097
	mov	r0,r5
.L6141:

	bl	TmcPrintf
	ldr	r1,.L6098
	mov	r0,r5
.L6143:

	bl	TmcPrintf
	ldr	r1,.L6099
	mov	r0,r5
.L6145:

	bl	TmcPrintf
	ldr	r1,.L6100
	mov	r0,r5
.L6147:

	bl	TmcPrintf
	ldr	r4,.L6101
	mov	r0,1
	str	r0,[r4,8]
.L6149:

	bl	getChar
	sub	r1,r0,48
	cmp	r1,10
	bhs	.L5623
	sub	r0,r0,51
	cmp	r0,4
	movlo	r0,1
	movhs	r0,0
	str	r0,[r4]
	strb	r1,[r4,4]
	b	.L5630
.L5623:
	sub	r1,r0,97
	cmp	r1,23
	bhs	.L5631
	cmp	r0,101
	b	.L6065
.L5631:
	sub	r1,r0,65
	cmp	r1,23
	bhs	.L5638
.L5643:
	cmp	r0,69
.L6065:

	moveq	r0,1
	movne	r0,0
	str	r0,[r4]
	add	r0,r1,10
	strb	r0,[r4,4]
	b	.L5630
.L5638:
	cmp	r0,120
	cmpne	r0,88
	moveq	r0,0
	moveq	r1,254
	streq	r0,[r4]
	moveq	r5,1
	strbeq	r1,[r4,4]
	ldrne	r1,.L6102
	movne	r0,r5
	streq	r0,[r4,8]
.L6151:

	blne	TmcPrintf
.L5630:
	ldrb	r0,[r4,4]
	cmp	r0,255
	beq	.L5620
	ldr	r0,[r4]
	cmp	r0,0
.L6153:

	bleq	Adc_Demo
.L5653:
	ldrb	r0,[r4,4]
	cmp	r0,255
	bne	.L5653
.L5620:
	cmp	r5,0
	beq	.L5622
.LDW06:
	add	sp,sp,20
.L6155:

	pop	{r4-r5,pc}
__ghs_eofn_Adc_DemoEntry::
	.endf	Adc_DemoEntry
;Cmd	r0	local
;ExitFlag	r5	local
;Adc_ver	[sp,8]	local

	.section ".rodata","a"
.L5909:;	"\n\n\n"
	.data.b	10,10,10,0
	.endo	.L5909
	.section ".mcal_data_asil_d_unspecified_uncached","aw"
	.align	4
Adc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_DemoCoreExeFlag:	.space	4
	.data.b	255,0,0,0
	.space	4
	.endo	Adc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_DemoCoreExeFlag
	.section ".rodata","a"
.L5910:;	"\n\n  INVALID OPTION\n"
	.data.b	10,10,32,32
	.data.b	73,78,86,65
	.data.b	76,73,68,32
	.data.b	79,80,84,73
	.data.b	79,78,10,0
	.endo	.L5910
.L5911:;	"\n  ENTER YOUR OPTION   : "
	.data.b	10,32,32,69
	.data.b	78,84,69,82
	.data.b	32,89,79,85
	.data.b	82,32,79,80
	.data.b	84,73,79,78
	.data.b	32,32,32,58
	.data.b	32,0
	.endo	.L5911
.L5912:;	"\n  <x> : Go back to Main Menu. \n"
	.data.b	10,32,32,60
	.data.b	120,62,32,58
	.data.b	32,71,111,32
	.data.b	98,97,99,107
	.data.b	32,116,111,32
	.data.b	77,97,105,110
	.data.b	32,77,101,110
	.data.b	117,46,32,10
	.data.b	0
	.endo	.L5912
.L5913:;	"\n                                                         "
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
	.endo	.L5913
.L5914:;	"\n           ADC DRIVER DEMO MENU V%02d.%02d.%02d            "
	.data.b	10,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	65,68,67,32
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
	.endo	.L5914
.L5915:;	"\n/*********************************************************/"
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
	.endo	.L5915
.L5916:;	"\n  <5> : (SARADC2)Start to Software trigger with shot conversion in C..."
	.data.b	10,32,32,60
	.data.b	53,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	50,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,115,104,111
	.data.b	116,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,105,110,32
	.data.b	67,111,114,101
	.data.b	49,46,32,0
	.endo	.L5916
.L5917:;	"\n  <f> : Sync conversion Demo in Core0, master is SARADC0, Slave is S..."
	.data.b	10,32,32,60
	.data.b	102,62,32,58
	.data.b	32,83,121,110
	.data.b	99,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,68,101,109
	.data.b	111,32,105,110
	.data.b	32,67,111,114
	.data.b	101,48,44,32
	.data.b	109,97,115,116
	.data.b	101,114,32,105
	.data.b	115,32,83,65
	.data.b	82,65,68,67
	.data.b	48,44,32,83
	.data.b	108,97,118,101
	.data.b	32,105,115,32
	.data.b	83,65,82,65
	.data.b	68,67,50,46
	.data.b	32,0
	.endo	.L5917
.L5918:;	"\n  <b> : (SARADC1)Start to Software trigger with DMA channel transfer..."
	.data.b	10,32,32,60
	.data.b	98,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	49,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,68,77,65
	.data.b	32,99,104,97
	.data.b	110,110,101,108
	.data.b	32,116,114,97
	.data.b	110,115,102,101
	.data.b	114,32,105,110
	.data.b	32,67,111,114
	.data.b	101,48,46,32
	.data.b	0
	.endo	.L5918
.L5919:;	"\n  <1> : (SARADC0)Start to Hardware trigger with GTM Timer(Single mod..."
	.data.b	10,32,32,60
	.data.b	49,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	48,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,72
	.data.b	97,114,100,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,71,84,77
	.data.b	32,84,105,109
	.data.b	101,114,40,83
	.data.b	105,110,103,108
	.data.b	101,32,109,111
	.data.b	100,101,41,32
	.data.b	105,110,32,67
	.data.b	111,114,101,48
	.data.b	46,32
	.data.b	0
	.endo	.L5919
.L5920:;	"\n  <8> : (SARADC8)Start to Hardware trigger with polling mode(single ..."
	.data.b	10,32,32,60
	.data.b	56,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	56,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,72
	.data.b	97,114,100,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,40,115,105
	.data.b	110,103,108,101
	.data.b	32,109,111,100
	.data.b	101,41,32,105
	.data.b	110,32,67,111
	.data.b	114,101,48,46
	.data.b	32,0
	.endo	.L5920
.L5921:;	"\n  <7> : (SARADC8)Start to Software trigger with polling mode(single ..."
	.data.b	10,32,32,60
	.data.b	55,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	56,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,40,115,105
	.data.b	110,103,108,101
	.data.b	32,109,111,100
	.data.b	101,41,32,105
	.data.b	110,32,67,111
	.data.b	114,101,48,46
	.data.b	32,0
	.endo	.L5921
.L5922:;	"\n  <2> : (SARADC0)Start to Hardware trigger with GTM Timer(Streaming ..."
	.data.b	10,32,32,60
	.data.b	50,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	48,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,72
	.data.b	97,114,100,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,71,84,77
	.data.b	32,84,105,109
	.data.b	101,114,40,83
	.data.b	116,114,101,97
	.data.b	109,105,110,103
	.data.b	32,109,111,100
	.data.b	101,41,32,105
	.data.b	110,32,67,111
	.data.b	114,101,48,46
	.data.b	32,0
	.endo	.L5922
.L5923:;	"\n  <9> : (SARADC8)Start to Software trigger with polling mode(streami..."
	.data.b	10,32,32,60
	.data.b	57,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	56,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,40,115,116
	.data.b	114,101,97,109
	.data.b	105,110,103,32
	.data.b	109,111,100,101
	.data.b	41,32,105,110
	.data.b	32,67,111,114
	.data.b	101,48,46,32
	.data.b	0
	.endo	.L5923
.L5924:;	"\n  <a> : (SARADC8)Start to Hardware trigger with polling mode(streami..."
	.data.b	10,32,32,60
	.data.b	97,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	56,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,72
	.data.b	97,114,100,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,112,111,108
	.data.b	108,105,110,103
	.data.b	32,109,111,100
	.data.b	101,40,115,116
	.data.b	114,101,97,109
	.data.b	105,110,103,32
	.data.b	109,111,100,101
	.data.b	41,32,105,110
	.data.b	32,67,111,114
	.data.b	101,48,46,32
	.data.b	0
	.endo	.L5924
.L5925:;	"\n  <3> : (SARADC2)Start to Software trigger with continuous conversio..."
	.data.b	10,32,32,60
	.data.b	51,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	50,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,99,111,110
	.data.b	116,105,110,117
	.data.b	111,117,115,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,40,115
	.data.b	105,110,103,108
	.data.b	101,32,109,111
	.data.b	100,101,41,32
	.data.b	105,110,32,67
	.data.b	111,114,101,49
	.data.b	46,32
	.data.b	0
	.endo	.L5925
.L5926:;	"\n  <6> : (SARADC2)Start to Software trigger with continuous conversio..."
	.data.b	10,32,32,60
	.data.b	54,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	50,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,99,111,110
	.data.b	116,105,110,117
	.data.b	111,117,115,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,40,115
	.data.b	116,114,101,97
	.data.b	109,105,110,103
	.data.b	32,109,111,100
	.data.b	101,41,32,105
	.data.b	110,32,67,111
	.data.b	114,101,49,46
	.data.b	32,0
	.endo	.L5926
.L5927:;	"\n  <4> : (SARADC2)Start to Software trigger with one shot conversion ..."
	.data.b	10,32,32,60
	.data.b	52,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	50,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,111,110,101
	.data.b	32,115,104,111
	.data.b	116,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,97,110,100
	.data.b	32,108,105,109
	.data.b	105,116,32,99
	.data.b	104,101,99,107
	.data.b	105,110,103,32
	.data.b	105,110,32,67
	.data.b	111,114,101,49
	.data.b	46,32
	.data.b	0
	.endo	.L5927
.L5928:;	"\n  <e> : (SARADC2)Start to Software trigger with conversion result ac..."
	.data.b	10,32,32,60
	.data.b	101,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	50,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,32
	.data.b	114,101,115,117
	.data.b	108,116,32,97
	.data.b	99,99,117,109
	.data.b	117,108,97,116
	.data.b	105,111,110,40
	.data.b	111,110,101,45
	.data.b	115,104,111,116
	.data.b	41,32,105,110
	.data.b	32,67,111,114
	.data.b	101,49,46,32
	.data.b	0
	.endo	.L5928
.L5929:;	"\n  <d> : (SARADC0)Start to Hardware trigger with conversion result ac..."
	.data.b	10,32,32,60
	.data.b	100,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	48,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,72
	.data.b	97,114,100,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,32
	.data.b	114,101,115,117
	.data.b	108,116,32,97
	.data.b	99,99,117,109
	.data.b	117,108,97,116
	.data.b	105,111,110,40
	.data.b	83,105,110,103
	.data.b	108,101,32,109
	.data.b	111,100,101,41
	.data.b	32,105,110,32
	.data.b	67,111,114,101
	.data.b	48,46,32,0
	.endo	.L5929
.L5930:;	"\n  <c> : (SARADC1)Start to Software trigger with DMA channel transfer..."
	.data.b	10,32,32,60
	.data.b	99,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	49,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,68,77,65
	.data.b	32,99,104,97
	.data.b	110,110,101,108
	.data.b	32,116,114,97
	.data.b	110,115,102,101
	.data.b	114,40,76,105
	.data.b	110,107,101,100
	.data.b	32,108,105,115
	.data.b	116,32,97,110
	.data.b	100,32,100,97
	.data.b	105,115,121,32
	.data.b	99,104,97,105
	.data.b	110,41,32,105
	.data.b	110,32,67,111
	.data.b	114,101,48,46
	.data.b	32,0
	.endo	.L5930
.L5931:;	"\n  <g> : (SARADC1)Start to Software trigger with DMA channel transfer..."
	.data.b	10,32,32,60
	.data.b	103,62,32,58
	.data.b	32,40,83,65
	.data.b	82,65,68,67
	.data.b	49,41,83,116
	.data.b	97,114,116,32
	.data.b	116,111,32,83
	.data.b	111,102,116,119
	.data.b	97,114,101,32
	.data.b	116,114,105,103
	.data.b	103,101,114,32
	.data.b	119,105,116,104
	.data.b	32,68,77,65
	.data.b	32,99,104,97
	.data.b	110,110,101,108
	.data.b	32,116,114,97
	.data.b	110,115,102,101
	.data.b	114,40,65,108
	.data.b	108,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,114,101,115
	.data.b	117,108,116,115
	.data.b	32,115,116,111
	.data.b	114,101,100,32
	.data.b	105,110,32,111
	.data.b	110,101,32,114
	.data.b	101,103,105,115
	.data.b	116,101,114,41
	.data.b	32,105,110,32
	.data.b	67,111,114,101
	.data.b	48,46,32,0
	.endo	.L5931
	.section ".bss","awb"
.L5932:
	.endo	.L5932
	.section ".ghcalltbl",""
.L6104:	.data.w	.L6103
	.endo	.L6104
.L6106:	.data.w	.L6105
	.endo	.L6106
.L6108:	.data.w	.L6107
	.endo	.L6108
.L6110:	.data.w	.L6109
	.endo	.L6110
.L6112:	.data.w	.L6111
	.endo	.L6112
.L6114:	.data.w	.L6113
	.endo	.L6114
.L6116:	.data.w	.L6115
	.endo	.L6116
.L6118:	.data.w	.L6117
	.endo	.L6118
.L6120:	.data.w	.L6119
	.endo	.L6120
.L6122:	.data.w	.L6121
	.endo	.L6122
.L6124:	.data.w	.L6123
	.endo	.L6124
.L6126:	.data.w	.L6125
	.endo	.L6126
.L6128:	.data.w	.L6127
	.endo	.L6128
.L6130:	.data.w	.L6129
	.endo	.L6130
.L6132:	.data.w	.L6131
	.endo	.L6132
.L6134:	.data.w	.L6133
	.endo	.L6134
.L6136:	.data.w	.L6135
	.endo	.L6136
.L6138:	.data.w	.L6137
	.endo	.L6138
.L6140:	.data.w	.L6139
	.endo	.L6140
.L6142:	.data.w	.L6141
	.endo	.L6142
.L6144:	.data.w	.L6143
	.endo	.L6144
.L6146:	.data.w	.L6145
	.endo	.L6146
.L6148:	.data.w	.L6147
	.endo	.L6148
.L6150:	.data.w	.L6149
	.endo	.L6150
.L6152:	.data.w	.L6151
	.endo	.L6152
.L6154:	.data.w	.L6153
	.endo	.L6154
	.section ".ghrettbl",""
.L6156:	.data.w	.L6155
	.endo	.L6156
	.data
	.global	__caller.Adc_Demo.v.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.getChar.i.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_GetVersionInfo.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
__callee.Adc_Demo.v.v::
	.size	__callee.Adc_Demo.v.v,0
Adc_Demo::
.LDW16:
	push	{r4-r6,lr}
.LDW26:
	b	.L6831

.L5591:	.data.w	.L5501
	.endo	.L5591

.L5592:	.data.w	.L451
	.endo	.L5592

.L5593:	.data.w	.L154
	.endo	.L5593

.L6079:	.data.w	.L5909
	.endo	.L6079

.L6080:	.data.w	.L5915
	.endo	.L6080

.L6081:	.data.w	.L5914
	.endo	.L6081

.L6082:	.data.w	.L5913
	.endo	.L6082

.L6083:	.data.w	.L5919
	.endo	.L6083

.L6084:	.data.w	.L5922
	.endo	.L6084

.L6085:	.data.w	.L5925
	.endo	.L6085

.L6086:	.data.w	.L5927
	.endo	.L6086

.L6087:	.data.w	.L5916
	.endo	.L6087

.L6088:	.data.w	.L5926
	.endo	.L6088

.L6089:	.data.w	.L5921
	.endo	.L6089

.L6090:	.data.w	.L5920
	.endo	.L6090

.L6091:	.data.w	.L5923
	.endo	.L6091

.L6092:	.data.w	.L5924
	.endo	.L6092

.L6093:	.data.w	.L5918
	.endo	.L6093

.L6094:	.data.w	.L5930
	.endo	.L6094

.L6095:	.data.w	.L5929
	.endo	.L6095

.L6096:	.data.w	.L5928
	.endo	.L6096

.L6097:	.data.w	.L5917
	.endo	.L6097

.L6098:	.data.w	.L5931
	.endo	.L6098

.L6099:	.data.w	.L5912
	.endo	.L6099

.L6100:	.data.w	.L5911
	.endo	.L6100

.L6101:	.data.w	Adc_DemoCoreExeFlag
	.endo	.L6101

.L6102:	.data.w	.L5910
	.endo	.L6102

.L6831:

;line1700
..lin.87a640f4..77f6e691.1_3::
.LDWlin3:
..gh.beginasm.18:
	.endo	..gh.beginasm.18
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.19:
	.endo	..gh.endasm.19

	ldr	r1,.L6832
;line1702
..lin.87a640f4..77f6e691.1_4::
.LDWlin4:
	ldr	r5,.L6833
	ldr	r6,[r1,r0 lsl 2]
	ldr	r1,[r5,8]
	mov	r4,r0
	ldrb	r0,[r6]
	cmp	r1,1
	bne	.L6163
	cmp	r0,0
	bne	.L6167
	ldr	r0,.L6834
.L6835:

	bl	Adc_Init
	mov	r0,1
	b	.L6320
.L6163:
	cmp	r0,1
	bne	.L6167
.L6837:

	bl	Adc_DeInit
	mov	r0,0
.L6320:
	strb	r0,[r6]
.L6167:
	ldr	r1,[r5]
	cmp	r1,r4
.L6839:

	popne	{r4-r6,pc}
	ldrb	r1,[r5,4]
	cmp	r1,255
.L6841:

	popeq	{r4-r6,pc}
	ldrb	r1,[r5,4]
	subs	r1,r1,254
	bhs	.L6514
	adds	r1,r1,253
	cmp	r1,15
	bhi	.L6193
	mov	r2,r1
	adr	r3,.L6517
	jtdispatch	r2,r3,50
.L6518:

.L6517:

;line1723
..lin.87a640f4..77f6e691.1_5::
.LDWlin5:
	jtentry	(.L6174-.L6518)>>2
	jtentry	(.L6175-.L6518)>>2
	jtentry	(.L6176-.L6518)>>2
	jtentry	(.L6177-.L6518)>>2
	jtentry	(.L6178-.L6518)>>2
	jtentry	(.L6179-.L6518)>>2
	jtentry	(.L6180-.L6518)>>2
	jtentry	(.L6181-.L6518)>>2
	jtentry	(.L6182-.L6518)>>2
	jtentry	(.L6183-.L6518)>>2
	jtentry	(.L6184-.L6518)>>2
	jtentry	(.L6185-.L6518)>>2
	jtentry	(.L6187-.L6518)>>2
	jtentry	(.L6188-.L6518)>>2
	jtentry	(.L6189-.L6518)>>2
	jtentry	(.L6186-.L6518)>>2
	jtentry	-1
	.align	4
	.type	.L6517, $object
	.size	.L6517, .-.L6517

.L6514:
;line1723
..lin.87a640f4..77f6e691.1_6::
.LDWlin6:
	cmp	r1,0
	bne	.L6193
	b	.L6190
.L6174:
.L6843:

	bl	Adc_HwTrigSingleWithGtmDemo
	b	.L6193
.L6175:
.L6845:

	bl	Adc_HwTrigStreamingWithGtmDemo
	b	.L6193
.L6176:
.L6847:

	bl	Adc_SwTrigContinuousConversionDemo
	b	.L6193
.L6177:
.L6849:

	bl	Adc_SwTrigWithLimitCheckingDemo
	b	.L6193
.L6178:
.L6851:

	bl	Adc_SwTrigOneShotConversionDemo
	b	.L6193
.L6179:
.L6853:

	bl	Adc_SwTrigContinuousStreamingDemo
	b	.L6193
.L6180:
.L6855:

	bl	Adc_SwTrigPollingSingleDemo
	b	.L6193
.L6181:
.L6857:

	bl	Adc_HwTrigPollingSingleDemo
	b	.L6193
.L6182:
.L6859:

	bl	Adc_SwTrigPollingStreamingDemo
	b	.L6193
.L6183:
.L6861:

	bl	Adc_HwTrigPollingStreamingDemo
	b	.L6193
.L6184:
.L6863:

	bl	Adc_SwTrigDmaTransferDemo
	b	.L6193
.L6185:
.L6865:

	bl	Adc_SwTrigDmaTransferWithDaisyChainDemo
	b	.L6193
.L6186:
.L6867:

	bl	Adc_SwTrigDmaTransferAllChToOneResRegDemo
	b	.L6193
.L6187:
.L6869:

	bl	Adc_HwTrigSingleWithResultAccumuDemo
	b	.L6193
.L6188:
.L6871:

	bl	Adc_SwTrigOneShotConversionResultAccumuDemo
	b	.L6193
.L6189:
.L6873:

	bl	Adc_SyncGroupHwTrigDemo
	b	.L6193
.L6190:
	cmp	r0,1
	strbeq	r1,[r6]
.L6875:

	bleq	Adc_DeInit
	mvn	r0,0
	strb	r0,[r5,4]
.L6193:
	ldrb	r0,[r5,4]
	cmp	r0,254
	mvnlo	r0,0
	strblo	r0,[r5,4]
	movlo	r0,0
	strlo	r0,[r5]
.LDW36:
.L6877:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_Demo::
	.endf	Adc_Demo
;CoreId	r4	local

	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Adc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_DemoCoreInitStatus:
	.data.w	Adc_DemoInitStatusCore0
	.data.w	Adc_DemoInitStatusCore1
	.space	8
	.endo	Adc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_DemoCoreInitStatus
	.section ".ghcalltbl",""
.L6836:	.data.w	.L6835
	.endo	.L6836
.L6838:	.data.w	.L6837
	.endo	.L6838
	.section ".ghrettbl",""
.L6840:	.data.w	.L6839
	.endo	.L6840
.L6842:	.data.w	.L6841
	.endo	.L6842
	.section ".ghcalltbl",""
.L6844:	.data.w	.L6843
	.endo	.L6844
.L6846:	.data.w	.L6845
	.endo	.L6846
.L6848:	.data.w	.L6847
	.endo	.L6848
.L6850:	.data.w	.L6849
	.endo	.L6850
.L6852:	.data.w	.L6851
	.endo	.L6852
.L6854:	.data.w	.L6853
	.endo	.L6854
.L6856:	.data.w	.L6855
	.endo	.L6856
.L6858:	.data.w	.L6857
	.endo	.L6858
.L6860:	.data.w	.L6859
	.endo	.L6860
.L6862:	.data.w	.L6861
	.endo	.L6862
.L6864:	.data.w	.L6863
	.endo	.L6864
.L6866:	.data.w	.L6865
	.endo	.L6866
.L6868:	.data.w	.L6867
	.endo	.L6868
.L6870:	.data.w	.L6869
	.endo	.L6870
.L6872:	.data.w	.L6871
	.endo	.L6872
.L6874:	.data.w	.L6873
	.endo	.L6874
.L6876:	.data.w	.L6875
	.endo	.L6876
	.section ".ghrettbl",""
.L6878:	.data.w	.L6877
	.endo	.L6878
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Adc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_DemoInitStatusCore0:	.space	1
	.endo	Adc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_DemoInitStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
Adc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.::
Adc_DemoInitStatusCore1:	.space	1
	.endo	Adc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.endo	Adc_DemoInitStatusCore1
	.data
	.global	__caller.Adc_DeInit.v.v

	.global	__caller.Adc_DeInit.v.v

	.global	__caller.Adc_Init.v.p

	.ghsnote jtable,4,.L6517,.L6518,.L6517,16
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_GtmTriggerCnt_0 - Adc_GtmTriggerCnt_0) +0 == 0
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
__callee.AdcDemo_Adc0HwTrigNotif.v.v::
	.size	__callee.AdcDemo_Adc0HwTrigNotif.v.v,0
AdcDemo_Adc0HwTrigNotif::
.LDW46:
	push	{r4-r5,lr}
	sub	sp,sp,20
	ldr	r4,.L7065
	ldrb	r0,[r4]
.LDW56:
	add	r0,r0,1
	mov	r1,sp
	strb	r0,[r4]
	mov	r0,0
.L7070:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L6881
	ldr	r1,.L7066
	ldrb	r2,[r4]
.L7072:

	bl	TmcPrintf
	mov	r5,0
.L6886:
	lsl	r0,r5,1
	ldr	r1,.L7067
	ldrh	r2,[r0,sp]
	mov	r0,0
.L7074:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,7
	blo	.L6886
	ldrb	r0,[r4]
	cmp	r0,5
	blo	.L6879
	mov	r0,0
.L7076:

	bl	Adc_DisableGroupNotification
	mov	r0,0
.L7078:

	bl	Adc_DisableHardwareTrigger
	ldr	r1,.L7068
	b	.L6925
.L6881:
	ldr	r1,.L7069
.L6925:
	mov	r0,0
.L7080:

	bl	TmcPrintf
.L6879:
.LDW66:
	add	sp,sp,20
.L7082:

	pop	{r4-r5,pc}
__ghs_eofn_AdcDemo_Adc0HwTrigNotif::
	.endf	AdcDemo_Adc0HwTrigNotif
;ResultBuffer	[sp]	local

	.section ".rodata","a"
.L6985:;	"\nNo. :%d: "
	.data.b	10,78,111,46
	.data.b	32,58,37,100
	.data.b	58,32
	.data.b	0
	.endo	.L6985
.L6986:;	"\n5 times SARADC0 conversions finished."
	.data.b	10,53,32,116
	.data.b	105,109,101,115
	.data.b	32,83,65,82
	.data.b	65,68,67,48
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,115
	.data.b	32,102,105,110
	.data.b	105,115,104,101
	.data.b	100,46
	.data.b	0
	.endo	.L6986
.L6987:;	"\nRead SARADC0 conversion result FAILED."
	.data.b	10,82,101,97
	.data.b	100,32,83,65
	.data.b	82,65,68,67
	.data.b	48,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,114,101,115
	.data.b	117,108,116,32
	.data.b	70,65,73,76
	.data.b	69,68,46,0
	.endo	.L6987
	.section ".ghcalltbl",""
.L7071:	.data.w	.L7070
	.endo	.L7071
.L7073:	.data.w	.L7072
	.endo	.L7073
.L7075:	.data.w	.L7074
	.endo	.L7075
.L7077:	.data.w	.L7076
	.endo	.L7077
.L7079:	.data.w	.L7078
	.endo	.L7079
.L7081:	.data.w	.L7080
	.endo	.L7081
	.section ".ghrettbl",""
.L7083:	.data.w	.L7082
	.endo	.L7083
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_DisableHardwareTrigger.v.i

	.global	__caller.Adc_DisableGroupNotification.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_GtmTriggerCnt_0 - Adc_GtmTriggerCnt_0) +0 == 0
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
__callee.AdcDemo_Adc0HwTrigRsltAccumNotif.v.v::
	.size	__callee.AdcDemo_Adc0HwTrigRsltAccumNotif.v.v,0
AdcDemo_Adc0HwTrigRsltAccumNotif::
.LDW76:
	push	{r4-r5,lr}
	sub	sp,sp,20
	ldr	r4,.L7065
	ldrb	r0,[r4]
.LDW86:
	add	r0,r0,1
	mov	r1,sp
	strb	r0,[r4]
	mov	r0,2
.L7272:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L7086
	ldr	r1,.L7271
	ldrb	r2,[r4]
.L7274:

	bl	TmcPrintf
	mov	r5,0
.L7091:
	lsl	r0,r5,1
	ldr	r1,.L7067
	ldrh	r2,[r0,sp]
	mov	r0,0
.L7276:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,7
	blo	.L7091
	ldrb	r0,[r4]
	cmp	r0,5
	blo	.L7084
	mov	r0,2
.L7278:

	bl	Adc_DisableGroupNotification
	mov	r0,2
.L7280:

	bl	Adc_DisableHardwareTrigger
	ldr	r1,.L7068
	b	.L7133
.L7086:
	ldr	r1,.L7069
.L7133:
	mov	r0,0
.L7282:

	bl	TmcPrintf
.L7084:
.LDW96:
	add	sp,sp,20
.L7284:

	pop	{r4-r5,pc}
__ghs_eofn_AdcDemo_Adc0HwTrigRsltAccumNotif::
	.endf	AdcDemo_Adc0HwTrigRsltAccumNotif
;ResultBuffer	[sp]	local

	.section ".rodata","a"
.L7193:;	"\nNo. %d: "
	.data.b	10,78,111,46
	.data.b	32,37,100,58
	.data.b	32,0
	.endo	.L7193
	.section ".ghcalltbl",""
.L7273:	.data.w	.L7272
	.endo	.L7273
.L7275:	.data.w	.L7274
	.endo	.L7275
.L7277:	.data.w	.L7276
	.endo	.L7277
.L7279:	.data.w	.L7278
	.endo	.L7279
.L7281:	.data.w	.L7280
	.endo	.L7281
.L7283:	.data.w	.L7282
	.endo	.L7283
	.section ".ghrettbl",""
.L7285:	.data.w	.L7284
	.endo	.L7285
	.data
	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_DisableHardwareTrigger.v.i

	.global	__caller.Adc_DisableGroupNotification.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_SwContinuousConversionCnt - Adc_SwContinuousConversionCnt) +0 == 0
..gh.f.a.1.e.22:
	.endo	..gh.f.a.1.e.22
__callee.AdcDemo_Adc2ContinuousNotif.v.v::
	.size	__callee.AdcDemo_Adc2ContinuousNotif.v.v,0
AdcDemo_Adc2ContinuousNotif::
.LDW07:
	push	{r4-r5,lr}
	sub	sp,sp,20
	ldr	r4,.L7783
	ldr	r0,[r4]
.LDW17:
	add	r0,r0,1
	mov	r1,sp
	str	r0,[r4]
	mov	r0,64
.L7784:

	bl	Adc_ReadGroup
	cmp	r0,0
	bne	.L7288
	ldr	r1,.L7271
	ldr	r2,[r4]
.L7786:

	bl	TmcPrintf
	mov	r5,0
.L7293:
	lsl	r0,r5,1
	ldr	r1,.L7067
	ldrh	r2,[r0,sp]
	mov	r0,0
.L7788:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,7
	blo	.L7293
.L7288:
	ldr	r0,[r4]
	cmp	r0,5
	blo	.L7286
	mov	r0,64
.L7790:

	bl	Adc_DisableGroupNotification
	mov	r0,64
.L7792:

	bl	Adc_StopGroupConversion
.L7286:
.LDW27:
	add	sp,sp,20
.L7794:

	pop	{r4-r5,pc}
__ghs_eofn_AdcDemo_Adc2ContinuousNotif::
	.endf	AdcDemo_Adc2ContinuousNotif
;ResultBuffer	[sp]	local

	.section ".ghcalltbl",""
.L7785:	.data.w	.L7784
	.endo	.L7785
.L7787:	.data.w	.L7786
	.endo	.L7787
.L7789:	.data.w	.L7788
	.endo	.L7789
.L7791:	.data.w	.L7790
	.endo	.L7791
.L7793:	.data.w	.L7792
	.endo	.L7793
	.section ".ghrettbl",""
.L7795:	.data.w	.L7794
	.endo	.L7795
	.data
	.global	__caller.Adc_StopGroupConversion.v.i

	.global	__caller.Adc_DisableGroupNotification.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Adc_ReadGroup.i.ip

	.section ".mcal_text_asil_d","ax"

.L6832:	.data.w	Adc_DemoCoreInitStatus
	.endo	.L6832

.L6833:	.data.w	Adc_DemoCoreExeFlag
	.endo	.L6833

.L6834:	.data.w	Adc_ConfigSet
	.endo	.L6834

.L7065:	.data.w	Adc_GtmTriggerCnt_0
	.endo	.L7065

.L7066:	.data.w	.L6985
	.endo	.L7066

.L7067:	.data.w	.L451
	.endo	.L7067

.L7068:	.data.w	.L6986
	.endo	.L7068

.L7069:	.data.w	.L6987
	.endo	.L7069

.L7271:	.data.w	.L7193
	.endo	.L7271

.L7783:	.data.w	Adc_SwContinuousConversionCnt
	.endo	.L7783

	.text
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..2::
	.global	__global.use.Adc_ConfigSet.a1_C11.struct.160

;Adc_ConfigSet	Adc_ConfigSet	import
	.global	__global.use.Dma_ConfigSet.a1_C11.struct.224

;Dma_ConfigSet	Dma_ConfigSet	import
;Adc_DemoInitStatusCore0	Adc_DemoInitStatusCore0	static
;Adc_DemoInitStatusCore1	Adc_DemoInitStatusCore1	static
;Adc_DemoCoreExeFlag	Adc_DemoCoreExeFlag	static
;Adc_GtmTriggerCnt_0	Adc_GtmTriggerCnt_0	static
;Adc_SwContinuousConversionCnt	Adc_SwContinuousConversionCnt	static
;Adc_HwTrigSingleResult	Adc_HwTrigSingleResult	static
;Adc_HwTrigStreamingResult	Adc_HwTrigStreamingResult	static
;Adc_SyncGrpResult	Adc_SyncGrpResult	static
;Adc_SwContinusBuffer	Adc_SwContinusBuffer	static
;Adc_SwOneShotLimitChecking	Adc_SwOneShotLimitChecking	static
;Adc_SwOneShotBuffer	Adc_SwOneShotBuffer	static
;Adc_SwStreamingBuffer	Adc_SwStreamingBuffer	static
;Adc_SwPollingSingleResult	Adc_SwPollingSingleResult	static
;Adc_HwPollingSingleResult	Adc_HwPollingSingleResult	static
;Adc_SwPollingStreamingResult	Adc_SwPollingStreamingResult	static
;Adc_HwPollingStreamingResult	Adc_HwPollingStreamingResult	static
	.global	__global.com.Adc_DmaTransferSwTrigResult.a20_Us

;Adc_DemoCoreInitStatus	Adc_DemoCoreInitStatus	static

	.global	Adc_ConfigSet

	.global	Dma_ConfigSet

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..2::
	.section ".sdk_text_asil_d","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
	.section ".mcal_text_asil_d","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
	.text
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	214,44,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,65,100,99,47,65,100,99,95,68,101,109,111,46,99,0
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
	.data.b	152,18,0,0
	.data.b	2,0
	.data.b	112,11,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,65,100,99,47,65,100,99,95,68,101,109,111,46,99,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,65,100,99,47,65,100,99,95,68,101,109,111,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,65,100,99,92,105,110,99,108,117,100,101,92,65,100,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,65,100,99,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,65,100,99,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,65,100,99,92,105,110,99,108,117,100,101,92,65,100,99,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,65,100,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,110,116,99,92,105,110,99,108,117,100,101,92,73,110,116,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,110,116,99,92,105,110,99,108,117,100,101,92,73,110,116,99,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,73,110,116,99,92,105,110,99,108,117,100,101,92,73,110,116,99,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,73,110,116,99,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,110,116,99,92,105,110,99,92,105,110,116,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,73,110,116,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,73,110,116,99,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,67,111,109,109,111,110,92,68,101,109,111,95,84,101,115,116,84,105,109,101,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,67,111,109,109,111,110,92,68,101,109,111,95,67,111,109,109,111,110,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,109,97,92,105,110,99,108,117,100,101,92,68,109,97,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,109,97,92,105,110,99,108,117,100,101,92,68,109,97,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,109,97,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,100,109,97,92,105,110,99,92,100,109,97,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,100,109,97,92,105,110,99,92,100,109,97,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,68,109,97,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,109,97,95,80,66,99,102,103,46,104,0
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
	.data.w	.Ldw_begin+1478
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

	.data.b	49
	.data.w	.Ldw_begin+1287

	.section	.debug_abbrev		;off: 46
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 71
	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 244
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 75
	.data.w	.Ldw_str_begin+244
	.data.b	7
	.data.b	2

	.data.b	53
	.data.w	.Ldw_begin+3472

	.section	.debug_abbrev		;off: 53
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 86
	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 259
	.data.b	105,110,116,0
	.section	.debug_info		;off: 93
	.data.w	.Ldw_str_begin+259
	.data.b	5
	.data.b	4

	.data.b	47
	.data.w	.Ldw_begin+1263

	.section	.debug_abbrev		;off: 60
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 104
	.data.b	64
	.data.b	0
	.data.b	2
	.data.w	.Ldw_begin+99

	.section	.debug_abbrev		;off: 67
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 111
	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 78
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 119
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

	.data.b	49
	.data.w	.Ldw_begin+1263

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	7

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

	.data.b	42
	.section	.debug_str		;off: 263
	.data.b	99,104,97,114,0
	.section	.debug_info		;off: 229
	.data.w	.Ldw_str_begin+263
	.data.b	8
	.data.b	1

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 268
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 296
	.data.w	.Ldw_str_begin+268
	.data.b	7
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+1514

	.data.b	64
	.data.b	0
	.data.b	36
	.data.w	.Ldw_begin+2463

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+323

	.data.b	53
	.data.w	.Ldw_begin+81

	.data.b	53
	.data.w	.Ldw_begin+1263

	.data.b	47
	.data.w	.Ldw_begin+3484

	.data.b	53
	.data.w	.Ldw_begin+341

	.data.b	53
	.data.w	.Ldw_begin+99

	.data.b	47
	.data.w	.Ldw_begin+2994

	.data.b	53
	.data.w	.Ldw_begin+356

	.data.b	47
	.data.w	.Ldw_begin+4116

	.data.b	53
	.data.w	.Ldw_begin+366

	.data.b	47
	.data.w	.Ldw_begin+3435

	.data.b	53
	.data.w	.Ldw_begin+376

	.data.b	47
	.data.w	.Ldw_begin+3508

	.data.b	53
	.data.w	.Ldw_begin+386

	.data.b	47
	.data.w	.Ldw_begin+4188

	.data.b	53
	.data.w	.Ldw_begin+396

	.data.b	47
	.data.w	.Ldw_begin+4061

	.data.b	53
	.data.w	.Ldw_begin+406

	.data.b	47
	.data.w	.Ldw_begin+4379

	.data.b	53
	.data.w	.Ldw_begin+416

	.data.b	47
	.data.w	.Ldw_begin+4434

	.data.b	53
	.data.w	.Ldw_begin+426

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+431

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3819

	.data.b	53
	.data.w	.Ldw_begin+452

	.data.b	53
	.data.w	.Ldw_begin+228

	.data.b	49
	.data.w	.Ldw_begin+4555

	.data.b	49
	.data.w	.Ldw_begin+4622

	.data.b	49
	.data.w	.Ldw_begin+4663

	.data.b	49
	.data.w	.Ldw_begin+4704

	.data.b	49
	.data.w	.Ldw_begin+4785

	.data.b	49
	.data.w	.Ldw_begin+5066

	.data.b	47
	.data.w	.Ldw_begin+6814

	.data.b	53
	.data.w	.Ldw_begin+497

	.data.b	47
	.data.w	.Ldw_begin+7360

	.data.b	53
	.data.w	.Ldw_begin+507

	.data.b	53
	.data.w	.Ldw_begin+6886

	.data.b	47
	.data.w	.Ldw_begin+6582

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+6802
	.data.b	0

	.section	.debug_abbrev		;off: 91
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 535
	.data.b	23
	.data.w	.Ldw_begin+7148
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+527

	.data.b	47
	.data.w	.Ldw_begin+6802

	.data.b	53
	.data.w	.Ldw_begin+547

	.data.b	47
	.data.w	.Ldw_begin+6421

	.data.b	47
	.data.w	.Ldw_begin+7470

	.data.b	53
	.data.w	.Ldw_begin+562

	.data.b	47
	.data.w	.Ldw_begin+7415

	.data.b	53
	.data.w	.Ldw_begin+572

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+6802
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+6977
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+582

	.data.b	47
	.data.w	.Ldw_begin+7686

	.data.b	53
	.data.w	.Ldw_begin+602

	.data.b	47
	.data.w	.Ldw_begin+6790

	.data.b	53
	.data.w	.Ldw_begin+612

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+552

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+7580

	.data.b	53
	.data.w	.Ldw_begin+638

	.data.b	47
	.data.w	.Ldw_begin+7894

	.data.b	53
	.data.w	.Ldw_begin+648

	.data.b	47
	.data.w	.Ldw_begin+7525

	.data.b	53
	.data.w	.Ldw_begin+658

	.data.b	47
	.data.w	.Ldw_begin+6671

	.data.b	53
	.data.w	.Ldw_begin+668

	.data.b	47
	.data.w	.Ldw_begin+6510

	.data.b	53
	.data.w	.Ldw_begin+678

	.data.b	47
	.data.w	.Ldw_begin+8055

	.data.b	53
	.data.w	.Ldw_begin+688

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+693

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+8127

	.data.b	53
	.data.w	.Ldw_begin+714

	.data.b	47
	.data.w	.Ldw_begin+7305

	.data.b	53
	.data.w	.Ldw_begin+724

	.data.b	47
	.data.w	.Ldw_begin+7966

	.data.b	53
	.data.w	.Ldw_begin+734

	.data.b	47
	.data.w	.Ldw_begin+4489

	.data.b	64
	.data.b	0
	.data.b	20
	.data.w	.Ldw_begin+744

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+8216

	.data.b	64
	.data.b	0
	.data.b	28
	.data.w	.Ldw_begin+765

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	30
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	14

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	20
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	9

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	19

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	14
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	30
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	14

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	50
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	24

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+3472

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	19

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+336

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+962

	.data.b	56
	.data.w	.Ldw_begin+92
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+744

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+983
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1311
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+81
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1311
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+81
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3584
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3496
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3460
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+331
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1410

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1124
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+4502
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+4502
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1287
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1263
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+462
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+351
	.data.b	0

	.data.b	76

	.section	.debug_abbrev		;off: 100
	.data.b	76
	.data.b	24
	.data.b	0
	.data.b	0,0

	.section	.debug_info		;off: 1184
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+228
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+765

	.data.b	47
	.data.w	.Ldw_begin+1192

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1197
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+6802
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+6802
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+6927
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1287
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+6802
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 281
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1252
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

	.section	.debug_info		;off: 1263
	.data.b	45
	.section	.debug_str		;off: 289
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1264
	.data.w	.Ldw_str_begin+289
	.data.b	56
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 295
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1276
	.data.w	.Ldw_str_begin+295
	.data.b	60
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+74

	.data.b	45
	.section	.debug_str		;off: 302
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1288
	.data.w	.Ldw_str_begin+302
	.data.b	64
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 309
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1300
	.data.w	.Ldw_str_begin+309
	.data.b	68
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 316
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1312
	.data.w	.Ldw_str_begin+316
	.data.b	39
	.data.b	15
	.data.b	3
	.data.w	.Ldw_begin+1263

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

	.section	.debug_info		;off: 1329
	.data.b	40
	.section	.debug_str		;off: 331
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1330
	.data.w	.Ldw_str_begin+331
	.data.b	63
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1275
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

	.section	.debug_info		;off: 1345
	.data.b	40
	.section	.debug_str		;off: 340
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1346
	.data.w	.Ldw_str_begin+340
	.data.b	64
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1275
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 349
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1362
	.data.w	.Ldw_str_begin+349
	.data.b	65
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 366
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1378
	.data.w	.Ldw_str_begin+366
	.data.b	66
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 383
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1394
	.data.w	.Ldw_str_begin+383
	.data.b	67
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 400
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1411
	.data.w	.Ldw_str_begin+400
	.data.b	68
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+1323

	.data.b	52
	.section	.debug_str		;off: 420
	.data.b	0
	.section	.debug_info		;off: 1423
	.data.w	.Ldw_str_begin+420
	.data.b	36
	.data.b	1
	.data.b	16
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

	.section	.debug_info		;off: 1432
	.data.b	51
	.section	.debug_str		;off: 421
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 1433
	.data.w	.Ldw_str_begin+421
	.data.b	37
	.data.b	5
	.data.b	16
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

	.section	.debug_info		;off: 1441
	.data.b	51
	.section	.debug_str		;off: 438
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 1442
	.data.w	.Ldw_str_begin+438
	.data.b	38
	.data.b	5
	.data.b	16
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 455
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 1451
	.data.w	.Ldw_str_begin+455
	.data.b	39
	.data.b	5
	.data.b	16
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 472
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 1460
	.data.w	.Ldw_str_begin+472
	.data.b	40
	.data.b	5
	.data.b	16
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 489
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 1469
	.data.w	.Ldw_str_begin+489
	.data.b	41
	.data.b	5
	.data.b	16
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 506
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1479
	.data.w	.Ldw_str_begin+506
	.data.b	42
	.data.b	3
	.data.b	16
	.data.w	.Ldw_begin+1422

	.data.b	45
	.section	.debug_str		;off: 518
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 1491
	.data.w	.Ldw_str_begin+518
	.data.b	32
	.data.b	21
	.data.b	15
	.data.w	.Ldw_begin+1478

	.data.b	45
	.section	.debug_str		;off: 532
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 1503
	.data.w	.Ldw_str_begin+532
	.data.b	24
	.data.b	22
	.data.b	20
	.data.w	.Ldw_begin+295

	.data.b	71
	.data.b	138,1
	.data.b	1
	.data.b	37
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 539
	.data.b	71,65,84,69,69,78,0
	.section	.debug_info		;off: 1522
	.data.w	.Ldw_str_begin+539
	.data.b	139,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 186
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

	.section	.debug_info		;off: 1541
	.data.b	41
	.section	.debug_str		;off: 546
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 1542
	.data.w	.Ldw_str_begin+546
	.data.b	140,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 557
	.data.b	69,88,84,84,82,73,69,78,0
	.section	.debug_info		;off: 1562
	.data.w	.Ldw_str_begin+557
	.data.b	141,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 566
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 1582
	.data.w	.Ldw_str_begin+566
	.data.b	142,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 577
	.data.b	83,84,82,73,71,69,78,0
	.section	.debug_info		;off: 1602
	.data.w	.Ldw_str_begin+577
	.data.b	143,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 585
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 1622
	.data.w	.Ldw_str_begin+585
	.data.b	144,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	20
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 596
	.data.b	70,76,85,81,85,0
	.section	.debug_info		;off: 1642
	.data.w	.Ldw_str_begin+596
	.data.b	145,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 602
	.data.b	114,101,115,101,114,118,101,100,95,49,51,0
	.section	.debug_info		;off: 1662
	.data.w	.Ldw_str_begin+602
	.data.b	146,1
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	19
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 614
	.data.b	83,65,82,65,68,67,95,81,77,79,68,69,95,66,105,116,115,0
	.section	.debug_info		;off: 1683
	.data.w	.Ldw_str_begin+614
	.data.b	147,1
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+302

	.data.b	73
	.data.b	179,5
	.data.b	1
	.data.b	37
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 211
	.data.b	73
	.data.b	23
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 1702
	.data.b	40
	.section	.debug_str		;off: 632
	.data.b	85,0
	.section	.debug_info		;off: 1703
	.data.w	.Ldw_str_begin+632
	.data.b	180,5
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 634
	.data.b	66,0
	.section	.debug_info		;off: 1720
	.data.w	.Ldw_str_begin+634
	.data.b	181,5
	.data.b	23
	.data.b	37
	.data.w	.Ldw_begin+1682
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 636
	.data.b	83,65,82,65,68,67,95,81,77,79,68,69,0
	.section	.debug_info		;off: 1738
	.data.w	.Ldw_str_begin+636
	.data.b	182,5
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+1695

	.data.b	52
	.section	.debug_str		;off: 649
	.data.b	0
	.section	.debug_info		;off: 1751
	.data.w	.Ldw_str_begin+649
	.data.b	32
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 650
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,49,50,66,73,84,0
	.section	.debug_info		;off: 1761
	.data.w	.Ldw_str_begin+650
	.data.b	33
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 674
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,49,48,66,73,84,0
	.section	.debug_info		;off: 1770
	.data.w	.Ldw_str_begin+674
	.data.b	34
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 698
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,56,66,73,84,0
	.section	.debug_info		;off: 1779
	.data.w	.Ldw_str_begin+698
	.data.b	35
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 721
	.data.b	83,97,114,97,100,99,95,82,101,115,111,108,117,116,105,111,110,0
	.section	.debug_info		;off: 1789
	.data.w	.Ldw_str_begin+721
	.data.b	36
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1750

	.data.b	52
	.section	.debug_str		;off: 739
	.data.b	0
	.section	.debug_info		;off: 1801
	.data.w	.Ldw_str_begin+739
	.data.b	45
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 740
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,77,65,83,84,69,82,0
	.section	.debug_info		;off: 1811
	.data.w	.Ldw_str_begin+740
	.data.b	46
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 764
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,49,0
	.section	.debug_info		;off: 1820
	.data.w	.Ldw_str_begin+764
	.data.b	47
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 788
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,50,0
	.section	.debug_info		;off: 1829
	.data.w	.Ldw_str_begin+788
	.data.b	48
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 812
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,51,0
	.section	.debug_info		;off: 1838
	.data.w	.Ldw_str_begin+812
	.data.b	49
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 836
	.data.b	83,97,114,97,100,99,95,67,111,110,118,101,114,116,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 1848
	.data.w	.Ldw_str_begin+836
	.data.b	50
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1800

	.data.b	52
	.section	.debug_str		;off: 859
	.data.b	0
	.section	.debug_info		;off: 1860
	.data.w	.Ldw_str_begin+859
	.data.b	55
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 860
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,83,84,79,80,0
	.section	.debug_info		;off: 1870
	.data.w	.Ldw_str_begin+860
	.data.b	56
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 882
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,70,79,76,76,79,87,84,73,77,69,82,0
	.section	.debug_info		;off: 1879
	.data.w	.Ldw_str_begin+882
	.data.b	57
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 911
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,70,79,76,76,79,87,84,73,77,69,82,95,79,78,76,89,79,78,67,69,0
	.section	.debug_info		;off: 1888
	.data.w	.Ldw_str_begin+911
	.data.b	58
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 949
	.data.b	83,97,114,97,100,99,95,84,105,109,101,114,77,111,100,101,0
	.section	.debug_info		;off: 1898
	.data.w	.Ldw_str_begin+949
	.data.b	60
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1859

	.data.b	52
	.section	.debug_str		;off: 966
	.data.b	0
	.section	.debug_info		;off: 1910
	.data.w	.Ldw_str_begin+966
	.data.b	64
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 967
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,76,79,87,69,83,84,0
	.section	.debug_info		;off: 1920
	.data.w	.Ldw_str_begin+967
	.data.b	65
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 995
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,76,79,87,0
	.section	.debug_info		;off: 1929
	.data.w	.Ldw_str_begin+995
	.data.b	66
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1020
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,72,73,71,72,0
	.section	.debug_info		;off: 1938
	.data.w	.Ldw_str_begin+1020
	.data.b	67
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1046
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,72,73,71,72,69,83,84,0
	.section	.debug_info		;off: 1947
	.data.w	.Ldw_str_begin+1046
	.data.b	68
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1075
	.data.b	83,97,114,97,100,99,95,65,114,98,105,116,101,114,80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 1957
	.data.w	.Ldw_str_begin+1075
	.data.b	69
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1909

	.data.b	52
	.section	.debug_str		;off: 1098
	.data.b	0
	.section	.debug_info		;off: 1969
	.data.w	.Ldw_str_begin+1098
	.data.b	73
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1099
	.data.b	83,65,82,65,68,67,95,83,84,65,82,84,77,79,68,69,95,87,65,73,84,70,79,82,83,84,65,82,84,0
	.section	.debug_info		;off: 1979
	.data.w	.Ldw_str_begin+1099
	.data.b	74
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1129
	.data.b	83,65,82,65,68,67,95,83,84,65,82,84,77,79,68,69,95,67,65,78,67,69,76,73,78,74,69,67,84,82,69,80,69,65,84,0
	.section	.debug_info		;off: 1988
	.data.w	.Ldw_str_begin+1129
	.data.b	75
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1165
	.data.b	83,97,114,97,100,99,95,83,116,97,114,116,77,111,100,101,0
	.section	.debug_info		;off: 1998
	.data.w	.Ldw_str_begin+1165
	.data.b	76
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1968

	.data.b	52
	.section	.debug_str		;off: 1182
	.data.b	0
	.section	.debug_info		;off: 2010
	.data.w	.Ldw_str_begin+1182
	.data.b	80
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1183
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,48,0
	.section	.debug_info		;off: 2020
	.data.w	.Ldw_str_begin+1183
	.data.b	81
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1205
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,0
	.section	.debug_info		;off: 2029
	.data.w	.Ldw_str_begin+1205
	.data.b	82
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1227
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,50,0
	.section	.debug_info		;off: 2038
	.data.w	.Ldw_str_begin+1227
	.data.b	83
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1249
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,51,0
	.section	.debug_info		;off: 2047
	.data.w	.Ldw_str_begin+1249
	.data.b	84
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1271
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,52,0
	.section	.debug_info		;off: 2056
	.data.w	.Ldw_str_begin+1271
	.data.b	85
	.data.b	5
	.data.b	36
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1293
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,53,0
	.section	.debug_info		;off: 2065
	.data.w	.Ldw_str_begin+1293
	.data.b	86
	.data.b	5
	.data.b	36
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 1315
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,54,0
	.section	.debug_info		;off: 2074
	.data.w	.Ldw_str_begin+1315
	.data.b	87
	.data.b	5
	.data.b	36
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 1337
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,55,0
	.section	.debug_info		;off: 2083
	.data.w	.Ldw_str_begin+1337
	.data.b	88
	.data.b	5
	.data.b	36
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 1359
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,56,0
	.section	.debug_info		;off: 2092
	.data.w	.Ldw_str_begin+1359
	.data.b	89
	.data.b	5
	.data.b	36
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 1381
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,57,0
	.section	.debug_info		;off: 2101
	.data.w	.Ldw_str_begin+1381
	.data.b	90
	.data.b	5
	.data.b	36
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 1403
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,48,0
	.section	.debug_info		;off: 2110
	.data.w	.Ldw_str_begin+1403
	.data.b	91
	.data.b	5
	.data.b	36
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 1426
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,49,0
	.section	.debug_info		;off: 2119
	.data.w	.Ldw_str_begin+1426
	.data.b	92
	.data.b	5
	.data.b	36
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 1449
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,50,0
	.section	.debug_info		;off: 2128
	.data.w	.Ldw_str_begin+1449
	.data.b	93
	.data.b	5
	.data.b	36
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1472
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,51,0
	.section	.debug_info		;off: 2137
	.data.w	.Ldw_str_begin+1472
	.data.b	94
	.data.b	5
	.data.b	36
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 1495
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,52,0
	.section	.debug_info		;off: 2146
	.data.w	.Ldw_str_begin+1495
	.data.b	95
	.data.b	5
	.data.b	36
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 1518
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,53,0
	.section	.debug_info		;off: 2155
	.data.w	.Ldw_str_begin+1518
	.data.b	96
	.data.b	5
	.data.b	36
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1541
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 2165
	.data.w	.Ldw_str_begin+1541
	.data.b	97
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2009

	.data.b	52
	.section	.debug_str		;off: 1562
	.data.b	0
	.section	.debug_info		;off: 2177
	.data.w	.Ldw_str_begin+1562
	.data.b	102
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1563
	.data.b	83,65,82,65,68,67,95,79,86,69,82,87,82,73,84,69,77,79,68,69,0
	.section	.debug_info		;off: 2187
	.data.w	.Ldw_str_begin+1563
	.data.b	103
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1584
	.data.b	83,65,82,65,68,67,95,87,65,73,84,70,79,82,82,69,65,68,77,79,68,69,0
	.section	.debug_info		;off: 2196
	.data.w	.Ldw_str_begin+1584
	.data.b	104
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1607
	.data.b	83,97,114,97,100,99,95,83,116,111,114,97,103,101,77,111,100,101,0
	.section	.debug_info		;off: 2206
	.data.w	.Ldw_str_begin+1607
	.data.b	105
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2176

	.data.b	52
	.section	.debug_str		;off: 1626
	.data.b	0
	.section	.debug_info		;off: 2218
	.data.w	.Ldw_str_begin+1626
	.data.b	110
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1627
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,48,0
	.section	.debug_info		;off: 2228
	.data.w	.Ldw_str_begin+1627
	.data.b	111
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1655
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,49,0
	.section	.debug_info		;off: 2237
	.data.w	.Ldw_str_begin+1655
	.data.b	112
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1683
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,50,0
	.section	.debug_info		;off: 2246
	.data.w	.Ldw_str_begin+1683
	.data.b	113
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1711
	.data.b	83,97,114,97,100,99,95,82,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2256
	.data.w	.Ldw_str_begin+1711
	.data.b	114
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2217

	.data.b	52
	.section	.debug_str		;off: 1732
	.data.b	0
	.section	.debug_info		;off: 2268
	.data.w	.Ldw_str_begin+1732
	.data.b	141,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1733
	.data.b	83,65,82,65,68,67,95,72,68,73,95,79,70,70,0
	.section	.debug_info		;off: 2279
	.data.w	.Ldw_str_begin+1733
	.data.b	142,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1748
	.data.b	83,65,82,65,68,67,95,72,68,73,95,70,67,0
	.section	.debug_info		;off: 2289
	.data.w	.Ldw_str_begin+1748
	.data.b	144,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1762
	.data.b	83,65,82,65,68,67,95,72,68,73,95,71,84,77,0
	.section	.debug_info		;off: 2299
	.data.w	.Ldw_str_begin+1762
	.data.b	146,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1777
	.data.b	83,65,82,65,68,67,95,72,68,73,95,82,68,67,0
	.section	.debug_info		;off: 2309
	.data.w	.Ldw_str_begin+1777
	.data.b	148,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1792
	.data.b	83,97,114,97,100,99,95,72,100,105,0
	.section	.debug_info		;off: 2320
	.data.w	.Ldw_str_begin+1792
	.data.b	150,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2267

	.data.b	71
	.data.b	159,1
	.data.b	1
	.data.b	36
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1803
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 2340
	.data.w	.Ldw_str_begin+1803
	.data.b	160,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1810
	.data.b	115,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 2357
	.data.w	.Ldw_str_begin+1810
	.data.b	161,1
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1819
	.data.b	116,105,109,101,114,109,111,100,101,0
	.section	.debug_info		;off: 2374
	.data.w	.Ldw_str_begin+1819
	.data.b	162,1
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+1897
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1829
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,66,121,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2392
	.data.w	.Ldw_str_begin+1829
	.data.b	163,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2332

	.data.b	71
	.data.b	167,1
	.data.b	1
	.data.b	36
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1857
	.data.b	112,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 2412
	.data.w	.Ldw_str_begin+1857
	.data.b	168,1
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+1956
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1866
	.data.b	115,116,97,114,116,77,111,100,101,0
	.section	.debug_info		;off: 2429
	.data.w	.Ldw_str_begin+1866
	.data.b	169,1
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+1997
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1876
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 2446
	.data.w	.Ldw_str_begin+1876
	.data.b	170,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1883
	.data.b	83,97,114,97,100,99,95,81,117,101,117,101,67,111,109,109,111,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2464
	.data.w	.Ldw_str_begin+1883
	.data.b	171,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2404

	.data.b	52
	.section	.debug_str		;off: 1908
	.data.b	0
	.section	.debug_info		;off: 2477
	.data.w	.Ldw_str_begin+1908
	.data.b	188,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1909
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 2488
	.data.w	.Ldw_str_begin+1909
	.data.b	189,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1941
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,73,78,66,79,85,78,68,65,82,89,0
	.section	.debug_info		;off: 2498
	.data.w	.Ldw_str_begin+1941
	.data.b	190,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1976
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,79,85,84,66,79,85,78,68,65,82,89,0
	.section	.debug_info		;off: 2508
	.data.w	.Ldw_str_begin+1976
	.data.b	191,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2012
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,69,78,65,66,76,69,0
	.section	.debug_info		;off: 2518
	.data.w	.Ldw_str_begin+2012
	.data.b	192,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2043
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,73,110,116,101,114,114,117,112,116,77,111,100,101,0
	.section	.debug_info		;off: 2529
	.data.w	.Ldw_str_begin+2043
	.data.b	193,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2476

	.data.b	52
	.section	.debug_str		;off: 2071
	.data.b	0
	.section	.debug_info		;off: 2542
	.data.w	.Ldw_str_begin+2071
	.data.b	210,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2072
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,68,73,83,65,66,76,69,68,0
	.section	.debug_info		;off: 2553
	.data.w	.Ldw_str_begin+2072
	.data.b	211,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2099
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,65,76,87,65,89,83,0
	.section	.debug_info		;off: 2563
	.data.w	.Ldw_str_begin+2099
	.data.b	212,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2124
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,71,65,84,73,78,71,72,73,71,72,0
	.section	.debug_info		;off: 2573
	.data.w	.Ldw_str_begin+2124
	.data.b	213,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2153
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,71,65,84,73,78,71,76,79,87,0
	.section	.debug_info		;off: 2583
	.data.w	.Ldw_str_begin+2153
	.data.b	215,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2181
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,77,111,100,101,0
	.section	.debug_info		;off: 2594
	.data.w	.Ldw_str_begin+2181
	.data.b	217,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2541

	.data.b	52
	.section	.debug_str		;off: 2199
	.data.b	0
	.section	.debug_info		;off: 2607
	.data.w	.Ldw_str_begin+2199
	.data.b	221,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2200
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,78,79,69,88,84,69,82,78,65,76,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+2200
	.data.b	222,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2237
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,69,68,71,69,0
	.section	.debug_info		;off: 2628
	.data.w	.Ldw_str_begin+2237
	.data.b	223,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2268
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,69,68,71,69,0
	.section	.debug_info		;off: 2638
	.data.w	.Ldw_str_begin+2268
	.data.b	224,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2298
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,65,78,89,69,68,71,69,0
	.section	.debug_info		;off: 2648
	.data.w	.Ldw_str_begin+2298
	.data.b	225,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2325
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 2659
	.data.w	.Ldw_str_begin+2325
	.data.b	226,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2606

	.data.b	52
	.section	.debug_str		;off: 2344
	.data.b	0
	.section	.debug_info		;off: 2672
	.data.w	.Ldw_str_begin+2344
	.data.b	230,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2345
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,48,0
	.section	.debug_info		;off: 2683
	.data.w	.Ldw_str_begin+2345
	.data.b	231,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2378
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,49,0
	.section	.debug_info		;off: 2693
	.data.w	.Ldw_str_begin+2378
	.data.b	232,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2411
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,52,0
	.section	.debug_info		;off: 2703
	.data.w	.Ldw_str_begin+2411
	.data.b	233,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2444
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,50,0
	.section	.debug_info		;off: 2713
	.data.w	.Ldw_str_begin+2444
	.data.b	234,1
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 2477
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,51,0
	.section	.debug_info		;off: 2723
	.data.w	.Ldw_str_begin+2477
	.data.b	235,1
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 2510
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,69,88,84,73,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2733
	.data.w	.Ldw_str_begin+2510
	.data.b	236,1
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 2543
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,81,85,69,85,69,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2743
	.data.w	.Ldw_str_begin+2543
	.data.b	237,1
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2577
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2754
	.data.w	.Ldw_str_begin+2577
	.data.b	238,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2671

	.data.b	52
	.section	.debug_str		;off: 2597
	.data.b	0
	.section	.debug_info		;off: 2767
	.data.w	.Ldw_str_begin+2597
	.data.b	242,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2598
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,82,68,67,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2778
	.data.w	.Ldw_str_begin+2598
	.data.b	243,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2631
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,52,0
	.section	.debug_info		;off: 2788
	.data.w	.Ldw_str_begin+2631
	.data.b	244,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2665
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,69,88,84,73,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2798
	.data.w	.Ldw_str_begin+2665
	.data.b	245,1
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 2699
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,48,0
	.section	.debug_info		;off: 2808
	.data.w	.Ldw_str_begin+2699
	.data.b	246,1
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 2733
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,49,0
	.section	.debug_info		;off: 2818
	.data.w	.Ldw_str_begin+2733
	.data.b	247,1
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 2767
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,50,0
	.section	.debug_info		;off: 2828
	.data.w	.Ldw_str_begin+2767
	.data.b	248,1
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 2801
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,51,0
	.section	.debug_info		;off: 2838
	.data.w	.Ldw_str_begin+2801
	.data.b	249,1
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 2835
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2848
	.data.w	.Ldw_str_begin+2835
	.data.b	250,1
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 2874
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,79,77,77,79,78,48,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2858
	.data.w	.Ldw_str_begin+2874
	.data.b	251,1
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 2920
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,79,77,77,79,78,49,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2868
	.data.w	.Ldw_str_begin+2920
	.data.b	252,1
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 2966
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,81,85,69,85,69,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 2878
	.data.w	.Ldw_str_begin+2966
	.data.b	253,1
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3001
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2889
	.data.w	.Ldw_str_begin+3001
	.data.b	254,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2766

	.data.b	71
	.data.b	154,2
	.data.b	1
	.data.b	35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3022
	.data.b	103,97,116,105,110,103,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2909
	.data.w	.Ldw_str_begin+3022
	.data.b	155,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+2753
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3035
	.data.b	116,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2926
	.data.w	.Ldw_str_begin+3035
	.data.b	156,2
	.data.b	26
	.data.b	35
	.data.w	.Ldw_begin+2888
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3049
	.data.b	103,97,116,105,110,103,77,111,100,101,0
	.section	.debug_info		;off: 2943
	.data.w	.Ldw_str_begin+3049
	.data.b	157,2
	.data.b	23
	.data.b	35
	.data.w	.Ldw_begin+2593
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3060
	.data.b	116,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 2960
	.data.w	.Ldw_str_begin+3060
	.data.b	158,2
	.data.b	24
	.data.b	35
	.data.w	.Ldw_begin+2658
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3072
	.data.b	116,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2977
	.data.w	.Ldw_str_begin+3072
	.data.b	159,2
	.data.b	33
	.data.b	35
	.data.w	.Ldw_begin+2391
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3084
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,84,114,105,103,103,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2995
	.data.w	.Ldw_str_begin+3084
	.data.b	160,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+2901

	.data.b	71
	.data.b	164,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3111
	.data.b	108,111,119,66,111,117,110,100,97,114,121,0
	.section	.debug_info		;off: 3015
	.data.w	.Ldw_str_begin+3111
	.data.b	165,2
	.data.b	12
	.data.b	35
	.data.w	.Ldw_begin+1275
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3123
	.data.b	104,105,103,104,66,111,117,110,100,97,114,121,0
	.section	.debug_info		;off: 3032
	.data.w	.Ldw_str_begin+3123
	.data.b	166,2
	.data.b	12
	.data.b	35
	.data.w	.Ldw_begin+1275
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3136
	.data.b	83,97,114,97,100,99,95,66,111,117,110,100,97,114,121,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3050
	.data.w	.Ldw_str_begin+3136
	.data.b	167,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+3007

	.data.b	71
	.data.b	185,2
	.data.b	1
	.data.b	35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3158
	.data.b	99,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 3070
	.data.w	.Ldw_str_begin+3158
	.data.b	186,2
	.data.b	26
	.data.b	35
	.data.w	.Ldw_begin+2164
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3172
	.data.b	115,116,111,114,97,103,101,77,111,100,101,0
	.section	.debug_info		;off: 3087
	.data.w	.Ldw_str_begin+3172
	.data.b	187,2
	.data.b	24
	.data.b	35
	.data.w	.Ldw_begin+2205
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3184
	.data.b	101,110,97,98,108,101,68,109,97,0
	.section	.debug_info		;off: 3104
	.data.w	.Ldw_str_begin+3184
	.data.b	188,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3194
	.data.b	114,105,103,104,116,65,108,105,103,110,101,100,83,116,111,114,97,103,101,0
	.section	.debug_info		;off: 3121
	.data.w	.Ldw_str_begin+3194
	.data.b	189,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	9
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3214
	.data.b	101,110,97,98,108,101,83,121,110,99,104,114,111,110,105,122,101,0
	.section	.debug_info		;off: 3138
	.data.w	.Ldw_str_begin+3214
	.data.b	190,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	10
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3232
	.data.b	98,111,117,110,100,97,114,121,82,97,110,103,101,0
	.section	.debug_info		;off: 3155
	.data.w	.Ldw_str_begin+3232
	.data.b	192,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	11
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3246
	.data.b	98,111,117,110,100,97,114,121,82,101,115,117,108,116,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 3172
	.data.w	.Ldw_str_begin+3246
	.data.b	194,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3268
	.data.b	104,100,105,73,102,69,110,0
	.section	.debug_info		;off: 3189
	.data.w	.Ldw_str_begin+3268
	.data.b	195,2
	.data.b	16
	.data.b	35
	.data.w	.Ldw_begin+2319
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3276
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3207
	.data.w	.Ldw_str_begin+3276
	.data.b	196,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+3062

	.data.b	71
	.data.b	200,2
	.data.b	1
	.data.b	35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3297
	.data.b	99,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 3227
	.data.w	.Ldw_str_begin+3297
	.data.b	201,2
	.data.b	26
	.data.b	35
	.data.w	.Ldw_begin+2164
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3311
	.data.b	101,110,97,98,108,101,68,109,97,0
	.section	.debug_info		;off: 3244
	.data.w	.Ldw_str_begin+3311
	.data.b	202,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3321
	.data.b	101,110,97,98,108,101,83,121,110,99,104,114,111,110,105,122,101,0
	.section	.debug_info		;off: 3261
	.data.w	.Ldw_str_begin+3321
	.data.b	203,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3339
	.data.b	98,111,117,110,100,97,114,121,82,97,110,103,101,0
	.section	.debug_info		;off: 3278
	.data.w	.Ldw_str_begin+3339
	.data.b	205,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3353
	.data.b	98,111,117,110,100,97,114,121,82,101,115,117,108,116,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 3295
	.data.w	.Ldw_str_begin+3353
	.data.b	207,2
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	7
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3375
	.data.b	104,100,105,73,102,69,110,0
	.section	.debug_info		;off: 3312
	.data.w	.Ldw_str_begin+3375
	.data.b	208,2
	.data.b	16
	.data.b	35
	.data.w	.Ldw_begin+2319
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3383
	.data.b	83,97,114,97,100,99,95,68,121,110,97,67,104,97,110,110,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3330
	.data.w	.Ldw_str_begin+3383
	.data.b	209,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+3219

	.data.b	71
	.data.b	214,2
	.data.b	1
	.data.b	35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3408
	.data.b	100,105,118,105,100,101,114,0
	.section	.debug_info		;off: 3350
	.data.w	.Ldw_str_begin+3408
	.data.b	215,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3416
	.data.b	115,97,109,112,108,101,84,105,109,101,0
	.section	.debug_info		;off: 3367
	.data.w	.Ldw_str_begin+3416
	.data.b	216,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3427
	.data.b	114,101,115,111,108,117,116,105,111,110,0
	.section	.debug_info		;off: 3384
	.data.w	.Ldw_str_begin+3427
	.data.b	217,2
	.data.b	23
	.data.b	35
	.data.w	.Ldw_begin+1788
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3438
	.data.b	99,111,110,118,101,114,116,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 3401
	.data.w	.Ldw_str_begin+3438
	.data.b	218,2
	.data.b	28
	.data.b	35
	.data.w	.Ldw_begin+1847
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3454
	.data.b	114,101,113,117,101,115,116,81,117,101,117,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3418
	.data.w	.Ldw_str_begin+3454
	.data.b	219,2
	.data.b	30
	.data.b	35
	.data.w	.Ldw_begin+307
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3473
	.data.b	83,97,114,97,100,99,95,77,111,100,117,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3436
	.data.w	.Ldw_str_begin+3473
	.data.b	220,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+3342

	.data.b	45
	.section	.debug_str		;off: 3493
	.data.b	65,100,99,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 3449
	.data.w	.Ldw_str_begin+3493
	.data.b	53
	.data.b	15
	.data.b	12
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 3509
	.data.b	65,100,99,95,71,114,111,117,112,84,121,112,101,0
	.section	.debug_info		;off: 3461
	.data.w	.Ldw_str_begin+3509
	.data.b	57
	.data.b	16
	.data.b	12
	.data.w	.Ldw_begin+1275

	.data.b	45
	.section	.debug_str		;off: 3523
	.data.b	65,100,99,95,86,97,108,117,101,71,114,111,117,112,84,121,112,101,0
	.section	.debug_info		;off: 3473
	.data.w	.Ldw_str_begin+3523
	.data.b	62
	.data.b	16
	.data.b	12
	.data.w	.Ldw_begin+1275

	.data.b	45
	.section	.debug_str		;off: 3542
	.data.b	65,100,99,95,71,114,111,117,112,68,101,102,84,121,112,101,0
	.section	.debug_info		;off: 3485
	.data.w	.Ldw_str_begin+3542
	.data.b	83
	.data.b	25
	.data.b	12
	.data.w	.Ldw_begin+3448

	.data.b	45
	.section	.debug_str		;off: 3559
	.data.b	65,100,99,95,83,116,114,101,97,109,78,117,109,83,97,109,112,108,101,84,121,112,101,0
	.section	.debug_info		;off: 3497
	.data.w	.Ldw_str_begin+3559
	.data.b	87
	.data.b	15
	.data.b	12
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 3583
	.data.b	65,100,99,95,72,119,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 3509
	.data.w	.Ldw_str_begin+3583
	.data.b	105
	.data.b	15
	.data.b	12
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 3598
	.data.b	65,100,99,95,78,111,116,105,102,70,99,116,80,116,114,84,121,112,101,0
	.section	.debug_info		;off: 3521
	.data.w	.Ldw_str_begin+3598
	.data.b	110
	.data.b	16
	.data.b	12
	.data.w	.Ldw_begin+326

	.data.b	52
	.section	.debug_str		;off: 3618
	.data.b	0
	.section	.debug_info		;off: 3533
	.data.w	.Ldw_str_begin+3618
	.data.b	128,1
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3619
	.data.b	65,68,67,95,73,68,76,69,0
	.section	.debug_info		;off: 3544
	.data.w	.Ldw_str_begin+3619
	.data.b	131,1
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3628
	.data.b	65,68,67,95,66,85,83,89,0
	.section	.debug_info		;off: 3554
	.data.w	.Ldw_str_begin+3628
	.data.b	134,1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3637
	.data.b	65,68,67,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 3564
	.data.w	.Ldw_str_begin+3637
	.data.b	137,1
	.data.b	5
	.data.b	12
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 3651
	.data.b	65,68,67,95,83,84,82,69,65,77,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 3574
	.data.w	.Ldw_str_begin+3651
	.data.b	141,1
	.data.b	5
	.data.b	12
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3672
	.data.b	65,100,99,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 3585
	.data.w	.Ldw_str_begin+3672
	.data.b	142,1
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3532

	.data.b	52
	.section	.debug_str		;off: 3687
	.data.b	0
	.section	.debug_info		;off: 3598
	.data.w	.Ldw_str_begin+3687
	.data.b	146,1
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3688
	.data.b	65,68,67,95,84,82,73,71,71,95,83,82,67,95,83,87,0
	.section	.debug_info		;off: 3609
	.data.w	.Ldw_str_begin+3688
	.data.b	148,1
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3705
	.data.b	65,68,67,95,84,82,73,71,71,95,83,82,67,95,72,87,0
	.section	.debug_info		;off: 3619
	.data.w	.Ldw_str_begin+3705
	.data.b	150,1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3722
	.data.b	65,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,84,121,112,101,0
	.section	.debug_info		;off: 3630
	.data.w	.Ldw_str_begin+3722
	.data.b	151,1
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3597

	.data.b	52
	.section	.debug_str		;off: 3744
	.data.b	0
	.section	.debug_info		;off: 3643
	.data.w	.Ldw_str_begin+3744
	.data.b	155,1
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3745
	.data.b	65,68,67,95,67,79,78,86,95,77,79,68,69,95,79,78,69,83,72,79,84,0
	.section	.debug_info		;off: 3654
	.data.w	.Ldw_str_begin+3745
	.data.b	161,1
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3767
	.data.b	65,68,67,95,67,79,78,86,95,77,79,68,69,95,67,79,78,84,73,78,85,79,85,83,0
	.section	.debug_info		;off: 3664
	.data.w	.Ldw_str_begin+3767
	.data.b	165,1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3792
	.data.b	65,100,99,95,71,114,111,117,112,67,111,110,118,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 3675
	.data.w	.Ldw_str_begin+3792
	.data.b	166,1
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3642

	.data.b	52
	.section	.debug_str		;off: 3814
	.data.b	0
	.section	.debug_info		;off: 3688
	.data.w	.Ldw_str_begin+3814
	.data.b	170,1
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3815
	.data.b	65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,76,73,78,69,65,82,0
	.section	.debug_info		;off: 3699
	.data.w	.Ldw_str_begin+3815
	.data.b	173,1
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3840
	.data.b	65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,67,73,82,67,85,76,65,82,0
	.section	.debug_info		;off: 3709
	.data.w	.Ldw_str_begin+3840
	.data.b	176,1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3867
	.data.b	65,100,99,95,83,116,114,101,97,109,66,117,102,102,101,114,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 3720
	.data.w	.Ldw_str_begin+3867
	.data.b	177,1
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3687

	.data.b	52
	.section	.debug_str		;off: 3892
	.data.b	0
	.section	.debug_info		;off: 3733
	.data.w	.Ldw_str_begin+3892
	.data.b	181,1
	.data.b	1
	.data.b	12
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3893
	.data.b	65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,73,78,71,76,69,0
	.section	.debug_info		;off: 3744
	.data.w	.Ldw_str_begin+3893
	.data.b	183,1
	.data.b	5
	.data.b	12
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3916
	.data.b	65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,84,82,69,65,77,73,78,71,0
	.section	.debug_info		;off: 3754
	.data.w	.Ldw_str_begin+3916
	.data.b	185,1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3942
	.data.b	65,100,99,95,71,114,111,117,112,65,99,99,101,115,115,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 3765
	.data.w	.Ldw_str_begin+3942
	.data.b	186,1
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3732

	.data.b	71
	.data.b	175,2
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3966
	.data.b	67,111,114,101,72,119,85,110,105,116,73,100,120,0
	.section	.debug_info		;off: 3785
	.data.w	.Ldw_str_begin+3966
	.data.b	177,2
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3508
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3980
	.data.b	72,119,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 3802
	.data.w	.Ldw_str_begin+3980
	.data.b	179,2
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3992
	.data.b	65,100,99,95,72,87,85,110,105,116,67,111,114,101,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 3820
	.data.w	.Ldw_str_begin+3992
	.data.b	180,2
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3777

	.data.b	71
	.data.b	150,3
	.data.b	1
	.data.b	12
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4014
	.data.b	73,115,83,121,110,99,67,104,69,120,105,115,116,115,0
	.section	.debug_info		;off: 3840
	.data.w	.Ldw_str_begin+4014
	.data.b	154,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4029
	.data.b	78,117,109,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 3857
	.data.w	.Ldw_str_begin+4029
	.data.b	157,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3496
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4040
	.data.b	73,110,116,67,104,77,97,115,107,0
	.section	.debug_info		;off: 3874
	.data.w	.Ldw_str_begin+4040
	.data.b	159,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1275
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4050
	.data.b	78,111,116,105,102,70,99,116,80,116,114,0
	.section	.debug_info		;off: 3891
	.data.w	.Ldw_str_begin+4050
	.data.b	163,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3520
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4062
	.data.b	71,114,111,117,112,68,101,102,105,110,105,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3908
	.data.w	.Ldw_str_begin+4062
	.data.b	167,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+346
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4081
	.data.b	71,114,111,117,112,82,101,115,82,101,103,80,116,114,0
	.section	.debug_info		;off: 3925
	.data.w	.Ldw_str_begin+4081
	.data.b	170,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+351
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4096
	.data.b	72,119,84,114,105,103,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3942
	.data.w	.Ldw_str_begin+4096
	.data.b	174,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+361
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4112
	.data.b	82,101,115,117,108,116,65,99,99,117,109,78,117,109,0
	.section	.debug_info		;off: 3959
	.data.w	.Ldw_str_begin+4112
	.data.b	177,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4127
	.data.b	84,114,105,103,103,83,114,99,0
	.section	.debug_info		;off: 3976
	.data.w	.Ldw_str_begin+4127
	.data.b	179,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3629
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4136
	.data.b	71,114,112,82,101,113,117,101,115,116,83,114,99,0
	.section	.debug_info		;off: 3993
	.data.w	.Ldw_str_begin+4136
	.data.b	181,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+2255
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4150
	.data.b	65,99,99,101,115,115,77,111,100,101,0
	.section	.debug_info		;off: 4010
	.data.w	.Ldw_str_begin+4150
	.data.b	183,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3764
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4161
	.data.b	67,111,110,118,77,111,100,101,0
	.section	.debug_info		;off: 4027
	.data.w	.Ldw_str_begin+4161
	.data.b	185,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3674
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4170
	.data.b	83,116,114,101,97,109,66,117,102,102,101,114,77,111,100,101,0
	.section	.debug_info		;off: 4044
	.data.w	.Ldw_str_begin+4170
	.data.b	187,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3719
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4187
	.data.b	65,100,99,95,71,114,111,117,112,67,102,103,84,121,112,101,0
	.section	.debug_info		;off: 4062
	.data.w	.Ldw_str_begin+4187
	.data.b	193,3
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+3832

	.data.b	71
	.data.b	200,3
	.data.b	1
	.data.b	12
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4204
	.data.b	67,104,76,105,109,105,116,67,104,107,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 4082
	.data.w	.Ldw_str_begin+4204
	.data.b	202,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3049
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4225
	.data.b	67,104,76,105,109,105,116,67,104,107,73,110,116,114,77,111,100,0
	.section	.debug_info		;off: 4099
	.data.w	.Ldw_str_begin+4225
	.data.b	204,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+2528
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4243
	.data.b	65,100,99,95,67,104,97,110,110,101,108,76,105,109,105,116,67,104,101,99,107,84,121,112,101,0
	.section	.debug_info		;off: 4117
	.data.w	.Ldw_str_begin+4243
	.data.b	205,3
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+4074

	.data.b	71
	.data.b	212,3
	.data.b	1
	.data.b	12
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4269
	.data.b	67,104,76,105,109,105,116,67,104,101,99,107,105,110,103,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4137
	.data.w	.Ldw_str_begin+4269
	.data.b	215,3
	.data.b	38
	.data.b	12
	.data.w	.Ldw_begin+371
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4294
	.data.b	67,104,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 4154
	.data.w	.Ldw_str_begin+4294
	.data.b	218,3
	.data.b	37
	.data.b	12
	.data.w	.Ldw_begin+3206
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4307
	.data.b	67,104,82,117,110,116,105,109,101,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 4171
	.data.w	.Ldw_str_begin+4307
	.data.b	220,3
	.data.b	37
	.data.b	12
	.data.w	.Ldw_begin+3329
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4327
	.data.b	65,100,99,95,67,104,97,110,110,101,108,67,102,103,84,121,112,101,0
	.section	.debug_info		;off: 4189
	.data.w	.Ldw_str_begin+4327
	.data.b	221,3
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+4129

	.data.b	71
	.data.b	227,3
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4346
	.data.b	65,100,99,72,119,85,110,105,116,0
	.section	.debug_info		;off: 4209
	.data.w	.Ldw_str_begin+4346
	.data.b	229,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+3508
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4356
	.data.b	82,115,108,116,72,108,100,77,116,104,100,0
	.section	.debug_info		;off: 4226
	.data.w	.Ldw_str_begin+4356
	.data.b	232,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4368
	.data.b	72,119,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4243
	.data.w	.Ldw_str_begin+4368
	.data.b	235,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+381
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4377
	.data.b	83,121,110,99,71,114,112,83,108,97,118,101,72,119,80,116,114,0
	.section	.debug_info		;off: 4260
	.data.w	.Ldw_str_begin+4377
	.data.b	238,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+391
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4395
	.data.b	67,104,78,117,109,0
	.section	.debug_info		;off: 4277
	.data.w	.Ldw_str_begin+4395
	.data.b	241,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4401
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4294
	.data.w	.Ldw_str_begin+4401
	.data.b	243,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+401
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4410
	.data.b	71,114,112,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4311
	.data.w	.Ldw_str_begin+4410
	.data.b	245,3
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+411
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4420
	.data.b	84,111,116,67,102,103,71,114,112,115,0
	.section	.debug_info		;off: 4328
	.data.w	.Ldw_str_begin+4420
	.data.b	251,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4431
	.data.b	73,110,100,101,120,71,114,112,115,67,111,114,101,0
	.section	.debug_info		;off: 4345
	.data.w	.Ldw_str_begin+4431
	.data.b	254,3
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	25
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4445
	.data.b	73,115,73,110,116,69,110,0
	.section	.debug_info		;off: 4362
	.data.w	.Ldw_str_begin+4445
	.data.b	129,4
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	26
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4453
	.data.b	65,100,99,95,75,101,114,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4380
	.data.w	.Ldw_str_begin+4453
	.data.b	131,4
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+4201

	.data.b	71
	.data.b	137,4
	.data.b	1
	.data.b	12
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4474
	.data.b	77,97,120,67,111,114,101,72,119,85,110,105,116,0
	.section	.debug_info		;off: 4400
	.data.w	.Ldw_str_begin+4474
	.data.b	139,4
	.data.b	40
	.data.b	12
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4488
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4417
	.data.w	.Ldw_str_begin+4488
	.data.b	141,4
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+421
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4504
	.data.b	65,100,99,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4435
	.data.w	.Ldw_str_begin+4504
	.data.b	142,4
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+4392

	.data.b	71
	.data.b	148,4
	.data.b	1
	.data.b	12
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4523
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4455
	.data.w	.Ldw_str_begin+4523
	.data.b	150,4
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+436
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4537
	.data.b	72,119,85,110,105,116,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 4472
	.data.w	.Ldw_str_begin+4537
	.data.b	152,4
	.data.b	41
	.data.b	12
	.data.w	.Ldw_begin+457
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4553
	.data.b	65,100,99,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4490
	.data.w	.Ldw_str_begin+4553
	.data.b	153,4
	.data.b	3
	.data.b	12
	.data.w	.Ldw_begin+4447

	.data.b	45
	.section	.debug_str		;off: 4568
	.data.b	73,110,116,99,95,73,110,116,83,114,99,84,121,112,101,0
	.section	.debug_info		;off: 4503
	.data.w	.Ldw_str_begin+4568
	.data.b	48
	.data.b	16
	.data.b	41
	.data.w	.Ldw_begin+1275

	.data.b	52
	.section	.debug_str		;off: 4584
	.data.b	0
	.section	.debug_info		;off: 4515
	.data.w	.Ldw_str_begin+4584
	.data.b	94
	.data.b	1
	.data.b	47
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4585
	.data.b	68,69,77,79,95,73,68,76,69,0
	.section	.debug_info		;off: 4525
	.data.w	.Ldw_str_begin+4585
	.data.b	95
	.data.b	5
	.data.b	47
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4595
	.data.b	68,69,77,79,95,83,84,65,82,84,69,68,0
	.section	.debug_info		;off: 4534
	.data.w	.Ldw_str_begin+4595
	.data.b	96
	.data.b	5
	.data.b	47
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4608
	.data.b	68,101,109,111,95,83,116,97,114,116,117,112,84,121,112,101,0
	.section	.debug_info		;off: 4544
	.data.w	.Ldw_str_begin+4608
	.data.b	97
	.data.b	3
	.data.b	47
	.data.w	.Ldw_begin+4514

	.data.b	71
	.data.b	119
	.data.b	1
	.data.b	47
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4625
	.data.b	69,120,101,67,109,100,67,111,114,101,0
	.section	.debug_info		;off: 4562
	.data.w	.Ldw_str_begin+4625
	.data.b	121
	.data.b	22
	.data.b	47
	.data.w	.Ldw_begin+1490
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4636
	.data.b	69,120,101,67,109,100,73,100,0
	.section	.debug_info		;off: 4578
	.data.w	.Ldw_str_begin+4636
	.data.b	123
	.data.b	22
	.data.b	47
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4645
	.data.b	68,101,109,111,83,116,97,114,116,117,112,70,108,103,0
	.section	.debug_info		;off: 4594
	.data.w	.Ldw_str_begin+4645
	.data.b	125
	.data.b	22
	.data.b	47
	.data.w	.Ldw_begin+4543
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4660
	.data.b	68,101,109,111,95,67,111,114,101,69,120,101,84,121,112,101,0
	.section	.debug_info		;off: 4611
	.data.w	.Ldw_str_begin+4660
	.data.b	126
	.data.b	3
	.data.b	47
	.data.w	.Ldw_begin+467

	.data.b	71
	.data.b	190,6
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4677
	.data.b	83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 4630
	.data.w	.Ldw_str_begin+4677
	.data.b	191,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4685
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 4651
	.data.w	.Ldw_str_begin+4685
	.data.b	192,6
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+472

	.data.b	71
	.data.b	196,6
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4705
	.data.b	68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 4671
	.data.w	.Ldw_str_begin+4705
	.data.b	197,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4714
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 4692
	.data.w	.Ldw_str_begin+4714
	.data.b	198,6
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+477

	.data.b	71
	.data.b	202,6
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4735
	.data.b	76,77,0
	.section	.debug_info		;off: 4712
	.data.w	.Ldw_str_begin+4735
	.data.b	203,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4738
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 4732
	.data.w	.Ldw_str_begin+4738
	.data.b	204,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4749
	.data.b	76,76,73,0
	.section	.debug_info		;off: 4752
	.data.w	.Ldw_str_begin+4749
	.data.b	205,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4753
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,66,105,116,115,0
	.section	.debug_info		;off: 4773
	.data.w	.Ldw_str_begin+4753
	.data.b	206,6
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+482

	.data.b	71
	.data.b	210,6
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4771
	.data.b	84,82,65,78,83,73,90,69,0
	.section	.debug_info		;off: 4793
	.data.w	.Ldw_str_begin+4771
	.data.b	211,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4780
	.data.b	83,66,83,73,90,69,0
	.section	.debug_info		;off: 4813
	.data.w	.Ldw_str_begin+4780
	.data.b	212,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	17
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4787
	.data.b	68,66,83,73,90,69,0
	.section	.debug_info		;off: 4833
	.data.w	.Ldw_str_begin+4787
	.data.b	213,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	14
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4794
	.data.b	83,87,73,68,84,72,0
	.section	.debug_info		;off: 4853
	.data.w	.Ldw_str_begin+4794
	.data.b	214,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	11
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4801
	.data.b	68,87,73,68,84,72,0
	.section	.debug_info		;off: 4873
	.data.w	.Ldw_str_begin+4801
	.data.b	215,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	8
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4808
	.data.b	83,0
	.section	.debug_info		;off: 4893
	.data.w	.Ldw_str_begin+4808
	.data.b	216,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4810
	.data.b	68,0
	.section	.debug_info		;off: 4913
	.data.w	.Ldw_str_begin+4810
	.data.b	217,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4812
	.data.b	83,73,0
	.section	.debug_info		;off: 4933
	.data.w	.Ldw_str_begin+4812
	.data.b	218,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4815
	.data.b	68,73,0
	.section	.debug_info		;off: 4953
	.data.w	.Ldw_str_begin+4815
	.data.b	219,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4818
	.data.b	65,77,0
	.section	.debug_info		;off: 4973
	.data.w	.Ldw_str_begin+4818
	.data.b	220,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4821
	.data.b	66,69,0
	.section	.debug_info		;off: 4993
	.data.w	.Ldw_str_begin+4821
	.data.b	221,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4824
	.data.b	67,69,0
	.section	.debug_info		;off: 5013
	.data.w	.Ldw_str_begin+4824
	.data.b	222,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4827
	.data.b	73,0
	.section	.debug_info		;off: 5033
	.data.w	.Ldw_str_begin+4827
	.data.b	223,6
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4829
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,95,66,105,116,115,0
	.section	.debug_info		;off: 5054
	.data.w	.Ldw_str_begin+4829
	.data.b	224,6
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+487

	.data.b	71
	.data.b	207,8
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4849
	.data.b	67,82,67,86,65,76,0
	.section	.debug_info		;off: 5074
	.data.w	.Ldw_str_begin+4849
	.data.b	208,8
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4856
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 5094
	.data.w	.Ldw_str_begin+4856
	.data.b	209,8
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+295
	.data.b	4
	.data.b	0
	.data.b	24
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4867
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,95,66,105,116,115,0
	.section	.debug_info		;off: 5115
	.data.w	.Ldw_str_begin+4867
	.data.b	210,8
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+492

	.data.b	73
	.data.b	227,10
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4889
	.data.b	85,0
	.section	.debug_info		;off: 5135
	.data.w	.Ldw_str_begin+4889
	.data.b	228,10
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4891
	.data.b	66,0
	.section	.debug_info		;off: 5152
	.data.w	.Ldw_str_begin+4891
	.data.b	229,10
	.data.b	25
	.data.b	67
	.data.w	.Ldw_begin+4650
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4893
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 5170
	.data.w	.Ldw_str_begin+4893
	.data.b	230,10
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5127

	.data.b	73
	.data.b	235,10
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4908
	.data.b	85,0
	.section	.debug_info		;off: 5190
	.data.w	.Ldw_str_begin+4908
	.data.b	236,10
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4910
	.data.b	66,0
	.section	.debug_info		;off: 5207
	.data.w	.Ldw_str_begin+4910
	.data.b	237,10
	.data.b	26
	.data.b	67
	.data.w	.Ldw_begin+4691
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4912
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 5225
	.data.w	.Ldw_str_begin+4912
	.data.b	238,10
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5182

	.data.b	73
	.data.b	243,10
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4928
	.data.b	85,0
	.section	.debug_info		;off: 5245
	.data.w	.Ldw_str_begin+4928
	.data.b	244,10
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4930
	.data.b	66,0
	.section	.debug_info		;off: 5262
	.data.w	.Ldw_str_begin+4930
	.data.b	245,10
	.data.b	23
	.data.b	67
	.data.w	.Ldw_begin+4772
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4932
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,0
	.section	.debug_info		;off: 5280
	.data.w	.Ldw_str_begin+4932
	.data.b	246,10
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5237

	.data.b	73
	.data.b	251,10
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4946
	.data.b	85,0
	.section	.debug_info		;off: 5300
	.data.w	.Ldw_str_begin+4946
	.data.b	252,10
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4948
	.data.b	66,0
	.section	.debug_info		;off: 5317
	.data.w	.Ldw_str_begin+4948
	.data.b	253,10
	.data.b	25
	.data.b	67
	.data.w	.Ldw_begin+5053
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4950
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,0
	.section	.debug_info		;off: 5335
	.data.w	.Ldw_str_begin+4950
	.data.b	254,10
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5292

	.data.b	73
	.data.b	195,12
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4965
	.data.b	85,0
	.section	.debug_info		;off: 5355
	.data.w	.Ldw_str_begin+4965
	.data.b	196,12
	.data.b	12
	.data.b	67
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4967
	.data.b	66,0
	.section	.debug_info		;off: 5372
	.data.w	.Ldw_str_begin+4967
	.data.b	197,12
	.data.b	27
	.data.b	67
	.data.w	.Ldw_begin+5114
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4969
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,0
	.section	.debug_info		;off: 5390
	.data.w	.Ldw_str_begin+4969
	.data.b	198,12
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5347

	.data.b	52
	.section	.debug_str		;off: 4986
	.data.b	0
	.section	.debug_info		;off: 5403
	.data.w	.Ldw_str_begin+4986
	.data.b	81
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4987
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,78,79,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 5413
	.data.w	.Ldw_str_begin+4987
	.data.b	82
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5027
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 5422
	.data.w	.Ldw_str_begin+5027
	.data.b	83
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5064
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,73,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 5432
	.data.w	.Ldw_str_begin+5064
	.data.b	84
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5402

	.data.b	52
	.section	.debug_str		;off: 5092
	.data.b	0
	.section	.debug_info		;off: 5444
	.data.w	.Ldw_str_begin+5092
	.data.b	88
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5093
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,56,66,73,84,0
	.section	.debug_info		;off: 5454
	.data.w	.Ldw_str_begin+5093
	.data.b	89
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5123
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,54,66,73,84,0
	.section	.debug_info		;off: 5463
	.data.w	.Ldw_str_begin+5123
	.data.b	90
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5154
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,51,50,66,73,84,0
	.section	.debug_info		;off: 5472
	.data.w	.Ldw_str_begin+5154
	.data.b	91
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5185
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,54,52,66,73,84,0
	.section	.debug_info		;off: 5481
	.data.w	.Ldw_str_begin+5185
	.data.b	92
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5216
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,50,56,66,73,84,0
	.section	.debug_info		;off: 5490
	.data.w	.Ldw_str_begin+5216
	.data.b	93
	.data.b	5
	.data.b	66
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5248
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 5500
	.data.w	.Ldw_str_begin+5248
	.data.b	94
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5443

	.data.b	52
	.section	.debug_str		;off: 5273
	.data.b	0
	.section	.debug_info		;off: 5512
	.data.w	.Ldw_str_begin+5273
	.data.b	98
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5274
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,0
	.section	.debug_info		;off: 5522
	.data.w	.Ldw_str_begin+5274
	.data.b	99
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5297
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,52,0
	.section	.debug_info		;off: 5531
	.data.w	.Ldw_str_begin+5297
	.data.b	100
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5320
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,56,0
	.section	.debug_info		;off: 5540
	.data.w	.Ldw_str_begin+5320
	.data.b	101
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5343
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,54,0
	.section	.debug_info		;off: 5549
	.data.w	.Ldw_str_begin+5343
	.data.b	102
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5367
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,51,50,0
	.section	.debug_info		;off: 5558
	.data.w	.Ldw_str_begin+5367
	.data.b	103
	.data.b	5
	.data.b	66
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5391
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,54,52,0
	.section	.debug_info		;off: 5567
	.data.w	.Ldw_str_begin+5391
	.data.b	104
	.data.b	5
	.data.b	66
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 5415
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,50,56,0
	.section	.debug_info		;off: 5576
	.data.w	.Ldw_str_begin+5415
	.data.b	105
	.data.b	5
	.data.b	66
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 5440
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,50,53,54,0
	.section	.debug_info		;off: 5585
	.data.w	.Ldw_str_begin+5440
	.data.b	106
	.data.b	5
	.data.b	66
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5465
	.data.b	68,109,97,95,67,104,97,110,110,101,108,66,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 5595
	.data.w	.Ldw_str_begin+5465
	.data.b	107
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5511

	.data.b	52
	.section	.debug_str		;off: 5486
	.data.b	0
	.section	.debug_info		;off: 5607
	.data.w	.Ldw_str_begin+5486
	.data.b	111
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5487
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,77,50,77,0
	.section	.debug_info		;off: 5617
	.data.w	.Ldw_str_begin+5487
	.data.b	112
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5526
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,77,50,80,0
	.section	.debug_info		;off: 5626
	.data.w	.Ldw_str_begin+5526
	.data.b	113
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5565
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,80,50,77,0
	.section	.debug_info		;off: 5635
	.data.w	.Ldw_str_begin+5565
	.data.b	114
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5604
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,80,50,80,0
	.section	.debug_info		;off: 5644
	.data.w	.Ldw_str_begin+5604
	.data.b	115
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5643
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,80,69,82,95,80,50,80,0
	.section	.debug_info		;off: 5653
	.data.w	.Ldw_str_begin+5643
	.data.b	116
	.data.b	5
	.data.b	66
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5683
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,80,69,82,95,77,50,80,0
	.section	.debug_info		;off: 5662
	.data.w	.Ldw_str_begin+5683
	.data.b	117
	.data.b	5
	.data.b	66
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 5722
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,80,69,82,95,80,50,77,0
	.section	.debug_info		;off: 5671
	.data.w	.Ldw_str_begin+5722
	.data.b	118
	.data.b	5
	.data.b	66
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 5761
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,83,80,69,82,95,80,50,80,0
	.section	.debug_info		;off: 5680
	.data.w	.Ldw_str_begin+5761
	.data.b	119
	.data.b	5
	.data.b	66
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5801
	.data.b	68,109,97,95,70,108,111,119,67,111,110,116,114,111,108,65,110,100,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 5690
	.data.w	.Ldw_str_begin+5801
	.data.b	120
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5606

	.data.b	52
	.section	.debug_str		;off: 5832
	.data.b	0
	.section	.debug_info		;off: 5702
	.data.w	.Ldw_str_begin+5832
	.data.b	124
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5833
	.data.b	68,77,65,95,68,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,83,79,85,82,67,69,0
	.section	.debug_info		;off: 5712
	.data.w	.Ldw_str_begin+5833
	.data.b	125
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5866
	.data.b	68,77,65,95,68,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,68,69,83,84,73,78,65,84,73,79,78,0
	.section	.debug_info		;off: 5721
	.data.w	.Ldw_str_begin+5866
	.data.b	126
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5904
	.data.b	68,109,97,95,68,66,83,111,117,114,99,101,79,114,68,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 5731
	.data.w	.Ldw_str_begin+5904
	.data.b	127
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5701

	.data.b	52
	.section	.debug_str		;off: 5930
	.data.b	0
	.section	.debug_info		;off: 5743
	.data.w	.Ldw_str_begin+5930
	.data.b	131,1
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5931
	.data.b	68,77,65,95,68,66,83,87,73,84,67,72,77,79,68,69,95,83,87,0
	.section	.debug_info		;off: 5754
	.data.w	.Ldw_str_begin+5931
	.data.b	132,1
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5951
	.data.b	68,77,65,95,68,66,83,87,73,84,67,72,77,79,68,69,95,72,87,95,83,87,0
	.section	.debug_info		;off: 5764
	.data.w	.Ldw_str_begin+5951
	.data.b	133,1
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5974
	.data.b	68,109,97,95,68,66,83,119,105,116,99,104,77,111,100,101,0
	.section	.debug_info		;off: 5775
	.data.w	.Ldw_str_begin+5974
	.data.b	134,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5742

	.data.b	52
	.section	.debug_str		;off: 5991
	.data.b	0
	.section	.debug_info		;off: 5788
	.data.w	.Ldw_str_begin+5991
	.data.b	138,1
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5992
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,83,79,85,82,67,69,0
	.section	.debug_info		;off: 5799
	.data.w	.Ldw_str_begin+5992
	.data.b	139,1
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6025
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,68,69,83,84,73,78,65,84,73,79,78,0
	.section	.debug_info		;off: 5809
	.data.w	.Ldw_str_begin+6025
	.data.b	140,1
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6063
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,66,79,84,72,0
	.section	.debug_info		;off: 5819
	.data.w	.Ldw_str_begin+6063
	.data.b	141,1
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6094
	.data.b	68,109,97,95,67,66,83,111,117,114,99,101,79,114,68,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 5830
	.data.w	.Ldw_str_begin+6094
	.data.b	142,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5787

	.data.b	52
	.section	.debug_str		;off: 6120
	.data.b	0
	.section	.debug_info		;off: 5843
	.data.w	.Ldw_str_begin+6120
	.data.b	146,1
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6121
	.data.b	68,77,65,95,67,66,83,73,90,69,95,78,79,78,69,0
	.section	.debug_info		;off: 5854
	.data.w	.Ldw_str_begin+6121
	.data.b	147,1
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6137
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,66,89,84,69,0
	.section	.debug_info		;off: 5864
	.data.w	.Ldw_str_begin+6137
	.data.b	148,1
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6154
	.data.b	68,77,65,95,67,66,83,73,90,69,95,52,66,89,84,69,0
	.section	.debug_info		;off: 5874
	.data.w	.Ldw_str_begin+6154
	.data.b	149,1
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6171
	.data.b	68,77,65,95,67,66,83,73,90,69,95,56,66,89,84,69,0
	.section	.debug_info		;off: 5884
	.data.w	.Ldw_str_begin+6171
	.data.b	150,1
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6188
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,54,66,89,84,69,0
	.section	.debug_info		;off: 5894
	.data.w	.Ldw_str_begin+6188
	.data.b	151,1
	.data.b	5
	.data.b	66
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 6206
	.data.b	68,77,65,95,67,66,83,73,90,69,95,51,50,66,89,84,69,0
	.section	.debug_info		;off: 5904
	.data.w	.Ldw_str_begin+6206
	.data.b	152,1
	.data.b	5
	.data.b	66
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 6224
	.data.b	68,77,65,95,67,66,83,73,90,69,95,54,52,66,89,84,69,0
	.section	.debug_info		;off: 5914
	.data.w	.Ldw_str_begin+6224
	.data.b	153,1
	.data.b	5
	.data.b	66
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 6242
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,50,56,66,89,84,69,0
	.section	.debug_info		;off: 5924
	.data.w	.Ldw_str_begin+6242
	.data.b	154,1
	.data.b	5
	.data.b	66
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 6261
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,53,54,66,89,84,69,0
	.section	.debug_info		;off: 5934
	.data.w	.Ldw_str_begin+6261
	.data.b	155,1
	.data.b	5
	.data.b	66
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 6280
	.data.b	68,77,65,95,67,66,83,73,90,69,95,53,49,50,66,89,84,69,0
	.section	.debug_info		;off: 5944
	.data.w	.Ldw_str_begin+6280
	.data.b	156,1
	.data.b	5
	.data.b	66
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 6299
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,48,50,52,66,89,84,69,0
	.section	.debug_info		;off: 5954
	.data.w	.Ldw_str_begin+6299
	.data.b	157,1
	.data.b	5
	.data.b	66
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 6319
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,48,52,56,66,89,84,69,0
	.section	.debug_info		;off: 5964
	.data.w	.Ldw_str_begin+6319
	.data.b	158,1
	.data.b	5
	.data.b	66
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 6339
	.data.b	68,77,65,95,67,66,83,73,90,69,95,52,48,57,54,66,89,84,69,0
	.section	.debug_info		;off: 5974
	.data.w	.Ldw_str_begin+6339
	.data.b	159,1
	.data.b	5
	.data.b	66
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 6359
	.data.b	68,77,65,95,67,66,83,73,90,69,95,56,49,57,50,66,89,84,69,0
	.section	.debug_info		;off: 5984
	.data.w	.Ldw_str_begin+6359
	.data.b	160,1
	.data.b	5
	.data.b	66
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 6379
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,54,51,56,52,66,89,84,69,0
	.section	.debug_info		;off: 5994
	.data.w	.Ldw_str_begin+6379
	.data.b	161,1
	.data.b	5
	.data.b	66
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 6400
	.data.b	68,77,65,95,67,66,83,73,90,69,95,51,50,55,54,56,66,89,84,69,0
	.section	.debug_info		;off: 6004
	.data.w	.Ldw_str_begin+6400
	.data.b	162,1
	.data.b	5
	.data.b	66
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6421
	.data.b	68,109,97,95,67,66,83,105,122,101,0
	.section	.debug_info		;off: 6015
	.data.w	.Ldw_str_begin+6421
	.data.b	163,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5842

	.data.b	52
	.section	.debug_str		;off: 6432
	.data.b	0
	.section	.debug_info		;off: 6028
	.data.w	.Ldw_str_begin+6432
	.data.b	167,1
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6433
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 6039
	.data.w	.Ldw_str_begin+6433
	.data.b	168,1
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6457
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,56,66,73,84,0
	.section	.debug_info		;off: 6049
	.data.w	.Ldw_str_begin+6457
	.data.b	169,1
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6478
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,49,54,66,73,84,0
	.section	.debug_info		;off: 6059
	.data.w	.Ldw_str_begin+6478
	.data.b	170,1
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6500
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,51,50,66,73,84,0
	.section	.debug_info		;off: 6069
	.data.w	.Ldw_str_begin+6500
	.data.b	171,1
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6522
	.data.b	68,109,97,95,80,97,116,116,101,114,110,83,105,122,101,0
	.section	.debug_info		;off: 6080
	.data.w	.Ldw_str_begin+6522
	.data.b	172,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6027

	.data.b	52
	.section	.debug_str		;off: 6538
	.data.b	0
	.section	.debug_info		;off: 6093
	.data.w	.Ldw_str_begin+6538
	.data.b	176,1
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6539
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,78,79,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 6104
	.data.w	.Ldw_str_begin+6539
	.data.b	177,1
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6578
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,48,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 6114
	.data.w	.Ldw_str_begin+6578
	.data.b	178,1
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6622
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,49,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 6124
	.data.w	.Ldw_str_begin+6622
	.data.b	179,1
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6666
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,48,70,73,82,83,84,0
	.section	.debug_info		;off: 6134
	.data.w	.Ldw_str_begin+6666
	.data.b	180,1
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6720
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,49,70,73,82,83,84,0
	.section	.debug_info		;off: 6144
	.data.w	.Ldw_str_begin+6720
	.data.b	181,1
	.data.b	5
	.data.b	66
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6774
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,70,114,111,122,101,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6155
	.data.w	.Ldw_str_begin+6774
	.data.b	182,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6092

	.data.b	71
	.data.b	253,1
	.data.b	1
	.data.b	66
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6803
	.data.b	97,100,100,114,101,115,115,0
	.section	.debug_info		;off: 6175
	.data.w	.Ldw_str_begin+6803
	.data.b	254,1
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6811
	.data.b	105,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 6192
	.data.w	.Ldw_str_begin+6811
	.data.b	255,1
	.data.b	33
	.data.b	66
	.data.w	.Ldw_begin+5431
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6821
	.data.b	98,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 6209
	.data.w	.Ldw_str_begin+6821
	.data.b	128,2
	.data.b	26
	.data.b	66
	.data.w	.Ldw_begin+5594
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6831
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6227
	.data.w	.Ldw_str_begin+6831
	.data.b	129,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6167

	.data.b	71
	.data.b	133,2
	.data.b	1
	.data.b	66
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6856
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 6247
	.data.w	.Ldw_str_begin+6856
	.data.b	134,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6864
	.data.b	114,101,113,117,101,115,116,77,85,88,0
	.section	.debug_info		;off: 6264
	.data.w	.Ldw_str_begin+6864
	.data.b	135,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6875
	.data.b	68,109,97,95,67,104,97,110,110,101,108,82,101,113,117,115,116,0
	.section	.debug_info		;off: 6282
	.data.w	.Ldw_str_begin+6875
	.data.b	138,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6239

	.data.b	71
	.data.b	143,2
	.data.b	1
	.data.b	66
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6893
	.data.b	115,111,117,114,99,101,0
	.section	.debug_info		;off: 6302
	.data.w	.Ldw_str_begin+6893
	.data.b	144,2
	.data.b	30
	.data.b	66
	.data.w	.Ldw_begin+6226
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6900
	.data.b	100,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 6319
	.data.w	.Ldw_str_begin+6900
	.data.b	145,2
	.data.b	30
	.data.b	66
	.data.w	.Ldw_begin+6226
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6912
	.data.b	116,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 6336
	.data.w	.Ldw_str_begin+6912
	.data.b	146,2
	.data.b	30
	.data.b	66
	.data.w	.Ldw_begin+5499
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6926
	.data.b	102,108,111,119,67,111,110,116,114,111,108,65,110,100,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 6353
	.data.w	.Ldw_str_begin+6926
	.data.b	147,2
	.data.b	36
	.data.b	66
	.data.w	.Ldw_begin+5689
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6953
	.data.b	115,111,117,114,99,101,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 6370
	.data.w	.Ldw_str_begin+6953
	.data.b	148,2
	.data.b	23
	.data.b	66
	.data.w	.Ldw_begin+6281
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6967
	.data.b	100,101,115,116,105,110,97,116,105,111,110,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 6387
	.data.w	.Ldw_str_begin+6967
	.data.b	151,2
	.data.b	23
	.data.b	66
	.data.w	.Ldw_begin+6281
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6986
	.data.b	116,114,97,110,115,102,101,114,83,105,122,101,0
	.section	.debug_info		;off: 6404
	.data.w	.Ldw_str_begin+6986
	.data.b	154,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1275
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6999
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,114,97,110,115,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6422
	.data.w	.Ldw_str_begin+6999
	.data.b	155,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6294

	.data.b	71
	.data.b	187,2
	.data.b	1
	.data.b	66
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7025
	.data.b	112,97,116,116,101,114,110,83,105,122,101,0
	.section	.debug_info		;off: 6442
	.data.w	.Ldw_str_begin+7025
	.data.b	188,2
	.data.b	21
	.data.b	66
	.data.w	.Ldw_begin+6079
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7037
	.data.b	112,97,116,116,101,114,110,68,97,116,97,0
	.section	.debug_info		;off: 6459
	.data.w	.Ldw_str_begin+7037
	.data.b	189,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7049
	.data.b	112,97,116,116,101,114,110,68,97,116,97,77,97,115,107,66,105,116,0
	.section	.debug_info		;off: 6476
	.data.w	.Ldw_str_begin+7049
	.data.b	190,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7068
	.data.b	112,97,116,116,101,114,110,77,97,116,99,104,101,100,83,116,111,112,0
	.section	.debug_info		;off: 6493
	.data.w	.Ldw_str_begin+7068
	.data.b	191,2
	.data.b	13
	.data.b	66
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7087
	.data.b	68,109,97,95,77,97,116,99,104,80,97,116,116,101,114,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6511
	.data.w	.Ldw_str_begin+7087
	.data.b	192,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6434

	.data.b	71
	.data.b	197,2
	.data.b	1
	.data.b	66
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7110
	.data.b	115,101,108,0
	.section	.debug_info		;off: 6531
	.data.w	.Ldw_str_begin+7110
	.data.b	198,2
	.data.b	31
	.data.b	66
	.data.w	.Ldw_begin+5730
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7114
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 6548
	.data.w	.Ldw_str_begin+7114
	.data.b	199,2
	.data.b	22
	.data.b	66
	.data.w	.Ldw_begin+5774
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7119
	.data.b	115,119,105,116,99,104,65,100,100,114,0
	.section	.debug_info		;off: 6565
	.data.w	.Ldw_str_begin+7119
	.data.b	200,2
	.data.b	12
	.data.b	66
	.data.w	.Ldw_begin+1287
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7130
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6583
	.data.w	.Ldw_str_begin+7130
	.data.b	201,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6523

	.data.b	71
	.data.b	207,2
	.data.b	1
	.data.b	66
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7153
	.data.b	115,101,108,0
	.section	.debug_info		;off: 6603
	.data.w	.Ldw_str_begin+7153
	.data.b	208,2
	.data.b	31
	.data.b	66
	.data.w	.Ldw_begin+5829
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7157
	.data.b	115,114,99,83,105,122,101,0
	.section	.debug_info		;off: 6620
	.data.w	.Ldw_str_begin+7157
	.data.b	209,2
	.data.b	16
	.data.b	66
	.data.w	.Ldw_begin+6014
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7165
	.data.b	100,101,115,83,105,122,101,0
	.section	.debug_info		;off: 6637
	.data.w	.Ldw_str_begin+7165
	.data.b	210,2
	.data.b	16
	.data.b	66
	.data.w	.Ldw_begin+6014
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7173
	.data.b	100,101,115,82,111,108,108,98,97,99,107,72,97,108,116,69,110,0
	.section	.debug_info		;off: 6654
	.data.w	.Ldw_str_begin+7173
	.data.b	211,2
	.data.b	13
	.data.b	66
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7191
	.data.b	68,109,97,95,67,105,114,99,117,108,97,114,66,117,102,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6672
	.data.w	.Ldw_str_begin+7191
	.data.b	212,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6595

	.data.b	71
	.data.b	218,2
	.data.b	1
	.data.b	66
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7216
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 6692
	.data.w	.Ldw_str_begin+7216
	.data.b	219,2
	.data.b	20
	.data.b	66
	.data.w	.Ldw_begin+5169
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7238
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,68,101,115,116,65,100,100,114,0
	.section	.debug_info		;off: 6709
	.data.w	.Ldw_str_begin+7238
	.data.b	220,2
	.data.b	21
	.data.b	66
	.data.w	.Ldw_begin+5224
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7261
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,76,108,105,82,101,103,0
	.section	.debug_info		;off: 6726
	.data.w	.Ldw_str_begin+7261
	.data.b	221,2
	.data.b	19
	.data.b	66
	.data.w	.Ldw_begin+5279
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7282
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,116,114,108,0
	.section	.debug_info		;off: 6743
	.data.w	.Ldw_str_begin+7282
	.data.b	222,2
	.data.b	20
	.data.b	66
	.data.w	.Ldw_begin+5334
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7301
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,82,67,0
	.section	.debug_info		;off: 6760
	.data.w	.Ldw_str_begin+7301
	.data.b	223,2
	.data.b	22
	.data.b	66
	.data.w	.Ldw_begin+5389
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7319
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,73,116,101,109,0
	.section	.debug_info		;off: 6778
	.data.w	.Ldw_str_begin+7319
	.data.b	224,2
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+6684

	.data.b	45
	.section	.debug_str		;off: 7338
	.data.b	68,109,97,95,72,119,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 6791
	.data.w	.Ldw_str_begin+7338
	.data.b	48
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 7353
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 6803
	.data.w	.Ldw_str_begin+7353
	.data.b	50
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 7369
	.data.b	68,109,97,95,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 6815
	.data.w	.Ldw_str_begin+7369
	.data.b	52
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+1263

	.data.b	45
	.section	.debug_str		;off: 7386
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,84,121,112,101,0
	.section	.debug_info		;off: 6827
	.data.w	.Ldw_str_begin+7386
	.data.b	55
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6814

	.data.b	45
	.section	.debug_str		;off: 7405
	.data.b	68,109,97,95,83,104,97,100,111,119,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 6839
	.data.w	.Ldw_str_begin+7405
	.data.b	59
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6814

	.data.b	45
	.section	.debug_str		;off: 7423
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 6851
	.data.w	.Ldw_str_begin+7423
	.data.b	63
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6814

	.data.b	45
	.section	.debug_str		;off: 7444
	.data.b	68,109,97,95,67,105,114,99,117,108,97,114,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 6863
	.data.w	.Ldw_str_begin+7444
	.data.b	67
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6814

	.data.b	45
	.section	.debug_str		;off: 7467
	.data.b	68,109,97,95,80,97,116,116,101,114,110,84,121,112,101,0
	.section	.debug_info		;off: 6875
	.data.w	.Ldw_str_begin+7467
	.data.b	71
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6814

	.data.b	45
	.section	.debug_str		;off: 7483
	.data.b	68,109,97,95,76,108,105,66,117,102,84,121,112,101,0
	.section	.debug_info		;off: 6887
	.data.w	.Ldw_str_begin+7483
	.data.b	75
	.data.b	46
	.data.b	64
	.data.w	.Ldw_begin+6777

	.data.b	52
	.section	.debug_str		;off: 7498
	.data.b	0
	.section	.debug_info		;off: 6899
	.data.w	.Ldw_str_begin+7498
	.data.b	94
	.data.b	1
	.data.b	64
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7499
	.data.b	68,77,65,95,67,72,95,67,65,78,67,69,76,95,68,73,82,69,67,84,0
	.section	.debug_info		;off: 6909
	.data.w	.Ldw_str_begin+7499
	.data.b	96
	.data.b	5
	.data.b	64
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7520
	.data.b	68,77,65,95,67,72,95,67,65,78,67,69,76,95,83,65,70,69,0
	.section	.debug_info		;off: 6918
	.data.w	.Ldw_str_begin+7520
	.data.b	98
	.data.b	5
	.data.b	64
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7539
	.data.b	68,109,97,95,67,104,67,97,110,99,101,108,84,121,112,101,0
	.section	.debug_info		;off: 6928
	.data.w	.Ldw_str_begin+7539
	.data.b	99
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+6898

	.data.b	52
	.section	.debug_str		;off: 7556
	.data.b	0
	.section	.debug_info		;off: 6940
	.data.w	.Ldw_str_begin+7556
	.data.b	103
	.data.b	1
	.data.b	64
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7557
	.data.b	68,77,65,95,67,72,95,73,78,84,95,84,67,0
	.section	.debug_info		;off: 6950
	.data.w	.Ldw_str_begin+7557
	.data.b	105
	.data.b	5
	.data.b	64
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7571
	.data.b	68,77,65,95,67,72,95,73,78,84,95,69,82,82,79,82,0
	.section	.debug_info		;off: 6959
	.data.w	.Ldw_str_begin+7571
	.data.b	107
	.data.b	6
	.data.b	64
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7588
	.data.b	68,77,65,95,67,72,95,73,78,84,95,80,65,84,84,69,82,78,0
	.section	.debug_info		;off: 6968
	.data.w	.Ldw_str_begin+7588
	.data.b	119
	.data.b	6
	.data.b	64
	.data.b	16

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7607
	.data.b	68,109,97,95,67,104,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 6978
	.data.w	.Ldw_str_begin+7607
	.data.b	126
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+6939

	.data.b	52
	.section	.debug_str		;off: 7623
	.data.b	0
	.section	.debug_info		;off: 6990
	.data.w	.Ldw_str_begin+7623
	.data.b	130,1
	.data.b	1
	.data.b	64
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7624
	.data.b	68,77,65,95,67,72,95,78,79,78,69,0
	.section	.debug_info		;off: 7001
	.data.w	.Ldw_str_begin+7624
	.data.b	132,1
	.data.b	5
	.data.b	64
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7636
	.data.b	68,77,65,95,67,72,95,84,82,65,78,83,70,69,82,95,67,79,77,80,76,69,84,69,0
	.section	.debug_info		;off: 7011
	.data.w	.Ldw_str_begin+7636
	.data.b	134,1
	.data.b	5
	.data.b	64
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7661
	.data.b	68,77,65,95,67,72,95,69,82,82,79,82,0
	.section	.debug_info		;off: 7021
	.data.w	.Ldw_str_begin+7661
	.data.b	136,1
	.data.b	5
	.data.b	64
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7674
	.data.b	68,77,65,95,67,72,95,83,67,66,0
	.section	.debug_info		;off: 7031
	.data.w	.Ldw_str_begin+7674
	.data.b	139,1
	.data.b	5
	.data.b	64
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7685
	.data.b	68,77,65,95,67,72,95,68,67,66,0
	.section	.debug_info		;off: 7041
	.data.w	.Ldw_str_begin+7685
	.data.b	141,1
	.data.b	5
	.data.b	64
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 7696
	.data.b	68,77,65,95,67,72,95,80,65,84,84,69,82,78,95,77,65,84,67,72,69,68,0
	.section	.debug_info		;off: 7051
	.data.w	.Ldw_str_begin+7696
	.data.b	145,1
	.data.b	5
	.data.b	64
	.data.b	16

	.data.b	51
	.section	.debug_str		;off: 7719
	.data.b	68,77,65,95,67,72,95,84,82,65,78,83,70,69,82,82,73,78,71,0
	.section	.debug_info		;off: 7061
	.data.w	.Ldw_str_begin+7719
	.data.b	148,1
	.data.b	5
	.data.b	64
	.data.b	192,0

	.data.b	51
	.section	.debug_str		;off: 7739
	.data.b	68,77,65,95,67,72,95,83,85,83,80,69,78,68,69,68,0
	.section	.debug_info		;off: 7072
	.data.w	.Ldw_str_begin+7739
	.data.b	150,1
	.data.b	5
	.data.b	64
	.data.b	128,1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7756
	.data.b	68,109,97,95,67,104,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 7084
	.data.w	.Ldw_str_begin+7756
	.data.b	151,1
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+6989

	.data.b	52
	.section	.debug_str		;off: 7773
	.data.b	0
	.section	.debug_info		;off: 7097
	.data.w	.Ldw_str_begin+7773
	.data.b	155,1
	.data.b	1
	.data.b	64
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7774
	.data.b	68,77,65,95,67,72,95,68,66,95,70,82,79,90,69,78,95,66,85,70,48,0
	.section	.debug_info		;off: 7108
	.data.w	.Ldw_str_begin+7774
	.data.b	157,1
	.data.b	5
	.data.b	64
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7796
	.data.b	68,77,65,95,67,72,95,68,66,95,70,82,79,90,69,78,95,66,85,70,49,0
	.section	.debug_info		;off: 7118
	.data.w	.Ldw_str_begin+7796
	.data.b	159,1
	.data.b	5
	.data.b	64
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7818
	.data.b	68,77,65,95,67,72,95,68,66,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,48,0
	.section	.debug_info		;off: 7128
	.data.w	.Ldw_str_begin+7818
	.data.b	161,1
	.data.b	5
	.data.b	64
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7845
	.data.b	68,77,65,95,67,72,95,68,66,95,66,79,84,72,95,70,79,82,90,69,78,95,66,85,70,49,0
	.section	.debug_info		;off: 7138
	.data.w	.Ldw_str_begin+7845
	.data.b	163,1
	.data.b	5
	.data.b	64
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7872
	.data.b	68,109,97,95,68,98,108,70,114,122,110,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 7149
	.data.w	.Ldw_str_begin+7872
	.data.b	164,1
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7096

	.data.b	71
	.data.b	221,1
	.data.b	1
	.data.b	64
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7894
	.data.b	80,104,121,67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 7169
	.data.w	.Ldw_str_begin+7894
	.data.b	223,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7907
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 7186
	.data.w	.Ldw_str_begin+7907
	.data.b	225,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6790
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7916
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 7203
	.data.w	.Ldw_str_begin+7916
	.data.b	227,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7926
	.data.b	67,104,84,114,97,110,115,102,101,114,73,100,120,0
	.section	.debug_info		;off: 7220
	.data.w	.Ldw_str_begin+7926
	.data.b	231,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6814
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7940
	.data.b	67,104,83,104,97,100,111,119,105,110,103,73,100,120,0
	.section	.debug_info		;off: 7237
	.data.w	.Ldw_str_begin+7940
	.data.b	236,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6838
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7955
	.data.b	67,111,114,101,68,99,73,100,120,0
	.section	.debug_info		;off: 7254
	.data.w	.Ldw_str_begin+7955
	.data.b	240,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7965
	.data.b	67,111,114,101,68,99,70,105,114,115,116,67,104,0
	.section	.debug_info		;off: 7271
	.data.w	.Ldw_str_begin+7965
	.data.b	243,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6802
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7979
	.data.b	67,104,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 7288
	.data.w	.Ldw_str_begin+7979
	.data.b	246,1
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+1490
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7991
	.data.b	68,109,97,95,67,104,97,110,110,101,108,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 7306
	.data.w	.Ldw_str_begin+7991
	.data.b	247,1
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7161

	.data.b	71
	.data.b	254,1
	.data.b	1
	.data.b	64
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8010
	.data.b	76,108,105,77,97,120,78,117,109,0
	.section	.debug_info		;off: 7326
	.data.w	.Ldw_str_begin+8010
	.data.b	128,2
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8020
	.data.b	76,108,105,84,111,84,114,97,110,115,102,101,114,73,100,80,116,114,0
	.section	.debug_info		;off: 7343
	.data.w	.Ldw_str_begin+8020
	.data.b	131,2
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+502
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8039
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 7361
	.data.w	.Ldw_str_begin+8039
	.data.b	132,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7318

	.data.b	71
	.data.b	138,2
	.data.b	1
	.data.b	64
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8061
	.data.b	76,108,105,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 7381
	.data.w	.Ldw_str_begin+8061
	.data.b	140,2
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+512
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8075
	.data.b	76,108,105,66,117,102,80,116,114,0
	.section	.debug_info		;off: 7398
	.data.w	.Ldw_str_begin+8075
	.data.b	142,2
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+517
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8085
	.data.b	68,109,97,95,67,104,76,105,110,107,101,100,76,105,115,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 7416
	.data.w	.Ldw_str_begin+8085
	.data.b	143,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7373

	.data.b	71
	.data.b	151,2
	.data.b	1
	.data.b	64
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8112
	.data.b	83,104,97,100,111,119,84,111,84,114,97,110,115,102,101,114,73,100,0
	.section	.debug_info		;off: 7436
	.data.w	.Ldw_str_begin+8112
	.data.b	153,2
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6814
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8131
	.data.b	83,104,97,100,111,119,84,111,76,108,105,73,100,0
	.section	.debug_info		;off: 7453
	.data.w	.Ldw_str_begin+8131
	.data.b	157,2
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6826
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8145
	.data.b	68,109,97,95,83,104,97,100,111,119,105,110,103,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 7471
	.data.w	.Ldw_str_begin+8145
	.data.b	159,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7428

	.data.b	71
	.data.b	167,2
	.data.b	1
	.data.b	64
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8166
	.data.b	68,98,108,66,117,102,67,111,110,102,105,103,0
	.section	.debug_info		;off: 7491
	.data.w	.Ldw_str_begin+8166
	.data.b	169,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+522
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8179
	.data.b	68,109,97,68,98,108,70,114,122,110,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 7508
	.data.w	.Ldw_str_begin+8179
	.data.b	171,2
	.data.b	12
	.data.b	64
	.data.w	.Ldw_begin+542
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8205
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 7526
	.data.w	.Ldw_str_begin+8205
	.data.b	173,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7483

	.data.b	71
	.data.b	181,2
	.data.b	1
	.data.b	64
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8232
	.data.b	68,99,77,97,120,78,117,109,0
	.section	.debug_info		;off: 7546
	.data.w	.Ldw_str_begin+8232
	.data.b	183,2
	.data.b	39
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8241
	.data.b	68,99,84,111,67,104,97,110,110,101,108,80,116,114,0
	.section	.debug_info		;off: 7563
	.data.w	.Ldw_str_begin+8241
	.data.b	186,2
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+552
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8256
	.data.b	68,109,97,95,68,97,105,115,121,67,104,97,105,110,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 7581
	.data.w	.Ldw_str_begin+8256
	.data.b	187,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7538

	.data.b	71
	.data.b	194,2
	.data.b	1
	.data.b	64
	.data.b	56
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8278
	.data.b	67,104,68,111,117,98,108,101,66,117,102,102,101,114,73,100,0
	.section	.debug_info		;off: 7601
	.data.w	.Ldw_str_begin+8278
	.data.b	197,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6850
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8295
	.data.b	67,104,67,105,114,99,117,108,97,114,66,117,102,102,101,114,73,100,0
	.section	.debug_info		;off: 7618
	.data.w	.Ldw_str_begin+8295
	.data.b	201,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6862
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8314
	.data.b	67,104,80,97,116,116,101,114,110,73,100,0
	.section	.debug_info		;off: 7635
	.data.w	.Ldw_str_begin+8314
	.data.b	205,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6874
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8326
	.data.b	67,104,76,105,110,107,101,100,76,105,115,116,73,100,0
	.section	.debug_info		;off: 7652
	.data.w	.Ldw_str_begin+8326
	.data.b	209,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6826
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8341
	.data.b	67,104,84,114,97,110,115,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 7669
	.data.w	.Ldw_str_begin+8341
	.data.b	216,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+557
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8358
	.data.b	68,109,97,95,84,114,97,110,115,102,101,114,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 7687
	.data.w	.Ldw_str_begin+8358
	.data.b	217,2
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7593

	.data.b	71
	.data.b	223,2
	.data.b	1
	.data.b	64
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8381
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 7707
	.data.w	.Ldw_str_begin+8381
	.data.b	225,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8391
	.data.b	73,115,84,114,97,110,115,67,102,103,69,120,105,115,116,115,0
	.section	.debug_info		;off: 7724
	.data.w	.Ldw_str_begin+8391
	.data.b	228,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8408
	.data.b	67,104,84,114,97,110,115,102,101,114,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 7741
	.data.w	.Ldw_str_begin+8408
	.data.b	232,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6814
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8427
	.data.b	67,104,83,104,97,100,111,119,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 7758
	.data.w	.Ldw_str_begin+8427
	.data.b	235,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6838
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8444
	.data.b	67,104,76,108,105,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 7775
	.data.w	.Ldw_str_begin+8444
	.data.b	239,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+6826
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8458
	.data.b	67,104,73,110,116,101,114,114,117,112,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 7792
	.data.w	.Ldw_str_begin+8458
	.data.b	244,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8476
	.data.b	67,104,67,111,110,116,105,110,117,111,117,115,77,111,100,101,0
	.section	.debug_info		;off: 7809
	.data.w	.Ldw_str_begin+8476
	.data.b	248,2
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8493
	.data.b	67,104,83,104,97,100,111,119,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 7826
	.data.w	.Ldw_str_begin+8493
	.data.b	252,2
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+567
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8512
	.data.b	67,104,76,108,105,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 7843
	.data.w	.Ldw_str_begin+8512
	.data.b	128,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+577
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8527
	.data.b	68,109,97,67,104,97,110,110,101,108,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 7860
	.data.w	.Ldw_str_begin+8527
	.data.b	131,3
	.data.b	12
	.data.b	64
	.data.w	.Ldw_begin+597
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8553
	.data.b	67,104,84,114,97,110,115,102,101,114,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 7877
	.data.w	.Ldw_str_begin+8553
	.data.b	133,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+607
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8573
	.data.b	68,109,97,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 7895
	.data.w	.Ldw_str_begin+8573
	.data.b	134,3
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7699

	.data.b	71
	.data.b	140,3
	.data.b	1
	.data.b	64
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8590
	.data.b	77,97,120,72,119,85,110,105,116,78,117,109,0
	.section	.debug_info		;off: 7915
	.data.w	.Ldw_str_begin+8590
	.data.b	142,3
	.data.b	40
	.data.b	64
	.data.w	.Ldw_begin+6790
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8603
	.data.b	72,119,85,110,105,116,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 7932
	.data.w	.Ldw_str_begin+8603
	.data.b	144,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+617
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8617
	.data.b	72,119,84,111,67,104,97,110,110,101,108,80,116,114,0
	.section	.debug_info		;off: 7949
	.data.w	.Ldw_str_begin+8617
	.data.b	147,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+622
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8632
	.data.b	68,109,97,95,72,119,85,110,105,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 7967
	.data.w	.Ldw_str_begin+8632
	.data.b	148,3
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7907

	.data.b	71
	.data.b	154,3
	.data.b	1
	.data.b	64
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8653
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7987
	.data.w	.Ldw_str_begin+8653
	.data.b	156,3
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8664
	.data.b	77,97,120,68,97,105,115,121,67,104,97,105,110,0
	.section	.debug_info		;off: 8004
	.data.w	.Ldw_str_begin+8664
	.data.b	159,3
	.data.b	44
	.data.b	64
	.data.w	.Ldw_begin+1263
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8678
	.data.b	68,97,105,115,121,67,104,97,105,110,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 8021
	.data.w	.Ldw_str_begin+8678
	.data.b	161,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+643
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8696
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8038
	.data.w	.Ldw_str_begin+8696
	.data.b	164,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+653
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8713
	.data.b	68,109,97,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 8056
	.data.w	.Ldw_str_begin+8713
	.data.b	165,3
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+7979

	.data.b	71
	.data.b	173,3
	.data.b	1
	.data.b	64
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8732
	.data.b	68,98,108,66,117,102,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8076
	.data.w	.Ldw_str_begin+8732
	.data.b	176,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+663
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8748
	.data.b	67,105,114,99,66,117,102,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8093
	.data.w	.Ldw_str_begin+8748
	.data.b	180,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+673
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8765
	.data.b	80,97,116,116,101,114,110,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8110
	.data.w	.Ldw_str_begin+8765
	.data.b	184,3
	.data.b	45
	.data.b	64
	.data.w	.Ldw_begin+683
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8782
	.data.b	68,109,97,95,67,111,109,109,111,110,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 8128
	.data.w	.Ldw_str_begin+8782
	.data.b	186,3
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+8068

	.data.b	71
	.data.b	193,3
	.data.b	1
	.data.b	64
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8803
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8148
	.data.w	.Ldw_str_begin+8803
	.data.b	195,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+698
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8817
	.data.b	67,111,109,109,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8165
	.data.w	.Ldw_str_begin+8817
	.data.b	199,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+719
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8831
	.data.b	67,104,97,110,110,101,108,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 8182
	.data.w	.Ldw_str_begin+8831
	.data.b	203,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+729
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8849
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 8199
	.data.w	.Ldw_str_begin+8849
	.data.b	205,3
	.data.b	41
	.data.b	64
	.data.w	.Ldw_begin+739
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8865
	.data.b	68,109,97,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 8217
	.data.w	.Ldw_str_begin+8865
	.data.b	206,3
	.data.b	3
	.data.b	64
	.data.w	.Ldw_begin+8140

	.data.b	8
	.section	.debug_str		;off: 8880
	.data.b	65,100,99,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 8230
	.data.w	.Ldw_str_begin+8880
	.data.b	51
	.data.b	29
	.data.b	11
	.data.w	.Ldw_begin+749
	.data.b	1
	.data.b	1

	.section	.debug_abbrev		;off: 226
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

	.section	.debug_info		;off: 8243
	.data.b	8
	.section	.debug_str		;off: 8894
	.data.b	68,109,97,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 8244
	.data.w	.Ldw_str_begin+8894
	.data.b	51
	.data.b	29
	.data.b	69
	.data.w	.Ldw_begin+770
	.data.b	1
	.data.b	1

	.data.b	6
	.section	.debug_str		;off: 8908
	.data.b	65,100,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 8258
	.data.w	.Ldw_str_begin+8908
	.data.b	71
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.section	.debug_abbrev		;off: 245
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

	.section	.debug_info		;off: 8277
	.data.b	6
	.section	.debug_str		;off: 8932
	.data.b	65,100,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 8278
	.data.w	.Ldw_str_begin+8932
	.data.b	80
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 8956
	.data.b	65,100,99,95,68,101,109,111,67,111,114,101,69,120,101,70,108,97,103,0
	.section	.debug_info		;off: 8298
	.data.w	.Ldw_str_begin+8956
	.data.b	90
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+4610
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 8976
	.data.b	65,100,99,95,71,116,109,84,114,105,103,103,101,114,67,110,116,95,48,0
	.section	.debug_info		;off: 8318
	.data.w	.Ldw_str_begin+8976
	.data.b	98
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_GtmTriggerCnt_0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 8996
	.data.b	65,100,99,95,83,119,67,111,110,116,105,110,117,111,117,115,67,111,110,118,101,114,115,105,111,110,67,110,116,0
	.section	.debug_info		;off: 8338
	.data.w	.Ldw_str_begin+8996
	.data.b	100
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+1287
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwContinuousConversionCnt..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9026
	.data.b	65,100,99,95,72,119,84,114,105,103,83,105,110,103,108,101,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8358
	.data.w	.Ldw_str_begin+9026
	.data.b	102
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+786
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_HwTrigSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9049
	.data.b	65,100,99,95,72,119,84,114,105,103,83,116,114,101,97,109,105,110,103,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8378
	.data.w	.Ldw_str_begin+9049
	.data.b	104
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+802
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_HwTrigStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9075
	.data.b	65,100,99,95,83,121,110,99,71,114,112,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8398
	.data.w	.Ldw_str_begin+9075
	.data.b	105
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+818
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SyncGrpResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9093
	.data.b	65,100,99,95,83,119,67,111,110,116,105,110,117,115,66,117,102,102,101,114,0
	.section	.debug_info		;off: 8418
	.data.w	.Ldw_str_begin+9093
	.data.b	107
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+834
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwContinusBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9114
	.data.b	65,100,99,95,83,119,79,110,101,83,104,111,116,76,105,109,105,116,67,104,101,99,107,105,110,103,0
	.section	.debug_info		;off: 8438
	.data.w	.Ldw_str_begin+9114
	.data.b	108
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+3472
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwOneShotLimitChecking..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9141
	.data.b	65,100,99,95,83,119,79,110,101,83,104,111,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 8458
	.data.w	.Ldw_str_begin+9141
	.data.b	110
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+850
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwOneShotBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9161
	.data.b	65,100,99,95,83,119,83,116,114,101,97,109,105,110,103,66,117,102,102,101,114,0
	.section	.debug_info		;off: 8478
	.data.w	.Ldw_str_begin+9161
	.data.b	112
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+866
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwStreamingBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9183
	.data.b	65,100,99,95,83,119,80,111,108,108,105,110,103,83,105,110,103,108,101,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8498
	.data.w	.Ldw_str_begin+9183
	.data.b	115
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+882
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9209
	.data.b	65,100,99,95,72,119,80,111,108,108,105,110,103,83,105,110,103,108,101,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8518
	.data.w	.Ldw_str_begin+9209
	.data.b	116
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+898
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_HwPollingSingleResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9235
	.data.b	65,100,99,95,83,119,80,111,108,108,105,110,103,83,116,114,101,97,109,105,110,103,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8538
	.data.w	.Ldw_str_begin+9235
	.data.b	118
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+914
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_SwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9264
	.data.b	65,100,99,95,72,119,80,111,108,108,105,110,103,83,116,114,101,97,109,105,110,103,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8558
	.data.w	.Ldw_str_begin+9264
	.data.b	120
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+930
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_HwPollingStreamingResult..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	6
	.section	.debug_str		;off: 9293
	.data.b	65,100,99,95,68,109,97,84,114,97,110,115,102,101,114,83,119,84,114,105,103,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8578
	.data.w	.Ldw_str_begin+9293
	.data.b	124
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+946
	.data.b	1
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_DmaTransferSwTrigResult

	.data.b	6
	.section	.debug_str		;off: 9321
	.data.b	65,100,99,95,68,101,109,111,67,111,114,101,73,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8598
	.data.w	.Ldw_str_begin+9321
	.data.b	134,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+967
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.

	.data.b	27
	.section	.debug_str		;off: 9344
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 8619
	.data.w	.Ldw_str_begin+9344
	.data.b	63
	.data.b	31
	.data.b	16
	.data.w	.Ldw_begin+1478
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 266
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

	.section	.debug_info		;off: 8636
	.data.b	37

	.section	.debug_abbrev		;off: 293
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 8637
	.data.b	8
	.section	.debug_str		;off: 9364
	.data.b	105,100,0
	.section	.debug_info		;off: 8638
	.data.w	.Ldw_str_begin+9364
	.data.b	65
	.data.b	17
	.data.b	16
	.data.w	.Ldw_begin+1478
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9367
	.data.b	65,100,99,95,73,110,105,116,0
	.section	.debug_info		;off: 8654
	.data.w	.Ldw_str_begin+9367
	.data.b	164,1
	.data.b	36
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 298
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

	.section	.debug_info		;off: 8668
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9376
	.data.b	65,100,99,95,83,101,116,117,112,82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 8670
	.data.w	.Ldw_str_begin+9376
	.data.b	170,1
	.data.b	46
	.data.b	9
	.data.w	.Ldw_begin+1311
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9398
	.data.b	65,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 8690
	.data.w	.Ldw_str_begin+9398
	.data.b	179,1
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
	.section	.debug_str		;off: 9409
	.data.b	65,100,99,95,83,116,97,114,116,71,114,111,117,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 8706
	.data.w	.Ldw_str_begin+9409
	.data.b	186,1
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
	.section	.debug_str		;off: 9434
	.data.b	65,100,99,95,83,116,111,112,71,114,111,117,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 8722
	.data.w	.Ldw_str_begin+9434
	.data.b	193,1
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
	.section	.debug_str		;off: 9458
	.data.b	65,100,99,95,82,101,97,100,71,114,111,117,112,0
	.section	.debug_info		;off: 8738
	.data.w	.Ldw_str_begin+9458
	.data.b	201,1
	.data.b	46
	.data.b	9
	.data.w	.Ldw_begin+1311
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9472
	.data.b	65,100,99,95,69,110,97,98,108,101,72,97,114,100,119,97,114,101,84,114,105,103,103,101,114,0
	.section	.debug_info		;off: 8758
	.data.w	.Ldw_str_begin+9472
	.data.b	211,1
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
	.section	.debug_str		;off: 9498
	.data.b	65,100,99,95,68,105,115,97,98,108,101,72,97,114,100,119,97,114,101,84,114,105,103,103,101,114,0
	.section	.debug_info		;off: 8774
	.data.w	.Ldw_str_begin+9498
	.data.b	218,1
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
	.section	.debug_str		;off: 9525
	.data.b	65,100,99,95,69,110,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 8790
	.data.w	.Ldw_str_begin+9525
	.data.b	225,1
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
	.section	.debug_str		;off: 9553
	.data.b	65,100,99,95,68,105,115,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 8806
	.data.w	.Ldw_str_begin+9553
	.data.b	232,1
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
	.section	.debug_str		;off: 9582
	.data.b	65,100,99,95,71,101,116,71,114,111,117,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8822
	.data.w	.Ldw_str_begin+9582
	.data.b	238,1
	.data.b	46
	.data.b	9
	.data.w	.Ldw_begin+3584
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9601
	.data.b	65,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 8842
	.data.w	.Ldw_str_begin+9601
	.data.b	244,1
	.data.b	55
	.data.b	9
	.data.w	.Ldw_begin+3496
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9626
	.data.b	65,100,99,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 8862
	.data.w	.Ldw_str_begin+9626
	.data.b	253,1
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
	.section	.debug_str		;off: 9645
	.data.b	73,110,116,99,95,68,105,115,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 8878
	.data.w	.Ldw_str_begin+9645
	.data.b	119
	.data.b	37
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9667
	.data.b	73,110,116,99,95,69,110,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 8893
	.data.w	.Ldw_str_begin+9667
	.data.b	124
	.data.b	37
	.data.b	39
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9688
	.data.b	84,105,109,101,114,95,68,101,108,97,121,77,115,0
	.section	.debug_info		;off: 8908
	.data.w	.Ldw_str_begin+9688
	.data.b	51
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9702
	.data.b	84,109,99,80,114,105,110,116,102,0
	.section	.debug_info		;off: 8923
	.data.w	.Ldw_str_begin+9702
	.data.b	176,1
	.data.b	14
	.data.b	49
	.data.w	.Ldw_begin+1263
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9712
	.data.b	103,101,116,67,104,97,114,0
	.section	.debug_info		;off: 8943
	.data.w	.Ldw_str_begin+9712
	.data.b	177,1
	.data.b	13
	.data.b	49
	.data.w	.Ldw_begin+228
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9720
	.data.b	68,109,97,95,73,110,105,116,0
	.section	.debug_info		;off: 8963
	.data.w	.Ldw_str_begin+9720
	.data.b	236,1
	.data.b	36
	.data.b	63
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9729
	.data.b	68,109,97,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 8979
	.data.w	.Ldw_str_begin+9729
	.data.b	242,1
	.data.b	36
	.data.b	63
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9740
	.data.b	68,109,97,95,67,104,97,110,110,101,108,83,116,97,114,116,0
	.section	.debug_info		;off: 8995
	.data.w	.Ldw_str_begin+9740
	.data.b	248,1
	.data.b	36
	.data.b	63
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 9757
	.data.b	68,109,97,95,67,104,97,110,110,101,108,67,97,110,99,101,108,0
	.section	.debug_info		;off: 9011
	.data.w	.Ldw_str_begin+9757
	.data.b	254,1
	.data.b	36
	.data.b	63
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 9775
	.data.b	68,109,97,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9027
	.data.w	.Ldw_str_begin+9775
	.data.b	175,2
	.data.b	38
	.data.b	63
	.data.w	.Ldw_begin+1287
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 9796
	.data.b	65,100,99,95,72,119,84,114,105,103,83,105,110,103,108,101,87,105,116,104,71,116,109,68,101,109,111,0
	.section	.debug_info		;off: 9047
	.data.w	.Ldw_str_begin+9796
	.data.b	206,1
	.data.b	13
	.data.b	1
	.data.w	Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigSingleWithGtmDemo
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

	.section	.debug_abbrev		;off: 323
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
	.data.w	Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigSingleWithGtmDemo-Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2938
	.data.b	0,5,2
	.data.w	Adc_HwTrigSingleWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	206,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	61
	.data.b	28
	.data.b	75
	.data.b	43
	.data.b	11
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	76
	.data.b	2
	.data.b	16
	.data.b	0,1,1
	.section	.debug_info		;off: 9078
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 369
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 9087
	.data.b	7
	.section	.debug_str		;off: 9824
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9088
	.data.w	.Ldw_str_begin+9824
	.data.b	208,1
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 378
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

	.section	.debug_info		;off: 9106
	.data.b	7
	.section	.debug_str		;off: 9828
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9107
	.data.w	.Ldw_str_begin+9828
	.data.b	209,1
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9125
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 9836
	.data.b	65,100,99,95,72,119,84,114,105,103,83,116,114,101,97,109,105,110,103,87,105,116,104,71,116,109,68,101,109,111,0
	.section	.debug_info		;off: 9128
	.data.w	.Ldw_str_begin+9836
	.data.b	148,2
	.data.b	13
	.data.b	1
	.data.w	Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigStreamingWithGtmDemo
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
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
	.data.w	Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigStreamingWithGtmDemo-Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2996
	.data.b	0,5,2
	.data.w	Adc_HwTrigStreamingWithGtmDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	148,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	45
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	60
	.data.b	27
	.data.b	43
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	28
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	76
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 9159
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	8
	.section	.debug_str		;off: 9867
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 9169
	.data.w	.Ldw_str_begin+9867
	.data.b	150,2
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 9879
	.data.b	83,116,114,101,97,109,105,110,103,76,111,111,112,0
	.section	.debug_info		;off: 9184
	.data.w	.Ldw_str_begin+9879
	.data.b	151,2
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 9893
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9199
	.data.w	.Ldw_str_begin+9893
	.data.b	152,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 9897
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9214
	.data.w	.Ldw_str_begin+9897
	.data.b	153,2
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9232
	.data.b	7
	.section	.debug_str		;off: 9905
	.data.b	82,101,115,117,108,116,80,116,114,0
	.section	.debug_info		;off: 9233
	.data.w	.Ldw_str_begin+9905
	.data.b	155,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+81
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9251
	.data.b	7
	.section	.debug_str		;off: 9915
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 9252
	.data.w	.Ldw_str_begin+9915
	.data.b	156,2
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+3496
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+77
	.section	.debug_loc		;off: 77
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9270
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 9924
	.data.b	65,100,99,95,72,119,84,114,105,103,83,105,110,103,108,101,87,105,116,104,82,101,115,117,108,116,65,99,99,117,109,117,68,101,109,111,0
	.section	.debug_info		;off: 9273
	.data.w	.Ldw_str_begin+9924
	.data.b	234,2
	.data.b	13
	.data.b	1
	.data.w	Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigSingleWithResultAccumuDemo
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
	.data.w	Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigSingleWithResultAccumuDemo-Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3080
	.data.b	0,5,2
	.data.w	Adc_HwTrigSingleWithResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	234,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	45
	.data.b	44
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	28
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	20
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	76
	.data.b	2
	.data.b	16
	.data.b	0,1,1
	.section	.debug_info		;off: 9304
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 9961
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9314
	.data.w	.Ldw_str_begin+9961
	.data.b	236,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+96
	.section	.debug_loc		;off: 96
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9332
	.data.b	7
	.section	.debug_str		;off: 9965
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9333
	.data.w	.Ldw_str_begin+9965
	.data.b	237,2
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+115
	.section	.debug_loc		;off: 115
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9351
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 9973
	.data.b	65,100,99,95,83,121,110,99,71,114,111,117,112,72,119,84,114,105,103,68,101,109,111,0
	.section	.debug_info		;off: 9354
	.data.w	.Ldw_str_begin+9973
	.data.b	175,3
	.data.b	13
	.data.b	1
	.data.w	Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SyncGroupHwTrigDemo
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
	.data.b	0
	.data.b	20
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
	.data.w	Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SyncGroupHwTrigDemo-Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3135
	.data.b	0,5,2
	.data.w	Adc_SyncGroupHwTrigDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	175,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	45
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	27
	.data.b	43
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	28
	.data.b	91
	.data.b	28
	.data.b	75
	.data.b	12
	.data.b	108
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	76
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 9385
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	8
	.section	.debug_str		;off: 9997
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 9395
	.data.w	.Ldw_str_begin+9997
	.data.b	177,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10009
	.data.b	72,119,117,110,105,116,76,111,111,112,0
	.section	.debug_info		;off: 9410
	.data.w	.Ldw_str_begin+10009
	.data.b	178,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10020
	.data.b	83,116,114,101,97,109,105,110,103,76,111,111,112,0
	.section	.debug_info		;off: 9425
	.data.w	.Ldw_str_begin+10020
	.data.b	179,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10034
	.data.b	83,121,110,99,71,114,112,72,119,73,100,0
	.section	.debug_info		;off: 9440
	.data.w	.Ldw_str_begin+10034
	.data.b	180,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+104
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+134
	.section	.debug_loc		;off: 134
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	2
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9458
	.data.b	8
	.section	.debug_str		;off: 10046
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9459
	.data.w	.Ldw_str_begin+10046
	.data.b	181,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10050
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9474
	.data.w	.Ldw_str_begin+10050
	.data.b	182,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+154
	.section	.debug_loc		;off: 154
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9492
	.data.b	7
	.section	.debug_str		;off: 10058
	.data.b	82,101,115,117,108,116,0
	.section	.debug_info		;off: 9493
	.data.w	.Ldw_str_begin+10058
	.data.b	183,3
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+81
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+173
	.section	.debug_loc		;off: 173
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9511
	.data.b	7
	.section	.debug_str		;off: 10065
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 9512
	.data.w	.Ldw_str_begin+10065
	.data.b	184,3
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+3496
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+193
	.section	.debug_loc		;off: 193
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9530
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10074
	.data.b	65,100,99,95,83,119,84,114,105,103,67,111,110,116,105,110,117,111,117,115,67,111,110,118,101,114,115,105,111,110,68,101,109,111,0
	.section	.debug_info		;off: 9533
	.data.w	.Ldw_str_begin+10074
	.data.b	138,4
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigContinuousConversionDemo
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
	.data.w	Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigContinuousConversionDemo-Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3227
	.data.b	0,5,2
	.data.w	Adc_SwTrigContinuousConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	138,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	45
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	2
	.data.b	16
	.data.b	0,1,1
	.section	.debug_info		;off: 9564
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	8
	.section	.debug_str		;off: 10109
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9574
	.data.w	.Ldw_str_begin+10109
	.data.b	140,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10113
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9589
	.data.w	.Ldw_str_begin+10113
	.data.b	141,4
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+212
	.section	.debug_loc		;off: 212
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9607
	.data.b	8
	.section	.debug_str		;off: 10121
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9608
	.data.w	.Ldw_str_begin+10121
	.data.b	142,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10134
	.data.b	65,100,99,95,83,119,84,114,105,103,87,105,116,104,76,105,109,105,116,67,104,101,99,107,105,110,103,68,101,109,111,0
	.section	.debug_info		;off: 9625
	.data.w	.Ldw_str_begin+10134
	.data.b	215,4
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigWithLimitCheckingDemo
	.data.b	1
	.data.b	93
	.data.b	144,128,1
	.data.b	124
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
	.data.w	Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigWithLimitCheckingDemo-Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3288
	.data.b	0,5,2
	.data.w	Adc_SwTrigWithLimitCheckingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	215,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	45
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	43
	.data.b	6
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	77
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 9656
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	8
	.section	.debug_str		;off: 10166
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9666
	.data.w	.Ldw_str_begin+10166
	.data.b	217,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10170
	.data.b	67,111,110,118,82,101,115,117,108,116,0
	.section	.debug_info		;off: 9681
	.data.w	.Ldw_str_begin+10170
	.data.b	218,4
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+3472
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+231
	.section	.debug_loc		;off: 231
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9699
	.data.b	7
	.section	.debug_str		;off: 10181
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9700
	.data.w	.Ldw_str_begin+10181
	.data.b	219,4
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+251
	.section	.debug_loc		;off: 251
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9718
	.data.b	7
	.section	.debug_str		;off: 10189
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9719
	.data.w	.Ldw_str_begin+10189
	.data.b	220,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+270
	.section	.debug_loc		;off: 270
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9737
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10202
	.data.b	65,100,99,95,83,119,84,114,105,103,79,110,101,83,104,111,116,67,111,110,118,101,114,115,105,111,110,68,101,109,111,0
	.section	.debug_info		;off: 9740
	.data.w	.Ldw_str_begin+10202
	.data.b	179,5
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigOneShotConversionDemo
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigOneShotConversionDemo-Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3408
	.data.b	0,5,2
	.data.w	Adc_SwTrigOneShotConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	179,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	45
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	77
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 9771
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	8
	.section	.debug_str		;off: 10234
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9781
	.data.w	.Ldw_str_begin+10234
	.data.b	181,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10238
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 9796
	.data.w	.Ldw_str_begin+10238
	.data.b	182,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+129
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+289
	.section	.debug_loc		;off: 289
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9814
	.data.b	7
	.section	.debug_str		;off: 10250
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9815
	.data.w	.Ldw_str_begin+10250
	.data.b	183,5
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+308
	.section	.debug_loc		;off: 308
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9833
	.data.b	7
	.section	.debug_str		;off: 10258
	.data.b	82,101,115,117,108,116,0
	.section	.debug_info		;off: 9834
	.data.w	.Ldw_str_begin+10258
	.data.b	184,5
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+134
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+327
	.section	.debug_loc		;off: 327
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9852
	.data.b	7
	.section	.debug_str		;off: 10265
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9853
	.data.w	.Ldw_str_begin+10265
	.data.b	185,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+347
	.section	.debug_loc		;off: 347
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9871
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10278
	.data.b	65,100,99,95,83,119,84,114,105,103,67,111,110,116,105,110,117,111,117,115,83,116,114,101,97,109,105,110,103,68,101,109,111,0
	.section	.debug_info		;off: 9874
	.data.w	.Ldw_str_begin+10278
	.data.b	137,6
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigContinuousStreamingDemo
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	20
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
	.data.w	Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigContinuousStreamingDemo-Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3487
	.data.b	0,5,2
	.data.w	Adc_SwTrigContinuousStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	137,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	45
	.data.b	75
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	60
	.data.b	27
	.data.b	43
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	28
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 9905
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	8
	.section	.debug_str		;off: 10312
	.data.b	114,101,116,0
	.section	.debug_info		;off: 9915
	.data.w	.Ldw_str_begin+10312
	.data.b	139,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10316
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 9930
	.data.w	.Ldw_str_begin+10316
	.data.b	140,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10328
	.data.b	83,116,114,101,97,109,105,110,103,76,111,111,112,0
	.section	.debug_info		;off: 9945
	.data.w	.Ldw_str_begin+10328
	.data.b	141,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10342
	.data.b	82,101,115,117,108,116,80,116,114,0
	.section	.debug_info		;off: 9960
	.data.w	.Ldw_str_begin+10342
	.data.b	143,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+81
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+366
	.section	.debug_loc		;off: 366
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9978
	.data.b	7
	.section	.debug_str		;off: 10352
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 9979
	.data.w	.Ldw_str_begin+10352
	.data.b	144,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+386
	.section	.debug_loc		;off: 386
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9997
	.data.b	8
	.section	.debug_str		;off: 10360
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9998
	.data.w	.Ldw_str_begin+10360
	.data.b	145,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10373
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 10013
	.data.w	.Ldw_str_begin+10373
	.data.b	146,6
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+3496
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+405
	.section	.debug_loc		;off: 405
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10031
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10382
	.data.b	65,100,99,95,83,119,84,114,105,103,79,110,101,83,104,111,116,67,111,110,118,101,114,115,105,111,110,82,101,115,117,108,116,65,99,99,117,109,117,68,101,109,111,0
	.section	.debug_info		;off: 10034
	.data.w	.Ldw_str_begin+10382
	.data.b	228,6
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigOneShotConversionResultAccumuDemo
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigOneShotConversionResultAccumuDemo-Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3591
	.data.b	0,5,2
	.data.w	Adc_SwTrigOneShotConversionResultAccumuDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	228,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	45
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	77
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10065
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	8
	.section	.debug_str		;off: 10426
	.data.b	114,101,116,0
	.section	.debug_info		;off: 10075
	.data.w	.Ldw_str_begin+10426
	.data.b	230,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10430
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10090
	.data.w	.Ldw_str_begin+10430
	.data.b	231,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+129
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+424
	.section	.debug_loc		;off: 424
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10108
	.data.b	7
	.section	.debug_str		;off: 10442
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10109
	.data.w	.Ldw_str_begin+10442
	.data.b	232,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+443
	.section	.debug_loc		;off: 443
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10127
	.data.b	7
	.section	.debug_str		;off: 10450
	.data.b	82,101,115,117,108,116,0
	.section	.debug_info		;off: 10128
	.data.w	.Ldw_str_begin+10450
	.data.b	233,6
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+156
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+462
	.section	.debug_loc		;off: 462
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10146
	.data.b	7
	.section	.debug_str		;off: 10457
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10147
	.data.w	.Ldw_str_begin+10457
	.data.b	234,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+482
	.section	.debug_loc		;off: 482
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10165
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10470
	.data.b	65,100,99,95,83,119,84,114,105,103,80,111,108,108,105,110,103,83,105,110,103,108,101,68,101,109,111,0
	.section	.debug_info		;off: 10168
	.data.w	.Ldw_str_begin+10470
	.data.b	188,7
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigPollingSingleDemo
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
	.data.b	0
	.data.b	28
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
	.data.w	Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigPollingSingleDemo-Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3670
	.data.b	0,5,2
	.data.w	Adc_SwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	188,7
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
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	93
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	77
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10199
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	8
	.section	.debug_str		;off: 10498
	.data.b	114,101,116,0
	.section	.debug_info		;off: 10209
	.data.w	.Ldw_str_begin+10498
	.data.b	190,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10502
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10224
	.data.w	.Ldw_str_begin+10502
	.data.b	191,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+129
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+501
	.section	.debug_loc		;off: 501
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10242
	.data.b	7
	.section	.debug_str		;off: 10514
	.data.b	82,101,115,117,108,116,0
	.section	.debug_info		;off: 10243
	.data.w	.Ldw_str_begin+10514
	.data.b	192,7
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+175
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+520
	.section	.debug_loc		;off: 520
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10261
	.data.b	7
	.section	.debug_str		;off: 10521
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10262
	.data.w	.Ldw_str_begin+10521
	.data.b	193,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+540
	.section	.debug_loc		;off: 540
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10280
	.data.b	7
	.section	.debug_str		;off: 10529
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10281
	.data.w	.Ldw_str_begin+10529
	.data.b	194,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+559
	.section	.debug_loc		;off: 559
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10299
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10542
	.data.b	65,100,99,95,72,119,84,114,105,103,80,111,108,108,105,110,103,83,105,110,103,108,101,68,101,109,111,0
	.section	.debug_info		;off: 10302
	.data.w	.Ldw_str_begin+10542
	.data.b	137,8
	.data.b	13
	.data.b	1
	.data.w	Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigPollingSingleDemo
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
	.data.b	0
	.data.b	28
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
	.data.w	Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigPollingSingleDemo-Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3749
	.data.b	0,5,2
	.data.w	Adc_HwTrigPollingSingleDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	137,8
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
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	93
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	77
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	76
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10333
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	8
	.section	.debug_str		;off: 10570
	.data.b	114,101,116,0
	.section	.debug_info		;off: 10343
	.data.w	.Ldw_str_begin+10570
	.data.b	139,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10574
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10358
	.data.w	.Ldw_str_begin+10574
	.data.b	140,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+129
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+578
	.section	.debug_loc		;off: 578
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10376
	.data.b	7
	.section	.debug_str		;off: 10586
	.data.b	82,101,115,117,108,116,0
	.section	.debug_info		;off: 10377
	.data.w	.Ldw_str_begin+10586
	.data.b	141,8
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+194
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+597
	.section	.debug_loc		;off: 597
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10395
	.data.b	7
	.section	.debug_str		;off: 10593
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10396
	.data.w	.Ldw_str_begin+10593
	.data.b	142,8
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+617
	.section	.debug_loc		;off: 617
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10414
	.data.b	7
	.section	.debug_str		;off: 10601
	.data.b	82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10415
	.data.w	.Ldw_str_begin+10601
	.data.b	143,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+636
	.section	.debug_loc		;off: 636
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10433
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10614
	.data.b	65,100,99,95,83,119,84,114,105,103,80,111,108,108,105,110,103,83,116,114,101,97,109,105,110,103,68,101,109,111,0
	.section	.debug_info		;off: 10436
	.data.w	.Ldw_str_begin+10614
	.data.b	216,8
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigPollingStreamingDemo
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	20
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
	.data.w	Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigPollingStreamingDemo-Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3830
	.data.b	0,5,2
	.data.w	Adc_SwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	216,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	28
	.data.b	75
	.data.b	28
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10467
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	8
	.section	.debug_str		;off: 10645
	.data.b	114,101,116,0
	.section	.debug_info		;off: 10477
	.data.w	.Ldw_str_begin+10645
	.data.b	218,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10649
	.data.b	82,101,115,117,108,116,80,116,114,0
	.section	.debug_info		;off: 10492
	.data.w	.Ldw_str_begin+10649
	.data.b	220,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+81
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+655
	.section	.debug_loc		;off: 655
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10510
	.data.b	8
	.section	.debug_str		;off: 10659
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10511
	.data.w	.Ldw_str_begin+10659
	.data.b	221,8
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10671
	.data.b	83,116,114,101,97,109,105,110,103,76,111,111,112,0
	.section	.debug_info		;off: 10526
	.data.w	.Ldw_str_begin+10671
	.data.b	222,8
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10685
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10541
	.data.w	.Ldw_str_begin+10685
	.data.b	223,8
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+675
	.section	.debug_loc		;off: 675
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10559
	.data.b	8
	.section	.debug_str		;off: 10693
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 10560
	.data.w	.Ldw_str_begin+10693
	.data.b	224,8
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+3496
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10702
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10575
	.data.w	.Ldw_str_begin+10702
	.data.b	225,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+694
	.section	.debug_loc		;off: 694
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10593
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10715
	.data.b	65,100,99,95,72,119,84,114,105,103,80,111,108,108,105,110,103,83,116,114,101,97,109,105,110,103,68,101,109,111,0
	.section	.debug_info		;off: 10596
	.data.w	.Ldw_str_begin+10715
	.data.b	176,9
	.data.b	13
	.data.b	1
	.data.w	Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigPollingStreamingDemo
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
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
	.data.w	Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_HwTrigPollingStreamingDemo-Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3940
	.data.b	0,5,2
	.data.w	Adc_HwTrigPollingStreamingDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	176,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	76
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	28
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	91
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10627
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	8
	.section	.debug_str		;off: 10746
	.data.b	114,101,116,0
	.section	.debug_info		;off: 10637
	.data.w	.Ldw_str_begin+10746
	.data.b	178,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10750
	.data.b	82,101,115,117,108,116,80,116,114,0
	.section	.debug_info		;off: 10652
	.data.w	.Ldw_str_begin+10750
	.data.b	180,9
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+81
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+713
	.section	.debug_loc		;off: 713
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10670
	.data.b	7
	.section	.debug_str		;off: 10760
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10671
	.data.w	.Ldw_str_begin+10760
	.data.b	181,9
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+733
	.section	.debug_loc		;off: 733
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10689
	.data.b	8
	.section	.debug_str		;off: 10768
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10690
	.data.w	.Ldw_str_begin+10768
	.data.b	182,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10780
	.data.b	83,116,114,101,97,109,105,110,103,76,111,111,112,0
	.section	.debug_info		;off: 10705
	.data.w	.Ldw_str_begin+10780
	.data.b	183,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10794
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10720
	.data.w	.Ldw_str_begin+10794
	.data.b	184,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+752
	.section	.debug_loc		;off: 752
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10738
	.data.b	8
	.section	.debug_str		;off: 10807
	.data.b	86,97,108,105,100,78,117,109,0
	.section	.debug_info		;off: 10739
	.data.w	.Ldw_str_begin+10807
	.data.b	185,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+3496
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10816
	.data.b	65,100,99,95,83,119,84,114,105,103,68,109,97,84,114,97,110,115,102,101,114,68,101,109,111,0
	.section	.debug_info		;off: 10756
	.data.w	.Ldw_str_begin+10816
	.data.b	139,10
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferDemo
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferDemo-Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4032
	.data.b	0,5,2
	.data.w	Adc_SwTrigDmaTransferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	139,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	44
	.data.b	45
	.data.b	44
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	106
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	23
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	28
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	61
	.data.b	11
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	61
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10787
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 10842
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10797
	.data.w	.Ldw_str_begin+10842
	.data.b	141,10
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+771
	.section	.debug_loc		;off: 771
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10815
	.data.b	8
	.section	.debug_str		;off: 10850
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10816
	.data.w	.Ldw_str_begin+10850
	.data.b	142,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10862
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 10831
	.data.w	.Ldw_str_begin+10862
	.data.b	143,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10868
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10846
	.data.w	.Ldw_str_begin+10868
	.data.b	144,10
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+790
	.section	.debug_loc		;off: 790
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10864
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10881
	.data.b	65,100,99,95,83,119,84,114,105,103,68,109,97,84,114,97,110,115,102,101,114,87,105,116,104,68,97,105,115,121,67,104,97,105,110,68,101,109,111,0
	.section	.debug_info		;off: 10867
	.data.w	.Ldw_str_begin+10881
	.data.b	228,10
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferWithDaisyChainDemo
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferWithDaisyChainDemo-Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4124
	.data.b	0,5,2
	.data.w	Adc_SwTrigDmaTransferWithDaisyChainDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	228,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	44
	.data.b	60
	.data.b	29
	.data.b	44
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	61
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	101
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	22
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	45
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	61
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10898
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 10921
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 10908
	.data.w	.Ldw_str_begin+10921
	.data.b	230,10
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+809
	.section	.debug_loc		;off: 809
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10926
	.data.b	8
	.section	.debug_str		;off: 10929
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 10927
	.data.w	.Ldw_str_begin+10929
	.data.b	231,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 10941
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 10942
	.data.w	.Ldw_str_begin+10941
	.data.b	232,10
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 10947
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10957
	.data.w	.Ldw_str_begin+10947
	.data.b	233,10
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3584
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+828
	.section	.debug_loc		;off: 828
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10975
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 10960
	.data.b	65,100,99,95,83,119,84,114,105,103,68,109,97,84,114,97,110,115,102,101,114,65,108,108,67,104,84,111,79,110,101,82,101,115,82,101,103,68,101,109,111,0
	.section	.debug_info		;off: 10978
	.data.w	.Ldw_str_begin+10960
	.data.b	180,11
	.data.b	13
	.data.b	1
	.data.w	Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferAllChToOneResRegDemo
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.w	__ghs_eofn_Adc_SwTrigDmaTransferAllChToOneResRegDemo-Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4202
	.data.b	0,5,2
	.data.w	Adc_SwTrigDmaTransferAllChToOneResRegDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc_Demo.
	.data.b	6
	.data.b	3
	.data.b	180,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	45
	.data.b	44
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	61
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	93
	.data.b	45
	.data.b	59
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 11009
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 11002
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 11019
	.data.w	.Ldw_str_begin+11002
	.data.b	182,11
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+66
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+847
	.section	.debug_loc		;off: 847
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11037
	.data.b	8
	.section	.debug_str		;off: 11010
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 11038
	.data.w	.Ldw_str_begin+11010
	.data.b	183,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11016
	.data.b	68,109,97,67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 11053
	.data.w	.Ldw_str_begin+11016
	.data.b	184,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1287
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+866
	.section	.debug_loc		;off: 866
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11071
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11028
	.data.b	65,100,99,95,68,101,109,111,69,110,116,114,121,0
	.section	.debug_info		;off: 11074
	.data.w	.Ldw_str_begin+11028
	.data.b	255,11
	.data.b	6
	.data.b	1
	.data.w	Adc_DemoEntry
	.data.w	__ghs_eofn_Adc_DemoEntry
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
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
	.data.w	Adc_DemoEntry
	.data.w	__ghs_eofn_Adc_DemoEntry-Adc_DemoEntry
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4262
	.data.b	0,5,2
	.data.w	Adc_DemoEntry
	.data.b	6
	.data.b	3
	.data.b	255,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	59
	.data.b	124
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	60
	.data.b	60
	.data.b	60
	.data.b	59
	.data.b	60
	.data.b	60
	.data.b	27
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	61
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	128,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	129,1
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 11105
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 11042
	.data.b	67,109,100,0
	.section	.debug_info		;off: 11115
	.data.w	.Ldw_str_begin+11042
	.data.b	129,12
	.data.b	10
	.data.b	1
	.data.w	.Ldw_begin+228
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+885
	.section	.debug_loc		;off: 885
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11133
	.data.b	7
	.section	.debug_str		;off: 11046
	.data.b	69,120,105,116,70,108,97,103,0
	.section	.debug_info		;off: 11134
	.data.w	.Ldw_str_begin+11046
	.data.b	130,12
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+904
	.section	.debug_loc		;off: 904
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11152
	.data.b	7
	.section	.debug_str		;off: 11055
	.data.b	65,100,99,95,118,101,114,0
	.section	.debug_info		;off: 11153
	.data.w	.Ldw_str_begin+11055
	.data.b	131,12
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1410
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+923
	.section	.debug_loc		;off: 923
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11171
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11063
	.data.b	65,100,99,95,68,101,109,111,0
	.section	.debug_info		;off: 11174
	.data.w	.Ldw_str_begin+11063
	.data.b	160,13
	.data.b	6
	.data.b	1
	.data.w	Adc_Demo
	.data.w	__ghs_eofn_Adc_Demo
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_Demo
	.data.w	__ghs_eofn_Adc_Demo-Adc_Demo
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4420
	.data.b	0,5,2
	.data.w	Adc_Demo
	.data.b	6
	.data.b	3
	.data.b	160,13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	141
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	107
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	2
	.data.b	0
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	2
	.data.b	0
	.data.b	61
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	29
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	29
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	45
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
	.section	.debug_info		;off: 11205
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 11072
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 11215
	.data.w	.Ldw_str_begin+11072
	.data.b	162,13
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1490
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+943
	.section	.debug_loc		;off: 943
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11233
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11079
	.data.b	65,100,99,68,101,109,111,95,65,100,99,48,72,119,84,114,105,103,78,111,116,105,102,0
	.section	.debug_info		;off: 11236
	.data.w	.Ldw_str_begin+11079
	.data.b	191,14
	.data.b	6
	.data.b	1
	.data.w	AdcDemo_Adc0HwTrigNotif
	.data.w	__ghs_eofn_AdcDemo_Adc0HwTrigNotif
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
	.data.b	0
	.data.b	28
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
	.data.w	AdcDemo_Adc0HwTrigNotif
	.data.w	__ghs_eofn_AdcDemo_Adc0HwTrigNotif-AdcDemo_Adc0HwTrigNotif
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4609
	.data.b	0,5,2
	.data.w	AdcDemo_Adc0HwTrigNotif
	.data.b	6
	.data.b	3
	.data.b	191,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	91
	.data.b	12
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	61
	.data.b	12
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	43
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
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 11267
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	8
	.section	.debug_str		;off: 11103
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 11277
	.data.w	.Ldw_str_begin+11103
	.data.b	193,14
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1275
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11115
	.data.b	82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 11292
	.data.w	.Ldw_str_begin+11115
	.data.b	194,14
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+241
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+962
	.section	.debug_loc		;off: 962
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11310
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11128
	.data.b	65,100,99,68,101,109,111,95,65,100,99,48,72,119,84,114,105,103,82,115,108,116,65,99,99,117,109,78,111,116,105,102,0
	.section	.debug_info		;off: 11313
	.data.w	.Ldw_str_begin+11128
	.data.b	223,14
	.data.b	6
	.data.b	1
	.data.w	AdcDemo_Adc0HwTrigRsltAccumNotif
	.data.w	__ghs_eofn_AdcDemo_Adc0HwTrigRsltAccumNotif
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
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
	.data.w	AdcDemo_Adc0HwTrigRsltAccumNotif
	.data.w	__ghs_eofn_AdcDemo_Adc0HwTrigRsltAccumNotif-AdcDemo_Adc0HwTrigRsltAccumNotif
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4663
	.data.b	0,5,2
	.data.w	AdcDemo_Adc0HwTrigRsltAccumNotif
	.data.b	6
	.data.b	3
	.data.b	223,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	91
	.data.b	12
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	61
	.data.b	12
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	43
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
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 11344
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	8
	.section	.debug_str		;off: 11161
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 11354
	.data.w	.Ldw_str_begin+11161
	.data.b	225,14
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1275
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11173
	.data.b	82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 11369
	.data.w	.Ldw_str_begin+11173
	.data.b	226,14
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+260
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+982
	.section	.debug_loc		;off: 982
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11387
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11186
	.data.b	65,100,99,68,101,109,111,95,65,100,99,50,67,111,110,116,105,110,117,111,117,115,78,111,116,105,102,0
	.section	.debug_info		;off: 11390
	.data.w	.Ldw_str_begin+11186
	.data.b	128,15
	.data.b	6
	.data.b	1
	.data.w	AdcDemo_Adc2ContinuousNotif
	.data.w	__ghs_eofn_AdcDemo_Adc2ContinuousNotif
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
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
	.data.w	AdcDemo_Adc2ContinuousNotif
	.data.w	__ghs_eofn_AdcDemo_Adc2ContinuousNotif-AdcDemo_Adc2ContinuousNotif
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4717
	.data.b	0,5,2
	.data.w	AdcDemo_Adc2ContinuousNotif
	.data.b	6
	.data.b	3
	.data.b	128,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	45
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	60
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	61
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 11421
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	8
	.section	.debug_str		;off: 11214
	.data.b	67,104,97,110,110,101,108,76,111,111,112,0
	.section	.debug_info		;off: 11431
	.data.w	.Ldw_str_begin+11214
	.data.b	130,15
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1263
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11226
	.data.b	82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 11446
	.data.w	.Ldw_str_begin+11226
	.data.b	131,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1002
	.section	.debug_loc		;off: 1002
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 11464
	.data.b	8
	.section	.debug_str		;off: 11239
	.data.b	114,101,116,0
	.section	.debug_info		;off: 11465
	.data.w	.Ldw_str_begin+11239
	.data.b	132,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1311
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
	.data.b	24
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
	.data.b	37
	.data.b	10
	.data.b	1
	.data.b	44
	.data.b	65,68,67,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	50
	.data.b	65,68,67,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	72
	.data.b	65,68,67,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	79
	.data.b	65,68,67,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	86
	.data.b	65,68,67,95,80,79,87,69,82,95,83,84,65,84,69,95,83,85,80,80,79,82,84,69,68,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	96
	.data.b	65,68,67,95,73,78,84,69,82,82,85,80,84,95,77,79,68,69,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	97
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,77,79,68,69,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	98
	.data.b	65,68,67,95,68,77,65,95,77,79,68,69,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	112
	.data.b	65,68,67,95,68,69,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	119
	.data.b	65,68,67,95,69,78,65,66,76,69,95,83,84,65,82,84,95,83,84,79,80,95,71,82,79,85,80,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	126
	.data.b	65,68,67,95,72,87,95,84,82,73,71,71,69,82,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	133,1
	.data.b	65,68,67,95,82,69,65,68,95,71,82,79,85,80,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	140,1
	.data.b	65,68,67,95,71,82,80,95,78,79,84,73,70,95,67,65,80,65,66,73,76,73,84,89,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	147,1
	.data.b	65,68,67,95,69,78,65,66,76,69,95,76,73,77,73,84,95,67,72,69,67,75,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	154,1
	.data.b	65,68,67,95,72,87,95,83,89,78,67,95,67,79,78,86,95,71,82,79,85,80,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	171,1
	.data.b	65,68,67,95,80,82,73,79,82,73,84,89,95,73,77,80,76,69,77,69,78,84,65,84,73,79,78,32,40,65,68,67,95,80,82,73,79,82,73,84,89,95,78,79,78,69,41,0
	.data.b	1
	.data.b	178,1
	.data.b	65,68,67,95,80,82,73,79,82,73,84,89,95,78,79,78,69,32,40,48,85,41,0
	.data.b	1
	.data.b	182,1
	.data.b	65,68,67,95,80,82,73,79,82,73,84,89,95,72,87,95,83,87,32,40,50,85,41,0
	.data.b	1
	.data.b	194,1
	.data.b	65,68,67,95,69,78,65,66,76,69,95,81,85,69,85,73,78,71,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	242,1
	.data.b	65,68,67,95,82,69,81,83,82,67,95,67,79,85,78,84,32,40,51,85,41,0
	.data.b	1
	.data.b	234,5
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,72,119,84,114,105,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,48,41,0
	.data.b	1
	.data.b	239,5
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,72,119,84,114,105,103,83,116,114,101,97,109,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,49,41,0
	.data.b	1
	.data.b	244,5
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,72,119,82,101,115,117,108,116,65,99,99,117,109,117,108,97,116,105,111,110,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,50
	.data.b	41,0
	.data.b	1
	.data.b	249,5
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,121,110,99,67,111,110,118,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,51,41,0
	.data.b	1
	.data.b	254,5
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,84,114,105,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,51,50,41,0
	.data.b	1
	.data.b	131,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,84,114,105,103,95,68,109,97,76,105,110,107,101,100,76,105,115,116,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,51
	.data.b	51,41,0
	.data.b	1
	.data.b	136,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,84,114,105,103,95,82,101,115,82,101,103,67,111,110,102,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,51,52,41,0
	.data.b	1
	.data.b	141,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,67,111,110,116,105,110,117,111,117,115,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,54,52,41,0
	.data.b	1
	.data.b	146,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,76,105,109,105,116,67,104,101,99,107,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,54,53,41,0
	.data.b	1
	.data.b	151,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,79,110,101,83,104,111,116,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,54,54,41,0
	.data.b	1
	.data.b	156,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,116,114,101,97,109,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,54,55,41,0
	.data.b	1
	.data.b	161,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,82,101,115,117,108,116,65,99,99,117,109,117,108,97,116,105,111,110,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,54
	.data.b	56,41,0
	.data.b	1
	.data.b	166,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,72,119,80,111,108,108,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,50,53,54,41,0
	.data.b	1
	.data.b	171,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,72,119,83,116,114,101,97,109,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,50,53,55,41,0
	.data.b	1
	.data.b	176,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,80,111,108,108,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,50,53,56,41,0
	.data.b	1
	.data.b	181,6
	.data.b	65,100,99,67,111,110,102,95,65,100,99,71,114,111,117,112,95,71,114,111,117,112,83,119,83,116,114,101,97,109,105,110,103,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,50,53,57,41,0
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	11
	.data.b	3
	.data.b	33
	.data.b	12
	.data.b	3
	.data.b	47
	.data.b	13
	.data.b	3
	.data.b	39
	.data.b	14
	.data.b	1
	.data.b	69
	.data.b	77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,84,72,65,54,50,48,54,95,76,70,66,71,65,50,57,50,32,40,48,85,41,0
	.data.b	1
	.data.b	71
	.data.b	77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,84,72,65,54,52,49,50,95,66,71,65,53,49,54,32,40,49,85,41,0
	.data.b	1
	.data.b	75
	.data.b	77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,67,65,84,32,40,77,67,65,76,95,80,82,79,67,69,83,83,79,82,95,84,72,65,54,52,49,50,95,66,71,65,53,49,54,41,0
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	1
	.data.b	134,1
	.data.b	77,67,65,76,95,77,79,68,85,76,69,95,67,70,71,95,68,77,65,95,85,83,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	15
	.data.b	3
	.data.b	26
	.data.b	16
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	17
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
	.data.b	17
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	18
	.data.b	3
	.data.b	28
	.data.b	19
	.data.b	3
	.data.b	22
	.data.b	20
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	21
	.data.b	3
	.data.b	56
	.data.b	22
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
	.data.b	23
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
	.data.b	23
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	24
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	25
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
	.data.b	25
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	26
	.data.b	3
	.data.b	34
	.data.b	27
	.data.b	3
	.data.b	31
	.data.b	28
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
	.data.b	4
	.data.b	1
	.data.b	66
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	29
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
	.data.b	29
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	30
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	29
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
	.data.b	29
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	31
	.data.b	3
	.data.b	38
	.data.b	32
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	33
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
	.data.b	33
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
	.data.b	34
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
	.data.b	34
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	48
	.data.b	35
	.data.b	3
	.data.b	35
	.data.b	36
	.data.b	3
	.data.b	15
	.data.b	37
	.data.b	4
	.data.b	1
	.data.b	175,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	176,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	180,1
	.data.b	83,65,82,65,68,67,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	222,3
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	223,3
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	228,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	229,2
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	250,7
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	251,7
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	53
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	55
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	161,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	162,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	165,2
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	166,2
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	33
	.data.b	65,68,67,95,68,77,65,95,84,82,83,78,65,70,69,82,95,83,87,95,84,82,73,71,95,67,79,85,78,84,32,40,53,85,41,0
	.data.b	1
	.data.b	34
	.data.b	65,68,67,95,68,77,65,95,84,82,65,78,83,70,69,82,95,83,87,95,84,82,73,71,95,67,72,83,32,40,52,85,41,0
	.data.b	1
	.data.b	36
	.data.b	65,68,67,95,68,77,65,95,84,82,83,78,65,70,69,82,95,83,87,95,84,82,73,71,95,79,78,69,95,82,69,83,95,82,69,71,95,67,79,85,78,84,32,40,54,85,41,0
	.data.b	1
	.data.b	41
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	42
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	49
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	50
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	63
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	64
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	73
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	28
	.data.b	39
	.data.b	3
	.data.b	34
	.data.b	40
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	41
	.data.b	3
	.data.b	34
	.data.b	42
	.data.b	1
	.data.b	59
	.data.b	73,78,84,67,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	67
	.data.b	73,78,84,67,95,67,70,71,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	70
	.data.b	73,78,84,67,95,67,70,71,95,83,71,73,95,73,78,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	73
	.data.b	73,78,84,67,95,67,79,78,70,73,71,83,69,84,95,67,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	153,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,48,32,40,48,85,41,0
	.data.b	1
	.data.b	161,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,32,40,49,85,41,0
	.data.b	1
	.data.b	169,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,32,40,50,85,41,0
	.data.b	1
	.data.b	177,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,32,40,51,85,41,0
	.data.b	1
	.data.b	185,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,32,40,52,85,41,0
	.data.b	1
	.data.b	193,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,53,32,40,53,85,41,0
	.data.b	1
	.data.b	201,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,54,32,40,54,85,41,0
	.data.b	1
	.data.b	209,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,55,32,40,55,85,41,0
	.data.b	1
	.data.b	217,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,56,32,40,56,85,41,0
	.data.b	1
	.data.b	225,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,57,32,40,57,85,41,0
	.data.b	1
	.data.b	233,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,48,32,40,49,48,85,41,0
	.data.b	1
	.data.b	241,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,49,32,40,49,49,85,41,0
	.data.b	1
	.data.b	249,7
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,50,32,40,49,50,85,41,0
	.data.b	1
	.data.b	129,8
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,51,32,40,49,51,85,41,0
	.data.b	1
	.data.b	137,8
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,52,32,40,49,52,85,41,0
	.data.b	1
	.data.b	145,8
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,53,32,40,49,53,85,41,0
	.data.b	1
	.data.b	153,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,54,32,40,49,54,85,41,0
	.data.b	1
	.data.b	161,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,55,32,40,49,55,85,41,0
	.data.b	1
	.data.b	169,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,56,32,40,49,56,85,41,0
	.data.b	1
	.data.b	177,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,49,57,32,40,49,57,85,41,0
	.data.b	1
	.data.b	185,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,48,32,40,50,48,85,41,0
	.data.b	1
	.data.b	193,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,49,32,40,50,49,85,41,0
	.data.b	1
	.data.b	201,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,50,32,40,50,50,85,41,0
	.data.b	1
	.data.b	209,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,51,32,40,50,51,85,41,0
	.data.b	1
	.data.b	217,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,52,32,40,50,52,85,41,0
	.data.b	1
	.data.b	225,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,53,32,40,50,53,85,41,0
	.data.b	1
	.data.b	233,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,54,32,40,50,54,85,41,0
	.data.b	1
	.data.b	241,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,50,55,32,40,50,55,85,41,0
	.data.b	1
	.data.b	249,11
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,48,32,40,51,48,85,41,0
	.data.b	1
	.data.b	195,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,53,54,32,40,53,54,85,41,0
	.data.b	1
	.data.b	203,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,53,55,32,40,53,55,85,41,0
	.data.b	1
	.data.b	211,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,53,56,32,40,53,56,85,41,0
	.data.b	1
	.data.b	219,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,53,57,32,40,53,57,85,41,0
	.data.b	1
	.data.b	227,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,56,57,32,40,56,57,85,41,0
	.data.b	1
	.data.b	235,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,57,48,32,40,57,48,85,41,0
	.data.b	1
	.data.b	243,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,57,49,32,40,57,49,85,41,0
	.data.b	1
	.data.b	251,15
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,57,50,32,40,57,50,85,41,0
	.data.b	1
	.data.b	143,29
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,55,55,32,40,51,55,55,85,41,0
	.data.b	1
	.data.b	149,29
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,55,56,32,40,51,55,56,85,41,0
	.data.b	1
	.data.b	191,29
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,56,57,32,40,51,56,57,85,41,0
	.data.b	1
	.data.b	197,29
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,57,48,32,40,51,57,48,85,41,0
	.data.b	1
	.data.b	203,29
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,51,57,49,32,40,51,57,49,85,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	43
	.data.b	1
	.data.b	187,21
	.data.b	73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	188,21
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	246,21
	.data.b	73,78,84,67,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	208,23
	.data.b	73,78,84,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	209,23
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	45
	.data.b	4
	.data.b	1
	.data.b	110
	.data.b	73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	111
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	145,1
	.data.b	73,78,84,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	146,1
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	46
	.data.b	4
	.data.b	3
	.data.b	30
	.data.b	47
	.data.b	1
	.data.b	22
	.data.b	68,69,77,79,95,67,79,77,77,79,78,95,72,95,32,0
	.data.b	3
	.data.b	30
	.data.b	48
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
	.data.b	49
	.data.b	3
	.data.b	35
	.data.b	50
	.data.b	1
	.data.b	20
	.data.b	95,83,84,68,65,82,71,95,72,32,0
	.data.b	3
	.data.b	38
	.data.b	51
	.data.b	1
	.data.b	31
	.data.b	95,95,95,103,104,115,95,100,105,100,95,112,97,99,107,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	52
	.data.b	3
	.data.b	36
	.data.b	53
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
	.data.b	54
	.data.b	3
	.data.b	41
	.data.b	55
	.data.b	3
	.data.b	26
	.data.b	56
	.data.b	4
	.data.b	1
	.data.b	239,2
	.data.b	65,83,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	241,2
	.data.b	57
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
	.data.b	57
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	58
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	59
	.data.b	4
	.data.b	1
	.data.b	140,1
	.data.b	85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	142,1
	.data.b	60
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
	.data.b	60
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	47
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	61
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
	.data.b	62
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
	.data.b	60
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
	.data.b	60
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
	.data.b	3
	.data.b	32
	.data.b	63
	.data.b	3
	.data.b	36
	.data.b	64
	.data.b	3
	.data.b	40
	.data.b	65
	.data.b	1
	.data.b	48
	.data.b	68,77,65,95,67,79,78,70,73,71,83,69,84,95,67,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	55
	.data.b	68,77,65,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	62
	.data.b	68,77,65,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	69
	.data.b	68,77,65,95,67,70,71,95,68,69,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	76
	.data.b	68,77,65,95,67,70,71,95,67,72,65,78,78,69,76,95,80,65,85,83,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	83
	.data.b	68,77,65,95,67,70,71,95,67,72,65,78,78,69,76,95,67,65,78,67,69,76,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	90
	.data.b	68,77,65,95,67,70,71,95,67,72,65,78,78,69,76,95,82,69,77,65,73,78,73,78,71,95,84,82,65,78,83,70,69,82,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	97
	.data.b	68,77,65,95,67,70,71,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	104
	.data.b	68,77,65,95,67,70,71,95,68,79,85,66,76,69,95,66,85,70,70,69,82,95,83,87,73,84,67,72,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	111
	.data.b	68,77,65,95,67,70,71,95,84,82,65,78,83,70,69,82,95,85,80,68,65,84,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	118
	.data.b	68,77,65,95,67,70,71,95,83,72,65,68,79,87,73,78,71,95,85,80,68,65,84,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	125
	.data.b	68,77,65,95,67,70,71,95,84,82,65,78,83,70,69,82,95,85,80,68,65,84,69,95,77,65,78,85,65,76,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	132,1
	.data.b	68,77,65,95,67,70,71,95,76,73,78,75,69,68,76,73,83,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	139,1
	.data.b	68,77,65,95,67,70,71,95,68,65,73,83,89,67,72,65,73,78,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	146,1
	.data.b	68,77,65,95,67,70,71,95,67,79,78,84,73,78,85,79,85,83,95,77,79,68,69,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	154,1
	.data.b	68,77,65,95,67,70,71,95,68,79,85,66,76,69,95,66,85,70,70,69,82,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	162,1
	.data.b	68,77,65,95,67,70,71,95,83,72,65,68,79,87,73,78,71,95,79,80,69,82,65,84,73,79,78,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	170,1
	.data.b	68,77,65,95,67,70,71,95,67,73,82,67,85,76,65,82,95,66,85,70,70,69,82,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	178,1
	.data.b	68,77,65,95,67,70,71,95,80,65,84,84,69,82,78,95,77,65,84,67,72,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	185,1
	.data.b	68,77,65,95,67,70,71,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	190,1
	.data.b	68,77,65,95,67,70,71,95,84,67,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	194,1
	.data.b	68,77,65,95,67,70,71,95,82,84,67,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	198,1
	.data.b	68,77,65,95,67,70,71,95,69,82,82,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	202,1
	.data.b	68,77,65,95,67,70,71,95,83,82,67,95,67,73,82,67,95,66,85,70,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	206,1
	.data.b	68,77,65,95,67,70,71,95,68,69,83,84,95,67,73,82,67,95,66,85,70,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	210,1
	.data.b	68,77,65,95,67,70,71,95,80,65,84,84,69,82,78,95,73,78,84,69,82,82,85,80,84,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	213,1
	.data.b	68,77,65,95,67,70,71,95,67,72,65,78,78,69,76,95,78,79,95,84,82,65,78,83,70,69,82,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	217,1
	.data.b	68,77,65,95,67,70,71,95,77,85,76,84,73,95,84,82,65,78,83,70,69,82,95,78,85,77,32,40,51,85,41,0
	.data.b	1
	.data.b	233,1
	.data.b	68,77,65,95,67,70,71,95,77,85,76,84,73,95,83,72,65,68,79,87,73,78,71,95,78,85,77,32,40,49,85,41,0
	.data.b	1
	.data.b	144,2
	.data.b	68,77,65,95,77,65,88,95,72,87,85,78,73,84,95,67,79,85,78,84,32,40,52,85,41,0
	.data.b	1
	.data.b	213,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,67,104,97,110,110,101,108,48,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,57,41,0
	.data.b	1
	.data.b	218,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,67,104,97,110,110,101,108,49,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49,48,41,0
	.data.b	1
	.data.b	223,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,67,104,97,110,110,101,108,50,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49,49,41,0
	.data.b	1
	.data.b	228,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,67,104,97,110,110,101,108,51,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49,50,41,0
	.data.b	1
	.data.b	233,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,67,104,97,110,110,101,108,55,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49,51,41,0
	.data.b	1
	.data.b	130,26
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,65,68,67,49,95,65,108,108,67,104,84,111,79,110,101,82,101,115,82,101,103,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49
	.data.b	56,41,0
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	66
	.data.b	3
	.data.b	41
	.data.b	67
	.data.b	4
	.data.b	1
	.data.b	64
	.data.b	68,77,65,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,84,67,32,40,49,85,41,0
	.data.b	1
	.data.b	65
	.data.b	68,77,65,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,66,85,83,69,82,82,79,82,32,40,50,85,41,0
	.data.b	1
	.data.b	68
	.data.b	68,77,65,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,80,65,84,32,40,49,54,85,41,0
	.data.b	1
	.data.b	233,2
	.data.b	68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	235,2
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	166,9
	.data.b	68,77,65,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	168,9
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	69
	.data.b	1
	.data.b	47
	.data.b	68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	53
	.data.b	68,77,65,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	55
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	233,1
	.data.b	68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	234,1
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,3
	.data.b	68,77,65,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	135,3
	.data.b	68
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	37
	.data.b	65,68,67,95,72,87,95,84,82,73,71,95,83,73,78,71,76,69,95,67,72,83,32,40,55,85,41,0
	.data.b	1
	.data.b	38
	.data.b	65,68,67,95,72,87,95,84,82,73,71,95,83,84,82,69,65,77,73,78,71,95,67,72,83,32,40,51,85,41,0
	.data.b	1
	.data.b	39
	.data.b	65,68,67,95,72,87,95,84,82,73,71,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	41
	.data.b	65,68,67,95,83,87,95,79,78,69,95,83,72,79,84,95,83,73,78,71,76,69,95,67,72,83,32,40,55,85,41,0
	.data.b	1
	.data.b	42
	.data.b	65,68,67,95,83,87,95,67,79,78,84,73,78,85,79,85,83,95,67,72,83,32,40,55,85,41,0
	.data.b	1
	.data.b	44
	.data.b	65,68,67,95,83,87,95,84,82,73,71,95,83,84,82,69,65,77,73,78,71,95,67,72,83,32,40,52,85,41,0
	.data.b	1
	.data.b	45
	.data.b	65,68,67,95,83,87,95,84,82,73,71,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	47
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,83,87,95,83,73,78,71,76,69,95,67,72,83,32,40,55,85,41,0
	.data.b	1
	.data.b	48
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,72,87,95,83,73,78,71,76,69,95,67,72,83,32,40,56,85,41,0
	.data.b	1
	.data.b	50
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,83,87,95,83,84,82,69,65,77,73,78,71,95,67,72,83,32,40,51,85,41,0
	.data.b	1
	.data.b	51
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,83,87,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	52
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,72,87,95,83,84,82,69,65,77,73,78,71,95,67,72,83,32,40,53,85,41,0
	.data.b	1
	.data.b	53
	.data.b	65,68,67,95,80,79,76,76,73,78,71,95,72,87,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	55
	.data.b	65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,72,87,85,78,73,84,95,78,85,77,32,40,50,85,41,0
	.data.b	1
	.data.b	56
	.data.b	65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,67,72,83,32,40,49,85,41,0
	.data.b	1
	.data.b	57
	.data.b	65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	58
	.data.b	65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,66,85,70,70,69,82,95,83,73,90,69,32,40,65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,67,72,83,32,42,32,65,68,67,95,83,89,78,67,95,71,82
	.data.b	79,85,80,95,83,84,82,69,65,77,73,78,71,95,78,85,77,32,42,32,65,68,67,95,83,89,78,67,95,71,82,79,85,80,95,72,87,85,78,73,84,95,78,85,77,41,0
	.data.b	1
	.data.b	61
	.data.b	65,68,67,95,67,79,78,86,69,82,83,73,79,78,95,87,65,73,84,95,84,73,77,69,79,85,84,32,40,49,48,48,48,85,41,0
	.data.b	1
	.data.b	62
	.data.b	65,68,67,95,67,79,78,86,69,82,83,73,79,78,95,87,65,73,84,95,76,79,78,71,95,84,73,77,69,79,85,84,32,40,53,48,48,48,85,41,0
	.data.b	1
	.data.b	68
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	69
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	73
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	74
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	77
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	78
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	82
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	83
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	87
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65,66,76
	.data.b	69,32,0
	.data.b	3
	.data.b	88
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,8
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67
	.data.b	65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	240,8
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65,66,76,69
	.data.b	32,0
	.data.b	3
	.data.b	93
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	95
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	96
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	128,1
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	129,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	131,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	132,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	140,1
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	141,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	158,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	159,1
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	158,15
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	159,15
	.data.b	38
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 399
	.data.b	0
