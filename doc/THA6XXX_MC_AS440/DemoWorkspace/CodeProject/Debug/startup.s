	.section ".sdk_text_asil_d","ax"
	.text
	.section ".init_default_vector","ax"
	.text
	.section ".sdk_text_asil_d","ax"
	.text
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_InitGlobalUncachedSections:
.LDW01:
	push	{r4,r6-r10,lr}
	sub	sp,sp,28
.LDW11:
	mov	r7,0
	mov	r3,r7
	mov	r4,r7
	mov	r0,r7
	mov	r1,r7
	mov	r2,r7
	stm	sp,{r0-r4,r7}
	mov	r12,r7
..gh.beginasm.1:
	.endo	..gh.beginasm.1
ldr r12, =__UNDEFINE_RAM_DATA_ADDRESS_START

..gh.endasm.2:
	.endo	..gh.endasm.2

	str	r12,[sp,12]
	ldr	r12,[sp,16]
..gh.beginasm.3:
	.endo	..gh.beginasm.3
ldr r12, =__UNDEFINE_RAM_DATA_ADDRESS_END

..gh.endasm.4:
	.endo	..gh.endasm.4

	str	r12,[sp,16]
	ldr	r12,[sp,20]
..gh.beginasm.5:
	.endo	..gh.beginasm.5
ldr r12, =__UNDEFINE_RAM_DATA_LOAD_ADDRESS_START

..gh.endasm.6:
	.endo	..gh.endasm.6

	str	r12,[sp,20]
;line211
..lin.7807341b..fa2e4f1f.0_1::
.LDWlin1:
	ldm	sp,{r3-r4,r6}
..gh.beginasm.7:
	.endo	..gh.beginasm.7
ldr r3, =__GLOBAL_UNCACHED_DATA_ADDRESS_START

..gh.endasm.8:
	.endo	..gh.endasm.8

..gh.beginasm.9:
	.endo	..gh.beginasm.9
ldr r4, =__GLOBAL_UNCACHED_DATA_ADDRESS_END

..gh.endasm.10:
	.endo	..gh.endasm.10

..gh.beginasm.11:
	.endo	..gh.beginasm.11
ldr r6, =__GLOBAL_UNCACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.12:
	.endo	..gh.endasm.12

	stm	sp,{r3-r4,r6}
;line214
..lin.7807341b..fa2e4f1f.0_2::
.LDWlin2:
..gh.beginasm.13:
	.endo	..gh.beginasm.13
ldr r0, =__UNDEFINE_RAM_BSS_ADDRESS_START

..gh.endasm.14:
	.endo	..gh.endasm.14

..gh.beginasm.15:
	.endo	..gh.beginasm.15
ldr r1, =__UNDEFINE_RAM_BSS_ADDRESS_END

..gh.endasm.16:
	.endo	..gh.endasm.16

;line217
..lin.7807341b..fa2e4f1f.0_3::
.LDWlin3:
..gh.beginasm.17:
	.endo	..gh.beginasm.17
ldr r2, =__GLOBAL_UNCACHED_BSS_ADDRESS_START

..gh.endasm.18:
	.endo	..gh.endasm.18

	mov	r6,r7
..gh.beginasm.19:
	.endo	..gh.beginasm.19
ldr r6, =__GLOBAL_UNCACHED_BSS_ADDRESS_END

..gh.endasm.20:
	.endo	..gh.endasm.20

.L263:
;line220
..lin.7807341b..fa2e4f1f.0_4::
.LDWlin4:
	ldr	r12,[sp,12]
	ldr	r3,[sp,16]
	cmp	r12,r3
	ldrlo	r3,[sp,20]
	ldrlo	r9,[r3],4
	strlo	r9,[r12],4
	strlo	r12,[sp,12]
	strlo	r3,[sp,20]
	blo	.L263
	b	.L269
.L268:
	ldr	r3,[sp,8]
	ldr	r10,[r3],4
	str	r10,[r8],4
	str	r8,[sp]
	str	r3,[sp,8]
.L269:
	ldm	sp,{r8-r9}
	cmp	r8,r9
	blo	.L268
.L275:
	cmp	r0,r1
	bhs	.L281
	str	r7,[r0],4
	b	.L275
.L280:
	str	r7,[r2],4
.L281:
	cmp	r2,r6
	blo	.L280
..gh.beginasm.21:
	.endo	..gh.beginasm.21
ldr r12, =__LMU2_CACHED_DATA_ADDRESS_START

..gh.endasm.22:
	.endo	..gh.endasm.22

	str	r12,[sp,12]
	ldr	r12,[sp,16]
..gh.beginasm.23:
	.endo	..gh.beginasm.23
ldr r12, =__LMU2_CACHED_DATA_ADDRESS_END

..gh.endasm.24:
	.endo	..gh.endasm.24

	str	r12,[sp,16]
	ldr	r12,[sp,20]
..gh.beginasm.25:
	.endo	..gh.beginasm.25
ldr r12, =__LMU2_CACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.26:
	.endo	..gh.endasm.26

	str	r12,[sp,20]
;line230
..lin.7807341b..fa2e4f1f.0_5::
.LDWlin5:
	ldm	sp,{r3-r4,r8}
..gh.beginasm.27:
	.endo	..gh.beginasm.27
ldr r3, =__LMU2_UNCACHED_DATA_ADDRESS_START

..gh.endasm.28:
	.endo	..gh.endasm.28

..gh.beginasm.29:
	.endo	..gh.beginasm.29
ldr r4, =__LMU2_UNCACHED_DATA_ADDRESS_END

..gh.endasm.30:
	.endo	..gh.endasm.30

..gh.beginasm.31:
	.endo	..gh.beginasm.31
ldr r8, =__LMU2_UNCACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.32:
	.endo	..gh.endasm.32

	stm	sp,{r3-r4,r8}
;line231
..lin.7807341b..fa2e4f1f.0_6::
.LDWlin6:
..gh.beginasm.33:
	.endo	..gh.beginasm.33
ldr r0, =__LMU2_CACHED_BSS_ADDRESS_START

..gh.endasm.34:
	.endo	..gh.endasm.34

..gh.beginasm.35:
	.endo	..gh.beginasm.35
ldr r1, =__LMU2_CACHED_BSS_ADDRESS_END

..gh.endasm.36:
	.endo	..gh.endasm.36

;line232
..lin.7807341b..fa2e4f1f.0_7::
.LDWlin7:
..gh.beginasm.37:
	.endo	..gh.beginasm.37
ldr r2, =__LMU2_UNCACHED_BSS_ADDRESS_START

..gh.endasm.38:
	.endo	..gh.endasm.38

..gh.beginasm.39:
	.endo	..gh.beginasm.39
ldr r6, =__LMU2_UNCACHED_BSS_ADDRESS_END

..gh.endasm.40:
	.endo	..gh.endasm.40

.L299:
;line233
..lin.7807341b..fa2e4f1f.0_8::
.LDWlin8:
	ldr	r12,[sp,12]
	ldr	r3,[sp,16]
	cmp	r12,r3
	ldrlo	r8,[sp,20]
	ldrlo	r3,[r8],4
	strlo	r3,[r12],4
	strlo	r12,[sp,12]
	strlo	r8,[sp,20]
	blo	.L299
	b	.L305
.L304:
	ldr	r9,[sp,8]
	ldr	r3,[r9],4
	str	r3,[r8],4
	str	r8,[sp]
	str	r9,[sp,8]
.L305:
	ldm	sp,{r8-r9}
	cmp	r8,r9
	blo	.L304
.L311:
	cmp	r0,r1
	bhs	.L317
	str	r7,[r0],4
	b	.L311
.L316:
	str	r7,[r2],4
.L317:
	cmp	r2,r6
	blo	.L316
..gh.beginasm.41:
	.endo	..gh.beginasm.41
ldr r12, =__LMU1_CACHED_DATA_ADDRESS_START

..gh.endasm.42:
	.endo	..gh.endasm.42

	str	r12,[sp,12]
	ldr	r12,[sp,16]
..gh.beginasm.43:
	.endo	..gh.beginasm.43
ldr r12, =__LMU1_CACHED_DATA_ADDRESS_END

..gh.endasm.44:
	.endo	..gh.endasm.44

	str	r12,[sp,16]
	ldr	r12,[sp,20]
..gh.beginasm.45:
	.endo	..gh.beginasm.45
ldr r12, =__LMU1_CACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.46:
	.endo	..gh.endasm.46

	str	r12,[sp,20]
;line242
..lin.7807341b..fa2e4f1f.0_9::
.LDWlin9:
	ldm	sp,{r3-r4,r8}
..gh.beginasm.47:
	.endo	..gh.beginasm.47
ldr r3, =__LMU1_UNCACHED_DATA_ADDRESS_START

..gh.endasm.48:
	.endo	..gh.endasm.48

..gh.beginasm.49:
	.endo	..gh.beginasm.49
ldr r4, =__LMU1_UNCACHED_DATA_ADDRESS_END

..gh.endasm.50:
	.endo	..gh.endasm.50

..gh.beginasm.51:
	.endo	..gh.beginasm.51
ldr r8, =__LMU1_UNCACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.52:
	.endo	..gh.endasm.52

	stm	sp,{r3-r4,r8}
;line243
..lin.7807341b..fa2e4f1f.0_10::
.LDWlin10:
..gh.beginasm.53:
	.endo	..gh.beginasm.53
ldr r0, =__LMU1_CACHED_BSS_ADDRESS_START

..gh.endasm.54:
	.endo	..gh.endasm.54

..gh.beginasm.55:
	.endo	..gh.beginasm.55
ldr r1, =__LMU1_CACHED_BSS_ADDRESS_END

..gh.endasm.56:
	.endo	..gh.endasm.56

;line244
..lin.7807341b..fa2e4f1f.0_11::
.LDWlin11:
..gh.beginasm.57:
	.endo	..gh.beginasm.57
ldr r2, =__LMU1_UNCACHED_BSS_ADDRESS_START

..gh.endasm.58:
	.endo	..gh.endasm.58

..gh.beginasm.59:
	.endo	..gh.beginasm.59
ldr r6, =__LMU1_UNCACHED_BSS_ADDRESS_END

..gh.endasm.60:
	.endo	..gh.endasm.60

.L335:
;line245
..lin.7807341b..fa2e4f1f.0_12::
.LDWlin12:
	ldr	r12,[sp,12]
	ldr	r3,[sp,16]
	cmp	r12,r3
	ldrlo	r8,[sp,20]
	ldrlo	r3,[r8],4
	strlo	r3,[r12],4
	strlo	r12,[sp,12]
	strlo	r8,[sp,20]
	blo	.L335
	b	.L341
.L340:
	ldr	r9,[sp,8]
	ldr	r3,[r9],4
	str	r3,[r8],4
	str	r8,[sp]
	str	r9,[sp,8]
.L341:
	ldm	sp,{r8-r9}
	cmp	r8,r9
	blo	.L340
.L347:
	cmp	r0,r1
	bhs	.L353
	str	r7,[r0],4
	b	.L347
.L352:
	str	r7,[r2],4
.L353:
	cmp	r2,r6
	blo	.L352
..gh.beginasm.61:
	.endo	..gh.beginasm.61
ldr r12, =__LMU3_CACHED_DATA_ADDRESS_START

..gh.endasm.62:
	.endo	..gh.endasm.62

	str	r12,[sp,12]
	ldr	r12,[sp,16]
..gh.beginasm.63:
	.endo	..gh.beginasm.63
ldr r12, =__LMU3_CACHED_DATA_ADDRESS_END

..gh.endasm.64:
	.endo	..gh.endasm.64

	str	r12,[sp,16]
	ldr	r12,[sp,20]
..gh.beginasm.65:
	.endo	..gh.beginasm.65
ldr r12, =__LMU3_CACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.66:
	.endo	..gh.endasm.66

	str	r12,[sp,20]
;line251
..lin.7807341b..fa2e4f1f.0_13::
.LDWlin13:
	ldm	sp,{r3-r4,r8}
..gh.beginasm.67:
	.endo	..gh.beginasm.67
ldr r3, =__LMU3_UNCACHED_DATA_ADDRESS_START

..gh.endasm.68:
	.endo	..gh.endasm.68

..gh.beginasm.69:
	.endo	..gh.beginasm.69
ldr r4, =__LMU3_UNCACHED_DATA_ADDRESS_END

..gh.endasm.70:
	.endo	..gh.endasm.70

..gh.beginasm.71:
	.endo	..gh.beginasm.71
ldr r8, =__LMU3_UNCACHED_DATA_LOAD_ADDRESS_START

..gh.endasm.72:
	.endo	..gh.endasm.72

	stm	sp,{r3-r4,r8}
;line252
..lin.7807341b..fa2e4f1f.0_14::
.LDWlin14:
..gh.beginasm.73:
	.endo	..gh.beginasm.73
ldr r0, =__LMU3_CACHED_BSS_ADDRESS_START

..gh.endasm.74:
	.endo	..gh.endasm.74

..gh.beginasm.75:
	.endo	..gh.beginasm.75
ldr r1, =__LMU3_CACHED_BSS_ADDRESS_END

..gh.endasm.76:
	.endo	..gh.endasm.76

;line253
..lin.7807341b..fa2e4f1f.0_15::
.LDWlin15:
..gh.beginasm.77:
	.endo	..gh.beginasm.77
ldr r2, =__LMU3_UNCACHED_BSS_ADDRESS_START

..gh.endasm.78:
	.endo	..gh.endasm.78

..gh.beginasm.79:
	.endo	..gh.beginasm.79
ldr r6, =__LMU3_UNCACHED_BSS_ADDRESS_END

..gh.endasm.80:
	.endo	..gh.endasm.80

.L371:
;line254
..lin.7807341b..fa2e4f1f.0_16::
.LDWlin16:
	ldr	r12,[sp,12]
	ldr	r3,[sp,16]
	cmp	r12,r3
	ldrlo	r3,[sp,20]
	ldrlo	r9,[r3],4
	strlo	r9,[r12],4
	strlo	r12,[sp,12]
	strlo	r3,[sp,20]
	blo	.L371
	b	.L377
.L376:
	ldr	r3,[sp,8]
	ldr	r12,[r3],4
	str	r12,[r8],4
	str	r8,[sp]
	str	r3,[sp,8]
.L377:
	ldm	sp,{r8,r12}
	cmp	r8,r12
	blo	.L376
.L383:
	cmp	r0,r1
	bhs	.L389
	str	r7,[r0],4
	b	.L383

.L1526:	.data.w	0xc0000800
	.endo	.L1526

.L388:
;line257
..lin.7807341b..fa2e4f1f.0_17::
.LDWlin17:
	str	r7,[r2],4
.L389:
	cmp	r2,r6
	blo	.L388
	ldr	r1,.L1526
	ldr	r0,[r1]
	cmp	r0,1<<23
	bne	.L245
	mov	r1,r7
..gh.beginasm.81:
	.endo	..gh.beginasm.81
ldr r1, =__UNCLEAR_RAM_BSS_ADDRESS_START

..gh.endasm.82:
	.endo	..gh.endasm.82

	mov	r0,r7
..gh.beginasm.83:
	.endo	..gh.beginasm.83
ldr r0, =__UNCLEAR_RAM_BSS_ADDRESS_END

..gh.endasm.84:
	.endo	..gh.endasm.84

.L400:
;line268
..lin.7807341b..fa2e4f1f.0_18::
.LDWlin18:
	cmp	r1,r0
	strlo	r7,[r1],4
	blo	.L400
.L245:
.LDW21:
	add	sp,sp,28
.L1527:

	pop	{r4,r6-r10,pc}
__ghs_eofn_Startup_InitGlobalUncachedSections:
	.endf	Startup_InitGlobalUncachedSections
	.endf	Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
;globalData	[sp,12]	local
;uncachedData	[sp]	local
;globalBss	r0	local
;uncachedBss	r2	local
;unclearBss	r4	local

	.section ".bss","awb"
.L1089:
	.endo	.L1089
	.section ".ghrettbl",""
	.align	4
.L1528:	.data.w	.L1527
	.endo	.L1528
	.text
..gh.f.a.1.e.85:
	.endo	..gh.f.a.1.e.85
	.global	Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_StartSlaveCore:
.LDW31:
	push	{r4-r6,lr}
.LDW41:
	ldr	r5,.L1864
	ldr	r0,.L1865
	mov	r4,80
	str	r0,[r5]
	b	.L1866

.L1864:	.data.w	0x10000040
	.endo	.L1864

.L1865:	.data.w	0x11110000
	.endo	.L1865

.L1866:

.L1698:
;line309
..lin.7807341b..e7ee2809.0_19::
.LDWlin19:
..gh.beginasm.86:
	.endo	..gh.beginasm.86
nop

..gh.endasm.87:
	.endo	..gh.endasm.87

;line306
..lin.7807341b..e7ee2809.0_20::
.LDWlin20:
	subs	r4,r4,1
	bne	.L1698
	ldr	r0,[r5]
	ldr	r4,.L1867
	tst	r0,1
	ldreq	r0,[r4,2060]
	orreq	r0,r0,1
	streq	r0,[r4,2060]
	mov	r6,80
	b	.L1868

.L1867:	.data.w	0xc0020450
	.endo	.L1867

.L1868:

.L1697:
;line328
..lin.7807341b..e7ee2809.0_21::
.LDWlin21:
..gh.beginasm.88:
	.endo	..gh.beginasm.88
nop

..gh.endasm.89:
	.endo	..gh.endasm.89

;line325
..lin.7807341b..e7ee2809.0_22::
.LDWlin22:
	subs	r6,r6,1
	bne	.L1697
	ldr	r0,[r5]
	tst	r0,2
	ldreq	r0,[r4,2064]
	orreq	r0,r0,1
	streq	r0,[r4,2064]
	mov	r6,80
.L1696:
..gh.beginasm.90:
	.endo	..gh.beginasm.90
nop

..gh.endasm.91:
	.endo	..gh.endasm.91

;line343
..lin.7807341b..e7ee2809.0_23::
.LDWlin23:
	subs	r6,r6,1
	bne	.L1696
	ldr	r0,[r5]
	tst	r0,4
	ldreq	r0,[r4]
	cmpeq	r0,48
	ldreq	r0,[r4,2068]
	orreq	r0,r0,1
	streq	r0,[r4,2068]
.LDW51:
.L1869:

	pop	{r4-r6,pc}
__ghs_eofn_Startup_StartSlaveCore:
	.endf	Startup_StartSlaveCore
	.endf	Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section ".bss","awb"
.L1744:
	.endo	.L1744
	.section ".ghrettbl",""
.L1870:	.data.w	.L1869
	.endo	.L1870
	.text
..gh.f.a.1.e.92:
	.endo	..gh.f.a.1.e.92
	.global	Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_InitPrivateSections:
.LDW61:
	push	{r4-r6,lr}
	sub	sp,sp,24
.LDW71:
	mov	r0,0
	mov	r3,r0
	mov	r4,r0
	mov	r12,r0
	mov	r1,r0
	mov	r2,r0
	stm	sp,{r0-r4,r12}
..gh.beginasm.93:
	.endo	..gh.beginasm.93
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.94:
	.endo	..gh.endasm.94

;line403
..lin.7807341b..f72dc80e.0_24::
.LDWlin24:
	ldr	r5,.L5426
	ldr	r6,.L5427
	subs	r0,r0,1
	blo	.L1886
	beq	.L1909
	cmp	r0,2
	ldr	r0,[sp,12]
	blo	.L1930
	beq	.L1951
	b	.L5428

.L5426:	.data.w	s_cpu01SyncFlag
	.endo	.L5426

.L5427:	.data.w	0x5a5a5a5a
	.endo	.L5427

.L5428:

;line530
..lin.7807341b..f72dc80e.0_25::
.LDWlin25:
..gh.beginasm.95:
	.endo	..gh.beginasm.95
cpsid aif
1:b 1b

..gh.endasm.96:
	.endo	..gh.endasm.96

	b	.L1871
.L1886:
;line409
..lin.7807341b..f72dc80e.0_26::
.LDWlin26:
	ldm	sp,{r1-r4,r12,lr}
..gh.beginasm.97:
	.endo	..gh.beginasm.97
ldr r4, =__PRIVATE_CODE_CORE0_ADDRESS_START

..gh.endasm.98:
	.endo	..gh.endasm.98

..gh.beginasm.99:
	.endo	..gh.beginasm.99
ldr r12, =__PRIVATE_CODE_CORE0_ADDRESS_END

..gh.endasm.100:
	.endo	..gh.endasm.100

..gh.beginasm.101:
	.endo	..gh.beginasm.101
ldr lr, =__PRIVATE_CODE_CORE0_LOAD_ADDRESS_START

..gh.endasm.102:
	.endo	..gh.endasm.102

	add	r0,sp,12
	stm	r0,{r4,r12,lr}
;line413
..lin.7807341b..f72dc80e.0_27::
.LDWlin27:
..gh.beginasm.103:
	.endo	..gh.beginasm.103
ldr r1, =__PRIVATE_DATA_CORE0_ADDRESS_START

..gh.endasm.104:
	.endo	..gh.endasm.104

..gh.beginasm.105:
	.endo	..gh.beginasm.105
ldr r2, =__PRIVATE_DATA_CORE0_ADDRESS_END

..gh.endasm.106:
	.endo	..gh.endasm.106

	stm	sp,{r1-r2}
	mov	r4,r3
..gh.beginasm.107:
	.endo	..gh.beginasm.107
ldr r4, =__PRIVATE_DATA_CORE0_LOAD_ADDRESS_START

..gh.endasm.108:
	.endo	..gh.endasm.108

.L1890:
;line421
..lin.7807341b..f72dc80e.0_28::
.LDWlin28:
	ldr	r1,.L5429
	ldr	r0,[r1]
	cmp	r0,0
	ldrne	r0,[r1]
	andne	r0,r0,7
	cmpne	r0,7
	bne	.L1890
.L5430:

	bl	Startup_InitGlobalUncachedSections
.L1898:
	ldr	r0,[sp,12]
	ldr	r1,[sp,16]
	cmp	r0,r1
	ldrlo	r1,[sp,20]
	ldrlo	r2,[r1],4
	strlo	r2,[r0],4
	strlo	r0,[sp,12]
	strlo	r1,[sp,20]
	blo	.L1898
	b	.L1904
.L1903:
	ldr	r1,[r4],4
	str	r1,[r0],4
	str	r0,[sp]
.L1904:
	ldm	sp,{r0-r1}
	cmp	r0,r1
	blo	.L1903
	str	r6,[r5]
	b	.L1871

.L5429:	.data.w	0x10000040
	.endo	.L5429

.L1909:
;line449
..lin.7807341b..f72dc80e.0_29::
.LDWlin29:
	ldm	sp,{r1-r4,r12,lr}
..gh.beginasm.109:
	.endo	..gh.beginasm.109
ldr r4, =__PRIVATE_CODE_CORE1_ADDRESS_START

..gh.endasm.110:
	.endo	..gh.endasm.110

..gh.beginasm.111:
	.endo	..gh.beginasm.111
ldr r12, =__PRIVATE_CODE_CORE1_ADDRESS_END

..gh.endasm.112:
	.endo	..gh.endasm.112

..gh.beginasm.113:
	.endo	..gh.beginasm.113
ldr lr, =__PRIVATE_CODE_CORE1_LOAD_ADDRESS_START

..gh.endasm.114:
	.endo	..gh.endasm.114

	add	r0,sp,12
	stm	r0,{r4,r12,lr}
;line453
..lin.7807341b..f72dc80e.0_30::
.LDWlin30:
..gh.beginasm.115:
	.endo	..gh.beginasm.115
ldr r1, =__PRIVATE_DATA_CORE1_ADDRESS_START

..gh.endasm.116:
	.endo	..gh.endasm.116

..gh.beginasm.117:
	.endo	..gh.beginasm.117
ldr r2, =__PRIVATE_DATA_CORE1_ADDRESS_END

..gh.endasm.118:
	.endo	..gh.endasm.118

	stm	sp,{r1-r2}
	mov	r4,r3
..gh.beginasm.119:
	.endo	..gh.beginasm.119
ldr r4, =__PRIVATE_DATA_CORE1_LOAD_ADDRESS_START

..gh.endasm.120:
	.endo	..gh.endasm.120

.L1917:
;line459
..lin.7807341b..f72dc80e.0_31::
.LDWlin31:
	ldr	r0,[sp,12]
	ldr	r1,[sp,16]
	cmp	r0,r1
	ldrlo	r1,[sp,20]
	ldrlo	r2,[r1],4
	strlo	r2,[r0],4
	strlo	r0,[sp,12]
	strlo	r1,[sp,20]
	blo	.L1917
	b	.L1923
.L1922:
	ldr	r1,[r4],4
	str	r1,[r0],4
	str	r0,[sp]
.L1923:
	ldm	sp,{r0-r1}
	cmp	r0,r1
	blo	.L1922
.L1925:
	ldr	r0,[r5]
	cmp	r0,r6
	bne	.L1925
	b	.L1871
.L1930:
..gh.beginasm.121:
	.endo	..gh.beginasm.121
ldr r0, =__PRIVATE_CODE_CORE2_ADDRESS_START

..gh.endasm.122:
	.endo	..gh.endasm.122

	str	r0,[sp,12]
	ldr	r0,[sp,16]
..gh.beginasm.123:
	.endo	..gh.beginasm.123
ldr r0, =__PRIVATE_CODE_CORE2_ADDRESS_END

..gh.endasm.124:
	.endo	..gh.endasm.124

	str	r0,[sp,16]
	ldr	r0,[sp,20]
..gh.beginasm.125:
	.endo	..gh.beginasm.125
ldr r0, =__PRIVATE_CODE_CORE2_LOAD_ADDRESS_START

..gh.endasm.126:
	.endo	..gh.endasm.126

	str	r0,[sp,20]
;line481
..lin.7807341b..f72dc80e.0_32::
.LDWlin32:
	ldm	sp,{r0,r3-r4}
..gh.beginasm.127:
	.endo	..gh.beginasm.127
ldr r0, =__PRIVATE_DATA_CORE2_ADDRESS_START

..gh.endasm.128:
	.endo	..gh.endasm.128

..gh.beginasm.129:
	.endo	..gh.beginasm.129
ldr r3, =__PRIVATE_DATA_CORE2_ADDRESS_END

..gh.endasm.130:
	.endo	..gh.endasm.130

	stm	sp,{r0,r3}
..gh.beginasm.131:
	.endo	..gh.beginasm.131
ldr r4, =__PRIVATE_DATA_CORE2_LOAD_ADDRESS_START

..gh.endasm.132:
	.endo	..gh.endasm.132

.L1938:
;line487
..lin.7807341b..f72dc80e.0_33::
.LDWlin33:
	ldr	r0,[sp,12]
	ldr	r1,[sp,16]
	cmp	r0,r1
	ldrlo	r1,[sp,20]
	ldrlo	r2,[r1],4
	strlo	r2,[r0],4
	strlo	r0,[sp,12]
	strlo	r1,[sp,20]
	blo	.L1938
	b	.L1944
.L1943:
	ldr	r1,[r4],4
	str	r1,[r0],4
	str	r0,[sp]
.L1944:
	ldm	sp,{r0-r1}
	cmp	r0,r1
	blo	.L1943
.L1946:
	ldr	r0,[r5]
	cmp	r0,r6
	bne	.L1946
	b	.L1871
.L1951:
..gh.beginasm.133:
	.endo	..gh.beginasm.133
ldr r0, =__PRIVATE_CODE_CORE3_ADDRESS_START

..gh.endasm.134:
	.endo	..gh.endasm.134

	str	r0,[sp,12]
	ldr	r0,[sp,16]
..gh.beginasm.135:
	.endo	..gh.beginasm.135
ldr r0, =__PRIVATE_CODE_CORE3_ADDRESS_END

..gh.endasm.136:
	.endo	..gh.endasm.136

	str	r0,[sp,16]
	ldr	r0,[sp,20]
..gh.beginasm.137:
	.endo	..gh.beginasm.137
ldr r0, =__PRIVATE_CODE_CORE3_LOAD_ADDRESS_START

..gh.endasm.138:
	.endo	..gh.endasm.138

	str	r0,[sp,20]
;line508
..lin.7807341b..f72dc80e.0_34::
.LDWlin34:
	ldm	sp,{r0,r3-r4}
..gh.beginasm.139:
	.endo	..gh.beginasm.139
ldr r0, =__PRIVATE_DATA_CORE3_ADDRESS_START

..gh.endasm.140:
	.endo	..gh.endasm.140

..gh.beginasm.141:
	.endo	..gh.beginasm.141
ldr r3, =__PRIVATE_DATA_CORE3_ADDRESS_END

..gh.endasm.142:
	.endo	..gh.endasm.142

	stm	sp,{r0,r3}
..gh.beginasm.143:
	.endo	..gh.beginasm.143
ldr r4, =__PRIVATE_DATA_CORE3_LOAD_ADDRESS_START

..gh.endasm.144:
	.endo	..gh.endasm.144

.L1959:
;line514
..lin.7807341b..f72dc80e.0_35::
.LDWlin35:
	ldr	r0,[sp,12]
	ldr	r1,[sp,16]
	cmp	r0,r1
	ldrlo	r1,[sp,20]
	ldrlo	r2,[r1],4
	strlo	r2,[r0],4
	strlo	r0,[sp,12]
	strlo	r1,[sp,20]
	blo	.L1959
	b	.L1965
.L1964:
	ldr	r1,[r4],4
	str	r1,[r0],4
	str	r0,[sp]
.L1965:
	ldm	sp,{r0-r1}
	cmp	r0,r1
	blo	.L1964
.L1967:
	ldr	r0,[r5]
	cmp	r0,r6
	bne	.L1967
.L1871:
.LDW81:
	add	sp,sp,24
.L5432:

	pop	{r4-r6,pc}
__ghs_eofn_Startup_InitPrivateSections:
	.endf	Startup_InitPrivateSections
	.endf	Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
;privateCode	[sp,12]	local
;privateData	[sp]	local

	.section ".uncached_data","aw"
	.align	128
s_cpu01SyncFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.::
s_cpu01SyncFlag:	.data.b	1,0,0,0
	.space	12
	.space	112
	.endo	s_cpu01SyncFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.endo	s_cpu01SyncFlag
	.section ".bss","awb"
.L5085:
	.endo	.L5085
	.section ".ghcalltbl",""
	.align	4
.L5431:	.data.w	.L5430
	.endo	.L5431
	.section ".ghrettbl",""
.L5433:	.data.w	.L5432
	.endo	.L5433
	.text
..gh.f.a.1.e.145:
	.endo	..gh.f.a.1.e.145
__callee.Startup_InitCloneSections.v.v::
	.size	__callee.Startup_InitCloneSections.v.v,0
Startup_InitCloneSections::
.LDW91:
	push	{r4-r7,lr}
	sub	sp,sp,44
.LDW02:
	mov	r3,0
	mov	r1,r3
	mov	r2,r3
	mov	r7,r3
	mov	r12,r3
	mov	lr,r3
	mov	r5,r1
	mov	r6,r2
	str	r3,[sp,4]
	add	r0,sp,8
	stm	r0,{r1-r3,r5-r7,r12,lr}
..gh.beginasm.146:
	.endo	..gh.beginasm.146
    mrc        p15, 0, r0, c1, c0, 2    
    orr        r0, r0, #(0xF << 20)     
    mcr        p15, 0, r0, c1, c0, 2    
    isb                                 
    mov        r0, #0x40000000          
    vmsr       fpexc, r0                

..gh.endasm.147:
	.endo	..gh.endasm.147

;line575
..lin.7807341b..c9d10724.0_36::
.LDWlin36:
..gh.beginasm.148:
	.endo	..gh.beginasm.148
    mrc        p15, 0, r0, c15, c0, 0    
    orr        r0, r0, #0x3              
    mcr        p15, 0, r0, c15, c0, 0     

..gh.endasm.149:
	.endo	..gh.endasm.149

;line583
..lin.7807341b..c9d10724.0_37::
.LDWlin37:
..gh.beginasm.150:
	.endo	..gh.beginasm.150
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.151:
	.endo	..gh.endasm.151

;line585
..lin.7807341b..c9d10724.0_38::
.LDWlin38:
	mov	r1,1<<28
	ldr	r3,.L6102
	subs	r0,r0,1
	blo	.L5449
	beq	.L5471
	cmp	r0,2
	blo	.L5489
	beq	.L5507
	b	.L6103

.L6102:	.data.w	0x0020001f
	.endo	.L6102

.L6103:

;line685
..lin.7807341b..c9d10724.0_39::
.LDWlin39:
..gh.beginasm.152:
	.endo	..gh.beginasm.152
cpsid aif
1:b 1b

..gh.endasm.153:
	.endo	..gh.endasm.153

	b	.L5532
;line685
..lin.7807341b..c9d10724.0_40::
.LDWlin40:

.L6104:	.data.w	0x03f000ff
	.endo	.L6104

.L5449:
;line592
..lin.7807341b..c9d10724.0_41::
.LDWlin41:
	ldr	r12,.L6104
.L5455:
	mov	r0,1<<28
..gh.beginasm.154:
	.endo	..gh.beginasm.154
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r4, r2, #1         

..gh.endasm.155:
	.endo	..gh.endasm.155

	cmp	r4,0
	beq	.L5455
;line605
..lin.7807341b..c9d10724.0_42::
.LDWlin42:
	ldr	r1,.L6105
	b	.L6106

.L6105:	.data.w	0x30100027
	.endo	.L6105

.L6106:

;line605
..lin.7807341b..c9d10724.0_43::
.LDWlin43:
..gh.beginasm.156:
	.endo	..gh.beginasm.156
mcr p15, 0, r1, c9, c1, 1

..gh.endasm.157:
	.endo	..gh.endasm.157

..gh.beginasm.158:
	.endo	..gh.beginasm.158
mcr p15, 0, r3, c9, c1, 2

..gh.endasm.159:
	.endo	..gh.endasm.159

;line606
..lin.7807341b..c9d10724.0_44::
.LDWlin44:
	mov	r1,r12
	mov	r0,0
.L6123:

	bl	Itmu_ClearModuleRam
	mov	r3,1<<28
..gh.beginasm.160:
	.endo	..gh.beginasm.160
1:ldrex r1, [r3]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r3]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.161:
	.endo	..gh.endasm.161

;line614
..lin.7807341b..c9d10724.0_45::
.LDWlin45:
	ldr	r1,.L6107
	mov	r0,0
	str	r0,[r1]
	str	r0,[r1,4]
	str	r0,[r1,8]
	str	r0,[r1,12]
.L6125:

	bl	Startup_StartSlaveCore
	b	.L5532

.L6107:	.data.w	s_cpu01SyncFlag
	.endo	.L6107

.L6108:	.data.w	0x11110000
	.endo	.L6108

.L5471:
;line626
..lin.7807341b..c9d10724.0_46::
.LDWlin46:
	ldr	r0,[r1,64]
	ldr	r2,.L6108
	cmp	r0,r2
	bne	.L5471
	mov	r12,255<<8
.L5474:
	mov	r0,1<<28
..gh.beginasm.162:
	.endo	..gh.beginasm.162
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r4, r2, #1         

..gh.endasm.163:
	.endo	..gh.endasm.163

	cmp	r4,0
	beq	.L5474
;line636
..lin.7807341b..c9d10724.0_47::
.LDWlin47:
	ldr	r1,.L6109
	b	.L6110

.L6109:	.data.w	0x30500027
	.endo	.L6109

.L6110:

;line636
..lin.7807341b..c9d10724.0_48::
.LDWlin48:
..gh.beginasm.164:
	.endo	..gh.beginasm.164
mcr p15, 0, r1, c9, c1, 1

..gh.endasm.165:
	.endo	..gh.endasm.165

..gh.beginasm.166:
	.endo	..gh.beginasm.166
mcr p15, 0, r3, c9, c1, 2

..gh.endasm.167:
	.endo	..gh.endasm.167

;line637
..lin.7807341b..c9d10724.0_49::
.LDWlin49:
	mov	r1,r12
	mov	r0,0
.L6127:

	bl	Itmu_ClearModuleRam
	mov	r3,1<<28
..gh.beginasm.168:
	.endo	..gh.beginasm.168
1:ldrex r1, [r3]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r3]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.169:
	.endo	..gh.endasm.169

	b	.L5532
;line639
..lin.7807341b..c9d10724.0_50::
.LDWlin50:

.L6111:	.data.w	0x11110000
	.endo	.L6111

.L5489:
;line646
..lin.7807341b..c9d10724.0_51::
.LDWlin51:
	ldr	r0,[r1,64]
	ldr	r2,.L6111
	cmp	r0,r2
	bne	.L5489
	mov	r12,255
.L5492:
	mov	r0,1<<28
..gh.beginasm.170:
	.endo	..gh.beginasm.170
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r4, r2, #1         

..gh.endasm.171:
	.endo	..gh.endasm.171

	cmp	r4,0
	beq	.L5492
;line656
..lin.7807341b..c9d10724.0_52::
.LDWlin52:
	ldr	r1,.L6112
	b	.L6113

.L6112:	.data.w	0x31100023
	.endo	.L6112

.L6113:

;line656
..lin.7807341b..c9d10724.0_53::
.LDWlin53:
..gh.beginasm.172:
	.endo	..gh.beginasm.172
mcr p15, 0, r1, c9, c1, 1

..gh.endasm.173:
	.endo	..gh.endasm.173

..gh.beginasm.174:
	.endo	..gh.beginasm.174
mcr p15, 0, r3, c9, c1, 2

..gh.endasm.175:
	.endo	..gh.endasm.175

;line657
..lin.7807341b..c9d10724.0_54::
.LDWlin54:
	mov	r1,r12
	mov	r0,1
.L6129:

	bl	Itmu_ClearModuleRam
	mov	r3,1<<28
..gh.beginasm.176:
	.endo	..gh.beginasm.176
1:ldrex r1, [r3]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r3]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.177:
	.endo	..gh.endasm.177

	b	.L5532
;line659
..lin.7807341b..c9d10724.0_55::
.LDWlin55:

.L6114:	.data.w	0x11110000
	.endo	.L6114

.L5507:
;line665
..lin.7807341b..c9d10724.0_56::
.LDWlin56:
	ldr	r0,[r1,64]
	ldr	r2,.L6114
	cmp	r0,r2
	bne	.L5507
	mov	r12,255<<8
.L5510:
	mov	r0,1<<28
..gh.beginasm.178:
	.endo	..gh.beginasm.178
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r4, r2, #1         

..gh.endasm.179:
	.endo	..gh.endasm.179

	cmp	r4,0
	beq	.L5510
;line675
..lin.7807341b..c9d10724.0_57::
.LDWlin57:
	ldr	r1,.L6115
	b	.L6116

.L6115:	.data.w	0x31500023
	.endo	.L6115

.L6116:

;line675
..lin.7807341b..c9d10724.0_58::
.LDWlin58:
..gh.beginasm.180:
	.endo	..gh.beginasm.180
mcr p15, 0, r1, c9, c1, 1

..gh.endasm.181:
	.endo	..gh.endasm.181

..gh.beginasm.182:
	.endo	..gh.beginasm.182
mcr p15, 0, r3, c9, c1, 2

..gh.endasm.183:
	.endo	..gh.endasm.183

;line676
..lin.7807341b..c9d10724.0_59::
.LDWlin59:
	mov	r1,r12
	mov	r0,1
.L6131:

	bl	Itmu_ClearModuleRam
	mov	r3,1<<28
..gh.beginasm.184:
	.endo	..gh.beginasm.184
1:ldrex r1, [r3]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r3]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.185:
	.endo	..gh.endasm.185

.L5532:
;line693
..lin.7807341b..c9d10724.0_60::
.LDWlin60:
	add	r0,sp,16
	ldm	r0,{r1-r6}
..gh.beginasm.186:
	.endo	..gh.beginasm.186
ldr r4, =__INT_VECTOR_TABLE_ADDRESS_START

..gh.endasm.187:
	.endo	..gh.endasm.187

..gh.beginasm.188:
	.endo	..gh.beginasm.188
ldr r5, =__INT_VECTOR_TABLE_ADDRESS_END

..gh.endasm.189:
	.endo	..gh.endasm.189

..gh.beginasm.190:
	.endo	..gh.beginasm.190
ldr r6, =__INT_VECTOR_TABLE_LOAD_ADDRESS_START

..gh.endasm.191:
	.endo	..gh.endasm.191

;line696
..lin.7807341b..c9d10724.0_61::
.LDWlin61:
..gh.beginasm.192:
	.endo	..gh.beginasm.192
ldr r1, =__CODE_CLONE_ADDRESS_START

..gh.endasm.193:
	.endo	..gh.endasm.193

..gh.beginasm.194:
	.endo	..gh.beginasm.194
ldr r2, =__CODE_CLONE_ADDRESS_END

..gh.endasm.195:
	.endo	..gh.endasm.195

..gh.beginasm.196:
	.endo	..gh.beginasm.196
ldr r3, =__CODE_CLONE_LOAD_ADDRESS_START

..gh.endasm.197:
	.endo	..gh.endasm.197

	stm	r0,{r1-r6}
;line699
..lin.7807341b..c9d10724.0_62::
.LDWlin62:
	ldmib	sp,{r0-r7}
	mov	lr,r5
	mov	r12,r4
..gh.beginasm.198:
	.endo	..gh.beginasm.198
ldr r0, =__DATA_CLONE_ADDRESS_START

..gh.endasm.199:
	.endo	..gh.endasm.199

..gh.beginasm.200:
	.endo	..gh.beginasm.200
ldr r1, =__DATA_CLONE_ADDRESS_END

..gh.endasm.201:
	.endo	..gh.endasm.201

..gh.beginasm.202:
	.endo	..gh.beginasm.202
ldr r2, =__DATA_CLONE_LOAD_ADDRESS_START

..gh.endasm.203:
	.endo	..gh.endasm.203

	stmib	sp,{r0-r2}
;line704
..lin.7807341b..c9d10724.0_63::
.LDWlin63:
	mov	r1,r6
	mov	r2,r7
	ldr	r0,[sp,36]
..gh.beginasm.204:
	.endo	..gh.beginasm.204
   add   r2, r2, #0x3F        
   bic   r2, r2, #0x3F        
   cmp   r2, r1               
   ble   2f                   
1: ldmia  r0!, {r4-r7}        
   stmia  r1!, {r4-r7}        
   cmp  r2, r1                
   bgt  1b                    
2:                            

..gh.endasm.205:
	.endo	..gh.endasm.205

;line707
..lin.7807341b..c9d10724.0_64::
.LDWlin64:
	ldr	r1,.L6117
	b	.L6118

.L6117:	.data.w	Startup_EL2ExceptionTable
	.endo	.L6117

.L6118:

;line707
..lin.7807341b..c9d10724.0_65::
.LDWlin65:
..gh.beginasm.206:
	.endo	..gh.beginasm.206
mcr p15, 4, r1, c12, c0, 0

..gh.endasm.207:
	.endo	..gh.endasm.207

;line710
..lin.7807341b..c9d10724.0_66::
.LDWlin66:
	ldr	r1,.L6119
	b	.L6120

.L6119:	.data.w	Startup_EL1ExceptionTable
	.endo	.L6119

.L6120:

;line710
..lin.7807341b..c9d10724.0_67::
.LDWlin67:
..gh.beginasm.208:
	.endo	..gh.beginasm.208
mcr p15, 0, r1, c12, c0, 0

..gh.endasm.209:
	.endo	..gh.endasm.209

;line712
..lin.7807341b..c9d10724.0_68::
.LDWlin68:
..gh.beginasm.210:
	.endo	..gh.beginasm.210
   add   r12, r12, #0x3F        
   bic   r12, r12, #0x3F        
   cmp   r12, r3               
   ble   2f                   
1: ldmia  lr!, {r4-r7}        
   stmia  r3!, {r4-r7}        
   cmp  r12, r3                
   bgt  1b                    
2:                            

..gh.endasm.211:
	.endo	..gh.endasm.211

;line714
..lin.7807341b..c9d10724.0_69::
.LDWlin69:
	ldmib	sp,{r1-r3}
..gh.beginasm.212:
	.endo	..gh.beginasm.212
   add   r2, r2, #0x3F        
   bic   r2, r2, #0x3F        
   cmp   r2, r1               
   ble   2f                   
1: ldmia  r3!, {r4-r7}        
   stmia  r1!, {r4-r7}        
   cmp  r2, r1                
   bgt  1b                    
2:                            

..gh.endasm.213:
	.endo	..gh.endasm.213

;line719
..lin.7807341b..c9d10724.0_70::
.LDWlin70:
	ldr	r0,.L6121
	b	.L6122

.L6121:	.data.w	Startup_InitStack
	.endo	.L6121

.L6122:

;line719
..lin.7807341b..c9d10724.0_71::
.LDWlin71:
..gh.beginasm.214:
	.endo	..gh.beginasm.214
bx r0

..gh.endasm.215:
	.endo	..gh.endasm.215

.LDW12:
;line720
..lin.7807341b..c9d10724.0_72::
.LDWlin72:
	add	sp,sp,44
.L6133:

	pop	{r4-r7,pc}
__ghs_eofn_Startup_InitCloneSections::
	.endf	Startup_InitCloneSections
;vectorTable	[sp,28]	local
;cloneCode	[sp,16]	local
;cloneData	[sp,4]	local
;clearBits	r12	local

	.section ".bss","awb"
.L5898:
	.endo	.L5898
	.section ".ghcalltbl",""
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
	.section ".ghrettbl",""
.L6134:	.data.w	.L6133
	.endo	.L6134
	.data
	.global	__caller.Itmu_ClearModuleRam.i.ii

	.global	__caller.Itmu_ClearModuleRam.i.ii

	.global	__caller.Itmu_ClearModuleRam.i.ii

	.global	__caller.Itmu_ClearModuleRam.i.ii

	.text
..gh.f.a.1.e.216:
	.endo	..gh.f.a.1.e.216
	.global	Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_InitStack:
.LDW22:
.LDW32:
	ldr	r0,.L6186
	b	.L6187

.L6186:	.data.w	Startup_InitHypStack
	.endo	.L6186

.L6187:

;line791
..lin.7807341b..6e8270e1.0_73::
.LDWlin73:
..gh.beginasm.217:
	.endo	..gh.beginasm.217
bx r0

..gh.endasm.218:
	.endo	..gh.endasm.218

.LDW42:
.L6188:

;line792
..lin.7807341b..6e8270e1.0_74::
.LDWlin74:
	ret	
__ghs_eofn_Startup_InitStack:
	.endf	Startup_InitStack
	.endf	Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section ".bss","awb"
.L6168:
	.endo	.L6168
	.section ".ghrettbl",""
.L6189:	.data.w	.L6188
	.endo	.L6189
	.text
..gh.f.a.1.e.219:
	.endo	..gh.f.a.1.e.219
	.global	Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_InitHypStack:
.LDW52:
	str	lr,[sp,-8]!
.LDW62:
..gh.beginasm.220:
	.endo	..gh.beginasm.220
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.221:
	.endo	..gh.endasm.221

;line825
..lin.7807341b..b1194df2.0_75::
.LDWlin75:
	ldr	r1,.L6378
	subs	r0,r0,1
	blo	.L6197
	beq	.L6198
	cmp	r0,2
	blo	.L6199
	beq	.L6200
	b	.L6379

.L6378:	.data.w	0x10000200
	.endo	.L6378

.L6379:

;line865
..lin.7807341b..b1194df2.0_76::
.LDWlin76:
..gh.beginasm.222:
	.endo	..gh.beginasm.222
cpsid aif
1:b 1b

..gh.endasm.223:
	.endo	..gh.endasm.223

	b	.L6203
.L6197:
;line830
..lin.7807341b..b1194df2.0_77::
.LDWlin77:
..gh.beginasm.224:
	.endo	..gh.beginasm.224
ldr r0, =__CORE0_HYP_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.225:
	.endo	..gh.endasm.225

;line832
..lin.7807341b..b1194df2.0_78::
.LDWlin78:
..gh.beginasm.226:
	.endo	..gh.beginasm.226
msr   sp_svc, r1 

..gh.endasm.227:
	.endo	..gh.endasm.227

;line833
..lin.7807341b..b1194df2.0_79::
.LDWlin79:
	b	.L6203
.L6198:
..gh.beginasm.228:
	.endo	..gh.beginasm.228
ldr r0, =__CORE1_HYP_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.229:
	.endo	..gh.endasm.229

;line841
..lin.7807341b..b1194df2.0_80::
.LDWlin80:
	add	r0,r1,1<<9
..gh.beginasm.230:
	.endo	..gh.beginasm.230
msr   sp_svc, r0 

..gh.endasm.231:
	.endo	..gh.endasm.231

;line842
..lin.7807341b..b1194df2.0_81::
.LDWlin81:
	b	.L6203
.L6199:
..gh.beginasm.232:
	.endo	..gh.beginasm.232
ldr r0, =__CORE2_HYP_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.233:
	.endo	..gh.endasm.233

;line850
..lin.7807341b..b1194df2.0_82::
.LDWlin82:
	add	r0,r1,1<<10
..gh.beginasm.234:
	.endo	..gh.beginasm.234
msr   sp_svc, r0 

..gh.endasm.235:
	.endo	..gh.endasm.235

;line851
..lin.7807341b..b1194df2.0_83::
.LDWlin83:
	b	.L6203
.L6200:
..gh.beginasm.236:
	.endo	..gh.beginasm.236
ldr r0, =__CORE3_HYP_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.237:
	.endo	..gh.endasm.237

;line858
..lin.7807341b..b1194df2.0_84::
.LDWlin84:
	add	r0,r1,3<<9
..gh.beginasm.238:
	.endo	..gh.beginasm.238
msr   sp_svc, r0 

..gh.endasm.239:
	.endo	..gh.endasm.239

.L6203:
;line870
..lin.7807341b..b1194df2.0_85::
.LDWlin85:
	ldr	r2,.L6380
	b	.L6381

.L6380:	.data.w	Startup_EL1ResetHandler
	.endo	.L6380

.L6381:

;line870
..lin.7807341b..b1194df2.0_86::
.LDWlin86:
..gh.beginasm.240:
	.endo	..gh.beginasm.240
    mrs   r0, cpsr                      
    mov   r1, #0x13                     
    bfi   r0, r1, #0, #6                
    msr   spsr_hyp, r0                  
    mov   r0, r2                        
    msr   elr_hyp, r0                   
    dsb                                 
    isb                                 
    eret                                

..gh.endasm.241:
	.endo	..gh.endasm.241

.LDW72:
.L6382:

;line871
..lin.7807341b..b1194df2.0_87::
.LDWlin87:
	ldr	pc,[sp],8
__ghs_eofn_Startup_InitHypStack:
	.endf	Startup_InitHypStack
	.endf	Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section ".bss","awb"
.L6292:
	.endo	.L6292
	.section ".ghrettbl",""
.L6383:	.data.w	.L6382
	.endo	.L6383
	.text
..gh.f.a.1.e.242:
	.endo	..gh.f.a.1.e.242
	.global	Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_EL1ResetHandler:
.LDW82:
	push	{r4-r5,lr}
	sub	sp,sp,28
.LDW92:
..gh.beginasm.243:
	.endo	..gh.beginasm.243
 mrc p15, 0, r1, c0, c0, 5
 and r4, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r4, r4, r1         

..gh.endasm.244:
	.endo	..gh.endasm.244

;line908
..lin.7807341b..e49c5d5a.0_88::
.LDWlin88:
	mov	r2,24
	ldr	r1,.L6736
	mov	r0,sp
.L6738:

	bl	memcpy
	mov	r1,sp
	mov	r0,0
.L6740:

	bl	MPU_Hal_SetEL1Re
	mov	r0,5<<29
	mov	r1,sp
	str	r0,[sp]
	mov	r0,1
.L6742:

	bl	MPU_Hal_SetEL1Re
.L6744:

	bl	MPU_Hal_EnableEL1Bg
.L6746:

	bl	MPU_Hal_EnableEL1
	mov	r5,1<<28
	subs	r4,r4,1
	blo	.L6391
	beq	.L6392
	cmp	r4,2
	blo	.L6393
	beq	.L6394
	b	.L6737

.L6736:	.data.w	.L6628
	.endo	.L6736

.L6737:

;line1049
..lin.7807341b..e49c5d5a.0_89::
.LDWlin89:
..gh.beginasm.245:
	.endo	..gh.beginasm.245
cpsid aif
1:b 1b

..gh.endasm.246:
	.endo	..gh.endasm.246

	b	.L6397
.L6391:
;line932
..lin.7807341b..e49c5d5a.0_90::
.LDWlin90:
..gh.beginasm.247:
	.endo	..gh.beginasm.247
cps #(0x1F)

..gh.endasm.248:
	.endo	..gh.endasm.248

..gh.beginasm.249:
	.endo	..gh.beginasm.249
ldr r0, =__CORE0_USER_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.250:
	.endo	..gh.endasm.250

;line935
..lin.7807341b..e49c5d5a.0_91::
.LDWlin91:
..gh.beginasm.251:
	.endo	..gh.beginasm.251
cps #(0x11)

..gh.endasm.252:
	.endo	..gh.endasm.252

..gh.beginasm.253:
	.endo	..gh.beginasm.253
ldr r0, =__CORE0_FIQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.254:
	.endo	..gh.endasm.254

;line938
..lin.7807341b..e49c5d5a.0_92::
.LDWlin92:
..gh.beginasm.255:
	.endo	..gh.beginasm.255
cps #(0x12)

..gh.endasm.256:
	.endo	..gh.endasm.256

..gh.beginasm.257:
	.endo	..gh.beginasm.257
ldr r0, =__CORE0_IRQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.258:
	.endo	..gh.endasm.258

;line941
..lin.7807341b..e49c5d5a.0_93::
.LDWlin93:
..gh.beginasm.259:
	.endo	..gh.beginasm.259
cps #(0x1B)

..gh.endasm.260:
	.endo	..gh.endasm.260

..gh.beginasm.261:
	.endo	..gh.beginasm.261
ldr r0, =__CORE0_UNDEFINED_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.262:
	.endo	..gh.endasm.262

;line944
..lin.7807341b..e49c5d5a.0_94::
.LDWlin94:
..gh.beginasm.263:
	.endo	..gh.beginasm.263
cps #(0x17)

..gh.endasm.264:
	.endo	..gh.endasm.264

..gh.beginasm.265:
	.endo	..gh.beginasm.265
ldr r0, =__CORE0_ABORT_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.266:
	.endo	..gh.endasm.266

;line947
..lin.7807341b..e49c5d5a.0_95::
.LDWlin95:
..gh.beginasm.267:
	.endo	..gh.beginasm.267
cps #(0x13)

..gh.endasm.268:
	.endo	..gh.endasm.268

..gh.beginasm.269:
	.endo	..gh.beginasm.269
ldr r0, =__CORE0_KERNEL_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.270:
	.endo	..gh.endasm.270

;line948
..lin.7807341b..e49c5d5a.0_96::
.LDWlin96:
	b	.L6397
.L6392:
..gh.beginasm.271:
	.endo	..gh.beginasm.271
cps #(0x1F)

..gh.endasm.272:
	.endo	..gh.endasm.272

..gh.beginasm.273:
	.endo	..gh.beginasm.273
ldr r0, =__CORE1_USER_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.274:
	.endo	..gh.endasm.274

;line957
..lin.7807341b..e49c5d5a.0_97::
.LDWlin97:
..gh.beginasm.275:
	.endo	..gh.beginasm.275
cps #(0x11)

..gh.endasm.276:
	.endo	..gh.endasm.276

..gh.beginasm.277:
	.endo	..gh.beginasm.277
ldr r0, =__CORE1_FIQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.278:
	.endo	..gh.endasm.278

;line960
..lin.7807341b..e49c5d5a.0_98::
.LDWlin98:
..gh.beginasm.279:
	.endo	..gh.beginasm.279
cps #(0x12)

..gh.endasm.280:
	.endo	..gh.endasm.280

..gh.beginasm.281:
	.endo	..gh.beginasm.281
ldr r0, =__CORE1_IRQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.282:
	.endo	..gh.endasm.282

;line963
..lin.7807341b..e49c5d5a.0_99::
.LDWlin99:
..gh.beginasm.283:
	.endo	..gh.beginasm.283
cps #(0x1B)

..gh.endasm.284:
	.endo	..gh.endasm.284

..gh.beginasm.285:
	.endo	..gh.beginasm.285
ldr r0, =__CORE1_UNDEFINED_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.286:
	.endo	..gh.endasm.286

;line966
..lin.7807341b..e49c5d5a.0_100::
.LDWlin100:
..gh.beginasm.287:
	.endo	..gh.beginasm.287
cps #(0x17)

..gh.endasm.288:
	.endo	..gh.endasm.288

..gh.beginasm.289:
	.endo	..gh.beginasm.289
ldr r0, =__CORE1_ABORT_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.290:
	.endo	..gh.endasm.290

;line969
..lin.7807341b..e49c5d5a.0_101::
.LDWlin101:
..gh.beginasm.291:
	.endo	..gh.beginasm.291
cps #(0x13)

..gh.endasm.292:
	.endo	..gh.endasm.292

..gh.beginasm.293:
	.endo	..gh.beginasm.293
ldr r0, =__CORE1_KERNEL_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.294:
	.endo	..gh.endasm.294

.L6398:
;line972
..lin.7807341b..e49c5d5a.0_102::
.LDWlin102:
	mov	r0,r5
..gh.beginasm.295:
	.endo	..gh.beginasm.295
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r3, r2, #1         

..gh.endasm.296:
	.endo	..gh.endasm.296

	cmp	r3,0
	beq	.L6398
;line977
..lin.7807341b..e49c5d5a.0_103::
.LDWlin103:
	ldr	r0,[r5,64]
	orr	r0,r0,1
	str	r0,[r5,64]
..gh.beginasm.297:
	.endo	..gh.beginasm.297
1:ldrex r1, [r5]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r5]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.298:
	.endo	..gh.endasm.298

	b	.L6397
.L6393:
;line986
..lin.7807341b..e49c5d5a.0_104::
.LDWlin104:
..gh.beginasm.299:
	.endo	..gh.beginasm.299
cps #(0x1F)

..gh.endasm.300:
	.endo	..gh.endasm.300

..gh.beginasm.301:
	.endo	..gh.beginasm.301
ldr r0, =__CORE2_USER_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.302:
	.endo	..gh.endasm.302

;line989
..lin.7807341b..e49c5d5a.0_105::
.LDWlin105:
..gh.beginasm.303:
	.endo	..gh.beginasm.303
cps #(0x11)

..gh.endasm.304:
	.endo	..gh.endasm.304

..gh.beginasm.305:
	.endo	..gh.beginasm.305
ldr r0, =__CORE2_FIQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.306:
	.endo	..gh.endasm.306

;line992
..lin.7807341b..e49c5d5a.0_106::
.LDWlin106:
..gh.beginasm.307:
	.endo	..gh.beginasm.307
cps #(0x12)

..gh.endasm.308:
	.endo	..gh.endasm.308

..gh.beginasm.309:
	.endo	..gh.beginasm.309
ldr r0, =__CORE2_IRQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.310:
	.endo	..gh.endasm.310

;line995
..lin.7807341b..e49c5d5a.0_107::
.LDWlin107:
..gh.beginasm.311:
	.endo	..gh.beginasm.311
cps #(0x1B)

..gh.endasm.312:
	.endo	..gh.endasm.312

..gh.beginasm.313:
	.endo	..gh.beginasm.313
ldr r0, =__CORE2_UNDEFINED_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.314:
	.endo	..gh.endasm.314

;line998
..lin.7807341b..e49c5d5a.0_108::
.LDWlin108:
..gh.beginasm.315:
	.endo	..gh.beginasm.315
cps #(0x17)

..gh.endasm.316:
	.endo	..gh.endasm.316

..gh.beginasm.317:
	.endo	..gh.beginasm.317
ldr r0, =__CORE2_ABORT_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.318:
	.endo	..gh.endasm.318

;line1001
..lin.7807341b..e49c5d5a.0_109::
.LDWlin109:
..gh.beginasm.319:
	.endo	..gh.beginasm.319
cps #(0x13)

..gh.endasm.320:
	.endo	..gh.endasm.320

..gh.beginasm.321:
	.endo	..gh.beginasm.321
ldr r0, =__CORE2_KERNEL_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.322:
	.endo	..gh.endasm.322

.L6409:
;line1004
..lin.7807341b..e49c5d5a.0_110::
.LDWlin110:
	mov	r0,r5
..gh.beginasm.323:
	.endo	..gh.beginasm.323
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r3, r2, #1         

..gh.endasm.324:
	.endo	..gh.endasm.324

	cmp	r3,0
	beq	.L6409
;line1009
..lin.7807341b..e49c5d5a.0_111::
.LDWlin111:
	ldr	r0,[r5,64]
	orr	r0,r0,2
	str	r0,[r5,64]
..gh.beginasm.325:
	.endo	..gh.beginasm.325
1:ldrex r1, [r5]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r5]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.326:
	.endo	..gh.endasm.326

	b	.L6397
.L6394:
;line1017
..lin.7807341b..e49c5d5a.0_112::
.LDWlin112:
..gh.beginasm.327:
	.endo	..gh.beginasm.327
cps #(0x1F)

..gh.endasm.328:
	.endo	..gh.endasm.328

..gh.beginasm.329:
	.endo	..gh.beginasm.329
ldr r0, =__CORE3_USER_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.330:
	.endo	..gh.endasm.330

;line1020
..lin.7807341b..e49c5d5a.0_113::
.LDWlin113:
..gh.beginasm.331:
	.endo	..gh.beginasm.331
cps #(0x11)

..gh.endasm.332:
	.endo	..gh.endasm.332

..gh.beginasm.333:
	.endo	..gh.beginasm.333
ldr r0, =__CORE3_FIQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.334:
	.endo	..gh.endasm.334

;line1023
..lin.7807341b..e49c5d5a.0_114::
.LDWlin114:
..gh.beginasm.335:
	.endo	..gh.beginasm.335
cps #(0x12)

..gh.endasm.336:
	.endo	..gh.endasm.336

..gh.beginasm.337:
	.endo	..gh.beginasm.337
ldr r0, =__CORE3_IRQ_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.338:
	.endo	..gh.endasm.338

;line1026
..lin.7807341b..e49c5d5a.0_115::
.LDWlin115:
..gh.beginasm.339:
	.endo	..gh.beginasm.339
cps #(0x1B)

..gh.endasm.340:
	.endo	..gh.endasm.340

..gh.beginasm.341:
	.endo	..gh.beginasm.341
ldr r0, =__CORE3_UNDEFINED_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.342:
	.endo	..gh.endasm.342

;line1029
..lin.7807341b..e49c5d5a.0_116::
.LDWlin116:
..gh.beginasm.343:
	.endo	..gh.beginasm.343
cps #(0x17)

..gh.endasm.344:
	.endo	..gh.endasm.344

..gh.beginasm.345:
	.endo	..gh.beginasm.345
ldr r0, =__CORE3_ABORT_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.346:
	.endo	..gh.endasm.346

;line1032
..lin.7807341b..e49c5d5a.0_117::
.LDWlin117:
..gh.beginasm.347:
	.endo	..gh.beginasm.347
cps #(0x13)

..gh.endasm.348:
	.endo	..gh.endasm.348

..gh.beginasm.349:
	.endo	..gh.beginasm.349
ldr r0, =__CORE3_KERNEL_STACK_ADDRESS_END 
mov sp, r0                                

..gh.endasm.350:
	.endo	..gh.endasm.350

.L6420:
;line1035
..lin.7807341b..e49c5d5a.0_118::
.LDWlin118:
	mov	r0,r5
..gh.beginasm.351:
	.endo	..gh.beginasm.351
 mov r1, #1                
 ldrex r2, [r0]            
 cmp r2, r1                
 beq 1f                    
 dsb                       
 strex r2, r1, [r0]        
 dsb                       
1: eor r3, r2, #1         

..gh.endasm.352:
	.endo	..gh.endasm.352

	cmp	r3,0
	beq	.L6420
;line1040
..lin.7807341b..e49c5d5a.0_119::
.LDWlin119:
	ldr	r0,[r5,64]
	orr	r0,r0,4
	str	r0,[r5,64]
..gh.beginasm.353:
	.endo	..gh.beginasm.353
1:ldrex r1, [r5]             
 cmp r1, #1                  
 bne 2f                      
 mov r1, #0                  
 dsb                         
 strex r2, r1, [r5]          
 dsb                         
 cmp r2, #0                  
 bne 1b                      
2:                           

..gh.endasm.354:
	.endo	..gh.endasm.354

.L6397:
.L6748:

;line1054
..lin.7807341b..e49c5d5a.0_120::
.LDWlin120:
	bl	Startup_InitPrivateSections
..gh.beginasm.355:
	.endo	..gh.beginasm.355
MRC p15, 0, r0, c14, c1, 0

..gh.endasm.356:
	.endo	..gh.endasm.356

;line1066
..lin.7807341b..e49c5d5a.0_121::
.LDWlin121:
	orr	r0,r0,1
..gh.beginasm.357:
	.endo	..gh.beginasm.357
MCR p15, 0, r0, c14, c1, 0

..gh.endasm.358:
	.endo	..gh.endasm.358

;line1070
..lin.7807341b..e49c5d5a.0_122::
.LDWlin122:
..gh.beginasm.359:
	.endo	..gh.beginasm.359
dmb

..gh.endasm.360:
	.endo	..gh.endasm.360

;line1072
..lin.7807341b..e49c5d5a.0_123::
.LDWlin123:
..gh.beginasm.361:
	.endo	..gh.beginasm.361
 cpsie if  

..gh.endasm.362:
	.endo	..gh.endasm.362

.L6750:

;line1074
..lin.7807341b..e49c5d5a.0_124::
.LDWlin124:
	bl	_main
..gh.beginasm.363:
	.endo	..gh.beginasm.363
14: nop        
    nop        
    nop        
    b  14b     

..gh.endasm.364:
	.endo	..gh.endasm.364

.LDW03:
;line1077
..lin.7807341b..e49c5d5a.0_125::
.LDWlin125:
	add	sp,sp,28
.L6752:

	pop	{r4-r5,pc}
__ghs_eofn_Startup_EL1ResetHandler:
	.endf	Startup_EL1ResetHandler
	.endf	Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
;xipRegionCfg	[sp]	local
;.L6589	.L6628	static

	.section ".bss","awb"
.L6588:
	.endo	.L6588
	.section ".rodata","a"
	.align	4
.L6628:	.data.b	0,0,0,80
	.data.b	0,0,0,8
	.space	4
	.data.b	2,0,0,0
	.data.b	1,0,0,0
	.data.b	1,0,0,0
	.endo	.L6628
	.section ".ghcalltbl",""
.L6739:	.data.w	.L6738
	.endo	.L6739
.L6741:	.data.w	.L6740
	.endo	.L6741
.L6743:	.data.w	.L6742
	.endo	.L6743
.L6745:	.data.w	.L6744
	.endo	.L6745
.L6747:	.data.w	.L6746
	.endo	.L6747
.L6749:	.data.w	.L6748
	.endo	.L6749
.L6751:	.data.w	.L6750
	.endo	.L6751
	.section ".ghrettbl",""
.L6753:	.data.w	.L6752
	.endo	.L6753
	.data
	.global	__caller._main.i.v

	.global	__caller.MPU_Hal_EnableEL1.v.v

	.global	__caller.MPU_Hal_EnableEL1Bg.v.v

	.global	__caller.MPU_Hal_SetEL1Re.v.ip

	.global	__caller.MPU_Hal_SetEL1Re.v.ip

	.text
	.section ".user_code","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..1::
..gh.f.a.1.e.365:
	.endo	..gh.f.a.1.e.365
__callee.Start.v.v::
	.size	__callee.Start.v.v,0
Start::
.LDW13:
.LDW23:
..gh.beginasm.366:
	.endo	..gh.beginasm.366
 cpsie a 
 ldr r0, =0x10000200 
 ldr r1, =0x10000400 
 ldr r2, =0x10000600 
 ldr r3, =0x10000800 
 ldr r9, =0xFFFF 
 ldr r10, =0x100 
 ldr r11, =0x101 
 mrc p15, 0, r4, c0, c0, 5
 and r4, r4, r9
 cmp r4, #0
 beq core0Pro
 cmp r4, #1
 beq core1Pro
 cmp r4, r10
 beq core2Pro
 cmp r4, r11
 beq core3Pro
core0Pro: mov sp, r0
 b ProEnd
core1Pro: mov sp, r1
 b ProEnd
core2Pro: mov sp, r2
 b ProEnd
core3Pro: mov sp, r3
ProEnd:mov r0, sp
 mov r1, #0x21
 sub r0, r0, #0x200
1:stm r0!, {r5-r8}
 subs r1,r1,#1
 bgt 1b
 isb
 ldr r0,=Startup_InitCloneSections
 bx r0

..gh.endasm.367:
	.endo	..gh.endasm.367

.LDW33:
;line1154
..lin.7807341b..e1e39b3.1_126::
__ghs_eofn_Start::
	.endf	Start

	.section ".bss","awb"
.L6791:
	.endo	.L6791
	.section ".user_code","ax"
	.section ".init_default_vector","ax"
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..2::
	.align	4
..gh.f.a.1.e.368:
	.endo	..gh.f.a.1.e.368
	.global	Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_EL2ExceptionTable:
.LDW43:
.LDW53:
..gh.beginasm.369:
	.endo	..gh.beginasm.369
    ldr pc, =Start                          
    ldr pc, =EL2_UndefinedException        
    ldr pc, =EL2_HVCHandler                 
    ldr pc, =EL2_PrefetchAbortException     
    ldr pc, =EL2_DataAbortException         
    ldr pc, =EL2_HypModeEntryHandler        
    ldr pc, =EL2_IRQHandler                 
    ldr pc, =EL2_FIQHandler                 

..gh.endasm.370:
	.endo	..gh.endasm.370

.LDW63:
;line225
..lin.7807341b..ace66951.2_127::
__ghs_eofn_Startup_EL2ExceptionTable:
	.endf	Startup_EL2ExceptionTable
	.endf	Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section ".bss","awb"
.L6840:
	.endo	.L6840
	.section ".init_default_vector","ax"
..gh.f.a.1.e.371:
	.endo	..gh.f.a.1.e.371
	.global	Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.:
Startup_EL1ExceptionTable:
.LDW73:
.LDW83:
..gh.beginasm.372:
	.endo	..gh.beginasm.372
    ldr pc, =Start                          
    ldr pc, =EL1_UndefinedException        
    ldr pc, =EL1_SVCHandler                 
    ldr pc, =EL1_PrefetchAbortException     
    ldr pc, =EL1_DataAbortException         
    ldr pc, =EL1_Reserved                   
    ldr pc, =EL1_IRQHandler                 
    ldr pc, =EL1_FIQHandler                 

..gh.endasm.373:
	.endo	..gh.endasm.373

.LDW93:
;line238
..lin.7807341b..99efb90.2_128::
__ghs_eofn_Startup_EL1ExceptionTable:
	.endf	Startup_EL1ExceptionTable
	.endf	Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section ".bss","awb"
.L6888:
	.endo	.L6888
	.section ".init_default_vector","ax"
;s_cpu01SyncFlag	s_cpu01SyncFlag	static

	.ghsnote info, 29, 8195, 131712
	.text
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..0::
	.section ".init_default_vector","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..2::
	.section ".user_code","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..1::
	.section ".init_default_vector","ax"
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	190,8,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,83,116,97,114,116,117,112,47,115,116,97,114,116,117,112,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 20
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+20
	.section	.debug_str		;off: 164
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+164
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
	.data.b	68,10,0,0
	.data.b	2,0
	.data.b	48,3,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,83,116,97,114,116,117,112,47,115,116,97,114,116,117,112,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,100,101,118,46,104,0
	.data.b	0,0,0
	.data.b	46,92,83,116,97,114,116,117,112,47,115,116,97,114,116,117,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,83,116,97,114,116,117,112,47,115,116,97,114,116,117,112,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,105,116,109,117,92,105,110,99,92,105,116,109,117,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,73,116,109,117,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,77,99,97,108,108,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,99,111,114,101,92,105,110,99,92,109,112,117,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,116,104,97,54,52,49,50,95,99,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,105,112,99,92,105,110,99,92,103,105,112,99,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,105,112,99,92,105,110,99,92,103,105,112,99,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,114,101,103,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,71,105,112,99,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,83,100,107,95,77,101,109,77,97,112,46,104,0
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
	.data.w	.Ldw_begin+468
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
	.section	.debug_str		;off: 186
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+186
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
	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 39
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 51
	.data.b	23
	.data.w	.Ldw_begin+364
	.data.b	0

	.section	.debug_abbrev		;off: 46
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 57
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

	.data.b	53
	.data.w	.Ldw_begin+64

	.section	.debug_abbrev		;off: 55
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 72
	.data.b	47
	.data.w	.Ldw_begin+480

	.section	.debug_abbrev		;off: 62
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 77
	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+72
	.data.b	0

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 200
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 87
	.data.w	.Ldw_str_begin+200
	.data.b	7
	.data.b	4

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+72
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+552

	.data.b	53
	.data.w	.Ldw_begin+123

	.data.b	47
	.data.w	.Ldw_begin+128

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+133
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+552

	.data.b	47
	.data.w	.Ldw_begin+147

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+152
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+607

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+166
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+952

	.data.b	53
	.data.w	.Ldw_begin+183

	.data.b	74
	.data.w	.Ldw_begin+364
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+188
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+188
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 214
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 222
	.data.w	.Ldw_str_begin+214
	.data.b	7
	.data.b	2

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

	.data.b	53
	.data.w	.Ldw_begin+400

	.data.b	42
	.section	.debug_str		;off: 229
	.data.b	105,110,116,0
	.section	.debug_info		;off: 252
	.data.w	.Ldw_str_begin+229
	.data.b	5
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 233
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 259
	.data.w	.Ldw_str_begin+233
	.data.b	7
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	60
	.data.w	.Ldw_begin+400

	.section	.debug_abbrev		;off: 69
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 272
	.data.b	56
	.data.w	.Ldw_begin+251
	.data.b	4
	.data.b	0
	.data.b	14

	.section	.debug_abbrev		;off: 80
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 280
	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+400

	.section	.debug_abbrev		;off: 93
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 286
	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+281

	.data.b	56
	.data.w	.Ldw_begin+251
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+251
	.data.b	1

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+364
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+898

	.data.b	53
	.data.w	.Ldw_begin+334

	.data.b	47
	.data.w	.Ldw_begin+339

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+376
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+344
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 246
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 365
	.data.w	.Ldw_str_begin+246
	.data.b	51
	.data.b	29
	.data.b	5
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

	.section	.debug_info		;off: 376
	.data.b	45
	.section	.debug_str		;off: 254
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 377
	.data.w	.Ldw_str_begin+254
	.data.b	56
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 260
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 389
	.data.w	.Ldw_str_begin+260
	.data.b	60
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+221

	.data.b	45
	.section	.debug_str		;off: 267
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 401
	.data.w	.Ldw_str_begin+267
	.data.b	64
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+86

	.data.b	52
	.section	.debug_str		;off: 274
	.data.b	0
	.section	.debug_info		;off: 413
	.data.w	.Ldw_str_begin+274
	.data.b	36
	.data.b	1
	.data.b	6
	.data.b	4
	.data.b	1

	.section	.debug_abbrev		;off: 115
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

	.section	.debug_info		;off: 422
	.data.b	51
	.section	.debug_str		;off: 275
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 423
	.data.w	.Ldw_str_begin+275
	.data.b	37
	.data.b	5
	.data.b	6
	.data.b	0

	.section	.debug_abbrev		;off: 132
	.data.b	51
	.data.b	40
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	28,13
	.data.b	0,0

	.section	.debug_info		;off: 431
	.data.b	51
	.section	.debug_str		;off: 292
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 432
	.data.w	.Ldw_str_begin+292
	.data.b	38
	.data.b	5
	.data.b	6
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 309
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 441
	.data.w	.Ldw_str_begin+309
	.data.b	39
	.data.b	5
	.data.b	6
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 326
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 450
	.data.w	.Ldw_str_begin+326
	.data.b	40
	.data.b	5
	.data.b	6
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 343
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 459
	.data.w	.Ldw_str_begin+343
	.data.b	41
	.data.b	5
	.data.b	6
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 360
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 469
	.data.w	.Ldw_str_begin+360
	.data.b	42
	.data.b	3
	.data.b	6
	.data.w	.Ldw_begin+412

	.data.b	45
	.section	.debug_str		;off: 372
	.data.b	70,117,110,99,116,105,111,110,78,111,80,97,114,97,109,0
	.section	.debug_info		;off: 481
	.data.w	.Ldw_str_begin+372
	.data.b	190,1
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+67

	.data.b	71
	.data.b	193,1
	.data.b	1
	.data.b	10
	.data.b	12
	.data.b	1

	.section	.debug_abbrev		;off: 147
	.data.b	71
	.data.b	19
	.data.b	1
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	11,15
	.data.b	50,11
	.data.b	0,0

	.section	.debug_info		;off: 500
	.data.b	40
	.section	.debug_str		;off: 388
	.data.b	99,111,112,121,68,97,116,97,73,109,97,103,101,65,100,100,114,0
	.section	.debug_info		;off: 501
	.data.w	.Ldw_str_begin+388
	.data.b	194,1
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+246
	.data.b	2,35
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 162
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

	.section	.debug_info		;off: 517
	.data.b	40
	.section	.debug_str		;off: 406
	.data.b	99,111,112,121,68,97,116,97,76,105,109,105,116,65,100,100,114,0
	.section	.debug_info		;off: 518
	.data.w	.Ldw_str_begin+406
	.data.b	195,1
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+246
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 424
	.data.b	99,111,112,121,68,97,116,97,76,111,97,100,65,100,100,114,0
	.section	.debug_info		;off: 535
	.data.w	.Ldw_str_begin+424
	.data.b	196,1
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+246
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 441
	.data.b	83,116,97,114,116,117,112,95,67,111,112,121,68,97,116,97,0
	.section	.debug_info		;off: 553
	.data.w	.Ldw_str_begin+441
	.data.b	197,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+493

	.data.b	71
	.data.b	200,1
	.data.b	1
	.data.b	10
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 458
	.data.b	99,108,101,97,114,73,109,97,103,101,65,100,100,114,0
	.section	.debug_info		;off: 573
	.data.w	.Ldw_str_begin+458
	.data.b	201,1
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+246
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 473
	.data.b	99,108,101,97,114,76,105,109,105,116,65,100,100,114,0
	.section	.debug_info		;off: 590
	.data.w	.Ldw_str_begin+473
	.data.b	202,1
	.data.b	13
	.data.b	10
	.data.w	.Ldw_begin+246
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 488
	.data.b	83,116,97,114,116,117,112,95,67,108,101,97,114,68,97,116,97,0
	.section	.debug_info		;off: 608
	.data.w	.Ldw_str_begin+488
	.data.b	203,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+565

	.data.b	52
	.section	.debug_str		;off: 506
	.data.b	0
	.section	.debug_info		;off: 621
	.data.w	.Ldw_str_begin+506
	.data.b	43
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 507
	.data.b	77,80,85,95,78,79,78,69,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 631
	.data.w	.Ldw_str_begin+507
	.data.b	44
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 526
	.data.b	77,80,85,95,85,78,80,82,69,68,73,67,84,65,66,76,69,0
	.section	.debug_info		;off: 640
	.data.w	.Ldw_str_begin+526
	.data.b	45
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 544
	.data.b	77,80,85,95,79,85,84,69,82,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 649
	.data.w	.Ldw_str_begin+544
	.data.b	46
	.data.b	5
	.data.b	14
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 564
	.data.b	77,80,85,95,73,78,78,69,82,95,83,72,65,82,69,65,66,76,69,0
	.section	.debug_info		;off: 658
	.data.w	.Ldw_str_begin+564
	.data.b	47
	.data.b	5
	.data.b	14
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 584
	.data.b	77,80,85,95,83,104,97,114,101,97,98,105,108,105,116,121,70,105,101,108,100,0
	.section	.debug_info		;off: 668
	.data.w	.Ldw_str_begin+584
	.data.b	48
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+620

	.data.b	52
	.section	.debug_str		;off: 606
	.data.b	0
	.section	.debug_info		;off: 680
	.data.w	.Ldw_str_begin+606
	.data.b	52
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 607
	.data.b	77,80,85,95,69,76,49,82,87,95,69,76,48,78,79,78,69,0
	.section	.debug_info		;off: 690
	.data.w	.Ldw_str_begin+607
	.data.b	53
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 625
	.data.b	77,80,85,95,69,76,49,82,87,95,69,76,48,82,87,0
	.section	.debug_info		;off: 699
	.data.w	.Ldw_str_begin+625
	.data.b	57
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 641
	.data.b	77,80,85,95,69,76,49,82,79,95,69,76,48,78,79,78,69,0
	.section	.debug_info		;off: 708
	.data.w	.Ldw_str_begin+641
	.data.b	61
	.data.b	5
	.data.b	14
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 659
	.data.b	77,80,85,95,69,76,49,82,79,95,69,76,48,82,79,0
	.section	.debug_info		;off: 717
	.data.w	.Ldw_str_begin+659
	.data.b	65
	.data.b	5
	.data.b	14
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 675
	.data.b	77,80,85,95,69,76,65,99,99,101,115,115,80,101,114,109,105,115,115,105,111,110,0
	.section	.debug_info		;off: 727
	.data.w	.Ldw_str_begin+675
	.data.b	67
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+679

	.data.b	52
	.section	.debug_str		;off: 698
	.data.b	0
	.section	.debug_info		;off: 739
	.data.w	.Ldw_str_begin+698
	.data.b	71
	.data.b	1
	.data.b	14
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 699
	.data.b	77,80,85,95,69,88,69,67,85,84,69,95,80,69,82,77,73,84,84,69,68,0
	.section	.debug_info		;off: 749
	.data.w	.Ldw_str_begin+699
	.data.b	72
	.data.b	5
	.data.b	14
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 721
	.data.b	77,80,85,95,69,88,69,67,85,84,69,95,78,69,86,69,82,0
	.section	.debug_info		;off: 758
	.data.w	.Ldw_str_begin+721
	.data.b	73
	.data.b	5
	.data.b	14
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 739
	.data.b	77,80,85,95,69,78,0
	.section	.debug_info		;off: 768
	.data.w	.Ldw_str_begin+739
	.data.b	74
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+738

	.data.b	71
	.data.b	84
	.data.b	1
	.data.b	14
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 746
	.data.b	77,80,85,95,83,116,97,114,116,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 786
	.data.w	.Ldw_str_begin+746
	.data.b	85
	.data.b	12
	.data.b	14
	.data.w	.Ldw_begin+400
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 763
	.data.b	77,80,85,95,82,101,103,105,111,110,83,105,122,101,0
	.section	.debug_info		;off: 802
	.data.w	.Ldw_str_begin+763
	.data.b	86
	.data.b	12
	.data.b	14
	.data.w	.Ldw_begin+400
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 778
	.data.b	77,80,85,95,83,104,97,114,101,70,105,101,108,100,0
	.section	.debug_info		;off: 818
	.data.w	.Ldw_str_begin+778
	.data.b	87
	.data.b	27
	.data.b	14
	.data.w	.Ldw_begin+667
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 793
	.data.b	77,80,85,95,65,99,99,80,101,114,109,0
	.section	.debug_info		;off: 834
	.data.w	.Ldw_str_begin+793
	.data.b	88
	.data.b	28
	.data.b	14
	.data.w	.Ldw_begin+726
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 805
	.data.b	77,80,85,95,88,78,0
	.section	.debug_info		;off: 850
	.data.w	.Ldw_str_begin+805
	.data.b	89
	.data.b	12
	.data.b	14
	.data.w	.Ldw_begin+767
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 812
	.data.b	77,80,85,95,82,101,103,105,111,110,69,110,97,98,108,101,0
	.section	.debug_info		;off: 866
	.data.w	.Ldw_str_begin+812
	.data.b	90
	.data.b	12
	.data.b	14
	.data.w	.Ldw_begin+388
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 829
	.data.b	77,80,85,95,65,116,116,73,110,100,101,120,0
	.section	.debug_info		;off: 882
	.data.w	.Ldw_str_begin+829
	.data.b	91
	.data.b	12
	.data.b	14
	.data.w	.Ldw_begin+388
	.data.b	2,35
	.data.b	22
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 842
	.data.b	77,80,85,95,82,101,103,105,111,110,65,116,116,0
	.section	.debug_info		;off: 899
	.data.w	.Ldw_str_begin+842
	.data.b	92
	.data.b	3
	.data.b	14
	.data.w	.Ldw_begin+779

	.data.b	71
	.data.b	203,1
	.data.b	1
	.data.b	17
	.data.b	64
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 856
	.data.b	108,111,99,107,83,116,97,116,117,115,0
	.section	.debug_info		;off: 918
	.data.w	.Ldw_str_begin+856
	.data.b	204,1
	.data.b	12
	.data.b	17
	.data.w	.Ldw_begin+400
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 867
	.data.b	114,101,115,101,114,118,101,100,0
	.section	.debug_info		;off: 935
	.data.w	.Ldw_str_begin+867
	.data.b	205,1
	.data.b	12
	.data.b	17
	.data.w	.Ldw_begin+265
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 876
	.data.b	71,105,112,99,95,76,111,99,107,0
	.section	.debug_info		;off: 953
	.data.w	.Ldw_str_begin+876
	.data.b	206,1
	.data.b	3
	.data.b	17
	.data.w	.Ldw_begin+910

	.data.b	6
	.section	.debug_str		;off: 886
	.data.b	115,95,99,112,117,48,49,83,121,110,99,70,108,97,103,0
	.section	.debug_info		;off: 966
	.data.w	.Ldw_str_begin+886
	.data.b	140,1
	.data.b	37
	.data.b	1
	.data.w	.Ldw_begin+286
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	s_cpu01SyncFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.

	.section	.debug_abbrev		;off: 181
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

	.section	.debug_info		;off: 986
	.data.b	27
	.section	.debug_str		;off: 902
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 987
	.data.w	.Ldw_str_begin+902
	.data.b	63
	.data.b	31
	.data.b	6
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 202
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

	.section	.debug_info		;off: 1004
	.data.b	37

	.section	.debug_abbrev		;off: 229
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 1005
	.data.b	8
	.section	.debug_str		;off: 922
	.data.b	105,100,0
	.section	.debug_info		;off: 1006
	.data.w	.Ldw_str_begin+922
	.data.b	65
	.data.b	17
	.data.b	6
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	0

	.section	.debug_abbrev		;off: 234
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

	.section	.debug_info		;off: 1019
	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 925
	.data.b	65,115,115,101,114,116,0
	.section	.debug_info		;off: 1022
	.data.w	.Ldw_str_begin+925
	.data.b	49
	.data.b	24
	.data.b	8
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 253
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

	.section	.debug_info		;off: 1035
	.data.b	20
	.section	.debug_str		;off: 932
	.data.b	99,111,110,100,0
	.section	.debug_info		;off: 1036
	.data.w	.Ldw_str_begin+932
	.data.b	49
	.data.b	39
	.data.b	8
	.data.w	.Ldw_begin+364
	.data.b	0

	.section	.debug_abbrev		;off: 278
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

	.section	.debug_info		;off: 1048
	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 937
	.data.b	83,116,97,114,116,117,112,95,69,76,50,69,120,99,101,112,116,105,111,110,84,97,98,108,101,0
	.section	.debug_info		;off: 1052
	.data.w	.Ldw_str_begin+937
	.data.b	214,1
	.data.b	35
	.data.b	10
	.data.w	Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL2ExceptionTable
	.data.b	1
	.data.b	93
	.data.b	128,128,1
	.data.b	124
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 295
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
	.data.w	Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL2ExceptionTable-Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 826
	.data.b	0,5,2
	.data.w	Startup_EL2ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	4
	.data.b	10
	.data.b	6
	.data.b	3
	.data.b	216,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Startup_EL2ExceptionTable
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1083
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.section	.debug_abbrev		;off: 341
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 1092
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 963
	.data.b	83,116,97,114,116,117,112,95,69,76,49,69,120,99,101,112,116,105,111,110,84,97,98,108,101,0
	.section	.debug_info		;off: 1095
	.data.w	.Ldw_str_begin+963
	.data.b	227,1
	.data.b	35
	.data.b	10
	.data.w	Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL1ExceptionTable
	.data.b	1
	.data.b	93
	.data.b	128,128,1
	.data.b	124
	.data.b	0
	.data.b	4
	.data.b	0
	.data.b	0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL1ExceptionTable-Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 857
	.data.b	0,5,2
	.data.w	Startup_EL1ExceptionTable..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	4
	.data.b	10
	.data.b	6
	.data.b	3
	.data.b	229,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Startup_EL1ExceptionTable
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1126
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 989
	.data.b	83,116,97,114,116,117,112,95,74,117,109,112,84,111,70,117,110,99,116,105,111,110,0
	.section	.debug_info		;off: 1138
	.data.w	.Ldw_str_begin+989
	.data.b	138,2
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1012
	.data.b	112,70,117,110,99,116,105,111,110,0
	.section	.debug_info		;off: 1153
	.data.w	.Ldw_str_begin+1012
	.data.b	138,2
	.data.b	69
	.data.b	10
	.data.w	.Ldw_begin+72
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1022
	.data.b	83,116,97,114,116,117,112,95,83,101,116,84,67,77,65,100,100,114,0
	.section	.debug_info		;off: 1170
	.data.w	.Ldw_str_begin+1022
	.data.b	219,2
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1041
	.data.b	66,84,67,77,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 1185
	.data.w	.Ldw_str_begin+1041
	.data.b	219,2
	.data.b	50
	.data.b	10
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	20
	.section	.debug_str		;off: 1053
	.data.b	67,84,67,77,65,100,100,114,101,115,115,0
	.section	.debug_info		;off: 1199
	.data.w	.Ldw_str_begin+1053
	.data.b	219,2
	.data.b	70
	.data.b	10
	.data.w	.Ldw_begin+400
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1065
	.data.b	83,116,97,114,116,117,112,95,69,120,105,116,69,76,50,87,105,116,104,83,86,67,77,111,100,101,0
	.section	.debug_info		;off: 1216
	.data.w	.Ldw_str_begin+1065
	.data.b	251,2
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1092
	.data.b	112,70,117,110,99,116,105,111,110,0
	.section	.debug_info		;off: 1231
	.data.w	.Ldw_str_begin+1092
	.data.b	251,2
	.data.b	73
	.data.b	10
	.data.w	.Ldw_begin+72
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1102
	.data.b	83,116,97,114,116,117,112,95,69,110,97,98,108,101,86,70,80,0
	.section	.debug_info		;off: 1248
	.data.w	.Ldw_str_begin+1102
	.data.b	166,3
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1120
	.data.b	83,116,97,114,116,117,112,95,73,110,102,105,110,105,116,101,76,111,111,112,0
	.section	.debug_info		;off: 1266
	.data.w	.Ldw_str_begin+1120
	.data.b	242,3
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1141
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,65,84,67,77,68,97,116,97,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1284
	.data.w	.Ldw_str_begin+1141
	.data.b	149,4
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1169
	.data.b	112,68,97,116,97,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1299
	.data.w	.Ldw_str_begin+1169
	.data.b	149,4
	.data.b	83
	.data.b	10
	.data.w	.Ldw_begin+133
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1182
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,68,97,116,97,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1316
	.data.w	.Ldw_str_begin+1182
	.data.b	192,4
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1206
	.data.b	112,68,97,116,97,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1331
	.data.w	.Ldw_str_begin+1206
	.data.b	192,4
	.data.b	73
	.data.b	10
	.data.w	.Ldw_begin+152
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1219
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,66,115,115,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1348
	.data.w	.Ldw_str_begin+1219
	.data.b	141,5
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1242
	.data.b	112,66,115,115,83,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1363
	.data.w	.Ldw_str_begin+1242
	.data.b	141,5
	.data.b	66
	.data.b	10
	.data.w	.Ldw_begin+166
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1254
	.data.b	83,116,97,114,116,117,112,95,69,110,97,98,108,101,76,76,80,80,0
	.section	.debug_info		;off: 1380
	.data.w	.Ldw_str_begin+1254
	.data.b	209,5
	.data.b	24
	.data.b	10
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1273
	.data.b	95,109,97,105,110,0
	.section	.debug_info		;off: 1398
	.data.w	.Ldw_str_begin+1273
	.data.b	31
	.data.b	12
	.data.b	9
	.data.w	.Ldw_begin+251
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1279
	.data.b	73,116,109,117,95,67,108,101,97,114,77,111,100,117,108,101,82,97,109,0
	.section	.debug_info		;off: 1417
	.data.w	.Ldw_str_begin+1279
	.data.b	179,1
	.data.b	16
	.data.b	11
	.data.w	.Ldw_begin+364
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1299
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,49,0
	.section	.debug_info		;off: 1437
	.data.w	.Ldw_str_begin+1299
	.data.b	119
	.data.b	13
	.data.b	14
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1317
	.data.b	77,80,85,95,72,97,108,95,69,110,97,98,108,101,69,76,49,66,103,0
	.section	.debug_info		;off: 1452
	.data.w	.Ldw_str_begin+1317
	.data.b	209,1
	.data.b	13
	.data.b	14
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1337
	.data.b	77,80,85,95,72,97,108,95,83,101,116,69,76,49,82,101,0
	.section	.debug_info		;off: 1468
	.data.w	.Ldw_str_begin+1337
	.data.b	142,2
	.data.b	13
	.data.b	14
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 1354
	.data.b	71,105,112,99,95,72,97,108,95,71,101,116,76,111,99,107,0
	.section	.debug_info		;off: 1484
	.data.w	.Ldw_str_begin+1354
	.data.b	168,2
	.data.b	27
	.data.b	17
	.data.w	.Ldw_begin+364
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1371
	.data.b	112,76,111,99,107,0
	.section	.debug_info		;off: 1503
	.data.w	.Ldw_str_begin+1371
	.data.b	168,2
	.data.b	61
	.data.b	17
	.data.w	.Ldw_begin+188
	.data.b	0

	.data.b	37

	.data.b	8
	.section	.debug_str		;off: 1377
	.data.b	114,101,115,117,108,116,0
	.section	.debug_info		;off: 1518
	.data.w	.Ldw_str_begin+1377
	.data.b	171,2
	.data.b	13
	.data.b	17
	.data.w	.Ldw_begin+364
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 1384
	.data.b	71,105,112,99,95,72,97,108,95,82,101,108,101,97,115,101,76,111,99,107,0
	.section	.debug_info		;off: 1535
	.data.w	.Ldw_str_begin+1384
	.data.b	207,2
	.data.b	24
	.data.b	17
	.data.b	0
	.data.b	3
	.data.b	0
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	20
	.section	.debug_str		;off: 1405
	.data.b	112,76,111,99,107,0
	.section	.debug_info		;off: 1550
	.data.w	.Ldw_str_begin+1405
	.data.b	207,2
	.data.b	62
	.data.b	17
	.data.w	.Ldw_begin+188
	.data.b	0

	.data.b	37

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1411
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,71,108,111,98,97,108,85,110,99,97,99,104,101,100,83,101,99,116,105,111,110,115,0
	.section	.debug_info		;off: 1567
	.data.w	.Ldw_str_begin+1411
	.data.b	198,1
	.data.b	14
	.data.b	1
	.data.w	Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitGlobalUncachedSections
	.data.b	1
	.data.b	93
	.data.b	208,143,1
	.data.b	104
	.data.b	0
	.data.b	52
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
	.data.w	Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitGlobalUncachedSections-Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 888
	.data.b	0,5,2
	.data.w	Startup_InitGlobalUncachedSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	198,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	59
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin4
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	172
	.data.b	172
	.data.b	44
	.data.b	61
	.data.b	0,5,2
	.data.w	.LDWlin5
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin6
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin7
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin8
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	171
	.data.b	171
	.data.b	43
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin9
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin10
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin11
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin12
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	171
	.data.b	171
	.data.b	43
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin14
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin15
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	0,5,2
	.data.w	.LDWlin16
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	171
	.data.b	171
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin17
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	75
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin18
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 1598
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.data.b	7
	.section	.debug_str		;off: 1446
	.data.b	103,108,111,98,97,108,68,97,116,97,0
	.section	.debug_info		;off: 1608
	.data.w	.Ldw_str_begin+1446
	.data.b	200,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin
	.section	.debug_loc		;off: 0
.Ldw_loc_begin:
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 350
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

	.section	.debug_info		;off: 1626
	.data.b	7
	.section	.debug_str		;off: 1457
	.data.b	117,110,99,97,99,104,101,100,68,97,116,97,0
	.section	.debug_info		;off: 1627
	.data.w	.Ldw_str_begin+1457
	.data.b	201,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+20
	.section	.debug_loc		;off: 20
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1645
	.data.b	7
	.section	.debug_str		;off: 1470
	.data.b	103,108,111,98,97,108,66,115,115,0
	.section	.debug_info		;off: 1646
	.data.w	.Ldw_str_begin+1470
	.data.b	202,1
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+40
	.section	.debug_loc		;off: 40
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1664
	.data.b	7
	.section	.debug_str		;off: 1480
	.data.b	117,110,99,97,99,104,101,100,66,115,115,0
	.section	.debug_info		;off: 1665
	.data.w	.Ldw_str_begin+1480
	.data.b	203,1
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+59
	.section	.debug_loc		;off: 59
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	82
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1683
	.data.b	7
	.section	.debug_str		;off: 1492
	.data.b	117,110,99,108,101,97,114,66,115,115,0
	.section	.debug_info		;off: 1684
	.data.w	.Ldw_str_begin+1492
	.data.b	204,1
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+607
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+78
	.section	.debug_loc		;off: 78
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1702
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1503
	.data.b	83,116,97,114,116,117,112,95,83,116,97,114,116,83,108,97,118,101,67,111,114,101,0
	.section	.debug_info		;off: 1705
	.data.w	.Ldw_str_begin+1503
	.data.b	168,2
	.data.b	13
	.data.b	1
	.data.w	Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_StartSlaveCore
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
	.data.w	Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_StartSlaveCore-Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1123
	.data.b	0,5,2
	.data.w	Startup_StartSlaveCore..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	168,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	11
	.data.b	12
	.data.b	59
	.data.b	11
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin19
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin20
	.data.b	3
	.data.b	125
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
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	13
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	11
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin21
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin22
	.data.b	3
	.data.b	125
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
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	13
	.data.b	59
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	29
	.data.b	0,5,2
	.data.w	.LDWlin23
	.data.b	3
	.data.b	125
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
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	13
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
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 1736
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	8
	.section	.debug_str		;off: 1526
	.data.b	108,111,111,112,0
	.section	.debug_info		;off: 1746
	.data.w	.Ldw_str_begin+1526
	.data.b	170,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+388
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1531
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,80,114,105,118,97,116,101,83,101,99,116,105,111,110,115,0
	.section	.debug_info		;off: 1763
	.data.w	.Ldw_str_begin+1531
	.data.b	137,3
	.data.b	14
	.data.b	1
	.data.w	Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitPrivateSections
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
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
	.data.w	Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitPrivateSections-Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1278
	.data.b	0,5,2
	.data.w	Startup_InitPrivateSections..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	137,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	75
	.data.b	61
	.data.b	0,5,2
	.data.w	.LDWlin24
	.data.b	12
	.data.b	2
	.data.b	40
	.data.b	0,5,2
	.data.w	.LDWlin25
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	248,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	13
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin26
	.data.b	3
	.data.b	135,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin27
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin28
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	125
	.data.b	13
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	172
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	29
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin29
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin30
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin31
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	172
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	77
	.data.b	12
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin32
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin33
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	172
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	77
	.data.b	12
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin34
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin35
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	172
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	24
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	12
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 1794
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	8
	.section	.debug_str		;off: 1559
	.data.b	105,100,0
	.section	.debug_info		;off: 1804
	.data.w	.Ldw_str_begin+1559
	.data.b	140,3
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1562
	.data.b	112,114,105,118,97,116,101,67,111,100,101,0
	.section	.debug_info		;off: 1819
	.data.w	.Ldw_str_begin+1562
	.data.b	141,3
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+97
	.section	.debug_loc		;off: 97
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1837
	.data.b	7
	.section	.debug_str		;off: 1574
	.data.b	112,114,105,118,97,116,101,68,97,116,97,0
	.section	.debug_info		;off: 1838
	.data.w	.Ldw_str_begin+1574
	.data.b	142,3
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+117
	.section	.debug_loc		;off: 117
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1856
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1586
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,67,108,111,110,101,83,101,99,116,105,111,110,115,0
	.section	.debug_info		;off: 1859
	.data.w	.Ldw_str_begin+1586
	.data.b	176,4
	.data.b	7
	.data.b	1
	.data.w	Startup_InitCloneSections
	.data.w	__ghs_eofn_Startup_InitCloneSections
	.data.b	1
	.data.b	93
	.data.b	240,129,1
	.data.b	112
	.data.b	0
	.data.b	60
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
	.data.w	Startup_InitCloneSections
	.data.w	__ghs_eofn_Startup_InitCloneSections-Startup_InitCloneSections
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1538
	.data.b	0,5,2
	.data.w	Startup_InitCloneSections
	.data.b	6
	.data.b	3
	.data.b	176,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	44
	.data.b	27
	.data.b	123
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin36
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin37
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin38
	.data.b	12
	.data.b	2
	.data.b	36
	.data.b	0,5,2
	.data.w	.LDWlin39
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	223,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin40
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin41
	.data.b	3
	.data.b	160,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	13
	.data.b	28
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin42
	.data.b	13
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin43
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin44
	.data.b	11
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin45
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	27
	.data.b	27
	.data.b	28
	.data.b	28
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin46
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	76
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin47
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin48
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin49
	.data.b	11
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin50
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin51
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	76
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin52
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin53
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin54
	.data.b	11
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin55
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin56
	.data.b	12
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	76
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin57
	.data.b	13
	.data.b	12
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin58
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin59
	.data.b	11
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin60
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin61
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin62
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin63
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin64
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin65
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin66
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin67
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin68
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin69
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin70
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin71
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin72
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 1890
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	8
	.section	.debug_str		;off: 1612
	.data.b	105,100,0
	.section	.debug_info		;off: 1900
	.data.w	.Ldw_str_begin+1612
	.data.b	178,4
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1615
	.data.b	118,101,99,116,111,114,84,97,98,108,101,0
	.section	.debug_info		;off: 1915
	.data.w	.Ldw_str_begin+1615
	.data.b	179,4
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+137
	.section	.debug_loc		;off: 137
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	28
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1933
	.data.b	7
	.section	.debug_str		;off: 1627
	.data.b	99,108,111,110,101,67,111,100,101,0
	.section	.debug_info		;off: 1934
	.data.w	.Ldw_str_begin+1627
	.data.b	180,4
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+157
	.section	.debug_loc		;off: 157
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	16
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1952
	.data.b	7
	.section	.debug_str		;off: 1637
	.data.b	99,108,111,110,101,68,97,116,97,0
	.section	.debug_info		;off: 1953
	.data.w	.Ldw_str_begin+1637
	.data.b	181,4
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+552
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+177
	.section	.debug_loc		;off: 177
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	4
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1971
	.data.b	7
	.section	.debug_str		;off: 1647
	.data.b	99,108,101,97,114,66,105,116,115,0
	.section	.debug_info		;off: 1972
	.data.w	.Ldw_str_begin+1647
	.data.b	183,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+400
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+197
	.section	.debug_loc		;off: 197
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	92
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 1990
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1657
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,83,116,97,99,107,0
	.section	.debug_info		;off: 1993
	.data.w	.Ldw_str_begin+1657
	.data.b	233,5
	.data.b	14
	.data.b	1
	.data.w	Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitStack
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitStack-Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 1994
	.data.b	0,5,2
	.data.w	Startup_InitStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	150,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin73
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin74
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2022
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1675
	.data.b	83,116,97,114,116,117,112,95,73,110,105,116,72,121,112,83,116,97,99,107,0
	.section	.debug_info		;off: 2034
	.data.w	.Ldw_str_begin+1675
	.data.b	178,6
	.data.b	14
	.data.b	1
	.data.w	Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitHypStack
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_InitHypStack-Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2032
	.data.b	0,5,2
	.data.w	Startup_InitHypStack..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	178,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin75
	.data.b	12
	.data.b	2
	.data.b	32
	.data.b	0,5,2
	.data.w	.LDWlin76
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	38
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin77
	.data.b	3
	.data.b	93
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin78
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin79
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin80
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin81
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin82
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin83
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin84
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin85
	.data.b	11
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	13
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin86
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin87
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 2065
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	8
	.section	.debug_str		;off: 1696
	.data.b	105,100,0
	.section	.debug_info		;off: 2075
	.data.w	.Ldw_str_begin+1696
	.data.b	180,6
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1699
	.data.b	83,116,97,114,116,117,112,95,69,76,49,82,101,115,101,116,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 2092
	.data.w	.Ldw_str_begin+1699
	.data.b	130,7
	.data.b	14
	.data.b	1
	.data.w	Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL1ResetHandler
	.data.b	1
	.data.b	93
	.data.b	176,128,1
	.data.b	120
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
	.data.w	Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.w	__ghs_eofn_Startup_EL1ResetHandler-Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2198
	.data.b	0,5,2
	.data.w	Startup_EL1ResetHandler..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cstartup.
	.data.b	6
	.data.b	3
	.data.b	130,7
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin88
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
	.data.b	61
	.data.b	43
	.data.b	60
	.data.b	28
	.data.b	28
	.data.b	2
	.data.b	32
	.data.b	0,5,2
	.data.w	.LDWlin89
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	244,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin90
	.data.b	3
	.data.b	139,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin91
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin92
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin93
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin94
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin95
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin96
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin97
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin98
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin99
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin100
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin101
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin102
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin103
	.data.b	13
	.data.b	12
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin104
	.data.b	11
	.data.b	3
	.data.b	6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin105
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin106
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin107
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin108
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin109
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin110
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin111
	.data.b	13
	.data.b	12
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin112
	.data.b	11
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin113
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin114
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin115
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin116
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin117
	.data.b	13
	.data.b	0,5,2
	.data.w	.LDWlin118
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin119
	.data.b	13
	.data.b	12
	.data.b	60
	.data.b	0,5,2
	.data.w	.LDWlin120
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	13
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin121
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin122
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	.LDWlin123
	.data.b	12
	.data.b	0,5,2
	.data.w	.LDWlin124
	.data.b	12
	.data.b	28
	.data.b	0,5,2
	.data.w	.LDWlin125
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 2123
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	8
	.section	.debug_str		;off: 1723
	.data.b	105,100,0
	.section	.debug_info		;off: 2133
	.data.w	.Ldw_str_begin+1723
	.data.b	132,7
	.data.b	17
	.data.b	1
	.data.w	.Ldw_begin+468
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1726
	.data.b	82,116,0
	.section	.debug_info		;off: 2148
	.data.w	.Ldw_str_begin+1726
	.data.b	133,7
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+400
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 1729
	.data.b	98,82,103,78,117,109,0
	.section	.debug_info		;off: 2163
	.data.w	.Ldw_str_begin+1729
	.data.b	138,7
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+376
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 1736
	.data.b	120,105,112,82,101,103,105,111,110,67,102,103,0
	.section	.debug_info		;off: 2178
	.data.w	.Ldw_str_begin+1736
	.data.b	140,7
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+898
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+216
	.section	.debug_loc		;off: 216
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	0
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 2196
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 1749
	.data.b	83,116,97,114,116,0
	.section	.debug_info		;off: 2199
	.data.w	.Ldw_str_begin+1749
	.data.b	211,8
	.data.b	17
	.data.b	1
	.data.w	Start
	.data.w	__ghs_eofn_Start
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

	.section	.debug_frame		;off: 360
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Start
	.data.w	__ghs_eofn_Start-Start
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 2603
	.data.b	0,5,2
	.data.w	Start
	.data.b	6
	.data.b	3
	.data.b	216,8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Start
	.data.b	3
	.data.b	41
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 2230
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

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
	.data.b	39
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
	.data.b	55
	.data.b	65,76,73,71,78,69,68,40,120,41,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,97,108,105,103,110,101,100,40,120,41,41,41,0
	.data.b	1
	.data.b	59
	.data.b	65,84,84,82,95,78,65,75,69,68,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,110,97,107,101,100,41,41,0
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
	.data.b	27
	.data.b	78,85,76,76,95,80,84,82,32,40,40,118,111,105,100,32,42,41,48,41,0
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
	.data.b	79
	.data.b	68,77,66,40,41,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,100,109,98,34,32,58,58,58,32,34,109,101,109,111,114,121,34,41,0
	.data.b	1
	.data.b	86
	.data.b	77,79,68,69,95,70,73,81,32,40,48,120,49,49,41,0
	.data.b	1
	.data.b	87
	.data.b	77,79,68,69,95,73,82,81,32,40,48,120,49,50,41,0
	.data.b	1
	.data.b	88
	.data.b	77,79,68,69,95,83,86,67,32,40,48,120,49,51,41,0
	.data.b	1
	.data.b	91
	.data.b	77,79,68,69,95,65,66,84,32,40,48,120,49,55,41,0
	.data.b	1
	.data.b	92
	.data.b	77,79,68,69,95,85,78,68,32,40,48,120,49,66,41,0
	.data.b	1
	.data.b	93
	.data.b	77,79,68,69,95,83,89,83,32,40,48,120,49,70,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	5
	.data.b	1
	.data.b	45
	.data.b	70,65,76,83,69,32,48,117,0
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	6
	.data.b	1
	.data.b	44
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	46
	.data.b	7
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
	.data.b	7
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	8
	.data.b	4
	.data.b	3
	.data.b	44
	.data.b	9
	.data.b	3
	.data.b	17
	.data.b	10
	.data.b	1
	.data.b	75
	.data.b	83,84,65,82,84,85,80,95,84,69,77,80,83,84,65,67,75,65,68,68,82,95,67,79,82,69,48,32,40,48,120,49,48,48,48,48,50,48,48,85,41,0
	.data.b	1
	.data.b	78
	.data.b	83,84,65,82,84,85,80,95,84,69,77,80,83,84,65,67,75,65,68,68,82,95,67,79,82,69,49,32,40,48,120,49,48,48,48,48,52,48,48,85,41,0
	.data.b	1
	.data.b	80
	.data.b	83,84,65,82,84,85,80,95,84,69,77,80,83,84,65,67,75,65,68,68,82,95,67,79,82,69,50,32,40,48,120,49,48,48,48,48,54,48,48,85,41,0
	.data.b	1
	.data.b	81
	.data.b	83,84,65,82,84,85,80,95,84,69,77,80,83,84,65,67,75,65,68,68,82,95,67,79,82,69,51,32,40,48,120,49,48,48,48,48,56,48,48,85,41,0
	.data.b	1
	.data.b	88
	.data.b	77,85,76,84,73,67,79,82,69,95,83,89,78,67,86,65,82,95,65,68,68,82,32,40,48,120,49,48,48,48,48,48,52,48,85,41,0
	.data.b	1
	.data.b	89
	.data.b	80,76,79,67,75,95,65,68,68,82,32,40,48,120,49,48,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	93
	.data.b	83,84,65,82,84,85,80,95,83,69,84,69,76,50,69,88,67,69,80,84,73,79,78,66,65,83,69,65,68,68,82,40,66,97,115,101,65,100,100,100,114,101,115,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76
	.data.b	69,40,34,109,99,114,32,112,49,53,44,32,52,44,32,37,91,114,48,93,44,32,99,49,50,44,32,99,48,44,32,48,34,32,58,58,91,114,48,93,32,34,114,34,40,38,66,97,115,101,65,100,100,100,114,101,115,115,115,41
	.data.b	32,58,32,34,109,101,109,111,114,121,34,44,32,34,114,48,34,41,59,32,125,0
	.data.b	1
	.data.b	100
	.data.b	83,84,65,82,84,85,80,95,83,69,84,69,76,49,69,88,67,69,80,84,73,79,78,66,65,83,69,65,68,68,82,40,66,97,115,101,65,100,100,100,114,101,115,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76
	.data.b	69,40,34,109,99,114,32,112,49,53,44,32,48,44,32,37,91,114,48,93,44,32,99,49,50,44,32,99,48,44,32,48,34,32,58,58,91,114,48,93,32,34,114,34,40,38,66,97,115,101,65,100,100,100,114,101,115,115,115,41
	.data.b	32,58,32,34,109,101,109,111,114,121,34,44,32,34,114,48,34,41,59,32,125,0
	.data.b	1
	.data.b	108
	.data.b	83,84,65,82,84,85,80,95,83,69,84,77,79,68,69,83,80,40,109,111,100,101,44,115,116,97,99,107,116,121,112,101,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,99,112,115,32,35,34,32,35,109,111
	.data.b	100,101,32,34,92,110,34,41,59,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,108,100,114,32,114,48,44,32,61,95,95,34,32,35,115,116,97,99,107,116,121,112,101,32,34,95,65,68,68,82,69,83,83,95,69,78
	.data.b	68,32,92,110,34,32,34,109,111,118,32,115,112,44,32,114,48,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,110,34,32,58,32,58,32,58,32,34
	.data.b	109,101,109,111,114,121,34,44,32,34,114,48,34,41,59,32,125,0
	.data.b	1
	.data.b	121
	.data.b	83,84,65,82,84,85,80,95,83,69,84,83,84,65,67,75,40,109,111,100,101,44,115,116,97,99,107,116,121,112,101,41,32,83,84,65,82,84,85,80,95,83,69,84,77,79,68,69,83,80,40,109,111,100,101,44,32,115,116,97
	.data.b	99,107,116,121,112,101,41,0
	.data.b	1
	.data.b	125
	.data.b	83,84,65,82,84,85,80,95,83,69,84,72,89,80,77,79,68,69,83,80,40,115,116,97,99,107,116,121,112,101,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,108,100,114,32,114,48,44,32,61,95,95,34
	.data.b	32,35,115,116,97,99,107,116,121,112,101,32,34,95,65,68,68,82,69,83,83,95,69,78,68,32,92,110,34,32,34,109,111,118,32,115,112,44,32,114,48,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
	.data.b	32,32,32,32,32,32,32,32,32,32,32,32,32,92,110,34,32,58,32,58,32,58,32,34,109,101,109,111,114,121,34,44,32,34,114,48,34,41,59,32,125,0
	.data.b	1
	.data.b	136,1
	.data.b	83,84,65,82,84,85,80,95,83,69,84,84,69,77,80,83,86,67,83,84,65,67,75,40,97,100,100,114,101,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34,109,115,114,32,32,32,115,112,95,115,118
	.data.b	99,44,32,37,48,32,92,110,34,58,58,34,114,34,40,97,100,100,114,101,115,115,41,58,41,59,32,125,0
	.data.b	1
	.data.b	142,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,73,77,65,71,69,66,65,83,69,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,97,100,100,114,101,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69,40
	.data.b	34,108,100,114,32,37,48,44,32,61,95,95,34,32,35,82,101,103,105,111,110,78,97,109,101,32,34,95,65,68,68,82,69,83,83,95,83,84,65,82,84,34,32,58,32,34,43,114,34,40,97,100,100,114,101,115,115,41,58,58
	.data.b	34,109,101,109,111,114,121,34,41,59,32,125,0
	.data.b	1
	.data.b	148,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,73,77,65,71,69,76,73,77,73,84,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,97,100,100,114,101,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69
	.data.b	40,34,108,100,114,32,37,48,44,32,61,95,95,34,32,35,82,101,103,105,111,110,78,97,109,101,32,34,95,65,68,68,82,69,83,83,95,69,78,68,34,32,58,32,34,43,114,34,40,97,100,100,114,101,115,115,41,58,58,34
	.data.b	109,101,109,111,114,121,34,41,59,32,125,0
	.data.b	1
	.data.b	154,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,73,77,65,71,69,66,83,83,76,73,77,73,84,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,97,100,100,114,101,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84
	.data.b	73,76,69,40,34,108,100,114,32,37,48,44,32,61,95,95,34,32,35,82,101,103,105,111,110,78,97,109,101,32,34,95,65,68,68,82,69,83,83,95,69,78,68,34,32,58,32,34,43,114,34,40,97,100,100,114,101,115,115,41
	.data.b	58,58,34,109,101,109,111,114,121,34,41,59,32,125,0
	.data.b	1
	.data.b	160,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,76,79,65,68,66,65,83,69,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,97,100,100,114,101,115,115,41,32,123,32,65,83,77,95,86,79,76,65,84,73,76,69,40,34
	.data.b	108,100,114,32,37,48,44,32,61,95,95,34,32,35,82,101,103,105,111,110,78,97,109,101,32,34,95,76,79,65,68,95,65,68,68,82,69,83,83,95,83,84,65,82,84,34,32,58,32,34,43,114,34,40,97,100,100,114,101,115
	.data.b	115,41,58,58,34,109,101,109,111,114,121,34,41,59,32,125,0
	.data.b	1
	.data.b	169,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,67,79,80,89,68,65,84,65,73,78,70,79,40,82,101,103,105,111,110,78,97,109,101,44,73,110,105,116,83,101,99,116,105,111,110,41,32,100,111,123,32,83,84,65,82,84,85,80,95
	.data.b	71,69,84,73,77,65,71,69,66,65,83,69,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,32,73,110,105,116,83,101,99,116,105,111,110,46,99,111,112,121,68,97,116,97,73,109,97,103,101,65,100,100,114,41,59
	.data.b	32,83,84,65,82,84,85,80,95,71,69,84,73,77,65,71,69,76,73,77,73,84,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,32,73,110,105,116,83,101,99,116,105,111,110,46,99,111,112,121,68,97,116,97,76
	.data.b	105,109,105,116,65,100,100,114,41,59,32,83,84,65,82,84,85,80,95,71,69,84,76,79,65,68,66,65,83,69,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,32,73,110,105,116,83,101,99,116,105,111,110,46,99
	.data.b	111,112,121,68,97,116,97,76,111,97,100,65,100,100,114,41,59,32,125,119,104,105,108,101,40,48,41,59,0
	.data.b	1
	.data.b	180,1
	.data.b	83,84,65,82,84,85,80,95,71,69,84,66,83,83,68,65,84,65,73,78,70,79,40,82,101,103,105,111,110,78,97,109,101,44,73,110,105,116,83,101,99,116,105,111,110,41,32,100,111,123,32,83,84,65,82,84,85,80,95,71
	.data.b	69,84,73,77,65,71,69,66,65,83,69,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,32,73,110,105,116,83,101,99,116,105,111,110,46,99,108,101,97,114,73,109,97,103,101,65,100,100,114,41,59,32,83,84,65
	.data.b	82,84,85,80,95,71,69,84,73,77,65,71,69,66,83,83,76,73,77,73,84,65,68,68,82,40,82,101,103,105,111,110,78,97,109,101,44,32,73,110,105,116,83,101,99,116,105,111,110,46,99,108,101,97,114,76,105,109,105,116
	.data.b	65,100,100,114,41,59,32,125,119,104,105,108,101,40,48,41,59,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	45
	.data.b	11
	.data.b	1
	.data.b	75
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,48,65,84,67,77,32,40,48,120,48,48,48,48,48,48,48,51,85,41,0
	.data.b	1
	.data.b	77
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,48,66,84,67,77,48,32,40,48,120,48,48,48,48,48,48,48,67,85,41,0
	.data.b	1
	.data.b	79
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,48,66,84,67,77,49,32,40,48,120,48,48,48,48,48,48,51,48,85,41,0
	.data.b	1
	.data.b	81
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,48,67,84,67,77,32,40,48,120,48,48,48,48,48,48,67,48,85,41,0
	.data.b	1
	.data.b	83
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,49,65,84,67,77,32,40,48,120,48,48,48,48,48,51,48,48,85,41,0
	.data.b	1
	.data.b	85
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,49,66,84,67,77,48,32,40,48,120,48,48,48,48,48,67,48,48,85,41,0
	.data.b	1
	.data.b	87
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,49,66,84,67,77,49,32,40,48,120,48,48,48,48,51,48,48,48,85,41,0
	.data.b	1
	.data.b	89
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,49,67,84,67,77,32,40,48,120,48,48,48,48,67,48,48,48,85,41,0
	.data.b	1
	.data.b	95
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,76,77,85,49,32,40,48,120,48,48,51,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	97
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,76,77,85,50,32,40,48,120,48,48,67,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	99
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,76,77,85,51,32,40,48,120,48,51,48,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	103
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,50,65,84,67,77,32,40,48,120,48,48,48,48,48,48,48,51,85,41,0
	.data.b	1
	.data.b	105
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,50,66,84,67,77,48,32,40,48,120,48,48,48,48,48,48,48,67,85,41,0
	.data.b	1
	.data.b	107
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,50,66,84,67,77,49,32,40,48,120,48,48,48,48,48,48,51,48,85,41,0
	.data.b	1
	.data.b	109
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,50,67,84,67,77,32,40,48,120,48,48,48,48,48,48,67,48,85,41,0
	.data.b	1
	.data.b	111
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,51,65,84,67,77,32,40,48,120,48,48,48,48,48,51,48,48,85,41,0
	.data.b	1
	.data.b	113
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,51,66,84,67,77,48,32,40,48,120,48,48,48,48,48,67,48,48,85,41,0
	.data.b	1
	.data.b	115
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,51,66,84,67,77,49,32,40,48,120,48,48,48,48,51,48,48,48,85,41,0
	.data.b	1
	.data.b	117
	.data.b	73,84,77,85,95,82,77,65,73,78,73,95,67,80,85,51,67,84,67,77,32,40,48,120,48,48,48,48,67,48,48,48,85,41,0
	.data.b	1
	.data.b	158,1
	.data.b	73,84,77,85,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,1
	.data.b	12
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
	.data.b	12
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	13
	.data.b	1
	.data.b	65
	.data.b	77,67,65,76,95,85,83,69,68,95,67,79,82,69,95,77,65,83,75,32,40,48,120,48,48,48,48,48,48,48,55,85,41,0
	.data.b	4
	.data.b	3
	.data.b	47
	.data.b	14
	.data.b	1
	.data.b	101
	.data.b	67,79,82,69,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	102
	.data.b	7
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
	.data.b	176,2
	.data.b	67,79,82,69,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	177,2
	.data.b	7
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	48
	.data.b	15
	.data.b	3
	.data.b	56
	.data.b	16
	.data.b	1
	.data.b	223,5
	.data.b	67,72,69,67,75,95,68,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	1
	.data.b	130,6
	.data.b	67,72,69,67,75,95,80,70,76,65,83,72,95,73,78,70,79,95,65,68,68,32,49,85,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	50
	.data.b	17
	.data.b	3
	.data.b	53
	.data.b	18
	.data.b	3
	.data.b	28
	.data.b	19
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	214,1
	.data.b	71,73,80,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	216,1
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,71,73,80,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	187,3
	.data.b	71,73,80,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	189,3
	.data.b	20
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	60
	.data.b	67,79,82,69,49,95,67,84,82,76,95,65,68,68,82,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,40,48,120,67,48,48,50,48,67,53,67,85,41,41,0
	.data.b	1
	.data.b	62
	.data.b	67,79,82,69,50,95,67,84,82,76,95,65,68,68,82,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,40,48,120,67,48,48,50,48,67,54,48,85,41,41,0
	.data.b	1
	.data.b	63
	.data.b	67,79,82,69,51,95,67,84,82,76,95,65,68,68,82,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,40,48,120,67,48,48,50,48,67,54,52,85,41,41,0
	.data.b	1
	.data.b	65
	.data.b	67,79,82,69,51,95,67,84,82,76,95,76,79,67,75,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,40,48,120,67,48,48,50,48,52,53,48,85,41,41,0
	.data.b	1
	.data.b	79
	.data.b	82,83,84,83,84,65,84,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,40,48,120,67,48,48,48,48,56,48,48,85,41,41,0
	.data.b	1
	.data.b	83
	.data.b	77,85,76,84,73,67,79,82,69,95,83,89,78,67,86,65,82,32,40,42,40,118,111,108,97,116,105,108,101,32,117,105,110,116,51,50,32,42,41,77,85,76,84,73,67,79,82,69,95,83,89,78,67,86,65,82,95,65,68,68
	.data.b	82,41,0
	.data.b	1
	.data.b	85
	.data.b	80,76,79,67,75,32,40,40,71,105,112,99,95,76,111,99,107,32,42,41,80,76,79,67,75,95,65,68,68,82,41,0
	.data.b	1
	.data.b	88
	.data.b	82,83,84,95,80,79,87,69,82,79,78,32,40,48,120,48,48,56,48,48,48,48,48,85,41,0
	.data.b	1
	.data.b	91
	.data.b	67,80,85,48,49,95,77,65,83,75,32,40,48,120,48,48,48,48,48,48,48,49,85,41,0
	.data.b	1
	.data.b	93
	.data.b	67,80,85,48,50,95,77,65,83,75,32,40,48,120,48,48,48,48,48,48,48,50,85,41,0
	.data.b	1
	.data.b	94
	.data.b	67,80,85,48,51,95,77,65,83,75,32,40,48,120,48,48,48,48,48,48,48,52,85,41,0
	.data.b	1
	.data.b	100
	.data.b	67,80,85,95,69,78,84,69,82,95,83,89,78,67,95,77,65,71,73,67,48,49,32,40,48,120,49,49,49,49,48,48,48,48,41,0
	.data.b	1
	.data.b	101
	.data.b	67,80,85,95,69,78,84,69,82,95,83,89,78,67,95,77,65,71,73,67,48,50,32,40,48,120,53,65,53,65,53,65,53,65,85,41,0
	.data.b	1
	.data.b	103
	.data.b	67,80,85,48,49,95,69,78,84,69,82,95,83,89,78,67,95,77,65,71,73,67,32,40,48,120,48,48,48,48,48,48,48,49,85,41,0
	.data.b	1
	.data.b	105
	.data.b	67,80,85,48,50,95,69,78,84,69,82,95,83,89,78,67,95,77,65,71,73,67,32,40,48,120,48,48,48,48,48,48,48,50,85,41,0
	.data.b	1
	.data.b	106
	.data.b	67,80,85,48,51,95,69,78,84,69,82,95,83,89,78,67,95,77,65,71,73,67,32,40,48,120,48,48,48,48,48,48,48,52,85,41,0
	.data.b	1
	.data.b	109
	.data.b	67,80,85,48,48,95,66,84,67,77,95,67,79,78,70,73,71,32,40,48,120,51,48,49,48,48,48,50,55,85,41,0
	.data.b	1
	.data.b	110
	.data.b	67,80,85,48,48,95,67,84,67,77,95,67,79,78,70,73,71,32,40,48,120,48,48,50,48,48,48,49,70,85,41,0
	.data.b	1
	.data.b	112
	.data.b	67,80,85,48,49,95,66,84,67,77,95,67,79,78,70,73,71,32,40,48,120,51,48,53,48,48,48,50,55,85,41,0
	.data.b	1
	.data.b	113
	.data.b	67,80,85,48,49,95,67,84,67,77,95,67,79,78,70,73,71,32,40,48,120,48,48,50,48,48,48,49,70,85,41,0
	.data.b	1
	.data.b	115
	.data.b	67,80,85,48,50,95,66,84,67,77,95,67,79,78,70,73,71,32,40,48,120,51,49,49,48,48,48,50,51,85,41,0
	.data.b	1
	.data.b	116
	.data.b	67,80,85,48,50,95,67,84,67,77,95,67,79,78,70,73,71,32,40,48,120,48,48,50,48,48,48,49,70,85,41,0
	.data.b	1
	.data.b	117
	.data.b	67,80,85,48,51,95,66,84,67,77,95,67,79,78,70,73,71,32,40,48,120,51,49,53,48,48,48,50,51,85,41,0
	.data.b	1
	.data.b	118
	.data.b	67,80,85,48,51,95,67,84,67,77,95,67,79,78,70,73,71,32,40,48,120,48,48,50,48,48,48,49,70,85,41,0
	.data.b	1
	.data.b	122
	.data.b	67,80,85,95,68,69,76,65,89,95,76,79,79,80,95,67,79,85,78,84,32,40,48,120,53,48,85,41,0
	.data.b	1
	.data.b	130,1
	.data.b	67,79,82,69,95,77,65,83,75,32,40,77,67,65,76,95,85,83,69,68,95,67,79,82,69,95,77,65,83,75,41,0
	.data.b	1
	.data.b	138,1
	.data.b	83,68,75,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,71,76,79,66,65,76,95,78,79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	3
	.data.b	139,1
	.data.b	21
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	58
	.data.b	73,78,83,73,68,69,95,83,68,75,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,71,76,79,66,65,76,95,78,79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	61
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	141,1
	.data.b	83,68,75,95,83,84,79,80,95,83,69,67,95,86,65,82,95,73,78,73,84,95,71,76,79,66,65,76,95,78,79,95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	3
	.data.b	143,1
	.data.b	21
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	208,8
	.data.b	83,68,75,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	210,8
	.data.b	21
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	215,2
	.data.b	73,78,83,73,68,69,95,83,68,75,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	218,2
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	131,9
	.data.b	83,68,75,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	133,9
	.data.b	21
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 371
	.data.b	0
