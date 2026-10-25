	.section ".sdk_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Citmu...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257A..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
__callee.Itmu_ClearModuleRam.i.ii::
	.size	__callee.Itmu_ClearModuleRam.i.ii,0
Itmu_ClearModuleRam::
.LDW01:
	push	{r4-r7,r10,lr}
.LDW11:
	ldr	r3,.L244
	ldr	r2,.L245
	cmp	r0,0
	mov	r0,1
	and	r12,r1,r3
	movw	r3,0x5555
	add	r10,r2,4
	add	r4,r2,184
	andne	r12,r1,r3
	movw	r3,0xffff
	addne	r10,r2,188
	ldreq	r4,.L245
	mvneq	r3,63<<26
	str	r12,[r10]
	and	r2,r3,r1
	mov	r6,0
	str	r2,[r4]
	b	.L246

.L244:	.data.w	0x01555555
	.endo	.L244

.L245:	.data.w	0xb0330c50
	.endo	.L245

.L246:

;line159
..lin.fb6c4027..7db1b8b0.0_1::
.LDWlin1:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
MRRC p15, 0, r2, r6, c14

..gh.endasm.2:
	.endo	..gh.endasm.2

	movw	r1,0xffff
	mov	r7,0
	adds	r4,r2,r1
	mov	r1,r0
;line161
..lin.fb6c4027..7db1b8b0.0_2::
.LDWlin2:
	adc	r5,r6,0
.L52:
	mov	r3,r7
..gh.beginasm.3:
	.endo	..gh.beginasm.3
MRRC p15, 0, r7, r3, c14

..gh.endasm.4:
	.endo	..gh.endasm.4

	ldr	r6,[r10]
	mov	r2,r7
;line165
..lin.fb6c4027..7db1b8b0.0_3::
.LDWlin3:
	and	r6,r12,r6
	mov	r7,0
	cmp	r6,r12
	moveq	r1,r7
	cmp	r3,r5
	cmpeq	r2,r4
	bhs	.L47
	cmp	r1,1
	beq	.L52
.L47:
	cmp	r1,0
	movne	r0,r7
.L39:
.LDW21:
.L247:

	pop	{r4-r7,r10,pc}
__ghs_eofn_Itmu_ClearModuleRam::
	.endf	Itmu_ClearModuleRam
;ret	r0	local
;status	r1	local
;endTime	r4	local
;curTime	r2	local
;ramIniStatus	r12	local
;raministsRegAddr	r10	local
;raminictrlRegAddr	r4	local
;raminictrlMask	r3	local
;value	r2	local
;value	r2	local

;index	r2	param
;clearBits	r1	param

	.section ".bss","awb"
.L162:
	.endo	.L162
	.section ".ghrettbl",""
	.align	4
.L248:	.data.w	.L247
	.endo	.L248
	.section ".sdk_text_asil_d","ax"
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
__callee.Itmu_InitRamOnSysReset.i.i::
	.size	__callee.Itmu_InitRamOnSysReset.i.i,0
Itmu_InitRamOnSysReset::
.LDW31:
	mov	r1,r0
.LDW41:
	ldr	r0,.L336
	str	r1,[r0]
	ldr	r2,[r0]
	cmp	r1,r2
	movne	r0,0
	moveq	r0,1
.LDW51:
.L337:

	ret	
__ghs_eofn_Itmu_InitRamOnSysReset::
	.endf	Itmu_InitRamOnSysReset
;ret	r0	local

;ramIniOnSysReset	r1	param

	.section ".bss","awb"
.L300:
	.endo	.L300
	.section ".ghrettbl",""
.L338:	.data.w	.L337
	.endo	.L338
	.section ".sdk_text_asil_d","ax"

.L336:	.data.w	0xb0330c4c
	.endo	.L336


	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Citmu...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257A..0::
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	31,5,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,116,109,117,92,115,114,99,47,105,116,109,117,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 28
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+28
	.section	.debug_str		;off: 172
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+172
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
	.data.b	163,2,0,0
	.data.b	2,0
	.data.b	54,2,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,116,109,117,92,115,114,99,47,105,116,109,117,46,99,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,115,116,109,92,105,110,99,92,115,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,116,109,117,92,105,110,99,92,105,116,109,117,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,73,116,109,117,95,77,101,109,77,97,112,46,104,0
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
	.section	.debug_str		;off: 194
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 36
	.data.w	.Ldw_str_begin+194
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
	.section	.debug_str		;off: 208
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+208
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 222
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 50
	.data.w	.Ldw_str_begin+222
	.data.b	7
	.data.b	8

	.data.b	74
	.data.w	.Ldw_begin+232
	.data.b	1

	.section	.debug_abbrev		;off: 30
	.data.b	74
	.data.b	21
	.data.b	1
	.data.b	73,16
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 62
	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+232

	.section	.debug_abbrev		;off: 39
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 68
	.data.b	74
	.data.w	.Ldw_begin+208
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+208
	.data.b	0

	.section	.debug_abbrev		;off: 46
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 80
	.data.b	23
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+208
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+208
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+815
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 241
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 126
	.data.w	.Ldw_str_begin+241
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 254
	.data.b	105,110,116,0
	.section	.debug_info		;off: 133
	.data.w	.Ldw_str_begin+254
	.data.b	5
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	20
	.data.w	.Ldw_begin+220

	.section	.debug_abbrev		;off: 55
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 146
	.data.b	56
	.data.w	.Ldw_begin+132
	.data.b	4
	.data.b	0
	.data.b	4

	.section	.debug_abbrev		;off: 66
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 154
	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	12
	.data.w	.Ldw_begin+220

	.data.b	56
	.data.w	.Ldw_begin+132
	.data.b	4
	.data.b	0
	.data.b	2

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+220

	.data.b	56
	.data.w	.Ldw_begin+132
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	120
	.data.w	.Ldw_begin+220

	.data.b	56
	.data.w	.Ldw_begin+132
	.data.b	4
	.data.b	0
	.data.b	29

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+244

	.data.b	45
	.section	.debug_str		;off: 258
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 209
	.data.w	.Ldw_str_begin+258
	.data.b	51
	.data.b	29
	.data.b	2
	.data.w	.Ldw_begin+35

	.section	.debug_abbrev		;off: 79
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 220
	.data.b	45
	.section	.debug_str		;off: 266
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 221
	.data.w	.Ldw_str_begin+266
	.data.b	64
	.data.b	29
	.data.b	2
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 273
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 233
	.data.w	.Ldw_str_begin+273
	.data.b	68
	.data.b	29
	.data.b	2
	.data.w	.Ldw_begin+49

	.data.b	71
	.data.b	35
	.data.b	1
	.data.b	13
	.data.b	144,2
	.data.b	1

	.section	.debug_abbrev		;off: 94
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 251
	.data.b	40
	.section	.debug_str		;off: 280
	.data.b	83,83,87,83,84,83,0
	.section	.debug_info		;off: 252
	.data.w	.Ldw_str_begin+280
	.data.b	36
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 109
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

	.section	.debug_info		;off: 267
	.data.b	40
	.section	.debug_str		;off: 287
	.data.b	72,87,80,73,78,67,70,71,0
	.section	.debug_info		;off: 268
	.data.w	.Ldw_str_begin+287
	.data.b	37
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 296
	.data.b	79,82,73,71,67,79,80,89,73,78,70,79,0
	.section	.debug_info		;off: 284
	.data.w	.Ldw_str_begin+296
	.data.b	38
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 309
	.data.b	114,101,115,101,114,118,101,100,95,48,67,0
	.section	.debug_info		;off: 300
	.data.w	.Ldw_str_begin+309
	.data.b	39
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+139
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 321
	.data.b	83,84,77,69,77,48,0
	.section	.debug_info		;off: 316
	.data.w	.Ldw_str_begin+321
	.data.b	40
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 328
	.data.b	83,84,77,69,77,49,0
	.section	.debug_info		;off: 332
	.data.w	.Ldw_str_begin+328
	.data.b	41
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 335
	.data.b	83,84,77,69,77,50,0
	.section	.debug_info		;off: 348
	.data.w	.Ldw_str_begin+335
	.data.b	42
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 342
	.data.b	83,84,77,69,77,51,0
	.section	.debug_info		;off: 364
	.data.w	.Ldw_str_begin+342
	.data.b	43
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 349
	.data.b	67,80,85,48,83,84,82,65,68,68,82,0
	.section	.debug_info		;off: 380
	.data.w	.Ldw_str_begin+349
	.data.b	44
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 361
	.data.b	67,80,85,49,83,84,82,65,68,68,82,0
	.section	.debug_info		;off: 396
	.data.w	.Ldw_str_begin+361
	.data.b	45
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 373
	.data.b	67,80,85,50,83,84,82,65,68,68,82,0
	.section	.debug_info		;off: 412
	.data.w	.Ldw_str_begin+373
	.data.b	46
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	56
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 385
	.data.b	67,80,85,51,83,84,82,65,68,68,82,0
	.section	.debug_info		;off: 428
	.data.w	.Ldw_str_begin+385
	.data.b	47
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	60
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 397
	.data.b	114,101,115,101,114,118,101,100,95,52,48,0
	.section	.debug_info		;off: 444
	.data.w	.Ldw_str_begin+397
	.data.b	48
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+155
	.data.b	2,35
	.data.b	64
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 409
	.data.b	82,65,77,73,78,73,0
	.section	.debug_info		;off: 460
	.data.w	.Ldw_str_begin+409
	.data.b	49
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	76
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 416
	.data.b	82,65,77,73,78,73,67,84,82,76,0
	.section	.debug_info		;off: 476
	.data.w	.Ldw_str_begin+416
	.data.b	50
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	80
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 427
	.data.b	82,65,77,73,78,73,83,84,83,0
	.section	.debug_info		;off: 492
	.data.w	.Ldw_str_begin+427
	.data.b	51
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	84
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 437
	.data.b	66,79,79,84,67,79,82,69,73,68,0
	.section	.debug_info		;off: 508
	.data.w	.Ldw_str_begin+437
	.data.b	52
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	88
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 448
	.data.b	67,80,85,82,85,78,0
	.section	.debug_info		;off: 524
	.data.w	.Ldw_str_begin+448
	.data.b	53
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	92
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 455
	.data.b	67,80,85,83,76,86,82,85,78,50,0
	.section	.debug_info		;off: 540
	.data.w	.Ldw_str_begin+455
	.data.b	54
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	96
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 466
	.data.b	67,80,85,83,76,86,82,85,78,51,0
	.section	.debug_info		;off: 556
	.data.w	.Ldw_str_begin+466
	.data.b	55
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	100
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 477
	.data.b	114,101,115,101,114,118,101,100,95,54,56,0
	.section	.debug_info		;off: 572
	.data.w	.Ldw_str_begin+477
	.data.b	56
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+171
	.data.b	2,35
	.data.b	104
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 489
	.data.b	83,89,83,77,79,68,69,0
	.section	.debug_info		;off: 588
	.data.w	.Ldw_str_begin+489
	.data.b	57
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	112
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 497
	.data.b	73,78,73,84,83,89,83,0
	.section	.debug_info		;off: 604
	.data.w	.Ldw_str_begin+497
	.data.b	58
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	116
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 505
	.data.b	73,78,73,84,70,65,85,76,84,67,84,82,76,0
	.section	.debug_info		;off: 620
	.data.w	.Ldw_str_begin+505
	.data.b	59
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	120
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 519
	.data.b	73,78,73,84,77,65,83,75,0
	.section	.debug_info		;off: 636
	.data.w	.Ldw_str_begin+519
	.data.b	60
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	2,35
	.data.b	124
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 528
	.data.b	83,69,82,82,80,79,82,83,84,83,0
	.section	.debug_info		;off: 652
	.data.w	.Ldw_str_begin+528
	.data.b	61
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	128,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 539
	.data.b	83,69,82,82,83,89,83,83,84,83,0
	.section	.debug_info		;off: 669
	.data.w	.Ldw_str_begin+539
	.data.b	62
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	132,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 550
	.data.b	83,65,70,69,69,78,73,78,73,84,0
	.section	.debug_info		;off: 686
	.data.w	.Ldw_str_begin+550
	.data.b	63
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	136,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 561
	.data.b	114,101,115,101,114,118,101,100,95,56,67,0
	.section	.debug_info		;off: 703
	.data.w	.Ldw_str_begin+561
	.data.b	64
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+187
	.data.b	3,35
	.data.b	140,1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 573
	.data.b	73,78,73,84,83,84,83,49,0
	.section	.debug_info		;off: 720
	.data.w	.Ldw_str_begin+573
	.data.b	65
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	132,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 582
	.data.b	82,65,77,73,78,73,67,84,82,76,49,0
	.section	.debug_info		;off: 737
	.data.w	.Ldw_str_begin+582
	.data.b	66
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	136,2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 594
	.data.b	82,65,77,73,78,73,83,84,83,49,0
	.section	.debug_info		;off: 754
	.data.w	.Ldw_str_begin+594
	.data.b	67
	.data.b	12
	.data.b	13
	.data.w	.Ldw_begin+220
	.data.b	3,35
	.data.b	140,2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 605
	.data.b	73,84,77,85,73,78,73,84,95,77,79,68,85,76,69,0
	.section	.debug_info		;off: 772
	.data.w	.Ldw_str_begin+605
	.data.b	68
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+203

	.data.b	52
	.section	.debug_str		;off: 621
	.data.b	0
	.section	.debug_info		;off: 784
	.data.w	.Ldw_str_begin+621
	.data.b	130,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 128
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

	.section	.debug_info		;off: 794
	.data.b	51
	.section	.debug_str		;off: 622
	.data.b	73,84,77,85,95,82,65,77,73,78,73,79,78,83,89,83,82,69,83,69,84,69,95,69,78,65,66,76,69,0
	.section	.debug_info		;off: 795
	.data.w	.Ldw_str_begin+622
	.data.b	131,1
	.data.b	5
	.data.b	13
	.data.b	0

	.section	.debug_abbrev		;off: 145
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 804
	.data.b	51
	.section	.debug_str		;off: 652
	.data.b	73,84,77,85,95,82,65,77,73,78,73,79,78,83,89,83,82,69,83,69,84,69,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 805
	.data.w	.Ldw_str_begin+652
	.data.b	132,1
	.data.b	5
	.data.b	13
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 683
	.data.b	73,116,109,117,95,82,97,109,73,110,105,79,110,83,121,115,82,101,115,101,116,0
	.section	.debug_info		;off: 816
	.data.w	.Ldw_str_begin+683
	.data.b	133,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+783

	.data.b	52
	.section	.debug_str		;off: 705
	.data.b	0
	.section	.debug_info		;off: 829
	.data.w	.Ldw_str_begin+705
	.data.b	137,1
	.data.b	1
	.data.b	13
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 706
	.data.b	73,84,77,85,95,83,84,65,84,85,83,95,79,75,0
	.section	.debug_info		;off: 840
	.data.w	.Ldw_str_begin+706
	.data.b	138,1
	.data.b	5
	.data.b	13
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 721
	.data.b	73,84,77,85,95,83,84,65,84,85,83,95,69,82,82,79,82,0
	.section	.debug_info		;off: 850
	.data.w	.Ldw_str_begin+721
	.data.b	139,1
	.data.b	5
	.data.b	13
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 739
	.data.b	73,116,109,117,95,83,116,97,116,117,115,0
	.section	.debug_info		;off: 861
	.data.w	.Ldw_str_begin+739
	.data.b	140,1
	.data.b	3
	.data.b	13
	.data.w	.Ldw_begin+828

	.data.b	27
	.section	.debug_str		;off: 751
	.data.b	83,116,109,95,72,97,108,95,71,101,116,86,97,108,117,101,0
	.section	.debug_info		;off: 874
	.data.w	.Ldw_str_begin+751
	.data.b	94
	.data.b	26
	.data.b	3
	.data.w	.Ldw_begin+232
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 160
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

	.section	.debug_info		;off: 891
	.data.b	37

	.section	.debug_abbrev		;off: 187
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 892
	.data.b	8
	.section	.debug_str		;off: 768
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 893
	.data.w	.Ldw_str_begin+768
	.data.b	109
	.data.b	21
	.data.b	3
	.data.w	.Ldw_begin+63
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 192
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

	.section	.debug_info		;off: 906
	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 774
	.data.b	118,97,108,49,95,116,101,109,112,0
	.section	.debug_info		;off: 908
	.data.w	.Ldw_str_begin+774
	.data.b	114
	.data.b	5
	.data.b	3
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 784
	.data.b	118,97,108,50,95,116,101,109,112,0
	.section	.debug_info		;off: 922
	.data.w	.Ldw_str_begin+784
	.data.b	114
	.data.b	5
	.data.b	3
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 794
	.data.b	73,116,109,117,95,82,101,103,105,115,116,101,114,95,82,101,97,100,66,97,99,107,95,67,104,101,99,107,0
	.section	.debug_info		;off: 939
	.data.w	.Ldw_str_begin+794
	.data.b	73
	.data.b	27
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 823
	.data.b	115,116,97,116,101,0
	.section	.debug_info		;off: 957
	.data.w	.Ldw_str_begin+823
	.data.b	73
	.data.b	64
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.b	0

	.section	.debug_abbrev		;off: 211
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

	.section	.debug_info		;off: 969
	.data.b	20
	.section	.debug_str		;off: 829
	.data.b	101,120,112,101,99,116,0
	.section	.debug_info		;off: 970
	.data.w	.Ldw_str_begin+829
	.data.b	73
	.data.b	78
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 836
	.data.b	118,97,108,117,101,0
	.section	.debug_info		;off: 983
	.data.w	.Ldw_str_begin+836
	.data.b	73
	.data.b	93
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 842
	.data.b	114,101,116,0
	.section	.debug_info		;off: 997
	.data.w	.Ldw_str_begin+842
	.data.b	75
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 846
	.data.b	73,116,109,117,95,67,108,101,97,114,77,111,100,117,108,101,82,97,109,0
	.section	.debug_info		;off: 1013
	.data.w	.Ldw_str_begin+846
	.data.b	110
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.w	Itmu_ClearModuleRam
	.data.w	__ghs_eofn_Itmu_ClearModuleRam
	.data.b	1
	.data.b	93
	.data.b	240,137,1
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

	.section	.debug_abbrev		;off: 228
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
	.data.w	Itmu_ClearModuleRam
	.data.w	__ghs_eofn_Itmu_ClearModuleRam-Itmu_ClearModuleRam
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 576
	.data.b	0,5,2
	.data.w	Itmu_ClearModuleRam
	.data.b	6
	.data.b	3
	.data.b	238,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	24
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	171
	.data.b	3
	.data.b	9
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
	.data.b	45
	.data.b	2
	.data.b	16
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	59
	.data.b	12
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	20
	.data.b	12
	.data.b	27
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1047
	.data.b	22
	.section	.debug_str		;off: 866
	.data.b	105,110,100,101,120,0
	.section	.debug_info		;off: 1048
	.data.w	.Ldw_str_begin+866
	.data.b	110
	.data.b	36
	.data.b	1
	.data.w	.Ldw_begin+220
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
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 276
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

	.section	.debug_info		;off: 1064
	.data.b	22
	.section	.debug_str		;off: 872
	.data.b	99,108,101,97,114,66,105,116,115,0
	.section	.debug_info		;off: 1065
	.data.w	.Ldw_str_begin+872
	.data.b	110
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.w	.Ldw_loc_begin+30
	.section	.debug_loc		;off: 30
	.data.w	.LDW01
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1081
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 295
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 1090
	.data.b	7
	.section	.debug_str		;off: 882
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1091
	.data.w	.Ldw_str_begin+882
	.data.b	112
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+49
	.section	.debug_loc		;off: 49
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 304
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

	.section	.debug_info		;off: 1108
	.data.b	7
	.section	.debug_str		;off: 886
	.data.b	115,116,97,116,117,115,0
	.section	.debug_info		;off: 1109
	.data.w	.Ldw_str_begin+886
	.data.b	113
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+860
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+68
	.section	.debug_loc		;off: 68
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1126
	.data.b	7
	.section	.debug_str		;off: 893
	.data.b	101,110,100,84,105,109,101,0
	.section	.debug_info		;off: 1127
	.data.w	.Ldw_str_begin+893
	.data.b	114
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+232
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+87
	.section	.debug_loc		;off: 87
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1144
	.data.b	7
	.section	.debug_str		;off: 901
	.data.b	99,117,114,84,105,109,101,0
	.section	.debug_info		;off: 1145
	.data.w	.Ldw_str_begin+901
	.data.b	115
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+232
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+106
	.section	.debug_loc		;off: 106
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1162
	.data.b	7
	.section	.debug_str		;off: 909
	.data.b	114,97,109,73,110,105,83,116,97,116,117,115,0
	.section	.debug_info		;off: 1163
	.data.w	.Ldw_str_begin+909
	.data.b	116
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+125
	.section	.debug_loc		;off: 125
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1180
	.data.b	7
	.section	.debug_str		;off: 922
	.data.b	114,97,109,105,110,105,115,116,115,82,101,103,65,100,100,114,0
	.section	.debug_info		;off: 1181
	.data.w	.Ldw_str_begin+922
	.data.b	117
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+144
	.section	.debug_loc		;off: 144
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	90
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1198
	.data.b	7
	.section	.debug_str		;off: 939
	.data.b	114,97,109,105,110,105,99,116,114,108,82,101,103,65,100,100,114,0
	.section	.debug_info		;off: 1199
	.data.w	.Ldw_str_begin+939
	.data.b	118
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+163
	.section	.debug_loc		;off: 163
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1216
	.data.b	7
	.section	.debug_str		;off: 957
	.data.b	114,97,109,105,110,105,99,116,114,108,77,97,115,107,0
	.section	.debug_info		;off: 1217
	.data.w	.Ldw_str_begin+957
	.data.b	119
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+220
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+182
	.section	.debug_loc		;off: 182
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	83
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1234
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 972
	.data.b	73,116,109,117,95,73,110,105,116,82,97,109,79,110,83,121,115,82,101,115,101,116,0
	.section	.debug_info		;off: 1237
	.data.w	.Ldw_str_begin+972
	.data.b	181,1
	.data.b	9
	.data.b	1
	.data.w	.Ldw_begin+208
	.data.w	Itmu_InitRamOnSysReset
	.data.w	__ghs_eofn_Itmu_InitRamOnSysReset
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Itmu_InitRamOnSysReset
	.data.w	__ghs_eofn_Itmu_InitRamOnSysReset-Itmu_InitRamOnSysReset
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 657
	.data.b	0,5,2
	.data.w	Itmu_InitRamOnSysReset
	.data.b	6
	.data.b	3
	.data.b	181,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	44
	.data.b	76
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1270
	.data.b	22
	.section	.debug_str		;off: 995
	.data.b	114,97,109,73,110,105,79,110,83,121,115,82,101,115,101,116,0
	.section	.debug_info		;off: 1271
	.data.w	.Ldw_str_begin+995
	.data.b	181,1
	.data.b	54
	.data.b	1
	.data.w	.Ldw_begin+815
	.data.b	0
	.data.w	.Ldw_loc_begin+201
	.section	.debug_loc		;off: 201
	.data.w	.LDW31
	.data.w	.LDW41
	.data.b	1,0
	.data.b	80
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	81
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1288
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	8
	.section	.debug_str		;off: 1012
	.data.b	114,101,116,0
	.section	.debug_info		;off: 1298
	.data.w	.Ldw_str_begin+1012
	.data.b	183,1
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+208
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
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	30
	.data.b	2
	.data.b	1
	.data.b	41
	.data.b	84,82,85,69,32,49,117,0
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	3
	.data.b	31
	.data.b	3
	.data.b	3
	.data.b	34
	.data.b	4
	.data.b	3
	.data.b	31
	.data.b	5
	.data.b	3
	.data.b	24
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
	.data.b	8
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
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	9
	.data.b	3
	.data.b	21
	.data.b	10
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	11
	.data.b	3
	.data.b	56
	.data.b	12
	.data.b	1
	.data.b	78
	.data.b	73,84,77,85,73,78,73,84,95,66,65,83,69,95,65,68,68,82,69,83,83,32,40,48,120,66,48,51,51,48,67,48,48,85,41,0
	.data.b	1
	.data.b	80
	.data.b	73,84,77,85,73,78,73,84,32,40,40,73,84,77,85,73,78,73,84,95,77,79,68,85,76,69,32,42,41,73,84,77,85,73,78,73,84,95,66,65,83,69,95,65,68,68,82,69,83,83,41,0
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	72
	.data.b	83,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	74
	.data.b	8
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
	.data.b	8
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	13
	.data.b	1
	.data.b	158,1
	.data.b	73,84,77,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,1
	.data.b	14
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,84,77,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	198,1
	.data.b	73,84,77,85,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	200,1
	.data.b	14
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	38
	.data.b	73,84,77,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	40
	.data.b	14
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,73,84,77,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	51
	.data.b	73,84,77,85,95,82,65,77,73,78,73,67,84,82,76,48,95,77,65,83,75,32,40,48,120,48,51,70,70,70,70,70,70,85,41,0
	.data.b	1
	.data.b	53
	.data.b	73,84,77,85,95,82,65,77,73,78,73,67,84,82,76,49,95,77,65,83,75,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	63
	.data.b	73,84,77,85,95,82,65,77,73,78,73,83,84,83,48,95,77,65,83,75,32,40,48,120,48,49,53,53,53,53,53,53,85,41,0
	.data.b	1
	.data.b	65
	.data.b	73,84,77,85,95,82,65,77,73,78,73,83,84,83,49,95,77,65,83,75,32,40,48,120,53,53,53,53,85,41,0
	.data.b	1
	.data.b	69
	.data.b	73,84,77,85,95,82,65,77,73,78,73,95,84,73,77,79,85,84,32,40,48,120,70,70,70,70,85,41,0
	.data.b	1
	.data.b	71
	.data.b	73,84,77,85,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	192,1
	.data.b	73,84,77,85,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	194,1
	.data.b	14
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 325
	.data.b	0
