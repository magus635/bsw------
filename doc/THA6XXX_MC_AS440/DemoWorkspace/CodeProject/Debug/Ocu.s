	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682574..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_CheckDetErrors:
.LDW01:
	push	{r2,r4-r5,lr}
.LDW11:
	mov	r4,1
	cmp	r0,4
	blo	.L42
.L43:
	mov	r2,r1
	mov	r3,3
.L234:

.L235:

	mov	r1,0
	mov	r0,125
.L247:

	bl	Det_ReportError
	b	.L44
.L42:
	ldr	r12,.L245
	ldr	r3,[r12,r2 lsl 2]
	ldr	r3,[r3]
	cmp	r3,1
	movne	r2,r1
	movne	r3,2
	bne	.L235
.L45:
	ldr	r3,.L246
	ldr	r5,[r3]
	ldr	r12,[r5,16]
	rsb	r3,r0,r0 lsl 2
	ldr	r2,[r5,r2 lsl 2]
	add	r12,r12,r3 lsl 2
	ldrb	r3,[r12,4]
	ldr	r2,[r2,4]
	rsb	r3,r3,r3 lsl 2
	ldrb	r2,[r2,r3 lsl 3]
	cmp	r2,r0
	movne	r2,r1
	movne	r3,225
	bne	.L234
.L48:
	mov	r4,0
.L44:
	mov	r0,r4
.LDW21:
.L249:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Ocu_CheckDetErrors:
	.endf	Ocu_CheckDetErrors
	.endf	Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;ErrValue	r4	local

;Channel	r0	param
;ApiSid	r1	param
;CoreId	r2	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Ocu_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_ConfigPtr:	.space	4
	.endo	Ocu_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Ocu_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_CoreDriverStatusPtr:
	.data.w	Ocu_DriverStatusCore0
	.data.w	Ocu_DriverStatusCore1
	.space	8
	.endo	Ocu_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_CoreDriverStatusPtr
	.section ".ghcalltbl",""
	.align	4
.L248:	.data.w	.L247
	.endo	.L248
	.section ".ghrettbl",""
	.align	4
.L250:	.data.w	.L249
	.endo	.L250
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Ocu_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_DriverStatusCore0:	.space	4
	.endo	Ocu_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_DriverStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Ocu_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_DriverStatusCore1:	.space	4
	.endo	Ocu_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_DriverStatusCore1
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_InitDetCheck:
.LDW31:
	push	{r4,lr}
.LDW41:
	mov	r4,1
	movs	r2,r0
	moveq	r3,11
	beq	.L742
.L253:
	ldr	r0,[r0,r1 lsl 2]
	movs	r2,r0
	bne	.L256
.L257:
	mov	r3,224
.L742:

	mov	r1,r0
	b	.L743
.L256:
	ldr	r0,.L245
	ldr	r0,[r0,r1 lsl 2]
	ldr	r0,[r0]
	cmp	r0,0
	beq	.L259
.L260:
	mov	r2,0
	mov	r3,7
	mov	r1,r2
.L743:

	mov	r0,125
.L753:

	bl	Det_ReportError
	b	.L255
.L259:
	mov	r4,r0
.L255:
	mov	r0,r4
.LDW51:
.L755:

	pop	{r4,pc}
__ghs_eofn_Ocu_InitDetCheck:
	.endf	Ocu_InitDetCheck
	.endf	Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;ErrValue	r4	local

;ConfigPtr	r0	param
;CoreId	r1	param

	.section ".bss","awb"
.L664:
	.endo	.L664
	.section ".ghcalltbl",""
.L754:	.data.w	.L753
	.endo	.L754
	.section ".ghrettbl",""
.L756:	.data.w	.L755
	.endo	.L756
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_SetAbsoluteThresholdDetCheck:
.LDW61:
	push	{r2,r4-r7,lr}
	mov	r6,r1
	mov	r7,r2
.LDW71:
	b	.L925

.L245:	.data.w	Ocu_CoreDriverStatusPtr
	.endo	.L245

.L246:	.data.w	Ocu_ConfigPtr
	.endo	.L246

.L925:

;line623
..lin.3629a0af..8f4ab29e.0_1::
.LDWlin1:
..gh.beginasm.3:
	.endo	..gh.beginasm.3
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.4:
	.endo	..gh.endasm.4

	mov	r4,r3
;line625
..lin.3629a0af..8f4ab29e.0_2::
.LDWlin2:
	mov	r2,r3
	mov	r5,r0
	mov	r1,7
.L927:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L929:

	popne	{r2,r4-r7,pc}
	ldr	r1,.L926
	ldr	r12,[r1]
	mov	r3,226
	rsb	r1,r5,r5 lsl 2
	ldr	r2,[r12,16]
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	rsb	r2,r1,r1 lsl 2
	ldr	r1,[r12,r4 lsl 2]
	ldr	r1,[r1,4]
	add	r1,r1,r2 lsl 3
	ldr	r1,[r1,4]
	cmp	r6,r1
	movls	r3,227
	cmpls	r7,r1
.L931:

	popls	{r2,r4-r7,pc}
	mov	r2,7
	mov	r1,r0
	mov	r0,125
.L933:

	bl	Det_ReportError
	mov	r0,1
.LDW81:
.L935:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Ocu_SetAbsoluteThresholdDetCheck:
	.endf	Ocu_SetAbsoluteThresholdDetCheck
	.endf	Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;CoreId	r4	local
;ErrValue	r0	local

;ChannelNumber	r5	param
;ReferenceValue	r6	param
;AbsoluteValue	r7	param

	.section ".ghcalltbl",""
.L928:	.data.w	.L927
	.endo	.L928
	.section ".ghrettbl",""
.L930:	.data.w	.L929
	.endo	.L930
.L932:	.data.w	.L931
	.endo	.L932
	.section ".ghcalltbl",""
.L934:	.data.w	.L933
	.endo	.L934
	.section ".ghrettbl",""
.L936:	.data.w	.L935
	.endo	.L936
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_SetRelativeThresholdDetCheck:
.LDW91:
	push	{r4-r6,lr}
	mov	r5,r1
.LDW02:
	b	.L1066

.L926:	.data.w	Ocu_ConfigPtr
	.endo	.L926

.L1066:

;line698
..lin.3629a0af..307a23b.0_3::
.LDWlin3:
..gh.beginasm.6:
	.endo	..gh.beginasm.6
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.7:
	.endo	..gh.endasm.7

	mov	r4,r2
;line700
..lin.3629a0af..307a23b.0_4::
.LDWlin4:
	mov	r6,r0
	mov	r1,8
.L1068:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L1070:

	popne	{r4-r6,pc}
	ldr	r1,.L1067
	ldr	r3,[r1]
	rsb	r1,r6,r6 lsl 2
	ldr	r2,[r3,16]
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	rsb	r2,r1,r1 lsl 2
	ldr	r1,[r3,r4 lsl 2]
	ldr	r1,[r1,4]
	add	r1,r1,r2 lsl 3
	ldr	r1,[r1,4]
	cmp	r5,r1
.L1072:

	popls	{r4-r6,pc}
	mov	r3,227
	mov	r2,8
	mov	r1,r0
	mov	r0,125
.L1074:

	bl	Det_ReportError
	mov	r0,1
.LDW12:
.L1076:

	pop	{r4-r6,pc}
__ghs_eofn_Ocu_SetRelativeThresholdDetCheck:
	.endf	Ocu_SetRelativeThresholdDetCheck
	.endf	Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;CoreId	r4	local
;ErrValue	r0	local

;ChannelNumber	r6	param
;RelativeValue	r5	param

	.section ".ghcalltbl",""
.L1069:	.data.w	.L1068
	.endo	.L1069
	.section ".ghrettbl",""
.L1071:	.data.w	.L1070
	.endo	.L1071
.L1073:	.data.w	.L1072
	.endo	.L1073
	.section ".ghcalltbl",""
.L1075:	.data.w	.L1074
	.endo	.L1075
	.section ".ghrettbl",""
.L1077:	.data.w	.L1076
	.endo	.L1077
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_EnableNotificationDetCheck:
.LDW22:
	push	{r2,r4-r5,lr}
.LDW32:
	b	.L1194

.L1067:	.data.w	Ocu_ConfigPtr
	.endo	.L1067

.L1194:

;line757
..lin.3629a0af..54e8654.0_5::
.LDWlin5:
..gh.beginasm.9:
	.endo	..gh.beginasm.9
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.10:
	.endo	..gh.endasm.10

	mov	r4,r2
;line759
..lin.3629a0af..54e8654.0_6::
.LDWlin6:
	mov	r5,r0
	mov	r1,11
.L1196:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L1198:

	popne	{r2,r4-r5,pc}
	ldr	r1,.L1195
	ldr	r3,[r1]
	rsb	r1,r5,r5 lsl 2
	ldr	r2,[r3,16]
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	rsb	r2,r1,r1 lsl 2
	ldr	r1,[r3,r4 lsl 2]
	ldr	r1,[r1,4]
	add	r1,r1,r2 lsl 3
	ldr	r1,[r1,8]
	cmp	r1,0
.L1200:

	popne	{r2,r4-r5,pc}
	mov	r3,6
	mov	r2,11
	mov	r0,125
.L1202:

	bl	Det_ReportError
	mov	r0,1
.LDW42:
.L1204:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Ocu_EnableNotificationDetCheck:
	.endf	Ocu_EnableNotificationDetCheck
	.endf	Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;CoreId	r4	local
;ErrValue	r0	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L1197:	.data.w	.L1196
	.endo	.L1197
	.section ".ghrettbl",""
.L1199:	.data.w	.L1198
	.endo	.L1199
.L1201:	.data.w	.L1200
	.endo	.L1201
	.section ".ghcalltbl",""
.L1203:	.data.w	.L1202
	.endo	.L1203
	.section ".ghrettbl",""
.L1205:	.data.w	.L1204
	.endo	.L1205
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.11:
	.endo	..gh.f.a.1.e.11
	.global	Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_DisableNotificationDetCheck:
.LDW52:
	push	{r2,r4-r5,lr}
.LDW62:
	b	.L1322

.L1195:	.data.w	Ocu_ConfigPtr
	.endo	.L1195

.L1322:

;line816
..lin.3629a0af..96863ca1.0_7::
.LDWlin7:
..gh.beginasm.12:
	.endo	..gh.beginasm.12
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.13:
	.endo	..gh.endasm.13

	mov	r4,r2
;line818
..lin.3629a0af..96863ca1.0_8::
.LDWlin8:
	mov	r5,r0
	mov	r1,10
.L1324:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L1326:

	popne	{r2,r4-r5,pc}
	ldr	r1,.L1323
	ldr	r3,[r1]
	rsb	r1,r5,r5 lsl 2
	ldr	r2,[r3,16]
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	rsb	r2,r1,r1 lsl 2
	ldr	r1,[r3,r4 lsl 2]
	ldr	r1,[r1,4]
	add	r1,r1,r2 lsl 3
	ldr	r1,[r1,8]
	cmp	r1,0
.L1328:

	popne	{r2,r4-r5,pc}
	mov	r3,6
	mov	r2,10
	mov	r0,125
.L1330:

	bl	Det_ReportError
	mov	r0,1
.LDW72:
.L1332:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Ocu_DisableNotificationDetCheck:
	.endf	Ocu_DisableNotificationDetCheck
	.endf	Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;CoreId	r4	local
;ErrValue	r0	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L1325:	.data.w	.L1324
	.endo	.L1325
	.section ".ghrettbl",""
.L1327:	.data.w	.L1326
	.endo	.L1327
.L1329:	.data.w	.L1328
	.endo	.L1329
	.section ".ghcalltbl",""
.L1331:	.data.w	.L1330
	.endo	.L1331
	.section ".ghrettbl",""
.L1333:	.data.w	.L1332
	.endo	.L1333
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
	.global	Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_DeInitCheck:
.LDW82:
	push	{r4-r6,lr}
	ldr	r2,.L1570
.LDW92:
	mov	r5,r0
	ldr	r1,[r2,r5 lsl 2]
	ldr	r1,[r1]
	mov	r0,0
	cmp	r1,1
	beq	.L1336
	mov	r3,2
	mov	r2,1
	mov	r1,r0
	mov	r0,125
.L1572:

	bl	Det_ReportError
	mov	r0,1
.L1574:

	pop	{r4-r6,pc}
.L1336:
	ldr	r1,.L1323
	ldr	r6,[r1]
	ldr	r6,[r6,r5 lsl 2]
	mov	r4,r0
	ldrb	r6,[r6]
	b	.L1342
.L1341:
	ldr	r3,.L1571
	lsr	r2,r4,24
	ldr	r1,[r3,r5 lsl 2]
	add	r2,r2,r2 lsl 2
	add	r1,r1,r2 lsl 2
	ldr	r2,[r1,8]
	cmp	r2,1
	bne	.L1340
	mov	r3,4
	mov	r1,r0
	mov	r0,125
.L1576:

	bl	Det_ReportError
	mov	r0,1
.L1340:
	add	r4,r4,1<<24
.L1342:
	cmp	r6,r4 lsr 24
.L1578:

	popls	{r4-r6,pc}
	cmp	r0,0
	beq	.L1341
.LDW03:
.L1580:

	pop	{r4-r6,pc}
__ghs_eofn_Ocu_DeInitCheck:
	.endf	Ocu_DeInitCheck
	.endf	Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;ErrValue	r0	local
;MaxChannel	r6	local

;CoreId	r5	param

	.section ".mcal_const_asil_d_unspecified","a"
Ocu_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_CoreChannelStatusPtr:
	.data.w	Ocu_ChannelStatusCore0
	.data.w	Ocu_ChannelStatusCore1
	.space	8
	.endo	Ocu_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_CoreChannelStatusPtr
	.section ".ghcalltbl",""
.L1573:	.data.w	.L1572
	.endo	.L1573
	.section ".ghrettbl",""
.L1575:	.data.w	.L1574
	.endo	.L1575
	.section ".ghcalltbl",""
.L1577:	.data.w	.L1576
	.endo	.L1577
	.section ".ghrettbl",""
.L1579:	.data.w	.L1578
	.endo	.L1579
.L1581:	.data.w	.L1580
	.endo	.L1581
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Ocu_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_ChannelStatusCore0:	.space	40
	.endo	Ocu_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_ChannelStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
Ocu_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.::
Ocu_ChannelStatusCore1:	.space	40
	.endo	Ocu_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.endo	Ocu_ChannelStatusCore1
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_GetReturnValue:
.LDW13:
.LDW23:
	cmp	r1,r2
	bhi	.L1584
	cmp	r1,r0
	cmpls	r0,r2
	bhs	.L1592
.L1591:
	mov	r0,1
.L1762:

	ret	
.L1584:
	cmp	r0,r1
	cmplo	r2,r0
	bhs	.L1591
.L1592:
	mov	r0,0
.LDW33:
.L1764:

	ret	
__ghs_eofn_Ocu_GetReturnValue:
	.endf	Ocu_GetReturnValue
	.endf	Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

;PostValue	r0	param
;StartVal	r1	param
;CompareVal	r2	param

	.section ".bss","awb"
.L1688:
	.endo	.L1688
	.section ".ghrettbl",""
.L1763:	.data.w	.L1762
	.endo	.L1763
.L1765:	.data.w	.L1764
	.endo	.L1765
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
	.global	Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_SetCompare:
.LDW43:
	str	lr,[sp,-4]!
	sub	sp,sp,20
	mov	r12,r1
.LDW53:
	strb	r3,[sp,8]
	mov	r1,0
	cmp	r2,0
	str	r1,[sp]
	str	r1,[sp,4]
	moveq	r1,2
	streq	r0,[sp]
	movne	r1,3
	strne	r0,[sp,4]
	str	r1,[sp,12]
	add	r2,sp,8
	mov	r1,sp
	mov	r0,r12
.L1871:

	bl	Gtm_Ocu_Hal_SetOutputBehavior
.LDW63:
	add	sp,sp,20
.L1873:

	ldr	pc,[sp],4
__ghs_eofn_Ocu_SetCompare:
	.endf	Ocu_SetCompare
	.endf	Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;BehaviorControl	[sp,8]	local
;CmpValue	[sp]	local

;CompareValue	r0	param
;HWchannelObjectPtr	r12	param
;Timebase	r2	param
;OutputAction	r3	param

	.section ".bss","awb"
.L1826:
	.endo	.L1826
	.section ".ghcalltbl",""
.L1872:	.data.w	.L1871
	.endo	.L1872
	.section ".ghrettbl",""
.L1874:	.data.w	.L1873
	.endo	.L1874
	.data
	.global	__caller.Gtm_Ocu_Hal_SetOutputBehavior.i.ppp

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
	.global	Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_StartChannelByAtom:
.LDW73:
	push	{r4-r8,lr}
	mov	r4,r0
	mov	r5,r1
	mov	r8,r2
.LDW83:
	mov	r0,r1
	mov	r1,3
.L2028:

	bl	Gtm_Ocu_Hal_ClearInterruptStatus
	movs	r2,r8
	mov	r0,r5
	moveq	r1,1
	movne	r2,1
	movne	r1,0
.L2030:

	bl	Gtm_Ocu_Hal_SetInterrupt
	and	r7,r0,1
	ldr	r6,[r4]
	mov	r0,r8
.L2032:

	bl	Gtm_Ocu_Hal_GetCounterValue
	sub	r0,r0,r6
	bic	r0,r0,255<<24
	mov	r2,r8
	cmp	r0,1<<23
	mov	r1,r5
	movhi	r0,0
	movls	r0,1
	ldrhi	r3,[r4,12]
	movls	r3,0
	strb	r0,[r4,16]
	addls	r0,r6,1<<23
	movhi	r0,r6
	bicls	r0,r0,255<<24
.L2034:

	bl	Ocu_SetCompare
	mov	r2,1
	and	r7,r7,r0
	mov	r0,r5
	mov	r1,r2
.L2036:

	bl	Gtm_Ocu_Hal_SetChannelOutput
	and	r0,r7,r0
.LDW93:
.L2038:

	pop	{r4-r8,pc}
__ghs_eofn_Ocu_StartChannelByAtom:
	.endf	Ocu_StartChannelByAtom
	.endf	Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
;AbsoluteValue	r6	local
;Ocu_RegRet	r7	local

;LocalChannelStatusPtr	r4	param
;HWchannelObjectPtr	r5	param
;Timebase	r8	param

	.section ".bss","awb"
.L1962:
	.endo	.L1962
	.section ".ghcalltbl",""
.L2029:	.data.w	.L2028
	.endo	.L2029
.L2031:	.data.w	.L2030
	.endo	.L2031
.L2033:	.data.w	.L2032
	.endo	.L2033
.L2035:	.data.w	.L2034
	.endo	.L2035
.L2037:	.data.w	.L2036
	.endo	.L2037
	.section ".ghrettbl",""
.L2039:	.data.w	.L2038
	.endo	.L2039
	.data
	.global	__caller.Gtm_Ocu_Hal_SetChannelOutput.i.pii

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.Gtm_Ocu_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Ocu_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Ocu_Hal_ClearInterruptStatus.v.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
	.global	Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.:
Ocu_GetHardwareChannelObjectPtr:
.LDW04:
.LDW14:
	ldr	r3,.L1323
	ldr	r2,[r3]
	rsb	r1,r1,r1 lsl 2
	ldr	r0,[r2,r0 lsl 2]
	ldr	r0,[r0,4]
	ldrb	r0,[r0,r1 lsl 3]
	rsb	r1,r0,r0 lsl 2
	ldr	r0,[r2,16]
	add	r0,r0,r1 lsl 2
	ldr	r3,[r0,8]
	mov	r1,44
	ldr	r0,[r2,20]
	mla	r0,r1,r3,r0
.LDW24:
.L2091:

	ret	
__ghs_eofn_Ocu_GetHardwareChannelObjectPtr:
	.endf	Ocu_GetHardwareChannelObjectPtr
	.endf	Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

;CoreId	r0	param
;ChInCoreIndex	r1	param

	.section ".ghrettbl",""
.L2092:	.data.w	.L2091
	.endo	.L2092
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.19:
	.endo	..gh.f.a.1.e.19
__callee.Ocu_GetVersionInfo.v.p::
	.size	__callee.Ocu_GetVersionInfo.v.p,0
Ocu_GetVersionInfo::
.LDW34:
.LDW44:
	movs	r1,r0
	moveq	r3,8
	moveq	r2,9
	moveq	r0,125
.L2187:

	beq	Det_ReportError
.L2095:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,125
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW54:
.L2189:

	ret	
__ghs_eofn_Ocu_GetVersionInfo::
	.endf	Ocu_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L2149:
	.endo	.L2149
	.section ".ghtailcalltbl",""
	.align	4
.L2188:	.data.w	.L2187
	.endo	.L2188
	.section ".ghrettbl",""
.L2190:	.data.w	.L2189
	.endo	.L2190
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Ocu_ConfigPtr - Ocu_ConfigPtr) +0 == 0
..gh.f.a.1.e.20:
	.endo	..gh.f.a.1.e.20
__callee.Ocu_Init.v.p::
	.size	__callee.Ocu_Init.v.p,0
Ocu_Init::
.LDW64:
	push	{r4-fp,lr}
	sub	sp,sp,20
.LDW74:
	mov	r5,1
	b	.L2785

.L1323:	.data.w	Ocu_ConfigPtr
	.endo	.L1323

.L1570:	.data.w	Ocu_CoreDriverStatusPtr
	.endo	.L1570

.L1571:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L1571

.L2785:

;line1289
..lin.3629a0af..40960d1f.0_9::
.LDWlin9:
..gh.beginasm.21:
	.endo	..gh.beginasm.21
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.22:
	.endo	..gh.endasm.22

;line1293
..lin.3629a0af..40960d1f.0_10::
.LDWlin10:
	mov	r1,r4
	mov	r8,r0
.L2789:

	bl	Ocu_InitDetCheck
	cmp	r0,0
	ldreq	r10,.L2786
	ldreq	r0,[r8,r4 lsl 2]
	streq	r8,[r10]
	ldrbeq	r1,[r0]
	ldreq	fp,[r0,4]
	moveq	r9,0
	strbeq	r1,[sp,7]
	beq	.L2202
	b	.L2191
.L2205:
	ldr	r2,.L2787
	ldr	r1,[r2,r4 lsl 2]
	add	r0,r9,r9 lsl 2
	add	r6,r1,r0 lsl 2
	rsb	r0,r9,r9 lsl 2
	lsl	r7,r0,3
	ldrb	r0,[fp,r7]
	ldr	r1,[r8,16]
	rsb	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 2
	ldr	r1,[r0,8]
	ldr	r0,[r10]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	str	r1,[sp,12]
	add	r0,r7,r0
	ldr	r0,[r0,12]
	mov	r1,r9
	cmp	r0,1
	moveq	r0,3
	movne	r0,0
	str	r0,[r6,12]
	mov	r0,r4
.L2791:

	bl	Ocu_GetHardwareChannelObjectPtr
	str	r0,[sp,8]
	mov	r0,7
.L2793:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L2216
	ldr	r1,[r8,20]
	ldr	r2,[sp,12]
	mov	r0,44
	mla	r0,r2,r0,r1
	add	r1,r0,4
	ldr	r0,[sp,8]
.L2795:

	bl	Gtm_Ocu_Hal_InitChannel
	and	r5,r5,r0
	ldr	r0,[r10]
	ldr	r0,[r0,r4 lsl 2]
	ldr	r0,[r0,4]
	add	r0,r7,r0
	ldr	r0,[r0,12]
	cmp	r0,0
	bne	.L2208
	ldr	r0,[sp,8]
	mov	r2,1
	mov	r1,0
.L2797:

	bl	Gtm_Ocu_Hal_SetChannelOutput
	and	r5,r5,r0
.L2208:
	mov	r0,7
.L2799:

	bl	Mcal_ReleaseLock
	cmp	r5,1
	addeq	r0,r7,fp
	ldreq	r0,[r0,16]
	streq	r0,[r6]
	moveq	r0,0
	streq	r0,[r6,8]
	strbeq	r0,[r6,4]
	add	r9,r9,1
	uxtb	r9,r9
.L2202:
	ldrb	r0,[sp,7]
	cmp	r9,r0
	blo	.L2205
	cmp	r5,1
	beq	.L2215
.L2216:
	mov	r2,0
	mov	r3,228
	mov	r0,125
	mov	r1,r2
.L2801:

	bl	Det_ReportRuntimeError
	b	.L2191
.L2215:
	ldr	r0,.L2788
	ldr	r0,[r0,r4 lsl 2]
	str	r5,[r0]
.L2191:
.LDW84:
	add	sp,sp,20
.L2803:

	pop	{r4-fp,pc}
__ghs_eofn_Ocu_Init::
	.endf	Ocu_Init
;CoreId	r4	local
;MaxChannel	[sp,7]	local
;ChanInCoreIndex	r9	local
;ChannelConfigPtr	fp	local
;LocalChannelStatusPtr	r6	local
;HWConfigIndex	[sp,12]	local
;HWchannelObjectPtr	[sp,8]	local
;Ocu_RegRet	r5	local

;ConfigPtr	r8	param

	.section ".ghcalltbl",""
.L2790:	.data.w	.L2789
	.endo	.L2790
.L2792:	.data.w	.L2791
	.endo	.L2792
.L2794:	.data.w	.L2793
	.endo	.L2794
.L2796:	.data.w	.L2795
	.endo	.L2796
.L2798:	.data.w	.L2797
	.endo	.L2798
.L2800:	.data.w	.L2799
	.endo	.L2800
.L2802:	.data.w	.L2801
	.endo	.L2802
	.section ".ghrettbl",""
.L2804:	.data.w	.L2803
	.endo	.L2804
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Gtm_Ocu_Hal_SetChannelOutput.i.pii

	.global	__caller.Gtm_Ocu_Hal_InitChannel.i.pp

	.global	__caller.Mcal_GetLock.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.23:
	.endo	..gh.f.a.1.e.23
__callee.Ocu_DeInit.v.v::
	.size	__callee.Ocu_DeInit.v.v,0
Ocu_DeInit::
.LDW94:
	push	{r2,r4-r9,lr}
.LDW05:
	mov	r6,1
	b	.L2982

.L2786:	.data.w	Ocu_ConfigPtr
	.endo	.L2786

.L2787:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L2787

.L2788:	.data.w	Ocu_CoreDriverStatusPtr
	.endo	.L2788

.L2982:

;line1420
..lin.3629a0af..b1ef9188.0_11::
.LDWlin11:
..gh.beginasm.24:
	.endo	..gh.beginasm.24
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.25:
	.endo	..gh.endasm.25

;line1423
..lin.3629a0af..b1ef9188.0_12::
.LDWlin12:
	mov	r0,r4
.L2986:

	bl	Ocu_DeInitCheck
	cmp	r0,0
	ldreq	r0,.L2983
	ldreq	r8,[r0]
	ldreq	r8,[r8,r4 lsl 2]
	moveq	r7,0
	ldrbeq	r8,[r8]
	beq	.L2816
.L2988:

	pop	{r2,r4-r9,pc}
.L2815:
	mov	r1,r5
	mov	r0,r4
.L2990:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r9,r0
	mov	r1,3
.L2992:

	bl	Gtm_Ocu_Hal_ClearInterruptStatus
	mov	r2,0
	mov	r0,r9
	mov	r1,r2
.L2994:

	bl	Gtm_Ocu_Hal_SetInterrupt
	ldr	r2,.L2984
	and	r6,r6,r0
	ldr	r0,[r2,r4 lsl 2]
	add	r1,r5,r5 lsl 2
	add	r0,r0,r1 lsl 2
	mov	r1,0
	add	r7,r7,1<<24
	strb	r1,[r0,4]
.L2816:
	lsr	r5,r7,24
	cmp	r5,r8
	blo	.L2815
	mov	r1,0
	cmp	r6,1
	beq	.L2817
	mov	r3,228
	mov	r2,1
	mov	r0,125
.L2996:

	bl	Det_ReportRuntimeError
.L2998:

	pop	{r2,r4-r9,pc}
.L2817:
	ldr	r0,.L2985
	ldr	r0,[r0,r4 lsl 2]
	str	r1,[r0]
.LDW15:
.L3000:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Ocu_DeInit::
	.endf	Ocu_DeInit
;CoreId	r4	local
;HWchannelObjectPtr	r9	local
;Ocu_RegRet	r6	local
;Ocu_ChInCore	r8	local

	.section ".ghcalltbl",""
.L2987:	.data.w	.L2986
	.endo	.L2987
	.section ".ghrettbl",""
.L2989:	.data.w	.L2988
	.endo	.L2989
	.section ".ghcalltbl",""
.L2991:	.data.w	.L2990
	.endo	.L2991
.L2993:	.data.w	.L2992
	.endo	.L2993
.L2995:	.data.w	.L2994
	.endo	.L2995
.L2997:	.data.w	.L2996
	.endo	.L2997
	.section ".ghrettbl",""
.L2999:	.data.w	.L2998
	.endo	.L2999
.L3001:	.data.w	.L3000
	.endo	.L3001
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Gtm_Ocu_Hal_SetInterrupt.i.pii

	.global	__caller.Gtm_Ocu_Hal_ClearInterruptStatus.v.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Ocu_ConfigPtr - Ocu_ConfigPtr) +0 == 0
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
__callee.Ocu_StartChannel.v.i::
	.size	__callee.Ocu_StartChannel.v.i,0
Ocu_StartChannel::
.LDW25:
	push	{r2,r4-r9,lr}
.LDW35:
	mov	r6,1
	b	.L3591

.L2983:	.data.w	Ocu_ConfigPtr
	.endo	.L2983

.L2984:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L2984

.L2985:	.data.w	Ocu_CoreDriverStatusPtr
	.endo	.L2985

.L3591:

;line1505
..lin.3629a0af..10c99032.0_13::
.LDWlin13:
..gh.beginasm.27:
	.endo	..gh.beginasm.27
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.28:
	.endo	..gh.endasm.28

;line1511
..lin.3629a0af..10c99032.0_14::
.LDWlin14:
	mov	r2,r4
	mov	r5,r0
	mov	r1,2
.L3594:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L3596:

	popne	{r2,r4-r9,pc}
	ldr	r9,.L3592
	ldr	r2,[r9]
	ldr	r2,[r2,16]
	rsb	r1,r5,r5 lsl 2
	add	r2,r2,r1 lsl 2
	ldr	r0,.L3593
	ldrb	r5,[r2,4]
	ldr	r0,[r0,r4 lsl 2]
	add	r1,r5,r5 lsl 2
	add	r7,r0,r1 lsl 2
	ldr	r0,[r7,8]
	cmp	r0,1
	moveq	r3,9
	beq	.L3581
.L3010:
	mov	r1,r5
	mov	r0,r4
.L3598:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r8,r0
.L3600:

	bl	SchM_Enter_Ocu_StartChannel
	mov	r0,7
.L3602:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L3023
	ldr	r2,[r9]
	ldr	r1,[r2,r4 lsl 2]
	ldr	r1,[r1,4]
	rsb	r0,r5,r5 lsl 2
	ldrb	r1,[r1,r0 lsl 3]
	rsb	r0,r1,r1 lsl 2
	ldr	r1,[r2,16]
	add	r1,r1,r0 lsl 2
	ldr	r4,[r1,8]
	cmp	r4,4
	ldrlo	r1,[r2,20]
	movlo	r0,44
	mlalo	r0,r4,r0,r1
	movhs	r2,255
	ldrlo	r2,[r0,40]
	mov	r1,r8
	mov	r0,r7
.L3604:

	bl	Ocu_StartChannelByAtom
	and	r6,r6,r0
	mov	r0,7
.L3606:

	bl	Mcal_ReleaseLock
	cmp	r6,1
	bne	.L3023
	str	r6,[r7,8]
.L3608:

	bl	SchM_Exit_Ocu_StartChannel
.L3610:

	pop	{r2,r4-r9,pc}
.L3023:
.L3612:

	bl	SchM_Exit_Ocu_StartChannel
	mov	r3,228
.L3581:

	mov	r2,2
	mov	r1,0
	mov	r0,125
.L3614:

	bl	Det_ReportRuntimeError
.LDW45:
.L3616:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Ocu_StartChannel::
	.endf	Ocu_StartChannel
;CoreId	r4	local
;ChanInCoreIndex	r5	local
;LocalChannelStatusPtr	r7	local
;HWchannelObjectPtr	r8	local
;Ocu_RegRet	r6	local
;HWConfigIndex	r1	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L3595:	.data.w	.L3594
	.endo	.L3595
	.section ".ghrettbl",""
.L3597:	.data.w	.L3596
	.endo	.L3597
	.section ".ghcalltbl",""
.L3599:	.data.w	.L3598
	.endo	.L3599
.L3601:	.data.w	.L3600
	.endo	.L3601
.L3603:	.data.w	.L3602
	.endo	.L3603
.L3605:	.data.w	.L3604
	.endo	.L3605
.L3607:	.data.w	.L3606
	.endo	.L3607
.L3609:	.data.w	.L3608
	.endo	.L3609
	.section ".ghrettbl",""
.L3611:	.data.w	.L3610
	.endo	.L3611
	.section ".ghcalltbl",""
.L3613:	.data.w	.L3612
	.endo	.L3613
.L3615:	.data.w	.L3614
	.endo	.L3615
	.section ".ghrettbl",""
.L3617:	.data.w	.L3616
	.endo	.L3617
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Ocu_StartChannel.v.v

	.global	__caller.SchM_Exit_Ocu_StartChannel.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Ocu_StartChannel.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Ocu_ConfigPtr - Ocu_ConfigPtr) +0 == 0
..gh.f.a.1.e.29:
	.endo	..gh.f.a.1.e.29
__callee.Ocu_StopChannel.v.i::
	.size	__callee.Ocu_StopChannel.v.i,0
Ocu_StopChannel::
.LDW55:
	push	{r2,r4-r9,lr}
.LDW65:
	mov	r5,1
	b	.L3879

.L3592:	.data.w	Ocu_ConfigPtr
	.endo	.L3592

.L3593:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L3593

.L3879:

;line1612
..lin.3629a0af..668fe5ea.0_15::
.LDWlin15:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.31:
	.endo	..gh.endasm.31

;line1618
..lin.3629a0af..668fe5ea.0_16::
.LDWlin16:
	mov	r2,r4
	mov	r6,r0
	mov	r1,3
.L3882:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L3884:

	popne	{r2,r4-r9,pc}
	ldr	r8,.L3880
	ldr	r2,[r8]
	ldr	r2,[r2,16]
	rsb	r1,r6,r6 lsl 2
	add	r2,r2,r1 lsl 2
	ldr	r0,.L3881
	ldrb	r7,[r2,4]
	ldr	r0,[r0,r4 lsl 2]
	add	r1,r7,r7 lsl 2
	add	r6,r0,r1 lsl 2
	ldr	r0,[r6,8]
	cmp	r0,1
.L3886:

	popne	{r2,r4-r9,pc}
	mov	r1,r7
	mov	r0,r4
.L3888:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r9,r0
.L3890:

	bl	SchM_Enter_Ocu_StopChannel
	mov	r0,7
.L3892:

	bl	Mcal_GetLock
	cmp	r0,0
	bne	.L3628
	ldr	r0,[r8]
	ldr	r0,[r0,r4 lsl 2]
	rsb	r1,r7,r7 lsl 2
	ldr	r0,[r0,4]
	lsl	r7,r1,3
	add	r0,r7,r0
	ldr	r0,[r0,12]
	cmp	r0,0
	bne	.L3632
	mov	r0,r9
	mov	r1,0
.L3894:

	bl	Gtm_Ocu_Hal_SetSignalLevelControl
	and	r5,r5,r0
.L3632:
	mov	r0,r9
	mov	r2,1
	mov	r1,0
.L3896:

	bl	Gtm_Ocu_Hal_SetChannelOutput
	and	r5,r5,r0
	cmp	r5,1
	moveq	r0,0
	streq	r0,[r6,8]
	streq	r0,[r6,12]
	ldreq	r0,[r8]
	ldreq	r0,[r0,r4 lsl 2]
	ldreq	r0,[r0,4]
	addeq	r0,r7,r0
	ldreq	r0,[r0,16]
	streq	r0,[r6]
	mov	r0,7
.L3898:

	bl	Mcal_ReleaseLock
	b	.L3635
.L3628:
	mov	r5,0
.L3635:
.L3900:

	bl	SchM_Exit_Ocu_StopChannel
	cmp	r5,1
	movne	r3,228
	movne	r2,3
	movne	r1,0
	movne	r0,125
.L3902:

	blne	Det_ReportRuntimeError
.LDW75:
.L3904:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Ocu_StopChannel::
	.endf	Ocu_StopChannel
;CoreId	r4	local
;ChanInCoreIndex	r7	local
;LocalChannelStatusPtr	r6	local
;HWchannelObjectPtr	r9	local
;Ocu_RegRet	r5	local

;ChannelNumber	r6	param

	.section ".ghcalltbl",""
.L3883:	.data.w	.L3882
	.endo	.L3883
	.section ".ghrettbl",""
.L3885:	.data.w	.L3884
	.endo	.L3885
.L3887:	.data.w	.L3886
	.endo	.L3887
	.section ".ghcalltbl",""
.L3889:	.data.w	.L3888
	.endo	.L3889
.L3891:	.data.w	.L3890
	.endo	.L3891
.L3893:	.data.w	.L3892
	.endo	.L3893
.L3895:	.data.w	.L3894
	.endo	.L3895
.L3897:	.data.w	.L3896
	.endo	.L3897
.L3899:	.data.w	.L3898
	.endo	.L3899
.L3901:	.data.w	.L3900
	.endo	.L3901
.L3903:	.data.w	.L3902
	.endo	.L3903
	.section ".ghrettbl",""
.L3905:	.data.w	.L3904
	.endo	.L3905
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Ocu_StopChannel.v.v

	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Gtm_Ocu_Hal_SetChannelOutput.i.pii

	.global	__caller.Gtm_Ocu_Hal_SetSignalLevelControl.i.pi

	.global	__caller.Mcal_GetLock.i.i

	.global	__caller.SchM_Enter_Ocu_StopChannel.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.32:
	.endo	..gh.f.a.1.e.32
__callee.Ocu_SetPinState.v.ii::
	.size	__callee.Ocu_SetPinState.v.ii,0
Ocu_SetPinState::
.LDW85:
	push	{r2,r4-r7,lr}
	mov	r6,r1
.LDW95:
	mov	r5,1
	b	.L4166

.L3880:	.data.w	Ocu_ConfigPtr
	.endo	.L3880

.L3881:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L3881

.L4166:

;line1738
..lin.3629a0af..624eb41f.0_17::
.LDWlin17:
..gh.beginasm.33:
	.endo	..gh.beginasm.33
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.34:
	.endo	..gh.endasm.34

	mov	r4,r2
;line1744
..lin.3629a0af..624eb41f.0_18::
.LDWlin18:
	mov	r7,r0
	mov	r1,4
.L4169:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L4171:

	popne	{r2,r4-r7,pc}
	ldr	r0,.L4167
	ldr	r2,[r0]
	ldr	r3,[r2,16]
	rsb	r1,r7,r7 lsl 2
	ldr	r0,.L4168
	add	r3,r3,r1 lsl 2
	ldrb	r1,[r3,4]
	ldr	r0,[r0,r4 lsl 2]
	add	r3,r1,r1 lsl 2
	add	r12,r0,r3 lsl 2
	ldr	r0,[r2,r4 lsl 2]
	ldr	r0,[r0,4]
	rsb	r2,r1,r1 lsl 2
	add	r0,r0,r2 lsl 3
	ldr	r0,[r0,12]
	mov	r3,10
	cmp	r0,0
	bne	.L3975
	mov	r3,4
	cmp	r6,1
	ble	.L3921
.L3975:
	mov	r2,4
	b	.L4157
.L3921:
	ldr	r0,[r12,8]
	cmp	r0,0
	bne	.L3922
	mov	r0,r4
.L4173:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r1,r6
.L4175:

	bl	Gtm_Ocu_Hal_SetSignalLevel
	and	r0,r5,r0
	cmp	r0,1
	movne	r3,228
	movne	r2,4
	movne	r1,0
	movne	r0,125
.L4177:

	blne	Det_ReportRuntimeError
.L4179:

	pop	{r2,r4-r7,pc}
.L3922:
	mov	r2,r3
.L4157:

	mov	r1,0
	mov	r0,125
.L4181:

	bl	Det_ReportError
.LDW06:
.L4183:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Ocu_SetPinState::
	.endf	Ocu_SetPinState
;CoreId	r4	local
;ChanInCoreIndex	r1	local
;LocalChannelStatusPtr	r12	local
;Ocu_RegRet	r5	local

;ChannelNumber	r7	param
;PinState	r6	param

	.section ".ghcalltbl",""
.L4170:	.data.w	.L4169
	.endo	.L4170
	.section ".ghrettbl",""
.L4172:	.data.w	.L4171
	.endo	.L4172
	.section ".ghcalltbl",""
.L4174:	.data.w	.L4173
	.endo	.L4174
.L4176:	.data.w	.L4175
	.endo	.L4176
.L4178:	.data.w	.L4177
	.endo	.L4178
	.section ".ghrettbl",""
.L4180:	.data.w	.L4179
	.endo	.L4180
	.section ".ghcalltbl",""
.L4182:	.data.w	.L4181
	.endo	.L4182
	.section ".ghrettbl",""
.L4184:	.data.w	.L4183
	.endo	.L4184
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Gtm_Ocu_Hal_SetSignalLevel.i.pi

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.35:
	.endo	..gh.f.a.1.e.35
__callee.Ocu_SetPinAction.v.ii::
	.size	__callee.Ocu_SetPinAction.v.ii,0
Ocu_SetPinAction::
.LDW16:
	push	{r2,r4-r7,lr}
	mov	r6,r1
.LDW26:
	mov	r5,1
	b	.L4432

.L4167:	.data.w	Ocu_ConfigPtr
	.endo	.L4167

.L4168:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L4168

.L4432:

;line1868
..lin.3629a0af..80fefa3c.0_19::
.LDWlin19:
..gh.beginasm.36:
	.endo	..gh.beginasm.36
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.37:
	.endo	..gh.endasm.37

	mov	r4,r2
;line1875
..lin.3629a0af..80fefa3c.0_20::
.LDWlin20:
	mov	r7,r0
	mov	r1,5
.L4435:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
.L4437:

	popne	{r2,r4-r7,pc}
	ldr	r0,.L4433
	ldr	r2,[r0]
	ldr	r3,[r2,16]
	rsb	r1,r7,r7 lsl 2
	ldr	r0,.L4434
	add	r3,r3,r1 lsl 2
	ldrb	r1,[r3,4]
	ldr	r0,[r0,r4 lsl 2]
	add	r3,r1,r1 lsl 2
	add	r7,r0,r3 lsl 2
	ldr	r0,[r2,r4 lsl 2]
	ldr	r0,[r0,4]
	rsb	r2,r1,r1 lsl 2
	add	r0,r0,r2 lsl 3
	ldr	r0,[r0,12]
	mov	r3,10
	cmp	r0,0
	bne	.L4250
	mov	r3,5
	cmp	r6,3
	ble	.L4202
.L4250:
	mov	r2,5
	mov	r1,0
	mov	r0,125
.L4439:

	bl	Det_ReportError
.L4441:

	pop	{r2,r4-r7,pc}
.L4202:
	mov	r0,r4
.L4443:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r4,r0
.L4445:

	bl	SchM_Enter_Ocu_SetPinAction
	uxtb	r1,r6
	mov	r0,r4
.L4447:

	bl	Gtm_Ocu_Hal_SetSignalLevelControl
	and	r0,r5,r0
	cmp	r0,1
	bne	.L4203
	str	r6,[r7,12]
.L4449:

	bl	SchM_Exit_Ocu_SetPinAction
.L4451:

	pop	{r2,r4-r7,pc}
.L4203:
.L4453:

	bl	SchM_Exit_Ocu_SetPinAction
	mov	r3,228
	mov	r2,5
	mov	r1,0
	mov	r0,125
.L4455:

	bl	Det_ReportRuntimeError
.LDW36:
.L4457:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Ocu_SetPinAction::
	.endf	Ocu_SetPinAction
;CoreId	r4	local
;ChanInCoreIndex	r1	local
;LocalChannelStatusPtr	r7	local
;HWchannelObjectPtr	r4	local
;Ocu_RegRet	r5	local

;ChannelNumber	r7	param
;OutputAction	r6	param

	.section ".ghcalltbl",""
.L4436:	.data.w	.L4435
	.endo	.L4436
	.section ".ghrettbl",""
.L4438:	.data.w	.L4437
	.endo	.L4438
	.section ".ghcalltbl",""
.L4440:	.data.w	.L4439
	.endo	.L4440
	.section ".ghrettbl",""
.L4442:	.data.w	.L4441
	.endo	.L4442
	.section ".ghcalltbl",""
.L4444:	.data.w	.L4443
	.endo	.L4444
.L4446:	.data.w	.L4445
	.endo	.L4446
.L4448:	.data.w	.L4447
	.endo	.L4448
.L4450:	.data.w	.L4449
	.endo	.L4450
	.section ".ghrettbl",""
.L4452:	.data.w	.L4451
	.endo	.L4452
	.section ".ghcalltbl",""
.L4454:	.data.w	.L4453
	.endo	.L4454
.L4456:	.data.w	.L4455
	.endo	.L4456
	.section ".ghrettbl",""
.L4458:	.data.w	.L4457
	.endo	.L4458
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Ocu_SetPinAction.v.v

	.global	__caller.SchM_Exit_Ocu_SetPinAction.v.v

	.global	__caller.Gtm_Ocu_Hal_SetSignalLevelControl.i.pi

	.global	__caller.SchM_Enter_Ocu_SetPinAction.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.38:
	.endo	..gh.f.a.1.e.38
__callee.Ocu_GetCounter.i.i::
	.size	__callee.Ocu_GetCounter.i.i,0
Ocu_GetCounter::
.LDW46:
	push	{r4-r6,lr}
.LDW56:
	mov	r4,0
	b	.L4612

.L4433:	.data.w	Ocu_ConfigPtr
	.endo	.L4433

.L4434:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L4434

.L4612:

;line1989
..lin.3629a0af..3662af2b.0_21::
.LDWlin21:
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
;line1995
..lin.3629a0af..3662af2b.0_22::
.LDWlin22:
	mov	r6,r0
	mov	r1,6
.L4614:

	bl	Ocu_CheckDetErrors
	cmp	r0,0
	bne	.L4465
	ldr	r0,.L4613
	ldr	r1,[r0]
	ldr	r2,[r1,16]
	rsb	r3,r6,r6 lsl 2
	add	r0,r2,r3 lsl 2
	ldrb	r3,[r0,4]
	rsb	r0,r3,r3 lsl 2
	ldr	r3,[r1,r5 lsl 2]
	ldr	r3,[r3,4]
	ldrb	r3,[r3,r0 lsl 3]
	rsb	r3,r3,r3 lsl 2
	add	r0,r2,r3 lsl 2
	ldr	r2,[r0,8]
	cmp	r2,4
	ldrlo	r1,[r1,20]
	movlo	r0,44
	mlalo	r0,r2,r0,r1
	movhs	r0,255
	ldrlo	r0,[r0,40]
.L4616:

	bl	Gtm_Ocu_Hal_GetCounterValue
	mov	r4,r0
.L4465:
	mov	r0,r4
.LDW66:
.L4618:

	pop	{r4-r6,pc}
__ghs_eofn_Ocu_GetCounter::
	.endf	Ocu_GetCounter
;CoreId	r5	local
;CounterValue	r4	local
;HWConfigIndex	r2	local

;ChannelNumber	r6	param

	.section ".ghcalltbl",""
.L4615:	.data.w	.L4614
	.endo	.L4615
.L4617:	.data.w	.L4616
	.endo	.L4617
	.section ".ghrettbl",""
.L4619:	.data.w	.L4618
	.endo	.L4619
	.data
	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.41:
	.endo	..gh.f.a.1.e.41
__callee.Ocu_SetAbsoluteThreshold.i.iii::
	.size	__callee.Ocu_SetAbsoluteThreshold.i.iii,0
Ocu_SetAbsoluteThreshold::
.LDW76:
	push	{r2,r4-fp,lr}
	mov	r8,r1
.LDW86:
	mov	r4,0
	mov	r6,1
	b	.L4851

.L4613:	.data.w	Ocu_ConfigPtr
	.endo	.L4613

.L4851:

;line2065
..lin.3629a0af..479686c3.0_23::
.LDWlin23:
..gh.beginasm.42:
	.endo	..gh.beginasm.42
 mrc p15, 0, r1, c0, c0, 5
 and r3, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r3, r3, r1         

..gh.endasm.43:
	.endo	..gh.endasm.43

	mov	r5,r3
;line2075
..lin.3629a0af..479686c3.0_24::
.LDWlin24:
	mov	r7,r2
	mov	r1,r8
	mov	r9,r0
.L4854:

	bl	Ocu_SetAbsoluteThresholdDetCheck
	cmp	r0,0
	bne	.L4626
	ldr	r1,.L4852
	ldr	r0,[r1]
	ldr	r1,[r0,16]
	rsb	r2,r9,r9 lsl 2
	ldr	r12,.L4853
	add	r2,r1,r2 lsl 2
	ldrb	fp,[r2,4]
	ldr	r3,[r12,r5 lsl 2]
	add	r2,fp,fp lsl 2
	add	r10,r3,r2 lsl 2
	ldr	r2,[r0,r5 lsl 2]
	ldr	r2,[r2,4]
	rsb	r3,fp,fp lsl 2
	ldrb	r2,[r2,r3 lsl 3]
	rsb	r2,r2,r2 lsl 2
	add	r1,r1,r2 lsl 2
	ldr	r1,[r1,8]
	cmp	r1,4
	ldrlo	r0,[r0,20]
	movlo	r2,44
	mlalo	r0,r2,r1,r0
	movhs	r4,255
	ldrlo	r4,[r0,40]
.L4856:

	bl	SchM_Enter_Ocu_SetAbsoluteThreshold
	str	r7,[r10]
	mov	r0,r4
.L4858:

	bl	Gtm_Ocu_Hal_GetCounterValue
	mov	r9,r0
	mov	r1,fp
	mov	r0,r5
.L4860:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r1,r0
	sub	r0,r9,r7
	bic	r0,r0,255<<24
	cmp	r0,1<<23
	mov	r2,r4
	ldrhi	r3,[r10,12]
	movhi	r0,0
	addls	r0,r7,1<<23
	strbls	r6,[r10,16]
	movls	r3,0
	strbhi	r0,[r10,16]
	movhi	r0,r7
	bicls	r0,r0,255<<24
.L4862:

	bl	Ocu_SetCompare
	and	r0,r6,r0
	cmp	r0,1
	bne	.L4638
	mov	r0,r4
.L4864:

	bl	Gtm_Ocu_Hal_GetCounterValue
	mov	r2,r7
	mov	r1,r8
.L4866:

	bl	Ocu_GetReturnValue
	mov	r4,r0
.L4868:

	bl	SchM_Exit_Ocu_SetAbsoluteThreshold
	b	.L4626
.L4638:
	mov	r4,2
.L4870:

	bl	SchM_Exit_Ocu_SetAbsoluteThreshold
	mov	r3,228
	mov	r2,7
	mov	r1,0
	mov	r0,125
.L4872:

	bl	Det_ReportRuntimeError
.L4626:
	mov	r0,r4
.LDW96:
.L4874:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Ocu_SetAbsoluteThreshold::
	.endf	Ocu_SetAbsoluteThreshold
;CoreId	r5	local
;ChanInCoreIndex	fp	local
;LocalChannelStatusPtr	r10	local
;CurrentCounter	r9	local
;IntervalStatus	r4	local
;Timebase	r4	local
;HWchannelObjectPtr	r1	local
;Ocu_RegRet	r6	local
;HWConfigIndex	r1	local

;ChannelNumber	r9	param
;ReferenceValue	r8	param
;AbsoluteValue	r7	param

	.section ".ghcalltbl",""
.L4855:	.data.w	.L4854
	.endo	.L4855
.L4857:	.data.w	.L4856
	.endo	.L4857
.L4859:	.data.w	.L4858
	.endo	.L4859
.L4861:	.data.w	.L4860
	.endo	.L4861
.L4863:	.data.w	.L4862
	.endo	.L4863
.L4865:	.data.w	.L4864
	.endo	.L4865
.L4867:	.data.w	.L4866
	.endo	.L4867
.L4869:	.data.w	.L4868
	.endo	.L4869
.L4871:	.data.w	.L4870
	.endo	.L4871
.L4873:	.data.w	.L4872
	.endo	.L4873
	.section ".ghrettbl",""
.L4875:	.data.w	.L4874
	.endo	.L4875
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Ocu_SetAbsoluteThreshold.v.v

	.global	__caller.SchM_Exit_Ocu_SetAbsoluteThreshold.v.v

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.SchM_Enter_Ocu_SetAbsoluteThreshold.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Ocu_ConfigPtr - Ocu_ConfigPtr) +0 == 0
..gh.f.a.1.e.44:
	.endo	..gh.f.a.1.e.44
__callee.Ocu_SetRelativeThreshold.i.ii::
	.size	__callee.Ocu_SetRelativeThreshold.i.ii,0
Ocu_SetRelativeThreshold::
.LDW07:
	push	{r4-fp,lr}
	sub	sp,sp,12
	mov	fp,r1
.LDW17:
	mov	r4,0
	mov	r9,1
	b	.L5154

.L4852:	.data.w	Ocu_ConfigPtr
	.endo	.L4852

.L4853:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L4853

.L5154:

;line2202
..lin.3629a0af..b2802960.0_25::
.LDWlin25:
..gh.beginasm.45:
	.endo	..gh.beginasm.45
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.46:
	.endo	..gh.endasm.46

;line2208
..lin.3629a0af..b2802960.0_26::
.LDWlin26:
	mov	r1,fp
	mov	r6,r0
.L5157:

	bl	Ocu_SetRelativeThresholdDetCheck
	cmp	r0,0
	bne	.L4882
	ldr	r7,.L5155
	ldr	r0,[r7]
	ldr	r1,[r0,16]
	rsb	r2,r6,r6 lsl 2
	add	r2,r1,r2 lsl 2
	ldr	r12,.L5156
	ldrb	r8,[r2,4]
	ldr	r3,[r12,r5 lsl 2]
	add	r2,r8,r8 lsl 2
	add	r6,r3,r2 lsl 2
	rsb	r2,r8,r8 lsl 2
	lsl	r10,r2,3
	ldr	r2,[r0,r5 lsl 2]
	ldr	r2,[r2,4]
	ldrb	r2,[r2,r10]
	rsb	r2,r2,r2 lsl 2
	add	r1,r1,r2 lsl 2
	ldr	r1,[r1,8]
	cmp	r1,4
	ldrlo	r0,[r0,20]
	movlo	r2,44
	mlalo	r0,r2,r1,r0
	movhs	r4,255
	ldrlo	r4,[r0,40]
.L5159:

	bl	SchM_Enter_Ocu_SetRelativeThreshold
	mov	r0,r4
.L5161:

	bl	Gtm_Ocu_Hal_GetCounterValue
	str	r0,[sp,4]
	add	fp,r0,fp
	ldr	r0,[r7]
	ldr	r0,[r0,r5 lsl 2]
	ldr	r0,[r0,4]
	add	r0,r10,r0
	ldr	r0,[r0,4]
	cmp	fp,r0
	subhi	fp,fp,r0
	str	fp,[r6]
	mov	r1,r8
	mov	r0,r5
.L5163:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r5,r0
	mov	r0,r4
.L5165:

	bl	Gtm_Ocu_Hal_GetCounterValue
	sub	r0,r0,fp
	bic	r0,r0,255<<24
	mov	r2,r4
	cmp	r0,1<<23
	mov	r1,r5
	ldrhi	r3,[r6,12]
	movhi	r0,0
	addls	r0,fp,1<<23
	strbls	r9,[r6,16]
	movls	r3,0
	strbhi	r0,[r6,16]
	movhi	r0,fp
	bicls	r0,r0,255<<24
.L5167:

	bl	Ocu_SetCompare
	and	r0,r9,r0
	cmp	r0,1
	bne	.L4896
	mov	r0,r4
.L5169:

	bl	Gtm_Ocu_Hal_GetCounterValue
	mov	r2,fp
	ldr	r1,[sp,4]
.L5171:

	bl	Ocu_GetReturnValue
	mov	r4,r0
.L5173:

	bl	SchM_Exit_Ocu_SetRelativeThreshold
	b	.L4882
.L4896:
	mov	r4,2
.L5175:

	bl	SchM_Exit_Ocu_SetRelativeThreshold
	mov	r3,228
	mov	r2,8
	mov	r1,0
	mov	r0,125
.L5177:

	bl	Det_ReportRuntimeError
.L4882:
	mov	r0,r4
.LDW27:
	add	sp,sp,12
.L5179:

	pop	{r4-fp,pc}
__ghs_eofn_Ocu_SetRelativeThreshold::
	.endf	Ocu_SetRelativeThreshold
;CoreId	r5	local
;ChanInCoreIndex	r8	local
;LocalChannelStatusPtr	r6	local
;CompareValue	fp	local
;ReferenceValue	[sp,4]	local
;ErrValue	r4	local
;Timebase	r4	local
;HWchannelObjectPtr	r5	local
;Ocu_RegRet	r9	local
;HWConfigIndex	r1	local

;ChannelNumber	r6	param
;RelativeValue	fp	param

	.section ".ghcalltbl",""
.L5158:	.data.w	.L5157
	.endo	.L5158
.L5160:	.data.w	.L5159
	.endo	.L5160
.L5162:	.data.w	.L5161
	.endo	.L5162
.L5164:	.data.w	.L5163
	.endo	.L5164
.L5166:	.data.w	.L5165
	.endo	.L5166
.L5168:	.data.w	.L5167
	.endo	.L5168
.L5170:	.data.w	.L5169
	.endo	.L5170
.L5172:	.data.w	.L5171
	.endo	.L5172
.L5174:	.data.w	.L5173
	.endo	.L5174
.L5176:	.data.w	.L5175
	.endo	.L5176
.L5178:	.data.w	.L5177
	.endo	.L5178
	.section ".ghrettbl",""
.L5180:	.data.w	.L5179
	.endo	.L5180
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Ocu_SetRelativeThreshold.v.v

	.global	__caller.SchM_Exit_Ocu_SetRelativeThreshold.v.v

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.Gtm_Ocu_Hal_GetCounterValue.i.i

	.global	__caller.SchM_Enter_Ocu_SetRelativeThreshold.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.47:
	.endo	..gh.f.a.1.e.47
__callee.Ocu_DisableNotification.v.i::
	.size	__callee.Ocu_DisableNotification.v.i,0
Ocu_DisableNotification::
.LDW37:
	push	{r2,r4-r5,lr}
.LDW47:
	b	.L5264

.L5155:	.data.w	Ocu_ConfigPtr
	.endo	.L5155

.L5156:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L5156

.L5264:

;line2334
..lin.3629a0af..2615bdc6.0_27::
.LDWlin27:
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
;line2341
..lin.3629a0af..2615bdc6.0_28::
.LDWlin28:
	mov	r5,r0
.L5267:

	bl	Ocu_DisableNotificationDetCheck
	cmp	r0,0
.L5269:

	popne	{r2,r4-r5,pc}
	ldr	r2,.L5265
	ldr	r2,[r2]
	ldr	r2,[r2,16]
	rsb	r1,r5,r5 lsl 2
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	add	r0,r1,r1 lsl 2
	ldr	r1,.L5266
	ldr	r4,[r1,r4 lsl 2]
	add	r4,r4,r0 lsl 2
.L5271:

	bl	SchM_Enter_Ocu_DisableNotification
	mov	r0,0
	strb	r0,[r4,4]
.L5273:

	bl	SchM_Exit_Ocu_DisableNotification
.LDW57:
.L5275:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Ocu_DisableNotification::
	.endf	Ocu_DisableNotification
;CoreId	r4	local
;LocalChannelStatusPtr	r4	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L5268:	.data.w	.L5267
	.endo	.L5268
	.section ".ghrettbl",""
.L5270:	.data.w	.L5269
	.endo	.L5270
	.section ".ghcalltbl",""
.L5272:	.data.w	.L5271
	.endo	.L5272
.L5274:	.data.w	.L5273
	.endo	.L5274
	.section ".ghrettbl",""
.L5276:	.data.w	.L5275
	.endo	.L5276
	.data
	.global	__caller.SchM_Exit_Ocu_DisableNotification.v.v

	.global	__caller.SchM_Enter_Ocu_DisableNotification.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.50:
	.endo	..gh.f.a.1.e.50
__callee.Ocu_EnableNotification.v.i::
	.size	__callee.Ocu_EnableNotification.v.i,0
Ocu_EnableNotification::
.LDW67:
	push	{r2,r4-r5,lr}
.LDW77:
	b	.L5360

.L5265:	.data.w	Ocu_ConfigPtr
	.endo	.L5265

.L5266:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L5266

.L5360:

;line2400
..lin.3629a0af..abf50479.0_29::
.LDWlin29:
..gh.beginasm.51:
	.endo	..gh.beginasm.51
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.52:
	.endo	..gh.endasm.52

	mov	r4,r2
;line2407
..lin.3629a0af..abf50479.0_30::
.LDWlin30:
	mov	r5,r0
.L5363:

	bl	Ocu_EnableNotificationDetCheck
	cmp	r0,0
.L5365:

	popne	{r2,r4-r5,pc}
	ldr	r2,.L5361
	ldr	r2,[r2]
	ldr	r2,[r2,16]
	rsb	r1,r5,r5 lsl 2
	add	r2,r2,r1 lsl 2
	ldrb	r1,[r2,4]
	add	r0,r1,r1 lsl 2
	ldr	r1,.L5362
	ldr	r4,[r1,r4 lsl 2]
	add	r4,r4,r0 lsl 2
.L5367:

	bl	SchM_Enter_Ocu_EnableNotification
	mov	r0,1
	strb	r0,[r4,4]
.L5369:

	bl	SchM_Exit_Ocu_EnableNotification
.LDW87:
.L5371:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Ocu_EnableNotification::
	.endf	Ocu_EnableNotification
;CoreId	r4	local
;LocalChannelStatusPtr	r4	local

;ChannelNumber	r5	param

	.section ".ghcalltbl",""
.L5364:	.data.w	.L5363
	.endo	.L5364
	.section ".ghrettbl",""
.L5366:	.data.w	.L5365
	.endo	.L5366
	.section ".ghcalltbl",""
.L5368:	.data.w	.L5367
	.endo	.L5368
.L5370:	.data.w	.L5369
	.endo	.L5370
	.section ".ghrettbl",""
.L5372:	.data.w	.L5371
	.endo	.L5372
	.data
	.global	__caller.SchM_Exit_Ocu_EnableNotification.v.v

	.global	__caller.SchM_Enter_Ocu_EnableNotification.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Ocu_ConfigPtr - Ocu_ConfigPtr) +0 == 0
..gh.f.a.1.e.53:
	.endo	..gh.f.a.1.e.53
__callee.Ocu_Gtm_Atom_CompareMatch_ISRHandler.v.ii::
	.size	__callee.Ocu_Gtm_Atom_CompareMatch_ISRHandler.v.ii,0
Ocu_Gtm_Atom_CompareMatch_ISRHandler::
.LDW97:
	push	{r4-r10,lr}
	mov	r2,r1
.LDW08:
	mov	r5,1
	b	.L5814

.L5361:	.data.w	Ocu_ConfigPtr
	.endo	.L5361

.L5362:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L5362

.L5814:

;line2469
..lin.3629a0af..72a9d481.0_31::
.LDWlin31:
..gh.beginasm.54:
	.endo	..gh.beginasm.54
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.55:
	.endo	..gh.endasm.55

;line2471
..lin.3629a0af..72a9d481.0_32::
.LDWlin32:
	ldr	r3,.L5815
	ldr	r1,[r3,r4 lsl 2]
	ldr	r1,[r1]
	cmp	r1,1
.L5818:

	popne	{r4-r10,pc}
	ldr	r9,.L5816
	ldr	r3,[r9]
	ldr	r1,[r3,24]
	add	r0,r2,r0 lsl 3
	uxtb	r0,r0
	ldrb	r0,[r1,r0]
	cmp	r0,255
.L5820:

	popeq	{r4-r10,pc}
	ldr	r1,[r3,16]
	rsb	r0,r0,r0 lsl 2
	lsl	r0,r0,2
	ldr	r2,[r1,r0]
	cmp	r4,r2
	beq	.L5383
	mov	r3,225
	mov	r2,224
	mov	r1,0
	mov	r0,125
.L5822:

	bl	Det_ReportError
.L5824:

	pop	{r4-r10,pc}
.L5383:
	add	r0,r0,r1
	ldr	r2,.L5817
	ldrb	r8,[r0,4]
	ldr	r1,[r2,r4 lsl 2]
	add	r0,r8,r8 lsl 2
	add	r6,r1,r0 lsl 2
	mov	r1,r8
	mov	r0,r4
.L5826:

	bl	Ocu_GetHardwareChannelObjectPtr
	mov	r7,r0
	mov	r1,3
.L5828:

	bl	Gtm_Ocu_Hal_GetInterruptEnableStatus
	mov	r10,r0
	mov	r0,r7
	mov	r1,3
.L5830:

	bl	Gtm_Ocu_Hal_GetInterruptStatus
	cmp	r10,0
.L5832:

	popeq	{r4-r10,pc}
	and	r0,r0,r10
	cmp	r10,r0
.L5834:

	popne	{r4-r10,pc}
	mov	r0,r7
	mov	r1,3
.L5836:

	bl	Gtm_Ocu_Hal_ClearInterruptStatus
	ldr	r0,[r6,8]
	cmp	r0,0
.L5838:

	popeq	{r4-r10,pc}
	ldr	r3,[r9]
	ldr	r0,[r3,r4 lsl 2]
	rsb	r2,r8,r8 lsl 2
	ldr	r0,[r0,4]
	lsl	r8,r2,3
	add	r12,r8,r0
	ldrb	r0,[r12]
	ldr	r1,[r3,16]
	rsb	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 2
	ldr	r0,[r0,8]
	cmp	r0,4
	ldrlo	r1,[r3,20]
	movlo	r2,44
	mlalo	r0,r2,r0,r1
	movhs	r2,255
	ldrlo	r2,[r0,40]
	ldrb	r1,[r6,16]
	ldr	r0,[r6]
	cmp	r1,1
	bne	.L5398
	mov	r1,0
	ldr	r3,[r6,12]
	strb	r1,[r6,16]
	mov	r1,r7
.L5840:

	bl	Ocu_SetCompare
	and	r5,r5,r0
	b	.L5400
.L5398:
	ldr	r1,[r12,12]
	strb	r5,[r6,16]
	cmp	r1,0
	streq	r1,[r6,12]
	add	r0,r0,1<<23
	mov	r1,r7
	mov	r3,0
	bic	r0,r0,255<<24
.L5842:

	bl	Ocu_SetCompare
	and	r5,r5,r0
	ldrb	r0,[r6,4]
	cmp	r0,1
	ldreq	r0,[r9]
	ldreq	r0,[r0,r4 lsl 2]
	ldreq	r0,[r0,4]
	addeq	r0,r8,r0
	ldreq	r0,[r0,8]
.L5844:

	blxeq	r0
.L5400:
	cmp	r5,1
	movne	r3,228
	movne	r2,224
	movne	r1,0
	movne	r0,125
.L5846:

	blne	Det_ReportRuntimeError
.LDW18:
.L5848:

	pop	{r4-r10,pc}
__ghs_eofn_Ocu_Gtm_Atom_CompareMatch_ISRHandler::
	.endf	Ocu_Gtm_Atom_CompareMatch_ISRHandler
;CoreId	r4	local
;ChanInCoreIndex	r8	local
;IntStatus	r0	local
;IntEnStatus	r10	local
;LocalChannelStatusPtr	r6	local
;AbsoluteValue	r0	local
;HWchannelObjectPtr	r7	local
;Timebase	r2	local
;Ocu_RegRet	r5	local
;LogicChannel	r0	local
;HWConfigIndex	r0	local

;ModuleIndex	r0	param
;Channel	r2	param

	.section ".ghrettbl",""
.L5819:	.data.w	.L5818
	.endo	.L5819
.L5821:	.data.w	.L5820
	.endo	.L5821
	.section ".ghcalltbl",""
.L5823:	.data.w	.L5822
	.endo	.L5823
	.section ".ghrettbl",""
.L5825:	.data.w	.L5824
	.endo	.L5825
	.section ".ghcalltbl",""
.L5827:	.data.w	.L5826
	.endo	.L5827
.L5829:	.data.w	.L5828
	.endo	.L5829
.L5831:	.data.w	.L5830
	.endo	.L5831
	.section ".ghrettbl",""
.L5833:	.data.w	.L5832
	.endo	.L5833
.L5835:	.data.w	.L5834
	.endo	.L5835
	.section ".ghcalltbl",""
.L5837:	.data.w	.L5836
	.endo	.L5837
	.section ".ghrettbl",""
.L5839:	.data.w	.L5838
	.endo	.L5839
	.section ".ghcalltbl",""
.L5841:	.data.w	.L5840
	.endo	.L5841
.L5843:	.data.w	.L5842
	.endo	.L5843
.L5845:	.data.w	.L5844
	.endo	.L5845
.L5847:	.data.w	.L5846
	.endo	.L5847
	.section ".ghrettbl",""
.L5849:	.data.w	.L5848
	.endo	.L5849
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Gtm_Ocu_Hal_ClearInterruptStatus.v.pi

	.global	__caller.Gtm_Ocu_Hal_GetInterruptStatus.i.pi

	.global	__caller.Gtm_Ocu_Hal_GetInterruptEnableStatus.i.pi

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"

.L5815:	.data.w	Ocu_CoreDriverStatusPtr
	.endo	.L5815

.L5816:	.data.w	Ocu_ConfigPtr
	.endo	.L5816

.L5817:	.data.w	Ocu_CoreChannelStatusPtr
	.endo	.L5817

;Ocu_ChannelStatusCore0	Ocu_ChannelStatusCore0	static
;Ocu_DriverStatusCore0	Ocu_DriverStatusCore0	static
;Ocu_ChannelStatusCore1	Ocu_ChannelStatusCore1	static
;Ocu_DriverStatusCore1	Ocu_DriverStatusCore1	static
;Ocu_CoreChannelStatusPtr	Ocu_CoreChannelStatusPtr	static
;Ocu_CoreDriverStatusPtr	Ocu_CoreDriverStatusPtr	static
;Ocu_ConfigPtr	Ocu_ConfigPtr	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682574..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	243,30,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,79,99,117,92,115,114,99,47,79,99,117,46,99,0
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
	.data.b	21,14,0,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,79,99,117,92,115,114,99,47,79,99,117,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,79,99,117,92,105,110,99,108,117,100,101,92,79,99,117,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,79,99,117,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,79,99,117,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,79,99,117,92,105,110,99,108,117,100,101,92,79,99,117,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,71,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,111,99,117,92,103,116,109,95,111,99,117,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,97,116,111,109,92,103,116,109,95,97,116,111,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,116,98,117,92,103,116,109,95,116,98,117,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,79,99,117,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,79,99,117,92,105,110,99,108,117,100,101,92,79,99,117,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,68,101,116,92,105,110,99,108,117,100,101,92,68,101,116,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,79,99,117,46,104,0
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
	.data.w	.Ldw_begin+1293
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
	.data.w	.Ldw_begin+2072
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1305
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
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1305
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2981

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
	.data.w	.Ldw_begin+3197

	.data.b	53
	.data.w	.Ldw_begin+117

	.data.b	47
	.data.w	.Ldw_begin+122

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+127
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1305
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1305
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2858

	.data.b	53
	.data.w	.Ldw_begin+234

	.data.b	47
	.data.w	.Ldw_begin+1102

	.data.b	74
	.data.w	.Ldw_begin+2599
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+244
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+244
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+244
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1672

	.data.b	53
	.data.w	.Ldw_begin+274

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1102
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+279
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2072
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2549
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2858

	.data.b	47
	.data.w	.Ldw_begin+315

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+320
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+279
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2072
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+279
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1305
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1225

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 62
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 376
	.data.b	23
	.data.w	.Ldw_begin+369
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+122
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2408
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2549
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2396
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2599
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2599
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2396
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2384
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 534
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	105,110,116,0
	.section	.debug_info		;off: 541
	.data.w	.Ldw_str_begin+260
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 264
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 548
	.data.w	.Ldw_str_begin+264
	.data.b	7
	.data.b	4

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+554

	.data.b	47
	.data.w	.Ldw_begin+3108

	.data.b	53
	.data.w	.Ldw_begin+562

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+567

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 579
	.data.b	56
	.data.w	.Ldw_begin+540
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

	.section	.debug_info		;off: 587
	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+3053

	.data.b	53
	.data.w	.Ldw_begin+588

	.data.b	47
	.data.w	.Ldw_begin+2752

	.data.b	53
	.data.w	.Ldw_begin+598

	.data.b	47
	.data.w	.Ldw_begin+1078

	.data.b	53
	.data.w	.Ldw_begin+608

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+2858

	.data.b	56
	.data.w	.Ldw_begin+540
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+2858

	.data.b	56
	.data.w	.Ldw_begin+540
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+320

	.data.b	56
	.data.w	.Ldw_begin+540
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2449

	.data.b	47
	.data.w	.Ldw_begin+666

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+671

	.data.b	56
	.data.w	.Ldw_begin+540
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1409
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1409
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+279

	.data.b	47
	.data.w	.Ldw_begin+2372

	.data.b	53
	.data.w	.Ldw_begin+719

	.data.b	47
	.data.w	.Ldw_begin+724

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+729
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1066
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1066
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1518
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+2241

	.data.b	53
	.data.w	.Ldw_begin+816

	.data.b	47
	.data.w	.Ldw_begin+821

	.data.b	47
	.data.w	.Ldw_begin+2190

	.data.b	53
	.data.w	.Ldw_begin+831

	.data.b	47
	.data.w	.Ldw_begin+836

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+826
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+841
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1066
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1066
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1066
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1102
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2072
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1102
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1967
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1102
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1967
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+714
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1967
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1090
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1126
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1090
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1078
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

	.data.b	45
	.section	.debug_str		;off: 277
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1067
	.data.w	.Ldw_str_begin+277
	.data.b	51
	.data.b	29
	.data.b	11
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

	.section	.debug_info		;off: 1078
	.data.b	45
	.section	.debug_str		;off: 285
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1079
	.data.w	.Ldw_str_begin+285
	.data.b	56
	.data.b	29
	.data.b	11
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 291
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1091
	.data.w	.Ldw_str_begin+291
	.data.b	60
	.data.b	29
	.data.b	11
	.data.w	.Ldw_begin+533

	.data.b	45
	.section	.debug_str		;off: 298
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1103
	.data.w	.Ldw_str_begin+298
	.data.b	64
	.data.b	29
	.data.b	11
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 305
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1115
	.data.w	.Ldw_str_begin+305
	.data.b	68
	.data.b	29
	.data.b	11
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1127
	.data.w	.Ldw_str_begin+312
	.data.b	39
	.data.b	15
	.data.b	6
	.data.w	.Ldw_begin+1078

	.data.b	71
	.data.b	62
	.data.b	1
	.data.b	6
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

	.section	.debug_info		;off: 1144
	.data.b	40
	.section	.debug_str		;off: 327
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1145
	.data.w	.Ldw_str_begin+327
	.data.b	63
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1090
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

	.section	.debug_info		;off: 1160
	.data.b	40
	.section	.debug_str		;off: 336
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1161
	.data.w	.Ldw_str_begin+336
	.data.b	64
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1090
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 345
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1177
	.data.w	.Ldw_str_begin+345
	.data.b	65
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 362
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1193
	.data.w	.Ldw_str_begin+362
	.data.b	66
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 379
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1209
	.data.w	.Ldw_str_begin+379
	.data.b	67
	.data.b	13
	.data.b	6
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 396
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1226
	.data.w	.Ldw_str_begin+396
	.data.b	68
	.data.b	2
	.data.b	6
	.data.w	.Ldw_begin+1138

	.data.b	52
	.section	.debug_str		;off: 416
	.data.b	0
	.section	.debug_info		;off: 1238
	.data.w	.Ldw_str_begin+416
	.data.b	36
	.data.b	1
	.data.b	15
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

	.section	.debug_info		;off: 1247
	.data.b	51
	.section	.debug_str		;off: 417
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 1248
	.data.w	.Ldw_str_begin+417
	.data.b	37
	.data.b	5
	.data.b	15
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

	.section	.debug_info		;off: 1256
	.data.b	51
	.section	.debug_str		;off: 434
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 1257
	.data.w	.Ldw_str_begin+434
	.data.b	38
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 451
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 1266
	.data.w	.Ldw_str_begin+451
	.data.b	39
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 468
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 1275
	.data.w	.Ldw_str_begin+468
	.data.b	40
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 485
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 1284
	.data.w	.Ldw_str_begin+485
	.data.b	41
	.data.b	5
	.data.b	15
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 502
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1294
	.data.w	.Ldw_str_begin+502
	.data.b	42
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+1237

	.data.b	45
	.section	.debug_str		;off: 514
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 1306
	.data.w	.Ldw_str_begin+514
	.data.b	32
	.data.b	21
	.data.b	14
	.data.w	.Ldw_begin+1293

	.data.b	52
	.section	.debug_str		;off: 528
	.data.b	0
	.section	.debug_info		;off: 1318
	.data.w	.Ldw_str_begin+528
	.data.b	39
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 529
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 1328
	.data.w	.Ldw_str_begin+529
	.data.b	41
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 547
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 1337
	.data.w	.Ldw_str_begin+547
	.data.b	43
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 564
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 1346
	.data.w	.Ldw_str_begin+564
	.data.b	45
	.data.b	5
	.data.b	14
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 582
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 1355
	.data.w	.Ldw_str_begin+582
	.data.b	47
	.data.b	5
	.data.b	14
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 599
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 1364
	.data.w	.Ldw_str_begin+599
	.data.b	49
	.data.b	5
	.data.b	14
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 616
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 1373
	.data.w	.Ldw_str_begin+616
	.data.b	51
	.data.b	5
	.data.b	14
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 633
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 1382
	.data.w	.Ldw_str_begin+633
	.data.b	53
	.data.b	5
	.data.b	14
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 650
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 1391
	.data.w	.Ldw_str_begin+650
	.data.b	55
	.data.b	5
	.data.b	14
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 667
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 1400
	.data.w	.Ldw_str_begin+667
	.data.b	57
	.data.b	5
	.data.b	14
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 684
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 1410
	.data.w	.Ldw_str_begin+684
	.data.b	58
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+1317

	.data.b	52
	.section	.debug_str		;off: 700
	.data.b	0
	.section	.debug_info		;off: 1422
	.data.w	.Ldw_str_begin+700
	.data.b	150,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 701
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,76,69,86,69,76,0
	.section	.debug_info		;off: 1433
	.data.w	.Ldw_str_begin+701
	.data.b	151,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 719
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,0
	.section	.debug_info		;off: 1443
	.data.w	.Ldw_str_begin+719
	.data.b	152,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 737
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,78,79,84,73,70,89,0
	.section	.debug_info		;off: 1453
	.data.w	.Ldw_str_begin+737
	.data.b	153,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 761
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,83,73,78,71,76,69,80,85,76,83,69,0
	.section	.debug_info		;off: 1463
	.data.w	.Ldw_str_begin+761
	.data.b	154,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 785
	.data.b	71,116,109,95,73,114,113,77,111,100,101,0
	.section	.debug_info		;off: 1474
	.data.w	.Ldw_str_begin+785
	.data.b	155,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+1421

	.data.b	52
	.section	.debug_str		;off: 797
	.data.b	0
	.section	.debug_info		;off: 1487
	.data.w	.Ldw_str_begin+797
	.data.b	159,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 798
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,76,79,87,0
	.section	.debug_info		;off: 1498
	.data.w	.Ldw_str_begin+798
	.data.b	160,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 818
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,72,73,71,72,0
	.section	.debug_info		;off: 1508
	.data.w	.Ldw_str_begin+818
	.data.b	161,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 839
	.data.b	71,116,109,95,83,105,103,110,97,108,83,116,97,116,101,0
	.section	.debug_info		;off: 1519
	.data.w	.Ldw_str_begin+839
	.data.b	162,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+1486

	.data.b	52
	.section	.debug_str		;off: 855
	.data.b	0
	.section	.debug_info		;off: 1532
	.data.w	.Ldw_str_begin+855
	.data.b	166,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 856
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1543
	.data.w	.Ldw_str_begin+856
	.data.b	167,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 876
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,48,0
	.section	.debug_info		;off: 1553
	.data.w	.Ldw_str_begin+876
	.data.b	168,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 896
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,49,0
	.section	.debug_info		;off: 1563
	.data.w	.Ldw_str_begin+896
	.data.b	169,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 916
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,65,76,76,0
	.section	.debug_info		;off: 1573
	.data.w	.Ldw_str_begin+916
	.data.b	170,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 935
	.data.b	71,116,109,95,79,109,95,73,114,113,84,121,112,101,0
	.section	.debug_info		;off: 1584
	.data.w	.Ldw_str_begin+935
	.data.b	171,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+1531

	.data.b	71
	.data.b	185,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 950
	.data.b	109,111,100,117,108,101,0
	.section	.debug_info		;off: 1604
	.data.w	.Ldw_str_begin+950
	.data.b	186,1
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 957
	.data.b	109,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 1621
	.data.w	.Ldw_str_begin+957
	.data.b	187,1
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 969
	.data.b	103,114,111,117,112,0
	.section	.debug_info		;off: 1638
	.data.w	.Ldw_str_begin+969
	.data.b	188,1
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 975
	.data.b	99,104,97,110,110,101,108,0
	.section	.debug_info		;off: 1655
	.data.w	.Ldw_str_begin+975
	.data.b	189,1
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 983
	.data.b	71,116,109,95,79,117,116,112,117,116,95,68,114,105,118,101,114,0
	.section	.debug_info		;off: 1673
	.data.w	.Ldw_str_begin+983
	.data.b	190,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+1596

	.data.b	52
	.section	.debug_str		;off: 1001
	.data.b	0
	.section	.debug_info		;off: 1686
	.data.w	.Ldw_str_begin+1001
	.data.b	93
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1002
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,77,80,66,79,84,72,0
	.section	.debug_info		;off: 1696
	.data.w	.Ldw_str_begin+1002
	.data.b	94
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1023
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,77,80,66,79,84,72,49,0
	.section	.debug_info		;off: 1705
	.data.w	.Ldw_str_begin+1023
	.data.b	96
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1045
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,67,85,48,84,83,48,0
	.section	.debug_info		;off: 1714
	.data.w	.Ldw_str_begin+1045
	.data.b	98
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1066
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,67,85,49,84,83,49,50,0
	.section	.debug_info		;off: 1723
	.data.w	.Ldw_str_begin+1066
	.data.b	99
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1088
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,67,85,48,49,84,83,48,0
	.section	.debug_info		;off: 1732
	.data.w	.Ldw_str_begin+1088
	.data.b	100
	.data.b	5
	.data.b	38
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1110
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,67,85,48,49,84,83,49,50,0
	.section	.debug_info		;off: 1741
	.data.w	.Ldw_str_begin+1110
	.data.b	101
	.data.b	5
	.data.b	38
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 1133
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,67,85,48,84,83,48,67,67,85,49,84,83,49,50,0
	.section	.debug_info		;off: 1750
	.data.w	.Ldw_str_begin+1133
	.data.b	102
	.data.b	5
	.data.b	38
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 1162
	.data.b	71,84,77,95,83,79,77,67,67,84,82,76,95,67,78,65,67,69,76,67,79,77,80,65,82,69,0
	.section	.debug_info		;off: 1759
	.data.w	.Ldw_str_begin+1162
	.data.b	103
	.data.b	5
	.data.b	38
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1189
	.data.b	71,116,109,95,83,111,109,99,67,116,114,108,0
	.section	.debug_info		;off: 1769
	.data.w	.Ldw_str_begin+1189
	.data.b	104
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1685

	.data.b	52
	.section	.debug_str		;off: 1202
	.data.b	0
	.section	.debug_info		;off: 1781
	.data.w	.Ldw_str_begin+1202
	.data.b	118
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1203
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,48,0
	.section	.debug_info		;off: 1791
	.data.w	.Ldw_str_begin+1203
	.data.b	119
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1230
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,49,0
	.section	.debug_info		;off: 1800
	.data.w	.Ldw_str_begin+1230
	.data.b	120
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1257
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,50,0
	.section	.debug_info		;off: 1809
	.data.w	.Ldw_str_begin+1257
	.data.b	121
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1284
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,51,0
	.section	.debug_info		;off: 1818
	.data.w	.Ldw_str_begin+1284
	.data.b	122
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1311
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,52,0
	.section	.debug_info		;off: 1827
	.data.w	.Ldw_str_begin+1311
	.data.b	123
	.data.b	5
	.data.b	38
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1338
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,53,0
	.section	.debug_info		;off: 1836
	.data.w	.Ldw_str_begin+1338
	.data.b	124
	.data.b	5
	.data.b	38
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 1365
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,54,0
	.section	.debug_info		;off: 1845
	.data.w	.Ldw_str_begin+1365
	.data.b	125
	.data.b	5
	.data.b	38
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 1392
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,67,77,85,67,76,75,55,0
	.section	.debug_info		;off: 1854
	.data.w	.Ldw_str_begin+1392
	.data.b	126
	.data.b	5
	.data.b	38
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 1419
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,78,79,67,76,79,67,75,0
	.section	.debug_info		;off: 1863
	.data.w	.Ldw_str_begin+1419
	.data.b	127
	.data.b	5
	.data.b	38
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 1446
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,83,84,79,80,0
	.section	.debug_info		;off: 1872
	.data.w	.Ldw_str_begin+1446
	.data.b	128,1
	.data.b	5
	.data.b	38
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1470
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,84,82,73,71,79,85,84,0
	.section	.debug_info		;off: 1882
	.data.w	.Ldw_str_begin+1470
	.data.b	129,1
	.data.b	5
	.data.b	38
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 1497
	.data.b	71,84,77,95,65,84,79,77,95,67,72,95,67,76,75,83,82,67,95,69,88,84,84,82,73,71,73,78,0
	.section	.debug_info		;off: 1892
	.data.w	.Ldw_str_begin+1497
	.data.b	130,1
	.data.b	5
	.data.b	38
	.data.b	14

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1526
	.data.b	71,116,109,95,65,116,111,109,95,67,104,95,67,108,107,83,114,99,0
	.section	.debug_info		;off: 1903
	.data.w	.Ldw_str_begin+1526
	.data.b	131,1
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1780

	.data.b	52
	.section	.debug_str		;off: 1545
	.data.b	0
	.section	.debug_info		;off: 1916
	.data.w	.Ldw_str_begin+1545
	.data.b	135,1
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1546
	.data.b	71,84,77,95,65,84,79,77,95,73,82,81,84,89,80,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1927
	.data.w	.Ldw_str_begin+1546
	.data.b	136,1
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1568
	.data.b	71,84,77,95,65,84,79,77,95,73,82,81,84,89,80,69,95,67,67,85,48,0
	.section	.debug_info		;off: 1937
	.data.w	.Ldw_str_begin+1568
	.data.b	137,1
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1590
	.data.b	71,84,77,95,65,84,79,77,95,73,82,81,84,89,80,69,95,67,67,85,49,0
	.section	.debug_info		;off: 1947
	.data.w	.Ldw_str_begin+1590
	.data.b	138,1
	.data.b	5
	.data.b	38
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1612
	.data.b	71,84,77,95,65,84,79,77,95,73,82,81,84,89,80,69,95,65,76,76,0
	.section	.debug_info		;off: 1957
	.data.w	.Ldw_str_begin+1612
	.data.b	139,1
	.data.b	5
	.data.b	38
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1633
	.data.b	71,116,109,95,65,116,111,109,95,73,114,113,84,121,112,101,0
	.section	.debug_info		;off: 1968
	.data.w	.Ldw_str_begin+1633
	.data.b	140,1
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1915

	.data.b	52
	.section	.debug_str		;off: 1650
	.data.b	0
	.section	.debug_info		;off: 1981
	.data.w	.Ldw_str_begin+1650
	.data.b	144,1
	.data.b	1
	.data.b	38
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1651
	.data.b	71,84,77,95,65,84,79,77,95,84,73,77,69,66,65,83,69,95,84,83,49,0
	.section	.debug_info		;off: 1992
	.data.w	.Ldw_str_begin+1651
	.data.b	145,1
	.data.b	5
	.data.b	38
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1673
	.data.b	71,84,77,95,65,84,79,77,95,84,73,77,69,66,65,83,69,95,84,83,50,0
	.section	.debug_info		;off: 2002
	.data.w	.Ldw_str_begin+1673
	.data.b	146,1
	.data.b	5
	.data.b	38
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1695
	.data.b	71,116,109,95,65,116,111,109,95,84,105,109,101,66,97,115,101,0
	.section	.debug_info		;off: 2013
	.data.w	.Ldw_str_begin+1695
	.data.b	147,1
	.data.b	3
	.data.b	38
	.data.w	.Ldw_begin+1980

	.data.b	52
	.section	.debug_str		;off: 1713
	.data.b	0
	.section	.debug_info		;off: 2026
	.data.w	.Ldw_str_begin+1713
	.data.b	53
	.data.b	1
	.data.b	39
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1714
	.data.b	71,84,77,95,84,66,85,95,67,72,95,84,83,48,0
	.section	.debug_info		;off: 2036
	.data.w	.Ldw_str_begin+1714
	.data.b	54
	.data.b	5
	.data.b	39
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1729
	.data.b	71,84,77,95,84,66,85,95,67,72,95,84,83,49,0
	.section	.debug_info		;off: 2045
	.data.w	.Ldw_str_begin+1729
	.data.b	55
	.data.b	5
	.data.b	39
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1744
	.data.b	71,84,77,95,84,66,85,95,67,72,95,84,83,50,0
	.section	.debug_info		;off: 2054
	.data.w	.Ldw_str_begin+1744
	.data.b	56
	.data.b	5
	.data.b	39
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1759
	.data.b	71,84,77,95,84,66,85,95,67,72,95,84,83,51,0
	.section	.debug_info		;off: 2063
	.data.w	.Ldw_str_begin+1759
	.data.b	57
	.data.b	5
	.data.b	39
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1774
	.data.b	71,116,109,95,84,98,117,95,67,104,0
	.section	.debug_info		;off: 2073
	.data.w	.Ldw_str_begin+1774
	.data.b	58
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+2025

	.data.b	71
	.data.b	67
	.data.b	1
	.data.b	37
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1785
	.data.b	105,115,67,99,117,48,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 2091
	.data.w	.Ldw_str_begin+1785
	.data.b	68
	.data.b	21
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1799
	.data.b	105,115,67,99,117,49,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 2107
	.data.w	.Ldw_str_begin+1799
	.data.b	69
	.data.b	21
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1813
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 2123
	.data.w	.Ldw_str_begin+1813
	.data.b	70
	.data.b	21
	.data.b	37
	.data.w	.Ldw_begin+1473
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1818
	.data.b	71,116,109,95,79,99,117,95,67,111,110,102,105,103,73,114,113,0
	.section	.debug_info		;off: 2140
	.data.w	.Ldw_str_begin+1818
	.data.b	71
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+2084

	.data.b	71
	.data.b	76
	.data.b	1
	.data.b	37
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1836
	.data.b	115,111,109,99,83,105,103,110,97,108,76,101,118,101,108,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 2158
	.data.w	.Ldw_str_begin+1836
	.data.b	77
	.data.b	26
	.data.b	37
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1859
	.data.b	115,111,109,99,67,111,109,112,97,114,101,83,116,114,97,116,101,103,121,0
	.section	.debug_info		;off: 2174
	.data.w	.Ldw_str_begin+1859
	.data.b	79
	.data.b	26
	.data.b	37
	.data.w	.Ldw_begin+1768
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1879
	.data.b	71,116,109,95,79,99,117,95,79,117,116,112,117,116,95,66,101,104,97,118,105,111,114,0
	.section	.debug_info		;off: 2191
	.data.w	.Ldw_str_begin+1879
	.data.b	80
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+2151

	.data.b	71
	.data.b	86
	.data.b	1
	.data.b	37
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1903
	.data.b	99,109,48,0
	.section	.debug_info		;off: 2209
	.data.w	.Ldw_str_begin+1903
	.data.b	87
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1907
	.data.b	99,109,49,0
	.section	.debug_info		;off: 2225
	.data.w	.Ldw_str_begin+1907
	.data.b	88
	.data.b	12
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1911
	.data.b	71,116,109,95,79,99,117,95,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 2242
	.data.w	.Ldw_str_begin+1911
	.data.b	89
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+2202

	.data.b	71
	.data.b	94
	.data.b	1
	.data.b	37
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1927
	.data.b	99,108,107,0
	.section	.debug_info		;off: 2260
	.data.w	.Ldw_str_begin+1927
	.data.b	95
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+1902
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1931
	.data.b	116,105,109,101,66,97,115,101,0
	.section	.debug_info		;off: 2276
	.data.w	.Ldw_str_begin+1931
	.data.b	96
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+2012
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1940
	.data.b	115,105,103,110,97,108,76,101,118,101,108,0
	.section	.debug_info		;off: 2292
	.data.w	.Ldw_str_begin+1940
	.data.b	97
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+1518
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1952
	.data.b	115,111,109,99,67,116,114,108,0
	.section	.debug_info		;off: 2308
	.data.w	.Ldw_str_begin+1952
	.data.b	98
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+2190
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1961
	.data.b	105,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 2324
	.data.w	.Ldw_str_begin+1961
	.data.b	99
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+2139
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1971
	.data.b	99,111,109,112,97,114,101,86,97,108,117,101,48,0
	.section	.debug_info		;off: 2340
	.data.w	.Ldw_str_begin+1971
	.data.b	100
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 1985
	.data.b	99,111,109,112,97,114,101,86,97,108,117,101,49,0
	.section	.debug_info		;off: 2356
	.data.w	.Ldw_str_begin+1985
	.data.b	101
	.data.b	33
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1999
	.data.b	71,116,109,95,79,99,117,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2373
	.data.w	.Ldw_str_begin+1999
	.data.b	102
	.data.b	3
	.data.b	37
	.data.w	.Ldw_begin+2253

	.data.b	45
	.section	.debug_str		;off: 2014
	.data.b	79,99,117,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 2385
	.data.w	.Ldw_str_begin+2014
	.data.b	63
	.data.b	16
	.data.b	5
	.data.w	.Ldw_begin+1102

	.data.b	45
	.section	.debug_str		;off: 2030
	.data.b	79,99,117,95,86,97,108,117,101,84,121,112,101,0
	.section	.debug_info		;off: 2397
	.data.w	.Ldw_str_begin+2030
	.data.b	66
	.data.b	16
	.data.b	5
	.data.w	.Ldw_begin+1102

	.data.b	45
	.section	.debug_str		;off: 2044
	.data.b	79,99,117,95,80,105,110,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 2409
	.data.w	.Ldw_str_begin+2044
	.data.b	69
	.data.b	25
	.data.b	5
	.data.w	.Ldw_begin+1518

	.data.b	52
	.section	.debug_str		;off: 2061
	.data.b	0
	.section	.debug_info		;off: 2421
	.data.w	.Ldw_str_begin+2061
	.data.b	75
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2062
	.data.b	79,67,85,95,85,78,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 2431
	.data.w	.Ldw_str_begin+2062
	.data.b	76
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2080
	.data.b	79,67,85,95,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 2440
	.data.w	.Ldw_str_begin+2080
	.data.b	77
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2096
	.data.b	79,99,117,95,73,110,105,116,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 2450
	.data.w	.Ldw_str_begin+2096
	.data.b	78
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2420

	.data.b	52
	.section	.debug_str		;off: 2114
	.data.b	0
	.section	.debug_info		;off: 2462
	.data.w	.Ldw_str_begin+2114
	.data.b	81
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2115
	.data.b	79,67,85,95,67,72,65,78,78,69,76,95,83,84,79,80,80,69,68,0
	.section	.debug_info		;off: 2472
	.data.w	.Ldw_str_begin+2115
	.data.b	82
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2135
	.data.b	79,67,85,95,67,72,65,78,78,69,76,95,82,85,78,78,73,78,71,0
	.section	.debug_info		;off: 2481
	.data.w	.Ldw_str_begin+2135
	.data.b	83
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2155
	.data.b	79,99,117,95,67,104,97,110,110,101,108,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 2491
	.data.w	.Ldw_str_begin+2155
	.data.b	84
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2461

	.data.b	52
	.section	.debug_str		;off: 2176
	.data.b	0
	.section	.debug_info		;off: 2503
	.data.w	.Ldw_str_begin+2176
	.data.b	89
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2177
	.data.b	79,67,85,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 2513
	.data.w	.Ldw_str_begin+2177
	.data.b	91
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2189
	.data.b	79,67,85,95,83,69,84,95,72,73,71,72,0
	.section	.debug_info		;off: 2522
	.data.w	.Ldw_str_begin+2189
	.data.b	93
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2202
	.data.b	79,67,85,95,83,69,84,95,76,79,87,0
	.section	.debug_info		;off: 2531
	.data.w	.Ldw_str_begin+2202
	.data.b	95
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2214
	.data.b	79,67,85,95,84,79,71,71,76,69,0
	.section	.debug_info		;off: 2540
	.data.w	.Ldw_str_begin+2214
	.data.b	97
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2225
	.data.b	79,99,117,95,80,105,110,65,99,116,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 2550
	.data.w	.Ldw_str_begin+2225
	.data.b	98
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2502

	.data.b	52
	.section	.debug_str		;off: 2243
	.data.b	0
	.section	.debug_info		;off: 2562
	.data.w	.Ldw_str_begin+2243
	.data.b	103
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2244
	.data.b	79,67,85,95,67,77,95,79,85,84,95,82,69,70,95,73,78,84,69,82,86,65,76,0
	.section	.debug_info		;off: 2572
	.data.w	.Ldw_str_begin+2244
	.data.b	105
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2268
	.data.b	79,67,85,95,67,77,95,73,78,95,82,69,70,95,73,78,84,69,82,86,65,76,0
	.section	.debug_info		;off: 2581
	.data.w	.Ldw_str_begin+2268
	.data.b	107
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2291
	.data.b	79,67,85,95,67,77,95,82,69,70,95,69,82,82,79,82,0
	.section	.debug_info		;off: 2590
	.data.w	.Ldw_str_begin+2291
	.data.b	109
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2308
	.data.b	79,99,117,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 2600
	.data.w	.Ldw_str_begin+2308
	.data.b	110
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2561

	.data.b	52
	.section	.debug_str		;off: 2323
	.data.b	0
	.section	.debug_info		;off: 2612
	.data.w	.Ldw_str_begin+2323
	.data.b	114
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2324
	.data.b	79,67,85,95,67,79,77,80,65,82,69,95,69,86,69,78,84,95,80,73,78,0
	.section	.debug_info		;off: 2622
	.data.w	.Ldw_str_begin+2324
	.data.b	116
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2346
	.data.b	79,67,85,95,67,79,77,80,65,82,69,95,69,86,69,78,84,95,65,68,67,0
	.section	.debug_info		;off: 2631
	.data.w	.Ldw_str_begin+2346
	.data.b	118
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2368
	.data.b	79,67,85,95,67,79,77,80,65,82,69,95,69,86,69,78,84,95,68,77,65,0
	.section	.debug_info		;off: 2640
	.data.w	.Ldw_str_begin+2368
	.data.b	120
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2390
	.data.b	79,99,117,95,67,111,109,112,97,114,101,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 2650
	.data.w	.Ldw_str_begin+2390
	.data.b	121
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2611

	.data.b	52
	.section	.debug_str		;off: 2411
	.data.b	0
	.section	.debug_info		;off: 2662
	.data.w	.Ldw_str_begin+2411
	.data.b	125
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2412
	.data.b	79,67,85,95,72,87,95,71,84,77,95,65,84,79,77,0
	.section	.debug_info		;off: 2672
	.data.w	.Ldw_str_begin+2412
	.data.b	126
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2428
	.data.b	79,99,117,95,72,87,84,121,112,101,0
	.section	.debug_info		;off: 2682
	.data.w	.Ldw_str_begin+2428
	.data.b	127
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2661

	.data.b	71
	.data.b	138,1
	.data.b	1
	.data.b	5
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2439
	.data.b	72,87,67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 2701
	.data.w	.Ldw_str_begin+2439
	.data.b	140,1
	.data.b	30
	.data.b	5
	.data.w	.Ldw_begin+1672
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2454
	.data.b	72,87,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2718
	.data.w	.Ldw_str_begin+2454
	.data.b	142,1
	.data.b	30
	.data.b	5
	.data.w	.Ldw_begin+2372
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2470
	.data.b	84,105,109,101,66,97,115,101,0
	.section	.debug_info		;off: 2735
	.data.w	.Ldw_str_begin+2470
	.data.b	144,1
	.data.b	30
	.data.b	5
	.data.w	.Ldw_begin+2072
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2479
	.data.b	79,99,117,95,72,87,71,116,109,65,116,111,109,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 2753
	.data.w	.Ldw_str_begin+2479
	.data.b	145,1
	.data.b	2
	.data.b	5
	.data.w	.Ldw_begin+2693

	.data.b	71
	.data.b	148,1
	.data.b	1
	.data.b	5
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2503
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2773
	.data.w	.Ldw_str_begin+2503
	.data.b	150,1
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2396
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2516
	.data.b	78,111,116,105,102,121,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 2790
	.data.w	.Ldw_str_begin+2516
	.data.b	152,1
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+1066
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2530
	.data.b	67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 2807
	.data.w	.Ldw_str_begin+2530
	.data.b	154,1
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2490
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2544
	.data.b	79,117,116,112,117,116,65,99,116,105,111,110,0
	.section	.debug_info		;off: 2824
	.data.w	.Ldw_str_begin+2544
	.data.b	156,1
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2549
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2557
	.data.b	65,116,111,109,82,101,80,114,111,103,0
	.section	.debug_info		;off: 2841
	.data.w	.Ldw_str_begin+2557
	.data.b	158,1
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+1066
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2568
	.data.b	79,99,117,95,67,104,97,110,110,101,108,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 2859
	.data.w	.Ldw_str_begin+2568
	.data.b	159,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2765

	.data.b	71
	.data.b	164,1
	.data.b	1
	.data.b	5
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2590
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 2879
	.data.w	.Ldw_str_begin+2590
	.data.b	166,1
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2600
	.data.b	77,97,120,67,111,117,110,116,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 2896
	.data.w	.Ldw_str_begin+2600
	.data.b	168,1
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2616
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 2913
	.data.w	.Ldw_str_begin+2616
	.data.b	170,1
	.data.b	28
	.data.b	5
	.data.w	.Ldw_begin+557
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2632
	.data.b	69,118,101,110,116,0
	.section	.debug_info		;off: 2930
	.data.w	.Ldw_str_begin+2632
	.data.b	172,1
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+2649
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2638
	.data.b	68,101,102,97,117,108,116,67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 2947
	.data.w	.Ldw_str_begin+2638
	.data.b	174,1
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2658
	.data.b	72,87,67,108,97,115,115,0
	.section	.debug_info		;off: 2964
	.data.w	.Ldw_str_begin+2658
	.data.b	176,1
	.data.b	27
	.data.b	5
	.data.w	.Ldw_begin+2681
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2666
	.data.b	79,99,117,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 2982
	.data.w	.Ldw_str_begin+2666
	.data.b	177,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2871

	.data.b	71
	.data.b	182,1
	.data.b	1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2683
	.data.b	67,111,114,101,0
	.section	.debug_info		;off: 3002
	.data.w	.Ldw_str_begin+2683
	.data.b	184,1
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+1305
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2688
	.data.b	73,110,100,101,120,73,110,67,111,114,101,0
	.section	.debug_info		;off: 3019
	.data.w	.Ldw_str_begin+2688
	.data.b	186,1
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2700
	.data.b	72,87,67,102,103,73,110,100,101,120,0
	.section	.debug_info		;off: 3036
	.data.w	.Ldw_str_begin+2700
	.data.b	188,1
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+1102
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2711
	.data.b	79,99,117,95,77,97,112,112,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 3054
	.data.w	.Ldw_str_begin+2711
	.data.b	189,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+2994

	.data.b	71
	.data.b	194,1
	.data.b	1
	.data.b	5
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2727
	.data.b	77,97,120,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 3074
	.data.w	.Ldw_str_begin+2727
	.data.b	196,1
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+1078
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2739
	.data.b	79,99,117,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3091
	.data.w	.Ldw_str_begin+2739
	.data.b	198,1
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+112
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2760
	.data.b	79,99,117,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3109
	.data.w	.Ldw_str_begin+2760
	.data.b	199,1
	.data.b	2
	.data.b	5
	.data.w	.Ldw_begin+3066

	.data.b	71
	.data.b	205,1
	.data.b	1
	.data.b	5
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2779
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3129
	.data.w	.Ldw_str_begin+2779
	.data.b	207,1
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+572
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2793
	.data.b	79,99,117,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,0
	.section	.debug_info		;off: 3146
	.data.w	.Ldw_str_begin+2793
	.data.b	209,1
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+593
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2813
	.data.b	79,99,117,95,72,87,71,116,109,65,116,111,109,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3163
	.data.w	.Ldw_str_begin+2813
	.data.b	211,1
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+603
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2836
	.data.b	79,99,117,72,119,67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 3180
	.data.w	.Ldw_str_begin+2836
	.data.b	213,1
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+613
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2855
	.data.b	79,99,117,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 3198
	.data.w	.Ldw_str_begin+2855
	.data.b	214,1
	.data.b	2
	.data.b	5
	.data.w	.Ldw_begin+3121

	.data.b	6
	.section	.debug_str		;off: 2870
	.data.b	79,99,117,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3211
	.data.w	.Ldw_str_begin+2870
	.data.b	122
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+618
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_ChannelStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

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

	.section	.debug_info		;off: 3230
	.data.b	6
	.section	.debug_str		;off: 2893
	.data.b	79,99,117,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 3231
	.data.w	.Ldw_str_begin+2893
	.data.b	124
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2449
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_DriverStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	6
	.section	.debug_str		;off: 2915
	.data.b	79,99,117,95,67,104,97,110,110,101,108,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3251
	.data.w	.Ldw_str_begin+2915
	.data.b	141,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+634
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_ChannelStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	6
	.section	.debug_str		;off: 2938
	.data.b	79,99,117,95,68,114,105,118,101,114,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 3272
	.data.w	.Ldw_str_begin+2938
	.data.b	143,1
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2449
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_DriverStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	6
	.section	.debug_str		;off: 2960
	.data.b	79,99,117,95,67,111,114,101,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3293
	.data.w	.Ldw_str_begin+2960
	.data.b	194,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+650
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_CoreChannelStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	6
	.section	.debug_str		;off: 2985
	.data.b	79,99,117,95,67,111,114,101,68,114,105,118,101,114,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 3314
	.data.w	.Ldw_str_begin+2985
	.data.b	229,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+676
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_CoreDriverStatusPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	6
	.section	.debug_str		;off: 3009
	.data.b	79,99,117,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 3335
	.data.w	.Ldw_str_begin+3009
	.data.b	141,2
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+122
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Ocu_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.

	.data.b	27
	.section	.debug_str		;off: 3023
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 3356
	.data.w	.Ldw_str_begin+3023
	.data.b	63
	.data.b	31
	.data.b	15
	.data.w	.Ldw_begin+1293
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

	.section	.debug_info		;off: 3373
	.data.b	37

	.section	.debug_abbrev		;off: 222
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 3374
	.data.b	8
	.section	.debug_str		;off: 3043
	.data.b	105,100,0
	.section	.debug_info		;off: 3375
	.data.w	.Ldw_str_begin+3043
	.data.b	65
	.data.b	17
	.data.b	15
	.data.w	.Ldw_begin+1293
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

	.section	.debug_info		;off: 3388
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3046
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 3391
	.data.w	.Ldw_str_begin+3046
	.data.b	131,2
	.data.b	48
	.data.b	12
	.data.w	.Ldw_begin+1126
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3059
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 3411
	.data.w	.Ldw_str_begin+3059
	.data.b	133,2
	.data.b	38
	.data.b	12
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

	.section	.debug_info		;off: 3425
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3076
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3427
	.data.w	.Ldw_str_begin+3076
	.data.b	140,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3100
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,83,101,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 3447
	.data.w	.Ldw_str_begin+3100
	.data.b	159,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3125
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,83,101,116,83,105,103,110,97,108,76,101,118,101,108,0
	.section	.debug_info		;off: 3467
	.data.w	.Ldw_str_begin+3125
	.data.b	179,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3152
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,83,101,116,83,105,103,110,97,108,76,101,118,101,108,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 3487
	.data.w	.Ldw_str_begin+3152
	.data.b	197,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3186
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,83,101,116,79,117,116,112,117,116,66,101,104,97,118,105,111,114,0
	.section	.debug_info		;off: 3507
	.data.w	.Ldw_str_begin+3186
	.data.b	217,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3216
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,83,101,116,67,104,97,110,110,101,108,79,117,116,112,117,116,0
	.section	.debug_info		;off: 3527
	.data.w	.Ldw_str_begin+3216
	.data.b	238,1
	.data.b	16
	.data.b	37
	.data.w	.Ldw_begin+1066
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3245
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,71,101,116,67,111,117,110,116,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 3547
	.data.w	.Ldw_str_begin+3245
	.data.b	255,1
	.data.b	15
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3273
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3567
	.data.w	.Ldw_str_begin+3273
	.data.b	144,2
	.data.b	15
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3304
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,71,101,116,73,110,116,101,114,114,117,112,116,69,110,97,98,108,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3587
	.data.w	.Ldw_str_begin+3304
	.data.b	161,2
	.data.b	15
	.data.b	37
	.data.w	.Ldw_begin+1102
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3341
	.data.b	71,116,109,95,79,99,117,95,72,97,108,95,67,108,101,97,114,73,110,116,101,114,114,117,112,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 3607
	.data.w	.Ldw_str_begin+3341
	.data.b	178,2
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
	.section	.debug_str		;off: 3374
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 3623
	.data.w	.Ldw_str_begin+3374
	.data.b	105
	.data.b	39
	.data.b	42
	.data.w	.Ldw_begin+1126
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3390
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 3642
	.data.w	.Ldw_str_begin+3390
	.data.b	113
	.data.b	39
	.data.b	42
	.data.w	.Ldw_begin+1126
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 3413
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,83,116,97,114,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3661
	.data.w	.Ldw_str_begin+3413
	.data.b	30
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
	.section	.debug_str		;off: 3441
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,83,116,97,114,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3676
	.data.w	.Ldw_str_begin+3441
	.data.b	35
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
	.section	.debug_str		;off: 3468
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,83,101,116,65,98,115,111,108,117,116,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 3691
	.data.w	.Ldw_str_begin+3468
	.data.b	40
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
	.section	.debug_str		;off: 3504
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,83,101,116,65,98,115,111,108,117,116,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 3706
	.data.w	.Ldw_str_begin+3504
	.data.b	45
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
	.section	.debug_str		;off: 3539
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,83,101,116,82,101,108,97,116,105,118,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 3721
	.data.w	.Ldw_str_begin+3539
	.data.b	50
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
	.section	.debug_str		;off: 3575
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,83,101,116,82,101,108,97,116,105,118,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 3736
	.data.w	.Ldw_str_begin+3575
	.data.b	55
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
	.section	.debug_str		;off: 3610
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,83,116,111,112,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3751
	.data.w	.Ldw_str_begin+3610
	.data.b	60
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
	.section	.debug_str		;off: 3637
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,83,116,111,112,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 3766
	.data.w	.Ldw_str_begin+3637
	.data.b	65
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
	.section	.debug_str		;off: 3663
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,83,101,116,80,105,110,65,99,116,105,111,110,0
	.section	.debug_info		;off: 3781
	.data.w	.Ldw_str_begin+3663
	.data.b	70
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
	.section	.debug_str		;off: 3691
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,83,101,116,80,105,110,65,99,116,105,111,110,0
	.section	.debug_info		;off: 3796
	.data.w	.Ldw_str_begin+3691
	.data.b	75
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
	.section	.debug_str		;off: 3718
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3811
	.data.w	.Ldw_str_begin+3718
	.data.b	80
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
	.section	.debug_str		;off: 3752
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3826
	.data.w	.Ldw_str_begin+3752
	.data.b	85
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
	.section	.debug_str		;off: 3785
	.data.b	83,99,104,77,95,69,110,116,101,114,95,79,99,117,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3841
	.data.w	.Ldw_str_begin+3785
	.data.b	90
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
	.section	.debug_str		;off: 3820
	.data.b	83,99,104,77,95,69,120,105,116,95,79,99,117,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 3856
	.data.w	.Ldw_str_begin+3820
	.data.b	95
	.data.b	13
	.data.b	43
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 3854
	.data.b	79,99,117,95,71,101,116,84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 3871
	.data.w	.Ldw_str_begin+3854
	.data.b	171,3
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 3870
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 3890
	.data.w	.Ldw_str_begin+3870
	.data.b	173,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+1305
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

	.section	.debug_info		;off: 3903
	.data.b	20
	.section	.debug_str		;off: 3877
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 3904
	.data.w	.Ldw_str_begin+3877
	.data.b	174,3
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 3891
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 3919
	.data.w	.Ldw_str_begin+3891
	.data.b	177,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3901
	.data.b	72,87,67,111,110,102,105,103,73,110,100,101,120,0
	.section	.debug_info		;off: 3934
	.data.w	.Ldw_str_begin+3901
	.data.b	178,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3915
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 3949
	.data.w	.Ldw_str_begin+3915
	.data.b	179,3
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 3924
	.data.b	79,99,117,95,67,104,101,99,107,68,101,116,69,114,114,111,114,115,0
	.section	.debug_info		;off: 3966
	.data.w	.Ldw_str_begin+3924
	.data.b	219,3
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_CheckDetErrors
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

	.section	.debug_abbrev		;off: 288
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
	.data.w	Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_CheckDetErrors-Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1772
	.data.b	0,5,2
	.data.w	Ocu_CheckDetErrors..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	224,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	108
	.data.b	11
	.data.b	75
	.data.b	11
	.data.b	61
	.data.b	12
	.data.b	12
	.data.b	45
	.data.b	155
	.data.b	11
	.data.b	60
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
	.section	.debug_info		;off: 4001
	.data.b	22
	.section	.debug_str		;off: 3943
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4002
	.data.w	.Ldw_str_begin+3943
	.data.b	221,3
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
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

	.section	.debug_abbrev		;off: 336
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

	.section	.debug_info		;off: 4019
	.data.b	22
	.section	.debug_str		;off: 3951
	.data.b	65,112,105,83,105,100,0
	.section	.debug_info		;off: 4020
	.data.w	.Ldw_str_begin+3951
	.data.b	222,3
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4037
	.data.b	22
	.section	.debug_str		;off: 3958
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4038
	.data.w	.Ldw_str_begin+3958
	.data.b	223,3
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4055
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 355
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 4064
	.data.b	8
	.section	.debug_str		;off: 3965
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 4065
	.data.w	.Ldw_str_begin+3965
	.data.b	226,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 3975
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4080
	.data.w	.Ldw_str_begin+3975
	.data.b	227,3
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 3992
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4095
	.data.w	.Ldw_str_begin+3992
	.data.b	228,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
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

	.section	.debug_abbrev		;off: 364
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

	.section	.debug_info		;off: 4113
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4001
	.data.b	79,99,117,95,73,110,105,116,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4116
	.data.w	.Ldw_str_begin+4001
	.data.b	160,4
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_InitDetCheck
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
	.data.w	Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_InitDetCheck-Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1822
	.data.b	0,5,2
	.data.w	Ocu_InitDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	164,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	45
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	61
	.data.b	11
	.data.b	91
	.data.b	12
	.data.b	109
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
	.section	.debug_info		;off: 4151
	.data.b	22
	.section	.debug_str		;off: 4018
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4152
	.data.w	.Ldw_str_begin+4018
	.data.b	162,4
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+127
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4169
	.data.b	22
	.section	.debug_str		;off: 4028
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4170
	.data.w	.Ldw_str_begin+4028
	.data.b	163,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4187
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 4035
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4197
	.data.w	.Ldw_str_begin+4035
	.data.b	166,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+114
	.section	.debug_loc		;off: 114
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4215
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4044
	.data.b	79,99,117,95,83,101,116,65,98,115,111,108,117,116,101,84,104,114,101,115,104,111,108,100,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4218
	.data.w	.Ldw_str_begin+4044
	.data.b	227,4
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetAbsoluteThresholdDetCheck
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetAbsoluteThresholdDetCheck-Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1863
	.data.b	0,5,2
	.data.w	Ocu_SetAbsoluteThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	232,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	12
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	44
	.data.b	188
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	60
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	13
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
	.section	.debug_info		;off: 4253
	.data.b	22
	.section	.debug_str		;off: 4077
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4254
	.data.w	.Ldw_str_begin+4077
	.data.b	229,4
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
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
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4271
	.data.b	22
	.section	.debug_str		;off: 4091
	.data.b	82,101,102,101,114,101,110,99,101,86,97,108,117,101,0
	.section	.debug_info		;off: 4272
	.data.w	.Ldw_str_begin+4091
	.data.b	230,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+163
	.section	.debug_loc		;off: 163
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	81
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4289
	.data.b	22
	.section	.debug_str		;off: 4106
	.data.b	65,98,115,111,108,117,116,101,86,97,108,117,101,0
	.section	.debug_info		;off: 4290
	.data.w	.Ldw_str_begin+4106
	.data.b	231,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+193
	.section	.debug_loc		;off: 193
	.data.w	.LDW61
	.data.w	.LDW71
	.data.b	1,0
	.data.b	82
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4307
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 4120
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4317
	.data.w	.Ldw_str_begin+4120
	.data.b	234,4
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
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

	.section	.debug_info		;off: 4335
	.data.b	7
	.section	.debug_str		;off: 4127
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4336
	.data.w	.Ldw_str_begin+4127
	.data.b	235,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
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

	.section	.debug_info		;off: 4354
	.data.b	8
	.section	.debug_str		;off: 4136
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4355
	.data.w	.Ldw_str_begin+4136
	.data.b	236,4
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4152
	.data.b	79,99,117,95,83,101,116,82,101,108,97,116,105,118,101,84,104,114,101,115,104,111,108,100,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4372
	.data.w	.Ldw_str_begin+4152
	.data.b	175,5
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetRelativeThresholdDetCheck
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

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetRelativeThresholdDetCheck-Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1948
	.data.b	0,5,2
	.data.w	Ocu_SetRelativeThresholdDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	179,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	44
	.data.b	188
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
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
	.section	.debug_info		;off: 4407
	.data.b	22
	.section	.debug_str		;off: 4185
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4408
	.data.w	.Ldw_str_begin+4185
	.data.b	177,5
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+261
	.section	.debug_loc		;off: 261
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	80
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4425
	.data.b	22
	.section	.debug_str		;off: 4199
	.data.b	82,101,108,97,116,105,118,101,86,97,108,117,101,0
	.section	.debug_info		;off: 4426
	.data.w	.Ldw_str_begin+4199
	.data.b	178,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+291
	.section	.debug_loc		;off: 291
	.data.w	.LDW91
	.data.w	.LDW02
	.data.b	1,0
	.data.b	81
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4443
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 4213
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4453
	.data.w	.Ldw_str_begin+4213
	.data.b	181,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+321
	.section	.debug_loc		;off: 321
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4471
	.data.b	7
	.section	.debug_str		;off: 4220
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4472
	.data.w	.Ldw_str_begin+4220
	.data.b	182,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+340
	.section	.debug_loc		;off: 340
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4490
	.data.b	8
	.section	.debug_str		;off: 4229
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4491
	.data.w	.Ldw_str_begin+4229
	.data.b	183,5
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4245
	.data.b	79,99,117,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4508
	.data.w	.Ldw_str_begin+4245
	.data.b	235,5
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_EnableNotificationDetCheck
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_EnableNotificationDetCheck-Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2009
	.data.b	0,5,2
	.data.w	Ocu_EnableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	238,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
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
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	187
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
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
	.section	.debug_info		;off: 4543
	.data.b	22
	.section	.debug_str		;off: 4276
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4544
	.data.w	.Ldw_str_begin+4276
	.data.b	237,5
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+359
	.section	.debug_loc		;off: 359
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

	.section	.debug_info		;off: 4561
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 4290
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4571
	.data.w	.Ldw_str_begin+4290
	.data.b	240,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+389
	.section	.debug_loc		;off: 389
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4589
	.data.b	7
	.section	.debug_str		;off: 4297
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4590
	.data.w	.Ldw_str_begin+4297
	.data.b	241,5
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+408
	.section	.debug_loc		;off: 408
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4608
	.data.b	8
	.section	.debug_str		;off: 4306
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4609
	.data.w	.Ldw_str_begin+4306
	.data.b	242,5
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4322
	.data.b	79,99,117,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,68,101,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4626
	.data.w	.Ldw_str_begin+4322
	.data.b	166,6
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_DisableNotificationDetCheck
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
	.data.w	Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_DisableNotificationDetCheck-Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2074
	.data.b	0,5,2
	.data.w	Ocu_DisableNotificationDetCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	169,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
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
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	187
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
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
	.section	.debug_info		;off: 4661
	.data.b	22
	.section	.debug_str		;off: 4354
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 4662
	.data.w	.Ldw_str_begin+4354
	.data.b	168,6
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+427
	.section	.debug_loc		;off: 427
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

	.section	.debug_info		;off: 4679
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 4368
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4689
	.data.w	.Ldw_str_begin+4368
	.data.b	171,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+457
	.section	.debug_loc		;off: 457
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4707
	.data.b	7
	.section	.debug_str		;off: 4375
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4708
	.data.w	.Ldw_str_begin+4375
	.data.b	172,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+476
	.section	.debug_loc		;off: 476
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4726
	.data.b	8
	.section	.debug_str		;off: 4384
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4727
	.data.w	.Ldw_str_begin+4384
	.data.b	173,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4400
	.data.b	79,99,117,95,68,101,73,110,105,116,67,104,101,99,107,0
	.section	.debug_info		;off: 4744
	.data.w	.Ldw_str_begin+4400
	.data.b	230,6
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.w	Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_DeInitCheck
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
	.data.w	Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_DeInitCheck-Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2139
	.data.b	0,5,2
	.data.w	Ocu_DeInitCheck..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	233,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	107
	.data.b	12
	.data.b	93
	.data.b	43
	.data.b	13
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	139
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	113
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4779
	.data.b	22
	.section	.debug_str		;off: 4416
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 4780
	.data.w	.Ldw_str_begin+4416
	.data.b	232,6
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.w	.Ldw_loc_begin+495
	.section	.debug_loc		;off: 495
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

	.section	.debug_info		;off: 4797
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 4423
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 4807
	.data.w	.Ldw_str_begin+4423
	.data.b	235,6
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+525
	.section	.debug_loc		;off: 525
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4825
	.data.b	7
	.section	.debug_str		;off: 4432
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4826
	.data.w	.Ldw_str_begin+4432
	.data.b	236,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+544
	.section	.debug_loc		;off: 544
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4844
	.data.b	8
	.section	.debug_str		;off: 4443
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4845
	.data.w	.Ldw_str_begin+4443
	.data.b	237,6
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4459
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 4860
	.data.w	.Ldw_str_begin+4459
	.data.b	238,6
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+239
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4481
	.data.b	79,99,117,95,71,101,116,82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 4877
	.data.w	.Ldw_str_begin+4481
	.data.b	177,7
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.w	Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_GetReturnValue
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
	.data.w	Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_GetReturnValue-Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2199
	.data.b	0,5,2
	.data.w	Ocu_GetReturnValue..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	186,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	6
	.data.b	60
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
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 4910
	.data.b	22
	.section	.debug_str		;off: 4500
	.data.b	80,111,115,116,86,97,108,117,101,0
	.section	.debug_info		;off: 4911
	.data.w	.Ldw_str_begin+4500
	.data.b	179,7
	.data.b	18
	.data.b	1
	.data.w	.Ldw_begin+244
	.data.b	0
	.data.w	.Ldw_loc_begin+563
	.section	.debug_loc		;off: 563
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4928
	.data.b	22
	.section	.debug_str		;off: 4510
	.data.b	83,116,97,114,116,86,97,108,0
	.section	.debug_info		;off: 4929
	.data.w	.Ldw_str_begin+4510
	.data.b	180,7
	.data.b	18
	.data.b	1
	.data.w	.Ldw_begin+244
	.data.b	0
	.data.w	.Ldw_loc_begin+582
	.section	.debug_loc		;off: 582
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4946
	.data.b	22
	.section	.debug_str		;off: 4519
	.data.b	67,111,109,112,97,114,101,86,97,108,0
	.section	.debug_info		;off: 4947
	.data.w	.Ldw_str_begin+4519
	.data.b	181,7
	.data.b	18
	.data.b	1
	.data.w	.Ldw_begin+244
	.data.b	0
	.data.w	.Ldw_loc_begin+601
	.section	.debug_loc		;off: 601
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 4964
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	8
	.section	.debug_str		;off: 4530
	.data.b	82,101,116,86,97,108,0
	.section	.debug_info		;off: 4974
	.data.w	.Ldw_str_begin+4530
	.data.b	184,7
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4537
	.data.b	79,99,117,95,83,101,116,67,111,109,112,97,114,101,0
	.section	.debug_info		;off: 4991
	.data.w	.Ldw_str_begin+4537
	.data.b	242,7
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.w	Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetCompare
	.data.b	1
	.data.b	93
	.data.b	128,128,1
	.data.b	0
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
	.data.w	Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_SetCompare-Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2263
	.data.b	0,5,2
	.data.w	Ocu_SetCompare..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	249,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	44
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	28
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	77
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5026
	.data.b	22
	.section	.debug_str		;off: 4552
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 5027
	.data.w	.Ldw_str_begin+4552
	.data.b	244,7
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.w	.Ldw_loc_begin+620
	.section	.debug_loc		;off: 620
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5044
	.data.b	22
	.section	.debug_str		;off: 4565
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5045
	.data.w	.Ldw_str_begin+4565
	.data.b	246,7
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.w	.Ldw_loc_begin+639
	.section	.debug_loc		;off: 639
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	81
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5062
	.data.b	22
	.section	.debug_str		;off: 4584
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 5063
	.data.w	.Ldw_str_begin+4584
	.data.b	247,7
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.w	.Ldw_loc_begin+669
	.section	.debug_loc		;off: 669
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5080
	.data.b	22
	.section	.debug_str		;off: 4593
	.data.b	79,117,116,112,117,116,65,99,116,105,111,110,0
	.section	.debug_info		;off: 5081
	.data.w	.Ldw_str_begin+4593
	.data.b	248,7
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2549
	.data.b	0
	.data.w	.Ldw_loc_begin+688
	.section	.debug_loc		;off: 688
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5098
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	7
	.section	.debug_str		;off: 4606
	.data.b	66,101,104,97,118,105,111,114,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 5108
	.data.w	.Ldw_str_begin+4606
	.data.b	251,7
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+707
	.section	.debug_loc		;off: 707
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5126
	.data.b	7
	.section	.debug_str		;off: 4622
	.data.b	67,109,112,86,97,108,117,101,0
	.section	.debug_info		;off: 5127
	.data.w	.Ldw_str_begin+4622
	.data.b	252,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2241
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+727
	.section	.debug_loc		;off: 727
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5145
	.data.b	8
	.section	.debug_str		;off: 4631
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 5146
	.data.w	.Ldw_str_begin+4631
	.data.b	253,7
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4642
	.data.b	79,99,117,95,83,116,97,114,116,67,104,97,110,110,101,108,66,121,65,116,111,109,0
	.section	.debug_info		;off: 5163
	.data.w	.Ldw_str_begin+4642
	.data.b	178,8
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.w	Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_StartChannelByAtom
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_StartChannelByAtom-Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2302
	.data.b	0,5,2
	.data.w	Ocu_StartChannelByAtom..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	184,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	61
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	12
	.data.b	13
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	92
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	75
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	93
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5198
	.data.b	22
	.section	.debug_str		;off: 4665
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5199
	.data.w	.Ldw_str_begin+4665
	.data.b	180,8
	.data.b	32
	.data.b	1
	.data.w	.Ldw_begin+320
	.data.b	0
	.data.w	.Ldw_loc_begin+747
	.section	.debug_loc		;off: 747
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	80
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5216
	.data.b	22
	.section	.debug_str		;off: 4687
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5217
	.data.w	.Ldw_str_begin+4687
	.data.b	182,8
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.w	.Ldw_loc_begin+777
	.section	.debug_loc		;off: 777
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	81
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5234
	.data.b	22
	.section	.debug_str		;off: 4706
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 5235
	.data.w	.Ldw_str_begin+4706
	.data.b	183,8
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.w	.Ldw_loc_begin+807
	.section	.debug_loc		;off: 807
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	82
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5252
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	8
	.section	.debug_str		;off: 4715
	.data.b	67,117,114,114,101,110,116,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 5262
	.data.w	.Ldw_str_begin+4715
	.data.b	186,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4730
	.data.b	65,98,115,111,108,117,116,101,86,97,108,117,101,0
	.section	.debug_info		;off: 5277
	.data.w	.Ldw_str_begin+4730
	.data.b	187,8
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+837
	.section	.debug_loc		;off: 837
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5295
	.data.b	7
	.section	.debug_str		;off: 4744
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 5296
	.data.w	.Ldw_str_begin+4744
	.data.b	188,8
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+856
	.section	.debug_loc		;off: 856
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5314
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 4755
	.data.b	79,99,117,95,71,101,116,72,97,114,100,119,97,114,101,67,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5317
	.data.w	.Ldw_str_begin+4755
	.data.b	138,9
	.data.b	69
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.w	Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_GetHardwareChannelObjectPtr
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

	.section	.debug_frame		;off: 384
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.w	__ghs_eofn_Ocu_GetHardwareChannelObjectPtr-Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2361
	.data.b	0,5,2
	.data.w	Ocu_GetHardwareChannelObjectPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5COcu.
	.data.b	6
	.data.b	3
	.data.b	147,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5350
	.data.b	22
	.section	.debug_str		;off: 4787
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5351
	.data.w	.Ldw_str_begin+4787
	.data.b	140,9
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.w	.Ldw_loc_begin+875
	.section	.debug_loc		;off: 875
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5368
	.data.b	22
	.section	.debug_str		;off: 4794
	.data.b	67,104,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5369
	.data.w	.Ldw_str_begin+4794
	.data.b	141,9
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.w	.Ldw_loc_begin+894
	.section	.debug_loc		;off: 894
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5386
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	8
	.section	.debug_str		;off: 4808
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 5396
	.data.w	.Ldw_str_begin+4808
	.data.b	144,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4818
	.data.b	72,87,67,111,110,102,105,103,73,110,100,101,120,0
	.section	.debug_info		;off: 5411
	.data.w	.Ldw_str_begin+4818
	.data.b	145,9
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 4832
	.data.b	67,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5426
	.data.w	.Ldw_str_begin+4832
	.data.b	146,9
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4849
	.data.b	79,99,117,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 5443
	.data.w	.Ldw_str_begin+4849
	.data.b	186,9
	.data.b	29
	.data.b	1
	.data.w	Ocu_GetVersionInfo
	.data.w	__ghs_eofn_Ocu_GetVersionInfo
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

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_GetVersionInfo
	.data.w	__ghs_eofn_Ocu_GetVersionInfo-Ocu_GetVersionInfo
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2388
	.data.b	0,5,2
	.data.w	Ocu_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	193,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	12
	.data.b	76
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	44
	.data.b	44
	.data.b	44
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5472
	.data.b	22
	.section	.debug_str		;off: 4868
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 5473
	.data.w	.Ldw_str_begin+4868
	.data.b	190,9
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+369
	.data.b	0
	.data.w	.Ldw_loc_begin+913
	.section	.debug_loc		;off: 913
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5490
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 4883
	.data.b	79,99,117,95,73,110,105,116,0
	.section	.debug_info		;off: 5502
	.data.w	.Ldw_str_begin+4883
	.data.b	243,9
	.data.b	29
	.data.b	1
	.data.w	Ocu_Init
	.data.w	__ghs_eofn_Ocu_Init
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_Init
	.data.w	__ghs_eofn_Ocu_Init-Ocu_Init
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2424
	.data.b	0,5,2
	.data.w	Ocu_Init
	.data.b	6
	.data.b	3
	.data.b	247,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	44
	.data.b	11
	.data.b	28
	.data.b	60
	.data.b	29
	.data.b	2
	.data.b	4
	.data.b	45
	.data.b	76
	.data.b	44
	.data.b	109
	.data.b	123
	.data.b	13
	.data.b	12
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	107
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	141
	.data.b	123
	.data.b	12
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	61
	.data.b	45
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	72
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	57
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	107
	.data.b	13
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 5533
	.data.b	22
	.section	.debug_str		;off: 4892
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5534
	.data.w	.Ldw_str_begin+4892
	.data.b	246,9
	.data.b	56
	.data.b	1
	.data.w	.Ldw_begin+122
	.data.b	0
	.data.w	.Ldw_loc_begin+932
	.section	.debug_loc		;off: 932
	.data.w	.LDW64
	.data.w	.LDW74
	.data.b	1,0
	.data.b	80
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5551
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 4902
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5561
	.data.w	.Ldw_str_begin+4902
	.data.b	249,9
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+962
	.section	.debug_loc		;off: 962
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5579
	.data.b	7
	.section	.debug_str		;off: 4909
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5580
	.data.w	.Ldw_str_begin+4909
	.data.b	250,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+981
	.section	.debug_loc		;off: 981
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5598
	.data.b	7
	.section	.debug_str		;off: 4920
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5599
	.data.w	.Ldw_str_begin+4920
	.data.b	251,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1001
	.section	.debug_loc		;off: 1001
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5617
	.data.b	7
	.section	.debug_str		;off: 4936
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5618
	.data.w	.Ldw_str_begin+4936
	.data.b	252,9
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+112
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1020
	.section	.debug_loc		;off: 1020
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5636
	.data.b	7
	.section	.debug_str		;off: 4953
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5637
	.data.w	.Ldw_str_begin+4953
	.data.b	253,9
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1039
	.section	.debug_loc		;off: 1039
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5655
	.data.b	7
	.section	.debug_str		;off: 4975
	.data.b	72,87,67,111,110,102,105,103,73,110,100,101,120,0
	.section	.debug_info		;off: 5656
	.data.w	.Ldw_str_begin+4975
	.data.b	254,9
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1058
	.section	.debug_loc		;off: 1058
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5674
	.data.b	8
	.section	.debug_str		;off: 4989
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 5675
	.data.w	.Ldw_str_begin+4989
	.data.b	255,9
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 4999
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5690
	.data.w	.Ldw_str_begin+4999
	.data.b	128,10
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1078
	.section	.debug_loc		;off: 1078
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5708
	.data.b	7
	.section	.debug_str		;off: 5018
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 5709
	.data.w	.Ldw_str_begin+5018
	.data.b	129,10
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1098
	.section	.debug_loc		;off: 1098
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5727
	.data.b	8
	.section	.debug_str		;off: 5029
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 5728
	.data.w	.Ldw_str_begin+5029
	.data.b	130,10
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5040
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5743
	.data.w	.Ldw_str_begin+5040
	.data.b	132,10
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5049
	.data.b	79,99,117,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 5760
	.data.w	.Ldw_str_begin+5049
	.data.b	253,10
	.data.b	29
	.data.b	1
	.data.w	Ocu_DeInit
	.data.w	__ghs_eofn_Ocu_DeInit
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
	.data.w	Ocu_DeInit
	.data.w	__ghs_eofn_Ocu_DeInit-Ocu_DeInit
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2548
	.data.b	0,5,2
	.data.w	Ocu_DeInit
	.data.b	6
	.data.b	3
	.data.b	128,11
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
	.data.b	43
	.data.b	27
	.data.b	11
	.data.b	75
	.data.b	60
	.data.b	61
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	13
	.data.b	43
	.data.b	11
	.data.b	92
	.data.b	13
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5791
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 5060
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5801
	.data.w	.Ldw_str_begin+5060
	.data.b	130,11
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1117
	.section	.debug_loc		;off: 1117
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5819
	.data.b	8
	.section	.debug_str		;off: 5067
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 5820
	.data.w	.Ldw_str_begin+5067
	.data.b	131,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5083
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 5835
	.data.w	.Ldw_str_begin+5083
	.data.b	132,11
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5105
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 5850
	.data.w	.Ldw_str_begin+5105
	.data.b	133,11
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1136
	.section	.debug_loc		;off: 1136
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5868
	.data.b	7
	.section	.debug_str		;off: 5124
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 5869
	.data.w	.Ldw_str_begin+5124
	.data.b	134,11
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1155
	.section	.debug_loc		;off: 1155
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5887
	.data.b	7
	.section	.debug_str		;off: 5135
	.data.b	79,99,117,95,67,104,73,110,67,111,114,101,0
	.section	.debug_info		;off: 5888
	.data.w	.Ldw_str_begin+5135
	.data.b	135,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1174
	.section	.debug_loc		;off: 1174
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5906
	.data.b	8
	.section	.debug_str		;off: 5148
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 5907
	.data.w	.Ldw_str_begin+5148
	.data.b	136,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5157
	.data.b	79,99,117,95,83,116,97,114,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 5924
	.data.w	.Ldw_str_begin+5157
	.data.b	207,11
	.data.b	29
	.data.b	1
	.data.w	Ocu_StartChannel
	.data.w	__ghs_eofn_Ocu_StartChannel
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_StartChannel
	.data.w	__ghs_eofn_Ocu_StartChannel-Ocu_StartChannel
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2629
	.data.b	0,5,2
	.data.w	Ocu_StartChannel
	.data.b	6
	.data.b	3
	.data.b	210,11
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
	.data.w	.LDWlin13
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	60
	.data.b	12
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	45
	.data.b	13
	.data.b	11
	.data.b	75
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	252
	.data.b	77
	.data.b	43
	.data.b	12
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	13
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	28
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 5955
	.data.b	22
	.section	.debug_str		;off: 5174
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 5956
	.data.w	.Ldw_str_begin+5174
	.data.b	209,11
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1193
	.section	.debug_loc		;off: 1193
	.data.w	.LDW25
	.data.w	.LDW35
	.data.b	1,0
	.data.b	80
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 5973
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	7
	.section	.debug_str		;off: 5188
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 5983
	.data.w	.Ldw_str_begin+5188
	.data.b	212,11
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1223
	.section	.debug_loc		;off: 1223
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6001
	.data.b	7
	.section	.debug_str		;off: 5195
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6002
	.data.w	.Ldw_str_begin+5195
	.data.b	213,11
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1242
	.section	.debug_loc		;off: 1242
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6020
	.data.b	7
	.section	.debug_str		;off: 5211
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6021
	.data.w	.Ldw_str_begin+5211
	.data.b	214,11
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1261
	.section	.debug_loc		;off: 1261
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6039
	.data.b	7
	.section	.debug_str		;off: 5233
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 6040
	.data.w	.Ldw_str_begin+5233
	.data.b	215,11
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1280
	.section	.debug_loc		;off: 1280
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6058
	.data.b	8
	.section	.debug_str		;off: 5252
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 6059
	.data.w	.Ldw_str_begin+5252
	.data.b	216,11
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5261
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 6074
	.data.w	.Ldw_str_begin+5261
	.data.b	217,11
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1299
	.section	.debug_loc		;off: 1299
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6092
	.data.b	8
	.section	.debug_str		;off: 5272
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6093
	.data.w	.Ldw_str_begin+5272
	.data.b	218,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5283
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6108
	.data.w	.Ldw_str_begin+5283
	.data.b	220,11
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5292
	.data.b	79,99,117,95,83,116,111,112,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 6125
	.data.w	.Ldw_str_begin+5292
	.data.b	187,12
	.data.b	29
	.data.b	1
	.data.w	Ocu_StopChannel
	.data.w	__ghs_eofn_Ocu_StopChannel
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_StopChannel
	.data.w	__ghs_eofn_Ocu_StopChannel-Ocu_StopChannel
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2719
	.data.b	0,5,2
	.data.w	Ocu_StopChannel
	.data.b	6
	.data.b	3
	.data.b	190,12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	60
	.data.b	12
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	75
	.data.b	27
	.data.b	43
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	155
	.data.b	12
	.data.b	6
	.data.b	77
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	45
	.data.b	28
	.data.b	109
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	27
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
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6156
	.data.b	22
	.section	.debug_str		;off: 5308
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6157
	.data.w	.Ldw_str_begin+5308
	.data.b	189,12
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1318
	.section	.debug_loc		;off: 1318
	.data.w	.LDW55
	.data.w	.LDW65
	.data.b	1,0
	.data.b	80
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6174
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 5322
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6184
	.data.w	.Ldw_str_begin+5322
	.data.b	192,12
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1348
	.section	.debug_loc		;off: 1348
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6202
	.data.b	7
	.section	.debug_str		;off: 5329
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6203
	.data.w	.Ldw_str_begin+5329
	.data.b	193,12
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1367
	.section	.debug_loc		;off: 1367
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6221
	.data.b	7
	.section	.debug_str		;off: 5345
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6222
	.data.w	.Ldw_str_begin+5345
	.data.b	194,12
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1386
	.section	.debug_loc		;off: 1386
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6240
	.data.b	7
	.section	.debug_str		;off: 5367
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 6241
	.data.w	.Ldw_str_begin+5367
	.data.b	195,12
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1405
	.section	.debug_loc		;off: 1405
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6259
	.data.b	7
	.section	.debug_str		;off: 5386
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 6260
	.data.w	.Ldw_str_begin+5386
	.data.b	196,12
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1424
	.section	.debug_loc		;off: 1424
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6278
	.data.b	8
	.section	.debug_str		;off: 5397
	.data.b	76,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 6279
	.data.w	.Ldw_str_begin+5397
	.data.b	197,12
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5408
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6294
	.data.w	.Ldw_str_begin+5408
	.data.b	199,12
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5417
	.data.b	79,99,117,95,83,101,116,80,105,110,83,116,97,116,101,0
	.section	.debug_info		;off: 6311
	.data.w	.Ldw_str_begin+5417
	.data.b	185,13
	.data.b	29
	.data.b	1
	.data.w	Ocu_SetPinState
	.data.w	__ghs_eofn_Ocu_SetPinState
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_SetPinState
	.data.w	__ghs_eofn_Ocu_SetPinState-Ocu_SetPinState
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2836
	.data.b	0,5,2
	.data.w	Ocu_SetPinState
	.data.b	6
	.data.b	3
	.data.b	189,13
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
	.data.w	.LDWlin17
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	13
	.data.b	108
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	139
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	12
	.data.b	13
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	60
	.data.b	27
	.data.b	11
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6342
	.data.b	22
	.section	.debug_str		;off: 5433
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6343
	.data.w	.Ldw_str_begin+5433
	.data.b	187,13
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1443
	.section	.debug_loc		;off: 1443
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	80
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6360
	.data.b	22
	.section	.debug_str		;off: 5447
	.data.b	80,105,110,83,116,97,116,101,0
	.section	.debug_info		;off: 6361
	.data.w	.Ldw_str_begin+5447
	.data.b	188,13
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+2408
	.data.b	0
	.data.w	.Ldw_loc_begin+1473
	.section	.debug_loc		;off: 1473
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

	.section	.debug_info		;off: 6378
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 5456
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6388
	.data.w	.Ldw_str_begin+5456
	.data.b	191,13
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1503
	.section	.debug_loc		;off: 1503
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6406
	.data.b	7
	.section	.debug_str		;off: 5463
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6407
	.data.w	.Ldw_str_begin+5463
	.data.b	192,13
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1522
	.section	.debug_loc		;off: 1522
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6425
	.data.b	7
	.section	.debug_str		;off: 5479
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6426
	.data.w	.Ldw_str_begin+5479
	.data.b	193,13
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+239
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1541
	.section	.debug_loc		;off: 1541
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6444
	.data.b	8
	.section	.debug_str		;off: 5501
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 6445
	.data.w	.Ldw_str_begin+5501
	.data.b	194,13
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5520
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 6460
	.data.w	.Ldw_str_begin+5520
	.data.b	195,13
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1560
	.section	.debug_loc		;off: 1560
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6478
	.data.b	8
	.section	.debug_str		;off: 5531
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6479
	.data.w	.Ldw_str_begin+5531
	.data.b	197,13
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 5540
	.data.b	79,99,117,95,83,101,116,80,105,110,65,99,116,105,111,110,0
	.section	.debug_info		;off: 6496
	.data.w	.Ldw_str_begin+5540
	.data.b	187,14
	.data.b	29
	.data.b	1
	.data.w	Ocu_SetPinAction
	.data.w	__ghs_eofn_Ocu_SetPinAction
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
	.data.w	Ocu_SetPinAction
	.data.w	__ghs_eofn_Ocu_SetPinAction-Ocu_SetPinAction
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2958
	.data.b	0,5,2
	.data.w	Ocu_SetPinAction
	.data.b	6
	.data.b	3
	.data.b	191,14
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
	.data.w	.LDWlin19
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	44
	.data.b	12
	.data.b	108
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	12
	.data.b	139
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	59
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	28
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6527
	.data.b	22
	.section	.debug_str		;off: 5557
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6528
	.data.w	.Ldw_str_begin+5557
	.data.b	189,14
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1579
	.section	.debug_loc		;off: 1579
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

	.section	.debug_info		;off: 6545
	.data.b	22
	.section	.debug_str		;off: 5571
	.data.b	79,117,116,112,117,116,65,99,116,105,111,110,0
	.section	.debug_info		;off: 6546
	.data.w	.Ldw_str_begin+5571
	.data.b	190,14
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+2549
	.data.b	0
	.data.w	.Ldw_loc_begin+1609
	.section	.debug_loc		;off: 1609
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	81
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6563
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 5584
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6573
	.data.w	.Ldw_str_begin+5584
	.data.b	193,14
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1639
	.section	.debug_loc		;off: 1639
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6591
	.data.b	7
	.section	.debug_str		;off: 5591
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6592
	.data.w	.Ldw_str_begin+5591
	.data.b	194,14
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1658
	.section	.debug_loc		;off: 1658
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6610
	.data.b	7
	.section	.debug_str		;off: 5607
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6611
	.data.w	.Ldw_str_begin+5607
	.data.b	195,14
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1677
	.section	.debug_loc		;off: 1677
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6629
	.data.b	7
	.section	.debug_str		;off: 5629
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 6630
	.data.w	.Ldw_str_begin+5629
	.data.b	196,14
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1696
	.section	.debug_loc		;off: 1696
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6648
	.data.b	7
	.section	.debug_str		;off: 5648
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 6649
	.data.w	.Ldw_str_begin+5648
	.data.b	197,14
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1715
	.section	.debug_loc		;off: 1715
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6667
	.data.b	8
	.section	.debug_str		;off: 5659
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6668
	.data.w	.Ldw_str_begin+5659
	.data.b	199,14
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5668
	.data.b	79,99,117,95,71,101,116,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 6685
	.data.w	.Ldw_str_begin+5668
	.data.b	181,15
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.w	Ocu_GetCounter
	.data.w	__ghs_eofn_Ocu_GetCounter
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_GetCounter
	.data.w	__ghs_eofn_Ocu_GetCounter-Ocu_GetCounter
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3075
	.data.b	0,5,2
	.data.w	Ocu_GetCounter
	.data.b	6
	.data.b	3
	.data.b	184,15
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
	.data.w	.LDWlin21
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	44
	.data.b	12
	.data.b	60
	.data.b	3
	.data.b	3
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6720
	.data.b	22
	.section	.debug_str		;off: 5683
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6721
	.data.w	.Ldw_str_begin+5683
	.data.b	183,15
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1734
	.section	.debug_loc		;off: 1734
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

	.section	.debug_info		;off: 6738
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	7
	.section	.debug_str		;off: 5697
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6748
	.data.w	.Ldw_str_begin+5697
	.data.b	186,15
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1764
	.section	.debug_loc		;off: 1764
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6766
	.data.b	8
	.section	.debug_str		;off: 5704
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6767
	.data.w	.Ldw_str_begin+5704
	.data.b	187,15
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 5720
	.data.b	67,111,117,110,116,101,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6782
	.data.w	.Ldw_str_begin+5720
	.data.b	188,15
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1783
	.section	.debug_loc		;off: 1783
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6800
	.data.b	8
	.section	.debug_str		;off: 5733
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 6801
	.data.w	.Ldw_str_begin+5733
	.data.b	189,15
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 5742
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 6816
	.data.w	.Ldw_str_begin+5742
	.data.b	191,15
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5751
	.data.b	79,99,117,95,83,101,116,65,98,115,111,108,117,116,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 6833
	.data.w	.Ldw_str_begin+5751
	.data.b	254,15
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.w	Ocu_SetAbsoluteThreshold
	.data.w	__ghs_eofn_Ocu_SetAbsoluteThreshold
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_SetAbsoluteThreshold
	.data.w	__ghs_eofn_Ocu_SetAbsoluteThreshold-Ocu_SetAbsoluteThreshold
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3137
	.data.b	0,5,2
	.data.w	Ocu_SetAbsoluteThreshold
	.data.b	6
	.data.b	3
	.data.b	131,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	44
	.data.b	12
	.data.b	108
	.data.b	75
	.data.b	220
	.data.b	28
	.data.b	28
	.data.b	59
	.data.b	76
	.data.b	76
	.data.b	12
	.data.b	29
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	77
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 6868
	.data.b	22
	.section	.debug_str		;off: 5776
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 6869
	.data.w	.Ldw_str_begin+5776
	.data.b	128,16
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+1802
	.section	.debug_loc		;off: 1802
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

	.section	.debug_info		;off: 6886
	.data.b	22
	.section	.debug_str		;off: 5790
	.data.b	82,101,102,101,114,101,110,99,101,86,97,108,117,101,0
	.section	.debug_info		;off: 6887
	.data.w	.Ldw_str_begin+5790
	.data.b	129,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+1832
	.section	.debug_loc		;off: 1832
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	81
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6904
	.data.b	22
	.section	.debug_str		;off: 5805
	.data.b	65,98,115,111,108,117,116,101,86,97,108,117,101,0
	.section	.debug_info		;off: 6905
	.data.w	.Ldw_str_begin+5805
	.data.b	130,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+1862
	.section	.debug_loc		;off: 1862
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	82
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6922
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	7
	.section	.debug_str		;off: 5819
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 6932
	.data.w	.Ldw_str_begin+5819
	.data.b	133,16
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1892
	.section	.debug_loc		;off: 1892
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6950
	.data.b	7
	.section	.debug_str		;off: 5826
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 6951
	.data.w	.Ldw_str_begin+5826
	.data.b	134,16
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1911
	.section	.debug_loc		;off: 1911
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6969
	.data.b	7
	.section	.debug_str		;off: 5842
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 6970
	.data.w	.Ldw_str_begin+5842
	.data.b	135,16
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1930
	.section	.debug_loc		;off: 1930
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 6988
	.data.b	7
	.section	.debug_str		;off: 5864
	.data.b	67,117,114,114,101,110,116,67,111,117,110,116,101,114,0
	.section	.debug_info		;off: 6989
	.data.w	.Ldw_str_begin+5864
	.data.b	136,16
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1949
	.section	.debug_loc		;off: 1949
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7007
	.data.b	7
	.section	.debug_str		;off: 5879
	.data.b	73,110,116,101,114,118,97,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7008
	.data.w	.Ldw_str_begin+5879
	.data.b	137,16
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1968
	.section	.debug_loc		;off: 1968
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7026
	.data.b	7
	.section	.debug_str		;off: 5894
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 7027
	.data.w	.Ldw_str_begin+5894
	.data.b	138,16
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1987
	.section	.debug_loc		;off: 1987
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7045
	.data.b	7
	.section	.debug_str		;off: 5903
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 7046
	.data.w	.Ldw_str_begin+5903
	.data.b	139,16
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2006
	.section	.debug_loc		;off: 2006
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7064
	.data.b	7
	.section	.debug_str		;off: 5922
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 7065
	.data.w	.Ldw_str_begin+5922
	.data.b	140,16
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2025
	.section	.debug_loc		;off: 2025
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7083
	.data.b	8
	.section	.debug_str		;off: 5933
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7084
	.data.w	.Ldw_str_begin+5933
	.data.b	147,16
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 5942
	.data.b	79,99,117,95,83,101,116,82,101,108,97,116,105,118,101,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 7101
	.data.w	.Ldw_str_begin+5942
	.data.b	130,17
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.w	Ocu_SetRelativeThreshold
	.data.w	__ghs_eofn_Ocu_SetRelativeThreshold
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_SetRelativeThreshold
	.data.w	__ghs_eofn_Ocu_SetRelativeThreshold-Ocu_SetRelativeThreshold
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3244
	.data.b	0,5,2
	.data.w	Ocu_SetRelativeThreshold
	.data.b	6
	.data.b	3
	.data.b	134,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	60
	.data.b	60
	.data.b	12
	.data.b	93
	.data.b	76
	.data.b	236
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	107
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	28
	.data.b	76
	.data.b	45
	.data.b	92
	.data.b	12
	.data.b	27
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 7136
	.data.b	22
	.section	.debug_str		;off: 5967
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7137
	.data.w	.Ldw_str_begin+5967
	.data.b	132,17
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+2044
	.section	.debug_loc		;off: 2044
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	80
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7154
	.data.b	22
	.section	.debug_str		;off: 5981
	.data.b	82,101,108,97,116,105,118,101,86,97,108,117,101,0
	.section	.debug_info		;off: 7155
	.data.w	.Ldw_str_begin+5981
	.data.b	133,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2396
	.data.b	0
	.data.w	.Ldw_loc_begin+2074
	.section	.debug_loc		;off: 2074
	.data.w	.LDW07
	.data.w	.LDW17
	.data.b	1,0
	.data.b	81
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7172
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	7
	.section	.debug_str		;off: 5995
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7182
	.data.w	.Ldw_str_begin+5995
	.data.b	136,17
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2104
	.section	.debug_loc		;off: 2104
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7200
	.data.b	7
	.section	.debug_str		;off: 6002
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7201
	.data.w	.Ldw_str_begin+6002
	.data.b	137,17
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2123
	.section	.debug_loc		;off: 2123
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7219
	.data.b	7
	.section	.debug_str		;off: 6018
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7220
	.data.w	.Ldw_str_begin+6018
	.data.b	138,17
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2142
	.section	.debug_loc		;off: 2142
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7238
	.data.b	7
	.section	.debug_str		;off: 6040
	.data.b	67,111,109,112,97,114,101,86,97,108,117,101,0
	.section	.debug_info		;off: 7239
	.data.w	.Ldw_str_begin+6040
	.data.b	139,17
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2161
	.section	.debug_loc		;off: 2161
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7257
	.data.b	7
	.section	.debug_str		;off: 6053
	.data.b	82,101,102,101,114,101,110,99,101,86,97,108,117,101,0
	.section	.debug_info		;off: 7258
	.data.w	.Ldw_str_begin+6053
	.data.b	140,17
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2180
	.section	.debug_loc		;off: 2180
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7276
	.data.b	7
	.section	.debug_str		;off: 6068
	.data.b	69,114,114,86,97,108,117,101,0
	.section	.debug_info		;off: 7277
	.data.w	.Ldw_str_begin+6068
	.data.b	141,17
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2599
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2200
	.section	.debug_loc		;off: 2200
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7295
	.data.b	8
	.section	.debug_str		;off: 6077
	.data.b	67,111,117,110,116,101,114,86,97,108,117,101,82,101,97,100,48,0
	.section	.debug_info		;off: 7296
	.data.w	.Ldw_str_begin+6077
	.data.b	142,17
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 6095
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 7311
	.data.w	.Ldw_str_begin+6095
	.data.b	143,17
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2219
	.section	.debug_loc		;off: 2219
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7329
	.data.b	7
	.section	.debug_str		;off: 6104
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 7330
	.data.w	.Ldw_str_begin+6104
	.data.b	144,17
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2238
	.section	.debug_loc		;off: 2238
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7348
	.data.b	7
	.section	.debug_str		;off: 6123
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 7349
	.data.w	.Ldw_str_begin+6123
	.data.b	145,17
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2257
	.section	.debug_loc		;off: 2257
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7367
	.data.b	8
	.section	.debug_str		;off: 6134
	.data.b	68,101,116,82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 7368
	.data.w	.Ldw_str_begin+6134
	.data.b	147,17
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 6149
	.data.b	79,99,117,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 7385
	.data.w	.Ldw_str_begin+6149
	.data.b	144,18
	.data.b	29
	.data.b	1
	.data.w	Ocu_DisableNotification
	.data.w	__ghs_eofn_Ocu_DisableNotification
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_DisableNotification
	.data.w	__ghs_eofn_Ocu_DisableNotification-Ocu_DisableNotification
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3363
	.data.b	0,5,2
	.data.w	Ocu_DisableNotification
	.data.b	6
	.data.b	3
	.data.b	147,18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	44
	.data.b	13
	.data.b	172
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7416
	.data.b	22
	.section	.debug_str		;off: 6173
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7417
	.data.w	.Ldw_str_begin+6173
	.data.b	146,18
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+2276
	.section	.debug_loc		;off: 2276
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

	.section	.debug_info		;off: 7434
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 6187
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7444
	.data.w	.Ldw_str_begin+6187
	.data.b	149,18
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2306
	.section	.debug_loc		;off: 2306
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7462
	.data.b	8
	.section	.debug_str		;off: 6194
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7463
	.data.w	.Ldw_str_begin+6194
	.data.b	150,18
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 6210
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7478
	.data.w	.Ldw_str_begin+6210
	.data.b	151,18
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2325
	.section	.debug_loc		;off: 2325
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7496
	.data.b	8
	.section	.debug_str		;off: 6232
	.data.b	68,101,116,82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 7497
	.data.w	.Ldw_str_begin+6232
	.data.b	154,18
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 6247
	.data.b	79,99,117,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 7514
	.data.w	.Ldw_str_begin+6247
	.data.b	211,18
	.data.b	29
	.data.b	1
	.data.w	Ocu_EnableNotification
	.data.w	__ghs_eofn_Ocu_EnableNotification
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_EnableNotification
	.data.w	__ghs_eofn_Ocu_EnableNotification-Ocu_EnableNotification
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3424
	.data.b	0,5,2
	.data.w	Ocu_EnableNotification
	.data.b	6
	.data.b	3
	.data.b	214,18
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
	.data.w	.LDWlin29
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	44
	.data.b	13
	.data.b	172
	.data.b	29
	.data.b	43
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7545
	.data.b	22
	.section	.debug_str		;off: 6270
	.data.b	67,104,97,110,110,101,108,78,117,109,98,101,114,0
	.section	.debug_info		;off: 7546
	.data.w	.Ldw_str_begin+6270
	.data.b	213,18
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2384
	.data.b	0
	.data.w	.Ldw_loc_begin+2344
	.section	.debug_loc		;off: 2344
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

	.section	.debug_info		;off: 7563
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	7
	.section	.debug_str		;off: 6284
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7573
	.data.w	.Ldw_str_begin+6284
	.data.b	216,18
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2374
	.section	.debug_loc		;off: 2374
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7591
	.data.b	8
	.section	.debug_str		;off: 6291
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7592
	.data.w	.Ldw_str_begin+6291
	.data.b	217,18
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 6307
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7607
	.data.w	.Ldw_str_begin+6307
	.data.b	218,18
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2393
	.section	.debug_loc		;off: 2393
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7625
	.data.b	8
	.section	.debug_str		;off: 6329
	.data.b	68,101,116,82,101,116,117,114,110,86,97,108,117,101,0
	.section	.debug_info		;off: 7626
	.data.w	.Ldw_str_begin+6329
	.data.b	220,18
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1126
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 6344
	.data.b	79,99,117,95,71,116,109,95,65,116,111,109,95,67,111,109,112,97,114,101,77,97,116,99,104,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 7643
	.data.w	.Ldw_str_begin+6344
	.data.b	145,19
	.data.b	29
	.data.b	1
	.data.w	Ocu_Gtm_Atom_CompareMatch_ISRHandler
	.data.w	__ghs_eofn_Ocu_Gtm_Atom_CompareMatch_ISRHandler
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Ocu_Gtm_Atom_CompareMatch_ISRHandler
	.data.w	__ghs_eofn_Ocu_Gtm_Atom_CompareMatch_ISRHandler-Ocu_Gtm_Atom_CompareMatch_ISRHandler
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3481
	.data.b	0,5,2
	.data.w	Ocu_Gtm_Atom_CompareMatch_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	149,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	12
	.data.b	107
	.data.b	13
	.data.b	91
	.data.b	43
	.data.b	12
	.data.b	107
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	43
	.data.b	75
	.data.b	60
	.data.b	77
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	91
	.data.b	12
	.data.b	60
	.data.b	59
	.data.b	11
	.data.b	3
	.data.b	1
	.data.b	2
	.data.b	68
	.data.b	1
	.data.b	28
	.data.b	59
	.data.b	13
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	28
	.data.b	43
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
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
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 7674
	.data.b	22
	.section	.debug_str		;off: 6381
	.data.b	77,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7675
	.data.w	.Ldw_str_begin+6381
	.data.b	147,19
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.w	.Ldw_loc_begin+2412
	.section	.debug_loc		;off: 2412
	.data.w	.LDW97
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7692
	.data.b	22
	.section	.debug_str		;off: 6393
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7693
	.data.w	.Ldw_str_begin+6393
	.data.b	148,19
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.w	.Ldw_loc_begin+2431
	.section	.debug_loc		;off: 2431
	.data.w	.LDW97
	.data.w	.LDW08
	.data.b	1,0
	.data.b	81
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7710
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	7
	.section	.debug_str		;off: 6401
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 7720
	.data.w	.Ldw_str_begin+6401
	.data.b	151,19
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1305
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2461
	.section	.debug_loc		;off: 2461
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7738
	.data.b	7
	.section	.debug_str		;off: 6408
	.data.b	67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,0
	.section	.debug_info		;off: 7739
	.data.w	.Ldw_str_begin+6408
	.data.b	152,19
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2480
	.section	.debug_loc		;off: 2480
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7757
	.data.b	7
	.section	.debug_str		;off: 6424
	.data.b	73,110,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7758
	.data.w	.Ldw_str_begin+6424
	.data.b	153,19
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2499
	.section	.debug_loc		;off: 2499
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7776
	.data.b	7
	.section	.debug_str		;off: 6434
	.data.b	73,110,116,69,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7777
	.data.w	.Ldw_str_begin+6434
	.data.b	154,19
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2518
	.section	.debug_loc		;off: 2518
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7795
	.data.b	7
	.section	.debug_str		;off: 6446
	.data.b	76,111,99,97,108,67,104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 7796
	.data.w	.Ldw_str_begin+6446
	.data.b	155,19
	.data.b	28
	.data.b	1
	.data.w	.Ldw_begin+315
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2537
	.section	.debug_loc		;off: 2537
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7814
	.data.b	7
	.section	.debug_str		;off: 6468
	.data.b	65,98,115,111,108,117,116,101,86,97,108,117,101,0
	.section	.debug_info		;off: 7815
	.data.w	.Ldw_str_begin+6468
	.data.b	156,19
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2556
	.section	.debug_loc		;off: 2556
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7833
	.data.b	7
	.section	.debug_str		;off: 6482
	.data.b	72,87,99,104,97,110,110,101,108,79,98,106,101,99,116,80,116,114,0
	.section	.debug_info		;off: 7834
	.data.w	.Ldw_str_begin+6482
	.data.b	157,19
	.data.b	30
	.data.b	1
	.data.w	.Ldw_begin+279
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2575
	.section	.debug_loc		;off: 2575
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7852
	.data.b	7
	.section	.debug_str		;off: 6501
	.data.b	84,105,109,101,98,97,115,101,0
	.section	.debug_info		;off: 7853
	.data.w	.Ldw_str_begin+6501
	.data.b	158,19
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+2072
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2594
	.section	.debug_loc		;off: 2594
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7871
	.data.b	7
	.section	.debug_str		;off: 6510
	.data.b	79,99,117,95,82,101,103,82,101,116,0
	.section	.debug_info		;off: 7872
	.data.w	.Ldw_str_begin+6510
	.data.b	159,19
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1066
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2613
	.section	.debug_loc		;off: 2613
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7890
	.data.b	8
	.section	.debug_str		;off: 6521
	.data.b	79,102,102,115,101,116,0
	.section	.debug_info		;off: 7891
	.data.w	.Ldw_str_begin+6521
	.data.b	160,19
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1078
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 6528
	.data.b	76,111,103,105,99,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 7906
	.data.w	.Ldw_str_begin+6528
	.data.b	161,19
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1102
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2632
	.section	.debug_loc		;off: 2632
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 7924
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
	.data.b	69
	.data.b	2
	.data.b	3
	.data.b	33
	.data.b	3
	.data.b	1
	.data.b	39
	.data.b	79,67,85,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	40
	.data.b	79,67,85,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	41
	.data.b	79,67,85,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	43
	.data.b	79,67,85,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	44
	.data.b	79,67,85,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	45
	.data.b	79,67,85,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	47
	.data.b	79,67,85,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	49
	.data.b	79,67,85,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,49,50,53,85,41,0
	.data.b	1
	.data.b	61
	.data.b	79,67,85,95,68,69,95,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	68
	.data.b	79,67,85,95,83,69,84,95,80,73,78,95,65,67,84,73,79,78,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	75
	.data.b	79,67,85,95,83,69,84,95,80,73,78,95,83,84,65,84,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	82
	.data.b	79,67,85,95,71,69,84,95,67,79,85,78,84,69,82,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	89
	.data.b	79,67,85,95,83,69,84,95,65,66,83,79,76,85,84,69,95,84,72,82,69,83,72,79,76,68,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	96
	.data.b	79,67,85,95,83,69,84,95,82,69,76,65,84,73,86,69,95,84,72,82,69,83,72,79,76,68,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	103
	.data.b	79,67,85,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	134,1
	.data.b	79,67,85,95,78,79,84,73,70,73,67,65,84,73,79,78,95,83,85,80,80,79,82,84,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	136,1
	.data.b	79,67,85,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	138,1
	.data.b	79,67,85,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	143,1
	.data.b	79,67,85,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,48,32,40,50,85,41,0
	.data.b	1
	.data.b	145,1
	.data.b	79,67,85,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,49,32,40,50,85,41,0
	.data.b	1
	.data.b	147,1
	.data.b	79,67,85,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	149,1
	.data.b	79,67,85,95,77,65,88,95,67,72,65,78,78,69,76,95,84,79,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	1
	.data.b	151,1
	.data.b	79,67,85,95,77,65,88,95,67,72,65,78,78,69,76,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	34
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	5
	.data.b	3
	.data.b	43
	.data.b	6
	.data.b	3
	.data.b	25
	.data.b	7
	.data.b	3
	.data.b	31
	.data.b	8
	.data.b	1
	.data.b	228,1
	.data.b	79,67,85,95,65,80,80,76,95,68,65,84,65,32,0
	.data.b	1
	.data.b	248,1
	.data.b	79,67,85,95,67,79,68,69,32,0
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
	.data.b	1
	.data.b	152,3
	.data.b	70,85,78,67,95,80,50,86,65,82,40,114,101,116,116,121,112,101,44,112,116,114,99,108,97,115,115,44,109,101,109,99,108,97,115,115,41,32,112,116,114,99,108,97,115,115,32,114,101,116,116,121,112,101,32,42,109,101,109,99
	.data.b	108,97,115,115,0
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	11
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
	.data.b	45
	.data.b	12
	.data.b	3
	.data.b	39
	.data.b	13
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	14
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
	.data.b	46
	.data.b	34
	.data.b	3
	.data.b	33
	.data.b	35
	.data.b	4
	.data.b	1
	.data.b	39
	.data.b	71,84,77,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	213,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	215,1
	.data.b	36
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
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	49
	.data.b	37
	.data.b	3
	.data.b	33
	.data.b	38
	.data.b	1
	.data.b	158,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,1
	.data.b	36
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
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	34
	.data.b	39
	.data.b	1
	.data.b	86
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	88
	.data.b	36
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
	.data.b	195,1
	.data.b	71,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	197,1
	.data.b	36
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	44
	.data.b	71,84,77,95,79,67,85,95,83,76,67,84,82,76,95,78,79,67,72,65,78,71,69,32,40,40,117,105,110,116,56,41,48,120,48,48,41,0
	.data.b	1
	.data.b	114
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	116
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	182,2
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	184,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	56
	.data.b	79,67,85,95,72,73,71,72,32,71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,72,73,71,72,0
	.data.b	4
	.data.b	1
	.data.b	39
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	40
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	46
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	47
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	41
	.data.b	1
	.data.b	32
	.data.b	79,67,85,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	33
	.data.b	79,67,85,95,77,79,68,85,76,69,95,73,68,32,40,49,50,53,85,41,0
	.data.b	1
	.data.b	34
	.data.b	79,67,85,95,73,78,83,84,65,78,67,69,95,73,68,32,40,48,85,41,0
	.data.b	1
	.data.b	37
	.data.b	79,67,85,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	38
	.data.b	79,67,85,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	39
	.data.b	79,67,85,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	42
	.data.b	79,67,85,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	43
	.data.b	79,67,85,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	44
	.data.b	79,67,85,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	4
	.data.b	1
	.data.b	48
	.data.b	79,67,85,95,65,84,79,77,95,67,79,85,78,84,69,82,95,82,65,78,71,69,95,77,65,83,75,32,40,48,120,70,70,70,70,70,70,85,41,0
	.data.b	1
	.data.b	50
	.data.b	79,67,85,95,84,66,85,95,66,79,82,68,69,82,95,80,65,83,84,95,70,85,84,85,82,69,32,40,48,120,56,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	54
	.data.b	79,67,85,95,69,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,50,85,41,0
	.data.b	1
	.data.b	56
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,73,78,86,65,76,73,68,95,67,72,65,78,78,69,76,32,40,40,117,105,110,116,56,41,48,120,48,51,85,41,0
	.data.b	1
	.data.b	58
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,73,78,86,65,76,73,68,95,83,84,65,84,69,32,40,40,117,105,110,116,56,41,48,120,48,52,85,41,0
	.data.b	1
	.data.b	60
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,73,78,86,65,76,73,68,95,65,67,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,48,53,85,41,0
	.data.b	1
	.data.b	62
	.data.b	79,67,85,95,69,95,78,79,95,86,65,76,73,68,95,78,79,84,73,70,32,40,40,117,105,110,116,56,41,48,120,48,54,85,41,0
	.data.b	1
	.data.b	64
	.data.b	79,67,85,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,48,120,48,55,85,41,0
	.data.b	1
	.data.b	66
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,48,56,85,41,0
	.data.b	1
	.data.b	68
	.data.b	79,67,85,95,69,95,66,85,83,89,32,40,40,117,105,110,116,56,41,48,120,48,57,85,41,0
	.data.b	1
	.data.b	70
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,78,79,95,80,73,78,32,40,40,117,105,110,116,56,41,48,120,48,65,85,41,0
	.data.b	1
	.data.b	72
	.data.b	79,67,85,95,69,95,73,78,73,84,95,70,65,73,76,69,68,32,40,40,117,105,110,116,56,41,48,120,48,66,85,41,0
	.data.b	1
	.data.b	76
	.data.b	79,67,85,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,40,117,105,110,116,56,41,48,120,69,48,85,41,0
	.data.b	1
	.data.b	78
	.data.b	79,67,85,95,69,95,67,79,82,69,95,67,72,65,78,78,69,76,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,69,49,85,41,0
	.data.b	1
	.data.b	80
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,82,69,70,95,86,65,76,85,69,32,40,40,117,105,110,116,56,41,48,120,69,50,85,41,0
	.data.b	1
	.data.b	82
	.data.b	79,67,85,95,69,95,80,65,82,65,77,95,67,79,77,80,65,82,69,95,86,65,76,85,69,32,40,40,117,105,110,116,56,41,48,120,69,51,85,41,0
	.data.b	1
	.data.b	84
	.data.b	79,67,85,95,69,95,87,82,73,84,69,95,82,69,71,73,83,84,69,82,32,40,40,117,105,110,116,56,41,48,120,69,52,85,41,0
	.data.b	1
	.data.b	88
	.data.b	79,67,85,95,83,73,68,95,73,78,73,84,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	90
	.data.b	79,67,85,95,83,73,68,95,68,69,73,78,73,84,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	92
	.data.b	79,67,85,95,83,73,68,95,83,84,65,82,84,67,72,65,78,78,69,76,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	94
	.data.b	79,67,85,95,83,73,68,95,83,84,79,80,67,72,65,78,78,69,76,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	96
	.data.b	79,67,85,95,83,73,68,95,83,69,84,80,73,78,83,84,65,84,69,32,40,48,120,48,52,85,41,0
	.data.b	1
	.data.b	98
	.data.b	79,67,85,95,83,73,68,95,83,69,84,80,73,78,65,67,84,73,79,78,32,40,48,120,48,53,85,41,0
	.data.b	1
	.data.b	100
	.data.b	79,67,85,95,83,73,68,95,71,69,84,67,79,85,78,84,69,82,32,40,48,120,48,54,85,41,0
	.data.b	1
	.data.b	102
	.data.b	79,67,85,95,83,73,68,95,83,69,84,65,66,83,79,76,85,84,69,84,72,82,69,83,72,79,76,68,32,40,48,120,48,55,85,41,0
	.data.b	1
	.data.b	104
	.data.b	79,67,85,95,83,73,68,95,83,69,84,82,69,76,65,84,73,86,69,84,72,82,69,83,72,79,76,68,32,40,48,120,48,56,85,41,0
	.data.b	1
	.data.b	106
	.data.b	79,67,85,95,83,73,68,95,71,69,84,86,69,82,83,73,79,78,73,78,70,79,32,40,48,120,48,57,85,41,0
	.data.b	1
	.data.b	108
	.data.b	79,67,85,95,83,73,68,95,68,73,83,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,32,40,48,120,48,65,85,41,0
	.data.b	1
	.data.b	110
	.data.b	79,67,85,95,83,73,68,95,69,78,65,66,76,69,78,79,84,73,70,73,67,65,84,73,79,78,32,40,48,120,48,66,85,41,0
	.data.b	1
	.data.b	113
	.data.b	79,67,85,95,83,73,68,95,71,84,77,95,65,84,79,77,95,67,79,77,80,65,82,69,77,65,84,67,72,95,73,83,72,65,78,68,76,69,82,32,40,48,120,69,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	73
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
	.data.b	74
	.data.b	43
	.data.b	4
	.data.b	1
	.data.b	115
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	117
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	128,1
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	130,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,1
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	136,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	147,1
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	149,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	152,1
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	154,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	160,49
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	163,49
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	165,1
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,50,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	167,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	170,1
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	172,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	211,57
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	214,57
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	183,1
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,51,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	185,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	189,1
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	191,1
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	131,2
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	133,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	136,2
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	138,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	144,2
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	146,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	154,2
	.data.b	79,67,85,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,32,35,35,32,69,120
	.data.b	99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	158,2
	.data.b	79,67,85,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,32,35,35,32,69,120,99,108
	.data.b	117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	161,2
	.data.b	79,67,85,95,71,69,84,95,67,72,65,78,78,69,76,95,82,65,77,95,80,84,82,40,67,111,114,101,73,100,44,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,41,32,38,40,40,79,99,117,95,67,111,114,101,67
	.data.b	104,97,110,110,101,108,83,116,97,116,117,115,80,116,114,91,67,111,114,101,73,100,93,41,91,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,93,41,0
	.data.b	1
	.data.b	166,2
	.data.b	79,67,85,95,71,69,84,95,67,72,65,78,78,69,76,95,69,86,69,78,84,40,67,111,114,101,73,100,44,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,41,32,40,79,99,117,95,67,111,110,102,105,103,80,116,114
	.data.b	45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,79,99,117,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,97,110,73,110,67,111,114,101,73,110,100,101
	.data.b	120,93,46,69,118,101,110,116,41,0
	.data.b	1
	.data.b	171,2
	.data.b	79,67,85,95,71,69,84,95,67,72,65,78,78,69,76,95,73,78,68,69,88,95,73,78,95,67,79,82,69,40,76,111,103,105,99,67,104,97,110,110,101,108,73,100,41,32,40,79,99,117,95,67,111,110,102,105,103,80,116,114
	.data.b	45,62,79,99,117,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,91,76,111,103,105,99,67,104,97,110,110,101,108,73,100,93,46,73,110,100,101,120,73,110,67,111,114,101,41,0
	.data.b	1
	.data.b	176,2
	.data.b	79,67,85,95,71,69,84,95,67,72,65,78,78,69,76,95,77,65,88,95,86,65,76,85,69,40,67,111,114,101,73,100,44,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,41,32,40,79,99,117,95,67,111,110,102,105
	.data.b	103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,79,99,117,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,97,110,73,110,67,111,114,101
	.data.b	73,110,100,101,120,93,46,77,97,120,67,111,117,110,116,101,114,86,97,108,117,101,41,0
	.data.b	1
	.data.b	181,2
	.data.b	79,67,85,95,71,69,84,95,67,72,65,78,78,69,76,95,78,79,84,73,70,89,95,80,84,82,40,67,111,114,101,73,100,44,67,104,97,110,73,110,67,111,114,101,73,110,100,101,120,41,32,40,79,99,117,95,67,111,110,102
	.data.b	105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,79,99,117,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,91,67,104,97,110,73,110,67,111,114
	.data.b	101,73,110,100,101,120,93,46,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,41,0
	.data.b	1
	.data.b	187,2
	.data.b	79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	189,2
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,79,67,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	129,20
	.data.b	79,67,85,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	131,20
	.data.b	40
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 431
	.data.b	0
