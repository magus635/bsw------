	.section ".sdk_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257B..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.
Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.:
Safewdt_Hal_CalculateDynamicPassword:
.LDW01:
.LDW11:
	cmp	r1,1
	lsreq	r2,r0,12
	eoreq	r1,r2,r0 lsr 13
	eoreq	r1,r1,r0 lsr 11
	eoreq	r1,r1,r0 lsr 2
	ubfxeq	r2,r0,0,13
	moveq	r0,r1
	eorne	r0,r0,63
	bfieq	r0,r2,1,31
.LDW21:
.L127:

	ret	
__ghs_eofn_Safewdt_Hal_CalculateDynamicPassword:
	.endf	Safewdt_Hal_CalculateDynamicPassword
	.endf	Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.

;prePassword	r0	param
;pwMode	r1	param

	.section ".bss","awb"
.L88:
	.endo	.L88
	.section ".ghrettbl",""
	.align	4
.L128:	.data.w	.L127
	.endo	.L128
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
__callee.Safewdt_Hal_InitWdt.i.p::
	.size	__callee.Safewdt_Hal_InitWdt.i.p,0
Safewdt_Hal_InitWdt::
.LDW31:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW41:
.L951:

	bl	Safewdt_Std_ClearPw0
	ldr	r3,[r5,28]
	and	r4,r0,1
	ldr	r2,.L950
	cmp	r3,0
	ldrhne	r1,[r5]
	ldrne	r0,[r2,8]
	bfine	r0,r1,0,14
	strne	r0,[r2,8]
	ldrne	r0,[r2,8]
	ubfxne	r0,r0,0,14
	cmpne	r1,r0
	movne	r4,0
.L133:
	ldr	r0,[r2,8]
	bfi	r0,r3,14,2
	str	r0,[r2,8]
	mov	r1,r4
	ldr	r0,[r2,8]
	ubfx	r0,r0,14,2
	cmp	r3,r0
	movne	r1,0
	ldr	r0,[r5,20]
	str	r0,[r2,80]
	ldr	r3,[r2,80]
	cmp	r0,r3
	movne	r1,0
	ldr	r3,[r5,32]
	ldr	r0,[r2,72]
	bfi	r0,r3,0,3
	str	r0,[r2,72]
	mov	r4,r1
	ldr	r0,[r2,72]
	and	r0,r0,7
	cmp	r3,r0
	movne	r4,0
	ldr	r1,[r5,24]
	ldr	r0,[r2,76]
	bfi	r0,r1,1,1
	str	r0,[r2,76]
	ldr	r0,[r2,76]
	ubfx	r0,r0,1,1
	cmp	r1,r0
	movne	r4,0
	ldr	r1,[r5,4]
	ldr	r0,[r2,40]
	cmp	r1,0
	bne	.L164
	bic	r0,r0,1
	str	r0,[r2,40]
	ldr	r0,[r2,40]
	tst	r0,1
	movne	r4,r1
	str	r1,[r2,44]
	ldr	r0,[r2,44]
	cmp	r0,0
	movne	r4,r1
	b	.L178
.L164:
	orr	r0,r0,1
	str	r0,[r2,40]
	ldr	r0,[r2,40]
	and	r0,r0,1
	cmp	r0,1
	movne	r4,0
	str	r1,[r2,44]
	ldr	r0,[r2,44]
	cmp	r1,r0
	movne	r4,0
.L178:
	ldr	r1,[r5,8]
	ldr	r0,[r2,40]
	cmp	r1,0
	bne	.L191
	bic	r0,r0,2
	str	r0,[r2,40]
	ldr	r0,[r2,40]
	tst	r0,2
	movne	r4,r1
	str	r1,[r2,52]
	ldr	r0,[r2,52]
	cmp	r0,0
	movne	r4,r1
	b	.L205
.L191:
	orr	r0,r0,2
	str	r0,[r2,40]
	ldr	r0,[r2,40]
	and	r0,r0,2
	cmp	r0,2
	movne	r4,0
	str	r1,[r2,52]
	ldr	r0,[r2,52]
	cmp	r1,r0
	movne	r4,0
.L205:
	ldr	r0,[r5,12]
	str	r0,[r2,48]
	ldr	r1,[r2,48]
	cmp	r0,r1
	movne	r4,0
	ldr	r0,[r5,16]
	str	r0,[r2,56]
	ldr	r1,[r2,56]
	cmp	r0,r1
	movne	r4,0
.L953:

	bl	Safewdt_Std_SetPw0
	and	r0,r4,r0
.LDW51:
.L955:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Safewdt_Hal_InitWdt::
	.endf	Safewdt_Hal_InitWdt
;ret	r4	local
;ret	r4	local
;ret	r1	local
;ret	r1	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local
;ret	r4	local

;pConfig	r5	param

	.section ".bss","awb"
.L644:
	.endo	.L644
	.section ".ghcalltbl",""
	.align	4
.L952:	.data.w	.L951
	.endo	.L952
.L954:	.data.w	.L953
	.endo	.L954
	.section ".ghrettbl",""
.L956:	.data.w	.L955
	.endo	.L956
	.data
	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
__callee.Safewdt_Hal_InitSafetyEndinit.i.p::
	.size	__callee.Safewdt_Hal_InitSafetyEndinit.i.p,0
Safewdt_Hal_InitSafetyEndinit::
.LDW61:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW71:
.L1362:

	bl	Safewdt_Std_ClearPw0
	and	r1,r0,1
	ldr	r0,[r6,4]
	ldr	r5,.L950
	str	r0,[r5,80]
	ldr	r2,[r5,80]
	cmp	r2,r0
	movne	r1,0
	ldr	r0,[r5,8]
	ldr	r2,[r6,12]
	bfc	r0,30,2
	orr	r0,r0,r2 lsl 30
	cmp	r2,0
	str	r0,[r5,8]
	ldrhne	r3,[r6]
	ldrne	r0,[r5,8]
	bfine	r0,r3,16,14
	strne	r0,[r5,8]
	ldrne	r0,[r5,8]
	ubfxne	r0,r0,16,14
	cmpne	r0,r3
	movne	r1,0
.L967:
	ldr	r0,[r5,8]
	cmp	r2,r0 lsr 30
	movne	r1,0
	ldr	r2,[r6,16]
	ldr	r0,[r5,72]
	bfi	r0,r2,3,3
	str	r0,[r5,72]
	ldr	r0,[r5,72]
	ubfx	r0,r0,3,3
	cmp	r0,r2
	movne	r1,0
	ldr	r2,[r6,8]
	ldr	r0,[r5,76]
	bfi	r0,r2,0,1
	str	r0,[r5,76]
	mov	r4,r1
	ldr	r0,[r5,76]
	and	r0,r0,1
	cmp	r0,r2
	movne	r4,0
	ldrh	r0,[r6,2]
	str	r0,[r5,20]
	ldr	r1,[r5,20]
	cmp	r1,r0
	movne	r4,0
.L1364:

	bl	Safewdt_Std_SetPw0
	and	r4,r4,r0
.L1366:

	bl	Safewdt_Std_ClearPwse
	and	r4,r4,r0
	mov	r0,3
	str	r0,[r5,28]
	ldr	r0,[r5,28]
	cmp	r0,3
	movne	r4,0
.L1368:

	bl	Safewdt_Std_SetPwse
	and	r0,r4,r0
.LDW81:
.L1370:

	pop	{r4-r6,pc}
__ghs_eofn_Safewdt_Hal_InitSafetyEndinit::
	.endf	Safewdt_Hal_InitSafetyEndinit
;ret	r4	local
;ret	r1	local
;ret	r1	local
;ret	r1	local
;ret	r1	local
;ret	r4	local
;ret	r4	local
;ret	r4	local

;pConfig	r6	param

	.section ".bss","awb"
.L1218:
	.endo	.L1218
	.section ".ghcalltbl",""
.L1363:	.data.w	.L1362
	.endo	.L1363
.L1365:	.data.w	.L1364
	.endo	.L1365
.L1367:	.data.w	.L1366
	.endo	.L1367
.L1369:	.data.w	.L1368
	.endo	.L1369
	.section ".ghrettbl",""
.L1371:	.data.w	.L1370
	.endo	.L1371
	.data
	.global	__caller.Safewdt_Std_SetPwse.i.v

	.global	__caller.Safewdt_Std_ClearPwse.i.v

	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
__callee.Safewdt_Hal_GetWdtPassword.i.v::
	.size	__callee.Safewdt_Hal_GetWdtPassword.i.v,0
Safewdt_Hal_GetWdtPassword::
.LDW91:
.LDW02:
	ldr	r0,.L1468
	ldr	r1,[r0]
	ldr	r0,[r0,52]
	lsl	r1,r1,16
	lsrs	r1,r1,30
	moveq	r0,0x0b40
	uxthne	r0,r0
.L1469:

	bne	Safewdt_Hal_CalculateDynamicPassword
.L1372:
.LDW12:
.L1471:

	ret	
__ghs_eofn_Safewdt_Hal_GetWdtPassword::
	.endf	Safewdt_Hal_GetWdtPassword
;wdtMode	r1	local
;prePassword	r0	local

	.section ".bss","awb"
.L1426:
	.endo	.L1426
	.section ".ghtailcalltbl",""
	.align	4
.L1470:	.data.w	.L1469
	.endo	.L1470
	.section ".ghrettbl",""
.L1472:	.data.w	.L1471
	.endo	.L1472
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
__callee.Safewdt_Hal_EnableWdt.i.v::
	.size	__callee.Safewdt_Hal_EnableWdt.i.v,0
Safewdt_Hal_EnableWdt::
.LDW22:
	push	{r4-r6,lr}
	sub	sp,sp,16
.LDW32:
	ldr	r0,.L1656
	mov	r1,sp
	add	r2,r0,16
.L1564:
	ldr	r3,[r0],4
	cmp	r2,r0
	str	r3,[r1],4
	bne	.L1564
	ldr	r1,.L1657
	ldr	r0,[r1]
	tst	r0,1
	bne	.L1475
.L1663:

	bl	Safewdt_Std_ClearPwwdt
	ldr	r1,.L1658
	and	r4,r0,1
	mov	r0,3
	str	r0,[r1]
	str	r0,[r1,4]
.L1665:

	bl	Safewdt_Std_SetPwwdt
	b	.L1477
.L1475:
	ldr	r1,.L1659
	ldr	r0,[r1]
	and	r0,r0,7
	cmp	r0,4
	ldrlo	r1,[sp,r0 lsl 2]
	movhs	r6,6
	rsblo	r0,r1,r1 lsl 2
	lsllo	r6,r0,1
	ldr	r0,.L1660
	ldr	r5,[r0]
.L1667:

	bl	Safewdt_Std_ClearPw0
	ldr	r1,.L1660
	and	r4,r0,1
	mov	r0,0
	str	r0,[r1]
.L1669:

	bl	Safewdt_Std_SetPw0
	and	r4,r4,r0
.L1671:

	bl	Safewdt_Std_ClearPwwdt
	ldr	r2,.L1658
	and	r4,r4,r0
	mov	r0,3
	str	r0,[r2]
	str	r0,[r2,4]
.L1673:

	bl	Safewdt_Std_SetPwwdt
	and	r4,r4,r0
	b	.L1661

.L950:	.data.w	0xc0040800
	.endo	.L950

.L1468:	.data.w	0xc0040808
	.endo	.L1468

.L1656:	.data.w	.L1590
	.endo	.L1656

.L1657:	.data.w	0xc0040828
	.endo	.L1657

.L1658:	.data.w	0xc0040840
	.endo	.L1658

.L1659:	.data.w	0xc0040848
	.endo	.L1659

.L1660:	.data.w	0xc004082c
	.endo	.L1660

.L1661:

;line435
..lin.8c7caeaa..b9bbbbc.0_1::
.LDWlin1:
..gh.beginasm.5:
	.endo	..gh.beginasm.5
1:               
 SUBS r6, r6, #1 
NOP              
 BNE 1b          

..gh.endasm.6:
	.endo	..gh.endasm.6

.L1675:

;line449
..lin.8c7caeaa..b9bbbbc.0_2::
.LDWlin2:
	bl	Safewdt_Std_ClearPw0
	ldr	r6,.L1662
	and	r4,r4,r0
	str	r5,[r6]
.L1677:

	bl	Safewdt_Std_SetPw0
.L1477:
	and	r0,r4,r0
.LDW42:
	add	sp,sp,16
.L1679:

	pop	{r4-r6,pc}
__ghs_eofn_Safewdt_Hal_EnableWdt::
	.endf	Safewdt_Hal_EnableWdt
;ret	r4	local
;thv	r5	local
;clkDiv	r6	local
;index	r0	local
;wdtFactors	[sp]	local
;.L1563	.L1590	static

	.section ".bss","awb"
.L1562:
	.endo	.L1562
	.section ".rodata","a"
	.align	4
.L1590:	.data.b	1,0,0,0
	.data.b	64,0,0,0
	.data.b	0,1,0,0
	.data.b	0,64,0,0
	.endo	.L1590
	.section ".ghcalltbl",""
.L1664:	.data.w	.L1663
	.endo	.L1664
.L1666:	.data.w	.L1665
	.endo	.L1666
.L1668:	.data.w	.L1667
	.endo	.L1668
.L1670:	.data.w	.L1669
	.endo	.L1670
.L1672:	.data.w	.L1671
	.endo	.L1672
.L1674:	.data.w	.L1673
	.endo	.L1674
.L1676:	.data.w	.L1675
	.endo	.L1676
.L1678:	.data.w	.L1677
	.endo	.L1678
	.section ".ghrettbl",""
.L1680:	.data.w	.L1679
	.endo	.L1680
	.data
	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.global	__caller.Safewdt_Std_SetPwwdt.i.v

	.global	__caller.Safewdt_Std_ClearPwwdt.i.v

	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.global	__caller.Safewdt_Std_SetPwwdt.i.v

	.global	__caller.Safewdt_Std_ClearPwwdt.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
__callee.Safewdt_Hal_ServiceWdt.i.v::
	.size	__callee.Safewdt_Hal_ServiceWdt.i.v,0
Safewdt_Hal_ServiceWdt::
.LDW52:
	push	{r4,lr}
.LDW62:
.L1747:

	bl	Safewdt_Std_ClearPwwdt
	ldr	r1,.L1746
	and	r4,r0,1
	mov	r0,3
	str	r0,[r1]
.L1749:

	bl	Safewdt_Std_SetPwwdt
	and	r0,r4,r0
.LDW72:
.L1751:

	pop	{r4,pc}
__ghs_eofn_Safewdt_Hal_ServiceWdt::
	.endf	Safewdt_Hal_ServiceWdt
;ret	r4	local

	.section ".bss","awb"
.L1722:
	.endo	.L1722
	.section ".ghcalltbl",""
.L1748:	.data.w	.L1747
	.endo	.L1748
.L1750:	.data.w	.L1749
	.endo	.L1750
	.section ".ghrettbl",""
.L1752:	.data.w	.L1751
	.endo	.L1752
	.data
	.global	__caller.Safewdt_Std_SetPwwdt.i.v

	.global	__caller.Safewdt_Std_ClearPwwdt.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
__callee.Safewdt_Hal_DisableWdt.i.v::
	.size	__callee.Safewdt_Hal_DisableWdt.i.v,0
Safewdt_Hal_DisableWdt::
.LDW82:
	push	{r2,r4-r9,lr}
.LDW92:
	ldr	r4,.L2152
	ldr	r6,[r4,112]
	ldr	r7,[r4,112]
	ldr	r8,[r4,116]
	mov	r5,0
	ubfx	r6,r6,2,2
	ubfx	r7,r7,4,2
	ubfx	r8,r8,2,2
.L2154:

	bl	Safewdt_Std_ClearPw0
	and	r9,r0,1
	ldr	r0,[r4,112]
	orr	r0,r0,12
	str	r0,[r4,112]
	ldr	r0,[r4,112]
	orr	r0,r0,48
	str	r0,[r4,112]
	ldr	r0,[r4,116]
	orr	r0,r0,12
	str	r0,[r4,116]
.L2156:

	bl	Safewdt_Std_SetPw0
	and	r9,r9,r0
	ldr	r0,[r4,112]
	and	r0,r0,12
	mov	r1,r9
	cmp	r0,12
	movne	r1,r5
	ldr	r0,[r4,112]
	and	r9,r9,r1
	and	r0,r0,48
	mov	r1,r9
	cmp	r0,48
	movne	r1,r5
	ldr	r0,[r4,116]
	and	r9,r9,r1
	and	r0,r0,12
	mov	r1,r9
	cmp	r0,12
	movne	r1,r5
	and	r9,r9,r1
.L2158:

	bl	Safewdt_Std_ClearPwwdt
	and	r9,r9,r0
	str	r5,[r4,64]
.L2160:

	bl	Safewdt_Std_SetPwwdt
	and	r9,r9,r0
	b	.L1773
.L1775:
	add	r5,r5,1
.L1773:
	ldr	r0,[r4,88]
	cmp	r0,0
	ldrne	r0,.L2153
	cmpne	r5,r0
	blo	.L1775
.L2162:

	bl	Safewdt_Std_ClearPw0
	and	r9,r9,r0
	ldr	r0,[r4,112]
	bfi	r0,r6,2,2
	str	r0,[r4,112]
	ldr	r0,[r4,112]
	bfi	r0,r7,4,2
	str	r0,[r4,112]
	ldr	r0,[r4,116]
	bfi	r0,r8,2,2
	str	r0,[r4,116]
.L2164:

	bl	Safewdt_Std_SetPw0
	and	r9,r9,r0
	ldr	r0,[r4,112]
	ubfx	r0,r0,2,2
	mov	r1,r9
	cmp	r6,r0
	movne	r1,0
	ldr	r0,[r4,112]
	and	r9,r9,r1
	ubfx	r0,r0,4,2
	mov	r1,r9
	cmp	r7,r0
	movne	r1,0
	ldr	r0,[r4,116]
	and	r9,r9,r1
	ubfx	r0,r0,2,2
	mov	r1,r9
	cmp	r8,r0
	movne	r1,0
	ldr	r0,.L2153
	and	r9,r9,r1
	cmp	r5,r0
	movhs	r9,0
	mov	r0,r9
.LDW03:
.L2166:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Safewdt_Hal_DisableWdt::
	.endf	Safewdt_Hal_DisableWdt
;ret	r9	local
;timeOutCnt	r5	local
;almMask1	r6	local
;almMask2	r7	local
;intMask	r8	local
;ret	r1	local
;ret	r1	local
;ret	r1	local
;ret	r1	local
;ret	r1	local
;ret	r1	local

	.section ".bss","awb"
.L1990:
	.endo	.L1990
	.section ".ghcalltbl",""
.L2155:	.data.w	.L2154
	.endo	.L2155
.L2157:	.data.w	.L2156
	.endo	.L2157
.L2159:	.data.w	.L2158
	.endo	.L2159
.L2161:	.data.w	.L2160
	.endo	.L2161
.L2163:	.data.w	.L2162
	.endo	.L2163
.L2165:	.data.w	.L2164
	.endo	.L2165
	.section ".ghrettbl",""
.L2167:	.data.w	.L2166
	.endo	.L2167
	.data
	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.global	__caller.Safewdt_Std_SetPwwdt.i.v

	.global	__caller.Safewdt_Std_ClearPwwdt.i.v

	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
__callee.Safewdt_Hal_ChangeHighThv.i.ii::
	.size	__callee.Safewdt_Hal_ChangeHighThv.i.ii,0
Safewdt_Hal_ChangeHighThv::
.LDW13:
	push	{r4-r6,lr}
	mov	r6,r0
	mov	r5,r1
.LDW23:
.L2310:

	bl	Safewdt_Hal_DisableWdt
	and	r4,r0,1
.L2312:

	bl	Safewdt_Std_ClearPw0
	and	r4,r4,r0
	ldr	r0,.L2308
	str	r6,[r0]
	str	r5,[r0,8]
.L2314:

	bl	Safewdt_Std_SetPw0
	ldr	r3,.L2308
	and	r2,r4,r0
	ldr	r0,[r3]
	cmp	r6,r0
	movne	r2,0
	ldr	r1,.L2309
	ldr	r0,[r1]
	mov	r4,r2
	cmp	r5,r0
	movne	r4,0
.L2316:

	bl	Safewdt_Hal_EnableWdt
	and	r0,r4,r0
.LDW33:
.L2318:

	pop	{r4-r6,pc}
__ghs_eofn_Safewdt_Hal_ChangeHighThv::
	.endf	Safewdt_Hal_ChangeHighThv
;ret	r4	local
;ret	r2	local
;ret	r4	local

;newHighThv0	r6	param
;newHighThv1	r5	param

	.section ".bss","awb"
.L2254:
	.endo	.L2254
	.section ".ghcalltbl",""
.L2311:	.data.w	.L2310
	.endo	.L2311
.L2313:	.data.w	.L2312
	.endo	.L2313
.L2315:	.data.w	.L2314
	.endo	.L2315
.L2317:	.data.w	.L2316
	.endo	.L2317
	.section ".ghrettbl",""
.L2319:	.data.w	.L2318
	.endo	.L2319
	.data
	.global	__caller.Safewdt_Hal_EnableWdt.i.v

	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.global	__caller.Safewdt_Hal_DisableWdt.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
__callee.Safewdt_Hal_GetAlarmFlagStatus.i.i::
	.size	__callee.Safewdt_Hal_GetAlarmFlagStatus.i.i,0
Safewdt_Hal_GetAlarmFlagStatus::
.LDW43:
.LDW53:
	ldr	r2,.L2397
	ldr	r1,[r2]
	ands	r0,r1,r0
	movne	r0,1
.LDW63:
.L2398:

	ret	
__ghs_eofn_Safewdt_Hal_GetAlarmFlagStatus::
	.endf	Safewdt_Hal_GetAlarmFlagStatus

;flag	r0	param

	.section ".bss","awb"
.L2379:
	.endo	.L2379
	.section ".ghrettbl",""
.L2399:	.data.w	.L2398
	.endo	.L2399
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
__callee.Safewdt_Hal_GetInterruptFlagStatus.i.i::
	.size	__callee.Safewdt_Hal_GetInterruptFlagStatus.i.i,0
Safewdt_Hal_GetInterruptFlagStatus::
.LDW73:
.LDW83:
	ldr	r2,.L2477
	ldr	r1,[r2]
	ands	r0,r1,r0
	movne	r0,1
.LDW93:
.L2478:

	ret	
__ghs_eofn_Safewdt_Hal_GetInterruptFlagStatus::
	.endf	Safewdt_Hal_GetInterruptFlagStatus

;flag	r0	param

	.section ".bss","awb"
.L2459:
	.endo	.L2459
	.section ".ghrettbl",""
.L2479:	.data.w	.L2478
	.endo	.L2479
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
__callee.Safewdt_Hal_GetPwAndLpFlagStatus.i.i::
	.size	__callee.Safewdt_Hal_GetPwAndLpFlagStatus.i.i,0
Safewdt_Hal_GetPwAndLpFlagStatus::
.LDW04:
.LDW14:
	ldr	r2,.L2557
	ldr	r1,[r2]
	ands	r0,r1,r0
	movne	r0,1
.LDW24:
.L2558:

	ret	
__ghs_eofn_Safewdt_Hal_GetPwAndLpFlagStatus::
	.endf	Safewdt_Hal_GetPwAndLpFlagStatus

;flag	r0	param

	.section ".bss","awb"
.L2539:
	.endo	.L2539
	.section ".ghrettbl",""
.L2559:	.data.w	.L2558
	.endo	.L2559
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
__callee.Safewdt_Hal_ClearFlagStatus.i.i::
	.size	__callee.Safewdt_Hal_ClearFlagStatus.i.i,0
Safewdt_Hal_ClearFlagStatus::
.LDW34:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW44:
.L2627:

	bl	Safewdt_Std_ClearPw0
	and	r4,r0,1
	ldr	r0,.L2626
	str	r5,[r0]
.L2629:

	bl	Safewdt_Std_SetPw0
	and	r0,r4,r0
.LDW54:
.L2631:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Safewdt_Hal_ClearFlagStatus::
	.endf	Safewdt_Hal_ClearFlagStatus
;ret	r4	local

;flag	r5	param

	.section ".bss","awb"
.L2602:
	.endo	.L2602
	.section ".ghcalltbl",""
.L2628:	.data.w	.L2627
	.endo	.L2628
.L2630:	.data.w	.L2629
	.endo	.L2630
	.section ".ghrettbl",""
.L2632:	.data.w	.L2631
	.endo	.L2632
	.data
	.global	__caller.Safewdt_Std_SetPw0.i.v

	.global	__caller.Safewdt_Std_ClearPw0.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
__callee.Safewdt_Hal_GetSePassword.i.v::
	.size	__callee.Safewdt_Hal_GetSePassword.i.v,0
Safewdt_Hal_GetSePassword::
.LDW64:
.LDW74:
	ldr	r0,.L2732
	ldr	r1,[r0]
	ldr	r0,[r0,16]
	lsrs	r1,r1,30
	moveq	r0,11<<10
	uxthne	r0,r0
.L2733:

	bne	Safewdt_Hal_CalculateDynamicPassword
.L2633:
.LDW84:
.L2735:

	ret	
__ghs_eofn_Safewdt_Hal_GetSePassword::
	.endf	Safewdt_Hal_GetSePassword
;seMode	r1	local
;prePassword	r0	local

	.section ".bss","awb"
.L2690:
	.endo	.L2690
	.section ".ghtailcalltbl",""
.L2734:	.data.w	.L2733
	.endo	.L2734
	.section ".ghrettbl",""
.L2736:	.data.w	.L2735
	.endo	.L2736
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
__callee.Safewdt_Hal_ClearSafetyEndinit.i.v::
	.size	__callee.Safewdt_Hal_ClearSafetyEndinit.i.v,0
Safewdt_Hal_ClearSafetyEndinit::
.LDW94:
	push	{r4-r6,lr}
.LDW05:
	mov	r6,0
.L2982:

	bl	Safewdt_Std_ClearPwse
	ldr	r5,.L2152
	and	r4,r0,1
	ldr	r0,[r5,28]
	cmp	r0,3
	movne	r0,3
	strne	r0,[r5,28]
	ldrne	r0,[r5,28]
	cmpne	r0,3
	movne	r4,r6
.L2739:
	ldr	r0,[r5,32]
	orr	r0,r0,3
	str	r0,[r5,32]
.L2984:

	bl	Safewdt_Std_SetPwse
	and	r4,r4,r0
.L2747:
	ldr	r0,[r5,84]
	tst	r0,1<<16
	ldr	r0,.L2981
	beq	.L2748
	cmp	r6,r0
	bhs	.L2752
	add	r6,r6,1
	b	.L2747
.L2748:
	cmp	r6,r0
.L2752:
	movhs	r4,0
.L2751:
	mov	r0,r4
.LDW15:
.L2986:

	pop	{r4-r6,pc}
__ghs_eofn_Safewdt_Hal_ClearSafetyEndinit::
	.endf	Safewdt_Hal_ClearSafetyEndinit
;timeOutCnt	r6	local
;ret	r4	local
;ret	r4	local

	.section ".bss","awb"
.L2873:
	.endo	.L2873
	.section ".ghcalltbl",""
.L2983:	.data.w	.L2982
	.endo	.L2983
.L2985:	.data.w	.L2984
	.endo	.L2985
	.section ".ghrettbl",""
.L2987:	.data.w	.L2986
	.endo	.L2987
	.data
	.global	__caller.Safewdt_Std_SetPwse.i.v

	.global	__caller.Safewdt_Std_ClearPwse.i.v

	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
__callee.Safewdt_Hal_SetSafetyEndinit.i.v::
	.size	__callee.Safewdt_Hal_SetSafetyEndinit.i.v,0
Safewdt_Hal_SetSafetyEndinit::
.LDW25:
	push	{r2,r4-r5,lr}
.LDW35:
	mov	r5,0
.L3171:

	bl	Safewdt_Std_ClearPwse
	ldr	r1,.L3169
	and	r4,r0,1
	ldr	r0,[r1]
	orr	r0,r0,12
	str	r0,[r1]
.L3173:

	bl	Safewdt_Std_SetPwse
	and	r4,r4,r0
.L2990:
	ldr	r1,.L3170
	ldr	r0,[r1]
	tst	r0,1<<16
	ldr	r0,.L2981
	bne	.L2991
	cmp	r5,r0
	bhs	.L2995
	add	r5,r5,1
	b	.L2990
.L2991:
	cmp	r5,r0
.L2995:
	movhs	r4,0
.L2994:
	mov	r0,r4
.LDW45:
.L3175:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Safewdt_Hal_SetSafetyEndinit::
	.endf	Safewdt_Hal_SetSafetyEndinit
;timeOutCnt	r5	local
;ret	r4	local

	.section ".bss","awb"
.L3091:
	.endo	.L3091
	.section ".ghcalltbl",""
.L3172:	.data.w	.L3171
	.endo	.L3172
.L3174:	.data.w	.L3173
	.endo	.L3174
	.section ".ghrettbl",""
.L3176:	.data.w	.L3175
	.endo	.L3176
	.data
	.global	__caller.Safewdt_Std_SetPwse.i.v

	.global	__caller.Safewdt_Std_ClearPwse.i.v

	.section ".sdk_text_asil_d","ax"

.L1662:	.data.w	0xc004082c
	.endo	.L1662

.L1746:	.data.w	0xc0040844
	.endo	.L1746

.L2152:	.data.w	0xc0040800
	.endo	.L2152

.L2153:	.data.w	0x03200600
	.endo	.L2153

.L2308:	.data.w	0xc0040830
	.endo	.L2308

.L2309:	.data.w	0xc0040838
	.endo	.L2309

.L2397:	.data.w	0xc0040860
	.endo	.L2397

.L2477:	.data.w	0xc0040864
	.endo	.L2477

.L2557:	.data.w	0xc004085c
	.endo	.L2557

.L2626:	.data.w	0xc004086c
	.endo	.L2626

.L2732:	.data.w	0xc0040808
	.endo	.L2732

.L2981:	.data.w	0x01800600
	.endo	.L2981

.L3169:	.data.w	0xc0040820
	.endo	.L3169

.L3170:	.data.w	0xc0040854
	.endo	.L3170


	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257B..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	48,30,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,115,114,99,47,115,97,102,101,119,100,116,95,104,97,108,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 38
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+38
	.section	.debug_str		;off: 182
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+182
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
	.data.b	32,5,0,0
	.data.b	2,0
	.data.b	24,2,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,115,114,99,47,115,97,102,101,119,100,116,95,104,97,108,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,105,110,99,92,115,97,102,101,119,100,116,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,97,102,101,119,100,116,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,105,110,99,92,115,97,102,101,119,100,116,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,102,101,119,100,116,92,105,110,99,92,115,97,102,101,119,100,116,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
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
	.section	.debug_str		;off: 204
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 36
	.data.w	.Ldw_str_begin+204
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
	.section	.debug_str		;off: 218
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+218
	.data.b	7
	.data.b	4

	.data.b	74
	.data.w	.Ldw_begin+358
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
	.data.w	.Ldw_begin+358
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
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 232
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 75
	.data.w	.Ldw_str_begin+232
	.data.b	7
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+370
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+370
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+500
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1090

	.section	.debug_abbrev		;off: 48
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 105
	.data.b	53
	.data.w	.Ldw_begin+100

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 110
	.data.b	47
	.data.w	.Ldw_begin+105

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+110
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1213

	.data.b	53
	.data.w	.Ldw_begin+128

	.data.b	47
	.data.w	.Ldw_begin+133

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+138
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+370
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 247
	.data.b	105,110,116,0
	.section	.debug_info		;off: 171
	.data.w	.Ldw_str_begin+247
	.data.b	5
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+382

	.section	.debug_abbrev		;off: 62
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 182
	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+177

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 189
	.data.b	56
	.data.w	.Ldw_begin+170
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

	.section	.debug_info		;off: 197
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+641
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+709
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+641
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+750
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+641
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+791
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+916
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+370
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 251
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 305
	.data.w	.Ldw_str_begin+251
	.data.b	7
	.data.b	4

	.data.b	49
	.data.w	.Ldw_begin+5594

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+358
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 264
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 359
	.data.w	.Ldw_str_begin+264
	.data.b	51
	.data.b	29
	.data.b	6
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

	.section	.debug_info		;off: 370
	.data.b	45
	.section	.debug_str		;off: 272
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 371
	.data.w	.Ldw_str_begin+272
	.data.b	60
	.data.b	29
	.data.b	6
	.data.w	.Ldw_begin+74

	.data.b	45
	.section	.debug_str		;off: 279
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 383
	.data.w	.Ldw_str_begin+279
	.data.b	64
	.data.b	29
	.data.b	6
	.data.w	.Ldw_begin+42

	.data.b	52
	.section	.debug_str		;off: 286
	.data.b	0
	.section	.debug_info		;off: 395
	.data.w	.Ldw_str_begin+286
	.data.b	49
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 108
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

	.section	.debug_info		;off: 404
	.data.b	51
	.section	.debug_str		;off: 287
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,48,0
	.section	.debug_info		;off: 405
	.data.w	.Ldw_str_begin+287
	.data.b	50
	.data.b	5
	.data.b	5
	.data.b	0

	.section	.debug_abbrev		;off: 125
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 413
	.data.b	51
	.section	.debug_str		;off: 307
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,49,0
	.section	.debug_info		;off: 414
	.data.w	.Ldw_str_begin+307
	.data.b	52
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 327
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,50,0
	.section	.debug_info		;off: 423
	.data.w	.Ldw_str_begin+327
	.data.b	54
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 347
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,51,0
	.section	.debug_info		;off: 432
	.data.w	.Ldw_str_begin+347
	.data.b	55
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 367
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 441
	.data.w	.Ldw_str_begin+367
	.data.b	58
	.data.b	5
	.data.b	5
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 390
	.data.b	83,97,102,101,119,100,116,95,83,97,102,101,67,112,117,73,100,0
	.section	.debug_info		;off: 451
	.data.w	.Ldw_str_begin+390
	.data.b	59
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+394

	.data.b	52
	.section	.debug_str		;off: 408
	.data.b	0
	.section	.debug_info		;off: 463
	.data.w	.Ldw_str_begin+408
	.data.b	63
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 409
	.data.b	83,65,70,69,87,68,84,95,80,87,77,79,68,69,95,70,73,88,69,68,0
	.section	.debug_info		;off: 473
	.data.w	.Ldw_str_begin+409
	.data.b	64
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 430
	.data.b	83,65,70,69,87,68,84,95,80,87,77,79,68,69,95,68,89,78,65,77,73,67,95,49,0
	.section	.debug_info		;off: 482
	.data.w	.Ldw_str_begin+430
	.data.b	65
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 455
	.data.b	83,65,70,69,87,68,84,95,80,87,77,79,68,69,95,68,89,78,65,77,73,67,95,50,0
	.section	.debug_info		;off: 491
	.data.w	.Ldw_str_begin+455
	.data.b	66
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 480
	.data.b	83,97,102,101,119,100,116,95,80,119,77,111,100,101,0
	.section	.debug_info		;off: 501
	.data.w	.Ldw_str_begin+480
	.data.b	67
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+462

	.data.b	52
	.section	.debug_str		;off: 495
	.data.b	0
	.section	.debug_info		;off: 513
	.data.w	.Ldw_str_begin+495
	.data.b	71
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 496
	.data.b	83,65,70,69,87,68,84,95,67,76,75,68,73,86,95,84,72,82,79,85,71,72,0
	.section	.debug_info		;off: 523
	.data.w	.Ldw_str_begin+496
	.data.b	72
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 519
	.data.b	83,65,70,69,87,68,84,95,67,76,75,68,73,86,95,54,52,0
	.section	.debug_info		;off: 532
	.data.w	.Ldw_str_begin+519
	.data.b	73
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 537
	.data.b	83,65,70,69,87,68,84,95,67,76,75,68,73,86,95,50,53,54,0
	.section	.debug_info		;off: 541
	.data.w	.Ldw_str_begin+537
	.data.b	74
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 556
	.data.b	83,65,70,69,87,68,84,95,67,76,75,68,73,86,95,49,54,51,56,52,0
	.section	.debug_info		;off: 550
	.data.w	.Ldw_str_begin+556
	.data.b	75
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 577
	.data.b	83,97,102,101,119,100,116,95,67,108,107,68,105,118,0
	.section	.debug_info		;off: 560
	.data.w	.Ldw_str_begin+577
	.data.b	76
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+512

	.data.b	52
	.section	.debug_str		;off: 592
	.data.b	0
	.section	.debug_info		;off: 572
	.data.w	.Ldw_str_begin+592
	.data.b	80
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 593
	.data.b	83,65,70,69,87,68,84,95,79,85,84,77,79,68,69,95,65,76,65,82,77,0
	.section	.debug_info		;off: 582
	.data.w	.Ldw_str_begin+593
	.data.b	81
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 615
	.data.b	83,65,70,69,87,68,84,95,79,85,84,77,79,68,69,95,73,78,84,69,82,82,85,80,84,0
	.section	.debug_info		;off: 591
	.data.w	.Ldw_str_begin+615
	.data.b	82
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 641
	.data.b	83,97,102,101,119,100,116,95,79,117,116,77,111,100,101,0
	.section	.debug_info		;off: 601
	.data.w	.Ldw_str_begin+641
	.data.b	83
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+571

	.data.b	52
	.section	.debug_str		;off: 657
	.data.b	0
	.section	.debug_info		;off: 613
	.data.w	.Ldw_str_begin+657
	.data.b	87
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 658
	.data.b	83,65,70,69,87,68,84,95,83,84,65,84,85,83,95,82,69,83,69,84,0
	.section	.debug_info		;off: 623
	.data.w	.Ldw_str_begin+658
	.data.b	88
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 679
	.data.b	83,65,70,69,87,68,84,95,83,84,65,84,85,83,95,83,69,84,0
	.section	.debug_info		;off: 632
	.data.w	.Ldw_str_begin+679
	.data.b	89
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 698
	.data.b	83,97,102,101,119,100,116,95,83,116,97,116,117,115,0
	.section	.debug_info		;off: 642
	.data.w	.Ldw_str_begin+698
	.data.b	90
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+612

	.data.b	52
	.section	.debug_str		;off: 713
	.data.b	0
	.section	.debug_info		;off: 654
	.data.w	.Ldw_str_begin+713
	.data.b	94
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 714
	.data.b	83,65,70,69,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,83,69,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 664
	.data.w	.Ldw_str_begin+714
	.data.b	95
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 748
	.data.b	83,65,70,69,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 673
	.data.w	.Ldw_str_begin+748
	.data.b	96
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 788
	.data.b	83,65,70,69,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,83,69,67,79,78,68,87,68,84,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 682
	.data.w	.Ldw_str_begin+788
	.data.b	97
	.data.b	5
	.data.b	5
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 829
	.data.b	83,65,70,69,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,80,65,83,83,87,79,82,68,69,82,82,79,82,0
	.section	.debug_info		;off: 691
	.data.w	.Ldw_str_begin+829
	.data.b	98
	.data.b	5
	.data.b	5
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 867
	.data.b	83,65,70,69,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,82,69,71,69,82,82,79,82,0
	.section	.debug_info		;off: 700
	.data.w	.Ldw_str_begin+867
	.data.b	99
	.data.b	5
	.data.b	5
	.data.b	16

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 900
	.data.b	83,97,102,101,119,100,116,95,65,108,97,114,109,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 710
	.data.w	.Ldw_str_begin+900
	.data.b	100
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+653

	.data.b	52
	.section	.debug_str		;off: 924
	.data.b	0
	.section	.debug_info		;off: 722
	.data.w	.Ldw_str_begin+924
	.data.b	104
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 925
	.data.b	83,65,70,69,87,68,84,95,73,78,84,69,82,82,85,80,84,83,84,65,84,85,83,70,76,65,71,95,83,69,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 732
	.data.w	.Ldw_str_begin+925
	.data.b	105
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 963
	.data.b	83,65,70,69,87,68,84,95,73,78,84,69,82,82,85,80,84,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 741
	.data.w	.Ldw_str_begin+963
	.data.b	106
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1007
	.data.b	83,97,102,101,119,100,116,95,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 751
	.data.w	.Ldw_str_begin+1007
	.data.b	107
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+721

	.data.b	52
	.section	.debug_str		;off: 1035
	.data.b	0
	.section	.debug_info		;off: 763
	.data.w	.Ldw_str_begin+1035
	.data.b	111
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1036
	.data.b	83,65,70,69,87,68,84,95,80,87,65,78,68,76,80,83,84,65,84,85,83,70,76,65,71,95,83,65,70,69,87,68,84,76,80,0
	.section	.debug_info		;off: 773
	.data.w	.Ldw_str_begin+1036
	.data.b	112
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1072
	.data.b	83,65,70,69,87,68,84,95,80,87,65,78,68,76,80,83,84,65,84,85,83,70,76,65,71,95,87,68,84,76,80,0
	.section	.debug_info		;off: 782
	.data.w	.Ldw_str_begin+1072
	.data.b	113
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1104
	.data.b	83,97,102,101,119,100,116,95,80,119,65,110,100,76,112,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 792
	.data.w	.Ldw_str_begin+1104
	.data.b	114
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+762

	.data.b	52
	.section	.debug_str		;off: 1130
	.data.b	0
	.section	.debug_info		;off: 804
	.data.w	.Ldw_str_begin+1130
	.data.b	118
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1131
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,83,69,65,76,65,82,77,0
	.section	.debug_info		;off: 814
	.data.w	.Ldw_str_begin+1131
	.data.b	119
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1163
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,83,69,73,78,84,82,0
	.section	.debug_info		;off: 823
	.data.w	.Ldw_str_begin+1163
	.data.b	120
	.data.b	5
	.data.b	5
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1194
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,65,76,65,82,77,0
	.section	.debug_info		;off: 832
	.data.w	.Ldw_str_begin+1194
	.data.b	121
	.data.b	5
	.data.b	5
	.data.b	48

	.data.b	51
	.section	.debug_str		;off: 1232
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,73,78,84,69,82,82,85,80,84,0
	.section	.debug_info		;off: 841
	.data.w	.Ldw_str_begin+1232
	.data.b	122
	.data.b	5
	.data.b	5
	.data.b	192,1

	.data.b	51
	.section	.debug_str		;off: 1274
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,83,69,67,79,78,68,87,68,84,65,76,65,82,77,0
	.section	.debug_info		;off: 851
	.data.w	.Ldw_str_begin+1274
	.data.b	123
	.data.b	5
	.data.b	5
	.data.b	128,6

	.data.b	51
	.section	.debug_str		;off: 1313
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,83,65,70,69,87,68,84,76,80,0
	.section	.debug_info		;off: 861
	.data.w	.Ldw_str_begin+1313
	.data.b	124
	.data.b	5
	.data.b	5
	.data.b	128,24

	.data.b	51
	.section	.debug_str		;off: 1347
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,87,68,84,76,80,0
	.section	.debug_info		;off: 871
	.data.w	.Ldw_str_begin+1347
	.data.b	125
	.data.b	5
	.data.b	5
	.data.b	128,224,0

	.data.b	51
	.section	.debug_str		;off: 1377
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,80,65,83,83,87,79,82,68,65,76,65,82,77,0
	.section	.debug_info		;off: 882
	.data.w	.Ldw_str_begin+1377
	.data.b	126
	.data.b	5
	.data.b	5
	.data.b	128,128,3

	.data.b	51
	.section	.debug_str		;off: 1415
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,82,69,71,65,76,65,82,77,0
	.section	.debug_info		;off: 893
	.data.w	.Ldw_str_begin+1415
	.data.b	127
	.data.b	5
	.data.b	5
	.data.b	128,128,12

	.data.b	51
	.section	.debug_str		;off: 1448
	.data.b	83,65,70,69,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,65,76,76,67,76,69,65,82,0
	.section	.debug_info		;off: 904
	.data.w	.Ldw_str_begin+1448
	.data.b	128,1
	.data.b	5
	.data.b	5
	.data.b	255,255,15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1481
	.data.b	83,97,102,101,119,100,116,95,67,108,101,97,114,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 917
	.data.w	.Ldw_str_begin+1481
	.data.b	129,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+803

	.data.b	71
	.data.b	140,1
	.data.b	1
	.data.b	5
	.data.b	36
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

	.section	.debug_info		;off: 936
	.data.b	40
	.section	.debug_str		;off: 1505
	.data.b	112,119,87,100,116,73,110,105,116,0
	.section	.debug_info		;off: 937
	.data.w	.Ldw_str_begin+1505
	.data.b	141,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+370
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

	.section	.debug_info		;off: 953
	.data.b	40
	.section	.debug_str		;off: 1515
	.data.b	119,100,116,76,111,119,84,104,118,48,0
	.section	.debug_info		;off: 954
	.data.w	.Ldw_str_begin+1515
	.data.b	142,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1526
	.data.b	119,100,116,76,111,119,84,104,118,49,0
	.section	.debug_info		;off: 971
	.data.w	.Ldw_str_begin+1526
	.data.b	143,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1537
	.data.b	119,100,116,72,105,103,104,84,104,118,48,0
	.section	.debug_info		;off: 988
	.data.w	.Ldw_str_begin+1537
	.data.b	144,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1549
	.data.b	119,100,116,72,105,103,104,84,104,118,49,0
	.section	.debug_info		;off: 1005
	.data.w	.Ldw_str_begin+1549
	.data.b	145,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1561
	.data.b	115,97,102,101,67,112,117,73,100,0
	.section	.debug_info		;off: 1022
	.data.w	.Ldw_str_begin+1561
	.data.b	146,1
	.data.b	23
	.data.b	5
	.data.w	.Ldw_begin+450
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1571
	.data.b	119,100,116,70,105,114,79,117,116,77,111,100,101,0
	.section	.debug_info		;off: 1039
	.data.w	.Ldw_str_begin+1571
	.data.b	147,1
	.data.b	21
	.data.b	5
	.data.w	.Ldw_begin+600
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1585
	.data.b	112,119,87,100,116,77,111,100,101,0
	.section	.debug_info		;off: 1056
	.data.w	.Ldw_str_begin+1585
	.data.b	148,1
	.data.b	20
	.data.b	5
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1595
	.data.b	119,100,116,67,108,107,68,105,118,0
	.section	.debug_info		;off: 1073
	.data.w	.Ldw_str_begin+1595
	.data.b	149,1
	.data.b	20
	.data.b	5
	.data.w	.Ldw_begin+559
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1605
	.data.b	83,97,102,101,119,100,116,95,87,100,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1091
	.data.w	.Ldw_str_begin+1605
	.data.b	150,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+929

	.data.b	71
	.data.b	156,1
	.data.b	1
	.data.b	5
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1623
	.data.b	112,119,83,101,73,110,105,116,0
	.section	.debug_info		;off: 1111
	.data.w	.Ldw_str_begin+1623
	.data.b	157,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+370
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1632
	.data.b	115,101,84,104,118,0
	.section	.debug_info		;off: 1128
	.data.w	.Ldw_str_begin+1632
	.data.b	158,1
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+370
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1638
	.data.b	115,97,102,101,67,112,117,73,100,0
	.section	.debug_info		;off: 1145
	.data.w	.Ldw_str_begin+1638
	.data.b	159,1
	.data.b	23
	.data.b	5
	.data.w	.Ldw_begin+450
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1648
	.data.b	115,101,79,117,116,77,111,100,101,0
	.section	.debug_info		;off: 1162
	.data.w	.Ldw_str_begin+1648
	.data.b	160,1
	.data.b	21
	.data.b	5
	.data.w	.Ldw_begin+600
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1658
	.data.b	112,119,83,101,77,111,100,101,0
	.section	.debug_info		;off: 1179
	.data.w	.Ldw_str_begin+1658
	.data.b	161,1
	.data.b	20
	.data.b	5
	.data.w	.Ldw_begin+500
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1667
	.data.b	115,101,67,108,107,68,105,118,0
	.section	.debug_info		;off: 1196
	.data.w	.Ldw_str_begin+1667
	.data.b	162,1
	.data.b	20
	.data.b	5
	.data.w	.Ldw_begin+559
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1676
	.data.b	83,97,102,101,119,100,116,95,83,97,102,101,116,121,69,110,100,105,110,105,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1214
	.data.w	.Ldw_str_begin+1676
	.data.b	163,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+1103

	.data.b	45
	.section	.debug_str		;off: 1704
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 1227
	.data.w	.Ldw_str_begin+1704
	.data.b	24
	.data.b	22
	.data.b	12
	.data.w	.Ldw_begin+304

	.data.b	71
	.data.b	34
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1711
	.data.b	80,87,48,0
	.section	.debug_info		;off: 1245
	.data.w	.Ldw_str_begin+1711
	.data.b	35
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 174
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

	.section	.debug_info		;off: 1263
	.data.b	41
	.section	.debug_str		;off: 1715
	.data.b	114,101,115,101,114,118,101,100,95,49,52,0
	.section	.debug_info		;off: 1264
	.data.w	.Ldw_str_begin+1715
	.data.b	36
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1727
	.data.b	83,65,70,69,87,68,84,95,80,87,48,95,66,105,116,115,0
	.section	.debug_info		;off: 1284
	.data.w	.Ldw_str_begin+1727
	.data.b	37
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1238

	.data.b	71
	.data.b	41
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1744
	.data.b	80,87,48,76,67,75,0
	.section	.debug_info		;off: 1302
	.data.w	.Ldw_str_begin+1744
	.data.b	42
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1751
	.data.b	83,69,80,87,76,67,75,0
	.section	.debug_info		;off: 1321
	.data.w	.Ldw_str_begin+1751
	.data.b	43
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1759
	.data.b	87,68,84,80,87,76,67,75,0
	.section	.debug_info		;off: 1340
	.data.w	.Ldw_str_begin+1759
	.data.b	44
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1768
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 1359
	.data.w	.Ldw_str_begin+1768
	.data.b	45
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	29
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1779
	.data.b	83,65,70,69,87,68,84,95,80,87,76,79,67,75,95,66,105,116,115,0
	.section	.debug_info		;off: 1379
	.data.w	.Ldw_str_begin+1779
	.data.b	46
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1295

	.data.b	71
	.data.b	50
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1799
	.data.b	87,68,84,80,87,73,78,73,84,0
	.section	.debug_info		;off: 1397
	.data.w	.Ldw_str_begin+1799
	.data.b	51
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1809
	.data.b	87,68,84,80,87,77,0
	.section	.debug_info		;off: 1416
	.data.w	.Ldw_str_begin+1809
	.data.b	52
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1816
	.data.b	83,69,80,87,73,78,73,84,0
	.section	.debug_info		;off: 1435
	.data.w	.Ldw_str_begin+1816
	.data.b	53
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	2
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1825
	.data.b	83,69,80,87,77,0
	.section	.debug_info		;off: 1454
	.data.w	.Ldw_str_begin+1825
	.data.b	54
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1831
	.data.b	83,65,70,69,87,68,84,95,80,87,77,65,73,95,66,105,116,115,0
	.section	.debug_info		;off: 1474
	.data.w	.Ldw_str_begin+1831
	.data.b	55
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1390

	.data.b	71
	.data.b	59
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1850
	.data.b	80,87,48,67,78,84,0
	.section	.debug_info		;off: 1492
	.data.w	.Ldw_str_begin+1850
	.data.b	60
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1857
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 1511
	.data.w	.Ldw_str_begin+1857
	.data.b	61
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1869
	.data.b	83,65,70,69,87,68,84,95,80,87,48,67,78,84,95,66,105,116,115,0
	.section	.debug_info		;off: 1531
	.data.w	.Ldw_str_begin+1869
	.data.b	62
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1485

	.data.b	71
	.data.b	66
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1889
	.data.b	87,68,84,67,76,75,68,73,86,0
	.section	.debug_info		;off: 1549
	.data.w	.Ldw_str_begin+1889
	.data.b	67
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	29
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1899
	.data.b	83,69,67,76,75,68,73,86,0
	.section	.debug_info		;off: 1568
	.data.w	.Ldw_str_begin+1899
	.data.b	68
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	26
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1908
	.data.b	76,80,83,69,78,0
	.section	.debug_info		;off: 1587
	.data.w	.Ldw_str_begin+1908
	.data.b	69
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	25
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1914
	.data.b	114,101,115,101,114,118,101,100,95,55,0
	.section	.debug_info		;off: 1606
	.data.w	.Ldw_str_begin+1914
	.data.b	70
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	25
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1925
	.data.b	83,65,70,69,87,68,84,95,67,76,75,77,78,71,95,66,105,116,115,0
	.section	.debug_info		;off: 1626
	.data.w	.Ldw_str_begin+1925
	.data.b	71
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1542

	.data.b	71
	.data.b	75
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1945
	.data.b	83,69,79,85,84,77,0
	.section	.debug_info		;off: 1644
	.data.w	.Ldw_str_begin+1945
	.data.b	76
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1952
	.data.b	87,68,84,79,85,84,77,49,0
	.section	.debug_info		;off: 1663
	.data.w	.Ldw_str_begin+1952
	.data.b	78
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1961
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 1682
	.data.w	.Ldw_str_begin+1961
	.data.b	80
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1972
	.data.b	83,65,70,69,87,68,84,95,79,85,84,77,95,66,105,116,115,0
	.section	.debug_info		;off: 1702
	.data.w	.Ldw_str_begin+1972
	.data.b	81
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1637

	.data.b	71
	.data.b	85
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1990
	.data.b	83,65,70,69,67,79,82,69,73,68,0
	.section	.debug_info		;off: 1720
	.data.w	.Ldw_str_begin+1990
	.data.b	86
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2001
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 1739
	.data.w	.Ldw_str_begin+2001
	.data.b	87
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2012
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,95,66,105,116,115,0
	.section	.debug_info		;off: 1759
	.data.w	.Ldw_str_begin+2012
	.data.b	88
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1713

	.data.b	71
	.data.b	92
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2035
	.data.b	87,68,84,76,80,73,0
	.section	.debug_info		;off: 1777
	.data.w	.Ldw_str_begin+2035
	.data.b	93
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2042
	.data.b	83,87,77,76,80,73,0
	.section	.debug_info		;off: 1796
	.data.w	.Ldw_str_begin+2042
	.data.b	94
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2049
	.data.b	80,87,48,83,84,83,0
	.section	.debug_info		;off: 1815
	.data.w	.Ldw_str_begin+2049
	.data.b	95
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2056
	.data.b	83,69,80,87,83,84,83,0
	.section	.debug_info		;off: 1834
	.data.w	.Ldw_str_begin+2056
	.data.b	96
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2064
	.data.b	87,68,84,80,87,83,84,83,0
	.section	.debug_info		;off: 1853
	.data.w	.Ldw_str_begin+2064
	.data.b	97
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2073
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 1872
	.data.w	.Ldw_str_begin+2073
	.data.b	98
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	27
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2084
	.data.b	83,65,70,69,87,68,84,95,83,87,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 1892
	.data.w	.Ldw_str_begin+2084
	.data.b	99
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1770

	.data.b	71
	.data.b	103
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2103
	.data.b	83,69,65,76,77,0
	.section	.debug_info		;off: 1910
	.data.w	.Ldw_str_begin+2103
	.data.b	104
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2109
	.data.b	87,68,84,65,76,77,49,0
	.section	.debug_info		;off: 1929
	.data.w	.Ldw_str_begin+2109
	.data.b	105
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2117
	.data.b	87,68,84,65,76,77,50,0
	.section	.debug_info		;off: 1948
	.data.w	.Ldw_str_begin+2117
	.data.b	106
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	29
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2125
	.data.b	83,87,65,76,77,0
	.section	.debug_info		;off: 1967
	.data.w	.Ldw_str_begin+2125
	.data.b	107
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2131
	.data.b	83,87,82,69,71,65,76,77,0
	.section	.debug_info		;off: 1986
	.data.w	.Ldw_str_begin+2131
	.data.b	109
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	27
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2140
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 2005
	.data.w	.Ldw_str_begin+2140
	.data.b	110
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	27
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2151
	.data.b	83,65,70,69,87,68,84,95,83,87,65,76,77,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 2025
	.data.w	.Ldw_str_begin+2151
	.data.b	111
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+1903

	.data.b	71
	.data.b	115
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2173
	.data.b	83,69,73,78,84,0
	.section	.debug_info		;off: 2043
	.data.w	.Ldw_str_begin+2173
	.data.b	116
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2179
	.data.b	87,68,84,73,78,84,49,0
	.section	.debug_info		;off: 2062
	.data.w	.Ldw_str_begin+2179
	.data.b	117
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2187
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 2081
	.data.w	.Ldw_str_begin+2187
	.data.b	118
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2198
	.data.b	83,65,70,69,87,68,84,95,83,87,73,78,84,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 2101
	.data.w	.Ldw_str_begin+2198
	.data.b	119
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2036

	.data.b	71
	.data.b	123
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2220
	.data.b	83,69,65,76,77,69,0
	.section	.debug_info		;off: 2119
	.data.w	.Ldw_str_begin+2220
	.data.b	124
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2227
	.data.b	83,69,73,78,84,69,0
	.section	.debug_info		;off: 2138
	.data.w	.Ldw_str_begin+2227
	.data.b	125
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2234
	.data.b	87,68,84,65,76,77,69,49,0
	.section	.debug_info		;off: 2157
	.data.w	.Ldw_str_begin+2234
	.data.b	126
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2243
	.data.b	87,68,84,73,78,84,69,49,0
	.section	.debug_info		;off: 2176
	.data.w	.Ldw_str_begin+2243
	.data.b	128,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2252
	.data.b	87,68,84,65,76,77,69,50,0
	.section	.debug_info		;off: 2196
	.data.w	.Ldw_str_begin+2252
	.data.b	130,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2261
	.data.b	87,68,84,76,80,73,69,0
	.section	.debug_info		;off: 2216
	.data.w	.Ldw_str_begin+2261
	.data.b	132,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2269
	.data.b	83,87,77,76,80,73,69,0
	.section	.debug_info		;off: 2236
	.data.w	.Ldw_str_begin+2269
	.data.b	133,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2277
	.data.b	83,87,65,76,77,69,78,0
	.section	.debug_info		;off: 2256
	.data.w	.Ldw_str_begin+2277
	.data.b	134,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2285
	.data.b	82,69,71,65,76,77,69,78,0
	.section	.debug_info		;off: 2276
	.data.w	.Ldw_str_begin+2285
	.data.b	135,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	14
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2294
	.data.b	114,101,115,101,114,118,101,100,95,49,56,0
	.section	.debug_info		;off: 2296
	.data.w	.Ldw_str_begin+2294
	.data.b	137,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2306
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,87,68,84,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 2317
	.data.w	.Ldw_str_begin+2306
	.data.b	138,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2112

	.data.b	71
	.data.b	142,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2329
	.data.b	83,69,65,76,77,67,0
	.section	.debug_info		;off: 2337
	.data.w	.Ldw_str_begin+2329
	.data.b	143,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2336
	.data.b	83,69,73,78,84,67,0
	.section	.debug_info		;off: 2357
	.data.w	.Ldw_str_begin+2336
	.data.b	144,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2343
	.data.b	87,68,84,65,76,77,67,49,0
	.section	.debug_info		;off: 2377
	.data.w	.Ldw_str_begin+2343
	.data.b	145,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2352
	.data.b	87,68,84,73,78,84,67,49,0
	.section	.debug_info		;off: 2397
	.data.w	.Ldw_str_begin+2352
	.data.b	146,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2361
	.data.b	87,68,84,65,76,77,67,50,0
	.section	.debug_info		;off: 2417
	.data.w	.Ldw_str_begin+2361
	.data.b	147,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2370
	.data.b	83,87,76,80,73,67,0
	.section	.debug_info		;off: 2437
	.data.w	.Ldw_str_begin+2370
	.data.b	148,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2377
	.data.b	87,68,84,76,80,73,67,0
	.section	.debug_info		;off: 2457
	.data.w	.Ldw_str_begin+2377
	.data.b	149,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2385
	.data.b	83,87,65,76,77,67,0
	.section	.debug_info		;off: 2477
	.data.w	.Ldw_str_begin+2385
	.data.b	150,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2392
	.data.b	83,87,82,69,71,65,76,77,67,0
	.section	.debug_info		;off: 2497
	.data.w	.Ldw_str_begin+2392
	.data.b	151,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	14
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2402
	.data.b	114,101,115,101,114,118,101,100,95,49,56,0
	.section	.debug_info		;off: 2517
	.data.w	.Ldw_str_begin+2402
	.data.b	152,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2414
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,87,68,84,67,76,95,66,105,116,115,0
	.section	.debug_info		;off: 2538
	.data.w	.Ldw_str_begin+2414
	.data.b	153,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2329

	.data.b	71
	.data.b	157,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2437
	.data.b	83,69,65,76,77,77,75,0
	.section	.debug_info		;off: 2558
	.data.w	.Ldw_str_begin+2437
	.data.b	158,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2445
	.data.b	87,68,84,65,76,77,49,77,75,0
	.section	.debug_info		;off: 2578
	.data.w	.Ldw_str_begin+2445
	.data.b	159,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2455
	.data.b	87,68,84,65,76,77,50,77,75,0
	.section	.debug_info		;off: 2598
	.data.w	.Ldw_str_begin+2455
	.data.b	160,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	26
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2465
	.data.b	83,87,65,76,77,77,75,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+2465
	.data.b	161,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2473
	.data.b	82,69,71,65,76,77,77,75,0
	.section	.debug_info		;off: 2638
	.data.w	.Ldw_str_begin+2473
	.data.b	162,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2482
	.data.b	66,69,77,65,83,75,0
	.section	.debug_info		;off: 2658
	.data.w	.Ldw_str_begin+2482
	.data.b	163,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2489
	.data.b	114,101,115,101,114,118,101,100,95,49,50,0
	.section	.debug_info		;off: 2678
	.data.w	.Ldw_str_begin+2489
	.data.b	164,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2501
	.data.b	83,65,70,69,87,68,84,95,83,87,77,65,83,75,95,66,105,116,115,0
	.section	.debug_info		;off: 2699
	.data.w	.Ldw_str_begin+2501
	.data.b	165,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2550

	.data.b	71
	.data.b	169,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2521
	.data.b	83,69,73,78,84,77,75,0
	.section	.debug_info		;off: 2719
	.data.w	.Ldw_str_begin+2521
	.data.b	170,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2529
	.data.b	87,68,84,73,78,84,49,77,75,0
	.section	.debug_info		;off: 2739
	.data.w	.Ldw_str_begin+2529
	.data.b	171,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2539
	.data.b	114,101,115,101,114,118,101,100,95,52,0
	.section	.debug_info		;off: 2759
	.data.w	.Ldw_str_begin+2539
	.data.b	172,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	28
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2550
	.data.b	83,65,70,69,87,68,84,95,83,87,73,78,84,77,65,83,75,95,66,105,116,115,0
	.section	.debug_info		;off: 2780
	.data.w	.Ldw_str_begin+2550
	.data.b	173,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2711

	.data.b	71
	.data.b	177,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2573
	.data.b	68,66,71,72,87,69,78,0
	.section	.debug_info		;off: 2800
	.data.w	.Ldw_str_begin+2573
	.data.b	178,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2581
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 2820
	.data.w	.Ldw_str_begin+2581
	.data.b	179,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	31
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2592
	.data.b	83,65,70,69,87,68,84,95,68,66,71,72,87,67,75,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 2841
	.data.w	.Ldw_str_begin+2592
	.data.b	180,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2792

	.data.b	71
	.data.b	186,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2615
	.data.b	83,69,80,87,0
	.section	.debug_info		;off: 2861
	.data.w	.Ldw_str_begin+2615
	.data.b	187,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2620
	.data.b	114,101,115,101,114,118,101,100,95,49,52,0
	.section	.debug_info		;off: 2881
	.data.w	.Ldw_str_begin+2620
	.data.b	188,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2632
	.data.b	83,65,70,69,87,68,84,95,83,69,80,87,95,66,105,116,115,0
	.section	.debug_info		;off: 2902
	.data.w	.Ldw_str_begin+2632
	.data.b	189,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2853

	.data.b	71
	.data.b	193,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2650
	.data.b	83,69,80,87,67,78,84,0
	.section	.debug_info		;off: 2922
	.data.w	.Ldw_str_begin+2650
	.data.b	194,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2658
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 2942
	.data.w	.Ldw_str_begin+2658
	.data.b	195,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2670
	.data.b	83,65,70,69,87,68,84,95,83,69,80,87,67,78,84,95,66,105,116,115,0
	.section	.debug_info		;off: 2963
	.data.w	.Ldw_str_begin+2670
	.data.b	196,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2914

	.data.b	71
	.data.b	200,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2691
	.data.b	83,69,67,78,84,69,78,0
	.section	.debug_info		;off: 2983
	.data.w	.Ldw_str_begin+2691
	.data.b	201,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2699
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3003
	.data.w	.Ldw_str_begin+2699
	.data.b	202,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2710
	.data.b	83,65,70,69,87,68,84,95,83,69,67,78,84,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 3024
	.data.w	.Ldw_str_begin+2710
	.data.b	203,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+2975

	.data.b	71
	.data.b	207,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2731
	.data.b	83,69,83,84,65,82,84,0
	.section	.debug_info		;off: 3044
	.data.w	.Ldw_str_begin+2731
	.data.b	208,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2739
	.data.b	83,69,83,84,79,80,0
	.section	.debug_info		;off: 3064
	.data.w	.Ldw_str_begin+2739
	.data.b	209,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	28
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2746
	.data.b	114,101,115,101,114,118,101,100,95,52,0
	.section	.debug_info		;off: 3084
	.data.w	.Ldw_str_begin+2746
	.data.b	210,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	28
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2757
	.data.b	83,65,70,69,87,68,84,95,83,69,67,78,84,67,95,66,105,116,115,0
	.section	.debug_info		;off: 3105
	.data.w	.Ldw_str_begin+2757
	.data.b	211,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3036

	.data.b	71
	.data.b	215,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2777
	.data.b	83,69,84,72,86,0
	.section	.debug_info		;off: 3125
	.data.w	.Ldw_str_begin+2777
	.data.b	216,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2783
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 3145
	.data.w	.Ldw_str_begin+2783
	.data.b	217,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2795
	.data.b	83,65,70,69,87,68,84,95,83,69,84,72,86,95,66,105,116,115,0
	.section	.debug_info		;off: 3166
	.data.w	.Ldw_str_begin+2795
	.data.b	218,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3117

	.data.b	71
	.data.b	222,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2814
	.data.b	83,69,67,78,84,0
	.section	.debug_info		;off: 3186
	.data.w	.Ldw_str_begin+2814
	.data.b	223,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2820
	.data.b	83,69,79,85,84,83,84,83,0
	.section	.debug_info		;off: 3206
	.data.w	.Ldw_str_begin+2820
	.data.b	224,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2829
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3226
	.data.w	.Ldw_str_begin+2829
	.data.b	225,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2841
	.data.b	83,65,70,69,87,68,84,95,83,69,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 3247
	.data.w	.Ldw_str_begin+2841
	.data.b	226,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3178

	.data.b	71
	.data.b	233,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2860
	.data.b	87,68,84,80,87,0
	.section	.debug_info		;off: 3267
	.data.w	.Ldw_str_begin+2860
	.data.b	234,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	18
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2866
	.data.b	114,101,115,101,114,118,101,100,95,49,52,0
	.section	.debug_info		;off: 3287
	.data.w	.Ldw_str_begin+2866
	.data.b	235,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2878
	.data.b	83,65,70,69,87,68,84,95,87,68,84,80,87,95,66,105,116,115,0
	.section	.debug_info		;off: 3308
	.data.w	.Ldw_str_begin+2878
	.data.b	236,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3259

	.data.b	71
	.data.b	240,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2897
	.data.b	87,68,84,80,87,67,78,84,0
	.section	.debug_info		;off: 3328
	.data.w	.Ldw_str_begin+2897
	.data.b	241,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2906
	.data.b	114,101,115,101,114,118,101,100,95,49,54,0
	.section	.debug_info		;off: 3348
	.data.w	.Ldw_str_begin+2906
	.data.b	242,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2918
	.data.b	83,65,70,69,87,68,84,95,87,68,84,80,87,67,78,84,95,66,105,116,115,0
	.section	.debug_info		;off: 3369
	.data.w	.Ldw_str_begin+2918
	.data.b	243,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3320

	.data.b	71
	.data.b	247,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2940
	.data.b	87,68,84,67,78,84,69,78,0
	.section	.debug_info		;off: 3389
	.data.w	.Ldw_str_begin+2940
	.data.b	248,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2949
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3409
	.data.w	.Ldw_str_begin+2949
	.data.b	249,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2960
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 3430
	.data.w	.Ldw_str_begin+2960
	.data.b	250,1
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3381

	.data.b	71
	.data.b	254,1
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2982
	.data.b	87,68,84,83,69,82,86,73,67,69,0
	.section	.debug_info		;off: 3450
	.data.w	.Ldw_str_begin+2982
	.data.b	255,1
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2993
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3470
	.data.w	.Ldw_str_begin+2993
	.data.b	128,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3004
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,67,95,66,105,116,115,0
	.section	.debug_info		;off: 3491
	.data.w	.Ldw_str_begin+3004
	.data.b	129,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3442

	.data.b	71
	.data.b	133,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3025
	.data.b	87,68,84,76,69,78,48,0
	.section	.debug_info		;off: 3511
	.data.w	.Ldw_str_begin+3025
	.data.b	134,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3033
	.data.b	87,68,84,76,69,78,49,0
	.section	.debug_info		;off: 3531
	.data.w	.Ldw_str_begin+3033
	.data.b	135,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3041
	.data.b	114,101,115,101,114,118,101,100,95,50,0
	.section	.debug_info		;off: 3551
	.data.w	.Ldw_str_begin+3041
	.data.b	136,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3052
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,69,78,95,66,105,116,115,0
	.section	.debug_info		;off: 3572
	.data.w	.Ldw_str_begin+3052
	.data.b	137,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3503

	.data.b	71
	.data.b	141,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3072
	.data.b	67,78,84,86,65,76,0
	.section	.debug_info		;off: 3592
	.data.w	.Ldw_str_begin+3072
	.data.b	142,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	14
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3079
	.data.b	114,101,115,101,114,118,101,100,95,49,56,0
	.section	.debug_info		;off: 3612
	.data.w	.Ldw_str_begin+3079
	.data.b	143,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	14
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3091
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,86,65,76,95,66,105,116,115,0
	.section	.debug_info		;off: 3633
	.data.w	.Ldw_str_begin+3091
	.data.b	144,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3584

	.data.b	71
	.data.b	148,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3114
	.data.b	87,68,84,76,84,72,86,48,0
	.section	.debug_info		;off: 3653
	.data.w	.Ldw_str_begin+3114
	.data.b	149,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	15
	.data.b	17
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3123
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3673
	.data.w	.Ldw_str_begin+3123
	.data.b	150,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3135
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,84,72,86,48,95,66,105,116,115,0
	.section	.debug_info		;off: 3694
	.data.w	.Ldw_str_begin+3135
	.data.b	151,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3645

	.data.b	71
	.data.b	155,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3157
	.data.b	87,68,84,72,84,72,86,48,0
	.section	.debug_info		;off: 3714
	.data.w	.Ldw_str_begin+3157
	.data.b	156,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	15
	.data.b	17
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3166
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3734
	.data.w	.Ldw_str_begin+3166
	.data.b	157,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3178
	.data.b	83,65,70,69,87,68,84,95,87,68,84,72,84,72,86,48,95,66,105,116,115,0
	.section	.debug_info		;off: 3755
	.data.w	.Ldw_str_begin+3178
	.data.b	158,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3706

	.data.b	71
	.data.b	162,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3200
	.data.b	87,68,84,76,84,72,86,49,0
	.section	.debug_info		;off: 3775
	.data.w	.Ldw_str_begin+3200
	.data.b	163,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	15
	.data.b	17
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3209
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3795
	.data.w	.Ldw_str_begin+3209
	.data.b	164,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3221
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,84,72,86,49,95,66,105,116,115,0
	.section	.debug_info		;off: 3816
	.data.w	.Ldw_str_begin+3221
	.data.b	165,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3767

	.data.b	71
	.data.b	169,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3243
	.data.b	87,68,84,72,84,72,86,49,0
	.section	.debug_info		;off: 3836
	.data.w	.Ldw_str_begin+3243
	.data.b	170,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	15
	.data.b	17
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 3252
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3856
	.data.w	.Ldw_str_begin+3252
	.data.b	171,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+304
	.data.b	4
	.data.b	0
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3264
	.data.b	83,65,70,69,87,68,84,95,87,68,84,72,84,72,86,49,95,66,105,116,115,0
	.section	.debug_info		;off: 3877
	.data.w	.Ldw_str_begin+3264
	.data.b	172,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3828

	.data.b	73
	.data.b	180,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 199
	.data.b	73
	.data.b	23
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 3896
	.data.b	40
	.section	.debug_str		;off: 3286
	.data.b	85,0
	.section	.debug_info		;off: 3897
	.data.w	.Ldw_str_begin+3286
	.data.b	181,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3288
	.data.b	66,0
	.section	.debug_info		;off: 3914
	.data.w	.Ldw_str_begin+3288
	.data.b	182,2
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+1378
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3290
	.data.b	83,65,70,69,87,68,84,95,80,87,76,79,67,75,0
	.section	.debug_info		;off: 3932
	.data.w	.Ldw_str_begin+3290
	.data.b	183,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3889

	.data.b	73
	.data.b	188,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3305
	.data.b	85,0
	.section	.debug_info		;off: 3952
	.data.w	.Ldw_str_begin+3305
	.data.b	189,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3307
	.data.b	66,0
	.section	.debug_info		;off: 3969
	.data.w	.Ldw_str_begin+3307
	.data.b	190,2
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+1283
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3309
	.data.b	83,65,70,69,87,68,84,95,80,87,48,0
	.section	.debug_info		;off: 3987
	.data.w	.Ldw_str_begin+3309
	.data.b	191,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3944

	.data.b	73
	.data.b	196,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3321
	.data.b	85,0
	.section	.debug_info		;off: 4007
	.data.w	.Ldw_str_begin+3321
	.data.b	197,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3323
	.data.b	66,0
	.section	.debug_info		;off: 4024
	.data.w	.Ldw_str_begin+3323
	.data.b	198,2
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+1530
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3325
	.data.b	83,65,70,69,87,68,84,95,80,87,48,67,78,84,0
	.section	.debug_info		;off: 4042
	.data.w	.Ldw_str_begin+3325
	.data.b	199,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+3999

	.data.b	73
	.data.b	204,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3340
	.data.b	85,0
	.section	.debug_info		;off: 4062
	.data.w	.Ldw_str_begin+3340
	.data.b	205,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3342
	.data.b	66,0
	.section	.debug_info		;off: 4079
	.data.w	.Ldw_str_begin+3342
	.data.b	206,2
	.data.b	24
	.data.b	11
	.data.w	.Ldw_begin+1473
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3344
	.data.b	83,65,70,69,87,68,84,95,80,87,77,65,73,0
	.section	.debug_info		;off: 4097
	.data.w	.Ldw_str_begin+3344
	.data.b	207,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4054

	.data.b	73
	.data.b	212,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3358
	.data.b	85,0
	.section	.debug_info		;off: 4117
	.data.w	.Ldw_str_begin+3358
	.data.b	213,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3360
	.data.b	66,0
	.section	.debug_info		;off: 4134
	.data.w	.Ldw_str_begin+3360
	.data.b	214,2
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+1625
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3362
	.data.b	83,65,70,69,87,68,84,95,67,76,75,77,78,71,0
	.section	.debug_info		;off: 4152
	.data.w	.Ldw_str_begin+3362
	.data.b	215,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4109

	.data.b	73
	.data.b	220,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3377
	.data.b	85,0
	.section	.debug_info		;off: 4172
	.data.w	.Ldw_str_begin+3377
	.data.b	221,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3379
	.data.b	66,0
	.section	.debug_info		;off: 4189
	.data.w	.Ldw_str_begin+3379
	.data.b	222,2
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+1701
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3381
	.data.b	83,65,70,69,87,68,84,95,79,85,84,77,0
	.section	.debug_info		;off: 4207
	.data.w	.Ldw_str_begin+3381
	.data.b	223,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4164

	.data.b	73
	.data.b	228,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3394
	.data.b	85,0
	.section	.debug_info		;off: 4227
	.data.w	.Ldw_str_begin+3394
	.data.b	229,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3396
	.data.b	66,0
	.section	.debug_info		;off: 4244
	.data.w	.Ldw_str_begin+3396
	.data.b	230,2
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+1758
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3398
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,67,80,85,73,68,0
	.section	.debug_info		;off: 4262
	.data.w	.Ldw_str_begin+3398
	.data.b	231,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4219

	.data.b	73
	.data.b	236,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3416
	.data.b	85,0
	.section	.debug_info		;off: 4282
	.data.w	.Ldw_str_begin+3416
	.data.b	237,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3418
	.data.b	66,0
	.section	.debug_info		;off: 4299
	.data.w	.Ldw_str_begin+3418
	.data.b	238,2
	.data.b	24
	.data.b	11
	.data.w	.Ldw_begin+1891
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3420
	.data.b	83,65,70,69,87,68,84,95,83,87,83,84,83,0
	.section	.debug_info		;off: 4317
	.data.w	.Ldw_str_begin+3420
	.data.b	239,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4274

	.data.b	73
	.data.b	244,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3434
	.data.b	85,0
	.section	.debug_info		;off: 4337
	.data.w	.Ldw_str_begin+3434
	.data.b	245,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3436
	.data.b	66,0
	.section	.debug_info		;off: 4354
	.data.w	.Ldw_str_begin+3436
	.data.b	246,2
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+2024
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3438
	.data.b	83,65,70,69,87,68,84,95,83,87,65,76,77,83,84,83,0
	.section	.debug_info		;off: 4372
	.data.w	.Ldw_str_begin+3438
	.data.b	247,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4329

	.data.b	73
	.data.b	252,2
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3455
	.data.b	85,0
	.section	.debug_info		;off: 4392
	.data.w	.Ldw_str_begin+3455
	.data.b	253,2
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3457
	.data.b	66,0
	.section	.debug_info		;off: 4409
	.data.w	.Ldw_str_begin+3457
	.data.b	254,2
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+2100
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3459
	.data.b	83,65,70,69,87,68,84,95,83,87,73,78,84,83,84,83,0
	.section	.debug_info		;off: 4427
	.data.w	.Ldw_str_begin+3459
	.data.b	255,2
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4384

	.data.b	73
	.data.b	132,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3476
	.data.b	85,0
	.section	.debug_info		;off: 4447
	.data.w	.Ldw_str_begin+3476
	.data.b	133,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3478
	.data.b	66,0
	.section	.debug_info		;off: 4464
	.data.w	.Ldw_str_begin+3478
	.data.b	134,3
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+2316
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3480
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,87,68,84,69,78,0
	.section	.debug_info		;off: 4482
	.data.w	.Ldw_str_begin+3480
	.data.b	135,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4439

	.data.b	73
	.data.b	140,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3498
	.data.b	85,0
	.section	.debug_info		;off: 4502
	.data.w	.Ldw_str_begin+3498
	.data.b	141,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3500
	.data.b	66,0
	.section	.debug_info		;off: 4519
	.data.w	.Ldw_str_begin+3500
	.data.b	142,3
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+2537
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3502
	.data.b	83,65,70,69,87,68,84,95,83,65,70,69,87,68,84,67,76,0
	.section	.debug_info		;off: 4537
	.data.w	.Ldw_str_begin+3502
	.data.b	143,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4494

	.data.b	73
	.data.b	148,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3520
	.data.b	85,0
	.section	.debug_info		;off: 4557
	.data.w	.Ldw_str_begin+3520
	.data.b	149,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3522
	.data.b	66,0
	.section	.debug_info		;off: 4574
	.data.w	.Ldw_str_begin+3522
	.data.b	150,3
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+2698
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3524
	.data.b	83,65,70,69,87,68,84,95,83,87,77,65,83,75,0
	.section	.debug_info		;off: 4592
	.data.w	.Ldw_str_begin+3524
	.data.b	151,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4549

	.data.b	73
	.data.b	156,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3539
	.data.b	85,0
	.section	.debug_info		;off: 4612
	.data.w	.Ldw_str_begin+3539
	.data.b	157,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3541
	.data.b	66,0
	.section	.debug_info		;off: 4629
	.data.w	.Ldw_str_begin+3541
	.data.b	158,3
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+2779
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3543
	.data.b	83,65,70,69,87,68,84,95,83,87,73,78,84,77,65,83,75,0
	.section	.debug_info		;off: 4647
	.data.w	.Ldw_str_begin+3543
	.data.b	159,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4604

	.data.b	73
	.data.b	164,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3561
	.data.b	85,0
	.section	.debug_info		;off: 4667
	.data.w	.Ldw_str_begin+3561
	.data.b	165,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3563
	.data.b	66,0
	.section	.debug_info		;off: 4684
	.data.w	.Ldw_str_begin+3563
	.data.b	166,3
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+2840
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3565
	.data.b	83,65,70,69,87,68,84,95,68,66,71,72,87,67,75,69,78,0
	.section	.debug_info		;off: 4702
	.data.w	.Ldw_str_begin+3565
	.data.b	167,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4659

	.data.b	73
	.data.b	174,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3583
	.data.b	85,0
	.section	.debug_info		;off: 4722
	.data.w	.Ldw_str_begin+3583
	.data.b	175,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3585
	.data.b	66,0
	.section	.debug_info		;off: 4739
	.data.w	.Ldw_str_begin+3585
	.data.b	176,3
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+2901
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3587
	.data.b	83,65,70,69,87,68,84,95,83,69,80,87,0
	.section	.debug_info		;off: 4757
	.data.w	.Ldw_str_begin+3587
	.data.b	177,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4714

	.data.b	73
	.data.b	182,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3600
	.data.b	85,0
	.section	.debug_info		;off: 4777
	.data.w	.Ldw_str_begin+3600
	.data.b	183,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3602
	.data.b	66,0
	.section	.debug_info		;off: 4794
	.data.w	.Ldw_str_begin+3602
	.data.b	184,3
	.data.b	26
	.data.b	11
	.data.w	.Ldw_begin+2962
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3604
	.data.b	83,65,70,69,87,68,84,95,83,69,80,87,67,78,84,0
	.section	.debug_info		;off: 4812
	.data.w	.Ldw_str_begin+3604
	.data.b	185,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4769

	.data.b	73
	.data.b	190,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3620
	.data.b	85,0
	.section	.debug_info		;off: 4832
	.data.w	.Ldw_str_begin+3620
	.data.b	191,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3622
	.data.b	66,0
	.section	.debug_info		;off: 4849
	.data.w	.Ldw_str_begin+3622
	.data.b	192,3
	.data.b	26
	.data.b	11
	.data.w	.Ldw_begin+3023
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3624
	.data.b	83,65,70,69,87,68,84,95,83,69,67,78,84,69,78,0
	.section	.debug_info		;off: 4867
	.data.w	.Ldw_str_begin+3624
	.data.b	193,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4824

	.data.b	73
	.data.b	198,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3640
	.data.b	85,0
	.section	.debug_info		;off: 4887
	.data.w	.Ldw_str_begin+3640
	.data.b	199,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3642
	.data.b	66,0
	.section	.debug_info		;off: 4904
	.data.w	.Ldw_str_begin+3642
	.data.b	200,3
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+3104
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3644
	.data.b	83,65,70,69,87,68,84,95,83,69,67,78,84,67,0
	.section	.debug_info		;off: 4922
	.data.w	.Ldw_str_begin+3644
	.data.b	201,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4879

	.data.b	73
	.data.b	206,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3659
	.data.b	85,0
	.section	.debug_info		;off: 4942
	.data.w	.Ldw_str_begin+3659
	.data.b	207,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3661
	.data.b	66,0
	.section	.debug_info		;off: 4959
	.data.w	.Ldw_str_begin+3661
	.data.b	208,3
	.data.b	24
	.data.b	11
	.data.w	.Ldw_begin+3165
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3663
	.data.b	83,65,70,69,87,68,84,95,83,69,84,72,86,0
	.section	.debug_info		;off: 4977
	.data.w	.Ldw_str_begin+3663
	.data.b	209,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4934

	.data.b	73
	.data.b	214,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3677
	.data.b	85,0
	.section	.debug_info		;off: 4997
	.data.w	.Ldw_str_begin+3677
	.data.b	215,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3679
	.data.b	66,0
	.section	.debug_info		;off: 5014
	.data.w	.Ldw_str_begin+3679
	.data.b	216,3
	.data.b	24
	.data.b	11
	.data.w	.Ldw_begin+3246
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3681
	.data.b	83,65,70,69,87,68,84,95,83,69,83,84,83,0
	.section	.debug_info		;off: 5032
	.data.w	.Ldw_str_begin+3681
	.data.b	217,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+4989

	.data.b	73
	.data.b	225,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3695
	.data.b	85,0
	.section	.debug_info		;off: 5052
	.data.w	.Ldw_str_begin+3695
	.data.b	226,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3697
	.data.b	66,0
	.section	.debug_info		;off: 5069
	.data.w	.Ldw_str_begin+3697
	.data.b	227,3
	.data.b	24
	.data.b	11
	.data.w	.Ldw_begin+3307
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3699
	.data.b	83,65,70,69,87,68,84,95,87,68,84,80,87,0
	.section	.debug_info		;off: 5087
	.data.w	.Ldw_str_begin+3699
	.data.b	228,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5044

	.data.b	73
	.data.b	233,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3713
	.data.b	85,0
	.section	.debug_info		;off: 5107
	.data.w	.Ldw_str_begin+3713
	.data.b	234,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3715
	.data.b	66,0
	.section	.debug_info		;off: 5124
	.data.w	.Ldw_str_begin+3715
	.data.b	235,3
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3368
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3717
	.data.b	83,65,70,69,87,68,84,95,87,68,84,80,87,67,78,84,0
	.section	.debug_info		;off: 5142
	.data.w	.Ldw_str_begin+3717
	.data.b	236,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5099

	.data.b	73
	.data.b	241,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3734
	.data.b	85,0
	.section	.debug_info		;off: 5162
	.data.w	.Ldw_str_begin+3734
	.data.b	242,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3736
	.data.b	66,0
	.section	.debug_info		;off: 5179
	.data.w	.Ldw_str_begin+3736
	.data.b	243,3
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3429
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3738
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,69,78,0
	.section	.debug_info		;off: 5197
	.data.w	.Ldw_str_begin+3738
	.data.b	244,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5154

	.data.b	73
	.data.b	249,3
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3755
	.data.b	85,0
	.section	.debug_info		;off: 5217
	.data.w	.Ldw_str_begin+3755
	.data.b	250,3
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3757
	.data.b	66,0
	.section	.debug_info		;off: 5234
	.data.w	.Ldw_str_begin+3757
	.data.b	251,3
	.data.b	26
	.data.b	11
	.data.w	.Ldw_begin+3490
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3759
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,67,0
	.section	.debug_info		;off: 5252
	.data.w	.Ldw_str_begin+3759
	.data.b	252,3
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5209

	.data.b	73
	.data.b	129,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3775
	.data.b	85,0
	.section	.debug_info		;off: 5272
	.data.w	.Ldw_str_begin+3775
	.data.b	130,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3777
	.data.b	66,0
	.section	.debug_info		;off: 5289
	.data.w	.Ldw_str_begin+3777
	.data.b	131,4
	.data.b	25
	.data.b	11
	.data.w	.Ldw_begin+3571
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3779
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,69,78,0
	.section	.debug_info		;off: 5307
	.data.w	.Ldw_str_begin+3779
	.data.b	132,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5264

	.data.b	73
	.data.b	137,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3794
	.data.b	85,0
	.section	.debug_info		;off: 5327
	.data.w	.Ldw_str_begin+3794
	.data.b	138,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3796
	.data.b	66,0
	.section	.debug_info		;off: 5344
	.data.w	.Ldw_str_begin+3796
	.data.b	139,4
	.data.b	28
	.data.b	11
	.data.w	.Ldw_begin+3632
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3798
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,86,65,76,0
	.section	.debug_info		;off: 5362
	.data.w	.Ldw_str_begin+3798
	.data.b	140,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5319

	.data.b	73
	.data.b	145,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3816
	.data.b	85,0
	.section	.debug_info		;off: 5382
	.data.w	.Ldw_str_begin+3816
	.data.b	146,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3818
	.data.b	66,0
	.section	.debug_info		;off: 5399
	.data.w	.Ldw_str_begin+3818
	.data.b	147,4
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3693
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3820
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,84,72,86,48,0
	.section	.debug_info		;off: 5417
	.data.w	.Ldw_str_begin+3820
	.data.b	148,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5374

	.data.b	73
	.data.b	153,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3837
	.data.b	85,0
	.section	.debug_info		;off: 5437
	.data.w	.Ldw_str_begin+3837
	.data.b	154,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3839
	.data.b	66,0
	.section	.debug_info		;off: 5454
	.data.w	.Ldw_str_begin+3839
	.data.b	155,4
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3754
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3841
	.data.b	83,65,70,69,87,68,84,95,87,68,84,72,84,72,86,48,0
	.section	.debug_info		;off: 5472
	.data.w	.Ldw_str_begin+3841
	.data.b	156,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5429

	.data.b	73
	.data.b	161,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3858
	.data.b	85,0
	.section	.debug_info		;off: 5492
	.data.w	.Ldw_str_begin+3858
	.data.b	162,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3860
	.data.b	66,0
	.section	.debug_info		;off: 5509
	.data.w	.Ldw_str_begin+3860
	.data.b	163,4
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3815
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3862
	.data.b	83,65,70,69,87,68,84,95,87,68,84,76,84,72,86,49,0
	.section	.debug_info		;off: 5527
	.data.w	.Ldw_str_begin+3862
	.data.b	164,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5484

	.data.b	73
	.data.b	169,4
	.data.b	1
	.data.b	11
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3879
	.data.b	85,0
	.section	.debug_info		;off: 5547
	.data.w	.Ldw_str_begin+3879
	.data.b	170,4
	.data.b	12
	.data.b	11
	.data.w	.Ldw_begin+382
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3881
	.data.b	66,0
	.section	.debug_info		;off: 5564
	.data.w	.Ldw_str_begin+3881
	.data.b	171,4
	.data.b	27
	.data.b	11
	.data.w	.Ldw_begin+3876
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3883
	.data.b	83,65,70,69,87,68,84,95,87,68,84,72,84,72,86,49,0
	.section	.debug_info		;off: 5582
	.data.w	.Ldw_str_begin+3883
	.data.b	172,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+5539

	.data.b	71
	.data.b	179,4
	.data.b	1
	.data.b	11
	.data.b	124
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3900
	.data.b	80,87,48,0
	.section	.debug_info		;off: 5602
	.data.w	.Ldw_str_begin+3900
	.data.b	180,4
	.data.b	17
	.data.b	11
	.data.w	.Ldw_begin+3986
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3904
	.data.b	80,87,76,79,67,75,0
	.section	.debug_info		;off: 5619
	.data.w	.Ldw_str_begin+3904
	.data.b	181,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+3931
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3911
	.data.b	80,87,77,65,73,0
	.section	.debug_info		;off: 5636
	.data.w	.Ldw_str_begin+3911
	.data.b	182,4
	.data.b	19
	.data.b	11
	.data.w	.Ldw_begin+4096
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3917
	.data.b	80,87,48,67,78,84,0
	.section	.debug_info		;off: 5653
	.data.w	.Ldw_str_begin+3917
	.data.b	183,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+4041
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3924
	.data.b	83,69,80,87,67,78,84,0
	.section	.debug_info		;off: 5670
	.data.w	.Ldw_str_begin+3924
	.data.b	184,4
	.data.b	21
	.data.b	11
	.data.w	.Ldw_begin+4811
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3932
	.data.b	83,69,84,72,86,0
	.section	.debug_info		;off: 5687
	.data.w	.Ldw_str_begin+3932
	.data.b	185,4
	.data.b	19
	.data.b	11
	.data.w	.Ldw_begin+4976
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3938
	.data.b	83,69,80,87,0
	.section	.debug_info		;off: 5704
	.data.w	.Ldw_str_begin+3938
	.data.b	186,4
	.data.b	18
	.data.b	11
	.data.w	.Ldw_begin+4756
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3943
	.data.b	83,69,67,78,84,69,78,0
	.section	.debug_info		;off: 5721
	.data.w	.Ldw_str_begin+3943
	.data.b	187,4
	.data.b	21
	.data.b	11
	.data.w	.Ldw_begin+4866
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3951
	.data.b	83,69,67,78,84,67,0
	.section	.debug_info		;off: 5738
	.data.w	.Ldw_str_begin+3951
	.data.b	188,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+4921
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3958
	.data.b	87,68,84,80,87,67,78,84,0
	.section	.debug_info		;off: 5755
	.data.w	.Ldw_str_begin+3958
	.data.b	189,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5141
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3967
	.data.b	87,68,84,76,69,78,0
	.section	.debug_info		;off: 5772
	.data.w	.Ldw_str_begin+3967
	.data.b	190,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+5306
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3974
	.data.b	87,68,84,76,84,72,86,48,0
	.section	.debug_info		;off: 5789
	.data.w	.Ldw_str_begin+3974
	.data.b	191,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5416
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3983
	.data.b	87,68,84,72,84,72,86,48,0
	.section	.debug_info		;off: 5806
	.data.w	.Ldw_str_begin+3983
	.data.b	192,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5471
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3992
	.data.b	87,68,84,76,84,72,86,49,0
	.section	.debug_info		;off: 5823
	.data.w	.Ldw_str_begin+3992
	.data.b	193,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5526
	.data.b	2,35
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4001
	.data.b	87,68,84,72,84,72,86,49,0
	.section	.debug_info		;off: 5840
	.data.w	.Ldw_str_begin+4001
	.data.b	194,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5581
	.data.b	2,35
	.data.b	56
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4010
	.data.b	87,68,84,80,87,0
	.section	.debug_info		;off: 5857
	.data.w	.Ldw_str_begin+4010
	.data.b	195,4
	.data.b	19
	.data.b	11
	.data.w	.Ldw_begin+5086
	.data.b	2,35
	.data.b	60
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4016
	.data.b	87,68,84,67,78,84,69,78,0
	.section	.debug_info		;off: 5874
	.data.w	.Ldw_str_begin+4016
	.data.b	196,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+5196
	.data.b	2,35
	.data.b	64
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4025
	.data.b	87,68,84,67,78,84,67,0
	.section	.debug_info		;off: 5891
	.data.w	.Ldw_str_begin+4025
	.data.b	197,4
	.data.b	21
	.data.b	11
	.data.w	.Ldw_begin+5251
	.data.b	2,35
	.data.b	68
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4033
	.data.b	67,76,75,77,78,71,0
	.section	.debug_info		;off: 5908
	.data.w	.Ldw_str_begin+4033
	.data.b	198,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+4151
	.data.b	2,35
	.data.b	72
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4040
	.data.b	79,85,84,77,0
	.section	.debug_info		;off: 5925
	.data.w	.Ldw_str_begin+4040
	.data.b	199,4
	.data.b	18
	.data.b	11
	.data.w	.Ldw_begin+4206
	.data.b	2,35
	.data.b	76
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4045
	.data.b	83,65,70,69,67,80,85,73,68,0
	.section	.debug_info		;off: 5942
	.data.w	.Ldw_str_begin+4045
	.data.b	200,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+4261
	.data.b	2,35
	.data.b	80
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4055
	.data.b	83,69,83,84,83,0
	.section	.debug_info		;off: 5959
	.data.w	.Ldw_str_begin+4055
	.data.b	201,4
	.data.b	19
	.data.b	11
	.data.w	.Ldw_begin+5031
	.data.b	2,35
	.data.b	84
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4061
	.data.b	87,68,84,67,78,84,86,65,76,0
	.section	.debug_info		;off: 5976
	.data.w	.Ldw_str_begin+4061
	.data.b	202,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+5361
	.data.b	2,35
	.data.b	88
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4071
	.data.b	83,87,83,84,83,0
	.section	.debug_info		;off: 5993
	.data.w	.Ldw_str_begin+4071
	.data.b	203,4
	.data.b	19
	.data.b	11
	.data.w	.Ldw_begin+4316
	.data.b	2,35
	.data.b	92
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4077
	.data.b	83,87,65,76,77,83,84,83,0
	.section	.debug_info		;off: 6010
	.data.w	.Ldw_str_begin+4077
	.data.b	204,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+4371
	.data.b	2,35
	.data.b	96
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4086
	.data.b	83,87,73,78,84,83,84,83,0
	.section	.debug_info		;off: 6027
	.data.w	.Ldw_str_begin+4086
	.data.b	205,4
	.data.b	22
	.data.b	11
	.data.w	.Ldw_begin+4426
	.data.b	2,35
	.data.b	100
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4095
	.data.b	83,65,70,69,87,68,84,69,78,0
	.section	.debug_info		;off: 6044
	.data.w	.Ldw_str_begin+4095
	.data.b	206,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+4481
	.data.b	2,35
	.data.b	104
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4105
	.data.b	83,65,70,69,87,68,84,67,76,0
	.section	.debug_info		;off: 6061
	.data.w	.Ldw_str_begin+4105
	.data.b	207,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+4536
	.data.b	2,35
	.data.b	108
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4115
	.data.b	83,87,77,65,83,75,0
	.section	.debug_info		;off: 6078
	.data.w	.Ldw_str_begin+4115
	.data.b	208,4
	.data.b	20
	.data.b	11
	.data.w	.Ldw_begin+4591
	.data.b	2,35
	.data.b	112
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4122
	.data.b	83,87,73,78,84,77,65,83,75,0
	.section	.debug_info		;off: 6095
	.data.w	.Ldw_str_begin+4122
	.data.b	209,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+4646
	.data.b	2,35
	.data.b	116
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4132
	.data.b	68,66,71,72,87,67,75,69,78,0
	.section	.debug_info		;off: 6112
	.data.w	.Ldw_str_begin+4132
	.data.b	210,4
	.data.b	23
	.data.b	11
	.data.w	.Ldw_begin+4701
	.data.b	2,35
	.data.b	120
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4142
	.data.b	83,65,70,69,87,68,84,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 6130
	.data.w	.Ldw_str_begin+4142
	.data.b	211,4
	.data.b	3
	.data.b	11
	.data.w	.Ldw_begin+311

	.data.b	27
	.section	.debug_str		;off: 4157
	.data.b	83,97,102,101,119,100,116,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 6143
	.data.w	.Ldw_str_begin+4157
	.data.b	82
	.data.b	27
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 214
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

	.section	.debug_info		;off: 6160
	.data.b	20
	.section	.debug_str		;off: 4189
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 6161
	.data.w	.Ldw_str_begin+4189
	.data.b	82
	.data.b	67
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	0

	.section	.debug_abbrev		;off: 241
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

	.section	.debug_info		;off: 6173
	.data.b	20
	.section	.debug_str		;off: 4195
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 6174
	.data.w	.Ldw_str_begin+4195
	.data.b	82
	.data.b	81
	.data.b	10
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 4202
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 6187
	.data.w	.Ldw_str_begin+4202
	.data.b	82
	.data.b	96
	.data.b	10
	.data.w	.Ldw_begin+382
	.data.b	0

	.data.b	37

	.section	.debug_abbrev		;off: 258
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 6200
	.data.b	8
	.section	.debug_str		;off: 4208
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6201
	.data.w	.Ldw_str_begin+4208
	.data.b	84
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 263
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

	.section	.debug_info		;off: 6214
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4212
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,67,108,101,97,114,80,119,48,0
	.section	.debug_info		;off: 6217
	.data.w	.Ldw_str_begin+4212
	.data.b	122
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4233
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,83,101,116,80,119,48,0
	.section	.debug_info		;off: 6236
	.data.w	.Ldw_str_begin+4233
	.data.b	139,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4252
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,67,108,101,97,114,80,119,119,100,116,0
	.section	.debug_info		;off: 6256
	.data.w	.Ldw_str_begin+4252
	.data.b	156,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4275
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,83,101,116,80,119,119,100,116,0
	.section	.debug_info		;off: 6276
	.data.w	.Ldw_str_begin+4275
	.data.b	173,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4296
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,67,108,101,97,114,80,119,115,101,0
	.section	.debug_info		;off: 6296
	.data.w	.Ldw_str_begin+4296
	.data.b	190,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 4318
	.data.b	83,97,102,101,119,100,116,95,83,116,100,95,83,101,116,80,119,115,101,0
	.section	.debug_info		;off: 6316
	.data.w	.Ldw_str_begin+4318
	.data.b	208,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+358
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4338
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,67,97,108,99,117,108,97,116,101,68,121,110,97,109,105,99,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6336
	.data.w	.Ldw_str_begin+4338
	.data.b	108
	.data.b	15
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.w	Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.
	.data.w	__ghs_eofn_Safewdt_Hal_CalculateDynamicPassword
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

	.section	.debug_abbrev		;off: 282
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
	.data.w	Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.
	.data.w	__ghs_eofn_Safewdt_Hal_CalculateDynamicPassword-Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 546
	.data.b	0,5,2
	.data.w	Safewdt_Hal_CalculateDynamicPassword..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Csafewdt_hal.
	.data.b	6
	.data.b	3
	.data.b	240,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6368
	.data.b	22
	.section	.debug_str		;off: 4375
	.data.b	112,114,101,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6369
	.data.w	.Ldw_str_begin+4375
	.data.b	108
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+370
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

	.section	.debug_abbrev		;off: 330
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

	.section	.debug_info		;off: 6385
	.data.b	22
	.section	.debug_str		;off: 4387
	.data.b	112,119,77,111,100,101,0
	.section	.debug_info		;off: 6386
	.data.w	.Ldw_str_begin+4387
	.data.b	108
	.data.b	87
	.data.b	1
	.data.w	.Ldw_begin+500
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6402
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 349
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 6411
	.data.b	8
	.section	.debug_str		;off: 4394
	.data.b	112,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6412
	.data.w	.Ldw_str_begin+4394
	.data.b	110
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4403
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,73,110,105,116,87,100,116,0
	.section	.debug_info		;off: 6428
	.data.w	.Ldw_str_begin+4403
	.data.b	133,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_InitWdt
	.data.w	__ghs_eofn_Safewdt_Hal_InitWdt
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_InitWdt
	.data.w	__ghs_eofn_Safewdt_Hal_InitWdt-Safewdt_Hal_InitWdt
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 582
	.data.b	0,5,2
	.data.w	Safewdt_Hal_InitWdt
	.data.b	6
	.data.b	3
	.data.b	133,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	76
	.data.b	6
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	76
	.data.b	76
	.data.b	75
	.data.b	13
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	12
	.data.b	13
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	28
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	75
	.data.b	13
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	12
	.data.b	13
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	28
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	61
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6463
	.data.b	22
	.section	.debug_str		;off: 4423
	.data.b	112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6464
	.data.w	.Ldw_str_begin+4423
	.data.b	133,1
	.data.b	60
	.data.b	1
	.data.w	.Ldw_begin+110
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW31
	.data.w	.LDW41
	.data.b	1,0
	.data.b	80
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6481
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 4431
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6491
	.data.w	.Ldw_str_begin+4431
	.data.b	135,1
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 358
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

	.section	.debug_info		;off: 6509
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4435
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,73,110,105,116,83,97,102,101,116,121,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 6512
	.data.w	.Ldw_str_begin+4435
	.data.b	143,2
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_InitSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_InitSafetyEndinit
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
	.data.w	Safewdt_Hal_InitSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_InitSafetyEndinit-Safewdt_Hal_InitSafetyEndinit
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 718
	.data.b	0,5,2
	.data.w	Safewdt_Hal_InitSafetyEndinit
	.data.b	6
	.data.b	3
	.data.b	143,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	60
	.data.b	60
	.data.b	6
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	76
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	76
	.data.b	93
	.data.b	44
	.data.b	61
	.data.b	45
	.data.b	44
	.data.b	44
	.data.b	59
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6547
	.data.b	22
	.section	.debug_str		;off: 4465
	.data.b	112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 6548
	.data.w	.Ldw_str_begin+4465
	.data.b	143,2
	.data.b	80
	.data.b	1
	.data.w	.Ldw_begin+138
	.data.b	0
	.data.w	.Ldw_loc_begin+87
	.section	.debug_loc		;off: 87
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

	.section	.debug_info		;off: 6565
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 4473
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6575
	.data.w	.Ldw_str_begin+4473
	.data.b	145,2
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6593
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4477
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,71,101,116,87,100,116,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6596
	.data.w	.Ldw_str_begin+4477
	.data.b	217,2
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.w	Safewdt_Hal_GetWdtPassword
	.data.w	__ghs_eofn_Safewdt_Hal_GetWdtPassword
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
	.data.w	Safewdt_Hal_GetWdtPassword
	.data.w	__ghs_eofn_Safewdt_Hal_GetWdtPassword-Safewdt_Hal_GetWdtPassword
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 796
	.data.b	0,5,2
	.data.w	Safewdt_Hal_GetWdtPassword
	.data.b	6
	.data.b	3
	.data.b	225,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	77
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6629
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 4504
	.data.b	119,100,116,77,111,100,101,0
	.section	.debug_info		;off: 6639
	.data.w	.Ldw_str_begin+4504
	.data.b	219,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+500
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+136
	.section	.debug_loc		;off: 136
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6657
	.data.b	7
	.section	.debug_str		;off: 4512
	.data.b	112,114,101,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6658
	.data.w	.Ldw_str_begin+4512
	.data.b	220,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+155
	.section	.debug_loc		;off: 155
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6676
	.data.b	8
	.section	.debug_str		;off: 4524
	.data.b	112,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 6677
	.data.w	.Ldw_str_begin+4524
	.data.b	221,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4533
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,69,110,97,98,108,101,87,100,116,0
	.section	.debug_info		;off: 6694
	.data.w	.Ldw_str_begin+4533
	.data.b	246,2
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_EnableWdt
	.data.w	__ghs_eofn_Safewdt_Hal_EnableWdt
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
	.data.b	0
	.data.b	28
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
	.data.w	Safewdt_Hal_EnableWdt
	.data.w	__ghs_eofn_Safewdt_Hal_EnableWdt-Safewdt_Hal_EnableWdt
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 825
	.data.b	0,5,2
	.data.w	Safewdt_Hal_EnableWdt
	.data.b	6
	.data.b	3
	.data.b	246,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	59
	.data.b	27
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	44
	.data.b	60
	.data.b	43
	.data.b	44
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
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
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 6729
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 4555
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6739
	.data.w	.Ldw_str_begin+4555
	.data.b	248,2
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+174
	.section	.debug_loc		;off: 174
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6757
	.data.b	7
	.section	.debug_str		;off: 4559
	.data.b	116,104,118,0
	.section	.debug_info		;off: 6758
	.data.w	.Ldw_str_begin+4559
	.data.b	249,2
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+193
	.section	.debug_loc		;off: 193
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6776
	.data.b	7
	.section	.debug_str		;off: 4563
	.data.b	99,108,107,68,105,118,0
	.section	.debug_info		;off: 6777
	.data.w	.Ldw_str_begin+4563
	.data.b	250,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+212
	.section	.debug_loc		;off: 212
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6795
	.data.b	7
	.section	.debug_str		;off: 4570
	.data.b	105,110,100,101,120,0
	.section	.debug_info		;off: 6796
	.data.w	.Ldw_str_begin+4570
	.data.b	251,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+231
	.section	.debug_loc		;off: 231
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6814
	.data.b	7
	.section	.debug_str		;off: 4576
	.data.b	119,100,116,70,97,99,116,111,114,115,0
	.section	.debug_info		;off: 6815
	.data.w	.Ldw_str_begin+4576
	.data.b	252,2
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+250
	.section	.debug_loc		;off: 250
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6833
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4587
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,83,101,114,118,105,99,101,87,100,116,0
	.section	.debug_info		;off: 6836
	.data.w	.Ldw_str_begin+4587
	.data.b	203,3
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_ServiceWdt
	.data.w	__ghs_eofn_Safewdt_Hal_ServiceWdt
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
	.data.w	Safewdt_Hal_ServiceWdt
	.data.w	__ghs_eofn_Safewdt_Hal_ServiceWdt-Safewdt_Hal_ServiceWdt
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 919
	.data.b	0,5,2
	.data.w	Safewdt_Hal_ServiceWdt
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
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6871
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 4610
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6881
	.data.w	.Ldw_str_begin+4610
	.data.b	205,3
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+270
	.section	.debug_loc		;off: 270
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6899
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4614
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,68,105,115,97,98,108,101,87,100,116,0
	.section	.debug_info		;off: 6902
	.data.w	.Ldw_str_begin+4614
	.data.b	220,3
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_DisableWdt
	.data.w	__ghs_eofn_Safewdt_Hal_DisableWdt
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_DisableWdt
	.data.w	__ghs_eofn_Safewdt_Hal_DisableWdt-Safewdt_Hal_DisableWdt
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 950
	.data.b	0,5,2
	.data.w	Safewdt_Hal_DisableWdt
	.data.b	6
	.data.b	3
	.data.b	220,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	43
	.data.b	44
	.data.b	60
	.data.b	60
	.data.b	59
	.data.b	45
	.data.b	108
	.data.b	108
	.data.b	108
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	93
	.data.b	13
	.data.b	44
	.data.b	60
	.data.b	60
	.data.b	59
	.data.b	45
	.data.b	108
	.data.b	108
	.data.b	108
	.data.b	43
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
	.section	.debug_info		;off: 6937
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 4637
	.data.b	114,101,116,0
	.section	.debug_info		;off: 6947
	.data.w	.Ldw_str_begin+4637
	.data.b	222,3
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+289
	.section	.debug_loc		;off: 289
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6965
	.data.b	7
	.section	.debug_str		;off: 4641
	.data.b	116,105,109,101,79,117,116,67,110,116,0
	.section	.debug_info		;off: 6966
	.data.w	.Ldw_str_begin+4641
	.data.b	223,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+308
	.section	.debug_loc		;off: 308
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6984
	.data.b	7
	.section	.debug_str		;off: 4652
	.data.b	97,108,109,77,97,115,107,49,0
	.section	.debug_info		;off: 6985
	.data.w	.Ldw_str_begin+4652
	.data.b	224,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+327
	.section	.debug_loc		;off: 327
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7003
	.data.b	7
	.section	.debug_str		;off: 4661
	.data.b	97,108,109,77,97,115,107,50,0
	.section	.debug_info		;off: 7004
	.data.w	.Ldw_str_begin+4661
	.data.b	225,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+346
	.section	.debug_loc		;off: 346
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7022
	.data.b	7
	.section	.debug_str		;off: 4670
	.data.b	105,110,116,77,97,115,107,0
	.section	.debug_info		;off: 7023
	.data.w	.Ldw_str_begin+4670
	.data.b	226,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+365
	.section	.debug_loc		;off: 365
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7041
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4678
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,67,104,97,110,103,101,72,105,103,104,84,104,118,0
	.section	.debug_info		;off: 7044
	.data.w	.Ldw_str_begin+4678
	.data.b	167,4
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_ChangeHighThv
	.data.w	__ghs_eofn_Safewdt_Hal_ChangeHighThv
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_ChangeHighThv
	.data.w	__ghs_eofn_Safewdt_Hal_ChangeHighThv-Safewdt_Hal_ChangeHighThv
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1026
	.data.b	0,5,2
	.data.w	Safewdt_Hal_ChangeHighThv
	.data.b	6
	.data.b	3
	.data.b	167,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	20
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	45
	.data.b	76
	.data.b	93
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7079
	.data.b	22
	.section	.debug_str		;off: 4704
	.data.b	110,101,119,72,105,103,104,84,104,118,48,0
	.section	.debug_info		;off: 7080
	.data.w	.Ldw_str_begin+4704
	.data.b	167,4
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.w	.Ldw_loc_begin+384
	.section	.debug_loc		;off: 384
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	80
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7097
	.data.b	22
	.section	.debug_str		;off: 4716
	.data.b	110,101,119,72,105,103,104,84,104,118,49,0
	.section	.debug_info		;off: 7098
	.data.w	.Ldw_str_begin+4716
	.data.b	167,4
	.data.b	62
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.w	.Ldw_loc_begin+414
	.section	.debug_loc		;off: 414
	.data.w	.LDW13
	.data.w	.LDW23
	.data.b	1,0
	.data.b	81
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7115
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 4728
	.data.b	114,101,116,0
	.section	.debug_info		;off: 7125
	.data.w	.Ldw_str_begin+4728
	.data.b	169,4
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+444
	.section	.debug_loc		;off: 444
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7143
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4732
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,71,101,116,65,108,97,114,109,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7146
	.data.w	.Ldw_str_begin+4732
	.data.b	214,4
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.w	Safewdt_Hal_GetAlarmFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetAlarmFlagStatus
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
	.data.w	Safewdt_Hal_GetAlarmFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetAlarmFlagStatus-Safewdt_Hal_GetAlarmFlagStatus
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1066
	.data.b	0,5,2
	.data.w	Safewdt_Hal_GetAlarmFlagStatus
	.data.b	6
	.data.b	3
	.data.b	219,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7179
	.data.b	22
	.section	.debug_str		;off: 4763
	.data.b	102,108,97,103,0
	.section	.debug_info		;off: 7180
	.data.w	.Ldw_str_begin+4763
	.data.b	214,4
	.data.b	71
	.data.b	1
	.data.w	.Ldw_begin+709
	.data.b	0
	.data.w	.Ldw_loc_begin+463
	.section	.debug_loc		;off: 463
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7197
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	8
	.section	.debug_str		;off: 4768
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 7207
	.data.w	.Ldw_str_begin+4768
	.data.b	216,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4775
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7224
	.data.w	.Ldw_str_begin+4775
	.data.b	233,4
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.w	Safewdt_Hal_GetInterruptFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetInterruptFlagStatus
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
	.data.w	Safewdt_Hal_GetInterruptFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetInterruptFlagStatus-Safewdt_Hal_GetInterruptFlagStatus
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1093
	.data.b	0,5,2
	.data.w	Safewdt_Hal_GetInterruptFlagStatus
	.data.b	6
	.data.b	3
	.data.b	238,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7257
	.data.b	22
	.section	.debug_str		;off: 4810
	.data.b	102,108,97,103,0
	.section	.debug_info		;off: 7258
	.data.w	.Ldw_str_begin+4810
	.data.b	233,4
	.data.b	79
	.data.b	1
	.data.w	.Ldw_begin+750
	.data.b	0
	.data.w	.Ldw_loc_begin+482
	.section	.debug_loc		;off: 482
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7275
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	8
	.section	.debug_str		;off: 4815
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 7285
	.data.w	.Ldw_str_begin+4815
	.data.b	235,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4822
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,71,101,116,80,119,65,110,100,76,112,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7302
	.data.w	.Ldw_str_begin+4822
	.data.b	252,4
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.w	Safewdt_Hal_GetPwAndLpFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetPwAndLpFlagStatus
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
	.data.w	Safewdt_Hal_GetPwAndLpFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_GetPwAndLpFlagStatus-Safewdt_Hal_GetPwAndLpFlagStatus
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1120
	.data.b	0,5,2
	.data.w	Safewdt_Hal_GetPwAndLpFlagStatus
	.data.b	6
	.data.b	3
	.data.b	129,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7335
	.data.b	22
	.section	.debug_str		;off: 4855
	.data.b	102,108,97,103,0
	.section	.debug_info		;off: 7336
	.data.w	.Ldw_str_begin+4855
	.data.b	252,4
	.data.b	75
	.data.b	1
	.data.w	.Ldw_begin+791
	.data.b	0
	.data.w	.Ldw_loc_begin+501
	.section	.debug_loc		;off: 501
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7353
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	8
	.section	.debug_str		;off: 4860
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 7363
	.data.w	.Ldw_str_begin+4860
	.data.b	254,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+641
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4867
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,67,108,101,97,114,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7380
	.data.w	.Ldw_str_begin+4867
	.data.b	143,5
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_ClearFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_ClearFlagStatus
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

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_ClearFlagStatus
	.data.w	__ghs_eofn_Safewdt_Hal_ClearFlagStatus-Safewdt_Hal_ClearFlagStatus
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1147
	.data.b	0,5,2
	.data.w	Safewdt_Hal_ClearFlagStatus
	.data.b	6
	.data.b	3
	.data.b	143,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7415
	.data.b	22
	.section	.debug_str		;off: 4895
	.data.b	102,108,97,103,0
	.section	.debug_info		;off: 7416
	.data.w	.Ldw_str_begin+4895
	.data.b	143,5
	.data.b	61
	.data.b	1
	.data.w	.Ldw_begin+916
	.data.b	0
	.data.w	.Ldw_loc_begin+520
	.section	.debug_loc		;off: 520
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	80
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7433
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 4900
	.data.b	114,101,116,0
	.section	.debug_info		;off: 7443
	.data.w	.Ldw_str_begin+4900
	.data.b	145,5
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+550
	.section	.debug_loc		;off: 550
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7461
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4904
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,71,101,116,83,101,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 7464
	.data.w	.Ldw_str_begin+4904
	.data.b	160,5
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.w	Safewdt_Hal_GetSePassword
	.data.w	__ghs_eofn_Safewdt_Hal_GetSePassword
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
	.data.w	Safewdt_Hal_GetSePassword
	.data.w	__ghs_eofn_Safewdt_Hal_GetSePassword-Safewdt_Hal_GetSePassword
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1178
	.data.b	0,5,2
	.data.w	Safewdt_Hal_GetSePassword
	.data.b	6
	.data.b	3
	.data.b	168,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	61
	.data.b	28
	.data.b	11
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7497
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 4930
	.data.b	115,101,77,111,100,101,0
	.section	.debug_info		;off: 7507
	.data.w	.Ldw_str_begin+4930
	.data.b	162,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+500
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+569
	.section	.debug_loc		;off: 569
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7525
	.data.b	7
	.section	.debug_str		;off: 4937
	.data.b	112,114,101,80,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 7526
	.data.w	.Ldw_str_begin+4937
	.data.b	163,5
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+588
	.section	.debug_loc		;off: 588
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7544
	.data.b	8
	.section	.debug_str		;off: 4949
	.data.b	112,97,115,115,119,111,114,100,0
	.section	.debug_info		;off: 7545
	.data.w	.Ldw_str_begin+4949
	.data.b	164,5
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+370
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4958
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,67,108,101,97,114,83,97,102,101,116,121,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 7562
	.data.w	.Ldw_str_begin+4958
	.data.b	187,5
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_ClearSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_ClearSafetyEndinit
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_ClearSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_ClearSafetyEndinit-Safewdt_Hal_ClearSafetyEndinit
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1207
	.data.b	0,5,2
	.data.w	Safewdt_Hal_ClearSafetyEndinit
	.data.b	6
	.data.b	3
	.data.b	187,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	59
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	45
	.data.b	108
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	12
	.data.b	27
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
	.section	.debug_info		;off: 7597
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 4989
	.data.b	116,105,109,101,79,117,116,67,110,116,0
	.section	.debug_info		;off: 7607
	.data.w	.Ldw_str_begin+4989
	.data.b	194,5
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+607
	.section	.debug_loc		;off: 607
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7625
	.data.b	7
	.section	.debug_str		;off: 5000
	.data.b	114,101,116,0
	.section	.debug_info		;off: 7626
	.data.w	.Ldw_str_begin+5000
	.data.b	195,5
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+626
	.section	.debug_loc		;off: 626
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7644
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5004
	.data.b	83,97,102,101,119,100,116,95,72,97,108,95,83,101,116,83,97,102,101,116,121,69,110,100,105,110,105,116,0
	.section	.debug_info		;off: 7647
	.data.w	.Ldw_str_begin+5004
	.data.b	231,5
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.w	Safewdt_Hal_SetSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_SetSafetyEndinit
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Safewdt_Hal_SetSafetyEndinit
	.data.w	__ghs_eofn_Safewdt_Hal_SetSafetyEndinit-Safewdt_Hal_SetSafetyEndinit
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1267
	.data.b	0,5,2
	.data.w	Safewdt_Hal_SetSafetyEndinit
	.data.b	6
	.data.b	3
	.data.b	231,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	45
	.data.b	124
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	29
	.data.b	12
	.data.b	27
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
	.section	.debug_info		;off: 7682
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 5033
	.data.b	116,105,109,101,79,117,116,67,110,116,0
	.section	.debug_info		;off: 7692
	.data.w	.Ldw_str_begin+5033
	.data.b	238,5
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+382
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+645
	.section	.debug_loc		;off: 645
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7710
	.data.b	7
	.section	.debug_str		;off: 5044
	.data.b	114,101,116,0
	.section	.debug_info		;off: 7711
	.data.w	.Ldw_str_begin+5044
	.data.b	239,5
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+358
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+664
	.section	.debug_loc		;off: 664
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7729
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
	.data.b	48
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
	.data.b	4
	.data.b	3
	.data.b	49
	.data.b	5
	.data.b	3
	.data.b	32
	.data.b	6
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	7
	.data.b	3
	.data.b	56
	.data.b	8
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	184,6
	.data.b	83,65,70,69,87,68,84,95,66,65,83,69,95,65,68,68,82,32,40,48,120,67,48,48,52,48,56,48,48,85,41,0
	.data.b	1
	.data.b	186,6
	.data.b	83,65,70,69,87,68,84,95,72,65,76,32,40,40,83,65,70,69,87,68,84,95,77,79,68,85,76,69,32,42,41,83,65,70,69,87,68,84,95,66,65,83,69,95,65,68,68,82,41,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	9
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
	.data.b	9
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	50
	.data.b	10
	.data.b	3
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	25
	.data.b	12
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	35
	.data.b	83,65,70,69,87,68,84,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	56
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	58
	.data.b	9
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
	.data.b	211,1
	.data.b	83,65,70,69,87,68,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	213,1
	.data.b	9
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	62
	.data.b	83,65,70,69,87,68,84,95,77,65,83,75,95,49,50,95,48,32,40,48,120,49,70,70,70,85,41,0
	.data.b	1
	.data.b	64
	.data.b	83,65,70,69,87,68,84,95,77,65,83,75,95,53,95,48,32,40,48,120,51,70,85,41,0
	.data.b	1
	.data.b	69
	.data.b	83,65,70,69,87,68,84,95,80,87,87,68,84,95,70,73,88,69,68,95,80,65,83,83,87,79,82,68,32,40,48,120,66,52,48,85,41,0
	.data.b	1
	.data.b	71
	.data.b	83,65,70,69,87,68,84,95,80,87,83,69,95,70,73,88,69,68,95,80,65,83,83,87,79,82,68,32,40,48,120,50,67,48,48,85,41,0
	.data.b	1
	.data.b	73
	.data.b	83,65,70,69,87,68,84,95,87,68,84,67,78,84,86,65,76,95,84,73,77,69,79,85,84,95,77,65,88,32,40,48,120,51,50,48,48,54,48,48,85,76,41,0
	.data.b	1
	.data.b	75
	.data.b	83,65,70,69,87,68,84,95,83,69,79,85,84,83,84,83,95,84,73,77,69,79,85,84,95,77,65,88,32,40,48,120,49,56,48,48,54,48,48,85,76,41,0
	.data.b	1
	.data.b	77
	.data.b	83,65,70,69,87,68,84,95,87,68,84,95,68,69,76,65,89,32,40,54,85,41,0
	.data.b	1
	.data.b	83
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	85
	.data.b	9
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
	.data.b	138,6
	.data.b	83,65,70,69,87,68,84,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	140,6
	.data.b	9
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 379
	.data.b	0
