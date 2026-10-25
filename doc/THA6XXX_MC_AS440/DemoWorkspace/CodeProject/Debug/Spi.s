	.section ".sdk_text_asil_d","ax"
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682576..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetCommonDetStatus:
.LDW01:
	push	{r4,lr}
.LDW11:
	ldr	r3,.L277
	ldr	r2,[r3,r0 lsl 2]
	mov	r4,1
	cmp	r2,0
	moveq	r2,r1
	moveq	r3,163
	beq	.L266
.L75:
	ldr	r2,[r2,12]
	ldr	r2,[r2]
	cmp	r2,0
	bne	.L78
.L79:
	mov	r2,r1
	mov	r3,26
.L266:

	mov	r1,0
	b	.L267
.L78:
	ldr	r3,.L278
	ldr	r2,[r3]
	ldr	r0,[r2,r0 lsl 2]
	cmp	r0,0
	bne	.L81
.L82:
	mov	r2,r1
	mov	r3,162
	mov	r1,r0
.L267:

	mov	r0,83
.L279:

	bl	Det_ReportError
	b	.L77
.L81:
	mov	r4,0
.L77:
	mov	r0,r4
.LDW21:
.L281:

	pop	{r4,pc}
__ghs_eofn_Spi_GetCommonDetStatus:
	.endf	Spi_GetCommonDetStatus
	.endf	Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local

;CoreId	r0	param
;ServiceId	r1	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	4
Spi_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_ConfigPtr:	.space	4
	.endo	Spi_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_ConfigPtr
	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Spi_CoreStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_CoreStatus:
	.data.w	Spi_StatusSetCore0
	.data.w	Spi_StatusSetCore1
	.space	8
	.endo	Spi_CoreStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_CoreStatus
	.section ".ghcalltbl",""
	.align	4
.L280:	.data.w	.L279
	.endo	.L280
	.section ".ghrettbl",""
	.align	4
.L282:	.data.w	.L281
	.endo	.L282
	.section ".mcal_const_asil_d_unspecified_core0","a"
	.align	4
Spi_StatusSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_StatusSetCore0:
	.data.w	Spi_SequenceStateCore0
	.data.w	Spi_PhyUnitStateCore0
	.data.w	Spi_DeviceStateCore0
	.data.w	Spi_InitStatusCore0
	.data.w	Spi_AsyncModeCore0
	.data.w	Spi_SyncTransferStatusCore0
	.endo	Spi_StatusSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_StatusSetCore0
	.section ".mcal_const_asil_d_unspecified_core1","a"
	.align	4
Spi_StatusSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_StatusSetCore1:
	.data.w	Spi_SequenceStateCore1
	.data.w	Spi_PhyUnitStateCore1
	.data.w	Spi_DeviceStateCore1
	.data.w	Spi_InitStatusCore1
	.data.w	Spi_AsyncModeCore1
	.data.w	Spi_SyncTransferStatusCore1
	.endo	Spi_StatusSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_StatusSetCore1
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
	.align	4
Spi_SequenceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_SequenceStateCore0:	.space	16
	.endo	Spi_SequenceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_SequenceStateCore0
Spi_PhyUnitStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_PhyUnitStateCore0:	.space	28
	.endo	Spi_PhyUnitStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_PhyUnitStateCore0
Spi_DeviceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_DeviceStateCore0:	.space	40
	.endo	Spi_DeviceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_DeviceStateCore0
Spi_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_InitStatusCore0:	.space	4
	.endo	Spi_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_InitStatusCore0
Spi_AsyncModeCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_AsyncModeCore0:	.space	4
	.endo	Spi_AsyncModeCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_AsyncModeCore0
Spi_SyncTransferStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_SyncTransferStatusCore0:	.space	2
	.endo	Spi_SyncTransferStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_SyncTransferStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
	.align	4
Spi_SequenceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_SequenceStateCore1:	.space	16
	.endo	Spi_SequenceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_SequenceStateCore1
Spi_PhyUnitStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_PhyUnitStateCore1:	.space	28
	.endo	Spi_PhyUnitStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_PhyUnitStateCore1
Spi_DeviceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_DeviceStateCore1:	.space	40
	.endo	Spi_DeviceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_DeviceStateCore1
Spi_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_InitStatusCore1:	.space	4
	.endo	Spi_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_InitStatusCore1
Spi_AsyncModeCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_AsyncModeCore1:	.space	4
	.endo	Spi_AsyncModeCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_AsyncModeCore1
Spi_SyncTransferStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_SyncTransferStatusCore1:	.space	2
	.endo	Spi_SyncTransferStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_SyncTransferStatusCore1
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetSeqDetStatus:
.LDW31:
	push	{r4,lr}
.LDW41:
	ldr	r12,.L277
	ldr	r3,[r12,r0 lsl 2]
	mov	r4,1
	cmp	r3,0
	bne	.L285
.L286:
	mov	r2,r1
	mov	r3,163
.L627:

.L628:

.L629:

	mov	r1,0
	b	.L630
.L285:
	ldr	r3,[r3,12]
	ldr	r3,[r3]
	cmp	r3,0
	moveq	r2,r1
	moveq	r3,26
	beq	.L627
.L288:
	ldr	r12,.L278
	ldr	r3,[r12]
	ldr	r0,[r3,r0 lsl 2]
	cmp	r0,0
	moveq	r2,r1
	moveq	r3,162
	beq	.L626
.L291:
	ldrb	r12,[r3,16]
	cmp	r2,r12
	ldrlo	r3,[r3,24]
	ldrblo	r12,[r0]
	ldrblo	r3,[r3,r2]
	cmplo	r3,r12
	movhs	r2,r1
	movhs	r3,12
	bhs	.L629
.L297:
	ldr	r0,[r0,8]
	lsl	r3,r3,4
	ldrb	r12,[r3,r0]
	cmp	r2,r12
	movne	r2,r1
	movne	r3,164
	bne	.L628
.L300:
	add	r0,r3,r0
	ldrh	r0,[r0,2]
	cmp	r0,0
	bne	.L303
.L304:
	mov	r2,r1
	mov	r3,160
.L626:

	mov	r1,r0
.L630:

	mov	r0,83
.L646:

	bl	Det_ReportError
	b	.L287
.L303:
	mov	r4,0
.L287:
	mov	r0,r4
.LDW51:
.L648:

	pop	{r4,pc}
__ghs_eofn_Spi_GetSeqDetStatus:
	.endf	Spi_GetSeqDetStatus
	.endf	Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;CorexSeqIdx	r3	local
;CurrentCoreConfigPtr	r0	local

;CoreId	r0	param
;ServiceId	r1	param
;Sequence	r2	param

	.section ".ghcalltbl",""
.L647:	.data.w	.L646
	.endo	.L647
	.section ".ghrettbl",""
.L649:	.data.w	.L648
	.endo	.L649
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetJobDetStatus:
.LDW61:
	push	{r4,lr}
.LDW71:
	ldr	r12,.L277
	ldr	r3,[r12,r0 lsl 2]
	mov	r4,1
	cmp	r3,0
	bne	.L652
.L653:
	mov	r2,r1
	mov	r3,163
.L979:

.L980:

.L981:

	mov	r1,0
	b	.L982
.L652:
	ldr	r3,[r3,12]
	ldr	r3,[r3]
	cmp	r3,0
	moveq	r2,r1
	moveq	r3,26
	beq	.L979
.L655:
	ldr	r12,.L278
	ldr	r3,[r12]
	ldr	r0,[r3,r0 lsl 2]
	cmp	r0,0
	moveq	r2,r1
	moveq	r3,162
	beq	.L978
.L658:
	ldrh	r12,[r3,18]
	cmp	r2,r12
	ldrlo	r3,[r3,28]
	lsllo	r12,r2,1
	ldrhlo	r3,[r12,r3]
	ldrhlo	r12,[r0,2]
	cmplo	r3,r12
	movhs	r2,r1
	movhs	r3,11
	bhs	.L981
.L664:
	ldr	r12,[r0,12]
	rsb	r3,r3,r3 lsl 2
	lsl	r0,r3,3
	ldrh	r3,[r12,r0]
	cmp	r2,r3
	movne	r2,r1
	movne	r3,165
	bne	.L980
.L667:
	add	r0,r0,r12
	ldrb	r0,[r0,5]
	cmp	r0,0
	bne	.L670
.L671:
	mov	r2,r1
	mov	r3,161
.L978:

	mov	r1,r0
.L982:

	mov	r0,83
.L998:

	bl	Det_ReportError
	b	.L654
.L670:
	mov	r4,0
.L654:
	mov	r0,r4
.LDW81:
.L1000:

	pop	{r4,pc}
__ghs_eofn_Spi_GetJobDetStatus:
	.endf	Spi_GetJobDetStatus
	.endf	Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;JobIndex	r3	local
;CurrentCoreConfigPtr	r0	local

;CoreId	r0	param
;ServiceId	r1	param
;Job	r2	param

	.section ".ghcalltbl",""
.L999:	.data.w	.L998
	.endo	.L999
	.section ".ghrettbl",""
.L1001:	.data.w	.L1000
	.endo	.L1001
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetChannelDetStatus:
.LDW91:
	push	{r4,lr}
.LDW02:
	ldr	r12,.L277
	ldr	r3,[r12,r0 lsl 2]
	mov	r4,1
	cmp	r3,0
	bne	.L1004
.L1005:
	mov	r2,r1
	mov	r3,163
.L1294:

.L1295:

.L1296:

	mov	r1,0
	b	.L1297
.L1004:
	ldr	r3,[r3,12]
	ldr	r3,[r3]
	cmp	r3,0
	moveq	r2,r1
	moveq	r3,26
	beq	.L1294
.L1007:
	ldr	r12,.L278
	ldr	r3,[r12]
	ldr	r0,[r3,r0 lsl 2]
	cmp	r0,0
	bne	.L1010
.L1011:
	mov	r2,r1
	mov	r3,162
	mov	r1,r0
.L1297:

	mov	r0,83
.L1311:

	bl	Det_ReportError
	b	.L1006
.L1010:
	ldrb	r12,[r3,20]
	cmp	r2,r12
	ldrlo	r3,[r3,32]
	ldrblo	r12,[r0,4]
	ldrblo	r3,[r3,r2]
	cmplo	r3,r12
	movhs	r2,r1
	movhs	r3,10
	bhs	.L1296
.L1016:
	ldr	r0,[r0,16]
	ldrb	r0,[r0,r3 lsl 5]
	cmp	r2,r0
	movne	r2,r1
	movne	r3,166
	bne	.L1295
.L1019:
	mov	r4,0
.L1006:
	mov	r0,r4
.LDW12:
.L1313:

	pop	{r4,pc}
__ghs_eofn_Spi_GetChannelDetStatus:
	.endf	Spi_GetChannelDetStatus
	.endf	Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;CoreChIdx	r3	local
;RetStatus	r4	local
;CurrentCoreConfigPtr	r0	local

;CoreId	r0	param
;ServiceId	r1	param
;Channel	r2	param

	.section ".ghcalltbl",""
.L1312:	.data.w	.L1311
	.endo	.L1312
	.section ".ghrettbl",""
.L1314:	.data.w	.L1313
	.endo	.L1314
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetPhyUnitDetStatus:
.LDW22:
	push	{r4,lr}
.LDW32:
	ldr	r12,.L277
	ldr	r3,[r12,r0 lsl 2]
	mov	r4,1
	cmp	r3,0
	bne	.L1317
.L1318:
	mov	r2,r1
	mov	r3,163
.L1614:

.L1615:

.L1616:

	mov	r1,0
	b	.L1617
.L1317:
	ldr	r3,[r3,12]
	ldr	r3,[r3]
	cmp	r3,0
	moveq	r2,r1
	moveq	r3,26
	beq	.L1614
.L1320:
	ldr	r12,.L278
	ldr	r3,[r12]
	ldr	r0,[r3,r0 lsl 2]
	cmp	r0,0
	bne	.L1323
.L1324:
	mov	r2,r1
	mov	r3,162
	mov	r1,r0
.L1617:

	mov	r0,83
.L1631:

	bl	Det_ReportError
	b	.L1319
.L1323:
	ldrb	r12,[r3,21]
	cmp	r2,r12
	ldrlo	r3,[r3,40]
	ldrblo	r12,[r0,6]
	ldrblo	r3,[r3,r2]
	cmplo	r3,r12
	movhs	r2,r1
	movhs	r3,14
	bhs	.L1616
.L1329:
	ldr	r0,[r0,24]
	ldrb	r0,[r0,r3 lsl 4]
	cmp	r2,r0
	movne	r2,r1
	movne	r3,168
	bne	.L1615
.L1332:
	mov	r4,0
.L1319:
	mov	r0,r4
.LDW42:
.L1633:

	pop	{r4,pc}
__ghs_eofn_Spi_GetPhyUnitDetStatus:
	.endf	Spi_GetPhyUnitDetStatus
	.endf	Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;CorePhyUnitIdx	r3	local
;CurrentCoreConfigPtr	r0	local

;CoreId	r0	param
;ServiceId	r1	param
;PhyUnit	r2	param

	.section ".ghcalltbl",""
.L1632:	.data.w	.L1631
	.endo	.L1632
	.section ".ghrettbl",""
.L1634:	.data.w	.L1633
	.endo	.L1634
	.data
	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetDriverStatus:
.LDW52:
	mov	r1,r0
.LDW62:
	mov	r0,2
	mov	r2,0
	b	.L1640
.L1639:
	ldr	r3,.L277
	ldr	r3,[r3,r1 lsl 2]
	lsl	r12,r12,3
	ldr	r3,[r3,4]
	sub	r0,r12,r2 lsr 24
	add	r0,r3,r0 lsl 2
	add	r2,r2,1<<24
	ldr	r0,[r0,4]
.L1640:
	ldr	r3,.L278
	ldr	r3,[r3]
	ldr	r3,[r3,r1 lsl 2]
	ldrb	r3,[r3,6]
	lsr	r12,r2,24
	cmp	r12,r3
.L1760:

	reths	
	cmp	r0,2
	beq	.L1639
.LDW72:
.L1762:

	ret	
__ghs_eofn_Spi_GetDriverStatus:
	.endf	Spi_GetDriverStatus
	.endf	Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

.L277:	.data.w	Spi_CoreStatus
	.endo	.L277

.L278:	.data.w	Spi_ConfigPtr
	.endo	.L278

;SpiStatus	r0	local

;CoreId	r1	param

	.section ".ghrettbl",""
.L1761:	.data.w	.L1760
	.endo	.L1761
.L1763:	.data.w	.L1762
	.endo	.L1763
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.global	Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncGetPhyUnitStatus:
.LDW82:
	push	{r4,lr}
	mov	r1,r0
.LDW92:
	mov	r0,2
	mov	r3,0
.L1773:
	ldr	r12,.L278
	ldr	r12,[r12]
	ldr	r12,[r12,r1 lsl 2]
	ldrb	r12,[r12,6]
	lsr	r2,r3,24
	cmp	r2,r12
.L1928:

	pophs	{r4,pc}
	ldr	r4,.L277
	ldr	r12,[r4,r1 lsl 2]
	rsb	r2,r2,r2 lsl 3
	ldr	r12,[r12,4]
	add	r2,r12,r2 lsl 2
	ldr	r12,[r2,4]
	cmp	r12,3
	ldrbeq	r2,[r2,1]
	cmpeq	r2,1
	moveq	r0,r12
	addne	r3,r3,1<<24
	bne	.L1773
.LDW03:
.L1930:

	pop	{r4,pc}
__ghs_eofn_Spi_AsyncGetPhyUnitStatus:
	.endf	Spi_AsyncGetPhyUnitStatus
	.endf	Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;SpiStatus	r0	local

;CoreId	r1	param

	.section ".ghrettbl",""
.L1929:	.data.w	.L1928
	.endo	.L1929
.L1931:	.data.w	.L1930
	.endo	.L1931
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
	.global	Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_SyncStartTransmit:
.LDW13:
	push	{r4-r10,lr}
	ldr	r8,.L278
	mov	r9,r0
.LDW23:
	ldr	r0,[r8]
	ldr	r2,[r0,r9 lsl 2]
	ldr	r0,[r0,24]
	ldrb	r0,[r0,r1]
	ldr	r1,[r2,8]
	mov	r10,1
	add	r0,r1,r0 lsl 4
	ldrh	r4,[r0,2]
	ldr	r5,[r0,4]
.L1934:
	cmp	r4,0
	beq	.L1935
	ldr	r0,[r8]
	ldrh	r2,[r5]
	ldr	r1,[r0,r9 lsl 2]
	ldr	r0,[r0,28]
	lsl	r2,r2,1
	ldrh	r0,[r2,r0]
	ldr	r1,[r1,12]
	rsb	r0,r0,r0 lsl 2
	add	r6,r1,r0 lsl 3
.L2307:

	bl	SchM_Enter_Spi_SyncTransmit
	ldr	r0,[r8]
	ldrh	r1,[r5]
	ldr	r3,[r0,28]
	ldr	r2,[r0,r9 lsl 2]
	lsl	r1,r1,1
	ldrh	r1,[r1,r3]
	ldr	r2,[r2,12]
	rsb	r1,r1,r1 lsl 2
	ldr	r0,[r0,40]
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,20]
	mov	r2,1
	str	r2,[r1]
	ldrb	r1,[r6,2]
	ldr	r2,.L277
	ldrb	r0,[r0,r1]
	ldr	r7,[r2,r9 lsl 2]
	rsb	r1,r0,r0 lsl 3
	ldr	r0,[r7,4]
	add	r0,r0,r1 lsl 2
	mov	r1,3
	str	r1,[r0,4]
.L2309:

	bl	SchM_Exit_Spi_SyncTransmit
	ldr	r0,[r8]
	ldrb	r1,[r6,2]
	ldr	r0,[r0,40]
	ldrb	r0,[r0,r1]
	add	r1,r0,r0 lsl 2
	ldr	r0,[r7,8]
	add	r0,r0,r1 lsl 3
	ldrh	r1,[r6]
	str	r6,[r0,4]
	mov	r0,r9
.L2311:

	bl	Spi_SyncTransmitJob
	and	r10,r0,1
.L2313:

	bl	SchM_Enter_Spi_SyncTransmit
	ldr	r0,[r8]
	ldrb	r2,[r6,2]
	ldr	r1,[r0,40]
	ldrb	r1,[r1,r2]
	rsb	r2,r1,r1 lsl 3
	ldr	r1,[r7,4]
	cmp	r10,0
	add	r1,r1,r2 lsl 2
	mov	r2,2
	str	r2,[r1,4]
	lsleq	r1,r4,16
	beq	.L1944
	ldrh	r2,[r5],2
	ldr	r1,[r0,r9 lsl 2]
	ldr	r0,[r0,28]
	lsl	r2,r2,1
	ldrh	r0,[r2,r0]
	ldr	r1,[r1,12]
	rsb	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 3
	ldr	r0,[r0,20]
	sub	r4,r4,1
	mov	r1,0
	uxth	r4,r4
	str	r1,[r0]
.L2315:

	bl	SchM_Exit_Spi_SyncTransmit
	ldr	r0,[r6,12]
	cmp	r0,0
.L2317:

	blxne	r0
	b	.L1934
.L1944:
	ldrh	r2,[r5]
	ldr	r12,[r0,28]
	ldr	r3,[r0,r9 lsl 2]
	lsl	r2,r2,1
	ldrh	r2,[r2,r12]
	ldr	r3,[r3,12]
	rsb	r2,r2,r2 lsl 2
	add	r2,r3,r2 lsl 3
	ldr	r2,[r2,20]
	mov	r3,2
	sub	r1,r1,1<<16
	str	r3,[r2]
	lsrs	r2,r1,16
	addne	r5,r5,2
	bne	.L1944
.L2319:

	bl	SchM_Exit_Spi_SyncTransmit
.L1935:
	mov	r0,r10
.LDW33:
.L2321:

	pop	{r4-r10,pc}
__ghs_eofn_Spi_SyncStartTransmit:
	.endf	Spi_SyncStartTransmit
	.endf	Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r10	local
;JobNumberInSeq	r4	local
;JobCfgPtr	r6	local
;JobIndexPtr	r5	local
;SeqCfgPtr	r0	local

;CoreId	r9	param
;Sequence	r1	param

	.section ".ghcalltbl",""
.L2308:	.data.w	.L2307
	.endo	.L2308
.L2310:	.data.w	.L2309
	.endo	.L2310
.L2312:	.data.w	.L2311
	.endo	.L2312
.L2314:	.data.w	.L2313
	.endo	.L2314
.L2316:	.data.w	.L2315
	.endo	.L2316
.L2318:	.data.w	.L2317
	.endo	.L2318
.L2320:	.data.w	.L2319
	.endo	.L2320
	.section ".ghrettbl",""
.L2322:	.data.w	.L2321
	.endo	.L2322
	.data
	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.8:
	.endo	..gh.f.a.1.e.8
	.global	Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_SyncTransmitJob:
.LDW43:
	push	{r4-fp,lr}
	sub	sp,sp,76
	ldr	fp,.L278
.LDW53:
	lsl	r1,r1,1
	ldr	r2,[fp]
	str	r0,[sp,28]
	ldr	r12,[r2,28]
	ldr	r3,[r2,r0 lsl 2]
	ldrh	r1,[r1,r12]
	ldr	r3,[r3,12]
	rsb	r1,r1,r1 lsl 2
	ldr	r8,[r2,48]
	add	r4,r3,r1 lsl 3
	ldrb	r1,[r4,5]
	ldr	r3,[r4,8]
	strb	r1,[sp,7]
	ldrb	r1,[r4,2]
	str	r3,[sp,24]
	ldr	r8,[r8,r1 lsl 2]
	ldrh	r1,[r4]
.L3193:

	bl	Spi_GetDataTotalNumOfJob
	mov	r1,r0
	mov	r0,r8
.L3195:

	bl	Espi_Hal_SetMoveCounterDataLength
	ldr	r2,[fp]
	ldr	r1,[sp,28]
	ldrb	r3,[r4,4]
	ldr	r1,[r2,r1 lsl 2]
	ldr	r2,[r2,36]
	ldr	r1,[r1,20]
	ldrb	r2,[r2,r3]
	mov	r3,44
	smlabb	r6,r2,r3,r1
	ldr	r1,[r6,12]
	mov	r5,r0
	add	r0,sp,32
	mov	r2,24
	str	r1,[sp,68]
	add	r1,r6,16
.L3197:

	bl	memmove
	mov	r2,5
	mov	r9,0
	mov	r1,7
	add	r0,sp,56
	stm	r0,{r1-r2,r9}
	ldr	r0,[r6,40]
	add	r1,sp,32
	ldr	r0,[r0,28]
.L3199:

	bl	Espi_Hal_CalculateChannelDynamicConfiguration
	mov	r7,r0
	mov	r0,r8
	mov	r1,r9
.L3201:

	bl	Espi_Hal_SetDma
	ldr	r1,[r6,4]
	cmp	r1,0
	ldrbeq	r1,[r4,3]
	and	r5,r5,r0
	cmpeq	r1,0
	ldrheq	r0,[r6,8]
.L3203:

	bleq	Dio_FlipChannel
.L3205:

	bl	SchM_Enter_Spi_SyncTransmit
	b	.L2328
.L2330:
	ldrb	r0,[sp,7]
	ldr	r1,[sp,28]
	ldr	r10,[sp,24]
	sub	r2,r0,r5
	strb	r2,[sp,7]
	ldr	r2,[fp]
	ldrb	r3,[r10],1
	ldr	r1,[r2,r1 lsl 2]
	ldr	r2,[r2,32]
	ldr	r1,[r1,16]
	ldrb	r2,[r2,r3]
	str	r10,[sp,24]
	add	r9,r1,r2 lsl 5
	ldr	r1,[r9,8]
	bic	r7,r7,250<<20
	ldr	r12,[r9,24]
	orr	r7,r7,r1 lsl 23
	ldr	r1,[r9,28]
	ldrh	r12,[r12]
	ldrb	r2,[r4,3]
	mov	r0,r8
	orr	r7,r7,r1 lsl 21
	strh	r12,[sp,14]
	mov	r1,r7
.L3207:

	bl	Espi_Hal_WriteConfiguration
	mov	r0,0
	str	r0,[sp,16]
	str	r0,[sp,20]
	b	.L2331
.L2336:
	ldrh	r0,[sp,14]
	cmp	r0,15
	movls	r10,r0
	movhi	r10,15
	strb	r10,[sp,6]
	ldrb	r10,[sp,6]
	mov	r1,0
	sub	r2,r0,r10
	mov	r0,r8
	strh	r2,[sp,14]
	mov	r2,r10
.L3209:

	bl	Espi_Hal_SetFifoLevel
	and	r5,r0,1
	b	.L2337
.L2339:
	ldr	r2,[r6,4]
	cmp	r2,0
	ldrbeq	r2,[r4,3]
	cmpeq	r2,1
	ldrheq	r0,[r6,8]
.L3211:

	bleq	Dio_FlipChannel
	ldr	r1,[r9,20]
	ldr	r3,[r1,4]
	ldr	r2,[r9,12]
	mov	r0,r8
	cmp	r3,0
	bne	.L2343
.L3213:

	bl	Espi_Hal_SendData
	b	.L2345
.L2343:
	ldr	r12,[sp,16]
	add	r1,r12,r3
.L3215:

	bl	Espi_Hal_SendData
	ldr	lr,[sp,16]
	add	lr,lr,r0
	str	lr,[sp,16]
.L2345:
	ldr	r2,[r6,4]
	cmp	r2,0
	ldrbeq	r2,[r4,3]
	cmpeq	r2,1
	bne	.L2346
	ldrb	r0,[r4,2]
.L3217:

	bl	Spi_WaitPhaseStatus
	and	r5,r0,1
	ldrh	r0,[r6,8]
.L3219:

	bl	Dio_FlipChannel
.L2346:
	sub	r10,r10,1
	uxtb	r10,r10
.L2337:
	cmp	r5,0
	beq	.L2350
	cmp	r10,0
	bne	.L2339
	ldrb	r1,[r4,2]
	ldr	r0,[sp,28]
.L3221:

	bl	Spi_SyncWaitTransFinish
	and	r5,r0,1
	b	.L2352
.L2354:
	ldr	r3,[r9,20]
	ldr	r3,[r3,8]
	ldr	r2,[r9,12]
	mov	r0,r8
	cmp	r3,0
	bne	.L2355
	add	r1,sp,8
.L3223:

	bl	Espi_Hal_ReceiveData
	b	.L2357
.L2355:
	ldr	r10,[sp,20]
	add	r1,r10,r3
.L3225:

	bl	Espi_Hal_ReceiveData
	add	r12,r10,r0
	str	r12,[sp,20]
.L2357:
	ldrb	r0,[sp,6]
	sub	r1,r0,1
	strb	r1,[sp,6]
.L2352:
	ldrb	r0,[sp,6]
	cmp	r0,0
	cmpne	r5,0
	bne	.L2354
.L2350:
	ldr	r1,.L3192
	mov	r0,r8
.L3227:

	bl	Espi_Hal_ClearFlagStatus
.L2331:
	ldrh	r0,[sp,14]
	cmp	r0,0
	beq	.L2328
	cmp	r5,1
	beq	.L2336
.L2328:
	ldrb	r0,[sp,7]
	cmp	r0,0
	beq	.L2329
	cmp	r5,1
	beq	.L2330
.L2329:
.L3229:

	bl	SchM_Exit_Spi_SyncTransmit
	ldr	r1,[r6,4]
	cmp	r1,0
	ldrbeq	r1,[r4,3]
	cmpeq	r1,0
	ldrheq	r0,[r6,8]
.L3231:

	bleq	Dio_FlipChannel
	mov	r0,r5
.LDW63:
	add	sp,sp,76
.L3233:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_SyncTransmitJob:
	.endf	Spi_SyncTransmitJob
	.endf	Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;Level	[sp,6]	local
;Threshold	r10	local
;TxBufferIndex	[sp,16]	local
;RxBufferIndex	[sp,20]	local
;ChDynamicCfg	r7	local
;TempRxBuffer	[sp,8]	local
;RetStatus	r5	local
;ChNumberInJob	[sp,7]	local
;FramesCount	[sp,14]	local
;PhyUnit	r8	local
;ChannelIndexPtr	[sp,24]	local
;ChannelCfgPtr	r9	local
;ExDeviceCfgPtr	r6	local
;ChDynamicConfig	[sp,32]	local
;JobCfgPtr	r4	local

;CoreId	[sp,28]	param
;Job	r1	param

	.section ".ghcalltbl",""
.L3194:	.data.w	.L3193
	.endo	.L3194
.L3196:	.data.w	.L3195
	.endo	.L3196
.L3198:	.data.w	.L3197
	.endo	.L3198
.L3200:	.data.w	.L3199
	.endo	.L3200
.L3202:	.data.w	.L3201
	.endo	.L3202
.L3204:	.data.w	.L3203
	.endo	.L3204
.L3206:	.data.w	.L3205
	.endo	.L3206
.L3208:	.data.w	.L3207
	.endo	.L3208
.L3210:	.data.w	.L3209
	.endo	.L3210
.L3212:	.data.w	.L3211
	.endo	.L3212
.L3214:	.data.w	.L3213
	.endo	.L3214
.L3216:	.data.w	.L3215
	.endo	.L3216
.L3218:	.data.w	.L3217
	.endo	.L3218
.L3220:	.data.w	.L3219
	.endo	.L3220
.L3222:	.data.w	.L3221
	.endo	.L3222
.L3224:	.data.w	.L3223
	.endo	.L3224
.L3226:	.data.w	.L3225
	.endo	.L3226
.L3228:	.data.w	.L3227
	.endo	.L3228
.L3230:	.data.w	.L3229
	.endo	.L3230
.L3232:	.data.w	.L3231
	.endo	.L3232
	.section ".ghrettbl",""
.L3234:	.data.w	.L3233
	.endo	.L3234
	.data
	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.global	__caller.Espi_Hal_ReceiveData.i.ppi

	.global	__caller.Espi_Hal_ReceiveData.i.ppi

	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_SendData.i.ppi

	.global	__caller.Espi_Hal_SendData.i.ppi

	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_SetFifoLevel.i.pii

	.global	__caller.Espi_Hal_WriteConfiguration.v.pii

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_SetDma.i.pi

	.global	__caller.Espi_Hal_CalculateChannelDynamicConfiguration.i.ip

	.global	__caller.Espi_Hal_SetMoveCounterDataLength.i.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.global	Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_SyncWaitTransFinish:
.LDW73:
	push	{r4-r7,r9,fp,lr}
	sub	sp,sp,12
	str	r0,[sp,4]
	mov	r0,0
	mov	r9,r1
.LDW83:
	strb	r0,[sp,3]
.L3456:

	bl	Rcc_Hal_GetStmClkFreq
.L3458:

	bl	__ftou64
	mov	r2,0x03e8
	mov	r3,0
.L3460:

	bl	__gh_mul64
	ldr	r2,.L3452
	mov	r3,0
.L3462:

	bl	__gh_udiv64
	mov	r2,0
	mov	r3,r2
	b	.L3453

.L3192:	.data.w	0x0007ffff
	.endo	.L3192

.L3452:	.data.w	0x000f4240
	.endo	.L3452

.L3453:

;line1811
..lin.3629b354..1b2c362b.0_1::
.LDWlin1:
..gh.beginasm.10:
	.endo	..gh.beginasm.10
MRRC p15, 0, r2, r3, c14

..gh.endasm.11:
	.endo	..gh.endasm.11

	adds	r4,r2,r0
	adc	r2,r3,r1
	mov	r5,r2
.L3246:
;line1817
..lin.3629b354..1b2c362b.0_2::
.LDWlin2:
..gh.beginasm.12:
	.endo	..gh.beginasm.12
MRRC p15, 0, r1, r2, c14

..gh.endasm.13:
	.endo	..gh.endasm.13

	mov	r7,r2
	ldr	r2,.L3454
	ldr	r0,[r2]
	ldr	r0,[r0,48]
	mov	fp,0
	mov	r6,r1
;line1819
..lin.3629b354..1b2c362b.0_3::
.LDWlin3:
	movw	r1,0x053f
	ldr	r0,[r0,r9 lsl 2]
.L3464:

	bl	Espi_Hal_GetFlagStatus
	cmp	r7,r5
	cmpeq	r6,r4
	bhs	.L3241
	cmp	r0,0
	beq	.L3246
.L3241:
	cmp	r0,1<<10
	moveq	r0,1
	strbeq	r0,[sp,3]
	beq	.L3251
	cmp	r7,r5
	cmpeq	r6,r4
	blo	.L3252
	mov	r3,233
	mov	r2,10
	mov	r1,fp
	mov	r0,83
.L3466:

	bl	Det_ReportRuntimeError
	b	.L3251
.L3252:
	mov	r1,r9
	ldr	r0,[sp,4]
.L3468:

	bl	Spi_IsrError
	ldr	r2,.L3454
	ldr	r0,[r2]
	ldr	r0,[r0,48]
	ldr	r1,.L3455
	ldr	r0,[r0,r9 lsl 2]
.L3470:

	bl	Espi_Hal_ClearFlagStatus
.L3251:
	ldrb	r0,[sp,3]
.LDW93:
	add	sp,sp,12
.L3472:

	pop	{r4-r7,r9,fp,pc}
__ghs_eofn_Spi_SyncWaitTransFinish:
	.endf	Spi_SyncWaitTransFinish
	.endf	Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	[sp,3]	local
;RegValue	r0	local
;TimeOutCount	r4	local
;CurrentCount	r6	local
;value	r2	local
;value	r6	local

;CoreId	[sp,4]	param
;PhyUnit	r9	param

	.section ".ghcalltbl",""
.L3457:	.data.w	.L3456
	.endo	.L3457
.L3459:	.data.w	.L3458
	.endo	.L3459
.L3461:	.data.w	.L3460
	.endo	.L3461
.L3463:	.data.w	.L3462
	.endo	.L3463
.L3465:	.data.w	.L3464
	.endo	.L3465
.L3467:	.data.w	.L3466
	.endo	.L3467
.L3469:	.data.w	.L3468
	.endo	.L3469
.L3471:	.data.w	.L3470
	.endo	.L3471
	.section ".ghrettbl",""
.L3473:	.data.w	.L3472
	.endo	.L3473
	.data
	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Espi_Hal_GetFlagStatus.i.pi

	.global	__caller.Rcc_Hal_GetStmClkFreq.f.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.14:
	.endo	..gh.f.a.1.e.14
	.global	Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncCheckJobLinkStatus:
.LDW04:
	push	{r4-fp,lr}
	ldr	r3,.L3454
.LDW14:
	ldr	r4,[r3]
	mov	r2,r0
	ldr	r5,[r4,r2 lsl 2]
	ldr	r8,[r4,24]
	ldr	r12,[r5,8]
	ldrb	r3,[r8,r1]
	add	r12,r12,r3 lsl 4
	ldrh	r9,[r12,2]
	mov	r0,0
	ldr	r12,[r12,4]
	mov	r3,r9
.L3485:
	cmp	r3,0
.L3768:

	popeq	{r4-fp,pc}
	ldrh	r10,[r12]
	ldr	r7,[r4,28]
	lsl	r10,r10,1
	ldrh	r10,[r10,r7]
	ldr	r6,[r5,12]
	rsb	r10,r10,r10 lsl 2
	add	r10,r6,r10 lsl 3
	ldr	r10,[r10,20]
	ldr	fp,[r10,4]
	cmp	fp,0
	ldreq	r7,.L3767
	ldreq	r6,[r7,r2 lsl 2]
	lslne	r1,r3,16
	ldrbeq	r7,[r8,r1]
	subeq	r3,r3,1
	ldreq	r6,[r6]
	addeq	r12,r12,2
	uxtheq	r3,r3
	addeq	r6,r6,r7 lsl 4
	streq	r6,[r10,4]
	beq	.L3485
	b	.L3482
.L3484:
	ldrh	r0,[r12,-2]!
	lsl	r0,r0,1
	ldrh	r0,[r0,r7]
	rsb	r0,r0,r0 lsl 2
	add	r1,r1,1<<16
	add	r2,r6,r0 lsl 3
	ldr	r0,[r2,20]
	mov	r2,0
	str	r2,[r0,4]
.L3482:
	cmp	r9,r1 lsr 16
	bhi	.L3484
	mov	r0,1
.LDW24:
.L3770:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_AsyncCheckJobLinkStatus:
	.endf	Spi_AsyncCheckJobLinkStatus
	.endf	Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r0	local
;JobNumberInSeq	r3	local
;JobIndexPtr	r12	local
;JobCfgPtr	r10	local
;SeqCfgPtr	r12	local

;CoreId	r2	param
;Sequence	r1	param

	.section ".ghrettbl",""
.L3769:	.data.w	.L3768
	.endo	.L3769
.L3771:	.data.w	.L3770
	.endo	.L3771
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.global	Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncScheduleJob:
.LDW34:
	push	{r2,r4-r9,lr}
	ldr	r8,.L3454
	mov	r5,r0
	ldr	r0,[r8]
	mov	r9,r1
.LDW44:
	lsl	r2,r1,1
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,28]
	ldrh	r0,[r2,r0]
	ldr	r1,[r1,12]
	rsb	r0,r0,r0 lsl 2
	mov	r6,0
	add	r7,r1,r0 lsl 3
.L3971:

	bl	SchM_Enter_Spi_AsyncTransmit
	ldr	r2,.L3767
	ldr	r0,[r8]
	ldr	r1,[r2,r5 lsl 2]
	ldrb	r2,[r7,2]
	ldr	r0,[r0,40]
	ldrb	r0,[r0,r2]
	ldr	r1,[r1,4]
	rsb	r0,r0,r0 lsl 3
	add	r2,r1,r0 lsl 2
	ldr	r3,[r2,4]
	mov	r1,r9
	mov	r0,r5
	cmp	r3,2
	bne	.L3774
	ldrb	r2,[r2]
	cmp	r2,1
	bne	.L3776
.L3973:

	bl	Spi_AsyncJobDmaTransfer
	mov	r6,r0
	b	.L3961
.L3776:
.L3975:

	bl	Spi_AsyncJobTransfer
.L3961:

	and	r4,r0,1
	b	.L3779
.L3774:
	mov	r4,1
.L3977:

	bl	Spi_AsyncLinkJobList
.L3779:
.L3979:

	bl	SchM_Exit_Spi_AsyncTransmit
	cmp	r6,1
	bne	.L3780
	ldr	r0,[r8]
	ldrb	r2,[r7,2]
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,40]
	ldr	r1,[r1,24]
	ldrb	r0,[r0,r2]
	add	r5,r1,r0 lsl 4
	ldrb	r0,[r5,2]
.L3981:

	bl	Dma_ChannelStart
	ldrb	r0,[r5,1]
.L3983:

	bl	Dma_ChannelStart
.L3780:
	mov	r0,r4
.LDW54:
.L3985:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Spi_AsyncScheduleJob:
	.endf	Spi_AsyncScheduleJob
	.endf	Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;JobCfgPtr	r7	local
;TriggerDmaFlag	r6	local
;PhyUnitCfgPtr	r5	local

;CoreId	r5	param
;Job	r9	param

	.section ".ghcalltbl",""
.L3972:	.data.w	.L3971
	.endo	.L3972
.L3974:	.data.w	.L3973
	.endo	.L3974
.L3976:	.data.w	.L3975
	.endo	.L3976
.L3978:	.data.w	.L3977
	.endo	.L3978
.L3980:	.data.w	.L3979
	.endo	.L3980
.L3982:	.data.w	.L3981
	.endo	.L3982
.L3984:	.data.w	.L3983
	.endo	.L3984
	.section ".ghrettbl",""
.L3986:	.data.w	.L3985
	.endo	.L3986
	.data
	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.16:
	.endo	..gh.f.a.1.e.16
	.global	Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncJobTransfer:
.LDW64:
	push	{r4-r10,lr}
	sub	sp,sp,40
	ldr	r6,.L3454
	ldr	r2,[r6]
	ldr	r12,[r2,28]
	ldr	r3,[r2,r0 lsl 2]
	lsl	r1,r1,1
	ldrh	r1,[r1,r12]
	ldr	r12,.L3767
	ldr	r3,[r3,12]
	ldr	r8,[r12,r0 lsl 2]
	rsb	r1,r1,r1 lsl 2
	ldr	r12,[r2,40]
	add	r5,r3,r1 lsl 3
	ldr	r1,[r5,20]
	ldrb	r4,[r5,2]
	mov	r3,1
	str	r3,[r1]
	ldrb	r2,[r12,r4]
	ldr	r1,[r8,4]
	rsb	r2,r2,r2 lsl 3
	mov	r7,3
	add	r2,r1,r2 lsl 2
	str	r7,[r2,4]
	ldrb	r2,[r12,r4]
.LDW74:
	rsb	r2,r2,r2 lsl 3
	mov	r7,r0
	add	r1,r1,r2 lsl 2
	strb	r3,[r1,1]
	ldrh	r1,[r5]
.L4202:

	bl	Spi_GetDataTotalNumOfJob
	ldr	r2,[r6]
	ldrb	r1,[r5,2]
	ldr	r2,[r2,48]
	ldr	r2,[r2,r1 lsl 2]
	mov	r1,r0
	mov	r0,r2
.L4204:

	bl	Espi_Hal_SetMoveCounterDataLength
	mov	r4,r0
	cmp	r0,1
	bne	.L3989
	ldr	r2,[r6]
	ldrb	r1,[r5,2]
	ldr	r0,[r2,40]
	ldrb	r0,[r0,r1]
	ldr	r4,[r8,8]
	add	r0,r0,r0 lsl 2
	add	r4,r4,r0 lsl 3
	ldr	r0,[r5,8]
	str	r5,[r4,4]
	mov	r9,0
	str	r0,[r4,16]
	ldrb	r0,[r5,5]
	ldr	r1,[r2,36]
	strb	r9,[r4,32]
	sub	r0,r0,1
	strb	r0,[r4,20]
	ldr	r0,[r2,r7 lsl 2]
	ldrb	r2,[r5,4]
	ldr	r0,[r0,20]
	ldrb	r1,[r1,r2]
	mov	r2,44
	smlabb	r10,r1,r2,r0
	ldr	r0,[r10,12]
	mov	r2,24
	add	r1,r10,16
	str	r0,[sp,36]
	mov	r0,sp
.L4206:

	bl	memmove
	mov	r1,5
	mov	r0,7
	add	r2,sp,24
	stm	r2,{r0-r1,r9}
	ldr	r0,[r10,40]
	mov	r1,sp
	ldr	r0,[r0,28]
.L4208:

	bl	Espi_Hal_CalculateChannelDynamicConfiguration
	str	r0,[r4,36]
	ldr	r0,[r10,4]
	cmp	r0,0
	ldrbeq	r0,[r5,3]
	cmpeq	r0,0
	ldrheq	r0,[r10,8]
.L4210:

	bleq	Dio_FlipChannel
	ldr	r0,[r8,16]
	ldr	r0,[r0]
	cmp	r0,1
	bne	.L3997
	ldr	r1,[r6]
	ldrb	r0,[r5,2]
	ldr	r1,[r1,48]
	mov	r2,1
	ldr	r0,[r1,r0 lsl 2]
	movw	r1,0x053f
.L4212:

	bl	Espi_Hal_SetInterrupt
	ands	r4,r0,1
	beq	.L3989
.L3997:
	ldr	r1,[r6]
	ldrb	r0,[r5,2]
	ldr	r1,[r1,48]
	ldr	r0,[r1,r0 lsl 2]
	mov	r1,r9
.L4214:

	bl	Espi_Hal_SetDma
	and	r4,r0,1
	ldrb	r1,[r5,2]
	mov	r0,r7
	b	.L4201

.L3454:	.data.w	Spi_ConfigPtr
	.endo	.L3454

.L3455:	.data.w	0x10000400
	.endo	.L3455

.L3767:	.data.w	Spi_CoreStatus
	.endo	.L3767

.L4201:

;line2161
..lin.3629b354..7539afce.0_4::
.LDWlin4:
	mov	r2,1
.L4216:

	bl	Spi_AsyncJobTransferChannel
	and	r4,r4,r0
.L3989:
	mov	r0,r4
.LDW84:
	add	sp,sp,40
.L4218:

	pop	{r4-r10,pc}
__ghs_eofn_Spi_AsyncJobTransfer:
	.endf	Spi_AsyncJobTransfer
	.endf	Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;DevStatePtr	r4	local
;ChDynamicConfig	[sp]	local
;ExDeviceCfgPtr	r10	local
;JobCfgPtr	r5	local

;CoreId	r7	param
;Job	r1	param

	.section ".ghcalltbl",""
.L4203:	.data.w	.L4202
	.endo	.L4203
.L4205:	.data.w	.L4204
	.endo	.L4205
.L4207:	.data.w	.L4206
	.endo	.L4207
.L4209:	.data.w	.L4208
	.endo	.L4209
.L4211:	.data.w	.L4210
	.endo	.L4211
.L4213:	.data.w	.L4212
	.endo	.L4213
.L4215:	.data.w	.L4214
	.endo	.L4215
.L4217:	.data.w	.L4216
	.endo	.L4217
	.section ".ghrettbl",""
.L4219:	.data.w	.L4218
	.endo	.L4219
	.data
	.global	__caller.Espi_Hal_SetDma.i.pi

	.global	__caller.Espi_Hal_SetInterrupt.i.pii

	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_CalculateChannelDynamicConfiguration.i.ip

	.global	__caller.Espi_Hal_SetMoveCounterDataLength.i.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.17:
	.endo	..gh.f.a.1.e.17
	.global	Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncJobDmaTransfer:
.LDW94:
	push	{r4-fp,lr}
	sub	sp,sp,100
	ldr	r7,.L3454
.LDW05:
	lsl	r1,r1,1
	ldr	r2,[r7]
	mov	r6,1
	ldr	r12,[r2,28]
	ldr	r3,[r2,r0 lsl 2]
	ldrh	r1,[r1,r12]
	ldr	r3,[r3,12]
	rsb	r1,r1,r1 lsl 2
	ldr	r2,[r2,40]
	add	r4,r3,r1 lsl 3
	ldr	r1,[r4,20]
	ldr	r3,.L3767
	str	r6,[r1]
	ldrb	r1,[r4,2]
	ldr	r3,[r3,r0 lsl 2]
	ldrb	r8,[r2,r1]
	ldr	r12,[r3,4]
	rsb	r8,r8,r8 lsl 3
	mov	r9,3
	add	r8,r12,r8 lsl 2
	str	r9,[r8,4]
	ldrb	r8,[r2,r1]
	rsb	r8,r8,r8 lsl 3
	add	r12,r12,r8 lsl 2
	strb	r6,[r12,1]
	ldrb	r1,[r2,r1]
	add	r2,r1,r1 lsl 2
	ldr	r1,[r3,8]
	mov	r5,0
	str	r0,[sp,16]
	add	r1,r1,r2 lsl 3
	str	r4,[r1,4]
	ldrh	r1,[r4]
.L4938:

	bl	Spi_GetDataTotalNumOfJob
	ldr	r2,[r7]
	ldrb	r1,[r4,2]
	ldr	r2,[r2,48]
	ldr	r2,[r2,r1 lsl 2]
	mov	r1,r0
	mov	r0,r2
.L4940:

	bl	Espi_Hal_SetMoveCounterDataLength
	cmp	r0,1
	bne	.L4258
	ldr	r2,[r7]
	ldr	fp,[sp,16]
	ldrb	r3,[r4,4]
	ldr	r1,[r2,fp lsl 2]
	ldr	r2,[r2,36]
	ldr	r1,[r1,20]
	ldrb	r2,[r2,r3]
	mov	r3,44
	smlabb	r9,r2,r3,r1
	ldr	r1,[r9,12]
	add	r0,sp,20
	str	r9,[sp,4]
	mov	r2,24
	str	r1,[sp,56]
	add	r1,r9,16
.L4942:

	bl	memmove
	mov	r2,5
	mov	r1,7
	add	r0,sp,44
	stm	r0,{r1-r2,r5}
	ldr	r0,[r9,40]
	add	r1,sp,20
	ldr	r0,[r0,28]
.L4944:

	bl	Espi_Hal_CalculateChannelDynamicConfiguration
	ldrb	r1,[r4,3]
	ldrb	r3,[r4,2]
	ldr	r2,[r7]
	str	r5,[sp,68]
	orr	r6,r0,r1
	ldr	r1,[r2,fp lsl 2]
	ldr	r2,[r2,40]
	ldr	r0,[r4,8]
	ldr	r1,[r1,24]
	str	r5,[sp,80]
	ldrb	r2,[r2,r3]
	str	r0,[sp,12]
	mov	r9,r5
	ldrb	r10,[r4,5]
	add	r8,r1,r2 lsl 4
	b	.L4227
.L4226:
	ldr	r2,[r7]
	ldr	r0,[sp,12]
	ldr	r3,[sp,16]
	ldr	r1,[r2,32]
	ldrb	r12,[r0],1
	ldr	r3,[r2,r3 lsl 2]
	ldrb	r1,[r1,r12]
	ldr	r3,[r3,16]
	bic	r6,r6,250<<20
	add	fp,r3,r1 lsl 5
	ldr	r1,[fp,8]
	ldr	r3,[r8,4]
	orr	r6,r6,r1 lsl 23
	ldr	r1,[fp,28]
	str	r0,[sp,12]
	orr	r6,r6,r1 lsl 21
	str	r6,[r3,r9 lsl 2]!
	ldr	r2,[r2,48]
	ldrb	r1,[r4,2]
	str	r5,[sp,76]
	strb	r5,[sp,94]
	ldrb	r0,[r8,1]
	ldr	r1,[r2,r1 lsl 2]
	ldr	r2,[r8,8]
	str	r3,[sp,60]
	str	r5,[sp,64]
	add	r1,r1,96
	str	r1,[sp,72]
	mov	r1,2
	str	r1,[sp,84]
	mov	r1,1
	add	r3,r9,r9 lsl 2
	strh	r1,[sp,92]
	lsl	r1,r3,3
	str	r1,[sp,8]
	add	r1,r1,r2
	add	r2,r1,20
	str	r2,[sp,88]
	add	r2,sp,60
.L4946:

	bl	Dma_LliMemberInsertManual
	ldr	r2,[fp,20]
	ldr	r12,[r2,4]
	mov	r5,r0
	cmp	r12,0
	beq	.L4228
	and	r2,r12,255<<24
	cmp	r2,1<<27
	ldreq	r2,.L4936
	addeq	r12,r12,r2
	mov	r2,1
	b	.L4233
.L4228:
	mov	r12,r2
	mov	r2,0
.L4233:
	ldr	r1,[r7]
	str	r2,[sp,64]
	ldrb	r2,[r4,2]
	ldr	r1,[r1,48]
	ldr	r1,[r1,r2 lsl 2]
	add	r1,r1,100
	str	r1,[sp,72]
	mov	r1,0
	str	r1,[sp,76]
	ldr	r1,[fp,24]
	ldrh	r1,[r1]
	strh	r1,[sp,92]
	ldr	r1,[fp,12]
	str	r12,[sp,60]
	cmp	r1,1
	moveq	r1,0
	beq	.L4236
	cmp	r1,2
	movne	r1,2
	moveq	r1,1
.L4236:
	str	r1,[sp,84]
	sub	r1,r10,1
	cmp	r1,r9
	ldrne	r1,[r8,8]
	ldrne	r0,[sp,8]
	moveq	r0,0
	addne	r1,r0,r1
	streq	r0,[sp,88]
	addne	r1,r1,40
	moveq	r1,1
	strne	r1,[sp,88]
	movne	r1,0
	ldr	r3,[r8,8]
	ldr	r0,[sp,8]
	add	r2,sp,60
	strb	r1,[sp,94]
	add	r3,r0,r3
	ldrb	r0,[r8,1]
	add	r1,r3,20
.L4948:

	bl	Dma_LliMemberInsertManual
	ldr	r2,[r7]
	ldrb	r1,[r4,2]
	ldr	r2,[r2,48]
	ldr	r1,[r2,r1 lsl 2]
	add	r1,r1,144
	str	r1,[sp,60]
	ldr	r1,[fp,20]
	mov	r3,0
	ldr	r1,[r1,8]
	orr	r5,r5,r0
	str	r3,[sp,64]
	cmp	r1,0
	movne	r2,1
	ldreq	r1,.L4937
	moveq	r2,r3
	str	r1,[sp,72]
	sub	r1,r10,1
	cmp	r1,r9
	str	r2,[sp,76]
	addne	r1,r9,r10 lsl 1
	ldrne	r2,[r8,8]
	addne	r1,r1,r1 lsl 2
	addne	r2,r2,r1 lsl 2
	streq	r3,[sp,88]
	addne	r1,r2,20
	moveq	r1,1
	strne	r1,[sp,88]
	movne	r1,r3
	ldr	r12,[r8,8]
	add	r3,r9,r10 lsl 1
	strb	r1,[sp,94]
	add	r3,r3,r3 lsl 2
	add	r2,sp,60
	ldrb	r0,[r8,2]
	add	r1,r12,r3 lsl 2
.L4950:

	bl	Dma_LliMemberInsertManual
	orr	r5,r5,r0
	add	r9,r9,1
	uxtb	r5,r5
	uxtb	r9,r9
.L4227:
	cmp	r9,r10
	bhs	.L4224
	cmp	r5,0
	beq	.L4226
.L4224:
	ldr	r1,[r8,8]
	ldrb	r0,[r8,1]
.L4952:

	bl	Dma_LliInsertCompleteManual
	ldr	r1,[r8,8]
	add	r0,r10,r10 lsl 2
	add	r1,r1,r0 lsl 3
	ldrb	r0,[r8,2]
.L4954:

	bl	Dma_LliInsertCompleteManual
	ldr	r0,[r7]
	ldrb	r1,[r4,2]
	ldr	r0,[r0,48]
	mov	r2,1
	ldr	r0,[r0,r1 lsl 2]
	movw	r1,0x013f
.L4956:

	bl	Espi_Hal_SetInterrupt
	and	r6,r0,1
	ldr	r0,[r7]
	ldrb	r1,[r4,2]
	ldr	r0,[r0,48]
	mov	r2,1
	ldr	r0,[r0,r1 lsl 2]
	mov	r1,0
.L4958:

	bl	Espi_Hal_SetFifoLevel
	and	r6,r6,r0
	ldr	r0,[r7]
	ldrb	r1,[r4,2]
	ldr	r0,[r0,48]
	ldr	r0,[r0,r1 lsl 2]
	mov	r1,1
.L4960:

	bl	Espi_Hal_SetDma
	ldr	r2,[r7]
	ldrb	r1,[r4,2]
	ldr	r2,[r2,48]
	ldr	r1,[r2,r1 lsl 2]
	ldr	r2,[r1,20]
	and	r6,r6,r0
	mov	r0,5
	mov	r3,r2
	bfi	r3,r0,26,4
	str	r3,[r1,20]
	str	r2,[r1,20]
	mov	r2,1<<9
	str	r2,[r1,64]
	ldr	r1,[r1,64]
	mov	r2,1
	and	r1,r1,1<<9
	cmp	r1,1<<9
	movne	r2,0
	tst	r6,r2
	beq	.L4258
	cmp	r5,0
	bne	.L4258
	ldr	r2,[sp,4]
	ldr	r1,[r2,4]
	cmp	r1,0
	ldrbeq	r1,[r4,3]
	mov	r6,1
	cmpeq	r1,0
	ldrheq	r0,[r2,8]
.L4962:

	bleq	Dio_FlipChannel
	b	.L4264
.L4258:
	mov	r6,0
.L4264:
	mov	r0,r6
.LDW15:
	add	sp,sp,100
.L4964:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_AsyncJobDmaTransfer:
	.endf	Spi_AsyncJobDmaTransfer
	.endf	Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r6	local
;RetResult	r5	local
;ChCount	r9	local
;ChannelTotalNum	r10	local
;ChDynamicCfg	r6	local
;ChannelIndexPtr	[sp,12]	local
;JobCfgPtr	r4	local
;ChannelCfgPtr	fp	local
;PhyUnitCfgPtr	r8	local
;ExDeviceCfgPtr	[sp,4]	local
;LliConfig	[sp,60]	local
;ChDynamicConfig	[sp,20]	local
;regValue	r2	local
;ret	r2	local

;CoreId	[sp,16]	param
;Job	r1	param

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
Spi_RxBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.::
Spi_RxBuffer:	.space	4
	.endo	Spi_RxBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.endo	Spi_RxBuffer
	.section ".ghcalltbl",""
.L4939:	.data.w	.L4938
	.endo	.L4939
.L4941:	.data.w	.L4940
	.endo	.L4941
.L4943:	.data.w	.L4942
	.endo	.L4943
.L4945:	.data.w	.L4944
	.endo	.L4945
.L4947:	.data.w	.L4946
	.endo	.L4947
.L4949:	.data.w	.L4948
	.endo	.L4949
.L4951:	.data.w	.L4950
	.endo	.L4951
.L4953:	.data.w	.L4952
	.endo	.L4953
.L4955:	.data.w	.L4954
	.endo	.L4955
.L4957:	.data.w	.L4956
	.endo	.L4957
.L4959:	.data.w	.L4958
	.endo	.L4959
.L4961:	.data.w	.L4960
	.endo	.L4961
.L4963:	.data.w	.L4962
	.endo	.L4963
	.section ".ghrettbl",""
.L4965:	.data.w	.L4964
	.endo	.L4965
	.data
	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_SetDma.i.pi

	.global	__caller.Espi_Hal_SetFifoLevel.i.pii

	.global	__caller.Espi_Hal_SetInterrupt.i.pii

	.global	__caller.Dma_LliInsertCompleteManual.i.ip

	.global	__caller.Dma_LliInsertCompleteManual.i.ip

	.global	__caller.Dma_LliMemberInsertManual.i.ipp

	.global	__caller.Dma_LliMemberInsertManual.i.ipp

	.global	__caller.Dma_LliMemberInsertManual.i.ipp

	.global	__caller.Espi_Hal_CalculateChannelDynamicConfiguration.i.ip

	.global	__caller.Espi_Hal_SetMoveCounterDataLength.i.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
__callee.Spi_DmaNotification.v.ii::
	.size	__callee.Spi_DmaNotification.v.ii,0
Spi_DmaNotification::
.LDW25:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW35:
	cmp	r1,1
.L5093:

	popne	{r4-r6,pc}
	ldr	r5,.L5090
	b	.L5091

.L4936:	.data.w	0x88400000
	.endo	.L4936

.L4937:	.data.w	Spi_RxBuffer
	.endo	.L4937

.L5090:	.data.w	Spi_ConfigPtr
	.endo	.L5090

.L5091:

;line2494
..lin.3629b354..1f914a69.0_5::
.LDWlin5:
..gh.beginasm.19:
	.endo	..gh.beginasm.19
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.20:
	.endo	..gh.endasm.20

	ldr	r0,[r5]
;line2497
..lin.3629b354..1f914a69.0_6::
.LDWlin6:
	ldr	r1,[r0,r2 lsl 2]
	mov	r4,r2
	ldr	r2,[r0,40]
	ldr	r0,[r0,44]
	ldrb	r0,[r0,r6]
	ldr	r1,[r1,24]
	ldrb	r0,[r2,r0]
	add	r0,r1,r0 lsl 4
	ldrb	r0,[r0,1]
.L5095:

	bl	Dma_GetChannelStatus
	tst	r0,1
.L5097:

	popeq	{r4-r6,pc}
	ldr	r0,[r5]
	ldr	r1,[r0,40]
	ldr	r0,[r0,44]
	ldrb	r0,[r0,r6]
	ldrb	r0,[r1,r0]
	ldr	r2,.L5092
	add	r1,r0,r0 lsl 2
	ldr	r0,[r2,r4 lsl 2]
	ldr	r0,[r0,8]
	add	r0,r0,r1 lsl 3
	ldr	r1,[r0,4]
	mov	r0,r4
	ldrh	r1,[r1]
.L5099:

	bl	Spi_AsyncJobTransferFinished
	movs	r1,r0
	moveq	r3,232
	moveq	r2,226
	moveq	r0,83
.L5101:

	bleq	Det_ReportRuntimeError
.LDW45:
.L5103:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_DmaNotification::
	.endf	Spi_DmaNotification
;CoreId	r4	local

;Channel	r6	param
;ChIntrEvt	r1	param

	.section ".ghrettbl",""
.L5094:	.data.w	.L5093
	.endo	.L5094
	.section ".ghcalltbl",""
.L5096:	.data.w	.L5095
	.endo	.L5096
	.section ".ghrettbl",""
.L5098:	.data.w	.L5097
	.endo	.L5098
	.section ".ghcalltbl",""
.L5100:	.data.w	.L5099
	.endo	.L5100
.L5102:	.data.w	.L5101
	.endo	.L5102
	.section ".ghrettbl",""
.L5104:	.data.w	.L5103
	.endo	.L5104
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Dma_GetChannelStatus.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
	.global	Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncLinkJobList:
.LDW55:
	push	{r4-r7,lr}
.LDW65:
	ldr	r3,.L5228
	ldr	r7,.L5092
	ldr	r2,[r3]
	ldr	r7,[r7,r0 lsl 2]
	ldr	r4,[r2,28]
	ldr	r12,[r2,r0 lsl 2]
	lsl	r3,r1,1
	ldrh	r3,[r3,r4]
	ldr	r12,[r12,12]
	rsb	r3,r3,r3 lsl 2
	ldr	r0,[r2,40]
	add	r6,r12,r3 lsl 3
	ldr	r3,[r6,20]
	ldrb	r2,[r6,2]
	movw	r5,0xffff
	strh	r5,[r3,8]
	ldrb	r0,[r0,r2]
	ldr	r2,[r7,4]
	ldrb	r3,[r6,16]
	rsb	r0,r0,r0 lsl 3
	add	r2,r2,r0 lsl 2
	lsl	r7,r3,1
	add	r0,r7,r2
	ldrh	r6,[r0,16]!
	cmp	r6,r5
	lslne	r5,r6,1
	ldrhne	r4,[r5,r4]
	rsbne	r4,r4,r4 lsl 2
	addeq	r12,r7,r2
	addne	r12,r12,r4 lsl 3
	ldrne	r12,[r12,20]
	strh	r1,[r12,8]
	strh	r1,[r0]
	sxtb	r0,r3
	ldrsb	r1,[r2,24]
	cmp	r1,r0
	strblt	r3,[r2,24]
.LDW75:
.L5229:

	pop	{r4-r7,pc}
__ghs_eofn_Spi_AsyncLinkJobList:
	.endf	Spi_AsyncLinkJobList
	.endf	Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;Priority	r3	local
;JobListTailPtr	r0	local
;SpiPhyUnitStatusPtr	r2	local
;JobCfgPtr	r6	local
;TailJobCfgPtr	r12	local

;CoreId	r0	param
;Job	r1	param

	.section ".ghrettbl",""
.L5230:	.data.w	.L5229
	.endo	.L5230
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.22:
	.endo	..gh.f.a.1.e.22
	.global	Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncJobTransferChannel:
.LDW85:
	push	{r2,r4-fp,lr}
	ldr	r7,.L5228
	mov	r9,r0
	ldr	r0,[r7]
.LDW95:
	ldr	r3,.L5092
	mov	r8,r1
	ldr	r1,[r0,40]
	ldr	r3,[r3,r9 lsl 2]
	ldrb	r1,[r1,r8]
	ldr	r3,[r3,8]
	add	r1,r1,r1 lsl 2
	add	r5,r3,r1 lsl 3
	ldr	r1,[r0,r9 lsl 2]
	ldr	r12,[r5,16]
	ldr	r3,[r0,32]
	ldrb	r12,[r12]
	ldr	r1,[r1,16]
	ldrb	r3,[r3,r12]
	cmp	r2,1
	add	r6,r1,r3 lsl 5
	bne	.L5233
	ldr	r1,[r6,12]
	str	r1,[r5,28]
	ldr	r1,[r6,24]
	ldrh	r1,[r1]
	strh	r1,[r5,22]
	strh	r1,[r5]
	ldr	r1,[r6,20]
	ldr	r2,[r1,4]
	str	r2,[r5,8]
	ldr	r1,[r1,8]
	ldr	r2,[r6,8]
	str	r1,[r5,12]
	ldr	r1,[r5,36]
	ldr	r0,[r0,48]
	bic	r1,r1,250<<20
	orr	r1,r1,r2 lsl 23
	ldr	r2,[r6,28]
	ldr	r0,[r0,r8 lsl 2]
	orr	r1,r1,r2 lsl 21
	ldr	r2,[r5,4]
	str	r1,[r5,36]
	ldrb	r2,[r2,3]
.L5699:

	bl	Espi_Hal_WriteConfiguration
.L5233:
	ldrh	r0,[r5,22]
	cmp	r0,15
	movhi	fp,15
	uxtbls	fp,r0
	ldr	r1,[r6,24]
	ldrh	r1,[r1]
	ldr	r2,[r5,28]
	sub	r1,r1,r0
	sub	r0,r0,fp
	mul	r10,r2,r1
	ldrb	r1,[r5,20]
	strh	r0,[r5,22]
	ldrh	r0,[r5,22]
	cmp	r1,0
	cmpeq	r0,0
	strh	fp,[r5,24]
	moveq	r0,1
	strbeq	r0,[r5,32]
	ldr	r0,[r7]
	ldr	r0,[r0,48]
	mov	r2,fp
	mov	r1,0
	ldr	r0,[r0,r8 lsl 2]
.L5701:

	bl	Espi_Hal_SetFifoLevel
	mov	r4,r0
	ldr	r0,[r7]
	ldr	r0,[r0,48]
	ldr	r1,.L5698
	ldr	r0,[r0,r8 lsl 2]
.L5703:

	bl	Espi_Hal_ClearFlagStatus
	ldr	r0,[r7]
	ldr	r2,[r5,4]
	ldr	r1,[r0,r9 lsl 2]
	ldr	r0,[r0,36]
	ldrb	r2,[r2,4]
	ldr	r1,[r1,20]
	ldrb	r0,[r0,r2]
	mov	r2,44
	lsl	fp,fp,24
	smlabb	r9,r0,r2,r1
	b	.L5241
.L5243:
	ldr	r0,[r9,4]
	cmp	r0,0
	ldreq	r0,[r5,4]
	ldrbeq	r0,[r0,3]
	sub	fp,fp,1<<24
	cmpeq	r0,1
	ldrheq	r0,[r9,8]
.L5705:

	bleq	Dio_FlipChannel
	ldr	r0,[r5,8]
	ldr	r3,[r7]
	ldr	r2,[r6,12]
	ldr	r3,[r3,48]
	cmp	r0,0
	bne	.L5247
	ldr	r1,[r6,20]
	ldr	r0,[r3,r8 lsl 2]
.L5707:

	bl	Espi_Hal_SendData
	b	.L5249
.L5247:
	add	r1,r10,r0
	ldr	r0,[r3,r8 lsl 2]
.L5709:

	bl	Espi_Hal_SendData
	add	r10,r10,r0
.L5249:
	ldr	r0,[r9,4]
	cmp	r0,0
	ldreq	r0,[r5,4]
	ldrbeq	r0,[r0,3]
	cmpeq	r0,1
	bne	.L5241
	mov	r0,r8
.L5711:

	bl	Spi_WaitPhaseStatus
	and	r4,r0,1
	ldrh	r0,[r9,8]
.L5713:

	bl	Dio_FlipChannel
.L5241:
	lsrs	r0,fp,24
	beq	.L5242
	cmp	r4,1
	beq	.L5243
.L5242:
	mov	r0,r4
.LDW06:
.L5715:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Spi_AsyncJobTransferChannel:
	.endf	Spi_AsyncJobTransferChannel
	.endf	Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;Threshold	fp	local
;RetStatus	r4	local
;TxBufferIndex	r10	local
;DevStatePtr	r5	local
;ChannelCfgPtr	r6	local
;ExDeviceCfgPtr	r9	local

;CoreId	r9	param
;PhyUnit	r8	param
;NewChannel	r2	param

	.section ".ghcalltbl",""
.L5700:	.data.w	.L5699
	.endo	.L5700
.L5702:	.data.w	.L5701
	.endo	.L5702
.L5704:	.data.w	.L5703
	.endo	.L5704
.L5706:	.data.w	.L5705
	.endo	.L5706
.L5708:	.data.w	.L5707
	.endo	.L5708
.L5710:	.data.w	.L5709
	.endo	.L5710
.L5712:	.data.w	.L5711
	.endo	.L5712
.L5714:	.data.w	.L5713
	.endo	.L5714
	.section ".ghrettbl",""
.L5716:	.data.w	.L5715
	.endo	.L5716
	.data
	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_SendData.i.ppi

	.global	__caller.Espi_Hal_SendData.i.ppi

	.global	__caller.Dio_FlipChannel.i.i

	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.global	__caller.Espi_Hal_SetFifoLevel.i.pii

	.global	__caller.Espi_Hal_WriteConfiguration.v.pii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.23:
	.endo	..gh.f.a.1.e.23
	.global	Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncJobTransferFinished:
.LDW16:
	push	{r4-fp,lr}
	sub	sp,sp,12
	ldr	r7,.L5228
	mov	r5,r0
	mov	r9,r1
.LDW26:
	ldr	r1,[r7]
	lsl	r2,r9,1
	ldr	r3,[r1,28]
	ldr	r0,[r1,r5 lsl 2]
	ldrh	r2,[r2,r3]
	ldr	r8,[r0,12]
	rsb	r2,r2,r2 lsl 2
	ldr	r1,[r1,36]
	add	r8,r8,r2 lsl 3
	ldrb	r2,[r8,4]
	ldr	r0,[r0,20]
	ldrb	r1,[r1,r2]
	mov	r2,44
	smlabb	r0,r1,r2,r0
	mov	r10,0
	ldr	r1,[r0,4]
	mov	fp,r10
	cmp	r1,0
	ldrbeq	r1,[r8,3]
	strb	r10,[sp,2]
	cmpeq	r1,0
	ldrheq	r0,[r0,8]
.L7328:

	bleq	Dio_FlipChannel
	ldr	r1,[r7]
	ldr	r2,[r1,r5 lsl 2]
	ldr	r1,[r1,28]
	lsl	r0,r9,1
	ldrh	r0,[r0,r1]
	ldr	r1,[r2,12]
	rsb	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 3
	ldr	r0,[r0,20]
	str	r10,[r0]
	ldr	r0,[r8,12]
	cmp	r0,0
.L7330:

	blxne	r0
.L7332:

	bl	SchM_Enter_Spi_AsyncTransmit
	ldr	r1,[r7]
	ldrb	r0,[r8,2]
	ldr	r3,.L5092
	ldr	r2,[r1,40]
	ldr	r3,[r3,r5 lsl 2]
	ldrb	r2,[r2,r0]
	ldr	r3,[r3,4]
	rsb	r2,r2,r2 lsl 3
	add	r2,r3,r2 lsl 2
	ldr	r3,[r1,48]
	ldrb	r12,[r2]
	str	r2,[sp,4]
	mov	r2,r10
	cmp	r12,1
	ldr	r0,[r3,r0 lsl 2]
	movweq	r1,0x013f
	movwne	r1,0x053f
.L7334:

	bl	Espi_Hal_SetInterrupt
	and	r4,r0,1
	ldr	r0,[r8,20]
	ldr	r6,[r0,4]
	str	r10,[r0,4]
	ldmib	r6,{r0-r1}
	ldrh	r2,[r0,2]
	add	r2,r1,r2 lsl 1
	cmp	r2,r1
	addhi	r1,r1,2
	strhi	r1,[r6,8]
	ldrhhi	r10,[r1]
	b	.L7327

.L5092:	.data.w	Spi_CoreStatus
	.endo	.L5092

.L5228:	.data.w	Spi_ConfigPtr
	.endo	.L5228

.L5698:	.data.w	0x0007ffff
	.endo	.L5698

.L7327:

;line2902
..lin.3629b354..a08317f8.0_7::
.LDWlin7:
	ldrhi	r1,[r7]
	ldrhi	r2,[r1,r5 lsl 2]
	ldrhi	r1,[r1,28]
	lslhi	r3,r10,1
	ldrhhi	r1,[r3,r1]
	ldrhi	r2,[r2,12]
	rsbhi	r1,r1,r1 lsl 2
	addhi	fp,r2,r1 lsl 3
	ldr	r1,[r6]
	cmp	r1,2
	beq	.L5734
	cmp	r1,3
	bne	.L5730
.L5733:
	ldrb	r1,[r0]
	mov	r0,r5
.L7336:

	bl	Spi_AsyncUnlockRemainingJobs
	b	.L5868
.L5734:
	ldr	r1,[r7]
	ldr	r2,[r1,r5 lsl 2]
	ldr	r1,[r1,28]
	lsl	r3,r9,1
	ldrh	r1,[r3,r1]
	ldr	r2,[r2,12]
	rsb	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,20]
	mov	r2,2
	str	r2,[r1]
	b	.L5733
.L5730:
	ldrh	r0,[r6,12]
	cmp	r0,0
	bne	.L5738
	str	r0,[r6]
.L5868:
.L7338:

	bl	SchM_Exit_Spi_AsyncTransmit
	ldr	r0,[r6,4]
	ldr	r0,[r0,12]
	cmp	r0,0
.L7340:

	blxne	r0
	b	.L7305
.L5738:
	ldrb	r1,[fp,2]
	ldrb	r8,[r8,2]
	sub	r0,r0,1
	strh	r0,[r6,12]
	strb	r1,[sp,3]
.L7342:

	bl	SchM_Exit_Spi_AsyncTransmit
	ldrb	r2,[sp,3]
	cmp	r8,r2
	bne	.L5747
	ldr	r0,[r6,4]
	ldrb	r0,[r0,1]
	cmp	r0,1
	bne	.L5746
.L5747:
	mov	r1,r10
	mov	r0,r5
.L7344:

	bl	Spi_AsyncScheduleJob
	and	r4,r4,r0
.L7305:

	mov	r1,r9
	mov	r0,r5
.L7346:

	bl	Spi_AsyncScheduleNextJob
	and	r4,r4,r0
	b	.L5752
.L5746:
.L7348:

	bl	SchM_Enter_Spi_AsyncTransmit
	ldr	r2,[sp,4]
	ldrb	r2,[r2]
	mov	r1,r10
	mov	r0,r5
	cmp	r2,1
	bne	.L5749
.L7350:

	bl	Spi_AsyncJobDmaTransfer
	strb	r0,[sp,2]
	b	.L5737
.L5749:
.L7352:

	bl	Spi_AsyncJobTransfer
	and	r4,r4,r0
.L5737:
.L7354:

	bl	SchM_Exit_Spi_AsyncTransmit
	ldrb	r0,[sp,2]
	cmp	r0,1
	bne	.L5752
	ldr	r1,[r7]
	ldrb	r2,[fp,2]
	ldr	r0,[r1,r5 lsl 2]
	ldr	r1,[r1,40]
	ldr	r0,[r0,24]
	ldrb	r1,[r1,r2]
	add	r5,r0,r1 lsl 4
	ldrb	r0,[r5,2]
.L7356:

	bl	Dma_ChannelStart
	ldrb	r0,[r5,1]
.L7358:

	bl	Dma_ChannelStart
.L5752:
	mov	r0,r4
.LDW36:
	add	sp,sp,12
.L7360:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_AsyncJobTransferFinished:
	.endf	Spi_AsyncJobTransferFinished
	.endf	Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;NextJob	r10	local
;RetStatus	r4	local
;SeqStatePtr	r6	local
;NextJobCfgPtr	fp	local
;JobCfgPtr	r8	local
;ExDeviceCfgPtr	r0	local
;TriggerDmaFlag	[sp,2]	local
;SpiPhyUnitStatusPtr	[sp,4]	local
;PhyUnitCfgPtr	r5	local

;CoreId	r5	param
;Job	r9	param

	.section ".ghcalltbl",""
.L7329:	.data.w	.L7328
	.endo	.L7329
.L7331:	.data.w	.L7330
	.endo	.L7331
.L7333:	.data.w	.L7332
	.endo	.L7333
.L7335:	.data.w	.L7334
	.endo	.L7335
.L7337:	.data.w	.L7336
	.endo	.L7337
.L7339:	.data.w	.L7338
	.endo	.L7339
.L7341:	.data.w	.L7340
	.endo	.L7341
.L7343:	.data.w	.L7342
	.endo	.L7343
.L7345:	.data.w	.L7344
	.endo	.L7345
.L7347:	.data.w	.L7346
	.endo	.L7347
.L7349:	.data.w	.L7348
	.endo	.L7349
.L7351:	.data.w	.L7350
	.endo	.L7351
.L7353:	.data.w	.L7352
	.endo	.L7353
.L7355:	.data.w	.L7354
	.endo	.L7355
.L7357:	.data.w	.L7356
	.endo	.L7357
.L7359:	.data.w	.L7358
	.endo	.L7359
	.section ".ghrettbl",""
.L7361:	.data.w	.L7360
	.endo	.L7361
	.data
	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.Espi_Hal_SetInterrupt.i.pii

	.global	__caller.Espi_Hal_SetInterrupt.i.pii

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.global	__caller.Dio_FlipChannel.i.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.24:
	.endo	..gh.f.a.1.e.24
	.global	Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncScheduleNextJob:
.LDW46:
	push	{r2,r4-fp,lr}
	mov	r5,r0
	mov	r6,r1
	ldr	r8,.L5228
.LDW56:
	mov	r7,0
	mov	r4,1
.L8439:

	bl	SchM_Enter_Spi_AsyncTransmit
	ldr	r0,[r8]
	ldr	r12,[r0,r5 lsl 2]
	ldr	r9,[r0,28]
	ldr	r1,[r0,40]
	lsl	r0,r6,1
	ldrh	r0,[r0,r9]
	ldr	r12,[r12,12]
	rsb	r0,r0,r0 lsl 2
	add	r0,r12,r0 lsl 3
	ldrb	r0,[r0,2]
	ldrb	r0,[r1,r0]
	ldr	r2,.L5092
	rsb	r1,r0,r0 lsl 3
	ldr	r0,[r2,r5 lsl 2]
	ldr	r0,[r0,4]
	add	r0,r0,r1 lsl 2
	ldrsb	r2,[r0,24]
	cmp	r2,0
	strblt	r7,[r0,1]
	movlt	r1,2
	strlt	r1,[r0,4]
	blt	.L7366
	b	.L7369
.L7374:
	sub	r2,r2,1<<24
.L7372:
	ubfx	r1,r2,24,2
	add	r1,r0,r1 lsl 1
	ldrh	r1,[r1,8]
	cmp	r1,fp
	bne	.L7373
	asrs	r1,r2,24
	bpl	.L7374
.L7373:
	asr	r2,r2,24
	strb	r2,[r0,24]
.L7368:
	ldr	r1,[r10,4]
	cmp	r1,0
	bne	.L7379
	cmp	r2,0
	blt	.L7381
.L7369:
	lsl	r1,r2,30
	add	r3,r0,r1 lsr 29
	ldrh	r1,[r3,8]
	lsl	r1,r1,1
	ldrh	r1,[r1,r9]
	rsb	r1,r1,r1 lsl 2
	add	r6,r12,r1 lsl 3
	ldr	r10,[r6,20]
	ldrh	r1,[r10,8]
	movw	fp,0xffff
	cmp	r1,fp
	strh	r1,[r3,8]
	lsleq	r2,r2,24
	strheq	r1,[r3,16]
	beq	.L7372
	b	.L7368
.L7379:
	ldrb	r2,[r0]
	ldrh	r1,[r6]
	mov	r0,r5
	cmp	r2,1
	bne	.L7382
.L8441:

	bl	Spi_AsyncJobDmaTransfer
	mov	r7,r0
	b	.L8422
.L7382:
.L8443:

	bl	Spi_AsyncJobTransfer
.L8422:

	and	r4,r0,1
	b	.L7366
.L7381:
	mov	r1,2
	str	r1,[r0,4]
.L7366:
.L8445:

	bl	SchM_Exit_Spi_AsyncTransmit
	cmp	r7,1
	bne	.L7384
	ldr	r0,[r8]
	ldrb	r2,[r6,2]
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,40]
	ldr	r1,[r1,24]
	ldrb	r0,[r0,r2]
	add	r5,r1,r0 lsl 4
	ldrb	r0,[r5,2]
.L8447:

	bl	Dma_ChannelStart
	ldrb	r0,[r5,1]
.L8449:

	bl	Dma_ChannelStart
.L7384:
	mov	r0,r4
.LDW66:
.L8451:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Spi_AsyncScheduleNextJob:
	.endf	Spi_AsyncScheduleNextJob
	.endf	Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;MaxPriority	r2	local
;JobListHeadPtr	r3	local
;SpiPhyUnitStatusPtr	r0	local
;NewJobCfgPtr	r6	local
;TriggerDmaFlag	r7	local
;PhyUnitCfgPtr	r5	local

;CoreId	r5	param
;Job	r6	param

	.section ".ghcalltbl",""
.L8440:	.data.w	.L8439
	.endo	.L8440
.L8442:	.data.w	.L8441
	.endo	.L8442
.L8444:	.data.w	.L8443
	.endo	.L8444
.L8446:	.data.w	.L8445
	.endo	.L8446
.L8448:	.data.w	.L8447
	.endo	.L8448
.L8450:	.data.w	.L8449
	.endo	.L8450
	.section ".ghrettbl",""
.L8452:	.data.w	.L8451
	.endo	.L8452
	.data
	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.25:
	.endo	..gh.f.a.1.e.25
	.global	Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncIsrFifoRx:
.LDW76:
	push	{r4-r9,lr}
	sub	sp,sp,12
	ldr	r5,.L5228
	mov	r6,r0
	ldr	r0,[r5]
	ldr	r2,.L5092
	mov	r8,r1
	ldr	r1,[r0,40]
	ldr	r2,[r2,r6 lsl 2]
	ldrb	r1,[r1,r8]
	ldr	r2,[r2,8]
	add	r1,r1,r1 lsl 2
	add	r4,r2,r1 lsl 3
	ldr	r2,[r0,r6 lsl 2]
	ldr	r3,[r4,16]
	ldr	r0,[r0,32]
	ldrb	r3,[r3]
	ldr	r2,[r2,16]
	ldrb	r0,[r0,r3]
	add	r0,r2,r0 lsl 5
	ldr	r0,[r0,24]
	ldrh	r1,[r4]
.LDW86:
	ldrh	r0,[r0]
	ldr	r2,[r4,28]
	sub	r0,r0,r1
	mul	r7,r2,r0
	ldrh	r0,[r4,24]
	ldr	r9,[r4,4]
	sub	r0,r1,r0
	strh	r0,[r4]
.L8763:

	bl	SchM_Enter_Spi_AsyncTransmit
	b	.L8455
.L8457:
	ldr	r1,[r4,12]
	ldr	r3,[r2,48]
	ldr	r2,[r4,28]
	cmp	r1,0
	ldr	r0,[r3,r0 lsl 2]
	bne	.L8458
	add	r1,sp,4
.L8765:

	bl	Espi_Hal_ReceiveData
	b	.L8460
.L8458:
	add	r1,r7,r1
.L8767:

	bl	Espi_Hal_ReceiveData
	add	r7,r7,r0
.L8460:
	ldrh	r0,[r4,24]
	sub	r0,r0,1
	strh	r0,[r4,24]
.L8455:
	ldrh	r1,[r4,24]
	ldr	r2,[r5]
	ldrb	r0,[r9,2]
	cmp	r1,0
	bne	.L8457
	ldr	r1,[r2,48]
	ldr	r0,[r1,r0 lsl 2]
	mov	r1,1<<10
.L8769:

	bl	Espi_Hal_ClearFlagStatus
	ldrb	r0,[r4,32]
	cmp	r0,0
	bne	.L8461
	ldrh	r0,[r4]
	cmp	r0,0
	bne	.L8463
	ldrb	r0,[r4,20]
	subs	r0,r0,1
	strbhs	r0,[r4,20]
	ldrhs	r0,[r4,16]
	movhs	r2,1
	addhs	r0,r0,1
	strhs	r0,[r4,16]
	bhs	.L8466
.L8463:
	mov	r2,0
.L8466:
	mov	r1,r8
	mov	r0,r6
.L8771:

	bl	Spi_AsyncJobTransferChannel
	mov	r4,r0
.L8773:

	bl	SchM_Exit_Spi_AsyncTransmit
	b	.L8467
.L8461:
.L8775:

	bl	SchM_Exit_Spi_AsyncTransmit
	ldr	r1,[r4,4]
	mov	r0,r6
	ldrh	r1,[r1]
.L8777:

	bl	Spi_AsyncJobTransferFinished
	mov	r4,r0
.L8467:
	and	r0,r4,1
.LDW96:
	add	sp,sp,12
.L8779:

	pop	{r4-r9,pc}
__ghs_eofn_Spi_AsyncIsrFifoRx:
	.endf	Spi_AsyncIsrFifoRx
	.endf	Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r0	local
;RxBufIndex	r7	local
;TempRxBuffer	[sp,4]	local
;DevStatePtr	r4	local
;JobCfgPtr	r9	local

;CoreId	r6	param
;PhyUnit	r8	param

	.section ".ghcalltbl",""
.L8764:	.data.w	.L8763
	.endo	.L8764
.L8766:	.data.w	.L8765
	.endo	.L8766
.L8768:	.data.w	.L8767
	.endo	.L8768
.L8770:	.data.w	.L8769
	.endo	.L8770
.L8772:	.data.w	.L8771
	.endo	.L8772
.L8774:	.data.w	.L8773
	.endo	.L8774
.L8776:	.data.w	.L8775
	.endo	.L8776
.L8778:	.data.w	.L8777
	.endo	.L8778
	.section ".ghrettbl",""
.L8780:	.data.w	.L8779
	.endo	.L8780
	.data
	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.global	__caller.Espi_Hal_ReceiveData.i.ppi

	.global	__caller.Espi_Hal_ReceiveData.i.ppi

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.26:
	.endo	..gh.f.a.1.e.26
	.global	Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_AsyncUnlockRemainingJobs:
.LDW07:
	push	{r2,r4-r9,lr}
	ldr	r4,.L8910
	mov	r7,r0
	ldr	r0,[r4]
.LDW17:
	mov	r9,r1
	ldr	r1,[r0,24]
	ldr	r0,[r0,r7 lsl 2]
	ldrb	r1,[r1,r9]
	ldr	r2,.L8911
	ldr	r0,[r0,8]
	ldr	r8,[r2,r7 lsl 2]
	add	r5,r0,r1 lsl 4
	ldr	r0,[r8]
	add	r0,r0,r1 lsl 4
	ldrh	r1,[r5,2]
	ldrh	r0,[r0,12]
	sub	r0,r1,r0
	lsl	r6,r0,16
	b	.L8786
.L8789:
	ldr	r3,[r5,4]
	lsl	r2,r2,1
	ldr	r0,[r4]
	ldrh	r2,[r2,r3]
	ldr	r3,[r0,28]
	ldr	r1,[r0,r7 lsl 2]
	lsl	r2,r2,1
	ldrh	r2,[r2,r3]
	ldr	r1,[r1,12]
	rsb	r2,r2,r2 lsl 2
	add	r1,r1,r2 lsl 3
	ldr	r2,[r1,20]
	mov	r3,0
	str	r3,[r2,4]
	ldr	r3,[r0,24]
	ldr	r12,[r8]
	ldrb	r3,[r3,r9]
	ldr	r3,[r12,r3 lsl 4]
	subs	r3,r3,3
	movne	r3,2
	str	r3,[r2]
	ldr	r2,[r0,48]
	ldrb	r0,[r1,2]
	ldr	r1,.L8912
	ldr	r0,[r2,r0 lsl 2]
.L8913:

	bl	Espi_Hal_ClearFlagStatus
	add	r6,r6,1<<16
.L8786:
	ldrh	r0,[r5,2]
	lsr	r2,r6,16
	cmp	r2,r0
	blo	.L8789
.LDW27:
.L8915:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Spi_AsyncUnlockRemainingJobs:
	.endf	Spi_AsyncUnlockRemainingJobs
	.endf	Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;JobCfgPtr	r1	local
;SeqCfgPtr	r5	local

;CoreId	r7	param
;Sequence	r9	param

	.section ".ghcalltbl",""
.L8914:	.data.w	.L8913
	.endo	.L8914
	.section ".ghrettbl",""
.L8916:	.data.w	.L8915
	.endo	.L8916
	.data
	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.27:
	.endo	..gh.f.a.1.e.27
	.global	Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_WaitPhaseStatus:
.LDW37:
	push	{r4-r6,r10-fp,lr}
	sub	sp,sp,8
.LDW47:
	mov	r6,0
	strb	r0,[sp,7]
.L9098:

	bl	Rcc_Hal_GetStmClkFreq
.L9100:

	bl	__ftou64
	mov	r2,0x03e8
	mov	r3,r6
.L9102:

	bl	__gh_mul64
	ldr	r2,.L9094
	mov	r3,r6
.L9104:

	bl	__gh_udiv64
	mov	r5,r1
	b	.L9095

.L8910:	.data.w	Spi_ConfigPtr
	.endo	.L8910

.L8911:	.data.w	Spi_CoreStatus
	.endo	.L8911

.L8912:	.data.w	0x10000400
	.endo	.L8912

.L9094:	.data.w	0x000f4240
	.endo	.L9094

.L9095:

;line3460
..lin.3629b354..e2c1847a.0_8::
.LDWlin8:
..gh.beginasm.28:
	.endo	..gh.beginasm.28
MRRC p15, 0, r1, r2, c14

..gh.endasm.29:
	.endo	..gh.endasm.29

	adds	r4,r1,r0
	mov	fp,r6
	adc	r5,r2,r5
.L8925:
;line3463
..lin.3629b354..e2c1847a.0_9::
.LDWlin9:
	ldr	r1,.L9096
	ldr	r0,[r1]
	ldrb	r1,[sp,7]
	ldr	r0,[r0,48]
	ldr	r0,[r0,r1 lsl 2]
	mov	r1,15<<28
.L9106:

	bl	Espi_Hal_GetFlagStatus
	cmp	r0,0
	andne	r1,r0,3<<29
	cmpne	r1,3<<29
	moveq	r6,1
	mov	r10,fp
	b	.L9097

.L9096:	.data.w	Spi_ConfigPtr
	.endo	.L9096

.L9097:

;line3475
..lin.3629b354..e2c1847a.0_10::
.LDWlin10:
..gh.beginasm.30:
	.endo	..gh.beginasm.30
MRRC p15, 0, r1, r10, c14

..gh.endasm.31:
	.endo	..gh.endasm.31

;line3477
..lin.3629b354..e2c1847a.0_11::
.LDWlin11:
	cmp	r10,r5
	cmpeq	r1,r4
	bhs	.L8923
	cmp	r6,0
	beq	.L8925
.L8923:
	mov	r0,r6
.LDW57:
	add	sp,sp,8
.L9108:

	pop	{r4-r6,r10-fp,pc}
__ghs_eofn_Spi_WaitPhaseStatus:
	.endf	Spi_WaitPhaseStatus
	.endf	Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RegStatus	r6	local
;RegValue	r0	local
;TimerFreq	r0	local
;TimeOutCount	r4	local
;CurrentCount	r2	local
;value	r8	local
;value	r2	local

;PhyUnit	[sp,7]	param

	.section ".ghcalltbl",""
.L9099:	.data.w	.L9098
	.endo	.L9099
.L9101:	.data.w	.L9100
	.endo	.L9101
.L9103:	.data.w	.L9102
	.endo	.L9103
.L9105:	.data.w	.L9104
	.endo	.L9105
.L9107:	.data.w	.L9106
	.endo	.L9107
	.section ".ghrettbl",""
.L9109:	.data.w	.L9108
	.endo	.L9109
	.data
	.global	__caller.Espi_Hal_GetFlagStatus.i.pi

	.global	__caller.Rcc_Hal_GetStmClkFreq.f.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.32:
	.endo	..gh.f.a.1.e.32
	.global	Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_GetDataTotalNumOfJob:
.LDW67:
	push	{r4-r6,lr}
.LDW77:
	ldr	r3,.L9220
	ldr	r12,[r3]
	lsl	r1,r1,1
	ldr	r2,[r12,28]
	ldr	r4,[r12,r0 lsl 2]
	ldrh	r1,[r1,r2]
	mov	r0,0
	rsb	r2,r1,r1 lsl 2
	ldr	r1,[r4,12]
	mov	r3,r0
	add	r1,r1,r2 lsl 3
	ldr	r2,[r1,8]
	b	.L9115
.L9114:
	ldr	r5,[r12,32]
	ldrb	r6,[r2],1
	ldrb	r5,[r5,r6]
	ldr	r6,[r4,16]
	add	r5,r6,r5 lsl 5
	ldr	r5,[r5,24]
	ldrh	r5,[r5]
	add	r3,r3,1<<16
	add	r0,r0,r5
	uxth	r0,r0
.L9115:
	ldrb	r6,[r1,5]
	cmp	r6,r3 lsr 16
	bhi	.L9114
.LDW87:
.L9221:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_GetDataTotalNumOfJob:
	.endf	Spi_GetDataTotalNumOfJob
	.endf	Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;DataTotalNum	r0	local
;ChannelIndexPtr	r2	local
;JobCfgPtr	r1	local

;CoreId	r2	param
;Job	r1	param

	.section ".ghrettbl",""
.L9222:	.data.w	.L9221
	.endo	.L9222
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.33:
	.endo	..gh.f.a.1.e.33
	.global	Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_IsrError:
.LDW97:
	push	{r4-r8,lr}
	mov	r8,r1
	ldr	r1,.L9495
.LDW08:
	ldr	r4,.L9220
	ldr	r7,[r1,r0 lsl 2]
	ldr	r0,[r4]
	ldr	r0,[r0,40]
	ldrb	r0,[r0,r8]
	add	r1,r0,r0 lsl 2
	ldr	r0,[r7,8]
	add	r0,r0,r1 lsl 3
	ldr	r6,[r0,4]
.L9496:

	bl	SchM_Enter_Spi_IsrError
	ldr	r1,[r4]
	ldrb	r0,[r6,2]
	ldr	r1,[r1,48]
	ldr	r0,[r1,r0 lsl 2]
	movw	r1,0x013f
.L9498:

	bl	Espi_Hal_GetFlagStatus
	mov	r5,r0
	movw	r0,0x013f
	tst	r5,r0
	beq	.L9225
	ldr	r1,[r4]
	ldrb	r0,[r6,2]
	ldr	r1,[r1,48]
	ldr	r0,[r1,r0 lsl 2]
	movw	r1,0x013f
.L9500:

	bl	Espi_Hal_ClearFlagStatus
	ldr	r0,[r4]
	ldr	r0,[r0,40]
	ldrb	r0,[r0,r8]
	rsb	r1,r0,r0 lsl 3
	ldr	r0,[r7,4]
	add	r0,r0,r1 lsl 2
	ldrb	r0,[r0,1]
	cmp	r0,1
	ldreq	r0,[r6,20]
	ldreq	r0,[r0,4]
	moveq	r1,2
	streq	r1,[r0]
.L9502:

	bl	SchM_Exit_Spi_IsrError
	mov	r1,0
	mov	r0,83
	tst	r5,1
	movne	r3,224
	movne	r2,225
	bne	.L9481
.L9229:
	tst	r5,2
	movne	r3,225
	movne	r2,r3
	bne	.L9483
.L9232:
	mov	r2,225
	tst	r5,8
	movne	r3,227
	bne	.L9482
.L9235:
	tst	r5,32
	movne	r3,229
	moveq	r3,231
.L9481:

.L9482:

.L9483:

.L9504:

	bl	Det_ReportError
.L9506:

	pop	{r4-r8,pc}
.L9225:
.L9508:

	bl	SchM_Exit_Spi_IsrError
.LDW18:
.L9510:

	pop	{r4-r8,pc}
__ghs_eofn_Spi_IsrError:
	.endf	Spi_IsrError
	.endf	Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RegStatus	r5	local
;JobCfgPtr	r6	local

;CoreId	r0	param
;PhyUnit	r8	param

	.section ".ghcalltbl",""
.L9497:	.data.w	.L9496
	.endo	.L9497
.L9499:	.data.w	.L9498
	.endo	.L9499
.L9501:	.data.w	.L9500
	.endo	.L9501
.L9503:	.data.w	.L9502
	.endo	.L9503
.L9505:	.data.w	.L9504
	.endo	.L9505
	.section ".ghrettbl",""
.L9507:	.data.w	.L9506
	.endo	.L9507
	.section ".ghcalltbl",""
.L9509:	.data.w	.L9508
	.endo	.L9509
	.section ".ghrettbl",""
.L9511:	.data.w	.L9510
	.endo	.L9511
	.data
	.global	__caller.SchM_Exit_Spi_IsrError.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Spi_IsrError.v.v

	.global	__caller.Espi_Hal_ClearFlagStatus.v.pi

	.global	__caller.Espi_Hal_GetFlagStatus.i.pi

	.global	__caller.SchM_Enter_Spi_IsrError.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.34:
	.endo	..gh.f.a.1.e.34
	.global	Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_InitDriver:
.LDW28:
	push	{r4-fp,lr}
	sub	sp,sp,12
	ldr	r9,.L9220
	ldr	r5,[r1,r0 lsl 2]
.LDW38:
	mov	r2,0
	str	r1,[r9]
	b	.L9517
.L9516:
	ldr	r12,[r5,12]
	rsb	r1,r1,r1 lsl 2
	add	r1,r12,r1 lsl 3
	mov	r12,r3
	ldr	r1,[r1,20]
	stm	r1,{r3,r12}
	add	r2,r2,1<<16
.L9517:
	ldrh	r12,[r5,2]
	lsr	r1,r2,16
	mov	r3,0
	cmp	r1,r12
	blo	.L9516
	mvn	fp,0
	mov	r2,r3
.L9521:
	ldr	r12,.L9495
	ldr	r8,[r12,r0 lsl 2]
	ldrb	r12,[r5]
	lsr	r6,r2,24
	cmp	r6,r12
	ldrhs	r0,[r8,16]
	strhs	r3,[r0]
	ldrhs	r0,[r8,20]
	movhs	r6,r3
	movhs	r7,1
	strhhs	r3,[r0]
	bhs	.L9525
	ldr	r1,[r8]
	str	r3,[r1,r6 lsl 4]!
	ldr	r4,[r5,8]
	mov	lr,r3
	add	r12,r4,r6 lsl 4
	stmib	r1,{r12,lr}
	strh	r3,[r1,12]
	add	r2,r2,1<<24
	b	.L9521
.L9524:
	ldr	r1,[r5,24]
	add	r0,r1,r6 lsl 4
	ldrb	r0,[r0,1]
	cmp	r0,255
	ldrne	r1,[r8,4]
	rsbne	r0,r6,r6 lsl 3
	movne	r2,1
	strbne	r2,[r1,r0 lsl 2]
	ldr	r1,[r8,4]
	rsb	r0,r6,r6 lsl 3
	add	r1,r1,r0 lsl 2
	mov	r0,0
	strb	r0,[r1,1]
	mov	r0,2
	str	r0,[r1,4]
	mov	r0,0
.L9531:
	add	r2,r1,r0 lsl 1
	add	r0,r0,1
	strh	fp,[r2,8]
	cmp	r0,4
	strh	fp,[r2,16]
	blo	.L9531
	strb	fp,[r1,24]
	mov	r10,0
	b	.L9535
.L9534:
	ldr	r2,[r9]
	ldr	r1,[r5,24]
	ldr	r2,[r2,48]
	ldrb	r0,[r1,r6 lsl 4]!
	ldr	r1,[r1,12]
	ldr	r0,[r2,r0 lsl 2]
.L10071:

	bl	Espi_Master_Hal_InitModule
	and	r7,r0,1
	lsr	r0,r10,24
	mov	r1,44
	smulbb	r2,r0,r1
	ldr	r0,[r5,20]
	ldr	r1,[r5,24]
	str	r2,[sp,4]
	ldrb	r2,[r0,r2]!
	ldrb	r1,[r1,r6 lsl 4]
	cmp	r2,r1
	bne	.L9533
	ldr	r1,[r0,4]
	cmp	r1,0
	ldreq	r1,[r0,40]
	ldrbeq	r1,[r1,32]
	ldrheq	r0,[r0,8]
	eoreq	r1,r1,1
.L10073:

	bleq	Dio_WriteChannel
	ldr	r1,[r9]
	ldr	r0,[r5,24]
	ldr	r1,[r1,48]
	ldrb	r0,[r0,r6 lsl 4]
	ldr	r2,[sp,4]
	ldr	r0,[r1,r0 lsl 2]
	ldr	r1,[r5,20]
	add	r1,r2,r1
	ldr	r1,[r1,40]
.L10075:

	bl	Espi_Master_Hal_InitChannel
	and	r7,r7,r0
.L9533:
	add	r10,r10,1<<24
.L9535:
	ldrb	r1,[r5,5]
	cmp	r1,r10 lsr 24
	bls	.L9523
	cmp	r7,0
	bne	.L9534
.L9523:
	add	r6,r6,1
	uxtb	r6,r6
.L9525:
	ldrb	r0,[r5,6]
	cmp	r6,r0
	bhs	.L9522
	cmp	r7,0
	bne	.L9524
.L9522:
	ldr	r0,[r8,12]
	mov	r1,1
	str	r1,[r0]
	mov	r0,r7
.LDW48:
	add	sp,sp,12
.L10077:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_InitDriver:
	.endf	Spi_InitDriver
	.endf	Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r7	local
;PhyUnitIndex	r6	local
;CurrentCoreConfigPtr	r5	local

;CoreId	r0	param
;ConfigPtr	r1	param

	.section ".ghcalltbl",""
.L10072:	.data.w	.L10071
	.endo	.L10072
.L10074:	.data.w	.L10073
	.endo	.L10074
.L10076:	.data.w	.L10075
	.endo	.L10076
	.section ".ghrettbl",""
.L10078:	.data.w	.L10077
	.endo	.L10078
	.data
	.global	__caller.Espi_Master_Hal_InitChannel.i.pp

	.global	__caller.Dio_WriteChannel.v.ii

	.global	__caller.Espi_Master_Hal_InitModule.i.pp

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.35:
	.endo	..gh.f.a.1.e.35
	.global	Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.:
Spi_DeInitDriver:
.LDW58:
	push	{r2,r4-fp,lr}
	ldr	fp,.L9220
	ldr	r7,[fp]
.LDW68:
	mov	r4,0
	mov	r5,r0
	mov	r10,r4
	ldr	r7,[r7,r0 lsl 2]
	b	.L10084
.L10083:
	mov	r0,4
.L11206:

	bl	Mcal_GetLock
	subs	r4,r0,0
	bne	.L10082
	ldr	r2,[fp]
	ldr	r1,[r2,r5 lsl 2]
	lsr	r8,r10,24
	ldr	r1,[r1,24]
	ldr	r0,[r2,48]
	ldrb	r1,[r1,r8 lsl 4]
	ldr	r0,[r0,r1 lsl 2]
.L11208:

	bl	Espi_Hal_ResetModule
	mov	r9,r0
	mov	r0,4
.L11210:

	bl	Mcal_ReleaseLock
	cmp	r9,0
	ldreq	r1,[r6,r5 lsl 2]
	ldreq	r1,[r1,4]
	rsbeq	r0,r8,r8 lsl 3
	addeq	r0,r1,r0 lsl 2
	moveq	r1,1
	movne	r4,1
	streq	r1,[r0,4]
.L10082:
	add	r10,r10,1<<24
.L10084:
	ldrb	r1,[r7,6]
	ldr	r6,.L9495
	cmp	r1,r10 lsr 24
	bls	.L10081
	cmp	r4,0
	beq	.L10083
	b	.L11205

.L9220:	.data.w	Spi_ConfigPtr
	.endo	.L9220

.L9495:	.data.w	Spi_CoreStatus
	.endo	.L9495

.L11205:

.L10081:
;line3920
..lin.3629b354..25e459b9.0_12::
.LDWlin12:
	mov	r0,0
	b	.L10094
.L10093:
	ldr	r2,[r7,12]
	rsb	r1,r1,r1 lsl 2
	add	r1,r2,r1 lsl 3
	ldr	r1,[r1,20]
	add	r0,r0,1<<16
	str	r4,[r1]
.L10094:
	ldrh	r2,[r7,2]
	lsr	r1,r0,16
	cmp	r1,r2
	bhs	.L10091
	cmp	r4,0
	beq	.L10093
.L10091:
	mov	r1,0
	cmp	r4,0
	bne	.L10101
.L10098:
	ldrne	r0,[r6,r5 lsl 2]
	ldrne	r0,[r0]
	addne	r1,r1,1<<24
	strne	r4,[r0,r3 lsl 4]
.L10100:
	ldrb	r2,[r7]
	lsr	r3,r1,24
	cmp	r3,r2
	blo	.L10098
	ldr	r0,[r6,r5 lsl 2]
	ldr	r0,[r0,12]
	str	r4,[r0]
.L10101:
	mov	r0,r4
.LDW78:
.L11212:

	pop	{r2,r4-fp,pc}
__ghs_eofn_Spi_DeInitDriver:
	.endf	Spi_DeInitDriver
	.endf	Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
;RetStatus	r4	local
;ResetStatus	r9	local
;SeqIndex	r0	local
;CurrentCoreConfigPtr	r7	local

;CoreId	r5	param

	.section ".ghcalltbl",""
.L11207:	.data.w	.L11206
	.endo	.L11207
.L11209:	.data.w	.L11208
	.endo	.L11209
.L11211:	.data.w	.L11210
	.endo	.L11211
	.section ".ghrettbl",""
.L11213:	.data.w	.L11212
	.endo	.L11213
	.data
	.global	__caller.Mcal_ReleaseLock.v.i

	.global	__caller.Espi_Hal_ResetModule.i.p

	.global	__caller.Mcal_GetLock.i.i

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.36:
	.endo	..gh.f.a.1.e.36
__callee.Spi_Init.v.p::
	.size	__callee.Spi_Init.v.p,0
Spi_Init::
.LDW88:
	str	lr,[sp,-8]!
.LDW98:
..gh.beginasm.37:
	.endo	..gh.beginasm.37
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.38:
	.endo	..gh.endasm.38

;line4004
..lin.3629b354..be548ee4.0_13::
.LDWlin13:
	ldr	r12,.L11434
	ldr	r1,[r12,r2 lsl 2]
	cmp	r1,0
	ldrne	r1,[r1,12]
	mov	r3,163
	ldrne	r1,[r1]
	movne	r3,74
	cmpne	r1,1
	beq	.L11222
	movs	r1,r0
	bne	.L11230
	mov	r3,16
	mov	r2,r0
	b	.L11427
.L11222:
	mov	r2,0
	mov	r1,r2
.L11427:

	mov	r0,83
.L11435:

	bl	Det_ReportError
.L11437:

	ldr	pc,[sp],8
.L11230:
	mov	r0,r2
.L11439:

	bl	Spi_InitDriver
	movs	r2,r0
	moveq	r3,232
	moveq	r1,r0
	moveq	r0,83
.L11441:

	bleq	Det_ReportRuntimeError
.LDW09:
.L11443:

	ldr	pc,[sp],8
__ghs_eofn_Spi_Init::
	.endf	Spi_Init
;CoreId	r2	local

;ConfigPtr	r0	param

	.section ".bss","awb"
.L11359:
	.endo	.L11359
	.section ".ghcalltbl",""
.L11436:	.data.w	.L11435
	.endo	.L11436
	.section ".ghrettbl",""
.L11438:	.data.w	.L11437
	.endo	.L11438
	.section ".ghcalltbl",""
.L11440:	.data.w	.L11439
	.endo	.L11440
.L11442:	.data.w	.L11441
	.endo	.L11442
	.section ".ghrettbl",""
.L11444:	.data.w	.L11443
	.endo	.L11444
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.39:
	.endo	..gh.f.a.1.e.39
__callee.Spi_DeInit.i.v::
	.size	__callee.Spi_DeInit.i.v,0
Spi_DeInit::
.LDW19:
	push	{r2,r4-r5,lr}
.LDW29:
	b	.L11699

.L11434:	.data.w	Spi_CoreStatus
	.endo	.L11434

.L11699:

;line4092
..lin.3629b354..9955988d.0_14::
.LDWlin14:
..gh.beginasm.40:
	.endo	..gh.beginasm.40
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.41:
	.endo	..gh.endasm.41

	ldr	r1,.L11700
;line4095
..lin.3629b354..9955988d.0_15::
.LDWlin15:
	mov	r5,r0
	ldr	r0,[r1,r0 lsl 2]
	mov	r4,1
	cmp	r0,0
	moveq	r3,163
	moveq	r2,r4
	moveq	r1,r0
	beq	.L11689
.L11451:
	ldr	r1,[r0,12]
	ldr	r1,[r1]
	cmp	r1,0
	bne	.L11458
.L11455:
	mov	r3,26
	mov	r2,r4
.L11689:

	mov	r0,83
.L11701:

	bl	Det_ReportError
	b	.L11457
.L11458:
.L11703:

	bl	SchM_Enter_Spi_DeInit
	mov	r0,r5
.L11705:

	bl	Spi_GetDriverStatus
	cmp	r0,3
	bne	.L11459
.L11707:

	bl	SchM_Exit_Spi_DeInit
	mov	r3,42
	mov	r2,r4
	mov	r1,0
	mov	r0,83
.L11709:

	bl	Det_ReportRuntimeError
	b	.L11457
.L11459:
	mov	r0,r5
.L11711:

	bl	Spi_DeInitDriver
	mov	r4,r0
.L11713:

	bl	SchM_Exit_Spi_DeInit
.L11457:
	mov	r0,r4
.LDW39:
.L11715:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Spi_DeInit::
	.endf	Spi_DeInit
;CoreId	r5	local
;RetStatus	r4	local

	.section ".bss","awb"
.L11611:
	.endo	.L11611
	.section ".ghcalltbl",""
.L11702:	.data.w	.L11701
	.endo	.L11702
.L11704:	.data.w	.L11703
	.endo	.L11704
.L11706:	.data.w	.L11705
	.endo	.L11706
.L11708:	.data.w	.L11707
	.endo	.L11708
.L11710:	.data.w	.L11709
	.endo	.L11710
.L11712:	.data.w	.L11711
	.endo	.L11712
.L11714:	.data.w	.L11713
	.endo	.L11714
	.section ".ghrettbl",""
.L11716:	.data.w	.L11715
	.endo	.L11716
	.data
	.global	__caller.SchM_Exit_Spi_DeInit.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_DeInit.v.v

	.global	__caller.SchM_Enter_Spi_DeInit.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.42:
	.endo	..gh.f.a.1.e.42
__callee.Spi_WriteIB.i.ip::
	.size	__callee.Spi_WriteIB.i.ip,0
Spi_WriteIB::
.LDW49:
	push	{r2,r4-r7,lr}
	mov	r7,r0
	mov	r6,r1
.LDW59:
	b	.L11990

.L11700:	.data.w	Spi_CoreStatus
	.endo	.L11700

.L11990:

;line4210
..lin.3629b354..9b3480c6.0_16::
.LDWlin16:
..gh.beginasm.43:
	.endo	..gh.beginasm.43
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.44:
	.endo	..gh.endasm.44

	mov	r5,r2
;line4213
..lin.3629b354..9b3480c6.0_17::
.LDWlin17:
	mov	r2,r0
	mov	r0,r5
	mov	r1,2
.L11992:

	bl	Spi_GetChannelDetStatus
	subs	r4,r0,0
	bne	.L11723
	ldr	r1,.L11991
	ldr	r0,[r1]
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,32]
	ldr	r1,[r1,16]
	ldrb	r0,[r0,r7]
	add	r5,r1,r0 lsl 5
	ldr	r0,[r5,4]
	cmp	r0,0
	beq	.L11725
	mov	r4,1
	mov	r3,10
	mov	r2,2
	mov	r1,0
	mov	r0,83
.L11994:

	bl	Det_ReportError
	b	.L11723
.L11725:
.L11996:

	bl	SchM_Enter_Spi_WriteIB
	ldr	r0,[r5,24]
	ldrh	r1,[r5,16]
	cmp	r6,0
	strh	r1,[r0]
	ldreq	r0,[r5,20]
	movne	r0,0
	streq	r6,[r0,4]
	bne	.L11734
	b	.L11730
.L11733:
	ldr	r1,[r5,20]
	ldrb	r2,[r6,r0]
	ldr	r1,[r1,4]
	strb	r2,[r1,r0]
	add	r0,r0,1
.L11734:
	ldr	r1,[r5,12]
	ldrh	r2,[r5,16]
	mul	r1,r2,r1
	cmp	r0,r1
	blo	.L11733
.L11730:
.L11998:

	bl	SchM_Exit_Spi_WriteIB
.L11723:
	mov	r0,r4
.LDW69:
.L12000:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Spi_WriteIB::
	.endf	Spi_WriteIB
;CoreId	r5	local
;RetStatus	r4	local
;DataIndex	r0	local
;ChannelCfgPtr	r5	local

;Channel	r7	param
;DataBufferPtr	r6	param

	.section ".ghcalltbl",""
.L11993:	.data.w	.L11992
	.endo	.L11993
.L11995:	.data.w	.L11994
	.endo	.L11995
.L11997:	.data.w	.L11996
	.endo	.L11997
.L11999:	.data.w	.L11998
	.endo	.L11999
	.section ".ghrettbl",""
.L12001:	.data.w	.L12000
	.endo	.L12001
	.data
	.global	__caller.SchM_Exit_Spi_WriteIB.v.v

	.global	__caller.SchM_Enter_Spi_WriteIB.v.v

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.45:
	.endo	..gh.f.a.1.e.45
__callee.Spi_AsyncTransmit.i.i::
	.size	__callee.Spi_AsyncTransmit.i.i,0
Spi_AsyncTransmit::
.LDW79:
	push	{r4-fp,lr}
	sub	sp,sp,28
	mov	r9,r0
.LDW89:
	mov	r2,r0
	mov	r0,1
	strb	r0,[sp,11]
	b	.L12630

.L11991:	.data.w	Spi_ConfigPtr
	.endo	.L11991

.L12630:

;line4359
..lin.3629b354..d867860.0_18::
.LDWlin18:
..gh.beginasm.46:
	.endo	..gh.beginasm.46
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.47:
	.endo	..gh.endasm.47

;line4362
..lin.3629b354..d867860.0_19::
.LDWlin19:
	mov	r0,r5
	mov	r1,3
.L12633:

	bl	Spi_GetSeqDetStatus
	subs	r4,r0,0
	bne	.L12039
	ldr	r6,.L12631
	ldr	r1,[r6]
	ldr	r0,[r1,r5 lsl 2]
	ldr	r1,[r1,24]
	ldr	r0,[r0,8]
	ldrb	r1,[r1,r9]
	add	r7,r0,r1 lsl 4
	ldrh	r8,[r7,2]
.L12635:

	bl	SchM_Enter_Spi_AsyncTransmit
	mov	r0,0
.L12024:
	cmp	r0,r8
	bhs	.L12010
	ldr	r3,[r7,4]
	lsl	r2,r0,1
	ldr	r1,[r6]
	ldrh	r2,[r2,r3]
	ldr	r3,[r1,28]
	ldr	fp,[r1,r5 lsl 2]
	lsl	r2,r2,1
	ldrh	r2,[r2,r3]
	rsb	r3,r2,r2 lsl 2
	ldr	r2,[fp,12]
	add	r2,r2,r3 lsl 3
	ldrb	lr,[r2,5]
	mov	r3,0
	cmp	lr,0
	movne	r4,0
	moveq	r4,1
	moveq	r10,161
	b	.L12019
.L12018:
	str	r0,[sp]
	ldr	r0,[r2,8]
	ldrb	r12,[r0,r12]
	ldr	r0,[r1,32]
	ldrb	r0,[r0,r12]
	ldr	r12,[fp,16]
	add	r12,r12,r0 lsl 5
	ldr	r0,[r12,4]
	cmp	r0,1
	ldreq	r12,[r12,24]
	ldrheq	r12,[r12]
	ldr	r0,[sp]
	cmpeq	r12,0
	moveq	r10,169
	moveq	r4,1
	add	r3,r3,1<<24
.L12019:
	cmp	r4,0
	bne	.L12013
	lsr	r12,r3,24
	cmp	r12,lr
	blo	.L12018
.L12013:
	add	r0,r0,1
	cmp	r4,0
	uxth	r0,r0
	beq	.L12024
.L12010:
.L12637:

	bl	SchM_Exit_Spi_AsyncTransmit
	cmp	r4,1
	bne	.L12008
	mov	r3,r10
	mov	r2,3
	mov	r1,0
	mov	r0,83
.L12639:

	bl	Det_ReportError
	b	.L12027
.L12008:
	cmp	r4,0
	bne	.L12027
.L12641:

	bl	SchM_Enter_Spi_AsyncTransmit
	ldr	r1,.L12632
	ldr	r0,[r6]
	ldr	r10,[r1,r5 lsl 2]
	ldr	r0,[r0,24]
	ldr	r1,[r10]
	ldrb	r0,[r0,r9]
	ldr	r0,[r1,r0 lsl 4]
	cmp	r0,1
	bne	.L12029
.L12643:

	bl	SchM_Exit_Spi_AsyncTransmit
	mov	r4,1
	b	.L12607
.L12029:
	mov	r1,r9
	mov	r0,r5
.L12645:

	bl	Spi_AsyncCheckJobLinkStatus
	subs	r4,r0,0
	ldreq	r1,[r6]
	ldreq	r12,[r1,24]
	ldreq	r3,[r10]
	ldrbeq	r0,[r12,r9]
	moveq	r2,1
	streq	r2,[r3,r0 lsl 4]
	moveq	r2,0
	beq	.L12037
.L12032:
.L12647:

	bl	SchM_Exit_Spi_AsyncTransmit
.L12607:

	mov	r3,42
	mov	r2,3
	mov	r1,0
	mov	r0,83
.L12649:

	bl	Det_ReportRuntimeError
	b	.L12027
.L12036:
	ldr	r6,[r7,4]
	lsl	r0,r0,1
	ldrh	r0,[r0,r6]
	ldr	r6,[r1,28]
	lsl	r0,r0,1
	ldrh	r0,[r0,r6]
	rsb	r6,r0,r0 lsl 2
	ldr	r0,[r1,r5 lsl 2]
	ldr	r0,[r0,12]
	add	r2,r2,1<<16
	add	r0,r0,r6 lsl 3
	ldr	r0,[r0,20]
	mov	r6,3
	str	r6,[r0]
.L12037:
	lsr	r0,r2,16
	cmp	r0,r8
	blo	.L12036
	ldrb	r0,[r12,r9]
	sub	r1,r8,1
	ldr	r6,[r7,4]
	add	r0,r3,r0 lsl 4
	strh	r1,[r0,12]
	str	r6,[r0,8]
.L12651:

	bl	SchM_Exit_Spi_AsyncTransmit
	ldrh	r1,[r6]
	mov	r0,r5
.L12653:

	bl	Spi_AsyncScheduleJob
	strb	r0,[sp,11]
.L12027:
	ldrb	r1,[sp,11]
	cmp	r1,0
	moveq	r4,1
	moveq	r3,232
	moveq	r2,3
	moveq	r0,83
.L12655:

	bleq	Det_ReportRuntimeError
.L12039:
	mov	r0,r4
.LDW99:
	add	sp,sp,28
.L12657:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_AsyncTransmit::
	.endf	Spi_AsyncTransmit
;RetResult	[sp,11]	local
;CoreId	r5	local
;RetStatus	r4	local
;NumJobsInSequence	r8	local
;JobIdx	r0	local
;SeqStatePtr	r0	local
;JobIndexPtr	r6	local
;SeqCfgPtr	r7	local
;JobCfgPtr	r2	local
;ChannelCfgPtr	r12	local
;ErrorFlag	r10	local

;Sequence	r9	param

	.section ".ghcalltbl",""
.L12634:	.data.w	.L12633
	.endo	.L12634
.L12636:	.data.w	.L12635
	.endo	.L12636
.L12638:	.data.w	.L12637
	.endo	.L12638
.L12640:	.data.w	.L12639
	.endo	.L12640
.L12642:	.data.w	.L12641
	.endo	.L12642
.L12644:	.data.w	.L12643
	.endo	.L12644
.L12646:	.data.w	.L12645
	.endo	.L12646
.L12648:	.data.w	.L12647
	.endo	.L12648
.L12650:	.data.w	.L12649
	.endo	.L12650
.L12652:	.data.w	.L12651
	.endo	.L12652
.L12654:	.data.w	.L12653
	.endo	.L12654
.L12656:	.data.w	.L12655
	.endo	.L12656
	.section ".ghrettbl",""
.L12658:	.data.w	.L12657
	.endo	.L12658
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.SchM_Exit_Spi_AsyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_AsyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.48:
	.endo	..gh.f.a.1.e.48
__callee.Spi_ReadIB.i.ip::
	.size	__callee.Spi_ReadIB.i.ip,0
Spi_ReadIB::
.LDW001:
	push	{r2,r4-r7,lr}
	mov	r6,r0
	mov	r7,r1
.LDW101:
	b	.L12945

.L12631:	.data.w	Spi_ConfigPtr
	.endo	.L12631

.L12632:	.data.w	Spi_CoreStatus
	.endo	.L12632

.L12945:

;line4578
..lin.3629b354..ba0acb97.0_20::
.LDWlin20:
..gh.beginasm.49:
	.endo	..gh.beginasm.49
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.50:
	.endo	..gh.endasm.50

	mov	r5,r2
;line4581
..lin.3629b354..ba0acb97.0_21::
.LDWlin21:
	mov	r2,r0
	mov	r0,r5
	mov	r1,4
.L12947:

	bl	Spi_GetChannelDetStatus
	subs	r4,r0,0
	bne	.L12668
	cmp	r7,0
	bne	.L12669
	mov	r3,10
	mov	r2,4
	mov	r1,r0
	mov	r0,83
.L12949:

	bl	Det_ReportError
	mov	r4,1
	b	.L12668
.L12669:
	ldr	r1,.L12946
	ldr	r0,[r1]
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,32]
	ldr	r1,[r1,16]
	ldrb	r0,[r0,r6]
	add	r5,r1,r0 lsl 5
	ldr	r0,[r5,4]
	cmp	r0,0
	beq	.L12670
	mov	r4,1
	mov	r3,10
	mov	r2,4
	mov	r1,0
	mov	r0,83
.L12951:

	bl	Det_ReportError
	b	.L12668
.L12670:
.L12953:

	bl	SchM_Enter_Spi_ReadIB
	mov	r0,0
	b	.L12676
.L12675:
	ldr	r1,[r5,20]
	ldr	r1,[r1,8]
	ldrb	r1,[r1,r0]
	strb	r1,[r7,r0]
	add	r0,r0,1
.L12676:
	ldr	r1,[r5,12]
	ldrh	r2,[r5,16]
	mul	r1,r2,r1
	cmp	r0,r1
	blo	.L12675
.L12955:

	bl	SchM_Exit_Spi_ReadIB
.L12668:
	mov	r0,r4
.LDW201:
.L12957:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Spi_ReadIB::
	.endf	Spi_ReadIB
;CoreId	r5	local
;RetStatus	r4	local
;DataIndex	r0	local
;ChannelCfgPtr	r5	local

;Channel	r6	param
;DataBufferPtr	r7	param

	.section ".ghcalltbl",""
.L12948:	.data.w	.L12947
	.endo	.L12948
.L12950:	.data.w	.L12949
	.endo	.L12950
.L12952:	.data.w	.L12951
	.endo	.L12952
.L12954:	.data.w	.L12953
	.endo	.L12954
.L12956:	.data.w	.L12955
	.endo	.L12956
	.section ".ghrettbl",""
.L12958:	.data.w	.L12957
	.endo	.L12958
	.data
	.global	__caller.SchM_Exit_Spi_ReadIB.v.v

	.global	__caller.SchM_Enter_Spi_ReadIB.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.51:
	.endo	..gh.f.a.1.e.51
__callee.Spi_SetupEB.i.ippi::
	.size	__callee.Spi_SetupEB.i.ippi,0
Spi_SetupEB::
.LDW301:
	push	{r2,r4-r9,lr}
	mov	r7,r0
	mov	r8,r1
	mov	r9,r2
	mov	r6,r3
.LDW401:
	b	.L13157

.L12946:	.data.w	Spi_ConfigPtr
	.endo	.L12946

.L13157:

;line4715
..lin.3629b354..49c045c8.0_22::
.LDWlin22:
..gh.beginasm.52:
	.endo	..gh.beginasm.52
 mrc p15, 0, r1, c0, c0, 5
 and r12, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r12, r12, r1         

..gh.endasm.53:
	.endo	..gh.endasm.53

	mov	r5,r12
;line4718
..lin.3629b354..49c045c8.0_23::
.LDWlin23:
	mov	r2,r0
	mov	r0,r12
	mov	r1,5
.L13159:

	bl	Spi_GetChannelDetStatus
	subs	r4,r0,0
	bne	.L12965
	ldr	r1,.L13158
	ldr	r0,[r1]
	ldr	r1,[r0,r5 lsl 2]
	ldr	r0,[r0,32]
	ldr	r1,[r1,16]
	ldrb	r0,[r0,r7]
	cmp	r6,0
	add	r5,r1,r0 lsl 5
	beq	.L12968
	ldrh	r0,[r5,16]
	cmp	r6,r0
	bls	.L12967
.L12968:
	mov	r4,1
	mov	r3,13
	b	.L13147
.L12967:
	ldr	r0,[r5,4]
	cmp	r0,1
	beq	.L12971
.L12972:
	mov	r4,1
	mov	r3,10
.L13147:

	mov	r2,5
	mov	r1,0
	mov	r0,83
.L13161:

	bl	Det_ReportError
	b	.L12965
.L12971:
.L13163:

	bl	SchM_Enter_Spi_SetupEB
	ldr	r0,[r5,20]
	stmib	r0,{r8-r9}
	ldr	r0,[r5,24]
	strh	r6,[r0]
.L13165:

	bl	SchM_Exit_Spi_SetupEB
.L12965:
	mov	r0,r4
.LDW501:
.L13167:

	pop	{r2,r4-r9,pc}
__ghs_eofn_Spi_SetupEB::
	.endf	Spi_SetupEB
;CoreId	r5	local
;RetStatus	r4	local
;ChannelCfgPtr	r5	local

;Channel	r7	param
;SrcDataBufferPtr	r8	param
;DesDataBufferPtr	r9	param
;Length	r6	param

	.section ".ghcalltbl",""
.L13160:	.data.w	.L13159
	.endo	.L13160
.L13162:	.data.w	.L13161
	.endo	.L13162
.L13164:	.data.w	.L13163
	.endo	.L13164
.L13166:	.data.w	.L13165
	.endo	.L13166
	.section ".ghrettbl",""
.L13168:	.data.w	.L13167
	.endo	.L13168
	.data
	.global	__caller.SchM_Exit_Spi_SetupEB.v.v

	.global	__caller.SchM_Enter_Spi_SetupEB.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.54:
	.endo	..gh.f.a.1.e.54
__callee.Spi_GetStatus.i.v::
	.size	__callee.Spi_GetStatus.i.v,0
Spi_GetStatus::
.LDW601:
	push	{r2,r4-r5,lr}
.LDW701:
	mov	r4,1
	b	.L13264

.L13158:	.data.w	Spi_ConfigPtr
	.endo	.L13158

.L13264:

;line4844
..lin.3629b354..f61cc734.0_24::
.LDWlin24:
..gh.beginasm.55:
	.endo	..gh.beginasm.55
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.56:
	.endo	..gh.endasm.56

	mov	r5,r0
;line4848
..lin.3629b354..f61cc734.0_25::
.LDWlin25:
	mov	r1,6
.L13265:

	bl	Spi_GetCommonDetStatus
	cmp	r0,0
	bne	.L13175
.L13267:

	bl	SchM_Enter_Spi_GetStatus
	mov	r0,r5
.L13269:

	bl	Spi_GetDriverStatus
	mov	r4,r0
.L13271:

	bl	SchM_Exit_Spi_GetStatus
.L13175:
	mov	r0,r4
.LDW801:
.L13273:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Spi_GetStatus::
	.endf	Spi_GetStatus
;CoreId	r5	local
;SpiStatus	r4	local

	.section ".bss","awb"
.L13222:
	.endo	.L13222
	.section ".ghcalltbl",""
.L13266:	.data.w	.L13265
	.endo	.L13266
.L13268:	.data.w	.L13267
	.endo	.L13268
.L13270:	.data.w	.L13269
	.endo	.L13270
.L13272:	.data.w	.L13271
	.endo	.L13272
	.section ".ghrettbl",""
.L13274:	.data.w	.L13273
	.endo	.L13274
	.data
	.global	__caller.SchM_Exit_Spi_GetStatus.v.v

	.global	__caller.SchM_Enter_Spi_GetStatus.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.57:
	.endo	..gh.f.a.1.e.57
__callee.Spi_GetJobResult.i.i::
	.size	__callee.Spi_GetJobResult.i.i,0
Spi_GetJobResult::
.LDW901:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW011:
	mov	r4,2
..gh.beginasm.58:
	.endo	..gh.beginasm.58
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.59:
	.endo	..gh.endasm.59

	mov	r5,r2
;line4918
..lin.3629b354..44ba18aa.0_26::
.LDWlin26:
	mov	r2,r0
	mov	r0,r5
	mov	r1,7
.L13379:

	bl	Spi_GetJobDetStatus
	cmp	r0,0
	ldreq	r0,.L13378
	ldreq	r2,[r0]
	lsleq	r0,r6,1
	ldreq	r1,[r2,28]
	ldrheq	r1,[r0,r1]
	rsbeq	r0,r1,r1 lsl 2
	ldreq	r1,[r2,r5 lsl 2]
	ldreq	r1,[r1,12]
	addeq	r1,r1,r0 lsl 3
	ldreq	r4,[r1,20]
	ldreq	r4,[r4]
	mov	r0,r4
.LDW111:
.L13381:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_GetJobResult::
	.endf	Spi_GetJobResult
;CoreId	r5	local
;JobResult	r4	local

;Job	r6	param

	.section ".ghcalltbl",""
.L13380:	.data.w	.L13379
	.endo	.L13380
	.section ".ghrettbl",""
.L13382:	.data.w	.L13381
	.endo	.L13382
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.60:
	.endo	..gh.f.a.1.e.60
__callee.Spi_GetSequenceResult.i.i::
	.size	__callee.Spi_GetSequenceResult.i.i,0
Spi_GetSequenceResult::
.LDW211:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW311:
	mov	r4,2
	b	.L13474

.L13378:	.data.w	Spi_ConfigPtr
	.endo	.L13378

.L13474:

;line4987
..lin.3629b354..a0ff7a28.0_27::
.LDWlin27:
..gh.beginasm.61:
	.endo	..gh.beginasm.61
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.62:
	.endo	..gh.endasm.62

	mov	r5,r2
;line4991
..lin.3629b354..a0ff7a28.0_28::
.LDWlin28:
	mov	r2,r0
	mov	r0,r5
	mov	r1,8
.L13477:

	bl	Spi_GetSeqDetStatus
	cmp	r0,0
	ldreq	r1,.L13475
	ldreq	r0,[r1]
	ldreq	r1,.L13476
	ldreq	r4,[r1,r5 lsl 2]
	ldreq	r0,[r0,24]
	ldreq	r4,[r4]
	ldrbeq	r0,[r0,r6]
	ldreq	r4,[r4,r0 lsl 4]
	mov	r0,r4
.LDW411:
.L13479:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_GetSequenceResult::
	.endf	Spi_GetSequenceResult
;CoreId	r5	local
;SeqResult	r4	local

;Sequence	r6	param

	.section ".ghcalltbl",""
.L13478:	.data.w	.L13477
	.endo	.L13478
	.section ".ghrettbl",""
.L13480:	.data.w	.L13479
	.endo	.L13480
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.63:
	.endo	..gh.f.a.1.e.63
__callee.Spi_GetVersionInfo.v.p::
	.size	__callee.Spi_GetVersionInfo.v.p,0
Spi_GetVersionInfo::
.LDW511:
.LDW611:
	movs	r1,r0
	moveq	r3,16
	moveq	r2,9
	moveq	r0,83
.L13563:

	beq	Det_ReportError
.L13483:
	mov	r1,175
	strh	r1,[r0]
	mov	r1,83
	strh	r1,[r0,2]
	mov	r1,1
	strb	r1,[r0,4]
	mov	r1,2
	strb	r1,[r0,5]
	mov	r1,0
	strb	r1,[r0,6]
.LDW711:
.L13565:

	ret	
__ghs_eofn_Spi_GetVersionInfo::
	.endf	Spi_GetVersionInfo

;VersionInfoPtr	r0	param

	.section ".bss","awb"
.L13525:
	.endo	.L13525
	.section ".ghtailcalltbl",""
	.align	4
.L13564:	.data.w	.L13563
	.endo	.L13564
	.section ".ghrettbl",""
.L13566:	.data.w	.L13565
	.endo	.L13566
	.data
	.global	__caller.Det_ReportError.i.iiii

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.64:
	.endo	..gh.f.a.1.e.64
__callee.Spi_SyncTransmit.i.i::
	.size	__callee.Spi_SyncTransmit.i.i,0
Spi_SyncTransmit::
.LDW811:
	push	{r4-fp,lr}
	sub	sp,sp,20
	mov	fp,r0
	mov	r2,r0
	mov	r0,0
.LDW911:
	mov	r9,1
	strb	r0,[sp,7]
	b	.L16768

.L13475:	.data.w	Spi_ConfigPtr
	.endo	.L13475

.L13476:	.data.w	Spi_CoreStatus
	.endo	.L13476

.L16768:

;line5130
..lin.3629b354..4b9ab87f.0_29::
.LDWlin29:
..gh.beginasm.65:
	.endo	..gh.beginasm.65
 mrc p15, 0, r1, c0, c0, 5
 and r6, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r6, r6, r1         

..gh.endasm.66:
	.endo	..gh.endasm.66

;line5136
..lin.3629b354..4b9ab87f.0_30::
.LDWlin30:
	mov	r0,r6
	mov	r1,10
.L16771:

	bl	Spi_GetSeqDetStatus
	subs	r5,r0,0
	bne	.L13614
	ldr	r8,.L16769
	ldr	r0,[r8]
	ldr	r1,[r0,r6 lsl 2]
	ldr	r0,[r0,24]
	ldr	r1,[r1,8]
	ldrb	r0,[r0,fp]
	add	r7,r1,r0 lsl 4
.L16773:

	bl	SchM_Enter_Spi_SyncTransmit
	ldr	r1,.L16770
	ldr	r10,[r1,r6 lsl 2]
	ldr	r0,[r10,20]
	ldrh	r1,[r7,8]
	ldrh	r0,[r0]
	ands	r1,r0,r1
	bne	.L13575
	b	.L13591
.L13586:
	ldr	lr,[r4,8]
	ldrb	r12,[lr,r12]
	ldr	lr,[r0,32]
	ldrb	r12,[lr,r12]
	ldr	lr,[r3,16]
	add	r12,lr,r12 lsl 5
	ldr	r12,[r12,24]
	ldrh	r12,[r12]
	cmp	r12,0
	moveq	r12,169
	moveq	r5,r9
	strbeq	r12,[sp,7]
	add	r2,r2,1<<24
.L13587:
	cmp	r5,0
	bne	.L13580
	ldrb	lr,[r4,5]
	lsr	r12,r2,24
	cmp	r12,lr
	blo	.L13586
.L13580:
	add	r1,r1,1
	cmp	r5,0
	uxth	r1,r1
	bne	.L13592
.L13591:
	ldrh	r0,[r7,2]
	cmp	r1,r0
	bhs	.L13592
	ldr	r12,[r7,4]
	ldr	r0,[r8]
	lsl	r2,r1,1
	ldrh	r2,[r2,r12]
	ldr	r12,[r0,28]
	ldr	r3,[r0,r6 lsl 2]
	lsl	r2,r2,1
	ldrh	r2,[r2,r12]
	ldr	r4,[r3,12]
	rsb	r2,r2,r2 lsl 2
	add	r4,r4,r2 lsl 3
	ldr	r2,[r0,40]
	ldrb	r12,[r4,2]
	ldrb	r2,[r2,r12]
	rsb	r12,r2,r2 lsl 3
	ldr	r2,[r10,4]
	add	r2,r2,r12 lsl 2
	ldr	r2,[r2,4]
	cmp	r2,3
	bne	.L13581
	ldr	r2,[r0,24]
	ldr	r12,[r10]
	ldrb	r2,[r2,fp]
	ldr	r2,[r12,r2 lsl 4]
	cmp	r2,3
	movne	r2,58
	movne	r5,r9
	strbne	r2,[sp,7]
.L13581:
	mov	r2,0
	b	.L13587
.L13575:
	mov	r0,58
	mov	r5,r9
	strb	r0,[sp,7]
.L13592:
.L16775:

	bl	SchM_Exit_Spi_SyncTransmit
	ldrb	r0,[sp,7]
	cmp	r0,58
	bne	.L13593
	mov	r3,r0
	mov	r2,10
	mov	r1,0
	mov	r0,83
.L16777:

	bl	Det_ReportRuntimeError
	b	.L13573
.L13593:
	cmp	r0,169
	moveq	r3,r0
	moveq	r2,10
	moveq	r1,0
	moveq	r0,83
.L16779:

	bleq	Det_ReportError
.L13573:
	cmp	r5,0
	bne	.L13599
.L16781:

	bl	SchM_Enter_Spi_SyncTransmit
	ldr	r0,[r8]
	ldr	r1,[r0,24]
	ldr	r2,[r10]
	ldrb	r1,[r1,fp]
	str	r9,[r2,r1 lsl 4]
	mov	r2,r5
	b	.L13604
.L13603:
	ldr	r3,[r7,4]
	lsl	r1,r1,1
	ldrh	r1,[r1,r3]
	ldr	r3,[r0,28]
	ldr	r4,[r0,r6 lsl 2]
	lsl	r1,r1,1
	ldrh	r1,[r1,r3]
	ldr	r4,[r4,12]
	rsb	r1,r1,r1 lsl 2
	add	r4,r4,r1 lsl 3
	ldr	r1,[r10,20]
	ldrb	r3,[r4,2]
	ldrh	r12,[r1]
	add	r2,r2,1<<16
	orr	r3,r12,r9 lsl r3
	strh	r3,[r1]
.L13604:
	ldrh	r3,[r7,2]
	lsr	r1,r2,16
	cmp	r1,r3
	blo	.L13603
.L16783:

	bl	SchM_Exit_Spi_SyncTransmit
	mov	r1,fp
	mov	r0,r6
.L16785:

	bl	Spi_SyncStartTransmit
	and	r9,r9,r0
	cmp	r9,1
	moveq	r0,r5
	movne	r0,2
	ldr	r1,[r8]
	ldr	r1,[r1,24]
	ldr	r2,[r10]
	ldrb	r1,[r1,fp]
	mov	fp,r5
	str	r0,[r2,r1 lsl 4]
	b	.L13611
.L13610:
	ldr	r2,[r7,4]
	lsl	r1,r1,1
	ldr	r0,[r8]
	ldrh	r1,[r1,r2]
	ldr	r2,[r0,28]
	ldr	r4,[r0,r6 lsl 2]
	lsl	r1,r1,1
	ldrh	r1,[r1,r2]
	ldr	r4,[r4,12]
	rsb	r1,r1,r1 lsl 2
	add	r4,r4,r1 lsl 3
.L16787:

	bl	SchM_Enter_Spi_SyncTransmit
	ldrb	r2,[r4,2]
	ldr	r1,[r10,20]
	mov	r0,1
	lsl	r2,r0,r2
	ldrh	r0,[r1]
	bic	r0,r0,r2
	strh	r0,[r1]
.L16789:

	bl	SchM_Exit_Spi_SyncTransmit
	ldrh	r1,[r4]
	mov	r0,r6
.L16791:

	bl	Spi_AsyncScheduleNextJob
	and	r9,r9,r0
	add	fp,fp,1<<16
.L13611:
	ldrh	r0,[r7,2]
	lsr	r1,fp,16
	cmp	r1,r0
	blo	.L13610
	ldr	r0,[r7,12]
	cmp	r0,0
.L16793:

	blxne	r0
.L13599:
	movs	r1,r9
	moveq	r5,1
	moveq	r3,232
	moveq	r2,10
	moveq	r0,83
.L16795:

	bleq	Det_ReportRuntimeError
.L13614:
	mov	r0,r5
.LDW021:
	add	sp,sp,20
.L16797:

	pop	{r4-fp,pc}
__ghs_eofn_Spi_SyncTransmit::
	.endf	Spi_SyncTransmit
;CoreId	r6	local
;RetResult	r9	local
;RetStatus	r5	local
;JobIndex	r1	local
;JobCfgPtr	r4	local
;SeqCfgPtr	r7	local
;ErrorFlag	[sp,7]	local

;Sequence	fp	param

	.section ".ghcalltbl",""
.L16772:	.data.w	.L16771
	.endo	.L16772
.L16774:	.data.w	.L16773
	.endo	.L16774
.L16776:	.data.w	.L16775
	.endo	.L16776
.L16778:	.data.w	.L16777
	.endo	.L16778
.L16780:	.data.w	.L16779
	.endo	.L16780
.L16782:	.data.w	.L16781
	.endo	.L16782
.L16784:	.data.w	.L16783
	.endo	.L16784
.L16786:	.data.w	.L16785
	.endo	.L16786
.L16788:	.data.w	.L16787
	.endo	.L16788
.L16790:	.data.w	.L16789
	.endo	.L16790
.L16792:	.data.w	.L16791
	.endo	.L16792
.L16794:	.data.w	.L16793
	.endo	.L16794
.L16796:	.data.w	.L16795
	.endo	.L16796
	.section ".ghrettbl",""
.L16798:	.data.w	.L16797
	.endo	.L16798
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.global	__caller.Det_ReportError.i.iiii

	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_SyncTransmit.v.v

	.global	__caller.SchM_Enter_Spi_SyncTransmit.v.v

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.67:
	.endo	..gh.f.a.1.e.67
__callee.Spi_GetHWUnitStatus.i.i::
	.size	__callee.Spi_GetHWUnitStatus.i.i,0
Spi_GetHWUnitStatus::
.LDW121:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW221:
	mov	r4,1
	b	.L16893

.L16769:	.data.w	Spi_ConfigPtr
	.endo	.L16769

.L16770:	.data.w	Spi_CoreStatus
	.endo	.L16770

.L16893:

;line5416
..lin.3629b354..25b615b3.0_31::
.LDWlin31:
..gh.beginasm.68:
	.endo	..gh.beginasm.68
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.69:
	.endo	..gh.endasm.69

	mov	r5,r2
;line5420
..lin.3629b354..25b615b3.0_32::
.LDWlin32:
	mov	r2,r0
	mov	r0,r5
	mov	r1,11
.L16896:

	bl	Spi_GetPhyUnitDetStatus
	cmp	r0,0
	ldreq	r1,.L16894
	ldreq	r1,[r1]
	ldreq	r1,[r1,40]
	ldrbeq	r1,[r1,r6]
	rsbeq	r0,r1,r1 lsl 3
	ldreq	r1,.L16895
	ldreq	r1,[r1,r5 lsl 2]
	ldreq	r1,[r1,4]
	addeq	r1,r1,r0 lsl 2
	ldreq	r4,[r1,4]
	mov	r0,r4
.LDW321:
.L16898:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_GetHWUnitStatus::
	.endf	Spi_GetHWUnitStatus
;CoreId	r5	local
;PhyUnitStatus	r4	local

;HWUnit	r6	param

	.section ".ghcalltbl",""
.L16897:	.data.w	.L16896
	.endo	.L16897
	.section ".ghrettbl",""
.L16899:	.data.w	.L16898
	.endo	.L16899
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.70:
	.endo	..gh.f.a.1.e.70
__callee.Spi_Cancel.v.i::
	.size	__callee.Spi_Cancel.v.i,0
Spi_Cancel::
.LDW421:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW521:
	b	.L16977

.L16894:	.data.w	Spi_ConfigPtr
	.endo	.L16894

.L16895:	.data.w	Spi_CoreStatus
	.endo	.L16895

.L16977:

;line5486
..lin.3629b354..96cc2896.0_33::
.LDWlin33:
..gh.beginasm.71:
	.endo	..gh.beginasm.71
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.72:
	.endo	..gh.endasm.72

	mov	r4,r2
;line5490
..lin.3629b354..96cc2896.0_34::
.LDWlin34:
	mov	r2,r0
	mov	r0,r4
	mov	r1,12
.L16980:

	bl	Spi_GetSeqDetStatus
	cmp	r0,0
	ldreq	r1,.L16978
	ldreq	r0,[r1]
	ldreq	r1,.L16979
	ldreq	r1,[r1,r4 lsl 2]
	ldreq	r0,[r0,24]
	ldreq	r1,[r1]
	ldrbeq	r0,[r0,r5]
	moveq	r2,3
	streq	r2,[r1,r0 lsl 4]
.LDW621:
.L16982:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Spi_Cancel::
	.endf	Spi_Cancel
;CoreId	r4	local

;Sequence	r5	param

	.section ".ghcalltbl",""
.L16981:	.data.w	.L16980
	.endo	.L16981
	.section ".ghrettbl",""
.L16983:	.data.w	.L16982
	.endo	.L16983
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.73:
	.endo	..gh.f.a.1.e.73
__callee.Spi_SetAsyncMode.i.i::
	.size	__callee.Spi_SetAsyncMode.i.i,0
Spi_SetAsyncMode::
.LDW721:
	push	{r4-r6,lr}
	mov	r6,r0
.LDW821:
	b	.L17268

.L16978:	.data.w	Spi_ConfigPtr
	.endo	.L16978

.L16979:	.data.w	Spi_CoreStatus
	.endo	.L16979

.L17268:

;line5556
..lin.3629b354..545c989f.0_35::
.LDWlin35:
..gh.beginasm.74:
	.endo	..gh.beginasm.74
 mrc p15, 0, r1, c0, c0, 5
 and r5, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r5, r5, r1         

..gh.endasm.75:
	.endo	..gh.endasm.75

;line5559
..lin.3629b354..545c989f.0_36::
.LDWlin36:
	mov	r0,r5
	mov	r1,13
.L17271:

	bl	Spi_GetCommonDetStatus
	subs	r4,r0,0
	bne	.L16990
.L17273:

	bl	SchM_Enter_Spi_SetAsyncMode
	mov	r0,r5
.L17275:

	bl	Spi_AsyncGetPhyUnitStatus
	mov	r4,r0
.L17277:

	bl	SchM_Exit_Spi_SetAsyncMode
	cmp	r4,3
	bne	.L16992
	mov	r4,1
	mov	r3,42
	mov	r2,13
	mov	r1,0
	mov	r0,83
.L17279:

	bl	Det_ReportRuntimeError
	b	.L16990
.L16992:
	ldr	r1,.L17269
	ldr	r3,[r1,r5 lsl 2]
	ldr	r0,[r3,16]
	ldr	r1,.L17270
	str	r6,[r0]
	ldr	r2,[r1]
	mov	r1,0
	ldr	r2,[r2,r5 lsl 2]
	b	.L16998
.L16997:
	cmp	r6,1
	bne	.L16999
	ldr	r12,[r2,24]
	add	r0,r12,r0 lsl 4
	ldrb	r0,[r0,1]
	cmp	r0,255
	movne	r12,r6
	bne	.L16996
.L16999:
	mov	r12,0
.L16996:
	lsr	r0,r1,24
	ldr	r4,[r3,4]
	rsb	r0,r0,r0 lsl 3
	add	r1,r1,1<<24
	strb	r12,[r4,r0 lsl 2]
.L16998:
	ldrb	r12,[r2,6]
	lsr	r0,r1,24
	cmp	r0,r12
	blo	.L16997
	mov	r4,0
.L16990:
	mov	r0,r4
.LDW921:
.L17281:

	pop	{r4-r6,pc}
__ghs_eofn_Spi_SetAsyncMode::
	.endf	Spi_SetAsyncMode
;CoreId	r5	local
;RetStatus	r4	local
;SpiStatus	r4	local
;CurrentCoreConfigPtr	r2	local

;Mode	r6	param

	.section ".ghcalltbl",""
.L17272:	.data.w	.L17271
	.endo	.L17272
.L17274:	.data.w	.L17273
	.endo	.L17274
.L17276:	.data.w	.L17275
	.endo	.L17276
.L17278:	.data.w	.L17277
	.endo	.L17278
.L17280:	.data.w	.L17279
	.endo	.L17280
	.section ".ghrettbl",""
.L17282:	.data.w	.L17281
	.endo	.L17282
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.SchM_Exit_Spi_SetAsyncMode.v.v

	.global	__caller.SchM_Enter_Spi_SetAsyncMode.v.v

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Spi_ConfigPtr - Spi_ConfigPtr) +0 == 0
..gh.f.a.1.e.76:
	.endo	..gh.f.a.1.e.76
__callee.Spi_MainFunction_Handling.v.v::
	.size	__callee.Spi_MainFunction_Handling.v.v,0
Spi_MainFunction_Handling::
.LDW031:
	push	{r2,r4-r7,lr}
.LDW131:
	b	.L17653

.L17269:	.data.w	Spi_CoreStatus
	.endo	.L17269

.L17270:	.data.w	Spi_ConfigPtr
	.endo	.L17270

.L17653:

;line5668
..lin.3629b354..9d97741f.0_37::
.LDWlin37:
..gh.beginasm.77:
	.endo	..gh.beginasm.77
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.78:
	.endo	..gh.endasm.78

	mov	r4,r0
;line5671
..lin.3629b354..9d97741f.0_38::
.LDWlin38:
	mov	r1,16
.L17656:

	bl	Spi_GetCommonDetStatus
	subs	r5,r0,0
.L17658:

	popne	{r2,r4-r7,pc}
	b	.L17294
.L17293:
	lsr	r0,r5,24
	ldr	r3,[r1,4]
	rsb	r2,r0,r0 lsl 3
	add	r2,r3,r2 lsl 2
	ldr	r2,[r2,4]
	cmp	r2,3
	bne	.L17292
	ldr	r1,[r1,8]
	add	r0,r0,r0 lsl 2
	add	r0,r1,r0 lsl 3
	ldr	r7,[r0,4]
	ldrb	r7,[r7,2]
	mov	r0,r4
	mov	r1,r7
.L17660:

	bl	Spi_IsrError
	ldr	r0,[r6]
	ldr	r0,[r0,48]
	mov	r1,1<<10
	ldr	r0,[r0,r7 lsl 2]
.L17662:

	bl	Espi_Hal_GetFlagStatus
	cmp	r0,0
	beq	.L17292
	mov	r1,r7
	mov	r0,r4
.L17664:

	bl	Spi_AsyncIsrFifoRx
	movs	r1,r0
	moveq	r3,232
	moveq	r2,16
	moveq	r0,83
.L17666:

	bleq	Det_ReportRuntimeError
.L17292:
	add	r5,r5,1<<24
.L17294:
	ldr	r6,.L17654
	ldr	r0,[r6]
	ldr	r0,[r0,r4 lsl 2]
	ldrb	r0,[r0,6]
	cmp	r0,r5 lsr 24
.L17668:

	popls	{r2,r4-r7,pc}
	ldr	r1,.L17655
	ldr	r1,[r1,r4 lsl 2]
	ldr	r0,[r1,16]
	ldr	r0,[r0]
	cmp	r0,0
	beq	.L17293
.LDW231:
.L17670:

	pop	{r2,r4-r7,pc}
__ghs_eofn_Spi_MainFunction_Handling::
	.endf	Spi_MainFunction_Handling
;CoreId	r4	local
;PhyUnit	r7	local
;RetStatus	r5	local

	.section ".ghcalltbl",""
.L17657:	.data.w	.L17656
	.endo	.L17657
	.section ".ghrettbl",""
.L17659:	.data.w	.L17658
	.endo	.L17659
	.section ".ghcalltbl",""
.L17661:	.data.w	.L17660
	.endo	.L17661
.L17663:	.data.w	.L17662
	.endo	.L17663
.L17665:	.data.w	.L17664
	.endo	.L17665
.L17667:	.data.w	.L17666
	.endo	.L17667
	.section ".ghrettbl",""
.L17669:	.data.w	.L17668
	.endo	.L17669
.L17671:	.data.w	.L17670
	.endo	.L17671
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.global	__caller.Espi_Hal_GetFlagStatus.i.pi

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.79:
	.endo	..gh.f.a.1.e.79
__callee.Spi_FifoRx_ISRHandler.v.i::
	.size	__callee.Spi_FifoRx_ISRHandler.v.i,0
Spi_FifoRx_ISRHandler::
.LDW331:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW431:
	b	.L17773

.L17654:	.data.w	Spi_ConfigPtr
	.endo	.L17654

.L17655:	.data.w	Spi_CoreStatus
	.endo	.L17655

.L17773:

;line5753
..lin.3629b354..c952cfc9.0_39::
.LDWlin39:
..gh.beginasm.80:
	.endo	..gh.beginasm.80
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.81:
	.endo	..gh.endasm.81

	mov	r4,r2
;line5757
..lin.3629b354..c952cfc9.0_40::
.LDWlin40:
	mov	r2,r0
	mov	r0,r4
	mov	r1,224
.L17774:

	bl	Spi_GetPhyUnitDetStatus
	cmp	r0,0
.L17776:

	popne	{r2,r4-r5,pc}
	mov	r1,r5
	mov	r0,r4
.L17778:

	bl	Spi_AsyncIsrFifoRx
	movs	r1,r0
	moveq	r3,232
	moveq	r2,224
	moveq	r0,83
.L17780:

	bleq	Det_ReportRuntimeError
.LDW531:
.L17782:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Spi_FifoRx_ISRHandler::
	.endf	Spi_FifoRx_ISRHandler
;CoreId	r4	local

;PhyUnit	r5	param

	.section ".bss","awb"
.L17734:
	.endo	.L17734
	.section ".ghcalltbl",""
.L17775:	.data.w	.L17774
	.endo	.L17775
	.section ".ghrettbl",""
.L17777:	.data.w	.L17776
	.endo	.L17777
	.section ".ghcalltbl",""
.L17779:	.data.w	.L17778
	.endo	.L17779
.L17781:	.data.w	.L17780
	.endo	.L17781
	.section ".ghrettbl",""
.L17783:	.data.w	.L17782
	.endo	.L17783
	.data
	.global	__caller.Det_ReportRuntimeError.i.iiii

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.82:
	.endo	..gh.f.a.1.e.82
__callee.Spi_Error_ISRHandler.v.i::
	.size	__callee.Spi_Error_ISRHandler.v.i,0
Spi_Error_ISRHandler::
.LDW631:
	push	{r2,r4-r5,lr}
	mov	r5,r0
.LDW731:
..gh.beginasm.83:
	.endo	..gh.beginasm.83
 mrc p15, 0, r1, c0, c0, 5
 and r2, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r2, r2, r1         

..gh.endasm.84:
	.endo	..gh.endasm.84

	mov	r4,r2
;line5816
..lin.3629b354..9bcbbb25.0_41::
.LDWlin41:
	mov	r2,r0
	mov	r0,r4
	mov	r1,225
.L17853:

	bl	Spi_GetPhyUnitDetStatus
	cmp	r0,0
	moveq	r1,r5
	moveq	r0,r4
.L17855:

	bleq	Spi_IsrError
.LDW831:
.L17857:

	pop	{r2,r4-r5,pc}
__ghs_eofn_Spi_Error_ISRHandler::
	.endf	Spi_Error_ISRHandler
;CoreId	r4	local

;PhyUnit	r5	param

	.section ".bss","awb"
.L17823:
	.endo	.L17823
	.section ".ghcalltbl",""
.L17854:	.data.w	.L17853
	.endo	.L17854
.L17856:	.data.w	.L17855
	.endo	.L17856
	.section ".ghrettbl",""
.L17858:	.data.w	.L17857
	.endo	.L17858
	.section ".mcal_text_asil_d","ax"
;Spi_SequenceStateCore0	Spi_SequenceStateCore0	static
;Spi_PhyUnitStateCore0	Spi_PhyUnitStateCore0	static
;Spi_DeviceStateCore0	Spi_DeviceStateCore0	static
;Spi_SyncTransferStatusCore0	Spi_SyncTransferStatusCore0	static
;Spi_InitStatusCore0	Spi_InitStatusCore0	static
;Spi_AsyncModeCore0	Spi_AsyncModeCore0	static
;Spi_StatusSetCore0	Spi_StatusSetCore0	static
;Spi_SequenceStateCore1	Spi_SequenceStateCore1	static
;Spi_PhyUnitStateCore1	Spi_PhyUnitStateCore1	static
;Spi_DeviceStateCore1	Spi_DeviceStateCore1	static
;Spi_SyncTransferStatusCore1	Spi_SyncTransferStatusCore1	static
;Spi_InitStatusCore1	Spi_InitStatusCore1	static
;Spi_AsyncModeCore1	Spi_AsyncModeCore1	static
;Spi_StatusSetCore1	Spi_StatusSetCore1	static
;Spi_RxBuffer	Spi_RxBuffer	static
;Spi_ConfigPtr	Spi_ConfigPtr	static
;Spi_CoreStatus	Spi_CoreStatus	static

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A682576..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	178,87,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,83,112,105,92,115,114,99,47,83,112,105,46,99,0
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
	.data.b	33,25,0,0
	.data.b	2,0
	.data.b	130,8,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,83,112,105,92,115,114,99,47,83,112,105,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,83,112,105,92,105,110,99,108,117,100,101,92,83,112,105,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,83,112,105,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,83,112,105,95,80,66,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,83,112,105,92,105,110,99,108,117,100,101,92,83,112,105,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,101,115,112,105,92,105,110,99,92,101,115,112,105,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,101,115,112,105,92,105,110,99,92,101,115,112,105,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,101,115,112,105,92,105,110,99,92,101,115,112,105,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,112,105,95,77,101,109,77,97,112,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,83,112,105,92,105,110,99,108,117,100,101,92,83,112,105,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,66,83,87,92,83,99,104,77,92,105,110,99,108,117,100,101,92,83,99,104,77,95,83,112,105,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,105,111,92,105,110,99,108,117,100,101,92,68,105,111,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,105,111,92,105,110,99,108,117,100,101,92,68,105,111,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,105,111,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,105,111,92,105,110,99,108,117,100,101,92,68,105,111,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,68,105,111,95,77,101,109,77,97,112,46,104,0
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
	.data.w	.Ldw_begin+2349
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
	.data.w	.Ldw_begin+2158
	.data.b	1

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+2158

	.section	.debug_abbrev		;off: 39
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 75
	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2098
	.data.b	0

	.section	.debug_abbrev		;off: 46
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 87
	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+7128

	.data.b	47
	.data.w	.Ldw_begin+7695

	.section	.debug_abbrev		;off: 55
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 110
	.data.b	53
	.data.w	.Ldw_begin+105

	.section	.debug_abbrev		;off: 62
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 115
	.data.b	47
	.data.w	.Ldw_begin+110

	.data.b	53
	.data.w	.Ldw_begin+7695

	.data.b	47
	.data.w	.Ldw_begin+120

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+13798

	.data.b	53
	.data.w	.Ldw_begin+187

	.data.b	42
	.section	.debug_str		;off: 245
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 198
	.data.w	.Ldw_str_begin+245
	.data.b	7
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11772
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+11910
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+11910
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+13153

	.data.b	53
	.data.w	.Ldw_begin+324

	.data.b	47
	.data.w	.Ldw_begin+11784

	.data.b	53
	.data.w	.Ldw_begin+334

	.data.b	47
	.data.w	.Ldw_begin+12415

	.data.b	53
	.data.w	.Ldw_begin+344

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+11772

	.data.b	53
	.data.w	.Ldw_begin+373

	.data.b	47
	.data.w	.Ldw_begin+12979

	.data.b	53
	.data.w	.Ldw_begin+383

	.data.b	47
	.data.w	.Ldw_begin+12538

	.data.b	53
	.data.w	.Ldw_begin+393

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+13276

	.data.b	53
	.data.w	.Ldw_begin+460

	.data.b	47
	.data.w	.Ldw_begin+12661

	.data.b	53
	.data.w	.Ldw_begin+470

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+13484

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 69
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 525
	.data.b	23
	.data.w	.Ldw_begin+11555
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11629
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+11784

	.data.b	53
	.data.w	.Ldw_begin+13276

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2098
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+12750

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 260
	.data.b	115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 632
	.data.w	.Ldw_str_begin+260
	.data.b	6
	.data.b	1

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+12750

	.data.b	53
	.data.w	.Ldw_begin+672

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2134
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+14023

	.data.b	53
	.data.w	.Ldw_begin+729

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+734
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2361
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+734
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+11748

	.data.b	53
	.data.w	.Ldw_begin+787

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11772
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+792
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+11748

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11772
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+829
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11772
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+792
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+829
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+11760
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+11910
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+11975
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11784
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+12040
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+2281

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+917
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+11910
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11796
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+12085
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11808
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 272
	.data.b	102,108,111,97,116,0
	.section	.debug_info		;off: 1001
	.data.w	.Ldw_str_begin+272
	.data.b	4
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 278
	.data.b	105,110,116,0
	.section	.debug_info		;off: 1008
	.data.w	.Ldw_str_begin+278
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 282
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 1015
	.data.w	.Ldw_str_begin+282
	.data.b	7
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+2122

	.section	.debug_abbrev		;off: 76
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 1028
	.data.b	56
	.data.w	.Ldw_begin+1007
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

	.section	.debug_info		;off: 1036
	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+2122

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+2122

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+6070

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+2122

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+6015

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+2122

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	11

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+2122

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+7115

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	7

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+10195

	.data.b	49
	.data.w	.Ldw_begin+10236

	.data.b	49
	.data.w	.Ldw_begin+10277

	.data.b	49
	.data.w	.Ldw_begin+10358

	.data.b	49
	.data.w	.Ldw_begin+10639

	.data.b	53
	.data.w	.Ldw_begin+2122

	.data.b	53
	.data.w	.Ldw_begin+11567

	.data.b	47
	.data.w	.Ldw_begin+11555

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1205

	.data.b	47
	.data.w	.Ldw_begin+11832

	.data.b	53
	.data.w	.Ldw_begin+1213

	.data.b	53
	.data.w	.Ldw_begin+2146

	.data.b	47
	.data.w	.Ldw_begin+11844

	.data.b	53
	.data.w	.Ldw_begin+1228

	.data.b	53
	.data.w	.Ldw_begin+12292

	.data.b	53
	.data.w	.Ldw_begin+11760

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1248

	.data.b	53
	.data.w	.Ldw_begin+12822

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+11784

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+11784

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+12220

	.data.b	53
	.data.w	.Ldw_begin+12085

	.data.b	53
	.data.w	.Ldw_begin+2134

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+192

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+11796

	.data.b	47
	.data.w	.Ldw_begin+11808

	.data.b	53
	.data.w	.Ldw_begin+1324

	.data.b	47
	.data.w	.Ldw_begin+11820

	.data.b	53
	.data.w	.Ldw_begin+1339

	.data.b	53
	.data.w	.Ldw_begin+1329

	.data.b	53
	.data.w	.Ldw_begin+125

	.data.b	47
	.data.w	.Ldw_begin+2122

	.data.b	53
	.data.w	.Ldw_begin+1359

	.data.b	47
	.data.w	.Ldw_begin+2134

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+12750

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	28
	.data.w	.Ldw_begin+13276

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+13484

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+13607

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+12750

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	28
	.data.w	.Ldw_begin+13276

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	40
	.data.w	.Ldw_begin+13484

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1422

	.data.b	47
	.data.w	.Ldw_begin+1475

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+1480

	.data.b	56
	.data.w	.Ldw_begin+1007
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2170
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2465
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2465
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+9936

	.data.b	53
	.data.w	.Ldw_begin+1530

	.data.b	47
	.data.w	.Ldw_begin+1535

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1540
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+10076

	.data.b	53
	.data.w	.Ldw_begin+1564

	.data.b	47
	.data.w	.Ldw_begin+1569

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1574
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+10182

	.data.b	53
	.data.w	.Ldw_begin+1598

	.data.b	47
	.data.w	.Ldw_begin+1603

	.data.b	74
	.data.w	.Ldw_begin+2146
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+9546
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1608
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2098
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1190

	.data.b	74
	.data.w	.Ldw_begin+2122
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+115
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1653
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+7823
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1364

	.data.b	47
	.data.w	.Ldw_begin+7823

	.data.b	74
	.data.w	.Ldw_begin+2122
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1683
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1688
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2098
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2146
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+115
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2541
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2134
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2098
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2098
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11555
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2146
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11555
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+1195

	.data.b	47
	.data.w	.Ldw_begin+11579

	.data.b	53
	.data.w	.Ldw_begin+1880

	.data.b	47
	.data.w	.Ldw_begin+1885

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11555
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1875
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1890
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+11567

	.data.b	53
	.data.w	.Ldw_begin+1920

	.data.b	47
	.data.w	.Ldw_begin+1925

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+11555
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+1930
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

	.data.b	23
	.data.w	.Ldw_begin+14036
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+14048
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+14048
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+14036
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2134
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+2182
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+2134
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+2122
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 295
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 2099
	.data.w	.Ldw_str_begin+295
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

	.section	.debug_info		;off: 2110
	.data.b	45
	.section	.debug_str		;off: 303
	.data.b	115,105,110,116,56,0
	.section	.debug_info		;off: 2111
	.data.w	.Ldw_str_begin+303
	.data.b	54
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+631

	.data.b	45
	.section	.debug_str		;off: 309
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 2123
	.data.w	.Ldw_str_begin+309
	.data.b	56
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 315
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 2135
	.data.w	.Ldw_str_begin+315
	.data.b	60
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+197

	.data.b	45
	.section	.debug_str		;off: 322
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 2147
	.data.w	.Ldw_str_begin+322
	.data.b	64
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 329
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 2159
	.data.w	.Ldw_str_begin+329
	.data.b	68
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 336
	.data.b	102,108,111,97,116,51,50,0
	.section	.debug_info		;off: 2171
	.data.w	.Ldw_str_begin+336
	.data.b	83
	.data.b	29
	.data.b	14
	.data.w	.Ldw_begin+1000

	.data.b	45
	.section	.debug_str		;off: 344
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 2183
	.data.w	.Ldw_str_begin+344
	.data.b	39
	.data.b	15
	.data.b	9
	.data.w	.Ldw_begin+2122

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

	.section	.debug_info		;off: 2200
	.data.b	40
	.section	.debug_str		;off: 359
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 2201
	.data.w	.Ldw_str_begin+359
	.data.b	63
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2134
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

	.section	.debug_info		;off: 2216
	.data.b	40
	.section	.debug_str		;off: 368
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 2217
	.data.w	.Ldw_str_begin+368
	.data.b	64
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2134
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 377
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2233
	.data.w	.Ldw_str_begin+377
	.data.b	65
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2122
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 394
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2249
	.data.w	.Ldw_str_begin+394
	.data.b	66
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2122
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 411
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 2265
	.data.w	.Ldw_str_begin+411
	.data.b	67
	.data.b	13
	.data.b	9
	.data.w	.Ldw_begin+2122
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 428
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 2282
	.data.w	.Ldw_str_begin+428
	.data.b	68
	.data.b	2
	.data.b	9
	.data.w	.Ldw_begin+2194

	.data.b	52
	.section	.debug_str		;off: 448
	.data.b	0
	.section	.debug_info		;off: 2294
	.data.w	.Ldw_str_begin+448
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

	.section	.debug_info		;off: 2303
	.data.b	51
	.section	.debug_str		;off: 449
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 2304
	.data.w	.Ldw_str_begin+449
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

	.section	.debug_info		;off: 2312
	.data.b	51
	.section	.debug_str		;off: 466
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 2313
	.data.w	.Ldw_str_begin+466
	.data.b	38
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 483
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 2322
	.data.w	.Ldw_str_begin+483
	.data.b	39
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 500
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 2331
	.data.w	.Ldw_str_begin+500
	.data.b	40
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 517
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 2340
	.data.w	.Ldw_str_begin+517
	.data.b	41
	.data.b	5
	.data.b	15
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 534
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 2350
	.data.w	.Ldw_str_begin+534
	.data.b	42
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+2293

	.data.b	45
	.section	.debug_str		;off: 546
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 2362
	.data.w	.Ldw_str_begin+546
	.data.b	32
	.data.b	21
	.data.b	8
	.data.w	.Ldw_begin+2349

	.data.b	52
	.section	.debug_str		;off: 560
	.data.b	0
	.section	.debug_info		;off: 2374
	.data.w	.Ldw_str_begin+560
	.data.b	39
	.data.b	1
	.data.b	8
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 561
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,78,84,67,0
	.section	.debug_info		;off: 2384
	.data.w	.Ldw_str_begin+561
	.data.b	41
	.data.b	5
	.data.b	8
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 579
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,71,80,84,0
	.section	.debug_info		;off: 2393
	.data.w	.Ldw_str_begin+579
	.data.b	43
	.data.b	5
	.data.b	8
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 596
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,79,82,84,0
	.section	.debug_info		;off: 2402
	.data.w	.Ldw_str_begin+596
	.data.b	45
	.data.b	5
	.data.b	8
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 614
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,73,67,85,0
	.section	.debug_info		;off: 2411
	.data.w	.Ldw_str_begin+614
	.data.b	47
	.data.b	5
	.data.b	8
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 631
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,82,67,67,0
	.section	.debug_info		;off: 2420
	.data.w	.Ldw_str_begin+631
	.data.b	49
	.data.b	5
	.data.b	8
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 648
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,80,87,77,0
	.section	.debug_info		;off: 2429
	.data.w	.Ldw_str_begin+648
	.data.b	51
	.data.b	5
	.data.b	8
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 665
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,77,67,85,0
	.section	.debug_info		;off: 2438
	.data.w	.Ldw_str_begin+665
	.data.b	53
	.data.b	5
	.data.b	8
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 682
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,79,67,85,0
	.section	.debug_info		;off: 2447
	.data.w	.Ldw_str_begin+682
	.data.b	55
	.data.b	5
	.data.b	8
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 699
	.data.b	77,67,65,76,95,76,79,67,75,95,73,68,95,78,85,77,0
	.section	.debug_info		;off: 2456
	.data.w	.Ldw_str_begin+699
	.data.b	57
	.data.b	5
	.data.b	8
	.data.b	8

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 716
	.data.b	77,99,97,108,95,76,111,99,107,73,100,84,121,112,101,0
	.section	.debug_info		;off: 2466
	.data.w	.Ldw_str_begin+716
	.data.b	58
	.data.b	3
	.data.b	8
	.data.w	.Ldw_begin+2373

	.data.b	45
	.section	.debug_str		;off: 732
	.data.b	117,114,101,103,51,50,0
	.section	.debug_info		;off: 2478
	.data.w	.Ldw_str_begin+732
	.data.b	24
	.data.b	22
	.data.b	19
	.data.w	.Ldw_begin+1014

	.data.b	52
	.section	.debug_str		;off: 739
	.data.b	0
	.section	.debug_info		;off: 2490
	.data.w	.Ldw_str_begin+739
	.data.b	237,3
	.data.b	1
	.data.b	30
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 740
	.data.b	82,67,67,95,69,82,82,79,82,70,76,65,71,95,83,85,67,67,69,83,83,0
	.section	.debug_info		;off: 2501
	.data.w	.Ldw_str_begin+740
	.data.b	238,3
	.data.b	5
	.data.b	30
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 762
	.data.b	82,67,67,95,69,82,82,79,82,70,76,65,71,95,84,73,77,69,79,85,84,0
	.section	.debug_info		;off: 2511
	.data.w	.Ldw_str_begin+762
	.data.b	239,3
	.data.b	5
	.data.b	30
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 784
	.data.b	82,67,67,95,69,82,82,79,82,70,76,65,71,95,78,85,76,76,80,84,82,0
	.section	.debug_info		;off: 2521
	.data.w	.Ldw_str_begin+784
	.data.b	240,3
	.data.b	5
	.data.b	30
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 806
	.data.b	82,67,67,95,69,82,82,79,82,70,76,65,71,95,70,65,73,76,0
	.section	.debug_info		;off: 2531
	.data.w	.Ldw_str_begin+806
	.data.b	241,3
	.data.b	5
	.data.b	30
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 825
	.data.b	82,99,99,95,69,114,114,111,114,70,108,97,103,0
	.section	.debug_info		;off: 2542
	.data.w	.Ldw_str_begin+825
	.data.b	242,3
	.data.b	3
	.data.b	30
	.data.w	.Ldw_begin+2489

	.data.b	71
	.data.b	36
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 839
	.data.b	83,77,73,83,83,0
	.section	.debug_info		;off: 2561
	.data.w	.Ldw_str_begin+839
	.data.b	37
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	29
	.data.b	3
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

	.section	.debug_info		;off: 2579
	.data.b	41
	.section	.debug_str		;off: 845
	.data.b	114,101,115,101,114,118,101,100,95,51,0
	.section	.debug_info		;off: 2580
	.data.w	.Ldw_str_begin+845
	.data.b	38
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	29
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 856
	.data.b	69,83,80,73,95,83,73,83,87,95,66,105,116,115,0
	.section	.debug_info		;off: 2600
	.data.w	.Ldw_str_begin+856
	.data.b	39
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2554

	.data.b	71
	.data.b	43
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 871
	.data.b	77,68,82,86,0
	.section	.debug_info		;off: 2618
	.data.w	.Ldw_str_begin+871
	.data.b	44
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 876
	.data.b	77,68,84,80,0
	.section	.debug_info		;off: 2637
	.data.w	.Ldw_str_begin+876
	.data.b	45
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 881
	.data.b	77,68,78,66,0
	.section	.debug_info		;off: 2656
	.data.w	.Ldw_str_begin+881
	.data.b	46
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 886
	.data.b	69,83,80,73,95,77,68,73,68,95,66,105,116,115,0
	.section	.debug_info		;off: 2676
	.data.w	.Ldw_str_begin+886
	.data.b	47
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2611

	.data.b	71
	.data.b	51
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 901
	.data.b	71,84,81,0
	.section	.debug_info		;off: 2694
	.data.w	.Ldw_str_begin+901
	.data.b	52
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 905
	.data.b	83,70,82,66,69,77,0
	.section	.debug_info		;off: 2713
	.data.w	.Ldw_str_begin+905
	.data.b	53
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	23
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 912
	.data.b	83,84,83,73,0
	.section	.debug_info		;off: 2732
	.data.w	.Ldw_str_begin+912
	.data.b	54
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 917
	.data.b	84,79,86,0
	.section	.debug_info		;off: 2751
	.data.w	.Ldw_str_begin+917
	.data.b	55
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 921
	.data.b	79,76,66,67,0
	.section	.debug_info		;off: 2770
	.data.w	.Ldw_str_begin+921
	.data.b	56
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 926
	.data.b	68,76,77,83,0
	.section	.debug_info		;off: 2789
	.data.w	.Ldw_str_begin+926
	.data.b	57
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 931
	.data.b	83,84,66,68,76,0
	.section	.debug_info		;off: 2808
	.data.w	.Ldw_str_begin+931
	.data.b	58
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	11
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 937
	.data.b	84,80,82,70,0
	.section	.debug_info		;off: 2827
	.data.w	.Ldw_str_begin+937
	.data.b	59
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 942
	.data.b	83,79,68,80,0
	.section	.debug_info		;off: 2846
	.data.w	.Ldw_str_begin+942
	.data.b	60
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 947
	.data.b	72,68,84,82,77,0
	.section	.debug_info		;off: 2865
	.data.w	.Ldw_str_begin+947
	.data.b	61
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 953
	.data.b	69,78,0
	.section	.debug_info		;off: 2884
	.data.w	.Ldw_str_begin+953
	.data.b	62
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 956
	.data.b	77,83,0
	.section	.debug_info		;off: 2903
	.data.w	.Ldw_str_begin+956
	.data.b	63
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	5
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 959
	.data.b	83,65,84,82,69,78,0
	.section	.debug_info		;off: 2922
	.data.w	.Ldw_str_begin+959
	.data.b	64
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 966
	.data.b	72,68,77,69,78,0
	.section	.debug_info		;off: 2941
	.data.w	.Ldw_str_begin+966
	.data.b	65
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 972
	.data.b	67,76,75,77,85,88,0
	.section	.debug_info		;off: 2960
	.data.w	.Ldw_str_begin+972
	.data.b	66
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 979
	.data.b	83,82,83,84,66,0
	.section	.debug_info		;off: 2979
	.data.w	.Ldw_str_begin+979
	.data.b	67
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 985
	.data.b	69,83,80,73,95,71,78,82,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 2999
	.data.w	.Ldw_str_begin+985
	.data.b	68
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2687

	.data.b	71
	.data.b	72
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1002
	.data.b	69,82,82,73,69,78,83,0
	.section	.debug_info		;off: 3017
	.data.w	.Ldw_str_begin+1002
	.data.b	73
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	23
	.data.b	9
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1010
	.data.b	84,88,70,73,69,78,0
	.section	.debug_info		;off: 3036
	.data.w	.Ldw_str_begin+1010
	.data.b	74
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1017
	.data.b	82,88,70,73,69,78,0
	.section	.debug_info		;off: 3055
	.data.w	.Ldw_str_begin+1017
	.data.b	75
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1024
	.data.b	84,83,69,49,69,78,0
	.section	.debug_info		;off: 3074
	.data.w	.Ldw_str_begin+1024
	.data.b	76
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1031
	.data.b	84,83,69,50,69,78,0
	.section	.debug_info		;off: 3093
	.data.w	.Ldw_str_begin+1031
	.data.b	77
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1038
	.data.b	68,65,73,71,69,78,0
	.section	.debug_info		;off: 3112
	.data.w	.Ldw_str_begin+1038
	.data.b	78
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1045
	.data.b	83,69,70,69,78,0
	.section	.debug_info		;off: 3131
	.data.w	.Ldw_str_begin+1045
	.data.b	79
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1051
	.data.b	85,69,73,69,78,0
	.section	.debug_info		;off: 3150
	.data.w	.Ldw_str_begin+1051
	.data.b	80
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1057
	.data.b	76,84,69,73,69,78,0
	.section	.debug_info		;off: 3169
	.data.w	.Ldw_str_begin+1057
	.data.b	81
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1064
	.data.b	114,101,115,101,114,118,101,100,95,49,55,0
	.section	.debug_info		;off: 3188
	.data.w	.Ldw_str_begin+1064
	.data.b	82
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	12
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1076
	.data.b	84,83,69,49,0
	.section	.debug_info		;off: 3207
	.data.w	.Ldw_str_begin+1076
	.data.b	83
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	9
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1081
	.data.b	84,83,69,50,0
	.section	.debug_info		;off: 3226
	.data.w	.Ldw_str_begin+1081
	.data.b	84
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	6
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1086
	.data.b	84,88,70,77,0
	.section	.debug_info		;off: 3245
	.data.w	.Ldw_str_begin+1086
	.data.b	85
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1091
	.data.b	82,88,70,77,0
	.section	.debug_info		;off: 3264
	.data.w	.Ldw_str_begin+1091
	.data.b	86
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1096
	.data.b	84,88,68,82,69,78,0
	.section	.debug_info		;off: 3283
	.data.w	.Ldw_str_begin+1096
	.data.b	87
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1103
	.data.b	82,88,68,82,69,78,0
	.section	.debug_info		;off: 3302
	.data.w	.Ldw_str_begin+1103
	.data.b	88
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1110
	.data.b	69,83,80,73,95,71,78,82,67,79,78,49,95,66,105,116,115,0
	.section	.debug_info		;off: 3322
	.data.w	.Ldw_str_begin+1110
	.data.b	89
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3010

	.data.b	71
	.data.b	93
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1128
	.data.b	76,68,66,0
	.section	.debug_info		;off: 3340
	.data.w	.Ldw_str_begin+1128
	.data.b	94
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1132
	.data.b	73,80,83,67,0
	.section	.debug_info		;off: 3359
	.data.w	.Ldw_str_begin+1132
	.data.b	95
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	28
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1137
	.data.b	73,68,76,0
	.section	.debug_info		;off: 3378
	.data.w	.Ldw_str_begin+1137
	.data.b	96
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	25
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1141
	.data.b	76,80,83,67,0
	.section	.debug_info		;off: 3397
	.data.w	.Ldw_str_begin+1141
	.data.b	97
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1146
	.data.b	76,68,76,0
	.section	.debug_info		;off: 3416
	.data.w	.Ldw_str_begin+1146
	.data.b	98
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1150
	.data.b	84,80,83,67,0
	.section	.debug_info		;off: 3435
	.data.w	.Ldw_str_begin+1150
	.data.b	99
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1155
	.data.b	84,68,76,0
	.section	.debug_info		;off: 3454
	.data.w	.Ldw_str_begin+1155
	.data.b	100
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	13
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1159
	.data.b	80,65,82,84,89,80,0
	.section	.debug_info		;off: 3473
	.data.w	.Ldw_str_begin+1159
	.data.b	101
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1166
	.data.b	85,73,79,84,49,0
	.section	.debug_info		;off: 3492
	.data.w	.Ldw_str_begin+1166
	.data.b	102
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1172
	.data.b	77,83,66,0
	.section	.debug_info		;off: 3511
	.data.w	.Ldw_str_begin+1172
	.data.b	103
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1176
	.data.b	68,76,85,0
	.section	.debug_info		;off: 3530
	.data.w	.Ldw_str_begin+1176
	.data.b	104
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1180
	.data.b	68,76,0
	.section	.debug_info		;off: 3549
	.data.w	.Ldw_str_begin+1180
	.data.b	105
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1183
	.data.b	83,67,77,0
	.section	.debug_info		;off: 3568
	.data.w	.Ldw_str_begin+1183
	.data.b	106
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1187
	.data.b	69,83,80,73,95,69,77,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 3588
	.data.w	.Ldw_str_begin+1187
	.data.b	107
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3333

	.data.b	71
	.data.b	111
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1203
	.data.b	84,81,0
	.section	.debug_info		;off: 3606
	.data.w	.Ldw_str_begin+1203
	.data.b	112
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	26
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1206
	.data.b	67,83,65,0
	.section	.debug_info		;off: 3625
	.data.w	.Ldw_str_begin+1206
	.data.b	113
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1210
	.data.b	67,83,66,0
	.section	.debug_info		;off: 3644
	.data.w	.Ldw_str_begin+1210
	.data.b	114
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1214
	.data.b	67,83,67,0
	.section	.debug_info		;off: 3663
	.data.w	.Ldw_str_begin+1214
	.data.b	115
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1218
	.data.b	67,80,72,0
	.section	.debug_info		;off: 3682
	.data.w	.Ldw_str_begin+1218
	.data.b	116
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1222
	.data.b	67,80,79,76,0
	.section	.debug_info		;off: 3701
	.data.w	.Ldw_str_begin+1222
	.data.b	117
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1227
	.data.b	80,82,84,69,78,0
	.section	.debug_info		;off: 3720
	.data.w	.Ldw_str_begin+1227
	.data.b	118
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1233
	.data.b	114,101,115,101,114,118,101,100,95,49,53,0
	.section	.debug_info		;off: 3739
	.data.w	.Ldw_str_begin+1233
	.data.b	119
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1245
	.data.b	68,70,66,69,78,0
	.section	.debug_info		;off: 3758
	.data.w	.Ldw_str_begin+1245
	.data.b	120
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1251
	.data.b	69,83,80,73,95,68,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 3778
	.data.w	.Ldw_str_begin+1251
	.data.b	121
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3599

	.data.b	71
	.data.b	125
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1266
	.data.b	69,82,82,73,70,83,0
	.section	.debug_info		;off: 3796
	.data.w	.Ldw_str_begin+1266
	.data.b	126
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	23
	.data.b	9
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1273
	.data.b	84,88,70,0
	.section	.debug_info		;off: 3815
	.data.w	.Ldw_str_begin+1273
	.data.b	127
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1277
	.data.b	82,88,70,0
	.section	.debug_info		;off: 3834
	.data.w	.Ldw_str_begin+1277
	.data.b	128,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1281
	.data.b	84,83,69,49,70,0
	.section	.debug_info		;off: 3854
	.data.w	.Ldw_str_begin+1281
	.data.b	129,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1287
	.data.b	84,83,69,50,70,0
	.section	.debug_info		;off: 3874
	.data.w	.Ldw_str_begin+1287
	.data.b	130,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1293
	.data.b	68,65,73,71,0
	.section	.debug_info		;off: 3894
	.data.w	.Ldw_str_begin+1293
	.data.b	131,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1298
	.data.b	83,69,70,0
	.section	.debug_info		;off: 3914
	.data.w	.Ldw_str_begin+1298
	.data.b	132,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1302
	.data.b	85,83,82,70,0
	.section	.debug_info		;off: 3934
	.data.w	.Ldw_str_begin+1302
	.data.b	133,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1307
	.data.b	83,70,82,65,70,0
	.section	.debug_info		;off: 3954
	.data.w	.Ldw_str_begin+1307
	.data.b	134,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1313
	.data.b	83,84,79,65,70,0
	.section	.debug_info		;off: 3974
	.data.w	.Ldw_str_begin+1313
	.data.b	135,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1319
	.data.b	83,69,65,70,0
	.section	.debug_info		;off: 3994
	.data.w	.Ldw_str_begin+1319
	.data.b	136,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1324
	.data.b	76,84,69,70,0
	.section	.debug_info		;off: 4014
	.data.w	.Ldw_str_begin+1324
	.data.b	137,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1329
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 4034
	.data.w	.Ldw_str_begin+1329
	.data.b	138,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	10
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1341
	.data.b	67,83,70,0
	.section	.debug_info		;off: 4054
	.data.w	.Ldw_str_begin+1341
	.data.b	139,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	6
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1345
	.data.b	82,80,86,0
	.section	.debug_info		;off: 4074
	.data.w	.Ldw_str_begin+1345
	.data.b	140,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1349
	.data.b	84,80,86,0
	.section	.debug_info		;off: 4094
	.data.w	.Ldw_str_begin+1349
	.data.b	141,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1353
	.data.b	70,83,0
	.section	.debug_info		;off: 4114
	.data.w	.Ldw_str_begin+1353
	.data.b	142,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1356
	.data.b	69,83,80,73,95,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 4135
	.data.w	.Ldw_str_begin+1356
	.data.b	143,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3789

	.data.b	71
	.data.b	147,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1370
	.data.b	84,66,67,78,84,0
	.section	.debug_info		;off: 4155
	.data.w	.Ldw_str_begin+1370
	.data.b	148,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1376
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 4175
	.data.w	.Ldw_str_begin+1376
	.data.b	149,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	20
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1387
	.data.b	67,66,68,69,78,0
	.section	.debug_info		;off: 4195
	.data.w	.Ldw_str_begin+1387
	.data.b	150,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1393
	.data.b	67,66,68,70,0
	.section	.debug_info		;off: 4215
	.data.w	.Ldw_str_begin+1393
	.data.b	151,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1398
	.data.b	67,83,68,69,78,0
	.section	.debug_info		;off: 4235
	.data.w	.Ldw_str_begin+1398
	.data.b	152,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1404
	.data.b	67,83,69,70,0
	.section	.debug_info		;off: 4255
	.data.w	.Ldw_str_begin+1404
	.data.b	153,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1409
	.data.b	69,83,80,73,95,69,83,84,83,95,66,105,116,115,0
	.section	.debug_info		;off: 4276
	.data.w	.Ldw_str_begin+1409
	.data.b	154,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4147

	.data.b	71
	.data.b	158,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1424
	.data.b	79,65,80,0
	.section	.debug_info		;off: 4296
	.data.w	.Ldw_str_begin+1424
	.data.b	159,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1428
	.data.b	79,69,66,0
	.section	.debug_info		;off: 4316
	.data.w	.Ldw_str_begin+1428
	.data.b	160,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1432
	.data.b	69,83,80,73,95,83,83,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 4337
	.data.w	.Ldw_str_begin+1432
	.data.b	161,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4288

	.data.b	71
	.data.b	165,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1448
	.data.b	69,82,82,70,83,67,0
	.section	.debug_info		;off: 4357
	.data.w	.Ldw_str_begin+1448
	.data.b	166,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	23
	.data.b	9
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1455
	.data.b	84,88,67,0
	.section	.debug_info		;off: 4377
	.data.w	.Ldw_str_begin+1455
	.data.b	167,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1459
	.data.b	82,88,67,0
	.section	.debug_info		;off: 4397
	.data.w	.Ldw_str_begin+1459
	.data.b	168,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	21
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1463
	.data.b	84,83,69,49,70,67,0
	.section	.debug_info		;off: 4417
	.data.w	.Ldw_str_begin+1463
	.data.b	169,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1470
	.data.b	84,83,69,50,70,67,0
	.section	.debug_info		;off: 4437
	.data.w	.Ldw_str_begin+1470
	.data.b	170,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1477
	.data.b	68,65,73,71,67,0
	.section	.debug_info		;off: 4457
	.data.w	.Ldw_str_begin+1477
	.data.b	171,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1483
	.data.b	83,69,70,67,0
	.section	.debug_info		;off: 4477
	.data.w	.Ldw_str_begin+1483
	.data.b	172,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1488
	.data.b	85,83,82,67,0
	.section	.debug_info		;off: 4497
	.data.w	.Ldw_str_begin+1488
	.data.b	173,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1493
	.data.b	83,70,82,65,67,0
	.section	.debug_info		;off: 4517
	.data.w	.Ldw_str_begin+1493
	.data.b	174,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1499
	.data.b	83,84,79,65,67,0
	.section	.debug_info		;off: 4537
	.data.w	.Ldw_str_begin+1499
	.data.b	175,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1505
	.data.b	83,69,65,67,0
	.section	.debug_info		;off: 4557
	.data.w	.Ldw_str_begin+1505
	.data.b	176,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1510
	.data.b	76,84,69,70,67,0
	.section	.debug_info		;off: 4577
	.data.w	.Ldw_str_begin+1510
	.data.b	177,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1516
	.data.b	114,101,115,101,114,118,101,100,95,50,48,0
	.section	.debug_info		;off: 4597
	.data.w	.Ldw_str_begin+1516
	.data.b	178,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1528
	.data.b	69,83,80,73,95,83,84,83,67,95,66,105,116,115,0
	.section	.debug_info		;off: 4618
	.data.w	.Ldw_str_begin+1528
	.data.b	179,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4349

	.data.b	71
	.data.b	183,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1543
	.data.b	68,76,84,0
	.section	.debug_info		;off: 4638
	.data.w	.Ldw_str_begin+1543
	.data.b	184,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1547
	.data.b	68,67,78,84,0
	.section	.debug_info		;off: 4658
	.data.w	.Ldw_str_begin+1547
	.data.b	185,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	16
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1552
	.data.b	69,83,80,73,95,76,84,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 4679
	.data.w	.Ldw_str_begin+1552
	.data.b	186,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4630

	.data.b	71
	.data.b	190,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1568
	.data.b	72,66,69,0
	.section	.debug_info		;off: 4699
	.data.w	.Ldw_str_begin+1568
	.data.b	191,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1572
	.data.b	69,83,80,73,95,72,66,82,69,78,84,82,89,95,66,105,116,115,0
	.section	.debug_info		;off: 4720
	.data.w	.Ldw_str_begin+1572
	.data.b	192,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4691

	.data.b	71
	.data.b	196,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1591
	.data.b	69,83,69,0
	.section	.debug_info		;off: 4740
	.data.w	.Ldw_str_begin+1591
	.data.b	197,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1595
	.data.b	69,83,80,73,95,69,77,67,79,78,69,78,84,82,89,95,66,105,116,115,0
	.section	.debug_info		;off: 4761
	.data.w	.Ldw_str_begin+1595
	.data.b	198,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4732

	.data.b	71
	.data.b	202,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1616
	.data.b	68,83,69,0
	.section	.debug_info		;off: 4781
	.data.w	.Ldw_str_begin+1616
	.data.b	203,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1620
	.data.b	69,83,80,73,95,68,65,84,65,69,78,84,82,89,95,66,105,116,115,0
	.section	.debug_info		;off: 4802
	.data.w	.Ldw_str_begin+1620
	.data.b	204,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4773

	.data.b	71
	.data.b	208,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1640
	.data.b	82,83,69,0
	.section	.debug_info		;off: 4822
	.data.w	.Ldw_str_begin+1640
	.data.b	209,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1644
	.data.b	69,83,80,73,95,82,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 4843
	.data.w	.Ldw_str_begin+1644
	.data.b	210,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4814

	.data.b	71
	.data.b	214,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1658
	.data.b	84,79,77,83,0
	.section	.debug_info		;off: 4863
	.data.w	.Ldw_str_begin+1658
	.data.b	215,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	13
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1663
	.data.b	114,101,115,101,114,118,101,100,95,49,51,0
	.section	.debug_info		;off: 4883
	.data.w	.Ldw_str_begin+1663
	.data.b	216,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1675
	.data.b	82,77,78,0
	.section	.debug_info		;off: 4903
	.data.w	.Ldw_str_begin+1675
	.data.b	217,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	3
	.data.b	13
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1679
	.data.b	114,101,115,101,114,118,101,100,95,50,57,0
	.section	.debug_info		;off: 4923
	.data.w	.Ldw_str_begin+1679
	.data.b	218,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1691
	.data.b	69,83,80,73,95,77,67,95,66,105,116,115,0
	.section	.debug_info		;off: 4944
	.data.w	.Ldw_str_begin+1691
	.data.b	219,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4855

	.data.b	71
	.data.b	223,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1704
	.data.b	69,84,80,83,67,0
	.section	.debug_info		;off: 4964
	.data.w	.Ldw_str_begin+1704
	.data.b	224,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	29
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1710
	.data.b	69,84,68,76,0
	.section	.debug_info		;off: 4984
	.data.w	.Ldw_str_begin+1710
	.data.b	225,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	26
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1715
	.data.b	114,101,115,101,114,118,101,100,95,54,0
	.section	.debug_info		;off: 5004
	.data.w	.Ldw_str_begin+1715
	.data.b	226,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	16
	.data.b	10
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1726
	.data.b	66,70,73,69,78,0
	.section	.debug_info		;off: 5024
	.data.w	.Ldw_str_begin+1726
	.data.b	227,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	15
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1732
	.data.b	66,70,73,70,0
	.section	.debug_info		;off: 5044
	.data.w	.Ldw_str_begin+1732
	.data.b	228,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	14
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1737
	.data.b	66,70,73,67,0
	.section	.debug_info		;off: 5064
	.data.w	.Ldw_str_begin+1737
	.data.b	229,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	13
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1742
	.data.b	66,70,73,83,0
	.section	.debug_info		;off: 5084
	.data.w	.Ldw_str_begin+1742
	.data.b	230,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	12
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1747
	.data.b	65,70,73,69,78,0
	.section	.debug_info		;off: 5104
	.data.w	.Ldw_str_begin+1747
	.data.b	231,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	11
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1753
	.data.b	65,70,73,70,0
	.section	.debug_info		;off: 5124
	.data.w	.Ldw_str_begin+1753
	.data.b	232,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	10
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1758
	.data.b	65,70,73,67,0
	.section	.debug_info		;off: 5144
	.data.w	.Ldw_str_begin+1758
	.data.b	233,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	9
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1763
	.data.b	65,70,73,83,0
	.section	.debug_info		;off: 5164
	.data.w	.Ldw_str_begin+1763
	.data.b	234,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	8
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1768
	.data.b	114,101,115,101,114,118,101,100,95,50,52,0
	.section	.debug_info		;off: 5184
	.data.w	.Ldw_str_begin+1768
	.data.b	235,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1780
	.data.b	69,84,69,78,0
	.section	.debug_info		;off: 5204
	.data.w	.Ldw_str_begin+1780
	.data.b	236,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1785
	.data.b	77,67,69,78,0
	.section	.debug_info		;off: 5224
	.data.w	.Ldw_str_begin+1785
	.data.b	237,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1790
	.data.b	69,83,80,73,95,77,67,67,79,78,95,66,105,116,115,0
	.section	.debug_info		;off: 5245
	.data.w	.Ldw_str_begin+1790
	.data.b	238,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+4956

	.data.b	71
	.data.b	242,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1806
	.data.b	68,69,76,65,89,84,73,77,69,0
	.section	.debug_info		;off: 5265
	.data.w	.Ldw_str_begin+1806
	.data.b	243,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	26
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1816
	.data.b	114,101,115,101,114,118,101,100,95,49,57,0
	.section	.debug_info		;off: 5285
	.data.w	.Ldw_str_begin+1816
	.data.b	244,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	26
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1828
	.data.b	69,83,80,73,95,68,69,76,65,89,95,66,105,116,115,0
	.section	.debug_info		;off: 5306
	.data.w	.Ldw_str_begin+1828
	.data.b	245,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5257

	.data.b	71
	.data.b	249,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1844
	.data.b	83,76,65,86,69,68,65,84,65,67,78,84,0
	.section	.debug_info		;off: 5326
	.data.w	.Ldw_str_begin+1844
	.data.b	250,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	15
	.data.b	17
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1857
	.data.b	68,65,84,65,83,69,76,0
	.section	.debug_info		;off: 5346
	.data.w	.Ldw_str_begin+1857
	.data.b	251,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	13
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1865
	.data.b	114,101,115,101,114,118,101,100,95,49,57,0
	.section	.debug_info		;off: 5366
	.data.w	.Ldw_str_begin+1865
	.data.b	252,1
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	13
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1877
	.data.b	69,83,80,73,95,68,65,84,65,77,79,68,69,95,66,105,116,115,0
	.section	.debug_info		;off: 5387
	.data.w	.Ldw_str_begin+1877
	.data.b	253,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5318

	.data.b	71
	.data.b	129,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1896
	.data.b	82,83,69,0
	.section	.debug_info		;off: 5407
	.data.w	.Ldw_str_begin+1896
	.data.b	130,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1900
	.data.b	69,83,80,73,95,82,68,82,68,95,66,105,116,115,0
	.section	.debug_info		;off: 5428
	.data.w	.Ldw_str_begin+1900
	.data.b	131,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5399

	.data.b	71
	.data.b	135,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1915
	.data.b	84,88,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 5448
	.data.w	.Ldw_str_begin+1915
	.data.b	136,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	28
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1927
	.data.b	82,88,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 5468
	.data.w	.Ldw_str_begin+1927
	.data.b	137,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	4
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1939
	.data.b	83,84,79,82,84,0
	.section	.debug_info		;off: 5488
	.data.w	.Ldw_str_begin+1939
	.data.b	138,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	6
	.data.b	18
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1945
	.data.b	83,84,79,69,78,0
	.section	.debug_info		;off: 5508
	.data.w	.Ldw_str_begin+1945
	.data.b	139,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1951
	.data.b	114,101,115,101,114,118,101,100,95,50,55,0
	.section	.debug_info		;off: 5528
	.data.w	.Ldw_str_begin+1951
	.data.b	140,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1963
	.data.b	69,83,80,73,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,66,105,116,115,0
	.section	.debug_info		;off: 5549
	.data.w	.Ldw_str_begin+1963
	.data.b	141,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5440

	.data.b	71
	.data.b	145,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1987
	.data.b	84,88,76,69,86,69,76,0
	.section	.debug_info		;off: 5569
	.data.w	.Ldw_str_begin+1987
	.data.b	146,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	27
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 1995
	.data.b	114,101,115,101,114,118,101,100,95,53,0
	.section	.debug_info		;off: 5589
	.data.w	.Ldw_str_begin+1995
	.data.b	147,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2006
	.data.b	82,88,76,69,86,69,76,0
	.section	.debug_info		;off: 5609
	.data.w	.Ldw_str_begin+2006
	.data.b	148,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	5
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2014
	.data.b	114,101,115,101,114,118,101,100,95,49,51,0
	.section	.debug_info		;off: 5629
	.data.w	.Ldw_str_begin+2014
	.data.b	149,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	19
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2026
	.data.b	69,83,80,73,95,70,73,70,79,76,69,86,69,76,95,66,105,116,115,0
	.section	.debug_info		;off: 5650
	.data.w	.Ldw_str_begin+2026
	.data.b	150,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5561

	.data.b	71
	.data.b	154,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2046
	.data.b	84,81,0
	.section	.debug_info		;off: 5670
	.data.w	.Ldw_str_begin+2046
	.data.b	155,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	26
	.data.b	6
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2049
	.data.b	67,83,65,0
	.section	.debug_info		;off: 5690
	.data.w	.Ldw_str_begin+2049
	.data.b	156,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2053
	.data.b	67,83,66,0
	.section	.debug_info		;off: 5710
	.data.w	.Ldw_str_begin+2053
	.data.b	157,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	22
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2057
	.data.b	67,83,67,0
	.section	.debug_info		;off: 5730
	.data.w	.Ldw_str_begin+2057
	.data.b	158,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2061
	.data.b	67,80,72,0
	.section	.debug_info		;off: 5750
	.data.w	.Ldw_str_begin+2061
	.data.b	159,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	19
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2065
	.data.b	67,80,79,76,0
	.section	.debug_info		;off: 5770
	.data.w	.Ldw_str_begin+2065
	.data.b	160,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	18
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2070
	.data.b	80,82,84,69,78,0
	.section	.debug_info		;off: 5790
	.data.w	.Ldw_str_begin+2070
	.data.b	161,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2076
	.data.b	114,101,115,101,114,118,101,100,95,49,53,0
	.section	.debug_info		;off: 5810
	.data.w	.Ldw_str_begin+2076
	.data.b	162,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	15
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 2088
	.data.b	68,70,66,69,78,0
	.section	.debug_info		;off: 5830
	.data.w	.Ldw_str_begin+2088
	.data.b	163,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	2
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2094
	.data.b	69,83,80,73,95,68,67,79,78,69,71,95,66,105,116,115,0
	.section	.debug_info		;off: 5851
	.data.w	.Ldw_str_begin+2094
	.data.b	164,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5662

	.data.b	73
	.data.b	171,2
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

	.section	.debug_info		;off: 5870
	.data.b	40
	.section	.debug_str		;off: 2111
	.data.b	85,0
	.section	.debug_info		;off: 5871
	.data.w	.Ldw_str_begin+2111
	.data.b	172,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2113
	.data.b	66,0
	.section	.debug_info		;off: 5888
	.data.w	.Ldw_str_begin+2113
	.data.b	173,2
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+3587
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2115
	.data.b	69,83,80,73,95,69,77,67,79,78,0
	.section	.debug_info		;off: 5906
	.data.w	.Ldw_str_begin+2115
	.data.b	174,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5863

	.data.b	73
	.data.b	179,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2126
	.data.b	85,0
	.section	.debug_info		;off: 5926
	.data.w	.Ldw_str_begin+2126
	.data.b	180,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2128
	.data.b	66,0
	.section	.debug_info		;off: 5943
	.data.w	.Ldw_str_begin+2128
	.data.b	181,2
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+4760
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2130
	.data.b	69,83,80,73,95,69,77,67,79,78,69,78,84,82,89,0
	.section	.debug_info		;off: 5961
	.data.w	.Ldw_str_begin+2130
	.data.b	182,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5918

	.data.b	73
	.data.b	187,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2146
	.data.b	85,0
	.section	.debug_info		;off: 5981
	.data.w	.Ldw_str_begin+2146
	.data.b	188,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2148
	.data.b	66,0
	.section	.debug_info		;off: 5998
	.data.w	.Ldw_str_begin+2148
	.data.b	189,2
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+4801
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2150
	.data.b	69,83,80,73,95,68,65,84,65,69,78,84,82,89,0
	.section	.debug_info		;off: 6016
	.data.w	.Ldw_str_begin+2150
	.data.b	190,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+5973

	.data.b	73
	.data.b	195,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2165
	.data.b	85,0
	.section	.debug_info		;off: 6036
	.data.w	.Ldw_str_begin+2165
	.data.b	196,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2167
	.data.b	66,0
	.section	.debug_info		;off: 6053
	.data.w	.Ldw_str_begin+2167
	.data.b	197,2
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+3777
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2169
	.data.b	69,83,80,73,95,68,67,79,78,0
	.section	.debug_info		;off: 6071
	.data.w	.Ldw_str_begin+2169
	.data.b	198,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6028

	.data.b	73
	.data.b	203,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2179
	.data.b	85,0
	.section	.debug_info		;off: 6091
	.data.w	.Ldw_str_begin+2179
	.data.b	204,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2181
	.data.b	66,0
	.section	.debug_info		;off: 6108
	.data.w	.Ldw_str_begin+2181
	.data.b	205,2
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+4617
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2183
	.data.b	69,83,80,73,95,83,84,83,67,0
	.section	.debug_info		;off: 6126
	.data.w	.Ldw_str_begin+2183
	.data.b	206,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6083

	.data.b	73
	.data.b	211,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2193
	.data.b	85,0
	.section	.debug_info		;off: 6146
	.data.w	.Ldw_str_begin+2193
	.data.b	212,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2195
	.data.b	66,0
	.section	.debug_info		;off: 6163
	.data.w	.Ldw_str_begin+2195
	.data.b	213,2
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+2998
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2197
	.data.b	69,83,80,73,95,71,78,82,67,79,78,0
	.section	.debug_info		;off: 6181
	.data.w	.Ldw_str_begin+2197
	.data.b	214,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6138

	.data.b	73
	.data.b	219,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2209
	.data.b	85,0
	.section	.debug_info		;off: 6201
	.data.w	.Ldw_str_begin+2209
	.data.b	220,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2211
	.data.b	66,0
	.section	.debug_info		;off: 6218
	.data.w	.Ldw_str_begin+2211
	.data.b	221,2
	.data.b	23
	.data.b	36
	.data.w	.Ldw_begin+3321
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2213
	.data.b	69,83,80,73,95,71,78,82,67,79,78,49,0
	.section	.debug_info		;off: 6236
	.data.w	.Ldw_str_begin+2213
	.data.b	222,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6193

	.data.b	73
	.data.b	227,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2226
	.data.b	85,0
	.section	.debug_info		;off: 6256
	.data.w	.Ldw_str_begin+2226
	.data.b	228,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2228
	.data.b	66,0
	.section	.debug_info		;off: 6273
	.data.w	.Ldw_str_begin+2228
	.data.b	229,2
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+2675
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2230
	.data.b	69,83,80,73,95,77,68,73,68,0
	.section	.debug_info		;off: 6291
	.data.w	.Ldw_str_begin+2230
	.data.b	230,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6248

	.data.b	73
	.data.b	235,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2240
	.data.b	85,0
	.section	.debug_info		;off: 6311
	.data.w	.Ldw_str_begin+2240
	.data.b	236,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2242
	.data.b	66,0
	.section	.debug_info		;off: 6328
	.data.w	.Ldw_str_begin+2242
	.data.b	237,2
	.data.b	18
	.data.b	36
	.data.w	.Ldw_begin+4943
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2244
	.data.b	69,83,80,73,95,77,67,0
	.section	.debug_info		;off: 6346
	.data.w	.Ldw_str_begin+2244
	.data.b	238,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6303

	.data.b	73
	.data.b	243,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2252
	.data.b	85,0
	.section	.debug_info		;off: 6366
	.data.w	.Ldw_str_begin+2252
	.data.b	244,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2254
	.data.b	66,0
	.section	.debug_info		;off: 6383
	.data.w	.Ldw_str_begin+2254
	.data.b	245,2
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+5244
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2256
	.data.b	69,83,80,73,95,77,67,67,79,78,0
	.section	.debug_info		;off: 6401
	.data.w	.Ldw_str_begin+2256
	.data.b	246,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6358

	.data.b	73
	.data.b	251,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2267
	.data.b	85,0
	.section	.debug_info		;off: 6421
	.data.w	.Ldw_str_begin+2267
	.data.b	252,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2269
	.data.b	66,0
	.section	.debug_info		;off: 6438
	.data.w	.Ldw_str_begin+2269
	.data.b	253,2
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+4719
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2271
	.data.b	69,83,80,73,95,72,66,82,69,78,84,82,89,0
	.section	.debug_info		;off: 6456
	.data.w	.Ldw_str_begin+2271
	.data.b	254,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6413

	.data.b	73
	.data.b	131,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2285
	.data.b	85,0
	.section	.debug_info		;off: 6476
	.data.w	.Ldw_str_begin+2285
	.data.b	132,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2287
	.data.b	66,0
	.section	.debug_info		;off: 6493
	.data.w	.Ldw_str_begin+2287
	.data.b	133,3
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+2599
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2289
	.data.b	69,83,80,73,95,83,73,83,87,0
	.section	.debug_info		;off: 6511
	.data.w	.Ldw_str_begin+2289
	.data.b	134,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6468

	.data.b	73
	.data.b	139,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2299
	.data.b	85,0
	.section	.debug_info		;off: 6531
	.data.w	.Ldw_str_begin+2299
	.data.b	140,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2301
	.data.b	66,0
	.section	.debug_info		;off: 6548
	.data.w	.Ldw_str_begin+2301
	.data.b	141,3
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+4842
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2303
	.data.b	69,83,80,73,95,82,68,82,0
	.section	.debug_info		;off: 6566
	.data.w	.Ldw_str_begin+2303
	.data.b	142,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6523

	.data.b	73
	.data.b	147,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2312
	.data.b	85,0
	.section	.debug_info		;off: 6586
	.data.w	.Ldw_str_begin+2312
	.data.b	148,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2314
	.data.b	66,0
	.section	.debug_info		;off: 6603
	.data.w	.Ldw_str_begin+2314
	.data.b	149,3
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+5427
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2316
	.data.b	69,83,80,73,95,82,68,82,68,0
	.section	.debug_info		;off: 6621
	.data.w	.Ldw_str_begin+2316
	.data.b	150,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6578

	.data.b	73
	.data.b	155,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2326
	.data.b	85,0
	.section	.debug_info		;off: 6641
	.data.w	.Ldw_str_begin+2326
	.data.b	156,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2328
	.data.b	66,0
	.section	.debug_info		;off: 6658
	.data.w	.Ldw_str_begin+2328
	.data.b	157,3
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+4336
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2330
	.data.b	69,83,80,73,95,83,83,67,79,78,0
	.section	.debug_info		;off: 6676
	.data.w	.Ldw_str_begin+2330
	.data.b	158,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6633

	.data.b	73
	.data.b	163,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2341
	.data.b	85,0
	.section	.debug_info		;off: 6696
	.data.w	.Ldw_str_begin+2341
	.data.b	164,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2343
	.data.b	66,0
	.section	.debug_info		;off: 6713
	.data.w	.Ldw_str_begin+2343
	.data.b	165,3
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+4134
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2345
	.data.b	69,83,80,73,95,83,84,83,0
	.section	.debug_info		;off: 6731
	.data.w	.Ldw_str_begin+2345
	.data.b	166,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6688

	.data.b	73
	.data.b	171,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2354
	.data.b	85,0
	.section	.debug_info		;off: 6751
	.data.w	.Ldw_str_begin+2354
	.data.b	172,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2356
	.data.b	66,0
	.section	.debug_info		;off: 6768
	.data.w	.Ldw_str_begin+2356
	.data.b	173,3
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+4275
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2358
	.data.b	69,83,80,73,95,69,83,84,83,0
	.section	.debug_info		;off: 6786
	.data.w	.Ldw_str_begin+2358
	.data.b	174,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6743

	.data.b	73
	.data.b	179,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2368
	.data.b	85,0
	.section	.debug_info		;off: 6806
	.data.w	.Ldw_str_begin+2368
	.data.b	180,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2370
	.data.b	66,0
	.section	.debug_info		;off: 6823
	.data.w	.Ldw_str_begin+2370
	.data.b	181,3
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+4678
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2372
	.data.b	69,83,80,73,95,76,84,67,79,78,0
	.section	.debug_info		;off: 6841
	.data.w	.Ldw_str_begin+2372
	.data.b	182,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6798

	.data.b	73
	.data.b	186,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2383
	.data.b	85,0
	.section	.debug_info		;off: 6861
	.data.w	.Ldw_str_begin+2383
	.data.b	187,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2385
	.data.b	66,0
	.section	.debug_info		;off: 6878
	.data.w	.Ldw_str_begin+2385
	.data.b	188,3
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+5305
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2387
	.data.b	69,83,80,73,95,68,69,76,65,89,0
	.section	.debug_info		;off: 6896
	.data.w	.Ldw_str_begin+2387
	.data.b	189,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6853

	.data.b	73
	.data.b	193,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2398
	.data.b	85,0
	.section	.debug_info		;off: 6916
	.data.w	.Ldw_str_begin+2398
	.data.b	194,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2400
	.data.b	66,0
	.section	.debug_info		;off: 6933
	.data.w	.Ldw_str_begin+2400
	.data.b	195,3
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+5386
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2402
	.data.b	69,83,80,73,95,68,65,84,65,77,79,68,69,0
	.section	.debug_info		;off: 6951
	.data.w	.Ldw_str_begin+2402
	.data.b	196,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6908

	.data.b	73
	.data.b	200,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2416
	.data.b	85,0
	.section	.debug_info		;off: 6971
	.data.w	.Ldw_str_begin+2416
	.data.b	201,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2418
	.data.b	66,0
	.section	.debug_info		;off: 6988
	.data.w	.Ldw_str_begin+2418
	.data.b	202,3
	.data.b	29
	.data.b	36
	.data.w	.Ldw_begin+5548
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2420
	.data.b	69,83,80,73,95,70,73,70,79,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 7006
	.data.w	.Ldw_str_begin+2420
	.data.b	203,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+6963

	.data.b	73
	.data.b	207,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2439
	.data.b	85,0
	.section	.debug_info		;off: 7026
	.data.w	.Ldw_str_begin+2439
	.data.b	208,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2441
	.data.b	66,0
	.section	.debug_info		;off: 7043
	.data.w	.Ldw_str_begin+2441
	.data.b	209,3
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+5649
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2443
	.data.b	69,83,80,73,95,70,73,70,79,76,69,86,69,76,0
	.section	.debug_info		;off: 7061
	.data.w	.Ldw_str_begin+2443
	.data.b	210,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+7018

	.data.b	73
	.data.b	214,3
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2458
	.data.b	85,0
	.section	.debug_info		;off: 7081
	.data.w	.Ldw_str_begin+2458
	.data.b	215,3
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2460
	.data.b	66,0
	.section	.debug_info		;off: 7098
	.data.w	.Ldw_str_begin+2460
	.data.b	216,3
	.data.b	22
	.data.b	36
	.data.w	.Ldw_begin+5850
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2462
	.data.b	69,83,80,73,95,68,67,79,78,69,71,0
	.section	.debug_info		;off: 7116
	.data.w	.Ldw_str_begin+2462
	.data.b	217,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+7073

	.data.b	71
	.data.b	222,3
	.data.b	1
	.data.b	36
	.data.b	224,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2474
	.data.b	82,69,83,69,82,86,69,68,95,48,0
	.section	.debug_info		;off: 7137
	.data.w	.Ldw_str_begin+2474
	.data.b	223,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1021
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2485
	.data.b	83,73,83,87,0
	.section	.debug_info		;off: 7154
	.data.w	.Ldw_str_begin+2485
	.data.b	224,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+6510
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2490
	.data.b	77,68,73,68,0
	.section	.debug_info		;off: 7171
	.data.w	.Ldw_str_begin+2490
	.data.b	225,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+6290
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2495
	.data.b	82,69,83,69,82,86,69,68,95,67,0
	.section	.debug_info		;off: 7188
	.data.w	.Ldw_str_begin+2495
	.data.b	226,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1037
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2506
	.data.b	71,78,82,67,79,78,0
	.section	.debug_info		;off: 7205
	.data.w	.Ldw_str_begin+2506
	.data.b	227,3
	.data.b	17
	.data.b	36
	.data.w	.Ldw_begin+6180
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2513
	.data.b	71,78,82,67,79,78,49,0
	.section	.debug_info		;off: 7222
	.data.w	.Ldw_str_begin+2513
	.data.b	228,3
	.data.b	18
	.data.b	36
	.data.w	.Ldw_begin+6235
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2521
	.data.b	69,77,67,79,78,0
	.section	.debug_info		;off: 7239
	.data.w	.Ldw_str_begin+2521
	.data.b	229,3
	.data.b	16
	.data.b	36
	.data.w	.Ldw_begin+5905
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2527
	.data.b	82,69,83,69,82,86,69,68,95,49,67,0
	.section	.debug_info		;off: 7256
	.data.w	.Ldw_str_begin+2527
	.data.b	230,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1053
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2539
	.data.b	68,67,79,78,0
	.section	.debug_info		;off: 7273
	.data.w	.Ldw_str_begin+2539
	.data.b	231,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+1069
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2544
	.data.b	83,84,83,0
	.section	.debug_info		;off: 7290
	.data.w	.Ldw_str_begin+2544
	.data.b	232,3
	.data.b	14
	.data.b	36
	.data.w	.Ldw_begin+6730
	.data.b	2,35
	.data.b	64
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2548
	.data.b	69,83,84,83,0
	.section	.debug_info		;off: 7307
	.data.w	.Ldw_str_begin+2548
	.data.b	233,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+6785
	.data.b	2,35
	.data.b	68
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2553
	.data.b	83,83,67,79,78,0
	.section	.debug_info		;off: 7324
	.data.w	.Ldw_str_begin+2553
	.data.b	234,3
	.data.b	16
	.data.b	36
	.data.w	.Ldw_begin+6675
	.data.b	2,35
	.data.b	72
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2559
	.data.b	82,69,83,69,82,86,69,68,95,52,67,0
	.section	.debug_info		;off: 7341
	.data.w	.Ldw_str_begin+2559
	.data.b	235,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1085
	.data.b	2,35
	.data.b	76
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2571
	.data.b	83,84,83,67,0
	.section	.debug_info		;off: 7358
	.data.w	.Ldw_str_begin+2571
	.data.b	236,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+6125
	.data.b	2,35
	.data.b	84
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2576
	.data.b	76,84,67,79,78,0
	.section	.debug_info		;off: 7375
	.data.w	.Ldw_str_begin+2576
	.data.b	237,3
	.data.b	16
	.data.b	36
	.data.w	.Ldw_begin+6840
	.data.b	2,35
	.data.b	88
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2582
	.data.b	72,66,82,69,78,84,82,89,0
	.section	.debug_info		;off: 7392
	.data.w	.Ldw_str_begin+2582
	.data.b	238,3
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+6455
	.data.b	2,35
	.data.b	92
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2591
	.data.b	69,77,67,79,78,69,78,84,82,89,0
	.section	.debug_info		;off: 7409
	.data.w	.Ldw_str_begin+2591
	.data.b	239,3
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+5960
	.data.b	2,35
	.data.b	96
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2602
	.data.b	68,65,84,65,69,78,84,82,89,0
	.section	.debug_info		;off: 7426
	.data.w	.Ldw_str_begin+2602
	.data.b	240,3
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+1101
	.data.b	2,35
	.data.b	100
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2612
	.data.b	82,69,83,69,82,86,69,68,95,56,52,0
	.section	.debug_info		;off: 7443
	.data.w	.Ldw_str_begin+2612
	.data.b	241,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1117
	.data.b	3,35
	.data.b	132,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2624
	.data.b	82,68,82,0
	.section	.debug_info		;off: 7461
	.data.w	.Ldw_str_begin+2624
	.data.b	242,3
	.data.b	14
	.data.b	36
	.data.w	.Ldw_begin+6565
	.data.b	3,35
	.data.b	144,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2628
	.data.b	82,68,82,49,0
	.section	.debug_info		;off: 7479
	.data.w	.Ldw_str_begin+2628
	.data.b	243,3
	.data.b	14
	.data.b	36
	.data.w	.Ldw_begin+6565
	.data.b	3,35
	.data.b	148,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2633
	.data.b	82,68,82,50,0
	.section	.debug_info		;off: 7497
	.data.w	.Ldw_str_begin+2633
	.data.b	244,3
	.data.b	14
	.data.b	36
	.data.w	.Ldw_begin+6565
	.data.b	3,35
	.data.b	152,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2638
	.data.b	82,68,82,51,0
	.section	.debug_info		;off: 7515
	.data.w	.Ldw_str_begin+2638
	.data.b	245,3
	.data.b	14
	.data.b	36
	.data.w	.Ldw_begin+6565
	.data.b	3,35
	.data.b	156,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2643
	.data.b	82,69,83,69,82,86,69,68,95,65,48,0
	.section	.debug_info		;off: 7533
	.data.w	.Ldw_str_begin+2643
	.data.b	246,3
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1133
	.data.b	3,35
	.data.b	160,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2655
	.data.b	77,67,0
	.section	.debug_info		;off: 7551
	.data.w	.Ldw_str_begin+2655
	.data.b	247,3
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+6345
	.data.b	3,35
	.data.b	164,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2658
	.data.b	77,67,67,79,78,0
	.section	.debug_info		;off: 7569
	.data.w	.Ldw_str_begin+2658
	.data.b	248,3
	.data.b	16
	.data.b	36
	.data.w	.Ldw_begin+6400
	.data.b	3,35
	.data.b	168,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2664
	.data.b	68,69,76,65,89,0
	.section	.debug_info		;off: 7587
	.data.w	.Ldw_str_begin+2664
	.data.b	249,3
	.data.b	16
	.data.b	36
	.data.w	.Ldw_begin+6895
	.data.b	3,35
	.data.b	172,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2670
	.data.b	68,65,84,65,77,79,68,69,0
	.section	.debug_info		;off: 7605
	.data.w	.Ldw_str_begin+2670
	.data.b	250,3
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+6950
	.data.b	3,35
	.data.b	176,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2679
	.data.b	82,68,82,68,0
	.section	.debug_info		;off: 7623
	.data.w	.Ldw_str_begin+2679
	.data.b	251,3
	.data.b	15
	.data.b	36
	.data.w	.Ldw_begin+6620
	.data.b	3,35
	.data.b	180,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2684
	.data.b	70,73,70,79,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 7641
	.data.w	.Ldw_str_begin+2684
	.data.b	252,3
	.data.b	24
	.data.b	36
	.data.w	.Ldw_begin+7005
	.data.b	3,35
	.data.b	184,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2698
	.data.b	70,73,70,79,76,69,86,69,76,0
	.section	.debug_info		;off: 7659
	.data.w	.Ldw_str_begin+2698
	.data.b	253,3
	.data.b	20
	.data.b	36
	.data.w	.Ldw_begin+7060
	.data.b	3,35
	.data.b	188,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2708
	.data.b	68,67,79,78,69,71,0
	.section	.debug_info		;off: 7677
	.data.w	.Ldw_str_begin+2708
	.data.b	254,3
	.data.b	17
	.data.b	36
	.data.w	.Ldw_begin+1149
	.data.b	3,35
	.data.b	192,1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2715
	.data.b	69,83,80,73,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 7696
	.data.w	.Ldw_str_begin+2715
	.data.b	255,3
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+100

	.data.b	52
	.section	.debug_str		;off: 2727
	.data.b	0
	.section	.debug_info		;off: 7709
	.data.w	.Ldw_str_begin+2727
	.data.b	43
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2728
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,83,73,78,71,76,69,83,72,79,82,84,0
	.section	.debug_info		;off: 7719
	.data.w	.Ldw_str_begin+2728
	.data.b	44
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2757
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,83,73,78,71,76,69,76,79,78,71,0
	.section	.debug_info		;off: 7728
	.data.w	.Ldw_str_begin+2757
	.data.b	45
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2785
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,67,79,78,84,73,78,85,79,85,83,83,72,79,82,84,0
	.section	.debug_info		;off: 7737
	.data.w	.Ldw_str_begin+2785
	.data.b	46
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2818
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,67,79,78,84,73,78,85,79,85,83,76,79,78,71,0
	.section	.debug_info		;off: 7746
	.data.w	.Ldw_str_begin+2818
	.data.b	47
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2850
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,88,88,76,0
	.section	.debug_info		;off: 7755
	.data.w	.Ldw_str_begin+2850
	.data.b	48
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2871
	.data.b	69,83,80,73,95,77,65,83,84,69,82,95,77,79,68,69,95,77,79,86,69,67,79,85,78,84,69,82,0
	.section	.debug_info		;off: 7764
	.data.w	.Ldw_str_begin+2871
	.data.b	49
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2900
	.data.b	69,115,112,105,95,77,97,115,116,101,114,95,68,97,116,97,77,111,100,101,0
	.section	.debug_info		;off: 7774
	.data.w	.Ldw_str_begin+2900
	.data.b	50
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+7708

	.data.b	52
	.section	.debug_str		;off: 2921
	.data.b	0
	.section	.debug_info		;off: 7786
	.data.w	.Ldw_str_begin+2921
	.data.b	62
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2922
	.data.b	69,83,80,73,95,68,65,84,65,66,85,70,70,69,82,95,56,66,73,84,83,0
	.section	.debug_info		;off: 7796
	.data.w	.Ldw_str_begin+2922
	.data.b	63
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2944
	.data.b	69,83,80,73,95,68,65,84,65,66,85,70,70,69,82,95,49,54,66,73,84,83,0
	.section	.debug_info		;off: 7805
	.data.w	.Ldw_str_begin+2944
	.data.b	64
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2967
	.data.b	69,83,80,73,95,68,65,84,65,66,85,70,70,69,82,95,51,50,66,73,84,83,0
	.section	.debug_info		;off: 7814
	.data.w	.Ldw_str_begin+2967
	.data.b	65
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2990
	.data.b	69,115,112,105,95,68,97,116,97,66,117,102,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 7824
	.data.w	.Ldw_str_begin+2990
	.data.b	66
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+7785

	.data.b	52
	.section	.debug_str		;off: 3011
	.data.b	0
	.section	.debug_info		;off: 7836
	.data.w	.Ldw_str_begin+3011
	.data.b	70
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3012
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,79,78,69,0
	.section	.debug_info		;off: 7846
	.data.w	.Ldw_str_begin+3012
	.data.b	71
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3038
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,87,79,0
	.section	.debug_info		;off: 7855
	.data.w	.Ldw_str_begin+3038
	.data.b	72
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3064
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,72,82,69,69,0
	.section	.debug_info		;off: 7864
	.data.w	.Ldw_str_begin+3064
	.data.b	73
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 3092
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,79,85,82,0
	.section	.debug_info		;off: 7873
	.data.w	.Ldw_str_begin+3092
	.data.b	74
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 3119
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,73,86,69,0
	.section	.debug_info		;off: 7882
	.data.w	.Ldw_str_begin+3119
	.data.b	75
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 3146
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,83,73,88,0
	.section	.debug_info		;off: 7891
	.data.w	.Ldw_str_begin+3146
	.data.b	76
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 3172
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,83,69,86,69,78,0
	.section	.debug_info		;off: 7900
	.data.w	.Ldw_str_begin+3172
	.data.b	77
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 3200
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,69,73,71,72,84,0
	.section	.debug_info		;off: 7909
	.data.w	.Ldw_str_begin+3200
	.data.b	78
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 3228
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,78,73,78,69,0
	.section	.debug_info		;off: 7918
	.data.w	.Ldw_str_begin+3228
	.data.b	79
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 3255
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,69,78,0
	.section	.debug_info		;off: 7927
	.data.w	.Ldw_str_begin+3255
	.data.b	80
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 3281
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,69,76,69,86,69,78,0
	.section	.debug_info		;off: 7936
	.data.w	.Ldw_str_begin+3281
	.data.b	81
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 3310
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,87,69,76,86,69,0
	.section	.debug_info		;off: 7945
	.data.w	.Ldw_str_begin+3310
	.data.b	82
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 3339
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,72,73,82,84,69,69,78,0
	.section	.debug_info		;off: 7954
	.data.w	.Ldw_str_begin+3339
	.data.b	83
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 3370
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,79,85,82,84,69,69,78,0
	.section	.debug_info		;off: 7963
	.data.w	.Ldw_str_begin+3370
	.data.b	84
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 3401
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,73,70,84,69,69,78,0
	.section	.debug_info		;off: 7972
	.data.w	.Ldw_str_begin+3401
	.data.b	85
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 3431
	.data.b	69,83,80,73,95,84,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,83,73,88,84,69,69,78,0
	.section	.debug_info		;off: 7981
	.data.w	.Ldw_str_begin+3431
	.data.b	86
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3461
	.data.b	69,115,112,105,95,84,120,70,105,102,111,95,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 7991
	.data.w	.Ldw_str_begin+3461
	.data.b	87
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+7835

	.data.b	52
	.section	.debug_str		;off: 3483
	.data.b	0
	.section	.debug_info		;off: 8003
	.data.w	.Ldw_str_begin+3483
	.data.b	91
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3484
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,90,69,82,79,0
	.section	.debug_info		;off: 8013
	.data.w	.Ldw_str_begin+3484
	.data.b	92
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3511
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,79,78,69,0
	.section	.debug_info		;off: 8022
	.data.w	.Ldw_str_begin+3511
	.data.b	93
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3537
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,87,79,0
	.section	.debug_info		;off: 8031
	.data.w	.Ldw_str_begin+3537
	.data.b	94
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 3563
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,72,82,69,69,0
	.section	.debug_info		;off: 8040
	.data.w	.Ldw_str_begin+3563
	.data.b	95
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 3591
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,79,85,82,0
	.section	.debug_info		;off: 8049
	.data.w	.Ldw_str_begin+3591
	.data.b	96
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 3618
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,73,86,69,0
	.section	.debug_info		;off: 8058
	.data.w	.Ldw_str_begin+3618
	.data.b	97
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 3645
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,83,73,88,0
	.section	.debug_info		;off: 8067
	.data.w	.Ldw_str_begin+3645
	.data.b	98
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 3671
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,83,69,86,69,78,0
	.section	.debug_info		;off: 8076
	.data.w	.Ldw_str_begin+3671
	.data.b	99
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 3699
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,69,73,71,72,84,0
	.section	.debug_info		;off: 8085
	.data.w	.Ldw_str_begin+3699
	.data.b	100
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 3727
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,78,73,78,69,0
	.section	.debug_info		;off: 8094
	.data.w	.Ldw_str_begin+3727
	.data.b	101
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 3754
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,69,78,0
	.section	.debug_info		;off: 8103
	.data.w	.Ldw_str_begin+3754
	.data.b	102
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 3780
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,69,76,69,86,69,78,0
	.section	.debug_info		;off: 8112
	.data.w	.Ldw_str_begin+3780
	.data.b	103
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 3809
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,87,69,76,86,69,0
	.section	.debug_info		;off: 8121
	.data.w	.Ldw_str_begin+3809
	.data.b	104
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 3838
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,84,72,73,82,84,69,69,78,0
	.section	.debug_info		;off: 8130
	.data.w	.Ldw_str_begin+3838
	.data.b	105
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 3869
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,79,85,82,84,69,69,78,0
	.section	.debug_info		;off: 8139
	.data.w	.Ldw_str_begin+3869
	.data.b	106
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 3900
	.data.b	69,83,80,73,95,82,88,70,73,70,79,95,84,72,82,69,83,72,79,76,68,95,70,73,70,84,69,69,78,0
	.section	.debug_info		;off: 8148
	.data.w	.Ldw_str_begin+3900
	.data.b	107
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3930
	.data.b	69,115,112,105,95,82,120,70,105,102,111,95,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 8158
	.data.w	.Ldw_str_begin+3930
	.data.b	108
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8002

	.data.b	52
	.section	.debug_str		;off: 3952
	.data.b	0
	.section	.debug_info		;off: 8170
	.data.w	.Ldw_str_begin+3952
	.data.b	112
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3953
	.data.b	69,83,80,73,95,70,73,70,79,77,79,68,69,95,67,79,77,66,73,78,69,68,0
	.section	.debug_info		;off: 8180
	.data.w	.Ldw_str_begin+3953
	.data.b	113
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3976
	.data.b	69,83,80,73,95,70,73,70,79,77,79,68,69,95,83,73,78,71,76,69,0
	.section	.debug_info		;off: 8189
	.data.w	.Ldw_str_begin+3976
	.data.b	114
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3997
	.data.b	69,83,80,73,95,70,73,70,79,77,79,68,69,95,66,65,84,67,72,0
	.section	.debug_info		;off: 8198
	.data.w	.Ldw_str_begin+3997
	.data.b	115
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4017
	.data.b	69,115,112,105,95,70,105,102,111,77,111,100,101,0
	.section	.debug_info		;off: 8208
	.data.w	.Ldw_str_begin+4017
	.data.b	116
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8169

	.data.b	52
	.section	.debug_str		;off: 4031
	.data.b	0
	.section	.debug_info		;off: 8220
	.data.w	.Ldw_str_begin+4031
	.data.b	120
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4032
	.data.b	69,83,80,73,95,80,65,82,73,84,89,77,79,68,69,95,69,86,69,78,0
	.section	.debug_info		;off: 8230
	.data.w	.Ldw_str_begin+4032
	.data.b	121
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4053
	.data.b	69,83,80,73,95,80,65,82,73,84,89,77,79,68,69,95,79,68,68,0
	.section	.debug_info		;off: 8239
	.data.w	.Ldw_str_begin+4053
	.data.b	122
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4073
	.data.b	69,83,80,73,95,80,65,82,73,84,89,77,79,68,69,95,78,79,78,69,0
	.section	.debug_info		;off: 8248
	.data.w	.Ldw_str_begin+4073
	.data.b	123
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4094
	.data.b	69,115,112,105,95,80,97,114,105,116,121,77,111,100,101,0
	.section	.debug_info		;off: 8258
	.data.w	.Ldw_str_begin+4094
	.data.b	124
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8219

	.data.b	52
	.section	.debug_str		;off: 4110
	.data.b	0
	.section	.debug_info		;off: 8270
	.data.w	.Ldw_str_begin+4110
	.data.b	128,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4111
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,0
	.section	.debug_info		;off: 8281
	.data.w	.Ldw_str_begin+4111
	.data.b	129,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4128
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,51,0
	.section	.debug_info		;off: 8291
	.data.w	.Ldw_str_begin+4128
	.data.b	130,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 4145
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,52,0
	.section	.debug_info		;off: 8301
	.data.w	.Ldw_str_begin+4145
	.data.b	131,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 4162
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,53,0
	.section	.debug_info		;off: 8311
	.data.w	.Ldw_str_begin+4162
	.data.b	132,1
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 4179
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,54,0
	.section	.debug_info		;off: 8321
	.data.w	.Ldw_str_begin+4179
	.data.b	133,1
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 4196
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,55,0
	.section	.debug_info		;off: 8331
	.data.w	.Ldw_str_begin+4196
	.data.b	134,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 4213
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,56,0
	.section	.debug_info		;off: 8341
	.data.w	.Ldw_str_begin+4213
	.data.b	135,1
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 4230
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,57,0
	.section	.debug_info		;off: 8351
	.data.w	.Ldw_str_begin+4230
	.data.b	136,1
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 4247
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,48,0
	.section	.debug_info		;off: 8361
	.data.w	.Ldw_str_begin+4247
	.data.b	137,1
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 4265
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,49,0
	.section	.debug_info		;off: 8371
	.data.w	.Ldw_str_begin+4265
	.data.b	138,1
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 4283
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,50,0
	.section	.debug_info		;off: 8381
	.data.w	.Ldw_str_begin+4283
	.data.b	139,1
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 4301
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,51,0
	.section	.debug_info		;off: 8391
	.data.w	.Ldw_str_begin+4301
	.data.b	140,1
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 4319
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,52,0
	.section	.debug_info		;off: 8401
	.data.w	.Ldw_str_begin+4319
	.data.b	141,1
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 4337
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,53,0
	.section	.debug_info		;off: 8411
	.data.w	.Ldw_str_begin+4337
	.data.b	142,1
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 4355
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,54,0
	.section	.debug_info		;off: 8421
	.data.w	.Ldw_str_begin+4355
	.data.b	143,1
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	51
	.section	.debug_str		;off: 4373
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,55,0
	.section	.debug_info		;off: 8431
	.data.w	.Ldw_str_begin+4373
	.data.b	144,1
	.data.b	5
	.data.b	35
	.data.b	16

	.data.b	51
	.section	.debug_str		;off: 4391
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,56,0
	.section	.debug_info		;off: 8441
	.data.w	.Ldw_str_begin+4391
	.data.b	145,1
	.data.b	5
	.data.b	35
	.data.b	17

	.data.b	51
	.section	.debug_str		;off: 4409
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,49,57,0
	.section	.debug_info		;off: 8451
	.data.w	.Ldw_str_begin+4409
	.data.b	146,1
	.data.b	5
	.data.b	35
	.data.b	18

	.data.b	51
	.section	.debug_str		;off: 4427
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,48,0
	.section	.debug_info		;off: 8461
	.data.w	.Ldw_str_begin+4427
	.data.b	147,1
	.data.b	5
	.data.b	35
	.data.b	19

	.data.b	51
	.section	.debug_str		;off: 4445
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,49,0
	.section	.debug_info		;off: 8471
	.data.w	.Ldw_str_begin+4445
	.data.b	148,1
	.data.b	5
	.data.b	35
	.data.b	20

	.data.b	51
	.section	.debug_str		;off: 4463
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,50,0
	.section	.debug_info		;off: 8481
	.data.w	.Ldw_str_begin+4463
	.data.b	149,1
	.data.b	5
	.data.b	35
	.data.b	21

	.data.b	51
	.section	.debug_str		;off: 4481
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,51,0
	.section	.debug_info		;off: 8491
	.data.w	.Ldw_str_begin+4481
	.data.b	150,1
	.data.b	5
	.data.b	35
	.data.b	22

	.data.b	51
	.section	.debug_str		;off: 4499
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,52,0
	.section	.debug_info		;off: 8501
	.data.w	.Ldw_str_begin+4499
	.data.b	151,1
	.data.b	5
	.data.b	35
	.data.b	23

	.data.b	51
	.section	.debug_str		;off: 4517
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,53,0
	.section	.debug_info		;off: 8511
	.data.w	.Ldw_str_begin+4517
	.data.b	152,1
	.data.b	5
	.data.b	35
	.data.b	24

	.data.b	51
	.section	.debug_str		;off: 4535
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,54,0
	.section	.debug_info		;off: 8521
	.data.w	.Ldw_str_begin+4535
	.data.b	153,1
	.data.b	5
	.data.b	35
	.data.b	25

	.data.b	51
	.section	.debug_str		;off: 4553
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,55,0
	.section	.debug_info		;off: 8531
	.data.w	.Ldw_str_begin+4553
	.data.b	154,1
	.data.b	5
	.data.b	35
	.data.b	26

	.data.b	51
	.section	.debug_str		;off: 4571
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,56,0
	.section	.debug_info		;off: 8541
	.data.w	.Ldw_str_begin+4571
	.data.b	155,1
	.data.b	5
	.data.b	35
	.data.b	27

	.data.b	51
	.section	.debug_str		;off: 4589
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,50,57,0
	.section	.debug_info		;off: 8551
	.data.w	.Ldw_str_begin+4589
	.data.b	156,1
	.data.b	5
	.data.b	35
	.data.b	28

	.data.b	51
	.section	.debug_str		;off: 4607
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,51,48,0
	.section	.debug_info		;off: 8561
	.data.w	.Ldw_str_begin+4607
	.data.b	157,1
	.data.b	5
	.data.b	35
	.data.b	29

	.data.b	51
	.section	.debug_str		;off: 4625
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,51,49,0
	.section	.debug_info		;off: 8571
	.data.w	.Ldw_str_begin+4625
	.data.b	158,1
	.data.b	5
	.data.b	35
	.data.b	30

	.data.b	51
	.section	.debug_str		;off: 4643
	.data.b	69,83,80,73,95,68,65,84,65,87,73,68,84,72,95,51,50,0
	.section	.debug_info		;off: 8581
	.data.w	.Ldw_str_begin+4643
	.data.b	159,1
	.data.b	5
	.data.b	35
	.data.b	31

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4661
	.data.b	69,115,112,105,95,68,97,116,97,87,105,100,116,104,0
	.section	.debug_info		;off: 8592
	.data.w	.Ldw_str_begin+4661
	.data.b	160,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8269

	.data.b	52
	.section	.debug_str		;off: 4676
	.data.b	0
	.section	.debug_info		;off: 8605
	.data.w	.Ldw_str_begin+4676
	.data.b	172,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4677
	.data.b	69,83,80,73,95,66,73,84,79,82,68,69,82,95,76,83,66,0
	.section	.debug_info		;off: 8616
	.data.w	.Ldw_str_begin+4677
	.data.b	173,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4695
	.data.b	69,83,80,73,95,66,73,84,79,82,68,69,82,95,77,83,66,0
	.section	.debug_info		;off: 8626
	.data.w	.Ldw_str_begin+4695
	.data.b	174,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4713
	.data.b	69,115,112,105,95,66,105,116,79,114,100,101,114,0
	.section	.debug_info		;off: 8637
	.data.w	.Ldw_str_begin+4713
	.data.b	175,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8604

	.data.b	52
	.section	.debug_str		;off: 4727
	.data.b	0
	.section	.debug_info		;off: 8650
	.data.w	.Ldw_str_begin+4727
	.data.b	202,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4728
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,54,52,0
	.section	.debug_info		;off: 8661
	.data.w	.Ldw_str_begin+4728
	.data.b	203,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4750
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,49,50,56,0
	.section	.debug_info		;off: 8671
	.data.w	.Ldw_str_begin+4750
	.data.b	204,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4773
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,50,53,54,0
	.section	.debug_info		;off: 8681
	.data.w	.Ldw_str_begin+4773
	.data.b	205,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 4796
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,53,49,50,0
	.section	.debug_info		;off: 8691
	.data.w	.Ldw_str_begin+4796
	.data.b	206,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 4819
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,49,48,50,52,0
	.section	.debug_info		;off: 8701
	.data.w	.Ldw_str_begin+4819
	.data.b	207,1
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 4843
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,50,48,52,56,0
	.section	.debug_info		;off: 8711
	.data.w	.Ldw_str_begin+4843
	.data.b	208,1
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 4867
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,52,48,57,54,0
	.section	.debug_info		;off: 8721
	.data.w	.Ldw_str_begin+4867
	.data.b	209,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 4891
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,56,49,57,50,0
	.section	.debug_info		;off: 8731
	.data.w	.Ldw_str_begin+4891
	.data.b	210,1
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 4915
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,49,54,51,56,52,0
	.section	.debug_info		;off: 8741
	.data.w	.Ldw_str_begin+4915
	.data.b	211,1
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 4940
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,51,50,55,54,56,0
	.section	.debug_info		;off: 8751
	.data.w	.Ldw_str_begin+4940
	.data.b	212,1
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 4965
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,54,53,53,51,54,0
	.section	.debug_info		;off: 8761
	.data.w	.Ldw_str_begin+4965
	.data.b	213,1
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 4990
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,49,51,49,48,55,50,0
	.section	.debug_info		;off: 8771
	.data.w	.Ldw_str_begin+4990
	.data.b	214,1
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 5016
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,50,54,50,49,52,52,0
	.section	.debug_info		;off: 8781
	.data.w	.Ldw_str_begin+5016
	.data.b	215,1
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 5042
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,53,50,52,50,56,56,0
	.section	.debug_info		;off: 8791
	.data.w	.Ldw_str_begin+5042
	.data.b	216,1
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 5068
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,49,48,52,56,53,55,54,0
	.section	.debug_info		;off: 8801
	.data.w	.Ldw_str_begin+5068
	.data.b	217,1
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 5095
	.data.b	69,83,80,73,95,69,88,80,69,67,84,84,73,77,69,79,85,84,95,50,48,57,55,49,53,50,0
	.section	.debug_info		;off: 8811
	.data.w	.Ldw_str_begin+5095
	.data.b	218,1
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5122
	.data.b	69,115,112,105,95,69,120,112,101,99,116,84,105,109,101,111,117,116,86,97,108,117,101,0
	.section	.debug_info		;off: 8822
	.data.w	.Ldw_str_begin+5122
	.data.b	219,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8649

	.data.b	52
	.section	.debug_str		;off: 5146
	.data.b	0
	.section	.debug_info		;off: 8835
	.data.w	.Ldw_str_begin+5146
	.data.b	223,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5147
	.data.b	69,83,80,73,95,67,76,79,67,75,80,79,76,65,82,73,84,89,95,73,68,76,69,95,76,79,87,0
	.section	.debug_info		;off: 8846
	.data.w	.Ldw_str_begin+5147
	.data.b	224,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5175
	.data.b	69,83,80,73,95,67,76,79,67,75,80,79,76,65,82,73,84,89,95,73,68,76,69,95,72,73,71,72,0
	.section	.debug_info		;off: 8856
	.data.w	.Ldw_str_begin+5175
	.data.b	225,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5204
	.data.b	69,115,112,105,95,67,108,111,99,107,80,111,108,97,114,105,116,121,0
	.section	.debug_info		;off: 8867
	.data.w	.Ldw_str_begin+5204
	.data.b	226,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8834

	.data.b	52
	.section	.debug_str		;off: 5223
	.data.b	0
	.section	.debug_info		;off: 8880
	.data.w	.Ldw_str_begin+5223
	.data.b	230,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5224
	.data.b	69,83,80,73,95,67,76,79,67,75,80,72,65,83,69,95,70,73,82,83,84,83,65,77,80,76,69,0
	.section	.debug_info		;off: 8891
	.data.w	.Ldw_str_begin+5224
	.data.b	231,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5252
	.data.b	69,83,80,73,95,67,76,79,67,75,80,72,65,83,69,95,83,69,67,79,78,68,83,65,77,80,76,69,0
	.section	.debug_info		;off: 8901
	.data.w	.Ldw_str_begin+5252
	.data.b	232,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5281
	.data.b	69,115,112,105,95,67,108,111,99,107,80,104,97,115,101,0
	.section	.debug_info		;off: 8912
	.data.w	.Ldw_str_begin+5281
	.data.b	233,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8879

	.data.b	52
	.section	.debug_str		;off: 5297
	.data.b	0
	.section	.debug_info		;off: 8925
	.data.w	.Ldw_str_begin+5297
	.data.b	237,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5298
	.data.b	69,83,80,73,95,83,76,83,79,79,85,84,80,85,84,95,76,69,86,69,76,95,76,79,87,0
	.section	.debug_info		;off: 8936
	.data.w	.Ldw_str_begin+5298
	.data.b	238,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5324
	.data.b	69,83,80,73,95,83,76,83,79,79,85,84,80,85,84,95,76,69,86,69,76,95,72,73,71,72,0
	.section	.debug_info		;off: 8946
	.data.w	.Ldw_str_begin+5324
	.data.b	239,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5351
	.data.b	69,115,112,105,95,65,99,116,105,118,101,79,117,116,112,117,116,76,101,118,101,108,0
	.section	.debug_info		;off: 8957
	.data.w	.Ldw_str_begin+5351
	.data.b	240,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8924

	.data.b	52
	.section	.debug_str		;off: 5374
	.data.b	0
	.section	.debug_info		;off: 8970
	.data.w	.Ldw_str_begin+5374
	.data.b	244,1
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5375
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,49,0
	.section	.debug_info		;off: 8981
	.data.w	.Ldw_str_begin+5375
	.data.b	245,1
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5398
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,52,0
	.section	.debug_info		;off: 8991
	.data.w	.Ldw_str_begin+5398
	.data.b	246,1
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5421
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,49,54,0
	.section	.debug_info		;off: 9001
	.data.w	.Ldw_str_begin+5421
	.data.b	247,1
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5445
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,54,52,0
	.section	.debug_info		;off: 9011
	.data.w	.Ldw_str_begin+5445
	.data.b	248,1
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5469
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,50,53,54,0
	.section	.debug_info		;off: 9021
	.data.w	.Ldw_str_begin+5469
	.data.b	249,1
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5494
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,49,48,50,52,0
	.section	.debug_info		;off: 9031
	.data.w	.Ldw_str_begin+5494
	.data.b	250,1
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 5520
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,52,48,57,54,0
	.section	.debug_info		;off: 9041
	.data.w	.Ldw_str_begin+5520
	.data.b	251,1
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 5546
	.data.b	69,83,80,73,95,68,69,76,65,89,95,80,82,69,83,67,65,76,69,82,95,49,54,51,56,52,0
	.section	.debug_info		;off: 9051
	.data.w	.Ldw_str_begin+5546
	.data.b	252,1
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5573
	.data.b	69,115,112,105,95,68,101,108,97,121,80,114,101,115,99,97,108,101,114,0
	.section	.debug_info		;off: 9062
	.data.w	.Ldw_str_begin+5573
	.data.b	253,1
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+8969

	.data.b	52
	.section	.debug_str		;off: 5593
	.data.b	0
	.section	.debug_info		;off: 9075
	.data.w	.Ldw_str_begin+5593
	.data.b	129,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5594
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,49,0
	.section	.debug_info		;off: 9086
	.data.w	.Ldw_str_begin+5594
	.data.b	130,2
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5612
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,50,0
	.section	.debug_info		;off: 9096
	.data.w	.Ldw_str_begin+5612
	.data.b	131,2
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5630
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,51,0
	.section	.debug_info		;off: 9106
	.data.w	.Ldw_str_begin+5630
	.data.b	132,2
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5648
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,52,0
	.section	.debug_info		;off: 9116
	.data.w	.Ldw_str_begin+5648
	.data.b	133,2
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5666
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,53,0
	.section	.debug_info		;off: 9126
	.data.w	.Ldw_str_begin+5666
	.data.b	134,2
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5684
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,54,0
	.section	.debug_info		;off: 9136
	.data.w	.Ldw_str_begin+5684
	.data.b	135,2
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 5702
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,55,0
	.section	.debug_info		;off: 9146
	.data.w	.Ldw_str_begin+5702
	.data.b	136,2
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 5720
	.data.b	69,83,80,73,95,68,69,76,65,89,95,85,78,73,84,95,56,0
	.section	.debug_info		;off: 9156
	.data.w	.Ldw_str_begin+5720
	.data.b	137,2
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5738
	.data.b	69,115,112,105,95,68,101,108,97,121,85,110,105,116,0
	.section	.debug_info		;off: 9167
	.data.w	.Ldw_str_begin+5738
	.data.b	138,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9074

	.data.b	52
	.section	.debug_str		;off: 5753
	.data.b	0
	.section	.debug_info		;off: 9180
	.data.w	.Ldw_str_begin+5753
	.data.b	142,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5754
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,65,95,79,78,69,95,85,78,73,84,0
	.section	.debug_info		;off: 9191
	.data.w	.Ldw_str_begin+5754
	.data.b	143,2
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5780
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,65,95,84,87,79,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9201
	.data.w	.Ldw_str_begin+5780
	.data.b	144,2
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5807
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,65,95,84,72,82,69,69,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9211
	.data.w	.Ldw_str_begin+5807
	.data.b	145,2
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5836
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,65,95,70,79,85,82,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9221
	.data.w	.Ldw_str_begin+5836
	.data.b	146,2
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5864
	.data.b	69,115,112,105,95,80,97,114,97,109,101,116,101,114,95,65,0
	.section	.debug_info		;off: 9232
	.data.w	.Ldw_str_begin+5864
	.data.b	147,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9179

	.data.b	52
	.section	.debug_str		;off: 5881
	.data.b	0
	.section	.debug_info		;off: 9245
	.data.w	.Ldw_str_begin+5881
	.data.b	151,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5882
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,66,95,78,79,78,69,0
	.section	.debug_info		;off: 9256
	.data.w	.Ldw_str_begin+5882
	.data.b	152,2
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5904
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,66,95,79,78,69,95,85,78,73,84,0
	.section	.debug_info		;off: 9266
	.data.w	.Ldw_str_begin+5904
	.data.b	153,2
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5930
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,66,95,84,87,79,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9276
	.data.w	.Ldw_str_begin+5930
	.data.b	154,2
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5957
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,66,95,84,72,82,69,69,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9286
	.data.w	.Ldw_str_begin+5957
	.data.b	155,2
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5986
	.data.b	69,115,112,105,95,80,97,114,97,109,101,116,101,114,95,66,0
	.section	.debug_info		;off: 9297
	.data.w	.Ldw_str_begin+5986
	.data.b	156,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9244

	.data.b	52
	.section	.debug_str		;off: 6003
	.data.b	0
	.section	.debug_info		;off: 9310
	.data.w	.Ldw_str_begin+6003
	.data.b	160,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6004
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,67,95,78,79,78,69,0
	.section	.debug_info		;off: 9321
	.data.w	.Ldw_str_begin+6004
	.data.b	161,2
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6026
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,67,95,79,78,69,95,85,78,73,84,0
	.section	.debug_info		;off: 9331
	.data.w	.Ldw_str_begin+6026
	.data.b	162,2
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6052
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,67,95,84,87,79,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9341
	.data.w	.Ldw_str_begin+6052
	.data.b	163,2
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6079
	.data.b	69,83,80,73,95,80,65,82,65,77,69,84,69,82,95,67,95,84,72,82,69,69,95,85,78,73,84,83,0
	.section	.debug_info		;off: 9351
	.data.w	.Ldw_str_begin+6079
	.data.b	164,2
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6108
	.data.b	69,115,112,105,95,80,97,114,97,109,101,116,101,114,95,67,0
	.section	.debug_info		;off: 9362
	.data.w	.Ldw_str_begin+6108
	.data.b	165,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9309

	.data.b	52
	.section	.debug_str		;off: 6125
	.data.b	0
	.section	.debug_info		;off: 9375
	.data.w	.Ldw_str_begin+6125
	.data.b	169,2
	.data.b	1
	.data.b	35
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6126
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,48,0
	.section	.debug_info		;off: 9386
	.data.w	.Ldw_str_begin+6126
	.data.b	170,2
	.data.b	5
	.data.b	35
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6147
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,0
	.section	.debug_info		;off: 9396
	.data.w	.Ldw_str_begin+6147
	.data.b	171,2
	.data.b	5
	.data.b	35
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6168
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,50,0
	.section	.debug_info		;off: 9406
	.data.w	.Ldw_str_begin+6168
	.data.b	172,2
	.data.b	5
	.data.b	35
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6189
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,51,0
	.section	.debug_info		;off: 9416
	.data.w	.Ldw_str_begin+6189
	.data.b	173,2
	.data.b	5
	.data.b	35
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 6210
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,52,0
	.section	.debug_info		;off: 9426
	.data.w	.Ldw_str_begin+6210
	.data.b	174,2
	.data.b	5
	.data.b	35
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 6231
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,53,0
	.section	.debug_info		;off: 9436
	.data.w	.Ldw_str_begin+6231
	.data.b	175,2
	.data.b	5
	.data.b	35
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 6252
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,54,0
	.section	.debug_info		;off: 9446
	.data.w	.Ldw_str_begin+6252
	.data.b	176,2
	.data.b	5
	.data.b	35
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 6273
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,55,0
	.section	.debug_info		;off: 9456
	.data.w	.Ldw_str_begin+6273
	.data.b	177,2
	.data.b	5
	.data.b	35
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 6294
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,56,0
	.section	.debug_info		;off: 9466
	.data.w	.Ldw_str_begin+6294
	.data.b	178,2
	.data.b	5
	.data.b	35
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 6315
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,57,0
	.section	.debug_info		;off: 9476
	.data.w	.Ldw_str_begin+6315
	.data.b	179,2
	.data.b	5
	.data.b	35
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 6336
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,48,0
	.section	.debug_info		;off: 9486
	.data.w	.Ldw_str_begin+6336
	.data.b	180,2
	.data.b	5
	.data.b	35
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 6358
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,49,0
	.section	.debug_info		;off: 9496
	.data.w	.Ldw_str_begin+6358
	.data.b	181,2
	.data.b	5
	.data.b	35
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 6380
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,50,0
	.section	.debug_info		;off: 9506
	.data.w	.Ldw_str_begin+6380
	.data.b	182,2
	.data.b	5
	.data.b	35
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 6402
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,51,0
	.section	.debug_info		;off: 9516
	.data.w	.Ldw_str_begin+6402
	.data.b	183,2
	.data.b	5
	.data.b	35
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 6424
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,52,0
	.section	.debug_info		;off: 9526
	.data.w	.Ldw_str_begin+6424
	.data.b	184,2
	.data.b	5
	.data.b	35
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 6446
	.data.b	69,83,80,73,95,67,83,95,67,72,65,78,78,69,76,95,73,68,95,49,53,0
	.section	.debug_info		;off: 9536
	.data.w	.Ldw_str_begin+6446
	.data.b	185,2
	.data.b	5
	.data.b	35
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6468
	.data.b	69,115,112,105,95,67,115,95,67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 9547
	.data.w	.Ldw_str_begin+6468
	.data.b	186,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9374

	.data.b	71
	.data.b	195,2
	.data.b	1
	.data.b	35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6486
	.data.b	98,97,117,100,114,97,116,101,80,97,114,97,109,101,116,101,114,65,0
	.section	.debug_info		;off: 9567
	.data.w	.Ldw_str_begin+6486
	.data.b	196,2
	.data.b	22
	.data.b	35
	.data.w	.Ldw_begin+9231
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6505
	.data.b	98,97,117,100,114,97,116,101,80,97,114,97,109,101,116,101,114,66,0
	.section	.debug_info		;off: 9584
	.data.w	.Ldw_str_begin+6505
	.data.b	197,2
	.data.b	22
	.data.b	35
	.data.w	.Ldw_begin+9296
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6524
	.data.b	98,97,117,100,114,97,116,101,80,97,114,97,109,101,116,101,114,67,0
	.section	.debug_info		;off: 9601
	.data.w	.Ldw_str_begin+6524
	.data.b	198,2
	.data.b	22
	.data.b	35
	.data.w	.Ldw_begin+9361
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6543
	.data.b	98,97,117,100,114,97,116,101,80,97,114,97,109,101,116,101,114,81,0
	.section	.debug_info		;off: 9618
	.data.w	.Ldw_str_begin+6543
	.data.b	199,2
	.data.b	11
	.data.b	35
	.data.w	.Ldw_begin+2122
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6562
	.data.b	69,115,112,105,95,66,97,117,100,82,97,116,101,0
	.section	.debug_info		;off: 9636
	.data.w	.Ldw_str_begin+6562
	.data.b	200,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9559

	.data.b	71
	.data.b	204,2
	.data.b	1
	.data.b	35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6576
	.data.b	100,101,108,97,121,84,105,109,101,80,114,101,115,99,97,108,101,114,99,111,69,102,102,105,99,105,101,110,116,0
	.section	.debug_info		;off: 9656
	.data.w	.Ldw_str_begin+6576
	.data.b	205,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+9061
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6606
	.data.b	100,101,108,97,121,84,105,109,101,80,114,101,115,99,97,108,101,114,85,110,105,116,0
	.section	.debug_info		;off: 9673
	.data.w	.Ldw_str_begin+6606
	.data.b	206,2
	.data.b	20
	.data.b	35
	.data.w	.Ldw_begin+9166
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6629
	.data.b	69,115,112,105,95,80,104,97,115,101,68,101,108,97,121,84,105,109,101,0
	.section	.debug_info		;off: 9691
	.data.w	.Ldw_str_begin+6629
	.data.b	207,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9648

	.data.b	71
	.data.b	211,2
	.data.b	1
	.data.b	35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6649
	.data.b	116,114,97,105,108,68,101,108,97,121,84,105,109,101,0
	.section	.debug_info		;off: 9711
	.data.w	.Ldw_str_begin+6649
	.data.b	212,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+9690
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6664
	.data.b	108,101,97,100,105,110,103,68,101,108,97,121,84,105,109,101,0
	.section	.debug_info		;off: 9728
	.data.w	.Ldw_str_begin+6664
	.data.b	213,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+9690
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6681
	.data.b	105,100,108,101,68,101,108,97,121,84,105,109,101,0
	.section	.debug_info		;off: 9745
	.data.w	.Ldw_str_begin+6681
	.data.b	214,2
	.data.b	25
	.data.b	35
	.data.w	.Ldw_begin+9690
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6695
	.data.b	69,115,112,105,95,80,104,97,115,101,68,101,108,97,121,0
	.section	.debug_info		;off: 9763
	.data.w	.Ldw_str_begin+6695
	.data.b	215,2
	.data.b	3
	.data.b	35
	.data.w	.Ldw_begin+9703

	.data.b	71
	.data.b	162,1
	.data.b	1
	.data.b	34
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6711
	.data.b	101,120,112,101,99,116,84,105,109,101,111,117,116,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 9783
	.data.w	.Ldw_str_begin+6711
	.data.b	163,1
	.data.b	29
	.data.b	34
	.data.w	.Ldw_begin+8821
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6734
	.data.b	116,120,70,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 9800
	.data.w	.Ldw_str_begin+6734
	.data.b	164,1
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+7990
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6750
	.data.b	114,120,70,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 9817
	.data.w	.Ldw_str_begin+6750
	.data.b	165,1
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+8157
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6766
	.data.b	116,120,70,105,102,111,77,111,100,101,0
	.section	.debug_info		;off: 9834
	.data.w	.Ldw_str_begin+6766
	.data.b	166,1
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8207
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6777
	.data.b	114,120,70,105,102,111,77,111,100,101,0
	.section	.debug_info		;off: 9851
	.data.w	.Ldw_str_begin+6777
	.data.b	167,1
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8207
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6788
	.data.b	105,110,116,101,114,114,117,112,116,69,110,0
	.section	.debug_info		;off: 9868
	.data.w	.Ldw_str_begin+6788
	.data.b	168,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6800
	.data.b	99,108,111,99,107,68,105,118,105,115,105,111,110,0
	.section	.debug_info		;off: 9885
	.data.w	.Ldw_str_begin+6800
	.data.b	169,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+2134
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6814
	.data.b	100,109,97,69,110,0
	.section	.debug_info		;off: 9902
	.data.w	.Ldw_str_begin+6814
	.data.b	170,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	26
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6820
	.data.b	109,111,118,101,67,111,117,110,116,101,114,69,110,0
	.section	.debug_info		;off: 9919
	.data.w	.Ldw_str_begin+6820
	.data.b	171,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	27
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6834
	.data.b	69,115,112,105,95,77,97,115,116,101,114,95,77,111,100,117,108,101,73,110,105,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 9937
	.data.w	.Ldw_str_begin+6834
	.data.b	172,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9775

	.data.b	71
	.data.b	175,1
	.data.b	1
	.data.b	34
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6863
	.data.b	98,97,117,100,82,97,116,101,0
	.section	.debug_info		;off: 9957
	.data.w	.Ldw_str_begin+6863
	.data.b	176,1
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+9635
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6872
	.data.b	99,108,111,99,107,80,111,108,97,114,105,116,121,0
	.section	.debug_info		;off: 9974
	.data.w	.Ldw_str_begin+6872
	.data.b	177,1
	.data.b	24
	.data.b	34
	.data.w	.Ldw_begin+8866
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6886
	.data.b	99,108,111,99,107,80,104,97,115,101,0
	.section	.debug_info		;off: 9991
	.data.w	.Ldw_str_begin+6886
	.data.b	178,1
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+8911
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6897
	.data.b	112,97,114,105,116,121,67,104,101,99,107,69,110,97,98,108,101,0
	.section	.debug_info		;off: 10008
	.data.w	.Ldw_str_begin+6897
	.data.b	179,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6915
	.data.b	99,115,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 10025
	.data.w	.Ldw_str_begin+6915
	.data.b	180,1
	.data.b	23
	.data.b	34
	.data.w	.Ldw_begin+9546
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6925
	.data.b	115,108,115,111,65,99,116,105,118,101,76,101,118,101,108,0
	.section	.debug_info		;off: 10042
	.data.w	.Ldw_str_begin+6925
	.data.b	181,1
	.data.b	28
	.data.b	34
	.data.w	.Ldw_begin+8956
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6941
	.data.b	115,108,115,111,69,110,0
	.section	.debug_info		;off: 10059
	.data.w	.Ldw_str_begin+6941
	.data.b	182,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6948
	.data.b	69,115,112,105,95,77,97,115,116,101,114,95,67,104,97,110,110,101,108,73,110,105,116,67,111,110,102,105,103,0
	.section	.debug_info		;off: 10077
	.data.w	.Ldw_str_begin+6948
	.data.b	183,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+9949

	.data.b	71
	.data.b	206,1
	.data.b	1
	.data.b	34
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6978
	.data.b	100,101,108,97,121,84,105,109,101,0
	.section	.debug_info		;off: 10097
	.data.w	.Ldw_str_begin+6978
	.data.b	207,1
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+9762
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6988
	.data.b	100,97,116,97,87,105,100,116,104,0
	.section	.debug_info		;off: 10114
	.data.w	.Ldw_str_begin+6988
	.data.b	208,1
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+8591
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6998
	.data.b	100,97,116,97,77,111,100,101,0
	.section	.debug_info		;off: 10131
	.data.w	.Ldw_str_begin+6998
	.data.b	209,1
	.data.b	26
	.data.b	34
	.data.w	.Ldw_begin+7773
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7007
	.data.b	98,105,116,79,114,100,101,114,0
	.section	.debug_info		;off: 10148
	.data.w	.Ldw_str_begin+7007
	.data.b	210,1
	.data.b	19
	.data.b	34
	.data.w	.Ldw_begin+8636
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7016
	.data.b	112,97,114,105,116,121,77,111,100,101,0
	.section	.debug_info		;off: 10165
	.data.w	.Ldw_str_begin+7016
	.data.b	211,1
	.data.b	21
	.data.b	34
	.data.w	.Ldw_begin+8257
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7027
	.data.b	69,115,112,105,95,67,104,97,110,110,101,108,68,121,110,97,109,105,99,67,111,110,102,105,103,0
	.section	.debug_info		;off: 10183
	.data.w	.Ldw_str_begin+7027
	.data.b	212,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+10089

	.data.b	71
	.data.b	190,6
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7053
	.data.b	83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 10203
	.data.w	.Ldw_str_begin+7053
	.data.b	191,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7061
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 10224
	.data.w	.Ldw_str_begin+7061
	.data.b	192,6
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+1165

	.data.b	71
	.data.b	196,6
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7081
	.data.b	68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 10244
	.data.w	.Ldw_str_begin+7081
	.data.b	197,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7090
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 10265
	.data.w	.Ldw_str_begin+7090
	.data.b	198,6
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+1170

	.data.b	71
	.data.b	202,6
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7111
	.data.b	76,77,0
	.section	.debug_info		;off: 10285
	.data.w	.Ldw_str_begin+7111
	.data.b	203,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7114
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 10305
	.data.w	.Ldw_str_begin+7114
	.data.b	204,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7125
	.data.b	76,76,73,0
	.section	.debug_info		;off: 10325
	.data.w	.Ldw_str_begin+7125
	.data.b	205,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7129
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,66,105,116,115,0
	.section	.debug_info		;off: 10346
	.data.w	.Ldw_str_begin+7129
	.data.b	206,6
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+1175

	.data.b	71
	.data.b	210,6
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7147
	.data.b	84,82,65,78,83,73,90,69,0
	.section	.debug_info		;off: 10366
	.data.w	.Ldw_str_begin+7147
	.data.b	211,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7156
	.data.b	83,66,83,73,90,69,0
	.section	.debug_info		;off: 10386
	.data.w	.Ldw_str_begin+7156
	.data.b	212,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	17
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7163
	.data.b	68,66,83,73,90,69,0
	.section	.debug_info		;off: 10406
	.data.w	.Ldw_str_begin+7163
	.data.b	213,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	14
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7170
	.data.b	83,87,73,68,84,72,0
	.section	.debug_info		;off: 10426
	.data.w	.Ldw_str_begin+7170
	.data.b	214,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	11
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7177
	.data.b	68,87,73,68,84,72,0
	.section	.debug_info		;off: 10446
	.data.w	.Ldw_str_begin+7177
	.data.b	215,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	8
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7184
	.data.b	83,0
	.section	.debug_info		;off: 10466
	.data.w	.Ldw_str_begin+7184
	.data.b	216,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7186
	.data.b	68,0
	.section	.debug_info		;off: 10486
	.data.w	.Ldw_str_begin+7186
	.data.b	217,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7188
	.data.b	83,73,0
	.section	.debug_info		;off: 10506
	.data.w	.Ldw_str_begin+7188
	.data.b	218,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7191
	.data.b	68,73,0
	.section	.debug_info		;off: 10526
	.data.w	.Ldw_str_begin+7191
	.data.b	219,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7194
	.data.b	65,77,0
	.section	.debug_info		;off: 10546
	.data.w	.Ldw_str_begin+7194
	.data.b	220,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7197
	.data.b	66,69,0
	.section	.debug_info		;off: 10566
	.data.w	.Ldw_str_begin+7197
	.data.b	221,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7200
	.data.b	67,69,0
	.section	.debug_info		;off: 10586
	.data.w	.Ldw_str_begin+7200
	.data.b	222,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7203
	.data.b	73,0
	.section	.debug_info		;off: 10606
	.data.w	.Ldw_str_begin+7203
	.data.b	223,6
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7205
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,95,66,105,116,115,0
	.section	.debug_info		;off: 10627
	.data.w	.Ldw_str_begin+7205
	.data.b	224,6
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+1180

	.data.b	71
	.data.b	207,8
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7225
	.data.b	67,82,67,86,65,76,0
	.section	.debug_info		;off: 10647
	.data.w	.Ldw_str_begin+7225
	.data.b	208,8
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 7232
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 10667
	.data.w	.Ldw_str_begin+7232
	.data.b	209,8
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+1014
	.data.b	4
	.data.b	0
	.data.b	24
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7243
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,95,66,105,116,115,0
	.section	.debug_info		;off: 10688
	.data.w	.Ldw_str_begin+7243
	.data.b	210,8
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+1185

	.data.b	73
	.data.b	227,10
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7265
	.data.b	85,0
	.section	.debug_info		;off: 10708
	.data.w	.Ldw_str_begin+7265
	.data.b	228,10
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7267
	.data.b	66,0
	.section	.debug_info		;off: 10725
	.data.w	.Ldw_str_begin+7267
	.data.b	229,10
	.data.b	25
	.data.b	42
	.data.w	.Ldw_begin+10223
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7269
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 10743
	.data.w	.Ldw_str_begin+7269
	.data.b	230,10
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+10700

	.data.b	73
	.data.b	235,10
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7284
	.data.b	85,0
	.section	.debug_info		;off: 10763
	.data.w	.Ldw_str_begin+7284
	.data.b	236,10
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7286
	.data.b	66,0
	.section	.debug_info		;off: 10780
	.data.w	.Ldw_str_begin+7286
	.data.b	237,10
	.data.b	26
	.data.b	42
	.data.w	.Ldw_begin+10264
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7288
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 10798
	.data.w	.Ldw_str_begin+7288
	.data.b	238,10
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+10755

	.data.b	73
	.data.b	243,10
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7304
	.data.b	85,0
	.section	.debug_info		;off: 10818
	.data.w	.Ldw_str_begin+7304
	.data.b	244,10
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7306
	.data.b	66,0
	.section	.debug_info		;off: 10835
	.data.w	.Ldw_str_begin+7306
	.data.b	245,10
	.data.b	23
	.data.b	42
	.data.w	.Ldw_begin+10345
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7308
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,0
	.section	.debug_info		;off: 10853
	.data.w	.Ldw_str_begin+7308
	.data.b	246,10
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+10810

	.data.b	73
	.data.b	251,10
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7322
	.data.b	85,0
	.section	.debug_info		;off: 10873
	.data.w	.Ldw_str_begin+7322
	.data.b	252,10
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7324
	.data.b	66,0
	.section	.debug_info		;off: 10890
	.data.w	.Ldw_str_begin+7324
	.data.b	253,10
	.data.b	25
	.data.b	42
	.data.w	.Ldw_begin+10626
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7326
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,0
	.section	.debug_info		;off: 10908
	.data.w	.Ldw_str_begin+7326
	.data.b	254,10
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+10865

	.data.b	73
	.data.b	195,12
	.data.b	1
	.data.b	42
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7341
	.data.b	85,0
	.section	.debug_info		;off: 10928
	.data.w	.Ldw_str_begin+7341
	.data.b	196,12
	.data.b	12
	.data.b	42
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 7343
	.data.b	66,0
	.section	.debug_info		;off: 10945
	.data.w	.Ldw_str_begin+7343
	.data.b	197,12
	.data.b	27
	.data.b	42
	.data.w	.Ldw_begin+10687
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7345
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,0
	.section	.debug_info		;off: 10963
	.data.w	.Ldw_str_begin+7345
	.data.b	198,12
	.data.b	3
	.data.b	42
	.data.w	.Ldw_begin+10920

	.data.b	52
	.section	.debug_str		;off: 7362
	.data.b	0
	.section	.debug_info		;off: 10976
	.data.w	.Ldw_str_begin+7362
	.data.b	81
	.data.b	1
	.data.b	41
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7363
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,78,79,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 10986
	.data.w	.Ldw_str_begin+7363
	.data.b	82
	.data.b	5
	.data.b	41
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7403
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 10995
	.data.w	.Ldw_str_begin+7403
	.data.b	83
	.data.b	5
	.data.b	41
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7440
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,73,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 11005
	.data.w	.Ldw_str_begin+7440
	.data.b	84
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+10975

	.data.b	52
	.section	.debug_str		;off: 7468
	.data.b	0
	.section	.debug_info		;off: 11017
	.data.w	.Ldw_str_begin+7468
	.data.b	88
	.data.b	1
	.data.b	41
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7469
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,56,66,73,84,0
	.section	.debug_info		;off: 11027
	.data.w	.Ldw_str_begin+7469
	.data.b	89
	.data.b	5
	.data.b	41
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7499
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,54,66,73,84,0
	.section	.debug_info		;off: 11036
	.data.w	.Ldw_str_begin+7499
	.data.b	90
	.data.b	5
	.data.b	41
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7530
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,51,50,66,73,84,0
	.section	.debug_info		;off: 11045
	.data.w	.Ldw_str_begin+7530
	.data.b	91
	.data.b	5
	.data.b	41
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7561
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,54,52,66,73,84,0
	.section	.debug_info		;off: 11054
	.data.w	.Ldw_str_begin+7561
	.data.b	92
	.data.b	5
	.data.b	41
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7592
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,50,56,66,73,84,0
	.section	.debug_info		;off: 11063
	.data.w	.Ldw_str_begin+7592
	.data.b	93
	.data.b	5
	.data.b	41
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7624
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 11073
	.data.w	.Ldw_str_begin+7624
	.data.b	94
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11016

	.data.b	52
	.section	.debug_str		;off: 7649
	.data.b	0
	.section	.debug_info		;off: 11085
	.data.w	.Ldw_str_begin+7649
	.data.b	98
	.data.b	1
	.data.b	41
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7650
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,0
	.section	.debug_info		;off: 11095
	.data.w	.Ldw_str_begin+7650
	.data.b	99
	.data.b	5
	.data.b	41
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7673
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,52,0
	.section	.debug_info		;off: 11104
	.data.w	.Ldw_str_begin+7673
	.data.b	100
	.data.b	5
	.data.b	41
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7696
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,56,0
	.section	.debug_info		;off: 11113
	.data.w	.Ldw_str_begin+7696
	.data.b	101
	.data.b	5
	.data.b	41
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7719
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,54,0
	.section	.debug_info		;off: 11122
	.data.w	.Ldw_str_begin+7719
	.data.b	102
	.data.b	5
	.data.b	41
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7743
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,51,50,0
	.section	.debug_info		;off: 11131
	.data.w	.Ldw_str_begin+7743
	.data.b	103
	.data.b	5
	.data.b	41
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7767
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,54,52,0
	.section	.debug_info		;off: 11140
	.data.w	.Ldw_str_begin+7767
	.data.b	104
	.data.b	5
	.data.b	41
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 7791
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,50,56,0
	.section	.debug_info		;off: 11149
	.data.w	.Ldw_str_begin+7791
	.data.b	105
	.data.b	5
	.data.b	41
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 7816
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,50,53,54,0
	.section	.debug_info		;off: 11158
	.data.w	.Ldw_str_begin+7816
	.data.b	106
	.data.b	5
	.data.b	41
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7841
	.data.b	68,109,97,95,67,104,97,110,110,101,108,66,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 11168
	.data.w	.Ldw_str_begin+7841
	.data.b	107
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11084

	.data.b	52
	.section	.debug_str		;off: 7862
	.data.b	0
	.section	.debug_info		;off: 11180
	.data.w	.Ldw_str_begin+7862
	.data.b	176,1
	.data.b	1
	.data.b	41
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7863
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,78,79,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 11191
	.data.w	.Ldw_str_begin+7863
	.data.b	177,1
	.data.b	5
	.data.b	41
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7902
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,48,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 11201
	.data.w	.Ldw_str_begin+7902
	.data.b	178,1
	.data.b	5
	.data.b	41
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7946
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,49,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 11211
	.data.w	.Ldw_str_begin+7946
	.data.b	179,1
	.data.b	5
	.data.b	41
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7990
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,48,70,73,82,83,84,0
	.section	.debug_info		;off: 11221
	.data.w	.Ldw_str_begin+7990
	.data.b	180,1
	.data.b	5
	.data.b	41
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 8044
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,49,70,73,82,83,84,0
	.section	.debug_info		;off: 11231
	.data.w	.Ldw_str_begin+8044
	.data.b	181,1
	.data.b	5
	.data.b	41
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8098
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,70,114,111,122,101,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 11242
	.data.w	.Ldw_str_begin+8098
	.data.b	182,1
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11179

	.data.b	71
	.data.b	253,1
	.data.b	1
	.data.b	41
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8127
	.data.b	97,100,100,114,101,115,115,0
	.section	.debug_info		;off: 11262
	.data.w	.Ldw_str_begin+8127
	.data.b	254,1
	.data.b	12
	.data.b	41
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8135
	.data.b	105,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 11279
	.data.w	.Ldw_str_begin+8135
	.data.b	255,1
	.data.b	33
	.data.b	41
	.data.w	.Ldw_begin+11004
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8145
	.data.b	98,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 11296
	.data.w	.Ldw_str_begin+8145
	.data.b	128,2
	.data.b	26
	.data.b	41
	.data.w	.Ldw_begin+11167
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8155
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 11314
	.data.w	.Ldw_str_begin+8155
	.data.b	129,2
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11254

	.data.b	71
	.data.b	161,2
	.data.b	1
	.data.b	41
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8180
	.data.b	115,111,117,114,99,101,0
	.section	.debug_info		;off: 11334
	.data.w	.Ldw_str_begin+8180
	.data.b	162,2
	.data.b	30
	.data.b	41
	.data.w	.Ldw_begin+11313
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8187
	.data.b	100,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 11351
	.data.w	.Ldw_str_begin+8187
	.data.b	163,2
	.data.b	30
	.data.b	41
	.data.w	.Ldw_begin+11313
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8199
	.data.b	116,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 11368
	.data.w	.Ldw_str_begin+8199
	.data.b	164,2
	.data.b	30
	.data.b	41
	.data.w	.Ldw_begin+11072
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8213
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 11385
	.data.w	.Ldw_str_begin+8213
	.data.b	165,2
	.data.b	12
	.data.b	41
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8235
	.data.b	116,114,97,110,115,102,101,114,83,105,122,101,0
	.section	.debug_info		;off: 11402
	.data.w	.Ldw_str_begin+8235
	.data.b	166,2
	.data.b	12
	.data.b	41
	.data.w	.Ldw_begin+2134
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8248
	.data.b	116,101,114,109,105,110,97,67,111,117,110,116,73,110,116,101,114,69,110,0
	.section	.debug_info		;off: 11419
	.data.w	.Ldw_str_begin+8248
	.data.b	167,2
	.data.b	13
	.data.b	41
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	34
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8268
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,73,116,101,109,67,111,110,102,105,103,0
	.section	.debug_info		;off: 11437
	.data.w	.Ldw_str_begin+8268
	.data.b	169,2
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11326

	.data.b	71
	.data.b	218,2
	.data.b	1
	.data.b	41
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8293
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 11457
	.data.w	.Ldw_str_begin+8293
	.data.b	219,2
	.data.b	20
	.data.b	41
	.data.w	.Ldw_begin+10742
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8315
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,68,101,115,116,65,100,100,114,0
	.section	.debug_info		;off: 11474
	.data.w	.Ldw_str_begin+8315
	.data.b	220,2
	.data.b	21
	.data.b	41
	.data.w	.Ldw_begin+10797
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8338
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,76,108,105,82,101,103,0
	.section	.debug_info		;off: 11491
	.data.w	.Ldw_str_begin+8338
	.data.b	221,2
	.data.b	19
	.data.b	41
	.data.w	.Ldw_begin+10852
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8359
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,116,114,108,0
	.section	.debug_info		;off: 11508
	.data.w	.Ldw_str_begin+8359
	.data.b	222,2
	.data.b	20
	.data.b	41
	.data.w	.Ldw_begin+10907
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8378
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,82,67,0
	.section	.debug_info		;off: 11525
	.data.w	.Ldw_str_begin+8378
	.data.b	223,2
	.data.b	22
	.data.b	41
	.data.w	.Ldw_begin+10962
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8396
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,73,116,101,109,0
	.section	.debug_info		;off: 11543
	.data.w	.Ldw_str_begin+8396
	.data.b	224,2
	.data.b	3
	.data.b	41
	.data.w	.Ldw_begin+11449

	.data.b	45
	.section	.debug_str		;off: 8415
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 11556
	.data.w	.Ldw_str_begin+8415
	.data.b	50
	.data.b	46
	.data.b	39
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8431
	.data.b	68,109,97,95,76,108,105,66,117,102,84,121,112,101,0
	.section	.debug_info		;off: 11568
	.data.w	.Ldw_str_begin+8431
	.data.b	75
	.data.b	46
	.data.b	39
	.data.w	.Ldw_begin+11542

	.data.b	45
	.section	.debug_str		;off: 8446
	.data.b	68,109,97,95,76,108,105,67,102,103,84,121,112,101,0
	.section	.debug_info		;off: 11580
	.data.w	.Ldw_str_begin+8446
	.data.b	77
	.data.b	46
	.data.b	39
	.data.w	.Ldw_begin+11436

	.data.b	52
	.section	.debug_str		;off: 8461
	.data.b	0
	.section	.debug_info		;off: 11592
	.data.w	.Ldw_str_begin+8461
	.data.b	103
	.data.b	1
	.data.b	39
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8462
	.data.b	68,77,65,95,67,72,95,73,78,84,95,84,67,0
	.section	.debug_info		;off: 11602
	.data.w	.Ldw_str_begin+8462
	.data.b	105
	.data.b	5
	.data.b	39
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8476
	.data.b	68,77,65,95,67,72,95,73,78,84,95,69,82,82,79,82,0
	.section	.debug_info		;off: 11611
	.data.w	.Ldw_str_begin+8476
	.data.b	107
	.data.b	6
	.data.b	39
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8493
	.data.b	68,77,65,95,67,72,95,73,78,84,95,80,65,84,84,69,82,78,0
	.section	.debug_info		;off: 11620
	.data.w	.Ldw_str_begin+8493
	.data.b	119
	.data.b	6
	.data.b	39
	.data.b	16

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8512
	.data.b	68,109,97,95,67,104,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 11630
	.data.w	.Ldw_str_begin+8512
	.data.b	126
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+11591

	.data.b	52
	.section	.debug_str		;off: 8528
	.data.b	0
	.section	.debug_info		;off: 11642
	.data.w	.Ldw_str_begin+8528
	.data.b	130,1
	.data.b	1
	.data.b	39
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8529
	.data.b	68,77,65,95,67,72,95,78,79,78,69,0
	.section	.debug_info		;off: 11653
	.data.w	.Ldw_str_begin+8529
	.data.b	132,1
	.data.b	5
	.data.b	39
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8541
	.data.b	68,77,65,95,67,72,95,84,82,65,78,83,70,69,82,95,67,79,77,80,76,69,84,69,0
	.section	.debug_info		;off: 11663
	.data.w	.Ldw_str_begin+8541
	.data.b	134,1
	.data.b	5
	.data.b	39
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8566
	.data.b	68,77,65,95,67,72,95,69,82,82,79,82,0
	.section	.debug_info		;off: 11673
	.data.w	.Ldw_str_begin+8566
	.data.b	136,1
	.data.b	5
	.data.b	39
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8579
	.data.b	68,77,65,95,67,72,95,83,67,66,0
	.section	.debug_info		;off: 11683
	.data.w	.Ldw_str_begin+8579
	.data.b	139,1
	.data.b	5
	.data.b	39
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 8590
	.data.b	68,77,65,95,67,72,95,68,67,66,0
	.section	.debug_info		;off: 11693
	.data.w	.Ldw_str_begin+8590
	.data.b	141,1
	.data.b	5
	.data.b	39
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 8601
	.data.b	68,77,65,95,67,72,95,80,65,84,84,69,82,78,95,77,65,84,67,72,69,68,0
	.section	.debug_info		;off: 11703
	.data.w	.Ldw_str_begin+8601
	.data.b	145,1
	.data.b	5
	.data.b	39
	.data.b	16

	.data.b	51
	.section	.debug_str		;off: 8624
	.data.b	68,77,65,95,67,72,95,84,82,65,78,83,70,69,82,82,73,78,71,0
	.section	.debug_info		;off: 11713
	.data.w	.Ldw_str_begin+8624
	.data.b	148,1
	.data.b	5
	.data.b	39
	.data.b	192,0

	.data.b	51
	.section	.debug_str		;off: 8644
	.data.b	68,77,65,95,67,72,95,83,85,83,80,69,78,68,69,68,0
	.section	.debug_info		;off: 11724
	.data.w	.Ldw_str_begin+8644
	.data.b	150,1
	.data.b	5
	.data.b	39
	.data.b	128,1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8661
	.data.b	68,109,97,95,67,104,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 11736
	.data.w	.Ldw_str_begin+8661
	.data.b	151,1
	.data.b	3
	.data.b	39
	.data.w	.Ldw_begin+11641

	.data.b	45
	.section	.debug_str		;off: 8678
	.data.b	83,112,105,95,68,97,116,97,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 11749
	.data.w	.Ldw_str_begin+8678
	.data.b	55
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8697
	.data.b	83,112,105,95,78,117,109,98,101,114,79,102,68,97,116,97,84,121,112,101,0
	.section	.debug_info		;off: 11761
	.data.w	.Ldw_str_begin+8697
	.data.b	63
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2134

	.data.b	45
	.section	.debug_str		;off: 8718
	.data.b	83,112,105,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 11773
	.data.w	.Ldw_str_begin+8718
	.data.b	72
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8734
	.data.b	83,112,105,95,74,111,98,84,121,112,101,0
	.section	.debug_info		;off: 11785
	.data.w	.Ldw_str_begin+8734
	.data.b	81
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2134

	.data.b	45
	.section	.debug_str		;off: 8746
	.data.b	83,112,105,95,83,101,113,117,101,110,99,101,84,121,112,101,0
	.section	.debug_info		;off: 11797
	.data.w	.Ldw_str_begin+8746
	.data.b	90
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8763
	.data.b	83,112,105,95,72,87,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 11809
	.data.w	.Ldw_str_begin+8763
	.data.b	101
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8778
	.data.b	83,112,105,95,69,120,116,101,114,110,97,108,68,101,118,105,99,101,84,121,112,101,0
	.section	.debug_info		;off: 11821
	.data.w	.Ldw_str_begin+8778
	.data.b	104
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+2122

	.data.b	45
	.section	.debug_str		;off: 8801
	.data.b	83,112,105,95,69,120,116,101,114,110,97,108,68,101,118,105,99,101,67,111,110,102,105,103,80,97,114,97,109,84,121,112,101,0
	.section	.debug_info		;off: 11833
	.data.w	.Ldw_str_begin+8801
	.data.b	107
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+10076

	.data.b	45
	.section	.debug_str		;off: 8835
	.data.b	83,112,105,95,80,104,121,85,110,105,116,67,111,110,102,105,103,80,97,114,97,109,84,121,112,101,0
	.section	.debug_info		;off: 11845
	.data.w	.Ldw_str_begin+8835
	.data.b	110
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+9936

	.data.b	45
	.section	.debug_str		;off: 8862
	.data.b	83,112,105,95,67,104,97,110,110,101,108,68,121,110,97,109,105,99,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 11857
	.data.w	.Ldw_str_begin+8862
	.data.b	113
	.data.b	39
	.data.b	5
	.data.w	.Ldw_begin+10182

	.data.b	52
	.section	.debug_str		;off: 8891
	.data.b	0
	.section	.debug_info		;off: 11869
	.data.w	.Ldw_str_begin+8891
	.data.b	128,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8892
	.data.b	83,80,73,95,85,78,73,78,73,84,0
	.section	.debug_info		;off: 11880
	.data.w	.Ldw_str_begin+8892
	.data.b	129,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8903
	.data.b	83,80,73,95,73,68,76,69,0
	.section	.debug_info		;off: 11890
	.data.w	.Ldw_str_begin+8903
	.data.b	130,1
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8912
	.data.b	83,80,73,95,66,85,83,89,0
	.section	.debug_info		;off: 11900
	.data.w	.Ldw_str_begin+8912
	.data.b	131,1
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8921
	.data.b	83,112,105,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 11911
	.data.w	.Ldw_str_begin+8921
	.data.b	132,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+11868

	.data.b	52
	.section	.debug_str		;off: 8936
	.data.b	0
	.section	.debug_info		;off: 11924
	.data.w	.Ldw_str_begin+8936
	.data.b	144,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8937
	.data.b	83,80,73,95,74,79,66,95,79,75,0
	.section	.debug_info		;off: 11935
	.data.w	.Ldw_str_begin+8937
	.data.b	145,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8948
	.data.b	83,80,73,95,74,79,66,95,80,69,78,68,73,78,71,0
	.section	.debug_info		;off: 11945
	.data.w	.Ldw_str_begin+8948
	.data.b	146,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8964
	.data.b	83,80,73,95,74,79,66,95,70,65,73,76,69,68,0
	.section	.debug_info		;off: 11955
	.data.w	.Ldw_str_begin+8964
	.data.b	147,1
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8979
	.data.b	83,80,73,95,74,79,66,95,81,85,69,85,69,68,0
	.section	.debug_info		;off: 11965
	.data.w	.Ldw_str_begin+8979
	.data.b	148,1
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8994
	.data.b	83,112,105,95,74,111,98,82,101,115,117,108,116,84,121,112,101,0
	.section	.debug_info		;off: 11976
	.data.w	.Ldw_str_begin+8994
	.data.b	150,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+11923

	.data.b	52
	.section	.debug_str		;off: 9012
	.data.b	0
	.section	.debug_info		;off: 11989
	.data.w	.Ldw_str_begin+9012
	.data.b	170,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9013
	.data.b	83,80,73,95,83,69,81,95,79,75,0
	.section	.debug_info		;off: 12000
	.data.w	.Ldw_str_begin+9013
	.data.b	171,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9024
	.data.b	83,80,73,95,83,69,81,95,80,69,78,68,73,78,71,0
	.section	.debug_info		;off: 12010
	.data.w	.Ldw_str_begin+9024
	.data.b	172,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9040
	.data.b	83,80,73,95,83,69,81,95,70,65,73,76,69,68,0
	.section	.debug_info		;off: 12020
	.data.w	.Ldw_str_begin+9040
	.data.b	173,1
	.data.b	5
	.data.b	5
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 9055
	.data.b	83,80,73,95,83,69,81,95,67,65,78,67,69,76,76,69,68,0
	.section	.debug_info		;off: 12030
	.data.w	.Ldw_str_begin+9055
	.data.b	174,1
	.data.b	5
	.data.b	5
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9073
	.data.b	83,112,105,95,83,101,113,82,101,115,117,108,116,84,121,112,101,0
	.section	.debug_info		;off: 12041
	.data.w	.Ldw_str_begin+9073
	.data.b	176,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+11988

	.data.b	52
	.section	.debug_str		;off: 9091
	.data.b	0
	.section	.debug_info		;off: 12054
	.data.w	.Ldw_str_begin+9091
	.data.b	203,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9092
	.data.b	83,80,73,95,80,79,76,76,73,78,71,95,77,79,68,69,0
	.section	.debug_info		;off: 12065
	.data.w	.Ldw_str_begin+9092
	.data.b	204,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9109
	.data.b	83,80,73,95,73,78,84,69,82,82,85,80,84,95,77,79,68,69,0
	.section	.debug_info		;off: 12075
	.data.w	.Ldw_str_begin+9109
	.data.b	205,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9128
	.data.b	83,112,105,95,65,115,121,110,99,77,111,100,101,84,121,112,101,0
	.section	.debug_info		;off: 12086
	.data.w	.Ldw_str_begin+9128
	.data.b	206,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12053

	.data.b	52
	.section	.debug_str		;off: 9146
	.data.b	0
	.section	.debug_info		;off: 12099
	.data.w	.Ldw_str_begin+9146
	.data.b	218,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9147
	.data.b	83,80,73,95,73,66,0
	.section	.debug_info		;off: 12110
	.data.w	.Ldw_str_begin+9147
	.data.b	219,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9154
	.data.b	83,80,73,95,69,66,0
	.section	.debug_info		;off: 12120
	.data.w	.Ldw_str_begin+9154
	.data.b	220,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9161
	.data.b	83,112,105,95,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 12131
	.data.w	.Ldw_str_begin+9161
	.data.b	221,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12098

	.data.b	52
	.section	.debug_str		;off: 9176
	.data.b	0
	.section	.debug_info		;off: 12144
	.data.w	.Ldw_str_begin+9176
	.data.b	228,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9177
	.data.b	83,80,73,95,67,83,95,86,73,65,95,71,80,73,79,0
	.section	.debug_info		;off: 12155
	.data.w	.Ldw_str_begin+9177
	.data.b	229,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9193
	.data.b	83,80,73,95,67,83,95,86,73,65,95,80,69,82,73,80,72,69,82,65,76,95,69,78,71,73,78,69,0
	.section	.debug_info		;off: 12165
	.data.w	.Ldw_str_begin+9193
	.data.b	230,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9222
	.data.b	83,112,105,95,67,115,83,101,108,101,99,116,105,111,110,84,121,112,101,0
	.section	.debug_info		;off: 12176
	.data.w	.Ldw_str_begin+9222
	.data.b	231,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12143

	.data.b	52
	.section	.debug_str		;off: 9242
	.data.b	0
	.section	.debug_info		;off: 12189
	.data.w	.Ldw_str_begin+9242
	.data.b	236,1
	.data.b	1
	.data.b	5
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9243
	.data.b	83,80,73,95,85,78,73,78,73,84,73,65,76,73,90,69,0
	.section	.debug_info		;off: 12200
	.data.w	.Ldw_str_begin+9243
	.data.b	237,1
	.data.b	5
	.data.b	5
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9260
	.data.b	83,80,73,95,73,78,73,84,73,65,76,73,90,69,68,0
	.section	.debug_info		;off: 12210
	.data.w	.Ldw_str_begin+9260
	.data.b	238,1
	.data.b	5
	.data.b	5
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9276
	.data.b	83,112,105,95,68,114,105,118,101,114,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 12221
	.data.w	.Ldw_str_begin+9276
	.data.b	239,1
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12188

	.data.b	71
	.data.b	252,1
	.data.b	1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9296
	.data.b	67,104,68,101,102,97,117,108,116,68,97,116,97,0
	.section	.debug_info		;off: 12241
	.data.w	.Ldw_str_begin+9296
	.data.b	254,1
	.data.b	31
	.data.b	5
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9310
	.data.b	84,88,66,117,102,102,80,116,114,0
	.section	.debug_info		;off: 12258
	.data.w	.Ldw_str_begin+9310
	.data.b	128,2
	.data.b	31
	.data.b	5
	.data.w	.Ldw_begin+829
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9320
	.data.b	82,88,66,117,102,102,80,116,114,0
	.section	.debug_info		;off: 12275
	.data.w	.Ldw_str_begin+9320
	.data.b	130,2
	.data.b	31
	.data.b	5
	.data.w	.Ldw_begin+829
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9330
	.data.b	83,112,105,95,66,117,102,102,101,114,68,101,115,99,114,105,112,116,111,114,84,121,112,101,0
	.section	.debug_info		;off: 12293
	.data.w	.Ldw_str_begin+9330
	.data.b	131,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12233

	.data.b	71
	.data.b	143,2
	.data.b	1
	.data.b	5
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9355
	.data.b	83,101,113,117,101,110,99,101,73,100,0
	.section	.debug_info		;off: 12313
	.data.w	.Ldw_str_begin+9355
	.data.b	145,2
	.data.b	24
	.data.b	5
	.data.w	.Ldw_begin+11796
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9366
	.data.b	73,110,116,101,114,114,117,112,116,105,98,108,101,0
	.section	.debug_info		;off: 12330
	.data.w	.Ldw_str_begin+9366
	.data.b	147,2
	.data.b	24
	.data.b	5
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9380
	.data.b	78,117,109,74,111,98,115,0
	.section	.debug_info		;off: 12347
	.data.w	.Ldw_str_begin+9380
	.data.b	149,2
	.data.b	24
	.data.b	5
	.data.w	.Ldw_begin+11784
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9388
	.data.b	74,111,98,73,110,100,101,120,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 12364
	.data.w	.Ldw_str_begin+9388
	.data.b	151,2
	.data.b	25
	.data.b	5
	.data.w	.Ldw_begin+339
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9404
	.data.b	77,97,115,107,83,101,113,85,115,101,100,80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 12381
	.data.w	.Ldw_str_begin+9404
	.data.b	153,2
	.data.b	24
	.data.b	5
	.data.w	.Ldw_begin+2134
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9423
	.data.b	83,101,113,69,110,100,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 12398
	.data.w	.Ldw_str_begin+9423
	.data.b	162,2
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+1208
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9445
	.data.b	83,112,105,95,83,101,113,117,101,110,99,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 12416
	.data.w	.Ldw_str_begin+9445
	.data.b	163,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12305

	.data.b	71
	.data.b	183,2
	.data.b	1
	.data.b	5
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9468
	.data.b	83,112,105,78,117,109,98,101,114,0
	.section	.debug_info		;off: 12436
	.data.w	.Ldw_str_begin+9468
	.data.b	185,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+11808
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9478
	.data.b	67,115,83,101,108,101,99,116,105,111,110,0
	.section	.debug_info		;off: 12453
	.data.w	.Ldw_str_begin+9478
	.data.b	187,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+12175
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9490
	.data.b	71,112,105,111,80,111,114,116,80,105,110,0
	.section	.debug_info		;off: 12470
	.data.w	.Ldw_str_begin+9490
	.data.b	189,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+2134
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9502
	.data.b	80,97,114,105,116,121,83,101,108,101,99,116,105,111,110,0
	.section	.debug_info		;off: 12487
	.data.w	.Ldw_str_begin+9502
	.data.b	191,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+8257
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9518
	.data.b	68,101,108,97,121,80,97,114,97,109,0
	.section	.debug_info		;off: 12504
	.data.w	.Ldw_str_begin+9518
	.data.b	193,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+9762
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9529
	.data.b	83,112,105,95,69,120,68,101,118,105,99,101,67,102,103,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 12521
	.data.w	.Ldw_str_begin+9529
	.data.b	195,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+1218
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9552
	.data.b	83,112,105,95,69,120,116,101,114,110,97,108,68,101,118,105,99,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 12539
	.data.w	.Ldw_str_begin+9552
	.data.b	196,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12428

	.data.b	71
	.data.b	201,2
	.data.b	1
	.data.b	5
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9581
	.data.b	83,112,105,78,117,109,98,101,114,0
	.section	.debug_info		;off: 12559
	.data.w	.Ldw_str_begin+9581
	.data.b	203,2
	.data.b	45
	.data.b	5
	.data.w	.Ldw_begin+11808
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9591
	.data.b	84,120,68,109,97,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 12576
	.data.w	.Ldw_str_begin+9591
	.data.b	207,2
	.data.b	45
	.data.b	5
	.data.w	.Ldw_begin+11555
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9604
	.data.b	82,120,68,109,97,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 12593
	.data.w	.Ldw_str_begin+9604
	.data.b	209,2
	.data.b	45
	.data.b	5
	.data.w	.Ldw_begin+11555
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9617
	.data.b	67,104,68,121,110,97,109,105,99,67,102,103,80,116,114,0
	.section	.debug_info		;off: 12610
	.data.w	.Ldw_str_begin+9617
	.data.b	213,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+1223
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9633
	.data.b	68,109,97,84,99,115,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 12627
	.data.w	.Ldw_str_begin+9633
	.data.b	215,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+1195
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9649
	.data.b	83,112,105,95,80,104,121,85,110,105,116,67,111,110,102,105,103,80,97,114,97,109,80,116,114,0
	.section	.debug_info		;off: 12644
	.data.w	.Ldw_str_begin+9649
	.data.b	218,2
	.data.b	46
	.data.b	5
	.data.w	.Ldw_begin+1233
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9675
	.data.b	83,112,105,95,80,104,121,85,110,105,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 12662
	.data.w	.Ldw_str_begin+9675
	.data.b	219,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12551

	.data.b	71
	.data.b	224,2
	.data.b	1
	.data.b	5
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9697
	.data.b	83,101,113,82,101,115,117,108,116,0
	.section	.debug_info		;off: 12682
	.data.w	.Ldw_str_begin+9697
	.data.b	226,2
	.data.b	35
	.data.b	5
	.data.w	.Ldw_begin+12040
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9707
	.data.b	83,101,113,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 12699
	.data.w	.Ldw_str_begin+9707
	.data.b	229,2
	.data.b	35
	.data.b	5
	.data.w	.Ldw_begin+349
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9720
	.data.b	67,117,114,74,111,98,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 12716
	.data.w	.Ldw_str_begin+9720
	.data.b	231,2
	.data.b	35
	.data.b	5
	.data.w	.Ldw_begin+339
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9735
	.data.b	82,101,109,97,105,110,105,110,103,74,111,98,115,0
	.section	.debug_info		;off: 12733
	.data.w	.Ldw_str_begin+9735
	.data.b	233,2
	.data.b	35
	.data.b	5
	.data.w	.Ldw_begin+11784
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9749
	.data.b	83,112,105,95,83,101,113,117,101,110,99,101,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 12751
	.data.w	.Ldw_str_begin+9749
	.data.b	235,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12674

	.data.b	71
	.data.b	240,2
	.data.b	1
	.data.b	5
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9771
	.data.b	74,111,98,82,101,115,117,108,116,0
	.section	.debug_info		;off: 12771
	.data.w	.Ldw_str_begin+9771
	.data.b	242,2
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11975
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9781
	.data.b	65,115,121,110,99,83,101,113,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 12788
	.data.w	.Ldw_str_begin+9781
	.data.b	245,2
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+607
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9798
	.data.b	65,115,121,110,99,78,101,120,116,74,111,98,0
	.section	.debug_info		;off: 12805
	.data.w	.Ldw_str_begin+9798
	.data.b	247,2
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11784
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9811
	.data.b	83,112,105,95,74,111,98,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 12823
	.data.w	.Ldw_str_begin+9811
	.data.b	249,2
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12763

	.data.b	71
	.data.b	135,3
	.data.b	1
	.data.b	5
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9828
	.data.b	76,111,103,105,99,67,104,73,100,0
	.section	.debug_info		;off: 12843
	.data.w	.Ldw_str_begin+9828
	.data.b	137,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11772
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9838
	.data.b	67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 12860
	.data.w	.Ldw_str_begin+9838
	.data.b	139,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+12130
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9850
	.data.b	68,97,116,97,70,114,97,109,101,87,105,100,116,104,0
	.section	.debug_info		;off: 12877
	.data.w	.Ldw_str_begin+9850
	.data.b	141,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+8591
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9865
	.data.b	70,114,97,109,101,87,105,100,116,104,0
	.section	.debug_info		;off: 12894
	.data.w	.Ldw_str_begin+9865
	.data.b	143,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+7823
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9876
	.data.b	68,97,116,97,76,101,110,103,116,104,0
	.section	.debug_info		;off: 12911
	.data.w	.Ldw_str_begin+9876
	.data.b	146,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11760
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9887
	.data.b	66,117,102,102,101,114,68,101,115,99,114,105,112,116,111,114,80,116,114,0
	.section	.debug_info		;off: 12928
	.data.w	.Ldw_str_begin+9887
	.data.b	148,3
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+1238
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9907
	.data.b	65,99,116,117,97,108,68,97,116,97,76,101,110,103,116,104,80,116,114,0
	.section	.debug_info		;off: 12945
	.data.w	.Ldw_str_begin+9907
	.data.b	150,3
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+1243
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9927
	.data.b	84,114,97,110,115,102,101,114,83,116,97,114,116,0
	.section	.debug_info		;off: 12962
	.data.w	.Ldw_str_begin+9927
	.data.b	152,3
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+8636
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9941
	.data.b	83,112,105,95,67,104,97,110,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 12980
	.data.w	.Ldw_str_begin+9941
	.data.b	153,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12835

	.data.b	71
	.data.b	158,3
	.data.b	1
	.data.b	5
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9963
	.data.b	74,111,98,73,100,0
	.section	.debug_info		;off: 13000
	.data.w	.Ldw_str_begin+9963
	.data.b	160,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+11784
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9969
	.data.b	83,112,105,78,117,109,98,101,114,0
	.section	.debug_info		;off: 13017
	.data.w	.Ldw_str_begin+9969
	.data.b	162,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+11808
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9979
	.data.b	80,117,108,108,67,83,98,121,68,97,116,97,0
	.section	.debug_info		;off: 13034
	.data.w	.Ldw_str_begin+9979
	.data.b	164,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9992
	.data.b	69,120,68,101,118,105,99,101,85,110,105,116,0
	.section	.debug_info		;off: 13051
	.data.w	.Ldw_str_begin+9992
	.data.b	170,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+11820
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10005
	.data.b	78,117,109,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 13068
	.data.w	.Ldw_str_begin+10005
	.data.b	172,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+11772
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10017
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 13085
	.data.w	.Ldw_str_begin+10017
	.data.b	174,3
	.data.b	30
	.data.b	5
	.data.w	.Ldw_begin+378
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10037
	.data.b	74,111,98,69,110,100,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 13102
	.data.w	.Ldw_str_begin+10037
	.data.b	183,3
	.data.b	12
	.data.b	5
	.data.w	.Ldw_begin+1251
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10059
	.data.b	80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 13119
	.data.w	.Ldw_str_begin+10059
	.data.b	185,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2122
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10068
	.data.b	74,111,98,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 13136
	.data.w	.Ldw_str_begin+10068
	.data.b	187,3
	.data.b	30
	.data.b	5
	.data.w	.Ldw_begin+1256
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10080
	.data.b	83,112,105,95,74,111,98,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 13154
	.data.w	.Ldw_str_begin+10080
	.data.b	188,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+12992

	.data.b	71
	.data.b	193,3
	.data.b	1
	.data.b	5
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10098
	.data.b	68,109,97,69,110,97,98,108,101,0
	.section	.debug_info		;off: 13174
	.data.w	.Ldw_str_begin+10098
	.data.b	196,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10108
	.data.b	73,115,65,115,121,110,99,0
	.section	.debug_info		;off: 13191
	.data.w	.Ldw_str_begin+10108
	.data.b	199,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10116
	.data.b	80,104,121,85,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 13208
	.data.w	.Ldw_str_begin+10116
	.data.b	202,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+11910
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10130
	.data.b	83,99,104,101,100,117,108,101,100,74,111,98,115,76,105,115,116,72,101,97,100,0
	.section	.debug_info		;off: 13225
	.data.w	.Ldw_str_begin+10130
	.data.b	205,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+1261
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10152
	.data.b	83,99,104,101,100,117,108,101,100,74,111,98,115,76,105,115,116,84,97,105,108,0
	.section	.debug_info		;off: 13242
	.data.w	.Ldw_str_begin+10152
	.data.b	207,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+1277
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10174
	.data.b	77,97,120,83,99,104,101,100,117,108,101,100,80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 13259
	.data.w	.Ldw_str_begin+10174
	.data.b	209,3
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+2110
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10195
	.data.b	83,112,105,95,80,104,121,85,110,105,116,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 13277
	.data.w	.Ldw_str_begin+10195
	.data.b	211,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+13166

	.data.b	71
	.data.b	216,3
	.data.b	1
	.data.b	5
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10216
	.data.b	82,101,99,101,105,118,101,100,68,97,116,97,0
	.section	.debug_info		;off: 13297
	.data.w	.Ldw_str_begin+10216
	.data.b	218,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11760
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10229
	.data.b	67,117,114,74,111,98,80,116,114,0
	.section	.debug_info		;off: 13314
	.data.w	.Ldw_str_begin+10229
	.data.b	220,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+329
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10239
	.data.b	67,117,114,84,120,66,117,102,80,116,114,0
	.section	.debug_info		;off: 13331
	.data.w	.Ldw_str_begin+10239
	.data.b	223,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+829
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10251
	.data.b	67,117,114,82,120,66,117,102,80,116,114,0
	.section	.debug_info		;off: 13348
	.data.w	.Ldw_str_begin+10251
	.data.b	225,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+829
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10263
	.data.b	67,117,114,67,104,97,110,110,101,108,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 13365
	.data.w	.Ldw_str_begin+10263
	.data.b	227,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+378
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10282
	.data.b	82,101,109,97,105,110,105,110,103,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 13382
	.data.w	.Ldw_str_begin+10282
	.data.b	229,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11772
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10300
	.data.b	82,101,109,97,105,110,105,110,103,68,97,116,97,0
	.section	.debug_info		;off: 13399
	.data.w	.Ldw_str_begin+10300
	.data.b	231,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11760
	.data.b	2,35
	.data.b	22
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10314
	.data.b	83,101,110,116,70,114,97,109,101,115,0
	.section	.debug_info		;off: 13416
	.data.w	.Ldw_str_begin+10314
	.data.b	233,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+11760
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10325
	.data.b	83,101,110,116,70,114,97,109,101,115,87,105,100,116,104,0
	.section	.debug_info		;off: 13433
	.data.w	.Ldw_str_begin+10325
	.data.b	235,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+7823
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10341
	.data.b	73,115,69,110,100,79,102,74,111,98,0
	.section	.debug_info		;off: 13450
	.data.w	.Ldw_str_begin+10341
	.data.b	237,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+2098
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10352
	.data.b	67,104,68,121,110,97,109,105,99,67,102,103,0
	.section	.debug_info		;off: 13467
	.data.w	.Ldw_str_begin+10352
	.data.b	239,3
	.data.b	33
	.data.b	5
	.data.w	.Ldw_begin+2146
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10365
	.data.b	83,112,105,95,68,101,118,105,99,101,83,116,97,116,101,84,121,112,101,0
	.section	.debug_info		;off: 13485
	.data.w	.Ldw_str_begin+10365
	.data.b	241,3
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+13289

	.data.b	71
	.data.b	244,3
	.data.b	1
	.data.b	5
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10385
	.data.b	83,101,113,117,101,110,99,101,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 13505
	.data.w	.Ldw_str_begin+10385
	.data.b	246,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+607
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10403
	.data.b	80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 13522
	.data.w	.Ldw_str_begin+10403
	.data.b	248,3
	.data.b	35
	.data.b	5
	.data.w	.Ldw_begin+558
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10420
	.data.b	68,101,118,105,99,101,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 13539
	.data.w	.Ldw_str_begin+10420
	.data.b	250,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+499
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10435
	.data.b	67,111,114,101,73,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 13556
	.data.w	.Ldw_str_begin+10435
	.data.b	253,3
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+1293
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10453
	.data.b	65,115,121,110,99,77,111,100,101,0
	.section	.debug_info		;off: 13573
	.data.w	.Ldw_str_begin+10453
	.data.b	129,4
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+1298
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10463
	.data.b	80,104,121,85,110,105,116,66,117,115,121,83,121,110,99,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 13590
	.data.w	.Ldw_str_begin+10463
	.data.b	133,4
	.data.b	34
	.data.b	5
	.data.w	.Ldw_begin+1303
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10488
	.data.b	83,112,105,95,67,111,114,101,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 13608
	.data.w	.Ldw_str_begin+10488
	.data.b	135,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+13497

	.data.b	71
	.data.b	149,4
	.data.b	1
	.data.b	5
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10507
	.data.b	77,97,120,83,101,113,0
	.section	.debug_info		;off: 13628
	.data.w	.Ldw_str_begin+10507
	.data.b	151,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11796
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10514
	.data.b	77,97,120,74,111,98,0
	.section	.debug_info		;off: 13645
	.data.w	.Ldw_str_begin+10514
	.data.b	153,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11784
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10521
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 13662
	.data.w	.Ldw_str_begin+10521
	.data.b	155,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11772
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10532
	.data.b	77,97,120,69,120,68,101,118,105,99,101,0
	.section	.debug_info		;off: 13679
	.data.w	.Ldw_str_begin+10532
	.data.b	157,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11820
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10544
	.data.b	77,97,120,80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 13696
	.data.w	.Ldw_str_begin+10544
	.data.b	159,4
	.data.b	41
	.data.b	5
	.data.w	.Ldw_begin+11808
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10555
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13713
	.data.w	.Ldw_str_begin+10555
	.data.b	161,4
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+349
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10565
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13730
	.data.w	.Ldw_str_begin+10565
	.data.b	163,4
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+329
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10575
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13747
	.data.w	.Ldw_str_begin+10575
	.data.b	165,4
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+388
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10589
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13764
	.data.w	.Ldw_str_begin+10589
	.data.b	167,4
	.data.b	42
	.data.b	5
	.data.w	.Ldw_begin+398
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10604
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 13781
	.data.w	.Ldw_str_begin+10604
	.data.b	169,4
	.data.b	43
	.data.b	5
	.data.w	.Ldw_begin+475
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10618
	.data.b	83,112,105,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 13799
	.data.w	.Ldw_str_begin+10618
	.data.b	170,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+13620

	.data.b	71
	.data.b	180,4
	.data.b	1
	.data.b	5
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10637
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 13819
	.data.w	.Ldw_str_begin+10637
	.data.b	182,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1308
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10651
	.data.b	77,97,120,83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 13836
	.data.w	.Ldw_str_begin+10651
	.data.b	184,4
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+1324
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10663
	.data.b	77,97,120,74,111,98,0
	.section	.debug_info		;off: 13853
	.data.w	.Ldw_str_begin+10663
	.data.b	186,4
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+334
	.data.b	2,35
	.data.b	18
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10670
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 13870
	.data.w	.Ldw_str_begin+10670
	.data.b	188,4
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+373
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10681
	.data.b	77,97,120,80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 13887
	.data.w	.Ldw_str_begin+10681
	.data.b	190,4
	.data.b	37
	.data.b	5
	.data.w	.Ldw_begin+1329
	.data.b	2,35
	.data.b	21
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10692
	.data.b	83,101,113,117,101,110,99,101,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 13904
	.data.w	.Ldw_str_begin+10692
	.data.b	192,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1334
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10710
	.data.b	74,111,98,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 13921
	.data.w	.Ldw_str_begin+10710
	.data.b	194,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+339
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10723
	.data.b	67,104,97,110,110,101,108,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 13938
	.data.w	.Ldw_str_begin+10723
	.data.b	196,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+378
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10740
	.data.b	69,120,68,101,118,105,99,101,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 13955
	.data.w	.Ldw_str_begin+10740
	.data.b	198,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1344
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10758
	.data.b	80,104,121,85,110,105,116,84,111,67,111,114,101,80,116,114,0
	.section	.debug_info		;off: 13972
	.data.w	.Ldw_str_begin+10758
	.data.b	200,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1349
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10775
	.data.b	68,109,97,67,104,84,111,80,104,121,85,110,105,116,80,116,114,0
	.section	.debug_info		;off: 13989
	.data.w	.Ldw_str_begin+10775
	.data.b	203,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1349
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10793
	.data.b	80,104,121,85,110,105,116,77,97,112,80,116,114,0
	.section	.debug_info		;off: 14006
	.data.w	.Ldw_str_begin+10793
	.data.b	206,4
	.data.b	38
	.data.b	5
	.data.w	.Ldw_begin+1354
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10807
	.data.b	83,112,105,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 14024
	.data.w	.Ldw_str_begin+10807
	.data.b	207,4
	.data.b	3
	.data.b	5
	.data.w	.Ldw_begin+13811

	.data.b	45
	.section	.debug_str		;off: 10822
	.data.b	68,105,111,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 14037
	.data.w	.Ldw_str_begin+10822
	.data.b	42
	.data.b	16
	.data.b	48
	.data.w	.Ldw_begin+2134

	.data.b	45
	.section	.debug_str		;off: 10838
	.data.b	68,105,111,95,76,101,118,101,108,84,121,112,101,0
	.section	.debug_info		;off: 14049
	.data.w	.Ldw_str_begin+10838
	.data.b	44
	.data.b	16
	.data.b	48
	.data.w	.Ldw_begin+2122

	.data.b	6
	.section	.debug_str		;off: 10852
	.data.b	83,112,105,95,83,101,113,117,101,110,99,101,83,116,97,116,101,67,111,114,101,48,0
	.section	.debug_info		;off: 14061
	.data.w	.Ldw_str_begin+10852
	.data.b	225,1
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1374
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_SequenceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

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

	.section	.debug_info		;off: 14081
	.data.b	6
	.section	.debug_str		;off: 10875
	.data.b	83,112,105,95,80,104,121,85,110,105,116,83,116,97,116,101,67,111,114,101,48,0
	.section	.debug_info		;off: 14082
	.data.w	.Ldw_str_begin+10875
	.data.b	226,1
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1390
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_PhyUnitStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 10897
	.data.b	83,112,105,95,68,101,118,105,99,101,83,116,97,116,101,67,111,114,101,48,0
	.section	.debug_info		;off: 14103
	.data.w	.Ldw_str_begin+10897
	.data.b	227,1
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1406
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_DeviceStateCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 10918
	.data.b	83,112,105,95,83,121,110,99,84,114,97,110,115,102,101,114,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 14124
	.data.w	.Ldw_str_begin+10918
	.data.b	232,1
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_SyncTransferStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 10946
	.data.b	83,112,105,95,73,110,105,116,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 14145
	.data.w	.Ldw_str_begin+10946
	.data.b	235,1
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+12220
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_InitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 10966
	.data.b	83,112,105,95,65,115,121,110,99,77,111,100,101,67,111,114,101,48,0
	.section	.debug_info		;off: 14166
	.data.w	.Ldw_str_begin+10966
	.data.b	132,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+12085
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_AsyncModeCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 10985
	.data.b	83,112,105,95,83,116,97,116,117,115,83,101,116,67,111,114,101,48,0
	.section	.debug_info		;off: 14187
	.data.w	.Ldw_str_begin+10985
	.data.b	143,2
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+1422
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_StatusSetCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11004
	.data.b	83,112,105,95,83,101,113,117,101,110,99,101,83,116,97,116,101,67,111,114,101,49,0
	.section	.debug_info		;off: 14208
	.data.w	.Ldw_str_begin+11004
	.data.b	175,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1427
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_SequenceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11027
	.data.b	83,112,105,95,80,104,121,85,110,105,116,83,116,97,116,101,67,111,114,101,49,0
	.section	.debug_info		;off: 14229
	.data.w	.Ldw_str_begin+11027
	.data.b	176,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1443
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_PhyUnitStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11049
	.data.b	83,112,105,95,68,101,118,105,99,101,83,116,97,116,101,67,111,114,101,49,0
	.section	.debug_info		;off: 14250
	.data.w	.Ldw_str_begin+11049
	.data.b	177,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+1459
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_DeviceStateCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11070
	.data.b	83,112,105,95,83,121,110,99,84,114,97,110,115,102,101,114,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 14271
	.data.w	.Ldw_str_begin+11070
	.data.b	182,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_SyncTransferStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11098
	.data.b	83,112,105,95,73,110,105,116,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 14292
	.data.w	.Ldw_str_begin+11098
	.data.b	185,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+12220
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_InitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11118
	.data.b	83,112,105,95,65,115,121,110,99,77,111,100,101,67,111,114,101,49,0
	.section	.debug_info		;off: 14313
	.data.w	.Ldw_str_begin+11118
	.data.b	209,2
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+12085
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_AsyncModeCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11137
	.data.b	83,112,105,95,83,116,97,116,117,115,83,101,116,67,111,114,101,49,0
	.section	.debug_info		;off: 14334
	.data.w	.Ldw_str_begin+11137
	.data.b	221,2
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+1422
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_StatusSetCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11156
	.data.b	83,112,105,95,82,120,66,117,102,102,101,114,0
	.section	.debug_info		;off: 14355
	.data.w	.Ldw_str_begin+11156
	.data.b	151,4
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_RxBuffer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11169
	.data.b	83,112,105,95,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 14376
	.data.w	.Ldw_str_begin+11169
	.data.b	153,4
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+734
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_ConfigPtr..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	6
	.section	.debug_str		;off: 11183
	.data.b	83,112,105,95,67,111,114,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14397
	.data.w	.Ldw_str_begin+11183
	.data.b	173,4
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+1485
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Spi_CoreStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.

	.data.b	27
	.section	.debug_str		;off: 11198
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 14418
	.data.w	.Ldw_str_begin+11198
	.data.b	63
	.data.b	31
	.data.b	15
	.data.w	.Ldw_begin+2349
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

	.section	.debug_info		;off: 14435
	.data.b	37

	.section	.debug_abbrev		;off: 269
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 14436
	.data.b	8
	.section	.debug_str		;off: 11218
	.data.b	105,100,0
	.section	.debug_info		;off: 14437
	.data.w	.Ldw_str_begin+11218
	.data.b	65
	.data.b	17
	.data.b	15
	.data.w	.Ldw_begin+2349
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

	.section	.debug_info		;off: 14450
	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11221
	.data.b	83,116,109,95,72,97,108,95,71,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 14453
	.data.w	.Ldw_str_begin+11221
	.data.b	94
	.data.b	26
	.data.b	25
	.data.w	.Ldw_begin+2158
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 11238
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 14472
	.data.w	.Ldw_str_begin+11238
	.data.b	109
	.data.b	21
	.data.b	25
	.data.w	.Ldw_begin+70
	.data.b	0
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 11244
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 14487
	.data.w	.Ldw_str_begin+11244
	.data.b	114
	.data.b	5
	.data.b	25
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11254
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 14501
	.data.w	.Ldw_str_begin+11254
	.data.b	114
	.data.b	5
	.data.b	25
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11264
	.data.b	82,99,99,95,72,97,108,95,71,101,116,83,116,109,67,108,107,70,114,101,113,0
	.section	.debug_info		;off: 14518
	.data.w	.Ldw_str_begin+11264
	.data.b	135,11
	.data.b	16
	.data.b	30
	.data.w	.Ldw_begin+2170
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11286
	.data.b	77,99,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 14538
	.data.w	.Ldw_str_begin+11286
	.data.b	131,2
	.data.b	48
	.data.b	6
	.data.w	.Ldw_begin+2182
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11299
	.data.b	77,99,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 14558
	.data.w	.Ldw_str_begin+11299
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

	.section	.debug_info		;off: 14572
	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11316
	.data.b	69,115,112,105,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 14574
	.data.w	.Ldw_str_begin+11316
	.data.b	222,3
	.data.b	27
	.data.b	35
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 11345
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 14593
	.data.w	.Ldw_str_begin+11345
	.data.b	222,3
	.data.b	64
	.data.b	35
	.data.w	.Ldw_begin+2098
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

	.section	.debug_info		;off: 14606
	.data.b	20
	.section	.debug_str		;off: 11351
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 14607
	.data.w	.Ldw_str_begin+11351
	.data.b	222,3
	.data.b	78
	.data.b	35
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 11357
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 14621
	.data.w	.Ldw_str_begin+11357
	.data.b	222,3
	.data.b	92
	.data.b	35
	.data.w	.Ldw_begin+2146
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 11364
	.data.b	114,101,116,0
	.section	.debug_info		;off: 14636
	.data.w	.Ldw_str_begin+11364
	.data.b	224,3
	.data.b	13
	.data.b	35
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11368
	.data.b	69,115,112,105,95,72,97,108,95,84,114,105,103,103,101,114,68,109,97,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 14653
	.data.w	.Ldw_str_begin+11368
	.data.b	239,1
	.data.b	27
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 11395
	.data.b	112,69,115,112,105,0
	.section	.debug_info		;off: 14672
	.data.w	.Ldw_str_begin+11395
	.data.b	239,1
	.data.b	73
	.data.b	34
	.data.w	.Ldw_begin+125
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 11401
	.data.b	114,101,116,0
	.section	.debug_info		;off: 14687
	.data.w	.Ldw_str_begin+11401
	.data.b	241,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11405
	.data.b	114,101,103,86,97,108,117,101,0
	.section	.debug_info		;off: 14702
	.data.w	.Ldw_str_begin+11405
	.data.b	251,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11414
	.data.b	69,115,112,105,95,77,97,115,116,101,114,95,72,97,108,95,73,110,105,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 14719
	.data.w	.Ldw_str_begin+11414
	.data.b	153,2
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11441
	.data.b	69,115,112,105,95,77,97,115,116,101,114,95,72,97,108,95,73,110,105,116,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 14739
	.data.w	.Ldw_str_begin+11441
	.data.b	172,2
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11469
	.data.b	69,115,112,105,95,72,97,108,95,67,97,108,99,117,108,97,116,101,67,104,97,110,110,101,108,68,121,110,97,109,105,99,67,111,110,102,105,103,117,114,97,116,105,111,110,0
	.section	.debug_info		;off: 14759
	.data.w	.Ldw_str_begin+11469
	.data.b	243,2
	.data.b	15
	.data.b	34
	.data.w	.Ldw_begin+2146
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11515
	.data.b	69,115,112,105,95,72,97,108,95,87,114,105,116,101,67,111,110,102,105,103,117,114,97,116,105,111,110,0
	.section	.debug_info		;off: 14779
	.data.w	.Ldw_str_begin+11515
	.data.b	134,3
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
	.section	.debug_str		;off: 11543
	.data.b	69,115,112,105,95,72,97,108,95,82,101,99,101,105,118,101,68,97,116,97,0
	.section	.debug_info		;off: 14795
	.data.w	.Ldw_str_begin+11543
	.data.b	153,3
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+2122
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11564
	.data.b	69,115,112,105,95,72,97,108,95,83,101,110,100,68,97,116,97,0
	.section	.debug_info		;off: 14815
	.data.w	.Ldw_str_begin+11564
	.data.b	172,3
	.data.b	14
	.data.b	34
	.data.w	.Ldw_begin+2122
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11582
	.data.b	69,115,112,105,95,72,97,108,95,83,101,116,70,105,102,111,76,101,118,101,108,0
	.section	.debug_info		;off: 14835
	.data.w	.Ldw_str_begin+11582
	.data.b	209,3
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11604
	.data.b	69,115,112,105,95,72,97,108,95,83,101,116,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 14855
	.data.w	.Ldw_str_begin+11604
	.data.b	132,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11626
	.data.b	69,115,112,105,95,72,97,108,95,71,101,116,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14875
	.data.w	.Ldw_str_begin+11626
	.data.b	150,4
	.data.b	15
	.data.b	34
	.data.w	.Ldw_begin+2146
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11649
	.data.b	69,115,112,105,95,72,97,108,95,67,108,101,97,114,70,108,97,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14895
	.data.w	.Ldw_str_begin+11649
	.data.b	168,4
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
	.section	.debug_str		;off: 11674
	.data.b	69,115,112,105,95,72,97,108,95,82,101,115,101,116,77,111,100,117,108,101,0
	.section	.debug_info		;off: 14911
	.data.w	.Ldw_str_begin+11674
	.data.b	183,4
	.data.b	22
	.data.b	34
	.data.w	.Ldw_begin+2541
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11695
	.data.b	69,115,112,105,95,72,97,108,95,83,101,116,77,111,118,101,67,111,117,110,116,101,114,68,97,116,97,76,101,110,103,116,104,0
	.section	.debug_info		;off: 14931
	.data.w	.Ldw_str_begin+11695
	.data.b	217,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11729
	.data.b	69,115,112,105,95,72,97,108,95,83,101,116,68,109,97,0
	.section	.debug_info		;off: 14951
	.data.w	.Ldw_str_begin+11729
	.data.b	234,4
	.data.b	16
	.data.b	34
	.data.w	.Ldw_begin+2098
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11745
	.data.b	68,109,97,95,67,104,97,110,110,101,108,83,116,97,114,116,0
	.section	.debug_info		;off: 14971
	.data.w	.Ldw_str_begin+11745
	.data.b	248,1
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
	.section	.debug_str		;off: 11762
	.data.b	68,109,97,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 14987
	.data.w	.Ldw_str_begin+11762
	.data.b	175,2
	.data.b	38
	.data.b	38
	.data.w	.Ldw_begin+2146
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11783
	.data.b	68,109,97,95,76,108,105,77,101,109,98,101,114,73,110,115,101,114,116,77,97,110,117,97,108,0
	.section	.debug_info		;off: 15007
	.data.w	.Ldw_str_begin+11783
	.data.b	188,2
	.data.b	47
	.data.b	38
	.data.w	.Ldw_begin+2182
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11809
	.data.b	68,109,97,95,76,108,105,73,110,115,101,114,116,67,111,109,112,108,101,116,101,77,97,110,117,97,108,0
	.section	.debug_info		;off: 15027
	.data.w	.Ldw_str_begin+11809
	.data.b	196,2
	.data.b	47
	.data.b	38
	.data.w	.Ldw_begin+2182
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11837
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,87,114,105,116,101,73,66,0
	.section	.debug_info		;off: 15047
	.data.w	.Ldw_str_begin+11837
	.data.b	33
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11860
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,87,114,105,116,101,73,66,0
	.section	.debug_info		;off: 15062
	.data.w	.Ldw_str_begin+11860
	.data.b	35
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11882
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,82,101,97,100,73,66,0
	.section	.debug_info		;off: 15077
	.data.w	.Ldw_str_begin+11882
	.data.b	37
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11904
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,82,101,97,100,73,66,0
	.section	.debug_info		;off: 15092
	.data.w	.Ldw_str_begin+11904
	.data.b	39
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11925
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,83,101,116,117,112,69,66,0
	.section	.debug_info		;off: 15107
	.data.w	.Ldw_str_begin+11925
	.data.b	41
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11948
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,83,101,116,117,112,69,66,0
	.section	.debug_info		;off: 15122
	.data.w	.Ldw_str_begin+11948
	.data.b	43
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11970
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,83,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 15137
	.data.w	.Ldw_str_begin+11970
	.data.b	45
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11998
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,83,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 15152
	.data.w	.Ldw_str_begin+11998
	.data.b	47
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12025
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,65,115,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 15167
	.data.w	.Ldw_str_begin+12025
	.data.b	49
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12054
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,65,115,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 15182
	.data.w	.Ldw_str_begin+12054
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

	.data.b	26
	.section	.debug_str		;off: 12082
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,83,101,116,65,115,121,110,99,77,111,100,101,0
	.section	.debug_info		;off: 15197
	.data.w	.Ldw_str_begin+12082
	.data.b	53
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12110
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,83,101,116,65,115,121,110,99,77,111,100,101,0
	.section	.debug_info		;off: 15212
	.data.w	.Ldw_str_begin+12110
	.data.b	55
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12137
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,73,115,114,69,114,114,111,114,0
	.section	.debug_info		;off: 15227
	.data.w	.Ldw_str_begin+12137
	.data.b	57
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12161
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,73,115,114,69,114,114,111,114,0
	.section	.debug_info		;off: 15242
	.data.w	.Ldw_str_begin+12161
	.data.b	59
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12184
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 15257
	.data.w	.Ldw_str_begin+12184
	.data.b	61
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12206
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 15272
	.data.w	.Ldw_str_begin+12206
	.data.b	63
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12227
	.data.b	83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15287
	.data.w	.Ldw_str_begin+12227
	.data.b	65
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12252
	.data.b	83,99,104,77,95,69,120,105,116,95,83,112,105,95,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15302
	.data.w	.Ldw_str_begin+12252
	.data.b	67
	.data.b	13
	.data.b	46
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 12276
	.data.b	68,105,111,95,87,114,105,116,101,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 15317
	.data.w	.Ldw_str_begin+12276
	.data.b	115
	.data.b	36
	.data.b	47
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12293
	.data.b	68,105,111,95,70,108,105,112,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 15332
	.data.w	.Ldw_str_begin+12293
	.data.b	154,1
	.data.b	45
	.data.b	47
	.data.w	.Ldw_begin+14048
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12309
	.data.b	68,101,116,95,82,101,112,111,114,116,69,114,114,111,114,0
	.section	.debug_info		;off: 15352
	.data.w	.Ldw_str_begin+12309
	.data.b	105
	.data.b	39
	.data.b	52
	.data.w	.Ldw_begin+2182
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 12325
	.data.b	68,101,116,95,82,101,112,111,114,116,82,117,110,116,105,109,101,69,114,114,111,114,0
	.section	.debug_info		;off: 15371
	.data.w	.Ldw_str_begin+12325
	.data.b	113
	.data.b	39
	.data.b	52
	.data.w	.Ldw_begin+2182
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12348
	.data.b	83,112,105,95,71,101,116,67,111,109,109,111,110,68,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15390
	.data.w	.Ldw_str_begin+12348
	.data.b	148,6
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetCommonDetStatus
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
	.data.w	Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetCommonDetStatus-Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2188
	.data.b	0,5,2
	.data.w	Spi_GetCommonDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	152,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	28
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	76
	.data.b	12
	.data.b	91
	.data.b	11
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
	.section	.debug_info		;off: 15425
	.data.b	22
	.section	.debug_str		;off: 12371
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15426
	.data.w	.Ldw_str_begin+12371
	.data.b	150,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2361
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

	.section	.debug_info		;off: 15443
	.data.b	22
	.section	.debug_str		;off: 12378
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15444
	.data.w	.Ldw_str_begin+12378
	.data.b	151,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15461
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

	.section	.debug_info		;off: 15470
	.data.b	7
	.section	.debug_str		;off: 12388
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15471
	.data.w	.Ldw_str_begin+12388
	.data.b	154,6
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+38
	.section	.debug_loc		;off: 38
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

	.section	.debug_info		;off: 15489
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12398
	.data.b	83,112,105,95,71,101,116,83,101,113,68,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15492
	.data.w	.Ldw_str_begin+12398
	.data.b	214,6
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetSeqDetStatus
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
	.data.w	Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetSeqDetStatus-Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2233
	.data.b	0,5,2
	.data.w	Spi_GetSeqDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	219,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	27
	.data.b	11
	.data.b	60
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	75
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	75
	.data.b	11
	.data.b	108
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
	.section	.debug_info		;off: 15527
	.data.b	22
	.section	.debug_str		;off: 12418
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15528
	.data.w	.Ldw_str_begin+12418
	.data.b	216,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+57
	.section	.debug_loc		;off: 57
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15545
	.data.b	22
	.section	.debug_str		;off: 12425
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15546
	.data.w	.Ldw_str_begin+12425
	.data.b	217,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.w	.Ldw_loc_begin+76
	.section	.debug_loc		;off: 76
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15563
	.data.b	22
	.section	.debug_str		;off: 12435
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 15564
	.data.w	.Ldw_str_begin+12435
	.data.b	218,6
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+95
	.section	.debug_loc		;off: 95
	.data.w	.LDW31
	.data.w	.LDW51
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15581
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 12444
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15591
	.data.w	.Ldw_str_begin+12444
	.data.b	221,6
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
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

	.section	.debug_info		;off: 15609
	.data.b	7
	.section	.debug_str		;off: 12454
	.data.b	67,111,114,101,120,83,101,113,73,100,120,0
	.section	.debug_info		;off: 15610
	.data.w	.Ldw_str_begin+12454
	.data.b	222,6
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+133
	.section	.debug_loc		;off: 133
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15628
	.data.b	7
	.section	.debug_str		;off: 12466
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 15629
	.data.w	.Ldw_str_begin+12466
	.data.b	223,6
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+152
	.section	.debug_loc		;off: 152
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15647
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12487
	.data.b	83,112,105,95,71,101,116,74,111,98,68,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15650
	.data.w	.Ldw_str_begin+12487
	.data.b	197,7
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetJobDetStatus
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
	.data.w	Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetJobDetStatus-Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2329
	.data.b	0,5,2
	.data.w	Spi_GetJobDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	202,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	27
	.data.b	11
	.data.b	60
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	91
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	75
	.data.b	11
	.data.b	108
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
	.section	.debug_info		;off: 15685
	.data.b	22
	.section	.debug_str		;off: 12507
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15686
	.data.w	.Ldw_str_begin+12507
	.data.b	199,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+171
	.section	.debug_loc		;off: 171
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15703
	.data.b	22
	.section	.debug_str		;off: 12514
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15704
	.data.w	.Ldw_str_begin+12514
	.data.b	200,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.w	.Ldw_loc_begin+190
	.section	.debug_loc		;off: 190
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15721
	.data.b	22
	.section	.debug_str		;off: 12524
	.data.b	74,111,98,0
	.section	.debug_info		;off: 15722
	.data.w	.Ldw_str_begin+12524
	.data.b	201,7
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+209
	.section	.debug_loc		;off: 209
	.data.w	.LDW61
	.data.w	.LDW81
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15739
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 12528
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15749
	.data.w	.Ldw_str_begin+12528
	.data.b	204,7
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+228
	.section	.debug_loc		;off: 228
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15767
	.data.b	7
	.section	.debug_str		;off: 12538
	.data.b	74,111,98,73,110,100,101,120,0
	.section	.debug_info		;off: 15768
	.data.w	.Ldw_str_begin+12538
	.data.b	205,7
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+247
	.section	.debug_loc		;off: 247
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15786
	.data.b	7
	.section	.debug_str		;off: 12547
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 15787
	.data.w	.Ldw_str_begin+12547
	.data.b	206,7
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+266
	.section	.debug_loc		;off: 266
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15805
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12568
	.data.b	83,112,105,95,71,101,116,67,104,97,110,110,101,108,68,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15808
	.data.w	.Ldw_str_begin+12568
	.data.b	181,8
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetChannelDetStatus
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
	.data.w	Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetChannelDetStatus-Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2425
	.data.b	0,5,2
	.data.w	Spi_GetChannelDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	186,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	108
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	44
	.data.b	6
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	59
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
	.section	.debug_info		;off: 15843
	.data.b	22
	.section	.debug_str		;off: 12592
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 15844
	.data.w	.Ldw_str_begin+12592
	.data.b	183,8
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+285
	.section	.debug_loc		;off: 285
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15861
	.data.b	22
	.section	.debug_str		;off: 12599
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 15862
	.data.w	.Ldw_str_begin+12599
	.data.b	184,8
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.w	.Ldw_loc_begin+304
	.section	.debug_loc		;off: 304
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15879
	.data.b	22
	.section	.debug_str		;off: 12609
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 15880
	.data.w	.Ldw_str_begin+12609
	.data.b	185,8
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.w	.Ldw_loc_begin+323
	.section	.debug_loc		;off: 323
	.data.w	.LDW91
	.data.w	.LDW12
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15897
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	7
	.section	.debug_str		;off: 12617
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 15907
	.data.w	.Ldw_str_begin+12617
	.data.b	188,8
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+342
	.section	.debug_loc		;off: 342
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15925
	.data.b	7
	.section	.debug_str		;off: 12627
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15926
	.data.w	.Ldw_str_begin+12627
	.data.b	189,8
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+361
	.section	.debug_loc		;off: 361
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15944
	.data.b	7
	.section	.debug_str		;off: 12637
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 15945
	.data.w	.Ldw_str_begin+12637
	.data.b	190,8
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+380
	.section	.debug_loc		;off: 380
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 15963
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12658
	.data.b	83,112,105,95,71,101,116,80,104,121,85,110,105,116,68,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 15966
	.data.w	.Ldw_str_begin+12658
	.data.b	150,9
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetPhyUnitDetStatus
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetPhyUnitDetStatus-Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2509
	.data.b	0,5,2
	.data.w	Spi_GetPhyUnitDetStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	155,9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	75
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	43
	.data.b	11
	.data.b	108
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	59
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
	.section	.debug_info		;off: 16001
	.data.b	22
	.section	.debug_str		;off: 12682
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16002
	.data.w	.Ldw_str_begin+12682
	.data.b	152,9
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+399
	.section	.debug_loc		;off: 399
	.data.w	.LDW22
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16019
	.data.b	22
	.section	.debug_str		;off: 12689
	.data.b	83,101,114,118,105,99,101,73,100,0
	.section	.debug_info		;off: 16020
	.data.w	.Ldw_str_begin+12689
	.data.b	153,9
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.w	.Ldw_loc_begin+418
	.section	.debug_loc		;off: 418
	.data.w	.LDW22
	.data.w	.LDW42
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16037
	.data.b	22
	.section	.debug_str		;off: 12699
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 16038
	.data.w	.Ldw_str_begin+12699
	.data.b	154,9
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+437
	.section	.debug_loc		;off: 437
	.data.w	.LDW22
	.data.w	.LDW42
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16055
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	7
	.section	.debug_str		;off: 12707
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16065
	.data.w	.Ldw_str_begin+12707
	.data.b	157,9
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+456
	.section	.debug_loc		;off: 456
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16083
	.data.b	7
	.section	.debug_str		;off: 12717
	.data.b	67,111,114,101,80,104,121,85,110,105,116,73,100,120,0
	.section	.debug_info		;off: 16084
	.data.w	.Ldw_str_begin+12717
	.data.b	158,9
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+475
	.section	.debug_loc		;off: 475
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16102
	.data.b	7
	.section	.debug_str		;off: 12732
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 16103
	.data.w	.Ldw_str_begin+12732
	.data.b	159,9
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+494
	.section	.debug_loc		;off: 494
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16121
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12753
	.data.b	83,112,105,95,71,101,116,68,114,105,118,101,114,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16124
	.data.w	.Ldw_str_begin+12753
	.data.b	130,10
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.w	Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetDriverStatus
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetDriverStatus-Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2601
	.data.b	0,5,2
	.data.w	Spi_GetDriverStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	133,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	139
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16157
	.data.b	22
	.section	.debug_str		;off: 12773
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16158
	.data.w	.Ldw_str_begin+12773
	.data.b	132,10
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+513
	.section	.debug_loc		;off: 513
	.data.w	.LDW52
	.data.w	.LDW62
	.data.b	1,0
	.data.b	80
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16175
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	7
	.section	.debug_str		;off: 12780
	.data.b	83,112,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16185
	.data.w	.Ldw_str_begin+12780
	.data.b	135,10
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+543
	.section	.debug_loc		;off: 543
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16203
	.data.b	8
	.section	.debug_str		;off: 12790
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 16204
	.data.w	.Ldw_str_begin+12790
	.data.b	136,10
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12803
	.data.b	83,112,105,95,65,115,121,110,99,71,101,116,80,104,121,85,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16221
	.data.w	.Ldw_str_begin+12803
	.data.b	183,10
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.w	Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncGetPhyUnitStatus
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncGetPhyUnitStatus-Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2643
	.data.b	0,5,2
	.data.w	Spi_AsyncGetPhyUnitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	186,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	124
	.data.b	123
	.data.b	43
	.data.b	11
	.data.b	28
	.data.b	12
	.data.b	11
	.data.b	44
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16256
	.data.b	22
	.section	.debug_str		;off: 12829
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16257
	.data.w	.Ldw_str_begin+12829
	.data.b	185,10
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+562
	.section	.debug_loc		;off: 562
	.data.w	.LDW82
	.data.w	.LDW92
	.data.b	1,0
	.data.b	80
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16274
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	8
	.section	.debug_str		;off: 12836
	.data.b	70,105,110,100,66,117,115,121,65,115,121,110,99,72,87,0
	.section	.debug_info		;off: 16284
	.data.w	.Ldw_str_begin+12836
	.data.b	188,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 12852
	.data.b	83,112,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16299
	.data.w	.Ldw_str_begin+12852
	.data.b	189,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+592
	.section	.debug_loc		;off: 592
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16317
	.data.b	8
	.section	.debug_str		;off: 12862
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 16318
	.data.w	.Ldw_str_begin+12862
	.data.b	190,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12875
	.data.b	83,112,105,95,83,121,110,99,83,116,97,114,116,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 16335
	.data.w	.Ldw_str_begin+12875
	.data.b	244,10
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncStartTransmit
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncStartTransmit-Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2693
	.data.b	0,5,2
	.data.w	Spi_SyncStartTransmit..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	248,10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	29
	.data.b	108
	.data.b	28
	.data.b	27
	.data.b	3
	.data.b	245,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	139,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	156
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	205
	.data.b	172
	.data.b	29
	.data.b	140
	.data.b	76
	.data.b	29
	.data.b	155
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	189
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	187
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 16370
	.data.b	22
	.section	.debug_str		;off: 12897
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16371
	.data.w	.Ldw_str_begin+12897
	.data.b	246,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+611
	.section	.debug_loc		;off: 611
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

	.section	.debug_info		;off: 16388
	.data.b	22
	.section	.debug_str		;off: 12904
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 16389
	.data.w	.Ldw_str_begin+12904
	.data.b	247,10
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+641
	.section	.debug_loc		;off: 641
	.data.w	.LDW13
	.data.w	.LDW33
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16406
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 12913
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16416
	.data.w	.Ldw_str_begin+12913
	.data.b	250,10
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+660
	.section	.debug_loc		;off: 660
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16434
	.data.b	7
	.section	.debug_str		;off: 12923
	.data.b	74,111,98,78,117,109,98,101,114,73,110,83,101,113,0
	.section	.debug_info		;off: 16435
	.data.w	.Ldw_str_begin+12923
	.data.b	251,10
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+679
	.section	.debug_loc		;off: 679
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16453
	.data.b	7
	.section	.debug_str		;off: 12938
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16454
	.data.w	.Ldw_str_begin+12938
	.data.b	252,10
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+698
	.section	.debug_loc		;off: 698
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16472
	.data.b	7
	.section	.debug_str		;off: 12948
	.data.b	74,111,98,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 16473
	.data.w	.Ldw_str_begin+12948
	.data.b	253,10
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+339
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+717
	.section	.debug_loc		;off: 717
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16491
	.data.b	7
	.section	.debug_str		;off: 12960
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16492
	.data.w	.Ldw_str_begin+12960
	.data.b	254,10
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+349
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+736
	.section	.debug_loc		;off: 736
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16510
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 12970
	.data.b	83,112,105,95,83,121,110,99,84,114,97,110,115,109,105,116,74,111,98,0
	.section	.debug_info		;off: 16513
	.data.w	.Ldw_str_begin+12970
	.data.b	156,12
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncTransmitJob
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	236,0
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
	.data.w	Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncTransmitJob-Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2801
	.data.b	0,5,2
	.data.w	Spi_SyncTransmitJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	160,12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	20
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
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
	.data.b	60
	.data.b	93
	.data.b	140
	.data.b	44
	.data.b	76
	.data.b	28
	.data.b	28
	.data.b	60
	.data.b	93
	.data.b	77
	.data.b	75
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	29
	.data.b	28
	.data.b	93
	.data.b	125
	.data.b	44
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	43
	.data.b	28
	.data.b	29
	.data.b	75
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	107
	.data.b	11
	.data.b	45
	.data.b	12
	.data.b	11
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	59
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	88
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	41
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	107
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	11
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	110
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	156,127
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	229,0
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	134,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	251,0
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 16549
	.data.b	22
	.section	.debug_str		;off: 12990
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16550
	.data.w	.Ldw_str_begin+12990
	.data.b	158,12
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+755
	.section	.debug_loc		;off: 755
	.data.w	.LDW43
	.data.w	.LDW53
	.data.b	1,0
	.data.b	80
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	28
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16567
	.data.b	22
	.section	.debug_str		;off: 12997
	.data.b	74,111,98,0
	.section	.debug_info		;off: 16568
	.data.w	.Ldw_str_begin+12997
	.data.b	159,12
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+786
	.section	.debug_loc		;off: 786
	.data.w	.LDW43
	.data.w	.LDW63
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16585
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	7
	.section	.debug_str		;off: 13001
	.data.b	76,101,118,101,108,0
	.section	.debug_info		;off: 16595
	.data.w	.Ldw_str_begin+13001
	.data.b	162,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+805
	.section	.debug_loc		;off: 805
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	6
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16613
	.data.b	7
	.section	.debug_str		;off: 13007
	.data.b	84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 16614
	.data.w	.Ldw_str_begin+13007
	.data.b	163,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+825
	.section	.debug_loc		;off: 825
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16632
	.data.b	8
	.section	.debug_str		;off: 13017
	.data.b	68,97,116,97,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 16633
	.data.w	.Ldw_str_begin+13017
	.data.b	164,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13030
	.data.b	84,120,66,117,102,102,101,114,73,110,100,101,120,0
	.section	.debug_info		;off: 16648
	.data.w	.Ldw_str_begin+13030
	.data.b	165,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+844
	.section	.debug_loc		;off: 844
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	16
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16666
	.data.b	7
	.section	.debug_str		;off: 13044
	.data.b	82,120,66,117,102,102,101,114,73,110,100,101,120,0
	.section	.debug_info		;off: 16667
	.data.w	.Ldw_str_begin+13044
	.data.b	166,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+864
	.section	.debug_loc		;off: 864
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	20
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16685
	.data.b	7
	.section	.debug_str		;off: 13058
	.data.b	67,104,68,121,110,97,109,105,99,67,102,103,0
	.section	.debug_info		;off: 16686
	.data.w	.Ldw_str_begin+13058
	.data.b	167,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+884
	.section	.debug_loc		;off: 884
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16704
	.data.b	7
	.section	.debug_str		;off: 13071
	.data.b	84,101,109,112,82,120,66,117,102,102,101,114,0
	.section	.debug_info		;off: 16705
	.data.w	.Ldw_str_begin+13071
	.data.b	168,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+903
	.section	.debug_loc		;off: 903
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16723
	.data.b	7
	.section	.debug_str		;off: 13084
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16724
	.data.w	.Ldw_str_begin+13084
	.data.b	169,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+923
	.section	.debug_loc		;off: 923
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16742
	.data.b	7
	.section	.debug_str		;off: 13094
	.data.b	67,104,78,117,109,98,101,114,73,110,74,111,98,0
	.section	.debug_info		;off: 16743
	.data.w	.Ldw_str_begin+13094
	.data.b	170,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+942
	.section	.debug_loc		;off: 942
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16761
	.data.b	7
	.section	.debug_str		;off: 13108
	.data.b	70,114,97,109,101,115,67,111,117,110,116,0
	.section	.debug_info		;off: 16762
	.data.w	.Ldw_str_begin+13108
	.data.b	171,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+11760
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+962
	.section	.debug_loc		;off: 962
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	14
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16780
	.data.b	7
	.section	.debug_str		;off: 13120
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 16781
	.data.w	.Ldw_str_begin+13120
	.data.b	172,12
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+120
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+982
	.section	.debug_loc		;off: 982
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16799
	.data.b	7
	.section	.debug_str		;off: 13128
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 16800
	.data.w	.Ldw_str_begin+13128
	.data.b	173,12
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+378
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1001
	.section	.debug_loc		;off: 1001
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	24
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16818
	.data.b	7
	.section	.debug_str		;off: 13144
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16819
	.data.w	.Ldw_str_begin+13144
	.data.b	174,12
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1021
	.section	.debug_loc		;off: 1021
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16837
	.data.b	7
	.section	.debug_str		;off: 13158
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16838
	.data.w	.Ldw_str_begin+13158
	.data.b	175,12
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+398
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1040
	.section	.debug_loc		;off: 1040
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16856
	.data.b	7
	.section	.debug_str		;off: 13173
	.data.b	67,104,68,121,110,97,109,105,99,67,111,110,102,105,103,0
	.section	.debug_info		;off: 16857
	.data.w	.Ldw_str_begin+13173
	.data.b	176,12
	.data.b	49
	.data.b	1
	.data.w	.Ldw_begin+11856
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1059
	.section	.debug_loc		;off: 1059
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	2,0
	.data.b	125
	.data.b	32
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16875
	.data.b	7
	.section	.debug_str		;off: 13189
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 16876
	.data.w	.Ldw_str_begin+13189
	.data.b	177,12
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1079
	.section	.debug_loc		;off: 1079
	.data.w	.LDW53
	.data.w	.LDW63
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16894
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13199
	.data.b	83,112,105,95,83,121,110,99,87,97,105,116,84,114,97,110,115,70,105,110,105,115,104,0
	.section	.debug_info		;off: 16897
	.data.w	.Ldw_str_begin+13199
	.data.b	255,13
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncWaitTransFinish
	.data.b	1
	.data.b	93
	.data.b	240,149,1
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_SyncWaitTransFinish-Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3018
	.data.b	0,5,2
	.data.w	Spi_SyncWaitTransFinish..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	131,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	44
	.data.b	109
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	61
	.data.b	2
	.data.b	20
	.data.b	13
	.data.b	27
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	108
	.data.b	13
	.data.b	11
	.data.b	60
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 16932
	.data.b	22
	.section	.debug_str		;off: 13223
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 16933
	.data.w	.Ldw_str_begin+13223
	.data.b	129,14
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+1098
	.section	.debug_loc		;off: 1098
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	80
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16950
	.data.b	22
	.section	.debug_str		;off: 13230
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 16951
	.data.w	.Ldw_str_begin+13230
	.data.b	130,14
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+1129
	.section	.debug_loc		;off: 1129
	.data.w	.LDW73
	.data.w	.LDW83
	.data.b	1,0
	.data.b	81
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16968
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	7
	.section	.debug_str		;off: 13238
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 16978
	.data.w	.Ldw_str_begin+13238
	.data.b	133,14
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1159
	.section	.debug_loc		;off: 1159
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	2,0
	.data.b	125
	.data.b	3
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 16996
	.data.b	7
	.section	.debug_str		;off: 13248
	.data.b	82,101,103,86,97,108,117,101,0
	.section	.debug_info		;off: 16997
	.data.w	.Ldw_str_begin+13248
	.data.b	134,14
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1179
	.section	.debug_loc		;off: 1179
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17015
	.data.b	8
	.section	.debug_str		;off: 13257
	.data.b	84,105,109,101,114,70,114,101,113,0
	.section	.debug_info		;off: 17016
	.data.w	.Ldw_str_begin+13257
	.data.b	135,14
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2158
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13267
	.data.b	84,105,109,101,79,117,116,67,111,117,110,116,0
	.section	.debug_info		;off: 17031
	.data.w	.Ldw_str_begin+13267
	.data.b	136,14
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2158
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1198
	.section	.debug_loc		;off: 1198
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17049
	.data.b	7
	.section	.debug_str		;off: 13280
	.data.b	67,117,114,114,101,110,116,67,111,117,110,116,0
	.section	.debug_info		;off: 17050
	.data.w	.Ldw_str_begin+13280
	.data.b	137,14
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2158
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1217
	.section	.debug_loc		;off: 1217
	.data.w	.LDW83
	.data.w	.LDW93
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17068
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13293
	.data.b	83,112,105,95,65,115,121,110,99,67,104,101,99,107,74,111,98,76,105,110,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 17071
	.data.w	.Ldw_str_begin+13293
	.data.b	211,14
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncCheckJobLinkStatus
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	32
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
	.data.w	Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncCheckJobLinkStatus-Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3098
	.data.b	0,5,2
	.data.w	Spi_AsyncCheckJobLinkStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	215,14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	156
	.data.b	28
	.data.b	27
	.data.b	3
	.data.b	42
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	86
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	123
	.data.b	75
	.data.b	13
	.data.b	108
	.data.b	44
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	28
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 17106
	.data.b	22
	.section	.debug_str		;off: 13321
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17107
	.data.w	.Ldw_str_begin+13321
	.data.b	213,14
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+1236
	.section	.debug_loc		;off: 1236
	.data.w	.LDW04
	.data.w	.LDW14
	.data.b	1,0
	.data.b	80
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17124
	.data.b	22
	.section	.debug_str		;off: 13328
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 17125
	.data.w	.Ldw_str_begin+13328
	.data.b	214,14
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+1266
	.section	.debug_loc		;off: 1266
	.data.w	.LDW04
	.data.w	.LDW24
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17142
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	7
	.section	.debug_str		;off: 13337
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 17152
	.data.w	.Ldw_str_begin+13337
	.data.b	217,14
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1285
	.section	.debug_loc		;off: 1285
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17170
	.data.b	7
	.section	.debug_str		;off: 13347
	.data.b	74,111,98,78,117,109,98,101,114,73,110,83,101,113,0
	.section	.debug_info		;off: 17171
	.data.w	.Ldw_str_begin+13347
	.data.b	218,14
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1304
	.section	.debug_loc		;off: 1304
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17189
	.data.b	7
	.section	.debug_str		;off: 13362
	.data.b	74,111,98,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 17190
	.data.w	.Ldw_str_begin+13362
	.data.b	219,14
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+339
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1323
	.section	.debug_loc		;off: 1323
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17208
	.data.b	7
	.section	.debug_str		;off: 13374
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17209
	.data.w	.Ldw_str_begin+13374
	.data.b	220,14
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1342
	.section	.debug_loc		;off: 1342
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17227
	.data.b	7
	.section	.debug_str		;off: 13384
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17228
	.data.w	.Ldw_str_begin+13384
	.data.b	221,14
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+349
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1361
	.section	.debug_loc		;off: 1361
	.data.w	.LDW14
	.data.w	.LDW24
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17246
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13394
	.data.b	83,112,105,95,65,115,121,110,99,83,99,104,101,100,117,108,101,74,111,98,0
	.section	.debug_info		;off: 17249
	.data.w	.Ldw_str_begin+13394
	.data.b	176,15
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncScheduleJob
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
	.data.w	Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncScheduleJob-Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3174
	.data.b	0,5,2
	.data.w	Spi_AsyncScheduleJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	180,15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	121
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	29
	.data.b	235
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	27
	.data.b	13
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	29
	.data.b	43
	.data.b	13
	.data.b	125
	.data.b	43
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
	.section	.debug_info		;off: 17284
	.data.b	22
	.section	.debug_str		;off: 13415
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17285
	.data.w	.Ldw_str_begin+13415
	.data.b	178,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+1380
	.section	.debug_loc		;off: 1380
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

	.section	.debug_info		;off: 17302
	.data.b	22
	.section	.debug_str		;off: 13422
	.data.b	74,111,98,0
	.section	.debug_info		;off: 17303
	.data.w	.Ldw_str_begin+13422
	.data.b	179,15
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+1410
	.section	.debug_loc		;off: 1410
	.data.w	.LDW34
	.data.w	.LDW44
	.data.b	1,0
	.data.b	81
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17320
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	7
	.section	.debug_str		;off: 13426
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 17330
	.data.w	.Ldw_str_begin+13426
	.data.b	182,15
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1440
	.section	.debug_loc		;off: 1440
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17348
	.data.b	7
	.section	.debug_str		;off: 13436
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17349
	.data.w	.Ldw_str_begin+13436
	.data.b	183,15
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1459
	.section	.debug_loc		;off: 1459
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17367
	.data.b	7
	.section	.debug_str		;off: 13446
	.data.b	84,114,105,103,103,101,114,68,109,97,70,108,97,103,0
	.section	.debug_info		;off: 17368
	.data.w	.Ldw_str_begin+13446
	.data.b	185,15
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1478
	.section	.debug_loc		;off: 1478
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17386
	.data.b	8
	.section	.debug_str		;off: 13461
	.data.b	83,112,105,80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 17387
	.data.w	.Ldw_str_begin+13461
	.data.b	186,15
	.data.b	44
	.data.b	1
	.data.w	.Ldw_begin+465
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13481
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17402
	.data.w	.Ldw_str_begin+13481
	.data.b	187,15
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+475
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1497
	.section	.debug_loc		;off: 1497
	.data.w	.LDW44
	.data.w	.LDW54
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17420
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13495
	.data.b	83,112,105,95,65,115,121,110,99,74,111,98,84,114,97,110,115,102,101,114,0
	.section	.debug_info		;off: 17423
	.data.w	.Ldw_str_begin+13495
	.data.b	143,16
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransfer
	.data.b	1
	.data.b	93
	.data.b	240,143,1
	.data.b	100
	.data.b	0
	.data.b	196,0
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
	.data.w	Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransfer-Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3247
	.data.b	0,5,2
	.data.w	Spi_AsyncJobTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	147,16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	25
	.data.b	2
	.data.b	64
	.data.b	1
	.data.b	141
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	60
	.data.b	140
	.data.b	43
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	61
	.data.b	45
	.data.b	92
	.data.b	44
	.data.b	76
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	75
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	76
	.data.b	12
	.data.b	140
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	27
	.data.b	12
	.data.b	125
	.data.b	2
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	2
	.data.b	0
	.data.b	59
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
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 17459
	.data.b	22
	.section	.debug_str		;off: 13516
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17460
	.data.w	.Ldw_str_begin+13516
	.data.b	145,16
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+1516
	.section	.debug_loc		;off: 1516
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

	.section	.debug_info		;off: 17477
	.data.b	22
	.section	.debug_str		;off: 13523
	.data.b	74,111,98,0
	.section	.debug_info		;off: 17478
	.data.w	.Ldw_str_begin+13523
	.data.b	146,16
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+1546
	.section	.debug_loc		;off: 1546
	.data.w	.LDW64
	.data.w	.LDW84
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17495
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	7
	.section	.debug_str		;off: 13527
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 17505
	.data.w	.Ldw_str_begin+13527
	.data.b	149,16
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1565
	.section	.debug_loc		;off: 1565
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17523
	.data.b	8
	.section	.debug_str		;off: 13537
	.data.b	68,97,116,97,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 17524
	.data.w	.Ldw_str_begin+13537
	.data.b	150,16
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13550
	.data.b	68,101,118,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 17539
	.data.w	.Ldw_str_begin+13550
	.data.b	151,16
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+499
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1584
	.section	.debug_loc		;off: 1584
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17557
	.data.b	7
	.section	.debug_str		;off: 13562
	.data.b	67,104,68,121,110,97,109,105,99,67,111,110,102,105,103,0
	.section	.debug_info		;off: 17558
	.data.w	.Ldw_str_begin+13562
	.data.b	152,16
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+11856
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1603
	.section	.debug_loc		;off: 1603
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17576
	.data.b	7
	.section	.debug_str		;off: 13578
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17577
	.data.w	.Ldw_str_begin+13578
	.data.b	153,16
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+398
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1623
	.section	.debug_loc		;off: 1623
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17595
	.data.b	7
	.section	.debug_str		;off: 13593
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17596
	.data.w	.Ldw_str_begin+13593
	.data.b	154,16
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1642
	.section	.debug_loc		;off: 1642
	.data.w	.LDW74
	.data.w	.LDW84
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17614
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13603
	.data.b	83,112,105,95,65,115,121,110,99,74,111,98,68,109,97,84,114,97,110,115,102,101,114,0
	.section	.debug_info		;off: 17617
	.data.w	.Ldw_str_begin+13603
	.data.b	145,17
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobDmaTransfer
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	132,1
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
	.data.w	Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobDmaTransfer-Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3361
	.data.b	0,5,2
	.data.w	Spi_AsyncJobDmaTransfer..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	149,17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	173
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	92
	.data.b	60
	.data.b	124
	.data.b	43
	.data.b	13
	.data.b	204
	.data.b	28
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	77
	.data.b	44
	.data.b	44
	.data.b	28
	.data.b	29
	.data.b	124
	.data.b	28
	.data.b	2
	.data.b	4
	.data.b	29
	.data.b	156
	.data.b	28
	.data.b	28
	.data.b	44
	.data.b	44
	.data.b	45
	.data.b	28
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	76
	.data.b	43
	.data.b	13
	.data.b	11
	.data.b	29
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	125
	.data.b	43
	.data.b	59
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	59
	.data.b	12
	.data.b	108
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	77
	.data.b	44
	.data.b	91
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	13
	.data.b	12
	.data.b	27
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	12
	.data.b	28
	.data.b	27
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	251,126
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	3
	.data.b	138,1
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	93
	.data.b	141
	.data.b	141
	.data.b	124
	.data.b	3
	.data.b	1
	.data.b	2
	.data.b	68
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	75
	.data.b	11
	.data.b	28
	.data.b	91
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	12
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
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 17653
	.data.b	22
	.section	.debug_str		;off: 13627
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 17654
	.data.w	.Ldw_str_begin+13627
	.data.b	147,17
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+1661
	.section	.debug_loc		;off: 1661
	.data.w	.LDW94
	.data.w	.LDW05
	.data.b	1,0
	.data.b	80
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	2,0
	.data.b	125
	.data.b	16
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17671
	.data.b	22
	.section	.debug_str		;off: 13634
	.data.b	74,111,98,0
	.section	.debug_info		;off: 17672
	.data.w	.Ldw_str_begin+13634
	.data.b	148,17
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+1692
	.section	.debug_loc		;off: 1692
	.data.w	.LDW94
	.data.w	.LDW15
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17689
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	7
	.section	.debug_str		;off: 13638
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 17699
	.data.w	.Ldw_str_begin+13638
	.data.b	151,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1711
	.section	.debug_loc		;off: 1711
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17717
	.data.b	7
	.section	.debug_str		;off: 13648
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 17718
	.data.w	.Ldw_str_begin+13648
	.data.b	152,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1730
	.section	.debug_loc		;off: 1730
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17736
	.data.b	7
	.section	.debug_str		;off: 13658
	.data.b	67,104,67,111,117,110,116,0
	.section	.debug_info		;off: 17737
	.data.w	.Ldw_str_begin+13658
	.data.b	153,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1749
	.section	.debug_loc		;off: 1749
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17755
	.data.b	7
	.section	.debug_str		;off: 13666
	.data.b	67,104,97,110,110,101,108,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 17756
	.data.w	.Ldw_str_begin+13666
	.data.b	154,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1768
	.section	.debug_loc		;off: 1768
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17774
	.data.b	8
	.section	.debug_str		;off: 13682
	.data.b	68,97,116,97,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 17775
	.data.w	.Ldw_str_begin+13682
	.data.b	155,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13695
	.data.b	67,104,68,121,110,97,109,105,99,67,102,103,0
	.section	.debug_info		;off: 17790
	.data.w	.Ldw_str_begin+13695
	.data.b	156,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1787
	.section	.debug_loc		;off: 1787
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17808
	.data.b	7
	.section	.debug_str		;off: 13708
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 17809
	.data.w	.Ldw_str_begin+13708
	.data.b	157,17
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+378
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1806
	.section	.debug_loc		;off: 1806
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17827
	.data.b	7
	.section	.debug_str		;off: 13724
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17828
	.data.w	.Ldw_str_begin+13724
	.data.b	158,17
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1826
	.section	.debug_loc		;off: 1826
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17846
	.data.b	7
	.section	.debug_str		;off: 13734
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17847
	.data.w	.Ldw_str_begin+13734
	.data.b	159,17
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1845
	.section	.debug_loc		;off: 1845
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17865
	.data.b	7
	.section	.debug_str		;off: 13748
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17866
	.data.w	.Ldw_str_begin+13748
	.data.b	160,17
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+475
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1864
	.section	.debug_loc		;off: 1864
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17884
	.data.b	7
	.section	.debug_str		;off: 13762
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 17885
	.data.w	.Ldw_str_begin+13762
	.data.b	161,17
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+398
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1883
	.section	.debug_loc		;off: 1883
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17903
	.data.b	7
	.section	.debug_str		;off: 13777
	.data.b	76,108,105,67,111,110,102,105,103,0
	.section	.debug_info		;off: 17904
	.data.w	.Ldw_str_begin+13777
	.data.b	162,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+11579
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1903
	.section	.debug_loc		;off: 1903
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	2,0
	.data.b	125
	.data.b	60
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17922
	.data.b	7
	.section	.debug_str		;off: 13787
	.data.b	67,104,68,121,110,97,109,105,99,67,111,110,102,105,103,0
	.section	.debug_info		;off: 17923
	.data.w	.Ldw_str_begin+13787
	.data.b	163,17
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+11856
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1923
	.section	.debug_loc		;off: 1923
	.data.w	.LDW05
	.data.w	.LDW15
	.data.b	2,0
	.data.b	125
	.data.b	20
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 17941
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 13803
	.data.b	83,112,105,95,68,109,97,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 17944
	.data.w	.Ldw_str_begin+13803
	.data.b	172,19
	.data.b	29
	.data.b	1
	.data.w	Spi_DmaNotification
	.data.w	__ghs_eofn_Spi_DmaNotification
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_DmaNotification
	.data.w	__ghs_eofn_Spi_DmaNotification-Spi_DmaNotification
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3592
	.data.b	0,5,2
	.data.w	Spi_DmaNotification
	.data.b	6
	.data.b	3
	.data.b	176,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	13
	.data.b	28
	.data.b	156
	.data.b	43
	.data.b	13
	.data.b	29
	.data.b	219
	.data.b	27
	.data.b	11
	.data.b	76
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
	.section	.debug_info		;off: 17975
	.data.b	22
	.section	.debug_str		;off: 13823
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 17976
	.data.w	.Ldw_str_begin+13823
	.data.b	174,19
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11555
	.data.b	0
	.data.w	.Ldw_loc_begin+1943
	.section	.debug_loc		;off: 1943
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

	.section	.debug_info		;off: 17993
	.data.b	22
	.section	.debug_str		;off: 13831
	.data.b	67,104,73,110,116,114,69,118,116,0
	.section	.debug_info		;off: 17994
	.data.w	.Ldw_str_begin+13831
	.data.b	175,19
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11629
	.data.b	0
	.data.w	.Ldw_loc_begin+1973
	.section	.debug_loc		;off: 1973
	.data.w	.LDW25
	.data.w	.LDW45
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18011
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	8
	.section	.debug_str		;off: 13841
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 18021
	.data.w	.Ldw_str_begin+13841
	.data.b	179,19
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 13851
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18036
	.data.w	.Ldw_str_begin+13851
	.data.b	181,19
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+1992
	.section	.debug_loc		;off: 1992
	.data.w	.LDW35
	.data.w	.LDW45
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18054
	.data.b	8
	.section	.debug_str		;off: 13858
	.data.b	68,109,97,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18055
	.data.w	.Ldw_str_begin+13858
	.data.b	182,19
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13875
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18070
	.data.w	.Ldw_str_begin+13875
	.data.b	183,19
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 13885
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18085
	.data.w	.Ldw_str_begin+13885
	.data.b	184,19
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+475
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 13899
	.data.b	83,112,105,95,65,115,121,110,99,76,105,110,107,74,111,98,76,105,115,116,0
	.section	.debug_info		;off: 18102
	.data.w	.Ldw_str_begin+13899
	.data.b	242,19
	.data.b	37
	.data.b	1
	.data.w	Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncLinkJobList
	.data.b	1
	.data.b	93
	.data.b	240,129,1
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncLinkJobList-Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3659
	.data.b	0,5,2
	.data.w	Spi_AsyncLinkJobList..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	246,19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	156
	.data.b	60
	.data.b	29
	.data.b	140
	.data.b	44
	.data.b	43
	.data.b	13
	.data.b	27
	.data.b	12
	.data.b	13
	.data.b	77
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18133
	.data.b	22
	.section	.debug_str		;off: 13920
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18134
	.data.w	.Ldw_str_begin+13920
	.data.b	244,19
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2011
	.section	.debug_loc		;off: 2011
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18151
	.data.b	22
	.section	.debug_str		;off: 13927
	.data.b	74,111,98,0
	.section	.debug_info		;off: 18152
	.data.w	.Ldw_str_begin+13927
	.data.b	245,19
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+2030
	.section	.debug_loc		;off: 2030
	.data.w	.LDW55
	.data.w	.LDW75
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18169
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	7
	.section	.debug_str		;off: 13931
	.data.b	80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 18179
	.data.w	.Ldw_str_begin+13931
	.data.b	248,19
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2049
	.section	.debug_loc		;off: 2049
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18197
	.data.b	7
	.section	.debug_str		;off: 13940
	.data.b	74,111,98,76,105,115,116,84,97,105,108,80,116,114,0
	.section	.debug_info		;off: 18198
	.data.w	.Ldw_str_begin+13940
	.data.b	249,19
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+553
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2068
	.section	.debug_loc		;off: 2068
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18216
	.data.b	7
	.section	.debug_str		;off: 13955
	.data.b	83,112,105,80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 18217
	.data.w	.Ldw_str_begin+13955
	.data.b	250,19
	.data.b	35
	.data.b	1
	.data.w	.Ldw_begin+558
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2087
	.section	.debug_loc		;off: 2087
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18235
	.data.b	7
	.section	.debug_str		;off: 13975
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18236
	.data.w	.Ldw_str_begin+13975
	.data.b	251,19
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2106
	.section	.debug_loc		;off: 2106
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18254
	.data.b	7
	.section	.debug_str		;off: 13985
	.data.b	84,97,105,108,74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18255
	.data.w	.Ldw_str_begin+13985
	.data.b	252,19
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2125
	.section	.debug_loc		;off: 2125
	.data.w	.LDW65
	.data.w	.LDW75
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18273
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 13999
	.data.b	83,112,105,95,65,115,121,110,99,74,111,98,84,114,97,110,115,102,101,114,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18276
	.data.w	.Ldw_str_begin+13999
	.data.b	190,20
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransferChannel
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransferChannel-Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3705
	.data.b	0,5,2
	.data.w	Spi_AsyncJobTransferChannel..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	195,20
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	141
	.data.b	124
	.data.b	43
	.data.b	12
	.data.b	44
	.data.b	60
	.data.b	28
	.data.b	60
	.data.b	44
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	60
	.data.b	92
	.data.b	2
	.data.b	0
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
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	28
	.data.b	91
	.data.b	11
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	125
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	156
	.data.b	45
	.data.b	29
	.data.b	43
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	17
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	107
	.data.b	11
	.data.b	77
	.data.b	13
	.data.b	11
	.data.b	76
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	75
	.data.b	12
	.data.b	59
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	81
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	49
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 18311
	.data.b	22
	.section	.debug_str		;off: 14027
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18312
	.data.w	.Ldw_str_begin+14027
	.data.b	192,20
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2144
	.section	.debug_loc		;off: 2144
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	80
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18329
	.data.b	22
	.section	.debug_str		;off: 14034
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 18330
	.data.w	.Ldw_str_begin+14034
	.data.b	193,20
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+2174
	.section	.debug_loc		;off: 2174
	.data.w	.LDW85
	.data.w	.LDW95
	.data.b	1,0
	.data.b	81
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18347
	.data.b	22
	.section	.debug_str		;off: 14042
	.data.b	78,101,119,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 18348
	.data.w	.Ldw_str_begin+14042
	.data.b	194,20
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.w	.Ldw_loc_begin+2204
	.section	.debug_loc		;off: 2204
	.data.w	.LDW85
	.data.w	.LDW06
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18365
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	7
	.section	.debug_str		;off: 14053
	.data.b	84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 18375
	.data.w	.Ldw_str_begin+14053
	.data.b	197,20
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2223
	.section	.debug_loc		;off: 2223
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18393
	.data.b	7
	.section	.debug_str		;off: 14063
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18394
	.data.w	.Ldw_str_begin+14063
	.data.b	198,20
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2242
	.section	.debug_loc		;off: 2242
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18412
	.data.b	7
	.section	.debug_str		;off: 14073
	.data.b	84,120,66,117,102,102,101,114,73,110,100,101,120,0
	.section	.debug_info		;off: 18413
	.data.w	.Ldw_str_begin+14073
	.data.b	199,20
	.data.b	53
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2261
	.section	.debug_loc		;off: 2261
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18431
	.data.b	7
	.section	.debug_str		;off: 14087
	.data.b	68,101,118,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 18432
	.data.w	.Ldw_str_begin+14087
	.data.b	200,20
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+499
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2280
	.section	.debug_loc		;off: 2280
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18450
	.data.b	7
	.section	.debug_str		;off: 14099
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18451
	.data.w	.Ldw_str_begin+14099
	.data.b	201,20
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2299
	.section	.debug_loc		;off: 2299
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18469
	.data.b	7
	.section	.debug_str		;off: 14113
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18470
	.data.w	.Ldw_str_begin+14113
	.data.b	203,20
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+398
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2318
	.section	.debug_loc		;off: 2318
	.data.w	.LDW95
	.data.w	.LDW06
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18488
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14128
	.data.b	83,112,105,95,65,115,121,110,99,74,111,98,84,114,97,110,115,102,101,114,70,105,110,105,115,104,101,100,0
	.section	.debug_info		;off: 18491
	.data.w	.Ldw_str_begin+14128
	.data.b	219,21
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransferFinished
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncJobTransferFinished-Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3828
	.data.b	0,5,2
	.data.w	Spi_AsyncJobTransferFinished..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	223,21
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	108
	.data.b	75
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	26
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	172
	.data.b	91
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	13
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	28
	.data.b	12
	.data.b	75
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	59
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	118
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	13
	.data.b	3
	.data.b	50
	.data.b	2
	.data.b	48
	.data.b	1
	.data.b	12
	.data.b	59
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	28
	.data.b	3
	.data.b	73
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	53
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	6
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	21
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	6
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	6
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	91
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	107
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	13
	.data.b	125
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 18526
	.data.b	22
	.section	.debug_str		;off: 14157
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18527
	.data.w	.Ldw_str_begin+14157
	.data.b	221,21
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2337
	.section	.debug_loc		;off: 2337
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

	.section	.debug_info		;off: 18544
	.data.b	22
	.section	.debug_str		;off: 14164
	.data.b	74,111,98,0
	.section	.debug_info		;off: 18545
	.data.w	.Ldw_str_begin+14164
	.data.b	222,21
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+2367
	.section	.debug_loc		;off: 2367
	.data.w	.LDW16
	.data.w	.LDW26
	.data.b	1,0
	.data.b	81
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18562
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	7
	.section	.debug_str		;off: 14168
	.data.b	78,101,120,116,74,111,98,0
	.section	.debug_info		;off: 18572
	.data.w	.Ldw_str_begin+14168
	.data.b	225,21
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2397
	.section	.debug_loc		;off: 2397
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18590
	.data.b	7
	.section	.debug_str		;off: 14176
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18591
	.data.w	.Ldw_str_begin+14176
	.data.b	226,21
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2416
	.section	.debug_loc		;off: 2416
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18609
	.data.b	7
	.section	.debug_str		;off: 14186
	.data.b	83,101,113,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 18610
	.data.w	.Ldw_str_begin+14186
	.data.b	227,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2435
	.section	.debug_loc		;off: 2435
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18628
	.data.b	7
	.section	.debug_str		;off: 14198
	.data.b	78,101,120,116,74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18629
	.data.w	.Ldw_str_begin+14198
	.data.b	228,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2454
	.section	.debug_loc		;off: 2454
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18647
	.data.b	7
	.section	.debug_str		;off: 14212
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18648
	.data.w	.Ldw_str_begin+14212
	.data.b	229,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2473
	.section	.debug_loc		;off: 2473
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18666
	.data.b	7
	.section	.debug_str		;off: 14222
	.data.b	69,120,68,101,118,105,99,101,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18667
	.data.w	.Ldw_str_begin+14222
	.data.b	231,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+398
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2492
	.section	.debug_loc		;off: 2492
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18685
	.data.b	7
	.section	.debug_str		;off: 14237
	.data.b	84,114,105,103,103,101,114,68,109,97,70,108,97,103,0
	.section	.debug_info		;off: 18686
	.data.w	.Ldw_str_begin+14237
	.data.b	234,21
	.data.b	41
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2511
	.section	.debug_loc		;off: 2511
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	2,0
	.data.b	125
	.data.b	2
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18704
	.data.b	7
	.section	.debug_str		;off: 14252
	.data.b	83,112,105,80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 18705
	.data.w	.Ldw_str_begin+14252
	.data.b	235,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+465
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2531
	.section	.debug_loc		;off: 2531
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18723
	.data.b	7
	.section	.debug_str		;off: 14272
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18724
	.data.w	.Ldw_str_begin+14272
	.data.b	236,21
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+475
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2551
	.section	.debug_loc		;off: 2551
	.data.w	.LDW26
	.data.w	.LDW36
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18742
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14286
	.data.b	83,112,105,95,65,115,121,110,99,83,99,104,101,100,117,108,101,78,101,120,116,74,111,98,0
	.section	.debug_info		;off: 18745
	.data.w	.Ldw_str_begin+14286
	.data.b	139,24
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncScheduleNextJob
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncScheduleNextJob-Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4131
	.data.b	0,5,2
	.data.w	Spi_AsyncScheduleNextJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	143,24
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	28
	.data.b	27
	.data.b	29
	.data.b	77
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	48
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	61
	.data.b	3
	.data.b	40
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	61
	.data.b	13
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	3
	.data.b	83
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	92
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	45
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	13
	.data.b	11
	.data.b	91
	.data.b	12
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	13
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	29
	.data.b	43
	.data.b	13
	.data.b	125
	.data.b	43
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
	.section	.debug_info		;off: 18780
	.data.b	22
	.section	.debug_str		;off: 14311
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 18781
	.data.w	.Ldw_str_begin+14311
	.data.b	141,24
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2570
	.section	.debug_loc		;off: 2570
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	80
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18798
	.data.b	22
	.section	.debug_str		;off: 14318
	.data.b	74,111,98,0
	.section	.debug_info		;off: 18799
	.data.w	.Ldw_str_begin+14318
	.data.b	142,24
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+2600
	.section	.debug_loc		;off: 2600
	.data.w	.LDW46
	.data.w	.LDW56
	.data.b	1,0
	.data.b	81
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18816
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	7
	.section	.debug_str		;off: 14322
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 18826
	.data.w	.Ldw_str_begin+14322
	.data.b	145,24
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2630
	.section	.debug_loc		;off: 2630
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18844
	.data.b	7
	.section	.debug_str		;off: 14332
	.data.b	77,97,120,80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 18845
	.data.w	.Ldw_str_begin+14332
	.data.b	146,24
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2110
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2649
	.section	.debug_loc		;off: 2649
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18863
	.data.b	7
	.section	.debug_str		;off: 14344
	.data.b	74,111,98,76,105,115,116,72,101,97,100,80,116,114,0
	.section	.debug_info		;off: 18864
	.data.w	.Ldw_str_begin+14344
	.data.b	147,24
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+553
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2668
	.section	.debug_loc		;off: 2668
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18882
	.data.b	7
	.section	.debug_str		;off: 14359
	.data.b	83,112,105,80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 18883
	.data.w	.Ldw_str_begin+14359
	.data.b	148,24
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+558
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2687
	.section	.debug_loc		;off: 2687
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18901
	.data.b	8
	.section	.debug_str		;off: 14379
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18902
	.data.w	.Ldw_str_begin+14379
	.data.b	149,24
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14389
	.data.b	78,101,119,74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18917
	.data.w	.Ldw_str_begin+14389
	.data.b	150,24
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2706
	.section	.debug_loc		;off: 2706
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18935
	.data.b	7
	.section	.debug_str		;off: 14402
	.data.b	84,114,105,103,103,101,114,68,109,97,70,108,97,103,0
	.section	.debug_info		;off: 18936
	.data.w	.Ldw_str_begin+14402
	.data.b	152,24
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2725
	.section	.debug_loc		;off: 2725
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18954
	.data.b	7
	.section	.debug_str		;off: 14417
	.data.b	80,104,121,85,110,105,116,67,102,103,80,116,114,0
	.section	.debug_info		;off: 18955
	.data.w	.Ldw_str_begin+14417
	.data.b	153,24
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+475
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2744
	.section	.debug_loc		;off: 2744
	.data.w	.LDW56
	.data.w	.LDW66
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 18973
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14431
	.data.b	83,112,105,95,65,115,121,110,99,73,115,114,70,105,102,111,82,120,0
	.section	.debug_info		;off: 18976
	.data.w	.Ldw_str_begin+14431
	.data.b	161,25
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncIsrFifoRx
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncIsrFifoRx-Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4250
	.data.b	0,5,2
	.data.w	Spi_AsyncIsrFifoRx..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	165,25
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	16
	.data.b	2
	.data.b	52
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	60
	.data.b	28
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	107
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	111
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	77
	.data.b	59
	.data.b	12
	.data.b	91
	.data.b	12
	.data.b	28
	.data.b	60
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	91
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	43
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	107
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 19011
	.data.b	22
	.section	.debug_str		;off: 14450
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19012
	.data.w	.Ldw_str_begin+14450
	.data.b	163,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2763
	.section	.debug_loc		;off: 2763
	.data.w	.LDW76
	.data.w	.LDW86
	.data.b	1,0
	.data.b	80
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19029
	.data.b	22
	.section	.debug_str		;off: 14457
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 19030
	.data.w	.Ldw_str_begin+14457
	.data.b	164,25
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+2793
	.section	.debug_loc		;off: 2793
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

	.section	.debug_info		;off: 19047
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	7
	.section	.debug_str		;off: 14465
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19057
	.data.w	.Ldw_str_begin+14465
	.data.b	167,25
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2823
	.section	.debug_loc		;off: 2823
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19075
	.data.b	7
	.section	.debug_str		;off: 14475
	.data.b	82,120,66,117,102,73,110,100,101,120,0
	.section	.debug_info		;off: 19076
	.data.w	.Ldw_str_begin+14475
	.data.b	168,25
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2842
	.section	.debug_loc		;off: 2842
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19094
	.data.b	7
	.section	.debug_str		;off: 14486
	.data.b	84,101,109,112,82,120,66,117,102,102,101,114,0
	.section	.debug_info		;off: 19095
	.data.w	.Ldw_str_begin+14486
	.data.b	169,25
	.data.b	45
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2861
	.section	.debug_loc		;off: 2861
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19113
	.data.b	7
	.section	.debug_str		;off: 14499
	.data.b	68,101,118,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 19114
	.data.w	.Ldw_str_begin+14499
	.data.b	170,25
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+499
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2881
	.section	.debug_loc		;off: 2881
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19132
	.data.b	7
	.section	.debug_str		;off: 14511
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19133
	.data.w	.Ldw_str_begin+14511
	.data.b	171,25
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2900
	.section	.debug_loc		;off: 2900
	.data.w	.LDW86
	.data.w	.LDW96
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19151
	.data.b	8
	.section	.debug_str		;off: 14521
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19152
	.data.w	.Ldw_str_begin+14521
	.data.b	172,25
	.data.b	46
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 14535
	.data.b	83,112,105,95,65,115,121,110,99,85,110,108,111,99,107,82,101,109,97,105,110,105,110,103,74,111,98,115,0
	.section	.debug_info		;off: 19169
	.data.w	.Ldw_str_begin+14535
	.data.b	170,26
	.data.b	37
	.data.b	1
	.data.w	Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncUnlockRemainingJobs
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
	.data.w	Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_AsyncUnlockRemainingJobs-Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4346
	.data.b	0,5,2
	.data.w	Spi_AsyncUnlockRemainingJobs..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	174,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
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
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	188
	.data.b	61
	.data.b	107
	.data.b	13
	.data.b	12
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	109
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	21
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19200
	.data.b	22
	.section	.debug_str		;off: 14564
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19201
	.data.w	.Ldw_str_begin+14564
	.data.b	172,26
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+2919
	.section	.debug_loc		;off: 2919
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

	.section	.debug_info		;off: 19218
	.data.b	22
	.section	.debug_str		;off: 14571
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 19219
	.data.w	.Ldw_str_begin+14571
	.data.b	173,26
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+2949
	.section	.debug_loc		;off: 2949
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

	.section	.debug_info		;off: 19236
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	8
	.section	.debug_str		;off: 14580
	.data.b	74,111,98,73,100,120,0
	.section	.debug_info		;off: 19246
	.data.w	.Ldw_str_begin+14580
	.data.b	176,26
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14587
	.data.b	78,117,109,74,111,98,115,73,110,83,101,113,0
	.section	.debug_info		;off: 19261
	.data.w	.Ldw_str_begin+14587
	.data.b	177,26
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14600
	.data.b	83,101,113,83,116,97,116,117,115,80,116,114,0
	.section	.debug_info		;off: 19276
	.data.w	.Ldw_str_begin+14600
	.data.b	178,26
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+677
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14613
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19291
	.data.w	.Ldw_str_begin+14613
	.data.b	179,26
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2979
	.section	.debug_loc		;off: 2979
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19309
	.data.b	7
	.section	.debug_str		;off: 14623
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19310
	.data.w	.Ldw_str_begin+14623
	.data.b	180,26
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+349
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+2998
	.section	.debug_loc		;off: 2998
	.data.w	.LDW17
	.data.w	.LDW27
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19328
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14633
	.data.b	83,112,105,95,87,97,105,116,80,104,97,115,101,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19331
	.data.w	.Ldw_str_begin+14633
	.data.b	241,26
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_WaitPhaseStatus
	.data.b	1
	.data.b	93
	.data.b	240,152,1
	.data.b	108
	.data.b	0
	.data.b	28
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
	.data.w	Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_WaitPhaseStatus-Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4401
	.data.b	0,5,2
	.data.w	Spi_WaitPhaseStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	244,26
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	60
	.data.b	2
	.data.b	32
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	13
	.data.b	29
	.data.b	108
	.data.b	27
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	12
	.data.b	3
	.data.b	127
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	13
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 19366
	.data.b	22
	.section	.debug_str		;off: 14653
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 19367
	.data.w	.Ldw_str_begin+14653
	.data.b	243,26
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+3017
	.section	.debug_loc		;off: 3017
	.data.w	.LDW37
	.data.w	.LDW47
	.data.b	1,0
	.data.b	80
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19384
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

	.data.b	7
	.section	.debug_str		;off: 14661
	.data.b	82,101,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19394
	.data.w	.Ldw_str_begin+14661
	.data.b	246,26
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3048
	.section	.debug_loc		;off: 3048
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19412
	.data.b	7
	.section	.debug_str		;off: 14671
	.data.b	82,101,103,86,97,108,117,101,0
	.section	.debug_info		;off: 19413
	.data.w	.Ldw_str_begin+14671
	.data.b	247,26
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3067
	.section	.debug_loc		;off: 3067
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19431
	.data.b	7
	.section	.debug_str		;off: 14680
	.data.b	84,105,109,101,114,70,114,101,113,0
	.section	.debug_info		;off: 19432
	.data.w	.Ldw_str_begin+14680
	.data.b	248,26
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+70
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3086
	.section	.debug_loc		;off: 3086
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19450
	.data.b	7
	.section	.debug_str		;off: 14690
	.data.b	84,105,109,101,79,117,116,67,111,117,110,116,0
	.section	.debug_info		;off: 19451
	.data.w	.Ldw_str_begin+14690
	.data.b	249,26
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+70
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3105
	.section	.debug_loc		;off: 3105
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19469
	.data.b	7
	.section	.debug_str		;off: 14703
	.data.b	67,117,114,114,101,110,116,67,111,117,110,116,0
	.section	.debug_info		;off: 19470
	.data.w	.Ldw_str_begin+14703
	.data.b	250,26
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+70
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3124
	.section	.debug_loc		;off: 3124
	.data.w	.LDW47
	.data.w	.LDW57
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19488
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14716
	.data.b	83,112,105,95,71,101,116,68,97,116,97,84,111,116,97,108,78,117,109,79,102,74,111,98,0
	.section	.debug_info		;off: 19491
	.data.w	.Ldw_str_begin+14716
	.data.b	179,27
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.w	Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetDataTotalNumOfJob
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

	.section	.debug_frame		;off: 672
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_GetDataTotalNumOfJob-Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW87
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4482
	.data.b	0,5,2
	.data.w	Spi_GetDataTotalNumOfJob..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	183,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	172
	.data.b	28
	.data.b	45
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19526
	.data.b	22
	.section	.debug_str		;off: 14741
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19527
	.data.w	.Ldw_str_begin+14741
	.data.b	181,27
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+3143
	.section	.debug_loc		;off: 3143
	.data.w	.LDW67
	.data.w	.LDW77
	.data.b	1,0
	.data.b	80
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19544
	.data.b	22
	.section	.debug_str		;off: 14748
	.data.b	74,111,98,0
	.section	.debug_info		;off: 19545
	.data.w	.Ldw_str_begin+14748
	.data.b	182,27
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+3173
	.section	.debug_loc		;off: 3173
	.data.w	.LDW67
	.data.w	.LDW87
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19562
	.data.b	34
	.data.w	.LDW77
	.data.w	.LDW87

	.data.b	8
	.section	.debug_str		;off: 14752
	.data.b	67,104,73,110,100,101,120,0
	.section	.debug_info		;off: 19572
	.data.w	.Ldw_str_begin+14752
	.data.b	185,27
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14760
	.data.b	68,97,116,97,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 19587
	.data.w	.Ldw_str_begin+14760
	.data.b	186,27
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2134
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3192
	.section	.debug_loc		;off: 3192
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19605
	.data.b	7
	.section	.debug_str		;off: 14773
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 19606
	.data.w	.Ldw_str_begin+14773
	.data.b	187,27
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+378
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3211
	.section	.debug_loc		;off: 3211
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19624
	.data.b	7
	.section	.debug_str		;off: 14789
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19625
	.data.w	.Ldw_str_begin+14789
	.data.b	188,27
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3230
	.section	.debug_loc		;off: 3230
	.data.w	.LDW77
	.data.w	.LDW87
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19643
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 14799
	.data.b	83,112,105,95,73,115,114,69,114,114,111,114,0
	.section	.debug_info		;off: 19646
	.data.w	.Ldw_str_begin+14799
	.data.b	235,27
	.data.b	37
	.data.b	1
	.data.w	Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_IsrError
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

	.section	.debug_frame		;off: 696
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_IsrError-Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW18
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4520
	.data.b	0,5,2
	.data.w	Spi_IsrError..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	239,27
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	156
	.data.b	28
	.data.b	125
	.data.b	59
	.data.b	12
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	140
	.data.b	11
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	29
	.data.b	59
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	44
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	28
	.data.b	12
	.data.b	11
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19677
	.data.b	22
	.section	.debug_str		;off: 14812
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19678
	.data.w	.Ldw_str_begin+14812
	.data.b	237,27
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+3249
	.section	.debug_loc		;off: 3249
	.data.w	.LDW97
	.data.w	.LDW18
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19695
	.data.b	22
	.section	.debug_str		;off: 14819
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 19696
	.data.w	.Ldw_str_begin+14819
	.data.b	238,27
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+3268
	.section	.debug_loc		;off: 3268
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

	.section	.debug_info		;off: 19713
	.data.b	34
	.data.w	.LDW08
	.data.w	.LDW18

	.data.b	7
	.section	.debug_str		;off: 14827
	.data.b	82,101,103,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19723
	.data.w	.Ldw_str_begin+14827
	.data.b	241,27
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3298
	.section	.debug_loc		;off: 3298
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19741
	.data.b	7
	.section	.debug_str		;off: 14837
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 19742
	.data.w	.Ldw_str_begin+14837
	.data.b	242,27
	.data.b	34
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3317
	.section	.debug_loc		;off: 3317
	.data.w	.LDW08
	.data.w	.LDW18
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19760
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14847
	.data.b	83,112,105,95,73,110,105,116,68,114,105,118,101,114,0
	.section	.debug_info		;off: 19763
	.data.w	.Ldw_str_begin+14847
	.data.b	231,28
	.data.b	40
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.w	Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_InitDriver
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

	.section	.debug_frame		;off: 720
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_InitDriver-Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW48
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4592
	.data.b	0,5,2
	.data.w	Spi_InitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	235,28
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	13
	.data.b	6
	.data.b	3
	.data.b	24
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	114
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
	.data.b	29
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	28
	.data.b	3
	.data.b	106
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	44
	.data.b	43
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	41
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	76
	.data.b	12
	.data.b	75
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	45
	.data.b	29
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	172
	.data.b	13
	.data.b	43
	.data.b	12
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	100
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	29
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	184,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	201,0
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	13
	.data.b	61
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 19798
	.data.b	22
	.section	.debug_str		;off: 14862
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19799
	.data.w	.Ldw_str_begin+14862
	.data.b	233,28
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+3336
	.section	.debug_loc		;off: 3336
	.data.w	.LDW28
	.data.w	.LDW48
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19816
	.data.b	22
	.section	.debug_str		;off: 14869
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 19817
	.data.w	.Ldw_str_begin+14869
	.data.b	234,28
	.data.b	56
	.data.b	1
	.data.w	.Ldw_begin+734
	.data.b	0
	.data.w	.Ldw_loc_begin+3355
	.section	.debug_loc		;off: 3355
	.data.w	.LDW28
	.data.w	.LDW48
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19834
	.data.b	34
	.data.w	.LDW38
	.data.w	.LDW48

	.data.b	7
	.section	.debug_str		;off: 14879
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 19844
	.data.w	.Ldw_str_begin+14879
	.data.b	237,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3374
	.section	.debug_loc		;off: 3374
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19862
	.data.b	8
	.section	.debug_str		;off: 14889
	.data.b	74,111,98,73,110,100,101,120,0
	.section	.debug_info		;off: 19863
	.data.w	.Ldw_str_begin+14889
	.data.b	238,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14898
	.data.b	83,101,113,73,110,100,101,120,0
	.section	.debug_info		;off: 19878
	.data.w	.Ldw_str_begin+14898
	.data.b	239,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14907
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 19893
	.data.w	.Ldw_str_begin+14907
	.data.b	240,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3393
	.section	.debug_loc		;off: 3393
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19911
	.data.b	8
	.section	.debug_str		;off: 14920
	.data.b	69,120,68,101,118,78,111,0
	.section	.debug_info		;off: 19912
	.data.w	.Ldw_str_begin+14920
	.data.b	241,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11820
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 14928
	.data.b	80,114,105,111,114,105,116,121,0
	.section	.debug_info		;off: 19927
	.data.w	.Ldw_str_begin+14928
	.data.b	243,28
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 14937
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 19942
	.data.w	.Ldw_str_begin+14937
	.data.b	245,28
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3412
	.section	.debug_loc		;off: 3412
	.data.w	.LDW38
	.data.w	.LDW48
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 19960
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 14958
	.data.b	83,112,105,95,68,101,73,110,105,116,68,114,105,118,101,114,0
	.section	.debug_info		;off: 19963
	.data.w	.Ldw_str_begin+14958
	.data.b	153,30
	.data.b	47
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_DeInitDriver
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

	.section	.debug_frame		;off: 744
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.w	__ghs_eofn_Spi_DeInitDriver-Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	1
	.data.w	.LDW78
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4768
	.data.b	0,5,2
	.data.w	Spi_DeInitDriver..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CSpi.
	.data.b	6
	.data.b	3
	.data.b	156,30
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	28
	.data.b	44
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	43
	.data.b	12
	.data.b	157
	.data.b	43
	.data.b	27
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	96
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	32
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	3
	.data.b	33
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	123
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 19998
	.data.b	22
	.section	.debug_str		;off: 14975
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 19999
	.data.w	.Ldw_str_begin+14975
	.data.b	155,30
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.w	.Ldw_loc_begin+3431
	.section	.debug_loc		;off: 3431
	.data.w	.LDW58
	.data.w	.LDW68
	.data.b	1,0
	.data.b	80
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20016
	.data.b	34
	.data.w	.LDW68
	.data.w	.LDW78

	.data.b	7
	.section	.debug_str		;off: 14982
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20026
	.data.w	.Ldw_str_begin+14982
	.data.b	158,30
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3461
	.section	.debug_loc		;off: 3461
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20044
	.data.b	7
	.section	.debug_str		;off: 14992
	.data.b	82,101,115,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20045
	.data.w	.Ldw_str_begin+14992
	.data.b	159,30
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2541
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3480
	.section	.debug_loc		;off: 3480
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20063
	.data.b	8
	.section	.debug_str		;off: 15004
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 20064
	.data.w	.Ldw_str_begin+15004
	.data.b	160,30
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 15017
	.data.b	74,111,98,73,110,100,101,120,0
	.section	.debug_info		;off: 20079
	.data.w	.Ldw_str_begin+15017
	.data.b	161,30
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15026
	.data.b	83,101,113,73,110,100,101,120,0
	.section	.debug_info		;off: 20094
	.data.w	.Ldw_str_begin+15026
	.data.b	162,30
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3499
	.section	.debug_loc		;off: 3499
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20112
	.data.b	7
	.section	.debug_str		;off: 15035
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 20113
	.data.w	.Ldw_str_begin+15035
	.data.b	163,30
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3518
	.section	.debug_loc		;off: 3518
	.data.w	.LDW68
	.data.w	.LDW78
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20131
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15056
	.data.b	83,112,105,95,73,110,105,116,0
	.section	.debug_info		;off: 20134
	.data.w	.Ldw_str_begin+15056
	.data.b	145,31
	.data.b	29
	.data.b	1
	.data.w	Spi_Init
	.data.w	__ghs_eofn_Spi_Init
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

	.section	.debug_frame		;off: 768
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_Init
	.data.w	__ghs_eofn_Spi_Init-Spi_Init
	.data.b	1
	.data.w	.LDW09
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4894
	.data.b	0,5,2
	.data.w	Spi_Init
	.data.b	6
	.data.b	3
	.data.b	149,31
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	91
	.data.b	13
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	60
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	92
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	27
	.data.b	11
	.data.b	76
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20165
	.data.b	22
	.section	.debug_str		;off: 15065
	.data.b	67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 20166
	.data.w	.Ldw_str_begin+15065
	.data.b	148,31
	.data.b	56
	.data.b	1
	.data.w	.Ldw_begin+734
	.data.b	0
	.data.w	.Ldw_loc_begin+3537
	.section	.debug_loc		;off: 3537
	.data.w	.LDW88
	.data.w	.LDW09
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20183
	.data.b	34
	.data.w	.LDW98
	.data.w	.LDW09

	.data.b	8
	.section	.debug_str		;off: 15075
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20193
	.data.w	.Ldw_str_begin+15075
	.data.b	152,31
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15085
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20208
	.data.w	.Ldw_str_begin+15085
	.data.b	154,31
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3556
	.section	.debug_loc		;off: 3556
	.data.w	.LDW98
	.data.w	.LDW09
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20226
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15092
	.data.b	83,112,105,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 20229
	.data.w	.Ldw_str_begin+15092
	.data.b	241,31
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_DeInit
	.data.w	__ghs_eofn_Spi_DeInit
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

	.section	.debug_frame		;off: 792
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_DeInit
	.data.w	__ghs_eofn_Spi_DeInit-Spi_DeInit
	.data.b	1
	.data.w	.LDW39
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4968
	.data.b	0,5,2
	.data.w	Spi_DeInit
	.data.b	6
	.data.b	3
	.data.b	244,31
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
	.data.w	.LDWlin14
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	13
	.data.b	27
	.data.b	59
	.data.b	11
	.data.b	76
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	11
	.data.b	92
	.data.b	12
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	12
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	28
	.data.b	108
	.data.b	12
	.data.b	12
	.data.b	61
	.data.b	27
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
	.section	.debug_info		;off: 20264
	.data.b	34
	.data.w	.LDW29
	.data.w	.LDW39

	.data.b	7
	.section	.debug_str		;off: 15103
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20274
	.data.w	.Ldw_str_begin+15103
	.data.b	246,31
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3575
	.section	.debug_loc		;off: 3575
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20292
	.data.b	7
	.section	.debug_str		;off: 15110
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20293
	.data.w	.Ldw_str_begin+15110
	.data.b	247,31
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3594
	.section	.debug_loc		;off: 3594
	.data.w	.LDW29
	.data.w	.LDW39
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20311
	.data.b	8
	.section	.debug_str		;off: 15120
	.data.b	83,112,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20312
	.data.w	.Ldw_str_begin+15120
	.data.b	248,31
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15130
	.data.b	83,112,105,95,87,114,105,116,101,73,66,0
	.section	.debug_info		;off: 20329
	.data.w	.Ldw_str_begin+15130
	.data.b	228,32
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_WriteIB
	.data.w	__ghs_eofn_Spi_WriteIB
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
	.data.w	Spi_WriteIB
	.data.w	__ghs_eofn_Spi_WriteIB-Spi_WriteIB
	.data.b	1
	.data.w	.LDW69
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5057
	.data.b	0,5,2
	.data.w	Spi_WriteIB
	.data.b	6
	.data.b	3
	.data.b	233,32
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
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
	.data.b	75
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	123
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	109
	.data.b	12
	.data.b	12
	.data.b	28
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	27
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20364
	.data.b	22
	.section	.debug_str		;off: 15142
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 20365
	.data.w	.Ldw_str_begin+15142
	.data.b	230,32
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.w	.Ldw_loc_begin+3613
	.section	.debug_loc		;off: 3613
	.data.w	.LDW49
	.data.w	.LDW59
	.data.b	1,0
	.data.b	80
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20382
	.data.b	22
	.section	.debug_str		;off: 15150
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 20383
	.data.w	.Ldw_str_begin+15150
	.data.b	232,32
	.data.b	60
	.data.b	1
	.data.w	.Ldw_begin+792
	.data.b	0
	.data.w	.Ldw_loc_begin+3643
	.section	.debug_loc		;off: 3643
	.data.w	.LDW49
	.data.w	.LDW59
	.data.b	1,0
	.data.b	81
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20400
	.data.b	34
	.data.w	.LDW59
	.data.w	.LDW69

	.data.b	7
	.section	.debug_str		;off: 15164
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20410
	.data.w	.Ldw_str_begin+15164
	.data.b	235,32
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3673
	.section	.debug_loc		;off: 3673
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20428
	.data.b	7
	.section	.debug_str		;off: 15171
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20429
	.data.w	.Ldw_str_begin+15171
	.data.b	236,32
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3692
	.section	.debug_loc		;off: 3692
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20447
	.data.b	7
	.section	.debug_str		;off: 15181
	.data.b	68,97,116,97,73,110,100,101,120,0
	.section	.debug_info		;off: 20448
	.data.w	.Ldw_str_begin+15181
	.data.b	237,32
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3711
	.section	.debug_loc		;off: 3711
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20466
	.data.b	7
	.section	.debug_str		;off: 15191
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 20467
	.data.w	.Ldw_str_begin+15191
	.data.b	238,32
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3730
	.section	.debug_loc		;off: 3730
	.data.w	.LDW59
	.data.w	.LDW69
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20485
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15205
	.data.b	83,112,105,95,65,115,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 20488
	.data.w	.Ldw_str_begin+15205
	.data.b	236,33
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_AsyncTransmit
	.data.w	__ghs_eofn_Spi_AsyncTransmit
	.data.b	1
	.data.b	93
	.data.b	240,159,1
	.data.b	96
	.data.b	0
	.data.b	60
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
	.data.w	Spi_AsyncTransmit
	.data.w	__ghs_eofn_Spi_AsyncTransmit-Spi_AsyncTransmit
	.data.b	1
	.data.w	.LDW99
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5168
	.data.b	0,5,2
	.data.w	Spi_AsyncTransmit
	.data.b	6
	.data.b	3
	.data.b	239,33
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	19
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	13
	.data.b	59
	.data.b	60
	.data.b	13
	.data.b	108
	.data.b	29
	.data.b	28
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	188
	.data.b	91
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	124
	.data.b	59
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	101
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	29
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	43
	.data.b	11
	.data.b	108
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	29
	.data.b	155
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	12
	.data.b	12
	.data.b	60
	.data.b	27
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	108
	.data.b	3
	.data.b	24
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	99
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	3
	.data.b	119
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	13
	.data.b	44
	.data.b	44
	.data.b	28
	.data.b	28
	.data.b	28
	.data.b	3
	.data.b	17
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
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	28
	.data.b	77
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 20523
	.data.b	22
	.section	.debug_str		;off: 15223
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 20524
	.data.w	.Ldw_str_begin+15223
	.data.b	238,33
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+3749
	.section	.debug_loc		;off: 3749
	.data.w	.LDW79
	.data.w	.LDW89
	.data.b	1,0
	.data.b	80
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20541
	.data.b	34
	.data.w	.LDW89
	.data.w	.LDW99

	.data.b	7
	.section	.debug_str		;off: 15232
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 20551
	.data.w	.Ldw_str_begin+15232
	.data.b	241,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3779
	.section	.debug_loc		;off: 3779
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	2,0
	.data.b	125
	.data.b	11
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20569
	.data.b	7
	.section	.debug_str		;off: 15242
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20570
	.data.w	.Ldw_str_begin+15242
	.data.b	242,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3799
	.section	.debug_loc		;off: 3799
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20588
	.data.b	7
	.section	.debug_str		;off: 15249
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20589
	.data.w	.Ldw_str_begin+15249
	.data.b	243,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3818
	.section	.debug_loc		;off: 3818
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20607
	.data.b	7
	.section	.debug_str		;off: 15259
	.data.b	78,117,109,74,111,98,115,73,110,83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 20608
	.data.w	.Ldw_str_begin+15259
	.data.b	244,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3837
	.section	.debug_loc		;off: 3837
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20626
	.data.b	7
	.section	.debug_str		;off: 15277
	.data.b	74,111,98,73,100,120,0
	.section	.debug_info		;off: 20627
	.data.w	.Ldw_str_begin+15277
	.data.b	245,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3856
	.section	.debug_loc		;off: 3856
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20645
	.data.b	7
	.section	.debug_str		;off: 15284
	.data.b	83,101,113,83,116,97,116,101,80,116,114,0
	.section	.debug_info		;off: 20646
	.data.w	.Ldw_str_begin+15284
	.data.b	246,33
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3875
	.section	.debug_loc		;off: 3875
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20664
	.data.b	7
	.section	.debug_str		;off: 15296
	.data.b	74,111,98,73,110,100,101,120,80,116,114,0
	.section	.debug_info		;off: 20665
	.data.w	.Ldw_str_begin+15296
	.data.b	247,33
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+339
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3894
	.section	.debug_loc		;off: 3894
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20683
	.data.b	7
	.section	.debug_str		;off: 15308
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 20684
	.data.w	.Ldw_str_begin+15308
	.data.b	248,33
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+349
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3913
	.section	.debug_loc		;off: 3913
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20702
	.data.b	7
	.section	.debug_str		;off: 15318
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 20703
	.data.w	.Ldw_str_begin+15318
	.data.b	250,33
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3932
	.section	.debug_loc		;off: 3932
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20721
	.data.b	8
	.section	.debug_str		;off: 15328
	.data.b	67,104,97,110,110,101,108,73,100,120,0
	.section	.debug_info		;off: 20722
	.data.w	.Ldw_str_begin+15328
	.data.b	252,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15339
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 20737
	.data.w	.Ldw_str_begin+15339
	.data.b	253,33
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3951
	.section	.debug_loc		;off: 3951
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20755
	.data.b	7
	.section	.debug_str		;off: 15353
	.data.b	69,114,114,111,114,70,108,97,103,0
	.section	.debug_info		;off: 20756
	.data.w	.Ldw_str_begin+15353
	.data.b	255,33
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+3970
	.section	.debug_loc		;off: 3970
	.data.w	.LDW89
	.data.w	.LDW99
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20774
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15363
	.data.b	83,112,105,95,82,101,97,100,73,66,0
	.section	.debug_info		;off: 20777
	.data.w	.Ldw_str_begin+15363
	.data.b	212,35
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_ReadIB
	.data.w	__ghs_eofn_Spi_ReadIB
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

	.section	.debug_frame		;off: 864
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_ReadIB
	.data.w	__ghs_eofn_Spi_ReadIB-Spi_ReadIB
	.data.b	1
	.data.w	.LDW201
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5364
	.data.b	0,5,2
	.data.w	Spi_ReadIB
	.data.b	6
	.data.b	3
	.data.b	217,35
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
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
	.data.b	76
	.data.b	75
	.data.b	12
	.data.b	92
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	123
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	109
	.data.b	12
	.data.b	12
	.data.b	28
	.data.b	2
	.data.b	4
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	124
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 20812
	.data.b	22
	.section	.debug_str		;off: 15374
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 20813
	.data.w	.Ldw_str_begin+15374
	.data.b	214,35
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.w	.Ldw_loc_begin+3989
	.section	.debug_loc		;off: 3989
	.data.w	.LDW001
	.data.w	.LDW101
	.data.b	1,0
	.data.b	80
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20830
	.data.b	22
	.section	.debug_str		;off: 15382
	.data.b	68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 20831
	.data.w	.Ldw_str_begin+15382
	.data.b	216,35
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+829
	.data.b	0
	.data.w	.Ldw_loc_begin+4019
	.section	.debug_loc		;off: 4019
	.data.w	.LDW001
	.data.w	.LDW101
	.data.b	1,0
	.data.b	81
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20848
	.data.b	34
	.data.w	.LDW101
	.data.w	.LDW201

	.data.b	7
	.section	.debug_str		;off: 15396
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 20858
	.data.w	.Ldw_str_begin+15396
	.data.b	219,35
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4049
	.section	.debug_loc		;off: 4049
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20876
	.data.b	7
	.section	.debug_str		;off: 15403
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 20877
	.data.w	.Ldw_str_begin+15403
	.data.b	220,35
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4068
	.section	.debug_loc		;off: 4068
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20895
	.data.b	7
	.section	.debug_str		;off: 15413
	.data.b	68,97,116,97,73,110,100,101,120,0
	.section	.debug_info		;off: 20896
	.data.w	.Ldw_str_begin+15413
	.data.b	221,35
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4087
	.section	.debug_loc		;off: 4087
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20914
	.data.b	7
	.section	.debug_str		;off: 15423
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 20915
	.data.w	.Ldw_str_begin+15423
	.data.b	222,35
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4106
	.section	.debug_loc		;off: 4106
	.data.w	.LDW101
	.data.w	.LDW201
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20933
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15437
	.data.b	83,112,105,95,83,101,116,117,112,69,66,0
	.section	.debug_info		;off: 20936
	.data.w	.Ldw_str_begin+15437
	.data.b	219,36
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_SetupEB
	.data.w	__ghs_eofn_Spi_SetupEB
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

	.section	.debug_frame		;off: 888
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_SetupEB
	.data.w	__ghs_eofn_Spi_SetupEB-Spi_SetupEB
	.data.b	1
	.data.w	.LDW501
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5465
	.data.b	0,5,2
	.data.w	Spi_SetupEB
	.data.b	6
	.data.b	3
	.data.b	227,36
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	13
	.data.b	75
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	123
	.data.b	91
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	45
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	11
	.data.b	28
	.data.b	109
	.data.b	12
	.data.b	12
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	44
	.data.b	27
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
	.section	.debug_info		;off: 20971
	.data.b	22
	.section	.debug_str		;off: 15449
	.data.b	67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 20972
	.data.w	.Ldw_str_begin+15449
	.data.b	221,36
	.data.b	21
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.w	.Ldw_loc_begin+4125
	.section	.debug_loc		;off: 4125
	.data.w	.LDW301
	.data.w	.LDW401
	.data.b	1,0
	.data.b	80
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 20989
	.data.b	22
	.section	.debug_str		;off: 15457
	.data.b	83,114,99,68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 20990
	.data.w	.Ldw_str_begin+15457
	.data.b	223,36
	.data.b	60
	.data.b	1
	.data.w	.Ldw_begin+792
	.data.b	0
	.data.w	.Ldw_loc_begin+4155
	.section	.debug_loc		;off: 4155
	.data.w	.LDW301
	.data.w	.LDW401
	.data.b	1,0
	.data.b	81
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	88
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21007
	.data.b	22
	.section	.debug_str		;off: 15474
	.data.b	68,101,115,68,97,116,97,66,117,102,102,101,114,80,116,114,0
	.section	.debug_info		;off: 21008
	.data.w	.Ldw_str_begin+15474
	.data.b	225,36
	.data.b	57
	.data.b	1
	.data.w	.Ldw_begin+829
	.data.b	0
	.data.w	.Ldw_loc_begin+4185
	.section	.debug_loc		;off: 4185
	.data.w	.LDW301
	.data.w	.LDW401
	.data.b	1,0
	.data.b	82
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21025
	.data.b	22
	.section	.debug_str		;off: 15491
	.data.b	76,101,110,103,116,104,0
	.section	.debug_info		;off: 21026
	.data.w	.Ldw_str_begin+15491
	.data.b	226,36
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+11760
	.data.b	0
	.data.w	.Ldw_loc_begin+4215
	.section	.debug_loc		;off: 4215
	.data.w	.LDW301
	.data.w	.LDW401
	.data.b	1,0
	.data.b	83
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21043
	.data.b	34
	.data.w	.LDW401
	.data.w	.LDW501

	.data.b	7
	.section	.debug_str		;off: 15498
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21053
	.data.w	.Ldw_str_begin+15498
	.data.b	229,36
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4245
	.section	.debug_loc		;off: 4245
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21071
	.data.b	7
	.section	.debug_str		;off: 15505
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21072
	.data.w	.Ldw_str_begin+15505
	.data.b	230,36
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4264
	.section	.debug_loc		;off: 4264
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21090
	.data.b	7
	.section	.debug_str		;off: 15515
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 21091
	.data.w	.Ldw_str_begin+15515
	.data.b	231,36
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4283
	.section	.debug_loc		;off: 4283
	.data.w	.LDW401
	.data.w	.LDW501
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21109
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15529
	.data.b	83,112,105,95,71,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21112
	.data.w	.Ldw_str_begin+15529
	.data.b	216,37
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.w	Spi_GetStatus
	.data.w	__ghs_eofn_Spi_GetStatus
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

	.section	.debug_frame		;off: 912
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetStatus
	.data.w	__ghs_eofn_Spi_GetStatus-Spi_GetStatus
	.data.b	1
	.data.w	.LDW801
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5564
	.data.b	0,5,2
	.data.w	Spi_GetStatus
	.data.b	6
	.data.b	3
	.data.b	219,37
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
	.data.w	.LDWlin24
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	12
	.data.b	27
	.data.b	60
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21147
	.data.b	34
	.data.w	.LDW701
	.data.w	.LDW801

	.data.b	7
	.section	.debug_str		;off: 15543
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21157
	.data.w	.Ldw_str_begin+15543
	.data.b	221,37
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4302
	.section	.debug_loc		;off: 4302
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21175
	.data.b	7
	.section	.debug_str		;off: 15550
	.data.b	83,112,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21176
	.data.w	.Ldw_str_begin+15550
	.data.b	222,37
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4321
	.section	.debug_loc		;off: 4321
	.data.w	.LDW701
	.data.w	.LDW801
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21194
	.data.b	8
	.section	.debug_str		;off: 15560
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21195
	.data.w	.Ldw_str_begin+15560
	.data.b	224,37
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15570
	.data.b	83,112,105,95,71,101,116,74,111,98,82,101,115,117,108,116,0
	.section	.debug_info		;off: 21212
	.data.w	.Ldw_str_begin+15570
	.data.b	158,38
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+11975
	.data.w	Spi_GetJobResult
	.data.w	__ghs_eofn_Spi_GetJobResult
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

	.section	.debug_frame		;off: 936
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetJobResult
	.data.w	__ghs_eofn_Spi_GetJobResult-Spi_GetJobResult
	.data.b	1
	.data.w	.LDW111
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5626
	.data.b	0,5,2
	.data.w	Spi_GetJobResult
	.data.b	6
	.data.b	3
	.data.b	161,38
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	187
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21247
	.data.b	22
	.section	.debug_str		;off: 15587
	.data.b	74,111,98,0
	.section	.debug_info		;off: 21248
	.data.w	.Ldw_str_begin+15587
	.data.b	160,38
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.w	.Ldw_loc_begin+4340
	.section	.debug_loc		;off: 4340
	.data.w	.LDW901
	.data.w	.LDW011
	.data.b	1,0
	.data.b	80
	.data.w	.LDW011
	.data.w	.LDW111
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21265
	.data.b	34
	.data.w	.LDW011
	.data.w	.LDW111

	.data.b	7
	.section	.debug_str		;off: 15591
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21275
	.data.w	.Ldw_str_begin+15591
	.data.b	163,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4370
	.section	.debug_loc		;off: 4370
	.data.w	.LDW011
	.data.w	.LDW111
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21293
	.data.b	7
	.section	.debug_str		;off: 15598
	.data.b	74,111,98,82,101,115,117,108,116,0
	.section	.debug_info		;off: 21294
	.data.w	.Ldw_str_begin+15598
	.data.b	164,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+11975
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4389
	.section	.debug_loc		;off: 4389
	.data.w	.LDW011
	.data.w	.LDW111
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21312
	.data.b	8
	.section	.debug_str		;off: 15608
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21313
	.data.w	.Ldw_str_begin+15608
	.data.b	166,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15618
	.data.b	83,112,105,95,71,101,116,83,101,113,117,101,110,99,101,82,101,115,117,108,116,0
	.section	.debug_info		;off: 21330
	.data.w	.Ldw_str_begin+15618
	.data.b	231,38
	.data.b	42
	.data.b	1
	.data.w	.Ldw_begin+12040
	.data.w	Spi_GetSequenceResult
	.data.w	__ghs_eofn_Spi_GetSequenceResult
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

	.section	.debug_frame		;off: 960
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetSequenceResult
	.data.w	__ghs_eofn_Spi_GetSequenceResult-Spi_GetSequenceResult
	.data.b	1
	.data.w	.LDW411
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5681
	.data.b	0,5,2
	.data.w	Spi_GetSequenceResult
	.data.b	6
	.data.b	3
	.data.b	234,38
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
	.data.w	.LDWlin27
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	28
	.data.b	13
	.data.b	139
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21365
	.data.b	22
	.section	.debug_str		;off: 15640
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 21366
	.data.w	.Ldw_str_begin+15640
	.data.b	233,38
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+4408
	.section	.debug_loc		;off: 4408
	.data.w	.LDW211
	.data.w	.LDW311
	.data.b	1,0
	.data.b	80
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21383
	.data.b	34
	.data.w	.LDW311
	.data.w	.LDW411

	.data.b	7
	.section	.debug_str		;off: 15649
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21393
	.data.w	.Ldw_str_begin+15649
	.data.b	236,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4438
	.section	.debug_loc		;off: 4438
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21411
	.data.b	7
	.section	.debug_str		;off: 15656
	.data.b	83,101,113,82,101,115,117,108,116,0
	.section	.debug_info		;off: 21412
	.data.w	.Ldw_str_begin+15656
	.data.b	237,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+12040
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4457
	.section	.debug_loc		;off: 4457
	.data.w	.LDW311
	.data.w	.LDW411
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21430
	.data.b	8
	.section	.debug_str		;off: 15666
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21431
	.data.w	.Ldw_str_begin+15666
	.data.b	239,38
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15676
	.data.b	83,112,105,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 21448
	.data.w	.Ldw_str_begin+15676
	.data.b	168,39
	.data.b	29
	.data.b	1
	.data.w	Spi_GetVersionInfo
	.data.w	__ghs_eofn_Spi_GetVersionInfo
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

	.section	.debug_frame		;off: 984
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetVersionInfo
	.data.w	__ghs_eofn_Spi_GetVersionInfo-Spi_GetVersionInfo
	.data.b	1
	.data.w	.LDW711
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5741
	.data.b	0,5,2
	.data.w	Spi_GetVersionInfo
	.data.b	6
	.data.b	3
	.data.b	178,39
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	27
	.data.b	11
	.data.b	76
	.data.b	13
	.data.b	12
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
	.section	.debug_info		;off: 21477
	.data.b	22
	.section	.debug_str		;off: 15695
	.data.b	86,101,114,115,105,111,110,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 21478
	.data.w	.Ldw_str_begin+15695
	.data.b	171,39
	.data.b	58
	.data.b	1
	.data.w	.Ldw_begin+917
	.data.b	0
	.data.w	.Ldw_loc_begin+4476
	.section	.debug_loc		;off: 4476
	.data.w	.LDW611
	.data.w	.LDW711
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21495
	.data.b	34
	.data.w	.LDW611
	.data.w	.LDW711

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15710
	.data.b	83,112,105,95,83,121,110,99,84,114,97,110,115,109,105,116,0
	.section	.debug_info		;off: 21507
	.data.w	.Ldw_str_begin+15710
	.data.b	246,39
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_SyncTransmit
	.data.w	__ghs_eofn_Spi_SyncTransmit
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

	.section	.debug_frame		;off: 1008
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_SyncTransmit
	.data.w	__ghs_eofn_Spi_SyncTransmit-Spi_SyncTransmit
	.data.b	1
	.data.w	.LDW021
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 5773
	.data.b	0,5,2
	.data.w	Spi_SyncTransmit
	.data.b	6
	.data.b	3
	.data.b	249,39
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	60
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	28
	.data.b	124
	.data.b	13
	.data.b	3
	.data.b	25
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	155
	.data.b	11
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	117
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	98
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	28
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	44
	.data.b	1
	.data.b	156
	.data.b	91
	.data.b	11
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	60
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	28
	.data.b	59
	.data.b	11
	.data.b	108
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	92
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	3
	.data.b	13
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	92
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	172
	.data.b	3
	.data.b	122
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	12
	.data.b	28
	.data.b	75
	.data.b	27
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	20
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	188
	.data.b	28
	.data.b	125
	.data.b	28
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	10
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
	.data.b	11
	.data.b	27
	.data.b	11
	.data.b	28
	.data.b	77
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 21542
	.data.b	22
	.section	.debug_str		;off: 15727
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 21543
	.data.w	.Ldw_str_begin+15727
	.data.b	248,39
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+4495
	.section	.debug_loc		;off: 4495
	.data.w	.LDW811
	.data.w	.LDW911
	.data.b	1,0
	.data.b	80
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	91
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21560
	.data.b	34
	.data.w	.LDW911
	.data.w	.LDW021

	.data.b	7
	.section	.debug_str		;off: 15736
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21570
	.data.w	.Ldw_str_begin+15736
	.data.b	251,39
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4525
	.section	.debug_loc		;off: 4525
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21588
	.data.b	7
	.section	.debug_str		;off: 15743
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 21589
	.data.w	.Ldw_str_begin+15743
	.data.b	252,39
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4544
	.section	.debug_loc		;off: 4544
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	89
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21607
	.data.b	7
	.section	.debug_str		;off: 15753
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21608
	.data.w	.Ldw_str_begin+15753
	.data.b	253,39
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4563
	.section	.debug_loc		;off: 4563
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21626
	.data.b	7
	.section	.debug_str		;off: 15763
	.data.b	74,111,98,73,110,100,101,120,0
	.section	.debug_info		;off: 21627
	.data.w	.Ldw_str_begin+15763
	.data.b	254,39
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11784
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4582
	.section	.debug_loc		;off: 4582
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21645
	.data.b	7
	.section	.debug_str		;off: 15772
	.data.b	74,111,98,67,102,103,80,116,114,0
	.section	.debug_info		;off: 21646
	.data.w	.Ldw_str_begin+15772
	.data.b	255,39
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+329
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4601
	.section	.debug_loc		;off: 4601
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21664
	.data.b	7
	.section	.debug_str		;off: 15782
	.data.b	83,101,113,67,102,103,80,116,114,0
	.section	.debug_info		;off: 21665
	.data.w	.Ldw_str_begin+15782
	.data.b	128,40
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+349
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4620
	.section	.debug_loc		;off: 4620
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21683
	.data.b	8
	.section	.debug_str		;off: 15792
	.data.b	67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 21684
	.data.w	.Ldw_str_begin+15792
	.data.b	131,40
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11772
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 15805
	.data.b	67,104,97,110,110,101,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 21699
	.data.w	.Ldw_str_begin+15805
	.data.b	132,40
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15819
	.data.b	69,114,114,111,114,70,108,97,103,0
	.section	.debug_info		;off: 21714
	.data.w	.Ldw_str_begin+15819
	.data.b	135,40
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2122
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4639
	.section	.debug_loc		;off: 4639
	.data.w	.LDW911
	.data.w	.LDW021
	.data.b	2,0
	.data.b	125
	.data.b	7
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21732
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15829
	.data.b	83,112,105,95,71,101,116,72,87,85,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21735
	.data.w	.Ldw_str_begin+15829
	.data.b	151,42
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.w	Spi_GetHWUnitStatus
	.data.w	__ghs_eofn_Spi_GetHWUnitStatus
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

	.section	.debug_frame		;off: 1032
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_GetHWUnitStatus
	.data.w	__ghs_eofn_Spi_GetHWUnitStatus-Spi_GetHWUnitStatus
	.data.b	1
	.data.w	.LDW321
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6019
	.data.b	0,5,2
	.data.w	Spi_GetHWUnitStatus
	.data.b	6
	.data.b	3
	.data.b	154,42
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
	.data.w	.LDWlin31
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	171
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21770
	.data.b	22
	.section	.debug_str		;off: 15849
	.data.b	72,87,85,110,105,116,0
	.section	.debug_info		;off: 21771
	.data.w	.Ldw_str_begin+15849
	.data.b	153,42
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+4659
	.section	.debug_loc		;off: 4659
	.data.w	.LDW121
	.data.w	.LDW221
	.data.b	1,0
	.data.b	80
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21788
	.data.b	34
	.data.w	.LDW221
	.data.w	.LDW321

	.data.b	7
	.section	.debug_str		;off: 15856
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21798
	.data.w	.Ldw_str_begin+15856
	.data.b	156,42
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4689
	.section	.debug_loc		;off: 4689
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21816
	.data.b	7
	.section	.debug_str		;off: 15863
	.data.b	80,104,121,85,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21817
	.data.w	.Ldw_str_begin+15863
	.data.b	157,42
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4708
	.section	.debug_loc		;off: 4708
	.data.w	.LDW221
	.data.w	.LDW321
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21835
	.data.b	8
	.section	.debug_str		;off: 15877
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21836
	.data.w	.Ldw_str_begin+15877
	.data.b	159,42
	.data.b	26
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 15887
	.data.b	83,112,105,95,67,97,110,99,101,108,0
	.section	.debug_info		;off: 21853
	.data.w	.Ldw_str_begin+15887
	.data.b	226,42
	.data.b	29
	.data.b	1
	.data.w	Spi_Cancel
	.data.w	__ghs_eofn_Spi_Cancel
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

	.section	.debug_frame		;off: 1056
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_Cancel
	.data.w	__ghs_eofn_Spi_Cancel-Spi_Cancel
	.data.b	1
	.data.w	.LDW621
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6083
	.data.b	0,5,2
	.data.w	Spi_Cancel
	.data.b	6
	.data.b	3
	.data.b	229,42
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
	.data.w	.LDWlin33
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	28
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	155
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21884
	.data.b	22
	.section	.debug_str		;off: 15898
	.data.b	83,101,113,117,101,110,99,101,0
	.section	.debug_info		;off: 21885
	.data.w	.Ldw_str_begin+15898
	.data.b	228,42
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+11796
	.data.b	0
	.data.w	.Ldw_loc_begin+4727
	.section	.debug_loc		;off: 4727
	.data.w	.LDW421
	.data.w	.LDW521
	.data.b	1,0
	.data.b	80
	.data.w	.LDW521
	.data.w	.LDW621
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21902
	.data.b	34
	.data.w	.LDW521
	.data.w	.LDW621

	.data.b	7
	.section	.debug_str		;off: 15907
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 21912
	.data.w	.Ldw_str_begin+15907
	.data.b	231,42
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4757
	.section	.debug_loc		;off: 4757
	.data.w	.LDW521
	.data.w	.LDW621
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 21930
	.data.b	8
	.section	.debug_str		;off: 15914
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 21931
	.data.w	.Ldw_str_begin+15914
	.data.b	233,42
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 15924
	.data.b	83,112,105,95,83,101,116,65,115,121,110,99,77,111,100,101,0
	.section	.debug_info		;off: 21948
	.data.w	.Ldw_str_begin+15924
	.data.b	165,43
	.data.b	39
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.w	Spi_SetAsyncMode
	.data.w	__ghs_eofn_Spi_SetAsyncMode
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

	.section	.debug_frame		;off: 1080
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_SetAsyncMode
	.data.w	__ghs_eofn_Spi_SetAsyncMode-Spi_SetAsyncMode
	.data.b	1
	.data.w	.LDW921
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6141
	.data.b	0,5,2
	.data.w	Spi_SetAsyncMode
	.data.b	6
	.data.b	3
	.data.b	168,43
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin36
	.data.b	13
	.data.b	59
	.data.b	44
	.data.b	12
	.data.b	28
	.data.b	60
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	108
	.data.b	12
	.data.b	13
	.data.b	77
	.data.b	61
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	75
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 21983
	.data.b	22
	.section	.debug_str		;off: 15941
	.data.b	77,111,100,101,0
	.section	.debug_info		;off: 21984
	.data.w	.Ldw_str_begin+15941
	.data.b	167,43
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+12085
	.data.b	0
	.data.w	.Ldw_loc_begin+4776
	.section	.debug_loc		;off: 4776
	.data.w	.LDW721
	.data.w	.LDW821
	.data.b	1,0
	.data.b	80
	.data.w	.LDW821
	.data.w	.LDW921
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22001
	.data.b	34
	.data.w	.LDW821
	.data.w	.LDW921

	.data.b	7
	.section	.debug_str		;off: 15946
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22011
	.data.w	.Ldw_str_begin+15946
	.data.b	170,43
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4806
	.section	.debug_loc		;off: 4806
	.data.w	.LDW821
	.data.w	.LDW921
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22029
	.data.b	7
	.section	.debug_str		;off: 15953
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 22030
	.data.w	.Ldw_str_begin+15953
	.data.b	171,43
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4825
	.section	.debug_loc		;off: 4825
	.data.w	.LDW821
	.data.w	.LDW921
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22048
	.data.b	7
	.section	.debug_str		;off: 15963
	.data.b	83,112,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 22049
	.data.w	.Ldw_str_begin+15963
	.data.b	172,43
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11910
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4844
	.section	.debug_loc		;off: 4844
	.data.w	.LDW821
	.data.w	.LDW921
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22067
	.data.b	8
	.section	.debug_str		;off: 15973
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 22068
	.data.w	.Ldw_str_begin+15973
	.data.b	174,43
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 15986
	.data.b	67,117,114,114,101,110,116,67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 22083
	.data.w	.Ldw_str_begin+15986
	.data.b	175,43
	.data.b	38
	.data.b	1
	.data.w	.Ldw_begin+192
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4863
	.section	.debug_loc		;off: 4863
	.data.w	.LDW821
	.data.w	.LDW921
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22101
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16007
	.data.b	83,112,105,95,77,97,105,110,70,117,110,99,116,105,111,110,95,72,97,110,100,108,105,110,103,0
	.section	.debug_info		;off: 22104
	.data.w	.Ldw_str_begin+16007
	.data.b	146,44
	.data.b	29
	.data.b	1
	.data.w	Spi_MainFunction_Handling
	.data.w	__ghs_eofn_Spi_MainFunction_Handling
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

	.section	.debug_frame		;off: 1104
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_MainFunction_Handling
	.data.w	__ghs_eofn_Spi_MainFunction_Handling-Spi_MainFunction_Handling
	.data.b	1
	.data.w	.LDW231
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6241
	.data.b	0,5,2
	.data.w	Spi_MainFunction_Handling
	.data.b	6
	.data.b	3
	.data.b	149,44
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin37
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin38
	.data.b	13
	.data.b	43
	.data.b	44
	.data.b	11
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	123
	.data.b	12
	.data.b	92
	.data.b	60
	.data.b	93
	.data.b	43
	.data.b	13
	.data.b	59
	.data.b	27
	.data.b	11
	.data.b	76
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
	.data.b	96
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	124
	.data.b	3
	.data.b	31
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 22135
	.data.b	34
	.data.w	.LDW131
	.data.w	.LDW231

	.data.b	8
	.section	.debug_str		;off: 16033
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 22145
	.data.w	.Ldw_str_begin+16033
	.data.b	152,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16043
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22160
	.data.w	.Ldw_str_begin+16043
	.data.b	154,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4882
	.section	.debug_loc		;off: 4882
	.data.w	.LDW131
	.data.w	.LDW231
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22178
	.data.b	7
	.section	.debug_str		;off: 16050
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 22179
	.data.w	.Ldw_str_begin+16050
	.data.b	155,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4901
	.section	.debug_loc		;off: 4901
	.data.w	.LDW131
	.data.w	.LDW231
	.data.b	1,0
	.data.b	87
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22197
	.data.b	8
	.section	.debug_str		;off: 16058
	.data.b	80,104,121,85,110,105,116,73,110,100,101,120,0
	.section	.debug_info		;off: 22198
	.data.w	.Ldw_str_begin+16058
	.data.b	156,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 16071
	.data.b	73,115,80,111,108,108,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 22213
	.data.w	.Ldw_str_begin+16071
	.data.b	157,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2146
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16085
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 22228
	.data.w	.Ldw_str_begin+16085
	.data.b	159,44
	.data.b	29
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4920
	.section	.debug_loc		;off: 4920
	.data.w	.LDW131
	.data.w	.LDW231
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22246
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16095
	.data.b	83,112,105,95,70,105,102,111,82,120,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 22249
	.data.w	.Ldw_str_begin+16095
	.data.b	233,44
	.data.b	29
	.data.b	1
	.data.w	Spi_FifoRx_ISRHandler
	.data.w	__ghs_eofn_Spi_FifoRx_ISRHandler
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

	.section	.debug_frame		;off: 1128
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_FifoRx_ISRHandler
	.data.w	__ghs_eofn_Spi_FifoRx_ISRHandler-Spi_FifoRx_ISRHandler
	.data.b	1
	.data.w	.LDW531
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6330
	.data.b	0,5,2
	.data.w	Spi_FifoRx_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	236,44
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin39
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin40
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	44
	.data.b	13
	.data.b	59
	.data.b	27
	.data.b	11
	.data.b	76
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
	.section	.debug_info		;off: 22280
	.data.b	22
	.section	.debug_str		;off: 16117
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 22281
	.data.w	.Ldw_str_begin+16117
	.data.b	235,44
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+4939
	.section	.debug_loc		;off: 4939
	.data.w	.LDW331
	.data.w	.LDW431
	.data.b	1,0
	.data.b	80
	.data.w	.LDW431
	.data.w	.LDW531
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22298
	.data.b	34
	.data.w	.LDW431
	.data.w	.LDW531

	.data.b	8
	.section	.debug_str		;off: 16125
	.data.b	82,101,116,82,101,115,117,108,116,0
	.section	.debug_info		;off: 22308
	.data.w	.Ldw_str_begin+16125
	.data.b	239,44
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2098
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 16135
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22323
	.data.w	.Ldw_str_begin+16135
	.data.b	241,44
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+4969
	.section	.debug_loc		;off: 4969
	.data.w	.LDW431
	.data.w	.LDW531
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22341
	.data.b	8
	.section	.debug_str		;off: 16142
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 22342
	.data.w	.Ldw_str_begin+16142
	.data.b	244,44
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+2182
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 16152
	.data.b	83,112,105,95,69,114,114,111,114,95,73,83,82,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 22359
	.data.w	.Ldw_str_begin+16152
	.data.b	168,45
	.data.b	29
	.data.b	1
	.data.w	Spi_Error_ISRHandler
	.data.w	__ghs_eofn_Spi_Error_ISRHandler
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

	.section	.debug_frame		;off: 1152
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Spi_Error_ISRHandler
	.data.w	__ghs_eofn_Spi_Error_ISRHandler-Spi_Error_ISRHandler
	.data.b	1
	.data.w	.LDW831
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 6394
	.data.b	0,5,2
	.data.w	Spi_Error_ISRHandler
	.data.b	6
	.data.b	3
	.data.b	171,45
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin41
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	75
	.data.b	28
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 22390
	.data.b	22
	.section	.debug_str		;off: 16173
	.data.b	80,104,121,85,110,105,116,0
	.section	.debug_info		;off: 22391
	.data.w	.Ldw_str_begin+16173
	.data.b	170,45
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+11808
	.data.b	0
	.data.w	.Ldw_loc_begin+4988
	.section	.debug_loc		;off: 4988
	.data.w	.LDW631
	.data.w	.LDW731
	.data.b	1,0
	.data.b	80
	.data.w	.LDW731
	.data.w	.LDW831
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22408
	.data.b	34
	.data.w	.LDW731
	.data.w	.LDW831

	.data.b	7
	.section	.debug_str		;off: 16181
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 22418
	.data.w	.Ldw_str_begin+16181
	.data.b	173,45
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2361
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+5018
	.section	.debug_loc		;off: 5018
	.data.w	.LDW731
	.data.w	.LDW831
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 22436
	.data.b	8
	.section	.debug_str		;off: 16188
	.data.b	82,101,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 22437
	.data.w	.Ldw_str_begin+16188
	.data.b	175,45
	.data.b	33
	.data.b	1
	.data.w	.Ldw_begin+2182
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
	.data.b	66
	.data.b	2
	.data.b	3
	.data.b	32
	.data.b	3
	.data.b	1
	.data.b	34
	.data.b	83,80,73,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	35
	.data.b	83,80,73,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	36
	.data.b	83,80,73,95,67,70,71,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	38
	.data.b	83,80,73,95,67,70,71,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	39
	.data.b	83,80,73,95,67,70,71,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	40
	.data.b	83,80,73,95,67,70,71,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	42
	.data.b	83,80,73,95,67,70,71,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	43
	.data.b	83,80,73,95,67,70,71,95,77,79,68,85,76,69,95,73,68,32,40,56,51,85,41,0
	.data.b	1
	.data.b	47
	.data.b	83,80,73,95,85,83,65,71,69,48,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	49
	.data.b	83,80,73,95,85,83,65,71,69,49,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	51
	.data.b	83,80,73,95,85,83,65,71,69,50,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	55
	.data.b	83,80,73,95,76,69,86,69,76,48,32,40,48,120,48,48,85,41,0
	.data.b	1
	.data.b	57
	.data.b	83,80,73,95,76,69,86,69,76,49,32,40,48,120,48,49,85,41,0
	.data.b	1
	.data.b	59
	.data.b	83,80,73,95,76,69,86,69,76,50,32,40,48,120,48,50,85,41,0
	.data.b	1
	.data.b	67
	.data.b	83,80,73,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	75
	.data.b	83,80,73,95,83,65,70,69,84,89,95,69,78,65,66,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	80
	.data.b	83,80,73,95,68,69,77,95,82,69,80,79,82,84,95,69,82,82,79,82,95,83,84,65,84,85,83,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	86
	.data.b	83,80,73,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	94
	.data.b	83,80,73,95,72,87,95,83,84,65,84,85,83,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	100
	.data.b	83,80,73,95,67,65,78,67,69,76,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	121
	.data.b	83,80,73,95,69,78,65,66,76,69,95,68,77,65,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	137,1
	.data.b	83,80,73,95,73,78,84,69,82,82,85,80,84,73,66,76,69,95,83,69,81,95,65,76,76,79,87,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	144,1
	.data.b	83,80,73,95,67,85,83,84,79,77,73,90,69,68,95,67,83,95,69,78,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	155,1
	.data.b	83,80,73,95,67,72,65,78,78,69,76,95,66,85,70,70,69,82,83,95,65,76,76,79,87,69,68,32,40,83,80,73,95,85,83,65,71,69,50,41,0
	.data.b	1
	.data.b	167,1
	.data.b	83,80,73,95,76,69,86,69,76,95,68,69,76,73,86,69,82,69,68,32,40,83,80,73,95,76,69,86,69,76,50,41,0
	.data.b	1
	.data.b	173,1
	.data.b	83,80,73,95,84,73,77,69,79,85,84,95,85,83,32,40,49,48,48,48,85,76,76,41,0
	.data.b	1
	.data.b	187,1
	.data.b	83,80,73,95,74,79,66,95,80,82,73,79,82,73,84,89,95,76,69,86,69,76,83,95,67,79,85,78,84,32,40,52,85,41,0
	.data.b	1
	.data.b	190,1
	.data.b	83,80,73,95,67,79,78,70,73,71,95,67,79,85,78,84,32,40,49,85,41,0
	.data.b	1
	.data.b	194,1
	.data.b	83,80,73,95,77,65,88,95,83,69,81,85,69,78,67,69,95,67,79,82,69,48,32,40,49,85,41,0
	.data.b	1
	.data.b	197,1
	.data.b	83,80,73,95,77,65,88,95,83,69,81,85,69,78,67,69,95,67,79,82,69,49,32,40,49,85,41,0
	.data.b	1
	.data.b	200,1
	.data.b	83,80,73,95,77,65,88,95,72,87,85,78,73,84,95,67,79,82,69,48,32,40,49,85,41,0
	.data.b	1
	.data.b	202,1
	.data.b	83,80,73,95,77,65,88,95,72,87,85,78,73,84,95,67,79,82,69,49,32,40,49,85,41,0
	.data.b	1
	.data.b	204,1
	.data.b	83,80,73,95,77,65,88,95,72,87,85,78,73,84,95,67,79,82,69,50,32,40,48,85,41,0
	.data.b	1
	.data.b	206,1
	.data.b	83,80,73,95,77,65,88,95,72,87,85,78,73,84,95,67,79,82,69,51,32,40,48,85,41,0
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	4
	.data.b	3
	.data.b	27
	.data.b	5
	.data.b	3
	.data.b	36
	.data.b	6
	.data.b	3
	.data.b	39
	.data.b	7
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
	.data.b	239,4
	.data.b	70,76,65,83,72,95,80,70,76,65,83,72,95,73,78,84,69,82,78,65,76,84,79,68,69,86,73,67,69,95,65,68,68,82,95,79,70,70,83,69,84,32,40,48,120,56,56,52,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	243,4
	.data.b	70,76,65,83,72,95,80,70,76,65,83,72,95,73,78,84,69,82,78,65,76,65,68,68,82,95,77,65,83,75,86,65,76,85,69,32,40,48,120,70,70,48,48,48,48,48,48,85,76,76,41,0
	.data.b	1
	.data.b	247,4
	.data.b	70,76,65,83,72,95,80,70,76,65,83,72,95,73,78,84,69,82,78,65,76,65,68,68,82,95,67,79,77,80,86,65,76,85,69,32,40,48,120,48,56,48,48,48,48,48,48,85,76,76,41,0
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
	.data.b	137,1
	.data.b	77,99,97,108,95,71,101,116,83,121,115,116,101,109,84,105,109,101,114,70,114,101,113,40,41,32,82,99,99,95,72,97,108,95,71,101,116,83,116,109,67,108,107,70,114,101,113,40,41,0
	.data.b	1
	.data.b	140,1
	.data.b	77,99,97,108,95,71,101,116,83,121,115,116,101,109,84,105,109,101,114,67,111,117,110,116,40,41,32,83,116,109,95,72,97,108,95,71,101,116,86,97,108,117,101,40,41,0
	.data.b	1
	.data.b	191,1
	.data.b	77,67,65,76,95,80,70,76,65,83,72,95,65,68,68,82,95,73,78,84,69,82,78,65,76,84,79,68,69,86,73,67,69,40,65,100,100,114,101,115,115,41,32,40,40,70,76,65,83,72,95,80,70,76,65,83,72,95,73,78
	.data.b	84,69,82,78,65,76,65,68,68,82,95,67,79,77,80,86,65,76,85,69,32,61,61,32,40,40,65,100,100,114,101,115,115,41,32,38,32,70,76,65,83,72,95,80,70,76,65,83,72,95,73,78,84,69,82,78,65,76,65,68
	.data.b	68,82,95,77,65,83,75,86,65,76,85,69,41,41,32,63,32,40,40,65,100,100,114,101,115,115,41,32,43,32,70,76,65,83,72,95,80,70,76,65,83,72,95,73,78,84,69,82,78,65,76,84,79,68,69,86,73,67,69,95
	.data.b	65,68,68,82,95,79,70,70,83,69,84,41,32,58,32,40,65,100,100,114,101,115,115,41,41,0
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
	.data.b	39
	.data.b	34
	.data.b	3
	.data.b	32
	.data.b	35
	.data.b	3
	.data.b	26
	.data.b	36
	.data.b	4
	.data.b	1
	.data.b	217,3
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	218,3
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	220,3
	.data.b	69,83,80,73,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	162,5
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	163,5
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	55
	.data.b	69,83,80,73,95,73,78,84,67,95,70,76,65,71,95,80,65,82,73,84,89,95,69,82,82,79,82,32,40,48,120,49,85,41,0
	.data.b	1
	.data.b	57
	.data.b	69,83,80,73,95,73,78,84,67,95,70,76,65,71,95,85,78,69,88,80,69,67,84,95,67,70,71,95,69,82,82,79,82,32,40,48,120,50,85,41,0
	.data.b	1
	.data.b	61
	.data.b	69,83,80,73,95,73,78,84,67,95,70,76,65,71,95,84,88,95,79,86,70,95,69,82,82,79,82,32,40,48,120,56,85,41,0
	.data.b	1
	.data.b	65
	.data.b	69,83,80,73,95,73,78,84,67,95,70,76,65,71,95,82,88,95,79,86,70,95,69,82,82,79,82,32,40,48,120,50,48,85,41,0
	.data.b	1
	.data.b	75
	.data.b	69,83,80,73,95,73,78,84,67,95,70,76,65,71,95,82,88,32,40,48,120,52,48,48,85,41,0
	.data.b	1
	.data.b	90
	.data.b	69,83,80,73,95,83,82,83,84,66,95,83,69,84,32,40,48,120,49,48,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	94
	.data.b	69,83,80,73,95,73,78,84,67,95,65,76,76,95,69,82,82,79,82,95,70,76,65,71,83,32,40,48,120,49,51,70,85,41,0
	.data.b	1
	.data.b	111
	.data.b	69,83,80,73,95,80,72,65,83,69,95,70,76,65,71,95,87,65,73,84,32,40,48,120,48,85,41,0
	.data.b	1
	.data.b	123
	.data.b	69,83,80,73,95,80,72,65,83,69,95,70,76,65,71,95,69,88,80,69,67,84,32,40,48,120,54,48,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	129,1
	.data.b	69,83,80,73,95,80,72,65,83,69,95,65,76,76,95,70,76,65,71,83,32,40,48,120,70,48,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	135,1
	.data.b	69,83,80,73,95,65,76,76,95,70,76,65,71,83,95,82,87,95,83,84,65,84,69,83,32,40,48,120,55,70,70,70,70,85,41,0
	.data.b	1
	.data.b	144,1
	.data.b	69,83,80,73,95,84,88,70,95,70,76,65,71,95,83,69,84,32,40,48,120,49,85,41,0
	.data.b	1
	.data.b	216,1
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	217,1
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	236,4
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	237,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	38
	.data.b	3
	.data.b	36
	.data.b	39
	.data.b	3
	.data.b	40
	.data.b	40
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
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	41
	.data.b	3
	.data.b	41
	.data.b	42
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
	.data.b	43
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
	.data.b	43
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	44
	.data.b	1
	.data.b	47
	.data.b	68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	43
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
	.data.b	43
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
	.data.b	43
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
	.data.b	43
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	45
	.data.b	1
	.data.b	28
	.data.b	83,80,73,95,65,82,95,82,69,76,69,65,83,69,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	29
	.data.b	83,80,73,95,65,82,95,82,69,76,69,65,83,69,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,52,85,41,0
	.data.b	1
	.data.b	30
	.data.b	83,80,73,95,65,82,95,82,69,76,69,65,83,69,95,82,69,86,73,83,73,79,78,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	32
	.data.b	83,80,73,95,83,87,95,77,65,74,79,82,95,86,69,82,83,73,79,78,32,40,49,85,41,0
	.data.b	1
	.data.b	33
	.data.b	83,80,73,95,83,87,95,77,73,78,79,82,95,86,69,82,83,73,79,78,32,40,50,85,41,0
	.data.b	1
	.data.b	34
	.data.b	83,80,73,95,83,87,95,80,65,84,67,72,95,86,69,82,83,73,79,78,32,40,48,85,41,0
	.data.b	1
	.data.b	36
	.data.b	83,80,73,95,86,69,78,68,79,82,95,73,68,32,40,49,55,53,85,41,0
	.data.b	1
	.data.b	37
	.data.b	83,80,73,95,77,79,68,85,76,69,95,73,68,32,40,56,51,85,41,0
	.data.b	1
	.data.b	38
	.data.b	83,80,73,95,73,78,83,84,65,78,67,69,95,73,68,32,40,40,117,105,110,116,56,41,48,85,41,0
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,67,72,65,78,78,69,76,32,40,40,117,105,110,116,56,41,48,120,48,65,85,41,0
	.data.b	1
	.data.b	47
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,74,79,66,32,40,40,117,105,110,116,56,41,48,120,48,66,85,41,0
	.data.b	1
	.data.b	49
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,83,69,81,32,40,40,117,105,110,116,56,41,48,120,48,67,85,41,0
	.data.b	1
	.data.b	51
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,76,69,78,71,84,72,32,40,40,117,105,110,116,56,41,48,120,48,68,85,41,0
	.data.b	1
	.data.b	53
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,85,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,69,85,41,0
	.data.b	1
	.data.b	55
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,80,79,73,78,84,69,82,32,40,40,117,105,110,116,56,41,48,120,49,48,85,41,0
	.data.b	1
	.data.b	57
	.data.b	83,80,73,95,69,95,85,78,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,49,65,85,41,0
	.data.b	1
	.data.b	59
	.data.b	83,80,73,95,69,95,83,69,81,95,80,69,78,68,73,78,71,32,40,40,117,105,110,116,56,41,48,120,50,65,85,41,0
	.data.b	1
	.data.b	61
	.data.b	83,80,73,95,69,95,83,69,81,95,73,78,95,80,82,79,67,69,83,83,32,40,40,117,105,110,116,56,41,48,120,51,65,85,41,0
	.data.b	1
	.data.b	63
	.data.b	83,80,73,95,69,95,65,76,82,69,65,68,89,95,73,78,73,84,73,65,76,73,90,69,68,32,40,40,117,105,110,116,56,41,48,120,52,65,85,41,0
	.data.b	1
	.data.b	67
	.data.b	83,80,73,95,69,95,83,69,81,95,69,77,80,84,89,32,40,40,117,105,110,116,56,41,48,120,65,48,85,41,0
	.data.b	1
	.data.b	69
	.data.b	83,80,73,95,69,95,74,79,66,95,69,77,80,84,89,32,40,40,117,105,110,116,56,41,48,120,65,49,85,41,0
	.data.b	1
	.data.b	71
	.data.b	83,80,73,95,69,95,67,79,82,69,95,78,79,84,95,67,79,78,70,73,71,85,82,69,68,32,40,40,117,105,110,116,56,41,48,120,65,50,85,41,0
	.data.b	1
	.data.b	73
	.data.b	83,80,73,95,69,95,67,79,82,69,95,78,79,84,95,83,84,65,84,85,83,95,83,84,79,82,65,71,69,86,65,82,32,40,40,117,105,110,116,56,41,48,120,65,51,85,41,0
	.data.b	1
	.data.b	75
	.data.b	83,80,73,95,69,95,67,79,82,69,95,83,69,81,85,69,78,67,69,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,65,52,85,41,0
	.data.b	1
	.data.b	77
	.data.b	83,80,73,95,69,95,67,79,82,69,95,74,79,66,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,65,53,85,41,0
	.data.b	1
	.data.b	79
	.data.b	83,80,73,95,69,95,67,79,82,69,95,67,72,65,78,78,69,76,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,65,54,85,41,0
	.data.b	1
	.data.b	81
	.data.b	83,80,73,95,69,95,67,79,82,69,95,72,87,85,78,73,84,95,77,73,83,77,65,84,67,72,32,40,40,117,105,110,116,56,41,48,120,65,56,85,41,0
	.data.b	1
	.data.b	83
	.data.b	83,80,73,95,69,95,80,65,82,65,77,95,69,66,95,85,78,73,84,32,40,40,117,105,110,116,56,41,48,120,65,57,85,41,0
	.data.b	1
	.data.b	87
	.data.b	83,80,73,95,69,95,83,84,65,84,69,95,80,65,82,73,84,89,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,48,85,41,0
	.data.b	1
	.data.b	89
	.data.b	83,80,73,95,69,95,83,84,65,84,69,95,85,78,69,88,80,69,67,84,67,79,78,70,73,71,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,49,85,41,0
	.data.b	1
	.data.b	91
	.data.b	83,80,73,95,69,95,83,84,65,84,69,95,84,88,70,73,70,79,95,79,86,69,82,70,76,79,87,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,51,85,41,0
	.data.b	1
	.data.b	93
	.data.b	83,80,73,95,69,95,83,84,65,84,69,95,82,88,70,73,70,79,95,79,86,69,82,70,76,79,87,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,53,85,41,0
	.data.b	1
	.data.b	95
	.data.b	83,80,73,95,69,95,83,84,65,84,69,95,85,78,75,78,79,87,78,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,55,85,41,0
	.data.b	1
	.data.b	97
	.data.b	83,80,73,95,69,95,83,65,70,69,84,89,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,56,85,41,0
	.data.b	1
	.data.b	99
	.data.b	83,80,73,95,69,95,84,73,77,69,79,85,84,95,69,82,82,79,82,32,40,40,117,105,110,116,56,41,48,120,69,57,85,41,0
	.data.b	1
	.data.b	102
	.data.b	83,80,73,95,83,73,68,95,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,48,85,41,0
	.data.b	1
	.data.b	104
	.data.b	83,80,73,95,83,73,68,95,68,69,73,78,73,84,32,40,40,117,105,110,116,56,41,48,120,48,49,85,41,0
	.data.b	1
	.data.b	106
	.data.b	83,80,73,95,83,73,68,95,87,82,73,84,69,73,66,32,40,40,117,105,110,116,56,41,48,120,48,50,85,41,0
	.data.b	1
	.data.b	108
	.data.b	83,80,73,95,83,73,68,95,65,83,89,78,67,84,82,65,78,83,77,73,84,32,40,40,117,105,110,116,56,41,48,120,48,51,85,41,0
	.data.b	1
	.data.b	110
	.data.b	83,80,73,95,83,73,68,95,82,69,65,68,73,66,32,40,40,117,105,110,116,56,41,48,120,48,52,85,41,0
	.data.b	1
	.data.b	112
	.data.b	83,80,73,95,83,73,68,95,83,69,84,85,80,69,66,32,40,40,117,105,110,116,56,41,48,120,48,53,85,41,0
	.data.b	1
	.data.b	114
	.data.b	83,80,73,95,83,73,68,95,71,69,84,83,84,65,84,85,83,32,40,40,117,105,110,116,56,41,48,120,48,54,85,41,0
	.data.b	1
	.data.b	116
	.data.b	83,80,73,95,83,73,68,95,71,69,84,74,79,66,82,69,83,85,76,84,32,40,40,117,105,110,116,56,41,48,120,48,55,85,41,0
	.data.b	1
	.data.b	118
	.data.b	83,80,73,95,83,73,68,95,71,69,84,83,69,81,85,69,78,67,69,82,69,83,85,76,84,32,40,40,117,105,110,116,56,41,48,120,48,56,85,41,0
	.data.b	1
	.data.b	120
	.data.b	83,80,73,95,83,73,68,95,71,69,84,86,69,82,83,73,79,78,73,78,70,79,32,40,40,117,105,110,116,56,41,48,120,48,57,85,41,0
	.data.b	1
	.data.b	122
	.data.b	83,80,73,95,83,73,68,95,83,89,78,67,84,82,65,78,83,77,73,84,32,40,40,117,105,110,116,56,41,48,120,48,65,85,41,0
	.data.b	1
	.data.b	124
	.data.b	83,80,73,95,83,73,68,95,71,69,84,72,87,85,78,73,84,83,84,65,84,85,83,32,40,40,117,105,110,116,56,41,48,120,48,66,85,41,0
	.data.b	1
	.data.b	126
	.data.b	83,80,73,95,83,73,68,95,67,65,78,67,69,76,32,40,40,117,105,110,116,56,41,48,120,48,67,85,41,0
	.data.b	1
	.data.b	128,1
	.data.b	83,80,73,95,83,73,68,95,83,69,84,65,83,89,78,67,77,79,68,69,32,40,40,117,105,110,116,56,41,48,120,48,68,85,41,0
	.data.b	1
	.data.b	130,1
	.data.b	83,80,73,95,83,73,68,95,77,65,73,78,70,85,78,67,84,73,79,78,95,72,65,78,68,76,73,78,71,32,40,40,117,105,110,116,56,41,48,120,49,48,85,41,0
	.data.b	1
	.data.b	134,1
	.data.b	83,80,73,95,83,73,68,95,70,73,70,79,95,82,88,95,73,83,82,32,40,40,117,105,110,116,56,41,48,120,69,48,85,41,0
	.data.b	1
	.data.b	136,1
	.data.b	83,80,73,95,83,73,68,95,69,82,82,79,82,95,73,83,82,32,40,40,117,105,110,116,56,41,48,120,69,49,85,41,0
	.data.b	1
	.data.b	138,1
	.data.b	83,80,73,95,83,73,68,95,68,77,65,95,78,79,84,73,70,73,67,65,84,73,79,78,32,40,40,117,105,110,116,56,41,48,120,69,50,85,41,0
	.data.b	1
	.data.b	153,1
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	154,1
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	144,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	145,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	69
	.data.b	46
	.data.b	4
	.data.b	3
	.data.b	74
	.data.b	47
	.data.b	3
	.data.b	37
	.data.b	48
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	49
	.data.b	1
	.data.b	55
	.data.b	68,73,79,95,68,69,86,95,69,82,82,79,82,95,68,69,84,69,67,84,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	62
	.data.b	68,73,79,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	69
	.data.b	68,73,79,95,70,76,73,80,95,67,72,65,78,78,69,76,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	71
	.data.b	68,73,79,95,77,65,83,75,69,68,95,87,82,73,84,69,95,80,79,82,84,95,65,80,73,32,40,83,84,68,95,79,70,70,41,0
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	50
	.data.b	4
	.data.b	1
	.data.b	107
	.data.b	68,73,79,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	108
	.data.b	51
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,68,73,79,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	169,1
	.data.b	68,73,79,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	170,1
	.data.b	51
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	77
	.data.b	52
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
	.data.b	121
	.data.b	83,80,73,95,74,79,66,95,78,85,76,76,32,40,40,83,112,105,95,74,111,98,84,121,112,101,41,40,48,120,70,70,70,70,85,41,41,0
	.data.b	1
	.data.b	125
	.data.b	83,80,73,95,65,86,65,73,76,65,66,76,69,95,70,73,70,79,76,69,86,69,76,32,40,48,120,48,70,85,41,0
	.data.b	1
	.data.b	127
	.data.b	83,80,73,95,67,72,95,67,79,78,70,73,71,95,67,76,82,32,40,48,120,70,48,53,70,70,70,70,70,85,76,41,0
	.data.b	1
	.data.b	129,1
	.data.b	83,80,73,95,68,65,84,65,87,73,68,84,72,95,77,65,83,75,32,40,50,51,85,41,0
	.data.b	1
	.data.b	131,1
	.data.b	83,80,73,95,83,72,73,70,84,79,82,68,69,82,95,77,65,83,75,32,40,50,49,85,41,0
	.data.b	1
	.data.b	133,1
	.data.b	83,80,73,95,68,77,65,67,72,78,79,85,83,69,68,95,77,65,83,75,32,40,48,120,70,70,85,41,0
	.data.b	1
	.data.b	135,1
	.data.b	83,80,73,95,82,65,78,71,69,95,48,84,79,51,95,77,65,83,75,32,40,48,120,48,51,85,41,0
	.data.b	1
	.data.b	140,1
	.data.b	83,80,73,95,83,69,81,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,83,101,113,117,101,110,99,101,41,32,40,38,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110
	.data.b	102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,83,101,113,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,83,101,113,117,101,110,99,101,84,111,67,111,114,101,80,116,114,91,83
	.data.b	101,113,117,101,110,99,101,93,93,41,41,0
	.data.b	1
	.data.b	145,1
	.data.b	83,80,73,95,83,69,81,95,83,84,65,84,85,83,80,84,82,40,67,111,114,101,73,100,44,83,101,113,117,101,110,99,101,41,32,40,38,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93
	.data.b	45,62,83,101,113,117,101,110,99,101,83,116,97,116,117,115,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,83,101,113,117,101,110,99,101,84,111,67,111,114,101,80,116,114,91,83,101,113,117,101,110,99
	.data.b	101,93,93,41,41,0
	.data.b	1
	.data.b	150,1
	.data.b	83,80,73,95,83,69,81,95,83,84,65,84,85,83,40,67,111,114,101,73,100,44,83,101,113,117,101,110,99,101,41,32,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93,45,62,83,101,113
	.data.b	117,101,110,99,101,83,116,97,116,117,115,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,83,101,113,117,101,110,99,101,84,111,67,111,114,101,80,116,114,91,83,101,113,117,101,110,99,101,93,93,46,83
	.data.b	101,113,82,101,115,117,108,116,41,0
	.data.b	1
	.data.b	156,1
	.data.b	83,80,73,95,74,79,66,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,74,111,98,41,32,40,38,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116
	.data.b	114,91,67,111,114,101,73,100,93,45,62,74,111,98,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,74,111,98,84,111,67,111,114,101,80,116,114,91,40,74,111,98,41,93,93,41,41,0
	.data.b	1
	.data.b	161,1
	.data.b	83,80,73,95,67,85,82,74,79,66,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,80,104,121,85,110,105,116,41,32,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93
	.data.b	45,62,68,101,118,105,99,101,83,116,97,116,101,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,80,104,121,85,110,105,116,84,111,67,111,114,101,80,116,114,91,40,80,104,121,85,110,105,116,41,93,93
	.data.b	46,67,117,114,74,111,98,80,116,114,41,0
	.data.b	1
	.data.b	166,1
	.data.b	83,80,73,95,74,79,66,95,83,84,65,84,85,83,40,67,111,114,101,73,100,44,74,111,98,41,32,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105,103,80,116,114,91,67,111,114
	.data.b	101,73,100,93,45,62,74,111,98,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,74,111,98,84,111,67,111,114,101,80,116,114,91,40,74,111,98,41,93,93,46,74,111,98,83,116,97,116,101
	.data.b	80,116,114,45,62,74,111,98,82,101,115,117,108,116,41,0
	.data.b	1
	.data.b	172,1
	.data.b	83,80,73,95,67,72,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,67,104,97,110,110,101,108,41,32,40,38,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110,102,105
	.data.b	103,80,116,114,91,67,111,114,101,73,100,93,45,62,67,104,97,110,110,101,108,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,104,97,110,110,101,108,84,111,67,111,114,101,80,116,114,91
	.data.b	40,67,104,97,110,110,101,108,41,93,93,41,41,0
	.data.b	1
	.data.b	177,1
	.data.b	83,80,73,95,69,88,68,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,69,120,68,101,118,105,99,101,41,32,40,38,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67,111,110
	.data.b	102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,69,120,68,101,118,105,99,101,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,69,120,68,101,118,105,99,101,84,111,67,111,114,101
	.data.b	80,116,114,91,40,69,120,68,101,118,105,99,101,41,93,93,41,41,0
	.data.b	1
	.data.b	182,1
	.data.b	83,80,73,95,69,88,68,95,83,84,65,84,85,83,80,84,82,40,67,111,114,101,73,100,44,80,104,121,85,110,105,116,41,32,40,38,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93,45
	.data.b	62,68,101,118,105,99,101,83,116,97,116,101,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,80,104,121,85,110,105,116,84,111,67,111,114,101,80,116,114,91,40,80,104,121,85,110,105,116,41,93,93,41
	.data.b	41,0
	.data.b	1
	.data.b	188,1
	.data.b	83,80,73,95,72,87,85,78,73,84,95,67,79,78,70,73,71,80,84,82,40,67,111,114,101,73,100,44,80,104,121,85,110,105,116,41,32,40,38,40,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,67,111,114,101,67
	.data.b	111,110,102,105,103,80,116,114,91,67,111,114,101,73,100,93,45,62,80,104,121,85,110,105,116,67,102,103,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,80,104,121,85,110,105,116,84,111,67,111,114,101
	.data.b	80,116,114,91,40,80,104,121,85,110,105,116,41,93,93,41,41,0
	.data.b	1
	.data.b	193,1
	.data.b	83,80,73,95,72,87,85,78,73,84,95,83,84,65,84,85,83,80,84,82,40,67,111,114,101,73,100,44,80,104,121,85,110,105,116,41,32,40,38,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73
	.data.b	100,93,45,62,80,104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,80,104,121,85,110,105,116,84,111,67,111,114,101,80,116,114,91,40,80,104,121,85,110,105
	.data.b	116,41,93,93,41,41,0
	.data.b	1
	.data.b	198,1
	.data.b	83,80,73,95,72,87,85,78,73,84,95,83,84,65,84,85,83,40,67,111,114,101,73,100,44,80,104,121,85,110,105,116,41,32,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93,45,62,80
	.data.b	104,121,85,110,105,116,83,116,97,116,117,115,80,116,114,91,83,112,105,95,67,111,110,102,105,103,80,116,114,45,62,80,104,121,85,110,105,116,84,111,67,111,114,101,80,116,114,91,40,80,104,121,85,110,105,116,41,93,93,46
	.data.b	80,104,121,85,110,105,116,83,116,97,116,117,115,41,0
	.data.b	1
	.data.b	204,1
	.data.b	83,80,73,95,65,83,89,78,67,95,77,79,68,69,40,67,111,114,101,73,100,41,32,40,42,40,83,112,105,95,67,111,114,101,83,116,97,116,117,115,91,67,111,114,101,73,100,93,45,62,65,115,121,110,99,77,111,100,101,41
	.data.b	41,0
	.data.b	1
	.data.b	211,1
	.data.b	83,80,73,95,69,78,84,69,82,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,110,116,101,114,95,83,112,105,95,32,35
	.data.b	35,32,69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	214,1
	.data.b	83,80,73,95,69,88,73,84,95,67,82,73,84,73,67,65,76,95,83,69,67,84,73,79,78,40,69,120,99,108,117,115,105,118,101,95,65,114,101,97,41,32,83,99,104,77,95,69,120,105,116,95,83,112,105,95,32,35,35,32
	.data.b	69,120,99,108,117,115,105,118,101,95,65,114,101,97,40,41,0
	.data.b	1
	.data.b	222,1
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	223,1
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	239,1
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	241,1
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	129,2
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	131,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	186,33
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	189,33
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	134,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	136,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	140,2
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	142,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	217,29
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	220,29
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	160,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	162,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	171,2
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	173,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	189,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	191,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	206,2
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	208,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	211,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	213,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	217,2
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	219,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	140,38
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	143,38
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	238,2
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	240,2
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	145,4
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69
	.data.b	65,66,76,69,32,0
	.data.b	3
	.data.b	147,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	142,10
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78
	.data.b	79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	145,10
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	156,4
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	158,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	167,4
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	169,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	203,2
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	206,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	211,4
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	213,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	222,4
	.data.b	83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	224,4
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,83,80,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	193,45
	.data.b	83,80,73,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	195,45
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 478
	.data.b	0
