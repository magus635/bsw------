	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682572..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalMakeBlockMarker:
.LDW01:
.LDW11:
	strh	r1,[r0,2]
	movw	r2,0x5555
	mvn	r3,0
	strh	r2,[r0]
	sub	r1,r3,r1
	strh	r1,[r0,4]
	mov	r1,0
.L26:
	add	r3,r1,r0
	add	r1,r1,1
	mov	r12,0
	cmp	r1,8
	strb	r12,[r3,6]
	blo	.L26
	strh	r2,[r0,14]
.LDW21:
.L129:

	ret	
__ghs_eofn_Fee_LocalMakeBlockMarker:
	.endf	Fee_LocalMakeBlockMarker
	.endf	Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

;BlockMarkerPtr	r0	param
;PageCount	r1	param

	.section ".bss","awb"
.L93:
	.endo	.L93
	.section ".ghrettbl",""
	.align	4
.L130:	.data.w	.L129
	.endo	.L130
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGetUsrBlockIndex:
.LDW31:
.LDW41:
	ldr	r2,.L292
	ldr	r3,[r2]
	mov	r1,0
	ldr	r2,[r3,4]
	b	.L133
.L135:
	add	r1,r1,1
	add	r2,r2,12
	uxth	r1,r1
.L133:
	ldrh	r12,[r3]
	cmp	r1,r12
	bhs	.L138
	ldrh	r12,[r2,4]
	cmp	r12,r0
	bne	.L135
	b	.L137
.L138:
	movw	r1,0xffff
.L137:
	mov	r0,r1
.LDW51:
.L293:

	ret	
__ghs_eofn_Fee_LocalGetUsrBlockIndex:
	.endf	Fee_LocalGetUsrBlockIndex
	.endf	Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BlockPtr	r2	local
;Index	r1	local

;BlockNumber	r0	param

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Fee_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_ConfigPtr:	.space	4
	.endo	Fee_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_ConfigPtr
	.section ".ghrettbl",""
.L294:	.data.w	.L293
	.endo	.L294
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_UserJobInfo - Fee_ConfigPtr) +0 == 28
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalHandleUsrJobEnd:
.LDW61:
	ldr	r12,.L292
.LDW71:
	ldr	r2,[r12,8]
	mov	r1,0
	str	r1,[r12,84]
	cmp	r2,3
	str	r1,[r12,28]
	movge	r2,0
	strge	r2,[r12,8]
	ldr	r1,[r12,76]
	cmp	r1,2
	streq	r0,[r12,76]
	ldr	r1,[r12]
	cmp	r0,0
	ldreq	r0,[r1,8]
	ldrne	r0,[r1,12]
	cmp	r0,0
.L482:

	bxne	r0
.L295:
.LDW81:
.L484:

	ret	
__ghs_eofn_Fee_LocalHandleUsrJobEnd:
	.endf	Fee_LocalHandleUsrJobEnd
	.endf	Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;NotificationPtr	r0	local

;Error	r0	param

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Fee_State..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_State:	.space	24
	.endo	Fee_State..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_State
Fee_UserJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_UserJobInfo:	.space	60
	.endo	Fee_UserJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_UserJobInfo
	.section ".ghtailcalltbl",""
	.align	4
.L483:	.data.w	.L482
	.endo	.L483
	.section ".ghrettbl",""
.L485:	.data.w	.L484
	.endo	.L485
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalDecideMainJob:
.LDW91:
	ldr	r12,.L953
.LDW02:
	ldr	r2,[r12,4]
	add	r0,r12,84
	add	r1,r12,24
	subs	r2,r2,0
	beq	.L489
	cmp	r2,2
.L954:

	retne	
	ldr	r2,[r0]
	cmp	r2,1
	beq	.L515
	ldr	r0,[r0,24]
	cmp	r0,1
.L956:

	reteq	
	cmp	r2,3
	cmpne	r2,5
.L958:

	retne	
.L515:
	ldr	r2,[r1]
	cmp	r2,2
	bne	.L519
	ldrb	r0,[r1,13]
	cmp	r0,0
.L960:

	retne	
.L522:
	mov	r0,4
	b	.L605
.L489:
	ldr	r2,[r12,24]
	cmp	r2,1
	beq	.L525
	cmp	r2,2
	bne	.L496
	ldrb	r1,[r1,13]
	cmp	r1,0
	beq	.L522
	ldr	r2,[r0]
	cmp	r2,0
	moveq	r1,1
	streq	r1,[r0]
	beq	.L510
	cmp	r2,2
.L962:

	reteq	
	b	.L510
.L496:
	ldr	r2,[r12,84]
	cmp	r2,0
	cmpne	r2,2
.L964:

	reteq	
	ldrb	r0,[r12,2]
	cmp	r0,1
.L966:

	retne	
.L510:
	mov	r0,2
	b	.L605
.L519:
	cmp	r2,1
.L968:

	retne	
.L525:
	mov	r0,3
.L605:
	str	r0,[r12,4]
.LDW12:
.L970:

	ret	
__ghs_eofn_Fee_LocalDecideMainJob:
	.endf	Fee_LocalDecideMainJob
	.endf	Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Fee_GcJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_GcJobInfo:	.space	28
	.endo	Fee_GcJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_GcJobInfo
	.section ".ghrettbl",""
.L955:	.data.w	.L954
	.endo	.L955
.L957:	.data.w	.L956
	.endo	.L957
.L959:	.data.w	.L958
	.endo	.L959
.L961:	.data.w	.L960
	.endo	.L961
.L963:	.data.w	.L962
	.endo	.L963
.L965:	.data.w	.L964
	.endo	.L965
.L967:	.data.w	.L966
	.endo	.L967
.L969:	.data.w	.L968
	.endo	.L969
.L971:	.data.w	.L970
	.endo	.L971
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
	.assert 0x0 + (Fee_BlockInfos - Fee_State) +0 == 112
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalSetInitGc:
.LDW22:
	push	{r4-r10,lr}
	sub	sp,sp,8
	ldr	r5,.L953
.LDW32:
	mov	r9,sp
	ldr	r6,[r5,8]
	mov	r10,0
	mov	r12,1<<18
	ldrb	r8,[r6,7]
	ldrb	r7,[r6,23]
	stm	r9,{r10,r12}
	cmp	r8,1
	bne	.L981
	cmp	r7,1
	bne	.L982
	ldrb	r0,[r6,8]
	add	r1,r0,1
	mov	r0,3
.L1339:

	bl	__umoddiv32_hard
	mov	r4,r0
	ldrb	r1,[r6,24]
	mov	r0,3
.L1341:

	bl	__umoddiv32_hard
	cmp	r4,r0
	beq	.L985
.L982:
	mov	r0,r10
	b	.L1070
.L981:
	cmp	r7,1
	bne	.L980
.L985:
	mov	r0,r7
.L1070:
	strb	r0,[r5]
.L980:
	orr	r0,r7,r8
	cmp	r0,5
	beq	.L989
	cmp	r8,1
	cmpne	r7,1
	ldrbeq	r0,[r5]
	ldreq	r1,[r9,r0 lsl 2]
	eoreq	r0,r0,1
	streq	r1,[r5,92]
	mov	r2,3
	ldreq	r1,[r9,r0 lsl 2]
	streq	r2,[r5,84]
	addeq	r0,r6,r0 lsl 4
	streq	r1,[r5,88]
	strbeq	r10,[r0,4]
	beq	.L989
	cmp	r8,4
	cmpeq	r7,0
	strbne	r10,[r6,7]
	strbne	r10,[r6,23]
	mov	r0,1
	str	r0,[r5,4]
	moveq	r0,6
	streq	r0,[r5,84]
	moveq	r0,1
	strb	r0,[r5]
	strbne	r10,[r6,4]
	ldreq	r0,[r6]
	strne	r2,[r5,84]
	strne	r10,[r5,88]
	streq	r0,[r5,88]
.L989:
	ldrb	r0,[r5]
	add	r2,r5,112
	add	r1,r2,r0 lsl 5
	ldr	r0,[r6,r0 lsl 4]
	str	r1,[r5,12]
	str	r0,[r5,20]
.LDW42:
	add	sp,sp,8
.L1343:

	pop	{r4-r10,pc}
__ghs_eofn_Fee_LocalSetInitGc:
	.endf	Fee_LocalSetInitGc
	.endf	Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;Bank0State	r8	local
;Bank1State	r7	local
;BaseAddr	[sp]	local

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Fee_BlockInfos..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_BlockInfos:	.space	64
	.endo	Fee_BlockInfos..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_BlockInfos
	.section ".ghcalltbl",""
	.align	4
.L1340:	.data.w	.L1339
	.endo	.L1340
.L1342:	.data.w	.L1341
	.endo	.L1342
	.section ".ghrettbl",""
.L1344:	.data.w	.L1343
	.endo	.L1344
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_RWBuffer - Fee_State) +0 == 188
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalCheckEraseStatePage:
.LDW52:
	push	{r4-r10,lr}
	sub	sp,sp,16
	ldr	r10,.L953
.LDW62:
	cmp	r0,1<<18
	ldr	r2,[r10,8]
	mov	r4,0
	mov	r9,r0
	movhs	r8,1
	movlo	r8,0
	mov	r1,sp
	add	r7,r2,r8 lsl 4
	mov	r2,4
.L1970:

	bl	Fls_ReadWordsSync
	cmp	r0,0
	bne	.L1353
	ldrh	r0,[sp]
	movw	r1,0x45a7
	cmp	r0,r1
	ldrbeq	r0,[sp,15]
	cmpeq	r0,165
	bne	.L1369
	ldrb	r0,[sp,2]
	strb	r0,[r7,4]
	add	r0,r0,3
	lsr	r0,r0,2
	lsl	r6,r0,4
	add	r0,r6,r9
	mov	r1,16
	add	r0,r0,16
.L1972:

	bl	Fls_BlankCheckSync
	cmp	r0,1
	bne	.L1353
	ldrb	r1,[r7,4]
	mov	r4,2
	ldr	r5,.L1969
	cmp	r1,0
	beq	.L1355
	lsr	r2,r6,2
	add	r1,r10,188
	add	r0,r9,16
.L1974:

	bl	Fls_ReadWordsSync
	movs	r1,r0
	bne	.L1355
	b	.L1362
.L1361:
	add	r2,r10,r2 lsl 2
	ldrb	r2,[r2,191]
	mov	r3,1
	add	r1,r1,1<<24
	strb	r3,[r5,r2]
.L1362:
	ldrb	r3,[r7,4]
	lsr	r2,r1,24
	cmp	r2,r3
	blo	.L1361
.L1355:
	lsl	r6,r8,5
	lsl	r2,r6,16
	uxth	r6,r6
	mov	r3,r2
	b	.L1366
.L1365:
	ldrb	r12,[r5,r1]
	cmp	r12,0
	strbeq	r1,[r5,r3 lsr 16]
	addeq	r3,r3,1<<16
	add	r2,r2,1<<16
.L1366:
	lsr	r1,r2,16
	add	r12,r6,32
	cmp	r1,r12
	blo	.L1365
.L1353:
	cmp	r0,7
	moveq	r4,16
.L1369:
	mov	r0,r4
.LDW72:
	add	sp,sp,16
.L1976:

	pop	{r4-r10,pc}
__ghs_eofn_Fee_LocalCheckEraseStatePage:
	.endf	Fee_LocalCheckEraseStatePage
	.endf	Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

.L292:	.data.w	Fee_ConfigPtr
	.endo	.L292

.L953:	.data.w	Fee_State
	.endo	.L953

.L1969:	.data.w	Fee_SectorReMap
	.endo	.L1969

;State	r4	local
;ReturnVal	r0	local
;BankNumber	r8	local
;Offset	r6	local
;BankInfoPtr	r7	local
;EraseHeader	[sp]	local

;CurrBankSrcAddr	r9	param

	.section ".mcal_bss_asil_d_8_core0","awb"
Fee_SectorReMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_SectorReMap:	.space	64
	.endo	Fee_SectorReMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_SectorReMap
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.space	12
	.align	64
Fee_RWBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_RWBuffer:	.space	256
	.endo	Fee_RWBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_RWBuffer
	.section ".ghcalltbl",""
.L1971:	.data.w	.L1970
	.endo	.L1971
.L1973:	.data.w	.L1972
	.endo	.L1973
.L1975:	.data.w	.L1974
	.endo	.L1975
	.section ".ghrettbl",""
.L1977:	.data.w	.L1976
	.endo	.L1977
	.data
	.global	__caller.Fls_ReadWordsSync.i.ipi

	.global	__caller.Fls_BlankCheckSync.i.ii

	.global	__caller.Fls_ReadWordsSync.i.ipi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_RWBuffer - Fee_ConfigPtr) +0 == 192
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_BlockInfos - Fee_ConfigPtr) +0 == 116
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalUpdateBlockInfo:
.LDW82:
	push	{r4-fp,lr}
	sub	sp,sp,36
	mov	r10,r0
	ldr	r0,[r0]
	str	r0,[sp,8]
	cmp	r0,1<<18
	ldrb	r0,[r1,2]
	mov	r9,r1
	ldrb	r1,[r1,1]
	mov	r4,0
	ldr	r6,.L292
.LDW92:
	mov	r5,r4
	orr	r0,r1,r0 lsl 8
	movhs	r7,1
	movlo	r7,0
	strh	r0,[sp,6]
.L2903:

	bl	Fee_LocalGetUsrBlockIndex
	mov	fp,r0
	movw	r3,0xffff
	ldr	r0,[r6]
	lsl	r1,r7,1
	add	r2,r6,116
	cmp	fp,r3
	beq	.L1980
	ldr	r0,[r0,4]
	rsb	r3,fp,fp lsl 2
	add	r0,r0,r3 lsl 2
	ldrh	r0,[r0,6]
	mov	r3,15
	add	r0,r0,6
	udiv	r0,r0,r3
	add	r8,r0,1
	add	r0,r1,fp
	uxth	r8,r8
	add	r7,r2,r0 lsl 4
	b	.L1982
.L1980:
	ldrh	r0,[r0]
	ldrh	r3,[r9,6]
	add	r1,r1,r0
	ubfx	r8,r3,0,15
	add	r7,r2,r1 lsl 4
	mov	r1,r4
	b	.L1983
.L1985:
	add	r1,r1,1<<16
	add	r7,r7,16
.L1983:
	ldrh	r3,[r6,22]
	cmp	r3,r1 lsr 16
	bls	.L1984
	ldrh	r2,[r7,4]
	ldrh	r3,[sp,6]
	cmp	r2,r3
	bne	.L1985
.L1984:
	add	fp,r0,r1 lsr 16
	uxth	fp,fp
.L1982:
	ldrh	r0,[r9,6]
	tst	r0,1<<15
	moveq	r8,1
	beq	.L1990
	cmp	r8,0
	beq	.L2019
.L1990:
	ldr	r2,[sp,8]
	lsl	r0,r8,4
	str	r0,[sp,12]
	add	r0,r0,r2
	ubfx	r1,r0,0,13
	lsr	r0,r0,13
	ldr	r3,.L1969
	uxtb	r0,r0
	ldrb	r0,[r3,r0]
	mov	r2,4
	add	r0,r1,r0 lsl 13
	add	r1,sp,16
	str	r0,[sp,8]
.L2905:

	bl	Fls_ReadWordsSync
	subs	r4,r0,0
	bne	.L1991
	ldrh	r0,[sp,16]
	movw	r1,0x5555
	cmp	r0,r1
	bne	.L1993
	ldrh	r2,[sp,20]
	ldrh	r0,[sp,18]
	movw	r1,0xffff
	sub	r1,r1,r2
	cmp	r0,r1
	cmpeq	r0,r8
	bne	.L2011
	b	.L2020
.L1993:
	and	r0,r0,255
	cmp	r0,163
	beq	.L2019
	cmp	r0,255
	bne	.L2011
	ldr	r0,[sp,8]
	mov	r1,16
.L2907:

	bl	Fls_BlankCheckSync
	subs	r4,r0,0
	beq	.L2019
.L1991:
	cmp	r0,7
	beq	.L2019
	b	.L2011
.L2013:
	add	r5,r5,1
	ldr	r1,[r10]
	uxth	r5,r5
	add	r0,r1,r5 lsl 4
	ubfx	r1,r0,0,13
	lsr	r0,r0,13
	ldr	r2,.L1969
	uxtb	r0,r0
	ldrb	r0,[r2,r0]
	mov	r2,1
	add	r0,r1,r0 lsl 13
	add	r1,r6,192
.L2909:

	bl	Fls_ReadWordsSync
	subs	r4,r0,0
	ldrbeq	r0,[r6,192]
	cmpeq	r0,161
	lslne	r0,r5,4
	subne	r1,r0,16
	ldrne	r0,[r10]
	addne	r0,r0,r1
	movne	r5,r8
	strne	r0,[r10]
.L2011:
	sub	r0,r8,1
	cmp	r0,r5
	bhi	.L2013
	movhs	r4,0
	bne	.L2019
.L2020:
	cmp	fp,2
	bhs	.L2021
	ldr	r1,[r6]
	ldrh	r0,[r6,22]
	ldrh	r1,[r1]
	add	r1,r0,r1
	cmp	fp,r1
	addeq	r0,r0,1
	strheq	r0,[r6,22]
	ldr	r0,[r10]
	str	r0,[r7,8]
	ldrb	r0,[r9,5]
	ldrb	r1,[r9,3]
	pkhbt	r0,r1,r0 lsl 16
	ldrb	r1,[r9,4]
	orr	r0,r0,r1 lsl 8
	str	r0,[r7,12]
	ldrh	r0,[r9,6]
	lsr	r0,r0,15
	strb	r0,[r7]
	mov	r0,1
	strb	r0,[r7,1]
	mov	r0,0
	strb	r0,[r7,2]
	ldrh	r0,[sp,6]
	strh	r8,[r7,6]
	strh	r0,[r7,4]
	b	.L2025
.L2021:
	ldrb	r2,[r6,20]
	movs	r1,r2
	bne	.L2025
	mov	r3,225
	mov	r0,21
.L2911:

	bl	Det_ReportError
	ldrb	r0,[r6,20]
	add	r0,r0,1
	strb	r0,[r6,20]
.L2025:
	ldr	r0,[r10]
	ldr	r1,[sp,12]
	add	r0,r0,r1
	str	r0,[r10]
.L2019:
	mov	r0,r4
.LDW03:
	add	sp,sp,36
.L2913:

	pop	{r4-fp,pc}
__ghs_eofn_Fee_LocalUpdateBlockInfo:
	.endf	Fee_LocalUpdateBlockInfo
	.endf	Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;RetVal	r4	local
;BankNumber	r7	local
;BlockNumber	[sp,6]	local
;Index	fp	local
;DataPageCount	r5	local
;PageCount	r8	local
;TotalLen	[sp,12]	local
;Addr	[sp,8]	local
;BlockInfoPtr	r7	local
;BlockMarker	[sp,16]	local

;CurrBankAddr	r10	param
;BlockHeaderPtr	r9	param

	.section ".ghcalltbl",""
.L2904:	.data.w	.L2903
	.endo	.L2904
.L2906:	.data.w	.L2905
	.endo	.L2906
.L2908:	.data.w	.L2907
	.endo	.L2908
.L2910:	.data.w	.L2909
	.endo	.L2910
.L2912:	.data.w	.L2911
	.endo	.L2912
	.section ".ghrettbl",""
.L2914:	.data.w	.L2913
	.endo	.L2914
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Fls_ReadWordsSync.i.ipi

	.global	__caller.Fls_BlankCheckSync.i.ii

	.global	__caller.Fls_ReadWordsSync.i.ipi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
	.global	Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalTraversalUpdateBlockInfo:
.LDW13:
	push	{r4-r10,lr}
	sub	sp,sp,24
	ldr	r2,.L953
	ldr	r1,[r2,8]
	add	r5,r1,r0 lsl 4
	mov	r6,0
	ldrb	r2,[r5,4]
	mov	r9,r0
.LDW23:
	ldr	r1,[r5]
	movw	r8,0x1fff
	mov	r7,r6
	mov	r0,1<<18
	lsl	r2,r2,13
	str	r1,[sp,4]
	rsb	r10,r2,r0 lsl r9
.L2919:
	lsr	r0,r1,13
	ldr	r4,.L1969
	uxtb	r0,r0
	ldrb	r0,[r4,r0]
	and	r2,r1,r8
	add	r1,sp,8
	add	r0,r2,r0 lsl 13
	mov	r2,4
.L3501:

	bl	Fls_ReadWordsSync
	cmp	r0,0
	bne	.L2920
	ldrb	r1,[sp,8]
	cmp	r1,163
	bne	.L2922
	add	r1,sp,8
	add	r0,sp,4
.L3503:

	bl	Fee_LocalUpdateBlockInfo
	b	.L2920
.L2922:
	cmp	r1,255
	bne	.L2925
	ldr	r1,[sp,4]
	lsr	r0,r1,13
	and	r2,r1,r8
	and	r1,r1,255
	uxtb	r0,r0
	rsb	r1,r1,256
	ldrb	r0,[r4,r0]
	cmp	r1,128
	movhi	r1,128
	add	r0,r2,r0 lsl 13
.L3505:

	bl	Fls_BlankCheckSync
	cmp	r0,0
	bne	.L2920
	ldr	r1,[sp,4]
	cmp	r6,1
	strbeq	r6,[r5,7]
	moveq	r7,r6
	streq	r1,[r5]
	beq	.L2920
	tst	r1,255
	bne	.L2932
	lsl	r2,r9,18
	add	r2,r2,256
	cmp	r2,r1
	moveq	r2,4
	movne	r2,8
	strb	r2,[r5,7]
	mov	r7,1
	str	r1,[r5]
	b	.L2920
.L2932:
	add	r1,r1,256
	bic	r1,r1,255
	sub	r1,r1,16
	str	r1,[sp,4]
	b	.L2920
.L2925:
	cmp	r6,0
	ldreq	r1,[sp,4]
	tsteq	r1,255
	ldrheq	r2,[sp,8]
	movweq	r3,0x56a7
	cmpeq	r2,r3
	bne	.L2920
	add	r0,r1,16
	and	r1,r0,r8
	lsr	r0,r0,13
	uxtb	r0,r0
	ldrb	r0,[r4,r0]
	add	r0,r1,r0 lsl 13
	mov	r1,16
.L3507:

	bl	Fls_BlankCheckSync
	cmp	r0,1
	ldrbeq	r1,[sp,11]
	strbeq	r1,[r5,8]
	ldreq	r1,[sp,12]
	streq	r1,[r5,12]
	ldreq	r1,[sp,4]
	moveq	r6,r0
	addeq	r1,r1,16
	streq	r1,[sp,4]
.L2920:
	ldr	r1,[sp,4]
	add	r1,r1,16
	str	r1,[sp,4]
	cmp	r1,r10
	blo	.L2917
	cmp	r6,1
	str	r1,[r5]
	movne	r2,8
	moveq	r2,1
	strb	r2,[r5,7]
	b	.L2915
.L2917:
	cmp	r7,0
	bne	.L2915
	cmp	r0,7
	bne	.L2919
.L2915:
.LDW33:
	add	sp,sp,24
.L3509:

	pop	{r4-r10,pc}
__ghs_eofn_Fee_LocalTraversalUpdateBlockInfo:
	.endf	Fee_LocalTraversalUpdateBlockInfo
	.endf	Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;EndAddr	r10	local
;CurrBankSrcAddr	[sp,4]	local
;FindValid	r6	local
;SearchEnd	r7	local
;RetVal	r0	local
;BankInfoPtr	r5	local
;BufferUnion	[sp,8]	local

;BankNumber	r9	param

	.section ".ghcalltbl",""
.L3502:	.data.w	.L3501
	.endo	.L3502
.L3504:	.data.w	.L3503
	.endo	.L3504
.L3506:	.data.w	.L3505
	.endo	.L3506
.L3508:	.data.w	.L3507
	.endo	.L3508
	.section ".ghrettbl",""
.L3510:	.data.w	.L3509
	.endo	.L3510
	.data
	.global	__caller.Fls_BlankCheckSync.i.ii

	.global	__caller.Fls_BlankCheckSync.i.ii

	.global	__caller.Fls_ReadWordsSync.i.ipi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_ConfigPtr) +0 == 28
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalHandleUserWriteReq:
.LDW43:
	push	{r4-r5,lr}
	ldr	r12,.L3749
.LDW53:
	ldr	r3,[r12]
	ldr	r3,[r3,4]
	rsb	r2,r0,r0 lsl 2
	add	r3,r3,r2 lsl 2
	ldrb	r2,[r12,40]
	cmp	r2,1
	ldrhne	r2,[r3,6]
	mov	r4,1
	movne	r5,15
	addne	r2,r2,6
	udivne	r2,r2,r5
	strb	r4,[r12,6]
	addne	r2,r2,2
	moveq	r2,2
	uxthne	r2,r2
	mov	r5,2
	str	r5,[r12,76]
	str	r1,[r12,48]
	str	r5,[r12,28]
	ldrh	r5,[r3,4]
	mov	r1,0
	strh	r1,[r12,74]
	strh	r1,[r12,70]
	strh	r1,[r12,66]
	ldr	r1,[r12,16]
	strh	r0,[r12,54]
	add	r1,r1,r0 lsl 4
	ldr	r0,[r3]
	strh	r2,[r12,72]
	strh	r5,[r12,52]
	cmp	r0,0
	beq	.L3517
	ldr	r1,[r1,12]
	cmp	r1,r0
	bhs	.L3516
.L3517:
	ldrb	r0,[r12,4]
	ldr	r5,[r12,24]
	mov	r1,1<<18
	rsb	r1,r5,r1 lsl r0
	ldr	r5,[r12,12]
	add	r0,r5,r0 lsl 4
	ldrb	r0,[r0,4]
	sub	r0,r1,r0 lsl 13
	mov	r1,0
	lsr	r0,r0,4
	strb	r1,[r12,41]
	add	r1,r2,12
	uxth	r0,r0
	cmp	r0,r1
.L3750:

	pophs	{r4-r5,pc}
	ldr	r1,[r12,88]
	cmp	r1,0
	streq	r4,[r12,88]
	ldrb	r1,[r3,8]
	cmp	r1,0
	beq	.L3524
	cmp	r0,r2
.L3752:

	pophs	{r4-r5,pc}
.L3524:
	strb	r4,[r12,41]
.L3754:

	pop	{r4-r5,pc}
.L3516:
	mov	r0,3
	str	r4,[r12,80]
	str	r0,[r12,84]
.LDW63:
.L3756:

	pop	{r4-r5,pc}
__ghs_eofn_Fee_LocalHandleUserWriteReq:
	.endf	Fee_LocalHandleUserWriteReq
	.endf	Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BlockPtr	r3	local
;BlockPages	r2	local
;RemainingPages	r0	local
;BlockInfoPtr	r1	local

;BlockIndex	r0	param
;DataBufferPtr	r1	param

	.section ".ghrettbl",""
.L3751:	.data.w	.L3750
	.endo	.L3751
.L3753:	.data.w	.L3752
	.endo	.L3753
.L3755:	.data.w	.L3754
	.endo	.L3755
.L3757:	.data.w	.L3756
	.endo	.L3757
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_ConfigPtr) +0 == 28
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_RWBuffer - Fee_ConfigPtr) +0 == 192
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.global	Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalWrite:
.LDW73:
	push	{r2,r4-fp,lr}
	ldr	r4,.L3749
.LDW83:
	ldrh	r0,[r4,54]
	ldr	r1,[r4,16]
	add	r7,r1,r0 lsl 4
	ldr	r0,[r4,84]
	mov	r6,1
	add	r5,r4,192
	cmp	r0,2
	bne	.L3760
	ldr	r1,[r4,24]
	lsr	r0,r1,13
	ubfx	r2,r1,0,13
	ldr	r1,.L4644
	uxtb	r0,r0
	ldrb	r0,[r1,r0]
	ldrh	r1,[r4,66]
	add	r0,r2,r0 lsl 13
	lsr	r2,r1,2
	mov	r1,r5
.L4645:

	bl	Fls_CompareWordsSync
	ldr	r1,[r4,24]
	ldrh	r2,[r4,66]
	cmp	r0,0
	add	r1,r1,r2
	movne	r0,r6
	str	r1,[r4,24]
	bne	.L3980
	ldrh	r2,[r4,70]
	ldrh	r0,[r4,72]
	cmp	r2,r0
	bne	.L3760
	sub	r1,r1,r0 lsl 4
	str	r1,[r7,8]
	strb	r6,[r7,1]
	ldrb	r1,[r4,40]
	sub	r0,r0,1
	strh	r0,[r7,6]
	ldr	r0,[r4,88]
	subs	r1,r1,1
	movne	r1,1
	cmp	r0,0
	cmpne	r0,2
	strb	r1,[r7]
	movne	r0,0
	strbne	r6,[r4,110]
	strbne	r0,[r7,2]
	mov	r0,0
.L3980:
.L4647:

	bl	Fee_LocalHandleUsrJobEnd
.L3760:
	ldr	r0,[r4,84]
	cmp	r0,3
	ldreq	r0,[r4,24]
	ldrheq	r1,[r4,66]
	addeq	r0,r0,r1
	streq	r0,[r4,24]
	ldreq	r0,[r4,80]
.L4649:

	bleq	Fee_LocalHandleUsrJobEnd
	ldr	r0,[r4,28]
	cmp	r0,2
.L4651:

	popne	{r2,r4-fp,pc}
	ldr	r12,[r4,48]
	ldrh	r0,[r4,54]
	ldr	r1,[r4]
	ldrb	r10,[r4,40]
	mov	r3,r5
	ldr	r1,[r1,4]
	mov	r8,r12
	rsb	r0,r0,r0 lsl 2
	cmp	r10,1
	add	r0,r1,r0 lsl 2
	ldrhne	r0,[r0,6]
	moveq	r0,0
	add	r1,r0,6
	mov	r2,15
	udiv	r1,r1,r2
	ldrh	r9,[r4,70]
	add	r1,r1,1
	uxth	r1,r1
	cmp	r9,r1
	blo	.L3777
	mov	r0,r5
.L4653:

	bl	Fee_LocalMakeBlockMarker
	ldrh	r0,[r4,70]
	mov	r2,16
	strh	r2,[r4,66]
	add	r0,r0,1
	strh	r0,[r4,70]
	b	.L3779
.L3777:
	cmp	r9,0
	bne	.L3780
	ldr	r2,[r7,12]
	strb	r9,[r7,1]
	mov	r3,163
	add	r2,r2,1
	str	r2,[r7,12]
	ldrh	r7,[r4,52]
	strb	r3,[r4,192]
	cmp	r10,1
	strb	r7,[r5,1]
	lsr	r7,r7,8
	strb	r7,[r5,2]
	movne	r7,1<<15
	moveq	r7,r9
	orr	r1,r7,r1
	mov	r7,8
	strh	r1,[r4,198]
	lsr	r1,r2,8
	strb	r2,[r5,3]
	strb	r1,[r5,4]
	lsr	r1,r2,16
	add	r3,r5,8
	strb	r1,[r5,5]
	b	.L3785
.L3780:
	mov	r7,r6
.L3785:
	ldrh	r10,[r4,74]
	sub	r0,r0,r10
	uxth	r0,r0
	add	r1,r7,r0
	mov	r2,15
	add	r1,r1,13
	udiv	r1,r1,r2
	lsl	r2,r1,4
	ldrb	r1,[r4,24]
	rsb	r1,r1,256
	cmp	r1,r2
	movls	r2,r1
	cmp	r2,128
	movhi	r2,128
	strh	r2,[r4,66]
	ldrh	r2,[r4,66]
	asr	fp,r2,4
	rsb	r1,fp,fp lsl 4
	sub	r1,r1,r7
	add	r1,r1,1
	uxth	r1,r1
	cmp	r1,r0
	movgt	r1,r0
	add	r12,r12,r1
	str	r12,[r4,48]
	add	r0,r1,r10
	strh	r0,[r4,74]
	add	r0,fp,r9
	strh	r0,[r4,70]
.L3786:
	cmp	r8,r12
	bhs	.L3791
	tst	r3,15
	moveq	r0,161
	strbeq	r0,[r3],1
	ldrb	r0,[r8],1
	strb	r0,[r3],1
	b	.L3786
.L3793:
	mov	r0,0
	strb	r0,[r3],1
.L3791:
	tst	r3,15
	bne	.L3793
.L3779:
	ldr	r1,[r4,24]
	lsr	r0,r1,13
	ubfx	r3,r1,0,13
	ldr	r1,.L4644
	uxtb	r0,r0
	ldrb	r0,[r1,r0]
	str	r6,[r4,84]
	mov	r1,r5
	add	r0,r3,r0 lsl 13
.L4655:

	bl	Fls_Write
	cmp	r0,0
	movne	r0,r6
.L4657:

	blne	Fee_LocalHandleUsrJobEnd
.LDW93:
.L4659:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Fee_LocalWrite:
	.endf	Fee_LocalWrite
	.endf	Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

.L3749:	.data.w	Fee_ConfigPtr
	.endo	.L3749

.L4644:	.data.w	Fee_SectorReMap
	.endo	.L4644

;RemainLen	r0	local
;RealLen	r1	local
;PageOffset	r7	local
;BlockSize	r0	local
;BlockPages	r1	local
;Length	r2	local
;SrcDataBufferPtr	r8	local
;BlockPtr	r0	local
;BlockInfoPtr	r7	local
;BlockHeaderPtr	r3	local
;DestWriteBuffPtr	r3	local

	.section ".ghcalltbl",""
.L4646:	.data.w	.L4645
	.endo	.L4646
.L4648:	.data.w	.L4647
	.endo	.L4648
.L4650:	.data.w	.L4649
	.endo	.L4650
	.section ".ghrettbl",""
.L4652:	.data.w	.L4651
	.endo	.L4652
	.section ".ghcalltbl",""
.L4654:	.data.w	.L4653
	.endo	.L4654
.L4656:	.data.w	.L4655
	.endo	.L4656
.L4658:	.data.w	.L4657
	.endo	.L4658
	.section ".ghrettbl",""
.L4660:	.data.w	.L4659
	.endo	.L4660
	.data
	.global	__caller.Fls_Write.i.ipi

	.global	__caller.Fls_CompareWordsSync.i.ipi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_UserJobInfo) +0 == 0
	.assert 0x0 + (Fee_RWBuffer - Fee_UserJobInfo) +0 == 164
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
	.global	Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalRead:
.LDW04:
	push	{r4-r8,lr}
	ldr	r5,.L4937
.LDW14:
	ldr	r0,[r5,56]
	cmp	r0,2
	ldrheq	r0,[r5,28]
	ldrheq	r2,[r5,40]
	addeq	r1,r5,r0
	ldreq	r0,[r5,16]
	mov	r8,1
	addeq	r1,r1,164
	addeq	r2,r2,r0
	beq	.L4665
	b	.L4663
.L4667:
	tst	r1,15
	addeq	r1,r1,1
	ldrb	r3,[r1],1
	strb	r3,[r0]
	ldr	r0,[r5,16]
	add	r0,r0,1
	str	r0,[r5,16]
.L4665:
	cmp	r0,r2
	blo	.L4667
	ldrh	r0,[r5,36]
	cmp	r0,0
	strhne	r8,[r5,28]
.L4938:

	bleq	Fee_LocalHandleUsrJobEnd
.L4663:
	ldr	r0,[r5,56]
	cmp	r0,3
	ldreq	r0,[r5,52]
.L4940:

	bleq	Fee_LocalHandleUsrJobEnd
	ldr	r0,[r5]
	cmp	r0,1
.L4942:

	popne	{r4-r8,pc}
	ldrh	r0,[r5,36]
	ldrh	r1,[r5,28]
	mov	r3,15
	add	r2,r1,r0
	add	r2,r2,13
	udiv	r2,r2,r3
	lsl	r6,r2,4
	cmp	r6,256
	movhi	r6,256
	lsr	r2,r6,4
	ldr	r7,[r5,32]
	rsb	r2,r2,r2 lsl 4
	sub	r1,r2,r1
	add	r4,r1,1
	uxth	r4,r4
	cmp	r4,r0
	movge	r4,r0
	sub	r0,r0,r4
	mov	r1,r6
	strh	r0,[r5,36]
	mov	r0,r7
.L4944:

	bl	Fee_LocalSkipRead
	cmp	r0,0
	streq	r8,[r5,56]
	addeq	r0,r7,r6
	strheq	r4,[r5,40]
	movne	r0,r8
	streq	r0,[r5,32]
.L4946:

	blne	Fee_LocalHandleUsrJobEnd
.LDW24:
.L4948:

	pop	{r4-r8,pc}
__ghs_eofn_Fee_LocalRead:
	.endf	Fee_LocalRead
	.endf	Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;ReadBufferPtr	r1	local
;ReadLimitPtr	r2	local
;RealLen	r4	local
;SrcAddr	r7	local
;ReadLength	r6	local

	.section ".ghcalltbl",""
.L4939:	.data.w	.L4938
	.endo	.L4939
.L4941:	.data.w	.L4940
	.endo	.L4941
	.section ".ghrettbl",""
.L4943:	.data.w	.L4942
	.endo	.L4943
	.section ".ghcalltbl",""
.L4945:	.data.w	.L4944
	.endo	.L4945
.L4947:	.data.w	.L4946
	.endo	.L4947
	.section ".ghrettbl",""
.L4949:	.data.w	.L4948
	.endo	.L4949
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_GcJobInfo) +0 == 0
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
	.global	Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcRead:
.LDW34:
	push	{r4-r6,lr}
	ldr	r6,.L5044
.LDW44:
	ldrh	r1,[r6,14]
	ldrh	r2,[r6,20]
	sub	r1,r1,r2
	ldrb	r2,[r6,4]
	lsl	r1,r1,4
	uxth	r1,r1
	rsb	r2,r2,256
	cmp	r2,r1
	movls	r1,r2
	mov	r5,r1
.L5045:

	bl	Fee_LocalSkipRead
	cmp	r0,0
	strheq	r5,[r6,18]
	moveq	r0,1
	movne	r0,2
	streq	r0,[r6,24]
	moveq	r0,0
.LDW54:
.L5047:

	pop	{r4-r6,pc}
__ghs_eofn_Fee_LocalGcRead:
	.endf	Fee_LocalGcRead
	.endf	Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;ReadLength	r5	local
;Error	r4	local

;SrcAddr	none	param

	.section ".ghcalltbl",""
.L5046:	.data.w	.L5045
	.endo	.L5046
	.section ".ghrettbl",""
.L5048:	.data.w	.L5047
	.endo	.L5048
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_GcJobInfo) +0 == 0
	.assert 0x0 + (Fee_RWBuffer - Fee_GcJobInfo) +0 == 104
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.global	Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcWrite:
.LDW64:
	push	{r4,lr}
	ldr	r4,.L5044
.LDW74:
	mov	r2,1
	str	r2,[r4,24]
	ubfx	r2,r0,0,13
	lsr	r0,r0,13
	ldr	r3,.L4644
	uxtb	r0,r0
	ldrb	r0,[r3,r0]
	strh	r1,[r4,16]
	add	r0,r2,r0 lsl 13
	mov	r2,r1
	add	r1,r4,104
.L5247:

	bl	Fls_Write
	cmp	r0,0
	movne	r0,0
	strne	r0,[r4,24]
	movne	r0,1
.L5049:
.LDW84:
.L5249:

	pop	{r4,pc}
__ghs_eofn_Fee_LocalGcWrite:
	.endf	Fee_LocalGcWrite
	.endf	Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;ReturnValue	r0	local

;DestAddr	r0	param
;Size	r1	param

	.section ".ghcalltbl",""
.L5248:	.data.w	.L5247
	.endo	.L5248
	.section ".ghrettbl",""
.L5250:	.data.w	.L5249
	.endo	.L5250
	.data
	.global	__caller.Fls_Write.i.ipi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
	.global	Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcRequested:
.LDW94:
	ldr	r12,.L3749
.LDW05:
	ldrb	r0,[r12,4]
	ldr	r1,[r12,12]
	eor	r0,r0,1
	ldr	r0,[r1,r0 lsl 4]
	ldr	r1,[r12,16]
	str	r0,[r12,92]
	mov	r0,2
.L5297:
	mov	r2,0
	subs	r0,r0,1
	strb	r2,[r1,2]
	add	r1,r1,16
	bne	.L5297
	strb	r0,[r12,110]
	ldr	r0,[r12]
	ldrsh	r1,[r12,22]
	ldrsh	r0,[r0]
	add	r0,r1,r0
	sub	r0,r0,1
	strh	r0,[r12,100]
.L5415:

	b	Fee_LocalGcStartCopy
.LDW15:
__ghs_eofn_Fee_LocalGcRequested:
	.endf	Fee_LocalGcRequested
	.endf	Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BlockInfoPtr	r1	local

	.section ".ghtailcalltbl",""
.L5416:	.data.w	.L5415
	.endo	.L5416
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
	.global	Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcStartCopy:
.LDW25:
	push	{r2,r4-r5,lr}
	ldr	r12,.L3749
.LDW35:
	mov	r0,0
	ldrb	r2,[r12,110]
	mov	r3,r0
	ldrsh	r1,[r12,100]
	cmp	r2,1
	bne	.L5429
	ldr	r2,[r12]
	ldrsh	r2,[r2]
	cmp	r1,r2
	sublt	r1,r2,1
	strblt	r0,[r12,110]
	sxthlt	r1,r1
.L5429:
	cmp	r1,0
	blt	.L5430
	ldr	r4,[r12,16]
	add	r2,r4,r1 lsl 4
	ldrb	r5,[r2,2]
	ldrb	r2,[r2,1]
	cmp	r2,1
	cmpeq	r5,0
	bne	.L5425
	strh	r1,[r12,100]
	add	r2,r4,r1 lsl 4
	mov	r0,1
	strb	r0,[r2,2]
	ldrb	r1,[r12,4]
	ldr	r4,[r12,92]
	strh	r3,[r12,108]
	mov	r3,1<<18
	ldr	r0,[r2,8]
	eor	r1,r1,1
	ldrh	r2,[r2,6]
	rsb	r3,r4,r3 lsl r1
	ldr	r4,[r12,12]
	str	r0,[r12,96]
	strh	r2,[r12,102]
	add	r1,r4,r1 lsl 4
	ldrb	r1,[r1,4]
	sub	r1,r3,r1 lsl 13
	lsr	r1,r1,4
	add	r2,r2,1
	uxth	r1,r1
	cmp	r2,r1
	bls	.L5432
	mov	r0,5
.L5745:

	pop	{r2,r4-r5,pc}
.L5425:
	sub	r1,r1,1
	b	.L5429
.L5432:
	mov	r1,4
	str	r1,[r12,88]
.L5747:

	bl	Fee_LocalGcRead
.L5749:

	pop	{r2,r4-r5,pc}
.L5430:
	str	r0,[r12,112]
	mov	r1,6
	str	r1,[r12,88]
.LDW45:
.L5751:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Fee_LocalGcStartCopy:
	.endf	Fee_LocalGcStartCopy
	.endf	Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BlockInfoPtr	r2	local
;BlockCount	r1	local
;CopiedFlag	r5	local
;Error	r0	local

	.section ".ghrettbl",""
.L5746:	.data.w	.L5745
	.endo	.L5746
	.section ".ghcalltbl",""
.L5748:	.data.w	.L5747
	.endo	.L5748
	.section ".ghrettbl",""
.L5750:	.data.w	.L5749
	.endo	.L5750
.L5752:	.data.w	.L5751
	.endo	.L5752
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_RWBuffer - Fee_State) +0 == 188
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcStartCopyWrite:
.LDW55:
	push	{r2,r4-r5,lr}
	ldr	r4,.L6248
.LDW65:
	ldr	r1,[r4,108]
	mov	r0,0
	mov	r5,r0
	cmp	r1,3
	bne	.L5755
	ldrsh	r3,[r4,96]
	ldr	r1,[r4,12]
	add	r0,r1,r3 lsl 4
	ldr	r1,[r4,84]
	cmp	r1,4
	bne	.L5757
	ldrb	r1,[r0,2]
	cmp	r1,1
	strbeq	r5,[r0,1]
	strbeq	r5,[r0,2]
	b	.L6229
.L5757:
	ldrb	r1,[r4,1]
	cmp	r1,0
	bne	.L5762
.L5763:
	ldr	r1,[r4,88]
	ldrh	r2,[r4,100]
	add	r1,r1,r2
	str	r1,[r4,88]
	mov	r1,1
	strb	r1,[r4,1]
	strb	r5,[r0,2]
.L6229:

.L6249:

	bl	Fee_LocalGcStartCopy
	b	.L5755
.L5762:
	mov	r0,1
.L5755:
	ldr	r1,[r4,108]
	cmp	r1,2
.L6251:

	popne	{r2,r4-r5,pc}
	ldr	r1,[r4,84]
	cmp	r1,5
	bne	.L5765
	ldrh	r1,[r4,104]
	ldrh	r0,[r4,100]
	ldr	r2,[r4,88]
	ldrh	r3,[r4,98]
	add	r1,r1,r0 lsr 4
	strh	r1,[r4,104]
	ldrh	r1,[r4,104]
	add	r2,r2,r0
	add	r12,r3,1
	str	r2,[r4,88]
	cmp	r1,r12
	bne	.L5768
	ldrsh	r3,[r4,96]
	ldr	r12,[r4,12]
	add	r0,r12,r3 lsl 4
	ldrb	r12,[r0,2]
	cmp	r12,1
	subeq	r1,r2,r1 lsl 4
	streq	r1,[r0,8]
	strb	r5,[r4,1]
	sub	r0,r3,1
	strh	r0,[r4,96]
.L6253:

	bl	Fee_LocalGcStartCopy
	b	.L5765

.L4937:	.data.w	Fee_UserJobInfo
	.endo	.L4937

.L5044:	.data.w	Fee_GcJobInfo
	.endo	.L5044

.L6248:	.data.w	Fee_State
	.endo	.L6248

.L5768:
;line2168
..lin.36297a98..579b88bd.0_1::
.LDWlin1:
	cmp	r1,r3
	strheq	r5,[r4,102]
	moveq	r0,2
	streq	r0,[r4,108]
	beq	.L5777
	mov	r1,4
	str	r1,[r4,84]
	ldr	r1,[r4,92]
	add	r0,r1,r0
	str	r0,[r4,92]
.L6255:

	bl	Fee_LocalGcRead
.L5765:
	ldr	r1,[r4,108]
	cmp	r1,2
	ldreq	r1,[r4,84]
	cmpeq	r1,4
.L6257:

	popne	{r2,r4-r5,pc}
.L5777:
	ldrb	r1,[r4,88]
	mov	r0,5
	str	r0,[r4,84]
	ldrh	r0,[r4,102]
	rsb	r1,r1,256
	cmp	r1,r0
	addhi	r1,r0,16
	strhhi	r1,[r4,102]
	addhi	r2,r4,r0
	ldrhhi	r1,[r4,98]
	addhi	r0,r2,188
.L6259:

	blhi	Fee_LocalMakeBlockMarker
	ldrh	r1,[r4,102]
	ldr	r0,[r4,88]
.L6261:

	bl	Fee_LocalGcWrite
.LDW75:
.L6263:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Fee_LocalGcStartCopyWrite:
	.endf	Fee_LocalGcStartCopyWrite
	.endf	Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;Error	r0	local
;BlockInfoPtr	r0	local

	.section ".ghcalltbl",""
.L6250:	.data.w	.L6249
	.endo	.L6250
	.section ".ghrettbl",""
.L6252:	.data.w	.L6251
	.endo	.L6252
	.section ".ghcalltbl",""
.L6254:	.data.w	.L6253
	.endo	.L6254
.L6256:	.data.w	.L6255
	.endo	.L6256
	.section ".ghrettbl",""
.L6258:	.data.w	.L6257
	.endo	.L6258
	.section ".ghcalltbl",""
.L6260:	.data.w	.L6259
	.endo	.L6260
.L6262:	.data.w	.L6261
	.endo	.L6262
	.section ".ghrettbl",""
.L6264:	.data.w	.L6263
	.endo	.L6264
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
	.global	Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcErasePrevBank:
.LDW85:
	push	{r4-r8,lr}
	ldr	r5,.L6736
.LDW95:
	mov	r4,0
	ldr	r1,[r5,112]
	movw	r7,0x1ff0
	cmp	r1,2
	blt	.L6267
	ldr	r0,[r5,92]
	cmp	r0,1<<18
	movhs	r6,1
	movlo	r6,0
	cmp	r1,2
	bne	.L6269
	mov	r1,16
.L6738:

	bl	Fls_BlankCheckSync
	cmp	r0,0
	bne	.L6271
	ldr	r0,[r5,92]
	mov	r1,16
	add	r0,r0,r7
.L6740:

	bl	Fls_BlankCheckSync
	cmp	r0,0
.L6271:
	movne	r0,3
	strne	r0,[r5,112]
	bne	.L6277
.L6269:
	ldr	r0,[r5,112]
	cmp	r0,3
	bne	.L6276
.L6277:
	ldr	r1,[r5,12]
	add	r1,r1,r6 lsl 4
	ldrb	r2,[r1,4]
	cmp	r2,2
	ldrlo	r0,[r5,92]
	movhs	r4,r0
	movhs	r0,2
	addlo	r3,r2,r1
	strhs	r0,[r5,88]
	lsrlo	r0,r0,13
	strblo	r0,[r3,5]
	ldrblo	r0,[r3,5]
	ldrlo	r3,.L6737
	movlo	r12,1
	strblo	r12,[r3,r0]
	addlo	r0,r2,1
	strblo	r0,[r1,4]
.L6276:
	ldr	r0,[r5,92]
	ldr	r1,[r5,88]
	add	r0,r0,1<<13
	str	r0,[r5,92]
	cmp	r1,2
	beq	.L6267
	lsls	r1,r0,14
	lsleq	r2,r6,5
	lsleq	r3,r2,16
	uxtheq	r2,r2
	moveq	r12,r3
	beq	.L6287
	b	.L6267
.L6286:
	ldr	r7,.L6737
	ldrb	r8,[r7,r1]
	cmp	r8,0
	strbeq	r1,[r7,r12 lsr 16]
	addeq	r12,r12,1<<16
	add	r3,r3,1<<16
.L6287:
	lsr	r1,r3,16
	add	r7,r2,32
	cmp	r1,r7
	blo	.L6286
	mov	r1,0
	str	r1,[r5,112]
	mov	r1,8
	str	r1,[r5,88]
	ldr	r1,[r5,12]
	sub	r0,r0,1<<18
	str	r0,[r5,92]
	add	r0,r1,r6 lsl 4
	ldrb	r0,[r0,4]
	cmp	r0,0
	ldrne	r0,[r5]
	ldrne	r0,[r0,20]
	cmpne	r0,0
	beq	.L6294
.L6742:

	blx	r0
.L6267:
	ldr	r0,[r5,88]
	cmp	r0,3
	bne	.L6294
	mov	r0,1
	str	r0,[r5,112]
	mov	r1,1<<13
	ldr	r0,[r5,92]
.L6744:

	bl	Fls_Erase
	cmp	r0,0
	movne	r0,0
	movne	r4,3
	strne	r0,[r5,112]
.L6294:
	mov	r0,r4
.LDW06:
.L6746:

	pop	{r4-r8,pc}
__ghs_eofn_Fee_LocalGcErasePrevBank:
	.endf	Fee_LocalGcErasePrevBank
	.endf	Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BankNumber	r6	local
;Offset	r2	local
;Error	r4	local
;BankPtr	r1	local
;SectorNumber	r0	local

	.section ".ghcalltbl",""
.L6739:	.data.w	.L6738
	.endo	.L6739
.L6741:	.data.w	.L6740
	.endo	.L6741
.L6743:	.data.w	.L6742
	.endo	.L6743
.L6745:	.data.w	.L6744
	.endo	.L6745
	.section ".ghrettbl",""
.L6747:	.data.w	.L6746
	.endo	.L6747
	.data
	.global	__caller.Fls_Erase.i.ii

	.global	__caller.Fls_BlankCheckSync.i.ii

	.global	__caller.Fls_BlankCheckSync.i.ii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
	.global	Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcStatePageCompare:
.LDW16:
	push	{r4-r5,r7-r8,lr}
	ldr	r12,.L6248
	mov	r2,r0
.LDW26:
	mov	r0,0
	subs	r2,r2,6
	add	r1,r12,84
	blo	.L6754
	beq	.L6751
	cmp	r2,2
	blo	.L6752
	bne	.L6754
	mov	r1,9
	b	.L7168
.L6751:
	mov	r1,7
.L7168:

	str	r1,[r12,84]
.L7181:

	pop	{r4-r5,r7-r8,pc}
.L6752:
	ldrb	r2,[r12]
	ldr	r5,[r12,8]
	add	r3,r5,r2 lsl 4
	mov	r4,32
	strb	r0,[r3,4]
	lsl	r3,r2,29
.L6932:
	ldr	r7,.L6737
	subs	r4,r4,1
	strb	r0,[r7,r3 lsr 24]
	add	r3,r3,1<<24
	bne	.L6932
	eor	r2,r2,1
	ldr	r3,[r1,4]
	cmp	r2,1
	strb	r2,[r12]
	add	r5,r5,r2 lsl 4
	add	r3,r3,32
	movne	r4,1<<18
	str	r3,[r5]
	str	r4,[r1,4]
	mov	r4,3
	str	r4,[r1]
	ldr	r1,[r12,24]
	str	r3,[r12,20]
	strb	r0,[r12,37]
	cmp	r1,2
.L7183:

	popne	{r4-r5,r7-r8,pc}
	mov	r1,1<<18
	rsb	r1,r3,r1 lsl r2
	ldrb	r2,[r5,4]
	sub	r1,r1,r2 lsl 13
	ldrh	r2,[r12,68]
	lsr	r1,r1,4
	uxth	r1,r1
	cmp	r1,r2
	movlo	r0,5
.L7185:

	pop	{r4-r5,r7-r8,pc}
.L6754:
	ldrb	r2,[r12]
	ldr	r4,[r12,8]
	eor	r3,r2,1
	add	r4,r4,r3 lsl 4
	ldr	r3,[r1,4]
	add	r3,r3,256
	str	r3,[r1,4]
	str	r3,[r4]
	ldr	r3,[r12,4]
	cmp	r3,1
	cmpeq	r2,1
	moveq	r2,6
	streq	r2,[r1]
.L7187:

	popeq	{r4-r5,r7-r8,pc}
	ldrb	r2,[r4,7]
	cmp	r2,8
	strne	r0,[r1]
	strne	r0,[r12,4]
	moveq	r2,4
	strbeq	r2,[r4,7]
	moveq	r2,1
	streq	r2,[r1]
.L6748:
.LDW36:
.L7189:

	pop	{r4-r5,r7-r8,pc}
__ghs_eofn_Fee_LocalGcStatePageCompare:
	.endf	Fee_LocalGcStatePageCompare
	.endf	Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BankInfoPtr	r4	local
;Error	r0	local

;GcState	r2	param

	.section ".ghrettbl",""
.L7182:	.data.w	.L7181
	.endo	.L7182
.L7184:	.data.w	.L7183
	.endo	.L7184
.L7186:	.data.w	.L7185
	.endo	.L7186
.L7188:	.data.w	.L7187
	.endo	.L7188
.L7190:	.data.w	.L7189
	.endo	.L7190
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_RWBuffer - Fee_State) +0 == 188
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
	.global	Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGcProgramStatePage:
.LDW46:
	push	{r4-r8,lr}
	ldr	r5,.L6248
	ldr	r2,[r5,108]
.LDW56:
	mov	r1,r0
	mov	r0,0
	mov	r7,r0
	cmp	r2,2
	blt	.L7193
	cmp	r2,3
	bne	.L7195
	ldr	r3,[r5,84]
	cmp	r3,7
	cmpne	r3,9
	moveq	r0,2
	streq	r0,[r5,108]
	beq	.L7205
	ldrb	r3,[r5,1]
	cmp	r3,0
	moveq	r1,1
	strbeq	r1,[r5,1]
	ldreq	r1,[r5,88]
	streq	r0,[r5,108]
	addeq	r1,r1,256
	streq	r1,[r5,88]
.L8125:

	popeq	{r4-r8,pc}
	mov	r0,1
.L7195:
	cmp	r2,2
.L8127:

	popne	{r4-r8,pc}
.L7205:
	mov	r0,r1
.L8129:

	bl	Fee_LocalGcStatePageCompare
	strb	r7,[r5,1]
	str	r7,[r5,108]
.L8131:

	pop	{r4-r8,pc}
.L7193:
	subs	r0,r1,6
	add	r2,r5,188
	cmpne	r0,2
	bne	.L7209
	ldrb	r12,[r5]
	ldr	r0,[r5,8]
	eor	r8,r12,1
	mov	r6,16
	mov	r3,r7
	add	r4,r0,r8 lsl 4
.L7214:
	strb	r7,[r2,r3]
	add	r3,r3,1
	cmp	r3,16
	blo	.L7214
	mov	r3,165
	cmp	r1,6
	strb	r3,[r5,203]
	bne	.L7215
	movw	r1,0x56a7
	add	r7,r0,r12 lsl 4
	strh	r1,[r5,188]
	mov	r0,3
	ldrb	r1,[r7,8]
.L8133:

	bl	__umoddiv32_hard
	add	r0,r0,1
	strb	r0,[r4,8]
	strb	r0,[r5,191]
	ldr	r0,[r7,12]
	add	r0,r0,1
	str	r0,[r4,12]
	str	r0,[r5,192]
	ldr	r0,[r5,88]
	add	r0,r0,240
	bic	r0,r0,255
	str	r0,[r5,88]
	b	.L7217

.L6736:	.data.w	Fee_ConfigPtr
	.endo	.L6736

.L6737:	.data.w	Fee_SectorReMap
	.endo	.L6737

.L7215:
;line2602
..lin.36297a98..837415ff.0_2::
.LDWlin2:
	ldrb	r3,[r4,4]
	movw	r0,0x45a7
	strh	r0,[r5,188]
	mov	r1,r7
	strb	r3,[r5,190]
.L7221:
	lsr	r0,r1,16
	cmp	r0,r3
	lslhs	r0,r0,16
	bhs	.L7222
	add	r12,r2,r0 lsl 2
	add	r0,r0,r4
	ldrb	r0,[r0,5]
	lsl	r0,r0,24
	orr	r0,r0,170
	add	r1,r1,1<<16
	str	r0,[r12,16]
	b	.L7221
.L7224:
	lsr	r1,r0,16
	add	r1,r2,r1 lsl 2
	add	r0,r0,1<<16
	str	r7,[r1,16]
.L7222:
	tst	r0,3<<16
	bne	.L7224
	lsr	r0,r0,16
	lsl	r0,r0,2
	add	r6,r0,16
	uxth	r6,r6
.L7217:
	ldr	r0,[r5,88]
	mov	r1,1<<18
	ldrb	r2,[r4,4]
	rsb	r1,r0,r1 lsl r8
	sub	r1,r1,r2 lsl 13
	lsr	r1,r1,4
	uxth	r1,r1
	cmp	r1,16
	movlo	r0,5
	movhs	r1,r6
.L8135:

	blhs	Fee_LocalGcWrite
.L8137:

	pop	{r4-r8,pc}
.L7209:
	mov	r0,4
.L7676:
	ldr	r1,.L8124
	subs	r0,r0,1
	str	r1,[r2],4
	bne	.L7676
	ldrh	r0,[r5,100]
	ldr	r1,[r5,88]
	add	r0,r0,r1
	mov	r1,16
.L8139:

	bl	Fee_LocalGcWrite
.LDW66:
.L8141:

	pop	{r4-r8,pc}
__ghs_eofn_Fee_LocalGcProgramStatePage:
	.endf	Fee_LocalGcProgramStatePage
	.endf	Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;GcNumber	r0	local
;Size	r6	local
;MarkerPtr	r2	local
;Error	r0	local
;BankInfoPtr	r4	local

;GcState	r1	param

	.section ".ghrettbl",""
.L8126:	.data.w	.L8125
	.endo	.L8126
.L8128:	.data.w	.L8127
	.endo	.L8128
	.section ".ghcalltbl",""
.L8130:	.data.w	.L8129
	.endo	.L8130
	.section ".ghrettbl",""
.L8132:	.data.w	.L8131
	.endo	.L8132
	.section ".ghcalltbl",""
.L8134:	.data.w	.L8133
	.endo	.L8134
.L8136:	.data.w	.L8135
	.endo	.L8136
	.section ".ghrettbl",""
.L8138:	.data.w	.L8137
	.endo	.L8138
	.section ".ghcalltbl",""
.L8140:	.data.w	.L8139
	.endo	.L8140
	.section ".ghrettbl",""
.L8142:	.data.w	.L8141
	.endo	.L8142
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_ConfigPtr) +0 == 88
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
..gh.f.a.1.e.19:
	.endo	..gh.f.a.1.e.19
	.global	Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGC:
.LDW76:
	push	{r4,lr}
	ldr	r4,.L6736
.LDW86:
	mov	r0,0
	ldr	r1,[r4,88]
	sub	r1,r1,4
	cmp	r1,1
.L8590:

	blls	Fee_LocalGcStartCopyWrite
	ldr	r1,[r4,88]
	cmp	r1,1
	cmpeq	r0,0
.L8592:

	bleq	Fee_LocalGcRequested
	ldr	r1,[r4,88]
	cmp	r1,6
	cmpeq	r0,0
	moveq	r0,r1
.L8594:

	bleq	Fee_LocalGcProgramStatePage
	ldr	r1,[r4,88]
	cmp	r1,3
	cmpeq	r0,0
.L8596:

	bleq	Fee_LocalGcErasePrevBank
	ldr	r1,[r4,88]
	cmp	r1,7
	cmpeq	r0,0
	moveq	r0,r1
.L8598:

	bleq	Fee_LocalGcProgramStatePage
	ldr	r1,[r4,88]
	cmp	r1,8
	cmpeq	r0,0
	moveq	r0,r1
.L8600:

	bleq	Fee_LocalGcProgramStatePage
	ldr	r1,[r4,88]
	cmp	r1,9
	bne	.L8163
	cmp	r0,0
	bne	.L8167
	mov	r0,r1
.L8602:

	bl	Fee_LocalGcProgramStatePage
.L8163:
	cmp	r0,0
.L8167:
	movne	r0,2
	strne	r0,[r4,88]
	movne	r0,0
	strne	r0,[r4,8]
	ldrne	r0,[r4]
	ldrne	r0,[r0,16]
	cmpne	r0,0
.L8604:

	blxne	r0
.L8143:
.LDW96:
.L8606:

	pop	{r4,pc}
__ghs_eofn_Fee_LocalGC:
	.endf	Fee_LocalGC
	.endf	Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;Error	r0	local

	.section ".ghcalltbl",""
.L8591:	.data.w	.L8590
	.endo	.L8591
.L8593:	.data.w	.L8592
	.endo	.L8593
.L8595:	.data.w	.L8594
	.endo	.L8595
.L8597:	.data.w	.L8596
	.endo	.L8597
.L8599:	.data.w	.L8598
	.endo	.L8599
.L8601:	.data.w	.L8600
	.endo	.L8601
.L8603:	.data.w	.L8602
	.endo	.L8603
.L8605:	.data.w	.L8604
	.endo	.L8605
	.section ".ghrettbl",""
.L8607:	.data.w	.L8606
	.endo	.L8607
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
	.global	Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalCommonDetCheck:
.LDW07:
	push	{r4,lr}
.LDW17:
	mov	r4,1
	b	.L8761

.L8124:	.data.w	0x5a5a5a5a
	.endo	.L8124

.L8761:

;line2833
..lin.36297a98..818099e3.0_3::
.LDWlin3:
..gh.beginasm.21:
	.endo	..gh.beginasm.21
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.22:
	.endo	..gh.endasm.22

;line2834
..lin.36297a98..818099e3.0_4::
.LDWlin4:
	uxtb	r2,r2
	cmp	r2,0
	movne	r2,r0
	movne	r3,224
	movne	r1,0
	bne	.L8753
.L8614:
	ldr	r1,.L8762
	ldr	r1,[r1]
	cmp	r1,0
	bne	.L8617
.L8618:
	mov	r2,r0
	mov	r3,r4
.L8753:

	mov	r0,21
.L8763:

	bl	Det_ReportError
	b	.L8616
.L8617:
	mov	r4,r2
.L8616:
	mov	r0,r4
.LDW27:
.L8765:

	pop	{r4,pc}
__ghs_eofn_Fee_LocalCommonDetCheck:
	.endf	Fee_LocalCommonDetCheck
	.endf	Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;ReturnValue	r4	local

;ServiceID	r0	param

	.section ".mcal_bss_asil_d_8_core0","awb"
	.align	4
Fee_Init_Status..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_Init_Status:	.space	4
	.endo	Fee_Init_Status..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_Init_Status
	.section ".ghcalltbl",""
.L8764:	.data.w	.L8763
	.endo	.L8764
	.section ".ghrettbl",""
.L8766:	.data.w	.L8765
	.endo	.L8766
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_RWBuffer - Fee_RWBuffer) +0 == 0
..gh.f.a.1.e.23:
	.endo	..gh.f.a.1.e.23
	.global	Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalSkipRead:
.LDW37:
	push	{r4-r9}
	ldr	r4,.L8877
.LDW47:
	ldr	r7,.L8878
	ubfx	r5,r0,0,13
	mov	r3,0
	mov	r2,r1
	movw	r8,0x1fff
	rsb	r6,r5,1<<13
	str	r3,[r7]
	ldr	r3,.L8879
	cmp	r6,r1
	bhs	.L8769
	lsr	r12,r0,13
	uxtb	r12,r12
	add	r9,r12,r3
	ldrb	r12,[r3,r12]
	ldrb	r9,[r9,1]
	sub	r12,r9,r12
	cmp	r12,1
	subhi	r1,r1,r6
	addhi	r2,r6,r4
	stmhi	r7,{r1-r2}
	addhi	r1,r6,r0
	andhi	r2,r1,r8
	lsrhi	r1,r1,13
	uxtbhi	r1,r1
	ldrbhi	r1,[r3,r1]
	addhi	r1,r2,r1 lsl 13
	movhi	r2,r6
	strhi	r1,[r7,8]
.L8769:
	lsr	r0,r0,13
	uxtb	r0,r0
	ldrb	r0,[r3,r0]
	mov	r1,r4
	add	r0,r5,r0 lsl 13
	pop	{r4-r9}
.L8880:

	b	Fls_Read
.LDW57:
__ghs_eofn_Fee_LocalSkipRead:
	.endf	Fee_LocalSkipRead
	.endf	Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;SectorRemain	r6	local
;SectorNo	r12	local
;ActReadLength	r2	local

;SrcAddr	r0	param
;ReadLength	r1	param

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Fee_SkipReadStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_SkipReadStatus:	.space	12
	.endo	Fee_SkipReadStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_SkipReadStatus
	.section ".ghtailcalltbl",""
.L8881:	.data.w	.L8880
	.endo	.L8881
	.data
	.global	__caller.Fls_Read.i.ipi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
..gh.f.a.1.e.24:
	.endo	..gh.f.a.1.e.24
	.global	Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_LocalGetStatus:
.LDW67:
.LDW77:
	ldr	r0,.L8762
	ldr	r0,[r0]
	cmp	r0,0
.L9172:

	reteq	
	ldr	r0,.L9171
	ldr	r1,[r0,24]
	cmp	r1,0
	movne	r0,2
.L9174:

	retne	
	ldr	r1,[r0,4]
	cmp	r1,1
	beq	.L8896
	ldr	r1,[r0,84]
	cmp	r1,0
	cmpne	r1,2
	ldrbne	r0,[r0,2]
	cmpne	r0,0
	beq	.L8893
.L8896:
	mov	r0,3
.L9176:

	ret	
.L8893:
	mov	r0,1
.LDW87:
.L9178:

	ret	
__ghs_eofn_Fee_LocalGetStatus:
	.endf	Fee_LocalGetStatus
	.endf	Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.section ".ghrettbl",""
.L9173:	.data.w	.L9172
	.endo	.L9173
.L9175:	.data.w	.L9174
	.endo	.L9175
.L9177:	.data.w	.L9176
	.endo	.L9177
.L9179:	.data.w	.L9178
	.endo	.L9179
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
	.assert 0x0 + (Fee_BlockInfos - Fee_ConfigPtr) +0 == 116
..gh.f.a.1.e.25:
	.endo	..gh.f.a.1.e.25
	.global	Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.:
Fee_InitializeModuleAndBanks:
.LDW97:
	push	{r2,r4-r9,lr}
	ldr	r6,.L10712
.LDW08:
	mov	r4,0
	str	r0,[r6]
.L9184:
	mov	r5,0
.L9189:
	add	r0,r5,r4 lsl 1
	mov	r9,0
	add	r0,r6,r0 lsl 4
	add	r5,r5,1
	strh	r9,[r0,116]!
	cmp	r5,2
	str	r9,[r0,12]
	blo	.L9189
	lsl	r8,r4,18
.L9192:
	mov	r5,0
.L9196:
	mov	r0,r8
.L10714:

	bl	Fee_LocalCheckEraseStatePage
	add	r5,r5,1
	subs	r7,r0,0
	bne	.L9198
	add	r8,r8,256
	cmp	r5,2
	blo	.L9196
	add	r0,r8,1<<13
	add	r9,r9,1
	lsr	r8,r0,13
	cmp	r9,2
	lsl	r8,r8,13
	bls	.L9192
	b	.L9185
.L9198:
	lsl	r3,r5,8
	ldr	r1,.L10713
	add	r2,r3,r4 lsl 18
	cmp	r0,2
	str	r2,[r1,r4 lsl 4]
	bne	.L9185
	mov	r0,r4
.L10716:

	bl	Fee_LocalTraversalUpdateBlockInfo
	cmp	r0,7
	beq	.L9207
.L9185:
	cmp	r7,16
	beq	.L9207
	add	r4,r4,1
	uxtb	r4,r4
	cmp	r4,2
	blo	.L9184
	ldr	r0,.L8762
	mov	r1,1
	str	r1,[r0]
.L10718:

	bl	Fee_LocalSetInitGc
.L10720:

	pop	{r2,r4-r9,pc}
.L9207:
	ldr	r0,[r6]
	ldr	r0,[r0,16]
	cmp	r0,0
.L10722:

	blxne	r0
	mov	r2,0
	mov	r3,9
	mov	r0,21
	mov	r1,r2
.L10724:

	bl	Det_ReportError
.LDW18:
.L10726:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Fee_InitializeModuleAndBanks:
	.endf	Fee_InitializeModuleAndBanks
	.endf	Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
;BankNumber	r4	local
;Count	r5	local
;FeeFailRetryNumber	r9	local
;RetVal	r0	local
;State	r7	local
;CurrBankSrcAddr	r8	local

;ConfigPtr	r0	param

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Fee_BankInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.::
Fee_BankInfo:	.space	32
	.endo	Fee_BankInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.endo	Fee_BankInfo
	.section ".ghcalltbl",""
.L10715:	.data.w	.L10714
	.endo	.L10715
.L10717:	.data.w	.L10716
	.endo	.L10717
.L10719:	.data.w	.L10718
	.endo	.L10719
	.section ".ghrettbl",""
.L10721:	.data.w	.L10720
	.endo	.L10721
	.section ".ghcalltbl",""
.L10723:	.data.w	.L10722
	.endo	.L10723
.L10725:	.data.w	.L10724
	.endo	.L10725
	.section ".ghrettbl",""
.L10727:	.data.w	.L10726
	.endo	.L10727
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
__callee.Fee_Init.v.p::
	.size	__callee.Fee_Init.v.p,0
Fee_Init::
.LDW28:
.LDW38:
	b	.L10929

.L8762:	.data.w	Fee_Init_Status
	.endo	.L8762

.L8877:	.data.w	Fee_RWBuffer
	.endo	.L8877

.L8878:	.data.w	Fee_SkipReadStatus
	.endo	.L8878

.L8879:	.data.w	Fee_SectorReMap
	.endo	.L8879

.L9171:	.data.w	Fee_State
	.endo	.L9171

.L10712:	.data.w	Fee_ConfigPtr
	.endo	.L10712

.L10713:	.data.w	Fee_BankInfo
	.endo	.L10713

.L10929:

;line3141
..lin.36297a98..66e780a8.0_5::
.LDWlin5:
..gh.beginasm.27:
	.endo	..gh.beginasm.27
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.28:
	.endo	..gh.endasm.28

;line3142
..lin.36297a98..66e780a8.0_6::
.LDWlin6:
	uxtb	r2,r2
	cmp	r2,0
	movne	r3,224
	movne	r2,0
	bne	.L10921
.L10734:
	cmp	r0,0
	bne	.L10737
.L10738:
	mov	r3,9
.L10921:

	mov	r1,r2
	mov	r0,21
.L10933:

	b	Det_ReportError
.L10737:
	ldr	r2,.L10930
	mov	r1,0
	ldr	r3,.L10931
	stmib	r2,{r1,r3}
	str	r1,[r2,24]
	strb	r1,[r2,28]
	strb	r1,[r2,1]
	strb	r1,[r2,2]
	strh	r1,[r2,18]
	strb	r1,[r2,16]
	str	r1,[r2,80]
	str	r1,[r2,84]
	str	r1,[r2,108]
	strb	r1,[r3,7]
	mov	r12,r1
	strb	r1,[r3,23]
.L10743:
	ldr	r2,.L10932
	strb	r12,[r2,r1]
	add	r1,r1,1
	cmp	r1,64
	blo	.L10743
.L10935:

	b	Fee_InitializeModuleAndBanks
.LDW48:
__ghs_eofn_Fee_Init::
	.endf	Fee_Init
;Count	r1	local

;ConfigPtr	r0	param

	.section ".ghtailcalltbl",""
.L10934:	.data.w	.L10933
	.endo	.L10934
.L10936:	.data.w	.L10935
	.endo	.L10936
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_UserJobInfo) +0 == 0
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
__callee.Fee_SetMode.v.i::
	.size	__callee.Fee_SetMode.v.i,0
Fee_SetMode::
.LDW58:
	push	{r4,lr}
	mov	r4,r0
.LDW68:
	mov	r0,1
.L11046:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
.L11048:

	popne	{r4,pc}
.L11050:

	bl	Fee_LocalGetStatus
	cmp	r0,1
	cmpne	r0,3
	ldreq	r1,.L11045
	moveq	r0,1
	movne	r3,6
	movne	r2,1
	streq	r4,[r1,8]
	movne	r1,0
	movne	r0,21
	strbeq	r0,[r1,4]
.L11052:

	blne	Det_ReportRuntimeError
.LDW78:
.L11054:

	pop	{r4,pc}
__ghs_eofn_Fee_SetMode::
	.endf	Fee_SetMode
;FeeStatus	r0	local

;Mode	r4	param

	.section ".ghcalltbl",""
.L11047:	.data.w	.L11046
	.endo	.L11047
	.section ".ghrettbl",""
.L11049:	.data.w	.L11048
	.endo	.L11049
	.section ".ghcalltbl",""
.L11051:	.data.w	.L11050
	.endo	.L11051
.L11053:	.data.w	.L11052
	.endo	.L11053
	.section ".ghrettbl",""
.L11055:	.data.w	.L11054
	.endo	.L11055
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_ConfigPtr) +0 == 28
	.assert 0x0 + (Fee_State - Fee_ConfigPtr) +0 == 4
	.assert 0x0 + (Fee_ConfigPtr - Fee_ConfigPtr) +0 == 0
..gh.f.a.1.e.30:
	.endo	..gh.f.a.1.e.30
__callee.Fee_Read.i.iipi::
	.size	__callee.Fee_Read.i.iipi,0
Fee_Read::
.LDW88:
	push	{r4-r10,lr}
	mov	r9,r0
	mov	r7,r1
	mov	r10,r2
	mov	r8,r3
.LDW98:
	mov	r4,1
	mov	r0,2
.L11632:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
	bne	.L11075
	mov	r0,r9
.L11634:

	bl	Fee_LocalGetUsrBlockIndex
	mov	r6,r0
	movw	r0,0xffff
	cmp	r6,r0
	moveq	r3,2
	beq	.L11171
	cmp	r10,0
	moveq	r3,4
	beq	.L11171
	cmp	r8,0
	beq	.L11073
	ldr	r5,.L11631
	ldr	r1,[r5]
	rsb	r0,r6,r6 lsl 2
	ldr	r1,[r1,4]
	add	r0,r1,r0 lsl 2
	ldrh	r0,[r0,6]
	cmp	r7,r0
	movhs	r3,3
	bhs	.L11171
	add	r1,r8,r7
	cmp	r1,r0
	ble	.L11076
.L11073:
	mov	r3,5
.L11171:
	mov	r2,2
	mov	r1,0
	mov	r0,21
.L11636:

	bl	Det_ReportError
	b	.L11075
.L11076:
.L11638:

	bl	Fee_LocalGetStatus
	cmp	r0,1
	cmpne	r0,3
	bne	.L11077
	ldr	r1,[r5,16]
	str	r4,[r5,28]
	mov	r0,2
	str	r0,[r5,76]
	add	r4,r1,r6 lsl 4
	ldrb	r1,[r4]
	ldrb	r0,[r4,1]
	strh	r7,[r5,56]
	str	r10,[r5,44]
	strh	r8,[r5,64]
	strh	r9,[r5,52]
	cmp	r0,1
	strh	r6,[r5,54]
	cmpeq	r1,1
	beq	.L11080
	mov	r1,3
	cmp	r0,1
	str	r1,[r5,84]
	moveq	r0,5
	movne	r0,4
	str	r0,[r5,80]
	b	.L11086
.L11080:
	add	r1,r7,7
	mov	r0,15
.L11640:

	bl	__umoddiv32_hard
	ldr	r2,[r4,8]
	add	r0,r0,1
	strh	r0,[r5,56]
	add	r1,r2,r1 lsl 4
	str	r1,[r5,60]
.L11086:
	mov	r4,0
	b	.L11075
.L11077:
	mov	r3,6
	mov	r2,2
	mov	r1,0
	mov	r0,21
.L11642:

	bl	Det_ReportRuntimeError
.L11075:
	mov	r0,r4
.LDW09:
.L11644:

	pop	{r4-r10,pc}
__ghs_eofn_Fee_Read::
	.endf	Fee_Read
;BlockIndex	r6	local
;ReturnValue	r4	local
;FeeStatus	r0	local
;ConsistentFlag	r0	local
;ValidFlag	r1	local
;BlockInfoPtr	r4	local
;BlockSize	r0	local

;BlockNumber	r9	param
;BlockOffset	r7	param
;DataBufferPtr	r10	param
;Length	r8	param

	.section ".ghcalltbl",""
.L11633:	.data.w	.L11632
	.endo	.L11633
.L11635:	.data.w	.L11634
	.endo	.L11635
.L11637:	.data.w	.L11636
	.endo	.L11637
.L11639:	.data.w	.L11638
	.endo	.L11639
.L11641:	.data.w	.L11640
	.endo	.L11641
.L11643:	.data.w	.L11642
	.endo	.L11643
	.section ".ghrettbl",""
.L11645:	.data.w	.L11644
	.endo	.L11645
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.31:
	.endo	..gh.f.a.1.e.31
__callee.Fee_Write.i.ip::
	.size	__callee.Fee_Write.i.ip,0
Fee_Write::
.LDW19:
	push	{r4-r6,lr}
	mov	r5,r0
	mov	r6,r1
.LDW29:
	mov	r4,1
	mov	r0,3
.L11942:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
	bne	.L11656
	mov	r0,r5
.L11944:

	bl	Fee_LocalGetUsrBlockIndex
	mov	r5,r0
	movw	r0,0xffff
	cmp	r5,r0
	moveq	r3,2
	moveq	r2,3
	moveq	r1,0
	beq	.L11931
.L11650:
	movs	r1,r6
	bne	.L11657
.L11654:
	mov	r3,4
	mov	r2,3
.L11931:

	mov	r0,21
.L11946:

	bl	Det_ReportError
	b	.L11656
.L11657:
.L11948:

	bl	Fee_LocalGetStatus
	cmp	r0,1
	cmpne	r0,3
	bne	.L11658
	ldr	r0,.L11045
	mov	r4,0
	mov	r1,r6
	strb	r4,[r0,12]
	mov	r0,r5
.L11950:

	bl	Fee_LocalHandleUserWriteReq
	b	.L11656
.L11658:
	mov	r3,6
	mov	r2,3
	mov	r1,0
	mov	r0,21
.L11952:

	bl	Det_ReportRuntimeError
.L11656:
	mov	r0,r4
.LDW39:
.L11954:

	pop	{r4-r6,pc}
__ghs_eofn_Fee_Write::
	.endf	Fee_Write
;BlockIndex	r5	local
;ReturnValue	r4	local
;FeeStatus	r0	local

;BlockNumber	r5	param
;DataBufferPtr	r6	param

	.section ".ghcalltbl",""
.L11943:	.data.w	.L11942
	.endo	.L11943
.L11945:	.data.w	.L11944
	.endo	.L11945
.L11947:	.data.w	.L11946
	.endo	.L11947
.L11949:	.data.w	.L11948
	.endo	.L11949
.L11951:	.data.w	.L11950
	.endo	.L11951
.L11953:	.data.w	.L11952
	.endo	.L11953
	.section ".ghrettbl",""
.L11955:	.data.w	.L11954
	.endo	.L11955
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.32:
	.endo	..gh.f.a.1.e.32
__callee.Fee_Cancel.v.v::
	.size	__callee.Fee_Cancel.v.v,0
Fee_Cancel::
.LDW49:
	push	{r2,r4-r5,lr}
.LDW59:
	mov	r0,4
.L12138:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
.L12140:

	popne	{r2,r4-r5,pc}
.L12142:

	bl	Fee_LocalGetStatus
	cmp	r0,2
	bne	.L11960
	ldr	r4,.L10930
	mov	r5,0
	ldr	r0,[r4,4]
	subs	r0,r0,3
	beq	.L11964
	cmp	r0,1
	ldreq	r0,[r4,20]
	ldrheq	r1,[r4,62]
	streq	r5,[r4,4]
	addeq	r0,r0,r1
	streq	r0,[r4,20]
	b	.L11967
.L11964:
	str	r5,[r4,4]
.L12144:

	bl	Fls_Cancel
.L11967:
	str	r5,[r4,24]
	mov	r0,3
	str	r5,[r4,80]
	str	r0,[r4,72]
.L12146:

	pop	{r2,r4-r5,pc}
.L11960:
	mov	r3,8
	mov	r2,4
	mov	r1,0
	mov	r0,21
.L12148:

	bl	Det_ReportRuntimeError
.LDW69:
.L12150:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Fee_Cancel::
	.endf	Fee_Cancel

	.section ".ghcalltbl",""
.L12139:	.data.w	.L12138
	.endo	.L12139
	.section ".ghrettbl",""
.L12141:	.data.w	.L12140
	.endo	.L12141
	.section ".ghcalltbl",""
.L12143:	.data.w	.L12142
	.endo	.L12143
.L12145:	.data.w	.L12144
	.endo	.L12145
	.section ".ghrettbl",""
.L12147:	.data.w	.L12146
	.endo	.L12147
	.section ".ghcalltbl",""
.L12149:	.data.w	.L12148
	.endo	.L12149
	.section ".ghrettbl",""
.L12151:	.data.w	.L12150
	.endo	.L12151
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Fls_Cancel.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.33:
	.endo	..gh.f.a.1.e.33
__callee.Fee_GetStatus.i.v::
	.size	__callee.Fee_GetStatus.i.v,0
Fee_GetStatus::
.LDW79:
	str	lr,[sp,-8]!
.LDW89:
	b	.L12250

.L10930:	.data.w	Fee_State
	.endo	.L10930

.L10931:	.data.w	Fee_BankInfo
	.endo	.L10931

.L10932:	.data.w	Fee_SectorReMap
	.endo	.L10932

.L11045:	.data.w	Fee_UserJobInfo
	.endo	.L11045

.L11631:	.data.w	Fee_ConfigPtr
	.endo	.L11631

.L12250:

;line3595
..lin.36297a98..be617378.0_7::
.LDWlin7:
..gh.beginasm.34:
	.endo	..gh.beginasm.34
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.35:
	.endo	..gh.endasm.35

;line3596
..lin.36297a98..be617378.0_8::
.LDWlin8:
	lsls	r0,r0,24
	beq	.L12158
	mov	r3,224
	mov	r2,5
	mov	r1,0
	mov	r0,21
.L12251:

	bl	Det_ReportError
	mov	r0,0
.L12253:

	ldr	pc,[sp],8
.L12158:
.L12255:

	bl	Fee_LocalGetStatus
.LDW99:
.L12257:

	ldr	pc,[sp],8
__ghs_eofn_Fee_GetStatus::
	.endf	Fee_GetStatus

	.section ".bss","awb"
.L12205:
	.endo	.L12205
	.section ".ghcalltbl",""
.L12252:	.data.w	.L12251
	.endo	.L12252
	.section ".ghrettbl",""
.L12254:	.data.w	.L12253
	.endo	.L12254
	.section ".ghcalltbl",""
.L12256:	.data.w	.L12255
	.endo	.L12256
	.section ".ghrettbl",""
.L12258:	.data.w	.L12257
	.endo	.L12258
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.36:
	.endo	..gh.f.a.1.e.36
__callee.Fee_GetJobResult.i.v::
	.size	__callee.Fee_GetJobResult.i.v,0
Fee_GetJobResult::
.LDW001:
	str	lr,[sp,-8]!
.LDW101:
	mov	r0,6
.L12356:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
	ldreq	r1,.L12355
	movne	r0,1
	ldreq	r0,[r1,48]
.LDW201:
.L12358:

	ldr	pc,[sp],8
__ghs_eofn_Fee_GetJobResult::
	.endf	Fee_GetJobResult

	.section ".ghcalltbl",""
.L12357:	.data.w	.L12356
	.endo	.L12357
	.section ".ghrettbl",""
.L12359:	.data.w	.L12358
	.endo	.L12359
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_UserJobInfo - Fee_UserJobInfo) +0 == 0
	.assert 0x0 + (Fee_RWBuffer - Fee_UserJobInfo) +0 == 164
..gh.f.a.1.e.37:
	.endo	..gh.f.a.1.e.37
__callee.Fee_InvalidateBlock.i.i::
	.size	__callee.Fee_InvalidateBlock.i.i,0
Fee_InvalidateBlock::
.LDW301:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW401:
	mov	r4,1
	mov	r0,7
.L12605:

	bl	Fee_LocalCommonDetCheck
	cmp	r0,0
	bne	.L12367
	mov	r0,r5
.L12607:

	bl	Fee_LocalGetUsrBlockIndex
	mov	r5,r0
	movw	r0,0xffff
	cmp	r5,r0
	bne	.L12368
	mov	r3,2
	mov	r2,7
	mov	r1,0
	mov	r0,21
.L12609:

	bl	Det_ReportError
	b	.L12367
.L12368:
.L12611:

	bl	Fee_LocalGetStatus
	cmp	r0,1
	cmpne	r0,3
	bne	.L12369
	ldr	r1,.L12355
	mov	r0,r5
	strb	r4,[r1,12]
	add	r1,r1,164
.L12613:

	bl	Fee_LocalHandleUserWriteReq
	mov	r4,0
	b	.L12367
.L12369:
	mov	r3,6
	mov	r2,7
	mov	r1,0
	mov	r0,21
.L12615:

	bl	Det_ReportRuntimeError
.L12367:
	mov	r0,r4
.LDW501:
.L12617:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Fee_InvalidateBlock::
	.endf	Fee_InvalidateBlock
;BlockIndex	r5	local
;ReturnValue	r4	local
;FeeStatus	r0	local

;BlockNumber	r5	param

	.section ".ghcalltbl",""
.L12606:	.data.w	.L12605
	.endo	.L12606
.L12608:	.data.w	.L12607
	.endo	.L12608
.L12610:	.data.w	.L12609
	.endo	.L12610
.L12612:	.data.w	.L12611
	.endo	.L12612
.L12614:	.data.w	.L12613
	.endo	.L12614
.L12616:	.data.w	.L12615
	.endo	.L12616
	.section ".ghrettbl",""
.L12618:	.data.w	.L12617
	.endo	.L12618
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.38:
	.endo	..gh.f.a.1.e.38
__callee.Fee_GetVersionInfo.v.p::
	.size	__callee.Fee_GetVersionInfo.v.p,0
Fee_GetVersionInfo::
.LDW601:
.LDW701:
	movs	r1,r0
	moveq	r3,4
	moveq	r2,8
	moveq	r0,21
.L12699:

	beq	Det_ReportError
.L12621:
	mov	r1,21
	strh	r1,[r0,2]
	mov	r1,175
	strh	r1,[r0]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW801:
.L12701:

	ret	
__ghs_eofn_Fee_GetVersionInfo::
	.endf	Fee_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L12661:
	.endo	.L12661
	.section ".ghtailcalltbl",""
.L12700:	.data.w	.L12699
	.endo	.L12700
	.section ".ghrettbl",""
.L12702:	.data.w	.L12701
	.endo	.L12702
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.39:
	.endo	..gh.f.a.1.e.39
__callee.Fee_EraseImmediateBlock.i.i::
	.size	__callee.Fee_EraseImmediateBlock.i.i,0
Fee_EraseImmediateBlock::
.LDW901:
.LDW011:
	mov	r0,0
.LDW111:
.L12745:

	ret	
__ghs_eofn_Fee_EraseImmediateBlock::
	.endf	Fee_EraseImmediateBlock

;BlockNumber	none	param

	.section ".bss","awb"
.L12727:
	.endo	.L12727
	.section ".ghrettbl",""
.L12746:	.data.w	.L12745
	.endo	.L12746
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.40:
	.endo	..gh.f.a.1.e.40
__callee.Fee_MainFunction.v.v::
	.size	__callee.Fee_MainFunction.v.v,0
Fee_MainFunction::
.LDW211:
	push	{r4,lr}
.LDW311:
	b	.L13032

.L12355:	.data.w	Fee_UserJobInfo
	.endo	.L12355

.L13032:

;line3868
..lin.36297a98..1b7595ff.0_9::
.LDWlin9:
..gh.beginasm.41:
	.endo	..gh.beginasm.41
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.42:
	.endo	..gh.endasm.42

;line3869
..lin.36297a98..1b7595ff.0_10::
.LDWlin10:
	lsls	r0,r0,24
	beq	.L12753
	mov	r3,224
	mov	r2,18
	mov	r1,0
	mov	r0,21
.L13034:

	bl	Det_ReportError
.L13036:

	pop	{r4,pc}
.L12753:
	ldr	r4,.L13033
	ldrb	r0,[r4,28]
	cmp	r0,1
	bne	.L12756
	ldr	r0,[r4,108]
	cmp	r0,1
	beq	.L12756
	ldr	r0,[r4,32]
.L13038:

	bl	Fls_SetMode
	mov	r0,0
	strb	r0,[r4,28]
.L12756:
.L13040:

	bl	Fls_GetStatus
	cmp	r0,1
.L13042:

	popne	{r4,pc}
.L13044:

	bl	Fee_LocalDecideMainJob
	ldr	r0,[r4,4]
	subs	r0,r0,1
	subs	r0,r0,2
	blo	.L12762
	beq	.L12764
	cmp	r0,1
.L13046:

	popne	{r4,pc}
	ldr	r0,[r4,80]
	cmp	r0,1
.L13048:

	blne	Fee_LocalWrite
.L13050:

	pop	{r4,pc}
.L12762:
	ldr	r0,[r4,108]
	cmp	r0,1
.L13052:

	blne	Fee_LocalGC
.L13054:

	pop	{r4,pc}
.L12764:
	ldr	r0,[r4,80]
	cmp	r0,1
.L13056:

	blne	Fee_LocalRead
.LDW411:
.L13058:

	pop	{r4,pc}
__ghs_eofn_Fee_MainFunction::
	.endf	Fee_MainFunction

	.section ".ghcalltbl",""
.L13035:	.data.w	.L13034
	.endo	.L13035
	.section ".ghrettbl",""
.L13037:	.data.w	.L13036
	.endo	.L13037
	.section ".ghcalltbl",""
.L13039:	.data.w	.L13038
	.endo	.L13039
.L13041:	.data.w	.L13040
	.endo	.L13041
	.section ".ghrettbl",""
.L13043:	.data.w	.L13042
	.endo	.L13043
	.section ".ghcalltbl",""
.L13045:	.data.w	.L13044
	.endo	.L13045
	.section ".ghrettbl",""
.L13047:	.data.w	.L13046
	.endo	.L13047
	.section ".ghcalltbl",""
.L13049:	.data.w	.L13048
	.endo	.L13049
	.section ".ghrettbl",""
.L13051:	.data.w	.L13050
	.endo	.L13051
	.section ".ghcalltbl",""
.L13053:	.data.w	.L13052
	.endo	.L13053
	.section ".ghrettbl",""
.L13055:	.data.w	.L13054
	.endo	.L13055
	.section ".ghcalltbl",""
.L13057:	.data.w	.L13056
	.endo	.L13057
	.section ".ghrettbl",""
.L13059:	.data.w	.L13058
	.endo	.L13059
	.data
	.global	__caller.Fls_GetStatus.i.v

	.global	__caller.Fls_SetMode.v.i

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.43:
	.endo	..gh.f.a.1.e.43
__callee.Fee_JobEndNotification.v.v::
	.size	__callee.Fee_JobEndNotification.v.v,0
Fee_JobEndNotification::
.LDW511:
	push	{r4,lr}
.LDW611:
	b	.L13295

.L13033:	.data.w	Fee_State
	.endo	.L13033

.L13295:

;line3979
..lin.36297a98..7115212d.0_11::
.LDWlin11:
..gh.beginasm.44:
	.endo	..gh.beginasm.44
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.45:
	.endo	..gh.endasm.45

;line3980
..lin.36297a98..7115212d.0_12::
.LDWlin12:
	lsls	r0,r0,24
	beq	.L13066
	mov	r3,224
	mov	r2,16
	mov	r1,0
	mov	r0,21
.L13298:

	bl	Det_ReportError
.L13300:

	pop	{r4,pc}
.L13066:
	ldr	r4,.L13296
	ldr	r2,[r4]
	ldr	r0,.L13297
	cmp	r2,0
	beq	.L13069
	ldmib	r4,{r1,r3}
	mov	r0,r3
.L13302:

	bl	Fls_Read
	cmp	r0,0
.L13304:

	blne	Fee_JobErrorNotification
	mov	r0,0
	str	r0,[r4]
.L13306:

	pop	{r4,pc}
.L13069:
	ldr	r1,[r0,4]
	cmp	r1,3
	movge	r1,2
	strge	r1,[r0,80]
.L13308:

	popge	{r4,pc}
	cmp	r1,0
	movgt	r1,2
	strgt	r1,[r0,108]
.LDW711:
.L13310:

	pop	{r4,pc}
__ghs_eofn_Fee_JobEndNotification::
	.endf	Fee_JobEndNotification

	.section ".ghcalltbl",""
.L13299:	.data.w	.L13298
	.endo	.L13299
	.section ".ghrettbl",""
.L13301:	.data.w	.L13300
	.endo	.L13301
	.section ".ghcalltbl",""
.L13303:	.data.w	.L13302
	.endo	.L13303
.L13305:	.data.w	.L13304
	.endo	.L13305
	.section ".ghrettbl",""
.L13307:	.data.w	.L13306
	.endo	.L13307
.L13309:	.data.w	.L13308
	.endo	.L13309
.L13311:	.data.w	.L13310
	.endo	.L13311
	.data
	.global	__caller.Fee_JobErrorNotification.v.v

	.global	__caller.Fls_Read.i.ipi

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_GcJobInfo - Fee_State) +0 == 84
	.assert 0x0 + (Fee_UserJobInfo - Fee_State) +0 == 24
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.46:
	.endo	..gh.f.a.1.e.46
__callee.Fee_JobErrorNotification.v.v::
	.size	__callee.Fee_JobErrorNotification.v.v,0
Fee_JobErrorNotification::
.LDW811:
.LDW911:
	b	.L13458

.L13296:	.data.w	Fee_SkipReadStatus
	.endo	.L13296

.L13297:	.data.w	Fee_State
	.endo	.L13297

.L13458:

;line4055
..lin.36297a98..d4053b00.0_13::
.LDWlin13:
..gh.beginasm.47:
	.endo	..gh.beginasm.47
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.48:
	.endo	..gh.endasm.48

;line4056
..lin.36297a98..d4053b00.0_14::
.LDWlin14:
	lsls	r0,r0,24
	movne	r3,224
	movne	r2,17
	movne	r1,0
	movne	r0,21
.L13460:

	bne	Det_ReportError
.L13318:
	ldr	r0,.L13459
	ldr	r1,[r0,4]
	mov	r2,3
	cmp	r1,3
	strge	r2,[r0,80]
	movge	r1,1
	strge	r1,[r0,76]
.L13462:

	retge	
	cmp	r1,0
	strgt	r2,[r0,108]
.LDW021:
.L13464:

	ret	
__ghs_eofn_Fee_JobErrorNotification::
	.endf	Fee_JobErrorNotification

	.section ".ghtailcalltbl",""
.L13461:	.data.w	.L13460
	.endo	.L13461
	.section ".ghrettbl",""
.L13463:	.data.w	.L13462
	.endo	.L13463
.L13465:	.data.w	.L13464
	.endo	.L13465
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Fee_State - Fee_State) +0 == 0
..gh.f.a.1.e.49:
	.endo	..gh.f.a.1.e.49
__callee.Fee_GetCycleCount.i.ip::
	.size	__callee.Fee_GetCycleCount.i.ip,0
Fee_GetCycleCount::
.LDW121:
	push	{r2,r4-r7,lr}
	mov	r7,r0
	mov	r6,r1
.LDW221:
	mov	r0,19
.L13738:

	bl	Fee_LocalCommonDetCheck
	subs	r4,r0,0
	bne	.L13478
	mov	r3,4
	cmp	r6,0
	beq	.L13529
	ldr	r5,.L13459
	movs	r0,r7
	beq	.L13480
.L13740:

	bl	Fee_LocalGetUsrBlockIndex
	movw	r1,0xffff
	mov	r3,2
	cmp	r0,r1
	bne	.L13481
.L13529:
	mov	r2,19
	mov	r1,0
	mov	r0,21
.L13742:

	bl	Det_ReportError
	mov	r4,1
	b	.L13478
.L13481:
	ldr	r1,[r5,12]
	add	r0,r1,r0 lsl 4
	ldr	r0,[r0,12]
	b	.L13728
.L13480:
	ldrb	r0,[r5]
	ldr	r1,[r5,8]
	add	r0,r1,r0 lsl 4
	ldr	r0,[r0,12]
	lsr	r0,r0,1
.L13728:

	str	r0,[r6]
.L13478:
	mov	r0,r4
.LDW321:
.L13744:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Fee_GetCycleCount::
	.endf	Fee_GetCycleCount
;BlockIndex	r0	local
;ReturnValue	r4	local

;BlockNumber	r7	param
;CountPtr	r6	param

	.section ".ghcalltbl",""
.L13739:	.data.w	.L13738
	.endo	.L13739
.L13741:	.data.w	.L13740
	.endo	.L13741
.L13743:	.data.w	.L13742
	.endo	.L13743
	.section ".ghrettbl",""
.L13745:	.data.w	.L13744
	.endo	.L13745
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"

.L13459:	.data.w	Fee_State
	.endo	.L13459

;Fee_ConfigPtr	Fee_ConfigPtr	static
;Fee_GcJobInfo	Fee_GcJobInfo	static
;Fee_UserJobInfo	Fee_UserJobInfo	static
;Fee_BankInfo	Fee_BankInfo	static
;Fee_State	Fee_State	static
;Fee_BlockInfos	Fee_BlockInfos	static
;Fee_SkipReadStatus	Fee_SkipReadStatus	static
;Fee_RWBuffer	Fee_RWBuffer	static
;Fee_SectorReMap	Fee_SectorReMap	static
;Fee_Init_Status	Fee_Init_Status	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682572..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	148,35,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,101,101,92,115,114,99,47,70,101,101,46,99,0
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
	.data.b	86,21,0,0
	.data.b	2,0
	.data.b	179,7,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,101,101,92,115,114,99,47,70,101,101,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,101,101,92,105,110,99,108,117,100,101,92,70,101,101,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,101,101,92,105,110,99,108,117,100,101,92,70,101,101,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,70,101,101,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,77,101,109,73,102,92,77,101,109,73,102,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,77,101,109,73,102,92,78,118,77,46,104,0
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
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,70,101,101,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,68,101,116,92,105,110,99,108,117,100,101,92,68,101,116,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,101,101,92,105,110,99,108,117,100,101,92,70,101,101,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,108,115,92,105,110,99,108,117,100,101,92,70,108,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,108,115,92,105,110,99,108,117,100,101,92,70,108,115,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,70,108,115,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,102,108,97,115,104,92,105,110,99,92,100,102,108,97,115,104,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,102,108,97,115,104,92,105,110,99,92,100,102,108,97,115,104,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,102,108,97,115,104,92,105,110,99,92,102,108,97,115,104,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,70,108,115,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,102,108,97,115,104,92,105,110,99,92,112,102,108,97,115,104,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,102,108,97,115,104,92,105,110,99,92,112,102,108,97,115,104,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,70,108,115,92,105,110,99,108,117,100,101,92,70,108,115,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,70,108,115,95,80,66,99,102,103,46,104,0
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
	.data.w	.Ldw_begin+3639
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

	.data.b	53
	.data.w	.Ldw_begin+2348

	.section	.debug_abbrev		;off: 39
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 68
	.data.b	47
	.data.w	.Ldw_begin+63

	.section	.debug_abbrev		;off: 46
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 73
	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 74
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 53
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 82
	.data.b	23
	.data.w	.Ldw_begin+68
	.data.b	0

	.section	.debug_abbrev		;off: 60
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 88
	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1283
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3358

	.data.b	53
	.data.w	.Ldw_begin+108

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1194
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+127

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	105,110,116,0
	.section	.debug_info		;off: 142
	.data.w	.Ldw_str_begin+260
	.data.b	5
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+1295

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 155
	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 80
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 163
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1259
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1295
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2543

	.data.b	53
	.data.w	.Ldw_begin+1295

	.data.b	47
	.data.w	.Ldw_begin+182

	.data.b	47
	.data.w	.Ldw_begin+2242

	.data.b	53
	.data.w	.Ldw_begin+192

	.data.b	47
	.data.w	.Ldw_begin+197

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+202
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1941

	.data.b	74
	.data.w	.Ldw_begin+1259
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1259

	.data.b	53
	.data.w	.Ldw_begin+244

	.data.b	47
	.data.w	.Ldw_begin+249

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+254
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1941

	.data.b	53
	.data.w	.Ldw_begin+274

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2242

	.data.b	53
	.data.w	.Ldw_begin+1259

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2543

	.data.b	53
	.data.w	.Ldw_begin+339

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 264
	.data.b	115,104,111,114,116,0
	.section	.debug_info		;off: 357
	.data.w	.Ldw_str_begin+264
	.data.b	5
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1593
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1801
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1593
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2030

	.data.b	53
	.data.w	.Ldw_begin+2153

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1295
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1295
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1117
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3498

	.data.b	53
	.data.w	.Ldw_begin+455

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+460
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1235
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+292
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+249
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1117
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1194
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1418

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+572
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
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

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+182
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	11

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	7
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	6

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	2
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	3
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	2
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+1295

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 270
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 740
	.data.w	.Ldw_str_begin+270
	.data.b	7
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+2543

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+1941

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+1941

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	128,2
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	255,1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	64
	.data.w	.Ldw_begin+1259

	.data.b	56
	.data.w	.Ldw_begin+141
	.data.b	4
	.data.b	0
	.data.b	63

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1283
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1259
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1295

	.data.b	53
	.data.w	.Ldw_begin+898

	.data.b	47
	.data.w	.Ldw_begin+903

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+249
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1235
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1319
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+292
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1117
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1259
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+187
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1259
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+908
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1259
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3663
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3675
	.data.b	0

	.data.b	0

	.data.b	52
	.section	.debug_str		;off: 283
	.data.b	0
	.section	.debug_info		;off: 1071
	.data.w	.Ldw_str_begin+283
	.data.b	27
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 93
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

	.section	.debug_info		;off: 1080
	.data.b	51
	.section	.debug_str		;off: 284
	.data.b	77,69,77,73,70,95,85,78,73,78,73,84,0
	.section	.debug_info		;off: 1081
	.data.w	.Ldw_str_begin+284
	.data.b	28
	.data.b	5
	.data.b	5
	.data.b	0

	.section	.debug_abbrev		;off: 110
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 1089
	.data.b	51
	.section	.debug_str		;off: 297
	.data.b	77,69,77,73,70,95,73,68,76,69,0
	.section	.debug_info		;off: 1090
	.data.w	.Ldw_str_begin+297
	.data.b	29
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 308
	.data.b	77,69,77,73,70,95,66,85,83,89,0
	.section	.debug_info		;off: 1099
	.data.w	.Ldw_str_begin+308
	.data.b	30
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 319
	.data.b	77,69,77,73,70,95,66,85,83,89,95,73,78,84,69,82,78,65,76,0
	.section	.debug_info		;off: 1108
	.data.w	.Ldw_str_begin+319
	.data.b	31
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 339
	.data.b	77,101,109,73,102,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 1118
	.data.w	.Ldw_str_begin+339
	.data.b	32
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+1070

	.section	.debug_abbrev		;off: 125
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 1129
	.data.b	52
	.section	.debug_str		;off: 356
	.data.b	0
	.section	.debug_info		;off: 1130
	.data.w	.Ldw_str_begin+356
	.data.b	35
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 357
	.data.b	77,69,77,73,70,95,74,79,66,95,79,75,0
	.section	.debug_info		;off: 1140
	.data.w	.Ldw_str_begin+357
	.data.b	36
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 370
	.data.b	77,69,77,73,70,95,74,79,66,95,70,65,73,76,69,68,0
	.section	.debug_info		;off: 1149
	.data.w	.Ldw_str_begin+370
	.data.b	37
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 387
	.data.b	77,69,77,73,70,95,74,79,66,95,80,69,78,68,73,78,71,0
	.section	.debug_info		;off: 1158
	.data.w	.Ldw_str_begin+387
	.data.b	38
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 405
	.data.b	77,69,77,73,70,95,74,79,66,95,67,65,78,67,69,76,69,68,0
	.section	.debug_info		;off: 1167
	.data.w	.Ldw_str_begin+405
	.data.b	39
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 424
	.data.b	77,69,77,73,70,95,66,76,79,67,75,95,73,78,67,79,78,83,73,83,84,69,78,84,0
	.section	.debug_info		;off: 1176
	.data.w	.Ldw_str_begin+424
	.data.b	40
	.data.b	5
	.data.b	5
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 449
	.data.b	77,69,77,73,70,95,66,76,79,67,75,95,73,78,86,65,76,73,68,0
	.section	.debug_info		;off: 1185
	.data.w	.Ldw_str_begin+449
	.data.b	41
	.data.b	5
	.data.b	5
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 469
	.data.b	77,101,109,73,102,95,74,111,98,82,101,115,117,108,116,84,121,112,101,0
	.section	.debug_info		;off: 1195
	.data.w	.Ldw_str_begin+469
	.data.b	42
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+1129

	.data.b	52
	.section	.debug_str		;off: 489
	.data.b	0
	.section	.debug_info		;off: 1207
	.data.w	.Ldw_str_begin+489
	.data.b	45
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 490
	.data.b	77,69,77,73,70,95,77,79,68,69,95,83,76,79,87,0
	.section	.debug_info		;off: 1217
	.data.w	.Ldw_str_begin+490
	.data.b	46
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 506
	.data.b	77,69,77,73,70,95,77,79,68,69,95,70,65,83,84,0
	.section	.debug_info		;off: 1226
	.data.w	.Ldw_str_begin+506
	.data.b	47
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 522
	.data.b	77,101,109,73,102,95,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 1236
	.data.w	.Ldw_str_begin+522
	.data.b	48
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+1206

	.data.b	45
	.section	.debug_str		;off: 537
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1248
	.data.w	.Ldw_str_begin+537
	.data.b	51
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 545
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1260
	.data.w	.Ldw_str_begin+545
	.data.b	56
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 551
	.data.b	115,105,110,116,49,54,0
	.section	.debug_info		;off: 1272
	.data.w	.Ldw_str_begin+551
	.data.b	58
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+356

	.data.b	45
	.section	.debug_str		;off: 558
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1284
	.data.w	.Ldw_str_begin+558
	.data.b	60
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+73

	.data.b	45
	.section	.debug_str		;off: 565
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1296
	.data.w	.Ldw_str_begin+565
	.data.b	64
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 572
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1308
	.data.w	.Ldw_str_begin+572
	.data.b	68
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 579
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1320
	.data.w	.Ldw_str_begin+579
	.data.b	39
	.data.b	15
	.data.b	7
	.data.w	.Ldw_begin+1259

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	7
	.data.b	8
	.data.b	1

	.section	.debug_abbrev		;off: 140
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 1337
	.data.b	40
	.section	.debug_str		;off: 594
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1338
	.data.w	.Ldw_str_begin+594
	.data.b	63
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 155
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

	.section	.debug_info		;off: 1353
	.data.b	40
	.section	.debug_str		;off: 603
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1354
	.data.w	.Ldw_str_begin+603
	.data.b	64
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 612
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1370
	.data.w	.Ldw_str_begin+612
	.data.b	65
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 629
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1386
	.data.w	.Ldw_str_begin+629
	.data.b	66
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 646
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1402
	.data.w	.Ldw_str_begin+646
	.data.b	67
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 663
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1419
	.data.w	.Ldw_str_begin+663
	.data.b	68
	.data.b	2
	.data.b	7
	.data.w	.Ldw_begin+1331

	.data.b	45
	.section	.debug_str		;off: 683
	.data.b	70,101,101,95,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,84,121,112,101,0
	.section	.debug_info		;off: 1431
	.data.w	.Ldw_str_begin+683
	.data.b	46
	.data.b	16
	.data.b	3
	.data.w	.Ldw_begin+130

	.data.b	52
	.section	.debug_str		;off: 707
	.data.b	0
	.section	.debug_info		;off: 1443
	.data.w	.Ldw_str_begin+707
	.data.b	53
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 708
	.data.b	70,69,69,95,80,69,78,68,95,78,79,95,82,69,81,0
	.section	.debug_info		;off: 1453
	.data.w	.Ldw_str_begin+708
	.data.b	55
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 724
	.data.b	70,69,69,95,82,69,65,68,95,82,69,81,0
	.section	.debug_info		;off: 1462
	.data.w	.Ldw_str_begin+724
	.data.b	57
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 737
	.data.b	70,69,69,95,87,82,73,84,69,95,82,69,81,0
	.section	.debug_info		;off: 1471
	.data.w	.Ldw_str_begin+737
	.data.b	59
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 751
	.data.b	70,101,101,95,80,101,110,100,82,101,113,117,101,115,116,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 1481
	.data.w	.Ldw_str_begin+751
	.data.b	60
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1442

	.data.b	52
	.section	.debug_str		;off: 777
	.data.b	0
	.section	.debug_info		;off: 1493
	.data.w	.Ldw_str_begin+777
	.data.b	64
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 778
	.data.b	70,69,69,95,71,67,95,73,68,76,69,0
	.section	.debug_info		;off: 1503
	.data.w	.Ldw_str_begin+778
	.data.b	66
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 790
	.data.b	70,69,69,95,71,67,95,82,69,81,85,69,83,84,69,68,0
	.section	.debug_info		;off: 1512
	.data.w	.Ldw_str_begin+790
	.data.b	68
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 807
	.data.b	70,69,69,95,71,67,95,70,65,73,76,0
	.section	.debug_info		;off: 1521
	.data.w	.Ldw_str_begin+807
	.data.b	70
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 819
	.data.b	70,69,69,95,71,67,95,69,82,65,83,69,95,80,82,69,86,95,66,65,78,75,0
	.section	.debug_info		;off: 1530
	.data.w	.Ldw_str_begin+819
	.data.b	73
	.data.b	5
	.data.b	3
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 842
	.data.b	70,69,69,95,71,67,95,67,79,80,89,95,82,69,65,68,95,78,88,84,80,65,71,69,0
	.section	.debug_info		;off: 1539
	.data.w	.Ldw_str_begin+842
	.data.b	76
	.data.b	5
	.data.b	3
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 867
	.data.b	70,69,69,95,71,67,95,67,79,80,89,95,87,82,73,84,69,0
	.section	.debug_info		;off: 1548
	.data.w	.Ldw_str_begin+867
	.data.b	78
	.data.b	5
	.data.b	3
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 885
	.data.b	70,69,69,95,71,67,95,77,65,82,75,95,66,65,78,75,95,78,69,87,95,86,95,83,80,0
	.section	.debug_info		;off: 1557
	.data.w	.Ldw_str_begin+885
	.data.b	81
	.data.b	5
	.data.b	3
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 911
	.data.b	70,69,69,95,71,67,95,77,65,82,75,95,66,65,78,75,95,78,69,87,95,86,95,77,0
	.section	.debug_info		;off: 1566
	.data.w	.Ldw_str_begin+911
	.data.b	84
	.data.b	5
	.data.b	3
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 936
	.data.b	70,69,69,95,71,67,95,77,65,82,75,95,66,65,78,75,95,79,76,68,95,69,95,83,80,0
	.section	.debug_info		;off: 1575
	.data.w	.Ldw_str_begin+936
	.data.b	87
	.data.b	5
	.data.b	3
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 962
	.data.b	70,69,69,95,71,67,95,77,65,82,75,95,66,65,78,75,95,79,76,68,95,69,95,77,0
	.section	.debug_info		;off: 1584
	.data.w	.Ldw_str_begin+962
	.data.b	90
	.data.b	5
	.data.b	3
	.data.b	9

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 987
	.data.b	70,101,101,95,71,99,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 1594
	.data.w	.Ldw_str_begin+987
	.data.b	91
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1492

	.data.b	52
	.section	.debug_str		;off: 1004
	.data.b	0
	.section	.debug_info		;off: 1606
	.data.w	.Ldw_str_begin+1004
	.data.b	95
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1005
	.data.b	70,69,69,95,77,65,73,78,95,78,79,78,69,0
	.section	.debug_info		;off: 1616
	.data.w	.Ldw_str_begin+1005
	.data.b	97
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1019
	.data.b	70,69,69,95,77,65,73,78,95,73,78,73,84,71,67,0
	.section	.debug_info		;off: 1625
	.data.w	.Ldw_str_begin+1019
	.data.b	99
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1035
	.data.b	70,69,69,95,77,65,73,78,95,71,67,0
	.section	.debug_info		;off: 1634
	.data.w	.Ldw_str_begin+1035
	.data.b	101
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1047
	.data.b	70,69,69,95,77,65,73,78,95,82,69,65,68,0
	.section	.debug_info		;off: 1643
	.data.w	.Ldw_str_begin+1047
	.data.b	103
	.data.b	5
	.data.b	3
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1061
	.data.b	70,69,69,95,77,65,73,78,95,87,82,73,84,69,0
	.section	.debug_info		;off: 1652
	.data.w	.Ldw_str_begin+1061
	.data.b	105
	.data.b	5
	.data.b	3
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1076
	.data.b	70,101,101,95,77,97,105,110,74,111,98,84,121,112,101,0
	.section	.debug_info		;off: 1662
	.data.w	.Ldw_str_begin+1076
	.data.b	106
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1605

	.data.b	52
	.section	.debug_str		;off: 1092
	.data.b	0
	.section	.debug_info		;off: 1674
	.data.w	.Ldw_str_begin+1092
	.data.b	110
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1093
	.data.b	70,69,69,95,74,79,66,95,73,68,76,69,0
	.section	.debug_info		;off: 1684
	.data.w	.Ldw_str_begin+1093
	.data.b	112
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1106
	.data.b	70,69,69,95,74,79,66,95,82,69,81,83,84,68,0
	.section	.debug_info		;off: 1693
	.data.w	.Ldw_str_begin+1106
	.data.b	114
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1121
	.data.b	70,69,69,95,74,79,66,95,68,79,78,69,0
	.section	.debug_info		;off: 1702
	.data.w	.Ldw_str_begin+1121
	.data.b	116
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1134
	.data.b	70,69,69,95,74,79,66,95,70,65,73,76,69,68,0
	.section	.debug_info		;off: 1711
	.data.w	.Ldw_str_begin+1134
	.data.b	118
	.data.b	5
	.data.b	3
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1149
	.data.b	70,101,101,95,74,111,98,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 1721
	.data.w	.Ldw_str_begin+1149
	.data.b	119
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1673

	.data.b	52
	.section	.debug_str		;off: 1166
	.data.b	0
	.section	.debug_info		;off: 1733
	.data.w	.Ldw_str_begin+1166
	.data.b	123
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1167
	.data.b	70,69,69,95,78,79,95,69,82,82,79,82,0
	.section	.debug_info		;off: 1743
	.data.w	.Ldw_str_begin+1167
	.data.b	125
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1180
	.data.b	70,69,69,95,71,67,95,87,82,73,84,69,0
	.section	.debug_info		;off: 1752
	.data.w	.Ldw_str_begin+1180
	.data.b	127
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1193
	.data.b	70,69,69,95,71,67,95,82,69,65,68,0
	.section	.debug_info		;off: 1761
	.data.w	.Ldw_str_begin+1193
	.data.b	129,1
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1205
	.data.b	70,69,69,95,71,67,95,69,82,65,83,69,0
	.section	.debug_info		;off: 1771
	.data.w	.Ldw_str_begin+1205
	.data.b	131,1
	.data.b	5
	.data.b	3
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1218
	.data.b	70,69,69,95,71,67,95,70,76,83,0
	.section	.debug_info		;off: 1781
	.data.w	.Ldw_str_begin+1218
	.data.b	133,1
	.data.b	5
	.data.b	3
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1229
	.data.b	70,69,69,95,71,67,95,84,82,73,71,0
	.section	.debug_info		;off: 1791
	.data.w	.Ldw_str_begin+1229
	.data.b	135,1
	.data.b	5
	.data.b	3
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1241
	.data.b	70,101,101,95,74,111,98,69,114,114,111,114,84,121,112,101,0
	.section	.debug_info		;off: 1802
	.data.w	.Ldw_str_begin+1241
	.data.b	136,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1732

	.data.b	71
	.data.b	143,1
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1258
	.data.b	86,97,108,105,100,0
	.section	.debug_info		;off: 1822
	.data.w	.Ldw_str_begin+1258
	.data.b	146,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1264
	.data.b	67,111,110,115,105,115,116,101,110,116,0
	.section	.debug_info		;off: 1839
	.data.w	.Ldw_str_begin+1264
	.data.b	147,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1275
	.data.b	67,111,112,105,101,100,0
	.section	.debug_info		;off: 1856
	.data.w	.Ldw_str_begin+1275
	.data.b	148,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1282
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 1873
	.data.w	.Ldw_str_begin+1282
	.data.b	149,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1294
	.data.b	80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 1890
	.data.w	.Ldw_str_begin+1294
	.data.b	150,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1304
	.data.b	65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 1907
	.data.w	.Ldw_str_begin+1304
	.data.b	151,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1312
	.data.b	66,108,111,99,107,67,121,99,108,101,67,111,117,110,116,0
	.section	.debug_info		;off: 1924
	.data.w	.Ldw_str_begin+1312
	.data.b	152,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1328
	.data.b	70,101,101,95,66,108,111,99,107,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1942
	.data.w	.Ldw_str_begin+1328
	.data.b	153,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1814

	.data.b	71
	.data.b	156,1
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1346
	.data.b	84,97,103,0
	.section	.debug_info		;off: 1962
	.data.w	.Ldw_str_begin+1346
	.data.b	157,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1350
	.data.b	66,97,100,83,101,99,116,111,114,78,117,109,0
	.section	.debug_info		;off: 1979
	.data.w	.Ldw_str_begin+1350
	.data.b	160,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1363
	.data.b	82,101,115,101,114,118,101,100,0
	.section	.debug_info		;off: 1996
	.data.w	.Ldw_str_begin+1363
	.data.b	161,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+627
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1372
	.data.b	84,97,105,108,84,97,103,0
	.section	.debug_info		;off: 2013
	.data.w	.Ldw_str_begin+1372
	.data.b	162,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	15
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1380
	.data.b	70,101,101,95,69,114,97,115,101,80,97,103,101,72,101,97,100,101,114,84,121,112,101,0
	.section	.debug_info		;off: 2031
	.data.w	.Ldw_str_begin+1380
	.data.b	163,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1954

	.data.b	71
	.data.b	166,1
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1404
	.data.b	84,97,103,0
	.section	.debug_info		;off: 2051
	.data.w	.Ldw_str_begin+1404
	.data.b	167,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1408
	.data.b	82,101,115,101,114,118,101,100,95,48,0
	.section	.debug_info		;off: 2068
	.data.w	.Ldw_str_begin+1408
	.data.b	170,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1419
	.data.b	83,116,97,116,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2085
	.data.w	.Ldw_str_begin+1419
	.data.b	171,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1430
	.data.b	71,99,78,117,109,98,101,114,0
	.section	.debug_info		;off: 2102
	.data.w	.Ldw_str_begin+1430
	.data.b	172,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1439
	.data.b	82,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2119
	.data.w	.Ldw_str_begin+1439
	.data.b	173,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+643
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1450
	.data.b	84,97,105,108,84,97,103,0
	.section	.debug_info		;off: 2136
	.data.w	.Ldw_str_begin+1450
	.data.b	174,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	15
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1458
	.data.b	70,101,101,95,86,97,108,105,100,80,97,103,101,72,101,97,100,101,114,84,121,112,101,0
	.section	.debug_info		;off: 2154
	.data.w	.Ldw_str_begin+1458
	.data.b	175,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2043

	.data.b	71
	.data.b	178,1
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1482
	.data.b	84,97,103,0
	.section	.debug_info		;off: 2174
	.data.w	.Ldw_str_begin+1482
	.data.b	179,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1486
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 2191
	.data.w	.Ldw_str_begin+1486
	.data.b	180,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+659
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1498
	.data.b	66,108,111,99,107,67,121,99,108,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2208
	.data.w	.Ldw_str_begin+1498
	.data.b	181,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+675
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1514
	.data.b	80,97,103,101,115,65,110,100,86,97,108,105,100,0
	.section	.debug_info		;off: 2225
	.data.w	.Ldw_str_begin+1514
	.data.b	183,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1528
	.data.b	70,101,101,95,66,108,111,99,107,72,101,97,100,101,114,84,121,112,101,0
	.section	.debug_info		;off: 2243
	.data.w	.Ldw_str_begin+1528
	.data.b	184,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2166

	.data.b	71
	.data.b	187,1
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1548
	.data.b	84,97,103,0
	.section	.debug_info		;off: 2263
	.data.w	.Ldw_str_begin+1548
	.data.b	188,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1552
	.data.b	80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2280
	.data.w	.Ldw_str_begin+1552
	.data.b	189,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1562
	.data.b	80,97,103,101,67,111,117,110,116,82,101,118,0
	.section	.debug_info		;off: 2297
	.data.w	.Ldw_str_begin+1562
	.data.b	190,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1575
	.data.b	82,101,115,101,114,118,101,100,0
	.section	.debug_info		;off: 2314
	.data.w	.Ldw_str_begin+1575
	.data.b	191,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+691
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1584
	.data.b	84,97,105,108,84,97,103,0
	.section	.debug_info		;off: 2331
	.data.w	.Ldw_str_begin+1584
	.data.b	192,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	14
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1592
	.data.b	70,101,101,95,66,108,111,99,107,77,97,114,107,101,114,84,121,112,101,0
	.section	.debug_info		;off: 2349
	.data.w	.Ldw_str_begin+1592
	.data.b	193,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2255

	.data.b	71
	.data.b	197,1
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1612
	.data.b	82,101,109,97,105,110,0
	.section	.debug_info		;off: 2369
	.data.w	.Ldw_str_begin+1612
	.data.b	198,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1619
	.data.b	82,101,115,117,109,101,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 2386
	.data.w	.Ldw_str_begin+1619
	.data.b	199,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+292
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1635
	.data.b	82,101,115,117,109,101,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 2403
	.data.w	.Ldw_str_begin+1635
	.data.b	200,1
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1649
	.data.b	70,101,101,95,83,116,97,116,117,115,83,107,105,112,82,101,97,100,84,121,112,101,0
	.section	.debug_info		;off: 2421
	.data.w	.Ldw_str_begin+1649
	.data.b	201,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2361

	.data.b	71
	.data.b	206,1
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1672
	.data.b	78,101,120,116,70,114,101,101,65,100,100,114,0
	.section	.debug_info		;off: 2441
	.data.w	.Ldw_str_begin+1672
	.data.b	208,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1685
	.data.b	85,110,101,114,97,115,97,98,108,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2458
	.data.w	.Ldw_str_begin+1685
	.data.b	210,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1701
	.data.b	85,110,101,114,97,115,97,98,108,101,83,101,99,116,111,114,78,117,109,0
	.section	.debug_info		;off: 2475
	.data.w	.Ldw_str_begin+1701
	.data.b	213,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+707
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1721
	.data.b	83,116,97,116,101,0
	.section	.debug_info		;off: 2492
	.data.w	.Ldw_str_begin+1721
	.data.b	216,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	7
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1727
	.data.b	83,116,97,116,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2509
	.data.w	.Ldw_str_begin+1727
	.data.b	218,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1738
	.data.b	71,99,78,117,109,98,101,114,0
	.section	.debug_info		;off: 2526
	.data.w	.Ldw_str_begin+1738
	.data.b	220,1
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1747
	.data.b	70,101,101,95,66,97,110,107,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 2544
	.data.w	.Ldw_str_begin+1747
	.data.b	221,1
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2433

	.data.b	71
	.data.b	225,1
	.data.b	1
	.data.b	3
	.data.b	60
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1764
	.data.b	80,101,110,100,82,101,113,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2564
	.data.w	.Ldw_str_begin+1764
	.data.b	227,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1480
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1778
	.data.b	70,101,101,83,101,116,77,111,100,101,82,101,113,80,101,110,100,0
	.section	.debug_info		;off: 2581
	.data.w	.Ldw_str_begin+1778
	.data.b	229,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1796
	.data.b	77,111,100,101,0
	.section	.debug_info		;off: 2598
	.data.w	.Ldw_str_begin+1796
	.data.b	231,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1235
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1801
	.data.b	66,108,111,99,107,73,110,118,97,108,105,100,82,101,113,0
	.section	.debug_info		;off: 2615
	.data.w	.Ldw_str_begin+1801
	.data.b	233,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1817
	.data.b	87,97,105,116,71,99,0
	.section	.debug_info		;off: 2632
	.data.w	.Ldw_str_begin+1817
	.data.b	235,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	13
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1824
	.data.b	82,101,97,100,68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 2649
	.data.w	.Ldw_str_begin+1824
	.data.b	237,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+292
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1842
	.data.b	87,114,105,116,101,68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 2666
	.data.w	.Ldw_str_begin+1842
	.data.b	239,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+249
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1861
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 2683
	.data.w	.Ldw_str_begin+1861
	.data.b	241,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1873
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 2700
	.data.w	.Ldw_str_begin+1873
	.data.b	243,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	26
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1884
	.data.b	66,108,111,99,107,79,102,102,115,101,116,0
	.section	.debug_info		;off: 2717
	.data.w	.Ldw_str_begin+1884
	.data.b	245,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1896
	.data.b	67,117,114,114,66,97,110,107,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 2734
	.data.w	.Ldw_str_begin+1896
	.data.b	247,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1912
	.data.b	76,101,110,103,116,104,0
	.section	.debug_info		;off: 2751
	.data.w	.Ldw_str_begin+1912
	.data.b	249,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1919
	.data.b	76,97,115,116,87,114,105,116,101,83,105,122,101,0
	.section	.debug_info		;off: 2768
	.data.w	.Ldw_str_begin+1919
	.data.b	251,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	38
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1933
	.data.b	76,97,115,116,82,101,97,100,83,105,122,101,0
	.section	.debug_info		;off: 2785
	.data.w	.Ldw_str_begin+1933
	.data.b	253,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1946
	.data.b	66,108,111,99,107,80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2802
	.data.w	.Ldw_str_begin+1946
	.data.b	255,1
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	42
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1961
	.data.b	66,108,111,99,107,80,97,103,101,115,0
	.section	.debug_info		;off: 2819
	.data.w	.Ldw_str_begin+1961
	.data.b	129,2
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1972
	.data.b	85,115,101,114,87,114,105,116,101,66,121,116,101,115,67,111,117,110,116,0
	.section	.debug_info		;off: 2836
	.data.w	.Ldw_str_begin+1972
	.data.b	131,2
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	46
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1992
	.data.b	74,111,98,82,101,115,117,108,116,0
	.section	.debug_info		;off: 2853
	.data.w	.Ldw_str_begin+1992
	.data.b	133,2
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1194
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2002
	.data.b	74,111,98,82,101,115,117,108,116,80,101,110,100,105,110,103,0
	.section	.debug_info		;off: 2870
	.data.w	.Ldw_str_begin+2002
	.data.b	135,2
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1194
	.data.b	2,35
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2019
	.data.b	70,108,115,74,111,98,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2887
	.data.w	.Ldw_str_begin+2019
	.data.b	137,2
	.data.b	31
	.data.b	3
	.data.w	.Ldw_begin+1720
	.data.b	2,35
	.data.b	56
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2032
	.data.b	70,101,101,95,85,115,101,114,74,111,98,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 2905
	.data.w	.Ldw_str_begin+2032
	.data.b	138,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2556

	.data.b	71
	.data.b	142,2
	.data.b	1
	.data.b	3
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2052
	.data.b	71,99,83,116,97,116,101,0
	.section	.debug_info		;off: 2925
	.data.w	.Ldw_str_begin+2052
	.data.b	144,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1593
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2060
	.data.b	71,99,68,101,115,116,65,100,100,114,0
	.section	.debug_info		;off: 2942
	.data.w	.Ldw_str_begin+2060
	.data.b	146,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2071
	.data.b	71,99,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 2959
	.data.w	.Ldw_str_begin+2071
	.data.b	148,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2081
	.data.b	71,67,67,111,112,121,73,110,100,101,120,0
	.section	.debug_info		;off: 2976
	.data.w	.Ldw_str_begin+2081
	.data.b	150,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1271
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2093
	.data.b	71,99,67,117,114,114,66,108,111,99,107,80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 2993
	.data.w	.Ldw_str_begin+2093
	.data.b	152,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	14
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2114
	.data.b	76,97,115,116,87,114,105,116,101,83,105,122,101,0
	.section	.debug_info		;off: 3010
	.data.w	.Ldw_str_begin+2114
	.data.b	154,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2128
	.data.b	76,97,115,116,82,101,97,100,83,105,122,101,0
	.section	.debug_info		;off: 3027
	.data.w	.Ldw_str_begin+2128
	.data.b	156,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	18
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2141
	.data.b	66,108,111,99,107,80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 3044
	.data.w	.Ldw_str_begin+2141
	.data.b	158,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2156
	.data.b	66,108,111,99,107,77,111,100,105,102,105,101,100,0
	.section	.debug_info		;off: 3061
	.data.w	.Ldw_str_begin+2156
	.data.b	160,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	22
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2170
	.data.b	70,108,115,74,111,98,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3078
	.data.w	.Ldw_str_begin+2170
	.data.b	162,2
	.data.b	22
	.data.b	3
	.data.w	.Ldw_begin+1720
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2183
	.data.b	70,101,101,95,71,99,74,111,98,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 3096
	.data.w	.Ldw_str_begin+2183
	.data.b	163,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+2917

	.data.b	71
	.data.b	167,2
	.data.b	1
	.data.b	3
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2201
	.data.b	67,117,114,114,66,97,110,107,0
	.section	.debug_info		;off: 3116
	.data.w	.Ldw_str_begin+2201
	.data.b	169,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2210
	.data.b	73,110,116,114,74,111,98,70,97,105,108,67,111,117,110,116,0
	.section	.debug_info		;off: 3133
	.data.w	.Ldw_str_begin+2210
	.data.b	172,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2227
	.data.b	70,101,101,87,114,105,116,101,65,80,73,67,97,108,108,101,100,0
	.section	.debug_info		;off: 3150
	.data.w	.Ldw_str_begin+2227
	.data.b	174,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2245
	.data.b	77,97,105,110,74,111,98,0
	.section	.debug_info		;off: 3167
	.data.w	.Ldw_str_begin+2245
	.data.b	176,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1661
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2253
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 3184
	.data.w	.Ldw_str_begin+2253
	.data.b	178,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+177
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2265
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 3201
	.data.w	.Ldw_str_begin+2265
	.data.b	180,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+226
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2278
	.data.b	85,110,99,102,103,66,108,107,115,69,120,99,101,101,100,101,100,0
	.section	.debug_info		;off: 3218
	.data.w	.Ldw_str_begin+2278
	.data.b	182,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1259
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2296
	.data.b	85,110,67,111,110,102,105,103,66,108,111,99,107,67,111,117,110,116,0
	.section	.debug_info		;off: 3235
	.data.w	.Ldw_str_begin+2296
	.data.b	184,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	18
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2315
	.data.b	78,101,120,116,70,114,101,101,80,97,103,101,65,100,100,114,0
	.section	.debug_info		;off: 3252
	.data.w	.Ldw_str_begin+2315
	.data.b	186,2
	.data.b	24
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2332
	.data.b	70,101,101,95,83,116,97,116,101,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 3270
	.data.w	.Ldw_str_begin+2332
	.data.b	187,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+3108

	.data.b	71
	.data.b	192,2
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2350
	.data.b	78,117,109,98,101,114,79,102,87,114,105,116,101,67,121,99,108,101,115,0
	.section	.debug_info		;off: 3290
	.data.w	.Ldw_str_begin+2350
	.data.b	194,2
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1295
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2370
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 3307
	.data.w	.Ldw_str_begin+2370
	.data.b	196,2
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2382
	.data.b	66,108,111,99,107,83,105,122,101,0
	.section	.debug_info		;off: 3324
	.data.w	.Ldw_str_begin+2382
	.data.b	198,2
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2392
	.data.b	73,109,109,101,100,105,97,116,101,68,97,116,97,0
	.section	.debug_info		;off: 3341
	.data.w	.Ldw_str_begin+2392
	.data.b	200,2
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1247
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2406
	.data.b	70,101,101,95,66,108,111,99,107,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3359
	.data.w	.Ldw_str_begin+2406
	.data.b	201,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+3282

	.data.b	71
	.data.b	205,2
	.data.b	1
	.data.b	3
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2426
	.data.b	70,101,101,66,108,107,67,110,116,0
	.section	.debug_info		;off: 3379
	.data.w	.Ldw_str_begin+2426
	.data.b	207,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2436
	.data.b	70,101,101,66,108,111,99,107,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3396
	.data.w	.Ldw_str_begin+2436
	.data.b	209,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+113
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2454
	.data.b	70,101,101,74,111,98,69,110,100,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3413
	.data.w	.Ldw_str_begin+2454
	.data.b	210,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1430
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2479
	.data.b	70,101,101,74,111,98,69,114,114,111,114,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3430
	.data.w	.Ldw_str_begin+2479
	.data.b	211,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1430
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2506
	.data.b	70,101,101,85,110,97,118,97,105,108,97,98,108,101,70,97,105,108,117,114,101,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3447
	.data.w	.Ldw_str_begin+2506
	.data.b	212,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1430
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2543
	.data.b	70,101,101,68,105,115,99,111,118,101,114,78,111,110,69,114,97,115,97,98,108,101,65,114,101,97,115,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3464
	.data.w	.Ldw_str_begin+2543
	.data.b	213,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1430
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2586
	.data.b	70,101,101,78,111,116,70,111,117,110,100,77,97,110,97,103,101,109,101,110,116,73,110,102,111,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 3481
	.data.w	.Ldw_str_begin+2586
	.data.b	214,2
	.data.b	32
	.data.b	3
	.data.w	.Ldw_begin+1430
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2627
	.data.b	70,101,101,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3499
	.data.w	.Ldw_str_begin+2627
	.data.b	215,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+3371

	.data.b	73
	.data.b	222,2
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.section	.debug_abbrev		;off: 174
	.data.b	73
	.data.b	23
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 3518
	.data.b	40
	.section	.debug_str		;off: 2642
	.data.b	66,117,102,102,101,114,0
	.section	.debug_info		;off: 3519
	.data.w	.Ldw_str_begin+2642
	.data.b	223,2
	.data.b	12
	.data.b	3
	.data.w	.Ldw_begin+723
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2649
	.data.b	86,97,108,105,100,72,101,97,100,101,114,0
	.section	.debug_info		;off: 3536
	.data.w	.Ldw_str_begin+2649
	.data.b	224,2
	.data.b	29
	.data.b	3
	.data.w	.Ldw_begin+2153
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2661
	.data.b	66,108,111,99,107,72,101,97,100,101,114,0
	.section	.debug_info		;off: 3553
	.data.w	.Ldw_str_begin+2661
	.data.b	225,2
	.data.b	25
	.data.b	3
	.data.w	.Ldw_begin+2242
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2673
	.data.b	70,101,101,95,66,117,102,102,101,114,85,110,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 3571
	.data.w	.Ldw_str_begin+2673
	.data.b	226,2
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+3511

	.data.b	52
	.section	.debug_str		;off: 2693
	.data.b	0
	.section	.debug_info		;off: 3584
	.data.w	.Ldw_str_begin+2693
	.data.b	36
	.data.b	1
	.data.b	18
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2694
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 3594
	.data.w	.Ldw_str_begin+2694
	.data.b	37
	.data.b	5
	.data.b	18
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2711
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 3603
	.data.w	.Ldw_str_begin+2711
	.data.b	38
	.data.b	5
	.data.b	18
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2728
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 3612
	.data.w	.Ldw_str_begin+2728
	.data.b	39
	.data.b	5
	.data.b	18
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2745
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 3621
	.data.w	.Ldw_str_begin+2745
	.data.b	40
	.data.b	5
	.data.b	18
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2762
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 3630
	.data.w	.Ldw_str_begin+2762
	.data.b	41
	.data.b	5
	.data.b	18
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2779
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 3640
	.data.w	.Ldw_str_begin+2779
	.data.b	42
	.data.b	3
	.data.b	18
	.data.w	.Ldw_begin+3583

	.data.b	45
	.section	.debug_str		;off: 2791
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 3652
	.data.w	.Ldw_str_begin+2791
	.data.b	32
	.data.b	21
	.data.b	17
	.data.w	.Ldw_begin+3639

	.data.b	45
	.section	.debug_str		;off: 2805
	.data.b	70,108,115,95,65,100,100,114,101,115,115,84,121,112,101,0
	.section	.debug_info		;off: 3664
	.data.w	.Ldw_str_begin+2805
	.data.b	47
	.data.b	16
	.data.b	39
	.data.w	.Ldw_begin+1295

	.data.b	45
	.section	.debug_str		;off: 2821
	.data.b	70,108,115,95,76,101,110,103,116,104,84,121,112,101,0
	.section	.debug_info		;off: 3676
	.data.w	.Ldw_str_begin+2821
	.data.b	50
	.data.b	16
	.data.b	39
	.data.w	.Ldw_begin+1295

	.data.b	6
	.section	.debug_str		;off: 2836
	.data.b	70,101,101,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3688
	.data.w	.Ldw_str_begin+2836
	.data.b	146,2
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+460
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.section	.debug_abbrev		;off: 189
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

	.section	.debug_info		;off: 3708
	.data.b	6
	.section	.debug_str		;off: 2850
	.data.b	70,101,101,95,71,99,74,111,98,73,110,102,111,0
	.section	.debug_info		;off: 3709
	.data.w	.Ldw_str_begin+2850
	.data.b	149,2
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+3095
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_GcJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2864
	.data.b	70,101,101,95,85,115,101,114,74,111,98,73,110,102,111,0
	.section	.debug_info		;off: 3730
	.data.w	.Ldw_str_begin+2864
	.data.b	152,2
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+2904
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_UserJobInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2880
	.data.b	70,101,101,95,66,97,110,107,73,110,102,111,0
	.section	.debug_info		;off: 3751
	.data.w	.Ldw_str_begin+2880
	.data.b	156,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+746
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_BankInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2893
	.data.b	70,101,101,95,83,116,97,116,101,0
	.section	.debug_info		;off: 3772
	.data.w	.Ldw_str_begin+2893
	.data.b	159,2
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+3269
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_State..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2903
	.data.b	70,101,101,95,66,108,111,99,107,73,110,102,111,115,0
	.section	.debug_info		;off: 3793
	.data.w	.Ldw_str_begin+2903
	.data.b	162,2
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+778
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_BlockInfos..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2918
	.data.b	70,101,101,95,83,107,105,112,82,101,97,100,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3814
	.data.w	.Ldw_str_begin+2918
	.data.b	165,2
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+2420
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_SkipReadStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2937
	.data.b	70,101,101,95,82,87,66,117,102,102,101,114,0
	.section	.debug_info		;off: 3835
	.data.w	.Ldw_str_begin+2937
	.data.b	168,2
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+802
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_RWBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2950
	.data.b	70,101,101,95,83,101,99,116,111,114,82,101,77,97,112,0
	.section	.debug_info		;off: 3856
	.data.w	.Ldw_str_begin+2950
	.data.b	202,2
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+820
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_SectorReMap..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	6
	.section	.debug_str		;off: 2966
	.data.b	70,101,101,95,73,110,105,116,95,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3877
	.data.w	.Ldw_str_begin+2966
	.data.b	205,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Fee_Init_Status..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.

	.data.b	27
	.section	.debug_str		;off: 2982
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 3898
	.data.w	.Ldw_str_begin+2982
	.data.b	63
	.data.b	31
	.data.b	18
	.data.w	.Ldw_begin+3639
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 210
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

	.section	.debug_info		;off: 3915
	.data.b	37

	.section	.debug_abbrev		;off: 237
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 3916
	.data.b	8
	.section	.debug_str		;off: 3002
	.data.b	105,100,0
	.section	.debug_info		;off: 3917
	.data.w	.Ldw_str_begin+3002
	.data.b	65
	.data.b	17
	.data.b	18
	.data.w	.Ldw_begin+3639
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 242
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

	.section	.debug_info		;off: 3930
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3005
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 3933
	.data.w	.Ldw_str_begin+3005
	.data.b	105
	.data.b	39
	.data.b	14
	.data.w	.Ldw_begin+1319
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3021
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 3952
	.data.w	.Ldw_str_begin+3021
	.data.b	113
	.data.b	39
	.data.b	14
	.data.w	.Ldw_begin+1319
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3044
	.data.b	70,108,115,95,69,114,97,115,101,0
	.section	.debug_info		;off: 3971
	.data.w	.Ldw_str_begin+3044
	.data.b	164,1
	.data.b	46
	.data.b	38
	.data.w	.Ldw_begin+1319
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3054
	.data.b	70,108,115,95,87,114,105,116,101,0
	.section	.debug_info		;off: 3991
	.data.w	.Ldw_str_begin+3054
	.data.b	171,1
	.data.b	46
	.data.b	38
	.data.w	.Ldw_begin+1319
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3064
	.data.b	70,108,115,95,67,97,110,99,101,108,0
	.section	.debug_info		;off: 4011
	.data.w	.Ldw_str_begin+3064
	.data.b	188,1
	.data.b	36
	.data.b	38
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 261
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

	.section	.debug_info		;off: 4025
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3075
	.data.b	70,108,115,95,83,101,116,77,111,100,101,0
	.section	.debug_info		;off: 4027
	.data.w	.Ldw_str_begin+3075
	.data.b	195,1
	.data.b	36
	.data.b	38
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3087
	.data.b	70,108,115,95,82,101,97,100,0
	.section	.debug_info		;off: 4043
	.data.w	.Ldw_str_begin+3087
	.data.b	207,1
	.data.b	47
	.data.b	38
	.data.w	.Ldw_begin+1319
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3096
	.data.b	70,108,115,95,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 4063
	.data.w	.Ldw_str_begin+3096
	.data.b	224,1
	.data.b	48
	.data.b	38
	.data.w	.Ldw_begin+1117
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3110
	.data.b	70,108,115,95,82,101,97,100,87,111,114,100,115,83,121,110,99,0
	.section	.debug_info		;off: 4083
	.data.w	.Ldw_str_begin+3110
	.data.b	237,1
	.data.b	37
	.data.b	38
	.data.w	.Ldw_begin+1259
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3128
	.data.b	70,108,115,95,67,111,109,112,97,114,101,87,111,114,100,115,83,121,110,99,0
	.section	.debug_info		;off: 4103
	.data.w	.Ldw_str_begin+3128
	.data.b	245,1
	.data.b	37
	.data.b	38
	.data.w	.Ldw_begin+1259
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3149
	.data.b	70,108,115,95,66,108,97,110,107,67,104,101,99,107,83,121,110,99,0
	.section	.debug_info		;off: 4123
	.data.w	.Ldw_str_begin+3149
	.data.b	252,1
	.data.b	37
	.data.b	38
	.data.w	.Ldw_begin+1259
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3168
	.data.b	70,101,101,95,76,111,99,97,108,77,97,107,101,66,108,111,99,107,77,97,114,107,101,114,0
	.section	.debug_info		;off: 4143
	.data.w	.Ldw_str_begin+3168
	.data.b	144,4
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalMakeBlockMarker
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

	.section	.debug_abbrev		;off: 286
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
	.data.w	Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalMakeBlockMarker-Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1981
	.data.b	0,5,2
	.data.w	Fee_LocalMakeBlockMarker..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	151,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	27
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	77
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4172
	.data.b	22
	.section	.debug_str		;off: 3193
	.data.b	66,108,111,99,107,77,97,114,107,101,114,80,116,114,0
	.section	.debug_info		;off: 4173
	.data.w	.Ldw_str_begin+3193
	.data.b	146,4
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+68
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

	.section	.debug_abbrev		;off: 332
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

	.section	.debug_info		;off: 4190
	.data.b	22
	.section	.debug_str		;off: 3208
	.data.b	80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 4191
	.data.w	.Ldw_str_begin+3208
	.data.b	147,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4208
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 351
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 4217
	.data.b	8
	.section	.debug_str		;off: 3218
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 4218
	.data.w	.Ldw_str_begin+3218
	.data.b	150,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3224
	.data.b	70,101,101,95,76,111,99,97,108,71,101,116,85,115,114,66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 4235
	.data.w	.Ldw_str_begin+3224
	.data.b	185,4
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.w	Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGetUsrBlockIndex
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

	.section	.debug_abbrev		;off: 360
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGetUsrBlockIndex-Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2012
	.data.b	0,5,2
	.data.w	Fee_LocalGetUsrBlockIndex..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	192,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	60
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	123
	.data.b	13
	.data.b	11
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
	.section	.debug_info		;off: 4268
	.data.b	22
	.section	.debug_str		;off: 3250
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4269
	.data.w	.Ldw_str_begin+3250
	.data.b	187,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4286
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 3262
	.data.b	66,108,111,99,107,80,116,114,0
	.section	.debug_info		;off: 4296
	.data.w	.Ldw_str_begin+3262
	.data.b	190,4
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+113
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 408
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

	.section	.debug_info		;off: 4314
	.data.b	7
	.section	.debug_str		;off: 3271
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 4315
	.data.w	.Ldw_str_begin+3271
	.data.b	191,4
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4333
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3277
	.data.b	70,101,101,95,76,111,99,97,108,72,97,110,100,108,101,85,115,114,74,111,98,69,110,100,0
	.section	.debug_info		;off: 4336
	.data.w	.Ldw_str_begin+3277
	.data.b	234,4
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalHandleUsrJobEnd
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalHandleUsrJobEnd-Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2051
	.data.b	0,5,2
	.data.w	Fee_LocalHandleUsrJobEnd..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	237,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
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
	.data.b	59
	.data.b	27
	.data.b	27
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4365
	.data.b	22
	.section	.debug_str		;off: 3302
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 4366
	.data.w	.Ldw_str_begin+3302
	.data.b	236,4
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1194
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4383
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 3308
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 4393
	.data.w	.Ldw_str_begin+3308
	.data.b	239,4
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1430
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4411
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3324
	.data.b	70,101,101,95,76,111,99,97,108,68,101,99,105,100,101,77,97,105,110,74,111,98,0
	.section	.debug_info		;off: 4414
	.data.w	.Ldw_str_begin+3324
	.data.b	161,5
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalDecideMainJob
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

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalDecideMainJob-Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2101
	.data.b	0,5,2
	.data.w	Fee_LocalDecideMainJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	164,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	38
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	11
	.data.b	60
	.data.b	59
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	82
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	47
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	68
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	61
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	61
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	61
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	27
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	69
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	12
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
	.section	.debug_info		;off: 4443
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3347
	.data.b	70,101,101,95,76,111,99,97,108,83,101,116,73,110,105,116,71,99,0
	.section	.debug_info		;off: 4455
	.data.w	.Ldw_str_begin+3347
	.data.b	148,6
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalSetInitGc
	.data.b	1
	.data.b	93
	.data.b	240,143,1
	.data.b	100
	.data.b	0
	.data.b	36
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
	.data.w	Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalSetInitGc-Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2247
	.data.b	0,5,2
	.data.w	Fee_LocalSetInitGc..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	151,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	27
	.data.b	43
	.data.b	44
	.data.b	75
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	12
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	91
	.data.b	28
	.data.b	59
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	27
	.data.b	29
	.data.b	59
	.data.b	27
	.data.b	59
	.data.b	27
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	75
	.data.b	43
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 4486
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 3366
	.data.b	66,97,110,107,48,83,116,97,116,101,0
	.section	.debug_info		;off: 4496
	.data.w	.Ldw_str_begin+3366
	.data.b	153,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+133
	.section	.debug_loc		;off: 133
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4514
	.data.b	7
	.section	.debug_str		;off: 3377
	.data.b	66,97,110,107,49,83,116,97,116,101,0
	.section	.debug_info		;off: 4515
	.data.w	.Ldw_str_begin+3377
	.data.b	154,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+152
	.section	.debug_loc		;off: 152
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4533
	.data.b	7
	.section	.debug_str		;off: 3388
	.data.b	66,97,115,101,65,100,100,114,0
	.section	.debug_info		;off: 4534
	.data.w	.Ldw_str_begin+3388
	.data.b	155,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+148
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+171
	.section	.debug_loc		;off: 171
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4552
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3397
	.data.b	70,101,101,95,76,111,99,97,108,67,104,101,99,107,69,114,97,115,101,83,116,97,116,101,80,97,103,101,0
	.section	.debug_info		;off: 4555
	.data.w	.Ldw_str_begin+3397
	.data.b	181,7
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.w	Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalCheckEraseStatePage
	.data.b	1
	.data.b	93
	.data.b	240,143,1
	.data.b	100
	.data.b	0
	.data.b	44
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
	.data.w	Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalCheckEraseStatePage-Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2370
	.data.b	0,5,2
	.data.w	Fee_LocalCheckEraseStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	184,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	91
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	109
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	28
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 4590
	.data.b	22
	.section	.debug_str		;off: 3426
	.data.b	67,117,114,114,66,97,110,107,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 4591
	.data.w	.Ldw_str_begin+3426
	.data.b	183,7
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.w	.Ldw_loc_begin+191
	.section	.debug_loc		;off: 191
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	80
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4608
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 3442
	.data.b	83,116,97,116,101,0
	.section	.debug_info		;off: 4618
	.data.w	.Ldw_str_begin+3442
	.data.b	186,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+221
	.section	.debug_loc		;off: 221
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4636
	.data.b	7
	.section	.debug_str		;off: 3448
	.data.b	82,101,116,117,114,110,86,97,108,0
	.section	.debug_info		;off: 4637
	.data.w	.Ldw_str_begin+3448
	.data.b	187,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+240
	.section	.debug_loc		;off: 240
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4655
	.data.b	8
	.section	.debug_str		;off: 3458
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 4656
	.data.w	.Ldw_str_begin+3458
	.data.b	188,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3464
	.data.b	66,97,110,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4671
	.data.w	.Ldw_str_begin+3464
	.data.b	189,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+259
	.section	.debug_loc		;off: 259
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4689
	.data.b	8
	.section	.debug_str		;off: 3475
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 4690
	.data.w	.Ldw_str_begin+3475
	.data.b	190,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3481
	.data.b	78,111,114,109,97,108,83,101,99,116,111,114,0
	.section	.debug_info		;off: 4705
	.data.w	.Ldw_str_begin+3481
	.data.b	191,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3494
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 4720
	.data.w	.Ldw_str_begin+3494
	.data.b	192,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+278
	.section	.debug_loc		;off: 278
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4738
	.data.b	8
	.section	.debug_str		;off: 3501
	.data.b	65,100,100,114,0
	.section	.debug_info		;off: 4739
	.data.w	.Ldw_str_begin+3501
	.data.b	193,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3506
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 4754
	.data.w	.Ldw_str_begin+3506
	.data.b	194,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+177
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+297
	.section	.debug_loc		;off: 297
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4772
	.data.b	7
	.section	.debug_str		;off: 3518
	.data.b	69,114,97,115,101,72,101,97,100,101,114,0
	.section	.debug_info		;off: 4773
	.data.w	.Ldw_str_begin+3518
	.data.b	195,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2030
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+316
	.section	.debug_loc		;off: 316
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4791
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3530
	.data.b	70,101,101,95,76,111,99,97,108,85,112,100,97,116,101,66,108,111,99,107,73,110,102,111,0
	.section	.debug_info		;off: 4794
	.data.w	.Ldw_str_begin+3530
	.data.b	164,8
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalUpdateBlockInfo
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	196,0
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
	.data.w	Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalUpdateBlockInfo-Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2492
	.data.b	0,5,2
	.data.w	Fee_LocalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	168,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	61
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	44
	.data.b	107
	.data.b	11
	.data.b	155
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	45
	.data.b	27
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	29
	.data.b	173
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	11
	.data.b	91
	.data.b	61
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	59
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
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	13
	.data.b	108
	.data.b	77
	.data.b	59
	.data.b	59
	.data.b	13
	.data.b	92
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	12
	.data.b	44
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
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	77
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	57
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	109
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
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	109
	.data.b	59
	.data.b	43
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
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
	.section	.debug_info		;off: 4830
	.data.b	22
	.section	.debug_str		;off: 3555
	.data.b	67,117,114,114,66,97,110,107,65,100,100,114,0
	.section	.debug_info		;off: 4831
	.data.w	.Ldw_str_begin+3555
	.data.b	166,8
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+187
	.data.b	0
	.data.w	.Ldw_loc_begin+336
	.section	.debug_loc		;off: 336
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	80
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4848
	.data.b	22
	.section	.debug_str		;off: 3568
	.data.b	66,108,111,99,107,72,101,97,100,101,114,80,116,114,0
	.section	.debug_info		;off: 4849
	.data.w	.Ldw_str_begin+3568
	.data.b	167,8
	.data.b	66
	.data.b	1
	.data.w	.Ldw_begin+202
	.data.b	0
	.data.w	.Ldw_loc_begin+366
	.section	.debug_loc		;off: 366
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	81
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4866
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 3583
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 4876
	.data.w	.Ldw_str_begin+3583
	.data.b	170,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+396
	.section	.debug_loc		;off: 396
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4894
	.data.b	7
	.section	.debug_str		;off: 3590
	.data.b	66,97,110,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4895
	.data.w	.Ldw_str_begin+3590
	.data.b	171,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+415
	.section	.debug_loc		;off: 415
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4913
	.data.b	7
	.section	.debug_str		;off: 3601
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4914
	.data.w	.Ldw_str_begin+3601
	.data.b	172,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+434
	.section	.debug_loc		;off: 434
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4932
	.data.b	7
	.section	.debug_str		;off: 3613
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 4933
	.data.w	.Ldw_str_begin+3613
	.data.b	173,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+454
	.section	.debug_loc		;off: 454
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4951
	.data.b	7
	.section	.debug_str		;off: 3619
	.data.b	68,97,116,97,80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 4952
	.data.w	.Ldw_str_begin+3619
	.data.b	174,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+473
	.section	.debug_loc		;off: 473
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4970
	.data.b	7
	.section	.debug_str		;off: 3633
	.data.b	80,97,103,101,67,111,117,110,116,0
	.section	.debug_info		;off: 4971
	.data.w	.Ldw_str_begin+3633
	.data.b	175,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+492
	.section	.debug_loc		;off: 492
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4989
	.data.b	7
	.section	.debug_str		;off: 3643
	.data.b	84,111,116,97,108,76,101,110,0
	.section	.debug_info		;off: 4990
	.data.w	.Ldw_str_begin+3643
	.data.b	176,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+511
	.section	.debug_loc		;off: 511
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5008
	.data.b	8
	.section	.debug_str		;off: 3652
	.data.b	73,110,116,97,99,116,66,108,111,99,107,0
	.section	.debug_info		;off: 5009
	.data.w	.Ldw_str_begin+3652
	.data.b	177,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3664
	.data.b	65,100,100,114,0
	.section	.debug_info		;off: 5024
	.data.w	.Ldw_str_begin+3664
	.data.b	178,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3663
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+531
	.section	.debug_loc		;off: 531
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5042
	.data.b	8
	.section	.debug_str		;off: 3669
	.data.b	80,111,116,101,110,116,105,97,108,77,97,114,107,101,114,80,97,103,101,0
	.section	.debug_info		;off: 5043
	.data.w	.Ldw_str_begin+3669
	.data.b	179,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3689
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 5058
	.data.w	.Ldw_str_begin+3689
	.data.b	180,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+226
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+551
	.section	.debug_loc		;off: 551
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5076
	.data.b	7
	.section	.debug_str		;off: 3702
	.data.b	66,108,111,99,107,77,97,114,107,101,114,0
	.section	.debug_info		;off: 5077
	.data.w	.Ldw_str_begin+3702
	.data.b	181,8
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2348
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+570
	.section	.debug_loc		;off: 570
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	16
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5095
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3714
	.data.b	70,101,101,95,76,111,99,97,108,84,114,97,118,101,114,115,97,108,85,112,100,97,116,101,66,108,111,99,107,73,110,102,111,0
	.section	.debug_info		;off: 5098
	.data.w	.Ldw_str_begin+3714
	.data.b	231,9
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.w	Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalTraversalUpdateBlockInfo
	.data.b	1
	.data.b	93
	.data.b	240,143,1
	.data.b	100
	.data.b	0
	.data.b	52
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
	.data.w	Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalTraversalUpdateBlockInfo-Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2736
	.data.b	0,5,2
	.data.w	Fee_LocalTraversalUpdateBlockInfo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	234,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	27
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	156
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	187
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	43
	.data.b	27
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	60
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	44
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	92
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	45
	.data.b	59
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
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
	.data.b	13
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	44
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	156,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	229,0
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5133
	.data.b	22
	.section	.debug_str		;off: 3748
	.data.b	66,97,110,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5134
	.data.w	.Ldw_str_begin+3748
	.data.b	233,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.w	.Ldw_loc_begin+590
	.section	.debug_loc		;off: 590
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	80
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5151
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 3759
	.data.b	69,110,100,65,100,100,114,0
	.section	.debug_info		;off: 5161
	.data.w	.Ldw_str_begin+3759
	.data.b	236,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+620
	.section	.debug_loc		;off: 620
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5179
	.data.b	7
	.section	.debug_str		;off: 3767
	.data.b	67,117,114,114,66,97,110,107,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 5180
	.data.w	.Ldw_str_begin+3767
	.data.b	237,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+639
	.section	.debug_loc		;off: 639
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5198
	.data.b	8
	.section	.debug_str		;off: 3783
	.data.b	66,108,97,110,107,67,104,101,99,107,76,101,110,0
	.section	.debug_info		;off: 5199
	.data.w	.Ldw_str_begin+3783
	.data.b	238,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3797
	.data.b	70,105,110,100,86,97,108,105,100,0
	.section	.debug_info		;off: 5214
	.data.w	.Ldw_str_begin+3797
	.data.b	239,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+659
	.section	.debug_loc		;off: 659
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5232
	.data.b	7
	.section	.debug_str		;off: 3807
	.data.b	83,101,97,114,99,104,69,110,100,0
	.section	.debug_info		;off: 5233
	.data.w	.Ldw_str_begin+3807
	.data.b	240,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+678
	.section	.debug_loc		;off: 678
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5251
	.data.b	7
	.section	.debug_str		;off: 3817
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 5252
	.data.w	.Ldw_str_begin+3817
	.data.b	241,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+697
	.section	.debug_loc		;off: 697
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5270
	.data.b	7
	.section	.debug_str		;off: 3824
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 5271
	.data.w	.Ldw_str_begin+3824
	.data.b	242,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+177
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+716
	.section	.debug_loc		;off: 716
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5289
	.data.b	7
	.section	.debug_str		;off: 3836
	.data.b	66,117,102,102,101,114,85,110,105,111,110,0
	.section	.debug_info		;off: 5290
	.data.w	.Ldw_str_begin+3836
	.data.b	243,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+3570
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+735
	.section	.debug_loc		;off: 735
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5308
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3848
	.data.b	70,101,101,95,76,111,99,97,108,72,97,110,100,108,101,85,115,101,114,87,114,105,116,101,82,101,113,0
	.section	.debug_info		;off: 5311
	.data.w	.Ldw_str_begin+3848
	.data.b	129,11
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalHandleUserWriteReq
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
	.data.b	0
	.data.b	8
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
	.data.w	Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalHandleUserWriteReq-Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2880
	.data.b	0,5,2
	.data.w	Fee_LocalHandleUserWriteReq..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	133,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	43
	.data.b	28
	.data.b	43
	.data.b	27
	.data.b	28
	.data.b	27
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	156
	.data.b	43
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	91
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5342
	.data.b	22
	.section	.debug_str		;off: 3876
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 5343
	.data.w	.Ldw_str_begin+3876
	.data.b	131,11
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+755
	.section	.debug_loc		;off: 755
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5360
	.data.b	22
	.section	.debug_str		;off: 3887
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 5361
	.data.w	.Ldw_str_begin+3887
	.data.b	132,11
	.data.b	52
	.data.b	1
	.data.w	.Ldw_begin+254
	.data.b	0
	.data.w	.Ldw_loc_begin+774
	.section	.debug_loc		;off: 774
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5378
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	7
	.section	.debug_str		;off: 3901
	.data.b	66,108,111,99,107,80,116,114,0
	.section	.debug_info		;off: 5388
	.data.w	.Ldw_str_begin+3901
	.data.b	135,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+113
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+793
	.section	.debug_loc		;off: 793
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5406
	.data.b	7
	.section	.debug_str		;off: 3910
	.data.b	66,108,111,99,107,80,97,103,101,115,0
	.section	.debug_info		;off: 5407
	.data.w	.Ldw_str_begin+3910
	.data.b	136,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+812
	.section	.debug_loc		;off: 812
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5425
	.data.b	7
	.section	.debug_str		;off: 3921
	.data.b	82,101,109,97,105,110,105,110,103,80,97,103,101,115,0
	.section	.debug_info		;off: 5426
	.data.w	.Ldw_str_begin+3921
	.data.b	137,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+831
	.section	.debug_loc		;off: 831
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5444
	.data.b	7
	.section	.debug_str		;off: 3936
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 5445
	.data.w	.Ldw_str_begin+3936
	.data.b	138,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+850
	.section	.debug_loc		;off: 850
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5463
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3949
	.data.b	70,101,101,95,76,111,99,97,108,87,114,105,116,101,0
	.section	.debug_info		;off: 5466
	.data.w	.Ldw_str_begin+3949
	.data.b	217,11
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalWrite
	.data.b	1
	.data.b	93
	.data.b	244,159,1
	.data.b	92
	.data.b	0
	.data.b	36
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
	.data.w	Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalWrite-Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2969
	.data.b	0,5,2
	.data.w	Fee_LocalWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	220,11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	119
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
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	44
	.data.b	28
	.data.b	13
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
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
	.data.b	11
	.data.b	75
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	13
	.data.b	27
	.data.b	27
	.data.b	59
	.data.b	123
	.data.b	93
	.data.b	59
	.data.b	13
	.data.b	43
	.data.b	59
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	59
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	93
	.data.b	27
	.data.b	45
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	45
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	91
	.data.b	60
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	45
	.data.b	92
	.data.b	43
	.data.b	43
	.data.b	43
	.data.b	45
	.data.b	45
	.data.b	27
	.data.b	11
	.data.b	44
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	28
	.data.b	156
	.data.b	27
	.data.b	12
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
	.section	.debug_info		;off: 5497
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 3964
	.data.b	82,101,109,97,105,110,76,101,110,0
	.section	.debug_info		;off: 5507
	.data.w	.Ldw_str_begin+3964
	.data.b	222,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+869
	.section	.debug_loc		;off: 869
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5525
	.data.b	7
	.section	.debug_str		;off: 3974
	.data.b	82,101,97,108,76,101,110,0
	.section	.debug_info		;off: 5526
	.data.w	.Ldw_str_begin+3974
	.data.b	223,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+888
	.section	.debug_loc		;off: 888
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5544
	.data.b	7
	.section	.debug_str		;off: 3982
	.data.b	80,97,103,101,79,102,102,115,101,116,0
	.section	.debug_info		;off: 5545
	.data.w	.Ldw_str_begin+3982
	.data.b	224,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+907
	.section	.debug_loc		;off: 907
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5563
	.data.b	7
	.section	.debug_str		;off: 3993
	.data.b	66,108,111,99,107,83,105,122,101,0
	.section	.debug_info		;off: 5564
	.data.w	.Ldw_str_begin+3993
	.data.b	225,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+926
	.section	.debug_loc		;off: 926
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5582
	.data.b	7
	.section	.debug_str		;off: 4003
	.data.b	66,108,111,99,107,80,97,103,101,115,0
	.section	.debug_info		;off: 5583
	.data.w	.Ldw_str_begin+4003
	.data.b	226,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+945
	.section	.debug_loc		;off: 945
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5601
	.data.b	7
	.section	.debug_str		;off: 4014
	.data.b	76,101,110,103,116,104,0
	.section	.debug_info		;off: 5602
	.data.w	.Ldw_str_begin+4014
	.data.b	227,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+964
	.section	.debug_loc		;off: 964
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5620
	.data.b	7
	.section	.debug_str		;off: 4021
	.data.b	83,114,99,68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 5621
	.data.w	.Ldw_str_begin+4021
	.data.b	228,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+249
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+983
	.section	.debug_loc		;off: 983
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5639
	.data.b	7
	.section	.debug_str		;off: 4038
	.data.b	66,108,111,99,107,80,116,114,0
	.section	.debug_info		;off: 5640
	.data.w	.Ldw_str_begin+4038
	.data.b	229,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+113
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1002
	.section	.debug_loc		;off: 1002
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5658
	.data.b	7
	.section	.debug_str		;off: 4047
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 5659
	.data.w	.Ldw_str_begin+4047
	.data.b	230,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+226
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1021
	.section	.debug_loc		;off: 1021
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5677
	.data.b	7
	.section	.debug_str		;off: 4060
	.data.b	66,108,111,99,107,72,101,97,100,101,114,80,116,114,0
	.section	.debug_info		;off: 5678
	.data.w	.Ldw_str_begin+4060
	.data.b	231,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+287
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1040
	.section	.debug_loc		;off: 1040
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5696
	.data.b	7
	.section	.debug_str		;off: 4075
	.data.b	68,101,115,116,87,114,105,116,101,66,117,102,102,80,116,114,0
	.section	.debug_info		;off: 5697
	.data.w	.Ldw_str_begin+4075
	.data.b	232,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+292
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1059
	.section	.debug_loc		;off: 1059
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5715
	.data.b	8
	.section	.debug_str		;off: 4092
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 5716
	.data.w	.Ldw_str_begin+4092
	.data.b	233,11
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4099
	.data.b	67,111,109,112,97,114,101,82,101,116,117,114,110,86,97,108,0
	.section	.debug_info		;off: 5731
	.data.w	.Ldw_str_begin+4099
	.data.b	235,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4116
	.data.b	70,101,101,95,76,111,99,97,108,82,101,97,100,0
	.section	.debug_info		;off: 5748
	.data.w	.Ldw_str_begin+4116
	.data.b	167,13
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalRead
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

	.section	.debug_frame		;off: 384
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalRead-Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3174
	.data.b	0,5,2
	.data.w	Fee_LocalRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	170,13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	44
	.data.b	45
	.data.b	27
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	43
	.data.b	93
	.data.b	43
	.data.b	45
	.data.b	59
	.data.b	27
	.data.b	11
	.data.b	28
	.data.b	28
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	11
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
	.section	.debug_info		;off: 5779
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	7
	.section	.debug_str		;off: 4130
	.data.b	82,101,97,100,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 5789
	.data.w	.Ldw_str_begin+4130
	.data.b	173,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+249
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1078
	.section	.debug_loc		;off: 1078
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5807
	.data.b	7
	.section	.debug_str		;off: 4144
	.data.b	82,101,97,100,76,105,109,105,116,80,116,114,0
	.section	.debug_info		;off: 5808
	.data.w	.Ldw_str_begin+4144
	.data.b	174,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+249
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1097
	.section	.debug_loc		;off: 1097
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5826
	.data.b	7
	.section	.debug_str		;off: 4157
	.data.b	82,101,97,108,76,101,110,0
	.section	.debug_info		;off: 5827
	.data.w	.Ldw_str_begin+4157
	.data.b	175,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1116
	.section	.debug_loc		;off: 1116
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5845
	.data.b	7
	.section	.debug_str		;off: 4165
	.data.b	83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 5846
	.data.w	.Ldw_str_begin+4165
	.data.b	176,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1135
	.section	.debug_loc		;off: 1135
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5864
	.data.b	7
	.section	.debug_str		;off: 4173
	.data.b	82,101,97,100,76,101,110,103,116,104,0
	.section	.debug_info		;off: 5865
	.data.w	.Ldw_str_begin+4173
	.data.b	177,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1154
	.section	.debug_loc		;off: 1154
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5883
	.data.b	8
	.section	.debug_str		;off: 4184
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 5884
	.data.w	.Ldw_str_begin+4184
	.data.b	178,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4196
	.data.b	70,101,101,95,76,111,99,97,108,71,99,82,101,97,100,0
	.section	.debug_info		;off: 5901
	.data.w	.Ldw_str_begin+4196
	.data.b	151,14
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcRead
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

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcRead-Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3283
	.data.b	0,5,2
	.data.w	Fee_LocalGcRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	154,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	156
	.data.b	43
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5936
	.data.b	22
	.section	.debug_str		;off: 4212
	.data.b	83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 5937
	.data.w	.Ldw_str_begin+4212
	.data.b	153,14
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+3663
	.data.b	0
	.data.w	.Ldw_loc_begin+1173
	.section	.debug_loc		;off: 1173
	.data.w	.LDW34
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5954
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 4220
	.data.b	82,101,97,100,76,101,110,103,116,104,0
	.section	.debug_info		;off: 5964
	.data.w	.Ldw_str_begin+4220
	.data.b	156,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1192
	.section	.debug_loc		;off: 1192
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5982
	.data.b	8
	.section	.debug_str		;off: 4231
	.data.b	80,101,110,100,105,110,103,66,108,111,99,107,83,105,122,101,0
	.section	.debug_info		;off: 5983
	.data.w	.Ldw_str_begin+4231
	.data.b	157,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4248
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 5998
	.data.w	.Ldw_str_begin+4248
	.data.b	158,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1211
	.section	.debug_loc		;off: 1211
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6016
	.data.b	8
	.section	.debug_str		;off: 4254
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 6017
	.data.w	.Ldw_str_begin+4254
	.data.b	159,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4261
	.data.b	70,101,101,95,76,111,99,97,108,71,99,87,114,105,116,101,0
	.section	.debug_info		;off: 6034
	.data.w	.Ldw_str_begin+4261
	.data.b	211,14
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcWrite
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcWrite-Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3319
	.data.b	0,5,2
	.data.w	Fee_LocalGcWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	215,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	44
	.data.b	156
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	27
	.data.b	12
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6069
	.data.b	22
	.section	.debug_str		;off: 4278
	.data.b	68,101,115,116,65,100,100,114,0
	.section	.debug_info		;off: 6070
	.data.w	.Ldw_str_begin+4278
	.data.b	213,14
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+3663
	.data.b	0
	.data.w	.Ldw_loc_begin+1230
	.section	.debug_loc		;off: 1230
	.data.w	.LDW64
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6087
	.data.b	22
	.section	.debug_str		;off: 4287
	.data.b	83,105,122,101,0
	.section	.debug_info		;off: 6088
	.data.w	.Ldw_str_begin+4287
	.data.b	214,14
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+1249
	.section	.debug_loc		;off: 1249
	.data.w	.LDW64
	.data.w	.LDW84
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6105
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	8
	.section	.debug_str		;off: 4292
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6115
	.data.w	.Ldw_str_begin+4292
	.data.b	217,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4298
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 6130
	.data.w	.Ldw_str_begin+4298
	.data.b	218,14
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1268
	.section	.debug_loc		;off: 1268
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6148
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4310
	.data.b	70,101,101,95,76,111,99,97,108,71,99,82,101,113,117,101,115,116,101,100,0
	.section	.debug_info		;off: 6151
	.data.w	.Ldw_str_begin+4310
	.data.b	136,15
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcRequested
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcRequested-Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3355
	.data.b	0,5,2
	.data.w	Fee_LocalGcRequested..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	139,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	91
	.data.b	29
	.data.b	28
	.data.b	60
	.data.b	27
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	29
	.data.b	108
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6184
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 4331
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6194
	.data.w	.Ldw_str_begin+4331
	.data.b	141,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+226
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1287
	.section	.debug_loc		;off: 1287
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6212
	.data.b	8
	.section	.debug_str		;off: 4344
	.data.b	66,108,111,99,107,67,111,117,110,116,0
	.section	.debug_info		;off: 6213
	.data.w	.Ldw_str_begin+4344
	.data.b	142,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4355
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6228
	.data.w	.Ldw_str_begin+4355
	.data.b	143,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4361
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6243
	.data.w	.Ldw_str_begin+4361
	.data.b	144,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+344
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4373
	.data.b	70,101,101,95,76,111,99,97,108,71,99,83,116,97,114,116,67,111,112,121,0
	.section	.debug_info		;off: 6260
	.data.w	.Ldw_str_begin+4373
	.data.b	194,15
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStartCopy
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
	.data.w	Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStartCopy-Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3389
	.data.b	0,5,2
	.data.w	Fee_LocalGcStartCopy..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	197,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	123
	.data.b	11
	.data.b	28
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	45
	.data.b	27
	.data.b	75
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	56
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	104
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	22
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6295
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 4394
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6305
	.data.w	.Ldw_str_begin+4394
	.data.b	199,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+226
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1306
	.section	.debug_loc		;off: 1306
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6323
	.data.b	8
	.section	.debug_str		;off: 4407
	.data.b	70,108,97,103,0
	.section	.debug_info		;off: 6324
	.data.w	.Ldw_str_begin+4407
	.data.b	200,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4412
	.data.b	66,108,111,99,107,67,111,117,110,116,0
	.section	.debug_info		;off: 6339
	.data.w	.Ldw_str_begin+4412
	.data.b	201,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1271
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1325
	.section	.debug_loc		;off: 1325
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6357
	.data.b	8
	.section	.debug_str		;off: 4423
	.data.b	82,101,109,97,105,110,105,110,103,80,97,103,101,115,0
	.section	.debug_info		;off: 6358
	.data.w	.Ldw_str_begin+4423
	.data.b	202,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4438
	.data.b	67,111,110,115,105,115,116,101,110,116,70,108,97,103,0
	.section	.debug_info		;off: 6373
	.data.w	.Ldw_str_begin+4438
	.data.b	203,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4453
	.data.b	67,111,112,105,101,100,70,108,97,103,0
	.section	.debug_info		;off: 6388
	.data.w	.Ldw_str_begin+4453
	.data.b	204,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1344
	.section	.debug_loc		;off: 1344
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6406
	.data.b	7
	.section	.debug_str		;off: 4464
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6407
	.data.w	.Ldw_str_begin+4464
	.data.b	205,15
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1363
	.section	.debug_loc		;off: 1363
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6425
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4470
	.data.b	70,101,101,95,76,111,99,97,108,71,99,83,116,97,114,116,67,111,112,121,87,114,105,116,101,0
	.section	.debug_info		;off: 6428
	.data.w	.Ldw_str_begin+4470
	.data.b	175,16
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStartCopyWrite
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
	.data.w	Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStartCopyWrite-Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3512
	.data.b	0,5,2
	.data.w	Fee_LocalGcStartCopyWrite..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	178,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	75
	.data.b	11
	.data.b	59
	.data.b	59
	.data.b	13
	.data.b	43
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	75
	.data.b	43
	.data.b	27
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
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	59
	.data.b	13
	.data.b	75
	.data.b	76
	.data.b	75
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	45
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	13
	.data.b	11
	.data.b	27
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6463
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	8
	.section	.debug_str		;off: 4496
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 6473
	.data.w	.Ldw_str_begin+4496
	.data.b	180,16
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4503
	.data.b	66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 6488
	.data.w	.Ldw_str_begin+4503
	.data.b	181,16
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+292
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4513
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6503
	.data.w	.Ldw_str_begin+4513
	.data.b	182,16
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1382
	.section	.debug_loc		;off: 1382
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6521
	.data.b	7
	.section	.debug_str		;off: 4519
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6522
	.data.w	.Ldw_str_begin+4519
	.data.b	183,16
	.data.b	24
	.data.b	1
	.data.w	.Ldw_begin+226
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1401
	.section	.debug_loc		;off: 1401
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6540
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4532
	.data.b	70,101,101,95,76,111,99,97,108,71,99,69,114,97,115,101,80,114,101,118,66,97,110,107,0
	.section	.debug_info		;off: 6543
	.data.w	.Ldw_str_begin+4532
	.data.b	186,17
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcErasePrevBank
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcErasePrevBank-Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3648
	.data.b	0,5,2
	.data.w	Fee_LocalGcErasePrevBank..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	189,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	12
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	6
	.data.b	28
	.data.b	6
	.data.b	11
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
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	61
	.data.b	43
	.data.b	13
	.data.b	12
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	27
	.data.b	12
	.data.b	28
	.data.b	92
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	44
	.data.b	43
	.data.b	75
	.data.b	11
	.data.b	75
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
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	45
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	60
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
	.section	.debug_info		;off: 6578
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 4557
	.data.b	66,97,110,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6588
	.data.w	.Ldw_str_begin+4557
	.data.b	191,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1420
	.section	.debug_loc		;off: 1420
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6606
	.data.b	8
	.section	.debug_str		;off: 4568
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 6607
	.data.w	.Ldw_str_begin+4568
	.data.b	192,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4574
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 6622
	.data.w	.Ldw_str_begin+4574
	.data.b	193,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1439
	.section	.debug_loc		;off: 1439
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6640
	.data.b	8
	.section	.debug_str		;off: 4581
	.data.b	78,111,114,109,97,108,83,101,99,116,111,114,0
	.section	.debug_info		;off: 6641
	.data.w	.Ldw_str_begin+4581
	.data.b	194,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4594
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6656
	.data.w	.Ldw_str_begin+4594
	.data.b	195,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1458
	.section	.debug_loc		;off: 1458
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6674
	.data.b	8
	.section	.debug_str		;off: 4600
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 6675
	.data.w	.Ldw_str_begin+4600
	.data.b	196,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4612
	.data.b	66,97,110,107,80,116,114,0
	.section	.debug_info		;off: 6690
	.data.w	.Ldw_str_begin+4612
	.data.b	198,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+177
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1477
	.section	.debug_loc		;off: 1477
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6708
	.data.b	7
	.section	.debug_str		;off: 4620
	.data.b	83,101,99,116,111,114,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6709
	.data.w	.Ldw_str_begin+4620
	.data.b	199,17
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1496
	.section	.debug_loc		;off: 1496
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6727
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4633
	.data.b	70,101,101,95,76,111,99,97,108,71,99,83,116,97,116,101,80,97,103,101,67,111,109,112,97,114,101,0
	.section	.debug_info		;off: 6730
	.data.w	.Ldw_str_begin+4633
	.data.b	202,18
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStatePageCompare
	.data.b	1
	.data.b	93
	.data.b	176,131,1
	.data.b	112
	.data.b	0
	.data.b	16
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
	.data.w	Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcStatePageCompare-Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3796
	.data.b	0,5,2
	.data.w	Fee_LocalGcStatePageCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	205,18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	37
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	3
	.data.b	87
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	11
	.data.b	43
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	76
	.data.b	44
	.data.b	43
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	44
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	28
	.data.b	44
	.data.b	27
	.data.b	59
	.data.b	12
	.data.b	139
	.data.b	12
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	77
	.data.b	59
	.data.b	29
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6765
	.data.b	22
	.section	.debug_str		;off: 4661
	.data.b	71,99,83,116,97,116,101,0
	.section	.debug_info		;off: 6766
	.data.w	.Ldw_str_begin+4661
	.data.b	204,18
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1593
	.data.b	0
	.data.w	.Ldw_loc_begin+1515
	.section	.debug_loc		;off: 1515
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	80
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6783
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	8
	.section	.debug_str		;off: 4669
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 6793
	.data.w	.Ldw_str_begin+4669
	.data.b	207,18
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4676
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 6808
	.data.w	.Ldw_str_begin+4676
	.data.b	208,18
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4682
	.data.b	82,101,109,97,105,110,80,97,103,101,115,0
	.section	.debug_info		;off: 6823
	.data.w	.Ldw_str_begin+4682
	.data.b	209,18
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4694
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 6838
	.data.w	.Ldw_str_begin+4694
	.data.b	210,18
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+177
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1545
	.section	.debug_loc		;off: 1545
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6856
	.data.b	7
	.section	.debug_str		;off: 4706
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 6857
	.data.w	.Ldw_str_begin+4706
	.data.b	211,18
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1564
	.section	.debug_loc		;off: 1564
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6875
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4712
	.data.b	70,101,101,95,76,111,99,97,108,71,99,80,114,111,103,114,97,109,83,116,97,116,101,80,97,103,101,0
	.section	.debug_info		;off: 6878
	.data.w	.Ldw_str_begin+4712
	.data.b	191,19
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.w	Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcProgramStatePage
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGcProgramStatePage-Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3923
	.data.b	0,5,2
	.data.w	Fee_LocalGcProgramStatePage..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	194,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	27
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	59
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
	.data.b	43
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	45
	.data.b	61
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
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	105
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	61
	.data.b	75
	.data.b	27
	.data.b	27
	.data.b	43
	.data.b	27
	.data.b	29
	.data.b	2
	.data.b	20
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	93
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	59
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
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	139
	.data.b	11
	.data.b	27
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
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6913
	.data.b	22
	.section	.debug_str		;off: 4740
	.data.b	71,99,83,116,97,116,101,0
	.section	.debug_info		;off: 6914
	.data.w	.Ldw_str_begin+4740
	.data.b	193,19
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1593
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
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6931
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	8
	.section	.debug_str		;off: 4748
	.data.b	78,101,119,67,111,117,110,116,0
	.section	.debug_info		;off: 6941
	.data.w	.Ldw_str_begin+4748
	.data.b	196,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4757
	.data.b	71,99,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6956
	.data.w	.Ldw_str_begin+4757
	.data.b	197,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1613
	.section	.debug_loc		;off: 1613
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6974
	.data.b	8
	.section	.debug_str		;off: 4766
	.data.b	65,100,100,114,0
	.section	.debug_info		;off: 6975
	.data.w	.Ldw_str_begin+4766
	.data.b	198,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4771
	.data.b	83,105,122,101,0
	.section	.debug_info		;off: 6990
	.data.w	.Ldw_str_begin+4771
	.data.b	199,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1632
	.section	.debug_loc		;off: 1632
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7008
	.data.b	8
	.section	.debug_str		;off: 4776
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 7009
	.data.w	.Ldw_str_begin+4776
	.data.b	200,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4782
	.data.b	77,97,114,107,101,114,80,116,114,0
	.section	.debug_info		;off: 7024
	.data.w	.Ldw_str_begin+4782
	.data.b	201,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1651
	.section	.debug_loc		;off: 1651
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7042
	.data.b	8
	.section	.debug_str		;off: 4792
	.data.b	82,101,109,97,105,110,105,110,103,80,97,103,101,115,0
	.section	.debug_info		;off: 7043
	.data.w	.Ldw_str_begin+4792
	.data.b	202,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4807
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 7058
	.data.w	.Ldw_str_begin+4807
	.data.b	203,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1670
	.section	.debug_loc		;off: 1670
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7076
	.data.b	8
	.section	.debug_str		;off: 4813
	.data.b	69,114,97,115,101,80,97,103,101,72,101,97,100,101,114,80,116,114,0
	.section	.debug_info		;off: 7077
	.data.w	.Ldw_str_begin+4813
	.data.b	204,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+403
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4832
	.data.b	86,97,108,105,100,80,97,103,101,72,101,97,100,101,114,80,116,114,0
	.section	.debug_info		;off: 7092
	.data.w	.Ldw_str_begin+4832
	.data.b	205,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+408
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4851
	.data.b	66,97,110,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 7107
	.data.w	.Ldw_str_begin+4851
	.data.b	206,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+177
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1689
	.section	.debug_loc		;off: 1689
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7125
	.data.b	8
	.section	.debug_str		;off: 4863
	.data.b	85,110,101,114,97,115,97,98,108,101,83,101,99,116,111,114,80,116,114,0
	.section	.debug_info		;off: 7126
	.data.w	.Ldw_str_begin+4863
	.data.b	208,19
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4883
	.data.b	70,101,101,95,76,111,99,97,108,71,67,0
	.section	.debug_info		;off: 7143
	.data.w	.Ldw_str_begin+4883
	.data.b	254,20
	.data.b	37
	.data.b	1
	.data.w	Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGC
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGC-Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4126
	.data.b	0,5,2
	.data.w	Fee_LocalGC..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	129,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	29
	.data.b	60
	.data.b	3
	.data.b	7
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
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	91
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	29
	.data.b	2
	.data.b	8
	.data.b	1
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
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7174
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	7
	.section	.debug_str		;off: 4895
	.data.b	69,114,114,111,114,0
	.section	.debug_info		;off: 7184
	.data.w	.Ldw_str_begin+4895
	.data.b	131,21
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1801
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1708
	.section	.debug_loc		;off: 1708
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7202
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4901
	.data.b	70,101,101,95,76,111,99,97,108,67,111,109,109,111,110,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 7205
	.data.w	.Ldw_str_begin+4901
	.data.b	134,22
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalCommonDetCheck
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalCommonDetCheck-Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4222
	.data.b	0,5,2
	.data.w	Fee_LocalCommonDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	137,22
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
	.data.w	.LDWlin3
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	13
	.data.b	75
	.data.b	11
	.data.b	91
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
	.section	.debug_info		;off: 7240
	.data.b	22
	.section	.debug_str		;off: 4925
	.data.b	83,101,114,118,105,99,101,73,68,0
	.section	.debug_info		;off: 7241
	.data.w	.Ldw_str_begin+4925
	.data.b	136,22
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.w	.Ldw_loc_begin+1727
	.section	.debug_loc		;off: 1727
	.data.w	.LDW07
	.data.w	.LDW27
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7258
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	7
	.section	.debug_str		;off: 4935
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 7268
	.data.w	.Ldw_str_begin+4935
	.data.b	139,22
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1746
	.section	.debug_loc		;off: 1746
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7286
	.data.b	8
	.section	.debug_str		;off: 4947
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7287
	.data.w	.Ldw_str_begin+4947
	.data.b	140,22
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4954
	.data.b	70,101,101,95,76,111,99,97,108,83,107,105,112,82,101,97,100,0
	.section	.debug_info		;off: 7304
	.data.w	.Ldw_str_begin+4954
	.data.b	190,22
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalSkipRead
	.data.b	1
	.data.b	93
	.data.b	240,7
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalSkipRead-Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4280
	.data.b	0,5,2
	.data.w	Fee_LocalSkipRead..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	194,22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	45
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	45
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	92
	.data.b	13
	.data.b	27
	.data.b	44
	.data.b	140
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	28
	.data.b	0,1,1
	.section	.debug_info		;off: 7338
	.data.b	22
	.section	.debug_str		;off: 4972
	.data.b	83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 7339
	.data.w	.Ldw_str_begin+4972
	.data.b	192,22
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.w	.Ldw_loc_begin+1765
	.section	.debug_loc		;off: 1765
	.data.w	.LDW37
	.data.w	.LDW57
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7356
	.data.b	22
	.section	.debug_str		;off: 4980
	.data.b	82,101,97,100,76,101,110,103,116,104,0
	.section	.debug_info		;off: 7357
	.data.w	.Ldw_str_begin+4980
	.data.b	193,22
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.w	.Ldw_loc_begin+1784
	.section	.debug_loc		;off: 1784
	.data.w	.LDW37
	.data.w	.LDW57
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7374
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 4991
	.data.b	83,101,99,116,111,114,82,101,109,97,105,110,0
	.section	.debug_info		;off: 7384
	.data.w	.Ldw_str_begin+4991
	.data.b	196,22
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1803
	.section	.debug_loc		;off: 1803
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7402
	.data.b	7
	.section	.debug_str		;off: 5004
	.data.b	83,101,99,116,111,114,78,111,0
	.section	.debug_info		;off: 7403
	.data.w	.Ldw_str_begin+5004
	.data.b	197,22
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1822
	.section	.debug_loc		;off: 1822
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7421
	.data.b	7
	.section	.debug_str		;off: 5013
	.data.b	65,99,116,82,101,97,100,76,101,110,103,116,104,0
	.section	.debug_info		;off: 7422
	.data.w	.Ldw_str_begin+5013
	.data.b	198,22
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1841
	.section	.debug_loc		;off: 1841
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7440
	.data.b	8
	.section	.debug_str		;off: 5027
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7441
	.data.w	.Ldw_str_begin+5027
	.data.b	199,22
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5040
	.data.b	70,101,101,95,76,111,99,97,108,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7458
	.data.w	.Ldw_str_begin+5040
	.data.b	253,22
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.w	Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGetStatus
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_LocalGetStatus-Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4325
	.data.b	0,5,2
	.data.w	Fee_LocalGetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	132,23
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	61
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7491
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	8
	.section	.debug_str		;off: 5059
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7501
	.data.w	.Ldw_str_begin+5059
	.data.b	130,23
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5072
	.data.b	70,101,101,95,73,110,105,116,105,97,108,105,122,101,77,111,100,117,108,101,65,110,100,66,97,110,107,115,0
	.section	.debug_info		;off: 7518
	.data.w	.Ldw_str_begin+5072
	.data.b	193,23
	.data.b	37
	.data.b	1
	.data.w	Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_InitializeModuleAndBanks
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.w	__ghs_eofn_Fee_InitializeModuleAndBanks-Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4395
	.data.b	0,5,2
	.data.w	Fee_InitializeModuleAndBanks..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CFee.
	.data.b	6
	.data.b	3
	.data.b	196,23
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	59
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
	.data.b	59
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
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	107
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	13
	.data.b	43
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	80
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	59
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	60
	.data.b	3
	.data.b	111
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7549
	.data.b	22
	.section	.debug_str		;off: 5101
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 7550
	.data.w	.Ldw_str_begin+5101
	.data.b	195,23
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+460
	.data.b	0
	.data.w	.Ldw_loc_begin+1860
	.section	.debug_loc		;off: 1860
	.data.w	.LDW97
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7567
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	7
	.section	.debug_str		;off: 5111
	.data.b	66,97,110,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7577
	.data.w	.Ldw_str_begin+5111
	.data.b	198,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1879
	.section	.debug_loc		;off: 1879
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7595
	.data.b	7
	.section	.debug_str		;off: 5122
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 7596
	.data.w	.Ldw_str_begin+5122
	.data.b	199,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1898
	.section	.debug_loc		;off: 1898
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7614
	.data.b	7
	.section	.debug_str		;off: 5128
	.data.b	70,101,101,70,97,105,108,82,101,116,114,121,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7615
	.data.w	.Ldw_str_begin+5128
	.data.b	200,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1917
	.section	.debug_loc		;off: 1917
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7633
	.data.b	7
	.section	.debug_str		;off: 5147
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 7634
	.data.w	.Ldw_str_begin+5147
	.data.b	201,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1936
	.section	.debug_loc		;off: 1936
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7652
	.data.b	7
	.section	.debug_str		;off: 5154
	.data.b	83,116,97,116,101,0
	.section	.debug_info		;off: 7653
	.data.w	.Ldw_str_begin+5154
	.data.b	202,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1259
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1955
	.section	.debug_loc		;off: 1955
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7671
	.data.b	7
	.section	.debug_str		;off: 5160
	.data.b	67,117,114,114,66,97,110,107,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 7672
	.data.w	.Ldw_str_begin+5160
	.data.b	203,23
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1974
	.section	.debug_loc		;off: 1974
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7690
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5176
	.data.b	70,101,101,95,73,110,105,116,0
	.section	.debug_info		;off: 7693
	.data.w	.Ldw_str_begin+5176
	.data.b	186,24
	.data.b	29
	.data.b	1
	.data.w	Fee_Init
	.data.w	__ghs_eofn_Fee_Init
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
	.data.w	Fee_Init
	.data.w	__ghs_eofn_Fee_Init-Fee_Init
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4540
	.data.b	0,5,2
	.data.w	Fee_Init
	.data.b	6
	.data.b	3
	.data.b	196,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	91
	.data.b	13
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	27
	.data.b	29
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	61
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7722
	.data.b	22
	.section	.debug_str		;off: 5185
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 7723
	.data.w	.Ldw_str_begin+5185
	.data.b	188,24
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+460
	.data.b	0
	.data.w	.Ldw_loc_begin+1993
	.section	.debug_loc		;off: 1993
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7740
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	7
	.section	.debug_str		;off: 5195
	.data.b	67,111,117,110,116,0
	.section	.debug_info		;off: 7750
	.data.w	.Ldw_str_begin+5195
	.data.b	191,24
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1295
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2012
	.section	.debug_loc		;off: 2012
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7768
	.data.b	8
	.section	.debug_str		;off: 5201
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7769
	.data.w	.Ldw_str_begin+5201
	.data.b	193,24
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5208
	.data.b	70,101,101,95,83,101,116,77,111,100,101,0
	.section	.debug_info		;off: 7786
	.data.w	.Ldw_str_begin+5208
	.data.b	131,25
	.data.b	29
	.data.b	1
	.data.w	Fee_SetMode
	.data.w	__ghs_eofn_Fee_SetMode
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

	.section	.debug_frame		;off: 744
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_SetMode
	.data.w	__ghs_eofn_Fee_SetMode-Fee_SetMode
	.data.b	1
	.data.w	.LDW78
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4611
	.data.b	0,5,2
	.data.w	Fee_SetMode
	.data.b	6
	.data.b	3
	.data.b	134,25
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	12
	.data.b	28
	.data.b	59
	.data.b	13
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
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
	.section	.debug_info		;off: 7817
	.data.b	22
	.section	.debug_str		;off: 5220
	.data.b	77,111,100,101,0
	.section	.debug_info		;off: 7818
	.data.w	.Ldw_str_begin+5220
	.data.b	133,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1235
	.data.b	0
	.data.w	.Ldw_loc_begin+2031
	.section	.debug_loc		;off: 2031
	.data.w	.LDW58
	.data.w	.LDW68
	.data.b	1,0
	.data.b	80
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7835
	.data.b	34
	.data.w	.LDW68
	.data.w	.LDW78

	.data.b	7
	.section	.debug_str		;off: 5225
	.data.b	70,101,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7845
	.data.w	.Ldw_str_begin+5225
	.data.b	136,25
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2061
	.section	.debug_loc		;off: 2061
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7863
	.data.b	8
	.section	.debug_str		;off: 5235
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 7864
	.data.w	.Ldw_str_begin+5235
	.data.b	138,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5250
	.data.b	70,101,101,95,82,101,97,100,0
	.section	.debug_info		;off: 7881
	.data.w	.Ldw_str_begin+5250
	.data.b	190,25
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_Read
	.data.w	__ghs_eofn_Fee_Read
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

	.section	.debug_frame		;off: 768
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_Read
	.data.w	__ghs_eofn_Fee_Read-Fee_Read
	.data.b	1
	.data.w	.LDW09
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4660
	.data.b	0,5,2
	.data.w	Fee_Read
	.data.b	6
	.data.b	3
	.data.b	196,25
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	61
	.data.b	12
	.data.b	11
	.data.b	92
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	59
	.data.b	13
	.data.b	27
	.data.b	27
	.data.b	28
	.data.b	27
	.data.b	29
	.data.b	44
	.data.b	43
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	43
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	92
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	44
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	93
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
	.section	.debug_info		;off: 7916
	.data.b	22
	.section	.debug_str		;off: 5259
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7917
	.data.w	.Ldw_str_begin+5259
	.data.b	192,25
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2080
	.section	.debug_loc		;off: 2080
	.data.w	.LDW88
	.data.w	.LDW98
	.data.b	1,0
	.data.b	80
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7934
	.data.b	22
	.section	.debug_str		;off: 5271
	.data.b	66,108,111,99,107,79,102,102,115,101,116,0
	.section	.debug_info		;off: 7935
	.data.w	.Ldw_str_begin+5271
	.data.b	193,25
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2110
	.section	.debug_loc		;off: 2110
	.data.w	.LDW88
	.data.w	.LDW98
	.data.b	1,0
	.data.b	81
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7952
	.data.b	22
	.section	.debug_str		;off: 5283
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 7953
	.data.w	.Ldw_str_begin+5283
	.data.b	194,25
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+292
	.data.b	0
	.data.w	.Ldw_loc_begin+2140
	.section	.debug_loc		;off: 2140
	.data.w	.LDW88
	.data.w	.LDW98
	.data.b	1,0
	.data.b	82
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7970
	.data.b	22
	.section	.debug_str		;off: 5297
	.data.b	76,101,110,103,116,104,0
	.section	.debug_info		;off: 7971
	.data.w	.Ldw_str_begin+5297
	.data.b	195,25
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2170
	.section	.debug_loc		;off: 2170
	.data.w	.LDW88
	.data.w	.LDW98
	.data.b	1,0
	.data.b	83
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7988
	.data.b	34
	.data.w	.LDW98
	.data.w	.LDW09

	.data.b	7
	.section	.debug_str		;off: 5304
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 7998
	.data.w	.Ldw_str_begin+5304
	.data.b	198,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2200
	.section	.debug_loc		;off: 2200
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8016
	.data.b	7
	.section	.debug_str		;off: 5315
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 8017
	.data.w	.Ldw_str_begin+5315
	.data.b	199,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2219
	.section	.debug_loc		;off: 2219
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8035
	.data.b	7
	.section	.debug_str		;off: 5327
	.data.b	70,101,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8036
	.data.w	.Ldw_str_begin+5327
	.data.b	200,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2238
	.section	.debug_loc		;off: 2238
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8054
	.data.b	7
	.section	.debug_str		;off: 5337
	.data.b	67,111,110,115,105,115,116,101,110,116,70,108,97,103,0
	.section	.debug_info		;off: 8055
	.data.w	.Ldw_str_begin+5337
	.data.b	201,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2257
	.section	.debug_loc		;off: 2257
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8073
	.data.b	7
	.section	.debug_str		;off: 5352
	.data.b	86,97,108,105,100,70,108,97,103,0
	.section	.debug_info		;off: 8074
	.data.w	.Ldw_str_begin+5352
	.data.b	202,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+1247
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2276
	.section	.debug_loc		;off: 2276
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8092
	.data.b	7
	.section	.debug_str		;off: 5362
	.data.b	66,108,111,99,107,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 8093
	.data.w	.Ldw_str_begin+5362
	.data.b	203,25
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2295
	.section	.debug_loc		;off: 2295
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8111
	.data.b	8
	.section	.debug_str		;off: 5375
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8112
	.data.w	.Ldw_str_begin+5375
	.data.b	206,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5390
	.data.b	66,108,111,99,107,83,105,122,101,0
	.section	.debug_info		;off: 8127
	.data.w	.Ldw_str_begin+5390
	.data.b	207,25
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2314
	.section	.debug_loc		;off: 2314
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8145
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5400
	.data.b	70,101,101,95,87,114,105,116,101,0
	.section	.debug_info		;off: 8148
	.data.w	.Ldw_str_begin+5400
	.data.b	215,26
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_Write
	.data.w	__ghs_eofn_Fee_Write
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

	.section	.debug_frame		;off: 792
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_Write
	.data.w	__ghs_eofn_Fee_Write-Fee_Write
	.data.b	1
	.data.w	.LDW39
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4786
	.data.b	0,5,2
	.data.w	Fee_Write
	.data.b	6
	.data.b	3
	.data.b	219,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	91
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	59
	.data.b	27
	.data.b	13
	.data.b	13
	.data.b	92
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
	.section	.debug_info		;off: 8183
	.data.b	22
	.section	.debug_str		;off: 5410
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 8184
	.data.w	.Ldw_str_begin+5410
	.data.b	217,26
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2333
	.section	.debug_loc		;off: 2333
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

	.section	.debug_info		;off: 8201
	.data.b	22
	.section	.debug_str		;off: 5422
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 8202
	.data.w	.Ldw_str_begin+5422
	.data.b	218,26
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+249
	.data.b	0
	.data.w	.Ldw_loc_begin+2363
	.section	.debug_loc		;off: 2363
	.data.w	.LDW19
	.data.w	.LDW29
	.data.b	1,0
	.data.b	81
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8219
	.data.b	34
	.data.w	.LDW29
	.data.w	.LDW39

	.data.b	7
	.section	.debug_str		;off: 5436
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 8229
	.data.w	.Ldw_str_begin+5436
	.data.b	221,26
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2393
	.section	.debug_loc		;off: 2393
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8247
	.data.b	7
	.section	.debug_str		;off: 5447
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 8248
	.data.w	.Ldw_str_begin+5447
	.data.b	222,26
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2412
	.section	.debug_loc		;off: 2412
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8266
	.data.b	7
	.section	.debug_str		;off: 5459
	.data.b	70,101,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8267
	.data.w	.Ldw_str_begin+5459
	.data.b	223,26
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2431
	.section	.debug_loc		;off: 2431
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8285
	.data.b	8
	.section	.debug_str		;off: 5469
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8286
	.data.w	.Ldw_str_begin+5469
	.data.b	225,26
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5484
	.data.b	70,101,101,95,67,97,110,99,101,108,0
	.section	.debug_info		;off: 8303
	.data.w	.Ldw_str_begin+5484
	.data.b	174,27
	.data.b	29
	.data.b	1
	.data.w	Fee_Cancel
	.data.w	__ghs_eofn_Fee_Cancel
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

	.section	.debug_frame		;off: 816
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_Cancel
	.data.w	__ghs_eofn_Fee_Cancel-Fee_Cancel
	.data.b	1
	.data.w	.LDW69
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4850
	.data.b	0,5,2
	.data.w	Fee_Cancel
	.data.b	6
	.data.b	3
	.data.b	177,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	11
	.data.b	28
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	75
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	28
	.data.b	44
	.data.b	43
	.data.b	13
	.data.b	12
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
	.section	.debug_info		;off: 8334
	.data.b	34
	.data.w	.LDW59
	.data.w	.LDW69

	.data.b	8
	.section	.debug_str		;off: 5495
	.data.b	70,101,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8344
	.data.w	.Ldw_str_begin+5495
	.data.b	179,27
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5505
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8359
	.data.w	.Ldw_str_begin+5505
	.data.b	181,27
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5520
	.data.b	70,101,101,95,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8376
	.data.w	.Ldw_str_begin+5520
	.data.b	128,28
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.w	Fee_GetStatus
	.data.w	__ghs_eofn_Fee_GetStatus
	.data.b	1
	.data.b	93
	.data.b	128,128,1
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

	.section	.debug_frame		;off: 840
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_GetStatus
	.data.w	__ghs_eofn_Fee_GetStatus-Fee_GetStatus
	.data.b	1
	.data.w	.LDW99
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4915
	.data.b	0,5,2
	.data.w	Fee_GetStatus
	.data.b	6
	.data.b	3
	.data.b	131,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	11
	.data.b	43
	.data.b	11
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
	.section	.debug_info		;off: 8411
	.data.b	34
	.data.w	.LDW89
	.data.w	.LDW99

	.data.b	8
	.section	.debug_str		;off: 5534
	.data.b	82,101,116,117,114,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8421
	.data.w	.Ldw_str_begin+5534
	.data.b	133,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5547
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 8436
	.data.w	.Ldw_str_begin+5547
	.data.b	135,28
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5554
	.data.b	70,101,101,95,71,101,116,74,111,98,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8453
	.data.w	.Ldw_str_begin+5554
	.data.b	187,28
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+1194
	.data.w	Fee_GetJobResult
	.data.w	__ghs_eofn_Fee_GetJobResult
	.data.b	1
	.data.b	93
	.data.b	128,128,1
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

	.section	.debug_frame		;off: 864
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_GetJobResult
	.data.w	__ghs_eofn_Fee_GetJobResult-Fee_GetJobResult
	.data.b	1
	.data.w	.LDW201
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4968
	.data.b	0,5,2
	.data.w	Fee_GetJobResult
	.data.b	6
	.data.b	3
	.data.b	190,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	13
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 8488
	.data.b	34
	.data.w	.LDW101
	.data.w	.LDW201

	.data.b	8
	.section	.debug_str		;off: 5571
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 8498
	.data.w	.Ldw_str_begin+5571
	.data.b	192,28
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1194
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5583
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8513
	.data.w	.Ldw_str_begin+5583
	.data.b	194,28
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5598
	.data.b	70,101,101,95,73,110,118,97,108,105,100,97,116,101,66,108,111,99,107,0
	.section	.debug_info		;off: 8530
	.data.w	.Ldw_str_begin+5598
	.data.b	236,28
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_InvalidateBlock
	.data.w	__ghs_eofn_Fee_InvalidateBlock
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

	.section	.debug_frame		;off: 888
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_InvalidateBlock
	.data.w	__ghs_eofn_Fee_InvalidateBlock-Fee_InvalidateBlock
	.data.b	1
	.data.w	.LDW501
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5002
	.data.b	0,5,2
	.data.w	Fee_InvalidateBlock
	.data.b	6
	.data.b	3
	.data.b	239,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	59
	.data.b	12
	.data.b	107
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	75
	.data.b	11
	.data.b	27
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	92
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
	.section	.debug_info		;off: 8565
	.data.b	22
	.section	.debug_str		;off: 5618
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 8566
	.data.w	.Ldw_str_begin+5618
	.data.b	238,28
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2450
	.section	.debug_loc		;off: 2450
	.data.w	.LDW301
	.data.w	.LDW401
	.data.b	1,0
	.data.b	80
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8583
	.data.b	34
	.data.w	.LDW401
	.data.w	.LDW501

	.data.b	7
	.section	.debug_str		;off: 5630
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 8593
	.data.w	.Ldw_str_begin+5630
	.data.b	241,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2480
	.section	.debug_loc		;off: 2480
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8611
	.data.b	7
	.section	.debug_str		;off: 5641
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 8612
	.data.w	.Ldw_str_begin+5641
	.data.b	242,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2499
	.section	.debug_loc		;off: 2499
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8630
	.data.b	7
	.section	.debug_str		;off: 5653
	.data.b	70,101,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8631
	.data.w	.Ldw_str_begin+5653
	.data.b	243,28
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2518
	.section	.debug_loc		;off: 2518
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8649
	.data.b	8
	.section	.debug_str		;off: 5663
	.data.b	68,101,116,67,104,101,99,107,82,101,115,117,108,116,0
	.section	.debug_info		;off: 8650
	.data.w	.Ldw_str_begin+5663
	.data.b	245,28
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5678
	.data.b	70,101,101,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 8667
	.data.w	.Ldw_str_begin+5678
	.data.b	189,29
	.data.b	29
	.data.b	1
	.data.w	Fee_GetVersionInfo
	.data.w	__ghs_eofn_Fee_GetVersionInfo
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

	.section	.debug_frame		;off: 912
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_GetVersionInfo
	.data.w	__ghs_eofn_Fee_GetVersionInfo-Fee_GetVersionInfo
	.data.b	1
	.data.w	.LDW801
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5062
	.data.b	0,5,2
	.data.w	Fee_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	194,29
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
	.section	.debug_info		;off: 8696
	.data.b	22
	.section	.debug_str		;off: 5697
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 8697
	.data.w	.Ldw_str_begin+5697
	.data.b	191,29
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+572
	.data.b	0
	.data.w	.Ldw_loc_begin+2537
	.section	.debug_loc		;off: 2537
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8714
	.data.b	34
	.data.w	.LDW701
	.data.w	.LDW801

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5712
	.data.b	70,101,101,95,69,114,97,115,101,73,109,109,101,100,105,97,116,101,66,108,111,99,107,0
	.section	.debug_info		;off: 8726
	.data.w	.Ldw_str_begin+5712
	.data.b	237,29
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_EraseImmediateBlock
	.data.w	__ghs_eofn_Fee_EraseImmediateBlock
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
	.data.w	Fee_EraseImmediateBlock
	.data.w	__ghs_eofn_Fee_EraseImmediateBlock-Fee_EraseImmediateBlock
	.data.b	1
	.data.w	.LDW111
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5094
	.data.b	0,5,2
	.data.w	Fee_EraseImmediateBlock
	.data.b	6
	.data.b	3
	.data.b	244,29
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 8759
	.data.b	22
	.section	.debug_str		;off: 5736
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 8760
	.data.w	.Ldw_str_begin+5736
	.data.b	239,29
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2556
	.section	.debug_loc		;off: 2556
	.data.w	.LDW011
	.data.w	.LDW111
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 8777
	.data.b	34
	.data.w	.LDW011
	.data.w	.LDW111

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5748
	.data.b	70,101,101,95,77,97,105,110,70,117,110,99,116,105,111,110,0
	.section	.debug_info		;off: 8789
	.data.w	.Ldw_str_begin+5748
	.data.b	145,30
	.data.b	29
	.data.b	1
	.data.w	Fee_MainFunction
	.data.w	__ghs_eofn_Fee_MainFunction
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

	.section	.debug_frame		;off: 960
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_MainFunction
	.data.w	__ghs_eofn_Fee_MainFunction-Fee_MainFunction
	.data.b	1
	.data.w	.LDW411
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5116
	.data.b	0,5,2
	.data.w	Fee_MainFunction
	.data.b	6
	.data.b	3
	.data.b	148,30
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
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
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	123
	.data.b	13
	.data.b	13
	.data.b	59
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	29
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	3
	.data.b	108
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	11
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
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 8820
	.data.b	34
	.data.w	.LDW311
	.data.w	.LDW411

	.data.b	8
	.section	.debug_str		;off: 5765
	.data.b	70,108,115,83,116,97,116,117,115,0
	.section	.debug_info		;off: 8830
	.data.w	.Ldw_str_begin+5765
	.data.b	150,30
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1117
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5775
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 8845
	.data.w	.Ldw_str_begin+5775
	.data.b	152,30
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5782
	.data.b	70,101,101,95,74,111,98,69,110,100,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 8862
	.data.w	.Ldw_str_begin+5782
	.data.b	255,30
	.data.b	29
	.data.b	1
	.data.w	Fee_JobEndNotification
	.data.w	__ghs_eofn_Fee_JobEndNotification
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

	.section	.debug_frame		;off: 984
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_JobEndNotification
	.data.w	__ghs_eofn_Fee_JobEndNotification-Fee_JobEndNotification
	.data.b	1
	.data.w	.LDW711
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5244
	.data.b	0,5,2
	.data.w	Fee_JobEndNotification
	.data.b	6
	.data.b	3
	.data.b	130,31
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	123
	.data.b	13
	.data.b	12
	.data.b	75
	.data.b	13
	.data.b	61
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	43
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
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 8893
	.data.b	34
	.data.w	.LDW611
	.data.w	.LDW711

	.data.b	8
	.section	.debug_str		;off: 5805
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 8903
	.data.w	.Ldw_str_begin+5805
	.data.b	132,31
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5812
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 8918
	.data.w	.Ldw_str_begin+5812
	.data.b	135,31
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5819
	.data.b	70,101,101,95,74,111,98,69,114,114,111,114,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 8935
	.data.w	.Ldw_str_begin+5819
	.data.b	205,31
	.data.b	29
	.data.b	1
	.data.w	Fee_JobErrorNotification
	.data.w	__ghs_eofn_Fee_JobErrorNotification
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

	.section	.debug_frame		;off: 1008
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_JobErrorNotification
	.data.w	__ghs_eofn_Fee_JobErrorNotification-Fee_JobErrorNotification
	.data.b	1
	.data.w	.LDW021
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5322
	.data.b	0,5,2
	.data.w	Fee_JobErrorNotification
	.data.b	6
	.data.b	3
	.data.b	214,31
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	11
	.data.b	27
	.data.b	11
	.data.b	107
	.data.b	13
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	27
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
	.section	.debug_info		;off: 8964
	.data.b	34
	.data.w	.LDW911
	.data.w	.LDW021

	.data.b	8
	.section	.debug_str		;off: 5844
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 8974
	.data.w	.Ldw_str_begin+5844
	.data.b	211,31
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+3651
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5851
	.data.b	70,101,101,95,71,101,116,67,121,99,108,101,67,111,117,110,116,0
	.section	.debug_info		;off: 8991
	.data.w	.Ldw_str_begin+5851
	.data.b	143,32
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.w	Fee_GetCycleCount
	.data.w	__ghs_eofn_Fee_GetCycleCount
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

	.section	.debug_frame		;off: 1032
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Fee_GetCycleCount
	.data.w	__ghs_eofn_Fee_GetCycleCount-Fee_GetCycleCount
	.data.b	1
	.data.w	.LDW321
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5381
	.data.b	0,5,2
	.data.w	Fee_GetCycleCount
	.data.b	6
	.data.b	3
	.data.b	147,32
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	28
	.data.b	75
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	11
	.data.b	107
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
	.section	.debug_info		;off: 9026
	.data.b	22
	.section	.debug_str		;off: 5869
	.data.b	66,108,111,99,107,78,117,109,98,101,114,0
	.section	.debug_info		;off: 9027
	.data.w	.Ldw_str_begin+5869
	.data.b	145,32
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.w	.Ldw_loc_begin+2575
	.section	.debug_loc		;off: 2575
	.data.w	.LDW121
	.data.w	.LDW221
	.data.b	1,0
	.data.b	80
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9044
	.data.b	22
	.section	.debug_str		;off: 5881
	.data.b	67,111,117,110,116,80,116,114,0
	.section	.debug_info		;off: 9045
	.data.w	.Ldw_str_begin+5881
	.data.b	146,32
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.w	.Ldw_loc_begin+2605
	.section	.debug_loc		;off: 2605
	.data.w	.LDW121
	.data.w	.LDW221
	.data.b	1,0
	.data.b	81
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9062
	.data.b	34
	.data.w	.LDW221
	.data.w	.LDW321

	.data.b	7
	.section	.debug_str		;off: 5890
	.data.b	66,108,111,99,107,73,110,100,101,120,0
	.section	.debug_info		;off: 9072
	.data.w	.Ldw_str_begin+5890
	.data.b	149,32
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1283
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2635
	.section	.debug_loc		;off: 2635
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9090
	.data.b	7
	.section	.debug_str		;off: 5901
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 9091
	.data.w	.Ldw_str_begin+5901
	.data.b	150,32
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+1319
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2654
	.section	.debug_loc		;off: 2654
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 9109
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
	.data.b	36
	.data.b	3
	.data.b	3
	.data.b	38
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	5
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	6
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	70,69,69,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	44
	.data.b	70,69,69,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,50,49,85,41,0
	.data.b	1
	.data.b	47
	.data.b	70,69,69,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	48
	.data.b	70,69,69,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	49
	.data.b	70,69,69,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	52
	.data.b	70,69,69,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	53
	.data.b	70,69,69,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	54
	.data.b	70,69,69,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	57
	.data.b	70,69,69,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	60
	.data.b	70,69,69,95,83,79,70,84,87,65,82,69,95,86,69,82,73,70,89,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	63
	.data.b	70,69,69,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	66
	.data.b	70,69,69,95,83,69,84,77,79,68,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	69
	.data.b	70,69,69,95,71,67,95,82,69,83,84,65,82,84,95,87,82,73,84,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	72
	.data.b	70,69,69,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	75
	.data.b	70,69,69,95,83,69,67,84,79,82,95,78,85,77,66,69,82,32,40,54,52,85,41,0
	.data.b	1
	.data.b	78
	.data.b	70,69,69,95,83,84,65,82,84,65,68,68,82,69,83,83,32,40,48,85,41,0
	.data.b	1
	.data.b	81
	.data.b	70,69,69,95,83,69,67,84,79,82,95,83,73,90,69,32,40,56,49,57,50,85,41,0
	.data.b	1
	.data.b	84
	.data.b	70,69,69,95,83,69,67,84,79,82,95,84,79,95,66,89,84,69,95,83,72,73,70,84,32,40,49,51,85,41,0
	.data.b	1
	.data.b	87
	.data.b	70,69,69,95,68,70,76,65,83,72,95,83,73,90,69,32,40,53,50,52,50,56,56,85,41,0
	.data.b	1
	.data.b	93
	.data.b	70,69,69,95,86,73,82,84,85,65,76,95,80,65,71,69,95,83,73,90,69,32,40,49,54,85,41,0
	.data.b	1
	.data.b	96
	.data.b	70,69,69,95,80,65,71,69,95,84,79,95,66,89,84,69,95,83,72,73,70,84,32,40,52,85,41,0
	.data.b	1
	.data.b	103
	.data.b	70,69,69,95,80,65,71,69,95,79,86,69,82,72,69,65,68,32,40,49,85,41,0
	.data.b	1
	.data.b	106
	.data.b	70,69,69,95,77,65,88,95,66,76,79,67,75,95,67,79,85,78,84,32,40,50,85,41,0
	.data.b	1
	.data.b	109
	.data.b	70,69,69,95,77,65,88,95,66,65,68,83,69,67,84,79,82,95,67,79,85,78,84,32,40,50,85,41,0
	.data.b	1
	.data.b	121
	.data.b	70,69,69,95,84,72,82,69,83,72,79,76,68,95,76,73,77,73,84,32,40,50,48,48,85,41,0
	.data.b	1
	.data.b	127
	.data.b	70,69,69,95,78,79,84,95,70,79,85,78,68,95,77,65,78,65,71,69,77,69,78,84,73,78,70,79,95,68,69,84,69,67,84,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	130,1
	.data.b	70,69,69,95,87,82,73,84,69,95,76,69,78,95,77,65,88,32,40,49,50,56,85,41,0
	.data.b	1
	.data.b	154,1
	.data.b	70,69,69,95,67,79,82,69,95,65,76,76,79,67,65,84,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	165,1
	.data.b	70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,32,40,48,85,41,0
	.data.b	1
	.data.b	166,1
	.data.b	70,69,69,95,69,78,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,32,40,49,85,41,0
	.data.b	1
	.data.b	169,1
	.data.b	70,69,69,95,71,67,95,87,82,73,84,69,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	171,1
	.data.b	70,69,69,95,71,67,95,82,69,65,68,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	173,1
	.data.b	70,69,69,95,71,67,95,69,82,65,83,69,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	175,1
	.data.b	70,69,69,95,71,67,95,84,82,73,71,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	177,1
	.data.b	70,69,69,95,87,82,73,84,69,95,67,89,67,76,69,83,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	179,1
	.data.b	70,69,69,95,85,78,67,70,71,95,66,76,75,95,68,69,77,95,82,69,80,79,82,84,32,40,70,69,69,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	181,1
	.data.b	70,69,69,95,68,69,77,95,69,78,65,66,76,69,68,32,40,83,84,68,95,79,70,70,41,0
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	7
	.data.b	3
	.data.b	25
	.data.b	8
	.data.b	3
	.data.b	31
	.data.b	9
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	10
	.data.b	3
	.data.b	13
	.data.b	11
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
	.data.b	55
	.data.b	65,76,73,71,78,69,68,40,120,41,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,97,108,105,103,110,101,100,40,120,41,41,41,0
	.data.b	1
	.data.b	88
	.data.b	77,69,77,77,65,80,95,83,84,65,82,84,95,66,83,83,40,83,101,99,116,105,111,110,78,97,109,101,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,98,115,115,32
	.data.b	61,32,83,101,99,116,105,111,110,78,97,109,101,41,0
	.data.b	1
	.data.b	91
	.data.b	77,69,77,77,65,80,95,83,84,79,80,95,66,83,83,40,41,32,69,88,80,65,78,68,95,80,82,65,71,77,65,40,103,104,115,32,115,101,99,116,105,111,110,32,98,115,115,32,61,32,100,101,102,97,117,108,116,41,0
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
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	12
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
	.data.b	4
	.data.b	1
	.data.b	44
	.data.b	70,69,69,95,73,78,83,84,65,78,67,69,95,73,68,32,40,48,85,41,0
	.data.b	1
	.data.b	46
	.data.b	70,69,69,95,73,78,73,84,95,73,68,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	47
	.data.b	70,69,69,95,83,69,84,77,79,68,69,95,73,68,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	48
	.data.b	70,69,69,95,82,69,65,68,95,73,68,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	49
	.data.b	70,69,69,95,87,82,73,84,69,95,73,68,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	50
	.data.b	70,69,69,95,67,65,78,67,69,76,95,73,68,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	51
	.data.b	70,69,69,95,71,69,84,83,84,65,84,85,83,95,73,68,32,40,48,120,48,53,85,41,0
	.data.b	1
	.data.b	52
	.data.b	70,69,69,95,71,69,84,74,79,66,82,69,83,85,76,84,95,73,68,32,40,48,120,48,54,85,41,0
	.data.b	1
	.data.b	53
	.data.b	70,69,69,95,73,78,86,65,76,73,68,65,84,69,66,76,79,67,75,95,73,68,32,40,48,120,48,55,85,41,0
	.data.b	1
	.data.b	54
	.data.b	70,69,69,95,71,69,84,86,69,82,83,73,79,78,73,78,70,79,95,73,68,32,40,48,120,48,56,85,41,0
	.data.b	1
	.data.b	55
	.data.b	70,69,69,95,74,79,66,69,78,68,78,79,84,73,70,73,67,65,84,73,79,78,95,73,68,32,40,48,120,49,48,85,41,0
	.data.b	1
	.data.b	56
	.data.b	70,69,69,95,74,79,66,69,82,82,79,82,78,79,84,73,70,73,67,65,84,73,79,78,95,73,68,32,40,48,120,49,49,85,41,0
	.data.b	1
	.data.b	57
	.data.b	70,69,69,95,77,65,73,78,70,85,78,67,84,73,79,78,95,73,68,32,40,48,120,49,50,85,41,0
	.data.b	1
	.data.b	58
	.data.b	70,69,69,95,83,73,68,95,71,69,84,67,89,67,76,69,67,79,85,78,84,32,40,48,120,49,51,85,41,0
	.data.b	1
	.data.b	61
	.data.b	70,69,69,95,69,95,85,78,73,78,73,84,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	62
	.data.b	70,69,69,95,69,95,73,78,86,65,76,73,68,95,66,76,79,67,75,95,78,79,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	63
	.data.b	70,69,69,95,69,95,73,78,86,65,76,73,68,95,66,76,79,67,75,95,79,70,83,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	64
	.data.b	70,69,69,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	65
	.data.b	70,69,69,95,69,95,73,78,86,65,76,73,68,95,66,76,79,67,75,95,76,69,78,32,40,48,120,48,53,85,41,0
	.data.b	1
	.data.b	66
	.data.b	70,69,69,95,69,95,73,78,73,84,95,70,65,73,76,69,68,32,40,48,120,48,57,85,41,0
	.data.b	1
	.data.b	69
	.data.b	70,69,69,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,48,120,69,48,85,41,0
	.data.b	1
	.data.b	70
	.data.b	70,69,69,95,69,95,85,78,67,79,78,70,73,71,95,66,76,79,67,75,95,69,88,67,69,69,68,69,68,32,40,48,120,69,49,85,41,0
	.data.b	1
	.data.b	74
	.data.b	70,69,69,95,69,95,66,85,83,89,32,40,48,120,48,54,85,41,0
	.data.b	1
	.data.b	75
	.data.b	70,69,69,95,69,95,73,78,86,65,76,73,68,95,67,65,78,67,69,76,32,40,48,120,48,56,85,41,0
	.data.b	1
	.data.b	94
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	95
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	178,1
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	179,1
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	65
	.data.b	14
	.data.b	3
	.data.b	29
	.data.b	15
	.data.b	3
	.data.b	39
	.data.b	16
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	17
	.data.b	3
	.data.b	26
	.data.b	18
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	19
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
	.data.b	19
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	20
	.data.b	3
	.data.b	28
	.data.b	21
	.data.b	3
	.data.b	22
	.data.b	22
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	23
	.data.b	3
	.data.b	56
	.data.b	24
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
	.data.b	25
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
	.data.b	25
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	26
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	27
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
	.data.b	27
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	28
	.data.b	3
	.data.b	34
	.data.b	29
	.data.b	3
	.data.b	31
	.data.b	30
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
	.data.b	31
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
	.data.b	31
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	32
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	31
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
	.data.b	31
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	33
	.data.b	3
	.data.b	38
	.data.b	34
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	35
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
	.data.b	35
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
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	36
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
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
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
	.data.b	68
	.data.b	37
	.data.b	1
	.data.b	28
	.data.b	70,69,69,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	29
	.data.b	70,69,69,95,77,79,68,85,76,69,95,73,68,32,40,50,49,85,41,0
	.data.b	1
	.data.b	31
	.data.b	70,69,69,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	32
	.data.b	70,69,69,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	33
	.data.b	70,69,69,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	35
	.data.b	70,69,69,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	36
	.data.b	70,69,69,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	37
	.data.b	70,69,69,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	69
	.data.b	38
	.data.b	3
	.data.b	37
	.data.b	39
	.data.b	3
	.data.b	39
	.data.b	40
	.data.b	1
	.data.b	65
	.data.b	70,76,83,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	117
	.data.b	70,76,83,95,69,82,65,83,69,95,86,65,76,85,69,32,40,48,120,102,102,85,41,0
	.data.b	1
	.data.b	120
	.data.b	70,76,83,95,67,65,78,67,69,76,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	123
	.data.b	70,76,83,95,83,69,84,95,77,79,68,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	126
	.data.b	70,76,83,95,67,79,77,80,65,82,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	129,1
	.data.b	70,76,83,95,71,69,84,95,74,79,66,95,82,69,83,85,76,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	132,1
	.data.b	70,76,83,95,71,69,84,95,83,84,65,84,85,83,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	135,1
	.data.b	70,76,83,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	138,1
	.data.b	70,76,83,95,66,76,65,78,75,95,67,72,69,67,75,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	144,1
	.data.b	70,76,83,95,85,83,69,95,73,78,84,69,82,82,85,80,84,83,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	153,1
	.data.b	70,76,83,95,84,73,77,69,79,85,84,95,83,85,80,69,82,86,73,83,73,79,78,95,69,78,65,66,76,69,68,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	157,1
	.data.b	70,76,83,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	41
	.data.b	3
	.data.b	26
	.data.b	42
	.data.b	3
	.data.b	37
	.data.b	43
	.data.b	1
	.data.b	102
	.data.b	70,76,65,83,72,95,87,82,95,78,85,77,66,69,82,32,50,0
	.data.b	1
	.data.b	103
	.data.b	70,76,65,83,72,95,80,65,83,83,87,79,82,68,95,78,85,77,66,69,82,32,56,0
	.data.b	4
	.data.b	1
	.data.b	187,1
	.data.b	70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	189,1
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	143,4
	.data.b	68,70,76,65,83,72,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	168,4
	.data.b	70,76,83,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	170,4
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	95
	.data.b	70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	97
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	247,2
	.data.b	70,76,83,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	249,2
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	45
	.data.b	3
	.data.b	35
	.data.b	46
	.data.b	1
	.data.b	217,1
	.data.b	70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	219,1
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	217,4
	.data.b	80,70,76,65,83,72,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	243,4
	.data.b	70,76,83,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	245,4
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	106
	.data.b	70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	108
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	132,4
	.data.b	70,76,83,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	134,4
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	47
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	48
	.data.b	4
	.data.b	1
	.data.b	120
	.data.b	70,76,83,95,82,69,65,68,95,83,85,67,67,69,83,83,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	121
	.data.b	70,76,83,95,82,69,65,68,95,66,85,83,89,32,40,48,120,48,55,85,41,0
	.data.b	1
	.data.b	126
	.data.b	70,76,83,95,67,79,77,80,65,82,69,95,69,81,85,65,76,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	133,1
	.data.b	70,76,83,95,66,76,65,78,75,67,72,69,67,75,95,69,77,80,84,89,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	134,1
	.data.b	70,76,83,95,66,76,65,78,75,67,72,69,67,75,95,68,73,82,84,89,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	156,1
	.data.b	70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	157,1
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,76,83,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	145,2
	.data.b	70,76,83,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	146,2
	.data.b	44
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	117
	.data.b	70,69,69,95,83,84,65,84,69,76,69,83,83,32,40,48,85,41,0
	.data.b	1
	.data.b	119
	.data.b	70,69,69,95,86,65,76,73,68,32,40,49,85,41,0
	.data.b	1
	.data.b	121
	.data.b	70,69,69,95,69,82,65,83,69,68,32,40,50,85,41,0
	.data.b	1
	.data.b	123
	.data.b	70,69,69,95,69,82,65,83,69,68,95,78,79,84,95,85,83,69,68,32,40,52,85,41,0
	.data.b	1
	.data.b	126
	.data.b	70,69,69,95,69,82,65,83,69,68,95,85,83,69,68,32,40,56,85,41,0
	.data.b	1
	.data.b	128,1
	.data.b	70,69,69,95,70,76,83,95,69,82,82,79,82,32,40,49,54,85,41,0
	.data.b	1
	.data.b	131,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,77,65,82,75,69,82,95,83,73,90,69,32,40,70,69,69,95,68,70,76,65,83,72,95,80,65,71,69,95,83,73,90,69,41,0
	.data.b	1
	.data.b	133,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,72,69,65,68,69,82,95,68,65,84,65,95,83,73,90,69,32,40,70,69,69,95,68,70,76,65,83,72,95,80,65,71,69,95,83,73,90,69,41,0
	.data.b	1
	.data.b	135,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,69,82,65,83,69,95,72,69,65,68,69,82,32,40,48,120,52,53,65,55,85,41,0
	.data.b	1
	.data.b	136,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,86,65,76,73,68,95,72,69,65,68,69,82,32,40,48,120,53,54,65,55,85,41,0
	.data.b	1
	.data.b	137,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,68,65,84,65,95,84,65,71,32,40,48,120,65,53,85,41,0
	.data.b	1
	.data.b	138,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,66,65,68,95,84,65,71,32,40,48,120,65,65,85,41,0
	.data.b	1
	.data.b	139,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,77,65,82,75,69,82,95,84,65,71,32,40,48,120,53,65,53,65,53,65,53,65,85,41,0
	.data.b	1
	.data.b	140,1
	.data.b	70,69,69,95,85,78,69,82,65,83,65,66,76,69,95,83,69,67,84,79,82,95,79,70,70,83,69,84,32,40,50,52,85,41,0
	.data.b	1
	.data.b	141,1
	.data.b	70,69,69,95,83,84,65,84,69,80,65,71,69,95,78,85,77,66,69,82,32,40,48,85,41,0
	.data.b	1
	.data.b	143,1
	.data.b	70,69,69,95,85,78,69,82,65,83,65,66,76,69,95,73,78,70,79,95,83,73,90,69,32,40,52,85,41,0
	.data.b	1
	.data.b	145,1
	.data.b	70,69,69,95,77,65,88,95,85,78,69,82,65,83,65,66,76,69,95,73,78,70,79,95,73,78,95,80,65,71,69,32,40,70,69,69,95,68,70,76,65,83,72,95,80,65,71,69,95,83,73,90,69,32,47,32,70,69,69,95
	.data.b	85,78,69,82,65,83,65,66,76,69,95,73,78,70,79,95,83,73,90,69,41,0
	.data.b	1
	.data.b	148,1
	.data.b	70,69,69,95,66,76,79,67,75,95,72,69,65,68,69,82,95,83,73,90,69,32,40,56,85,41,0
	.data.b	1
	.data.b	150,1
	.data.b	70,69,69,95,73,78,86,65,76,73,68,66,76,79,67,75,95,80,65,71,69,95,83,73,90,69,32,40,50,85,41,0
	.data.b	1
	.data.b	152,1
	.data.b	70,69,69,95,66,76,79,67,75,95,72,69,65,68,69,82,95,68,65,84,65,95,83,73,90,69,32,40,56,85,41,0
	.data.b	1
	.data.b	154,1
	.data.b	70,69,69,95,66,76,79,67,75,95,72,69,65,68,69,82,95,84,65,71,32,40,48,120,65,51,85,41,0
	.data.b	1
	.data.b	155,1
	.data.b	70,69,69,95,66,76,79,67,75,95,68,65,84,65,95,84,65,71,32,40,48,120,65,49,85,41,0
	.data.b	1
	.data.b	156,1
	.data.b	70,69,69,95,66,76,79,67,75,95,77,65,82,75,69,82,95,84,65,71,32,40,48,120,53,53,53,53,85,41,0
	.data.b	1
	.data.b	158,1
	.data.b	70,69,69,95,76,79,71,95,66,76,79,67,75,95,78,79,84,95,70,79,85,78,68,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	160,1
	.data.b	70,69,69,95,80,65,71,69,67,79,85,78,84,95,86,69,82,73,70,89,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	163,1
	.data.b	70,69,69,95,69,82,65,83,69,95,86,65,76,85,69,32,40,70,76,83,95,69,82,65,83,69,95,86,65,76,85,69,41,0
	.data.b	1
	.data.b	165,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,80,65,71,69,95,83,73,90,69,32,40,70,69,69,95,86,73,82,84,85,65,76,95,80,65,71,69,95,83,73,90,69,41,0
	.data.b	1
	.data.b	167,1
	.data.b	70,69,69,95,85,83,69,82,95,80,65,71,69,95,66,89,84,69,95,67,79,85,78,84,32,40,40,70,69,69,95,68,70,76,65,83,72,95,80,65,71,69,95,83,73,90,69,32,45,32,70,69,69,95,80,65,71,69,95,79
	.data.b	86,69,82,72,69,65,68,41,41,0
	.data.b	1
	.data.b	169,1
	.data.b	70,69,69,95,87,79,82,68,95,84,79,95,66,89,84,69,95,83,72,73,70,84,32,40,50,85,41,0
	.data.b	1
	.data.b	171,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,87,79,82,68,76,73,78,69,95,83,73,90,69,32,40,50,53,54,85,41,0
	.data.b	1
	.data.b	173,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,83,69,67,84,79,82,95,83,73,90,69,32,40,70,69,69,95,83,69,67,84,79,82,95,83,73,90,69,41,0
	.data.b	1
	.data.b	175,1
	.data.b	70,69,69,95,71,69,84,95,76,79,87,95,66,89,84,69,32,40,48,120,48,48,70,70,85,41,0
	.data.b	1
	.data.b	177,1
	.data.b	70,69,69,95,80,65,71,69,95,67,79,85,78,84,95,77,65,83,75,32,40,48,120,55,70,70,70,85,41,0
	.data.b	1
	.data.b	178,1
	.data.b	70,69,69,95,86,65,76,73,68,95,77,65,83,75,32,40,48,120,56,48,48,48,85,41,0
	.data.b	1
	.data.b	179,1
	.data.b	70,69,69,95,86,65,76,73,68,95,66,73,84,32,40,48,120,56,48,48,48,85,41,0
	.data.b	1
	.data.b	180,1
	.data.b	70,69,69,95,77,65,88,95,82,69,84,82,89,95,84,73,77,69,83,32,40,50,85,41,0
	.data.b	1
	.data.b	181,1
	.data.b	70,69,69,95,79,78,69,95,66,89,84,69,95,83,72,73,70,84,32,40,56,85,41,0
	.data.b	1
	.data.b	182,1
	.data.b	70,69,69,95,84,87,79,95,66,89,84,69,95,83,72,73,70,84,32,40,49,54,85,41,0
	.data.b	1
	.data.b	185,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,95,78,85,77,32,40,50,85,41,0
	.data.b	1
	.data.b	186,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,95,83,69,67,84,79,82,95,78,85,77,32,40,70,69,69,95,83,69,67,84,79,82,95,78,85,77,66,69,82,32,62,62,32,49,85,41,0
	.data.b	1
	.data.b	187,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,95,83,73,90,69,32,40,70,69,69,95,68,70,76,65,83,72,95,83,73,90,69,32,62,62,32,49,85,41,0
	.data.b	1
	.data.b	188,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,48,95,66,65,83,69,32,40,48,85,41,0
	.data.b	1
	.data.b	189,1
	.data.b	70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,49,95,66,65,83,69,32,40,70,69,69,95,68,70,76,65,83,72,95,66,65,78,75,95,83,73,90,69,41,0
	.data.b	1
	.data.b	193,1
	.data.b	70,69,69,95,77,73,78,40,78,117,109,98,101,114,49,44,78,117,109,98,101,114,50,41,32,40,40,40,78,117,109,98,101,114,49,41,32,60,32,40,78,117,109,98,101,114,50,41,41,32,63,32,40,78,117,109,98,101,114,49
	.data.b	41,32,58,32,40,78,117,109,98,101,114,50,41,41,0
	.data.b	1
	.data.b	198,1
	.data.b	70,69,69,95,79,70,70,83,69,84,79,70,83,69,67,84,79,82,40,65,100,100,114,101,115,115,41,32,40,40,65,100,100,114,101,115,115,41,32,38,32,40,70,69,69,95,68,70,76,65,83,72,95,83,69,67,84,79,82,95
	.data.b	83,73,90,69,32,45,32,49,85,41,41,0
	.data.b	1
	.data.b	204,1
	.data.b	70,69,69,95,71,69,84,87,76,66,69,71,73,78,78,73,78,71,40,65,100,100,114,101,115,115,41,32,40,40,65,100,100,114,101,115,115,41,32,38,32,40,126,40,70,69,69,95,68,70,76,65,83,72,95,87,79,82,68,76
	.data.b	73,78,69,95,83,73,90,69,32,45,32,49,85,41,41,41,0
	.data.b	1
	.data.b	210,1
	.data.b	70,69,69,95,71,69,84,83,69,67,84,79,82,66,69,71,73,78,78,73,78,71,40,65,100,100,114,101,115,115,41,32,40,40,65,100,100,114,101,115,115,41,32,38,32,40,126,40,70,69,69,95,68,70,76,65,83,72,95,83
	.data.b	69,67,84,79,82,95,83,73,90,69,32,45,32,49,85,41,41,41,0
	.data.b	1
	.data.b	216,1
	.data.b	70,69,69,95,79,70,70,83,69,84,79,70,87,76,40,65,100,100,114,101,115,115,41,32,40,40,65,100,100,114,101,115,115,41,32,38,32,40,70,69,69,95,68,70,76,65,83,72,95,87,79,82,68,76,73,78,69,95,83,73
	.data.b	90,69,32,45,32,49,85,41,41,0
	.data.b	1
	.data.b	221,1
	.data.b	70,69,69,95,65,68,68,82,84,79,83,69,67,84,79,82,78,85,77,66,69,82,40,65,100,100,114,101,115,115,41,32,40,117,105,110,116,56,41,40,40,65,100,100,114,101,115,115,41,32,62,62,32,70,69,69,95,83,69,67
	.data.b	84,79,82,95,84,79,95,66,89,84,69,95,83,72,73,70,84,41,0
	.data.b	1
	.data.b	226,1
	.data.b	70,69,69,95,77,65,80,65,68,68,82,40,65,100,100,114,101,115,115,41,32,40,70,108,115,95,65,100,100,114,101,115,115,84,121,112,101,41,40,40,40,117,105,110,116,51,50,41,70,101,101,95,83,101,99,116,111,114,82,101
	.data.b	77,97,112,91,70,69,69,95,65,68,68,82,84,79,83,69,67,84,79,82,78,85,77,66,69,82,40,65,100,100,114,101,115,115,41,93,32,60,60,32,70,69,69,95,83,69,67,84,79,82,95,84,79,95,66,89,84,69,95,83
	.data.b	72,73,70,84,41,32,43,32,70,69,69,95,79,70,70,83,69,84,79,70,83,69,67,84,79,82,40,65,100,100,114,101,115,115,41,32,43,32,70,69,69,95,83,84,65,82,84,65,68,68,82,69,83,83,41,0
	.data.b	1
	.data.b	231,1
	.data.b	70,69,69,95,82,69,65,76,65,68,68,82,40,65,100,100,114,101,115,115,41,32,40,70,108,115,95,65,100,100,114,101,115,115,84,121,112,101,41,40,40,65,100,100,114,101,115,115,41,32,43,32,70,69,69,95,83,84,65,82
	.data.b	84,65,68,68,82,69,83,83,41,0
	.data.b	1
	.data.b	236,1
	.data.b	70,69,69,95,67,65,76,80,65,71,69,83,40,83,105,122,101,41,32,40,117,105,110,116,49,54,41,40,40,40,40,117,105,110,116,51,50,41,40,83,105,122,101,41,32,43,32,70,69,69,95,66,76,79,67,75,95,72,69,65
	.data.b	68,69,82,95,68,65,84,65,95,83,73,90,69,32,45,32,50,85,41,32,47,32,70,69,69,95,85,83,69,82,95,80,65,71,69,95,66,89,84,69,95,67,79,85,78,84,41,32,43,32,49,85,41,0
	.data.b	1
	.data.b	241,1
	.data.b	70,69,69,95,71,69,84,82,69,77,65,73,78,80,65,71,69,83,40,66,97,110,107,78,117,109,98,101,114,44,83,116,97,114,116,65,100,100,114,41,32,40,117,105,110,116,49,54,41,40,40,40,70,69,69,95,68,70,76,65
	.data.b	83,72,95,66,65,78,75,95,83,73,90,69,32,60,60,32,40,66,97,110,107,78,117,109,98,101,114,41,41,32,45,32,40,83,116,97,114,116,65,100,100,114,41,32,45,32,40,40,117,105,110,116,51,50,41,70,101,101,95,83
	.data.b	116,97,116,101,46,66,97,110,107,73,110,102,111,80,116,114,91,66,97,110,107,78,117,109,98,101,114,93,46,85,110,101,114,97,115,97,98,108,101,67,111,117,110,116,32,42,32,70,69,69,95,83,69,67,84,79,82,95,83,73
	.data.b	90,69,41,41,32,62,62,32,70,69,69,95,80,65,71,69,95,84,79,95,66,89,84,69,95,83,72,73,70,84,41,59,0
	.data.b	1
	.data.b	246,1
	.data.b	70,69,69,95,82,69,80,79,82,84,69,82,82,79,82,40,65,112,105,73,100,44,69,114,114,111,114,73,100,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,40,70,69,69,95,77,79,68
	.data.b	85,76,69,95,73,68,44,32,70,69,69,95,73,78,83,84,65,78,67,69,95,73,68,44,32,65,112,105,73,100,44,32,69,114,114,111,114,73,100,41,0
	.data.b	1
	.data.b	253,1
	.data.b	70,69,69,95,82,69,80,79,82,84,82,85,78,84,73,77,69,69,82,82,79,82,40,65,112,105,73,100,44,69,114,114,111,114,73,100,41,32,40,118,111,105,100,41,68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109
	.data.b	101,69,114,114,111,114,40,70,69,69,95,77,79,68,85,76,69,95,73,68,44,32,70,69,69,95,73,78,83,84,65,78,67,69,95,73,68,44,32,65,112,105,73,100,44,32,69,114,114,111,114,73,100,41,0
	.data.b	1
	.data.b	133,2
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	144,2
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	172,2
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	184,2
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	188,2
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,56,32,0
	.data.b	3
	.data.b	200,2
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	218,32
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,56,32,0
	.data.b	1
	.data.b	221,32
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	209,2
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,56,32,0
	.data.b	3
	.data.b	221,2
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	239,2
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	241,2
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	236,3
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	238,3
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	245,3
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	247,3
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	150,24
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	152,24
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	158,24
	.data.b	70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,24
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,70,69,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	202,32
	.data.b	70,69,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	204,32
	.data.b	13
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 429
	.data.b	0
