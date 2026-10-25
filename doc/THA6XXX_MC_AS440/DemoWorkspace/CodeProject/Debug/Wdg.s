	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682576..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
__callee.Wdg_Init.v.p::
	.size	__callee.Wdg_Init.v.p,0
Wdg_Init::
.LDW01:
	push	{r2,r4-r7,lr}
.LDW11:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.2:
	.endo	..gh.endasm.2

;line480
..lin.3629c2ca..cef6b81a.0_1::
.LDWlin1:
	movs	r2,r0
	moveq	r3,20
	beq	.L775
.L117:
	mov	r6,r0
	ldr	r0,[r6,r4 lsl 2]
	movs	r2,r0
	bne	.L123
.L118:
	mov	r3,224
.L775:

	mov	r1,r0
	mov	r0,102
.L796:

	bl	Det_ReportError
.L798:

	pop	{r2,r4-r7,pc}
.L123:
	ldr	r1,[r0,32]
	cmp	r1,0
	ldrbeq	r0,[r0,36]
	cmpeq	r0,0
.L800:

	popeq	{r2,r4-r7,pc}
	cmp	r4,0
	bne	.L133
.L802:

	bl	SchM_Enter_Wdg_Init
	mov	r3,r4
	mov	r2,6
	mov	r1,10
	mov	r0,1
.L804:

	bl	Sac_Hal_SetAlarmAction
	mov	r5,r0
.L806:

	bl	Sac_Hal_ActivateRunState
	mov	r7,r0
.L808:

	bl	SchM_Exit_Wdg_Init
	cmp	r7,1
	moveq	r3,225
	moveq	r2,r4
	moveq	r1,r4
	moveq	r0,102
.L810:

	bleq	Det_ReportRuntimeError
	cmp	r5,1
.L812:

	popne	{r2,r4-r7,pc}
.L133:
	ldr	r0,[r6,r4 lsl 2]
	ldr	r0,[r0]
.L814:

	bl	Cpuwdt_Hal_InitWdt
	cmp	r0,1
.L816:

	popne	{r2,r4-r7,pc}
	ldr	r0,[r6,r4 lsl 2]
	ldr	r0,[r0,32]
	cmp	r0,0
	beq	.L141
.L818:

	bl	Cpuwdt_Hal_EnableWdt
	cmp	r0,1
.L820:

	popne	{r2,r4-r7,pc}
.L141:
	mov	r0,8
.L822:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	moveq	r5,32
	moveq	r0,3<<14
	beq	.L145
	mov	r5,0
	mov	r0,16
.L824:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	bne	.L137
	mov	r5,38
	mov	r0,3<<16
.L145:
.L826:

	bl	Cpuwdt_Hal_ClearFlagStatus
	cmp	r0,0
	moveq	r5,54
.L137:
	cmp	r5,0
.L828:

	popne	{r2,r4-r7,pc}
	ldr	r0,.L794
	str	r6,[r0]
	ldr	r1,.L795
	ldr	r0,[r6,r4 lsl 2]
	ldr	r1,[r1,r4 lsl 2]
	ldr	r2,[r0,32]
	str	r2,[r1,8]
	cmp	r2,2
	ldreq	r2,[r0,4]
	ldrne	r2,[r0,8]
	ldr	r3,[r0,12]
	ldr	r0,[r0,16]
	sub	r0,r3,r0
	mov	r3,1
	udiv	r0,r0,r2
	stm	r1,{r0,r3}
.LDW21:
.L830:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Wdg_Init::
	.endf	Wdg_Init
;CoreId	r4	local
;RetValue	r5	local
;RegRetValue	r7	local
;WdgError	r5	local
;RetValue	r0	local

;ConfigPtr	r6	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Wdg_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_ConfigPtr:	.space	4
	.endo	Wdg_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Wdg_CoreStatePtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_CoreStatePtr:
	.data.w	Wdg_InformationCore0
	.data.w	Wdg_InformationCore1
	.data.w	Wdg_InformationCore2
	.data.w	Wdg_InformationCore3
	.endo	Wdg_CoreStatePtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_CoreStatePtr
	.section ".ghcalltbl",""
	.align	4
.L797:	.data.w	.L796
	.endo	.L797
	.section ".ghrettbl",""
	.align	4
.L799:	.data.w	.L798
	.endo	.L799
.L801:	.data.w	.L800
	.endo	.L801
	.section ".ghcalltbl",""
.L803:	.data.w	.L802
	.endo	.L803
.L805:	.data.w	.L804
	.endo	.L805
.L807:	.data.w	.L806
	.endo	.L807
.L809:	.data.w	.L808
	.endo	.L809
.L811:	.data.w	.L810
	.endo	.L811
	.section ".ghrettbl",""
.L813:	.data.w	.L812
	.endo	.L813
	.section ".ghcalltbl",""
.L815:	.data.w	.L814
	.endo	.L815
	.section ".ghrettbl",""
.L817:	.data.w	.L816
	.endo	.L817
	.section ".ghcalltbl",""
.L819:	.data.w	.L818
	.endo	.L819
	.section ".ghrettbl",""
.L821:	.data.w	.L820
	.endo	.L821
	.section ".ghcalltbl",""
.L823:	.data.w	.L822
	.endo	.L823
.L825:	.data.w	.L824
	.endo	.L825
.L827:	.data.w	.L826
	.endo	.L827
	.section ".ghrettbl",""
.L829:	.data.w	.L828
	.endo	.L829
.L831:	.data.w	.L830
	.endo	.L831
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Wdg_InformationCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_InformationCore0:	.space	12
	.endo	Wdg_InformationCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_InformationCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Wdg_InformationCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_InformationCore1:	.space	12
	.endo	Wdg_InformationCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_InformationCore1
	.section ".mcal_bss_asil_d_unspecified_core2","awb"
	.align	4
Wdg_InformationCore2..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_InformationCore2:	.space	12
	.endo	Wdg_InformationCore2..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_InformationCore2
	.section ".mcal_bss_asil_d_unspecified_core3","awb"
	.align	4
Wdg_InformationCore3..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.::
Wdg_InformationCore3:	.space	12
	.endo	Wdg_InformationCore3..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.
	.endo	Wdg_InformationCore3
	.data
	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_EnableWdt.i.v

	.global	__caller.Cpuwdt_Hal_InitWdt.i.p

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Wdg_Init.v.v

	.global	__caller.Sac_Hal_ActivateRunState.i.v

	.global	__caller.Sac_Hal_SetAlarmAction.i.iiii

	.global	__caller.SchM_Enter_Wdg_Init.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
__callee.Wdg_SetMode.i.i::
	.size	__callee.Wdg_SetMode.i.i,0
Wdg_SetMode::
.LDW31:
	push	{r4-r8,lr}
	mov	r7,r0
.LDW41:
	b	.L1640

.L794:	.data.w	Wdg_ConfigPtr
	.endo	.L794

.L795:	.data.w	Wdg_CoreStatePtr
	.endo	.L795

.L1640:

;line635
..lin.3629c2ca..45a57bf7.0_2::
.LDWlin2:
..gh.beginasm.4:
	.endo	..gh.beginasm.4
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.5:
	.endo	..gh.endasm.5

;line637
..lin.3629c2ca..45a57bf7.0_3::
.LDWlin3:
	ldr	r1,.L1641
	ldr	r6,[r1,r5 lsl 2]
	ldr	r0,[r6,4]
	mov	r4,1
	cmp	r0,1
	bne	.L842
	ldr	r0,.L1642
	ldr	r0,[r0]
	cmp	r0,0
	bne	.L843
.L842:
	mov	r3,16
	b	.L1615
.L843:
	cmp	r7,2
	ble	.L849
.L844:
	mov	r3,17
.L1615:

	mov	r2,r4
	mov	r1,0
	mov	r0,102
.L1643:

	bl	Det_ReportError
	b	.L848
.L849:
	cmp	r7,0
	ldreq	r0,[r0,r5 lsl 2]
	ldrbeq	r0,[r0,36]
	cmpeq	r0,0
	beq	.L848
	ldr	r0,[r6,8]
	cmp	r7,r0
	beq	.L854
.L1645:

	bl	SchM_Enter_Wdg_SetMode
	mov	r0,2
	cmp	r7,2
	str	r0,[r6,4]
	bne	.L856
	ldr	r0,.L1642
	ldr	r1,[r0]
	ldr	r0,[r6,8]
	ldr	r1,[r1,r5 lsl 2]
	cmp	r0,0
	ldrne	r0,[r6]
	ldrne	r2,[r1,8]
	ldreq	r0,[r1,12]
	ldreq	r2,[r1,16]
	mulne	r2,r0,r2
	subeq	r2,r0,r2
	ldr	r0,[r1,4]
	b	.L1616
.L856:
	cmp	r7,1
	bne	.L862
	ldr	r0,.L1642
	ldr	r1,[r0]
	ldr	r0,[r6,8]
	ldr	r1,[r1,r5 lsl 2]
	cmp	r0,0
	ldrne	r0,[r6]
	ldrne	r2,[r1,4]
	ldreq	r0,[r1,12]
	ldreq	r2,[r1,16]
	mulne	r2,r0,r2
	subeq	r2,r0,r2
.L866:
	ldr	r0,[r1,8]
.L1616:

	udiv	r2,r2,r0
	str	r2,[r6]
	ldr	r1,[r1]
	ldr	r1,[r1,16]
.L1647:

	bl	Cpuwdt_Hal_ChangeHighThv
	b	.L861
.L862:
.L1649:

	bl	Cpuwdt_Hal_DisableWdt
.L861:
	cmp	r0,1
	bne	.L882
	mov	r0,8
.L1651:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	moveq	r5,32
	moveq	r0,3<<14
	beq	.L876
	mov	r5,0
	mov	r0,16
.L1653:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	bne	.L868
	mov	r5,38
	mov	r0,3<<16
.L876:
.L1655:

	bl	Cpuwdt_Hal_ClearFlagStatus
	cmp	r0,0
	moveq	r5,54
.L868:
	cmp	r5,0
	streq	r7,[r6,8]
	moveq	r4,r5
.L882:
	mov	r0,1
	str	r0,[r6,4]
.L1657:

	bl	SchM_Exit_Wdg_SetMode
	b	.L848
.L854:
	mov	r4,0
.L848:
	mov	r0,r4
.LDW51:
.L1659:

	pop	{r4-r8,pc}
__ghs_eofn_Wdg_SetMode::
	.endf	Wdg_SetMode
;ReturnValue	r4	local
;CoreId	r5	local
;RetValue	r0	local
;WdgError	r5	local
;RetValue	r0	local

;Mode	r7	param

	.section ".ghcalltbl",""
.L1644:	.data.w	.L1643
	.endo	.L1644
.L1646:	.data.w	.L1645
	.endo	.L1646
.L1648:	.data.w	.L1647
	.endo	.L1648
.L1650:	.data.w	.L1649
	.endo	.L1650
.L1652:	.data.w	.L1651
	.endo	.L1652
.L1654:	.data.w	.L1653
	.endo	.L1654
.L1656:	.data.w	.L1655
	.endo	.L1656
.L1658:	.data.w	.L1657
	.endo	.L1658
	.section ".ghrettbl",""
.L1660:	.data.w	.L1659
	.endo	.L1660
	.data
	.global	__caller.SchM_Exit_Wdg_SetMode.v.v

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_DisableWdt.i.v

	.global	__caller.Cpuwdt_Hal_ChangeHighThv.i.ii

	.global	__caller.Cpuwdt_Hal_ChangeHighThv.i.ii

	.global	__caller.SchM_Enter_Wdg_SetMode.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Wdg_ConfigPtr - Wdg_ConfigPtr) +0 == 0
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
__callee.Wdg_SetTriggerCondition.v.i::
	.size	__callee.Wdg_SetTriggerCondition.v.i,0
Wdg_SetTriggerCondition::
.LDW61:
	push	{r2,r4-r7,lr}
	mov	r7,r0
.LDW71:
	b	.L2644

.L1641:	.data.w	Wdg_CoreStatePtr
	.endo	.L1641

.L1642:	.data.w	Wdg_ConfigPtr
	.endo	.L1642

.L2644:

;line804
..lin.3629c2ca..3778b24d.0_4::
.LDWlin4:
..gh.beginasm.7:
	.endo	..gh.beginasm.7
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.8:
	.endo	..gh.endasm.8

;line807
..lin.3629c2ca..3778b24d.0_5::
.LDWlin5:
	ldr	r1,.L2645
	ldr	r5,[r1,r4 lsl 2]
	ldr	r0,[r5,4]
	cmp	r0,1
	bne	.L1668
	ldr	r6,.L2646
	ldr	r0,[r6]
	cmp	r0,0
	bne	.L1667
.L1668:
	mov	r3,16
	b	.L2628
.L1667:
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,20]
	cmp	r0,r7
	bhs	.L1671
.L1672:
	mov	r3,19
.L2628:

	mov	r2,3
	mov	r1,0
	mov	r0,102
.L2647:

	bl	Det_ReportError
.L2649:

	pop	{r2,r4-r7,pc}
.L1671:
	ldr	r0,[r5,8]
	cmp	r0,0
.L2651:

	popeq	{r2,r4-r7,pc}
.L2653:

	bl	SchM_Enter_Wdg_SetTriggerCondition
	mov	r0,2
	cmp	r7,0
	str	r0,[r5,4]
	beq	.L1676
	ldr	r1,[r6]
	ldr	r1,[r1,r4 lsl 2]
	ldr	r0,[r1,24]
	ldr	r2,[r1,16]
	mul	r0,r7,r0
	cmp	r0,r2
	movlo	r0,0
	subhs	r0,r0,r2
	ldr	r2,[r5,8]
	cmp	r2,2
	ldreq	r1,[r1,4]
	ldrne	r1,[r1,8]
	udiv	r0,r0,r1
	str	r0,[r5]
.L2655:

	bl	Cpuwdt_Hal_ServiceWdt
	mov	r4,r0
	b	.L1684
.L1676:
	mov	r1,1
	str	r7,[r5]
	mov	r0,r1
.L2657:

	bl	Cpuwdt_Hal_ChangeHighThv
	mov	r4,r0
	mov	r0,8
.L2659:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	bne	.L1689
	mov	r0,3<<14
.L2661:

	bl	Cpuwdt_Hal_ClearFlagStatus
	b	.L1684
.L1689:
	mov	r0,16
.L2663:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	cmp	r0,1
	moveq	r0,3<<16
.L2665:

	bleq	Cpuwdt_Hal_ClearFlagStatus
.L1684:
	mov	r0,1
	str	r0,[r5,4]
.L2667:

	bl	SchM_Exit_Wdg_SetTriggerCondition
	movs	r1,r4
	moveq	r3,225
	moveq	r2,3
	moveq	r0,102
.L2669:

	bleq	Det_ReportRuntimeError
.LDW81:
.L2671:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Wdg_SetTriggerCondition::
	.endf	Wdg_SetTriggerCondition
;CoreId	r4	local
;RetValue	r4	local
;FirstLevelTick	r0	local
;TimeoutTick	r0	local

;Timeout	r7	param

	.section ".ghcalltbl",""
.L2648:	.data.w	.L2647
	.endo	.L2648
	.section ".ghrettbl",""
.L2650:	.data.w	.L2649
	.endo	.L2650
.L2652:	.data.w	.L2651
	.endo	.L2652
	.section ".ghcalltbl",""
.L2654:	.data.w	.L2653
	.endo	.L2654
.L2656:	.data.w	.L2655
	.endo	.L2656
.L2658:	.data.w	.L2657
	.endo	.L2658
.L2660:	.data.w	.L2659
	.endo	.L2660
.L2662:	.data.w	.L2661
	.endo	.L2662
.L2664:	.data.w	.L2663
	.endo	.L2664
.L2666:	.data.w	.L2665
	.endo	.L2666
.L2668:	.data.w	.L2667
	.endo	.L2668
.L2670:	.data.w	.L2669
	.endo	.L2670
	.section ".ghrettbl",""
.L2672:	.data.w	.L2671
	.endo	.L2672
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Wdg_SetTriggerCondition.v.v

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_ChangeHighThv.i.ii

	.global	__caller.Cpuwdt_Hal_ServiceWdt.i.v

	.global	__caller.SchM_Enter_Wdg_SetTriggerCondition.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
__callee.Wdg_GetVersionInfo.v.p::
	.size	__callee.Wdg_GetVersionInfo.v.p,0
Wdg_GetVersionInfo::
.LDW91:
.LDW02:
	movs	r1,r0
	moveq	r3,20
	moveq	r2,4
	moveq	r0,102
.L2763:

	beq	Det_ReportError
.L2675:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,102
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW12:
.L2765:

	ret	
__ghs_eofn_Wdg_GetVersionInfo::
	.endf	Wdg_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L2725:
	.endo	.L2725
	.section ".ghtailcalltbl",""
	.align	4
.L2764:	.data.w	.L2763
	.endo	.L2764
	.section ".ghrettbl",""
.L2766:	.data.w	.L2765
	.endo	.L2766
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
__callee.Wdg_RefreshTimer_ISRHandler.v.v::
	.size	__callee.Wdg_RefreshTimer_ISRHandler.v.v,0
Wdg_RefreshTimer_ISRHandler::
.LDW22:
	push	{r4-r6,lr}
.LDW32:
.L3190:

	bl	SchM_Enter_Wdg_ISRHandler
	b	.L3187

.L2645:	.data.w	Wdg_CoreStatePtr
	.endo	.L2645

.L2646:	.data.w	Wdg_ConfigPtr
	.endo	.L2646

.L3187:

;line973
..lin.3629c2ca..54f60ea1.0_6::
.LDWlin6:
..gh.beginasm.11:
	.endo	..gh.beginasm.11
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.12:
	.endo	..gh.endasm.12

	mov	r4,r0
;line975
..lin.3629c2ca..54f60ea1.0_7::
.LDWlin7:
	mov	r0,192
.L3192:

	bl	Cpuwdt_Hal_ClearFlagStatus
	ldr	r1,.L3188
	ldr	r5,[r1,r4 lsl 2]
	mov	r6,r0
	ldr	r0,[r5,4]
	cmp	r0,1
	cmpeq	r6,1
	bne	.L2794
	ldr	r0,[r5,8]
	cmp	r0,0
	beq	.L2776
	ldr	r0,[r5]
	subs	r0,r0,1
	blo	.L2778
	mov	r1,2
	stm	r5,{r0-r1}
.L3194:

	bl	Cpuwdt_Hal_ServiceWdt
	mov	r6,r0
	mov	r0,8
.L3196:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	mov	r1,3<<14
	cmp	r0,1
	beq	.L3017
	mov	r0,16
.L3198:

	bl	Cpuwdt_Hal_GetAlarmFlagStatus
	mov	r1,3<<16
	cmp	r0,1
.L3017:
	moveq	r0,r1
.L3200:

	bleq	Cpuwdt_Hal_ClearFlagStatus
.L2780:
	mov	r0,1
	str	r0,[r5,4]
.L2794:
.L3202:

	bl	SchM_Exit_Wdg_ISRHandler
	movs	r1,r6
	moveq	r3,225
	moveq	r2,16
	moveq	r0,102
.L3204:

	bleq	Det_ReportRuntimeError
.L3206:

	pop	{r4-r6,pc}
.L2778:
.L3208:

	bl	SchM_Exit_Wdg_ISRHandler
	ldr	r1,.L3189
	ldr	r0,[r1]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,28]
	cmp	r0,0
.L3210:

	blxne	r0
.L3212:

	pop	{r4-r6,pc}
.L2776:
.L3214:

	bl	SchM_Exit_Wdg_ISRHandler
	mov	r3,37
	mov	r2,16
	mov	r1,0
	mov	r0,102
.L3216:

	bl	Det_ReportError
.LDW42:
.L3218:

	pop	{r4-r6,pc}
__ghs_eofn_Wdg_RefreshTimer_ISRHandler::
	.endf	Wdg_RefreshTimer_ISRHandler
;CoreId	r4	local
;RetValue	r6	local

	.section ".ghcalltbl",""
.L3191:	.data.w	.L3190
	.endo	.L3191
.L3193:	.data.w	.L3192
	.endo	.L3193
.L3195:	.data.w	.L3194
	.endo	.L3195
.L3197:	.data.w	.L3196
	.endo	.L3197
.L3199:	.data.w	.L3198
	.endo	.L3199
.L3201:	.data.w	.L3200
	.endo	.L3201
.L3203:	.data.w	.L3202
	.endo	.L3203
.L3205:	.data.w	.L3204
	.endo	.L3205
	.section ".ghrettbl",""
.L3207:	.data.w	.L3206
	.endo	.L3207
	.section ".ghcalltbl",""
.L3209:	.data.w	.L3208
	.endo	.L3209
.L3211:	.data.w	.L3210
	.endo	.L3211
	.section ".ghrettbl",""
.L3213:	.data.w	.L3212
	.endo	.L3213
	.section ".ghcalltbl",""
.L3215:	.data.w	.L3214
	.endo	.L3215
.L3217:	.data.w	.L3216
	.endo	.L3217
	.section ".ghrettbl",""
.L3219:	.data.w	.L3218
	.endo	.L3219
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Wdg_ISRHandler.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Wdg_ISRHandler.v.v

	.global	__caller.SchM_Exit_Wdg_ISRHandler.v.v

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_GetAlarmFlagStatus.i.i

	.global	__caller.Cpuwdt_Hal_ServiceWdt.i.v

	.global	__caller.Cpuwdt_Hal_ClearFlagStatus.i.i

	.global	__caller.SchM_Enter_Wdg_ISRHandler.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Wdg_ConfigPtr - Wdg_ConfigPtr) +0 == 0
..gh.f.a.1.e.13:
	.endo	..gh.f.a.1.e.13
__callee.Wdg_GetCurrentTimeout.i.v::
	.size	__callee.Wdg_GetCurrentTimeout.i.v,0
Wdg_GetCurrentTimeout::
.LDW52:
	push	{r2,r4-r5,lr}
.LDW62:
	b	.L3385

.L3188:	.data.w	Wdg_CoreStatePtr
	.endo	.L3188

.L3189:	.data.w	Wdg_ConfigPtr
	.endo	.L3189

.L3385:

;line1070
..lin.3629c2ca..9e6365b0.0_8::
.LDWlin8:
..gh.beginasm.14:
	.endo	..gh.beginasm.14
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.15:
	.endo	..gh.endasm.15

	mov	r5,r0
;line1071
..lin.3629c2ca..9e6365b0.0_9::
.LDWlin9:
	mov	r4,0
.L3388:

	bl	Cpuwdt_Hal_GetWdgCounter
	ldr	r2,.L3386
	ldr	r2,[r2,r5 lsl 2]
	ldr	r3,[r2,8]
	cmp	r3,0
	beq	.L3226
	ldr	r1,.L3387
	ldr	r1,[r1]
	ldr	r1,[r1,r5 lsl 2]
	cmp	r3,2
	ldreq	r3,[r1,4]
	ldrne	r3,[r1,8]
	ldr	r2,[r2]
	add	r2,r2,1
	mul	r2,r3,r2
	cmp	r2,r0
	ldrhi	r1,[r1,24]
	subhi	r0,r2,r0
	udivhi	r4,r0,r1
	uxthhi	r4,r4
.L3226:
	mov	r0,r4
.LDW72:
.L3390:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Wdg_GetCurrentTimeout::
	.endf	Wdg_GetCurrentTimeout
;CoreId	r5	local
;Timeout	r4	local
;WdtCounter	r0	local
;RefreshTime	r3	local

	.section ".ghcalltbl",""
.L3389:	.data.w	.L3388
	.endo	.L3389
	.section ".ghrettbl",""
.L3391:	.data.w	.L3390
	.endo	.L3391
	.data
	.global	__caller.Cpuwdt_Hal_GetWdgCounter.i.v

	.section ".mcal_text_asil_d","ax"

.L3386:	.data.w	Wdg_CoreStatePtr
	.endo	.L3386

.L3387:	.data.w	Wdg_ConfigPtr
	.endo	.L3387

;Wdg_InformationCore0	Wdg_InformationCore0	static
;Wdg_InformationCore1	Wdg_InformationCore1	static
;Wdg_InformationCore2	Wdg_InformationCore2	static
;Wdg_InformationCore3	Wdg_InformationCore3	static
;Wdg_CoreStatePtr	Wdg_CoreStatePtr	static
;Wdg_ConfigPtr	Wdg_ConfigPtr	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682576..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	165,14,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,87,100,103,92,115,114,99,47,87,100,103,46,99,0
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
	.data.b	17,9,0,0
	.data.b	2,0
	.data.b	132,6,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,87,100,103,92,115,114,99,47,87,100,103,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,87,100,103,92,105,110,99,108,117,100,101,92,87,100,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,87,100,103,92,105,110,99,108,117,100,101,92,87,100,103,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,66,83,87,92,87,100,103,73,102,92,87,100,103,73,102,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,87,100,103,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,87,100,103,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,87,100,103,92,105,110,99,108,117,100,101,92,87,100,103,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,87,100,103,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,87,100,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,99,92,105,110,99,92,115,97,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,97,99,92,105,110,99,92,115,97,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,97,99,95,77,101,109,77,97,112,46,104,0
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
	.data.w	.Ldw_begin+721
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
	.data.w	.Ldw_begin+506
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1683

	.section	.debug_abbrev		;off: 39
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 75
	.data.b	53
	.data.w	.Ldw_begin+70

	.section	.debug_abbrev		;off: 46
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 80
	.data.b	47
	.data.w	.Ldw_begin+75

	.data.b	74
	.data.w	.Ldw_begin+554
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+80
	.data.b	0

	.section	.debug_abbrev		;off: 53
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 97
	.data.b	23
	.data.w	.Ldw_begin+733
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+554
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+733
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1316
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

	.section	.debug_info		;off: 125
	.data.b	23
	.data.w	.Ldw_begin+75
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+554
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1316
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 146
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+518
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+653

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+161
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+518
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	105,110,116,0
	.section	.debug_info		;off: 186
	.data.w	.Ldw_str_begin+260
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 264
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 193
	.data.w	.Ldw_str_begin+264
	.data.b	7
	.data.b	4

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+199

	.data.b	47
	.data.w	.Ldw_begin+1340

	.data.b	53
	.data.w	.Ldw_begin+207

	.data.b	47
	.data.w	.Ldw_begin+1648

	.data.b	53
	.data.w	.Ldw_begin+217

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+222

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 234
	.data.b	56
	.data.w	.Ldw_begin+185
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

	.section	.debug_info		;off: 242
	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1469

	.data.b	47
	.data.w	.Ldw_begin+243

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+248

	.data.b	56
	.data.w	.Ldw_begin+185
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1265

	.data.b	53
	.data.w	.Ldw_begin+269

	.data.b	47
	.data.w	.Ldw_begin+274

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+279
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+530
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+530
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+530
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+924
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+992
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1116
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

	.data.b	74
	.data.w	.Ldw_begin+494
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1841
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2152
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2238
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2279
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2323
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+554
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+518
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+554
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+518
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+506
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 495
	.data.w	.Ldw_str_begin+277
	.data.b	51
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+42

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

	.section	.debug_info		;off: 506
	.data.b	45
	.section	.debug_str		;off: 285
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 507
	.data.w	.Ldw_str_begin+285
	.data.b	56
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 291
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 519
	.data.w	.Ldw_str_begin+291
	.data.b	60
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+145

	.data.b	45
	.section	.debug_str		;off: 298
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 531
	.data.w	.Ldw_str_begin+298
	.data.b	64
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 305
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 543
	.data.w	.Ldw_str_begin+305
	.data.b	68
	.data.b	29
	.data.b	12
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 555
	.data.w	.Ldw_str_begin+312
	.data.b	39
	.data.b	15
	.data.b	7
	.data.w	.Ldw_begin+506

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	7
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

	.section	.debug_info		;off: 572
	.data.b	40
	.section	.debug_str		;off: 327
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 573
	.data.w	.Ldw_str_begin+327
	.data.b	63
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+518
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

	.section	.debug_info		;off: 588
	.data.b	40
	.section	.debug_str		;off: 336
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 589
	.data.w	.Ldw_str_begin+336
	.data.b	64
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+518
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 345
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 605
	.data.w	.Ldw_str_begin+345
	.data.b	65
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+506
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 621
	.data.w	.Ldw_str_begin+362
	.data.b	66
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+506
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 637
	.data.w	.Ldw_str_begin+379
	.data.b	67
	.data.b	13
	.data.b	7
	.data.w	.Ldw_begin+506
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 396
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 654
	.data.w	.Ldw_str_begin+396
	.data.b	68
	.data.b	2
	.data.b	7
	.data.w	.Ldw_begin+566

	.data.b	52
	.section	.debug_str		;off: 416
	.data.b	0
	.section	.debug_info		;off: 666
	.data.w	.Ldw_str_begin+416
	.data.b	36
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

	.section	.debug_info		;off: 675
	.data.b	51
	.section	.debug_str		;off: 417
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 676
	.data.w	.Ldw_str_begin+417
	.data.b	37
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

	.section	.debug_info		;off: 684
	.data.b	51
	.section	.debug_str		;off: 434
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 685
	.data.w	.Ldw_str_begin+434
	.data.b	38
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 451
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 694
	.data.w	.Ldw_str_begin+451
	.data.b	39
	.data.b	5
	.data.b	13
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 468
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 703
	.data.w	.Ldw_str_begin+468
	.data.b	40
	.data.b	5
	.data.b	13
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 485
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 712
	.data.w	.Ldw_str_begin+485
	.data.b	41
	.data.b	5
	.data.b	13
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 502
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 722
	.data.w	.Ldw_str_begin+502
	.data.b	42
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+665

	.data.b	45
	.section	.debug_str		;off: 514
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 734
	.data.w	.Ldw_str_begin+514
	.data.b	32
	.data.b	21
	.data.b	6
	.data.w	.Ldw_begin+721

	.data.b	52
	.section	.debug_str		;off: 528
	.data.b	0
	.section	.debug_info		;off: 746
	.data.w	.Ldw_str_begin+528
	.data.b	45
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 529
	.data.b	67,80,85,87,68,84,95,80,87,77,79,68,69,95,70,73,88,69,68,0
	.section	.debug_info		;off: 756
	.data.w	.Ldw_str_begin+529
	.data.b	46
	.data.b	5
	.data.b	15
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 549
	.data.b	67,80,85,87,68,84,95,80,87,77,79,68,69,95,68,89,78,65,77,73,67,95,49,0
	.section	.debug_info		;off: 765
	.data.w	.Ldw_str_begin+549
	.data.b	47
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 573
	.data.b	67,80,85,87,68,84,95,80,87,77,79,68,69,95,68,89,78,65,77,73,67,95,50,0
	.section	.debug_info		;off: 774
	.data.w	.Ldw_str_begin+573
	.data.b	48
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 597
	.data.b	67,112,117,119,100,116,95,80,119,77,111,100,101,0
	.section	.debug_info		;off: 784
	.data.w	.Ldw_str_begin+597
	.data.b	49
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+745

	.data.b	52
	.section	.debug_str		;off: 611
	.data.b	0
	.section	.debug_info		;off: 796
	.data.w	.Ldw_str_begin+611
	.data.b	53
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 612
	.data.b	67,80,85,87,68,84,95,67,76,75,68,73,86,95,84,72,82,79,85,71,72,0
	.section	.debug_info		;off: 806
	.data.w	.Ldw_str_begin+612
	.data.b	54
	.data.b	5
	.data.b	15
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 634
	.data.b	67,80,85,87,68,84,95,67,76,75,68,73,86,95,54,52,0
	.section	.debug_info		;off: 815
	.data.w	.Ldw_str_begin+634
	.data.b	55
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 651
	.data.b	67,80,85,87,68,84,95,67,76,75,68,73,86,95,50,53,54,0
	.section	.debug_info		;off: 824
	.data.w	.Ldw_str_begin+651
	.data.b	56
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 669
	.data.b	67,80,85,87,68,84,95,67,76,75,68,73,86,95,49,54,51,56,52,0
	.section	.debug_info		;off: 833
	.data.w	.Ldw_str_begin+669
	.data.b	57
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 689
	.data.b	67,112,117,119,100,116,95,67,108,107,68,105,118,0
	.section	.debug_info		;off: 843
	.data.w	.Ldw_str_begin+689
	.data.b	58
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+795

	.data.b	52
	.section	.debug_str		;off: 703
	.data.b	0
	.section	.debug_info		;off: 855
	.data.w	.Ldw_str_begin+703
	.data.b	62
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 704
	.data.b	67,80,85,87,68,84,95,79,85,84,77,79,68,69,95,65,76,65,82,77,0
	.section	.debug_info		;off: 865
	.data.w	.Ldw_str_begin+704
	.data.b	63
	.data.b	5
	.data.b	15
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 725
	.data.b	67,80,85,87,68,84,95,79,85,84,77,79,68,69,95,73,78,84,69,82,82,85,80,84,0
	.section	.debug_info		;off: 874
	.data.w	.Ldw_str_begin+725
	.data.b	64
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 750
	.data.b	67,112,117,119,100,116,95,79,117,116,77,111,100,101,0
	.section	.debug_info		;off: 884
	.data.w	.Ldw_str_begin+750
	.data.b	65
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+854

	.data.b	52
	.section	.debug_str		;off: 765
	.data.b	0
	.section	.debug_info		;off: 896
	.data.w	.Ldw_str_begin+765
	.data.b	69
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 766
	.data.b	67,80,85,87,68,84,95,83,84,65,84,85,83,95,82,69,83,69,84,0
	.section	.debug_info		;off: 906
	.data.w	.Ldw_str_begin+766
	.data.b	70
	.data.b	5
	.data.b	15
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 786
	.data.b	67,80,85,87,68,84,95,83,84,65,84,85,83,95,83,69,84,0
	.section	.debug_info		;off: 915
	.data.w	.Ldw_str_begin+786
	.data.b	71
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 804
	.data.b	67,112,117,119,100,116,95,83,116,97,116,117,115,0
	.section	.debug_info		;off: 925
	.data.w	.Ldw_str_begin+804
	.data.b	72
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+895

	.data.b	52
	.section	.debug_str		;off: 818
	.data.b	0
	.section	.debug_info		;off: 937
	.data.w	.Ldw_str_begin+818
	.data.b	76
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 819
	.data.b	67,80,85,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,67,69,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 947
	.data.w	.Ldw_str_begin+819
	.data.b	77
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 852
	.data.b	67,80,85,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 956
	.data.w	.Ldw_str_begin+852
	.data.b	78
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 891
	.data.b	67,80,85,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,83,69,67,79,78,68,87,68,84,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 965
	.data.w	.Ldw_str_begin+891
	.data.b	79
	.data.b	5
	.data.b	15
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 931
	.data.b	67,80,85,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,80,65,83,83,87,79,82,68,69,82,82,79,82,0
	.section	.debug_info		;off: 974
	.data.w	.Ldw_str_begin+931
	.data.b	80
	.data.b	5
	.data.b	15
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 968
	.data.b	67,80,85,87,68,84,95,65,76,65,82,77,83,84,65,84,85,83,70,76,65,71,95,82,69,71,69,82,82,79,82,0
	.section	.debug_info		;off: 983
	.data.w	.Ldw_str_begin+968
	.data.b	81
	.data.b	5
	.data.b	15
	.data.b	16

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1000
	.data.b	67,112,117,119,100,116,95,65,108,97,114,109,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 993
	.data.w	.Ldw_str_begin+1000
	.data.b	82
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+936

	.data.b	52
	.section	.debug_str		;off: 1023
	.data.b	0
	.section	.debug_info		;off: 1005
	.data.w	.Ldw_str_begin+1023
	.data.b	100
	.data.b	1
	.data.b	15
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1024
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,67,69,65,76,65,82,77,0
	.section	.debug_info		;off: 1015
	.data.w	.Ldw_str_begin+1024
	.data.b	101
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1055
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,67,69,73,78,84,82,0
	.section	.debug_info		;off: 1024
	.data.w	.Ldw_str_begin+1055
	.data.b	102
	.data.b	5
	.data.b	15
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1085
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,65,76,65,82,77,0
	.section	.debug_info		;off: 1033
	.data.w	.Ldw_str_begin+1085
	.data.b	103
	.data.b	5
	.data.b	15
	.data.b	48

	.data.b	51
	.section	.debug_str		;off: 1122
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,70,73,82,83,84,87,68,84,73,78,84,69,82,82,85,80,84,0
	.section	.debug_info		;off: 1042
	.data.w	.Ldw_str_begin+1122
	.data.b	104
	.data.b	5
	.data.b	15
	.data.b	192,1

	.data.b	51
	.section	.debug_str		;off: 1163
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,83,69,67,79,78,68,87,68,84,65,76,65,82,77,0
	.section	.debug_info		;off: 1052
	.data.w	.Ldw_str_begin+1163
	.data.b	105
	.data.b	5
	.data.b	15
	.data.b	128,6

	.data.b	51
	.section	.debug_str		;off: 1201
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,67,80,85,87,68,84,76,80,0
	.section	.debug_info		;off: 1062
	.data.w	.Ldw_str_begin+1201
	.data.b	106
	.data.b	5
	.data.b	15
	.data.b	128,24

	.data.b	51
	.section	.debug_str		;off: 1233
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,87,68,84,76,80,0
	.section	.debug_info		;off: 1072
	.data.w	.Ldw_str_begin+1233
	.data.b	107
	.data.b	5
	.data.b	15
	.data.b	128,224,0

	.data.b	51
	.section	.debug_str		;off: 1262
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,80,65,83,83,87,79,82,68,65,76,65,82,77,0
	.section	.debug_info		;off: 1083
	.data.w	.Ldw_str_begin+1262
	.data.b	108
	.data.b	5
	.data.b	15
	.data.b	128,128,3

	.data.b	51
	.section	.debug_str		;off: 1299
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,82,69,71,65,76,65,82,77,0
	.section	.debug_info		;off: 1094
	.data.w	.Ldw_str_begin+1299
	.data.b	109
	.data.b	5
	.data.b	15
	.data.b	128,128,12

	.data.b	51
	.section	.debug_str		;off: 1331
	.data.b	67,80,85,87,68,84,95,67,76,69,65,82,83,84,65,84,85,83,70,76,65,71,95,65,76,76,67,76,69,65,82,0
	.section	.debug_info		;off: 1105
	.data.w	.Ldw_str_begin+1331
	.data.b	110
	.data.b	5
	.data.b	15
	.data.b	255,255,15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1363
	.data.b	67,112,117,119,100,116,95,67,108,101,97,114,83,116,97,116,117,115,70,108,97,103,0
	.section	.debug_info		;off: 1117
	.data.w	.Ldw_str_begin+1363
	.data.b	111
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+1004

	.data.b	71
	.data.b	121
	.data.b	1
	.data.b	15
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1386
	.data.b	112,119,87,100,116,73,110,105,116,0
	.section	.debug_info		;off: 1135
	.data.w	.Ldw_str_begin+1386
	.data.b	122
	.data.b	12
	.data.b	15
	.data.w	.Ldw_begin+518
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1396
	.data.b	119,100,116,76,111,119,84,104,118,48,0
	.section	.debug_info		;off: 1151
	.data.w	.Ldw_str_begin+1396
	.data.b	123
	.data.b	12
	.data.b	15
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1407
	.data.b	119,100,116,76,111,119,84,104,118,49,0
	.section	.debug_info		;off: 1167
	.data.w	.Ldw_str_begin+1407
	.data.b	124
	.data.b	12
	.data.b	15
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1418
	.data.b	119,100,116,72,105,103,104,84,104,118,48,0
	.section	.debug_info		;off: 1183
	.data.w	.Ldw_str_begin+1418
	.data.b	125
	.data.b	12
	.data.b	15
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1430
	.data.b	119,100,116,72,105,103,104,84,104,118,49,0
	.section	.debug_info		;off: 1199
	.data.w	.Ldw_str_begin+1430
	.data.b	126
	.data.b	12
	.data.b	15
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1442
	.data.b	119,100,116,70,105,114,79,117,116,77,111,100,101,0
	.section	.debug_info		;off: 1215
	.data.w	.Ldw_str_begin+1442
	.data.b	127
	.data.b	20
	.data.b	15
	.data.w	.Ldw_begin+883
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1456
	.data.b	112,119,87,100,116,77,111,100,101,0
	.section	.debug_info		;off: 1231
	.data.w	.Ldw_str_begin+1456
	.data.b	128,1
	.data.b	19
	.data.b	15
	.data.w	.Ldw_begin+783
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1466
	.data.b	119,100,116,67,108,107,68,105,118,0
	.section	.debug_info		;off: 1248
	.data.w	.Ldw_str_begin+1466
	.data.b	129,1
	.data.b	19
	.data.b	15
	.data.w	.Ldw_begin+842
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1476
	.data.b	67,112,117,119,100,116,95,87,100,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 1266
	.data.w	.Ldw_str_begin+1476
	.data.b	130,1
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+1128

	.data.b	52
	.section	.debug_str		;off: 1493
	.data.b	0
	.section	.debug_info		;off: 1279
	.data.w	.Ldw_str_begin+1493
	.data.b	39
	.data.b	1
	.data.b	32
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1494
	.data.b	87,68,71,73,70,95,79,70,70,95,77,79,68,69,0
	.section	.debug_info		;off: 1289
	.data.w	.Ldw_str_begin+1494
	.data.b	40
	.data.b	5
	.data.b	32
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1509
	.data.b	87,68,71,73,70,95,83,76,79,87,95,77,79,68,69,0
	.section	.debug_info		;off: 1298
	.data.w	.Ldw_str_begin+1509
	.data.b	41
	.data.b	5
	.data.b	32
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1525
	.data.b	87,68,71,73,70,95,70,65,83,84,95,77,79,68,69,0
	.section	.debug_info		;off: 1307
	.data.w	.Ldw_str_begin+1525
	.data.b	42
	.data.b	5
	.data.b	32
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1541
	.data.b	87,100,103,73,102,95,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 1317
	.data.w	.Ldw_str_begin+1541
	.data.b	43
	.data.b	2
	.data.b	32
	.data.w	.Ldw_begin+1278

	.data.b	45
	.section	.debug_str		;off: 1556
	.data.b	87,100,103,95,78,111,116,105,102,70,117,110,99,116,105,111,110,80,116,114,84,121,112,101,0
	.section	.debug_info		;off: 1329
	.data.w	.Ldw_str_begin+1556
	.data.b	46
	.data.b	16
	.data.b	3
	.data.w	.Ldw_begin+202

	.data.b	45
	.section	.debug_str		;off: 1581
	.data.b	87,100,103,95,68,101,118,105,99,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1341
	.data.w	.Ldw_str_begin+1581
	.data.b	48
	.data.b	26
	.data.b	3
	.data.w	.Ldw_begin+1265

	.data.b	45
	.section	.debug_str		;off: 1602
	.data.b	87,100,103,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 1353
	.data.w	.Ldw_str_begin+1602
	.data.b	50
	.data.b	23
	.data.b	3
	.data.w	.Ldw_begin+924

	.data.b	52
	.section	.debug_str		;off: 1617
	.data.b	0
	.section	.debug_info		;off: 1365
	.data.w	.Ldw_str_begin+1617
	.data.b	56
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1618
	.data.b	87,68,71,95,85,78,73,78,73,84,0
	.section	.debug_info		;off: 1375
	.data.w	.Ldw_str_begin+1618
	.data.b	57
	.data.b	5
	.data.b	3
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1629
	.data.b	87,68,71,95,73,68,76,69,0
	.section	.debug_info		;off: 1384
	.data.w	.Ldw_str_begin+1629
	.data.b	58
	.data.b	5
	.data.b	3
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1638
	.data.b	87,68,71,95,66,85,83,89,0
	.section	.debug_info		;off: 1393
	.data.w	.Ldw_str_begin+1638
	.data.b	59
	.data.b	5
	.data.b	3
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1647
	.data.b	87,100,103,95,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 1403
	.data.w	.Ldw_str_begin+1647
	.data.b	60
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1364

	.data.b	71
	.data.b	71
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1661
	.data.b	87,100,103,95,84,114,105,103,103,101,114,67,111,110,100,105,116,105,111,110,84,105,109,101,0
	.section	.debug_info		;off: 1421
	.data.w	.Ldw_str_begin+1661
	.data.b	73
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1686
	.data.b	87,100,103,95,67,117,114,114,101,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 1437
	.data.w	.Ldw_str_begin+1686
	.data.b	75
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+1402
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1704
	.data.b	87,100,103,95,67,117,114,114,101,110,116,77,111,100,101,0
	.section	.debug_info		;off: 1453
	.data.w	.Ldw_str_begin+1704
	.data.b	77
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+1316
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1720
	.data.b	87,100,103,95,67,111,114,101,73,110,102,111,114,109,97,116,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 1470
	.data.w	.Ldw_str_begin+1720
	.data.b	78
	.data.b	3
	.data.b	3
	.data.w	.Ldw_begin+1414

	.data.b	71
	.data.b	83
	.data.b	1
	.data.b	3
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1744
	.data.b	68,101,118,105,99,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 1488
	.data.w	.Ldw_str_begin+1744
	.data.b	85
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+212
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1760
	.data.b	70,97,115,116,77,111,100,101,82,101,102,114,101,115,104,84,105,109,101,0
	.section	.debug_info		;off: 1504
	.data.w	.Ldw_str_begin+1760
	.data.b	87
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1780
	.data.b	83,108,111,119,77,111,100,101,82,101,102,114,101,115,104,84,105,109,101,0
	.section	.debug_info		;off: 1520
	.data.w	.Ldw_str_begin+1780
	.data.b	89
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1800
	.data.b	73,110,105,116,105,97,108,84,105,109,101,111,117,116,0
	.section	.debug_info		;off: 1536
	.data.w	.Ldw_str_begin+1800
	.data.b	91
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1815
	.data.b	84,105,109,101,66,101,102,111,114,101,82,101,115,101,116,0
	.section	.debug_info		;off: 1552
	.data.w	.Ldw_str_begin+1815
	.data.b	93
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1831
	.data.b	77,97,120,84,105,109,101,111,117,116,0
	.section	.debug_info		;off: 1568
	.data.w	.Ldw_str_begin+1831
	.data.b	95
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1842
	.data.b	67,108,111,99,107,70,114,101,113,117,101,110,99,121,75,72,122,0
	.section	.debug_info		;off: 1584
	.data.w	.Ldw_str_begin+1842
	.data.b	97
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+530
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1860
	.data.b	87,100,103,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 1600
	.data.w	.Ldw_str_begin+1860
	.data.b	99
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+1328
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1879
	.data.b	68,101,102,97,117,108,116,77,111,100,101,0
	.section	.debug_info		;off: 1616
	.data.w	.Ldw_str_begin+1879
	.data.b	101
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+1316
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1891
	.data.b	68,105,115,97,98,108,101,65,108,108,111,119,101,100,0
	.section	.debug_info		;off: 1632
	.data.w	.Ldw_str_begin+1891
	.data.b	103
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+494
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1906
	.data.b	87,100,103,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1649
	.data.w	.Ldw_str_begin+1906
	.data.b	104
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+1481

	.data.b	71
	.data.b	108
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1925
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 1667
	.data.w	.Ldw_str_begin+1925
	.data.b	110
	.data.b	39
	.data.b	3
	.data.w	.Ldw_begin+227
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1939
	.data.b	87,100,103,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 1684
	.data.w	.Ldw_str_begin+1939
	.data.b	111
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+1660

	.data.b	52
	.section	.debug_str		;off: 1954
	.data.b	0
	.section	.debug_info		;off: 1696
	.data.w	.Ldw_str_begin+1954
	.data.b	53
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1955
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,48,0
	.section	.debug_info		;off: 1706
	.data.w	.Ldw_str_begin+1955
	.data.b	54
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1972
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,49,0
	.section	.debug_info		;off: 1715
	.data.w	.Ldw_str_begin+1972
	.data.b	55
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1989
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,50,0
	.section	.debug_info		;off: 1724
	.data.w	.Ldw_str_begin+1989
	.data.b	57
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2006
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,51,0
	.section	.debug_info		;off: 1733
	.data.w	.Ldw_str_begin+2006
	.data.b	58
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2023
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,52,0
	.section	.debug_info		;off: 1742
	.data.w	.Ldw_str_begin+2023
	.data.b	60
	.data.b	5
	.data.b	38
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2040
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,53,0
	.section	.debug_info		;off: 1751
	.data.w	.Ldw_str_begin+2040
	.data.b	61
	.data.b	5
	.data.b	38
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 2057
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,54,0
	.section	.debug_info		;off: 1760
	.data.w	.Ldw_str_begin+2057
	.data.b	62
	.data.b	5
	.data.b	38
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2074
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,55,0
	.section	.debug_info		;off: 1769
	.data.w	.Ldw_str_begin+2074
	.data.b	63
	.data.b	5
	.data.b	38
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 2091
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,56,0
	.section	.debug_info		;off: 1778
	.data.w	.Ldw_str_begin+2091
	.data.b	64
	.data.b	5
	.data.b	38
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 2108
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,57,0
	.section	.debug_info		;off: 1787
	.data.w	.Ldw_str_begin+2108
	.data.b	65
	.data.b	5
	.data.b	38
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 2125
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,49,48,0
	.section	.debug_info		;off: 1796
	.data.w	.Ldw_str_begin+2125
	.data.b	66
	.data.b	5
	.data.b	38
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 2143
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,49,49,0
	.section	.debug_info		;off: 1805
	.data.w	.Ldw_str_begin+2143
	.data.b	67
	.data.b	5
	.data.b	38
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 2161
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,49,50,0
	.section	.debug_info		;off: 1814
	.data.w	.Ldw_str_begin+2161
	.data.b	68
	.data.b	5
	.data.b	38
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 2179
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,50,48,0
	.section	.debug_info		;off: 1823
	.data.w	.Ldw_str_begin+2179
	.data.b	69
	.data.b	5
	.data.b	38
	.data.b	20

	.data.b	51
	.section	.debug_str		;off: 2197
	.data.b	83,65,67,95,65,76,65,82,77,71,82,79,85,80,95,50,49,0
	.section	.debug_info		;off: 1832
	.data.w	.Ldw_str_begin+2197
	.data.b	70
	.data.b	5
	.data.b	38
	.data.b	21

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2215
	.data.b	83,97,99,95,65,108,97,114,109,71,114,111,117,112,0
	.section	.debug_info		;off: 1842
	.data.w	.Ldw_str_begin+2215
	.data.b	71
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1695

	.data.b	52
	.section	.debug_str		;off: 2230
	.data.b	0
	.section	.debug_info		;off: 1854
	.data.w	.Ldw_str_begin+2230
	.data.b	75
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2231
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,48,0
	.section	.debug_info		;off: 1864
	.data.w	.Ldw_str_begin+2231
	.data.b	76
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2248
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,0
	.section	.debug_info		;off: 1873
	.data.w	.Ldw_str_begin+2248
	.data.b	77
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2265
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,0
	.section	.debug_info		;off: 1882
	.data.w	.Ldw_str_begin+2265
	.data.b	78
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2282
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,51,0
	.section	.debug_info		;off: 1891
	.data.w	.Ldw_str_begin+2282
	.data.b	79
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2299
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,52,0
	.section	.debug_info		;off: 1900
	.data.w	.Ldw_str_begin+2299
	.data.b	80
	.data.b	5
	.data.b	38
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2316
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,53,0
	.section	.debug_info		;off: 1909
	.data.w	.Ldw_str_begin+2316
	.data.b	81
	.data.b	5
	.data.b	38
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 2333
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,54,0
	.section	.debug_info		;off: 1918
	.data.w	.Ldw_str_begin+2333
	.data.b	82
	.data.b	5
	.data.b	38
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2350
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,55,0
	.section	.debug_info		;off: 1927
	.data.w	.Ldw_str_begin+2350
	.data.b	83
	.data.b	5
	.data.b	38
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 2367
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,56,0
	.section	.debug_info		;off: 1936
	.data.w	.Ldw_str_begin+2367
	.data.b	84
	.data.b	5
	.data.b	38
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 2384
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,57,0
	.section	.debug_info		;off: 1945
	.data.w	.Ldw_str_begin+2384
	.data.b	85
	.data.b	5
	.data.b	38
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 2401
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,48,0
	.section	.debug_info		;off: 1954
	.data.w	.Ldw_str_begin+2401
	.data.b	86
	.data.b	5
	.data.b	38
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 2419
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,49,0
	.section	.debug_info		;off: 1963
	.data.w	.Ldw_str_begin+2419
	.data.b	87
	.data.b	5
	.data.b	38
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 2437
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,50,0
	.section	.debug_info		;off: 1972
	.data.w	.Ldw_str_begin+2437
	.data.b	88
	.data.b	5
	.data.b	38
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 2455
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,51,0
	.section	.debug_info		;off: 1981
	.data.w	.Ldw_str_begin+2455
	.data.b	89
	.data.b	5
	.data.b	38
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 2473
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,52,0
	.section	.debug_info		;off: 1990
	.data.w	.Ldw_str_begin+2473
	.data.b	90
	.data.b	5
	.data.b	38
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 2491
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,53,0
	.section	.debug_info		;off: 1999
	.data.w	.Ldw_str_begin+2491
	.data.b	91
	.data.b	5
	.data.b	38
	.data.b	15

	.data.b	51
	.section	.debug_str		;off: 2509
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,54,0
	.section	.debug_info		;off: 2008
	.data.w	.Ldw_str_begin+2509
	.data.b	92
	.data.b	5
	.data.b	38
	.data.b	16

	.data.b	51
	.section	.debug_str		;off: 2527
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,55,0
	.section	.debug_info		;off: 2017
	.data.w	.Ldw_str_begin+2527
	.data.b	93
	.data.b	5
	.data.b	38
	.data.b	17

	.data.b	51
	.section	.debug_str		;off: 2545
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,56,0
	.section	.debug_info		;off: 2026
	.data.w	.Ldw_str_begin+2545
	.data.b	94
	.data.b	5
	.data.b	38
	.data.b	18

	.data.b	51
	.section	.debug_str		;off: 2563
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,49,57,0
	.section	.debug_info		;off: 2035
	.data.w	.Ldw_str_begin+2563
	.data.b	95
	.data.b	5
	.data.b	38
	.data.b	19

	.data.b	51
	.section	.debug_str		;off: 2581
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,48,0
	.section	.debug_info		;off: 2044
	.data.w	.Ldw_str_begin+2581
	.data.b	96
	.data.b	5
	.data.b	38
	.data.b	20

	.data.b	51
	.section	.debug_str		;off: 2599
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,49,0
	.section	.debug_info		;off: 2053
	.data.w	.Ldw_str_begin+2599
	.data.b	97
	.data.b	5
	.data.b	38
	.data.b	21

	.data.b	51
	.section	.debug_str		;off: 2617
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,50,0
	.section	.debug_info		;off: 2062
	.data.w	.Ldw_str_begin+2617
	.data.b	98
	.data.b	5
	.data.b	38
	.data.b	22

	.data.b	51
	.section	.debug_str		;off: 2635
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,51,0
	.section	.debug_info		;off: 2071
	.data.w	.Ldw_str_begin+2635
	.data.b	99
	.data.b	5
	.data.b	38
	.data.b	23

	.data.b	51
	.section	.debug_str		;off: 2653
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,52,0
	.section	.debug_info		;off: 2080
	.data.w	.Ldw_str_begin+2653
	.data.b	100
	.data.b	5
	.data.b	38
	.data.b	24

	.data.b	51
	.section	.debug_str		;off: 2671
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,53,0
	.section	.debug_info		;off: 2089
	.data.w	.Ldw_str_begin+2671
	.data.b	101
	.data.b	5
	.data.b	38
	.data.b	25

	.data.b	51
	.section	.debug_str		;off: 2689
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,54,0
	.section	.debug_info		;off: 2098
	.data.w	.Ldw_str_begin+2689
	.data.b	102
	.data.b	5
	.data.b	38
	.data.b	26

	.data.b	51
	.section	.debug_str		;off: 2707
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,55,0
	.section	.debug_info		;off: 2107
	.data.w	.Ldw_str_begin+2707
	.data.b	103
	.data.b	5
	.data.b	38
	.data.b	27

	.data.b	51
	.section	.debug_str		;off: 2725
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,56,0
	.section	.debug_info		;off: 2116
	.data.w	.Ldw_str_begin+2725
	.data.b	104
	.data.b	5
	.data.b	38
	.data.b	28

	.data.b	51
	.section	.debug_str		;off: 2743
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,50,57,0
	.section	.debug_info		;off: 2125
	.data.w	.Ldw_str_begin+2743
	.data.b	105
	.data.b	5
	.data.b	38
	.data.b	29

	.data.b	51
	.section	.debug_str		;off: 2761
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,51,48,0
	.section	.debug_info		;off: 2134
	.data.w	.Ldw_str_begin+2761
	.data.b	106
	.data.b	5
	.data.b	38
	.data.b	30

	.data.b	51
	.section	.debug_str		;off: 2779
	.data.b	83,65,67,95,65,76,65,82,77,73,78,68,69,88,95,51,49,0
	.section	.debug_info		;off: 2143
	.data.w	.Ldw_str_begin+2779
	.data.b	107
	.data.b	5
	.data.b	38
	.data.b	31

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2797
	.data.b	83,97,99,95,65,108,97,114,109,73,110,100,101,120,0
	.section	.debug_info		;off: 2153
	.data.w	.Ldw_str_begin+2797
	.data.b	108
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1853

	.data.b	52
	.section	.debug_str		;off: 2812
	.data.b	0
	.section	.debug_info		;off: 2165
	.data.w	.Ldw_str_begin+2812
	.data.b	112
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2813
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,78,79,78,69,0
	.section	.debug_info		;off: 2175
	.data.w	.Ldw_str_begin+2813
	.data.b	113
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2842
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,73,71,67,83,48,0
	.section	.debug_info		;off: 2184
	.data.w	.Ldw_str_begin+2842
	.data.b	114
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2872
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,73,71,67,83,49,0
	.section	.debug_info		;off: 2193
	.data.w	.Ldw_str_begin+2872
	.data.b	115
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2902
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,73,71,67,83,50,0
	.section	.debug_info		;off: 2202
	.data.w	.Ldw_str_begin+2902
	.data.b	116
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2932
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,73,71,67,83,51,0
	.section	.debug_info		;off: 2211
	.data.w	.Ldw_str_begin+2932
	.data.b	117
	.data.b	5
	.data.b	38
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2962
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,78,77,73,0
	.section	.debug_info		;off: 2220
	.data.w	.Ldw_str_begin+2962
	.data.b	118
	.data.b	5
	.data.b	38
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 2990
	.data.b	83,65,67,95,65,76,65,82,77,73,78,84,69,82,78,65,76,65,67,84,73,79,78,95,82,83,84,0
	.section	.debug_info		;off: 2229
	.data.w	.Ldw_str_begin+2990
	.data.b	119
	.data.b	5
	.data.b	38
	.data.b	6

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3018
	.data.b	83,97,99,95,65,108,97,114,109,73,110,116,101,114,110,97,108,65,99,116,105,111,110,0
	.section	.debug_info		;off: 2239
	.data.w	.Ldw_str_begin+3018
	.data.b	120
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+2164

	.data.b	52
	.section	.debug_str		;off: 3042
	.data.b	0
	.section	.debug_info		;off: 2251
	.data.w	.Ldw_str_begin+3042
	.data.b	124
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3043
	.data.b	83,65,67,95,70,73,80,65,67,84,73,79,78,95,78,79,78,69,0
	.section	.debug_info		;off: 2261
	.data.w	.Ldw_str_begin+3043
	.data.b	125
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3062
	.data.b	83,65,67,95,70,73,80,65,67,84,73,79,78,95,65,67,84,73,86,65,84,69,0
	.section	.debug_info		;off: 2270
	.data.w	.Ldw_str_begin+3062
	.data.b	126
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3085
	.data.b	83,97,99,95,70,105,112,65,99,116,105,111,110,0
	.section	.debug_info		;off: 2280
	.data.w	.Ldw_str_begin+3085
	.data.b	127
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+2250

	.data.b	52
	.section	.debug_str		;off: 3099
	.data.b	0
	.section	.debug_info		;off: 2292
	.data.w	.Ldw_str_begin+3099
	.data.b	211,1
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3100
	.data.b	83,65,67,95,67,77,68,69,88,82,69,83,85,76,84,95,83,85,67,67,69,83,83,70,85,76,0
	.section	.debug_info		;off: 2303
	.data.w	.Ldw_str_begin+3100
	.data.b	212,1
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3127
	.data.b	83,65,67,95,67,77,68,69,88,82,69,83,85,76,84,95,70,65,73,76,69,68,0
	.section	.debug_info		;off: 2313
	.data.w	.Ldw_str_begin+3127
	.data.b	213,1
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3150
	.data.b	83,97,99,95,67,109,100,69,120,82,101,115,117,108,116,0
	.section	.debug_info		;off: 2324
	.data.w	.Ldw_str_begin+3150
	.data.b	214,1
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+2291

	.data.b	6
	.section	.debug_str		;off: 3166
	.data.b	87,100,103,95,73,110,102,111,114,109,97,116,105,111,110,67,111,114,101,48,0
	.section	.debug_info		;off: 2337
	.data.w	.Ldw_str_begin+3166
	.data.b	131,1
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1469
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_InformationCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

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

	.section	.debug_info		;off: 2357
	.data.b	6
	.section	.debug_str		;off: 3187
	.data.b	87,100,103,95,73,110,102,111,114,109,97,116,105,111,110,67,111,114,101,49,0
	.section	.debug_info		;off: 2358
	.data.w	.Ldw_str_begin+3187
	.data.b	146,1
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1469
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_InformationCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

	.data.b	6
	.section	.debug_str		;off: 3208
	.data.b	87,100,103,95,73,110,102,111,114,109,97,116,105,111,110,67,111,114,101,50,0
	.section	.debug_info		;off: 2379
	.data.w	.Ldw_str_begin+3208
	.data.b	161,1
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1469
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_InformationCore2..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

	.data.b	6
	.section	.debug_str		;off: 3229
	.data.b	87,100,103,95,73,110,102,111,114,109,97,116,105,111,110,67,111,114,101,51,0
	.section	.debug_info		;off: 2400
	.data.w	.Ldw_str_begin+3229
	.data.b	176,1
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+1469
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_InformationCore3..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

	.data.b	6
	.section	.debug_str		;off: 3250
	.data.b	87,100,103,95,67,111,114,101,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 2421
	.data.w	.Ldw_str_begin+3250
	.data.b	189,1
	.data.b	5
	.data.b	1
	.data.w	.Ldw_begin+253
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_CoreStatePtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

	.data.b	6
	.section	.debug_str		;off: 3267
	.data.b	87,100,103,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 2442
	.data.w	.Ldw_str_begin+3267
	.data.b	230,1
	.data.b	59
	.data.b	1
	.data.w	.Ldw_begin+75
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Wdg_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CWdg.

	.data.b	27
	.section	.debug_str		;off: 3281
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 2463
	.data.w	.Ldw_str_begin+3281
	.data.b	63
	.data.b	31
	.data.b	13
	.data.w	.Ldw_begin+721
	.data.b	0
	.data.b	3
	.data.b	0
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

	.section	.debug_info		;off: 2480
	.data.b	37

	.section	.debug_abbrev		;off: 222
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 2481
	.data.b	8
	.section	.debug_str		;off: 3301
	.data.b	105,100,0
	.section	.debug_info		;off: 2482
	.data.w	.Ldw_str_begin+3301
	.data.b	65
	.data.b	17
	.data.b	13
	.data.w	.Ldw_begin+721
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 227
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

	.section	.debug_info		;off: 2495
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3304
	.data.b	67,112,117,119,100,116,95,72,97,108,95,73,110,105,116,87,100,116,0
	.section	.debug_info		;off: 2498
	.data.w	.Ldw_str_begin+3304
	.data.b	173,1
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3323
	.data.b	67,112,117,119,100,116,95,72,97,108,95,69,110,97,98,108,101,87,100,116,0
	.section	.debug_info		;off: 2518
	.data.w	.Ldw_str_begin+3323
	.data.b	226,1
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3344
	.data.b	67,112,117,119,100,116,95,72,97,108,95,83,101,114,118,105,99,101,87,100,116,0
	.section	.debug_info		;off: 2538
	.data.w	.Ldw_str_begin+3344
	.data.b	243,1
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3366
	.data.b	67,112,117,119,100,116,95,72,97,108,95,71,101,116,87,100,103,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 2558
	.data.w	.Ldw_str_begin+3366
	.data.b	132,2
	.data.b	15
	.data.b	15
	.data.w	.Ldw_begin+530
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3391
	.data.b	67,112,117,119,100,116,95,72,97,108,95,68,105,115,97,98,108,101,87,100,116,0
	.section	.debug_info		;off: 2578
	.data.w	.Ldw_str_begin+3391
	.data.b	149,2
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3413
	.data.b	67,112,117,119,100,116,95,72,97,108,95,67,104,97,110,103,101,72,105,103,104,84,104,118,0
	.section	.debug_info		;off: 2598
	.data.w	.Ldw_str_begin+3413
	.data.b	168,2
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3438
	.data.b	67,112,117,119,100,116,95,72,97,108,95,71,101,116,65,108,97,114,109,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+3438
	.data.b	186,2
	.data.b	22
	.data.b	15
	.data.w	.Ldw_begin+924
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3468
	.data.b	67,112,117,119,100,116,95,72,97,108,95,67,108,101,97,114,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2638
	.data.w	.Ldw_str_begin+3468
	.data.b	239,2
	.data.b	16
	.data.b	15
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3495
	.data.b	83,99,104,77,95,69,110,116,101,114,95,87,100,103,95,73,110,105,116,0
	.section	.debug_info		;off: 2658
	.data.w	.Ldw_str_begin+3495
	.data.b	42
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 246
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

	.section	.debug_info		;off: 2671
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3515
	.data.b	83,99,104,77,95,69,120,105,116,95,87,100,103,95,73,110,105,116,0
	.section	.debug_info		;off: 2673
	.data.w	.Ldw_str_begin+3515
	.data.b	43
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3534
	.data.b	83,99,104,77,95,69,110,116,101,114,95,87,100,103,95,83,101,116,77,111,100,101,0
	.section	.debug_info		;off: 2688
	.data.w	.Ldw_str_begin+3534
	.data.b	44
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3557
	.data.b	83,99,104,77,95,69,120,105,116,95,87,100,103,95,83,101,116,77,111,100,101,0
	.section	.debug_info		;off: 2703
	.data.w	.Ldw_str_begin+3557
	.data.b	45
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3579
	.data.b	83,99,104,77,95,69,110,116,101,114,95,87,100,103,95,83,101,116,84,114,105,103,103,101,114,67,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 2718
	.data.w	.Ldw_str_begin+3579
	.data.b	46
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3614
	.data.b	83,99,104,77,95,69,120,105,116,95,87,100,103,95,83,101,116,84,114,105,103,103,101,114,67,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 2733
	.data.w	.Ldw_str_begin+3614
	.data.b	47
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3648
	.data.b	83,99,104,77,95,69,110,116,101,114,95,87,100,103,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 2748
	.data.w	.Ldw_str_begin+3648
	.data.b	48
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3674
	.data.b	83,99,104,77,95,69,120,105,116,95,87,100,103,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 2763
	.data.w	.Ldw_str_begin+3674
	.data.b	49
	.data.b	13
	.data.b	37
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3699
	.data.b	83,97,99,95,72,97,108,95,83,101,116,65,108,97,114,109,65,99,116,105,111,110,0
	.section	.debug_info		;off: 2778
	.data.w	.Ldw_str_begin+3699
	.data.b	162,3
	.data.b	16
	.data.b	38
	.data.w	.Ldw_begin+494
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3722
	.data.b	83,97,99,95,72,97,108,95,65,99,116,105,118,97,116,101,82,117,110,83,116,97,116,101,0
	.section	.debug_info		;off: 2798
	.data.w	.Ldw_str_begin+3722
	.data.b	213,3
	.data.b	24
	.data.b	38
	.data.w	.Ldw_begin+2323
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3747
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 2818
	.data.w	.Ldw_str_begin+3747
	.data.b	105
	.data.b	39
	.data.b	41
	.data.w	.Ldw_begin+554
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3763
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 2837
	.data.w	.Ldw_str_begin+3763
	.data.b	113
	.data.b	39
	.data.b	41
	.data.w	.Ldw_begin+554
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3786
	.data.b	87,100,103,95,67,104,101,99,107,65,110,100,67,108,114,69,114,114,111,114,0
	.section	.debug_info		;off: 2856
	.data.w	.Ldw_str_begin+3786
	.data.b	159,2
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+506
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 3807
	.data.b	87,100,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2876
	.data.w	.Ldw_str_begin+3807
	.data.b	164,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1352
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3817
	.data.b	87,100,103,69,114,114,111,114,0
	.section	.debug_info		;off: 2891
	.data.w	.Ldw_str_begin+3817
	.data.b	165,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+506
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3826
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 2906
	.data.w	.Ldw_str_begin+3826
	.data.b	166,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+494
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3835
	.data.b	87,100,103,95,73,110,105,116,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 2923
	.data.w	.Ldw_str_begin+3835
	.data.b	219,2
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 3852
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 2942
	.data.w	.Ldw_str_begin+3852
	.data.b	221,2
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+80
	.data.b	0

	.section	.debug_abbrev		;off: 271
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

	.section	.debug_info		;off: 2955
	.data.b	20
	.section	.debug_str		;off: 3862
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 2956
	.data.w	.Ldw_str_begin+3862
	.data.b	222,2
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 3869
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 2971
	.data.w	.Ldw_str_begin+3869
	.data.b	225,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3878
	.data.b	87,100,103,95,83,101,116,77,111,100,101,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 2988
	.data.w	.Ldw_str_begin+3878
	.data.b	140,3
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 3898
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3007
	.data.w	.Ldw_str_begin+3898
	.data.b	142,3
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 3905
	.data.b	77,111,100,101,0
	.section	.debug_info		;off: 3021
	.data.w	.Ldw_str_begin+3905
	.data.b	143,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1316
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 3910
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 3036
	.data.w	.Ldw_str_begin+3910
	.data.b	146,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 3919
	.data.b	87,100,103,95,73,110,105,116,0
	.section	.debug_info		;off: 3053
	.data.w	.Ldw_str_begin+3919
	.data.b	206,3
	.data.b	29
	.data.b	1
	.data.w	Wdg_Init
	.data.w	__ghs_eofn_Wdg_Init
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

	.section	.debug_abbrev		;off: 288
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
	.data.w	Wdg_Init
	.data.w	__ghs_eofn_Wdg_Init-Wdg_Init
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1678
	.data.b	0,5,2
	.data.w	Wdg_Init
	.data.b	6
	.data.b	3
	.data.b	209,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	13
	.data.b	203
	.data.b	12
	.data.b	12
	.data.b	43
	.data.b	60
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	44
	.data.b	28
	.data.b	27
	.data.b	11
	.data.b	92
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
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	107
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	3
	.data.b	1
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	92
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	108
	.data.b	13
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
	.section	.debug_info		;off: 3084
	.data.b	22
	.section	.debug_str		;off: 3928
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3085
	.data.w	.Ldw_str_begin+3928
	.data.b	208,3
	.data.b	56
	.data.b	1
	.data.w	.Ldw_begin+75
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
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 334
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

	.section	.debug_info		;off: 3102
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 353
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 3111
	.data.b	7
	.section	.debug_str		;off: 3938
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3112
	.data.w	.Ldw_str_begin+3938
	.data.b	211,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+30
	.section	.debug_loc		;off: 30
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 362
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

	.section	.debug_info		;off: 3130
	.data.b	8
	.section	.debug_str		;off: 3945
	.data.b	87,100,103,69,114,114,111,114,0
	.section	.debug_info		;off: 3131
	.data.w	.Ldw_str_begin+3945
	.data.b	212,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+506
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3954
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 3146
	.data.w	.Ldw_str_begin+3954
	.data.b	213,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+494
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+49
	.section	.debug_loc		;off: 49
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3164
	.data.b	7
	.section	.debug_str		;off: 3963
	.data.b	82,101,103,82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 3165
	.data.w	.Ldw_str_begin+3963
	.data.b	214,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2323
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3183
	.data.b	8
	.section	.debug_str		;off: 3975
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 3184
	.data.w	.Ldw_str_begin+3975
	.data.b	216,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3984
	.data.b	87,100,103,95,83,101,116,77,111,100,101,0
	.section	.debug_info		;off: 3201
	.data.w	.Ldw_str_begin+3984
	.data.b	237,4
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.w	Wdg_SetMode
	.data.w	__ghs_eofn_Wdg_SetMode
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

	.section	.debug_abbrev		;off: 383
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
	.data.w	Wdg_SetMode
	.data.w	__ghs_eofn_Wdg_SetMode-Wdg_SetMode
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1816
	.data.b	0,5,2
	.data.w	Wdg_SetMode
	.data.b	6
	.data.b	3
	.data.b	240,4
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
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	1
	.data.b	2
	.data.b	76
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	92
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	119
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
	.data.b	17
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	45
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	119
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
	.data.b	17
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	125
	.data.b	13
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	3
	.data.b	1
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	27
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	45
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
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3236
	.data.b	22
	.section	.debug_str		;off: 3996
	.data.b	77,111,100,101,0
	.section	.debug_info		;off: 3237
	.data.w	.Ldw_str_begin+3996
	.data.b	239,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1316
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
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3254
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 4001
	.data.b	82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 3264
	.data.w	.Ldw_str_begin+4001
	.data.b	242,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3282
	.data.b	7
	.section	.debug_str		;off: 4013
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3283
	.data.w	.Ldw_str_begin+4013
	.data.b	243,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+136
	.section	.debug_loc		;off: 136
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3301
	.data.b	8
	.section	.debug_str		;off: 4020
	.data.b	87,100,103,69,114,114,111,114,0
	.section	.debug_info		;off: 3302
	.data.w	.Ldw_str_begin+4020
	.data.b	244,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4029
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 3317
	.data.w	.Ldw_str_begin+4029
	.data.b	245,4
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+494
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+155
	.section	.debug_loc		;off: 155
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3335
	.data.b	8
	.section	.debug_str		;off: 4038
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 3336
	.data.w	.Ldw_str_begin+4038
	.data.b	247,4
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+554
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4047
	.data.b	87,100,103,95,83,101,116,84,114,105,103,103,101,114,67,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 3353
	.data.w	.Ldw_str_begin+4047
	.data.b	153,6
	.data.b	29
	.data.b	1
	.data.w	Wdg_SetTriggerCondition
	.data.w	__ghs_eofn_Wdg_SetTriggerCondition
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Wdg_SetTriggerCondition
	.data.w	__ghs_eofn_Wdg_SetTriggerCondition-Wdg_SetTriggerCondition
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1998
	.data.b	0,5,2
	.data.w	Wdg_SetTriggerCondition
	.data.b	6
	.data.b	3
	.data.b	156,6
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
	.data.w	.LDWlin4
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	13
	.data.b	155
	.data.b	12
	.data.b	44
	.data.b	11
	.data.b	75
	.data.b	12
	.data.b	108
	.data.b	13
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	29
	.data.b	61
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	28
	.data.b	12
	.data.b	12
	.data.b	28
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	91
	.data.b	12
	.data.b	11
	.data.b	29
	.data.b	75
	.data.b	203
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	45
	.data.b	28
	.data.b	27
	.data.b	11
	.data.b	76
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
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3384
	.data.b	22
	.section	.debug_str		;off: 4071
	.data.b	84,105,109,101,111,117,116,0
	.section	.debug_info		;off: 3385
	.data.w	.Ldw_str_begin+4071
	.data.b	155,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+518
	.data.b	0
	.data.w	.Ldw_loc_begin+174
	.section	.debug_loc		;off: 174
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	80
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3402
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 4079
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3412
	.data.w	.Ldw_str_begin+4079
	.data.b	158,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+733
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

	.section	.debug_info		;off: 3430
	.data.b	7
	.section	.debug_str		;off: 4086
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 3431
	.data.w	.Ldw_str_begin+4086
	.data.b	159,6
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+494
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+223
	.section	.debug_loc		;off: 223
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3449
	.data.b	7
	.section	.debug_str		;off: 4095
	.data.b	70,105,114,115,116,76,101,118,101,108,84,105,99,107,0
	.section	.debug_info		;off: 3450
	.data.w	.Ldw_str_begin+4095
	.data.b	160,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+530
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+242
	.section	.debug_loc		;off: 242
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3468
	.data.b	7
	.section	.debug_str		;off: 4110
	.data.b	84,105,109,101,111,117,116,84,105,99,107,0
	.section	.debug_info		;off: 3469
	.data.w	.Ldw_str_begin+4110
	.data.b	161,6
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+530
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+261
	.section	.debug_loc		;off: 261
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3487
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4122
	.data.b	87,100,103,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 3490
	.data.w	.Ldw_str_begin+4122
	.data.b	145,7
	.data.b	29
	.data.b	1
	.data.w	Wdg_GetVersionInfo
	.data.w	__ghs_eofn_Wdg_GetVersionInfo
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
	.data.w	Wdg_GetVersionInfo
	.data.w	__ghs_eofn_Wdg_GetVersionInfo-Wdg_GetVersionInfo
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2102
	.data.b	0,5,2
	.data.w	Wdg_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	150,7
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
	.section	.debug_info		;off: 3519
	.data.b	22
	.section	.debug_str		;off: 4141
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 3520
	.data.w	.Ldw_str_begin+4141
	.data.b	147,7
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+161
	.data.b	0
	.data.w	.Ldw_loc_begin+280
	.section	.debug_loc		;off: 280
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3537
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4156
	.data.b	87,100,103,95,82,101,102,114,101,115,104,84,105,109,101,114,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 3549
	.data.w	.Ldw_str_begin+4156
	.data.b	193,7
	.data.b	29
	.data.b	1
	.data.w	Wdg_RefreshTimer_ISRHandler
	.data.w	__ghs_eofn_Wdg_RefreshTimer_ISRHandler
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Wdg_RefreshTimer_ISRHandler
	.data.w	__ghs_eofn_Wdg_RefreshTimer_ISRHandler-Wdg_RefreshTimer_ISRHandler
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2134
	.data.b	0,5,2
	.data.w	Wdg_RefreshTimer_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	196,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	12
	.data.b	60
	.data.b	107
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	59
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	189
	.data.b	6
	.data.b	3
	.data.b	26
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	104
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
	.data.b	27
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
	.data.b	27
	.data.b	11
	.data.b	3
	.data.b	98
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	91
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	11
	.data.b	28
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 3580
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 4184
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3590
	.data.w	.Ldw_str_begin+4184
	.data.b	198,7
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+299
	.section	.debug_loc		;off: 299
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3608
	.data.b	7
	.section	.debug_str		;off: 4191
	.data.b	82,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 3609
	.data.w	.Ldw_str_begin+4191
	.data.b	199,7
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+494
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+318
	.section	.debug_loc		;off: 318
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3627
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4200
	.data.b	87,100,103,95,71,101,116,67,117,114,114,101,110,116,84,105,109,101,111,117,116,0
	.section	.debug_info		;off: 3630
	.data.w	.Ldw_str_begin+4200
	.data.b	163,8
	.data.b	31
	.data.b	1
	.data.w	.Ldw_begin+518
	.data.w	Wdg_GetCurrentTimeout
	.data.w	__ghs_eofn_Wdg_GetCurrentTimeout
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Wdg_GetCurrentTimeout
	.data.w	__ghs_eofn_Wdg_GetCurrentTimeout-Wdg_GetCurrentTimeout
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2253
	.data.b	0,5,2
	.data.w	Wdg_GetCurrentTimeout
	.data.b	6
	.data.b	3
	.data.b	166,8
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
	.data.w	.LDWlin8
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	11
	.data.b	28
	.data.b	27
	.data.b	107
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	93
	.data.b	75
	.data.b	11
	.data.b	77
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
	.section	.debug_info		;off: 3665
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 4222
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3675
	.data.w	.Ldw_str_begin+4222
	.data.b	168,8
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+733
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+337
	.section	.debug_loc		;off: 337
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3693
	.data.b	7
	.section	.debug_str		;off: 4229
	.data.b	84,105,109,101,111,117,116,0
	.section	.debug_info		;off: 3694
	.data.w	.Ldw_str_begin+4229
	.data.b	169,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+518
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+356
	.section	.debug_loc		;off: 356
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3712
	.data.b	7
	.section	.debug_str		;off: 4237
	.data.b	87,100,116,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 3713
	.data.w	.Ldw_str_begin+4237
	.data.b	170,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+530
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+375
	.section	.debug_loc		;off: 375
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3731
	.data.b	7
	.section	.debug_str		;off: 4248
	.data.b	82,101,102,114,101,115,104,84,105,109,101,0
	.section	.debug_info		;off: 3732
	.data.w	.Ldw_str_begin+4248
	.data.b	171,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+530
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+394
	.section	.debug_loc		;off: 394
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 3750
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
	.data.b	47
	.data.b	2
	.data.b	3
	.data.b	35
	.data.b	3
	.data.b	3
	.data.b	38
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	5
	.data.b	1
	.data.b	78
	.data.b	77,67,65,76,95,77,65,83,84,69,82,95,67,79,82,69,32,40,77,67,65,76,95,67,79,82,69,48,41,0
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	6
	.data.b	3
	.data.b	25
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
	.data.b	3
	.data.b	26
	.data.b	13
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	14
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
	.data.b	14
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	15
	.data.b	3
	.data.b	28
	.data.b	16
	.data.b	3
	.data.b	22
	.data.b	17
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	29
	.data.b	18
	.data.b	3
	.data.b	56
	.data.b	19
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
	.data.b	20
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
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	21
	.data.b	1
	.data.b	175,1
	.data.b	83,65,70,69,87,68,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,1
	.data.b	22
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
	.data.b	22
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	23
	.data.b	3
	.data.b	34
	.data.b	24
	.data.b	3
	.data.b	31
	.data.b	25
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
	.data.b	26
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
	.data.b	26
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	27
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	26
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
	.data.b	26
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	28
	.data.b	3
	.data.b	38
	.data.b	29
	.data.b	4
	.data.b	1
	.data.b	231,5
	.data.b	82,67,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,5
	.data.b	30
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
	.data.b	30
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
	.data.b	252,1
	.data.b	77,67,65,76,76,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	253,1
	.data.b	31
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
	.data.b	31
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	32
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	33
	.data.b	1
	.data.b	38
	.data.b	87,68,71,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	39
	.data.b	87,68,71,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	41
	.data.b	87,68,71,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	43
	.data.b	87,68,71,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	44
	.data.b	87,68,71,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	45
	.data.b	87,68,71,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	47
	.data.b	87,68,71,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	48
	.data.b	87,68,71,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,49,48,50,85,41,0
	.data.b	1
	.data.b	55
	.data.b	87,68,71,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	68
	.data.b	87,68,71,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	75
	.data.b	87,68,71,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	81
	.data.b	87,68,71,95,68,69,86,73,67,69,48,95,67,79,78,70,73,71,85,82,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	82
	.data.b	87,68,71,95,68,69,86,73,67,69,49,95,67,79,78,70,73,71,85,82,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	83
	.data.b	87,68,71,95,68,69,86,73,67,69,50,95,67,79,78,70,73,71,85,82,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	84
	.data.b	87,68,71,95,68,69,86,73,67,69,51,95,67,79,78,70,73,71,85,82,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	87
	.data.b	87,68,71,95,73,78,83,84,65,78,67,69,95,73,68,32,40,48,85,41,0
	.data.b	1
	.data.b	90
	.data.b	87,68,71,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	93
	.data.b	87,68,71,95,79,86,69,82,70,76,79,87,95,65,67,84,73,79,78,95,82,69,83,69,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	97
	.data.b	87,68,71,95,69,78,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,32,40,49,85,41,0
	.data.b	1
	.data.b	98
	.data.b	87,68,71,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,32,40,48,85,41,0
	.data.b	1
	.data.b	100
	.data.b	87,68,71,95,68,73,83,65,66,76,69,95,82,69,74,69,67,84,95,68,69,77,95,82,69,80,79,82,84,32,40,87,68,71,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	1
	.data.b	101
	.data.b	87,68,71,95,77,79,68,69,95,70,65,73,76,95,68,69,77,95,82,69,80,79,82,84,32,40,87,68,71,95,68,73,83,65,66,76,69,95,68,69,77,95,82,69,80,79,82,84,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	34
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	35
	.data.b	1
	.data.b	29
	.data.b	87,68,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	31
	.data.b	87,68,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	33
	.data.b	87,68,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	37
	.data.b	87,68,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	39
	.data.b	87,68,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	41
	.data.b	87,68,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	44
	.data.b	87,68,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	46
	.data.b	87,68,71,95,77,79,68,85,76,69,95,73,68,32,40,49,48,50,85,41,0
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	87,68,71,95,69,95,68,82,73,86,69,82,95,83,84,65,84,69,32,40,48,120,49,48,85,41,0
	.data.b	1
	.data.b	49
	.data.b	87,68,71,95,69,95,80,65,82,65,77,95,77,79,68,69,32,40,48,120,49,49,85,41,0
	.data.b	1
	.data.b	54
	.data.b	87,68,71,95,69,95,80,65,82,65,77,95,84,73,77,69,79,85,84,32,40,48,120,49,51,85,41,0
	.data.b	1
	.data.b	56
	.data.b	87,68,71,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,48,120,49,52,85,41,0
	.data.b	1
	.data.b	62
	.data.b	87,68,71,95,69,95,73,78,84,95,79,70,70,95,77,79,68,69,32,40,48,120,50,53,85,41,0
	.data.b	1
	.data.b	64
	.data.b	87,68,71,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,48,120,69,48,85,41,0
	.data.b	1
	.data.b	68
	.data.b	87,68,71,95,69,95,82,69,71,95,67,72,69,67,75,95,70,65,73,76,69,68,32,40,48,120,69,49,85,41,0
	.data.b	1
	.data.b	72
	.data.b	87,68,71,95,83,73,68,95,73,78,73,84,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	74
	.data.b	87,68,71,95,83,73,68,95,83,69,84,77,79,68,69,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	76
	.data.b	87,68,71,95,83,73,68,95,83,69,84,84,82,73,71,71,69,82,67,79,78,68,73,84,73,79,78,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	78
	.data.b	87,68,71,95,83,73,68,95,71,69,84,86,69,82,83,73,79,78,73,78,70,79,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	80
	.data.b	87,68,71,95,83,73,68,95,82,69,70,82,69,83,72,84,73,77,69,82,95,73,83,82,72,65,78,68,76,69,82,32,40,48,120,49,48,85,41,0
	.data.b	1
	.data.b	98
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	99
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	131,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	132,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	51
	.data.b	37
	.data.b	4
	.data.b	3
	.data.b	54
	.data.b	38
	.data.b	3
	.data.b	17
	.data.b	39
	.data.b	1
	.data.b	26
	.data.b	83,65,67,95,65,76,65,77,95,71,85,80,77,85,77,32,40,49,51,85,41,0
	.data.b	1
	.data.b	28
	.data.b	83,65,67,95,83,84,68,66,95,65,76,65,77,95,71,85,80,77,85,77,32,40,50,85,41,0
	.data.b	4
	.data.b	1
	.data.b	201,2
	.data.b	83,65,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	202,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,65,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	226,2
	.data.b	83,65,67,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	241,4
	.data.b	83,65,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	242,4
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	66
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
	.data.b	106
	.data.b	87,68,71,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,87,100,103,95,32,35
	.data.b	35,32,69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	108
	.data.b	87,68,71,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,87,100,103,95,32,35,35,32
	.data.b	69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	111
	.data.b	87,68,71,95,77,73,78,73,77,85,77,95,67,79,85,78,84,95,84,72,82,69,83,72,79,76,68,32,40,49,85,41,0
	.data.b	1
	.data.b	114
	.data.b	87,68,71,95,72,65,82,68,87,65,82,69,95,69,82,82,79,82,32,40,48,120,50,48,85,41,0
	.data.b	1
	.data.b	116
	.data.b	87,68,71,95,82,69,68,85,78,68,65,78,67,89,95,69,82,82,79,82,32,40,48,120,50,54,85,41,0
	.data.b	1
	.data.b	118
	.data.b	87,68,71,95,67,76,69,65,82,95,70,65,73,76,68,69,68,32,40,48,120,51,54,85,41,0
	.data.b	1
	.data.b	128,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	129,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	133,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	135,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	142,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	144,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	148,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	150,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	157,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	159,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	160,49
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	163,49
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	163,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	165,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	172,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	174,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	211,57
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	214,57
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	178,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	180,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	185,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	187,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	221,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	223,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	226,1
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	228,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	233,1
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	235,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	129,2
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	131,2
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	170,3
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	172,3
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	178,3
	.data.b	87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	180,3
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,87,68,71,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	194,8
	.data.b	87,68,71,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	196,8
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 431
	.data.b	0
