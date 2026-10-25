	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682570..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckStateForStartGroup:
.LDW01:
.LDW11:
	mov	r3,r1
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.2:
	.endo	..gh.endasm.2

;line1113
..lin.36296530..e0831a4d.0_1::
.LDWlin1:
	ldr	r1,.L212
	ldr	r0,[r1]
	ldr	r1,.L213
	ldr	r1,[r1,r2 lsl 2]
	ldr	r0,[r0,16]
	ldr	r1,[r1,4]
	ldrb	r0,[r0,r3 lsl 1]
	mov	r3,88
	smlabb	r1,r3,r0,r1
	ldr	r1,[r1,4]
	movs	r0,r1
	movne	r0,1
.L117:
.LDW21:
.L214:

	ret	
__ghs_eofn_Adc_CheckStateForStartGroup:
	.endf	Adc_CheckStateForStartGroup
	.endf	Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r0	local

;Group	none	param
;HwUnitId	r1	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Adc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_ConfigPtr:	.space	4
	.endo	Adc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Adc_InstanceDataSet..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InstanceDataSet:
	.data.w	Adc_InstanceDataSetCore0
	.data.w	Adc_InstanceDataSetCore1
	.space	8
	.endo	Adc_InstanceDataSet..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InstanceDataSet
	.section ".ghrettbl",""
	.align	4
.L215:	.data.w	.L214
	.endo	.L215
	.section ".mcal_const_asil_d_unspecified_core0","a"
	.align	4
Adc_InstanceDataSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InstanceDataSetCore0:
	.data.w	Adc_InitStatusCore0
	.data.w	Adc_InstanceDataCore0
	.data.w	Adc_NumValidConResCore0
	.data.w	Adc_GroupResultBufferCore0
	.endo	Adc_InstanceDataSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InstanceDataSetCore0
	.section ".mcal_const_asil_d_unspecified_core1","a"
	.align	4
Adc_InstanceDataSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InstanceDataSetCore1:
	.data.w	Adc_InitStatusCore1
	.data.w	Adc_InstanceDataCore1
	.data.w	Adc_NumValidConResCore1
	.data.w	Adc_GroupResultBufferCore1
	.endo	Adc_InstanceDataSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InstanceDataSetCore1
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Adc_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InitStatusCore0:	.space	1
	.endo	Adc_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InitStatusCore0
	.space	3
Adc_InstanceDataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InstanceDataCore0:	.space	264
	.endo	Adc_InstanceDataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InstanceDataCore0
Adc_NumValidConResCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_NumValidConResCore0:	.space	11
	.endo	Adc_NumValidConResCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_NumValidConResCore0
	.space	1
Adc_GroupResultBufferCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_GroupResultBufferCore0:	.space	44
	.endo	Adc_GroupResultBufferCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_GroupResultBufferCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Adc_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InitStatusCore1:	.space	1
	.endo	Adc_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InitStatusCore1
	.space	3
Adc_InstanceDataCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_InstanceDataCore1:	.space	88
	.endo	Adc_InstanceDataCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_InstanceDataCore1
Adc_NumValidConResCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_NumValidConResCore1:	.space	5
	.endo	Adc_NumValidConResCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_NumValidConResCore1
	.space	3
Adc_GroupResultBufferCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_GroupResultBufferCore1:	.space	20
	.endo	Adc_GroupResultBufferCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_GroupResultBufferCore1
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckStateForEnableGroup:
.LDW31:
.LDW41:
	mov	r3,r1
	b	.L308

.L212:	.data.w	Adc_ConfigPtr
	.endo	.L212

.L213:	.data.w	Adc_InstanceDataSet
	.endo	.L213

.L308:

;line1184
..lin.36296530..a4981166.0_2::
.LDWlin2:
..gh.beginasm.4:
	.endo	..gh.beginasm.4
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.5:
	.endo	..gh.endasm.5

;line1217
..lin.36296530..a4981166.0_3::
.LDWlin3:
	ldr	r1,.L309
	ldr	r0,[r1]
	ldr	r1,.L310
	ldr	r1,[r1,r2 lsl 2]
	ldr	r0,[r0,16]
	ldr	r1,[r1,4]
	ldrb	r0,[r0,r3 lsl 1]
	mov	r3,88
	smlabb	r1,r3,r0,r1
	ldr	r1,[r1,4]
	movs	r0,r1
	movne	r0,1
.L216:
.LDW51:
.L311:

	ret	
__ghs_eofn_Adc_CheckStateForEnableGroup:
	.endf	Adc_CheckStateForEnableGroup
	.endf	Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r0	local

;Group	none	param
;HwUnitId	r1	param

	.section ".ghrettbl",""
.L312:	.data.w	.L311
	.endo	.L312
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_UpdateResBuffer:
.LDW61:
	push	{r4-fp,lr}
	sub	sp,sp,20
	mov	r8,r1
	mov	fp,r2
.LDW71:
	mov	r3,r1
	strb	r0,[sp,7]
	b	.L693

.L309:	.data.w	Adc_ConfigPtr
	.endo	.L309

.L310:	.data.w	Adc_InstanceDataSet
	.endo	.L310

.L693:

;line1279
..lin.36296530..e0ac9493.0_4::
.LDWlin4:
..gh.beginasm.7:
	.endo	..gh.beginasm.7
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.8:
	.endo	..gh.endasm.8

;line1282
..lin.36296530..e0ac9493.0_5::
.LDWlin5:
	ldr	r0,.L694
	ldr	r12,[r0]
	ldrb	r1,[sp,7]
	ldr	r12,[r12,16]
	ldrb	r1,[r12,r1 lsl 1]
	mov	r12,88
	smulbb	r1,r1,r12
	ldr	r12,.L695
	ldr	r5,[r12,r2 lsl 2]
	ldr	r5,[r5,4]
	ldr	r2,[r5,r1]!
	ldr	r4,[r5,84]
	ldr	r2,[r2,r3 lsl 2]
	ldr	r3,[fp,20]
	mov	r1,44
	mla	r7,r8,r1,r3
	ldrb	r4,[r4,r8]
	mov	r10,0
	ldr	r6,[r7,8]
	ldrb	r9,[r7,1]
	ldrb	r6,[r6]
	cmp	r4,r9
	moveq	r4,0
	smulbb	r12,r9,r6
	strb	r6,[sp,5]
	add	r3,r2,r4 lsl 1
	str	r3,[sp,8]
	strh	r12,[sp,14]
	b	.L321
.L323:
	ldrb	r2,[r7,28]
	add	r1,r5,32
	add	r2,r2,r2 lsl 4
	ldrb	r0,[sp,7]
	add	r1,r2,r1
	ldr	r3,.L696
	ldrb	r1,[r1,r10]
	ldr	r0,[r3,r0 lsl 2]
	strb	r1,[sp,6]
.L697:

	bl	Saradc_Hal_GetResult
	ldr	r1,[sp,8]
	strh	r0,[r1]
	ldr	r1,[fp,8]
	cmp	r1,0
	beq	.L324
	ldrb	r6,[r7]
	cmp	r6,1
	bne	.L324
	b	.L330
.L329:
	ldr	r2,[r7,8]
	add	r2,r10,r2
	ldrb	r2,[r2,1]
	ldr	r3,[fp,16]
	add	r2,r2,r2 lsl 3
	add	r2,r3,r2 lsl 2
	ldrb	r2,[r2,29]
	cmp	r2,1
	bne	.L331
	ldrb	r0,[r1,r6]
	ldr	r2,.L696
	ldrb	r1,[sp,6]
	ldr	r0,[r2,r0 lsl 2]
.L699:

	bl	Saradc_Hal_GetResult
	b	.L328
.L331:
	mvn	r0,0
.L328:
	ldrh	r2,[sp,14]
	mul	r1,r6,r2
	ldr	r3,[sp,8]
	add	r6,r6,1
	lsl	r1,r1,1
	uxtb	r6,r6
	strh	r0,[r1,r3]
.L330:
	ldr	r1,[fp,8]
	ldrb	r2,[r1]
	cmp	r6,r2
	bls	.L329
.L324:
	ldr	r0,[sp,8]
	ldrb	r2,[sp,5]
	add	r0,r0,r9 lsl 1
	str	r0,[sp,8]
	sub	r1,r2,1
	add	r10,r10,1
	strb	r1,[sp,5]
.L321:
	ldrb	r0,[sp,5]
	cmp	r0,0
	bne	.L323
	ldr	r1,[r5,84]
	add	r0,r4,1
	strb	r0,[r1,r8]
	ldrb	r4,[r1,r8]
	cmp	r4,r9
	moveq	r1,1
	lsleq	r2,r1,r8
	ldreq	r1,[r5,12]
	biceq	r1,r1,r2
	orreq	r1,r2,r1
	streq	r1,[r5,12]
.LDW81:
	add	sp,sp,20
.L701:

	pop	{r4-fp,pc}
__ghs_eofn_Adc_UpdateResBuffer:
	.endf	Adc_UpdateResBuffer
	.endf	Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;NoOfSamples	r9	local
;CurrBufPos	r4	local
;ChannelNum	[sp,6]	local
;NoOfChannels	[sp,5]	local
;HwUnitCnt	r6	local
;SyncGrpSlaveRsltStartPos	[sp,14]	local
;DataPtr	r5	local
;GrpPtr	r7	local
;LoopCnt	r10	local
;CurrentResBufPtr	[sp,8]	local
;GrpBufferBasePtr	r2	local

;HwUnitId	[sp,7]	param
;Group	r8	param
;AdcKernelPtr	fp	param

	.section ".mcal_const_asil_d_unspecified","a"
Adc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_BaseAddrs:	.data.b	0,0,0,176
	.data.b	0,4,0,176
	.data.b	0,8,0,176
	.data.b	0,12,0,176
	.data.b	0,0,48,176
	.data.b	0,4,48,176
	.data.b	0,8,48,176
	.data.b	0,12,48,176
	.data.b	0,0,1,176
	.data.b	0,4,1,176
	.data.b	0,8,1,176
	.data.b	0,12,1,176
	.endo	Adc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_BaseAddrs
	.section ".ghcalltbl",""
	.align	4
.L698:	.data.w	.L697
	.endo	.L698
.L700:	.data.w	.L699
	.endo	.L700
	.section ".ghrettbl",""
.L702:	.data.w	.L701
	.endo	.L702
	.data
	.global	__caller.Saradc_Hal_GetResult.i.pi

	.global	__caller.Saradc_Hal_GetResult.i.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.global	Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_StopConvRequestSource:
.LDW91:
	push	{r4-r7,lr}
	sub	sp,sp,12
	mov	r5,r0
	ldr	r6,.L696
	mov	r4,r1
	mov	r0,r1
	ldr	r1,[r5,28]
.LDW02:
	ldr	r0,[r6,r0 lsl 2]
.L776:

	bl	Saradc_Hal_FlushQueue
	and	r7,r0,1
	b	.L773

.L694:	.data.w	Adc_ConfigPtr
	.endo	.L694

.L695:	.data.w	Adc_InstanceDataSet
	.endo	.L695

.L696:	.data.w	Adc_BaseAddrs
	.endo	.L696

.L773:

;line1754
..lin.36296530..4d1a7762.0_6::
.LDWlin6:
..gh.beginasm.10:
	.endo	..gh.beginasm.10
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.11:
	.endo	..gh.endasm.11

;line1759
..lin.36296530..4d1a7762.0_7::
.LDWlin7:
	ldr	r1,.L774
	ldr	r0,.L775
	ldr	r3,[r1]
	ldr	r0,[r0,r2 lsl 2]
	ldr	r3,[r3,16]
	ldr	r0,[r0,4]
	ldrb	r3,[r3,r4 lsl 1]
	mov	r1,88
	smlabb	r0,r1,r3,r0
	ldr	r1,[r5,28]
	add	r1,r1,r1 lsl 4
	add	r0,r1,r0
	ldrb	r1,[r0,48]
	ldr	r6,[r6,r4 lsl 2]
	mov	r2,sp
	add	r0,r1,r0
	ldrb	r1,[r0,31]
	mov	r0,0
	strb	r0,[sp]
	str	r0,[sp,4]
	mov	r0,r6
.L778:

	bl	Saradc_Hal_SetResultInterrupt
	and	r4,r7,r0
	ldrh	r2,[r5,2]
	mov	r0,r6
	mov	r1,2
.L780:

	bl	Saradc_Hal_ClearInterruptStatus
.LDW12:
	mov	r0,r4
	add	sp,sp,12
.L782:

	pop	{r4-r7,pc}
__ghs_eofn_Adc_StopConvRequestSource:
	.endf	Adc_StopConvRequestSource
	.endf	Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;LastChannelNum	r1	local
;RsltIntConfig	[sp]	local
;OperationRslt	r7	local

;GrpPtr	r5	param
;HwUnitId	r4	param

	.section ".ghcalltbl",""
.L777:	.data.w	.L776
	.endo	.L777
.L779:	.data.w	.L778
	.endo	.L779
.L781:	.data.w	.L780
	.endo	.L781
	.section ".ghrettbl",""
.L783:	.data.w	.L782
	.endo	.L783
	.data
	.global	__caller.Saradc_Hal_ClearInterruptStatus.v.pii

	.global	__caller.Saradc_Hal_SetResultInterrupt.i.pip

	.global	__caller.Saradc_Hal_FlushQueue.i.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_ConfigPtr - Adc_ConfigPtr) +0 == 0
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.global	Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_InitGlobalVariables:
.LDW22:
	push	{r4-r6,lr}
	ldr	r12,.L774
.LDW32:
	b	.L951

.L774:	.data.w	Adc_ConfigPtr
	.endo	.L774

.L775:	.data.w	Adc_InstanceDataSet
	.endo	.L775

.L951:

;line2103
..lin.36296530..211beca.0_8::
.LDWlin8:
..gh.beginasm.13:
	.endo	..gh.beginasm.13
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.14:
	.endo	..gh.endasm.14

;line2106
..lin.36296530..211beca.0_9::
.LDWlin9:
	ldr	r3,[r12]
	ldr	r1,[r3,16]
	ldrb	r0,[r1,r0 lsl 1]
	rsb	r1,r0,r0 lsl 3
	lsl	r4,r1,2
	ldr	r1,[r3,r2 lsl 2]
	ldr	r5,.L952
	ldr	r1,[r1,4]
	ldr	r5,[r5,r2 lsl 2]
	add	r1,r4,r1
	ldrb	r3,[r1,25]
	ldr	r1,[r5,4]
	mov	r6,88
	smlabb	r1,r0,r6,r1
	ldr	r6,[r5,12]
	add	r0,r6,r3 lsl 2
	str	r0,[r1]
	ldr	r0,[r5,8]
	add	r0,r3,r0
	str	r0,[r1,84]
	mov	r0,0
.L790:
	add	r3,r1,r0 lsl 2
	mvn	r5,0
	strh	r5,[r3,20]
	add	r0,r0,1
	strb	r5,[r3,22]
	mov	r5,1
	cmp	r0,3
	strb	r5,[r3,23]
	blo	.L790
	mov	r3,0
	str	r3,[r1,8]
	mov	r0,r3
	str	r3,[r1,12]
	b	.L793
.L795:
	ldr	r5,[r1]
	str	r3,[r5,r0 lsl 2]
	ldr	r5,[r1,84]
	strb	r3,[r5,r0]
	add	r0,r0,1
.L793:
	ldr	r5,[r12]
	ldr	r5,[r5,r2 lsl 2]
	ldr	r5,[r5,4]
	add	r5,r4,r5
	ldrb	r5,[r5,24]
	cmp	r0,r5
	blo	.L795
	str	r3,[r1,4]
	str	r3,[r1,16]
.LDW42:
.L953:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_InitGlobalVariables:
	.endf	Adc_InitGlobalVariables
	.endf	Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;DataPtr	r1	local
;LoopCtr	r0	local
;CoreId	r2	local
;HwUnitCoreIdx	r0	local
;GrpIndex	r3	local

;HwUnitId	r0	param

	.section ".ghrettbl",""
.L954:	.data.w	.L953
	.endo	.L954
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_RSInterruptHandler:
.LDW52:
	push	{r4-r8,lr}
	ldr	r2,[r2,20]
	mov	r7,r1
.LDW62:
	mov	r1,44
	mla	r5,r7,r1,r2
	ldr	r2,[r5,24]
	mov	r6,r3
	cmp	r2,0
	ldreq	r2,[r5,36]
	mov	r4,1
	ldrb	r1,[r5,28]
	cmpeq	r2,0
	beq	.L968
	ldr	r2,[r5,32]
	cmp	r2,1
	ldreq	r2,[r5,40]
	cmpeq	r2,0
	bne	.L967
	ldr	r2,[r3,12]
	lsr	r2,r2,r7
	tst	r2,1
	beq	.L967
.L968:
	add	r1,r3,r1 lsl 2
	strb	r4,[r1,23]
	mov	r1,r0
	mov	r0,r5
.L1175:

	bl	Adc_StopConvRequestSource
	lsl	r1,r4,r7
	mov	r4,r0
	ldr	r0,[r6,4]
	bic	r0,r0,r1
	mov	r1,r6
	str	r0,[r6,4]
	mov	r0,r5
.L1177:

	bl	Adc_ResetTrigSrcData
.L967:
	mov	r0,r4
.LDW72:
.L1179:

	pop	{r4-r8,pc}
__ghs_eofn_Adc_RSInterruptHandler:
	.endf	Adc_RSInterruptHandler
	.endf	Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;GrpRequestSrc	r1	local
;GrpPtr	r5	local
;OperationRslt	r4	local

;HwUnitId	r0	param
;GroupId	r7	param
;AdcKernelPtr	r2	param
;DataPtr	r6	param

	.section ".bss","awb"
.L1105:
	.endo	.L1105
	.section ".ghcalltbl",""
.L1176:	.data.w	.L1175
	.endo	.L1176
.L1178:	.data.w	.L1177
	.endo	.L1178
	.section ".ghrettbl",""
.L1180:	.data.w	.L1179
	.endo	.L1180
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
	.global	Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_IsrEventHandler:
.LDW82:
	push	{r4-r10,lr}
	mov	r7,r0
	add	r0,r1,r1 lsl 4
	add	r0,r0,r3
	mov	r8,r1
.LDW92:
	ldrb	r1,[r0,48]
	mov	r6,r2
	mov	r5,r3
	add	r0,r1,r0
	mov	r4,1
	ldrb	r9,[r0,31]
.L1403:

	bl	SchM_Enter_Adc_ResultHandling
	ldr	r1,.L1402
	ldr	r10,[r1,r7 lsl 2]
	mov	r1,2
	mov	r0,r10
.L1405:

	bl	Saradc_Hal_GetInterruptStatus
	tst	r0,r4 lsl r9
	beq	.L1183
	lsl	r2,r4,r9
	mov	r0,r10
	mov	r1,2
.L1407:

	bl	Saradc_Hal_ClearInterruptStatus
	add	r0,r5,r8 lsl 2
	ldrb	r1,[r0,23]
	cmp	r1,1
	beq	.L1183
	ldrh	r9,[r0,20]
	ldrb	r0,[r6,1]
	cmp	r0,2
	ldreq	r0,[r5,12]
	lsleq	r1,r4,r9
	movne	r2,r6
	biceq	r0,r0,r1
	movne	r1,r9
	orreq	r0,r1,r0
	movne	r0,r7
	streq	r0,[r5,12]
.L1409:

	blne	Adc_UpdateResBuffer
	ldr	r0,[r5,8]
	lsl	r8,r4,r9
	mov	r3,r5
	bic	r0,r0,r8
	mov	r2,r6
	orr	r0,r8,r0
	mov	r1,r9
	str	r0,[r5,8]
	mov	r0,r7
.L1411:

	bl	Adc_RSInterruptHandler
	mov	r4,r0
.L1413:

	bl	SchM_Exit_Adc_ResultHandling
	ldr	r0,[r5,16]
	tst	r8,r0
	ldrne	r1,[r6,20]
	movne	r0,44
	mlane	r0,r9,r0,r1
	ldrne	r0,[r0,4]
.L1415:

	blxne	r0
	b	.L1199
.L1183:
.L1417:

	bl	SchM_Exit_Adc_ResultHandling
.L1199:
	mov	r0,r4
.LDW03:
.L1419:

	pop	{r4-r10,pc}
__ghs_eofn_Adc_IsrEventHandler:
	.endf	Adc_IsrEventHandler
	.endf	Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;OperationRslt	r4	local
;GrpNr	r9	local
;LastChannelNum	r9	local

;HwUnitId	r7	param
;ReqSrc	r8	param
;HwUnitConfigPtr	r6	param
;DataPtr	r5	param

	.section ".bss","awb"
.L1315:
	.endo	.L1315
	.section ".ghcalltbl",""
.L1404:	.data.w	.L1403
	.endo	.L1404
.L1406:	.data.w	.L1405
	.endo	.L1406
.L1408:	.data.w	.L1407
	.endo	.L1408
.L1410:	.data.w	.L1409
	.endo	.L1410
.L1412:	.data.w	.L1411
	.endo	.L1412
.L1414:	.data.w	.L1413
	.endo	.L1414
.L1416:	.data.w	.L1415
	.endo	.L1416
.L1418:	.data.w	.L1417
	.endo	.L1418
	.section ".ghrettbl",""
.L1420:	.data.w	.L1419
	.endo	.L1420
	.data
	.global	__caller.SchM_Exit_Adc_ResultHandling.v.v

	.global	__caller.SchM_Exit_Adc_ResultHandling.v.v

	.global	__caller.Saradc_Hal_ClearInterruptStatus.v.pii

	.global	__caller.Saradc_Hal_GetInterruptStatus.i.pi

	.global	__caller.SchM_Enter_Adc_ResultHandling.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
	.global	Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_StartConversion:
.LDW13:
	push	{r4-fp,lr}
	sub	sp,sp,44
	ldrb	r6,[r2,28]
	str	r1,[sp,12]
	ldr	r1,.L1402
	strb	r0,[sp,7]
	ldr	r5,[r1,r0 lsl 2]
	mov	r9,r2
.LDW23:
	mov	r8,32
	str	r3,[sp,16]
	mov	r1,r6
	mov	r0,r5
.L3439:

	bl	Saradc_Hal_FlushQueue
	and	r4,r0,1
	ldrh	r2,[r9,2]
	mov	r0,r5
	mov	r1,2
.L3441:

	bl	Saradc_Hal_ClearInterruptStatus
	ldr	r2,[r9,8]
	ldrb	r0,[r2]
	strb	r0,[sp,6]
	b	.L3433

.L952:	.data.w	Adc_InstanceDataSet
	.endo	.L952

.L1402:	.data.w	Adc_BaseAddrs
	.endo	.L1402

.L3433:

;line2531
..lin.36296530..890e2e0.0_10::
.LDWlin10:
..gh.beginasm.18:
	.endo	..gh.beginasm.18
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.19:
	.endo	..gh.endasm.19

;line2536
..lin.36296530..890e2e0.0_11::
.LDWlin11:
	ldr	r1,.L3434
	ldr	r5,[r1]
	ldrb	r12,[sp,7]
	ldr	r5,[r5,16]
	ldrb	r12,[r5,r12 lsl 1]
	ldr	r5,.L3435
	ldr	r2,[r5,r2 lsl 2]
	ldr	r2,[r2,4]
	mov	r0,88
	smlabb	r2,r12,r0,r2
	ldrb	r0,[sp,6]
	add	r12,r6,r6 lsl 4
	add	r3,r12,r2
	ldr	r12,[sp,16]
	strb	r0,[r3,48]
	cmp	r12,0
	ldreq	r2,[r9,36]
	add	r0,r3,32
	cmpeq	r2,0
	ldrbeq	r2,[r9,20]
	str	r0,[sp,8]
	cmpeq	r2,0
	moveq	r8,r2
	mov	r10,0
	strb	r10,[sp,4]
	mov	fp,r10
	b	.L1435
.L1434:
	ldr	r2,[r9,8]
	ldr	r12,[sp,12]
	add	r2,fp,r2
	ldrb	r4,[r2,1]
	ldr	r12,[r12,16]
	add	r0,sp,20
	add	r2,r4,r4 lsl 3
	strb	r4,[sp,4]
	add	r12,r12,r2 lsl 2
	mov	r2,12
	add	r1,r12,24
.L3443:

	bl	memmove
	ldr	r2,[r9,12]
	cmp	r2,0
	ldrbne	r2,[r2,r4]
	ldrb	r10,[sp,20]
	strne	r2,[sp,20]
	ldr	r0,[sp,8]
	ldrb	r5,[sp,7]
	ldr	r7,.L3436
	strb	r10,[r0,fp]
	ldr	r5,[r7,r5 lsl 2]
	add	r2,sp,20
	mov	r1,r10
	mov	r0,r5
.L3445:

	bl	Saradc_Hal_DynamicChannelConfig
	ldrb	r3,[r9,20]
	and	r4,r0,1
	cmp	r3,0
	beq	.L1438
	add	r0,r5,72
	add	r12,r0,r10 lsl 2
	ldr	r2,[r12]
	bfi	r2,r3,16,4
	str	r2,[r12]
	mvn	r12,0
	ldr	r2,[r0,r10 lsl 2]
	ubfx	r2,r2,16,4
	cmp	r3,r2
	movne	r12,0
	and	r4,r4,r12
.L1438:
	ldr	r2,[sp,12]
	ldr	r2,[r2,8]
	cmp	r2,0
	beq	.L1448
	ldrb	r2,[r9]
	cmp	r2,1
	ldrbeq	r2,[sp,25]
	cmpeq	r2,1
	bne	.L1448
	b	.L1456
.L1455:
	ldrb	r0,[r2,r1]
	add	r2,sp,20
	mov	r1,r10
	ldr	r0,[r7,r0 lsl 2]
.L3447:

	bl	Saradc_Hal_DynamicChannelConfig
	ldrb	r3,[r9,20]
	and	r4,r4,r0
	cmp	r3,0
	beq	.L1454
	ldr	lr,[sp,12]
	ldrb	r1,[sp,5]
	ldr	lr,[lr,8]
	ldrb	lr,[lr,r1]
	ldr	lr,[r7,lr lsl 2]
	add	lr,lr,72
	add	r12,lr,r10 lsl 2
	ldr	r2,[r12]
	bfi	r2,r3,16,4
	str	r2,[r12]
	ldr	r2,[lr,r10 lsl 2]
	mov	r12,1
	ubfx	r2,r2,16,4
	cmp	r3,r2
	movne	r12,0
	and	r4,r4,r12
.L1454:
	ldrb	r0,[sp,5]
	add	r2,r0,1
.L1456:
	strb	r2,[sp,5]
	ldr	r2,[sp,12]
	ldr	r2,[r2,8]
	ldrb	r1,[sp,5]
	ldrb	r12,[r2]
	cmp	r1,r12
	bls	.L1455
.L1448:
	cmp	fp,0
	orreq	r8,r8,128
	bicne	r8,r8,128
	mov	r3,r8
	mov	r2,r6
	mov	r1,r10
	mov	r0,r5
.L3449:

	bl	Saradc_Hal_FillQueue
	add	fp,fp,1
	and	r4,r4,r0
	uxtb	fp,fp
.L1435:
	ldrb	r0,[sp,6]
	cmp	fp,r0
	bhs	.L1432
	cmp	r4,1
	beq	.L1434
.L1432:
	ldr	r1,[sp,12]
	ldrb	r2,[sp,4]
	ldr	r1,[r1,16]
	add	r2,r2,r2 lsl 3
	ldrb	r5,[sp,7]
	ldr	r1,[r1,r2 lsl 2]
	ldr	r2,.L3436
	ldr	r5,[r2,r5 lsl 2]
	cmp	r1,0
	ldreq	r1,.L3437
	mov	r0,r5
.L3451:

	bl	Saradc_Hal_SetBoundary
	mov	r2,1
	str	r6,[sp,36]
	and	r4,r4,r0
	mov	r1,r10
	mov	r0,r5
	strb	r2,[sp,32]
	add	r2,sp,32
.L3453:

	bl	Saradc_Hal_SetResultInterrupt
	and	r4,r4,r0
	ldr	r0,[sp,16]
	cmp	r0,0
	bne	.L1474
	ldr	r2,[r9,36]
	cmp	r2,0
	ldrbeq	r2,[r9,20]
	cmpeq	r2,0
	bne	.L1476
	add	r12,r5,r6 lsl 2
	ldr	r2,[r12,36]
	mov	r1,1
	add	r8,r5,36
	bfi	r2,r1,0,2
	str	r2,[r8,r6 lsl 2]
	ldr	r12,[r12,36]
	mvn	r7,0
	cmp	r2,r12
	movne	r7,r0
	ldr	r2,[r8,r6 lsl 2]
	orr	r2,r2,256
	and	r0,r4,r7
	str	r2,[r8,r6 lsl 2]
	b	.L1421
.L1476:
	mov	r2,r6
	ldr	r1,.L3438
	mov	r0,r5
.L3455:

	bl	Saradc_Hal_SetTriggerGating
	add	r12,r5,r6 lsl 2
	ldr	r2,[r12,60]!
	orr	r2,r2,1<<16
	and	r0,r4,r0
	str	r2,[r12]
	b	.L1421
.L1474:
	mov	r2,r6
	ldr	r1,[r9,16]
	mov	r0,r5
.L3457:

	bl	Saradc_Hal_SetTriggerGating
	and	r0,r4,r0
.L1421:
.LDW33:
	add	sp,sp,44
.L3459:

	pop	{r4-fp,pc}
__ghs_eofn_Adc_StartConversion:
	.endf	Adc_StartConversion
	.endf	Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;GrpReqSrc	r6	local
;ChCnt	fp	local
;TotalGrpCh	[sp,6]	local
;ChIdx	[sp,4]	local
;IntChNr	r10	local
;ConversionMode	r8	local
;HwUnitCnt	[sp,5]	local
;RsltIntConfig	[sp,32]	local
;OperationRslt	r4	local
;ChConfig	[sp,20]	local
;dataReductionMode	r3	local
;ret	r12	local
;pSaradc	lr	local
;dataReductionMode	r3	local
;ret	r12	local
;QMODE	r2	local
;ret	r7	local

;HwUnitId	[sp,7]	param
;AdcKernelPtr	[sp,12]	param
;GrpPtr	r9	param
;TriggerSrc	[sp,16]	param

	.section ".mcal_const_asil_d_unspecified","a"
Adc_BoundDefaultConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_BoundDefaultConfig:	.data.b	0,0,255,15
	.endo	Adc_BoundDefaultConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_BoundDefaultConfig
Adc_ContinuousTimerConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.::
Adc_ContinuousTimerConfig:	.space	4
	.data.b	3,0,0,0
	.data.b	1,0,0,0
	.data.b	3,0,0,0
	.data.b	0,1,0,0
	.data.b	2,0,0,0
	.endo	Adc_ContinuousTimerConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.endo	Adc_ContinuousTimerConfig
	.section ".ghcalltbl",""
.L3440:	.data.w	.L3439
	.endo	.L3440
.L3442:	.data.w	.L3441
	.endo	.L3442
.L3444:	.data.w	.L3443
	.endo	.L3444
.L3446:	.data.w	.L3445
	.endo	.L3446
.L3448:	.data.w	.L3447
	.endo	.L3448
.L3450:	.data.w	.L3449
	.endo	.L3450
.L3452:	.data.w	.L3451
	.endo	.L3452
.L3454:	.data.w	.L3453
	.endo	.L3454
.L3456:	.data.w	.L3455
	.endo	.L3456
.L3458:	.data.w	.L3457
	.endo	.L3458
	.section ".ghrettbl",""
.L3460:	.data.w	.L3459
	.endo	.L3460
	.data
	.global	__caller.Saradc_Hal_SetTriggerGating.i.ppi

	.global	__caller.Saradc_Hal_SetTriggerGating.i.ppi

	.global	__caller.Saradc_Hal_SetResultInterrupt.i.pip

	.global	__caller.Saradc_Hal_SetBoundary.i.pp

	.global	__caller.Saradc_Hal_SetBoundary.i.pp

	.global	__caller.Saradc_Hal_FillQueue.i.piii

	.global	__caller.Saradc_Hal_DynamicChannelConfig.i.pip

	.global	__caller.Saradc_Hal_DynamicChannelConfig.i.pip

	.global	__caller.Saradc_Hal_ClearInterruptStatus.v.pii

	.global	__caller.Saradc_Hal_FlushQueue.i.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
	.global	Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckGroupStatusAll:
.LDW43:
	push	{r4-r6,lr}
.LDW53:
	mov	r4,0
	b	.L3631

.L3434:	.data.w	Adc_ConfigPtr
	.endo	.L3434

.L3435:	.data.w	Adc_InstanceDataSet
	.endo	.L3435

.L3436:	.data.w	Adc_BaseAddrs
	.endo	.L3436

.L3437:	.data.w	Adc_BoundDefaultConfig
	.endo	.L3437

.L3438:	.data.w	Adc_ContinuousTimerConfig
	.endo	.L3438

.L3631:

;line2755
..lin.36296530..a30e99b4.0_12::
.LDWlin12:
..gh.beginasm.21:
	.endo	..gh.beginasm.21
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.22:
	.endo	..gh.endasm.22

	mov	r5,r0
;line2759
..lin.36296530..a30e99b4.0_13::
.LDWlin13:
	mov	r6,r4
	b	.L3467
.L3469:
	ldr	r1,[r1,4]
	ldr	r3,[r2,16]
	rsb	r0,r0,r0 lsl 3
	ldrb	r0,[r1,r0 lsl 2]
	ldr	r2,.L3632
	ldrb	r3,[r3,r0 lsl 1]
	ldr	r0,[r2,r5 lsl 2]
	ldr	r0,[r0,4]
	mov	r1,88
	smlabb	r0,r1,r3,r0
	ldr	r0,[r0,4]
	cmp	r0,0
	movne	r4,1
	movne	r3,11
	movne	r1,0
	movne	r0,123
	movne	r2,r4
.L3634:

	blne	Det_ReportRuntimeError
	add	r6,r6,1<<24
.L3467:
	ldr	r0,.L3633
	ldr	r2,[r0]
	ldr	r1,[r2,r5 lsl 2]
	lsr	r0,r6,24
	ldrb	r3,[r1]
	cmp	r0,r3
	bhs	.L3468
	cmp	r4,0
	beq	.L3469
.L3468:
	mov	r0,r4
.LDW63:
.L3636:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_CheckGroupStatusAll:
	.endf	Adc_CheckGroupStatusAll
	.endf	Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r4	local
;CoreId	r5	local

	.section ".ghcalltbl",""
.L3635:	.data.w	.L3634
	.endo	.L3635
	.section ".ghrettbl",""
.L3637:	.data.w	.L3636
	.endo	.L3637
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.23:
	.endo	..gh.f.a.1.e.23
	.global	Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckDriverState:
.LDW73:
	push	{r4,lr}
.LDW83:
	mov	r2,0
	mov	r12,r1
	b	.L3746

.L3632:	.data.w	Adc_InstanceDataSet
	.endo	.L3632

.L3633:	.data.w	Adc_ConfigPtr
	.endo	.L3633

.L3746:

;line2827
..lin.36296530..86b3bc97.0_14::
.LDWlin14:
..gh.beginasm.24:
	.endo	..gh.beginasm.24
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.25:
	.endo	..gh.endasm.25

;line2830
..lin.36296530..86b3bc97.0_15::
.LDWlin15:
	ldr	r4,.L3747
	ldr	r1,.L3748
	ldr	r4,[r4]
	ldr	r1,[r1,r3 lsl 2]
	ldr	r4,[r4,16]
	ldr	r1,[r1,4]
	ldrb	r4,[r4,r12 lsl 1]
	mov	r12,88
	smlabb	r1,r12,r4,r1
	ldr	r12,[r1,84]
	ldr	r3,[r1,8]
	ldr	r1,[r1,4]
	lsr	r3,r3,r0
	ldrb	r12,[r12,r0]
	lsr	r0,r1,r0
	and	r3,r3,1
	tst	r0,1
	cmpeq	r3,0
	cmpeq	r12,0
	moveq	r2,1
	mov	r0,r2
.LDW93:
.L3749:

	pop	{r4,pc}
__ghs_eofn_Adc_CheckDriverState:
	.endf	Adc_CheckDriverState
	.endf	Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;DataPtr	r1	local
;RetErr	r2	local
;GrpRes	r3	local
;NoOfValidConv	r12	local

;Group	r0	param
;HwUnitId	r1	param

	.section ".ghrettbl",""
.L3750:	.data.w	.L3749
	.endo	.L3750
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
	.global	Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckInit:
.LDW04:
	push	{r4,lr}
.LDW14:
	mov	r4,1
	b	.L3913

.L3747:	.data.w	Adc_ConfigPtr
	.endo	.L3747

.L3748:	.data.w	Adc_InstanceDataSet
	.endo	.L3748

.L3913:

;line2889
..lin.36296530..8aa610be.0_16::
.LDWlin16:
..gh.beginasm.27:
	.endo	..gh.beginasm.27
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.28:
	.endo	..gh.endasm.28

;line2891
..lin.36296530..8aa610be.0_17::
.LDWlin17:
	ldr	r1,.L3914
	ldr	r1,[r1,r2 lsl 2]
	cmp	r1,0
	moveq	r2,r0
	moveq	r3,224
	beq	.L3905
.L3757:
	ldr	r1,[r1]
	ldrb	r1,[r1]
	cmp	r1,1
	beq	.L3760
.L3761:
	mov	r2,r0
	mov	r3,10
	mov	r1,0
.L3905:

	mov	r0,123
.L3915:

	bl	Det_ReportError
	b	.L3759
.L3760:
	mov	r4,0
.L3759:
	mov	r0,r4
.LDW24:
.L3917:

	pop	{r4,pc}
__ghs_eofn_Adc_CheckInit:
	.endf	Adc_CheckInit
	.endf	Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r4	local

;ServiceId	r0	param

	.section ".bss","awb"
.L3843:
	.endo	.L3843
	.section ".ghcalltbl",""
.L3916:	.data.w	.L3915
	.endo	.L3916
	.section ".ghrettbl",""
.L3918:	.data.w	.L3917
	.endo	.L3918
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
	.global	Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CommDetCheck:
.LDW34:
	push	{r2,r4-r7,lr}
	mov	r12,r0
	mov	r5,r1
	mov	r6,r2
.LDW44:
	mov	r0,0
	b	.L4236

.L3914:	.data.w	Adc_InstanceDataSet
	.endo	.L3914

.L4236:

;line2951
..lin.36296530..256fd593.0_18::
.LDWlin18:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.31:
	.endo	..gh.endasm.31

	ldr	r1,.L4237
;line2957
..lin.36296530..256fd593.0_19::
.LDWlin19:
	ldr	r2,[r1]
	mov	r4,r3
	ldr	r1,[r2,16]
	ldr	r7,[r2,r4 lsl 2]
	ldrb	r1,[r1,r6 lsl 1]
	ldr	r7,[r7,4]
	rsb	r1,r1,r1 lsl 3
	add	r7,r7,r1 lsl 2
	ldrb	r1,[r7,24]
	cmp	r5,r1
	movhs	r2,r12
	movhs	r3,21
	bhs	.L4218
.L3925:
	ldr	r1,[r7,20]
	subs	r2,r12,2
	mov	r3,44
	cmp	r2,7
	mla	r1,r5,r3,r1
.L4238:

	pophi	{r2,r4-r7,pc}
	adr	r3,.L4091
	jtdispatch	r2,r3,50
.L4092:

.L4091:

;line2971
..lin.36296530..256fd593.0_20::
.LDWlin20:
	jtentry	(.L3929-.L4092)>>2
	jtentry	(.L3930-.L4092)>>2
	jtentry	(.L3927-.L4092)>>2
	jtentry	(.L3931-.L4092)>>2
	jtentry	(.L3932-.L4092)>>2
	jtentry	(.L3933-.L4092)>>2
	jtentry	(.L3933-.L4092)>>2
	jtentry	(.L3934-.L4092)>>2
	jtentry	-1
	.align	4
	.type	.L4091, $object
	.size	.L4091, .-.L4091

.L3929:
;line2976
..lin.36296530..256fd593.0_21::
.LDWlin21:
	mov	r3,r7
	mov	r2,r5
	mov	r1,r6
	mov	r0,r4
.L4240:

	bl	Adc_CheckSwConv
.L4242:

	pop	{r2,r4-r7,pc}
.L3930:
	ldr	r1,[r1,24]
	cmp	r1,0
.L4244:

	popeq	{r2,r4-r7,pc}
	mov	r2,r12
	mov	r3,23
	b	.L4219
.L3931:
	mov	r3,r7
	mov	r2,r6
	mov	r1,r5
	mov	r0,r4
.L4246:

	bl	Adc_CheckParamGrpEnableHwTrigg
.L4248:

	pop	{r2,r4-r7,pc}
.L3932:
	mov	r0,r12
.L4250:

	bl	Adc_CheckParamGrpDisableHwTrigg
.L4252:

	pop	{r2,r4-r7,pc}
.L3933:
	ldr	r1,[r1,4]
	cmp	r1,0
.L4254:

	popne	{r2,r4-r7,pc}
	mov	r2,r12
	mov	r3,24
	b	.L4220
.L3934:
	ldr	r1,[r1,12]
	cmp	r1,0
.L4256:

	popeq	{r2,r4-r7,pc}
.L3948:
	mov	r2,r12
	mov	r3,33
.L4218:

.L4219:

	mov	r1,r0
.L4220:

	mov	r0,123
.L4258:

	bl	Det_ReportError
	mov	r0,1
.L3927:
.LDW54:
.L4260:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Adc_CommDetCheck:
	.endf	Adc_CommDetCheck
	.endf	Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;GrpPtr	r1	local
;CfgPtr	r7	local
;RetErr	r0	local
;CoreId	r4	local

;ServiceId	r12	param
;Group	r5	param
;HwUnitId	r6	param

	.section ".ghrettbl",""
.L4239:	.data.w	.L4238
	.endo	.L4239
	.section ".ghcalltbl",""
.L4241:	.data.w	.L4240
	.endo	.L4241
	.section ".ghrettbl",""
.L4243:	.data.w	.L4242
	.endo	.L4243
.L4245:	.data.w	.L4244
	.endo	.L4245
	.section ".ghcalltbl",""
.L4247:	.data.w	.L4246
	.endo	.L4247
	.section ".ghrettbl",""
.L4249:	.data.w	.L4248
	.endo	.L4249
	.section ".ghcalltbl",""
.L4251:	.data.w	.L4250
	.endo	.L4251
	.section ".ghrettbl",""
.L4253:	.data.w	.L4252
	.endo	.L4253
.L4255:	.data.w	.L4254
	.endo	.L4255
.L4257:	.data.w	.L4256
	.endo	.L4257
	.section ".ghcalltbl",""
.L4259:	.data.w	.L4258
	.endo	.L4259
	.section ".ghrettbl",""
.L4261:	.data.w	.L4260
	.endo	.L4261
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.ghsnote jtable,4,.L4091,.L4092,.L4091,8
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.32:
	.endo	..gh.f.a.1.e.32
	.global	Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_DetErrorCheck:
.LDW64:
	push	{r4-r6,lr}
	mov	r6,r1
	mov	r5,r2
.LDW74:
	mov	r4,r0
.L4371:

	bl	Adc_CheckInit
	cmp	r0,0
.L4373:

	popne	{r4-r6,pc}
	mov	r1,r5
	mov	r0,r4
.L4375:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
	moveq	r2,r5
	moveq	r1,r6
	moveq	r0,r4
.L4377:

	bleq	Adc_CommDetCheck
.L4262:
.LDW84:
.L4379:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_DetErrorCheck:
	.endf	Adc_DetErrorCheck
	.endf	Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;Error	r0	local

;ServiceId	r4	param
;Group	r6	param
;HwUnitId	r5	param

	.section ".bss","awb"
.L4322:
	.endo	.L4322
	.section ".ghcalltbl",""
.L4372:	.data.w	.L4371
	.endo	.L4372
	.section ".ghrettbl",""
.L4374:	.data.w	.L4373
	.endo	.L4374
	.section ".ghcalltbl",""
.L4376:	.data.w	.L4375
	.endo	.L4376
.L4378:	.data.w	.L4377
	.endo	.L4378
	.section ".ghrettbl",""
.L4380:	.data.w	.L4379
	.endo	.L4380
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.33:
	.endo	..gh.f.a.1.e.33
	.global	Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckInitParam:
.LDW94:
	push	{r4,lr}
.LDW05:
	mov	r4,1
	b	.L4614

.L4237:	.data.w	Adc_ConfigPtr
	.endo	.L4237

.L4614:

;line3131
..lin.36296530..3603026f.0_22::
.LDWlin22:
..gh.beginasm.34:
	.endo	..gh.beginasm.34
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.35:
	.endo	..gh.endasm.35

;line3133
..lin.36296530..3603026f.0_23::
.LDWlin23:
	ldr	r3,.L4615
	ldr	r1,[r3,r2 lsl 2]
	cmp	r1,0
	beq	.L4397
	ldr	r1,[r1]
	ldrb	r1,[r1]
	cmp	r1,1
	moveq	r3,13
	beq	.L4602
.L4390:
	movs	r1,r0
	moveq	r3,14
	moveq	r2,r0
	beq	.L4603
.L4393:
	ldr	r0,[r0,r2 lsl 2]
	cmp	r0,0
	bne	.L4396
.L4397:
	mov	r3,224
.L4602:

	mov	r2,0
	mov	r1,r2
.L4603:

	mov	r0,123
.L4616:

	bl	Det_ReportError
	b	.L4389
.L4396:
	mov	r4,0
.L4389:
	mov	r0,r4
.LDW15:
.L4618:

	pop	{r4,pc}
__ghs_eofn_Adc_CheckInitParam:
	.endf	Adc_CheckInitParam
	.endf	Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;CoreId	r2	local
;RetErr	r4	local

;ConfigPtr	r0	param

	.section ".bss","awb"
.L4516:
	.endo	.L4516
	.section ".ghcalltbl",""
.L4617:	.data.w	.L4616
	.endo	.L4617
	.section ".ghrettbl",""
.L4619:	.data.w	.L4618
	.endo	.L4619
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.36:
	.endo	..gh.f.a.1.e.36
	.global	Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckSwConv:
.LDW25:
	push	{r2,r4-r5,lr}
.LDW35:
	ldr	r5,[r3,20]
	mov	r12,44
	mla	r12,r2,r12,r5
	ldr	r12,[r12,24]
	mov	r4,1
	cmp	r12,0
	movne	r3,23
	movne	r2,2
	movne	r1,0
	bne	.L4805
.L4622:
	ldrb	r3,[r3,1]
	cmp	r3,2
	beq	.L4628
	ldr	r5,.L4814
	ldr	r3,[r5]
	ldr	r3,[r3,16]
	ldrb	r1,[r3,r1 lsl 1]
	mov	r3,88
	smulbb	r1,r1,r3
	ldr	r3,.L4615
	ldr	r0,[r3,r0 lsl 2]
	ldr	r0,[r0,4]
	ldr	r1,[r1,r0]
	ldr	r1,[r1,r2 lsl 2]
	cmp	r1,0
	bne	.L4628
.L4629:
	mov	r3,25
	mov	r2,2
.L4805:

	mov	r0,123
.L4815:

	bl	Det_ReportError
	b	.L4624
.L4628:
	mov	r4,r12
.L4624:
	mov	r0,r4
.LDW45:
.L4817:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_CheckSwConv:
	.endf	Adc_CheckSwConv
	.endf	Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r4	local

;CoreId	r0	param
;HwUnitId	r1	param
;Group	r2	param
;AdcKernelPtr	r3	param

	.section ".ghcalltbl",""
.L4816:	.data.w	.L4815
	.endo	.L4816
	.section ".ghrettbl",""
.L4818:	.data.w	.L4817
	.endo	.L4818
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.37:
	.endo	..gh.f.a.1.e.37
	.global	Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckParamGrpEnableHwTrigg:
.LDW55:
	push	{r2,r4-r5,lr}
.LDW65:
	ldr	r5,[r3,20]
	mov	r12,44
	mla	r12,r1,r12,r5
	ldr	r5,[r12,24]
	mov	r4,1
	cmp	r5,1
	movne	r3,23
	bne	.L5033
.L4821:
	ldr	r12,[r12,36]
	cmp	r12,1
	bne	.L4824
.L4825:
	mov	r3,22
.L5033:

	mov	r2,5
	mov	r1,0
	b	.L5034
.L4824:
	ldrb	r3,[r3,1]
	cmp	r3,2
	beq	.L4830
	ldr	r12,.L4814
	ldr	r3,[r12]
	ldr	r3,[r3,16]
	ldrb	r2,[r3,r2 lsl 1]
	mov	r3,88
	smulbb	r2,r2,r3
	ldr	r3,.L4615
	ldr	r0,[r3,r0 lsl 2]
	ldr	r0,[r0,4]
	ldr	r0,[r2,r0]
	ldr	r1,[r0,r1 lsl 2]
	cmp	r1,0
	bne	.L4830
.L4831:
	mov	r3,25
	mov	r2,5
.L5034:

	mov	r0,123
.L5045:

	bl	Det_ReportError
	b	.L4823
.L4830:
	mov	r4,0
.L4823:
	mov	r0,r4
.LDW75:
.L5047:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_CheckParamGrpEnableHwTrigg:
	.endf	Adc_CheckParamGrpEnableHwTrigg
	.endf	Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;GrpPtr	r12	local
;RetErr	r4	local

;CoreId	r0	param
;Group	r1	param
;HwUnitId	r2	param
;AdcKernelPtr	r3	param

	.section ".ghcalltbl",""
.L5046:	.data.w	.L5045
	.endo	.L5046
	.section ".ghrettbl",""
.L5048:	.data.w	.L5047
	.endo	.L5048
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.38:
	.endo	..gh.f.a.1.e.38
	.global	Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckParamGrpDisableHwTrigg:
.LDW85:
	str	lr,[sp,-8]!
.LDW95:
	ldr	r2,[r1,24]
	cmp	r2,1
	beq	.L5051
.L5052:
	mov	r2,r0
	mov	r3,23
.L5179:

	mov	r1,0
	mov	r0,123
.L5186:

	bl	Det_ReportError
	mov	r0,1
.L5188:

	ldr	pc,[sp],8
.L5051:
	ldr	r1,[r1,36]
	cmp	r1,1
	moveq	r2,r0
	moveq	r3,22
	beq	.L5179
.L5054:
	mov	r0,0
.LDW06:
.L5190:

	ldr	pc,[sp],8
__ghs_eofn_Adc_CheckParamGrpDisableHwTrigg:
	.endf	Adc_CheckParamGrpDisableHwTrigg
	.endf	Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

;ServiceId	r0	param
;GrpPtr	r1	param

	.section ".bss","awb"
.L5122:
	.endo	.L5122
	.section ".ghcalltbl",""
.L5187:	.data.w	.L5186
	.endo	.L5187
	.section ".ghrettbl",""
.L5189:	.data.w	.L5188
	.endo	.L5189
.L5191:	.data.w	.L5190
	.endo	.L5191
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.39:
	.endo	..gh.f.a.1.e.39
	.global	Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_CheckMulticoreAllocateError:
.LDW16:
	push	{r2,r4-r5,lr}
.LDW26:
	mov	r4,1
	cmp	r1,12
	blo	.L5199
.L5195:
	mov	r2,r0
	mov	r3,21
.L5417:

.L5418:

	mov	r1,0
	mov	r0,123
.L5430:

	bl	Det_ReportError
	b	.L5196

.L4615:	.data.w	Adc_InstanceDataSet
	.endo	.L4615

.L4814:	.data.w	Adc_ConfigPtr
	.endo	.L4814

.L5199:
;line3429
..lin.36296530..ae58230d.0_24::
.LDWlin24:
	mov	r12,r1
..gh.beginasm.40:
	.endo	..gh.beginasm.40
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.41:
	.endo	..gh.endasm.41

;line3438
..lin.36296530..ae58230d.0_25::
.LDWlin25:
	ldr	r1,.L5429
	ldr	r5,[r1]
	ldr	r3,[r5,16]
	ldr	r1,[r5,r2 lsl 2]
	ldrb	r3,[r3,r12 lsl 1]
	ldrb	r2,[r1]
	cmp	r3,r2
	bhs	.L5208
	ldr	r1,[r1,4]
	rsb	r2,r3,r3 lsl 3
	lsl	r2,r2,2
	adds	r3,r2,r1
	moveq	r2,r0
	moveq	r3,224
	beq	.L5418
.L5204:
	ldrb	r1,[r1,r2]
	cmp	r12,r1
	beq	.L5207
.L5208:
	mov	r2,r0
	mov	r3,225
	b	.L5417
.L5207:
	mov	r4,0
.L5196:
	mov	r0,r4
.LDW36:
.L5432:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_CheckMulticoreAllocateError:
	.endf	Adc_CheckMulticoreAllocateError
	.endf	Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;RetErr	r4	local
;HwUnitCoreIdx	r3	local

;ServiceId	r0	param
;HwUnitId	r12	param

	.section ".ghcalltbl",""
.L5431:	.data.w	.L5430
	.endo	.L5431
	.section ".ghrettbl",""
.L5433:	.data.w	.L5432
	.endo	.L5433
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.42:
	.endo	..gh.f.a.1.e.42
	.global	Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_ResetTrigSrcData:
.LDW46:
.LDW56:
	ldrb	r0,[r0,28]
	add	r0,r1,r0 lsl 2
	mvn	r1,0
	strh	r1,[r0,20]
	strb	r1,[r0,22]
.LDW66:
.L5484:

	ret	
__ghs_eofn_Adc_ResetTrigSrcData:
	.endf	Adc_ResetTrigSrcData
	.endf	Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

;GrpPtr	r0	param
;DataPtr	r1	param

	.section ".bss","awb"
.L5466:
	.endo	.L5466
	.section ".ghrettbl",""
.L5485:	.data.w	.L5484
	.endo	.L5485
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.43:
	.endo	..gh.f.a.1.e.43
	.global	Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_ReadGroupDetCheck:
.LDW76:
	push	{r2,r4-r5,lr}
	mov	r4,r1
	mov	r5,r2
.LDW86:
	mov	r2,r1
	mov	r1,r0
	mov	r0,4
.L5650:

	bl	Adc_DetErrorCheck
	cmp	r0,0
.L5652:

	popne	{r2,r4-r5,pc}
	mov	r12,20
	cmp	r5,0
	beq	.L5491
	b	.L5648

.L5429:	.data.w	Adc_ConfigPtr
	.endo	.L5429

.L5648:

;line3576
..lin.36296530..f5a3b3d0.0_26::
.LDWlin26:
..gh.beginasm.44:
	.endo	..gh.beginasm.44
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.45:
	.endo	..gh.endasm.45

;line3578
..lin.36296530..f5a3b3d0.0_27::
.LDWlin27:
	ldr	r1,.L5649
	ldr	r5,[r1]
	mov	r12,32
	ldr	r1,[r5,16]
	ldrb	r1,[r1,r4 lsl 1]
	rsb	r2,r1,r1 lsl 3
	ldr	r1,[r5,r3 lsl 2]
	ldr	r1,[r1,4]
	add	r1,r1,r2 lsl 2
	ldrb	r1,[r1,1]
	cmp	r1,2
.L5654:

	popne	{r2,r4-r5,pc}
.L5491:
	mov	r3,r12
	mov	r2,4
	mov	r1,r0
	mov	r0,123
.L5656:

	bl	Det_ReportError
	mov	r0,1
.LDW96:
.L5658:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_ReadGroupDetCheck:
	.endf	Adc_ReadGroupDetCheck
	.endf	Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;Error	r0	local

;GroupId	r0	param
;PhyHwUnitId	r4	param
;DataBufferPtr	r5	param

	.section ".ghcalltbl",""
.L5651:	.data.w	.L5650
	.endo	.L5651
	.section ".ghrettbl",""
.L5653:	.data.w	.L5652
	.endo	.L5653
.L5655:	.data.w	.L5654
	.endo	.L5655
	.section ".ghcalltbl",""
.L5657:	.data.w	.L5656
	.endo	.L5657
	.section ".ghrettbl",""
.L5659:	.data.w	.L5658
	.endo	.L5659
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.46:
	.endo	..gh.f.a.1.e.46
	.global	Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.:
Adc_LocalDisableHardwareTrigger:
.LDW07:
	push	{r2,r4-r9,lr}
	mov	r9,r1
	ldr	r1,.L5649
	mov	r8,r0
.LDW17:
	ldr	r0,[r1]
	ldr	r1,[r0,r3 lsl 2]
	ldr	r0,[r0,16]
	ldrb	r0,[r0,r9 lsl 1]
	ldr	r1,[r1,4]
	rsb	r0,r0,r0 lsl 3
	add	r5,r2,4
	add	r0,r1,r0 lsl 2
	ldr	r0,[r0,20]
	mov	r1,44
	mov	r4,1
	mla	r7,r8,r1,r0
.L5785:

	bl	SchM_Enter_Adc_DisableHwTrig
	mvn	r6,r4 lsl r8
	ldm	r5,{r1-r3}
	and	r0,r2,r6
	and	r3,r3,r6
	stmib	r5,{r0,r3}
	lsr	r0,r1,r8
	sub	r5,r5,4
	tst	r0,1
	beq	.L5675
	ldr	r0,[r7,28]
	add	r0,r5,r0 lsl 2
	mov	r1,r9
	strb	r4,[r0,23]
	mov	r0,r7
.L5787:

	bl	Adc_StopConvRequestSource
	mov	r4,r0
	mov	r1,r5
	mov	r0,r7
.L5789:

	bl	Adc_ResetTrigSrcData
	ldr	r0,[r5,4]
	and	r0,r0,r6
	str	r0,[r5,4]
.L5675:
	add	r3,r5,8
	ldm	r3,{r0-r2}
	and	r0,r0,r6
	and	r1,r1,r6
	and	r2,r2,r6
	stm	r3,{r0-r2}
.L5791:

	bl	SchM_Exit_Adc_DisableHwTrig
	mov	r0,r4
.LDW27:
.L5793:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Adc_LocalDisableHardwareTrigger:
	.endf	Adc_LocalDisableHardwareTrigger
	.endf	Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
;OperationRslt	r4	local
;GrpPtr	r7	local

;GroupId	r8	param
;PhyHwUnitId	r9	param
;DataPtr	r5	param
;CoreId	r3	param

	.section ".ghcalltbl",""
.L5786:	.data.w	.L5785
	.endo	.L5786
.L5788:	.data.w	.L5787
	.endo	.L5788
.L5790:	.data.w	.L5789
	.endo	.L5790
.L5792:	.data.w	.L5791
	.endo	.L5792
	.section ".ghrettbl",""
.L5794:	.data.w	.L5793
	.endo	.L5794
	.data
	.global	__caller.SchM_Exit_Adc_DisableHwTrig.v.v

	.global	__caller.SchM_Enter_Adc_DisableHwTrig.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.47:
	.endo	..gh.f.a.1.e.47
__callee.Adc_Init.v.p::
	.size	__callee.Adc_Init.v.p,0
Adc_Init::
.LDW37:
	push	{r4-r10,lr}
.LDW47:
	mov	r6,1
	mov	r7,r0
.L7724:

	bl	Adc_CheckInitParam
	cmp	r0,0
.L7726:

	popne	{r4-r10,pc}
	ldr	r0,.L5649
	str	r7,[r0]
	b	.L7721

.L5649:	.data.w	Adc_ConfigPtr
	.endo	.L5649

.L7721:

;line3815
..lin.36296530..77f9ca40.0_28::
.LDWlin28:
..gh.beginasm.48:
	.endo	..gh.beginasm.48
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.49:
	.endo	..gh.endasm.49

	mov	r4,r2
;line3818
..lin.36296530..77f9ca40.0_29::
.LDWlin29:
	mov	r5,0
.L5828:
	ldr	r1,[r7,r4 lsl 2]
	ldrb	r0,[r1]
	cmp	r5,r0
	ldrhs	r0,.L7722
	ldrhs	r0,[r0,r4 lsl 2]
	ldrhs	r0,[r0]
	strbhs	r6,[r0]
	bhs	.L5797
	ldr	r1,[r1,4]
	rsb	r0,r5,r5 lsl 3
	add	r8,r1,r0 lsl 2
.L7728:

	bl	SchM_Enter_Adc_Endinit
	ldrb	r0,[r8]
	ldr	r9,.L7723
	ldr	r1,[r8,4]
	ldr	r0,[r9,r0 lsl 2]
.L7730:

	bl	Saradc_Hal_InitModule
	and	r6,r6,r0
.L7732:

	bl	SchM_Exit_Adc_Endinit
	mov	r0,0
.L5809:
	ldrb	r1,[r8]
	ldr	r1,[r9,r1 lsl 2]
	ldr	r1,[r1,4]
	tst	r1,1<<31
	bne	.L5815
	add	r0,r0,1
	uxtb	r0,r0
	cmp	r0,63
	blo	.L5809
	mov	r6,0
	b	.L5806
.L5815:
.L7734:

	bl	SchM_Enter_Adc_Endinit
	ldrb	r0,[r8]
	ldr	r0,[r9,r0 lsl 2]
.L7736:

	bl	Saradc_Hal_OpenCalibration
	mov	r10,0
	b	.L5821
.L5820:
	ldr	r1,[r8,16]
	add	r0,r0,r0 lsl 3
	add	r1,r1,r0 lsl 2
	ldrb	r0,[r8]
	add	r2,r1,4
	ldr	r1,[r1,4]
	ldr	r0,[r9,r0 lsl 2]
.L7738:

	bl	Saradc_Hal_InitChannel
	add	r10,r10,1<<24
.L5821:
	ldrb	r1,[r8,12]
	and	r6,r6,r0
	lsr	r0,r10,24
	cmp	r0,r1
	blo	.L5820
	ldrb	r0,[r8,1]
	cmp	r0,1
	ldrbne	r0,[r8,26]
	cmpne	r0,0
	moveq	r1,1
	movne	r1,0
	ldrb	r0,[r8]
	ldr	r0,[r9,r0 lsl 2]
.L7740:

	bl	Saradc_Hal_MaskResultInterrupt
	and	r6,r6,r0
.L7742:

	bl	SchM_Exit_Adc_Endinit
.L5806:
	ldrb	r0,[r8]
.L7744:

	bl	Adc_InitGlobalVariables
	add	r5,r5,1
	cmp	r6,1
	uxtb	r5,r5
	beq	.L5828
.L5797:
	movs	r2,r6
	moveq	r3,241
	moveq	r1,r6
	moveq	r0,123
.L7746:

	bleq	Det_ReportRuntimeError
.LDW57:
.L7748:

	pop	{r4-r10,pc}
__ghs_eofn_Adc_Init::
	.endf	Adc_Init
;Cnt	r0	local
;HWUnitIdx	r5	local
;KernelPtr	r8	local
;CoreId	r4	local
;Err	r0	local
;OperationRslt	r6	local

;ConfigPtr	r7	param

	.section ".ghcalltbl",""
.L7725:	.data.w	.L7724
	.endo	.L7725
	.section ".ghrettbl",""
.L7727:	.data.w	.L7726
	.endo	.L7727
	.section ".ghcalltbl",""
.L7729:	.data.w	.L7728
	.endo	.L7729
.L7731:	.data.w	.L7730
	.endo	.L7731
.L7733:	.data.w	.L7732
	.endo	.L7733
.L7735:	.data.w	.L7734
	.endo	.L7735
.L7737:	.data.w	.L7736
	.endo	.L7737
.L7739:	.data.w	.L7738
	.endo	.L7739
.L7741:	.data.w	.L7740
	.endo	.L7741
.L7743:	.data.w	.L7742
	.endo	.L7743
.L7745:	.data.w	.L7744
	.endo	.L7745
.L7747:	.data.w	.L7746
	.endo	.L7747
	.section ".ghrettbl",""
.L7749:	.data.w	.L7748
	.endo	.L7749
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_Endinit.v.v

	.global	__caller.Saradc_Hal_MaskResultInterrupt.i.pi

	.global	__caller.Saradc_Hal_MaskResultInterrupt.i.pi

	.global	__caller.Saradc_Hal_InitChannel.i.pip

	.global	__caller.Saradc_Hal_OpenCalibration.i.p

	.global	__caller.SchM_Enter_Adc_Endinit.v.v

	.global	__caller.SchM_Exit_Adc_Endinit.v.v

	.global	__caller.Saradc_Hal_InitModule.i.pp

	.global	__caller.SchM_Enter_Adc_Endinit.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.50:
	.endo	..gh.f.a.1.e.50
__callee.Adc_DeInit.v.v::
	.size	__callee.Adc_DeInit.v.v,0
Adc_DeInit::
.LDW67:
	push	{r4-r6,lr}
.LDW77:
	mov	r5,1
	mov	r0,r5
.L8185:

	bl	Adc_CheckInit
	cmp	r0,0
.L8187:

	popne	{r4-r6,pc}
.L8189:

	bl	Adc_CheckGroupStatusAll
	movs	r6,r0
.L8191:

	popne	{r4-r6,pc}
	b	.L8181

.L7722:	.data.w	Adc_InstanceDataSet
	.endo	.L7722

.L7723:	.data.w	Adc_BaseAddrs
	.endo	.L7723

.L8181:

;line3980
..lin.36296530..51371ae9.0_30::
.LDWlin30:
..gh.beginasm.51:
	.endo	..gh.beginasm.51
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.52:
	.endo	..gh.endasm.52

;line3982
..lin.36296530..51371ae9.0_31::
.LDWlin31:
	b	.L7763
.L7762:
	ldr	r3,[r3,4]
	rsb	r2,r2,r2 lsl 3
	add	r5,r3,r2 lsl 2
	ldr	r3,.L8182
	ldr	r2,[r3,r4 lsl 2]
	ldr	r3,[r0,16]
	ldrb	r0,[r5]
	ldr	r2,[r2,4]
	ldrb	r0,[r3,r0 lsl 1]
	mov	r3,88
	smlabb	r0,r0,r3,r2
	str	r1,[r0,16]
.L8193:

	bl	SchM_Enter_Adc_DeInit
	mov	r0,4
.L8195:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L7764
	ldrb	r0,[r5]
	ldr	r1,.L8183
	ldr	r0,[r1,r0 lsl 2]
.L8197:

	bl	Saradc_Hal_DeInitModule
	and	r5,r0,1
	mov	r0,4
.L8199:

	bl	Mcal_ReleaseLock
	b	.L7766
.L7764:
	mov	r5,0
.L7766:
.L8201:

	bl	SchM_Exit_Adc_DeInit
	add	r6,r6,1<<24
.L7763:
	ldr	r1,.L8184
	ldr	r0,[r1]
	ldr	r3,[r0,r4 lsl 2]
	mov	r1,0
	lsr	r2,r6,24
	ldrb	r12,[r3]
	cmp	r2,r12
	bhs	.L7760
	cmp	r5,1
	beq	.L7762
.L7760:
	cmp	r5,0
	bne	.L7768
	mov	r3,241
	mov	r2,1
	mov	r0,123
.L8203:

	bl	Det_ReportRuntimeError
.L8205:

	pop	{r4-r6,pc}
.L7768:
	ldr	r0,.L8182
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0]
	strb	r1,[r0]
.LDW87:
.L8207:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_DeInit::
	.endf	Adc_DeInit
;DataPtr	r0	local
;OperationRslt	r5	local
;KernelPtr	r5	local
;CoreId	r4	local

	.section ".ghcalltbl",""
.L8186:	.data.w	.L8185
	.endo	.L8186
	.section ".ghrettbl",""
.L8188:	.data.w	.L8187
	.endo	.L8188
	.section ".ghcalltbl",""
.L8190:	.data.w	.L8189
	.endo	.L8190
	.section ".ghrettbl",""
.L8192:	.data.w	.L8191
	.endo	.L8192
	.section ".ghcalltbl",""
.L8194:	.data.w	.L8193
	.endo	.L8194
.L8196:	.data.w	.L8195
	.endo	.L8196
.L8198:	.data.w	.L8197
	.endo	.L8198
.L8200:	.data.w	.L8199
	.endo	.L8200
.L8202:	.data.w	.L8201
	.endo	.L8202
.L8204:	.data.w	.L8203
	.endo	.L8204
	.section ".ghrettbl",""
.L8206:	.data.w	.L8205
	.endo	.L8206
.L8208:	.data.w	.L8207
	.endo	.L8208
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_DeInit.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Saradc_Hal_DeInitModule.i.p

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Adc_DeInit.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.53:
	.endo	..gh.f.a.1.e.53
__callee.Adc_SetupResultBuffer.i.ip::
	.size	__callee.Adc_SetupResultBuffer.i.ip,0
Adc_SetupResultBuffer::
.LDW97:
	push	{r4-r8,lr}
	mov	r8,r1
.LDW08:
	ubfx	r5,r0,5,4
	and	r7,r0,31
	mov	r0,12
.L8575:

	bl	Adc_CheckInit
	subs	r4,r0,0
	bne	.L8211
	b	.L8572

.L8182:	.data.w	Adc_InstanceDataSet
	.endo	.L8182

.L8183:	.data.w	Adc_BaseAddrs
	.endo	.L8183

.L8184:	.data.w	Adc_ConfigPtr
	.endo	.L8184

.L8572:

;line4103
..lin.36296530..326dfe96.0_32::
.LDWlin32:
..gh.beginasm.54:
	.endo	..gh.beginasm.54
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.55:
	.endo	..gh.endasm.55

	mov	r6,r0
;line4107
..lin.36296530..326dfe96.0_33::
.LDWlin33:
	mov	r1,r5
	mov	r0,12
.L8577:

	bl	Adc_CheckMulticoreAllocateError
	subs	r4,r0,0
	bne	.L8211
	mov	r2,r5
	mov	r1,r7
	mov	r0,12
.L8579:

	bl	Adc_CommDetCheck
	subs	r4,r0,0
	bne	.L8211
	cmp	r8,0
	ldrne	r0,.L8573
	ldrne	r2,[r0]
	ldrne	r0,[r2,16]
	ldrne	r2,[r2,r6 lsl 2]
	ldrbne	r0,[r0,r5 lsl 1]
	ldrne	r2,[r2,4]
	rsbne	r1,r0,r0 lsl 3
	mov	r3,20
	addne	r1,r2,r1 lsl 2
	ldrbne	r1,[r1,1]
	movne	r3,32
	cmpne	r1,2
	bne	.L8227
	mov	r2,12
	mov	r1,0
	mov	r0,123
.L8581:

	bl	Det_ReportError
	mov	r4,1
	b	.L8211
.L8227:
	ldr	r1,.L8574
	ldr	r1,[r1,r6 lsl 2]
	ldr	r1,[r1,4]
	mov	r2,88
	smlabb	r0,r0,r2,r1
	ldr	r1,[r0,4]
	lsr	r1,r1,r7
	tst	r1,1
	ldreq	r2,[r0]
	moveq	r4,0
	movne	r4,1
	movne	r3,11
	movne	r2,12
	ldreq	r0,[r0,84]
	movne	r1,0
	movne	r0,123
	streq	r8,[r2,r7 lsl 2]
	strbeq	r4,[r0,r7]
.L8583:

	blne	Det_ReportRuntimeError
.L8211:
	mov	r0,r4
.LDW18:
.L8585:

	pop	{r4-r8,pc}
__ghs_eofn_Adc_SetupResultBuffer::
	.endf	Adc_SetupResultBuffer
;GroupId	r7	local
;RetStatus	r4	local
;PhyHwUnitId	r5	local
;CoreId	r6	local
;DataPtr	r0	local

;Group	r0	param
;DataBufferPtr	r8	param

	.section ".ghcalltbl",""
.L8576:	.data.w	.L8575
	.endo	.L8576
.L8578:	.data.w	.L8577
	.endo	.L8578
.L8580:	.data.w	.L8579
	.endo	.L8580
.L8582:	.data.w	.L8581
	.endo	.L8582
.L8584:	.data.w	.L8583
	.endo	.L8584
	.section ".ghrettbl",""
.L8586:	.data.w	.L8585
	.endo	.L8586
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.56:
	.endo	..gh.f.a.1.e.56
__callee.Adc_StartGroupConversion.v.i::
	.size	__callee.Adc_StartGroupConversion.v.i,0
Adc_StartGroupConversion::
.LDW28:
	push	{r4-r10,lr}
.LDW38:
	mov	r6,1
	ubfx	r5,r0,5,4
	and	r4,r0,31
	mov	r0,2
.L8907:

	bl	Adc_CheckInit
	cmp	r0,0
.L8909:

	popne	{r4-r10,pc}
	mov	r1,r5
	mov	r0,2
.L8911:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
.L8913:

	popne	{r4-r10,pc}
	mov	r2,r5
	mov	r1,r4
	mov	r0,2
.L8915:

	bl	Adc_CommDetCheck
	cmp	r0,0
.L8917:

	popne	{r4-r10,pc}
.L8919:

	bl	SchM_Enter_Adc_StartGroup
	mov	r1,r5
	mov	r0,r4
.L8921:

	bl	Adc_CheckStateForStartGroup
	mov	r7,r0
.L8923:

	bl	SchM_Exit_Adc_StartGroup
	mov	r3,11
	cmp	r7,0
	bne	.L8656
	b	.L8904

.L8573:	.data.w	Adc_ConfigPtr
	.endo	.L8573

.L8574:	.data.w	Adc_InstanceDataSet
	.endo	.L8574

.L8904:

;line4265
..lin.36296530..4ec74a0d.0_34::
.LDWlin34:
..gh.beginasm.57:
	.endo	..gh.beginasm.57
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.58:
	.endo	..gh.endasm.58

;line4270
..lin.36296530..4ec74a0d.0_35::
.LDWlin35:
	ldr	r1,.L8905
	ldr	r3,[r1]
	ldr	r1,[r3,16]
	ldr	r3,[r3,r0 lsl 2]
	ldrb	r1,[r1,r5 lsl 1]
	ldr	r3,[r3,4]
	rsb	r2,r1,r1 lsl 3
	add	r8,r3,r2 lsl 2
	ldr	r3,[r8,20]
	mov	r2,44
	mla	r9,r4,r2,r3
	ldr	r2,.L8906
	ldr	r0,[r2,r0 lsl 2]
	ldr	r0,[r0,4]
	mov	r2,88
	ldr	r10,[r9,28]
	smlabb	r7,r1,r2,r0
.L8925:

	bl	SchM_Enter_Adc_StartGroup
	ldr	r0,[r7,4]
	lsl	r1,r6,r4
	mvn	r2,r1
	bic	r0,r0,r1
	orr	r0,r1,r0
	ldr	r1,[r7,8]
	str	r0,[r7,4]
	and	r1,r1,r2
	str	r1,[r7,8]
	ldr	r1,[r7,12]
	add	r0,r7,r10 lsl 2
	strh	r4,[r0,20]
	and	r1,r1,r2
	str	r1,[r7,12]
	ldr	r1,[r7,84]
	mov	r2,r9
	mov	r3,0
	strb	r3,[r1,r4]
	mov	r1,r8
	strb	r3,[r0,23]
	mov	r0,r5
.L8927:

	bl	Adc_StartConversion
	and	r6,r6,r0
.L8929:

	bl	SchM_Exit_Adc_StartGroup
	mov	r3,241
	cmp	r6,0
.L8931:

	popne	{r4-r10,pc}
.L8656:
	mov	r2,2
	mov	r1,0
	mov	r0,123
.L8933:

	bl	Det_ReportRuntimeError
.LDW48:
.L8935:

	pop	{r4-r10,pc}
__ghs_eofn_Adc_StartGroupConversion::
	.endf	Adc_StartGroupConversion
;AdcKernelPtr	r8	local
;GroupId	r4	local
;PhyHwUnitId	r5	local
;DataPtr	r7	local
;GrpPtr	r9	local
;GrpRequestSource	r10	local
;Err	r7	local
;OperationRslt	r6	local

;Group	r0	param

	.section ".ghcalltbl",""
.L8908:	.data.w	.L8907
	.endo	.L8908
	.section ".ghrettbl",""
.L8910:	.data.w	.L8909
	.endo	.L8910
	.section ".ghcalltbl",""
.L8912:	.data.w	.L8911
	.endo	.L8912
	.section ".ghrettbl",""
.L8914:	.data.w	.L8913
	.endo	.L8914
	.section ".ghcalltbl",""
.L8916:	.data.w	.L8915
	.endo	.L8916
	.section ".ghrettbl",""
.L8918:	.data.w	.L8917
	.endo	.L8918
	.section ".ghcalltbl",""
.L8920:	.data.w	.L8919
	.endo	.L8920
.L8922:	.data.w	.L8921
	.endo	.L8922
.L8924:	.data.w	.L8923
	.endo	.L8924
.L8926:	.data.w	.L8925
	.endo	.L8926
.L8928:	.data.w	.L8927
	.endo	.L8928
.L8930:	.data.w	.L8929
	.endo	.L8930
	.section ".ghrettbl",""
.L8932:	.data.w	.L8931
	.endo	.L8932
	.section ".ghcalltbl",""
.L8934:	.data.w	.L8933
	.endo	.L8934
	.section ".ghrettbl",""
.L8936:	.data.w	.L8935
	.endo	.L8936
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_StartGroup.v.v

	.global	__caller.SchM_Enter_Adc_StartGroup.v.v

	.global	__caller.SchM_Exit_Adc_StartGroup.v.v

	.global	__caller.SchM_Enter_Adc_StartGroup.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_ConfigPtr - Adc_ConfigPtr) +0 == 0
..gh.f.a.1.e.59:
	.endo	..gh.f.a.1.e.59
__callee.Adc_StopGroupConversion.v.i::
	.size	__callee.Adc_StopGroupConversion.v.i,0
Adc_StopGroupConversion::
.LDW58:
	push	{r2,r4-r9,lr}
.LDW68:
	mov	r6,1
	ubfx	r5,r0,5,4
	and	r8,r0,31
	mov	r2,r5
	mov	r1,r8
	mov	r0,3
.L9288:

	bl	Adc_DetErrorCheck
	cmp	r0,0
.L9290:

	popne	{r2,r4-r9,pc}
	ldr	r9,.L8905
	b	.L9286

.L8905:	.data.w	Adc_ConfigPtr
	.endo	.L8905

.L8906:	.data.w	Adc_InstanceDataSet
	.endo	.L8906

.L9286:

;line4410
..lin.36296530..7b03f7a5.0_36::
.LDWlin36:
..gh.beginasm.60:
	.endo	..gh.beginasm.60
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.61:
	.endo	..gh.endasm.61

	ldr	r1,.L9287
;line4413
..lin.36296530..7b03f7a5.0_37::
.LDWlin37:
	ldr	r1,[r1,r0 lsl 2]
	mov	r4,r0
	ldr	r0,[r9]
	ldr	r0,[r0,16]
	ldr	r1,[r1,4]
	ldrb	r0,[r0,r5 lsl 1]
	mov	r2,88
	smlabb	r7,r0,r2,r1
.L9292:

	bl	SchM_Enter_Adc_StopGroup
	ldr	r0,[r7,4]
	lsr	r0,r0,r8
	tst	r0,1
	ldreq	r0,[r7,8]
	lsreq	r0,r0,r8
	tsteq	r0,1
	beq	.L8945
.L9294:

	bl	SchM_Exit_Adc_StopGroup
	ldr	r0,[r9]
	ldr	r1,[r0,r4 lsl 2]
	ldr	r0,[r0,16]
	ldrb	r0,[r0,r5 lsl 1]
	ldr	r1,[r1,4]
	rsb	r0,r0,r0 lsl 3
	add	r0,r1,r0 lsl 2
	ldr	r0,[r0,20]
	mov	r1,44
	mla	r4,r8,r1,r0
.L9296:

	bl	SchM_Enter_Adc_StopGroup
	ldr	r0,[r7,4]
	lsr	r0,r0,r8
	tst	r0,1
	beq	.L8955
	ldr	r0,[r4,28]
	mov	r9,r6
	add	r0,r7,r0 lsl 2
	mov	r1,r5
	strb	r6,[r0,23]
	mov	r0,r4
.L9298:

	bl	Adc_StopConvRequestSource
	mov	r6,r0
	mov	r1,r7
	mov	r0,r4
.L9300:

	bl	Adc_ResetTrigSrcData
	ldr	r0,[r7,4]
	lsl	r1,r9,r8
	bic	r0,r0,r1
	str	r0,[r7,4]
.L8955:
	mov	r0,1
	add	r12,r7,8
	mvn	r0,r0 lsl r8
	ldm	r12,{r1-r3}
	and	r1,r1,r0
	and	r2,r2,r0
	and	r8,r3,r0
	stm	r12,{r1-r2,r8}
.L9302:

	bl	SchM_Exit_Adc_StopGroup
	cmp	r6,0
	moveq	r3,241
	beq	.L9008
.L9304:

	pop	{r2,r4-r9,pc}
.L8945:
.L9306:

	bl	SchM_Exit_Adc_StopGroup
	mov	r3,12
.L9008:
	mov	r2,3
	mov	r1,0
	mov	r0,123
.L9308:

	bl	Det_ReportRuntimeError
.LDW78:
.L9310:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Adc_StopGroupConversion::
	.endf	Adc_StopGroupConversion
;DataPtr	r7	local
;GrpPtr	r4	local
;GroupId	r8	local
;PhyHwUnitId	r5	local
;CoreId	r4	local
;OperationRslt	r6	local

;Group	r0	param

	.section ".ghcalltbl",""
.L9289:	.data.w	.L9288
	.endo	.L9289
	.section ".ghrettbl",""
.L9291:	.data.w	.L9290
	.endo	.L9291
	.section ".ghcalltbl",""
.L9293:	.data.w	.L9292
	.endo	.L9293
.L9295:	.data.w	.L9294
	.endo	.L9295
.L9297:	.data.w	.L9296
	.endo	.L9297
.L9299:	.data.w	.L9298
	.endo	.L9299
.L9301:	.data.w	.L9300
	.endo	.L9301
.L9303:	.data.w	.L9302
	.endo	.L9303
	.section ".ghrettbl",""
.L9305:	.data.w	.L9304
	.endo	.L9305
	.section ".ghcalltbl",""
.L9307:	.data.w	.L9306
	.endo	.L9307
.L9309:	.data.w	.L9308
	.endo	.L9309
	.section ".ghrettbl",""
.L9311:	.data.w	.L9310
	.endo	.L9311
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_StopGroup.v.v

	.global	__caller.SchM_Exit_Adc_StopGroup.v.v

	.global	__caller.SchM_Enter_Adc_StopGroup.v.v

	.global	__caller.SchM_Exit_Adc_StopGroup.v.v

	.global	__caller.SchM_Enter_Adc_StopGroup.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_ConfigPtr - Adc_ConfigPtr) +0 == 0
..gh.f.a.1.e.62:
	.endo	..gh.f.a.1.e.62
__callee.Adc_ReadGroup.i.ip::
	.size	__callee.Adc_ReadGroup.i.ip,0
Adc_ReadGroup::
.LDW88:
	push	{r2,r4-fp,lr}
	mov	r5,r1
.LDW98:
	ubfx	r6,r0,5,4
	and	r7,r0,31
	mov	r2,r1
	b	.L9721

.L9287:	.data.w	Adc_InstanceDataSet
	.endo	.L9287

.L9721:

;line4592
..lin.36296530..652275f5.0_38::
.LDWlin38:
..gh.beginasm.63:
	.endo	..gh.beginasm.63
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.64:
	.endo	..gh.endasm.64

	mov	r4,r0
;line4595
..lin.36296530..652275f5.0_39::
.LDWlin39:
	mov	r1,r6
	mov	r0,r7
.L9724:

	bl	Adc_ReadGroupDetCheck
	subs	r8,r0,0
	bne	.L9318
.L9726:

	bl	SchM_Enter_Adc_ReadGroup
	mov	r1,r6
	mov	r0,r7
.L9728:

	bl	Adc_CheckDriverState
	mov	r8,r0
.L9730:

	bl	SchM_Exit_Adc_ReadGroup
	cmp	r8,0
	bne	.L9320
	ldr	r8,.L9722
	ldr	r2,[r8]
	ldr	r0,[r2,16]
	ldr	r2,[r2,r4 lsl 2]
	ldrb	r0,[r0,r6 lsl 1]
	ldr	r2,[r2,4]
	rsb	r1,r0,r0 lsl 3
	add	r1,r2,r1 lsl 2
	ldr	r1,[r1,20]
	mov	r2,44
	mla	r9,r7,r2,r1
	ldr	r2,.L9723
	ldr	r1,[r2,r4 lsl 2]
	ldr	r1,[r1,4]
	mov	r2,88
	smlabb	r10,r0,r2,r1
.L9732:

	bl	SchM_Enter_Adc_ReadGroup
	ldmib	r10,{r2-r3}
	mov	r0,r3
	lsr	r2,r2,r7
	lsr	r1,r0,r7
	tst	r2,1
	and	r1,r1,1
	beq	.L9328
	cmp	r1,0
	bne	.L9328
.L9734:

	bl	SchM_Exit_Adc_ReadGroup
	mov	r8,1
	b	.L9318
.L9328:
	mov	r1,1
	mvn	r1,r1 lsl r7
	and	r0,r1,r0
	str	r0,[r10,8]
	ldr	r0,[r10,12]
	and	r0,r0,r1
	ldr	r1,[r10]
	str	r0,[r10,12]
	ldr	r0,[r10,84]
	ldr	r1,[r1,r7 lsl 2]
	ldrb	r0,[r0,r7]
	ldr	r7,[r9,8]
	ldrb	r12,[r9,1]
	ldrb	r2,[r7]
	add	r0,r1,r0 lsl 1
	mov	r1,r5
	sub	r3,r0,2
	smulbb	r10,r12,r2
	b	.L9332
.L9334:
	ldr	r5,[r8]
	ldrh	r0,[r3]
	ldr	r5,[r5,r4 lsl 2]
	strh	r0,[r1]
	ldr	r5,[r5,4]
	rsb	r0,r6,r6 lsl 3
	add	r0,r5,r0 lsl 2
	ldr	r5,[r0,8]
	cmp	r5,0
	beq	.L9335
	ldrb	r0,[r9]
	cmp	r0,1
	bne	.L9335
	b	.L9341
.L9340:
	mul	lr,r0,r10
	ldrb	fp,[r7]
	lsl	lr,lr,1
	smulbb	fp,r0,fp
	ldrh	lr,[lr,r3]
	add	r0,r0,1
	lsl	fp,fp,1
	uxtb	r0,r0
	strh	lr,[fp,r1]
.L9341:
	ldrb	fp,[r5]
	cmp	r0,fp
	bls	.L9340
.L9335:
	sub	r2,r2,1
	add	r1,r1,2
	add	r3,r3,r12 lsl 1
	uxtb	r2,r2
.L9332:
	cmp	r2,0
	bne	.L9334
.L9736:

	bl	SchM_Exit_Adc_ReadGroup
	mov	r8,0
	b	.L9318
.L9320:
	mov	r3,12
	mov	r2,4
	mov	r1,0
	mov	r0,123
.L9738:

	bl	Det_ReportRuntimeError
.L9318:
	mov	r0,r8
.LDW09:
.L9740:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Adc_ReadGroup::
	.endf	Adc_ReadGroup
;NoOfChannels	r2	local
;GroupId	r7	local
;RetStatus	r8	local
;StreamNumOfSamples	r12	local
;GrpRes	r1	local
;PhyHwUnitId	r6	local
;CoreId	r4	local
;HwUnitCnt	r0	local
;SyncGrpSlaveRsltStartPos	r10	local
;DataPtr	r10	local
;GrpPtr	r9	local
;CurrentResBufPtr	r3	local
;TargetDataBufPtr	r1	local

;Group	r0	param
;DataBufferPtr	r5	param

	.section ".ghcalltbl",""
.L9725:	.data.w	.L9724
	.endo	.L9725
.L9727:	.data.w	.L9726
	.endo	.L9727
.L9729:	.data.w	.L9728
	.endo	.L9729
.L9731:	.data.w	.L9730
	.endo	.L9731
.L9733:	.data.w	.L9732
	.endo	.L9733
.L9735:	.data.w	.L9734
	.endo	.L9735
.L9737:	.data.w	.L9736
	.endo	.L9737
.L9739:	.data.w	.L9738
	.endo	.L9739
	.section ".ghrettbl",""
.L9741:	.data.w	.L9740
	.endo	.L9741
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_ReadGroup.v.v

	.global	__caller.SchM_Exit_Adc_ReadGroup.v.v

	.global	__caller.SchM_Enter_Adc_ReadGroup.v.v

	.global	__caller.SchM_Exit_Adc_ReadGroup.v.v

	.global	__caller.SchM_Enter_Adc_ReadGroup.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.65:
	.endo	..gh.f.a.1.e.65
__callee.Adc_EnableHardwareTrigger.v.i::
	.size	__callee.Adc_EnableHardwareTrigger.v.i,0
Adc_EnableHardwareTrigger::
.LDW19:
	push	{r4-r8,lr}
.LDW29:
	ubfx	r5,r0,5,4
	and	r6,r0,31
	mov	r0,5
.L10059:

	bl	Adc_CheckInit
	cmp	r0,0
.L10061:

	popne	{r4-r8,pc}
	mov	r1,r5
	mov	r0,5
.L10063:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
.L10065:

	popne	{r4-r8,pc}
	mov	r2,r5
	mov	r1,r6
	mov	r0,5
.L10067:

	bl	Adc_CommDetCheck
	cmp	r0,0
.L10069:

	popne	{r4-r8,pc}
.L10071:

	bl	SchM_Enter_Adc_EnableHwTrig
	mov	r1,r5
	mov	r0,r6
.L10073:

	bl	Adc_CheckStateForEnableGroup
	mov	r4,r0
.L10075:

	bl	SchM_Exit_Adc_EnableHwTrig
	mov	r3,11
	cmp	r4,0
	bne	.L9808
	b	.L10056

.L9722:	.data.w	Adc_ConfigPtr
	.endo	.L9722

.L9723:	.data.w	Adc_InstanceDataSet
	.endo	.L9723

.L10056:

;line4804
..lin.36296530..87d7a435.0_40::
.LDWlin40:
..gh.beginasm.66:
	.endo	..gh.beginasm.66
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.67:
	.endo	..gh.endasm.67

;line4808
..lin.36296530..87d7a435.0_41::
.LDWlin41:
	ldr	r1,.L10057
	ldr	r3,[r1]
	ldr	r1,[r3,16]
	ldr	r3,[r3,r0 lsl 2]
	ldrb	r1,[r1,r5 lsl 1]
	ldr	r3,[r3,4]
	rsb	r2,r1,r1 lsl 3
	add	r7,r3,r2 lsl 2
	ldr	r3,[r7,20]
	mov	r2,44
	mla	r4,r6,r2,r3
	ldr	r2,.L10058
	ldr	r0,[r2,r0 lsl 2]
	ldr	r0,[r0,4]
	mov	r2,88
	smlabb	r8,r1,r2,r0
.L10077:

	bl	SchM_Enter_Adc_EnableHwTrig
	mov	r3,1
	lsl	r0,r3,r6
	ldmib	r8,{r1-r2,r12}
	bic	r1,r1,r0
	orr	r1,r0,r1
	str	r1,[r8,4]
	mvn	r1,r0
	and	r0,r2,r1
	str	r0,[r8,8]
	and	r0,r12,r1
	ldr	r1,[r8,84]
	str	r0,[r8,12]
	mov	r0,0
	strb	r0,[r1,r6]
	ldrb	r1,[r4,28]
	mov	r2,r4
	add	r1,r8,r1 lsl 2
	strb	r0,[r1,23]
	mov	r0,r5
	strh	r6,[r1,20]
	mov	r1,r7
.L10079:

	bl	Adc_StartConversion
	mov	r4,r0
.L10081:

	bl	SchM_Exit_Adc_EnableHwTrig
	mov	r3,241
	cmp	r4,0
.L10083:

	popne	{r4-r8,pc}
.L9808:
	mov	r2,5
	mov	r1,0
	mov	r0,123
.L10085:

	bl	Det_ReportRuntimeError
.LDW39:
.L10087:

	pop	{r4-r8,pc}
__ghs_eofn_Adc_EnableHardwareTrigger::
	.endf	Adc_EnableHardwareTrigger
;DataPtr	r8	local
;GrpPtr	r4	local
;GroupId	r6	local
;GrpRequestSource	r1	local
;PhyHwUnitId	r5	local
;Err	r4	local
;OperationRslt	r4	local

;Group	r0	param

	.section ".ghcalltbl",""
.L10060:	.data.w	.L10059
	.endo	.L10060
	.section ".ghrettbl",""
.L10062:	.data.w	.L10061
	.endo	.L10062
	.section ".ghcalltbl",""
.L10064:	.data.w	.L10063
	.endo	.L10064
	.section ".ghrettbl",""
.L10066:	.data.w	.L10065
	.endo	.L10066
	.section ".ghcalltbl",""
.L10068:	.data.w	.L10067
	.endo	.L10068
	.section ".ghrettbl",""
.L10070:	.data.w	.L10069
	.endo	.L10070
	.section ".ghcalltbl",""
.L10072:	.data.w	.L10071
	.endo	.L10072
.L10074:	.data.w	.L10073
	.endo	.L10074
.L10076:	.data.w	.L10075
	.endo	.L10076
.L10078:	.data.w	.L10077
	.endo	.L10078
.L10080:	.data.w	.L10079
	.endo	.L10080
.L10082:	.data.w	.L10081
	.endo	.L10082
	.section ".ghrettbl",""
.L10084:	.data.w	.L10083
	.endo	.L10084
	.section ".ghcalltbl",""
.L10086:	.data.w	.L10085
	.endo	.L10086
	.section ".ghrettbl",""
.L10088:	.data.w	.L10087
	.endo	.L10088
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_EnableHwTrig.v.v

	.global	__caller.SchM_Enter_Adc_EnableHwTrig.v.v

	.global	__caller.SchM_Exit_Adc_EnableHwTrig.v.v

	.global	__caller.SchM_Enter_Adc_EnableHwTrig.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.68:
	.endo	..gh.f.a.1.e.68
__callee.Adc_DisableHardwareTrigger.v.i::
	.size	__callee.Adc_DisableHardwareTrigger.v.i,0
Adc_DisableHardwareTrigger::
.LDW49:
	push	{r2,r4-r7,lr}
.LDW59:
	ubfx	r7,r0,5,4
	and	r5,r0,31
	mov	r2,r7
	mov	r1,r5
	mov	r0,6
.L10367:

	bl	Adc_DetErrorCheck
	cmp	r0,0
.L10369:

	popne	{r2,r4-r7,pc}
	b	.L10364

.L10057:	.data.w	Adc_ConfigPtr
	.endo	.L10057

.L10058:	.data.w	Adc_InstanceDataSet
	.endo	.L10058

.L10364:

;line4943
..lin.36296530..ed8c5e82.0_42::
.LDWlin42:
..gh.beginasm.69:
	.endo	..gh.beginasm.69
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.70:
	.endo	..gh.endasm.70

	ldr	r1,.L10365
;line4946
..lin.36296530..ed8c5e82.0_43::
.LDWlin43:
	ldr	r2,.L10366
	ldr	r1,[r1,r0 lsl 2]
	mov	r4,r0
	ldr	r0,[r2]
	ldr	r0,[r0,16]
	ldr	r1,[r1,4]
	ldrb	r0,[r0,r7 lsl 1]
	mov	r2,88
	smlabb	r6,r0,r2,r1
.L10371:

	bl	SchM_Enter_Adc_DisableHwTrig
	ldr	r0,[r6,4]
	lsr	r0,r0,r5
	tst	r0,1
	ldreq	r0,[r6,8]
	lsreq	r0,r0,r5
	tsteq	r0,1
	beq	.L10097
.L10373:

	bl	SchM_Exit_Adc_DisableHwTrig
	mov	r3,r4
	mov	r2,r6
	mov	r1,r7
	mov	r0,r5
.L10375:

	bl	Adc_LocalDisableHardwareTrigger
	cmp	r0,0
	moveq	r3,241
	beq	.L10138
.L10377:

	pop	{r2,r4-r7,pc}
.L10097:
.L10379:

	bl	SchM_Exit_Adc_DisableHwTrig
	mov	r3,12
.L10138:
	mov	r2,6
	mov	r1,0
	mov	r0,123
.L10381:

	bl	Det_ReportRuntimeError
.LDW69:
.L10383:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Adc_DisableHardwareTrigger::
	.endf	Adc_DisableHardwareTrigger
;DataPtr	r6	local
;GroupId	r5	local
;PhyHwUnitId	r7	local
;CoreId	r4	local
;Err	r0	local

;Group	r0	param

	.section ".ghcalltbl",""
.L10368:	.data.w	.L10367
	.endo	.L10368
	.section ".ghrettbl",""
.L10370:	.data.w	.L10369
	.endo	.L10370
	.section ".ghcalltbl",""
.L10372:	.data.w	.L10371
	.endo	.L10372
.L10374:	.data.w	.L10373
	.endo	.L10374
.L10376:	.data.w	.L10375
	.endo	.L10376
	.section ".ghrettbl",""
.L10378:	.data.w	.L10377
	.endo	.L10378
	.section ".ghcalltbl",""
.L10380:	.data.w	.L10379
	.endo	.L10380
.L10382:	.data.w	.L10381
	.endo	.L10382
	.section ".ghrettbl",""
.L10384:	.data.w	.L10383
	.endo	.L10384
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_DisableHwTrig.v.v

	.global	__caller.SchM_Exit_Adc_DisableHwTrig.v.v

	.global	__caller.SchM_Enter_Adc_DisableHwTrig.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.71:
	.endo	..gh.f.a.1.e.71
__callee.Adc_EnableGroupNotification.v.i::
	.size	__callee.Adc_EnableGroupNotification.v.i,0
Adc_EnableGroupNotification::
.LDW79:
	push	{r2,r4-r5,lr}
.LDW89:
	ubfx	r4,r0,5,4
	and	r5,r0,31
	mov	r0,7
.L10602:

	bl	Adc_CheckInit
	cmp	r0,0
.L10604:

	popne	{r2,r4-r5,pc}
	mov	r1,r4
	mov	r0,7
.L10606:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
.L10608:

	popne	{r2,r4-r5,pc}
	mov	r2,r4
	mov	r1,r5
	mov	r0,7
.L10610:

	bl	Adc_CommDetCheck
	cmp	r0,0
.L10612:

	popne	{r2,r4-r5,pc}
	b	.L10599

.L10365:	.data.w	Adc_InstanceDataSet
	.endo	.L10365

.L10366:	.data.w	Adc_ConfigPtr
	.endo	.L10366

.L10599:

;line5053
..lin.36296530..6eb21967.0_44::
.LDWlin44:
..gh.beginasm.72:
	.endo	..gh.beginasm.72
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.73:
	.endo	..gh.endasm.73

;line5056
..lin.36296530..6eb21967.0_45::
.LDWlin45:
	ldr	r1,.L10600
	ldr	r2,.L10601
	ldr	r0,[r1,r0 lsl 2]
	ldr	r1,[r2]
	ldr	r1,[r1,16]
	ldr	r0,[r0,4]
	ldrb	r1,[r1,r4 lsl 1]
	mov	r2,88
	smlabb	r4,r1,r2,r0
.L10614:

	bl	SchM_Enter_Adc_EnableGroupNotification
	mov	r0,1
	lsl	r1,r0,r5
	ldr	r0,[r4,16]
	bic	r0,r0,r1
	orr	r0,r1,r0
	str	r0,[r4,16]
.L10616:

	bl	SchM_Exit_Adc_EnableGroupNotification
.LDW99:
.L10618:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_EnableGroupNotification::
	.endf	Adc_EnableGroupNotification
;DataPtr	r4	local
;GroupId	r5	local
;HwUnitId	r4	local
;Err	r0	local

;Group	r0	param

	.section ".ghcalltbl",""
.L10603:	.data.w	.L10602
	.endo	.L10603
	.section ".ghrettbl",""
.L10605:	.data.w	.L10604
	.endo	.L10605
	.section ".ghcalltbl",""
.L10607:	.data.w	.L10606
	.endo	.L10607
	.section ".ghrettbl",""
.L10609:	.data.w	.L10608
	.endo	.L10609
	.section ".ghcalltbl",""
.L10611:	.data.w	.L10610
	.endo	.L10611
	.section ".ghrettbl",""
.L10613:	.data.w	.L10612
	.endo	.L10613
	.section ".ghcalltbl",""
.L10615:	.data.w	.L10614
	.endo	.L10615
.L10617:	.data.w	.L10616
	.endo	.L10617
	.section ".ghrettbl",""
.L10619:	.data.w	.L10618
	.endo	.L10619
	.data
	.global	__caller.SchM_Exit_Adc_EnableGroupNotification.v.v

	.global	__caller.SchM_Enter_Adc_EnableGroupNotification.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.74:
	.endo	..gh.f.a.1.e.74
__callee.Adc_DisableGroupNotification.v.i::
	.size	__callee.Adc_DisableGroupNotification.v.i,0
Adc_DisableGroupNotification::
.LDW001:
	push	{r2,r4-r5,lr}
.LDW101:
	ubfx	r4,r0,5,4
	and	r5,r0,31
	mov	r0,8
.L10842:

	bl	Adc_CheckInit
	cmp	r0,0
.L10844:

	popne	{r2,r4-r5,pc}
	mov	r1,r4
	mov	r0,8
.L10846:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
.L10848:

	popne	{r2,r4-r5,pc}
	mov	r2,r4
	mov	r1,r5
	mov	r0,8
.L10850:

	bl	Adc_CommDetCheck
	cmp	r0,0
.L10852:

	popne	{r2,r4-r5,pc}
	b	.L10839

.L10600:	.data.w	Adc_InstanceDataSet
	.endo	.L10600

.L10601:	.data.w	Adc_ConfigPtr
	.endo	.L10601

.L10839:

;line5143
..lin.36296530..147e9af4.0_46::
.LDWlin46:
..gh.beginasm.75:
	.endo	..gh.beginasm.75
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.76:
	.endo	..gh.endasm.76

;line5146
..lin.36296530..147e9af4.0_47::
.LDWlin47:
	ldr	r1,.L10840
	ldr	r2,.L10841
	ldr	r0,[r1,r0 lsl 2]
	ldr	r1,[r2]
	ldr	r1,[r1,16]
	ldr	r0,[r0,4]
	ldrb	r1,[r1,r4 lsl 1]
	mov	r2,88
	smlabb	r4,r1,r2,r0
.L10854:

	bl	SchM_Enter_Adc_DisableGroupNotification
	mov	r0,1
	lsl	r1,r0,r5
	ldr	r0,[r4,16]
	bic	r0,r0,r1
	str	r0,[r4,16]
.L10856:

	bl	SchM_Exit_Adc_DisableGroupNotification
.LDW201:
.L10858:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_DisableGroupNotification::
	.endf	Adc_DisableGroupNotification
;DataPtr	r4	local
;GroupId	r5	local
;PhyHwUnitId	r4	local
;Err	r0	local

;Group	r0	param

	.section ".ghcalltbl",""
.L10843:	.data.w	.L10842
	.endo	.L10843
	.section ".ghrettbl",""
.L10845:	.data.w	.L10844
	.endo	.L10845
	.section ".ghcalltbl",""
.L10847:	.data.w	.L10846
	.endo	.L10847
	.section ".ghrettbl",""
.L10849:	.data.w	.L10848
	.endo	.L10849
	.section ".ghcalltbl",""
.L10851:	.data.w	.L10850
	.endo	.L10851
	.section ".ghrettbl",""
.L10853:	.data.w	.L10852
	.endo	.L10853
	.section ".ghcalltbl",""
.L10855:	.data.w	.L10854
	.endo	.L10855
.L10857:	.data.w	.L10856
	.endo	.L10857
	.section ".ghrettbl",""
.L10859:	.data.w	.L10858
	.endo	.L10859
	.data
	.global	__caller.SchM_Exit_Adc_DisableGroupNotification.v.v

	.global	__caller.SchM_Enter_Adc_DisableGroupNotification.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.77:
	.endo	..gh.f.a.1.e.77
__callee.Adc_GetGroupStatus.i.i::
	.size	__callee.Adc_GetGroupStatus.i.i,0
Adc_GetGroupStatus::
.LDW301:
	push	{r4-r6,lr}
.LDW401:
	mov	r4,0
	ubfx	r5,r0,5,4
	and	r6,r0,31
	mov	r0,9
.L11408:

	bl	Adc_CheckInit
	cmp	r0,0
	bne	.L10862
	mov	r1,r5
	mov	r0,9
.L11410:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
	bne	.L10862
	mov	r2,r5
	mov	r1,r6
	mov	r0,9
.L11412:

	bl	Adc_CommDetCheck
	cmp	r0,0
	bne	.L10862
	b	.L11405

.L10840:	.data.w	Adc_InstanceDataSet
	.endo	.L10840

.L10841:	.data.w	Adc_ConfigPtr
	.endo	.L10841

.L11405:

;line5244
..lin.36296530..29fdebfd.0_48::
.LDWlin48:
..gh.beginasm.78:
	.endo	..gh.beginasm.78
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.79:
	.endo	..gh.endasm.79

;line5247
..lin.36296530..29fdebfd.0_49::
.LDWlin49:
	ldr	r1,.L11406
	ldr	r12,.L11407
	ldr	r2,[r1]
	ldr	r3,[r12,r0 lsl 2]
	ldr	r1,[r2,16]
	ldr	r3,[r3,4]
	ldrb	r1,[r1,r5 lsl 1]
	ldr	r2,[r2,r0 lsl 2]
	mov	r12,88
	rsb	r0,r1,r1 lsl 3
	smlabb	r4,r1,r12,r3
	ldr	r1,[r2,4]
	add	r2,r1,r0 lsl 2
	ldrb	r0,[r2,1]
	cmp	r0,1
	ldrbne	r0,[r2,26]
	cmpne	r0,0
	bne	.L10878
	ldr	r1,[r2,20]
	mov	r0,44
	mla	r0,r6,r0,r1
	mov	r3,r4
	ldr	r1,[r0,28]
	mov	r0,r5
.L11414:

	bl	Adc_IsrEventHandler
	movs	r1,r0
	moveq	r3,241
	moveq	r2,9
	moveq	r0,123
.L11416:

	bleq	Det_ReportRuntimeError
.L10878:
.L11418:

	bl	SchM_Enter_Adc_GetGrpStatus
	ldr	r0,[r4,12]
	lsr	r0,r0,r6
	tst	r0,1
	movne	r4,3
	bne	.L10884
	ldr	r0,[r4,8]
	lsr	r0,r0,r6
	tst	r0,1
	ldreq	r0,[r4,4]
	movne	r4,2
	lsreq	r0,r0,r6
	andeq	r4,r0,1
.L10884:
.L11420:

	bl	SchM_Exit_Adc_GetGrpStatus
.L10862:
	mov	r0,r4
.LDW501:
.L11422:

	pop	{r4-r6,pc}
__ghs_eofn_Adc_GetGroupStatus::
	.endf	Adc_GetGroupStatus
;HwUnitConfigPtr	r2	local
;DataPtr	r4	local
;GroupId	r6	local
;RetStatus	r4	local
;PhyHwUnitId	r5	local
;Err	r0	local

;Group	r0	param

	.section ".ghcalltbl",""
.L11409:	.data.w	.L11408
	.endo	.L11409
.L11411:	.data.w	.L11410
	.endo	.L11411
.L11413:	.data.w	.L11412
	.endo	.L11413
.L11415:	.data.w	.L11414
	.endo	.L11415
.L11417:	.data.w	.L11416
	.endo	.L11417
.L11419:	.data.w	.L11418
	.endo	.L11419
.L11421:	.data.w	.L11420
	.endo	.L11421
	.section ".ghrettbl",""
.L11423:	.data.w	.L11422
	.endo	.L11423
	.data
	.global	__caller.SchM_Exit_Adc_GetGrpStatus.v.v

	.global	__caller.SchM_Enter_Adc_GetGrpStatus.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Adc_ConfigPtr - Adc_ConfigPtr) +0 == 0
..gh.f.a.1.e.80:
	.endo	..gh.f.a.1.e.80
__callee.Adc_GetStreamLastPointer.i.ip::
	.size	__callee.Adc_GetStreamLastPointer.i.ip,0
Adc_GetStreamLastPointer::
.LDW601:
	push	{r4-r10,lr}
	mov	r6,0
.LDW701:
	mov	r8,r1
	ubfx	r4,r0,5,4
	and	r5,r0,31
	str	r6,[r1]
	b	.L11789

.L11406:	.data.w	Adc_ConfigPtr
	.endo	.L11406

.L11407:	.data.w	Adc_InstanceDataSet
	.endo	.L11407

.L11789:

;line5409
..lin.36296530..8c8fc6ed.0_50::
.LDWlin50:
..gh.beginasm.81:
	.endo	..gh.beginasm.81
 mrc p15, 0, r1, c0, c0, 5
 and r7, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r7, r7, r1         

..gh.endasm.82:
	.endo	..gh.endasm.82

;line5415
..lin.36296530..8c8fc6ed.0_51::
.LDWlin51:
	mov	r2,r4
	mov	r1,r5
	mov	r0,11
.L11792:

	bl	Adc_DetErrorCheck
	cmp	r0,0
	bne	.L11434
	ldr	r9,.L11790
	ldr	r1,[r9]
	ldr	r0,[r1,16]
	ldr	r1,[r1,r7 lsl 2]
	ldrb	r0,[r0,r4 lsl 1]
	ldr	r1,[r1,4]
	rsb	r0,r0,r0 lsl 3
	add	r0,r1,r0 lsl 2
	ldrb	r0,[r0,1]
	cmp	r0,2
	bne	.L11435
	mov	r3,32
	mov	r2,11
	mov	r1,r6
	mov	r0,123
.L11794:

	bl	Det_ReportError
	b	.L11434
.L11435:
.L11796:

	bl	SchM_Enter_Adc_GetStreamLastPtr
	mov	r1,r4
	mov	r0,r5
.L11798:

	bl	Adc_CheckDriverState
	mov	r10,r0
.L11800:

	bl	SchM_Exit_Adc_GetStreamLastPtr
	cmp	r10,0
	bne	.L11436
	ldr	r1,[r9]
	ldr	r0,[r1,16]
	ldr	r2,[r1,r7 lsl 2]
	ldrb	r0,[r0,r4 lsl 1]
	ldr	r2,[r2,4]
	rsb	r1,r0,r0 lsl 3
	add	r1,r2,r1 lsl 2
	ldr	r1,[r1,20]
	mov	r2,44
	mla	r6,r5,r2,r1
	ldr	r1,.L11791
	ldr	r1,[r1,r7 lsl 2]
	ldr	r1,[r1,4]
	mov	r2,88
	smlabb	r9,r0,r2,r1
.L11802:

	bl	SchM_Enter_Adc_GetStreamLastPtr
	ldmib	r9,{r2-r3}
	mov	r0,r3
	lsr	r2,r2,r5
	lsr	r1,r0,r5
	tst	r2,1
	and	r1,r1,1
	beq	.L11438
	cmp	r1,0
	bne	.L11438
.L11804:

	bl	SchM_Exit_Adc_GetStreamLastPtr
	mov	r4,r10
	b	.L11441
.L11438:
	ldr	r2,[r9,12]!
	lsr	r1,r2,r5
	and	r7,r1,1
	mov	r1,1
	mvn	r1,r1 lsl r5
	and	r0,r1,r0
	and	r1,r1,r2
	stmda	r9,{r0-r1}
	ldr	r4,[r9,72]
	ldr	r1,[r9,-12]
	ldrb	r4,[r4,r5]
	ldr	r1,[r1,r5 lsl 2]
	add	r0,r1,r4 lsl 1
	sub	r5,r0,2
.L11806:

	bl	SchM_Exit_Adc_GetStreamLastPtr
	cmp	r7,0
	ldrbne	r4,[r6,1]
	str	r5,[r8]
.L11441:
	mov	r6,r4
	b	.L11434
.L11436:
	mov	r3,12
	mov	r2,11
	mov	r1,r6
	mov	r0,123
.L11808:

	bl	Det_ReportRuntimeError
.L11434:
	mov	r0,r6
.LDW801:
.L11810:

	pop	{r4-r10,pc}
__ghs_eofn_Adc_GetStreamLastPointer::
	.endf	Adc_GetStreamLastPointer
;DataPtr	r9	local
;GrpPtr	r6	local
;BufEndStatus	r7	local
;CurrentResBufPtr	r5	local
;GroupId	r5	local
;NoOfValidConv	r4	local
;RetVal	r6	local
;GrpRes	r1	local
;PhyHwUnitId	r4	local
;CoreId	r7	local
;HwUnitCoreIdx	r0	local
;Err	r10	local

;Group	r0	param
;PtrToSamplePtr	r8	param

	.section ".ghcalltbl",""
.L11793:	.data.w	.L11792
	.endo	.L11793
.L11795:	.data.w	.L11794
	.endo	.L11795
.L11797:	.data.w	.L11796
	.endo	.L11797
.L11799:	.data.w	.L11798
	.endo	.L11799
.L11801:	.data.w	.L11800
	.endo	.L11801
.L11803:	.data.w	.L11802
	.endo	.L11803
.L11805:	.data.w	.L11804
	.endo	.L11805
.L11807:	.data.w	.L11806
	.endo	.L11807
.L11809:	.data.w	.L11808
	.endo	.L11809
	.section ".ghrettbl",""
.L11811:	.data.w	.L11810
	.endo	.L11811
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Adc_GetStreamLastPtr.v.v

	.global	__caller.SchM_Exit_Adc_GetStreamLastPtr.v.v

	.global	__caller.SchM_Enter_Adc_GetStreamLastPtr.v.v

	.global	__caller.SchM_Exit_Adc_GetStreamLastPtr.v.v

	.global	__caller.SchM_Enter_Adc_GetStreamLastPtr.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.83:
	.endo	..gh.f.a.1.e.83
__callee.Adc_GetVersionInfo.v.p::
	.size	__callee.Adc_GetVersionInfo.v.p,0
Adc_GetVersionInfo::
.LDW901:
.LDW011:
	movs	r1,r0
	moveq	r3,20
	moveq	r2,10
	moveq	r0,123
.L11899:

	beq	Det_ReportError
.L11814:
	mov	r1,123
	strh	r1,[r0,2]
	mov	r1,175
	strh	r1,[r0]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW111:
.L11901:

	ret	
__ghs_eofn_Adc_GetVersionInfo::
	.endf	Adc_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L11861:
	.endo	.L11861
	.section ".ghtailcalltbl",""
	.align	4
.L11900:	.data.w	.L11899
	.endo	.L11900
	.section ".ghrettbl",""
.L11902:	.data.w	.L11901
	.endo	.L11902
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.84:
	.endo	..gh.f.a.1.e.84
__callee.Adc_QueueRequest_ISRHandler.v.ii::
	.size	__callee.Adc_QueueRequest_ISRHandler.v.ii,0
Adc_QueueRequest_ISRHandler::
.LDW211:
	push	{r2,r4-r5,lr}
	mov	r4,r0
	mov	r5,r1
.LDW311:
	mov	r0,224
.L12093:

	bl	Adc_CheckInit
	cmp	r0,0
.L12095:

	popne	{r2,r4-r5,pc}
	mov	r1,r4
	mov	r0,224
.L12097:

	bl	Adc_CheckMulticoreAllocateError
	cmp	r0,0
.L12099:

	popne	{r2,r4-r5,pc}
	b	.L12090

.L11790:	.data.w	Adc_ConfigPtr
	.endo	.L11790

.L11791:	.data.w	Adc_InstanceDataSet
	.endo	.L11791

.L12090:

;line5822
..lin.36296530..ed323505.0_52::
.LDWlin52:
..gh.beginasm.85:
	.endo	..gh.beginasm.85
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.86:
	.endo	..gh.endasm.86

;line5831
..lin.36296530..ed323505.0_53::
.LDWlin53:
	ldr	r1,.L12091
	ldr	r3,.L12092
	ldr	r0,[r1]
	ldr	r1,[r3,r2 lsl 2]
	ldr	r12,[r0,16]
	ldr	r0,[r0,r2 lsl 2]
	ldr	r1,[r1,4]
	ldrb	r12,[r12,r4 lsl 1]
	ldr	r0,[r0,4]
	mov	r3,88
	rsb	r2,r12,r12 lsl 3
	smlabb	r3,r12,r3,r1
	mov	r1,r5
	add	r2,r0,r2 lsl 2
	mov	r0,r4
.L12101:

	bl	Adc_IsrEventHandler
	movs	r1,r0
	moveq	r3,241
	moveq	r2,224
	moveq	r0,123
.L12103:

	bleq	Det_ReportRuntimeError
.LDW411:
.L12105:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Adc_QueueRequest_ISRHandler::
	.endf	Adc_QueueRequest_ISRHandler
;Err	r0	local

;PhyHwUnitId	r4	param
;ReqSrc	r5	param

	.section ".ghcalltbl",""
.L12094:	.data.w	.L12093
	.endo	.L12094
	.section ".ghrettbl",""
.L12096:	.data.w	.L12095
	.endo	.L12096
	.section ".ghcalltbl",""
.L12098:	.data.w	.L12097
	.endo	.L12098
	.section ".ghrettbl",""
.L12100:	.data.w	.L12099
	.endo	.L12100
	.section ".ghcalltbl",""
.L12102:	.data.w	.L12101
	.endo	.L12102
.L12104:	.data.w	.L12103
	.endo	.L12104
	.section ".ghrettbl",""
.L12106:	.data.w	.L12105
	.endo	.L12106
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"

.L12091:	.data.w	Adc_ConfigPtr
	.endo	.L12091

.L12092:	.data.w	Adc_InstanceDataSet
	.endo	.L12092

;Adc_InitStatusCore0	Adc_InitStatusCore0	static
;Adc_InstanceDataCore0	Adc_InstanceDataCore0	static
;Adc_GroupResultBufferCore0	Adc_GroupResultBufferCore0	static
;Adc_NumValidConResCore0	Adc_NumValidConResCore0	static
;Adc_InstanceDataSetCore0	Adc_InstanceDataSetCore0	static
;Adc_InitStatusCore1	Adc_InitStatusCore1	static
;Adc_InstanceDataCore1	Adc_InstanceDataCore1	static
;Adc_GroupResultBufferCore1	Adc_GroupResultBufferCore1	static
;Adc_NumValidConResCore1	Adc_NumValidConResCore1	static
;Adc_InstanceDataSetCore1	Adc_InstanceDataSetCore1	static
;Adc_ConfigPtr	Adc_ConfigPtr	static
;Adc_InstanceDataSet	Adc_InstanceDataSet	static
;Adc_BaseAddrs	Adc_BaseAddrs	static
;Adc_BoundDefaultConfig	Adc_BoundDefaultConfig	static
;Adc_ContinuousTimerConfig	Adc_ContinuousTimerConfig	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682570..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	130,100,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,65,100,99,92,115,114,99,47,65,100,99,46,99,0
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
	.data.b	119,20,0,0
	.data.b	2,0
	.data.b	118,6,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,65,100,99,92,115,114,99,47,65,100,99,46,99,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,114,97,100,99,92,105,110,99,92,115,97,114,97,100,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,65,100,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,65,100,99,92,105,110,99,108,117,100,101,92,65,100,99,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,65,100,99,46,104,0
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
	.data.w	.Ldw_begin+2381
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
	.section	.debug_str		;off: 198
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+198
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
	.section	.debug_str		;off: 212
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 50
	.data.w	.Ldw_str_begin+212
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 226
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 57
	.data.w	.Ldw_str_begin+226
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2154
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
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+13267

	.section	.debug_abbrev		;off: 48
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 93
	.data.b	53
	.data.w	.Ldw_begin+14111

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 98
	.data.b	47
	.data.w	.Ldw_begin+93

	.section	.debug_abbrev		;off: 62
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 103
	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 69
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 105
	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14763
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+15742
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+14111

	.data.b	53
	.data.w	.Ldw_begin+177

	.data.b	47
	.data.w	.Ldw_begin+182

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 206
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+17024

	.data.b	53
	.data.w	.Ldw_begin+231

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+17673

	.data.b	53
	.data.w	.Ldw_begin+260

	.data.b	47
	.data.w	.Ldw_begin+265

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+17024

	.data.b	47
	.data.w	.Ldw_begin+17355

	.data.b	53
	.data.w	.Ldw_begin+301

	.data.b	53
	.data.w	.Ldw_begin+16381

	.data.b	47
	.data.w	.Ldw_begin+306

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+316
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+296
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+296

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+380
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+316
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16550
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+17783

	.data.b	53
	.data.w	.Ldw_begin+536

	.data.b	47
	.data.w	.Ldw_begin+541

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+546
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2393
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+16381

	.data.b	53
	.data.w	.Ldw_begin+595

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2393
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+270
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+316
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+316
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+380
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+600
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+296
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2393
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+541
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+311
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+311
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+16505
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+311

	.data.b	74
	.data.w	.Ldw_begin+16417
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16369
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+862
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2313

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+886
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+16429
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	105,110,116,0
	.section	.debug_info		;off: 916
	.data.w	.Ldw_str_begin+260
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 264
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 923
	.data.w	.Ldw_str_begin+264
	.data.b	7
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+2863

	.data.b	49
	.data.w	.Ldw_begin+3414

	.data.b	49
	.data.w	.Ldw_begin+3471

	.data.b	49
	.data.w	.Ldw_begin+3566

	.data.b	49
	.data.w	.Ldw_begin+3699

	.data.b	49
	.data.w	.Ldw_begin+3934

	.data.b	49
	.data.w	.Ldw_begin+4115

	.data.b	49
	.data.w	.Ldw_begin+4376

	.data.b	49
	.data.w	.Ldw_begin+4517

	.data.b	49
	.data.w	.Ldw_begin+4878

	.data.b	49
	.data.w	.Ldw_begin+5019

	.data.b	49
	.data.w	.Ldw_begin+5160

	.data.b	49
	.data.w	.Ldw_begin+5301

	.data.b	49
	.data.w	.Ldw_begin+5682

	.data.b	49
	.data.w	.Ldw_begin+6063

	.data.b	49
	.data.w	.Ldw_begin+6184

	.data.b	49
	.data.w	.Ldw_begin+6545

	.data.b	49
	.data.w	.Ldw_begin+6906

	.data.b	49
	.data.w	.Ldw_begin+7007

	.data.b	49
	.data.w	.Ldw_begin+7188

	.data.b	49
	.data.w	.Ldw_begin+7369

	.data.b	49
	.data.w	.Ldw_begin+7550

	.data.b	49
	.data.w	.Ldw_begin+7731

	.data.b	49
	.data.w	.Ldw_begin+7832

	.data.b	49
	.data.w	.Ldw_begin+8053

	.data.b	49
	.data.w	.Ldw_begin+8114

	.data.b	49
	.data.w	.Ldw_begin+8475

	.data.b	49
	.data.w	.Ldw_begin+8536

	.data.b	49
	.data.w	.Ldw_begin+8637

	.data.b	49
	.data.w	.Ldw_begin+8798

	.data.b	49
	.data.w	.Ldw_begin+9019

	.data.b	49
	.data.w	.Ldw_begin+9560

	.data.b	49
	.data.w	.Ldw_begin+9701

	.data.b	49
	.data.w	.Ldw_begin+9842

	.data.b	49
	.data.w	.Ldw_begin+9883

	.data.b	49
	.data.w	.Ldw_begin+9924

	.data.b	49
	.data.w	.Ldw_begin+9965

	.data.b	49
	.data.w	.Ldw_begin+10006

	.data.b	49
	.data.w	.Ldw_begin+10167

	.data.b	49
	.data.w	.Ldw_begin+10328

	.data.b	49
	.data.w	.Ldw_begin+10489

	.data.b	49
	.data.w	.Ldw_begin+10630

	.data.b	49
	.data.w	.Ldw_begin+10691

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+11164

	.section	.debug_abbrev		;off: 76
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 1151
	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.section	.debug_abbrev		;off: 87
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 1159
	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+11219

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+11274

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+11329

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+11384

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	15

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+11439

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	15

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+11494

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	15

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+11549

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	15

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+12429

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	72
	.data.w	.Ldw_begin+2509

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	17

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	36
	.data.w	.Ldw_begin+14972

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1320

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+16357

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	15

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+16812

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	51
	.data.w	.Ldw_begin+16867

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+16417

	.data.b	53
	.data.w	.Ldw_begin+2166

	.data.b	47
	.data.w	.Ldw_begin+16405

	.data.b	53
	.data.w	.Ldw_begin+1386

	.data.b	47
	.data.w	.Ldw_begin+2166

	.data.b	53
	.data.w	.Ldw_begin+1396

	.data.b	47
	.data.w	.Ldw_begin+15848

	.data.b	53
	.data.w	.Ldw_begin+1406

	.data.b	47
	.data.w	.Ldw_begin+17410

	.data.b	53
	.data.w	.Ldw_begin+1416

	.data.b	47
	.data.w	.Ldw_begin+16344

	.data.b	53
	.data.w	.Ldw_begin+1426

	.data.b	47
	.data.w	.Ldw_begin+16429

	.data.b	53
	.data.w	.Ldw_begin+1436

	.data.b	47
	.data.w	.Ldw_begin+17482

	.data.b	53
	.data.w	.Ldw_begin+1446

	.data.b	47
	.data.w	.Ldw_begin+17728

	.data.b	53
	.data.w	.Ldw_begin+1456

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+1461

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+16740

	.data.b	53
	.data.w	.Ldw_begin+1482

	.data.b	64
	.data.b	0
	.data.b	136,2
	.data.w	.Ldw_begin+17024

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	44
	.data.w	.Ldw_begin+311

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	10

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	11
	.data.w	.Ldw_begin+16417

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	10

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+17113

	.data.b	64
	.data.b	0
	.data.b	88
	.data.w	.Ldw_begin+17024

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	20
	.data.w	.Ldw_begin+311

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	4

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	5
	.data.w	.Ldw_begin+16417

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	4

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1541

	.data.b	47
	.data.w	.Ldw_begin+1594

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+1599

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	48
	.data.w	.Ldw_begin+98

	.data.b	56
	.data.w	.Ldw_begin+915
	.data.b	4
	.data.b	0
	.data.b	11

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+15903

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2497
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2497
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1431

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1663
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2190
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+15027
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+15027
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+16115

	.data.b	53
	.data.w	.Ldw_begin+1753

	.data.b	47
	.data.w	.Ldw_begin+1758

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14763
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1763
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+16238

	.data.b	53
	.data.w	.Ldw_begin+1793

	.data.b	47
	.data.w	.Ldw_begin+1798

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14763
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1803
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14763
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2178
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14538
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1636

	.data.b	47
	.data.w	.Ldw_begin+1902

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1907
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1411

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1931
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+15958

	.data.b	53
	.data.w	.Ldw_begin+1961

	.data.b	47
	.data.w	.Ldw_begin+1966

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14538
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1971
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2154
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
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2178
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2178
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2166
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 2155
	.data.w	.Ldw_str_begin+277
	.data.b	51
	.data.b	29
	.data.b	14
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

	.section	.debug_info		;off: 2166
	.data.b	45
	.section	.debug_str		;off: 285
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 2167
	.data.w	.Ldw_str_begin+285
	.data.b	56
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 291
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 2179
	.data.w	.Ldw_str_begin+291
	.data.b	60
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+205

	.data.b	45
	.section	.debug_str		;off: 298
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 2191
	.data.w	.Ldw_str_begin+298
	.data.b	64
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 305
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 2203
	.data.w	.Ldw_str_begin+305
	.data.b	68
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 2215
	.data.w	.Ldw_str_begin+312
	.data.b	39
	.data.b	15
	.data.b	9
	.data.w	.Ldw_begin+2166

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	9
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

	.section	.debug_info		;off: 2232
	.data.b	40
	.section	.debug_str		;off: 327
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 2233
	.data.w	.Ldw_str_begin+327
	.data.b	63
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2178
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

	.section	.debug_info		;off: 2248
	.data.b	40
	.section	.debug_str		;off: 336
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 2249
	.data.w	.Ldw_str_begin+336
	.data.b	64
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 345
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2265
	.data.w	.Ldw_str_begin+345
	.data.b	65
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2281
	.data.w	.Ldw_str_begin+362
	.data.b	66
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2297
	.data.w	.Ldw_str_begin+379
	.data.b	67
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 396
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 2314
	.data.w	.Ldw_str_begin+396
	.data.b	68
	.data.b	2
	.data.b	9
	.data.w	.Ldw_begin+2226

	.data.b	52
	.section	.debug_str		;off: 416
	.data.b	0
	.section	.debug_info		;off: 2326
	.data.w	.Ldw_str_begin+416
	.data.b	36
	.data.b	1
	.data.b	15
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

	.section	.debug_info		;off: 2335
	.data.b	51
	.section	.debug_str		;off: 417
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 2336
	.data.w	.Ldw_str_begin+417
	.data.b	37
	.data.b	5
	.data.b	15
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

	.section	.debug_info		;off: 2344
	.data.b	51
	.section	.debug_str		;off: 434
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 2345
	.data.w	.Ldw_str_begin+434
	.data.b	38
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 451
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 2354
	.data.w	.Ldw_str_begin+451
	.data.b	39
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 468
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 2363
	.data.w	.Ldw_str_begin+468
	.data.b	40
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 485
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 2372
	.data.w	.Ldw_str_begin+485
	.data.b	41
	.data.b	5
	.data.b	15
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 502
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 2382
	.data.w	.Ldw_str_begin+502
	.data.b	42
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+2325

	.data.b	45
	.section	.debug_str		;off: 514
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 2394
	.data.w	.Ldw_str_begin+514
	.data.b	32
	.data.b	21
	.data.b	8
	.data.w	.Ldw_begin+2381

	.data.b	52
	.section	.debug_str		;off: 528
	.data.b	0
	.section	.debug_info		;off: 2406
	.data.w	.Ldw_str_begin+528
	.data.b	39
	.data.b	1
	.data.b	8
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 529
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 2416
	.data.w	.Ldw_str_begin+529
	.data.b	41
	.data.b	5
	.data.b	8
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 547
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 2425
	.data.w	.Ldw_str_begin+547
	.data.b	43
	.data.b	5
	.data.b	8
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 564
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 2434
	.data.w	.Ldw_str_begin+564
	.data.b	45
	.data.b	5
	.data.b	8
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 582
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 2443
	.data.w	.Ldw_str_begin+582
	.data.b	47
	.data.b	5
	.data.b	8
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 599
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 2452
	.data.w	.Ldw_str_begin+599
	.data.b	49
	.data.b	5
	.data.b	8
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 616
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 2461
	.data.w	.Ldw_str_begin+616
	.data.b	51
	.data.b	5
	.data.b	8
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 633
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 2470
	.data.w	.Ldw_str_begin+633
	.data.b	53
	.data.b	5
	.data.b	8
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 650
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 2479
	.data.w	.Ldw_str_begin+650
	.data.b	55
	.data.b	5
	.data.b	8
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 667
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 2488
	.data.w	.Ldw_str_begin+667
	.data.b	57
	.data.b	5
	.data.b	8
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 684
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 2498
	.data.w	.Ldw_str_begin+684
	.data.b	58
	.data.b	3
	.data.b	8
	.data.w	.Ldw_begin+2405

	.data.b	45
	.section	.debug_str		;off: 700
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 2510
	.data.w	.Ldw_str_begin+700
	.data.b	24
	.data.b	22
	.data.b	19
	.data.w	.Ldw_begin+922

	.data.b	71
	.data.b	31
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 707
	.data.b	84,82,73,67,78,84,0
	.section	.debug_info		;off: 2528
	.data.w	.Ldw_str_begin+707
	.data.b	32
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	6
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

	.section	.debug_info		;off: 2546
	.data.b	41
	.section	.debug_str		;off: 714
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 2547
	.data.w	.Ldw_str_begin+714
	.data.b	33
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 725
	.data.b	84,82,73,67,78,84,83,69,84,0
	.section	.debug_info		;off: 2566
	.data.w	.Ldw_str_begin+725
	.data.b	34
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 735
	.data.b	114,101,115,101,114,118,101,100,95,49,52,0
	.section	.debug_info		;off: 2585
	.data.w	.Ldw_str_begin+735
	.data.b	35
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 747
	.data.b	73,78,84,82,73,83,69,76,0
	.section	.debug_info		;off: 2604
	.data.w	.Ldw_str_begin+747
	.data.b	36
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 756
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 2623
	.data.w	.Ldw_str_begin+756
	.data.b	37
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 768
	.data.b	83,65,82,65,68,67,95,81,50,84,82,73,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 2643
	.data.w	.Ldw_str_begin+768
	.data.b	38
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2521

	.data.b	71
	.data.b	42
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 790
	.data.b	65,78,65,69,78,0
	.section	.debug_info		;off: 2661
	.data.w	.Ldw_str_begin+790
	.data.b	43
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 796
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2680
	.data.w	.Ldw_str_begin+796
	.data.b	48
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 807
	.data.b	65,78,65,82,69,83,79,0
	.section	.debug_info		;off: 2699
	.data.w	.Ldw_str_begin+807
	.data.b	50
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 815
	.data.b	67,65,76,73,67,0
	.section	.debug_info		;off: 2718
	.data.w	.Ldw_str_begin+815
	.data.b	51
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 821
	.data.b	68,73,83,72,69,78,0
	.section	.debug_info		;off: 2737
	.data.w	.Ldw_str_begin+821
	.data.b	52
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 828
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 2756
	.data.w	.Ldw_str_begin+828
	.data.b	53
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 839
	.data.b	65,78,65,68,73,86,70,0
	.section	.debug_info		;off: 2775
	.data.w	.Ldw_str_begin+839
	.data.b	54
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 847
	.data.b	79,70,70,83,69,84,0
	.section	.debug_info		;off: 2794
	.data.w	.Ldw_str_begin+847
	.data.b	55
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	10
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 854
	.data.b	114,101,115,101,114,118,101,100,95,50,50,0
	.section	.debug_info		;off: 2813
	.data.w	.Ldw_str_begin+854
	.data.b	56
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	1
	.data.b	9
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 866
	.data.b	65,78,65,70,76,71,0
	.section	.debug_info		;off: 2832
	.data.w	.Ldw_str_begin+866
	.data.b	57
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 873
	.data.b	83,65,82,65,68,67,95,65,78,65,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 2852
	.data.w	.Ldw_str_begin+873
	.data.b	58
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2654

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 892
	.data.b	80,82,73,79,76,48,0
	.section	.debug_info		;off: 2870
	.data.w	.Ldw_str_begin+892
	.data.b	63
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 899
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 2889
	.data.w	.Ldw_str_begin+899
	.data.b	64
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 910
	.data.b	67,79,78,83,77,79,68,69,48,0
	.section	.debug_info		;off: 2908
	.data.w	.Ldw_str_begin+910
	.data.b	65
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 920
	.data.b	80,82,73,79,76,49,0
	.section	.debug_info		;off: 2927
	.data.w	.Ldw_str_begin+920
	.data.b	66
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 927
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 2946
	.data.w	.Ldw_str_begin+927
	.data.b	67
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 938
	.data.b	67,79,78,83,77,79,68,69,49,0
	.section	.debug_info		;off: 2965
	.data.w	.Ldw_str_begin+938
	.data.b	68
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 948
	.data.b	80,82,73,79,76,50,0
	.section	.debug_info		;off: 2984
	.data.w	.Ldw_str_begin+948
	.data.b	69
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 955
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 3003
	.data.w	.Ldw_str_begin+955
	.data.b	70
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 967
	.data.b	67,79,78,83,77,79,68,69,50,0
	.section	.debug_info		;off: 3022
	.data.w	.Ldw_str_begin+967
	.data.b	71
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 977
	.data.b	114,101,115,101,114,118,101,100,95,0
	.section	.debug_info		;off: 3041
	.data.w	.Ldw_str_begin+977
	.data.b	72
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 987
	.data.b	73,78,74,69,67,84,48,67,76,82,0
	.section	.debug_info		;off: 3060
	.data.w	.Ldw_str_begin+987
	.data.b	73
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 998
	.data.b	73,78,74,69,67,84,49,67,76,82,0
	.section	.debug_info		;off: 3079
	.data.w	.Ldw_str_begin+998
	.data.b	74
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1009
	.data.b	73,78,74,69,67,84,50,67,76,82,0
	.section	.debug_info		;off: 3098
	.data.w	.Ldw_str_begin+1009
	.data.b	75
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1020
	.data.b	81,48,87,65,73,84,0
	.section	.debug_info		;off: 3117
	.data.w	.Ldw_str_begin+1020
	.data.b	76
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1027
	.data.b	81,49,87,65,73,84,0
	.section	.debug_info		;off: 3136
	.data.w	.Ldw_str_begin+1027
	.data.b	77
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1034
	.data.b	81,50,87,65,73,84,0
	.section	.debug_info		;off: 3155
	.data.w	.Ldw_str_begin+1034
	.data.b	78
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1041
	.data.b	114,101,115,101,114,118,101,100,95,49,57,0
	.section	.debug_info		;off: 3174
	.data.w	.Ldw_str_begin+1041
	.data.b	79
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1053
	.data.b	81,48,66,85,83,89,0
	.section	.debug_info		;off: 3193
	.data.w	.Ldw_str_begin+1053
	.data.b	80
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1060
	.data.b	81,49,66,85,83,89,0
	.section	.debug_info		;off: 3212
	.data.w	.Ldw_str_begin+1060
	.data.b	81
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1067
	.data.b	81,50,66,85,83,89,0
	.section	.debug_info		;off: 3231
	.data.w	.Ldw_str_begin+1067
	.data.b	82
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1074
	.data.b	83,89,78,67,66,85,83,89,0
	.section	.debug_info		;off: 3250
	.data.w	.Ldw_str_begin+1074
	.data.b	83
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1083
	.data.b	65,82,66,69,78,48,0
	.section	.debug_info		;off: 3269
	.data.w	.Ldw_str_begin+1083
	.data.b	84
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1090
	.data.b	65,82,66,69,78,49,0
	.section	.debug_info		;off: 3288
	.data.w	.Ldw_str_begin+1090
	.data.b	85
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1097
	.data.b	65,82,66,69,78,50,0
	.section	.debug_info		;off: 3307
	.data.w	.Ldw_str_begin+1097
	.data.b	86
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1104
	.data.b	73,78,74,69,67,84,48,83,84,65,0
	.section	.debug_info		;off: 3326
	.data.w	.Ldw_str_begin+1104
	.data.b	87
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1115
	.data.b	73,78,74,69,67,84,49,83,84,65,0
	.section	.debug_info		;off: 3345
	.data.w	.Ldw_str_begin+1115
	.data.b	88
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1126
	.data.b	73,78,74,69,67,84,50,83,84,65,0
	.section	.debug_info		;off: 3364
	.data.w	.Ldw_str_begin+1126
	.data.b	89
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1137
	.data.b	114,101,115,101,114,118,101,100,95,51,48,0
	.section	.debug_info		;off: 3383
	.data.w	.Ldw_str_begin+1137
	.data.b	90
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1149
	.data.b	83,65,82,65,68,67,95,65,82,66,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 3403
	.data.w	.Ldw_str_begin+1149
	.data.b	91
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+929

	.data.b	71
	.data.b	95
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1169
	.data.b	83,84,67,84,82,76,0
	.section	.debug_info		;off: 3421
	.data.w	.Ldw_str_begin+1169
	.data.b	96
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1176
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 3440
	.data.w	.Ldw_str_begin+1176
	.data.b	97
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	24
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1187
	.data.b	83,65,82,65,68,67,95,83,65,77,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 3460
	.data.w	.Ldw_str_begin+1187
	.data.b	98
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+934

	.data.b	71
	.data.b	102
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1207
	.data.b	66,79,85,78,68,76,0
	.section	.debug_info		;off: 3478
	.data.w	.Ldw_str_begin+1207
	.data.b	103
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1214
	.data.b	66,79,85,78,68,76,83,69,76,0
	.section	.debug_info		;off: 3497
	.data.w	.Ldw_str_begin+1214
	.data.b	104
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1224
	.data.b	66,79,85,78,68,85,0
	.section	.debug_info		;off: 3516
	.data.w	.Ldw_str_begin+1224
	.data.b	105
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1231
	.data.b	66,79,85,78,68,85,83,69,76,0
	.section	.debug_info		;off: 3535
	.data.w	.Ldw_str_begin+1231
	.data.b	106
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1241
	.data.b	83,65,82,65,68,67,95,70,85,78,66,79,85,78,68,95,66,105,116,115,0
	.section	.debug_info		;off: 3555
	.data.w	.Ldw_str_begin+1241
	.data.b	107
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+939

	.data.b	71
	.data.b	111
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1262
	.data.b	83,89,78,67,83,69,76,0
	.section	.debug_info		;off: 3573
	.data.w	.Ldw_str_begin+1262
	.data.b	112
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1270
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3592
	.data.w	.Ldw_str_begin+1270
	.data.b	113
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1281
	.data.b	83,89,78,67,69,78,49,0
	.section	.debug_info		;off: 3611
	.data.w	.Ldw_str_begin+1281
	.data.b	114
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1289
	.data.b	83,89,78,67,69,78,50,0
	.section	.debug_info		;off: 3630
	.data.w	.Ldw_str_begin+1289
	.data.b	115
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1297
	.data.b	83,89,78,67,69,78,51,0
	.section	.debug_info		;off: 3649
	.data.w	.Ldw_str_begin+1297
	.data.b	116
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1305
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 3668
	.data.w	.Ldw_str_begin+1305
	.data.b	117
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	25
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1316
	.data.b	83,65,82,65,68,67,95,83,89,78,67,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 3688
	.data.w	.Ldw_str_begin+1316
	.data.b	118
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+944

	.data.b	71
	.data.b	122
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1337
	.data.b	114,101,115,101,114,118,101,100,95,48,0
	.section	.debug_info		;off: 3706
	.data.w	.Ldw_str_begin+1337
	.data.b	123
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1348
	.data.b	84,82,73,83,69,76,0
	.section	.debug_info		;off: 3725
	.data.w	.Ldw_str_begin+1348
	.data.b	124
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1355
	.data.b	69,88,84,84,82,73,83,69,76,0
	.section	.debug_info		;off: 3744
	.data.w	.Ldw_str_begin+1355
	.data.b	125
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1365
	.data.b	69,88,84,84,82,73,76,86,76,0
	.section	.debug_info		;off: 3763
	.data.w	.Ldw_str_begin+1365
	.data.b	126
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1375
	.data.b	84,82,73,77,79,68,69,0
	.section	.debug_info		;off: 3782
	.data.w	.Ldw_str_begin+1375
	.data.b	127
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1383
	.data.b	84,82,87,69,0
	.section	.debug_info		;off: 3801
	.data.w	.Ldw_str_begin+1383
	.data.b	128,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1388
	.data.b	71,65,84,69,83,69,76,0
	.section	.debug_info		;off: 3821
	.data.w	.Ldw_str_begin+1388
	.data.b	129,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1396
	.data.b	71,65,84,69,76,86,76,0
	.section	.debug_info		;off: 3841
	.data.w	.Ldw_str_begin+1396
	.data.b	130,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1404
	.data.b	114,101,115,101,114,118,101,100,95,50,49,0
	.section	.debug_info		;off: 3861
	.data.w	.Ldw_str_begin+1404
	.data.b	131,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1416
	.data.b	71,83,87,69,0
	.section	.debug_info		;off: 3881
	.data.w	.Ldw_str_begin+1416
	.data.b	132,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1421
	.data.b	114,101,115,101,114,118,101,100,95,50,51,0
	.section	.debug_info		;off: 3901
	.data.w	.Ldw_str_begin+1421
	.data.b	133,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1433
	.data.b	83,65,82,65,68,67,95,81,84,82,73,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 3922
	.data.w	.Ldw_str_begin+1433
	.data.b	134,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+949

	.data.b	71
	.data.b	138,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1454
	.data.b	71,65,84,69,69,78,0
	.section	.debug_info		;off: 3942
	.data.w	.Ldw_str_begin+1454
	.data.b	139,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1461
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3962
	.data.w	.Ldw_str_begin+1461
	.data.b	140,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1472
	.data.b	69,88,84,84,82,73,69,78,0
	.section	.debug_info		;off: 3982
	.data.w	.Ldw_str_begin+1472
	.data.b	141,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1481
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 4002
	.data.w	.Ldw_str_begin+1481
	.data.b	142,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1492
	.data.b	83,84,82,73,71,69,78,0
	.section	.debug_info		;off: 4022
	.data.w	.Ldw_str_begin+1492
	.data.b	143,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1500
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 4042
	.data.w	.Ldw_str_begin+1500
	.data.b	144,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1511
	.data.b	70,76,85,81,85,0
	.section	.debug_info		;off: 4062
	.data.w	.Ldw_str_begin+1511
	.data.b	145,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1517
	.data.b	114,101,115,101,114,118,101,100,95,49,51,0
	.section	.debug_info		;off: 4082
	.data.w	.Ldw_str_begin+1517
	.data.b	146,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	19
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1529
	.data.b	83,65,82,65,68,67,95,81,77,79,68,69,95,66,105,116,115,0
	.section	.debug_info		;off: 4103
	.data.w	.Ldw_str_begin+1529
	.data.b	147,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+954

	.data.b	71
	.data.b	151,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1547
	.data.b	82,69,81,67,72,78,0
	.section	.debug_info		;off: 4123
	.data.w	.Ldw_str_begin+1547
	.data.b	152,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1554
	.data.b	82,70,69,78,0
	.section	.debug_info		;off: 4143
	.data.w	.Ldw_str_begin+1554
	.data.b	153,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1559
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 4163
	.data.w	.Ldw_str_begin+1559
	.data.b	154,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1570
	.data.b	69,88,84,69,82,69,78,0
	.section	.debug_info		;off: 4183
	.data.w	.Ldw_str_begin+1570
	.data.b	155,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1578
	.data.b	81,73,69,78,0
	.section	.debug_info		;off: 4203
	.data.w	.Ldw_str_begin+1578
	.data.b	156,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1583
	.data.b	77,68,76,80,68,0
	.section	.debug_info		;off: 4223
	.data.w	.Ldw_str_begin+1583
	.data.b	157,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1589
	.data.b	77,68,80,68,0
	.section	.debug_info		;off: 4243
	.data.w	.Ldw_str_begin+1589
	.data.b	158,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1594
	.data.b	77,68,80,85,0
	.section	.debug_info		;off: 4263
	.data.w	.Ldw_str_begin+1594
	.data.b	159,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1599
	.data.b	67,68,69,78,0
	.section	.debug_info		;off: 4283
	.data.w	.Ldw_str_begin+1599
	.data.b	160,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1604
	.data.b	67,79,78,68,83,69,76,0
	.section	.debug_info		;off: 4303
	.data.w	.Ldw_str_begin+1604
	.data.b	161,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1612
	.data.b	83,85,67,67,69,69,78,0
	.section	.debug_info		;off: 4323
	.data.w	.Ldw_str_begin+1612
	.data.b	162,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1620
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 4343
	.data.w	.Ldw_str_begin+1620
	.data.b	163,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1632
	.data.b	83,65,82,65,68,67,95,81,73,78,67,70,71,95,66,105,116,115,0
	.section	.debug_info		;off: 4364
	.data.w	.Ldw_str_begin+1632
	.data.b	164,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+959

	.data.b	71
	.data.b	168,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1651
	.data.b	83,69,81,84,77,79,68,0
	.section	.debug_info		;off: 4384
	.data.w	.Ldw_str_begin+1651
	.data.b	169,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1659
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 4404
	.data.w	.Ldw_str_begin+1659
	.data.b	170,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1670
	.data.b	83,69,81,84,86,65,76,85,69,0
	.section	.debug_info		;off: 4424
	.data.w	.Ldw_str_begin+1670
	.data.b	171,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1680
	.data.b	83,84,82,73,84,69,78,0
	.section	.debug_info		;off: 4444
	.data.w	.Ldw_str_begin+1680
	.data.b	172,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1688
	.data.b	69,88,84,84,82,73,84,69,78,0
	.section	.debug_info		;off: 4464
	.data.w	.Ldw_str_begin+1688
	.data.b	173,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1698
	.data.b	114,101,115,101,114,118,101,100,95,49,56,0
	.section	.debug_info		;off: 4484
	.data.w	.Ldw_str_begin+1698
	.data.b	174,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1710
	.data.b	83,65,82,65,68,67,95,81,82,69,81,84,77,95,66,105,116,115,0
	.section	.debug_info		;off: 4505
	.data.w	.Ldw_str_begin+1710
	.data.b	175,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+964

	.data.b	71
	.data.b	179,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1729
	.data.b	67,72,73,78,84,77,79,68,69,0
	.section	.debug_info		;off: 4525
	.data.w	.Ldw_str_begin+1729
	.data.b	180,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1739
	.data.b	83,89,78,67,82,69,81,0
	.section	.debug_info		;off: 4545
	.data.w	.Ldw_str_begin+1739
	.data.b	181,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1747
	.data.b	66,79,85,78,68,83,69,76,0
	.section	.debug_info		;off: 4565
	.data.w	.Ldw_str_begin+1747
	.data.b	182,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1756
	.data.b	66,79,85,78,68,68,82,0
	.section	.debug_info		;off: 4585
	.data.w	.Ldw_str_begin+1756
	.data.b	183,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1764
	.data.b	66,79,85,78,68,82,83,0
	.section	.debug_info		;off: 4605
	.data.w	.Ldw_str_begin+1764
	.data.b	184,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1772
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 4625
	.data.w	.Ldw_str_begin+1772
	.data.b	185,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1783
	.data.b	82,69,83,83,84,84,65,82,0
	.section	.debug_info		;off: 4645
	.data.w	.Ldw_str_begin+1783
	.data.b	186,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1792
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 4665
	.data.w	.Ldw_str_begin+1792
	.data.b	187,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1803
	.data.b	82,69,83,83,84,82,69,71,0
	.section	.debug_info		;off: 4685
	.data.w	.Ldw_str_begin+1803
	.data.b	188,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1812
	.data.b	68,82,69,68,67,84,82,76,0
	.section	.debug_info		;off: 4705
	.data.w	.Ldw_str_begin+1812
	.data.b	189,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1821
	.data.b	72,68,73,70,67,69,78,0
	.section	.debug_info		;off: 4725
	.data.w	.Ldw_str_begin+1821
	.data.b	190,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1829
	.data.b	72,68,73,71,84,77,69,78,0
	.section	.debug_info		;off: 4745
	.data.w	.Ldw_str_begin+1829
	.data.b	191,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1838
	.data.b	72,68,73,82,68,67,69,78,0
	.section	.debug_info		;off: 4765
	.data.w	.Ldw_str_begin+1838
	.data.b	192,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1847
	.data.b	114,101,115,101,114,118,101,100,95,50,51,0
	.section	.debug_info		;off: 4785
	.data.w	.Ldw_str_begin+1847
	.data.b	193,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1859
	.data.b	66,87,68,69,84,69,78,0
	.section	.debug_info		;off: 4805
	.data.w	.Ldw_str_begin+1859
	.data.b	194,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1867
	.data.b	66,87,68,82,69,70,83,69,76,0
	.section	.debug_info		;off: 4825
	.data.w	.Ldw_str_begin+1867
	.data.b	195,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1877
	.data.b	114,101,115,101,114,118,101,100,95,50,54,0
	.section	.debug_info		;off: 4845
	.data.w	.Ldw_str_begin+1877
	.data.b	196,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1889
	.data.b	83,65,82,65,68,67,95,67,72,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 4866
	.data.w	.Ldw_str_begin+1889
	.data.b	197,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+969

	.data.b	71
	.data.b	201,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1908
	.data.b	87,70,82,77,79,68,69,0
	.section	.debug_info		;off: 4886
	.data.w	.Ldw_str_begin+1908
	.data.b	202,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1916
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 4906
	.data.w	.Ldw_str_begin+1916
	.data.b	203,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1927
	.data.b	82,69,83,65,76,73,0
	.section	.debug_info		;off: 4926
	.data.w	.Ldw_str_begin+1927
	.data.b	204,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1934
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 4946
	.data.w	.Ldw_str_begin+1934
	.data.b	205,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1945
	.data.b	78,82,73,78,84,69,78,0
	.section	.debug_info		;off: 4966
	.data.w	.Ldw_str_begin+1945
	.data.b	206,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1953
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 4986
	.data.w	.Ldw_str_begin+1953
	.data.b	207,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	23
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1964
	.data.b	83,65,82,65,68,67,95,82,69,83,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 5007
	.data.w	.Ldw_str_begin+1964
	.data.b	208,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+974

	.data.b	71
	.data.b	212,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1984
	.data.b	67,79,78,82,69,83,85,76,84,0
	.section	.debug_info		;off: 5027
	.data.w	.Ldw_str_begin+1984
	.data.b	213,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1994
	.data.b	67,72,78,85,77,0
	.section	.debug_info		;off: 5047
	.data.w	.Ldw_str_begin+1994
	.data.b	214,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2000
	.data.b	67,79,78,82,69,81,83,0
	.section	.debug_info		;off: 5067
	.data.w	.Ldw_str_begin+2000
	.data.b	215,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2008
	.data.b	114,101,115,101,114,118,101,100,95,50,51,0
	.section	.debug_info		;off: 5087
	.data.w	.Ldw_str_begin+2008
	.data.b	216,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2020
	.data.b	86,70,76,65,71,0
	.section	.debug_info		;off: 5107
	.data.w	.Ldw_str_begin+2020
	.data.b	217,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2026
	.data.b	114,101,115,101,114,118,101,100,95,50,53,0
	.section	.debug_info		;off: 5127
	.data.w	.Ldw_str_begin+2026
	.data.b	218,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2038
	.data.b	83,65,82,65,68,67,95,82,69,83,85,76,84,95,66,105,116,115,0
	.section	.debug_info		;off: 5148
	.data.w	.Ldw_str_begin+2038
	.data.b	219,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+979

	.data.b	71
	.data.b	223,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2057
	.data.b	67,79,78,82,69,83,85,76,84,0
	.section	.debug_info		;off: 5168
	.data.w	.Ldw_str_begin+2057
	.data.b	224,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2067
	.data.b	67,72,78,85,77,0
	.section	.debug_info		;off: 5188
	.data.w	.Ldw_str_begin+2067
	.data.b	225,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2073
	.data.b	67,79,78,82,69,81,83,0
	.section	.debug_info		;off: 5208
	.data.w	.Ldw_str_begin+2073
	.data.b	226,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2081
	.data.b	114,101,115,101,114,118,101,100,95,50,51,0
	.section	.debug_info		;off: 5228
	.data.w	.Ldw_str_begin+2081
	.data.b	227,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2093
	.data.b	86,70,76,65,71,0
	.section	.debug_info		;off: 5248
	.data.w	.Ldw_str_begin+2093
	.data.b	228,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2099
	.data.b	114,101,115,101,114,118,101,100,95,50,53,0
	.section	.debug_info		;off: 5268
	.data.w	.Ldw_str_begin+2099
	.data.b	229,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2111
	.data.b	83,65,82,65,68,67,95,82,69,83,85,76,84,68,95,66,105,116,115,0
	.section	.debug_info		;off: 5289
	.data.w	.Ldw_str_begin+2111
	.data.b	230,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+984

	.data.b	71
	.data.b	234,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2131
	.data.b	67,73,78,84,48,0
	.section	.debug_info		;off: 5309
	.data.w	.Ldw_str_begin+2131
	.data.b	235,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2137
	.data.b	67,73,78,84,49,0
	.section	.debug_info		;off: 5329
	.data.w	.Ldw_str_begin+2137
	.data.b	236,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2143
	.data.b	67,73,78,84,50,0
	.section	.debug_info		;off: 5349
	.data.w	.Ldw_str_begin+2143
	.data.b	237,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2149
	.data.b	67,73,78,84,51,0
	.section	.debug_info		;off: 5369
	.data.w	.Ldw_str_begin+2149
	.data.b	238,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2155
	.data.b	67,73,78,84,52,0
	.section	.debug_info		;off: 5389
	.data.w	.Ldw_str_begin+2155
	.data.b	239,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2161
	.data.b	67,73,78,84,53,0
	.section	.debug_info		;off: 5409
	.data.w	.Ldw_str_begin+2161
	.data.b	240,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2167
	.data.b	67,73,78,84,54,0
	.section	.debug_info		;off: 5429
	.data.w	.Ldw_str_begin+2167
	.data.b	241,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2173
	.data.b	67,73,78,84,55,0
	.section	.debug_info		;off: 5449
	.data.w	.Ldw_str_begin+2173
	.data.b	242,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2179
	.data.b	67,73,78,84,56,0
	.section	.debug_info		;off: 5469
	.data.w	.Ldw_str_begin+2179
	.data.b	243,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2185
	.data.b	67,73,78,84,57,0
	.section	.debug_info		;off: 5489
	.data.w	.Ldw_str_begin+2185
	.data.b	244,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2191
	.data.b	67,73,78,84,49,48,0
	.section	.debug_info		;off: 5509
	.data.w	.Ldw_str_begin+2191
	.data.b	245,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2198
	.data.b	67,73,78,84,49,49,0
	.section	.debug_info		;off: 5529
	.data.w	.Ldw_str_begin+2198
	.data.b	246,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2205
	.data.b	67,73,78,84,49,50,0
	.section	.debug_info		;off: 5549
	.data.w	.Ldw_str_begin+2205
	.data.b	247,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2212
	.data.b	67,73,78,84,49,51,0
	.section	.debug_info		;off: 5569
	.data.w	.Ldw_str_begin+2212
	.data.b	248,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2219
	.data.b	67,73,78,84,49,52,0
	.section	.debug_info		;off: 5589
	.data.w	.Ldw_str_begin+2219
	.data.b	249,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2226
	.data.b	67,73,78,84,49,53,0
	.section	.debug_info		;off: 5609
	.data.w	.Ldw_str_begin+2226
	.data.b	250,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2233
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 5629
	.data.w	.Ldw_str_begin+2233
	.data.b	251,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2245
	.data.b	67,77,65,83,75,0
	.section	.debug_info		;off: 5649
	.data.w	.Ldw_str_begin+2245
	.data.b	252,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2251
	.data.b	83,65,82,65,68,67,95,67,73,78,84,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 5670
	.data.w	.Ldw_str_begin+2251
	.data.b	253,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+989

	.data.b	71
	.data.b	129,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2272
	.data.b	82,73,78,84,48,0
	.section	.debug_info		;off: 5690
	.data.w	.Ldw_str_begin+2272
	.data.b	130,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2278
	.data.b	82,73,78,84,49,0
	.section	.debug_info		;off: 5710
	.data.w	.Ldw_str_begin+2278
	.data.b	131,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2284
	.data.b	82,73,78,84,50,0
	.section	.debug_info		;off: 5730
	.data.w	.Ldw_str_begin+2284
	.data.b	132,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2290
	.data.b	82,73,78,84,51,0
	.section	.debug_info		;off: 5750
	.data.w	.Ldw_str_begin+2290
	.data.b	133,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2296
	.data.b	82,73,78,84,52,0
	.section	.debug_info		;off: 5770
	.data.w	.Ldw_str_begin+2296
	.data.b	134,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2302
	.data.b	82,73,78,84,53,0
	.section	.debug_info		;off: 5790
	.data.w	.Ldw_str_begin+2302
	.data.b	135,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2308
	.data.b	82,73,78,84,54,0
	.section	.debug_info		;off: 5810
	.data.w	.Ldw_str_begin+2308
	.data.b	136,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2314
	.data.b	82,73,78,84,55,0
	.section	.debug_info		;off: 5830
	.data.w	.Ldw_str_begin+2314
	.data.b	137,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2320
	.data.b	82,73,78,84,56,0
	.section	.debug_info		;off: 5850
	.data.w	.Ldw_str_begin+2320
	.data.b	138,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2326
	.data.b	82,73,78,84,57,0
	.section	.debug_info		;off: 5870
	.data.w	.Ldw_str_begin+2326
	.data.b	139,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2332
	.data.b	82,73,78,84,49,48,0
	.section	.debug_info		;off: 5890
	.data.w	.Ldw_str_begin+2332
	.data.b	140,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2339
	.data.b	82,73,78,84,49,49,0
	.section	.debug_info		;off: 5910
	.data.w	.Ldw_str_begin+2339
	.data.b	141,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2346
	.data.b	82,73,78,84,49,50,0
	.section	.debug_info		;off: 5930
	.data.w	.Ldw_str_begin+2346
	.data.b	142,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2353
	.data.b	82,73,78,84,49,51,0
	.section	.debug_info		;off: 5950
	.data.w	.Ldw_str_begin+2353
	.data.b	143,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2360
	.data.b	82,73,78,84,49,52,0
	.section	.debug_info		;off: 5970
	.data.w	.Ldw_str_begin+2360
	.data.b	144,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2367
	.data.b	82,73,78,84,49,53,0
	.section	.debug_info		;off: 5990
	.data.w	.Ldw_str_begin+2367
	.data.b	145,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2374
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 6010
	.data.w	.Ldw_str_begin+2374
	.data.b	146,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2386
	.data.b	82,77,65,83,75,0
	.section	.debug_info		;off: 6030
	.data.w	.Ldw_str_begin+2386
	.data.b	147,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2392
	.data.b	83,65,82,65,68,67,95,82,73,78,84,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 6051
	.data.w	.Ldw_str_begin+2392
	.data.b	148,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+994

	.data.b	71
	.data.b	152,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2413
	.data.b	83,73,78,84,48,0
	.section	.debug_info		;off: 6071
	.data.w	.Ldw_str_begin+2413
	.data.b	153,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2419
	.data.b	83,73,78,84,49,0
	.section	.debug_info		;off: 6091
	.data.w	.Ldw_str_begin+2419
	.data.b	154,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2425
	.data.b	83,73,78,84,50,0
	.section	.debug_info		;off: 6111
	.data.w	.Ldw_str_begin+2425
	.data.b	155,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2431
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 6131
	.data.w	.Ldw_str_begin+2431
	.data.b	156,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	27
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2442
	.data.b	83,77,65,83,75,0
	.section	.debug_info		;off: 6151
	.data.w	.Ldw_str_begin+2442
	.data.b	157,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2448
	.data.b	83,65,82,65,68,67,95,83,73,78,84,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 6172
	.data.w	.Ldw_str_begin+2448
	.data.b	158,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+999

	.data.b	71
	.data.b	162,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2469
	.data.b	67,67,76,82,48,0
	.section	.debug_info		;off: 6192
	.data.w	.Ldw_str_begin+2469
	.data.b	163,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2475
	.data.b	67,67,76,82,49,0
	.section	.debug_info		;off: 6212
	.data.w	.Ldw_str_begin+2475
	.data.b	164,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2481
	.data.b	67,67,76,82,50,0
	.section	.debug_info		;off: 6232
	.data.w	.Ldw_str_begin+2481
	.data.b	165,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2487
	.data.b	67,67,76,82,51,0
	.section	.debug_info		;off: 6252
	.data.w	.Ldw_str_begin+2487
	.data.b	166,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2493
	.data.b	67,67,76,82,52,0
	.section	.debug_info		;off: 6272
	.data.w	.Ldw_str_begin+2493
	.data.b	167,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2499
	.data.b	67,67,76,82,53,0
	.section	.debug_info		;off: 6292
	.data.w	.Ldw_str_begin+2499
	.data.b	168,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2505
	.data.b	67,67,76,82,54,0
	.section	.debug_info		;off: 6312
	.data.w	.Ldw_str_begin+2505
	.data.b	169,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2511
	.data.b	67,67,76,82,55,0
	.section	.debug_info		;off: 6332
	.data.w	.Ldw_str_begin+2511
	.data.b	170,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2517
	.data.b	67,67,76,82,56,0
	.section	.debug_info		;off: 6352
	.data.w	.Ldw_str_begin+2517
	.data.b	171,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2523
	.data.b	67,67,76,82,57,0
	.section	.debug_info		;off: 6372
	.data.w	.Ldw_str_begin+2523
	.data.b	172,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2529
	.data.b	67,67,76,82,49,48,0
	.section	.debug_info		;off: 6392
	.data.w	.Ldw_str_begin+2529
	.data.b	173,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2536
	.data.b	67,67,76,82,49,49,0
	.section	.debug_info		;off: 6412
	.data.w	.Ldw_str_begin+2536
	.data.b	174,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2543
	.data.b	67,67,76,82,49,50,0
	.section	.debug_info		;off: 6432
	.data.w	.Ldw_str_begin+2543
	.data.b	175,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2550
	.data.b	67,67,76,82,49,51,0
	.section	.debug_info		;off: 6452
	.data.w	.Ldw_str_begin+2550
	.data.b	176,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2557
	.data.b	67,67,76,82,49,52,0
	.section	.debug_info		;off: 6472
	.data.w	.Ldw_str_begin+2557
	.data.b	177,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2564
	.data.b	67,67,76,82,49,53,0
	.section	.debug_info		;off: 6492
	.data.w	.Ldw_str_begin+2564
	.data.b	178,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2571
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 6512
	.data.w	.Ldw_str_begin+2571
	.data.b	179,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2583
	.data.b	83,65,82,65,68,67,95,67,73,78,84,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 6533
	.data.w	.Ldw_str_begin+2583
	.data.b	180,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1004

	.data.b	71
	.data.b	184,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2603
	.data.b	82,67,76,82,48,0
	.section	.debug_info		;off: 6553
	.data.w	.Ldw_str_begin+2603
	.data.b	185,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2609
	.data.b	82,67,76,82,49,0
	.section	.debug_info		;off: 6573
	.data.w	.Ldw_str_begin+2609
	.data.b	186,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2615
	.data.b	82,67,76,82,50,0
	.section	.debug_info		;off: 6593
	.data.w	.Ldw_str_begin+2615
	.data.b	187,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2621
	.data.b	82,67,76,82,51,0
	.section	.debug_info		;off: 6613
	.data.w	.Ldw_str_begin+2621
	.data.b	188,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2627
	.data.b	82,67,76,82,52,0
	.section	.debug_info		;off: 6633
	.data.w	.Ldw_str_begin+2627
	.data.b	189,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2633
	.data.b	82,67,76,82,53,0
	.section	.debug_info		;off: 6653
	.data.w	.Ldw_str_begin+2633
	.data.b	190,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2639
	.data.b	82,67,76,82,54,0
	.section	.debug_info		;off: 6673
	.data.w	.Ldw_str_begin+2639
	.data.b	191,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2645
	.data.b	82,67,76,82,55,0
	.section	.debug_info		;off: 6693
	.data.w	.Ldw_str_begin+2645
	.data.b	192,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2651
	.data.b	82,67,76,82,56,0
	.section	.debug_info		;off: 6713
	.data.w	.Ldw_str_begin+2651
	.data.b	193,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2657
	.data.b	82,67,76,82,57,0
	.section	.debug_info		;off: 6733
	.data.w	.Ldw_str_begin+2657
	.data.b	194,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2663
	.data.b	82,67,76,82,49,48,0
	.section	.debug_info		;off: 6753
	.data.w	.Ldw_str_begin+2663
	.data.b	195,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2670
	.data.b	82,67,76,82,49,49,0
	.section	.debug_info		;off: 6773
	.data.w	.Ldw_str_begin+2670
	.data.b	196,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2677
	.data.b	82,67,76,82,49,50,0
	.section	.debug_info		;off: 6793
	.data.w	.Ldw_str_begin+2677
	.data.b	197,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2684
	.data.b	82,67,76,82,49,51,0
	.section	.debug_info		;off: 6813
	.data.w	.Ldw_str_begin+2684
	.data.b	198,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2691
	.data.b	82,67,76,82,49,52,0
	.section	.debug_info		;off: 6833
	.data.w	.Ldw_str_begin+2691
	.data.b	199,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2698
	.data.b	82,67,76,82,49,53,0
	.section	.debug_info		;off: 6853
	.data.w	.Ldw_str_begin+2698
	.data.b	200,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2705
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 6873
	.data.w	.Ldw_str_begin+2705
	.data.b	201,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2717
	.data.b	83,65,82,65,68,67,95,82,73,78,84,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 6894
	.data.w	.Ldw_str_begin+2717
	.data.b	202,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1009

	.data.b	71
	.data.b	206,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2737
	.data.b	83,67,76,82,48,0
	.section	.debug_info		;off: 6914
	.data.w	.Ldw_str_begin+2737
	.data.b	207,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2743
	.data.b	83,67,76,82,49,0
	.section	.debug_info		;off: 6934
	.data.w	.Ldw_str_begin+2743
	.data.b	208,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2749
	.data.b	83,67,76,82,50,0
	.section	.debug_info		;off: 6954
	.data.w	.Ldw_str_begin+2749
	.data.b	209,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2755
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 6974
	.data.w	.Ldw_str_begin+2755
	.data.b	210,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	29
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2766
	.data.b	83,65,82,65,68,67,95,83,73,78,84,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 6995
	.data.w	.Ldw_str_begin+2766
	.data.b	211,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1014

	.data.b	71
	.data.b	215,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2786
	.data.b	67,73,78,84,48,78,80,0
	.section	.debug_info		;off: 7015
	.data.w	.Ldw_str_begin+2786
	.data.b	216,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2794
	.data.b	67,73,78,84,49,78,80,0
	.section	.debug_info		;off: 7035
	.data.w	.Ldw_str_begin+2794
	.data.b	217,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2802
	.data.b	67,73,78,84,50,78,80,0
	.section	.debug_info		;off: 7055
	.data.w	.Ldw_str_begin+2802
	.data.b	218,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2810
	.data.b	67,73,78,84,51,78,80,0
	.section	.debug_info		;off: 7075
	.data.w	.Ldw_str_begin+2810
	.data.b	219,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2818
	.data.b	67,73,78,84,52,78,80,0
	.section	.debug_info		;off: 7095
	.data.w	.Ldw_str_begin+2818
	.data.b	220,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2826
	.data.b	67,73,78,84,53,78,80,0
	.section	.debug_info		;off: 7115
	.data.w	.Ldw_str_begin+2826
	.data.b	221,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2834
	.data.b	67,73,78,84,54,78,80,0
	.section	.debug_info		;off: 7135
	.data.w	.Ldw_str_begin+2834
	.data.b	222,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2842
	.data.b	67,73,78,84,55,78,80,0
	.section	.debug_info		;off: 7155
	.data.w	.Ldw_str_begin+2842
	.data.b	223,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2850
	.data.b	83,65,82,65,68,67,95,67,73,78,84,78,80,48,95,66,105,116,115,0
	.section	.debug_info		;off: 7176
	.data.w	.Ldw_str_begin+2850
	.data.b	224,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1019

	.data.b	71
	.data.b	228,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2870
	.data.b	67,73,78,84,56,78,80,0
	.section	.debug_info		;off: 7196
	.data.w	.Ldw_str_begin+2870
	.data.b	229,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2878
	.data.b	67,73,78,84,57,78,80,0
	.section	.debug_info		;off: 7216
	.data.w	.Ldw_str_begin+2878
	.data.b	230,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2886
	.data.b	67,73,78,84,49,48,78,80,0
	.section	.debug_info		;off: 7236
	.data.w	.Ldw_str_begin+2886
	.data.b	231,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2895
	.data.b	67,73,78,84,49,49,78,80,0
	.section	.debug_info		;off: 7256
	.data.w	.Ldw_str_begin+2895
	.data.b	232,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2904
	.data.b	67,73,78,84,49,50,78,80,0
	.section	.debug_info		;off: 7276
	.data.w	.Ldw_str_begin+2904
	.data.b	233,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2913
	.data.b	67,73,78,84,49,51,78,80,0
	.section	.debug_info		;off: 7296
	.data.w	.Ldw_str_begin+2913
	.data.b	234,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2922
	.data.b	67,73,78,84,49,52,78,80,0
	.section	.debug_info		;off: 7316
	.data.w	.Ldw_str_begin+2922
	.data.b	235,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2931
	.data.b	67,73,78,84,49,53,78,80,0
	.section	.debug_info		;off: 7336
	.data.w	.Ldw_str_begin+2931
	.data.b	236,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2940
	.data.b	83,65,82,65,68,67,95,67,73,78,84,78,80,49,95,66,105,116,115,0
	.section	.debug_info		;off: 7357
	.data.w	.Ldw_str_begin+2940
	.data.b	237,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1024

	.data.b	71
	.data.b	241,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2960
	.data.b	82,73,78,84,48,78,80,0
	.section	.debug_info		;off: 7377
	.data.w	.Ldw_str_begin+2960
	.data.b	242,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2968
	.data.b	82,73,78,84,49,78,80,0
	.section	.debug_info		;off: 7397
	.data.w	.Ldw_str_begin+2968
	.data.b	243,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2976
	.data.b	82,73,78,84,50,78,80,0
	.section	.debug_info		;off: 7417
	.data.w	.Ldw_str_begin+2976
	.data.b	244,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2984
	.data.b	82,73,78,84,51,78,80,0
	.section	.debug_info		;off: 7437
	.data.w	.Ldw_str_begin+2984
	.data.b	245,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2992
	.data.b	82,73,78,84,52,78,80,0
	.section	.debug_info		;off: 7457
	.data.w	.Ldw_str_begin+2992
	.data.b	246,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3000
	.data.b	82,73,78,84,53,78,80,0
	.section	.debug_info		;off: 7477
	.data.w	.Ldw_str_begin+3000
	.data.b	247,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3008
	.data.b	82,73,78,84,54,78,80,0
	.section	.debug_info		;off: 7497
	.data.w	.Ldw_str_begin+3008
	.data.b	248,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3016
	.data.b	82,73,78,84,55,78,80,0
	.section	.debug_info		;off: 7517
	.data.w	.Ldw_str_begin+3016
	.data.b	249,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3024
	.data.b	83,65,82,65,68,67,95,82,73,78,84,78,80,48,95,66,105,116,115,0
	.section	.debug_info		;off: 7538
	.data.w	.Ldw_str_begin+3024
	.data.b	250,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1029

	.data.b	71
	.data.b	254,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3044
	.data.b	82,73,78,84,56,78,80,0
	.section	.debug_info		;off: 7558
	.data.w	.Ldw_str_begin+3044
	.data.b	255,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3052
	.data.b	82,73,78,84,57,78,80,0
	.section	.debug_info		;off: 7578
	.data.w	.Ldw_str_begin+3052
	.data.b	128,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3060
	.data.b	82,73,78,84,49,48,78,80,0
	.section	.debug_info		;off: 7598
	.data.w	.Ldw_str_begin+3060
	.data.b	129,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3069
	.data.b	82,73,78,84,49,49,78,80,0
	.section	.debug_info		;off: 7618
	.data.w	.Ldw_str_begin+3069
	.data.b	130,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3078
	.data.b	82,73,78,84,49,50,78,80,0
	.section	.debug_info		;off: 7638
	.data.w	.Ldw_str_begin+3078
	.data.b	131,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3087
	.data.b	82,73,78,84,49,51,78,80,0
	.section	.debug_info		;off: 7658
	.data.w	.Ldw_str_begin+3087
	.data.b	132,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3096
	.data.b	82,73,78,84,49,52,78,80,0
	.section	.debug_info		;off: 7678
	.data.w	.Ldw_str_begin+3096
	.data.b	133,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3105
	.data.b	82,73,78,84,49,53,78,80,0
	.section	.debug_info		;off: 7698
	.data.w	.Ldw_str_begin+3105
	.data.b	134,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3114
	.data.b	83,65,82,65,68,67,95,82,73,78,84,78,80,49,95,66,105,116,115,0
	.section	.debug_info		;off: 7719
	.data.w	.Ldw_str_begin+3114
	.data.b	135,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1034

	.data.b	71
	.data.b	139,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3134
	.data.b	83,73,78,84,48,78,80,0
	.section	.debug_info		;off: 7739
	.data.w	.Ldw_str_begin+3134
	.data.b	140,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3142
	.data.b	83,73,78,84,49,78,80,0
	.section	.debug_info		;off: 7759
	.data.w	.Ldw_str_begin+3142
	.data.b	141,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3150
	.data.b	83,73,78,84,50,78,80,0
	.section	.debug_info		;off: 7779
	.data.w	.Ldw_str_begin+3150
	.data.b	142,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3158
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 7799
	.data.w	.Ldw_str_begin+3158
	.data.b	143,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3170
	.data.b	83,65,82,65,68,67,95,83,73,78,84,78,80,95,66,105,116,115,0
	.section	.debug_info		;off: 7820
	.data.w	.Ldw_str_begin+3170
	.data.b	144,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1039

	.data.b	71
	.data.b	148,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3189
	.data.b	83,65,71,73,78,84,48,0
	.section	.debug_info		;off: 7840
	.data.w	.Ldw_str_begin+3189
	.data.b	149,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3197
	.data.b	83,65,71,73,78,84,49,0
	.section	.debug_info		;off: 7860
	.data.w	.Ldw_str_begin+3197
	.data.b	150,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3205
	.data.b	83,65,71,73,78,84,50,0
	.section	.debug_info		;off: 7880
	.data.w	.Ldw_str_begin+3205
	.data.b	151,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3213
	.data.b	83,65,71,73,78,84,51,0
	.section	.debug_info		;off: 7900
	.data.w	.Ldw_str_begin+3213
	.data.b	152,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3221
	.data.b	114,101,115,101,114,118,101,100,95,52,0
	.section	.debug_info		;off: 7920
	.data.w	.Ldw_str_begin+3221
	.data.b	153,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3232
	.data.b	83,65,83,73,78,84,48,0
	.section	.debug_info		;off: 7940
	.data.w	.Ldw_str_begin+3232
	.data.b	154,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3240
	.data.b	83,65,83,73,78,84,49,0
	.section	.debug_info		;off: 7960
	.data.w	.Ldw_str_begin+3240
	.data.b	155,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3248
	.data.b	83,65,83,73,78,84,50,0
	.section	.debug_info		;off: 7980
	.data.w	.Ldw_str_begin+3248
	.data.b	156,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3256
	.data.b	83,65,83,73,78,84,51,0
	.section	.debug_info		;off: 8000
	.data.w	.Ldw_str_begin+3256
	.data.b	157,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3264
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 8020
	.data.w	.Ldw_str_begin+3264
	.data.b	158,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3276
	.data.b	83,65,82,65,68,67,95,83,84,82,73,73,78,84,95,66,105,116,115,0
	.section	.debug_info		;off: 8041
	.data.w	.Ldw_str_begin+3276
	.data.b	159,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1044

	.data.b	71
	.data.b	163,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3296
	.data.b	65,76,73,65,83,67,72,0
	.section	.debug_info		;off: 8061
	.data.w	.Ldw_str_begin+3296
	.data.b	164,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3304
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 8081
	.data.w	.Ldw_str_begin+3304
	.data.b	165,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	27
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3315
	.data.b	83,65,82,65,68,67,95,65,76,73,65,83,67,72,95,66,105,116,115,0
	.section	.debug_info		;off: 8102
	.data.w	.Ldw_str_begin+3315
	.data.b	166,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1049

	.data.b	71
	.data.b	170,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3335
	.data.b	68,77,65,69,78,48,0
	.section	.debug_info		;off: 8122
	.data.w	.Ldw_str_begin+3335
	.data.b	171,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3342
	.data.b	68,77,65,69,78,49,0
	.section	.debug_info		;off: 8142
	.data.w	.Ldw_str_begin+3342
	.data.b	172,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3349
	.data.b	68,77,65,69,78,50,0
	.section	.debug_info		;off: 8162
	.data.w	.Ldw_str_begin+3349
	.data.b	173,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3356
	.data.b	68,77,65,69,78,51,0
	.section	.debug_info		;off: 8182
	.data.w	.Ldw_str_begin+3356
	.data.b	174,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3363
	.data.b	68,77,65,69,78,52,0
	.section	.debug_info		;off: 8202
	.data.w	.Ldw_str_begin+3363
	.data.b	175,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3370
	.data.b	68,77,65,69,78,53,0
	.section	.debug_info		;off: 8222
	.data.w	.Ldw_str_begin+3370
	.data.b	176,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3377
	.data.b	68,77,65,69,78,54,0
	.section	.debug_info		;off: 8242
	.data.w	.Ldw_str_begin+3377
	.data.b	177,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3384
	.data.b	68,77,65,69,78,55,0
	.section	.debug_info		;off: 8262
	.data.w	.Ldw_str_begin+3384
	.data.b	178,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3391
	.data.b	68,77,65,69,78,56,0
	.section	.debug_info		;off: 8282
	.data.w	.Ldw_str_begin+3391
	.data.b	179,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3398
	.data.b	68,77,65,69,78,57,0
	.section	.debug_info		;off: 8302
	.data.w	.Ldw_str_begin+3398
	.data.b	180,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3405
	.data.b	68,77,65,69,78,49,48,0
	.section	.debug_info		;off: 8322
	.data.w	.Ldw_str_begin+3405
	.data.b	181,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3413
	.data.b	68,77,65,69,78,49,49,0
	.section	.debug_info		;off: 8342
	.data.w	.Ldw_str_begin+3413
	.data.b	182,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3421
	.data.b	68,77,65,69,78,49,50,0
	.section	.debug_info		;off: 8362
	.data.w	.Ldw_str_begin+3421
	.data.b	183,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3429
	.data.b	68,77,65,69,78,49,51,0
	.section	.debug_info		;off: 8382
	.data.w	.Ldw_str_begin+3429
	.data.b	184,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3437
	.data.b	68,77,65,69,78,49,52,0
	.section	.debug_info		;off: 8402
	.data.w	.Ldw_str_begin+3437
	.data.b	185,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3445
	.data.b	68,77,65,69,78,49,53,0
	.section	.debug_info		;off: 8422
	.data.w	.Ldw_str_begin+3445
	.data.b	186,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3453
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 8442
	.data.w	.Ldw_str_begin+3453
	.data.b	187,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3465
	.data.b	83,65,82,65,68,67,95,68,77,65,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 8463
	.data.w	.Ldw_str_begin+3465
	.data.b	188,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1054

	.data.b	71
	.data.b	192,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3483
	.data.b	67,79,77,80,67,82,84,0
	.section	.debug_info		;off: 8483
	.data.w	.Ldw_str_begin+3483
	.data.b	193,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3491
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 8503
	.data.w	.Ldw_str_begin+3491
	.data.b	194,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3502
	.data.b	83,65,82,65,68,67,95,65,78,67,79,78,70,73,71,95,66,105,116,115,0
	.section	.debug_info		;off: 8524
	.data.w	.Ldw_str_begin+3502
	.data.b	195,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1059

	.data.b	71
	.data.b	199,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3523
	.data.b	67,79,85,78,84,0
	.section	.debug_info		;off: 8544
	.data.w	.Ldw_str_begin+3523
	.data.b	200,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3529
	.data.b	69,77,80,84,89,0
	.section	.debug_info		;off: 8564
	.data.w	.Ldw_str_begin+3529
	.data.b	201,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3535
	.data.b	70,85,76,76,0
	.section	.debug_info		;off: 8584
	.data.w	.Ldw_str_begin+3535
	.data.b	202,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3540
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 8604
	.data.w	.Ldw_str_begin+3540
	.data.b	203,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	25
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3551
	.data.b	83,65,82,65,68,67,95,81,70,73,70,79,95,66,105,116,115,0
	.section	.debug_info		;off: 8625
	.data.w	.Ldw_str_begin+3551
	.data.b	204,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1064

	.data.b	71
	.data.b	208,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3569
	.data.b	68,82,70,73,0
	.section	.debug_info		;off: 8645
	.data.w	.Ldw_str_begin+3569
	.data.b	209,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3574
	.data.b	84,82,73,68,70,73,0
	.section	.debug_info		;off: 8665
	.data.w	.Ldw_str_begin+3574
	.data.b	210,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3581
	.data.b	70,84,70,73,0
	.section	.debug_info		;off: 8685
	.data.w	.Ldw_str_begin+3581
	.data.b	211,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3586
	.data.b	71,65,84,69,68,70,73,0
	.section	.debug_info		;off: 8705
	.data.w	.Ldw_str_begin+3586
	.data.b	212,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3594
	.data.b	83,89,78,67,68,70,73,0
	.section	.debug_info		;off: 8725
	.data.w	.Ldw_str_begin+3594
	.data.b	213,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3602
	.data.b	68,65,73,83,89,68,70,73,0
	.section	.debug_info		;off: 8745
	.data.w	.Ldw_str_begin+3602
	.data.b	214,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3611
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 8765
	.data.w	.Ldw_str_begin+3611
	.data.b	215,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3623
	.data.b	83,65,82,65,68,67,95,70,65,85,76,84,73,78,95,66,105,116,115,0
	.section	.debug_info		;off: 8786
	.data.w	.Ldw_str_begin+3623
	.data.b	216,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1069

	.data.b	71
	.data.b	220,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3643
	.data.b	68,82,83,69,0
	.section	.debug_info		;off: 8806
	.data.w	.Ldw_str_begin+3643
	.data.b	221,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3648
	.data.b	84,82,73,68,83,69,0
	.section	.debug_info		;off: 8826
	.data.w	.Ldw_str_begin+3648
	.data.b	222,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3655
	.data.b	68,84,83,69,0
	.section	.debug_info		;off: 8846
	.data.w	.Ldw_str_begin+3655
	.data.b	223,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3660
	.data.b	66,68,83,69,0
	.section	.debug_info		;off: 8866
	.data.w	.Ldw_str_begin+3660
	.data.b	224,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3665
	.data.b	71,65,84,69,68,83,69,0
	.section	.debug_info		;off: 8886
	.data.w	.Ldw_str_begin+3665
	.data.b	225,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3673
	.data.b	83,89,78,67,68,83,69,0
	.section	.debug_info		;off: 8906
	.data.w	.Ldw_str_begin+3673
	.data.b	226,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3681
	.data.b	68,65,73,83,89,68,83,69,0
	.section	.debug_info		;off: 8926
	.data.w	.Ldw_str_begin+3681
	.data.b	227,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3690
	.data.b	68,77,65,76,83,69,0
	.section	.debug_info		;off: 8946
	.data.w	.Ldw_str_begin+3690
	.data.b	228,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3697
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 8966
	.data.w	.Ldw_str_begin+3697
	.data.b	229,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3709
	.data.b	66,69,77,65,83,75,0
	.section	.debug_info		;off: 8986
	.data.w	.Ldw_str_begin+3709
	.data.b	231,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3716
	.data.b	83,65,82,65,68,67,95,83,65,70,69,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 9007
	.data.w	.Ldw_str_begin+3716
	.data.b	236,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1074

	.data.b	71
	.data.b	240,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3735
	.data.b	66,79,85,78,68,65,76,77,0
	.section	.debug_info		;off: 9027
	.data.w	.Ldw_str_begin+3735
	.data.b	241,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3744
	.data.b	68,77,65,84,79,65,76,77,0
	.section	.debug_info		;off: 9047
	.data.w	.Ldw_str_begin+3744
	.data.b	242,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3753
	.data.b	69,65,76,77,0
	.section	.debug_info		;off: 9067
	.data.w	.Ldw_str_begin+3753
	.data.b	243,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3758
	.data.b	83,69,65,76,77,0
	.section	.debug_info		;off: 9087
	.data.w	.Ldw_str_begin+3758
	.data.b	244,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3764
	.data.b	84,82,73,84,79,65,76,77,0
	.section	.debug_info		;off: 9107
	.data.w	.Ldw_str_begin+3764
	.data.b	245,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3773
	.data.b	71,65,84,79,65,76,77,0
	.section	.debug_info		;off: 9127
	.data.w	.Ldw_str_begin+3773
	.data.b	246,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3781
	.data.b	83,89,78,84,79,65,76,77,0
	.section	.debug_info		;off: 9147
	.data.w	.Ldw_str_begin+3781
	.data.b	247,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3790
	.data.b	68,65,73,84,79,65,76,77,0
	.section	.debug_info		;off: 9167
	.data.w	.Ldw_str_begin+3790
	.data.b	248,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3799
	.data.b	65,78,65,67,70,71,65,76,77,0
	.section	.debug_info		;off: 9187
	.data.w	.Ldw_str_begin+3799
	.data.b	249,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3809
	.data.b	65,82,66,67,84,82,76,65,76,77,0
	.section	.debug_info		;off: 9207
	.data.w	.Ldw_str_begin+3809
	.data.b	250,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3820
	.data.b	81,73,78,67,70,71,65,76,77,0
	.section	.debug_info		;off: 9227
	.data.w	.Ldw_str_begin+3820
	.data.b	251,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3830
	.data.b	67,72,67,84,82,76,65,76,77,0
	.section	.debug_info		;off: 9247
	.data.w	.Ldw_str_begin+3830
	.data.b	252,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3840
	.data.b	82,69,83,67,84,82,76,65,76,77,0
	.section	.debug_info		;off: 9267
	.data.w	.Ldw_str_begin+3840
	.data.b	253,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3851
	.data.b	82,69,83,85,76,84,65,76,77,0
	.section	.debug_info		;off: 9287
	.data.w	.Ldw_str_begin+3851
	.data.b	254,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3861
	.data.b	65,78,67,79,78,70,73,71,65,76,77,0
	.section	.debug_info		;off: 9307
	.data.w	.Ldw_str_begin+3861
	.data.b	255,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3873
	.data.b	70,65,85,76,84,73,78,65,76,77,0
	.section	.debug_info		;off: 9327
	.data.w	.Ldw_str_begin+3873
	.data.b	128,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3884
	.data.b	83,65,70,69,69,78,65,76,77,0
	.section	.debug_info		;off: 9347
	.data.w	.Ldw_str_begin+3884
	.data.b	129,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3894
	.data.b	65,76,65,82,77,67,76,82,65,76,77,0
	.section	.debug_info		;off: 9367
	.data.w	.Ldw_str_begin+3894
	.data.b	130,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3906
	.data.b	71,76,79,82,69,83,85,76,84,65,76,77,0
	.section	.debug_info		;off: 9387
	.data.w	.Ldw_str_begin+3906
	.data.b	131,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3919
	.data.b	71,76,79,82,69,83,67,84,82,76,65,76,77,0
	.section	.debug_info		;off: 9407
	.data.w	.Ldw_str_begin+3919
	.data.b	132,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3933
	.data.b	68,77,65,65,76,79,83,69,65,76,77,0
	.section	.debug_info		;off: 9427
	.data.w	.Ldw_str_begin+3933
	.data.b	133,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3945
	.data.b	67,73,78,84,77,83,75,65,76,77,0
	.section	.debug_info		;off: 9447
	.data.w	.Ldw_str_begin+3945
	.data.b	134,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3956
	.data.b	82,73,78,84,77,83,75,65,76,77,0
	.section	.debug_info		;off: 9467
	.data.w	.Ldw_str_begin+3956
	.data.b	135,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3967
	.data.b	83,73,78,84,77,83,75,65,76,77,0
	.section	.debug_info		;off: 9487
	.data.w	.Ldw_str_begin+3967
	.data.b	136,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3978
	.data.b	71,73,78,84,77,83,75,65,76,77,0
	.section	.debug_info		;off: 9507
	.data.w	.Ldw_str_begin+3978
	.data.b	137,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3989
	.data.b	114,101,115,101,114,118,101,100,95,50,53,0
	.section	.debug_info		;off: 9527
	.data.w	.Ldw_str_begin+3989
	.data.b	138,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4001
	.data.b	83,65,82,65,68,67,95,83,65,70,69,65,76,77,95,66,105,116,115,0
	.section	.debug_info		;off: 9548
	.data.w	.Ldw_str_begin+4001
	.data.b	139,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1079

	.data.b	71
	.data.b	143,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4021
	.data.b	68,82,65,76,77,67,0
	.section	.debug_info		;off: 9568
	.data.w	.Ldw_str_begin+4021
	.data.b	144,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4028
	.data.b	83,77,68,65,76,77,67,0
	.section	.debug_info		;off: 9588
	.data.w	.Ldw_str_begin+4028
	.data.b	145,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4036
	.data.b	66,79,85,78,68,65,76,77,67,0
	.section	.debug_info		;off: 9608
	.data.w	.Ldw_str_begin+4036
	.data.b	146,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4046
	.data.b	68,77,65,84,79,65,76,77,67,0
	.section	.debug_info		;off: 9628
	.data.w	.Ldw_str_begin+4046
	.data.b	147,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4056
	.data.b	69,83,69,65,76,77,67,0
	.section	.debug_info		;off: 9648
	.data.w	.Ldw_str_begin+4056
	.data.b	148,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4064
	.data.b	114,101,115,101,114,118,101,100,95,49,48,0
	.section	.debug_info		;off: 9668
	.data.w	.Ldw_str_begin+4064
	.data.b	149,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	22
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4076
	.data.b	83,65,82,65,68,67,95,83,65,70,69,65,76,77,67,76,82,95,66,105,116,115,0
	.section	.debug_info		;off: 9689
	.data.w	.Ldw_str_begin+4076
	.data.b	150,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1084

	.data.b	71
	.data.b	154,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4099
	.data.b	83,65,70,69,66,79,85,78,68,76,0
	.section	.debug_info		;off: 9709
	.data.w	.Ldw_str_begin+4099
	.data.b	155,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4110
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 9729
	.data.w	.Ldw_str_begin+4110
	.data.b	156,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4122
	.data.b	83,65,70,69,66,79,85,78,68,85,0
	.section	.debug_info		;off: 9749
	.data.w	.Ldw_str_begin+4122
	.data.b	157,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4133
	.data.b	114,101,115,101,114,118,101,100,95,50,56,0
	.section	.debug_info		;off: 9769
	.data.w	.Ldw_str_begin+4133
	.data.b	158,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4145
	.data.b	83,65,70,69,66,79,85,78,68,68,82,0
	.section	.debug_info		;off: 9789
	.data.w	.Ldw_str_begin+4145
	.data.b	159,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4157
	.data.b	114,101,115,101,114,118,101,100,95,51,49,0
	.section	.debug_info		;off: 9809
	.data.w	.Ldw_str_begin+4157
	.data.b	160,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4169
	.data.b	83,65,82,65,68,67,95,83,65,70,69,66,79,85,78,68,95,66,105,116,115,0
	.section	.debug_info		;off: 9830
	.data.w	.Ldw_str_begin+4169
	.data.b	161,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1089

	.data.b	71
	.data.b	165,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4191
	.data.b	84,82,73,71,65,84,84,72,82,69,83,0
	.section	.debug_info		;off: 9850
	.data.w	.Ldw_str_begin+4191
	.data.b	166,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4203
	.data.b	83,65,82,65,68,67,95,84,82,73,71,65,84,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 9871
	.data.w	.Ldw_str_begin+4203
	.data.b	167,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1094

	.data.b	71
	.data.b	171,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4227
	.data.b	83,89,78,67,84,72,82,69,83,0
	.section	.debug_info		;off: 9891
	.data.w	.Ldw_str_begin+4227
	.data.b	172,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4237
	.data.b	83,65,82,65,68,67,95,83,89,78,67,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 9912
	.data.w	.Ldw_str_begin+4237
	.data.b	173,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1099

	.data.b	71
	.data.b	177,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4259
	.data.b	68,65,73,83,89,84,72,82,69,83,0
	.section	.debug_info		;off: 9932
	.data.w	.Ldw_str_begin+4259
	.data.b	178,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4270
	.data.b	83,65,82,65,68,67,95,68,65,73,83,89,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 9953
	.data.w	.Ldw_str_begin+4270
	.data.b	179,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1104

	.data.b	71
	.data.b	183,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4293
	.data.b	68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 9973
	.data.w	.Ldw_str_begin+4293
	.data.b	184,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4302
	.data.b	83,65,82,65,68,67,95,68,77,65,84,72,82,69,83,95,66,105,116,115,0
	.section	.debug_info		;off: 9994
	.data.w	.Ldw_str_begin+4302
	.data.b	185,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1109

	.data.b	71
	.data.b	189,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4323
	.data.b	71,73,78,84,0
	.section	.debug_info		;off: 10014
	.data.w	.Ldw_str_begin+4323
	.data.b	190,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4328
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 10034
	.data.w	.Ldw_str_begin+4328
	.data.b	191,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4339
	.data.b	71,67,76,82,0
	.section	.debug_info		;off: 10054
	.data.w	.Ldw_str_begin+4339
	.data.b	192,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4344
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 10074
	.data.w	.Ldw_str_begin+4344
	.data.b	193,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	7
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4355
	.data.b	71,82,73,78,84,78,80,0
	.section	.debug_info		;off: 10094
	.data.w	.Ldw_str_begin+4355
	.data.b	194,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4363
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 10114
	.data.w	.Ldw_str_begin+4363
	.data.b	195,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	10
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4375
	.data.b	71,77,65,83,75,0
	.section	.debug_info		;off: 10134
	.data.w	.Ldw_str_begin+4375
	.data.b	196,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4381
	.data.b	83,65,82,65,68,67,95,71,76,79,73,78,84,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 10155
	.data.w	.Ldw_str_begin+4381
	.data.b	197,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1114

	.data.b	71
	.data.b	201,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4404
	.data.b	71,67,79,78,82,69,83,85,76,84,0
	.section	.debug_info		;off: 10175
	.data.w	.Ldw_str_begin+4404
	.data.b	202,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4415
	.data.b	71,78,85,77,0
	.section	.debug_info		;off: 10195
	.data.w	.Ldw_str_begin+4415
	.data.b	203,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4420
	.data.b	71,67,72,78,85,77,0
	.section	.debug_info		;off: 10215
	.data.w	.Ldw_str_begin+4420
	.data.b	204,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4427
	.data.b	114,101,115,101,114,118,101,100,95,50,53,0
	.section	.debug_info		;off: 10235
	.data.w	.Ldw_str_begin+4427
	.data.b	205,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4439
	.data.b	71,67,79,78,82,69,81,83,0
	.section	.debug_info		;off: 10255
	.data.w	.Ldw_str_begin+4439
	.data.b	206,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4448
	.data.b	114,101,115,101,114,118,101,100,95,51,48,0
	.section	.debug_info		;off: 10275
	.data.w	.Ldw_str_begin+4448
	.data.b	207,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4460
	.data.b	71,86,70,76,65,71,0
	.section	.debug_info		;off: 10295
	.data.w	.Ldw_str_begin+4460
	.data.b	208,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4467
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,85,76,84,95,66,105,116,115,0
	.section	.debug_info		;off: 10316
	.data.w	.Ldw_str_begin+4467
	.data.b	209,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1119

	.data.b	71
	.data.b	213,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4489
	.data.b	71,67,79,78,82,69,83,85,76,84,0
	.section	.debug_info		;off: 10336
	.data.w	.Ldw_str_begin+4489
	.data.b	214,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4500
	.data.b	71,78,85,77,0
	.section	.debug_info		;off: 10356
	.data.w	.Ldw_str_begin+4500
	.data.b	215,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	12
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4505
	.data.b	71,67,72,78,85,77,0
	.section	.debug_info		;off: 10376
	.data.w	.Ldw_str_begin+4505
	.data.b	216,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	7
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4512
	.data.b	114,101,115,101,114,118,101,100,95,50,53,0
	.section	.debug_info		;off: 10396
	.data.w	.Ldw_str_begin+4512
	.data.b	217,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4524
	.data.b	71,67,79,78,82,69,81,83,0
	.section	.debug_info		;off: 10416
	.data.w	.Ldw_str_begin+4524
	.data.b	218,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	2
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4533
	.data.b	114,101,115,101,114,118,101,100,95,51,48,0
	.section	.debug_info		;off: 10436
	.data.w	.Ldw_str_begin+4533
	.data.b	219,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4545
	.data.b	71,86,70,76,65,71,0
	.section	.debug_info		;off: 10456
	.data.w	.Ldw_str_begin+4545
	.data.b	220,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4552
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,85,76,84,68,95,66,105,116,115,0
	.section	.debug_info		;off: 10477
	.data.w	.Ldw_str_begin+4552
	.data.b	221,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1124

	.data.b	71
	.data.b	225,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4575
	.data.b	71,82,69,83,65,76,73,0
	.section	.debug_info		;off: 10497
	.data.w	.Ldw_str_begin+4575
	.data.b	226,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4583
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 10517
	.data.w	.Ldw_str_begin+4583
	.data.b	227,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4594
	.data.b	71,87,70,82,77,79,68,69,0
	.section	.debug_info		;off: 10537
	.data.w	.Ldw_str_begin+4594
	.data.b	228,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4603
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 10557
	.data.w	.Ldw_str_begin+4603
	.data.b	229,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4614
	.data.b	71,78,82,73,78,84,69,78,0
	.section	.debug_info		;off: 10577
	.data.w	.Ldw_str_begin+4614
	.data.b	230,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4623
	.data.b	114,101,115,101,114,118,101,100,95,57,0
	.section	.debug_info		;off: 10597
	.data.w	.Ldw_str_begin+4623
	.data.b	231,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	23
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4634
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,67,84,82,76,95,66,105,116,115,0
	.section	.debug_info		;off: 10618
	.data.w	.Ldw_str_begin+4634
	.data.b	232,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1129

	.data.b	71
	.data.b	236,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4657
	.data.b	71,68,77,65,69,78,0
	.section	.debug_info		;off: 10638
	.data.w	.Ldw_str_begin+4657
	.data.b	237,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4664
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 10658
	.data.w	.Ldw_str_begin+4664
	.data.b	238,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4675
	.data.b	83,65,82,65,68,67,95,71,76,79,68,77,65,95,66,105,116,115,0
	.section	.debug_info		;off: 10679
	.data.w	.Ldw_str_begin+4675
	.data.b	239,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1134

	.data.b	71
	.data.b	243,4
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4694
	.data.b	71,66,79,85,78,68,76,0
	.section	.debug_info		;off: 10699
	.data.w	.Ldw_str_begin+4694
	.data.b	244,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4702
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 10719
	.data.w	.Ldw_str_begin+4702
	.data.b	245,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	16
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4714
	.data.b	71,66,79,85,78,68,85,0
	.section	.debug_info		;off: 10739
	.data.w	.Ldw_str_begin+4714
	.data.b	246,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	4
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 4722
	.data.b	114,101,115,101,114,118,101,100,95,50,56,0
	.section	.debug_info		;off: 10759
	.data.w	.Ldw_str_begin+4722
	.data.b	247,4
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+922
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4734
	.data.b	83,65,82,65,68,67,95,71,76,79,70,85,78,66,79,85,78,68,95,66,105,116,115,0
	.section	.debug_info		;off: 10780
	.data.w	.Ldw_str_begin+4734
	.data.b	248,4
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1139

	.data.b	73
	.data.b	130,5
	.data.b	1
	.data.b	36
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

	.section	.debug_info		;off: 10799
	.data.b	40
	.section	.debug_str		;off: 4758
	.data.b	85,0
	.section	.debug_info		;off: 10800
	.data.w	.Ldw_str_begin+4758
	.data.b	131,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4760
	.data.b	66,0
	.section	.debug_info		;off: 10817
	.data.w	.Ldw_str_begin+4760
	.data.b	132,5
	.data.b	27
	.data.b	36
	.data.w	.Ldw_begin+2642
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4762
	.data.b	83,65,82,65,68,67,95,81,50,84,82,73,67,84,82,76,0
	.section	.debug_info		;off: 10835
	.data.w	.Ldw_str_begin+4762
	.data.b	133,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+10792

	.data.b	73
	.data.b	137,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4779
	.data.b	85,0
	.section	.debug_info		;off: 10855
	.data.w	.Ldw_str_begin+4779
	.data.b	138,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4781
	.data.b	66,0
	.section	.debug_info		;off: 10872
	.data.w	.Ldw_str_begin+4781
	.data.b	139,5
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+2851
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4783
	.data.b	83,65,82,65,68,67,95,65,78,65,67,70,71,0
	.section	.debug_info		;off: 10890
	.data.w	.Ldw_str_begin+4783
	.data.b	140,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+10847

	.data.b	73
	.data.b	144,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4797
	.data.b	85,0
	.section	.debug_info		;off: 10910
	.data.w	.Ldw_str_begin+4797
	.data.b	145,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4799
	.data.b	66,0
	.section	.debug_info		;off: 10927
	.data.w	.Ldw_str_begin+4799
	.data.b	146,5
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+3402
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4801
	.data.b	83,65,82,65,68,67,95,65,82,66,67,84,82,76,0
	.section	.debug_info		;off: 10945
	.data.w	.Ldw_str_begin+4801
	.data.b	147,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+10902

	.data.b	73
	.data.b	151,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4816
	.data.b	85,0
	.section	.debug_info		;off: 10965
	.data.w	.Ldw_str_begin+4816
	.data.b	152,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4818
	.data.b	66,0
	.section	.debug_info		;off: 10982
	.data.w	.Ldw_str_begin+4818
	.data.b	153,5
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+3459
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4820
	.data.b	83,65,82,65,68,67,95,83,65,77,67,84,82,76,0
	.section	.debug_info		;off: 11000
	.data.w	.Ldw_str_begin+4820
	.data.b	154,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+10957

	.data.b	73
	.data.b	158,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4835
	.data.b	85,0
	.section	.debug_info		;off: 11020
	.data.w	.Ldw_str_begin+4835
	.data.b	159,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4837
	.data.b	66,0
	.section	.debug_info		;off: 11037
	.data.w	.Ldw_str_begin+4837
	.data.b	160,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+3554
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4839
	.data.b	83,65,82,65,68,67,95,70,85,78,66,79,85,78,68,0
	.section	.debug_info		;off: 11055
	.data.w	.Ldw_str_begin+4839
	.data.b	161,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11012

	.data.b	73
	.data.b	165,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4855
	.data.b	85,0
	.section	.debug_info		;off: 11075
	.data.w	.Ldw_str_begin+4855
	.data.b	166,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4857
	.data.b	66,0
	.section	.debug_info		;off: 11092
	.data.w	.Ldw_str_begin+4857
	.data.b	167,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+3687
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4859
	.data.b	83,65,82,65,68,67,95,83,89,78,67,67,84,82,76,0
	.section	.debug_info		;off: 11110
	.data.w	.Ldw_str_begin+4859
	.data.b	168,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11067

	.data.b	73
	.data.b	172,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4875
	.data.b	85,0
	.section	.debug_info		;off: 11130
	.data.w	.Ldw_str_begin+4875
	.data.b	173,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4877
	.data.b	66,0
	.section	.debug_info		;off: 11147
	.data.w	.Ldw_str_begin+4877
	.data.b	174,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+3921
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4879
	.data.b	83,65,82,65,68,67,95,81,84,82,73,67,84,82,76,0
	.section	.debug_info		;off: 11165
	.data.w	.Ldw_str_begin+4879
	.data.b	175,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11122

	.data.b	73
	.data.b	179,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4895
	.data.b	85,0
	.section	.debug_info		;off: 11185
	.data.w	.Ldw_str_begin+4895
	.data.b	180,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4897
	.data.b	66,0
	.section	.debug_info		;off: 11202
	.data.w	.Ldw_str_begin+4897
	.data.b	181,5
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+4102
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4899
	.data.b	83,65,82,65,68,67,95,81,77,79,68,69,0
	.section	.debug_info		;off: 11220
	.data.w	.Ldw_str_begin+4899
	.data.b	182,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11177

	.data.b	73
	.data.b	186,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4912
	.data.b	85,0
	.section	.debug_info		;off: 11240
	.data.w	.Ldw_str_begin+4912
	.data.b	187,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4914
	.data.b	66,0
	.section	.debug_info		;off: 11257
	.data.w	.Ldw_str_begin+4914
	.data.b	188,5
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+4363
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4916
	.data.b	83,65,82,65,68,67,95,81,73,78,67,70,71,0
	.section	.debug_info		;off: 11275
	.data.w	.Ldw_str_begin+4916
	.data.b	189,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11232

	.data.b	73
	.data.b	193,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4930
	.data.b	85,0
	.section	.debug_info		;off: 11295
	.data.w	.Ldw_str_begin+4930
	.data.b	194,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4932
	.data.b	66,0
	.section	.debug_info		;off: 11312
	.data.w	.Ldw_str_begin+4932
	.data.b	195,5
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+4504
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4934
	.data.b	83,65,82,65,68,67,95,81,82,69,81,84,77,0
	.section	.debug_info		;off: 11330
	.data.w	.Ldw_str_begin+4934
	.data.b	196,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11287

	.data.b	73
	.data.b	200,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4948
	.data.b	85,0
	.section	.debug_info		;off: 11350
	.data.w	.Ldw_str_begin+4948
	.data.b	201,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4950
	.data.b	66,0
	.section	.debug_info		;off: 11367
	.data.w	.Ldw_str_begin+4950
	.data.b	202,5
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+4865
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4952
	.data.b	83,65,82,65,68,67,95,67,72,67,84,82,76,0
	.section	.debug_info		;off: 11385
	.data.w	.Ldw_str_begin+4952
	.data.b	203,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11342

	.data.b	73
	.data.b	207,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4966
	.data.b	85,0
	.section	.debug_info		;off: 11405
	.data.w	.Ldw_str_begin+4966
	.data.b	208,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4968
	.data.b	66,0
	.section	.debug_info		;off: 11422
	.data.w	.Ldw_str_begin+4968
	.data.b	209,5
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+5006
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4970
	.data.b	83,65,82,65,68,67,95,82,69,83,67,84,82,76,0
	.section	.debug_info		;off: 11440
	.data.w	.Ldw_str_begin+4970
	.data.b	210,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11397

	.data.b	73
	.data.b	214,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4985
	.data.b	85,0
	.section	.debug_info		;off: 11460
	.data.w	.Ldw_str_begin+4985
	.data.b	215,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4987
	.data.b	66,0
	.section	.debug_info		;off: 11477
	.data.w	.Ldw_str_begin+4987
	.data.b	216,5
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+5147
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4989
	.data.b	83,65,82,65,68,67,95,82,69,83,85,76,84,0
	.section	.debug_info		;off: 11495
	.data.w	.Ldw_str_begin+4989
	.data.b	217,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11452

	.data.b	73
	.data.b	221,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5003
	.data.b	85,0
	.section	.debug_info		;off: 11515
	.data.w	.Ldw_str_begin+5003
	.data.b	222,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5005
	.data.b	66,0
	.section	.debug_info		;off: 11532
	.data.w	.Ldw_str_begin+5005
	.data.b	223,5
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+5288
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5007
	.data.b	83,65,82,65,68,67,95,82,69,83,85,76,84,68,0
	.section	.debug_info		;off: 11550
	.data.w	.Ldw_str_begin+5007
	.data.b	224,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11507

	.data.b	73
	.data.b	228,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5022
	.data.b	85,0
	.section	.debug_info		;off: 11570
	.data.w	.Ldw_str_begin+5022
	.data.b	229,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5024
	.data.b	66,0
	.section	.debug_info		;off: 11587
	.data.w	.Ldw_str_begin+5024
	.data.b	230,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+5669
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5026
	.data.b	83,65,82,65,68,67,95,67,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 11605
	.data.w	.Ldw_str_begin+5026
	.data.b	231,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11562

	.data.b	73
	.data.b	235,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5042
	.data.b	85,0
	.section	.debug_info		;off: 11625
	.data.w	.Ldw_str_begin+5042
	.data.b	236,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5044
	.data.b	66,0
	.section	.debug_info		;off: 11642
	.data.w	.Ldw_str_begin+5044
	.data.b	237,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+6050
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5046
	.data.b	83,65,82,65,68,67,95,82,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 11660
	.data.w	.Ldw_str_begin+5046
	.data.b	238,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11617

	.data.b	73
	.data.b	242,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5062
	.data.b	85,0
	.section	.debug_info		;off: 11680
	.data.w	.Ldw_str_begin+5062
	.data.b	243,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5064
	.data.b	66,0
	.section	.debug_info		;off: 11697
	.data.w	.Ldw_str_begin+5064
	.data.b	244,5
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+6171
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5066
	.data.b	83,65,82,65,68,67,95,83,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 11715
	.data.w	.Ldw_str_begin+5066
	.data.b	245,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11672

	.data.b	73
	.data.b	249,5
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5082
	.data.b	85,0
	.section	.debug_info		;off: 11735
	.data.w	.Ldw_str_begin+5082
	.data.b	250,5
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5084
	.data.b	66,0
	.section	.debug_info		;off: 11752
	.data.w	.Ldw_str_begin+5084
	.data.b	251,5
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+6532
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5086
	.data.b	83,65,82,65,68,67,95,67,73,78,84,67,76,82,0
	.section	.debug_info		;off: 11770
	.data.w	.Ldw_str_begin+5086
	.data.b	252,5
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11727

	.data.b	73
	.data.b	128,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5101
	.data.b	85,0
	.section	.debug_info		;off: 11790
	.data.w	.Ldw_str_begin+5101
	.data.b	129,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5103
	.data.b	66,0
	.section	.debug_info		;off: 11807
	.data.w	.Ldw_str_begin+5103
	.data.b	130,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+6893
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5105
	.data.b	83,65,82,65,68,67,95,82,73,78,84,67,76,82,0
	.section	.debug_info		;off: 11825
	.data.w	.Ldw_str_begin+5105
	.data.b	131,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11782

	.data.b	73
	.data.b	135,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5120
	.data.b	85,0
	.section	.debug_info		;off: 11845
	.data.w	.Ldw_str_begin+5120
	.data.b	136,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5122
	.data.b	66,0
	.section	.debug_info		;off: 11862
	.data.w	.Ldw_str_begin+5122
	.data.b	137,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+6994
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5124
	.data.b	83,65,82,65,68,67,95,83,73,78,84,67,76,82,0
	.section	.debug_info		;off: 11880
	.data.w	.Ldw_str_begin+5124
	.data.b	138,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11837

	.data.b	73
	.data.b	142,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5139
	.data.b	85,0
	.section	.debug_info		;off: 11900
	.data.w	.Ldw_str_begin+5139
	.data.b	143,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5141
	.data.b	66,0
	.section	.debug_info		;off: 11917
	.data.w	.Ldw_str_begin+5141
	.data.b	144,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+7175
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5143
	.data.b	83,65,82,65,68,67,95,67,73,78,84,78,80,48,0
	.section	.debug_info		;off: 11935
	.data.w	.Ldw_str_begin+5143
	.data.b	145,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11892

	.data.b	73
	.data.b	149,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5158
	.data.b	85,0
	.section	.debug_info		;off: 11955
	.data.w	.Ldw_str_begin+5158
	.data.b	150,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5160
	.data.b	66,0
	.section	.debug_info		;off: 11972
	.data.w	.Ldw_str_begin+5160
	.data.b	151,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+7356
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5162
	.data.b	83,65,82,65,68,67,95,67,73,78,84,78,80,49,0
	.section	.debug_info		;off: 11990
	.data.w	.Ldw_str_begin+5162
	.data.b	152,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+11947

	.data.b	73
	.data.b	156,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5177
	.data.b	85,0
	.section	.debug_info		;off: 12010
	.data.w	.Ldw_str_begin+5177
	.data.b	157,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5179
	.data.b	66,0
	.section	.debug_info		;off: 12027
	.data.w	.Ldw_str_begin+5179
	.data.b	158,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+7537
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5181
	.data.b	83,65,82,65,68,67,95,82,73,78,84,78,80,48,0
	.section	.debug_info		;off: 12045
	.data.w	.Ldw_str_begin+5181
	.data.b	159,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12002

	.data.b	73
	.data.b	163,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5196
	.data.b	85,0
	.section	.debug_info		;off: 12065
	.data.w	.Ldw_str_begin+5196
	.data.b	164,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5198
	.data.b	66,0
	.section	.debug_info		;off: 12082
	.data.w	.Ldw_str_begin+5198
	.data.b	165,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+7718
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5200
	.data.b	83,65,82,65,68,67,95,82,73,78,84,78,80,49,0
	.section	.debug_info		;off: 12100
	.data.w	.Ldw_str_begin+5200
	.data.b	166,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12057

	.data.b	73
	.data.b	170,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5215
	.data.b	85,0
	.section	.debug_info		;off: 12120
	.data.w	.Ldw_str_begin+5215
	.data.b	171,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5217
	.data.b	66,0
	.section	.debug_info		;off: 12137
	.data.w	.Ldw_str_begin+5217
	.data.b	172,6
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+7819
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5219
	.data.b	83,65,82,65,68,67,95,83,73,78,84,78,80,0
	.section	.debug_info		;off: 12155
	.data.w	.Ldw_str_begin+5219
	.data.b	173,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12112

	.data.b	73
	.data.b	177,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5233
	.data.b	85,0
	.section	.debug_info		;off: 12175
	.data.w	.Ldw_str_begin+5233
	.data.b	178,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5235
	.data.b	66,0
	.section	.debug_info		;off: 12192
	.data.w	.Ldw_str_begin+5235
	.data.b	179,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+8040
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5237
	.data.b	83,65,82,65,68,67,95,83,84,82,73,73,78,84,0
	.section	.debug_info		;off: 12210
	.data.w	.Ldw_str_begin+5237
	.data.b	180,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12167

	.data.b	73
	.data.b	184,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5252
	.data.b	85,0
	.section	.debug_info		;off: 12230
	.data.w	.Ldw_str_begin+5252
	.data.b	185,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5254
	.data.b	66,0
	.section	.debug_info		;off: 12247
	.data.w	.Ldw_str_begin+5254
	.data.b	186,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+8101
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5256
	.data.b	83,65,82,65,68,67,95,65,76,73,65,83,67,72,0
	.section	.debug_info		;off: 12265
	.data.w	.Ldw_str_begin+5256
	.data.b	187,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12222

	.data.b	73
	.data.b	191,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5271
	.data.b	85,0
	.section	.debug_info		;off: 12285
	.data.w	.Ldw_str_begin+5271
	.data.b	192,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5273
	.data.b	66,0
	.section	.debug_info		;off: 12302
	.data.w	.Ldw_str_begin+5273
	.data.b	193,6
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+8462
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5275
	.data.b	83,65,82,65,68,67,95,68,77,65,69,78,0
	.section	.debug_info		;off: 12320
	.data.w	.Ldw_str_begin+5275
	.data.b	194,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12277

	.data.b	73
	.data.b	198,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5288
	.data.b	85,0
	.section	.debug_info		;off: 12340
	.data.w	.Ldw_str_begin+5288
	.data.b	199,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5290
	.data.b	66,0
	.section	.debug_info		;off: 12357
	.data.w	.Ldw_str_begin+5290
	.data.b	200,6
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+8523
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5292
	.data.b	83,65,82,65,68,67,95,65,78,67,79,78,70,73,71,0
	.section	.debug_info		;off: 12375
	.data.w	.Ldw_str_begin+5292
	.data.b	201,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12332

	.data.b	73
	.data.b	205,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5308
	.data.b	85,0
	.section	.debug_info		;off: 12395
	.data.w	.Ldw_str_begin+5308
	.data.b	206,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5310
	.data.b	66,0
	.section	.debug_info		;off: 12412
	.data.w	.Ldw_str_begin+5310
	.data.b	207,6
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+8624
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5312
	.data.b	83,65,82,65,68,67,95,81,70,73,70,79,0
	.section	.debug_info		;off: 12430
	.data.w	.Ldw_str_begin+5312
	.data.b	208,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12387

	.data.b	73
	.data.b	212,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5325
	.data.b	85,0
	.section	.debug_info		;off: 12450
	.data.w	.Ldw_str_begin+5325
	.data.b	213,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5327
	.data.b	66,0
	.section	.debug_info		;off: 12467
	.data.w	.Ldw_str_begin+5327
	.data.b	214,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+8785
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5329
	.data.b	83,65,82,65,68,67,95,70,65,85,76,84,73,78,0
	.section	.debug_info		;off: 12485
	.data.w	.Ldw_str_begin+5329
	.data.b	215,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12442

	.data.b	73
	.data.b	219,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5344
	.data.b	85,0
	.section	.debug_info		;off: 12505
	.data.w	.Ldw_str_begin+5344
	.data.b	220,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5346
	.data.b	66,0
	.section	.debug_info		;off: 12522
	.data.w	.Ldw_str_begin+5346
	.data.b	221,6
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+9006
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5348
	.data.b	83,65,82,65,68,67,95,83,65,70,69,69,78,0
	.section	.debug_info		;off: 12540
	.data.w	.Ldw_str_begin+5348
	.data.b	222,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12497

	.data.b	73
	.data.b	226,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5362
	.data.b	85,0
	.section	.debug_info		;off: 12560
	.data.w	.Ldw_str_begin+5362
	.data.b	227,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5364
	.data.b	66,0
	.section	.debug_info		;off: 12577
	.data.w	.Ldw_str_begin+5364
	.data.b	228,6
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+9547
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5366
	.data.b	83,65,82,65,68,67,95,83,65,70,69,65,76,77,0
	.section	.debug_info		;off: 12595
	.data.w	.Ldw_str_begin+5366
	.data.b	229,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12552

	.data.b	73
	.data.b	233,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5381
	.data.b	85,0
	.section	.debug_info		;off: 12615
	.data.w	.Ldw_str_begin+5381
	.data.b	234,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5383
	.data.b	66,0
	.section	.debug_info		;off: 12632
	.data.w	.Ldw_str_begin+5383
	.data.b	235,6
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+9688
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5385
	.data.b	83,65,82,65,68,67,95,83,65,70,69,65,76,77,67,76,82,0
	.section	.debug_info		;off: 12650
	.data.w	.Ldw_str_begin+5385
	.data.b	236,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12607

	.data.b	73
	.data.b	240,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5403
	.data.b	85,0
	.section	.debug_info		;off: 12670
	.data.w	.Ldw_str_begin+5403
	.data.b	241,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5405
	.data.b	66,0
	.section	.debug_info		;off: 12687
	.data.w	.Ldw_str_begin+5405
	.data.b	242,6
	.data.b	27
	.data.b	36
	.data.w	.Ldw_begin+9829
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5407
	.data.b	83,65,82,65,68,67,95,83,65,70,69,66,79,85,78,68,0
	.section	.debug_info		;off: 12705
	.data.w	.Ldw_str_begin+5407
	.data.b	243,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12662

	.data.b	73
	.data.b	247,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5424
	.data.b	85,0
	.section	.debug_info		;off: 12725
	.data.w	.Ldw_str_begin+5424
	.data.b	248,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5426
	.data.b	66,0
	.section	.debug_info		;off: 12742
	.data.w	.Ldw_str_begin+5426
	.data.b	249,6
	.data.b	29
	.data.b	36
	.data.w	.Ldw_begin+9870
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5428
	.data.b	83,65,82,65,68,67,95,84,82,73,71,65,84,84,72,82,69,83,0
	.section	.debug_info		;off: 12760
	.data.w	.Ldw_str_begin+5428
	.data.b	250,6
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12717

	.data.b	73
	.data.b	254,6
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5447
	.data.b	85,0
	.section	.debug_info		;off: 12780
	.data.w	.Ldw_str_begin+5447
	.data.b	255,6
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5449
	.data.b	66,0
	.section	.debug_info		;off: 12797
	.data.w	.Ldw_str_begin+5449
	.data.b	128,7
	.data.b	27
	.data.b	36
	.data.w	.Ldw_begin+9911
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5451
	.data.b	83,65,82,65,68,67,95,83,89,78,67,84,72,82,69,83,0
	.section	.debug_info		;off: 12815
	.data.w	.Ldw_str_begin+5451
	.data.b	129,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12772

	.data.b	73
	.data.b	133,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5468
	.data.b	85,0
	.section	.debug_info		;off: 12835
	.data.w	.Ldw_str_begin+5468
	.data.b	134,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5470
	.data.b	66,0
	.section	.debug_info		;off: 12852
	.data.w	.Ldw_str_begin+5470
	.data.b	135,7
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+9952
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5472
	.data.b	83,65,82,65,68,67,95,68,65,73,83,89,84,72,82,69,83,0
	.section	.debug_info		;off: 12870
	.data.w	.Ldw_str_begin+5472
	.data.b	136,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12827

	.data.b	73
	.data.b	140,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5490
	.data.b	85,0
	.section	.debug_info		;off: 12890
	.data.w	.Ldw_str_begin+5490
	.data.b	141,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5492
	.data.b	66,0
	.section	.debug_info		;off: 12907
	.data.w	.Ldw_str_begin+5492
	.data.b	142,7
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+9993
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5494
	.data.b	83,65,82,65,68,67,95,68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 12925
	.data.w	.Ldw_str_begin+5494
	.data.b	143,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12882

	.data.b	73
	.data.b	147,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5510
	.data.b	85,0
	.section	.debug_info		;off: 12945
	.data.w	.Ldw_str_begin+5510
	.data.b	148,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5512
	.data.b	66,0
	.section	.debug_info		;off: 12962
	.data.w	.Ldw_str_begin+5512
	.data.b	149,7
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+10154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5514
	.data.b	83,65,82,65,68,67,95,71,76,79,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 12980
	.data.w	.Ldw_str_begin+5514
	.data.b	150,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12937

	.data.b	73
	.data.b	154,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5532
	.data.b	85,0
	.section	.debug_info		;off: 13000
	.data.w	.Ldw_str_begin+5532
	.data.b	155,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5534
	.data.b	66,0
	.section	.debug_info		;off: 13017
	.data.w	.Ldw_str_begin+5534
	.data.b	156,7
	.data.b	27
	.data.b	36
	.data.w	.Ldw_begin+10315
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5536
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,85,76,84,0
	.section	.debug_info		;off: 13035
	.data.w	.Ldw_str_begin+5536
	.data.b	157,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+12992

	.data.b	73
	.data.b	161,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5553
	.data.b	85,0
	.section	.debug_info		;off: 13055
	.data.w	.Ldw_str_begin+5553
	.data.b	162,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5555
	.data.b	66,0
	.section	.debug_info		;off: 13072
	.data.w	.Ldw_str_begin+5555
	.data.b	163,7
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+10476
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5557
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,85,76,84,68,0
	.section	.debug_info		;off: 13090
	.data.w	.Ldw_str_begin+5557
	.data.b	164,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+13047

	.data.b	73
	.data.b	168,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5575
	.data.b	85,0
	.section	.debug_info		;off: 13110
	.data.w	.Ldw_str_begin+5575
	.data.b	169,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5577
	.data.b	66,0
	.section	.debug_info		;off: 13127
	.data.w	.Ldw_str_begin+5577
	.data.b	170,7
	.data.b	28
	.data.b	36
	.data.w	.Ldw_begin+10617
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5579
	.data.b	83,65,82,65,68,67,95,71,76,79,82,69,83,67,84,82,76,0
	.section	.debug_info		;off: 13145
	.data.w	.Ldw_str_begin+5579
	.data.b	171,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+13102

	.data.b	73
	.data.b	175,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5597
	.data.b	85,0
	.section	.debug_info		;off: 13165
	.data.w	.Ldw_str_begin+5597
	.data.b	176,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5599
	.data.b	66,0
	.section	.debug_info		;off: 13182
	.data.w	.Ldw_str_begin+5599
	.data.b	177,7
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+10678
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5601
	.data.b	83,65,82,65,68,67,95,71,76,79,68,77,65,0
	.section	.debug_info		;off: 13200
	.data.w	.Ldw_str_begin+5601
	.data.b	178,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+13157

	.data.b	73
	.data.b	182,7
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5615
	.data.b	85,0
	.section	.debug_info		;off: 13220
	.data.w	.Ldw_str_begin+5615
	.data.b	183,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5617
	.data.b	66,0
	.section	.debug_info		;off: 13237
	.data.w	.Ldw_str_begin+5617
	.data.b	184,7
	.data.b	29
	.data.b	36
	.data.w	.Ldw_begin+10779
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5619
	.data.b	83,65,82,65,68,67,95,71,76,79,70,85,78,66,79,85,78,68,0
	.section	.debug_info		;off: 13255
	.data.w	.Ldw_str_begin+5619
	.data.b	185,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+13212

	.data.b	71
	.data.b	193,7
	.data.b	1
	.data.b	36
	.data.b	152,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5638
	.data.b	81,50,84,82,73,67,84,82,76,0
	.section	.debug_info		;off: 13276
	.data.w	.Ldw_str_begin+5638
	.data.b	194,7
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+10834
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5648
	.data.b	65,78,65,67,70,71,0
	.section	.debug_info		;off: 13293
	.data.w	.Ldw_str_begin+5648
	.data.b	195,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+10889
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5655
	.data.b	65,82,66,67,84,82,76,0
	.section	.debug_info		;off: 13310
	.data.w	.Ldw_str_begin+5655
	.data.b	196,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+10944
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5663
	.data.b	83,65,77,67,84,82,76,0
	.section	.debug_info		;off: 13327
	.data.w	.Ldw_str_begin+5663
	.data.b	197,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+10999
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5671
	.data.b	70,85,78,66,79,85,78,68,0
	.section	.debug_info		;off: 13344
	.data.w	.Ldw_str_begin+5671
	.data.b	198,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+11054
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5680
	.data.b	83,89,78,67,67,84,82,76,0
	.section	.debug_info		;off: 13361
	.data.w	.Ldw_str_begin+5680
	.data.b	199,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+11109
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5689
	.data.b	81,84,82,73,67,84,82,76,0
	.section	.debug_info		;off: 13378
	.data.w	.Ldw_str_begin+5689
	.data.b	200,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+1144
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5698
	.data.b	81,77,79,68,69,0
	.section	.debug_info		;off: 13395
	.data.w	.Ldw_str_begin+5698
	.data.b	201,7
	.data.b	18
	.data.b	36
	.data.w	.Ldw_begin+1160
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5704
	.data.b	81,73,78,67,70,71,0
	.section	.debug_info		;off: 13412
	.data.w	.Ldw_str_begin+5704
	.data.b	202,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+1176
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5711
	.data.b	81,82,69,81,84,77,0
	.section	.debug_info		;off: 13429
	.data.w	.Ldw_str_begin+5711
	.data.b	203,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+1192
	.data.b	2,35
	.data.b	60
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5718
	.data.b	67,72,67,84,82,76,0
	.section	.debug_info		;off: 13446
	.data.w	.Ldw_str_begin+5718
	.data.b	204,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+1208
	.data.b	2,35
	.data.b	72
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5725
	.data.b	82,69,83,67,84,82,76,0
	.section	.debug_info		;off: 13463
	.data.w	.Ldw_str_begin+5725
	.data.b	205,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+1224
	.data.b	3,35
	.data.b	136,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5733
	.data.b	82,69,83,85,76,84,0
	.section	.debug_info		;off: 13481
	.data.w	.Ldw_str_begin+5733
	.data.b	206,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+1240
	.data.b	3,35
	.data.b	200,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5740
	.data.b	82,69,83,85,76,84,68,0
	.section	.debug_info		;off: 13499
	.data.w	.Ldw_str_begin+5740
	.data.b	207,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+1256
	.data.b	3,35
	.data.b	136,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5748
	.data.b	67,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 13517
	.data.w	.Ldw_str_begin+5748
	.data.b	208,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+11604
	.data.b	3,35
	.data.b	200,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5757
	.data.b	82,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 13535
	.data.w	.Ldw_str_begin+5757
	.data.b	209,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+11659
	.data.b	3,35
	.data.b	204,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5766
	.data.b	83,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 13553
	.data.w	.Ldw_str_begin+5766
	.data.b	210,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+11714
	.data.b	3,35
	.data.b	208,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5775
	.data.b	67,73,78,84,67,76,82,0
	.section	.debug_info		;off: 13571
	.data.w	.Ldw_str_begin+5775
	.data.b	211,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+11769
	.data.b	3,35
	.data.b	212,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5783
	.data.b	82,73,78,84,67,76,82,0
	.section	.debug_info		;off: 13589
	.data.w	.Ldw_str_begin+5783
	.data.b	212,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+11824
	.data.b	3,35
	.data.b	216,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5791
	.data.b	83,73,78,84,67,76,82,0
	.section	.debug_info		;off: 13607
	.data.w	.Ldw_str_begin+5791
	.data.b	213,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+11879
	.data.b	3,35
	.data.b	220,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5799
	.data.b	67,73,78,84,78,80,48,0
	.section	.debug_info		;off: 13625
	.data.w	.Ldw_str_begin+5799
	.data.b	214,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+11934
	.data.b	3,35
	.data.b	224,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5807
	.data.b	67,73,78,84,78,80,49,0
	.section	.debug_info		;off: 13643
	.data.w	.Ldw_str_begin+5807
	.data.b	215,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+11989
	.data.b	3,35
	.data.b	228,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5815
	.data.b	82,73,78,84,78,80,48,0
	.section	.debug_info		;off: 13661
	.data.w	.Ldw_str_begin+5815
	.data.b	216,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12044
	.data.b	3,35
	.data.b	232,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5823
	.data.b	82,73,78,84,78,80,49,0
	.section	.debug_info		;off: 13679
	.data.w	.Ldw_str_begin+5823
	.data.b	217,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12099
	.data.b	3,35
	.data.b	236,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5831
	.data.b	83,73,78,84,78,80,0
	.section	.debug_info		;off: 13697
	.data.w	.Ldw_str_begin+5831
	.data.b	218,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+12154
	.data.b	3,35
	.data.b	240,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5838
	.data.b	83,84,82,73,73,78,84,0
	.section	.debug_info		;off: 13715
	.data.w	.Ldw_str_begin+5838
	.data.b	219,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12209
	.data.b	3,35
	.data.b	244,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5846
	.data.b	65,76,73,65,83,67,72,0
	.section	.debug_info		;off: 13733
	.data.w	.Ldw_str_begin+5846
	.data.b	220,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12264
	.data.b	3,35
	.data.b	248,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5854
	.data.b	68,77,65,69,78,0
	.section	.debug_info		;off: 13751
	.data.w	.Ldw_str_begin+5854
	.data.b	221,7
	.data.b	18
	.data.b	36
	.data.w	.Ldw_begin+12319
	.data.b	3,35
	.data.b	252,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5860
	.data.b	65,78,67,79,78,70,73,71,0
	.section	.debug_info		;off: 13769
	.data.w	.Ldw_str_begin+5860
	.data.b	222,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+12374
	.data.b	3,35
	.data.b	128,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5869
	.data.b	81,70,73,70,79,0
	.section	.debug_info		;off: 13787
	.data.w	.Ldw_str_begin+5869
	.data.b	223,7
	.data.b	18
	.data.b	36
	.data.w	.Ldw_begin+1272
	.data.b	3,35
	.data.b	132,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5875
	.data.b	82,69,83,69,82,86,69,68,95,48,49,57,48,0
	.section	.debug_info		;off: 13805
	.data.w	.Ldw_str_begin+5875
	.data.b	224,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2509
	.data.b	3,35
	.data.b	144,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5889
	.data.b	70,65,85,76,84,73,78,0
	.section	.debug_info		;off: 13823
	.data.w	.Ldw_str_begin+5889
	.data.b	225,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12484
	.data.b	3,35
	.data.b	148,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5897
	.data.b	83,65,70,69,69,78,0
	.section	.debug_info		;off: 13841
	.data.w	.Ldw_str_begin+5897
	.data.b	226,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+12539
	.data.b	3,35
	.data.b	152,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5904
	.data.b	83,65,70,69,65,76,77,0
	.section	.debug_info		;off: 13859
	.data.w	.Ldw_str_begin+5904
	.data.b	227,7
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+12594
	.data.b	3,35
	.data.b	156,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5912
	.data.b	83,65,70,69,65,76,77,67,76,82,0
	.section	.debug_info		;off: 13877
	.data.w	.Ldw_str_begin+5912
	.data.b	228,7
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+12649
	.data.b	3,35
	.data.b	160,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5923
	.data.b	83,65,70,69,66,79,85,78,68,0
	.section	.debug_info		;off: 13895
	.data.w	.Ldw_str_begin+5923
	.data.b	229,7
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+12704
	.data.b	3,35
	.data.b	164,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5933
	.data.b	84,82,73,71,65,84,84,72,82,69,83,0
	.section	.debug_info		;off: 13913
	.data.w	.Ldw_str_begin+5933
	.data.b	230,7
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+12759
	.data.b	3,35
	.data.b	168,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5945
	.data.b	83,89,78,67,84,72,82,69,83,0
	.section	.debug_info		;off: 13931
	.data.w	.Ldw_str_begin+5945
	.data.b	231,7
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+12814
	.data.b	3,35
	.data.b	172,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5955
	.data.b	68,65,73,83,89,84,72,82,69,83,0
	.section	.debug_info		;off: 13949
	.data.w	.Ldw_str_begin+5955
	.data.b	232,7
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+12869
	.data.b	3,35
	.data.b	176,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5966
	.data.b	68,77,65,84,72,82,69,83,0
	.section	.debug_info		;off: 13967
	.data.w	.Ldw_str_begin+5966
	.data.b	233,7
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+12924
	.data.b	3,35
	.data.b	180,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5975
	.data.b	82,69,83,69,82,86,69,68,95,48,49,66,56,0
	.section	.debug_info		;off: 13985
	.data.w	.Ldw_str_begin+5975
	.data.b	234,7
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1288
	.data.b	3,35
	.data.b	184,3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5989
	.data.b	71,76,79,73,78,84,67,84,82,76,0
	.section	.debug_info		;off: 14003
	.data.w	.Ldw_str_begin+5989
	.data.b	235,7
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+12979
	.data.b	3,35
	.data.b	128,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6000
	.data.b	71,76,79,82,69,83,85,76,84,0
	.section	.debug_info		;off: 14021
	.data.w	.Ldw_str_begin+6000
	.data.b	236,7
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+13034
	.data.b	3,35
	.data.b	132,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6010
	.data.b	71,76,79,82,69,83,85,76,84,68,0
	.section	.debug_info		;off: 14039
	.data.w	.Ldw_str_begin+6010
	.data.b	237,7
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+13089
	.data.b	3,35
	.data.b	136,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6021
	.data.b	71,76,79,82,69,83,67,84,82,76,0
	.section	.debug_info		;off: 14057
	.data.w	.Ldw_str_begin+6021
	.data.b	238,7
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+13144
	.data.b	3,35
	.data.b	140,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6032
	.data.b	71,76,79,68,77,65,0
	.section	.debug_info		;off: 14075
	.data.w	.Ldw_str_begin+6032
	.data.b	239,7
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+13199
	.data.b	3,35
	.data.b	144,4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6039
	.data.b	71,76,79,70,85,78,66,79,85,78,68,0
	.section	.debug_info		;off: 14093
	.data.w	.Ldw_str_begin+6039
	.data.b	240,7
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+13254
	.data.b	3,35
	.data.b	148,4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6051
	.data.b	83,65,82,65,68,67,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 14112
	.data.w	.Ldw_str_begin+6051
	.data.b	241,7
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+88

	.data.b	52
	.section	.debug_str		;off: 6065
	.data.b	0
	.section	.debug_info		;off: 14125
	.data.w	.Ldw_str_begin+6065
	.data.b	32
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6066
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,49,50,66,73,84,0
	.section	.debug_info		;off: 14135
	.data.w	.Ldw_str_begin+6066
	.data.b	33
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6090
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,49,48,66,73,84,0
	.section	.debug_info		;off: 14144
	.data.w	.Ldw_str_begin+6090
	.data.b	34
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6114
	.data.b	83,65,82,65,68,67,95,82,69,83,79,76,85,84,73,79,78,95,56,66,73,84,0
	.section	.debug_info		;off: 14153
	.data.w	.Ldw_str_begin+6114
	.data.b	35
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6137
	.data.b	83,97,114,97,100,99,95,82,101,115,111,108,117,116,105,111,110,0
	.section	.debug_info		;off: 14163
	.data.w	.Ldw_str_begin+6137
	.data.b	36
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14124

	.data.b	52
	.section	.debug_str		;off: 6155
	.data.b	0
	.section	.debug_info		;off: 14175
	.data.w	.Ldw_str_begin+6155
	.data.b	45
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6156
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,77,65,83,84,69,82,0
	.section	.debug_info		;off: 14185
	.data.w	.Ldw_str_begin+6156
	.data.b	46
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6180
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,49,0
	.section	.debug_info		;off: 14194
	.data.w	.Ldw_str_begin+6180
	.data.b	47
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6204
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,50,0
	.section	.debug_info		;off: 14203
	.data.w	.Ldw_str_begin+6204
	.data.b	48
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6228
	.data.b	83,65,82,65,68,67,95,67,79,78,86,69,82,84,69,82,95,83,76,65,86,69,51,0
	.section	.debug_info		;off: 14212
	.data.w	.Ldw_str_begin+6228
	.data.b	49
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6252
	.data.b	83,97,114,97,100,99,95,67,111,110,118,101,114,116,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 14222
	.data.w	.Ldw_str_begin+6252
	.data.b	50
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14174

	.data.b	52
	.section	.debug_str		;off: 6275
	.data.b	0
	.section	.debug_info		;off: 14234
	.data.w	.Ldw_str_begin+6275
	.data.b	55
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6276
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,83,84,79,80,0
	.section	.debug_info		;off: 14244
	.data.w	.Ldw_str_begin+6276
	.data.b	56
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6298
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,70,79,76,76,79,87,84,73,77,69,82,0
	.section	.debug_info		;off: 14253
	.data.w	.Ldw_str_begin+6298
	.data.b	57
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6327
	.data.b	83,65,82,65,68,67,95,84,73,77,69,82,77,79,68,69,95,70,79,76,76,79,87,84,73,77,69,82,95,79,78,76,89,79,78,67,69,0
	.section	.debug_info		;off: 14262
	.data.w	.Ldw_str_begin+6327
	.data.b	58
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6365
	.data.b	83,97,114,97,100,99,95,84,105,109,101,114,77,111,100,101,0
	.section	.debug_info		;off: 14272
	.data.w	.Ldw_str_begin+6365
	.data.b	60
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14233

	.data.b	52
	.section	.debug_str		;off: 6382
	.data.b	0
	.section	.debug_info		;off: 14284
	.data.w	.Ldw_str_begin+6382
	.data.b	64
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6383
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,76,79,87,69,83,84,0
	.section	.debug_info		;off: 14294
	.data.w	.Ldw_str_begin+6383
	.data.b	65
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6411
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,76,79,87,0
	.section	.debug_info		;off: 14303
	.data.w	.Ldw_str_begin+6411
	.data.b	66
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6436
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,72,73,71,72,0
	.section	.debug_info		;off: 14312
	.data.w	.Ldw_str_begin+6436
	.data.b	67
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6462
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,80,82,73,79,82,73,84,89,95,72,73,71,72,69,83,84,0
	.section	.debug_info		;off: 14321
	.data.w	.Ldw_str_begin+6462
	.data.b	68
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6491
	.data.b	83,97,114,97,100,99,95,65,114,98,105,116,101,114,80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 14331
	.data.w	.Ldw_str_begin+6491
	.data.b	69
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14283

	.data.b	52
	.section	.debug_str		;off: 6514
	.data.b	0
	.section	.debug_info		;off: 14343
	.data.w	.Ldw_str_begin+6514
	.data.b	73
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6515
	.data.b	83,65,82,65,68,67,95,83,84,65,82,84,77,79,68,69,95,87,65,73,84,70,79,82,83,84,65,82,84,0
	.section	.debug_info		;off: 14353
	.data.w	.Ldw_str_begin+6515
	.data.b	74
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6545
	.data.b	83,65,82,65,68,67,95,83,84,65,82,84,77,79,68,69,95,67,65,78,67,69,76,73,78,74,69,67,84,82,69,80,69,65,84,0
	.section	.debug_info		;off: 14362
	.data.w	.Ldw_str_begin+6545
	.data.b	75
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6581
	.data.b	83,97,114,97,100,99,95,83,116,97,114,116,77,111,100,101,0
	.section	.debug_info		;off: 14372
	.data.w	.Ldw_str_begin+6581
	.data.b	76
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14342

	.data.b	52
	.section	.debug_str		;off: 6598
	.data.b	0
	.section	.debug_info		;off: 14384
	.data.w	.Ldw_str_begin+6598
	.data.b	80
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6599
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,48,0
	.section	.debug_info		;off: 14394
	.data.w	.Ldw_str_begin+6599
	.data.b	81
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6621
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,0
	.section	.debug_info		;off: 14403
	.data.w	.Ldw_str_begin+6621
	.data.b	82
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6643
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,50,0
	.section	.debug_info		;off: 14412
	.data.w	.Ldw_str_begin+6643
	.data.b	83
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6665
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,51,0
	.section	.debug_info		;off: 14421
	.data.w	.Ldw_str_begin+6665
	.data.b	84
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6687
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,52,0
	.section	.debug_info		;off: 14430
	.data.w	.Ldw_str_begin+6687
	.data.b	85
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 6709
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,53,0
	.section	.debug_info		;off: 14439
	.data.w	.Ldw_str_begin+6709
	.data.b	86
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 6731
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,54,0
	.section	.debug_info		;off: 14448
	.data.w	.Ldw_str_begin+6731
	.data.b	87
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 6753
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,55,0
	.section	.debug_info		;off: 14457
	.data.w	.Ldw_str_begin+6753
	.data.b	88
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 6775
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,56,0
	.section	.debug_info		;off: 14466
	.data.w	.Ldw_str_begin+6775
	.data.b	89
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 6797
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,57,0
	.section	.debug_info		;off: 14475
	.data.w	.Ldw_str_begin+6797
	.data.b	90
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 6819
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,48,0
	.section	.debug_info		;off: 14484
	.data.w	.Ldw_str_begin+6819
	.data.b	91
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 6842
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,49,0
	.section	.debug_info		;off: 14493
	.data.w	.Ldw_str_begin+6842
	.data.b	92
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 6865
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,50,0
	.section	.debug_info		;off: 14502
	.data.w	.Ldw_str_begin+6865
	.data.b	93
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 6888
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,51,0
	.section	.debug_info		;off: 14511
	.data.w	.Ldw_str_begin+6888
	.data.b	94
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 6911
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,52,0
	.section	.debug_info		;off: 14520
	.data.w	.Ldw_str_begin+6911
	.data.b	95
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 6934
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,82,69,83,85,76,84,49,53,0
	.section	.debug_info		;off: 14529
	.data.w	.Ldw_str_begin+6934
	.data.b	96
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6957
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 14539
	.data.w	.Ldw_str_begin+6957
	.data.b	97
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14383

	.data.b	52
	.section	.debug_str		;off: 6978
	.data.b	0
	.section	.debug_info		;off: 14551
	.data.w	.Ldw_str_begin+6978
	.data.b	102
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6979
	.data.b	83,65,82,65,68,67,95,79,86,69,82,87,82,73,84,69,77,79,68,69,0
	.section	.debug_info		;off: 14561
	.data.w	.Ldw_str_begin+6979
	.data.b	103
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7000
	.data.b	83,65,82,65,68,67,95,87,65,73,84,70,79,82,82,69,65,68,77,79,68,69,0
	.section	.debug_info		;off: 14570
	.data.w	.Ldw_str_begin+7000
	.data.b	104
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7023
	.data.b	83,97,114,97,100,99,95,83,116,111,114,97,103,101,77,111,100,101,0
	.section	.debug_info		;off: 14580
	.data.w	.Ldw_str_begin+7023
	.data.b	105
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14550

	.data.b	52
	.section	.debug_str		;off: 7042
	.data.b	0
	.section	.debug_info		;off: 14592
	.data.w	.Ldw_str_begin+7042
	.data.b	110
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7043
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,48,0
	.section	.debug_info		;off: 14602
	.data.w	.Ldw_str_begin+7043
	.data.b	111
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7071
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,49,0
	.section	.debug_info		;off: 14611
	.data.w	.Ldw_str_begin+7071
	.data.b	112
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7099
	.data.b	83,65,82,65,68,67,95,82,69,81,85,69,83,84,83,79,85,82,67,69,95,81,85,69,85,69,50,0
	.section	.debug_info		;off: 14620
	.data.w	.Ldw_str_begin+7099
	.data.b	113
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7127
	.data.b	83,97,114,97,100,99,95,82,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 14630
	.data.w	.Ldw_str_begin+7127
	.data.b	114
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14591

	.data.b	52
	.section	.debug_str		;off: 7148
	.data.b	0
	.section	.debug_info		;off: 14642
	.data.w	.Ldw_str_begin+7148
	.data.b	118
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7149
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,48,0
	.section	.debug_info		;off: 14652
	.data.w	.Ldw_str_begin+7149
	.data.b	119
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7168
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,49,0
	.section	.debug_info		;off: 14661
	.data.w	.Ldw_str_begin+7168
	.data.b	120
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7187
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,50,0
	.section	.debug_info		;off: 14670
	.data.w	.Ldw_str_begin+7187
	.data.b	121
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7206
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,51,0
	.section	.debug_info		;off: 14679
	.data.w	.Ldw_str_begin+7206
	.data.b	122
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7225
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,52,0
	.section	.debug_info		;off: 14688
	.data.w	.Ldw_str_begin+7225
	.data.b	123
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7244
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,53,0
	.section	.debug_info		;off: 14697
	.data.w	.Ldw_str_begin+7244
	.data.b	124
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 7263
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,54,0
	.section	.debug_info		;off: 14706
	.data.w	.Ldw_str_begin+7263
	.data.b	125
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 7282
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,55,0
	.section	.debug_info		;off: 14715
	.data.w	.Ldw_str_begin+7282
	.data.b	126
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 7301
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,56,0
	.section	.debug_info		;off: 14724
	.data.w	.Ldw_str_begin+7301
	.data.b	127
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 7320
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,57,0
	.section	.debug_info		;off: 14733
	.data.w	.Ldw_str_begin+7320
	.data.b	128,1
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 7339
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,49,48,0
	.section	.debug_info		;off: 14743
	.data.w	.Ldw_str_begin+7339
	.data.b	129,1
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 7359
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,68,95,49,49,0
	.section	.debug_info		;off: 14753
	.data.w	.Ldw_str_begin+7359
	.data.b	130,1
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7379
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,73,68,0
	.section	.debug_info		;off: 14764
	.data.w	.Ldw_str_begin+7379
	.data.b	137,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14641

	.data.b	52
	.section	.debug_str		;off: 7396
	.data.b	0
	.section	.debug_info		;off: 14777
	.data.w	.Ldw_str_begin+7396
	.data.b	141,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7397
	.data.b	83,65,82,65,68,67,95,72,68,73,95,79,70,70,0
	.section	.debug_info		;off: 14788
	.data.w	.Ldw_str_begin+7397
	.data.b	142,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7412
	.data.b	83,65,82,65,68,67,95,72,68,73,95,70,67,0
	.section	.debug_info		;off: 14798
	.data.w	.Ldw_str_begin+7412
	.data.b	144,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7426
	.data.b	83,65,82,65,68,67,95,72,68,73,95,71,84,77,0
	.section	.debug_info		;off: 14808
	.data.w	.Ldw_str_begin+7426
	.data.b	146,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7441
	.data.b	83,65,82,65,68,67,95,72,68,73,95,82,68,67,0
	.section	.debug_info		;off: 14818
	.data.w	.Ldw_str_begin+7441
	.data.b	148,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7456
	.data.b	83,97,114,97,100,99,95,72,100,105,0
	.section	.debug_info		;off: 14829
	.data.w	.Ldw_str_begin+7456
	.data.b	150,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14776

	.data.b	71
	.data.b	159,1
	.data.b	1
	.data.b	35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7467
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 14849
	.data.w	.Ldw_str_begin+7467
	.data.b	160,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7474
	.data.b	115,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 14866
	.data.w	.Ldw_str_begin+7474
	.data.b	161,1
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7483
	.data.b	116,105,109,101,114,109,111,100,101,0
	.section	.debug_info		;off: 14883
	.data.w	.Ldw_str_begin+7483
	.data.b	162,1
	.data.b	22
	.data.b	35
	.data.w	.Ldw_begin+14271
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7493
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,66,121,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 14901
	.data.w	.Ldw_str_begin+7493
	.data.b	163,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14841

	.data.b	71
	.data.b	167,1
	.data.b	1
	.data.b	35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7521
	.data.b	112,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 14921
	.data.w	.Ldw_str_begin+7521
	.data.b	168,1
	.data.b	28
	.data.b	35
	.data.w	.Ldw_begin+14330
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7530
	.data.b	115,116,97,114,116,77,111,100,101,0
	.section	.debug_info		;off: 14938
	.data.w	.Ldw_str_begin+7530
	.data.b	169,1
	.data.b	22
	.data.b	35
	.data.w	.Ldw_begin+14371
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7540
	.data.b	101,110,97,98,108,101,0
	.section	.debug_info		;off: 14955
	.data.w	.Ldw_str_begin+7540
	.data.b	170,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7547
	.data.b	83,97,114,97,100,99,95,81,117,101,117,101,67,111,109,109,111,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 14973
	.data.w	.Ldw_str_begin+7547
	.data.b	171,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+14913

	.data.b	52
	.section	.debug_str		;off: 7572
	.data.b	0
	.section	.debug_info		;off: 14986
	.data.w	.Ldw_str_begin+7572
	.data.b	180,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7573
	.data.b	83,65,82,65,68,67,95,73,78,84,69,82,82,85,80,84,83,79,85,82,67,69,95,81,85,69,85,69,0
	.section	.debug_info		;off: 14997
	.data.w	.Ldw_str_begin+7573
	.data.b	181,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7602
	.data.b	83,65,82,65,68,67,95,73,78,84,69,82,82,85,80,84,83,79,85,82,67,69,95,67,72,65,78,78,69,76,0
	.section	.debug_info		;off: 15007
	.data.w	.Ldw_str_begin+7602
	.data.b	182,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7633
	.data.b	83,65,82,65,68,67,95,73,78,84,69,82,82,85,80,84,83,79,85,82,67,69,95,82,69,83,85,76,84,0
	.section	.debug_info		;off: 15017
	.data.w	.Ldw_str_begin+7633
	.data.b	183,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7663
	.data.b	83,97,114,97,100,99,95,73,110,116,101,114,114,117,112,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 15028
	.data.w	.Ldw_str_begin+7663
	.data.b	184,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+14985

	.data.b	52
	.section	.debug_str		;off: 7686
	.data.b	0
	.section	.debug_info		;off: 15041
	.data.w	.Ldw_str_begin+7686
	.data.b	188,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7687
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 15052
	.data.w	.Ldw_str_begin+7687
	.data.b	189,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7719
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,73,78,66,79,85,78,68,65,82,89,0
	.section	.debug_info		;off: 15062
	.data.w	.Ldw_str_begin+7719
	.data.b	190,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7754
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,79,85,84,66,79,85,78,68,65,82,89,0
	.section	.debug_info		;off: 15072
	.data.w	.Ldw_str_begin+7754
	.data.b	191,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7790
	.data.b	83,65,82,65,68,67,95,67,72,65,78,78,69,76,73,78,84,69,82,82,85,80,84,95,69,78,65,66,76,69,0
	.section	.debug_info		;off: 15082
	.data.w	.Ldw_str_begin+7790
	.data.b	192,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7821
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,73,110,116,101,114,114,117,112,116,77,111,100,101,0
	.section	.debug_info		;off: 15093
	.data.w	.Ldw_str_begin+7821
	.data.b	193,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15040

	.data.b	52
	.section	.debug_str		;off: 7849
	.data.b	0
	.section	.debug_info		;off: 15106
	.data.w	.Ldw_str_begin+7849
	.data.b	197,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7850
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,73,78,84,69,82,82,85,80,84,48,0
	.section	.debug_info		;off: 15117
	.data.w	.Ldw_str_begin+7850
	.data.b	198,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7876
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,73,78,84,69,82,82,85,80,84,49,0
	.section	.debug_info		;off: 15127
	.data.w	.Ldw_str_begin+7876
	.data.b	199,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7902
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,73,78,84,69,82,82,85,80,84,50,0
	.section	.debug_info		;off: 15137
	.data.w	.Ldw_str_begin+7902
	.data.b	200,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7928
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,73,78,84,69,82,82,85,80,84,51,0
	.section	.debug_info		;off: 15147
	.data.w	.Ldw_str_begin+7928
	.data.b	201,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7954
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,83,72,65,82,69,95,73,78,84,69,82,82,85,80,84,48,0
	.section	.debug_info		;off: 15157
	.data.w	.Ldw_str_begin+7954
	.data.b	202,1
	.data.b	5
	.data.b	34
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7986
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,83,72,65,82,69,95,73,78,84,69,82,82,85,80,84,49,0
	.section	.debug_info		;off: 15167
	.data.w	.Ldw_str_begin+7986
	.data.b	203,1
	.data.b	5
	.data.b	34
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 8018
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,83,72,65,82,69,95,73,78,84,69,82,82,85,80,84,50,0
	.section	.debug_info		;off: 15177
	.data.w	.Ldw_str_begin+8018
	.data.b	204,1
	.data.b	5
	.data.b	34
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 8050
	.data.b	83,65,82,65,68,67,95,77,65,80,80,73,78,71,95,83,72,65,82,69,95,73,78,84,69,82,82,85,80,84,51,0
	.section	.debug_info		;off: 15187
	.data.w	.Ldw_str_begin+8050
	.data.b	205,1
	.data.b	5
	.data.b	34
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8082
	.data.b	83,97,114,97,100,99,95,73,110,116,101,114,114,117,112,116,77,97,112,112,105,110,103,0
	.section	.debug_info		;off: 15198
	.data.w	.Ldw_str_begin+8082
	.data.b	206,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15105

	.data.b	52
	.section	.debug_str		;off: 8106
	.data.b	0
	.section	.debug_info		;off: 15211
	.data.w	.Ldw_str_begin+8106
	.data.b	210,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8107
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,68,73,83,65,66,76,69,68,0
	.section	.debug_info		;off: 15222
	.data.w	.Ldw_str_begin+8107
	.data.b	211,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8134
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,65,76,87,65,89,83,0
	.section	.debug_info		;off: 15232
	.data.w	.Ldw_str_begin+8134
	.data.b	212,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8159
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,71,65,84,73,78,71,72,73,71,72,0
	.section	.debug_info		;off: 15242
	.data.w	.Ldw_str_begin+8159
	.data.b	213,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8188
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,77,79,68,69,95,71,65,84,73,78,71,76,79,87,0
	.section	.debug_info		;off: 15252
	.data.w	.Ldw_str_begin+8188
	.data.b	215,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8216
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,77,111,100,101,0
	.section	.debug_info		;off: 15263
	.data.w	.Ldw_str_begin+8216
	.data.b	217,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15210

	.data.b	52
	.section	.debug_str		;off: 8234
	.data.b	0
	.section	.debug_info		;off: 15276
	.data.w	.Ldw_str_begin+8234
	.data.b	221,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8235
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,78,79,69,88,84,69,82,78,65,76,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15287
	.data.w	.Ldw_str_begin+8235
	.data.b	222,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8272
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,69,68,71,69,0
	.section	.debug_info		;off: 15297
	.data.w	.Ldw_str_begin+8272
	.data.b	223,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8303
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,69,68,71,69,0
	.section	.debug_info		;off: 15307
	.data.w	.Ldw_str_begin+8303
	.data.b	224,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8333
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,77,79,68,69,95,65,78,89,69,68,71,69,0
	.section	.debug_info		;off: 15317
	.data.w	.Ldw_str_begin+8333
	.data.b	225,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8360
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 15328
	.data.w	.Ldw_str_begin+8360
	.data.b	226,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15275

	.data.b	52
	.section	.debug_str		;off: 8379
	.data.b	0
	.section	.debug_info		;off: 15341
	.data.w	.Ldw_str_begin+8379
	.data.b	230,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8380
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,48,0
	.section	.debug_info		;off: 15352
	.data.w	.Ldw_str_begin+8380
	.data.b	231,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8413
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,49,0
	.section	.debug_info		;off: 15362
	.data.w	.Ldw_str_begin+8413
	.data.b	232,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8446
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,52,0
	.section	.debug_info		;off: 15372
	.data.w	.Ldw_str_begin+8446
	.data.b	233,1
	.data.b	5
	.data.b	34
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 8479
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,50,0
	.section	.debug_info		;off: 15382
	.data.w	.Ldw_str_begin+8479
	.data.b	234,1
	.data.b	5
	.data.b	34
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 8512
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,51,0
	.section	.debug_info		;off: 15392
	.data.w	.Ldw_str_begin+8512
	.data.b	235,1
	.data.b	5
	.data.b	34
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 8545
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,69,88,84,73,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15402
	.data.w	.Ldw_str_begin+8545
	.data.b	236,1
	.data.b	5
	.data.b	34
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 8578
	.data.b	83,65,82,65,68,67,95,71,65,84,73,78,71,83,79,85,82,67,69,95,81,85,69,85,69,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15412
	.data.w	.Ldw_str_begin+8578
	.data.b	237,1
	.data.b	5
	.data.b	34
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8612
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,83,111,117,114,99,101,0
	.section	.debug_info		;off: 15423
	.data.w	.Ldw_str_begin+8612
	.data.b	238,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15340

	.data.b	52
	.section	.debug_str		;off: 8632
	.data.b	0
	.section	.debug_info		;off: 15436
	.data.w	.Ldw_str_begin+8632
	.data.b	242,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8633
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,82,68,67,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15447
	.data.w	.Ldw_str_begin+8633
	.data.b	243,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 8666
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,52,0
	.section	.debug_info		;off: 15457
	.data.w	.Ldw_str_begin+8666
	.data.b	244,1
	.data.b	5
	.data.b	34
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 8700
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,69,88,84,73,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15467
	.data.w	.Ldw_str_begin+8700
	.data.b	245,1
	.data.b	5
	.data.b	34
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 8734
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,48,0
	.section	.debug_info		;off: 15477
	.data.w	.Ldw_str_begin+8734
	.data.b	246,1
	.data.b	5
	.data.b	34
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 8768
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,49,0
	.section	.debug_info		;off: 15487
	.data.w	.Ldw_str_begin+8768
	.data.b	247,1
	.data.b	5
	.data.b	34
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 8802
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,50,0
	.section	.debug_info		;off: 15497
	.data.w	.Ldw_str_begin+8802
	.data.b	248,1
	.data.b	5
	.data.b	34
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 8836
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,84,77,95,84,82,73,71,71,69,82,51,0
	.section	.debug_info		;off: 15507
	.data.w	.Ldw_str_begin+8836
	.data.b	249,1
	.data.b	5
	.data.b	34
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 8870
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15517
	.data.w	.Ldw_str_begin+8870
	.data.b	250,1
	.data.b	5
	.data.b	34
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 8909
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,79,77,77,79,78,48,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15527
	.data.w	.Ldw_str_begin+8909
	.data.b	251,1
	.data.b	5
	.data.b	34
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 8955
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,79,77,77,79,78,49,73,78,84,69,82,82,85,80,84,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15537
	.data.w	.Ldw_str_begin+8955
	.data.b	252,1
	.data.b	5
	.data.b	34
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 9001
	.data.b	83,65,82,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,81,85,69,85,69,95,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 15547
	.data.w	.Ldw_str_begin+9001
	.data.b	253,1
	.data.b	5
	.data.b	34
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9036
	.data.b	83,97,114,97,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 15558
	.data.w	.Ldw_str_begin+9036
	.data.b	254,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15435

	.data.b	52
	.section	.debug_str		;off: 9057
	.data.b	0
	.section	.debug_info		;off: 15571
	.data.w	.Ldw_str_begin+9057
	.data.b	130,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9058
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,48,0
	.section	.debug_info		;off: 15582
	.data.w	.Ldw_str_begin+9058
	.data.b	131,2
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9085
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,0
	.section	.debug_info		;off: 15592
	.data.w	.Ldw_str_begin+9085
	.data.b	132,2
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9112
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,50,0
	.section	.debug_info		;off: 15602
	.data.w	.Ldw_str_begin+9112
	.data.b	133,2
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 9139
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,51,0
	.section	.debug_info		;off: 15612
	.data.w	.Ldw_str_begin+9139
	.data.b	134,2
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 9166
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,52,0
	.section	.debug_info		;off: 15622
	.data.w	.Ldw_str_begin+9166
	.data.b	135,2
	.data.b	5
	.data.b	34
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 9193
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,53,0
	.section	.debug_info		;off: 15632
	.data.w	.Ldw_str_begin+9193
	.data.b	136,2
	.data.b	5
	.data.b	34
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 9220
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,54,0
	.section	.debug_info		;off: 15642
	.data.w	.Ldw_str_begin+9220
	.data.b	137,2
	.data.b	5
	.data.b	34
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 9247
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,55,0
	.section	.debug_info		;off: 15652
	.data.w	.Ldw_str_begin+9247
	.data.b	138,2
	.data.b	5
	.data.b	34
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 9274
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,56,0
	.section	.debug_info		;off: 15662
	.data.w	.Ldw_str_begin+9274
	.data.b	139,2
	.data.b	5
	.data.b	34
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 9301
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,57,0
	.section	.debug_info		;off: 15672
	.data.w	.Ldw_str_begin+9301
	.data.b	140,2
	.data.b	5
	.data.b	34
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 9328
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,48,0
	.section	.debug_info		;off: 15682
	.data.w	.Ldw_str_begin+9328
	.data.b	141,2
	.data.b	5
	.data.b	34
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 9356
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,49,0
	.section	.debug_info		;off: 15692
	.data.w	.Ldw_str_begin+9356
	.data.b	142,2
	.data.b	5
	.data.b	34
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 9384
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,50,0
	.section	.debug_info		;off: 15702
	.data.w	.Ldw_str_begin+9384
	.data.b	143,2
	.data.b	5
	.data.b	34
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 9412
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,51,0
	.section	.debug_info		;off: 15712
	.data.w	.Ldw_str_begin+9412
	.data.b	144,2
	.data.b	5
	.data.b	34
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 9440
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,52,0
	.section	.debug_info		;off: 15722
	.data.w	.Ldw_str_begin+9440
	.data.b	145,2
	.data.b	5
	.data.b	34
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 9468
	.data.b	83,65,82,65,68,67,95,68,65,84,65,82,69,68,85,67,84,73,79,78,77,79,68,69,95,49,53,0
	.section	.debug_info		;off: 15732
	.data.w	.Ldw_str_begin+9468
	.data.b	146,2
	.data.b	5
	.data.b	34
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9496
	.data.b	83,97,114,97,100,99,95,68,97,116,97,82,101,100,117,99,116,105,111,110,77,111,100,101,0
	.section	.debug_info		;off: 15743
	.data.w	.Ldw_str_begin+9496
	.data.b	147,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15570

	.data.b	71
	.data.b	154,2
	.data.b	1
	.data.b	34
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9521
	.data.b	103,97,116,105,110,103,83,111,117,114,99,101,0
	.section	.debug_info		;off: 15763
	.data.w	.Ldw_str_begin+9521
	.data.b	155,2
	.data.b	25
	.data.b	34
	.data.w	.Ldw_begin+15422
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9534
	.data.b	116,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 15780
	.data.w	.Ldw_str_begin+9534
	.data.b	156,2
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+15557
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9548
	.data.b	103,97,116,105,110,103,77,111,100,101,0
	.section	.debug_info		;off: 15797
	.data.w	.Ldw_str_begin+9548
	.data.b	157,2
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+15262
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9559
	.data.b	116,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 15814
	.data.w	.Ldw_str_begin+9559
	.data.b	158,2
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+15327
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9571
	.data.b	116,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 15831
	.data.w	.Ldw_str_begin+9571
	.data.b	159,2
	.data.b	33
	.data.b	34
	.data.w	.Ldw_begin+14900
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9583
	.data.b	83,97,114,97,100,99,95,71,97,116,105,110,103,84,114,105,103,103,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 15849
	.data.w	.Ldw_str_begin+9583
	.data.b	160,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15755

	.data.b	71
	.data.b	164,2
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9610
	.data.b	108,111,119,66,111,117,110,100,97,114,121,0
	.section	.debug_info		;off: 15869
	.data.w	.Ldw_str_begin+9610
	.data.b	165,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+2178
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9622
	.data.b	104,105,103,104,66,111,117,110,100,97,114,121,0
	.section	.debug_info		;off: 15886
	.data.w	.Ldw_str_begin+9622
	.data.b	166,2
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+2178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9635
	.data.b	83,97,114,97,100,99,95,66,111,117,110,100,97,114,121,67,111,110,102,105,103,0
	.section	.debug_info		;off: 15904
	.data.w	.Ldw_str_begin+9635
	.data.b	167,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15861

	.data.b	71
	.data.b	171,2
	.data.b	1
	.data.b	34
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9657
	.data.b	105,110,116,101,114,114,117,112,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 15924
	.data.w	.Ldw_str_begin+9657
	.data.b	172,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9673
	.data.b	105,110,116,101,114,114,117,112,116,77,97,112,112,105,110,103,0
	.section	.debug_info		;off: 15941
	.data.w	.Ldw_str_begin+9673
	.data.b	173,2
	.data.b	29
	.data.b	34
	.data.w	.Ldw_begin+15197
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9690
	.data.b	83,97,114,97,100,99,95,73,110,116,101,114,114,117,112,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 15959
	.data.w	.Ldw_str_begin+9690
	.data.b	174,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15916

	.data.b	71
	.data.b	185,2
	.data.b	1
	.data.b	34
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9713
	.data.b	99,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 15979
	.data.w	.Ldw_str_begin+9713
	.data.b	186,2
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+14538
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9727
	.data.b	115,116,111,114,97,103,101,77,111,100,101,0
	.section	.debug_info		;off: 15996
	.data.w	.Ldw_str_begin+9727
	.data.b	187,2
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+14579
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9739
	.data.b	101,110,97,98,108,101,68,109,97,0
	.section	.debug_info		;off: 16013
	.data.w	.Ldw_str_begin+9739
	.data.b	188,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9749
	.data.b	114,105,103,104,116,65,108,105,103,110,101,100,83,116,111,114,97,103,101,0
	.section	.debug_info		;off: 16030
	.data.w	.Ldw_str_begin+9749
	.data.b	189,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	9
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9769
	.data.b	101,110,97,98,108,101,83,121,110,99,104,114,111,110,105,122,101,0
	.section	.debug_info		;off: 16047
	.data.w	.Ldw_str_begin+9769
	.data.b	190,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	10
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9787
	.data.b	98,111,117,110,100,97,114,121,82,97,110,103,101,0
	.section	.debug_info		;off: 16064
	.data.w	.Ldw_str_begin+9787
	.data.b	192,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	11
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9801
	.data.b	98,111,117,110,100,97,114,121,82,101,115,117,108,116,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 16081
	.data.w	.Ldw_str_begin+9801
	.data.b	194,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9823
	.data.b	104,100,105,73,102,69,110,0
	.section	.debug_info		;off: 16098
	.data.w	.Ldw_str_begin+9823
	.data.b	195,2
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+14828
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9831
	.data.b	83,97,114,97,100,99,95,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 16116
	.data.w	.Ldw_str_begin+9831
	.data.b	196,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+15971

	.data.b	71
	.data.b	200,2
	.data.b	1
	.data.b	34
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9852
	.data.b	99,104,97,110,110,101,108,82,101,115,117,108,116,0
	.section	.debug_info		;off: 16136
	.data.w	.Ldw_str_begin+9852
	.data.b	201,2
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+14538
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9866
	.data.b	101,110,97,98,108,101,68,109,97,0
	.section	.debug_info		;off: 16153
	.data.w	.Ldw_str_begin+9866
	.data.b	202,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9876
	.data.b	101,110,97,98,108,101,83,121,110,99,104,114,111,110,105,122,101,0
	.section	.debug_info		;off: 16170
	.data.w	.Ldw_str_begin+9876
	.data.b	203,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9894
	.data.b	98,111,117,110,100,97,114,121,82,97,110,103,101,0
	.section	.debug_info		;off: 16187
	.data.w	.Ldw_str_begin+9894
	.data.b	205,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9908
	.data.b	98,111,117,110,100,97,114,121,82,101,115,117,108,116,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 16204
	.data.w	.Ldw_str_begin+9908
	.data.b	207,2
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	7
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9930
	.data.b	104,100,105,73,102,69,110,0
	.section	.debug_info		;off: 16221
	.data.w	.Ldw_str_begin+9930
	.data.b	208,2
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+14828
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9938
	.data.b	83,97,114,97,100,99,95,68,121,110,97,67,104,97,110,110,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 16239
	.data.w	.Ldw_str_begin+9938
	.data.b	209,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+16128

	.data.b	71
	.data.b	214,2
	.data.b	1
	.data.b	34
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9963
	.data.b	100,105,118,105,100,101,114,0
	.section	.debug_info		;off: 16259
	.data.w	.Ldw_str_begin+9963
	.data.b	215,2
	.data.b	11
	.data.b	34
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9971
	.data.b	115,97,109,112,108,101,84,105,109,101,0
	.section	.debug_info		;off: 16276
	.data.w	.Ldw_str_begin+9971
	.data.b	216,2
	.data.b	11
	.data.b	34
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9982
	.data.b	114,101,115,111,108,117,116,105,111,110,0
	.section	.debug_info		;off: 16293
	.data.w	.Ldw_str_begin+9982
	.data.b	217,2
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+14162
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9993
	.data.b	99,111,110,118,101,114,116,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 16310
	.data.w	.Ldw_str_begin+9993
	.data.b	218,2
	.data.b	28
	.data.b	34
	.data.w	.Ldw_begin+14221
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10009
	.data.b	114,101,113,117,101,115,116,81,117,101,117,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 16327
	.data.w	.Ldw_str_begin+10009
	.data.b	219,2
	.data.b	30
	.data.b	34
	.data.w	.Ldw_begin+1304
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10028
	.data.b	83,97,114,97,100,99,95,77,111,100,117,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 16345
	.data.w	.Ldw_str_begin+10028
	.data.b	220,2
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+16251

	.data.b	45
	.section	.debug_str		;off: 10048
	.data.b	65,100,99,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 16358
	.data.w	.Ldw_str_begin+10048
	.data.b	53
	.data.b	15
	.data.b	5
	.data.w	.Ldw_begin+2166

	.data.b	45
	.section	.debug_str		;off: 10064
	.data.b	65,100,99,95,71,114,111,117,112,84,121,112,101,0
	.section	.debug_info		;off: 16370
	.data.w	.Ldw_str_begin+10064
	.data.b	57
	.data.b	16
	.data.b	5
	.data.w	.Ldw_begin+2178

	.data.b	45
	.section	.debug_str		;off: 10078
	.data.b	65,100,99,95,86,97,108,117,101,71,114,111,117,112,84,121,112,101,0
	.section	.debug_info		;off: 16382
	.data.w	.Ldw_str_begin+10078
	.data.b	62
	.data.b	16
	.data.b	5
	.data.w	.Ldw_begin+2178

	.data.b	45
	.section	.debug_str		;off: 10097
	.data.b	65,100,99,95,71,114,111,117,112,80,114,105,111,114,105,116,121,84,121,112,101,0
	.section	.debug_info		;off: 16394
	.data.w	.Ldw_str_begin+10097
	.data.b	80
	.data.b	15
	.data.b	5
	.data.w	.Ldw_begin+2166

	.data.b	45
	.section	.debug_str		;off: 10119
	.data.b	65,100,99,95,71,114,111,117,112,68,101,102,84,121,112,101,0
	.section	.debug_info		;off: 16406
	.data.w	.Ldw_str_begin+10119
	.data.b	83
	.data.b	25
	.data.b	5
	.data.w	.Ldw_begin+16357

	.data.b	45
	.section	.debug_str		;off: 10136
	.data.b	65,100,99,95,83,116,114,101,97,109,78,117,109,83,97,109,112,108,101,84,121,112,101,0
	.section	.debug_info		;off: 16418
	.data.w	.Ldw_str_begin+10136
	.data.b	87
	.data.b	15
	.data.b	5
	.data.w	.Ldw_begin+2166

	.data.b	45
	.section	.debug_str		;off: 10160
	.data.b	65,100,99,95,72,119,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 16430
	.data.w	.Ldw_str_begin+10160
	.data.b	105
	.data.b	15
	.data.b	5
	.data.w	.Ldw_begin+2166

	.data.b	45
	.section	.debug_str		;off: 10175
	.data.b	65,100,99,95,78,111,116,105,102,70,99,116,80,116,114,84,121,112,101,0
	.section	.debug_info		;off: 16442
	.data.w	.Ldw_str_begin+10175
	.data.b	110
	.data.b	16
	.data.b	5
	.data.w	.Ldw_begin+1323

	.data.b	52
	.section	.debug_str		;off: 10195
	.data.b	0
	.section	.debug_info		;off: 16454
	.data.w	.Ldw_str_begin+10195
	.data.b	128,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10196
	.data.b	65,68,67,95,73,68,76,69,0
	.section	.debug_info		;off: 16465
	.data.w	.Ldw_str_begin+10196
	.data.b	131,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 10205
	.data.b	65,68,67,95,66,85,83,89,0
	.section	.debug_info		;off: 16475
	.data.w	.Ldw_str_begin+10205
	.data.b	134,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10214
	.data.b	65,68,67,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 16485
	.data.w	.Ldw_str_begin+10214
	.data.b	137,1
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 10228
	.data.b	65,68,67,95,83,84,82,69,65,77,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 16495
	.data.w	.Ldw_str_begin+10228
	.data.b	141,1
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10249
	.data.b	65,100,99,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 16506
	.data.w	.Ldw_str_begin+10249
	.data.b	142,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16453

	.data.b	52
	.section	.debug_str		;off: 10264
	.data.b	0
	.section	.debug_info		;off: 16519
	.data.w	.Ldw_str_begin+10264
	.data.b	146,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10265
	.data.b	65,68,67,95,84,82,73,71,71,95,83,82,67,95,83,87,0
	.section	.debug_info		;off: 16530
	.data.w	.Ldw_str_begin+10265
	.data.b	148,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 10282
	.data.b	65,68,67,95,84,82,73,71,71,95,83,82,67,95,72,87,0
	.section	.debug_info		;off: 16540
	.data.w	.Ldw_str_begin+10282
	.data.b	150,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10299
	.data.b	65,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,84,121,112,101,0
	.section	.debug_info		;off: 16551
	.data.w	.Ldw_str_begin+10299
	.data.b	151,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16518

	.data.b	52
	.section	.debug_str		;off: 10321
	.data.b	0
	.section	.debug_info		;off: 16564
	.data.w	.Ldw_str_begin+10321
	.data.b	155,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10322
	.data.b	65,68,67,95,67,79,78,86,95,77,79,68,69,95,79,78,69,83,72,79,84,0
	.section	.debug_info		;off: 16575
	.data.w	.Ldw_str_begin+10322
	.data.b	161,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 10344
	.data.b	65,68,67,95,67,79,78,86,95,77,79,68,69,95,67,79,78,84,73,78,85,79,85,83,0
	.section	.debug_info		;off: 16585
	.data.w	.Ldw_str_begin+10344
	.data.b	165,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10369
	.data.b	65,100,99,95,71,114,111,117,112,67,111,110,118,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 16596
	.data.w	.Ldw_str_begin+10369
	.data.b	166,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16563

	.data.b	52
	.section	.debug_str		;off: 10391
	.data.b	0
	.section	.debug_info		;off: 16609
	.data.w	.Ldw_str_begin+10391
	.data.b	170,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10392
	.data.b	65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,76,73,78,69,65,82,0
	.section	.debug_info		;off: 16620
	.data.w	.Ldw_str_begin+10392
	.data.b	173,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 10417
	.data.b	65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,67,73,82,67,85,76,65,82,0
	.section	.debug_info		;off: 16630
	.data.w	.Ldw_str_begin+10417
	.data.b	176,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10444
	.data.b	65,100,99,95,83,116,114,101,97,109,66,117,102,102,101,114,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 16641
	.data.w	.Ldw_str_begin+10444
	.data.b	177,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16608

	.data.b	52
	.section	.debug_str		;off: 10469
	.data.b	0
	.section	.debug_info		;off: 16654
	.data.w	.Ldw_str_begin+10469
	.data.b	181,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 10470
	.data.b	65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,73,78,71,76,69,0
	.section	.debug_info		;off: 16665
	.data.w	.Ldw_str_begin+10470
	.data.b	183,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 10493
	.data.b	65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,84,82,69,65,77,73,78,71,0
	.section	.debug_info		;off: 16675
	.data.w	.Ldw_str_begin+10493
	.data.b	185,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10519
	.data.b	65,100,99,95,71,114,111,117,112,65,99,99,101,115,115,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 16686
	.data.w	.Ldw_str_begin+10519
	.data.b	186,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16653

	.data.b	71
	.data.b	175,2
	.data.b	1
	.data.b	5
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10543
	.data.b	67,111,114,101,72,119,85,110,105,116,73,100,120,0
	.section	.debug_info		;off: 16706
	.data.w	.Ldw_str_begin+10543
	.data.b	177,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16429
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10557
	.data.b	72,119,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 16723
	.data.w	.Ldw_str_begin+10557
	.data.b	179,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10569
	.data.b	65,100,99,95,72,87,85,110,105,116,67,111,114,101,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 16741
	.data.w	.Ldw_str_begin+10569
	.data.b	180,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16698

	.data.b	71
	.data.b	185,2
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10591
	.data.b	71,114,112,73,100,0
	.section	.debug_info		;off: 16761
	.data.w	.Ldw_str_begin+10591
	.data.b	187,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16369
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10597
	.data.b	71,114,112,80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 16778
	.data.w	.Ldw_str_begin+10597
	.data.b	189,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16393
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10609
	.data.b	73,115,114,83,101,114,118,82,101,113,70,108,103,0
	.section	.debug_info		;off: 16795
	.data.w	.Ldw_str_begin+10609
	.data.b	191,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10623
	.data.b	65,100,99,95,84,114,105,103,103,83,114,99,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 16813
	.data.w	.Ldw_str_begin+10623
	.data.b	192,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16753

	.data.b	71
	.data.b	197,2
	.data.b	1
	.data.b	5
	.data.b	17
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10644
	.data.b	71,114,112,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 16833
	.data.w	.Ldw_str_begin+10644
	.data.b	200,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+1328
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10656
	.data.b	78,111,79,102,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 16850
	.data.w	.Ldw_str_begin+10656
	.data.b	202,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10669
	.data.b	65,100,99,95,71,114,111,117,112,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 16868
	.data.w	.Ldw_str_begin+10669
	.data.b	203,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16825

	.data.b	71
	.data.b	220,2
	.data.b	1
	.data.b	5
	.data.b	88
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10687
	.data.b	71,114,111,117,112,82,101,115,117,108,116,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 16888
	.data.w	.Ldw_str_begin+10687
	.data.b	222,2
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+862
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10708
	.data.b	71,114,111,117,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16905
	.data.w	.Ldw_str_begin+10708
	.data.b	224,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10720
	.data.b	71,114,111,117,112,82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16922
	.data.w	.Ldw_str_begin+10720
	.data.b	226,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10738
	.data.b	71,114,112,66,117,102,102,101,114,69,110,100,82,101,115,117,108,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16939
	.data.w	.Ldw_str_begin+10738
	.data.b	228,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10763
	.data.b	71,114,112,78,111,116,105,102,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16956
	.data.w	.Ldw_str_begin+10763
	.data.b	231,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10778
	.data.b	84,114,105,103,103,83,114,99,68,97,116,97,0
	.section	.debug_info		;off: 16973
	.data.w	.Ldw_str_begin+10778
	.data.b	240,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+1344
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10791
	.data.b	82,115,71,114,111,117,112,68,97,116,97,0
	.section	.debug_info		;off: 16990
	.data.w	.Ldw_str_begin+10791
	.data.b	242,2
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+1360
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10803
	.data.b	78,117,109,86,97,108,105,100,67,111,110,82,101,115,80,116,114,0
	.section	.debug_info		;off: 17007
	.data.w	.Ldw_str_begin+10803
	.data.b	252,2
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1376
	.data.b	2,35
	.data.b	84
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10821
	.data.b	65,100,99,95,71,108,111,98,97,108,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 17025
	.data.w	.Ldw_str_begin+10821
	.data.b	253,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+16880

	.data.b	71
	.data.b	129,3
	.data.b	1
	.data.b	5
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10840
	.data.b	73,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 17045
	.data.w	.Ldw_str_begin+10840
	.data.b	132,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1381
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10854
	.data.b	71,108,111,98,97,108,68,97,116,97,83,101,116,80,116,114,0
	.section	.debug_info		;off: 17062
	.data.w	.Ldw_str_begin+10854
	.data.b	135,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+296
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10871
	.data.b	71,114,111,117,112,78,117,109,86,97,108,105,100,67,111,110,82,101,115,80,116,114,0
	.section	.debug_info		;off: 17079
	.data.w	.Ldw_str_begin+10871
	.data.b	141,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1376
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10894
	.data.b	71,114,112,82,115,108,116,68,97,116,97,66,102,80,116,114,0
	.section	.debug_info		;off: 17096
	.data.w	.Ldw_str_begin+10894
	.data.b	143,3
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+862
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10911
	.data.b	65,100,99,95,71,108,111,98,97,108,68,97,116,97,83,101,116,84,121,112,101,0
	.section	.debug_info		;off: 17114
	.data.w	.Ldw_str_begin+10911
	.data.b	144,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17037

	.data.b	71
	.data.b	150,3
	.data.b	1
	.data.b	5
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10933
	.data.b	73,115,83,121,110,99,67,104,69,120,105,115,116,115,0
	.section	.debug_info		;off: 17134
	.data.w	.Ldw_str_begin+10933
	.data.b	154,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10948
	.data.b	78,117,109,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 17151
	.data.w	.Ldw_str_begin+10948
	.data.b	157,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16417
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10959
	.data.b	73,110,116,67,104,77,97,115,107,0
	.section	.debug_info		;off: 17168
	.data.w	.Ldw_str_begin+10959
	.data.b	159,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10969
	.data.b	78,111,116,105,102,70,99,116,80,116,114,0
	.section	.debug_info		;off: 17185
	.data.w	.Ldw_str_begin+10969
	.data.b	163,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16441
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10981
	.data.b	71,114,111,117,112,68,101,102,105,110,105,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 17202
	.data.w	.Ldw_str_begin+10981
	.data.b	167,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1391
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11000
	.data.b	71,114,111,117,112,82,101,115,82,101,103,80,116,114,0
	.section	.debug_info		;off: 17219
	.data.w	.Ldw_str_begin+11000
	.data.b	170,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1401
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11015
	.data.b	72,119,84,114,105,103,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17236
	.data.w	.Ldw_str_begin+11015
	.data.b	174,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1411
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11031
	.data.b	82,101,115,117,108,116,65,99,99,117,109,78,117,109,0
	.section	.debug_info		;off: 17253
	.data.w	.Ldw_str_begin+11031
	.data.b	177,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11046
	.data.b	84,114,105,103,103,83,114,99,0
	.section	.debug_info		;off: 17270
	.data.w	.Ldw_str_begin+11046
	.data.b	179,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16550
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11055
	.data.b	71,114,112,82,101,113,117,101,115,116,83,114,99,0
	.section	.debug_info		;off: 17287
	.data.w	.Ldw_str_begin+11055
	.data.b	181,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+14629
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11069
	.data.b	65,99,99,101,115,115,77,111,100,101,0
	.section	.debug_info		;off: 17304
	.data.w	.Ldw_str_begin+11069
	.data.b	183,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16685
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11080
	.data.b	67,111,110,118,77,111,100,101,0
	.section	.debug_info		;off: 17321
	.data.w	.Ldw_str_begin+11080
	.data.b	185,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16595
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11089
	.data.b	83,116,114,101,97,109,66,117,102,102,101,114,77,111,100,101,0
	.section	.debug_info		;off: 17338
	.data.w	.Ldw_str_begin+11089
	.data.b	187,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16640
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11106
	.data.b	65,100,99,95,71,114,111,117,112,67,102,103,84,121,112,101,0
	.section	.debug_info		;off: 17356
	.data.w	.Ldw_str_begin+11106
	.data.b	193,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17126

	.data.b	71
	.data.b	200,3
	.data.b	1
	.data.b	5
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11123
	.data.b	67,104,76,105,109,105,116,67,104,107,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 17376
	.data.w	.Ldw_str_begin+11123
	.data.b	202,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+15903
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11144
	.data.b	67,104,76,105,109,105,116,67,104,107,73,110,116,114,77,111,100,0
	.section	.debug_info		;off: 17393
	.data.w	.Ldw_str_begin+11144
	.data.b	204,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+15092
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11162
	.data.b	65,100,99,95,67,104,97,110,110,101,108,76,105,109,105,116,67,104,101,99,107,84,121,112,101,0
	.section	.debug_info		;off: 17411
	.data.w	.Ldw_str_begin+11162
	.data.b	205,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17368

	.data.b	71
	.data.b	212,3
	.data.b	1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11188
	.data.b	67,104,76,105,109,105,116,67,104,101,99,107,105,110,103,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17431
	.data.w	.Ldw_str_begin+11188
	.data.b	215,3
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1421
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11213
	.data.b	67,104,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 17448
	.data.w	.Ldw_str_begin+11213
	.data.b	218,3
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+16115
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11226
	.data.b	67,104,82,117,110,116,105,109,101,67,111,110,102,105,103,68,97,116,97,0
	.section	.debug_info		;off: 17465
	.data.w	.Ldw_str_begin+11226
	.data.b	220,3
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+16238
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11246
	.data.b	65,100,99,95,67,104,97,110,110,101,108,67,102,103,84,121,112,101,0
	.section	.debug_info		;off: 17483
	.data.w	.Ldw_str_begin+11246
	.data.b	221,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17423

	.data.b	71
	.data.b	227,3
	.data.b	1
	.data.b	5
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11265
	.data.b	65,100,99,72,119,85,110,105,116,0
	.section	.debug_info		;off: 17503
	.data.w	.Ldw_str_begin+11265
	.data.b	229,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+16429
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11275
	.data.b	82,115,108,116,72,108,100,77,116,104,100,0
	.section	.debug_info		;off: 17520
	.data.w	.Ldw_str_begin+11275
	.data.b	232,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11287
	.data.b	72,119,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17537
	.data.w	.Ldw_str_begin+11287
	.data.b	235,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1431
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11296
	.data.b	83,121,110,99,71,114,112,83,108,97,118,101,72,119,80,116,114,0
	.section	.debug_info		;off: 17554
	.data.w	.Ldw_str_begin+11296
	.data.b	238,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1441
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11314
	.data.b	67,104,78,117,109,0
	.section	.debug_info		;off: 17571
	.data.w	.Ldw_str_begin+11314
	.data.b	241,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11320
	.data.b	67,104,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17588
	.data.w	.Ldw_str_begin+11320
	.data.b	243,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1451
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11329
	.data.b	71,114,112,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17605
	.data.w	.Ldw_str_begin+11329
	.data.b	245,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+306
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11339
	.data.b	84,111,116,67,102,103,71,114,112,115,0
	.section	.debug_info		;off: 17622
	.data.w	.Ldw_str_begin+11339
	.data.b	251,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11350
	.data.b	73,110,100,101,120,71,114,112,115,67,111,114,101,0
	.section	.debug_info		;off: 17639
	.data.w	.Ldw_str_begin+11350
	.data.b	254,3
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	25
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11364
	.data.b	73,115,73,110,116,69,110,0
	.section	.debug_info		;off: 17656
	.data.w	.Ldw_str_begin+11364
	.data.b	129,4
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2154
	.data.b	2,35
	.data.b	26
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11372
	.data.b	65,100,99,95,75,101,114,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 17674
	.data.w	.Ldw_str_begin+11372
	.data.b	131,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17495

	.data.b	71
	.data.b	137,4
	.data.b	1
	.data.b	5
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11393
	.data.b	77,97,120,67,111,114,101,72,119,85,110,105,116,0
	.section	.debug_info		;off: 17694
	.data.w	.Ldw_str_begin+11393
	.data.b	139,4
	.data.b	40
	.data.b	5
	.data.w	.Ldw_begin+2166
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11407
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17711
	.data.w	.Ldw_str_begin+11407
	.data.b	141,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+265
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11423
	.data.b	65,100,99,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 17729
	.data.w	.Ldw_str_begin+11423
	.data.b	142,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17686

	.data.b	71
	.data.b	148,4
	.data.b	1
	.data.b	5
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11442
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 17749
	.data.w	.Ldw_str_begin+11442
	.data.b	150,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1466
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 11456
	.data.b	72,119,85,110,105,116,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 17766
	.data.w	.Ldw_str_begin+11456
	.data.b	152,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+1487
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 11472
	.data.b	65,100,99,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 17784
	.data.w	.Ldw_str_begin+11472
	.data.b	153,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+17741

	.data.b	6
	.section	.debug_str		;off: 11487
	.data.b	65,100,99,95,73,110,105,116,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 17797
	.data.w	.Ldw_str_begin+11487
	.data.b	155,2
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

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

	.section	.debug_info		;off: 17817
	.data.b	6
	.section	.debug_str		;off: 11507
	.data.b	65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,67,111,114,101,48,0
	.section	.debug_info		;off: 17818
	.data.w	.Ldw_str_begin+11507
	.data.b	159,2
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+1492
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InstanceDataCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11529
	.data.b	65,100,99,95,71,114,111,117,112,82,101,115,117,108,116,66,117,102,102,101,114,67,111,114,101,48,0
	.section	.debug_info		;off: 17839
	.data.w	.Ldw_str_begin+11529
	.data.b	162,2
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+1509
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_GroupResultBufferCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11556
	.data.b	65,100,99,95,78,117,109,86,97,108,105,100,67,111,110,82,101,115,67,111,114,101,48,0
	.section	.debug_info		;off: 17860
	.data.w	.Ldw_str_begin+11556
	.data.b	165,2
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1525
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_NumValidConResCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11580
	.data.b	65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,83,101,116,67,111,114,101,48,0
	.section	.debug_info		;off: 17881
	.data.w	.Ldw_str_begin+11580
	.data.b	183,2
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1541
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InstanceDataSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11605
	.data.b	65,100,99,95,73,110,105,116,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 17902
	.data.w	.Ldw_str_begin+11605
	.data.b	212,2
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11625
	.data.b	65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,67,111,114,101,49,0
	.section	.debug_info		;off: 17923
	.data.w	.Ldw_str_begin+11625
	.data.b	216,2
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+1546
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InstanceDataCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11647
	.data.b	65,100,99,95,71,114,111,117,112,82,101,115,117,108,116,66,117,102,102,101,114,67,111,114,101,49,0
	.section	.debug_info		;off: 17944
	.data.w	.Ldw_str_begin+11647
	.data.b	219,2
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+1562
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_GroupResultBufferCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11674
	.data.b	65,100,99,95,78,117,109,86,97,108,105,100,67,111,110,82,101,115,67,111,114,101,49,0
	.section	.debug_info		;off: 17965
	.data.w	.Ldw_str_begin+11674
	.data.b	222,2
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1578
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_NumValidConResCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11698
	.data.b	65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,83,101,116,67,111,114,101,49,0
	.section	.debug_info		;off: 17986
	.data.w	.Ldw_str_begin+11698
	.data.b	238,2
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1541
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InstanceDataSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11723
	.data.b	65,100,99,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 18007
	.data.w	.Ldw_str_begin+11723
	.data.b	239,3
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+541
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11737
	.data.b	65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,83,101,116,0
	.section	.debug_info		;off: 18028
	.data.w	.Ldw_str_begin+11737
	.data.b	132,4
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+1604
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_InstanceDataSet..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11757
	.data.b	65,100,99,95,66,97,115,101,65,100,100,114,115,0
	.section	.debug_info		;off: 18049
	.data.w	.Ldw_str_begin+11757
	.data.b	167,4
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+1620
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_BaseAddrs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11771
	.data.b	65,100,99,95,66,111,117,110,100,68,101,102,97,117,108,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 18070
	.data.w	.Ldw_str_begin+11771
	.data.b	151,5
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+1636
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_BoundDefaultConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	6
	.section	.debug_str		;off: 11794
	.data.b	65,100,99,95,67,111,110,116,105,110,117,111,117,115,84,105,109,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 18091
	.data.w	.Ldw_str_begin+11794
	.data.b	158,5
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1406
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Adc_ContinuousTimerConfig..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.

	.data.b	27
	.section	.debug_str		;off: 11820
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 18112
	.data.w	.Ldw_str_begin+11820
	.data.b	63
	.data.b	31
	.data.b	15
	.data.w	.Ldw_begin+2381
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

	.section	.debug_info		;off: 18129
	.data.b	37

	.section	.debug_abbrev		;off: 269
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 18130
	.data.b	8
	.section	.debug_str		;off: 11840
	.data.b	105,100,0
	.section	.debug_info		;off: 18131
	.data.w	.Ldw_str_begin+11840
	.data.b	65
	.data.b	17
	.data.b	15
	.data.w	.Ldw_begin+2381
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

	.section	.debug_info		;off: 18144
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11843
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 18147
	.data.w	.Ldw_str_begin+11843
	.data.b	131,2
	.data.b	48
	.data.b	6
	.data.w	.Ldw_begin+2214
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11856
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 18167
	.data.w	.Ldw_str_begin+11856
	.data.b	133,2
	.data.b	38
	.data.b	6
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

	.section	.debug_info		;off: 18181
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11873
	.data.b	83,97,114,97,100,99,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 18183
	.data.w	.Ldw_str_begin+11873
	.data.b	182,1
	.data.b	27
	.data.b	35
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 11904
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 18202
	.data.w	.Ldw_str_begin+11904
	.data.b	182,1
	.data.b	66
	.data.b	35
	.data.w	.Ldw_begin+2154
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

	.section	.debug_info		;off: 18215
	.data.b	20
	.section	.debug_str		;off: 11910
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 18216
	.data.w	.Ldw_str_begin+11910
	.data.b	182,1
	.data.b	80
	.data.b	35
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 11916
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 18230
	.data.w	.Ldw_str_begin+11916
	.data.b	182,1
	.data.b	94
	.data.b	35
	.data.w	.Ldw_begin+2190
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 11923
	.data.b	114,101,116,0
	.section	.debug_info		;off: 18245
	.data.w	.Ldw_str_begin+11923
	.data.b	184,1
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11927
	.data.b	83,97,114,97,100,99,95,72,97,108,95,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 18262
	.data.w	.Ldw_str_begin+11927
	.data.b	248,2
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11949
	.data.b	83,97,114,97,100,99,95,72,97,108,95,68,101,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 18282
	.data.w	.Ldw_str_begin+11949
	.data.b	136,3
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11973
	.data.b	83,97,114,97,100,99,95,72,97,108,95,79,112,101,110,67,97,108,105,98,114,97,116,105,111,110,0
	.section	.debug_info		;off: 18302
	.data.w	.Ldw_str_begin+11973
	.data.b	153,3
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12000
	.data.b	83,97,114,97,100,99,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18322
	.data.w	.Ldw_str_begin+12000
	.data.b	191,3
	.data.b	15
	.data.b	34
	.data.w	.Ldw_begin+2190
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12030
	.data.b	83,97,114,97,100,99,95,72,97,108,95,67,108,101,97,114,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18342
	.data.w	.Ldw_str_begin+12030
	.data.b	230,3
	.data.b	13
	.data.b	34
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12062
	.data.b	83,97,114,97,100,99,95,72,97,108,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18358
	.data.w	.Ldw_str_begin+12062
	.data.b	248,3
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12085
	.data.b	83,97,114,97,100,99,95,72,97,108,95,68,121,110,97,109,105,99,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 18378
	.data.w	.Ldw_str_begin+12085
	.data.b	138,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12117
	.data.b	83,97,114,97,100,99,95,72,97,108,95,70,105,108,108,81,117,101,117,101,0
	.section	.debug_info		;off: 18398
	.data.w	.Ldw_str_begin+12117
	.data.b	171,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12138
	.data.b	83,97,114,97,100,99,95,72,97,108,95,70,108,117,115,104,81,117,101,117,101,0
	.section	.debug_info		;off: 18418
	.data.w	.Ldw_str_begin+12138
	.data.b	189,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12160
	.data.b	83,97,114,97,100,99,95,72,97,108,95,71,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 18438
	.data.w	.Ldw_str_begin+12160
	.data.b	207,4
	.data.b	15
	.data.b	34
	.data.w	.Ldw_begin+2178
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12181
	.data.b	83,97,114,97,100,99,95,72,97,108,95,83,101,116,66,111,117,110,100,97,114,121,0
	.section	.debug_info		;off: 18458
	.data.w	.Ldw_str_begin+12181
	.data.b	241,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12204
	.data.b	83,97,114,97,100,99,95,72,97,108,95,83,101,116,84,114,105,103,103,101,114,71,97,116,105,110,103,0
	.section	.debug_info		;off: 18478
	.data.w	.Ldw_str_begin+12204
	.data.b	132,5
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12232
	.data.b	83,97,114,97,100,99,95,72,97,108,95,83,101,116,82,101,115,117,108,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 18498
	.data.w	.Ldw_str_begin+12232
	.data.b	150,5
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12262
	.data.b	83,97,114,97,100,99,95,72,97,108,95,77,97,115,107,82,101,115,117,108,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 18518
	.data.w	.Ldw_str_begin+12262
	.data.b	184,5
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12293
	.data.b	83,97,114,97,100,99,95,72,97,108,95,84,114,105,103,103,101,114,66,121,83,111,102,116,119,97,114,101,0
	.section	.debug_info		;off: 18538
	.data.w	.Ldw_str_begin+12293
	.data.b	139,7
	.data.b	24
	.data.b	34
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 12322
	.data.b	112,83,97,114,97,100,99,0
	.section	.debug_info		;off: 18553
	.data.w	.Ldw_str_begin+12322
	.data.b	139,7
	.data.b	74
	.data.b	34
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 12330
	.data.b	114,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 18567
	.data.w	.Ldw_str_begin+12330
	.data.b	139,7
	.data.b	104
	.data.b	34
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12344
	.data.b	83,97,114,97,100,99,95,72,97,108,95,84,114,105,103,84,105,109,101,114,66,121,83,111,102,116,119,97,114,101,0
	.section	.debug_info		;off: 18584
	.data.w	.Ldw_str_begin+12344
	.data.b	153,7
	.data.b	24
	.data.b	34
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 12375
	.data.b	112,83,97,114,97,100,99,0
	.section	.debug_info		;off: 18599
	.data.w	.Ldw_str_begin+12375
	.data.b	153,7
	.data.b	76
	.data.b	34
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 12383
	.data.b	114,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 18613
	.data.w	.Ldw_str_begin+12383
	.data.b	153,7
	.data.b	106
	.data.b	34
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12397
	.data.b	83,97,114,97,100,99,95,72,97,108,95,83,101,116,65,108,119,97,121,115,71,97,116,105,110,103,77,111,100,101,0
	.section	.debug_info		;off: 18630
	.data.w	.Ldw_str_begin+12397
	.data.b	186,7
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 12428
	.data.b	112,83,97,114,97,100,99,0
	.section	.debug_info		;off: 18649
	.data.w	.Ldw_str_begin+12428
	.data.b	186,7
	.data.b	79
	.data.b	34
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 12436
	.data.b	114,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 18663
	.data.w	.Ldw_str_begin+12436
	.data.b	186,7
	.data.b	109
	.data.b	34
	.data.w	.Ldw_begin+14629
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 12450
	.data.b	81,77,79,68,69,0
	.section	.debug_info		;off: 18678
	.data.w	.Ldw_str_begin+12450
	.data.b	189,7
	.data.b	18
	.data.b	34
	.data.w	.Ldw_begin+11219
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 12456
	.data.b	114,101,116,83,116,115,0
	.section	.debug_info		;off: 18693
	.data.w	.Ldw_str_begin+12456
	.data.b	190,7
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12463
	.data.b	83,97,114,97,100,99,95,72,97,108,95,83,101,116,68,97,116,97,82,101,100,117,99,116,105,111,110,0
	.section	.debug_info		;off: 18710
	.data.w	.Ldw_str_begin+12463
	.data.b	209,7
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 12491
	.data.b	112,83,97,114,97,100,99,0
	.section	.debug_info		;off: 18729
	.data.w	.Ldw_str_begin+12491
	.data.b	209,7
	.data.b	76
	.data.b	34
	.data.w	.Ldw_begin+98
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 12499
	.data.b	99,104,97,110,110,101,108,73,68,0
	.section	.debug_info		;off: 18743
	.data.w	.Ldw_str_begin+12499
	.data.b	209,7
	.data.b	102
	.data.b	34
	.data.w	.Ldw_begin+14763
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 12509
	.data.b	100,97,116,97,82,101,100,117,99,116,105,111,110,77,111,100,101,0
	.section	.debug_info		;off: 18757
	.data.w	.Ldw_str_begin+12509
	.data.b	210,7
	.data.b	59
	.data.b	34
	.data.w	.Ldw_begin+15742
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 12527
	.data.b	114,101,116,83,116,115,0
	.section	.debug_info		;off: 18772
	.data.w	.Ldw_str_begin+12527
	.data.b	212,7
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12534
	.data.b	83,97,114,97,100,99,95,72,97,108,95,71,101,116,65,110,97,108,111,103,82,101,97,100,121,70,108,103,0
	.section	.debug_info		;off: 18789
	.data.w	.Ldw_str_begin+12534
	.data.b	229,7
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 12563
	.data.b	112,83,97,114,97,100,99,0
	.section	.debug_info		;off: 18808
	.data.w	.Ldw_str_begin+12563
	.data.b	229,7
	.data.b	83
	.data.b	34
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12571
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,83,116,97,114,116,71,114,111,117,112,0
	.section	.debug_info		;off: 18825
	.data.w	.Ldw_str_begin+12571
	.data.b	34
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
	.section	.debug_str		;off: 12597
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,83,116,111,112,71,114,111,117,112,0
	.section	.debug_info		;off: 18840
	.data.w	.Ldw_str_begin+12597
	.data.b	36
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
	.section	.debug_str		;off: 12622
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,82,101,97,100,71,114,111,117,112,0
	.section	.debug_info		;off: 18855
	.data.w	.Ldw_str_begin+12622
	.data.b	38
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
	.section	.debug_str		;off: 12647
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,69,110,97,98,108,101,72,119,84,114,105,103,0
	.section	.debug_info		;off: 18870
	.data.w	.Ldw_str_begin+12647
	.data.b	40
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
	.section	.debug_str		;off: 12675
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,68,105,115,97,98,108,101,72,119,84,114,105,103,0
	.section	.debug_info		;off: 18885
	.data.w	.Ldw_str_begin+12675
	.data.b	42
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
	.section	.debug_str		;off: 12704
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,71,101,116,71,114,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18900
	.data.w	.Ldw_str_begin+12704
	.data.b	44
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
	.section	.debug_str		;off: 12732
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,116,114,0
	.section	.debug_info		;off: 18915
	.data.w	.Ldw_str_begin+12732
	.data.b	46
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
	.section	.debug_str		;off: 12764
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,83,116,97,114,116,71,114,111,117,112,0
	.section	.debug_info		;off: 18930
	.data.w	.Ldw_str_begin+12764
	.data.b	58
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
	.section	.debug_str		;off: 12789
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,83,116,111,112,71,114,111,117,112,0
	.section	.debug_info		;off: 18945
	.data.w	.Ldw_str_begin+12789
	.data.b	60
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
	.section	.debug_str		;off: 12813
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,82,101,97,100,71,114,111,117,112,0
	.section	.debug_info		;off: 18960
	.data.w	.Ldw_str_begin+12813
	.data.b	62
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
	.section	.debug_str		;off: 12837
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,69,110,97,98,108,101,72,119,84,114,105,103,0
	.section	.debug_info		;off: 18975
	.data.w	.Ldw_str_begin+12837
	.data.b	64
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
	.section	.debug_str		;off: 12864
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,68,105,115,97,98,108,101,72,119,84,114,105,103,0
	.section	.debug_info		;off: 18990
	.data.w	.Ldw_str_begin+12864
	.data.b	66
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
	.section	.debug_str		;off: 12892
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,71,101,116,71,114,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19005
	.data.w	.Ldw_str_begin+12892
	.data.b	68
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
	.section	.debug_str		;off: 12919
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,116,114,0
	.section	.debug_info		;off: 19020
	.data.w	.Ldw_str_begin+12919
	.data.b	70
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
	.section	.debug_str		;off: 12950
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,68,105,115,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 19035
	.data.w	.Ldw_str_begin+12950
	.data.b	82
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
	.section	.debug_str		;off: 12990
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,68,105,115,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 19050
	.data.w	.Ldw_str_begin+12990
	.data.b	84
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
	.section	.debug_str		;off: 13029
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,69,110,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 19065
	.data.w	.Ldw_str_begin+13029
	.data.b	86
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
	.section	.debug_str		;off: 13068
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,69,110,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 19080
	.data.w	.Ldw_str_begin+13068
	.data.b	88
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
	.section	.debug_str		;off: 13106
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 19095
	.data.w	.Ldw_str_begin+13106
	.data.b	90
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
	.section	.debug_str		;off: 13129
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 19110
	.data.w	.Ldw_str_begin+13129
	.data.b	92
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
	.section	.debug_str		;off: 13151
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,82,101,115,117,108,116,72,97,110,100,108,105,110,103,0
	.section	.debug_info		;off: 19125
	.data.w	.Ldw_str_begin+13151
	.data.b	94
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
	.section	.debug_str		;off: 13181
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,82,101,115,117,108,116,72,97,110,100,108,105,110,103,0
	.section	.debug_info		;off: 19140
	.data.w	.Ldw_str_begin+13181
	.data.b	96
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
	.section	.debug_str		;off: 13210
	.data.b	83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 19155
	.data.w	.Ldw_str_begin+13210
	.data.b	98
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
	.section	.debug_str		;off: 13232
	.data.b	83,99,104,77,95,69,120,105,116,95,65,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 19170
	.data.w	.Ldw_str_begin+13232
	.data.b	100
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
	.section	.debug_str		;off: 13253
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 19185
	.data.w	.Ldw_str_begin+13253
	.data.b	105
	.data.b	39
	.data.b	40
	.data.w	.Ldw_begin+2214
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 13269
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 19204
	.data.w	.Ldw_str_begin+13269
	.data.b	113
	.data.b	39
	.data.b	40
	.data.w	.Ldw_begin+2214
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13292
	.data.b	65,100,99,95,67,104,101,99,107,83,116,97,116,101,70,111,114,83,116,97,114,116,71,114,111,117,112,0
	.section	.debug_info		;off: 19223
	.data.w	.Ldw_str_begin+13292
	.data.b	136,8
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckStateForStartGroup
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
	.data.w	Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckStateForStartGroup-Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1664
	.data.b	0,5,2
	.data.w	Adc_CheckStateForStartGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	166,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	3
	.data.b	50
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	187
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19256
	.data.b	22
	.section	.debug_str		;off: 13320
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 19257
	.data.w	.Ldw_str_begin+13320
	.data.b	138,8
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
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

	.section	.debug_info		;off: 19274
	.data.b	22
	.section	.debug_str		;off: 13326
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 19275
	.data.w	.Ldw_str_begin+13326
	.data.b	139,8
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19292
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

	.section	.debug_info		;off: 19301
	.data.b	7
	.section	.debug_str		;off: 13335
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 19302
	.data.w	.Ldw_str_begin+13335
	.data.b	142,8
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
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

	.section	.debug_info		;off: 19320
	.data.b	8
	.section	.debug_str		;off: 13342
	.data.b	65,108,108,71,114,112,83,116,97,116,0
	.section	.debug_info		;off: 19321
	.data.w	.Ldw_str_begin+13342
	.data.b	149,8
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13353
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19336
	.data.w	.Ldw_str_begin+13353
	.data.b	158,8
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13360
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 19351
	.data.w	.Ldw_str_begin+13360
	.data.b	160,8
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13368
	.data.b	65,100,99,95,67,104,101,99,107,83,116,97,116,101,70,111,114,69,110,97,98,108,101,71,114,111,117,112,0
	.section	.debug_info		;off: 19368
	.data.w	.Ldw_str_begin+13368
	.data.b	136,9
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckStateForEnableGroup
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
	.data.w	Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckStateForEnableGroup-Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1705
	.data.b	0,5,2
	.data.w	Adc_CheckStateForEnableGroup..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	159,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	3
	.data.b	33
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	187
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19401
	.data.b	22
	.section	.debug_str		;off: 13397
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 19402
	.data.w	.Ldw_str_begin+13397
	.data.b	138,9
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19419
	.data.b	22
	.section	.debug_str		;off: 13403
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 19420
	.data.w	.Ldw_str_begin+13403
	.data.b	139,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19437
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 13412
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 19447
	.data.w	.Ldw_str_begin+13412
	.data.b	142,9
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19465
	.data.b	8
	.section	.debug_str		;off: 13419
	.data.b	65,108,108,71,114,112,83,116,97,116,0
	.section	.debug_info		;off: 19466
	.data.w	.Ldw_str_begin+13419
	.data.b	149,9
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13430
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 19481
	.data.w	.Ldw_str_begin+13430
	.data.b	152,9
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13438
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19496
	.data.w	.Ldw_str_begin+13438
	.data.b	156,9
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 13445
	.data.b	65,100,99,95,85,112,100,97,116,101,82,101,115,66,117,102,102,101,114,0
	.section	.debug_info		;off: 19513
	.data.w	.Ldw_str_begin+13445
	.data.b	231,9
	.data.b	37
	.data.b	1
	.data.w	Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_UpdateResBuffer
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	52
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_UpdateResBuffer-Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1753
	.data.b	0,5,2
	.data.w	Adc_UpdateResBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	236,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	13
	.data.b	173
	.data.b	45
	.data.b	61
	.data.b	29
	.data.b	43
	.data.b	43
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	29
	.data.b	155
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	111
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	90
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	43
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	29
	.data.b	61
	.data.b	27
	.data.b	13
	.data.b	2
	.data.b	24
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 19544
	.data.b	22
	.section	.debug_str		;off: 13465
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 19545
	.data.w	.Ldw_str_begin+13465
	.data.b	233,9
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	80
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19562
	.data.b	22
	.section	.debug_str		;off: 13474
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 19563
	.data.w	.Ldw_str_begin+13474
	.data.b	234,9
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+145
	.section	.debug_loc		;off: 145
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	81
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19580
	.data.b	22
	.section	.debug_str		;off: 13480
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 19581
	.data.w	.Ldw_str_begin+13480
	.data.b	235,9
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+175
	.section	.debug_loc		;off: 175
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	82
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19598
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 13493
	.data.b	78,111,79,102,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 19608
	.data.w	.Ldw_str_begin+13493
	.data.b	238,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+205
	.section	.debug_loc		;off: 205
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19626
	.data.b	7
	.section	.debug_str		;off: 13505
	.data.b	67,117,114,114,66,117,102,80,111,115,0
	.section	.debug_info		;off: 19627
	.data.w	.Ldw_str_begin+13505
	.data.b	239,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+224
	.section	.debug_loc		;off: 224
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19645
	.data.b	7
	.section	.debug_str		;off: 13516
	.data.b	67,104,97,110,110,101,108,78,117,109,0
	.section	.debug_info		;off: 19646
	.data.w	.Ldw_str_begin+13516
	.data.b	240,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+16357
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+243
	.section	.debug_loc		;off: 243
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19664
	.data.b	7
	.section	.debug_str		;off: 13527
	.data.b	78,111,79,102,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 19665
	.data.w	.Ldw_str_begin+13527
	.data.b	241,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+263
	.section	.debug_loc		;off: 263
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	5
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19683
	.data.b	7
	.section	.debug_str		;off: 13540
	.data.b	72,119,85,110,105,116,67,110,116,0
	.section	.debug_info		;off: 19684
	.data.w	.Ldw_str_begin+13540
	.data.b	243,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+283
	.section	.debug_loc		;off: 283
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19702
	.data.b	8
	.section	.debug_str		;off: 13550
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 19703
	.data.w	.Ldw_str_begin+13550
	.data.b	244,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13556
	.data.b	83,121,110,99,71,114,112,83,108,97,118,101,82,115,108,116,83,116,97,114,116,80,111,115,0
	.section	.debug_info		;off: 19718
	.data.w	.Ldw_str_begin+13556
	.data.b	245,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2178
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+302
	.section	.debug_loc		;off: 302
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	14
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19736
	.data.b	7
	.section	.debug_str		;off: 13581
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 19737
	.data.w	.Ldw_str_begin+13581
	.data.b	247,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+322
	.section	.debug_loc		;off: 322
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19755
	.data.b	7
	.section	.debug_str		;off: 13589
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 19756
	.data.w	.Ldw_str_begin+13589
	.data.b	248,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+341
	.section	.debug_loc		;off: 341
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19774
	.data.b	7
	.section	.debug_str		;off: 13596
	.data.b	76,111,111,112,67,110,116,0
	.section	.debug_info		;off: 19775
	.data.w	.Ldw_str_begin+13596
	.data.b	249,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+360
	.section	.debug_loc		;off: 360
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19793
	.data.b	7
	.section	.debug_str		;off: 13604
	.data.b	67,117,114,114,101,110,116,82,101,115,66,117,102,80,116,114,0
	.section	.debug_info		;off: 19794
	.data.w	.Ldw_str_begin+13604
	.data.b	250,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+379
	.section	.debug_loc		;off: 379
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19812
	.data.b	7
	.section	.debug_str		;off: 13621
	.data.b	71,114,112,66,117,102,102,101,114,66,97,115,101,80,116,114,0
	.section	.debug_info		;off: 19813
	.data.w	.Ldw_str_begin+13621
	.data.b	251,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+399
	.section	.debug_loc		;off: 399
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19831
	.data.b	8
	.section	.debug_str		;off: 13638
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19832
	.data.w	.Ldw_str_begin+13638
	.data.b	252,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13645
	.data.b	65,100,99,95,83,116,111,112,67,111,110,118,82,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 19849
	.data.w	.Ldw_str_begin+13645
	.data.b	201,13
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.w	Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_StopConvRequestSource
	.data.b	1
	.data.b	93
	.data.b	240,129,1
	.data.b	112
	.data.b	0
	.data.b	28
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
	.data.w	Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_StopConvRequestSource-Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1888
	.data.b	0,5,2
	.data.w	Adc_StopConvRequestSource..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	205,13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	253
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	77
	.data.b	2
	.data.b	12
	.data.b	0,1,1
	.section	.debug_info		;off: 19884
	.data.b	22
	.section	.debug_str		;off: 13671
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 19885
	.data.w	.Ldw_str_begin+13671
	.data.b	203,13
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+316
	.data.b	0
	.data.w	.Ldw_loc_begin+418
	.section	.debug_loc		;off: 418
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

	.section	.debug_info		;off: 19902
	.data.b	22
	.section	.debug_str		;off: 13678
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 19903
	.data.w	.Ldw_str_begin+13678
	.data.b	204,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+448
	.section	.debug_loc		;off: 448
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	81
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19920
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 13687
	.data.b	76,97,115,116,67,104,97,110,110,101,108,78,117,109,0
	.section	.debug_info		;off: 19930
	.data.w	.Ldw_str_begin+13687
	.data.b	207,13
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+16357
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+478
	.section	.debug_loc		;off: 478
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19948
	.data.b	8
	.section	.debug_str		;off: 13702
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 19949
	.data.w	.Ldw_str_begin+13702
	.data.b	208,13
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13710
	.data.b	82,115,108,116,73,110,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 19964
	.data.w	.Ldw_str_begin+13710
	.data.b	209,13
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+15958
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+497
	.section	.debug_loc		;off: 497
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19982
	.data.b	8
	.section	.debug_str		;off: 13724
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19983
	.data.w	.Ldw_str_begin+13724
	.data.b	210,13
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13731
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 19998
	.data.w	.Ldw_str_begin+13731
	.data.b	211,13
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+517
	.section	.debug_loc		;off: 517
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20016
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 13745
	.data.b	65,100,99,95,73,110,105,116,71,108,111,98,97,108,86,97,114,105,97,98,108,101,115,0
	.section	.debug_info		;off: 20019
	.data.w	.Ldw_str_begin+13745
	.data.b	170,16
	.data.b	37
	.data.b	1
	.data.w	Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_InitGlobalVariables
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
	.data.w	Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_InitGlobalVariables-Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1943
	.data.b	0,5,2
	.data.w	Adc_InitGlobalVariables..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	173,16
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
	.data.w	.LDWlin8
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	109
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20050
	.data.b	22
	.section	.debug_str		;off: 13769
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 20051
	.data.w	.Ldw_str_begin+13769
	.data.b	172,16
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+536
	.section	.debug_loc		;off: 536
	.data.w	.LDW22
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20068
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 13778
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 20078
	.data.w	.Ldw_str_begin+13778
	.data.b	175,16
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+555
	.section	.debug_loc		;off: 555
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20096
	.data.b	7
	.section	.debug_str		;off: 13786
	.data.b	76,111,111,112,67,116,114,0
	.section	.debug_info		;off: 20097
	.data.w	.Ldw_str_begin+13786
	.data.b	176,16
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+574
	.section	.debug_loc		;off: 574
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20115
	.data.b	7
	.section	.debug_str		;off: 13794
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20116
	.data.w	.Ldw_str_begin+13794
	.data.b	177,16
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+593
	.section	.debug_loc		;off: 593
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20134
	.data.b	7
	.section	.debug_str		;off: 13801
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 20135
	.data.w	.Ldw_str_begin+13801
	.data.b	178,16
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+612
	.section	.debug_loc		;off: 612
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20153
	.data.b	7
	.section	.debug_str		;off: 13815
	.data.b	71,114,112,73,110,100,101,120,0
	.section	.debug_info		;off: 20154
	.data.w	.Ldw_str_begin+13815
	.data.b	179,16
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+631
	.section	.debug_loc		;off: 631
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20172
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13824
	.data.b	65,100,99,95,82,83,73,110,116,101,114,114,117,112,116,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 20175
	.data.w	.Ldw_str_begin+13824
	.data.b	177,17
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.w	Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_RSInterruptHandler
	.data.b	1
	.data.b	93
	.data.b	240,131,1
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
	.data.w	Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_RSInterruptHandler-Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2078
	.data.b	0,5,2
	.data.w	Adc_RSInterruptHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	184,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	59
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	12
	.data.b	45
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	20
	.data.b	13
	.data.b	3
	.data.b	36
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20210
	.data.b	22
	.section	.debug_str		;off: 13847
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 20211
	.data.w	.Ldw_str_begin+13847
	.data.b	179,17
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+650
	.section	.debug_loc		;off: 650
	.data.w	.LDW52
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20228
	.data.b	22
	.section	.debug_str		;off: 13856
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 20229
	.data.w	.Ldw_str_begin+13856
	.data.b	180,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+669
	.section	.debug_loc		;off: 669
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	81
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20246
	.data.b	22
	.section	.debug_str		;off: 13864
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 20247
	.data.w	.Ldw_str_begin+13864
	.data.b	181,17
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+699
	.section	.debug_loc		;off: 699
	.data.w	.LDW52
	.data.w	.LDW72
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20264
	.data.b	22
	.section	.debug_str		;off: 13877
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 20265
	.data.w	.Ldw_str_begin+13877
	.data.b	183,17
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.w	.Ldw_loc_begin+718
	.section	.debug_loc		;off: 718
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	83
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20282
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 13885
	.data.b	71,114,112,82,101,113,117,101,115,116,83,114,99,0
	.section	.debug_info		;off: 20292
	.data.w	.Ldw_str_begin+13885
	.data.b	186,17
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+748
	.section	.debug_loc		;off: 748
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20310
	.data.b	8
	.section	.debug_str		;off: 13899
	.data.b	69,110,100,71,114,112,70,108,103,0
	.section	.debug_info		;off: 20311
	.data.w	.Ldw_str_begin+13899
	.data.b	187,17
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13909
	.data.b	66,117,102,69,110,100,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20326
	.data.w	.Ldw_str_begin+13909
	.data.b	191,17
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13922
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 20341
	.data.w	.Ldw_str_begin+13922
	.data.b	192,17
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+767
	.section	.debug_loc		;off: 767
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20359
	.data.b	7
	.section	.debug_str		;off: 13929
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 20360
	.data.w	.Ldw_str_begin+13929
	.data.b	193,17
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+786
	.section	.debug_loc		;off: 786
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20378
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13943
	.data.b	65,100,99,95,73,115,114,69,118,101,110,116,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 20381
	.data.w	.Ldw_str_begin+13943
	.data.b	185,18
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.w	Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_IsrEventHandler
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_IsrEventHandler-Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2177
	.data.b	0,5,2
	.data.w	Adc_IsrEventHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	192,18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	93
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	2
	.data.b	20
	.data.b	11
	.data.b	13
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	20
	.data.b	13
	.data.b	108
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	24
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
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20416
	.data.b	22
	.section	.debug_str		;off: 13963
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 20417
	.data.w	.Ldw_str_begin+13963
	.data.b	187,18
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+805
	.section	.debug_loc		;off: 805
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	80
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20434
	.data.b	22
	.section	.debug_str		;off: 13972
	.data.b	82,101,113,83,114,99,0
	.section	.debug_info		;off: 20435
	.data.w	.Ldw_str_begin+13972
	.data.b	188,18
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+14629
	.data.b	0
	.data.w	.Ldw_loc_begin+835
	.section	.debug_loc		;off: 835
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	81
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20452
	.data.b	22
	.section	.debug_str		;off: 13979
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 20453
	.data.w	.Ldw_str_begin+13979
	.data.b	189,18
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+865
	.section	.debug_loc		;off: 865
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	82
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20470
	.data.b	22
	.section	.debug_str		;off: 13995
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 20471
	.data.w	.Ldw_str_begin+13995
	.data.b	191,18
	.data.b	63
	.data.b	1
	.data.w	.Ldw_begin+380
	.data.b	0
	.data.w	.Ldw_loc_begin+895
	.section	.debug_loc		;off: 895
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	83
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20488
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 14003
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 20498
	.data.w	.Ldw_str_begin+14003
	.data.b	194,18
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+925
	.section	.debug_loc		;off: 925
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20516
	.data.b	7
	.section	.debug_str		;off: 14017
	.data.b	71,114,112,78,114,0
	.section	.debug_info		;off: 20517
	.data.w	.Ldw_str_begin+14017
	.data.b	195,18
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+944
	.section	.debug_loc		;off: 944
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20535
	.data.b	7
	.section	.debug_str		;off: 14023
	.data.b	76,97,115,116,67,104,97,110,110,101,108,78,117,109,0
	.section	.debug_info		;off: 20536
	.data.w	.Ldw_str_begin+14023
	.data.b	196,18
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16357
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+963
	.section	.debug_loc		;off: 963
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20554
	.data.b	8
	.section	.debug_str		;off: 14038
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 20555
	.data.w	.Ldw_str_begin+14038
	.data.b	197,18
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14047
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 20570
	.data.w	.Ldw_str_begin+14047
	.data.b	199,18
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14054
	.data.b	65,100,99,95,83,116,97,114,116,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 20587
	.data.w	.Ldw_str_begin+14054
	.data.b	182,19
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.w	Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_StartConversion
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	204,0
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
	.data.w	Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_StartConversion-Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2277
	.data.b	0,5,2
	.data.w	Adc_StartConversion..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	188,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	24
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	3
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	75
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	27
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
	.data.b	45
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	172
	.data.b	28
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
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
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	107
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	29
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	110
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	11
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
	.data.b	43
	.data.b	28
	.data.b	3
	.data.b	177,127
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	92
	.data.b	3
	.data.b	211,0
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	4
	.data.b	1
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
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 20623
	.data.b	22
	.section	.debug_str		;off: 14074
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 20624
	.data.w	.Ldw_str_begin+14074
	.data.b	184,19
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+982
	.section	.debug_loc		;off: 982
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	80
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20641
	.data.b	22
	.section	.debug_str		;off: 14083
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 20642
	.data.w	.Ldw_str_begin+14083
	.data.b	185,19
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+1013
	.section	.debug_loc		;off: 1013
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	81
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20659
	.data.b	22
	.section	.debug_str		;off: 14096
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 20660
	.data.w	.Ldw_str_begin+14096
	.data.b	186,19
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+316
	.data.b	0
	.data.w	.Ldw_loc_begin+1044
	.section	.debug_loc		;off: 1044
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	82
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20677
	.data.b	22
	.section	.debug_str		;off: 14103
	.data.b	84,114,105,103,103,101,114,83,114,99,0
	.section	.debug_info		;off: 20678
	.data.w	.Ldw_str_begin+14103
	.data.b	187,19
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+16550
	.data.b	0
	.data.w	.Ldw_loc_begin+1074
	.section	.debug_loc		;off: 1074
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	83
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	16
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20695
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 14114
	.data.b	71,114,112,82,101,113,83,114,99,0
	.section	.debug_info		;off: 20705
	.data.w	.Ldw_str_begin+14114
	.data.b	190,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1105
	.section	.debug_loc		;off: 1105
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20723
	.data.b	7
	.section	.debug_str		;off: 14124
	.data.b	67,104,67,110,116,0
	.section	.debug_info		;off: 20724
	.data.w	.Ldw_str_begin+14124
	.data.b	191,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1124
	.section	.debug_loc		;off: 1124
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20742
	.data.b	7
	.section	.debug_str		;off: 14130
	.data.b	84,111,116,97,108,71,114,112,67,104,0
	.section	.debug_info		;off: 20743
	.data.w	.Ldw_str_begin+14130
	.data.b	192,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1143
	.section	.debug_loc		;off: 1143
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20761
	.data.b	7
	.section	.debug_str		;off: 14141
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 20762
	.data.w	.Ldw_str_begin+14141
	.data.b	193,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1163
	.section	.debug_loc		;off: 1163
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20780
	.data.b	7
	.section	.debug_str		;off: 14147
	.data.b	73,110,116,67,104,78,114,0
	.section	.debug_info		;off: 20781
	.data.w	.Ldw_str_begin+14147
	.data.b	194,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+16357
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1183
	.section	.debug_loc		;off: 1183
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20799
	.data.b	7
	.section	.debug_str		;off: 14155
	.data.b	67,111,110,118,101,114,115,105,111,110,77,111,100,101,0
	.section	.debug_info		;off: 20800
	.data.w	.Ldw_str_begin+14155
	.data.b	195,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1202
	.section	.debug_loc		;off: 1202
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20818
	.data.b	7
	.section	.debug_str		;off: 14170
	.data.b	72,119,85,110,105,116,67,110,116,0
	.section	.debug_info		;off: 20819
	.data.w	.Ldw_str_begin+14170
	.data.b	197,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1221
	.section	.debug_loc		;off: 1221
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	5
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20837
	.data.b	8
	.section	.debug_str		;off: 14180
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 20838
	.data.w	.Ldw_str_begin+14180
	.data.b	199,19
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14188
	.data.b	82,115,108,116,73,110,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 20853
	.data.w	.Ldw_str_begin+14188
	.data.b	200,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+15958
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1241
	.section	.debug_loc		;off: 1241
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	32
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20871
	.data.b	8
	.section	.debug_str		;off: 14202
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20872
	.data.w	.Ldw_str_begin+14202
	.data.b	201,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14209
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 20887
	.data.w	.Ldw_str_begin+14209
	.data.b	202,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1261
	.section	.debug_loc		;off: 1261
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20905
	.data.b	7
	.section	.debug_str		;off: 14223
	.data.b	67,104,67,111,110,102,105,103,0
	.section	.debug_info		;off: 20906
	.data.w	.Ldw_str_begin+14223
	.data.b	203,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+16238
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1280
	.section	.debug_loc		;off: 1280
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	20
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20924
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14232
	.data.b	65,100,99,95,67,104,101,99,107,71,114,111,117,112,83,116,97,116,117,115,65,108,108,0
	.section	.debug_info		;off: 20927
	.data.w	.Ldw_str_begin+14232
	.data.b	179,21
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckGroupStatusAll
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckGroupStatusAll-Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2556
	.data.b	0,5,2
	.data.w	Adc_CheckGroupStatusAll..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	182,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	203
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	110
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	124
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20962
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	8
	.section	.debug_str		;off: 14256
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 20972
	.data.w	.Ldw_str_begin+14256
	.data.b	184,21
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14264
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 20987
	.data.w	.Ldw_str_begin+14264
	.data.b	185,21
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1300
	.section	.debug_loc		;off: 1300
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21005
	.data.b	8
	.section	.debug_str		;off: 14271
	.data.b	76,111,111,112,67,116,114,0
	.section	.debug_info		;off: 21006
	.data.w	.Ldw_str_begin+14271
	.data.b	186,21
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14279
	.data.b	65,108,108,71,114,112,83,116,97,116,0
	.section	.debug_info		;off: 21021
	.data.w	.Ldw_str_begin+14279
	.data.b	187,21
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14290
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21036
	.data.w	.Ldw_str_begin+14290
	.data.b	188,21
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1319
	.section	.debug_loc		;off: 1319
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21054
	.data.b	8
	.section	.debug_str		;off: 14297
	.data.b	75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 21055
	.data.w	.Ldw_str_begin+14297
	.data.b	189,21
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14307
	.data.b	65,100,99,95,67,104,101,99,107,68,114,105,118,101,114,83,116,97,116,101,0
	.section	.debug_info		;off: 21072
	.data.w	.Ldw_str_begin+14307
	.data.b	251,21
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckDriverState
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckDriverState-Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2637
	.data.b	0,5,2
	.data.w	Adc_CheckDriverState..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	255,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	61
	.data.b	61
	.data.b	91
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21107
	.data.b	22
	.section	.debug_str		;off: 14328
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 21108
	.data.w	.Ldw_str_begin+14328
	.data.b	253,21
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+1338
	.section	.debug_loc		;off: 1338
	.data.w	.LDW73
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21125
	.data.b	22
	.section	.debug_str		;off: 14334
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 21126
	.data.w	.Ldw_str_begin+14334
	.data.b	254,21
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+1357
	.section	.debug_loc		;off: 1357
	.data.w	.LDW73
	.data.w	.LDW93
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21143
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 14343
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 21153
	.data.w	.Ldw_str_begin+14343
	.data.b	129,22
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1376
	.section	.debug_loc		;off: 1376
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21171
	.data.b	7
	.section	.debug_str		;off: 14351
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 21172
	.data.w	.Ldw_str_begin+14351
	.data.b	130,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1395
	.section	.debug_loc		;off: 1395
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21190
	.data.b	8
	.section	.debug_str		;off: 14358
	.data.b	71,114,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21191
	.data.w	.Ldw_str_begin+14358
	.data.b	131,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14368
	.data.b	71,114,112,82,101,115,0
	.section	.debug_info		;off: 21206
	.data.w	.Ldw_str_begin+14368
	.data.b	132,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1414
	.section	.debug_loc		;off: 1414
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21224
	.data.b	7
	.section	.debug_str		;off: 14375
	.data.b	78,111,79,102,86,97,108,105,100,67,111,110,118,0
	.section	.debug_info		;off: 21225
	.data.w	.Ldw_str_begin+14375
	.data.b	133,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1433
	.section	.debug_loc		;off: 1433
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21243
	.data.b	8
	.section	.debug_str		;off: 14389
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21244
	.data.w	.Ldw_str_begin+14389
	.data.b	134,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14396
	.data.b	65,100,99,95,67,104,101,99,107,73,110,105,116,0
	.section	.debug_info		;off: 21261
	.data.w	.Ldw_str_begin+14396
	.data.b	189,22
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckInit
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
	.data.w	Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckInit-Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2696
	.data.b	0,5,2
	.data.w	Adc_CheckInit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	192,22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	75
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
	.section	.debug_info		;off: 21296
	.data.b	22
	.section	.debug_str		;off: 14410
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 21297
	.data.w	.Ldw_str_begin+14410
	.data.b	191,22
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.w	.Ldw_loc_begin+1452
	.section	.debug_loc		;off: 1452
	.data.w	.LDW04
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21314
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	7
	.section	.debug_str		;off: 14420
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 21324
	.data.w	.Ldw_str_begin+14420
	.data.b	194,22
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1471
	.section	.debug_loc		;off: 1471
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21342
	.data.b	8
	.section	.debug_str		;off: 14427
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21343
	.data.w	.Ldw_str_begin+14427
	.data.b	195,22
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14434
	.data.b	65,100,99,95,67,111,109,109,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 21360
	.data.w	.Ldw_str_begin+14434
	.data.b	246,22
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CommDetCheck
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

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CommDetCheck-Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2758
	.data.b	0,5,2
	.data.w	Adc_CommDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	251,22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	141
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	44
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	2
	.data.b	0
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	91
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	12
	.data.b	91
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	91
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
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
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21395
	.data.b	22
	.section	.debug_str		;off: 14451
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 21396
	.data.w	.Ldw_str_begin+14451
	.data.b	248,22
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.w	.Ldw_loc_begin+1490
	.section	.debug_loc		;off: 1490
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	80
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21413
	.data.b	22
	.section	.debug_str		;off: 14461
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 21414
	.data.w	.Ldw_str_begin+14461
	.data.b	249,22
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+1520
	.section	.debug_loc		;off: 1520
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	81
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21431
	.data.b	22
	.section	.debug_str		;off: 14467
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 21432
	.data.w	.Ldw_str_begin+14467
	.data.b	250,22
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+1550
	.section	.debug_loc		;off: 1550
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	82
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21449
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 14476
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 21459
	.data.w	.Ldw_str_begin+14476
	.data.b	253,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1580
	.section	.debug_loc		;off: 1580
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21477
	.data.b	7
	.section	.debug_str		;off: 14483
	.data.b	67,102,103,80,116,114,0
	.section	.debug_info		;off: 21478
	.data.w	.Ldw_str_begin+14483
	.data.b	254,22
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1599
	.section	.debug_loc		;off: 1599
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21496
	.data.b	7
	.section	.debug_str		;off: 14490
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 21497
	.data.w	.Ldw_str_begin+14490
	.data.b	255,22
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1618
	.section	.debug_loc		;off: 1618
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21515
	.data.b	7
	.section	.debug_str		;off: 14497
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21516
	.data.w	.Ldw_str_begin+14497
	.data.b	128,23
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1637
	.section	.debug_loc		;off: 1637
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21534
	.data.b	8
	.section	.debug_str		;off: 14504
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 21535
	.data.w	.Ldw_str_begin+14504
	.data.b	129,23
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14518
	.data.b	65,100,99,95,68,101,116,69,114,114,111,114,67,104,101,99,107,0
	.section	.debug_info		;off: 21552
	.data.w	.Ldw_str_begin+14518
	.data.b	253,23
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_DetErrorCheck
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_DetErrorCheck-Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2908
	.data.b	0,5,2
	.data.w	Adc_DetErrorCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	130,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	27
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21587
	.data.b	22
	.section	.debug_str		;off: 14536
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 21588
	.data.w	.Ldw_str_begin+14536
	.data.b	255,23
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.w	.Ldw_loc_begin+1656
	.section	.debug_loc		;off: 1656
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	80
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21605
	.data.b	22
	.section	.debug_str		;off: 14546
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 21606
	.data.w	.Ldw_str_begin+14546
	.data.b	128,24
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+1686
	.section	.debug_loc		;off: 1686
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	81
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21623
	.data.b	22
	.section	.debug_str		;off: 14552
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 21624
	.data.w	.Ldw_str_begin+14552
	.data.b	129,24
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+1716
	.section	.debug_loc		;off: 1716
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	82
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21641
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 14561
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 21651
	.data.w	.Ldw_str_begin+14561
	.data.b	132,24
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1746
	.section	.debug_loc		;off: 1746
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21669
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14567
	.data.b	65,100,99,95,67,104,101,99,107,73,110,105,116,80,97,114,97,109,0
	.section	.debug_info		;off: 21672
	.data.w	.Ldw_str_begin+14567
	.data.b	175,24
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckInitParam
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckInitParam-Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2945
	.data.b	0,5,2
	.data.w	Adc_CheckInitParam..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	178,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	13
	.data.b	59
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	15
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
	.section	.debug_info		;off: 21707
	.data.b	22
	.section	.debug_str		;off: 14586
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 21708
	.data.w	.Ldw_str_begin+14586
	.data.b	177,24
	.data.b	61
	.data.b	1
	.data.w	.Ldw_begin+546
	.data.b	0
	.data.w	.Ldw_loc_begin+1765
	.section	.debug_loc		;off: 1765
	.data.w	.LDW94
	.data.w	.LDW15
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21725
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 14596
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21735
	.data.w	.Ldw_str_begin+14596
	.data.b	180,24
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1784
	.section	.debug_loc		;off: 1784
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21753
	.data.b	7
	.section	.debug_str		;off: 14603
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 21754
	.data.w	.Ldw_str_begin+14603
	.data.b	181,24
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1803
	.section	.debug_loc		;off: 1803
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21772
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14610
	.data.b	65,100,99,95,67,104,101,99,107,83,119,67,111,110,118,0
	.section	.debug_info		;off: 21775
	.data.w	.Ldw_str_begin+14610
	.data.b	247,24
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckSwConv
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckSwConv-Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3028
	.data.b	0,5,2
	.data.w	Adc_CheckSwConv..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	253,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	91
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	12
	.data.b	61
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	219
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
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
	.section	.debug_info		;off: 21810
	.data.b	22
	.section	.debug_str		;off: 14626
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21811
	.data.w	.Ldw_str_begin+14626
	.data.b	249,24
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.w	.Ldw_loc_begin+1822
	.section	.debug_loc		;off: 1822
	.data.w	.LDW25
	.data.w	.LDW45
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21828
	.data.b	22
	.section	.debug_str		;off: 14633
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 21829
	.data.w	.Ldw_str_begin+14633
	.data.b	250,24
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+1841
	.section	.debug_loc		;off: 1841
	.data.w	.LDW25
	.data.w	.LDW45
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21846
	.data.b	22
	.section	.debug_str		;off: 14642
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 21847
	.data.w	.Ldw_str_begin+14642
	.data.b	251,24
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+1860
	.section	.debug_loc		;off: 1860
	.data.w	.LDW25
	.data.w	.LDW45
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21864
	.data.b	22
	.section	.debug_str		;off: 14648
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 21865
	.data.w	.Ldw_str_begin+14648
	.data.b	252,24
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+1879
	.section	.debug_loc		;off: 1879
	.data.w	.LDW25
	.data.w	.LDW45
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21882
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	8
	.section	.debug_str		;off: 14661
	.data.b	68,97,116,97,86,97,108,117,101,66,102,80,116,114,0
	.section	.debug_info		;off: 21892
	.data.w	.Ldw_str_begin+14661
	.data.b	255,24
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+600
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14676
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 21907
	.data.w	.Ldw_str_begin+14676
	.data.b	128,25
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14683
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 21922
	.data.w	.Ldw_str_begin+14683
	.data.b	129,25
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1898
	.section	.debug_loc		;off: 1898
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21940
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14690
	.data.b	65,100,99,95,67,104,101,99,107,80,97,114,97,109,71,114,112,69,110,97,98,108,101,72,119,84,114,105,103,103,0
	.section	.debug_info		;off: 21943
	.data.w	.Ldw_str_begin+14690
	.data.b	200,25
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckParamGrpEnableHwTrigg
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckParamGrpEnableHwTrigg-Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3098
	.data.b	0,5,2
	.data.w	Adc_CheckParamGrpEnableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	206,25
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	75
	.data.b	12
	.data.b	12
	.data.b	61
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	219
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
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
	.section	.debug_info		;off: 21978
	.data.b	22
	.section	.debug_str		;off: 14721
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21979
	.data.w	.Ldw_str_begin+14721
	.data.b	202,25
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.w	.Ldw_loc_begin+1917
	.section	.debug_loc		;off: 1917
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21996
	.data.b	22
	.section	.debug_str		;off: 14728
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 21997
	.data.w	.Ldw_str_begin+14728
	.data.b	203,25
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+1936
	.section	.debug_loc		;off: 1936
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22014
	.data.b	22
	.section	.debug_str		;off: 14734
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 22015
	.data.w	.Ldw_str_begin+14734
	.data.b	204,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+1955
	.section	.debug_loc		;off: 1955
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22032
	.data.b	22
	.section	.debug_str		;off: 14743
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 22033
	.data.w	.Ldw_str_begin+14743
	.data.b	205,25
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+270
	.data.b	0
	.data.w	.Ldw_loc_begin+1974
	.section	.debug_loc		;off: 1974
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22050
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	8
	.section	.debug_str		;off: 14756
	.data.b	68,97,116,97,86,97,108,117,101,66,102,80,116,114,0
	.section	.debug_info		;off: 22060
	.data.w	.Ldw_str_begin+14756
	.data.b	208,25
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+600
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14771
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 22075
	.data.w	.Ldw_str_begin+14771
	.data.b	209,25
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1993
	.section	.debug_loc		;off: 1993
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22093
	.data.b	7
	.section	.debug_str		;off: 14778
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 22094
	.data.w	.Ldw_str_begin+14778
	.data.b	210,25
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2012
	.section	.debug_loc		;off: 2012
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22112
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14785
	.data.b	65,100,99,95,67,104,101,99,107,80,97,114,97,109,71,114,112,68,105,115,97,98,108,101,72,119,84,114,105,103,103,0
	.section	.debug_info		;off: 22115
	.data.w	.Ldw_str_begin+14785
	.data.b	154,26
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckParamGrpDisableHwTrigg
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckParamGrpDisableHwTrigg-Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3169
	.data.b	0,5,2
	.data.w	Adc_CheckParamGrpDisableHwTrigg..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	158,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	59
	.data.b	12
	.data.b	91
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	43
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 22150
	.data.b	22
	.section	.debug_str		;off: 14817
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 22151
	.data.w	.Ldw_str_begin+14817
	.data.b	156,26
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.w	.Ldw_loc_begin+2031
	.section	.debug_loc		;off: 2031
	.data.w	.LDW85
	.data.w	.LDW06
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22168
	.data.b	22
	.section	.debug_str		;off: 14827
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 22169
	.data.w	.Ldw_str_begin+14827
	.data.b	157,26
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+316
	.data.b	0
	.data.w	.Ldw_loc_begin+2050
	.section	.debug_loc		;off: 2050
	.data.w	.LDW85
	.data.w	.LDW06
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22186
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	8
	.section	.debug_str		;off: 14834
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 22196
	.data.w	.Ldw_str_begin+14834
	.data.b	160,26
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14841
	.data.b	65,100,99,95,67,104,101,99,107,77,117,108,116,105,99,111,114,101,65,108,108,111,99,97,116,101,69,114,114,111,114,0
	.section	.debug_info		;off: 22213
	.data.w	.Ldw_str_begin+14841
	.data.b	213,26
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckMulticoreAllocateError
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_CheckMulticoreAllocateError-Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3204
	.data.b	0,5,2
	.data.w	Adc_CheckMulticoreAllocateError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	217,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	2
	.data.b	24
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	2
	.data.b	0
	.data.b	27
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	13
	.data.b	75
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	59
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
	.section	.debug_info		;off: 22248
	.data.b	22
	.section	.debug_str		;off: 14873
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 22249
	.data.w	.Ldw_str_begin+14873
	.data.b	215,26
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.w	.Ldw_loc_begin+2069
	.section	.debug_loc		;off: 2069
	.data.w	.LDW16
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22266
	.data.b	22
	.section	.debug_str		;off: 14883
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 22267
	.data.w	.Ldw_str_begin+14883
	.data.b	216,26
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+2088
	.section	.debug_loc		;off: 2088
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	81
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22284
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 14892
	.data.b	82,101,116,69,114,114,0
	.section	.debug_info		;off: 22294
	.data.w	.Ldw_str_begin+14892
	.data.b	219,26
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2118
	.section	.debug_loc		;off: 2118
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22312
	.data.b	8
	.section	.debug_str		;off: 14899
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22313
	.data.w	.Ldw_str_begin+14899
	.data.b	220,26
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14906
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 22328
	.data.w	.Ldw_str_begin+14906
	.data.b	221,26
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2137
	.section	.debug_loc		;off: 2137
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22346
	.data.b	8
	.section	.debug_str		;off: 14920
	.data.b	67,102,103,80,116,114,0
	.section	.debug_info		;off: 22347
	.data.w	.Ldw_str_begin+14920
	.data.b	222,26
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 14927
	.data.b	65,100,99,95,82,101,115,101,116,84,114,105,103,83,114,99,68,97,116,97,0
	.section	.debug_info		;off: 22364
	.data.w	.Ldw_str_begin+14927
	.data.b	167,27
	.data.b	37
	.data.b	1
	.data.w	Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_ResetTrigSrcData
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_ResetTrigSrcData-Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3294
	.data.b	0,5,2
	.data.w	Adc_ResetTrigSrcData..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	174,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 22393
	.data.b	22
	.section	.debug_str		;off: 14948
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 22394
	.data.w	.Ldw_str_begin+14948
	.data.b	169,27
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+316
	.data.b	0
	.data.w	.Ldw_loc_begin+2156
	.section	.debug_loc		;off: 2156
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22411
	.data.b	22
	.section	.debug_str		;off: 14955
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 22412
	.data.w	.Ldw_str_begin+14955
	.data.b	171,27
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+380
	.data.b	0
	.data.w	.Ldw_loc_begin+2175
	.section	.debug_loc		;off: 2175
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22429
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14963
	.data.b	65,100,99,95,82,101,97,100,71,114,111,117,112,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 22441
	.data.w	.Ldw_str_begin+14963
	.data.b	218,27
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_ReadGroupDetCheck
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_ReadGroupDetCheck-Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3319
	.data.b	0,5,2
	.data.w	Adc_ReadGroupDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	223,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	75
	.data.b	43
	.data.b	11
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	92
	.data.b	2
	.data.b	0
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
	.section	.debug_info		;off: 22476
	.data.b	22
	.section	.debug_str		;off: 14985
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 22477
	.data.w	.Ldw_str_begin+14985
	.data.b	220,27
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+2194
	.section	.debug_loc		;off: 2194
	.data.w	.LDW76
	.data.w	.LDW96
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22494
	.data.b	22
	.section	.debug_str		;off: 14993
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 22495
	.data.w	.Ldw_str_begin+14993
	.data.b	221,27
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+2213
	.section	.debug_loc		;off: 2213
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	81
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22512
	.data.b	22
	.section	.debug_str		;off: 15005
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 22513
	.data.w	.Ldw_str_begin+15005
	.data.b	222,27
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+600
	.data.b	0
	.data.w	.Ldw_loc_begin+2243
	.section	.debug_loc		;off: 2243
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	82
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22530
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	8
	.section	.debug_str		;off: 15019
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22540
	.data.w	.Ldw_str_begin+15019
	.data.b	226,27
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 15026
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 22555
	.data.w	.Ldw_str_begin+15026
	.data.b	227,27
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15040
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 22570
	.data.w	.Ldw_str_begin+15040
	.data.b	229,27
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2273
	.section	.debug_loc		;off: 2273
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22588
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15046
	.data.b	65,100,99,95,76,111,99,97,108,68,105,115,97,98,108,101,72,97,114,100,119,97,114,101,84,114,105,103,103,101,114,0
	.section	.debug_info		;off: 22591
	.data.w	.Ldw_str_begin+15046
	.data.b	165,28
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.w	Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_LocalDisableHardwareTrigger
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.w	__ghs_eofn_Adc_LocalDisableHardwareTrigger-Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3407
	.data.b	0,5,2
	.data.w	Adc_LocalDisableHardwareTrigger..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CAdc.
	.data.b	6
	.data.b	3
	.data.b	171,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	173
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	77
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	45
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
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
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 22626
	.data.b	22
	.section	.debug_str		;off: 15078
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 22627
	.data.w	.Ldw_str_begin+15078
	.data.b	167,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+2292
	.section	.debug_loc		;off: 2292
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	80
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22644
	.data.b	22
	.section	.debug_str		;off: 15086
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 22645
	.data.w	.Ldw_str_begin+15086
	.data.b	168,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+2322
	.section	.debug_loc		;off: 2322
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	81
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22662
	.data.b	22
	.section	.debug_str		;off: 15098
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 22663
	.data.w	.Ldw_str_begin+15098
	.data.b	169,28
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.w	.Ldw_loc_begin+2352
	.section	.debug_loc		;off: 2352
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	82
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22680
	.data.b	22
	.section	.debug_str		;off: 15106
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22681
	.data.w	.Ldw_str_begin+15106
	.data.b	170,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.w	.Ldw_loc_begin+2382
	.section	.debug_loc		;off: 2382
	.data.w	.LDW07
	.data.w	.LDW27
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22698
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	8
	.section	.debug_str		;off: 15113
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 22708
	.data.w	.Ldw_str_begin+15113
	.data.b	173,28
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15127
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 22723
	.data.w	.Ldw_str_begin+15127
	.data.b	174,28
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2401
	.section	.debug_loc		;off: 2401
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22741
	.data.b	7
	.section	.debug_str		;off: 15141
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 22742
	.data.w	.Ldw_str_begin+15141
	.data.b	175,28
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2420
	.section	.debug_loc		;off: 2420
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22760
	.data.b	8
	.section	.debug_str		;off: 15148
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 22761
	.data.w	.Ldw_str_begin+15148
	.data.b	176,28
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15161
	.data.b	65,100,99,95,73,110,105,116,0
	.section	.debug_info		;off: 22778
	.data.w	.Ldw_str_begin+15161
	.data.b	199,29
	.data.b	29
	.data.b	1
	.data.w	Adc_Init
	.data.w	__ghs_eofn_Adc_Init
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_Init
	.data.w	__ghs_eofn_Adc_Init-Adc_Init
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3517
	.data.b	0,5,2
	.data.w	Adc_Init
	.data.b	6
	.data.b	3
	.data.b	203,29
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	43
	.data.b	44
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	3
	.data.b	204,0
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	178,127
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	109
	.data.b	28
	.data.b	27
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	36
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	28
	.data.b	13
	.data.b	12
	.data.b	92
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	179,127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	215,0
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
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
	.section	.debug_info		;off: 22809
	.data.b	22
	.section	.debug_str		;off: 15170
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 22810
	.data.w	.Ldw_str_begin+15170
	.data.b	202,29
	.data.b	56
	.data.b	1
	.data.w	.Ldw_begin+541
	.data.b	0
	.data.w	.Ldw_loc_begin+2439
	.section	.debug_loc		;off: 2439
	.data.w	.LDW37
	.data.w	.LDW47
	.data.b	1,0
	.data.b	80
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22827
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 15180
	.data.b	67,110,116,0
	.section	.debug_info		;off: 22837
	.data.w	.Ldw_str_begin+15180
	.data.b	205,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2469
	.section	.debug_loc		;off: 2469
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22855
	.data.b	8
	.section	.debug_str		;off: 15184
	.data.b	72,119,85,110,105,116,82,101,97,100,70,108,97,103,0
	.section	.debug_info		;off: 22856
	.data.w	.Ldw_str_begin+15184
	.data.b	206,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15199
	.data.b	72,87,85,110,105,116,73,100,120,0
	.section	.debug_info		;off: 22871
	.data.w	.Ldw_str_begin+15199
	.data.b	207,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2488
	.section	.debug_loc		;off: 2488
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22889
	.data.b	8
	.section	.debug_str		;off: 15209
	.data.b	67,104,73,100,120,0
	.section	.debug_info		;off: 22890
	.data.w	.Ldw_str_begin+15209
	.data.b	208,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15215
	.data.b	75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 22905
	.data.w	.Ldw_str_begin+15215
	.data.b	209,29
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2507
	.section	.debug_loc		;off: 2507
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22923
	.data.b	7
	.section	.debug_str		;off: 15225
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22924
	.data.w	.Ldw_str_begin+15225
	.data.b	210,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2526
	.section	.debug_loc		;off: 2526
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22942
	.data.b	7
	.section	.debug_str		;off: 15232
	.data.b	69,114,114,0
	.section	.debug_info		;off: 22943
	.data.w	.Ldw_str_begin+15232
	.data.b	212,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2545
	.section	.debug_loc		;off: 2545
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22961
	.data.b	7
	.section	.debug_str		;off: 15236
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 22962
	.data.w	.Ldw_str_begin+15236
	.data.b	214,29
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2564
	.section	.debug_loc		;off: 2564
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22980
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15250
	.data.b	65,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 22983
	.data.w	.Ldw_str_begin+15250
	.data.b	236,30
	.data.b	29
	.data.b	1
	.data.w	Adc_DeInit
	.data.w	__ghs_eofn_Adc_DeInit
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_DeInit
	.data.w	__ghs_eofn_Adc_DeInit-Adc_DeInit
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3695
	.data.b	0,5,2
	.data.w	Adc_DeInit
	.data.b	6
	.data.b	3
	.data.b	239,30
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	140
	.data.b	29
	.data.b	28
	.data.b	43
	.data.b	43
	.data.b	13
	.data.b	93
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	95
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
	.data.b	139
	.data.b	3
	.data.b	32
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	91
	.data.b	13
	.data.b	12
	.data.b	76
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
	.section	.debug_info		;off: 23014
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	8
	.section	.debug_str		;off: 15261
	.data.b	69,114,114,0
	.section	.debug_info		;off: 23024
	.data.w	.Ldw_str_begin+15261
	.data.b	241,30
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 15265
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 23039
	.data.w	.Ldw_str_begin+15265
	.data.b	242,30
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15276
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 23054
	.data.w	.Ldw_str_begin+15276
	.data.b	244,30
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2583
	.section	.debug_loc		;off: 2583
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23072
	.data.b	8
	.section	.debug_str		;off: 15284
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 23073
	.data.w	.Ldw_str_begin+15284
	.data.b	246,30
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15296
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 23088
	.data.w	.Ldw_str_begin+15296
	.data.b	247,30
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2602
	.section	.debug_loc		;off: 2602
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23106
	.data.b	7
	.section	.debug_str		;off: 15310
	.data.b	75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 23107
	.data.w	.Ldw_str_begin+15310
	.data.b	249,30
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2621
	.section	.debug_loc		;off: 2621
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23125
	.data.b	7
	.section	.debug_str		;off: 15320
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 23126
	.data.w	.Ldw_str_begin+15320
	.data.b	251,30
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2640
	.section	.debug_loc		;off: 2640
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23144
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15327
	.data.b	65,100,99,95,83,101,116,117,112,82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 23147
	.data.w	.Ldw_str_begin+15327
	.data.b	228,31
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_SetupResultBuffer
	.data.w	__ghs_eofn_Adc_SetupResultBuffer
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
	.data.w	Adc_SetupResultBuffer
	.data.w	__ghs_eofn_Adc_SetupResultBuffer-Adc_SetupResultBuffer
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3801
	.data.b	0,5,2
	.data.w	Adc_SetupResultBuffer
	.data.b	6
	.data.b	3
	.data.b	234,31
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin33
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	75
	.data.b	140
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	92
	.data.b	59
	.data.b	13
	.data.b	28
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
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
	.section	.debug_info		;off: 23182
	.data.b	22
	.section	.debug_str		;off: 15349
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 23183
	.data.w	.Ldw_str_begin+15349
	.data.b	230,31
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+2659
	.section	.debug_loc		;off: 2659
	.data.w	.LDW97
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23200
	.data.b	22
	.section	.debug_str		;off: 15355
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 23201
	.data.w	.Ldw_str_begin+15355
	.data.b	233,31
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.w	.Ldw_loc_begin+2678
	.section	.debug_loc		;off: 2678
	.data.w	.LDW97
	.data.w	.LDW08
	.data.b	1,0
	.data.b	81
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23218
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	8
	.section	.debug_str		;off: 15369
	.data.b	72,119,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 23228
	.data.w	.Ldw_str_begin+15369
	.data.b	238,31
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15381
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 23243
	.data.w	.Ldw_str_begin+15381
	.data.b	241,31
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2708
	.section	.debug_loc		;off: 2708
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23261
	.data.b	7
	.section	.debug_str		;off: 15389
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 23262
	.data.w	.Ldw_str_begin+15389
	.data.b	242,31
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2727
	.section	.debug_loc		;off: 2727
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23280
	.data.b	7
	.section	.debug_str		;off: 15399
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 23281
	.data.w	.Ldw_str_begin+15399
	.data.b	243,31
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2746
	.section	.debug_loc		;off: 2746
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23299
	.data.b	7
	.section	.debug_str		;off: 15411
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 23300
	.data.w	.Ldw_str_begin+15411
	.data.b	244,31
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2765
	.section	.debug_loc		;off: 2765
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23318
	.data.b	7
	.section	.debug_str		;off: 15418
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 23319
	.data.w	.Ldw_str_begin+15418
	.data.b	245,31
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+236
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2784
	.section	.debug_loc		;off: 2784
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23337
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15426
	.data.b	65,100,99,95,83,116,97,114,116,71,114,111,117,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 23340
	.data.w	.Ldw_str_begin+15426
	.data.b	232,32
	.data.b	29
	.data.b	1
	.data.w	Adc_StartGroupConversion
	.data.w	__ghs_eofn_Adc_StartGroupConversion
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

	.section	.debug_frame		;off: 720
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_StartGroupConversion
	.data.w	__ghs_eofn_Adc_StartGroupConversion-Adc_StartGroupConversion
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3938
	.data.b	0,5,2
	.data.w	Adc_StartGroupConversion
	.data.b	6
	.data.b	3
	.data.b	235,32
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	76
	.data.b	28
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	61
	.data.b	29
	.data.b	93
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	20
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	13
	.data.b	61
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
	.data.b	29
	.data.b	59
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	75
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
	.section	.debug_info		;off: 23371
	.data.b	22
	.section	.debug_str		;off: 15451
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 23372
	.data.w	.Ldw_str_begin+15451
	.data.b	234,32
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+2803
	.section	.debug_loc		;off: 2803
	.data.w	.LDW28
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23389
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	7
	.section	.debug_str		;off: 15457
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 23399
	.data.w	.Ldw_str_begin+15457
	.data.b	237,32
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2822
	.section	.debug_loc		;off: 2822
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23417
	.data.b	7
	.section	.debug_str		;off: 15470
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 23418
	.data.w	.Ldw_str_begin+15470
	.data.b	238,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2841
	.section	.debug_loc		;off: 2841
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23436
	.data.b	7
	.section	.debug_str		;off: 15478
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 23437
	.data.w	.Ldw_str_begin+15478
	.data.b	239,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2860
	.section	.debug_loc		;off: 2860
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23455
	.data.b	8
	.section	.debug_str		;off: 15490
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 23456
	.data.w	.Ldw_str_begin+15490
	.data.b	240,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 15497
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 23471
	.data.w	.Ldw_str_begin+15497
	.data.b	241,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15511
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 23486
	.data.w	.Ldw_str_begin+15511
	.data.b	243,32
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2879
	.section	.debug_loc		;off: 2879
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23504
	.data.b	7
	.section	.debug_str		;off: 15519
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 23505
	.data.w	.Ldw_str_begin+15519
	.data.b	244,32
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2898
	.section	.debug_loc		;off: 2898
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23523
	.data.b	7
	.section	.debug_str		;off: 15526
	.data.b	71,114,112,82,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 23524
	.data.w	.Ldw_str_begin+15526
	.data.b	245,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2917
	.section	.debug_loc		;off: 2917
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23542
	.data.b	7
	.section	.debug_str		;off: 15543
	.data.b	69,114,114,0
	.section	.debug_info		;off: 23543
	.data.w	.Ldw_str_begin+15543
	.data.b	247,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2936
	.section	.debug_loc		;off: 2936
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23561
	.data.b	7
	.section	.debug_str		;off: 15547
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 23562
	.data.w	.Ldw_str_begin+15547
	.data.b	248,32
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2955
	.section	.debug_loc		;off: 2955
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23580
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15561
	.data.b	65,100,99,95,83,116,111,112,71,114,111,117,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 23583
	.data.w	.Ldw_str_begin+15561
	.data.b	144,34
	.data.b	29
	.data.b	1
	.data.w	Adc_StopGroupConversion
	.data.w	__ghs_eofn_Adc_StopGroupConversion
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

	.section	.debug_frame		;off: 744
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_StopGroupConversion
	.data.w	__ghs_eofn_Adc_StopGroupConversion-Adc_StopGroupConversion
	.data.b	1
	.data.w	.LDW78
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4081
	.data.b	0,5,2
	.data.w	Adc_StopGroupConversion
	.data.b	6
	.data.b	3
	.data.b	147,34
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin36
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin37
	.data.b	13
	.data.b	141
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	75
	.data.b	12
	.data.b	29
	.data.b	3
	.data.b	23
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	75
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	109
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	20
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
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
	.data.b	12
	.data.b	29
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 23614
	.data.b	22
	.section	.debug_str		;off: 15585
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 23615
	.data.w	.Ldw_str_begin+15585
	.data.b	146,34
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+2974
	.section	.debug_loc		;off: 2974
	.data.w	.LDW58
	.data.w	.LDW78
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23632
	.data.b	34
	.data.w	.LDW68
	.data.w	.LDW78

	.data.b	7
	.section	.debug_str		;off: 15591
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 23642
	.data.w	.Ldw_str_begin+15591
	.data.b	149,34
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2993
	.section	.debug_loc		;off: 2993
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23660
	.data.b	7
	.section	.debug_str		;off: 15599
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 23661
	.data.w	.Ldw_str_begin+15599
	.data.b	151,34
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3012
	.section	.debug_loc		;off: 3012
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23679
	.data.b	8
	.section	.debug_str		;off: 15606
	.data.b	69,114,114,0
	.section	.debug_info		;off: 23680
	.data.w	.Ldw_str_begin+15606
	.data.b	154,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15610
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 23695
	.data.w	.Ldw_str_begin+15610
	.data.b	156,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3031
	.section	.debug_loc		;off: 3031
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23713
	.data.b	7
	.section	.debug_str		;off: 15618
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 23714
	.data.w	.Ldw_str_begin+15618
	.data.b	157,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3050
	.section	.debug_loc		;off: 3050
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23732
	.data.b	7
	.section	.debug_str		;off: 15630
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 23733
	.data.w	.Ldw_str_begin+15630
	.data.b	161,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3069
	.section	.debug_loc		;off: 3069
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23751
	.data.b	8
	.section	.debug_str		;off: 15637
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 23752
	.data.w	.Ldw_str_begin+15637
	.data.b	162,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15651
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 23767
	.data.w	.Ldw_str_begin+15651
	.data.b	163,34
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3088
	.section	.debug_loc		;off: 3088
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23785
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15665
	.data.b	65,100,99,95,82,101,97,100,71,114,111,117,112,0
	.section	.debug_info		;off: 23788
	.data.w	.Ldw_str_begin+15665
	.data.b	202,35
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.w	Adc_ReadGroup
	.data.w	__ghs_eofn_Adc_ReadGroup
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

	.section	.debug_frame		;off: 768
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_ReadGroup
	.data.w	__ghs_eofn_Adc_ReadGroup-Adc_ReadGroup
	.data.b	1
	.data.w	.LDW09
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4232
	.data.b	0,5,2
	.data.w	Adc_ReadGroup
	.data.b	6
	.data.b	3
	.data.b	208,35
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	23
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin38
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin39
	.data.b	13
	.data.b	59
	.data.b	44
	.data.b	12
	.data.b	29
	.data.b	76
	.data.b	28
	.data.b	59
	.data.b	12
	.data.b	60
	.data.b	125
	.data.b	93
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	109
	.data.b	28
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
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
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	139
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	28
	.data.b	28
	.data.b	3
	.data.b	98
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	31
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	91
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
	.section	.debug_info		;off: 23823
	.data.b	22
	.section	.debug_str		;off: 15679
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 23824
	.data.w	.Ldw_str_begin+15679
	.data.b	204,35
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3107
	.section	.debug_loc		;off: 3107
	.data.w	.LDW88
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23841
	.data.b	22
	.section	.debug_str		;off: 15685
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 23842
	.data.w	.Ldw_str_begin+15685
	.data.b	207,35
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.w	.Ldw_loc_begin+3126
	.section	.debug_loc		;off: 3126
	.data.w	.LDW88
	.data.w	.LDW98
	.data.b	1,0
	.data.b	81
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23859
	.data.b	34
	.data.w	.LDW98
	.data.w	.LDW09

	.data.b	7
	.section	.debug_str		;off: 15699
	.data.b	78,111,79,102,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 23869
	.data.w	.Ldw_str_begin+15699
	.data.b	210,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3156
	.section	.debug_loc		;off: 3156
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23887
	.data.b	7
	.section	.debug_str		;off: 15712
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 23888
	.data.w	.Ldw_str_begin+15712
	.data.b	211,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3175
	.section	.debug_loc		;off: 3175
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23906
	.data.b	7
	.section	.debug_str		;off: 15720
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 23907
	.data.w	.Ldw_str_begin+15720
	.data.b	212,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3194
	.section	.debug_loc		;off: 3194
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23925
	.data.b	8
	.section	.debug_str		;off: 15730
	.data.b	78,111,79,102,86,97,108,105,100,67,111,110,118,0
	.section	.debug_info		;off: 23926
	.data.w	.Ldw_str_begin+15730
	.data.b	213,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15744
	.data.b	83,116,114,101,97,109,78,117,109,79,102,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 23941
	.data.w	.Ldw_str_begin+15744
	.data.b	214,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3213
	.section	.debug_loc		;off: 3213
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23959
	.data.b	8
	.section	.debug_str		;off: 15763
	.data.b	71,114,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 23960
	.data.w	.Ldw_str_begin+15763
	.data.b	215,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15773
	.data.b	71,114,112,82,101,115,0
	.section	.debug_info		;off: 23975
	.data.w	.Ldw_str_begin+15773
	.data.b	216,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3232
	.section	.debug_loc		;off: 3232
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 23993
	.data.b	7
	.section	.debug_str		;off: 15780
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 23994
	.data.w	.Ldw_str_begin+15780
	.data.b	217,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3251
	.section	.debug_loc		;off: 3251
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24012
	.data.b	7
	.section	.debug_str		;off: 15792
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 24013
	.data.w	.Ldw_str_begin+15792
	.data.b	218,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3270
	.section	.debug_loc		;off: 3270
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24031
	.data.b	8
	.section	.debug_str		;off: 15799
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 24032
	.data.w	.Ldw_str_begin+15799
	.data.b	219,35
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15813
	.data.b	72,119,85,110,105,116,67,110,116,0
	.section	.debug_info		;off: 24047
	.data.w	.Ldw_str_begin+15813
	.data.b	221,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3289
	.section	.debug_loc		;off: 3289
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24065
	.data.b	7
	.section	.debug_str		;off: 15823
	.data.b	83,121,110,99,71,114,112,83,108,97,118,101,82,115,108,116,83,116,97,114,116,80,111,115,0
	.section	.debug_info		;off: 24066
	.data.w	.Ldw_str_begin+15823
	.data.b	222,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2178
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3308
	.section	.debug_loc		;off: 3308
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24084
	.data.b	8
	.section	.debug_str		;off: 15848
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 24085
	.data.w	.Ldw_str_begin+15848
	.data.b	223,35
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15861
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 24100
	.data.w	.Ldw_str_begin+15861
	.data.b	225,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3327
	.section	.debug_loc		;off: 3327
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24118
	.data.b	7
	.section	.debug_str		;off: 15869
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 24119
	.data.w	.Ldw_str_begin+15869
	.data.b	226,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3346
	.section	.debug_loc		;off: 3346
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24137
	.data.b	7
	.section	.debug_str		;off: 15876
	.data.b	67,117,114,114,101,110,116,82,101,115,66,117,102,80,116,114,0
	.section	.debug_info		;off: 24138
	.data.w	.Ldw_str_begin+15876
	.data.b	227,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+600
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3365
	.section	.debug_loc		;off: 3365
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24156
	.data.b	7
	.section	.debug_str		;off: 15893
	.data.b	84,97,114,103,101,116,68,97,116,97,66,117,102,80,116,114,0
	.section	.debug_info		;off: 24157
	.data.w	.Ldw_str_begin+15893
	.data.b	228,35
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3384
	.section	.debug_loc		;off: 3384
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24175
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15910
	.data.b	65,100,99,95,69,110,97,98,108,101,72,97,114,100,119,97,114,101,84,114,105,103,103,101,114,0
	.section	.debug_info		;off: 24178
	.data.w	.Ldw_str_begin+15910
	.data.b	133,37
	.data.b	29
	.data.b	1
	.data.w	Adc_EnableHardwareTrigger
	.data.w	__ghs_eofn_Adc_EnableHardwareTrigger
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

	.section	.debug_frame		;off: 792
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_EnableHardwareTrigger
	.data.w	__ghs_eofn_Adc_EnableHardwareTrigger-Adc_EnableHardwareTrigger
	.data.b	1
	.data.w	.LDW39
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4409
	.data.b	0,5,2
	.data.w	Adc_EnableHardwareTrigger
	.data.b	6
	.data.b	3
	.data.b	136,37
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	76
	.data.b	28
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin40
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin41
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	24
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	13
	.data.b	61
	.data.b	28
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	29
	.data.b	59
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	75
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
	.section	.debug_info		;off: 24209
	.data.b	22
	.section	.debug_str		;off: 15936
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 24210
	.data.w	.Ldw_str_begin+15936
	.data.b	135,37
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3403
	.section	.debug_loc		;off: 3403
	.data.w	.LDW19
	.data.w	.LDW39
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24227
	.data.b	34
	.data.w	.LDW29
	.data.w	.LDW39

	.data.b	7
	.section	.debug_str		;off: 15942
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 24237
	.data.w	.Ldw_str_begin+15942
	.data.b	138,37
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3422
	.section	.debug_loc		;off: 3422
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24255
	.data.b	7
	.section	.debug_str		;off: 15950
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 24256
	.data.w	.Ldw_str_begin+15950
	.data.b	139,37
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3441
	.section	.debug_loc		;off: 3441
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24274
	.data.b	7
	.section	.debug_str		;off: 15957
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 24275
	.data.w	.Ldw_str_begin+15957
	.data.b	140,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3460
	.section	.debug_loc		;off: 3460
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24293
	.data.b	7
	.section	.debug_str		;off: 15965
	.data.b	71,114,112,82,101,113,117,101,115,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 24294
	.data.w	.Ldw_str_begin+15965
	.data.b	141,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3479
	.section	.debug_loc		;off: 3479
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24312
	.data.b	7
	.section	.debug_str		;off: 15982
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 24313
	.data.w	.Ldw_str_begin+15982
	.data.b	142,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3498
	.section	.debug_loc		;off: 3498
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24331
	.data.b	8
	.section	.debug_str		;off: 15994
	.data.b	65,100,99,75,101,114,110,101,108,80,116,114,0
	.section	.debug_info		;off: 24332
	.data.w	.Ldw_str_begin+15994
	.data.b	143,37
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16007
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 24347
	.data.w	.Ldw_str_begin+16007
	.data.b	144,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16014
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 24362
	.data.w	.Ldw_str_begin+16014
	.data.b	145,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16028
	.data.b	69,114,114,0
	.section	.debug_info		;off: 24377
	.data.w	.Ldw_str_begin+16028
	.data.b	146,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3517
	.section	.debug_loc		;off: 3517
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24395
	.data.b	7
	.section	.debug_str		;off: 16032
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 24396
	.data.w	.Ldw_str_begin+16032
	.data.b	147,37
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3536
	.section	.debug_loc		;off: 3536
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24414
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16046
	.data.b	65,100,99,95,68,105,115,97,98,108,101,72,97,114,100,119,97,114,101,84,114,105,103,103,101,114,0
	.section	.debug_info		;off: 24417
	.data.w	.Ldw_str_begin+16046
	.data.b	171,38
	.data.b	29
	.data.b	1
	.data.w	Adc_DisableHardwareTrigger
	.data.w	__ghs_eofn_Adc_DisableHardwareTrigger
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
	.data.w	Adc_DisableHardwareTrigger
	.data.w	__ghs_eofn_Adc_DisableHardwareTrigger-Adc_DisableHardwareTrigger
	.data.b	1
	.data.w	.LDW69
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4560
	.data.b	0,5,2
	.data.w	Adc_DisableHardwareTrigger
	.data.b	6
	.data.b	3
	.data.b	174,38
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin42
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin43
	.data.b	13
	.data.b	157
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
	.data.b	27
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
	.data.b	12
	.data.b	29
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 24448
	.data.b	22
	.section	.debug_str		;off: 16073
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 24449
	.data.w	.Ldw_str_begin+16073
	.data.b	173,38
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3555
	.section	.debug_loc		;off: 3555
	.data.w	.LDW49
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24466
	.data.b	34
	.data.w	.LDW59
	.data.w	.LDW69

	.data.b	7
	.section	.debug_str		;off: 16079
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 24476
	.data.w	.Ldw_str_begin+16079
	.data.b	176,38
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3574
	.section	.debug_loc		;off: 3574
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24494
	.data.b	7
	.section	.debug_str		;off: 16087
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 24495
	.data.w	.Ldw_str_begin+16087
	.data.b	177,38
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3593
	.section	.debug_loc		;off: 3593
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24513
	.data.b	7
	.section	.debug_str		;off: 16095
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 24514
	.data.w	.Ldw_str_begin+16095
	.data.b	178,38
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3612
	.section	.debug_loc		;off: 3612
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24532
	.data.b	7
	.section	.debug_str		;off: 16107
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 24533
	.data.w	.Ldw_str_begin+16107
	.data.b	179,38
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3631
	.section	.debug_loc		;off: 3631
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24551
	.data.b	7
	.section	.debug_str		;off: 16114
	.data.b	69,114,114,0
	.section	.debug_info		;off: 24552
	.data.w	.Ldw_str_begin+16114
	.data.b	181,38
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3650
	.section	.debug_loc		;off: 3650
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24570
	.data.b	8
	.section	.debug_str		;off: 16118
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 24571
	.data.w	.Ldw_str_begin+16118
	.data.b	183,38
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16132
	.data.b	65,100,99,95,69,110,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 24588
	.data.w	.Ldw_str_begin+16132
	.data.b	148,39
	.data.b	29
	.data.b	1
	.data.w	Adc_EnableGroupNotification
	.data.w	__ghs_eofn_Adc_EnableGroupNotification
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

	.section	.debug_frame		;off: 840
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_EnableGroupNotification
	.data.w	__ghs_eofn_Adc_EnableGroupNotification-Adc_EnableGroupNotification
	.data.b	1
	.data.w	.LDW99
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4651
	.data.b	0,5,2
	.data.w	Adc_EnableGroupNotification
	.data.b	6
	.data.b	3
	.data.b	151,39
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin44
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin45
	.data.b	13
	.data.b	157
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	24
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 24619
	.data.b	22
	.section	.debug_str		;off: 16160
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 24620
	.data.w	.Ldw_str_begin+16160
	.data.b	150,39
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3669
	.section	.debug_loc		;off: 3669
	.data.w	.LDW79
	.data.w	.LDW99
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24637
	.data.b	34
	.data.w	.LDW89
	.data.w	.LDW99

	.data.b	7
	.section	.debug_str		;off: 16166
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 24647
	.data.w	.Ldw_str_begin+16166
	.data.b	153,39
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3688
	.section	.debug_loc		;off: 3688
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24665
	.data.b	7
	.section	.debug_str		;off: 16174
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 24666
	.data.w	.Ldw_str_begin+16174
	.data.b	154,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3707
	.section	.debug_loc		;off: 3707
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24684
	.data.b	7
	.section	.debug_str		;off: 16182
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 24685
	.data.w	.Ldw_str_begin+16182
	.data.b	155,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3726
	.section	.debug_loc		;off: 3726
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24703
	.data.b	7
	.section	.debug_str		;off: 16191
	.data.b	69,114,114,0
	.section	.debug_info		;off: 24704
	.data.w	.Ldw_str_begin+16191
	.data.b	157,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3745
	.section	.debug_loc		;off: 3745
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24722
	.data.b	8
	.section	.debug_str		;off: 16195
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 24723
	.data.w	.Ldw_str_begin+16195
	.data.b	159,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16202
	.data.b	65,100,99,95,68,105,115,97,98,108,101,71,114,111,117,112,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 24740
	.data.w	.Ldw_str_begin+16202
	.data.b	238,39
	.data.b	29
	.data.b	1
	.data.w	Adc_DisableGroupNotification
	.data.w	__ghs_eofn_Adc_DisableGroupNotification
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

	.section	.debug_frame		;off: 864
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_DisableGroupNotification
	.data.w	__ghs_eofn_Adc_DisableGroupNotification-Adc_DisableGroupNotification
	.data.b	1
	.data.w	.LDW201
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4736
	.data.b	0,5,2
	.data.w	Adc_DisableGroupNotification
	.data.b	6
	.data.b	3
	.data.b	241,39
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin46
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin47
	.data.b	13
	.data.b	157
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	20
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 24771
	.data.b	22
	.section	.debug_str		;off: 16231
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 24772
	.data.w	.Ldw_str_begin+16231
	.data.b	240,39
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3764
	.section	.debug_loc		;off: 3764
	.data.w	.LDW001
	.data.w	.LDW201
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24789
	.data.b	34
	.data.w	.LDW101
	.data.w	.LDW201

	.data.b	7
	.section	.debug_str		;off: 16237
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 24799
	.data.w	.Ldw_str_begin+16237
	.data.b	243,39
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3783
	.section	.debug_loc		;off: 3783
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24817
	.data.b	7
	.section	.debug_str		;off: 16245
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 24818
	.data.w	.Ldw_str_begin+16245
	.data.b	244,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3802
	.section	.debug_loc		;off: 3802
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24836
	.data.b	7
	.section	.debug_str		;off: 16253
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 24837
	.data.w	.Ldw_str_begin+16253
	.data.b	245,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3821
	.section	.debug_loc		;off: 3821
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24855
	.data.b	7
	.section	.debug_str		;off: 16265
	.data.b	69,114,114,0
	.section	.debug_info		;off: 24856
	.data.w	.Ldw_str_begin+16265
	.data.b	247,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3840
	.section	.debug_loc		;off: 3840
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24874
	.data.b	8
	.section	.debug_str		;off: 16269
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 24875
	.data.w	.Ldw_str_begin+16269
	.data.b	249,39
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 16276
	.data.b	65,100,99,95,71,101,116,71,114,111,117,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 24892
	.data.w	.Ldw_str_begin+16276
	.data.b	200,40
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.w	Adc_GetGroupStatus
	.data.w	__ghs_eofn_Adc_GetGroupStatus
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

	.section	.debug_frame		;off: 888
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_GetGroupStatus
	.data.w	__ghs_eofn_Adc_GetGroupStatus-Adc_GetGroupStatus
	.data.b	1
	.data.w	.LDW501
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4817
	.data.b	0,5,2
	.data.w	Adc_GetGroupStatus
	.data.b	6
	.data.b	3
	.data.b	203,40
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin48
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin49
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	13
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	125
	.data.b	27
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
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
	.section	.debug_info		;off: 24927
	.data.b	22
	.section	.debug_str		;off: 16295
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 24928
	.data.w	.Ldw_str_begin+16295
	.data.b	202,40
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3859
	.section	.debug_loc		;off: 3859
	.data.w	.LDW301
	.data.w	.LDW501
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 24945
	.data.b	34
	.data.w	.LDW401
	.data.w	.LDW501

	.data.b	8
	.section	.debug_str		;off: 16301
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 24955
	.data.w	.Ldw_str_begin+16301
	.data.b	206,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16315
	.data.b	80,111,108,108,105,110,103,70,108,103,0
	.section	.debug_info		;off: 24970
	.data.w	.Ldw_str_begin+16315
	.data.b	207,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16326
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 24985
	.data.w	.Ldw_str_begin+16326
	.data.b	208,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16340
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 25000
	.data.w	.Ldw_str_begin+16340
	.data.b	209,40
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3878
	.section	.debug_loc		;off: 3878
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25018
	.data.b	8
	.section	.debug_str		;off: 16356
	.data.b	82,101,113,83,114,99,0
	.section	.debug_info		;off: 25019
	.data.w	.Ldw_str_begin+16356
	.data.b	210,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+14629
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16363
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 25034
	.data.w	.Ldw_str_begin+16363
	.data.b	212,40
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3897
	.section	.debug_loc		;off: 3897
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25052
	.data.b	7
	.section	.debug_str		;off: 16371
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 25053
	.data.w	.Ldw_str_begin+16371
	.data.b	213,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3916
	.section	.debug_loc		;off: 3916
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25071
	.data.b	7
	.section	.debug_str		;off: 16379
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 25072
	.data.w	.Ldw_str_begin+16379
	.data.b	214,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3935
	.section	.debug_loc		;off: 3935
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25090
	.data.b	7
	.section	.debug_str		;off: 16389
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 25091
	.data.w	.Ldw_str_begin+16389
	.data.b	215,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3954
	.section	.debug_loc		;off: 3954
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25109
	.data.b	8
	.section	.debug_str		;off: 16401
	.data.b	69,110,100,83,116,97,116,117,115,0
	.section	.debug_info		;off: 25110
	.data.w	.Ldw_str_begin+16401
	.data.b	216,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16411
	.data.b	71,114,112,82,101,115,0
	.section	.debug_info		;off: 25125
	.data.w	.Ldw_str_begin+16411
	.data.b	217,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16418
	.data.b	69,114,114,0
	.section	.debug_info		;off: 25140
	.data.w	.Ldw_str_begin+16418
	.data.b	219,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3973
	.section	.debug_loc		;off: 3973
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25158
	.data.b	8
	.section	.debug_str		;off: 16422
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 25159
	.data.w	.Ldw_str_begin+16422
	.data.b	221,40
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 16429
	.data.b	65,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 25176
	.data.w	.Ldw_str_begin+16429
	.data.b	249,41
	.data.b	48
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.w	Adc_GetStreamLastPointer
	.data.w	__ghs_eofn_Adc_GetStreamLastPointer
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

	.section	.debug_frame		;off: 912
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_GetStreamLastPointer
	.data.w	__ghs_eofn_Adc_GetStreamLastPointer-Adc_GetStreamLastPointer
	.data.b	1
	.data.w	.LDW801
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4989
	.data.b	0,5,2
	.data.w	Adc_GetStreamLastPointer
	.data.b	6
	.data.b	3
	.data.b	255,41
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin50
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin51
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	124
	.data.b	12
	.data.b	91
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	29
	.data.b	76
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	93
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	29
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	13
	.data.b	44
	.data.b	77
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	91
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
	.section	.debug_info		;off: 25211
	.data.b	22
	.section	.debug_str		;off: 16454
	.data.b	71,114,111,117,112,0
	.section	.debug_info		;off: 25212
	.data.w	.Ldw_str_begin+16454
	.data.b	251,41
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.w	.Ldw_loc_begin+3992
	.section	.debug_loc		;off: 3992
	.data.w	.LDW601
	.data.w	.LDW801
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25229
	.data.b	22
	.section	.debug_str		;off: 16460
	.data.b	80,116,114,84,111,83,97,109,112,108,101,80,116,114,0
	.section	.debug_info		;off: 25230
	.data.w	.Ldw_str_begin+16460
	.data.b	254,41
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+862
	.data.b	0
	.data.w	.Ldw_loc_begin+4011
	.section	.debug_loc		;off: 4011
	.data.w	.LDW601
	.data.w	.LDW701
	.data.b	1,0
	.data.b	81
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25247
	.data.b	34
	.data.w	.LDW701
	.data.w	.LDW801

	.data.b	7
	.section	.debug_str		;off: 16475
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 25257
	.data.w	.Ldw_str_begin+16475
	.data.b	129,42
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4041
	.section	.debug_loc		;off: 4041
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25275
	.data.b	7
	.section	.debug_str		;off: 16483
	.data.b	71,114,112,80,116,114,0
	.section	.debug_info		;off: 25276
	.data.w	.Ldw_str_begin+16483
	.data.b	130,42
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+306
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4060
	.section	.debug_loc		;off: 4060
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25294
	.data.b	7
	.section	.debug_str		;off: 16490
	.data.b	66,117,102,69,110,100,83,116,97,116,117,115,0
	.section	.debug_info		;off: 25295
	.data.w	.Ldw_str_begin+16490
	.data.b	131,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4079
	.section	.debug_loc		;off: 4079
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25313
	.data.b	7
	.section	.debug_str		;off: 16503
	.data.b	67,117,114,114,101,110,116,82,101,115,66,117,102,80,116,114,0
	.section	.debug_info		;off: 25314
	.data.w	.Ldw_str_begin+16503
	.data.b	132,42
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+311
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4098
	.section	.debug_loc		;off: 4098
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25332
	.data.b	7
	.section	.debug_str		;off: 16520
	.data.b	71,114,111,117,112,73,100,0
	.section	.debug_info		;off: 25333
	.data.w	.Ldw_str_begin+16520
	.data.b	133,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16369
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4117
	.section	.debug_loc		;off: 4117
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25351
	.data.b	7
	.section	.debug_str		;off: 16528
	.data.b	78,111,79,102,86,97,108,105,100,67,111,110,118,0
	.section	.debug_info		;off: 25352
	.data.w	.Ldw_str_begin+16528
	.data.b	134,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4136
	.section	.debug_loc		;off: 4136
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25370
	.data.b	7
	.section	.debug_str		;off: 16542
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 25371
	.data.w	.Ldw_str_begin+16542
	.data.b	135,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16417
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4155
	.section	.debug_loc		;off: 4155
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25389
	.data.b	8
	.section	.debug_str		;off: 16549
	.data.b	71,114,112,83,116,97,116,117,115,0
	.section	.debug_info		;off: 25390
	.data.w	.Ldw_str_begin+16549
	.data.b	136,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16559
	.data.b	71,114,112,82,101,115,0
	.section	.debug_info		;off: 25405
	.data.w	.Ldw_str_begin+16559
	.data.b	137,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16505
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4174
	.section	.debug_loc		;off: 4174
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25423
	.data.b	7
	.section	.debug_str		;off: 16566
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 25424
	.data.w	.Ldw_str_begin+16566
	.data.b	138,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4193
	.section	.debug_loc		;off: 4193
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25442
	.data.b	7
	.section	.debug_str		;off: 16578
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 25443
	.data.w	.Ldw_str_begin+16578
	.data.b	139,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4212
	.section	.debug_loc		;off: 4212
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25461
	.data.b	7
	.section	.debug_str		;off: 16585
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 25462
	.data.w	.Ldw_str_begin+16585
	.data.b	140,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4231
	.section	.debug_loc		;off: 4231
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25480
	.data.b	7
	.section	.debug_str		;off: 16599
	.data.b	69,114,114,0
	.section	.debug_info		;off: 25481
	.data.w	.Ldw_str_begin+16599
	.data.b	141,42
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4250
	.section	.debug_loc		;off: 4250
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25499
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16603
	.data.b	65,100,99,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 25502
	.data.w	.Ldw_str_begin+16603
	.data.b	171,43
	.data.b	29
	.data.b	1
	.data.w	Adc_GetVersionInfo
	.data.w	__ghs_eofn_Adc_GetVersionInfo
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

	.section	.debug_frame		;off: 936
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_GetVersionInfo
	.data.w	__ghs_eofn_Adc_GetVersionInfo-Adc_GetVersionInfo
	.data.b	1
	.data.w	.LDW111
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5137
	.data.b	0,5,2
	.data.w	Adc_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	179,43
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
	.section	.debug_info		;off: 25531
	.data.b	22
	.section	.debug_str		;off: 16622
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 25532
	.data.w	.Ldw_str_begin+16622
	.data.b	175,43
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+886
	.data.b	0
	.data.w	.Ldw_loc_begin+4269
	.section	.debug_loc		;off: 4269
	.data.w	.LDW011
	.data.w	.LDW111
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25549
	.data.b	34
	.data.w	.LDW011
	.data.w	.LDW111

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16637
	.data.b	65,100,99,95,81,117,101,117,101,82,101,113,117,101,115,116,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 25561
	.data.w	.Ldw_str_begin+16637
	.data.b	164,45
	.data.b	29
	.data.b	1
	.data.w	Adc_QueueRequest_ISRHandler
	.data.w	__ghs_eofn_Adc_QueueRequest_ISRHandler
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

	.section	.debug_frame		;off: 960
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Adc_QueueRequest_ISRHandler
	.data.w	__ghs_eofn_Adc_QueueRequest_ISRHandler-Adc_QueueRequest_ISRHandler
	.data.b	1
	.data.w	.LDW411
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5169
	.data.b	0,5,2
	.data.w	Adc_QueueRequest_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	168,45
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin52
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin53
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	2
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	27
	.data.b	11
	.data.b	75
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
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 25592
	.data.b	22
	.section	.debug_str		;off: 16665
	.data.b	80,104,121,72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 25593
	.data.w	.Ldw_str_begin+16665
	.data.b	166,45
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+16429
	.data.b	0
	.data.w	.Ldw_loc_begin+4288
	.section	.debug_loc		;off: 4288
	.data.w	.LDW211
	.data.w	.LDW311
	.data.b	1,0
	.data.b	80
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25610
	.data.b	22
	.section	.debug_str		;off: 16677
	.data.b	82,101,113,83,114,99,0
	.section	.debug_info		;off: 25611
	.data.w	.Ldw_str_begin+16677
	.data.b	167,45
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+14629
	.data.b	0
	.data.w	.Ldw_loc_begin+4318
	.section	.debug_loc		;off: 4318
	.data.w	.LDW211
	.data.w	.LDW311
	.data.b	1,0
	.data.b	81
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25628
	.data.b	34
	.data.w	.LDW311
	.data.w	.LDW411

	.data.b	8
	.section	.debug_str		;off: 16684
	.data.b	72,119,85,110,105,116,67,111,114,101,73,100,120,0
	.section	.debug_info		;off: 25638
	.data.w	.Ldw_str_begin+16684
	.data.b	170,45
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2166
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16698
	.data.b	79,112,101,114,97,116,105,111,110,82,115,108,116,0
	.section	.debug_info		;off: 25653
	.data.w	.Ldw_str_begin+16698
	.data.b	171,45
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2154
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16712
	.data.b	68,97,116,97,80,116,114,0
	.section	.debug_info		;off: 25668
	.data.w	.Ldw_str_begin+16712
	.data.b	172,45
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+296
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16720
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 25683
	.data.w	.Ldw_str_begin+16720
	.data.b	173,45
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2393
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16727
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 25698
	.data.w	.Ldw_str_begin+16727
	.data.b	174,45
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+265
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16743
	.data.b	69,114,114,0
	.section	.debug_info		;off: 25713
	.data.w	.Ldw_str_begin+16743
	.data.b	176,45
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4348
	.section	.debug_loc		;off: 4348
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 25731
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
	.data.b	72
	.data.b	2
	.data.b	3
	.data.b	37
	.data.b	3
	.data.b	1
	.data.b	34
	.data.b	65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	35
	.data.b	65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	36
	.data.b	65,68,67,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	38
	.data.b	65,68,67,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	39
	.data.b	65,68,67,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	40
	.data.b	65,68,67,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	41
	.data.b	65,68,67,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	42
	.data.b	65,68,67,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,49,50,51,85,41,0
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
	.data.b	93
	.data.b	65,68,67,95,82,69,83,85,76,84,95,72,65,78,68,76,73,78,71,95,80,79,76,76,73,78,71,95,77,79,68,69,32,40,49,85,41,0
	.data.b	1
	.data.b	94
	.data.b	65,68,67,95,82,69,83,85,76,84,95,72,65,78,68,76,73,78,71,95,68,77,65,95,77,79,68,69,32,40,50,85,41,0
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
	.data.b	105
	.data.b	65,68,67,95,83,84,65,82,84,85,80,95,67,65,76,73,66,82,65,84,73,79,78,32,40,83,84,68,95,79,78,41,0
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
	.data.b	180,1
	.data.b	65,68,67,95,80,82,73,79,82,73,84,89,95,72,87,32,40,49,85,41,0
	.data.b	1
	.data.b	182,1
	.data.b	65,68,67,95,80,82,73,79,82,73,84,89,95,72,87,95,83,87,32,40,50,85,41,0
	.data.b	1
	.data.b	194,1
	.data.b	65,68,67,95,69,78,65,66,76,69,95,81,85,69,85,73,78,71,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	197,1
	.data.b	65,68,67,95,77,65,88,95,75,69,82,78,69,76,83,32,40,49,50,85,41,0
	.data.b	1
	.data.b	200,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,48,32,40,48,41,0
	.data.b	1
	.data.b	201,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,49,32,40,49,41,0
	.data.b	1
	.data.b	202,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,50,32,40,50,41,0
	.data.b	1
	.data.b	203,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,51,32,40,51,41,0
	.data.b	1
	.data.b	204,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,52,32,40,52,41,0
	.data.b	1
	.data.b	205,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,53,32,40,53,41,0
	.data.b	1
	.data.b	206,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,54,32,40,54,41,0
	.data.b	1
	.data.b	207,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,55,32,40,55,41,0
	.data.b	1
	.data.b	208,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,56,32,40,56,41,0
	.data.b	1
	.data.b	209,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,57,32,40,57,41,0
	.data.b	1
	.data.b	210,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,49,48,32,40,49,48,41,0
	.data.b	1
	.data.b	211,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,65,68,67,49,49,32,40,49,49,41,0
	.data.b	1
	.data.b	218,1
	.data.b	65,68,67,95,84,79,84,65,76,95,71,82,79,85,80,83,95,67,79,82,69,48,32,40,49,49,85,41,0
	.data.b	1
	.data.b	221,1
	.data.b	65,68,67,95,84,79,84,65,76,95,71,82,79,85,80,83,95,67,79,82,69,49,32,40,53,85,41,0
	.data.b	1
	.data.b	242,1
	.data.b	65,68,67,95,82,69,81,83,82,67,95,67,79,85,78,84,32,40,51,85,41,0
	.data.b	1
	.data.b	245,1
	.data.b	65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,48,32,40,51,85,41,0
	.data.b	1
	.data.b	247,1
	.data.b	65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,49,32,40,49,85,41,0
	.data.b	1
	.data.b	249,1
	.data.b	65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	251,1
	.data.b	65,68,67,95,77,65,88,95,72,87,85,78,73,84,95,84,79,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	5
	.data.b	3
	.data.b	47
	.data.b	6
	.data.b	3
	.data.b	39
	.data.b	7
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	8
	.data.b	3
	.data.b	25
	.data.b	9
	.data.b	3
	.data.b	25
	.data.b	10
	.data.b	3
	.data.b	31
	.data.b	11
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	12
	.data.b	3
	.data.b	13
	.data.b	13
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
	.data.b	203,2
	.data.b	67,79,78,83,84,80,50,67,79,78,83,84,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,99,111,110,115,116,32,112,116,114,116,121,112,101,32,42,99,111,110,115,116
	.data.b	0
	.data.b	1
	.data.b	157,3
	.data.b	80,50,80,50,86,65,82,40,112,116,114,116,121,112,101,44,109,101,109,99,108,97,115,115,44,112,116,114,99,108,97,115,115,41,32,112,116,114,116,121,112,101,32,42,42,0
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	14
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
	.data.b	15
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	16
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
	.data.b	16
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	17
	.data.b	3
	.data.b	28
	.data.b	18
	.data.b	3
	.data.b	22
	.data.b	19
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	20
	.data.b	3
	.data.b	56
	.data.b	21
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
	.data.b	205,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,48,32,40,48,120,66,48,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	206,1
	.data.b	83,65,82,65,68,67,48,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,48,41,0
	.data.b	1
	.data.b	208,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,32,40,48,120,66,48,48,48,48,52,48,48,85,41,0
	.data.b	1
	.data.b	209,1
	.data.b	83,65,82,65,68,67,49,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,41,0
	.data.b	1
	.data.b	211,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,50,32,40,48,120,66,48,48,48,48,56,48,48,85,41,0
	.data.b	1
	.data.b	212,1
	.data.b	83,65,82,65,68,67,50,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,50,41,0
	.data.b	1
	.data.b	214,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,51,32,40,48,120,66,48,48,48,48,67,48,48,85,41,0
	.data.b	1
	.data.b	215,1
	.data.b	83,65,82,65,68,67,51,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,51,41,0
	.data.b	1
	.data.b	217,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,52,32,40,48,120,66,48,51,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	218,1
	.data.b	83,65,82,65,68,67,52,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,52,41,0
	.data.b	1
	.data.b	220,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,53,32,40,48,120,66,48,51,48,48,52,48,48,85,41,0
	.data.b	1
	.data.b	221,1
	.data.b	83,65,82,65,68,67,53,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,53,41,0
	.data.b	1
	.data.b	223,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,54,32,40,48,120,66,48,51,48,48,56,48,48,85,41,0
	.data.b	1
	.data.b	224,1
	.data.b	83,65,82,65,68,67,54,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,54,41,0
	.data.b	1
	.data.b	226,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,55,32,40,48,120,66,48,51,48,48,67,48,48,85,41,0
	.data.b	1
	.data.b	227,1
	.data.b	83,65,82,65,68,67,55,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,55,41,0
	.data.b	1
	.data.b	229,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,56,32,40,48,120,66,48,48,49,48,48,48,48,85,41,0
	.data.b	1
	.data.b	230,1
	.data.b	83,65,82,65,68,67,56,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,56,41,0
	.data.b	1
	.data.b	232,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,57,32,40,48,120,66,48,48,49,48,52,48,48,85,41,0
	.data.b	1
	.data.b	233,1
	.data.b	83,65,82,65,68,67,57,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,57,41,0
	.data.b	1
	.data.b	235,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,48,32,40,48,120,66,48,48,49,48,56,48,48,85,41,0
	.data.b	1
	.data.b	236,1
	.data.b	83,65,82,65,68,67,49,48,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,48,41,0
	.data.b	1
	.data.b	239,1
	.data.b	83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,49,32,40,48,120,66,48,48,49,48,67,48,48,85,41,0
	.data.b	1
	.data.b	241,1
	.data.b	83,65,82,65,68,67,49,49,32,40,40,83,65,82,65,68,67,95,77,79,68,85,76,69,32,42,41,83,65,82,65,68,67,95,66,65,83,69,95,65,68,68,82,69,83,83,49,49,41,0
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
	.data.b	22
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
	.data.b	22
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	23
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	24
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
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	25
	.data.b	3
	.data.b	34
	.data.b	26
	.data.b	3
	.data.b	31
	.data.b	27
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
	.data.b	28
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
	.data.b	28
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	29
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	28
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
	.data.b	28
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	30
	.data.b	3
	.data.b	38
	.data.b	31
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	32
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
	.data.b	32
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	110
	.data.b	77,99,97,108,95,71,101,116,67,111,114,101,73,100,40,41,32,77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,40,41,0
	.data.b	1
	.data.b	176,1
	.data.b	77,67,65,76,95,85,78,85,83,69,68,95,86,65,82,40,86,97,114,105,97,98,108,101,78,97,109,101,41,32,40,40,118,111,105,100,41,40,86,97,114,105,97,98,108,101,78,97,109,101,41,41,0
	.data.b	1
	.data.b	219,1
	.data.b	77,67,65,76,95,83,69,84,66,73,84,83,40,79,112,116,68,97,116,97,80,116,114,44,66,105,116,80,111,115,44,66,105,116,76,101,110,44,68,97,116,97,41,32,100,111,32,123,32,42,40,79,112,116,68,97,116,97,80,116
	.data.b	114,41,32,38,61,32,40,126,40,40,40,49,85,76,32,60,60,32,40,66,105,116,76,101,110,41,41,32,45,32,49,85,76,41,32,60,60,32,40,66,105,116,80,111,115,41,41,41,59,32,42,40,79,112,116,68,97,116,97,80
	.data.b	116,114,41,32,124,61,32,40,40,40,68,97,116,97,41,32,38,32,40,40,49,85,76,32,60,60,32,40,66,105,116,76,101,110,41,41,32,45,32,49,85,76,41,41,32,60,60,32,40,66,105,116,80,111,115,41,41,59,32,125
	.data.b	32,119,104,105,108,101,32,40,48,41,0
	.data.b	1
	.data.b	228,1
	.data.b	77,67,65,76,95,67,76,82,66,73,84,83,40,79,112,116,68,97,116,97,80,116,114,44,66,105,116,80,111,115,44,66,105,116,76,101,110,41,32,100,111,32,123,32,42,40,79,112,116,68,97,116,97,80,116,114,41,32,38,61
	.data.b	32,40,126,40,40,40,49,85,76,32,60,60,32,40,66,105,116,76,101,110,41,41,32,45,32,49,85,76,41,32,60,60,32,40,66,105,116,80,111,115,41,41,41,59,32,125,32,119,104,105,108,101,32,40,48,41,0
	.data.b	1
	.data.b	237,1
	.data.b	77,67,65,76,95,71,69,84,66,73,84,83,40,68,97,116,97,86,97,108,117,101,44,66,105,116,80,111,115,44,66,105,116,76,101,110,41,32,40,40,117,105,110,116,51,50,41,40,40,40,68,97,116,97,86,97,108,117,101,41
	.data.b	32,62,62,32,40,66,105,116,80,111,115,41,41,32,38,32,40,40,49,85,32,60,60,32,40,66,105,116,76,101,110,41,41,32,45,32,49,85,41,41,41,0
	.data.b	1
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	33
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
	.data.b	33
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	48
	.data.b	34
	.data.b	3
	.data.b	35
	.data.b	35
	.data.b	3
	.data.b	15
	.data.b	36
	.data.b	4
	.data.b	1
	.data.b	175,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	176,1
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	81
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,79,80,84,73,79,78,95,82,69,70,73,76,76,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,53,41,0
	.data.b	1
	.data.b	84
	.data.b	83,65,82,65,68,67,95,81,85,69,85,69,79,80,84,73,79,78,95,69,88,84,69,82,78,65,76,84,82,73,71,71,69,82,32,40,40,117,105,110,116,51,50,41,49,85,32,60,60,32,55,41,0
	.data.b	1
	.data.b	228,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	229,2
	.data.b	37
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
	.data.b	37
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
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	65,68,67,95,69,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,65,41,0
	.data.b	1
	.data.b	49
	.data.b	65,68,67,95,69,95,66,85,83,89,32,40,40,117,105,110,116,56,41,48,120,48,66,41,0
	.data.b	1
	.data.b	51
	.data.b	65,68,67,95,69,95,73,68,76,69,32,40,40,117,105,110,116,56,41,48,120,48,67,41,0
	.data.b	1
	.data.b	53
	.data.b	65,68,67,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,48,120,48,68,41,0
	.data.b	1
	.data.b	55
	.data.b	65,68,67,95,69,95,80,65,82,65,77,95,67,79,78,70,73,71,32,40,40,117,105,110,116,56,41,48,120,48,69,41,0
	.data.b	1
	.data.b	57
	.data.b	65,68,67,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,49,52,41,0
	.data.b	1
	.data.b	59
	.data.b	65,68,67,95,69,95,80,65,82,65,77,95,71,82,79,85,80,32,40,40,117,105,110,116,56,41,48,120,49,53,41,0
	.data.b	1
	.data.b	61
	.data.b	65,68,67,95,69,95,87,82,79,78,71,95,67,79,78,86,95,77,79,68,69,32,40,40,117,105,110,116,56,41,48,120,49,54,41,0
	.data.b	1
	.data.b	63
	.data.b	65,68,67,95,69,95,87,82,79,78,71,95,84,82,73,71,71,95,83,82,67,32,40,40,117,105,110,116,56,41,48,120,49,55,41,0
	.data.b	1
	.data.b	66
	.data.b	65,68,67,95,69,95,78,79,84,73,70,95,67,65,80,65,66,73,76,73,84,89,32,40,40,117,105,110,116,56,41,48,120,49,56,41,0
	.data.b	1
	.data.b	68
	.data.b	65,68,67,95,69,95,66,85,70,70,69,82,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,49,57,41,0
	.data.b	1
	.data.b	85
	.data.b	65,68,67,95,69,95,68,77,65,95,67,72,65,78,78,69,76,95,69,78,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,50,48,41,0
	.data.b	1
	.data.b	87
	.data.b	65,68,67,95,69,95,77,65,78,85,65,76,95,82,69,83,82,69,71,95,69,78,65,66,76,69,68,32,40,40,117,105,110,116,56,41,48,120,50,49,41,0
	.data.b	1
	.data.b	90
	.data.b	65,68,67,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,40,117,105,110,116,56,41,48,120,69,48,41,0
	.data.b	1
	.data.b	92
	.data.b	65,68,67,95,69,95,67,79,82,69,95,72,87,85,78,73,84,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,69,49,41,0
	.data.b	1
	.data.b	95
	.data.b	65,68,67,95,69,95,82,69,71,95,67,72,69,67,75,95,70,65,73,76,32,40,40,117,105,110,116,56,41,48,120,70,49,41,0
	.data.b	1
	.data.b	100
	.data.b	65,68,67,95,83,73,68,95,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,48,41,0
	.data.b	1
	.data.b	104
	.data.b	65,68,67,95,83,73,68,95,68,69,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,49,41,0
	.data.b	1
	.data.b	108
	.data.b	65,68,67,95,83,73,68,95,83,84,65,82,84,95,71,82,79,85,80,95,67,79,78,86,69,82,83,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,50,41,0
	.data.b	1
	.data.b	110
	.data.b	65,68,67,95,83,73,68,95,83,84,79,80,95,71,82,79,85,80,95,67,79,78,86,69,82,83,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,51,41,0
	.data.b	1
	.data.b	112
	.data.b	65,68,67,95,83,73,68,95,82,69,65,68,95,71,82,79,85,80,32,40,40,117,105,110,116,56,41,48,120,48,52,41,0
	.data.b	1
	.data.b	114
	.data.b	65,68,67,95,83,73,68,95,69,78,65,66,76,69,95,72,65,82,68,87,65,82,69,95,84,82,73,71,71,69,82,32,40,40,117,105,110,116,56,41,48,120,48,53,41,0
	.data.b	1
	.data.b	116
	.data.b	65,68,67,95,83,73,68,95,68,73,83,65,66,76,69,95,72,65,82,68,87,65,82,69,95,84,82,73,71,71,69,82,32,40,40,117,105,110,116,56,41,48,120,48,54,41,0
	.data.b	1
	.data.b	118
	.data.b	65,68,67,95,83,73,68,95,69,78,65,66,76,69,95,71,82,79,85,80,95,78,79,84,73,70,73,67,65,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,55,41,0
	.data.b	1
	.data.b	120
	.data.b	65,68,67,95,83,73,68,95,68,73,83,65,66,76,69,95,71,82,79,85,80,95,78,79,84,73,70,73,67,65,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,56,41,0
	.data.b	1
	.data.b	122
	.data.b	65,68,67,95,83,73,68,95,71,69,84,95,71,82,79,85,80,95,83,84,65,84,85,83,32,40,40,117,105,110,116,56,41,48,120,48,57,41,0
	.data.b	1
	.data.b	124
	.data.b	65,68,67,95,83,73,68,95,71,69,84,95,86,69,82,83,73,79,78,95,73,78,70,79,32,40,40,117,105,110,116,56,41,48,120,48,65,41,0
	.data.b	1
	.data.b	126
	.data.b	65,68,67,95,83,73,68,95,71,69,84,95,83,84,82,69,65,77,95,76,65,83,84,95,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,48,66,41,0
	.data.b	1
	.data.b	128,1
	.data.b	65,68,67,95,83,73,68,95,83,69,84,85,80,95,82,69,83,85,76,84,95,66,85,70,70,69,82,32,40,40,117,105,110,116,56,41,48,120,48,67,41,0
	.data.b	1
	.data.b	142,1
	.data.b	65,68,67,95,83,73,68,95,82,69,81,95,81,85,69,85,69,95,73,83,82,32,40,40,117,105,110,116,56,41,48,120,69,48,41,0
	.data.b	1
	.data.b	161,1
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	162,1
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	73
	.data.b	38
	.data.b	1
	.data.b	27
	.data.b	65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	28
	.data.b	65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	29
	.data.b	65,68,67,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	31
	.data.b	65,68,67,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	32
	.data.b	65,68,67,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	33
	.data.b	65,68,67,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	35
	.data.b	65,68,67,95,86,69,78,68,79,82,95,73,68,32,40,48,120,65,70,85,41,0
	.data.b	1
	.data.b	36
	.data.b	65,68,67,95,77,79,68,85,76,69,95,73,68,32,40,49,50,51,85,41,0
	.data.b	1
	.data.b	39
	.data.b	65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,32,40,40,117,105,110,116,56,41,48,41,0
	.data.b	4
	.data.b	3
	.data.b	74
	.data.b	39
	.data.b	4
	.data.b	3
	.data.b	77
	.data.b	40
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
	.data.b	128,1
	.data.b	65,68,67,95,85,78,73,78,73,84,73,65,76,73,90,69,32,40,40,117,105,110,116,56,41,48,41,0
	.data.b	1
	.data.b	130,1
	.data.b	65,68,67,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,49,41,0
	.data.b	1
	.data.b	134,1
	.data.b	65,68,67,95,71,82,80,95,82,69,81,95,83,82,67,95,70,82,69,69,32,40,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,48,120,70,70,70,70,41,0
	.data.b	1
	.data.b	137,1
	.data.b	65,68,67,95,73,78,86,65,76,73,68,95,80,82,73,79,82,73,84,89,32,40,40,65,100,99,95,71,114,111,117,112,80,114,105,111,114,105,116,121,84,121,112,101,41,48,120,70,70,41,0
	.data.b	1
	.data.b	140,1
	.data.b	65,68,67,95,73,83,82,95,82,69,81,95,83,69,86,32,40,40,117,105,110,116,56,41,48,120,48,48,41,0
	.data.b	1
	.data.b	142,1
	.data.b	65,68,67,95,78,79,95,83,69,82,86,73,67,69,32,40,40,117,105,110,116,56,41,48,120,48,49,41,0
	.data.b	1
	.data.b	155,1
	.data.b	65,68,67,95,75,69,82,78,69,76,95,78,85,77,95,83,84,65,82,84,95,66,73,84,32,40,53,85,41,0
	.data.b	1
	.data.b	157,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,71,79,85,80,95,77,65,83,75,32,40,48,120,48,70,85,41,0
	.data.b	1
	.data.b	159,1
	.data.b	65,68,67,95,75,69,82,78,69,76,95,71,82,79,85,80,95,73,68,95,77,65,83,75,32,40,48,120,49,70,85,41,0
	.data.b	1
	.data.b	162,1
	.data.b	65,68,67,95,72,87,85,78,73,84,95,69,78,65,66,76,69,95,84,73,77,69,79,85,84,32,40,48,120,51,70,85,41,0
	.data.b	1
	.data.b	167,1
	.data.b	65,68,67,95,71,69,84,95,71,82,79,85,80,73,68,40,71,114,111,117,112,41,32,40,40,40,71,114,111,117,112,41,32,38,32,40,65,100,99,95,71,114,111,117,112,84,121,112,101,41,65,68,67,95,75,69,82,78,69,76
	.data.b	95,71,82,79,85,80,95,73,68,95,77,65,83,75,41,41,0
	.data.b	1
	.data.b	172,1
	.data.b	65,68,67,95,71,69,84,95,72,87,85,78,73,84,73,68,40,71,114,111,117,112,41,32,40,40,40,71,114,111,117,112,41,32,62,62,32,65,68,67,95,75,69,82,78,69,76,95,78,85,77,95,83,84,65,82,84,95,66,73
	.data.b	84,41,32,38,32,65,68,67,95,72,87,85,78,73,84,95,71,79,85,80,95,77,65,83,75,41,0
	.data.b	1
	.data.b	176,1
	.data.b	65,68,67,95,78,79,95,82,69,83,85,76,84,95,65,67,67,85,77,85,32,40,48,85,41,0
	.data.b	1
	.data.b	181,1
	.data.b	65,68,67,95,71,69,84,95,82,69,83,66,85,70,69,78,68,83,84,65,84,85,83,40,69,110,100,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,71,69,84,66,73,84,83,40,40,69,110,100,83,116
	.data.b	97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,41,0
	.data.b	1
	.data.b	187,1
	.data.b	65,68,67,95,83,69,84,95,82,69,83,66,85,70,69,78,68,83,84,65,84,85,83,40,69,110,100,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,83,69,84,66,73,84,83,40,38,40,69,110,100,83
	.data.b	116,97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,41,0
	.data.b	1
	.data.b	193,1
	.data.b	65,68,67,95,67,76,82,95,82,69,83,66,85,70,69,78,68,83,84,65,84,85,83,40,69,110,100,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,67,76,82,66,73,84,83,40,38,40,69,110,100,83
	.data.b	116,97,116,117,115,41,44,32,40,71,114,111,117,112,41,44,32,40,49,85,41,41,0
	.data.b	1
	.data.b	199,1
	.data.b	65,68,67,95,71,69,84,95,71,82,79,85,80,83,84,65,84,85,83,40,71,114,111,117,112,83,116,97,116,117,115,44,71,114,111,117,112,41,32,40,65,100,99,95,83,116,97,116,117,115,84,121,112,101,41,77,67,65,76,95
	.data.b	71,69,84,66,73,84,83,40,40,71,114,111,117,112,83,116,97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,41,0
	.data.b	1
	.data.b	205,1
	.data.b	65,68,67,95,83,69,84,95,71,82,79,85,80,83,84,65,84,85,83,40,71,114,111,117,112,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,83,69,84,66,73,84,83,40,38,40,71,114,111,117,112,83
	.data.b	116,97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,44,32,40,117,105,110,116,51,50,41,40,65,68,67,95,66,85,83,89,41,41,0
	.data.b	1
	.data.b	210,1
	.data.b	65,68,67,95,67,76,82,95,71,82,79,85,80,83,84,65,84,85,83,40,71,114,111,117,112,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,67,76,82,66,73,84,83,40,38,40,71,114,111,117,112,83
	.data.b	116,97,116,117,115,41,44,32,40,71,114,111,117,112,41,44,32,40,49,85,41,41,0
	.data.b	1
	.data.b	216,1
	.data.b	65,68,67,95,71,69,84,95,82,69,83,85,76,84,83,84,65,84,85,83,40,82,101,115,117,108,116,83,116,97,116,117,115,44,71,114,111,117,112,41,32,40,65,100,99,95,83,116,97,116,117,115,84,121,112,101,41,77,67,65
	.data.b	76,95,71,69,84,66,73,84,83,40,40,82,101,115,117,108,116,83,116,97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,41,0
	.data.b	1
	.data.b	221,1
	.data.b	65,68,67,95,83,69,84,95,82,69,83,85,76,84,83,84,65,84,85,83,40,82,101,115,117,108,116,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,83,69,84,66,73,84,83,40,38,40,82,101,115,117
	.data.b	108,116,83,116,97,116,117,115,41,44,32,40,117,105,110,116,51,50,41,40,71,114,111,117,112,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,44,32,40,117,105,110,116,51,50,41,40,49,85,41,41,0
	.data.b	1
	.data.b	226,1
	.data.b	65,68,67,95,67,76,82,95,82,69,83,85,76,84,83,84,65,84,85,83,40,82,101,115,117,108,116,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,67,76,82,66,73,84,83,40,38,40,82,101,115,117
	.data.b	108,116,83,116,97,116,117,115,41,44,32,40,71,114,111,117,112,41,44,32,40,49,85,41,41,0
	.data.b	1
	.data.b	232,1
	.data.b	65,68,67,95,68,73,83,65,66,76,69,95,78,79,84,73,70,40,78,111,116,105,102,83,116,97,116,117,115,44,71,114,111,117,112,41,32,77,67,65,76,95,67,76,82,66,73,84,83,40,38,40,78,111,116,105,102,83,116,97
	.data.b	116,117,115,41,44,32,40,71,114,111,117,112,41,44,32,40,49,85,41,41,0
	.data.b	1
	.data.b	237,1
	.data.b	65,68,67,95,71,69,84,95,68,65,84,65,65,68,68,82,69,83,83,40,67,111,114,101,73,100,44,72,119,85,110,105,116,73,100,41,32,40,65,100,99,95,71,108,111,98,97,108,68,97,116,97,84,121,112,101,32,42,41,38
	.data.b	40,65,100,99,95,73,110,115,116,97,110,99,101,68,97,116,97,83,101,116,91,40,67,111,114,101,73,100,41,93,45,62,71,108,111,98,97,108,68,97,116,97,83,101,116,80,116,114,91,32,65,100,99,95,67,111,110,102,105,103
	.data.b	80,116,114,45,62,72,119,85,110,105,116,84,111,67,111,114,101,80,116,114,91,40,72,119,85,110,105,116,73,100,41,93,46,67,111,114,101,72,119,85,110,105,116,73,100,120,93,41,0
	.data.b	1
	.data.b	244,1
	.data.b	65,68,67,95,71,69,84,95,82,69,83,85,76,84,66,85,70,70,69,82,65,68,68,82,69,83,83,40,67,111,114,101,73,100,44,72,119,85,110,105,116,73,100,44,71,114,111,117,112,41,32,40,65,100,99,95,73,110,115,116
	.data.b	97,110,99,101,68,97,116,97,83,101,116,91,40,67,111,114,101,73,100,41,93,45,62,71,108,111,98,97,108,68,97,116,97,83,101,116,80,116,114,91,32,65,100,99,95,67,111,110,102,105,103,80,116,114,45,62,72,119,85,110
	.data.b	105,116,84,111,67,111,114,101,80,116,114,91,40,72,119,85,110,105,116,73,100,41,93,46,67,111,114,101,72,119,85,110,105,116,73,100,120,93,46,32,71,114,111,117,112,82,101,115,117,108,116,66,117,102,102,101,114,80,116,114
	.data.b	91,40,71,114,111,117,112,41,93,41,0
	.data.b	1
	.data.b	254,1
	.data.b	65,100,99,95,82,101,112,111,114,116,69,114,114,111,114,40,83,101,114,118,105,99,101,73,100,44,69,114,114,67,111,100,101,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,40,65,68,67
	.data.b	95,77,79,68,85,76,69,95,73,68,44,32,65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,44,32,83,101,114,118,105,99,101,73,100,44,32,69,114,114,67,111,100,101,41,0
	.data.b	1
	.data.b	131,2
	.data.b	65,100,99,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,40,83,101,114,118,105,99,101,73,100,44,69,114,114,67,111,100,101,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,82,117
	.data.b	110,116,105,109,101,69,114,114,111,114,40,65,68,67,95,77,79,68,85,76,69,95,73,68,44,32,65,68,67,95,73,78,83,84,65,78,67,69,95,73,68,44,32,83,101,114,118,105,99,101,73,100,44,32,69,114,114,67,111,100
	.data.b	101,41,0
	.data.b	1
	.data.b	139,2
	.data.b	65,68,67,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,65,100,99,95,32,35
	.data.b	35,32,69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	142,2
	.data.b	65,68,67,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,65,100,99,95,32,35,35,32
	.data.b	69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	150,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	151,2
	.data.b	37
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
	.data.b	172,2
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	174,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	177,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	179,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	217,29
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	220,29
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	196,2
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	198,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	206,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	208,2
	.data.b	37
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
	.data.b	229,2
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	231,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	233,2
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	235,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	140,38
	.data.b	73,78,83,73,68,69,95,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	143,38
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	251,2
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	253,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	234,3
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	236,3
	.data.b	37
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
	.data.b	242,3
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	244,3
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	254,3
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	128,4
	.data.b	37
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
	.data.b	181,5
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	183,5
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	194,5
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	196,5
	.data.b	37
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
	.data.b	175,7
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,7
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	182,7
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	184,7
	.data.b	37
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
	.data.b	163,29
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	165,29
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	171,29
	.data.b	65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	173,29
	.data.b	37
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
	.data.b	214,45
	.data.b	65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	216,45
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 478
	.data.b	0
